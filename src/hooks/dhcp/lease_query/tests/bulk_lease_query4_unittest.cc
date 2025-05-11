// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests DHCPv6 Bulk Lease Queries.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option_int.h>
#include <dhcp/option_custom.h>
#include <dhcp/pkt4.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <bulk_lease_query4.h>
#include <blq_service.h>
#include <lease_query_impl4.h>
#include <testutils/gtest_utils.h>
#include <test_lease_mgr.h>

#include <gtest/gtest.h>
#include <list>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::lease_query;
using namespace isc::util;

namespace ph = std::placeholders;

namespace {

/// @brief Text fixture for testing LeaseQueryImpl4
template <typename TestLeaseMgrType>
class BaseBulkLeaseQuery4ProcessTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Clears the configuration and unloads hook libraries.
    BaseBulkLeaseQuery4ProcessTest()
        : hwaddr_empty_(new HWAddr(std::vector<uint8_t>{}, 0)),
          hwaddr1_(new HWAddr(std::vector<uint8_t>{ 1, 2, 3, 4, 5, 6 }, 1)),
          hwaddr2_(new HWAddr(std::vector<uint8_t>{ 2, 3, 4, 5, 6, 7 }, 1)),
          cid_empty_(),
          cid1_(new ClientId(vector<uint8_t>{ 1, 2, 3, 4, 5, 6 })),
          cid2_(new ClientId(vector<uint8_t>{ 2, 3, 4, 5, 6, 7 })),
          id1_(vector<uint8_t>{ 0xaa, 0xbb, 0xcc }),
          id2_(vector<uint8_t>{ 1, 2, 3, 4}) {
        CfgMgr::instance().clear();
    }

    /// @brief Destructor
    ///
    /// Clears the configuration and unloads hook libraries.
    virtual ~BaseBulkLeaseQuery4ProcessTest() {
        BulkLeaseQueryService::reset();
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.destroySchema();
        if (test_timer_) {
            test_timer_->cancel();
        }
        if (io_service_) {
            io_service_->stopAndPoll();
        }
    }

    /// @brief Sets the DHCP multi-threading configuration in staging SrvConfig.
    ///
    /// @param enable_multi_threading value that maps to enable-multi-threading.
    /// @param thread_pool_size value that maps to thread-pool-size.
    /// @param queue_size value that maps to queue-size.
    void setDHCPMultiThreadingConfig(bool enabled, uint32_t thread_pool_size,
                                     uint32_t packet_queue_size) {
        MultiThreadingMgr::instance().setMode(enabled);
        ElementPtr mt_config = Element::createMap();
        mt_config->set("enable-multi-threading", Element::create(enabled));
        mt_config->set("thread-pool-size",
                       Element::create(static_cast<int>(thread_pool_size)));
        mt_config->set("queue-size",
                       Element::create(static_cast<int>(packet_queue_size)));
        CfgMgr::instance().getStagingCfg()->setDHCPMultiThreading(mt_config);
    }

    /// @brief Prepares system managers for testing
    /// - Creates a new v4 lease manager
    /// - Creates the configuration.
    void SetUp() {
        LeaseMgrFactory::destroy();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.createSchema();
        LeaseMgrFactory::create(test_lease_mgr.dbAccess());

        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();

        // Build and add subnet2_.
        subnet2_.reset(new Subnet4(IOAddress("192.0.2.0"), 24,
                                   1200, 2400, 3600, 2));

        Pool4Ptr pool(new Pool4(IOAddress("192.0.2.100"),
                                IOAddress("192.0.2.200")));
        subnet2_->addPool(pool);

        // Add a second pool.
        pool.reset(new Pool4(IOAddress("192.0.2.201"),
                             IOAddress("192.0.2.220")));
        subnet2_->addPool(pool);
        subnets->add(subnet2_);

        // Build and add subnet3_.
        Triplet<uint32_t> unspec;
        subnet3_.reset(new Subnet4(IOAddress("192.0.3.0"), 24,
                                   unspec, unspec, 3600, 3));

        pool.reset(new Pool4(IOAddress("192.0.3.100"),
                             IOAddress("192.0.3.200")));

        subnet3_->addPool(pool);
        subnet3_->setT1Percent(0.5);
        subnet3_->setT2Percent(0.75);
        subnet3_->setCalculateTeeTimes(true);
        subnets->add(subnet3_);

        // Build and add subnet4_.
        subnet4_.reset(new Subnet4(IOAddress("192.0.4.0"), 24,
                                   unspec, unspec, 3600, 4));

        pool.reset(new Pool4(IOAddress("192.0.4.100"),
                             IOAddress("192.0.4.200")));

        subnet4_->addPool(pool);
        subnet4_->setCalculateTeeTimes(false);
        subnets->add(subnet4_);

        // Build and add a shared-network.
        CfgSharedNetworks4Ptr networks = cfg_mgr.getStagingCfg()->getCfgSharedNetworks4();
        network1_.reset(new SharedNetwork4("one"));
        network1_->add(subnet4_);
        networks->add(network1_);

        // Commit the config.
        cfg_mgr.commit();

        // Create I/O service.
        io_service_.reset(new IOService());

        // Enable Kea core MT. We set it here as code checks staging not current.
        setDHCPMultiThreadingConfig(true, 4, 16);
    }

    /// @brief Create the Multi-Threaded Lease Query Listener Manager.
    ///
    /// @param page_size Maximum size of the page returned.
    void createBulkLeaseQueryService(size_t page_size = 10) {
        ElementPtr cfg = Element::createMap();
        ElementPtr advanced = Element::createMap();
        cfg->set("requesters", Element::fromJSON("[ \"127.0.0.1\" ]"));
        cfg->set("advanced", advanced);
        advanced->set("max-leases-per-fetch",
                      Element::create(static_cast<long long>(page_size)));
        ASSERT_NO_THROW(impl_.reset(new LeaseQueryImpl4(cfg)));
        EXPECT_TRUE(BulkLeaseQueryService::instance());
    }

    /// @brief Adds a v4 lease to the lease store.
    ///
    /// @param addr ip address of the lease
    /// @param subnet subnet to which the lease belongs
    /// @param hwaddr hardware addresss
    /// @param client_id duid of the lease owner
    /// @param cltt CLTT of the lease
    /// @param json_context user context of the lease as JSON
    /// @param state lease state of the lease
    ///
    /// @return pointer to the new lease
    Lease4Ptr addLease(const IOAddress& addr, const Subnet4Ptr& subnet,
                       const HWAddrPtr& hwaddr, const ClientIdPtr& client_id,
                       time_t cltt, const string& json_context = "",
                       const uint32_t state = Lease::STATE_DEFAULT) {
        if (!subnet) {
            isc_throw(Unexpected, "subnet cannot be empty");
        }

        Lease4Ptr lease(new Lease4(addr, hwaddr, client_id,
                                   subnet->getValid(), cltt, subnet->getID()));
        lease->state_ = state;
        if (!json_context.empty()) {
            ElementPtr user_context;
            user_context = Element::fromJSON(json_context);
            lease->setContext(user_context);
            LeaseMgr::extractLease4ExtendedInfo(lease, false);
        }

        LeaseMgrFactory::instance().addLease(lease);
        return (lease);
    }

    /// @brief Creates a DHCPBULKLEASEQUERY packet.
    ///
    /// @return DHCPBULKLEASEQUERY packet.
    Pkt4Ptr makeLeaseQuery() const {
        Pkt4Ptr query(new Pkt4(DHCPBULKLEASEQUERY, 123));
        query->setHWAddr(hwaddr_empty_);
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

    /// @brief Fetches a packet from the sent packet list.
    ///
    /// @return The packet de-queued.
    Pkt4Ptr getSentPacket() {
        Pkt4Ptr sent_packet;
        {
            lock_guard<mutex> lck(sent_packets_mutex_);
            if (!sent_packets_.empty()) {
                sent_packet = sent_packets_.front();
                sent_packets_.pop_front();
            }
        }

        return (sent_packet);
    }

    /// @brief Flushes any packets in the sent packet queue.
    void flushSentPackets() {
        lock_guard<mutex> lck(sent_packets_mutex_);
        sent_packets_.clear();
    }

    /// @brief Queue to hold any packets sent by BulkLeaseQuery4 instances.
    list<Pkt4Ptr> sent_packets_;

    /// @brief Mutex to protect the sent packet queue.
    std::mutex sent_packets_mutex_;

    /// @brief Convenience values.
    HWAddrPtr hwaddr_empty_;
    HWAddrPtr hwaddr1_;
    HWAddrPtr hwaddr2_;
    ClientIdPtr cid_empty_;
    ClientIdPtr cid1_;
    ClientIdPtr cid2_;
    vector<uint8_t> id1_;
    vector<uint8_t> id2_;
    Subnet4Ptr subnet2_;
    Subnet4Ptr subnet3_;
    Subnet4Ptr subnet4_;
    SharedNetwork4Ptr network1_;

    static string user_context_;
    static string user_context1_;
    static string user_context2_;

    IOServicePtr io_service_;
    IntervalTimerPtr test_timer_;
    LeaseQueryImplPtr impl_;
    BulkLeaseQuery4Ptr bulk_lease_query_;

    /// @note Factored test parts: to share.

    /// @brief Timeout handler.
    static void TimeoutHandler() {
        isc_throw(Unexpected, "test timeouts");
    }

    /// @brief The post method.
    ///
    /// @param cont The continuation to post.
    void post(const BlqPostCbArg& cont) {
        ASSERT_TRUE(io_service_);
        io_service_->post(cont);
    }

    /// @brief The post callback.
    BlqPostCb post_cb_ =
        std::bind(&BaseBulkLeaseQuery4ProcessTest::post, this, ph::_1);

    /// @brief The pushToSend method.
    ///
    /// @param response The response.
    /// @return Always true.
    bool pushToSend(BlqResponsePtr response) {
        Pkt4Ptr resp =
            boost::dynamic_pointer_cast<Pkt4>(response->getResponse());
        if (!resp) {
            isc_throw(Unexpected, "response is null or not v4");
        }
        lock_guard<mutex> lck(sent_packets_mutex_);
        sent_packets_.push_back(resp);
        return (true);
    }

    /// @brief The pushToSend callback.
    BlqPushToSendCb push_to_send_cb_ =
        std::bind(&BaseBulkLeaseQuery4ProcessTest::pushToSend, this, ph::_1);

    /// @brief The queryComplete method.
    ///
    /// @param xid The transaction id (ignored).
    void queryComplete(Xid) {
        ASSERT_TRUE(io_service_);
        io_service_->stop();
    }

    /// @brief The queryComplete callback.
    BlqQueryCompleteCb query_complete_cb_ =
        std::bind(&BaseBulkLeaseQuery4ProcessTest::queryComplete, this, ph::_1);

    /// @brief Initialize BulkLeaseQuery4.
    ///
    /// @param query The query.
    void initBulkQuery(PktPtr query) {
        ASSERT_TRUE(query);
        BlqQueryPtr blq_query(new BlqQuery(query));
        bulk_lease_query_.reset(new BulkLeaseQuery4(blq_query,
                                                    post_cb_,
                                                    push_to_send_cb_,
                                                    query_complete_cb_));
    }

    /// @brief Process a single bulk query.
    ///
    /// @param query The query.
    void processBulkQuery(Pkt4Ptr query) {
        // Init BulkLeaseQuery4.
        initBulkQuery(query);
        ASSERT_TRUE(bulk_lease_query_);

        // Check for early errors.
        if (bulk_lease_query_->isProcessed()) {
            return;
        }

        // Setup test processing environment.
        test_timer_.reset(new IntervalTimer(io_service_));
        test_timer_->setup(TimeoutHandler, 2000, IntervalTimer::ONE_SHOT);

        // Start processing.
        bulk_lease_query_->start();

        // Wait for completion.
        try {
            if (!io_service_->stopped()) {
                io_service_->run();
            }
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "run failed with " << ex.what();
        }

        // Clear test processing environment.
        test_timer_->cancel();
        io_service_->stopAndPoll();
        test_timer_.reset();
        io_service_.reset();
    }

    /// @brief Verify client id.
    ///
    /// @param cid Expected client id.
    /// @param pkt Pakcet where to find the client id option.
    void verifyClientId(ClientIdPtr cid, const PktPtr& pkt) {
        ASSERT_TRUE(cid);
        OptionPtr opt = pkt->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        ASSERT_TRUE(opt) << "can't find DHO_DHCP_CLIENT_IDENTIFIER";
        EXPECT_EQ(cid->getClientId(), opt->getData());
    }

    /// @brief Verify hardware address.
    ///
    /// @param hwaddr Expected hardware address.
    /// @param pkt Packet where to find the hardware address.
    void verifyHWaddr(HWAddrPtr hwaddr, Pkt4Ptr pkt) {
        ASSERT_TRUE(hwaddr);
        ASSERT_TRUE(pkt);
        HWAddrPtr hw = pkt->getHWAddr();
        ASSERT_TRUE(hw);
        EXPECT_EQ(hwaddr->toText(false), hw->toText(false));
    }

    /// @brief Verify by client id.
    void verifyByClientId();

    /// @brief Veify by hardware address.
    void verifyByHWAddr();

    /// @brief Verify by relay id.
    ///
    /// @param page_size Maximum size of returned pages.
    void verifyByRelayId(size_t page_size);

    /// @brief Verify by remote id.
    ///
    /// @param page_size Maximum size of returned pages.
    void verifyByRemoteId(size_t page_size);
};

template <typename TestLeaseMgrType> string
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::user_context_ =
    "{ \"ISC\": {"
    "   \"relay-agent-info\": {"
    "       \"sub-options\": \"0x0104A1B1C1D1\""
    "   } } }";

template <typename TestLeaseMgrType> string
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::user_context1_ =
    "{ \"ISC\": {"
    "   \"relay-agent-info\": {"
    "       \"relay-id\": \"AABBCC\","
    "       \"remote-id\": \"01020304\","
    "       \"sub-options\": \"0204010203040C03AABBCC\""
    "   } } }";

template <typename TestLeaseMgrType> string
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::user_context2_ =
    "{ \"ISC\": {"
    "   \"relay-agent-info\": {"
    "       \"relay-id\": \"01020304\","
    "       \"remote-id\": \"AABBCC\","
    "       \"sub-options\": \"0203AABBCC0C0401020304\""
    "   } } }";

// Verifies that configuration errors are detected.
TEST(BulkLeaseQuery4Test, invalidConfig4) {
    struct Scenario {
        const string description_;
        const string config_;
        const string exp_msg_;
    };

    vector<Scenario> scenarios = {
        {
            "unknown keyword",
            "{ \"foo\": 1 }",
            "spurious 'foo' parameter"
        },
        {
            "bulk-query-enabled not a boolean",
            "{ \"bulk-query-enabled\": 1 }",
            "'bulk-query-enabled' parameter is not a boolean"
        },
        {
            "active-query-enabled not a boolean",
            "{ \"active-query-enabled\": \"on\" }",
            "'active-query-enabled' parameter is not a boolean"
        },
        {
            "active-query-enabled not supported",
            "{ \"active-query-enabled\": true }",
            "Active query is not supported"
        },
        {
            "extended-info-tables-enabled not a boolean",
            "{ \"extended-info-tables-enabled\": 0}",
            "'extended-info-tables-enabled' parameter is not a boolean"
        },
        {
            "lease-query-ip not a string",
            "{ \"lease-query-ip\": 1 }",
            "'lease-query-ip' parameter is not a string"
        },
        {
            "lease-query-ip bad address",
            "{ \"lease-query-ip\": \"1:2\" }",
            "invalid lease-query-ip '1:2': Failed to convert string to"
            " address '1:2': Invalid argument"
        },
        {
            "lease-query-ip IPv6",
            "{ \"lease-query-ip\": \"::1\" }",
            "lease-query-ip not a IPv4 address"
        },
        {
            "lease-query-tcp-port not an integer",
            "{ \"lease-query-tcp-port\": true }",
            "'lease-query-tcp-port' parameter is not an integer"
        },
        {
            "lease-query-tcp-port is 0",
            "{ \"lease-query-tcp-port\": 0 }",
            "invalid lease-query-tcp-port '0'"
        },
        {
            "lease-query-tcp-port is 65536",
            "{ \"lease-query-tcp-port\": 65536 }",
            "invalid lease-query-tcp-port '65536'"
        },
        {
            "max-bulk-query-threads not an integer",
            "{ \"max-bulk-query-threads\": false }",
            "'max-bulk-query-threads' parameter is not an integer"
        },
        {
            "max-bulk-query-threads -1",
            "{ \"max-bulk-query-threads\": -1 }",
            "invalid max-bulk-query-threads '-1'"
        },
        {
            "max-requester-connections not an integer",
            "{ \"max-requester-connections\": 1.000 }",
            "'max-requester-connections' parameter is not an integer"
        },
        {
            "max-requester-connections 0",
            "{ \"max-requester-connections\": 0 }",
            "invalid max-requester-connections '0'"
        },
        {
            "max-concurrent-queries not an integer",
            "{ \"max-concurrent-queries\": \"10\" }",
            "'max-concurrent-queries' parameter is not an integer"
        },
        {
            "max-concurrent-queries -1",
            "{ \"max-concurrent-queries\": -1 }",
            "invalid max-concurrent-queries '-1'"
        },
        {
            "max-requester-idle-time not an integer",
            "{ \"max-requester-idle-time\": 300. }",
            "'max-requester-idle-time' parameter is not an integer"
        },
        {
            "max-requester-idle-time 0",
            "{ \"max-requester-idle-time\": 0 }",
            "invalid max-requester-idle-time '0'"
        },
        {
            "max-requester-idle-time 5000000",
            "{ \"max-requester-idle-time\": 5000000 }",
            "invalid max-requester-idle-time '5000000'"
        },
        {
            "max-leases-per-fetch not an integer",
            "{ \"max-leases-per-fetch\": \"5\" }",
            "'max-leases-per-fetch' parameter is not an integer"
        },
        {
            "max-leases-per-fetch 0",
            "{ \"max-leases-per-fetch\": 0 }",
            "invalid max-leases-per-fetch '0'"
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        LeaseQueryImplPtr impl;
        ElementPtr cfg = Element::createMap();
        ASSERT_NO_THROW(cfg->set("advanced",
                                 Element::fromJSON(scenario.config_)))
            << "bad JSON: " << scenario.config_;
        cfg->set("requesters", Element::fromJSON("[ \"127.0.0.1\" ]"));
        EXPECT_THROW_MSG(impl.reset(new LeaseQueryImpl4(cfg)),
                         Exception, scenario.exp_msg_);
    }
}

/// @brief Memfile test fixture.
class MemfileBulkLeaseQuery4ProcessTest : public
    BaseBulkLeaseQuery4ProcessTest<MemfileTestLeaseMgr> {
};

// Verifies that valid v4 configuration parses and that requesters
// can be validated.
TEST_F(MemfileBulkLeaseQuery4ProcessTest, validConfig4) {
    // Create an implementation with two requesters.
    const string json = "{\n"
        " \"requesters\" : [ \"127.0.0.1\", \"192.0.2.2\" ],\n"
        " \"advanced\": {\n"
        "  \"bulk-query-enabled\": true,\n"
        "  \"active-query-enabled\": false,\n"
        "  \"extended-info-tables-enabled\": false,\n"
        "  \"lease-query-ip\": \"127.0.0.1\",\n"
        "  \"lease-query-tcp-port\": 12345,\n"
        "  \"max-bulk-query-threads\": 10,\n"
        "  \"max-requester-connections\": 10,\n"
        "  \"max-concurrent-queries\": 5,\n"
        "  \"max-requester-idle-time\": 300,\n"
        "  \"max-leases-per-fetch\": 100\n"
        " }"
        "}";

    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));

    LeaseQueryImplPtr impl;
    ASSERT_NO_THROW_LOG(impl.reset(new LeaseQueryImpl4(config)));

    // Verify known and unknown requesters check correctly.
    EXPECT_EQ(2, impl->getNumRequesters());
    EXPECT_FALSE(impl->isRequester(IOAddress("192.0.2.1")));
    EXPECT_TRUE(impl->isRequester(IOAddress("127.0.0.1")));
    EXPECT_TRUE(impl->isRequester(IOAddress("192.0.2.2")));

    // Make sure a test with a v6 address complains.
    ASSERT_THROW_MSG(impl->isRequester(IOAddress("2001:db8:1::1")), BadValue,
                     "not a IPv4 address");

    // Verify the advanced config.
    auto mgr = BulkLeaseQueryService::instance();
    ASSERT_TRUE(mgr);
    EXPECT_EQ(AF_INET, mgr->getFamily());
    EXPECT_TRUE(mgr->getBulkQueryEnabled());
    EXPECT_FALSE(mgr->getActiveQueryEnabled());
    EXPECT_FALSE(mgr->getExtendedInfoTablesEnabled());
    EXPECT_EQ(IOAddress("127.0.0.1"), mgr->getLeaseQueryIp());
    EXPECT_EQ(12345, mgr->getLeaseQueryTcpPort());
    EXPECT_EQ(10, mgr->getMaxBulkQueryThreads());
    EXPECT_EQ(10, mgr->getMaxRequesterConnections());
    EXPECT_EQ(5, mgr->getMaxConcurrentQueries());
    EXPECT_EQ(300, mgr->getMaxRequesterIdleTime());
    EXPECT_EQ(100, mgr->getMaxLeasePerFetch());

    // Verify setters.
    EXPECT_NO_THROW(mgr->setMaxBulkQueryThreads(20));
    EXPECT_EQ(20, mgr->getMaxBulkQueryThreads());

    EXPECT_THROW_MSG(mgr->setMaxRequesterConnections(0), BadValue,
                     "new max requester connections is 0");
    EXPECT_NO_THROW(mgr->setMaxRequesterConnections(20));
    EXPECT_EQ(20, mgr->getMaxRequesterConnections());

    EXPECT_NO_THROW(mgr->setMaxConcurrentQueries(0));
    EXPECT_EQ(0, mgr->getMaxConcurrentQueries());

    EXPECT_THROW_MSG(mgr->setMaxLeasePerFetch(0), BadValue,
                     "new max leases per fetch is 0");
    EXPECT_NO_THROW(mgr->setMaxLeasePerFetch(200));
    EXPECT_EQ(200, mgr->getMaxLeasePerFetch());

    // Make sure listener involved functions do not misbehave.
    ASSERT_NO_THROW(mgr->startListener());
    ASSERT_NO_THROW(mgr->checkListenerPausePermission());
    ASSERT_NO_THROW(mgr->pauseListener());
    ASSERT_NO_THROW(mgr->resumeListener());
    ASSERT_NO_THROW(mgr->stopListener());
}

// Verifies that service detects when Kea core is not configured
// for multi-threading when BLQ is enabled.
TEST_F(MemfileBulkLeaseQuery4ProcessTest, coreNotMultiThreadedCheck) {
    // Create an implementation with two requesters.
    const string json = "{\n"
        " \"requesters\" : [ \"127.0.0.1\", \"192.0.2.2\" ],\n"
        " \"advanced\": {\n"
        "  \"bulk-query-enabled\": true,\n"
        "  \"active-query-enabled\": false,\n"
        "  \"extended-info-tables-enabled\": false,\n"
        "  \"lease-query-ip\": \"127.0.0.1\",\n"
        "  \"lease-query-tcp-port\": 12345,\n"
        "  \"max-bulk-query-threads\": 10,\n"
        "  \"max-requester-connections\": 10,\n"
        "  \"max-concurrent-queries\": 5,\n"
        "  \"max-requester-idle-time\": 300,\n"
        "  \"max-leases-per-fetch\": 100\n"
        " }"
        "}";

    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));

    // Turn off core multi-threading.
    setDHCPMultiThreadingConfig(false, 0, 0);

    LeaseQueryImplPtr impl;
    ASSERT_THROW_MSG(impl.reset(new LeaseQueryImpl4(config)), BadValue,
                     "BulkLeaseQuery requires Kea multi-threading to be enabled");
}

// Verifies that implementation loads when core MT is off but
// bulk lease query is disabled.
TEST_F(MemfileBulkLeaseQuery4ProcessTest, bulkLeaseQueryDisabled) {
    // Create an implementation with two requesters.
    const string json = "{\n"
        " \"requesters\" : [ \"127.0.0.1\", \"192.0.2.2\" ],\n"
        " \"advanced\": {\n"
        "  \"bulk-query-enabled\": false,\n"
        "  \"active-query-enabled\": false,\n"
        "  \"extended-info-tables-enabled\": false,\n"
        "  \"lease-query-ip\": \"127.0.0.1\",\n"
        "  \"lease-query-tcp-port\": 12345,\n"
        "  \"max-bulk-query-threads\": 10,\n"
        "  \"max-requester-connections\": 10,\n"
        "  \"max-concurrent-queries\": 5,\n"
        "  \"max-requester-idle-time\": 300,\n"
        "  \"max-leases-per-fetch\": 100\n"
        " }"
        "}";

    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));

    // Turn off core multi-threading.
    setDHCPMultiThreadingConfig(false, 0, 0);

    LeaseQueryImplPtr impl;
    ASSERT_NO_THROW(impl.reset(new LeaseQueryImpl4(config)));

    // Verify the advanced config.
    auto mgr = BulkLeaseQueryService::instance();
    ASSERT_TRUE(mgr);
    EXPECT_FALSE(mgr->getBulkQueryEnabled());

    // Make sure listener involved functions do not misbehave.
    ASSERT_NO_THROW(mgr->startListener());
    ASSERT_NO_THROW(mgr->checkListenerPausePermission());
    ASSERT_NO_THROW(mgr->pauseListener());
    ASSERT_NO_THROW(mgr->resumeListener());
    ASSERT_NO_THROW(mgr->stopListener());
}

// These tests verify scenarios where the inbound packet invalid and
// to for which the init function throws.
TEST_F(MemfileBulkLeaseQuery4ProcessTest, initQueryInvalidQuery) {
    // An v6 packet should get tossed.
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_LEASEQUERY, 123));
    ASSERT_THROW_MSG(initBulkQuery(pkt6), BadValue,
                     "BulkLeaseQuery4 has no DHCPv4 query");
}

// This test verifies scenarios were the query is logically invalid and
// to which the server responds with a DHCPLEASEQUERYDONE packet
// but with an error status code option.
TEST_F(MemfileBulkLeaseQuery4ProcessTest, initQueryInvalidWithStatus) {
    // For the server id.
    createBulkLeaseQueryService();

    // Structure that contains a test scenario.
    struct Scenario {
        const string description_;
        std::function<void(Pkt4Ptr)> modifier_;
        BLQStatusCode exp_status_code_;
        const string exp_message_;
    };

    // List of test scenarios to execute.
    vector<Scenario> scenarios {
        {
            "no zero ciaddr",
            [](Pkt4Ptr lq) {
                lq->setCiaddr(IOAddress("129.0.2.1"));
            },
            BLQ_STATUS_MalformedQuery,
            "ciaddr must be zero"
        },
        {
            "no zero yiaddr",
            [](Pkt4Ptr lq) {
                lq->setYiaddr(IOAddress("129.0.2.1"));
            },
            BLQ_STATUS_MalformedQuery,
            "yiaddr must be zero"
        },
        {
            "no zero siaddr",
            [](Pkt4Ptr lq) {
                lq->setSiaddr(IOAddress("129.0.2.1"));
            },
            BLQ_STATUS_MalformedQuery,
            "siaddr must be zero"
        },
        {
            "malformed query start time",
            [](Pkt4Ptr lq) {
                OptionPtr opt(new Option(Option::V4, DHO_QUERY_START_TIME));
                lq->addOption(opt);
            },
            BLQ_STATUS_MalformedQuery,
            "illegal 'query-start-time'"
        },
        {
            "negative query start time",
            [](Pkt4Ptr lq) {
                OptionPtr opt(new OptionUint32(Option::V4,
                                               DHO_QUERY_START_TIME,
                                               static_cast<uint32_t>(-1)));
                lq->addOption(opt);
            },
            BLQ_STATUS_MalformedQuery,
            "illegal 'query-start-time'"
        },
        {
            "malformed query end time",
            [](Pkt4Ptr lq) {
                OptionPtr opt(new Option(Option::V4, DHO_QUERY_END_TIME));
                lq->addOption(opt);
            },
            BLQ_STATUS_MalformedQuery,
            "illegal 'query-end-time'"
        },
        {
            "negative query end time",
            [](Pkt4Ptr lq) {
                OptionPtr opt(new OptionUint32(Option::V4,
                                               DHO_QUERY_END_TIME,
                                               static_cast<uint32_t>(-1)));
                lq->addOption(opt);
            },
            BLQ_STATUS_MalformedQuery,
            "illegal 'query-end-time'"
        },
        {
            "query start time > end time",
            [](Pkt4Ptr lq) {
                OptionPtr opt(new OptionUint32(Option::V4,
                                               DHO_QUERY_START_TIME,
                                               time(0) + 10000));
                lq->addOption(opt);
                opt.reset(new OptionUint32(Option::V4,
                                           DHO_QUERY_END_TIME,
                                           time(0)));
                lq->addOption(opt);
            },
            BLQ_STATUS_MalformedQuery,
            "query-start-time > query-end-time"
        },
        {
            "vpn id",
            [](Pkt4Ptr lq) {
                OptionPtr opt(new Option(Option::V4, DHO_VSS));
                lq->addOption(opt);
            },
            BLQ_STATUS_NotAllowed,
            "VPNs are not supported"
        },
        {
            "for all configured addresses",
            [](Pkt4Ptr) { },
            BLQ_STATUS_NotAllowed,
            "query for all configured addresses is not supported"
        },
        {
            "multiple query types",
            [this](Pkt4Ptr lq) {
                OptionPtr opt = makeClientIdOption(cid1_);
                lq->addOption(opt);
                lq->setHWAddr(hwaddr1_);
            },
            BLQ_STATUS_MalformedQuery,
            "multiple queries"
        },
        {
            "multiple query types 2",
            [this](Pkt4Ptr lq) {
                OptionPtr rai(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS));
                const vector<uint8_t> relay = { 0xaa, 0xbb, 0xcc };
                OptionPtr opt = makeRelayIdOption(relay);
                rai->addOption(opt);
                const vector<uint8_t> remote = { 1, 2, 3, 4 };
                opt = makeRemoteIdOption(remote);
                rai->addOption(opt);
                lq->addOption(rai);
            },
            BLQ_STATUS_MalformedQuery,
            "multiple queries"
        },
        {
            "empty relay id option",
            [this](Pkt4Ptr lq) {
                OptionPtr rai(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS));
                const vector<uint8_t> empty;
                OptionPtr opt = makeRelayIdOption(empty);
                rai->addOption(opt);
                lq->addOption(rai);
            },
             BLQ_STATUS_MalformedQuery,
             "empty relay id option"
        },
        {
            "empty remote id option",
            [this](Pkt4Ptr lq) {
                OptionPtr rai(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS));
                const vector<uint8_t> empty;
                OptionPtr opt = makeRemoteIdOption(empty);
                rai->addOption(opt);
                lq->addOption(rai);
            },
             BLQ_STATUS_MalformedQuery,
             "empty remote id option"
        }
    };

    // Iterate over the scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Make the lease query.
        Pkt4Ptr lq = makeLeaseQuery();

        // Modify the lease query.
        ASSERT_NO_THROW_LOG(scenario.modifier_(lq));

        // Initialize the query.
        ASSERT_NO_THROW_LOG(initBulkQuery(lq));

        // We should have generated a DHCPLEASEQUERYDONE with a
        // status option containing the expected status.
        Pkt4Ptr done = getSentPacket();
        ASSERT_TRUE(done);
        ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
        checkStatus(done, scenario.exp_status_code_, scenario.exp_message_);

        // It is the first packet so it should carry a server id.
        checkServerIdOption(done, IOAddress("127.0.0.1"));

        // Make sure there are no left over packets.
        ASSERT_FALSE(getSentPacket());
    }
}

/// This test exercises queries by client id.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::verifyByClientId() {
    // For the server id.
    createBulkLeaseQueryService();

    time_t now = time(0);

    // Create some leases.
    Lease4Ptr active_lease = addLease(IOAddress("192.0.2.2"), subnet2_,
                                      HWAddrPtr(), cid2_, now);

    Lease4Ptr expired_lease = addLease(IOAddress("192.0.2.3"), subnet2_,
                                       HWAddrPtr(), cid1_, now - 4000);

    Lease4Ptr declined_lease = addLease(IOAddress("192.0.2.4"), subnet2_,
                                        HWAddrPtr(), cid1_, now, "",
                                        Lease::STATE_DECLINED);

    Lease4Ptr reclaimed_lease = addLease(IOAddress("192.0.2.5"), subnet2_,
                                         HWAddrPtr(), cid1_, now, "",
                                         Lease::STATE_EXPIRED_RECLAIMED);

    Lease4Ptr second_lease = addLease(IOAddress("192.0.3.6"), subnet3_,
                                      hwaddr1_, cid2_, now - 1000,
                                      user_context_);

    // Make the lease query.
    Pkt4Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a DHCPLEASEQUERYDONE without a status option.
    Pkt4Ptr done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(done, IOAddress("127.0.0.1"));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Make another lease query.
    lq = makeQueryByClientId(cid2_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated two DHCPLEASEACTIVEs.
    Pkt4Ptr active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Gather the response for further checks.
    Pkt4Ptr active1;
    Pkt4Ptr active2;
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Get the second DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(active->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Gather the response.
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Fully check active_lease response.
    ASSERT_TRUE(active1);
    EXPECT_FALSE(active1->getOption(DHO_DHCP_AGENT_OPTIONS));
    verifyClientId(cid2_, active1);
    verifyHWaddr(hwaddr_empty_, active1);
    verifyTimeOption(active1, DHO_BASE_TIME, now);
    verifyTimeOption(active1, DHO_CLIENT_LAST_TRANSACTION_TIME, 0);
    int32_t exp_lft = active_lease->valid_lft_;
    verifyTimeOption(active1, DHO_DHCP_LEASE_TIME, exp_lft);
    uint32_t exp_t1 = subnet2_->getT1().get();
    verifyTimeOption(active1, DHO_DHCP_RENEWAL_TIME, exp_t1);
    uint32_t exp_t2 = subnet2_->getT2().get();
    verifyTimeOption(active1, DHO_DHCP_REBINDING_TIME, exp_t2);

    // Fully check second_lease response.
    ASSERT_TRUE(active2);
    verifyClientId(cid2_, active2);
    verifyHWaddr(hwaddr1_, active2);
    verifyTimeOption(active2, DHO_BASE_TIME, now);
    verifyTimeOption(active2, DHO_CLIENT_LAST_TRANSACTION_TIME, 1000);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active2, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active2, "0x0104A1B1C1D1");

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too old leases.
    lq = makeQueryByClientId(cid2_);
    OptionPtr opt(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 2000));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too recent leases.
    lq = makeQueryByClientId(cid2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now + 100));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();
    now = time(0);

    // Final test: try to get only the second_lease.
    lq = makeQueryByClientId(cid2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now - 2000));
    lq->addOption(opt);
    OptionPtr opt2(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 100));
    lq->addOption(opt2);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated one DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Check it.
    EXPECT_EQ(IOAddress("192.0.3.6"), active->getCiaddr());
    verifyClientId(cid2_, active);
    verifyHWaddr(hwaddr1_, active);
    verifyTimeOption(active, DHO_BASE_TIME, now);
    verifyTimeOption(active, DHO_CLIENT_LAST_TRANSACTION_TIME,
                     now - second_lease->cltt_);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active, "0x0104A1B1C1D1");

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byClientId) {
    verifyByClientId();
}

/// This test exercises queries by hardware address.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::verifyByHWAddr() {
    // For the server id.
    createBulkLeaseQueryService();

    time_t now = time(0);

    // Create some leases.
    Lease4Ptr active_lease = addLease(IOAddress("192.0.2.2"), subnet2_,
                                      hwaddr2_, cid2_, now);

    Lease4Ptr expired_lease = addLease(IOAddress("192.0.2.3"), subnet2_,
                                       hwaddr1_, cid1_, now - 4000);

    Lease4Ptr declined_lease = addLease(IOAddress("192.0.2.4"), subnet2_,
                                        hwaddr1_, cid1_, now, "",
                                        Lease::STATE_DECLINED);

    Lease4Ptr reclaimed_lease = addLease(IOAddress("192.0.2.5"), subnet2_,
                                         hwaddr1_, cid1_, now, "",
                                         Lease::STATE_EXPIRED_RECLAIMED);

    Lease4Ptr second_lease = addLease(IOAddress("192.0.3.6"), subnet3_,
                                      hwaddr2_, cid2_, now - 1000,
                                      user_context_);

    // Make the lease query.
    Pkt4Ptr lq = makeQueryByHWAddr(hwaddr1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a DHCPLEASEQUERYDONE without a status option.
    Pkt4Ptr done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(done, IOAddress("127.0.0.1"));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Make another lease query.
    lq = makeQueryByHWAddr(hwaddr2_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated two DHCPLEASEACTIVEs.
    Pkt4Ptr active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Gather the response for further checks.
    Pkt4Ptr active1;
    Pkt4Ptr active2;
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Get the second DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(active->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Gather the response.
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Fully check active_lease response.
    ASSERT_TRUE(active1);
    EXPECT_FALSE(active1->getOption(DHO_DHCP_AGENT_OPTIONS));
    verifyClientId(cid2_, active1);
    verifyHWaddr(hwaddr2_, active1);
    verifyTimeOption(active1, DHO_BASE_TIME, now);
    verifyTimeOption(active1, DHO_CLIENT_LAST_TRANSACTION_TIME, 0);
    int32_t exp_lft = active_lease->valid_lft_;
    verifyTimeOption(active1, DHO_DHCP_LEASE_TIME, exp_lft);
    uint32_t exp_t1 = subnet2_->getT1().get();
    verifyTimeOption(active1, DHO_DHCP_RENEWAL_TIME, exp_t1);
    uint32_t exp_t2 = subnet2_->getT2().get();
    verifyTimeOption(active1, DHO_DHCP_REBINDING_TIME, exp_t2);

    // Fully check second_lease response.
    ASSERT_TRUE(active2);
    verifyClientId(cid2_, active2);
    verifyHWaddr(hwaddr2_, active2);
    verifyTimeOption(active2, DHO_BASE_TIME, now);
    verifyTimeOption(active2, DHO_CLIENT_LAST_TRANSACTION_TIME, 1000);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active2, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active2, "0x0104A1B1C1D1");

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too old leases.
    lq = makeQueryByHWAddr(hwaddr2_);
    OptionPtr opt(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 2000));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too recent leases.
    lq = makeQueryByHWAddr(hwaddr2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now + 100));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();
    now = time(0);

    // Final test: try to get only the second_lease.
    lq = makeQueryByHWAddr(hwaddr2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now - 2000));
    lq->addOption(opt);
    OptionPtr opt2(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 100));
    lq->addOption(opt2);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated one DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Check it.
    EXPECT_EQ(IOAddress("192.0.3.6"), active->getCiaddr());
    verifyClientId(cid2_, active);
    verifyHWaddr(hwaddr2_, active);
    verifyTimeOption(active, DHO_BASE_TIME, now);
    verifyTimeOption(active, DHO_CLIENT_LAST_TRANSACTION_TIME,
                     now - second_lease->cltt_);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active, "0x0104A1B1C1D1");

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byHWAddr) {
    verifyByHWAddr();
}

/// This test exercises queries by relay id.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::verifyByRelayId(size_t page_size) {
    // For the server id.
    createBulkLeaseQueryService(page_size);

    time_t now = time(0);

    // Create some leases.
    Lease4Ptr active_lease = addLease(IOAddress("192.0.2.2"), subnet2_,
                                      HWAddrPtr(), cid2_, now,
                                      user_context2_);

    Lease4Ptr expired_lease = addLease(IOAddress("192.0.2.3"), subnet2_,
                                       HWAddrPtr(), cid1_, now - 4000,
                                       user_context1_);

    Lease4Ptr declined_lease = addLease(IOAddress("192.0.2.4"), subnet2_,
                                        HWAddrPtr(), cid1_, now,
                                        user_context1_,
                                        Lease::STATE_DECLINED);

    Lease4Ptr reclaimed_lease = addLease(IOAddress("192.0.2.5"), subnet2_,
                                         HWAddrPtr(), cid1_, now,
                                         user_context1_,
                                         Lease::STATE_EXPIRED_RECLAIMED);

    Lease4Ptr second_lease = addLease(IOAddress("192.0.3.6"), subnet3_,
                                      hwaddr1_, cid2_, now - 1000,
                                      user_context2_);

    // Make the lease query.
    Pkt4Ptr lq = makeQueryByRelayId(id1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a DHCPLEASEQUERYDONE without a status option.
    Pkt4Ptr done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(done, IOAddress("127.0.0.1"));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Make another lease query.
    lq = makeQueryByRelayId(id2_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated two DHCPLEASEACTIVEs.
    Pkt4Ptr active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Gather the response for further checks.
    Pkt4Ptr active1;
    Pkt4Ptr active2;
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Get the second DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(active->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Gather the response.
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Fully check active_lease response.
    ASSERT_TRUE(active1);
    verifyClientId(cid2_, active1);
    verifyHWaddr(hwaddr_empty_, active1);
    verifyTimeOption(active1, DHO_BASE_TIME, now);
    verifyTimeOption(active1, DHO_CLIENT_LAST_TRANSACTION_TIME, 0);
    int32_t exp_lft = active_lease->valid_lft_;
    verifyTimeOption(active1, DHO_DHCP_LEASE_TIME, exp_lft);
    uint32_t exp_t1 = subnet2_->getT1().get();
    verifyTimeOption(active1, DHO_DHCP_RENEWAL_TIME, exp_t1);
    uint32_t exp_t2 = subnet2_->getT2().get();
    verifyTimeOption(active1, DHO_DHCP_REBINDING_TIME, exp_t2);
    verifyRelayAgentInfo(active1, "0x0203AABBCC0C0401020304");

    // Fully check second_lease response.
    ASSERT_TRUE(active2);
    verifyClientId(cid2_, active2);
    verifyHWaddr(hwaddr1_, active2);
    verifyTimeOption(active2, DHO_BASE_TIME, now);
    verifyTimeOption(active2, DHO_CLIENT_LAST_TRANSACTION_TIME, 1000);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active2, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active2, "0x0203AABBCC0C0401020304");

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too old leases.
    lq = makeQueryByRelayId(id2_);
    OptionPtr opt(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 2000));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too recent leases.
    lq = makeQueryByRelayId(id2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now + 100));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();
    now = time(0);

    // Final test: try to get only the second_lease.
    lq = makeQueryByRelayId(id2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now - 2000));
    lq->addOption(opt);
    OptionPtr opt2(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 100));
    lq->addOption(opt2);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated one DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Check it.
    EXPECT_EQ(IOAddress("192.0.3.6"), active->getCiaddr());
    verifyClientId(cid2_, active);
    verifyHWaddr(hwaddr1_, active);
    verifyTimeOption(active, DHO_BASE_TIME, now);
    verifyTimeOption(active, DHO_CLIENT_LAST_TRANSACTION_TIME,
                     now - second_lease->cltt_);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active, "0x0203AABBCC0C0401020304");

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byRelayId100) {
    verifyByRelayId(100);
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byRelayId2) {
    verifyByRelayId(2);
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byRelayId1) {
    verifyByRelayId(1);
}

/// This test exercises queries by remote id.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery4ProcessTest<TestLeaseMgrType>::verifyByRemoteId(size_t page_size) {
    // For the server id.
    createBulkLeaseQueryService(page_size);

    time_t now = time(0);

    // Create some leases.
    Lease4Ptr active_lease = addLease(IOAddress("192.0.2.2"), subnet2_,
                                      HWAddrPtr(), cid2_, now,
                                      user_context1_);

    Lease4Ptr expired_lease = addLease(IOAddress("192.0.2.3"), subnet2_,
                                       HWAddrPtr(), cid1_, now - 4000,
                                       user_context2_);

    Lease4Ptr declined_lease = addLease(IOAddress("192.0.2.4"), subnet2_,
                                        HWAddrPtr(), cid1_, now,
                                        user_context2_,
                                        Lease::STATE_DECLINED);

    Lease4Ptr reclaimed_lease = addLease(IOAddress("192.0.2.5"), subnet2_,
                                         HWAddrPtr(), cid1_, now,
                                         user_context2_,
                                         Lease::STATE_EXPIRED_RECLAIMED);

    Lease4Ptr second_lease = addLease(IOAddress("192.0.3.6"), subnet3_,
                                      hwaddr1_, cid2_, now - 1000,
                                      user_context1_);

    // Make the lease query.
    Pkt4Ptr lq = makeQueryByRemoteId(id1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a DHCPLEASEQUERYDONE without a status option.
    Pkt4Ptr done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(done, IOAddress("127.0.0.1"));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Make another lease query.
    lq = makeQueryByRemoteId(id2_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated two DHCPLEASEACTIVEs.
    Pkt4Ptr active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Gather the response for further checks.
    Pkt4Ptr active1;
    Pkt4Ptr active2;
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Get the second DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(active->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Gather the response.
    if (active->getCiaddr() == IOAddress("192.0.2.2")) {
        active1 = active;
    } else if (active->getCiaddr() == IOAddress("192.0.3.6")) {
        active2 = active;
    } else {
        FAIL() << "unexpected address " << active->getCiaddr().toText();
    }

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());

    // Fully check active_lease response.
    ASSERT_TRUE(active1);
    verifyClientId(cid2_, active1);
    verifyHWaddr(hwaddr_empty_, active1);
    verifyTimeOption(active1, DHO_BASE_TIME, now);
    verifyTimeOption(active1, DHO_CLIENT_LAST_TRANSACTION_TIME, 0);
    int32_t exp_lft = active_lease->valid_lft_;
    verifyTimeOption(active1, DHO_DHCP_LEASE_TIME, exp_lft);
    uint32_t exp_t1 = subnet2_->getT1().get();
    verifyTimeOption(active1, DHO_DHCP_RENEWAL_TIME, exp_t1);
    uint32_t exp_t2 = subnet2_->getT2().get();
    verifyTimeOption(active1, DHO_DHCP_REBINDING_TIME, exp_t2);
    verifyRelayAgentInfo(active1, "0x0204010203040C03AABBCC");

    // Fully check second_lease response.
    ASSERT_TRUE(active2);
    verifyClientId(cid2_, active2);
    verifyHWaddr(hwaddr1_, active2);
    verifyTimeOption(active2, DHO_BASE_TIME, now);
    verifyTimeOption(active2, DHO_CLIENT_LAST_TRANSACTION_TIME, 1000);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active2, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active2, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active2, "0x0204010203040C03AABBCC");

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too old leases.
    lq = makeQueryByRemoteId(id2_);
    OptionPtr opt(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 2000));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Try to get too recent leases.
    lq = makeQueryByRemoteId(id2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now + 100));
    lq->addOption(opt);
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    checkServerIdOption(done, IOAddress("127.0.0.1"));
    ASSERT_FALSE(getSentPacket());

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();
    now = time(0);

    // Final test: try to get only the second_lease.
    lq = makeQueryByRemoteId(id2_);
    opt.reset(new OptionUint32(Option::V4, DHO_QUERY_START_TIME, now - 2000));
    lq->addOption(opt);
    OptionPtr opt2(new OptionUint32(Option::V4, DHO_QUERY_END_TIME, now - 100));
    lq->addOption(opt2);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated one DHCPLEASEACTIVE.
    active = getSentPacket();
    ASSERT_TRUE(active);
    ASSERT_EQ(DHCPLEASEACTIVE, active->getType());
    EXPECT_FALSE(active->getOption(DHO_STATUS_CODE));

    // It is the first packet so it should carry a server id.
    checkServerIdOption(active, IOAddress("127.0.0.1"));

    // Check it.
    EXPECT_EQ(IOAddress("192.0.3.6"), active->getCiaddr());
    verifyClientId(cid2_, active);
    verifyHWaddr(hwaddr1_, active);
    verifyTimeOption(active, DHO_BASE_TIME, now);
    verifyTimeOption(active, DHO_CLIENT_LAST_TRANSACTION_TIME,
                     now - second_lease->cltt_);
    exp_lft = second_lease->valid_lft_;
    verifyTimeOption(active, DHO_DHCP_LEASE_TIME,
                     exp_lft - (now - second_lease->cltt_));
    exp_t1 = static_cast<uint32_t>(round(subnet3_->getT1Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_RENEWAL_TIME,
                     exp_t1 - (now - second_lease->cltt_));
    exp_t2 = static_cast<uint32_t>(round(subnet3_->getT2Percent() * exp_lft));
    verifyTimeOption(active, DHO_DHCP_REBINDING_TIME,
                     exp_t2 - (now - second_lease->cltt_));
    verifyRelayAgentInfo(active, "0x0204010203040C03AABBCC");

    // Last packet is the DHCPLEASEQUERYDONE.
    done = getSentPacket();
    ASSERT_TRUE(done);
    ASSERT_EQ(DHCPLEASEQUERYDONE, done->getType());
    EXPECT_FALSE(done->getOption(DHO_STATUS_CODE));
    EXPECT_FALSE(done->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byRemoteId100) {
    verifyByRemoteId(100);
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byRemoteId2) {
    verifyByRemoteId(2);
}

TEST_F(MemfileBulkLeaseQuery4ProcessTest, byRemoteId1) {
    verifyByRemoteId(1);
}

#ifdef HAVE_MYSQL
/// @brief MySQL test fixture.
class MySQLBulkLeaseQuery4ProcessTest : public
    BaseBulkLeaseQuery4ProcessTest<MySQLTestLeaseMgr> {
};

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byClientId) {
    verifyByClientId();
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byHWAddr) {
    verifyByHWAddr();
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byRelayId100) {
    verifyByRelayId(100);
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byRelayId2) {
    verifyByRelayId(2);
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byRelayId1) {
    verifyByRelayId(1);
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byRemoteId100) {
    verifyByRemoteId(100);
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byRemoteId2) {
    verifyByRemoteId(2);
}

TEST_F(MySQLBulkLeaseQuery4ProcessTest, byRemoteId1) {
    verifyByRemoteId(1);
}
#endif

#ifdef HAVE_PGSQL
/// @brief PostgreSQL test fixture.
class PgSQLBulkLeaseQuery4ProcessTest : public
    BaseBulkLeaseQuery4ProcessTest<PgSQLTestLeaseMgr> {
};

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byClientId) {
    verifyByClientId();
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byHWAddr) {
    verifyByHWAddr();
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byRelayId100) {
    verifyByRelayId(100);
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byRelayId2) {
    verifyByRelayId(2);
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byRelayId1) {
    verifyByRelayId(1);
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byRemoteId100) {
    verifyByRemoteId(100);
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byRemoteId2) {
    verifyByRemoteId(2);
}

TEST_F(PgSQLBulkLeaseQuery4ProcessTest, byRemoteId1) {
    verifyByRemoteId(1);
}
#endif

}
