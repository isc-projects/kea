// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const shared_networks[] = "shared networks";

/// @brief Test fixture class for @ref TranslatorSharedNetworks.
class TranslatorSharedNetworksTestKeaV4 :
    public GenericTranslatorTest<shared_networks, TranslatorSharedNetworks> {
public:

    /// Constructor.
    TranslatorSharedNetworksTestKeaV4() {
        model_ = KEA_DHCP4_SERVER;
    }
};
class TranslatorSharedNetworksTestKeaV6 :
    public GenericTranslatorTest<shared_networks, TranslatorSharedNetworks> {
public:

    /// Constructor.
    TranslatorSharedNetworksTestKeaV6() {
        model_ = KEA_DHCP6_SERVER;
    }
};

// This test verifies that an empty shared network list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorSharedNetworksTestKeaV4, getEmpty) {
    // Get the shared network list and check if it is empty.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr networks;
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_FALSE(networks);
}

// This test verifies that one shared network can be properly
// translated from YANG to JSON.
TEST_F(TranslatorSharedNetworksTestKeaV6, get) {
    // Create the subnet 2001:db8::/48 #111 in shared network foo.
    const string& xpath = "/kea-dhcp6-server:config";
    const string& xnetwork = xpath + "/shared-network[name='foo']";
    const string& xsubnet = xnetwork + "/subnet6[id='111']/subnet";
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
TEST_F(TranslatorSharedNetworksTestKeaV4, setEmpty) {
    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config";
    ConstElementPtr networks = Element::createList();
    EXPECT_NO_THROW(t_obj_->setSharedNetworks(xpath, networks));

    // Get it back.
    networks.reset();
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_FALSE(networks);
}

// This test verifies that one shared network can be properly
// translated from JSON to YANG.
TEST_F(TranslatorSharedNetworksTestKeaV6, set) {
    // Set one shared network.
    const string& xpath = "/kea-dhcp6-server:config";
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

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

// This test verifies that several shared networks can be properly
// translated from YANG to JSON. This test adds the following structure:
//
// shared-network "foo":
//   - subnet1: 2001:db8:1::/48 (subnet-id 1)
//   - subnet1: 2001:db8:2::/48 (subnet-id 2)
// shared-network "bar":
//   - subnet1: 2001:db8:101::/48 (subnet-id 101)
//   - subnet1: 2001:db8:102::/48 (subnet-id 102)
TEST_F(TranslatorSharedNetworksTestKeaV6, getList) {
    const string& xpath = "/kea-dhcp6-server:config";

    // Those two networks will be added.
    const string& xnetwork1 = xpath + "/shared-network[name='foo']";
    const string& xnetwork2 = xpath + "/shared-network[name='bar']";

    // Non-existent network
    const string& xnetwork3 = xpath + "/shared-network[name='baz']";

    const string& exp_net1 =
        "{ \"name\": \"foo\", \"subnet6\": [ { \"id\": 1, "
        "\"subnet\": \"2001:db8:1::/48\" }, "
        "{ \"id\": 2, \"subnet\": \"2001:db8:2::/48\" } ] }";

    const string& exp_net2 =
        "{ \"name\": \"bar\", \"subnet6\": [ { \"id\": 101, "
        "\"subnet\": \"2001:db8:101::/48\" }, "
        "{ \"id\": 102, \"subnet\": \"2001:db8:102::/48\" } ] }";

    const string exp_both =
        "[ " + exp_net1 + ", " + exp_net2 + " ]";

    // Create the subnet1: 2001:db8:1::/48 #1 in shared network foo.
    const string& xsubnet1 = xnetwork1 + "/subnet6[id='1']/subnet";
    S_Val v_subnet1(new Val("2001:db8:1::/48", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(xsubnet1.c_str(), v_subnet1));

    // Create the subnet2: 2001:db8:2::/48 #2 in shared network foo.
    const string& xsubnet2 = xnetwork1 + "/subnet6[id='2']/subnet";
    S_Val v_subnet2(new Val("2001:db8:2::/48", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(xsubnet2.c_str(), v_subnet2));

    // Create the subnet1: 2001:db8:101::/48 #101 in shared network foo.
    const string& xsubnet3 = xnetwork2 + "/subnet6[id='101']/subnet";
    S_Val v_subnet(new Val("2001:db8:101::/48", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(xsubnet3.c_str(), v_subnet));

    // Create the subnet2: 2001:db8:2::/48 #2 in shared network foo.
    const string& xsubnet4 = xnetwork2 + "/subnet6[id='102']/subnet";
    S_Val v_subnet4(new Val("2001:db8:102::/48", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(xsubnet4.c_str(), v_subnet4));

    // Ok, now test the getters. Let's start with the easier ones that
    // return a single network.
    ConstElementPtr network;

    // Get the first network.
    EXPECT_NO_THROW(network = t_obj_->getSharedNetwork(xnetwork1));
    ASSERT_TRUE(network);
    EXPECT_EQ(exp_net1, network->str());

    // Get the second network.
    EXPECT_NO_THROW(network = t_obj_->getSharedNetwork(xnetwork2));
    ASSERT_TRUE(network);
    EXPECT_EQ(exp_net2, network->str());

    // Check that networks with non-existent name are not returned.
    EXPECT_THROW(network = t_obj_->getSharedNetwork(xnetwork3), Unexpected);

    // Now test returns all networks
    ConstElementPtr networks;
    EXPECT_NO_THROW(networks = t_obj_->getSharedNetworks(xpath));
    ASSERT_TRUE(networks);
    EXPECT_EQ(exp_both, networks->str());
}

}  // namespace
