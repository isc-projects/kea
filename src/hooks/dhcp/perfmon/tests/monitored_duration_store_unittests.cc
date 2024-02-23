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
    MonitoredDurationStoreTest() {
    }

    /// @brief Destructor
    virtual ~MonitoredDurationStoreTest() = default;

    /// @brief Verifies that durations be added to the store and fetched
    /// by DurationKey.
    void addDurationTest() {
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStore store(AF_INET6, interval_duration);

        // Create a key.
        DurationKeyPtr key;
        ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                                       "mt_queued", "process_started", 77)));
        // Add a duration using the key.
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW_LOG(mond = store.addDuration(key, interval_duration));
        ASSERT_TRUE(mond);

        // Verify we can fetch duration by key.
        MonitoredDurationPtr found;
        ASSERT_NO_THROW_LOG(found = store.getDuration(key));
        ASSERT_TRUE(found);

        // Verify we have different objects but equal keys. Ensures we retrieved
        // a copy, not what is stored.
        EXPECT_NE(found, mond);
        EXPECT_EQ(*found, *mond);

        // Create a second key and duration.
        DurationKeyPtr key2;
        ASSERT_NO_THROW_LOG(key2.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_REPLY,
                                                       "mt_queued", "process_started", 77)));
        MonitoredDurationPtr mond2;
        ASSERT_NO_THROW_LOG(mond2 = store.addDuration(key2, interval_duration));
        ASSERT_TRUE(mond2);

        // Verify we can fetch duration by key.
        MonitoredDurationPtr found2;
        ASSERT_NO_THROW_LOG(found2 = store.getDuration(key2));
        ASSERT_TRUE(found2);

        // Fetch all durations, should return them both.
        MonitoredDurationCollectionPtr durations;
        ASSERT_NO_THROW_LOG(durations = store.getAll());
        ASSERT_TRUE(durations);
        ASSERT_EQ(durations->size(), 2);

        // They should be in order by key.
        EXPECT_EQ(*(*durations)[0], *mond);
        EXPECT_EQ(*(*durations)[1], *mond2);
    }

    /// @brief Verifies that duplicate durations cannot be added to the store.
    void addDurationDuplicateTest() {
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStore store(AF_INET6, interval_duration);

        // Create a key.
        DurationKeyPtr key;
        ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                                       "mt_queued", "process_started", 77)));
        // Add a duration using the key.
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW_LOG(mond = store.addDuration(key, interval_duration));
        ASSERT_TRUE(mond);

        // Attempting to add it again should evoke a duplicate key exception.
        ASSERT_THROW_MSG(store.addDuration(key, interval_duration),
                         DuplicateDurationKey,
                         "MonitoredDurationStore::addDuration: duration already exists for:"
                         " SOLICIT-ADVERTISE.mt_queued-process_started.77");
    }

    /// @brief Verifies that duration and store families must match on add.
    void addDurationInvalidTest() {
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStorePtr store(new MonitoredDurationStore(AF_INET, interval_duration));

        // Create a key.
        DurationKeyPtr key;
        ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                                       "mt_queued", "process_started", 77)));

        // Attempting to add it the key should fail.
        ASSERT_THROW_MSG(store->addDuration(key, interval_duration),
                         BadValue,
                         "MonitoredDurationStore::addDuration - cannot add v6 key to v4 store");

        store.reset(new MonitoredDurationStore(AF_INET6, interval_duration));
        ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                                       "mt_queued", "process_started", 77)));
        // Attempting to add it the key should fail.
        ASSERT_THROW_MSG(store->addDuration(key, interval_duration),
                         BadValue,
                         "MonitoredDurationStore::addDuration - cannot add v4 key to v6 store");
    }

    /// @brief Verify that durations can be deleted from the store.
    void deleteDurationTest() {
        MonitoredDurationStore store(AF_INET, milliseconds(5));

        std::vector<DurationKeyPtr> keys;
        for (int subnet = 0; subnet < 3; ++subnet) {
            MonitoredDurationPtr mond;
            DurationKeyPtr key(new DurationKey(AF_INET, DHCPDISCOVER, DHCPOFFER,
                                               "socket_received", "buffer_read", subnet));
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

    /// @brief Verify that durations in the store can be updated.
    void updateDurationTest() {
        Duration interval_duration(seconds(60));
        MonitoredDurationStore store(AF_INET6, interval_duration);
        MonitoredDurationPtr mond;

        // Passing in an empty duration should throw.
        ASSERT_THROW_MSG(store.updateDuration(mond), BadValue,
                         "MonitoredDurationStore::updateDuration - duration is empty");

        // Create a key and then a duration.
        DurationKeyPtr key;
        ASSERT_NO_THROW_LOG(key.reset(new DurationKey(AF_INET6, DHCPV6_SOLICIT, DHCPV6_ADVERTISE,
                                                       "mt_queued", "process_started", 77)));
        ASSERT_NO_THROW(mond.reset(new MonitoredDuration(*key, interval_duration)));

        ASSERT_THROW_MSG(store.updateDuration(mond), InvalidOperation,
                         "MonitoredDurationStore::updateDuration duration not found:"
                         " SOLICIT-ADVERTISE.mt_queued-process_started.77");

        // Now add the duration to the store.
        ASSERT_NO_THROW(store.addDuration(mond));

        // Fetch it.
        MonitoredDurationPtr found;
        ASSERT_NO_THROW_LOG(found = store.getDuration(key));
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

        // Fetch it again and verify there is now a current interval.
        ASSERT_NO_THROW_LOG(found = store.getDuration(key));
        ASSERT_FALSE(found->getPreviousInterval());

        DurationDataIntervalPtr current;
        ASSERT_TRUE(current = found->getCurrentInterval());
        EXPECT_EQ(current->getOccurrences(), 1);
        EXPECT_EQ(current->getTotalDuration(), milliseconds(75));
    }

YOU ARE HERE
#if 0
    void getAllAndClearTest() {
        MonitoredDurationStore store;

        // Add contexts to store.
        for (int i = 0; i < leases_.size(); ++i) {
            MonitoredDurationPtr context;
            ASSERT_NO_THROW_LOG(context = store.addDuration(leases_[i], queries_[i], 1, 100));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
        }

        // Fetch them all.
        MonitoredDurationCollectionPtr contexts;
        ASSERT_NO_THROW_LOG(contexts = store.getAll());
        ASSERT_EQ(leases_.size(), contexts->size());

        // Verify we got them all in order.
        int i = 0;
        for (const auto& context : *contexts) {
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
            ++i;
        }

        // Now clear the store. Verify it's empty.
        ASSERT_NO_THROW_LOG(store.clear());
        ASSERT_NO_THROW_LOG(contexts = store.getAll());
        ASSERT_EQ(0, contexts->size());

        // Verify clearing an empty store does no harm.
        ASSERT_NO_THROW_LOG(store.clear());
    }
#endif
};

TEST_F(MonitoredDurationStoreTest, addDuration) {
    addDurationTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationMultiThreading) {
    MultiThreadingTest mt;
    addDurationTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationDuplicate) {
    addDurationDuplicateTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationDuplicateMultiThreading) {
    MultiThreadingTest mt;
    addDurationDuplicateTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationInvalid) {
    addDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationInvalidMultiThreading) {
    MultiThreadingTest mt;
    addDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, deleteDuration) {
    deleteDurationTest();
}

TEST_F(MonitoredDurationStoreTest, deleteDurationMultiThreading) {
    MultiThreadingTest mt;
    deleteDurationTest();
}

TEST_F(MonitoredDurationStoreTest, updateDuration) {
    updateDurationTest();
}

TEST_F(MonitoredDurationStoreTest, updateDurationMultiThreading) {
    MultiThreadingTest mt;
    updateDurationTest();
}

#if 0
TEST_F(MonitoredDurationStoreTest, getAllAndClear) {
    getAllAndClearTest();
}

TEST_F(MonitoredDurationStoreTest, getAllAndClearMultiThreading) {
    MultiThreadingTest mt;
    getAllAndClearTest();
}
#endif

} // end of anonymous namespace
