// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/testutils/concrete_lease_mgr.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <exceptions/exceptions.h>
#include <functional>
#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace std::placeholders;

namespace {

/// @brief Test fixture class for @c TrackingLeaseMgr.
class TrackingLeaseMgrTest : public GenericLeaseMgrTest {
public:

    /// @brief A structure holding a single callback log entry.
    ///
    /// The @c logCallback function inserts logs of this type into the
    /// @c logs vector. The vector can be later examined to see what
    /// callbacks have been invoked.
    typedef struct {
        TrackingLeaseMgr::CallbackType type;
        SubnetID subnet_id;
        LeasePtr lease;
    } Log;

    /// @brief Reopen the database
    ///
    /// No-op implementation. We need to provide concrete implementation,
    /// as this is a pure virtual method in GenericLeaseMgrTest.
    virtual void reopen(Universe) {}

    /// @brief Convenience function creating a lease instance.
    ///
    /// @param subnet_id subnet identifier for the lease.
    /// @param address leased address.
    /// @tparam LeaseType type of the lease: @c Lease4 or Lease6.
    template<typename LeaseType>
    boost::shared_ptr<LeaseType> createLease(int subnet_id, std::string address) const {
        auto lease = boost::make_shared<LeaseType>();
        lease->subnet_id_ = SubnetID(subnet_id);
        lease->addr_ = IOAddress(address);
        return (lease);
    }

    /// @brief Callback function recording its parameters.
    ///
    /// It is used in the unit tests that verify that appropriate callbacks
    /// have been invoked.
    ///
    /// @param type callback type.
    /// @param subnet_id subnet identifier.
    /// @param lease lease instance.
    void logCallback(const TrackingLeaseMgr::CallbackType type, SubnetID subnet_id, const LeasePtr& lease) {
        logs_.push_back(Log{type, subnet_id, lease});
    }

    /// @brief Counts log entries.
    ///
    /// It counts the logs associated with the specific callback type and subnet id.
    ///
    /// @param type callback type.
    /// @param subnet_id subnet identifier.
    /// @return The number of callback logs associated with the specific type and
    /// the subnet id.
    int countLogs(TrackingLeaseMgr::CallbackType type, SubnetID subnet_id) const {
        int count = 0;
        for (auto log : logs_) {
            if ((log.type == type) && (log.subnet_id == subnet_id)) {
                ++count;
            }
        }
        return (count);
    }

    /// Recorded callback logs.
    std::vector<Log> logs_;
};

/// Tests that leases can be locked and unlocked. When a lease is locked
/// an attempt to lock it again fails.
TEST_F(TrackingLeaseMgrTest, tryLock) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    // An attempt to lock an already locked lease should fail.
    EXPECT_TRUE(mgr.tryLock(createLease<Lease4>(1, "192.0.2.1")));
    EXPECT_FALSE(mgr.tryLock(createLease<Lease4>(1, "192.0.2.1")));

    // We can lock another lease but we cannot lock an already locked one.
    EXPECT_TRUE(mgr.tryLock(createLease<Lease4>(1, "192.0.2.2")));
    EXPECT_FALSE(mgr.tryLock(createLease<Lease4>(1, "192.0.2.1")));
    EXPECT_FALSE(mgr.tryLock(createLease<Lease4>(2, "192.0.2.2")));

    // If we unlock the lease, it can be locked again. However, unlocking
    // the lease should not affect other locks.
    mgr.unlock(createLease<Lease4>(1, "192.0.2.1"));
    EXPECT_FALSE(mgr.tryLock(createLease<Lease4>(2, "192.0.2.2")));
    EXPECT_TRUE(mgr.tryLock(createLease<Lease4>(1, "192.0.2.1")));
}

/// Tests registering the callbacks.
TEST_F(TrackingLeaseMgrTest, registerCallbacks) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    // Callback for lease add and subnet id 0.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));
    // Callback for lease add and subnet id 1.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 1, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   1,
                                                   _1)));
    // Callback for lease add and subnet id 2.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 2, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   1,
                                                   _1)));
    // Callback for lease update and subnet id 0.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                                   0,
                                                   _1)));
    // Callback for lease delete and subnet id 0.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                                   1,
                                                   _1)));

    // This call should trigger the lease add callbacks for subnet id 0 and 1.
    EXPECT_NO_THROW(mgr.trackAddLease(createLease<Lease4>(1, "192.0.2.1"), false));
    EXPECT_EQ(2, logs_.size());
    EXPECT_EQ(1, countLogs(TrackingLeaseMgr::TRACK_ADD_LEASE, 0));
    EXPECT_EQ(1, countLogs(TrackingLeaseMgr::TRACK_ADD_LEASE, 1));

    // This call should trigger the lease add callback for subnet id 0 only. That's
    // because we have no callback for the subnet id 3.
    EXPECT_NO_THROW(mgr.trackAddLease(createLease<Lease4>(3, "192.0.2.1"), false));
    EXPECT_EQ(3, logs_.size());
    EXPECT_EQ(2, countLogs(TrackingLeaseMgr::TRACK_ADD_LEASE, 0));
}

/// Test that registering the callbacks of the same type, for the same subnet id by the
/// same owner fails.
TEST_F(TrackingLeaseMgrTest, registerCallbacksConflicts) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    // Add the callback for lease add and subnet id 0.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));

    // Another attempt should fail.
    EXPECT_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                      std::bind(&TrackingLeaseMgrTest::logCallback,
                                                this,
                                                TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                0,
                                                _1)),
                 InvalidOperation);

    // It should succeed for a different owner.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "qlf",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));

    // It should also succeed for a different subnet id.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 5, "qlf",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   5,
                                                   _1)));

    // But, another attempt for the subnet id should fail.
    EXPECT_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 5, "qlf",
                                      std::bind(&TrackingLeaseMgrTest::logCallback,
                                                this,
                                                TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                5,
                                                _1)),
                 InvalidOperation);
}

/// Test invoking the registered lease update callbacks.
TEST_F(TrackingLeaseMgrTest, trackUpdateLease) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.trackUpdateLease(createLease<Lease4>(1, "192.0.2.1"), false));
    EXPECT_EQ(1, logs_.size());
    EXPECT_EQ(1, countLogs(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 0));
}

/// Test invoking the registered lease delete callbacks.
TEST_F(TrackingLeaseMgrTest, trackDeleteLease) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.trackDeleteLease(createLease<Lease4>(1, "192.0.2.1"), false));
    EXPECT_EQ(1, logs_.size());
    EXPECT_EQ(1, countLogs(TrackingLeaseMgr::TRACK_DELETE_LEASE, 0));
}

// Test unregistering the callbacks by subnet id.
TEST_F(TrackingLeaseMgrTest, unregisterCallbacksBySubnetID) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    // Register different callback types for different subnet identifiers.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 1, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   1,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 2, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   2,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 1, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                                   1,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 2, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                                   2,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, 1, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                                   1,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, 2, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                                   2,
                                                   _1)));

    // Unregister the callbacks for subnet id 1.
    EXPECT_NO_THROW(mgr.unregisterCallbacks(SubnetID(1)));

    // Invoke the remaining callbacksm for the subnet id 1.
    EXPECT_NO_THROW(mgr.trackAddLease(createLease<Lease4>(1, "192.0.2.1"), false));
    EXPECT_NO_THROW(mgr.trackUpdateLease(createLease<Lease4>(1, "192.0.2.1"), false));
    EXPECT_NO_THROW(mgr.trackDeleteLease(createLease<Lease4>(1, "192.0.2.1"), false));

    // It should only run the callback for the subnet id 0 that is still
    // registered.
    EXPECT_EQ(1, logs_.size());
    EXPECT_EQ(1, countLogs(TrackingLeaseMgr::TRACK_ADD_LEASE, 0));

    // Unregister this callback.
    EXPECT_NO_THROW(mgr.unregisterCallbacks(SubnetID(0)));

    // Make sure it is no longer invoked.
    EXPECT_NO_THROW(mgr.trackAddLease(createLease<Lease4>(1, "192.0.2.1"), false));
    EXPECT_EQ(1, logs_.size());

    // Unregistering it again should be no-op.
    EXPECT_NO_THROW(mgr.unregisterCallbacks(SubnetID(0)));
}

/// Test unregistering all callbacks.
TEST_F(TrackingLeaseMgrTest, unregisterAllCallbacks) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);

    // Register some callbacks.
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                                   0,
                                                   _1)));
    // Make sure they have been registered.
    EXPECT_TRUE(mgr.hasCallbacks());

    // Unregister them and make sure it was successful.
    EXPECT_NO_THROW(mgr.unregisterAllCallbacks());
    EXPECT_FALSE(mgr.hasCallbacks());
}

/// Test the function checking if any callbacks have been registered.
TEST_F(TrackingLeaseMgrTest, hasCallbacks) {
    DatabaseConnection::ParameterMap pmap;
    ConcreteLeaseMgr mgr(pmap);
    EXPECT_FALSE(mgr.hasCallbacks());

    EXPECT_NO_THROW(mgr.registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, 0, "flq",
                                         std::bind(&TrackingLeaseMgrTest::logCallback,
                                                   this,
                                                   TrackingLeaseMgr::TRACK_ADD_LEASE,
                                                   0,
                                                   _1)));
    EXPECT_TRUE(mgr.hasCallbacks());
}

/// Test conversion of the callback type to string.
TEST_F(TrackingLeaseMgrTest, callbackTypeToString) {
    EXPECT_EQ("add_lease", ConcreteLeaseMgr::callbackTypeToString(TrackingLeaseMgr::TRACK_ADD_LEASE));
    EXPECT_EQ("update_lease", ConcreteLeaseMgr::callbackTypeToString(TrackingLeaseMgr::TRACK_UPDATE_LEASE));
    EXPECT_EQ("delete_lease", ConcreteLeaseMgr::callbackTypeToString(TrackingLeaseMgr::TRACK_DELETE_LEASE));
}

} // end of anonymous namespace
