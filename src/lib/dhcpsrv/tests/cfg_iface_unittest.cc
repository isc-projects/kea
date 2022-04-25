// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_filter_test_stub.h>
#include <dhcp/tests/pkt_filter6_test_stub.h>
#include <dhcpsrv/cfg_iface.h>
#include <asiolink/io_service.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <dhcpsrv/timer_mgr.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;
using namespace isc::data;
using namespace isc::util;

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

    /// @brief Wait for specific timeout.
    ///
    /// @param timeout Wait timeout in milliseconds.
    void doWait(const long timeout);

    /// @brief Holds a fake configuration of the interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

    /// @brief Pointer to IO service used by the tests.
    asiolink::IOServicePtr io_service_;

private:

    /// @brief Prepares the class for a test.
    virtual void SetUp();

    /// @brief Cleans up after the test.
    virtual void TearDown();
};

void
CfgIfaceTest::SetUp() {
    IfaceMgr::instance().setTestMode(true);
    io_service_.reset(new asiolink::IOService());
    TimerMgr::instance()->setIOService(io_service_);
}

void
CfgIfaceTest::TearDown() {
    // Remove all timers.
    TimerMgr::instance()->unregisterTimers();

    IfaceMgr::instance().setTestMode(false);
    IfaceMgr::instance().clearIfaces();
    IfaceMgr::instance().closeSockets();
    IfaceMgr::instance().detectIfaces();

    // Reset global handlers
    CfgIface::open_sockets_failed_callback_ = 0;
}

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

void
CfgIfaceTest::doWait(const long timeout) {
    asiolink::IntervalTimer timer(*io_service_);
    timer.setup([this]() {
        io_service_->stop();
    }, timeout, asiolink::IntervalTimer::ONE_SHOT);
    io_service_->run();
    io_service_->get_io_service().reset();
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

    // Retry with wildcard
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

    // Retry with wildcard
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
        "{ "
        "\"interfaces\": [ \"*\", \"eth0\", \"eth1/192.0.2.3\" ], "
        "\"re-detect\": false, "
        "\"user-context\": { \"comment\": \"foo\", \"bar\": 1 } }";
    runToElementTest<CfgIface>(expected, cfg4);

    // Now check IPv6
    CfgIface cfg6;
    EXPECT_NO_THROW(cfg6.use(AF_INET6, "*"));
    EXPECT_NO_THROW(cfg6.use(AF_INET6, "eth1"));
    EXPECT_NO_THROW(cfg6.use(AF_INET6, "eth0/2001:db8:1::1"));
    comment = "{ \"comment\": \"bar\", \"foo\": 2 }";
    EXPECT_NO_THROW(cfg6.setContext(Element::fromJSON(comment)));

    expected =
        "{ "
        "\"interfaces\": [ \"*\", \"eth1\", \"eth0/2001:db8:1::1\" ], "
        "\"re-detect\": false, "
        "\"user-context\": { \"comment\": \"bar\", \"foo\": 2 } }";
    runToElementTest<CfgIface>(expected, cfg6);
}

// This test verifies that it is possible to require that all
// service sockets are opened properly. If any socket fails to
// bind then an exception should be thrown.
TEST_F(CfgIfaceTest, requireOpenAllServiceSockets) {
    CfgIface cfg4;
    CfgIface cfg6;

    // Configure a fail callback
    uint16_t fail_calls = 0;
    CfgIface::OpenSocketsFailedCallback on_fail_callback =
        [&fail_calls](ReconnectCtlPtr reconnect_ctl) {
            EXPECT_TRUE(reconnect_ctl);
            EXPECT_TRUE(reconnect_ctl->exitOnFailure());
            fail_calls++;
        };

    CfgIface::open_sockets_failed_callback_ = on_fail_callback;

    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth0"));
    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth1/192.0.2.3"));
    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth0/2001:db8:1::1"));
    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth1"));

    // Require all sockets bind successfully
    cfg4.setServiceSocketsRequireAll(true);
    cfg4.setServiceSocketsMaxRetries(0);
    cfg6.setServiceSocketsRequireAll(true);
    cfg6.setServiceSocketsMaxRetries(0);

    // Open the available ports
    ASSERT_NO_THROW(cfg4.openSockets(AF_INET, DHCP4_SERVER_PORT));
    ASSERT_NO_THROW(cfg6.openSockets(AF_INET6, DHCP6_SERVER_PORT));
    cfg4.closeSockets();
    cfg6.closeSockets();

    // Set the callback to throw an exception on open
    auto open_callback = [](uint16_t) {
        isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
    };
    boost::shared_ptr<isc::dhcp::test::PktFilterTestStub> filter(new isc::dhcp::test::PktFilterTestStub());
    boost::shared_ptr<isc::dhcp::test::PktFilter6TestStub> filter6(new isc::dhcp::test::PktFilter6TestStub());
    filter->setOpenSocketCallback(open_callback);
    filter6->setOpenSocketCallback(open_callback);
    ASSERT_TRUE(filter);
    ASSERT_TRUE(filter6);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter6));

    // Open an unavailable port
    EXPECT_NO_THROW(cfg4.openSockets(AF_INET, DHCP4_SERVER_PORT));
    EXPECT_NO_THROW(cfg6.openSockets(AF_INET6, DHCP6_SERVER_PORT));

    // Both instances should call the fail callback.
    EXPECT_EQ(fail_calls, 2);
}

// This test verifies that if any IPv4 socket fails to bind,
// the opening will retry.
TEST_F(CfgIfaceTest, retryOpenServiceSockets4) {
    CfgIface cfg4;

    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth0"));
    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth1/192.0.2.3"));

    // Parameters
    const uint16_t RETRIES = 5;
    const uint16_t WAIT_TIME = 10; // miliseconds
    // The number of sockets opened in a single retry attempt.
    // iface: eth0 addr: 10.0.0.1 port: 67 rbcast: 0 sbcast: 0
    // iface: eth1 addr: 192.0.2.3 port: 67 rbcast: 0 sbcast: 0
    const uint16_t CALLS_PER_RETRY = 2;

    // Require retry socket binding
    cfg4.setServiceSocketsMaxRetries(RETRIES);
    cfg4.setServiceSocketsRetryWaitTime(WAIT_TIME);

    // Set the callback to count calls and check wait time
    size_t total_calls = 0;
    auto last_call_time = std::chrono::system_clock::time_point::min();
    auto open_callback = [&total_calls, &last_call_time, WAIT_TIME](uint16_t) {
        auto now = std::chrono::system_clock::now();

        // Check waiting time only for the first call in a retry attempt.
        if (total_calls % CALLS_PER_RETRY == 0) {
            // Don't check the waiting time for initial call.
            if (total_calls != 0) {
                auto interval = now - last_call_time;
                auto interval_ms =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        interval
                    ).count();

                EXPECT_GE(interval_ms, WAIT_TIME);
            }

            last_call_time = now;
        }

        total_calls++;

        // Fail to open a socket
        isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
    };

    boost::shared_ptr<isc::dhcp::test::PktFilterTestStub> filter(
        new isc::dhcp::test::PktFilterTestStub()
    );

    filter->setOpenSocketCallback(open_callback);

    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));

    // Open an unavailable port
    ASSERT_NO_THROW(cfg4.openSockets(AF_INET, DHCP4_SERVER_PORT));

    // Wait for a finish sockets binding (with a safe margin).
    doWait(RETRIES * WAIT_TIME * 2);

    // For each interface perform 1 init open and a few retries.
    EXPECT_EQ(CALLS_PER_RETRY * (RETRIES + 1), total_calls);
}

// This test verifies that if any IPv4 socket fails to bind, the opening will
// retry, but the opened sockets will not be re-bound.
TEST_F(CfgIfaceTest, retryOpenServiceSockets4OmitBound) {
    CfgIface cfg4;

    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth0"));
    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth1/192.0.2.3"));

    // Parameters
    const uint16_t RETRIES = 5;
    const uint16_t WAIT_TIME = 10; // miliseconds

    // Require retry socket binding
    cfg4.setServiceSocketsMaxRetries(RETRIES);
    cfg4.setServiceSocketsRetryWaitTime(WAIT_TIME);

    // Set the callback to count calls and check wait time
    size_t total_calls = 0;
    auto last_call_time = std::chrono::system_clock::time_point::min();
    auto open_callback = [&total_calls, &last_call_time, WAIT_TIME](uint16_t) {
        auto now = std::chrono::system_clock::now();
        bool is_eth1 = total_calls == 1;

        // Skip the wait time check for the socket when two sockets are
        // binding in a single attempt.

        // Don't check the waiting time for initial calls.
        // iface: eth0 addr: 10.0.0.1 port: 67 rbcast: 0 sbcast: 0
        // iface: eth1 addr: 192.0.2.3 port: 67 rbcast: 0 sbcast: 0 - fails
        if (total_calls > 1) {
            auto interval = now - last_call_time;
            auto interval_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    interval
                ).count();

            EXPECT_GE(interval_ms, WAIT_TIME);
        }

        last_call_time = now;

        total_calls++;

        // Fail to open a socket on eth0, success for eth1
        if (!is_eth1) {
            isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
        }
    };

    boost::shared_ptr<isc::dhcp::test::PktFilterTestStub> filter(
        new isc::dhcp::test::PktFilterTestStub()
    );

    filter->setOpenSocketCallback(open_callback);

    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));

    // Open an unavailable port
    ASSERT_NO_THROW(cfg4.openSockets(AF_INET, DHCP4_SERVER_PORT));

    // Wait for a finish sockets binding (with a safe margin).
    doWait(RETRIES * WAIT_TIME * 2);

    // For eth0 interface perform 1 init open and a few retries,
    // for eth1 interface perform only init open.
    EXPECT_EQ((RETRIES + 1) + 1, total_calls);
}

// Test that only one reopen timer is active simultaneously. If a new opening
// starts, then the previous should be interrupted.
TEST_F(CfgIfaceTest, retryDoubleOpenServiceSockets4) {
    CfgIface cfg4;

    ASSERT_NO_THROW(cfg4.use(AF_INET, "eth0"));

    // Initial timer has a high frequency.
    cfg4.setServiceSocketsMaxRetries(10000);
    cfg4.setServiceSocketsRetryWaitTime(1);

    // Set the callback that interrupt the previous execution.
    uint16_t first_port_calls = 0;
    uint16_t second_port_calls = 0;
    auto open_callback = [&first_port_calls, &second_port_calls](uint16_t port) {
        // First timer must be interrupted.
        if (second_port_calls > 0) {
            EXPECT_TRUE(port == 2);
        }

        if (port == 1) {
            first_port_calls++;
        } else {
            second_port_calls++;
        }

        // Fail to open and retry.
        isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
    };

    boost::shared_ptr<isc::dhcp::test::PktFilterTestStub> filter(
        new isc::dhcp::test::PktFilterTestStub()
    );

    filter->setOpenSocketCallback(open_callback);

    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));

    // First opening.
    ASSERT_NO_THROW(cfg4.openSockets(AF_INET, 1));

    // Wait a short time.
    doWait(10);

    // Reconfigure the interface parameters.
    cfg4.setServiceSocketsMaxRetries(1);
    cfg4.setServiceSocketsRetryWaitTime(10);

    // Second opening.
    ASSERT_NO_THROW(cfg4.openSockets(AF_INET, 2));

    doWait(50);

    // The first timer should perform some calls.
    EXPECT_GT(first_port_calls, 0);
    // The secondary timer should make 2 calls: initial and 1 retry.
    EXPECT_EQ(second_port_calls, 2);
}

// This test verifies that if any IPv6 socket fails to bind,
// the opening will retry.
TEST_F(CfgIfaceTest, retryOpenServiceSockets6) {
    CfgIface cfg6;

    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth0/2001:db8:1::1"));
    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth1"));

    // Parameters
    const uint16_t RETRIES = 5;
    const uint16_t WAIT_TIME = 10; // miliseconds
    // The number of sockets opened in a single retry attempt.
    // 1 unicast and 2 multicast sockets.
    // iface: eth0 addr: 2001:db8:1::1 port: 547 multicast: 0
    // iface: eth0 addr: fe80::3a60:77ff:fed5:cdef port: 547 multicast: 1
    // iface: eth1 addr: fe80::3a60:77ff:fed5:abcd port: 547 multicast: 1
    const uint16_t CALLS_PER_RETRY = 3;

    // Require retry socket binding
    cfg6.setServiceSocketsMaxRetries(RETRIES);
    cfg6.setServiceSocketsRetryWaitTime(WAIT_TIME);

    // Set the callback to count calls and check wait time
    size_t total_calls = 0;
    auto last_call_time = std::chrono::system_clock::time_point::min();
    auto open_callback = [&total_calls, &last_call_time, WAIT_TIME](uint16_t) {
        auto now = std::chrono::system_clock::now();

        // Check waiting time only for the first call in a retry attempt.
        if (total_calls % CALLS_PER_RETRY == 0) {
            // Don't check the waiting time for initial call.
            if (total_calls != 0) {
                auto interval = now - last_call_time;
                auto interval_ms =
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        interval
                    ).count();

                EXPECT_GE(interval_ms, WAIT_TIME);
            }

            last_call_time = now;
        }

        total_calls++;

        // Fail to open a socket
        isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
    };

    boost::shared_ptr<isc::dhcp::test::PktFilter6TestStub> filter(
        new isc::dhcp::test::PktFilter6TestStub()
    );
    filter->setOpenSocketCallback(open_callback);
    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));

    // Open an unavailable port
    ASSERT_NO_THROW(cfg6.openSockets(AF_INET6, DHCP6_SERVER_PORT));

    // Wait for a finish sockets binding (with a safe margin).
    doWait(RETRIES * WAIT_TIME * 2);

    // For each interface perform 1 init open and a few retries.
    EXPECT_EQ(CALLS_PER_RETRY * (RETRIES + 1), total_calls);
}

// This test verifies that if any IPv6 socket fails to bind, the opening will
// retry, but the opened sockets will not be re-bound.
TEST_F(CfgIfaceTest, retryOpenServiceSockets6OmitBound) {
    CfgIface cfg6;

    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth0/2001:db8:1::1"));
    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth1"));

    // Parameters
    const uint16_t RETRIES = 5;
    const uint16_t WAIT_TIME = 10; // miliseconds

    // Require retry socket binding
    cfg6.setServiceSocketsMaxRetries(RETRIES);
    cfg6.setServiceSocketsRetryWaitTime(WAIT_TIME);

#if defined OS_LINUX
    const uint32_t opened_by_eth0 = 3;
#else
    const uint32_t opened_by_eth0 = 2;
#endif

    // Set the callback to count calls and check wait time
    size_t total_calls = 0;
    auto last_call_time = std::chrono::system_clock::time_point::min();
    auto open_callback = [&total_calls, &last_call_time, WAIT_TIME](uint16_t) {
        auto now = std::chrono::system_clock::now();
        bool is_eth0 = total_calls < opened_by_eth0;

        // Skip the wait time check for the socket when two sockets are
        // binding in a single attempt.

        // Don't check the waiting time for initial calls.
        // iface: eth0 addr: 2001:db8:1::1 port: 547 multicast: 0
        // iface: eth0 addr: fe80::3a60:77ff:fed5:cdef port: 547 multicast: 1
        // iface: eth0 addr: ff02::1:2 port: 547 multicast: 0 --- only on Linux systems
        // iface: eth1 addr: fe80::3a60:77ff:fed5:abcd port: 547 multicast: 1 - fails

        if (total_calls > (opened_by_eth0 + 1)) {
            auto interval = now - last_call_time;
            auto interval_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    interval
                ).count();

            EXPECT_GE(interval_ms, WAIT_TIME);
        }

        last_call_time = now;

        total_calls++;

        // Fail to open a socket on eth1, success for eth0
        if (!is_eth0) {
            isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
        }
    };

    boost::shared_ptr<isc::dhcp::test::PktFilter6TestStub> filter(
        new isc::dhcp::test::PktFilter6TestStub()
    );

    filter->setOpenSocketCallback(open_callback);

    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));

    // Open an unavailable port
    ASSERT_NO_THROW(cfg6.openSockets(AF_INET6, DHCP6_SERVER_PORT));

    // Wait for a finish sockets binding (with a safe margin).
    doWait(RETRIES * WAIT_TIME * 2);

    // For eth0 interface perform only 3 (on Linux Systems or 2 otherwise) init open,
    // for eth1 interface perform 1 init open and a few retries.
    EXPECT_EQ((RETRIES + 1) + opened_by_eth0, total_calls);
}

// Test that only one reopen timer is active simultaneously. If a new opening
// starts, then the previous should be interrupted.
TEST_F(CfgIfaceTest, retryDoubleOpenServiceSockets6) {
    CfgIface cfg6;

    ASSERT_NO_THROW(cfg6.use(AF_INET6, "eth0"));

    // Initial timer has a high frequency.
    cfg6.setServiceSocketsMaxRetries(10000);
    cfg6.setServiceSocketsRetryWaitTime(1);

    // Set the callback that interrupt the previous execution.
    uint16_t first_port_calls = 0;
    uint16_t second_port_calls = 0;
    auto open_callback = [&first_port_calls, &second_port_calls](uint16_t port) {
        // First timer must be interrupted.
        if (second_port_calls > 0) {
            EXPECT_TRUE(port == 2);
        }

        if (port == 1) {
            first_port_calls++;
        } else {
            second_port_calls++;
        }

        // Fail to open and retry.
        isc_throw(Unexpected, "CfgIfaceTest: cannot open a port");
    };

    boost::shared_ptr<isc::dhcp::test::PktFilter6TestStub> filter(
        new isc::dhcp::test::PktFilter6TestStub()
    );

    filter->setOpenSocketCallback(open_callback);

    ASSERT_TRUE(filter);
    ASSERT_NO_THROW(IfaceMgr::instance().setPacketFilter(filter));

    // First opening.
    ASSERT_NO_THROW(cfg6.openSockets(AF_INET6, 1));

    // Wait a short time.
    doWait(10);

    // Reconfigure the interface parameters.
    cfg6.setServiceSocketsMaxRetries(1);
    cfg6.setServiceSocketsRetryWaitTime(10);

    // Second opening.
    ASSERT_NO_THROW(cfg6.openSockets(AF_INET6, 2));

    doWait(50);

    // The first timer should perform some calls.
    EXPECT_GT(first_port_calls, 0);
    // The secondary timer should make 2 calls: initial and 1 retry.
    EXPECT_EQ(second_port_calls, 2);
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
