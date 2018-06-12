// Copyright (C) 2012-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/callout_handle_store.h>
#include "test_get_callout_handle.h"

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::hooks;

namespace {

TEST(CalloutHandleStoreTest, StoreRetrieve) {

    // Create two DHCP4 packets during tests.  The constructor arguments are
    // arbitrary.
    Pkt4Ptr pktptr_1(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr pktptr_2(new Pkt4(DHCPDISCOVER, 5678));

    // Check that the pointers point to objects that are different, and that
    // the pointers are the only pointers pointing to the packets.
    ASSERT_TRUE(pktptr_1);
    ASSERT_TRUE(pktptr_2);

    ASSERT_TRUE(pktptr_1 != pktptr_2);

    // Get the CalloutHandle for the first packet.
    CalloutHandlePtr chptr_1 = getCalloutHandle(pktptr_1);
    ASSERT_TRUE(chptr_1);

    // Try getting another pointer for the same packet.  Use a different
    // pointer object to check that the function returns a handle based on the
    // pointed-to data and not the pointer.
    Pkt4Ptr pktptr_temp = pktptr_1;
    CalloutHandlePtr chptr_2 = getCalloutHandle(pktptr_temp);
    pktptr_temp.reset();

    ASSERT_TRUE(chptr_2);
    EXPECT_TRUE(chptr_1 == chptr_2);

    // Now ask for a CalloutHandle for a different object.  This should return
    // a different CalloutHandle.
    chptr_2 = getCalloutHandle(pktptr_2);
    EXPECT_FALSE(chptr_1 == chptr_2);
}

// The followings is a trivial test to check that if the template function
// is referred to in a separate compilation unit, only one copy of the static
// objects stored in it are returned.  (For a change, we'll use a Pkt6 as the
// packet object.)

TEST(CalloutHandleStoreTest, SeparateCompilationUnit) {

    // Access the template function here.
    Pkt6Ptr pktptr_1(new Pkt6(DHCPV6_ADVERTISE, 4321));
    CalloutHandlePtr chptr_1 = getCalloutHandle(pktptr_1);
    ASSERT_TRUE(chptr_1);

    // Access it from within another compilation unit.
    CalloutHandlePtr chptr_2 = isc::dhcp::test::testGetCalloutHandle(pktptr_1);
    EXPECT_TRUE(chptr_1 == chptr_2);
}

} // Anonymous namespace
