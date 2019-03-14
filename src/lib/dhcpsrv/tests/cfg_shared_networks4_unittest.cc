// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <exceptions/exceptions.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <testutils/test_to_element.h>
#include <asiolink/io_address.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace asiolink;

namespace {

void checkMergedNetwork(const CfgSharedNetworks4& networks, const std::string& name,
                       const Triplet<uint32_t>& exp_valid,
                       const std::vector<SubnetID>& exp_subnets) {
    auto network = networks.getByName(name);
    ASSERT_TRUE(network) << "expected network: " << name << " not found";
    ASSERT_EQ(exp_valid, network->getValid()) << " network valid lifetime wrong";
    const Subnet4Collection* subnets = network->getAllSubnets();
    ASSERT_EQ(exp_subnets.size(), subnets->size()) << " wrong number of subnets";
    for (auto exp_id : exp_subnets) {
        ASSERT_TRUE(network->getSubnet(exp_id))
                    << " did not find expected subnet: " << exp_id;
    }
}

// This test verifies that shared networks can be added to the configruation
// and retrieved by name.
TEST(CfgSharedNetworks4Test, getByName) {
    SharedNetwork4Ptr network1(new SharedNetwork4("frog"));
    SharedNetwork4Ptr network2(new SharedNetwork4("dog"));

    CfgSharedNetworks4 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_NO_THROW(cfg.add(network2));

    SharedNetwork4Ptr returned_network1 = cfg.getByName("frog");
    ASSERT_TRUE(returned_network1);
    SharedNetwork4Ptr returned_network2 = cfg.getByName("dog");
    ASSERT_TRUE(returned_network2);

    // Check that non-existent name does not return bogus data.
    EXPECT_FALSE(cfg.getByName("ant"));
}

// This test verifies that it is possible to delete a network.
TEST(CfgSharedNetworks4Test, deleteByName) {
    SharedNetwork4Ptr network1(new SharedNetwork4("frog"));
    SharedNetwork4Ptr network2(new SharedNetwork4("dog"));

    // Add two networks to the configuration.
    CfgSharedNetworks4 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_NO_THROW(cfg.add(network2));

    // Try to delete non-existing network. This should throw.
    ASSERT_THROW(cfg.del("lion"), BadValue);

    // Delete network #1.
    ASSERT_NO_THROW(cfg.del(network1->getName()));
    ASSERT_FALSE(cfg.getByName(network1->getName()));
    ASSERT_TRUE(cfg.getByName(network2->getName()));

    // Delete network #2.
    ASSERT_NO_THROW(cfg.del(network2->getName()));
    ASSERT_FALSE(cfg.getByName(network1->getName()));
    ASSERT_FALSE(cfg.getByName(network2->getName()));

    // Check that attempting to delete the same subnet twice will fail.
    ASSERT_THROW(cfg.del(network1->getName()), BadValue);
    ASSERT_THROW(cfg.del(network2->getName()), BadValue);
}

// Checks that subnets have their shared network pointers updated when
// the network is deleted. This is used when the shared network is deleted
// by admin commands.
TEST(CfgSharedNetworks4Test, deleteNetworkWithSubnets) {
    CfgSharedNetworks4 cfg;
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    SubnetID id1(100);
    SubnetID id2(101);
    Subnet4Ptr sub1(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, id1));
    Subnet4Ptr sub2(new Subnet4(IOAddress("192.0.3.0"), 24, 1, 2, 3, id2));
    network->add(sub1);
    network->add(sub2);
    cfg.add(network);

    // Make sure the subnets are part of the network.
    SharedNetwork4Ptr test;
    sub1->getSharedNetwork(test);
    EXPECT_TRUE(test);
    EXPECT_EQ(network->toElement()->str(), test->toElement()->str());
    sub2->getSharedNetwork(test);
    EXPECT_TRUE(test);
    EXPECT_EQ(network->toElement()->str(), test->toElement()->str());

    // Now remove the network. Subnets should be disassociated with the network.
    cfg.del("frog");
    sub1->getSharedNetwork(test);
    EXPECT_FALSE(test);
    sub2->getSharedNetwork(test);
    EXPECT_FALSE(test);
}

// This test verifies that shared networks must have unique names.
TEST(CfgSharedNetworks4Test, duplicateName) {
    SharedNetwork4Ptr network1(new SharedNetwork4("frog"));
    SharedNetwork4Ptr network2(new SharedNetwork4("frog"));

    CfgSharedNetworks4 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_THROW(cfg.add(network2), BadValue);
}

// This test verifies that unparsing shared networks returns valid structure.
TEST(CfgSharedNetworks4Test, unparse) {
    SharedNetwork4Ptr network1(new SharedNetwork4("frog"));
    SharedNetwork4Ptr network2(new SharedNetwork4("dog"));
    network1->setIface("eth0");
    network1->addRelayAddress(IOAddress("198.16.1.1"));
    network1->addRelayAddress(IOAddress("198.16.1.2"));
    network1->setCalculateTeeTimes(true);
    network1->setT1Percent(.35);
    network1->setT2Percent(.655);

    network2->setIface("eth1");
    network2->setT1(Triplet<uint32_t>(100));
    network2->setT2(Triplet<uint32_t>(200));
    network2->setValid(Triplet<uint32_t>(300));

    CfgSharedNetworks4 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_NO_THROW(cfg.add(network2));

    std::string expected =
        "[\n"
        "  {\n"
        "    \"interface\": \"eth1\",\n"
        "    \"name\": \"dog\",\n"
        "    \"rebind-timer\": 200,\n"
        "    \"option-data\": [ ],\n"
        "    \"renew-timer\": 100,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"subnet4\": [ ],\n"
        "    \"valid-lifetime\": 300\n"
        "  },\n"
        "  {\n"
        "    \"calculate-tee-times\": true,\n"
        "    \"interface\": \"eth0\",\n"
        "    \"name\": \"frog\",\n"
        "    \"option-data\": [ ],\n"
        "    \"relay\": { \"ip-addresses\": [ \"198.16.1.1\", \"198.16.1.2\" ] },\n"
        "    \"subnet4\": [ ],\n"
        "    \"t1-percent\": .35,\n"
        "    \"t2-percent\": .655\n"
        "  }\n"
        "]\n";

    test::runToElementTest<CfgSharedNetworks4>(expected, cfg);
}

// This test verifies that shared-network configurations are properly merged.
TEST(CfgSharedNetworks4Test, mergeNetworks) {
    // Create custom options dictionary for testing merge. We're keeping it
    // simple because they are more rigorous tests elsewhere.
    CfgOptionDefPtr cfg_def(new CfgOptionDef());
    cfg_def->add((OptionDefinitionPtr(new OptionDefinition("one", 1, "string"))), "isc");

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.1.0"),
                                   26, 1, 2, 100, SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"),
                                   26, 1, 2, 100, SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.3.0"),
                                   26, 1, 2, 100, SubnetID(3)));
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.4.0"),
                                   26, 1, 2, 100, SubnetID(4)));

    // Create network1 and add two subnets to it
    SharedNetwork4Ptr network1(new SharedNetwork4("network1"));
    network1->setValid(Triplet<uint32_t>(100));
    ASSERT_NO_THROW(network1->add(subnet1));
    ASSERT_NO_THROW(network1->add(subnet2));

    // Create network2 with no subnets.
    SharedNetwork4Ptr network2(new SharedNetwork4("network2"));
    network2->setValid(Triplet<uint32_t>(200));

    // Create network3 with one subnet.
    SharedNetwork4Ptr network3(new SharedNetwork4("network3"));
    network3->setValid(Triplet<uint32_t>(300));
    ASSERT_NO_THROW(network3->add(subnet3));

    // Create our "existing" configured networks.
    // Add all three networks to the existing config.
    CfgSharedNetworks4 cfg_to;
    ASSERT_NO_THROW(cfg_to.add(network1));
    ASSERT_NO_THROW(cfg_to.add(network2));
    ASSERT_NO_THROW(cfg_to.add(network3));

    // Merge in an "empty" config. Should have the original config, still intact.
    CfgSharedNetworks4 cfg_from;
    ASSERT_NO_THROW(cfg_to.merge(cfg_def, cfg_from));

    ASSERT_EQ(3, cfg_to.getAll()->size());
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network1", Triplet<uint32_t>(100),
                                               std::vector<SubnetID>{SubnetID(1), SubnetID(2)}));
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network2", Triplet<uint32_t>(200),
                                               std::vector<SubnetID>()));

    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network3", Triplet<uint32_t>(300),
                                               std::vector<SubnetID>{SubnetID(3)}));

    // Create network1b, this is an "update" of network1
    // We'll double the valid time and add subnet4 to it
    SharedNetwork4Ptr network1b(new SharedNetwork4("network1"));
    network1b->setValid(Triplet<uint32_t>(200));

    // Now let's a add generic option 1 to network1b.
    std::string value("Yay!");
    OptionPtr option(new Option(Option::V4, 1));
    option->setData(value.begin(), value.end());
    ASSERT_NO_THROW(network1b->getCfgOption()->add(option, false, "isc"));
    // Verify that our option is a generic option.
    EXPECT_EQ("type=001, len=004: 59:61:79:21", option->toText());

    ASSERT_NO_THROW(network1b->add(subnet4));

    // Network2 we will not touch.

    // Create network3b, this is an "update" of network3.
    // We'll double it's valid time, but leave off the subnet.
    SharedNetwork4Ptr network3b(new SharedNetwork4("network3"));
    network3b->setValid(Triplet<uint32_t>(600));

    // Create our "existing" configured networks.
    ASSERT_NO_THROW(cfg_from.add(network1b));
    ASSERT_NO_THROW(cfg_from.add(network3b));

    ASSERT_NO_THROW(cfg_to.merge(cfg_def, cfg_from));

    // Should still have 3 networks.

    // Network1 should have doubled its valid lifetime but still only have
    // the orignal two subnets.  Merge should discard assocations on CB
    // subnets and preserve the associations from existing config.
    ASSERT_EQ(3, cfg_to.getAll()->size());
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network1", Triplet<uint32_t>(200),
                                               std::vector<SubnetID>{SubnetID(1), SubnetID(2)}));

    // Make sure we have option 1 and that it has been replaced with a string option.
    auto network = cfg_to.getByName("network1");
    auto desc = network->getCfgOption()->get("isc", 1);
    ASSERT_TRUE(desc.option_);
    EXPECT_EQ("type=001, len=004: \"Yay!\" (string)", desc.option_->toText());

    // No changes to network2.
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network2", Triplet<uint32_t>(200),
                                               std::vector<SubnetID>()));

    // Network1 should have doubled its valid lifetime and still subnet3.
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network3", Triplet<uint32_t>(600),
                                               std::vector<SubnetID>{SubnetID(3)}));
}

} // end of anonymous namespace
