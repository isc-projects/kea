// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_CONFIG_BACKEND_DHCP4_H
#define GENERIC_CONFIG_BACKEND_DHCP4_H

#include <database/database_connection.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Generic test fixture class for testing DHCPv4
/// config backend operations.
class GenericConfigBackendDHCPv4Test : public GenericBackendTest {
public:
    /// @brief Constructor.
    GenericConfigBackendDHCPv4Test()
        : test_subnets_(), test_networks_(), test_option_defs_(),
          test_options_(), test_client_classes_(), test_servers_(), timestamps_(),
          cbptr_(), audit_entries_() {
    }

    /// @brief Destructor.
    virtual ~GenericConfigBackendDHCPv4Test(){};

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic host manager to
    /// wipe out any prior instance
    virtual void SetUp();

    /// @brief Pre-text exit clean up
    ///
    /// Invoked by gtest upon test exit, we destroy the schema
    /// we created.
    virtual void TearDown();

    /// @brief Abstract method for destroying the back end specific schema
    virtual void destroySchema() = 0;

    /// @brief Abstract method for creating the back end specific schema
    virtual void createSchema() = 0;

    /// @brief Abstract method which returns the back end specific connection
    /// string
    virtual std::string validConnectionString() = 0;

    /// @brief Abstract method which instantiates an instance of a
    /// DHCPv4 configuration back end.
    ///
    /// @params Connection parameters describing the back end to create.
    ///
    /// @return Pointer to the newly created back end instance.
    virtual ConfigBackendDHCPv4Ptr backendFactory(db::DatabaseConnection::ParameterMap&
                                                  params) = 0;

    /// @brief Counts rows in a selected table in the back end database.
    ///
    /// This method can be used to verify that some configuration elements were
    /// deleted from a selected table as a result of cascade delete or a trigger.
    /// For example, deleting a subnet should trigger deletion of its address
    /// pools and options. By counting the rows on each table we can determine
    /// whether the deletion took place on all tables for which it was expected.
    ///
    /// @param table Table name.
    /// @return Number of rows in the specified table.
    virtual size_t countRows(const std::string& table) const = 0;

    /// @brief Creates several servers used in tests.
    void initTestServers();

    /// @brief Creates several subnets used in tests.
    void initTestSubnets();

    /// @brief Creates several subnets used in tests.
    void initTestSharedNetworks();

    /// @brief Creates several option definitions used in tests.
    void initTestOptionDefs();

    /// @brief Creates several DHCP options used in tests.
    void initTestOptions();

    /// @brief Creates several client classes used in tests.
    void initTestClientClasses();

    /// @brief Initialize posix time values used in tests.
    void initTimestamps();

    /// @brief Logs audit entries in the @c audit_entries_ member.
    ///
    /// This function is called in case of an error.
    ///
    /// @param server_tag Server tag for which the audit entries should be logged.
    std::string logExistingAuditEntries(const std::string& server_tag);

    /// @brief Tests that a backend of the given type can be instantiated.
    ///
    /// @param  expected_type type of the back end created (i.e. "mysql",
    /// "postgresql").
    void getTypeTest(const std::string& expected_type);

    /// @brief Verifies that a backend on the localhost can be instantiated.
    void getHostTest();

    /// @brief Verifies that a backend on the localhost port 0 can be instantiated.
    void getPortTest();

    /// @brief Tests that the new audit entry is added.
    ///
    /// This method retrieves a collection of the existing audit entries and
    /// checks that the new one has been added at the end of this collection.
    /// It then verifies the values of the audit entry against the values
    /// specified by the caller.
    ///
    /// @param exp_object_type Expected object type.
    /// @param exp_modification_type Expected modification type.
    /// @param exp_log_message Expected log message.
    /// @param server_selector Server selector to be used for next query.
    /// @param new_entries_num Number of the new entries expected to be inserted.
    /// @param max_tested_entries Maximum number of entries tested.
    void newAuditEntryTest(const std::string& exp_object_type,
                           const db::AuditEntry::ModificationType& exp_modification_type,
                           const std::string& exp_log_message,
                           const db::ServerSelector& server_selector = db::ServerSelector::ALL(),
                           const size_t new_entries_num = 1,
                           const size_t max_tested_entries = 65535);

    /// @brief Verifies that the server can be added, updated and deleted.
    void createUpdateDeleteServerTest();

    /// @brief Holds pointers to subnets used in tests.
    std::vector<Subnet4Ptr> test_subnets_;

    /// @brief Holds pointers to shared networks used in tests.
    std::vector<SharedNetwork4Ptr> test_networks_;

    /// @brief Holds pointers to option definitions used in tests.
    std::vector<OptionDefinitionPtr> test_option_defs_;

    /// @brief Holds pointers to options used in tests.
    std::vector<OptionDescriptorPtr> test_options_;

    /// @brief Holds pointers to classes used in tests.
    std::vector<ClientClassDefPtr> test_client_classes_;

    /// @brief Holds pointers to the servers used in tests.
    std::vector<db::ServerPtr> test_servers_;

    /// @brief Holds timestamp values used in tests.
    std::map<std::string, boost::posix_time::ptime> timestamps_;

    /// @brief Holds pointer to the backend.
    boost::shared_ptr<ConfigBackendDHCPv4> cbptr_;

    /// @brief Holds the most recent audit entries.
    std::map<std::string, db::AuditEntryCollection> audit_entries_;
};

}  // namespace test
}  // namespace dhcp
}  // namespace isc

#endif // GENERIC_CONFIG_BACKEND_DHCP4_H
