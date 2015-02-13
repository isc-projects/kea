// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for @c IfacesConfigParser
class IfacesConfigParserTest : public ::testing::Test {
protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

};

void
IfacesConfigParserTest::SetUp() {
    CfgMgr::instance().clear();
}

void
IfacesConfigParserTest::TearDown() {
    CfgMgr::instance().clear();
}

// This test checks that the parser correctly parses the list of interfaces
// on which the server should listen.
TEST_F(IfacesConfigParserTest, interfaces) {
    // Creates fake interfaces with fake addresses.
    IfaceMgrTestConfig test_config(true);

    // Configuration with one interface.
    std::string config = "{ ""\"interfaces\": [ \"eth0\" ] }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser4 parser;
    ASSERT_NO_THROW(parser.build(config_element));

    // Open sockets according to the parsed configuration.
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    ASSERT_NO_THROW(cfg->getCfgIface()->openSockets(AF_INET, 10000));

    // Only eth0 should have an open socket.
    EXPECT_TRUE(test_config.socketOpen("eth0", AF_INET));
    EXPECT_FALSE(test_config.socketOpen("eth1", AF_INET));

    // Reset configuration.
    cfg->getCfgIface()->closeSockets();
    CfgMgr::instance().clear();

    // Try similar configuration but this time add a wildcard interface
    // to see if sockets will open on all interfaces.
    config = "{ \"interfaces\": [ \"eth0\", \"*\" ] }";
    config_element = Element::fromJSON(config);

    ASSERT_NO_THROW(parser.build(config_element));

    cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_NO_THROW(cfg->getCfgIface()->openSockets(AF_INET, 10000));

    EXPECT_TRUE(test_config.socketOpen("eth0", AF_INET));
    EXPECT_TRUE(test_config.socketOpen("eth1", AF_INET));
}

// This test verifies that it is possible to select the raw socket
// use in the configuration for interfaces.
TEST_F(IfacesConfigParserTest, socketTypeRaw) {
    // Create the reference configuration, which we will compare
    // the parsed configuration to.
    CfgIface cfg_ref;

    // Configuration with a raw socket selected.
    std::string config = "{ ""\"interfaces\": [ ],"
        " \"dhcp-socket-type\": \"raw\" }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser4 parser;
    ASSERT_NO_THROW(parser.build(config_element));

    // Compare the resulting configuration with a reference
    // configuration using the raw socket.
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    cfg_ref.useSocketType(AF_INET, CfgIface::SOCKET_RAW);
    EXPECT_TRUE(*cfg->getCfgIface() == cfg_ref);
}

// This test verifies that it is possible to select the datagram socket
// use in the configuration for interfaces.
TEST_F(IfacesConfigParserTest, socketTypeDatagram) {
    // Create the reference configuration, which we will compare
    // the parsed configuration to.
    CfgIface cfg_ref;

    // Configuration with a datagram socket selected.
    std::string config = "{ ""\"interfaces\": [ ],"
        " \"dhcp-socket-type\": \"udp\" }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser4 parser;
    ASSERT_NO_THROW(parser.build(config_element));

    // Compare the resulting configuration with a reference
    // configuration using the raw socket.
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    cfg_ref.useSocketType(AF_INET, CfgIface::SOCKET_UDP);
    EXPECT_TRUE(*cfg->getCfgIface() == cfg_ref);
}

// Test that the configuration rejects the invalid socket type.
TEST_F(IfacesConfigParserTest, socketTypeInvalid) {
    // For DHCPv4 we only accept the raw socket or datagram socket.
    IfacesConfigParser4 parser4;
    std::string config = "{ \"interfaces\": [ ],"
        "\"dhcp-socket-type\": \"default\" }";
    ElementPtr config_element = Element::fromJSON(config);
    ASSERT_THROW(parser4.build(config_element), DhcpConfigError);

    // For DHCPv6 we don't accept any socket type.
    IfacesConfigParser6 parser6;
    config = "{ \"interfaces\": [ ],"
        " \"dhcp-socket-type\": \"udp\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser6.build(config_element), DhcpConfigError);
}

} // end of anonymous namespace
