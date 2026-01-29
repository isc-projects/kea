// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <radius.h>
#include <radius_access.h>
#include <radius_utils.h>
#include <attribute_test.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service_mgr.h>
#include <asiolink/udp_socket.h>
#include <cryptolink/crypto_hash.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcp/testutils/pkt_captures.h>
#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <atomic>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::radius;
using namespace isc::stats;
using namespace isc::test;
using namespace isc::util;

extern "C" {
extern int dhcp4_srv_configured(CalloutHandle& handle);
extern int dhcp6_srv_configured(CalloutHandle& handle);
extern int subnet4_select(CalloutHandle& handle);
extern int subnet6_select(CalloutHandle& handle);
}

namespace {

struct TestHooks {
    int hook_index_dhcp4_srv_configured_;
    int hook_index_dhcp6_srv_configured_;
    int hook_index_subnet4_select_;
    int hook_index_subnet6_select_;

    TestHooks() {
        hook_index_dhcp4_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
        hook_index_dhcp6_srv_configured_ = HooksManager::registerHook("dhcp6_srv_configured");
        hook_index_subnet4_select_ = HooksManager::registerHook("subnet4_select");
        hook_index_subnet6_select_ = HooksManager::registerHook("subnet6_select");
    }
};

TestHooks Hooks;

/// @brief RAII object for enabling multi-threading for its lifetime.
struct MultiThreaded {
    /// @brief Constructor.
    ///
    /// RadiusImpl.init() inspects the staging configuration. So set it there as well.
    MultiThreaded() {
        // Default config is MT so use ElementPtr().
        CfgMgr::instance().getStagingCfg()->setDHCPMultiThreading(ElementPtr());
        MultiThreadingMgr::instance().setMode(true);
    }
    ~MultiThreaded() {
        MultiThreadingMgr::instance().setMode(false);
    }
};

/// @brief RAII object for disabling multi-threading for its lifetime.
struct SingleThreaded {
    /// @brief Constructor.
    ///
    /// RadiusImpl.init() inspects the staging configuration. So set it there as well.
    SingleThreaded() {
        CfgMgr::instance().getStagingCfg()->setDHCPMultiThreading(
            Element::fromJSON(R"({ "enable-multi-threading": false })"));
        MultiThreadingMgr::instance().setMode(false);
    }
};

/// @brief Test dump cache class.
class TestHostCache : public MemHostDataSource, public CacheHostDataSource {
public:
    /// Override add
    ///
    /// Always throws.
    ///
    /// @param host host to be added.
    /// @throw NotImplemented.
    void add(const HostPtr& host) override {
        isc_throw(NotImplemented,
                  "add is not implemented: " << host->toText());
    }

    /// Insert the host into the store.
    ///
    /// @param host host to be added
    /// @param overwrite does nothing.
    size_t insert(const ConstHostPtr& host, bool /* overwrite */) override {
        MultiThreadingLock lock(mutex_);
        HostPtr host_copy(new Host(*host));
        store_.push_back(host_copy);
        return (0);
    }

    /// Remove host from the store.
    ///
    /// @param host host to be removed
    /// @return true if removed, false if not found.
    bool remove(const HostPtr& host) override {
        MultiThreadingLock lock(mutex_);
        for (auto h = store_.begin(); h != store_.end(); ++h) {
            if (*h == host) {
                store_.erase(h);
                return (true);
            }
        }
        return (false);
    }

    /// Flush
    ///
    /// @throw NotImplemented
    void flush(size_t /*count*/) override {
        isc_throw(NotImplemented, "flush is not implemented");
    }

    /// Size
    ///
    /// @return size of the store
    size_t size() const override {
        return (MemHostDataSource::size());
    }

    /// Capacity
    ///
    /// @return always 0
    size_t capacity() const override {
        return (0);
    }

    /// Type
    ///
    /// @return "cache" string
    string getType() const override {
        return ("cache");
    }
};

/// @brief TestHostCache pointer type
typedef boost::shared_ptr<TestHostCache> TestHostCachePtr;

/// Server.
const char SERVER_ADDRESS[] = "127.0.0.1";
const unsigned short SERVER_PORT = 11812;

/// Config.
const char* CONFIG =
"{\n"
"    \"access\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 11812,\n"
"            \"secret\": \"foo\" } ] },\n"
"    \"identifier-type4\": \"flex-id\",\n"
"    \"identifier-type6\": \"flex-id\",\n"
"    \"retries\": 0,\n"
"    \"thread-pool-size\": 4,"
"    \"timeout\": 4\n"
"}"
;

constexpr long GENERAL_TIMEOUT = 10000;
constexpr long SERVER_RECEIVE_TIMEOUT = 2000;

/// @brief Thread pointer type.
typedef boost::shared_ptr<thread> ThreadPtr;

/// @brief Test fixture for testing access code.
class AccessTest : public radius::test::AttributeTest {
public:

    /// @brief Constructor.
    AccessTest() : impl_(RadiusImpl::instance()),
                   cache_(new TestHostCache()),
                   service_(new IOService()),
                   ready_(false), close_(false), finished_(false),
                   expected_received_(1), unparked_(0) {
        // Cache stuff
        HostMgr::create();
        auto cacheFactory = [this](const DatabaseConnection::ParameterMap&) {
            return (cache_);
        };
        HostDataSourceFactory::registerFactory("cache", cacheFactory);
        HostMgr::addBackend("type=cache");

        // Initialize.
        ElementPtr config = Element::fromJSON(CONFIG);
        impl_.init(config);
        impl_.setIOService(service_);
        impl_.setIOContext(service_);
        impl_.cache_ = cache_;
        HooksManager::clearParkingLots();
    }

    /// @brief Destructor.
    virtual ~AccessTest() {
        impl_.reset();

        // Purge remaining handlers.
        try {
            service_->poll();
        } catch (...) {
            // Ignoring exceptions.
        }
        service_->stop();

        if (thread_) {
            thread_->join();
            thread_.reset();
        }

        HooksManager::clearParkingLots();
        HostDataSourceFactory::deregisterFactory("cache");
        cache_.reset();

        // As a best practice, call any remaining handlers.
        service_->stopAndPoll();

        CfgMgr::instance().clear();
    }

    /// @brief Thread server function.
    void server();

    /// @brief Thread not servicing server function.
    void dummyServer();

    /// @brief Verify that the select subnet hook looks at host cache - IPv4.
    ///
    /// Note the best (and only) way to get a visible side effect is to use a pool.
    void testHostPool4(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - IPv6.
    ///
    /// Note the best (and only) way to get a visible side effect is to use a pool.
    void testHostPool6(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - IPv4
    /// with subnet reselect.
    void testHostReselect4(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - IPv6
    /// with subnet reselect.
    void testHostReselect6(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - IPv4.
    ///
    /// Use both a reservation and a pool: the reservation is looked at first
    /// so the pool has no effect...
    void testHostReservation4(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - IPv6.
    /// Use both a reservation and a pool: the reservation is looked at first
    /// so the pool has no effect...
    void testHostReservation6(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - prefix.
    /// Use both a reservation and a pool: the reservation is looked at first
    /// so the pool has no effect...
    void testHostReservation6Prefix(uint32_t const test_id = 12345);

    /// @brief Verify that the select subnet hook looks at host cache - both
    /// IPv6 address and delegated prefix.
    /// Use both a reservation and a pool: the reservation is looked at first
    /// so the pool has no effect...
    void testHostReservation6Both(uint32_t const test_id = 12345);

    /// @brief Verify that if two conflicting queries are tried the second
    /// will be dropped.
    void testTwoQueries4(ConstSubnet4Ptr subnet,
                         uint32_t const test_id = 12345);

    /// @brief Verify that if two conflicting queries are tried the second
    /// will be dropped.
    void testTwoQueries6(ConstSubnet6Ptr subnet,
                         uint32_t const test_id = 12345);

    /// @brief Verify that the max-pending-requests limit is enforced.
    void testTooManyQueries4(ConstSubnet4Ptr subnet, uint32_t const test_id = 12345);

    /// @brief Verify that the max-pending-requests limit is enforced.
    void testTooManyQueries6(ConstSubnet6Ptr subnet, uint32_t const test_id = 12345);

    /// @brief Verify the hook calls the server when it can't get a host - IPv4.
    void testNoHost4(ConstSubnet4Ptr subnet, uint32_t const test_id = 12345);

    /// @brief Verify the result of running testNoHost4.
    void checkNoHost4Results(ConstSubnet4Ptr subnet, uint32_t const test_id = 12345);

    /// @brief Verify the hook calls the server when it can't get a host - IPv6.
    void testNoHost6(ConstSubnet6Ptr subnet, uint32_t const test_id = 12345);

    /// @brief Verify the result of running testNoHost6.
    void checkNoHost6Results(ConstSubnet6Ptr subnet, uint32_t const test_id = 12345);

    /// @brief Verify that failing to get identifier makes SKIP status - IPv4.
    void testNoIdentifier4(uint32_t const test_id = 12345);

    /// @brief Verify that failing to get identifier makes SKIP status - IPv6.
    void testNoIdentifier6(uint32_t const test_id = 12345);

    /// @brief Governs multi-threading core settings.
    ///
    /// Gets constructed and destructed by default.
    SingleThreaded st_;

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    /// @brief Test host cache.
    TestHostCachePtr cache_;

    /// @brief IO service.
    IOServicePtr service_;

    /// @brief Thread.
    ThreadPtr thread_;

    /// @brief ready flag.
    atomic<bool> ready_;

    /// @brief close flag.
    atomic<bool> close_;

    /// @brief Whether the simulated RADIUS server has finished processing.
    atomic<bool> finished_;

    /// @brief Number of expected RADIUS responses before stopping the server.
    uint16_t expected_received_;

    /// @brief Mutex to protect various code blocks in tests that are normally
    /// not executed concurrently in real code.
    mutex mutex_;

    /// @brief Histogram of next steps set after callouts.
    unordered_map<CalloutHandle::CalloutNextStep, int> steps_;

    /// @brief Number of unparked packets.
    uint32_t unparked_;

    /// @brief Collection of packets used in processing that is inspected afterwards.
    vector<PktPtr> packets_;

    /// @brief Collection of error codes used when receiving a RADIUS request
    /// that is then inspected.
    vector<boost::system::error_code> error_codes_;

    /// @brief Collection of buffers used when receiving a RADIUS request
    /// that is then inspected. Also used when sending RADIUS responses.
    vector<vector<uint8_t>> receive_buffers_;

    /// @brief Collection of buffer sizes used when receiving a RADIUS request
    /// that is then inspected.
    vector<size_t> sizes_;
};

/// @brief Fixture for multi-threading tests.
///
/// Adds MT functionality on top of @ref AccessTest.
struct MTAccessTest : AccessTest {
    /// @brief Constructor.
    MTAccessTest() : mt_(new MultiThreaded()) {
        // Reserve two hook libraries, in case host cache is added too.
        boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>(2));
        CalloutHandle handle(manager);

        // Call dhcp*_srv_configured() for startServices().
        handle.setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        switch(CfgMgr::instance().getFamily()) {
            case AF_INET:
                handle.setCurrentHook(Hooks.hook_index_dhcp4_srv_configured_);
                dhcp4_srv_configured(handle);
                break;
            case AF_INET6:
                handle.setCurrentHook(Hooks.hook_index_dhcp6_srv_configured_);
                dhcp6_srv_configured(handle);
                break;
            default:
                // Lambda to avoid error: constructor 'AccessTest' must not return void expression
                []() { FAIL() << "impossible"; }();
                break;
        }
        IOServiceMgr::instance().unregisterIOService(service_);

        // Run one to run the handler that starts the RADIUS thread pool.
        EXPECT_NO_THROW_LOG(service_->runOne());

        // Start the core thread pool with 4 threads.
        // Pause the thread pool and resume only after work items have
        // been added to it to increase the chance of finding race conditions.
        EXPECT_EQ(4, impl_.thread_pool_size_);
        EXPECT_EQ(4, impl_.thread_pool_->getPoolSize());
        EXPECT_NO_THROW_LOG(thread_pool_.start(impl_.thread_pool_size_));
        EXPECT_NO_THROW_LOG(thread_pool_.pause());

        // By default run the test function 10 times.
        expected_received_ = 10;
    }

    /// @brief Destructor.
    ~MTAccessTest() {
        // Join threads if not already joined.
        if (thread_pool_.enabled()) {
            EXPECT_NO_THROW_LOG(thread_pool_.wait());
            EXPECT_NO_THROW_LOG(thread_pool_.stop());
        }

        impl_.reset();
        mt_.reset();
        // As a best practice, call any remaining handlers.
        service_->stopAndPoll();
    }

    /// @brief Queue up multiple test functions to run concurrently.
    ///
    /// @param test_function the function that is being tested.
    void run(function<void(uint32_t const)> test_function) {
        // Fill the thread pool.
        for (uint16_t i = 0; i < expected_received_; ++i) {
            boost::shared_ptr<function<void()>> const work(
                boost::make_shared<function<void()>>(bind(test_function, i)));
            EXPECT_NO_THROW_LOG(thread_pool_.add(work));
        }
        EXPECT_NO_THROW_LOG(thread_pool_.resume());
    }

    /// @brief Governs multi-threading core settings.
    ///
    /// Gets constructed and destructed by default.
    std::unique_ptr<MultiThreaded> mt_;

    /// @brief Simulates the core thread pool.
    ///
    /// Used to park packets and call callouts.
    ThreadPool<function<void()>> thread_pool_;
};

/// @brief Server method running in a thread.
void
AccessTest::server() {
    // Get private service.
    IOServicePtr service(new IOService());

    // Get the socket.
    boost::asio::ip::udp::socket server_socket(service->getInternalIOService());
    boost::system::error_code ec;
    server_socket.open(boost::asio::ip::udp::v4(), ec);
    ASSERT_FALSE(ec) << "udp::v4 failed: " << ec.message();

    // Get the address.
    boost::asio::ip::address server_address =
        boost::asio::ip::make_address(SERVER_ADDRESS, ec);
    ASSERT_FALSE(ec) << "make_address failed: " << ec.message();

    // Get the endpoint.
    boost::asio::ip::udp::endpoint server_endpoint =
        boost::asio::ip::udp::endpoint(server_address, SERVER_PORT);

    // Bind the socket.
    server_socket.bind(server_endpoint, ec);
    ASSERT_FALSE(ec) << "bind failed: " << ec.message();

    // Notify the server is ready.
    ready_ = true;

    // Set the timer for timeout.
    IntervalTimer timer(service);
    atomic<bool> timeout;
    timeout = false;
    auto timeout_handler = [&timeout]() {
        timeout = true;
        FAIL() << "timeout";
    };
    timer.setup(timeout_handler, SERVER_RECEIVE_TIMEOUT,
                IntervalTimer::ONE_SHOT);

    // Get the requests.
    auto receive_handler = [this](boost::system::error_code erc, size_t size) {
        lock_guard<mutex> lock(mutex_);
        error_codes_.push_back(erc);
        sizes_.push_back(size);
    };
    vector<boost::asio::ip::udp::endpoint> clients(expected_received_);
    for (uint16_t i = 0; i < expected_received_; ++i) {
        receive_buffers_.push_back(vector<uint8_t>(4096));
        server_socket.async_receive_from(
                 boost::asio::buffer(&receive_buffers_[i][0],
                                     receive_buffers_[i].size()),
                 clients[i], receive_handler);
    }

    // Get the requests or a timeout. Don't wait forever.
    system_clock::time_point start(system_clock::now());
    while (!timeout && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        service->poll();
        {
            lock_guard<mutex> lock(mutex_);
            if (expected_received_ <= error_codes_.size()) {
                break;
            }
        }
        this_thread::sleep_for(1ms);
    }
    EXPECT_EQ(expected_received_, error_codes_.size());

    // Stop timer.
    timer.cancel();

    EXPECT_FALSE(timeout);

    for (uint16_t i = 0; i < expected_received_; ++i) {
        ASSERT_LT(i, error_codes_.size());
        boost::system::error_code error_code(error_codes_[i]);
        ASSERT_LT(i, sizes_.size());
        size_t const received_size(sizes_[i]);

        // Sanity check the request.
        EXPECT_FALSE(error_code) << "request failed: " << error_code.message();
        ASSERT_LE(AUTH_HDR_LEN, received_size) << "too short";
        receive_buffers_[i].resize(received_size);
        EXPECT_EQ(PW_ACCESS_REQUEST, receive_buffers_[i][0]);

        // Build response.
        string pool = "foobar";
        size_t send_size = AUTH_HDR_LEN + 2 + pool.size();
        vector<uint8_t> send_buffer(send_size);
        memmove(&send_buffer[0], &receive_buffers_[i][0], AUTH_HDR_LEN);
        send_buffer[0] = PW_ACCESS_ACCEPT;
        send_buffer[2] = send_buffer.size() >> 8;
        send_buffer[3] = send_buffer.size() & 0xff;
        send_buffer[AUTH_HDR_LEN] = PW_FRAMED_POOL;
        send_buffer[AUTH_HDR_LEN + 1] = send_size - AUTH_HDR_LEN;
        memmove(&send_buffer[AUTH_HDR_LEN + 2], pool.c_str(), pool.size());

        // Compute the authenticator.
        string secret = "foo";
        vector<unsigned char> auth_input(send_size + secret.size());
        memmove(&auth_input[0], &send_buffer[0], send_size);
        memmove(&auth_input[send_size], secret.c_str(), secret.size());
        OutputBuffer auth_output(AUTH_VECTOR_LEN);
        digest(&auth_input[0], auth_input.size(), isc::cryptolink::MD5,
               auth_output, AUTH_VECTOR_LEN);
        memmove(&send_buffer[4], auth_output.getData(), AUTH_VECTOR_LEN);

        // Send the response.
        size_t sent_size =
            server_socket.send_to(boost::asio::buffer(&send_buffer[0], send_buffer.size()),
                                  clients[i], 0, error_code);
        ASSERT_FALSE(error_code) << "send_to failed: " << error_code.message();
        EXPECT_EQ(send_buffer.size(), sent_size);
    }

    // Close the socket.
    if (server_socket.is_open()) {
        EXPECT_NO_THROW(server_socket.close());
    }

    // As a best practice, call any remaining handlers.
    service->stopAndPoll();

    // Finished!
    finished_ = true;
}

/// @brief Not serving server method running in a thread.
void
AccessTest::dummyServer() {
    // Get private service.
    IOServicePtr service(new IOService());

    // Get the socket.
    boost::asio::ip::udp::socket server_socket(service->getInternalIOService());
    boost::system::error_code ec;
    server_socket.open(boost::asio::ip::udp::v4(), ec);
    ASSERT_FALSE(ec) << "udp::v4 failed: " << ec.message();

    // Get the address.
    boost::asio::ip::address server_address =
        boost::asio::ip::make_address(SERVER_ADDRESS, ec);
    ASSERT_FALSE(ec) << "make_address failed: " << ec.message();

    // Get the endpoint.
    boost::asio::ip::udp::endpoint server_endpoint =
        boost::asio::ip::udp::endpoint(server_address, SERVER_PORT);

    // Bind the socket.
    server_socket.bind(server_endpoint, ec);
    ASSERT_FALSE(ec) << "bind failed: " << ec.message();

    // Notify the server is ready.
    ready_ = true;

    // Set the timer for timeout.
    IntervalTimer timer(service);
    atomic<bool> timeout;
    timeout = false;
    auto timeout_handler = [&timeout]() {
        timeout = true;
        FAIL() << "timeout";
    };
    timer.setup(timeout_handler, SERVER_RECEIVE_TIMEOUT,
                IntervalTimer::ONE_SHOT);

    // Get a timeout or the finished flag. Don't wait forever.
    system_clock::time_point start(system_clock::now());
    while (!timeout && !close_ &&
           system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }

    // Stop timer.
    timer.cancel();

    EXPECT_FALSE(timeout);
    EXPECT_TRUE(close_);

    // Close the socket.
    if (server_socket.is_open()) {
        EXPECT_NO_THROW(server_socket.close());
    }

    // As a best practice, call any remaining handlers.
    service->stopAndPoll();

    // Finished!
    finished_ = true;
}

void
AccessTest::testHostPool4(uint32_t const test_id /* = 12345 */) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query4", pkt);
    ConstSubnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    handle->setArgument("subnet4", subnet);

    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id));
    pkt->addOption(option);

    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host(new Host(&id[1], id.size() - 1, impl_.id_type4_,
                          subnet->getID(), SUBNET_ID_UNUSED, addr4));
    ASSERT_TRUE(host);
    ElementPtr map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host->setContext(map);
    host->setNegative(true);
    ASSERT_EQ(0, cache_->insert(host, true));

    HooksManager::park("subnet4_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet4_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    EXPECT_TRUE(pkt->inClass("foobar"));

    subnet.reset();
    handle->getArgument("subnet4", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
}

void
AccessTest::testHostPool6(uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    ConstSubnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                       64, 1, 2, 3, 4, 1));
    handle->setArgument("subnet6", subnet);

    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host(new Host(&id[2], id.size() - 2, impl_.id_type6_,
                          SUBNET_ID_UNUSED, subnet->getID(), addr4));
    ASSERT_TRUE(host);
    ElementPtr map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host->setContext(map);
    host->setNegative(true);
    ASSERT_EQ(0, cache_->insert(host, true));

    HooksManager::park("subnet6_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    EXPECT_TRUE(pkt->inClass("foobar"));

    subnet.reset();
    handle->getArgument("subnet6", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("2001:db8::/64", subnet->toText());
}

void
AccessTest::testHostReselect4(uint32_t const test_id /* = 12345 */) {
    // Create an environment with 2 subnets:
    // - subnet-id 1
    // - subnet-id 2
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query4", pkt);
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 1));
    ConstSubnet4Ptr subnet4 = subnet1;
    handle->setArgument("subnet4", subnet4);
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 2));
    ASSERT_NE(subnet1->getID(), subnet2->getID());

    {
        lock_guard<mutex> lock(mutex_);
        if (CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll()->empty()) {
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);
        }
    }

    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id));
    pkt->addOption(option);

    // Add a subnet reselect cache entry for the host in subnet 1.
    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host1(new Host(&id[1], id.size() - 1, impl_.id_type4_,
                           subnet1->getID(), 0, addr4));
    ElementPtr map = Element::createMap();
    map->set("subnet-id",
             Element::create(static_cast<int64_t>(subnet2->getID())));
    host1->setContext(map);
    host1->setNegative(true);
    ASSERT_EQ(0, cache_->insert(host1, true));

    // Add a RADIUS with pool cache entry for the host in subnet 2.
    HostPtr host2(new Host(&id[1], id.size() - 1, impl_.id_type4_,
                           subnet2->getID(), 0, addr4));
    ASSERT_TRUE(host2);
    map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host2->setContext(map);
    host2->setNegative(true); // no reserved address nor hostname
    ASSERT_EQ(0, cache_->insert(host2, true));

    // Now call subnet4_select callout and check the second subnet is selected.
    // Note reselect is checked twice: on the return of host cache
    // (this code is tested here) and on the return of the handler
    // (same code with a few simplification).
    HooksManager::park("subnet4_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet4_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    ConstSubnet4Ptr subnet;
    handle->getArgument("subnet4", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(subnet2->getID(), subnet->getID());
    EXPECT_TRUE(pkt->inClass("foobar"));
}

void
AccessTest::testHostReselect6(uint32_t const test_id /* = 12345 */) {
    // Create an environment with 2 subnets:
    // - subnet-id 1
    // - subnet-id 2
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 1));
    ConstSubnet6Ptr subnet6 = subnet1;
    handle->setArgument("subnet6", subnet6);
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:0:2::"),
                                   64, 1, 2, 3, 4, 2));
    ASSERT_NE(subnet1->getID(), subnet2->getID());

    {
        lock_guard<mutex> lock(mutex_);
        if (CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll()->empty()) {
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);
        }
    }

    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    // Add a subnet reselect cache entry for the host in subnet 1.
    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host1(new Host(&id[2], id.size() - 2, impl_.id_type6_,
                           0, subnet1->getID(), addr4));
    ElementPtr map = Element::createMap();
    map->set("subnet-id",
             Element::create(static_cast<int64_t>(subnet2->getID())));
    host1->setContext(map);
    host1->setNegative(true);
    ASSERT_EQ(0, cache_->insert(host1, true));

    // Add a RADIUS with pool cache entry for the host in subnet 2.
    HostPtr host2(new Host(&id[2], id.size() - 2, impl_.id_type6_,
                           0, subnet2->getID(), addr4));
    ASSERT_TRUE(host2);
    map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host2->setContext(map);
    host2->setNegative(true); // no reserved address nor hostname
    ASSERT_EQ(0, cache_->insert(host2, true));

    // Now call subnet6_select callout and check the second subnet is selected.
    // Note reselect is checked twice: on the return of host cache
    // (this code is tested here) and on the return of the handler
    // (same code with a few simplification).
    HooksManager::park("subnet6_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    ConstSubnet6Ptr subnet;
    handle->getArgument("subnet6", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(subnet2->getID(), subnet->getID());
    EXPECT_TRUE(pkt->inClass("foobar"));

    subnet.reset();
    handle->getArgument("subnet6", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(2, subnet->getID());
    EXPECT_EQ("2001:db8:0:2::/64", subnet->toText());
}

void
AccessTest::testHostReservation4(uint32_t const test_id /* = 12345 */) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query4", pkt);
    ConstSubnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    handle->setArgument("subnet4", subnet);

    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id));
    pkt->addOption(option);

    IOAddress addr4 = IOAddress("192.0.2.1");
    HostPtr host(new Host(&id[1], id.size() - 1, impl_.id_type4_,
                          subnet->getID(), SUBNET_ID_UNUSED, addr4));
    ASSERT_TRUE(host);
    ElementPtr map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host->setContext(map);
    ASSERT_EQ(0, cache_->insert(host, true));

    HooksManager::park("subnet4_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet4_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    const ClientClasses& classes = pkt->getClasses();
    EXPECT_TRUE(classes.empty());

    subnet.reset();
    handle->getArgument("subnet4", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
}

void
AccessTest::testHostReservation6(uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    ConstSubnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                       64, 1, 2, 3, 4, 1));
    handle->setArgument("subnet6", subnet);

    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host(new Host(&id[2], id.size() - 2, impl_.id_type6_,
                          SUBNET_ID_UNUSED, subnet->getID(), addr4));
    ASSERT_TRUE(host);
    IOAddress addr6 = IOAddress("2001:db8::1235");
    ASSERT_NO_THROW(host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, addr6)));
    ElementPtr map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host->setContext(map);
    ASSERT_EQ(0, cache_->insert(host, true));

    HooksManager::park("subnet6_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    const ClientClasses& classes = pkt->getClasses();
    EXPECT_TRUE(classes.empty());

    subnet.reset();
    handle->getArgument("subnet6", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("2001:db8::/64", subnet->toText());
}

void
AccessTest::testHostReservation6Prefix(uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    ConstSubnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                       64, 1, 2, 3, 4, 1));
    handle->setArgument("subnet6", subnet);

    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    writeUint32(test_id, &id[4], 4);
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host(new Host(&id[2], id.size() - 2, impl_.id_type6_,
                          SUBNET_ID_UNUSED, subnet->getID(), addr4));
    ASSERT_TRUE(host);
    IOAddress pref = IOAddress("2001:db8:0:0:1::");
    ASSERT_NO_THROW(host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, pref, 64)));
    ElementPtr map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host->setContext(map);
    ASSERT_EQ(0, cache_->insert(host, true));

    HooksManager::park("subnet6_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    const ClientClasses& classes = pkt->getClasses();
    EXPECT_TRUE(classes.empty());

    subnet.reset();
    handle->getArgument("subnet6", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("2001:db8::/64", subnet->toText());
}

void
AccessTest::testHostReservation6Both(uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    ConstSubnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                       64, 1, 2, 3, 4, 1));
    handle->setArgument("subnet6", subnet);

    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    writeUint32(test_id, &id[4], 4);
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    HostPtr host(new Host(&id[2], id.size() - 2, impl_.id_type6_,
                          SUBNET_ID_UNUSED, subnet->getID(), addr4));
    ASSERT_TRUE(host);
    IOAddress addr6 = IOAddress("2001:db8::1235");
    ASSERT_NO_THROW(host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, addr6)));
    IOAddress pref = IOAddress("2001:db8:0:0:1::");
    ASSERT_NO_THROW(host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, pref, 64)));
    ElementPtr map = Element::createMap();
    AttributesPtr attrs(new Attributes());
    attrs->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    map->set("radius", attrs->toElement());
    host->setContext(map);
    ASSERT_EQ(0, cache_->insert(host, true));

    HooksManager::park("subnet6_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle->getStatus());
    const ClientClasses& classes = pkt->getClasses();
    EXPECT_TRUE(classes.empty());

    subnet.reset();
    handle->getArgument("subnet6", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("2001:db8::/64", subnet->toText());
}

void
AccessTest::testTwoQueries4(ConstSubnet4Ptr subnet, uint32_t const test_id /* = 12345 */) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id));
    pkt->addOption(option);

    HooksManager::park("subnet4_select", pkt, [&]() mutable {
        lock_guard<mutex> lock(mutex_);
        ++unparked_;
    });

    {
        CalloutHandlePtr handle = getCalloutHandle(pkt);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", pkt);
        handle->setArgument("subnet4", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet4_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, handle->getStatus());
    }

    Pkt4Ptr pkt2(new Pkt4(DHCPDISCOVER, test_id + 1));
    pkt2->addOption(option);

    HooksManager::park("subnet4_select", pkt2,
                       [] () { FAIL() << "unparked"; });
    {
        CalloutHandlePtr handle = getCalloutHandle(pkt2);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", pkt2);
        handle->setArgument("subnet4", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet4_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle->getStatus());
    }
}

void
AccessTest::testTwoQueries6(ConstSubnet6Ptr subnet, uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    HooksManager::park("subnet6_select", pkt, [&]() mutable {
        lock_guard<mutex> lock(mutex_);
        ++unparked_;
    });

    {
        CalloutHandlePtr handle = getCalloutHandle(pkt);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", pkt);
        handle->setArgument("subnet6", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet6_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, handle->getStatus());
    }

    Pkt6Ptr pkt2(new Pkt6(DHCPV6_SOLICIT, test_id + 1));
    pkt2->addOption(option);

    HooksManager::park("subnet6_select", pkt2,
                       [] () { FAIL() << "unparked"; });
    {
        CalloutHandlePtr handle = getCalloutHandle(pkt2);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", pkt2);
        handle->setArgument("subnet6", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet6_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle->getStatus());
    }
}

void
AccessTest::testTooManyQueries4(ConstSubnet4Ptr subnet, uint32_t const test_id /* = 12345 */) {
    impl_.auth_->max_pending_requests_ = 1;
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id));
    pkt->addOption(option);

    HooksManager::park("subnet4_select", pkt, [&]() mutable {
        lock_guard<mutex> lock(mutex_);
        ++unparked_;
    });

    {
        CalloutHandlePtr handle = getCalloutHandle(pkt);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", pkt);
        handle->setArgument("subnet4", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet4_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, handle->getStatus());
    }

    Pkt4Ptr pkt2(new Pkt4(DHCPDISCOVER, test_id + 1));
    vector<uint8_t> id2 = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id + 1, &id2[7], 4);
    OptionPtr option2(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id2));
    pkt2->addOption(option2);

    HooksManager::park("subnet4_select", pkt2,
                       [] () { FAIL() << "unparked"; });
    {
        CalloutHandlePtr handle = getCalloutHandle(pkt2);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query4", pkt2);
        handle->setArgument("subnet4", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet4_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle->getStatus());
    }
}

void
AccessTest::testTooManyQueries6(ConstSubnet6Ptr subnet, uint32_t const test_id /* = 12345 */) {
    impl_.auth_->max_pending_requests_ = 1;
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    HooksManager::park("subnet6_select", pkt, [&]() mutable {
        lock_guard<mutex> lock(mutex_);
        ++unparked_;
    });

    {
        CalloutHandlePtr handle = getCalloutHandle(pkt);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", pkt);
        handle->setArgument("subnet6", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet6_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, handle->getStatus());
    }

    Pkt6Ptr pkt2(new Pkt6(DHCPV6_SOLICIT, test_id + 1));
    vector<uint8_t> id2 = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id + 1, &id2[7], 4);
    OptionPtr option2(new Option(Option::V6, D6O_CLIENTID, id2));
    pkt2->addOption(option2);

    HooksManager::park("subnet6_select", pkt2,
                       [] () { FAIL() << "unparked"; });
    {
        CalloutHandlePtr handle = getCalloutHandle(pkt2);
        ScopedCalloutHandleState callout_handle_state(handle);
        handle->setArgument("query6", pkt2);
        handle->setArgument("subnet6", subnet);
        handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
        handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
        int ret(-1);
        ASSERT_NO_THROW(ret = subnet6_select(*handle));
        EXPECT_EQ(0, ret);
        EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle->getStatus());
    }
}

void
AccessTest::testNoHost4(ConstSubnet4Ptr subnet, uint32_t const test_id /* = 12345 */) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, id));
    pkt->addOption(option);

    HooksManager::park("subnet4_select", pkt, [&]() mutable {
        lock_guard<mutex> lock(mutex_);
        ++unparked_;
    });

    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query4", pkt);
    handle->setArgument("subnet4", subnet);
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet4_select(*handle));
    EXPECT_EQ(0, ret);

    // Collect handle states and packets.
    lock_guard<mutex> lock(mutex_);
    CalloutHandle::CalloutNextStep const status(handle->getStatus());
    size_t const count(steps_[status]);
    steps_[status] = count + 1;
    packets_.push_back(pkt);
}

void
AccessTest::checkNoHost4Results(ConstSubnet4Ptr subnet, uint32_t i /* = 12345 */) {
    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(i, &id[7], 4);
    ConstHostPtr host = HostMgr::instance().get4Any(subnet->getID(),
                                                    impl_.id_type4_,
                                                    &id[1], id.size() - 1);
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size() - 1, hid.size());
    EXPECT_EQ(0, memcmp(&id[1], &hid[0], hid.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(subnet->getID(), host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());

    for (PktPtr const& pkt : packets_) {
        EXPECT_TRUE(pkt->inClass("foobar"));

        CalloutHandlePtr handle = getCalloutHandle(pkt);
        ConstSubnet4Ptr subneth;
        EXPECT_NO_THROW(handle->getContext("subnet4", subneth));
        ASSERT_TRUE(subneth);
        EXPECT_EQ(1, subneth->getID());
    }
}

void
AccessTest::testNoHost6(ConstSubnet6Ptr subnet, uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(test_id, &id[7], 4);
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, id));
    pkt->addOption(option);

    HooksManager::park("subnet6_select", pkt, [&]() mutable {
        lock_guard<mutex> lock(mutex_);
        ++unparked_;
    });

    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    handle->setArgument("subnet6", subnet);
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);

    // Collect handle states and packets.
    lock_guard<mutex> lock(mutex_);
    CalloutHandle::CalloutNextStep const status(handle->getStatus());
    size_t const count(steps_[status]);
    steps_[status] = count + 1;
    packets_.push_back(pkt);
}

void
AccessTest::checkNoHost6Results(ConstSubnet6Ptr subnet, uint32_t i /* = 12345 */) {
    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00 };
    writeUint32(i, &id[7], 4);
    ConstHostPtr host = HostMgr::instance().get6Any(subnet->getID(),
                                                    impl_.id_type6_,
                                                    &id[2], id.size() - 2);
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size() - 2 , hid.size());
    EXPECT_EQ(0, memcmp(&id[2], &hid[0], hid.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(subnet->getID(), host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());

    for (PktPtr const& pkt : packets_) {
        EXPECT_TRUE(pkt->inClass("foobar"));

        CalloutHandlePtr handle = getCalloutHandle(pkt);
        ConstSubnet6Ptr subneth;
        EXPECT_NO_THROW(handle->getContext("subnet6", subneth));
        ASSERT_TRUE(subneth);
        EXPECT_EQ(1, subneth->getID());
    }
}

void
AccessTest::testNoIdentifier4(uint32_t const test_id /* = 12345 */) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query4", pkt);
    ConstSubnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    handle->setArgument("subnet4", subnet);

    HooksManager::park("subnet4_select", pkt,
                    [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet4_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet4_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle->getStatus());
    EXPECT_EQ(0, impl_.auth_->requests4_.size());

    subnet.reset();
    handle->getArgument("subnet4", subnet);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getID());
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
}

void
AccessTest::testNoIdentifier6(uint32_t const test_id /* = 12345 */) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, test_id));
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    ScopedCalloutHandleState callout_handle_state(handle);
    handle->setArgument("query6", pkt);
    ConstSubnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                       64, 1, 2, 3, 4, 1));
    handle->setArgument("subnet6", subnet);

    HooksManager::park("subnet6_select", pkt,
                       [] () { FAIL() << "unparked"; });
    handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    handle->setCurrentHook(Hooks.hook_index_subnet6_select_);
    int ret(-1);
    ASSERT_NO_THROW(ret = subnet6_select(*handle));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle->getStatus());
    EXPECT_EQ(0, impl_.auth_->requests6_.size());
}

/// Verify that getIdentifier handles correctly IPv4 packets using
/// captured discover.
TEST_F(AccessTest, getIdentifierDiscover) {
    // Get the discover from capture.
    Pkt4Ptr pkt = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(pkt->unpack());

    // Try standard case with hw-address.
    vector<uint8_t> id;
    string text;
    impl_.id_type4_ = Host::IDENT_HWADDR;
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("20:e5:2a:b8:15:14", text);

    // Try canonize case.
    impl_.canonical_mac_address_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("20-e5-2a-b8-15-14", text);

    // Try standard case with duid.
    impl_.id_type4_ = Host::IDENT_DUID;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", text);

    // Pop0 is for client-id only.
    impl_.clientid_pop0_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", text);

    // And printable too.
    impl_.clientid_printable_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", text);

    // Try standard case with circuit-id.
    impl_.id_type4_ = Host::IDENT_CIRCUIT_ID;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("20:00:00:02", toHex(id));
    EXPECT_EQ("20:00:00:02", text);

    // Try standard case with client-id.
    impl_.id_type4_ = Host::IDENT_CLIENT_ID;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("ff:2a:b8:15:14:00:03:00:01:20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("00:03:00:01:20:e5:2a:b8:15:14", text);

    // Try without extract duid.
    impl_.extract_duid_ = false;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("ff:2a:b8:15:14:00:03:00:01:20:e5:2a:b8:15:14", toHex(id));
    EXPECT_EQ("ff:2a:b8:15:14:00:03:00:01:20:e5:2a:b8:15:14", text);

    // Try standard case with flex-id.
    impl_.id_type4_ = Host::IDENT_FLEX;
    id.clear();
    text.clear();
    EXPECT_FALSE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_TRUE(id.empty());
    EXPECT_TRUE(text.empty());
}

/// Verify that getIdentifier handles correctly IPv4 packets using
/// captured simple solicit.
TEST_F(AccessTest, getIdentifierSimpleSolicit) {
    // Get the discover from capture.
    Pkt6Ptr pkt = PktCaptures::captureSimpleSolicit();
    ASSERT_NO_THROW(pkt->unpack());

    // Try standard case with duid.
    vector<uint8_t> id;
    string text;
    impl_.id_type6_ = Host::IDENT_DUID;
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", toHex(id));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", text);

    // Pop0 does nothing (does not start with a 0).
    impl_.clientid_pop0_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", toHex(id));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", text);

    // Printable does nothing too (not printable).
    impl_.clientid_pop0_ = false;
    impl_.clientid_printable_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", toHex(id));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", text);

    // Nor both pop0 and printable.
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", toHex(id));
    EXPECT_EQ("01:02:03:04:05:06:07:08:09:0a", text);

    // Try standard case with hw-address.
    impl_.id_type6_ = Host::IDENT_HWADDR;
    id.clear();
    text.clear();
    EXPECT_FALSE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_TRUE(id.empty());
    EXPECT_TRUE(text.empty());

    // Try with flex.
    impl_.id_type6_ = Host::IDENT_FLEX;
    id.clear();
    text.clear();
    EXPECT_FALSE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_TRUE(id.empty());
    EXPECT_TRUE(text.empty());

    // Client-id is not supported.
    impl_.id_type6_ = Host::IDENT_CLIENT_ID;
    id.clear();
    text.clear();
    EXPECT_FALSE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_TRUE(id.empty());
    EXPECT_TRUE(text.empty());

    // Nor circuit-id.
    impl_.id_type6_ = Host::IDENT_CIRCUIT_ID;
    id.clear();
    text.clear();
    EXPECT_FALSE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_TRUE(id.empty());
    EXPECT_TRUE(text.empty());
}

/// Verify that getIdentifier handles correctly IPv4 packets using
/// captured relayed solicit.
TEST_F(AccessTest, getIdentifierRelayedSolicit) {
    // Get the discover from capture.
    Pkt6Ptr pkt = PktCaptures::captureRelayedSolicit();
    ASSERT_NO_THROW(pkt->unpack());

    // Relayed solicit has a DUID-LLT so a hardware address.
    vector<uint8_t> id;
    string text;
    impl_.id_type6_ = Host::IDENT_HWADDR;
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("08:00:27:58:f1:e8", toHex(id));
    EXPECT_EQ("08:00:27:58:f1:e8", text);

    // With canonize.
    impl_.canonical_mac_address_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("08:00:27:58:f1:e8", toHex(id));
    EXPECT_EQ("08-00-27-58-f1-e8", text);
}

/// Verify that getIdentifier handles correctly IPv4 packets using flex-id.
TEST_F(AccessTest, getIdentifierFlex4) {
    // Prepare the packet.
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    vector<uint8_t> flex = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER, flex));
    pkt->addOption(option);

    // Try standard case with flex.
    vector<uint8_t> id;
    string text;
    impl_.id_type4_ = Host::IDENT_FLEX;
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    ASSERT_EQ(flex.size() - 1, id.size());
    EXPECT_EQ(0, memcmp(&id[0], &flex[1], id.size()));
    EXPECT_EQ("46:6f:6f:62:61:72", text);

    // Pop0 does nothing because it is already done!
    impl_.clientid_pop0_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("46:6f:6f:62:61:72", text);

    // Try printable.
    impl_.clientid_printable_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("Foobar", text);
}

/// Verify that getIdentifier handles correctly IPv6 packets using flex-id.
TEST_F(AccessTest, getIdentifierFlex6) {
    // Prepare the packet.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 12345));
    vector<uint8_t> flex = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    OptionPtr option(new Option(Option::V6, D6O_CLIENTID, flex));
    pkt->addOption(option);

    // Try standard case with flex.
    vector<uint8_t> id;
    string text;
    impl_.id_type6_ = Host::IDENT_FLEX;
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    ASSERT_EQ(flex.size() - 2, id.size());
    EXPECT_EQ(0, memcmp(&id[0], &flex[2], id.size()));
    EXPECT_EQ("46:6f:6f:62:61:72", text);

    // Pop0 does nothing because it is already done!
    impl_.clientid_pop0_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("46:6f:6f:62:61:72", text);

    // Try printable.
    impl_.clientid_printable_ = true;
    id.clear();
    text.clear();
    EXPECT_TRUE(impl_.auth_->getIdentifier(*pkt, id, text));
    EXPECT_EQ("Foobar", text);
}

/// Verify the buildAuth behavior in IPv4 with unused subnet Id.
TEST_F(AccessTest, buildBadSubnet4) {
    Pkt4Ptr pkt = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type4_ = Host::IDENT_FLEX;
    RadiusAuthHandlerPtr handler;
    uint32_t reserved = SUBNET_ID_UNUSED;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, reserved,
                                                     id, text));
    EXPECT_FALSE(handler);
}

/// Verify the buildAuth behavior in IPv6 with unused subnet Id.
TEST_F(AccessTest, buildBadSubnet6) {
    Pkt6Ptr pkt = PktCaptures::captureSimpleSolicit();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type6_ = Host::IDENT_FLEX;
    RadiusAuthHandlerPtr handler;
    uint32_t reserved = SUBNET_ID_UNUSED;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, reserved,
                                                     id, text));
    EXPECT_FALSE(handler);
}

/// Verify the buildAuth behavior in IPv4 with hardware address.
TEST_F(AccessTest, buildHWAddr4) {
    Pkt4Ptr pkt = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type4_ = Host::IDENT_FLEX;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    EXPECT_EQ(1, handler->env_.subnet_id_);
    ASSERT_EQ(id.size(), handler->env_.id_.size());
    EXPECT_EQ(0, memcmp(&id[0], &handler->env_.id_[0], id.size()));

    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(2, handler->env_.send_attrs_->size());
    ConstAttributePtr user_name = handler->env_.send_attrs_->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    string expected = "User-Name='" + text + "'";
    EXPECT_EQ(expected, user_name->toText());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
}

/// Verify the buildAuth behavior in IPv6 with hardware address.
TEST_F(AccessTest, buildHWAddr6) {
    Pkt6Ptr pkt = PktCaptures::captureRelayedSolicit();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type6_ = Host::IDENT_FLEX;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    EXPECT_EQ(1, handler->env_.subnet_id_);
    ASSERT_EQ(id.size(), handler->env_.id_.size());
    EXPECT_EQ(0, memcmp(&id[0], &handler->env_.id_[0], id.size()));

    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(2, handler->env_.send_attrs_->size());
    ConstAttributePtr user_name = handler->env_.send_attrs_->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    string expected = "User-Name='" + text + "'";
    EXPECT_EQ(expected, user_name->toText());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='08:00:27:58:f1:e8'",
              calling_station_id->toText());
}

/// Verify the buildAuth behavior in IPv4 with canonical hardware address.
TEST_F(AccessTest, buildCanonHWAddr4) {
    Pkt4Ptr pkt = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type4_ = Host::IDENT_FLEX;
    impl_.canonical_mac_address_ = true;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(2, handler->env_.send_attrs_->size());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20-e5-2a-b8-15-14'",
              calling_station_id->toText());
}

/// Verify the buildAuth behavior in IPv6 with canonical hardware address.
TEST_F(AccessTest, buildCanonHWAddr6) {
    Pkt6Ptr pkt = PktCaptures::captureRelayedSolicit();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type6_ = Host::IDENT_FLEX;
    impl_.canonical_mac_address_ = true;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(2, handler->env_.send_attrs_->size());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='08-00-27-58-f1-e8'",
              calling_station_id->toText());
}

/// Verify the buildAuth behavior in IPv4 without hardware address.
TEST_F(AccessTest, buildNoHWAddr4) {
    Pkt4Ptr pkt = PktCaptures::captureRelayedDiscover();
    ASSERT_NO_THROW(pkt->unpack());
    ASSERT_TRUE(pkt->getHWAddr());
    ASSERT_FALSE(pkt->getHWAddr()->hwaddr_.empty());
    vector<uint8_t> id = pkt->getHWAddr()->hwaddr_;
    string text = toHex(id);
    impl_.id_type4_ = Host::IDENT_HWADDR;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(1, handler->env_.send_attrs_->size());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_FALSE(calling_station_id);
}

/// Verify the buildAuth behavior in IPv6 without hardware address.
TEST_F(AccessTest, buildNoHWAddr6) {
    Pkt6Ptr pkt = PktCaptures::captureRelayedSolicit();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type6_ = Host::IDENT_HWADDR;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(1, handler->env_.send_attrs_->size());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_FALSE(calling_station_id);
}

/// Verify the buildAuth behavior in IPv6 with simple solicit.
TEST_F(AccessTest, buildSimple6) {
    Pkt6Ptr pkt = PktCaptures::captureSimpleSolicit();
    ASSERT_NO_THROW(pkt->unpack());
    vector<uint8_t> id = { 0x01, 0x02 };
    string text = "01:02";
    impl_.id_type6_ = Host::IDENT_FLEX;
    RadiusAuthHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.auth_->buildAuth(*pkt, 1, id, text));
    ASSERT_TRUE(handler);

    // Simple Solicit has no hardware address.
    ASSERT_TRUE(handler->env_.send_attrs_);
    EXPECT_LE(1, handler->env_.send_attrs_->size());
    ConstAttributePtr calling_station_id =
        handler->env_.send_attrs_->get(PW_CALLING_STATION_ID);
    ASSERT_FALSE(calling_station_id);
}

/// Verify the terminate behavior on errors - IPv4.
TEST_F(AccessTest, terminate4Error) {
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt4Ptr pkt;
    bool drop;

    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    drop = false;
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, -3, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_EQ(0, cache_->size());

    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, BADRESP_RC, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_EQ(0, cache_->size());

    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, ERROR_RC, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_EQ(0, cache_->size());

    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, TIMEOUT_RC, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_EQ(0, cache_->size());
}

/// Verify the terminate behavior on error - IPv6.
TEST_F(AccessTest, terminate6Error) {
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt6Ptr pkt;
    bool drop;

    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    drop = false;
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, -3, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_EQ(0, cache_->size());

    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, BADRESP_RC, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_EQ(0, cache_->size());

    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, ERROR_RC, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_EQ(0, cache_->size());

    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, TIMEOUT_RC, attrs,
                                                    pkt, drop));
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_EQ(0, cache_->size());
}

/// Verify the terminate behavior on reject - IPv4.
TEST_F(AccessTest, terminate4Reject) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, REJECT_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(SUBNET_ID_UNUSED, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(SUBNET_ID_UNUSED, SubnetID(reselected->intValue()));
}

/// Verify the terminate behavior on reject - IPv6.
TEST_F(AccessTest, terminate6Reject) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, REJECT_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(SUBNET_ID_UNUSED, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(SUBNET_ID_UNUSED, SubnetID(reselected->intValue()));
}

/// Verify the terminate behavior on reject - IPv4, global.
TEST_F(AccessTest, terminate4RejectGlobal) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, REJECT_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(SUBNET_ID_UNUSED, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(SUBNET_ID_UNUSED, SubnetID(reselected->intValue()));
}

/// Verify the terminate behavior on reject - IPv6, global.
TEST_F(AccessTest, terminate6RejectGlobal) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, REJECT_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(SUBNET_ID_UNUSED, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(SUBNET_ID_UNUSED, SubnetID(reselected->intValue()));
}

/// Verify the terminate behavior on empty accept - IPv4.
TEST_F(AccessTest, terminate4AcceptEmpty) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    EXPECT_FALSE(saved_attrs);
}

/// Verify the terminate behavior on empty accept - IPv6.
TEST_F(AccessTest, terminate6AcceptEmpty) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    EXPECT_FALSE(saved_attrs);
}

/// Verify the terminate behavior on empty accept - IPv4, global.
TEST_F(AccessTest, terminate4AcceptEmptyGlobal) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    EXPECT_FALSE(saved_attrs);
}

/// Verify the terminate behavior on empty accept - IPv6, global.
TEST_F(AccessTest, terminate6AcceptEmptyGlobal) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, attrs,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    EXPECT_FALSE(saved_attrs);
}

/// Verify the terminate behavior on unrelevant accept - IPv4.
TEST_F(AccessTest, terminate4AcceptUnrelevant) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_USER_NAME, "foobar"));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on unrelevant accept - IPv6.
TEST_F(AccessTest, terminate6AcceptUnrelevant) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_USER_NAME, "foobar"));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on unrelevant reject - IPv4.
TEST_F(AccessTest, terminate4RejectUnrelevant) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_USER_NAME, "foobar"));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, REJECT_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(SUBNET_ID_UNUSED, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(SUBNET_ID_UNUSED, SubnetID(reselected->intValue()));
}

/// Verify the terminate behavior on unrelevant reject - IPv6.
TEST_F(AccessTest, terminate6RejectUnrelevant) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_USER_NAME, "foobar"));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, REJECT_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(SUBNET_ID_UNUSED, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(SUBNET_ID_UNUSED, SubnetID(reselected->intValue()));
}

/// Verify the terminate behavior on pool accept - IPv4.
TEST_F(AccessTest, terminate4AcceptPool) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    Pkt4Ptr pkt2;
    bool drop = false;
    impl_.auth_->requests4_.set(id, pkt);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt2, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt2);
    EXPECT_EQ(pkt, pkt2);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(pkt->inClass("foobar"));
}

/// Verify the terminate behavior on pool accept - IPv6.
TEST_F(AccessTest, terminate6AcceptPool) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 12345));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    Pkt6Ptr pkt2;
    bool drop = false;
    impl_.auth_->requests6_.set(id, pkt);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt2, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt2);
    EXPECT_EQ(pkt, pkt2);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(pkt->inClass("foobar"));
}

/// Verify the terminate behavior on pool accept - IPv4, global.
TEST_F(AccessTest, terminate4AcceptPoolGlobal) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    Pkt4Ptr pkt2;
    bool drop = false;
    impl_.auth_->requests4_.set(id, pkt);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt2, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt2);
    EXPECT_EQ(pkt, pkt2);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(pkt->inClass("foobar"));
}

/// Verify the terminate behavior on pool accept - IPv6, global.
TEST_F(AccessTest, terminate6AcceptPoolGlobal) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 12345));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foobar"));
    Pkt6Ptr pkt2;
    bool drop = false;
    impl_.auth_->requests6_.set(id, pkt);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt2, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt2);
    EXPECT_EQ(pkt, pkt2);
    EXPECT_FALSE(drop);
    ASSERT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(pkt->inClass("foobar"));
}

/// Verify the terminate behavior on IPv4 address accept - IPv4.
TEST_F(AccessTest, terminate4AcceptAddress) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.1", host->getIPv4Reservation().toText());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on IPv4 address accept - IPv4, global.
TEST_F(AccessTest, terminate4AcceptAddressGlobal) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.1", host->getIPv4Reservation().toText());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on IPv4 address accept - IPv6.
TEST_F(AccessTest, terminate6AcceptAddress4) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on IPv6 address accept - IPv6.
TEST_F(AccessTest, terminate6AcceptAddress) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on IPv6 address accept - IPv6, global.
TEST_F(AccessTest, terminate6AcceptAddressGlobal) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on delegated prefix accept - IPv6.
TEST_F(AccessTest, terminate6AcceptPrefix) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8:1::");
    received->add(Attribute::fromIpv6Prefix(PW_DELEGATED_IPV6_PREFIX, 64, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8:1::", resrvs.first->second.getPrefix().toText());
    EXPECT_EQ(64, resrvs.first->second.getPrefixLen());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on delegated prefix accept - IPv6, global.
TEST_F(AccessTest, terminate6AcceptPrefixGlobal) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8:1::");
    received->add(Attribute::fromIpv6Prefix(PW_DELEGATED_IPV6_PREFIX, 64, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8:1::", resrvs.first->second.getPrefix().toText());
    EXPECT_EQ(64, resrvs.first->second.getPrefixLen());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on both IPv6 address and
/// delegated prefix accept - IPv6.
TEST_F(AccessTest, terminate6AcceptBoth) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    IOAddress pref("2001:db8:1::");
    received->add(Attribute::fromIpv6Prefix(PW_DELEGATED_IPV6_PREFIX, 64, pref));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(1, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(1, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    resrvs = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8:1::", resrvs.first->second.getPrefix().toText());
    EXPECT_EQ(64, resrvs.first->second.getPrefixLen());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(2, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on both IPv6 address and
/// delegated prefix accept - IPv6, global.
TEST_F(AccessTest, terminate6AcceptBothGlobal) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:0:1::"),
                                  64, 1, 2, 3, 4, 1));
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    IOAddress pref("2001:db8:1::");
    received->add(Attribute::fromIpv6Prefix(PW_DELEGATED_IPV6_PREFIX, 64, pref));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, Pkt6Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    resrvs = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8:1::", resrvs.first->second.getPrefix().toText());
    EXPECT_EQ(64, resrvs.first->second.getPrefixLen());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    EXPECT_EQ(2, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on IPv6 address accept - IPv4.
TEST_F(AccessTest, terminate4AcceptAddress6) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    subnet->setReservationsGlobal(false);
    subnet->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;
    RadiusAuthEnv env(1, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, Pkt4Ptr());
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    EXPECT_FALSE(pkt);
    EXPECT_FALSE(drop);
    EXPECT_EQ(1, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());
    ConstHostPtr host = HostMgr::instance().get4Any(1, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    const vector<uint8_t>& hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

TEST_F(AccessTest, hostPool4) {
    testHostPool4();
}

TEST_F(AccessTest, hostPool6) {
    testHostPool6();
}

TEST_F(AccessTest, hostReselect4) {
    testHostReselect4();
}

TEST_F(AccessTest, hostReselect6) {
    testHostReselect6();
}

TEST_F(AccessTest, hostReservation4) {
    testHostReservation4();
}

TEST_F(AccessTest, hostReservation6) {
    testHostReservation6();
}

TEST_F(AccessTest, hostReservation6Prefix) {
    testHostReservation6Prefix();
}

TEST_F(AccessTest, hostReservation6Both) {
    testHostReservation6Both();
}

TEST_F(AccessTest, twoQueries4) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Initialize stats.
    StatsMgr::instance().setValue("pkt4-duplicate",
                                  static_cast<int64_t>(0));
    StatsMgr::instance().setValue("pkt4-receive-drop",
                                  static_cast<int64_t>(0));

    // Start not servicing server.
    thread_.reset(new thread(bind(&AccessTest::dummyServer, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    testTwoQueries4(subnet);

    // Say the dummy server it can finish.
    close_ = true;

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);

    // Check stats.
    ObservationPtr qf_stat =
        StatsMgr::instance().getObservation("pkt4-duplicate");
    ObservationPtr rd_stat =
        StatsMgr::instance().getObservation("pkt4-receive-drop");
    ASSERT_TRUE(qf_stat);
    ASSERT_TRUE(rd_stat);
    EXPECT_EQ(1, qf_stat->getInteger().first);
    EXPECT_EQ(1, rd_stat->getInteger().first);
}

TEST_F(AccessTest, twoQueries6) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 1, 2, 3, 4, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Initialize stats.
    StatsMgr::instance().setValue("pkt6-duplicate",
                                  static_cast<int64_t>(0));
    StatsMgr::instance().setValue("pkt6-receive-drop",
                                  static_cast<int64_t>(0));

    // Start not servicing server.
    thread_.reset(new thread(bind(&AccessTest::dummyServer, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    testTwoQueries6(subnet);

    // Say the dummy server it can finish.
    close_ = true;

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);

    // Check stats.
    ObservationPtr qf_stat =
        StatsMgr::instance().getObservation("pkt6-duplicate");
    ObservationPtr rd_stat =
        StatsMgr::instance().getObservation("pkt6-receive-drop");
    ASSERT_TRUE(qf_stat);
    ASSERT_TRUE(rd_stat);
    EXPECT_EQ(1, qf_stat->getInteger().first);
    EXPECT_EQ(1, rd_stat->getInteger().first);
}

TEST_F(AccessTest, maxPendingRequest4) {
    // Run the test in MT mode.
    MultiThreadingTest mt(true);

    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Initialize stats.
    StatsMgr::instance().setValue("pkt4-queue-full",
                                  static_cast<int64_t>(0));
    StatsMgr::instance().setValue("pkt4-receive-drop",
                                  static_cast<int64_t>(0));

    // Start not servicing server.
    thread_.reset(new thread(bind(&AccessTest::dummyServer, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    testTooManyQueries4(subnet);

    // Say the dummy server it can finish.
    close_ = true;

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);

    // Check stats.
    ObservationPtr qf_stat =
        StatsMgr::instance().getObservation("pkt4-queue-full");
    ObservationPtr rd_stat =
        StatsMgr::instance().getObservation("pkt4-receive-drop");
    ASSERT_TRUE(qf_stat);
    ASSERT_TRUE(rd_stat);
    EXPECT_EQ(1, qf_stat->getInteger().first);
    EXPECT_EQ(1, rd_stat->getInteger().first);
}

TEST_F(AccessTest, maxPendingRequest6) {
    // Run the test in MT mode.
    MultiThreadingTest mt(true);

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 1, 2, 3, 4, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Initialize stats.
    StatsMgr::instance().setValue("pkt6-queue-full",
                                  static_cast<int64_t>(0));
    StatsMgr::instance().setValue("pkt6-receive-drop",
                                  static_cast<int64_t>(0));

    // Start not servicing server.
    thread_.reset(new thread(bind(&AccessTest::dummyServer, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    testTooManyQueries6(subnet);

    // Say the dummy server it can finish.
    close_ = true;

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);

    // Check stats.
    ObservationPtr qf_stat =
        StatsMgr::instance().getObservation("pkt6-queue-full");
    ObservationPtr rd_stat =
        StatsMgr::instance().getObservation("pkt6-receive-drop");
    ASSERT_TRUE(qf_stat);
    ASSERT_TRUE(rd_stat);
    EXPECT_EQ(1, qf_stat->getInteger().first);
    EXPECT_EQ(1, rd_stat->getInteger().first);
}

TEST_F(AccessTest, noHost4) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Start server.
    thread_.reset(new thread(bind(&AccessTest::server, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    testNoHost4(subnet);

    start = system_clock::now();
    while (system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        {
            if (expected_received_ <= unparked_) {
                break;
            }
        }
        service_->poll();
        this_thread::sleep_for(1ms);
    }
    EXPECT_EQ(expected_received_, unparked_);

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);

    checkNoHost4Results(subnet);
}

TEST_F(AccessTest, noHost6) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 1, 2, 3, 4, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Start server.
    thread_.reset(new thread(bind(&AccessTest::server, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    testNoHost6(subnet);

    start = system_clock::now();
    while (system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        service_->poll();
        {
            if (expected_received_ <= unparked_) {
                break;
            }
        }
        this_thread::sleep_for(1ms);
    }
    EXPECT_EQ(expected_received_, unparked_);

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);

    checkNoHost6Results(subnet);
}

TEST_F(AccessTest, noIdentifier4) {
    testNoIdentifier4();
}

TEST_F(AccessTest, noIdentifier6) {
    testNoIdentifier6();
}

TEST_F(MTAccessTest, hostPool4) {
    run([&](uint32_t const i) { testHostPool4(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostPool6) {
    run([&](uint32_t const i) { testHostPool6(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostReselect4) {
    run([&](uint32_t const i) { testHostReselect4(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostReselect6) {
    run([&](uint32_t const i) { testHostReselect6(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostReservation4) {
    run([&](uint32_t const i) { testHostReservation4(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostReservation6) {
    run([&](uint32_t const i) { testHostReservation6(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostReservation6Prefix) {
    run([&](uint32_t const i) { testHostReservation6Prefix(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, hostReservation6Both) {
    run([&](uint32_t const i) { testHostReservation6Both(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, twoQueries4) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Start not servicing server.
    thread_.reset(new thread(bind(&AccessTest::dummyServer, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    run([subnet, this](uint32_t const i) { testTwoQueries4(subnet, i); });

    // Say the dummy server it can finish.
    close_ = true;

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);
}

TEST_F(MTAccessTest, twoQueries6) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 1, 2, 3, 4, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Start not servicing server.
    thread_.reset(new thread(bind(&AccessTest::dummyServer, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    run([subnet, this](uint32_t const i) { testTwoQueries6(subnet, i); });

    // Say the dummy server it can finish.
    close_ = true;

    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(finished_);
}

TEST_F(MTAccessTest, noHost4) {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Start server.
    thread_.reset(new thread(bind(&AccessTest::server, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    run([&](uint32_t const i) { testNoHost4(subnet, i); });

    // Wait for the simulated RADIUS server to finish.
    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }

    // Wait for all the unpark callbacks.
    start = system_clock::now();
    while (system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        service_->poll();
        size_t const parking_lot_size(
            ServerHooks::getServerHooks().getParkingLotPtr("subnet4_select")->size());
        {
            lock_guard<mutex> lock(mutex_);
            if (expected_received_ <= unparked_ && !parking_lot_size) {
                break;
            }
        }
        this_thread::sleep_for(1ms);
    }
    EXPECT_EQ(expected_received_, unparked_);
    EXPECT_EQ(0, ServerHooks::getServerHooks().getParkingLotPtr("subnet4_select")->size());

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());

    // Join RADIUS hook library threads.
    EXPECT_NO_THROW_LOG(impl_.thread_pool_->stop());

    // Half should be parked and then unparked. Half should be dropped.
    EXPECT_EQ(0, steps_[CalloutHandle::NEXT_STEP_CONTINUE]);
    EXPECT_EQ(0, steps_[CalloutHandle::NEXT_STEP_SKIP]);
    EXPECT_EQ(0, steps_[CalloutHandle::NEXT_STEP_DROP]);
    EXPECT_EQ(expected_received_, steps_[CalloutHandle::NEXT_STEP_PARK]);
    EXPECT_EQ(expected_received_, unparked_);

    EXPECT_EQ(expected_received_, cache_->size());

    for (uint16_t i = 0; i < expected_received_; ++i) {
        checkNoHost4Results(subnet, static_cast<uint32_t>(i));
    }
}

TEST_F(MTAccessTest, noHost6) {
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 1, 2, 3, 4, 1));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Start server.
    thread_.reset(new thread(bind(&AccessTest::server, this)));
    system_clock::time_point start(system_clock::now());
    while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }
    EXPECT_TRUE(ready_);

    run([&](uint32_t const i) { testNoHost6(subnet, i); });

    // Wait for the simulated RADIUS server to finish.
    start = system_clock::now();
    while (!finished_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        this_thread::sleep_for(1ms);
    }

    // Wait for all the unpark callbacks.
    start = system_clock::now();
    while (system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
        service_->poll();
        size_t const parking_lot_size(
            ServerHooks::getServerHooks().getParkingLotPtr("subnet6_select")->size());
        {
            lock_guard<mutex> lock(mutex_);
            if (expected_received_ <= unparked_ && !parking_lot_size) {
                break;
            }
        }
        this_thread::sleep_for(1ms);
    }
    EXPECT_EQ(expected_received_, unparked_);
    EXPECT_EQ(0, ServerHooks::getServerHooks().getParkingLotPtr("subnet6_select")->size());

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());

    // Join RADIUS hook library threads.
    EXPECT_NO_THROW_LOG(impl_.thread_pool_->stop());

    // Half should be parked and then unparked. Half should be dropped.
    EXPECT_EQ(0, steps_[CalloutHandle::NEXT_STEP_CONTINUE]);
    EXPECT_EQ(0, steps_[CalloutHandle::NEXT_STEP_SKIP]);
    EXPECT_EQ(0, steps_[CalloutHandle::NEXT_STEP_DROP]);
    EXPECT_EQ(expected_received_, steps_[CalloutHandle::NEXT_STEP_PARK]);
    EXPECT_EQ(expected_received_, unparked_);

    EXPECT_EQ(expected_received_, cache_->size());

    for (uint16_t i = 0; i < expected_received_; ++i) {
        checkNoHost6Results(subnet, static_cast<uint32_t>(i));
    }
}

TEST_F(MTAccessTest, noIdentifier4) {
    run([&](uint32_t const i) { testNoIdentifier4(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

TEST_F(MTAccessTest, noIdentifier6) {
    run([&](uint32_t const i) { testNoIdentifier6(i); });

    // Join threads.
    EXPECT_NO_THROW_LOG(thread_pool_.wait());
    EXPECT_NO_THROW_LOG(thread_pool_.stop());
}

/// @brief Test fixture for testing reselect code.
class ReselectTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ReselectTest() { }

    /// @brief Destructor.
    virtual ~ReselectTest() {
        CfgMgr::instance().clear();
    }
};

/// @brief Check that reselectSubnet accepts correct class - IPv4.
TEST_F(ReselectTest, goodClass4) {
    // Create a subnet with a pool guarded by the foo client class.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 14));
    PoolPtr pool(new Pool4(IOAddress("192.0.2.10"), IOAddress("192.0.2.20")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));

    // Check that the subnet is accepted.
    uint32_t id = 14;
    bool both = false;
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet changes bad pool - IPv4.
TEST_F(ReselectTest, badClass4) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool4(IOAddress("192.0.2.130"),
                           IOAddress("192.0.2.140")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");

    // Check that the subnet is reselected.
    uint32_t id = 13;
    bool both = false;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Both subnets.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_TRUE(both);

    // Last case.
    subnet1->setReservationsGlobal(false);
    subnet1->setReservationsInSubnet(true);
    subnet1->setReservationsOutOfPool(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet accepts correct class - IPv6
TEST_F(ReselectTest, goodClass6) {
    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                  64, 1, 2, 3, 4, 14));
    PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                           IOAddress("2001:db8::20")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));

    // Check that the subnet is accepted.
    uint32_t id = 14;
    bool both = false;
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet changes bad pool - IPv6.
TEST_F(ReselectTest, badClass6) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                  64, 1, 2, 3, 4, 14));
    PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                           IOAddress("2001:db8::20")));
    subnet2->setIface("eth0");
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");

    // Check that the subnet is accepted.
    uint32_t id = 13;
    bool both = false;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Both subnets.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_TRUE(both);

    // Last case.
    subnet1->setReservationsGlobal(false);
    subnet1->setReservationsInSubnet(true);
    subnet1->setReservationsOutOfPool(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, "foo"));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet accepts correct address - IPv4.
TEST_F(ReselectTest, goodAddress4) {
    // Create a subnet.
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 14));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));

    // Check that the subnet is accepted.
    IOAddress addr = IOAddress("192.0.2.1");
    uint32_t id = 14;
    bool both = false;
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet change bad address - IPv4.
TEST_F(ReselectTest, badAddress4) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");

    // Check that the subnet is accepted.
    IOAddress addr = IOAddress("192.0.2.1");
    uint32_t id = 13;
    bool both = false;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Both subnets.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_TRUE(both);

    // Last case.
    subnet1->setReservationsGlobal(false);
    subnet1->setReservationsInSubnet(true);
    subnet1->setReservationsOutOfPool(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet accepts correct address - IPv6.
TEST_F(ReselectTest, goodAddress6) {
    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"),
                                  64, 1, 2, 3, 4, 14));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));

    // Check that the subnet is accepted.
    IOAddress addr = IOAddress("2001:db8::1");
    uint32_t id = 14;
    bool both = false;
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet->setReservationsGlobal(true);
    subnet->setReservationsInSubnet(false);
    EXPECT_FALSE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// @brief Check that reselectSubnet changes bad address - IPv6.
TEST_F(ReselectTest, badAddress6) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);

    // Check that the subnet is accepted.
    IOAddress addr = IOAddress("2001:db8::1");
    uint32_t id = 13;
    bool both = false;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Retrying using global reservations.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);

    // Both subnets.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_TRUE(both);

    // Last case.
    subnet1->setReservationsGlobal(false);
    subnet1->setReservationsInSubnet(true);
    subnet1->setReservationsOutOfPool(false);
    id = 13;
    EXPECT_TRUE(RadiusAccess::reselectSubnet(query, id, both, addr));
    EXPECT_EQ(14, id);
    EXPECT_FALSE(both);
}

/// Verify the terminate behavior on pool reselect - IPv4.
TEST_F(AccessTest, terminate4ReselectPool) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool4(IOAddress("192.0.2.130"),
                           IOAddress("192.0.2.140")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(13, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(13, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get4Any(14, impl_.id_type4_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(14, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));

    // There should be no global host entry.
    host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type4_,
                                       &id[0], id.size());
    EXPECT_FALSE(host);
}

/// Verify the terminate behavior on pool reselect - IPv4, first global.
TEST_F(AccessTest, terminate4ReselectPoolGlobal1) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool4(IOAddress("192.0.2.130"),
                           IOAddress("192.0.2.140")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get4Any(14, impl_.id_type4_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(14, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on pool reselect - IPv4, second global.
TEST_F(AccessTest, terminate4ReselectPoolGlobal2) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool4(IOAddress("192.0.2.130"),
                           IOAddress("192.0.2.140")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(13, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(13, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type4_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on pool reselect - IPv4, both global.
TEST_F(AccessTest, terminate4ReselectPoolBoth) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool4(IOAddress("192.0.2.130"),
                           IOAddress("192.0.2.140")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());

    // Check merged host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_TRUE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on pool reselect - IPv6.
TEST_F(AccessTest, terminate6ReselectPool) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                           IOAddress("2001:db8::20")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(13, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(13, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get6Any(14, impl_.id_type6_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(14, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));

    // There should be no global host entry.
    host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type6_,
                                       &id[0], id.size());
    EXPECT_FALSE(host);
}

/// Verify the terminate behavior on pool reselect - IPv6, first global.
TEST_F(AccessTest, terminate6ReselectPoolGlobal1) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                           IOAddress("2001:db8::20")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get6Any(14, impl_.id_type6_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(14, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on pool reselect - IPv6, second global.
TEST_F(AccessTest, terminate6ReselectPoolGlobal2) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                           IOAddress("2001:db8::20")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(13, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(13, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type6_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on pool reselect - IPv6, both global.
TEST_F(AccessTest, terminate6ReselectPool6Both) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet without pools.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet with a pool guarded by the foo client class.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    PoolPtr pool(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                           IOAddress("2001:db8::20")));
    pool->allowClientClass("foo");
    EXPECT_NO_THROW(subnet2->addPool(pool));
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_pool_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    received->add(Attribute::fromString(PW_FRAMED_POOL, "foo"));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());

    // Check merged host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_TRUE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on address reselect - IPv4.
TEST_F(AccessTest, terminate4ReselectAddress) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(13, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(13, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get4Any(14, impl_.id_type4_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(14, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.1", host->getIPv4Reservation().toText());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));

    // There should be no global host entry.
    host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type4_,
                                       &id[0], id.size());
    EXPECT_FALSE(host);
}

/// Verify the terminate behavior on address reselect - IPv4, first global.
TEST_F(AccessTest, terminate4ReselectAddressGlobal1) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get4Any(14, impl_.id_type4_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(14, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.1", host->getIPv4Reservation().toText());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on address reselect - IPv4, second global.
TEST_F(AccessTest, terminate4ReselectAddressGlobal2) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(13, impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(13, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type4_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.1", host->getIPv4Reservation().toText());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on address reselect - IPv4, both global.
TEST_F(AccessTest, terminate4ReselectAddressBoth) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 14));
    subnet2->setIface("eth0");
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->add(subnet2);

    // Create a packet.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    query->addClass("foo");
    // Set giaddr in subnet 13.
    query->setGiaddr(IOAddress("192.0.2.192"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("192.0.2.1");
    received->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));
    Pkt4Ptr pkt;
    bool drop = false;
    impl_.auth_->requests4_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate4Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests4_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());

    // Check merged host entry.
    ConstHostPtr host = HostMgr::instance().get4Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type4_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type4_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.1", host->getIPv4Reservation().toText());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
    EXPECT_TRUE(query->inClass("foo"));
}

/// Verify the terminate behavior on address reselect - IPv6.
TEST_F(AccessTest, terminate6ReselectAddress) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(13, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(13, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get6Any(14, impl_.id_type6_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(14, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());

    // There should be no global host entry.
    host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type6_,
                                       &id[0], id.size());
    EXPECT_FALSE(host);
}

/// Verify the terminate behavior on address reselect - IPv6, first global.
TEST_F(AccessTest, terminate6ReselectAddressGlobal1) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get6Any(14, impl_.id_type6_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(14, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on address reselect - IPv6, second global.
TEST_F(AccessTest, terminate6ReselectAddressGlobal2) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(2, cache_->size());

    // Check reselect host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(13, impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(13, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_FALSE(host->hasIPv6Reservation());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_TRUE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_FALSE(ctx->contains("radius"));
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));

    // Check class host entry.
    host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                       impl_.id_type6_, &id[0], id.size());
    ASSERT_TRUE(host);
    hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

/// Verify the terminate behavior on address reselect - IPv6, both global.
TEST_F(AccessTest, terminate6ReselectAddressBoth) {
    // We'll put everything in eth0.
    IfaceMgrTestConfig test_config(true);

    // Create a subnet outside the address range.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 13));
    subnet1->setIface("eth0");
    // Set first subnet to global.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet1);

    // Create a subnet inside the address range.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 14));
    subnet2->setIface("eth0");
    // Set second subnet to global.
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->add(subnet2);

    // Create a packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    query->setIface("eth0");
    query->setIndex(ETH0_INDEX);
    // Set remote address in subnet 13.
    query->setRemoteAddr(IOAddress("2001:db8:0:1::1"));
    vector<uint8_t> id = { 0x01, 0x02 };
    AttributesPtr attrs;

    impl_.reselect_subnet_address_ = true;
    RadiusAuthEnv env(13, id, attrs);
    AttributesPtr received(new Attributes());
    IOAddress addr("2001:db8::1235");
    received->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    Pkt6Ptr pkt;
    bool drop = false;
    impl_.auth_->requests6_.set(id, query);
    ASSERT_NO_THROW(impl_.auth_->terminate6Internal(env, OK_RC, received,
                                                    pkt, drop));
    EXPECT_FALSE(impl_.auth_->requests6_.get(id));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(pkt, query);
    EXPECT_FALSE(drop);
    EXPECT_EQ(14, env.subnet_id_);
    EXPECT_EQ(1, cache_->size());

    // Check merged host entry.
    ConstHostPtr host = HostMgr::instance().get6Any(SUBNET_ID_GLOBAL,
                                                    impl_.id_type6_,
                                                    &id[0], id.size());
    ASSERT_TRUE(host);
    vector<uint8_t> hid = host->getIdentifier();
    ASSERT_EQ(id.size(), hid.size());
    EXPECT_EQ(0, memcmp(&id[0], &hid[0], id.size()));
    EXPECT_EQ(impl_.id_type6_, host->getIdentifierType());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_GLOBAL, host->getIPv6SubnetID());
    EXPECT_TRUE(host->getIPv4Reservation().isV4Zero());
    EXPECT_TRUE(host->hasIPv6Reservation());
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    EXPECT_EQ("2001:db8::1235", resrvs.first->second.getPrefix().toText());
    EXPECT_TRUE(host->getHostname().empty());
    EXPECT_TRUE(host->getClientClasses4().empty());
    EXPECT_TRUE(host->getClientClasses6().empty());
    EXPECT_TRUE(host->getNextServer().isV4Zero());
    EXPECT_TRUE(host->getServerHostname().empty());
    EXPECT_TRUE(host->getBootFileName().empty());
    EXPECT_TRUE(host->getCfgOption4()->empty());
    EXPECT_TRUE(host->getCfgOption6()->empty());
    EXPECT_FALSE(host->getNegative());
    ConstElementPtr ctx = host->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    ConstElementPtr reselected = ctx->get("subnet-id");
    ASSERT_TRUE(reselected);
    ASSERT_EQ(Element::integer, reselected->getType());
    EXPECT_EQ(14, SubnetID(reselected->intValue()));
    ConstElementPtr saved_attrs = ctx->get("radius");
    ASSERT_TRUE(saved_attrs);
    ASSERT_EQ(Element::list, saved_attrs->getType());
    ASSERT_EQ(1, saved_attrs->size());
    EXPECT_TRUE(*saved_attrs == *received->toElement());
}

} // end of anonymous namespace
