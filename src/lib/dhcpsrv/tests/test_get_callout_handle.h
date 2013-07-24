// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef TEST_GET_CALLOUT_HANDLE_H
#define TEST_GET_CALLOUT_HANDLE_H

#include <dhcp/pkt6.h>
#include <hooks/callout_handle.h>

namespace isc {
namespace dhcp {
namespace test {

/// @file
/// @brief Get Callout Handle
///
/// This function is a shall around getCalloutHandle.  It's purpose is to
/// ensure that the getCalloutHandle() template function is referred to by
/// two separate compilation units, and so test that data stored in one unit
/// can be accessed by another. (This should be the case, but some compilers
/// mabe be odd when it comes to template instantiation.)
///
/// @param pktptr Pointer to a Pkt6 object.
///
/// @return CalloutHandlePtr pointing to CalloutHandle associated with the
///         Pkt6 object.
isc::hooks::CalloutHandlePtr
testGetCalloutHandle(const Pkt6Ptr& pktptr);

} // namespace test
} // namespace dhcp
} // namespace isc


#endif // TEST_GET_CALLOUT_HANDLE_H
