
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

#include <dns/message.h>
#include <dns/rrset.h>
#include "response_scrubber.h"

using namespace isc::dns;
using namespace asio::ip;

// Compare addresses etc.

ResponseScrubber::Category ResponseScrubber::addressPortCheck(
    const udp::endpoint& to, const udp::endpoint& from)
{
    if (from.address() == to.address()) {
        if (from.port() == to.port()) {
            return (ResponseScrubber::SUCCESS);
        }
        else {
            return (ResponseScrubber::PORT);
        }
    }
    return (ResponseScrubber::ADDRESS);
}

// Scrub a section of the message

unsigned int
ResponseScrubber::scrubSection(const Name& bailiwick, Message& message,
    const Message::Section section)
{
    unsigned int count = 0;
    bool removed = true;

    // Need to iterate multiple times as removing an RRset from the section
    // invalidates the iterators.
    while (removed) {
        removed = false;
        for (RRsetIterator i = message.beginSection(section);
            i != message.endSection(section); ++i) {
            NameComparisonResult result = (*i)->getName().compare(bailiwick);
            NameComparisonResult::NameRelation relation =
                    result.getRelation();
            if ((relation != NameComparisonResult::EQUAL) &&
                (relation != NameComparisonResult::SUBDOMAIN)) {
                    
                // Name is a superdomain of the bailiwick name or has a
                // common ancestor somewhere in the chain.  Either way it's
                // not in bailiwick and we should remove this name from the
                // message section.
                message.removeRRset(section, i);
                ++count;            // One more RRset removed
                removed = true;     // Something was removed
                    
                // Must now work through the section again because the
                // removal of the RRset has invalidated the iterators.
                break;
            }
        }


    }
    return count;
}

// Perform the scrubbing of the message.

unsigned int
ResponseScrubber::scrub(const Name& bailiwick, Message& message) {

    // Leave the question section alone.  Just go through the RRsets in the
    // answer, authority and additional sectiuons.
    unsigned int count = 0;

    count += scrubSection(bailiwick, message, Message::SECTION_ANSWER);
    count += scrubSection(bailiwick, message, Message::SECTION_AUTHORITY);
    count += scrubSection(bailiwick, message, Message::SECTION_ADDITIONAL);

    return count;
}

