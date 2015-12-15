// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/subnet_selector.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// @brief Generates interface id option.
///
/// @param text Interface id in a textual format.
OptionPtr
generateInterfaceId(const std::string& text) {
    OptionBuffer buffer(text.begin(), text.end());
    return OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID, buffer));
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
    subnet1->setRelayInfo(IOAddress("2001:db8:ff::1"));
    subnet2->setRelayInfo(IOAddress("2001:db8:ff::2"));
    subnet3->setRelayInfo(IOAddress("2001:db8:ff::3"));

    // And try again. This time relay-info is there and should match.
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::1");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.first_relay_linkaddr_ = IOAddress("2001:db8:ff::2");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
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

// Test that client classes are considered when the subnet is selcted by the
// interface name.
TEST(CfgSubnets6Test, selectSubnetByInterfaceNameAndClaassify) {
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

    ASSERT_NO_THROW(cfg.add(subnet1));
    EXPECT_NO_THROW(cfg.add(subnet2));
    // Subnet 3 has the same ID as subnet 1. It shouldn't be able to add it.
    EXPECT_THROW(cfg.add(subnet3), isc::dhcp::DuplicateSubnetID);
}

} // end of anonymous namespace
