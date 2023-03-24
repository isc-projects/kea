// Copyright (C) 2019-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/stamped_value.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <dhcpsrv/cb_ctl_dhcp6.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp4.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp6.h>
#include <hooks/server_hooks.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks_manager.h>
#include <testutils/gtest_utils.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace isc::hooks;

namespace {

/// @brief Derivation of the @c MemHostDataSource which always returns
/// @c false when setting IP reservations unique/non-unique mode.
class NonUniqueHostDataSource : public MemHostDataSource {
public:

    /// @brief Virtual destructor.
    virtual ~NonUniqueHostDataSource() {}

    /// @brief Configure unique/non-unique IP reservations.
    ///
    /// @return Always false.
    virtual bool setIPReservationsUnique(const bool) {
        return (false);
    }
};

/// @brief Pointer to the @c NonUniqueHostDataSource instance.
typedef boost::shared_ptr<NonUniqueHostDataSource> NonUniqueHostDataSourcePtr;

/// @brief Base class for testing derivations of the CBControlDHCP.
class CBControlDHCPTest : public GenericBackendTest {
public:

    /// @brief Constructor.
    CBControlDHCPTest()
        : timestamp_(), object_timestamp_(), audit_entries_(),
          modification_id_(2345) {
        CfgMgr::instance().clear();
        initTimestamps();
        callback_name_ = std::string("");
        callback_audit_entries_.reset();
        HostMgr::create();
    }

    /// @brief Destructor.
    virtual ~CBControlDHCPTest() {
        // Unregister the factory to be tidy.
        ConfigBackendDHCPv4Mgr::instance().unregisterBackendFactory("memfile");
        CfgMgr::instance().clear();
        // Unregister hooks.
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("cb4_updated");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts("cb6_updated");
        bool status = HooksManager::unloadLibraries();
        if (!status) {
            std::cerr << "(fixture dtor) unloadLibraries failed" << std::endl;
        }
        HostDataSourceFactory::deregisterFactory("test");
    }

    /// @brief Creates new CREATE audit entry.
    ///
    /// The audit entry is added to the @c audit_entries_ collection.
    ///
    /// @param object_type Object type to be associated with the audit
    /// entry.
    /// @param object_id Identifier of the object to be associated with
    /// the audit entry.
    void addCreateAuditEntry(const std::string& object_type,
                             const uint64_t object_id) {
        AuditEntryPtr entry(new AuditEntry(object_type, object_id,
                                           AuditEntry::ModificationType::CREATE,
                                           ++modification_id_,
                                           "some log message"));
        audit_entries_.insert(entry);
    }

    /// @brief Creates new DELETE audit entry.
    ///
    /// The audit entry is added to the @c audit_entries_ collection.
    ///
    /// @param object_type Object type to be associated with the audit
    /// entry.
    /// @param object_id Identifier of the object to be associated with
    /// the audit entry.
    void addDeleteAuditEntry(const std::string& object_type,
                             const uint64_t object_id) {
        AuditEntryPtr entry(new AuditEntry(object_type, object_id,
                                           AuditEntry::ModificationType::DELETE,
                                           ++modification_id_,
                                           "some log message"));
        audit_entries_.insert(entry);
    }

    /// @brief Initializes timestamps used in tests.
    void initTimestamps() {
        // Get the current timestamp and move it 30 seconds backwards.
        auto now = boost::posix_time::second_clock::local_time() -
            boost::posix_time::seconds(30);

        // Initialize multiple timestamps from the base timestamp. The
        // values with indexes [-5, 0] are in the past. The remaining
        // four are in the future.
        for (int i = -5; i < 5; ++i) {
            timestamp_[i] = now + boost::posix_time::minutes(i);
        }
    }

    /// @brief Returns timestamp associated with a given index.
    ///
    /// @param timestamp_index Index of the timestamp to be returned.
    boost::posix_time::ptime getTimestamp(const int timestamp_index) {
        return (timestamp_[timestamp_index]);
    }

    /// @brief Returns timestamp to be associated with a given object type.
    ///
    /// The object types correspond to the names of the SQL tables holding
    /// them, e.g. dhcp4_global_parameter, dhcp4_subnet etc.
    ///
    /// @param object_type Object type.
    boost::posix_time::ptime getTimestamp(const std::string& object_type) {
        return (object_timestamp_[object_type]);
    }

    /// @brief Associates object type with a timestamp.
    ///
    /// When adding objects to the database, each one is associated with
    /// a modification time value. This value is setup by unit tests
    /// via this method.
    void setTimestamp(const std::string& object_type, const int timestamp_index) {
        object_timestamp_[object_type] = timestamp_[timestamp_index];
    }

    /// @brief Sets timestamps for various object types to the same value.
    ///
    /// @param timestamp_index Index of the timestamp to be set.
    virtual void setAllTimestamps(const int timestamp_index) = 0;

    /// @brief Checks if @c databaseConfigApply should fetch updates for specified
    /// object types.
    ///
    /// @param object_type Object type.
    bool hasConfigElement(const std::string& object_type) const {
        if (!audit_entries_.empty()) {
            const auto& index = audit_entries_.get<AuditEntryObjectTypeTag>();
            auto range = index.equal_range(object_type);
            for (auto it = range.first; it != range.second; ++it) {
                if (((*it)->getModificationType() != AuditEntry::ModificationType::DELETE)) {
                    return (true);
                }
            }
            return (false);
        }

        return (true);
    }

    /// @brief Check if @c databaseConfigApply should delete a given object from the
    /// local configuration.
    ///
    /// @param object_type Object type.
    /// @param object_id Object identifier.
    bool deleteConfigElement(const std::string& object_type,
                             const uint64_t object_id) const {
        if (!audit_entries_.empty()) {
            const auto& index = audit_entries_.get<AuditEntryObjectTypeTag>();
            auto range = index.equal_range(boost::make_tuple(object_type,
                                                             AuditEntry::ModificationType::DELETE));
            for (auto it = range.first; it != range.second; ++it) {
                if ((*it)->getObjectId() == object_id) {
                    return (true);
                }
            }
        }
        return (false);
    }

    /// @brief Callback that stores received callout name and received value.
    ///
    /// @param callout_handle Callout handle.
    static int
    cb4_updated_callout(CalloutHandle& callout_handle) {
        callback_name_ = std::string("cb4_updated");
        callout_handle.getArgument("audit_entries", callback_audit_entries_);
        return (0);
    }

    /// @brief Callback that stores received callout name and received value.
    ///
    /// @param callout_handle Callout handle.
    static int
    cb6_updated_callout(CalloutHandle& callout_handle) {
        callback_name_ = std::string("cb6_updated");
        callout_handle.getArgument("audit_entries", callback_audit_entries_);
        return (0);
    }

    /// @brief Holds test timestamps.
    std::map<int, boost::posix_time::ptime> timestamp_;

    /// @brief Holds mapping of the objects types to their timestamps.
    std::map<std::string, boost::posix_time::ptime> object_timestamp_;

    /// @brief Collection of audit entries used in the unit tests.
    AuditEntryCollection audit_entries_;

    /// @brief Modification id counter.
    uint64_t modification_id_;

    /// @brief Callback name.
    static std::string callback_name_;

    /// @brief Callback value.
    static AuditEntryCollectionPtr callback_audit_entries_;
};

std::string CBControlDHCPTest::callback_name_;
AuditEntryCollectionPtr CBControlDHCPTest::callback_audit_entries_;

// ************************ V4 tests *********************

/// @brief Naked @c CBControlDHCPv4 class exposing protected methods.
class TestCBControlDHCPv4 : public CBControlDHCPv4 {
public:
    /// @brief Constructor.
    TestCBControlDHCPv4() {
        CfgMgr::instance().setFamily(AF_INET);
    }

    using CBControlDHCPv4::getInitialAuditRevisionTime;
    using CBControlDHCPv4::databaseConfigApply;
};

/// @brief Test fixture class for @c CBControlDHCPv4 unit tests.
class CBControlDHCPv4Test : public CBControlDHCPTest {
public:

    /// @brief Constructor.
    CBControlDHCPv4Test()
        : CBControlDHCPTest(), ctl_() {
        ConfigBackendDHCPv4Mgr::instance().registerBackendFactory("memfile",
            [](const DatabaseConnection::ParameterMap& params)
                -> ConfigBackendDHCPv4Ptr {
                    return (TestConfigBackendDHCPv4Ptr(new TestConfigBackendDHCPv4(params)));
             });
        ConfigBackendDHCPv4Mgr::instance().addBackend("type=memfile");

        // By default, set timestamps for all object types to -4. That leaves
        // us with the possibility to use index -5 (earlier) to use as lower
        // bound modification time so as all objects are fetched.
        setAllTimestamps(-4);
    }

    /// @brief Sets timestamps of all DHCPv4 specific object types.
    ///
    /// @param timestamp_index Index of the timestamp to be set.
    virtual void setAllTimestamps(const int timestamp_index) {
        setTimestamp("dhcp4_global_parameter", timestamp_index);
        setTimestamp("dhcp4_option_def", timestamp_index);
        setTimestamp("dhcp4_options", timestamp_index);
        setTimestamp("dhcp4_shared_network", timestamp_index);
        setTimestamp("dhcp4_subnet", timestamp_index);
        setTimestamp("dhcp4_client_class", timestamp_index);
    }

    /// @brief Creates test server configuration and stores it in a test
    /// configuration backend.
    ///
    /// There are pairs of configuration elements stored in the database.
    /// For example: two global parameters, two option definitions etc.
    /// Having two elements of each type in the database is useful in tests
    /// which verify that an element is deleted from the local configuration
    /// as a result of being deleted from the configuration backend. In that
    /// case the test verifies that one of the elements of the given type
    /// is deleted and one is left.
    void remoteStoreTestConfiguration() {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        // Insert global parameters into a database.
        StampedValuePtr global_parameter = StampedValue::create("comment", "bar");
        global_parameter->setModificationTime(getTimestamp("dhcp4_global_parameter"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter4(BackendSelector::UNSPEC(),
                                                                    ServerSelector::ALL(),
                                                                    global_parameter));

        global_parameter = StampedValue::create("next-server", "teta");
        global_parameter->setModificationTime(getTimestamp("dhcp4_global_parameter"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter4(BackendSelector::UNSPEC(),
                                                                    ServerSelector::ALL(),
                                                                    global_parameter));

        // Insert option definitions into the database.
        OptionDefinitionPtr def(new OptionDefinition("one", 101, "isc", "uint16"));
        def->setId(1);
        def->setModificationTime(getTimestamp("dhcp4_option_def"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateOptionDef4(BackendSelector::UNSPEC(),
                                                              ServerSelector::ALL(),
                                                              def));
        def.reset(new OptionDefinition("two", 102, "isc", "uint16"));
        def->setId(2);
        def->setModificationTime(getTimestamp("dhcp4_option_def"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateOptionDef4(BackendSelector::UNSPEC(),
                                                              ServerSelector::ALL(),
                                                              def));

        // Insert global options into the database.
        OptionDescriptorPtr opt(new OptionDescriptor(createOption<OptionString>
                                                     (Option::V4, DHO_HOST_NAME,
                                                      true, false, false,
                                                      "new.example.com")));
        opt->setId(1);
        opt->space_name_ = DHCP4_OPTION_SPACE;
        opt->setModificationTime(getTimestamp("dhcp4_options"));
        mgr.getPool()->createUpdateOption4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           opt);

        opt.reset(new OptionDescriptor(createOption<OptionString>
                                       (Option::V4, DHO_TFTP_SERVER_NAME,
                                        true, false, false, "tftp-my")));
        opt->setId(2);
        opt->space_name_ = DHCP4_OPTION_SPACE;
        opt->setModificationTime(getTimestamp("dhcp4_options"));
        mgr.getPool()->createUpdateOption4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           opt);

        // Insert shared networks into the database.
        SharedNetwork4Ptr network(new SharedNetwork4("one"));
        network->setId(1);
        network->setModificationTime(getTimestamp("dhcp4_shared_network"));
        mgr.getPool()->createUpdateSharedNetwork4(BackendSelector::UNSPEC(),
                                                  ServerSelector::ALL(),
                                                  network);

        network.reset(new SharedNetwork4("two"));
        network->setId(2);
        network->setModificationTime(getTimestamp("dhcp4_shared_network"));
        mgr.getPool()->createUpdateSharedNetwork4(BackendSelector::UNSPEC(),
                                                  ServerSelector::ALL(),
                                                  network);

        // Insert subnets into the database.
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.3.0"), 26, 1, 2, 3, SubnetID(1)));
        subnet->setModificationTime(getTimestamp("dhcp4_subnet"));
        subnet->setSharedNetworkName("one");
        mgr.getPool()->createUpdateSubnet4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.4.0"), 26, 1, 2, 3, SubnetID(2)));
        subnet->setModificationTime(getTimestamp("dhcp4_subnet"));
        mgr.getPool()->createUpdateSubnet4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           subnet);

        // Insert client classes into the database.
        auto expression = boost::make_shared<Expression>();
        ClientClassDefPtr client_class = boost::make_shared<ClientClassDef>("first-class", expression);
        client_class->setTest("substring(option[1].hex, 0, 8) == 'my-value'");
        client_class->setId(1);
        client_class->setModificationTime(getTimestamp("dhcp4_client_class"));

        // Add a standard option to the class.
        OptionPtr option = Option::create(Option::V4, DHO_BOOT_FILE_NAME);
        OptionDescriptorPtr desc = OptionDescriptor::create(option,
                                                            true,
                                                            false,
                                                            "bogus-file.txt");
        desc->space_name_ = DHCP4_OPTION_SPACE;
        desc->setModificationTime(getTimestamp("dhcp4_client_class"));
        client_class->getCfgOption()->add(*desc, desc->space_name_);

        // Add a custom option definition to the class.
        CfgOptionDefPtr cc_cfg_option_def(new CfgOptionDef());
        def.reset(new OptionDefinition("v4str", 201, "isc", "string"));
        def->setId(201);
        def->setModificationTime(getTimestamp("dhcp4_client_class"));
        cc_cfg_option_def->add(def);
        client_class->setCfgOptionDef(cc_cfg_option_def);

        // Add a custom option to the class.
        option = Option::create(Option::V4, 201);
        desc = OptionDescriptor::create(option, true, false, "custom-stuff");
        desc->space_name_ = "isc";
        desc->setModificationTime(getTimestamp("dhcp4_client_class"));
        client_class->getCfgOption()->add(*desc, desc->space_name_);

        mgr.getPool()->createUpdateClientClass4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                                client_class, "");

        client_class = boost::make_shared<ClientClassDef>("second-class", expression);
        client_class->setId(2);
        client_class->setModificationTime(getTimestamp("dhcp4_client_class"));
        mgr.getPool()->createUpdateClientClass4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                                client_class, "");
    }

    /// @brief Deletes specified global parameter from the configuration
    /// backend and generates audit entry.
    ///
    /// Note that the current Kea implementation does not track database
    /// identifiers of the global parameters. Therefore, the identifier to
    /// be used to create the audit entry for the deleted parameter must
    /// be explicitly specified.
    ///
    /// @param parameter_name Parameter name.
    /// @param id Parameter id.
    void remoteDeleteGlobalParameter(const std::string& parameter_name,
                                     const uint64_t id) {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();
        mgr.getPool()->deleteGlobalParameter4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                             parameter_name);
        addDeleteAuditEntry("dhcp4_global_parameter", id);
    }

    /// @brief Deletes specified option definition from the configuration
    /// backend and generates audit entry.
    ///
    /// @param code Option code.
    /// @param space Option space.
    void remoteDeleteOptionDef(const uint16_t code, const std::string& space) {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        auto option_def = mgr.getPool()->getOptionDef4(BackendSelector::UNSPEC(),
                                                       ServerSelector::ALL(),
                                                       code, space);

        if (option_def) {
            mgr.getPool()->deleteOptionDef4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                            code, space);
            addDeleteAuditEntry("dhcp4_option_def", option_def->getId());
        }
    }

    /// @brief Deletes specified global option from the configuration backend
    /// and generates audit entry.
    ///
    /// @param code Option code.
    /// @param space Option space.
    void remoteDeleteOption(const uint16_t code, const std::string& space) {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        auto option = mgr.getPool()->getOption4(BackendSelector::UNSPEC(),
                                                ServerSelector::ALL(),
                                                code, space);

        if (option) {
            mgr.getPool()->deleteOptionDef4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                            code, space);
            addDeleteAuditEntry("dhcp4_option_def", option->getId());
        }
    }

    /// @brief Deletes specified shared network from the configuration backend
    /// and generates audit entry.
    ///
    /// @param name Name of the shared network to be deleted.
    void remoteDeleteSharedNetwork(const std::string& name) {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        auto network = mgr.getPool()->getSharedNetwork4(BackendSelector::UNSPEC(),
                                                        ServerSelector::ALL(),
                                                        name);

        if (network) {
            mgr.getPool()->deleteSharedNetwork4(BackendSelector::UNSPEC(),
                                                ServerSelector::ALL(),
                                                name);
            addDeleteAuditEntry("dhcp4_shared_network", network->getId());
        }
    }

    /// @brief Deletes specified subnet from the configuration backend and
    /// generates audit entry.
    void remoteDeleteSubnet(const SubnetID& id) {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        mgr.getPool()->deleteSubnet4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                     id);
        addDeleteAuditEntry("dhcp4_subnet", id);
    }

    /// @brief Deletes specified client class from the configuration backend
    /// and generates audit entry.
    ///
    /// @param name Name of the client class to be deleted.
    void remoteDeleteClientClass(const std::string& name) {
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        auto client_class = mgr.getPool()->getClientClass4(BackendSelector::UNSPEC(),
                                                           ServerSelector::ALL(),
                                                           name);

        if (client_class) {
            mgr.getPool()->deleteClientClass4(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              name);
            addDeleteAuditEntry("dhcp4_client_class", client_class->getId());
        }
    }

    /// @brief Tests the @c CBControlDHCPv4::databaseConfigApply method.
    ///
    /// This test inserts configuration elements of each type into the
    /// configuration database. Next, it calls the @c databaseConfigApply,
    /// which should merge each object from the database for which the
    /// CREATE or UPDATE audit entry is found. The test then verifies
    /// if the appropriate entries have been merged.
    ///
    /// @param lb_modification_time Lower bound modification time to be
    /// passed to the @c databaseConfigApply.
    void testDatabaseConfigApply(const boost::posix_time::ptime& lb_modification_time) {
        remoteStoreTestConfiguration();

        ASSERT_FALSE(audit_entries_.empty())
            << "Require at least one audit entry. The test is broken!";

        ASSERT_NO_THROW_LOG(ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                            lb_modification_time, audit_entries_));

        // The updates should have been merged into current configuration.
        auto srv_cfg = CfgMgr::instance().getCurrentCfg();

        // If there is an audit entry for global parameter and the parameter
        // modification time is later than last audit revision time it should
        // be merged.
        if (hasConfigElement("dhcp4_global_parameter") &&
            (getTimestamp("dhcp4_global_parameter") > lb_modification_time)) {
            checkConfiguredGlobal(srv_cfg, "comment", Element::create("bar"));

        } else {
            // Otherwise it shouldn't exist.
            EXPECT_FALSE(srv_cfg->getConfiguredGlobals()->get("comment"));
        }

        // If there is an audit entry for option definition and the definition
        // modification time is later than last audit revision time it should
        // be merged.
        auto found_def = srv_cfg->getCfgOptionDef()->get("isc", "one");
        if (hasConfigElement("dhcp4_option_def") &&
            getTimestamp("dhcp4_option_def") > lb_modification_time) {
            ASSERT_TRUE(found_def);
            EXPECT_EQ(101, found_def->getCode());
            EXPECT_EQ(OptionDataType::OPT_UINT16_TYPE, found_def->getType());

        } else {
            EXPECT_FALSE(found_def);
        }

        // If there is an audit entry for an option and the option
        // modification time is later than last audit revision time it should
        // be merged.
        auto options = srv_cfg->getCfgOption();
        auto found_opt = options->get(DHCP4_OPTION_SPACE, DHO_HOST_NAME);
        if (hasConfigElement("dhcp4_options") &&
            (getTimestamp("dhcp4_options") > lb_modification_time)) {
            ASSERT_TRUE(found_opt.option_);
            EXPECT_EQ("new.example.com", found_opt.option_->toString());

        } else {
            EXPECT_FALSE(found_opt.option_);
        }

        // If there is an audit entry for a shared network and the network
        // modification time is later than last audit revision time it should
        // be merged.
        auto networks = srv_cfg->getCfgSharedNetworks4();
        auto found_network = networks->getByName("one");
        if (hasConfigElement("dhcp4_shared_network") &&
            (getTimestamp("dhcp4_shared_network") > lb_modification_time)) {
            ASSERT_TRUE(found_network);
            EXPECT_TRUE(found_network->hasFetchGlobalsFn());

        } else {
            EXPECT_FALSE(found_network);
        }

        // If there is an audit entry for a subnet and the subnet modification
        // time is later than last audit revision time it should be merged.
        auto subnets = srv_cfg->getCfgSubnets4();
        auto found_subnet = subnets->getBySubnetId(1);
        if (hasConfigElement("dhcp4_subnet") &&
            (getTimestamp("dhcp4_subnet") > lb_modification_time)) {
            ASSERT_TRUE(found_subnet);
            EXPECT_TRUE(found_subnet->hasFetchGlobalsFn());

        } else {
            EXPECT_FALSE(found_subnet);
        }

        auto client_classes = srv_cfg->getClientClassDictionary();
        auto found_class = client_classes->findClass("first-class");
        if (hasConfigElement("dhcp4_client_class") &&
            (getTimestamp("dhcp4_client_class") > lb_modification_time)) {
            ASSERT_TRUE(found_class);
            ASSERT_TRUE(found_class->getMatchExpr());
            EXPECT_GT(found_class->getMatchExpr()->size(), 0);
            EXPECT_EQ("first-class", found_class->getName());

            // Check for the standard class option, make sure it has been "created".
            auto cfg_option_desc = found_class->getCfgOption();
            ASSERT_TRUE(cfg_option_desc);
            auto option_desc = cfg_option_desc->get(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
            auto option = option_desc.option_;
            ASSERT_TRUE(option);
            EXPECT_EQ(OptionBuffer(option_desc.formatted_value_.begin(),
                                   option_desc.formatted_value_.end()),
                      option->getData());

            // Check for the custom class option, make sure it has been "created".
            option_desc = cfg_option_desc->get("isc", 201);
            option = option_desc.option_;
            ASSERT_TRUE(option);
            EXPECT_EQ(OptionBuffer(option_desc.formatted_value_.begin(),
                                   option_desc.formatted_value_.end()),
                      option->getData());
        } else {
            EXPECT_FALSE(found_class);
        }
    }

    /// @brief Tests deletion of the configuration elements by the
    /// @c CBControlDHCPv4::databaseConfigApply method.
    ///
    /// This test inserts configuration elements of each type into the
    /// configuration database and calls the @c databaseConfigApply
    /// to fetch this configuration and merge into the local server
    /// configuration.
    ///
    /// Next, the test calls the specified callback function, i.e.
    /// @c db_modifications, which deletes selected configuration
    /// elements from the database and generates appropriate audit
    /// entries. Finally, it calls the @c databaseConfigApply again
    /// to process the audit entries and checks if the appropriate
    /// configuration elements are deleted from the local configuration
    ///
    /// @param lb_modification_time Lower bound modification time to be
    /// passed to the @c databaseConfigApply.
    /// @param db_modifications Pointer to the callback function which
    /// applies test specific modifications into the database.
    void testDatabaseConfigApplyDelete(const boost::posix_time::ptime& lb_modification_time,
                                       std::function<void()> db_modifications) {
        // Store initial configuration into the database.
        remoteStoreTestConfiguration();

        // Since we pass an empty audit collection the server treats this
        // as if the server is starting up and fetches the entire
        // configuration from the database.
        ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                 ctl_.getInitialAuditRevisionTime(),
                                 AuditEntryCollection());
        // Commit the configuration so as it is moved from the staging
        // to current.
        CfgMgr::instance().commit();

        // Run user defined callback which should delete selected configuration
        // elements from the configuration backend. The appropriate DELETE
        // audit entries should now be stored in the audit_entries_ collection.
        if (db_modifications) {
            db_modifications();
        }

        // Process the DELETE audit entries.
        ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                 lb_modification_time, audit_entries_);

        // All changes should have been applied in the current configuration.
        auto srv_cfg = CfgMgr::instance().getCurrentCfg();

        {
            SCOPED_TRACE("global parameters");
            // One of the global parameters should still be there.
            EXPECT_TRUE(srv_cfg->getConfiguredGlobals()->get("next-server"));
            if (deleteConfigElement("dhcp4_global_parameter", 1)) {
                EXPECT_FALSE(srv_cfg->getConfiguredGlobals()->get("comment"));

            } else {
                EXPECT_TRUE(srv_cfg->getConfiguredGlobals()->get("next-server"));
            }
        }

        {
            SCOPED_TRACE("option definitions");
            // One of the option definitions should still be there.
            EXPECT_TRUE(srv_cfg->getCfgOptionDef()->get("isc", "two"));
            auto found_def = srv_cfg->getCfgOptionDef()->get("isc", "one");
            if (deleteConfigElement("dhcp4_option_def", 1)) {
                EXPECT_FALSE(found_def);

            } else {
                EXPECT_TRUE(found_def);
            }
        }

        {
            SCOPED_TRACE("global options");
            // One of the options should still be there.
            EXPECT_TRUE(srv_cfg->getCfgOption()->get(DHCP4_OPTION_SPACE,
                                                     DHO_TFTP_SERVER_NAME).option_);
            auto found_opt = srv_cfg->getCfgOption()->get(DHCP4_OPTION_SPACE,
                                                          DHO_HOST_NAME);
            if (deleteConfigElement("dhcp4_options", 1)) {
                EXPECT_FALSE(found_opt.option_);

            } else {
                EXPECT_TRUE(found_opt.option_);
            }
        }

        {
            SCOPED_TRACE("shared networks");
            // One of the shared networks should still be there.
            EXPECT_TRUE(srv_cfg->getCfgSharedNetworks4()->getByName("two"));
            auto found_network = srv_cfg->getCfgSharedNetworks4()->getByName("one");
            if (deleteConfigElement("dhcp4_shared_network", 1)) {
                EXPECT_FALSE(found_network);

            } else {
                EXPECT_TRUE(found_network);
            }
        }

        {
            SCOPED_TRACE("subnets");
            // One of the subnets should still be there.
            EXPECT_TRUE(srv_cfg->getCfgSubnets4()->getBySubnetId(2));
            auto found_subnet = srv_cfg->getCfgSubnets4()->getBySubnetId(1);
            if (deleteConfigElement("dhcp4_subnet", 1)) {
                EXPECT_FALSE(found_subnet);

                // If the subnet has been deleted, make sure that
                // it was detached from the shared network it belonged
                // to, if the shared network still exists.
                auto found_network = srv_cfg->getCfgSharedNetworks4()->getByName("one");
                if (found_network) {
                    EXPECT_TRUE(found_network->getAllSubnets()->empty());
                }

            } else {
                EXPECT_TRUE(found_subnet);
            }
        }

        {
            SCOPED_TRACE("client classes");
            // One of the subnets should still be there.
            EXPECT_TRUE(srv_cfg->getClientClassDictionary()->findClass("second-class"));
            auto found_client_class = srv_cfg->getClientClassDictionary()->findClass("first-class");
            if (deleteConfigElement("dhcp4_client_class", 1)) {
                EXPECT_FALSE(found_client_class);

            } else {
                EXPECT_TRUE(found_client_class);
            }
        }
    }

    /// @brief Instance of the @c CBControlDHCPv4 used for testing.
    TestCBControlDHCPv4 ctl_;
};


// This test verifies that the configuration updates for all object
// types are merged into the current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyAll) {

    addCreateAuditEntry("dhcp4_global_parameter", 1);
    addCreateAuditEntry("dhcp4_global_parameter", 2);
    addCreateAuditEntry("dhcp4_option_def", 1);
    addCreateAuditEntry("dhcp4_option_def", 2);
    addCreateAuditEntry("dhcp4_options", 1);
    addCreateAuditEntry("dhcp4_options", 2);
    addCreateAuditEntry("dhcp4_shared_network", 1);
    addCreateAuditEntry("dhcp4_shared_network", 2);
    addCreateAuditEntry("dhcp4_subnet", 1);
    addCreateAuditEntry("dhcp4_subnet", 2);
    addCreateAuditEntry("dhcp4_client_class", 1);
    addCreateAuditEntry("dhcp4_client_class", 2);

    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that multiple configuration elements are
// deleted from the local configuration as a result of being
// deleted from the database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteAll) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteGlobalParameter("comment", 1);
        remoteDeleteOptionDef(101, "isc");
        remoteDeleteOption(DHO_HOST_NAME, DHCP4_OPTION_SPACE);
        remoteDeleteSharedNetwork("one");
        remoteDeleteSubnet(SubnetID(1));
        remoteDeleteClientClass("first-class");
    });
}

// This test verifies that an attempt to delete non-existing
// configuration element does not cause an error.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteNonExisting) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        // Add several audit entries instructing to delete the
        // non-existing configuration elements. The ids are set
        // to 3, but the only existing elements have ids of 1
        // and 2.
        addDeleteAuditEntry("dhcp4_global_parameter", 3);
        addDeleteAuditEntry("dhcp4_option_def", 3);
        addDeleteAuditEntry("dhcp4_options", 3);
        addDeleteAuditEntry("dhcp4_shared_network", 3);
        addDeleteAuditEntry("dhcp4_subnet", 3);
        addDeleteAuditEntry("dhcp4_client_class", 3);
    });
}

// This test verifies that only a global parameter is merged into
// the current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyGlobal) {
    addCreateAuditEntry("dhcp4_global_parameter", 1);
    addCreateAuditEntry("dhcp4_global_parameter", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the global parameter is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteGlobal) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteGlobalParameter("comment", 1);
    });
}

// This test verifies that global parameter is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyGlobalNotFetched) {
    addCreateAuditEntry("dhcp4_global_parameter", 1);
    addCreateAuditEntry("dhcp4_global_parameter", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only an option definition is merged into
// the current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOptionDef) {
    addCreateAuditEntry("dhcp4_option_def", 1);
    addCreateAuditEntry("dhcp4_option_def", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the option definition is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteOptionDef) {
    addDeleteAuditEntry("dhcp4_option_def", 1);
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteOptionDef(101, "isc");
    });
}

// This test verifies that option definition is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOptionDefNotFetched) {
    addCreateAuditEntry("dhcp4_option_def", 1);
    addCreateAuditEntry("dhcp4_option_def", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a DHCPv4 option is merged into the
// current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOption) {
    addCreateAuditEntry("dhcp4_options", 1);
    addCreateAuditEntry("dhcp4_options", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the global option is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteOption) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteOption(DHO_HOST_NAME, DHCP4_OPTION_SPACE);
    });
}

// This test verifies that DHCPv4 option is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOptionNotFetched) {
    addCreateAuditEntry("dhcp4_options", 1);
    addCreateAuditEntry("dhcp4_options", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a shared network is merged into the
// current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySharedNetwork) {
    addCreateAuditEntry("dhcp4_shared_network", 1);
    addCreateAuditEntry("dhcp4_shared_network", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the shared network is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteSharedNetwork) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteSharedNetwork("one");
    });
}

// This test verifies that shared network is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySharedNetworkNotFetched) {
    addCreateAuditEntry("dhcp4_shared_network", 1);
    addCreateAuditEntry("dhcp4_shared_network", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a subnet is merged into the current
// configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySubnet) {
    addCreateAuditEntry("dhcp4_shared_network", 1);
    addCreateAuditEntry("dhcp4_shared_network", 2);
    addCreateAuditEntry("dhcp4_subnet", 1);
    addCreateAuditEntry("dhcp4_subnet", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the subnet is deleted from the local
// configuration as a result of being deleted from the database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteSubnet) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteSubnet(SubnetID(1));
    });
}

// This test verifies that subnet is not fetched from the database
// when the modification time is earlier than the last fetched audit
// entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySubnetNotFetched) {
    addCreateAuditEntry("dhcp4_subnet", 1);
    addCreateAuditEntry("dhcp4_subnet", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only client classes are merged into the current
// configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyClientClasses) {
    addCreateAuditEntry("dhcp4_client_class", 1);
    addCreateAuditEntry("dhcp4_client_class", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that a client class is deleted from the local
// configuration as a result of being deleted from the database.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyDeleteClientClass) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteClientClass("first-class");
    });
}

// This test verifies that the configuration update calls the hook.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyHook) {

    // Initialize Hooks Manager.
    HooksManager::loadLibraries(HookLibsCollection());

    // Install cb4_updated.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "cb4_updated", cb4_updated_callout));

    // Create audit entries.
    addCreateAuditEntry("dhcp4_global_parameter", 1);
    addCreateAuditEntry("dhcp4_global_parameter", 2);
    addCreateAuditEntry("dhcp4_option_def", 1);
    addCreateAuditEntry("dhcp4_option_def", 2);
    addCreateAuditEntry("dhcp4_options", 1);
    addCreateAuditEntry("dhcp4_options", 2);
    addCreateAuditEntry("dhcp4_shared_network", 1);
    addCreateAuditEntry("dhcp4_shared_network", 2);
    addCreateAuditEntry("dhcp4_subnet", 1);
    addCreateAuditEntry("dhcp4_subnet", 2);

    // Run the test.
    testDatabaseConfigApply(getTimestamp(-5));

    // Checks the callout.
    EXPECT_EQ("cb4_updated", callback_name_);
    ASSERT_TRUE(callback_audit_entries_);
    EXPECT_TRUE(audit_entries_ == *callback_audit_entries_);
}

// This test verifies that it is possible to set ip-reservations-unique
// parameter via configuration backend and that it is successful when
// host database backend accepts the new setting.
TEST_F(CBControlDHCPv4Test, ipReservationsNonUniqueAccepted) {
    // Create host data source which accepts setting non-unique IP
    // reservations.
    MemHostDataSourcePtr hds(new MemHostDataSource());
    auto testFactory = [hds](const DatabaseConnection::ParameterMap&) {
        return (hds);
    };
    HostDataSourceFactory::registerFactory("test", testFactory);
    HostMgr::addBackend("type=test");

    // Insert ip-reservations-unique value set to false into the database.
    auto& mgr = ConfigBackendDHCPv4Mgr::instance();
    StampedValuePtr global_parameter = StampedValue::create("ip-reservations-unique",
                                                            Element::create(false));
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter4(BackendSelector::UNSPEC(),
                                                                ServerSelector::ALL(),
                                                                global_parameter));
    // Adding audit entry simulates the case when the server is already configured
    // and we're adding incremental changes. These changes should be applied to
    // the current configuration.
    addCreateAuditEntry("dhcp4_global_parameter", 1);

    // Apply the configuration.
    ASSERT_NO_THROW(ctl_.databaseConfigApply(BackendSelector::UNSPEC(),
                                             ServerSelector::ALL(),
                                             getTimestamp(-5),
                                             audit_entries_));
    // The new setting should be visible in both CfgDbAccess and HostMgr.
    EXPECT_FALSE(CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->getIPReservationsUnique());
    EXPECT_FALSE(HostMgr::instance().getIPReservationsUnique());
}

// This test verifies that the new setting of ip-reservations-unique is not
// accepted when one of the host database backends does not support it.
TEST_F(CBControlDHCPv4Test, ipReservationsNonUniqueRefused) {
    // Create host data source which does not accept setting IP reservations
    // non-unique setting.
    NonUniqueHostDataSourcePtr hds(new NonUniqueHostDataSource());
    auto testFactory = [hds](const DatabaseConnection::ParameterMap&) {
        return (hds);
    };
    HostDataSourceFactory::registerFactory("test", testFactory);
    HostMgr::addBackend("type=test");

    // Insert ip-reservations-unique value set to false into the database.
    auto& mgr = ConfigBackendDHCPv4Mgr::instance();
    StampedValuePtr global_parameter = StampedValue::create("ip-reservations-unique",
                                                            Element::create(false));
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter4(BackendSelector::UNSPEC(),
                                                                ServerSelector::ALL(),
                                                                global_parameter));
    // Adding audit entry simulates the case when the server is already configured
    // and we're adding incremental changes. These changes should be applied to
    // the current configuration.
    addCreateAuditEntry("dhcp4_global_parameter", 1);

    // Apply the configuration.
    ASSERT_NO_THROW(ctl_.databaseConfigApply(BackendSelector::UNSPEC(),
                                             ServerSelector::ALL(),
                                             getTimestamp(-5),
                                             audit_entries_));
    // The default setting should be applied, because the backend refused to
    // set it to false.
    EXPECT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->getIPReservationsUnique());
    EXPECT_TRUE(HostMgr::instance().getIPReservationsUnique());
}

// ************************ V6 tests *********************

/// @brief Naked @c CBControlDHCPv6 class exposing protected methods.
class TestCBControlDHCPv6 : public CBControlDHCPv6 {
public:
    /// @brief Constructor.
    TestCBControlDHCPv6() {
        CfgMgr::instance().setFamily(AF_INET6);
    }

    using CBControlDHCPv6::getInitialAuditRevisionTime;
    using CBControlDHCPv6::databaseConfigApply;
};

/// @brief Test fixture class for @c CBControlDHCPv6 unit tests.
class CBControlDHCPv6Test : public CBControlDHCPTest {
public:

    /// @brief Constructor.
    CBControlDHCPv6Test()
        : CBControlDHCPTest(), ctl_() {
        ConfigBackendDHCPv6Mgr::instance().registerBackendFactory("memfile",
            [](const DatabaseConnection::ParameterMap& params)
                -> ConfigBackendDHCPv6Ptr {
                    return (TestConfigBackendDHCPv6Ptr(new TestConfigBackendDHCPv6(params)));
             });
        ConfigBackendDHCPv6Mgr::instance().addBackend("type=memfile");

        // By default, set timestamps for all object types to -4. That leaves
        // us with the possibility to use index -5 (earlier) to use as lower
        // bound modification time so as all objects are fetched.
        setAllTimestamps(-4);
    }

    /// @brief Sets timestamps of all DHCPv6 specific object types.
    ///
    /// @param timestamp_index Index of the timestamp to be set.
    virtual void setAllTimestamps(const int timestamp_index) {
        setTimestamp("dhcp6_global_parameter", timestamp_index);
        setTimestamp("dhcp6_option_def", timestamp_index);
        setTimestamp("dhcp6_options", timestamp_index);
        setTimestamp("dhcp6_shared_network", timestamp_index);
        setTimestamp("dhcp6_subnet", timestamp_index);
        setTimestamp("dhcp6_client_class", timestamp_index);
    }

    /// @brief Creates test server configuration and stores it in a test
    /// configuration backend.
    ///
    /// There are pairs of configuration elements stored in the database.
    /// For example: two global parameters, two option definitions etc.
    /// Having two elements of each type in the database is useful in tests
    /// which verify that an element is deleted from the local configuration
    /// as a result of being deleted from the configuration backend. In that
    /// case the test verifies that one of the elements of the given type
    /// is deleted and one is left.
    void remoteStoreTestConfiguration() {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();

        // Insert global parameters into a database.
        StampedValuePtr global_parameter = StampedValue::create("comment", "bar");
        global_parameter->setModificationTime(getTimestamp("dhcp6_global_parameter"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter6(BackendSelector::UNSPEC(),
                                                                    ServerSelector::ALL(),
                                                                    global_parameter));

        global_parameter = StampedValue::create("data-directory", "teta");
        global_parameter->setModificationTime(getTimestamp("dhcp6_global_parameter"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter6(BackendSelector::UNSPEC(),
                                                                    ServerSelector::ALL(),
                                                                    global_parameter));

        // Insert option definitions into the database.
        OptionDefinitionPtr def(new OptionDefinition("one", 101, "isc", "uint16"));
        def->setId(1);
        def->setModificationTime(getTimestamp("dhcp6_option_def"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateOptionDef6(BackendSelector::UNSPEC(),
                                                              ServerSelector::ALL(),
                                                              def));
        def.reset(new OptionDefinition("two", 102, "isc", "uint16"));
        def->setId(2);
        def->setModificationTime(getTimestamp("dhcp6_option_def"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateOptionDef6(BackendSelector::UNSPEC(),
                                                              ServerSelector::ALL(),
                                                              def));

        // Insert global options into the database.
        OptionDescriptorPtr opt(new OptionDescriptor(createOption<OptionString>
                                                     (Option::V6, D6O_BOOTFILE_URL,
                                                      true, false, false,
                                                      "some.bootfile")));
        opt->setId(1);
        opt->space_name_ = DHCP6_OPTION_SPACE;
        opt->setModificationTime(getTimestamp("dhcp6_options"));
        mgr.getPool()->createUpdateOption6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           opt);

        opt.reset(new OptionDescriptor(createOption<OptionString>
                                       (Option::V6, D6O_AFTR_NAME,
                                        true, true, true,
                                        "some.example.com")));
        opt->setId(2);
        opt->space_name_ = DHCP6_OPTION_SPACE;
        opt->setModificationTime(getTimestamp("dhcp6_options"));
        mgr.getPool()->createUpdateOption6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           opt);

        // Insert shared networks into the database.
        SharedNetwork6Ptr network(new SharedNetwork6("one"));
        network->setId(1);
        network->setModificationTime(getTimestamp("dhcp6_shared_network"));
        mgr.getPool()->createUpdateSharedNetwork6(BackendSelector::UNSPEC(),
                                                  ServerSelector::ALL(),
                                                  network);

        network.reset(new SharedNetwork6("two"));
        network->setId(2);
        network->setModificationTime(getTimestamp("dhcp6_shared_network"));
        mgr.getPool()->createUpdateSharedNetwork6(BackendSelector::UNSPEC(),
                                                  ServerSelector::ALL(),
                                                  network);

        // Insert subnets into the database.
        Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4, SubnetID(1)));
        subnet->setModificationTime(getTimestamp("dhcp6_subnet"));
        subnet->setSharedNetworkName("one");
        mgr.getPool()->createUpdateSubnet6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           subnet);

        subnet.reset(new Subnet6(IOAddress("2001:db8:2::"), 64, 1, 2, 3, 4, SubnetID(2)));
        subnet->setModificationTime(getTimestamp("dhcp6_subnet"));
        mgr.getPool()->createUpdateSubnet6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           subnet);

        // Insert client classes into the database.
        auto expression = boost::make_shared<Expression>();
        ClientClassDefPtr client_class = boost::make_shared<ClientClassDef>("first-class", expression);
        client_class->setTest("substring(option[1].hex, 0, 8) == 'my-value'");
        client_class->setId(1);
        client_class->setModificationTime(getTimestamp("dhcp6_client_class"));

        // Add an option to the class.
        OptionPtr option = Option::create(Option::V6, D6O_BOOTFILE_URL);
        OptionDescriptorPtr desc = OptionDescriptor::create(option, true,
                                                            false,
                                                            "client.boot.url");
        desc->space_name_ = DHCP6_OPTION_SPACE;
        desc->setModificationTime(getTimestamp("dhcp6_client_class"));
        client_class->getCfgOption()->add(*desc, desc->space_name_);

        mgr.getPool()->createUpdateClientClass6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                                client_class, "");

        client_class = boost::make_shared<ClientClassDef>("second-class", expression);
        client_class->setId(2);
        client_class->setModificationTime(getTimestamp("dhcp6_client_class"));
        mgr.getPool()->createUpdateClientClass6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                                client_class, "");
    }

    /// @brief Deletes specified global parameter from the configuration
    /// backend and generates audit entry.
    ///
    /// Note that the current Kea implementation does not track database
    /// identifiers of the global parameters. Therefore, the identifier to
    /// be used to create the audit entry for the deleted parameter must
    /// be explicitly specified.
    ///
    /// @param parameter_name Parameter name.
    /// @param id Parameter id.
    void remoteDeleteGlobalParameter(const std::string& parameter_name,
                                     const uint64_t id) {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();
        mgr.getPool()->deleteGlobalParameter6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                             parameter_name);
        addDeleteAuditEntry("dhcp6_global_parameter", id);
    }

    /// @brief Deletes specified option definition from the configuration
    /// backend and generates audit entry.
    ///
    /// @param code Option code.
    /// @param space Option space.
    void remoteDeleteOptionDef(const uint16_t code, const std::string& space) {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();

        auto option_def = mgr.getPool()->getOptionDef6(BackendSelector::UNSPEC(),
                                                       ServerSelector::ALL(),
                                                       code, space);

        if (option_def) {
            mgr.getPool()->deleteOptionDef6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                            code, space);
            addDeleteAuditEntry("dhcp6_option_def", option_def->getId());
        }
    }

    /// @brief Deletes specified global option from the configuration backend
    /// and generates audit entry.
    ///
    /// @param code Option code.
    /// @param space Option space.
    void remoteDeleteOption(const uint16_t code, const std::string& space) {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();

        auto option = mgr.getPool()->getOption6(BackendSelector::UNSPEC(),
                                                ServerSelector::ALL(),
                                                code, space);

        if (option) {
            mgr.getPool()->deleteOptionDef6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                            code, space);
            addDeleteAuditEntry("dhcp6_option_def", option->getId());
        }
    }

    /// @brief Deletes specified shared network from the configuration backend
    /// and generates audit entry.
    ///
    /// @param name Name of the shared network to be deleted.
    void remoteDeleteSharedNetwork(const std::string& name) {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();

        auto network = mgr.getPool()->getSharedNetwork6(BackendSelector::UNSPEC(),
                                                        ServerSelector::ALL(),
                                                        name);

        if (network) {
            mgr.getPool()->deleteSharedNetwork6(BackendSelector::UNSPEC(),
                                                ServerSelector::ALL(),
                                                name);
            addDeleteAuditEntry("dhcp6_shared_network", network->getId());
        }
    }

    /// @brief Deletes specified subnet from the configuration backend and
    /// generates audit entry.
    void remoteDeleteSubnet(const SubnetID& id) {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();

        mgr.getPool()->deleteSubnet6(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                     id);
        addDeleteAuditEntry("dhcp6_subnet", id);
    }

    /// @brief Deletes specified client class from the configuration backend
    /// and generates audit entry.
    ///
    /// @param name Name of the client class to be deleted.
    void remoteDeleteClientClass(const std::string& name) {
        auto& mgr = ConfigBackendDHCPv6Mgr::instance();

        auto client_class = mgr.getPool()->getClientClass6(BackendSelector::UNSPEC(),
                                                           ServerSelector::ALL(),
                                                           name);

        if (client_class) {
            mgr.getPool()->deleteClientClass6(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              name);
            addDeleteAuditEntry("dhcp6_client_class", client_class->getId());
        }
    }

    /// @brief Tests the @c CBControlDHCPv6::databaseConfigApply method.
    ///
    /// This test inserts configuration elements of each type into the
    /// configuration database. Next, it calls the @c databaseConfigApply,
    /// which should merge each object from the database for which the
    /// CREATE or UPDATE audit entry is found. The test then verifies
    /// if the appropriate entries have been merged.
    ///
    /// @param lb_modification_time Lower bound modification time to be
    /// passed to the @c databaseConfigApply.
    void testDatabaseConfigApply(const boost::posix_time::ptime& lb_modification_time) {
        remoteStoreTestConfiguration();

        ASSERT_FALSE(audit_entries_.empty())
            << "Require at least one audit entry. The test is broken!";

        ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                 lb_modification_time, audit_entries_);

        // The updates should have been merged into current configuration.
        auto srv_cfg = CfgMgr::instance().getCurrentCfg();

        // If there is an audit entry for global parameter and the parameter
        // modification time is later than last audit revision time it should
        // be merged.
        if (hasConfigElement("dhcp6_global_parameter") &&
            (getTimestamp("dhcp6_global_parameter") > lb_modification_time)) {
            checkConfiguredGlobal(srv_cfg, "comment", Element::create("bar"));

        } else {
            // Otherwise it shouldn't exist.
            EXPECT_FALSE(srv_cfg->getConfiguredGlobals()->get("comment"));
        }

        // If there is an audit entry for option definition and the definition
        // modification time is later than last audit revision time it should
        // be merged.
        auto found_def = srv_cfg->getCfgOptionDef()->get("isc", "one");
        if (hasConfigElement("dhcp6_option_def") &&
            getTimestamp("dhcp6_option_def") > lb_modification_time) {
            ASSERT_TRUE(found_def);
            EXPECT_EQ(101, found_def->getCode());
            EXPECT_EQ(OptionDataType::OPT_UINT16_TYPE, found_def->getType());

        } else {
            EXPECT_FALSE(found_def);
        }

        // If there is an audit entry for an option and the option
        // modification time is later than last audit revision time it should
        // be merged.
        auto options = srv_cfg->getCfgOption();
        auto found_opt = options->get(DHCP6_OPTION_SPACE, D6O_BOOTFILE_URL);
        if (hasConfigElement("dhcp6_options") &&
            (getTimestamp("dhcp6_options") > lb_modification_time)) {
            ASSERT_TRUE(found_opt.option_);
            EXPECT_EQ("some.bootfile", found_opt.option_->toString());

        } else {
            EXPECT_FALSE(found_opt.option_);
        }

        // If there is an audit entry for a shared network and the network
        // modification time is later than last audit revision time it should
        // be merged.
        auto networks = srv_cfg->getCfgSharedNetworks6();
        auto found_network = networks->getByName("one");
        if (hasConfigElement("dhcp6_shared_network") &&
            (getTimestamp("dhcp6_shared_network") > lb_modification_time)) {
            ASSERT_TRUE(found_network);
            EXPECT_TRUE(found_network->hasFetchGlobalsFn());

        } else {
            EXPECT_FALSE(found_network);
        }

        // If there is an audit entry for a subnet and the subnet modification
        // time is later than last audit revision time it should be merged.
        auto subnets = srv_cfg->getCfgSubnets6();
        auto found_subnet = subnets->getBySubnetId(1);
        if (hasConfigElement("dhcp6_subnet") &&
            (getTimestamp("dhcp6_subnet") > lb_modification_time)) {
            ASSERT_TRUE(found_subnet);
            EXPECT_TRUE(found_subnet->hasFetchGlobalsFn());

        } else {
            EXPECT_FALSE(found_subnet);
        }

        auto client_classes = srv_cfg->getClientClassDictionary();
        auto found_class = client_classes->findClass("first-class");
        if (hasConfigElement("dhcp6_client_class") &&
            (getTimestamp("dhcp6_client_class") > lb_modification_time)) {
            ASSERT_TRUE(found_class);
            ASSERT_TRUE(found_class->getMatchExpr());
            EXPECT_GT(found_class->getMatchExpr()->size(), 0);
            EXPECT_EQ("first-class", found_class->getName());

            // Check for class option, make sure it has been "created".
            auto cfg_option_desc = found_class->getCfgOption();
            ASSERT_TRUE(cfg_option_desc);
            auto option_desc = cfg_option_desc->get(DHCP6_OPTION_SPACE, D6O_BOOTFILE_URL);
            auto option = option_desc.option_;
            ASSERT_TRUE(option);
            EXPECT_EQ(OptionBuffer(option_desc.formatted_value_.begin(),
                                   option_desc.formatted_value_.end()),
                      option->getData());
        } else {
            EXPECT_FALSE(found_class);
        }
    }

    /// @brief Tests deletion of the configuration elements by the
    /// @c CBControlDHCPv6::databaseConfigApply method.
    ///
    /// This test inserts configuration elements of each type into the
    /// configuration database and calls the @c databaseConfigApply
    /// to fetch this configuration and merge into the local server
    /// configuration.
    ///
    /// Next, the test calls the specified callback function, i.e.
    /// @c db_modifications, which deletes selected configuration
    /// elements from the database and generates appropriate audit
    /// entries. Finally, it calls the @c databaseConfigApply again
    /// to process the audit entries and checks if the appropriate
    /// configuration elements are deleted from the local configuration
    ///
    /// @param lb_modification_time Lower bound modification time to be
    /// passed to the @c databaseConfigApply.
    /// @param db_modifications Pointer to the callback function which
    /// applies test specific modifications into the database.
    void testDatabaseConfigApplyDelete(const boost::posix_time::ptime& lb_modification_time,
                                       std::function<void()> db_modifications) {
        // Store initial configuration into the database.
        remoteStoreTestConfiguration();

        // Since we pass an empty audit collection the server treats this
        // as if the server is starting up and fetches the entire
        // configuration from the database.
        ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                 ctl_.getInitialAuditRevisionTime(),
                                 AuditEntryCollection());
        // Commit the configuration so as it is moved from the staging
        // to current.
        CfgMgr::instance().commit();

        // Run user defined callback which should delete selected configuration
        // elements from the configuration backend. The appropriate DELETE
        // audit entries should now be stored in the audit_entries_ collection.
        if (db_modifications) {
            db_modifications();
        }

        // Process the DELETE audit entries.
        ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                 lb_modification_time, audit_entries_);

        // All changes should have been applied in the current configuration.
        auto srv_cfg = CfgMgr::instance().getCurrentCfg();

        {
            SCOPED_TRACE("global parameters");
            // One of the global parameters should still be there.
            EXPECT_TRUE(srv_cfg->getConfiguredGlobals()->get("data-directory"));
            if (deleteConfigElement("dhcp6_global_parameter", 1)) {
                EXPECT_FALSE(srv_cfg->getConfiguredGlobals()->get("comment"));

            } else {
                EXPECT_TRUE(srv_cfg->getConfiguredGlobals()->get("comment"));
            }
        }

        {
            SCOPED_TRACE("option definitions");
            // One of the option definitions should still be there.
            EXPECT_TRUE(srv_cfg->getCfgOptionDef()->get("isc", "two"));
            auto found_def = srv_cfg->getCfgOptionDef()->get("isc", "one");
            if (deleteConfigElement("dhcp6_option_def", 1)) {
                EXPECT_FALSE(found_def);

            } else {
                EXPECT_TRUE(found_def);
            }
        }

        {
            SCOPED_TRACE("global options");
            // One of the options should still be there.
            EXPECT_TRUE(srv_cfg->getCfgOption()->get(DHCP6_OPTION_SPACE,
                                                     D6O_AFTR_NAME).option_);
            auto found_opt = srv_cfg->getCfgOption()->get(DHCP6_OPTION_SPACE,
                                                          D6O_AFTR_NAME);
            if (deleteConfigElement("dhcp6_options", 1)) {
                EXPECT_FALSE(found_opt.option_);

            } else {
                EXPECT_TRUE(found_opt.option_);
            }
        }

        {
            SCOPED_TRACE("shared networks");
            // One of the shared networks should still be there.
            EXPECT_TRUE(srv_cfg->getCfgSharedNetworks6()->getByName("two"));
            auto found_network = srv_cfg->getCfgSharedNetworks6()->getByName("one");
            if (deleteConfigElement("dhcp6_shared_network", 1)) {
                EXPECT_FALSE(found_network);

            } else {
                EXPECT_TRUE(found_network);
            }
        }

        {
            SCOPED_TRACE("subnets");
            // One of the subnets should still be there.
            EXPECT_TRUE(srv_cfg->getCfgSubnets6()->getBySubnetId(2));
            auto found_subnet = srv_cfg->getCfgSubnets6()->getBySubnetId(1);
            if (deleteConfigElement("dhcp6_subnet", 1)) {
                EXPECT_FALSE(found_subnet);
                // If the subnet has been deleted, make sure that
                // it was detached from the shared network it belonged
                // to, if the shared network still exists.
                auto found_network = srv_cfg->getCfgSharedNetworks6()->getByName("one");
                if (found_network) {
                    EXPECT_TRUE(found_network->getAllSubnets()->empty());
                }

            } else {
                EXPECT_TRUE(found_subnet);
            }
        }
    }

    /// @brief Instance of the @c CBControlDHCPv6 used for testing.
    TestCBControlDHCPv6 ctl_;
};


// This test verifies that the configuration updates for all object
// types are merged into the current configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyAll) {

    addCreateAuditEntry("dhcp6_global_parameter", 1);
    addCreateAuditEntry("dhcp6_global_parameter", 2);
    addCreateAuditEntry("dhcp6_option_def", 1);
    addCreateAuditEntry("dhcp6_option_def", 2);
    addCreateAuditEntry("dhcp6_options", 1);
    addCreateAuditEntry("dhcp6_options", 2);
    addCreateAuditEntry("dhcp6_shared_network", 1);
    addCreateAuditEntry("dhcp6_shared_network", 2);
    addCreateAuditEntry("dhcp6_subnet", 1);
    addCreateAuditEntry("dhcp6_subnet", 2);
    addCreateAuditEntry("dhcp6_client_class", 1);
    addCreateAuditEntry("dhcp6_client_class", 2);

    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that multiple configuration elements are
// deleted from the local configuration as a result of being
// deleted from the database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteAll) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteGlobalParameter("comment", 1);
        remoteDeleteOptionDef(101, "isc");
        remoteDeleteOption(D6O_BOOTFILE_URL, DHCP6_OPTION_SPACE);
        remoteDeleteSharedNetwork("one");
        remoteDeleteSubnet(SubnetID(1));
    });
}

// This test verifies that an attempt to delete non-existing
// configuration element does not cause an error.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteNonExisting) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        // Add several audit entries instructing to delete the
        // non-existing configuration elements. The ids are set
        // to 3, but the only existing elements have ids of 1
        // and 2.
        addDeleteAuditEntry("dhcp6_global_parameter", 3);
        addDeleteAuditEntry("dhcp6_option_def", 3);
        addDeleteAuditEntry("dhcp6_options", 3);
        addDeleteAuditEntry("dhcp6_shared_network", 3);
        addDeleteAuditEntry("dhcp6_subnet", 3);
    });
}

// This test verifies that only a global parameter is merged into
// the current configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyGlobal) {
    addCreateAuditEntry("dhcp6_global_parameter", 1);
    addCreateAuditEntry("dhcp6_global_parameter", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the global parameter is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteGlobal) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteGlobalParameter("comment", 1);
    });
}

// This test verifies that global parameter is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyGlobalNotFetched) {
    addCreateAuditEntry("dhcp6_global_parameter", 1);
    addCreateAuditEntry("dhcp6_global_parameter", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only an option definition is merged into
// the current configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyOptionDef) {
    addCreateAuditEntry("dhcp6_option_def", 1);
    addCreateAuditEntry("dhcp6_option_def", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the option definition is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteOptionDef) {
    addDeleteAuditEntry("dhcp6_option_def", 1);
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteOptionDef(101, "isc");
    });
}

// This test verifies that option definition is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyOptionDefNotFetched) {
    addCreateAuditEntry("dhcp6_option_def", 1);
    addCreateAuditEntry("dhcp6_option_def", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a DHCPv6 option is merged into the
// current configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyOption) {
    addCreateAuditEntry("dhcp6_options", 1);
    addCreateAuditEntry("dhcp6_options", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the global option is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteOption) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteOption(D6O_BOOTFILE_URL, DHCP6_OPTION_SPACE);
    });
}

// This test verifies that DHCPv6 option is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyOptionNotFetched) {
    addCreateAuditEntry("dhcp6_options", 1);
    addCreateAuditEntry("dhcp6_options", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a shared network is merged into the
// current configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplySharedNetwork) {
    addCreateAuditEntry("dhcp6_shared_network", 1);
    addCreateAuditEntry("dhcp6_shared_network", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the shared network is deleted from
// the local configuration as a result of being deleted from the
// database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteSharedNetwork) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteSharedNetwork("one");
    });
}

// This test verifies that shared network is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv6Test, databaseConfigApplySharedNetworkNotFetched) {
    addCreateAuditEntry("dhcp6_shared_network", 1);
    addCreateAuditEntry("dhcp6_shared_network", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a subnet is merged into the current
// configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplySubnet) {
    addCreateAuditEntry("dhcp6_shared_network", 1);
    addCreateAuditEntry("dhcp6_shared_network", 2);
    addCreateAuditEntry("dhcp6_subnet", 1);
    addCreateAuditEntry("dhcp6_subnet", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that the subnet is deleted from the local
// configuration as a result of being deleted from the database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteSubnet) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteSubnet(SubnetID(1));
    });
}

// This test verifies that subnet is not fetched from the database
// when the modification time is earlier than the last fetched audit
// entry.
TEST_F(CBControlDHCPv6Test, databaseConfigApplySubnetNotFetched) {
    addCreateAuditEntry("dhcp6_subnet", 1);
    addCreateAuditEntry("dhcp6_subnet", 2);
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only client classes are merged into the current
// configuration.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyClientClasses) {
    addCreateAuditEntry("dhcp6_client_class", 1);
    addCreateAuditEntry("dhcp6_client_class", 2);
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that a client class is deleted from the local
// configuration as a result of being deleted from the database.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyDeleteClientClass) {
    testDatabaseConfigApplyDelete(getTimestamp(-5), [this]() {
        remoteDeleteClientClass("first-class");
    });
}

// This test verifies that the configuration update calls the hook.
TEST_F(CBControlDHCPv6Test, databaseConfigApplyHook) {

    // Initialize Hooks Manager.
    HooksManager::loadLibraries(HookLibsCollection());

    // Install cb6_updated.
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
        "cb6_updated", cb6_updated_callout));

    // Create audit entries.
    addCreateAuditEntry("dhcp6_global_parameter", 1);
    addCreateAuditEntry("dhcp6_global_parameter", 2);
    addCreateAuditEntry("dhcp6_option_def", 1);
    addCreateAuditEntry("dhcp6_option_def", 2);
    addCreateAuditEntry("dhcp6_options", 1);
    addCreateAuditEntry("dhcp6_options", 2);
    addCreateAuditEntry("dhcp6_shared_network", 1);
    addCreateAuditEntry("dhcp6_shared_network", 2);
    addCreateAuditEntry("dhcp6_subnet", 1);
    addCreateAuditEntry("dhcp6_subnet", 2);

    // Run the test.
    testDatabaseConfigApply(getTimestamp(-5));

    // Checks the callout.
    EXPECT_EQ("cb6_updated", callback_name_);
    ASSERT_TRUE(callback_audit_entries_);
    EXPECT_TRUE(audit_entries_ == *callback_audit_entries_);
}

// This test verifies that it is possible to set ip-reservations-unique
// parameter via configuration backend and that it is successful when
// host database backend accepts the new setting.
TEST_F(CBControlDHCPv6Test, ipReservationsNonUniqueAccepted) {
    // Create host data source which accepts setting non-unique IP
    // reservations.
    MemHostDataSourcePtr hds(new MemHostDataSource());
    auto testFactory = [hds](const DatabaseConnection::ParameterMap&) {
        return (hds);
    };
    HostDataSourceFactory::registerFactory("test", testFactory);
    HostMgr::addBackend("type=test");

    // Insert ip-reservations-unique value set to false into the database.
    auto& mgr = ConfigBackendDHCPv6Mgr::instance();
    StampedValuePtr global_parameter = StampedValue::create("ip-reservations-unique",
                                                            Element::create(false));
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter6(BackendSelector::UNSPEC(),
                                                                ServerSelector::ALL(),
                                                                global_parameter));
    // Adding audit entry simulates the case when the server is already configured
    // and we're adding incremental changes. These changes should be applied to
    // the current configuration.
    addCreateAuditEntry("dhcp6_global_parameter", 1);

    // Apply the configuration.
    ASSERT_NO_THROW(ctl_.databaseConfigApply(BackendSelector::UNSPEC(),
                                             ServerSelector::ALL(),
                                             getTimestamp(-5),
                                             audit_entries_));
    // The new setting should be visible in both CfgDbAccess and HostMgr.
    EXPECT_FALSE(CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->getIPReservationsUnique());
    EXPECT_FALSE(HostMgr::instance().getIPReservationsUnique());
}

// This test verifies that the new setting of ip-reservations-unique is not
// accepted when one of the host database backends does not support it.
TEST_F(CBControlDHCPv6Test, ipReservationsNonUniqueRefused) {
    // Create host data source which does not accept setting IP reservations
    // non-unique setting.
    NonUniqueHostDataSourcePtr hds(new NonUniqueHostDataSource());
    auto testFactory = [hds](const DatabaseConnection::ParameterMap&) {
        return (hds);
    };
    HostDataSourceFactory::registerFactory("test", testFactory);
    HostMgr::addBackend("type=test");

    // Insert ip-reservations-unique value set to false into the database.
    auto& mgr = ConfigBackendDHCPv6Mgr::instance();
    StampedValuePtr global_parameter = StampedValue::create("ip-reservations-unique",
                                                            Element::create(false));
    ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter6(BackendSelector::UNSPEC(),
                                                                ServerSelector::ALL(),
                                                                global_parameter));
    // Adding audit entry simulates the case when the server is already configured
    // and we're adding incremental changes. These changes should be applied to
    // the current configuration.
    addCreateAuditEntry("dhcp6_global_parameter", 1);

    // Apply the configuration.
    ASSERT_NO_THROW(ctl_.databaseConfigApply(BackendSelector::UNSPEC(),
                                             ServerSelector::ALL(),
                                             getTimestamp(-5),
                                             audit_entries_));
    // The default setting should be applied, because the backend refused to
    // set it to false.
    EXPECT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->getIPReservationsUnique());
    EXPECT_TRUE(HostMgr::instance().getIPReservationsUnique());
}

}
