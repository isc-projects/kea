// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config_backend/base_config_backend_mgr.h>
#include <config_backend/base_config_backend_pool.h>
#include <process/cb_ctl_base.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <map>
#include <string>

using namespace isc;
using namespace isc::cb;
using namespace isc::db;
using namespace isc::process;

namespace {

/// @brief Implementation of the config backend for testing the
/// @c CBControlBase template class.
///
/// This simple class allows for adding, retrieving and clearing audit
/// entries. The @c CBControlBase unit tests use it to control the
/// behavior of the @c CBControlBase class under test.
class CBControlBackend : BaseConfigBackend {
public:

    /// @brief Constructor.
    CBControlBackend(const db::DatabaseConnection::ParameterMap&) {
    }

    /// @brief Retrieves the audit entries later than specified time.
    ///
    /// @param modification_time The lower bound time for which audit
    /// entries should be returned.
    ///
    /// @return Collection of audit entries later than specified time.
    virtual db::AuditEntryCollection
    getRecentAuditEntries(const db::ServerSelector&,
                          const boost::posix_time::ptime& modification_time) const {
        db::AuditEntryCollection filtered_entries;

        // Use the index which orders the audit entries by timestamps.
        const auto& index = audit_entries_.get<AuditEntryModificationTimeTag>();

        // Locate the first audit entry after the last one having the
        // specified modification time.
        auto first_entry = index.upper_bound(modification_time);

        // If there are any entries found return them.
        if (first_entry != index.end()) {
            filtered_entries.insert(first_entry, index.end());
        }

        return (filtered_entries);
    }

    /// @brief Add audit entry to the backend.
    ///
    /// @param object_type Object type to be stored in the audit entry.
    /// @param object_id Object id to be stored in the audit entry.
    /// @param modification_time Audit entry modification time to be set.
    void addAuditEntry(const ServerSelector&,
                       const std::string& object_type,
                       const uint64_t object_id,
                       const boost::posix_time::ptime& modification_time) {
        // Create new audit entry from the specified parameters.
        AuditEntryPtr audit_entry(new AuditEntry(object_type,
                                                 object_id,
                                                 AuditEntry::ModificationType::CREATE,
                                                 modification_time,
                                                 "added audit entry"));

        // The audit entries are held in the static variable so as they
        // don't disappear when we diconnect from the backend. The
        // audit entries are explicitly cleared during the unit tests
        // setup.
        audit_entries_.insert(audit_entry);
    }

    /// @brief Returns backend type in the textual format.
    ///
    /// @return Name of the storage for configurations, e.g. "mysql",
    /// "pgsql" and so forth.
    virtual std::string getType() const {
        return ("memfile");
    }

    /// @brief Returns backend host
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return host on which the database is located.
    virtual std::string getHost() const {
        return ("");
    }

    /// @brief Returns backend port number.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return Port number on which database service is available.
    virtual uint16_t getPort() const {
        return (0);
    }

    /// @brief Removes audit entries.
    static void clearAuditEntries() {
        audit_entries_.clear();
    }

private:

    /// @brief Static collection of audit entries.
    ///
    /// Thanks to storing them in the static member they are preserved
    /// when the unit tests "disconnect" from the backend.
    static AuditEntryCollection audit_entries_;
};

/// @brief Pointer to the @c CBControlBackend object.
typedef boost::shared_ptr<CBControlBackend> CBControlBackendPtr;

AuditEntryCollection CBControlBackend::audit_entries_;

/// @brief Implementation of the backends pool used in the
/// @c CBControlBase template class unit tests.
class CBControlBackendPool : public BaseConfigBackendPool<CBControlBackend> {
public:

    /// @brief Add audit entry to the backend.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param object_type Object type to be stored in the audit entry.
    /// @param object_id Object id to be stored in the audit entry.
    /// @param modification_time Audit entry modification time to be set.
    void addAuditEntry(const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& object_type,
                       const uint64_t object_id,
                       const boost::posix_time::ptime& modification_time) {
        createUpdateDeleteProperty<void, const std::string&, uint64_t,
                                   const boost::posix_time::ptime&>
            (&CBControlBackend::addAuditEntry, backend_selector, server_selector,
             object_type, object_id, modification_time);
    }

    /// @brief Retrieves the audit entries later than specified time.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param modification_time The lower bound time for which audit
    /// entries should be returned.
    ///
    /// @return Collection of audit entries later than specified time.
    virtual db::AuditEntryCollection
    getRecentAuditEntries(const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const boost::posix_time::ptime& modification_time) const {
        AuditEntryCollection audit_entries;
        getMultiplePropertiesConst<AuditEntryCollection, const boost::posix_time::ptime&>
            (&CBControlBackend::getRecentAuditEntries, backend_selector,
             server_selector, audit_entries, modification_time);
        return (audit_entries);
    }
};

/// @brief Implementation of the config backends manager used
/// in the @c CBControlBase template class unit tests.
class CBControlBackendMgr : public BaseConfigBackendMgr<CBControlBackendPool> {
public:

    /// @brief Constructor.
    CBControlBackendMgr()
        : instance_id_(0) {
    }

    /// @brief Returns instance of the @c CBControlBackendMgr.
    ///
    /// @return Reference to the instance of the @c CBControlBackendMgr.
    static CBControlBackendMgr& instance() {
        static CBControlBackendMgr mgr;
        return (mgr);
    }

    /// @brief Returns instance id.
    ///
    /// This value is used in tests which verify that the @c CBControlBase::getMgr
    /// returns the right instance of the CB manager.
    ///
    /// @return Instance id.
    uint32_t getInstanceId() const {
        return (instance_id_);
    }

    /// @brief Sets new instance id.
    ///
    /// @param instance_id New instance id.
    void setInstanceId(const uint32_t instance_id) {
        instance_id_ = instance_id;
    }

    /// @brief Instance id.
    uint32_t instance_id_;
};

/// @brief Implementation of the @c CBControlBase class used in
/// the unit tests.
///
/// It makes some of the protected methods public. It also provides
/// means to test the behavior of the @c CBControlBase template.
class CBControl : public CBControlBase<CBControlBackendMgr> {
public:

    using CBControlBase<CBControlBackendMgr>::fetchConfigElement;
    using CBControlBase<CBControlBackendMgr>::getMgr;
    using CBControlBase<CBControlBackendMgr>::getInitialAuditEntryTime;

    /// @brief Constructor.
    CBControl()
        : CBControlBase<CBControlBackendMgr>(),
        merges_num_(0),
        backend_selector_(BackendSelector::Type::MYSQL),
        server_selector_(ServerSelector::UNASSIGNED()),
        audit_entries_num_(-1),
        enable_throw_(false) {
    }

    /// @brief Implementation of the method called to fetch and apply
    /// configuration from the database into the local configuration.
    ///
    /// This stub implementation doesn't attempt to merge any configurations
    /// but merely records the values of the parameters called.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param audit_entries Collection of audit entries.
    virtual void databaseConfigApply(const BackendSelector& backend_selector,
                                     const ServerSelector& server_selector,
                                     const boost::posix_time::ptime&,
                                     const AuditEntryCollection& audit_entries) {
        ++merges_num_;
        backend_selector_ = backend_selector;
        server_selector_ = server_selector;
        audit_entries_num_ = static_cast<int>(audit_entries.size());

        if (enable_throw_) {
            isc_throw(Unexpected, "throwing from databaseConfigApply");
        }
    }

    /// @brief Returns the number of times the @c databaseConfigApply was called.
    size_t getMergesNum() const {
        return (merges_num_);
    }

    /// @brief Returns backend selector used as an argument in a call to
    /// @c databaseConfigApply.
    const BackendSelector& getBackendSelector() const {
        return (backend_selector_);
    }

    /// @brief Returns server selector used as an argument in a call to
    /// @c databaseConfigApply.
    const ServerSelector& getServerSelector() const {
        return (server_selector_);
    }

    /// @brief Returns the number of audit entries in the collection passed
    /// to @c databaseConfigApply
    int getAuditEntriesNum() const {
        return (audit_entries_num_);
    }

    /// @brief Returns the recorded time of last audit entry.
    boost::posix_time::ptime getLastAuditEntryTime() const {
        return (last_audit_entry_time_);
    }

    /// @brief Overwrites the last audit entry time.
    ///
    /// @param last_audit_entry_time New time to be set.
    void setLastAuditEntryTime(const boost::posix_time::ptime& last_audit_entry_time) {
        last_audit_entry_time_ = last_audit_entry_time;
    }

    /// @brief Enables the @c databaseConfigApply function to throw.
    ///
    /// This is useful to test scenarios when configuration merge fails.
    void enableThrow() {
        enable_throw_ = true;
    }

private:

    /// @brief Recorded number of calls to @c databaseConfigApply.
    size_t merges_num_;

    /// @brief Recorded backend selector value.
    BackendSelector backend_selector_;

    /// @brief Recorded server selector value.
    ServerSelector server_selector_;

    /// @brief Recorded number of audit entries.
    int audit_entries_num_;

    /// @brief Boolean value indicating if the @c databaseConfigApply should throw.
    bool enable_throw_;
};

/// @brief Out of the blue instance id used in tests.
constexpr uint32_t TEST_INSTANCE_ID = 123;

/// @brief Test fixture class for @c CBControlBase template class.
class CBControlBaseTest : public ::testing::Test {
public:

    /// @brief Constructor.
    CBControlBaseTest()
        : cb_ctl_(), mgr_(CBControlBackendMgr::instance()),
          timestamps_() {
        mgr_.registerBackendFactory("db1",
            [](const DatabaseConnection::ParameterMap& params)
                -> CBControlBackendPtr {
            return (CBControlBackendPtr(new CBControlBackend(params)));
        });
        mgr_.setInstanceId(TEST_INSTANCE_ID);
        initTimestamps();
        CBControlBackend::clearAuditEntries();
    }

    /// @brief Destructor.
    ///
    /// Removes audit entries created in the test.
    ~CBControlBaseTest() {
        CBControlBackend::clearAuditEntries();
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

    /// @brief Creates an instance of the configuration object.
    ///
    /// @param db1_access Database access string to be used to connect to
    /// the test configuration backend. It doesn't connect if the string
    /// is empty.
    ConfigPtr makeConfigBase(const std::string& db1_access = "") const {
        ConfigControlInfoPtr config_ctl_info(new ConfigControlInfo());

        if (!db1_access.empty()) {
            config_ctl_info->addConfigDatabase(db1_access);
        }

        ConfigPtr config_base(new ConfigBase());

        config_base->setConfigControlInfo(config_ctl_info);
        return (config_base);
    }

    /// @brief Instance of the @c CBControl used in tests.
    CBControl cb_ctl_;

    /// @brief Instance of the Config Backend Manager.
    CBControlBackendMgr& mgr_;

    /// @brief Holds timestamp values used in tests.
    std::map<std::string, boost::posix_time::ptime> timestamps_;
};

// This test verifies that the same instance of the Config
// Backend Manager is returned all the time.
TEST_F(CBControlBaseTest, getMgr) {
    auto mgr = cb_ctl_.getMgr();
    EXPECT_EQ(TEST_INSTANCE_ID, mgr.getInstanceId());
}

// This test verifies that last audit entry time is reset upon the
// call to CBControlBase::reset().
TEST_F(CBControlBaseTest, reset) {
    cb_ctl_.setLastAuditEntryTime(timestamps_["tomorrow"]);
    cb_ctl_.reset();
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());
}

// This test verifies that it is correctly determined whether the
// server should fetch the particular configuration element.
TEST_F(CBControlBaseTest, fetchConfigElement) {
    db::AuditEntryCollection audit_entries;
    // When audit entries collection is empty it indicates that this
    // is the case of the full server reconfiguration. Always indicate
    // that the configuration elements must be fetched.
    EXPECT_TRUE(cb_ctl_.fetchConfigElement(audit_entries, "my_object_type"));

    // Now test the case that there is a DELETE audit entry. In this case
    // our function should indicate that the configuration should not be
    // fetched for the given object type. Note that when the configuration
    // element is deleted, it no longer exists in database so there is
    // no reason to fetch the data from the database.
    AuditEntryPtr audit_entry(new AuditEntry("dhcp4_subnet", 1234 ,
                                             AuditEntry::ModificationType::DELETE,
                                             "added audit entry"));
    audit_entries.insert(audit_entry);
    EXPECT_FALSE(cb_ctl_.fetchConfigElement(audit_entries, "my_object_type"));

    // Add another audit entry which indicates creation of the configuration element.
    // This time we should get 'true'.
    audit_entry.reset(new AuditEntry("my_object_type", 5678,
                                     AuditEntry::ModificationType::CREATE,
                                     "added audit entry"));
    audit_entries.insert(audit_entry);
    EXPECT_TRUE(cb_ctl_.fetchConfigElement(audit_entries, "my_object_type"));

    // Also we should get 'true' for the UPDATE case.
    audit_entry.reset(new AuditEntry("another_object_type",
                                     5678, AuditEntry::ModificationType::UPDATE,
                                     "added audit entry"));
    audit_entries.insert(audit_entry);
    EXPECT_TRUE(cb_ctl_.fetchConfigElement(audit_entries, "another_object_type"));
}

// This test verifies that true is return when the server successfully
// connects to the backend and false if there are no backends to connect
// to.
TEST_F(CBControlBaseTest, connect) {
    EXPECT_TRUE(cb_ctl_.databaseConfigConnect(makeConfigBase("type=db1")));
    EXPECT_FALSE(cb_ctl_.databaseConfigConnect(makeConfigBase()));
}

// This test verifies the scenario when the server fetches the entire
// configuration from the database upon startup.
TEST_F(CBControlBaseTest, fetchAll) {
    auto config_base = makeConfigBase("type=db1");

    // Add two audit entries to the database. The server should load
    // the entire configuration from the database regardless of the
    // existing audit entries. However, the last audit entry timestamp
    // should be set to the most recent audit entry in the
    // @c CBControlBase.
    ASSERT_TRUE(cb_ctl_.databaseConfigConnect(config_base));

    cb_ctl_.getMgr().getPool()->addAuditEntry(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              "sql_table_2",
                                              1234,
                                              timestamps_["yesterday"]);

    cb_ctl_.getMgr().getPool()->addAuditEntry(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              "sql_table_1",
                                              3456,
                                              timestamps_["today"]);

    // Disconnect from the database in order to check that the
    // databaseConfigFetch reconnects.
    ASSERT_NO_THROW(cb_ctl_.databaseConfigDisconnect());

    // Verify that various indicators are set to their initial values.
    ASSERT_EQ(0, cb_ctl_.getMergesNum());
    ASSERT_EQ(BackendSelector::Type::MYSQL, cb_ctl_.getBackendSelector().getBackendType());
    ASSERT_EQ(ServerSelector::Type::UNASSIGNED, cb_ctl_.getServerSelector().getType());
    ASSERT_EQ(-1, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());

    // Connect to the database and fetch the configuration.
    ASSERT_NO_THROW(cb_ctl_.databaseConfigFetch(config_base));

    // There should be one invocation of the databaseConfigApply.
    ASSERT_EQ(1, cb_ctl_.getMergesNum());
    // Since this is full reconfiguration the audit entry collection
    // passed to the databaseConfigApply should be empty.
    EXPECT_EQ(0, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(BackendSelector::Type::UNSPEC, cb_ctl_.getBackendSelector().getBackendType());
    EXPECT_EQ(ServerSelector::Type::ALL, cb_ctl_.getServerSelector().getType());
    // Make sure that the internal timestamp is set to the most recent
    // audit entry, so as the server will only later fetch config
    // updates after this timestamp.
    EXPECT_EQ(timestamps_["today"], cb_ctl_.getLastAuditEntryTime());
}

// This test verifies that the configuration can be fetched for a
// specified server tag.
TEST_F(CBControlBaseTest, fetchFromServer) {
    auto config_base = makeConfigBase("type=db1");
    // Set a server tag.
    config_base->setServerTag("a-tag");

    // Verify that various indicators are set to their initial values.
    ASSERT_EQ(0, cb_ctl_.getMergesNum());
    ASSERT_EQ(BackendSelector::Type::MYSQL, cb_ctl_.getBackendSelector().getBackendType());
    ASSERT_EQ(ServerSelector::Type::UNASSIGNED, cb_ctl_.getServerSelector().getType());
    ASSERT_EQ(-1, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());

    ASSERT_NO_THROW(cb_ctl_.databaseConfigFetch(config_base));

    ASSERT_EQ(1, cb_ctl_.getMergesNum());
    EXPECT_EQ(0, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(BackendSelector::Type::UNSPEC, cb_ctl_.getBackendSelector().getBackendType());
    // An explicit server selector should have been used this time.
    ASSERT_EQ(ServerSelector::Type::SUBSET, cb_ctl_.getServerSelector().getType());
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());

    // Make sure that the server selector used in databaseConfigFetch is
    // correct.
    auto tags = cb_ctl_.getServerSelector().getTags();
    ASSERT_EQ(1, tags.size());
    EXPECT_EQ("a-tag", *tags.begin());
}

// This test verifies that incremental configuration changes can be
// fetched.
TEST_F(CBControlBaseTest, fetchUpdates) {
    auto config_base = makeConfigBase("type=db1");

    // Connect to the database and store an audit entry. Do not close
    // the database connection to simulate the case when the server
    // uses existing connection to fetch configuration updates.
    ASSERT_TRUE(cb_ctl_.databaseConfigConnect(config_base));
    cb_ctl_.getMgr().getPool()->addAuditEntry(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              "sql_table_1",
                                              3456,
                                              timestamps_["today"]);

    // Verify that various indicators are set to their initial values.
    ASSERT_EQ(0, cb_ctl_.getMergesNum());
    ASSERT_EQ(BackendSelector::Type::MYSQL, cb_ctl_.getBackendSelector().getBackendType());
    ASSERT_EQ(ServerSelector::Type::UNASSIGNED, cb_ctl_.getServerSelector().getType());
    ASSERT_EQ(-1, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());

    ASSERT_NO_THROW(cb_ctl_.databaseConfigFetch(config_base,
                                                CBControl::FetchMode::FETCH_UPDATE));

    // There should be one invocation to databaseConfigApply recorded.
    ASSERT_EQ(1, cb_ctl_.getMergesNum());
    // The number of audit entries passed to this function should be 1.
    EXPECT_EQ(1, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(BackendSelector::Type::UNSPEC, cb_ctl_.getBackendSelector().getBackendType());
    EXPECT_EQ(ServerSelector::Type::ALL, cb_ctl_.getServerSelector().getType());
    // The last audit entry time should be set to the latest audit entry.
    EXPECT_EQ(timestamps_["today"], cb_ctl_.getLastAuditEntryTime());
}

// Check that the databaseConfigApply function is not called when there
// are no more unprocessed audit entries.
TEST_F(CBControlBaseTest, fetchNoUpdates) {
    auto config_base = makeConfigBase("type=db1");

    // Set last audit entry time to the timestamp of the audit
    // entry we are going to add. That means that there will be
    // no new audit entries to fetch.
    cb_ctl_.setLastAuditEntryTime(timestamps_["yesterday"]);

    ASSERT_TRUE(cb_ctl_.databaseConfigConnect(config_base));

    cb_ctl_.getMgr().getPool()->addAuditEntry(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              "sql_table_1",
                                              3456,
                                              timestamps_["yesterday"]);

    ASSERT_EQ(0, cb_ctl_.getMergesNum());

    ASSERT_NO_THROW(cb_ctl_.databaseConfigFetch(config_base,
                                                CBControl::FetchMode::FETCH_UPDATE));

    // The databaseConfigApply should not be called because there are
    // no new audit entires to process.
    ASSERT_EQ(0, cb_ctl_.getMergesNum());
}

// This test verifies that database config fetch failures are handled
// gracefully.
TEST_F(CBControlBaseTest, fetchFailure) {
    auto config_base = makeConfigBase("type=db1");

    // Connect to the database and store an audit entry. Do not close
    // the database connection to simulate the case when the server
    // uses existing connection to fetch configuration updates.
    ASSERT_TRUE(cb_ctl_.databaseConfigConnect(config_base));
    cb_ctl_.getMgr().getPool()->addAuditEntry(BackendSelector::UNSPEC(),
                                              ServerSelector::ALL(),
                                              "sql_table_1",
                                              3456,
                                              timestamps_["today"]);

    // Configure the CBControl to always throw simulating the failure
    // during configuration merge.
    cb_ctl_.enableThrow();

    // Verify that various indicators are set to their initial values.
    ASSERT_EQ(0, cb_ctl_.getMergesNum());
    ASSERT_EQ(BackendSelector::Type::MYSQL, cb_ctl_.getBackendSelector().getBackendType());
    ASSERT_EQ(ServerSelector::Type::UNASSIGNED, cb_ctl_.getServerSelector().getType());
    ASSERT_EQ(-1, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());

    ASSERT_THROW(cb_ctl_.databaseConfigFetch(config_base, CBControl::FetchMode::FETCH_UPDATE),
                 isc::Unexpected);

    // There should be one invocation to databaseConfigApply recorded.
    ASSERT_EQ(1, cb_ctl_.getMergesNum());
    // The number of audit entries passed to this function should be 1.
    EXPECT_EQ(1, cb_ctl_.getAuditEntriesNum());
    EXPECT_EQ(BackendSelector::Type::UNSPEC, cb_ctl_.getBackendSelector().getBackendType());
    EXPECT_EQ(ServerSelector::Type::ALL, cb_ctl_.getServerSelector().getType());
    // The last audit entry time should not be modified because there was a merge
    // error.
    EXPECT_EQ(cb_ctl_.getInitialAuditEntryTime(), cb_ctl_.getLastAuditEntryTime());

}

}
