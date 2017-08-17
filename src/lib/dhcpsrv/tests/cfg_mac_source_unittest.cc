// Copyright (C) 2014-2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfg_mac_source.h>
#include <dhcp/hwaddr.h>
#include <exceptions/exceptions.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>
#include <string>

namespace {

using namespace isc;
using namespace isc::dhcp;
using namespace isc::test;

// Checks whether CfgMACSource::MACSourceFromText is working correctly.
// Technically, this is a Pkt, not Pkt6 test, but since there is no separate
// unit-tests for Pkt and it is abstract, so it would be tricky to test it
// directly. Hence test is being run in Pkt6.
TEST(CfgMACSourceTest, MACSourceFromText) {
    EXPECT_THROW(CfgMACSource::MACSourceFromText("unknown"), BadValue);

    EXPECT_EQ(HWAddr::HWADDR_SOURCE_ANY, CfgMACSource::MACSourceFromText("any"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_RAW, CfgMACSource::MACSourceFromText("raw"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_DUID, CfgMACSource::MACSourceFromText("duid"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL,
              CfgMACSource::MACSourceFromText("ipv6-link-local"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION,
              CfgMACSource::MACSourceFromText("client-link-addr-option"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION,
              CfgMACSource::MACSourceFromText("rfc6939"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_REMOTE_ID,
              CfgMACSource::MACSourceFromText("remote-id"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_REMOTE_ID,
              CfgMACSource::MACSourceFromText("rfc4649"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID,
              CfgMACSource::MACSourceFromText("subscriber-id"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID,
              CfgMACSource::MACSourceFromText("rfc4580"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_DOCSIS_CMTS,
              CfgMACSource::MACSourceFromText("docsis-cmts"));
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM,
              CfgMACSource::MACSourceFromText("docsis-modem"));
}

// Checks whether the opposite operation is working correctly.
TEST(CfgMACSourceTest, unparse) {
    CfgMACSource cfg;
    // any was added by the constructor
    cfg.add(HWAddr::HWADDR_SOURCE_RAW);
    cfg.add(HWAddr::HWADDR_SOURCE_DUID);
    cfg.add(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL);
    cfg.add(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION);
    cfg.add(HWAddr::HWADDR_SOURCE_REMOTE_ID);
    cfg.add(HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID);
    cfg.add(HWAddr::HWADDR_SOURCE_DOCSIS_CMTS);
    cfg.add(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM);

    // Unparse
    std::string expected = "["
        "\"any\","
        "\"raw\","
        "\"duid\","
        "\"ipv6-link-local\","
        "\"client-link-addr-option\","
        "\"remote-id\","
        "\"subscriber-id\","
        "\"docsis-cmts\","
        "\"docsis-modem\""
        "]";
    runToElementTest<CfgMACSource>(expected, cfg);

    // Add an unknown type
    cfg.add(0x12345678);
    ASSERT_THROW(cfg.toElement(), ToElementError);
}

};
