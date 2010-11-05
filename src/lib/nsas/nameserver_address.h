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

#ifndef __NAMESERVER_ADDRESS_H
#define __NAMESERVER_ADDRESS_H

#include <boost/shared_ptr.hpp>

#include "asiolink.h"
#include "nameserver_entry.h"

namespace isc {
namespace nsas {

/// \brief Nameserver Address
///
/// This class implements the object that returned from NSAS when the resolver
/// request an address for the name server. It contains one IOAddress object
/// that can be used by resolver. When the resolver get query back from the name
/// server, it should update the name server's RTT(Round Trip Time) with this 
/// object.

class NameserverAddress {
public:
    /// \brief Constructor
    ///
    /// The NameserverAddress object will contain one shared_ptr object that
    /// pointed to NameserverEntry which contains the address as well as it's 
    /// corresponding index. The user can update it's RTT with the index later.
    ///
    /// \param namerserver A shared_ptr that points to a NameserverEntry object
    /// the shared_ptr can avoid the NameserverEntry object being dropped while the
    /// request is processing.
    /// \param index The address's index in NameserverEntry's addresses vector
    NameserverAddress(boost::shared_ptr<NameserverEntry>& nameserver, uint32_t index):
        ns_(nameserver), index_(index)
    {
    }

    /// \brief Destructor
    ///
    /// Empty destructor.
    ~NameserverAddress()
    {}

    /// \brief Return address
    ///
    asiolink::IOAddress getAddress() const { 
        NameserverEntry *ne = ns_.get();
        assert(ne != NULL);
        return ne->getAddressAtIndex(index_); 
    }

    /// \brief Update Round-trip Time
    ///
    /// When the user get one request back from the name server, it should
    /// update the address's RTT.
    /// \param rtt The new Round-Trip Time
    void updateRTT(uint32_t rtt) { 
        NameserverEntry* ne = ns_.get();
        if(ne) ne->updateAddressRTTAtIndex(rtt, index_); 
    }
private:
    /// \brief Default Constructor
    ///
    /// A private default constructor to avoid creating an empty object.
    NameserverAddress();

    boost::shared_ptr<NameserverEntry> ns_;  ///< Shared-pointer to NameserverEntry object
    uint32_t index_;                         ///< The address index in NameserverEntry
};

} // namespace nsas
} // namespace isc

#endif//__NAMESERVER_ADDRESS_H
