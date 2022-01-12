// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/classify.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_string.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/cfg_hosts.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <util/doubles.h>

#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief Generates interface id option.
///
/// @param text Interface id in a textual format.
OptionPtr
generateInterfaceId(const std::string& text) {
    OptionBuffer buffer(text.begin(), text.end());
    return OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID, buffer));
}

/// @brief Verifies that a set of subnets contains a given a subnet
///
/// @param cfg_subnets set of subnets in which to look
/// @param exp_subnet_id expected id of the target subnet
/// @param prefix prefix of the target subnet
/// @param exp_valid expected valid lifetime of the subnet
/// @param exp_network  pointer to the subnet's shared-network (if one)
void checkMergedSubnet(CfgSubnets6& cfg_subnets,
                       const std::string& prefix,
                       const SubnetID exp_subnet_id,
                       int exp_valid,
                       SharedNetwork6Ptr exp_network) {
    // Look for the network by prefix.
    auto subnet = cfg_subnets.getByPrefix(prefix);
    ASSERT_TRUE(subnet) << "subnet: " << prefix << " not found";

    // Make sure we have the one we expect.
    ASSERT_EQ(exp_subnet_id, subnet->getID()) << "subnet ID is wrong";
    ASSERT_EQ(exp_valid, subnet->getValid()) << "subnetID:"
              << subnet->getID() << ", subnet valid time is wrong";

    SharedNetwork6Ptr shared_network;
    subnet->getSharedNetwork(shared_network);
    if (exp_network) {
        ASSERT_TRUE(shared_network)
            << " expected network: " << exp_network->getName() << " not found";
        ASSERT_TRUE(shared_network == exp_network) << " networks do no match";
    } else {
        ASSERT_FALSE(shared_network) << " unexpected network assignment: "
            << shared_network->getName();
    }
}

// This test verifies that specific subnet can be retrieved by specifying
// subnet identifier or subnet prefix.
TEST(CfgSubnets6Test, getSpecificSubnet) {
    CfgSubnets6 cfg;

    // Create 3 subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4,
                                   SubnetID(5)));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4,
                                   SubnetID(8)));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4,
                                   SubnetID(10)));

    // Store the subnets in a vector to make it possible to loop over
    // all configured subnets.
    std::vector<Subnet6Ptr> subnets;
    subnets.push_back(subnet1);
    subnets.push_back(subnet2);
    subnets.push_back(subnet3);

    // Add all subnets to the configuration.
    for (auto subnet = subnets.cbegin(); subnet != subnets.cend(); ++subnet) {
        ASSERT_NO_THROW(cfg.add(*subnet)) << "failed to add subnet with id: "
            << (*subnet)->getID();
    }

    // Iterate over all subnets and make sure they can be retrieved by
    // subnet identifier.
    for (auto subnet = subnets.rbegin(); subnet != subnets.rend(); ++subnet) {
        ConstSubnet6Ptr subnet_returned = cfg.getBySubnetId((*subnet)->getID());
        ASSERT_TRUE(subnet_returned) << "failed to return subnet with id: "
            << (*subnet)->getID();
        EXPECT_EQ((*subnet)->getID(), subnet_returned->getID());
        EXPECT_EQ((*subnet)->toText(), subnet_returned->toText());
    }

    // Repeat the previous test, but this time retrieve subnets by their
    // prefixes.
    for (auto subnet = subnets.rbegin(); subnet != subnets.rend(); ++subnet) {
        ConstSubnet6Ptr subnet_returned = cfg.getByPrefix((*subnet)->toText());
        ASSERT_TRUE(subnet_returned) << "failed to return subnet with id: "
            << (*subnet)->getID();
        EXPECT_EQ((*subnet)->getID(), subnet_returned->getID());
        EXPECT_EQ((*subnet)->toText(), subnet_returned->toText());
    }

    // Make sure that null pointers are returned for non-existing subnets.
    EXPECT_FALSE(cfg.getBySubnetId(SubnetID(123)));
    EXPECT_FALSE(cfg.getByPrefix("3000::/16"));
}

// This test verifies that a single subnet can be removed from the configuration.
TEST(CfgSubnets6Test, deleteSubnet) {
    CfgSubnets6 cfg;

    // Create 3 subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    ASSERT_NO_THROW(cfg.add(subnet1));
    ASSERT_NO_THROW(cfg.add(subnet2));
    ASSERT_NO_THROW(cfg.add(subnet3));

    // There should be three subnets.
    ASSERT_EQ(3, cfg.getAll()->size());
    // We're going to remove the subnet #2. Let's make sure it exists before
    // we remove it.
    ASSERT_TRUE(cfg.getByPrefix("2001:db8:2::/48"));

    // Remove the subnet and make sure it is gone.
    ASSERT_NO_THROW(cfg.del(subnet2));
    ASSERT_EQ(2, cfg.getAll()->size());
    EXPECT_FALSE(cfg.getByPrefix("2001:db8:2::/48"));

    // Remove another subnet by ID.
    ASSERT_NO_THROW(cfg.del(subnet1->getID()));
    ASSERT_EQ(1, cfg.getAll()->size());
    EXPECT_FALSE(cfg.getByPrefix("2001:db8:1::/48"));
}

// This test verifies that replace a subnet works as expected.
TEST(CfgSubnets6Test, replaceSubnet) {
    CfgSubnets6 cfg;

    // Create 3 subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"),
                                   48, 1, 2, 3, 100, SubnetID(10)));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"),
                                   48, 1, 2, 3, 100, SubnetID(2)));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"),
                                   48, 1, 2, 3, 100, SubnetID(13)));

    ASSERT_NO_THROW(cfg.add(subnet1));
    ASSERT_NO_THROW(cfg.add(subnet2));
    ASSERT_NO_THROW(cfg.add(subnet3));

    // There should be three subnets.
    ASSERT_EQ(3, cfg.getAll()->size());
    // We're going to replace  the subnet #2. Let's make sure it exists before
    // we replace it.
    ASSERT_TRUE(cfg.getByPrefix("2001:db8:2::/48"));

    // Replace the subnet and make sure it was updated.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:2::"),
                                  48, 10, 20, 30, 1000,  SubnetID(2)));
    Subnet6Ptr replaced = cfg.replace(subnet);
    ASSERT_TRUE(replaced);
    EXPECT_TRUE(replaced == subnet2);
    ASSERT_EQ(3, cfg.getAll()->size());
    Subnet6Ptr returned = cfg.getSubnet(SubnetID(2));
    ASSERT_TRUE(returned);
    EXPECT_TRUE(returned == subnet);

    // Restore.
    replaced = cfg.replace(replaced);
    ASSERT_TRUE(replaced);
    EXPECT_TRUE(replaced == subnet);
    ASSERT_EQ(3, cfg.getAll()->size());
    returned = cfg.getSubnet(SubnetID(2));
    ASSERT_TRUE(returned);
    EXPECT_TRUE(returned == subnet2);

    // Prefix conflict returns null.
    subnet.reset(new Subnet6(IOAddress("2001:db8:3::"),
                             48, 10, 20, 30, 1000,  SubnetID(2)));
    replaced = cfg.replace(subnet);
    EXPECT_FALSE(replaced);
    returned = cfg.getSubnet(SubnetID(2));
    ASSERT_TRUE(returned);
    EXPECT_TRUE(returned == subnet2);

    // Changing prefix works even it is highly not recommended.
    subnet.reset(new Subnet6(IOAddress("2001:db8:10::"),
                             48, 10, 20, 30, 1000,  SubnetID(2)));
    replaced = cfg.replace(subnet);
    ASSERT_TRUE(replaced);
    EXPECT_TRUE(replaced == subnet2);
    returned = cfg.getSubnet(SubnetID(2));
    ASSERT_TRUE(returned);
    EXPECT_TRUE(returned == subnet);
}

// This test checks that the subnet can be selected using a relay agent's
// link address.
TEST(CfgSubnets6Test, selectSubnetByRelayAddress) {
    CfgSubnets6 cfg;

    // Let's configure 3 subnets
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Make sure that none of the subnets is selected when there is no relay
    // information configured for them.
    SubnetSelector selector;
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::1");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::2");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::3");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Now specify relay information.
    subnet1->addRelayAddress(IOAddress("2001:db8:ff::1"));
    subnet2->addRelayAddress(IOAddress("2001:db8:ff::2"));
    subnet3->addRelayAddress(IOAddress("2001:db8:ff::3"));

    // And try again. This time relay-info is there and should match.
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::1");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::2");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::3");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
}

// This test checks that subnet can be selected using a relay agent's
// link address specified on the shared network level.
TEST(CfgSubnets6Test, selectSubnetByNetworkRelayAddress) {
    // Create 2 shared networks.
    SharedNetwork6Ptr network1(new SharedNetwork6("net1"));
    SharedNetwork6Ptr network2(new SharedNetwork6("net2"));
    SharedNetwork6Ptr network3(new SharedNetwork6("net3"));

    // Let's configure 3 subnets
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    // Allow subnet class of clients to use the subnets.
    subnet1->allowClientClass("subnet");
    subnet2->allowClientClass("subnet");
    subnet3->allowClientClass("subnet");

    // Associate subnets with shared networks.
    network1->add(subnet1);
    network2->add(subnet2);
    network3->add(subnet3);

    // Add subnets to the configuration.
    CfgSubnets6 cfg;

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Make sure that none of the subnets is selected when there is no relay
    // information configured for them.
    SubnetSelector selector;
    selector.client_classes_.insert("subnet");

    // The relays are not set for networks, so none of the subnets should
    // be selected.
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::1");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::2");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::3");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Now specify relay information.
    network1->addRelayAddress(IOAddress("2001:db8:ff::1"));
    network2->addRelayAddress(IOAddress("2001:db8:ff::2"));
    network3->addRelayAddress(IOAddress("2001:db8:ff::3"));

    // And try again. This time relay-info is there and should match.
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::1");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::2");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::3");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Modify the client classes associated with the first two subnets.
    subnet1->allowClientClass("subnet1");
    subnet2->allowClientClass("subnet2");

    // This time the non-matching classes should prevent selection.
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::1");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::2");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::3");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
}

// This test checks that the subnet can be selected using an interface
// name associated with a asubnet.
TEST(CfgSubnets6Test, selectSubnetByInterfaceName) {
    CfgSubnets6 cfg;

    // Let's create 3 subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));
    subnet1->setIface("foo");
    subnet2->setIface("bar");
    subnet3->setIface("foobar");

    // Until subnets are added to the configuration, there should be nothing
    // returned.
    SubnetSelector selector;
    selector.iface_name_ = "foo";
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Add one of the subnets.
    cfg.add(subnet1);

    // The subnet should be now selected for the interface name "foo".
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));

    // Check that the interface name is checked even when there is
    // only one subnet defined: there should be nothing returned when
    // other interface name is specified.
    selector.iface_name_ = "bar";
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Add other subnets.
    cfg.add(subnet2);
    cfg.add(subnet3);

    // When we specify correct interface names, the subnets should be returned.
    selector.iface_name_ = "foobar";
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
    selector.iface_name_ = "bar";
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));

    // When specifying a non-existing interface the subnet should not be
    // returned.
    selector.iface_name_ = "xyzzy";
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// This test checks that the subnet can be selected using an Interface ID
// option inserted by a relay.
TEST(CfgSubnets6Test, selectSubnetByInterfaceId) {
    CfgSubnets6 cfg;

    // Create 3 subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // Create Interface-id options used in subnets 1,2, and 3
    OptionPtr ifaceid1 = generateInterfaceId("relay1.eth0");
    OptionPtr ifaceid2 = generateInterfaceId("VL32");
    // That's a strange interface-id, but this is a real life example
    OptionPtr ifaceid3 = generateInterfaceId("ISAM144|299|ipv6|nt:vp:1:110");

    // Bogus interface-id.
    OptionPtr ifaceid_bogus = generateInterfaceId("non-existent");

    // Assign interface ids to the respective subnets.
    subnet1->setInterfaceId(ifaceid1);
    subnet2->setInterfaceId(ifaceid2);
    subnet3->setInterfaceId(ifaceid3);

    // There shouldn't be any subnet configured at this stage.
    SubnetSelector selector;
    selector.interface_id_ = ifaceid1;
    // Note that some link address must be specified to indicate that it is
    // a relayed message!
    selector.first_relay_linkaddr_ = IOAddress("5000::1");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Add one of the subnets.
    cfg.add(subnet1);

    // If only one subnet has been specified, it should be returned when the
    // interface id matches. But, for a different interface id there should be
    // no match.
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.interface_id_ = ifaceid2;
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Add other subnets.
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Now that we have all subnets added. we should be able to retrieve them
    // using appropriate interface ids.
    selector.interface_id_ = ifaceid3;
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
    selector.interface_id_ = ifaceid2;
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));

    // For invalid interface id, there should be nothing returned.
    selector.interface_id_ = ifaceid_bogus;
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// Test that the client classes are considered when the subnet is selected by
// the relay link address.
TEST(CfgSubnets6Test, selectSubnetByRelayAddressAndClassify) {
    CfgSubnets6 cfg;

    // Let's configure 3 subnets
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Let's sanity check that we can use that configuration.
    SubnetSelector selector;
    selector.first_relay_linkaddr_ = IOAddress("2000::123");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("3000::345");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("4000::567");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Client now belongs to bar class.
    selector.client_classes_.insert("bar");

    // There are no class restrictions defined, so everything should work
    // as before.
    selector.first_relay_linkaddr_ = IOAddress("2000::123");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("3000::345");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("4000::567");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Now let's add client class restrictions.
    subnet1->allowClientClass("foo"); // Serve here only clients from foo class
    subnet2->allowClientClass("bar"); // Serve here only clients from bar class
    subnet3->allowClientClass("baz"); // Serve here only clients from baz class

    // The same check as above should result in client being served only in
    // bar class, i.e. subnet2
    selector.first_relay_linkaddr_ = IOAddress("2000::123");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("3000::345");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("4000::567");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Now let's check that client with wrong class is not supported
    selector.client_classes_.clear();
    selector.client_classes_.insert("some_other_class");
    selector.first_relay_linkaddr_ = IOAddress("2000::123");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("3000::345");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("4000::567");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Finally, let's check that client without any classes is not supported
    selector.client_classes_.clear();
    selector.first_relay_linkaddr_ = IOAddress("2000::123");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("3000::345");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("4000::567");
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// Test that client classes are considered when the subnet is selected by the
// interface name.
TEST(CfgSubnets6Test, selectSubnetByInterfaceNameAndClassify) {
    CfgSubnets6 cfg;

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));
    subnet1->setIface("foo");
    subnet2->setIface("bar");
    subnet3->setIface("foobar");

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Now we have only one subnet, any request will be served from it
    SubnetSelector selector;
    selector.client_classes_.insert("bar");
    selector.iface_name_ = "foo";
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.iface_name_ = "bar";
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.iface_name_ = "foobar";
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    subnet1->allowClientClass("foo"); // Serve here only clients from foo class
    subnet2->allowClientClass("bar"); // Serve here only clients from bar class
    subnet3->allowClientClass("baz"); // Serve here only clients from baz class

    selector.iface_name_ = "foo";
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.iface_name_ = "bar";
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.iface_name_ = "foobar";
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// Test that client classes are considered when the interface is selected by
// the interface id.
TEST(CfgSubnets6Test, selectSubnetByInterfaceIdAndClassify) {
    CfgSubnets6 cfg;

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // interface-id options used in subnets 1,2, and 3
    OptionPtr ifaceid1 = generateInterfaceId("relay1.eth0");
    OptionPtr ifaceid2 = generateInterfaceId("VL32");
    // That's a strange interface-id, but this is a real life example
    OptionPtr ifaceid3 = generateInterfaceId("ISAM144|299|ipv6|nt:vp:1:110");

    // bogus interface-id
    OptionPtr ifaceid_bogus = generateInterfaceId("non-existent");

    subnet1->setInterfaceId(ifaceid1);
    subnet2->setInterfaceId(ifaceid2);
    subnet3->setInterfaceId(ifaceid3);

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // If we have only a single subnet and the request came from a local
    // address, let's use that subnet
    SubnetSelector selector;
    selector.first_relay_linkaddr_ = IOAddress("5000::1");
    selector.client_classes_.insert("bar");
    selector.interface_id_ = ifaceid1;
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.interface_id_ = ifaceid2;
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.interface_id_ = ifaceid3;
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    subnet1->allowClientClass("foo"); // Serve here only clients from foo class
    subnet2->allowClientClass("bar"); // Serve here only clients from bar class
    subnet3->allowClientClass("baz"); // Serve here only clients from baz class

    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.interface_id_ = ifaceid2;
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.interface_id_ = ifaceid3;
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// Checks that detection of duplicated subnet IDs works as expected. It should
// not be possible to add two IPv6 subnets holding the same ID.
TEST(CfgSubnets6Test, duplication) {
    CfgSubnets6 cfg;

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4, 123));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4, 124));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4, 123));
    Subnet6Ptr subnet4(new Subnet6(IOAddress("2000::1"), 48, 1, 2, 3, 4, 125));

    ASSERT_NO_THROW(cfg.add(subnet1));
    EXPECT_NO_THROW(cfg.add(subnet2));
    // Subnet 3 has the same ID as subnet 1. It shouldn't be able to add it.
    EXPECT_THROW(cfg.add(subnet3), isc::dhcp::DuplicateSubnetID);
    // Subnet 4 has a similar but different subnet as subnet 1.
    EXPECT_NO_THROW(cfg.add(subnet4));
}

// This test check if IPv6 subnets can be unparsed in a predictable way,
TEST(CfgSubnets6Test, unparseSubnet) {
    CfgSubnets6 cfg;

    // Add some subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"),
                                   48, 1, 2, 3, 4, 123));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"),
                                   48, 1, 2, 3, 4, 124));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"),
                                   48, 1, 2, 3, 4, 125));

    OptionPtr ifaceid = generateInterfaceId("relay.eth0");
    subnet1->setInterfaceId(ifaceid);
    subnet1->allowClientClass("foo");

    subnet1->setT1Percent(0.45);
    subnet1->setT2Percent(0.70);
    subnet1->setCacheThreshold(0.20);

    subnet2->setIface("lo");
    subnet2->addRelayAddress(IOAddress("2001:db8:ff::2"));
    subnet2->setValid(Triplet<uint32_t>(200));
    subnet2->setPreferred(Triplet<uint32_t>(100));
    subnet2->setStoreExtendedInfo(true);
    subnet2->setCacheMaxAge(80);

    subnet3->setIface("eth1");
    subnet3->requireClientClass("foo");
    subnet3->requireClientClass("bar");
    subnet3->setReservationsGlobal(false);
    subnet3->setReservationsInSubnet(true);
    subnet3->setReservationsOutOfPool(false);
    subnet3->setRapidCommit(false);
    subnet3->setCalculateTeeTimes(true);
    subnet3->setT1Percent(0.50);
    subnet3->setT2Percent(0.65);
    subnet3->setValid(Triplet<uint32_t>(100, 200, 300));
    subnet3->setPreferred(Triplet<uint32_t>(50, 100, 150));
    subnet3->setDdnsSendUpdates(true);
    subnet3->setDdnsOverrideNoUpdate(true);
    subnet3->setDdnsOverrideClientUpdate(true);
    subnet3->setDdnsReplaceClientNameMode(D2ClientConfig::RCM_ALWAYS);
    subnet3->setDdnsGeneratedPrefix("prefix");
    subnet3->setDdnsQualifyingSuffix("example.com.");
    subnet3->setHostnameCharSet("[^A-Z]");
    subnet3->setHostnameCharReplacement("x");

    data::ElementPtr ctx1 = data::Element::fromJSON("{ \"comment\": \"foo\" }");
    subnet1->setContext(ctx1);
    data::ElementPtr ctx2 = data::Element::createMap();
    subnet2->setContext(ctx2);

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Unparse
    std::string expected = "[\n"
        "{\n"
        "    \"id\": 123,\n"
        "    \"subnet\": \"2001:db8:1::/48\",\n"
        "    \"t1-percent\": 0.45,"
        "    \"t2-percent\": 0.7,"
        "    \"cache-threshold\": .20,\n"
        "    \"interface-id\": \"relay.eth0\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"preferred-lifetime\": 3,\n"
        "    \"min-preferred-lifetime\": 3,\n"
        "    \"max-preferred-lifetime\": 3,\n"
        "    \"valid-lifetime\": 4,\n"
        "    \"min-valid-lifetime\": 4,\n"
        "    \"max-valid-lifetime\": 4,\n"
        "    \"client-class\": \"foo\",\n"
        "    \"pools\": [ ],\n"
        "    \"pd-pools\": [ ],\n"
        "    \"option-data\": [ ],\n"
        "    \"user-context\": { \"comment\": \"foo\" }\n"
        "},{\n"
        "    \"id\": 124,\n"
        "    \"subnet\": \"2001:db8:2::/48\",\n"
        "    \"interface\": \"lo\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ \"2001:db8:ff::2\" ] },\n"
        "    \"preferred-lifetime\": 100,\n"
        "    \"min-preferred-lifetime\": 100,\n"
        "    \"max-preferred-lifetime\": 100,\n"
        "    \"valid-lifetime\": 200,\n"
        "    \"min-valid-lifetime\": 200,\n"
        "    \"max-valid-lifetime\": 200,\n"
        "    \"user-context\": { },\n"
        "    \"pools\": [ ],\n"
        "    \"pd-pools\": [ ],\n"
        "    \"option-data\": [ ],\n"
        "    \"store-extended-info\": true,\n"
        "    \"cache-max-age\": 80\n"
        "},{\n"
        "    \"id\": 125,\n"
        "    \"subnet\": \"2001:db8:3::/48\",\n"
        "    \"interface\": \"eth1\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"preferred-lifetime\": 100,\n"
        "    \"min-preferred-lifetime\": 50,\n"
        "    \"max-preferred-lifetime\": 150,\n"
        "    \"valid-lifetime\": 200,\n"
        "    \"min-valid-lifetime\": 100,\n"
        "    \"max-valid-lifetime\": 300,\n"
        "    \"rapid-commit\": false,\n"
        "    \"reservations-global\": false,\n"
        "    \"reservations-in-subnet\": true,\n"
        "    \"reservations-out-of-pool\": false,\n"
        "    \"pools\": [ ],\n"
        "    \"pd-pools\": [ ],\n"
        "    \"option-data\": [ ],\n"
        "    \"require-client-classes\": [ \"foo\", \"bar\" ],\n"
        "    \"calculate-tee-times\": true,\n"
        "    \"t1-percent\": 0.50,\n"
        "    \"t2-percent\": 0.65,\n"
        "    \"ddns-generated-prefix\": \"prefix\",\n"
        "    \"ddns-override-client-update\": true,\n"
        "    \"ddns-override-no-update\": true,\n"
        "    \"ddns-qualifying-suffix\": \"example.com.\",\n"
        "    \"ddns-replace-client-name\": \"always\",\n"
        "    \"ddns-send-updates\": true,\n"
        "    \"hostname-char-replacement\": \"x\",\n"
        "    \"hostname-char-set\": \"[^A-Z]\"\n"
        "} ]\n";

    runToElementTest<CfgSubnets6>(expected, cfg);
}

// This test check if IPv6 pools can be unparsed in a predictable way,
TEST(CfgSubnets6Test, unparsePool) {
    CfgSubnets6 cfg;

    // Add a subnet with pools
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  48, 1, 2, 3, 4, 123));
    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA,
                             IOAddress("2001:db8:1::100"),
                             IOAddress("2001:db8:1::199")));
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    pool2->allowClientClass("bar");

    std::string json1 = "{ \"comment\": \"foo\", \"version\": 1 }";
    data::ElementPtr ctx1 = data::Element::fromJSON(json1);
    pool1->setContext(ctx1);
    data::ElementPtr ctx2 = data::Element::fromJSON("{ \"foo\": \"bar\" }");
    pool2->setContext(ctx2);
    pool2->requireClientClass("foo");

    subnet->addPool(pool1);
    subnet->addPool(pool2);
    cfg.add(subnet);

    // Unparse
    std::string expected = "[\n"
        "{\n"
        "    \"id\": 123,\n"
        "    \"subnet\": \"2001:db8:1::/48\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"preferred-lifetime\": 3,\n"
        "    \"min-preferred-lifetime\": 3,\n"
        "    \"max-preferred-lifetime\": 3,\n"
        "    \"valid-lifetime\": 4,\n"
        "    \"min-valid-lifetime\": 4,\n"
        "    \"max-valid-lifetime\": 4,\n"
        "    \"pools\": [\n"
        "        {\n"
        "            \"pool\": \"2001:db8:1::100-2001:db8:1::199\",\n"
        "            \"user-context\": { \"version\": 1,\n"
        "                                \"comment\": \"foo\" },\n"
        "            \"option-data\": [ ]\n"
        "        },{\n"
        "            \"pool\": \"2001:db8:1:1::/64\",\n"
        "            \"user-context\": { \"foo\": \"bar\" },\n"
        "            \"option-data\": [ ],\n"
        "            \"client-class\": \"bar\",\n"
        "            \"require-client-classes\": [ \"foo\" ]\n"
        "        }\n"
        "    ],\n"
        "    \"pd-pools\": [ ],\n"
        "    \"option-data\": [ ]\n"
        "} ]\n";
    runToElementTest<CfgSubnets6>(expected, cfg);
}

// This test check if IPv6 prefix delegation pools can be unparsed
// in a predictable way,
TEST(CfgSubnets6Test, unparsePdPool) {
    CfgSubnets6 cfg;

    // Add a subnet with pd-pools
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"),
                                  48, 1, 2, 3, 4, 123));
    Pool6Ptr pdpool1(new Pool6(Lease::TYPE_PD,
                               IOAddress("2001:db8:2::"), 48, 64));
    Pool6Ptr pdpool2(new Pool6(IOAddress("2001:db8:3::"), 48, 56,
                               IOAddress("2001:db8:3::"), 64));
    pdpool2->allowClientClass("bar");

    data::ElementPtr ctx1 = data::Element::fromJSON("{ \"foo\": [ \"bar\" ] }");
    pdpool1->setContext(ctx1);
    pdpool1->requireClientClass("bar");
    pdpool2->allowClientClass("bar");

    subnet->addPool(pdpool1);
    subnet->addPool(pdpool2);
    cfg.add(subnet);

    // Unparse
    std::string expected = "[\n"
        "{\n"
        "    \"id\": 123,\n"
        "    \"subnet\": \"2001:db8:1::/48\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"preferred-lifetime\": 3,\n"
        "    \"min-preferred-lifetime\": 3,\n"
        "    \"max-preferred-lifetime\": 3,\n"
        "    \"valid-lifetime\": 4,\n"
        "    \"min-valid-lifetime\": 4,\n"
        "    \"max-valid-lifetime\": 4,\n"
        "    \"pools\": [ ],\n"
        "    \"pd-pools\": [\n"
        "        {\n"
        "            \"prefix\": \"2001:db8:2::\",\n"
        "            \"prefix-len\": 48,\n"
        "            \"delegated-len\": 64,\n"
        "            \"user-context\": { \"foo\": [ \"bar\" ] },\n"
        "            \"option-data\": [ ],\n"
        "            \"require-client-classes\": [ \"bar\" ]\n"
        "        },{\n"
        "            \"prefix\": \"2001:db8:3::\",\n"
        "            \"prefix-len\": 48,\n"
        "            \"delegated-len\": 56,\n"
        "            \"excluded-prefix\": \"2001:db8:3::\",\n"
        "            \"excluded-prefix-len\": 64,\n"
        "            \"option-data\": [ ],\n"
        "            \"client-class\": \"bar\"\n"
        "        }\n"
        "    ],\n"
        "    \"option-data\": [ ]\n"
        "} ]\n";
    runToElementTest<CfgSubnets6>(expected, cfg);
}

// This test verifies that it is possible to retrieve a subnet using subnet-id.
TEST(CfgSubnets6Test, getSubnet) {
    CfgSubnets6 cfg;

    // Let's configure 3 subnets
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 100));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4, 200));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4, 300));
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    EXPECT_EQ(subnet1, cfg.getSubnet(100));
    EXPECT_EQ(subnet2, cfg.getSubnet(200));
    EXPECT_EQ(subnet3, cfg.getSubnet(300));
    EXPECT_EQ(Subnet6Ptr(), cfg.getSubnet(400)); // no such subnet
}

// This test verifies that subnets configuration is properly merged.
TEST(CfgSubnets6Test, mergeSubnets) {
    // Create custom options dictionary for testing merge. We're keeping it
    // simple because they are more rigorous tests elsewhere.
    CfgOptionDefPtr cfg_def(new CfgOptionDef());
    cfg_def->add((OptionDefinitionPtr(new OptionDefinition("one", 1, "isc", "string"))));

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:1::"),
                                   64, 1, 2, 100, 100, SubnetID(1)));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:2::"),
                                   64, 1, 2, 100, 100, SubnetID(2)));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:3::"),
                                   64, 1, 2, 100, 100, SubnetID(3)));
    Subnet6Ptr subnet4(new Subnet6(IOAddress("2001:4::"),
                                   64, 1, 2, 100, 100, SubnetID(4)));

    // Create the "existing" list of shared networks
    CfgSharedNetworks6Ptr networks(new CfgSharedNetworks6());
    SharedNetwork6Ptr shared_network1(new SharedNetwork6("shared-network1"));
    networks->add(shared_network1);
    SharedNetwork6Ptr shared_network2(new SharedNetwork6("shared-network2"));
    networks->add(shared_network2);

    // Empty network pointer.
    SharedNetwork6Ptr no_network;

    // Add Subnets 1, 2 and 4 to shared networks.
    ASSERT_NO_THROW(shared_network1->add(subnet1));
    ASSERT_NO_THROW(shared_network2->add(subnet2));
    ASSERT_NO_THROW(shared_network2->add(subnet4));

    // Create our "existing" configured subnets.
    CfgSubnets6 cfg_to;
    ASSERT_NO_THROW(cfg_to.add(subnet1));
    ASSERT_NO_THROW(cfg_to.add(subnet2));
    ASSERT_NO_THROW(cfg_to.add(subnet3));
    ASSERT_NO_THROW(cfg_to.add(subnet4));

    // Merge in an "empty" config. Should have the original config,
    // still intact.
    CfgSubnets6 cfg_from;
    ASSERT_NO_THROW(cfg_to.merge(cfg_def, networks, cfg_from));

    // We should have all four subnets, with no changes.
    ASSERT_EQ(4, cfg_to.getAll()->size());

    // Should be no changes to the configuration.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:1::/64",
                                              SubnetID(1), 100, shared_network1));
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:2::/64",
                                              SubnetID(2), 100, shared_network2));
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:3::/64",
                                              SubnetID(3), 100, no_network));
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:4::/64",
                                              SubnetID(4), 100, shared_network2));

    // Fill cfg_from configuration with subnets.
    // subnet 1b updates subnet 1 but leaves it in network 1 with the same ID.
    Subnet6Ptr subnet1b(new Subnet6(IOAddress("2001:10::"),
                                   64, 2, 3, 100, 400, SubnetID(1)));
    subnet1b->setSharedNetworkName("shared-network1");

    // Add generic option 1 to subnet 1b.
    std::string value("Yay!");
    OptionPtr option(new Option(Option::V6, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(subnet1b->getCfgOption()->add(option, false, "isc"));

    // subnet 3b updates subnet 3 with different UD and removes it
    // from network 2
    Subnet6Ptr subnet3b(new Subnet6(IOAddress("2001:3::"),
                                   64, 3, 4, 100, 500, SubnetID(30)));

    // Now Add generic option 1 to subnet 3b.
    value = "Team!";
    option.reset(new Option(Option::V6, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(subnet3b->getCfgOption()->add(option, false, "isc"));

    // subnet 4b updates subnet 4 and moves it from network2 to network 1
    Subnet6Ptr subnet4b(new Subnet6(IOAddress("2001:4::"),
                                   64, 3, 4, 100, 500, SubnetID(4)));
    subnet4b->setSharedNetworkName("shared-network1");

    // subnet 5 is new and belongs to network 2
    // Has two pools both with an option 1
    Subnet6Ptr subnet5(new Subnet6(IOAddress("2001:5::"),
                                   64, 1, 2, 100, 300, SubnetID(5)));
    subnet5->setSharedNetworkName("shared-network2");

    // Add pool 1
    Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:5::10"), IOAddress("2001:5::20")));
    value = "POOLS";
    option.reset(new Option(Option::V6, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, "isc"));
    subnet5->addPool(pool);

    // Add pool 2
    pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("2001:6::"), 64));
    value ="RULE!";
    option.reset(new Option(Option::V6, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, "isc"));
    subnet5->addPool(pool);

    // Add subnets to the merge from config.
    ASSERT_NO_THROW(cfg_from.add(subnet1b));
    ASSERT_NO_THROW(cfg_from.add(subnet3b));
    ASSERT_NO_THROW(cfg_from.add(subnet4b));
    ASSERT_NO_THROW(cfg_from.add(subnet5));

    // Merge again.
    ASSERT_NO_THROW(cfg_to.merge(cfg_def, networks, cfg_from));
    ASSERT_EQ(5, cfg_to.getAll()->size());

    // The subnet1 should be replaced by subnet1b.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:10::/64",
                                              SubnetID(1), 400, shared_network1));

    // Let's verify that our option is there and populated correctly.
    auto subnet = cfg_to.getByPrefix("2001:10::/64");
    auto desc = subnet->getCfgOption()->get("isc", 1);
    ASSERT_TRUE(desc.option_);
    OptionStringPtr opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("Yay!", opstr->getValue());

    // The subnet2 should not be affected because it was not present.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:2::/64",
                                              SubnetID(2), 100, shared_network2));

    // subnet3 should be replaced by subnet3b and no longer assigned to a network.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:3::/64",
                                              SubnetID(30), 500, no_network));
    // Let's verify that our option is there and populated correctly.
    subnet = cfg_to.getByPrefix("2001:3::/64");
    desc = subnet->getCfgOption()->get("isc", 1);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("Team!", opstr->getValue());

    // subnet4 should be replaced by subnet4b and moved to network1.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:4::/64",
                                              SubnetID(4), 500, shared_network1));

    // subnet5 should have been added to configuration.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "2001:5::/64",
                                              SubnetID(5), 300, shared_network2));

    // Let's verify that both pools have the proper options.
    subnet = cfg_to.getByPrefix("2001:5::/64");
    const PoolPtr merged_pool = subnet->getPool(Lease::TYPE_NA, IOAddress("2001:5::10"));
    ASSERT_TRUE(merged_pool);
    desc = merged_pool->getCfgOption()->get("isc", 1);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("POOLS", opstr->getValue());

    const PoolPtr merged_pool2 = subnet->getPool(Lease::TYPE_PD, IOAddress("2001:1::"));
    ASSERT_TRUE(merged_pool2);
    desc = merged_pool2->getCfgOption()->get("isc", 1);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("RULE!", opstr->getValue());
}

// This test verifies the Subnet6 parser's validation logic for
// t1-percent and t2-percent parameters.
TEST(CfgSubnets6Test, teeTimePercentValidation) {

    // Describes a single test scenario.
    struct Scenario {
        std::string label;         // label used for logging test failures
        bool calculate_tee_times;  // value of calculate-tee-times parameter
        double t1_percent;         // value of t1-percent parameter
        double t2_percent;         // value of t2-percent parameter
        std::string error_message; // expected error message is parsing should fail
    };

    // Test Scenarios.
    std::vector<Scenario> tests = {
        {"off and valid", false, .5, .95, ""},
        {"on and valid", true, .5, .95, ""},
        {"t2_negative", true, .5, -.95,
         "subnet configuration failed: t2-percent:"
         "  -0.95 is invalid, it must be greater than 0.0 and less than 1.0"
        },
        {"t2_too_big", true, .5, 1.95,
         "subnet configuration failed: t2-percent:"
         "  1.95 is invalid, it must be greater than 0.0 and less than 1.0"
        },
        {"t1_negative", true, -.5, .95,
         "subnet configuration failed: t1-percent:"
         "  -0.5 is invalid it must be greater than 0.0 and less than 1.0"
        },
        {"t1_too_big", true, 1.5, .95,
         "subnet configuration failed: t1-percent:"
         "  1.5 is invalid it must be greater than 0.0 and less than 1.0"
        },
        {"t1_bigger_than_t2", true, .85, .45,
         "subnet configuration failed: t1-percent:"
         "  0.85 is invalid, it must be less than t2-percent: 0.45"
        }
    };

    // First we create a set of elements that provides all
    // required for a Subnet6.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"valid-lifetime\": 300, \n"
        "            \"client-class\": \"\", \n"
        "            \"require-client-classes\": [] \n,"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false \n"
        "        }";


    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
            SCOPED_TRACE("test: " + (*test).label);

            // Set this scenario's configuration parameters
            elems->set("calculate-tee-times", data::Element::create((*test).calculate_tee_times));
            elems->set("t1-percent", data::Element::create((*test).t1_percent));
            elems->set("t2-percent", data::Element::create((*test).t2_percent));

            Subnet6Ptr subnet;
            try {
                // Attempt to parse the configuration.
                Subnet6ConfigParser parser;
                subnet = parser.parse(elems);
            } catch (const std::exception& ex) {
                if (!(*test).error_message.empty()) {
                    // We expected a failure, did we fail the correct way?
                    EXPECT_EQ((*test).error_message, ex.what());
                } else {
                    // Should not have failed.
                    ADD_FAILURE() << "Scenario should not have failed: " << ex.what();
                }

                // Either way we're done with this scenario.
                continue;
            }

            // We parsed correctly, make sure the values are right.
            EXPECT_EQ((*test).calculate_tee_times, subnet->getCalculateTeeTimes());
            EXPECT_TRUE(util::areDoublesEquivalent((*test).t1_percent, subnet->getT1Percent()))
                << "expected:" << (*test).t1_percent << " actual: " << subnet->getT1Percent();
            EXPECT_TRUE(util::areDoublesEquivalent((*test).t2_percent, subnet->getT2Percent()))
                << "expected:" << (*test).t2_percent << " actual: " << subnet->getT2Percent();
        }
    }
}

// This test verifies the Subnet6 parser's validation logic for
// preferred-lifetime and indirectly shared lifetime parsing.
// Note the valid-lifetime stuff is similar and already done for Subnet4.
TEST(CfgSubnets6Test, preferredLifetimeValidation) {
    // First we create a set of elements that provides all
    // required for a Subnet6.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"valid-lifetime\": 300, \n"
        "            \"client-class\": \"\", \n"
        "            \"require-client-classes\": [] \n,"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false \n"
        "        }";


    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    {
        SCOPED_TRACE("no preferred-lifetime");

        data::ElementPtr copied = data::copy(elems);
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_TRUE(subnet->getPreferred().unspecified());
        data::ConstElementPtr repr = subnet->toElement();
        EXPECT_FALSE(repr->get("preferred-lifetime"));
        EXPECT_FALSE(repr->get("min-preferred-lifetime"));
        EXPECT_FALSE(repr->get("max-preferred-lifetime"));
    }

    {
        SCOPED_TRACE("preferred-lifetime only");

        data::ElementPtr copied = data::copy(elems);
        copied->set("preferred-lifetime", data::Element::create(100));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(100, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(100, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }

    {
        SCOPED_TRACE("min-preferred-lifetime only");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(100));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(100, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(100, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }

    {
        SCOPED_TRACE("max-preferred-lifetime only");
        data::ElementPtr copied = data::copy(elems);
        copied->set("max-preferred-lifetime", data::Element::create(100));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(100, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(100, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }

    {
        SCOPED_TRACE("min-preferred-lifetime and preferred-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(100));
        // Use a different (and greater) value for the default.
        copied->set("preferred-lifetime", data::Element::create(200));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(200, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(200, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("200", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("200", max_value->str());
    }

    {
        SCOPED_TRACE("max-preferred-lifetime and preferred-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("max-preferred-lifetime", data::Element::create(200));
        // Use a different (and smaller) value for the default.
        copied->set("preferred-lifetime", data::Element::create(100));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(100, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(200, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("200", max_value->str());
    }

    {
        SCOPED_TRACE("min-preferred-lifetime and max-preferred-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(100));
        copied->set("max-preferred-lifetime", data::Element::create(200));
        Subnet6ConfigParser parser;
        // No idea about the value to use for the default so failing.
        ASSERT_THROW(parser.parse(copied), DhcpConfigError);
    }

    {
        SCOPED_TRACE("all 3 (min, max and default) preferred-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(100));
        // Use a different (and greater) value for the default.
        copied->set("preferred-lifetime", data::Element::create(200));
        // Use a different (and greater than both) value for max.
        copied->set("max-preferred-lifetime", data::Element::create(300));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(200, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(300, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("200", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("300", max_value->str());
    }

    {
        SCOPED_TRACE("default value too small");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(200));
        // 100 < 200 so it will fail.
        copied->set("preferred-lifetime", data::Element::create(100));
        // Use a different (and greater than both) value for max.
        copied->set("max-preferred-lifetime", data::Element::create(300));
        Subnet6ConfigParser parser;
        ASSERT_THROW(parser.parse(copied), DhcpConfigError);
    }

    {
        SCOPED_TRACE("default value too large");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(100));
        // Use a different (and greater) value for the default.
        copied->set("preferred-lifetime", data::Element::create(300));
        // 300 > 200 so it will fail.
        copied->set("max-preferred-lifetime", data::Element::create(200));
        Subnet6ConfigParser parser;
        ASSERT_THROW(parser.parse(copied), DhcpConfigError);
    }

    {
        SCOPED_TRACE("equal bounds are no longer ignored");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-preferred-lifetime", data::Element::create(100));
        copied->set("preferred-lifetime", data::Element::create(100));
        copied->set("max-preferred-lifetime", data::Element::create(100));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getPreferred().unspecified());
        EXPECT_EQ(100, subnet->getPreferred());
        EXPECT_EQ(100, subnet->getPreferred().getMin());
        EXPECT_EQ(100, subnet->getPreferred().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("preferred-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-preferred-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-preferred-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }
}

// This test verifies the Subnet6 parser's validation logic for
// hostname sanitizer values.
TEST(CfgSubnets6Test, hostnameSanitizierValidation) {

    // First we create a set of elements that provides all
    // required for a Subnet6.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"valid-lifetime\": 300, \n"
        "            \"client-class\": \"\", \n"
        "            \"require-client-classes\": [] \n,"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false \n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    {
        SCOPED_TRACE("invalid regular expression");

        data::ElementPtr copied = data::copy(elems);
        copied->set("hostname-char-set", data::Element::create("^[A-"));
        copied->set("hostname-char-replacement", data::Element::create("x"));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        EXPECT_THROW_MSG(subnet = parser.parse(copied), DhcpConfigError,
                         "subnet configuration failed: hostname-char-set "
                         "'^[A-' is not a valid regular expression");

    }
    {
        SCOPED_TRACE("valid regular expression");

        data::ElementPtr copied = data::copy(elems);
        copied->set("hostname-char-set", data::Element::create("^[A-Z]"));
        copied->set("hostname-char-replacement", data::Element::create("x"));
        Subnet6Ptr subnet;
        Subnet6ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        EXPECT_EQ("^[A-Z]", subnet->getHostnameCharSet().get());
        EXPECT_EQ("x", subnet->getHostnameCharReplacement().get());
    }
}

// This test verifies the Subnet6 parser's validation logic for
// lease cache parameters.
TEST(CfgSubnets6Test, cacheParamValidation) {

    // Describes a single test scenario.
    struct Scenario {
        std::string label;         // label used for logging test failures
        double threshold;          // value of cache-threshold
        std::string error_message; // expected error message is parsing should fail
    };

    // Test Scenarios.
    std::vector<Scenario> tests = {
        {"valid", .25, ""},
        {"negative", -.25,
         "subnet configuration failed: cache-threshold:"
         " -0.25 is invalid, it must be greater than 0.0 and less than 1.0"
        },
        {"too big", 1.05,
         "subnet configuration failed: cache-threshold:"
         " 1.05 is invalid, it must be greater than 0.0 and less than 1.0"
        }
    };

    // First we create a set of elements that provides all
    // required for a Subnet6.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"valid-lifetime\": 300, \n"
        "            \"client-class\": \"\", \n"
        "            \"require-client-classes\": [] \n,"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false \n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto test = tests.begin(); test != tests.end(); ++test) {
        {
            SCOPED_TRACE("test: " + (*test).label);

            // Set this scenario's configuration parameters
            elems->set("cache-threshold", data::Element::create((*test).threshold));

            Subnet6Ptr subnet;
            try {
                // Attempt to parse the configuration.
                Subnet6ConfigParser parser;
                subnet = parser.parse(elems);
            } catch (const std::exception& ex) {
                if (!(*test).error_message.empty()) {
                    // We expected a failure, did we fail the correct way?
                    EXPECT_EQ((*test).error_message, ex.what());
                } else {
                    // Should not have failed.
                    ADD_FAILURE() << "Scenario should not have failed: " << ex.what();
                }

                // Either way we're done with this scenario.
                continue;
            }

            // We parsed correctly, make sure the values are right.
            EXPECT_TRUE(util::areDoublesEquivalent((*test).threshold, subnet->getCacheThreshold()));
        }
    }
}

// This test verifies that the optional interface check works as expected.
TEST(CfgSubnets6Test, iface) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"interface\": \"eth1\"\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    // The interface check can be disabled.
    Subnet6ConfigParser parser_no_check(false);
    Subnet6Ptr subnet;
    EXPECT_NO_THROW(subnet = parser_no_check.parse(elems));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getIface().unspecified());
    EXPECT_EQ("eth1", subnet->getIface().get());

    // Retry with the interface check enabled.
    Subnet6ConfigParser parser;
    EXPECT_THROW(parser.parse(elems), DhcpConfigError);

    // Configure default test interfaces.
    IfaceMgrTestConfig config(true);

    EXPECT_NO_THROW(subnet = parser_no_check.parse(elems));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getIface().unspecified());
    EXPECT_EQ("eth1", subnet->getIface().get());

    EXPECT_NO_THROW(subnet = parser.parse(elems));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getIface().unspecified());
    EXPECT_EQ("eth1", subnet->getIface().get());
}

// This test verifies that update statistics works as expected.
TEST(CfgSubnets6Test, updateStatistics) {
    CfgMgr::instance().clear();

    CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    ObservationPtr observation;
    SubnetID subnet_id = 100;

    LeaseMgrFactory::create("type=memfile universe=6 persist=false");

    // remove all statistics
    StatsMgr::instance().removeAll();

    // Create subnet.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 100));

    // Add subnet.
    cfg->add(subnet);

    observation = StatsMgr::instance().getObservation(
        "cumulative-assigned-nas");
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        "cumulative-assigned-pds");
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        "declined-addresses");
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        "reclaimed-declined-addresses");
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        "reclaimed-leases");
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-nas"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-pds"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-nas"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-pds"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-nas"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-pds"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_FALSE(observation);

    cfg->updateStatistics();

    observation = StatsMgr::instance().getObservation(
        "cumulative-assigned-nas");
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        "cumulative-assigned-pds");
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        "declined-addresses");
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        "reclaimed-declined-addresses");
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        "reclaimed-leases");
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-nas"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-pds"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-nas"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-pds"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-nas"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-pds"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);
}

// This test verifies that remove statistics works as expected.
TEST(CfgSubnets6Test, removeStatistics) {
    CfgSubnets6 cfg;
    ObservationPtr observation;
    SubnetID subnet_id = 100;

    // remove all statistics and then set them all to 0
    StatsMgr::instance().removeAll();

    // Create subnet.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4, 100));

    // Add subnet.
    cfg.add(subnet);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-nas"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-nas"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-pds"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-pds"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-nas"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-nas"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-pds"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-pds"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-nas"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-nas"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-pds"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-pds"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    // remove all statistics
    cfg.removeStatistics();

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-nas"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-pds"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-nas"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-pds"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-nas"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-pds"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_FALSE(observation);
}

// This test verifies that in range host reservation works as expected.
TEST(CfgSubnets6Test, hostNA) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/48\", \n"
        "            \"reservations\": [ {\n"
        "                \"hw-address\": \"aa:bb:cc:dd:ee:ff\", \n"
        "                \"ip-addresses\": [\"2001:db8:1::1\"] } ]\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    Subnet6ConfigParser parser;
    Subnet6Ptr subnet;
    EXPECT_NO_THROW(subnet = parser.parse(elems));
    ASSERT_TRUE(subnet);
    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(cfg_hosts);
    HostCollection hosts = cfg_hosts->getAll6(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    ConstHostPtr host = hosts[0];
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_EQ("hwaddr=AABBCCDDEEFF", host->getIdentifierAsText());
    IPv6ResrvRange addresses = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(1, std::distance(addresses.first, addresses.second));
    EXPECT_EQ("2001:db8:1::1", addresses.first->second.getPrefix().toText());

    CfgMgr::instance().clear();
}

// This test verifies that an out of range host reservation is rejected.
TEST(CfgSubnets6Test, outOfRangeHost) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/48\", \n"
        "            \"reservations\": [ {\n"
        "                \"hw-address\": \"aa:bb:cc:dd:ee:ff\", \n"
        "                \"ip-addresses\": [\"2001:db8:1::1\", \n"
        "                                   \"2001:db8:2::1\"] } ]\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    Subnet6ConfigParser parser;
    std::string msg = "specified reservation '2001:db8:2::1' is ";
    msg += "not within the IPv6 subnet '2001:db8:1::/48'";
    EXPECT_THROW_MSG(parser.parse(elems), DhcpConfigError, msg);
}

// This test verifies that in range validation does not applies to prefixes.
TEST(CfgSubnets6Test, hostPD) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"2001:db8:1::/48\", \n"
        "            \"reservations\": [ {\n"
        "                \"hw-address\": \"aa:bb:cc:dd:ee:ff\", \n"
        "                \"prefixes\": [\"2001:db8:2::/64\"] } ]\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    Subnet6ConfigParser parser;
    Subnet6Ptr subnet;
    try {
        subnet = parser.parse(elems);
    } catch (const std::exception& ex) {
        std::cerr << "parse fail with " << ex.what() << std::endl;
    }
    //EXPECT_NO_THROW(subnet = parser.parse(elems));
    ASSERT_TRUE(subnet);
    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(cfg_hosts);
    HostCollection hosts = cfg_hosts->getAll6(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    ConstHostPtr host = hosts[0];
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_EQ("hwaddr=AABBCCDDEEFF", host->getIdentifierAsText());
    IPv6ResrvRange prefixes = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(prefixes.first, prefixes.second));
    EXPECT_EQ("2001:db8:2::", prefixes.first->second.getPrefix().toText());
    EXPECT_EQ(64, prefixes.first->second.getPrefixLen());

    // Verify the prefix is not in the subnet range.
    EXPECT_FALSE(subnet->inRange(prefixes.first->second.getPrefix()));

    CfgMgr::instance().clear();
}

} // end of anonymous namespace
