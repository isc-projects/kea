// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_shared_network.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;

namespace {

/// @brief Translator name.
extern char const shared_networks[] = "shared networks";

/// @brief Test fixture class for @ref TranslatorSharedNetworks.
class TranslatorSharedNetworksTest :
    public GenericTranslatorTest<shared_networks, TranslatorSharedNetworks> {
public:

    /// Constructor.
    TranslatorSharedNetworksTest() { }

    /// Destructor (does nothing).
    virtual ~TranslatorSharedNetworksTest() { }
};

// This test verifies that an empty shared network list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorSharedNetworksTest, getEmpty) {
    useModel(KEA_DHCP4_SERVER);

    // Get the shared network list and check if it is empty.
    const string& xpath = "/kea-dhcp4-server:config/shared-networks";
    ConstElementPtr networks;
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_TRUE(networks);
    ASSERT_EQ(Element::list, networks->getType());
    EXPECT_EQ(0, networks->size());
}

// This test verifies that one shared network can be properly
// translated from YANG to JSON.
TEST_F(TranslatorSharedNetworksTest, get) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111 in shared network foo.
    const string& xpath = "/kea-dhcp6-server:config/shared-networks";
    const string& xnetwork = xpath + "/shared-network[name='foo']";
    const string& xsubnet = xnetwork + "/subnet6/subnet6[id='111']/subnet";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Get the shared network.
    ConstElementPtr network;
    EXPECT_NO_THROW(network = t_obj_->getSharedNetwork(xnetwork));
    ASSERT_TRUE(network);
    ElementPtr subnet = Element::createMap();
    subnet->set("id", Element::create(111));
    subnet->set("subnet", Element::create(string("2001:db8::/48")));
    ElementPtr subnets = Element::createList();
    subnets->add(subnet);
    ElementPtr expected = Element::createMap();
    expected->set("name", Element::create(string("foo")));
    expected->set("subnet6", subnets);
    EXPECT_TRUE(expected->equals(*network));

    // Get the shared network list and check if the shared network is in it.
    ConstElementPtr networks;
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_TRUE(networks);
    ASSERT_EQ(Element::list, networks->getType());
    ASSERT_EQ(1, networks->size());
    EXPECT_TRUE(network->equals(*networks->get(0)));
}

// This test verifies that an empty shared network list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorSharedNetworksTest, setEmpty) {
    useModel(KEA_DHCP4_SERVER);

    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config/shared-networks";
    ConstElementPtr networks = Element::createList();
    EXPECT_NO_THROW(t_obj_->setSharedNetworks(xpath, networks));

    // Get it back.
    networks.reset();
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_TRUE(networks);
    ASSERT_EQ(Element::list, networks->getType());
    EXPECT_EQ(0, networks->size());

    // Check that the tree representation is empty.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp4-server:config"));
    EXPECT_FALSE(tree);
}

// This test verifies that one shared network can be properly
// translated from JSON to YANG.
TEST_F(TranslatorSharedNetworksTest, set) {
    useModel(KEA_DHCP6_SERVER);

    // Set one shared network.
    const string& xpath = "/kea-dhcp6-server:config/shared-networks";
    ElementPtr networks = Element::createList();
    ElementPtr share = Element::createMap();
    ElementPtr subnets = Element::createList();
    ElementPtr subnet = Element::createMap();
    subnet->set("subnet", Element::create(string("2001:db8::/48")));
    subnet->set("id", Element::create(123));
    subnets->add(subnet);
    share->set("name", Element::create(string("foo")));
    share->set("subnet6", subnets);
    networks->add(share);
    EXPECT_NO_THROW(t_obj_->setSharedNetworks(xpath, networks));

    // Get it back.
    networks.reset();
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_TRUE(networks);
    ASSERT_EQ(Element::list, networks->getType());
    ASSERT_EQ(1, networks->size());
    EXPECT_TRUE(share->equals(*networks->get(0)));

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp6-server:config"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp6-server:config (container)\n"
        " |\n"
        " -- shared-networks (container)\n"
        "     |\n"
        "     -- shared-network (list instance)\n"
        "         |\n"
        "         -- name = foo\n"
        "         |\n"
        "         -- subnet6 (container)\n"
        "             |\n"
        "             -- subnet6 (list instance)\n"
        "                 |\n"
        "                 -- id = 123\n"
        "                 |\n"
        "                 -- subnet = 2001:db8::/48\n";
    EXPECT_EQ(expected, tree->to_string(100));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}; // end of anonymous namespace
