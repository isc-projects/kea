// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option.h>
#include <dhcp6/client_handler.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <stats/stats_mgr.h>
#include <util/multi_threading_mgr.h>
#include <unistd.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;
using namespace isc::util;

namespace {

/// @brief Test fixture class for testing client handler.
class ClientHandleTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates the pkt6-receive-drop statistic.
    ClientHandleTest() : called1_(false), called2_(false), called3_(false) {
        MultiThreadingMgr::instance().apply(false, 0, 0);
        StatsMgr::instance().setValue("pkt6-receive-drop", static_cast<int64_t>(0));
    }

    /// @brief Destructor.
    ///
    /// Removes statistics.
    ~ClientHandleTest() {
        MultiThreadingMgr::instance().apply(false, 0, 0);
        StatsMgr::instance().removeAll();
    }

    /// @brief Generates a client-id option.
    ///
    /// (from dhcp6_test_utils.h)
    ///
    /// @return A random client-id option.
    OptionPtr generateClientId(uint8_t base = 100) {
        const size_t len = 32;
        OptionBuffer duid(len);
        for (size_t i = 0; i < len; ++i) {
            duid[i] = base + i;
        }
        return (OptionPtr(new Option(Option::V6, D6O_CLIENTID, duid)));
    }

    /// @brief Check statistics.
    ///
    /// @param bumped True if pkt6-receive-drop should have been bumped by one,
    /// false otherwise.
    void checkStat(bool bumped) {
        ObservationPtr obs = StatsMgr::instance().getObservation("pkt6-receive-drop");
        ASSERT_TRUE(obs);
        if (bumped) {
            EXPECT_EQ(1, obs->getInteger().first);
        } else {
            EXPECT_EQ(0, obs->getInteger().first);
        }
    }

    /// @brief Waits for pending continuations.
    void waitForThreads() {
        MultiThreadingMgr::instance().getThreadPool().wait(3);
    }

    /// @brief Set called1_ to true.
    void setCalled1() {
        called1_ = true;
    }

    /// @brief Set called2_ to true.
    void setCalled2() {
        called2_ = true;
    }

    /// @brief Set called3_ to true.
    void setCalled3() {
        called3_ = true;
    }

    /// @brief The called flag number 1.
    bool called1_;

    /// @brief The called flag number 2.
    bool called2_;

    /// @brief The called flag number 3.
    bool called3_;
};

// Verifies behavior with empty block.
TEST_F(ClientHandleTest, empty) {
    try {
        // Get a client handler.
        ClientHandler client_handler;
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(false);
}

// Verifies behavior with one query.
TEST_F(ClientHandleTest, oneQuery) {
    // Get a query.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->addOption(generateClientId());

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(false);
}

// Verifies behavior with two queries for the same client.
TEST_F(ClientHandleTest, sharedQueries) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req));

        // Should return true (race with the duplicate).
        EXPECT_TRUE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(true);
}

// Verifies behavior with a sequence of two queries.
TEST_F(ClientHandleTest, sequence) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }

    // As it is a different block the lock was released.

    try {
        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(false);
}

// Verifies behavior with different clients.
TEST_F(ClientHandleTest, notSharedQueries) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    OptionPtr client_id = generateClientId();
    OptionPtr client_id2 = generateClientId(111);
    // Different client ID: different client.
    sol->addOption(client_id);
    req->addOption(client_id2);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(false);
}

// Verifies behavior without client ID.
TEST_F(ClientHandleTest, noClientId) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    // No client id: nothing to recognize the client.

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(false);
}

// Verifies the query is required.
TEST_F(ClientHandleTest, noQuery) {
    Pkt6Ptr no_pkt;

    try {
        // Get a client handler.
        ClientHandler client_handler;

        EXPECT_THROW(client_handler.tryLock(no_pkt), InvalidParameter);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies that double tryLock call fails.
TEST_F(ClientHandleTest, doubleTryLock) {
    // Get a query.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    sol->addOption(generateClientId());

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Try to lock a second time.
        EXPECT_THROW(client_handler.tryLock(sol), Unexpected);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Cannot verifies that empty client ID fails because getClientId() handles
// this condition and replaces it by no client ID.

// Verifies behavior with two queries for the same client and multi-threading.
TEST_F(ClientHandleTest, serializeTwoQueries) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol, cont1));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Create a continuation.
        ContinuationPtr cont2 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled2, this));

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req, cont2));

        // Should return true (race with the duplicate).
        EXPECT_TRUE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }

    // Give the second continuation a chance.
    waitForThreads();

    // Force multi-threading to stop;
    MultiThreadingCriticalSection cs;

    checkStat(false);
    EXPECT_FALSE(called1_);
    EXPECT_TRUE(called2_);
}

// Verifies behavior with two queries for the same client and multi-threading.
// Continuations are required for serialization.
TEST_F(ClientHandleTest, serializeNoCont) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req));

        // Should return true (race with the duplicate).
        EXPECT_TRUE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }

    // Give the second continuation a chance even there is none...
    waitForThreads();

    // Force multi-threading to stop;
    MultiThreadingCriticalSection cs;

    checkStat(true);
}

// Verifies behavior with three queries for the same client and
// multi-threading: currently we accept only two queries,
// a third one replaces second so we get the first (oldest) query and
// the last (newest) query when the client is busy.
TEST_F(ClientHandleTest, serializeThreeQueries) {
    // Get two queries.
    Pkt6Ptr sol(new Pkt6(DHCPV6_SOLICIT, 1234));
    Pkt6Ptr req(new Pkt6(DHCPV6_REQUEST, 2345));
    Pkt6Ptr ren(new Pkt6(DHCPV6_RENEW, 3456));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);
    ren->addOption(client_id);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the solicit.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(sol, cont1));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Create a continuation.
        ContinuationPtr cont2 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled2, this));

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = !client_handler2.tryLock(req, cont2));

        // Should return true (race with the duplicate).
        EXPECT_TRUE(duplicate);

        // Get a third client handler.
        ClientHandler client_handler3;

        // Create a continuation.
        ContinuationPtr cont3 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled3, this));

        // Try to lock it with a renew.
        EXPECT_NO_THROW(duplicate = !client_handler3.tryLock(ren, cont3));

        // Should return true (race with the duplicate).
        EXPECT_TRUE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }

    // Give the second continuation a chance.
    waitForThreads();

    // Force multi-threading to stop;
    MultiThreadingCriticalSection cs;

    checkStat(true);
    EXPECT_FALSE(called1_);
    EXPECT_FALSE(called2_);
    EXPECT_TRUE(called3_);
}

} // end of anonymous namespace
