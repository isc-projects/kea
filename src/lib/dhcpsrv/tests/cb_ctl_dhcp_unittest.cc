// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <gtest/gtest.h>

using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c CBControlDHCPv4 unit tests.
class TestCBControlDHCPv4 : public CBControlDHCPv4 {
public:

    using CBControlDHCPv4::databaseConfigApply;
};


// This test verifies that the configuration updates are
// merged into the current configuration.
TEST(CBControlDHCPv4Test, databaseConfigApplyUpdates) {
    TestCBControlDHCPv4 ctl;
    /// @todo implement the actual test.
}


}
