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

#ifndef __NSAS_TYPES_H
#define __NSAS_TYPES_H

/// \file nsas_types.h
/// \brief Nameserver Address Store Types
///
/// Defines a set of types used within the Network Address Store.

namespace isc {
namespace nsas {

/// \brief Address requested
enum AddressRequest {
    /// \short Interested only in IPv4 address
    V4_ONLY,
    /// \short Interested only in IPv6 address
    V6_ONLY,
    /// \short Any address is good
    ANY_OK
};

}
}

#endif // __NSAS_TYPES_H
