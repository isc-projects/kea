// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
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
using namespace isc::util;
using namespace asiolink;

namespace {

/// @brief Attempts to verify an expected network within a collection
/// of networks
///
/// @param networks set of networks in which to look
/// @param name name of the expected network
/// @param exp_valid expected valid lifetime of the network
/// @param exp_subnets list of subnet IDs the network is expected to own
void checkMergedNetwork(const CfgSharedNetworks4& networks, const std::string& name,
                       const Triplet<uint32_t>& exp_valid,
                       const std::vector<SubnetID>& exp_subnets) {
    auto network = networks.getByName(name);
    ASSERT_TRUE(network) << "expected network: " << name << " not found";
    ASSERT_EQ(exp_valid, network->getValid().get()) << " network valid lifetime wrong";
    const Subnet4SimpleCollection* subnets = network->getAllSubnets();
    ASSERT_EQ(exp_subnets.size(), subnets->size()) << " wrong number of subnets";
    for (auto const& exp_id : exp_subnets) {
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

// This test verifies that it is possible to delete a shared network by
// its database identifier.
TEST(CfgSharedNetworks4Test, deleteNetworksById) {
    // Create three shared networks.
    CfgSharedNetworks4 cfg;
    SharedNetwork4Ptr network1(new SharedNetwork4("frog"));
    SharedNetwork4Ptr network2(new SharedNetwork4("whale"));
    SharedNetwork4Ptr network3(new SharedNetwork4("fly"));

    // Add one subnet to each shared network.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.3.0"), 24, 1, 2, 3, 2));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.4.0"), 24, 1, 2, 3, 3));

    network1->add(subnet1);
    network2->add(subnet2);
    network3->add(subnet3);

    // Set unique identifier for the second shared network.
    network2->setId(123);

    // Verify that we have two networks with a default identifier and one
    // with a unique identifier.
    EXPECT_EQ(0, network1->getId());
    EXPECT_EQ(123, network2->getId());
    EXPECT_EQ(0, network3->getId());

    // Add our networks to the configuration.
    cfg.add(network1);
    cfg.add(network2);
    cfg.add(network3);

    // Delete second network by id.
    uint64_t deleted_num = 0;
    ASSERT_NO_THROW(deleted_num = cfg.del(network2->getId()));
    EXPECT_EQ(1, deleted_num);

    // Make sure that the subnet no longer points to the deleted network.
    SharedNetwork4Ptr returned_network;
    subnet2->getSharedNetwork(returned_network);
    EXPECT_FALSE(returned_network);
    EXPECT_FALSE(cfg.getByName("whale"));

    // Delete the remaining two shared network using id of 0.
    ASSERT_NO_THROW(deleted_num = cfg.del(network1->getId()));
    EXPECT_EQ(2, deleted_num);

    // The subnets should no longer point to the deleted networks and
    // the shared networks should no longer exist in the configuration.
    subnet1->getSharedNetwork(returned_network);
    EXPECT_FALSE(returned_network);
    EXPECT_FALSE(cfg.getByName("frog"));

    subnet3->getSharedNetwork(returned_network);
    EXPECT_FALSE(returned_network);
    EXPECT_FALSE(cfg.getByName("fly"));

    EXPECT_EQ(0, cfg.del(network1->getId()));
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
    SharedNetwork4Ptr network3(new SharedNetwork4("cat"));

    network1->setIface("eth0");
    network1->addRelayAddress(IOAddress("198.16.1.1"));
    network1->addRelayAddress(IOAddress("198.16.1.2"));
    network1->setCalculateTeeTimes(true);
    network1->setT1Percent(.35);
    network1->setT2Percent(.655);
    network1->setDdnsSendUpdates(true);
    network1->setDdnsOverrideNoUpdate(true);
    network1->setDdnsOverrideClientUpdate(true);
    network1->setDdnsReplaceClientNameMode(D2ClientConfig::RCM_ALWAYS);
    network1->setDdnsGeneratedPrefix("prefix");
    network1->setDdnsQualifyingSuffix("example.com.");
    network1->setHostnameCharSet("[^A-Z]");
    network1->setHostnameCharReplacement("x");
    network1->setCacheThreshold(.20);
    network1->setOfferLft(77);

    network2->setIface("eth1");
    network2->setT1(Triplet<uint32_t>(100));
    network2->setT2(Triplet<uint32_t>(200));
    network2->setValid(Triplet<uint32_t>(200, 300, 400));
    network2->setDdnsSendUpdates(false);
    network2->setStoreExtendedInfo(true);
    network2->setCacheMaxAge(50);

    network3->setIface("eth2");
    network3->setValid(Triplet<uint32_t>(100));

    CfgSharedNetworks4 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_NO_THROW(cfg.add(network2));
    ASSERT_NO_THROW(cfg.add(network3));

    std::string expected =
        "[\n"
        "  {\n"
        "    \"interface\": \"eth2\",\n"
        "    \"name\": \"cat\",\n"
        "    \"option-data\": [ ],\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"subnet4\": [ ],\n"
        "    \"valid-lifetime\": 100,\n"
        "    \"min-valid-lifetime\": 100,\n"
        "    \"max-valid-lifetime\": 100\n"
        "  },\n"
        "  {\n"
        "    \"ddns-send-updates\": false,\n"
        "    \"interface\": \"eth1\",\n"
        "    \"name\": \"dog\",\n"
        "    \"rebind-timer\": 200,\n"
        "    \"option-data\": [ ],\n"
        "    \"renew-timer\": 100,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"subnet4\": [ ],\n"
        "    \"valid-lifetime\": 300,\n"
        "    \"min-valid-lifetime\": 200,\n"
        "    \"max-valid-lifetime\": 400,\n"
        "    \"store-extended-info\": true,\n"
        "    \"cache-max-age\": 50\n"
        "  },\n"
        "  {\n"
        "    \"calculate-tee-times\": true,\n"
        "    \"ddns-generated-prefix\": \"prefix\",\n"
        "    \"ddns-override-no-update\": true,\n"
        "    \"ddns-override-client-update\": true,\n"
        "    \"ddns-qualifying-suffix\": \"example.com.\",\n"
        "    \"ddns-replace-client-name\": \"always\",\n"
        "    \"ddns-send-updates\": true,\n"
        "    \"interface\": \"eth0\",\n"
        "    \"name\": \"frog\",\n"
        "    \"option-data\": [ ],\n"
        "    \"relay\": { \"ip-addresses\": [ \"198.16.1.1\", \"198.16.1.2\" ] },\n"
        "    \"subnet4\": [ ],\n"
        "    \"t1-percent\": .35,\n"
        "    \"t2-percent\": .655,\n"
        "    \"hostname-char-replacement\": \"x\",\n"
        "    \"hostname-char-set\": \"[^A-Z]\",\n"
        "    \"cache-threshold\": .20,\n"
        "    \"offer-lifetime\": 77\n"
        "  }\n"
        "]\n";

    test::runToElementTest<CfgSharedNetworks4>(expected, cfg);
}

// This test verifies that shared-network configurations are properly merged.
TEST(CfgSharedNetworks4Test, mergeNetworks) {
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
    ASSERT_NO_THROW(network1b->getCfgOption()->add(option, false, false, "isc"));
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
    // the orignal two subnets.  Merge should discard associations on CB
    // subnets and preserve the associations from existing config.
    ASSERT_EQ(3, cfg_to.getAll()->size());
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network1", Triplet<uint32_t>(200),
                                               std::vector<SubnetID>{SubnetID(1), SubnetID(2)}));

    // Make sure we have option 1 and that it has been replaced with a string option.
    auto network = cfg_to.getByName("network1");
    auto desc = network->getCfgOption()->get("isc", 1);
    OptionStringPtr opstr = boost::dynamic_pointer_cast<OptionString>(desc.option_);
    ASSERT_TRUE(opstr);
    EXPECT_EQ("Yay!", opstr->getValue());
    EXPECT_TRUE(network->getCfgOption()->isEncapsulated());

    // No changes to network2.
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network2", Triplet<uint32_t>(200),
                                               std::vector<SubnetID>()));

    // Network1 should have doubled its valid lifetime and still subnet3.
    ASSERT_NO_FATAL_FAILURE(checkMergedNetwork(cfg_to, "network3", Triplet<uint32_t>(600),
                                               std::vector<SubnetID>{SubnetID(3)}));
}

} // end of anonymous namespace
