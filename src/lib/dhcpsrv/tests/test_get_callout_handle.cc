// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/callout_handle_store.h>
#include "test_get_callout_handle.h"

// Just instantiate the getCalloutHandle function and call it.

namespace isc {
namespace dhcp {
namespace test {

isc::hooks::CalloutHandlePtr
testGetCalloutHandle(const Pkt6Ptr& pktptr) {
    return (isc::dhcp::getCalloutHandle(pktptr));
}

} // namespace test
} // namespace dhcp
} // namespace isc
