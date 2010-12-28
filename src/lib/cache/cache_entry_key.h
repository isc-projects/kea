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

#ifndef __CACHE_ENTRY_H
#define __CACHE_ENTRY_H

#include <string>


namespace isc {
namespace cache {

class Name;
class RRtype;

std::pair<const char*, const uint32_t>
genCacheEntryKey(const isc::dns::Name& qname,
                 const isc::dns::RRType& qtype) 
{
    std::string keystr = qname.toText();
    //TODO, use uint16_t rcode in case the text is too long?
    keystr += qtype.toText(); 
    return std::pair<const char*, const uint32_t>(keystr.c_str(), keystr.length());
}
    
} // namespace cache
} // namespace isc

#endif // __CACHE_ENTRY_H

