// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/stamped_value.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/testutils/generic_backend_unittest.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp4.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <map>
#include <string>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;

namespace {

/// @brief Base class for testing derivations of the CBControlDHCP.
class CBControlDHCPTest : public GenericBackendTest {
public:

    /// @brief Constructor.
    CBControlDHCPTest()
        : timestamp_(), object_timestamp_(), audit_entries_() {
        CfgMgr::instance().clear();
        initTimestamps();
    }

    /// @brief Destructor.
    virtual ~CBControlDHCPTest() {
        // Unregister the factory to be tidy.
        ConfigBackendDHCPv4Mgr::instance().unregisterBackendFactory("memfile");
        CfgMgr::instance().clear();
    }

    /// @brief Creates new CREATE audit entry.
    ///
    /// The audit entry is added to the @c audit_entries_ collection.
    ///
    /// @param object_type Object type to be associated with the audit
    /// entry.
    void addCreateAuditEntry(const std::string& object_type) {
        AuditEntryPtr entry(new AuditEntry(object_type, 1234,
                                           AuditEntry::ModificationType::CREATE,
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
    bool fetchConfigElement(const std::string& object_type) const {
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

    /// @brief Holds test timestamps.
    std::map<int, boost::posix_time::ptime> timestamp_;

    /// @brief Holds mapping of the objects types to their timestamps.
    std::map<std::string, boost::posix_time::ptime> object_timestamp_;

    /// @brief Collection of audit entries used in the unit tests.
    AuditEntryCollection audit_entries_;
};

/// @brief Naked @c CBControlDHCPv4 class exposing protected methods.
class TestCBControlDHCPv4 : public CBControlDHCPv4 {
public:
    using CBControlDHCPv4::getInitialAuditEntryTime;
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
        auto& mgr = ConfigBackendDHCPv4Mgr::instance();

        // Insert global parameter into a database.
        StampedValuePtr global_parameter = StampedValue::create("foo", "bar");
        global_parameter->setModificationTime(getTimestamp("dhcp4_global_parameter"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateGlobalParameter4(BackendSelector::UNSPEC(),
                                                                    ServerSelector::ALL(),
                                                                    global_parameter));

        // Insert option definition into the database.
        OptionDefinitionPtr def(new OptionDefinition("one", 101, "uint16"));
        def->setOptionSpaceName("isc");
        def->setModificationTime(getTimestamp("dhcp4_option_def"));
        ASSERT_NO_THROW(mgr.getPool()->createUpdateOptionDef4(BackendSelector::UNSPEC(),
                                                              ServerSelector::ALL(),
                                                              def));

        // Insert global option into the database.
        OptionDescriptorPtr opt(new OptionDescriptor(createOption<OptionString>
                                                     (Option::V4, DHO_HOST_NAME,
                                                      true, false, "new.example.com")));
        opt->space_name_ = DHCP4_OPTION_SPACE;
        opt->setModificationTime(getTimestamp("dhcp4_options"));
        mgr.getPool()->createUpdateOption4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           opt);

        // Insert shared network into the database.
        SharedNetwork4Ptr network(new SharedNetwork4("one"));
        network->setModificationTime(getTimestamp("dhcp4_shared_network"));

        mgr.getPool()->createUpdateSharedNetwork4(BackendSelector::UNSPEC(),
                                                  ServerSelector::ALL(),
                                                  network);

        // Insert subnet into the database.
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, SubnetID(1)));
        subnet->setModificationTime(getTimestamp("dhcp4_subnet"));

        mgr.getPool()->createUpdateSubnet4(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                           subnet);

        ASSERT_FALSE(audit_entries_.empty())
            << "Require at least one audit entry. The test is broken!";

        ctl_.databaseConfigApply(BackendSelector::UNSPEC(), ServerSelector::ALL(),
                                 lb_modification_time, audit_entries_);

        // The updates should have been merged into current configuration.
        auto srv_cfg = CfgMgr::instance().getCurrentCfg();

        // If there is an audit entry for global parameter and the parameter
        // modification time is later than last audit entry time it should
        // be merged.
        if (fetchConfigElement("dhcp4_global_parameter") &&
            (global_parameter->getModificationTime() > lb_modification_time)) {
            checkConfiguredGlobal(srv_cfg, "foo", Element::create("bar"));

        } else {
            // Otherwise it shouldn't exist.
            EXPECT_FALSE(srv_cfg->getConfiguredGlobals()->get("foo"));
        }

        // If there is an audit entry for option definition and the definition
        // modification time is later than last audit entry time it should
        // be merged.
        auto found_def = srv_cfg->getCfgOptionDef()->get("isc", "one");
        if (fetchConfigElement("dhcp4_option_def") &&
            def->getModificationTime() > lb_modification_time) {
            ASSERT_TRUE(found_def);
            EXPECT_EQ(101, found_def->getCode());
            EXPECT_EQ(OptionDataType::OPT_UINT16_TYPE, found_def->getType());

        } else {
            EXPECT_FALSE(found_def);
        }

        // If there is an audit entry for an option and the option
        // modification time is later than last audit entry time it should
        // be merged.
        auto options = srv_cfg->getCfgOption();
        auto found_opt = options->get("dhcp4", DHO_HOST_NAME);
        if (fetchConfigElement("dhcp4_options") &&
            (opt->getModificationTime() > lb_modification_time)) {
            ASSERT_TRUE(found_opt.option_);
            EXPECT_EQ("new.example.com", found_opt.option_->toString());

        } else {
            EXPECT_FALSE(found_opt.option_);
        }

        // If there is an audit entry for a shared network and the network
        // modification time is later than last audit entry time it should
        // be merged.
        auto networks = srv_cfg->getCfgSharedNetworks4();
        auto found_network = networks->getByName("one");
        if (fetchConfigElement("dhcp4_shared_network") &&
            (network->getModificationTime() > lb_modification_time)) {
            EXPECT_TRUE(found_network);
            EXPECT_TRUE(found_network->hasFetchGlobalsFn());

        } else {
            EXPECT_FALSE(found_network);
        }

        // If there is an audit entry for a subnet and the subnet modification
        // time is later than last audit entry time it should be merged.
        auto subnets = srv_cfg->getCfgSubnets4();
        auto found_subnet = subnets->getSubnet(1);
        if (fetchConfigElement("dhcp4_subnet") &&
            (subnet->getModificationTime() > lb_modification_time)) {
            ASSERT_TRUE(found_subnet);
            EXPECT_TRUE(found_subnet->hasFetchGlobalsFn());

        } else {
            EXPECT_FALSE(found_subnet);
        }
    }

    TestCBControlDHCPv4 ctl_;
};


// This test verifies that the configuration updates for all object
// types are merged into the current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyAll) {

    addCreateAuditEntry("dhcp4_global_parameter");
    addCreateAuditEntry("dhcp4_option_def");
    addCreateAuditEntry("dhcp4_options");
    addCreateAuditEntry("dhcp4_shared_network");
    addCreateAuditEntry("dhcp4_subnet");

    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that only a global parameter is merged into
// the current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyGlobal) {
    addCreateAuditEntry("dhcp4_global_parameter");
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that global parameter is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyGlobalNotFetched) {
    addCreateAuditEntry("dhcp4_global_parameter");
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only an option definition is merged into
// the current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOptionDef) {
    addCreateAuditEntry("dhcp4_option_def");
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that option definition is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOptionDefNotFetched) {
    addCreateAuditEntry("dhcp4_option_def");
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a DHCPv4 option is merged into the
// current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOption) {
    addCreateAuditEntry("dhcp4_options");
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that DHCPv4 option is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplyOptionNotFetched) {
    addCreateAuditEntry("dhcp4_options");
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a shared network is merged into the
// current configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySharedNetwork) {
    addCreateAuditEntry("dhcp4_shared_network");
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that shared network is not fetched from the
// database when the modification time is earlier than the last
// fetched audit entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySharedNetworkNotFetched) {
    addCreateAuditEntry("dhcp4_shared_network");
    testDatabaseConfigApply(getTimestamp(-3));
}

// This test verifies that only a subnet is merged into the current
// configuration.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySubnet) {
    addCreateAuditEntry("dhcp4_subnet");
    testDatabaseConfigApply(getTimestamp(-5));
}

// This test verifies that subnet is not fetched from the database
// when the modification time is earlier than the last fetched audit
// entry.
TEST_F(CBControlDHCPv4Test, databaseConfigApplySubnetNotFetched) {
    addCreateAuditEntry("dhcp4_subnet");
    testDatabaseConfigApply(getTimestamp(-3));
}

}
