// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <mysql_cb_dhcp6.h>
#include <database/testutils/schema.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
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

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv6.
///
/// @todo The tests we're providing here only test cases when the
/// server selector is set to 'ALL' (configuration elements belong to
/// all servers). Currently we have no API to insert servers into
/// the database, and therefore we can't test the case when
/// configuration elements are assigned to particular servers by
/// server tags. We will have to expand existing tests when
/// the API is extended allowing for inserting servers to the
/// database.
class MySqlConfigBackendDHCPv6Test : public GenericBackendTest {
public:

    /// @brief Constructor.
    MySqlConfigBackendDHCPv6Test()
        : test_subnets_(), test_networks_(), timestamps_() {
        // Recreate database schema.
        destroyMySQLSchema();
        createMySQLSchema();

        try {
            // Create MySQL connection and use it to start the backend.
            DatabaseConnection::ParameterMap params =
                DatabaseConnection::parse(validMySQLConnectionString());
            cbptr_.reset(new MySqlConfigBackendDHCPv6(params));

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
    virtual ~MySqlConfigBackendDHCPv6Test() {
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

        Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 30, 40, 50, 60, 1024));
        subnet->allowClientClass("home");
        subnet->setIface("eth1");
        subnet->setT2(323212);
        subnet->addRelayAddress(IOAddress("2001:db8:1::2"));
        subnet->addRelayAddress(IOAddress("2001:db8:3::4"));
        subnet->setT1(1234);
        subnet->requireClientClass("required-class1");
        subnet->requireClientClass("required-class2");
        subnet->setHostReservationMode(Subnet4::HR_DISABLED);
        subnet->setContext(user_context);
        subnet->setValid(555555);

        Pool6Ptr pool1(new Pool6(Lease::TYPE_NA,
                                 IOAddress("2001:db8::10"),
                                 IOAddress("2001:db8::20")));
        subnet->addPool(pool1);

        Pool6Ptr pool2(new Pool6(Lease::TYPE_NA,
                                 IOAddress("2001:db8::50"),
                                 IOAddress("2001:db8::60")));
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
        subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 20, 30, 40, 50, 1024));

        pool1.reset(new Pool6(Lease::TYPE_NA,
                              IOAddress("2001:db8:1::10"),
                              IOAddress("2001:db8:1::20")));
        subnet->addPool(pool1);

        pool1->getCfgOption()->add(test_options_[3]->option_,
                                   test_options_[3]->persistent_,
                                   test_options_[3]->space_name_);

        pool1->getCfgOption()->add(test_options_[4]->option_,
                                   test_options_[4]->persistent_,
                                   test_options_[4]->space_name_);

        pool2.reset(new Pool6(Lease::TYPE_NA,
                              IOAddress("2001:db8:1::50"),
                              IOAddress("2001:db8:1::60")));
        subnet->addPool(pool2);

        test_subnets_.push_back(subnet);

        subnet.reset(new Subnet6(IOAddress("2001:db8:3::0"), 64, 20, 30, 40, 50, 2048));
        test_subnets_.push_back(subnet);

        subnet.reset(new Subnet6(IOAddress("2001:db8:4::0"), 64, 30, 40, 60, 4096));
        test_subnets_.push_back(subnet);
    }

    /// @brief Creates several subnets used in tests.
    void initTestSharedNetworks() {
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        SharedNetwork6Ptr shared_network(new SharedNetwork6("level1"));
        shared_network->allowClientClass("foo");
        shared_network->setIface("eth1");
        shared_network->setT2(323212);
        shared_network->addRelayAddress(IOAddress("2001:db8:1::2"));
        shared_network->addRelayAddress(IOAddress("2001:db8:3::4"));
        shared_network->setT1(1234);
        shared_network->requireClientClass("required-class1");
        shared_network->requireClientClass("required-class2");
        shared_network->setHostReservationMode(Subnet6::HR_DISABLED);
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
        shared_network.reset(new SharedNetwork6("level1"));
        test_networks_.push_back(shared_network);

        // Add more shared networks.
        shared_network.reset(new SharedNetwork6("level2"));
        test_networks_.push_back(shared_network);

        shared_network.reset(new SharedNetwork6("level3"));
        test_networks_.push_back(shared_network);
    }

    /// @brief Creates several option definitions used in tests.
    void initTestOptionDefs() {
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        OptionDefinitionPtr option_def(new OptionDefinition("foo", 234, "string",
                                                            "espace"));
        option_def->setOptionSpaceName("dhcp6");
        test_option_defs_.push_back(option_def);

        option_def.reset(new OptionDefinition("bar", 234, "uint32", true));
        option_def->setOptionSpaceName("dhcp6");
        test_option_defs_.push_back(option_def);

        option_def.reset(new OptionDefinition("fish", 235, "record", true));
        option_def->setOptionSpaceName("dhcp6");
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
            createOption<OptionString>(Option::V6, D6O_NEW_POSIX_TIMEZONE,
                                       true, false, "my-timezone");
        desc.space_name_ = DHCP6_OPTION_SPACE;
        desc.setContext(user_context);
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createOption<OptionUint8>(Option::V6, D6O_PREFERENCE,
                                         false, true, 64);
        desc.space_name_ = DHCP6_OPTION_SPACE;
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createOption<OptionUint32>(Option::V6, 1, false, false, 312131),
        desc.space_name_ = "vendor-encapsulated-options";
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createAddressOption<Option6AddrLst>(254, true, true,
                                                   "2001:db8::3");
        desc.space_name_ = DHCP6_OPTION_SPACE;
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createEmptyOption(Option::V6, 1, true);
        desc.space_name_ = "isc";
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        desc = createAddressOption<Option6AddrLst>(2, false, true, "2001:db8:1::5",
                                                   "2001:db8:1::3", "2001:db8:4::4");
        desc.space_name_ = "isc";
        test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

        // Add definitions for DHCPv6 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "vendor-encapsulated-1", 1, "uint32")),
                     "vendor-encapsulated-options");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "option-254", 254, "ipv6-address", true)),
                     DHCP6_OPTION_SPACE);
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-1", 1, "empty")), "isc");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-2", 2, "ipv6-address", true)),
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
    std::vector<Subnet6Ptr> test_subnets_;

    /// @brief Holds pointers to shared networks used in tests.
    std::vector<SharedNetwork6Ptr> test_networks_;

    /// @brief Holds pointers to option definitions used in tests.
    std::vector<OptionDefinitionPtr> test_option_defs_;

    /// @brief Holds pointers to options used in tests.
    std::vector<OptionDescriptorPtr> test_options_;

    /// @brief Holds timestamp values used in tests.
    std::map<std::string, boost::posix_time::ptime> timestamps_;

    /// @brief Holds pointer to the backend.
    boost::shared_ptr<ConfigBackendDHCPv6> cbptr_;
};

// This test verifies that the expected backend type is returned.
TEST_F(MySqlConfigBackendDHCPv6Test, getType) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_.reset(new MySqlConfigBackendDHCPv6(params)));
    EXPECT_EQ("mysql", cbptr_->getType());
}

// This test verifies that by default localhost is returned as MySQL connection
// host.
TEST_F(MySqlConfigBackendDHCPv6Test, getHost) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_.reset(new MySqlConfigBackendDHCPv6(params)));
    EXPECT_EQ("localhost", cbptr_->getHost());
}

// This test verifies that by default port of 0 is returned as MySQL connection
// port.
TEST_F(MySqlConfigBackendDHCPv6Test, getPort) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_.reset(new MySqlConfigBackendDHCPv6(params)));
    EXPECT_EQ(0, cbptr_->getPort());
}

// This test verifies that the global parameter can be added, updated and
// deleted.
TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteGlobalParameter6) {
    StampedValuePtr global_parameter = StampedValue::create("global", "whale");

    // Explicitly set modification time to make sure that the time
    // returned from the database is correct.
    global_parameter->setModificationTime(timestamps_["yesterday"]);
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         global_parameter);

    // Verify returned parameter and the modification time.
    StampedValuePtr returned_global_parameter =
        cbptr_->getGlobalParameter6(ServerSelector::ALL(), "global");
    ASSERT_TRUE(returned_global_parameter);
    EXPECT_EQ("global", returned_global_parameter->getName());
    EXPECT_EQ("whale", returned_global_parameter->getValue());
    EXPECT_TRUE(returned_global_parameter->getModificationTime() ==
                global_parameter->getModificationTime());

    // Because we have added the global parameter for all servers, it
    // should be also returned for the explicitly specified server.
    returned_global_parameter = cbptr_->getGlobalParameter6(ServerSelector::ONE("server1"),
                                                            "global");
    ASSERT_TRUE(returned_global_parameter);
    EXPECT_EQ("global", returned_global_parameter->getName());
    EXPECT_EQ("whale", returned_global_parameter->getValue());
    EXPECT_TRUE(returned_global_parameter->getModificationTime() ==
                global_parameter->getModificationTime());

    // Check that the parameter is udpated when selector is specified correctly.
    global_parameter = StampedValue::create("global", "fish");
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         global_parameter);
    returned_global_parameter = cbptr_->getGlobalParameter6(ServerSelector::ALL(),
                                                            "global");
    ASSERT_TRUE(returned_global_parameter);
    EXPECT_EQ("global", returned_global_parameter->getName());
    EXPECT_EQ("fish", returned_global_parameter->getValue());
    EXPECT_TRUE(returned_global_parameter->getModificationTime() ==
                global_parameter->getModificationTime());

    // Should not delete parameter specified for all servers if explicit
    // server name is provided.
    EXPECT_EQ(0, cbptr_->deleteGlobalParameter6(ServerSelector::ONE("server1"),
                                                "global"));

    // Delete parameter and make sure it is gone.
    cbptr_->deleteGlobalParameter6(ServerSelector::ALL(), "global");
    returned_global_parameter = cbptr_->getGlobalParameter6(ServerSelector::ALL(),
                                                            "global");
    EXPECT_FALSE(returned_global_parameter);
}

// This test verifies that all global parameters can be retrieved and deleted.
TEST_F(MySqlConfigBackendDHCPv6Test, getAllGlobalParameters6) {
    // Create 3 parameters and put them into the database.
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         StampedValue::create("name1", "value1"));
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         StampedValue::create("name2", 65));
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         StampedValue::create("name3", "value3"));

    // Fetch all parameters.
    auto parameters = cbptr_->getAllGlobalParameters6(ServerSelector::ALL());

    // Verify their values.
    std::vector<StampedValuePtr> plist(parameters.begin(), parameters.end());
    ASSERT_EQ(3, plist.size());
    EXPECT_EQ("value1", plist[0]->getValue());
    EXPECT_EQ(65, plist[1]->getSignedIntegerValue());
    EXPECT_EQ("value3", plist[2]->getValue());

    // Should be able to fetct these parameters when explicitly providing
    // the server tag.
    parameters = cbptr_->getAllGlobalParameters6(ServerSelector::ONE("server1"));
    EXPECT_EQ(3, parameters.size());

    // Deleting global parameters with non-matching server selector
    // should fail.
    EXPECT_EQ(0, cbptr_->deleteAllGlobalParameters6(ServerSelector::ONE("server1")));

    // Delete all parameters and make sure they are gone.
    EXPECT_EQ(3, cbptr_->deleteAllGlobalParameters6(ServerSelector::ALL()));
    parameters = cbptr_->getAllGlobalParameters6(ServerSelector::ALL());
    EXPECT_TRUE(parameters.empty());
}

// This test verifies that modified global parameters can be retrieved.
TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedGlobalParameters6) {
    // Create 3 global parameters and assign modification times:
    // "yesterday", "today" and "tomorrow" respectively.
    StampedValuePtr value = StampedValue::create("name1", "value1");
    value->setModificationTime(timestamps_["yesterday"]);
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         value);

    value = StampedValue::create("name2", 65);
    value->setModificationTime(timestamps_["today"]);
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         value);

    value = StampedValue::create("name3", "value3");
    value->setModificationTime(timestamps_["tomorrow"]);
    cbptr_->createUpdateGlobalParameter6(ServerSelector::ALL(),
                                         value);

    // Get parameters modified after "today".
    auto parameters = cbptr_->getModifiedGlobalParameters6(ServerSelector::ALL(),
                                                           timestamps_["today"]);

    // It should be the one modified "tomorrow".
    ASSERT_EQ(1, parameters.size());
    EXPECT_EQ("value3", (*parameters.begin())->getValue());

    // Should be able to fetct these parameters when explicitly providing
    // the server tag.
    parameters = cbptr_->getModifiedGlobalParameters6(ServerSelector::ONE("server1"),
                                                      timestamps_["today"]);
    EXPECT_EQ(1, parameters.size());
}

// Test that subnet can be inserted, fetched, updated and then fetched again.
TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6) {
    // Insert new subnet.
    Subnet6Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet6Ptr returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                                    test_subnets_[0]->getID());
    ASSERT_TRUE(returned_subnet);

    // The easiest way to verify whether the returned subnet matches the inserted
    // subnet is to convert both to text.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    // Update the subnet in the database (both use the same ID).
    Subnet6Ptr subnet2 = test_subnets_[1];
    cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet2);

    // Fetch updated subnet and see if it matches.
    returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                         SubnetID(1024));
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());

    // Fetching the subnet for an explicitly specified server tag should
    // succeeed too.
    returned_subnet = cbptr_->getSubnet6(ServerSelector::ONE("server1"),
                                         SubnetID(1024));
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that subnet can be associated with a shared network.
TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6SharedNetwork) {
    Subnet6Ptr subnet = test_subnets_[0];
    SharedNetwork6Ptr shared_network = test_networks_[0];

    // Add subnet to a shared network.
    shared_network->add(subnet);

    // Store shared network in the database.
    cbptr_->createUpdateSharedNetwork6(ServerSelector::ALL(),
                                       shared_network);

    // Store subnet associated with the shared network in the database.
    cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet6Ptr returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
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
TEST_F(MySqlConfigBackendDHCPv6Test, getSubnet6ByPrefix) {
    // Insert subnet to the database.
    Subnet6Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet);

    // Fetch the subnet by prefix.
    Subnet6Ptr returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                                    "2001:db8::/64");
    ASSERT_TRUE(returned_subnet);

    // Verify subnet contents.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    // Fetching the subnet for an explicitly specified server tag should
    // succeeed too.
    returned_subnet = cbptr_->getSubnet6(ServerSelector::ONE("server1"),
                                         "2001:db8::/64");
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that all subnets can be fetched and then deleted.
TEST_F(MySqlConfigBackendDHCPv6Test, getAllSubnets6) {
    // Insert test subnets into the database. Note that the second subnet will
    // overwrite the first subnet as they use the same ID.
    for (auto subnet : test_subnets_) {
        cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet);
    }

    // Fetch all subnets.
    Subnet6Collection subnets = cbptr_->getAllSubnets6(ServerSelector::ALL());
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // All subnets should also be returned for explicitly specified server tag.
    subnets = cbptr_->getAllSubnets6(ServerSelector::ONE("server1"));
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // See if the subnets are returned ok.
    for (auto i = 0; i < subnets.size(); ++i) {
        EXPECT_EQ(test_subnets_[i + 1]->toElement()->str(),
                  subnets[i]->toElement()->str());
    }

    // Attempt to remove the non existing subnet should  return 0.
    EXPECT_EQ(0, cbptr_->deleteSubnet6(ServerSelector::ALL(), 22));
    EXPECT_EQ(0, cbptr_->deleteSubnet6(ServerSelector::ALL(),
                                       "2001:db8:5::/64"));
    // All subnets should be still there.
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // Should not delete the subnet for explicit server tag because
    // our subnet is for all servers.
    EXPECT_EQ(0, cbptr_->deleteSubnet6(ServerSelector::ONE("server1"),
                                       test_subnets_[1]->getID()));

    // Also, verify that behavior when deleting by prefix.
    EXPECT_EQ(0, cbptr_->deleteSubnet6(ServerSelector::ONE("server1"),
                                       test_subnets_[2]->toText()));

    // Same for all subnets.
    EXPECT_EQ(0, cbptr_->deleteAllSubnets6(ServerSelector::ONE("server1")));

    // Delete first subnet by id and verify that it is gone.
    EXPECT_EQ(1, cbptr_->deleteSubnet6(ServerSelector::ALL(),
                                       test_subnets_[1]->getID()));
    subnets = cbptr_->getAllSubnets6(ServerSelector::ALL());
    ASSERT_EQ(test_subnets_.size() - 2, subnets.size());

    // Delete second subnet by prefix and verify it is gone.
    EXPECT_EQ(1, cbptr_->deleteSubnet6(ServerSelector::ALL(),
                                       test_subnets_[2]->toText()));
    subnets = cbptr_->getAllSubnets6(ServerSelector::ALL());
    ASSERT_EQ(test_subnets_.size() - 3, subnets.size());

    // Delete all.
    EXPECT_EQ(1, cbptr_->deleteAllSubnets6(ServerSelector::ALL()));
    subnets = cbptr_->getAllSubnets6(ServerSelector::ALL());
    ASSERT_TRUE(subnets.empty());
}

// Test that subnets modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedSubnets6) {
    // Explicitly set timestamps of subnets. First subnet has a timestamp
    // pointing to the future. Second subnet has timestamp pointing to the
    // past (yesterday). Third subnet has a timestamp pointing to the
    // past (an hour ago).
    test_subnets_[1]->setModificationTime(timestamps_["tomorrow"]);
    test_subnets_[2]->setModificationTime(timestamps_["yesterday"]);
    test_subnets_[3]->setModificationTime(timestamps_["today"]);

    // Insert subnets into the database.
    for (int i = 1; i < test_subnets_.size(); ++i) {
        cbptr_->createUpdateSubnet6(ServerSelector::ALL(),
                                    test_subnets_[i]);
    }

    // Fetch subnets with timestamp later than today. Only one subnet
    // should be returned.
    Subnet6Collection
        subnets = cbptr_->getModifiedSubnets6(ServerSelector::ALL(),
                                              timestamps_["today"]);
    ASSERT_EQ(1, subnets.size());

    // All subnets should also be returned for explicitly specified server tag.
    subnets = cbptr_->getModifiedSubnets6(ServerSelector::ONE("server1"),
                                          timestamps_["today"]);
    ASSERT_EQ(1, subnets.size());

    // Fetch subnets with timestamp later than yesterday. We should get
    // two subnets.
    subnets = cbptr_->getModifiedSubnets6(ServerSelector::ALL(),
                                          timestamps_["yesterday"]);
    ASSERT_EQ(2, subnets.size());

    // Fetch subnets with timestamp later than tomorrow. Nothing should
    // be returned.
    subnets = cbptr_->getModifiedSubnets6(ServerSelector::ALL(),
                                          timestamps_["tomorrow"]);
    ASSERT_TRUE(subnets.empty());
}

// Test that shared network can be inserted, fetched, updated and then
// fetched again.
TEST_F(MySqlConfigBackendDHCPv6Test, getSharedNetwork6) {
    // Insert new shared network.
    SharedNetwork6Ptr shared_network = test_networks_[0];
    cbptr_->createUpdateSharedNetwork6(ServerSelector::ALL(), shared_network);

    // Fetch this shared network by name.
    SharedNetwork6Ptr
        returned_network = cbptr_->getSharedNetwork6(ServerSelector::ALL(),
                                                     test_networks_[0]->getName());
    ASSERT_TRUE(returned_network);

    // The easiest way to verify whether the returned shared network matches the
    // inserted shared network is to convert both to text.
    EXPECT_EQ(shared_network->toElement()->str(),
              returned_network->toElement()->str());

    // Update shared network in the database.
    SharedNetwork6Ptr shared_network2 = test_networks_[1];
    cbptr_->createUpdateSharedNetwork6(ServerSelector::ALL(), shared_network2);

    // Fetch updated subnet and see if it matches.
    returned_network = cbptr_->getSharedNetwork6(ServerSelector::ALL(),
                                                 test_networks_[1]->getName());
    EXPECT_EQ(shared_network2->toElement()->str(),
              returned_network->toElement()->str());

    // Fetching the shared network for an explicitly specified server tag should
    // succeed too.
    returned_network = cbptr_->getSharedNetwork6(ServerSelector::ONE("server1"),
                                                 shared_network2->getName());
    EXPECT_EQ(shared_network2->toElement()->str(),
              returned_network->toElement()->str());
}

// Test that all shared networks can be fetched.
TEST_F(MySqlConfigBackendDHCPv6Test, getAllSharedNetworks6) {
    // Insert test shared networks into the database. Note that the second shared
    // network will overwrite the first shared network as they use the same name.
    for (auto network : test_networks_) {
        cbptr_->createUpdateSharedNetwork6(ServerSelector::ALL(), network);
    }

    // Fetch all shared networks.
    SharedNetwork6Collection networks =
        cbptr_->getAllSharedNetworks6(ServerSelector::ALL());
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // All shared networks should also be returned for explicitly specified
    // server tag.
    networks = cbptr_->getAllSharedNetworks6(ServerSelector::ONE("server1"));
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // See if shared networks are returned ok.
    for (auto i = 0; i < networks.size(); ++i) {
        EXPECT_EQ(test_networks_[i + 1]->toElement()->str(),
                  networks[i]->toElement()->str());
    }

    // Deleting non-existing shared network should return 0.
    EXPECT_EQ(0, cbptr_->deleteSharedNetwork6(ServerSelector::ALL(),
                                              "big-fish"));
    // All shared networks should be still there.
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // Should not delete the subnet for explicit server tag because
    // our shared network is for all servers.
    EXPECT_EQ(0, cbptr_->deleteSharedNetwork6(ServerSelector::ONE("server1"),
                                              test_networks_[1]->getName()));

    // Same for all shared networks.
    EXPECT_EQ(0, cbptr_->deleteAllSharedNetworks6(ServerSelector::ONE("server1")));

    // Delete first shared network and verify it is gone.
    EXPECT_EQ(1, cbptr_->deleteSharedNetwork6(ServerSelector::ALL(),
                                              test_networks_[1]->getName()));
    networks = cbptr_->getAllSharedNetworks6(ServerSelector::ALL());
    ASSERT_EQ(test_networks_.size() - 2, networks.size());

    // Delete all.
    EXPECT_EQ(2, cbptr_->deleteAllSharedNetworks6(ServerSelector::ALL()));
    networks = cbptr_->getAllSharedNetworks6(ServerSelector::ALL());
    ASSERT_TRUE(networks.empty());
}

// Test that shared networks modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedSharedNetworks6) {
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
        cbptr_->createUpdateSharedNetwork6(ServerSelector::ALL(),
                                           test_networks_[i]);
    }

    // Fetch shared networks with timestamp later than today. Only one
    // shared network  should be returned.
    SharedNetwork6Collection
        networks = cbptr_->getModifiedSharedNetworks6(ServerSelector::ALL(),
                                                      timestamps_["today"]);
    ASSERT_EQ(1, networks.size());

    // Fetch shared networks with timestamp later than yesterday. We
    // should get two shared networks.
    networks = cbptr_->getModifiedSharedNetworks6(ServerSelector::ALL(),
                                                 timestamps_["yesterday"]);
    ASSERT_EQ(2, networks.size());

    // Fetch shared networks with timestamp later than tomorrow. Nothing
    // should be returned.
    networks = cbptr_->getModifiedSharedNetworks6(ServerSelector::ALL(),
                                                  timestamps_["tomorrow"]);
    ASSERT_TRUE(networks.empty());
}

// Test that option definition can be inserted, fetched, updated and then
// fetched again.
TEST_F(MySqlConfigBackendDHCPv6Test, getOptionDef6) {
    // Insert new option definition.
    OptionDefinitionPtr option_def = test_option_defs_[0];
    cbptr_->createUpdateOptionDef6(ServerSelector::ALL(), option_def);

    // Fetch this option_definition by subnet identifier.
    OptionDefinitionPtr returned_option_def =
        cbptr_->getOptionDef6(ServerSelector::ALL(),
                              test_option_defs_[0]->getCode(),
                              test_option_defs_[0]->getOptionSpaceName());
    ASSERT_TRUE(returned_option_def);

    EXPECT_TRUE(returned_option_def->equals(*option_def));

    // Update the option definition in the database.
    OptionDefinitionPtr option_def2 = test_option_defs_[1];
    cbptr_->createUpdateOptionDef6(ServerSelector::ALL(), option_def2);

    // Fetch updated option definition and see if it matches.
    returned_option_def = cbptr_->getOptionDef6(ServerSelector::ALL(),
                                                test_option_defs_[1]->getCode(),
                                                test_option_defs_[1]->getOptionSpaceName());
    EXPECT_TRUE(returned_option_def->equals(*option_def2));

    // Fetching option definition for an explicitly specified server tag
    // should succeed too.
    returned_option_def = cbptr_->getOptionDef6(ServerSelector::ONE("server1"),
                                                test_option_defs_[1]->getCode(),
                                                test_option_defs_[1]->getOptionSpaceName());
    EXPECT_TRUE(returned_option_def->equals(*option_def2));
}

// Test that all option definitions can be fetched.
TEST_F(MySqlConfigBackendDHCPv6Test, getAllOptionDefs6) {
    // Insert test option definitions into the database. Note that the second
    // option definition will overwrite the first option definition as they use
    // the same code and space.
    for (auto option_def : test_option_defs_) {
        cbptr_->createUpdateOptionDef6(ServerSelector::ALL(), option_def);
    }

    // Fetch all option_definitions.
    OptionDefContainer option_defs = cbptr_->getAllOptionDefs6(ServerSelector::ALL());
    ASSERT_EQ(test_option_defs_.size() - 1, option_defs.size());

    // All option definitions should also be returned for explicitly specified
    // server tag.
    option_defs = cbptr_->getAllOptionDefs6(ServerSelector::ONE("server1"));
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
    EXPECT_EQ(0, cbptr_->deleteOptionDef6(ServerSelector::ALL(),
                                          99, "non-exiting-space"));
    // All option definitions should be still there.
    ASSERT_EQ(test_option_defs_.size() - 1, option_defs.size());

    // Should not delete option definition for explicit server tag
    // because our option definition is for all servers.
    EXPECT_EQ(0, cbptr_->deleteOptionDef6(ServerSelector::ONE("server1"),
                                          test_option_defs_[1]->getCode(),
                                          test_option_defs_[1]->getOptionSpaceName()));

    // Same for all option definitions.
    EXPECT_EQ(0, cbptr_->deleteAllOptionDefs6(ServerSelector::ONE("server1")));

    // Delete one of the option definitions and see if it is gone.
    EXPECT_EQ(1, cbptr_->deleteOptionDef6(ServerSelector::ALL(),
                                          test_option_defs_[2]->getCode(),
                                          test_option_defs_[2]->getOptionSpaceName()));
    ASSERT_FALSE(cbptr_->getOptionDef6(ServerSelector::ALL(),
                                       test_option_defs_[2]->getCode(),
                                       test_option_defs_[2]->getOptionSpaceName()));

    // Delete all remaining option definitions.
    EXPECT_EQ(2, cbptr_->deleteAllOptionDefs6(ServerSelector::ALL()));
    option_defs = cbptr_->getAllOptionDefs6(ServerSelector::ALL());
    ASSERT_TRUE(option_defs.empty());
}

// Test that option definitions modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedOptionDefs6) {
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
        cbptr_->createUpdateOptionDef6(ServerSelector::ALL(),
                                       test_option_defs_[i]);
    }

    // Fetch option definitions with timestamp later than today. Only one
    // option definition should be returned.
    OptionDefContainer
        option_defs = cbptr_->getModifiedOptionDefs6(ServerSelector::ALL(),
                                                     timestamps_["today"]);
    ASSERT_EQ(1, option_defs.size());

    // Fetch option definitions with timestamp later than yesterday. We
    // should get two option definitions.
    option_defs = cbptr_->getModifiedOptionDefs6(ServerSelector::ALL(),
                                                 timestamps_["yesterday"]);
    ASSERT_EQ(2, option_defs.size());

    // Fetch option definitions with timestamp later than tomorrow. Nothing
    // should be returned.
    option_defs = cbptr_->getModifiedOptionDefs6(ServerSelector::ALL(),
                                              timestamps_["tomorrow"]);
    ASSERT_TRUE(option_defs.empty());
}

// This test verifies that global option can be added, updated and deleted.
TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteOption6) {
    // Add option to the database.
    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                opt_boot_file_name);

    // Make sure we can retrieve this option and that it is equal to the
    // option we have inserted into the database.
    OptionDescriptorPtr returned_opt_boot_file_name =
        cbptr_->getOption6(ServerSelector::ALL(),
                           opt_boot_file_name->option_->getType(),
                           opt_boot_file_name->space_name_);
    ASSERT_TRUE(returned_opt_boot_file_name);
    EXPECT_TRUE(returned_opt_boot_file_name->equals(*opt_boot_file_name));

    // Modify option and update it in the database.
    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                opt_boot_file_name);

    // Retrieve the option again and make sure that updates were
    // properly propagated to the database.
    returned_opt_boot_file_name = cbptr_->getOption6(ServerSelector::ALL(),
                                                     opt_boot_file_name->option_->getType(),
                                                     opt_boot_file_name->space_name_);
    ASSERT_TRUE(returned_opt_boot_file_name);
    EXPECT_TRUE(returned_opt_boot_file_name->equals(*opt_boot_file_name));

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption6(ServerSelector::ONE("server1"),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Deleting option for all servers should succeed.
    EXPECT_EQ(1, cbptr_->deleteOption6(ServerSelector::ALL(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    EXPECT_FALSE(cbptr_->getOption6(ServerSelector::ALL(),
                                    opt_boot_file_name->option_->getType(),
                                    opt_boot_file_name->space_name_));
}

// This test verifies that all global options can be retrieved.
TEST_F(MySqlConfigBackendDHCPv6Test, getAllOptions6) {
    // Add three global options to the database.
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                test_options_[0]);
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                test_options_[1]);
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                test_options_[5]);

    // Retrieve all these options.
    OptionContainer returned_options = cbptr_->getAllOptions6(ServerSelector::ALL());
    ASSERT_EQ(3, returned_options.size());

    // Fetching global options with explicitly specified server tag should return
    // the same result.
    returned_options = cbptr_->getAllOptions6(ServerSelector::ONE("server1"));
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
TEST_F(MySqlConfigBackendDHCPv6Test, getModifiedOptions6) {
    // Assign timestamps to the options we're going to store in the
    // database.
    test_options_[0]->setModificationTime(timestamps_["tomorrow"]);
    test_options_[1]->setModificationTime(timestamps_["yesterday"]);
    test_options_[5]->setModificationTime(timestamps_["today"]);

    // Put options into the database.
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                test_options_[0]);
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                test_options_[1]);
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                test_options_[5]);

    // Get options with the timestamp later than today. Only
    // one option should be returned.
    OptionContainer returned_options =
        cbptr_->getModifiedOptions6(ServerSelector::ALL(),
                                    timestamps_["today"]);
    ASSERT_EQ(1, returned_options.size());

    // Fetching modified options with explicitly specified server selector
    // should return the same result.
    returned_options = cbptr_->getModifiedOptions6(ServerSelector::ONE("server1"),
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
TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteSubnetOption6) {
    // Insert new subnet.
    Subnet6Ptr subnet = test_subnets_[1];
    cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet6Ptr returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                                    subnet->getID());
    ASSERT_TRUE(returned_subnet);

    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption6(ServerSelector::ALL(), subnet->getID(),
                                opt_boot_file_name);

    returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);

    OptionDescriptor returned_opt_boot_file_name =
        returned_subnet->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption6(ServerSelector::ALL(), subnet->getID(),
                                opt_boot_file_name);

    returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    returned_opt_boot_file_name =
        returned_subnet->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption6(ServerSelector::ONE("server1"),
                                       subnet->getID(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // It should succeed for all servers.
    EXPECT_EQ(1, cbptr_->deleteOption6(ServerSelector::ALL(), subnet->getID(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);

    EXPECT_FALSE(returned_subnet->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE).option_);
}

// This test verifies that option can be inserted, updated and deleted
// from the pool.
TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeletePoolOption6) {
    // Insert new subnet.
    Subnet6Ptr subnet = test_subnets_[1];
    cbptr_->createUpdateSubnet6(ServerSelector::ALL(), subnet);

    // Add an option into the pool.
    const PoolPtr pool = subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8::10"));
    ASSERT_TRUE(pool);
    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                pool->getFirstAddress(),
                                pool->getLastAddress(),
                                opt_boot_file_name);

    // Query for a subnet.
    Subnet6Ptr returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                                    subnet->getID());
    ASSERT_TRUE(returned_subnet);

    // The returned subnet should include our pool.
    const PoolPtr returned_pool = returned_subnet->getPool(Lease::TYPE_NA,
                                                           IOAddress("2001:db8::10"));
    ASSERT_TRUE(returned_pool);

    // The pool should contain option we added earlier.
    OptionDescriptor returned_opt_boot_file_name =
        returned_pool->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    // Modify the option and update it in the database.
    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                pool->getFirstAddress(),
                                pool->getLastAddress(),
                                opt_boot_file_name);

    // Fetch the subnet and the corresponding pool.
    returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    const PoolPtr returned_pool1 = returned_subnet->getPool(Lease::TYPE_NA,
                                                            IOAddress("2001:db8::10"));
    ASSERT_TRUE(returned_pool1);

    // Test that the option has been correctly updated in the database.
    returned_opt_boot_file_name =
        returned_pool1->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption6(ServerSelector::ONE("server1"),
                                       pool->getFirstAddress(),
                                       pool->getLastAddress(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Delete option for all servers should succeed.
    EXPECT_EQ(1, cbptr_->deleteOption6(ServerSelector::ALL(),
                                       pool->getFirstAddress(),
                                       pool->getLastAddress(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Fetch the subnet and the pool from the database again to make sure
    // that the option is really gone.
    returned_subnet = cbptr_->getSubnet6(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    const PoolPtr returned_pool2 = returned_subnet->getPool(Lease::TYPE_NA,
                                                            IOAddress("2001:db8::10"));
    ASSERT_TRUE(returned_pool2);

    // Option should be gone.
    EXPECT_FALSE(returned_pool2->getCfgOption()->get(DHCP6_OPTION_SPACE,
                                                     D6O_NEW_POSIX_TIMEZONE).option_);
}

// This test verifies that shared network level option can be added,
// updated and deleted.
TEST_F(MySqlConfigBackendDHCPv6Test, createUpdateDeleteSharedNetworkOption6) {
    // Insert new shared network.
    SharedNetwork6Ptr shared_network = test_networks_[1];
    cbptr_->createUpdateSharedNetwork6(ServerSelector::ALL(),
                                       shared_network);

    // Fetch this shared network by name.
    SharedNetwork6Ptr returned_network =
        cbptr_->getSharedNetwork6(ServerSelector::ALL(),
                                  shared_network->getName());
    ASSERT_TRUE(returned_network);

    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                shared_network->getName(),
                                opt_boot_file_name);

    returned_network = cbptr_->getSharedNetwork6(ServerSelector::ALL(),
                                                shared_network->getName());
    ASSERT_TRUE(returned_network);

    OptionDescriptor returned_opt_boot_file_name =
        returned_network->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption6(ServerSelector::ALL(),
                                shared_network->getName(),
                                opt_boot_file_name);

    returned_network = cbptr_->getSharedNetwork6(ServerSelector::ALL(),
                                                 shared_network->getName());
    ASSERT_TRUE(returned_network);
    returned_opt_boot_file_name =
        returned_network->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);
    EXPECT_TRUE(returned_opt_boot_file_name.equals(*opt_boot_file_name));

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption6(ServerSelector::ONE("server1"),
                                       shared_network->getName(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Deleting an option for all servers should succeed.
    EXPECT_EQ(1, cbptr_->deleteOption6(ServerSelector::ALL(),
                                       shared_network->getName(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));
    returned_network = cbptr_->getSharedNetwork6(ServerSelector::ALL(),
                                                 shared_network->getName());
    ASSERT_TRUE(returned_network);
    EXPECT_FALSE(returned_network->getCfgOption()->get(DHCP6_OPTION_SPACE, D6O_NEW_POSIX_TIMEZONE).option_);
}


}
