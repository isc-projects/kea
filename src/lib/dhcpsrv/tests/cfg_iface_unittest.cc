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
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfg_iface.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for testing the @c CfgIface class.
class CfgIfaceTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// By initializing the @c IfaceMgrTestConfig object it creates a set of
    /// fake interfaces: lo, eth0, eth1.
    CfgIfaceTest() :
        iface_mgr_test_config_(true) {
    }

    /// @brief Checks if socket of the specified family is opened on interface.
    ///
    /// @param iface_name Interface name.
    /// @param family One of: AF_INET or AF_INET6
    bool socketOpen(const std::string& iface_name, const int family) const;

    /// @brief Checks if unicast socket is opened on interface.
    ///
    /// @param iface_name Interface name.
    bool unicastOpen(const std::string& iface_name) const;

    /// @brief Holds a fake configuration of the interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

bool
CfgIfaceTest::socketOpen(const std::string& iface_name,
                         const int family) const {
    return (iface_mgr_test_config_.socketOpen(iface_name, family));
}
bool
CfgIfaceTest::unicastOpen(const std::string& iface_name) const {
    return (iface_mgr_test_config_.unicastOpen(iface_name));
}

// This test checks that the interface names can be explicitly selected
// by their names and IPv4 sockets are opened on these interfaces.
TEST_F(CfgIfaceTest, explicitNamesV4) {
    CfgIface cfg(CfgIface::V4);
    // Specify valid interface names. There should be no error.
    ASSERT_NO_THROW(cfg.use("eth0"));
    ASSERT_NO_THROW(cfg.use("eth1"));

    // Open sockets on specified interfaces.
    cfg.openSockets(DHCP4_SERVER_PORT);

    // Sockets should be now open on eth0 and eth1, but not on loopback.
    EXPECT_TRUE(socketOpen("eth0", AF_INET));
    EXPECT_TRUE(socketOpen("eth1", AF_INET));
    EXPECT_FALSE(socketOpen("lo", AF_INET));

    // No IPv6 sockets should be present because we wanted IPv4 sockets.
    EXPECT_FALSE(socketOpen("eth0", AF_INET6));
    EXPECT_FALSE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));

    // Close all sockets and make sure they are really closed.
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("eth0", AF_INET));
    ASSERT_FALSE(socketOpen("eth1", AF_INET));
    ASSERT_FALSE(socketOpen("lo", AF_INET));

    // Reset configuration and select only one interface this time.
    cfg.reset();
    ASSERT_NO_THROW(cfg.use("eth1"));

    cfg.openSockets(DHCP4_SERVER_PORT);

    // Socket should be open on eth1 only.
    EXPECT_FALSE(socketOpen("eth0", AF_INET));
    EXPECT_TRUE(socketOpen("eth1", AF_INET));
    EXPECT_FALSE(socketOpen("lo", AF_INET));

}

// This test checks that the interface names can be explicitly selected
// by their names and IPv6 sockets are opened on these interfaces.
TEST_F(CfgIfaceTest, explicitNamesV6) {
    CfgIface cfg(CfgIface::V6);
    // Specify valid interface names. There should be no error.
    ASSERT_NO_THROW(cfg.use("eth0"));
    ASSERT_NO_THROW(cfg.use("eth1"));

    // Open sockets on specified interfaces.
    cfg.openSockets(DHCP6_SERVER_PORT);

    // Sockets should be now open on eth0 and eth1, but not on loopback.
    EXPECT_TRUE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));

    // No IPv4 sockets should be present because we wanted IPv4 sockets.
    EXPECT_FALSE(socketOpen("eth0", AF_INET));
    EXPECT_FALSE(socketOpen("eth1", AF_INET));
    EXPECT_FALSE(socketOpen("lo", AF_INET));

    // Close all sockets and make sure they are really closed.
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("eth0", AF_INET6));
    ASSERT_FALSE(socketOpen("eth1", AF_INET6));
    ASSERT_FALSE(socketOpen("lo", AF_INET6));

    // Reset configuration and select only one interface this time.
    cfg.reset();
    ASSERT_NO_THROW(cfg.use("eth1"));

    cfg.openSockets(DHCP6_SERVER_PORT);

    // Socket should be open on eth1 only.
    EXPECT_FALSE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));

}

// This test checks that the wildcard interface name can be specified to
// select all interfaces to open IPv4 sockets.
TEST_F(CfgIfaceTest, wildcardV4) {
    CfgIface cfg(CfgIface::V4);
    ASSERT_NO_THROW(cfg.use(CfgIface::ALL_IFACES_KEYWORD));

    cfg.openSockets(DHCP4_SERVER_PORT);

    // Sockets should be now open on eth0 and eth1, but not on loopback.
    EXPECT_TRUE(socketOpen("eth0", AF_INET));
    EXPECT_TRUE(socketOpen("eth1", AF_INET));
    EXPECT_FALSE(socketOpen("lo", AF_INET));

    // No IPv6 sockets should be present because we wanted IPv4 sockets.
    EXPECT_FALSE(socketOpen("eth0", AF_INET6));
    EXPECT_FALSE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));
}

// This test checks that the wildcard interface name can be specified to
// select all interfaces to open IPv6 sockets.
TEST_F(CfgIfaceTest, wildcardV6) {
    CfgIface cfg(CfgIface::V6);
    ASSERT_NO_THROW(cfg.use(CfgIface::ALL_IFACES_KEYWORD));

    cfg.openSockets(DHCP4_SERVER_PORT);

    // Sockets should be now open on eth0 and eth1, but not on loopback.
    EXPECT_TRUE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));

    // No IPv6 sockets should be present because we wanted IPv6 sockets.
    EXPECT_FALSE(socketOpen("eth0", AF_INET));
    EXPECT_FALSE(socketOpen("eth1", AF_INET));
    EXPECT_FALSE(socketOpen("lo", AF_INET));
}

// Test that unicast address can be specified for the socket to be opened on
// the interface on which the socket bound to link local address is also
// opened.
TEST_F(CfgIfaceTest, validUnicast) {
    CfgIface cfg(CfgIface::V6);

    // One socket will be opened on link-local address, one on unicast but
    // on the same interface.
    ASSERT_NO_THROW(cfg.use("eth0"));
    ASSERT_NO_THROW(cfg.use("eth0/2001:db8:1::1"));

    cfg.openSockets(DHCP6_SERVER_PORT);

    EXPECT_TRUE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(unicastOpen("eth0"));
}

// Test that when invalid interface names are specified an exception is thrown.
TEST_F(CfgIfaceTest, invalidValues) {
    CfgIface cfg(CfgIface::V4);
    ASSERT_THROW(cfg.use(""), InvalidIfaceName);
    ASSERT_THROW(cfg.use(" "), InvalidIfaceName);
    ASSERT_THROW(cfg.use("bogus"), NoSuchIface);

    ASSERT_NO_THROW(cfg.use("eth0"));
    ASSERT_THROW(cfg.use("eth0"), DuplicateIfaceName);

    ASSERT_THROW(cfg.use("eth0/2001:db8:1::1"), InvalidIfaceName);

    cfg.setFamily(CfgIface::V6);

    ASSERT_THROW(cfg.use("eth0/"), InvalidIfaceName);
    ASSERT_THROW(cfg.use("/2001:db8:1::1"), InvalidIfaceName);
    ASSERT_THROW(cfg.use("*/2001:db8:1::1"), InvalidIfaceName);
    ASSERT_THROW(cfg.use("bogus/2001:db8:1::1"), NoSuchIface);
    ASSERT_THROW(cfg.use("eth0/fe80::3a60:77ff:fed5:cdef"), InvalidIfaceName);
    ASSERT_THROW(cfg.use("eth0/fe80::3a60:77ff:fed5:cdef"), InvalidIfaceName);
    ASSERT_THROW(cfg.use("eth0/2001:db8:1::2"), NoSuchAddress);

    ASSERT_NO_THROW(cfg.use(CfgIface::ALL_IFACES_KEYWORD));
    ASSERT_THROW(cfg.use(CfgIface::ALL_IFACES_KEYWORD), DuplicateIfaceName);
}

} // end of anonymous namespace
