// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/lease.h>

#include <gtest/gtest.h>
#include <ctime>
#include <functional>
#include <stdint.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
namespace ph = std::placeholders;

namespace {

/// @brief Base test fixture class for testing generation of the name
/// change requests from leases.
///
/// @tparam LeasePtrType One of the @c Lease4Ptr or @c Lease6Ptr.
template<typename LeasePtrType>
class NCRGeneratorTest : public ::testing::Test {
public:

    /// @brief Reference to the D2 client manager.
    D2ClientMgr& d2_mgr_;

    /// @brief Pointer to the lease object used by the tests.
    LeasePtrType lease_;

    /// @brief Pointer to the lease's subnet
    SubnetPtr subnet_;

    /// @brief Constructor.
    NCRGeneratorTest()
        : d2_mgr_(CfgMgr::instance().getD2ClientMgr()), lease_() {
    }

    /// @brief Destructor
    virtual ~NCRGeneratorTest() = default;

    /// @brief Initializes the lease pointer used by the tests and starts D2.
    ///
    /// This method initializes the pointer to the lease which will be used
    /// throughout the tests. Because the lease may be either a v4 or v6 lease
    /// it calls a virtual function @c initLease, which must be implemented
    /// in the derived classes as appropriate. Note that lease object can't
    /// be initialized in the constructor, because it is not allowed to
    /// call virtual functions in the constructors. Hence, the @c SetUp
    /// function is needed.
    virtual void SetUp() {
        // Base class SetUp.
        ::testing::Test::SetUp();
        // Initialize lease_ object.
        initLease();
        // Start D2 by default.
        enableD2();
    }

    /// @brief Stops D2.
    virtual void TearDown() {
        // Stop D2 if running.
        disableD2();
        // Base class TearDown.
        ::testing::Test::TearDown();

        CfgMgr::instance().clear();
    }

    /// @brief Enables DHCP-DDNS updates.
    ///
    /// Replaces the current D2ClientConfiguration with a configuration
    /// which has updates enabled and the control options set based upon
    /// the bit mask of options.
    void enableD2() {
        D2ClientConfigPtr cfg(new D2ClientConfig());
        ASSERT_NO_THROW(cfg->enableUpdates(true));
        ASSERT_NO_THROW(CfgMgr::instance().setD2ClientConfig(cfg));
        d2_mgr_.startSender(std::bind(&NCRGeneratorTest::d2ErrorHandler, this,
                                      ph::_1, ph::_2));
    }

    /// @brief Disables DHCP-DDNS updates.
    void disableD2() {
        d2_mgr_.stopSender();
        // Default constructor creates a config with DHCP-DDNS updates
        // disabled.
        D2ClientConfigPtr cfg(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(cfg);
    }

    /// @brief No-op error handler for D2.
    void d2ErrorHandler(const NameChangeSender::Result, NameChangeRequestPtr&) {
        // no-op
    }

    /// @brief Abstract method to initialize @c lease_ object.
    virtual void initLease() = 0;

    /// @brief Verify that NameChangeRequest holds valid values.
    ///
    /// This function picks first NameChangeRequest from the internal server's
    /// queue and checks that it holds valid parameters. The NameChangeRequest
    /// is removed from the queue.
    ///
    /// @param type An expected type of the NameChangeRequest (Add or Remove).
    /// @param reverse An expected setting of the reverse update flag.
    /// @param forward An expected setting of the forward update flag.
    /// @param addr A string representation of the IPv6 address held in the
    /// NameChangeRequest.
    /// @param dhcid An expected DHCID value.
    /// @note This value is the value that is produced by
    /// dhcp_ddns::D2Dhcid::createDigest() with the appropriate arguments. This
    /// method uses encryption tools to produce the value which cannot be
    /// easily duplicated by hand.  It is more or less necessary to generate
    /// these values programmatically and place them here. Should the
    /// underlying implementation of createDigest() change these test values
    /// will likely need to be updated as well.
    /// @param expires A timestamp when the lease associated with the
    /// NameChangeRequest expires.
    /// @param len A valid lifetime of the lease associated with the
    /// NameChangeRequest.
    /// @param fqdn The expected string value of the FQDN, if blank the
    /// check is skipped
    void verifyNameChangeRequest(const isc::dhcp_ddns::NameChangeType type,
                                 const bool reverse, const bool forward,
                                 const std::string& addr,
                                 const std::string& dhcid,
                                 const uint64_t expires,
                                 const uint16_t len,
                                 const std::string& fqdn="",
                                 const bool use_conflict_resolution = true) {
        NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = CfgMgr::instance().getD2ClientMgr().peekAt(0));
        ASSERT_TRUE(ncr);

        EXPECT_EQ(type, ncr->getChangeType());
        EXPECT_EQ(forward, ncr->isForwardChange());
        EXPECT_EQ(reverse, ncr->isReverseChange());
        EXPECT_EQ(addr, ncr->getIpAddress());
        EXPECT_EQ(dhcid, ncr->getDhcid().toStr());
        EXPECT_EQ(expires, ncr->getLeaseExpiresOn());
        EXPECT_EQ(len, ncr->getLeaseLength());
        EXPECT_EQ(isc::dhcp_ddns::ST_NEW, ncr->getStatus());
        EXPECT_EQ(use_conflict_resolution, ncr->useConflictResolution());

        if (!fqdn.empty()) {
           EXPECT_EQ(fqdn, ncr->getFqdn());
        }

        // Process the message off the queue
        ASSERT_NO_THROW(CfgMgr::instance().getD2ClientMgr().runReadyIO());
    }

    /// @brief Sets the FQDN information for a lease and queues an NCR.
    ///
    /// @param fwd Perform forward update.
    /// @param rev Perform reverse update.
    /// @param fqdn Hostname.
    void queueRemovalNCR(const bool fwd, const bool rev, const std::string& fqdn) {
        lease_->fqdn_fwd_ = fwd;
        lease_->fqdn_rev_ = rev;
        lease_->hostname_ = fqdn;

        /// Send NCR to D2.
        ASSERT_NO_THROW(queueNCR(CHG_REMOVE, lease_));
    }

    /// @brief Sets the FQDN information for a lease and queues an NCR.
    ///
    /// @param chg_type Name change type.
    /// @param fwd Perform forward update.
    /// @param rev Perform reverse update.
    /// @param fqdn Hostname.
    void sendNCR(const NameChangeType chg_type, const bool fwd, const bool rev,
                 const std::string& fqdn) {
        lease_->fqdn_fwd_ = fwd;
        lease_->fqdn_rev_ = rev;
        lease_->hostname_ = fqdn;

        /// Send NCR to D2.
        ASSERT_NO_THROW(queueNCR(chg_type, lease_));
    }

    /// @brief Test that for the given values the NCR is not generated.
    ///
    /// @param chg_type Name change type.
    /// @param fwd Perform forward update.
    /// @param rev Perform reverse update.
    /// @param fqdn Hostname.
    void testNoUpdate(const NameChangeType chg_type, const bool fwd, const bool rev,
                      const std::string& fqdn) {
        ASSERT_NO_FATAL_FAILURE(sendNCR(chg_type, fwd, rev, fqdn));
        ASSERT_EQ(0, d2_mgr_.getQueueSize());
    }

    /// @brief Test that sending an NCR while DNS updates would not throw.
    ///
    /// @param chg_type Name change type.
    void testD2Disabled(const NameChangeType chg_type) {
        // Disable DDNS updates.
        disableD2();
        ASSERT_NO_FATAL_FAILURE(sendNCR(chg_type, true, true, "MYHOST.example.com."));
    }

    /// @brief Test that NCR is generated as expected.
    ///
    /// @param chg_type Name change type.
    /// @param fwd Perform forward update.
    /// @param rev Perform reverse update.
    /// @param fqdn Hostname.
    /// @param exp_dhcid Expected DHCID.
    /// @param exp_use_cr expected value of conflict resolution flag
    void testNCR(const NameChangeType chg_type, const bool fwd, const bool rev,
                 const std::string& fqdn, const std::string exp_dhcid,
                 const bool exp_use_cr = true) {
        // Queue NCR.
        ASSERT_NO_FATAL_FAILURE(sendNCR(chg_type, fwd, rev, fqdn));
        // Expecting one NCR be generated.
        ASSERT_EQ(1, d2_mgr_.getQueueSize());

        uint32_t ttl = calculateDdnsTtl(lease_->valid_lft_);

        // Check the details of the NCR.
        verifyNameChangeRequest(chg_type, rev, fwd, lease_->addr_.toText(), exp_dhcid,
                                lease_->cltt_ + ttl, ttl, fqdn, exp_use_cr);
    }

    /// @brief Test that calling queueNCR for NULL lease doesn't cause
    /// an exception.
    ///
    /// @param chg_type Name change type.
    void testNullLease(const NameChangeType chg_type) {
        lease_.reset();
        ASSERT_NO_FATAL_FAILURE(queueNCR(chg_type, lease_));
        EXPECT_EQ(0, d2_mgr_.getQueueSize());
    }
};

/// @brief Test fixture class implementation for DHCPv6.
class NCRGenerator6Test : public NCRGeneratorTest<Lease6Ptr> {
public:

    /// @brief Pointer to the DUID used in the tests.
    DuidPtr duid_;

    /// @brief Constructor.
    ///
    /// Initializes DUID.
    NCRGenerator6Test()
        : duid_() {
        duid_.reset(new DUID(DUID::fromText("01:02:03:04:05:06:07:08:09")));
    }

    /// @brief Implementation of the method creating DHCPv6 lease instance.
    virtual void initLease() {
        Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 64, 100, 200, 300, 400));
        // Normally, this would be set via defaults
        subnet->setDdnsUseConflictResolution(true);

        Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                                IOAddress("2001:db8:1::200")));
        subnet->addPool(pool);
        subnet_ = subnet;

        CfgMgr& cfg_mgr = CfgMgr::instance();
        cfg_mgr.getStagingCfg()->getCfgSubnets6()->add(subnet);
        cfg_mgr.commit();

        lease_.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                                duid_, 1234, 501, 502, subnet_->getID(), HWAddrPtr()));
    }
};


// Test creation of the NameChangeRequest for both forward and reverse
// mapping for the given lease.
TEST_F(NCRGenerator6Test, fwdRev) {
    // Part of the domain name is in upper case, to test that it gets converted
    // to lower case before DHCID is computed. So, we should get the same DHCID
    // as if we typed domain-name in lower case.
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, true, "MYHOST.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }

    // Now try the same test with all lower case.
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, true, "myhost.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }

    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "MYHOST.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }

    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "myhost.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }

}

// Checks that NameChangeRequests are not created when ddns updates are disabled.
TEST_F(NCRGenerator6Test, d2Disabled) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testD2Disabled(CHG_REMOVE);
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testD2Disabled(CHG_ADD);
    }
}

// Test creation of the NameChangeRequest for reverse mapping in the
// given lease.
TEST_F(NCRGenerator6Test, revOnly) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, false, true, "myhost.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }

    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, false, true, "myhost.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }
}

// Test creation of the NameChangeRequest for forward mapping in the
// given lease.
TEST_F(NCRGenerator6Test, fwdOnly) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, false, "myhost.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }

    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, false, "myhost.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3"
                "D0ECCEA5E0DD71730F392119A");
    }
}


// Test that NameChangeRequest is not generated when neither forward
// nor reverse DNS update has been performed for a lease.
TEST_F(NCRGenerator6Test, noFwdRevUpdate) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, false, false, "myhost.example.com.");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "myhost.example.com.");
    }
}

// Test that NameChangeRequest is not generated if the hostname hasn't been
// specified for a lease for which forward and reverse mapping has been set.
TEST_F(NCRGenerator6Test, noHostname) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, false, false, "");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "");
    }
}

// Test that NameChangeRequest is not generated if an invalid hostname has
// been specified for a lease for which forward and reverse mapping has been
// set.
TEST_F(NCRGenerator6Test, wrongHostname) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, false, false, "myhost...example.com.");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "myhost...example.com.");
    }
}

// Test that NameChangeRequest is not generated if the lease is not an
// address lease, i.e. is a prefix.
TEST_F(NCRGenerator6Test, wrongLeaseType) {
    // Change lease type to delegated prefix.
    lease_->type_ = Lease::TYPE_PD;

    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, true, true, "myhost.example.org.");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, true, true, "myhost.example.org.");
    }
}

// Test that NameChangeRequest is not generated if the lease is NULL,
// and that the call to queueNCR doesn't cause an exception or
// assertion.
TEST_F(NCRGenerator6Test, nullLease) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNullLease(CHG_REMOVE);
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNullLease(CHG_ADD);
    }
}

// Verify that conflict resolution is set correctly by v6 queueNCR()
TEST_F(NCRGenerator6Test, useConflictResolution) {
    {
        SCOPED_TRACE("Subnet flag is false");
        subnet_->setDdnsUseConflictResolution(false);
        testNCR(CHG_REMOVE, true, true, "MYHOST.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3D0ECCEA5E0DD71730F392119A",
                false);
    }
    {
        SCOPED_TRACE("Subnet flag is true");
        subnet_->setDdnsUseConflictResolution(true);
        testNCR(CHG_REMOVE, true, true, "MYHOST.example.com.",
                "000201BE0D7A66F8AB6C4082E7F8B81E2656667A102E3D0ECCEA5E0DD71730F392119A",
                true);
    }
}

/// @brief Test fixture class implementation for DHCPv4.
class NCRGenerator4Test : public NCRGeneratorTest<Lease4Ptr> {
public:

    /// @brief Pointer to HW address used by the tests.
    HWAddrPtr hwaddr_;

    /// @brief Constructor.
    ///
    /// Initializes HW address.
    NCRGenerator4Test()
        : hwaddr_(new HWAddr(HWAddr::fromText("01:02:03:04:05:06"))) {
    }

    /// @brief Implementation of the method creating DHCPv4 lease instance.
    virtual void initLease() {

        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3));
        // Normally, this would be set via defaults
        subnet->setDdnsUseConflictResolution(true);

        Pool4Ptr pool(new Pool4(IOAddress("192.0.2.100"),
                                IOAddress("192.0.2.200")));
        subnet->addPool(pool);

        CfgMgr& cfg_mgr = CfgMgr::instance();
        cfg_mgr.getStagingCfg()->getCfgSubnets4()->add(subnet);
        cfg_mgr.commit();

        subnet_ = subnet;
        lease_.reset(new Lease4(IOAddress("192.0.2.1"), hwaddr_, ClientIdPtr(),
                                100, time(NULL), subnet_->getID()));
    }

};

// Test creation of the NameChangeRequest for both forward and reverse
// mapping for the given lease.
TEST_F(NCRGenerator4Test, fwdRev) {
    // Part of the domain name is in upper case, to test that it gets converted
    // to lower case before DHCID is computed. So, we should get the same DHCID
    // as if we typed domain-name in lower case.
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, true, "MYHOST.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3"
                "B03AB370BFF46BFA309AE7BFD");
    }

    // Now try the same with all lower case.
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, true, "myhost.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3"
                "B03AB370BFF46BFA309AE7BFD");
    }

    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "MYHOST.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3"
                "B03AB370BFF46BFA309AE7BFD");
    }

    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "myhost.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3"
                "B03AB370BFF46BFA309AE7BFD");
    }
}

// Checks that NameChangeRequests are not created when ddns updates are disabled.
TEST_F(NCRGenerator4Test, d2Disabled) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testD2Disabled(CHG_REMOVE);
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testD2Disabled(CHG_ADD);
    }
}

// Test creation of the NameChangeRequest for reverse mapping in the
// given lease.
TEST_F(NCRGenerator4Test, revOnly) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, false, true, "myhost.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3B"
                "03AB370BFF46BFA309AE7BFD");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, false, true, "myhost.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3B"
                "03AB370BFF46BFA309AE7BFD");
    }
}

// Test creation of the NameChangeRequest for forward mapping in the
// given lease.
TEST_F(NCRGenerator4Test, fwdOnly) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, false, "myhost.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3B"
                "03AB370BFF46BFA309AE7BFD");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, false, "myhost.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3B"
                "03AB370BFF46BFA309AE7BFD");
    }
}

// Test that NameChangeRequest is not generated when neither forward
// nor reverse DNS update has been performed for a lease.
TEST_F(NCRGenerator4Test, noFwdRevUpdate) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, false, false, "myhost.example.com.");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "myhost.example.com.");
    }
}

// Test that NameChangeRequest is not generated if the hostname hasn't been
// specified for a lease for which forward and reverse mapping has been set.
TEST_F(NCRGenerator4Test, noHostname) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, false, false, "");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "");
    }
}

// Test that NameChangeRequest is not generated if the invalid hostname has
// been specified for a lease for which forward and reverse mapping has been
// set.
TEST_F(NCRGenerator4Test, wrongHostname) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNoUpdate(CHG_REMOVE, false, false, "myhost...example.org.");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "myhost...example.org.");
    }
}

// Test that the correct NameChangeRequest is generated when the lease
// includes client identifier.
TEST_F(NCRGenerator4Test, useClientId) {
    lease_->client_id_ = ClientId::fromText("01:01:01:01");

    ASSERT_NO_FATAL_FAILURE(queueRemovalNCR(true, true, "myhost.example.com."));
    ASSERT_EQ(1, d2_mgr_.getQueueSize());

    uint32_t ttl = calculateDdnsTtl(lease_->valid_lft_);
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "192.0.2.1",
                            "000101C7AA5420483BDA99C437636EA7DA2FE18"
                            "31C9679FEB031C360CA571298F3D1FA",
                            lease_->cltt_ + ttl, ttl);
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNCR(CHG_REMOVE, true, true, "myhost.example.com.",
                "000101C7AA5420483BDA99C437636EA7DA2FE1831C9679"
                "FEB031C360CA571298F3D1FA");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "myhost.example.com.",
                "000101C7AA5420483BDA99C437636EA7DA2FE1831C9679"
                "FEB031C360CA571298F3D1FA");
    }
}

// Test that NameChangeRequest is not generated if the lease is NULL,
// and that the call to queueNCR doesn't cause an exception or
// assertion.
TEST_F(NCRGenerator4Test, nullLease) {
    {
        SCOPED_TRACE("case CHG_REMOVE");
        testNullLease(CHG_REMOVE);
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNullLease(CHG_ADD);
    }
}

// Verify that conflict resolution is set correctly by v4 queueNCR()
TEST_F(NCRGenerator4Test, useConflictResolution) {
    {
        SCOPED_TRACE("Subnet flag is false");
        subnet_->setDdnsUseConflictResolution(false);
        testNCR(CHG_REMOVE, true, true, "MYHOST.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3"
                "B03AB370BFF46BFA309AE7BFD", false);
    }
    {
        SCOPED_TRACE("Subnet flag is true");
        subnet_->setDdnsUseConflictResolution(true);
        testNCR(CHG_REMOVE, true, true, "MYHOST.example.com.",
                "000001E356D43E5F0A496D65BCA24D982D646140813E3"
                "B03AB370BFF46BFA309AE7BFD", true);
    }
}

// Verify that calculateDdnsTtl() produces the expected values.
TEST_F(NCRGenerator4Test, calculateDdnsTtl) {

    // A life time less than or equal to 1800 should yield a TTL of 600 seconds.
    EXPECT_EQ(600, calculateDdnsTtl(100));

    // A life time > 1800 should be 1/3 of the value.
    EXPECT_EQ(601, calculateDdnsTtl(1803));
}

} // end of anonymous namespace
