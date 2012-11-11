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

#ifndef ZONE_ENTRY_H
#define ZONE_ENTRY_H

#include <string>
#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <dns/rrset.h>

#include <resolve/resolver_interface.h>

#include <util/locks.h>
#include <util/random/random_number_generator.h>

#include "hash_key.h"
#include "nsas_entry.h"
#include "asiolink.h"
#include "fetchable.h"
#include "nsas_types.h"
#include "glue_hints.h"

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
     * \param nameserver_table Hashtable of NameServerEntry objects for
     *     this zone
     * \param nameserver_lru LRU for the nameserver entries
     * \todo Move to cc file, include the lookup (if NSAS uses resolver for
     *     everything)
     */
    ZoneEntry(isc::resolve::ResolverInterface* resolver,
        const std::string& name, const isc::dns::RRClass& class_code,
        boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table,
        boost::shared_ptr<isc::util::LruList<NameserverEntry> > nameserver_lru);

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
     * \param glue_hints If a non-empty glue-hints object is passed,
     *        and the NSAS does not have an immediate answer, it will
     *        call back immediately with one of the glue hints.
     */
    void addCallback(boost::shared_ptr<AddressRequestCallback>
        callback, AddressFamily family,
        const GlueHints& glue_hints = GlueHints());

    /**
     * \short Remove a callback from the list
     *
     * \param callback The callback itself.
     * \param family Which address family is acceptable as an answer?
     */
    void removeCallback(const boost::shared_ptr<AddressRequestCallback>&
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
    mutable isc::util::locks::recursive_mutex    mutex_;///< Mutex protecting this zone entry
    std::string     name_;      ///< Canonical zone name
    isc::dns::RRClass        class_code_; ///< Class code
    /**
     * \short Process all the callbacks that can be processed
     *
     * The purpose of this funtion is to ask all nameservers for their IP
     * addresses and execute all callbacks that can be executed. It is
     * called whenever new callback appears and there's a chance it could
     * be answered or when new information is available (list of nameservers,
     * nameserver is unreachable or has an address).
     * \param family Which is the interesting address family where the change
     *     happened. ADDR_REQ_MAX means it could be any of them and it will
     *     trigger processing of all callbacks no matter what their family
     *     was.
     * \param nameserver Pass a nameserver if the change was triggered by
     *     the nameserver (if it wasn't triggered by a nameserver, pass empty
     *     pointer). This one will be accepted even with 0 TTL, the information
     *     just arrived and we are allowed to use it just now.
     * \todo With the recursive locks now, we might want to simplify executing
     *     callbacks (here and other functions as well);
     */
    void process(AddressFamily family,
        const boost::shared_ptr<NameserverEntry>& nameserver);
    // Resolver we use
    isc::resolve::ResolverInterface* resolver_;
    // We store the nameserver table and lru, so we can look up when there's
    // update
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table_;
    boost::shared_ptr<isc::util::LruList<NameserverEntry> > nameserver_lru_;
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
    // This dispatches callbacks of given family with failures
    void dispatchFailures(AddressFamily family);
    // Put a callback into the nameserver entry. Same ADDR_REQ_MAX means for
    // all families
    void insertCallback(NameserverPtr nameserver, AddressFamily family);
    // A random generator for this zone entry
    // TODO: A more global one? Per thread one?
    isc::util::random::WeightedRandomIntegerGenerator address_selector;
};

} // namespace nsas
} // namespace isc

#endif // ZONE_ENTRY_H
