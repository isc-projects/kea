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
#include <boost/enable_shared_from_this.hpp>

#include <exceptions/exceptions.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

#include "address_entry.h"
#include "asiolink.h"
#include "nsas_entry.h"
#include "nsas_types.h"
#include "hash_key.h"
#include "lru_list.h"
#include "fetchable.h"
#include "resolver_interface.h"

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

class ZoneEntry;
class ResolverInterface;

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
/// it is derived from the LRU list entry class.
///
/// It uses shared_from_this in its methods. It must live inside a shared_ptr.

class NameserverEntry : public NsasEntry<NameserverEntry>, public Fetchable,
    public boost::enable_shared_from_this<NameserverEntry>
{
public:
    /// List of addresses associated with this nameserver
    typedef std::vector<AddressEntry>   AddressVector;
    typedef AddressVector::iterator     AddressVectorIterator;

    /// \brief Constructor where no A records are supplied.
    ///
    /// \param name Name of the nameserver,
    /// \param class_code class of the nameserver
    NameserverEntry(const std::string& name,
        const isc::dns::RRClass& class_code) :
        name_(name),
        classCode_(class_code),
        expiration_(0)
    {}

    /// \brief Return Address
    ///
    /// Returns a vector of addresses corresponding to this nameserver.
    ///
    /// \param addresses Vector of address entries into which will be appended
    /// addresses that match the specified criteria. (The reason for choosing
    /// this signature is that addresses from more than one nameserver may be
    /// retrieved, in which case appending to an existing list of addresses is
    /// convenient.)
    /// \param family The family of address that is requested.
    /// else for all addresses.
    /// \param expired_ok Return addresses even when expired. In that case,
    ///     it will pretend to be READY. This is here to allow getting address
    ///     with TTL 0 from a nameserver that just arrived and triggered
    ///     a callback.
    /// \return The state this is currently in. If the TTL expires, it enters
    ///     the EXPIRED state by itself. It may be IN_PROGRESS and still
    ///     return some addresses (when one address family arrived and is
    ///     is returned, but the other is still on the way).
    /// \todo Should we sort out unreachable addresses as well?
    Fetchable::State getAddresses(
        NameserverEntry::AddressVector& addresses,
        AddressFamily family = ANY_OK, bool expired_ok = false);

    // TODO Is this one of any use at all?
    /// \brief Return Address that corresponding to the index
    ///
    /// \param index The address index in the address vector
    asiolink::IOAddress getAddressAtIndex(uint32_t index) const;

    /// \brief Update RTT
    ///
    /// Updates the RTT for a particular address
    ///
    /// \param address Address to update
    /// \param RTT New RTT for the address
    void setAddressRTT(const asiolink::IOAddress& address, uint32_t rtt);

    /// \brief Update RTT of the address that corresponding to the index
    ///
    /// \param rtt Round-Trip Time
    /// \param index The address's index in address vector
    void updateAddressRTTAtIndex(uint32_t rtt, uint32_t index);

    /// \brief Set Address Unreachable
    ///
    /// Sets the specified address to be unreachable
    ///
    /// \param address Address to update
    void setAddressUnreachable(const asiolink::IOAddress& address);

    /// \return Owner Name of RRset
    std::string getName() const {
        return name_;
    }

    /// \return Class of RRset
    const isc::dns::RRClass& getClass() const {
        return classCode_;
    }

    /// \return Hash Key of the Nameserver
    virtual HashKey hashKey() const {
        return HashKey(name_, classCode_);
    }

    /// \return Hash Key of the Nameserver

    /// \return Expiration Time of Data
    ///
    /// Returns the expiration time of addresses for this nameserver.  For
    /// simplicity, this quantity is calculated as the minimum expiration time
    /// of the A and AAAA address records.
    time_t getExpiration() const {
        return expiration_;
    }

    /// \name Obtaining the IP addresses from resolver
    //@{
    /// \short A callback that some information here arrived (or are unavailable).
    struct Callback {
        virtual void operator()(boost::shared_ptr<NameserverEntry> self) = 0;
        /// \short Virtual destructor, so descendants are properly cleaned up
        virtual ~ Callback() {}
    };

    /**
     * \short Asks the resolver for IP address (or addresses).
     *
     * Adds a callback for given zone when they are ready or the information
     * is found unreachable.
     *
     * If it is not in NOT_ASKED or EXPIRED state, it does not ask the for the
     * IP address again, it just inserts the callback. It is up to the caller
     * not to insert one callback multiple times.
     *
     * The callback might be called directly from this function.
     *
     * \param resolver Who to ask.
     * \param callback The callback.
     * \param family Which addresses are interesting to the caller. This does
     *     not change which adresses are requested, but the callback might
     *     be executed when at last one requested type is available (eg. not
     *     waiting for the other one).
     * \return The state the entry is currently in. It can return UNREACHABLE
     *     even when there are addresses, if there are no addresses for this
     *     family.
     */
    void askIP(boost::shared_ptr<ResolverInterface> resolver,
        boost::shared_ptr<Callback> callback, AddressFamily family);
    //@}

private:
    // TODO Read-write lock?
    mutable boost::mutex    mutex_;     ///< Mutex protecting this object
    std::string     name_;              ///< Canonical name of the nameserver
    isc::dns::RRClass classCode_;       ///< Class of the nameserver
    /// The current addresses and addresses from previous request to keep RTT
    std::vector<AddressEntry> address_, previous_addresses_;
    time_t          expiration_;        ///< Summary expiration time. 0 = unset
    // Do we have some addresses already? Do we expect some to come?
    // These are set after asking for IP, if NOT_ASKED, they are uninitialized
    bool has_address_[ADDR_REQ_MAX], expect_address_[ADDR_REQ_MAX];
    // Callbacks from resolver
    class ResolverCallback;
    friend class ResolverCallback;
    // Callbacks inserted into this object
    typedef std::pair<AddressFamily, boost::shared_ptr<Callback> >
        CallbackPair;
    std::vector<CallbackPair> callbacks_;
    /// \short Private version that does the actual asking of one address type
    ///
    /// Call unlocked.
    void askIP(boost::shared_ptr<ResolverInterface> resolver,
        const isc::dns::RRType&, AddressFamily);
};

}   // namespace dns
}   // namespace isc

#endif // __NAMESERVER_ENTRY_H
