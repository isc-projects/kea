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
#include "rrset_entry.h"

using namespace isc::dns;

namespace isc {
namespace cache {

RRsetEntry::RRsetEntry(const isc::dns::RRset& rrset, const RRsetTrustLevel& level): 
    type_(rrset.getClass().getCode()), 
    class_(rrset.getClass().getCode()), ttl_(0), rr_count_(0), rrsig_count_(0),
    expire_time_(0), trust_level_(level)
{
}

isc::dns::RRsetPtr
RRsetEntry::genRRset() const {
    return boost::shared_ptr<isc::dns::RRset> ();
}

time_t
RRsetEntry::getExpireTime() const {
    return expire_time_;
}

HashKey
RRsetEntry::hashKey() const {
    CacheEntryKey keydata = genCacheEntryKey(name_, type_);
    return HashKey(keydata.first, keydata.second, RRClass(class_));
}

} // namespace cache
} // namespace isc


