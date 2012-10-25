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

#ifndef NAMESERVER_ENTRY_H
#define NAMESERVER_ENTRY_H

#include <string>
#include <vector>
#include <boost/enable_shared_from_this.hpp>

#include <exceptions/exceptions.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

#include <resolve/resolver_interface.h>

#include <util/lru_list.h>

#include "address_entry.h"
#include "asiolink.h"
#include "nsas_types.h"
#include "hash_key.h"
#include "fetchable.h"
#include "nsas_entry.h"
#include "nameserver_address.h"

namespace isc {
namespace nsas {

class NameserverAddress;

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

/// \brief RTT is zero
///
/// Thrown if a RTT related with an address is 0.
class RTTIsZero : public Exception {
public:
    RTTIsZero(const char* file, size_t line, const char* what) :
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

/// \brief Nameserver Entry
///
/// Describes a nameserver and its addresses.  A nameserver be authoritative
/// for several zones (hence is pointed to by more than one zone entry), and
/// may have several addresses associated with it.
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

class NameserverEntry : public NsasEntry<NameserverEntry>, public Fetchable {
public:
    /// List of addresses associated with this nameserver
    typedef std::vector<NameserverAddress>   AddressVector;
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
    {
        has_address_[V4_ONLY] = false;
        has_address_[V6_ONLY] = false;
        has_address_[ANY_OK] = false;
        expect_address_[V4_ONLY] = false;
        expect_address_[V6_ONLY] = false;
        expect_address_[ANY_OK] = false;
    }

    /*
     * \brief Return Address
     *
     * Returns a vector of addresses corresponding to this nameserver.
     *
     * \param addresses Vector of address entries into which will be appended
     *     addresses that match the specified criteria. (The reason for
     *     choosing this signature is that addresses from more than one
     *     nameserver may be retrieved, in which case appending to an existing
     *     list of addresses is convenient.)
     * \param family The family of address that is requested.
     * \param expired_ok Return addresses even when expired. This is here
     *     because an address with TTL 0 is expired at the exact time it
     *     arrives. But when we call the callback, the owner of callback
     *     is allowed to use them anyway so it should set expired_ok
     *     to true.
     * \return The state this is currently in. If the TTL expires, it enters
     *     the EXPIRED state by itself and passes no addresses. It may be
     *     IN_PROGRESS and still return some addresses (when one address family
     *     arrived and is is returned, but the other is still on the way).
     * \todo Should we sort out unreachable addresses as well?
     */
    Fetchable::State getAddresses(AddressVector& addresses,
        AddressFamily family = ANY_OK, bool expired_ok = false);

    /// \brief Return Address that corresponding to the index
    ///
    /// \param index The address index in the address vector
    /// \param family The address family, V4_ONLY or V6_ONLY
    asiolink::IOAddress getAddressAtIndex(size_t index,
        AddressFamily family) const;

    /// \brief Update RTT
    ///
    /// Updates the RTT for a particular address
    ///
    /// \param address Address to update
    /// \param rtt New RTT for the address
    void setAddressRTT(const asiolink::IOAddress& address, uint32_t rtt);

    /// \brief Update RTT of the address that corresponding to the index
    ///
    /// Shouldn't probably be used directly. Use corresponding
    /// NameserverAddress.
    /// \param rtt Round-Trip Time
    /// \param index The address's index in address vector
    /// \param family The address family, V4_ONLY or V6_ONLY
    void updateAddressRTTAtIndex(uint32_t rtt, size_t index,
        AddressFamily family);
    /**
     * \short Update RTT of an address.
     *
     * This is similar to updateAddressRTTAtIndex, but you pass the address,
     * not it's index. Passing the index might be unsafe, because the position
     * of the address or the cound of addresses may change in time.
     *
     * \param rtt Round-Trip Time
     * \param address The address whose RTT should be updated.
     * \param family The address family, V4_ONLY or V6_ONLY
     */
    void updateAddressRTT(uint32_t rtt, const asiolink::IOAddress& address,
        AddressFamily family);

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
    void askIP(isc::resolve::ResolverInterface* resolver,
        boost::shared_ptr<Callback> callback, AddressFamily family);
    //@}

private:
    mutable isc::util::locks::recursive_mutex    mutex_;///< Mutex protecting this object
    std::string     name_;              ///< Canonical name of the nameserver
    isc::dns::RRClass classCode_;       ///< Class of the nameserver
    /**
     * \short Address lists.
     *
     * Only V4_ONLY and V6_ONLY is used, therefore we use the nearest larger
     * value as the size of the array.
     *
     * previous_addresses is kept until the data arrive again on re-fetch and
     * is used to pick up the RTTs from there.
     */
    std::vector<AddressEntry> addresses_[ANY_OK], previous_addresses_[ANY_OK];
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
    void askIP(isc::resolve::ResolverInterface* resolver,
        const isc::dns::RRType&, AddressFamily);
};

}   // namespace dns
}   // namespace isc

#endif // NAMESERVER_ENTRY_H
