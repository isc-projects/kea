// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests DHCPv6 Bulk Lease Queries.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option_int.h>
#include <dhcp/option_custom.h>
#include <dhcp/pkt4.h>
#include <bulk_lease_query4.h>
#include <lease_query_impl4.h>

#include <gtest/gtest.h>
#include <sstream>
#include <queue>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::lease_query;

namespace isc {
namespace lease_query {
namespace test {

/// @brief Test fixture class for tests which need to manipulate
/// bulk lease query packets.
class BlqPacketTest4 : public ::testing::Test {
public:
    /// @brief Destructor.
    virtual ~BlqPacketTest4() {};

    /// @brief Creates a DHCPBULKLEASEQUERY packet.
    ///
    /// @return DHCPBULKLEASEQUERY packet.
    Pkt4Ptr makeLeaseQuery() const {
        Pkt4Ptr query(new Pkt4(DHCPBULKLEASEQUERY, 123));
        query->setHWAddr(HWAddrPtr(new HWAddr(std::vector<uint8_t>{}, 0)));
        return (query);
    }

    /// @brief Convenience method for making a client identifier option instance.
    ///
    /// @param cid client id.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeClientIdOption(const ClientIdPtr& cid) const {
        OptionPtr opt(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                 cid->getClientId()));
        return (opt);
    }

    /// @brief Convenience method for making an identifier option instance.
    ///
    /// @param opt_type option type (DHO_...).
    /// @param data binary data a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeBinaryOption(const uint8_t& opt_type,
                               const vector<uint8_t>& data) const {
        OptionPtr opt(new Option(Option::V4, opt_type, data));
        return (opt);
    }

    /// @brief Convenience method for making a relay identifier option instance.
    ///
    /// @param data relay id as a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeRelayIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(RAI_OPTION_RELAY_ID, data));
    }

    /// @brief Convenience method for making a remote identifier option instance.
    ///
    /// @param data remote id as a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeRemoteIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(RAI_OPTION_REMOTE_ID, data));
    }

    /// @brief Creates a DHCPBULKLEASEQUERY packet for query by client id.
    ///
    /// @param cid client id for which to query.
    ///
    /// @return DHCPBULKLEASEQUERY packet.
    Pkt4Ptr makeQueryByClientId(const ClientIdPtr& cid) const {
        Pkt4Ptr query = makeLeaseQuery();
        OptionPtr opt = makeClientIdOption(cid);
        query->addOption(opt);
        return (query);
    }

    /// @brief Creates a DHCPBULKLEASEQUERY packet for query by hardware address.
    ///
    /// @param hwaddr hardware address for which to query.
    ///
    /// @return DHCPBULKLEASEQUERY packet.
    Pkt4Ptr makeQueryByHWAddr(const HWAddrPtr& hwaddr) const {
        Pkt4Ptr query = makeLeaseQuery();
        query->setHWAddr(hwaddr);
        return (query);
    }

    /// @brief Creates a DHCPBULKLEASEQUERY packet for query by relay id.
    ///
    /// @param data relay id as a vector of bytes.
    ///
    /// @return DHCPBULKLEASEQUERY packet.
    Pkt4Ptr makeQueryByRelayId(const vector<uint8_t>& data) const {
        Pkt4Ptr query = makeLeaseQuery();
        OptionPtr rai(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS));
        OptionPtr opt = makeRelayIdOption(data);
        rai->addOption(opt);
        query->addOption(rai);
        return (query);
    }

    /// @brief Creates a DHCPBULKLEASEQUERY packet for query by remote id.
    ///
    /// @param data remote id as a vector of bytes.
    ///
    /// @return DHCPBULKLEASEQUERY packet.
    Pkt4Ptr makeQueryByRemoteId(const vector<uint8_t>& data) const {
        Pkt4Ptr query = makeLeaseQuery();
        OptionPtr rai(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS));
        OptionPtr opt = makeRemoteIdOption(data);
        rai->addOption(opt);
        query->addOption(rai);
        return (query);
    }

    /// @brief Verifies that a response contains the expected value for
    /// an option containing a time sensitive value.  The value is
    /// is correct if it lies within a range.
    ///
    /// @param response response to test
    /// @param code option code of the expected option
    /// @param exp_value  value the option should have
    /// @param tol tolerance in seconds. Defaults to 2.  Actual values
    /// are correct if they fall within +/- tolerance of expected value.
    void verifyTimeOption(const Pkt4Ptr& response, uint16_t code,
                          uint32_t exp_value, uint32_t tol = 2) const {
        OptionUint32Ptr uint32_opt;
        uint32_opt = boost::dynamic_pointer_cast<OptionUint32>(response->getOption(code));
        ASSERT_TRUE(uint32_opt)
                    << "option: " << code << " missing or it has an unexpected type";

        uint32_t lower = ((exp_value > tol) ? (exp_value - tol) : 0);
        uint32_t upper = ((exp_value < (UINT32_MAX - 2)) ? (exp_value + tol) : UINT32_MAX);
        uint32_t actual = uint32_opt->getValue();
        EXPECT_TRUE((lower <= actual ) && (actual <= upper))
                    << "option: " << code << " value is wrong:"
                    << " lower: " << lower << " <= "
                    << " actual: " << actual << " <= "
                    << " upper: " << upper;
    }

    /// @brief Verify relay-agent-info is correct.
    ///
    /// @param response response to test
    /// @param exp_hex_string expected option data as a hex string "0x...".
    /// If empty the option should not be present.
    void verifyRelayAgentInfo(const Pkt4Ptr& response,
                              const std::string& exp_hex_string) const {
        // Look for relay agent information option (option 82)
        OptionPtr rai = response->getOption(DHO_DHCP_AGENT_OPTIONS);

        if (exp_hex_string.empty()) {
            // Option should not be present.
            ASSERT_FALSE(rai) << "relay-agent-info should not be present";
            return;
        }

        // Verify it is present and content is as expected.
        ASSERT_TRUE(rai) << "relay-agent-info should be present";
        EXPECT_EQ(exp_hex_string, rai->toHexString());
    }

    /// @brief Validate that a Pkt4 contains the expected DHO_STATUS_CODE.
    ///
    /// @param response response packet.
    /// @param exp_status expected status code.
    /// @param exp_msg expected status text message.
    void checkStatus(const Pkt4Ptr& response,
                     const BLQStatusCode& exp_status,
                     const string& exp_msg = "") {
        OptionCustomPtr status_opt =
            boost::dynamic_pointer_cast<OptionCustom>
                (response->getOption(DHO_STATUS_CODE));
        ASSERT_TRUE(status_opt) << "DHO_STATUS_CODE missing";
        EXPECT_NO_THROW(checkStatus(status_opt, exp_status, exp_msg));
    }

    /// @brief Validate a DHO_STATUS_CODE option.
    ///
    /// @param status_opt status-code option to check.
    /// @param exp_status expected status code.
    /// @param exp_msg expected status text message.
    void checkStatus(const OptionCustomPtr& status_opt,
                     const BLQStatusCode& exp_status,
                     const string& exp_msg = "") {
        uint8_t status = status_opt->readInteger<uint8_t>(0);
        EXPECT_EQ(exp_status, status);
        string msg = status_opt->readString(1);
        EXPECT_EQ(exp_msg, msg);
    }

    /// @brief Checks the value of the dhcp-server-identifier option.
    ///
    /// @param pkt packet to check.
    /// @param expected_address IP address the packet's option should contain.
    void checkServerIdOption(const Pkt4Ptr& pkt,
                             const IOAddress& expected_address) {
        OptionPtr opt = pkt->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        ASSERT_TRUE(opt) << "no server-id option";
        OptionCustomPtr server_id =
            boost::dynamic_pointer_cast<OptionCustom>(opt);
        ASSERT_TRUE(server_id) << "bad server-id option";
        EXPECT_EQ(expected_address, server_id->readAddress(0));
    }
};

} // end of namespace isc::lease_query::test
} // end of namespace isc::lease_query
} // end of namespace isc
