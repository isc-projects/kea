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

#ifndef ADDRESS_REQUEST_CALLBACK_H
#define ADDRESS_REQUEST_CALLBACK_H

#include "asiolink.h"
#include "nameserver_address.h"

namespace isc {
namespace nsas {

/// \brief Callback When Address Obtained
///
/// This is the callback object used to return an address of a nameserver to a
/// caller.  It (or a subclass of it) is passed to the NSAS when a request is
/// made for the address of a nameserver.  When an address is available,
/// methods on the passed objects are called.
///
/// Note that there is no guarantee as to when the methods are called; they
/// could be called after the function call that made the address request has
/// returned the caller.  Equally, the call could complete before that function
/// call returns.  It is up to the caller to handle all cases.
///
/// In terms of use, a shared pointer to this object is passed to the NSAS.
/// The NSAS will store the object via a shared pointer and after the callback
/// will delete the pointer.  Whether this results in the deletion of the
/// callback object is up to the caller - if the caller wants to retain it
/// they should keep the shared pointer.

class AddressRequestCallback {
public:

    /// Default constructor, copy contructor and assignment operator
    /// are implicitly present and are OK.

    /// \brief Virtual Destructor
    virtual ~AddressRequestCallback()
    {}

    /// \brief Success Callback
    ///
    /// This method is used when an address has been retrieved for the request.
    ///
    /// \param address Address to be used to access the nameserver.
    virtual void success(const NameserverAddress& address) = 0;

    /// \brief Unreachable
    ///
    /// This method is called when a request is made for an address, but all
    /// the addresses for the zone are marked as unreachable.  This may be
    /// due to the NS records being unobtainable, or the A records for known
    /// nameservers being unobtainable.
    virtual void unreachable() = 0;

};

} // namespace nsas
} // namespace isc

#endif // ADDRESS_REQUEST_CALLBACK_H
