// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/triplet.h>
#include <exceptions/exceptions.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

// This test verifies that shared network can be given a name and that
// this name can be retrieved.
TEST(SharedNetwork4Test, getName) {
    // Create shared network with an initial name "dog".
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    EXPECT_EQ("frog", network->getName());

    // Override the name.
    network->setName("dog");
    EXPECT_EQ("dog", network->getName());
}

// This test verifies that an IPv4 subnet can be added to a shared network.
// It also verifies that two subnets with the same ID can't be added to
// a shared network and that a single subnet can't be added to two different
// shared subnets.
TEST(SharedNetwork4Test, addSubnet4) {
    // First, create a network.
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));

    // Try to add null pointer. It should throw.
    Subnet4Ptr subnet;
    ASSERT_THROW(network->add(subnet), BadValue);

    // Create a valid subnet. It should now be added successfully.
    subnet.reset(new Subnet4(IOAddress("10.0.0.0"), 8, 10, 20, 30,
                             SubnetID(15)));
    ASSERT_NO_THROW(network->add(subnet));
    ASSERT_EQ(1, network->getAllSubnets()->size());

    // Retrieve the subnet from the network and make sure it is returned
    // as expected.
    Subnet4Ptr returned_subnet = network->getAllSubnets()->front();
    ASSERT_TRUE(returned_subnet);
    EXPECT_EQ(subnet->getID(), returned_subnet->getID());
    SharedNetwork4Ptr network1;
    subnet->getSharedNetwork(network1);
    ASSERT_TRUE(network1);
    EXPECT_TRUE(network1 == network);

    // Create another subnet with the same ID. Adding a network with the
    // same ID should cause an error.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 10, 20, 30,
                                   SubnetID(15)));
    ASSERT_THROW(network->add(subnet), DuplicateSubnetID);

    // Create another network and try to add a subnet to it. It should fail
    // because the subnet is already associated with the first network.
    SharedNetwork4Ptr network2(new SharedNetwork4("dog"));
    ASSERT_THROW(network2->add(subnet), InvalidOperation);
}

// This test verifies that it is possible to remove a specified subnet.
TEST(SharedNetwork4Test, delSubnet4) {
    // Create two subnets and add them to the shared network.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("10.0.0.0"), 8, 10, 20, 30,
                                   SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 10, 20, 30,
                                   SubnetID(2)));

    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    ASSERT_NO_THROW(network->add(subnet1));
    ASSERT_NO_THROW(network->add(subnet2));

    // Make sure they have been added successfully.
    ASSERT_EQ(2, network->getAllSubnets()->size());

    // Try to remove a subnet that doesn't exist in this shared network.
    // It should cause an error.
    ASSERT_THROW(network->del(SubnetID(5)), BadValue);

    // Now delete the subnet that exists.
    ASSERT_NO_THROW(network->del(subnet1->getID()));
    // We should be left with only one subnet.
    ASSERT_EQ(1, network->getAllSubnets()->size());
    Subnet4Ptr subnet_returned = network->getAllSubnets()->front();
    ASSERT_TRUE(subnet_returned);
    EXPECT_EQ(subnet2->getID(), subnet_returned->getID());

    // Check that shared network has been cleared for the removed subnet.
    SharedNetwork4Ptr network1;
    subnet1->getSharedNetwork(network1);
    EXPECT_FALSE(network1);

    // Remove another subnet and make sure there are no subnets left.
    ASSERT_NO_THROW(network->del(subnet2->getID()));
    EXPECT_EQ(0, network->getAllSubnets()->size());

    // The network pointer should be cleared for this second subnet too.
    SharedNetwork4Ptr network2;
    subnet1->getSharedNetwork(network2);
    EXPECT_FALSE(network2);
}

// This test verifies that it is possible to iterate over the subnets
// associated with a particular shared network.
TEST(SharedNetwork4Test, getNextSubnet) {
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));

    // Create three subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("10.0.0.0"), 8, 10, 20, 30,
                                   SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 10, 20, 30,
                                   SubnetID(2)));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("172.16.25.0"), 24, 10, 20, 30,
                                   SubnetID(3)));
    std::vector<Subnet4Ptr> subnets;
    subnets.push_back(subnet1);
    subnets.push_back(subnet2);
    subnets.push_back(subnet3);

    // Subnets have unique IDs so they should successfully be added to the
    // network.
    for (auto i = 0; i < subnets.size(); ++i) {
        ASSERT_NO_THROW(network->add(subnets[i]))
            << "failed to add subnet with id " << subnets[i]->getID()
            << " to shared network";
    }

    // Collect networks associated with our subnets in the vector.
    std::vector<SharedNetwork4Ptr> networks;
    for (auto i = 0; i < subnets.size(); ++i) {
        SharedNetwork4Ptr network;
        subnets[i]->getSharedNetwork(network);
        ASSERT_TRUE(network) << "failed to retrieve shared network for a"
            << " subnet id " << subnets[i]->getID();
        networks.push_back(network);
    }

    // All subnets should be associated with the same network.
    for (auto i = 1; i < networks.size(); ++i) {
        EXPECT_TRUE(networks[0] == networks[i]);
    }

    // Perform the test 3 times where each subnet belonging to the shared
    // network is treated as a "first" subnet in the call to getNextSubnet.
    for (auto i = 0; i < subnets.size(); ++i) {
        Subnet4Ptr s = subnets[i];

        // Iterate over the subnets starting from the subnet with index i.
        for (auto j = 0; j < subnets.size(); ++j) {
            // Get next subnet (following the one currently in s).
            s = networks[0]->getNextSubnet(subnets[i], s->getID());
            // The last iteration should return empty pointer to indicate end of
            // the subnets within shared network. If we're not at last iteration
            // check that the subnet identifier of the returned subnet is valid.
            if (j < subnets.size() - 1) {
                ASSERT_TRUE(s) << "retrieving next subnet failed for pair of"
                    " indexes (i, j) = (" << i << ", " << j << ")";
                const auto expected_subnet_id = (i + j + 1) % subnets.size() + 1;
                EXPECT_EQ(expected_subnet_id, s->getID());
            } else {
                // Null subnet returned for a last iteration.
                ASSERT_FALSE(s) << "expected null pointer to be returned as"
                    " next subnet for pair of indexes (i, j) = ("
                                << i << ", " << j << ")";
            }
        }
    }
}

// This test verifies that unparsing shared network returns valid structure.
TEST(SharedNetwork4Test, unparse) {
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));

    // Set interface name.
    network->setIface("eth1");

    network->setT1(100);
    network->setT2(150);
    network->setValid(200);
    network->setMatchClientId(false);

    // Add several subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("10.0.0.0"), 8, 10, 20, 30,
                                   SubnetID(1)));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 10, 20, 30,
                                   SubnetID(2)));
    network->add(subnet1);
    network->add(subnet2);

    std::string expected = "{\n"
        "    \"interface\": \"eth1\",\n"
        "    \"match-client-id\": false,\n"
        "    \"name\": \"frog\",\n"
        "    \"option-data\": [ ],\n"
        "    \"rebind-timer\": 150,\n"
        "    \"relay\": {\n"
        "        \"ip-address\": \"0.0.0.0\"\n"
        "    },\n"
        "    \"renew-timer\": 100,\n"
        "    \"reservation-mode\": \"all\","
        "    \"subnet4\": [\n"
        "      {\n"
        "        \"4o6-interface\": \"\",\n"
        "        \"4o6-interface-id\": \"\",\n"
        "        \"4o6-subnet\": \"\",\n"
        "        \"id\": 1,\n"
        "        \"match-client-id\": true,\n"
        "        \"next-server\": \"0.0.0.0\",\n"
        "        \"option-data\": [ ],\n"
        "        \"pools\": [ ],\n"
        "        \"rebind-timer\": 20,\n"
        "        \"relay\": {\n"
        "          \"ip-address\": \"0.0.0.0\"\n"
        "        },\n"
        "        \"renew-timer\": 10,\n"
        "        \"reservation-mode\": \"all\",\n"
        "        \"subnet\": \"10.0.0.0/8\",\n"
        "        \"valid-lifetime\": 30\n"
        "      },\n"
        "      {\n"
        "        \"4o6-interface\": \"\",\n"
        "        \"4o6-interface-id\": \"\",\n"
        "        \"4o6-subnet\": \"\",\n"
        "        \"id\": 2,\n"
        "        \"match-client-id\": true,\n"
        "        \"next-server\": \"0.0.0.0\",\n"
        "        \"option-data\": [ ],\n"
        "        \"pools\": [ ],\n"
        "        \"rebind-timer\": 20,\n"
        "        \"relay\": {\n"
        "          \"ip-address\": \"0.0.0.0\"\n"
        "        },\n"
        "        \"renew-timer\": 10,\n"
        "        \"reservation-mode\": \"all\",\n"
        "        \"subnet\": \"192.0.2.0/24\",\n"
        "        \"valid-lifetime\": 30\n"
        "      }\n"
        "    ],\n"
        "    \"valid-lifetime\": 200\n"
        "}\n";

    test::runToElementTest<SharedNetwork4>(expected, *network);
}

// This test verifies that when the shared network object is destroyed,
// the subnets belonging to this shared network will not hold the pointer
// to the destroyed network.
TEST(SharedNetwork4Test, destructSharedNetwork) {
    // Create a network and add a subnet to it.
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    Subnet4Ptr subnet(new Subnet4(IOAddress("10.0.0.0"), 8, 10, 20, 30,
                                  SubnetID(1)));
    ASSERT_NO_THROW(network->add(subnet));

    // Get the pointer to the network from subnet.
    SharedNetwork4Ptr subnet_to_network;
    subnet->getSharedNetwork(subnet_to_network);
    ASSERT_TRUE(subnet_to_network);

    // Reset the pointer to not hold the reference to the shared network.
    subnet_to_network.reset();

    // Destroy the network object.
    network.reset();

    // The reference to the network from the subnet should be lost.
    subnet->getSharedNetwork(subnet_to_network);
    ASSERT_FALSE(subnet_to_network);
}

// This test verifies that shared network can be given a name and that
// this name can be retrieved.
TEST(SharedNetwork6Test, getName) {
    // Create shared network with an initial name "frog".
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    EXPECT_EQ("frog", network->getName());

    // Override the name.
    network->setName("dog");
    EXPECT_EQ("dog", network->getName());
}

// This test verifies that an IPv6 subnet can be added to a shared network.
// It also verifies that two subnets with the same ID can't be added to
// a shared network and that a single subnet can't be added to two different
// shared subnets.
TEST(SharedNetwork6Test, addSubnet6) {
    // First, create a network.
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));

    // Try to add null pointer. It should throw.
    Subnet6Ptr subnet;
    ASSERT_THROW(network->add(subnet), BadValue);

    // Create a valid subnet. It should now be added successfully.
    subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 10, 20, 30, 40,
                             SubnetID(15)));
    ASSERT_NO_THROW(network->add(subnet));
    ASSERT_EQ(1, network->getAllSubnets()->size());

    // Retrieve the subnet from the network and make sure it is returned
    // as expected.
    Subnet6Ptr returned_subnet = network->getAllSubnets()->front();
    ASSERT_TRUE(returned_subnet);
    EXPECT_EQ(subnet->getID(), returned_subnet->getID());
    SharedNetwork6Ptr network1;
    subnet->getSharedNetwork(network1);
    ASSERT_TRUE(network1);
    EXPECT_TRUE(network1 == network);

    // Create another subnet with the same ID. Adding a network with the
    // same ID should cause an error.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 16, 10, 20, 30, 40,
                                   SubnetID(15)));
    ASSERT_THROW(network->add(subnet), DuplicateSubnetID);

    // Create another network and try to add a subnet to it. It should fail
    // because the subnet is already associated with the first network.
    SharedNetwork6Ptr network2(new SharedNetwork6("dog"));
    ASSERT_THROW(network2->add(subnet), InvalidOperation);
}

// This test verifies that it is possible to remove a specified subnet.
TEST(SharedNetwork6Test, delSubnet6) {
    // Create two subnets and add them to the shared network.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 64, 10, 20, 30,
                                   40, SubnetID(1)));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 16, 10, 20, 30, 40,
                                   SubnetID(2)));

    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    ASSERT_NO_THROW(network->add(subnet1));
    ASSERT_NO_THROW(network->add(subnet2));

    // Make sure they have been added successfully.
    ASSERT_EQ(2, network->getAllSubnets()->size());

    // Try to remove a subnet that doesn't exist in this shared network.
    // It should cause an error.
    ASSERT_THROW(network->del(SubnetID(5)), BadValue);

    // Now delete the subnet that exists.
    ASSERT_NO_THROW(network->del(subnet1->getID()));
    // We should be left with only one subnet.
    ASSERT_EQ(1, network->getAllSubnets()->size());
    Subnet6Ptr subnet_returned = network->getAllSubnets()->front();
    ASSERT_TRUE(subnet_returned);
    EXPECT_EQ(subnet2->getID(), subnet_returned->getID());

    // Check that shared network has been cleared for the removed subnet.
    SharedNetwork6Ptr network1;
    subnet1->getSharedNetwork(network1);
    EXPECT_FALSE(network1);

    // Remove another subnet and make sure there are no subnets left.
    ASSERT_NO_THROW(network->del(subnet2->getID()));
    EXPECT_EQ(0, network->getAllSubnets()->size());

    // The network pointer should be cleared for this second subnet too.
    SharedNetwork6Ptr network2;
    subnet1->getSharedNetwork(network2);
    EXPECT_FALSE(network2);
}

// This test verifies that it is possible to iterate over the subnets
// associated with a particular shared network.
TEST(SharedNetwork6Test, getNextSubnet) {
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));

    // Create three subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 64, 10, 20, 30,
                                   40, SubnetID(1)));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 16, 10, 20, 30, 40,
                                   SubnetID(2)));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:2::"), 64, 10, 20, 30,
                                   40, SubnetID(3)));
    std::vector<Subnet6Ptr> subnets;
    subnets.push_back(subnet1);
    subnets.push_back(subnet2);
    subnets.push_back(subnet3);

    // Subnets have unique IDs so they should successfully be added to the
    // network.
    for (auto i = 0; i < subnets.size(); ++i) {
        ASSERT_NO_THROW(network->add(subnets[i]))
            << "failed to add subnet with id " << subnets[i]->getID()
            << " to shared network";
    }

    // Collect networks associated with our subnets in the vector.
    std::vector<SharedNetwork6Ptr> networks;
    for (auto i = 0; i < subnets.size(); ++i) {
        SharedNetwork6Ptr network;
        subnets[i]->getSharedNetwork(network);
        ASSERT_TRUE(network) << "failed to retrieve shared network for a"
            << " subnet id " << subnets[i]->getID();
        networks.push_back(network);
    }

    // All subnets should be associated with the same network.
    for (auto i = 1; i < networks.size(); ++i) {
        EXPECT_TRUE(networks[0] == networks[i]);
    }

    // Perform the test 3 times where each subnet belonging to the shared
    // network is treated as a "first" subnet in the call to getNextSubnet.
    for (auto i = 0; i < subnets.size(); ++i) {
        Subnet6Ptr s = subnets[i];

        // Iterate over the subnets starting from the subnet with index i.
        for (auto j = 0; j < subnets.size(); ++j) {
            // Get next subnet (following the one currently in s).
            s = networks[0]->getNextSubnet(subnets[i], s->getID());
            // The last iteration should return empty pointer to indicate end of
            // the subnets within shared network. If we're not at last iteration
            // check that the subnet identifier of the returned subnet is valid.
            if (j < subnets.size() - 1) {
                ASSERT_TRUE(s) << "retrieving next subnet failed for pair of"
                    " indexes (i, j) = (" << i << ", " << j << ")";
                const auto expected_subnet_id = (i + j + 1) % subnets.size() + 1;
                EXPECT_EQ(expected_subnet_id, s->getID());
            } else {
                // Null subnet returned for a last iteration.
                ASSERT_FALSE(s) << "expected null pointer to be returned as"
                    " next subnet for pair of indexes (i, j) = ("
                                << i << ", " << j << ")";
            }
        }
    }
}

// This test verifies that unparsing shared network returns valid structure.
TEST(SharedNetwork6Test, unparse) {
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    network->setIface("eth1");
    network->setT1(100);
    network->setT2(150);
    network->setPreferred(200);
    network->setValid(300);
    network->setRapidCommit(true);

    // Add several subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 64, 10, 20, 30,
                                   40, SubnetID(1)));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 16, 10, 20, 30, 40,
                                   SubnetID(2)));
    network->add(subnet1);
    network->add(subnet2);

    std::string expected = "{\n"
        "    \"interface\": \"eth1\",\n"
        "    \"name\": \"frog\",\n"
        "    \"option-data\": [ ],\n"
        "    \"preferred-lifetime\": 200,\n"
        "    \"rapid-commit\": true,\n"
        "    \"rebind-timer\": 150,\n"
        "    \"relay\": {\n"
        "        \"ip-address\": \"::\"\n"
        "    },\n"
        "    \"renew-timer\": 100,\n"
        "    \"reservation-mode\": \"all\","
        "    \"subnet6\": [\n"
        "      {\n"
        "        \"id\": 1,\n"
        "        \"option-data\": [ ],\n"
        "        \"pd-pools\": [ ],\n"
        "        \"pools\": [ ],\n"
        "        \"preferred-lifetime\": 30,\n"
        "        \"rapid-commit\": false,\n"
        "        \"rebind-timer\": 20,\n"
        "        \"relay\": {\n"
        "          \"ip-address\": \"::\"\n"
        "        },\n"
        "        \"renew-timer\": 10,\n"
        "        \"reservation-mode\": \"all\",\n"
        "        \"subnet\": \"2001:db8:1::/64\",\n"
        "        \"valid-lifetime\": 40\n"
        "      },\n"
        "      {\n"
        "        \"id\": 2,\n"
        "        \"option-data\": [ ],\n"
        "        \"pd-pools\": [ ],\n"
        "        \"pools\": [ ],\n"
        "        \"preferred-lifetime\": 30,\n"
        "        \"rapid-commit\": false,\n"
        "        \"rebind-timer\": 20,\n"
        "        \"relay\": {\n"
        "          \"ip-address\": \"::\"\n"
        "        },\n"
        "        \"renew-timer\": 10,\n"
        "        \"reservation-mode\": \"all\",\n"
        "        \"subnet\": \"3000::/16\",\n"
        "        \"valid-lifetime\": 40\n"
        "      }\n"
        "    ],\n"
        "    \"valid-lifetime\": 300\n"
        "}\n";

    test::runToElementTest<SharedNetwork6>(expected, *network);
}

// This test verifies that when the shared network object is destroyed,
// the subnets belonging to this shared network will not hold the pointer
// to the destroyed network.
TEST(SharedNetwork6Test, destructSharedNetwork) {
    // Create a network and add a subnet to it.
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 10, 20, 30,
                                  40, SubnetID(1)));
    ASSERT_NO_THROW(network->add(subnet));

    // Get the pointer to the network from subnet.
    SharedNetwork6Ptr subnet_to_network;
    subnet->getSharedNetwork(subnet_to_network);
    ASSERT_TRUE(subnet_to_network);

    // Reset the pointer to not hold the reference to the shared network.
    subnet_to_network.reset();

    // Destroy the network object.
    network.reset();

    // The reference to the network from the subnet should be lost.
    subnet->getSharedNetwork(subnet_to_network);
    ASSERT_FALSE(subnet_to_network);
}


} // end of anonymous namespace
