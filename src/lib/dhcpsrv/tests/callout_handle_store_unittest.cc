// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
    EXPECT_EQ(1, pktptr_1.use_count());
    EXPECT_EQ(1, pktptr_2.use_count());

    // Get the CalloutHandle for the first packet.
    CalloutHandlePtr chptr_1 = getCalloutHandle(pktptr_1);
    ASSERT_TRUE(chptr_1);

    // Reference counts on both the callout handle and the packet should have
    // been incremented because of the stored data.  The reference count on the
    // other Pkt4 object should not have changed.
    EXPECT_EQ(2, chptr_1.use_count());
    EXPECT_EQ(2, pktptr_1.use_count());
    EXPECT_EQ(1, pktptr_2.use_count());

    // Try getting another pointer for the same packet.  Use a different
    // pointer object to check that the function returns a handle based on the
    // pointed-to data and not the pointer.  (Clear the temporary pointer after
    // use to avoid complicating reference counts.)
    Pkt4Ptr pktptr_temp = pktptr_1;
    CalloutHandlePtr chptr_2 = getCalloutHandle(pktptr_temp);
    pktptr_temp.reset();

    ASSERT_TRUE(chptr_2);
    EXPECT_TRUE(chptr_1 == chptr_2);

    // Reference count is now 3 on the callout handle - two for pointers here,
    // one for the static pointer in the function.  The count is 2 for the]
    // object pointed to by pktptr_1 - one for that pointer and one for the
    // pointer in the function.
    EXPECT_EQ(3, chptr_1.use_count());
    EXPECT_EQ(3, chptr_2.use_count());
    EXPECT_EQ(2, pktptr_1.use_count());
    EXPECT_EQ(1, pktptr_2.use_count());

    // Now ask for a CalloutHandle for a different object.  This should return
    // a different CalloutHandle.
    chptr_2 = getCalloutHandle(pktptr_2);
    EXPECT_FALSE(chptr_1 == chptr_2);

    // Check reference counts.  The getCalloutHandle function should be storing
    // pointers to the objects poiunted to by chptr_2 and pktptr_2.
    EXPECT_EQ(1, chptr_1.use_count());
    EXPECT_EQ(1, pktptr_1.use_count());
    EXPECT_EQ(2, chptr_2.use_count());
    EXPECT_EQ(2, pktptr_2.use_count());

    // Now try clearing the stored pointers.
    Pkt4Ptr pktptr_empty;
    ASSERT_FALSE(pktptr_empty);

    CalloutHandlePtr chptr_empty = getCalloutHandle(pktptr_empty);
    EXPECT_FALSE(chptr_empty);

    // Reference counts should be back to 1 for the CalloutHandles and the
    // Packet pointers.
    EXPECT_EQ(1, chptr_1.use_count());
    EXPECT_EQ(1, pktptr_1.use_count());
    EXPECT_EQ(1, chptr_2.use_count());
    EXPECT_EQ(1, pktptr_2.use_count());
}

// The followings is a trival test to check that if the template function
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
