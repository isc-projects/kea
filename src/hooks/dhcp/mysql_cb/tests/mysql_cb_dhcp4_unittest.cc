// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <mysql_cb_dhcp4.h>
#include <database/db_exceptions.h>
#include <database/testutils/schema.h>
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
#include <sstream>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv4.
///
/// @todo The tests we're providing here only test cases when the
/// server selector is set to 'ALL' (configuration elements belong to
/// all servers). Currently we have no API to insert servers into
/// the database, and therefore we can't test the case when
/// configuration elements are assigned to particular servers by
/// server tags. We will have to expand existing tests when
/// the API is extended allowing for inserting servers to the
/// database.
class MySqlConfigBackendDHCPv4Test : public GenericBackendTest {
public:

    /// @brief Constructor.
    MySqlConfigBackendDHCPv4Test()
        : test_subnets_(), test_networks_(), timestamps_(), audit_entries_() {
        // Ensure we have the proper schema with no transient data.
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
        // If data wipe enabled, delete transient data otherwise destroy the schema.
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
        subnet->setAuthoritative(true);
        subnet->setCalculateTeeTimes(true);
        subnet->setT1Percent(0.345);
        subnet->setT2Percent(0.444);

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
        Triplet<uint32_t> null_timer;
        subnet->setT1(null_timer);
        subnet->setT2(null_timer);
        subnet->setValid(null_timer);
        test_subnets_.push_back(subnet);

        // Add a subnet with all defaults.
        subnet.reset(new Subnet4(IOAddress("192.0.4.0"), 24, Triplet<uint32_t>(),
                                 Triplet<uint32_t>(), Triplet<uint32_t>(), 4096));
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
        shared_network->setCalculateTeeTimes(true);
        shared_network->setT1Percent(0.345);
        shared_network->setT2Percent(0.444);
        shared_network->setSiaddr(IOAddress("192.0.1.2"));
        shared_network->setSname("frog");
        shared_network->setFilename("/dev/null");
        shared_network->setAuthoritative(true);

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
        Triplet<uint32_t> null_timer;
        shared_network->setT1(null_timer);
        shared_network->setT2(null_timer);
        shared_network->setValid(null_timer);
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

        // Add definitions for DHCPv4 non-standard options in case we need to
        // compare subnets, networks and pools in JSON format. In that case,
        // the @c toElement functions require option definitions to generate the
        // proper output.
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
        timestamps_["today"] = boost::posix_time::second_clock::local_time()
            - boost::posix_time::hours(1);
        // Yesterday.
        timestamps_["yesterday"] = timestamps_["today"] - boost::posix_time::hours(24);
        // Two days ago.
        timestamps_["two days ago"] = timestamps_["today"] - boost::posix_time::hours(48);
        // Tomorrow.
        timestamps_["tomorrow"] = timestamps_["today"] + boost::posix_time::hours(24);
    }

    /// @brief Logs audit entries in the @c audit_entries_ member.
    ///
    /// This function is called in case of an error.
    std::string logExistingAuditEntries() {
        std::ostringstream s;

        auto& mod_time_idx = audit_entries_.get<AuditEntryModificationTimeTag>();

        for (auto audit_entry_it = mod_time_idx.begin();
             audit_entry_it != mod_time_idx.end();
             ++audit_entry_it) {
            auto audit_entry = *audit_entry_it;
            s << audit_entry->getObjectType() << ", "
              << audit_entry->getObjectId() << ", "
              << static_cast<int>(audit_entry->getModificationType()) << ", "
              << audit_entry->getModificationTime() << ", "
              << audit_entry->getLogMessage()
              << std::endl;
        }

        return (s.str());
    }

    /// @brief Tests that the new audit entry is added.
    ///
    /// This method retrieves a collection of the existing audit entries and
    /// checks that the new one has been added at the end of this collection.
    /// It then verifies the values of the audit entry against the values
    /// specified by the caller.
    ///
    /// @param exp_object_type Expected object type.
    /// @param exp_modification_time Expected modification time.
    /// @param exp_log_message Expected log message.
    /// @param new_entries_num Number of the new entries expected to be inserted.
    void testNewAuditEntry(const std::string& exp_object_type,
                           const AuditEntry::ModificationType& exp_modification_type,
                           const std::string& exp_log_message,
                           const size_t new_entries_num = 1) {
        auto audit_entries_size_save = audit_entries_.size();
        audit_entries_ = cbptr_->getRecentAuditEntries(ServerSelector::ALL(),
                                                       timestamps_["two days ago"]);
        ASSERT_EQ(audit_entries_size_save + new_entries_num, audit_entries_.size())
            << logExistingAuditEntries();

        auto& mod_time_idx = audit_entries_.get<AuditEntryModificationTimeTag>();

        // Iterate over specified number of entries starting from the most recent
        // one and check they have correct values.
        for (auto audit_entry_it = mod_time_idx.rbegin();
             std::distance(mod_time_idx.rbegin(), audit_entry_it) < new_entries_num;
             ++audit_entry_it) {
            auto audit_entry = *audit_entry_it;
            EXPECT_EQ(exp_object_type, audit_entry->getObjectType())
                << logExistingAuditEntries();
            EXPECT_EQ(exp_modification_type, audit_entry->getModificationType())
                << logExistingAuditEntries();
            EXPECT_EQ(exp_log_message, audit_entry->getLogMessage())
                << logExistingAuditEntries();
        }
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

    /// @brief Holds the most recent audit entries.
    AuditEntryCollection audit_entries_;
};

// This test verifies that the expected backend type is returned.
TEST_F(MySqlConfigBackendDHCPv4Test, getType) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_.reset(new MySqlConfigBackendDHCPv4(params)));
    EXPECT_EQ("mysql", cbptr_->getType());
}

// This test verifies that by default localhost is returned as MySQL connection
// host.
TEST_F(MySqlConfigBackendDHCPv4Test, getHost) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_.reset(new MySqlConfigBackendDHCPv4(params)));
    EXPECT_EQ("localhost", cbptr_->getHost());
}

// This test verifies that by default port of 0 is returned as MySQL connection
// port.
TEST_F(MySqlConfigBackendDHCPv4Test, getPort) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_.reset(new MySqlConfigBackendDHCPv4(params)));
    EXPECT_EQ(0, cbptr_->getPort());
}

// This test verifies that the global parameter can be added, updated and
// deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteGlobalParameter4) {
    StampedValuePtr global_parameter = StampedValue::create("global", "whale");

    // Explicitly set modification time to make sure that the time
    // returned from the database is correct.
    global_parameter->setModificationTime(timestamps_["yesterday"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
                                         global_parameter);

    {
        SCOPED_TRACE("CREATE audit entry for global parameter");
        testNewAuditEntry("dhcp4_global_parameter",
                          AuditEntry::ModificationType::CREATE,
                          "global parameter set");
    }

    // Verify returned parameter and the modification time.
    StampedValuePtr returned_global_parameter =
        cbptr_->getGlobalParameter4(ServerSelector::ALL(), "global");
    ASSERT_TRUE(returned_global_parameter);
    EXPECT_EQ("global", returned_global_parameter->getName());
    EXPECT_EQ("whale", returned_global_parameter->getValue());
    EXPECT_TRUE(returned_global_parameter->getModificationTime() ==
                global_parameter->getModificationTime());

    // Because we have added the global parameter for all servers, it
    // should be also returned for the explicitly specified server.
    returned_global_parameter = cbptr_->getGlobalParameter4(ServerSelector::ONE("server1"),
                                                            "global");
    ASSERT_TRUE(returned_global_parameter);
    EXPECT_EQ("global", returned_global_parameter->getName());
    EXPECT_EQ("whale", returned_global_parameter->getValue());
    EXPECT_TRUE(returned_global_parameter->getModificationTime() ==
                global_parameter->getModificationTime());

    // Check that the parameter is udpated when selector is specified correctly.
    global_parameter = StampedValue::create("global", "fish");
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
                                         global_parameter);
    returned_global_parameter = cbptr_->getGlobalParameter4(ServerSelector::ALL(),
                                                            "global");
    ASSERT_TRUE(returned_global_parameter);
    EXPECT_EQ("global", returned_global_parameter->getName());
    EXPECT_EQ("fish", returned_global_parameter->getValue());
    EXPECT_TRUE(returned_global_parameter->getModificationTime() ==
                global_parameter->getModificationTime());

    {
        SCOPED_TRACE("UPDATE audit entry for the global parameter");
        testNewAuditEntry("dhcp4_global_parameter",
                          AuditEntry::ModificationType::UPDATE,
                          "global parameter set");
    }

    // Should not delete parameter specified for all servers if explicit
    // server name is provided.
    EXPECT_EQ(0, cbptr_->deleteGlobalParameter4(ServerSelector::ONE("server1"),
                                                "global"));

    // Delete parameter and make sure it is gone.
    cbptr_->deleteGlobalParameter4(ServerSelector::ALL(), "global");
    returned_global_parameter = cbptr_->getGlobalParameter4(ServerSelector::ALL(),
                                                            "global");
    EXPECT_FALSE(returned_global_parameter);

    {
        SCOPED_TRACE("DELETE audit entry for the global parameter");
        testNewAuditEntry("dhcp4_global_parameter",
                          AuditEntry::ModificationType::DELETE,
                          "global parameter deleted");
    }
}

// This test verifies that all global parameters can be retrieved and deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllGlobalParameters4) {
    // Create 3 parameters and put them into the database.
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
        StampedValue::create("name1", "value1"));
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
        StampedValue::create("name2", Element::create(static_cast<int64_t>(65))));
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
        StampedValue::create("name3", "value3"));
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
        StampedValue::create("name4", Element::create(static_cast<bool>(true))));
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
        StampedValue::create("name5", Element::create(static_cast<double>(1.65))));

    // Fetch all parameters.
    auto parameters = cbptr_->getAllGlobalParameters4(ServerSelector::ALL());
    ASSERT_EQ(5, parameters.size());

    const auto& parameters_index = parameters.get<StampedValueNameIndexTag>();

    // Verify their values.
    EXPECT_EQ("value1", (*parameters_index.find("name1"))->getValue());
    EXPECT_EQ(65, (*parameters_index.find("name2"))->getIntegerValue());
    EXPECT_EQ("value3", (*parameters_index.find("name3"))->getValue());
    EXPECT_TRUE((*parameters_index.find("name4"))->getBoolValue());
    EXPECT_EQ(1.65, (*parameters_index.find("name5"))->getDoubleValue());

    // Should be able to fetch these parameters when explicitly providing
    // the server tag.
    parameters = cbptr_->getAllGlobalParameters4(ServerSelector::ONE("server1"));
    EXPECT_EQ(5, parameters.size());

    // Deleting global parameters with non-matching server selector
    // should fail.
    EXPECT_EQ(0, cbptr_->deleteAllGlobalParameters4(ServerSelector::ONE("server1")));

    // Delete all parameters and make sure they are gone.
    EXPECT_EQ(5, cbptr_->deleteAllGlobalParameters4(ServerSelector::ALL()));
    parameters = cbptr_->getAllGlobalParameters4(ServerSelector::ALL());
    EXPECT_TRUE(parameters.empty());
}

// This test verifies that modified global parameters can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedGlobalParameters4) {
    // Create 3 global parameters and assign modification times:
    // "yesterday", "today" and "tomorrow" respectively.
    StampedValuePtr value = StampedValue::create("name1", "value1");
    value->setModificationTime(timestamps_["yesterday"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
                                         value);

    value = StampedValue::create("name2", Element::create(static_cast<int64_t>(65)));
    value->setModificationTime(timestamps_["today"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
                                         value);

    value = StampedValue::create("name3", "value3");
    value->setModificationTime(timestamps_["tomorrow"]);
    cbptr_->createUpdateGlobalParameter4(ServerSelector::ALL(),
                                         value);

    // Get parameters modified after "today".
    auto parameters = cbptr_->getModifiedGlobalParameters4(ServerSelector::ALL(),
                                                           timestamps_["today"]);

    const auto& parameters_index = parameters.get<StampedValueNameIndexTag>();

    // It should be the one modified "tomorrow".
    ASSERT_EQ(1, parameters_index.size());

    auto parameter = parameters_index.find("name3");
    ASSERT_FALSE(parameter == parameters_index.end());

    ASSERT_TRUE(*parameter);
    EXPECT_EQ("value3", (*parameter)->getValue());

    // Should be able to fetct these parameters when explicitly providing
    // the server tag.
    parameters = cbptr_->getModifiedGlobalParameters4(ServerSelector::ONE("server1"),
                                                      timestamps_["today"]);
    EXPECT_EQ(1, parameters.size());
}

// Test that subnet can be inserted, fetched, updated and then fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                                    test_subnets_[0]->getID());
    ASSERT_TRUE(returned_subnet);

    // The easiest way to verify whether the returned subnet matches the inserted
    // subnet is to convert both to text.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    {
        SCOPED_TRACE("CREATE audit entry for the subnet");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::CREATE,
                          "subnet set");
    }

    // Update the subnet in the database (both use the same ID).
    Subnet4Ptr subnet2 = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet2);

    // Fetch updated subnet and see if it matches.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         SubnetID(1024));
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());

    // Fetching the subnet for an explicitly specified server tag should
    // succeed too.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ONE("server1"),
                                         SubnetID(1024));
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());

    {
        SCOPED_TRACE("UPDATE audit entry for the subnet");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "subnet set");
    }

    // Insert another subnet.
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), test_subnets_[2]);

    // Fetch this subnet by prefix and verify it matches.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         test_subnets_[2]->toText());
    ASSERT_TRUE(returned_subnet);
    EXPECT_EQ(test_subnets_[2]->toElement()->str(), returned_subnet->toElement()->str());

    // Update the subnet in the database (both use the same prefix).
    subnet2.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 30, 40, 60, 8192));
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(),  subnet2);

    // Fetch again and verify.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         test_subnets_[2]->toText());
    ASSERT_TRUE(returned_subnet);
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());

    // Update the subnet when it conflicts same id and same prefix both
    // with different subnets. This should throw.
    // Subnets are 10.0.0.0/8 id 1024 and 192.0.3.0/24 id 8192
    subnet2.reset(new Subnet4(IOAddress("10.0.0.0"), 8, 30, 40, 60, 8192));
    EXPECT_THROW(cbptr_->createUpdateSubnet4(ServerSelector::ALL(),  subnet2),
                 DuplicateEntry);
}

// Test that the information about unspecified optional parameters gets
// propagated to the database.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4WithOptionalUnspecified) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[2];
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                                    subnet->getID());
    ASSERT_TRUE(returned_subnet);

    EXPECT_TRUE(returned_subnet->getIface().unspecified());
    EXPECT_TRUE(returned_subnet->getIface().empty());

    EXPECT_TRUE(returned_subnet->getClientClass().unspecified());
    EXPECT_TRUE(returned_subnet->getClientClass().empty());

    EXPECT_TRUE(returned_subnet->getValid().unspecified());
    EXPECT_EQ(0, returned_subnet->getValid().get());

    EXPECT_TRUE(returned_subnet->getT1().unspecified());
    EXPECT_EQ(0, returned_subnet->getT1().get());

    EXPECT_TRUE(returned_subnet->getT2().unspecified());
    EXPECT_EQ(0, returned_subnet->getT2().get());

    EXPECT_TRUE(returned_subnet->getHostReservationMode().unspecified());
    EXPECT_EQ(Network::HR_ALL, returned_subnet->getHostReservationMode().get());

    EXPECT_TRUE(returned_subnet->getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(returned_subnet->getCalculateTeeTimes().get());

    EXPECT_TRUE(returned_subnet->getT1Percent().unspecified());
    EXPECT_EQ(0.0, returned_subnet->getT1Percent().get());

    EXPECT_TRUE(returned_subnet->getT2Percent().unspecified());
    EXPECT_EQ(0.0, returned_subnet->getT2Percent().get());

    EXPECT_TRUE(returned_subnet->getMatchClientId().unspecified());
    EXPECT_TRUE(returned_subnet->getMatchClientId().get());

    EXPECT_TRUE(returned_subnet->getAuthoritative().unspecified());
    EXPECT_FALSE(returned_subnet->getAuthoritative().get());

    EXPECT_TRUE(returned_subnet->getSiaddr().unspecified());
    EXPECT_TRUE(returned_subnet->getSiaddr().get().isV4Zero());

    EXPECT_TRUE(returned_subnet->getSname().unspecified());
    EXPECT_TRUE(returned_subnet->getSname().empty());

    EXPECT_TRUE(returned_subnet->getFilename().unspecified());
    EXPECT_TRUE(returned_subnet->getFilename().empty());

    EXPECT_FALSE(returned_subnet->get4o6().enabled());

    EXPECT_TRUE(returned_subnet->get4o6().getIface4o6().unspecified());
    EXPECT_TRUE(returned_subnet->get4o6().getIface4o6().empty());

    EXPECT_TRUE(returned_subnet->get4o6().getSubnet4o6().unspecified());
    EXPECT_TRUE(returned_subnet->get4o6().getSubnet4o6().get().first.isV6Zero());
    EXPECT_EQ(128, returned_subnet->get4o6().getSubnet4o6().get().second);

    // The easiest way to verify whether the returned subnet matches the inserted
    // subnet is to convert both to text.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());
}


// Test that subnet can be associated with a shared network.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4SharedNetwork) {
    Subnet4Ptr subnet = test_subnets_[0];
    SharedNetwork4Ptr shared_network = test_networks_[0];

    // Add subnet to a shared network.
    shared_network->add(subnet);

    // Store shared network in the database.
    cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(),
                                       shared_network);

    // Store subnet associated with the shared network in the database.
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
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
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

    // Fetch the subnet by prefix.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                                    "192.0.2.0/24");
    ASSERT_TRUE(returned_subnet);

    // Verify subnet contents.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    // Fetching the subnet for an explicitly specified server tag should
    // succeeed too.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ONE("server1"),
                                         "192.0.2.0/24");
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that all subnets can be fetched and then deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllSubnets4) {
    // Insert test subnets into the database. Note that the second subnet will
    // overwrite the first subnet as they use the same ID.
    for (auto subnet : test_subnets_) {
        cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

        // That subnet overrides the first subnet so the audit entry should
        // indicate an update.
        if (subnet->toText() == "10.0.0.0/8") {
            SCOPED_TRACE("UPDATE audit entry for the subnet " + subnet->toText());
            testNewAuditEntry("dhcp4_subnet",
                              AuditEntry::ModificationType::UPDATE,
                              "subnet set");

        } else {
            SCOPED_TRACE("CREATE audit entry for the subnet " + subnet->toText());
            testNewAuditEntry("dhcp4_subnet",
                              AuditEntry::ModificationType::CREATE,
                              "subnet set");
        }
    }

    // Fetch all subnets.
    Subnet4Collection subnets = cbptr_->getAllSubnets4(ServerSelector::ALL());
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // All subnets should also be returned for explicitly specified server tag.
    subnets = cbptr_->getAllSubnets4(ServerSelector::ONE("server1"));
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // See if the subnets are returned ok.
    for (auto i = 0; i < subnets.size(); ++i) {
        EXPECT_EQ(test_subnets_[i + 1]->toElement()->str(),
                  subnets[i]->toElement()->str());
    }

    // Attempt to remove the non existing subnet should  return 0.
    EXPECT_EQ(0, cbptr_->deleteSubnet4(ServerSelector::ALL(), 22));
    EXPECT_EQ(0, cbptr_->deleteSubnet4(ServerSelector::ALL(),
                                       "155.0.3.0/24"));
    // All subnets should be still there.
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // Should not delete the subnet for explicit server tag because
    // our subnet is for all servers.
    EXPECT_EQ(0, cbptr_->deleteSubnet4(ServerSelector::ONE("server1"),
                                       test_subnets_[1]->getID()));

    // Also, verify that behavior when deleting by prefix.
    EXPECT_EQ(0, cbptr_->deleteSubnet4(ServerSelector::ONE("server1"),
                                       test_subnets_[2]->toText()));

    // Same for all subnets.
    EXPECT_EQ(0, cbptr_->deleteAllSubnets4(ServerSelector::ONE("server1")));

    // Delete first subnet by id and verify that it is gone.
    EXPECT_EQ(1, cbptr_->deleteSubnet4(ServerSelector::ALL(),
                                       test_subnets_[1]->getID()));

    {
        SCOPED_TRACE("DELETE first subnet audit entry");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::DELETE,
                          "subnet deleted");
    }

    subnets = cbptr_->getAllSubnets4(ServerSelector::ALL());
    ASSERT_EQ(test_subnets_.size() - 2, subnets.size());

    // Delete second subnet by prefix and verify it is gone.
    EXPECT_EQ(1, cbptr_->deleteSubnet4(ServerSelector::ALL(),
                                       test_subnets_[2]->toText()));
    subnets = cbptr_->getAllSubnets4(ServerSelector::ALL());
    ASSERT_EQ(test_subnets_.size() - 3, subnets.size());

    {
        SCOPED_TRACE("DELETE second subnet audit entry");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::DELETE,
                          "subnet deleted");
    }

    // Delete all.
    EXPECT_EQ(1, cbptr_->deleteAllSubnets4(ServerSelector::ALL()));
    subnets = cbptr_->getAllSubnets4(ServerSelector::ALL());
    ASSERT_TRUE(subnets.empty());

    {
        SCOPED_TRACE("DELETE all subnets audit entry");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::DELETE,
                          "deleted all subnets");
    }
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
        cbptr_->createUpdateSubnet4(ServerSelector::ALL(),
                                    test_subnets_[i]);
    }

    // Fetch subnets with timestamp later than today. Only one subnet
    // should be returned.
    Subnet4Collection
        subnets = cbptr_->getModifiedSubnets4(ServerSelector::ALL(),
                                              timestamps_["today"]);
    ASSERT_EQ(1, subnets.size());

    // All subnets should also be returned for explicitly specified server tag.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::ONE("server1"),
                                          timestamps_["today"]);
    ASSERT_EQ(1, subnets.size());

    // Fetch subnets with timestamp later than yesterday. We should get
    // two subnets.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::ALL(),
                                          timestamps_["yesterday"]);
    ASSERT_EQ(2, subnets.size());

    // Fetch subnets with timestamp later than tomorrow. Nothing should
    // be returned.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::ALL(),
                                          timestamps_["tomorrow"]);
    ASSERT_TRUE(subnets.empty());
}

// Test that subnets belonging to a shared network can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetworkSubnets4) {
    // Assign test subnets to shared networks level1 and level2.
    test_subnets_[1]->setSharedNetworkName("level1");
    test_subnets_[2]->setSharedNetworkName("level2");
    test_subnets_[3]->setSharedNetworkName("level2");

    // Store shared networks in the database.
    for (auto network : test_networks_) {
        cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(), network);
    }

    // Store subnets in the database.
    for (auto subnet : test_subnets_) {
        cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);
    }

    // Fetch all subnets belonging to shared network level1.
    Subnet4Collection subnets = cbptr_->getSharedNetworkSubnets4(ServerSelector::ALL(),
                                                                 "level1");
    ASSERT_EQ(1, subnets.size());

    // Returned subnet should match test subnet #1.
    EXPECT_TRUE(isEquivalent(test_subnets_[1]->toElement(),
                             subnets[0]->toElement()));

    // All subnets should also be returned for explicitly specified server tag.
    subnets = cbptr_->getSharedNetworkSubnets4(ServerSelector::ONE("server1"), "level1");
    ASSERT_EQ(1, subnets.size());

    // Returned subnet should match test subnet #1.
    EXPECT_TRUE(isEquivalent(test_subnets_[1]->toElement(),
                             subnets[0]->toElement()));

    // Fetch all subnets belonging to shared network level2.
    subnets = cbptr_->getSharedNetworkSubnets4(ServerSelector::ALL(), "level2");
    ASSERT_EQ(2, subnets.size());

    ElementPtr test_list = Element::createList();
    test_list->add(test_subnets_[2]->toElement());
    test_list->add(test_subnets_[3]->toElement());

    ElementPtr returned_list = Element::createList();
    returned_list->add(subnets[0]->toElement());
    returned_list->add(subnets[1]->toElement());

    EXPECT_TRUE(isEquivalent(returned_list, test_list));

    // All subnets should also be returned for explicitly specified server tag.
    subnets = cbptr_->getSharedNetworkSubnets4(ServerSelector::ONE("server1"), "level2");
    ASSERT_EQ(2, subnets.size());

    returned_list = Element::createList();
    returned_list->add(subnets[0]->toElement());
    returned_list->add(subnets[1]->toElement());

    EXPECT_TRUE(isEquivalent(returned_list, test_list));
}

// Test that shared network can be inserted, fetched, updated and then
// fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetwork4) {
    // Insert new shared network.
    SharedNetwork4Ptr shared_network = test_networks_[0];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(), shared_network);

    // Fetch this shared network by name.
    SharedNetwork4Ptr
        returned_network = cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                                     test_networks_[0]->getName());
    ASSERT_TRUE(returned_network);

    // The easiest way to verify whether the returned shared network matches the
    // inserted shared network is to convert both to text.
    EXPECT_EQ(shared_network->toElement()->str(),
              returned_network->toElement()->str());

    {
        SCOPED_TRACE("CREATE audit entry for a shared network");
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::CREATE,
                          "shared network set");
    }

    // Update shared network in the database.
    SharedNetwork4Ptr shared_network2 = test_networks_[1];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(), shared_network2);

    // Fetch updated shared network and see if it matches.
    returned_network = cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                                 test_networks_[1]->getName());
    EXPECT_EQ(shared_network2->toElement()->str(),
              returned_network->toElement()->str());

    {
        SCOPED_TRACE("UPDATE audit entry for a shared network");
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::UPDATE,
                          "shared network set");
    }

    // Fetching the shared network for an explicitly specified server tag should
    // succeed too.
    returned_network = cbptr_->getSharedNetwork4(ServerSelector::ONE("server1"),
                                                 shared_network2->getName());
    EXPECT_EQ(shared_network2->toElement()->str(),
              returned_network->toElement()->str());
}

// Test that the information about unspecified optional parameters gets
// propagated to the database.
TEST_F(MySqlConfigBackendDHCPv4Test, getSharedNetwork4WithOptionalUnspecified) {
    // Insert new shared network.
    SharedNetwork4Ptr shared_network = test_networks_[2];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(), shared_network);

    // Fetch this shared network by name.
    SharedNetwork4Ptr
        returned_network = cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                                     test_networks_[2]->getName());
    ASSERT_TRUE(returned_network);

    EXPECT_TRUE(returned_network->getIface().unspecified());
    EXPECT_TRUE(returned_network->getIface().empty());

    EXPECT_TRUE(returned_network->getClientClass().unspecified());
    EXPECT_TRUE(returned_network->getClientClass().empty());

    EXPECT_TRUE(returned_network->getValid().unspecified());
    EXPECT_EQ(0, returned_network->getValid().get());

    EXPECT_TRUE(returned_network->getT1().unspecified());
    EXPECT_EQ(0, returned_network->getT1().get());

    EXPECT_TRUE(returned_network->getT2().unspecified());
    EXPECT_EQ(0, returned_network->getT2().get());

    EXPECT_TRUE(returned_network->getHostReservationMode().unspecified());
    EXPECT_EQ(Network::HR_ALL, returned_network->getHostReservationMode().get());

    EXPECT_TRUE(returned_network->getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(returned_network->getCalculateTeeTimes().get());

    EXPECT_TRUE(returned_network->getT1Percent().unspecified());
    EXPECT_EQ(0.0, returned_network->getT1Percent().get());

    EXPECT_TRUE(returned_network->getT2Percent().unspecified());
    EXPECT_EQ(0.0, returned_network->getT2Percent().get());

    EXPECT_TRUE(returned_network->getMatchClientId().unspecified());
    EXPECT_TRUE(returned_network->getMatchClientId().get());

    EXPECT_TRUE(returned_network->getAuthoritative().unspecified());
    EXPECT_FALSE(returned_network->getAuthoritative().get());
}

// Test that all shared networks can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllSharedNetworks4) {
    // Insert test shared networks into the database. Note that the second shared
    // network will overwrite the first shared network as they use the same name.
    for (auto network : test_networks_) {
        cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(), network);

        // That shared network overrides the first one so the audit entry should
        // indicate an update.
        if ((network->getName() == "level1") && (!audit_entries_.empty())) {
            SCOPED_TRACE("UPDATE audit entry for the shared network " +
                         network->getName());
            testNewAuditEntry("dhcp4_shared_network",
                              AuditEntry::ModificationType::UPDATE,
                              "shared network set");

        } else {
            SCOPED_TRACE("CREATE audit entry for the shared network " +
                         network->getName());
            testNewAuditEntry("dhcp4_shared_network",
                              AuditEntry::ModificationType::CREATE,
                              "shared network set");
        }
    }

    // Fetch all shared networks.
    SharedNetwork4Collection networks =
        cbptr_->getAllSharedNetworks4(ServerSelector::ALL());
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // All shared networks should also be returned for explicitly specified
    // server tag.
    networks = cbptr_->getAllSharedNetworks4(ServerSelector::ONE("server1"));
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // See if shared networks are returned ok.
    for (auto i = 0; i < networks.size(); ++i) {
        EXPECT_EQ(test_networks_[i + 1]->toElement()->str(),
                  networks[i]->toElement()->str());
    }

    // Add some subnets.
    test_networks_[1]->add(test_subnets_[0]);
    test_subnets_[2]->setSharedNetworkName("level2");
    test_networks_[2]->add(test_subnets_[3]);
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), test_subnets_[0]);
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), test_subnets_[2]);
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), test_subnets_[3]);

    // Both ways to attach a subnet are equivalent.
    Subnet4Ptr subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                           test_subnets_[0]->getID());
    ASSERT_TRUE(subnet);
    EXPECT_EQ("level1", subnet->getSharedNetworkName());

    {
        SCOPED_TRACE("CREATE audit entry for subnets");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::CREATE,
                          "subnet set", 3);
    }

    // Deleting non-existing shared network should return 0.
    EXPECT_EQ(0, cbptr_->deleteSharedNetwork4(ServerSelector::ALL(),
                                              "big-fish"));
    // All shared networks should be still there.
    ASSERT_EQ(test_networks_.size() - 1, networks.size());

    // Should not delete the shared network for explicit server tag
    // because our shared network is for all servers.
    EXPECT_EQ(0, cbptr_->deleteSharedNetwork4(ServerSelector::ONE("server1"),
                                              test_networks_[1]->getName()));

    // Same for all shared networks.
    EXPECT_EQ(0, cbptr_->deleteAllSharedNetworks4(ServerSelector::ONE("server1")));

    // Delete first shared network with it subnets and verify it is gone.

    // Begin by its subnet.
    EXPECT_EQ(1, cbptr_->deleteSharedNetworkSubnets4(ServerSelector::ALL(),
                                                     test_networks_[1]->getName()));

    {
        SCOPED_TRACE("DELETE audit entry for subnets of the first shared network");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::DELETE,
                          "deleted all subnets for a shared network");
    }

    // Check that the subnet is gone..
    subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                test_subnets_[0]->getID());
    EXPECT_FALSE(subnet);

    // And after the shared network itself.
    EXPECT_EQ(1, cbptr_->deleteSharedNetwork4(ServerSelector::ALL(),
                                              test_networks_[1]->getName()));
    networks = cbptr_->getAllSharedNetworks4(ServerSelector::ALL());
    ASSERT_EQ(test_networks_.size() - 2, networks.size());

    {
        SCOPED_TRACE("DELETE audit entry for the first shared network");
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::DELETE,
                          "shared network deleted");
    }

    // Delete all.
    EXPECT_EQ(2, cbptr_->deleteAllSharedNetworks4(ServerSelector::ALL()));
    networks = cbptr_->getAllSharedNetworks4(ServerSelector::ALL());
    ASSERT_TRUE(networks.empty());

    {
        SCOPED_TRACE("DELETE audit entry for the remaining two shared networks");
        // The last parameter indicates that we expect two new audit entries.
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::DELETE,
                          "deleted all shared networks", 2);
    }

    // Check that subnets are still there but detached.
    subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                test_subnets_[2]->getID());
    ASSERT_TRUE(subnet);
    EXPECT_TRUE(subnet->getSharedNetworkName().empty());
    subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                test_subnets_[3]->getID());
    ASSERT_TRUE(subnet);
    EXPECT_TRUE(subnet->getSharedNetworkName().empty());
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
        cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(),
                                           test_networks_[i]);
    }

    // Fetch shared networks with timestamp later than today. Only one
    // shared network  should be returned.
    SharedNetwork4Collection
        networks = cbptr_->getModifiedSharedNetworks4(ServerSelector::ALL(),
                                                      timestamps_["today"]);
    ASSERT_EQ(1, networks.size());

    // Fetch shared networks with timestamp later than yesterday. We
    // should get two shared networks.
    networks = cbptr_->getModifiedSharedNetworks4(ServerSelector::ALL(),
                                                 timestamps_["yesterday"]);
    ASSERT_EQ(2, networks.size());

    // Fetch shared networks with timestamp later than tomorrow. Nothing
    // should be returned.
    networks = cbptr_->getModifiedSharedNetworks4(ServerSelector::ALL(),
                                                  timestamps_["tomorrow"]);
    ASSERT_TRUE(networks.empty());
}

// Test that option definition can be inserted, fetched, updated and then
// fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getOptionDef4) {
    // Insert new option definition.
    OptionDefinitionPtr option_def = test_option_defs_[0];
    cbptr_->createUpdateOptionDef4(ServerSelector::ALL(), option_def);

    // Fetch this option_definition by subnet identifier.
    OptionDefinitionPtr returned_option_def =
        cbptr_->getOptionDef4(ServerSelector::ALL(),
                              test_option_defs_[0]->getCode(),
                              test_option_defs_[0]->getOptionSpaceName());
    ASSERT_TRUE(returned_option_def);

    EXPECT_TRUE(returned_option_def->equals(*option_def));

    {
        SCOPED_TRACE("CREATE audit entry for an option definition");
        testNewAuditEntry("dhcp4_option_def",
                          AuditEntry::ModificationType::CREATE,
                          "option definition set");
    }

    // Update the option definition in the database.
    OptionDefinitionPtr option_def2 = test_option_defs_[1];
    cbptr_->createUpdateOptionDef4(ServerSelector::ALL(), option_def2);

    // Fetch updated option definition and see if it matches.
    returned_option_def = cbptr_->getOptionDef4(ServerSelector::ALL(),
                                                test_option_defs_[1]->getCode(),
                                                test_option_defs_[1]->getOptionSpaceName());
    EXPECT_TRUE(returned_option_def->equals(*option_def2));

    // Fetching option definition for an explicitly specified server tag
    // should succeed too.
    returned_option_def = cbptr_->getOptionDef4(ServerSelector::ONE("server1"),
                                                test_option_defs_[1]->getCode(),
                                                test_option_defs_[1]->getOptionSpaceName());
    EXPECT_TRUE(returned_option_def->equals(*option_def2));

    {
        SCOPED_TRACE("UPDATE audit entry for an option definition");
        testNewAuditEntry("dhcp4_option_def",
                          AuditEntry::ModificationType::UPDATE,
                          "option definition set");
    }
}

// Test that all option definitions can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllOptionDefs4) {
    // Insert test option definitions into the database. Note that the second
    // option definition will overwrite the first option definition as they use
    // the same code and space.
    for (auto option_def : test_option_defs_) {
        cbptr_->createUpdateOptionDef4(ServerSelector::ALL(), option_def);

        // That option definition overrides the first one so the audit entry should
        // indicate an update.
        if (option_def->getName() == "bar") {
            SCOPED_TRACE("UPDATE audit entry for the option definition " +
                         option_def->getName());
            testNewAuditEntry("dhcp4_option_def",
                              AuditEntry::ModificationType::UPDATE,
                              "option definition set");

        } else {
            SCOPED_TRACE("CREATE audit entry for the option defnition " +
                         option_def->getName());
            testNewAuditEntry("dhcp4_option_def",
                              AuditEntry::ModificationType::CREATE,
                              "option definition set");
        }
    }

    // Fetch all option_definitions.
    OptionDefContainer option_defs = cbptr_->getAllOptionDefs4(ServerSelector::ALL());
    ASSERT_EQ(test_option_defs_.size() - 1, option_defs.size());

    // All option definitions should also be returned for explicitly specified
    // server tag.
    option_defs = cbptr_->getAllOptionDefs4(ServerSelector::ONE("server1"));
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
    EXPECT_EQ(0, cbptr_->deleteOptionDef4(ServerSelector::ALL(),
                                          99, "non-exiting-space"));
    // All option definitions should be still there.
    ASSERT_EQ(test_option_defs_.size() - 1, option_defs.size());

    // Should not delete option definition for explicit server tag
    // because our option definition is for all servers.
    EXPECT_EQ(0, cbptr_->deleteOptionDef4(ServerSelector::ONE("server1"),
                                          test_option_defs_[1]->getCode(),
                                          test_option_defs_[1]->getOptionSpaceName()));

    // Same for all option definitions.
    EXPECT_EQ(0, cbptr_->deleteAllOptionDefs4(ServerSelector::ONE("server1")));

    // Delete one of the option definitions and see if it is gone.
    EXPECT_EQ(1, cbptr_->deleteOptionDef4(ServerSelector::ALL(),
                                          test_option_defs_[2]->getCode(),
                                          test_option_defs_[2]->getOptionSpaceName()));
    ASSERT_FALSE(cbptr_->getOptionDef4(ServerSelector::ALL(),
                                       test_option_defs_[2]->getCode(),
                                       test_option_defs_[2]->getOptionSpaceName()));

    {
        SCOPED_TRACE("DELETE audit entry for the first option definition");
        testNewAuditEntry("dhcp4_option_def",
                          AuditEntry::ModificationType::DELETE,
                          "option definition deleted");
    }

    // Delete all remaining option definitions.
    EXPECT_EQ(2, cbptr_->deleteAllOptionDefs4(ServerSelector::ALL()));
    option_defs = cbptr_->getAllOptionDefs4(ServerSelector::ALL());
    ASSERT_TRUE(option_defs.empty());

    {
        SCOPED_TRACE("DELETE audit entries for the remaining option definitions");
        // The last parameter indicates that we expect two new audit entries.
        testNewAuditEntry("dhcp4_option_def",
                          AuditEntry::ModificationType::DELETE,
                          "deleted all option definitions", 2);
    }
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
        cbptr_->createUpdateOptionDef4(ServerSelector::ALL(),
                                       test_option_defs_[i]);
    }

    // Fetch option definitions with timestamp later than today. Only one
    // option definition should be returned.
    OptionDefContainer
        option_defs = cbptr_->getModifiedOptionDefs4(ServerSelector::ALL(),
                                                     timestamps_["today"]);
    ASSERT_EQ(1, option_defs.size());

    // Fetch option definitions with timestamp later than yesterday. We
    // should get two option definitions.
    option_defs = cbptr_->getModifiedOptionDefs4(ServerSelector::ALL(),
                                                 timestamps_["yesterday"]);
    ASSERT_EQ(2, option_defs.size());

    // Fetch option definitions with timestamp later than tomorrow. Nothing
    // should be returned.
    option_defs = cbptr_->getModifiedOptionDefs4(ServerSelector::ALL(),
                                              timestamps_["tomorrow"]);
    ASSERT_TRUE(option_defs.empty());
}

// This test verifies that global option can be added, updated and deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteOption4) {
    // Add option to the database.
    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                opt_boot_file_name);

    // Make sure we can retrieve this option and that it is equal to the
    // option we have inserted into the database.
    OptionDescriptorPtr returned_opt_boot_file_name =
        cbptr_->getOption4(ServerSelector::ALL(),
                           opt_boot_file_name->option_->getType(),
                           opt_boot_file_name->space_name_);
    ASSERT_TRUE(returned_opt_boot_file_name);

    {
        SCOPED_TRACE("verify created option");
        testOptionsEquivalent(*test_options_[0], *returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("CREATE audit entry for an option");
        testNewAuditEntry("dhcp4_options",
                          AuditEntry::ModificationType::CREATE,
                          "global option set");
    }

    // Modify option and update it in the database.
    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                opt_boot_file_name);

    // Retrieve the option again and make sure that updates were
    // properly propagated to the database.
    returned_opt_boot_file_name = cbptr_->getOption4(ServerSelector::ALL(),
                                                     opt_boot_file_name->option_->getType(),
                                                     opt_boot_file_name->space_name_);
    ASSERT_TRUE(returned_opt_boot_file_name);

    {
        SCOPED_TRACE("verify updated option");
        testOptionsEquivalent(*opt_boot_file_name, *returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for an option");
        testNewAuditEntry("dhcp4_options",
                          AuditEntry::ModificationType::UPDATE,
                          "global option set");
    }

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption4(ServerSelector::ONE("server1"),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Deleting option for all servers should succeed.
    EXPECT_EQ(1, cbptr_->deleteOption4(ServerSelector::ALL(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    EXPECT_FALSE(cbptr_->getOption4(ServerSelector::ALL(),
                                    opt_boot_file_name->option_->getType(),
                                    opt_boot_file_name->space_name_));

    {
        SCOPED_TRACE("DELETE audit entry for an option");
        testNewAuditEntry("dhcp4_options",
                          AuditEntry::ModificationType::DELETE,
                          "global option deleted");
    }
}

// This test verifies that all global options can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllOptions4) {
    // Add three global options to the database.
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                test_options_[0]);
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                test_options_[1]);
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                test_options_[5]);

    // Retrieve all these options.
    OptionContainer returned_options = cbptr_->getAllOptions4(ServerSelector::ALL());
    ASSERT_EQ(3, returned_options.size());

    // Fetching global options with explicitly specified server tag should return
    // the same result.
    returned_options = cbptr_->getAllOptions4(ServerSelector::ONE("server1"));
    ASSERT_EQ(3, returned_options.size());

    // Get the container index used to search options by option code.
    const OptionContainerTypeIndex& index = returned_options.get<1>();

    // Verify that all options we put into the database were
    // returned.
    {
        SCOPED_TRACE("verify test_options_[0]");
        auto option0 = index.find(test_options_[0]->option_->getType());
        ASSERT_FALSE(option0 == index.end());
        testOptionsEquivalent(*test_options_[0], *option0);
    }

    {
        SCOPED_TRACE("verify test_options_[1]");
        auto option1 = index.find(test_options_[1]->option_->getType());
        ASSERT_FALSE(option1 == index.end());
        testOptionsEquivalent(*test_options_[1], *option1);
    }

    {
        SCOPED_TRACE("verify test_options_[5]");
        auto option5 = index.find(test_options_[5]->option_->getType());
        ASSERT_FALSE(option5 == index.end());
        testOptionsEquivalent(*test_options_[5], *option5);
    }
}

// This test verifies that modified global options can be retrieved.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedOptions4) {
    // Assign timestamps to the options we're going to store in the
    // database.
    test_options_[0]->setModificationTime(timestamps_["tomorrow"]);
    test_options_[1]->setModificationTime(timestamps_["yesterday"]);
    test_options_[5]->setModificationTime(timestamps_["today"]);

    // Put options into the database.
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                test_options_[0]);
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                test_options_[1]);
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                test_options_[5]);

    // Get options with the timestamp later than today. Only
    // one option should be returned.
    OptionContainer returned_options =
        cbptr_->getModifiedOptions4(ServerSelector::ALL(),
                                    timestamps_["today"]);
    ASSERT_EQ(1, returned_options.size());

    // Fetching modified options with explicitly specified server selector
    // should return the same result.
    returned_options = cbptr_->getModifiedOptions4(ServerSelector::ONE("server1"),
                                                   timestamps_["today"]);
    ASSERT_EQ(1, returned_options.size());

    // The returned option should be the one with the timestamp
    // set to tomorrow.
    const OptionContainerTypeIndex& index = returned_options.get<1>();
    auto option0 = index.find(test_options_[0]->option_->getType());
    ASSERT_FALSE(option0 == index.end());
    {
        SCOPED_TRACE("verify returned option");
        testOptionsEquivalent(*test_options_[0], *option0);
    }
}

// This test verifies that subnet level option can be added, updated and
// deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteSubnetOption4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                                    subnet->getID());
    ASSERT_TRUE(returned_subnet);

    {
        SCOPED_TRACE("CREATE audit entry for a new subnet");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::CREATE,
                          "subnet set");
    }

    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::ALL(), subnet->getID(),
                                opt_boot_file_name);

    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);

    OptionDescriptor returned_opt_boot_file_name =
        returned_subnet->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);

    {
        SCOPED_TRACE("verify returned option");
        testOptionsEquivalent(*opt_boot_file_name, returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for an added subnet option");
        // Instead of adding an audit entry for an option we add an audit
        // entry for the entire subnet so as the server refreshes the
        // subnet with the new option. Note that the server doesn't
        // have means to retrieve only the newly added option.
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "subnet specific option set");
    }

    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::ALL(), subnet->getID(),
                                opt_boot_file_name);

    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    returned_opt_boot_file_name =
        returned_subnet->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);

    {
        SCOPED_TRACE("verify returned option with modified persistence");
        testOptionsEquivalent(*opt_boot_file_name, returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for an updated subnet option");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "subnet specific option set");
    }

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption4(ServerSelector::ONE("server1"),
                                       subnet->getID(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // It should succeed for all servers.
    EXPECT_EQ(1, cbptr_->deleteOption4(ServerSelector::ALL(), subnet->getID(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);

    EXPECT_FALSE(returned_subnet->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME).option_);

    {
        SCOPED_TRACE("UPDATE audit entry for a deleted subnet option");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "subnet specific option deleted");
    }
}

// This test verifies that option can be inserted, updated and deleted
// from the pool.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeletePoolOption4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::ALL(), subnet);

    {
        SCOPED_TRACE("CREATE audit entry for a subnet");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::CREATE,
                          "subnet set");
    }

    // Add an option into the pool.
    const PoolPtr pool = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.2.10"));
    ASSERT_TRUE(pool);
    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                pool->getFirstAddress(),
                                pool->getLastAddress(),
                                opt_boot_file_name);

    // Query for a subnet.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
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

    {
        SCOPED_TRACE("verify returned pool option");
        testOptionsEquivalent(*opt_boot_file_name, returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for a subnet after adding an option "
                     "to the pool");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "pool specific option set");
    }


    // Modify the option and update it in the database.
    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                pool->getFirstAddress(),
                                pool->getLastAddress(),
                                opt_boot_file_name);

    // Fetch the subnet and the corresponding pool.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    const PoolPtr returned_pool1 = returned_subnet->getPool(Lease::TYPE_V4,
                                                            IOAddress("192.0.2.10"));
    ASSERT_TRUE(returned_pool1);

    // Test that the option has been correctly updated in the database.
    returned_opt_boot_file_name =
        returned_pool1->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);

    {
        SCOPED_TRACE("verify updated option with modified persistence");
        testOptionsEquivalent(*opt_boot_file_name, returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for a subnet when updating pool "
                     "specific option");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "pool specific option set");
    }

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption4(ServerSelector::ONE("server1"),
                                       pool->getFirstAddress(),
                                       pool->getLastAddress(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Delete option for all servers should succeed.
    EXPECT_EQ(1, cbptr_->deleteOption4(ServerSelector::ALL(),
                                       pool->getFirstAddress(),
                                       pool->getLastAddress(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Fetch the subnet and the pool from the database again to make sure
    // that the option is really gone.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::ALL(),
                                         subnet->getID());
    ASSERT_TRUE(returned_subnet);
    const PoolPtr returned_pool2 = returned_subnet->getPool(Lease::TYPE_V4,
                                                            IOAddress("192.0.2.10"));
    ASSERT_TRUE(returned_pool2);

    // Option should be gone.
    EXPECT_FALSE(returned_pool2->getCfgOption()->get(DHCP4_OPTION_SPACE,
                                                     DHO_BOOT_FILE_NAME).option_);

    {
        SCOPED_TRACE("UPDATE audit entry for a subnet when deleting pool "
                     "specific option");
        testNewAuditEntry("dhcp4_subnet",
                          AuditEntry::ModificationType::UPDATE,
                          "pool specific option deleted");
    }
}

// This test verifies that shared network level option can be added,
// updated and deleted.
TEST_F(MySqlConfigBackendDHCPv4Test, createUpdateDeleteSharedNetworkOption4) {
    // Insert new shared network.
    SharedNetwork4Ptr shared_network = test_networks_[1];
    cbptr_->createUpdateSharedNetwork4(ServerSelector::ALL(),
                                       shared_network);

    // Fetch this shared network by name.
    SharedNetwork4Ptr returned_network =
        cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                  shared_network->getName());
    ASSERT_TRUE(returned_network);

    {
        SCOPED_TRACE("CREATE audit entry for the new shared network");
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::CREATE,
                          "shared network set");
    }

    OptionDescriptorPtr opt_boot_file_name = test_options_[0];
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                shared_network->getName(),
                                opt_boot_file_name);

    returned_network = cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                                shared_network->getName());
    ASSERT_TRUE(returned_network);

    OptionDescriptor returned_opt_boot_file_name =
        returned_network->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);

    {
        SCOPED_TRACE("verify returned option");
        testOptionsEquivalent(*opt_boot_file_name, returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for the added shared network option");
        // Instead of adding an audit entry for an option we add an audit
        // entry for the entire shared network so as the server refreshes the
        // shared network with the new option. Note that the server doesn't
        // have means to retrieve only the newly added option.
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::UPDATE,
                          "shared network specific option set");
    }

    opt_boot_file_name->persistent_ = !opt_boot_file_name->persistent_;
    cbptr_->createUpdateOption4(ServerSelector::ALL(),
                                shared_network->getName(),
                                opt_boot_file_name);

    returned_network = cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                                 shared_network->getName());
    ASSERT_TRUE(returned_network);
    returned_opt_boot_file_name =
        returned_network->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(returned_opt_boot_file_name.option_);

    {
        SCOPED_TRACE("verify updated option with modified persistence");
        testOptionsEquivalent(*opt_boot_file_name, returned_opt_boot_file_name);
    }

    {
        SCOPED_TRACE("UPDATE audit entry for the updated shared network option");
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::UPDATE,
                          "shared network specific option set");
    }

    // Deleting an option with explicitly specified server tag should fail.
    EXPECT_EQ(0, cbptr_->deleteOption4(ServerSelector::ONE("server1"),
                                       shared_network->getName(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));

    // Deleting an option for all servers should succeed.
    EXPECT_EQ(1, cbptr_->deleteOption4(ServerSelector::ALL(),
                                       shared_network->getName(),
                                       opt_boot_file_name->option_->getType(),
                                       opt_boot_file_name->space_name_));
    returned_network = cbptr_->getSharedNetwork4(ServerSelector::ALL(),
                                                 shared_network->getName());
    ASSERT_TRUE(returned_network);
    EXPECT_FALSE(returned_network->getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME).option_);

    {
        SCOPED_TRACE("UPDATE audit entry for the deleted shared network option");
        testNewAuditEntry("dhcp4_shared_network",
                          AuditEntry::ModificationType::UPDATE,
                          "shared network specific option deleted");
    }
}


}
