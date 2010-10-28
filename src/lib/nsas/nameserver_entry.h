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

#ifndef __NAMESERVER_ENTRY_H
#define __NAMESERVER_ENTRY_H

#include <string>
#include <vector>
#include <boost/thread.hpp>

#include "address_entry.h"
#include "asiolink.h"
#include "exceptions/exceptions.h"
#include "lru_list.h"
#include "rrset.h"

namespace isc {
namespace nsas {

/// \brief Inconsistent Owner Names
///
/// Thrown if a NameserverEntry is constructed from both an A and AAAA RRset
/// where the owner names do not match.
class InconsistentOwnerNames : public Exception {
public:
    InconsistentOwnerNames(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// \brief Inconsistent Class
///
/// Thrown if a NameserverEntry is constructed from both an A and AAAA RRset
/// where the classes do not match.
class InconsistentClass : public Exception {
public:
    InconsistentClass(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};



/// \brief Nameserver Entry
///
/// Describes a nameserver and its addresses.  A nameserver be authoritative
/// for several zones (hence is pointed to by more than one zone entry), and
/// may have several addresses associated with it.
///
/// When created, zero or more addresses may be given.  At any time, the list
/// of addresses may be updated.  This may occur (a) after creation, either to
/// to get the list of addresses when none have been supplied or to replace
/// glue records, or (b) when the object has been accessed but found to be
/// expired (the address records have reached their TTL).
/// TODO: Add code for update of addresses
///
/// The addresses expire after their TTL has been reached.  For simplicity,
/// (and because it is unlikely that A and AAAA records from the same zone have
/// different TTLs) there is one expiration time for all address records.
/// When that is reached, all records are declared expired and new fetches
/// started for the information.
///
/// As this object will be stored in the nameserver address store LRU list,
/// it is derived from the LRU list element class.

class NameserverEntry : public LruList<NameserverEntry>::Element {
public:
    /// List of addresses associated with this nameserver
    typedef std::vector<AddressEntry>   AddressVector;
    typedef AddressVector::iterator     AddressVectorIterator;

    /// \brief Constructor where no A records are supplied.
    ///
    /// \param name Name of the nameserver,
    /// \param classCode class of the nameserver
    NameserverEntry(const std::string& name, uint16_t classCode) :
        name_(name), classCode_(classCode)
    {}

    /// Constructor where one or more RRsets of A/AAAA records are supplied.
    /// The class is taken from class of address records and the name from
    /// the owner of the records.  If both sets of information are supplied
    /// and the owner names are different, the V4 set wins out; the V6 set of
    /// information is ignored and an error message is logged.
    ///
    /// \param v4Set RRset of A records
    /// \param v6Set RRset of AAAA records
    /// \param curtime Current time.  Present for testing, but also as a
    /// possible optimisation if the caller has the current time (it saves
    /// the overhead of a call to time()).  The default value of 0 requests
    /// the constructor to get its own copy of the current time.
    NameserverEntry(const isc::dns::AbstractRRset* v4Set,
        const isc::dns::AbstractRRset* v6Set, time_t curtime = 0);

    /// \brief Virtual Destructor
    virtual ~NameserverEntry()
    {}

    /// \brief Return Address
    ///
    /// Returns a vector of addresses corresponding to this nameserver.
    /// It is up to the caller to 
    ///
    /// \param addresses Vector of address entries into which will be appended
    /// addresses that match the specified criteria. (The reason for choosing
    /// this signature is that addresses from more than one nameserver may be
    /// retrieved, in which case appending to an existing list of addresses is
    /// convenient.)
    /// \param family Set to AF_INET/AF_INET6 for V6/V6 addresses, anything
    /// else for all addresses.
    virtual void getAddresses(NameserverEntry::AddressVector& addresses, short family = 0) const;

    /// \brief Update RTT
    ///
    /// Updates the RTT for a particular address
    ///
    /// \param address Address to update
    /// \param RTT New RTT for the address
    virtual void setAddressRTT(const asiolink::IOAddress& address, uint32_t rtt);

    /// \brief Set Address Unreachable
    ///
    /// Sets the specified address to be unreachable
    ///
    /// \param address Address to update
    virtual void setAddressUnreachable(const asiolink::IOAddress& address);

    /// \return Owner Name of RRset
    virtual std::string getName() const {
        return name_;
    }

    /// \return Class of RRset
    virtual short getClass() const {
        return classCode_;
    }

    /// \return Expiration Time of Data
    ///
    /// Returns the expiration time of addresses for this nameserver.  For
    /// simplicity, this quantity is calculated as the minimum expiration time
    /// of the A and AAAA address records.
    virtual time_t getExpiration() const {
        return expiration_;
    }


    /// \brief Predicate for Address Selection
    ///
    /// Returns false if the address family of a given entry matches the address
    /// family given or if the address family is 0 (which means return all
    /// addresses).  This curious logic is needed for use in the remove_copy_if
    /// algorithm, which copies all values apart from those for which the
    /// criteria is met.
    class AddressSelection : public std::binary_function<short, AddressEntry, bool> {
    public:
        bool operator()(short family, const AddressEntry& entry) const {
            bool match = (entry.getAddress().getFamily() == family) ||
                (family == 0);
            return (! match);
        }
    };

private:
    boost::mutex    mutex_;             ///< Mutex protecting this object
    std::string     name_;              ///< Canonical name of the nameserver
    uint16_t        classCode_;         ///< Class of the nameserver
    std::vector<AddressEntry> address_; ///< Set of V4/V6 addresses
    time_t          expiration_;        ///< Summary expiration time
    time_t          last_access_;       ///< Last access time to the structure
};

}   // namespace dns
}   // namespace isc

#endif // __NAMESERVER_ENTRY_H
