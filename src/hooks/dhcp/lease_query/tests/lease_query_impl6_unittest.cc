// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests LeaseQueryImpl6 class.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_int.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/pkt6.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <lease_query_impl6.h>
#include <test_lease_mgr.h>

#include <gtest/gtest.h>
#include <sstream>
#include <queue>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::lease_query;
using namespace isc::stats;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief LeaseQueryImpl6 derivation for testing
///
/// This derivation overrides the send() method with a simple
/// queue which captures "outbound" responses so they may
/// be examined.
class LeaseQueryTestImpl6 : public LeaseQueryImpl6 {
public:
    /// @brief Constructor
    ///
    /// @param config input configuration
    /// @param queue reference to queue on which to place sent packets
    LeaseQueryTestImpl6(const isc::data::ConstElementPtr config, std::queue<Pkt6Ptr>& queue)
    : LeaseQueryImpl6(config), packet_queue_(queue) {
    }

    /// @brief Sends a DHCPv6 packet
    ///
    /// Overrides the base class implementation. Rather than passing the
    /// packet to IfaceMgr it pushes it to the end of the packet queue.
    void send(const Pkt6Ptr& packet) const override {
        packet_queue_.push(packet);
    }

    /// @brief Reference to the queue of packets
    std::queue<Pkt6Ptr>& packet_queue_;
};

/// @brief Text fixture for testing LeaseQueryImpl6
template <typename TestLeaseMgrType>
class BaseLeaseQueryImpl6ProcessTest : public ::testing::Test {
public:
    /// @brief Path name of server's duid file
    static const std::string duid_file_;

    /// @brief Constructor
    ///
    /// Clears the configuration and unloads hook libraries.
    BaseLeaseQueryImpl6ProcessTest()
        : cid_empty_(),
          cid1_(new DUID(std::vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x06 })),
          cid2_(new DUID(std::vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x07 })) {
        CfgMgr::instance().clear();
    }

    /// @brief Destructor
    ///
    /// Clears the configuration and unloads hook libraries.
    virtual ~BaseLeaseQueryImpl6ProcessTest() {
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        static_cast<void>(remove(duid_file_.c_str()));
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.destroySchema();
    }

    /// @brief  Prepares system managers for testing
    /// - Creates a new v4 lease manager
    /// - Creates the configuration.
    /// - Inits IfaceMgr with test config.
    void SetUp() override {
        LeaseMgrFactory::destroy();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.createSchema();
        LeaseMgrFactory::create(test_lease_mgr.dbAccess());

        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets6Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets6();

        // Build and add subnet2_.
        subnet2_.reset(new Subnet6(IOAddress("2001:db8:2::"), 64,
                                   1200, 2400, 3600, 3600, 2));

        Pool6Ptr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                IOAddress("2001:db8:2::200")));

        CfgOptionPtr cfg_option = pool->getCfgOption();
        subnet2_->addPool(pool);

        // Add a second pool.
        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:2::201"),
                             IOAddress("2001:db8:2::220")));
        subnet2_->addPool(pool);
        subnets->add(subnet2_);

        // Build and add subnet3_.
        Triplet<uint32_t> unspec;
        subnet3_.reset(new Subnet6(IOAddress("2001:db8:3::"), 64,
                                   unspec, unspec, 3600, 3600, 3));

        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                             IOAddress("2001:db8:3::200")));

        subnet3_->addPool(pool);
        subnet3_->setT1Percent(0.5);
        subnet3_->setT2Percent(0.75);
        subnet3_->setCalculateTeeTimes(true);
        subnets->add(subnet3_);

        // Build and add subnet4_.
        subnet4_.reset(new Subnet6(IOAddress("2001:db8:4::"), 64,
                                   unspec, unspec, 3600, 3600, 4));

        pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                             IOAddress("2001:db8:4::200")));

        subnet4_->addPool(pool);

        // Add PD pool
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("3001::"), 64, 64));
        subnet4_->addPool(pool);

        // Add second PD pool
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("3002::"), 64, 72));
        subnet4_->addPool(pool);

        subnet4_->setCalculateTeeTimes(false);
        subnets->add(subnet4_);

        // Build and add a shared-network.
        CfgSharedNetworks6Ptr networks = cfg_mgr.getStagingCfg()->getCfgSharedNetworks6();
        network1_.reset(new SharedNetwork6("one"));
        network1_->add(subnet4_);
        networks->add(network1_);

        // Configure a server id
        server_id_ = CfgMgr::instance().getStagingCfg()->getCfgDUID()->create(duid_file_);

        // Commit the config.
        cfg_mgr.commit();

        // Initialize interface mgr with test config.
        iface_config_.reset(new IfaceMgrTestConfig(true));
        IfaceMgr::instance().openSockets6();
    }

    /// @brief Instantiates a LeaseQueryImpl6 with a valid configuration
    ///
    /// @return Pointer to the new instance.
    LeaseQueryImpl6Ptr createLeaseQueryImpl6(const std::string& prefixes = "") {
        std::ostringstream oss;
        oss << "{ \"requesters\" : [ \"2001:db8:2::1\", \"2001:db8:3::1\" ]";
        if (!prefixes.empty()) {
            oss << ", \"prefix-lengths\" : " << prefixes;
        }

        oss << " }";

        ConstElementPtr config;
        try {
            config = Element::fromJSON(oss.str());
        } catch (const exception& ex) {
            isc_throw(Unexpected, "invalid query config, test is broken: "
                      << ex.what());
        }

        LeaseQueryImpl6Ptr impl;
        try {
            impl.reset(new LeaseQueryTestImpl6(config, sent_packets_));
        } catch (const exception& ex) {
            isc_throw(Unexpected, "impl creation failed: " << ex.what());
        }

        return (impl);
    }

    /// @brief Adds a v6 lease to the lease store.
    ///
    /// @param ltype lease type of the lease
    /// @param addr ip address of the lease
    /// @param subnet  subnet to which the lease belongs
    /// @param client_id duid of the lease owner
    /// @param cltt CLTT of the lease
    /// @param json_context user context of the lease as JSON
    /// @param state lease state of the lease
    ///
    /// @return pointer to the new lease
    Lease6Ptr addLease(const Lease::Type& ltype, const IOAddress& addr,
                       const Subnet6Ptr& subnet, const DuidPtr& client_id,
                       time_t cltt, const std::string& json_context = "",
                       const uint32_t state = Lease::STATE_DEFAULT) {
        static uint32_t iaid=1;

        if (!subnet) {
            isc_throw(Unexpected, "subnet cannot be empty");
        }

        Lease6Ptr lease(new Lease6(ltype, addr, client_id, ++iaid, subnet->getPreferred(),
                                   subnet->getValid(), subnet->getID()));
        lease->cltt_ = cltt;
        lease->state_ = state;
        if (!json_context.empty()) {
            ElementPtr user_context;
            user_context = Element::fromJSON(json_context);
            lease->setContext(user_context);
        }

        LeaseMgrFactory::instance().addLease(lease);
        return (lease);
    }

    /// @brief Converts a packed RELAY_FORW message into a list of RelayInfos
    ///
    /// This function was largely borrowed from Pkt6. The primary difference
    /// is not expected the innermost message to contain a D6O_RELAY_MSG.
    ///
    /// @param data buffer containing the packed RELAY_FORW message
    /// @param[out] relay_infos list into which the RelayInfo instances
    /// should be stored.
    void unpackRelayForwardMsg(const std::vector<uint8_t>data,
                               std::vector<RelayInfoPtr>& relay_infos) {
        size_t bufsize = data.size();
        size_t offset = 0;

        while (bufsize >= Pkt6::DHCPV6_RELAY_HDR_LEN) {
            RelayInfoPtr relay(new Pkt6::RelayInfo);

            size_t relay_msg_offset = 0;
            size_t relay_msg_len = 0;

            // parse fixed header first (first 34 bytes)
            relay->msg_type_ = data[offset++];
            if (relay->msg_type_ != DHCPV6_RELAY_FORW) {
                isc_throw(Unexpected, "invalid message type: " << relay->msg_type_);
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

            // If custom option parsing function has been set, use this function
            // to parse options. Otherwise, use standard function from libdhcp.
            int last_offset =
            LibDHCP::unpackOptions6(opt_buffer, DHCP6_OPTION_SPACE, relay->options_,
                                    &relay_msg_offset, &relay_msg_len);

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
    /// @param opt_type option type (D6O_...)
    /// @param data binary data a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeBinaryOption(const uint16_t& opt_type,
                               const std::vector<uint8_t>& data) const {
        OptionPtr opt(new Option(Option::V6, opt_type, data));
        return (opt);
    }

    /// @brief Convenience method for making a server identifier option instance.
    ///
    /// @param data server id as a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeServerIdOption(const std::vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_SERVERID, data));
    }

    /// @brief Convenience method for making a client identifier option instance.
    ///
    /// @param data client id as a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeClientIdOption(const std::vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_CLIENTID, data));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by ip address
    ///
    /// @param qry_iaaddr ip address for which to query
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByIpAddress(const IOAddress& qry_iaaddr) const {
        return (makeLeaseQuery(LQ6QT_BY_ADDRESS, qry_iaaddr, DuidPtr()));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by client id
    ///
    /// @param qry_cid client id for which to query
    /// @param link_addr link address to filter by
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByClientId(const DuidPtr& qry_cid, const IOAddress& link_addr
                                = IOAddress::IPV6_ZERO_ADDRESS()) const {
        return (makeLeaseQuery(LQ6QT_BY_CLIENTID, link_addr, qry_cid));
    }

    /// @brief Constructs a DHCPV6_LEASEQUERY message.
    ///
    /// @param qry_type type of query to perform
    /// @param qry_iaaddr ip address for which to query
    /// @param qry_link_addr ip address of the link for which to query. Defaults
    /// to ::.
    Pkt6Ptr makeLeaseQuery(const uint8_t& qry_type, const IOAddress& qry_iaaddr,
                           const DuidPtr& qry_cid, const IOAddress& qry_link_addr =
                           IOAddress::IPV6_ZERO_ADDRESS()) const {
        Pkt6Ptr lq(new Pkt6(DHCPV6_LEASEQUERY, 123));
        // Give a client id and a known requester.
        lq->addOption(makeClientIdOption(std::vector<uint8_t>{ 01, 02, 03, 04, 05, 06}));
        lq->setRemoteAddr(IOAddress("2001:db8:2::1"));

        // Create the query option.
        const OptionDefinition& lq_query_def = LibDHCP::D6O_LQ_QUERY_DEF();
        OptionCustomPtr lq_option(new OptionCustom(lq_query_def, Option::V6));

        // Set the query option's query type and query link fields.
        lq_option->writeInteger<uint8_t>(qry_type, 0);
        lq_option->writeAddress(qry_link_addr, 1);

        // Add a D6O_IAADDR option if we have a non-zero address parameter.
        if (qry_iaaddr != IOAddress::IPV6_ZERO_ADDRESS()) {
            Option6IAAddrPtr opt;
            opt.reset(new Option6IAAddr(D6O_IAADDR, qry_iaaddr, 0, 0));
            lq_option->addOption(opt);
        }

        // Add a D6O_CLIENTID option if we have a non-empty client id parameter.
        if (qry_cid) {
            OptionPtr opt = makeClientIdOption(qry_cid->getDuid());
            lq_option->addOption(opt);
        }

        lq->addOption(lq_option);
        return (lq);
    }

    /// @brief Validate a D6O_IAAddr option against a lease and elapsed time
    ///
    /// @param opt OptionPtr which should point to a D6O_IAAddr instance
    /// @param lease lease from which the option should have been created
    /// @param elapsed number of seconds that have elapsed since the
    /// lease's CLTT
    void checkIAAddrOption(OptionPtr opt, const Lease6Ptr lease, uint32_t elapsed) {
        Option6IAAddrPtr iaaddr_opt;
        iaaddr_opt = boost::dynamic_pointer_cast<Option6IAAddr>(opt);
        ASSERT_TRUE(iaaddr_opt);
        EXPECT_EQ(lease->addr_, iaaddr_opt->getAddress());
        // Since the initial lifetime were set, one second could have ticked,
        // so allow one second of margin error.
        EXPECT_NEAR(lease->valid_lft_ - elapsed, iaaddr_opt->getValid(), 1);
        EXPECT_NEAR(lease->preferred_lft_ - elapsed, iaaddr_opt->getPreferred(), 1);
    }

    /// @brief Validate a D6O_IAPrefix option against a lease and elapsed time
    ///
    /// @param opt OptionPtr which should point to a D6O_IAAddr instance
    /// @param lease lease from which the option should have been created
    /// @param elapsed number of seconds that have elapsed since the
    /// lease's CLTT
    void checkIAPrefixOption(OptionPtr opt, const Lease6Ptr lease, uint32_t elapsed = 0) {
        Option6IAPrefixPtr iaprefix_opt;
        iaprefix_opt = boost::dynamic_pointer_cast<Option6IAPrefix>(opt);
        ASSERT_TRUE(iaprefix_opt);
        EXPECT_EQ(lease->addr_, iaprefix_opt->getAddress());
        EXPECT_EQ(lease->prefixlen_, iaprefix_opt->getLength());
        if (elapsed) {
            // Since the initial lifetime were set, one second could have ticked,
            // so allow one second of margin error.
            EXPECT_NEAR(lease->valid_lft_ - elapsed, iaprefix_opt->getValid(), 1);
            EXPECT_NEAR(lease->preferred_lft_ - elapsed, iaprefix_opt->getPreferred(), 1);
        }
    }

    /// @brief Validate that a Pkt6 contains the expected D6O_STATUS_CODE
    ///
    /// @param reply reply packet
    /// @param exp_status expected status code
    /// @param exp_msg expected status text message
    void checkStatus(const Pkt6Ptr& reply, const DHCPv6StatusCode& exp_status,
                     const std::string& exp_msg = "") {
        Option6StatusCodePtr status_opt = boost::dynamic_pointer_cast<Option6StatusCode>
                                          (reply->getOption(D6O_STATUS_CODE));
        ASSERT_TRUE(status_opt) << "D6O_STATUS_CODE missing";
        checkStatus(status_opt, exp_status, exp_msg);
    }

    /// @brief Validate that a Pkt6 contains the expected D6O_STATUS_CODE
    ///
    /// @param status_opt status-code option to check
    /// @param exp_status expected status code
    /// @param exp_msg expected status text message
    void checkStatus(Option6StatusCodePtr& status_opt, const DHCPv6StatusCode& exp_status,
                     const std::string& exp_msg = "") {
        EXPECT_EQ(status_opt->getStatusCode(), exp_status);
        EXPECT_EQ(status_opt->getStatusMessage(), exp_msg);
    }

    /// @brief Fetches a packet from the sent packet queue
    ///
    /// Used in conjunction with LeaseQueryTestImpl6 instances which
    /// "send" packets to the queue.  If the queue is not empty, it pops a
    /// a packed packet from the queue.  It then creates a clone using the
    /// packed content, and unpacks it.  The clone is then returned.
    /// Cloning ensures that callers do not see any vestigial information.
    ///
    /// @return A clone of the packet de-queued
    Pkt6Ptr getSentPacket() {
        Pkt6Ptr clone;
        if (!sent_packets_.empty()) {
            Pkt6Ptr sent_packet = sent_packets_.front();
            sent_packets_.pop();
            clone.reset(new Pkt6(sent_packet->getBuffer().getData(),
                                 sent_packet->getBuffer().getLength()));
            clone->unpack();
        }

        return (clone);
    }

    /// @brief Flushes any packets in the sent packet queue.
    void flushSentPackets() {
        while (!sent_packets_.empty()) {
            sent_packets_.pop();
        }
    }

    /// @brief Test makeClientOption with multiple links.
    void testMakeClientOptionMultipleLinks();

    /// @brief Test makeClientOption with a single link.
    void testMakeClientOptionSingleLink();

    /// @brief Test makeRelayOption with no relay info.
    void testMakeRelayOptionNoRelayInfo();

    /// @brief Test makeRelayOption with relay info.
    void testMakeRelayOptionRelayInfo();

    /// @brief Test makeRelayOption with old relay info.
    void testOldMakeRelayOptionRelayInfo();

    /// @brief Test queryByIpAddress with no active lease.
    void testQueryByIpAddressNoActiveLease();

    /// @brief Test queryByIpAddress with active lease.
    void testQueryByIpAddressActiveLease();

    /// @brief Test queryByClientId with no active lease.
    void testQueryByClientIdNoActiveLease();

    /// @brief Test queryByClientId with multiple links.
    void testQueryByClientIdMultipleLinks();

    /// @brief Test queryByClientId with active leases.
    void testQueryByClientIdActiveLeases();

    /// @brief Test queryByClientId with link address.
    void testQueryByClientIdLinkAddr();

    /// @brief Test queryByIpaddress with prefix delegation leases.
    void testQueryByIpaddressPDLeases();

    /// @brief Queue to hold any packets sent by LeaseQueryImpl6Test
    /// instances.
    std::queue<Pkt6Ptr> sent_packets_;

    /// @brief Convenience values.
    DuidPtr cid_empty_;
    DuidPtr cid1_;
    DuidPtr cid2_;
    Subnet6Ptr subnet2_;
    Subnet6Ptr subnet3_;
    Subnet6Ptr subnet4_;
    SharedNetwork6Ptr network1_;
    DuidPtr server_id_;

    // Test configuration for IfaceMgr.
    boost::shared_ptr<IfaceMgrTestConfig> iface_config_;
};

/// @brief Path name for server-id generation
template <typename TestLeaseMgrType> const std::string
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::duid_file_
    = std::string(TEST_DATA_BUILDDIR) + std::string("/lq6-duid");

// Verifies that configuration errors are detected.
TEST(LeaseQueryImpl6Test, invalidConfig6) {

    struct Scenario {
        const std::string description_;
        ConstElementPtr config_;
        const std::string exp_msg_;
    };

    std::vector<Scenario> scenarios = {
        {
            "empty config",
            ConstElementPtr(),
            "Lease Query config is empty or not a map"
        },
        {
            "config not a map",
            Element::create("foo"),
            "Lease Query config is empty or not a map"
        },
        {
            "requesters missing",
            Element::fromJSON("{}"),
            "'requesters' address list is missing or not a list"
        },
        {
            "requesters not a list",
            Element::fromJSON("{ \"requesters\" : 123 }"),
            "'requesters' address list is missing or not a list"
        },
        {
            "requesters list is empty",
            Element::fromJSON("{ \"requesters\" : [] }"),
            "'requesters' address list cannot be empty"
        },
        {
            "requesters entry not an address",
            Element::fromJSON("{ \"requesters\" : [ \"foo\" ] }"),
            "'requesters' entry 'foo' is invalid: Failed to convert"
            " string to address 'foo': Invalid argument"
        },
        {
            "requesters entry not a v6 address",
            Element::fromJSON("{ \"requesters\" : [ \"192.0.2.1\" ] }"),
            "'requesters' entry '192.0.2.1' is invalid: not a IPv6 address"
        },
        {
            "requesters entry is a duplicate",
            Element::fromJSON("{ \"requesters\" : [ \"2001:db8:1::\", \"2001:db8:1::\" ] }"),
            "'requesters' entry '2001:db8:1::' is invalid: address is already in the list"
        },
        {
            "prefix_lengths not a list",
            Element::fromJSON("{ \"requesters\" : [ \"2001:db8:1::\" ], \"prefix-lengths\": 77 }"),
            "'prefix-lengths' is not a list"
        },
        {
            "prefix_lengths entry is not an int",
            Element::fromJSON("{ \"requesters\" : [ \"2001:db8:1::\" ], \"prefix-lengths\": [ \"boo\" ] }"),
            "'prefix-lengths' entry '\"boo\"' is invalid: must be an integer"
        },
        {
            "prefix_lengths entry is 0",
            Element::fromJSON("{ \"requesters\" : [ \"2001:db8:1::\" ], \"prefix-lengths\": [ 0 ] }"),
            "'prefix-lengths' entry '0' is invalid: must be greater than 0 and less than or equal to 128"

        },
        {
            "prefix_lengths entry is 129",
            Element::fromJSON("{ \"requesters\" : [ \"2001:db8:1::\" ], \"prefix-lengths\": [ 4, 129 ] }"),
            "'prefix-lengths' entry '129' is invalid: must be greater than 0 and less than or equal to 128"

        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        LeaseQueryImplPtr impl;
        ASSERT_THROW_MSG(impl.reset(new LeaseQueryImpl6(scenario.config_)),
                         BadValue, scenario.exp_msg_);
    }
}

// Verifies that valid v6 configuration parses and that requesters
// can be validated.
TEST(LeaseQueryImpl6Test, validConfig6) {
    // Create an implementation with two requesters.
    const std::string json = "{ \"requesters\" : [ \"2001:db8:1::1\", \"2001:db8:1::3\" ] }";
    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));

    LeaseQueryImplPtr impl;
    ASSERT_NO_THROW_LOG(impl.reset(new LeaseQueryImpl6(config)));

    // Verify known and unknown requesters check correctly.
    EXPECT_FALSE(impl->isRequester(IOAddress("2001:db8:1::")));
    EXPECT_TRUE(impl->isRequester(IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(impl->isRequester(IOAddress("2001:db8:1::2")));
    EXPECT_TRUE(impl->isRequester(IOAddress("2001:db8:1::3")));

    // Make sure a test with a v4 address complains.
    ASSERT_THROW_MSG(impl->isRequester(IOAddress("192.0.2.1")), BadValue,
                     "not a IPv6 address");
}

/// @brief Memfile test fixture.
class MemfileLeaseQueryImpl6ProcessTest : public
    BaseLeaseQueryImpl6ProcessTest<MemfileTestLeaseMgr> {
};

// These tests verify scenarios where the inbound packet invalid and
// to for which the hook lib will drop the packet without generating
// a reply.
// - Not a DHCPv6 packet
// - No D6O_CLIENTID option
// - Non-matching D6O_SERVERID
// - Source address of ::
// - Source address that does not match a requester
// - No D6O_LQ_QUERY option
TEST_F(MemfileLeaseQueryImpl6ProcessTest, processQueryInvalidQuery) {
    // Create an implementation with two requesters.
    const std::string json = "{ \"requesters\" : [ \"2001:db8:2::1\", \"2001:db8:3::1\" ] }";
    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl.reset(new LeaseQueryImpl6(config)));

    // A v4 packet should get tossed.
    Pkt4Ptr pkt4(new Pkt4(DHCPLEASEQUERY, 0));
    ASSERT_THROW_MSG(impl->processQuery(pkt4), BadValue,
                     "LeaseQueryImpl6 query is not DHCPv6 packet");

    // No client-id option should fail.
    Pkt6Ptr lq(new Pkt6(DHCPV6_LEASEQUERY_REPLY, 123));
    ASSERT_THROW_MSG(impl->processQuery(lq), BadValue,
                     "DHCPV6_LEASEQUERY must supply a D6O_CLIENTID");

    // Add a client-id option.
    lq->addOption(makeClientIdOption(std::vector<uint8_t>{ 01, 02, 03, 04, 05, 06}));

    // Add an a non-matching server id.
    lq->addOption(makeServerIdOption(std::vector<uint8_t>{ 10, 11, 12, 13, 14, 15, 16 }));
    ASSERT_THROW_MSG(impl->processQuery(lq), BadValue,
                     "rejecting DHCPV6_LEASEQUERY from: ::,"
                     " unknown server-id: type=00002, len=00007: 0a:0b:0c:0d:0e:0f:10");

    // Add a matching server id.
    lq->delOption(D6O_SERVERID);
    lq->addOption(makeServerIdOption(server_id_->getDuid()));

    // Source address cannot be ::.
    ASSERT_THROW_MSG(impl->processQuery(lq), BadValue,
                     "DHCPV6_LEASEQUERY source address cannot be ::");

    // Set the pkt6-admin-filtered stat to 0.
    StatsMgr::instance().setValue("pkt6-admin-filtered", static_cast<int64_t>(0));

    // Set source address to an unknown requester address.
    lq->setRemoteAddr(IOAddress("de:ad:be:ef::"));

    // An unknown requester should fail.
    ASSERT_THROW_MSG(impl->processQuery(lq), BadValue,
                     "rejecting DHCPV6_LEASEQUERY from unauthorized requester: de:ad:be:ef::");

    // Check the stat which was bumped by one.
    ObservationPtr stat = StatsMgr::instance().getObservation("pkt6-admin-filtered");
    ASSERT_TRUE(stat);
    EXPECT_EQ(1, stat->getInteger().first);

    // Set source address to a known requester address.
    lq->setRemoteAddr(IOAddress("2001:db8:2::1"));

    // A query without a D6O_LQ_QUERY option should fail.
    ASSERT_THROW_MSG(impl->processQuery(lq), BadValue,
                     "DHCPV6_LEASEQUERY must supply a D6O_LQ_QUERY option");
}

// Verifies the operation of LeaseQueryImpl6::initReply().
TEST_F(MemfileLeaseQueryImpl6ProcessTest, initReply) {
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());

    Pkt6Ptr lq = makeQueryByIpAddress(IOAddress("2001:db8::100"));
    lq->setIface("eth1");
    lq->setIndex(ETH1_INDEX);
    lq->setRemoteAddr(IOAddress("2001:db8::77"));
    lq->setRemotePort(777);
    lq->setLocalAddr(IOAddress("2001:db8::88"));
    lq->setLocalPort(888);

    // Given a valid content in the query, the reply should
    // be generated without a throw.
    Pkt6Ptr reply;
    ASSERT_NO_THROW_LOG(reply = impl->initReply(lq));
    ASSERT_TRUE(reply);

    // Make sure it's the right message type.
    EXPECT_EQ(DHCPV6_LEASEQUERY_REPLY, reply->getType());

    // Verify reply content that is copied from the
    // input query.
    EXPECT_EQ(lq->getTransid(), reply->getTransid());
    EXPECT_EQ(lq->getRemoteAddr(), reply->getRemoteAddr());
    EXPECT_EQ(lq->getRemotePort(), reply->getRemotePort());
    EXPECT_EQ(lq->getLocalAddr(), reply->getLocalAddr());;
    EXPECT_EQ(lq->getLocalPort(), reply->getLocalPort());
    EXPECT_EQ(lq->getIface(), reply->getIface());
    EXPECT_EQ(lq->getIndex(), reply->getIndex());

    // Reply should have a client id and it should match
    // the client id in the query.
    ASSERT_TRUE(reply->getClientId());
    EXPECT_EQ(*(lq->getClientId()), *(reply->getClientId()));

    // Reply should have the server-id.
    OptionPtr server_id_opt =  reply->getOption(D6O_SERVERID);
    ASSERT_TRUE(server_id_opt);
    EXPECT_EQ(server_id_->getDuid(), server_id_opt->getData());

    // Verify that a query missing the D6O_CLIENTID option throws.
    // This case really shouldn't happen.
    lq->delOption(D6O_CLIENTID);
    ASSERT_THROW_MSG(reply = impl->initReply(lq), Unexpected,
                     "query has no D6O_CLIENTID");
}

// Verifies that makeClientOption() throws when passed an empty
// lease collection.
TEST_F(MemfileLeaseQueryImpl6ProcessTest, makeClientOptionNoLeases) {
    Lease6Collection leases;

    ASSERT_THROW_MSG(LeaseQueryImpl6::makeClientOption(leases), Unexpected,
                     "makeClientOption: leases list is empty");
}

// Verifies that makeClientOption() creates an D6O_LQ_CLIENT_LINK option
// when passed a lease collection containing active leases from
// multiple subnets.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testMakeClientOptionMultipleLinks() {
    Lease6Collection leases;

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                subnet2_, cid1_, time(0));
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                                subnet3_, cid1_, time(0));
    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::101"),
                                subnet3_, cid1_, time(0));
    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::101"),
                                subnet4_, cid1_, time(0));

    // Add them to lease collection.
    leases.push_back(lease2);
    leases.push_back(lease1);
    leases.push_back(lease4);
    leases.push_back(lease3);

    // Invoke makeClientOption.
    OptionPtr opt;
    ASSERT_NO_THROW_LOG(opt = LeaseQueryImpl6::makeClientOption(leases));

    // We should have a non-empty option. That converts to an Option6AddrLst.
    ASSERT_TRUE(opt);
    ASSERT_EQ(D6O_LQ_CLIENT_LINK, opt->getType());
    Option6AddrLstPtr link_opt = boost::dynamic_pointer_cast<Option6AddrLst>(opt);
    ASSERT_TRUE(link_opt);

    // We should have the addresses for subnet2_, subnet3_, and sunbed4_
    // in that order.  Note subnet3_ should only be in the list once
    // despite they're being two of its leases in the collection.
    Option6AddrLst::AddressContainer links = link_opt->getAddresses();
    ASSERT_EQ(3, links.size());
    EXPECT_EQ(subnet2_->get().first, links[0]);
    EXPECT_EQ(subnet3_->get().first, links[1]);
    EXPECT_EQ(subnet4_->get().first, links[2]);
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, makeClientOptionMultipleLinks) {
    testMakeClientOptionMultipleLinks();
}

// Verifies that makeClientOption() creates an D6O_CLIENT_DATA option
// when passed a lease collection containing multiple active leases on a
// single subnet.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testMakeClientOptionSingleLink () {
    Lease6Collection leases;
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 100);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::104"),
                                subnet4_, cid1_, now - 200);
    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::108"),
                                subnet4_, cid1_, now - 300);
    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::10a"),
                                subnet4_, cid1_, now - 400);
    Lease6Ptr lease5 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                subnet4_, cid1_, now - 500);
    Lease6Ptr lease6 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:2::"),
                                subnet4_, cid1_, now - 600);

    // Add them to lease collection.
    leases.push_back(lease1);
    leases.push_back(lease2);
    leases.push_back(lease3);
    leases.push_back(lease4);
    leases.push_back(lease5);
    leases.push_back(lease6);

    // Invoke makeClientOption.
    OptionPtr opt;
    ASSERT_NO_THROW_LOG(opt = LeaseQueryImpl6::makeClientOption(leases));
    // We should have a non-empty option, that converts to a OptionCustom
    // i.e. D6O_CLIENT_DATA option.
    ASSERT_TRUE(opt);
    ASSERT_EQ(D6O_CLIENT_DATA, opt->getType());
    OptionCustomPtr data_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(data_option);

    auto options = data_option->getOptions();
    EXPECT_EQ(8, options.size());

    // Verify client id.
    auto opt_iter = options.find(D6O_CLIENTID);
    ASSERT_TRUE(opt_iter != options.end());
    opt = opt_iter->second;
    EXPECT_EQ(cid1_->getDuid(), opt->getData());

    // Verify CLTT, is take from the first lease in the list.
    opt_iter = options.find(D6O_CLT_TIME);
    ASSERT_TRUE(opt_iter != options.end());
    OptionUint32Ptr cltt_opt = boost::dynamic_pointer_cast<OptionUint32>
                              (opt_iter->second);
    // CLTT on the initial lease was set to 100 seconds ago, but one second could have ticked since
    // then, so allow one second of margin error.
    EXPECT_NEAR(cltt_opt->getValue(), 100, 1);

    // Now let's check the TYPE_NA leases. We should have a four leases
    // (lease1 through lease4).
    opt_iter = options.find(D6O_IAADDR);
    ASSERT_TRUE(opt_iter != options.end());
    checkIAAddrOption(opt_iter->second, lease1, 100);

    ASSERT_TRUE(++opt_iter != options.end());
    checkIAAddrOption(opt_iter->second, lease2, 200);

    ASSERT_TRUE(++opt_iter != options.end());
    checkIAAddrOption(opt_iter->second, lease3, 300);

    ASSERT_TRUE(++opt_iter != options.end());
    checkIAAddrOption(opt_iter->second, lease4, 400);

    // Now let's check the TYPE_PD leases. We should have two: lease6 then
    // lease5.
    opt_iter = options.find(D6O_IAPREFIX);
    ASSERT_TRUE(opt_iter != options.end());
    checkIAPrefixOption(opt_iter->second, lease5, 500);

    ASSERT_TRUE(++opt_iter != options.end());
    checkIAPrefixOption(opt_iter->second, lease6, 600);
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, makeClientOptionSingleLink) {
    testMakeClientOptionSingleLink();
}

// Verifies that parseRelayInfo() correctly detects invalid content.
TEST(LeaseQueryImpl6Test, parseRelayInfoInvalid) {
    ElementPtr relay_elem;
    // An empty element will throw.
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: relay element empty or not a map");

    // An element that is not a map will throw.
    relay_elem = Element::create("foo");
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: relay element empty or not a map");

    // 'hop' is required.
    relay_elem = Element::createMap();
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'hop' is missing");

    // 'hop' must be an integer.
    relay_elem->set("hop", Element::create("not an int"));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'hop' is invalid:"
                     " intValue() called on non-integer Element");

    // Add a valid 'hop' entry.
    relay_elem->set("hop", Element::create(1));

    // 'peer' is required.
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'peer' is missing");

    // 'peer' must be an string.
    relay_elem->set("peer", Element::create(777));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'peer' is invalid:"
                     " stringValue() called on non-string Element");

    // 'peer' must convert to an IP address.
    relay_elem->set("peer", Element::create("boo"));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'peer' is invalid: Failed to convert string"
                     " to address 'boo': Invalid argument");

    // 'peer' must convert to an IPv6 address.
    relay_elem->set("peer", Element::create("192.1.2.1"));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'peer' is invalid: not a V6 address: 192.1.2.1");

    // Add a valid 'peer'.
    relay_elem->set("peer", Element::create("2001:db8:1::1"));

    // 'link' is required.
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'link' is missing");

    // 'link' must be an string.
    relay_elem->set("link", Element::create(777));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'link' is invalid:"
                     " stringValue() called on non-string Element");

    // 'link' must convert to an IP address.
    relay_elem->set("link", Element::create("boo"));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'link' is invalid: Failed to convert string"
                     " to address 'boo': Invalid argument");

    // 'link' must convert to an IPv6 address.
    relay_elem->set("link", Element::create("192.1.2.1"));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'link' is invalid: not a V6 address: 192.1.2.1");

    // Add a valid 'link'.
    relay_elem->set("link", Element::create("2001:db8:1::2"));

    // Add an invalid options member.
    relay_elem->set("options", Element::create("not hex digits"));
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfo(relay_elem), BadValue,
                     "parseRelayInfo: 'options' is invalid: invalid format"
                     " of the decoded string 'not hex digits'");
}

// Verifies that parseRelayInfo() correctly parses valid content.
TEST(LeaseQueryImpl6Test, parseRelayInfoValid) {
    ElementPtr relay_elem;

    relay_elem = Element::createMap();
    relay_elem->set("hop", Element::create(1));
    relay_elem->set("peer", Element::create("2001:db8:1::1"));
    relay_elem->set("link", Element::create("2001:db8:1::2"));

    // Should parse because "options" is not a required member.
    RelayInfoPtr relay_info;
    ASSERT_NO_THROW_LOG(relay_info = LeaseQueryImpl6::parseRelayInfo(relay_elem));
    ASSERT_TRUE(relay_info);

    // Make sure the field contents are correct.
    ASSERT_EQ(relay_info->hop_count_, 1);
    ASSERT_EQ(relay_info->peeraddr_, IOAddress("2001:db8:1::1"));
    ASSERT_EQ(relay_info->linkaddr_, IOAddress("2001:db8:1::2"));

    // Make sure there are no options.
    ASSERT_EQ(0, relay_info->options_.size());

    // Now Add a valid options member: D6O_INTERFACE_ID = "eth0"
    relay_elem->set("options", Element::create("0x0012000465746830"));
    ASSERT_NO_THROW_LOG(relay_info = LeaseQueryImpl6::parseRelayInfo(relay_elem));
    ASSERT_TRUE(relay_info);

    // Make sure the field contents are correct.
    ASSERT_EQ(relay_info->hop_count_, 1);
    ASSERT_EQ(relay_info->peeraddr_, IOAddress("2001:db8:1::1"));
    ASSERT_EQ(relay_info->linkaddr_, IOAddress("2001:db8:1::2"));

    // Verify that the relay options_ data unpacked correctly.
    // Under the covers this relies on LibDHCP::unpackOptions6()
    // which is tested pretty exhaustively elsewhere, so we're not
    // going to go nuts with testing here.
    ASSERT_EQ(1, relay_info->options_.size());
    auto x = relay_info->options_.find(0x12);
    ASSERT_TRUE(x != relay_info->options_.end());
    ASSERT_EQ(std::string("type=00018, len=00004: 65:74:68:30 'eth0'"), x->second->toString());
}

// Verifies that parseRelayInfoList() detects invalid lists.
TEST(LeaseQueryImpl6Test, parseRelayInfoListInvalid) {
    ElementPtr relay_list;
    std::vector<RelayInfoPtr> relay_infos;

    // Relay list cannot be null.
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfoList(relay_list, relay_infos), BadValue,
                     "parseRelayInfoList: relay-info element empty or not a list");

    relay_list = Element::create("not a list");
    ASSERT_THROW_MSG(LeaseQueryImpl6::parseRelayInfoList(relay_list, relay_infos), BadValue,
                     "parseRelayInfoList: relay-info element empty or not a list");
}

// Verifies that parseRelayInfoList() correctly parses a valid list.
TEST(LeaseQueryImpl6Test, parseRelayInfoListValid) {
    ElementPtr relay_list;
    std::vector<RelayInfoPtr> relay_infos;

    // Test input which equates to user-context content.
    std::string relays_json =
    "[ \n"
    "   { \n"
    "      \"hop\": 3, \n"
    "      \"peer\": \"2001:db8:3::1\", \n"
    "      \"link\": \"2001:db8:3::2\" \n"
    "   }, \n"
    "   { \n"
    "      \"hop\": 2, \n"
    "      \"peer\": \"2001:db8:2::1\", \n"
    "      \"link\": \"2001:db8:2::2\", \n"
    "      \"options\": \"0x0012000465746830\" \n"
    "   }, \n"
    "   { \n"
    "      \"hop\": 1, \n"
    "      \"peer\": \"2001:db8:1::1\", \n"
    "      \"link\": \"2001:db8:1::2\", \n"
    "      \"options\": \"0x01ff0003666f6f02ff0003626172\" \n"
    "   } \n"
    "]";

    // Make an Element::list of relays.
    ASSERT_NO_THROW_LOG(relay_list = Element::fromJSON(relays_json));

    // Parse it.
    ASSERT_NO_THROW_LOG(LeaseQueryImpl6::parseRelayInfoList(relay_list, relay_infos));

    // We should have three instances.
    ASSERT_EQ(3, relay_infos.size());

    // Verify the first instance.
    // Make sure the field contents are correct.
    ASSERT_EQ(relay_infos[0]->hop_count_, 3);
    ASSERT_EQ(relay_infos[0]->peeraddr_, IOAddress("2001:db8:3::1"));
    ASSERT_EQ(relay_infos[0]->linkaddr_, IOAddress("2001:db8:3::2"));
    // It should have no options.
    ASSERT_EQ(0, relay_infos[0]->options_.size());

    // Verify the second instance.
    ASSERT_EQ(relay_infos[1]->hop_count_, 2);
    ASSERT_EQ(relay_infos[1]->peeraddr_, IOAddress("2001:db8:2::1"));
    ASSERT_EQ(relay_infos[1]->linkaddr_, IOAddress("2001:db8:2::2"));

    // It should have one option.
    ASSERT_EQ(1, relay_infos[1]->options_.size());
    auto x = relay_infos[1]->options_.find(0x12);
    ASSERT_TRUE(x != relay_infos[1]->options_.end());
    ASSERT_EQ(std::string("type=00018, len=00004: 65:74:68:30 'eth0'"), x->second->toString());

    // Verify the third instance.
    ASSERT_EQ(relay_infos[2]->hop_count_, 1);
    ASSERT_EQ(relay_infos[2]->peeraddr_, IOAddress("2001:db8:1::1"));
    ASSERT_EQ(relay_infos[2]->linkaddr_, IOAddress("2001:db8:1::2"));

    // We should have two options, "foo" and then "bar"
    ASSERT_EQ(2, relay_infos[2]->options_.size());

    // Option "foo"
    x = relay_infos[2]->options_.find(0x1FF);
    ASSERT_TRUE(x != relay_infos[2]->options_.end());
    ASSERT_EQ(std::string("type=00511, len=00003: 66:6f:6f 'foo'"), x->second->toString());

    // Option "bar"
    x = relay_infos[2]->options_.find(0x2FF);
    ASSERT_TRUE(x != relay_infos[2]->options_.end());
    ASSERT_EQ(std::string("type=00767, len=00003: 62:61:72 'bar'"), x->second->toString());
}

// Verifies that makeRelayOption() does not return a D6O_RELAY_DATA option
// when given a lease with invalid relay information.
TEST_F(MemfileLeaseQueryImpl6ProcessTest, makeRelayOptionInvalid) {
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 400);

    struct Scenario {
        std::string description_;
        std::string context_json_;
    };

    std::vector<Scenario> scenarios {
        {
        "no ISC entry",
        "{ \"foo\": \"bar\" }"
        },
        {
        "no relays element",
        "{ \"ISC\": {  \"magic\": \"stuff\" } }"
        },
        {
        "empty relay list",
        "{ \"ISC\": {  \"relay-info\": []  } }"
        },
        {
        "relay-info not list",
        "{ \"ISC\": {  \"relay-info\": 123  } }"
        },
        {
        "invalid relay",
        "{ \"ISC\": { \"relay-info\": [{ \"hop\": 1 }] } }"
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        ASSERT_NO_THROW_LOG(lease->setContext(Element::fromJSON(scenario.context_json_)));

        // Invoke makeRelayOption.
        OptionPtr opt;
        ASSERT_NO_THROW_LOG(opt = LeaseQueryImpl6::makeRelayOption(*lease));
        ASSERT_FALSE(opt);
    }
}

// Verifies makeRelayOption() does not return a D6O_RELAY_DATA option
// when given a lease with no relay information.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testMakeRelayOptionNoRelayInfo() {
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 400);

    // Invoke makeRelayOption.
    OptionPtr opt;
    ASSERT_NO_THROW_LOG(opt = LeaseQueryImpl6::makeRelayOption(*lease));
    ASSERT_FALSE(opt);
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, makeRelayOptionNoRelayInfo) {
        testMakeRelayOptionNoRelayInfo();
}

// Verifies makeRelayOption() returns a D6O_RELAY_DATA option
// when given a lease with relay information.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testMakeRelayOptionRelayInfo() {
    time_t now = time(0);

    // JSON user-context content.
    std::string user_context =
    "{ \"ISC\": {"
    "   \"relay-info\": [ \n"
    "       { \n"
    "           \"hop\": 1, \n"
    "           \"peer\": \"2001:db8:2::1\", \n"
    "           \"link\": \"2001:db8:2::2\", \n"
    "           \"options\": \"0x0012000465746830\" \n"
    "       }, \n"
    "       { \n"
    "           \"hop\": 0, \n"
    "           \"peer\": \"2001:db8:1::1\", \n"
    "           \"link\": \"2001:db8:1::2\" \n"
    "       }] \n"
    "   }"
    "}";

    // Create a lease with user-context.
    Lease6Ptr lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 400, user_context);
    // Invoke makeRelayOption.
    OptionPtr opt;
    ASSERT_NO_THROW_LOG(opt = LeaseQueryImpl6::makeRelayOption(*lease));
    ASSERT_TRUE(opt);
    OptionCustomPtr relay_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(relay_option);

    // Verify the peer address field. It should come from the outermost
    // relay.
    IOAddress peer_addr("::");
    ASSERT_NO_THROW_LOG(peer_addr = relay_option->readAddress(0));
    EXPECT_EQ(IOAddress("2001:db8:2::1"), peer_addr);

    // Verify the RELAY_FORW content.
    OptionBuffer relay_forw_data;
    ASSERT_NO_THROW_LOG(relay_forw_data = relay_option->readBinary(1));

    // First we unpack it.
    std::vector<RelayInfoPtr> relay_infos;
    ASSERT_NO_THROW_LOG(unpackRelayForwardMsg(relay_forw_data, relay_infos));

    // We should have two relays.
    EXPECT_EQ(2, relay_infos.size());

    // Verify the first instance.
    // Make sure the field contents are correct.
    ASSERT_EQ(relay_infos[0]->hop_count_, 1);
    ASSERT_EQ(relay_infos[0]->peeraddr_, IOAddress("2001:db8:2::1"));
    ASSERT_EQ(relay_infos[0]->linkaddr_, IOAddress("2001:db8:2::2"));

    // It should have one option.
    ASSERT_EQ(1, relay_infos[0]->options_.size());
    auto x = relay_infos[0]->options_.find(0x12);
    ASSERT_TRUE(x != relay_infos[0]->options_.end());
    ASSERT_EQ(std::string("type=00018, len=00004: 65:74:68:30 'eth0'"), x->second->toString());

    // Verify the second instance.
    ASSERT_EQ(relay_infos[1]->hop_count_, 0);
    ASSERT_EQ(relay_infos[1]->peeraddr_, IOAddress("2001:db8:1::1"));
    ASSERT_EQ(relay_infos[1]->linkaddr_, IOAddress("2001:db8:1::2"));

    // It should have no options.
    ASSERT_EQ(0, relay_infos[1]->options_.size());
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, makeRelayOptionRelayInfo) {
    testMakeRelayOptionRelayInfo();
}

// Same with the old entry name.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testOldMakeRelayOptionRelayInfo() {
    time_t now = time(0);

    // JSON user-context content.
    std::string user_context =
    "{ \"ISC\": {"
    "   \"relays\": [ \n"
    "       { \n"
    "           \"hop\": 1, \n"
    "           \"peer\": \"2001:db8:2::1\", \n"
    "           \"link\": \"2001:db8:2::2\", \n"
    "           \"options\": \"0x0012000465746830\" \n"
    "       }, \n"
    "       { \n"
    "           \"hop\": 0, \n"
    "           \"peer\": \"2001:db8:1::1\", \n"
    "           \"link\": \"2001:db8:1::2\" \n"
    "       }] \n"
    "   }"
    "}";

    // Create a lease with user-context.
    Lease6Ptr lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 400, user_context);
    // Invoke makeRelayOption.
    OptionPtr opt;
    ASSERT_NO_THROW_LOG(opt = LeaseQueryImpl6::makeRelayOption(*lease));
    ASSERT_TRUE(opt);
    OptionCustomPtr relay_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(relay_option);

    // Verify the peer address field. It should come from the outermost
    // relay.
    IOAddress peer_addr("::");
    ASSERT_NO_THROW_LOG(peer_addr = relay_option->readAddress(0));
    EXPECT_EQ(IOAddress("2001:db8:2::1"), peer_addr);

    // Verify the RELAY_FORW content.
    OptionBuffer relay_forw_data;
    ASSERT_NO_THROW_LOG(relay_forw_data = relay_option->readBinary(1));

    // First we unpack it.
    std::vector<RelayInfoPtr> relay_infos;
    ASSERT_NO_THROW_LOG(unpackRelayForwardMsg(relay_forw_data, relay_infos));

    // We should have two relays.
    EXPECT_EQ(2, relay_infos.size());

    // Verify the first instance.
    // Make sure the field contents are correct.
    ASSERT_EQ(relay_infos[0]->hop_count_, 1);
    ASSERT_EQ(relay_infos[0]->peeraddr_, IOAddress("2001:db8:2::1"));
    ASSERT_EQ(relay_infos[0]->linkaddr_, IOAddress("2001:db8:2::2"));

    // It should have one option.
    ASSERT_EQ(1, relay_infos[0]->options_.size());
    auto x = relay_infos[0]->options_.find(0x12);
    ASSERT_TRUE(x != relay_infos[0]->options_.end());
    ASSERT_EQ(std::string("type=00018, len=00004: 65:74:68:30 'eth0'"), x->second->toString());

    // Verify the second instance.
    ASSERT_EQ(relay_infos[1]->hop_count_, 0);
    ASSERT_EQ(relay_infos[1]->peeraddr_, IOAddress("2001:db8:1::1"));
    ASSERT_EQ(relay_infos[1]->linkaddr_, IOAddress("2001:db8:1::2"));

    // It should have no options.
    ASSERT_EQ(0, relay_infos[1]->options_.size());
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, oldMakeRelayOptionRelayInfo) {
    testOldMakeRelayOptionRelayInfo();
}

// This test verifies scenarios were the query is logically
// invalid and to which the server responds with a DHCPV6_LEASEQUERY_REPLY
// packet but with an other than successful status code option:
// - Unknown query type
// - query by ip address that's missing the D6O_IAADDR option
// - query by client id that's missing the D6O_CLIENTID option
TEST_F(MemfileLeaseQueryImpl6ProcessTest, processQueryInvalidWithStatus) {
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());

    // Structure that contains a test scenario.
    struct Scenario {
        const std::string description_;
        uint8_t qry_type_;
        IOAddress qry_iaaddr_;
        DuidPtr qry_cid_;
        DHCPv6StatusCode exp_status_code_;
        const std::string exp_message_;
    };

    // List of test scenarios to execute.
    std::vector<Scenario> scenarios {
        {
        "unknown query type",
        77,
        IOAddress::IPV6_ZERO_ADDRESS(),
        DuidPtr(),
        STATUS_UnknownQueryType,
        "unknown query-type"
        },
        {
        "missing iaaddr",
        LQ6QT_BY_ADDRESS,
        IOAddress::IPV6_ZERO_ADDRESS(),
        DuidPtr(),
        STATUS_MalformedQuery,
        "missing D6O_IAADDR"
        },
        {
        "missing client id",
        LQ6QT_BY_CLIENTID,
        IOAddress::IPV6_ZERO_ADDRESS(),
        DuidPtr(),
        STATUS_MalformedQuery,
        "missing D6O_CLIENTID"
        }
    };

    // Iterate over the scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Make the lease query.
        Pkt6Ptr lq = makeLeaseQuery(scenario.qry_type_, scenario.qry_iaaddr_,
                                    scenario.qry_cid_);
        // Process the query.
        ASSERT_NO_THROW_LOG(impl->processQuery(lq));

        // We should have generated a LEASE_QUERY_REPLY with a
        // status option containing the expected status.
        Pkt6Ptr rsp = getSentPacket();
        ASSERT_TRUE(rsp);
        ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
        checkStatus(rsp, scenario.exp_status_code_, scenario.exp_message_);

        // Should not have any options.
        EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

        // Make sure there are no left over packets.
        ASSERT_FALSE(getSentPacket());
    }
}

// This test verifies scenarios were a query by ip address is logically
// valid but for which no active leases exist and to which the server
// should respond with a DHCPV6_LEASEQUERY_REPLY packet with the
// appropriate status.
// - Lease is expired
// - Lease is declined
// - Lease is reclaimed
// - Lease address is known but no lease exists
// - Lease address is not known
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByIpAddressNoActiveLease() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());

    // Create some leases.
    Lease6Ptr active_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::120"),
                                      subnet2_, cid1_, time(0));

    Lease6Ptr expired_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::115"),
                                       subnet2_, cid1_, time(0) - 4000, "");

    Lease6Ptr declined_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::110"),
                                        subnet2_, cid1_, time(0), "",
                                        Lease::STATE_DECLINED);

    Lease6Ptr reclaimed_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::105"),
                                         subnet2_, cid1_, time(0), "",
                                         Lease::STATE_EXPIRED_RECLAIMED);

    // Structure that contains a test scenario.
    struct Scenario {
        const std::string description_;
        IOAddress qry_iaaddr_;
        DHCPv6StatusCode exp_status_code_;
        const std::string exp_message_;
    };

    // List of test scenarios to execute.
    std::vector<Scenario> scenarios {
        {
        "lease is expired",
        expired_lease->addr_,
        STATUS_Success,
        "inactive lease exists"
        },
        {
        "lease is declined",
        declined_lease->addr_,
        STATUS_Success,
        "inactive lease exists"
        },
        {
        "lease is reclaimed",
        reclaimed_lease->addr_,
        STATUS_Success,
        "inactive lease exists"
        },
        {
        "lease does not exist, but is in a pool",
        IOAddress("2001:db8:2::200"),
        STATUS_Success,
        "no active lease"
        },
        {
        "address is not in a configured pool",
        IOAddress("2001:db8:77::1"),
        STATUS_NotConfigured,
        "address not in a configured pool"
        }
    };

    // Iterate over the scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Make the lease query.
        Pkt6Ptr lq = makeQueryByIpAddress(scenario.qry_iaaddr_);

        // Process the query.
        ASSERT_NO_THROW_LOG(impl->processQuery(lq));

        // We should have generated a DHCPV6_LEASEQUERY_REPLY with a
        // status option containing the expected status.
        Pkt6Ptr rsp = getSentPacket();
        ASSERT_TRUE(rsp);
        ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
        checkStatus(rsp, scenario.exp_status_code_, scenario.exp_message_);

        // Should not have any options.
        EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

        // Make sure there are no left over packets.
        ASSERT_FALSE(getSentPacket());
    }
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByIpAddressNoActiveLease) {
    testQueryByIpAddressNoActiveLease();
}

// This test verifies that given a logically valid query by ip address
// for which an active lease exists the server responds with a
// DHCPV6_LEASEQUERY_REPLY packet with the proper content.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByIpAddressActiveLease() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr active_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::120"),
                                      subnet2_, cid1_, now - 100);

    Lease6Ptr expired_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::115"),
                                       subnet2_, cid1_, now - 4000, "");

    Lease6Ptr declined_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::110"),
                                        subnet2_, cid1_, now, "",
                                        Lease::STATE_DECLINED);

    Lease6Ptr reclaimed_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::105"),
                                         subnet2_, cid1_, now, "",
                                         Lease::STATE_EXPIRED_RECLAIMED);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByIpAddress(active_lease->addr_);

    // Process the query.
    ASSERT_NO_THROW_LOG(impl->processQuery(lq));

    // We should have generated a DHCPV6_LEASEQUERY_REPLY with a
    // status option containing the successful status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_Success, "active lease found");

    // Should not have either of these two options.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    OptionPtr opt;
    ASSERT_TRUE(opt = rsp->getOption(D6O_CLIENT_DATA));
    OptionCustomPtr data_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(data_option);

    auto options = data_option->getOptions();
    EXPECT_EQ(3, options.size());

    // Verify client id.
    auto opt_iter = options.find(D6O_CLIENTID);
    ASSERT_TRUE(opt_iter != options.end());
    opt = opt_iter->second;
    EXPECT_EQ(cid1_->getDuid(), opt->getData());

    // Verify CLTT, is take from the first lease in the list.
    opt_iter = options.find(D6O_CLT_TIME);
    ASSERT_TRUE(opt_iter != options.end());
    OptionUint32Ptr cltt_opt = boost::dynamic_pointer_cast<OptionUint32>
                              (opt_iter->second);
    EXPECT_NEAR(cltt_opt->getValue(), 100, 1);

    // Now let's check w should have one TYPE_NA lease.
    opt_iter = options.find(D6O_IAADDR);
    ASSERT_TRUE(opt_iter != options.end());

    Option6IAAddrPtr iaaddr_opt;
    iaaddr_opt = boost::dynamic_pointer_cast<Option6IAAddr>(opt_iter->second);
    ASSERT_TRUE(iaaddr_opt);
    EXPECT_EQ(active_lease->addr_, iaaddr_opt->getAddress());

    // Should not be any more options.
    ASSERT_TRUE((++opt_iter) != options.end());

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByIpAddressActiveLease) {
    testQueryByIpAddressActiveLease();
}

// This test verifies that given a logically valid query by client id
// for which no active leases exist the server responds with a
// DHCPV6_LEASEQUERY_REPLY packet with the proper content.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByClientIdNoActiveLease() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());

    // Create some leases.
    Lease6Ptr active_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                      subnet2_, cid2_, time(0));

    Lease6Ptr expired_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                                       subnet3_, cid1_, time(0) - 4000, "");

    Lease6Ptr declined_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                        subnet4_, cid1_, time(0), "",
                                        Lease::STATE_DECLINED);

    Lease6Ptr reclaimed_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::101"),
                                         subnet2_, cid1_, time(0), "",
                                         Lease::STATE_EXPIRED_RECLAIMED);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(impl->processQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_Success, "no active leases");

    // Should not have any options.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByClientIdNoActiveLease) {
    testQueryByClientIdNoActiveLease();
}

// This test verifies that given a logically valid query by client id
// for which active leases on multiple subnets exist, the server responds
// with a DHCPV6_LEASEQUERY_REPLY packet with the proper content.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByClientIdMultipleLinks() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                      subnet2_, cid1_, now - 300);

    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                                       subnet3_, cid1_, now - 100);

    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                        subnet4_, cid1_, now - 200);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(impl->processQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // Should not these two any options.
    EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Should have client link option.
    OptionPtr opt;
    ASSERT_TRUE(opt = rsp->getOption(D6O_LQ_CLIENT_LINK));
    Option6AddrLstPtr link_opt = boost::dynamic_pointer_cast<Option6AddrLst>(opt);
    ASSERT_TRUE(link_opt);

    // We should have the addresses for subnet2_, subnet3_, and subnet4_
    // in that order.
    Option6AddrLst::AddressContainer links = link_opt->getAddresses();
    ASSERT_EQ(3, links.size());
    EXPECT_EQ(subnet2_->get().first, links[0]);
    EXPECT_EQ(subnet3_->get().first, links[1]);
    EXPECT_EQ(subnet4_->get().first, links[2]);

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByClientIdMultipleLinks) {
    testQueryByClientIdMultipleLinks();
}

// This test verifies that given a logically valid query by client id
// for which active leases on the same subnet exist, the server responds
// with a DHCPV6_LEASEQUERY_REPLY packet with the proper content, including
// a D6O_LQ_RELAY_DATA option from the newest active lease.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByClientIdActiveLeases() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());
    time_t now = time(0);

    // JSON user-context content.
    std::string user_context =
    "{ \"ISC\": {"
    "   \"relay-info\": ["
    "       {"
    "           \"hop\": 1,"
    "           \"peer\": \"2001:db8:2::1\","
    "           \"link\": \"2001:db8:2::2\","
    "           \"options\": \"0x0012000465746830\""
    "       }]"
    "   }"
    "}";

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 4000);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::104"),
                                subnet4_, cid1_, now - 100, user_context);
    Lease6Ptr lease3 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                subnet4_, cid1_, now - 200);
    Lease6Ptr lease4 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:2::"),
                                subnet4_, cid1_, now - 4000);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(impl->processQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // Should not have a clink link option.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));

    // Should have client data option.
    OptionPtr opt;
    ASSERT_TRUE(opt = rsp->getOption(D6O_CLIENT_DATA));
    OptionCustomPtr data_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(data_option);

    // Client data option should have four sub options.
    auto options = data_option->getOptions();
    EXPECT_EQ(4, options.size());

    // Verify client id.
    auto opt_iter = options.find(D6O_CLIENTID);
    ASSERT_TRUE(opt_iter != options.end());
    opt = opt_iter->second;
    EXPECT_EQ(cid1_->getDuid(), opt->getData());

    // Verify that CLTT comes from lease2.
    opt_iter = options.find(D6O_CLT_TIME);
    ASSERT_TRUE(opt_iter != options.end());
    OptionUint32Ptr cltt_opt = boost::dynamic_pointer_cast<OptionUint32>
                              (opt_iter->second);
    // CLTT on the initial lease was set to 100 seconds ago, but one second could have ticked since
    // then, so allow one second of margin error.
    EXPECT_NEAR(cltt_opt->getValue(), 100, 1);

    // Now let's check we should have one TYPE_NA lease.
    opt_iter = options.find(D6O_IAADDR);
    ASSERT_TRUE(opt_iter != options.end());
    checkIAAddrOption(opt_iter->second, lease2, 100);

    // Now let's check we should have one TYPE_PD lease.
    opt_iter = options.find(D6O_IAPREFIX);
    ASSERT_TRUE(opt_iter != options.end());
    checkIAPrefixOption(opt_iter->second, lease3, 200);

    // We should have a relay option.
    opt = rsp->getOption(D6O_LQ_RELAY_DATA);
    ASSERT_TRUE(opt);
    OptionCustomPtr relay_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(relay_option);

    // Verify the peer address field. It should come from the outermost
    // relay.
    IOAddress peer_addr("::");
    ASSERT_NO_THROW_LOG(peer_addr = relay_option->readAddress(0));
    EXPECT_EQ(IOAddress("2001:db8:2::1"), peer_addr);

    // Verify the RELAY_FORW content.
    OptionBuffer relay_forw_data;
    ASSERT_NO_THROW_LOG(relay_forw_data = relay_option->readBinary(1));

    // First we unpack it.
    std::vector<RelayInfoPtr> relay_infos;
    ASSERT_NO_THROW_LOG(unpackRelayForwardMsg(relay_forw_data, relay_infos));

    // We should have two relays.
    EXPECT_EQ(1, relay_infos.size());

    // Verify the first instance.
    // Make sure the field contents are correct.
    ASSERT_EQ(relay_infos[0]->hop_count_, 1);
    ASSERT_EQ(relay_infos[0]->peeraddr_, IOAddress("2001:db8:2::1"));
    ASSERT_EQ(relay_infos[0]->linkaddr_, IOAddress("2001:db8:2::2"));

    // It should have one option.
    ASSERT_EQ(1, relay_infos[0]->options_.size());
    auto x = relay_infos[0]->options_.find(0x12);
    ASSERT_TRUE(x != relay_infos[0]->options_.end());
    ASSERT_EQ(std::string("type=00018, len=00004: 65:74:68:30 'eth0'"), x->second->toString());

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByClientIdActiveLeases) {
    testQueryByClientIdActiveLeases();
}

// Verifies that queryByClientId() correctly applies the link address
// value when matching leases.
// - Detect unknown link address
// - No filtering when the link address is ::
// - Include only a client's leases whose subnet matches the link addr (three scenarios)
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByClientIdLinkAddr() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                       subnet2_, cid1_, now - 300);

    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::101"),
                                       subnet2_, cid1_, now - 100);

    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                                       subnet3_, cid2_, now - 100);

    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                       subnet4_, cid1_, now - 200);

    Lease6Collection leases;
    Option6StatusCodePtr status;

    // With an unknown link address we should not configured status and no leases.
    leases.clear();
    ASSERT_NO_THROW_LOG(status = impl->queryByClientId(cid1_, IOAddress("3001::"), leases));
    checkStatus(status, STATUS_NotConfigured, "not a configured link");
    ASSERT_EQ(0, leases.size());

    // With no link address filter. We should get all three cid1_ leases
    // ordered by CLTT : lease2, lease4, lease1
    ASSERT_NO_THROW_LOG(status = impl->queryByClientId(cid1_, IOAddress("::"), leases));
    checkStatus(status, STATUS_Success, "active lease(s) found");
    ASSERT_EQ(3, leases.size());
    EXPECT_EQ(lease2->addr_, leases[0]->addr_);
    EXPECT_EQ(lease4->addr_, leases[1]->addr_);
    EXPECT_EQ(lease1->addr_, leases[2]->addr_);

    // With link address = subnet4. We should only get lease4 for cid1_
    leases.clear();
    ASSERT_NO_THROW_LOG(status = impl->queryByClientId(cid1_, IOAddress("2001:db8:4::"), leases));
    checkStatus(status, STATUS_Success, "active lease(s) found");
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ(lease4->addr_, leases[0]->addr_);

    // With link address filter = subnet3, we should no active lease for cid1_.
    leases.clear();
    ASSERT_NO_THROW_LOG(status = impl->queryByClientId(cid1_, IOAddress("2001:db8:3::"), leases));
    ASSERT_EQ(0, leases.size());
    checkStatus(status, STATUS_Success, "no active leases");

    // With link address filter = subnet3, we should get one active lease for cid2_.
    leases.clear();
    ASSERT_NO_THROW_LOG(status = impl->queryByClientId(cid2_, IOAddress("2001:db8:3::"), leases));
    checkStatus(status, STATUS_Success, "active lease(s) found");
    ASSERT_EQ(1, leases.size());
    EXPECT_EQ(lease3->addr_, leases[0]->addr_);
}

// This test exercises LeaseQueryImpl6::getPrefixFromAddress().
TEST_F(MemfileLeaseQueryImpl6ProcessTest, getPrefixFromAddress) {
    IOAddress src_addr("8001:db8:0134:dead:beef::0567");
    IOAddress prefix_addr("::");
    ASSERT_NO_THROW(prefix_addr = LeaseQueryImpl6::getPrefixFromAddress(src_addr, 64));
    EXPECT_EQ(IOAddress("8001:db8:0134:dead::"), prefix_addr);

    ASSERT_NO_THROW(prefix_addr = LeaseQueryImpl6::getPrefixFromAddress(src_addr, 70));
    EXPECT_EQ(IOAddress("8001:db8:0134:dead:bc00::"), prefix_addr);

    ASSERT_NO_THROW(prefix_addr = LeaseQueryImpl6::getPrefixFromAddress(src_addr, 128));
    EXPECT_EQ(IOAddress("8001:db8:0134:dead:beef::0567"), prefix_addr);

    prefix_addr = LeaseQueryImpl6::getPrefixFromAddress(src_addr, 1);
    EXPECT_EQ(IOAddress("8000::"), prefix_addr);

    ASSERT_THROW (LeaseQueryImpl6::getPrefixFromAddress(src_addr, 129), BadValue);
    ASSERT_THROW (LeaseQueryImpl6::getPrefixFromAddress(src_addr, 0), BadValue);
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByClientIdLinkAddr) {
    testQueryByClientIdLinkAddr();
}

// This test verifies searching for PD leases associated with a
// IP address and permutations of a list of prefix lengths to search.
template <typename TestLeaseMgrType> void
BaseLeaseQueryImpl6ProcessTest<TestLeaseMgrType>::testQueryByIpaddressPDLeases() {
    // Create our impl instance.
    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6());
    time_t now = time(0);

    // Create some PD leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_PD, IOAddress("3001:aabb:ccdd:eeff:1000::"),
                                subnet4_, cid1_, now - 200);
    Lease6Ptr lease2 = addLease(Lease::TYPE_PD, IOAddress("3001:aabb:ccdd:eeff:1f00::"),
                                subnet4_, cid1_, now - 200);
    Lease6Ptr lease3 = addLease(Lease::TYPE_PD, IOAddress("3001:aabb:ccdd:eeff:1d00::"),
                                subnet4_, cid1_, now - 4000);

    // Structure that contains a test scenario.
    struct Scenario {
        std::string desc_;
        IOAddress query_address_;
        std::list<uint8_t> prefix_lengths_;
        DHCPv6StatusCode expected_status_;
        std::string expected_msg_;
        Lease6Ptr expected_lease_;
    };

    // List of scenarios to test.
    std::list<Scenario> scenarios {
        {
            "No prefix lengths, no match",
            IOAddress("3001:aabb:ccdd:eeff:1f00::1"),
            {},
            STATUS_NotConfigured,
            "address not in a configured pool",
            Lease6Ptr()
        },
        {
            "Prefix too short to match",
            IOAddress("3001:aabb:ccdd:eeff:1f00::1"),
            {64},
            STATUS_NotConfigured,
            "address not in a configured pool",
            Lease6Ptr()
        },
        {
            "Should match active lease2",
            IOAddress("3001:aabb:ccdd:eeff:1f00::1"),
            {64, 72},
            STATUS_Success,
            "active lease found",
            lease2
        },
        {
            "Should be within PD pool 4, and return no active leases",
            IOAddress("3001::"),
            {64, 72},
            STATUS_Success,
            "no active lease",
            Lease6Ptr()
        },
        {
            "Should be outside all pools, and return not configured",
            IOAddress("3001:dead:beef::"),
            {64, 72},
            STATUS_NotConfigured,
            "address not in a configured pool",
            Lease6Ptr()
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.desc_);
        // Make the lease query.
        Pkt6Ptr lq = makeQueryByIpAddress(scenario.query_address_);

        impl->clearPrefixLengthList();
        for (auto const& plen : scenario.prefix_lengths_) {
            impl->addPrefixLength(plen);
        }

        // Process the query.
        ASSERT_NO_THROW_LOG(impl->processQuery(lq));

        // We should have generated a LEASE_QUERY_REPLY with a
        // status option containing the expected status.
        Pkt6Ptr rsp = getSentPacket();
        ASSERT_TRUE(rsp);
        ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
        checkStatus(rsp, scenario.expected_status_, scenario.expected_msg_);

        if (!scenario.expected_lease_) {
            // Should not have any options.
            EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
            EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
            EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));
        } else {
            // We should have D6O_CLIENT_DATA option.
            OptionPtr opt;
            ASSERT_TRUE(opt = rsp->getOption(D6O_CLIENT_DATA));
            OptionCustomPtr data_option = boost::dynamic_pointer_cast<OptionCustom>(opt);
            ASSERT_TRUE(data_option);

            auto options = data_option->getOptions();
            EXPECT_EQ(3, options.size());

            // Now let's check we should have one TYPE_PD lease.
            auto opt_iter = options.find(D6O_IAPREFIX);
            ASSERT_TRUE(opt_iter != options.end());
            checkIAPrefixOption(opt_iter->second, scenario.expected_lease_);
        }
    }
}

TEST_F(MemfileLeaseQueryImpl6ProcessTest, queryByIpaddressPDLeases) {
    testQueryByIpaddressPDLeases();
}

// Verifies prefix length list population over valid configuration
// permutations.
TEST_F(MemfileLeaseQueryImpl6ProcessTest, populatePrefixLengthList) {

    // Struct descibing each test scenario.
    struct Scenario {
        std::string desc_;            // text description
        std::string cfg_prefixes_;    // RHV for "prefix-length-list" if not empty
        size_t expected_start_size_;  // number of entries after LeaseQueryImpl6 is configured
        size_t expected_end_size_;    // number of entries after call to populatePrefixLenghtList()
        std::string expected_list_;   // expected contents of the prefix length list
    };

    // List of scenarios.
    std::list<Scenario> scenarios {
        {
            "No config entry, populate should build it",
            "",
            0, 2,
            "[ 72, 64 ]"
        },
        {
            "Empty list, should stay empty",
            "[ ]",
            0, 0,
            "[ ]"
        },
        {
            "Non-empty list, should remain intact",
            "[ 96 ]",
            1, 1,
            "[ 96 ]"
        }
    };

    // Iterate over the scenarios.
    for (auto const& scenario : scenarios) {
        // Create the impl.
        LeaseQueryImpl6Ptr impl;
        ASSERT_NO_THROW_LOG(impl = createLeaseQueryImpl6(scenario.cfg_prefixes_));

        // Verify the list after configuration.
        auto prefix_lengths = impl->getPrefixLengthList();
        ASSERT_EQ(scenario.expected_start_size_, prefix_lengths.size());

        // Verify the list after call to populatePrefixLengthList().
        impl->populatePrefixLengthList(CfgMgr::instance().getCurrentCfg());
        prefix_lengths = impl->getPrefixLengthList();
        ASSERT_EQ(scenario.expected_end_size_, prefix_lengths.size());
        EXPECT_EQ(scenario.expected_list_, impl->dumpPrefixLengthList(prefix_lengths));
    }
}

#ifdef HAVE_MYSQL
/// @brief MySQL test fixture.
class MySQLLeaseQueryImpl6ProcessTest : public
    BaseLeaseQueryImpl6ProcessTest<MySQLTestLeaseMgr> {
};

TEST_F(MySQLLeaseQueryImpl6ProcessTest, makeClientOptionMultipleLinks) {
    testMakeClientOptionMultipleLinks();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, makeClientOptionSingleLink) {
    testMakeClientOptionSingleLink();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, makeRelayOptionNoRelayInfo) {
        testMakeRelayOptionNoRelayInfo();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, makeRelayOptionRelayInfo) {
    testMakeRelayOptionRelayInfo();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, oldMakeRelayOptionRelayInfo) {
    testOldMakeRelayOptionRelayInfo();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, queryByIpAddressNoActiveLease) {
    testQueryByIpAddressNoActiveLease();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, queryByIpAddressActiveLease) {
    testQueryByIpAddressActiveLease();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, queryByClientIdNoActiveLease) {
    testQueryByClientIdNoActiveLease();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, queryByClientIdMultipleLinks) {
    testQueryByClientIdMultipleLinks();
}

TEST_F(MySQLLeaseQueryImpl6ProcessTest, queryByClientIdActiveLeases) {
    testQueryByClientIdActiveLeases();
}
#endif

#ifdef HAVE_PGSQL
/// @brief PostgreSQL test fixture.
class PgSQLLeaseQueryImpl6ProcessTest : public
    BaseLeaseQueryImpl6ProcessTest<PgSQLTestLeaseMgr> {
};

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, makeClientOptionMultipleLinks) {
    testMakeClientOptionMultipleLinks();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, makeClientOptionSingleLink) {
    testMakeClientOptionSingleLink();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, makeRelayOptionNoRelayInfo) {
        testMakeRelayOptionNoRelayInfo();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, makeRelayOptionRelayInfo) {
    testMakeRelayOptionRelayInfo();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, oldMakeRelayOptionRelayInfo) {
    testOldMakeRelayOptionRelayInfo();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, queryByIpAddressNoActiveLease) {
    testQueryByIpAddressNoActiveLease();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, queryByIpAddressActiveLease) {
    testQueryByIpAddressActiveLease();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, queryByClientIdNoActiveLease) {
    testQueryByClientIdNoActiveLease();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, queryByClientIdMultipleLinks) {
    testQueryByClientIdMultipleLinks();
}

TEST_F(PgSQLLeaseQueryImpl6ProcessTest, queryByClientIdActiveLeases) {
    testQueryByClientIdActiveLeases();
}
#endif

}
