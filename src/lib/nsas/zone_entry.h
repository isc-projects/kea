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
#include <set>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

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
///
/// It uses shared_from_this in its methods. It must live inside a shared_ptr.

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
        boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru);

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
     */
    void addCallback(boost::shared_ptr<AddressRequestCallback>
        callback, AddressFamily family);

    /// \short Protected members, so they can be accessed by tests.
    //@{
protected:
    // TODO Read-Write lock?
    typedef boost::shared_ptr<NameserverEntry> NameserverPtr;
    typedef std::vector<NameserverPtr> NameserverVector;
    NameserverVector nameservers_; ///< Nameservers
    // Which nameservers didn't have any of our callbacks yet
    std::set<NameserverPtr> nameservers_not_asked_;
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
    // will use its own. It will unlock the lock if it terminates without
    // an exception.
    void process(boost::shared_ptr<AddressRequestCallback> callback,
         AddressFamily family, boost::shared_ptr<NameserverEntry> nameserver,
         boost::shared_ptr<boost::mutex::scoped_lock> lock =
         boost::shared_ptr<boost::mutex::scoped_lock>());
    // Resolver we use
    boost::shared_ptr<ResolverInterface> resolver_;
    // We store the nameserver table and lru, so we can look up when there's
    // update
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table_;
    boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru_;
    // Resolver callback class, documentation with the class declaration
    class ResolverCallback;
    // It has direct access to us
    friend class ResolverCallback;
    // Guard class to eliminate missing finally
    class ProcessGuard;
    friend class ProcessGuard;
    // Are we in the process method?
    bool in_process_[ADDR_REQ_MAX];
    // Callback from nameserver entry (documented with the class)
    class NameserverCallback;
    // And it can get into our internals as well (call process)
    friend class NameserverCallback;
    // This dispatches callbacks of given family with failures (and unlocks)
    // The lock is mandatory
    void dispatchFailures(AddressFamily family,
        boost::shared_ptr<boost::mutex::scoped_lock> lock);
    // Put a callback into the nameserver entry. Same ADDR_REQ_MAX means for
    // all families
    void insertCallback(NameserverPtr nameserver, AddressFamily family);
};

} // namespace nsas
} // namespace isc

#endif // __ZONE_ENTRY_H
