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

#ifndef __NAMESERVER_ADDRESS_STORE_H
#define __NAMESERVER_ADDRESS_STORE_H

#include <string>
#include <vector>

#include "rrset.h"

#include "address_request_callback.h"
#include "hash_table.h"
#include "nameserver_entry.h"
#include "lru_list.h"
#include "zone_entry.h"

namespace isc {
namespace nsas {

/// \brief Nameserver Address Store
///
/// This class implements the bare bones of the nameserver address store - the
/// storage of nameserver information.  An additional layer above it implements
/// the logic for sending queries for the nameserver addresses if they are not
/// in the store.

class NameserverAddressStore {
public:

    /// \brief Constructor
    ///
    /// The constructor sizes all the tables.  As there are various
    /// relationships between the table sizes, and as some values are best as
    /// prime numbers, the table sizes are determined by compile-time values.
    /// 
    /// \param zonehashsize Size of the zone hash table.  The default value of
    /// 1009 is the first prime number above 1000.
    /// \param nshash size Size of the nameserver hash table.  The default
    /// value of 2003 is the first prime number over 2000, and by implication,
    /// there is an assumption that there will be more nameservers than zones
    /// in the store.
    NameserverAddressStore(uint32_t zonehashsize = 1009,
        uint32_t nshashsize = 3001);

    /// \brief Destructor
    ///
    /// Empty virtual destructor.
    virtual ~NameserverAddressStore()
    {}

    /// \brief Lookup Address for a Zone
    ///
    /// Looks up the address of a nameserver in the zone.
    ///
    /// \param zone Name of zone for which an address is required.
    /// \param authority Authority RRset from the referral containing the
    /// nameservers that serve the zone.
    /// \param additional Additional RRset(s) for authority information.  These
    /// are taken from the referral.
    /// \param callback Callback object used to pass the result back to the
    /// caller.
    /* void lookup(const std::string& zone, isc::dns::AbstractRRset& authority,
        const std::vector<isc::dns::AbstractRRset>& additional
        boost::shared_ptr<isc::dns::AddressRequestCallback> callback ); */

    /// \brief Protected Members
    ///
    /// These members should be private.  However, with so few public methods
    /// and with a lot of internal processing, the testing of this class is
    /// problematical.
    ///
    /// To get round this, a number of elements are declared protected.  This
    /// means that tests can be carried out by testing a subclass.  The subclass
    /// does not override the main class methods, but does contain additional
    /// methods to set up data and examine the internal state of the class.
    //@{
protected:
    // Zone and nameserver hash tables
    HashTable<ZoneEntry>        zone_hash_;
    HashTable<NameserverEntry>  nameserver_hash_;

    // ... and the LRU lists
    LruList<ZoneEntry>          zone_lru_;
    LruList<NameserverEntry>    nameserver_lru_;
    //}@
};

} // namespace nsas
} // namespace isc


#endif // __NAMESERVER_ADDRESS_STORE_H
