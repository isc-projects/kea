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

#ifndef __RECURSOR_CACHE_H
#define __RECURSOR_CACHE_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/message.h>
#include "message_cache.h"


namespace isc {
namespace cache {
class RRsetCache;

///    
/// \brief Recursor Cache
/// The object of RecursorCache represents the cache of the recursor. It holds
/// a list of message cache and rrset cache.
///
class RecursorCache {
public:
    RecursorCache();

    /// \name Lookup Interfaces
    //@{
    /// \brief Look up message in cache.
    ///
    /// \param response generated response message if the message can be found 
    ///  in cache.
    ///
    /// \return return true if the message can be found, or else, return false.
    bool lookUp(const isc::dns::Name& qname, 
                const isc::dns::RRType& qtype,
                const isc::dns::RRClass& qclass,
                isc::dns::Message& response);

    /// \brief Look up rrset in cache.
    /// \param rrset generated rrset if it can be found in the cache.
    /// \return return true if the rrset can be found, or else, return false.
    ///
    /// \overload
    ///
    bool lookUp(const isc::dns::Name& qname, 
                const isc::dns::RRType& qtype,
                const isc::dns::RRClass& qclass,
                isc::dns::RRset& rrset);
    //@}

    /// \brief Update the message in the cache with the new one.
    void update(const isc::dns::Message& msg);

    /// \brief Update the rrset in the cache with the new one.
    /// rrset_cache1_ and rrset_cache2_ should be updated together
    /// if the rrset exists in both of them.
    ///
    /// \overload 
    ///
    void update(const isc::dns::RRset& rrset);

    /// \name Cache Serialization
    //@{
    /// \brief Dump the cache content to one file.
    /// \todo It should can be dumped to one configured database.
    void dump(const std::string& file_name);

    /// \brief Load the cache from one file.
    /// \todo It should can be loaded from one configured database.
    void load(const std::string& file_name);
    //@}

protected:

    /// \brief the list of message cache for configured classes(message cache
    /// is class-specific)
    std::map<uint16_t, MessageCache*> messages_cache_;
    
    /// \name rrset caches
    //@{
    /// \brief the list of rrset cache for configured classes.
    /// rrsets_cache1_ is used to cache the configured rrsets in localzone, rrsets 
    /// in it will never expire.
    std::map<uint16_t, RRsetCache*> rrsets_cache1_;

    /// \brief cache the rrsets parsed from the received message.
    std::map<uint16_t, RRsetCache*> rrsets_cache2_;
    //@}
};

} // namespace cache
} // namespace isc

#endif // __RECURSOR_CACHE_H

