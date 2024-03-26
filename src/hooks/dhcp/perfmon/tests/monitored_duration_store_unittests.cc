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

#include <boost/range/adaptor/reversed.hpp>
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

    EXPECT_THROW_MSG(MonitoredDurationStore(777, seconds(60)),
                     BadValue,
                     "MonitoredDurationStore - invalid family 777, must be AF_INET or AF_INET6");

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

    /// @brief Verifies that durations can be added to the store and fetched
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
            ASSERT_NO_THROW_LOG(mond = store.addDuration(makeKey(family, subnet)));
            ASSERT_TRUE(mond);
            monds.push_back(mond);
        }

        // Get all should retrieve all four in ascending order.
        MonitoredDurationCollectionPtr durations = store.getAll();
        ASSERT_EQ(durations->size(), monds.size());

        int idx = monds.size() - 1;
        for (auto const& d : *durations) {
            EXPECT_EQ(*d, *monds[idx]) << "failed on pass: " << idx;
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
        ASSERT_NO_THROW_LOG(mond = store.addDuration(makeKey(family)));
        ASSERT_TRUE(mond);

        // Attempting to add it again should evoke a duplicate key exception.
        ASSERT_THROW(store.addDuration(mond), DuplicateDurationKey);
    }

    /// @brief Verifies that duration key must be valid to add a duration to the store.
    ///
    /// Tests both v4 and v6.
    void addDurationInvalidTest() {
        // Create a v4 store.
        Duration interval_duration(milliseconds(10));
        MonitoredDurationStorePtr store(new MonitoredDurationStore(AF_INET, interval_duration));

        // Attempting to add with an empty key should throw.
        ASSERT_THROW_MSG(store->addDuration(DurationKeyPtr()),
                         BadValue,
                         "MonitoredDurationStore::addDuration - key is empty");

        // Attempting to add a v6 key should fail.
        ASSERT_THROW_MSG(store->addDuration(makeKey(AF_INET6)),
                         BadValue,
                         "MonitoredDurationStore::addDuration"
                         " - family mismatch, key is v6, store is v4");

        // Create a v6 store.
        store.reset(new MonitoredDurationStore(AF_INET6, interval_duration));

        // Attempting to add a v4 key should fail.
        ASSERT_THROW_MSG(store->addDuration(makeKey(AF_INET)),
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
        ASSERT_NE(current, mond->getCurrentInterval());
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
        MonitoredDurationStorePtr store(new MonitoredDurationStore(AF_INET, interval_duration));

        // Attempting to update an empty key should throw.
        ASSERT_THROW_MSG(store->updateDuration(mond),
                         BadValue,
                         "MonitoredDurationStore::updateDuration - key is empty");

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
                         InvalidOperation,
                         "MonitoredDurationStore::updateDuration duration not found:"
                         " SOLICIT-REPLY.socket_received-buffer_read.1");

        // Create a v4 duration.
        ASSERT_NO_THROW_LOG(mond.reset(new MonitoredDuration(*makeKey(AF_INET), interval_duration)));

        // Attempting to update v4 duration in a v6 store fail.
        ASSERT_THROW_MSG(store->updateDuration(mond),
                         BadValue,
                         "MonitoredDurationStore::updateDuration"
                         " - family mismatch, key is v4, store is v6");
    }

    /// @brief Exercises addDurationSample() valid behavior.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void addDurationSampleTest(uint16_t family) {
        // Create a store.
        Duration interval_duration(milliseconds(50));
        MonitoredDurationStore store(family, interval_duration);

        // Create valid key.
        DurationKeyPtr key = makeKey(family);

        // Add a 5 ms sample for the key.
        MonitoredDurationPtr mond;
        Duration five_ms(milliseconds(5));
        ASSERT_NO_THROW_LOG(mond = store.addDurationSample(key, five_ms));

        // Should return an empty pointer as nothing to report yet.
        EXPECT_FALSE(mond);

        // Make sure the duration was created and stored, and has only
        // the current interval with 1 occurrence and a total of 5 ms.
        ASSERT_NO_THROW_LOG(mond = store.getDuration(key));
        ASSERT_TRUE(mond);
        auto current_interval = mond->getCurrentInterval();
        ASSERT_TRUE(current_interval);
        EXPECT_EQ(current_interval->getOccurrences(), 1);
        EXPECT_EQ(current_interval->getTotalDuration(), (five_ms));
        auto previous_interval = mond->getPreviousInterval();
        ASSERT_FALSE(previous_interval);

        // Now lets add a second sample. We should still be inside the
        // interval, so it still should return an empty pointer.
        ASSERT_NO_THROW_LOG(mond = store.addDurationSample(key, five_ms));
        EXPECT_FALSE(mond);

        // Make sure the duration's current interval (only) was updated
        ASSERT_NO_THROW_LOG(mond = store.getDuration(key));
        ASSERT_TRUE(mond);
        current_interval = mond->getCurrentInterval();
        ASSERT_TRUE(current_interval);
        EXPECT_EQ(current_interval->getOccurrences(), 2);
        EXPECT_EQ(current_interval->getTotalDuration(), (five_ms * 2));
        previous_interval = mond->getPreviousInterval();
        ASSERT_FALSE(previous_interval);

        // Sleep til past the end of interval
        usleep(60 * 1000);

        // Now lets add a third sample. We are past the end of the
        // interval, so it should return the duration.
        ASSERT_NO_THROW_LOG(mond = store.addDurationSample(key, five_ms));
        ASSERT_TRUE(mond);

        // Make sure the duration's current interval and prevous intervals correct.
        current_interval = mond->getCurrentInterval();
        ASSERT_TRUE(current_interval);
        EXPECT_EQ(current_interval->getOccurrences(), 1);
        EXPECT_EQ(current_interval->getTotalDuration(), (five_ms));

        previous_interval = mond->getPreviousInterval();
        ASSERT_TRUE(previous_interval);
        EXPECT_EQ(previous_interval->getOccurrences(), 2);
        EXPECT_EQ(previous_interval->getTotalDuration(), (five_ms) * 2);
    }

    /// @brief Veriries getReportsNext and getOverdueReports
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void reportDueTest(uint16_t family) {
        // Create a store.
        Duration interval_duration(milliseconds(100));
        MonitoredDurationStore store(family, interval_duration);

        // Create durations in the store, none of them will have intervals.
        size_t num_subnets = 4;
        std::vector<DurationKeyPtr> keys;
        for (int s = 0; s < num_subnets; ++s) {
            auto key = makeKey(family, s);
            store.addDuration(key);
            keys.push_back(key);
        }

        // No duration should be due to report.
        MonitoredDurationPtr mond;
        ASSERT_NO_THROW_LOG(mond = store.getReportsNext());
        ASSERT_FALSE(mond);

        // No durations should be over due to report.
        MonitoredDurationCollectionPtr durations;
        ASSERT_NO_THROW_LOG(durations = store.getOverdueReports());
        ASSERT_TRUE(durations);
        EXPECT_TRUE(durations->empty());

        // Now add a 5ms sample to all four durations in reverse order
        // This should give us a list of durations (by key) as follows:
        //
        // key[0] - interval start = now + 54ms
        // key[1] - interval start = now + 52ms
        // key[2] - interval start = now + 2ms
        // key[3] - interval start = now
        auto five_ms(milliseconds(5));
        for (auto const& k : boost::adaptors::reverse(keys)) {
            ASSERT_NO_THROW_LOG(store.addDurationSample(k, five_ms));
            if (k->getSubnetId() != 2) {
                usleep(2 * 1000);   // put 2ms gap between them
            } else {
                usleep(50 * 1000);  // put 50ms gap between them.
            }
        }

        // Key[3] should be returned by getReportsNext().
        ASSERT_NO_THROW_LOG(mond = store.getReportsNext());
        ASSERT_TRUE(mond);
        EXPECT_EQ(*mond, *keys[3]) << "mond: " << mond->getLabel();

        // None should be returned by getOverdueReports().
        ASSERT_NO_THROW_LOG(durations = store.getOverdueReports());
        ASSERT_TRUE(durations);
        EXPECT_TRUE(durations->empty());

        // Sleep for 50 ms.
        usleep(50 * 1000);

        // Key[1] should be returned by getReportsNext().
        ASSERT_NO_THROW_LOG(mond = store.getReportsNext());
        ASSERT_TRUE(mond);
        EXPECT_EQ(*mond, *keys[1]) << "mond: " << mond->getLabel();

        // Key[3] and key[2] should be returned by getOverdueReports().
        ASSERT_NO_THROW_LOG(durations = store.getOverdueReports());
        ASSERT_TRUE(durations);
        EXPECT_EQ(durations->size(), 2);
        EXPECT_EQ(*(*durations)[0], *keys[3]);
        EXPECT_EQ(*(*durations)[1], *keys[2]);

        // Sleep for 50 ms.
        usleep(50 * 1000);

        // None should report as reports next.
        ASSERT_NO_THROW_LOG(mond = store.getReportsNext());
        ASSERT_FALSE(mond);

        // All should be found overdue.
        ASSERT_NO_THROW_LOG(durations = store.getOverdueReports());
        ASSERT_TRUE(durations);
        EXPECT_EQ(durations->size(), keys.size());
        EXPECT_EQ(*(*durations)[0], *keys[3]);
        EXPECT_EQ(*(*durations)[1], *keys[2]);
        EXPECT_EQ(*(*durations)[2], *keys[1]);
        EXPECT_EQ(*(*durations)[3], *keys[0]);
    }

    /// @brief Test tool for gauging speed.
    ///
    /// This test is really just a development tool for gauging performance.
    /// of adding duration samples. It does not pass or fail and thus is not
    /// included in explicit UTs.
    ///
    /// @param family protocol family to test, AF_INET or AF_INET6
    void speedCheck(uint16_t family) {
        // Create a store.
        Duration interval_duration(microseconds(100));
        MonitoredDurationStore store(family, interval_duration);

        // Create keys.
        size_t num_subnets = 100;
        std::vector<DurationKeyPtr> keys;

        for (int s = 0; s < num_subnets; ++s) {
            keys.push_back(makeKey(family, s));
        }

        auto start_time = PktEvent::now();

        for (auto k : keys) {
            store.addDuration(k);
        }

        auto add_keys_time = PktEvent::now();

        size_t num_passes = 100;
        size_t report_count = 0;
        Duration two_us(microseconds(2));
        for (int p = 0; p < num_passes; ++p) {
            for (auto k : keys) {
                if (store.addDurationSample(k, two_us)) {
                    ++report_count;
                }
            }
        }

        auto add_samples_time = PktEvent::now();

        EXPECT_GT(report_count, 0);
        auto durations = store.getAll();
        EXPECT_EQ(durations->size(), num_subnets);

        std::cout << "report count: " << report_count << std::endl
                  << "add keys time: " << (add_keys_time - start_time) << std::endl
                  << "add samples time: " << (add_samples_time - add_keys_time) << std::endl
                  << "time per sample: "
                  << (add_samples_time - add_keys_time) / (num_subnets * num_passes) << std::endl;
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

TEST_F(MonitoredDurationStoreTest, updateDurationInvalid) {
    updateDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, updateDurationInvalidMultiThreading) {
    MultiThreadingTest mt;
    updateDurationInvalidTest();
}

TEST_F(MonitoredDurationStoreTest, addDurationSample) {
    addDurationSampleTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, addDurationSampleMultiThreading) {
    MultiThreadingTest mt;
    addDurationSampleTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, addDurationSample6) {
    addDurationSampleTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, addDurationSample6MultiThreading) {
    MultiThreadingTest mt;
    addDurationSampleTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, reportDue) {
    reportDueTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, reportDueMultiThreading) {
    MultiThreadingTest mt;
    reportDueTest(AF_INET);
}

TEST_F(MonitoredDurationStoreTest, reportDue6) {
    reportDueTest(AF_INET6);
}

TEST_F(MonitoredDurationStoreTest, reportDue6MultiThreading) {
    MultiThreadingTest mt;
    reportDueTest(AF_INET6);
}

} // end of anonymous namespace
