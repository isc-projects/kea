// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/parsers/shared_networks_list_parser.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

// This is a basic test verifying that all shared networks are correctly
// parsed.
TEST(SharedNetworkListParserTest, parse) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration with array of shared networks.
    std::string config = "["
        "    {"
        "        \"name\": \"bird\","
        "        \"interface\": \"eth0\""
        "    },"
        "    {"
        "        \"name\": \"monkey\","
        "        \"interface\": \"eth1\","
        "        \"user-context\": { \"comment\": \"example\" }"
        "    }"
        "]";

    ElementPtr config_element = Element::fromJSON(config);

    SharedNetworks4ListParser parser;
    CfgSharedNetworks4Ptr cfg(new CfgSharedNetworks4());
    ASSERT_NO_THROW(parser.parse(cfg, config_element));

    SharedNetwork4Ptr network1 = cfg->getByName("bird");
    ASSERT_TRUE(network1);
    EXPECT_EQ("bird", network1->getName());
    EXPECT_EQ("eth0", network1->getIface().get());
    EXPECT_FALSE(network1->getContext());

    SharedNetwork4Ptr network2 = cfg->getByName("monkey");
    ASSERT_TRUE(network2);
    EXPECT_EQ("monkey", network2->getName());
    EXPECT_EQ("eth1", network2->getIface().get());
    ASSERT_TRUE(network2->getContext());
    EXPECT_EQ(1, network2->getContext()->size());
    EXPECT_TRUE(network2->getContext()->get("comment"));
}

// This test verifies that specifying two networks with the same name
// yields an error.
TEST(SharedNetworkListParserTest, duplicatedName) {
    IfaceMgrTestConfig ifmgr(true);

    // Basic configuration with two networks having the same name.
    std::string config = "["
        "    {"
        "        \"name\": \"bird\","
        "        \"interface\": \"eth0\""
        "    },"
        "    {"
        "        \"name\": \"bird\","
        "        \"interface\": \"eth1\""
        "    }"
        "]";

    ElementPtr config_element = Element::fromJSON(config);

    SharedNetworks4ListParser parser;
    CfgSharedNetworks4Ptr cfg(new CfgSharedNetworks4());
    EXPECT_THROW(parser.parse(cfg, config_element), DhcpConfigError);
}

// This test verifies that the optional interface check works as expected.
TEST(SharedNetworkListParserTest, iface) {
    // Basic configuration with a shared network.
    std::string config = "["
        "    {"
        "        \"name\": \"bird\","
        "        \"interface\": \"eth0\""
        "    }"
        "]";

    ElementPtr config_element = Element::fromJSON(config);

    // The interface check can be disabled.
    SharedNetworks6ListParser parser_no_check(false);
    CfgSharedNetworks6Ptr cfg(new CfgSharedNetworks6());
    EXPECT_NO_THROW(parser_no_check.parse(cfg, config_element));
    cfg.reset(new CfgSharedNetworks6());

    // Retry with the interface check enabled.
    SharedNetworks6ListParser parser;
    EXPECT_THROW(parser.parse(cfg, config_element), DhcpConfigError);
    cfg.reset(new CfgSharedNetworks6());

    // Configure default test interfaces.
    IfaceMgrTestConfig ifmgr(true);
    EXPECT_NO_THROW(parser_no_check.parse(cfg, config_element));
    cfg.reset(new CfgSharedNetworks6());
    EXPECT_NO_THROW(parser.parse(cfg, config_element));
}

} // end of anonymous namespace
