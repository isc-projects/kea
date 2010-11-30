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
#include <list>
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
     * \brief Constructor where no NS records are supplied
     *
     * It is here mostly for testing purposes.
     *
     * \param resolver The resolver used to ask for IP addresses
     * \param name Name of the zone
     * \param class_code Class of this zone (zones of different classes have
     *     different objects.
     * \todo Move to cc file, include the lookup (if NSAS uses resolver for
     *     everything)
     */
    ZoneEntry(boost::shared_ptr<ResolverInterface> resolver,
        const std::string& name, uint16_t class_code,
        boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table,
        boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru) :
        name_(name), classCode_(class_code), resolver_(resolver),
        nameserver_table_(nameserver_table), nameserver_lru_(nameserver_lru)
    {}

    /**
     * \brief Constructor
     *
     * Creates a zone entry object with an RRset representing the nameservers.
     *
     * \param resolver The resolver used to ask for IP addresses
     * \param authority Specifies the name, code and nameservers of this zone.
     * \param nameserver_table Hash table of existing nameserves and a place
     *     where new ones will be put.
     * \param nameserver_lru The lru where the nameservers will be added or
     *     touched.
     * \todo This might be completely unneeded if NSAS uses resolver for
     *     everything.
     */
    ZoneEntry(boost::shared_ptr<ResolverInterface> resolver,
        const isc::dns::AbstractRRset& authority,
        boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table,
        boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru);

    /// \return Name of the zone
    std::string getName() const {
        return name_;
    }

    /// \return Class of zone
    const isc::dns::RRClass& getClass() const {
        return classCode_;
    }

    /// \return Return Hash Key
    virtual HashKey hashKey() const {
        return HashKey(name_, classCode_);
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
     * \return True if the zone is still valid and accepted the callback.
     *     If it returns false, it should be discarded (it has timed out)
     *     and new instance should be created.
     */
    bool addCallback(boost::shared_ptr<AddressRequestCallback>
        callback, AddressFamily family, boost::shared_ptr<ZoneEntry> self);

    /// \short Protected members, so they can be accessed by tests.
    //@{
protected:
    // TODO Read-Write lock?
    typedef boost::shared_ptr<NameserverEntry> NameserverPtr;
    typedef std::vector<NameserverPtr> NameserverVector;
    NameserverVector nameservers_; ///< Nameservers
    std::list<boost::shared_ptr<AddressRequestCallback> > callbacks_;
    time_t          expiry_;    ///< Expiry time of this entry
    //}@
private:
    mutable boost::mutex    mutex_;     ///< Mutex protecting this zone entry
    std::string     name_;      ///< Canonical zone name
    isc::dns::RRClass        classCode_; ///< Class code
    // Internal function that adds a callback (if there's one) and processes
    // the nameservers (if there's chance there's some info) and calls
    // callbacks. If nameserver is given, it is considered new and valid
    // even if its TTL is 0.
    void process(boost::shared_ptr<AddressRequestCallback> callback,
         AddressFamily family, NameserverEntry* nameserver);
    // Resolver we use
    boost::shared_ptr<ResolverInterface> resolver_;
    // We store the nameserver table and lru, so we can look up when there's
    // update
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table_;
    boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru_;
};

} // namespace nsas
} // namespace isc

#endif // __ZONE_ENTRY_H
