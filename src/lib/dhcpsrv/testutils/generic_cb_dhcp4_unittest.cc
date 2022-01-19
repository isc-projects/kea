// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <database/server.h>
#include <database/testutils/schema.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_space.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/testutils/generic_cb_dhcp4_unittest.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <testutils/gtest_utils.h>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace isc::test;
namespace ph = std::placeholders;

void
GenericConfigBackendDHCPv4Test::SetUp() {
    // Ensure we have the proper schema with no transient data.
    createSchema();

    try {
        // Create a connection parameter map and use it to start the backend.
        DatabaseConnection::ParameterMap params =
            DatabaseConnection::parse(validConnectionString());
        cbptr_ = backendFactory(params);
    } catch (...) {
        std::cerr << "*** ERROR: unable to open database. The test\n"
                     "*** environment is broken and must be fixed before\n"
                     "*** the tests will run correctly.\n"
                     "*** The reason for the problem is described in the\n"
                     "*** accompanying exception output.\n";
        throw;
    }

    // Create test data.
    initTestServers();
    initTestOptions();
    initTestSubnets();
    initTestSharedNetworks();
    initTestOptionDefs();
    initTestClientClasses();
    initTimestamps();
}

void
GenericConfigBackendDHCPv4Test::TearDown() {
    cbptr_.reset();
    // If data wipe enabled, delete transient data otherwise destroy the schema.
    destroySchema();
}

void
GenericConfigBackendDHCPv4Test::initTestServers() {
    test_servers_.push_back(Server::create(ServerTag("server1"), "this is server 1"));
    test_servers_.push_back(Server::create(ServerTag("server1"), "this is server 1 bis"));
    test_servers_.push_back(Server::create(ServerTag("server2"), "this is server 2"));
    test_servers_.push_back(Server::create(ServerTag("server3"), "this is server 3"));
}

void
GenericConfigBackendDHCPv4Test::initTestSubnets() {
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
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    subnet->setSname("server-hostname");
    subnet->setContext(user_context);
    subnet->setValid(555555);
    subnet->setAuthoritative(true);
    subnet->setCalculateTeeTimes(true);
    subnet->setT1Percent(0.345);
    subnet->setT2Percent(0.444);
    subnet->setDdnsSendUpdates(false);

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

    pool2->allowClientClass("work");
    pool2->requireClientClass("required-class3");
    pool2->requireClientClass("required-class4");
    user_context = Element::createMap();
    user_context->set("bar", Element::create("foo"));
    pool2->setContext(user_context);

    subnet->addPool(pool2);

    test_subnets_.push_back(subnet);

    subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 20, 30, 40, 2048));
    Triplet<uint32_t> null_timer;
    subnet->setT1(null_timer);
    subnet->setT2(null_timer);
    subnet->setValid(null_timer);
    subnet->setDdnsSendUpdates(true);
    subnet->setDdnsOverrideNoUpdate(true);
    subnet->setDdnsOverrideClientUpdate(false);
    subnet->setDdnsReplaceClientNameMode(D2ClientConfig::ReplaceClientNameMode::RCM_WHEN_PRESENT);
    subnet->setDdnsGeneratedPrefix("myhost");
    subnet->setDdnsQualifyingSuffix("example.org");

    subnet->getCfgOption()->add(test_options_[0]->option_,
                                test_options_[0]->persistent_,
                                test_options_[0]->space_name_);

    test_subnets_.push_back(subnet);

    // Add a subnet with all defaults.
    subnet.reset(new Subnet4(IOAddress("192.0.4.0"), 24, Triplet<uint32_t>(),
                             Triplet<uint32_t>(), Triplet<uint32_t>(), 4096));
    test_subnets_.push_back(subnet);
}

void
GenericConfigBackendDHCPv4Test::initTestSharedNetworks() {
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
    shared_network->setReservationsGlobal(false);
    shared_network->setReservationsInSubnet(false);
    shared_network->setContext(user_context);
    shared_network->setValid(5555);
    shared_network->setCalculateTeeTimes(true);
    shared_network->setT1Percent(0.345);
    shared_network->setT2Percent(0.444);
    shared_network->setSiaddr(IOAddress("192.0.1.2"));
    shared_network->setSname("frog");
    shared_network->setFilename("/dev/null");
    shared_network->setAuthoritative(true);
    shared_network->setDdnsSendUpdates(false);

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
    shared_network->setDdnsSendUpdates(true);
    shared_network->setDdnsOverrideNoUpdate(true);
    shared_network->setDdnsOverrideClientUpdate(false);
    shared_network->setDdnsReplaceClientNameMode(D2ClientConfig::ReplaceClientNameMode::RCM_WHEN_PRESENT);
    shared_network->setDdnsGeneratedPrefix("myhost");
    shared_network->setDdnsQualifyingSuffix("example.org");

    shared_network->getCfgOption()->add(test_options_[0]->option_,
                                        test_options_[0]->persistent_,
                                        test_options_[0]->space_name_);
    test_networks_.push_back(shared_network);

    shared_network.reset(new SharedNetwork4("level3"));
    test_networks_.push_back(shared_network);
}

void
GenericConfigBackendDHCPv4Test::initTestOptionDefs() {
    ElementPtr user_context = Element::createMap();
    user_context->set("foo", Element::create("bar"));

    OptionDefinitionPtr option_def(new OptionDefinition("foo", 234,
                                                        DHCP4_OPTION_SPACE,
                                                        "string",
                                                        "espace"));
    test_option_defs_.push_back(option_def);

    option_def.reset(new OptionDefinition("bar", 234, DHCP4_OPTION_SPACE,
                                          "uint32", true));
    test_option_defs_.push_back(option_def);

    option_def.reset(new OptionDefinition("fish", 235, DHCP4_OPTION_SPACE,
                                          "record", true));
    option_def->addRecordField("uint32");
    option_def->addRecordField("string");
    test_option_defs_.push_back(option_def);

    option_def.reset(new OptionDefinition("whale", 236, "xyz", "string"));
    test_option_defs_.push_back(option_def);

    option_def.reset(new OptionDefinition("foobar", 234, DHCP4_OPTION_SPACE,
                                          "uint64", true));
    test_option_defs_.push_back(option_def);
}

void
GenericConfigBackendDHCPv4Test::initTestOptions() {
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

    desc = createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                      true, false, "my-boot-file-2");
    desc.space_name_ = DHCP4_OPTION_SPACE;
    desc.setContext(user_context);
    test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

    desc = createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                      true, false, "my-boot-file-3");
    desc.space_name_ = DHCP4_OPTION_SPACE;
    desc.setContext(user_context);
    test_options_.push_back(OptionDescriptorPtr(new OptionDescriptor(desc)));

    // Add definitions for DHCPv4 non-standard options in case we need to
    // compare subnets, networks and pools in JSON format. In that case,
    // the @c toElement functions require option definitions to generate the
    // proper output.
    defs.addItem(OptionDefinitionPtr(new OptionDefinition("vendor-encapsulated-1", 1,
                                                          "vendor-encapsulated-options",
                                                          "uint32")));
    defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-254", 254,
                                                          DHCP4_OPTION_SPACE,
                                                          "ipv4-address", true)));
    defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-1", 1, "isc", "empty")));
    defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-2", 2, "isc", "ipv4-address", true)));

    // Register option definitions.
    LibDHCP::setRuntimeOptionDefs(defs);
}

void
GenericConfigBackendDHCPv4Test::initTestClientClasses() {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();
    auto class1 = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
    class1->setRequired(true);
    class1->setNextServer(IOAddress("1.2.3.4"));
    class1->setSname("cool");
    class1->setFilename("epc.cfg");
    class1->setValid(Triplet<uint32_t>(30, 60, 90));
    test_client_classes_.push_back(class1);

    auto class2 = boost::make_shared<ClientClassDef>("bar", match_expr, cfg_option);
    class2->setTest("member('foo')");
    test_client_classes_.push_back(class2);

    auto class3 = boost::make_shared<ClientClassDef>("foobar", match_expr, cfg_option);
    class3->setTest("member('foo') and member('bar')");
    test_client_classes_.push_back(class3);
}

void
GenericConfigBackendDHCPv4Test::initTimestamps() {
    // Current time minus 1 hour to make sure it is in the past.
    timestamps_["today"] = boost::posix_time::second_clock::local_time()
                           - boost::posix_time::hours(1);
    // One second after today.
    timestamps_["after today"] = timestamps_["today"] + boost::posix_time::seconds(1);
    // Yesterday.
    timestamps_["yesterday"] = timestamps_["today"] - boost::posix_time::hours(24);
    // One second after yesterday.
    timestamps_["after yesterday"] = timestamps_["yesterday"] + boost::posix_time::seconds(1);
    // Two days ago.
    timestamps_["two days ago"] = timestamps_["today"] - boost::posix_time::hours(48);
    // Tomorrow.
    timestamps_["tomorrow"] = timestamps_["today"] + boost::posix_time::hours(24);
    // One second after tomorrow.
    timestamps_["after tomorrow"] = timestamps_["tomorrow"] + boost::posix_time::seconds(1);
}

std::string
GenericConfigBackendDHCPv4Test::logExistingAuditEntries(const std::string& server_tag) {
    std::ostringstream s;

    auto& mod_time_idx = audit_entries_[server_tag].get<AuditEntryModificationTimeIdTag>();

    for (auto audit_entry_it = mod_time_idx.begin();
         audit_entry_it != mod_time_idx.end();
         ++audit_entry_it) {
        auto audit_entry = *audit_entry_it;
        s << audit_entry->getObjectType() << ", "
          << audit_entry->getObjectId() << ", "
          << static_cast<int>(audit_entry->getModificationType()) << ", "
          << audit_entry->getModificationTime() << ", "
          << audit_entry->getRevisionId() << ", "
          << audit_entry->getLogMessage()
          << std::endl;
    }

    return (s.str());
}

void
GenericConfigBackendDHCPv4Test::getTypeTest(const std::string& expected_type) {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_ = backendFactory(params));
    ASSERT_NE(cbptr_->getParameters(), DatabaseConnection::ParameterMap());
    EXPECT_EQ(expected_type, cbptr_->getType());
}

void
GenericConfigBackendDHCPv4Test::getHostTest() {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_ = backendFactory(params));
    ASSERT_NE(cbptr_->getParameters(), DatabaseConnection::ParameterMap());
    EXPECT_EQ("localhost", cbptr_->getHost());
}

void
GenericConfigBackendDHCPv4Test::getPortTest() {
    DatabaseConnection::ParameterMap params;
    params["name"] = "keatest";
    params["password"] = "keatest";
    params["user"] = "keatest";
    ASSERT_NO_THROW(cbptr_ = backendFactory(params));
    ASSERT_NE(cbptr_->getParameters(), DatabaseConnection::ParameterMap());
    EXPECT_EQ(0, cbptr_->getPort());
}

void
GenericConfigBackendDHCPv4Test::newAuditEntryTest(const std::string& exp_object_type,
                                                  const AuditEntry::ModificationType&
                                                        exp_modification_type,
                                                  const std::string& exp_log_message,
                                                  const ServerSelector& server_selector,
                                                  const size_t new_entries_num,
                                                  const size_t max_tested_entries) {

    // Get the server tag for which the entries are fetched.
    std::string tag;
    if (server_selector.getType() == ServerSelector::Type::ALL) {
        // Server tag is 'all'.
        tag = "all";
    } else {
        auto tags = server_selector.getTags();
        // This test is not meant to handle multiple server tags all at once.
        if (tags.size() > 1) {
            ADD_FAILURE() << "Test error: do not use multiple server tags";
        } else if (tags.size() == 1) {
            // Get the server tag for which we run the current test.
            tag = tags.begin()->get();
        }
    }

    auto audit_entries_size_save = audit_entries_[tag].size();

    // Audit entries for different server tags are stored in separate
    // containers.
    ASSERT_NO_THROW_LOG(audit_entries_[tag]
                        = cbptr_->getRecentAuditEntries(server_selector,
                                                        timestamps_["two days ago"], 0));
    ASSERT_EQ(audit_entries_size_save + new_entries_num, audit_entries_[tag].size())
              << logExistingAuditEntries(tag);

    auto& mod_time_idx = audit_entries_[tag].get<AuditEntryModificationTimeIdTag>();

    // Iterate over specified number of entries starting from the most recent
    // one and check they have correct values.
    for (auto audit_entry_it = mod_time_idx.rbegin();
         ((std::distance(mod_time_idx.rbegin(), audit_entry_it) < new_entries_num) &&
         (std::distance(mod_time_idx.rbegin(), audit_entry_it) < max_tested_entries));
         ++audit_entry_it) {
        auto audit_entry = *audit_entry_it;
        EXPECT_EQ(exp_object_type, audit_entry->getObjectType())
                  << logExistingAuditEntries(tag);
        EXPECT_EQ(exp_modification_type, audit_entry->getModificationType())
                  << logExistingAuditEntries(tag);
        EXPECT_EQ(exp_log_message, audit_entry->getLogMessage())
                  << logExistingAuditEntries(tag);
    }
}

// This test verifies that the server can be added, updated and deleted.
void GenericConfigBackendDHCPv4Test::createUpdateDeleteServerTest() {
    // Explicitly set modification time to make sure that the time
    // returned from the database is correct.
    test_servers_[0]->setModificationTime(timestamps_["yesterday"]);
    test_servers_[1]->setModificationTime(timestamps_["today"]);

    // Insert the server1 into the database.
    ASSERT_NO_THROW_LOG(cbptr_->createUpdateServer4(test_servers_[0]));

    {
        SCOPED_TRACE("CREATE audit entry for server");
        newAuditEntryTest("dhcp4_server",
                          AuditEntry::ModificationType::CREATE,
                          "server set");
    }

    // It should not be possible to create a duplicate of the logical
    // server 'all'.
    auto all_server = Server::create(ServerTag("all"), "this is logical server all");
    EXPECT_THROW(cbptr_->createUpdateServer4(all_server), isc::InvalidOperation);

    ServerPtr returned_server;

    // An attempt to fetch the server that hasn't been inserted should return
    // a null pointer.
    ASSERT_NO_THROW_LOG(returned_server = cbptr_->getServer4(ServerTag("server2")));
    EXPECT_FALSE(returned_server);

    // Try to fetch the server which we expect to exist.
    ASSERT_NO_THROW_LOG(returned_server = cbptr_->getServer4(ServerTag("server1")));
    ASSERT_TRUE(returned_server);
    EXPECT_EQ("server1", returned_server->getServerTag().get());
    EXPECT_EQ("this is server 1", returned_server->getDescription());
    EXPECT_EQ(timestamps_["yesterday"], returned_server->getModificationTime());

    // This call is expected to update the existing server.
    ASSERT_NO_THROW_LOG(cbptr_->createUpdateServer4(test_servers_[1]));

    {
        SCOPED_TRACE("UPDATE audit entry for server");
        newAuditEntryTest("dhcp4_server",
                          AuditEntry::ModificationType::UPDATE,
                          "server set");
    }

    // Verify that the server has been updated.
    ASSERT_NO_THROW_LOG(returned_server = cbptr_->getServer4(ServerTag("server1")));
    ASSERT_TRUE(returned_server);
    EXPECT_EQ("server1", returned_server->getServerTag().get());
    EXPECT_EQ("this is server 1 bis", returned_server->getDescription());
    EXPECT_EQ(timestamps_["today"], returned_server->getModificationTime());

    uint64_t servers_deleted = 0;

    // Try to delete non-existing server.
    ASSERT_NO_THROW_LOG(servers_deleted = cbptr_->deleteServer4(ServerTag("server2")));
    EXPECT_EQ(0, servers_deleted);

    // Make sure that the server1 wasn't deleted.
    ASSERT_NO_THROW_LOG(returned_server = cbptr_->getServer4(ServerTag("server1")));
    EXPECT_TRUE(returned_server);

    // Deleting logical server 'all' is not allowed.
    EXPECT_THROW(cbptr_->deleteServer4(ServerTag()), isc::InvalidOperation);

    // Delete the existing server.
    ASSERT_NO_THROW_LOG(servers_deleted = cbptr_->deleteServer4(ServerTag("server1")));
    EXPECT_EQ(1, servers_deleted);

    {
        SCOPED_TRACE("DELETE audit entry for server");
        newAuditEntryTest("dhcp4_server",
                          AuditEntry::ModificationType::DELETE,
                          "deleting a server");
    }

    // Make sure that the server is gone.
    ASSERT_NO_THROW_LOG(returned_server = cbptr_->getServer4(ServerTag("server1")));
    EXPECT_FALSE(returned_server);
}