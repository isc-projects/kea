// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/classify.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcp/option_string.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/iterative_allocator.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/cfg_hosts.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/log_utils.h>
#include <testutils/test_to_element.h>
#include <util/doubles.h>

#include <boost/range/adaptor/reversed.hpp>
#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief An allocator recording calls to @c initAfterConfigure.
class InitRecordingAllocator : public IterativeAllocator {
public:

    /// @brief Constructor.
    ///
    /// @param type specifies the type of allocated leases.
    /// @param subnet weak pointer to the subnet owning the allocator.
    InitRecordingAllocator(Lease::Type type, const WeakSubnetPtr& subnet)
        : IterativeAllocator(type, subnet), callcount_(0) {
    }

    /// @brief Increases the call count of this function.
    ///
    /// The call count can be later examined to check whether or not
    /// the function was called.
    virtual void initAfterConfigureInternal() {
        ++callcount_;
    };

    /// @brief Call count of the @c initAllocatorsAfterConfigure.
    int callcount_;
};

/// @brief Verifies that a set of subnets contains a given a subnet
///
/// @param cfg_subnets set of subnets in which to look
/// @param prefix prefix of the target subnet
/// @param exp_subnet_id expected id of the target subnet
/// @param exp_valid expected valid lifetime of the subnet
/// @param exp_network  pointer to the subnet's shared-network (if one)
void checkMergedSubnet(CfgSubnets4& cfg_subnets,
                       const std::string& prefix,
                       const SubnetID exp_subnet_id,
                       int exp_valid,
                       SharedNetwork4Ptr exp_network) {
    // Look for the network by prefix.
    auto subnet = cfg_subnets.getByPrefix(prefix);
    ASSERT_TRUE(subnet) << "subnet: " << prefix << " not found";

    // Make sure we have the one we expect.
    ASSERT_EQ(exp_subnet_id, subnet->getID()) << "subnet ID is wrong";
    ASSERT_EQ(exp_valid, subnet->getValid().get()) << "subnet valid time is wrong";

    SharedNetwork4Ptr shared_network;
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
TEST(CfgSubnets4Test, getSpecificSubnet) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(5)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(8)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(10)));

    // Store the subnets in a vector to make it possible to loop over
    // all configured subnets.
    std::vector<Subnet4Ptr> subnets;
    subnets.push_back(subnet1);
    subnets.push_back(subnet2);
    subnets.push_back(subnet3);

    // Add all subnets to the configuration.
    for (auto const& subnet : subnets) {
        ASSERT_NO_THROW(cfg.add(subnet)) << "failed to add subnet with id: "
            << subnet->getID();
    }

    // Iterate over all subnets and make sure they can be retrieved by
    // subnet identifier.
    for (auto const& subnet : boost::adaptors::reverse(subnets)) {
        ConstSubnet4Ptr subnet_returned = cfg.getBySubnetId(subnet->getID());
        ASSERT_TRUE(subnet_returned) << "failed to return subnet with id: "
            << subnet->getID();
        EXPECT_EQ(subnet->getID(), subnet_returned->getID());
        EXPECT_EQ(subnet->toText(), subnet_returned->toText());
    }

    // Repeat the previous test, but this time retrieve subnets by their
    // prefixes.
    for (auto const& subnet : boost::adaptors::reverse(subnets)) {
        ConstSubnet4Ptr subnet_returned = cfg.getByPrefix(subnet->toText());
        ASSERT_TRUE(subnet_returned) << "failed to return subnet with id: "
            << subnet->getID();
        EXPECT_EQ(subnet->getID(), subnet_returned->getID());
        EXPECT_EQ(subnet->toText(), subnet_returned->toText());
    }

    // Make sure that null pointers are returned for non-existing subnets.
    EXPECT_FALSE(cfg.getBySubnetId(SubnetID(123)));
    EXPECT_FALSE(cfg.getByPrefix("10.20.30.0/29"));
}

// This test verifies that a single subnet can be removed from the configuration.
TEST(CfgSubnets4Test, deleteSubnet) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(5)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 1, 2, 3, SubnetID(8)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.4.0"),
                                   26, 1, 2, 3, SubnetID(10)));

    ASSERT_NO_THROW(cfg.add(subnet1));
    ASSERT_NO_THROW(cfg.add(subnet2));
    ASSERT_NO_THROW(cfg.add(subnet3));

    // There should be three subnets.
    ASSERT_EQ(3, cfg.getAll()->size());
    // We're going to remove the subnet #2. Let's make sure it exists before
    // we remove it.
    ASSERT_TRUE(cfg.getByPrefix("192.0.3.0/26"));

    // Remove the subnet and make sure it is gone.
    ASSERT_NO_THROW(cfg.del(subnet2));
    ASSERT_EQ(2, cfg.getAll()->size());
    EXPECT_FALSE(cfg.getByPrefix("192.0.3.0/26"));

    // Remove another subnet by ID.
    ASSERT_NO_THROW(cfg.del(subnet1->getID()));
    ASSERT_EQ(1, cfg.getAll()->size());
    EXPECT_FALSE(cfg.getByPrefix("192.0.2.0/26"));
}

// This test verifies that replace a subnet works as expected.
TEST(CfgSubnets4Test, replaceSubnet) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.1.0"),
                                   26, 1, 2, 100, SubnetID(10)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 100, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 1, 2, 100, SubnetID(13)));

    ASSERT_NO_THROW(cfg.add(subnet1));
    ASSERT_NO_THROW(cfg.add(subnet2));
    ASSERT_NO_THROW(cfg.add(subnet3));

    // There should be three subnets.
    ASSERT_EQ(3, cfg.getAll()->size());
    // We're going to replace  the subnet #2. Let's make sure it exists before
    // we replace it.
    ASSERT_TRUE(cfg.getByPrefix("192.0.3.0/26"));

    // Replace the subnet and make sure it was updated.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"),
                                  26, 10, 20, 1000,  SubnetID(2)));
    Subnet4Ptr replaced = cfg.replace(subnet);
    ASSERT_TRUE(replaced);
    EXPECT_TRUE(replaced == subnet2);
    ASSERT_EQ(3, cfg.getAll()->size());
    Subnet4Ptr returned = cfg.getSubnet(SubnetID(2));
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
    subnet.reset(new Subnet4(IOAddress("192.0.3.0"),
                             26, 10, 20, 1000,  SubnetID(2)));
    replaced = cfg.replace(subnet);
    EXPECT_FALSE(replaced);
    returned = cfg.getSubnet(SubnetID(2));
    ASSERT_TRUE(returned);
    EXPECT_TRUE(returned == subnet2);

    // Changing prefix works even it is highly not recommended.
    subnet.reset(new Subnet4(IOAddress("192.0.10.0"),
                             26, 10, 20, 1000,  SubnetID(2)));
    replaced = cfg.replace(subnet);
    ASSERT_TRUE(replaced);
    EXPECT_TRUE(replaced == subnet2);
    returned = cfg.getSubnet(SubnetID(2));
    ASSERT_TRUE(returned);
    EXPECT_TRUE(returned == subnet);
}

// This test verifies that subnets configuration is properly merged.
TEST(CfgSubnets4Test, mergeSubnets) {
    // Create custom options dictionary for testing merge. We're keeping it
    // simple because they are more rigorous tests elsewhere.
    CfgOptionDefPtr cfg_def(new CfgOptionDef());
    cfg_def->add((OptionDefinitionPtr(new OptionDefinition("one", 1, "isc", "string"))));

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.1.0"),
                                   26, 1, 2, 100, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 100, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 1, 2, 100, SubnetID(3)));
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.4.0"),
                                   26, 1, 2, 100, SubnetID(4)));

    // Create the "existing" list of shared networks
    CfgSharedNetworks4Ptr networks(new CfgSharedNetworks4());
    SharedNetwork4Ptr shared_network1(new SharedNetwork4("shared-network1"));
    networks->add(shared_network1);
    SharedNetwork4Ptr shared_network2(new SharedNetwork4("shared-network2"));
    networks->add(shared_network2);

    // Empty network pointer.
    SharedNetwork4Ptr no_network;

    // Add Subnets 1, 2 and 4 to shared networks.
    ASSERT_NO_THROW(shared_network1->add(subnet1));
    ASSERT_NO_THROW(shared_network2->add(subnet2));
    ASSERT_NO_THROW(shared_network2->add(subnet4));

    // Create our "existing" configured subnets.
    CfgSubnets4 cfg_to;
    ASSERT_NO_THROW(cfg_to.add(subnet1));
    ASSERT_NO_THROW(cfg_to.add(subnet2));
    ASSERT_NO_THROW(cfg_to.add(subnet3));
    ASSERT_NO_THROW(cfg_to.add(subnet4));

    // Merge in an "empty" config. Should have the original config,
    // still intact.
    CfgSubnets4 cfg_from;
    ASSERT_NO_THROW(cfg_to.merge(cfg_def, networks, cfg_from));

    // We should have all four subnets, with no changes.
    ASSERT_EQ(4, cfg_to.getAll()->size());

    // Should be no changes to the configuration.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.1.0/26",
                                              SubnetID(1), 100, shared_network1));
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.2.0/26",
                                              SubnetID(2), 100, shared_network2));
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.3.0/26",
                                              SubnetID(3), 100, no_network));
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.4.0/26",
                                              SubnetID(4), 100, shared_network2));

    // Fill cfg_from configuration with subnets.
    // subnet 1b updates subnet 1 but leaves it in network 1 with the same ID.
    Subnet4Ptr subnet1b(new Subnet4(IOAddress("192.0.10.0"),
                                   26, 2, 3, 400, SubnetID(1)));
    subnet1b->setSharedNetworkName("shared-network1");

    // Add generic option 1 to subnet 1b.
    std::string value("Yay!");
    OptionPtr option(new Option(Option::V4, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(subnet1b->getCfgOption()->add(option, false, false, "isc"));

    // subnet 3b updates subnet 3 with different ID and removes it
    // from network 2
    Subnet4Ptr subnet3b(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 3, 4, 500, SubnetID(30)));

    // Now Add generic option 1 to subnet 3b.
    value = "Team!";
    option.reset(new Option(Option::V4, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(subnet3b->getCfgOption()->add(option, false, false, "isc"));

    // subnet 4b updates subnet 4 and moves it from network2 to network 1
    Subnet4Ptr subnet4b(new Subnet4(IOAddress("192.0.4.0"),
                                   26, 3, 4, 500, SubnetID(4)));
    subnet4b->setSharedNetworkName("shared-network1");

    // subnet 5 is new and belongs to network 2
    // Has two pools both with an option 1
    Subnet4Ptr subnet5(new Subnet4(IOAddress("192.0.5.0"),
                                   26, 1, 2, 300, SubnetID(5)));
    subnet5->setSharedNetworkName("shared-network2");

    // Add pool 1
    Pool4Ptr pool(new Pool4(IOAddress("192.0.5.10"), IOAddress("192.0.5.20")));
    value = "POOLS";
    option.reset(new Option(Option::V4, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, false, "isc"));
    subnet5->addPool(pool);

    // Add pool 2
    pool.reset(new Pool4(IOAddress("192.0.5.30"), IOAddress("192.0.5.40")));
    value ="RULE!";
    option.reset(new Option(Option::V4, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(pool->getCfgOption()->add(option, false, false, "isc"));
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
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.10.0/26",
                                              SubnetID(1), 400, shared_network1));

    // Let's verify that our option is there and populated correctly.
    auto subnet = cfg_to.getByPrefix("192.0.10.0/26");
    auto desc = subnet->getCfgOption()->get("isc", 1);
    ASSERT_TRUE(desc.option_);
    OptionStringPtr opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("Yay!", opstr->getValue());

    // The subnet2 should not be affected because it was not present.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.2.0/26",
                                              SubnetID(2), 100, shared_network2));

    // subnet3 should be replaced by subnet3b and no longer assigned to a network.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.3.0/26",
                                              SubnetID(30), 500, no_network));
    // Let's verify that our option is there and populated correctly.
    subnet = cfg_to.getByPrefix("192.0.3.0/26");
    desc = subnet->getCfgOption()->get("isc", 1);
    ASSERT_TRUE(desc.option_);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("Team!", opstr->getValue());
    EXPECT_TRUE(subnet->getCfgOption()->isEncapsulated());

    // subnet4 should be replaced by subnet4b and moved to network1.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.4.0/26",
                                              SubnetID(4), 500, shared_network1));

    // subnet5 should have been added to configuration.
    ASSERT_NO_FATAL_FAILURE(checkMergedSubnet(cfg_to, "192.0.5.0/26",
                                              SubnetID(5), 300, shared_network2));

    // Let's verify that both pools have the proper options.
    subnet = cfg_to.getByPrefix("192.0.5.0/26");
    const PoolPtr merged_pool = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.5.10"));
    ASSERT_TRUE(merged_pool);
    desc = merged_pool->getCfgOption()->get("isc", 1);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("POOLS", opstr->getValue());
    EXPECT_TRUE(merged_pool->getCfgOption()->isEncapsulated());

    const PoolPtr merged_pool2 = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.5.30"));
    ASSERT_TRUE(merged_pool2);
    desc = merged_pool2->getCfgOption()->get("isc", 1);
    opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("RULE!", opstr->getValue());
    EXPECT_TRUE(merged_pool2->getCfgOption()->isEncapsulated());
}

// This test verifies that it is possible to retrieve a subnet using an
// IP address.
TEST(CfgSubnets4Test, selectSubnetByCiaddr) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

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

// This test verifies that it is possible to select a subnet by
// matching an interface name.
TEST(CfgSubnets4Test, selectSubnetByIface) {
    // The IfaceMgrTestConfig object initializes fake interfaces:
    // eth0, eth1 and lo on the configuration manager. The CfgSubnets4
    // object uses interface names to select the appropriate subnet.
    IfaceMgrTestConfig config(true);

    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));
    // No interface defined for subnet1
    subnet2->setIface("lo");
    subnet3->setIface("eth1");

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Make sure that initially the subnets don't exist.
    SubnetSelector selector;
    // Set an interface to a name that is not defined in the config.
    // Subnet selection should fail.
    selector.iface_name_ = "eth0";
    ASSERT_FALSE(cfg.selectSubnet(selector));

    // Now select an interface name that matches. Selection should succeed
    // and return subnet3.
    selector.iface_name_ = "eth1";
    ConstSubnet4Ptr selected = cfg.selectSubnet(selector);
    ASSERT_TRUE(selected);
    EXPECT_EQ(subnet3, selected);
}

// This test verifies that it is possible to select subnet by interface
// name specified on the shared network level.
TEST(CfgSubnets4Test, selectSharedNetworkByIface) {
    // The IfaceMgrTestConfig object initializes fake interfaces:
    // eth0, eth1 and lo on the configuration manager. The CfgSubnets4
    // object uses interface names to select the appropriate subnet.
    IfaceMgrTestConfig config(true);

    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("172.16.2.0"), 24, 1, 2, 3,
                                   SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("10.1.2.0"), 24, 1, 2, 3,
                                   SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.3.4.0"), 24, 1, 2, 3,
                                   SubnetID(3)));
    subnet2->setIface("lo");

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SharedNetwork4Ptr network(new SharedNetwork4("network_eth1"));
    network->setIface("eth1");
    ASSERT_NO_THROW(network->add(subnet1));
    ASSERT_NO_THROW(network->add(subnet2));

    // Make sure that initially the subnets don't exist.
    SubnetSelector selector;
    // Set an interface to a name that is not defined in the config.
    // Subnet selection should fail.
    selector.iface_name_ = "eth0";
    ASSERT_FALSE(cfg.selectSubnet(selector));

    // Now select an interface name that matches. Selection should succeed
    // and return subnet3.
    selector.iface_name_ = "eth1";
    ConstSubnet4Ptr selected = cfg.selectSubnet(selector);
    ASSERT_TRUE(selected);
    SharedNetwork4Ptr network_returned;
    selected->getSharedNetwork(network_returned);
    ASSERT_TRUE(network_returned);
    EXPECT_EQ(network, network_returned);

    const Subnet4SimpleCollection* subnets_eth1 =
        network_returned->getAllSubnets();
    EXPECT_EQ(2, subnets_eth1->size());
    ASSERT_TRUE(network_returned->getSubnet(SubnetID(1)));
    ASSERT_TRUE(network_returned->getSubnet(SubnetID(2)));

    // Make sure that it is still possible to select subnet2 which is
    // outside of a shared network.
    selector.iface_name_ = "lo";
    selected = cfg.selectSubnet(selector);
    ASSERT_TRUE(selected);
    EXPECT_EQ(2, selected->getID());

    // Try selecting by eth1 again, but this time set subnet specific
    // interface name to eth0. Subnet selection should fail.
    selector.iface_name_ = "eth1";
    subnet1->setIface("eth0");
    subnet3->setIface("eth0");
    selected = cfg.selectSubnet(selector);
    ASSERT_FALSE(selected);

    // It should be possible to select by eth0, though.
    selector.iface_name_ = "eth0";
    selected = cfg.selectSubnet(selector);
    ASSERT_TRUE(selected);
    EXPECT_EQ(subnet1, selected);
}

// This test verifies that when the classification information is specified for
// subnets, the proper subnets are returned by the subnet configuration.
TEST(CfgSubnets4Test, selectSubnetByClasses) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

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

// This test verifies that shared network can be selected based on client
// classification.
TEST(CfgSubnets4Test, selectSharedNetworkByClasses) {
    IfaceMgrTestConfig config(true);

    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

    // Add them to the configuration.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    // Create first network and add first two subnets to it.
    SharedNetwork4Ptr network1(new SharedNetwork4("network1"));
    network1->setIface("eth1");
    network1->allowClientClass("device-type1");
    ASSERT_NO_THROW(network1->add(subnet1));
    ASSERT_NO_THROW(network1->add(subnet2));

    // Create second network and add last subnet there.
    SharedNetwork4Ptr network2(new SharedNetwork4("network2"));
    network2->setIface("eth1");
    network2->allowClientClass("device-type2");
    ASSERT_NO_THROW(network2->add(subnet3));

    // Use interface name as a selector. This guarantees that subnet
    // selection will be made based on the classification.
    SubnetSelector selector;
    selector.iface_name_ = "eth1";

    // If the client has "device-type2" class, it is expected that the
    // second network will be used. This network has only one subnet
    // in it, i.e. subnet3.
    ClientClasses client_classes;
    client_classes.insert("device-type2");
    selector.client_classes_ = client_classes;
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));

    // Switch to device-type1 and expect that we assigned a subnet from
    // another shared network.
    client_classes.clear();
    client_classes.insert("device-type1");
    selector.client_classes_ = client_classes;

    ConstSubnet4Ptr subnet = cfg.selectSubnet(selector);
    ASSERT_TRUE(subnet);
    SharedNetwork4Ptr network;
    subnet->getSharedNetwork(network);
    ASSERT_TRUE(network);
    EXPECT_EQ("network1", network->getName());
}

// This test verifies the option selection can be used and is only
// used when present.
TEST(CfgSubnets4Test, selectSubnetByOptionSelect) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

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
    subnet2->addRelayAddress(IOAddress("10.0.0.1"));
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
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

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
    subnet1->addRelayAddress(IOAddress("10.0.0.1"));
    subnet2->addRelayAddress(IOAddress("10.0.0.2"));
    subnet3->addRelayAddress(IOAddress("10.0.0.3"));

    // And try again. This time relay-info is there and should match.
    selector.giaddr_ = IOAddress("10.0.0.1");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.2");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.3");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
}

// This test verifies that the relay information specified on the shared
// network level can be used to select a subnet.
TEST(CfgSubnets4Test, selectSharedNetworkByRelayAddressNetworkLevel) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

    // Add them to the configuration.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SharedNetwork4Ptr network(new SharedNetwork4("network"));
    network->add(subnet2);

    SubnetSelector selector;

    // Now specify relay info. Note that for the second subnet we specify
    // relay info on the network level.
    subnet1->addRelayAddress(IOAddress("10.0.0.1"));
    network->addRelayAddress(IOAddress("10.0.0.2"));
    subnet3->addRelayAddress(IOAddress("10.0.0.3"));

    // And try again. This time relay-info is there and should match.
    selector.giaddr_ = IOAddress("10.0.0.1");
    EXPECT_EQ(subnet1, cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.2");
    EXPECT_EQ(subnet2, cfg.selectSubnet(selector));
    selector.giaddr_ = IOAddress("10.0.0.3");
    EXPECT_EQ(subnet3, cfg.selectSubnet(selector));
}

// This test verifies that the relay information specified on the subnet
// level can be used to select a subnet and the fact that a subnet belongs
// to a shared network doesn't affect the process.
TEST(CfgSubnets4Test, selectSharedNetworkByRelayAddressSubnetLevel) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

    // Add them to the configuration.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SharedNetwork4Ptr network1(new SharedNetwork4("network1"));
    network1->add(subnet1);

    SharedNetwork4Ptr network2(new SharedNetwork4("network2"));
    network2->add(subnet2);

    SubnetSelector selector;

    // Now specify relay info. Note that for the second subnet we specify
    // relay info on the network level.
    subnet1->addRelayAddress(IOAddress("10.0.0.1"));
    subnet2->addRelayAddress(IOAddress("10.0.0.2"));
    subnet3->addRelayAddress(IOAddress("10.0.0.3"));

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
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"),
                                   26, 1, 2, 3, SubnetID(3)));

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
    Subnet4Ptr subnet1(new Subnet4(IOAddress("10.0.0.1"),
                                   24, 1, 2, 3, SubnetID(1)));
    cfg.add(subnet1);

    // The address on eth0 should match the existing subnet.
    selector.iface_name_ = "eth0";
    ConstSubnet4Ptr subnet1_ret = cfg.selectSubnet(selector);
    ASSERT_TRUE(subnet1_ret);
    EXPECT_EQ(subnet1->get().first, subnet1_ret->get().first);
    // There should still be no match for eth1.
    selector.iface_name_ = "eth1";
    EXPECT_FALSE(cfg.selectSubnet(selector));

    // Configure a second subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.1"),
                                   24, 1, 2, 3, SubnetID(2)));
    cfg.add(subnet2);

    // There should be match between eth0 and subnet1 and between eth1 and
    // subnet 2.
    selector.iface_name_ = "eth0";
    subnet1_ret = cfg.selectSubnet(selector);
    ASSERT_TRUE(subnet1_ret);
    EXPECT_EQ(subnet1->get().first, subnet1_ret->get().first);
    selector.iface_name_ = "eth1";
    ConstSubnet4Ptr subnet2_ret = cfg.selectSubnet(selector);
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
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.2.1"), 26, 1, 2, 3, 125));

    ASSERT_NO_THROW(cfg.add(subnet1));
    EXPECT_NO_THROW(cfg.add(subnet2));
    // Subnet 3 has the same ID as subnet 1. It shouldn't be able to add it.
    EXPECT_THROW(cfg.add(subnet3), isc::dhcp::DuplicateSubnetID);
    // Subnet 4 has a similar but different subnet as subnet 1.
    EXPECT_NO_THROW(cfg.add(subnet4));
}

// This test checks if the IPv4 subnet can be selected based on the IPv6 address.
TEST(CfgSubnets4Test, 4o6subnetMatchByAddress) {
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

    EXPECT_EQ(subnet2, cfg.selectSubnet4o6(selector));
}

// This test checks if the IPv4 subnet can be selected based on the value of
// interface-id option.
TEST(CfgSubnets4Test, 4o6subnetMatchByInterfaceId) {
    CfgSubnets4 cfg;

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 123));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 124));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 125));

    const uint8_t dummyPayload1[] = { 1, 2, 3, 4};
    const uint8_t dummyPayload2[] = { 1, 2, 3, 5};
    std::vector<uint8_t> data1(dummyPayload1, dummyPayload1 + sizeof(dummyPayload1));
    std::vector<uint8_t> data2(dummyPayload2, dummyPayload2 + sizeof(dummyPayload2));

    OptionPtr interfaceId1(new Option(Option::V6, D6O_INTERFACE_ID, data1));
    OptionPtr interfaceId2(new Option(Option::V6, D6O_INTERFACE_ID, data2));

    subnet2->get4o6().setInterfaceId(interfaceId1);

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SubnetSelector selector;
    selector.dhcp4o6_ = true;
    selector.interface_id_ = interfaceId2;
    // We have mismatched interface-id options (data1 vs data2). Should not match.
    EXPECT_FALSE(cfg.selectSubnet4o6(selector));

    // This time we have correct interface-id. Should match.
    selector.interface_id_ = interfaceId1;
    EXPECT_EQ(subnet2, cfg.selectSubnet4o6(selector));
}

// This test checks if the IPv4 subnet can be selected based on the value of
// interface name option.
TEST(CfgSubnets4Test, 4o6subnetMatchByInterfaceName) {
    CfgSubnets4 cfg;

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 123));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 124));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 125));

    subnet2->get4o6().setIface4o6("eth7");

    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    SubnetSelector selector;
    selector.dhcp4o6_ = true;
    selector.iface_name_ = "eth5";
    // We have mismatched interface names. Should not match.
    EXPECT_FALSE(cfg.selectSubnet4o6(selector));

    // This time we have correct names. Should match.
    selector.iface_name_ = "eth7";
    EXPECT_EQ(subnet2, cfg.selectSubnet4o6(selector));
}

// This test check if IPv4 subnets can be unparsed in a predictable way,
TEST(CfgSubnets4Test, unparseSubnet) {
    CfgSubnets4 cfg;

    // Add some subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 123));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 124));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 125));

    subnet1->allowClientClass("foo");
    subnet1->allowClientClass("bar");

    subnet1->setT1Percent(0.45);
    subnet1->setT2Percent(0.70);
    subnet1->setCacheThreshold(0.20);

    subnet2->setIface("lo");
    subnet2->addRelayAddress(IOAddress("10.0.0.1"));
    subnet2->setValid(Triplet<uint32_t>(100));
    subnet2->setStoreExtendedInfo(true);
    subnet2->setCacheMaxAge(80);
    subnet2->setOfferLft(99);

    subnet3->setIface("eth1");
    subnet3->addAdditionalClass("foo");
    subnet3->addAdditionalClass("bar");
    subnet3->setCalculateTeeTimes(true);
    subnet3->setT1Percent(0.50);
    subnet3->setT2Percent(0.65);
    subnet3->setReservationsGlobal(false);
    subnet3->setReservationsInSubnet(true);
    subnet3->setReservationsOutOfPool(false);
    subnet3->setAuthoritative(false);
    subnet3->setMatchClientId(true);
    subnet3->setSiaddr(IOAddress("192.0.2.2"));
    subnet3->setSname("frog");
    subnet3->setFilename("/dev/null");
    subnet3->setValid(Triplet<uint32_t>(100, 200, 300));
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
        "    \"subnet\": \"192.0.2.0/26\",\n"
        "    \"t1-percent\": 0.45,"
        "    \"t2-percent\": 0.7,"
        "    \"cache-threshold\": .20,\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"valid-lifetime\": 3,\n"
        "    \"min-valid-lifetime\": 3,\n"
        "    \"max-valid-lifetime\": 3,\n"
        "    \"client-classes\": [ \"foo\", \"bar\" ],\n"
        "    \"4o6-interface\": \"\",\n"
        "    \"4o6-interface-id\": \"\",\n"
        "    \"4o6-subnet\": \"\",\n"
        "    \"option-data\": [ ],\n"
        "    \"pools\": [ ],\n"
        "    \"user-context\": { \"comment\": \"foo\" }\n"
        "},{\n"
        "    \"id\": 124,\n"
        "    \"subnet\": \"192.0.2.64/26\",\n"
        "    \"interface\": \"lo\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ \"10.0.0.1\" ] },\n"
        "    \"valid-lifetime\": 100,\n"
        "    \"min-valid-lifetime\": 100,\n"
        "    \"max-valid-lifetime\": 100,\n"
        "    \"4o6-interface\": \"\",\n"
        "    \"4o6-interface-id\": \"\",\n"
        "    \"4o6-subnet\": \"\",\n"
        "    \"user-context\": {},\n"
        "    \"option-data\": [ ],\n"
        "    \"pools\": [ ],\n"
        "    \"store-extended-info\": true,\n"
        "    \"cache-max-age\": 80,\n"
        "    \"offer-lifetime\": 99\n"
        "},{\n"
        "    \"id\": 125,\n"
        "    \"subnet\": \"192.0.2.128/26\",\n"
        "    \"interface\": \"eth1\",\n"
        "    \"match-client-id\": true,\n"
        "    \"next-server\": \"192.0.2.2\",\n"
        "    \"server-hostname\": \"frog\",\n"
        "    \"boot-file-name\": \"/dev/null\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"valid-lifetime\": 200,\n"
        "    \"min-valid-lifetime\": 100,\n"
        "    \"max-valid-lifetime\": 300,\n"
        "    \"4o6-interface\": \"\",\n"
        "    \"4o6-interface-id\": \"\",\n"
        "    \"4o6-subnet\": \"\",\n"
        "    \"authoritative\": false,\n"
        "    \"reservations-global\": false,\n"
        "    \"reservations-in-subnet\": true,\n"
        "    \"reservations-out-of-pool\": false,\n"
        "    \"option-data\": [ ],\n"
        "    \"pools\": [ ]\n,"
        "    \"evaluate-additional-classes\": [ \"foo\", \"bar\" ],\n"
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

    runToElementTest<CfgSubnets4>(expected, cfg);
}

// This test check if IPv4 pools can be unparsed in a predictable way,
TEST(CfgSubnets4Test, unparsePool) {
    CfgSubnets4 cfg;

    // Add a subnet with pools
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 123));
    Pool4Ptr pool1(new Pool4(IOAddress("192.0.2.1"), IOAddress("192.0.2.10")));
    Pool4Ptr pool2(new Pool4(IOAddress("192.0.2.64"), 26));
    pool2->allowClientClass("bar");

    std::string json1 = "{ \"comment\": \"foo\", \"version\": 1 }";
    data::ElementPtr ctx1 = data::Element::fromJSON(json1);
    pool1->setContext(ctx1);
    data::ElementPtr ctx2 = data::Element::fromJSON("{ \"foo\": \"bar\" }");
    pool2->setContext(ctx2);
    pool2->addAdditionalClass("foo");

    subnet->addPool(pool1);
    subnet->addPool(pool2);
    cfg.add(subnet);

    // Unparse
    std::string expected = "[\n"
        "{\n"
        "    \"id\": 123,\n"
        "    \"subnet\": \"192.0.2.0/24\",\n"
        "    \"renew-timer\": 1,\n"
        "    \"rebind-timer\": 2,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"valid-lifetime\": 3,\n"
        "    \"min-valid-lifetime\": 3,\n"
        "    \"max-valid-lifetime\": 3,\n"
        "    \"4o6-interface\": \"\",\n"
        "    \"4o6-interface-id\": \"\",\n"
        "    \"4o6-subnet\": \"\",\n"
        "    \"option-data\": [],\n"
        "    \"pools\": [\n"
        "        {\n"
        "            \"option-data\": [ ],\n"
        "            \"pool\": \"192.0.2.1-192.0.2.10\",\n"
        "            \"user-context\": { \"comment\": \"foo\",\n"
        "                                \"version\": 1 }\n"
        "        },{\n"
        "            \"option-data\": [ ],\n"
        "            \"pool\": \"192.0.2.64/26\",\n"
        "            \"user-context\": { \"foo\": \"bar\" },\n"
        "            \"client-classes\": [ \"bar\" ],\n"
        "            \"evaluate-additional-classes\": [ \"foo\" ]\n"
        "        }\n"
        "    ]\n"
        "} ]\n";
    runToElementTest<CfgSubnets4>(expected, cfg);
}

// This test verifies that it is possible to retrieve a subnet using subnet-id.
TEST(CfgSubnets4Test, getSubnet) {
    CfgSubnets4 cfg;

    // Create 3 subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 100));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 200));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 300));

    // Add one subnet and make sure it is returned.
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    EXPECT_EQ(subnet1, cfg.getSubnet(100));
    EXPECT_EQ(subnet2, cfg.getSubnet(200));
    EXPECT_EQ(subnet3, cfg.getSubnet(300));
    EXPECT_EQ(Subnet4Ptr(), cfg.getSubnet(400)); // no such subnet
}

// This test verifies that hasSubnetWithServerId returns correct value.
TEST(CfgSubnets4Test, hasSubnetWithServerId) {
    CfgSubnets4 cfg;

    // Initially, there is no server identifier option present.
    EXPECT_FALSE(cfg.hasSubnetWithServerId(IOAddress("1.2.3.4")));

    const OptionDefinition& def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();
    OptionCustomPtr opt_server_id(new OptionCustom(def, Option::V4));
    opt_server_id->writeAddress(IOAddress("1.2.3.4"));
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 100));
    subnet->getCfgOption()->add(opt_server_id, false, false,
                                DHCP4_OPTION_SPACE);
    cfg.add(subnet);

    EXPECT_TRUE(cfg.hasSubnetWithServerId(IOAddress("1.2.3.4")));
    EXPECT_FALSE(cfg.hasSubnetWithServerId(IOAddress("2.3.4.5")));
}

// This test verifies the Subnet4 parser's validation logic for id parameter.
TEST(CfgSubnets4Test, idValidation) {
    {
        // id 0.
        SCOPED_TRACE("id 0");
        std::string json =
            "        {\n"
            "            \"id\": 0,\n"
            "            \"subnet\": \"10.1.2.0/24\"\n"
            "        }\n";
        data::ElementPtr elems;
        ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
            << "invalid JSON:" << json  << "\n test is broken";
        std::string expected = "subnet configuration failed: ";
        expected += "The 'id' value (0) is not within ";
        expected += "expected range: (1 - 4294967294)";
        try {
            // Attempt to parse the configuration.
            Subnet4ConfigParser parser;
            Subnet4Ptr subnet = parser.parse(elems);
            ADD_FAILURE() << "expected exception";
        } catch (const std::exception& ex) {
            EXPECT_EQ(expected, ex.what());
        }
    }

    {
        // id 4294967295.
        SCOPED_TRACE("id 4294967295");
        std::string json =
            "        {\n"
            "            \"id\": 4294967295,\n"
            "            \"subnet\": \"10.1.2.0/24\"\n"
            "        }\n";
        data::ElementPtr elems;
        ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
            << "invalid JSON:" << json  << "\n test is broken";
        std::string expected = "subnet configuration failed: ";
        expected += "The 'id' value (4294967295) is not within ";
        expected += "expected range: (1 - 4294967294)";
        try {
            // Attempt to parse the configuration.
            Subnet4ConfigParser parser;
            Subnet4Ptr subnet = parser.parse(elems);
            ADD_FAILURE() << "expected exception";
        } catch (const std::exception& ex) {
            EXPECT_EQ(expected, ex.what());
        }
    }

    {
        // id 1 (valid).
        SCOPED_TRACE("id 1");
        std::string json =
            "        {\n"
            "            \"id\": 1,\n"
            "            \"subnet\": \"10.1.2.0/24\"\n"
            "        }\n";
        data::ElementPtr elems;
        ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
            << "invalid JSON:" << json  << "\n test is broken";
        try {
            // Attempt to parse the configuration.
            Subnet4ConfigParser parser;
            Subnet4Ptr subnet = parser.parse(elems);
            EXPECT_TRUE(subnet);
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "unexpected failure " << ex.what();
        }
    }
}

// This test verifies the Subnet4 parser's validation logic for
// t1-percent and t2-percent parameters.
TEST(CfgSubnets4Test, teeTimePercentValidation) {

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
    // required for a Subnet4.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"valid-lifetime\": 300, \n"
        "            \"match-client-id\": false, \n"
        "            \"authoritative\": false, \n"
        "            \"next-server\": \"\", \n"
        "            \"server-hostname\": \"\", \n"
        "            \"boot-file-name\": \"\", \n"
        "            \"client-classes\": [] , \n"
        "            \"evaluate-additional-classes\": [] \n,"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false, \n"
        "            \"4o6-interface\": \"\", \n"
        "            \"4o6-interface-id\": \"\", \n"
        "            \"4o6-subnet\": \"\" \n"
        "        }";


    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto const& test : tests) {
        {
            SCOPED_TRACE("test: " + test.label);

            // Set this scenario's configuration parameters
            elems->set("calculate-tee-times", data::Element::create(test.calculate_tee_times));
            elems->set("t1-percent", data::Element::create(test.t1_percent));
            elems->set("t2-percent", data::Element::create(test.t2_percent));

            Subnet4Ptr subnet;
            try {
                // Attempt to parse the configuration.
                Subnet4ConfigParser parser;
                subnet = parser.parse(elems);
            } catch (const std::exception& ex) {
                if (!test.error_message.empty()) {
                    // We expected a failure, did we fail the correct way?
                    EXPECT_EQ(test.error_message, ex.what());
                } else {
                    // Should not have failed.
                    ADD_FAILURE() << "Scenario should not have failed: " << ex.what();
                }

                // Either way we're done with this scenario.
                continue;
            }

            // We parsed correctly, make sure the values are right.
            EXPECT_EQ(test.calculate_tee_times, subnet->getCalculateTeeTimes());
            EXPECT_TRUE(util::areDoublesEquivalent(test.t1_percent, subnet->getT1Percent()));
            EXPECT_TRUE(util::areDoublesEquivalent(test.t2_percent, subnet->getT2Percent()));
        }
    }
}

// This test verifies the Subnet4 parser's validation logic for
// valid-lifetime and indirectly shared lifetime parsing.
TEST(CfgSubnets4Test, validLifetimeValidation) {
    // First we create a set of elements that provides all
    // required for a Subnet4.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"match-client-id\": false, \n"
        "            \"authoritative\": false, \n"
        "            \"next-server\": \"\", \n"
        "            \"server-hostname\": \"\", \n"
        "            \"boot-file-name\": \"\", \n"
        "            \"client-classes\": [], \n"
        "            \"evaluate-additional-classes\": [], \n"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false, \n"
        "            \"4o6-interface\": \"\", \n"
        "            \"4o6-interface-id\": \"\", \n"
        "            \"4o6-subnet\": \"\" \n"
        "        }";


    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    {
        SCOPED_TRACE("no valid-lifetime");

        data::ElementPtr copied = data::copy(elems);
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_TRUE(subnet->getValid().unspecified());
        data::ConstElementPtr repr = subnet->toElement();
        EXPECT_FALSE(repr->get("valid-lifetime"));
        EXPECT_FALSE(repr->get("min-valid-lifetime"));
        EXPECT_FALSE(repr->get("max-valid-lifetime"));
    }

    {
        SCOPED_TRACE("valid-lifetime only");

        data::ElementPtr copied = data::copy(elems);
        copied->set("valid-lifetime", data::Element::create(100));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(100, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(100, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }

    {
        SCOPED_TRACE("min-valid-lifetime only");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(100));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(100, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(100, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }

    {
        SCOPED_TRACE("max-valid-lifetime only");
        data::ElementPtr copied = data::copy(elems);
        copied->set("max-valid-lifetime", data::Element::create(100));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(100, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(100, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }

    {
        SCOPED_TRACE("min-valid-lifetime and valid-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(100));
        // Use a different (and greater) value for the default.
        copied->set("valid-lifetime", data::Element::create(200));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(200, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(200, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("200", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("200", max_value->str());
    }

    {
        SCOPED_TRACE("max-valid-lifetime and valid-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("max-valid-lifetime", data::Element::create(200));
        // Use a different (and smaller) value for the default.
        copied->set("valid-lifetime", data::Element::create(100));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(100, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(200, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("200", max_value->str());
    }

    {
        SCOPED_TRACE("min-valid-lifetime and max-valid-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(100));
        copied->set("max-valid-lifetime", data::Element::create(200));
        Subnet4ConfigParser parser;
        // No idea about the value to use for the default so failing.
        ASSERT_THROW(parser.parse(copied), DhcpConfigError);
    }

    {
        SCOPED_TRACE("all 3 (min, max and default) valid-lifetime");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(100));
        // Use a different (and greater) value for the default.
        copied->set("valid-lifetime", data::Element::create(200));
        // Use a different (and greater than both) value for max.
        copied->set("max-valid-lifetime", data::Element::create(300));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(200, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(300, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("200", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("300", max_value->str());
    }

    {
        SCOPED_TRACE("default value too small");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(200));
        // 100 < 200 so it will fail.
        copied->set("valid-lifetime", data::Element::create(100));
        // Use a different (and greater than both) value for max.
        copied->set("max-valid-lifetime", data::Element::create(300));
        Subnet4ConfigParser parser;
        ASSERT_THROW(parser.parse(copied), DhcpConfigError);
    }

    {
        SCOPED_TRACE("default value too large");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(100));
        // Use a different (and greater) value for the default.
        copied->set("valid-lifetime", data::Element::create(300));
        // 300 > 200 so it will fail.
        copied->set("max-valid-lifetime", data::Element::create(200));
        Subnet4ConfigParser parser;
        ASSERT_THROW(parser.parse(copied), DhcpConfigError);
    }

    {
        SCOPED_TRACE("equal bounds are no longer ignored");
        data::ElementPtr copied = data::copy(elems);
        copied->set("min-valid-lifetime", data::Element::create(100));
        copied->set("valid-lifetime", data::Element::create(100));
        copied->set("max-valid-lifetime", data::Element::create(100));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        ASSERT_TRUE(subnet);
        EXPECT_FALSE(subnet->getValid().unspecified());
        EXPECT_EQ(100, subnet->getValid().get());
        EXPECT_EQ(100, subnet->getValid().getMin());
        EXPECT_EQ(100, subnet->getValid().getMax());
        data::ConstElementPtr repr = subnet->toElement();
        data::ConstElementPtr value = repr->get("valid-lifetime");
        ASSERT_TRUE(value);
        EXPECT_EQ("100", value->str());
        data::ConstElementPtr min_value = repr->get("min-valid-lifetime");
        ASSERT_TRUE(min_value);
        EXPECT_EQ("100", min_value->str());
        data::ConstElementPtr max_value = repr->get("max-valid-lifetime");
        ASSERT_TRUE(max_value);
        EXPECT_EQ("100", max_value->str());
    }
}

// This test verifies the Subnet4 parser's validation logic for
// hostname sanitizer values.
TEST(CfgSubnets4Test, hostnameSanitizierValidation) {

    // First we create a set of elements that provides all
    // required for a Subnet4.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"match-client-id\": false, \n"
        "            \"authoritative\": false, \n"
        "            \"next-server\": \"\", \n"
        "            \"server-hostname\": \"\", \n"
        "            \"boot-file-name\": \"\", \n"
        "            \"client-classes\": [], \n"
        "            \"evaluate-additional-classes\": [], \n"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false, \n"
        "            \"4o6-interface\": \"\", \n"
        "            \"4o6-interface-id\": \"\", \n"
        "            \"4o6-subnet\": \"\" \n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    {
        SCOPED_TRACE("invalid regular expression");

        data::ElementPtr copied = data::copy(elems);
        copied->set("hostname-char-set", data::Element::create("^[A-"));
        copied->set("hostname-char-replacement", data::Element::create("x"));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        EXPECT_THROW_MSG(subnet = parser.parse(copied), DhcpConfigError,
                         "subnet configuration failed: hostname-char-set "
                         "'^[A-' is not a valid regular expression");

    }
    {
        SCOPED_TRACE("valid regular expression");

        data::ElementPtr copied = data::copy(elems);
        copied->set("hostname-char-set", data::Element::create("^[A-Z]"));
        copied->set("hostname-char-replacement", data::Element::create("x"));
        Subnet4Ptr subnet;
        Subnet4ConfigParser parser;
        ASSERT_NO_THROW(subnet = parser.parse(copied));
        EXPECT_EQ("^[A-Z]", subnet->getHostnameCharSet().get());
        EXPECT_EQ("x", subnet->getHostnameCharReplacement().get());
    }
}

// This test verifies the Subnet4 parser's validation logic for
// lease cache parameters.
TEST(CfgSubnets4Test, cacheParamValidation) {

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
    // required for a Subnet4.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"interface\": \"\", \n"
        "            \"renew-timer\": 100, \n"
        "            \"rebind-timer\": 200, \n"
        "            \"valid-lifetime\": 300, \n"
        "            \"match-client-id\": false, \n"
        "            \"authoritative\": false, \n"
        "            \"next-server\": \"\", \n"
        "            \"server-hostname\": \"\", \n"
        "            \"boot-file-name\": \"\", \n"
        "            \"client-classes\": [], \n"
        "            \"evaluate-additional-classes\": [], \n"
        "            \"reservations-global\": false, \n"
        "            \"reservations-in-subnet\": true, \n"
        "            \"reservations-out-of-pool\": false, \n"
        "            \"4o6-interface\": \"\", \n"
        "            \"4o6-interface-id\": \"\", \n"
        "            \"4o6-subnet\": \"\" \n"
        "        }";


    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
                    << "invalid JSON:" << json << "\n test is broken";

    // Iterate over the test scenarios, verifying each prescribed
    // outcome.
    for (auto const& test : tests) {
        {
            SCOPED_TRACE("test: " + test.label);

            // Set this scenario's configuration parameters
            elems->set("cache-threshold", data::Element::create(test.threshold));

            Subnet4Ptr subnet;
            try {
                // Attempt to parse the configuration.
                Subnet4ConfigParser parser;
                subnet = parser.parse(elems);
            } catch (const std::exception& ex) {
                if (!test.error_message.empty()) {
                    // We expected a failure, did we fail the correct way?
                    EXPECT_EQ(test.error_message, ex.what());
                } else {
                    // Should not have failed.
                    ADD_FAILURE() << "Scenario should not have failed: " << ex.what();
                }

                // Either way we're done with this scenario.
                continue;
            }

            // We parsed correctly, make sure the values are right.
            EXPECT_TRUE(util::areDoublesEquivalent(test.threshold, subnet->getCacheThreshold()));
        }
    }
}

// This test verifies that the optional interface check works as expected.
TEST(CfgSubnets4Test, iface) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"interface\": \"eth1961\"\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    // The interface check can be disabled.
    Subnet4ConfigParser parser_no_check(false);
    Subnet4Ptr subnet;
    EXPECT_NO_THROW(subnet = parser_no_check.parse(elems));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getIface().unspecified());
    EXPECT_EQ("eth1961", subnet->getIface().get());

    // Retry with the interface check enabled.
    Subnet4ConfigParser parser;
    EXPECT_THROW(parser.parse(elems), DhcpConfigError);

    // Configure default test interfaces.
    IfaceMgrTestConfig config(true);

    EXPECT_NO_THROW(subnet = parser_no_check.parse(elems));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getIface().unspecified());
    EXPECT_EQ("eth1961", subnet->getIface().get());

    EXPECT_NO_THROW(subnet = parser.parse(elems));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getIface().unspecified());
    EXPECT_EQ("eth1961", subnet->getIface().get());
}

// This test verifies that update statistics works as expected.
TEST(CfgSubnets4Test, updateStatistics) {
    CfgMgr::instance().clear();

    CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ObservationPtr observation;
    SubnetID subnet_id = 100;

    LeaseMgrFactory::create("type=memfile universe=4 persist=false");

    // remove all statistics
    StatsMgr::instance().removeAll();

    // Create subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 100));

    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.0"), 26));
    subnet->addPool(pool);

    // Add subnet.
    cfg->add(subnet);

    observation = StatsMgr::instance().getObservation(
        "cumulative-assigned-addresses");
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
                               "total-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "total-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "assigned-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "cumulative-assigned-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "declined-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-declined-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-leases")));
    ASSERT_FALSE(observation);

    cfg->updateStatistics();

    observation = StatsMgr::instance().getObservation(
        "cumulative-assigned-addresses");
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
                               "total-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(64, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "total-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(64, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "assigned-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "cumulative-assigned-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "declined-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-declined-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-leases")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);
}

// This test verifies that remove statistics works as expected.
TEST(CfgSubnets4Test, removeStatistics) {
    CfgSubnets4 cfg;
    ObservationPtr observation;
    SubnetID subnet_id = 100;

    // remove all statistics and then set them all to 0
    StatsMgr::instance().removeAll();

    // Create subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 100));

    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.0"), 26));
    subnet->addPool(pool);

    // Add subnet.
    cfg.add(subnet);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-addresses"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "total-addresses")),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "total-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-addresses"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "assigned-addresses")),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "assigned-addresses")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-addresses"),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-addresses"));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "cumulative-assigned-addresses")),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "cumulative-assigned-addresses")));
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
                               StatsMgr::generateName("pool", 0, "declined-addresses")),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "declined-addresses")));
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
                               StatsMgr::generateName("pool", 0, "reclaimed-declined-addresses")),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-declined-addresses")));
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

    StatsMgr::instance().setValue(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-leases")),
        int64_t(0));

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-leases")));
    ASSERT_TRUE(observation);
    ASSERT_EQ(0, observation->getInteger().first);

    // remove all statistics
    cfg.removeStatistics();

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "total-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "total-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "assigned-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "assigned-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "cumulative-assigned-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "cumulative-assigned-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "declined-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-declined-addresses"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-declined-addresses")));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               "reclaimed-leases"));
    ASSERT_FALSE(observation);

    observation = StatsMgr::instance().getObservation(
        StatsMgr::generateName("subnet", subnet_id,
                               StatsMgr::generateName("pool", 0, "reclaimed-leases")));
    ASSERT_FALSE(observation);
}

// This test verifies that in range host reservation works as expected.
TEST(CfgSubnets4Test, host) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"reservations\": [ {\n"
        "                \"hw-address\": \"aa:bb:cc:dd:ee:ff\", \n"
        "                \"ip-address\": \"10.1.2.1\" } ]\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    Subnet4ConfigParser parser;
    Subnet4Ptr subnet;
    EXPECT_NO_THROW(subnet = parser.parse(elems));
    ASSERT_TRUE(subnet);
    CfgHostsPtr cfg_hosts = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(cfg_hosts);
    HostCollection hosts = cfg_hosts->getAll4(SubnetID(1));
    ASSERT_EQ(1, hosts.size());
    ConstHostPtr host = hosts[0];
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("hwaddr=AABBCCDDEEFF", host->getIdentifierAsText());
    EXPECT_EQ("10.1.2.1", host->getIPv4Reservation().toText());

    CfgMgr::instance().clear();
}

// This test verifies that an out of range host reservation is rejected.
TEST(CfgSubnets4Test, outOfRangeHost) {
    // Create a configuration.
    std::string json =
        "        {"
        "            \"id\": 1,\n"
        "            \"subnet\": \"10.1.2.0/24\", \n"
        "            \"reservations\": [ {\n"
        "                \"hw-address\": \"aa:bb:cc:dd:ee:ff\", \n"
        "                \"ip-address\": \"10.2.2.1\" } ]\n"
        "        }";

    data::ElementPtr elems;
    ASSERT_NO_THROW(elems = data::Element::fromJSON(json))
        << "invalid JSON:" << json << "\n test is broken";

    Subnet4ConfigParser parser;
    std::string msg = "specified reservation '10.2.2.1' is not within ";
    msg += "the IPv4 subnet '10.1.2.0/24'";
    EXPECT_THROW_MSG(parser.parse(elems), DhcpConfigError, msg);
}

// This test verifies that the getLinks tool works as expected.
TEST(CfgSubnets4Test, getLinks) {
    CfgSubnets4 cfg;

    // Create 4 subnets.
    Subnet4Ptr subnet0(new Subnet4(IOAddress("0.0.0.0"),
                                   24, 1, 2, 3, SubnetID(111)));
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.1.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 1, 2, 3, SubnetID(3)));

    // Add all subnets to the configuration.
    ASSERT_NO_THROW(cfg.add(subnet0));
    ASSERT_NO_THROW(cfg.add(subnet1));
    ASSERT_NO_THROW(cfg.add(subnet2));
    ASSERT_NO_THROW(cfg.add(subnet3));

    // No 192.0.4.0 subnet.
    SubnetIDSet links;
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.4.0")));
    EXPECT_TRUE(links.empty());

    // A 192.0.2.0/26 subnet.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.2.0")));
    SubnetIDSet expected = { 2 };
    EXPECT_EQ(expected, links);

    // Check that any address in the subnet works.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.2.23")));
    EXPECT_EQ(expected, links);

    // Check that an address outside the subnet does not work.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.2.123")));
    EXPECT_TRUE(links.empty());

    // Add a second 192.0.2.0/26 subnet.
    Subnet4Ptr subnet10(new Subnet4(IOAddress("192.0.2.10"),
                                    26, 1, 2, 3, SubnetID(10)));
    ASSERT_NO_THROW(cfg.add(subnet10));

    // Now we should get 2 subnets.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.2.0")));
    expected = { 2, 10 };
    EXPECT_EQ(expected, links);

    // Add a larger subnet.
    Subnet4Ptr subnet20(new Subnet4(IOAddress("192.0.2.20"),
                                    24, 1, 2, 3, SubnetID(20)));
    ASSERT_NO_THROW(cfg.add(subnet20));

    // Now we should get 3 subnets.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.2.0")));
    expected = { 2, 10, 20 };
    EXPECT_EQ(expected, links);

    // But only the larger subnet if the address is only in it.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("192.0.2.123")));
    expected = { 20 };
    EXPECT_EQ(expected, links);

    // Even it is not used for Bulk Leasequery, it works for 0.0.0.0 too.
    links.clear();
    EXPECT_NO_THROW(links = cfg.getLinks(IOAddress("0.0.0.0")));
    expected = { 111 };
    EXPECT_EQ(expected, links);
}

// This test verifies that for each subnet in the configuration it calls
// the initAllocatorAfterConfigure function.
TEST(CfgSubnets4Test, initAllocatorsAfterConfigure) {
    CfgSubnets4 cfg;

    // Create 4 subnets.
    Subnet4Ptr subnet0(new Subnet4(IOAddress("0.0.0.0"),
                                   24, 1, 2, 3, SubnetID(111)));
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.1.0"),
                                   26, 1, 2, 3, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 3, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 1, 2, 3, SubnetID(3)));

    auto allocator0 = boost::make_shared<InitRecordingAllocator>(Lease::TYPE_V4, subnet0);
    subnet0->setAllocator(Lease::TYPE_V4, allocator0);

    auto allocator2 = boost::make_shared<InitRecordingAllocator>(Lease::TYPE_V4, subnet2);
    subnet2->setAllocator(Lease::TYPE_V4, allocator2);

    cfg.add(subnet0);
    cfg.add(subnet1);
    cfg.add(subnet2);
    cfg.add(subnet3);

    EXPECT_EQ(0, allocator0->callcount_);
    EXPECT_EQ(0, allocator2->callcount_);

    cfg.initAllocatorsAfterConfigure();

    EXPECT_EQ(1, allocator0->callcount_);
    EXPECT_EQ(1, allocator2->callcount_);
}

/// @brief Test fixture for parsing v4 Subnets that can verify log output.
class Subnet4ParserTest : public LogContentTest {
public:

    /// @brief virtual destructor
    virtual ~Subnet4ParserTest() = default;
};

// This test verifies that subnet parser for IPv4 works properly
// when using invalid renew and rebind timers.
TEST_F(Subnet4ParserTest, parseWithInvalidRenewRebind) {
    std::string config =
        "{\n"
        "    \"id\": 1,\n"
        "    \"subnet\": \"10.1.2.0/24\",\n"
        "    \"valid-lifetime\": 399,\n"
        "    \"rebind-timer\": 199,\n"
        "    \"renew-timer\": 200\n"
        "}";

    // Basic configuration for subnet4 but with a renew-timer value
    // larger than rebind-timer.
    ElementPtr config_element = Element::fromJSON(config);

    // Parse configuration specified above.
    Subnet4ConfigParser parser(false);
    Subnet4Ptr subnet;

    // Parser should not throw.
    ASSERT_NO_THROW(subnet = parser.parse(config_element));
    ASSERT_TRUE(subnet);

    // Veriy we emitted the proper log message.
    addString("DHCPSRV_CFGMGR_RENEW_GTR_REBIND in subnet-id 1,"
              " the value of renew-timer 200 is greater than the value"
              " of rebind-timer 199, ignoring renew-timer");
    EXPECT_TRUE(checkFile());
}

} // end of anonymous namespace
