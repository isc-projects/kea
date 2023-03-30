// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/pgsql_lease_mgr.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp;
using namespace isc::test;
using namespace isc::util;
using namespace std;

namespace {

/// @brief IPv4 addresses used in the tests.
const vector<string> ADDRESS4 = {
    "192.0.2.0", "192.0.2.1", "192.0.2.2", "192.0.2.3",
    "192.0.2.4", "192.0.2.5", "192.0.2.6", "192.0.2.7"
};

/// @brief DUIDs used in the tests.
const vector<string> DUIDS = {
    "wwwwwwww", "BBBBBBBB", "::::::::", "0123456789acdef",
    "BBBBBBBB", "$$$$$$$$", "^^^^^^^^", "\xe5\xe5\xe5\xe5\xe5\xe5\xe5\xe5"
};

/// @brief Test fixture class for extended info tests.
class PgSqlExtendedInfoTest : public ::testing::Test {
public:
    /// @brief Constructor.
    PgSqlExtendedInfoTest() {
        // Ensure we have the proper schema with no transient data.
        createPgSQLSchema();

        // Connect to the database.
        try {
            LeaseMgrFactory::create(validPgSQLConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the PostgreSQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        lease_mgr_ = &(LeaseMgrFactory::instance());
        leases4.clear();
        MultiThreadingMgr::instance().setMode(false);
        now_ = time(0);
    }

    /// @brief Destructor.
    ~PgSqlExtendedInfoTest() {
        LeaseMgrFactory::destroy();
        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        destroyPgSQLSchema();

        leases4.clear();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Create and set v4 leases.
    ///
    /// @param insert When true insert in the database.
    void initLease4(bool insert = true) {
        ASSERT_EQ(ADDRESS4.size(), DUIDS.size());
        for (size_t i = 0; i < ADDRESS4.size(); ++i) {
            Lease4Ptr lease;
            vector<uint8_t> hwaddr_data(5, 0x08);
            hwaddr_data.push_back(0x80 + i);
            HWAddrPtr hwaddr(new HWAddr(hwaddr_data, HTYPE_ETHER));
            vector<uint8_t> client_id = createFromString(DUIDS[i]);
            IOAddress address(ADDRESS4[i]);
            ASSERT_NO_THROW(lease.reset(new Lease4(address, hwaddr,
                                                   &client_id[0],
                                                   client_id.size(),
                                                   1000, now_,
                                                   static_cast<SubnetID>(i))));
            leases4.push_back(lease);
            if (insert) {
                EXPECT_TRUE(lease_mgr_->addLease(lease));
            }
        }
        ASSERT_EQ(ADDRESS4.size(), leases4.size());
    }

    /// @brief Create a vector of uint8_t from a string.
    ///
    /// @param content A not empty string holding the content.
    /// @return A vector of uint8_t with the given content.
    inline vector<uint8_t> createFromString(const string& content) {
        vector<uint8_t> v;
        v.resize(content.size());
        memmove(&v[0], &content[0], v.size());
        return (v);
    }

    /// @brief Test initLease4.
    void testInitLease4();

    /// @brief Test getLease4ByRelayId.
    void testGetLeases4ByRelayId();

    /// @brief Test getLease4ByRemoteId.
    void testGetLeases4ByRemoteId();

    /// @brief Lease manager.
    LeaseMgr* lease_mgr_;

    /// @brief V4 leases.
    Lease4Collection leases4;

    /// @brief Current timestamp.
    time_t now_;
};

/// @brief Verifies that the lease manager can add the v4 leases.
void
PgSqlExtendedInfoTest::testInitLease4() {
    initLease4();
    EXPECT_EQ(8, leases4.size());
    IOAddress zero = IOAddress::IPV4_ZERO_ADDRESS();
    Lease4Collection got;
    // Use the page version as it returns leases in order.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4(zero, LeasePageSize(100)));
    ASSERT_EQ(leases4.size(), got.size());
    for (size_t i = 0; i < leases4.size(); ++i) {
        ConstElementPtr expected = leases4[i]->toElement();
        LeasePtr lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_TRUE(expected->equals(*lease->toElement()))
            << "expected: " << expected->str() << "\n"
            << "got: " << lease->toElement()->str() << "\n";
    }
}

TEST_F(PgSqlExtendedInfoTest, initLease4) {
    testInitLease4();
}

TEST_F(PgSqlExtendedInfoTest, initLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testInitLease4();
}

/// @brief Verifies that getLeases4ByRelayId works as expected.
void
PgSqlExtendedInfoTest::testGetLeases4ByRelayId() {
    // Lease manager is created with empty tables.
    initLease4(false);

    // Create leases.
    IOAddress addr0(ADDRESS4[0]);
    IOAddress addr1(ADDRESS4[1]);
    IOAddress addr2(ADDRESS4[2]);
    IOAddress addr3(ADDRESS4[3]);
    IOAddress addr4(ADDRESS4[4]);
    IOAddress zero = IOAddress::IPV4_ZERO_ADDRESS();
    vector<uint8_t> relay_id0 = { 0xaa, 0xbb, 0xcc };
    vector<uint8_t> relay_id1 = { 1, 2, 3, 4 };
    vector<uint8_t> relay_id2 = createFromString(DUIDS[2]);
    string user_context_txt0 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt0 += " \"sub-options\": \"0C03AABBCC\",";
    user_context_txt0 += " \"relay-id\": \"AABBCC\" } } }";
    ElementPtr user_context0;
    ASSERT_NO_THROW(user_context0 = Element::fromJSON(user_context_txt0));
    string user_context_txt1 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt1 += " \"sub-options\": \"0C0401020304\",";
    user_context_txt1 += " \"relay-id\": \"01020304\" } } }";
    ElementPtr user_context1;
    ASSERT_NO_THROW(user_context1 = Element::fromJSON(user_context_txt1));

    Lease4Ptr lease;
    // lease0: addr0, id0, now.
    lease = leases4[0];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id0;
    lease->setContext(user_context0);

    // lease1: addr1, id1, now.
    lease = leases4[1];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id1;
    lease->setContext(user_context1);

    // lease2: addr2, id0, now - 500.
    lease = leases4[2];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 500;

    // lease3: addr3, id0, now - 800.
    lease = leases4[3];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 800;

    // lease4: addr4, id0, now - 100.
    lease = leases4[4];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 100;

    // Add leases.
    for (size_t i = 0; i < leases4.size(); ++i) {
        EXPECT_TRUE(lease_mgr_->addLease(leases4[i]));
    }

    Lease4Collection got;
    // Unknown relay id #2: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id2,
                                                          zero,
                                                          LeasePageSize(100)));
    EXPECT_EQ(0, got.size());

    // Unknown relay id #2, now - 1000, now + 1000: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id2,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ - 1000,
                                                          now_ + 1000));
    EXPECT_EQ(0, got.size());

    // Relay id #0, now - 2000, now - 1000: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ - 2000,
                                                          now_ - 1000));
    EXPECT_EQ(0, got.size());

    // Relay id #0, now + 1000, now + 2000: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ + 1000,
                                                          now_ + 2000));
    EXPECT_EQ(0, got.size());

    // Relay id #0: 3 entries (0, 2, 3, 4).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(100)));
    ASSERT_EQ(4, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[2];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[3]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[3];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, partial: 2 entries (0, 2).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, partial from previous: 2 entries (3, 4).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          addr2,
                                                          LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[3]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, final partial: no entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          addr4,
                                                          LeasePageSize(2)));
    EXPECT_EQ(0, got.size());

    // Relay id #0, from now - 500: 3 entries (0, 2, 4).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ - 500));
    ASSERT_EQ(3, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[2];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, to now - 200: 3 entries (2, 3).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          0, now_ - 200));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(relay_id0, lease->relay_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[3]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, from now - 500 to now - 100, partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(1),
                                                          now_ - 500,
                                                          now_ - 100));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, from now - 500 to now - 100, partial from 2: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          addr2,
                                                          LeasePageSize(1),
                                                          now_ - 500,
                                                          now_ - 100));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(relay_id0, lease->relay_id_);

    // Relay id #0, from now - 500 to now - 100, final partial.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRelayId(relay_id0,
                                                          addr4,
                                                          LeasePageSize(1),
                                                          now_ - 500,
                                                          now_ - 100));
    EXPECT_EQ(0, got.size());
}

TEST_F(PgSqlExtendedInfoTest, getLeases4ByRelayId) {
    testGetLeases4ByRelayId();
}

TEST_F(PgSqlExtendedInfoTest, getLeases4ByRelayIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRelayId();
}

/// @brief Verifies that getLeases4ByRemoteId works as expected.
void
PgSqlExtendedInfoTest::testGetLeases4ByRemoteId() {
    // Lease manager is created with empty tables.
    initLease4(true);

    // Update leases.
    IOAddress addr0(ADDRESS4[0]);
    IOAddress addr1(ADDRESS4[1]);
    IOAddress addr2(ADDRESS4[2]);
    IOAddress addr3(ADDRESS4[3]);
    IOAddress addr4(ADDRESS4[4]);
    IOAddress zero = IOAddress::IPV4_ZERO_ADDRESS();
    vector<uint8_t> remote_id0 = { 1, 2, 3, 4 };
    vector<uint8_t> remote_id1 = { 0xaa, 0xbb, 0xcc };
    vector<uint8_t> remote_id2 = createFromString(DUIDS[2]);
    string user_context_txt0 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt0 += " \"sub-options\": \"020401020304\",";
    user_context_txt0 += " \"remote-id\": \"01020304\" } } }";
    ElementPtr user_context0;
    ASSERT_NO_THROW(user_context0 = Element::fromJSON(user_context_txt0));
    string user_context_txt1 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt1 += " \"sub-options\": \"0203AABBCC\",";
    user_context_txt1 += " \"remote-id\": \"AABBCC\" } } }";
    ElementPtr user_context1;
    ASSERT_NO_THROW(user_context1 = Element::fromJSON(user_context_txt1));

    Lease4Ptr lease;
    // lease0: addr0, id0, now.
    lease = leases4[0];
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);

    // lease1: addr1, id1, now.
    lease = leases4[1];
    lease->remote_id_ = remote_id1;
    lease->setContext(user_context1);

    // lease2: addr2, id0, now - 500.
    lease = leases4[2];
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 500;

    // lease3: addr3, id0, now - 800.
    lease = leases4[3];
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 800;

    // lease4: addr4, id0, now - 100.
    lease = leases4[4];
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 100;

    // Update leases.
    for (size_t i = 0; i < leases4.size(); ++i) {
        EXPECT_NO_THROW(lease_mgr_->updateLease4(leases4[i]));
    }

    Lease4Collection got;
    // Unknown remote id #2: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id2,
                                                          zero,
                                                          LeasePageSize(100)));
    EXPECT_EQ(0, got.size());

    // Unknown remote id #2, now - 1000, now + 1000: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id2,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ - 1000,
                                                          now_ + 1000));
    EXPECT_EQ(0, got.size());

    // Remote id #0, now - 2000, now - 1000: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ - 2000,
                                                          now_ - 1000));
    EXPECT_EQ(0, got.size());

    // Remote id #0, now + 1000, now + 2000: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ + 1000,
                                                          now_ + 2000));
    EXPECT_EQ(0, got.size());

    // Remote id #0: 3 entries (0, 2, 3, 4).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(100)));
    ASSERT_EQ(4, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[2];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[3]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[3];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, partial: 2 entries (0, 2).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, partial from previous: 2 entries (3, 4).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          addr2,
                                                          LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[3]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, final partial: no entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          addr4,
                                                          LeasePageSize(2)));
    EXPECT_EQ(0, got.size());

    // Remote id #0, from now - 500: 3 entries (0, 2, 4).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          now_ - 500));
    ASSERT_EQ(3, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[2];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, to now - 200: 3 entries (2, 3).
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(100),
                                                          0, now_ - 200));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(remote_id0, lease->remote_id_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[3]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, from now - 500 to now - 100, partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          zero,
                                                          LeasePageSize(1),
                                                          now_ - 500,
                                                          now_ - 100));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[2]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, from now - 500 to now - 100, partial from 2: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          addr2,
                                                          LeasePageSize(1),
                                                          now_ - 500,
                                                          now_ - 100));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(*lease, *leases4[4]);
    EXPECT_EQ(remote_id0, lease->remote_id_);

    // Remote id #0, from now - 500 to now - 100, final partial.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4ByRemoteId(remote_id0,
                                                          addr4,
                                                          LeasePageSize(1),
                                                          now_ - 500,
                                                          now_ - 100));
    EXPECT_EQ(0, got.size());
}

TEST_F(PgSqlExtendedInfoTest, getLeases4ByRemoteId) {
    testGetLeases4ByRemoteId();
}

TEST_F(PgSqlExtendedInfoTest, getLeases4ByRemoteIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRemoteId();
}

}  // namespace
