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

#include "recursor_cache.h"


namespace isc {
namespace cache {

RecursorCache::RecursorCache() {
}

bool
RecursorCache::lookUp(const isc::dns::Name& qname, 
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass,
               isc::dns::Message& response)
{
    //TODO, temp code begin
    qname.toText();
    qtype.toText();
    qclass.toText();
    response.toText();
    //TODO, temp code end 
    return true;
}

bool
RecursorCache::lookUp(const isc::dns::Name& qname, 
               const isc::dns::RRType& qtype,
               const isc::dns::RRClass& qclass,
               isc::dns::RRset& rrset)
{
    //TODO, temp code begin
    qname.toText();
    qtype.toText();
    qclass.toText();
    rrset.toText();
    //TODO, temp code end 
    return true;
}

void
RecursorCache::update(const isc::dns::Message& msg) {
    msg.toText();
    return;
}

void
RecursorCache::update(const isc::dns::RRset& rrset) {
    rrset.toText();
    return;
}

void
RecursorCache::dump(const std::string& file_name) {
    std::cout << file_name;
}

void
RecursorCache::load(const std::string& file_name) {
    std::cout << file_name;
}

} // namespace cache
} // namespace isc

