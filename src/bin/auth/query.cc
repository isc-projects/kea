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

#include <algorithm>            // for std::max
#include <vector>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <dns/message.h>
#include <dns/rcode.h>
#include <dns/rdataclass.h>

#include <datasrc/client.h>

#include <auth/query.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::dns::rdata;

namespace isc {
namespace auth {

void
Query::addAdditional(ZoneFinder& zone, const AbstractRRset& rrset) {
    RdataIteratorPtr rdata_iterator(rrset.getRdataIterator());
    for (; !rdata_iterator->isLast(); rdata_iterator->next()) {
        const Rdata& rdata(rdata_iterator->getCurrent());
        if (rrset.getType() == RRType::NS()) {
            // Need to perform the search in the "GLUE OK" mode.
            const generic::NS& ns = dynamic_cast<const generic::NS&>(rdata);
            addAdditionalAddrs(zone, ns.getNSName(), ZoneFinder::FIND_GLUE_OK);
        } else if (rrset.getType() == RRType::MX()) {
            const generic::MX& mx(dynamic_cast<const generic::MX&>(rdata));
            addAdditionalAddrs(zone, mx.getMXName());
        }
    }
}

void
Query::addAdditionalAddrs(ZoneFinder& zone, const Name& qname,
                          const ZoneFinder::FindOptions options)
{
    // Out of zone name
    NameComparisonResult result = zone.getOrigin().compare(qname);
    if ((result.getRelation() != NameComparisonResult::SUPERDOMAIN) &&
        (result.getRelation() != NameComparisonResult::EQUAL))
        return;

    // Omit additional data which has already been provided in the answer
    // section from the additional.
    //
    // All the address rrset with the owner name of qname have been inserted
    // into ANSWER section.
    if (qname_ == qname && qtype_ == RRType::ANY())
        return;

    // Find A rrset
    if (qname_ != qname || qtype_ != RRType::A()) {
        ZoneFinder::FindResult a_result = zone.find(qname, RRType::A(),
                                                    options | dnssec_opt_);
        if (a_result.code == ZoneFinder::SUCCESS) {
            response_.addRRset(Message::SECTION_ADDITIONAL,
                    boost::const_pointer_cast<AbstractRRset>(a_result.rrset), dnssec_);
        }
    }

    // Find AAAA rrset
    if (qname_ != qname || qtype_ != RRType::AAAA()) {
        ZoneFinder::FindResult aaaa_result = zone.find(qname, RRType::AAAA(),
                                                       options | dnssec_opt_);
        if (aaaa_result.code == ZoneFinder::SUCCESS) {
            response_.addRRset(Message::SECTION_ADDITIONAL,
                    boost::const_pointer_cast<AbstractRRset>(aaaa_result.rrset),
                    dnssec_);
        }
    }
}

void
Query::addSOA(ZoneFinder& finder) {
    ZoneFinder::FindResult soa_result = finder.find(finder.getOrigin(),
                                                    RRType::SOA(),
                                                    dnssec_opt_);
    if (soa_result.code != ZoneFinder::SUCCESS) {
        isc_throw(NoSOA, "There's no SOA record in zone " <<
            finder.getOrigin().toText());
    } else {
        /*
         * FIXME:
         * The const-cast is wrong, but the Message interface seems
         * to insist.
         */
        response_.addRRset(Message::SECTION_AUTHORITY,
            boost::const_pointer_cast<AbstractRRset>(soa_result.rrset), dnssec_);
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
Query::addNXDOMAINProof(ZoneFinder& finder, ConstRRsetPtr nsec) {
    if (nsec->getRdataCount() == 0) {
        isc_throw(BadNSEC, "NSEC for NXDOMAIN is empty");
    }

    // Add the NSEC proving NXDOMAIN to the authority section.
    response_.addRRset(Message::SECTION_AUTHORITY,
                       boost::const_pointer_cast<AbstractRRset>(nsec), dnssec_);

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
    const ZoneFinder::FindResult fresult =
        finder.find(wildname, RRType::NSEC(), dnssec_opt_);
    if (fresult.code != ZoneFinder::NXDOMAIN || !fresult.rrset ||
        fresult.rrset->getRdataCount() == 0) {
        isc_throw(BadNSEC, "Unexpected result for wildcard NXDOMAIN proof");
    }

    // Add the (no-) wildcard proof only when it's different from the NSEC
    // that proves NXDOMAIN; sometimes they can be the same.
    // Note: name comparison is relatively expensive.  When we are at the
    // stage of performance optimization, we should consider optimizing this
    // for some optimized data source implementations.
    if (nsec->getName() != fresult.rrset->getName()) {
        response_.addRRset(Message::SECTION_AUTHORITY,
                           boost::const_pointer_cast<AbstractRRset>(fresult.rrset),
                           dnssec_);
    }
}

// Note: unless the data source client implementation or the zone content
// is broken, 'nsec3' should be a valid NSEC3 RR.  Likewise, the call to
// findNSEC3() in this method should result an FindNSEC3Result that proves
// the Closest Encloser Proof and non existent of matching wildcard.
// Firstly, the call to findNSEC3() set the recursive to true in order to
// get the an NSEC3 RR that matches the closest (provable) encloser and
// an NSEC3 RR that covers the "next closer" name to the closest encloser.
// This corresponds to Section 7.2.1 of RFC 5155.
// Then,construct the wildcard domain, call to findNSEC3() set the recursive
// to false to get the prove that the wildcard that could have matched QNAME
// also does not exist.
void
Query::addNSEC3NXDOMAINProof(ZoneFinder& finder) {
    // Firstly get the NSEC3 proves for Closest Encloser Proof
    // See section 7.2.1 of RFC 5155.
    const ZoneFinder::FindNSEC3Result fresult1 = finder.findNSEC3(qname_,
                                                                  true);
    if (!fresult1.closest_proof) {
        isc_throw(BadNSEC3,  "NSEC3 RR for NXDOMAIN proving that matches the "
                  "closest encloser is empty.");
    }
    // Add the NSEC3 proving that matches the closest (provable) encloser.
    response_.addRRset(Message::SECTION_AUTHORITY,
                       boost::const_pointer_cast<AbstractRRset>(
                       fresult1.closest_proof),
                       dnssec_);
    if (!fresult1.next_proof) {
        isc_throw(BadNSEC3,  "NSEC3 RR for NXDOMAIN proving that covers the "
                  "next closer to the closest encloser is empty.");
    }
    // Add the NSEC3 RR that covers the "next closer" name to the closest
    // encloser.
    response_.addRRset(Message::SECTION_AUTHORITY,
                       boost::const_pointer_cast<AbstractRRset>(
                       fresult1.next_proof),
                       dnssec_);
    // Next, identify the best possible wildcard name that would match
    // the query name.  It's the longer common suffix with the qname
    // between the owner and the 'matched' domain of the NSEC3 that
    // proves NXDOMAIN,prefixed by the wildcard label, "*".
    const Name wildname(Name("*").concatenate(
               qname_.split(qname_.getLabelCount() - fresult1.closest_labels)));
    const ZoneFinder::FindNSEC3Result fresult2 =
        finder.findNSEC3(wildname, false);
    if (!fresult2.closest_proof) {
            isc_throw(BadNSEC3, "NSEC3 for NXDOMAIN covering the wildcard "
                      "RR at the closest encloser is empty.");
    }
    // Add the wildcard proof only when it's different from the NSEC3 RR
    // that covers the "next closer" name to the closest encloser.
    if (fresult1.next_proof->getName() != fresult2.closest_proof->getName()) {
        response_.addRRset(Message::SECTION_AUTHORITY,
                           boost::const_pointer_cast<AbstractRRset>(
                               fresult2.closest_proof),
                           dnssec_);
    }
}

void
Query::addWildcardProof(ZoneFinder& finder) {
    // The query name shouldn't exist in the zone if there were no wildcard
    // substitution.  Confirm that by specifying NO_WILDCARD.  It should result
    // in NXDOMAIN and an NSEC RR that proves it should be returned.
    const ZoneFinder::FindResult fresult =
        finder.find(qname_, RRType::NSEC(),
                    dnssec_opt_ | ZoneFinder::NO_WILDCARD);
    if (fresult.code != ZoneFinder::NXDOMAIN || !fresult.rrset ||
        fresult.rrset->getRdataCount() == 0) {
        isc_throw(BadNSEC, "Unexpected result for wildcard proof");
    }
    response_.addRRset(Message::SECTION_AUTHORITY,
                       boost::const_pointer_cast<AbstractRRset>(fresult.rrset),
                       dnssec_);
}

void
Query::addWildcardNXRRSETProof(ZoneFinder& finder, ConstRRsetPtr nsec) {
    // There should be one NSEC RR which was found in the zone to prove
    // that there is not matched <QNAME,QTYPE> via wildcard expansion.
    if (nsec->getRdataCount() == 0) {
        isc_throw(BadNSEC, "NSEC for WILDCARD_NXRRSET is empty");
    }
    
    const ZoneFinder::FindResult fresult =
        finder.find(qname_, RRType::NSEC(),
                    dnssec_opt_ | ZoneFinder::NO_WILDCARD);
    if (fresult.code != ZoneFinder::NXDOMAIN || !fresult.rrset ||
        fresult.rrset->getRdataCount() == 0) {
        isc_throw(BadNSEC, "Unexpected result for no match QNAME proof");
    }
   
    if (nsec->getName() != fresult.rrset->getName()) {
        // one NSEC RR proves wildcard_nxrrset that no matched QNAME.
        response_.addRRset(Message::SECTION_AUTHORITY,
                           boost::const_pointer_cast<AbstractRRset>(fresult.rrset),
                           dnssec_);
    }
}

void
Query::addDS(ZoneFinder& finder, const Name& dname) {
    ZoneFinder::FindResult ds_result =
        finder.find(dname, RRType::DS(), dnssec_opt_);
    if (ds_result.code == ZoneFinder::SUCCESS) {
        response_.addRRset(Message::SECTION_AUTHORITY,
                           boost::const_pointer_cast<AbstractRRset>(ds_result.rrset),
                           dnssec_);
    } else if (ds_result.code == ZoneFinder::NXRRSET) {
        addNXRRsetProof(finder, ds_result);
    } else {
        // Any other case should be an error
        isc_throw(BadDS, "Unexpected result for DS lookup for delegation");
    }
}

void
Query::addNXRRsetProof(ZoneFinder& finder,
                       const ZoneFinder::FindResult& db_result)
{
    if (db_result.isNSECSigned() && db_result.rrset) {
        response_.addRRset(Message::SECTION_AUTHORITY,
                           boost::const_pointer_cast<AbstractRRset>(
                               db_result.rrset),
                           dnssec_);
        if (db_result.isWildcard()) {
            addWildcardNXRRSETProof(finder, db_result.rrset);
        }
    }
}

void
Query::addAuthAdditional(ZoneFinder& finder) {
    // Fill in authority and addtional sections.
    ZoneFinder::FindResult ns_result =
        finder.find(finder.getOrigin(), RRType::NS(), dnssec_opt_);

    // zone origin name should have NS records
    if (ns_result.code != ZoneFinder::SUCCESS) {
        isc_throw(NoApexNS, "There's no apex NS records in zone " <<
                finder.getOrigin().toText());
    } else {
        response_.addRRset(Message::SECTION_AUTHORITY,
            boost::const_pointer_cast<AbstractRRset>(ns_result.rrset), dnssec_);
        // Handle additional for authority section
        addAdditional(finder, *ns_result.rrset);
    }
}

void
Query::process() {
    const bool qtype_is_any = (qtype_ == RRType::ANY());

    response_.setHeaderFlag(Message::HEADERFLAG_AA, false);
    const DataSourceClient::FindResult result =
        datasrc_client_.findZone(qname_);

    // If we have no matching authoritative zone for the query name, return
    // REFUSED.  In short, this is to be compatible with BIND 9, but the
    // background discussion is not that simple.  See the relevant topic
    // at the BIND 10 developers's ML:
    // https://lists.isc.org/mailman/htdig/bind10-dev/2010-December/001633.html
    if (result.code != result::SUCCESS &&
        result.code != result::PARTIALMATCH) {
        response_.setRcode(Rcode::REFUSED());
        return;
    }
    ZoneFinder& zfinder = *result.zone_finder;

    // Found a zone which is the nearest ancestor to QNAME, set the AA bit
    response_.setHeaderFlag(Message::HEADERFLAG_AA);
    response_.setRcode(Rcode::NOERROR());
    std::vector<ConstRRsetPtr> target;
    boost::function0<ZoneFinder::FindResult> find;
    if (qtype_is_any) {
        find = boost::bind(&ZoneFinder::findAll, &zfinder, qname_,
                           boost::ref(target), dnssec_opt_);
    } else {
        find = boost::bind(&ZoneFinder::find, &zfinder, qname_, qtype_,
                           dnssec_opt_);
    }
    ZoneFinder::FindResult db_result(find());
    switch (db_result.code) {
        case ZoneFinder::DNAME: {
            // First, put the dname into the answer
            response_.addRRset(Message::SECTION_ANSWER,
                boost::const_pointer_cast<AbstractRRset>(db_result.rrset),
                dnssec_);
            /*
             * Empty DNAME should never get in, as it is impossible to
             * create one in master file.
             *
             * FIXME: Other way to prevent this should be done
             */
            assert(db_result.rrset->getRdataCount() > 0);
            // Get the data of DNAME
            const rdata::generic::DNAME& dname(
                dynamic_cast<const rdata::generic::DNAME&>(
                db_result.rrset->getRdataIterator()->getCurrent()));
            // The yet unmatched prefix dname
            const Name prefix(qname_.split(0, qname_.getLabelCount() -
                db_result.rrset->getName().getLabelCount()));
            // If we put it together, will it be too long?
            // (The prefix contains trailing ., which will be removed
            if (prefix.getLength() - Name::ROOT_NAME().getLength() +
                dname.getDname().getLength() > Name::MAX_WIRE) {
                /*
                 * In case the synthesized name is too long, section 4.1
                 * of RFC 2672 mandates we return YXDOMAIN.
                 */
                response_.setRcode(Rcode::YXDOMAIN());
                return;
            }
            // The new CNAME we are creating (it will be unsigned even
            // with DNSSEC, the DNAME is signed and it can be validated
            // by that)
            RRsetPtr cname(new RRset(qname_, db_result.rrset->getClass(),
                RRType::CNAME(), db_result.rrset->getTTL()));
            // Construct the new target by replacing the end
            cname->addRdata(rdata::generic::CNAME(qname_.split(0,
                qname_.getLabelCount() -
                db_result.rrset->getName().getLabelCount()).
                concatenate(dname.getDname())));
            response_.addRRset(Message::SECTION_ANSWER, cname, dnssec_);
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
            response_.addRRset(Message::SECTION_ANSWER,
                boost::const_pointer_cast<AbstractRRset>(db_result.rrset),
                dnssec_);

            // If the answer is a result of wildcard substitution,
            // add a proof that there's no closer name.
            if (dnssec_ && db_result.isWildcard()) {
                addWildcardProof(*result.zone_finder);
            }
            break;
        case ZoneFinder::SUCCESS:
            if (qtype_is_any) {
                // If quety type is ANY, insert all RRs under the domain
                // into answer section.
                BOOST_FOREACH(ConstRRsetPtr rrset, target) {
                    response_.addRRset(Message::SECTION_ANSWER,
                        boost::const_pointer_cast<AbstractRRset>(rrset), dnssec_);
                    // Handle additional for answer section
                    addAdditional(*result.zone_finder, *rrset.get());
                }
            } else {
                response_.addRRset(Message::SECTION_ANSWER,
                    boost::const_pointer_cast<AbstractRRset>(db_result.rrset),
                    dnssec_);
                // Handle additional for answer section
                addAdditional(*result.zone_finder, *db_result.rrset);
            }
            // If apex NS records haven't been provided in the answer
            // section, insert apex NS records into the authority section
            // and AAAA/A RRS of each of the NS RDATA into the additional
            // section.
            if (qname_ != result.zone_finder->getOrigin() ||
                db_result.code != ZoneFinder::SUCCESS ||
                (qtype_ != RRType::NS() && !qtype_is_any))
            {
                addAuthAdditional(*result.zone_finder);
            }

            // If the answer is a result of wildcard substitution,
            // add a proof that there's no closer name.
            if (dnssec_ && db_result.isWildcard()) {
                addWildcardProof(*result.zone_finder);
            }
            break;
        case ZoneFinder::DELEGATION:
            response_.setHeaderFlag(Message::HEADERFLAG_AA, false);
            response_.addRRset(Message::SECTION_AUTHORITY,
                boost::const_pointer_cast<AbstractRRset>(db_result.rrset),
                dnssec_);
            // If DNSSEC is requested, see whether there is a DS
            // record for this delegation.
            if (dnssec_) {
                addDS(*result.zone_finder, db_result.rrset->getName());
            }
            addAdditional(*result.zone_finder, *db_result.rrset);
            break;
        case ZoneFinder::NXDOMAIN:
            response_.setRcode(Rcode::NXDOMAIN());
            addSOA(*result.zone_finder);
            if (dnssec_ && db_result.isNSEC3Signed()) {
                addNSEC3NXDOMAINProof(zfinder);
                break;
            }
            if (dnssec_ && db_result.rrset) {
                addNXDOMAINProof(zfinder, db_result.rrset);
            }
            break;
        case ZoneFinder::NXRRSET:
            addSOA(*result.zone_finder);
            if (dnssec_) {
                addNXRRsetProof(zfinder, db_result);
            }
            break;
        default:
            // This is basically a bug of the data source implementation,
            // but could also happen in the middle of development where
            // we try to add a new result code.
            isc_throw(isc::NotImplemented, "Unknown result code");
            break;
    }
}

}
}
