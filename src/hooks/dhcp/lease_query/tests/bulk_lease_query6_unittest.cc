// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests DHCPv6 Bulk Lease Queries.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
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
#include <bulk_lease_query6.h>
#include <blq_service.h>
#include <lease_query_impl_factory.h>
#include <lease_query_impl6.h>
#include <testutils/gtest_utils.h>
#include <test_lease_mgr.h>

#include <gtest/gtest.h>
#include <list>

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

/// @brief Text fixture for testing LeaseQueryImpl6
template <typename TestLeaseMgrType>
class BaseBulkLeaseQuery6ProcessTest : public ::testing::Test {
public:
    /// @brief Path name of server's duid file
    static const string duid_file_;

    /// @brief Constructor
    ///
    /// Clears the configuration and unloads hook libraries.
    BaseBulkLeaseQuery6ProcessTest()
        : cid_empty_(),
          cid1_(new DUID(vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x06 })),
          cid2_(new DUID(vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x07 })) {
        CfgMgr::instance().clear();
    }

    /// @brief Destructor
    ///
    /// Clears the configuration and unloads hook libraries.
    virtual ~BaseBulkLeaseQuery6ProcessTest() {
        BulkLeaseQueryService::reset();
        LeaseQueryImplFactory::destroyImpl();
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        static_cast<void>(remove(duid_file_.c_str()));
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
    /// - Inits IfaceMgr with test config.
    void SetUp() {
        LeaseMgrFactory::destroy();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.createSchema();
        LeaseMgrFactory::create(test_lease_mgr.dbAccess() +
                                " extended-info-tables=true");

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
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("3001::"), 64));
        subnet4_->addPool(pool);

        // Add PD pool
        pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:4::400"), 118));
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

        // Create I/O service.
        io_service_.reset(new IOService());

        // Enable Kea core MT. We set it here as code checks staging not current.
        setDHCPMultiThreadingConfig(true, 4, 16);
    }

    /// @brief Create the Multi-Threaded Lease Query Listener Manager.
    ///
    /// @param page_size Maximum size of the page returned.
    void createBulkLeaseQueryService(size_t page_size = 10, std::string prefix_lengths = "") {
        ElementPtr cfg = Element::createMap();
        ElementPtr advanced = Element::createMap();
        cfg->set("requesters", Element::fromJSON("[ \"::1\" ]"));
        if (!prefix_lengths.empty()) {
            cfg->set("prefix-lengths", Element::fromJSON(prefix_lengths));
        }
        cfg->set("advanced", advanced);
        advanced->set("max-leases-per-fetch",
                      Element::create(static_cast<long long>(page_size)));
        ASSERT_NO_THROW_LOG(LeaseQueryImplFactory::createImpl(AF_INET6, cfg));
        EXPECT_TRUE(BulkLeaseQueryService::instance());
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
                       time_t cltt, const string& json_context = "",
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
                               const vector<uint8_t>& data) const {
        OptionPtr opt(new Option(Option::V6, opt_type, data));
        return (opt);
    }

    /// @brief Convenience method for making a server identifier option instance.
    ///
    /// @param data server id as a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeServerIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_SERVERID, data));
    }

    /// @brief Convenience method for making a client identifier option instance.
    ///
    /// @param data client id as a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeClientIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_CLIENTID, data));
    }

    /// @brief Convenience method for making a relay identifier option instance.
    ///
    /// @param data relay id as a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeRelayIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_RELAY_ID, data));
    }

    /// @brief Convenience method for making a remote identifier option instance.
    ///
    /// @param data remote id as a vector of bytes
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeRemoteIdOption(const vector<uint8_t>& data) const {
        return (makeBinaryOption(D6O_REMOTE_ID, data));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by ip address
    ///
    /// @param qry_iaaddr ip address for which to query
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByIpAddress(const IOAddress& qry_iaaddr) const {
        Option6IAAddrPtr opt(new Option6IAAddr(D6O_IAADDR, qry_iaaddr, 0, 0));
        return (makeLeaseQuery(LQ6QT_BY_ADDRESS, opt));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by client id
    ///
    /// @param qry_cid client id for which to query
    /// @param link_addr link address to filter by
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByClientId(const DuidPtr& qry_cid,
                                const IOAddress& link_addr
                                = IOAddress::IPV6_ZERO_ADDRESS()) const {
        OptionPtr opt = makeClientIdOption(qry_cid->getDuid());
        return (makeLeaseQuery(LQ6QT_BY_CLIENTID, opt, link_addr));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by relay id
    ///
    /// @param qry_cid relay id for which to query
    /// @param link_addr link address to filter by
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByRelayId(const DuidPtr& qry_cid,
                               const IOAddress& link_addr
                               = IOAddress::IPV6_ZERO_ADDRESS()) const {
        OptionPtr opt = makeRelayIdOption(qry_cid->getDuid());
        return (makeLeaseQuery(LQ6QT_BY_RELAY_ID, opt, link_addr));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by remote id
    ///
    /// @param qry_cid remote id for which to query
    /// @param link_addr link address to filter by
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByRemoteId(const OptionBuffer& qry_cid,
                                const IOAddress& link_addr
                                = IOAddress::IPV6_ZERO_ADDRESS()) const {
        OptionPtr opt = makeRemoteIdOption(qry_cid);
        return (makeLeaseQuery(LQ6QT_BY_REMOTE_ID, opt, link_addr));
    }

    /// @brief Creates a DHCPV6_LEASEQUERY packet for query by link address
    ///
    /// @param link_addr link address to filter by
    ///
    /// @return DHCPV6_LEASEQUERY packet
    Pkt6Ptr makeQueryByLinkAddr(const IOAddress& link_addr) const {
        return (makeLeaseQuery(LQ6QT_BY_LINK_ADDRESS, OptionPtr(), link_addr));
    }

    /// @brief Constructs a DHCPV6_LEASEQUERY message.
    ///
    /// @param qry_type type of query to perform
    /// @param qry_opt option to add to the query. Default null.
    /// @param qry_link_addr ip address of the link for which to query. Defaults
    /// to ::.
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
    void checkIAPrefixOption(OptionPtr opt, const Lease6Ptr lease, uint32_t elapsed) {
        Option6IAPrefixPtr iaprefix_opt;
        iaprefix_opt = boost::dynamic_pointer_cast<Option6IAPrefix>(opt);
        ASSERT_TRUE(iaprefix_opt);
        EXPECT_EQ(lease->addr_, iaprefix_opt->getAddress());
        EXPECT_EQ(lease->prefixlen_, iaprefix_opt->getLength());
        // Since the initial lifetime were set, one second could have ticked,
        // so allow one second of margin error.
        EXPECT_NEAR(lease->valid_lft_ - elapsed, iaprefix_opt->getValid(), 1);
        EXPECT_NEAR(lease->preferred_lft_ - elapsed, iaprefix_opt->getPreferred(), 1);
    }

    /// @brief Validate that a Pkt6 contains the expected D6O_STATUS_CODE
    ///
    /// @param response response packet
    /// @param exp_status expected status code
    /// @param exp_msg expected status text message
    void checkStatus(const Pkt6Ptr& response,
                     const DHCPv6StatusCode& exp_status,
                     const string& exp_msg = "") {
        Option6StatusCodePtr status_opt =
            boost::dynamic_pointer_cast<Option6StatusCode>
                (response->getOption(D6O_STATUS_CODE));
        ASSERT_TRUE(status_opt) << "D6O_STATUS_CODE missing";
        checkStatus(status_opt, exp_status, exp_msg);
    }

    /// @brief Validate that a Pkt6 contains the expected D6O_STATUS_CODE
    ///
    /// @param status_opt status-code option to check
    /// @param exp_status expected status code
    /// @param exp_msg expected status text message
    void checkStatus(Option6StatusCodePtr& status_opt,
                     const DHCPv6StatusCode& exp_status,
                     const string& exp_msg = "") {
        EXPECT_EQ(status_opt->getStatusCode(), exp_status);
        EXPECT_EQ(status_opt->getStatusMessage(), exp_msg);
    }

    /// @brief Fetches a packet from the sent packet list.
    ///
    /// @return The packet de-queued.
    Pkt6Ptr getSentPacket() {
        Pkt6Ptr sent_packet;
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

    /// @brief Queue to hold any packets sent by BulkLeaseQuery6 instances.
    list<Pkt6Ptr> sent_packets_;

    /// @brief Mutex to protect the sent packet queue.
    std::mutex sent_packets_mutex_;

    /// @brief Convenience values.
    DuidPtr cid_empty_;
    DuidPtr cid1_;
    DuidPtr cid2_;
    Subnet6Ptr subnet2_;
    Subnet6Ptr subnet3_;
    Subnet6Ptr subnet4_;
    SharedNetwork6Ptr network1_;
    DuidPtr server_id_;

    static string user_context_;
    static string user_context1_;
    static string user_context2_;

    IOServicePtr io_service_;
    IntervalTimerPtr test_timer_;
    LeaseQueryImplPtr impl_;
    BulkLeaseQuery6Ptr bulk_lease_query_;

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
        std::bind(&BaseBulkLeaseQuery6ProcessTest::post, this, ph::_1);

    /// @brief The pushToSend method.
    ///
    /// @param response The response.
    /// @return Always true.
    bool pushToSend(BlqResponsePtr response) {
        Pkt6Ptr resp =
            boost::dynamic_pointer_cast<Pkt6>(response->getResponse());
        if (!resp) {
            isc_throw(Unexpected, "response is null or not v6");
        }
        lock_guard<mutex> lck(sent_packets_mutex_);
        sent_packets_.push_back(resp);
        return (true);
    }

    /// @brief The pushToSend callback.
    BlqPushToSendCb push_to_send_cb_ =
        std::bind(&BaseBulkLeaseQuery6ProcessTest::pushToSend, this, ph::_1);

    /// @brief The queryComplete method.
    ///
    /// @param xid The transaction id (ignored).
    void queryComplete(Xid) {
        ASSERT_TRUE(io_service_);
        io_service_->stop();
    }

    /// @brief The queryComplete callback.
    BlqQueryCompleteCb query_complete_cb_ =
        std::bind(&BaseBulkLeaseQuery6ProcessTest::queryComplete, this, ph::_1);

    /// @brief Initialize BulkLeaseQuery6.
    ///
    /// @param query The query.
    void initBulkQuery(PktPtr query) {
        ASSERT_TRUE(query);
        BlqQueryPtr blq_query(new BlqQuery(query));
        bulk_lease_query_.reset(new BulkLeaseQuery6(blq_query,
                                                    post_cb_,
                                                    push_to_send_cb_,
                                                    query_complete_cb_));
    }

    /// @brief Process a single bulk query.
    ///
    /// @param query The query.
    void processBulkQuery(Pkt6Ptr query) {
        // Init BulkLeaseQuery6.
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
        // Difference should be less than one second.
        int32_t diff = static_cast<int32_t>(cltt) -
            static_cast<int32_t>(cltt_opt->getValue());
        EXPECT_GE(1, abs(diff));
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

    /// @brief Verify IAPREFIX.
    ///
    /// @param prefix Expected prefix.
    /// @param options Options where to find the IAPREFIX option.
    void verifyIAPREFIX(const IOAddress& prefix,
                        const OptionCollection& options) {
        auto it = options.find(D6O_IAPREFIX);
        ASSERT_TRUE(it != options.end()) << "can't find D6O_IAPREFIX";
        Option6IAPrefixPtr iaprefix_opt;
        iaprefix_opt = boost::dynamic_pointer_cast<Option6IAPrefix>(it->second);
        ASSERT_TRUE(iaprefix_opt) << "D6O_IAPREFIX is not Option6IAPrefixPtr";
        EXPECT_EQ(prefix, iaprefix_opt->getAddress());
    }

    /// @brief Verify relay data option.
    ///
    /// @param hop Expected hop count.
    /// @param peer Expected peer address.
    /// @param link Expected link address.
    /// @param interface_id Expected interface id option.
    /// @param relay_id Expected relay id option.
    /// @param remote_id Expected remote id option.
    /// @param options Options where to find the D6O_LQ_RELAY_DATA option.
    void verifyRelay(uint8_t hop,
                     const IOAddress& peer,
                     const IOAddress& link,
                     const OptionBuffer& interface_id,
                     DuidPtr relay_id,
                     const OptionBuffer& remote_id,
                     const OptionCollection& options);

    /// @brief Verify final DHCPV6_LEASEQUERY_DONE.
    void verifyDone() {
        Pkt6Ptr done = getSentPacket();
        ASSERT_TRUE(done) << "can't find the DHCPV6_LEASEQUERY_DONE";
        EXPECT_EQ(DHCPV6_LEASEQUERY_DONE, done->getType());
        EXPECT_FALSE(done->getOption(D6O_STATUS_CODE));
        EXPECT_FALSE(done->getOption(D6O_CLIENT_DATA));

        // Make sure there are no left over packets.
        EXPECT_FALSE(getSentPacket());
    }

    /// @brief Verify by relay id.
    ///
    /// @param page_size Maximum size of returned pages.
    /// @param link_addr Link address.
    void verifyByRelayId(size_t page_size, const IOAddress& link_addr);

    /// @brief Verify by remote id.
    ///
    /// @param page_size Maximum size of returned pages.
    /// @param link_addr Link address.
    void verifyByRemoteId(size_t page_size, const IOAddress& link_addr);

    /// @brief Verify by link address.
    ///
    /// @param page_size Maximum size of returned pages.
    /// @param link_addr Link address.
    void verifyByLinkAddress(size_t page_size, const IOAddress& link_addr);

    /// @brief Verify by link address with multiple subnets.
    ///
    /// @param page_size Maximum size of returned pages.
    void verifyByLinkAddressMultipleSubnets(size_t page_size);

    /// @brief Verify no extended info tables.
    ///
    /// @param enabled If True enables extended info tables, if False disables
    /// them.
    void verifyNoExtendedInfoTables(bool enabled);

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

    /// @brief Test queryByIpAddress with active PD lease.
    void testQueryByIpAddressActivePDLease();
};

template <typename TestLeaseMgrType> string
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::user_context_ =
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

template <typename TestLeaseMgrType> string
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::user_context1_ =
    "{ \"ISC\": {"
    "   \"relay-info\": ["
    "       {"
    "           \"hop\": 10,"
    "           \"peer\": \"2001:db8:2::1\","
    "           \"link\": \"2001:db8:2::2\","
    "           \"options\": \"0x00250006010203040506003500086464646464646464\","
    "           \"remote-id\": \"010203040506\","
    "           \"relay-id\": \"6464646464646464\""
    "       }]"
    "   }"
    "}";

template <typename TestLeaseMgrType> string
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::user_context2_ =
    "{ \"ISC\": {"
    "   \"relay-info\": ["
    "       {"
    "           \"hop\": 2,"
    "           \"peer\": \"2001:db8:2::3\","
    "           \"link\": \"2001:db8:2::4\","
    "           \"options\": \"0x002500060102030405080035000765656565656565\","
    "           \"remote-id\": \"010203040508\","
    "           \"relay-id\": \"65656565656565\""
    "       }]"
    "   }"
    "}";

template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::verifyRelay(
    uint8_t hop,
    const IOAddress& peer,
    const IOAddress& link,
    const OptionBuffer& interface_id,
    DuidPtr relay_id,
    const OptionBuffer& remote_id,
    const OptionCollection& options) {

    auto it = options.find(D6O_LQ_RELAY_DATA);
    ASSERT_TRUE(it != options.end()) << "can't find D6O_LQ_RELAY_DATA";
    OptionCustomPtr relay_option;
    relay_option = boost::dynamic_pointer_cast<OptionCustom>(it->second);
    ASSERT_TRUE(relay_option) << "D6O_LQ_RELAY_DATA is not OptionCustom";

    // Verify peer address.
    IOAddress peer_addr = IOAddress::IPV6_ZERO_ADDRESS();
    ASSERT_NO_THROW_LOG(peer_addr = relay_option->readAddress(0));
    EXPECT_EQ(peer, peer_addr);

    // Verify the RELAY_FORW content.
    OptionBuffer relay_forw_data;
    ASSERT_NO_THROW_LOG(relay_forw_data = relay_option->readBinary(1));

    // First we unpack it.
    vector<RelayInfoPtr> relay_infos;
    ASSERT_NO_THROW_LOG(unpackRelayForwardMsg(relay_forw_data, relay_infos));

    // We should have one relay.
    EXPECT_EQ(1, relay_infos.size());

    // Verify the first instance.
    ASSERT_EQ(hop, relay_infos[0]->hop_count_);
    ASSERT_EQ(peer, relay_infos[0]->peeraddr_);
    ASSERT_EQ(link, relay_infos[0]->linkaddr_);

    // Count expected options.
    size_t opt_cnt(0);
    if (!interface_id.empty()) {
        ++opt_cnt;
    }
    if (relay_id) {
        ++opt_cnt;
    }
    if (!remote_id.empty()) {
        ++opt_cnt;
    }
    ASSERT_EQ(opt_cnt, relay_infos[0]->options_.size());

    // Check the interface id option.
    if (!interface_id.empty()) {
        auto ifid = relay_infos[0]->options_.find(D6O_INTERFACE_ID);
        ASSERT_TRUE(ifid != relay_infos[0]->options_.end())
            << "can't find D6O_INTERFACE_ID";
        EXPECT_EQ(interface_id, ifid->second->getData());
    }

    // Check the remote id option.
    if (relay_id) {
        auto rid = relay_infos[0]->options_.find(D6O_RELAY_ID);
        ASSERT_TRUE(rid != relay_infos[0]->options_.end())
            << "can't find D6O_RELAY_ID";
        EXPECT_EQ(relay_id->getDuid(), rid->second->getData());
    }

    // Check the remote id option.
    if (!remote_id.empty()) {
        auto rid = relay_infos[0]->options_.find(D6O_REMOTE_ID);
        ASSERT_TRUE(rid != relay_infos[0]->options_.end())
            << "can't find D6O_REMOTE_ID";
        EXPECT_EQ(remote_id, rid->second->getData());
    }
}

/// @brief Path name for server-id generation
template <typename TestLeaseMgrType> const string
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::duid_file_
    = string(TEST_DATA_BUILDDIR) + string("/lq6-duid");

// Verifies that configuration errors are detected.
TEST(BulkLeaseQuery6Test, invalidConfig6) {
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
            "lease-query-ip IPv4",
            "{ \"lease-query-ip\": \"127.0.0.1\" }",
            "lease-query-ip not a IPv6 address"
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
        cfg->set("requesters", Element::fromJSON("[ \"::1\" ]"));
        EXPECT_THROW_MSG(impl.reset(new LeaseQueryImpl6(cfg)),
                         Exception, scenario.exp_msg_);
    }
}

/// @brief Memfile test fixture.
class MemfileBulkLeaseQuery6ProcessTest : public
    BaseBulkLeaseQuery6ProcessTest<MemfileTestLeaseMgr> {
};

// Verifies that valid v6 configuration parses and that requesters
// can be validated.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, validConfig6) {
    // Create an implementation with two requesters.
    const string json = "{\n"
        " \"requesters\" : [ \"2001:db8:1::1\", \"2001:db8:1::3\" ],\n"
        " \"prefix-lengths\": [ 72, 64 ],\n"
        " \"advanced\": {\n"
        "  \"bulk-query-enabled\": true,\n"
        "  \"active-query-enabled\": false,\n"
        "  \"extended-info-tables-enabled\": false,\n"
        "  \"lease-query-ip\": \"::1\",\n"
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

    LeaseQueryImpl6Ptr impl;
    ASSERT_NO_THROW_LOG(impl.reset(new LeaseQueryImpl6(config)));

    // Verify known and unknown requesters check correctly.
    EXPECT_EQ(2, impl->getNumRequesters());
    EXPECT_FALSE(impl->isRequester(IOAddress("2001:db8:1::")));
    EXPECT_TRUE(impl->isRequester(IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(impl->isRequester(IOAddress("2001:db8:1::2")));
    EXPECT_TRUE(impl->isRequester(IOAddress("2001:db8:1::3")));

    // Make sure a test with a v4 address complains.
    ASSERT_THROW_MSG(impl->isRequester(IOAddress("192.0.2.1")), BadValue,
                     "not a IPv6 address");

    // Verify prefix length list.
    PrefixLengthList prefix_lengths;
    ASSERT_NO_THROW_LOG(prefix_lengths = impl->getPrefixLengthList());
    EXPECT_EQ(2, prefix_lengths.size());
    auto it = prefix_lengths.crbegin();
    EXPECT_EQ(*it++, 72);
    EXPECT_EQ(*it, 64);

    // Verify the advanced config.
    auto mgr = BulkLeaseQueryService::instance();
    ASSERT_TRUE(mgr);
    EXPECT_EQ(AF_INET6, mgr->getFamily());
    EXPECT_TRUE(mgr->getBulkQueryEnabled());
    EXPECT_FALSE(mgr->getActiveQueryEnabled());
    EXPECT_FALSE(mgr->getExtendedInfoTablesEnabled());
    EXPECT_EQ(IOAddress("::1"), mgr->getLeaseQueryIp());
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
TEST_F(MemfileBulkLeaseQuery6ProcessTest, coreNotMultiThreadedCheck) {
    // Create an implementation with two requesters.
    const string json = "{\n"
        " \"requesters\" : [ \"2001:db8:1::1\", \"2001:db8:1::3\" ],\n"
        " \"advanced\": {\n"
        "  \"bulk-query-enabled\": true,\n"
        "  \"active-query-enabled\": false,\n"
        "  \"extended-info-tables-enabled\": false,\n"
        "  \"lease-query-ip\": \"::1\",\n"
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
    ASSERT_THROW_MSG(impl.reset(new LeaseQueryImpl6(config)), BadValue,
                     "BulkLeaseQuery requires Kea multi-threading to be enabled");
}

// Verifies that implementation loads when core MT is off but
// bulk lease query is disabled.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, bulkLeaseQueryDisabled) {
    // Create an implementation with two requesters.
    const string json = "{\n"
        " \"requesters\" : [ \"2001:db8:1::1\", \"2001:db8:1::3\" ],\n"
        " \"advanced\": {\n"
        "  \"bulk-query-enabled\": false,\n"
        "  \"active-query-enabled\": false,\n"
        "  \"extended-info-tables-enabled\": false,\n"
        "  \"lease-query-ip\": \"::1\",\n"
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
    ASSERT_NO_THROW(impl.reset(new LeaseQueryImpl6(config)));

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
// to for which the hook lib will drop the packet without generating
// a response.
//
// - Not a DHCPv6 packet
// - No D6O_CLIENTID option
// - Non-matching D6O_SERVERID
// - Source address of ::
// - Source address that does not match a requester
// - No D6O_LQ_QUERY option
TEST_F(MemfileBulkLeaseQuery6ProcessTest, initQueryInvalidQuery) {
    // A v4 packet should get tossed.
    Pkt4Ptr pkt4(new Pkt4(DHCPLEASEQUERY, 0));
    ASSERT_THROW_MSG(initBulkQuery(pkt4), BadValue,
                     "BulkLeaseQuery6 has no DHCPv6 query");

    // No client-id option should fail.
    Pkt6Ptr lq(new Pkt6(DHCPV6_LEASEQUERY, 123));
    ASSERT_THROW_MSG(initBulkQuery(lq), BadValue,
                     "DHCPV6_LEASEQUERY must supply a D6O_CLIENTID");

    // Add a client-id option.
    lq->addOption(makeClientIdOption(vector<uint8_t>{ 01, 02, 03, 04, 05, 06}));

    // Add an a non-matching server id.
    lq->addOption(makeServerIdOption(vector<uint8_t>{ 10, 11, 12, 13, 14, 15, 16 }));
    string expected = "rejecting DHCPV6_LEASEQUERY from: ::, unknown";
    expected += " server-id: type=00002, len=00007: 0a:0b:0c:0d:0e:0f:10";
    ASSERT_THROW_MSG(initBulkQuery(lq), BadValue, expected);

    // Add a matching server id.
    lq->delOption(D6O_SERVERID);
    lq->addOption(makeServerIdOption(server_id_->getDuid()));

    // A query without a D6O_LQ_QUERY option should fail.
    ASSERT_THROW_MSG(initBulkQuery(lq), BadValue,
                     "DHCPV6_LEASEQUERY must supply a D6O_LQ_QUERY option");
}

// This test verifies scenarios were the query is logically
// invalid and to which the server responds with a DHCPV6_LEASEQUERY_REPLY
// packet but with an other than successful status code option:
// - Unknown query type
// - query by ip address that's missing the D6O_IAADDR option
// - query by client id that's missing the D6O_CLIENTID option
// - query by relay id that's missing the D6O_RELAY_ID option
// - query by remote id that's missing the D6O_REMOTE_ID option
// - query by link address with a :: address
TEST_F(MemfileBulkLeaseQuery6ProcessTest, processQueryInvalidWithStatus) {
    // Structure that contains a test scenario.
    struct Scenario {
        const string description_;
        uint8_t qry_type_;
        DHCPv6StatusCode exp_status_code_;
        const string exp_message_;
    };

    // List of test scenarios to execute.
    vector<Scenario> scenarios {
        {
            "unknown query type",
            77,
            STATUS_UnknownQueryType,
            "unknown query-type"
        },
        {
            "missing iaaddr",
            LQ6QT_BY_ADDRESS,
            STATUS_MalformedQuery,
            "missing D6O_IAADDR"
        },
        {
            "missing client id",
            LQ6QT_BY_CLIENTID,
            STATUS_MalformedQuery,
            "missing D6O_CLIENTID"
        },
        {
            "missing relay id",
            LQ6QT_BY_RELAY_ID,
            STATUS_MalformedQuery,
            "missing D6O_RELAY_ID"
        },
        {
            "missing remote id",
            LQ6QT_BY_REMOTE_ID,
            STATUS_MalformedQuery,
            "missing D6O_REMOTE_ID"
        },
        {
            "missing link address",
            LQ6QT_BY_LINK_ADDRESS,
            STATUS_MalformedQuery,
            "undefined link address"
        }
    };

    // Iterate over the scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Make the lease query.
        Pkt6Ptr lq = makeLeaseQuery(scenario.qry_type_);
        // Process the query.
        ASSERT_NO_THROW_LOG(processBulkQuery(lq));

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

// This test verifies that an empty relay id option is invalid.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, processQueryEmptyRelayId) {
    // Create an empty relay id option.
    const vector<uint8_t> empty;
    OptionPtr opt = makeRelayIdOption(empty);
    // Make the lease query.
    Pkt6Ptr lq = makeLeaseQuery(LQ6QT_BY_RELAY_ID, opt);
    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a status option.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_MalformedQuery, "malformed D6O_RELAY_ID");

    // Should not have any options.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
}

// This test verifies that an empty remote id option is invalid.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, processQueryEmptyRemoteId) {
    // Create an empty remote id option.
    const vector<uint8_t> empty;
    OptionPtr opt = makeRemoteIdOption(empty);
    // Make the lease query.
    Pkt6Ptr lq = makeLeaseQuery(LQ6QT_BY_REMOTE_ID, opt);
    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a status option.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_MalformedQuery, "empty D6O_REMOTE_ID");

    // Should not have any options.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Make sure there are no left over packets.
    ASSERT_FALSE(getSentPacket());
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
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::testQueryByIpAddressNoActiveLease() {
    createBulkLeaseQueryService();

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
        const string description_;
        IOAddress qry_iaaddr_;
        DHCPv6StatusCode exp_status_code_;
        const string exp_message_;
    };

    // List of test scenarios to execute.
    vector<Scenario> scenarios {
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

        // Reset test environment.
        io_service_.reset(new IOService());
        flushSentPackets();

        // Make the lease query.
        Pkt6Ptr lq = makeQueryByIpAddress(scenario.qry_iaaddr_);

        // Process the query.
        ASSERT_NO_THROW_LOG(processBulkQuery(lq));

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

TEST_F(MemfileBulkLeaseQuery6ProcessTest, queryByIpAddressNoActiveLease) {
    testQueryByIpAddressNoActiveLease();
}

// This test verifies that given a logically valid query by ip address
// for which an active lease exists the server responds with a
// DHCPV6_LEASEQUERY_REPLY packet with the proper content followed
// by a DHCPV6_LEASEQUERY_DONE.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::testQueryByIpAddressActiveLease() {
    createBulkLeaseQueryService();

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
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

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
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(100, options);

    // Now let's check w should have one TYPE_NA lease.
    verifyIAADDR(active_lease->addr_, options);

    // There should be a DHCPV6_LEASEQUERY_DONE message.
    verifyDone();
}

TEST_F(MemfileBulkLeaseQuery6ProcessTest, queryByIpAddressActiveLease) {
    testQueryByIpAddressActiveLease();
}

// This test verifies that given a logically valid query by client id
// for which no active leases exist the server responds with a
// DHCPV6_LEASEQUERY_REPLY packet with the proper content.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::testQueryByClientIdNoActiveLease() {
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr active_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                      subnet2_, cid2_, now);

    Lease6Ptr expired_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                                       subnet3_, cid1_, now - 4000, "");

    Lease6Ptr declined_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                        subnet4_, cid1_, now, "",
                                        Lease::STATE_DECLINED);

    Lease6Ptr reclaimed_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::101"),
                                         subnet2_, cid1_, now, "",
                                         Lease::STATE_EXPIRED_RECLAIMED);

    Lease6Ptr pd_lease = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                  subnet4_, cid1_, now - 4000);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

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

TEST_F(MemfileBulkLeaseQuery6ProcessTest, queryByClientIdNoActiveLease) {
    testQueryByClientIdNoActiveLease();
}

// This test verifies that given a logically valid query by client id
// for which active leases on multiple subnets exist, the server responds
// with a DHCPV6_LEASEQUERY_REPLY packet with the proper content followed
// by DHCPV6_LEASEQUERY_DATA packets and a final DHCPV6_LEASEQUERY_DONE.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::testQueryByClientIdMultipleLinks() {
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                      subnet2_, cid1_, now - 300);

    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:3::100"),
                                       subnet3_, cid1_, now - 100);

    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                        subnet4_, cid1_, now - 200);

    Lease6Ptr pd_lease = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                  subnet4_, cid1_, now - 400);
    // Make the lease query.
    Pkt6Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // Should not these two any options.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(100, options);

    // Now let's check w should have one TYPE_NA lease.
    // Most recent lease is lease2.
    verifyIAADDR(lease2->addr_, options);

    // Second message is a DHCPV6_LEASEQUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(200, options);

    // Now let's check w should have one TYPE_NA lease.
    // Second lease is lease3.
    verifyIAADDR(lease3->addr_, options);

    // Third message is a DHCPV6_LEASEQUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(300, options);

    // Now let's check w should have one TYPE_NA lease.
    // Third lease is lease1.
    verifyIAADDR(lease1->addr_, options);

    // Fourth message is a DHCPV6_LEASEQUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(400, options);

    // Now let's check w should have one TYPE_PD lease.
    verifyIAPREFIX(pd_lease->addr_, options);

    // There should be a final DHCPV6_LEASEQUERY_DONE message.
    verifyDone();
}

TEST_F(MemfileBulkLeaseQuery6ProcessTest, queryByClientIdMultipleLinks) {
    testQueryByClientIdMultipleLinks();
}

// This test verifies that given a logically valid query by client id
// for which active leases on the same subnet exist, the server responds
// with a DHCPV6_LEASEQUERY_REPLY packet with the proper content, including
// a D6O_LQ_RELAY_DATA option from the newest active lease.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::testQueryByClientIdActiveLeases() {
    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 4000);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::104"),
                                subnet4_, cid1_, now - 100, user_context_);
    Lease6Ptr lease3 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                subnet4_, cid1_, now - 200);
    Lease6Ptr lease4 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:2::"),
                                subnet4_, cid1_, now - 4000);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByClientId(cid1_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // Should not have a clink link option.
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));

    // Should have client data option.
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify that CLTT comes from lease2.
    verifyCLTT(100, options);

    // Now let's check we should have one TYPE_NA lease.
    auto opt_iter = options.find(D6O_IAADDR);
    ASSERT_TRUE(opt_iter != options.end());
    // Most recent lease is lease2.
    checkIAAddrOption(opt_iter->second, lease2, 100);

    // We should have a relay option.
    const vector<uint8_t> interface_id = { 0x65, 0x74, 0x68, 0x30 };
    verifyRelay(1, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                interface_id, DuidPtr(), OptionBuffer(), options);

    // Second message is a DHCPV6_LEASEQUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    EXPECT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(200, options);

    // Now let's check we should have one TYPE_PD lease.
    opt_iter = options.find(D6O_IAPREFIX);
    ASSERT_TRUE(opt_iter != options.end());
    // Second lease is lease3.
    checkIAPrefixOption(opt_iter->second, lease3, 200);

    // There should be a final DHCPV6_LEASEQUERY_DONE message.
    verifyDone();
}

TEST_F(MemfileBulkLeaseQuery6ProcessTest, queryByClientIdActiveLeases) {
    testQueryByClientIdActiveLeases();
}

template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::verifyByRelayId(
    size_t page_size,
    const IOAddress& link_addr) {

    createBulkLeaseQueryService(page_size);

    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                subnet2_, cid1_, now - 4000, user_context1_);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::101"),
                                subnet2_, cid2_, now - 300, user_context1_);
    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 200, user_context1_);
    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::104"),
                                subnet4_, cid2_, now - 100, user_context1_);
    Lease6Ptr lease5 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::200"),
                                subnet4_, cid2_, now, user_context2_);
    Lease6Ptr pd_lease = addLease(Lease::TYPE_PD, IOAddress("2001:db8:4::300"),
                                  subnet4_, cid1_, now - 50, user_context1_);
    Lease6Ptr pd_lease2 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                   subnet4_, cid1_, now - 50, user_context1_);

    // Make the lease query.
    DuidPtr relay_id(new DUID(vector<uint8_t>(8, 0x64)));
    Pkt6Ptr lq = makeQueryByRelayId(relay_id, link_addr);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Unknown link case.
    if (link_addr == IOAddress("2001:db8:111::")) {
        checkStatus(rsp, STATUS_NotConfigured, "not a configured link");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Link without any lease.
    if (link_addr == IOAddress("2001:db8:3::")) {
        checkStatus(rsp, STATUS_Success, "no active leases");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Other cases are successful.
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // We should have D6O_CLIENT_DATA option.
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // First lease is lease2.

        // Verify client id.
        verifyClientId(cid2_, options);

        // Verify CLTT.
        verifyCLTT(300, options);

        // Verify IAADDR.
        verifyIAADDR(lease2->addr_, options);
    } else {
        // First lease is lease 3.

        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(200, options);

        // Verify IAADDR.
        verifyIAADDR(lease3->addr_, options);
    }

    // Verify relay data.
    vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Second packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // Second lease is lease 3.

        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(200, options);

        // Verify IAADDR.
        verifyIAADDR(lease3->addr_, options);
    } else {
        // Second lease is lease 4.

        // Verify client id.
        verifyClientId(cid2_, options);

        // Verify CLTT.
        verifyCLTT(100, options);

        // Verify IAADDR.
        verifyIAADDR(lease4->addr_, options);
    }

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Third packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // Next lease is lease 4.
        // Verify client id.
        verifyClientId(cid2_, options);

        // Verify CLTT.
        verifyCLTT(100, options);

        // Verify IAADDR.
        verifyIAADDR(lease4->addr_, options);
    } else {
        // Next lease is pd_lease.
        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(50, options);

        // Verify IAPREFIX.
        verifyIAPREFIX(pd_lease->addr_, options);
    }

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Fourth packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // Next lease is pd_lease.
        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(50, options);

        // Verify IAPREFIX.
        verifyIAPREFIX(pd_lease->addr_, options);
    } else {
        // Last lease is pd_lease 2.
        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(50, options);

        // Verify IAPREFIX.
        verifyIAPREFIX(pd_lease2->addr_, options);
    }

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    if (!link_addr.isV6Zero()) {
        // Finished.
        verifyDone();
        return;
    }

    // Fifth packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // Last lease is pd lease 2.

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(50, options);

    // Verify IAPREFIX.
    verifyIAPREFIX(pd_lease2->addr_, options);

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Finished.
    verifyDone();
}

// This test verifies that by relay id with unknown link returns an error.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdUnknownLink) {
    verifyByRelayId(10, IOAddress("2001:db8:111::"));
}

// This test verifies that by relay id with a link without lease returns nothing.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdEmptyLink) {
    verifyByRelayId(10, IOAddress("2001:db8:3::"));
}

// This test verifies that by relay id with no link and 10 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdNoLink) {
    verifyByRelayId(10, IOAddress::IPV6_ZERO_ADDRESS());
}

// This test verifies that by relay id with no link and 2 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdNoLink2) {
    verifyByRelayId(2, IOAddress::IPV6_ZERO_ADDRESS());
}

// This test verifies that by relay id with no link and 1 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdNoLink1) {
    verifyByRelayId(1, IOAddress::IPV6_ZERO_ADDRESS());
}

// This test verifies that by relay id with a link and 10 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdLink) {
    verifyByRelayId(10, IOAddress("2001:db8:4::1"));
}

// This test verifies that by relay id with a link and 2 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdLink2) {
    verifyByRelayId(2, IOAddress("2001:db8:4::1"));
}

// This test verifies that by relay id with a link and 1 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRelayIdLink1) {
    verifyByRelayId(1, IOAddress("2001:db8:4::1"));
}

template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::verifyByRemoteId(
    size_t page_size,
    const IOAddress& link_addr) {

    createBulkLeaseQueryService(page_size);

    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                subnet2_, cid1_, now - 4000, user_context1_);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::101"),
                                subnet2_, cid2_, now - 300, user_context1_);
    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 200, user_context1_);
    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::104"),
                                subnet4_, cid2_, now - 100, user_context1_);
    Lease6Ptr lease5 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::200"),
                                subnet4_, cid2_, now, user_context2_);
    Lease6Ptr pd_lease = addLease(Lease::TYPE_PD, IOAddress("2001:db8:4::300"),
                                  subnet4_, cid1_, now - 50, user_context1_);
    Lease6Ptr pd_lease2 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                   subnet4_, cid1_, now - 50, user_context1_);

    // Make the lease query.
    vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
    Pkt6Ptr lq = makeQueryByRemoteId(remote_id, link_addr);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Unknown link case.
    if (link_addr == IOAddress("2001:db8:111::")) {
        checkStatus(rsp, STATUS_NotConfigured, "not a configured link");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Link without any lease.
    if (link_addr == IOAddress("2001:db8:3::")) {
        checkStatus(rsp, STATUS_Success, "no active leases");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Other cases are successful.
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // We should have D6O_CLIENT_DATA option.
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // First lease is lease2.

        // Verify client id.
        verifyClientId(cid2_, options);

        // Verify CLTT.
        verifyCLTT(300, options);

        // Verify IAADDR.
        verifyIAADDR(lease2->addr_, options);
    } else {
        // First lease is lease 3.

        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(200, options);

        // Verify IAADDR.
        verifyIAADDR(lease3->addr_, options);
    }

    // Verify relay data.
    DuidPtr relay_id(new DUID(vector<uint8_t>(8, 0x64)));
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Second packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // Second lease is lease 3.

        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(200, options);

        // Verify IAADDR.
        verifyIAADDR(lease3->addr_, options);
    } else {
        // Second lease is lease 4.

        // Verify client id.
        verifyClientId(cid2_, options);

        // Verify CLTT.
        verifyCLTT(100, options);

        // Verify IAADDR.
        verifyIAADDR(lease4->addr_, options);
    }

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Third packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // Next lease is lease 4.
        // Verify client id.
        verifyClientId(cid2_, options);

        // Verify CLTT.
        verifyCLTT(100, options);

        // Verify IAADDR.
        verifyIAADDR(lease4->addr_, options);
    } else {
        // Next lease is pd_lease.
        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(50, options);

        // Verify IAPREFIX.
        verifyIAPREFIX(pd_lease->addr_, options);
    }

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Fourth packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    if (link_addr.isV6Zero()) {
        // Next lease is pd_lease.
        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(50, options);

        // Verify IAPREFIX.
        verifyIAPREFIX(pd_lease->addr_, options);
    } else {
        // Last lease is pd_lease 2.
        // Verify client id.
        verifyClientId(cid1_, options);

        // Verify CLTT.
        verifyCLTT(50, options);

        // Verify IAPREFIX.
        verifyIAPREFIX(pd_lease2->addr_, options);
    }

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    if (!link_addr.isV6Zero()) {
        // Finished.
        verifyDone();
        return;
    }

    // Fifth packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // Last lease is pd lease 2.

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(50, options);

    // Verify IAPREFIX.
    verifyIAPREFIX(pd_lease2->addr_, options);

    // Verify relay data.
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Finished.
    verifyDone();
}

// This test verifies that by remote id with unknown link returns an error.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdUnknownLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:111::"));
}

// This test verifies that by remote id with a link without lease returns nothing.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdEmptyLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:3::"));
}

// This test verifies that by remote id with no link and 10 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdNoLink) {
    verifyByRemoteId(10, IOAddress::IPV6_ZERO_ADDRESS());
}

// This test verifies that by remote id with no link and 2 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdNoLink2) {
    verifyByRemoteId(2, IOAddress::IPV6_ZERO_ADDRESS());
}

// This test verifies that by remote id with no link and 1 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdNoLink1) {
    verifyByRemoteId(1, IOAddress::IPV6_ZERO_ADDRESS());
}

// This test verifies that by remote id with a link and 10 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:4::1"));
}

// This test verifies that by remote id with a link and 2 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdLink2) {
    verifyByRemoteId(2, IOAddress("2001:db8:4::1"));
}

// This test verifies that by remote id with a link and 1 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byRemoteIdLink1) {
    verifyByRemoteId(1, IOAddress("2001:db8:4::1"));
}

template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::verifyByLinkAddress(
    size_t page_size,
    const IOAddress& link_addr) {

    createBulkLeaseQueryService(page_size);

    time_t now = time(0);

    // Create some leases.
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                                subnet2_, cid1_, now - 4000);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::101"),
                                subnet2_, cid2_, now - 300, "",
                                Lease::STATE_DECLINED);
    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::100"),
                                subnet4_, cid1_, now - 200, user_context1_);
    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::104"),
                                subnet4_, cid2_, now - 100);
    Lease6Ptr lease5 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:4::200"),
                                subnet4_, cid1_, now - 300, user_context2_);
    Lease6Ptr pd_lease = addLease(Lease::TYPE_PD, IOAddress("2001:db8:4::300"),
                                  subnet4_, cid1_, now - 50, user_context1_);
    Lease6Ptr pd_lease2 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                   subnet4_, cid2_, now - 50, user_context2_);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByLinkAddr(link_addr);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a
    // status option containing the expected status.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // Unknown link case.
    if (link_addr == IOAddress("2001:db8:111::")) {
        checkStatus(rsp, STATUS_NotConfigured, "not a configured link");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Link without any lease.
    if (link_addr == IOAddress("2001:db8:3::")) {
        checkStatus(rsp, STATUS_Success, "no active leases");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Link without active lease.
    if (link_addr == IOAddress("2001:db8:2::")) {
        checkStatus(rsp, STATUS_Success, "no active leases");
        EXPECT_FALSE(rsp->getOption(D6O_CLIENT_DATA));
        return;
    }

    // Other cases are successful.
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // We should have D6O_CLIENT_DATA option.
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // First lease is lease 3.

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(200, options);

    // Verify IAADDR.
    verifyIAADDR(lease3->addr_, options);

    // Verify relay data.
    DuidPtr relay_id(new DUID(vector<uint8_t>(8, 0x64)));
    vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
    verifyRelay(10, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::2"),
                OptionBuffer(), relay_id, remote_id, options);

    // Second packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Second lease is lease 4.

    // Verify client id.
    verifyClientId(cid2_, options);

    // Verify CLTT.
    verifyCLTT(100, options);

    // Verify IAADDR.
    verifyIAADDR(lease4->addr_, options);

    // Third packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // Third lease is lease 5.

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(300, options);

    // Verify IAADDR.
    verifyIAADDR(lease5->addr_, options);

    // Verify relay data.
    DuidPtr relay_id2(new DUID(vector<uint8_t>(7, 0x65)));
    vector<uint8_t> remote_id2 = { 1, 2, 3, 4, 5, 8 };
    verifyRelay(2, IOAddress("2001:db8:2::3"), IOAddress("2001:db8:2::4"),
                OptionBuffer(), relay_id2, remote_id2, options);

    // Forth packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // Forth lease is pd_lease.

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(50, options);

    // Verify IAPREFIX.
    verifyIAPREFIX(pd_lease->addr_, options);

    // Fifth packet is a LEASE_QUERY_DATA.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));

    // We should have D6O_CLIENT_DATA option.
    verifyClientData(rsp, options);
    EXPECT_EQ(4, options.size());

    // Last lease is pd_lease2,

    // Verify client id.
    verifyClientId(cid2_, options);

    // Verify CLTT.
    verifyCLTT(50, options);

    // Verify IAPREFIX.
    verifyIAPREFIX(pd_lease2->addr_, options);

    // Finished.
    verifyDone();
}

template <typename TestLeaseMgrType> void
    BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::verifyByLinkAddressMultipleSubnets(size_t page_size) {
    createBulkLeaseQueryService(page_size);

    // Create some subnets.
    CfgMgr& cfg_mgr = CfgMgr::instance();
    CfgSubnets6Ptr subnets = cfg_mgr.getCurrentCfg()->getCfgSubnets6();

    Subnet6Ptr subnet10(new Subnet6(IOAddress("2001:db8:1::"), 64,
                                    1200, 2400, 3600, 3600, 10));
    subnets->add(subnet10);

    Subnet6Ptr subnet11(new Subnet6(IOAddress("2001:db8:1::1"), 64,
                                    1200, 2400, 3600, 3600, 11));
    subnets->add(subnet11);

    Subnet6Ptr subnet12(new Subnet6(IOAddress("2001:db8:1::2"), 64,
                                    1200, 2400, 3600, 3600, 12));
    subnets->add(subnet12);

    Subnet6Ptr subnet13(new Subnet6(IOAddress("2001:db8:1::3"), 64,
                                    1200, 2400, 3600, 3600, 13));
    subnets->add(subnet13);

    Subnet6Ptr subnet14(new Subnet6(IOAddress("2001:db8:1::4"), 64,
                                    1200, 2400, 3600, 3600, 14));
    subnets->add(subnet14);

    // Create some leases.
    time_t now = time(0);
    Lease6Ptr lease1 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                                subnet12, cid1_, now - 100, user_context1_);
    Lease6Ptr lease2 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:1::2"),
                                subnet12, cid2_, now - 100, user_context2_);
    Lease6Ptr lease3 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:1::3"),
                                subnet13, cid1_, now - 100, user_context1_);
    // In range but not in a matching subnet.
    Lease6Ptr lease4 = addLease(Lease::TYPE_NA, IOAddress("2001:db8:1::4"),
                                subnet2_, cid2_, now - 100, user_context2_);
    Lease6Ptr pd_lease1 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                   subnet11, cid1_, now - 100, user_context1_);
    Lease6Ptr pd_lease2 = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:2::"),
                                   subnet13, cid2_, now - 100, user_context2_);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByLinkAddr(IOAddress("2001:db8:1::100"));

    // Process the query
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY with a successful
    // status option.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
    EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));
    checkStatus(rsp, STATUS_Success, "active lease(s) found");

    // We should get 5 LEASE_QUERY_DATA.
    for (unsigned i = 0; i < 5; ++i) {
        if (i > 0) {
            rsp = getSentPacket();
            ASSERT_TRUE(rsp);
            ASSERT_EQ(DHCPV6_LEASEQUERY_DATA, rsp->getType());
            EXPECT_FALSE(rsp->getOption(D6O_STATUS_CODE));
            EXPECT_FALSE(rsp->getOption(D6O_LQ_CLIENT_LINK));
            EXPECT_FALSE(rsp->getOption(D6O_LQ_RELAY_DATA));
        }
        OptionCollection options;
        verifyClientData(rsp, options);
        EXPECT_EQ(4, options.size());

        // Verify CLTT.
        verifyCLTT(100, options);

        switch (i) {
        case 0:
            // First lease is pd_lease1.
            verifyClientId(cid1_, options);
            verifyIAPREFIX(pd_lease1->addr_, options);
            break;
        case 1:
            // Second lease is lease1.
            verifyClientId(cid1_, options);
            verifyIAADDR(lease1->addr_, options);
            break;
        case 2:
            // Third lease is lease2.
            verifyClientId(cid2_, options);
            verifyIAADDR(lease2->addr_, options);
            break;
        case 3:
            // Forth lease is lease3.
            verifyClientId(cid1_, options);
            verifyIAADDR(lease3->addr_, options);
            break;
        default:
            // Last lease is pd_lease2.
            verifyClientId(cid2_, options);
            verifyIAPREFIX(pd_lease2->addr_, options);
            break;
        }
    }

    // Finished.
    verifyDone();
}

// This test verifies that by link address with unknown link returns an error.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressUnknownLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:111::"));
}

// This test verifies that by link address with a link without lease returns nothing.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressEmptyLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:3::"));
}

// This test verifies that by link address with a link without active lease
// return nothing.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressNoActive) {
    verifyByLinkAddress(10, IOAddress("2001:db8:2::"));
}

// This test verifies that by link address with a link and 10 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:4::1"));
}

// This test verifies that by link address with a link and 2 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressLink2) {
    verifyByLinkAddress(2, IOAddress("2001:db8:4::1"));
}

// This test verifies that by link address with a link and 1 item pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressLink1) {
    verifyByLinkAddress(1, IOAddress("2001:db8:4::1"));
}

// This test verifies that by link address with multiple subnets and 10 item
// pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressMultiple) {
    verifyByLinkAddressMultipleSubnets(10);
}

// This test verifies that by link address with multiple subnets and 2 item
// pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressMultiple2) {
    verifyByLinkAddressMultipleSubnets(2);
}

// This test verifies that by link address with multiple subnets and 1 item
// pages works.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, byLinkAddressMultiple1) {
    verifyByLinkAddressMultipleSubnets(1);
}

template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::verifyNoExtendedInfoTables(
    bool enabled) {

    if (!enabled) {
        LeaseMgrFactory::destroy();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.createSchema();
        LeaseMgrFactory::create(test_lease_mgr.dbAccess() +
                                " extended-info-tables=false");
    }

    time_t now = time(0);

    // Create a lease.
    Lease6Ptr lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::100"),
                               subnet2_, cid1_, now - 100, user_context1_);

    // Make the by-relay-id lease query.
    DuidPtr relay_id(new DUID(vector<uint8_t>(8, 0x64)));
    Pkt6Ptr lq = makeQueryByRelayId(relay_id);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY.
    Pkt6Ptr rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    if (enabled) {
        // Enabled: success.
        checkStatus(rsp, STATUS_Success, "active lease(s) found");
        // DHCPV6_LEASEQUERY_DONE.
        rsp = getSentPacket();
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPV6_LEASEQUERY_DONE, rsp->getType());
    } else {
        // Disabled: not allowed.
        checkStatus(rsp, STATUS_NotAllowed,
                    "extended info tables are disabled");
        // Nothing.
        rsp = getSentPacket();
        EXPECT_FALSE(rsp);
    }

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Make the by-remote-id lease query.
    vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
    lq = makeQueryByRemoteId(remote_id);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    if (enabled) {
        // Enabled: success.
        checkStatus(rsp, STATUS_Success, "active lease(s) found");
        // DHCPV6_LEASEQUERY_DONE.
        rsp = getSentPacket();
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPV6_LEASEQUERY_DONE, rsp->getType());
    } else {
        // Disabled: not allowed.
        checkStatus(rsp, STATUS_NotAllowed,
                    "extended info tables are disabled");
        // Nothing.
        rsp = getSentPacket();
        EXPECT_FALSE(rsp);
    }

    // Reset test environment.
    io_service_.reset(new IOService());
    flushSentPackets();

    // Make the by-link-addr lease query.
    lq = makeQueryByLinkAddr(lease->addr_);

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

    // We should have generated a LEASE_QUERY_REPLY.
    rsp = getSentPacket();
    ASSERT_TRUE(rsp);
    ASSERT_EQ(DHCPV6_LEASEQUERY_REPLY, rsp->getType());
    if (enabled) {
        // Enabled: success.
        checkStatus(rsp, STATUS_Success, "active lease(s) found");
        // DHCPV6_LEASEQUERY_DONE.
        rsp = getSentPacket();
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPV6_LEASEQUERY_DONE, rsp->getType());
    } else {
        // Disabled: not allowed.
        checkStatus(rsp, STATUS_NotAllowed,
                    "extended info tables are disabled");
        // Nothing.
        rsp = getSentPacket();
        EXPECT_FALSE(rsp);
    }
}

// This test verifies that without extended info tables new query types
// return not allowed.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, noExtendedInfoTables) {
    verifyNoExtendedInfoTables(false);
}

// This test verifies that with extended info tables new query types
// return success.
TEST_F(MemfileBulkLeaseQuery6ProcessTest, extendedInfoTables) {
    verifyNoExtendedInfoTables(true);
}

// This test verifies that BulkLeaseQuery6 utilizes the configured
// prefix length list to find PD leases.
template <typename TestLeaseMgrType> void
BaseBulkLeaseQuery6ProcessTest<TestLeaseMgrType>::testQueryByIpAddressActivePDLease() {
    createBulkLeaseQueryService(10, "[ 80 ]");

    time_t now = time(0);

    // Create some leases.
    Lease6Ptr active_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::120"),
                                      subnet2_, cid1_, now - 100);

    Lease6Ptr expired_lease = addLease(Lease::TYPE_NA, IOAddress("2001:db8:2::115"),
                                       subnet2_, cid1_, now - 4000, "");

    Lease6Ptr pd_lease = addLease(Lease::TYPE_PD, IOAddress("3001:0:0:0:1::"),
                                  subnet4_, cid1_, now - 100);

    // Make the lease query.
    Pkt6Ptr lq = makeQueryByIpAddress(IOAddress("3001:0:0:0:1::100"));

    // Process the query.
    ASSERT_NO_THROW_LOG(processBulkQuery(lq));

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
    OptionCollection options;
    verifyClientData(rsp, options);
    EXPECT_EQ(3, options.size());

    // Verify client id.
    verifyClientId(cid1_, options);

    // Verify CLTT.
    verifyCLTT(100, options);

    // Now let's check we should have one TYPE_NA lease.
    verifyIAPREFIX(pd_lease->addr_, options);

    // There should be a DHCPV6_LEASEQUERY_DONE message.
    verifyDone();
}

TEST_F(MemfileBulkLeaseQuery6ProcessTest, queryByIpAddressActivePDLease) {
    testQueryByIpAddressActivePDLease();
}

#ifdef HAVE_MYSQL
/// @brief MySQL test fixture.
class MySQLBulkLeaseQuery6ProcessTest : public
    BaseBulkLeaseQuery6ProcessTest<MySQLTestLeaseMgr> {
};

TEST_F(MySQLBulkLeaseQuery6ProcessTest, queryByIpAddressNoActiveLease) {
    testQueryByIpAddressNoActiveLease();
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, queryByIpAddressActiveLease) {
    testQueryByIpAddressActiveLease();
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, queryByClientIdNoActiveLease) {
    testQueryByClientIdNoActiveLease();
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, queryByClientIdMultipleLinks) {
    testQueryByClientIdMultipleLinks();
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, queryByClientIdActiveLeases) {
    testQueryByClientIdActiveLeases();
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdUnknownLink) {
    verifyByRelayId(10, IOAddress("2001:db8:111::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdEmptyLink) {
    verifyByRelayId(10, IOAddress("2001:db8:3::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdNoLink) {
    verifyByRelayId(10, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdNoLink2) {
    verifyByRelayId(2, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdNoLink1) {
    verifyByRelayId(1, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdLink) {
    verifyByRelayId(10, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdLink2) {
    verifyByRelayId(2, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRelayIdLink1) {
    verifyByRelayId(1, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdUnknownLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:111::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdEmptyLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:3::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdNoLink) {
    verifyByRemoteId(10, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdNoLink2) {
    verifyByRemoteId(2, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdNoLink1) {
    verifyByRemoteId(1, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdLink2) {
    verifyByRemoteId(2, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byRemoteIdLink1) {
    verifyByRemoteId(1, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressUnknownLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:111::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressEmptyLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:3::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressNoActive) {
    verifyByLinkAddress(10, IOAddress("2001:db8:2::"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressLink2) {
    verifyByLinkAddress(2, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressLink1) {
    verifyByLinkAddress(1, IOAddress("2001:db8:4::1"));
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressMultiple) {
    verifyByLinkAddressMultipleSubnets(10);
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressMultiple2) {
    verifyByLinkAddressMultipleSubnets(2);
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, byLinkAddressMultiple1) {
    verifyByLinkAddressMultipleSubnets(1);
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, noExtendedInfoTables) {
    verifyNoExtendedInfoTables(false);
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, extendedInfoTables) {
    verifyNoExtendedInfoTables(true);
}

TEST_F(MySQLBulkLeaseQuery6ProcessTest, queryByIpAddressActivePDLease) {
    testQueryByIpAddressActivePDLease();
}
#endif

#ifdef HAVE_PGSQL
/// @brief PostgreSQL test fixture.
class PgSQLBulkLeaseQuery6ProcessTest : public
    BaseBulkLeaseQuery6ProcessTest<PgSQLTestLeaseMgr> {
};

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, queryByIpAddressNoActiveLease) {
    testQueryByIpAddressNoActiveLease();
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, queryByIpAddressActiveLease) {
    testQueryByIpAddressActiveLease();
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, queryByClientIdNoActiveLease) {
    testQueryByClientIdNoActiveLease();
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, queryByClientIdMultipleLinks) {
    testQueryByClientIdMultipleLinks();
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, queryByClientIdActiveLeases) {
    testQueryByClientIdActiveLeases();
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdUnknownLink) {
    verifyByRelayId(10, IOAddress("2001:db8:111::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdEmptyLink) {
    verifyByRelayId(10, IOAddress("2001:db8:3::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdNoLink) {
    verifyByRelayId(10, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdNoLink2) {
    verifyByRelayId(2, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdNoLink1) {
    verifyByRelayId(1, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdLink) {
    verifyByRelayId(10, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdLink2) {
    verifyByRelayId(2, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRelayIdLink1) {
    verifyByRelayId(1, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdUnknownLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:111::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdEmptyLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:3::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdNoLink) {
    verifyByRemoteId(10, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdNoLink2) {
    verifyByRemoteId(2, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdNoLink1) {
    verifyByRemoteId(1, IOAddress::IPV6_ZERO_ADDRESS());
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdLink) {
    verifyByRemoteId(10, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdLink2) {
    verifyByRemoteId(2, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byRemoteIdLink1) {
    verifyByRemoteId(1, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressUnknownLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:111::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressEmptyLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:3::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressNoActive) {
    verifyByLinkAddress(10, IOAddress("2001:db8:2::"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressLink) {
    verifyByLinkAddress(10, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressLink2) {
    verifyByLinkAddress(2, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressLink1) {
    verifyByLinkAddress(1, IOAddress("2001:db8:4::1"));
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressMultiple) {
    verifyByLinkAddressMultipleSubnets(10);
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressMultiple2) {
    verifyByLinkAddressMultipleSubnets(2);
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, byLinkAddressMultiple1) {
    verifyByLinkAddressMultipleSubnets(1);
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, noExtendedInfoTables) {
    verifyNoExtendedInfoTables(false);
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, extendedInfoTables) {
    verifyNoExtendedInfoTables(true);
}

TEST_F(PgSQLBulkLeaseQuery6ProcessTest, queryByIpAddressActivePDLease) {
    testQueryByIpAddressActivePDLease();
}
#endif

}
