// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible identifier callouts.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/option_string.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcpsrv/host.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <flex_id.h>
#include <flex_id_log.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::hooks;

extern "C" {
extern int host4_identifier(CalloutHandle& handle);
extern int host6_identifier(CalloutHandle& handle);
extern int pkt4_receive(CalloutHandle& handle);
extern int pkt4_send(CalloutHandle& handle);
extern int pkt6_receive(CalloutHandle& handle);
extern int pkt6_send(CalloutHandle& handle);
}

namespace {

/// @brief Test fixture for exercising flex-id library callouts
/// It fetches the CalloutManager and prepares stub packets that can be used in
/// tests.
class CalloutTest : public ::testing::Test {
public:

    /// @brief Data structure indicating if flex-id should be used for client
    /// identification in the lease database.
    struct FlexIdForLeases {

        /// @brief Constructor.
        ///
        /// @param use_for_leases Flag indicating if flex-id should be used for
        /// leases.
        explicit FlexIdForLeases(const bool use_for_leases)
            : value_(use_for_leases) { }

        bool value_;
    };

    /// @brief Constructor
    /// Fetches the current day and removes files that may be left
    /// over from previous tests
    CalloutTest() : co_manager_(new CalloutManager(1)) {
        isc::flex_id::storeConfiguration(false, "1", true, false);

        pkt4_.reset(new Pkt4(DHCPDISCOVER, 12345));
        pkt6_.reset(new Pkt6(DHCPV6_SOLICIT, 12345));

        response4_.reset(new Pkt4(DHCPOFFER, 12345));
        response6_.reset(new Pkt6(DHCPV6_ADVERTISE, 12345));

        // Add options with easily identifiable strings in them
        option_str4_.reset(new OptionString(Option::V4, 100, "hundred4"));
        option_str6_.reset(new OptionString(Option::V6, 100, "hundred6"));

        pkt4_->addOption(option_str4_);
        pkt6_->addOption(option_str6_);

    }

    /// @brief Destructor
    ///
    /// Removes configuration applied by a test.
    virtual ~CalloutTest() {
        isc::flex_id::clearConfiguration();
    }

    /// @brief Fetches the callout manager instance
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

    /// @brief Tests host4_identifier callout
    ///
    /// @param expr expression to be used (in textual form)
    /// @param expected expected value of the identifier
    void host4_identifierCall(const std::string& expr,
                              const std::vector<uint8_t>& expected) {

        isc::flex_id::storeConfiguration(false, expr, true, false);

        // Make a callout handle
        CalloutHandle handle(getCalloutManager());
        Host::IdentifierType type = Host::IDENT_FLEX;
        std::vector<uint8_t> id;

        handle.setArgument("query4", pkt4_);
        handle.setArgument("id_type", type);
        handle.setArgument("id_value", id);

        // The callout should succeed.
        int ret;
        ASSERT_NO_THROW(ret = host4_identifier(handle));
        EXPECT_EQ(0, ret);

        Host::IdentifierType type_returned;
        std::vector<uint8_t> id_returned;
        handle.getArgument("id_type", type_returned);
        handle.getArgument("id_value", id_returned);

        ASSERT_EQ(expected.size(), id_returned.size());
        EXPECT_EQ(expected, id_returned);

        EXPECT_EQ(Host::IDENT_FLEX, type_returned);
    }

    /// @brief Tests pkt4_receive callout.
    ///
    /// @param expr Expression to be used (in textual form).
    /// @param use_for_leases Indicates if flexible identifier should be used for
    /// identification of clients within lease database.
    /// @param exp_client_id Expected client identifier in the query
    /// created from flex-id.
    /// @param exp_old_client_id Expected client identifier to be stored in
    /// the context. This is original client identifier inserted by the client.
    /// @param preloaded_flex_id Flexible identifier stored in the context (simulating
    /// a case when flexible identifier is computed in other callout).
    void pkt4_receiveCall(const std::string& expr,
                          const FlexIdForLeases& use_for_leases,
                          const std::vector<uint8_t>& exp_client_id,
                          const std::vector<uint8_t>& exp_old_client_id = std::vector<uint8_t>(),
                          const std::vector<uint8_t>& preloaded_flex_id = std::vector<uint8_t>()) {

        isc::flex_id::storeConfiguration(false, expr, use_for_leases.value_, false);

        CalloutHandle handle(getCalloutManager());

        // If flex-id is specified, store its value in a query.
        if (!preloaded_flex_id.empty()) {
            handle.setContext("id_value", preloaded_flex_id);
        }

        // Set query.
        handle.setArgument("query4", pkt4_);

        // Execute pkt4_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt4_receive(handle));
        EXPECT_EQ(0, ret);

        OptionPtr client_id = pkt4_->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

        // The client identifier may not be present if flex-id can't be computed
        // for the given packet and the client didn't supply client identifier.
        if (exp_client_id.empty()) {
            EXPECT_FALSE(client_id);

        } else {
            ASSERT_TRUE(client_id);
            const OptionBuffer& client_id_buf = client_id->getData();
            EXPECT_EQ(exp_client_id, client_id_buf);
        }

        OptionPtr old_client_id;
        if (exp_old_client_id.empty()) {
            EXPECT_THROW(handle.getContext("client_identifier", old_client_id),
                         NoSuchCalloutContext);

        } else {
            ASSERT_NO_THROW(handle.getContext("client_identifier", old_client_id));
            ASSERT_TRUE(old_client_id);
            const OptionBuffer& expected_old_cid_buf = old_client_id->getData();
            EXPECT_EQ(exp_old_client_id, expected_old_cid_buf);
        }
    }

    /// @brief Tests pkt4_send callout.
    ///
    /// @param original_client_id Client identifier to be stored in the context.
    /// @param flex_id Client identifier constructed from flex-id and stored in the
    /// response before pkt4_send hook point.
    /// @param expected_client_id Expected value of the client identifier after
    /// pkt4_send call.
    void pkt4_sendCall(const std::vector<uint8_t>& original_client_id,
                       const std::vector<uint8_t>& flex_id,
                       const std::vector<uint8_t>& expected_client_id) {
        CalloutHandle handle(getCalloutManager());

        if (!original_client_id.empty()) {
            // Store client supplied client identifier in the context like pkt4_receive
            // would do.
            OptionPtr opt_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                               original_client_id));
            handle.setContext("client_identifier", opt_client_id);

            // If there is no flex-id, add original client identifier to a response.
            if (flex_id.empty()) {
                response4_->addOption(opt_client_id);
            }
        }

        if (!flex_id.empty()) {
            // Use flex-id as a new client identifier if specified.
            OptionPtr opt_flex_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, flex_id));
            response4_->addOption(opt_flex_id);
            handle.setContext("id_value", flex_id);
        }

        handle.setArgument("query4", pkt4_);
        handle.setArgument("response4", response4_);

        // Execute the callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt4_send(handle));

        EXPECT_EQ(0, ret);

        // Try to get the client identifier option from the response.
        OptionPtr opt_client_id = response4_->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

        // If expected client identifier is empty, we expect no client identifier option
        // to be present.
        if (expected_client_id.empty()) {
            EXPECT_FALSE(opt_client_id);

        } else {
            ASSERT_TRUE(opt_client_id);
            const OptionBuffer& client_id_buf = opt_client_id->getData();
            EXPECT_EQ(expected_client_id, client_id_buf);
        }
    }

    /// @brief Tests host6_identifier callout
    ///
    /// @param expr expression to be used (in textual form)
    /// @param expected expected value of the identifier
    void host6_identifierCall(const std::string& expr,
                              const std::vector<uint8_t>& expected) {

        isc::flex_id::storeConfiguration(true, expr, true, false);

        // Make a callout handle
        CalloutHandle handle(getCalloutManager());
        Host::IdentifierType type = Host::IDENT_FLEX;
        std::vector<uint8_t> id;

        handle.setArgument("query6", pkt6_);
        handle.setArgument("id_type", type);
        handle.setArgument("id_value", id);

        // The callout should succeed.
        int ret;
        ASSERT_NO_THROW(ret = host6_identifier(handle));
        EXPECT_EQ(0, ret);

        Host::IdentifierType type_returned;
        std::vector<uint8_t> id_returned;
        handle.getArgument("id_type", type_returned);
        handle.getArgument("id_value", id_returned);

        ASSERT_EQ(expected.size(), id_returned.size());
        EXPECT_EQ(expected, id_returned);

        EXPECT_EQ(Host::IDENT_FLEX, type_returned);
    }

    /// @brief Tests pkt6_receive callout.
    ///
    /// @param expr Expression to be used (in textual form).
    /// @param use_for_leases Indicates if flexible identifier should be used for
    /// identification of clients within lease database.
    /// @param expected_duid Expected DUID in the query, created from flex-id.
    /// @param expected_old_duid Expected DUID to be stored in the context.
    /// This is original DUID inserted by the client.
    /// @param preloaded_flex_id Flexible identifier stored in the context (simulating
    /// a case when flexible identifier is computed in other callout).
    void pkt6_receiveCall(const std::string& expr,
                          const FlexIdForLeases& use_for_leases,
                          const std::vector<uint8_t>& expected_duid,
                          const std::vector<uint8_t>& expected_old_duid = std::vector<uint8_t>(),
                          const std::vector<uint8_t>& preloaded_flex_id = std::vector<uint8_t>()) {

        isc::flex_id::storeConfiguration(true, expr, use_for_leases.value_, false);

        CalloutHandle handle(getCalloutManager());

        // If flex-id is specified, store its value in a query.
        if (!preloaded_flex_id.empty()) {
            handle.setContext("id_value", preloaded_flex_id);
        }

        // Set query.
        handle.setArgument("query6", pkt6_);

        // Execute pkt6_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt6_receive(handle));
        EXPECT_EQ(0, ret);

        OptionPtr duid = pkt6_->getOption(D6O_CLIENTID);

        // The DUID may not be present if flex-id can't be computed for the given
        // packet and the client didn't supply DUID.
        if (expected_duid.empty()) {
            EXPECT_FALSE(duid);

        } else {
            ASSERT_TRUE(duid);
            const OptionBuffer& duid_buf = duid->getData();
            EXPECT_EQ(expected_duid, duid_buf);
        }

        OptionPtr old_duid;
        if (expected_old_duid.empty()) {
            EXPECT_THROW(handle.getContext("duid", old_duid),
                         NoSuchCalloutContext);

        } else {
            ASSERT_NO_THROW(handle.getContext("duid", old_duid));
            ASSERT_TRUE(old_duid);
            const OptionBuffer& expected_old_duid_buf = old_duid->getData();
            EXPECT_EQ(expected_old_duid, expected_old_duid_buf);
        }
    }

    /// @brief Tests pkt6_send callout.
    ///
    /// @param original_duid DUID to be stored in the context.
    /// @param flex_id DUID constructed from flex-id and stored in the response
    /// before pkt6_send hook point.
    /// @param expected_duid Expected value of the DUID after pkt6_send call.
    void pkt6_sendCall(const std::vector<uint8_t>& original_duid,
                       const std::vector<uint8_t>& flex_id,
                       const std::vector<uint8_t>& expected_duid) {
        CalloutHandle handle(getCalloutManager());

        if (!original_duid.empty()) {
            // Store client supplied client identifier in the context like pkt4_receive
            // would do.
            OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, original_duid));
            handle.setContext("duid", opt_duid);

            // If there is no flex-id, add original DUID to a response.
            if (flex_id.empty()) {
                response6_->addOption(opt_duid);
            }
        }

        if (!flex_id.empty()) {
            // Use flex-id as a new DUID if specified.
            OptionPtr opt_flex_id(new Option(Option::V6, D6O_CLIENTID, flex_id));
            response6_->addOption(opt_flex_id);
            handle.setContext("id_value", flex_id);
        }

        handle.setArgument("query6", pkt6_);
        handle.setArgument("response6", response6_);

        // Execute the callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt6_send(handle));
        EXPECT_EQ(0, ret);

        // Try to get the DUID option from the response.
        OptionPtr opt_duid = response6_->getOption(D6O_CLIENTID);

        // If expected DUID is empty, we expect no DUID option to be present.
        if (expected_duid.empty()) {
            EXPECT_FALSE(opt_duid);

        } else {
            ASSERT_TRUE(opt_duid);
            const OptionBuffer& duid_buf = opt_duid->getData();
            EXPECT_EQ(expected_duid, duid_buf);
        }
    }

    /// @brief Test if ignoring the IAID works properly.
    ///
    /// If the flag is disabled, the packet is not modified, and no parameters
    /// are stored in the hook context.
    /// It the flag is enabled and there are more than either one IANA or one
    /// IAPD, the DROP flag is set on pkt6_receive.
    /// If the flag is enabled and there are at most one IANA and one IAPD, the
    /// IAIDs are set to 0 and the initial values are stored in the hook context
    /// as 'iana_iaid' and 'iapd_iaid' on pk6_receive. On pkt6_send the initial
    /// IAIDs are restored.
    ///
    /// @param ignore_iaid The flag which enables ignore IAID functionality.
    /// @param iana_count The number of IANAs in the packet.
    /// @param iapd_count The number of IAPDs in the packet.
    void ignoreIAIDTest(bool ignore_iaid, uint32_t iana_count, uint32_t iapd_count) {
        isc::flex_id::storeConfiguration(true, "", false, ignore_iaid);

        ASSERT_TRUE(iana_count + iapd_count < 15);

        CalloutHandle handle(getCalloutManager());

        // Set query.
        handle.setArgument("query6", pkt6_);

        // iana_count addresses will be added
        // iapd_count prefixes will be added

        // start from 1 to iana_count
        uint32_t expected_iana_iaid = 0;
        for (uint32_t idx = 0; idx < iana_count; idx++) {
            expected_iana_iaid++;
            Option6IAPtr ia(new Option6IA(D6O_IA_NA, expected_iana_iaid));
            // Generate 2003:db8::1 address.
            // If N addresses are generated then 2003:db8::2, 2003:db8::3, ...
            // 2003:db8::N will be added.
            Option6IAAddrPtr addr(new Option6IAAddr(D6O_IAADDR,
                                                    IOAddress(string("2003:db8::") + to_string(expected_iana_iaid)),
                                                    100, 100));
            ia->addOption(addr);
            pkt6_->addOption(ia);
        }

        // start from iana_count + 1 to iana_count + iapd_count
        uint32_t expected_iapd_iaid = expected_iana_iaid;
        for (uint32_t idx = 0; idx < iapd_count; idx++) {
            expected_iapd_iaid++;
            Option6IAPtr ia(new Option6IA(D6O_IA_PD, expected_iapd_iaid));
            // If no address has been generated, generate 2003:db8:1:: prefix.
            // If 2003:db8::1 address has been generated, generate 2003:db8:2::
            // prefix.
            // If N addresses are generated and M prefixes are generated then
            // 2003:db8:(N + 1)::, 2003:db8:(N + 2)::, ... 2003:db8:(N + M)::
            // will be added.
            Option6IAPrefixPtr addr(new Option6IAPrefix(D6O_IAPREFIX,
                                                        IOAddress(string("2003:db8:") + to_string(expected_iapd_iaid) + "::"),
                                                        64, 100, 100));
            ia->addOption(addr);
            pkt6_->addOption(ia);
        }

        // Execute pkt6_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt6_receive(handle));
        EXPECT_EQ(0, ret);

        uint32_t iana_iaid = 0;
        uint32_t iapd_iaid = expected_iana_iaid;
        ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        if (ignore_iaid) {
            uint32_t context_iana_count;
            uint32_t context_iapd_count;
            ASSERT_NO_THROW(handle.getContext("iana_count", context_iana_count));
            ASSERT_NO_THROW(handle.getContext("iapd_count", context_iapd_count));
            ASSERT_EQ(iana_count, context_iana_count);
            ASSERT_EQ(iapd_count, context_iapd_count);
            if (iana_count == 1) {
                ASSERT_NO_THROW(handle.getContext("iana_iaid", iana_iaid));
                ASSERT_TRUE(expected_iana_iaid > 0);
                ASSERT_EQ(iana_iaid, expected_iana_iaid);
            } else {
                ASSERT_THROW(handle.getContext("iana_iaid", iana_iaid), NoSuchCalloutContext);
            }
            if (iapd_count == 1) {
                ASSERT_NO_THROW(handle.getContext("iapd_iaid", iapd_iaid));
                ASSERT_TRUE(expected_iapd_iaid > expected_iana_iaid);
                ASSERT_EQ(iapd_iaid, expected_iapd_iaid);
            } else {
                ASSERT_THROW(handle.getContext("iapd_iaid", iapd_iaid), NoSuchCalloutContext);
            }
            iapd_count = iana_count;
            iana_count = 0;
            for (auto const& opt : pkt6_->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_NA: {
                        iana_count++;
                        auto iana = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        if (context_iana_count == 1) {
                            ASSERT_EQ(iana->getIAID(), 0);
                        } else {
                            ASSERT_EQ(iana->getIAID(), iana_count);
                        }
                        break;
                    }
                }
            }
            for (auto const& opt : pkt6_->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_PD: {
                        iapd_count++;
                        auto iapd = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        if (context_iapd_count == 1) {
                            ASSERT_EQ(iapd->getIAID(), 0);
                        } else {
                            ASSERT_EQ(iapd->getIAID(), iapd_count);
                        }
                        break;
                    }
                }
            }
        } else {
            ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
            uint32_t context_iana_count;
            uint32_t context_iapd_count;
            ASSERT_THROW(handle.getContext("iana_count", context_iana_count), NoSuchCalloutContext);
            ASSERT_THROW(handle.getContext("iapd_count", context_iapd_count), NoSuchCalloutContext);
            ASSERT_THROW(handle.getContext("iana_iaid", iana_iaid), NoSuchCalloutContext);
            ASSERT_THROW(handle.getContext("iapd_iaid", iapd_iaid), NoSuchCalloutContext);
            iapd_count = iana_count;
            iana_count = 0;
            for (auto const& opt : pkt6_->options_) {
                switch (opt.second->getType()) {
                    case D6O_IA_NA: {
                        iana_count++;
                        auto iana = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        ASSERT_EQ(iana->getIAID(), iana_count);
                        break;
                    }
                    case D6O_IA_PD: {
                        iapd_count++;
                        auto iapd = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                        ASSERT_EQ(iapd->getIAID(), iapd_count);
                        break;
                    }
                }
            }
        }

        handle.setArgument("query6", pkt6_);
        handle.setArgument("response6", pkt6_);

        // Execute the callout.
        ASSERT_NO_THROW(ret = pkt6_send(handle));
        EXPECT_EQ(0, ret);

        ASSERT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);
        iapd_count = iana_count;
        iana_count = 0;
        for (auto const& opt : pkt6_->options_) {
            switch (opt.second->getType()) {
                case D6O_IA_NA: {
                    iana_count++;
                    auto iana = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                    ASSERT_EQ(iana->getIAID(), iana_count);
                    break;
                }
                case D6O_IA_PD: {
                    iapd_count++;
                    auto iapd = boost::dynamic_pointer_cast<Option6IA>(opt.second);
                    ASSERT_EQ(iapd->getIAID(), iapd_count);
                    break;
                }
            }
        }
    }

    /// Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;

    Pkt4Ptr pkt4_; ///< A stub DHCPv4 packet
    Pkt6Ptr pkt6_; ///< A stub DHCPv6 packet

    Pkt4Ptr response4_; ///< A stub DHCPv4 response.
    Pkt6Ptr response6_; ///< A stub DHCPv6 response.

    OptionPtr option_str4_; ///< A string option for DHCPv4
    OptionPtr option_str6_; ///< A string option for DHCPv6

};

// Verifies that the host4_identifier callout does generate identifier when
// the expression is specified (test case: use message type)
TEST_F(CalloutTest, host4_identifierMsgType) {

    string expr = "pkt4.msgtype";

    vector<uint8_t> expected(4);
    expected[3] = 1; // msgtype represented as 0x00000001

    host4_identifierCall(expr, expected);
}

// Verifies that the host4_identifier callout does generate identifier when
// the expression is specified (test case: use option content)
TEST_F(CalloutTest, host4_identifierOptionValue) {

    string expr = "option[100].hex";

    const string exp("hundred4");
    vector<uint8_t> expected(exp.size());
    std::memcpy(&expected[0], &exp[0], exp.size());

    host4_identifierCall(expr, expected);
}

// Verifies that the host4_identifier does not generate identifier when
// the expression is specified, but option defined in it is missing.
TEST_F(CalloutTest, host4_identifierEmpty) {

    // We want content of option 123, but there's no such option present.
    string expr = "option[123].hex";
    vector<uint8_t> empty;

    host4_identifierCall(expr, empty);
}

// Verifies that pkt4_receive callout uses flexible identifier to create
// client identifier option.
TEST_F(CalloutTest, pkt4_receiveNoClientId1) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_cid = { 0, 'h', 'u', 'n', 'd', 'r', 'e', 'd', '4' };
    pkt4_receiveCall(expr, FlexIdForLeases(true), expected_cid);
}

// Verifies that pkt4_receive callout does not use flexible identifier as
// client identifier if disabled in the configuration.
TEST_F(CalloutTest, pkt4_receiveNoClientId2) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_cid;
    pkt4_receiveCall(expr, FlexIdForLeases(false), expected_cid);
}

// Verifies that old client identifier is stored in the callouts context
// when new client identifier is generated from flex-id.
TEST_F(CalloutTest, pkt4_receiveExistingClientId1) {
    string expr = "option[100].hex";

    OptionBuffer buf(7, 1);
    OptionPtr opt_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, buf));
    pkt4_->addOption(opt_client_id);

    std::vector<uint8_t> expected_cid = { 0, 'h', 'u', 'n', 'd', 'r', 'e', 'd', '4' };
    std::vector<uint8_t> expected_old_cid = { 1, 1, 1, 1, 1, 1, 1 };
    pkt4_receiveCall(expr, FlexIdForLeases(true), expected_cid, expected_old_cid);
}

// Verifies that client identifier is not replaced in the client's query when
// disabled in the configuration.
TEST_F(CalloutTest, pkt4_receiveExistingClientId2) {
    string expr = "option[100].hex";

    OptionBuffer buf(7, 1);
    OptionPtr opt_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, buf));
    pkt4_->addOption(opt_client_id);

    std::vector<uint8_t> expected_cid = { 1, 1, 1, 1, 1, 1, 1 };
    std::vector<uint8_t> expected_old_cid;
    pkt4_receiveCall(expr, FlexIdForLeases(false), expected_cid, expected_old_cid);
}

// Verifies that flex-id generated by other callouts is propagated to the
// pkt4_receive callout.
TEST_F(CalloutTest, pkt4_receiveExistingFlexId1) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_cid = { 0, 1, 2, 3, 4 };
    std::vector<uint8_t> expected_old_cid;
    std::vector<uint8_t> preloaded_flex_id = { 1, 2, 3, 4 };
    pkt4_receiveCall(expr, FlexIdForLeases(true), expected_cid, expected_old_cid,
                     preloaded_flex_id);
}

// Verifies that client identifier derived from flex-id is not inserted into
// the client's query when disabled by the configuration.
TEST_F(CalloutTest, pkt4_receiveExistingFlexId2) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_cid;
    std::vector<uint8_t> expected_old_cid;
    std::vector<uint8_t> preloaded_flex_id = { 1, 2, 3, 4 };
    pkt4_receiveCall(expr, FlexIdForLeases(false), expected_cid, expected_old_cid,
                     preloaded_flex_id);
}

// This test verifies that client identifier is not replaced when the flex-id
// can't be computed.
TEST_F(CalloutTest, pkt4_receiveNonMatchingExpression) {
    string expr = "option[123].hex";

    OptionBuffer buf(7, 1);
    OptionPtr opt_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, buf));
    pkt4_->addOption(opt_client_id);

    std::vector<uint8_t> expected_cid = { 1, 1, 1, 1, 1, 1, 1 };
    std::vector<uint8_t> expected_old_cid;
    pkt4_receiveCall(expr, FlexIdForLeases(true), expected_cid, expected_old_cid);
}

// Verifies that client identifier created from flex-id is removed in pkt4_send
// callout.
TEST_F(CalloutTest, pkt4_sendNoClientId) {
    std::vector<uint8_t> original_client_id;
    std::vector<uint8_t> flex_id = { 0, 1, 2, 3, 4 };
    std::vector<uint8_t> expected_client_id;

    pkt4_sendCall(original_client_id, flex_id, expected_client_id);
}

// Verifies that original client identifier is preserved if there is no
// flex-id used as client identifier.
TEST_F(CalloutTest, pkt4_sendNoFlexId) {
    std::vector<uint8_t> original_client_id = { 1, 1, 2, 3, 4, 5, 6 };
    std::vector<uint8_t> flex_id;
    std::vector<uint8_t> expected_client_id = original_client_id;

    pkt4_sendCall(original_client_id, flex_id, expected_client_id);
}

// Verifies that response contains no client identifier if there is neither
// client identifier nor flex-id.
TEST_F(CalloutTest, pkt4_sendNoClientIdNoFlexId) {
    std::vector<uint8_t> original_client_id;
    std::vector<uint8_t> flex_id;
    std::vector<uint8_t> expected_client_id;

    pkt4_sendCall(original_client_id, flex_id, expected_client_id);
}

// Verifies that client id is preserved if flex-id can't be generated due to
// an error.
TEST_F(CalloutTest, pkt4_sendClientIdNoFlexId) {
    // Add client identifier option into the response.
    OptionBuffer buf = { 1, 1, 2, 3, 4, 5, 6 };
    OptionPtr client_id_response(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, buf));
    response4_->addOption(client_id_response);

    // The original client id and the flex id are empty which simulates the
    // case when the pkt4_receive callout was unable to generate flex-id due to
    // an error (exception). In this case, the original client identifier is not
    // saved in the context and the flex-id is also undefined. The expected
    // client id is equal to the client identifier we have added to the response
    // because this option must not be removed if pkt4_receive is unsuccessful.
    // The pkt4_receive must be able to determine that.
    std::vector<uint8_t> original_client_id;
    std::vector<uint8_t> flex_id;
    std::vector<uint8_t> expected_client_id = { 1, 1, 2, 3, 4, 5, 6 };

    pkt4_sendCall(original_client_id, flex_id, expected_client_id);
}

// Verifies that original client identifier is inserted into response in the
// pkt4_receive callout.
TEST_F(CalloutTest, pkt4_sendExistingClientId) {
    std::vector<uint8_t> original_client_id = { 1, 1, 2, 3, 4, 5, 6 };
    std::vector<uint8_t> flex_id = { 0, 1, 2, 3, 4 };
    std::vector<uint8_t> expected_client_id = original_client_id;

    pkt4_sendCall(original_client_id, flex_id, expected_client_id);
}

// Verifies that the host6_identifier callout does generate identifier when
// the expression is specified (test case: use message type)
TEST_F(CalloutTest, host6_identifierMsgType) {

    string expr = "pkt6.msgtype";

    vector<uint8_t> expected(4);
    expected[3] = 1; // msgtype represented as 0x00000001

    host6_identifierCall(expr, expected);
}

// Verifies that the host6_identifier callout does generate identifier when
// the expression is specified (test case: use option content)
TEST_F(CalloutTest, host6_identifierOptionValue) {

    string expr = "option[100].hex";

    const string exp("hundred6");
    vector<uint8_t> expected(exp.size());
    std::memcpy(&expected[0], &exp[0], exp.size());

    host6_identifierCall(expr, expected);
}

// Verifies that the host6_identifier does not generate identifier when
// the expression is specified, but option defined in it is missing.
TEST_F(CalloutTest, host6_identifierEmpty) {

    // We want content of option 123, but there's no such option present.
    string expr = "option[123].hex";
    vector<uint8_t> empty;

    host6_identifierCall(expr, empty);
}

// Verifies that pkt6_receive callout uses flexible identifier to create
// client identifier option.
TEST_F(CalloutTest, pkt6_receiveNoDUID1) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_duid = { 0, 0, 'h', 'u', 'n', 'd', 'r', 'e', 'd', '6' };
    pkt6_receiveCall(expr, FlexIdForLeases(true), expected_duid);
}

// Verifies that pkt6_receive callout does not use flexible identifier as
// client identifier if disabled in the configuration.
TEST_F(CalloutTest, pkt6_receiveNoDUID2) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_duid;
    pkt6_receiveCall(expr, FlexIdForLeases(false), expected_duid);
}

// Verifies that old DUID is stored in the callouts context when new DUID is
// generated from flex-id.
TEST_F(CalloutTest, pkt6_receiveExistingDUID1) {
    string expr = "option[100].hex";

    OptionBuffer buf = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, buf));
    pkt6_->addOption(opt_duid);

    std::vector<uint8_t> expected_duid = { 0, 0, 'h', 'u', 'n', 'd', 'r', 'e', 'd', '6' };
    std::vector<uint8_t> expected_old_duid = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    pkt6_receiveCall(expr, FlexIdForLeases(true), expected_duid, expected_old_duid);
}

// Verifies that DUID is not replaced in the client's query when disabled in
// the configuration.
TEST_F(CalloutTest, pkt6_receiveExistingDUID2) {
    string expr = "option[100].hex";

    OptionBuffer buf = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, buf));
    pkt6_->addOption(opt_duid);

    std::vector<uint8_t> expected_duid = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    std::vector<uint8_t> expected_old_duid;
    pkt6_receiveCall(expr, FlexIdForLeases(false), expected_duid, expected_old_duid);
}

// Verifies that flex-id generates by other callouts is propagated to the
// pkt6_receive callout.
TEST_F(CalloutTest, pkt6_receiveExistingFlexId1) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_duid = { 0, 0, 1, 2, 3, 4 };
    std::vector<uint8_t> expected_old_duid;
    std::vector<uint8_t> preloaded_flex_id = { 1, 2, 3, 4 };
    pkt6_receiveCall(expr, FlexIdForLeases(true), expected_duid, expected_old_duid,
                     preloaded_flex_id);
}

// Verifies that DUID derived from flex-id is not inserted into the client's query
// when disabled by the configuration.
TEST_F(CalloutTest, pkt6_receiveExistingFlexId2) {
    string expr = "option[100].hex";

    std::vector<uint8_t> expected_duid;
    std::vector<uint8_t> expected_old_duid;
    std::vector<uint8_t> preloaded_flex_id = { 1, 2, 3, 4 };
    pkt6_receiveCall(expr, FlexIdForLeases(false), expected_duid, expected_old_duid,
                     preloaded_flex_id);
}

// This test verifies that DUID is not replaced when the flex-id can't be computed.
TEST_F(CalloutTest, pkt6_receiveNonMatchingExpression) {
    string expr = "option[123].hex";

    OptionBuffer buf = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, buf));
    pkt6_->addOption(opt_duid);

    std::vector<uint8_t> expected_duid = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    std::vector<uint8_t> expected_old_duid;
    pkt6_receiveCall(expr, FlexIdForLeases(true), expected_duid, expected_old_duid);
}

// Verifies that DUID created from flex-id is removed in pkt6_send callout.
TEST_F(CalloutTest, pkt6_sendNoDUID) {
    std::vector<uint8_t> original_duid;
    std::vector<uint8_t> flex_id = { 0, 0, 1, 2, 3, 4 };
    std::vector<uint8_t> expected_duid;

    pkt6_sendCall(original_duid, flex_id, expected_duid);
}

// Verifies that original DUID is preserved if there is no flex-id
// used as DUID.
TEST_F(CalloutTest, pkt6_sendNoFlexId) {
    std::vector<uint8_t> original_duid = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    std::vector<uint8_t> flex_id;
    std::vector<uint8_t> expected_duid = original_duid;

    pkt6_sendCall(original_duid, flex_id, expected_duid);
}

// Verifies that response contains no DUID if there is neither DUID nor flex-id.
TEST_F(CalloutTest, pkt6_sendNoDUIDNoFlexId) {
    std::vector<uint8_t> original_duid;
    std::vector<uint8_t> flex_id;
    std::vector<uint8_t> expected_duid;

    pkt6_sendCall(original_duid, flex_id, expected_duid);
}

// Verifies that original DUID is inserted into response in the pkt6_receive
// callout.
TEST_F(CalloutTest, pkt6_sendExistingDUID) {
    std::vector<uint8_t> original_duid = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    std::vector<uint8_t> flex_id = { 0, 0, 1, 2, 3, 4 };
    std::vector<uint8_t> expected_duid = original_duid;

    pkt6_sendCall(original_duid, flex_id, expected_duid);
}

// Verifies that client id is preserved if flex-id can't be generated due to
// an error.
TEST_F(CalloutTest, pkt6_sendDUIDNoFlexId) {
    // Add DUID option into the response.
    OptionBuffer buf = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };
    OptionPtr duid_response(new Option(Option::V6, D6O_CLIENTID, buf));
    response6_->addOption(duid_response);

    // The original DUID and the flex id are empty which simulates the
    // case when the pkt6_receive callout was unable to generate flex-id due to
    // an error (exception). In this case, the original DUID is not saved in the
    // context and the flex-id is also undefined. The expected DUID is equal to
    // the DUID we have added to the response because this option must not be
    // removed if pkt6_receive is unsuccessful. The pkt6_receive must be able to
    // determine that.
    std::vector<uint8_t> original_duid;
    std::vector<uint8_t> flex_id;
    std::vector<uint8_t> expected_duid = { 0, 3, 0, 1, 1, 2, 3, 4, 5, 6 };

    pkt6_sendCall(original_duid, flex_id, expected_duid);
}

// Verifies that disabled ignore-iaid flag does not change packet.
TEST_F(CalloutTest, ignoreIAIDTestNotEnabled) {
    ignoreIAIDTest(false, 2, 2);
}

// Verifies that enabled ignore-iaid with more than one IANA and one IAPD drops
// the packet.
TEST_F(CalloutTest, ignoreIAIDTestTooManyIANATooManyIAPD) {
    ignoreIAIDTest(true, 2, 2);
}

// Verifies that enabled ignore-iaid with more than one IANA drops the packet.
TEST_F(CalloutTest, ignoreIAIDTestTooManyIANA) {
    ignoreIAIDTest(true, 2, 0);
}

// Verifies that enabled ignore-iaid with more than one IAPD drops the packet.
TEST_F(CalloutTest, ignoreIAIDTestTooManyIAPD) {
    ignoreIAIDTest(true, 0, 2);
}

// Verifies that enabled ignore-iaid with one IANA works as expected.
TEST_F(CalloutTest, ignoreIAIDTestOneIANA) {
    ignoreIAIDTest(true, 1, 0);
}

// Verifies that enabled ignore-iaid with one IAPD works as expected.
TEST_F(CalloutTest, ignoreIAIDTestOneIAPD) {
    ignoreIAIDTest(true, 0, 1);
}

// Verifies that enabled ignore-iaid with one IANA and one IAPD works as expected.
TEST_F(CalloutTest, ignoreIAIDTestOneIANAAndOneIAPD) {
    ignoreIAIDTest(true, 1, 1);
}

// Verifies that enabled ignore-iaid with one IANA and multiple IAPDs works as expected.
TEST_F(CalloutTest, ignoreIAIDTestOneIANATooManyIAPD) {
    ignoreIAIDTest(true, 1, 2);
}

// Verifies that enabled ignore-iaid with multiple IANAs and one IAPD works as expected.
TEST_F(CalloutTest, ignoreIAIDTestTooMankeIANAOneIAPD) {
    ignoreIAIDTest(true, 2, 1);
}

} // end of anonymous namespace
