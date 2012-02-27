// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "glue_hints.h"

#include <stdlib.h>

#include <dns/rrset.h>
#include <dns/rdata.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

#include <asiolink/io_address.h>
#include <nsas/nameserver_entry.h>

using namespace isc::dns;
using namespace isc::nsas;

// This is a simple implementation for finding glue
//
// It iterates over the AUTHORITY section of the given Message,
// and for each NS RR it iterates over the ADDITIONAL section to
// see if there are A or AAAA records.
//
// Of course, this could be done more efficiently. One option is to
// reverse this; check for A and AAAA records (since those will only
// be there if there actually is glue, while NS records will be present
// in any delegation). However, it may be even better to let the
// Response Classifier decide on glue, while it is validating the packet
//
// (er, TODO, so to speak. discuss.)

// Helper functions
namespace {
    // Add the contents of the given A or AAAA rrset to the given
    // addressvector
    //
    // This creates an 'dummy' NameserverEntry value, because that
    // is enforced by NameserverAddress. We may want to reconsider
    // the need for that (perhaps we can change it so that if it is
    // NULL, all NSAS-related calls to the NameserverAddress object
    // become nops)
    void
    addRRset(std::vector<NameserverAddress>& addresses,
             const RRsetPtr rrset)
    {
        const std::string ns_name = rrset->getName().toText();
        RdataIteratorPtr rdi = rrset->getRdataIterator();
        while (!rdi->isLast()) {
            AddressEntry entry(isc::asiolink::IOAddress(rdi->getCurrent().toText()));
            boost::shared_ptr<NameserverEntry> ns_entry(new NameserverEntry(ns_name, rrset->getClass()));
            NameserverAddress ns_address(ns_entry, entry, V4_ONLY);
            addresses.push_back(ns_address);
            rdi->next();
        }
    }
}

namespace isc {
namespace nsas {

GlueHints::GlueHints(const std::string& zone_name,
                     const isc::dns::Message& delegation_message)
{
    for (RRsetIterator rssi = delegation_message.beginSection(Message::SECTION_AUTHORITY);
         rssi != delegation_message.endSection(Message::SECTION_AUTHORITY);
         ++rssi) {
        if ((*rssi)->getType() == RRType::NS() &&
            (*rssi)->getName().toText() == zone_name) {
            addGlueForRRset(*rssi, delegation_message);
        }
    }
}


bool
GlueHints::hasGlue(AddressFamily family) const {
    return ((!addresses_v4.empty() && (family == ANY_OK || family == V4_ONLY)) ||
            (!addresses_v6.empty() && (family == ANY_OK || family == V6_ONLY)));
}

NameserverAddress
GlueHints::getGlue(AddressFamily family) const {
    // TODO: once we have a more general random lib, use that. Since
    // this is simply glue, and we don't need a weighted selection,
    // for now srandom should be good enough. Once #583 has been merged,
    // (or better yet, once that one and the weighted random have gone
    // together in a util lib), we can use that.
    int max = 0;
    size_t v4s = addresses_v4.size();
    size_t v6s = addresses_v6.size();

    if (family == ANY_OK || family == V4_ONLY) {
        max += v4s;
    }
    if (family == ANY_OK || family == V6_ONLY) {
        max += v6s;
    }

    assert(max > 0);
    long int selection = random() % max;

    if (family == ANY_OK) {
        if (selection < v4s) {
            return addresses_v4[selection];
        } else {
            return addresses_v6[selection-v4s];
        }
    } else if (family == V4_ONLY) {
        return addresses_v4[selection];
    } else if (family == V6_ONLY) {
        return addresses_v6[selection];
    } else {
        // Unknown family
        assert(false);
        // Some compilers want something returned anyway
        return NameserverAddress();
    }
}

// Add the A and AAAA records from the given message for the given
// NS name to the relevant address vector
// (A rrsets are added to addresses_v4, AAAA rrsets are added to
// addresses_v6).
void
GlueHints::addGlueForName(const Name& name, const Message& message)
{
    for (RRsetIterator rssi = message.beginSection(Message::SECTION_ADDITIONAL);
         rssi != message.endSection(Message::SECTION_ADDITIONAL);
         ++rssi) {
        if ((*rssi)->getName() == name) {
            if ((*rssi)->getType() == RRType::A()) {
                addRRset(addresses_v4, *rssi);
            } else if ((*rssi)->getType() == RRType::AAAA()) {
                addRRset(addresses_v6, *rssi);
            }
        }
    }
}

// Add the glue for the given NS RRset in the message to the
// relevant vectors.
void
GlueHints::addGlueForRRset(const RRsetPtr rrset, const Message& message)
{
    RdataIteratorPtr rdi = rrset->getRdataIterator();
    while (!rdi->isLast()) {
        isc::dns::Name name(dynamic_cast<const rdata::generic::NS&>(
                        rdi->getCurrent()).getNSName());
        addGlueForName(name, message);
        rdi->next();
    }
}


} // namespace nsas
} // namespace isc
