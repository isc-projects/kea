// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfg_iface.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;
using namespace isc::data;

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

// This test checks that it is possible to explicitly select multiple
// IPv4 addresses on a single interface.
TEST_F(CfgIfaceTest, multipleAddressesSameInterfaceV4) {
    CfgIface cfg;
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1/192.0.2.3"));
    // Cannot add the same address twice.
    ASSERT_THROW(cfg.use(AF_INET, "eth1/192.0.2.3"), DuplicateAddress);
    // Can add another address on this interface.
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth1/192.0.2.5"));
    // Can't select the whole interface.
    ASSERT_THROW(cfg.use(AF_INET, "eth1"), DuplicateIfaceName);

    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

    EXPECT_FALSE(socketOpen("eth0", "10.0.0.1"));
    EXPECT_TRUE(socketOpen("eth1", "192.0.2.3"));
    EXPECT_TRUE(socketOpen("eth1", "192.0.2.5"));
}

// This test checks that it is possible to specify the loopback interface.
TEST_F(CfgIfaceTest, explicitLoopbackV4) {
    CfgIface cfg;
    ASSERT_NO_THROW(cfg.use(AF_INET, "lo"));

    // Use UDP sockets
    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, CfgIface::SOCKET_UDP));

    // Open sockets on specified interfaces and addresses.
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);

    EXPECT_TRUE(socketOpen("lo", "127.0.0.1"));

    // Close all sockets and make sure they are really closed.
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("lo", "127.0.0.1"));

    // Reset configuration.
    cfg.reset();

    // Retry with wirdcard
    ASSERT_NO_THROW(cfg.use(AF_INET, "*"));
    ASSERT_NO_THROW(cfg.use(AF_INET, "lo"));
    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, CfgIface::SOCKET_UDP));
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);
    // It is now allowed to use loopback, even with wildcard.
    EXPECT_TRUE(socketOpen("lo", "127.0.0.1"));
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("lo", "127.0.0.1"));

    // Retry without UDP sockets (lo can be only used with udp sockets)
    cfg.reset();
    ASSERT_NO_THROW(cfg.use(AF_INET, "lo"));
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);
    // No loopback socket
    EXPECT_FALSE(socketOpen("lo", "127.0.0.1"));

    // Retry with a second interface
    cfg.reset();
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth0"));
    ASSERT_NO_THROW(cfg.use(AF_INET, "lo"));
    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, CfgIface::SOCKET_UDP));
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);
    // The logic used to require lo to be the only interface. That constraint
    // was removed.
    EXPECT_TRUE(socketOpen("lo", "127.0.0.1"));
    cfg.closeSockets();
    EXPECT_FALSE(socketOpen("lo", "127.0.0.1"));

    // Finally with interfaces and addresses
    cfg.reset();
    ASSERT_NO_THROW(cfg.use(AF_INET, "eth0/10.0.0.1"));
    ASSERT_NO_THROW(cfg.use(AF_INET, "lo/127.0.0.1"));
    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, CfgIface::SOCKET_UDP));
    cfg.openSockets(AF_INET, DHCP4_SERVER_PORT);
    // Only loopback is no longer a constraint
    EXPECT_TRUE(socketOpen("lo", "127.0.0.1"));
    cfg.closeSockets();
    EXPECT_FALSE(socketOpen("lo", "127.0.0.1"));
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

// This test checks that it is possible to specify the loopback interface.
// Note that without a link-local address an unicast address is required.
TEST_F(CfgIfaceTest, explicitLoopbackV6) {
    CfgIface cfg;
    ASSERT_NO_THROW(cfg.use(AF_INET6, "lo/::1"));

    // Open sockets on specified interfaces and addresses.
    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);

    EXPECT_TRUE(socketOpen("lo", AF_INET6));

    // Close all sockets and make sure they are really closed.
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("lo", AF_INET6));

    // Reset configuration.
    cfg.reset();

    // Retry with wirdcard
    ASSERT_NO_THROW(cfg.use(AF_INET6, "*"));
    ASSERT_NO_THROW(cfg.use(AF_INET6, "lo/::1"));
    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);
    // The logic used to require lo to be used only on its own, not with a
    // wildcard. That constraint was removed.
    EXPECT_TRUE(socketOpen("lo", AF_INET6));
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("lo", AF_INET6));

    // Retry with a second interface
    cfg.reset();
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth0"));
    ASSERT_NO_THROW(cfg.use(AF_INET6, "lo/::1"));
    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);
    // The logic used to require lo to be used only on its own, not with a
    // wildcard. That constraint was removed.
    EXPECT_TRUE(socketOpen("lo", AF_INET6));
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("lo", AF_INET6));

    // Finally with interfaces and addresses
    cfg.reset();
    ASSERT_NO_THROW(cfg.use(AF_INET6, "eth0/2001:db8:1::1"));
    ASSERT_NO_THROW(cfg.use(AF_INET6, "lo/::1"));
    cfg.openSockets(AF_INET6, DHCP6_SERVER_PORT);
    // The logic used to require lo to be used only on its own, not with a
    // wildcard. That constraint was removed.
    EXPECT_TRUE(socketOpen("lo", AF_INET6));
    cfg.closeSockets();
    ASSERT_FALSE(socketOpen("lo", AF_INET6));
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

    // Finally, both are equal as they use wildcard.
    cfg2.use(AF_INET, "*");
    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);

    // Differ by socket type.
    cfg1.useSocketType(AF_INET, "udp");
    EXPECT_FALSE(cfg1 == cfg2);
    EXPECT_TRUE(cfg1 != cfg2);

    // Now, both should use the same socket type.
    cfg2.useSocketType(AF_INET, "udp");
    EXPECT_TRUE(cfg1 == cfg2);
    EXPECT_FALSE(cfg1 != cfg2);
}

// This test verifies that it is possible to unparse the interface config.
TEST_F(CfgIfaceTest, unparse) {
    CfgIface cfg4;

    // Add things in it
    EXPECT_NO_THROW(cfg4.use(AF_INET, "*"));
    EXPECT_NO_THROW(cfg4.use(AF_INET, "eth0"));
    EXPECT_NO_THROW(cfg4.use(AF_INET, "eth1/192.0.2.3"));
    std::string comment = "{ \"comment\": \"foo\", \"bar\": 1 }";
    EXPECT_NO_THROW(cfg4.setContext(Element::fromJSON(comment)));

    // Check unparse
    std::string expected =
        "{ \"comment\": \"foo\", "
        "\"interfaces\": [ \"*\", \"eth0\", \"eth1/192.0.2.3\" ], "
        "\"re-detect\": false, "
        "\"user-context\": { \"bar\": 1 } }";
    runToElementTest<CfgIface>(expected, cfg4);

    // Now check IPv6
    CfgIface cfg6;
    EXPECT_NO_THROW(cfg6.use(AF_INET6, "*"));
    EXPECT_NO_THROW(cfg6.use(AF_INET6, "eth1"));
    EXPECT_NO_THROW(cfg6.use(AF_INET6, "eth0/2001:db8:1::1"));
    comment = "{ \"comment\": \"bar\", \"foo\": 2 }";
    EXPECT_NO_THROW(cfg6.setContext(Element::fromJSON(comment)));

    expected =
        "{ \"comment\": \"bar\", "
        "\"interfaces\": [ \"*\", \"eth1\", \"eth0/2001:db8:1::1\" ], "
        "\"re-detect\": false, "
        "\"user-context\": { \"foo\": 2 } }";
    runToElementTest<CfgIface>(expected, cfg6);
}

// This test verifies that it is possible to specify the socket
// type to be used by the DHCPv4 server.
// This test is enabled on LINUX and BSD only, because the
// direct traffic is only supported on those systems.
#if defined OS_LINUX || defined OS_BSD
TEST(CfgIfaceNoStubTest, useSocketType) {
    CfgIface cfg;
    // Select datagram sockets.
    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, "udp"));
    EXPECT_EQ("udp", cfg.socketTypeToText());
    ASSERT_NO_THROW(cfg.openSockets(AF_INET, 10067, true));
    // For datagram sockets, the direct traffic is not supported.
    ASSERT_TRUE(!IfaceMgr::instance().isDirectResponseSupported());

    // Check unparse
    std::string expected = "{\n"
        " \"interfaces\": [ ],\n"
        " \"dhcp-socket-type\": \"udp\",\n"
        " \"re-detect\": false }";
    runToElementTest<CfgIface>(expected, cfg);

    // Select raw sockets.
    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, "raw"));
    EXPECT_EQ("raw", cfg.socketTypeToText());
    ASSERT_NO_THROW(cfg.openSockets(AF_INET, 10067, true));
    // For raw sockets, the direct traffic is supported.
    ASSERT_TRUE(IfaceMgr::instance().isDirectResponseSupported());

    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, CfgIface::SOCKET_UDP));
    EXPECT_EQ("udp", cfg.socketTypeToText());
    ASSERT_NO_THROW(cfg.openSockets(AF_INET, 10067, true));
    ASSERT_TRUE(!IfaceMgr::instance().isDirectResponseSupported());

    ASSERT_NO_THROW(cfg.useSocketType(AF_INET, CfgIface::SOCKET_RAW));
    EXPECT_EQ("raw", cfg.socketTypeToText());
    ASSERT_NO_THROW(cfg.openSockets(AF_INET, 10067, true));
    ASSERT_TRUE(IfaceMgr::instance().isDirectResponseSupported());

    // Test invalid values.
    EXPECT_THROW(cfg.useSocketType(AF_INET, "default"),
        InvalidSocketType);
    EXPECT_THROW(cfg.useSocketType(AF_INET6, "udp"),
        InvalidSocketType);
}
#endif


} // end of anonymous namespace
