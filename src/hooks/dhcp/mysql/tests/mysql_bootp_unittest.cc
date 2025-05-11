// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/testutils/alloc_engine_utils.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <mysql/testutils/mysql_schema.h>
#include <mysql_lease_mgr.h>
#include <util/triplet.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

/// @brief Extension of the fixture class to use the MySQL backend.
class MySqlAllocEngine4Test : public AllocEngine4Test {
public:
    /// @brief Constructor.
    MySqlAllocEngine4Test() {
        // Ensure we have the proper schema with no transient data.
        isc::db::test::createMySQLSchema();
        factory_.create(isc::db::test::validMySQLConnectionString());
    }

    /// @brief Destructor.
    ~MySqlAllocEngine4Test() {
        // If data wipe enabled, delete transient data otherwise destroy
        // the schema.
        isc::db::test::destroyMySQLSchema();
        LeaseMgrFactory::destroy();
    }

    /// @brief Initializer.
    MySqlLeaseMgrInit init_;
};

// This test checks that simple allocation handles BOOTP queries.
TEST_F(MySqlAllocEngine4Test, bootpAlloc4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(0)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);
    // The MySQL database does not keep the hwtype for DHCPv4 leases.
    from_mgr->hwaddr_->htype_ = HTYPE_FDDI;

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease(lease, from_mgr);
}

// This test checks simple renewal handles BOOTP queries.
TEST_F(MySqlAllocEngine4Test, bootpRenew4) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(0)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Do it again, this should amount to the renew of an existing lease
    Lease4Ptr lease2 = engine->allocateLease4(ctx);

    // Check that we got a lease.
    ASSERT_TRUE(lease2);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease2->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease2->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease2->addr_));
    ASSERT_TRUE(lease2->client_id_);
    EXPECT_TRUE(*lease2->client_id_ == *clientid_);
    ASSERT_TRUE(lease2->hwaddr_);
    EXPECT_TRUE(*lease2->hwaddr_ == *hwaddr_);

    // Lease already existed, so old_lease should be set.
    EXPECT_TRUE(ctx.old_lease_);

    // Check the renewed valid lifetime has the max value.
    EXPECT_EQ(infinity_lft, lease2->valid_lft_);
}

// This test checks that deleteRelease handles BOOTP leases.
TEST_F(MySqlAllocEngine4Test, bootpDelete) {
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(0)));
    ASSERT_TRUE(engine);

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    subnet_->setValid(Triplet<uint32_t>(1, 3, 5));
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));

    // Make the query a BOOTP one.
    ctx.query_->addClass("BOOTP");

    Lease4Ptr lease = engine->allocateLease4(ctx);
    // The new lease has been allocated, so the old lease should not exist.
    ASSERT_FALSE(ctx.old_lease_);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Check that is belongs to the right subnet and client.
    EXPECT_EQ(lease->subnet_id_, subnet_->getID());
    EXPECT_TRUE(subnet_->inRange(lease->addr_));
    EXPECT_TRUE(subnet_->inPool(Lease::TYPE_V4, lease->addr_));
    ASSERT_TRUE(lease->client_id_);
    EXPECT_TRUE(*lease->client_id_ == *clientid_);
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_TRUE(*lease->hwaddr_ == *hwaddr_);

    // Check the valid lifetime is infinite.
    uint32_t infinity_lft = Lease::INFINITY_LFT;
    EXPECT_EQ(infinity_lft, lease->valid_lft_);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now delete it.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = LeaseMgrFactory::instance().deleteLease(lease));
    EXPECT_TRUE(deleted);
    from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    EXPECT_FALSE(from_mgr);
}

}
