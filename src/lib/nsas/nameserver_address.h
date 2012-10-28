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

#ifndef NAMESERVER_ADDRESS_H
#define NAMESERVER_ADDRESS_H

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include "asiolink.h"
#include "address_entry.h"
#include "nsas_types.h"

namespace isc {
namespace nsas {

class ZoneEntry;
class NameserverEntry;

/// \brief Empty \c NameserverEntry pointer exception
///
/// Thrown if the the \c NameservrEntry pointer in the \c boost::shared_ptr that passed
/// into \c NameserverAddress' constructor is NULL
class NullNameserverEntryPointer : public isc::Exception {
public:
    NullNameserverEntryPointer(const char* file, size_t line,
        const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// \brief Nameserver Address
///
/// This class implements the object that returned from NSAS when the resolver
/// request an address for the name server. It contains one address
/// that can be used by resolver. When the resolver get query back from the name
/// server, it should update the name server's RTT(Round Trip Time) with this
/// object.
///
/// It is not thread safe, only reentrant. It is expected to be kept inside
/// the resolver and used only once for the address and once for the update.

class NameserverAddress {
public:
    /// \brief Constructor
    ///
    /// The NameserverAddress object will contain one shared_ptr object that
    /// pointed to NameserverEntry which contains the address as well as it's
    /// corresponding index. The user can update it's RTT with the index later.
    ///
    /// \param nameserver A shared_ptr that points to a NameserverEntry object
    /// the shared_ptr can avoid the NameserverEntry object being dropped while the
    /// request is processing.
    /// \param address The address's index in NameserverEntry's addresses vector
    /// \param family Address family, V4_ONLY or V6_ONLY
    NameserverAddress(const boost::shared_ptr<NameserverEntry>& nameserver,
        const AddressEntry& address, AddressFamily family):
        ns_(nameserver), address_(address), family_(family)
    {
        if(!ns_) {
            isc_throw(NullNameserverEntryPointer, "NULL NameserverEntry pointer.");
        }
    }

    /// \brief Default Constructor
    NameserverAddress() : address_(asiolink::IOAddress("::1")) { }

    /// \brief Return address
    ///
    asiolink::IOAddress getAddress() const {
        return (address_.getAddress());
    }

    /// \brief Update Round-trip Time
    ///
    /// When the user get one request back from the name server, it should
    /// update the address's RTT.
    /// \param rtt The new Round-Trip Time
    void updateRTT(uint32_t rtt) const;

    /// Short access to the AddressEntry inside.
    //@{
    const AddressEntry& getAddressEntry() const {
        return (address_);
    }
    AddressEntry& getAddressEntry() {
        return (address_);
    }
    //@}
private:

    /*
     * Note: Previous implementation used index into the entry. That is wrong,
     * as the list of addresses may change. Thil would cause setting a
     * different address or a crash.
     */
    boost::shared_ptr<NameserverEntry> ns_;  ///< Shared-pointer to NameserverEntry object
    AddressEntry address_;            ///< The address
    AddressFamily family_;                   ///< The address family (V4_ONLY or V6_ONLY)
};

} // namespace nsas
} // namespace isc

#endif//NAMESERVER_ADDRESS_H
