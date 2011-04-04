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

// $Id$

#include "message_utility.h"
#include <dns/rcode.h>

using namespace isc::dns;

namespace isc {
namespace cache {
namespace MessageUtility{

bool
hasTheRecordInAuthoritySection(const isc::dns::Message& msg,
                               const isc::dns::RRType& type)
{
    // isc::dns::Message provide one function hasRRset() should be used to
    // determine whether the given section has an RRset matching the given
    // name and type, but currently it is not const-qualified and cannot be
    // used here
    // TODO: use hasRRset() function when it is const qualified
    for (RRsetIterator iter = msg.beginSection(Message::SECTION_AUTHORITY);
            iter != msg.endSection(Message::SECTION_AUTHORITY);
            ++iter) {
        RRsetPtr rrset_ptr = *iter;
        if (rrset_ptr->getType() == type) {
            return (true);
        }
    }
    return (false);
}

bool
isNegativeResponse(const isc::dns::Message& msg) {
    if (msg.getRcode() == Rcode::NXDOMAIN()) {
        return (true);
    } else if (msg.getRcode() == Rcode::NOERROR()) {
        // no data in the answer section
        if (msg.getRRCount(Message::SECTION_ANSWER) == 0) {
            // NODATA type 1/ type 2 (ref sec2.2 of RFC2308)
            if (hasTheRecordInAuthoritySection(msg, RRType::SOA())) {
                return (true);
            } else if (!hasTheRecordInAuthoritySection(msg, RRType::NS())) {
                // NODATA type 3 (sec2.2 of RFC2308)
                return (true);
            }
        }
    }

    return (false);
}

bool
canMessageBeCached(const isc::dns::Message& msg) {
    // If the message is a negative response, but no SOA record is found in
    // the authority section, the message cannot be cached
    if (isNegativeResponse(msg) &&
        !hasTheRecordInAuthoritySection(msg, RRType::SOA())){
        return (false);
    }

    return (true);
}

} // namespace MessageUtility
} // namespace cache
} // namespace isc
