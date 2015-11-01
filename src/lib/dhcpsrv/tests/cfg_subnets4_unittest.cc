// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/classify.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/subnet_selector.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

// This test verifies that it is possible to retrieve a subnet using an
// IP address.
TEST(CfgSubnets4Test, selectSubnetByCiaddr) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // Make sure that initially the subnets don't exist.
    SubnetSelector selector;
    selector.ciaddr_ = IOAddress("192.0.2.0");
    // Set some unicast local address to simulate a Renew.
    selector.local_address_ = IOAddress("10.0.0.100");
    ASSERT_FALSE(cfg.selectSubnet(selector));

    // Add one subnet and make sure it is returned.
    cfg.add(subnet1);
    selector.ciaddr_ = IOAddress("192.0.2.63");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));

    // Add all other subnets.
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Make sure they are returned for the appropriate addresses.
    selector.ciaddr_ = IOAddress("192.0.2.15");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.85");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.191");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Also, make sure that the NULL pointer is returned if the subnet
    // cannot be found.
    selector.ciaddr_ = IOAddress("192.0.2.192");
    EXPECT_FALSE(cfg.selectSubnet(selector));
}


// This test verifies that when the classification information is specified for
// subnets, the proper subnets are returned by the subnet configuration.
TEST(CfgSubnets4Test, selectSubnetByClasses) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // Add them to the configuration.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SubnetSelector selector;

    selector.local_address_ = IOAddress("10.0.0.10");

    selector.ciaddr_ = IOAddress("192.0.2.5");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.70");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.130");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    ClientClasses client_classes;
    client_classes.insert("bar");
    selector.client_classes_ = client_classes;

    // There are no class restrictions defined, so everything should work
    // as before
    selector.ciaddr_ = IOAddress("192.0.2.5");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.70");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.130");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Now let's add client class restrictions.
    subnet1->allowClientClass("foo"); // Serve here only clients from foo class
    subnet2->allowClientClass("bar"); // Serve here only clients from bar class
    subnet3->allowClientClass("baz"); // Serve here only clients from baz class

    // The same check as above should result in client being served only in
    // bar class, i.e. subnet2.
    selector.ciaddr_ = IOAddress("192.0.2.5");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.70");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.130");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Now let's check that client with wrong class is not supported.
    client_classes.clear();
    client_classes.insert("some_other_class");
    selector.client_classes_ = client_classes;
    selector.ciaddr_ = IOAddress("192.0.2.5");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.70");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.130");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Finally, let's check that client without any classes is not supported.
    client_classes.clear();
    selector.ciaddr_ = IOAddress("192.0.2.5");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.70");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.ciaddr_ = IOAddress("192.0.2.130");
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// This test verifies the option selection can be used and is only
// used when present.
TEST(CfgSubnets4Test, selectSubnetByOptionSelect) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // Add them to the configuration.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SubnetSelector selector;

    // Check that without option selection something else is used
    selector.ciaddr_ = IOAddress("192.0.2.5");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));

    // The option selection has precedence
    selector.option_select_ = IOAddress("192.0.2.130");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Over relay-info too
    selector.giaddr_ = IOAddress("10.0.0.1");
    subnet2->setRelayInfo(IOAddress("10.0.0.1"));
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
    selector.option_select_ = IOAddress("0.0.0.0");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));

    // Check that a not matching option selection it shall fail
    selector.option_select_ = IOAddress("10.0.0.1");
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// This test verifies that the relay information can be used to retrieve the
// subnet.
TEST(CfgSubnets4Test, selectSubnetByRelayAddress) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // Add them to the configuration.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SubnetSelector selector;

    // Check that without relay-info specified, subnets are not selected
    selector.giaddr_ = IOAddress("10.0.0.1");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.2");
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.3");
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Now specify relay info
    subnet1->setRelayInfo(IOAddress("10.0.0.1"));
    subnet2->setRelayInfo(IOAddress("10.0.0.2"));
    subnet3->setRelayInfo(IOAddress("10.0.0.3"));

    // And try again. This time relay-info is there and should match.
    selector.giaddr_ = IOAddress("10.0.0.1");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.2");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.3");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
}

// This test verifies that the subnet can be selected for the client
// using a source address if the client hasn't set the ciaddr.
TEST(CfgSubnets4Test, selectSubnetNoCiaddr) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // Make sure that initially the subnets don't exist.
    SubnetSelector selector;
    selector.remote_address_ = IOAddress("192.0.2.0");
    // Set some unicast local address to simulate a Renew.
    selector.local_address_ = IOAddress("10.0.0.100");
    ASSERT_FALSE(cfg.selectSubnet(selector));

    // Add one subnet and make sure it is returned.
    cfg.add(subnet1);
    selector.remote_address_ = IOAddress("192.0.2.63");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));

    // Add all other subnets.
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Make sure they are returned for the appropriate addresses.
    selector.remote_address_ = IOAddress("192.0.2.15");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.remote_address_ = IOAddress("192.0.2.85");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.remote_address_ = IOAddress("192.0.2.191");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Also, make sure that the NULL pointer is returned if the subnet
    // cannot be found.
    selector.remote_address_ = IOAddress("192.0.2.192");
    EXPECT_FALSE(cfg.selectSubnet(selector));
}

// This test verifies that the subnet can be selected using an address
// set on the local interface.
TEST(CfgSubnets4Test, selectSubnetInterface) {
    // The IfaceMgrTestConfig object initializes fake interfaces:
    // eth0, eth1 and lo on the configuration manager. The CfgSubnets4
    // object uses addresses assigned to these fake interfaces to
    // select the appropriate subnet.
    IfaceMgrTestConfig config(true);

    CfgSubnets4 cfg;
    SubnetSelector selector;

    // Initially, there are no subnets configured, so none of the IPv4
    // addresses assigned to eth0 and eth1 can match with any subnet.
    selector.iface_name_ = "eth0";
    EXPECT_FALSE(cfg.selectSubnet(selector));
    selector.iface_name_ = "eth1";
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Configure first subnet which address on eth0 corresponds to.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("10.0.0.1"), 24, 1, 2, 3));
    cfg.add(subnet1);

    // The address on eth0 should match the existing subnet.
    selector.iface_name_ = "eth0";
    Subnet4Ptr subnet1_ret = cfg.selectSubnet(selector);
    ASSERT_TRUE(subnet1_ret);
    EXPECT_EQ(subnet1->get().first, subnet1_ret->get().first);
    // There should still be no match for eth1.
    selector.iface_name_ = "eth1";
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Configure a second subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.1"), 24, 1, 2, 3));
    cfg.add(subnet2);

    // There should be match between eth0 and subnet1 and between eth1 and
    // subnet 2.
    selector.iface_name_ = "eth0";
    subnet1_ret = cfg.selectSubnet(selector);
    ASSERT_TRUE(subnet1_ret);
    EXPECT_EQ(subnet1->get().first, subnet1_ret->get().first);
    selector.iface_name_ = "eth1";
    Subnet4Ptr subnet2_ret = cfg.selectSubnet(selector);
    ASSERT_TRUE(subnet2_ret);
    EXPECT_EQ(subnet2->get().first, subnet2_ret->get().first);

    // This function throws an exception if the name of the interface is wrong.
    selector.iface_name_ = "bogus-interface";
    EXPECT_THROW(cfg.selectSubnet(selector), isc::BadValue);
}

// Checks that detection of duplicated subnet IDs works as expected. It should
// not be possible to add two IPv4 subnets holding the same ID.
TEST(CfgSubnets4Test, duplication) {
    CfgSubnets4 cfg;

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 123));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 124));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 123));

    ASSERT_NO_THROW(cfg.add(subnet1));
    EXPECT_NO_THROW(cfg.add(subnet2));
    // Subnet 3 has the same ID as subnet 1. It shouldn't be able to add it.
    EXPECT_THROW(cfg.add(subnet3), isc::dhcp::DuplicateSubnetID);
}

// This test checks if the IPv4 subnet can be selected based on the IPv6 address.
TEST(CfgSubnets4Test, 4o6subnet) {
    CfgSubnets4 cfg;

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 123));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 124));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 125));

    subnet2->get4o6().setSubnet4o6(IOAddress("2001:db8:1::"), 48);
    subnet3->get4o6().setSubnet4o6(IOAddress("2001:db8:2::"), 48);


    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SubnetSelector selector;
    selector.dhcp4o6_ = true;
    selector.remote_address_ = IOAddress("2001:db8:1::dead:beef");

    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
}


} // end of anonymous namespace
