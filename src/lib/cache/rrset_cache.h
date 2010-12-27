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
    /// \param msg_entry
    /// \return return true if the message can be found in cache, or else,
    /// return false.
    bool lookUp(const isc::dns::Name& qname,
                const isc::dns::RRType& qtype,
                const isc::dns::RRClass& qclass,
                RRsetEntry& rrset_entry);

    /// \brief Update the rrset in the cache with the new one.
    /// If the rrset doesn't exist in the cache, it will be added
    /// directly. It may be ingored if the new rrset is not more
    /// authoritative than the old rrset in cache.
    bool update(const isc::dns::RRset& rrset);

    /// \brief Dump the rrset cache to specified file.
    /// \todo It should can be dumped to one configured database.
    void dump(const std::string& file_name);

    /// \brief Load the cache from one file.
    /// \todo It should can be loaded from one configured database.
    void load(const std::string& file_name);

    /// \brief Resize the size of rrset cache in runtime. 
    bool resize(uint32_t size);

private:
    uint16_t class_; // The class of the rrset cache.
    isc::nsas::HashTable<RRsetEntry> rrset_table_;
    isc::nsas::LruList<RRsetEntry> rrset_lru_;

};
    
} // namespace cache
} // namespace isc

#endif // __RRSET_CACHE_H

