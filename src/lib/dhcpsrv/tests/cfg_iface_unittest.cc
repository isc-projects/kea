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

    /// @brief Checks if socket is opened on the specified interface and bound
    /// to a specific IPv4 address.
    ///
    /// @param iface_name Interface name.
    /// @param address Address that the socket should be bound to.
    bool socketOpen(const std::string& iface_name,
                    const std::string& address) const;

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
CfgIfaceTest::socketOpen(const std::string& iface_name,
                         const std::string& address) const {
    return (iface_mgr_test_config_.socketOpen(iface_name, address));
}



bool
CfgIfaceTest::unicastOpen(const std::string& iface_name) const {
    return (iface_mgr_test_config_.unicastOpen(iface_name));
}

// This test checks that the interface names can be explicitly selected
// by their names and IPv4 sockets are opened on these interfaces.
TEST_F(CfgIfaceTest, explicitNamesV4) {
    CfgIface cfg;
    // Specify valid interface names. There should be no error.
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth0"));
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1"));

    // Open sockets on specified interfaces.
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

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
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1"));

    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

    // Socket should be open on eth1 only.
    EXPECT_FALSE(socketOpen("eth0", AF_INET));
    EXPECT_TRUE(socketOpen("eth1", AF_INET));
    EXPECT_FALSE(socketOpen("lo", AF_INET));
}

// This test checks that it is possible to specify an interface and address
// on this interface to which the socket should be bound. The sockets should
// not be opened on other addresses on this interface.
TEST_F(CfgIfaceTest, explicitNamesAndAddressesV4) {
    CfgIface cfg;
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth0/10.0.0.1"));
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1/192.0.2.3"));
    ASSERT_THROW(cfg.use(AF_INET, "eth1/192.0.2.5"), DuplicateIfaceName);

    // Open sockets on specified interfaces and addresses.
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

    EXPECT_TRUE(socketOpen("eth0", "10.0.0.1"));
    EXPECT_TRUE(socketOpen("eth1", "192.0.2.3"));
    EXPECT_FALSE(socketOpen("eth1", "192.0.2.5"));

    // Close all sockets and make sure they are really closed.
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("eth0", "10.0.0.1"));
    ASSERT_FALSE(socketOpen("eth1", "192.0.2.3"));
    ASSERT_FALSE(socketOpen("eth1", "192.0.2.5"));

    // Reset configuration.
    cfg.reset();

    // Now check that the socket can be bound to a different address on
    // eth1.
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1/192.0.2.5"));
    ASSERT_THROW(cfg.use(AF_INET, "eth1/192.0.2.3"), DuplicateIfaceName);

    // Open sockets according to the new configuration.
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

    EXPECT_FALSE(socketOpen("eth0", "10.0.0.1"));
    EXPECT_FALSE(socketOpen("eth1", "192.0.2.3"));
    EXPECT_TRUE(socketOpen("eth1", "192.0.2.5"));
}

// This test checks that the invalid interface name and/or IPv4 address
// results in error.
TEST_F(CfgIfaceTest, explicitNamesAndAddressesInvalidV4) {
    CfgIface cfg;
    // An address not assigned to the interface.
    EXPECT_THROW(cfg.use(AF_INET, "eth0/10.0.0.2"), NoSuchAddress);
    // IPv6 address.
    EXPECT_THROW(cfg.use(AF_INET, "eth0/2001:db8:1::1"), InvalidIfaceName);
    // Wildcard interface name with an address.
    EXPECT_THROW(cfg.use(AF_INET, "*/10.0.0.1"), InvalidIfaceName);

    // Duplicated interface.
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1"));
    EXPECT_THROW(cfg.use(AF_INET, "eth1/192.0.2.3"), DuplicateIfaceName);
}

// This test checks that the interface names can be explicitly selected
// by their names and IPv6 sockets are opened on these interfaces.
TEST_F(CfgIfaceTest, explicitNamesV6) {
    CfgIface cfg;
    // Specify valid interface names. There should be no error.
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth0"));
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth1"));

    // Open sockets on specified interfaces.
    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);

    // Sockets should be now open on eth0 and eth1, but not on loopback.
    EXPECT_TRUE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));

    // No IPv4 sockets should be present because we wanted IPv6 sockets.
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
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth1"));

    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);

    // Socket should be open on eth1 only.
    EXPECT_FALSE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(socketOpen("eth1", AF_INET6));
    EXPECT_FALSE(socketOpen("lo", AF_INET6));

}

// This test checks that the wildcard interface name can be specified to
// select all interfaces to open IPv4 sockets.
TEST_F(CfgIfaceTest, wildcardV4) {
    CfgIface cfg;
    ASSERT_NO_THROW(cfg.use(AF_INET, "*"));

    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

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
    CfgIface cfg;
    ASSERT_NO_THROW(cfg.use(AF_INET6, "*"));

    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);

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
    CfgIface cfg;

    // One socket will be opened on link-local address, one on unicast but
    // on the same interface.
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth0"));
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth0/2001:db8:1::1"));

    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);

    EXPECT_TRUE(socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(unicastOpen("eth0"));
}

// Test that when invalid interface names are specified an exception is thrown.
TEST_F(CfgIfaceTest, invalidValues) {
    CfgIface cfg;
    ASSERT_THROW(cfg.use(AF_INET, ""), InvalidIfaceName);
    ASSERT_THROW(cfg.use(AF_INET, " "), InvalidIfaceName);
    ASSERT_THROW(cfg.use(AF_INET, "bogus"), NoSuchIface);

    ASSERT_NO_THROW(cfg.use(AF_INET, "eth0"));
    ASSERT_THROW(cfg.use(AF_INET, "eth0"), DuplicateIfaceName);

    ASSERT_THROW(cfg.use(AF_INET, "eth0/2001:db8:1::1"), InvalidIfaceName);

    ASSERT_THROW(cfg.use(AF_INET6, "eth0/"), InvalidIfaceName);
    ASSERT_THROW(cfg.use(AF_INET6, "/2001:db8:1::1"), InvalidIfaceName);
    ASSERT_THROW(cfg.use(AF_INET6, "*/2001:db8:1::1"), InvalidIfaceName);
    ASSERT_THROW(cfg.use(AF_INET6, "bogus/2001:db8:1::1"), NoSuchIface);
    ASSERT_THROW(cfg.use(AF_INET6, "eth0/2001:db8:1::2"), NoSuchAddress);
    ASSERT_NO_THROW(cfg.use(AF_INET6, "*"));
    ASSERT_THROW(cfg.use(AF_INET6, "*"), DuplicateIfaceName);
}

// Test that the equality and inequality operators work fine for CfgIface.
TEST_F(CfgIfaceTest, equality) {
    CfgIface cfg1;
    CfgIface cfg2;

    // Initially objects must be equal.
    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);

    // Differ by one interface.
    cfg1.use(AF_INET, "eth0");
    EXPECT_FALSE(cfg1 == cfg2);
    EXPECT_TRUE(cfg1 != cfg2);

    // Now interfaces should be equal.
    cfg2.use(AF_INET, "eth0");
    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);

    // Differ by unicast address.
    cfg1.use(AF_INET6, "eth0/2001:db8:1::1");
    EXPECT_FALSE(cfg1 == cfg2);
    EXPECT_TRUE(cfg1 != cfg2);

    // Differ by unicast address and one interface.
    cfg2.use(AF_INET6, "eth1");
    EXPECT_FALSE(cfg1 == cfg2);
    EXPECT_TRUE(cfg1 != cfg2);

    // Now, the unicast addresses are equal but still differ by one interface.
    cfg2.use(AF_INET6, "eth0/2001:db8:1::1");
    EXPECT_FALSE(cfg1 == cfg2);
    EXPECT_TRUE(cfg1 != cfg2);

    // They should be now back to equal.
    cfg1.use(AF_INET6, "eth1");
    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);

    // Even though the wildcard doesn't change anything because all interfaces
    // are already in use, the fact that the wildcard is specified should
    // cause them to be not equal.
    cfg1.use(AF_INET6, "*");
    EXPECT_FALSE(cfg1 == cfg2);
    EXPECT_TRUE(cfg1 != cfg2);

    // Finally, both are equal as they use wildacard.
    cfg2.use(AF_INET, "*");
    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);
}

} // end of anonymous namespace
