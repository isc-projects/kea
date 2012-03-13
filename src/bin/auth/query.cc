// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <dns/message.h>
#include <dns/rcode.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

#include <datasrc/client.h>

#include <auth/query.h>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <algorithm>            // for std::max
#include <vector>

using namespace std;
using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::dns::rdata;

// Commonly used helper callback object for vector<ConstRRsetPtr> to
// insert them to (the specified section of) a message.
namespace {
class RRsetInserter {
public:
    RRsetInserter(Message& msg, Message::Section section, bool dnssec) :
        msg_(msg), section_(section), dnssec_(dnssec)
    {}
    void operator()(const ConstRRsetPtr& rrset) {
        /*
         * FIXME:
         * The const-cast is wrong, but the Message interface seems
         * to insist.
         */
        msg_.addRRset(section_,
                      boost::const_pointer_cast<AbstractRRset>(rrset),
                      dnssec_);
    }

private:
    Message& msg_;
    const Message::Section section_;
    const bool dnssec_;
};

// This is a "constant" vector storing desired RR types for the additional
// section.  The vector is filled first time it's used.
const vector<RRType>&
A_AND_AAAA() {
    static vector<RRType> needed_types;
    if (needed_types.empty()) {
        needed_types.push_back(RRType::A());
        needed_types.push_back(RRType::AAAA());
    }
    return (needed_types);
}

// A wrapper for ZoneFinder::Context::getAdditional() so we don't include
// duplicate RRs.  This is not efficient, and we should actually unify
// this at the end of the process() method.  See also #1688.
void
getAdditional(const Name& qname, RRType qtype,
              ZoneFinder::Context& ctx, vector<ConstRRsetPtr>& results)
{
    vector<ConstRRsetPtr> additionals;
    ctx.getAdditional(A_AND_AAAA(), additionals);

    vector<ConstRRsetPtr>::const_iterator it = additionals.begin();
    vector<ConstRRsetPtr>::const_iterator it_end = additionals.end();
    for (; it != it_end; ++it) {
        if ((qtype == (*it)->getType() || qtype == RRType::ANY()) &&
            qname == (*it)->getName()) {
            continue;
        }
        results.push_back(*it);
    }
}
}

namespace isc {
namespace auth {

void
Query::addSOA(ZoneFinder& finder) {
    ZoneFinderContextPtr soa_ctx = finder.find(finder.getOrigin(),
                                               RRType::SOA(), dnssec_opt_);
    if (soa_ctx->code != ZoneFinder::SUCCESS) {
        isc_throw(NoSOA, "There's no SOA record in zone " <<
            finder.getOrigin().toText());
    } else {
        authorities_.push_back(soa_ctx->rrset);
    }
}

// Note: unless the data source client implementation or the zone content
// is broken, 'nsec' should be a valid NSEC RR.  Likewise, the call to
// find() in this method should result in NXDOMAIN and an NSEC RR that proves
// the non existent of matching wildcard.  If these assumptions aren't met
// due to a buggy data source implementation or a broken zone, we'll let
// underlying libdns++ modules throw an exception, which would result in
// either an SERVFAIL response or just ignoring the query.  We at least prevent
// a complete crash due to such broken behavior.
void
Query::addNXDOMAINProofByNSEC(ZoneFinder& finder, ConstRRsetPtr nsec) {
    if (nsec->getRdataCount() == 0) {
        isc_throw(BadNSEC, "NSEC for NXDOMAIN is empty");
    }

    // Add the NSEC proving NXDOMAIN to the authority section.
    authorities_.push_back(nsec);

    // Next, identify the best possible wildcard name that would match
    // the query name.  It's the longer common suffix with the qname
    // between the owner or the next domain of the NSEC that proves NXDOMAIN,
    // prefixed by the wildcard label, "*".  For example, for query name
    // a.b.example.com, if the NXDOMAIN NSEC is
    // b.example.com. NSEC c.example.com., the longer suffix is b.example.com.,
    // and the best possible wildcard is *.b.example.com.  If the NXDOMAIN
    // NSEC is a.example.com. NSEC c.b.example.com., the longer suffix
    // is the next domain of the NSEC, and we get the same wildcard name.
    const int qlabels = qname_.getLabelCount();
    const int olabels = qname_.compare(nsec->getName()).getCommonLabels();
    const int nlabels = qname_.compare(
        dynamic_cast<const generic::NSEC&>(nsec->getRdataIterator()->
                                           getCurrent()).
        getNextName()).getCommonLabels();
    const int common_labels = std::max(olabels, nlabels);
    const Name wildname(Name("*").concatenate(qname_.split(qlabels -
                                                           common_labels)));

    // Confirm the wildcard doesn't exist (this should result in NXDOMAIN;
    // otherwise we shouldn't have got NXDOMAIN for the original query in
    // the first place).
    ConstZoneFinderContextPtr fcontext =
        finder.find(wildname, RRType::NSEC(), dnssec_opt_);
    if (fcontext->code != ZoneFinder::NXDOMAIN || !fcontext->rrset ||
        fcontext->rrset->getRdataCount() == 0) {
        isc_throw(BadNSEC, "Unexpected result for wildcard NXDOMAIN proof");
    }

    // Add the (no-) wildcard proof only when it's different from the NSEC
    // that proves NXDOMAIN; sometimes they can be the same.
    // Note: name comparison is relatively expensive.  When we are at the
    // stage of performance optimization, we should consider optimizing this
    // for some optimized data source implementations.
    if (nsec->getName() != fcontext->rrset->getName()) {
        authorities_.push_back(fcontext->rrset);
    }
}

uint8_t
Query::addClosestEncloserProof(ZoneFinder& finder, const Name& name,
                               bool exact_ok, bool add_closest)
{
    const ZoneFinder::FindNSEC3Result result = finder.findNSEC3(name, true);

    // Validity check (see the method description).  Note that a completely
    // broken findNSEC3 implementation could even return NULL RRset in
    // closest_proof.  We don't explicitly check such case; addRRset() will
    // throw an exception, and it will be converted to SERVFAIL at the caller.
    if (!exact_ok && !result.next_proof) {
        isc_throw(BadNSEC3, "Matching NSEC3 found for a non existent name: "
                  << qname_);
    }

    if (add_closest) {
        authorities_.push_back(result.closest_proof);
    }
    if (result.next_proof) {
        authorities_.push_back(result.next_proof);
    }
    return (result.closest_labels);
}

void
Query::addNSEC3ForName(ZoneFinder& finder, const Name& name, bool match) {
    const ZoneFinder::FindNSEC3Result result = finder.findNSEC3(name, false);

    // See the comment for addClosestEncloserProof().  We don't check a
    // totally bogus case where closest_proof is NULL here.
    if (match != result.matched) {
        isc_throw(BadNSEC3, "Unexpected "
                  << (result.matched ? "matching" : "covering")
                  << " NSEC3 found for " << name);
    }
    authorities_.push_back(result.closest_proof);
}

void
Query::addNXDOMAINProofByNSEC3(ZoneFinder& finder) {
    // Firstly get the NSEC3 proves for Closest Encloser Proof
    // See Section 7.2.1 of RFC 5155.
    const uint8_t closest_labels =
        addClosestEncloserProof(finder, qname_, false);

    // Next, construct the wildcard name at the closest encloser, i.e.,
    // '*' followed by the closest encloser, and add NSEC3 for it.
    const Name wildname(Name("*").concatenate(
               qname_.split(qname_.getLabelCount() - closest_labels)));
    addNSEC3ForName(finder, wildname, false);
}

void
Query::addWildcardProof(ZoneFinder& finder,
                        const ZoneFinder::Context& db_context)
{
    if (db_context.isNSECSigned()) {
        // Case for RFC4035 Section 3.1.3.3.
        //
        // The query name shouldn't exist in the zone if there were no wildcard
        // substitution.  Confirm that by specifying NO_WILDCARD.  It should
        // result in NXDOMAIN and an NSEC RR that proves it should be returned.
        ConstZoneFinderContextPtr fcontext =
            finder.find(qname_, RRType::NSEC(),
                        dnssec_opt_ | ZoneFinder::NO_WILDCARD);
        if (fcontext->code != ZoneFinder::NXDOMAIN || !fcontext->rrset ||
            fcontext->rrset->getRdataCount() == 0) {
            isc_throw(BadNSEC,
                      "Unexpected NSEC result for wildcard proof");
        }
        authorities_.push_back(fcontext->rrset);
    } else if (db_context.isNSEC3Signed()) {
        // Case for RFC 5155 Section 7.2.6.
        //
        // Note that the closest encloser must be the immediate ancestor
        // of the matching wildcard, so NSEC3 for its next closer (and only
        // that NSEC3) is what we are expected to provided per the RFC (if
        // this assumption isn't met the zone is broken anyway).
        addClosestEncloserProof(finder, qname_, false, false);
    }
}

void
Query::addWildcardNXRRSETProof(ZoneFinder& finder, ConstRRsetPtr nsec) {
    // There should be one NSEC RR which was found in the zone to prove
    // that there is not matched <QNAME,QTYPE> via wildcard expansion.
    if (nsec->getRdataCount() == 0) {
        isc_throw(BadNSEC, "NSEC for WILDCARD_NXRRSET is empty");
    }
    
    ConstZoneFinderContextPtr fcontext =
        finder.find(qname_, RRType::NSEC(),
                    dnssec_opt_ | ZoneFinder::NO_WILDCARD);
    if (fcontext->code != ZoneFinder::NXDOMAIN || !fcontext->rrset ||
        fcontext->rrset->getRdataCount() == 0) {
        isc_throw(BadNSEC, "Unexpected result for no match QNAME proof");
    }
   
    if (nsec->getName() != fcontext->rrset->getName()) {
        // one NSEC RR proves wildcard_nxrrset that no matched QNAME.
        authorities_.push_back(fcontext->rrset);
    }
}

void
Query::addDS(ZoneFinder& finder, const Name& dname) {
    ConstZoneFinderContextPtr ds_context =
        finder.find(dname, RRType::DS(), dnssec_opt_);
    if (ds_context->code == ZoneFinder::SUCCESS) {
        authorities_.push_back(ds_context->rrset);
    } else if (ds_context->code == ZoneFinder::NXRRSET &&
               ds_context->isNSECSigned()) {
        addNXRRsetProof(finder, *ds_context);
    } else if (ds_context->code == ZoneFinder::NXRRSET &&
               ds_context->isNSEC3Signed()) {
        // Add no DS proof with NSEC3 as specified in RFC 5155 Section 7.2.7.
        addClosestEncloserProof(finder, dname, true);
    } else {
        // Any other case should be an error
        isc_throw(BadDS, "Unexpected result for DS lookup for delegation");
    }
}

void
Query::addNXRRsetProof(ZoneFinder& finder,
                       const ZoneFinder::Context& db_context)
{
    if (db_context.isNSECSigned() && db_context.rrset) {
        authorities_.push_back(db_context.rrset);
        if (db_context.isWildcard()) {
            addWildcardNXRRSETProof(finder, db_context.rrset);
        }
    } else if (db_context.isNSEC3Signed() && !db_context.isWildcard()) {
        if (qtype_ == RRType::DS()) {
            // RFC 5155, Section 7.2.4.  Add either NSEC3 for the qname or
            // closest (provable) encloser proof in case of optout.
            addClosestEncloserProof(finder, qname_, true);
        } else {
            // RFC 5155, Section 7.2.3.  Just add NSEC3 for the qname.
            addNSEC3ForName(finder, qname_, true);
        }
    } else if (db_context.isNSEC3Signed() && db_context.isWildcard()) {
        // Case for RFC 5155 Section 7.2.5: add closest encloser proof for the
        // qname, construct the matched wildcard name and add NSEC3 for it.
        const uint8_t closest_labels =
            addClosestEncloserProof(finder, qname_, false);
        const Name wname = Name("*").concatenate(
            qname_.split(qname_.getLabelCount() - closest_labels));
        addNSEC3ForName(finder, wname, true);
    }
}

void
Query::addAuthAdditional(ZoneFinder& finder,
                         vector<ConstRRsetPtr>& additionals)
{
    const Name& origin = finder.getOrigin();

    // Fill in authority and addtional sections.
    ConstZoneFinderContextPtr ns_context = finder.find(origin, RRType::NS(),
                                                       dnssec_opt_);

    // zone origin name should have NS records
    if (ns_context->code != ZoneFinder::SUCCESS) {
        isc_throw(NoApexNS, "There's no apex NS records in zone " <<
                  finder.getOrigin().toText());
    }
    authorities_.push_back(ns_context->rrset);
    getAdditional(qname_, qtype_, *ns_context, additionals);
}

namespace {
// A simple wrapper for DataSourceClient::findZone().  Normally we can simply
// check the closest zone to the qname, but for type DS query we need to
// look into the parent zone.  Nevertheless, if there is no "parent" (i.e.,
// the qname consists of a single label, which also means it's the root name),
// we should search the deepest zone we have (which should be the root zone;
// otherwise it's a query error).
DataSourceClient::FindResult
findZone(const DataSourceClient& client, const Name& qname, RRType qtype) {
    if (qtype != RRType::DS() || qname.getLabelCount() == 1) {
        return (client.findZone(qname));
    }
    return (client.findZone(qname.split(1)));
}
}

void
Query::process(datasrc::DataSourceClient& datasrc_client,
               const isc::dns::Name qname, const isc::dns::RRType qtype,
               isc::dns::Message& response, bool dnssec)
{
    // First a bit of house cleaning
    // The call to reset() could in theory be ommitted, but
    // seems prudent, just in case a previous process() left
    // data in here.
    reset();

    // Set up query parameters for the rest of the (internal) methods
    initialize(datasrc_client, qname, qtype, response, dnssec);

    // Found a zone which is the nearest ancestor to QNAME
    const DataSourceClient::FindResult result = findZone(*datasrc_client_,
                                                         qname_, qtype_);

    // If we have no matching authoritative zone for the query name, return
    // REFUSED.  In short, this is to be compatible with BIND 9, but the
    // background discussion is not that simple.  See the relevant topic
    // at the BIND 10 developers's ML:
    // https://lists.isc.org/mailman/htdig/bind10-dev/2010-December/001633.html
    if (result.code != result::SUCCESS &&
        result.code != result::PARTIALMATCH) {
        // If we tried to find a "parent zone" for a DS query and failed,
        // we may still have authority at the child side.  If we do, the query
        // has to be handled there.
        if (qtype_ == RRType::DS() && qname_.getLabelCount() > 1 &&
            processDSAtChild()) {
            createResponse();
            return;
        }
        response_->setHeaderFlag(Message::HEADERFLAG_AA, false);
        response_->setRcode(Rcode::REFUSED());
        createResponse();
        return;
    }
    ZoneFinder& zfinder = *result.zone_finder;

    // We have authority for a zone that contain the query name (possibly
    // indirectly via delegation).  Look into the zone.
    response_->setHeaderFlag(Message::HEADERFLAG_AA);
    response_->setRcode(Rcode::NOERROR());
    boost::function0<ZoneFinderContextPtr> find;
    const bool qtype_is_any = (qtype_ == RRType::ANY());
    if (qtype_is_any) {
        find = boost::bind(&ZoneFinder::findAll, &zfinder, qname_,
                           boost::ref(answers_), dnssec_opt_);
    } else {
        find = boost::bind(&ZoneFinder::find, &zfinder, qname_, qtype_,
                           dnssec_opt_);
    }
    ZoneFinderContextPtr db_context(find());
    switch (db_context->code) {
        case ZoneFinder::DNAME: {
            // First, put the dname into the answer
            answers_.push_back(db_context->rrset);
            /*
             * Empty DNAME should never get in, as it is impossible to
             * create one in master file.
             *
             * FIXME: Other way to prevent this should be done
             */
            assert(db_context->rrset->getRdataCount() > 0);
            // Get the data of DNAME
            const rdata::generic::DNAME& dname(
                dynamic_cast<const rdata::generic::DNAME&>(
                db_context->rrset->getRdataIterator()->getCurrent()));
            // The yet unmatched prefix dname
            const Name prefix(qname_.split(0, qname_.getLabelCount() -
                db_context->rrset->getName().getLabelCount()));
            // If we put it together, will it be too long?
            // (The prefix contains trailing ., which will be removed
            if (prefix.getLength() - Name::ROOT_NAME().getLength() +
                dname.getDname().getLength() > Name::MAX_WIRE) {
                /*
                 * In case the synthesized name is too long, section 4.1
                 * of RFC 2672 mandates we return YXDOMAIN.
                 */
                response_->setRcode(Rcode::YXDOMAIN());
                break;
            }
            // The new CNAME we are creating (it will be unsigned even
            // with DNSSEC, the DNAME is signed and it can be validated
            // by that)
            RRsetPtr cname(new RRset(qname_, db_context->rrset->getClass(),
                RRType::CNAME(), db_context->rrset->getTTL()));
            // Construct the new target by replacing the end
            cname->addRdata(rdata::generic::CNAME(qname_.split(0,
                qname_.getLabelCount() -
                db_context->rrset->getName().getLabelCount()).
                concatenate(dname.getDname())));
            answers_.push_back(cname);
            break;
        }
        case ZoneFinder::CNAME:
            /*
             * We don't do chaining yet. Therefore handling a CNAME is
             * mostly the same as handling SUCCESS, but we didn't get
             * what we expected. It means no exceptions in ANY or NS
             * on the origin (though CNAME in origin is probably
             * forbidden anyway).
             *
             * So, just put it there.
             */
            answers_.push_back(db_context->rrset);

            // If the answer is a result of wildcard substitution,
            // add a proof that there's no closer name.
            if (dnssec_ && db_context->isWildcard()) {
                addWildcardProof(*result.zone_finder, *db_context);
            }
            break;
        case ZoneFinder::SUCCESS:
            // If query type is ANY, the rrs have already been added
            if (!qtype_is_any) {
                answers_.push_back(db_context->rrset);
            }

            // Retrieve additional records for the answer
            getAdditional(qname_, qtype_, *db_context, additionals_);

            // If apex NS records haven't been provided in the answer
            // section, insert apex NS records into the authority section
            // and AAAA/A RRS of each of the NS RDATA into the additional
            // section.
            // Checking the findZone() is a lightweight check to see if
            // qname is the zone origin.
            if (result.code != result::SUCCESS ||
                db_context->code != ZoneFinder::SUCCESS ||
                (qtype_ != RRType::NS() && !qtype_is_any))
            {
                addAuthAdditional(*result.zone_finder, additionals_);
            }

            // If the answer is a result of wildcard substitution,
            // add a proof that there's no closer name.
            if (dnssec_ && db_context->isWildcard()) {
                addWildcardProof(*result.zone_finder, *db_context);
            }
            break;
        case ZoneFinder::DELEGATION:
            // If a DS query resulted in delegation, we also need to check
            // if we are an authority of the child, too.  If so, we need to
            // complete the process in the child as specified in Section
            // 2.2.1.2. of RFC3658.
            if (qtype_ == RRType::DS() && processDSAtChild()) {
                break;
            }

            response_->setHeaderFlag(Message::HEADERFLAG_AA, false);
            authorities_.push_back(db_context->rrset);
            // Retrieve additional records for the name servers
            db_context->getAdditional(A_AND_AAAA(), additionals_);

            // If DNSSEC is requested, see whether there is a DS
            // record for this delegation.
            if (dnssec_) {
                addDS(*result.zone_finder, db_context->rrset->getName());
            }
            break;
        case ZoneFinder::NXDOMAIN:
            response_->setRcode(Rcode::NXDOMAIN());
            addSOA(*result.zone_finder);
            if (dnssec_) {
                if (db_context->isNSECSigned() && db_context->rrset) {
                    addNXDOMAINProofByNSEC(zfinder, db_context->rrset);
                } else if (db_context->isNSEC3Signed()) {
                    addNXDOMAINProofByNSEC3(zfinder);
                }
            }
            break;
        case ZoneFinder::NXRRSET:
            addSOA(*result.zone_finder);
            if (dnssec_) {
                addNXRRsetProof(zfinder, *db_context);
            }
            break;
        default:
            // This is basically a bug of the data source implementation,
            // but could also happen in the middle of development where
            // we try to add a new result code.
            isc_throw(isc::NotImplemented, "Unknown result code");
            break;
    }

    createResponse();
}

void
Query::initialize(datasrc::DataSourceClient& datasrc_client,
                  const isc::dns::Name qname, const isc::dns::RRType qtype,
                  isc::dns::Message& response, bool dnssec) {
    datasrc_client_ = &datasrc_client;
    qname_ = qname;
    qtype_ = qtype;
    response_ = &response;
    dnssec_ = dnssec;
    dnssec_opt_ = (dnssec ?  isc::datasrc::ZoneFinder::FIND_DNSSEC :
                   isc::datasrc::ZoneFinder::FIND_DEFAULT);
}

void
Query::createResponse() {
    for_each(answers_.begin(), answers_.end(),
             RRsetInserter(*response_, Message::SECTION_ANSWER, dnssec_));
    answers_.clear();
    for_each(authorities_.begin(), authorities_.end(),
             RRsetInserter(*response_, Message::SECTION_AUTHORITY, dnssec_));
    authorities_.clear();
    for_each(additionals_.begin(), additionals_.end(),
             RRsetInserter(*response_, Message::SECTION_ADDITIONAL, dnssec_));
    additionals_.clear();
}

bool
Query::processDSAtChild() {
    const DataSourceClient::FindResult zresult =
        datasrc_client_->findZone(qname_);

    if (zresult.code != result::SUCCESS) {
        return (false);
    }

    // We are receiving a DS query at the child side of the owner name,
    // where the DS isn't supposed to belong.  We should return a "no data"
    // response as described in Section 3.1.4.1 of RFC4035 and Section
    // 2.2.1.1 of RFC 3658.  find(DS) should result in NXRRSET, in which
    // case (and if DNSSEC is required) we also add the proof for that,
    // but even if find() returns an unexpected result, we don't bother.
    // The important point in this case is to return SOA so that the resolver
    // that happens to contact us can hunt for the appropriate parent zone
    // by seeing the SOA.
    response_->setHeaderFlag(Message::HEADERFLAG_AA);
    response_->setRcode(Rcode::NOERROR());
    addSOA(*zresult.zone_finder);
    ConstZoneFinderContextPtr ds_context =
        zresult.zone_finder->find(qname_, RRType::DS(), dnssec_opt_);
    if (ds_context->code == ZoneFinder::NXRRSET) {
        if (dnssec_) {
            addNXRRsetProof(*zresult.zone_finder, *ds_context);
        }
    }

    return (true);
}

}
}
