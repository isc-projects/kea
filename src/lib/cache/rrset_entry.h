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
#include "cache_entry_key.h"

using namespace isc::nsas;

namespace isc {
namespace cache {

class RRset;

/// \enum RRset Trustworthiness
/// For detail of rrset trustworthiness, please refer to
/// RFC2181 section5.4.1.
/// Bigger value is more trustworthy.
enum RRsetTrustLevel {
    // Default trust for rrset. 
    RRSET_TRUST_DEFAULT = 0,
    // Additional information from non-authoritative answer.
    RRSET_TRUST_ADDITIONAL_NONAA,
    // Data from the authority section of a non-authoritative answer
    RRSET_TRUST_AUTHORITY_NONAA,
    // Additional information from an authoritative answer.
    RRSET_TRUST_ADDITIONAL_AA,
    // Non-authoritative data from the answer section of authoritative
    // answers
    RRSET_TRUST_NONAUTH_ANSWER_AA,
    // Data from the answer section of a non-authoritative answer.
    RRSET_TRUST_ANSWER_NONAA,
    // Data from the authority section of an authoritative answer.
    RRSET_TRUST_AUTHORITY_AA, 
    // Authoritative data included in the answer section of 
    // an authoritative reply.
    RRSET_TRUST_ANSWER_AA,
    // Data from a primary zone file, other than glue data.
    RRSET_TRUST_PRIM_ZONE_NONGLUE, ///< RRSET_TRUST_DEFAULT
};

/// \brief RRset Entry
/// The object of RRsetEntry represents one cached rrset.
/// Each rrset entry may be refered using shared_ptr by several message 
/// entries.
class RRsetEntry : public NsasEntry<RRsetEntry>, 
                   public Fetchable 
{
public:
    /// \param rrset The rrset used to initialize the rrset entry.
    /// \param level trustworthiness of the rrset.
    RRsetEntry(const isc::dns::RRset& rrset, const RRsetTrustLevel& level);

    /// \brief Generate one rrset according the entry information.
    boost::shared_ptr<RRset> genRRset() const;
    
    /// \brief Get the expiration time of the rrset.
    time_t getExpireTime() const;

    /// \brief Get the ttl of the rrset.
    uint32_t getTTL() const {
        return ttl_;
    }

    /// \return return hash key
    virtual HashKey hashKey() const;

    /// \brief get rrset trustworthiness
    RRsetTrustLevel getTrustLevel() const {
        return trust_level_;
    }

private:
    std::string name_; // rrset name.
    uint16_t type_; // rrset type.
    uint16_t class_; // rrset class.

    uint32_t ttl_; // ttl of rrset
    uint32_t rr_count;
    uint32_t rrsig_count;

    time_t expire_time_; // Expiration time of rrset.
    RRsetTrustLevel trust_level_; // rrset trustworthiness.
    // sec_status;
};
    
typedef boost::shared_ptr<RRsetEntry> RRsetEntryPtr;    

} // namespace cache
} // namespace isc

#endif // __RRSET_ENTRY_H

