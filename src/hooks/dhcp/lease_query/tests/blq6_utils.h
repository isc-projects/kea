// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests DHCPv6 Bulk Lease Queries.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_int.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/pkt6.h>
#include <lease_query_impl6.h>

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
class BlqPacketTest6 : public ::testing::Test {
public:
    /// @brief Destructor.
    virtual ~BlqPacketTest6() {};

    /// @brief Converts a packed RELAY_FORW message into a list of RelayInfos.
    ///
    /// This function was largely borrowed from Pkt6. The primary difference
    /// is not expected the innermost message to contain a D6O_RELAY_MSG.
    ///
    /// @param data buffer containing the packed RELAY_FORW message.
    /// @param[out] relay_infos list into which the RelayInfo instances
    /// should be stored.
    void unpackRelayForwardMsg(const vector<uint8_t>data,
                               vector<RelayInfoPtr>& relay_infos) {
        size_t bufsize = data.size();
        size_t offset = 0;

        while (bufsize >= Pkt6::DHCPV6_RELAY_HDR_LEN) {
            RelayInfoPtr relay(new Pkt6::RelayInfo);

            size_t relay_msg_offset = 0;
            size_t relay_msg_len = 0;

            // parse fixed header first (first 34 bytes)
            relay->msg_type_ = data[offset++];
            if (relay->msg_type_ != DHCPV6_RELAY_FORW) {
                isc_throw(Unexpected, "invalid message type: "
                          << relay->msg_type_);
            }

            relay->hop_count_ = data[offset++];
            relay->linkaddr_ = IOAddress::fromBytes(AF_INET6, &data[offset]);
            offset += isc::asiolink::V6ADDRESS_LEN;
            relay->peeraddr_ = IOAddress::fromBytes(AF_INET6, &data[offset]);
            offset += isc::asiolink::V6ADDRESS_LEN;
            bufsize -= Pkt6::DHCPV6_RELAY_HDR_LEN; // 34 bytes (1+1+16+16)

            // parse the rest as options
            OptionBuffer opt_buffer;
            if (bufsize != 0) {
                opt_buffer = OptionBuffer(&data[offset], &data[offset] + bufsize);
            }

            // If custom option parsing function has been set, use
            // this function to parse options. Otherwise, use standard
            // function from libdhcp.
            int last_offset = LibDHCP::unpackOptions6(opt_buffer,
                                                      DHCP6_OPTION_SPACE,
                                                      relay->options_,
                                                      &relay_msg_offset,
                                                      &relay_msg_len);

            // Store the parsed relay information.
            relay_infos.push_back(relay);

            // We're done if this relay has no relay message.
            if (relay_msg_offset == 0 || relay_msg_len == 0) {
                // Account for the options in this relay (if any).
                offset += last_offset;
                bufsize -= last_offset;
                break;
            }

            if (relay_msg_len >= bufsize) {
                // length of the relay_msg option extends beyond end of the message
                isc_throw(Unexpected, "Relay-msg option is truncated.");
            }

            uint8_t inner_type = data[offset + relay_msg_offset];
            offset += relay_msg_offset; // offset is relative
            bufsize = relay_msg_len;    // length is absolute

            if (inner_type != DHCPV6_RELAY_FORW) {
                isc_throw(Unexpected, "inner message is not a RELAY_FORW");
            }
        }

        if ( (offset != data.size()) || (bufsize != 0) ) {
            isc_throw(Unexpected, "message not parsed completely");
        }
    }

    /// @brief Convenience method for making a server identifier option instance.
    ///
    /// @param opt_type option type (D6O_...).
    /// @param data binary data a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeBinaryOption(const uint16_t& opt_type,
                               const vector<uint8_t>& data) const {
        OptionPtr opt(new Option(Option::V6, opt_type, data));
        return (opt);
    }

    /// @brief Convenience method for making a server identifier option instance.
    ///
    /// @param data server id as a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeServerIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_SERVERID, data));
    }

    /// @brief Convenience method for making a client identifier option instance.
    ///
    /// @param data client id as a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeClientIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_CLIENTID, data));
    }

    /// @brief Convenience method for making a relay identifier option instance.
    ///
    /// @param data relay id as a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeRelayIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_RELAY_ID, data));
    }

    /// @brief Convenience method for making a remote identifier option instance.
    ///
    /// @param data remote id as a vector of bytes.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeRemoteIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_REMOTE_ID, data));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by ip address.
    ///
    /// @param qry_iaaddr ip address for which to query.
    ///
    /// @return DHCPV6_LEASEQUERY packet.
    Pkt6Ptr makeQueryByIpAddress6(const IOAddress& qry_iaaddr) const {
        Option6IAAddrPtr opt(new Option6IAAddr(D6O_IAADDR, qry_iaaddr, 0, 0));
        return (makeLeaseQuery(LQ6QT_BY_ADDRESS, opt));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by client id.
    ///
    /// @param qry_cid client id for which to query.
    /// @param link_addr link address to filter by.
    ///
    /// @return DHCPV6_LEASEQUERY packet.
    Pkt6Ptr makeQueryByClientId(const DuidPtr& qry_cid,
                                const IOAddress& link_addr
                                = IOAddress::IPV6_ZERO_ADDRESS()) const {
        OptionPtr opt = makeClientIdOption(qry_cid->getDuid());
        return (makeLeaseQuery(LQ6QT_BY_CLIENTID, opt, link_addr));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by relay id.
    ///
    /// @param qry_cid relay id for which to query.
    /// @param link_addr link address to filter by.
    ///
    /// @return DHCPV6_LEASEQUERY packet.
    Pkt6Ptr makeQueryByRelayId(const DuidPtr& qry_cid,
                               const IOAddress& link_addr
                               = IOAddress::IPV6_ZERO_ADDRESS()) const {
        OptionPtr opt = makeRelayIdOption(qry_cid->getDuid());
        return (makeLeaseQuery(LQ6QT_BY_RELAY_ID, opt, link_addr));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by remote id.
    ///
    /// @param qry_cid remote id for which to query.
    /// @param link_addr link address to filter by.
    ///
    /// @return DHCPV6_LEASEQUERY packet.
    Pkt6Ptr makeQueryByRemoteId(const OptionBuffer& qry_cid,
                                const IOAddress& link_addr
                                = IOAddress::IPV6_ZERO_ADDRESS()) const {
        OptionPtr opt = makeRemoteIdOption(qry_cid);
        return (makeLeaseQuery(LQ6QT_BY_REMOTE_ID, opt, link_addr));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by link address.
    ///
    /// @param link_addr link address to filter by.
    ///
    /// @return DHCPV6_LEASEQUERY packet.
    Pkt6Ptr makeQueryByLinkAddr(const IOAddress& link_addr) const {
        return (makeLeaseQuery(LQ6QT_BY_LINK_ADDRESS, OptionPtr(), link_addr));
    }

    /// @brief Constructs a DHCPV6_LEASEQUERY message.
    ///
    /// @param qry_type type of query to perform.
    /// @param qry_opt option to add to the query. Default null.
    /// @param qry_link_addr ip address of the link for which to query.
    /// Defaults to ::.
    Pkt6Ptr makeLeaseQuery(const uint8_t& qry_type,
                           const OptionPtr& qry_opt = OptionPtr(),
                           const IOAddress& qry_link_addr =
                           IOAddress::IPV6_ZERO_ADDRESS()) const {
        Pkt6Ptr lq(new Pkt6(DHCPV6_LEASEQUERY, 123));
        // Give a client id and a known requester.
        lq->addOption(makeClientIdOption(vector<uint8_t>{ 01, 02, 03, 04, 05, 06}));
        lq->setRemoteAddr(IOAddress("2001:db8:2::1"));

        // Create the query option.
        const OptionDefinition& lq_query_def = LibDHCP::D6O_LQ_QUERY_DEF();
        OptionCustomPtr lq_option(new OptionCustom(lq_query_def, Option::V6));

        // Set the query option's query type and query link fields.
        lq_option->writeInteger<uint8_t>(qry_type, 0);
        lq_option->writeAddress(qry_link_addr, 1);
        if (qry_opt) {
            lq_option->addOption(qry_opt);
        }

        lq->addOption(lq_option);
        return (lq);
    }

    /// @brief Validate a D6O_IAAddr option against a lease and elapsed time.
    ///
    /// @param opt OptionPtr which should point to a D6O_IAAddr instance.
    /// @param lease lease from which the option should have been created.
    /// @param elapsed number of seconds that have elapsed since the
    /// lease's CLTT.
    void checkIAAddrOption(OptionPtr opt, const Lease6Ptr lease, uint32_t elapsed) {
        Option6IAAddrPtr iaaddr_opt;
        iaaddr_opt = boost::dynamic_pointer_cast<Option6IAAddr>(opt);
        ASSERT_TRUE(iaaddr_opt);
        EXPECT_EQ(lease->addr_, iaaddr_opt->getAddress());
        EXPECT_EQ(lease->valid_lft_ - elapsed, iaaddr_opt->getValid());
        EXPECT_EQ(lease->preferred_lft_ - elapsed, iaaddr_opt->getPreferred());
    }

    /// @brief Validate a D6O_IAPrefix option against a lease and elapsed time.
    ///
    /// @param opt OptionPtr which should point to a D6O_IAAddr instance.
    /// @param lease lease from which the option should have been created.
    /// @param elapsed number of seconds that have elapsed since the
    /// lease's CLTT.
    void checkIAPrefixOption(OptionPtr opt, const Lease6Ptr lease, uint32_t elapsed) {
        Option6IAPrefixPtr iaprefix_opt;
        iaprefix_opt = boost::dynamic_pointer_cast<Option6IAPrefix>(opt);
        ASSERT_TRUE(iaprefix_opt);
        EXPECT_EQ(lease->addr_, iaprefix_opt->getAddress());
        EXPECT_EQ(lease->prefixlen_, iaprefix_opt->getLength());
        EXPECT_EQ(lease->valid_lft_ - elapsed, iaprefix_opt->getValid());
        EXPECT_EQ(lease->preferred_lft_ - elapsed, iaprefix_opt->getPreferred());
    }

    /// @brief Validate that a Pkt6 contains the expected D6O_STATUS_CODE.
    ///
    /// @param response response packet.
    /// @param exp_status expected status code.
    /// @param exp_msg expected status text message.
    void checkStatus(const Pkt6Ptr& response,
                     const DHCPv6StatusCode& exp_status,
                     const string& exp_msg = "") {
        Option6StatusCodePtr status_opt =
            boost::dynamic_pointer_cast<Option6StatusCode>
                (response->getOption(D6O_STATUS_CODE));
        ASSERT_TRUE(status_opt) << "D6O_STATUS_CODE missing";
        checkStatus(status_opt, exp_status, exp_msg);
    }

    /// @brief Validate that a Pkt6 contains the expected D6O_STATUS_CODE.
    ///
    /// @param status_opt status-code option to check.
    /// @param exp_status expected status code.
    /// @param exp_msg expected status text message.
    void checkStatus(Option6StatusCodePtr& status_opt,
                     const DHCPv6StatusCode& exp_status,
                     const string& exp_msg = "") {
        EXPECT_EQ(status_opt->getStatusCode(), exp_status);
        EXPECT_EQ(status_opt->getStatusMessage(), exp_msg);
    }

    /// @brief Verify client data.
    ///
    /// @param response Response packet.
    /// @param[out] options Options from the client data option.
    void verifyClientData(Pkt6Ptr response, OptionCollection& options) {
        ASSERT_TRUE(response);
        OptionPtr opt = response->getOption(D6O_CLIENT_DATA);
        ASSERT_TRUE(opt) << "can't find D6O_CLIENT_DATA";
        OptionCustomPtr data_option;
        data_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
        ASSERT_TRUE(data_option) << "D6O_CLIENT_DATA is not OptionCustom";
        options = data_option->getOptions();
    }

    /// @brief Verify client id.
    ///
    /// @param cid Expected client id.
    /// @param options Options where to find the client id option.
    void verifyClientId(DuidPtr cid, const OptionCollection& options) {
        ASSERT_TRUE(cid);
        auto it = options.find(D6O_CLIENTID);
        ASSERT_TRUE(it != options.end()) << "can't find D6O_CLIENTID";
        EXPECT_EQ(cid->getDuid(), it->second->getData());
    }

    /// @brief Verify CLTT.
    ///
    /// @param cltt Expected CLTT.
    /// @param options Options where to find the CLT time option.
    void verifyCLTT(uint32_t cltt, const OptionCollection& options) {
        auto it = options.find(D6O_CLT_TIME);
        ASSERT_TRUE(it != options.end()) << "can't find D6O_CLT_TIME";
        OptionUint32Ptr cltt_opt;
        cltt_opt = boost::dynamic_pointer_cast<OptionUint32>(it->second);
        ASSERT_TRUE(cltt_opt) << "D6O_CLT_TIME is not OptionUint32";
        EXPECT_EQ(cltt, cltt_opt->getValue());
    }

    /// @brief Verify IAADDR.
    ///
    /// @param addr Expected address.
    /// @param options Options where to find the IAADDR option.
    void verifyIAADDR(const IOAddress& addr, const OptionCollection& options) {
        auto it = options.find(D6O_IAADDR);
        ASSERT_TRUE(it != options.end()) << "can't find D6O_IAADDR";
        Option6IAAddrPtr iaaddr_opt;
        iaaddr_opt = boost::dynamic_pointer_cast<Option6IAAddr>(it->second);
        ASSERT_TRUE(iaaddr_opt) << "D6O_IAADDR is not Option6IAAddrPtr";
        EXPECT_EQ(addr, iaaddr_opt->getAddress());
    }
};

} // end of namespace isc::lease_query::test
} // end of namespace isc::lease_query
} // end of namespace isc
