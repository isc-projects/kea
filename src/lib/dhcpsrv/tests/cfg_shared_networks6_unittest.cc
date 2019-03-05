// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <asiolink/io_address.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace asiolink;

namespace {

// This test verifies that shared networks can be added to the configruation
// and retrieved by name.
TEST(CfgSharedNetworks6Test, getByName) {
    SharedNetwork6Ptr network1(new SharedNetwork6("frog"));
    SharedNetwork6Ptr network2(new SharedNetwork6("dog"));

    CfgSharedNetworks6 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_NO_THROW(cfg.add(network2));

    SharedNetwork6Ptr returned_network1 = cfg.getByName("frog");
    ASSERT_TRUE(returned_network1);
    SharedNetwork6Ptr returned_network2 = cfg.getByName("dog");
    ASSERT_TRUE(returned_network2);

    // Check that non-existent name does not return bogus data.
    EXPECT_FALSE(cfg.getByName("ant"));
}

// This test verifies that it is possible to delete a network.
TEST(CfgSharedNetworks6Test, deleteByName) {
    SharedNetwork6Ptr network1(new SharedNetwork6("frog"));
    SharedNetwork6Ptr network2(new SharedNetwork6("dog"));

    // Add two networks to the configuration.
    CfgSharedNetworks6 cfg;
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
TEST(CfgSharedNetworks6Test, deleteNetworkWithSubnets) {
    CfgSharedNetworks6 cfg;
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    SubnetID id1(100);
    SubnetID id2(101);
    Subnet6Ptr sub1(new Subnet6(IOAddress("2001:db8::"), 48, 1, 2, 3, 4, id1));
    Subnet6Ptr sub2(new Subnet6(IOAddress("fec0::"), 12, 1, 2, 3, 4, id2));
    network->add(sub1);
    network->add(sub2);
    cfg.add(network);

    // Make sure the subnets are part of the network.
    SharedNetwork6Ptr test;
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
TEST(CfgSharedNetworks6Test, duplicateName) {
    SharedNetwork6Ptr network1(new SharedNetwork6("frog"));
    SharedNetwork6Ptr network2(new SharedNetwork6("frog"));

    CfgSharedNetworks6 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_THROW(cfg.add(network2), BadValue);
}

// This test verifies that unparsing shared networks returns valid structure.
TEST(CfgSharedNetworks6Test, unparse) {
    SharedNetwork6Ptr network1(new SharedNetwork6("frog"));
    SharedNetwork6Ptr network2(new SharedNetwork6("dog"));

    network1->setIface("eth0");
    network1->addRelayAddress(IOAddress("2001:db8:1::1"));
    network1->addRelayAddress(IOAddress("2001:db8:1::2"));

    network2->setIface("eth1");
    network2->setT1(Triplet<uint32_t>(100));
    network2->setT2(Triplet<uint32_t>(200));
    network2->setValid(Triplet<uint32_t>(300));

    CfgSharedNetworks6 cfg;
    ASSERT_NO_THROW(cfg.add(network1));
    ASSERT_NO_THROW(cfg.add(network2));

    std::string expected =
        "[\n"
        "  {\n"
        "    \"interface\": \"eth1\",\n"
        "    \"name\": \"dog\",\n"
        "    \"option-data\": [ ],\n"
        "    \"rapid-commit\": false,\n"
        "    \"rebind-timer\": 200,\n"
        "    \"relay\": { \"ip-addresses\": [ ] },\n"
        "    \"renew-timer\": 100,\n"
        "    \"reservation-mode\": \"all\","
        "    \"subnet6\": [ ],\n"
        "    \"valid-lifetime\": 300\n"
        "  },\n"
        "  {\n"
        "    \"interface\": \"eth0\",\n"
        "    \"name\": \"frog\",\n"
        "    \"option-data\": [ ],\n"
        "    \"rapid-commit\": false,\n"
        "    \"relay\": { \"ip-addresses\": [ \"2001:db8:1::1\", \"2001:db8:1::2\" ] },\n"
        "    \"reservation-mode\": \"all\","
        "    \"subnet6\": [ ]\n"
        "  }\n"
        "]\n";

    test::runToElementTest<CfgSharedNetworks6>(expected, cfg);
}

} // end of anonymous namespace
