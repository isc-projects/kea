// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <radius.h>
#include <radius_accounting.h>
#include <radius_utils.h>
#include <attribute_test.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service_mgr.h>
#include <asiolink/udp_socket.h>
#include <cc/command_interpreter.h>
#include <cryptolink/crypto_hash.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>
#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks_manager.h>
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
using namespace isc::config;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::radius;
using namespace isc::test;
using namespace isc::util;

extern "C" {
extern int dhcp4_srv_configured(CalloutHandle& handle);
extern int dhcp6_srv_configured(CalloutHandle& handle);
extern int lease4_select(CalloutHandle& handle);
extern int lease4_renew(CalloutHandle& handle);
extern int lease4_release(CalloutHandle& handle);
extern int lease4_decline(CalloutHandle& handle);
extern int lease4_expire(CalloutHandle& handle);
extern int lease6_select(CalloutHandle& handle);
extern int lease6_renew(CalloutHandle& handle);
extern int lease6_rebind(CalloutHandle& handle);
extern int lease6_release(CalloutHandle& handle);
extern int lease6_decline(CalloutHandle& handle);
extern int lease6_expire(CalloutHandle& handle);
extern int command_processed(CalloutHandle& handle);
}

namespace {

struct TestHooks {
    int hook_index_dhcp4_srv_configured_;
    int hook_index_dhcp6_srv_configured_;

    TestHooks() {
        hook_index_dhcp4_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
        hook_index_dhcp6_srv_configured_ = HooksManager::registerHook("dhcp6_srv_configured");
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
const unsigned short SERVER_PORT = 11813;

/// Config.
const char* CONFIG =
"{\n"
"    \"accounting\": {\n"
"        \"servers\": [ {\n"
"            \"name\": \"127.0.0.1\",\n"
"            \"port\": 11813,\n"
"            \"secret\": \"foo\" } ] },\n"
"    \"extract-duid\": false,\n"
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

/// @brief Test fixture for testing accounting code.
class AccountingTest : public radius::test::AttributeTest {
public:
    /// @brief Constructor.
    AccountingTest() : AttributeTest(),
                       impl_(RadiusImpl::instance()),
                       cache_(new TestHostCache()),
                       manager_(new CalloutManager(1)),
                       service_(new IOService()), thread_(),
                       ready_(false), finished_(false),
                       timeout_expected_(false), expected_received_(1),
                       start_acct_counter_(0) {
        // Cache stuff
        HostMgr::create();
        auto cacheFactory = [this](const DatabaseConnection::ParameterMap&) {
            return (cache_);
        };
        HostDataSourceFactory::registerFactory("cache", cacheFactory);
        HostMgr::addBackend("type=cache");

        // Initialize.
        impl_.reset();
        ElementPtr config = Element::fromJSON(CONFIG);
        impl_.init(config);
        impl_.setIOService(service_);
        impl_.setIOContext(service_);
        impl_.cache_ = cache_;
    }

    /// @brief Destructor.
    virtual ~AccountingTest() {
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

        HostDataSourceFactory::deregisterFactory("cache");
        cache_.reset();

        // As a best practice, call any remaining handlers.
        service_->stopAndPoll();
    }

    /// @brief Thread server function.
    void server();

    /// @brief Start server.
    void startServer() {
        start_acct_counter_ = RadiusAcctHandler::getCounter();
        thread_.reset(new thread(std::bind(&AccountingTest::server, this)));
        // Wait for the server to be ready. Don't wait forever.
        system_clock::time_point const start(system_clock::now());
        while (!ready_ && system_clock::now() < start + milliseconds(GENERAL_TIMEOUT)) {
            this_thread::sleep_for(1ms);
        }
        EXPECT_TRUE(ready_);
    }

    /// @brief Wait for server to finish.
    void waitForServerToFinish() {
        // Wait for server to finish. Don't wait forever.
        system_clock::time_point const start(system_clock::now());
        while ((!finished_ ||
                (RadiusAcctHandler::getCounter() > start_acct_counter_)) &&
               (system_clock::now() < start + milliseconds(GENERAL_TIMEOUT))) {
            service_->poll();
            this_thread::sleep_for(1ms);
        }
        EXPECT_TRUE(finished_);
        EXPECT_EQ(start_acct_counter_, RadiusAcctHandler::getCounter());
    }

    /// @brief Tests
    /// @{
    void testEventToText();
    void testBuildAcctLease4();
    void testBuildAcctLease4canon();
    void testBuildAcctLease4noDuid();
    void testBuildAcctLease4noPop0();
    void testBuildAcctLease4notPrintable();
    void testBuildAcctLease4Duid();
    void testBuildAcctLease4DuidPrintable();
    void testBuildAcctLease4Pop0();
    void testBuildAcctLease4Pop0Printable();
    void testBuildAcctLease4noClientId();
    void testBuildAcctLease4Renew();
    void testBuildAcctLease4expire();
    void testBuildAcctLease4Release();
    void testBuildAcctLease4Decline();
    void testBuildAcctLease4Add();
    void testBuildAcctLease4Update();
    void testBuildAcctLease4Del();
    void testBuildAcctLease4ClassClientID();
    void testBuildAcctLease4ClassHwAddr();
    void testBuildAcctLease4ClassDuid();
    void testBuildAcctLease4ClassFlex();
    void testBuildAcctLease6();
    void testBuildAcctLease6prefix();
    void testBuildAcctLease6canon();
    void testBuildAcctLease6noPop0();
    void testBuildAcctLease6notPrintable();
    void testBuildAcctLease6Pop0();
    void testBuildAcctLease6Printable();
    void testBuildAcctLease6Pop0Printable();
    void testBuildAcctLease6Renew();
    void testBuildAcctLease6expire();
    void testBuildAcctLease6Release();
    void testBuildAcctLease6Decline();
    void testBuildAcctLease6Add();
    void testBuildAcctLease6Update();
    void testBuildAcctLease6Del();
    void testBuildAcctLease6ClassDUID();
    void testBuildAcctLease6ClassHwAddr();
    void testBuildAcctLease6ClassFlex();
    void testBuildAcct4();
    void testBuildAcct4noAddress();
    void testBuildAcct4noSubnet();
    void testBuildAcct4noHwAddr();
    void testBuildAcct4canon();
    void testBuildAcct4noPop0();
    void testBuildAcct4notPrintable();
    void testBuildAcct4Pop0();
    void testBuildAcct4Printable();
    void testBuildAcct4Pop0Printable();
    void testBuildAcct4noForce();
    void testBuildAcct4noClientId();
    void testBuildAcct4noClientIdcanon();
    void testBuildAcct4update();
    void testBuildAcct4del();
    void testBuildAcct4ClassClientID();
    void testBuildAcct4ClassHwAddr();
    void testBuildAcct4ClassFlex();
    void testBuildAcct6();
    void testBuildAcct6prefix();
    void testBuildAcct6noAddress();
    void testBuildAcct6noPDlength();
    void testBuildAcct6ZeroPDlength();
    void testBuildAcct6LargePDlength();
    void testBuildAcct6InvalidPDlength();
    void testBuildAcct6noSubnet();
    void testBuildAcct6noDuid();
    void testBuildAcct6noType();
    void testBuildAcct6Prefix();
    void testBuildAcct6canon();
    void testBuildAcct6noPop0();
    void testBuildAcct6notPrintable();
    void testBuildAcct6Pop0();
    void testBuildAcct6Printable();
    void testBuildAcct6Pop0Printable();
    void testBuildAcct6noForce();
    void testBuildAcct6update();
    void testBuildAcct6del();
    void testBuildAcct6ClassDUID();
    void testBuildAcct6ClassHwAddr();
    void testBuildAcct6ClassFlex();
    void testLease4SelectFake();
    void testLease4Select();
    void testLease4Renew();
    void testLease4Release();
    void testLease4Decline();
    void testLease4Expire();
    void testLease6SelectFake();
    void testLease6Select();
    void testLease6Renew();
    void testLease6Release();
    void testLease6Decline();
    void testLease6Expire();
    void testCommandProcessed();
    void testCommandProcessedNoOrigin();
    void testCommandProcessedNullArguments();
    void testNoPeerUpdates();
    void testNoPeerUpdatesNoOrigin();
    /// @}

    /// @brief Governs multi-threading core settings.
    ///
    /// Gets constructed and destructed by default.
    SingleThreaded st_;

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    /// @brief Test host cache.
    TestHostCachePtr cache_;

    /// @brief Callout manager.
    boost::shared_ptr<CalloutManager> manager_;

    /// @brief IO service.
    IOServicePtr service_;

    /// @brief Thread.
    ThreadPtr thread_;

    /// @brief Ready flag.
    atomic<bool> ready_;

    /// @brief Received status types.
    vector<AcctStatusType> status_types_;

    /// @brief Finished flag.
    atomic<bool> finished_;

    /// @brief Whether timeout is expected in the mock server.
    bool timeout_expected_;

    /// @brief Number of expected RADIUS responses before stopping the server.
    uint16_t expected_received_;

    /// @brief Counter of active accounting exchange.
    size_t start_acct_counter_;

    /// @brief Mutex to protect various code blocks in tests that are normally
    /// not executed concurrently in real code.
    mutex mutex_;

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
/// Adds MT functionality on top of @ref AccountingTest.
struct MTAccountingTest : AccountingTest {
    /// @brief Constructor.
    MTAccountingTest() : mt_(new MultiThreaded())  {
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
                // Lambda to avoid error: constructor 'AccountingTest' must not return void expression
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
        // Can't use ASSERT here.
        EXPECT_TRUE(impl_.udp_client_);
        if (impl_.udp_client_) {
            EXPECT_EQ(4, impl_.udp_client_->getThreadPoolSize());
        }
        EXPECT_NO_THROW_LOG(thread_pool_.start(impl_.thread_pool_size_));
        EXPECT_NO_THROW_LOG(thread_pool_.pause());

        // By default run the test function 10 times.
        expected_received_ = 10;
    }

    /// @brief Destructor.
    ~MTAccountingTest() {
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
    void run(function<void()> test_function) {
        // Fill the thread pool.
        for (uint16_t i = 0; i < expected_received_; ++i) {
            boost::shared_ptr<function<void()>> const work(
                boost::make_shared<function<void()>>(test_function));
            EXPECT_NO_THROW_LOG(thread_pool_.add(work));
        }
        EXPECT_NO_THROW_LOG(thread_pool_.resume());

        // Join the threads.
        EXPECT_NO_THROW_LOG(thread_pool_.wait());
        EXPECT_NO_THROW_LOG(thread_pool_.stop());
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
AccountingTest::server() {
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
    bool timeout = false;
    auto timeout_handler = [this, &timeout]() {
        timeout = true;
        if (!timeout_expected_) {
            FAIL() << "timeout";
        }
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

    // Stop timer.
    timer.cancel();

    if (timeout_expected_) {
        EXPECT_TRUE(timeout);
        finished_ = true;
        return;
    } else {
        EXPECT_FALSE(timeout);
    }
    EXPECT_EQ(expected_received_, error_codes_.size());

    lock_guard<mutex> lock(mutex_);
    for (uint16_t i = 0; i < expected_received_; ++i) {
        ASSERT_LT(i, error_codes_.size());
        boost::system::error_code error_code(error_codes_[i]);
        ASSERT_LT(i, sizes_.size());
        size_t received_size(sizes_[i]);
        ASSERT_LT(i, receive_buffers_.size());
        vector<uint8_t> rcv_buf(receive_buffers_[i]);

        // Sanity check the request.
        EXPECT_FALSE(error_code);
        EXPECT_LE(AUTH_HDR_LEN, received_size);
        if (error_code) {
            isc_throw(Unexpected, "I/O error");
        }
        if (received_size < AUTH_HDR_LEN) {
            isc_throw(Unexpected, "too short");
        }
        size_t radius_size = rcv_buf[2] << 8;
        radius_size |= rcv_buf[3] & 0xff;
        if (radius_size > received_size) {
            isc_throw(Unexpected, "size mismatch " << radius_size);
        }
        if (radius_size < AUTH_HDR_LEN) {
            isc_throw(Unexpected, "too short " << radius_size);
        }
        if (radius_size < received_size) {
            received_size = radius_size;
        }
        rcv_buf.resize(received_size);
        EXPECT_EQ(PW_ACCOUNTING_REQUEST, rcv_buf[0]);

        // Get status type.
        if (received_size > AUTH_HDR_LEN) {
            size_t ptr = AUTH_HDR_LEN;
            for (;;) {
                if (ptr == received_size) {
                    break;
                }
                ASSERT_FALSE(ptr + 2 > received_size);
                const uint8_t type = rcv_buf[ptr];
                const uint8_t len = rcv_buf[ptr + 1];
                ASSERT_FALSE(len < 3);
                ptr += len;
                ASSERT_FALSE(ptr > received_size);
                if (type == PW_ACCT_STATUS_TYPE) {
                    status_types_.push_back(AcctStatusType(rcv_buf[ptr - 1]));
                    break;
                }
            }
        }

        // Build response.
        string pool = "foobar";
        size_t send_size = AUTH_HDR_LEN + 2 + pool.size();
        vector<uint8_t> send_buffer(send_size);
        memmove(&send_buffer[0], &rcv_buf[0], AUTH_HDR_LEN);
        send_buffer[0] = PW_ACCOUNTING_RESPONSE;
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
        EXPECT_FALSE(error_code);
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

/// Verify that eventToText works as expected.
void AccountingTest::testEventToText() {
    EXPECT_EQ("create", eventToText(EVENT_CREATE));
    EXPECT_EQ("renew", eventToText(EVENT_RENEW));
    EXPECT_EQ("rebind", eventToText(EVENT_REBIND));
    EXPECT_EQ("expire", eventToText(EVENT_EXPIRE));
    EXPECT_EQ("release", eventToText(EVENT_RELEASE));
    EXPECT_EQ("decline", eventToText(EVENT_DECLINE));
    EXPECT_EQ("add", eventToText(EVENT_ADD));
    EXPECT_EQ("update", eventToText(EVENT_UPDATE));
    EXPECT_EQ("delete", eventToText(EVENT_DEL));
}

/// Verify that buildAcct on IPv4 lease works.
void AccountingTest::testBuildAcctLease4() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    EXPECT_EQ(EVENT_CREATE, handler->env_.event_);
    EXPECT_EQ(4, handler->env_.subnet_id_);
    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IP_ADDRESS);
    ASSERT_TRUE(framed_ip_address);
    EXPECT_EQ("Framed-IP-Address=192.0.2.1", framed_ip_address->toText());
    ConstAttributePtr session_id = attrs->get(PW_ACCT_SESSION_ID);
    ASSERT_TRUE(session_id);
    string strvalue;
    EXPECT_NO_THROW(strvalue = session_id->toString());
    EXPECT_EQ(handler->env_.session_id_, strvalue);
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with canonical hardware address.
void AccountingTest::testBuildAcctLease4canon() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20-e5-2a-b8-15-14'",
              calling_station_id->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with not duid client-id.
void AccountingTest::testBuildAcctLease4noDuid() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with not pop0 client-id.
void AccountingTest::testBuildAcctLease4noPop0() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with not printable client-id.
void AccountingTest::testBuildAcctLease4notPrintable() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with duid client-id.
void AccountingTest::testBuildAcctLease4Duid() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = {
        0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
    };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='05:06:07:08:09'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with printable duid client-id.
void AccountingTest::testBuildAcctLease4DuidPrintable() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = {
        0xff, 0x01, 0x02, 0x03, 0x04,
        0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 // Foobar
    };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with pop0 client-id.
void AccountingTest::testBuildAcctLease4Pop0() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with printable pop0 client-id.
void AccountingTest::testBuildAcctLease4Pop0Printable() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works without client-id.
void AccountingTest::testBuildAcctLease4noClientId() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    Lease4Ptr lease(new Lease4(addr, hwaddr, ClientIdPtr(), 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(4, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='20:e5:2a:b8:15:14'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    EXPECT_FALSE(calling_station_id);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with RENEW event.
void AccountingTest::testBuildAcctLease4Renew() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_RENEW));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with EXPIRE event.
void AccountingTest::testBuildAcctLease4expire() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_EXPIRE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with RELEASE event.
void AccountingTest::testBuildAcctLease4Release() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_RELEASE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with DECLINE event.
void AccountingTest::testBuildAcctLease4Decline() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_DECLINE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with ADD event.
void AccountingTest::testBuildAcctLease4Add() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with UPDATE event.
void AccountingTest::testBuildAcctLease4Update() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_UPDATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4 lease works with DELete event.
void AccountingTest::testBuildAcctLease4Del() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv4/ClientId can get the Class from host cache.
void AccountingTest::testBuildAcctLease4ClassClientID() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[0], id.size(),
                                        Host::IDENT_CLIENT_ID,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct on IPv4/HwAddr can get the Class from host cache.
void AccountingTest::testBuildAcctLease4ClassHwAddr() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&hwaddr->hwaddr_[0],
                                        hwaddr->hwaddr_.size(),
                                        Host::IDENT_HWADDR,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct on IPv4/DUID can get the Class from host cache.
void AccountingTest::testBuildAcctLease4ClassDuid() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = {
        0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
    };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[5], id.size() - 5,
                                        Host::IDENT_DUID,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct on IPv4/Flex can get the Class from host cache.
void AccountingTest::testBuildAcctLease4ClassFlex() {
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[1], id.size() - 1,
                                        Host::IDENT_FLEX,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct on IPv6 lease works.
void AccountingTest::testBuildAcctLease6() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    EXPECT_EQ(EVENT_CREATE, handler->env_.event_);
    EXPECT_EQ(4, handler->env_.subnet_id_);
    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IPV6_ADDRESS);
    ASSERT_TRUE(framed_ip_address);
    EXPECT_EQ("Framed-IPv6-Address=2001:db8::1235",
              framed_ip_address->toText());
    ConstAttributePtr session_id = attrs->get(PW_ACCT_SESSION_ID);
    ASSERT_TRUE(session_id);
    string strvalue;
    EXPECT_NO_THROW(strvalue = session_id->toString());
    EXPECT_EQ(handler->env_.session_id_, strvalue);
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 prefix lease works.
void AccountingTest::testBuildAcctLease6prefix() {
    IOAddress addr = IOAddress("2001:db8::");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_PD, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr, 64));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    EXPECT_EQ(EVENT_CREATE, handler->env_.event_);
    EXPECT_EQ(4, handler->env_.subnet_id_);
    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
    ConstAttributePtr delegated_prefix = attrs->get(PW_DELEGATED_IPV6_PREFIX);
    ASSERT_TRUE(delegated_prefix);
    EXPECT_EQ("Delegated-IPv6-Prefix=2001:db8::/64",
              delegated_prefix->toText());
    ConstAttributePtr session_id = attrs->get(PW_ACCT_SESSION_ID);
    ASSERT_TRUE(session_id);
    string strvalue;
    EXPECT_NO_THROW(strvalue = session_id->toString());
    EXPECT_EQ(handler->env_.session_id_, strvalue);
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with canonical hardware address.
void AccountingTest::testBuildAcctLease6canon() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20-e5-2a-b8-15-14'",
              calling_station_id->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with not pop0 duid.
void AccountingTest::testBuildAcctLease6noPop0() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
}

/// Verify that buildAcct on IPv6 lease works with not printable duid.
void AccountingTest::testBuildAcctLease6notPrintable() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with pop0 duid.
void AccountingTest::testBuildAcctLease6Pop0() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with printable duid.
void AccountingTest::testBuildAcctLease6Printable() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with printable pop0 duid.
void AccountingTest::testBuildAcctLease6Pop0Printable() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x00, 0x00, 0x46, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with RENEW event.
void AccountingTest::testBuildAcctLease6Renew() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_RENEW));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with EXPIRE event.
void AccountingTest::testBuildAcctLease6expire() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_EXPIRE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with RELEASE event.
void AccountingTest::testBuildAcctLease6Release() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_RELEASE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with DECLINE event.
void AccountingTest::testBuildAcctLease6Decline() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_DECLINE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with ADD event.
void AccountingTest::testBuildAcctLease6Add() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with UPDATE event.
void AccountingTest::testBuildAcctLease6Update() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_UPDATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6 lease works with DELete event.
void AccountingTest::testBuildAcctLease6Del() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct on IPv6/DUID can get the Class from host cache.
void AccountingTest::testBuildAcctLease6ClassDUID() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[0], id.size(),
                                        Host::IDENT_DUID, SUBNET_ID_UNUSED, 4,
                                        IOAddress::IPV4_ZERO_ADDRESS())));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct on IPv6/HwAddr can get the Class from host cache.
void AccountingTest::testBuildAcctLease6ClassHwAddr() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&hwaddr->hwaddr_[0],
                                        hwaddr->hwaddr_.size(),
                                        Host::IDENT_HWADDR, SUBNET_ID_UNUSED, 4,
                                        IOAddress::IPV4_ZERO_ADDRESS())));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct on IPv6/Flex can get the Class from host cache.
void AccountingTest::testBuildAcctLease6ClassFlex() {
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));

    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[2], id.size() - 2,
                                        Host::IDENT_FLEX, SUBNET_ID_UNUSED, 4,
                                        IOAddress::IPV4_ZERO_ADDRESS())));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr map = Element::createMap();
    map->set("radius", huc_attrs->toElement());
    host->setContext(map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct(lease, EVENT_CREATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct4 works.
void AccountingTest::testBuildAcct4() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    // EXPECT_EQ(xxx, handler->env_.session_id_);
    EXPECT_EQ(EVENT_ADD, handler->env_.event_);
    EXPECT_EQ(4, handler->env_.subnet_id_);
    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IP_ADDRESS);
    ASSERT_TRUE(framed_ip_address);
    EXPECT_EQ("Framed-IP-Address=192.0.2.1", framed_ip_address->toText());
    ConstAttributePtr session_id = attrs->get(PW_ACCT_SESSION_ID);
    ASSERT_TRUE(session_id);
    string strvalue;
    EXPECT_NO_THROW(strvalue = session_id->toString());
    EXPECT_EQ(handler->env_.session_id_, strvalue);
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 requires address.
void AccountingTest::testBuildAcct4noAddress() {
    ElementPtr map = Element::createMap();
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct4 requires subnet-id..
void AccountingTest::testBuildAcct4noSubnet() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct4 requires hardware address..
void AccountingTest::testBuildAcct4noHwAddr() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct4 works with canonical.
void AccountingTest::testBuildAcct4canon() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20-e5-2a-b8-15-14'",
              calling_station_id->toText());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IP_ADDRESS);
    EXPECT_EQ("Framed-IP-Address=192.0.2.1", framed_ip_address->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with no pop0 client-id.
void AccountingTest::testBuildAcct4noPop0() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with not printable client-id.
void AccountingTest::testBuildAcct4notPrintable() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with pop0 client-id.
void AccountingTest::testBuildAcct4Pop0() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("00:01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with printable client-id.
void AccountingTest::testBuildAcct4Printable() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("46:6f:6f:62:61:72"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with printable pop0 client-id.
void AccountingTest::testBuildAcct4Pop0Printable() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("00:46:6f:6f:62:61:72"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works without force-create.
void AccountingTest::testBuildAcct4noForce() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works without client-id.
void AccountingTest::testBuildAcct4noClientId() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(4, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='20:e5:2a:b8:15:14'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works without client-id and with canonical.
void AccountingTest::testBuildAcct4noClientIdcanon() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(4, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='20-e5-2a-b8-15-14'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with UPDATE event.
void AccountingTest::testBuildAcct4update() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_UPDATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 works with DELete event.
void AccountingTest::testBuildAcct4del() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct4 on ClientId can get the Class from host cache.
void AccountingTest::testBuildAcct4ClassClientID() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[0], id.size(),
                                        Host::IDENT_CLIENT_ID,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr huc_map = Element::createMap();
    huc_map->set("radius", huc_attrs->toElement());
    host->setContext(huc_map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct4 on HwAddr can get the Class from host cache.
void AccountingTest::testBuildAcct4ClassHwAddr() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&hw[0], hw.size(),
                                        Host::IDENT_HWADDR,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr huc_map = Element::createMap();
    huc_map->set("radius", huc_attrs->toElement());
    host->setContext(huc_map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct4 on Flex can get the Class from host cache.
void AccountingTest::testBuildAcct4ClassFlex() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("192.0.2.1"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("client-id", Element::create("00:01:02:03:04"));
    map->set("force-create", Element::create(true));

    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> id = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[1], id.size() - 1,
                                        Host::IDENT_FLEX,
                                        4, SUBNET_ID_UNUSED, addr)));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr huc_map = Element::createMap();
    huc_map->set("radius", huc_attrs->toElement());
    host->setContext(huc_map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct4(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct6 works.
void AccountingTest::testBuildAcct6() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    EXPECT_EQ(EVENT_ADD, handler->env_.event_);
    EXPECT_EQ(4, handler->env_.subnet_id_);
    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IPV6_ADDRESS);
    ASSERT_TRUE(framed_ip_address);
    EXPECT_EQ("Framed-IPv6-Address=2001:db8::1235",
              framed_ip_address->toText());
    ConstAttributePtr session_id = attrs->get(PW_ACCT_SESSION_ID);
    ASSERT_TRUE(session_id);
    string strvalue;
    EXPECT_NO_THROW(strvalue = session_id->toString());
    EXPECT_EQ(handler->env_.session_id_, strvalue);
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with a prefix.
void AccountingTest::testBuildAcct6prefix() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::"));
    map->set("prefix-len", Element::create(64));
    map->set("type", Element::create("IA_PD"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    EXPECT_EQ(EVENT_ADD, handler->env_.event_);
    EXPECT_EQ(4, handler->env_.subnet_id_);
    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20:e5:2a:b8:15:14'",
              calling_station_id->toText());
    ConstAttributePtr delegated_prefix = attrs->get(PW_DELEGATED_IPV6_PREFIX);
    ASSERT_TRUE(delegated_prefix);
    EXPECT_EQ("Delegated-IPv6-Prefix=2001:db8::/64",
              delegated_prefix->toText());
    ConstAttributePtr session_id = attrs->get(PW_ACCT_SESSION_ID);
    ASSERT_TRUE(session_id);
    string strvalue;
    EXPECT_NO_THROW(strvalue = session_id->toString());
    EXPECT_EQ(handler->env_.session_id_, strvalue);
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_START, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 requires address.
void AccountingTest::testBuildAcct6noAddress() {
    ElementPtr map = Element::createMap();
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 requires prefix-length with prefix.
void AccountingTest::testBuildAcct6noPDlength() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::"));
    map->set("type", Element::create("IA_PD"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 requires non zero prefix-length with prefix.
void AccountingTest::testBuildAcct6ZeroPDlength() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::"));
    map->set("type", Element::create("IA_PD"));
    map->set("prefix-len", Element::create(0));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 requires in range prefix-length with prefix.
void AccountingTest::testBuildAcct6LargePDlength() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::"));
    map->set("type", Element::create("IA_PD"));
    map->set("prefix-len", Element::create(129));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 requires prefix-length with prefix with no extra bits set.
void AccountingTest::testBuildAcct6InvalidPDlength() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::"));
    map->set("type", Element::create("IA_PD"));
    map->set("prefix-len", Element::create(16));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 requires subnet-id..
void AccountingTest::testBuildAcct6noSubnet() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 requires hardware address..
void AccountingTest::testBuildAcct6noDuid() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_FALSE(handler);
}

/// Verify that buildAcct6 works without type (default is IA_NA).
void AccountingTest::testBuildAcct6noType() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IPV6_ADDRESS);
    ASSERT_TRUE(framed_ip_address);
    EXPECT_EQ("Framed-IPv6-Address=2001:db8::1235",
              framed_ip_address->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with prefix.
void AccountingTest::testBuildAcct6Prefix() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::"));
    map->set("type", Element::create("IA_PD"));
    map->set("prefix-len", Element::create(64));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr delegated_prefix = attrs->get(PW_DELEGATED_IPV6_PREFIX);
    ASSERT_TRUE(delegated_prefix);
    EXPECT_EQ("Delegated-IPv6-Prefix=2001:db8::/64",
              delegated_prefix->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with canonical.
void AccountingTest::testBuildAcct6canon() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr calling_station_id = attrs->get(PW_CALLING_STATION_ID);
    ASSERT_TRUE(calling_station_id);
    EXPECT_EQ("Calling-Station-Id='20-e5-2a-b8-15-14'",
              calling_station_id->toText());
    ConstAttributePtr framed_ip_address = attrs->get(PW_FRAMED_IPV6_ADDRESS);
    EXPECT_EQ("Framed-IPv6-Address=2001:db8::1235",
              framed_ip_address->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with no pop0 duid.
void AccountingTest::testBuildAcct6noPop0() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with not printable duid.
void AccountingTest::testBuildAcct6notPrintable() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with pop0 duid.
void AccountingTest::testBuildAcct6Pop0() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("00:00:01:02:03:04"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='01:02:03:04'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with printable duid.
void AccountingTest::testBuildAcct6Printable() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("46:6f:6f:62:61:72"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with printable pop0 duid.
void AccountingTest::testBuildAcct6Pop0Printable() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("00:00:46:6f:6f:62:61:72"));
    map->set("force-create", Element::create(true));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr user_name = attrs->get(PW_USER_NAME);
    ASSERT_TRUE(user_name);
    EXPECT_EQ("User-Name='Foobar'", user_name->toText());
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works without force-create.
void AccountingTest::testBuildAcct6noForce() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_ADD));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with UPDATE event.
void AccountingTest::testBuildAcct6update() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_UPDATE));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_ALIVE, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 works with DELete event.
void AccountingTest::testBuildAcct6del() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(5, attrs->size());
    ConstAttributePtr status_type = attrs->get(PW_ACCT_STATUS_TYPE);
    ASSERT_TRUE(status_type);
    uint32_t lvalue = 111;
    EXPECT_NO_THROW(lvalue = status_type->toInt());
    EXPECT_EQ(PW_STATUS_STOP, lvalue);
    EXPECT_EQ(0, attrs->count(PW_CLASS));
}

/// Verify that buildAcct6 on DUID can get the Class from host cache.
void AccountingTest::testBuildAcct6ClassDUID() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));

    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[0], id.size(),
                                        Host::IDENT_DUID, SUBNET_ID_UNUSED, 4,
                                        IOAddress::IPV4_ZERO_ADDRESS())));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr huc_map = Element::createMap();
    huc_map->set("radius", huc_attrs->toElement());
    host->setContext(huc_map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct6 on HwAddr can get the Class from host cache.
void AccountingTest::testBuildAcct6ClassHwAddr() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("01:02:03:04"));

    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&hw[0], hw.size(),
                                        Host::IDENT_HWADDR, SUBNET_ID_UNUSED, 4,
                                        IOAddress::IPV4_ZERO_ADDRESS())));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr huc_map = Element::createMap();
    huc_map->set("radius", huc_attrs->toElement());
    host->setContext(huc_map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that buildAcct6 on Flex can get the Class from host cache.
void AccountingTest::testBuildAcct6ClassFlex() {
    ElementPtr map = Element::createMap();
    map->set("ip-address", Element::create("2001:db8::1235"));
    map->set("type", Element::create("IA_NA"));
    map->set("subnet-id", Element::create(4));
    map->set("hw-address", Element::create("20:e5:2a:b8:15:14"));
    map->set("duid", Element::create("00:00:01:02:03:04"));

    vector<uint8_t> id = { 0x00, 0x00, 0x01, 0x02, 0x03, 0x04 };
    HostPtr host;
    ASSERT_NO_THROW(host.reset(new Host(&id[2], id.size() - 2,
                                        Host::IDENT_FLEX, SUBNET_ID_UNUSED, 4,
                                        IOAddress::IPV4_ZERO_ADDRESS())));
    ASSERT_TRUE(host);
    AttributesPtr huc_attrs(new Attributes());
    huc_attrs->add(Attribute::fromString(PW_CLASS, "foobar"));
    ElementPtr huc_map = Element::createMap();
    huc_map->set("radius", huc_attrs->toElement());
    host->setContext(huc_map);
    cache_->insert(host, true);

    RadiusAcctHandlerPtr handler;
    ASSERT_NO_THROW(handler = impl_.acct_->buildAcct6(map, EVENT_DEL));
    ASSERT_TRUE(handler);

    AttributesPtr attrs = handler->env_.send_attrs_;
    ASSERT_TRUE(attrs);
    ASSERT_LE(6, attrs->size());
    ConstAttributePtr cclass = attrs->get(PW_CLASS);
    ASSERT_TRUE(cclass);
    EXPECT_EQ("Class='foobar'", cclass->toText());
}

/// Verify that lease4_select hook returns for fake allocations.
void AccountingTest::testLease4SelectFake() {
    CalloutHandle handle(manager_);
    bool fake_allocation = true;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));
    handle.setArgument("lease4", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease4_select hook sends a START.
void AccountingTest::testLease4Select() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));
    handle.setArgument("lease4", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease4_select(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease4_renew hook sends a ALIVE.
void AccountingTest::testLease4Renew() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));
    handle.setArgument("lease4", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease4_renew(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease4_release hook sends a STOP.
void AccountingTest::testLease4Release() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));
    handle.setArgument("lease4", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease4_release(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease4_decline hook sends a STOP.
void AccountingTest::testLease4Decline() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));
    handle.setArgument("lease4", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease4_decline(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease4_expire hook sends a STOP.
void AccountingTest::testLease4Expire() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("192.0.2.1");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ClientIdPtr clientid(new ClientId(id));
    Lease4Ptr lease(new Lease4(addr, hwaddr, clientid, 4, 1, 4));
    handle.setArgument("lease4", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease4_expire(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease6_select hook returns for fake allocations.
void AccountingTest::testLease6SelectFake() {
    CalloutHandle handle(manager_);
    bool fake_allocation = true;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));
    handle.setArgument("lease6", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease6_select(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease6_select hook sends a START.
void AccountingTest::testLease6Select() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));
    handle.setArgument("lease6", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease6_select(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease6_renew hook sends a ALIVE.
void AccountingTest::testLease6Renew() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));
    handle.setArgument("lease6", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease6_renew(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease6_release hook sends a STOP.
void AccountingTest::testLease6Release() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));
    handle.setArgument("lease6", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease6_release(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease6_decline hook sends a STOP.
void AccountingTest::testLease6Decline() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));
    handle.setArgument("lease6", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease6_decline(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that lease6_expire hook sends a STOP.
void AccountingTest::testLease6Expire() {
    CalloutHandle handle(manager_);
    bool fake_allocation = false;
    handle.setArgument("fake_allocation", fake_allocation);
    IOAddress addr = IOAddress("2001:db8::1235");
    vector<uint8_t> hw = { 0x20, 0xe5, 0x2a, 0xb8, 0x15, 0x14 };
    HWAddrPtr hwaddr(new HWAddr(hw, 1));
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    DuidPtr duid(new DUID(id));
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, 0x12345678,
                               1, 2, 4, hwaddr));
    handle.setArgument("lease6", lease);

    int ret(-1);
    ASSERT_NO_THROW(ret = lease6_expire(handle));
    EXPECT_EQ(0, ret);
}

/// Verify that the command_processed hook with peer-updates enabled by default
/// properly sends an accounting request for a lease4-update command with origin
/// set to "ha-partner", effectively simulating an HA lease update.
void AccountingTest::testCommandProcessed() {
    ConstElementPtr arguments(Element::fromJSON(R"({
        "client-id": "01:00:0c:01:02:03:04",
        "expire": 1800000000,
        "force-create": true,
        "fqdn-fwd": false,
        "fqdn-rev": false,
        "hostname": "",
        "hw-address": "00:0c:01:02:03:04",
        "ip-address": "192.0.2.1",
        "origin": "ha-partner",
        "state": 0,
        "subnet-id": 1,
        "user-context": {
            "ISC": {
                "client-classes": [
                    "ALL",
                    "UNKNOWN"
                ]
            }
        },
        "valid-lft": 7200
    })"));
    ConstElementPtr response(Element::fromJSON(R"({
        "result": 0,
        "text": "IPv4 lease added."
    })"));
    CalloutHandle handle(manager_);
    handle.setArgument("name", string("lease4-update"));
    handle.setArgument("arguments", arguments);
    handle.setArgument("response", response);

    EXPECT_EQ(0, service_->pollOne());

    int ret(-1);
    EXPECT_NO_THROW_LOG(ret = command_processed(handle));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, ret);
}

/// Verify that the command_processed hook with peer-updates enabled by default
/// properly sends an accounting request for a lease4-update command with no
/// origin set, effectively simulating a user-provided command.
void AccountingTest::testCommandProcessedNoOrigin() {
    ConstElementPtr arguments(Element::fromJSON(R"({
        "client-id": "01:00:0c:01:02:03:04",
        "expire": 1800000000,
        "force-create": true,
        "fqdn-fwd": false,
        "fqdn-rev": false,
        "hostname": "",
        "hw-address": "00:0c:01:02:03:04",
        "ip-address": "192.0.2.1",
        "state": 0,
        "subnet-id": 1,
        "user-context": {
            "ISC": {
                "client-classes": [
                    "ALL",
                    "UNKNOWN"
                ]
            }
        },
        "valid-lft": 7200
    })"));
    ConstElementPtr response(Element::fromJSON(R"({
        "result": 0,
        "text": "IPv4 lease added."
    })"));
    CalloutHandle handle(manager_);
    handle.setArgument("name", string("lease4-update"));
    handle.setArgument("arguments", arguments);
    handle.setArgument("response", response);

    EXPECT_EQ(0, service_->pollOne());

    int ret(-1);
    EXPECT_NO_THROW_LOG(ret = command_processed(handle));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, ret);
}

/// Verify that the command_processed hook with peer-updates explicitly disabled
/// does not send an accounting request for a lease4-update command with origin
/// set to "ha-partner", effectively simulating blocking an HA lease update.
void AccountingTest::testNoPeerUpdates() {
    ConstElementPtr arguments(Element::fromJSON(R"({
        "client-id": "01:00:0c:01:02:03:04",
        "expire": 1800000000,
        "force-create": true,
        "fqdn-fwd": false,
        "fqdn-rev": false,
        "hostname": "",
        "hw-address": "00:0c:01:02:03:04",
        "ip-address": "192.0.2.1",
        "origin": "ha-partner",
        "state": 0,
        "subnet-id": 1,
        "user-context": {
            "ISC": {
                "client-classes": [
                    "ALL",
                    "UNKNOWN"
                ]
            }
        },
        "valid-lft": 7200
    })"));
    ConstElementPtr response(Element::fromJSON(R"({
        "result": 0,
        "text": "IPv4 lease added."
    })"));
    CalloutHandle handle(manager_);
    handle.setArgument("name", string("lease4-update"));
    handle.setArgument("arguments", arguments);
    handle.setArgument("response", response);

    EXPECT_EQ(0, service_->pollOne());

    int ret(-1);
    EXPECT_NO_THROW_LOG(ret = command_processed(handle));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, ret);
}

/// Verify that the command_processed hook with peer-updates explicitly disabled
/// properly sends an accounting request for a lease4-update command with no
/// origin set, thereby checking that the flag has no effect on a user-provided
/// command.
void AccountingTest::testNoPeerUpdatesNoOrigin() {
    ConstElementPtr arguments(Element::fromJSON(R"({
        "client-id": "01:00:0c:01:02:03:04",
        "expire": 1800000000,
        "force-create": true,
        "fqdn-fwd": false,
        "fqdn-rev": false,
        "hostname": "",
        "hw-address": "00:0c:01:02:03:04",
        "ip-address": "192.0.2.1",
        "state": 0,
        "subnet-id": 1,
        "user-context": {
            "ISC": {
                "client-classes": [
                    "ALL",
                    "UNKNOWN"
                ]
            }
        },
        "valid-lft": 7200
    })"));
    ConstElementPtr response(Element::fromJSON(R"({
        "result": 0,
        "text": "IPv4 lease added."
    })"));
    CalloutHandle handle(manager_);
    handle.setArgument("name", string("lease4-update"));
    handle.setArgument("arguments", arguments);
    handle.setArgument("response", response);

    EXPECT_EQ(0, service_->pollOne());

    int ret(-1);
    EXPECT_NO_THROW_LOG(ret = command_processed(handle));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, ret);
}

/// Verify that the command_processed hook handles null arguments.
void AccountingTest::testCommandProcessedNullArguments() {
    CalloutHandle handle(manager_);
    handle.setArgument("name", string("lease4-update"));
    handle.setArgument("arguments", ConstElementPtr());
    handle.setArgument("response", ConstElementPtr());

    EXPECT_EQ(0, service_->pollOne());

    int ret(-1);
    EXPECT_NO_THROW_LOG(ret = command_processed(handle));
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, ret);
}

TEST_F(AccountingTest, eventToText) {
    testEventToText();
}
TEST_F(AccountingTest, buildAcctLease4) {
    testBuildAcctLease4();
}
TEST_F(AccountingTest, buildAcctLease4canon) {
    impl_.canonical_mac_address_ = true;
    testBuildAcctLease4canon();
}
TEST_F(AccountingTest, buildAcctLease4noDuid) {
    impl_.extract_duid_ = true;
    testBuildAcctLease4noDuid();
}
TEST_F(AccountingTest, buildAcctLease4noPop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcctLease4noPop0();
}
TEST_F(AccountingTest, buildAcctLease4notPrintable) {
    impl_.clientid_printable_ = true;
    testBuildAcctLease4notPrintable();
}
TEST_F(AccountingTest, buildAcctLease4Duid) {
    impl_.extract_duid_ = true;
    testBuildAcctLease4Duid();
}
TEST_F(AccountingTest, buildAcctLease4DuidPrintable) {
    impl_.extract_duid_ = true;
    impl_.clientid_printable_ = true;
    testBuildAcctLease4DuidPrintable();
}
TEST_F(AccountingTest, buildAcctLease4Pop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcctLease4Pop0();
}
TEST_F(AccountingTest, buildAcctLease4Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    testBuildAcctLease4Pop0Printable();
}
TEST_F(AccountingTest, buildAcctLease4noClientId) {
    testBuildAcctLease4noClientId();
}
TEST_F(AccountingTest, buildAcctLease4Renew) {
    testBuildAcctLease4Renew();
}
TEST_F(AccountingTest, buildAcctLease4expire) {
    testBuildAcctLease4expire();
}
TEST_F(AccountingTest, buildAcctLease4Release) {
    testBuildAcctLease4Release();
}
TEST_F(AccountingTest, buildAcctLease4Decline) {
    testBuildAcctLease4Decline();
}
TEST_F(AccountingTest, buildAcctLease4Add) {
    testBuildAcctLease4Add();
}
TEST_F(AccountingTest, buildAcctLease4Update) {
    testBuildAcctLease4Update();
}
TEST_F(AccountingTest, buildAcctLease4Del) {
    testBuildAcctLease4Del();
}
TEST_F(AccountingTest, buildAcctLease4ClassClientID) {
    impl_.clientid_printable_ = true;
    impl_.id_type4_ = Host::IDENT_CLIENT_ID;
    testBuildAcctLease4ClassClientID();
}
TEST_F(AccountingTest, buildAcctLease4ClassHwAddr) {
    impl_.id_type4_ = Host::IDENT_HWADDR;
    testBuildAcctLease4ClassHwAddr();
}
TEST_F(AccountingTest, buildAcctLease4ClassDuid) {
    impl_.id_type4_ = Host::IDENT_DUID;
    testBuildAcctLease4ClassDuid();
}
TEST_F(AccountingTest, buildAcctLease4ClassFlex) {
    testBuildAcctLease4ClassFlex();
}
TEST_F(AccountingTest, buildAcctLease6) {
    testBuildAcctLease6();
}
TEST_F(AccountingTest, buildAcctLease6prefix) {
    testBuildAcctLease6prefix();
}
TEST_F(AccountingTest, buildAcctLease6canon) {
    impl_.canonical_mac_address_ = true;
    testBuildAcctLease6canon();
}
TEST_F(AccountingTest, buildAcctLease6noPop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcctLease6noPop0();
}
TEST_F(AccountingTest, buildAcctLease6notPrintable) {
    impl_.clientid_printable_ = true;
    testBuildAcctLease6notPrintable();
}
TEST_F(AccountingTest, buildAcctLease6Pop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcctLease6Pop0();
}
TEST_F(AccountingTest, buildAcctLease6Printable) {
    impl_.clientid_printable_ = true;
    testBuildAcctLease6Printable();
}
TEST_F(AccountingTest, buildAcctLease6Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    testBuildAcctLease6Pop0Printable();
}
TEST_F(AccountingTest, buildAcctLease6Renew) {
    testBuildAcctLease6Renew();
}
TEST_F(AccountingTest, buildAcctLease6expire) {
    testBuildAcctLease6expire();
}
TEST_F(AccountingTest, buildAcctLease6Release) {
    testBuildAcctLease6Release();
}
TEST_F(AccountingTest, buildAcctLease6Decline) {
    testBuildAcctLease6Decline();
}
TEST_F(AccountingTest, buildAcctLease6Add) {
    testBuildAcctLease6Add();
}
TEST_F(AccountingTest, buildAcctLease6Update) {
    testBuildAcctLease6Update();
}
TEST_F(AccountingTest, buildAcctLease6Del) {
    testBuildAcctLease6Del();
}
TEST_F(AccountingTest, buildAcctLease6ClassDUID) {
    impl_.id_type6_ = Host::IDENT_DUID;
    testBuildAcctLease6ClassDUID();
}
TEST_F(AccountingTest, buildAcctLease6ClassHwAddr) {
    impl_.id_type6_ = Host::IDENT_HWADDR;
    testBuildAcctLease6ClassHwAddr();
}
TEST_F(AccountingTest, buildAcctLease6ClassFlex) {
    testBuildAcctLease6ClassFlex();
}
TEST_F(AccountingTest, buildAcct4) {
    testBuildAcct4();
}
TEST_F(AccountingTest, buildAcct4noAddress) {
    testBuildAcct4noAddress();
}
TEST_F(AccountingTest, buildAcct4noSubnet) {
    testBuildAcct4noSubnet();
}
TEST_F(AccountingTest, buildAcct4noHwAddr) {
    testBuildAcct4noHwAddr();
}
TEST_F(AccountingTest, buildAcct4canon) {
    impl_.canonical_mac_address_ = true;
    testBuildAcct4canon();
}
TEST_F(AccountingTest, buildAcct4noPop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcct4noPop0();
}
TEST_F(AccountingTest, buildAcct4notPrintable) {
    impl_.clientid_printable_ = true;
    testBuildAcct4notPrintable();
}
TEST_F(AccountingTest, buildAcct4Pop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcct4Pop0();
}
TEST_F(AccountingTest, buildAcct4Printable) {
    impl_.clientid_printable_ = true;
    testBuildAcct4Printable();
}
TEST_F(AccountingTest, buildAcct4Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    testBuildAcct4Pop0Printable();
}
TEST_F(AccountingTest, buildAcct4noForce) {
    testBuildAcct4noForce();
}
TEST_F(AccountingTest, buildAcct4noClientId) {
    testBuildAcct4noClientId();
}
TEST_F(AccountingTest, buildAcct4noClientIdcanon) {
    impl_.canonical_mac_address_ = true;
    testBuildAcct4noClientIdcanon();
}
TEST_F(AccountingTest, buildAcct4update) {
    testBuildAcct4update();
}
TEST_F(AccountingTest, buildAcct4del) {
    testBuildAcct4del();
}
TEST_F(AccountingTest, buildAcct4ClassClientID) {
    impl_.clientid_printable_ = true;
    impl_.id_type4_ = Host::IDENT_CLIENT_ID;
    testBuildAcct4ClassClientID();
}
TEST_F(AccountingTest, buildAcct4ClassHwAddr) {
    impl_.clientid_printable_ = true;
    impl_.id_type4_ = Host::IDENT_HWADDR;
    testBuildAcct4ClassHwAddr();
}
TEST_F(AccountingTest, buildAcct4ClassFlex) {
    impl_.clientid_printable_ = true;
    testBuildAcct4ClassFlex();
}
TEST_F(AccountingTest, buildAcct6) {
    testBuildAcct6();
}
TEST_F(AccountingTest, buildAcct6prefix) {
    testBuildAcct6prefix();
}
TEST_F(AccountingTest, buildAcct6noAddress) {
    testBuildAcct6noAddress();
}
TEST_F(AccountingTest, buildAcct6noPDlength) {
    testBuildAcct6noPDlength();
}
TEST_F(AccountingTest, buildAcct6ZeroPDlength) {
    testBuildAcct6ZeroPDlength();
}
TEST_F(AccountingTest, buildAcct6LargePDlength) {
    testBuildAcct6LargePDlength();
}
TEST_F(AccountingTest, buildAcct6InvalidPDlength) {
    testBuildAcct6InvalidPDlength();
}
TEST_F(AccountingTest, buildAcct6noSubnet) {
    testBuildAcct6noSubnet();
}
TEST_F(AccountingTest, buildAcct6noDuid) {
    testBuildAcct6noDuid();
}
TEST_F(AccountingTest, buildAcct6noType) {
    testBuildAcct6noType();
}
TEST_F(AccountingTest, buildAcct6Prefix) {
    testBuildAcct6Prefix();
}
TEST_F(AccountingTest, buildAcct6canon) {
    impl_.canonical_mac_address_ = true;
    testBuildAcct6canon();
}
TEST_F(AccountingTest, buildAcct6noPop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcct6noPop0();
}
TEST_F(AccountingTest, buildAcct6notPrintable) {
    impl_.clientid_printable_ = true;
    testBuildAcct6notPrintable();
}
TEST_F(AccountingTest, buildAcct6Pop0) {
    impl_.clientid_pop0_ = true;
    testBuildAcct6Pop0();
}
TEST_F(AccountingTest, buildAcct6Printable) {
    impl_.clientid_printable_ = true;
    testBuildAcct6Printable();
}
TEST_F(AccountingTest, buildAcct6Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    testBuildAcct6Pop0Printable();
}
TEST_F(AccountingTest, buildAcct6noForce) {
    testBuildAcct6noForce();
}
TEST_F(AccountingTest, buildAcct6update) {
    testBuildAcct6update();
}
TEST_F(AccountingTest, buildAcct6del) {
    testBuildAcct6del();
}
TEST_F(AccountingTest, buildAcct6ClassDUID) {
    impl_.id_type6_ = Host::IDENT_DUID;
    testBuildAcct6ClassDUID();
}
TEST_F(AccountingTest, buildAcct6ClassHwAddr) {
    impl_.id_type6_ = Host::IDENT_HWADDR;
    testBuildAcct6ClassHwAddr();
}
TEST_F(AccountingTest, buildAcct6ClassFlex) {
    testBuildAcct6ClassFlex();
}
TEST_F(AccountingTest, lease4SelectFake) {
    testLease4SelectFake();
}
TEST_F(AccountingTest, lease4Select) {
    startServer();

    testLease4Select();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_START, status_types_[0]);
}
TEST_F(AccountingTest, lease4Renew) {
    startServer();

    testLease4Renew();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_ALIVE, status_types_[0]);
}
TEST_F(AccountingTest, lease4Release) {
    startServer();

    testLease4Release();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_STOP, status_types_[0]);
}
TEST_F(AccountingTest, lease4Decline) {
    startServer();

    testLease4Decline();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_STOP, status_types_[0]);
}
TEST_F(AccountingTest, lease4Expire) {
    startServer();

    testLease4Expire();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_STOP, status_types_[0]);
}
TEST_F(AccountingTest, lease6SelectFake) {
    testLease6SelectFake();
}
TEST_F(AccountingTest, lease6Select) {
    startServer();

    testLease6Select();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_START, status_types_[0]);
}
TEST_F(AccountingTest, lease6Renew) {
    startServer();

    testLease6Renew();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_ALIVE, status_types_[0]);
}
TEST_F(AccountingTest, lease6Release) {
    startServer();

    testLease6Release();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_STOP, status_types_[0]);
}
TEST_F(AccountingTest, lease6Decline) {
    startServer();

    testLease6Decline();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_STOP, status_types_[0]);
}
TEST_F(AccountingTest, lease6Expire) {
    startServer();

    testLease6Expire();

    waitForServerToFinish();

    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_STOP, status_types_[0]);
}
TEST_F(AccountingTest, commandProcessed) {
    startServer();

    testCommandProcessed();

    waitForServerToFinish();

    // The mocked accounting request should have been sent, effectively
    // setting the status type.
    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_ALIVE, status_types_[0]);
}
TEST_F(AccountingTest, commandProcessedNoOrigin) {
    startServer();

    testCommandProcessedNoOrigin();

    waitForServerToFinish();

    // The mocked accounting request should have been sent, effectively
    // setting the status type.
    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_ALIVE, status_types_[0]);
}
TEST_F(AccountingTest, commandProcessedNullArguments) {
    timeout_expected_ = true;

    startServer();

    testCommandProcessedNullArguments();

    waitForServerToFinish();

    // No accounting request should have been called. There should be no status type.
    ASSERT_EQ(0, status_types_.size());
}
TEST_F(AccountingTest, noPeerUpdates) {
    impl_.acct_->peer_updates_ = false;
    timeout_expected_ = true;
    startServer();

    testNoPeerUpdates();

    waitForServerToFinish();

    // No accounting request should have been called. There should be no status type.
    ASSERT_EQ(0, status_types_.size());
}
TEST_F(AccountingTest, noPeerUpdatesNoOrigin) {
    impl_.acct_->peer_updates_ = false;
    startServer();

    testNoPeerUpdatesNoOrigin();

    waitForServerToFinish();

    // The mocked accounting request should have been sent, effectively
    // setting the status type.
    ASSERT_EQ(1, status_types_.size());
    EXPECT_EQ(PW_STATUS_ALIVE, status_types_[0]);
}

TEST_F(MTAccountingTest, eventToText) {
    run([this]() { testEventToText(); });
}
TEST_F(MTAccountingTest, buildAcctLease4) {
    run([this]() { testBuildAcctLease4(); });
}
TEST_F(MTAccountingTest, buildAcctLease4canon) {
    impl_.canonical_mac_address_ = true;
    run([this]() { testBuildAcctLease4canon(); });
}
TEST_F(MTAccountingTest, buildAcctLease4noDuid) {
    impl_.extract_duid_ = true;
    run([this]() { testBuildAcctLease4noDuid(); });
}
TEST_F(MTAccountingTest, buildAcctLease4noPop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcctLease4noPop0(); });
}
TEST_F(MTAccountingTest, buildAcctLease4notPrintable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcctLease4notPrintable(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Duid) {
    impl_.extract_duid_ = true;
    run([this]() { testBuildAcctLease4Duid(); });
}
TEST_F(MTAccountingTest, buildAcctLease4DuidPrintable) {
    impl_.extract_duid_ = true;
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcctLease4DuidPrintable(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Pop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcctLease4Pop0(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcctLease4Pop0Printable(); });
}
TEST_F(MTAccountingTest, buildAcctLease4noClientId) {
    run([this]() { testBuildAcctLease4noClientId(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Renew) {
    run([this]() { testBuildAcctLease4Renew(); });
}
TEST_F(MTAccountingTest, buildAcctLease4expire) {
    run([this]() { testBuildAcctLease4expire(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Release) {
    run([this]() { testBuildAcctLease4Release(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Decline) {
    run([this]() { testBuildAcctLease4Decline(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Add) {
    run([this]() { testBuildAcctLease4Add(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Update) {
    run([this]() { testBuildAcctLease4Update(); });
}
TEST_F(MTAccountingTest, buildAcctLease4Del) {
    run([this]() { testBuildAcctLease4Del(); });
}
TEST_F(MTAccountingTest, buildAcctLease4ClassClientID) {
    impl_.id_type4_ = Host::IDENT_CLIENT_ID;
    run([this]() { testBuildAcctLease4ClassClientID(); });
}
TEST_F(MTAccountingTest, buildAcctLease4ClassHwAddr) {
    impl_.id_type4_ = Host::IDENT_HWADDR;
    run([this]() { testBuildAcctLease4ClassHwAddr(); });
}
TEST_F(MTAccountingTest, buildAcctLease4ClassDuid) {
    impl_.id_type4_ = Host::IDENT_DUID;

    run([this]() { testBuildAcctLease4ClassDuid(); });
}
TEST_F(MTAccountingTest, buildAcctLease4ClassFlex) {
    run([this]() { testBuildAcctLease4ClassFlex(); });
}
TEST_F(MTAccountingTest, buildAcctLease6) {
    run([this]() { testBuildAcctLease6(); });
}
TEST_F(MTAccountingTest, buildAcctLease6prefix) {
    run([this]() { testBuildAcctLease6prefix(); });
}
TEST_F(MTAccountingTest, buildAcctLease6canon) {
    impl_.canonical_mac_address_ = true;
    run([this]() { testBuildAcctLease6canon(); });
}
TEST_F(MTAccountingTest, buildAcctLease6noPop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcctLease6noPop0(); });
}
TEST_F(MTAccountingTest, buildAcctLease6notPrintable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcctLease6notPrintable(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Pop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcctLease6Pop0(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Printable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcctLease6Printable(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcctLease6Pop0Printable(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Renew) {
    run([this]() { testBuildAcctLease6Renew(); });
}
TEST_F(MTAccountingTest, buildAcctLease6expire) {
    run([this]() { testBuildAcctLease6expire(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Release) {
    run([this]() { testBuildAcctLease6Release(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Decline) {
    run([this]() { testBuildAcctLease6Decline(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Add) {
    run([this]() { testBuildAcctLease6Add(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Update) {
    run([this]() { testBuildAcctLease6Update(); });
}
TEST_F(MTAccountingTest, buildAcctLease6Del) {
    run([this]() { testBuildAcctLease6Del(); });
}
TEST_F(MTAccountingTest, buildAcctLease6ClassDUID) {
    impl_.id_type6_ = Host::IDENT_DUID;

    run([this]() { testBuildAcctLease6ClassDUID(); });
}
TEST_F(MTAccountingTest, buildAcctLease6ClassHwAddr) {
    impl_.id_type6_ = Host::IDENT_HWADDR;
    run([this]() { testBuildAcctLease6ClassHwAddr(); });
}
TEST_F(MTAccountingTest, buildAcctLease6ClassFlex) {
    run([this]() { testBuildAcctLease6ClassFlex(); });
}
TEST_F(MTAccountingTest, buildAcct4) {
    run([this]() { testBuildAcct4(); });
}
TEST_F(MTAccountingTest, buildAcct4noAddress) {
    run([this]() { testBuildAcct4noAddress(); });
}
TEST_F(MTAccountingTest, buildAcct4noSubnet) {
    run([this]() { testBuildAcct4noSubnet(); });
}
TEST_F(MTAccountingTest, buildAcct4noHwAddr) {
    run([this]() { testBuildAcct4noHwAddr(); });
}
TEST_F(MTAccountingTest, buildAcct4canon) {
    impl_.canonical_mac_address_ = true;
    run([this]() { testBuildAcct4canon(); });
}
TEST_F(MTAccountingTest, buildAcct4noPop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcct4noPop0(); });
}
TEST_F(MTAccountingTest, buildAcct4notPrintable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct4notPrintable(); });
}
TEST_F(MTAccountingTest, buildAcct4Pop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcct4Pop0(); });
}
TEST_F(MTAccountingTest, buildAcct4Printable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct4Printable(); });
}
TEST_F(MTAccountingTest, buildAcct4Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct4Pop0Printable(); });
}
TEST_F(MTAccountingTest, buildAcct4noForce) {
    run([this]() { testBuildAcct4noForce(); });
}
TEST_F(MTAccountingTest, buildAcct4noClientId) {
    run([this]() { testBuildAcct4noClientId(); });
}
TEST_F(MTAccountingTest, buildAcct4noClientIdcanon) {
    impl_.canonical_mac_address_ = true;
    run([this]() { testBuildAcct4noClientIdcanon(); });
}
TEST_F(MTAccountingTest, buildAcct4update) {
    run([this]() { testBuildAcct4update(); });
}
TEST_F(MTAccountingTest, buildAcct4del) {
    run([this]() { testBuildAcct4del(); });
}
TEST_F(MTAccountingTest, buildAcct4ClassClientID) {
    impl_.clientid_printable_ = true;
    impl_.id_type4_ = Host::IDENT_CLIENT_ID;
    run([this]() { testBuildAcct4ClassClientID(); });
}
TEST_F(MTAccountingTest, buildAcct4ClassHwAddr) {
    impl_.clientid_printable_ = true;
    impl_.id_type4_ = Host::IDENT_HWADDR;
    run([this]() { testBuildAcct4ClassHwAddr(); });
}
TEST_F(MTAccountingTest, buildAcct4ClassFlex) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct4ClassFlex(); });
}
TEST_F(MTAccountingTest, buildAcct6) {
    run([this]() { testBuildAcct6(); });
}
TEST_F(MTAccountingTest, buildAcct6prefix) {
    run([this]() { testBuildAcct6prefix(); });
}
TEST_F(MTAccountingTest, buildAcct6noAddress) {
    run([this]() { testBuildAcct6noAddress(); });
}
TEST_F(MTAccountingTest, buildAcct6noPDlength) {
    run([this]() { testBuildAcct6noPDlength(); });
}
TEST_F(MTAccountingTest, buildAcct6ZeroPDlength) {
    run([this]() { testBuildAcct6ZeroPDlength(); });
}
TEST_F(MTAccountingTest, buildAcct6LargePDlength) {
    run([this]() { testBuildAcct6LargePDlength(); });
}
TEST_F(MTAccountingTest, buildAcct6InvalidPDlength) {
    run([this]() { testBuildAcct6InvalidPDlength(); });
}
TEST_F(MTAccountingTest, buildAcct6noSubnet) {
    run([this]() { testBuildAcct6noSubnet(); });
}
TEST_F(MTAccountingTest, buildAcct6noDuid) {
    run([this]() { testBuildAcct6noDuid(); });
}
TEST_F(MTAccountingTest, buildAcct6noType) {
    run([this]() { testBuildAcct6noType(); });
}
TEST_F(MTAccountingTest, buildAcct6Prefix) {
    run([this]() { testBuildAcct6Prefix(); });
}
TEST_F(MTAccountingTest, buildAcct6canon) {
    impl_.canonical_mac_address_ = true;
    run([this]() { testBuildAcct6canon(); });
}
TEST_F(MTAccountingTest, buildAcct6noPop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcct6noPop0(); });
}
TEST_F(MTAccountingTest, buildAcct6notPrintable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct6notPrintable(); });
}
TEST_F(MTAccountingTest, buildAcct6Pop0) {
    impl_.clientid_pop0_ = true;
    run([this]() { testBuildAcct6Pop0(); });
}
TEST_F(MTAccountingTest, buildAcct6Printable) {
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct6Printable(); });
}
TEST_F(MTAccountingTest, buildAcct6Pop0Printable) {
    impl_.clientid_pop0_ = true;
    impl_.clientid_printable_ = true;
    run([this]() { testBuildAcct6Pop0Printable(); });
}
TEST_F(MTAccountingTest, buildAcct6noForce) {
    run([this]() { testBuildAcct6noForce(); });
}
TEST_F(MTAccountingTest, buildAcct6update) {
    run([this]() { testBuildAcct6update(); });
}
TEST_F(MTAccountingTest, buildAcct6del) {
    run([this]() { testBuildAcct6del(); });
}
TEST_F(MTAccountingTest, buildAcct6ClassDUID) {
    impl_.id_type6_ = Host::IDENT_DUID;

    run([this]() { testBuildAcct6ClassDUID(); });
}
TEST_F(MTAccountingTest, buildAcct6ClassHwAddr) {
    impl_.id_type6_ = Host::IDENT_HWADDR;
    run([this]() { testBuildAcct6ClassHwAddr(); });
}
TEST_F(MTAccountingTest, buildAcct6ClassFlex) {
    run([this]() { testBuildAcct6ClassFlex(); });
}
TEST_F(MTAccountingTest, lease4SelectFake) {
    run([this]() { testLease4SelectFake(); });
}
TEST_F(MTAccountingTest, lease4Select) {
    startServer();

    run([this]() { testLease4Select(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_START, status);
    }
}
TEST_F(MTAccountingTest, lease4Renew) {
    startServer();

    run([this]() { testLease4Renew(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_ALIVE, status);
    }
}
TEST_F(MTAccountingTest, lease4Release) {
    startServer();

    run([this]() { testLease4Release(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_STOP, status);
    }
}
TEST_F(MTAccountingTest, lease4Decline) {
    startServer();

    run([this]() { testLease4Decline(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_STOP, status);
    }
}
TEST_F(MTAccountingTest, lease4Expire) {
    startServer();

    run([this]() { testLease4Expire(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_STOP, status);
    }
}
TEST_F(MTAccountingTest, lease6SelectFake) {
    run([this]() { testLease6SelectFake(); });
}
TEST_F(MTAccountingTest, lease6Select) {
    startServer();

    run([this]() { testLease6Select(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_START, status);
    }
}
TEST_F(MTAccountingTest, lease6Renew) {
    startServer();

    run([this]() { testLease6Renew(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_ALIVE, status);
    }
}
TEST_F(MTAccountingTest, lease6Release) {
    startServer();

    run([this]() { testLease6Release(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_STOP, status);
    }
}
TEST_F(MTAccountingTest, lease6Decline) {
    startServer();

    run([this]() { testLease6Decline(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_STOP, status);
    }
}
TEST_F(MTAccountingTest, lease6Expire) {
    startServer();

    run([this]() { testLease6Expire(); });

    waitForServerToFinish();

    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_STOP, status);
    }
}
TEST_F(MTAccountingTest, commandProcessed) {
    startServer();

    run([this]() { testCommandProcessed(); });

    waitForServerToFinish();

    // The mocked accounting request should have been sent, effectively
    // setting the status types.
    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_ALIVE, status);
    }
}
TEST_F(MTAccountingTest, commandProcessedNoOrigin) {
    startServer();

    run([this]() { testCommandProcessedNoOrigin(); });

    waitForServerToFinish();

    // The mocked accounting request should have been sent, effectively
    // setting the status types.
    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_ALIVE, status);
    }
}
TEST_F(MTAccountingTest, commandProcessedNullArguments) {
    timeout_expected_ = true;

    startServer();

    run([this]() { testCommandProcessedNullArguments(); });

    waitForServerToFinish();

    // No accounting request should have been called. There should be no status type.
    ASSERT_EQ(0, status_types_.size());
}
TEST_F(MTAccountingTest, noPeerUpdates) {
    impl_.acct_->peer_updates_ = false;
    timeout_expected_ = true;
    startServer();

    run([this]() { testNoPeerUpdates(); });

    waitForServerToFinish();

    // No accounting request should have been called. There should be no status type.
    ASSERT_EQ(0, status_types_.size());
}
TEST_F(MTAccountingTest, noPeerUpdatesNoOrigin) {
    impl_.acct_->peer_updates_ = false;
    startServer();

    run([this]() { testNoPeerUpdatesNoOrigin(); });

    waitForServerToFinish();

    // The mocked accounting request should have been sent, effectively
    // setting the status types.
    ASSERT_EQ(expected_received_, status_types_.size());
    for (AcctStatusType const status : status_types_) {
        EXPECT_EQ(PW_STATUS_ALIVE, status);
    }
}

/// @todo: missing tests for session-history, both in memory and disk operations.

} // end of anonymous namespace
