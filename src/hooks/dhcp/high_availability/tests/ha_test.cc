// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <ha_test.h>
#include <asiolink/interval_timer.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <util/range_utilities.h>
#include <functional>
#include <utility>
#include <vector>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;

namespace {

/// @brief Structure that holds registered hook indexes.
struct TestHooks {
    int hooks_index_dhcp4_srv_configured_;

    /// Constructor that registers hook points for the tests.
    TestHooks() {
        hooks_index_dhcp4_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
    }
};

TestHooks Hooks;

}

namespace isc {
namespace ha {
namespace test {

HATest::HATest()
    : io_service_(new IOService()),
      network_state_(new NetworkState(NetworkState::DHCPv4)) {
}

HATest::~HATest() {
}

void
HATest::startHAService() {
    if (HooksManager::calloutsPresent(Hooks.hooks_index_dhcp4_srv_configured_)) {
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("io_context", io_service_);
        callout_handle->setArgument("network_state", network_state_);
        HooksManager::callCallouts(Hooks.hooks_index_dhcp4_srv_configured_,
                                   *callout_handle);
    }
}

void
HATest::runIOService(long ms) {
    io_service_->get_io_service().reset();
    IntervalTimer timer(*io_service_);
    timer.setup(std::bind(&IOService::stop, io_service_), ms,
                IntervalTimer::ONE_SHOT);
    io_service_->run();
    timer.cancel();
}

void
HATest::runIOService(long ms, std::function<bool()> stop_condition) {
    io_service_->get_io_service().reset();
    IntervalTimer timer(*io_service_);
    bool timeout = false;
    timer.setup(std::bind(&HATest::stopIOServiceHandler, this, std::ref(timeout)),
                ms, IntervalTimer::ONE_SHOT);

    while (!stop_condition() && !timeout) {
        io_service_->run_one();
    }

    timer.cancel();
}

boost::shared_ptr<std::thread>
HATest::runIOServiceInThread() {
    io_service_->get_io_service().reset();

    bool running = false;
    std::mutex mutex;
    std::condition_variable condvar;

    io_service_->post(std::bind(&HATest::signalServiceRunning, this, std::ref(running),
                                std::ref(mutex), std::ref(condvar)));
    boost::shared_ptr<std::thread>
        th(new std::thread(std::bind(&IOService::run, io_service_.get())));

    std::unique_lock<std::mutex> lock(mutex);
    while (!running) {
        condvar.wait(lock);
    }

    return (th);
}

void
HATest::testSynchronousCommands(std::function<void()> commands) {
    // Run IO service in thread.
    auto thread = runIOServiceInThread();

    // Run desired commands.
    commands();

    // Stop the IO service. This should cause the thread to terminate.
    io_service_->stop();
    thread->join();
}

void
HATest::signalServiceRunning(bool& running, std::mutex& mutex,
                             std::condition_variable& condvar) {
    std::lock_guard<std::mutex> lock(mutex);
    running = true;
    condvar.notify_one();
}

void
HATest::stopIOServiceHandler(bool& stop_flag) {
    stop_flag = true;
}

ConstElementPtr
HATest::createValidJsonConfiguration(const HAConfig::HAMode& ha_mode) const {
    std::ostringstream config_text;
    config_text <<
        "["
        "     {"
        "         \"this-server-name\": \"server1\","
        "         \"mode\": " << (ha_mode == HAConfig::LOAD_BALANCING ?
                                  "\"load-balancing\"" : "\"hot-standby\"") << ","
        "         \"sync-page-limit\": 3,"
        "         \"heartbeat-delay\": 1000,"
        "         \"max-response-delay\": 1000,"
        "         \"max-ack-delay\": 10000,"
        "         \"max-unacked-clients\": 10,"
        "         \"wait-backup-ack\": false,"
        "         \"peers\": ["
        "             {"
        "                 \"name\": \"server1\","
        "                 \"url\": \"http://127.0.0.1:18123/\","
        "                 \"role\": \"primary\","
        "                 \"auto-failover\": true"
        "             },"
        "             {"
        "                 \"name\": \"server2\","
        "                 \"url\": \"http://127.0.0.1:18124/\","
        "                 \"role\": " << (ha_mode == HAConfig::LOAD_BALANCING ?
                                          "\"secondary\"" : "\"standby\"") << ","
        "                 \"auto-failover\": true"
        "             },"
        "             {"
        "                 \"name\": \"server3\","
        "                 \"url\": \"http://127.0.0.1:18125/\","
        "                 \"role\": \"backup\","
        "                 \"auto-failover\": false"
        "             }"
        "         ]"
        "     }"
        "]";

    return (Element::fromJSON(config_text.str()));
}

ConstElementPtr
HATest::createValidPassiveBackupJsonConfiguration() const {
    std::ostringstream config_text;
    config_text <<
        "["
        "     {"
        "         \"this-server-name\": \"server1\","
        "         \"mode\": \"passive-backup\","
        "         \"wait-backup-ack\": false,"
        "         \"peers\": ["
        "             {"
        "                 \"name\": \"server1\","
        "                 \"url\": \"http://127.0.0.1:18123/\","
        "                 \"role\": \"primary\""
        "             },"
        "             {"
        "                 \"name\": \"server2\","
        "                 \"url\": \"http://127.0.0.1:18124/\","
        "                 \"role\": \"backup\""
        "             },"
        "             {"
        "                 \"name\": \"server3\","
        "                 \"url\": \"http://127.0.0.1:18125/\","
        "                 \"role\": \"backup\""
        "             }"
        "         ]"
        "     }"
        "]";

    return (Element::fromJSON(config_text.str()));
}


HAConfigPtr
HATest::createValidConfiguration(const HAConfig::HAMode& ha_mode) const {
    HAConfigPtr config_storage(new HAConfig());
    HAConfigParser parser;

    parser.parse(config_storage, createValidJsonConfiguration(ha_mode));
    return (config_storage);
}

HAConfigPtr
HATest::createValidPassiveBackupConfiguration() const {
    HAConfigPtr config_storage(new HAConfig());
    HAConfigParser parser;

    parser.parse(config_storage, createValidPassiveBackupJsonConfiguration());
    return (config_storage);
}

void
HATest::checkAnswer(const isc::data::ConstElementPtr& answer,
                    const int exp_status,
                    const std::string& exp_txt) {
    int rcode = 0;
    isc::data::ConstElementPtr comment;
    comment = isc::config::parseAnswer(rcode, answer);

    EXPECT_EQ(exp_status, rcode)
        << "Expected status code " << exp_status
        << " but received " << rcode << ", comment: "
        << (comment ? comment->str() : "(none)");

    // Ok, parseAnswer interface is weird. If there are no arguments,
    // it returns content of text. But if there is an argument,
    // it returns the argument and it's not possible to retrieve
    // "text" (i.e. comment).
    if (comment->getType() != Element::string) {
        comment = answer->get("text");
    }

    if (!exp_txt.empty()) {
        EXPECT_EQ(exp_txt, comment->stringValue());
    }
}

std::vector<uint8_t>
HATest::randomKey(const size_t key_size) const {
    std::vector<uint8_t> key(key_size);
    util::fillRandom(key.begin(), key.end());
    return (key);
}


Pkt4Ptr
HATest::createMessage4(const uint8_t msg_type, const uint8_t hw_address_seed,
                       const uint8_t client_id_seed, const uint16_t secs) const {
    Pkt4Ptr message(new Pkt4(msg_type, 0x1234));

    HWAddrPtr hw_address(new HWAddr(std::vector<uint8_t>(6, hw_address_seed),
                                    HTYPE_ETHER));
    message->setHWAddr(hw_address);
    message->setSecs(secs);

    if (client_id_seed > 0) {
        OptionPtr opt_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                           std::vector<uint8_t>(6, client_id_seed)));
        message->addOption(opt_client_id);
    }

    return (message);
}

Pkt4Ptr
HATest::createQuery4(const std::string& hw_address_text) const {
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 0x1234));
    HWAddr hwaddr = HWAddr::fromText(hw_address_text);
    query4->setHWAddr(HWAddrPtr(new HWAddr(hwaddr.hwaddr_, HTYPE_ETHER)));
    return (query4);
}

Pkt4Ptr
HATest::createQuery4(const std::vector<uint8_t>& hw_address,
                     const std::vector<uint8_t>& client_id) const {
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 0x1234));
    query4->setHWAddr(HWAddrPtr(new HWAddr(hw_address, HTYPE_ETHER)));
    if (!client_id.empty()) {
        OptionPtr opt_client_id(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                           client_id));
        query4->addOption(opt_client_id);
    }
    return (query4);
}

Pkt6Ptr
HATest::createQuery6(const std::vector<uint8_t>& duid) const {
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 0x1234));
    OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, duid));
    query6->addOption(opt_duid);
    return (query6);
}

Pkt6Ptr
HATest::createMessage6(const uint8_t msg_type, const uint8_t duid_seed,
                       const uint16_t elapsed_time) const {
    Pkt6Ptr message(new Pkt6(msg_type, 0x1234));

    OptionPtr opt_duid(new Option(Option::V6, D6O_CLIENTID, OptionBuffer(8, duid_seed)));
    message->addOption(opt_duid);

    OptionUint16Ptr opt_elapsed_time(new OptionUint16(Option::V6, D6O_ELAPSED_TIME,
                                                      elapsed_time));
    message->addOption(opt_elapsed_time);

    return (message);
}

Pkt6Ptr
HATest::createQuery6(const std::string& duid_text) const {
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 0x1234));
    DUID duid = DUID::fromText(duid_text);
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, duid.getDuid()));
    query6->addOption(client_id);
    return (query6);
}

void
HATest::setDHCPMultiThreadingConfig(bool enabled, uint32_t thread_pool_size,
                                    uint32_t packet_queue_size) {
    ElementPtr mt_config = Element::createMap();
    mt_config->set("enable-multi-threading", Element::create(enabled));
    mt_config->set("thread-pool-size",
                   Element::create(static_cast<int>(thread_pool_size)));
    mt_config->set("queue-size",
                   Element::create(static_cast<int>(packet_queue_size)));
    CfgMgr::instance().getStagingCfg()->setDHCPMultiThreading(mt_config);
}

std::string
HATest::makeHAMtJson(bool enable_multi_threading, bool http_dedicated_listener,
                     uint32_t http_listener_threads,  uint32_t http_client_threads) {
    std::stringstream ss;
    ss << "\"multi-threading\": {"
       << " \"enable-multi-threading\": "
       << (enable_multi_threading ? "true" : "false") << ","
       << " \"http-dedicated-listener\": "
       << (http_dedicated_listener ? "true" : "false")  << ","
       << " \"http-listener-threads\": " << http_listener_threads  << ","
       << " \"http-client-threads\": " << http_client_threads << "}";
    return (ss.str());
}

} // end of namespace isc::ha::test
} // end of namespace isc::ha
} // end of namespace isc
