// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PingContextStore class.

#include <config.h>
#include <ping_context_store.h>
#include <asiolink/io_address.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::ping_check;
using namespace isc::test;
using namespace std::chrono;

namespace {

/// @brief Text fixture class for @c PingContextStore
///
/// In order to facilitate single and multi threaded testing,
/// individual tests are implemented as methods that are called
/// from within TEST_F bodies rather than in TEST_F bodies.
class PingContextStoreTest : public ::testing::Test {
public:

    /// @brief Constructor
    PingContextStoreTest() {
    }

    /// @brief Destructor
    virtual ~PingContextStoreTest() = default;

    /// @brief Verifies that contexts can be added to the store given valid leases and queries.
    /// Also verifies that they can be fetched by address.
    void addContextTest() {
        PingContextStore store;
        PingContextPtr context;

        // Add three contexts, one for each lease/query.
        auto now = PingContext::now();
        for (int i = 0; i < leases_.size(); ++i) {
            ASSERT_NO_THROW_LOG(context = store.addContext(leases_[i], queries_[i], 2, 300));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());

            // Check initial values.
            EXPECT_EQ(PingContext::WAITING_TO_SEND, context->getState());
            EXPECT_LE(now, context->getSendWaitStart());
            EXPECT_EQ(2, context->getMinEchos());
            EXPECT_EQ(300, context->getReplyTimeout());
        }

        // Make sure they can be fetched by address and by query individually.
        for (int i = 0; i < leases_.size(); ++i) {
            ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[i]->addr_));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());

            ASSERT_NO_THROW_LOG(context = store.getContextByQuery(queries_[i]));
            ASSERT_TRUE(context);
            EXPECT_EQ(queries_[i], context->getQuery());
        }
    }

    /// @brief Verifies that the store only allows once entry per IP address.
    void addContextDuplicateTest() {
        PingContextStore store;
        PingContextPtr context;

        ASSERT_NO_THROW_LOG(context = store.addContext(leases_[0], queries_[0], 1, 100));
        ASSERT_TRUE(context);
        ASSERT_THROW_MSG(store.addContext(leases_[0], queries_[0], 1, 100), DuplicateContext,
                         "PingContextStore::addContex: context already exists for: 192.0.2.1");
    }

    /// @brief Verify that addContext fails given invalid input.
    void addContextInvalidTest() {
        PingContextStore store;

        // Verify that given an empty lease the add will fail.
        Lease4Ptr empty_lease;
        ASSERT_THROW_MSG(store.addContext(empty_lease, queries_[0], 1, 100), BadValue,
                                          "PingContextStore::addContext failed:"
                                          " PingContext ctor - lease cannot be empty");

        // Verify that given an empty query the add will fail.
        Pkt4Ptr empty_query;
        ASSERT_THROW_MSG(store.addContext(leases_[0], empty_query, 1, 100), BadValue,
                                          "PingContextStore::addContext failed:"
                                          " PingContext ctor - query cannot be empty");
    }

    /// @brief Verify that contexts can be deleted from the store.
    void deleteContextTest() {
        PingContextStore store;

        // Add contexts to store.
        for (int i = 0; i < leases_.size(); ++i) {
            PingContextPtr context;
            ASSERT_NO_THROW_LOG(context = store.addContext(leases_[i], queries_[i], 1, 100));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
        }

        // Fetch the second context.
        PingContextPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = store.getContextByAddress(leases_[1]->addr_));
        ASSERT_TRUE(orig_context);
        EXPECT_EQ(leases_[1], orig_context->getLease());

        // Delete it.
        ASSERT_NO_THROW_LOG(store.deleteContext(orig_context));

        // Try to fetch it, shouldn't find it.
        PingContextPtr context;
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[1]->addr_));
        ASSERT_FALSE(context);

        // Deleting it again should do no harm.
        ASSERT_NO_THROW_LOG(store.deleteContext(orig_context));
    }

    /// @brief Verify that contexts in the store can be updated.
    void updateContextTest() {
        PingContextStore store;
        PingContextPtr context;

        // Try to update a context that doesn't exist. It should throw.
        ASSERT_NO_THROW_LOG(context.reset(new PingContext(leases_[0], queries_[0])));
        ASSERT_THROW_MSG(store.updateContext(context), InvalidOperation,
                         "PingContextStore::updateContext failed for address:"
                         " 192.0.2.1, not in store");

        auto test_start = PingContext::now();

        // Add contexts to store.
        for (int i = 0; i < leases_.size(); ++i) {
            ASSERT_NO_THROW_LOG(context = store.addContext(leases_[i], queries_[i], 1, 100));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
        }

        // Fetch the second context.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[1]->addr_));
        ASSERT_TRUE(context);
        ASSERT_EQ(leases_[1], context->getLease());
        ASSERT_EQ(queries_[1], context->getQuery());

        // Check initial values for state and expiration.
        EXPECT_EQ(PingContext::WAITING_TO_SEND, context->getState());
        EXPECT_LE(test_start, context->getSendWaitStart());
        EXPECT_LE(PingContext::EMPTY_TIME(), context->getNextExpiry());

        // Modify the state and expiration, then update the context.
        auto wait_start = PingContext::now();
        context->beginWaitingForReply(wait_start);
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Fetch the context and verify the values are correct.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[1]->addr_));
        ASSERT_TRUE(context);
        EXPECT_EQ(PingContext::WAITING_FOR_REPLY, context->getState());
        EXPECT_LE(wait_start + milliseconds(context->getReplyTimeout()), context->getNextExpiry());
    }

    /// @brief Verify that contexts can be fetched based on when they entered WAITING_TO_SEND
    /// by getNextToSend().
    void getNextToSendTest() {
        PingContextStore store;
        PingContextPtr context;

        // Capture time now.
        auto start_time = PingContext::now();

        // Add contexts to store.
        for (int i = 0; i < leases_.size(); ++i) {
            ASSERT_NO_THROW_LOG(context = store.addContext(leases_[i], queries_[i], 1, 100));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
            usleep(1000);
        }

        // Fetching the next context to send should return the first context as
        // it has the oldest send wait start time.
        context.reset();
        ASSERT_NO_THROW(context = store.getNextToSend());
        ASSERT_TRUE(context);
        EXPECT_EQ(leases_[0], context->getLease());
        EXPECT_EQ(queries_[0], context->getQuery());
        EXPECT_LE(start_time, context->getSendWaitStart());

        // Update the first context's state  to TARGET_FREE which should
        // disqualify it from being returned as next to send.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[0]->addr_));
        ASSERT_TRUE(context);
        ASSERT_EQ(PingContext::WAITING_TO_SEND, context->getState());
        context->setState(PingContext::TARGET_FREE);
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Update the send wait start of the second context making it the
        // youngest send wait start time.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[1]->addr_));
        ASSERT_TRUE(context);
        ASSERT_EQ(PingContext::WAITING_TO_SEND, context->getState());
        context->setSendWaitStart(start_time + milliseconds(1000));
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Update the send wait start of the third context, making it the oldest.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[2]->addr_));
        ASSERT_TRUE(context);
        ASSERT_EQ(PingContext::WAITING_TO_SEND, context->getState());
        context->setSendWaitStart(start_time + milliseconds(500));
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Fetching the next context to send should return the third context.
        context.reset();
        ASSERT_NO_THROW(context = store.getNextToSend());
        ASSERT_TRUE(context);
        EXPECT_EQ(leases_[2], context->getLease());
        EXPECT_EQ(queries_[2], context->getQuery());
        EXPECT_EQ(start_time + milliseconds(500), context->getSendWaitStart());
    }

    /// @brief Verify that contexts can be fetched based on when they expire using
    /// getExpiresNext() and getExpiredSince().
    void getByExpirationTest() {
        PingContextStore store;
        PingContextPtr context;

        // Add contexts to store.
        for (int i = 0; i < leases_.size(); ++i) {
            ASSERT_NO_THROW_LOG(context = store.addContext(leases_[i], queries_[i], 1, 100));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
        }

        // Capture time now.
        auto start_time = PingContext::now();

        // Update the state and expiration of the first context.
        // State set to TARGET_FREE should disqualify if from
        // fetch by expiration even though it has the soonest expiration
        // time.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[0]->addr_));
        ASSERT_TRUE(context);
        context->setState(PingContext::TARGET_FREE);
        context->setNextExpiry(start_time + milliseconds(1));
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Update the state and expiration of the second context giving it
        // the youngest expiration time.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[1]->addr_));
        ASSERT_TRUE(context);
        context->setState(PingContext::WAITING_FOR_REPLY);
        context->setNextExpiry(start_time + milliseconds(1000));
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Update the state and expiration of the third context, make it the
        // soonest qualified expiration time.
        ASSERT_NO_THROW_LOG(context = store.getContextByAddress(leases_[2]->addr_));
        ASSERT_TRUE(context);
        context->setState(PingContext::WAITING_FOR_REPLY);
        context->setNextExpiry(start_time + milliseconds(500));
        ASSERT_NO_THROW_LOG(store.updateContext(context));

        // Fetching the context that expires next should return the third context.
        context.reset();
        ASSERT_NO_THROW(context = store.getExpiresNext());
        ASSERT_TRUE(context);
        EXPECT_EQ(leases_[2], context->getLease());
        EXPECT_EQ(queries_[2], context->getQuery());
        EXPECT_EQ(start_time + milliseconds(500), context->getNextExpiry());

        // Fetch all that have expired since current time.  Should be none.
        PingContextCollectionPtr expired_since;
        ASSERT_NO_THROW_LOG(expired_since = store.getExpiredSince());
        ASSERT_TRUE(expired_since);
        EXPECT_EQ(0, expired_since->size());

        // Fetch all that have expired since start time + 750 ms, should be third context.
        ASSERT_NO_THROW_LOG(expired_since = store.getExpiredSince(start_time + milliseconds(750)));
        ASSERT_TRUE(expired_since);
        EXPECT_EQ(1, expired_since->size());
        context = (*expired_since)[0];
        EXPECT_EQ(leases_[2], context->getLease());
        EXPECT_EQ(queries_[2], context->getQuery());
        EXPECT_EQ(start_time + milliseconds(500), context->getNextExpiry());

        // Fetch all that have expired since start time + 1500 ms
        // Should be the third and second contexts
        ASSERT_NO_THROW_LOG(expired_since = store.getExpiredSince(start_time + milliseconds(1500)));
        ASSERT_TRUE(expired_since);
        EXPECT_EQ(2, expired_since->size());

        // First in list should be the third context.
        context = (*expired_since)[0];
        EXPECT_EQ(leases_[2], context->getLease());
        EXPECT_EQ(queries_[2], context->getQuery());
        EXPECT_EQ(start_time + milliseconds(500), context->getNextExpiry());

        // The last one in the list should be the second context.
        context = (*expired_since)[1];
        EXPECT_EQ(leases_[1], context->getLease());
        EXPECT_EQ(queries_[1], context->getQuery());
        EXPECT_EQ(start_time + milliseconds(1000), context->getNextExpiry());
    }

    /// @brief Verifies that getAll() and clear() work properly.
    void getAllAndClearTest() {
        PingContextStore store;

        // Add contexts to store.
        for (int i = 0; i < leases_.size(); ++i) {
            PingContextPtr context;
            ASSERT_NO_THROW_LOG(context = store.addContext(leases_[i], queries_[i], 1, 100));
            ASSERT_TRUE(context);
            EXPECT_EQ(leases_[i], context->getLease());
            EXPECT_EQ(queries_[i], context->getQuery());
        }

        // Fetch them all.
        PingContextCollectionPtr contexts;
        ASSERT_NO_THROW_LOG(contexts = store.getAll());
        ASSERT_EQ(leases_.size(), contexts->size());

        // Verify we got them all in order.
        int i = 0;
        for (auto const& context : *contexts) {
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

private:
    /// @brief Prepares the class for a test.
    virtual void SetUp() {
        Lease4Ptr lease;
        lease.reset(new Lease4());
        lease->addr_ = IOAddress("192.0.2.1");
        leases_.push_back(lease);

        lease.reset(new Lease4());
        lease->addr_ = IOAddress("192.0.2.2");
        leases_.push_back(lease);

        lease.reset(new Lease4());
        lease->addr_ = IOAddress("192.0.2.3");
        leases_.push_back(lease);

        Pkt4Ptr query;
        query.reset(new Pkt4(DHCPDISCOVER, 101));
        queries_.push_back(query);

        query.reset(new Pkt4(DHCPDISCOVER, 102));
        queries_.push_back(query);

        query.reset(new Pkt4(DHCPDISCOVER, 103));
        queries_.push_back(query);

        ASSERT_EQ(leases_.size(), queries_.size());
    }

public:
    /// @brief List of pre-made leases.
    std::vector<Lease4Ptr> leases_;

    /// @brief List of pre-made queries.
    std::vector<Pkt4Ptr> queries_;
};

TEST_F(PingContextStoreTest, addContext) {
    addContextTest();
}

TEST_F(PingContextStoreTest, addContextMultiThreading) {
    MultiThreadingTest mt;
    addContextTest();
}

TEST_F(PingContextStoreTest, addContextDuplicate) {
    addContextDuplicateTest();
}

TEST_F(PingContextStoreTest, addContextDuplicateMultiThreading) {
    MultiThreadingTest mt;
    addContextDuplicateTest();
}

TEST_F(PingContextStoreTest, addContextInvalid) {
    addContextInvalidTest();
}

TEST_F(PingContextStoreTest, addContextInvalidMultiThreading) {
    MultiThreadingTest mt;
    addContextInvalidTest();
}

TEST_F(PingContextStoreTest, deleteContext) {
    deleteContextTest();
}

TEST_F(PingContextStoreTest, deleteContextMultiThreading) {
    MultiThreadingTest mt;
    deleteContextTest();
}

TEST_F(PingContextStoreTest, updateContext) {
    updateContextTest();
}

TEST_F(PingContextStoreTest, updateContextMultiThreading) {
    MultiThreadingTest mt;
    updateContextTest();
}

TEST_F(PingContextStoreTest, getNextToSend) {
    getNextToSendTest();
}

TEST_F(PingContextStoreTest, getNextToSendMultiThreading) {
    MultiThreadingTest mt;
    getNextToSendTest();
}

TEST_F(PingContextStoreTest, getByExpiration) {
    getByExpirationTest();
}

TEST_F(PingContextStoreTest, getByExpirationMultiThreading) {
    MultiThreadingTest mt;
    getByExpirationTest();
}

TEST_F(PingContextStoreTest, getAllAndClear) {
    getAllAndClearTest();
}

TEST_F(PingContextStoreTest, getAllAndClearMultiThreading) {
    MultiThreadingTest mt;
    getAllAndClearTest();
}

} // end of anonymous namespace
