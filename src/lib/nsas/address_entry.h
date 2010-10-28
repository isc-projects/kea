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

#ifndef __ADDRESS_ENTRY_H
#define __ADDRESS_ENTRY_H

/// \brief Address Entry
///
/// Lightweight class that couples an address with a RTT and provides some
/// convenience methods for accessing and updating the information.

#include <stdint.h>
#include "asiolink.h"

namespace isc {
namespace nsas {

class AddressEntry {
public:
    /// Creates an address entry given IOAddress entry and RTT
    /// This is the only constructor; the default copy constructor and
    /// assignment operator are valid for this object.
    ///
    /// \param address Address object representing this address
    /// \param rtt Initial round-trip time
    AddressEntry(const asiolink::IOAddress& address, uint32_t rtt = 0) :
        address_(address), rtt_(rtt)
    {}

    /// \return Address object
    asiolink::IOAddress getAddress() const {
        return address_;
    }

    /// \return Current round-trip time
    uint32_t getRTT() const {
        return rtt_;
    }

    /// Set current RTT
    ///
    /// \param rtt New RTT to be associated with this address
    void setRTT(uint32_t rtt) {
        rtt_ = rtt;     // TODO: Modify to use weighting formula
    }

    /// Mark address as unreachable.
    void setUnreachable() {
        setRTT(UNREACHABLE);   // Largest long number is code for unreachable
    }

    /// Check if address is unreachable
    ///
    /// \return true if the address is unreachable, false if not
    bool isUnreachable() const {
        return (rtt_ == UNREACHABLE);
    }

    /// \return true if the object is a V4 address
    bool isV4() const {
        return (address_.getFamily() == AF_INET);
    }

    /// \return true if the object is a V6 address
    bool isV6() const {
        return (address_.getFamily() == AF_INET6);
    }

    // Next element is defined public for testing
    static const uint32_t UNREACHABLE;  ///< RTT indicating unreachable address

private:
    asiolink::IOAddress address_;       ///< Address
    uint32_t        rtt_;               ///< Round-trip time
};

}   // namespace dns
}   // namespace isc


#endif // __ADDRESS_ENTRY_H
