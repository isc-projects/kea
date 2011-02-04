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

#include <vector>
#include <boost/foreach.hpp>

#include <dns/message.h>
#include <dns/rcode.h>
#include <dns/rdataclass.h>

#include <datasrc/memory_datasrc.h>

#include <auth/query.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::dns::rdata;

namespace isc {
namespace auth {

void
Query::getAdditional(const Zone& zone, const RRset& rrset) const {
    RdataIteratorPtr rdata_iterator(rrset.getRdataIterator());
    for (; !rdata_iterator->isLast(); rdata_iterator->next()) {
        const Rdata& rdata(rdata_iterator->getCurrent());
        if (rrset.getType() == RRType::NS()) {
            // Need to perform the search in the "GLUE OK" mode.
            const generic::NS& ns = dynamic_cast<const generic::NS&>(rdata);
            findAddrs(zone, ns.getNSName(), Zone::FIND_GLUE_OK);
        } else if (rrset.getType() == RRType::MX()) {
            const generic::MX& mx(dynamic_cast<const generic::MX&>(rdata));
            findAddrs(zone, mx.getMXName());
        }
    }
}

void
Query::findAddrs(const Zone& zone, const Name& qname,
                 const Zone::FindOptions options) const
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
        Zone::FindResult a_result = zone.find(qname, RRType::A(), NULL,
                                              options);
        if (a_result.code == Zone::SUCCESS) {
            response_.addRRset(Message::SECTION_ADDITIONAL,
                    boost::const_pointer_cast<RRset>(a_result.rrset));
        }
    }

    // Find AAAA rrset
    if (qname_ != qname || qtype_ != RRType::AAAA()) {
        Zone::FindResult aaaa_result =
            zone.find(qname, RRType::AAAA(), NULL, options);
        if (aaaa_result.code == Zone::SUCCESS) {
            response_.addRRset(Message::SECTION_ADDITIONAL,
                    boost::const_pointer_cast<RRset>(aaaa_result.rrset));
        }
    }
}

void
Query::putSOA(const Zone& zone) const {
    Zone::FindResult soa_result(zone.find(zone.getOrigin(),
        RRType::SOA()));
    if (soa_result.code != Zone::SUCCESS) {
        isc_throw(NoSOA, "There's no SOA record in zone " <<
            zone.getOrigin().toText());
    } else {
        /*
         * FIXME:
         * The const-cast is wrong, but the Message interface seems
         * to insist.
         */
        response_.addRRset(Message::SECTION_AUTHORITY,
            boost::const_pointer_cast<RRset>(soa_result.rrset));
    }
}

void
Query::getAuthAdditional(const Zone& zone) const {
    // Fill in authority and addtional sections.
    Zone::FindResult ns_result = zone.find(zone.getOrigin(), RRType::NS());
    // zone origin name should have NS records
    if (ns_result.code != Zone::SUCCESS) {
        isc_throw(NoApexNS, "There's no apex NS records in zone " <<
                zone.getOrigin().toText());
    } else {
        response_.addRRset(Message::SECTION_AUTHORITY,
            boost::const_pointer_cast<RRset>(ns_result.rrset));
        // Handle additional for authority section
        getAdditional(zone, *ns_result.rrset);
    }
}

void
Query::process() const {
    bool keep_doing = true;
    bool qtype_is_any = (qtype_ == RRType::ANY());

    response_.setHeaderFlag(Message::HEADERFLAG_AA, false);
    const MemoryDataSrc::FindResult result =
        memory_datasrc_.findZone(qname_);

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

    // Found a zone which is the nearest ancestor to QNAME, set the AA bit
    response_.setHeaderFlag(Message::HEADERFLAG_AA);
    while (keep_doing) {
        keep_doing = false;
        std::auto_ptr<RRsetList> target(qtype_is_any ? new RRsetList : NULL);
        /*
         * We use the rrset, not db_result.rrset because we might replace
         * it while synthetizing the CNAME out of DNAME. The db_result is
         * imutable, so we have a different variable.
         */
        Zone::FindResult db_result(result.zone->find(qname_, qtype_,
            target.get()));
        ConstRRsetPtr rrset(db_result.rrset);

        switch (db_result.code) {
            case Zone::DNAME: {
                // First, put the dname into the answer
                response_.addRRset(Message::SECTION_ANSWER,
                    boost::const_pointer_cast<RRset>(rrset));
                /*
                 * We synthetize CNAME out of it, replace the rrset and let
                 * the CNAME case handle it (including future chaining).
                 * Therefore, we just fall trough to it.
                 */
                /*
                 * Empty DNAME should never get in, as it is impossible to
                 * create one in master file.
                 */
                assert(rrset->getRdataCount() > 0);
                // Get the data of DNAME
                const rdata::generic::DNAME& dname(
                    dynamic_cast<const rdata::generic::DNAME&>(
                    rrset->getRdataIterator()->getCurrent()));
                // The new CNAME we are creating (it will be unsigned even
                // with DNSSEC, the DNAME is signed and it can be validated
                // by that)
                RRsetPtr cname(new RRset(qname_, rrset->getClass(),
                    RRType::CNAME(), rrset->getTTL()));
                try {
                    // Construct the new target by replacing the end
                    cname->addRdata(rdata::generic::CNAME(qname_.split(0,
                        qname_.getLabelCount() -
                        rrset->getName().getLabelCount()).concatenate(
                        dname.getDname())));
                    rrset = cname;
                    // If this was ANY, act as it wasn't, because we put the
                    // CNAME into rrset, not to target and there's nothing else.
                    // TODO: This might need to be changed when CNAME gets
                    // chaining.
                    qtype_is_any = false;
                }
                /*
                 * In case the synthetized name is too long, section 4.1 of RFC 2672
                 * mandates we return YXDOMAIN.
                 */
                catch (const isc::dns::TooLongName&) {
                    response_.setRcode(Rcode::YXDOMAIN());
                    return;
                }
                // No break; here, fall trough.
            }
            case Zone::CNAME:
                /*
                 * We don't do chaining yet. Therefore handling a CNAME is
                 * mostly the same as handling SUCCESS, but we didn't get
                 * what we expected. It means no exceptions in ANY or NS
                 * on the origin (though CNAME in origin is probably
                 * forbidden anyway).
                 */
                // No break; here, fall trough.
            case Zone::SUCCESS:
                response_.setRcode(Rcode::NOERROR());
                if (qtype_is_any) {
                    // If quety type is ANY, insert all RRs under the domain
                    // into answer section.
                    BOOST_FOREACH(RRsetPtr rrset, *target) {
                        response_.addRRset(Message::SECTION_ANSWER, rrset);
                    }
                } else {
                    response_.addRRset(Message::SECTION_ANSWER,
                        boost::const_pointer_cast<RRset>(rrset));
                    // Handle additional for answer section
                    getAdditional(*result.zone, *rrset);
                }
                // If apex NS records haven't been provided in the answer
                // section, insert apex NS records into the authority section
                // and AAAA/A RRS of each of the NS RDATA into the additional
                // section.
                if (qname_ != result.zone->getOrigin() ||
                    db_result.code != Zone::SUCCESS ||
                    (qtype_ != RRType::NS() && !qtype_is_any))
                {
                    getAuthAdditional(*result.zone);
                }
                break;
            case Zone::DELEGATION:
                response_.setHeaderFlag(Message::HEADERFLAG_AA, false);
                response_.setRcode(Rcode::NOERROR());
                response_.addRRset(Message::SECTION_AUTHORITY,
                    boost::const_pointer_cast<RRset>(rrset));
                getAdditional(*result.zone, *rrset);
                break;
            case Zone::NXDOMAIN:
                // Just empty answer with SOA in authority section
                response_.setRcode(Rcode::NXDOMAIN());
                putSOA(*result.zone);
                break;
            case Zone::NXRRSET:
                // Just empty answer with SOA in authority section
                response_.setRcode(Rcode::NOERROR());
                putSOA(*result.zone);
                break;
        }
    }
}

}
}
