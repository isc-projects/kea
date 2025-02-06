// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <lease_cmds.h>
#include <lease_cmds_func_unittest.h>
#include <hooks/hooks_manager.h>
#include <dhcpsrv/lease_mgr.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcp/pkt4.h>

#include <testutils/gtest_utils.h>
#include <testutils/user_context_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::test;
using namespace isc::asiolink;
using namespace isc::hooks;

using namespace isc::lease_cmds;

namespace {

class LeaseCmdsFuncTest4 :  public LeaseCmdsFuncTest { 
public:
    /// @brief Constructor
    LeaseCmdsFuncTest4() = default;

    /// @brief Destructor
    ///
    virtual ~LeaseCmdsFuncTest4() = default;

    /// @brief Creates an IPv4 lease
    ///
    /// Lease parameters: valid lifetime = 0xFFFFFFFE, cltt = 1923222072, fqdn-fwd = false,
    /// fqdn-rev = true, hostname = myhost.example.com
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param hw_address_pattern value to be used for generating HW address by repeating
    /// it 6 times.
    /// @param client_id_pattern value to be used for generating client identifier by
    /// repeating it 8 times.
    ///
    /// @return Returns the lease created
    Lease4Ptr createLease(const std::string& ip_address,
                          const SubnetID& subnet_id,
                          const uint8_t hw_address_pattern,
                          const uint8_t client_id_pattern,
                          uint32_t pool_id = 0) {
        Lease4Ptr lease(new Lease4());
        lease->addr_ = IOAddress(ip_address);

        lease->hwaddr_.reset(new HWAddr(std::vector<uint8_t>(6, hw_address_pattern), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(new ClientId(std::vector<uint8_t>(8, client_id_pattern)));
        lease->valid_lft_ = 2400;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = subnet_id;
        lease->pool_id_ = pool_id;
        return (lease);
    }

    /// @brief Initializes lease manager (and optionally populates it with a lease)
    ///
    /// Creates a lease manager and initial leases.
    /// only) and optionally can create a lease, which is useful for leaseX-get and
    /// leaseX-del type of tests. For lease details, see @ref createLease and
    /// @ref createLease6.
    ///
    virtual void initLeaseMgr() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=4");
        lmptr_ = &(LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);

        lmptr_->addLease(createLease("192.0.2.1", 44, 0x08, 0x42));
        lmptr_->addLease(createLease("192.0.2.2", 44, 0x09, 0x56));
        lmptr_->addLease(createLease("192.0.3.1", 88, 0x08, 0x42));
        lmptr_->addLease(createLease("192.0.3.2", 88, 0x09, 0x56));
    }

    /// @brief Check that lease4_offer handler works as expected with
    /// valid inputs.
    void testValidLease4Offer();

    /// @brief Check that leases4_committed handler works as expected with
    /// valid inputs.
    void testValidLeases4Committed();

    /// @brief Check that leases4_committed handler does not throw or alter
    /// the lease under NOP conditions: 
    /// 1. There is no repsonse packet
    /// 2. Response packet is a DHCPACK 
    /// 3. There is no active lease
    void testNopLeases4Committed();
};

void
LeaseCmdsFuncTest4::testValidLease4Offer() {
    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
        uint32_t offer_lifetime_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})",
        500
    },
    {
        // lease context has no binding-variables, two configured
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        500
    },
    {
        // lease context has no binding-variables, two configured
        // offer lifetime is 0.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({})",
        0
    },
    {
        // lease context has binding-variables, none configured
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        500
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": ""
            }
        }})",
        500
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });

    Pkt4Ptr response(new Pkt4(DHCPOFFER, 1234));
    IOAddress yiaddr("192.0.2.1");
    response->setYiaddr(yiaddr);

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Fetch the lease and set its user-context to the original content.
        Lease4Ptr orig_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(orig_lease);
        ConstElementPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
        orig_lease->setContext(orig_context);
        ASSERT_NO_THROW_LOG(lmptr_->updateLease4(orig_lease));

        Lease4CollectionPtr leases(new Lease4Collection());
        leases->push_back(orig_lease);

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("response4", response);
        callout_handle->setArgument("leases4", leases);
        callout_handle->setArgument("offer_lifetime", scenario.offer_lifetime_);

        // Invoke the leases4Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.lease4Offer(*callout_handle, mgr));

        // Fetch the lease.
        Lease4Ptr after_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(after_lease);

        // Context contents should match the expected context content.
        ConstElementPtr exp_context;
        ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));
        ASSERT_EQ(*(after_lease->getContext()), *exp_context);
    }
}

void
LeaseCmdsFuncTest4::testValidLeases4Committed() {
    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})"
    },
    {
        // lease context has no binding-variables, two configured
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
    },
    {
        // lease context has binding-variables, none configured
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": ""
            }
        }})",
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPREQUEST, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });

    Pkt4Ptr response(new Pkt4(DHCPACK, 1234));
    IOAddress yiaddr("192.0.2.1");
    response->setYiaddr(yiaddr);

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Fetch the lease and set its user-context to the original content.
        Lease4Ptr orig_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(orig_lease);
        ConstElementPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
        orig_lease->setContext(orig_context);
        ASSERT_NO_THROW_LOG(lmptr_->updateLease4(orig_lease));

        Lease4CollectionPtr leases(new Lease4Collection());
        leases->push_back(orig_lease);

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("response4", response);
        callout_handle->setArgument("leases4", leases);

        // Invoke the leases4Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases4Committed(*callout_handle, mgr));

        // Fetch the lease.
        Lease4Ptr after_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(after_lease);

        // Context contents should match the expected context content.
        ConstElementPtr exp_context;
        ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));
        ASSERT_EQ(*(after_lease->getContext()), *exp_context);
    }
}

void
LeaseCmdsFuncTest4::testNopLeases4Committed() {
    struct Scenario {
        uint32_t line_;
        DHCPMessageType response_type_;
        bool send_lease_;
    };

    // Configure a single variable.
    std::string config =
    R"^({"binding-variables":[
    {
        "name": "hwaddr",
        "expression": "hexstring(pkt4.mac,':')",
        "source": "query"
    }]})^";

    // Create and configure the manager.
    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
    ASSERT_NO_THROW_LOG(mgr->configure(Element::fromJSON(config)));

    // Scenarios should all result in no change to the lease.
    std::list<Scenario> scenarios = {
    {
        // Response is not a DHCPACK.
        __LINE__,
        DHCPNAK,
        true
    },
    {
        // No active lease.
        __LINE__,
        DHCPACK,
        false
    },
    {
        // No response.
        __LINE__,
        DHCP_NOTYPE,
        false
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPREQUEST, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });
    IOAddress yiaddr("192.0.2.1");
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        Pkt4Ptr response;
        if (scenario.response_type_ != DHCP_NOTYPE) {
            response.reset(new Pkt4(scenario.response_type_, 1234));
        }

        // Fetch the lease and set its user-context to the original content.
        Lease4Ptr orig_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(orig_lease);
        ASSERT_FALSE(orig_lease->getContext());

        Lease4CollectionPtr leases(new Lease4Collection());
        if (scenario.send_lease_) {
            leases->push_back(orig_lease);
        }

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("response4", response);
        callout_handle->setArgument("leases4", leases);

        // Invoke the leases4Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases4Committed(*callout_handle, mgr));

        // Fetch the lease. Context should still be empty.
        Lease4Ptr after_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(after_lease);
        ASSERT_FALSE(after_lease->getContext());
    }
}

TEST_F(LeaseCmdsFuncTest4, validLease4Offer) {
    testValidLease4Offer();
}

TEST_F(LeaseCmdsFuncTest4, validLease4OfferMultiThreading) {
    MultiThreadingTest mt(true);
    testValidLease4Offer();
}

TEST_F(LeaseCmdsFuncTest4, validLeases4Committed) {
    testValidLeases4Committed();
}

TEST_F(LeaseCmdsFuncTest4, validLeases4CommittedMultiThreading) {
    MultiThreadingTest mt(true);
    testValidLeases4Committed();
}

TEST_F(LeaseCmdsFuncTest4, nopLeases4Committed) {
    testNopLeases4Committed();
}

TEST_F(LeaseCmdsFuncTest4, nopLeases4CommittedMultiThreading) {
    MultiThreadingTest mt(true);
    testNopLeases4Committed();
}

} // end of anonymous namespace
