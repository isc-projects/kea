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
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>

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

class LeaseCmdsFuncTest6 :  public LeaseCmdsFuncTest { 
public:
    /// @brief Constructor
    LeaseCmdsFuncTest6() = default;

    /// @brief Destructor
    virtual ~LeaseCmdsFuncTest6() = default;

    /// @brief Initializes lease manager (and optionally populates it with a lease)
    void initLeaseMgr() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false " 
                                               "universe=6 extended-info-tables=true");
        lmptr_ = &(isc::dhcp::LeaseMgrFactory::instance());
        ASSERT_TRUE(lmptr_);
        lmptr_->addLease(createLease6("2001:db8:1::1", 66, 0x42));
        lmptr_->addLease(createLease6("2001:db8:1::2", 66, 0x56));
        lmptr_->addLease(createLease6("2001:db8:2::1", 99, 0x42));
        lmptr_->addLease(createLease6("2001:db8:2::2", 99, 0x56));
    }

    /// @brief Creates an IPv6 lease
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param duid_address_pattern value to be used for generating DUID by
    /// repeating it 8 times
    /// @return Returns the lease created
    isc::dhcp::Lease6Ptr createLease6(const std::string& ip_address,
                                      const isc::dhcp::SubnetID& subnet_id,
                                      const uint8_t duid_pattern) {
        isc::dhcp::Lease6Ptr lease(new isc::dhcp::Lease6());
        lease->addr_ = isc::asiolink::IOAddress(ip_address);
        lease->type_ = isc::dhcp::Lease::TYPE_NA;
        lease->prefixlen_ = 128;
        lease->iaid_ = 42;
        lease->duid_ = isc::dhcp::DuidPtr(new isc::dhcp::DUID(std::vector<uint8_t>(8, duid_pattern)));
        lease->preferred_lft_ = 1800;
        lease->valid_lft_ = 2400;
        lease->subnet_id_ = subnet_id;
        return (lease);
    }

    /// @brief Check that leases6_committed handler works as expected with
    /// valid inputs.
    void testValidLeases6Committed();

    /// @brief Check that leases6_committed handler does not throw or alter
    /// leases under NOP conditions:
    /// 1. There is no repsonse packet
    /// 2. There are no leases
    /// 3. There are leases but none active
    void testNopLeases6Committed();

    /// @brief Checks that errors occurring in leases6Committed() are handled
    /// properly.
    void testLeases6CommittedErrors();
};

void
LeaseCmdsFuncTest6::testValidLeases6Committed() {
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
        // Lease context has no binding-variables, two configured.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "duid",
                "expression": "hexstring(option[1].hex,':')",
                "source": "query"
            },
            {
                "name": "sub-id",
                "expression": "hexstring(option[38].hex, ':')",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})",
    },
    {
        // Lease context has binding-variables, none configured.
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})",
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "my-var",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "my-var": "pre-existing value"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "my-var": ""
            }
        }})",
    }
    };

    // Create packet pair and lease.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID,
                                   { 0x01, 0x02, 0x03, 0x04 }));
    query->addOption(client_id);

    Pkt6Ptr response(new Pkt6(DHCPV6_REPLY, 7890));
    OptionPtr subscriber_id(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                                       { 0x05, 0x06, 0x07, 0x08 }));
    response->addOption(subscriber_id);

    // Create a list of the lease addresses.
    std::list<IOAddress> lease_addrs;
    lease_addrs.push_back(IOAddress("2001:db8:1::1"));
    lease_addrs.push_back(IOAddress("2001:db8:1::2"));
    lease_addrs.push_back(IOAddress("2001:db8:2::2"));

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Fetch the lease and set its user-context to the original content.
        Lease6CollectionPtr orig_leases(new Lease6Collection());
        for (auto const& address : lease_addrs) {
            Lease6Ptr orig_lease = lmptr_->getLease6(Lease::TYPE_NA, address);
            ASSERT_TRUE(orig_lease);
            ASSERT_TRUE(orig_lease->valid_lft_ > 0);

            ConstElementPtr orig_context;
            ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
            orig_lease->setContext(orig_context);
            ASSERT_NO_THROW_LOG(lmptr_->updateLease6(orig_lease));
            orig_leases->push_back(orig_lease);
        }

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query6", query);
        callout_handle->setArgument("response6", response);
        callout_handle->setArgument("leases6", orig_leases);

        // Invoke the leases6Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases6Committed(*callout_handle, mgr));

        // Iterate over the leases and make sure the user-contexts are as expected.
        for (auto const& lease : *orig_leases) {
            // Fetch the lease.
            Lease6Ptr after_lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
            ASSERT_TRUE(after_lease);

            // Context contents should match the expected context content.
            ConstElementPtr exp_context;
            ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));
            ASSERT_EQ(*(after_lease->getContext()), *exp_context);
        }
    }
}

void
LeaseCmdsFuncTest6::testNopLeases6Committed() {
    struct Scenario {
        uint32_t line_;
        DHCPv6MessageType response_type_;
        bool send_lease_;
        uint32_t valid_lft_;
    };

    // Configure a single variable.
    std::string config =
    R"^({"binding-variables":[
    {
        "name": "duid",
        "expression": "hexstring(option[1].hex,':')",
        "source": "query"
    }]})^";

    // Create and configure the manager.
    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
    ASSERT_NO_THROW_LOG(mgr->configure(Element::fromJSON(config)));

    // Scenarios should all result in no change to the lease.
    std::list<Scenario> scenarios = {
    {
        // No leases.
        __LINE__,
        DHCPV6_REPLY,
        false,
        0
    },
    {
        // No active leases.
        __LINE__,
        DHCPV6_REPLY,
        true,
        0
    },
    {
        // No response.
        __LINE__,
        DHCPV6_NOTYPE,
        true,
        1000
    }};

    // Create query packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID,
                                   { 0x01, 0x02, 0x03, 0x04 }));
    query->addOption(client_id);

    IOAddress na_addr("2001:db8:1::1");
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create the response packet, if one.
        Pkt6Ptr response;
        if (scenario.response_type_ != DHCPV6_NOTYPE) {
            response.reset(new Pkt6(scenario.response_type_, 1234));
        }


        // Fetch the lease and verify there is no context content.
        Lease6Ptr orig_lease = lmptr_->getLease6(Lease::TYPE_NA, na_addr);
        ASSERT_TRUE(orig_lease);
        ASSERT_FALSE(orig_lease->getContext());
        orig_lease->valid_lft_ =  scenario.valid_lft_;

        Lease6CollectionPtr leases(new Lease6Collection());
        if (scenario.send_lease_) {
            leases->push_back(orig_lease);
        }

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query6", query);
        callout_handle->setArgument("response6", response);
        callout_handle->setArgument("leases6", leases);

        // Invoke the leases6Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases6Committed(*callout_handle, mgr));

        // Fetch the lease. Context should still be empty.
        Lease6Ptr after_lease = lmptr_->getLease6(Lease::TYPE_NA, na_addr);
        ASSERT_TRUE(after_lease);
        ASSERT_FALSE(after_lease->getContext());
    }
}

void
LeaseCmdsFuncTest6::testLeases6CommittedErrors() {
    // Create a config with two binding variables.
    std::string config_str =
        R"^({"binding-variables":[
            {
                "name": "duid",
                "expression": "hexstring(option[1].hex,':')",
                "source": "query"
            },
            {
                "name": "sub-id",
                "expression": "hexstring(option[38].hex, ':')",
                "source": "response"
            }]})^";

    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(config_str));

    // Create the expected context contents.
    std::string exp_context_str =
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})";


    ConstElementPtr exp_context;
    ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(exp_context_str));

    // Create packet pair and lease.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID,
                                   { 0x01, 0x02, 0x03, 0x04 }));
    query->addOption(client_id);

    Pkt6Ptr response(new Pkt6(DHCPV6_REPLY, 7890));
    OptionPtr subscriber_id(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                                       { 0x05, 0x06, 0x07, 0x08 }));
    response->addOption(subscriber_id);

    // Create and configure the manager.
    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
    ASSERT_NO_THROW_LOG(mgr->configure(config));

    // Fetch the leases.
    std::list<IOAddress> lease_addrs;
    lease_addrs.push_back(IOAddress("2001:db8:1::1"));
    lease_addrs.push_back(IOAddress("2001:db8:1::2"));
    lease_addrs.push_back(IOAddress("2001:db8:2::2"));

    Lease6CollectionPtr orig_leases(new Lease6Collection());
    for (auto const& address : lease_addrs) {
        Lease6Ptr orig_lease = lmptr_->getLease6(Lease::TYPE_NA, address);
        ASSERT_TRUE(orig_lease);
        orig_leases->push_back(orig_lease);
    }

    // Delete the middle lease from the back end. This should cause a conflict error.
    ASSERT_NO_THROW_LOG(lmptr_->deleteLease((*orig_leases)[1]));

    // Create a callout handle and add the expected arguments.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("query6", query);
    callout_handle->setArgument("response6", response);
    callout_handle->setArgument("leases6", orig_leases);

    // Invoke the leases6Committed handler.
    LeaseCmds cmds;
    ASSERT_THROW_MSG(cmds.leases6Committed(*callout_handle, mgr),
                     Unexpected,
                     "1 out of 3 leases failed to update for "
                     "duid=[01:02:03:04], [no hwaddr info], tid=0x4d2");

    for (auto const& lease : *orig_leases) {
        // Fetch the lease.
        Lease6Ptr after_lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
        if (after_lease) {
            // Context contents should match the expected context content.
            ASSERT_EQ(*(after_lease->getContext()), *exp_context);
        } else {
            // Middle lease should not be found.
            EXPECT_EQ(lease->addr_, (*orig_leases)[1]->addr_);
        }
    }
}

TEST_F(LeaseCmdsFuncTest6, validLeases6Committed) {
    testValidLeases6Committed();
}

TEST_F(LeaseCmdsFuncTest6, validLeases6CommittedMultiThreading) {
    MultiThreadingTest mt(true);
    testValidLeases6Committed();
}

TEST_F(LeaseCmdsFuncTest6, nopLeases6Committed) {
    testNopLeases6Committed();
}

TEST_F(LeaseCmdsFuncTest6, nopLeases6CommittedMultiThreading) {
    MultiThreadingTest mt(true);
    testNopLeases6Committed();
}

TEST_F(LeaseCmdsFuncTest6, leases6CommittedErrors) {
    testLeases6CommittedErrors();
}

TEST_F(LeaseCmdsFuncTest6, leases6CommittedErrorsMultiThreading) {
    MultiThreadingTest mt(true);
    testLeases6CommittedErrors();
}

} // end of anonymous namespace
