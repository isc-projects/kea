// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/mysql_lease_mgr.h>
#include <mysql/testutils/mysql_schema.h>
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
class MySqlExtendedInfoTest : public ::testing::Test {
public:
    /// @brief Constructor.
    MySqlExtendedInfoTest() {
        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();

        // Connect to the database.
        try {
            LeaseMgrFactory::create(validMySQLConnectionString());
        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
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
    ~MySqlExtendedInfoTest() {
        LeaseMgrFactory::destroy();
        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        destroyMySQLSchema();

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

    /// @brief Test upgradeExtendedInfo.
    void testUpgradeExtendedInfo(const CfgConsistency::ExtendedInfoSanity& check,
                                 const LeasePageSize& page_size);

    /// @brief Lease manager.
    LeaseMgr* lease_mgr_;

    /// @brief V4 leases.
    Lease4Collection leases4;

    /// @brief Current timestamp.
    time_t now_;
};

/// @brief Verifies that the lease manager can add the v4 leases.
void
MySqlExtendedInfoTest::testInitLease4() {
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

TEST_F(MySqlExtendedInfoTest, initLease4) {
    testInitLease4();
}

TEST_F(MySqlExtendedInfoTest, initLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testInitLease4();
}

/// @brief Verifies that getLeases4ByRelayId works as expected.
void
MySqlExtendedInfoTest::testGetLeases4ByRelayId() {
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

TEST_F(MySqlExtendedInfoTest, getLeases4ByRelayId) {
    testGetLeases4ByRelayId();
}

TEST_F(MySqlExtendedInfoTest, getLeases4ByRelayIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRelayId();
}

/// @brief Verifies that getLeases4ByRemoteId works as expected.
void
MySqlExtendedInfoTest::testGetLeases4ByRemoteId() {
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

TEST_F(MySqlExtendedInfoTest, getLeases4ByRemoteId) {
    testGetLeases4ByRemoteId();
}

TEST_F(MySqlExtendedInfoTest, getLeases4ByRemoteIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRemoteId();
}

void
MySqlExtendedInfoTest::testUpgradeExtendedInfo(const CfgConsistency::ExtendedInfoSanity& check,
                                               const LeasePageSize& page_size) {
    // Lease manager is created with empty tables.
    initLease4(false);

    // Create leases.
    IOAddress addr0(ADDRESS4[0]);
    IOAddress addr1(ADDRESS4[1]);
    IOAddress addr2(ADDRESS4[2]);
    IOAddress addr3(ADDRESS4[3]);
    IOAddress addr4(ADDRESS4[4]);
    IOAddress addr5(ADDRESS4[5]);
    IOAddress addr6(ADDRESS4[6]);
    IOAddress addr7(ADDRESS4[7]);
    IOAddress zero = IOAddress::IPV4_ZERO_ADDRESS();
    vector<uint8_t> relay_id = { 0xaa, 0xbb, 0xcc };
    vector<uint8_t> relay_id2 = { 0xdd, 0xee, 0xff };
    vector<uint8_t> remote_id = { 1, 2, 3, 4 };
    vector<uint8_t> remote_id2 = { 5, 6, 7, 8 };
    string user_context_txt = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt += " \"sub-options\": \"0204010203040C03AABBCC\",";
    user_context_txt += " \"relay-id\": \"AABBCC\",";
    user_context_txt += " \"remote-id\": \"01020304\" } } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    string user_context_txt_old = "{ \"ISC\": { \"relay-agent-info\":";
    user_context_txt_old += " \"0204010203040C03AABBCC\" } }";
    ElementPtr user_context_old;
    ASSERT_NO_THROW(user_context_old = Element::fromJSON(user_context_txt_old));
    string user_context_list_txt = "{ \"ISC\": { \"relay-agent-info\": [ ] } }";
    ElementPtr user_context_list;
    ASSERT_NO_THROW(user_context_list = Element::fromJSON(user_context_list_txt));
    string user_context_lower_txt = "{ \"isc\": { \"relay-agent-info\":";
    user_context_lower_txt += " \"0204010203040c03aabbcc\" } }";
    ElementPtr user_context_lower;
    ASSERT_NO_THROW(user_context_lower = Element::fromJSON(user_context_lower_txt));
    string user_context_badsub_txt = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_badsub_txt += " \"sub-options\": \"foobar\",";
    user_context_badsub_txt += " \"relay-id\": \"AABBCC\",";
    user_context_badsub_txt += " \"remote-id\": \"01020304\" } } }";
    ElementPtr user_context_badsub;
    ASSERT_NO_THROW(user_context_badsub = Element::fromJSON(user_context_badsub_txt));
    string user_context_extra_txt = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_extra_txt += " \"foo\": \"bar\", ";
    user_context_extra_txt += " \"sub-options\": \"0204010203040C03AABBCC\",";
    user_context_extra_txt += " \"relay-id\": \"AABBCC\",";
    user_context_extra_txt += " \"remote-id\": \"01020304\" } } }";
    ElementPtr user_context_extra;
    ASSERT_NO_THROW(user_context_extra = Element::fromJSON(user_context_extra_txt));

    Lease4Ptr lease;
    // lease0: addr0, ids, before: always not updated.
    lease = leases4[0];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id;
    lease->remote_id_ = remote_id;
    lease->setContext(user_context);
    lease->cltt_ = now_ - 500;

    // lease1: addr1, ids, after: always not updated.
    lease = leases4[1];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id;
    lease->remote_id_ = remote_id;
    lease->setContext(user_context);
    lease->cltt_ = now_ + 500;

    // lease2: addr2, no id, old user context: updated on check > NONE.
    lease = leases4[2];
    ASSERT_TRUE(lease);
    lease->setContext(user_context_old);

    // lease3: addr3, ids, lower case old user context: always updated.
    lease = leases4[3];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id;
    lease->remote_id_ = remote_id;
    lease->setContext(user_context_lower);

    // Lease4: addr4, ids, bad (list) user context: updated on check > NONE.
    lease = leases4[4];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id;
    lease->remote_id_ = remote_id;
    lease->setContext(user_context_list);

    // Lease5: addr5, other ids: always updated.
    lease = leases4[5];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id2;
    lease->remote_id_ = remote_id2;
    lease->setContext(user_context);

    // Lease6: addr6, ids, bad sub-options: updated on check > FIX.
    lease = leases4[6];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id;
    lease->remote_id_ = remote_id;
    lease->setContext(user_context_badsub);

    // Lease7: addr7, ids, extra in ISC: updated on check > STRICT.
    lease = leases4[7];
    ASSERT_TRUE(lease);
    lease->relay_id_ = relay_id;
    lease->remote_id_ = remote_id;
    lease->setContext(user_context_extra);

    // Add leases.
    for (size_t i = 0; i < leases4.size(); ++i) {
        EXPECT_TRUE(lease_mgr_->addLease(leases4[i]));
    }

    // Set extended info consistency.
    CfgMgr::instance().getCurrentCfg()->getConsistency()->
        setExtendedInfoSanityCheck(check);

    size_t updated;
    ASSERT_NO_THROW(updated = lease_mgr_->upgradeExtendedInfo(page_size));

    // Verify result.
    switch (check) {
    case CfgConsistency::EXTENDED_INFO_CHECK_NONE:
        // Updated leases: 3, 5.
        EXPECT_EQ(updated, 2);
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_FIX:
        // Updated leases: 2, 3, 4, 5.
        EXPECT_EQ(updated, 4);
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_STRICT:
        // Updated leases: 2, 3, 4, 5, 6.
        EXPECT_EQ(updated, 5);
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC:
    default:
        // Updated leases: 2, 3, 4, 5, 6, 7.
        EXPECT_EQ(updated, 6);
        break;
    }

    // Verify stored leases.
    Lease4Collection got;
    // Use the page version as it returns leases in order.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4(zero, LeasePageSize(100)));
    ASSERT_EQ(leases4.size(), got.size());

    // Check lease0.
    lease = got[0];
    EXPECT_EQ(*lease, *leases4[0]);
    EXPECT_EQ(relay_id, lease->relay_id_);
    EXPECT_EQ(remote_id, lease->remote_id_);

    // Check lease1.
    lease = got[1];
    EXPECT_EQ(*lease, *leases4[1]);
    EXPECT_EQ(relay_id, lease->relay_id_);
    EXPECT_EQ(remote_id, lease->remote_id_);

    // Check lease2.
    lease = got[2];
    Lease4Ptr expected2(new Lease4(*leases4[2]));
    if (check == CfgConsistency::EXTENDED_INFO_CHECK_NONE) {
        EXPECT_EQ(*lease, *expected2);
        EXPECT_TRUE(lease->relay_id_.empty());
        EXPECT_TRUE(lease->remote_id_.empty());
    } else {
        expected2->setContext(user_context);
        expected2->relay_id_ = relay_id;
        expected2->remote_id_ = remote_id;
        EXPECT_EQ(*lease, *expected2);
        EXPECT_EQ(relay_id, lease->relay_id_);
        EXPECT_EQ(remote_id, lease->remote_id_);
    }

    // Check lease3.
    lease = got[3];
    Lease4Ptr expected3(new Lease4(*leases4[3]));
    expected3->relay_id_.clear();
    expected3->remote_id_.clear();
    EXPECT_EQ(*lease, *expected3);
    EXPECT_TRUE(lease->relay_id_.empty());
    EXPECT_TRUE(lease->remote_id_.empty());

    // Check lease4.
    lease = got[4];
    Lease4Ptr expected4(new Lease4(*leases4[4]));
    if (check == CfgConsistency::EXTENDED_INFO_CHECK_NONE) {
        EXPECT_EQ(*lease, *expected4);
        EXPECT_EQ(relay_id, lease->relay_id_);
        EXPECT_EQ(remote_id, lease->remote_id_);
    } else {
        expected4->relay_id_.clear();
        expected4->remote_id_.clear();
        expected4->setContext(ElementPtr());
        EXPECT_EQ(*lease, *expected4);
        EXPECT_TRUE(lease->relay_id_.empty());
        EXPECT_TRUE(lease->remote_id_.empty());
    }

    // Check lease5.
    lease = got[5];
    Lease4Ptr expected5(new Lease4(*leases4[5]));
    expected5->relay_id_ = relay_id;
    expected5->remote_id_ = remote_id;
    EXPECT_EQ(*lease, *expected5);
    EXPECT_EQ(relay_id, lease->relay_id_);
    EXPECT_EQ(remote_id, lease->remote_id_);

    // Check lease6.
    lease = got[6];
    Lease4Ptr expected6(new Lease4(*leases4[6]));
    if ((check != CfgConsistency::EXTENDED_INFO_CHECK_STRICT) &&
        (check != CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC)) {
        EXPECT_EQ(*lease, *expected6);
        EXPECT_EQ(relay_id, lease->relay_id_);
        EXPECT_EQ(remote_id, lease->remote_id_);
    } else {
        expected6->relay_id_.clear();
        expected6->remote_id_.clear();
        expected6->setContext(ElementPtr());
        EXPECT_EQ(*lease, *expected6);
        EXPECT_TRUE(lease->relay_id_.empty());
        EXPECT_TRUE(lease->remote_id_.empty());
    }

    // Check lease7.
    lease = got[7];
    Lease4Ptr expected7(new Lease4(*leases4[7]));
    if (check != CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC) {
        EXPECT_EQ(*lease, *expected7);
        EXPECT_EQ(relay_id, lease->relay_id_);
        EXPECT_EQ(remote_id, lease->remote_id_);
    } else {
        expected7->relay_id_.clear();
        expected7->remote_id_.clear();
        expected7->setContext(ElementPtr());
        EXPECT_EQ(*lease, *expected7);
        EXPECT_TRUE(lease->relay_id_.empty());
        EXPECT_TRUE(lease->remote_id_.empty());
    }

    // Verify getLeases4ByRelayId.
    Lease4Collection by_relay_id;
    EXPECT_NO_THROW(by_relay_id =
                    lease_mgr_->getLeases4ByRelayId(relay_id,
                                                    zero,
                                                    LeasePageSize(100)));
    switch (check) {
    case CfgConsistency::EXTENDED_INFO_CHECK_NONE:
        // Got leases: 0, 1, 4, 5, 6, 7.
        EXPECT_EQ(6, by_relay_id.size());
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_FIX:
        // Got leases: 0, 1, 2, 5, 6, 7.
        EXPECT_EQ(6, by_relay_id.size());
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_STRICT:
        // Got leases: 0, 1, 2, 4, 7.
        EXPECT_EQ(5, by_relay_id.size());
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC:
    default:
        // Got leases: 0, 1, 2, 4.
        EXPECT_EQ(4, by_relay_id.size());
        break;
    }

    // Verify getLeases4ByRemoteId.
    Lease4Collection by_remote_id;
    EXPECT_NO_THROW(by_remote_id =
                    lease_mgr_->getLeases4ByRemoteId(remote_id,
                                                     zero,
                                                     LeasePageSize(100)));
    switch (check) {
    case CfgConsistency::EXTENDED_INFO_CHECK_NONE:
        // Got leases: 0, 1, 4, 5, 6, 7.
        EXPECT_EQ(6, by_remote_id.size());
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_FIX:
        // Got leases: 0, 1, 2, 5, 6, 7.
        EXPECT_EQ(6, by_remote_id.size());
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_STRICT:
        // Got leases: 0, 1, 2, 4, 7.
        EXPECT_EQ(5, by_remote_id.size());
        break;

    case CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC:
    default:
        // Got leases: 0, 1, 2, 4.
        EXPECT_EQ(4, by_remote_id.size());
        break;
    }

}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfoNone) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_NONE,
                            LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfoFix) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                            LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfoStrict) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_STRICT,
                            LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfoPedantic) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_PEDANTIC,
                            LeasePageSize(100));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo10) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                            LeasePageSize(10));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo5) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                            LeasePageSize(5));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo2) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                            LeasePageSize(2));
}

TEST_F(MySqlExtendedInfoTest, upgradeExtendedInfo1) {
    testUpgradeExtendedInfo(CfgConsistency::EXTENDED_INFO_CHECK_FIX,
                            LeasePageSize(1));
}

}  // namespace
