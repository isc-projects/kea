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

#ifndef __MESSAGE_ENTRY_H
#define __MESSAGE_ENTRY_H

#include <vector>
#include <dns/message.h>
#include <dns/rrset.h>
#include <boost/noncopyable.hpp>
#include <nsas/nsas_entry.h>
#include "rrset_entry.h"


using namespace isc::nsas;

namespace isc {
namespace cache {

class RRsetEntry;
class RRsetCache;

/// \brief Information to refer an RRset.
/// There is no class information here, since the rrsets
/// are cached in the class-specific rrset cache.
struct RRsetRef{
    RRsetRef(const isc::dns::Name& name, const isc::dns::RRType& type):
            name_(name), type_(type)
    {}

    isc::dns::Name name_; // Name of rrset.
    isc::dns::RRType type_; // Type of rrset. 
};

/// \brief Message Entry
/// The object of MessageEntry represents one response message
/// answered to the recursor client. 
class MessageEntry : public NsasEntry<MessageEntry>,
                     public boost::noncopyable
{
public:

    /// \brief Initialize the message entry object with one dns 
    /// message.
    /// \param message The message used to initialize MessageEntry.
    /// \param rrset_cache the pointer of RRsetCache. When one message
    /// entry is created, rrset cache needs to be updated, since some
    /// new rrset entries may be inserted into the rrset cache, or the
    /// existed rrset entries need to be updated.
    MessageEntry(const isc::dns::Message& message,
                 boost::shared_ptr<RRsetCache> rrset_cache);

    /// \brief generate one dns message according 
    /// the rrsets information of the message.
    /// \param response generated dns message.
    /// \param time_now set the ttl of each rrset in the message
    ///        as "expire_time - time_now" (expire_time is the 
    ///        expiration time of the rrset).
    /// \return return true if the response message can be generated 
    /// from the cached information, or else, return false.
    bool genMessage(const time_t& time_now,
                    isc::dns::Message& response);
    
    /// \brief Get the hash key of the message entry.
    /// \return return hash key
    virtual HashKey hashKey() const {
        return *hash_key_ptr_;
    }

protected:
    /// \brief Initialize the message entry with dns message.
    void initMessageEntry(const isc::dns::Message& message);

    /// \brief These two functions should be static functions
    /// placed in cc file. Put them here just for easy unit 
    /// test.
    //@{
    /// \brief Parse the rrsets in specified section.
    /// \param smaller_ttl Get the smallest ttl of rrsets in 
    /// specified section, if it's smaller than the given value.
    /// \param rrset_count set the rrset count of the section.
    /// (TODO for Message, getRRsetCount() should be one interface provided 
    //  by Message.)
    void parseSection(const isc::dns::Message& msg,
                    const isc::dns::Message::Section& section,
                    uint32_t& smaller_ttl,
                    uint16_t& rrset_count);

    /// \brief Get RRset Trust worthiness
    /// The algorithm refers to RFC2181 section 5.4.1
    ///
    /// Only the rrset can be updated by the rrsets 
    /// with higher trust level.
    /// 
    /// \param message Message that the rrset belongs to
    /// \param rrset specified rrset which needs to get its 
    ///     trust worthiness
    /// \param section Section of the rrset
    /// \return return rrset trust level.
    RRsetTrustLevel getRRsetTrustLevel(const isc::dns::Message& message,
                               const isc::dns::RRsetPtr rrset,
                               const isc::dns::Message::Section& section);

    /// \brief Add rrset to one section of message.
    /// \param dnssec_need need dnssec records or not.
    /// \param message The message to add rrsets.
    /// \param rrset_entry_vec vector for rrset entries in
    ///        different sections.
    void addRRset(isc::dns::Message& message,
                  const std::vector<RRsetEntryPtr> rrset_entry_vec,
                  isc::dns::Message::Section section,
                  bool dnssec_need);

    /// \brief Get the all the rrset entries for the message entry.
    /// \param rrset_entry_vec vector of rrset entries
    /// \param time_now the time of now. Used to compare with rrset
    ///        entry's expire time.
    /// \return return false if any rrset entry has expired, or else,
    ///         return false.
    bool getRRsetEntries(std::vector<RRsetEntryPtr>& rrset_entry_vec, 
                         const time_t time_now); 
    //@}
protected:
    /// \note Make the variable be protected for easy test.
    time_t expire_time_;  // Expiration time of the message.

private:
    std::string entry_name_; // The name for this entry(name + type)
    HashKey* hash_key_ptr_;  // the key for messag entry in hash table.

    std::vector<RRsetRef> rrsets_;
    boost::shared_ptr<RRsetCache> rrset_cache_;

    std::string query_name_; // query name of the message.
    uint16_t query_class_; // query class of the message.
    uint16_t query_type_; // query type of message.

    uint16_t query_count_; // query count in query section.
    uint16_t answer_count_; // rrset count in answer section.
    uint16_t authority_count_; // rrset count in authority section.
    uint16_t additional_count_; // rrset count in addition section.

    //TODO, there should be a better way to cache these header flags
    bool headerflag_aa_; // Whether AA bit is set.
    bool headerflag_tc_; // Whether TC bit is set.
};
    
typedef boost::shared_ptr<MessageEntry> MessageEntryPtr;

} // namespace cache
} // namespace isc

#endif // __MESSAGE_ENTRY_H

