// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/adaptor_subnet.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::yang;

namespace {

// Verifies how collectID handles a subnet entry without ID.
TEST(AdaptorSubnetTest, collectNoId) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\"\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    SubnetIDSet set;
    bool ret = true;
    ASSERT_NO_THROW_LOG(ret = AdaptorSubnet::collectID(json, set));
    EXPECT_FALSE(ret);
    EXPECT_EQ(0, set.size());
}

// Verifies how collectID handles a subnet entry with an ID.
TEST(AdaptorSubnetTest, collectId) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"id\": 123\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    SubnetIDSet set;
    bool ret = false;
    ASSERT_NO_THROW_LOG(ret = AdaptorSubnet::collectID(json, set));
    EXPECT_TRUE(ret);
    EXPECT_EQ(1, set.size());
    EXPECT_EQ(1, set.count(123));
}

// Verifies how collectID handles a subnet entry with an ID which is
// already known: the set is not updated.
TEST(AdaptorSubnetTest, collectKnownId) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"id\": 123\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    SubnetIDSet set = { 123 };
    bool ret = false;
    ASSERT_NO_THROW_LOG(ret = AdaptorSubnet::collectID(json, set));
    EXPECT_TRUE(ret);
    EXPECT_EQ(1, set.size());
    EXPECT_EQ(1, set.count(123));
}

// Verifies how assignID handles a subnet entry without ID: the next ID
// is assigned, the set is updated and the next ID is incremented.
TEST(AdaptorSubnetTest, assignNoId) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    SubnetIDSet set;
    SubnetID next_id = 123;
    ASSERT_NO_THROW_LOG(AdaptorSubnet::assignID(json, set, next_id));
    EXPECT_FALSE(copied->equals(*json));
    EXPECT_EQ(1, set.size());
    EXPECT_EQ(1, set.count(123));
    EXPECT_EQ(124, next_id);
    ConstElementPtr id = json->get("id");
    ASSERT_TRUE(id);
    ASSERT_EQ(Element::integer, id->getType());
    EXPECT_EQ(123, id->intValue());
}

// Verifies how assignID handles a subnet entry without ID but with the
// candidate ID already used: the used value is skipped.
TEST(AdaptorSubnetTest, assignNoIdUsed) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    SubnetIDSet set = { 123 };
    SubnetID next_id = 123;
    ASSERT_NO_THROW_LOG(AdaptorSubnet::assignID(json, set, next_id));
    EXPECT_FALSE(copied->equals(*json));
    EXPECT_EQ(2, set.size());
    EXPECT_EQ(1, set.count(123));
    EXPECT_EQ(1, set.count(124));
    EXPECT_EQ(125, next_id);
    ConstElementPtr id = json->get("id");
    ASSERT_TRUE(id);
    ASSERT_EQ(Element::integer, id->getType());
    EXPECT_EQ(124, id->intValue());
}

// Verifies how assignID handles a subnet entry with ID: no change.
TEST(AdaptorSubnetTest, assignId) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"id\": 123\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    SubnetIDSet set; // ignored.
    SubnetID next_id = 123; // ignored.
    ASSERT_NO_THROW_LOG(AdaptorSubnet::assignID(json, set, next_id));
    EXPECT_TRUE(copied->equals(*json));
    EXPECT_EQ(0, set.size());
    EXPECT_EQ(123, next_id);
}

// Verifies how updateRelay handles a subnet entry without relay: no change.
TEST(AdaptorSubnetTest, updateNoRelay) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ASSERT_NO_THROW_LOG(AdaptorSubnet::updateRelay(json));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies how updateRelay handles a subnet entry with empty relay:
// the relay entry is useless and removed.
TEST(AdaptorSubnetTest, updateEmptyRelay) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"relay\": { }\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ASSERT_NO_THROW_LOG(AdaptorSubnet::updateRelay(json));
    EXPECT_FALSE(copied->equals(*json));
    EXPECT_FALSE(json->get("relay"));
}

// Verifies how updateRelay handles a subnet entry with relay which
// has empty addresses: the relay entry is useless and removed.
TEST(AdaptorSubnetTest, updateRelayEmptyAddresses) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"relay\": {\n"
        "     \"ip-addresses\": [ ]\n"
        " }\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ASSERT_NO_THROW_LOG(AdaptorSubnet::updateRelay(json));
    EXPECT_FALSE(copied->equals(*json));
    EXPECT_FALSE(json->get("relay"));
}

// Verifies how updateRelay handles a subnet entry with relay which
// has addresses: no change.
TEST(AdaptorSubnetTest, updateRelayAddresses) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"relay\": {\n"
        "     \"ip-addresses\": [ \"192.168.1.1\" ]\n"
        " }\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ASSERT_NO_THROW_LOG(AdaptorSubnet::updateRelay(json));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies how updateRelay handles a subnet entry with relay which
// has only address: the address is moved to a new list.
TEST(AdaptorSubnetTest, updateRelayAddress) {
    string config = "{\n"
        " \"subnet\": \"192.0.2.0/24\",\n"
        " \"relay\": {\n"
        "     \"ip-address\": \"192.168.1.1\"\n"
        " }\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    ASSERT_NO_THROW_LOG(AdaptorSubnet::updateRelay(json));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr relay = json->get("relay");
    ASSERT_TRUE(relay);
    string expected = "{ \"ip-addresses\": [ \"192.168.1.1\" ] }";
    EXPECT_EQ(expected, relay->str());
}

// It does not make sense to have both ip-address and ip-addresses...

}; // end of anonymous namespace
