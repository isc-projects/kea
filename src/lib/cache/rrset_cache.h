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

#ifndef __RRSET_CACHE_H
#define __RRSET_CACHE_H

#include <rrset_entry.h>
#include <nsas/hash_table.h>
#include <nsas/lru_list.h>

using namespace isc::nsas;

namespace isc {
namespace cache {

class RRsetEntry;

/// \brief RRset Cache
/// The object of RRsetCache represented the cache for class-specific
/// RRsets.
class RRsetCache{
public:
    RRsetCache(uint32_t cache_size);
    
    /// \brief Look up rrset in cache.
    /// \return return the shared_ptr of rrset entry if it can 
    /// found in the cache, or else, return NULL.
    RRsetEntryPtr lookup(const isc::dns::Name& qname,
                         const isc::dns::RRType& qtype);

    /// \brief Update RRset Cache
    /// Update the rrset entry in the cache with the new one.
    /// If the rrset has expired or doesn't exist in the cache, 
    /// it will be added directly. It may be ingored if the new 
    /// rrset is not more authoritative than the old rrset in cache.
    /// 
    /// \param rrset The new rrset used to update cache.
    /// \param level trustworthiness of the rrset.
    /// \return return the rrset entry in the cache, it may be the 
    /// new added rrset entry or existed one if it is not replaced.
    RRsetEntryPtr update(const isc::dns::RRset& rrset,
                         const RRsetTrustLevel& level);

    /// \brief Dump the rrset cache to specified file.
    /// \todo It should can be dumped to one configured database.
    void dump(const std::string& file_name);

    /// \brief Load the cache from one file.
    /// \todo It should can be loaded from one configured database.
    void load(const std::string& file_name);

    /// \brief Resize the size of rrset cache in runtime. 
    bool resize(uint32_t size);

protected:
    /// \brief Get the hash key for the rrset entry in the cache.
    /// \param name name of the rrset.
    /// \param type type of the rrset.
    /// \return return the hash key.
    HashKey getEntryHashKey(const isc::dns::Name& name, 
                            const isc::dns::RRType& type) const;

private:
    uint16_t class_; // The class of the rrset cache.
    isc::nsas::HashTable<RRsetEntry> rrset_table_;
    isc::nsas::LruList<RRsetEntry> rrset_lru_;

};
    
} // namespace cache
} // namespace isc

#endif // __RRSET_CACHE_H

