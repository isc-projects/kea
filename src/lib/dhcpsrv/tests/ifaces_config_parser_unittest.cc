// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;

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
    std::string config =
        "{ \"interfaces\": [ \"eth0\" ], \"re-detect\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser parser(AF_INET);
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    ASSERT_TRUE(cfg_iface);
    ASSERT_NO_THROW(parser.parse(cfg_iface, config_element));

    // Check it can be unparsed.
    runToElementTest<CfgIface>(config, *cfg_iface);

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
    config = "{ \"interfaces\": [ \"eth0\", \"*\" ], \"re-detect\": false }";
    config_element = Element::fromJSON(config);

    cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    ASSERT_TRUE(cfg_iface);
    ASSERT_NO_THROW(parser.parse(cfg_iface, config_element));

    runToElementTest<CfgIface>(config, *cfg_iface);

    cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_NO_THROW(cfg->getCfgIface()->openSockets(AF_INET, 10000));

    EXPECT_TRUE(test_config.socketOpen("eth0", AF_INET));
    EXPECT_TRUE(test_config.socketOpen("eth1", AF_INET));
}


// This test checks that the parsed structure can be converted back to Element
// tree.
TEST_F(IfacesConfigParserTest, toElement) {
    // Creates fake interfaces with fake addresses.
    IfaceMgrTestConfig test_config(true);

    // Configuration with one interface.
    std::string config =
        "{ \"user-context\": { \"foo\": \"bar\" }, "
        "  \"interfaces\": [ \"eth0\" ], "
        "  \"dhcp-socket-type\": \"udp\","
        "  \"outbound-interface\": \"use-routing\", "
        "  \"re-detect\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser parser(AF_INET);
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    ASSERT_TRUE(cfg_iface);
    ASSERT_NO_THROW(parser.parse(cfg_iface, config_element));

    // Check it can be unparsed.
    runToElementTest<CfgIface>(config, *cfg_iface);
}


// This test verifies that it is possible to select the raw socket
// use in the configuration for interfaces.
TEST_F(IfacesConfigParserTest, socketTypeRaw) {
    // Create the reference configuration, which we will compare
    // the parsed configuration to.
    CfgIface cfg_ref;

    // Configuration with a raw socket selected.
    std::string config = "{ ""\"interfaces\": [ ],"
        " \"dhcp-socket-type\": \"raw\","
        " \"re-detect\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser parser(AF_INET);
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    ASSERT_NO_THROW(parser.parse(cfg_iface, config_element));

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
    std::string config = "{ \"interfaces\": [ ],"
        " \"dhcp-socket-type\": \"udp\","
        " \"re-detect\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    // Parse the configuration.
    IfacesConfigParser parser(AF_INET);
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    ASSERT_TRUE(cfg_iface);
    ASSERT_NO_THROW(parser.parse(cfg_iface, config_element));

    // Check it can be unparsed.
    runToElementTest<CfgIface>(config, *cfg_iface);

    // Compare the resulting configuration with a reference
    // configuration using the raw socket.
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    cfg_ref.useSocketType(AF_INET, CfgIface::SOCKET_UDP);
    ASSERT_TRUE(cfg->getCfgIface());
    EXPECT_TRUE(*cfg->getCfgIface() == cfg_ref);
}

// Test that the configuration rejects the invalid socket type.
TEST_F(IfacesConfigParserTest, socketTypeInvalid) {
    // For DHCPv4 we only accept the raw socket or datagram socket.
    IfacesConfigParser parser4(AF_INET);
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    std::string config = "{ \"interfaces\": [ ],"
        "\"dhcp-socket-type\": \"default\","
        " \"re-detect\": false }";
    ElementPtr config_element = Element::fromJSON(config);
    ASSERT_THROW(parser4.parse(cfg_iface, config_element), DhcpConfigError);

    // For DHCPv6 we don't accept any socket type.
    IfacesConfigParser parser6(AF_INET6);
    config = "{ \"interfaces\": [ ],"
        " \"dhcp-socket-type\": \"udp\","
        " \"re-detect\": false }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser6.parse(cfg_iface, config_element), DhcpConfigError);
}

// Tests that outbound-interface is parsed properly.
TEST_F(IfacesConfigParserTest, outboundInterface) {
    // For DHCPv4 we accept 'use-routing' or 'same-as-inbound'.
    IfacesConfigParser parser4(AF_INET);

    // For DHCPv6 we don't accept this at all.
    IfacesConfigParser parser6(AF_INET6);

    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();

    // The default should be to use the same as client's query packet.
    EXPECT_EQ(CfgIface::SAME_AS_INBOUND, cfg_iface->getOutboundIface());

    // Value 1: use-routing
    std::string config = "{ \"interfaces\": [ ],"
        "\"outbound-interface\": \"use-routing\","
        " \"re-detect\": false }";
    ElementPtr config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser4.parse(cfg_iface, config_element));
    EXPECT_EQ(CfgIface::USE_ROUTING, cfg_iface->getOutboundIface());
    EXPECT_THROW(parser6.parse(cfg_iface, config_element), DhcpConfigError);

    // Value 2: same-as-inbound
    config = "{ \"interfaces\": [ ],"
        "\"outbound-interface\": \"same-as-inbound\","
        " \"re-detect\": false }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser4.parse(cfg_iface, config_element));
    EXPECT_EQ(CfgIface::SAME_AS_INBOUND, cfg_iface->getOutboundIface());
    EXPECT_THROW(parser6.parse(cfg_iface, config_element), DhcpConfigError);

    // Other values are not supported.
    config = "{ \"interfaces\": [ ],"
        "\"outbound-interface\": \"default\","
        " \"re-detect\": false }";
    config_element = Element::fromJSON(config);
    EXPECT_THROW(parser4.parse(cfg_iface, config_element), DhcpConfigError);
    EXPECT_THROW(parser6.parse(cfg_iface, config_element), DhcpConfigError);
}

} // end of anonymous namespace
