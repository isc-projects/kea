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

#ifndef RRSET_ENTRY_H
#define RRSET_ENTRY_H

#include <dns/rrset.h>
#include <dns/message.h>
#include <dns/rrttl.h>
#include <nsas/nsas_entry.h>
#include <nsas/fetchable.h>
#include "cache_entry_key.h"

using namespace isc::nsas;

namespace isc {
namespace cache {

/// \enum RRsetTrustLevel
/// For detail of RRset trustworthiness, please refer to
/// RFC 2181 section 5.4.1.
/// Bigger value is more trustworthy.
enum RRsetTrustLevel {
    /// Default trust for RRset.
    RRSET_TRUST_DEFAULT = 0,
    /// Additional information from non-authoritative answer.
    RRSET_TRUST_ADDITIONAL_NONAA,
    /// Data from the authority section of a non-authoritative answer
    RRSET_TRUST_AUTHORITY_NONAA,
    /// Additional information from an authoritative answer.
    RRSET_TRUST_ADDITIONAL_AA,
    /// Non-authoritative data from the answer section of authoritative
    /// answers
    RRSET_TRUST_NONAUTH_ANSWER_AA,
    /// Data from the answer section of a non-authoritative answer.
    RRSET_TRUST_ANSWER_NONAA,
    /// Glue from a primary zone, or glue from a zone transfer.
    RRSET_TRUST_PRIM_GLUE,
    /// Data from the authority section of an authoritative answer.
    RRSET_TRUST_AUTHORITY_AA,
    /// Authoritative data included in the answer section of
    /// an authoritative reply.
    RRSET_TRUST_ANSWER_AA,
    /// Data from a primary zone file, other than glue data.
    RRSET_TRUST_PRIM_ZONE_NONGLUE
};

/// \brief RRset Entry
/// The object of RRsetEntry represents one cached RRset.
/// Each RRset entry may be refered using shared_ptr by several message
/// entries.
class RRsetEntry : public NsasEntry<RRsetEntry>
{
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private to make it uncopyable
    //@{
private:
    RRsetEntry(const RRsetEntry&);
    RRsetEntry& operator=(const RRsetEntry&);
public:
    /// \brief Constructor
    /// \param rrset The RRset used to initialize the RRset entry.
    /// \param level trustworthiness of the RRset.
    RRsetEntry(const isc::dns::AbstractRRset& rrset,
               const RRsetTrustLevel& level);

    /// The destructor.
    ~RRsetEntry() {}
    //@}

    /// \brief Return a pointer to a generated RRset
    ///
    /// \return Pointer to the generated RRset
    isc::dns::RRsetPtr getRRset();

    /// \brief Get the expiration time of the RRset.
    ///
    /// \return The expiration time of the RRset
    ///
    /// \todo RRsig expiration processing
    time_t getExpireTime() const;

    /// \brief Get the ttl of the RRset.
    ///
    /// \return The TTL of the RRset
    uint32_t getTTL() {
        updateTTL();
        return (rrset_->getTTL().getValue());
    }

    /// \brief Get the hash key
    ///
    /// \return return hash key
    HashKey hashKey() const {
        return (hash_key_);
    }

    /// \brief get RRset trustworthiness
    ///
    /// \return return the trust level
    RRsetTrustLevel getTrustLevel() const {
        return (trust_level_);
    }
private:
    /// \brief Update TTL according to expiration time
    void updateTTL();

private:
    std::string entry_name_; // The entry name for this rrset entry.
    time_t expire_time_;     // Expiration time of rrset.
    RRsetTrustLevel trust_level_; // RRset trustworthiness.
    boost::shared_ptr<isc::dns::RRset> rrset_;
    HashKey hash_key_;       // RRsetEntry hash key
};

typedef boost::shared_ptr<RRsetEntry> RRsetEntryPtr;

} // namespace cache
} // namespace isc

#endif // RRSET_ENTRY_H

