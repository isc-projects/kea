// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <mysql_cb_dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_space.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <mysql/testutils/mysql_schema.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <map>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv4.
class MySqlConfigBackendDHCPv4Test : public GenericBackendTest {
public:

    /// @brief Constructor.
    MySqlConfigBackendDHCPv4Test()
        : test_subnets_(), test_networks_(), timestamps_() {
        // Recreate database schema.
        destroyMySQLSchema();
        createMySQLSchema();

        try {
            // Create MySQL connection and use it to start the backend.
            DatabaseConnection::ParameterMap params =
                DatabaseConnection::parse(validMySQLConnectionString());
            cbptr_.reset(new MySqlConfigBackendDHCPv4(params));

        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        // Create test data.
        initTestOptions();
        initTestSubnets();
        initTestSharedNetworks();
        initTestOptionDefs();
        initTimestamps();
    }

    /// @brief Destructor.
    virtual ~MySqlConfigBackendDHCPv4Test() {
        cbptr_.reset();
        destroyMySQLSchema();
    }

    /// @brief Creates several subnets used in tests.
    void initTestSubnets() {
        // First subnet includes all parameters.
        std::string interface_id_text = "whale";
        OptionBuffer interface_id(interface_id_text.begin(), interface_id_text.end());
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1024));
        subnet->get4o6().setIface4o6("eth0");
        subnet->get4o6().setInterfaceId(OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID,
                                                         interface_id)));
        subnet->get4o6().setSubnet4o6(IOAddress("2001:db8:1::"), 64);
        subnet->setFilename("/tmp/filename");
        subnet->allowClientClass("home");
        subnet->setIface("eth1");
        subnet->setMatchClientId(false);
        subnet->setSiaddr(IOAddress("10.1.2.3"));
        subnet->setT2(323212);
        subnet->addRelayAddress(IOAddress("10.2.3.4"));
        subnet->addRelayAddress(IOAddress("10.5.6.7"));
        subnet->setT1(1234);
        subnet->requireClientClass("required-class1");
        subnet->requireClientClass("required-class2");
        subnet->setHostReservationMode(Subnet4::HR_DISABLED);
        subnet->setSname("server-hostname");
        subnet->setContext(user_context);
        subnet->setValid(555555);

        Pool4Ptr pool1(new Pool4(IOAddress("192.0.2.10"), IOAddress("192.0.2.20")));
        subnet->addPool(pool1);

        Pool4Ptr pool2(new Pool4(IOAddress("192.0.2.50"), IOAddress("192.0.2.60")));
        subnet->addPool(pool2);

        // Add several options to the subnet.
        subnet->getCfgOption()->add(test_options_[0]->option_,
                                    test_options_[0]->persistent_,
                                    test_options_[0]->space_name_);

        subnet->getCfgOption()->add(test_options_[1]->option_,
                                    test_options_[1]->persistent_,
                                    test_options_[1]->space_name_);

        subnet->getCfgOption()->add(test_options_[2]->option_,
                                    test_options_[2]->persistent_,
                                    test_options_[2]->space_name_);

        test_subnets_.push_back(subnet);

        // Adding another subnet with the same subnet id to test
        // cases that this second instance can override existing
        // subnet instance.
        subnet.reset(new Subnet4(IOAddress("10.0.0.0"), 8, 20, 30, 40, 1024));

        pool1.reset(new Pool4(IOAddress("10.0.0.10"), IOAddress("10.0.0.20")));
        subnet->addPool(pool1);

        pool1->getCfgOption()->add(test_options_[3]->option_,
                                   test_options_[3]->persistent_,
                                   test_options_[3]->space_name_);

        pool1->getCfgOption()->add(test_options_[4]->option_,
                                   test_options_[4]->persistent_,
                                   test_options_[4]->space_name_);

        pool2.reset(new Pool4(IOAddress("10.0.0.50"), IOAddress("10.0.0.60")));
        subnet->addPool(pool2);

        test_subnets_.push_back(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 20, 30, 40, 2048));
        test_subnets_.push_back(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.4.0"), 24, 30, 40, 60, 4096));
        test_subnets_.push_back(subnet);
    }

    /// @brief Creates several subnets used in tests.
    void initTestSharedNetworks() {
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        SharedNetwork4Ptr shared_network(new SharedNetwork4("level1"));
        shared_network->allowClientClass("foo");
        shared_network->setIface("eth1");
        shared_network->setMatchClientId(false);
        shared_network->setT2(323212);
        shared_network->addRelayAddress(IOAddress("10.2.3.4"));
        shared_network->addRelayAddress(IOAddress("10.5.6.7"));
        shared_network->setT1(1234);
        shared_network->requireClientClass("required-class1");
        shared_network->requireClientClass("required-class2");
        shared_network->setHostReservationMode(Subnet4::HR_DISABLED);
        shared_network->setContext(user_context);
        shared_network->setValid(5555);

        // Add several options to the shared network.
        shared_network->getCfgOption()->add(test_options_[2]->option_,
                                            test_options_[2]->persistent_,
                                            test_options_[2]->space_name_);

        shared_network->getCfgOption()->add(test_options_[3]->option_,
                                            test_options_[3]->persistent_,
                                            test_options_[3]->space_name_);

        shared_network->getCfgOption()->add(test_options_[4]->option_,
                                            test_options_[4]->persistent_,
                                            test_options_[4]->space_name_);

        test_networks_.push_back(shared_network);

        // Adding another shared network called "level1" to test
        // cases that this second instance can override existing
        // "level1" instance.
        shared_network.reset(new SharedNetwork4("level1"));
        test_networks_.push_back(shared_network);

        // Add more shared networks.
        shared_network.reset(new SharedNetwork4("level2"));
        test_networks_.push_back(shared_network);

        shared_network.reset(new SharedNetwork4("level3"));
        test_networks_.push_back(shared_network);
    }

    /// @brief Creates several option definitions used in tests.
    void initTestOptionDefs() {
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        OptionDefinitionPtr option_def(new OptionDefinition("foo", 234, "string",
                                                            "espace"));
        option_def->setOptionSpaceName("dhcp4");
        test_option_defs_.push_back(option_def);

        option_def.reset(new OptionDefinition("bar", 234, "uint32", true));
        option_def->setOptionSpaceName("dhcp4");
        test_option_defs_.push_back(option_def);

        option_def.reset(new OptionDefinition("fish", 235, "record", true));
        option_def->setOptionSpaceName("dhcp4");
        option_def->addRecordField("uint32");
        option_def->addRecordField("string");
        test_option_defs_.push_back(option_def);

        option_def.reset(new OptionDefinition("whale", 236, "string"));
        option_def->setOptionSpaceName("xyz");
        test_option_defs_.push_back(option_def);
    }

    /// @brief Creates several DHCP options used in tests.
    void initTestOptions() {
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        OptionDefSpaceContainer defs;

        OptionDescriptor desc =
            createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                       true, false, "my-boot-file");
        desc.space_name_ = DHCP4_OPTION_SPACE;
        desc.setContext(user_context);
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createOption<OptionUint8>(Option::V4, DHO_DEFAULT_IP_TTL,
                                         false, true, 64);
        desc.space_name_ = DHCP4_OPTION_SPACE;
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createOption<OptionUint32>(Option::V4, 1, false, false, 312131),
        desc.space_name_ = "vendor-encapsulated-options";
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createAddressOption<Option4AddrLst>(254, true, true,
                                                   "192.0.2.3");
        desc.space_name_ = DHCP4_OPTION_SPACE;
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createEmptyOption(Option::V4, 1, true);
        desc.space_name_ = "isc";
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createAddressOption<Option4AddrLst>(2, false, true, "10.0.0.5",
                                                   "10.0.0.3", "10.0.3.4");
        desc.space_name_ = "isc";
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        // Add definitions for DHCPv4 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "vendor-encapsulated-1", 1, "uint32")),
                     "vendor-encapsulated-options");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "option-254", 254, "ipv4-address", true)),
                     DHCP4_OPTION_SPACE);
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-1", 1, "empty")), "isc");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-2", 2, "ipv4-address", true)),
                     "isc");

        // Register option definitions.
        LibDHCP::setRuntimeOptionDefs(defs);
    }

    /// @brief Initialize posix time values used in tests.
    void initTimestamps() {
        // Current time minus 1 hour to make sure it is in the past.
        timestamps_["today"] = boost::posix_time::second_clock::universal_time()
            - boost::posix_time::hours(1);
        // Yesterday.
        timestamps_["yesterday"] = timestamps_["today"] - boost::posix_time::hours(24);
        // Tomorrow.
        timestamps_["tomorrow"] = timestamps_["today"] + boost::posix_time::hours(24);
    }

    /// @brief Holds pointers to subnets used in tests.
    std::vector<Subnet4Ptr> test_subnets_;

    /// @brief Holds pointers to shared networks used in tests.
    std::vector<SharedNetwork4Ptr> test_networks_;

    /// @brief Holds pointers to option definitions used in tests.
    std::vector<OptionDefinitionPtr> test_option_defs_;

    /// @brief Holds pointers to options used in tests.
    std::vector<OptionDescriptorPtr> test_options_;

    /// @brief Holds timestamp values used in tests.
    std::map<std::string, boost::posix_time::ptime> timestamps_;

    /// @brief Holds pointer to the backend.
    boost::shared_ptr<ConfigBackendDHCPv4> cbptr_;
};

// This test verifies that the global parameter can be added, updated and
// deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteGlobalParameter4) {
    StampedValuePtr server_tag = StampedValue::create("server-tag", "whale");
    StampedValuePtr original_server_tag = server_tag;

    // Explicitly set modification time to make sure that the time
    // returned from the database is correct.
    server_tag->setModificationTime(timestamps_["yesterday"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         server_tag);

    // Verify returned parameter and the modification time.
    StampedValuePtr returned_server_tag =
        cbptr_->getGlobalParameter4(ServerSelector::UNASSIGNED(), "server-tag");
    ASSERT_TRUE(returned_server_tag);
    EXPECT_EQ("server-tag", returned_server_tag->getName());
    EXPECT_EQ("whale", returned_server_tag->getValue());
    EXPECT_TRUE(returned_server_tag->getModificationTime() ==
                server_tag->getModificationTime());

    // Check that the parameter is not returned when the server tag is not
    // matching.
    returned_server_tag = cbptr_->getGlobalParameter4(ServerSelector::ALL(),
                                                      "server-tag");
    EXPECT_FALSE(returned_server_tag);

    // Check that the parameter is not updated when the server tag is not
    // matching.
    server_tag = StampedValue::create("server-tag", "fish");
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
                                         server_tag);
    returned_server_tag = cbptr_->getGlobalParameter4(ServerSelector::UNASSIGNED()
                                                      , "server-tag");
    ASSERT_TRUE(returned_server_tag);
    EXPECT_EQ("server-tag", returned_server_tag->getName());
    EXPECT_EQ("whale", returned_server_tag->getValue());
    EXPECT_TRUE(returned_server_tag->getModificationTime() ==
                original_server_tag->getModificationTime());

    // Check that the parameter is udpated when it already exists in
    // the database.
    server_tag = StampedValue::create("server-tag", "fish");
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         server_tag);
    returned_server_tag = cbptr_->getGlobalParameter4(ServerSelector::UNASSIGNED(),
                                             "server-tag");
    ASSERT_TRUE(returned_server_tag);
    EXPECT_EQ("server-tag", returned_server_tag->getName());
    EXPECT_EQ("fish", returned_server_tag->getValue());
    EXPECT_TRUE(returned_server_tag->getModificationTime() ==
                server_tag->getModificationTime());

    // Delete parameter and make sure it is gone.
    cbptr_->deleteGlobalParameter4(ServerSelector::UNASSIGNED(), "server-tag");
    returned_server_tag = cbptr_->getGlobalParameter4(ServerSelector::UNASSIGNED(),
                                                      "server-tag");
    EXPECT_FALSE(returned_server_tag);
}

// This test verifies that all global parameters can be retrieved and deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllGlobalParameters4) {
    // Create 3 parameters and put them into the database.
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         StampedValue::create("name1", "value1"));
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         StampedValue::create("name2", 65));
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         StampedValue::create("name3", "value3"));

    // Fetch all parameters.
    auto parameters = cbptr_->getAllGlobalParameters4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(3, parameters.size());

    // Verify their values.
    EXPECT_EQ("value1", parameters[0]->getValue());
    EXPECT_EQ(65, parameters[1]->getSignedIntegerValue());
    EXPECT_EQ("value3", parameters[2]->getValue());

    // Delete all parameters and make sure they are gone.
    cbptr_->deleteAllGlobalParameters4(ServerSelector::UNASSIGNED());
    parameters = cbptr_->getAllGlobalParameters4(ServerSelector::UNASSIGNED());
    EXPECT_TRUE(parameters.empty());
}

// This test verifies that modified global parameters can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedGlobalParameters4) {
    // Create 3 global parameters and assign modification times:
    // "yesterday", "today" and "tomorrow" respectively.
    StampedValuePtr value = StampedValue::create("name1", "value1");
    value->setModificationTime(timestamps_["yesterday"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         value);

    value = StampedValue::create("name2", 65);
    value->setModificationTime(timestamps_["today"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         value);

    value = StampedValue::create("name3", "value3");
    value->setModificationTime(timestamps_["tomorrow"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::UNASSIGNED(),
                                         value);

    // Get parameters modified after "today".
    auto parameters = cbptr_->getModifiedGlobalParameters4(ServerSelector::UNASSIGNED(),
                                                           timestamps_["today"]);

    // It should be the one modified "tomorrow". 
    ASSERT_EQ(1, parameters.size());
    ASSERT_TRUE(parameters[0]);
    EXPECT_EQ("value3", parameters[0]->getValue());
}

// Test that subnet can be inserted, fetched, updated and then fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    test_subnets_[0]->getID());
    ASSERT_TRUE(returned_subnet);

    // The easiest way to verify whether the returned subnet matches the inserted
    // subnet is to convert both to text.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    // Update the subnet in the database (both use the same ID).
    Subnet4Ptr subnet2 = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet2);

    // Fetch updated subnet and see if it matches.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         SubnetID(1024));
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that subnet can be associated with a shared network.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4SharedNetwork) {
    Subnet4Ptr subnet = test_subnets_[0];
    SharedNetwork4Ptr shared_network = test_networks_[0];

    // Add subnet to a shared network.
    shared_network->add(subnet);

    // Store shared network in the database.
    cbptr_->createUpdateSharedNetwork4(ServerSelector::UNASSIGNED(),
                                       shared_network);

    // Store subnet associated with the shared network in the database.
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    test_subnets_[0]->getID());
    ASSERT_TRUE(returned_subnet);

    // The easiest way to verify whether the returned subnet matches the inserted
    // subnet is to convert both to text.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    // However, the check above doesn't verify whether shared network name was
    // correctly returned from the database.
    EXPECT_EQ(shared_network->getName(), returned_subnet->getSharedNetworkName());
}

// Test that subnet can be fetched by prefix.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4ByPrefix) {
    // Insert subnet to the database.
    Subnet4Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Fetch the subnet by prefix.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    "192.0.2.0/24");
    ASSERT_TRUE(returned_subnet);

    // Verify subnet contents.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that all subnets can be fetched and then deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllSubnets4) {
    // Insert test subnets into the database. Note that the second subnet will
    // overwrite the first subnet as they use the same ID.
    for (auto subnet : test_subnets_) {
        cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);
    }

    // Fetch all subnets.
    Subnet4Collection subnets = cbptr_->getAllSubnets4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // See if the subnets are returned ok.
    for (auto i = 0; i < subnets.size(); ++i) {
        EXPECT_EQ(test_subnets_[i + 1]->toElement()->str(),
                  subnets[i]->toElement()->str());
    }

    // Attempt to remove the non existing subnet should  return 0.
    EXPECT_EQ(0, cbptr_->deleteSubnet4(ServerSelector::UNASSIGNED(), 22));
    EXPECT_EQ(0, cbptr_->deleteSubnet4(ServerSelector::UNASSIGNED(),
                                       "155.0.3.0/24"));
    // All subnets should be still there.
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // Delete first subnet by id and verify that it is gone.
    EXPECT_EQ(1, cbptr_->deleteSubnet4(ServerSelector::UNASSIGNED(),
                                       test_subnets_[1]->getID()));
    subnets = cbptr_->getAllSubnets4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_subnets_.size() - 2, subnets.size());

    // Delete second subnet by prefix and verify it is gone.
    EXPECT_EQ(1, cbptr_->deleteSubnet4(ServerSelector::UNASSIGNED(),
                                       test_subnets_[2]->toText()));
    subnets = cbptr_->getAllSubnets4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_subnets_.size() - 3, subnets.size());

    // Delete all.
    EXPECT_EQ(1, cbptr_->deleteAllSubnets4(ServerSelector::UNASSIGNED()));
    subnets = cbptr_->getAllSubnets4(ServerSelector::UNASSIGNED());
    ASSERT_TRUE(subnets.empty());
}

// Test that subnets modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSubnets4) {
    // Explicitly set timestamps of subnets. First subnet has a timestamp
    // pointing to the future. Second subnet has timestamp pointing to the
    // past (yesterday). Third subnet has a timestamp pointing to the
    // past (an hour ago).
    test_subnets_[1]->setModificationTime(timestamps_["tomorrow"]);
    test_subnets_[2]->setModificationTime(timestamps_["yesterday"]);
    test_subnets_[3]->setModificationTime(timestamps_["today"]);

    // Insert subnets into the database.
    for (int i = 1; i < test_subnets_.size(); ++i) {
        cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(),
                                    test_subnets_[i]);
    }

    // Fetch subnets with timestamp later than today. Only one subnet
    // should be returned.
    Subnet4Collection
        subnets = cbptr_->getModifiedSubnets4(ServerSelector::UNASSIGNED(),
                                              timestamps_["today"]);
    ASSERT_EQ(1, subnets.size());

    // Fetch subnets with timestamp later than yesterday. We should get
    // two subnets.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::UNASSIGNED(),
                                          timestamps_["yesterday"]);
    ASSERT_EQ(2, subnets.size());

    // Fetch subnets with timestamp later than tomorrow. Nothing should
    // be returned.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::UNASSIGNED(),
                                          timestamps_["tomorrow"]);
    ASSERT_TRUE(subnets.empty());
}

// Test that shared network can be inserted, fetched, updated and then
// fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetwork4) {
    // Insert new shared network.
    SharedNetwork4Ptr shared_network = test_networks_[0];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::UNASSIGNED(), shared_network);

    // Fetch this shared network by name.
    SharedNetwork4Ptr
        returned_network = cbptr_->getSharedNetwork4(ServerSelector::UNASSIGNED(),
                                                     test_networks_[0]->getName());
    ASSERT_TRUE(returned_network);

    // The easiest way to verify whether the returned shared network matches the
    // inserted shared network is to convert both to text.
    EXPECT_EQ(shared_network->toElement()->str(),
              returned_network->toElement()->str());

    // Update shared network in the database.
    SharedNetwork4Ptr shared_network2 = test_networks_[1];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::UNASSIGNED(), shared_network2);

    // Fetch updated subnet and see if it matches.
    returned_network = cbptr_->getSharedNetwork4(ServerSelector::UNASSIGNED(),
                                                 test_networks_[1]->getName());
    EXPECT_EQ(shared_network2->toElement()->str(),
              returned_network->toElement()->str());
}

// Test that all shared networks can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllSharedNetworks4) {
    // Insert test shared networks into the database. Note that the second shared
    // network will overwrite the first shared network as they use the same name.
    for (auto network : test_networks_) {
        cbptr_->createUpdateSharedNetwork4(ServerSelector::UNASSIGNED(), network);
    }

    // Fetch all shared networks.
    SharedNetwork4Collection networks =
        cbptr_->getAllSharedNetworks4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // See if shared networks are returned ok.
    for (auto i = 0; i < networks.size(); ++i) {
        EXPECT_EQ(test_networks_[i + 1]->toElement()->str(),
                  networks[i]->toElement()->str());
    }

    // Deleting non-existing shared network should return 0.
    EXPECT_EQ(0, cbptr_->deleteSharedNetwork4(ServerSelector::UNASSIGNED(),
                                              "big-fish"));
    // All shared networks should be still there.
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // Delete first shared network and verify it is gone..
    EXPECT_EQ(1, cbptr_->deleteSharedNetwork4(ServerSelector::UNASSIGNED(),
                                              test_networks_[1]->getName()));
    networks = cbptr_->getAllSharedNetworks4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_networks_.size() - 2, networks.size());

    // Delete all.
    EXPECT_EQ(2, cbptr_->deleteAllSharedNetworks4(ServerSelector::UNASSIGNED()));
    networks = cbptr_->getAllSharedNetworks4(ServerSelector::UNASSIGNED());
    ASSERT_TRUE(networks.empty());
}

// Test that shared networks modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSharedNetworks4) {
    // Explicitly set timestamps of shared networks. First shared
    // network has a timestamp pointing to the future. Second shared
    // network has timestamp pointing to the past (yesterday).
    // Third shared network has a timestamp pointing to the
    // past (an hour ago).
    test_networks_[1]->setModificationTime(timestamps_["tomorrow"]);
    test_networks_[2]->setModificationTime(timestamps_["yesterday"]);
    test_networks_[3]->setModificationTime(timestamps_["today"]);

    // Insert shared networks into the database.
    for (int i = 1; i < test_networks_.size(); ++i) {
        cbptr_->createUpdateSharedNetwork4(ServerSelector::UNASSIGNED(),
                                           test_networks_[i]);
    }

    // Fetch shared networks with timestamp later than today. Only one
    // shared network  should be returned.
    SharedNetwork4Collection
        networks = cbptr_->getModifiedSharedNetworks4(ServerSelector::UNASSIGNED(),
                                                      timestamps_["today"]);
    ASSERT_EQ(1, networks.size());

    // Fetch shared networks with timestamp later than yesterday. We
    // should get two shared networks.
    networks = cbptr_->getModifiedSharedNetworks4(ServerSelector::UNASSIGNED(),
                                                 timestamps_["yesterday"]);
    ASSERT_EQ(2, networks.size());

    // Fetch shared networks with timestamp later than tomorrow. Nothing
    // should be returned.
    networks = cbptr_->getModifiedSharedNetworks4(ServerSelector::UNASSIGNED(),
                                                  timestamps_["tomorrow"]);
    ASSERT_TRUE(networks.empty());
}

// Test that option definition can be inserted, fetched, updated and then
// fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getOptionDef4) {
    // Insert new option definition.
    OptionDefinitionPtr option_def = test_option_defs_[0];
    cbptr_->createUpdateOptionDef4(ServerSelector::UNASSIGNED(), option_def);

    // Fetch this option_definition by subnet identifier.
    OptionDefinitionPtr returned_option_def =
        cbptr_->getOptionDef4(ServerSelector::UNASSIGNED(),
                              test_option_defs_[0]->getCode(),
                              test_option_defs_[0]->getOptionSpaceName());
    ASSERT_TRUE(returned_option_def);

    EXPECT_TRUE(returned_option_def->equals(*option_def));

    // Update the option definition in the database.
    OptionDefinitionPtr option_def2 = test_option_defs_[1];
    cbptr_->createUpdateOptionDef4(ServerSelector::UNASSIGNED(), option_def2);

    // Fetch updated option definition and see if it matches.
    returned_option_def = cbptr_->getOptionDef4(ServerSelector::UNASSIGNED(),
                                                test_option_defs_[1]->getCode(),
                                                test_option_defs_[1]->getOptionSpaceName());
    EXPECT_TRUE(returned_option_def->equals(*option_def2));
}

// Test that all option definitions can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllOptionDefs4) {
    // Insert test option definitions into the database. Note that the second
    // option definition will overwrite the first option definition as they use
    // the same code and space.
    for (auto option_def : test_option_defs_) {
        cbptr_->createUpdateOptionDef4(ServerSelector::UNASSIGNED(), option_def);
    }

    // Fetch all option_definitions.
    OptionDefContainer option_defs = cbptr_->getAllOptionDefs4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_option_defs_.size() - 1, option_defs.size());

    // See if option definitions are returned ok.
    for (auto def = option_defs.begin(); def != option_defs.end(); ++def) {
        bool success = false;
        for (auto i = 1; i < test_option_defs_.size(); ++i) {
            if ((*def)->equals(*test_option_defs_[i])) {
                success = true;
            }
        }
        ASSERT_TRUE(success) << "failed for option definition " << (*def)->getCode()
            << ", option space " << (*def)->getOptionSpaceName();
    }

    // Deleting non-existing option definition should return 0.
    EXPECT_EQ(0, cbptr_->deleteOptionDef4(ServerSelector::UNASSIGNED(),
                                          99, "non-exiting-space"));
    // All option definitions should be still there.
    ASSERT_EQ(test_option_defs_.size() - 1, option_defs.size());

    // Delete one of the option definitions and see if it is gone.
    EXPECT_EQ(1, cbptr_->deleteOptionDef4(ServerSelector::UNASSIGNED(),
                                          test_option_defs_[2]->getCode(),
                                          test_option_defs_[2]->getOptionSpaceName()));
    ASSERT_FALSE(cbptr_->getOptionDef4(ServerSelector::UNASSIGNED(),
                                       test_option_defs_[2]->getCode(),
                                       test_option_defs_[2]->getOptionSpaceName()));

    // Delete all remaining option definitions.
    EXPECT_EQ(2, cbptr_->deleteAllOptionDefs4(ServerSelector::UNASSIGNED()));
    option_defs = cbptr_->getAllOptionDefs4(ServerSelector::UNASSIGNED());
    ASSERT_TRUE(option_defs.empty());
}

// Test that option definitions modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedOptionDefs4) {
    // Explicitly set timestamps of option definitions. First option
    // definition has a timestamp pointing to the future. Second option
    // definition has timestamp pointing to the past (yesterday).
    // Third option definitions has a timestamp pointing to the
    // past (an hour ago).
    test_option_defs_[1]->setModificationTime(timestamps_["tomorrow"]);
    test_option_defs_[2]->setModificationTime(timestamps_["yesterday"]);
    test_option_defs_[3]->setModificationTime(timestamps_["today"]);

    // Insert option definitions into the database.
    for (int i = 1; i < test_networks_.size(); ++i) {
        cbptr_->createUpdateOptionDef4(ServerSelector::UNASSIGNED(),
                                       test_option_defs_[i]);
    }

    // Fetch option definitions with timestamp later than today. Only one
    // option definition should be returned.
    OptionDefContainer
        option_defs = cbptr_->getModifiedOptionDefs4(ServerSelector::UNASSIGNED(),
                                                     timestamps_["today"]);
    ASSERT_EQ(1, option_defs.size());

    // Fetch option definitions with timestamp later than yesterday. We
    // should get two option definitions.
    option_defs = cbptr_->getModifiedOptionDefs4(ServerSelector::UNASSIGNED(),
                                                 timestamps_["yesterday"]);
    ASSERT_EQ(2, option_defs.size());

    // Fetch option definitions with timestamp later than tomorrow. Nothing
    // should be returned.
    option_defs = cbptr_->getModifiedOptionDefs4(ServerSelector::UNASSIGNED(),
                                              timestamps_["tomorrow"]);
    ASSERT_TRUE(option_defs.empty());
}

// This test verifies that global option can be added, updated and deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteOption4) {
    // Add option to the database.
    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                opt_boot_file_name);

    // Make sure we can retrieve this option and that it is equal to the
    // option we have inserted into the database.
    OptionDescriptorPtr returned_opt_boot_file_name =
        cbptr_->getOption4(ServerSelector::UNASSIGNED(),
                           opt_boot_file_name->option_->getType(),
                           opt_boot_file_name->space_name_);
    ASSERT_TRUE(returned_opt_boot_file_name);
    EXPECT_TRUE(returned_opt_boot_file_name->equals(*opt_boot_file_name));

    // Modify option and update it in the database.
    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                opt_boot_file_name);

    // Retrieve the option again and make sure that updates were
    // properly propagated to the database.
    returned_opt_boot_file_name = cbptr_->getOption4(ServerSelector::UNASSIGNED(),
                                                     opt_boot_file_name->option_->getType(),
                                                     opt_boot_file_name->space_name_);
    ASSERT_TRUE(returned_opt_boot_file_name);
    EXPECT_TRUE(returned_opt_boot_file_name->equals(*opt_boot_file_name));

    // Delete option from the database and make sure it is gone.
    cbptr_->deleteOption4(ServerSelector::UNASSIGNED(),
                          opt_boot_file_name->option_->getType(),
                          opt_boot_file_name->space_name_);
    EXPECT_FALSE(cbptr_->getOption4(ServerSelector::UNASSIGNED(),
                                    opt_boot_file_name->option_->getType(),
                                    opt_boot_file_name->space_name_));
}

// This test verifies that all global options can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllOptions4) {
    // Add three global options to the database.
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                test_options_[0]);
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                test_options_[1]);
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                test_options_[5]);

    // Retrieve all these options.
    OptionContainer returned_options = cbptr_->getAllOptions4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(3, returned_options.size());

    // Get the container index used to search options by option code.
    const OptionContainerTypeIndex& index = returned_options.get<1>();

    // Verify that all options we put into the database were
    // returned.
    auto option0 = index.find(test_options_[0]->option_->getType());
    ASSERT_FALSE(option0 == index.end());
    EXPECT_TRUE(option0->equals(*test_options_[0]));

    auto option1 = index.find(test_options_[1]->option_->getType());
    ASSERT_FALSE(option1 == index.end());
    EXPECT_TRUE(option1->equals(*test_options_[1]));

    auto option5 = index.find(test_options_[5]->option_->getType());
    ASSERT_FALSE(option5 == index.end());
    EXPECT_TRUE(option5->equals(*test_options_[5]));
}

// This test verifies that modified global options can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedOptions4) {
    // Assign timestamps to the options we're going to store in the
    // database.
    test_options_[0]->setModificationTime(timestamps_["tomorrow"]);
    test_options_[1]->setModificationTime(timestamps_["yesterday"]);
    test_options_[5]->setModificationTime(timestamps_["today"]);

    // Put options into the database.
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                test_options_[0]);
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                test_options_[1]);
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                test_options_[5]);

    // Get options with the timestamp later than today. Only
    // one option should be returned.
    OptionContainer returned_options =
        cbptr_->getModifiedOptions4(ServerSelector::UNASSIGNED(),
                                    timestamps_["today"]);
    ASSERT_EQ(1, returned_options.size());

    // The returned option should be the one with the timestamp
    // set to tomorrow.
    const OptionContainerTypeIndex& index = returned_options.get<1>();
    auto option0 = index.find(test_options_[0]->option_->getType());
    ASSERT_FALSE(option0 == index.end());
    EXPECT_TRUE(option0->equals(*test_options_[0]));
}

// This test verifies that subnet level option can be added, updated and
// deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteSubnetOption4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    subnet->getID());
    ASSERT_TRUE(returned_subnet);

    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(), subnet->getID(),
                                opt_boot_file_name);

    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);

    OptionDescriptor returned_opt_boot_file_name =
        returned_subnet->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(), subnet->getID(),
                                opt_boot_file_name);

    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    returned_opt_boot_file_name =
        returned_subnet->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    cbptr_->deleteOption4(ServerSelector::UNASSIGNED(), subnet->getID(),
                          opt_boot_file_name->option_->getType(),
                          opt_boot_file_name->space_name_);

    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);

    EXPECT_FALSE(returned_subnet->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME).option_);
}

// This test verifies that option can be inserted, updated and deleted
// from the pool.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeletePoolOption4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Add an option into the pool.
    const PoolPtr pool = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.2.10"));
    ASSERT_TRUE(pool);
    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                pool->getFirstAddress(),
                                pool->getLastAddress(),
                                opt_boot_file_name);

    // Query for a subnet.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    subnet->getID());
    ASSERT_TRUE(returned_subnet);

    // The returned subnet should include our pool.
    const PoolPtr returned_pool = returned_subnet->getPool(Lease::TYPE_V4,
                                                           IOAddress("192.0.2.10"));
    ASSERT_TRUE(returned_pool);

    // The pool should contain option we added earlier.
    OptionDescriptor returned_opt_boot_file_name =
        returned_pool->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    // Modify the option and update it in the database.
    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                pool->getFirstAddress(),
                                pool->getLastAddress(),
                                opt_boot_file_name);

    // Fetch the subnet and the corresponding pool.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    const PoolPtr returned_pool1 = returned_subnet->getPool(Lease::TYPE_V4,
                                                            IOAddress("192.0.2.10"));
    ASSERT_TRUE(returned_pool1);

    // Test that the option has been correctly updated in the database.
    returned_opt_boot_file_name =
        returned_pool1->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    // Delete option from the pool.
    cbptr_->deleteOption4(ServerSelector::UNASSIGNED(),
                          pool->getFirstAddress(),
                          pool->getLastAddress(),
                          opt_boot_file_name->option_->getType(),
                          opt_boot_file_name->space_name_);

    // Fetch the subnet and the pool from the database again to make sure
    // that the option is really gone.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    const PoolPtr returned_pool2 = returned_subnet->getPool(Lease::TYPE_V4,
                                                            IOAddress("192.0.2.10"));
    ASSERT_TRUE(returned_pool2);

    // Option should be gone.
    EXPECT_FALSE(returned_pool2->getCfgOption()->get(DHCP4_OPTION_SPACE,
                                                     DHO_BOOT_FILE_NAME).option_);
}

// This test verifies that shared network level option can be added,
// updated and deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteSharedNetworkOption4) {
    // Insert new shared network.
    SharedNetwork4Ptr shared_network = test_networks_[1];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::UNASSIGNED(),
                                       shared_network);

    // Fetch this shared network by name.
    SharedNetwork4Ptr returned_network =
        cbptr_->getSharedNetwork4(ServerSelector::UNASSIGNED(),
                                  shared_network->getName());
    ASSERT_TRUE(returned_network);

    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                shared_network->getName(),
                                opt_boot_file_name);

    returned_network = cbptr_->getSharedNetwork4(ServerSelector::UNASSIGNED(),
                                                shared_network->getName());
    ASSERT_TRUE(returned_network);

    OptionDescriptor returned_opt_boot_file_name =
        returned_network->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::UNASSIGNED(),
                                shared_network->getName(),
                                opt_boot_file_name);

    returned_network = cbptr_->getSharedNetwork4(ServerSelector::UNASSIGNED(),
                                                 shared_network->getName());
    ASSERT_TRUE(returned_network);
    returned_opt_boot_file_name =
        returned_network->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    cbptr_->deleteOption4(ServerSelector::UNASSIGNED(),
                          shared_network->getName(),
                          opt_boot_file_name->option_->getType(),
                          opt_boot_file_name->space_name_);
    returned_network = cbptr_->getSharedNetwork4(ServerSelector::UNASSIGNED(),
                                                 shared_network->getName());
    ASSERT_TRUE(returned_network);
    EXPECT_FALSE(returned_network->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME).option_);
}


}
