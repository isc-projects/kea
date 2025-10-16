// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests LeaseQueryImpl4.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_int.h>
#include <dhcp/option_custom.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/pkt6.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <lease_query_impl4.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::lease_query;
using namespace isc::stats;
using namespace isc::util;

namespace {

class LeaseQueryImpl4ProcessTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Clears the configuration and unloads hook libraries.
    LeaseQueryImpl4ProcessTest()
     : ciaddr_empty_(IOAddress::IPV4_ZERO_ADDRESS()),
       hwaddr_empty_(new HWAddr(std::vector<uint8_t>{}, 0)),
       hwaddr1_(new HWAddr(std::vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x06 }, 1)),
       cid_empty_(),
       cid1_(new ClientId(std::vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x06 })) {
        CfgMgr::instance().clear();
    }

    /// @brief Destructor
    ///
    /// Clears the configuration and unloads hook libraries.
    virtual ~LeaseQueryImpl4ProcessTest() {
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
    }

    /// @brief  Prepares system managers for testing
    /// - Creates a new v4 Memfile lease manager
    /// - Creates the configuration.
    /// - Inits IfaceMgr with test config.
    void SetUp() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=4");

        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();

        // Build and add subnet2_.
        subnet2_.reset(new Subnet4(IOAddress("192.0.2.0"), 24, 1200, 2400, 3600, 2));
        Pool4Ptr pool(new Pool4(IOAddress("192.0.2.100"), IOAddress("192.0.2.200")));
        // Add server identifier to the pool.
        OptionCustomPtr server_id = makeServerIdOption(IOAddress("192.0.2.254"));
        CfgOptionPtr cfg_option = pool->getCfgOption();
        cfg_option->add(server_id, false, false, DHCP4_OPTION_SPACE);
        subnet2_->addPool(pool);

        // Add a second pool.
        pool.reset(new Pool4(IOAddress("192.0.2.201"), IOAddress("192.0.2.220")));
        subnet2_->addPool(pool);

        subnets->add(subnet2_);

        // Build and add subnet3_.
        Triplet<uint32_t> unspec;
        subnet3_.reset(new Subnet4(IOAddress("192.0.3.0"), 24, unspec, unspec, 3600, 3));
        pool.reset(new Pool4(IOAddress("192.0.3.100"), IOAddress("192.0.3.200")));
        subnet3_->addPool(pool);
        subnet3_->setT1Percent(0.5);
        subnet3_->setT2Percent(0.75);
        subnet3_->setCalculateTeeTimes(true);

        // Add server identifier.
        server_id = makeServerIdOption(IOAddress("192.0.3.254"));
        cfg_option = subnet3_->getCfgOption();
        cfg_option->add(server_id, false, false, DHCP4_OPTION_SPACE);

        subnets->add(subnet3_);

        // Build and add subnet4_.
        subnet4_.reset(new Subnet4(IOAddress("192.0.4.0"), 24, unspec, unspec, 3600, 4));
        pool.reset(new Pool4(IOAddress("192.0.4.100"), IOAddress("192.0.4.200")));
        subnet4_->addPool(pool);
        subnet4_->setCalculateTeeTimes(false);

        subnets->add(subnet4_);

        // Build and add subnet5_.
        subnet5_.reset(new Subnet4(IOAddress("192.0.5.0"), 24, unspec, unspec, 3600, 5));
        pool.reset(new Pool4(IOAddress("192.0.5.100"), IOAddress("192.0.5.200")));
        subnet5_->addPool(pool);
        subnet5_->setCalculateTeeTimes(false);

        subnets->add(subnet5_);

        CfgOptionPtr options(new CfgOption());
        OptionDescriptor desc(false, false);
        desc.option_ = makeServerIdOption(IOAddress("192.0.5.254"));
        options->add(desc, DHCP4_OPTION_SPACE);
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass("foo", ExpressionPtr(), "", true, false, options);
        subnet5_->addAdditionalClass("foo");

        // Build and add subnet6_.
        subnet6_.reset(new Subnet4(IOAddress("192.0.6.0"), 24, unspec, unspec, 3600, 6));
        pool.reset(new Pool4(IOAddress("192.0.6.100"), IOAddress("192.0.6.200")));
        subnet6_->addPool(pool);
        subnet6_->setCalculateTeeTimes(false);

        subnets->add(subnet6_);

        options.reset(new CfgOption());
        OptionDescriptor desc_other(false, false);
        desc_other.option_ = makeFqdnListOption();
        options->add(desc_other, DHCP4_OPTION_SPACE);
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass("bar", ExpressionPtr(), "", true, false, options);
        subnet6_->addAdditionalClass("bar");

        // Build and add subnet7_.
        subnet7_.reset(new Subnet4(IOAddress("192.0.7.0"), 24, unspec, unspec, 3600, 7));
        pool.reset(new Pool4(IOAddress("192.0.7.100"), IOAddress("192.0.7.200")));
        subnet7_->addPool(pool);
        subnet7_->setCalculateTeeTimes(false);

        subnets->add(subnet7_);

        options.reset();
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass("xyz", ExpressionPtr(), "", true, false, options);
        subnet7_->addAdditionalClass("xyz");

        // Build and add a shared-network.
        CfgSharedNetworks4Ptr networks = cfg_mgr.getStagingCfg()->getCfgSharedNetworks4();
        network1_.reset(new SharedNetwork4("one"));
        network1_->add(subnet4_);

        // Add server identifier.
        server_id = makeServerIdOption(IOAddress("192.0.4.254"));
        cfg_option = network1_->getCfgOption();
        cfg_option->add(server_id, false, false, DHCP4_OPTION_SPACE);

        networks->add(network1_);

        // Add a global server identifier.
        cfg_option = cfg_mgr.getStagingCfg()->getCfgOption();
        server_id = makeServerIdOption(IOAddress("10.0.0.254"));
        cfg_option->add(server_id, false, false, DHCP4_OPTION_SPACE);

        // Commit the config.
        cfg_mgr.commit();

        // Initialize interface mgr with test config.
        iface_config_.reset(new IfaceMgrTestConfig(true));
        IfaceMgr::instance().openSockets4();
    }

    /// @brief Adds a v4 lease to the lease store.
    ///
    /// @param addr ip address of the lease
    /// @param subnet  subnet to which the lease belongs
    /// @param hwaddr hardware address to associate with the lease
    /// @param client_id client identifier to associate with the lease
    /// @param cltt CLTT of the lease
    /// @param state lease state of the lease
    ///
    /// @return pointer to the new lease
    Lease4Ptr addLease(const IOAddress& addr, const Subnet4Ptr& subnet,
                       const HWAddrPtr& hwaddr, const ClientIdPtr& client_id,
                       time_t cltt, const std::string& json_context = "",
                       const uint32_t state = Lease::STATE_DEFAULT) {

        if (!subnet) {
            isc_throw(Unexpected, "subnet cannot be empty");
        }

        Lease4Ptr lease(new Lease4(addr, hwaddr, client_id, subnet->getValid(), cltt,
                                   subnet->getID()));
        lease->state_ = state;
        if (!json_context.empty()) {
            ElementPtr user_context;
            user_context = Element::fromJSON(json_context);
            lease->setContext(user_context);
        }

        LeaseMgrFactory::instance().addLease(lease);
        return (lease);
    }

    /// @brief Creates a DHCPLEASEQUERY packet
    ///
    /// There are no sanity checks to prevent specifying more than one
    /// of ciaddr, hwaddr, or cid.  This is deliberate as we may wish
    /// to create invalid query packets.
    ///
    /// @param giaddr ip address of the requester
    /// @param ciaddr ip address for which to query (if not 0.0.0.0)
    /// @param hwaddr hardware address for which to query (if not empty)
    /// @param cid client id for which to query (if not empty)
    ///
    /// @return DHCPLEASEQUERY packet
    Pkt4Ptr makeLeaseQuery(const IOAddress& giaddr, const IOAddress& ciaddr,
                           const HWAddrPtr& hwaddr, const ClientIdPtr& cid) const {
        Pkt4Ptr query(new Pkt4(DHCPLEASEQUERY, 123));
        query->setGiaddr(giaddr);
        query->setCiaddr(ciaddr);
        if (hwaddr) {
            query->setHWAddr(hwaddr);
        } else {
            query->setHWAddr(hwaddr_empty_);
        }

        if (cid) {
            OptionPtr opt(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                     cid->getClientId()));
            query->addOption(opt);
        }

        return (query);
    }

    /// @brief Creates a DHCPLEASEQUERY packet for query by ip address
    ///
    /// @param giaddr ip address of the requester
    /// @param ciaddr ip address for which to query (if not 0.0.0.0)
    ///
    /// @return DHCPLEASEQUERY packet
    Pkt4Ptr makeQueryByIpAddress(const IOAddress& giaddr,
                                 const IOAddress& ciaddr) const {
        return (makeLeaseQuery(giaddr, ciaddr, HWAddrPtr(), ClientIdPtr()));
    }

    /// @brief Creates a DHCPLEASEQUERY packet for query by hardware address
    ///
    /// @param giaddr ip address of the requester
    /// @param hwaddr hardware address for which to query (if not empty)
    ///
    /// @return DHCPLEASEQUERY packet
    Pkt4Ptr makeQueryByHWAddr(const IOAddress& giaddr,
                              const HWAddrPtr& hwaddr) const {
        return (makeLeaseQuery(giaddr, IOAddress::IPV4_ZERO_ADDRESS(),
                               hwaddr, ClientIdPtr()));
    }

    /// @brief Creates a DHCPLEASEQUERY packet for query by client id
    ///
    /// @param giaddr ip address of the requester
    /// @param cid client id for which to query (if not empty)
    ///
    /// @return DHCPLEASEQUERY packet
    Pkt4Ptr makeQueryByClientId(const IOAddress& giaddr,
                                const ClientIdPtr& cid) const {
        return (makeLeaseQuery(giaddr, IOAddress::IPV4_ZERO_ADDRESS(),
                               HWAddrPtr(), cid));
    }

    /// @brief Checks that a response does not contain an option
    /// @param response response to test
    /// @param code option code of the option which should not be present
    void checkNoOption(const Pkt4Ptr& response, uint16_t code) const {
        EXPECT_FALSE(response->getOption(code))
                     << "option: " << code << " should not be present";
    }

    /// @brief Checks that a response contains the expected value for
    /// an option containing a time sensitive value.  The value is
    /// is correct if it lies within a range.
    ///
    /// @param response response to test
    /// @param code option code of the expected option
    /// @param exp_value  value the option should have
    /// @param tol tolerance in seconds. Defaults to 2.  Actual values
    /// are correct if they fall within +/- tolerance of expected value.
    void checkTimeOption(const Pkt4Ptr& response, uint16_t code,
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
    void checkRelayAgentInfo(const Pkt4Ptr& response,
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

    /// @brief Verify associated-ip option is correct.
    ///
    /// @param response response to test
    /// @param exp_ips list of expected ip addresses
    /// If empty the option should not be present
    void checkAssociatedIpOpt(const Pkt4Ptr& response,
                              const Option4AddrLst::AddressContainer& exp_ips) {
        OptionPtr opt = response->getOption(DHO_ASSOCIATED_IP);
        if (exp_ips.empty()) {
            ASSERT_FALSE(opt) << "associated-ip should not be present";
            return;
        }

        ASSERT_TRUE(opt) << "associated-ip is missing";
        Option4AddrLstPtr assoc_ips = boost::dynamic_pointer_cast<Option4AddrLst>(opt);

        ASSERT_TRUE(assoc_ips) << "associated-ip is wrong type";
        Option4AddrLst::AddressContainer addrs = assoc_ips->getAddresses();
        ASSERT_EQ(exp_ips, addrs) << "associated-ip list does not match expected";
    }

    /// @brief Add user-context from JSON to the lease.
    ///
    /// @param lease lease to modify
    /// @param json JSON text of the user-context content desired.
    void setLeaseUserContext(Lease4Ptr& lease, const std::string& json) {
        ElementPtr user_context;
        ASSERT_NO_THROW_LOG(user_context = Element::fromJSON(json));
        lease->setContext(user_context);
    }

    /// @brief Calls LeaseQueryImpl4::addLeaseTimes() and verifies the results
    ///
    /// Creates lease based on parameters given. The new lease will use the given
    /// subnet's value for valid life time, and the current time for CLTT.
    /// It then creates response packet and calls addLeaseTimes().  Finally
    /// verifies options 51,92,59, and 58 for the expected (or not present) values.
    ///
    /// @param addr - address of the test lease
    /// @param subnet - subnet of the test lease
    /// @param hwaddr - hwaddr of the test lease
    /// @param cid - client id of the test lease
    /// @param elapsed - amount of time (in seconds) that have elapsed since
    /// the lease's CLTT.
    /// @param exp_t2 - expected value fo T2 (option 59)
    /// @param exp_t1 - expected value fo T2 (option 58)
    void addLeaseTimesTest(const IOAddress& addr, const Subnet4Ptr& subnet,
                          const HWAddrPtr& hwaddr, const ClientIdPtr& cid,
                          time_t elapsed, time_t exp_t2, time_t exp_t1) {
        time_t now = time(0);
        time_t cltt = now - elapsed;

        ASSERT_TRUE(subnet->inRange(addr)) << "address not in subnet";
        Lease4Ptr lease = addLease(addr, subnet, hwaddr, cid, cltt);

        // Make the lease.
        ASSERT_TRUE(lease) << "could not create lease";

        // Create a response.
        Pkt4Ptr response(new Pkt4(DHCPLEASEACTIVE, 123));

        // Call addLeaseTimes().
        LeaseQueryImpl4::addLeaseTimes(response, lease, subnet);

        // Verify life time is valid - elapsed.
        checkTimeOption(response, DHO_DHCP_LEASE_TIME, lease->valid_lft_ - elapsed);

        // Since lease->cltt = now - elapsed, LQ CLTT should = elapsed.
        checkTimeOption(response, DHO_CLIENT_LAST_TRANSACTION_TIME, elapsed);

        // Verify T2 is as expected or not present.
        if (exp_t2) {
            checkTimeOption(response, DHO_DHCP_REBINDING_TIME, exp_t2);
        } else {
            checkNoOption(response, DHO_DHCP_REBINDING_TIME);
        }

        // Verify T2 is as expected or not present.
        if (exp_t1) {
            checkTimeOption(response, DHO_DHCP_RENEWAL_TIME, exp_t1);
        } else {
            checkNoOption(response, DHO_DHCP_RENEWAL_TIME);
        }
    }

    /// @brief Convenience method for making a server identifier option instance.
    ///
    /// @param address IP address to add to the option
    ///
    /// @return Pointer to the newly constructed option.
    OptionCustomPtr makeServerIdOption(const IOAddress& address) {
        const OptionDefinition& option_def = LibDHCP::DHO_DHCP_SERVER_IDENTIFIER_DEF();
        OptionCustomPtr server_id(new OptionCustom(option_def, Option::V4));
        server_id->writeAddress(address);
        return (server_id);
    }

    /// @brief Convenience method for making a fqdn list option instance.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeFqdnListOption() {
        const OptionDefinition& def = LibDHCP::DHO_DOMAIN_SEARCH_DEF();

        // Prepare buffer holding an array of FQDNs.
        const uint8_t fqdn[] = {
            8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
            7, 101, 120, 97, 109, 112, 108, 101,      // "example"
            3, 99, 111, 109,                          // "com"
            0
        };

        // Initialize a vector with the FQDN data.
        std::vector<uint8_t> fqdn_buf(fqdn, fqdn + sizeof(fqdn));

        OptionPtr option = def.optionFactory(Option::V4, DHO_DOMAIN_SEARCH,
                                             fqdn_buf.begin(), fqdn_buf.end());

        return (option);
    }

    /// @brief Checks the value of the dhcp-server-identifier option in a packet
    ///
    /// @param packet packet to test
    /// @param expected_address IP address the packet's option should contain
    ///
    /// @return Pointer to the newly constructed option.
    void checkServerIdOption(const Pkt4Ptr& packet, const IOAddress& expected_address) {
        OptionPtr opt = packet->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        ASSERT_TRUE(opt) << "no server-id option";

        OptionCustomPtr server_id_opt = boost::dynamic_pointer_cast<OptionCustom>(opt);
        ASSERT_TRUE(server_id_opt) << "server-id option is not an instance of OptionCustom";

        EXPECT_EQ(expected_address, server_id_opt->readAddress());
    }

    /// @brief Tests an invocation of LeaseQueryImpl4::acceptServerId()
    ///
    /// @param client_server_id - dhcp-server-identifier option (54) to test
    /// @param expected_ret - expected return value of acceptServerId()
    /// @param client_class - if not empty, add client class to query
    void acceptServerIdTest(const OptionPtr& client_server_id, bool expected_ret,
                            string client_class = "") {
        // Make the query.
        IOAddress giaddr("192.0.2.1");
        IOAddress ciaddr("192.0.2.101");
        Pkt4Ptr query = makeQueryByIpAddress(giaddr, ciaddr);

        // Add the server-id option from the client, if one.
        if (client_server_id) {
            query->addOption(client_server_id);
        }

        // Add client class.
        if (!client_class.empty()) {
            query->addClass(client_class);
        }

        // Now call acceptServerId() and check the outcome.
        OptionPtr accepted_server_id;
        bool result = LeaseQueryImpl4::acceptServerId(query, accepted_server_id);
        ASSERT_EQ(expected_ret, result) << "acceptServerId() result is wrong";

        // If there was a client server-id it should be returned in accepted_server_id.
        if (!client_server_id) {
            ASSERT_FALSE(accepted_server_id);
        } else {
            ASSERT_TRUE(accepted_server_id);
            ASSERT_EQ(client_server_id, accepted_server_id);
        }
    }

    /// @brief Create test which verifies server identifier.
    ///
    /// @param expected_server_id expected server identifier
    /// @param query the query used to get associated client classes
    /// @param subnet the subnet used to get configured options
    /// @param lease_addr the address used to get subnet pool configured options
    void buildCfgOptionTest(IOAddress expected_server_id,
                            const Pkt4Ptr& query,
                            const Subnet4Ptr& subnet = Subnet4Ptr(),
                            IOAddress lease_addr = IOAddress::IPV4_ZERO_ADDRESS()) {
        Lease4Ptr lease;
        if (subnet) {
            ASSERT_TRUE(subnet->inPool(Lease::TYPE_V4, lease_addr)) << "address not in subnet";
            lease = addLease(lease_addr, subnet, HWAddrPtr(), ClientIdPtr(), time(0));
            ASSERT_TRUE(lease);
        }

        Pkt4Ptr response(new Pkt4(DHCPLEASEACTIVE, 123));
        CfgOptionList co_list;
        ASSERT_NO_THROW_LOG(LeaseQueryImpl4::buildCfgOptionList(co_list, query, lease, subnet));

        LeaseQueryImpl4::appendServerId(response, co_list);
        checkServerIdOption(response, expected_server_id);
    }

    /// @brief Convenience values.
    IOAddress ciaddr_empty_;
    HWAddrPtr hwaddr_empty_;
    HWAddrPtr hwaddr1_;
    ClientIdPtr cid_empty_;
    ClientIdPtr cid1_;
    Subnet4Ptr subnet2_;
    Subnet4Ptr subnet3_;
    Subnet4Ptr subnet4_;
    Subnet4Ptr subnet5_;
    Subnet4Ptr subnet6_;
    Subnet4Ptr subnet7_;
    SharedNetwork4Ptr network1_;

    // Test configuration for IfaceMgr.
    boost::shared_ptr<IfaceMgrTestConfig> iface_config_;
};

// Verifies that configuration errors are detected.
TEST(LeaseQueryImpl4Test, invalidConfig4) {

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
            "requesters entry not a v4 address",
            Element::fromJSON("{ \"requesters\" : [ \"2001:db8:1::\" ] }"),
            "'requesters' entry '2001:db8:1::' is invalid: not a IPv4 address"
        },
        {
            "requesters entry is a duplicate",
            Element::fromJSON("{ \"requesters\" : [ \"192.0.2.1\", \"192.0.2.1\" ] }"),
            "'requesters' entry '192.0.2.1' is invalid: address is already in the list"
        }
    };

    for (auto const& scenario : scenarios ) {
        SCOPED_TRACE(scenario.description_);
        LeaseQueryImpl4Ptr impl;
        ASSERT_THROW_MSG(impl.reset(new LeaseQueryImpl4(scenario.config_)),
                         BadValue, scenario.exp_msg_);
    }
}

// Verifies that valid v4 configuration parses and that requesters
// can be validated.
TEST(LeaseQueryImpl4Test, validConfig4) {
    // Create an implementation with two requesters.
    const std::string json = "{ \"requesters\" : [ \"192.0.2.1\", \"192.0.2.3\" ] }";
    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));

    LeaseQueryImpl4Ptr impl;
    ASSERT_NO_THROW_LOG(impl.reset(new LeaseQueryImpl4(config)));

    // Verify known and unknown requesters check correctly.
    EXPECT_FALSE(impl->isRequester(IOAddress("192.0.2.0")));
    EXPECT_TRUE(impl->isRequester(IOAddress("192.0.2.1")));
    EXPECT_FALSE(impl->isRequester(IOAddress("192.0.2.2")));
    EXPECT_TRUE(impl->isRequester(IOAddress("192.0.2.3")));

    // Make sure a test with a v6 address complains.
    ASSERT_THROW_MSG(impl->isRequester(IOAddress("2001:db8:1::")), BadValue,
                     "not a IPv4 address");
}

// Verifies the invalid combinations of query parameters (ciaddr, HWAddr,
// and client id) are detected.
TEST(LeaseQueryImpl4Test, processQueryInvalidQuery) {
    // Create an implementation with two requesters.
    const std::string json = "{ \"requesters\" : [ \"192.0.2.1\", \"192.0.2.3\" ] }";
    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));
    LeaseQueryImpl4Ptr impl;
    ASSERT_NO_THROW_LOG(impl.reset(new LeaseQueryImpl4(config)));

    // A v6 packet should get tossed.
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_LEASEQUERY, 0));
    bool invalid = false;
    bool sending = false;
    ASSERT_THROW_MSG(impl->processQuery(pkt6, invalid, sending), BadValue,
                     "LeaseQueryImpl4 query is not DHCPv4 packet");
    EXPECT_FALSE(invalid);
    EXPECT_FALSE(sending);

    // An empty giaddr should fail.
    Pkt4Ptr lq(new Pkt4(DHCPLEASEQUERY, 123));
    invalid = false;
    sending = false;
    ASSERT_THROW_MSG(impl->processQuery(lq, invalid, sending), BadValue,
                     "giaddr cannot be 0.0.0.0");
    EXPECT_TRUE(invalid);
    EXPECT_FALSE(sending);

    // Set the pkt4-admin-filtered stat to 0.
    StatsMgr::instance().setValue("pkt4-admin-filtered", static_cast<int64_t>(0));

    // An unknown giaddr should fail.
    lq->setGiaddr(IOAddress("192.0.2.2"));
    invalid = false;
    sending = false;
    ASSERT_THROW_MSG(impl->processQuery(lq, invalid, sending), BadValue,
                     "rejecting query from unauthorized requester: 192.0.2.2");
    EXPECT_TRUE(invalid);
    EXPECT_FALSE(sending);

    // Check the stat which was bumped by one.
    ObservationPtr stat = StatsMgr::instance().getObservation("pkt4-admin-filtered");
    ASSERT_TRUE(stat);
    EXPECT_EQ(1, stat->getInteger().first);

    // Now we'll iterate over all invalid combinations of ciaddr, HWAddr, client id.
    struct Scenario {
        const std::string description_;
        IOAddress ciaddr_;
        HWAddrPtr hwaddr_;
        OptionPtr client_id_;
        const std::string exp_message_;
    };

    // Convenience values for scenario matrix.
    IOAddress ciaddr_empty(IOAddress::IPV4_ZERO_ADDRESS());
    IOAddress ciaddr("192.0.2.100");

    HWAddrPtr hw_addr_empty(new HWAddr(std::vector<uint8_t>{}, 0));
    HWAddrPtr hw_addr(new HWAddr(std::vector<uint8_t>{ 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }, 1));

    OptionPtr client_id_empty;
    OptionPtr client_id (new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                    std::vector<uint8_t>{ 0x0l, 0x02, 0x03, 0x04 }));

    std::vector<Scenario> scenarios {
        {
            "000",
            ciaddr_empty, hw_addr_empty, client_id_empty,
            "malformed lease query: ciaddr: [0.0.0.0] HWAddr: [hwtype=0 ] Client id: []"
        },
        //  "001" ciaddr only is valid, skip it
        //  "010" hwaddr only is valid, skip it
        {
            "011",
            ciaddr_empty, hw_addr, client_id,
            "malformed lease query: ciaddr: [0.0.0.0] HWAddr:"
            " [hwtype=1 0a:0b:0c:0d:0e:0f] Client id: [00:02:03:04]"
        },
        //  "100" client_id only is valid, skip it
        {
            "101",
            ciaddr, hw_addr_empty, client_id,
            "malformed lease query: ciaddr: [192.0.2.100] HWAddr:"
            " [hwtype=0 ] Client id: [00:02:03:04]"
        },
        {
            "110",
            ciaddr, hw_addr, client_id_empty,
            "malformed lease query: ciaddr: [192.0.2.100] HWAddr:"
            " [hwtype=1 0a:0b:0c:0d:0e:0f] Client id: []"
        },
        {
            "111",
            ciaddr, hw_addr, client_id,
            "malformed lease query: ciaddr: [192.0.2.100] HWAddr:"
            " [hwtype=1 0a:0b:0c:0d:0e:0f] Client id: [00:02:03:04]"
        }
    };

    // Iterate over the invalid query parameter scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        lq.reset(new Pkt4(DHCPLEASEQUERY, 123));
        lq->setGiaddr(IOAddress("192.0.2.1"));
        lq->setCiaddr(scenario.ciaddr_);
        lq->setHWAddr(scenario.hwaddr_);
        if (scenario.client_id_) {
            lq->addOption(client_id);
        }

        invalid = false;
        sending = false;
        ASSERT_THROW_MSG(impl->processQuery(lq, invalid, sending), BadValue,
                         scenario.exp_message_);
        EXPECT_TRUE(invalid);
        EXPECT_FALSE(sending);
    }
}

// Verifies that LeaseQuery4Impl::winnowLeases() produces the expected results.
TEST(LeaseQueryImpl4Test, winnowLeases) {
    Lease4Collection  input_leases;
    Lease4Collection output_leases;
    Lease4Collection expected_leases;

    time_t cltt = time(0);
    Lease4Ptr active1(new Lease4(IOAddress("192.0.2.1"), HWAddrPtr(), ClientIdPtr(), 3600, cltt - 300, 0));
    Lease4Ptr active2(new Lease4(IOAddress("192.0.2.2"), HWAddrPtr(), ClientIdPtr(), 3600, cltt - 200, 0));
    Lease4Ptr active3(new Lease4(IOAddress("192.0.2.3"), HWAddrPtr(), ClientIdPtr(), 3600, cltt - 100, 0));
    Lease4Ptr declined(new Lease4(IOAddress("192.0.2.4"), HWAddrPtr(), ClientIdPtr(), 3600, cltt - 300, 0));
    declined->state_ = Lease::STATE_DECLINED;
    Lease4Ptr expired(new Lease4(IOAddress("192.0.2.5"), HWAddrPtr(), ClientIdPtr(), 3600, cltt - 4000, 0));
    Lease4Ptr reclaimed(new Lease4(IOAddress("192.0.2.6"), HWAddrPtr(), ClientIdPtr(), 3600, cltt - 300, 0));
    reclaimed->state_ = Lease::STATE_EXPIRED_RECLAIMED;

    // Verify that an empty list in produces an empty list out.
    output_leases = LeaseQueryImpl4::winnowLeases(input_leases);
    EXPECT_EQ(0, output_leases.size());

    // Verify that an list with only inactive leases
    // in produces an empty list out.
    input_leases.push_back(declined);
    input_leases.push_back(reclaimed);
    output_leases = LeaseQueryImpl4::winnowLeases(input_leases);
    EXPECT_EQ(0, output_leases.size());

    // Now let's make sure a mixed list gives us only
    // active leases and in the proper order.
    input_leases.clear();

    input_leases.push_back(active3);
    input_leases.push_back(declined);
    input_leases.push_back(expired);
    input_leases.push_back(active1);
    input_leases.push_back(reclaimed);
    input_leases.push_back(active2);

    expected_leases.push_back(active3);
    expected_leases.push_back(active2);
    expected_leases.push_back(active1);

    output_leases = LeaseQueryImpl4::winnowLeases(input_leases);
    EXPECT_EQ(expected_leases, output_leases);
}

// Exercises LeaseQueryImpl4::queryByIpAddress.
// - look for an known address with no lease
// - look for an known address with active lease
// - look for an known address with inactive lease
// - look for an out-of-subnet address
// - look for an out-of-pool address
TEST_F(LeaseQueryImpl4ProcessTest, queryByIpAddress) {
    Lease4Collection leases;
    DHCPMessageType ret_type;

    // Look for an known address with no lease.
    // We should return unassigned and an empty collection.
    IOAddress addr1("192.0.2.101");
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByIpAddress(addr1, leases));
    EXPECT_EQ(DHCPLEASEUNASSIGNED, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for an known address with active lease.
    // We should return active and the lease in the collection.
    Lease4Ptr lease = addLease(addr1, subnet2_, HWAddrPtr(), ClientIdPtr(), time(0));
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByIpAddress(addr1, leases));
    EXPECT_EQ(DHCPLEASEACTIVE, ret_type);
    ASSERT_EQ(1, leases.size());
    EXPECT_TRUE(*leases[0] == *lease);

    // Look for an known address with inactive lease
    // We should return unassigned and an empty lease collection
    IOAddress addr2("192.0.2.102");
    lease = addLease(addr2, subnet2_, HWAddrPtr(), ClientIdPtr(), time(0), "",
                     Lease::STATE_EXPIRED_RECLAIMED);
    leases.clear();
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByIpAddress(addr2, leases));
    EXPECT_EQ(DHCPLEASEUNASSIGNED, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for an known address with an expired active lease
    // We should return unassigned and an empty lease collection
    IOAddress addr3("192.0.2.103");
    lease = addLease(addr2, subnet2_, HWAddrPtr(), ClientIdPtr(), 100, "");
    leases.clear();
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByIpAddress(addr2, leases));
    EXPECT_EQ(DHCPLEASEUNASSIGNED, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for an out-of-subnet address.
    // We should return unknown and an empty collection.
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByIpAddress(IOAddress("192.0.9.101"), leases));
    EXPECT_EQ(DHCPLEASEUNKNOWN, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for an in-subnet but out-of-pool address.
    // We should return unknown and an empty collection.
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByIpAddress(IOAddress("192.0.3.99"), leases));
    EXPECT_EQ(DHCPLEASEUNKNOWN, ret_type);
    EXPECT_EQ(0, leases.size());
}

// Exercises LeaseQueryImpl4::queryByClientId().
// - look for a ClientId with no lease.
// - look for a ClientId with a inactive lease.
// - look for a ClientId with an active lease.
// - look for a ClientId with a more than one active lease.
TEST_F(LeaseQueryImpl4ProcessTest, queryByClientId) {
    Lease4Collection leases;
    DHCPMessageType ret_type;

    // Look for a ClientId with no lease.
    // We should return unknown and an empty collection.
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByClientId(cid1_, leases));
    EXPECT_EQ(DHCPLEASEUNKNOWN, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for a ClientId with a inactive lease.
    // We should return unknown and an empty lease collection.
    IOAddress addr1("192.0.2.101");
    Lease4Ptr lease1 = addLease(addr1, subnet2_, HWAddrPtr(), cid1_, 100, "",
                                Lease::STATE_EXPIRED_RECLAIMED);
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByClientId(cid1_, leases));
    EXPECT_EQ(DHCPLEASEUNKNOWN, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for a ClientId with an active lease.
    // We should return active with the lease in the collection.
    IOAddress addr2("192.0.2.102");
    Lease4Ptr lease2 = addLease(addr2, subnet2_, HWAddrPtr(), cid1_, time(0) - 50);
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByClientId(cid1_, leases));
    EXPECT_EQ(DHCPLEASEACTIVE, ret_type);
    ASSERT_EQ(1, leases.size());
    EXPECT_TRUE(*leases[0] == *lease2);

    // Look for a ClientId with more than one active lease.
    // We should return active with both leases in the collection, ordered by CLTT.
    IOAddress addr3("192.0.2.103");
    Lease4Ptr lease3 = addLease(addr3, subnet3_, HWAddrPtr(), cid1_, time(0) - 100);
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByClientId(cid1_, leases));
    EXPECT_EQ(DHCPLEASEACTIVE, ret_type);
    ASSERT_EQ(2, leases.size());
    EXPECT_TRUE(*leases[0] == *lease2);
    EXPECT_TRUE(*leases[1] == *lease3);
}

// Exercises LeaseQueryImpl4::queryByHWAddr().
// - look for a HWAddress with no lease.
// - look for a HWAddress with a inactive lease.
// - look for a HWAddress with an active lease.
// - look for a HWAddress with a more than one active lease.
TEST_F(LeaseQueryImpl4ProcessTest, queryByHWAddress) {
    Lease4Collection leases;
    DHCPMessageType ret_type;

    // Look for a HWAddress with no lease.
    // We should return unknown and an empty collection.
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByHWAddr(hwaddr1_, leases));
    EXPECT_EQ(DHCPLEASEUNKNOWN, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for a HWAddress with a inactive lease.
    // We should return unknown and an empty lease collection.
    IOAddress addr1("192.0.2.101");
    Lease4Ptr lease1 = addLease(addr1, subnet2_, hwaddr1_, ClientIdPtr(), 100, "",
                                Lease::STATE_EXPIRED_RECLAIMED);
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByHWAddr(hwaddr1_, leases));
    EXPECT_EQ(DHCPLEASEUNKNOWN, ret_type);
    EXPECT_EQ(0, leases.size());

    // Look for a HWAddress with an active lease.
    // We should return active with the lease in the collection.
    IOAddress addr2("192.0.2.102");
    Lease4Ptr lease2 = addLease(addr2, subnet2_, hwaddr1_, ClientIdPtr(), time(0) - 50);
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByHWAddr(hwaddr1_, leases));
    EXPECT_EQ(DHCPLEASEACTIVE, ret_type);
    ASSERT_EQ(1, leases.size());
    EXPECT_TRUE(*leases[0] == *lease2);

    // Look for a HWAddress with more than one active lease.
    // We should return active with both leases in the collection, ordered by CLTT.
    IOAddress addr3("192.0.2.103");
    Lease4Ptr lease3 = addLease(addr3, subnet3_, hwaddr1_, ClientIdPtr(), time(0) - 100);
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByHWAddr(hwaddr1_, leases));
    EXPECT_EQ(DHCPLEASEACTIVE, ret_type);
    ASSERT_EQ(2, leases.size());
    EXPECT_TRUE(*leases[0] == *lease2);
    EXPECT_TRUE(*leases[1] == *lease3);
}

// Verifies the content for a DHCPLEASEUNKNOWN response
// for query by ip address.
TEST_F(LeaseQueryImpl4ProcessTest, ipAddressBuildResponseUnknown) {
    // Make a query-by-ip-address.
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByIpAddress(IOAddress("192.0.2.1"),
                                                     IOAddress("192.0.4.1")));
    // Build a response for DHCPLEASEUNKNOWN.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEUNKNOWN, query,
                                                                  Lease4Collection()));
    // Verify type and giaddr.
    EXPECT_EQ(DHCPLEASEUNKNOWN, response->getType());
    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // Response ciaddr should be set to query ciaddr.
    EXPECT_EQ(query->getCiaddr(), response->getCiaddr());

    // Make sure hwaddr is empty.
    EXPECT_EQ(*hwaddr_empty_, *response->getHWAddr());

    //  Make sure there isn't a client option.
    EXPECT_FALSE(response->getOption(DHO_DHCP_CLIENT_IDENTIFIER));

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Verifies the content for a DHCPLEASEUNASSIGNED response
// for query by ip address.
TEST_F(LeaseQueryImpl4ProcessTest, ipAddressBuildResponseUnassigned) {
    // Make a query-by-ip-address.
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByIpAddress(IOAddress("192.0.2.1"),
                                                     IOAddress("192.0.4.1")));

    // Build a response for DHCPLEASEUNASSIGNED.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEUNASSIGNED, query,
                                                                  Lease4Collection()));
    EXPECT_EQ(DHCPLEASEUNASSIGNED, response->getType());

    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // Response ciaddr should match that from the query.
    EXPECT_EQ(query->getCiaddr(), response->getCiaddr());

    // Make sure hwaddr is empty.
    EXPECT_EQ(*response->getHWAddr(), *hwaddr_empty_);

    //  Make sure there isn't a client option.
    EXPECT_FALSE(response->getOption(DHO_DHCP_CLIENT_IDENTIFIER));

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Verifies the content for a DHCPLEASEUNKNOWN response
// for query by hardware address.
TEST_F(LeaseQueryImpl4ProcessTest, hwAddressBuildResponseUnknown) {
    // Make a query-by-hw-address.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>{0x01, 0x02, 0x03, 0x04, 0x04, 0x06},
                                HType::HTYPE_ETHER));
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByHWAddr(IOAddress("192.0.2.1"), hwaddr));

    // Build a response for DHCPLEASEUNKNOWN.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEUNKNOWN, query,
                                                                  Lease4Collection()));
    // Verify type and giaddr.
    EXPECT_EQ(DHCPLEASEUNKNOWN, response->getType());
    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // ciaddr should NOT be set.
    EXPECT_EQ(ciaddr_empty_, response->getCiaddr());

    // Response hwddr should match query hwaddr.
    EXPECT_EQ(*query->getHWAddr(), *response->getHWAddr());

    //  Make sure there isn't a client option.
    EXPECT_FALSE(response->getOption(DHO_DHCP_CLIENT_IDENTIFIER));

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Verifies the content for a DHCPLEASEUNASSIGNED response.
// for query by hardware address.
TEST_F(LeaseQueryImpl4ProcessTest, hwAddressBuildResponseUnassigned) {
    // Make a query-by-hw-address.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>{0x01, 0x02, 0x03, 0x04, 0x04, 0x06},
                                HType::HTYPE_ETHER));
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByHWAddr(IOAddress("192.0.2.1"), hwaddr));

    // Build a response for DHCPLEASEUNASSIGNED.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEUNASSIGNED, query,
                                                                  Lease4Collection()));
    EXPECT_EQ(DHCPLEASEUNASSIGNED, response->getType());

    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // ciaddr should NOT be set.
    EXPECT_EQ(ciaddr_empty_, response->getCiaddr());

    // Response hwddr should match query hwaddr.
    EXPECT_EQ(*query->getHWAddr(), *response->getHWAddr());

    //  Make sure there isn't a client option.
    EXPECT_FALSE(response->getOption(DHO_DHCP_CLIENT_IDENTIFIER));

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Verifies the content for a DHCPLEASEUNKNOWN response
// for query by client id.
TEST_F(LeaseQueryImpl4ProcessTest, clientIdBuildResponseUnknown) {
    // Make a query-by-client-id
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByClientId(IOAddress("192.0.2.1"), cid1_));

    // Build a response for DHCPLEASEUNKNOWN.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEUNKNOWN, query,
                                                                  Lease4Collection()));
    // Verify type and giaddr.
    EXPECT_EQ(DHCPLEASEUNKNOWN, response->getType());
    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // ciaddr should NOT be set.
    EXPECT_EQ(ciaddr_empty_, response->getCiaddr());

    // Make sure hwaddr is empty.
    EXPECT_EQ(*response->getHWAddr(), *hwaddr_empty_);

    // Client id should be present.
    OptionPtr opt = response->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    ASSERT_TRUE(opt);
    EXPECT_EQ(cid1_->getClientId(), opt->getData());

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Verifies the content for a DHCPLEASEUNASSIGNED response.
// for query by hardware address.
TEST_F(LeaseQueryImpl4ProcessTest, clientIdBuildResponseUnassigned) {
    // Make a query-by-client-id
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByClientId(IOAddress("192.0.2.1"), cid1_));

    // Build a response for DHCPLEASEUNASSIGNED.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEUNASSIGNED, query,
                                                                  Lease4Collection()));
    EXPECT_EQ(DHCPLEASEUNASSIGNED, response->getType());

    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // ciaddr should NOT be set.
    EXPECT_EQ(ciaddr_empty_, response->getCiaddr());

    // Make sure hwaddr is empty.
    EXPECT_EQ(*response->getHWAddr(), *hwaddr_empty_);

    // Client id should be present.
    OptionPtr opt = response->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    ASSERT_TRUE(opt);
    EXPECT_EQ(cid1_->getClientId(), opt->getData());

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Verifies that LeaseQueryImpl4::addLeaseTimes() adds
// lease time, T1, and T2 options correctly.
TEST_F(LeaseQueryImpl4ProcessTest, addLeaseTimes) {
    uint32_t elapsed;
    uint32_t exp_t2;
    uint32_t exp_t1;

    {
        SCOPED_TRACE("explicit when  elapsed < T1");
        elapsed = 60;
        // T2 should be subnet->T2 - elapsed
        // T1 should be subnet->T1 - elapsed
        exp_t2 = subnet2_->getT2() - elapsed;
        exp_t1 = subnet2_->getT1() - elapsed;
        addLeaseTimesTest(IOAddress("192.0.2.102"), subnet2_, hwaddr1_, cid1_,
                         elapsed, exp_t2, exp_t1);
    }

    {
        SCOPED_TRACE("explicit when elapsed > T2");
        // Neither timer should be present.
        elapsed = subnet2_->getT2() + 60;
        exp_t2 = 0;
        exp_t1 = 0;
        addLeaseTimesTest(IOAddress("192.0.2.102"), subnet2_, hwaddr1_, cid1_,
                         elapsed, exp_t2, exp_t1);
    }

    {
        SCOPED_TRACE("explicit when  T2 > elapsed > T1");
        // T2 should = subnet->T2 - elapsed.
        // T1 should not be present.
        elapsed = subnet2_->getT1() + 60;
        exp_t2 = subnet2_->getT2() - elapsed;
        exp_t1 = 0;
        addLeaseTimesTest(IOAddress("192.0.2.101"), subnet2_, hwaddr1_, cid1_,
                         elapsed, exp_t2, exp_t1);
    }

    {
        SCOPED_TRACE("calculated timers");
        // Should calculate T1 and T2 based on subnet3 percentages.
        time_t valid_lft = subnet3_->getValid();
        elapsed = 60;
        exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent()
                                                * valid_lft)) - elapsed;
        exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent()
                                             * valid_lft)) - elapsed;
        addLeaseTimesTest(IOAddress("192.0.3.101"), subnet3_, hwaddr1_, cid1_,
                         elapsed, exp_t2, exp_t1);
    }

    {
        SCOPED_TRACE("no timers");
        // When T1 and T2 are not specified and calculation is turned off
        // neither timer should be present.
        elapsed = 60;
        exp_t2 = 0;
        exp_t1 = 0;
        addLeaseTimesTest(IOAddress("192.0.4.101"), subnet4_, hwaddr1_, cid1_,
                         elapsed, exp_t2, exp_t1);
    }

    {
        SCOPED_TRACE("infinite life time");
        // When T1 and T2 are not specified and calculation is turned off
        // neither timer should be present.
        subnet4_->setValid(Lease::INFINITY_LFT);
        elapsed = 0;
        exp_t2 = 0;
        exp_t1 = 0;
        addLeaseTimesTest(IOAddress("192.0.4.102"), subnet4_, hwaddr1_, cid1_,
                         elapsed, exp_t2, exp_t1);
    }
}

// Verifies that LeaseQueryImpl4::addRelayAgentInfo()
// handles  relay-agent-info from the lease correctly.
TEST_F(LeaseQueryImpl4ProcessTest, addRelayAgentInfo) {
    Lease4Ptr lease;
    Pkt4Ptr response;

    {
    SCOPED_TRACE("no user context");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100);
    ASSERT_FALSE(lease->getContext());

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_NO_THROW_LOG(LeaseQueryImpl4::addRelayAgentInfo(response, lease));

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "");
    }

    {
    SCOPED_TRACE("no extended info");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100,
                              "{ \"foo\": 123 }");

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_NO_THROW_LOG(LeaseQueryImpl4::addRelayAgentInfo(response, lease));

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "");
    }

    {
    SCOPED_TRACE("no relay-agent-info");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100,
                               "{ \"ISC\": { \"foo\": 123 }}");

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_NO_THROW_LOG(LeaseQueryImpl4::addRelayAgentInfo(response, lease));

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "");
    }

    {
    SCOPED_TRACE("invalid relay-agent-info type");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100,
                     "{ \"ISC\": { \"relay-agent-info\": 123 }}");

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_THROW_MSG(LeaseQueryImpl4::addRelayAgentInfo(response, lease),
                     Unexpected, "Error creating relay-agent-info option:"
                     " stringValue() called on non-string Element in (<string>:1:32)");

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "");
    }

    {
    SCOPED_TRACE("invalid relay-agent-info content");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100,
                     "{ \"ISC\": { \"relay-agent-info\": \"foobar\" }}");

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_THROW_MSG(LeaseQueryImpl4::addRelayAgentInfo(response, lease),
                     Unexpected, "Error creating relay-agent-info option:"
                     " 'foobar' is not a valid string of hexadecimal digits");

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "");
    }

    {
    SCOPED_TRACE("valid old relay-agent-info");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100,
                     "{ \"ISC\": { \"relay-agent-info\": \"0x0104A1B1C1D1\" } }");

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_NO_THROW_LOG(LeaseQueryImpl4::addRelayAgentInfo(response, lease));

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "0x0104A1B1C1D1");
    }

    {
    SCOPED_TRACE("valid new relay-agent-info");
    response.reset(new Pkt4(DHCPLEASEACTIVE, 123));

    // Make the lease.
    lease = addLease(IOAddress("192.0.2.100"), subnet2_, hwaddr1_, cid1_, 100,
                     "{ \"ISC\": { \"relay-agent-info\": {"
                     " \"sub-options\": \"0x0104A1B1C1D1\" } } }");

    // Pass lease and response into addRelayAgentInfo().
    ASSERT_NO_THROW_LOG(LeaseQueryImpl4::addRelayAgentInfo(response, lease));

    // Verify relay-agent-info is not in the response
    checkRelayAgentInfo(response, "0x0104A1B1C1D1");
    }
}

TEST_F(LeaseQueryImpl4ProcessTest, addAssociatedLeases) {

    Lease4Collection input_leases;

    Lease4Ptr active1(new Lease4(IOAddress("192.0.2.1"), HWAddrPtr(), ClientIdPtr(), 0, 100, 0));
    Lease4Ptr active2(new Lease4(IOAddress("192.0.2.2"), HWAddrPtr(), ClientIdPtr(), 0, 200, 0));
    Lease4Ptr active3(new Lease4(IOAddress("192.0.2.3"), HWAddrPtr(), ClientIdPtr(), 0, 300, 0));

    {
    SCOPED_TRACE("empty lease list");
    Pkt4Ptr response(new Pkt4(DHCPLEASEACTIVE, 123));
    IOAddress active_ip("192.0.2.1");
    response->setCiaddr(active_ip);

    LeaseQueryImpl4::addAssociatedLeases(response, input_leases);
    checkNoOption(response, DHO_ASSOCIATED_IP);
    }

    {
    SCOPED_TRACE("active lease only");
    Pkt4Ptr response(new Pkt4(DHCPLEASEACTIVE, 123));
    IOAddress active_ip("192.0.2.1");
    response->setCiaddr(active_ip);

    input_leases.push_back(active1);
    LeaseQueryImpl4::addAssociatedLeases(response, input_leases);
    checkNoOption(response, DHO_ASSOCIATED_IP);
    }

    {
    SCOPED_TRACE("active lease plus others");
    Pkt4Ptr response(new Pkt4(DHCPLEASEACTIVE, 123));
    IOAddress active_ip("192.0.2.1");
    response->setCiaddr(active_ip);

    input_leases.push_back(active2);
    input_leases.push_back(active3);
    LeaseQueryImpl4::addAssociatedLeases(response, input_leases);

    Option4AddrLst::AddressContainer exp_ips = { active2->addr_, active3->addr_ };
    checkAssociatedIpOpt(response, exp_ips);
    }
}

// Verifies that buildResponseActive() correctly assembles
// a DHCPLEASEACTIVE response with all options present.
TEST_F(LeaseQueryImpl4ProcessTest, buildResponseActive) {
    Lease4Collection leases;
    time_t now = time(0);
    DHCPMessageType ret_type;

    // We create three active leases for the same client-id, one per subnet.
    IOAddress addr1("192.0.2.101");
    Lease4Ptr lease1 = addLease(addr1, subnet2_, HWAddrPtr(), cid1_, now - 100);

    IOAddress addr2("192.0.3.102");
    Lease4Ptr lease2 = addLease(addr2, subnet3_, hwaddr1_, cid1_, now,
                                "{ \"ISC\": { \"relay-agent-info\":"
                                " \"0104AABBCCDD\" }}");

    IOAddress addr3("192.0.4.103");
    Lease4Ptr lease3 = addLease(addr3, subnet4_, HWAddrPtr(), cid1_, now - 200);

    // Now create a DHCPLEASEQUERY packet for query by client id 1.
    Pkt4Ptr query;
    ASSERT_NO_THROW_LOG(query = makeQueryByClientId(IOAddress("192.0.2.1"), cid1_));

    // Submit the query.
    ASSERT_NO_THROW_LOG(ret_type = LeaseQueryImpl4::queryByClientId(cid1_, leases));
    EXPECT_EQ(DHCPLEASEACTIVE, ret_type);

    // We should have found three leases.  Lease2 should be first in the list.
    ASSERT_EQ(3, leases.size());
    ASSERT_EQ(lease2->addr_, leases[0]->addr_);

    // Build a response for DHCPLEASEACTIVE.
    Pkt4Ptr response;
    ASSERT_NO_THROW_LOG(response = LeaseQueryImpl4::buildResponse(DHCPLEASEACTIVE, query,
                                                                  leases));
    EXPECT_EQ(DHCPLEASEACTIVE, response->getType());

    // Verify the response content.

    // Response giaddr should match the query giaddr.
    EXPECT_EQ(query->getGiaddr(), response->getGiaddr());

    // Response ciaddr should match lease2 address.
    EXPECT_EQ(lease2->addr_, response->getCiaddr());

    // Response hwaddr should match lease1.
    EXPECT_EQ(*lease2->hwaddr_, *response->getHWAddr());

    // Client id should be present (unless we implement PRL requirement).
    OptionPtr opt = response->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    ASSERT_TRUE(opt);
    EXPECT_EQ(cid1_->getClientId(), opt->getData());

    // Verify lifetime, T1, and T2.  Subnet3 calculates timers.
    uint32_t exp_lft = lease2->valid_lft_;
    uint32_t exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent()
                                                  * (exp_lft)));
    uint32_t exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent()
                                                  * (exp_lft)));
    checkTimeOption(response, DHO_DHCP_LEASE_TIME, exp_lft);
    checkTimeOption(response, DHO_CLIENT_LAST_TRANSACTION_TIME, 0);
    checkTimeOption(response, DHO_DHCP_REBINDING_TIME, exp_t2);
    checkTimeOption(response, DHO_DHCP_RENEWAL_TIME, exp_t1);

    // Verify relay-agent-info is correct.
    checkRelayAgentInfo(response, "0x0104AABBCCDD");

    // Verify associated ip option.
    Option4AddrLst::AddressContainer exp_ips = { lease1->addr_, lease3->addr_ };
    checkAssociatedIpOpt(response, exp_ips);

    // Configured global server id should be present.
    checkServerIdOption(response, IOAddress("10.0.0.254"));
}

// Exercises LeaseQueryImpl4::acceptServerId.
TEST_F(LeaseQueryImpl4ProcessTest, acceptServerId) {

    {
        SCOPED_TRACE("no client server id");
        acceptServerIdTest(OptionPtr(), true);
    }

    {
        SCOPED_TRACE("wrong option type");
        OptionPtr server_id(new OptionInt<uint16_t>(Option::V4,
                                                    DHO_DHCP_SERVER_IDENTIFIER, 123));
        acceptServerIdTest(server_id, false);
    }

    {
        SCOPED_TRACE("No addresses");
        OptionPtr server_id(new Option(Option::V4, DHO_DHCP_SERVER_IDENTIFIER));
        acceptServerIdTest(server_id, false);
    }

    {
        SCOPED_TRACE("IPV4 Zero address");
        OptionPtr server_id = makeServerIdOption(IOAddress::IPV4_ZERO_ADDRESS());
        acceptServerIdTest(server_id, false);
    }

    {
        SCOPED_TRACE("Too many addresses");
        OptionCustomPtr server_id = makeServerIdOption(IOAddress("192.0.2.101"));
        // Add a second address.
        server_id->writeAddress(IOAddress("192.0.2.102"));
        acceptServerIdTest(server_id, false);
    }

    {
        SCOPED_TRACE("Valid value, no match");
        OptionPtr server_id = makeServerIdOption(IOAddress("192.0.1.1"));
        acceptServerIdTest(server_id, false);
    }

    {
        SCOPED_TRACE("Valid value, matches an interface");
        // We'll use an address from IfaceMgrTestConfig.
        OptionPtr server_id = makeServerIdOption(IOAddress("10.0.0.1"));
        acceptServerIdTest(server_id, true);
    }

    {
        SCOPED_TRACE("Valid value, matches a subnet");
        OptionPtr server_id = makeServerIdOption(subnet3_->getServerId());
        acceptServerIdTest(server_id, true);
    }

    {
        SCOPED_TRACE("Valid value, matches a shared-network");
        OptionPtr server_id = makeServerIdOption(network1_->getServerId());
        acceptServerIdTest(server_id, true);
    }

    {
        SCOPED_TRACE("Valid value, matches a client class");
        OptionCustomPtr server_id = makeServerIdOption(IOAddress("192.0.5.254"));
        acceptServerIdTest(server_id, true, "foo");
    }

    {
        SCOPED_TRACE("Valid value, matches a global value as client class does not define it");
        OptionCustomPtr server_id = makeServerIdOption(IOAddress("10.0.0.254"));
        acceptServerIdTest(server_id, true, "bar");
    }

    {
        SCOPED_TRACE("Valid value, matches a global value as client class does not define any option");
        OptionCustomPtr server_id = makeServerIdOption(IOAddress("10.0.0.254"));
        acceptServerIdTest(server_id, true, "xyz");
    }

    {
        SCOPED_TRACE("Valid value, matches a global");
        OptionCustomPtr server_id = makeServerIdOption(IOAddress("10.0.0.254"));
        acceptServerIdTest(server_id, true);
    }
}

// Exercises LeaseQueryImpl4::appendServerId().
TEST_F(LeaseQueryImpl4ProcessTest, appendServerId) {
    Pkt4Ptr response;
    OptionPtr resp_server_id;
    CfgOptionList co_list;

    {
        SCOPED_TRACE("Fallback to local address");
        response.reset(new Pkt4(DHCPLEASEUNKNOWN, 123));
        response->setLocalAddr(IOAddress("10.0.0.1"));

        LeaseQueryImpl4::appendServerId(response, co_list);
        checkServerIdOption(response, IOAddress("10.0.0.1"));
    }

    {
        SCOPED_TRACE("Response already has it");
        response.reset(new Pkt4(DHCPLEASEUNKNOWN, 123));
        response->setLocalAddr(IOAddress("10.0.0.1"));
        OptionPtr server_id = makeServerIdOption(IOAddress("10.0.0.2"));
        response->addOption(server_id);

        LeaseQueryImpl4::appendServerId(response, co_list);
        checkServerIdOption(response, IOAddress("10.0.0.2"));
    }

    {
        SCOPED_TRACE("Use configured value");
        response.reset(new Pkt4(DHCPLEASEUNKNOWN, 123));
        response->setLocalAddr(IOAddress("10.0.0.1"));

        co_list.push_back(CfgMgr::instance().getCurrentCfg()->getCfgOption());
        LeaseQueryImpl4::appendServerId(response, co_list);
        checkServerIdOption(response, IOAddress("10.0.0.254"));
    }
}

// Exercises LeaseQueryImpl4::buildCfgOptionList().
TEST_F(LeaseQueryImpl4ProcessTest, buildCfgOptionsList) {
    const Pkt4Ptr& query = boost::make_shared<Pkt4>(DHCPLEASEQUERY, 1234);

    {
        SCOPED_TRACE("Lease specified without subnet");
        CfgOptionList co_list;
        Lease4Ptr lease = addLease(IOAddress("192.0.2.130"), subnet2_,
                                   HWAddrPtr(), ClientIdPtr(), time(0));

        // Should throw when a lease is specified without a subnet.
        ASSERT_THROW_MSG(LeaseQueryImpl4::buildCfgOptionList(co_list, query, lease),
                         Unexpected, "buildCfgOptionList: subnet must be provided with lease");
    }

    {
        SCOPED_TRACE("Global only");
        // Server id should come from global options.
        buildCfgOptionTest(IOAddress("10.0.0.254"), query);
    }

    {
        SCOPED_TRACE("Pool value");
        // Server id should come from subnet2's first pool.
        buildCfgOptionTest(IOAddress("192.0.2.254"), query, subnet2_, IOAddress("192.0.2.100"));
    }

    {
        SCOPED_TRACE("Subnet value");
        // Server id should come from subnet3.
        buildCfgOptionTest(IOAddress("192.0.3.254"), query, subnet3_, IOAddress("192.0.3.100"));
    }

    {
        SCOPED_TRACE("Shared-network value");
        // Server id should come from subnet4's shared-network.
        buildCfgOptionTest(IOAddress("192.0.4.254"), query, subnet4_, IOAddress("192.0.4.100"));
    }

    {
        SCOPED_TRACE("Client-class value");
        // Server id should come from subnet5's client-class value.
        const Pkt4Ptr& query_with_classes = boost::make_shared<Pkt4>(DHCPLEASEQUERY, 1234);
        query_with_classes->addClass("foo");
        buildCfgOptionTest(IOAddress("192.0.5.254"), query_with_classes, subnet5_, IOAddress("192.0.5.100"));
    }

    {
        SCOPED_TRACE("Global value if client class does not define it");
        // Server id should be global value as subnet6's client-class does not define it.
        const Pkt4Ptr& query_with_classes = boost::make_shared<Pkt4>(DHCPLEASEQUERY, 1234);
        query_with_classes->addClass("bar");
        buildCfgOptionTest(IOAddress("10.0.0.254"), query_with_classes, subnet6_, IOAddress("192.0.6.100"));
    }

    {
        SCOPED_TRACE("Global value if client class does not define any option");
        // Server id should be global value as subnet7's client-class does not define any option.
        const Pkt4Ptr& query_with_classes = boost::make_shared<Pkt4>(DHCPLEASEQUERY, 1234);
        query_with_classes->addClass("xyz");
        buildCfgOptionTest(IOAddress("10.0.0.254"), query_with_classes, subnet7_, IOAddress("192.0.7.100"));
    }

    {
        SCOPED_TRACE("Global value");
        // Server id should be global value as lease is from subnet2's second pool.
        buildCfgOptionTest(IOAddress("10.0.0.254"), query, subnet2_, IOAddress("192.0.2.201"));
    }
}

} // end of anonymous namespace
