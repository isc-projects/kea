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

    /// @brief Checks if socket of the specified family is opened on interface.
    ///
    /// @param iface_name Interface name.
    /// @param family One of: AF_INET or AF_INET6
    bool socketOpen(const std::string& iface_name, const int family) const;

    /// @brief Holds a fake configuration of the interfaces.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

bool
IfaceCfgTest::socketOpen(const std::string& iface_name,
                         const int family) const {
    Iface* iface = IfaceMgr::instance().getIface(iface_name);
    if (iface == NULL) {
        ADD_FAILURE() << "No such interface '" << iface_name << "'";
        return (false);
    }

    const Iface::SocketCollection& sockets = iface->getSockets();
    for (Iface::SocketCollection::const_iterator sock = sockets.begin();
         sock != sockets.end(); ++sock) {
        if (sock->family_ == family) {
            return (true);
        }
    }
    return (false);
}

// This test checks that the interface names can be explicitly selected
// by their names and IPv4 sockets are opened on these interfaces.
TEST_F(IfaceCfgTest, explicitNamesV4) {
    IfaceCfg cfg(IfaceCfg::V4);
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
TEST_F(IfaceCfgTest, explicitNamesV6) {
    IfaceCfg cfg(IfaceCfg::V6);
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

} // end of anonymous namespace
