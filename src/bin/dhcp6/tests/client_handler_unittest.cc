// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option.h>
#include <dhcp6/client_handler.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <stats/stats_mgr.h>

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
    ClientHandleTest() {
        StatsMgr::instance().setValue("pkt6-receive-drop", static_cast<int64_t>(0));
    }

    /// @brief Destructor.
    ///
    /// Removes statistics.
    ~ClientHandleTest() {
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
    /// @param bumped True if pkt6-receive-drop shoud have been bumped by one,
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
};

// Verifies behavior with empty block.
TEST_F(ClientHandleTest, empty) {
    try {
        // Get a client handler.
        ClientHandler client_handler;
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
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
        EXPECT_NO_THROW(duplicate = client_handler.tryLock(sol));

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
        EXPECT_NO_THROW(duplicate = client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = client_handler2.tryLock(req));

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
        EXPECT_NO_THROW(duplicate = client_handler.tryLock(sol));

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
        EXPECT_NO_THROW(duplicate = client_handler2.tryLock(req));

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
        EXPECT_NO_THROW(duplicate = client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = client_handler2.tryLock(req));

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
        EXPECT_NO_THROW(duplicate = client_handler.tryLock(sol));

        // Should return false (no duplicate).
        EXPECT_FALSE(duplicate);

        // Get a second client handler.
        ClientHandler client_handler2;

        // Try to lock it with a request.
        EXPECT_NO_THROW(duplicate = client_handler2.tryLock(req));

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
        EXPECT_NO_THROW(duplicate = client_handler.tryLock(sol));

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

} // end of anonymous namespace
