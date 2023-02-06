// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
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

/// @brief IPv6 addresses used in the tests.
const vector<string> ADDRESS6 = {
    "2001:db8::0", "2001:db8::1", "2001:db8::2", "2001:db8::3",
    "2001:db8::4", "2001:db8::5", "2001:db8::6", "2001:db8::7"
};

/// @brief DUIDs used in the tests.
const vector<string> DUIDS = {
    "wwwwwwww", "BBBBBBBB", "::::::::", "0123456789acdef",
    "BBBBBBBB", "$$$$$$$$", "^^^^^^^^", "\xe5\xe5\xe5\xe5\xe5\xe5\xe5\xe5"
};

/// @brief A derivation of the lease manager exposing protected methods.
class NakedMemfileLeaseMgr : public Memfile_LeaseMgr {
public:
    /// @brief Constructor.
    ///
    /// Creates an instance of the lease manager.
    ///
    /// @param parameters Parameter map.
    NakedMemfileLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
        : Memfile_LeaseMgr(parameters) {
    }

    /// @brief Destructor.
    virtual ~NakedMemfileLeaseMgr() {
    }

    /// @brief Exposes protected methods and members.
    using LeaseMgr::setExtendedInfoTablesEnabled;
    using Memfile_LeaseMgr::relay_id6_;
    using Memfile_LeaseMgr::remote_id6_;
    using Memfile_LeaseMgr::deleteExtendedInfo6;
    using Memfile_LeaseMgr::addRelayId6;
    using Memfile_LeaseMgr::addRemoteId6;
};

/// @brief Type of unique pointers to naked lease manager.
typedef unique_ptr<NakedMemfileLeaseMgr> NakedMemfileLeaseMgrPtr;

/// @brief Test fixture class for extended info tests.
class MemfileExtendedInfoTest : public ::testing::Test {
public:
    /// @brief Constructor.
    MemfileExtendedInfoTest() {
        pmap_.clear();
        lease_mgr_.reset();
        leases4.clear();
        leases6.clear();
        MultiThreadingMgr::instance().setMode(false);
        now_ = time(0);
    }

    /// @brief Destructor.
    ~MemfileExtendedInfoTest() {
        pmap_.clear();
        lease_mgr_.reset();
        leases4.clear();
        leases6.clear();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Start lease manager.
    ///
    /// @param universe Universe (@c Memfile_LeaseMgr::V4 or
    //  @c Memfile_LeaseMgr::v6).
    void start(Memfile_LeaseMgr::Universe u) {
        pmap_["universe"] = (u == Memfile_LeaseMgr::V4 ? "4" : "6");
        pmap_["persist"] = "false";
        if (u == Memfile_LeaseMgr::V6) {
            pmap_["extended-info-tables"] = "true";
        }

        ASSERT_NO_THROW(lease_mgr_.reset(new NakedMemfileLeaseMgr(pmap_)));
        if (u == Memfile_LeaseMgr::V6) {
            EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());
        }
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

    /// @brief Create and set v6 leases.
    void initLease6() {
        ASSERT_EQ(ADDRESS6.size(), DUIDS.size());
        for (size_t i = 0; i < ADDRESS6.size(); ++i) {
            Lease6Ptr lease;
            vector<uint8_t> duid_data = createFromString(DUIDS[i]);
            DuidPtr duid(new DUID(duid_data));
            IOAddress addr(ADDRESS6[i]);
            ASSERT_NO_THROW(lease.reset(new Lease6(((i % 2) ? Lease::TYPE_NA : Lease::TYPE_PD), addr, duid,
                                                   123, 1000, 2000,
                                                   static_cast<SubnetID>(i))));
            leases6.push_back(lease);
            EXPECT_TRUE(lease_mgr_->addLease(lease));
        }
        ASSERT_EQ(ADDRESS6.size(), leases6.size());
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

    /// @brief Test initLease6.
    void testInitLease6();

    /// @brief Test getLease4ByRelayId.
    void testGetLeases4ByRelayId();

    /// @brief Test getLease4ByRemoteId.
    void testGetLeases4ByRemoteId();

    /// @brief Test getLeases6ByRelayId.
    void testGetLeases6ByRelayId();

    /// @brief Test getLeases6ByRemoteId.
    void testGetLeases6ByRemoteId();

    /// @brief Test getLeases6ByLink.
    void testGetLeases6ByLink();

    /// @brief Parameter map.
    DatabaseConnection::ParameterMap pmap_;

    /// @brief Lease manager.
    NakedMemfileLeaseMgrPtr lease_mgr_;

    /// @brief V4 leases.
    Lease4Collection leases4;

    /// @brief V6 leases.
    Lease6Collection leases6;

    /// @brief Current timestamp.
    time_t now_;
};

/// @brief Verifies that the lease manager can start in V4.
TEST_F(MemfileExtendedInfoTest, startV4) {
    start(Memfile_LeaseMgr::V4);
}

/// @brief Verifies that the lease manager can start in V4 with MT.
TEST_F(MemfileExtendedInfoTest, startV4MultiThreading) {
    MultiThreadingTest mt(true);
    start(Memfile_LeaseMgr::V4);
}

/// @brief Verifies that the lease manager can add the v4 leases.
void
MemfileExtendedInfoTest::testInitLease4() {
    start(Memfile_LeaseMgr::V4);
    initLease4();
    EXPECT_EQ(8, leases4.size());
    Lease4Collection got;
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4());
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

TEST_F(MemfileExtendedInfoTest, initLease4) {
    testInitLease4();
}

TEST_F(MemfileExtendedInfoTest, initLease4MultiThreading) {
    MultiThreadingTest mt(true);
    testInitLease4();
}

/// @brief Verifies that getLeases4ByRelayId works as expected.
void
MemfileExtendedInfoTest::testGetLeases4ByRelayId() {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V4);
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

TEST_F(MemfileExtendedInfoTest, getLeases4ByRelayId) {
    testGetLeases4ByRelayId();
}

TEST_F(MemfileExtendedInfoTest, getLeases4ByRelayIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRelayId();
}

/// @brief Verifies that getLeases4ByRemoteId works as expected.
void
MemfileExtendedInfoTest::testGetLeases4ByRemoteId() {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V4);
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

    // The multi-index requires to keep all fields used as indexes read only
    // so instead of modifying members of leases4 first take a copy on them.
    // If you do not do this the multi-index replace operation which implements
    // the updateLease4 method will fail to update all modified indexes
    // because some will have the same value as in the stored object...

    Lease4Ptr lease;
    // lease0: addr0, id0, now.
    lease.reset(new Lease4(*leases4[0]));
    leases4[0] = lease;
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);

    // lease1: addr1, id1, now.
    lease.reset(new Lease4(*leases4[1]));
    leases4[1] = lease;
    lease->remote_id_ = remote_id1;
    lease->setContext(user_context1);

    // lease2: addr2, id0, now - 500.
    lease.reset(new Lease4(*leases4[2]));
    leases4[2] = lease;
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 500;

    // lease3: addr3, id0, now - 800.
    lease.reset(new Lease4(*leases4[3]));
    leases4[3] = lease;
    lease->remote_id_ = remote_id0;
    lease->setContext(user_context0);
    lease->cltt_ = now_ - 800;

    // lease4: addr4, id0, now - 100.
    lease.reset(new Lease4(*leases4[4]));
    leases4[4] = lease;
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

TEST_F(MemfileExtendedInfoTest, getLeases4ByRemoteId) {
    testGetLeases4ByRemoteId();
}

TEST_F(MemfileExtendedInfoTest, getLeases4ByRemoteIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases4ByRemoteId();
}

/// @brief Verifies that the lease manager can start in V6.
TEST_F(MemfileExtendedInfoTest, startV6) {
    start(Memfile_LeaseMgr::V6);
}

/// @brief Verifies that the lease manager can start in V6 with MT.
TEST_F(MemfileExtendedInfoTest, startV6MultiThreading) {
    MultiThreadingTest mt(true);
    start(Memfile_LeaseMgr::V6);
}

/// @brief Verifies that the lease manager can add the v6 leases.
void
MemfileExtendedInfoTest::testInitLease6() {
    start(Memfile_LeaseMgr::V6);
    initLease6();
    EXPECT_EQ(8, leases6.size());
    Lease6Collection got;
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6());
    ASSERT_EQ(leases6.size(), got.size());
    for (size_t i = 0; i < leases6.size(); ++i) {
        ConstElementPtr expected = leases6[i]->toElement();
        LeasePtr lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_TRUE(expected->equals(*lease->toElement()))
            << "expected: " << expected->str() << "\n"
            << "got: " << lease->toElement()->str() << "\n";
    }
}

TEST_F(MemfileExtendedInfoTest, initLease6) {
    testInitLease6();
}

TEST_F(MemfileExtendedInfoTest, initLease6MultiThreading) {
    MultiThreadingTest mt(true);
    testInitLease6();
}

/// @brief Verifies that add and delete work on the by relay id table.
TEST_F(MemfileExtendedInfoTest, relayIdTable6) {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V6);
    EXPECT_EQ(0, lease_mgr_->relay_id6_.size());

    // Create parameter values.
    IOAddress lease_addr0(ADDRESS6[0]);
    IOAddress lease_addr1(ADDRESS6[1]);
    IOAddress lease_addr2(ADDRESS6[2]);
    IOAddress other_lease_addr("2001:db8:1::4");
    vector<uint8_t> relay_id0 = createFromString(DUIDS[0]);
    vector<uint8_t> relay_id1 = createFromString(DUIDS[1]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id1));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr1, relay_id0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr1, relay_id1));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr2, relay_id1));

    // Check delete.
    EXPECT_EQ(6, lease_mgr_->relay_id6_.size());
    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(other_lease_addr));
    // No match so doing nothing.
    EXPECT_EQ(6, lease_mgr_->relay_id6_.size());

    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr0));
    // Removed 3 entries.
    EXPECT_EQ(3, lease_mgr_->relay_id6_.size());
    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr0));
    // Already removed: doing nothing again.
    EXPECT_EQ(3, lease_mgr_->relay_id6_.size());

    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr1));
    // Removed 2 entries.
    EXPECT_EQ(1, lease_mgr_->relay_id6_.size());

    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr2));
    // Removed last entry.
    EXPECT_EQ(0, lease_mgr_->relay_id6_.size());
}

/// @brief Verifies that add and delete work on the by remote id table.
TEST_F(MemfileExtendedInfoTest, remoteIdTable6) {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V6);
    EXPECT_EQ(0, lease_mgr_->remote_id6_.size());

    // Create parameter values.
    IOAddress lease_addr0(ADDRESS6[0]);
    IOAddress lease_addr1(ADDRESS6[1]);
    IOAddress lease_addr2(ADDRESS6[2]);
    IOAddress other_lease_addr("2001:db8:1::4");
    vector<uint8_t> remote_id0 = createFromString(DUIDS[0]);
    vector<uint8_t> remote_id1 = createFromString(DUIDS[1]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr1, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr1, remote_id1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr2, remote_id1));

    // Check delete.
    EXPECT_EQ(6, lease_mgr_->remote_id6_.size());
    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(other_lease_addr));
    // No match so doing nothing.
    EXPECT_EQ(6, lease_mgr_->remote_id6_.size());

    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr0));
    // Removed 3 entries.
    EXPECT_EQ(3, lease_mgr_->remote_id6_.size());
    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr0));
    // Already removed: doing nothing again.
    EXPECT_EQ(3, lease_mgr_->remote_id6_.size());

    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr1));
    // Removed 2 entries.
    EXPECT_EQ(1, lease_mgr_->remote_id6_.size());

    EXPECT_NO_THROW(lease_mgr_->deleteExtendedInfo6(lease_addr2));
    // Removed last entry.
    EXPECT_EQ(0, lease_mgr_->remote_id6_.size());
}

/// @brief Verifies that getLeases6ByRelayId works as expected.
void
MemfileExtendedInfoTest::testGetLeases6ByRelayId() {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V6);
    initLease6();
    EXPECT_EQ(0, lease_mgr_->relay_id6_.size());

    // Create parameter values.
    IOAddress lease_addr0(ADDRESS6[0]);
    IOAddress lease_addr1(ADDRESS6[1]);
    IOAddress lease_addr2(ADDRESS6[2]);
    IOAddress link_addr(ADDRESS6[4]);
    IOAddress other_link_addr("2001:db8:1::4");
    IOAddress zero = IOAddress::IPV6_ZERO_ADDRESS();
    vector<uint8_t> relay_id_data0 = createFromString(DUIDS[0]);
    DUID relay_id0(relay_id_data0);
    vector<uint8_t> relay_id_data1 = createFromString(DUIDS[1]);
    DUID relay_id1(relay_id_data1);
    vector<uint8_t> relay_id_data2 = createFromString(DUIDS[2]);
    DUID relay_id2(relay_id_data2);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data1));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr1, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr1, relay_id_data1));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr2, relay_id_data1));
    EXPECT_EQ(6, lease_mgr_->relay_id6_.size());

    Lease6Collection got;
    // Unknown relay id #2, no link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id2,
                                                          zero,
                                                          0,
                                                          zero,
                                                          LeasePageSize(100)));
    EXPECT_EQ(0, got.size());

    // Unknown relay id #2, link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id2,
                                                          link_addr,
                                                          64,
                                                          zero,
                                                          LeasePageSize(100)));
    EXPECT_EQ(0, got.size());

    // Relay id #0, other link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id0,
                                                          other_link_addr,
                                                          64,
                                                          zero,
                                                          LeasePageSize(100)));
    EXPECT_EQ(0, got.size());

    // Relay id #0, no link: 3 entries but 2 addresses.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id0,
                                                          zero,
                                                          0,
                                                          zero,
                                                          LeasePageSize(100)));
    ASSERT_EQ(2, got.size());
    Lease6Ptr lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Relay id #1, no link, partial: 2 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          zero,
                                                          0,
                                                          zero,
                                                          LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Relay id #1, no link, partial from previous: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          zero,
                                                          0,
                                                          lease->addr_,
                                                          LeasePageSize(2)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);

    // Add another entry for last tests.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data1));
    EXPECT_EQ(7, lease_mgr_->relay_id6_.size());

    // Relay id #1, link: 3 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          link_addr,
                                                          64,
                                                          zero,
                                                          LeasePageSize(100)));
    ASSERT_EQ(3, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);
    lease = got[2];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);

    // Relay id #1, link, initial partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          link_addr,
                                                          64,
                                                          zero,
                                                          LeasePageSize(1)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);

    // Relay id #1, link, next partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          link_addr,
                                                          64,
                                                          lease->addr_,
                                                          LeasePageSize(1)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Relay id #1, link, next partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          link_addr,
                                                          64,
                                                          lease->addr_,
                                                          LeasePageSize(1)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);

    // Relay id #1, link, final partial: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          link_addr,
                                                          64,
                                                          lease->addr_,
                                                          LeasePageSize(1)));
    EXPECT_EQ(0, got.size());
}

TEST_F(MemfileExtendedInfoTest, getLeases6ByRelayId) {
    testGetLeases6ByRelayId();
}

TEST_F(MemfileExtendedInfoTest, getLeases6ByRelayIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6ByRelayId();
}

/// @brief Verifies that getLeases6ByRemoteId works as expected.
void
MemfileExtendedInfoTest::testGetLeases6ByRemoteId() {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V6);
    initLease6();
    EXPECT_EQ(0, lease_mgr_->remote_id6_.size());

    // Create parameter values.
    IOAddress lease_addr0(ADDRESS6[0]);
    IOAddress lease_addr1(ADDRESS6[1]);
    IOAddress lease_addr2(ADDRESS6[2]);
    IOAddress link_addr(ADDRESS6[4]);
    IOAddress other_link_addr("2001:db8:1::4");
    IOAddress zero = IOAddress::IPV6_ZERO_ADDRESS();
    vector<uint8_t> remote_id0 = createFromString(DUIDS[0]);
    vector<uint8_t> remote_id1 = createFromString(DUIDS[1]);
    vector<uint8_t> remote_id2 = createFromString(DUIDS[2]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr1, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr1, remote_id1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr2, remote_id1));
    EXPECT_EQ(6, lease_mgr_->remote_id6_.size());

    Lease6Collection got;
    // Unknown remote id #2, no link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id2,
                                                           zero,
                                                           0,
                                                           zero,
                                                           LeasePageSize(10)));
    EXPECT_EQ(0, got.size());

    // Unknown remote id #2, link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id2,
                                                           link_addr,
                                                           64,
                                                           zero,
                                                           LeasePageSize(10)));
    EXPECT_EQ(0, got.size());

    // Remote id #0, other link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id0,
                                                           other_link_addr,
                                                           64,
                                                           zero,
                                                           LeasePageSize(10)));
    EXPECT_EQ(0, got.size());

    // Remote id #0, no link: 3 entries but 2 addresses.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id0,
                                                           zero,
                                                           0,
                                                           zero,
                                                           LeasePageSize(10)));
    ASSERT_EQ(2, got.size());
    Lease6Ptr lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Remote id #1, no link, partial: 2 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           zero,
                                                           0,
                                                           zero,
                                                           LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Remote id #1, no link, partial from previous: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           zero,
                                                           0,
                                                           lease->addr_,
                                                           LeasePageSize(2)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);

    // Add another entry for last tests.
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id1));
    EXPECT_EQ(7, lease_mgr_->remote_id6_.size());

    // Remote id #1, link: 3 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           link_addr,
                                                           64,
                                                           zero,
                                                           LeasePageSize(10)));
    ASSERT_EQ(3, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);
    lease = got[2];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);

    // Remote id #1, link, initial partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           link_addr,
                                                           64,
                                                           zero,
                                                           LeasePageSize(1)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);

    // Remote id #1, link, next partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           link_addr,
                                                           64,
                                                           lease->addr_,
                                                           LeasePageSize(1)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Remote id #1, link, next partial: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           link_addr,
                                                           64,
                                                           lease->addr_,
                                                           LeasePageSize(1)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);

    // Remote id #1, link, final partial: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           link_addr,
                                                           64,
                                                           lease->addr_,
                                                           LeasePageSize(1)));
    EXPECT_EQ(0, got.size());
}

TEST_F(MemfileExtendedInfoTest, getLeases6ByRemoteId) {
    testGetLeases6ByRemoteId();
}

TEST_F(MemfileExtendedInfoTest, getLeases6ByRemoteIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6ByRemoteId();
}

/// @brief Verifies that getLeases6ByLink works as expected.
void
MemfileExtendedInfoTest::testGetLeases6ByLink() {
    // Lease manager is created with empty tables.
    start(Memfile_LeaseMgr::V6);
    initLease6();

    // Create parameter values.
    IOAddress link_addr(ADDRESS6[4]);
    IOAddress other_link_addr("2001:db8:1::4");
    IOAddress zero = IOAddress::IPV6_ZERO_ADDRESS();

    Lease6Collection got;
    // Other link: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByLink(other_link_addr,
                                                       64,
                                                       zero,
                                                       LeasePageSize(10)));
    EXPECT_EQ(0, got.size());

    // Link: 8 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByLink(link_addr,
                                                       64,
                                                       zero,
                                                       LeasePageSize(10)));

    ASSERT_EQ(8, got.size());
    Lease6Ptr lease;
    for (size_t i = 0; i < 8; ++i) {
        lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_EQ(IOAddress(ADDRESS6[i]), lease->addr_);
    }

    // Link: initial partial: 4 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByLink(link_addr,
                                                       64,
                                                       zero,
                                                       LeasePageSize(4)));
    ASSERT_EQ(4, got.size());
    for (size_t i = 0; i < 4; ++i) {
        lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_EQ(IOAddress(ADDRESS6[i]), lease->addr_);
    }

    // Link: next partial: 4 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByLink(link_addr,
                                                       64,
                                                       lease->addr_,
                                                       LeasePageSize(4)));
    ASSERT_EQ(4, got.size());
    for (size_t i = 0; i < 4; ++i) {
        lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_EQ(IOAddress(ADDRESS6[i + 4]), lease->addr_);
    }

    // Link: further partial: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByLink(link_addr,
                                                       64,
                                                       lease->addr_,
                                                       LeasePageSize(4)));
    EXPECT_EQ(0, got.size());
}

TEST_F(MemfileExtendedInfoTest, getLeases6ByLink) {
    testGetLeases6ByLink();
}

TEST_F(MemfileExtendedInfoTest, getLeases6ByLinkMultiThreading) {
    MultiThreadingTest mt(true);
    testGetLeases6ByLink();
}

/// @brief Verifies that v6 deleteLease removes references from extended
/// info tables.
TEST_F(MemfileExtendedInfoTest, deleteLease6) {
    start(Memfile_LeaseMgr::V6);
    initLease6();
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());

    // Create parameter values.
    IOAddress lease_addr(ADDRESS6[0]);
    vector<uint8_t> relay_id = createFromString(DUIDS[0]);
    vector<uint8_t> remote_id = createFromString(DUIDS[1]);
    vector<uint8_t> relay_id2 = createFromString(DUIDS[2]);
    vector<uint8_t> remote_id2 = createFromString(DUIDS[3]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr, relay_id));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr, remote_id));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr, relay_id2));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr, remote_id2));

    EXPECT_EQ(2, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(2, lease_mgr_->remote_id6_.size());

    // Delete the second lease: no side effect on tables.
    Lease6Ptr lease = leases6[1];
    ASSERT_TRUE(lease);
    EXPECT_NE(lease_addr, lease->addr_);
    // Put a value different of the expected one.
    lease->extended_info_action_ = Lease6::ACTION_UPDATE;
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->deleteLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);
    EXPECT_EQ(2, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(2, lease_mgr_->remote_id6_.size());

    // Delete the first lease: tables are cleared.
    lease = leases6[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr, lease->addr_);
    EXPECT_NO_THROW(ret = lease_mgr_->deleteLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());
}

/// @brief Verifies that v6 deleteLease does not touch extended info tables
/// when they are disabled.
TEST_F(MemfileExtendedInfoTest, deleteLease6disabled) {
    start(Memfile_LeaseMgr::V6);
    initLease6();
    lease_mgr_->setExtendedInfoTablesEnabled(false);

    // Create parameter values.
    IOAddress lease_addr(ADDRESS6[0]);
    vector<uint8_t> relay_id = createFromString(DUIDS[0]);
    vector<uint8_t> remote_id = createFromString(DUIDS[1]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr, relay_id));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr, remote_id));

    EXPECT_EQ(1, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(1, lease_mgr_->remote_id6_.size());

    // Delete the first lease: tables are no longer cleared.
    Lease6Ptr lease = leases6[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr, lease->addr_);
    // Put a value different from the expected one.
    lease->extended_info_action_ = Lease6::ACTION_UPDATE;
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->deleteLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);
    EXPECT_EQ(1, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(1, lease_mgr_->remote_id6_.size());
}

/// @brief Verifies that v6 addLease adds references to extended info tables.
TEST_F(MemfileExtendedInfoTest, addLease6) {
    start(Memfile_LeaseMgr::V6);
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);
    // Put a value different of the expected one.
    lease->extended_info_action_ = Lease6::ACTION_DELETE;
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Check extended info tables.
    ASSERT_EQ(1, lease_mgr_->relay_id6_.size());
    auto relay_id_it =  lease_mgr_->relay_id6_.cbegin();
    ASSERT_NE(relay_id_it, lease_mgr_->relay_id6_.cend());
    Lease6ExtendedInfoPtr ex_info = *relay_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id = ex_info->id_;
    const vector<uint8_t>& exp_relay_id = vector<uint8_t>(8, 0x64);
    EXPECT_EQ(exp_relay_id, relay_id);

    ASSERT_EQ(1, lease_mgr_->remote_id6_.size());
    auto remote_id_it = lease_mgr_->remote_id6_.cbegin();
    ASSERT_NE(remote_id_it, lease_mgr_->remote_id6_.cend());
    ex_info = *remote_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id = ex_info->id_;
    const vector<uint8_t>& exp_remote_id = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(exp_remote_id, remote_id);
}

/// @brief Verifies that v6 addLease does not touch extended info tables
/// when they are disabled.
TEST_F(MemfileExtendedInfoTest, addLease6disabled) {
    start(Memfile_LeaseMgr::V6);
    lease_mgr_->setExtendedInfoTablesEnabled(false);

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);
    lease->extended_info_action_ = Lease6::ACTION_UPDATE;
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());
}

/// @brief Verifies that updateLease6 does not touch references to extended
/// info tables when the action is ACTION_IGNORE.
TEST_F(MemfileExtendedInfoTest, updateLease6ignore) {
    start(Memfile_LeaseMgr::V6);
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));

    // Add the lease.
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);

    // Set user context.
    lease.reset(new Lease6(*lease));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);

    // Set action and call updateLease6.
    lease->extended_info_action_ = Lease6::ACTION_IGNORE;
    ASSERT_NO_THROW(lease_mgr_->updateLease6(lease));
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Tables were not touched.
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());

    // Note that with persist when the database is reloaded the user context
    // is still there so tables will be updated: the ACTION_IGNORE setting
    // has no persistent effect: instead cleanup the user context before
    // calling updateLease6...
}

/// @brief Verifies that updateLease6 clears references from extended
/// info tables when the action is ACTION_DELETE.
TEST_F(MemfileExtendedInfoTest, updateLease6delete) {
    start(Memfile_LeaseMgr::V6);
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);

    // Add the lease.
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_EQ(1, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(1, lease_mgr_->remote_id6_.size());

    // Set action and call updateLease6.
    lease.reset(new Lease6(*lease));
    lease->extended_info_action_ = Lease6::ACTION_DELETE;;
    ASSERT_NO_THROW(lease_mgr_->updateLease6(lease));
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Tables were cleared.
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());
}

/// @brief Verifies that updateLease6 does not clears references from extended
/// info tables when the action is ACTION_DELETE but tables are disabled.
TEST_F(MemfileExtendedInfoTest, updateLease6deleteDisabled) {
    start(Memfile_LeaseMgr::V6);
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);

    // Add the lease.
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_EQ(1, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(1, lease_mgr_->remote_id6_.size());

    // Disable on the fly extended info tables.
    // Note it is a priori an illegal operation so this could have to be
    // changed...
    lease_mgr_->setExtendedInfoTablesEnabled(false);

    // Set action and call updateLease6.
    lease.reset(new Lease6(*lease));
    lease->extended_info_action_ = Lease6::ACTION_DELETE;;
    ASSERT_NO_THROW(lease_mgr_->updateLease6(lease));
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Tables were not touched.
    EXPECT_EQ(1, lease_mgr_->relay_id6_.size());
    EXPECT_EQ(1, lease_mgr_->remote_id6_.size());
}

/// @brief Verifies that updateLease6 adds references to extended
/// info tables when the action is ACTION_UPDATE.
TEST_F(MemfileExtendedInfoTest, updateLease6update) {
    start(Memfile_LeaseMgr::V6);
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));

    // Add the lease.
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());

    // Set user context.
    lease.reset(new Lease6(*lease));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);

    // Set action and call updateLease6.
    lease->extended_info_action_ = Lease6::ACTION_UPDATE;
    ASSERT_NO_THROW(lease_mgr_->updateLease6(lease));
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Tables were updated.
    ASSERT_EQ(1, lease_mgr_->relay_id6_.size());
    auto relay_id_it =  lease_mgr_->relay_id6_.cbegin();
    ASSERT_NE(relay_id_it, lease_mgr_->relay_id6_.cend());
    Lease6ExtendedInfoPtr ex_info = *relay_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id = ex_info->id_;
    const vector<uint8_t>& exp_relay_id = vector<uint8_t>(8, 0x64);
    EXPECT_EQ(exp_relay_id, relay_id);

    ASSERT_EQ(1, lease_mgr_->remote_id6_.size());
    auto remote_id_it = lease_mgr_->remote_id6_.cbegin();
    ASSERT_NE(remote_id_it, lease_mgr_->remote_id6_.cend());
    ex_info = *remote_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id = ex_info->id_;
    const vector<uint8_t>& exp_remote_id = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(exp_remote_id, remote_id);
}

/// @brief Verifies that updateLease6 does not add references to extended
/// info tables when the action is ACTION_UPDATE but tables are disabled.
TEST_F(MemfileExtendedInfoTest, updateLease6updateDisabled) {
    start(Memfile_LeaseMgr::V6);
    lease_mgr_->setExtendedInfoTablesEnabled(false);

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));

    // Add the lease.
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);

    // Set user context.
    lease.reset(new Lease6(*lease));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);

    // Set action and call updateLease6.
    lease->extended_info_action_ = Lease6::ACTION_UPDATE;
    ASSERT_NO_THROW(lease_mgr_->updateLease6(lease));
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Tables were not touched.
    EXPECT_TRUE(lease_mgr_->relay_id6_.empty());
    EXPECT_TRUE(lease_mgr_->remote_id6_.empty());
}

/// @brief Verifies that updateLease6 modifies references to extended
/// info tables when the action is ACTION_UPDATE and the extended
/// info is modified before the call.
TEST_F(MemfileExtendedInfoTest, updateLease6update2) {
    start(Memfile_LeaseMgr::V6);
    EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());

    // Create parameter values.
    Lease6Ptr lease;
    IOAddress lease_addr(ADDRESS6[1]);
    vector<uint8_t> duid_data = createFromString(DUIDS[0]);
    DuidPtr duid(new DUID(duid_data));
    ASSERT_NO_THROW(lease.reset(new Lease6(Lease::TYPE_NA, lease_addr, duid,
                                           123, 1000, 2000, 1)));
    lease.reset(new Lease6(*lease));
    string user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,"
        " \"link\": \"2001:db8::2\",  \"peer\": \"2001:db8::3\","
        " \"options\": \"0x00250006010203040506003500086464646464646464\","
        " \"remote-id\": \"010203040506\","
        " \"relay-id\": \"6464646464646464\" } ] } }";
    ElementPtr user_context;
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease->setContext(user_context);

    // Add the lease.
    bool ret = false;
    EXPECT_NO_THROW(ret = lease_mgr_->addLease(lease));
    EXPECT_TRUE(ret);

    // Verify updated extended info tables.
    ASSERT_EQ(1, lease_mgr_->relay_id6_.size());
    auto relay_id_it =  lease_mgr_->relay_id6_.cbegin();
    ASSERT_NE(relay_id_it, lease_mgr_->relay_id6_.cend());
    Lease6ExtendedInfoPtr ex_info = *relay_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id = ex_info->id_;
    const vector<uint8_t>& exp_relay_id = vector<uint8_t>(8, 0x64);
    EXPECT_EQ(exp_relay_id, relay_id);

    ASSERT_EQ(1, lease_mgr_->remote_id6_.size());
    auto remote_id_it = lease_mgr_->remote_id6_.cbegin();
    ASSERT_NE(remote_id_it, lease_mgr_->remote_id6_.cend());
    ex_info = *remote_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id = ex_info->id_;
    const vector<uint8_t>& exp_remote_id = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(exp_remote_id, remote_id);

    // Change the user context.
    user_context_txt =
        "{ \"ISC\": { \"relay-info\": [ { \"hop\": 44,"
        " \"link\": \"2001:db8::4\",  \"peer\": \"2001:db8::5\","
        " \"options\": \"0x00250006010203040507003500086465656565656565\","
        " \"remote-id\": \"010203040507\","
        " \"relay-id\": \"6565656565656565\" } ] } }";
    ASSERT_NO_THROW(user_context = Element::fromJSON(user_context_txt));
    lease.reset(new Lease6(*lease));
    lease->setContext(user_context);

    // Set action and call updateLease6.
    lease->extended_info_action_ = Lease6::ACTION_UPDATE;
    ASSERT_NO_THROW(lease_mgr_->updateLease6(lease));
    EXPECT_EQ(Lease6::ACTION_IGNORE, lease->extended_info_action_);

    // Tables were updated.
    ASSERT_EQ(1, lease_mgr_->relay_id6_.size());
    relay_id_it = lease_mgr_->relay_id6_.cbegin();
    ASSERT_NE(relay_id_it, lease_mgr_->relay_id6_.cend());
    ex_info = *relay_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& relay_id2 = ex_info->id_;
    const vector<uint8_t>& exp_relay_id2 = vector<uint8_t>(8, 0x65);
    EXPECT_NE(exp_relay_id, relay_id2);
    EXPECT_EQ(exp_relay_id2, relay_id2);

    ASSERT_EQ(1, lease_mgr_->remote_id6_.size());
    remote_id_it = lease_mgr_->remote_id6_.cbegin();
    ASSERT_NE(remote_id_it, lease_mgr_->remote_id6_.cend());
    ex_info = *remote_id_it;
    ASSERT_TRUE(ex_info);
    EXPECT_EQ(ADDRESS6[1], ex_info->lease_addr_.toText());
    const vector<uint8_t>& remote_id2 = ex_info->id_;
    const vector<uint8_t>& exp_remote_id2 = { 1, 2, 3, 4, 5, 7 };
    EXPECT_NE(exp_remote_id, remote_id2);
    EXPECT_EQ(exp_remote_id2, remote_id2);
}

}  // namespace
