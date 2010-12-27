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

#ifndef __RRSET_ENTRY_H
#define __RRSET_ENTRY_H

#include <dns/message.h>
#include <nsas/nsas_entry.h>
#include <nsas/fetchable.h>


using namespace isc::nsas;

namespace isc {
namespace cache {

class RRsetEntry : public NsasEntry<RRsetEntry>, 
                   public Fetchable 
{
public:
    RRsetEntry();

    /// \brief Generate one rrset according the entry information.
    void generateRRset(isc::dns::RRset& rrset) const;
    
    /// \brief Get the expiration time of the rrset.
    time_t getExpirationTime() const;

private:
    time_t expire_time_; // Expiration time of rrset.
    uint32_t ttl_;
    uint16_t class_;
    uint32_t rr_count;
    uint32_t rrsig_count;
    // sec_status;
    // trust_level; trust or not.
};
    
} // namespace cache
} // namespace isc

#endif // __RRSET_ENTRY_H

