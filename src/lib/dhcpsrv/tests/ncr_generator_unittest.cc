// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/lease.h>

#include <ctime>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

#include <stdint.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;

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

    /// @brief Constructor.
    NCRGeneratorTest()
        : d2_mgr_(CfgMgr::instance().getD2ClientMgr()), lease_() {
    }

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
        d2_mgr_.startSender(boost::bind(&NCRGeneratorTest::d2ErrorHandler, this,
                                        _1, _2));
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
    /// @param forward An expected setting of the forward udpate flag.
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
                                 const std::string& fqdn="") {
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
    void testNCR(const NameChangeType chg_type, const bool fwd, const bool rev,
                 const std::string& fqdn, const std::string exp_dhcid) {
        // Queue NCR.
        ASSERT_NO_FATAL_FAILURE(sendNCR(chg_type, fwd, rev, fqdn));
        // Expecting one NCR be generated.
        ASSERT_EQ(1, d2_mgr_.getQueueSize());
        // Check the details of the NCR.
        verifyNameChangeRequest(chg_type, rev, fwd, lease_->addr_.toText(), exp_dhcid,
                                lease_->cltt_ + lease_->valid_lft_,
                                lease_->valid_lft_);
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
        lease_.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                                duid_, 1234, 501, 502, 503,
                                504, 1, HWAddrPtr(), 0));
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
    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "MYHOST.example.com.",
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
TEST_F(NCRGenerator6Test, removeRev) {
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
        testNoUpdate(CHG_REMOVE, false, false, "");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "");
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

    /// @brief Implementation of the method creating DHCPv6 lease instance.
    virtual void initLease() {
        lease_.reset(new Lease4(IOAddress("2001:db8:1::1"), hwaddr_, ClientIdPtr(),
                                100, 30, 60, time(NULL), 1));
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
    {
        SCOPED_TRACE("case CHG_ADD");
        testNCR(CHG_ADD, true, true, "MYHOST.example.com.",
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
TEST_F(NCRGenerator4Test, removeRev) {
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
        testNoUpdate(CHG_REMOVE, false, false, "");
    }
    {
        SCOPED_TRACE("case CHG_ADD");
        testNoUpdate(CHG_ADD, false, false, "");
    }
}

// Test that the correct NameChangeRequest is generated when the lease
// includes client identifier.
TEST_F(NCRGenerator4Test, useClientId) {
    lease_->client_id_ = ClientId::fromText("01:01:01:01");

    ASSERT_NO_FATAL_FAILURE(queueRemovalNCR(true, true, "myhost.example.com."));
    ASSERT_EQ(1, d2_mgr_.getQueueSize());

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1::1",
                            "000101C7AA5420483BDA99C437636EA7DA2FE18"
                            "31C9679FEB031C360CA571298F3D1FA",
                            lease_->cltt_ + lease_->valid_lft_, 100);
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

} // end of anonymous namespace
