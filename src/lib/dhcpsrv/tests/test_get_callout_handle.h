// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
