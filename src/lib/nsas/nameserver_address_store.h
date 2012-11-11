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

#ifndef NAMESERVER_ADDRESS_STORE_H
#define NAMESERVER_ADDRESS_STORE_H

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <resolve/resolver_interface.h>

#include "nsas_types.h"
#include "glue_hints.h"

namespace isc {
// Some forward declarations, so we do not need to include so many headers

namespace dns {
class RRClass;
}

namespace util {
template<class T> class LruList;
}

namespace nsas {

template<class T> class HashTable;
class ZoneEntry;
class NameserverEntry;
class AddressRequestCallback;

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
    /// \param resolver Which resolver object (or resolver-like, in case of
    /// tests) should it use to ask questions.
    /// \param zonehashsize Size of the zone hash table.  The default value of
    /// 1009 is the first prime number above 1000.
    /// \param nshashsize Size of the nameserver hash table.  The default
    /// value of 3001 is the first prime number over 3000, and by implication,
    /// there is an assumption that there will be more nameservers than zones
    /// in the store.
    NameserverAddressStore(
        boost::shared_ptr<isc::resolve::ResolverInterface> resolver,
        uint32_t zonehashsize = 1009, uint32_t nshashsize = 3001);

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
    /// \param class_code Class of the zone.
    /// \param callback Callback object used to pass the result back to the
    /// caller.
    /// \param family Which address is requested.
    void lookup(const std::string& zone, const dns::RRClass& class_code,
        boost::shared_ptr<AddressRequestCallback> callback, AddressFamily
        family = ANY_OK, const GlueHints& = GlueHints());

    /// \brief cancel the given lookup action
    ///
    /// \param zone Name of zone.
    /// \param class_code Class of the zone.
    /// \param callback Callback object that would be called.
    /// \param family Address family for which lookup is being cancelled.
    void cancel(const std::string& zone, const dns::RRClass& class_code,
                const boost::shared_ptr<AddressRequestCallback>& callback,
                AddressFamily family = ANY_OK);

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
    boost::shared_ptr<HashTable<ZoneEntry> > zone_hash_;
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_hash_;

    // ... and the LRU lists
    boost::shared_ptr<isc::util::LruList<ZoneEntry> > zone_lru_;
    boost::shared_ptr<isc::util::LruList<NameserverEntry> > nameserver_lru_;
    // The resolver we use
private:
    isc::resolve::ResolverInterface* resolver_;
    //}@
};

} // namespace nsas
} // namespace isc


#endif // NAMESERVER_ADDRESS_STORE_H
