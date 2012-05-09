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

#include <config.h>

#include <dns/message.h>
#include <nsas/nsas_entry.h>
#include <nsas/fetchable.h>
#include "rrset_entry.h"
#include "rrset_copy.h"

using namespace isc::dns;

namespace isc {
namespace cache {

RRsetEntry::RRsetEntry(const isc::dns::AbstractRRset& rrset,
                       const RRsetTrustLevel& level):
    entry_name_(genCacheEntryName(rrset.getName(), rrset.getType())),
    expire_time_(time(NULL) + rrset.getTTL().getValue()),
    trust_level_(level),
    rrset_(new RRset(rrset.getName(), rrset.getClass(), rrset.getType(), rrset.getTTL())),
    hash_key_(HashKey(entry_name_, rrset_->getClass()))
{
    rrsetCopy(rrset, *(rrset_.get()));
}

isc::dns::RRsetPtr
RRsetEntry::getRRset() {
    updateTTL();
    return (rrset_);
}

time_t
RRsetEntry::getExpireTime() const {
    return (expire_time_);
}

void
RRsetEntry::updateTTL(){
    uint32_t oldTTL = rrset_->getTTL().getValue();
    if(oldTTL == 0) {
        return;
    }

    uint32_t now = time(NULL);
    uint32_t newTTL = now < expire_time_ ? (expire_time_ - now) : 0;

    RRTTL ttl(newTTL);
    rrset_->setTTL(ttl);
}

} // namespace cache
} // namespace isc


