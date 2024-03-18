// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the AlarmStore class.
#include <config.h>
#include <alarm_store.h>
#include <dhcp/dhcp6.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfmon;
using namespace isc::test;
using namespace boost::posix_time;

namespace {

// Verifies AlarmStore valid construction.
TEST(AlarmStore, validConstructors) {
    AlarmStorePtr store;

    // Construct and verify v4 store.
    EXPECT_NO_THROW_LOG(store.reset(new AlarmStore(AF_INET)));
    ASSERT_TRUE(store);
    EXPECT_EQ(store->getFamily(), AF_INET);

    AlarmCollectionPtr alarms;
    ASSERT_NO_THROW_LOG(alarms = store->getAll());
    ASSERT_TRUE(alarms);
    EXPECT_TRUE(alarms->empty());

    // Construct and verify v6 store.
    EXPECT_NO_THROW_LOG(store.reset(new AlarmStore(AF_INET6)));
    ASSERT_TRUE(store);
    EXPECT_EQ(store->getFamily(), AF_INET6);

    ASSERT_NO_THROW_LOG(alarms = store->getAll());
    ASSERT_TRUE(alarms);
    EXPECT_TRUE(alarms->empty());
}

// Verifies AlarmStore invalid construction.
TEST(AlarmStore, invalidConstructors) {
    AlarmStorePtr store;

    // Invalid family should throw.
    EXPECT_THROW_MSG(AlarmStore(777),
                     BadValue,
                     "AlarmStore - invalid family 777, must be AF_INET or AF_INET6");
}

/// @brief Text fixture class for @c AlarmStore
///
/// In order to facilitate single and multi threaded testing,
/// individual tests are implemented as methods that are called
/// from within TEST_F bodies rather than in TEST_F bodies.
class AlarmStoreTest : public ::testing::Test {
public:

    /// @brief Constructor
    AlarmStoreTest() = default;

    /// @brief Destructor
    virtual ~AlarmStoreTest() = default;

    /// @brief Creates a protocol-specific DurationKey for a given subnet
    ///
    /// The message-pair and socket-event pairs are fixed.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    /// @param subnet SubnetID of the duration
    DurationKeyPtr makeKey(uint16_t family, SubnetID subnet = 1) {
        DurationKeyPtr key;
        if (family == AF_INET) {
            return (DurationKeyPtr(new DurationKey(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                                   "socket_received", "buffer_read", subnet)));
        }

        return (DurationKeyPtr(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_REPLY,
                                               "socket_received", "buffer_read", subnet)));
    }

    /// @brief Verifies that alarms can be added to the store and fetched
    /// by DurationKey.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void addAlarmTest(uint16_t family) {
        Duration low_water(milliseconds(10));
        Duration high_water(milliseconds(250));
        AlarmStore store(family);

        // Add four alarms with decreaing subnet ids.
        std::vector<AlarmPtr> orig_alarms;
        for (int subnet = 4; subnet > 0; --subnet) {
            AlarmPtr alarm;
            ASSERT_NO_THROW_LOG(alarm = store.addAlarm(makeKey(family, subnet),
                                                       low_water, high_water));
            ASSERT_TRUE(alarm);
            orig_alarms.push_back(alarm);
        }

        // Get all should retrieve all four in ascending order.
        AlarmCollectionPtr alarms = store.getAll();
        ASSERT_EQ(alarms->size(), orig_alarms.size());

        int idx = orig_alarms.size() - 1;
        for (auto const& d : *alarms) {
            EXPECT_EQ(*d, *orig_alarms[idx]) << "failed on pass :" << idx;
            --idx;
        }

        // Make sure we can fetch them all individually.
        for (auto const& alarm : orig_alarms) {
            AlarmPtr found;
            ASSERT_NO_THROW_LOG(found = store.getAlarm(alarm));
            ASSERT_TRUE(found);
            EXPECT_EQ(*alarm, *found);
        }

        // Verify that clear() discards store contents.
        store.clear();
        alarms = store.getAll();
        ASSERT_TRUE(alarms->empty());
    }

    /// @brief Verifies that duplicate alarms cannot be added to the store.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void addAlarmDuplicateTest(uint16_t family) {
        AlarmStore store(family);

        // Add an alarm.
        AlarmPtr alarm;
        ASSERT_NO_THROW_LOG(alarm = store.addAlarm(makeKey(family), milliseconds(10),
                                                   milliseconds(250)));
        ASSERT_TRUE(alarm);

        // Attempting to add it again should evoke a duplicate key exception.
        ASSERT_THROW(store.addAlarm(alarm), DuplicateAlarm);
    }

    /// @brief Verifies that duration key must be valid to add an alarm to the store.
    ///
    /// Tests both v4 and v6.
    void addAlarmInvalidTest() {
        // Create a v4 store.
        AlarmStorePtr store(new AlarmStore(AF_INET));

        // Attempting to add with an empty key should throw.
        ASSERT_THROW_MSG(store->addAlarm(DurationKeyPtr(),
                                         milliseconds(10), milliseconds(250)),
                         BadValue,
                         "AlarmStore::addAlarm - key is empty");

        // Attempting to add a v6 key should fail.
        ASSERT_THROW_MSG(store->addAlarm(makeKey(AF_INET6),
                                         milliseconds(10), milliseconds(250)),
                         BadValue,
                         "AlarmStore::addAlarm"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new AlarmStore(AF_INET6));

        // Attempting to add a v4 key should fail.
        ASSERT_THROW_MSG(store->addAlarm(makeKey(AF_INET),
                                         milliseconds(10), milliseconds(250)),
                         BadValue,
                         "AlarmStore::addAlarm"
                         " - family mismatch, key is v4, store is v6");
    }

    /// @brief Verify that alarms can be deleted from the store.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void deleteAlarmTest(uint16_t family) {
        AlarmStore store(family);

        std::vector<DurationKeyPtr> keys;
        for (int subnet = 0; subnet < 3; ++subnet) {
            AlarmPtr alarm;
            DurationKeyPtr key = makeKey(family, subnet);
            ASSERT_NO_THROW_LOG(alarm = store.addAlarm(key, milliseconds(10), milliseconds(250)));
            ASSERT_TRUE(alarm);
            keys.push_back(key);
        }

        // Verify we added three of them.
        auto alarms = store.getAll();
        ASSERT_EQ(alarms->size(), 3);

        // Fetch the second alarm.
        AlarmPtr alarm;
        ASSERT_NO_THROW_LOG(alarm = store.getAlarm(keys[1]));
        ASSERT_TRUE(alarm);
        EXPECT_EQ(*alarm, *(keys[1]));

        // Delete it.
        ASSERT_NO_THROW_LOG(store.deleteAlarm(alarm));

        // Try to fetch it, shouldn't find it.
        AlarmPtr alarm2;
        ASSERT_NO_THROW_LOG(alarm2 = store.getAlarm(alarm));
        ASSERT_FALSE(alarm2);

        // Deleting it again should do no harm.
        ASSERT_NO_THROW_LOG(store.deleteAlarm(alarm));

        // Verify there are two left.
        alarms = store.getAll();
        ASSERT_EQ(alarms->size(), 2);
    }

    /// @brief Verify an invalid alarm key on delete is detected.
    ///
    /// Tests both v4 and v6.
    void deleteAlarmInvalidTest() {
        // Create a v4 store.
        AlarmStorePtr store(new AlarmStore(AF_INET));

        // Attempting to delete an empty key should throw.
        DurationKeyPtr key;
        ASSERT_THROW_MSG(store->deleteAlarm(key),
                         BadValue,
                         "AlarmStore::deleteAlarm - key is empty");

        // Attempting to delete a v6 key should fail.
        ASSERT_THROW_MSG(store->deleteAlarm(makeKey(AF_INET6)),
                         BadValue,
                         "AlarmStore::deleteAlarm"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new AlarmStore(AF_INET6));

        // Attempting to delete a v4 key should fail.
        ASSERT_THROW_MSG(store->deleteAlarm(makeKey(AF_INET)),
                         BadValue,
                         "AlarmStore::deleteAlarm"
                         " - family mismatch, key is v4, store is v6");
    }

    /// @brief Verify that alarms in the store can be updated.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void updateAlarmTest(uint16_t family) {
        AlarmStore store(family);

        // Add the alarm to the store.
        AlarmPtr alarm;
        ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(*makeKey(family), milliseconds(10),
                                                  milliseconds(250))));
        ASSERT_NO_THROW_LOG(store.addAlarm(alarm));

        // Fetch it.
        AlarmPtr found;
        ASSERT_NO_THROW_LOG(found = store.getAlarm(alarm));
        ASSERT_TRUE(found);

        // Verify the fetched object is a copy.
        ASSERT_NE(found, alarm);
        ASSERT_EQ(*found, *alarm);

        // Now change the thresholds and update it.
        alarm->setLowWater(milliseconds(125));
        alarm->setHighWater(milliseconds(500));
        ASSERT_NO_THROW_LOG(store.updateAlarm(alarm));

        // Fetch it again.
        ASSERT_NO_THROW_LOG(found = store.getAlarm(alarm));

        // Verify it has the expected thresholds.
        EXPECT_EQ(found->getLowWater(), milliseconds(125));
        EXPECT_EQ(found->getHighWater(), milliseconds(500));
    }

    /// @brief Verify an invalid alarm key on update is detected.
    ///
    /// Tests both v4 and v6.
    void updateAlarmInvalidTest() {
        AlarmPtr alarm;

        // Create a v4 store.
        AlarmStorePtr store(new AlarmStore(AF_INET));

        // Attempting to update an empty key should throw.
        ASSERT_THROW_MSG(store->updateAlarm(alarm),
                         BadValue,
                         "AlarmStore::updateAlarm - key is empty");

        // Create a v6 alarm.
        ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(*makeKey(AF_INET6), milliseconds(10),
                                                  milliseconds(250))));

        // Attempting to update v6 alarm to a v4 store should fail.
        ASSERT_THROW_MSG(store->updateAlarm(alarm),
                         BadValue,
                         "AlarmStore::updateAlarm"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new AlarmStore(AF_INET6));

        // Updating a non-existent alarm should fail.
        ASSERT_THROW_MSG(store->updateAlarm(alarm),
                         InvalidOperation,
                         "AlarmStore::updateAlarm alarm not found:"
                         " SOLICIT-REPLY.socket_received-buffer_read.1");

        // Create a v4 alarm.
        ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(*makeKey(AF_INET), milliseconds(10),
                                                  milliseconds(250))));

        // Attempting to update v4 alarm to a v6 store fail.
        ASSERT_THROW_MSG(store->updateAlarm(alarm),
                         BadValue,
                         "AlarmStore::updateAlarm"
                         " - family mismatch, key is v4, store is v6");
    }

    /// @brief Verify checkDurationSample() valid behavior.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void checkDurationSampleTest(uint16_t family) {
        AlarmStore store(family);

        Duration under_low_water(milliseconds(50));
        Duration low_water(milliseconds(100));
        Duration mid_range(milliseconds(175));
        Duration high_water(milliseconds(250));
        Duration over_high_water(milliseconds(300));
        Duration report_interval(milliseconds(10));

        DurationKeyPtr key(makeKey(family));
        AlarmPtr reportable;
        ASSERT_NO_THROW_LOG(reportable = store.checkDurationSample(key, over_high_water,
                                                                   report_interval));
        ASSERT_FALSE(reportable);

        // Add an alarm for the key to the store.
        AlarmPtr alarm;
        ASSERT_NO_THROW_LOG(alarm.reset(new Alarm(*key, low_water, high_water)));
        ASSERT_NO_THROW_LOG(store.addAlarm(alarm));

        // Fetch it.
        AlarmPtr found;
        ASSERT_NO_THROW_LOG(found = store.getAlarm(alarm));
        ASSERT_TRUE(found);

        // Check a sample at mid range. Should not return the alarm.
        ASSERT_NO_THROW_LOG(reportable = store.checkDurationSample(key, mid_range,
                                                                   report_interval));
        ASSERT_FALSE(reportable);

        // Check a sample over high water.  Should return the alarm.
        ASSERT_NO_THROW_LOG(reportable = store.checkDurationSample(key, over_high_water,
                                                                   report_interval));
        ASSERT_TRUE(reportable);
        EXPECT_EQ(reportable->getState(), Alarm::TRIGGERED);

        // Check a sample over high water but before report interval elapses.
        // Should not return the alarm.
        ASSERT_NO_THROW_LOG(reportable = store.checkDurationSample(key, over_high_water,
                                                                   report_interval));
        ASSERT_FALSE(reportable);

        // Sleep beyond the report interval.
        usleep(15 * 1000);

        // Check a sample over high water after report interval elapses.
        // Should return the alarm.
        ASSERT_NO_THROW_LOG(reportable = store.checkDurationSample(key, over_high_water,
                                                                   report_interval));
        ASSERT_TRUE(reportable);
        EXPECT_EQ(reportable->getState(), Alarm::TRIGGERED);

        // Check a sample below low water.
        // Should return the alarm.
        ASSERT_NO_THROW_LOG(reportable = store.checkDurationSample(key, under_low_water,
                                                                   report_interval));
        ASSERT_TRUE(reportable);
        EXPECT_EQ(reportable->getState(), Alarm::CLEAR);
    }
};

TEST_F(AlarmStoreTest, addAlarm) {
    addAlarmTest(AF_INET);
}

TEST_F(AlarmStoreTest, addAlarmMultiThreading) {
    MultiThreadingTest mt;
    addAlarmTest(AF_INET);
}

TEST_F(AlarmStoreTest, addAlarm6) {
    addAlarmTest(AF_INET6);
}

TEST_F(AlarmStoreTest, addAlarm6MultiThreading) {
    MultiThreadingTest mt;
    addAlarmTest(AF_INET6);
}

TEST_F(AlarmStoreTest, addAlarmDuplicate) {
    addAlarmDuplicateTest(AF_INET);
}

TEST_F(AlarmStoreTest, addAlarmDuplicateMultiThreading) {
    MultiThreadingTest mt;
    addAlarmDuplicateTest(AF_INET);
}

TEST_F(AlarmStoreTest, addAlarm6Duplicate) {
    addAlarmDuplicateTest(AF_INET6);
}

TEST_F(AlarmStoreTest, addAlarm6DuplicateMultiThreading) {
    MultiThreadingTest mt;
    addAlarmDuplicateTest(AF_INET6);
}

TEST_F(AlarmStoreTest, addAlarmInvalid) {
    addAlarmInvalidTest();
}

TEST_F(AlarmStoreTest, addAlarmInvalidMultiThreading) {
    MultiThreadingTest mt;
    addAlarmInvalidTest();
}

TEST_F(AlarmStoreTest, deleteAlarm) {
    deleteAlarmTest(AF_INET);
}

TEST_F(AlarmStoreTest, deleteAlarmMultiThreading) {
    MultiThreadingTest mt;
    deleteAlarmTest(AF_INET);
}

TEST_F(AlarmStoreTest, deleteAlarm6) {
    deleteAlarmTest(AF_INET6);
}

TEST_F(AlarmStoreTest, deleteAlarm6MultiThreading) {
    MultiThreadingTest mt;
    deleteAlarmTest(AF_INET6);
}

TEST_F(AlarmStoreTest, deleteAlarmInvalid) {
    deleteAlarmInvalidTest();
}

TEST_F(AlarmStoreTest, deleteAlarmInvalidMultiThreading) {
    MultiThreadingTest mt;
    deleteAlarmInvalidTest();
}

TEST_F(AlarmStoreTest, updateAlarm) {
    updateAlarmTest(AF_INET);
}

TEST_F(AlarmStoreTest, updateAlarmMultiThreading) {
    MultiThreadingTest mt;
    updateAlarmTest(AF_INET);
}

TEST_F(AlarmStoreTest, updateAlarm6) {
    updateAlarmTest(AF_INET6);
}

TEST_F(AlarmStoreTest, updateAlarm6MultiThreading) {
    MultiThreadingTest mt;
    updateAlarmTest(AF_INET6);
}

TEST_F(AlarmStoreTest, updateAlarmInvalid) {
    updateAlarmInvalidTest();
}

TEST_F(AlarmStoreTest, updateAlarmInvalidMultiThreading) {
    MultiThreadingTest mt;
    updateAlarmInvalidTest();
}

TEST_F(AlarmStoreTest, checkDurationSample) {
    checkDurationSampleTest(AF_INET);
}

TEST_F(AlarmStoreTest, checkDurationSampleMultiThreading) {
    MultiThreadingTest mt;
    checkDurationSampleTest(AF_INET);
}

TEST_F(AlarmStoreTest, checkDurationSample6) {
    checkDurationSampleTest(AF_INET6);
}

TEST_F(AlarmStoreTest, checkDurationSample6MultiThreading) {
    MultiThreadingTest mt;
    checkDurationSampleTest(AF_INET6);
}

} // end of anonymous namespace
