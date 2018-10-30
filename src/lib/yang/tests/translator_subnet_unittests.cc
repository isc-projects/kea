// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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
#ifndef HAVE_OLD_SYSREPO
using namespace sysrepo;
#endif

namespace {

/// @brief Translator name.
extern char const subnet_list[] = "subnet list";

/// @brief Test fixture class for @ref TranslatorSubnets.
class TranslatorSubnetsTest :
    public GenericTranslatorTest<subnet_list, TranslatorSubnets> {
public:

    /// Constructor.
    TranslatorSubnetsTest() { }

    /// Destructor (does nothing).
    virtual ~TranslatorSubnetsTest() { }
};

// This test verifies that an empty subnet list can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorSubnetsTest, getEmptyIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Get the subnet list and check if it is empty.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    EXPECT_EQ(0, subnets->size());
}

// This test verifies that an empty subnet list can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorSubnetsTest, getEmptyKea) {
    useModel(KEA_DHCP6_SERVER);

    // Get the subnet list and check if it is empty.
    const string& xpath = "/kea-dhcp6-server:config/subnet6";
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    EXPECT_EQ(0, subnets->size());
}

// This test verifies that one subnet can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorSubnetsTest, getIetf) {
    useModel(IETF_DHCPV6_SERVER);

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
    EXPECT_EQ("{ \"id\": 111, \"pools\": [  ], "
              "\"subnet\": \"2001:db8::/48\" }",
              subnet->str());

    // Get the subnet list and check if the subnet is in it.
    ConstElementPtr subnets;
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    ASSERT_EQ(1, subnets->size());
    EXPECT_TRUE(subnet->equals(*subnets->get(0)));
}

// This test verifies that one subnet can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorSubnetsTest, getKea) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& xpath = "/kea-dhcp6-server:config/subnet6";
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
TEST_F(TranslatorSubnetsTest, getPoolsIetf) {
    useModel(IETF_DHCPV6_SERVER);

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

    // Uncomment this for debugging.
    // S_Tree tree = sess_->get_subtree("/ietf-dhcpv6-server:server");
    // cerr << "tree:\n" << tree->to_string(100) << "\n";

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
TEST_F(TranslatorSubnetsTest, getPoolsKea) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& xpath = "/kea-dhcp6-server:config/subnet6";
    const string& xsub = xpath + "/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = xsub + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Create the pool 2001:db8::1:0/112.
    const string& xpool = xsub + "/pools";
    const string& prefix1 = xpool + "/pool[start-address='2001:db8::1:0']" +
        "[end-address='2001:db8::1:ffff']/prefix";
    S_Val s_pool1(new Val("2001:db8::1:0/112", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(prefix1.c_str(), s_pool1));

    // Create the pool 2001:db8::2:0/112.
    const string& prefix2 = xpool + "/pool[start-address='2001:db8::2:0']" +
        "[end-address='2001:db8::2:ffff']";
    S_Val s_pool2;
    EXPECT_NO_THROW(sess_->set_item(prefix2.c_str(), s_pool2));

    // Uncomment this for debugging.
    // S_Tree tree = sess_->get_subtree("/kea-dhcp6-server:config");
    // cerr << "tree:\n" << tree->to_string(100) << "\n";

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
TEST_F(TranslatorSubnetsTest, setEmptyIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Set empty list.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ConstElementPtr subnets = Element::createList();
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    EXPECT_EQ(0, subnets->size());

    // Check that the tree representation is empty.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/ietf-dhcpv6-server:server"));
    EXPECT_FALSE(tree);
}

// This test verifies that an empty subnet list can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorSubnetsTest, setEmptyKea) {
    useModel(KEA_DHCP4_SERVER);

    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config/subnet4";
    ElementPtr subnets = Element::createList();
    EXPECT_NO_THROW(t_obj_->setSubnets(xpath, subnets));

    // Get it back.
    subnets.reset();
    EXPECT_NO_THROW(subnets = t_obj_->getSubnets(xpath));
    ASSERT_TRUE(subnets);
    ASSERT_EQ(Element::list, subnets->getType());
    EXPECT_EQ(0, subnets->size());

    // Check that the tree representation is empty.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp4-server:config"));
    EXPECT_FALSE(tree);
}

// This test verifies that one subnet can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorSubnetsTest, setIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Set one subnet.
    const string& xpath =
        "/ietf-dhcpv6-server:server/server-config/network-ranges";
    ElementPtr subnets = Element::createList();
    ElementPtr subnet = Element::createMap();
    subnet->set("subnet", Element::create(string("2001:db8::/48")));
    subnet->set("id", Element::create(123));
    subnet->set("pools", Element::createList());
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
TEST_F(TranslatorSubnetsTest, setKea) {
    useModel(KEA_DHCP4_SERVER);

    // Set one subnet.
    const string& xpath = "/kea-dhcp4-server:config/subnet4";
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
TEST_F(TranslatorSubnetsTest, setTwoIetf) {
    useModel(IETF_DHCPV6_SERVER);

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

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/ietf-dhcpv6-server:server"));
    ASSERT_TRUE(tree);
    string expected =
        "ietf-dhcpv6-server:server (container)\n"
        " |\n"
        " -- server-config (container)\n"
        "     |\n"
        "     -- network-ranges (container)\n"
        "         |\n"
        "         -- network-range (list instance)\n"
        "             |\n"
        "             -- network-range-id = 123\n"
        "             |\n"
        "             -- network-prefix = 2001:db8::/48\n"
        "             |\n"
        "             -- address-pools (container)\n"
        "                 |\n"
        "                 -- address-pool (list instance)\n"
        "                 |   |\n"
        "                 |   -- pool-id = 0\n"
        "                 |   |\n"
        "                 |   -- pool-prefix = 2001:db8::1:0/112\n"
        "                 |   |\n"
        "                 |   -- start-address = 2001:db8::1:0\n"
        "                 |   |\n"
        "                 |   -- end-address = 2001:db8::1:ffff\n"
        "                 |   |\n"
        "                 |   -- max-address-count = disabled\n"
        "                 |\n"
        "                 -- address-pool (list instance)\n"
        "                     |\n"
        "                     -- pool-id = 1\n"
        "                     |\n"
        "                     -- pool-prefix = 2001:db8::2:0/112\n"
        "                     |\n"
        "                     -- start-address = 2001:db8::2:0\n"
        "                     |\n"
        "                     -- end-address = 2001:db8::2:ffff\n"
        "                     |\n"
        "                     -- max-address-count = disabled\n";
    EXPECT_EQ(expected, tree->to_string(100));
}

// This test verifies that one subnet with two pools can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorSubnetsTest, setTwoKea) {
    useModel(KEA_DHCP4_SERVER);

    // Set one subnet.
    const string& xpath = "/kea-dhcp4-server:config/subnet4";
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

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp4-server:config"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp4-server:config (container)\n"
        " |\n"
        " -- subnet4 (container)\n"
        "     |\n"
        "     -- subnet4 (list instance)\n"
        "         |\n"
        "         -- id = 123\n"
        "         |\n"
        "         -- pools (container)\n"
        "         |   |\n"
        "         |   -- pool (list instance)\n"
        "         |   |   |\n"
        "         |   |   -- start-address = 10.0.1.0\n"
        "         |   |   |\n"
        "         |   |   -- end-address = 10.0.1.15\n"
        "         |   |   |\n"
        "         |   |   -- prefix = 10.0.1.0/28\n"
        "         |   |\n"
        "         |   -- pool (list instance)\n"
        "         |       |\n"
        "         |       -- start-address = 10.0.1.200\n"
        "         |       |\n"
        "         |       -- end-address = 10.0.1.222\n"
        "         |\n"
        "         -- subnet = 10.0.1.0/24\n";
    EXPECT_EQ(expected, tree->to_string(100));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}; // end of anonymous namespace
