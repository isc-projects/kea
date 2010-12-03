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

#ifndef __ZONE_ENTRY_H
#define __ZONE_ENTRY_H

#include <string>
#include <vector>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/rrset.h>

#include "hash_key.h"
#include "nsas_entry.h"
#include "asiolink.h"
#include "fetchable.h"
#include "resolver_interface.h"
#include "nsas_types.h"

namespace isc {
namespace nsas {

class NameserverEntry;
class AddressRequestCallback;

/// \brief Zone Entry
///
/// The zone entry object describes a zone for which nameserver address
/// information is held.
///
/// Although the interface is simple, the internal processing is fairly
/// complicated, in that the class takes account of triggering fetches for
/// addresses of nameservers when the address records expire.

class ZoneEntry : public NsasEntry<ZoneEntry>, public Fetchable {
public:

    /**
     * \brief Constructor.
     *
     * It asks the resolver any needed questions to get the nameservers.
     *
     * \param resolver The resolver used to ask for IP addresses
     * \param name Name of the zone
     * \param class_code Class of this zone (zones of different classes have
     *     different objects.
     * \todo Move to cc file, include the lookup (if NSAS uses resolver for
     *     everything)
     */
    ZoneEntry(boost::shared_ptr<ResolverInterface> resolver,
        const std::string& name, const isc::dns::RRClass& class_code,
        boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table,
        boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru) :
        expiry_(0),
        name_(name), class_code_(class_code), resolver_(resolver),
        nameserver_table_(nameserver_table), nameserver_lru_(nameserver_lru)
    {}

    /// \return Name of the zone
    std::string getName() const {
        return name_;
    }

    /// \return Class of zone
    const isc::dns::RRClass& getClass() const {
        return class_code_;
    }

    /// \return Return Hash Key
    virtual HashKey hashKey() const {
        return HashKey(name_, class_code_);
    }

    /**
     * \short Put another callback inside.
     *
     * This callback is either executed right away, if it is possible,
     * or queued for later.
     *
     * \param callback The callback itself.
     * \param family Which address family is acceptable as an answer?
     * \param self A shared pointer to this zone entry. It is not possible to
     *     create one from C++ this pointer, since another shared pointer
     *     will already exist at that point, however it is needed to callback.
     *     When calling function on the zone entry, you should already have
     *     one.
     */
    void addCallback(boost::shared_ptr<AddressRequestCallback>
        callback, AddressFamily family, boost::shared_ptr<ZoneEntry> self);

    /// \short Protected members, so they can be accessed by tests.
    //@{
protected:
    // TODO Read-Write lock?
    typedef boost::shared_ptr<NameserverEntry> NameserverPtr;
    typedef std::vector<NameserverPtr> NameserverVector;
    NameserverVector nameservers_; ///< Nameservers
    /*
     * Callbacks. For each fimily type one vector, so we can process
     * them separately.
     */
    std::vector<boost::shared_ptr<AddressRequestCallback> >
        callbacks_[ADDR_REQ_MAX];
    time_t          expiry_;    ///< Expiry time of this entry, 0 means not set
    //}@
private:
    mutable boost::mutex    mutex_;     ///< Mutex protecting this zone entry
    std::string     name_;      ///< Canonical zone name
    isc::dns::RRClass        class_code_; ///< Class code
    // Internal function that adds a callback (if there's one) and processes
    // the nameservers (if there's chance there's some info) and calls
    // callbacks. If nameserver is given, it is considered new and valid
    // even if its TTL is 0.
    // The family says which one changed or has any update.
    // If the familly is ADDR_REQ_MAX, then it means process all callbacks.
    // However, you must not provide callback.
    // If lock is provided, it is locked mutex_ and will be used. If not,
    // will use its own.
    void process(boost::shared_ptr<AddressRequestCallback> callback,
         AddressFamily family, NameserverEntry* nameserver,
         boost::shared_ptr<boost::mutex::scoped_lock> lock =
         boost::shared_ptr<boost::mutex::scoped_lock>());
    // Resolver we use
    boost::shared_ptr<ResolverInterface> resolver_;
    // We store the nameserver table and lru, so we can look up when there's
    // update
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table_;
    boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru_;
    // Resolver callback class
    class ResolverCallback;
    // It has direct access to us
    friend class ResolverCallback;
};

} // namespace nsas
} // namespace isc

#endif // __ZONE_ENTRY_H
