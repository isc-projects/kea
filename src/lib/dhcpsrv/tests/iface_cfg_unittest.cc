// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/iface_cfg.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for testing the @c IfaceCfg class.
class IfaceCfgTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// By initializing the @c IfaceMgrTestConfig object it creates a set of
    /// fake interfaces: lo, eth0, eth1.
    IfaceCfgTest() :
        iface_mgr_test_config_(true) {
    }

    /// @brief Holds a fake configuration of the interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

TEST_F(IfaceCfgTest, explicitNames) {
    IfaceCfg cfg;
    ASSERT_NO_THROW(cfg.use("eth0"));
    ASSERT_NO_THROW(cfg.use("eth1"));
}

} // end of anonymous namespace
