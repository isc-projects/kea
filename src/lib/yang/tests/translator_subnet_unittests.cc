// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_subnet.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const subnet_list[] = "subnet list";

/// @brief Test fixture class for @ref TranslatorSubnets.
class TranslatorSubnetsTestKeaV4 :
    public GenericTranslatorTest<subnet_list, TranslatorSubnets> {
public:

    /// Constructor.
    TranslatorSubnetsTestKeaV4() {
        model_ = KEA_DHCP4_SERVER;
    }
};
class TranslatorSubnetsTestKeaV6 :
    public GenericTranslatorTest<subnet_list, TranslatorSubnets> {
public:

    /// Constructor.
    TranslatorSubnetsTestKeaV6() {
        model_ = KEA_DHCP6_SERVER;
    }
};
class TranslatorSubnetsTestIetfV6 :
    public GenericTranslatorTest<subnet_list, TranslatorSubnets> {
public:

    /// Constructor.
    TranslatorSubnetsTestIetfV6() {
        model_ = IETF_DHCPV6_SERVER;
    }
};

// This test verifies that an empty subnet list can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorSubnetsTestIetfV6, getEmptyIetf) {
    // Get the subnet list and check if it is empty.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_FALSE(subnets);
}

// This test verifies that an empty subnet list can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorSubnetsTestKeaV6, getEmptyKea) {
    // Get the subnet list and check if it is empty.
    const string& xpath = "/kea-dhcp6-server:config";
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_FALSE(subnets);
}

// This test verifies that one subnet can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorSubnetsTestIetfV6, getIetf) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    const string& xsub = xpath + "/network-range[network-range-id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = xsub + "/network-prefix";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Get the subnet.
    ConstElementPtr subnet;
    EXPECT_NO_THROW(subnet = t_obj_->getSubnet(xsub));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("{ \"id\": 111, "
              "\"subnet\": \"2001:db8::/48\" }",
              subnet->str());

    // Get the subnet list and check if the subnet is in it.
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    ASSERT_TRUE(subnets->get(0));
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that one subnet can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorSubnetsTestKeaV6, getKea) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xsub = xpath + "/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = xsub + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Get the subnet.
    ConstElementPtr subnet;
    EXPECT_NO_THROW(subnet = t_obj_->getSubnet(xsub));
    ASSERT_TRUE(subnet);
    ElementPtr expected = Element::createMap();
    expected->set("id", Element::create(111));
    expected->set("subnet", Element::create(string("2001:db8::/48")));
    EXPECT_TRUE(expected->equals(*subnet));

    // Get the subnet list and check if the subnet is in it.
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that one subnet with two pools can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorSubnetsTestIetfV6, getPoolsIetf) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    const string& xsub = xpath + "/network-range[network-range-id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = xsub + "/network-prefix";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Create the pool 2001:db8::1:0/112 #1.
    const string& xpool = xsub + "/address-pools";
    const string& prefix1 = xpool + "/address-pool[pool-id='1']/pool-prefix";
    S_Val s_pool1(new Val("2001:db8::1:0/112"));
    EXPECT_NO_THROW(sess_->set_item(prefix1.c_str(), s_pool1));

    // Create the pool 2001:db8::2:0/112 #2.
    const string& prefix2 = xpool + "/address-pool[pool-id='2']/pool-prefix";
    S_Val s_pool2(new Val("2001:db8::2:0/112"));
    EXPECT_NO_THROW(sess_->set_item(prefix2.c_str(), s_pool2));

    // Get the subnet.
    ConstElementPtr subnet;
    EXPECT_NO_THROW(subnet = t_obj_->getSubnet(xsub));
    ASSERT_TRUE(subnet);
    string expected =
        "{\n"
        "  \"id\": 111,\n"
        "  \"pools\": [\n"
        "    {\n"
        "      \"pool\": \"2001:db8::1:0/112\"\n"
        "    },\n"
        "    {\n"
        "      \"pool\": \"2001:db8::2:0/112\"\n"
        "    }\n"
        "  ],\n"
        "  \"subnet\": \"2001:db8::/48\"\n"
        "}";
    EXPECT_EQ(expected, prettyPrint(subnet));

    // Get the subnet list and check if the subnet is in it.
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that one subnet with two pools can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorSubnetsTestKeaV6, getPoolsKea) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xsub = xpath + "/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = xsub + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Create the pool 2001:db8::1:0/112.
    const string& prefix1 = xsub + "/pool[start-address='2001:db8::1:0']" +
        "[end-address='2001:db8::1:ffff']/prefix";
    S_Val s_pool1(new Val("2001:db8::1:0/112", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(prefix1.c_str(), s_pool1));

    // Create the pool 2001:db8::2:0/112.
    const string& prefix2 = xsub + "/pool[start-address='2001:db8::2:0']" +
        "[end-address='2001:db8::2:ffff']";
    S_Val s_pool2;
    EXPECT_NO_THROW(sess_->set_item(prefix2.c_str(), s_pool2));

    // Get the subnet.
    ConstElementPtr subnet;
    EXPECT_NO_THROW(subnet = t_obj_->getSubnet(xsub));
    ASSERT_TRUE(subnet);
    string expected =
        "{\n"
        "  \"id\": 111,\n"
        "  \"pools\": [\n"
        "    {\n"
        "      \"pool\": \"2001:db8::1:0/112\"\n"
        "    },\n"
        "    {\n"
        "      \"pool\": \"2001:db8::2:0 - 2001:db8::2:ffff\"\n"
        "    }\n"
        "  ],\n"
        "  \"subnet\": \"2001:db8::/48\"\n"
        "}";
    EXPECT_EQ(expected, prettyPrint(subnet));

    // Get the subnet list and check if the subnet is in it.
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that an empty subnet list can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorSubnetsTestIetfV6, setEmptyIetf) {
    // Set empty list.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ConstElementPtr subnets = Element::createList();
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_FALSE(subnets);
}

// This test verifies that an empty subnet list can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorSubnetsTestKeaV4, setEmptyKea) {
    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config";
    ElementPtr subnets = Element::createList();
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_FALSE(subnets);
}

// This test verifies that one subnet can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorSubnetsTestIetfV6, setIetf) {
    // Set one subnet.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ElementPtr subnets = Element::createList();
    ElementPtr subnet = Element::createMap();
    subnet->set("subnet", Element::create(string("2001:db8::/48")));
    subnet->set("id", Element::create(123));
    subnets->add(subnet);
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that one subnet can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorSubnetsTestKeaV4, setKea) {
    // Set one subnet.
    const string& xpath = "/kea-dhcp4-server:config";
    ElementPtr subnets = Element::createList();
    ElementPtr subnet = Element::createMap();
    subnet->set("subnet", Element::create(string("10.0.1.0/24")));
    subnet->set("id", Element::create(123));
    subnets->add(subnet);
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

// This test verifies that one subnet with two pools can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorSubnetsTestIetfV6, setTwoIetf) {
    // Set one subnet.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ElementPtr subnets = Element::createList();
    ElementPtr subnet = Element::createMap();
    subnet->set("subnet", Element::create(string("2001:db8::/48")));
    subnet->set("id", Element::create(123));

    // Add two pools.
    ElementPtr pools = Element::createList();
    ElementPtr pool1 = Element::createMap();
    pool1->set("pool", Element::create(string("2001:db8::1:0/112")));
    pools->add(pool1);
    ElementPtr pool2 = Element::createMap();
    pool2->set("pool", Element::create(string("2001:db8::2:0/112")));
    pools->add(pool2);
    subnet->set("pools", pools);

    // Add the subnet.
    subnets->add(subnet);
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that one subnet with two pools can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorSubnetsTestKeaV4, setTwoKea) {
    // Set one subnet.
    const string& xpath = "/kea-dhcp4-server:config";
    ElementPtr subnets = Element::createList();
    ElementPtr subnet = Element::createMap();
    subnet->set("subnet", Element::create(string("10.0.1.0/24")));
    subnet->set("id", Element::create(123));

    // Add two pools.
    ElementPtr pools = Element::createList();
    ElementPtr pool1 = Element::createMap();
    pool1->set("pool", Element::create(string("10.0.1.0/28")));
    pools->add(pool1);
    ElementPtr pool2 = Element::createMap();
    pool2->set("pool", Element::create(string("10.0.1.200 - 10.0.1.222")));
    pools->add(pool2);
    subnet->set("pools", pools);

    // Add the subnet.
    subnets->add(subnet);
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}  // namespace
