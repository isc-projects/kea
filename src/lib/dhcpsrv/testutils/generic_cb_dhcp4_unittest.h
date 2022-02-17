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

/// @brief Describes an expected audit table entry.
struct ExpAuditEntry {
    /// @brief Type of object changed.
    std::string object_type;

    /// @brief Timestamp the change occurred.
    db::AuditEntry::ModificationType modification_type;

    /// @brief Log message describing the change.
    std::string log_message;
};

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
    virtual ~GenericConfigBackendDHCPv4Test() {};

    /// @brief Prepares the class for a test.
    ///
    /// Invoked by gtest prior test entry, we create the
    /// appropriate schema and create a basic host manager to
    /// wipe out any prior instance
    virtual void SetUp();

    /// @brief Pre-test exit clean up
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
    void testNewAuditEntry(const std::string& exp_object_type,
                           const db::AuditEntry::ModificationType& exp_modification_type,
                           const std::string& exp_log_message,
                           const db::ServerSelector& server_selector = db::ServerSelector::ALL(),
                           const size_t new_entries_num = 1,
                           const size_t max_tested_entries = 65535);

    /// @brief Checks the new audit entries against a list of
    /// expected entries.
    ///
    /// This method retrieves a collection of the existing audit entries and
    /// checks that number and content of the expected new entries have been
    /// added to the end of this collection.
    ///
    /// @param exp_entries a list of the expected new audit entries.
    /// @param server_selector Server selector to be used for next query.
    void testNewAuditEntry(const std::vector<ExpAuditEntry>& exp_entries,
                           const db::ServerSelector& server_selector);

    /// @brief This test verifies that the server can be added, updated and deleted.
    void createUpdateDeleteServerTest();

    /// @brief This test verifies that it is possible to retrieve all servers from the
    /// database and then delete all of them.
    void getAndDeleteAllServersTest();

    /// @brief This test verifies that the global parameter can be added, updated and
    /// deleted.
    void createUpdateDeleteGlobalParameter4Test();

    /// @brief This test verifies that it is possible to differentiate between the
    /// global parameters by server tag and that the value specified for the
    /// particular server overrides the value specified for all servers.
    void globalParameters4WithServerTagsTest();

    /// @brief This test verifies that all global parameters can be retrieved and deleted.
    void getAllGlobalParameters4Test();

    /// @brief This test verifies that modified global parameters can be retrieved.
    void getModifiedGlobalParameters4Test();

    /// @brief Test that the NullKeyError message is correctly updated.
    void nullKeyErrorTest();

    /// @brief Test that createUpdateSubnet4 throws appropriate exceptions for various
    /// server selectors.
    void createUpdateSubnet4SelectorsTest();

    /// @brief Test that subnet can be inserted, fetched, updated and then fetched again.
    void getSubnet4Test();

    /// @brief Test that getSubnet4 by ID throws appropriate exceptions for various server
    /// selectors.
    void getSubnet4byIdSelectorsTest();

    /// @brief Test that the information about unspecified optional parameters gets
    /// propagated to the database.
    void getSubnet4WithOptionalUnspecifiedTest();

    /// @brief Test that subnet can be associated with a shared network.
    void getSubnet4SharedNetworkTest();

    /// @brief Test that subnet can be fetched by prefix.
    void getSubnet4ByPrefixTest();

    /// @brief Test that getSubnet4 by prefix throws appropriate exceptions for various server
    /// selectors.
    void getSubnet4byPrefixSelectorsTest();

    /// @brief Test that all subnets can be fetched and then deleted.
    void getAllSubnets4Test();

    /// @brief Test that getAllSubnets4 throws appropriate exceptions for various
    /// server selectors.
    void getAllSubnets4SelectorsTest();

    /// @brief Test that subnets with different server associations are returned.
    void getAllSubnets4WithServerTagsTest();

    /// @brief Test that getModifiedSubnets4 throws appropriate exceptions for various
    /// server selectors.
    void getModifiedSubnets4SelectorsTest();

    /// @brief Test that selected subnet can be deleted.
    void deleteSubnet4Test();

    /// @brief Test that deleteSubnet4 by ID throws appropriate exceptions for various
    /// server selectors.
    void deleteSubnet4ByIdSelectorsTest();

    /// @brief Test that deleteSubnet4 by prefix throws appropriate exceptions for various
    /// server selectors.
    void deleteSubnet4ByPrefixSelectorsTest();

    /// @brief Test that deleteAllSubnets4 throws appropriate exceptions for various
    /// server selectors.
    void deleteAllSubnets4SelectorsTest();

    /// @brief Test that it is possible to retrieve and delete orphaned subnet.
    void unassignedSubnet4Test();

    /// @brief Test that subnets modified after given time can be fetched.
    void getModifiedSubnets4Test();

    /// @brief Test that lifetimes in subnets are handled as expected.
    void subnetLifetimeTest();

    /// @brief Test that subnets belonging to a shared network can be retrieved.
    void getSharedNetworkSubnets4Test();

    /// @brief Test that pools are properly updated as a result a subnet update.
    void subnetUpdatePoolsTest();

    /// @brief Test that deleting a subnet triggers deletion of the options associated
    /// with the subnet and pools.
    void subnetOptionsTest();

    /// @brief Test that shared network can be inserted, fetched, updated and then
    /// fetched again.
    void getSharedNetwork4Test();

    /// @brief Test that getSharedNetwork4 throws appropriate exceptions for various
    /// server selectors.
    void getSharedNetwork4SelectorsTest();

    /// @brief Test that shared network may be created and updated and the server tags
    /// are properly assigned to it.
    void createUpdateSharedNetwork4Test();

    /// @brief Test that createUpdateSharedNetwork4 throws appropriate exceptions for various
    /// server selectors.
    void createUpdateSharedNetwork4SelectorsTest();

    /// @brief Test that the information about unspecified optional parameters gets
    /// propagated to the database.
    void getSharedNetwork4WithOptionalUnspecifiedTest();

    /// @brief Test that deleteSharedNetworkSubnets4 with not ANY selector throw.
    void deleteSharedNetworkSubnets4Test();

    /// @brief Test that all shared networks can be fetched.
    void getAllSharedNetworks4Test();

    /// @brief Test that getAllSharedNetworks4 throws appropriate exceptions for various
    /// server selectors.
    void getAllSharedNetworks4SelectorsTest();

    /// @brief Test that shared networks with different server associations are returned.
    void getAllSharedNetworks4WithServerTagsTest();

    /// @brief Test that shared networks modified after given time can be fetched.
    void getModifiedSharedNetworks4Test();

    /// @brief Test that getModifiedSharedNetworks4 throws appropriate exceptions for various
    /// server selectors.
    void getModifiedSharedNetworks4SelectorsTest();

    /// @brief Test that selected shared network can be deleted.
    void deleteSharedNetwork4Test();

    /// @brief Test that deleteSharedNetwork4 throws appropriate exceptions for various
    /// server selectors.
    void deleteSharedNetwork4SelectorsTest();

    /// @brief Test that deleteAllSharedNetworks4 throws appropriate exceptions for various
    /// server selectors.
    void deleteAllSharedNetworks4SelectorsTest();

    /// @brief Test that it is possible to retrieve and delete orphaned shared network.
    void unassignedSharedNetworkTest();

    /// @brief Test that lifetimes in shared networks are handled as expected.
    void sharedNetworkLifetimeTest();

    /// @brief Test that deleting a shared network triggers deletion of the options
    /// associated with the shared network.
    void sharedNetworkOptionsTest();

    /// @brief Test that option definition can be inserted, fetched, updated and then
    /// fetched again.
    void getOptionDef4Test();

    /// @brief This test verifies that it is possible to differentiate between the
    /// option definitions by server tag and that the option definition
    /// specified for the particular server overrides the definition for
    /// all servers.
    void optionDefs4WithServerTagsTest();

    /// @brief Test that all option definitions can be fetched.
    void getAllOptionDefs4Test();

    /// @brief Test that option definitions modified after given time can be fetched.
    void getModifiedOptionDefs4Test();

    /// @brief This test verifies that global option can be added, updated and deleted.
    void createUpdateDeleteOption4Test();

    /// @brief This test verifies that it is possible to differentiate between the
    /// global options by server tag and that the option specified for the
    /// particular server overrides the value specified for all servers.
    void globalOptions4WithServerTagsTest();

    /// @brief This test verifies that all global options can be retrieved.
    void getAllOptions4Test();

    /// @brief This test verifies that modified global options can be retrieved.
    void getModifiedOptions4Test();

    /// @brief This test verifies that subnet level option can be added, updated and
    /// deleted.
    void createUpdateDeleteSubnetOption4Test();

    /// @brief This test verifies that option can be inserted, updated and deleted
    /// from the pool.
    void createUpdateDeletePoolOption4Test();

    /// @brief This test verifies that shared network level option can be added,
    /// updated and deleted.
    void createUpdateDeleteSharedNetworkOption4Test();

    /// @brief This test verifies that option id values in one subnet do
    /// not impact options returned in subsequent subnets when
    /// fetching subnets from the backend.
    void subnetOptionIdOrderTest();

    /// @brief This test verifies that option id values in one shared network do
    /// not impact options returned in subsequent shared networks when
    /// fetching shared networks from the backend.
    void sharedNetworkOptionIdOrderTest();

    /// @brief This test verifies that it is possible to create client classes, update them
    /// and retrieve all classes for a given server.
    void setAndGetAllClientClasses4Test();

    /// @brief This test verifies that a single class can be retrieved from the database.
    void getClientClass4Test();

    /// @brief This test verifies that client class specific DHCP options can be
    /// modified during the class update.
    void createUpdateClientClass4OptionsTest();

    /// @brief This test verifies that modified client classes can be retrieved from the database.
    void getModifiedClientClasses4Test();

    /// @brief This test verifies that a specified client class can be deleted.
    void deleteClientClass4Test();

    /// @brief This test verifies that all client classes can be deleted using
    /// a specified server selector.
    void deleteAllClientClasses4Test();

    /// @brief This test verifies that client class dependencies are tracked when the
    /// classes are added to the database. It verifies that an attempt to update
    /// a class violating the dependencies results in an error.
    void clientClassDependencies4Test();

    /// @brief This test verifies that audit entries can be retrieved from a given
    /// timestamp and id including when two entries can get the same timestamp.
    /// (either it is a common even and this should catch it, or it is a rare
    /// event and it does not matter).
    void multipleAuditEntriesTest();

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
