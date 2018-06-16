// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_handle.h>
#include <hooks/callout_handle_associate.h>
#include <gtest/gtest.h>

using namespace isc::hooks;

namespace {

// This test verifies that the callout handle can be created and
// retrieved from the CalloutHandleAssociate.
TEST(CalloutHandleAssociate, getCalloutHandle) {
    CalloutHandleAssociate associate;
    // The handle should be initialized and returned.
    CalloutHandlePtr callout_handle = associate.getCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // When calling the second time, the same handle should be returned.
    CalloutHandlePtr callout_handle2 = associate.getCalloutHandle();
    EXPECT_TRUE(callout_handle == callout_handle2);

    // A different associate should produce a different handle.
    CalloutHandleAssociate associate2;
    callout_handle2 = associate2.getCalloutHandle();
    EXPECT_FALSE(callout_handle == callout_handle2);
}

} // end of anonymous namespace
