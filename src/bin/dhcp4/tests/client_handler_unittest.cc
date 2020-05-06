// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option.h>
#include <dhcp4/client_handler.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
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
    /// Creates the pkt4-receive-drop statistic.
    ClientHandleTest() {
        StatsMgr::instance().setValue("pkt4-receive-drop", static_cast<int64_t>(0));
    }

    /// @brief Destructor.
    ///
    /// Removes statistics.
    ~ClientHandleTest() {
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
    /// @param bumped True if pkt4-receive-drop shoud have been bumped by one,
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
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    sol->addOption(generateClientId());
    sol->setHWAddr(generateHWAddr());

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

// Verifies behavior with two queries for the same client (id).
TEST_F(ClientHandleTest, sharedQueriesById) {
    // Get two queries.
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);
    sol->setHWAddr(generateHWAddr());
    req->setHWAddr(generateHWAddr(55));

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

// Verifies behavior with two queries for the same client (hw).
TEST_F(ClientHandleTest, sharedQueriesByHWAddr) {
    // Get two queries.
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    sol->addOption(generateClientId());
    req->addOption(generateClientId(111));
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    sol->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

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

// Verifies behavior with two queries for the same client (hw only).
TEST_F(ClientHandleTest, sharedQueriesByHWAddrOnly) {
    // Get two queries.
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    // No client ID.
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    sol->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

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
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    // Same client ID: same client.
    sol->addOption(client_id);
    req->addOption(client_id);
    HWAddrPtr hwaddr = generateHWAddr();
    // Same hardware address: same client.
    sol->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr);

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
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    OptionPtr client_id = generateClientId();
    OptionPtr client_id2 = generateClientId(111);
    HWAddrPtr hwaddr = generateHWAddr();
    HWAddrPtr hwaddr1 = generateHWAddr(55);
    // Different client ID and hardware address: different client.
    sol->addOption(client_id);
    req->addOption(client_id2);
    sol->setHWAddr(hwaddr);
    req->setHWAddr(hwaddr1);

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

// Verifies behavior without client ID nor hardware address.
TEST_F(ClientHandleTest, noClientIdHWAddr) {
    // Get two queries.
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    Pkt4Ptr req(new Pkt4(DHCPREQUEST, 2345));
    // No client id nor hardware address: nothing to recognize the client.

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
    Pkt4Ptr no_pkt;

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
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
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

// Verifies that double tryLock call fails (hw only).
TEST_F(ClientHandleTest, doubleTryLockByHWAddr) {
    // Get a query without a client ID.
    Pkt4Ptr sol(new Pkt4(DHCPDISCOVER, 1234));
    sol->setHWAddr(generateHWAddr());

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
