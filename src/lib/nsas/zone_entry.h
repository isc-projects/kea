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

    // TODO Constructor from namesarver table and referral information

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

    /**
     * \short Put another callback inside.
     *
     * This callback is either executed right away, if it is possible,
     * or queued for later.
     * \param callback The callback itself.
     * \param v4ok Is it ok to give the callback a IPv4 address?
     * \param v6ok Is it ok to give the callback a IPv6 address? (At last one
     *     of them must be true or isc::BadValue is thrown)
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
        callback, bool v4ok, bool v6ok, boost::shared_ptr<ZoneEntry> self);

private:
    // TODO Read-Write lock?
    mutable boost::mutex    mutex_;     ///< Mutex protecting this zone entry
    std::string     name_;      ///< Canonical zone name
    uint16_t        classCode_; ///< Class code
    typedef boost::shared_ptr<NameserverEntry> NameserverPtr;
    typedef std::vector<NameserverPtr> NameserverVector;
    NameserverVector nameservers_; ///< Nameservers
    time_t          expiry_;    ///< Expiry time of this entry
    std::list<boost::shared_ptr<AddressRequestCallback> > callbacks_;
    // Internal function that adds a callback (if there's one) and processes
    // the nameservers (if there's chance there's some info) and calls
    // callbacks. If nameserver is given, it is considered new and valid
    // even if its TTL is 0.
    void process(boost::shared_ptr<AddressRequestCallback> callback,
         bool v4ok, bool v6ok, NameserverEntry* nameserver);
};

} // namespace nsas
} // namespace isc
 
#endif // __ZONE_ENTRY_H
