// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_EXTENDED_INFO_UNITTEST_H
#define GENERIC_EXTENDED_INFO_UNITTEST_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Base test fixture class for extended info tests.
template<typename NakedLeaseMgrType>
class GenericExtendedInfoTest : public ::testing::Test {
public:
    /// @brief IPv4 addresses used in the tests.
    static const std::vector<std::string> ADDRESS4;

    /// @brief IPv6 addresses used in the tests.
    static const std::vector<std::string> ADDRESS6;

    /// @brief DUIDs used in the tests.
    static const std::vector<std::string> DUIDS;

    /// @brief Return valid connection string.
    virtual std::string validConnectionString() {
        isc_throw(isc::NotImplemented, "attempt to use base test fixture?");
    }

    /// @brief Create the database schema.
    virtual void createSchema() { }

    /// @brief Destroy the database schema.
    virtual void destroySchema() { }

    /// @brief Constructor.
    GenericExtendedInfoTest() {
        // Ensure we have the proper schema with no transient data.
        NakedLeaseMgrType::createSchema();

        const std::string& conn = NakedLeaseMgrType::validConnectionString();
        pmap_ = db::DatabaseConnection::parse(conn);
        lease_mgr_.reset();
        leases4.clear();
        leases6.clear();
        util::MultiThreadingMgr::instance().setMode(false);
        now_ = time(0);
    }

    /// @brief Destructor.
    ~GenericExtendedInfoTest() {
        pmap_.clear();
        lease_mgr_.reset();
        leases4.clear();
        leases6.clear();
        util::MultiThreadingMgr::instance().setMode(false);

        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        NakedLeaseMgrType::destroySchema();
    }

    /// @brief Create and set v4 leases.
    ///
    /// @param insert When true insert in the database.
    void initLease4(bool insert = true) {
        ASSERT_EQ(ADDRESS4.size(), DUIDS.size());
        for (size_t i = 0; i < ADDRESS4.size(); ++i) {
            Lease4Ptr lease;
            std::vector<uint8_t> hwaddr_data(5, 0x08);
            hwaddr_data.push_back(0x80 + i);
            HWAddrPtr hwaddr(new HWAddr(hwaddr_data, HTYPE_ETHER));
            std::vector<uint8_t> client_id = createFromString(DUIDS[i]);
            asiolink::IOAddress address(ADDRESS4[i]);
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
            std::vector<uint8_t> duid_data = createFromString(DUIDS[i]);
            DuidPtr duid(new DUID(duid_data));
            asiolink::IOAddress addr(ADDRESS6[i]);
            ASSERT_NO_THROW(lease.reset(new Lease6(((i % 2) ? Lease::TYPE_NA : Lease::TYPE_PD),
                                                   addr, duid,
                                                   123, 1000, 2000,
                                                   static_cast<SubnetID>(i))));
            leases6.push_back(lease);
            EXPECT_TRUE(lease_mgr_->addLease(lease));
        }
        ASSERT_EQ(ADDRESS6.size(), leases6.size());
    }

    /// @brief Check v6 leases (using get page to keep order).
    void checkLease6() {
        EXPECT_EQ(8, leases6.size());
        Lease6Collection got;
        asiolink::IOAddress zero = asiolink::IOAddress::IPV6_ZERO_ADDRESS();
        LeasePageSize ps100(100);
        EXPECT_NO_THROW(got = lease_mgr_->getLeases6(zero, ps100));
        ASSERT_EQ(leases6.size(), got.size());
        for (size_t i = 0; i < leases6.size(); ++i) {
            data::ConstElementPtr expected = leases6[i]->toElement();
            LeasePtr lease = got[i];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected->equals(*lease->toElement()))
                << "expected: " << expected->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";
        }
    }

    /// @brief Start lease manager.
    ///
    /// @param enable When true enable extended info tables.
    void start(bool enable) {
        // Do not set unused pmap_["universe"].
        if (enable) {
            pmap_["extended-info-tables"] = "true";
        }

        ASSERT_NO_THROW(lease_mgr_.reset(new NakedLeaseMgrType(pmap_)));
        if (enable) {
            EXPECT_TRUE(lease_mgr_->getExtendedInfoTablesEnabled());
        } else {
            EXPECT_FALSE(lease_mgr_->getExtendedInfoTablesEnabled());
        }
    }

    /// @brief Create a vector of uint8_t from a string.
    ///
    /// @param content A not empty string holding the content.
    /// @return A vector of uint8_t with the given content.
    inline std::vector<uint8_t> createFromString(const std::string& content) {
        std::vector<uint8_t> v;
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

    /// @brief Test upgradeExtendedInfo4.
    void testUpgradeExtendedInfo4(const CfgConsistency::ExtendedInfoSanity& check,
                                  const LeasePageSize& page_size);

    /// @brief Test initLease6 with tables.
    void testEnableTables();

    /// @brief Test delete cascade on tables.
    void testDeleteCascade();

    /// @brief Test getLeases6ByRelayId.
    void testGetLeases6ByRelayId();

    /// @brief Test getLeases6ByRemoteId.
    void testGetLeases6ByRemoteId();

    /// @brief Test getLeases6ByLink.
    void testGetLeases6ByLink();

    /// @brief Test upgradeExtendedInfo6.
    void testUpgradeExtendedInfo6(const CfgConsistency::ExtendedInfoSanity& check,
                                  bool extended_info_table_enable,
                                  const LeasePageSize& page_size);

    /// @brief Parameter map.
    db::DatabaseConnection::ParameterMap pmap_;

    /// @brief Lease manager.
    boost::shared_ptr<NakedLeaseMgrType> lease_mgr_;

    /// @brief V4 leases.
    Lease4Collection leases4;

    /// @brief V6 leases.
    Lease6Collection leases6;

    /// @brief Current timestamp.
    time_t now_;
};

template<typename NakedLeaseMgrType>
const std::vector<std::string>
GenericExtendedInfoTest<NakedLeaseMgrType>::ADDRESS4 = {
    "192.0.2.0", "192.0.2.1", "192.0.2.2", "192.0.2.3",
    "192.0.2.4", "192.0.2.5", "192.0.2.6", "192.0.2.7"
};

template<typename NakedLeaseMgrType>
const std::vector<std::string>
GenericExtendedInfoTest<NakedLeaseMgrType>::ADDRESS6 = {
    "2001:db8::", "2001:db8::1", "2001:db8::2", "2001:db8::3",
    "2001:db8::4", "2001:db8::5", "2001:db8::6", "2001:db8::7"
};

template<typename NakedLeaseMgrType>
const std::vector<std::string>
GenericExtendedInfoTest<NakedLeaseMgrType>::DUIDS = {
    "wwwwwwww", "BBBBBBBB", "::::::::", "0123456789acdef",
    "BBBBBBBB", "$$$$$$$$", "^^^^^^^^", "\xe5\xe5\xe5\xe5\xe5\xe5\xe5\xe5"
};

/// @brief Verifies that the lease manager can add the v4 leases.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testInitLease4() {
    start(false);
    initLease4();
    EXPECT_EQ(8, leases4.size());
    asiolink::IOAddress zero = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
    Lease4Collection got;
    // Use the page version as it returns leases in order.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases4(zero, LeasePageSize(100)));
    ASSERT_EQ(leases4.size(), got.size());
    auto compare = [](Lease4Ptr const& left, Lease4Ptr const& right) {
        return (left->addr_ < right->addr_);
    };
    std::sort(got.begin(), got.end(), compare);
    for (size_t i = 0; i < leases4.size(); ++i) {
        data::ConstElementPtr expected = leases4[i]->toElement();
        LeasePtr lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_TRUE(expected->equals(*lease->toElement()))
            << "expected: " << expected->str() << "\n"
            << "got: " << lease->toElement()->str() << "\n";
    }
}

/// @brief Verifies that getLeases4ByRelayId works as expected.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testGetLeases4ByRelayId() {
    // Lease manager is created with empty tables.
    start(false);
    initLease4(false);

    // Create leases.
    asiolink::IOAddress addr0(ADDRESS4[0]);
    asiolink::IOAddress addr1(ADDRESS4[1]);
    asiolink::IOAddress addr2(ADDRESS4[2]);
    asiolink::IOAddress addr3(ADDRESS4[3]);
    asiolink::IOAddress addr4(ADDRESS4[4]);
    asiolink::IOAddress zero = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
    std::vector<uint8_t> relay_id0 = { 0xaa, 0xbb, 0xcc };
    std::vector<uint8_t> relay_id1 = { 1, 2, 3, 4 };
    std::vector<uint8_t> relay_id2 = createFromString(DUIDS[2]);
    std::string user_context_txt0 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt0 += " \"sub-options\": \"0C03AABBCC\",";
    user_context_txt0 += " \"relay-id\": \"AABBCC\" } } }";
    data::ElementPtr user_context0;
    ASSERT_NO_THROW(user_context0 = data::Element::fromJSON(user_context_txt0));
    std::string user_context_txt1 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt1 += " \"sub-options\": \"0C0401020304\",";
    user_context_txt1 += " \"relay-id\": \"01020304\" } } }";
    data::ElementPtr user_context1;
    ASSERT_NO_THROW(user_context1 = data::Element::fromJSON(user_context_txt1));

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

/// @brief Verifies that getLeases4ByRemoteId works as expected.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testGetLeases4ByRemoteId() {
    // Lease manager is created with empty tables.
    start(false);
    initLease4(true);

    // Update leases.
    asiolink::IOAddress addr0(ADDRESS4[0]);
    asiolink::IOAddress addr1(ADDRESS4[1]);
    asiolink::IOAddress addr2(ADDRESS4[2]);
    asiolink::IOAddress addr3(ADDRESS4[3]);
    asiolink::IOAddress addr4(ADDRESS4[4]);
    asiolink::IOAddress zero = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
    std::vector<uint8_t> remote_id0 = { 1, 2, 3, 4 };
    std::vector<uint8_t> remote_id1 = { 0xaa, 0xbb, 0xcc };
    std::vector<uint8_t> remote_id2 = createFromString(DUIDS[2]);
    std::string user_context_txt0 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt0 += " \"sub-options\": \"020401020304\",";
    user_context_txt0 += " \"remote-id\": \"01020304\" } } }";
    data::ElementPtr user_context0;
    ASSERT_NO_THROW(user_context0 = data::Element::fromJSON(user_context_txt0));
    std::string user_context_txt1 = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt1 += " \"sub-options\": \"0203AABBCC\",";
    user_context_txt1 += " \"remote-id\": \"AABBCC\" } } }";
    data::ElementPtr user_context1;
    ASSERT_NO_THROW(user_context1 = data::Element::fromJSON(user_context_txt1));

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

template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testUpgradeExtendedInfo4(
    const CfgConsistency::ExtendedInfoSanity& check,
    const LeasePageSize& page_size) {

    // Lease manager is created with empty tables.
    start(false);
    initLease4(false);

    // Create leases.
    asiolink::IOAddress addr0(ADDRESS4[0]);
    asiolink::IOAddress addr1(ADDRESS4[1]);
    asiolink::IOAddress addr2(ADDRESS4[2]);
    asiolink::IOAddress addr3(ADDRESS4[3]);
    asiolink::IOAddress addr4(ADDRESS4[4]);
    asiolink::IOAddress addr5(ADDRESS4[5]);
    asiolink::IOAddress addr6(ADDRESS4[6]);
    asiolink::IOAddress addr7(ADDRESS4[7]);
    asiolink::IOAddress zero = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
    std::vector<uint8_t> relay_id = { 0xaa, 0xbb, 0xcc };
    std::vector<uint8_t> relay_id2 = { 0xdd, 0xee, 0xff };
    std::vector<uint8_t> remote_id = { 1, 2, 3, 4 };
    std::vector<uint8_t> remote_id2 = { 5, 6, 7, 8 };
    std::string user_context_txt = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_txt += " \"sub-options\": \"0204010203040C03AABBCC\",";
    user_context_txt += " \"relay-id\": \"AABBCC\",";
    user_context_txt += " \"remote-id\": \"01020304\" } } }";
    data::ElementPtr user_context;
    ASSERT_NO_THROW(user_context = data::Element::fromJSON(user_context_txt));
    std::string user_context_txt_old = "{ \"ISC\": { \"relay-agent-info\":";
    user_context_txt_old += " \"0204010203040C03AABBCC\" } }";
    data::ElementPtr user_context_old;
    ASSERT_NO_THROW(user_context_old = data::Element::fromJSON(user_context_txt_old));
    std::string user_context_list_txt = "{ \"ISC\": { \"relay-agent-info\": [ ] } }";
    data::ElementPtr user_context_list;
    ASSERT_NO_THROW(user_context_list = data::Element::fromJSON(user_context_list_txt));
    std::string user_context_lower_txt = "{ \"isc\": { \"relay-agent-info\":";
    user_context_lower_txt += " \"0204010203040c03aabbcc\" } }";
    data::ElementPtr user_context_lower;
    ASSERT_NO_THROW(user_context_lower = data::Element::fromJSON(user_context_lower_txt));
    std::string user_context_badsub_txt = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_badsub_txt += " \"sub-options\": \"foobar\",";
    user_context_badsub_txt += " \"relay-id\": \"AABBCC\",";
    user_context_badsub_txt += " \"remote-id\": \"01020304\" } } }";
    data::ElementPtr user_context_badsub;
    ASSERT_NO_THROW(user_context_badsub = data::Element::fromJSON(user_context_badsub_txt));
    std::string user_context_extra_txt = "{ \"ISC\": { \"relay-agent-info\": {";
    user_context_extra_txt += " \"foo\": \"bar\", ";
    user_context_extra_txt += " \"sub-options\": \"0204010203040C03AABBCC\",";
    user_context_extra_txt += " \"relay-id\": \"AABBCC\",";
    user_context_extra_txt += " \"remote-id\": \"01020304\" } } }";
    data::ElementPtr user_context_extra;
    ASSERT_NO_THROW(user_context_extra = data::Element::fromJSON(user_context_extra_txt));

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
    ASSERT_NO_THROW(updated = lease_mgr_->upgradeExtendedInfo4(page_size));

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
        expected4->setContext(data::ElementPtr());
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
        expected6->setContext(data::ElementPtr());
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
        expected7->setContext(data::ElementPtr());
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

/// @brief Verifies that the lease manager can add the v6 leases.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testInitLease6() {
    start(false);
    initLease6();
    checkLease6();
}

/// @brief Verifies that the lease manager can add the v6 leases with tables.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testEnableTables() {
    start(true);
    initLease6();
    EXPECT_EQ(8, leases6.size());
    Lease6Collection got;
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6());
    ASSERT_EQ(leases6.size(), got.size());
    for (size_t i = 0; i < leases6.size(); ++i) {
        data::ConstElementPtr expected = leases6[i]->toElement();
        LeasePtr lease = got[i];
        ASSERT_TRUE(lease);
        EXPECT_TRUE(expected->equals(*lease->toElement()))
            << "expected: " << expected->str() << "\n"
            << "got: " << lease->toElement()->str() << "\n";
    }
}

/// @brief Verifies that the delete cascade feature works as expected,
/// i.e. that deleteLease() does not require an explicit call to
/// deleteExtendedInfo6().
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testDeleteCascade() {
    // Lease manager is created with empty tables.
    start(true);
    initLease6();
    EXPECT_EQ(0, lease_mgr_->byRelayId6size());
    EXPECT_EQ(0, lease_mgr_->byRemoteId6size());

    // Create parameter values.
    asiolink::IOAddress lease_addr(ADDRESS6[0]);
    std::vector<uint8_t> relay_id_data0 = createFromString(DUIDS[0]);
    DUID relay_id0(relay_id_data0);
    std::vector<uint8_t> relay_id_data1 = createFromString(DUIDS[1]);
    DUID relay_id1(relay_id_data1);
    std::vector<uint8_t> remote_id0 = createFromString(DUIDS[2]);
    std::vector<uint8_t> remote_id1 = createFromString(DUIDS[3]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr, relay_id_data1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr, remote_id1));
    EXPECT_EQ(2, lease_mgr_->byRelayId6size());
    EXPECT_EQ(2, lease_mgr_->byRemoteId6size());

    // Remove the first lease.
    EXPECT_NO_THROW(lease_mgr_->deleteLease(leases6[0]));

    // Check the first lease was gone.
    EXPECT_FALSE(lease_mgr_->getLease6(Lease::TYPE_NA, lease_addr));
    EXPECT_FALSE(lease_mgr_->getLease6(Lease::TYPE_PD, lease_addr));

    // Check tables are now empty.
    EXPECT_EQ(0, lease_mgr_->byRelayId6size());
    EXPECT_EQ(0, lease_mgr_->byRemoteId6size());
}

/// @brief Verifies that getLeases6ByRelayId works as expected.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testGetLeases6ByRelayId() {
    // Lease manager is created with empty tables.
    start(true);
    initLease6();
    EXPECT_EQ(0, lease_mgr_->byRelayId6size());

    // Create parameter values.
    asiolink::IOAddress lease_addr0(ADDRESS6[0]);
    asiolink::IOAddress lease_addr1(ADDRESS6[1]);
    asiolink::IOAddress lease_addr2(ADDRESS6[2]);
    asiolink::IOAddress zero = asiolink::IOAddress::IPV6_ZERO_ADDRESS();
    std::vector<uint8_t> relay_id_data0 = createFromString(DUIDS[0]);
    DUID relay_id0(relay_id_data0);
    std::vector<uint8_t> relay_id_data1 = createFromString(DUIDS[1]);
    DUID relay_id1(relay_id_data1);
    std::vector<uint8_t> relay_id_data2 = createFromString(DUIDS[2]);
    DUID relay_id2(relay_id_data2);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr0, relay_id_data1));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr1, relay_id_data0));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr1, relay_id_data1));
    EXPECT_NO_THROW(lease_mgr_->addRelayId6(lease_addr2, relay_id_data1));
    EXPECT_EQ(6, lease_mgr_->byRelayId6size());

    Lease6Collection got;
    // Unknown relay id #2: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id2,
                                                          zero,
                                                          LeasePageSize(100)));
    EXPECT_EQ(0, got.size());

    // Relay id #0: 3 entries but 2 addresses.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id0,
                                                          zero,
                                                          LeasePageSize(100)));
    ASSERT_EQ(2, got.size());
    Lease6Ptr lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Relay id #1, partial: 2 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          zero,
                                                          LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Relay id #1, partial from previous: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id1,
                                                          lease->addr_,
                                                          LeasePageSize(2)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);
}

/// @brief Verifies that getLeases6ByRemoteId works as expected.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testGetLeases6ByRemoteId() {
    // Lease manager is created with empty tables.
    start(true);
    initLease6();
    EXPECT_EQ(0, lease_mgr_->byRemoteId6size());

    // Create parameter values.
    asiolink::IOAddress lease_addr0(ADDRESS6[0]);
    asiolink::IOAddress lease_addr1(ADDRESS6[1]);
    asiolink::IOAddress lease_addr2(ADDRESS6[2]);
    asiolink::IOAddress zero = asiolink::IOAddress::IPV6_ZERO_ADDRESS();
    std::vector<uint8_t> remote_id0 = createFromString(DUIDS[0]);
    std::vector<uint8_t> remote_id1 = createFromString(DUIDS[1]);
    std::vector<uint8_t> remote_id2 = createFromString(DUIDS[2]);

    // Fill the table.
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr0, remote_id1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr1, remote_id0));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr1, remote_id1));
    EXPECT_NO_THROW(lease_mgr_->addRemoteId6(lease_addr2, remote_id1));
    EXPECT_EQ(6, lease_mgr_->byRemoteId6size());

    Lease6Collection got;
    // Unknown remote id #2: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id2,
                                                           zero,
                                                           LeasePageSize(10)));
    EXPECT_EQ(0, got.size());

    // Remote id #0: 3 entries but 2 addresses.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id0,
                                                           zero,
                                                           LeasePageSize(10)));
    ASSERT_EQ(2, got.size());
    Lease6Ptr lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Remote id #1, partial: 2 entries.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           zero,
                                                           LeasePageSize(2)));
    ASSERT_EQ(2, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr0, lease->addr_);
    lease = got[1];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr1, lease->addr_);

    // Remote id #1, partial from previous: 1 entry.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id1,
                                                           lease->addr_,
                                                           LeasePageSize(2)));
    ASSERT_EQ(1, got.size());
    lease = got[0];
    ASSERT_TRUE(lease);
    EXPECT_EQ(lease_addr2, lease->addr_);
}

/// @brief Verifies that getLeases6ByLink works as expected.
template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testGetLeases6ByLink() {
    // Lease manager is created with empty tables.
    start(false);
    initLease6();

    // Create parameter values.
    asiolink::IOAddress link_addr(ADDRESS6[4]);
    asiolink::IOAddress other_link_addr("2001:db8:1::4");
    asiolink::IOAddress zero = asiolink::IOAddress::IPV6_ZERO_ADDRESS();

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
        EXPECT_EQ(asiolink::IOAddress(ADDRESS6[i]), lease->addr_);
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
        EXPECT_EQ(asiolink::IOAddress(ADDRESS6[i]), lease->addr_);
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
        EXPECT_EQ(asiolink::IOAddress(ADDRESS6[i + 4]), lease->addr_);
    }

    // Link: further partial: nothing.
    EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByLink(link_addr,
                                                       64,
                                                       lease->addr_,
                                                       LeasePageSize(4)));
    EXPECT_EQ(0, got.size());
}

template<typename NakedLeaseMgrType> void
GenericExtendedInfoTest<NakedLeaseMgrType>::testUpgradeExtendedInfo6(
    const CfgConsistency::ExtendedInfoSanity& check,
    bool extended_info_table_enable,
    const LeasePageSize& page_size) {

    // Lease manager is created with empty tables.
    start(false);
    initLease6();

    asiolink::IOAddress zero = asiolink::IOAddress::IPV6_ZERO_ADDRESS();
    LeasePageSize ps100(100);
    Lease6Collection got;

    // Set empty map user context to first lease.
    leases6[0]->setContext(data::Element::createMap());

    // Set old extended info format to second lease.
    std::string txt1 = "{ \"ISC\": { \"relays\": [ { \"hop\": 44,";
    txt1 += " \"link\": \"2001:db8::4\", \"peer\": \"2001:db8::5\",";
    txt1 += " \"options\": \"0x00250006010203040506003500086464646464646464\"";
    txt1 += " } ] } }";
    EXPECT_NO_THROW(leases6[1]->setContext(data::Element::fromJSON(txt1)));

    // Set third lease with two relays.
    std::string txt2 = "{ \"ISC\": { \"relay-info\": [ { \"hop\": 33,";
    txt2 += " \"link\": \"2001:db8::1\",  \"peer\": \"2001:db8::2\",";
    txt2 += " \"options\": \"0x00C800080102030405060708\" }, { \"hop\": 100,";
    txt2 += " \"options\": \"0x00250006010203040506003500086464646464646464\",";
    txt2 += " \"link\": \"2001:db8::5\", \"peer\": \"2001:db8::6\",";
    txt2 += " \"remote-id\": \"010203040506\",";
    txt2 += " \"relay-id\": \"6464646464646464\" } ] } }";
    EXPECT_NO_THROW(leases6[2]->setContext(data::Element::fromJSON(txt2)));

    // Update leases.
    for (size_t i = 0; i < leases6.size(); ++i) {
        Lease6Ptr copy(new Lease6(*leases6[i]));
        EXPECT_NO_THROW(lease_mgr_->updateLease6(copy));
    }

    // Check we have expected leases.
    checkLease6();

    // Set expected lease6.
    if (check != CfgConsistency::EXTENDED_INFO_CHECK_NONE) {
        // Reset user context for first lease.
        leases6[0]->setContext(data::ConstElementPtr());

        // Compute upgraded extended info for second lease.
        EXPECT_TRUE(LeaseMgr::upgradeLease6ExtendedInfo(leases6[1], check));
    }

    // Set extended info consistency.
    CfgMgr::instance().getCurrentCfg()->getConsistency()->
        setExtendedInfoSanityCheck(check);

    // Set extended info table enable flag.
    lease_mgr_->setExtendedInfoTablesEnabled(extended_info_table_enable);

    // Put something in extended info tables.
    ASSERT_NO_THROW(lease_mgr_->wipeExtendedInfoTables6());
    ASSERT_NO_THROW(lease_mgr_->addRelayId6(ADDRESS6[4],
                                            createFromString(DUIDS[4])));
    ASSERT_NO_THROW(lease_mgr_->addRemoteId6(ADDRESS6[5],
                                             createFromString(DUIDS[5])));

    // Run upgrade command.
    size_t updated;
    ASSERT_NO_THROW(updated = lease_mgr_->upgradeExtendedInfo6(page_size));

    // Verify result.
    checkLease6();

    // If extended info tables were not enabled they are not touched.
    if (!extended_info_table_enable) {
        EXPECT_EQ(1, lease_mgr_->byRelayId6size());
        EXPECT_EQ(1, lease_mgr_->byRemoteId6size());

        // Check relay id.
        std::vector<uint8_t> relay_id_data = createFromString(DUIDS[4]);
        DUID relay_id(relay_id_data);
        EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id,
                                                              zero,
                                                              ps100));
        ASSERT_EQ(1, got.size());
        EXPECT_EQ(asiolink::IOAddress(ADDRESS6[4]), got[0]->addr_);

        // Check remote id.
        std::vector<uint8_t> remote_id = createFromString(DUIDS[5]);
        EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id,
                                                               zero,
                                                               ps100));
        ASSERT_EQ(1, got.size());
        EXPECT_EQ(asiolink::IOAddress(ADDRESS6[5]), got[0]->addr_);
    }

    if (check == CfgConsistency::EXTENDED_INFO_CHECK_NONE) {
        if (!extended_info_table_enable) {
            // Nothing was done.
            EXPECT_EQ(0, updated);
        } else {
            // Tables were rebuilt with only the third lease.
            EXPECT_EQ(1, updated);
            EXPECT_EQ(1, lease_mgr_->byRelayId6size());
            EXPECT_EQ(1, lease_mgr_->byRemoteId6size());

            DUID relay_id(std::vector<uint8_t>(8, 0x64));
            EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id,
                                                                  zero,
                                                                  ps100));
            ASSERT_EQ(1, got.size());
            data::ConstElementPtr expected2 = leases6[2]->toElement();
            LeasePtr lease = got[0];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected2->equals(*lease->toElement()))
                << "expected2: " << expected2->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";

            std::vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
            EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id,
                                                                   zero,
                                                                   ps100));
            ASSERT_EQ(1, got.size());
            lease = got[0];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected2->equals(*lease->toElement()))
                << "expected2: " << expected2->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";
        }
    } else {
        // Updated first and second.
        if (!extended_info_table_enable) {
            // and nothing else.
            EXPECT_EQ(2, updated);
        } else {
            // Second and third leases were added to extended info tables.
            EXPECT_EQ(3, updated);
            EXPECT_EQ(2, lease_mgr_->byRelayId6size());
            EXPECT_EQ(2, lease_mgr_->byRemoteId6size());

            DUID relay_id(std::vector<uint8_t>(8, 0x64));
            EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRelayId(relay_id,
                                                                  zero,
                                                                  ps100));
            ASSERT_EQ(2, got.size());
            data::ConstElementPtr expected1 = leases6[1]->toElement();
            LeasePtr lease = got[0];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected1->equals(*lease->toElement()))
                << "expected1: " << expected1->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";
            data::ConstElementPtr expected2 = leases6[2]->toElement();
            lease = got[1];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected2->equals(*lease->toElement()))
                << "expected2: " << expected2->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";

            std::vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
            EXPECT_NO_THROW(got = lease_mgr_->getLeases6ByRemoteId(remote_id,
                                                                   zero,
                                                                   ps100));
            ASSERT_EQ(2, got.size());
            lease = got[0];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected1->equals(*lease->toElement()))
                << "expected1: " << expected1->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";
            lease = got[1];
            ASSERT_TRUE(lease);
            EXPECT_TRUE(expected2->equals(*lease->toElement()))
                << "expected2: " << expected2->str() << "\n"
                << "got: " << lease->toElement()->str() << "\n";
        }
    }
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif // GENERIC_EXTENDED_INFO_UNITTEST_H
