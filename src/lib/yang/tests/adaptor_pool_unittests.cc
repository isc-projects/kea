// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/adaptor_pool.h>
#include <yang/yang_models.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Verifies that canonizePool does not touch a prefix without space.
TEST(AdaptorPoolTest, canonizePoolPrefixNoSpace) {
    string config = "{\n"
        " \"pool\": \"192.0.2.128/28\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorPool::canonizePool(json));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies that canonizePool does not touch a canonical range.
TEST(AdaptorPoolTest, canonizePoolRange) {
    string config = "{\n"
        " \"pool\": \"192.0.2.1 - 192.0.2.200\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorPool::canonizePool(json));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies that canonizePool removes spaces from a prefix.
TEST(AdaptorPoolTest, canonizePoolPrefixSpaces) {
    string config = "{\n"
        " \"pool\": \"192.0.2.128 /\t28\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorPool::canonizePool(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr pool = json->get("pool");
    ASSERT_TRUE(pool);
    ASSERT_EQ(Element::string, pool->getType());
    EXPECT_EQ("192.0.2.128/28", pool->stringValue());
}

// Verifies that canonizePool adds two spaces from a range.
TEST(AdaptorPoolTest, canonizePoolRangeNoSpace) {
    string config = "{\n"
        " \"pool\": \"192.0.2.1-192.0.2.200\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorPool::canonizePool(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr pool = json->get("pool");
    ASSERT_TRUE(pool);
    ASSERT_EQ(Element::string, pool->getType());
    EXPECT_EQ("192.0.2.1 - 192.0.2.200", pool->stringValue());
}

// Verifies that canonizePool removes extra spaces from a range.
TEST(AdaptorPoolTest, canonizePoolRangeExtraSpaces) {
    string config = "{\n"
        " \"pool\": \"192.0.2.1  -  192.0.2.200\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW(AdaptorPool::canonizePool(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr pool = json->get("pool");
    ASSERT_TRUE(pool);
    ASSERT_EQ(Element::string, pool->getType());
    EXPECT_EQ("192.0.2.1 - 192.0.2.200", pool->stringValue());
}

// Verifies that fromSubnet is specific to ietf-dhcpv6-server model.
TEST(AdaptorPoolTest, fromSubnetKea) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"pools\": [\n"
        "     {\n"
        "         \"pool\": \"192.0.2.1 - 192.0.2.100\"\n"
        "     },{\n"
        "         \"pool\": \"192.0.2.101 - 192.0.2.200\"\n"
        "     } ],\n"
        " \"valid-lifetime\": 4000,\n"
        " \"renew-timer\": 1000,\n"
        " \"rebind-timer\": 2000\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ConstElementPtr pools = json->get("pools");

    // This should be no-op for kea-dhcp4-server and kea-dhcp6-server models
    EXPECT_NO_THROW(AdaptorPool::fromSubnet(KEA_DHCP4_SERVER, json, pools));
    EXPECT_TRUE(copied->equals(*json));
    // The model is checked first.
    EXPECT_NO_THROW(AdaptorPool::fromSubnet(KEA_DHCP6_SERVER, json, pools));
    EXPECT_TRUE(copied->equals(*json));

    // Check that the model name is actually checked.
    EXPECT_THROW(AdaptorPool::fromSubnet("non-existent-module", json, pools),
                 NotImplemented);
}

// Verifies that fromSubnet works as expected.
TEST(AdaptorPoolTest, fromSubnet) {
    string config = "{\n"
        " \"subnet\": \"2001:db8:1::/64\",\n"
        " \"pools\": [\n"
        "     {\n"
        "         \"pool\": \"2001:db8:1::/80\"\n"
        "     },{\n"
        "         \"pool\": \"2001:db8:1:0:1::/80\"\n"
        "     } ],\n"
        " \"preferred-lifetime\": 3000,\n"
        " \"valid-lifetime\": 4000,\n"
        " \"renew-timer\": 1000,\n"
        " \"rebind-timer\": 2000\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ConstElementPtr pools = json->get("pools");
    EXPECT_NO_THROW(AdaptorPool::fromSubnet(IETF_DHCPV6_SERVER, json, pools));
    EXPECT_FALSE(copied->equals(*json));
    pools = json->get("pools");
    ASSERT_TRUE(pools);
    ASSERT_EQ(2, pools->size());
    ConstElementPtr pool = pools->get(0);
    ASSERT_TRUE(pool);
    string expected = "{"
        " \"pool\": \"2001:db8:1::/80\","
        " \"preferred-lifetime\": 3000,"
        " \"rebind-timer\": 2000,"
        " \"renew-timer\": 1000,"
        " \"valid-lifetime\": 4000 }";
    EXPECT_EQ(expected, pool->str());
    pool = pools->get(1);
    ASSERT_TRUE(pool);
    expected = "{"
        " \"pool\": \"2001:db8:1:0:1::/80\","
        " \"preferred-lifetime\": 3000,"
        " \"rebind-timer\": 2000,"
        " \"renew-timer\": 1000,"
        " \"valid-lifetime\": 4000 }";
    EXPECT_EQ(expected, pool->str());
}

// Verifies that toSubnet is specific to ietf-dhcpv6-server model.
TEST(AdaptorPoolTest, toSubnetKea) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"pools\": [\n"
        "     {\n"
        "         \"pool\": \"192.0.2.1 - 192.0.2.100\"\n"
        "     },{\n"
        "         \"pool\": \"192.0.2.101 - 192.0.2.200\"\n"
        "     } ],\n"
        " \"valid-lifetime\": 4000,\n"
        " \"renew-timer\": 1000,\n"
        " \"rebind-timer\": 2000\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ConstElementPtr pools = json->get("pools");
    EXPECT_NO_THROW(AdaptorPool::toSubnet(KEA_DHCP4_SERVER, json, pools));
    EXPECT_TRUE(copied->equals(*json));
    // The model is checked first.
    EXPECT_NO_THROW(AdaptorPool::toSubnet(KEA_DHCP6_SERVER, json, pools));
    EXPECT_TRUE(copied->equals(*json));
    // Model name is not free: an error is raised if it is not expected.
    EXPECT_THROW(AdaptorPool::toSubnet("keatest-module", json, pools),
                 NotImplemented);
}

// Verifies that toSubnet works as expected.
TEST(AdaptorPoolTest, toSubnet) {
    string config = "{\n"
        " \"subnet\": \"2001:db8:1::/64\",\n"
        " \"pools\": [\n"
        "     {\n"
        "         \"pool\": \"2001:db8:1::/80\",\n"
        "         \"preferred-lifetime\": 3000,\n"
        "         \"valid-lifetime\": 4000,\n"
        "         \"renew-timer\": 1000,\n"
        "         \"rebind-timer\": 2000\n"
        "     },{\n"
        "         \"pool\": \"2001:db8:1:0:1::/80\",\n"
        "         \"preferred-lifetime\": 3000,\n"
        "         \"valid-lifetime\": 4000,\n"
        "         \"renew-timer\": 1000,\n"
        "         \"rebind-timer\": 2000\n"
        "     } ]\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ConstElementPtr pools = json->get("pools");
    EXPECT_NO_THROW(AdaptorPool::toSubnet(IETF_DHCPV6_SERVER, json, pools));
    EXPECT_FALSE(copied->equals(*json));
    // Check timers.
    ConstElementPtr timer = json->get("valid-lifetime");
    ASSERT_TRUE(timer);
    EXPECT_EQ("4000", timer->str());
    timer = json->get("preferred-lifetime");
    ASSERT_TRUE(timer);
    EXPECT_EQ("3000", timer->str());
    timer = json->get("renew-timer");
    ASSERT_TRUE(timer);
    EXPECT_EQ("1000", timer->str());
    timer = json->get("rebind-timer");
    ASSERT_TRUE(timer);
    EXPECT_EQ("2000", timer->str());
    // Timers must be removed as they are not allowed here in Kea.
    pools = json->get("pools");
    ASSERT_TRUE(pools);
    ASSERT_EQ(2, pools->size());
    ConstElementPtr pool = pools->get(0);
    ASSERT_TRUE(pool);
    EXPECT_EQ("{ \"pool\": \"2001:db8:1::/80\" }", pool->str());
    pool = pools->get(1);
    ASSERT_TRUE(pool);
    EXPECT_EQ("{ \"pool\": \"2001:db8:1:0:1::/80\" }", pool->str());
}

// Verifies that toSubnet fails on inconsistent input.
TEST(AdaptorPoolTest, toSubnetBad) {
    // Changed last rebind-timer to a different value.
    string config = "{\n"
        " \"subnet\": \"2001:db8:1::/64\",\n"
        " \"pools\": [\n"
        "     {\n"
        "         \"pool\": \"2001:db8:1::/80\",\n"
        "         \"preferred-lifetime\": 3000,\n"
        "         \"valid-lifetime\": 4000,\n"
        "         \"renew-timer\": 1000,\n"
        "         \"rebind-timer\": 2000\n"
        "     },{\n"
        "         \"pool\": \"2001:db8:1:0:1::/80\",\n"
        "         \"preferred-lifetime\": 3000,\n"
        "         \"valid-lifetime\": 4000,\n"
        "         \"renew-timer\": 1000,\n"
        "         \"rebind-timer\": 20\n"
        "     } ]\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr pools = json->get("pools");
    EXPECT_THROW(AdaptorPool::toSubnet(IETF_DHCPV6_SERVER, json, pools),
                 BadValue);
}

}; // end of anonymous namespace
