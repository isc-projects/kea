// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the MonitoredDurationStore class.
#include <config.h>
#include <monitored_duration_store.h>
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

// Verifies MonitoredDurationStore valid construction.
TEST(MonitoredDurationStore, validConstructors) {
    MonitoredDurationStorePtr store;

    EXPECT_NO_THROW_LOG(store.reset(new MonitoredDurationStore(AF_INET, milliseconds(5))));
    ASSERT_TRUE(store);

    MonitoredDurationCollectionPtr durations;
    ASSERT_NO_THROW_LOG(durations = store->getAll());
    ASSERT_TRUE(durations);
    EXPECT_TRUE(durations->empty());
}

// Verifies MonitoredDurationStore invalid construction.
TEST(MonitoredDurationStore, invalidConstructors) {
    MonitoredDurationStorePtr store;

    EXPECT_THROW_MSG(MonitoredDurationStore(AF_INET, milliseconds(0)),
                     BadValue,
                     "MonitoredDurationStore - invalid interval_duration"
                     " 00:00:00, must be greater than zero");

    EXPECT_THROW_MSG(MonitoredDurationStore(AF_INET, milliseconds(-5)),
                     BadValue,
                     "MonitoredDurationStore - invalid interval_duration"
                     " -00:00:00.005000, must be greater than zero");
}

/// @brief Text fixture class for @c MonitoredDurationStore
///
/// In order to facilitate single and multi threaded testing,
/// individual tests are implemented as methods that are called
/// from within TEST_F bodies rather than in TEST_F bodies.
class MonitoredDurationStoreTest : public ::testing::Test {
public:

    /// @brief Constructor
    MonitoredDurationStoreTest() = default;

    /// @brief Destructor
    virtual ~MonitoredDurationStoreTest() = default;

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

    /// @brief Verifies that durations be added to the store and fetched
    /// by DurationKey.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void addDurationTest(uint16_t family) {
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStore store(family, interval_duration);

        std::vector<MonitoredDurationPtr> monds;
        // Add four durations with decreaing subnet ids.
        for (int subnet = 4; subnet > 0; --subnet) {
            MonitoredDurationPtr mond;
            ASSERT_NO_THROW_LOG(mond = store.addDuration(makeKey(family, subnet),
                                                         interval_duration));
            ASSERT_TRUE(mond);
            monds.push_back(mond);
        }

        // Get all should retrieve all four in ascending order.
        MonitoredDurationCollectionPtr durations = store.getAll();
        ASSERT_EQ(durations->size(), monds.size());

        int idx = monds.size() - 1;
        for (auto const& d : *durations) {
            EXPECT_EQ(*d, *monds[idx]) << "failed on pass :" << idx;
            --idx;
        }

        // Make sure we can fetch them all individually.
        for (auto const& mond : monds) {
            MonitoredDurationPtr found;
            ASSERT_NO_THROW_LOG(found = store.getDuration(mond));
            ASSERT_TRUE(found);
            EXPECT_EQ(*mond, *found);
        }

        // Verify that clear() discards store contents.
        store.clear();
        durations = store.getAll();
        ASSERT_TRUE(durations->empty());
    }

    /// @brief Verifies that duplicate durations cannot be added to the store.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void addDurationDuplicateTest(uint16_t family) {
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStore store(family, interval_duration);

        // Add a duration.
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW_LOG(mond = store.addDuration(makeKey(family), interval_duration));
        ASSERT_TRUE(mond);

        // Attempting to add it again should evoke a duplicate key exception.
        ASSERT_THROW(store.addDuration(mond, interval_duration), DuplicateDurationKey);
    }

    /// @brief Verifies that duration key must be valid to add a duration to the store.
    ///
    /// Tests both v4 and v6.
    void addDurationInvalidTest() {
        // Create a v4 store.
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStorePtr store(new MonitoredDurationStore(AF_INET, interval_duration));

        // Attempting to add with an empty key should throw.
        ASSERT_THROW_MSG(store->addDuration(DurationKeyPtr(), interval_duration),
                         BadValue,
                         "MonitoredDurationStore::addDuration - key is empty");

        // Attempting to a v6 key should fail.
        ASSERT_THROW_MSG(store->addDuration(makeKey(AF_INET6), interval_duration),
                         BadValue,
                         "MonitoredDurationStore::addDuration"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new MonitoredDurationStore(AF_INET6, interval_duration));

        // Attempting to add a v4 key should fail.
        ASSERT_THROW_MSG(store->addDuration(makeKey(AF_INET), interval_duration),
                         BadValue,
                         "MonitoredDurationStore::addDuration"
                         " - family mismatch, key is v4, store is v6");
    }

    /// @brief Verify that durations can be deleted from the store.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void deleteDurationTest(uint16_t family) {
        MonitoredDurationStore store(family, milliseconds(5));

        std::vector<DurationKeyPtr> keys;
        for (int subnet = 0; subnet < 3; ++subnet) {
            MonitoredDurationPtr mond;
            DurationKeyPtr key = makeKey(family, subnet);
            ASSERT_NO_THROW_LOG(mond = store.addDuration(key));
            ASSERT_TRUE(mond);
            keys.push_back(key);
        }

        // Verify we added three of them.
        auto durations = store.getAll();
        ASSERT_EQ(durations->size(), 3);

        // Fetch the second duration.
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW_LOG(mond = store.getDuration(keys[1]));
        ASSERT_TRUE(mond);
        EXPECT_EQ(*mond, *(keys[1]));

        // Delete it.
        ASSERT_NO_THROW_LOG(store.deleteDuration(mond));

        // Try to fetch it, shouldn't find it.
        MonitoredDurationPtr mond2;
        ASSERT_NO_THROW_LOG(mond2 = store.getDuration(mond));
        ASSERT_FALSE(mond2);

        // Deleting it again should do no harm.
        ASSERT_NO_THROW_LOG(store.deleteDuration(mond));

        // Verify there are two left.
        durations = store.getAll();
        ASSERT_EQ(durations->size(), 2);
    }

    /// @brief Verify an invalid duration key on delete is detected.
    ///
    /// Tests both v4 and v6.
    void deleteDurationInvalidTest() {
         // Create a v4 store.
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStorePtr store(new MonitoredDurationStore(AF_INET, interval_duration));

        // Attempting to delete an empty key should throw.
        DurationKeyPtr key;
        ASSERT_THROW_MSG(store->deleteDuration(key),
                         BadValue,
                         "MonitoredDurationStore::deleteDuration - key is empty");

        // Attempting to delete a v6 key should fail.
        ASSERT_THROW_MSG(store->deleteDuration(makeKey(AF_INET6)),
                         BadValue,
                         "MonitoredDurationStore::deleteDuration"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new MonitoredDurationStore(AF_INET6, interval_duration));

        // Attempting to delete a v4 key should fail.
        ASSERT_THROW_MSG(store->deleteDuration(makeKey(AF_INET)),
                         BadValue,
                         "MonitoredDurationStore::deleteDuration"
                         " - family mismatch, key is v4, store is v6");
    }

    /// @brief Verify that durations in the store can be updated.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void updateDurationTest(uint16_t family) {
        Duration interval_duration(seconds(60));
        MonitoredDurationStore store(family, interval_duration);

        // Add the duration to the store.
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW(mond.reset(new MonitoredDuration(*makeKey(family), interval_duration)));
        ASSERT_NO_THROW(store.addDuration(mond));

        // Fetch it.
        MonitoredDurationPtr found;
        ASSERT_NO_THROW_LOG(found = store.getDuration(mond));
        ASSERT_TRUE(found);

        // Verify the fetched object is a copy.
        ASSERT_NE(found, mond);
        ASSERT_EQ(*found, *mond);

        // Verify that it has no intervals.
        ASSERT_FALSE(found->getPreviousInterval());
        ASSERT_FALSE(found->getCurrentInterval());

        // Now add a sample to the duration and update it.
        mond->addSample(milliseconds(75));
        ASSERT_NO_THROW(store.updateDuration(mond));

        // Fetch it again.
        ASSERT_NO_THROW_LOG(found = store.getDuration(mond));
        ASSERT_FALSE(found->getPreviousInterval());

        // Verify it has the expected current interval.
        DurationDataIntervalPtr current;
        ASSERT_TRUE(current = found->getCurrentInterval());
        EXPECT_EQ(current->getOccurrences(), 1);
        EXPECT_EQ(current->getTotalDuration(), milliseconds(75));
    }

    /// @brief Verify an invalid duration key on update is detected.
    ///
    /// Tests both v4 and v6.
    void updateDurationInvalidTest() {
        Duration interval_duration(seconds(60));
        MonitoredDurationPtr mond;

         // Create a v4 store.
        MonitoredDurationStorePtr store(new MonitoredDurationStore(AF_INET6, interval_duration));

        // Attempting to update an empty key should throw.
        ASSERT_THROW_MSG(store->updateDuration(mond),
                         BadValue,
                         "MonitoredDurationStore::deleteDuration - key is empty");

        // Create a v6 duration.
        ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(*makeKey(AF_INET6), interval_duration)));

        // Attempting to update v6 duration in a v4 store should fail.
        ASSERT_THROW_MSG(store->updateDuration(mond),
                         BadValue,
                         "MonitoredDurationStore::updateDuration"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new MonitoredDurationStore(AF_INET6, interval_duration));

        // Updating a non-existent duration should fail.
        ASSERT_THROW_MSG(store->updateDuration(mond),
                         BadValue,
                         "MonitoredDurationStore::updateDuration duration not found:"
                         " SOLICIT-ADVERTISE.mt_queued-process_started.77");

        // Create a v4 duration.
        ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(*makeKey(AF_INET), interval_duration)));

        // Attempting to update v4 duration in a v6 store fail.
        ASSERT_THROW_MSG(store->updateDuration(mond),
                         BadValue,
                         "MonitoredDurationStore::updateDuration"
                         " - family mismatch, key is v4, store is v6");
    }
};

TEST_F(MonitoredDurationStoreTest, addDuration) {
    addDurationTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, addDurationMultiThreading) {
    MultiThreadingTest mt;
    addDurationTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, addDuration6) {
    addDurationTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, addDuration6MultiThreading) {
    MultiThreadingTest mt;
    addDurationTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, addDurationDuplicate) {
    addDurationDuplicateTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, addDurationDuplicateMultiThreading) {
    MultiThreadingTest mt;
    addDurationDuplicateTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, addDuration6Duplicate) {
    addDurationDuplicateTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, addDuration6DuplicateMultiThreading) {
    MultiThreadingTest mt;
    addDurationDuplicateTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, addDurationInvalid) {
    addDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationInvalidMultiThreading) {
    MultiThreadingTest mt;
    addDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, deleteDuration) {
    deleteDurationTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, deleteDurationMultiThreading) {
    MultiThreadingTest mt;
    deleteDurationTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, deleteDuration6) {
    deleteDurationTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, deleteDuration6MultiThreading) {
    MultiThreadingTest mt;
    deleteDurationTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, deleteDurationInvalid) {
    deleteDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, deleteDurationInvalidMultiThreading) {
    MultiThreadingTest mt;
    deleteDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, updateDuration) {
    updateDurationTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, updateDurationMultiThreading) {
    MultiThreadingTest mt;
    updateDurationTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, updateDuration6) {
    updateDurationTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, updateDuration6MultiThreading) {
    MultiThreadingTest mt;
    updateDurationTest(AF_INET6);
}

} // end of anonymous namespace
