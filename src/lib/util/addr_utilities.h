// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>

namespace isc {
namespace util {

/// This code is based on similar code from the Dibbler project. I, Tomasz Mrugalski,
/// as a sole creater of that code hereby release it under BSD license for the benefit
/// of the BIND10 project.

/// @brief returns a first address in a given prefix
///
/// Example: For 2001:db8:1::deaf:beef and length /120 the function will return
/// 2001:db8:1::dead:bee0. See also @ref lastAddrInPrefix.
///
/// @param prefix and address that belongs to a prefix
/// @param len prefix length
///
/// @return first address from a prefix
isc::asiolink::IOAddress firstAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                           uint8_t len);

/// @brief returns a last address in a given prefix
///
/// Example: For 2001:db8:1::deaf:beef and length /112 the function will return
/// 2001:db8:1::dead:ffff. See also @ref firstAddrInPrefix.
///
/// @param prefix and address that belongs to a prefix
/// @param len prefix length
///
/// @return first address from a prefix
isc::asiolink::IOAddress lastAddrInPrefix(const isc::asiolink::IOAddress& prefix,
                                          uint8_t len);

};
};
