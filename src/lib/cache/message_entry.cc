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

// $Id$

#include <dns/message.h>
#include <nsas/nsas_entry.h>
#include <nsas/fetchable.h>
#include "message_entry.h"
#include "rrset_entry.h"


using namespace isc::dns;

namespace isc {
namespace cache {

MessageEntry::MessageEntry(const isc::dns::Message&,
                           boost::shared_ptr<RRsetCache> rrset_cache):
    rrset_cache_(rrset_cache)
{

}
    
bool
MessageEntry::genMessage(const time_t&,
                         const uint16_t,
                         isc::dns::Message&)
{
    return true;
}

void
MessageEntry::initMessageEntry(const isc::dns::Message& msg) {
    query_count_ = msg.getRRCount(Message::SECTION_QUESTION);
    answer_count_ = msg.getRRCount(Message::SECTION_ANSWER);
    authority_count_ = msg.getRRCount(Message::SECTION_AUTHORITY);
    additional_count_ = msg.getRRCount(Message::SECTION_ADDITIONAL);

    // query_header \\TODO how to cache the header?
    RRsetIterator iter;
    for (iter = msg.beginSection(Message::SECTION_ANSWER);
         iter != msg.endSection(Message::SECTION_ANSWER);
         ++iter) {
        //*rit is one pointer to RRset.
        //boost::shared_ptr<RRsetEntry> entry_ptr = new RRsetEntry(*(*iter);
        //rrsets_.append(entry_ptr);

        // Add the rrset entry to rrset_cache or update the existed 
        // rrset entry if the new one is more authoritative.
    }

}

} // namespace cache
} // namespace isc


