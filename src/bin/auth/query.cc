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
using namespace std;

namespace isc {
namespace auth {

void
Query::process() const {
    bool keep_doing = true;
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
        Zone::FindResult db_result = result.zone->find(qname_, qtype_);
        switch (db_result.code) {
            case Zone::SUCCESS:
                response_.setRcode(Rcode::NOERROR());
                response_.addRRset(Message::SECTION_ANSWER,
                            boost::const_pointer_cast<RRset>(db_result.rrset));
                // Some additional processing
                if (qtype_ == RRType::MX()) {
                    // We look up these RR types
                    vector<RRType> interesting_types;
                    interesting_types.push_back(RRType::A());
                    interesting_types.push_back(RRType::AAAA());
                    // Go trough all the RRs in the RRset
                    for (RdataIteratorPtr i(
                        db_result.rrset->getRdataIterator()); !i->isLast();
                        i->next())
                    {
                        // Who does it talk about?
                        Name name(
                            dynamic_cast<const isc::dns::rdata::generic::MX &>(
                            i->getCurrent()).getMXName());
                        // Look up both addresses
                        BOOST_FOREACH(const RRType& type, interesting_types) {
                            // Recursively call query
                            Message response(Message::RENDER);
                            Query sub(memory_datasrc_, name, type, response);
                            sub.process();
                            // And run trough all the answers and look if some
                            // of them match
                            for (SectionIterator<RRsetPtr> ai(
                                response.beginSection(
                                Message::SECTION_ANSWER)); ai !=
                                response.endSection(Message::SECTION_ANSWER);
                                ++ ai)
                            {
                                if ((*ai)->getType() == type &&
                                    (*ai)->getName() == name)
                                {
                                    response_.addRRset(
                                        Message::SECTION_ADDITIONAL, *ai);
                                }
                            }
                        }
                    }
                }
                // TODO : fill in authority and addtional sections.
                break;
            case Zone::DELEGATION:
                // TODO : add NS to authority section, fill in additional section.
                break;
            case Zone::NXDOMAIN:
                response_.setRcode(Rcode::NXDOMAIN());
                // TODO : add SOA to authority section
                break;
            case Zone::NXRRSET:
                response_.setRcode(Rcode::NOERROR());
                // TODO : add SOA to authority section
                break;
            case Zone::CNAME:
            case Zone::DNAME:
                // TODO : replace qname, continue lookup
                break;
        }
    }
}
}
}
