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

    /// \brief Constructor where no NS records are supplied
    ///
    /// \param name Name of the zone
    /// \param class_code Class of this zone (zones of different classes have
    /// different objects.
    ZoneEntry(const std::string& name, uint16_t class_code) :
        name_(name), classCode_(class_code)
    {}

    /// \brief Constructor
    ///
    /// Creates a zone entry object with an RRset representing the nameservers,
    /// plus possibly additional RRsets holding address information.
    //ZoneEntry(isc::dns::AbstractRRset* nsrrset,
    //       const std::vector<isc::dns::AbstractRRset*>& additional);

    /// \brief Destructor
    virtual ~ZoneEntry()
    {}

    /// \return Name of the zone
    virtual std::string getName() const {
        return name_;
    }

    /// \return Class of zone
    virtual short getClass() const {
        return classCode_;
    }

    /// \return Return Hash Key
    virtual HashKey hashKey() const {
        return HashKey(name_, classCode_);
    }

    // TODO The callbacks must be distinguished - A, AAAA or any of them

    /// \short Add another callback here
    void addCallback(boost::shared_ptr<AddressRequestCallback> callback);
    /// \short Is there at last one callback waiting?
    bool hasCallbacks() const;
    /// \short Remove a callback from queue and return it
    boost::shared_ptr<AddressRequestCallback> popCallback();

    /// \short Nameserver entry pointer
    typedef boost::shared_ptr<NameserverEntry> NameserverPtr;
    /// \short Vector of nameservers
    typedef std::vector<NameserverPtr> NameserverVector;
    /**
     * \name Iterators
     *
     * They iterate over the nameservers.
     */
    //@{
    typedef NameserverVector::iterator iterator;
    typedef NameserverVector::const_iterator const_iterator;
    //@}

    /**
     * \short Add a nameserver pointer to this zone.
     *
     * This does not lock, as it should be called while it is being created.
     * No new nameservers should be added later (it should timeout first and
     * be rebuild). Calling this after addition to the NameserverAddressStore
     * is undefined (it is not thread safe).
     */
    void nameserverAdd(NameserverPtr ns) { nameservers_.push_back(ns); }
    /**
     * \name Iterator access
     *
     * They work similar to usual stl iterator access functions. They iterate
     * over the nameservers.
     *
     * They do not lock, as the nameservers should be read only during
     * the life of the zone.
     */
    //@{
    iterator begin() { return (nameservers_.begin()); }
    iterator end() { return (nameservers_.end()); }
    const_iterator begin() const { return (nameservers_.begin()); }
    const_iterator end() const { return (nameservers_.end()); }
    //@}

    // TODO Get rid of this
    /**
     * \short Lock of the zone entry.
     *
     * Something like a scope lock for the zone entry. It can be copyed (so
     * the result of the getLock() can be assigned to a local variable). The
     * lock is released once all copies of the getLock result are destroyed.
     * However, it is not reentrant (another call to getLock will block).
     *
     * This locks both the zone entry and all nameserver entries in a manner
     * avoiding deadlocks (sorts the nameserver entry pointers before trying to
     * lock them). However, it asumes no one does any other kind of locking
     * of multiple mutices.
     *
     * Copy constructor, assignment operator and destructor are default.
     * The constructor that creates a new lock is private, use getLock()
     * to lock a zone entry.
     *
     * It is an error for the lock to survive destruction of its zone entry.
     */
    class Lock {
        private:
            struct Impl;
            boost::shared_ptr<Impl> impl_;
            Lock(boost::shared_ptr<Impl>);
            friend class ZoneEntry;
    };

    /**
     * \short Acquire a lock.
     *
     * \see Lock
     */
    Lock getLock();
private:
    // TODO Read-Write lock?
    mutable boost::mutex    mutex_;     ///< Mutex protecting this zone entry
    std::string     name_;      ///< Canonical zone name
    uint16_t        classCode_; ///< Class code
    NameserverVector nameservers_; ///< Nameservers
    time_t          expiry_;    ///< Expiry time of this entry
    std::list<boost::shared_ptr<AddressRequestCallback> > callbacks_;
};

} // namespace nsas
} // namespace isc
 
#endif // __ZONE_ENTRY_H
