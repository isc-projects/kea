// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option.h>
#include <dhcp4/client_handler.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
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
    /// Creates the pkt4-receive-drop statistic.
    ClientHandleTest() : called1_(false), called2_(false), called3_(false) {
        MultiThreadingMgr::instance().apply(false, 0, 0);
        StatsMgr::instance().setValue("pkt4-receive-drop", static_cast<int64_t>(0));
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
    /// (from dhcp4_test_utils.h)
    ///
    /// @return A random client-id option.
    OptionPtr generateClientId(uint8_t base = 100) {
        const size_t len = 32;
        OptionBuffer duid(len);
        for (size_t i = 0; i < len; ++i) {
            duid[i] = base + i;
        }
        return (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, duid)));
    }

    /// @brief Generates a hardware address.
    ///
    /// (from dhcp4_test_utils.h)
    ///
    /// @return A random hardware address.
    HWAddrPtr generateHWAddr(uint8_t base = 50) {
        const uint16_t hw_type = 6;
        const size_t len = 6;
        OptionBuffer mac(len);
        for (size_t i = 0; i < len; ++i) {
            mac[i] = base + i;
        }
        return (HWAddrPtr(new HWAddr(mac, hw_type)));
    }

    /// @brief Check statistics.
    ///
    /// @param bumped True if pkt4-receive-drop should have been bumped by one,
    /// false otherwise.
    void checkStat(bool bumped) {
        ObservationPtr obs = StatsMgr::instance().getObservation("pkt4-receive-drop");
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
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    dis->addOption(generateClientId());
    dis->setHWAddr(generateHWAddr());

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
    checkStat(false);
}

// Verifies behavior with two queries for the same client (id).
TEST_F(ClientHandleTest, sharedQueriesById) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    dis->addOption(client_id);
    req->addOption(client_id);
    dis->setHWAddr(generateHWAddr());
    req->setHWAddr(generateHWAddr(55));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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

// Verifies behavior with two queries for the same client (hw).
TEST_F(ClientHandleTest, sharedQueriesByHWAddr) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    dis->addOption(generateClientId());
    req->addOption(generateClientId(111));
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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

// Verifies behavior with two queries for the same client (hw only).
TEST_F(ClientHandleTest, sharedQueriesByHWAddrOnly) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    // No client ID.
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    dis->addOption(client_id);
    req->addOption(client_id);
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    OptionPtr client_id2 = generateClientId(111);
    HWAddrPtr hwaddr = generateHWAddr();
    HWAddrPtr hwaddr1 = generateHWAddr(55);
    // Different client ID and hardware address: different client.
    dis->addOption(client_id);
    req->addOption(client_id2);
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr1);

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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

// Verifies behavior without client ID nor hardware address.
TEST_F(ClientHandleTest, noClientIdHWAddr) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    // No client id nor hardware address: nothing to recognize the client.

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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
    Pkt4Ptr no_pkt;

    try {
        // Get a client handler.
        ClientHandler client_handler;

        EXPECT_THROW(client_handler.tryLock(no_pkt), InvalidParameter);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies that double tryLock call fails (id only).
TEST_F(ClientHandleTest, doubleTryLockById) {
    // Get a query.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    dis->addOption(generateClientId());

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Try to lock a second time.
        EXPECT_THROW(client_handler.tryLock(dis), Unexpected);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies that double tryLock call fails (hw only).
TEST_F(ClientHandleTest, doubleTryLockByHWAddr) {
    // Get a query without a client ID.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    dis->setHWAddr(generateHWAddr());

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Try to lock a second time.
        EXPECT_THROW(client_handler.tryLock(dis), Unexpected);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Cannot verifies that empty client ID fails because getClientId() handles
// this condition and replaces it by no client ID.

// Verifies behavior with two queries for the same client and
// multi-threading, by client id option version.
TEST_F(ClientHandleTest, serializeTwoQueriesById) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    dis->addOption(client_id);
    req->addOption(client_id);
    dis->setHWAddr(generateHWAddr());
    req->setHWAddr(generateHWAddr(55));

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis, cont1));

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

// Verifies behavior with two queries for the same client and
// multi-threading, by hardware address version.
TEST_F(ClientHandleTest, serializeTwoQueriesByHWAddr) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    dis->addOption(generateClientId());
    req->addOption(generateClientId(111));
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis, cont1));

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
// Continuations are required for serialization. By client id option version.
TEST_F(ClientHandleTest, serializeNoContById) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    dis->addOption(client_id);
    req->addOption(client_id);
    dis->setHWAddr(generateHWAddr());
    req->setHWAddr(generateHWAddr(55));

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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

// Verifies behavior with two queries for the same client and multi-threading.
// Continuations are required for serialization. By hardware address version.
TEST_F(ClientHandleTest, serializeNoContByHWAddr) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    dis->addOption(generateClientId());
    req->addOption(generateClientId(111));
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis));

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
// By client id option version.
TEST_F(ClientHandleTest, serializeThreeQueriesById) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    Pkt4Ptr rel(new Pkt4(DHCPRELEASE, 3456));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    dis->addOption(client_id);
    req->addOption(client_id);
    rel->addOption(client_id);
    dis->setHWAddr(generateHWAddr());
    req->setHWAddr(generateHWAddr(55));
    rel->setHWAddr(generateHWAddr(66));

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis, cont1));

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

        // Try to lock it with a release.
        EXPECT_NO_THROW(duplicate = !client_handler3.tryLock(rel, cont3));

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

// Verifies behavior with three queries for the same client and
// multi-threading: currently we accept only two queries,
// a third one replaces second so we get the first (oldest) query and
// the last (newest) query when the client is busy.
// By hardware address version.
TEST_F(ClientHandleTest, serializeThreeQueriesHWAddr) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    Pkt4Ptr rel(new Pkt4(DHCPRELEASE, 3456));
    dis->addOption(generateClientId());
    req->addOption(generateClientId(111));
    rel->addOption(generateClientId(99));
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);
    rel->setHWAddr(hwaddr);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis, cont1));

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

        // Try to lock it with a release.
        EXPECT_NO_THROW(duplicate = !client_handler3.tryLock(rel, cont3));

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

// Verifies behavior with three queries for the same client and
// multi-threading: currently we accept only two queries,
// a third one replaces second so we get the first (oldest) query and
// the last (newest) query when the client is busy.
// Mixed version (hardware address then client id option duplicates).
// Note the system is transitive because further races are detected
// when serialized packet processing is performed.
TEST_F(ClientHandleTest, serializeThreeQueriesMixed) {
    // Get two queries.
    Pkt4Ptr dis(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    Pkt4Ptr rel(new Pkt4(DHCPRELEASE, 3456));
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client for discover and request.
    dis->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);
    rel->setHWAddr(generateHWAddr(55));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client for discover and release.
    dis->addOption(client_id);
    req->addOption(generateClientId(111));
    rel->addOption(client_id);

    // Start multi-threading.
    EXPECT_NO_THROW(MultiThreadingMgr::instance().apply(true, 1, 0));

    try {
        // Get a client handler.
        ClientHandler client_handler;

        // Create a continuation.
        ContinuationPtr cont1 =
            makeContinuation(std::bind(&ClientHandleTest::setCalled1, this));

        // Try to lock it with the discover.
        bool duplicate = false;
        EXPECT_NO_THROW(duplicate = !client_handler.tryLock(dis, cont1));

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

        // Try to lock it with a release.
        EXPECT_NO_THROW(duplicate = !client_handler3.tryLock(rel, cont3));

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
