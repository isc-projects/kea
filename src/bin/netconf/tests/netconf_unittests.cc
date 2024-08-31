// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <netconf/netconf.h>
#include <netconf/netconf_process.h>
#include <netconf/parser_context.h>
#include <netconf/simple_parser.h>
#include <netconf/unix_control_socket.h>
#include <testutils/log_utils.h>
#include <testutils/sandbox.h>
#include <testutils/threaded_test.h>
#include <yang/tests/sysrepo_setup.h>
#include <yang/testutils/translator_test.h>
#include <yang/translator_config.h>
#include <yang/yang_models.h>
#include <yang/yang_revisions.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include <gtest/gtest.h>

#include <sysrepo-cpp/utils/exception.hpp>

using namespace std;
using namespace isc;
using namespace isc::netconf;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;
using namespace isc::test;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace libyang;
using namespace sysrepo;

using isc::yang::test::SysrepoSetup;

namespace {

/// @brief Test unix socket file name.
const string TEST_SOCKET = "test-socket";

/// @brief Type definition for the pointer to Thread objects.
using ThreadPtr = shared_ptr<thread>;

/// @brief Test version of the NetconfAgent class.
class NakedNetconfAgent : public NetconfAgent {
public:
    /// Export protected methods and fields.
    using NetconfAgent::checkModule;
    using NetconfAgent::checkModules;
    using NetconfAgent::initSysrepo;
    using NetconfAgent::keaConfig;
    using NetconfAgent::modules_;
    using NetconfAgent::running_sess_;
    using NetconfAgent::startup_sess_;
    using NetconfAgent::subscribeToDataChanges;
    using NetconfAgent::subscriptions_;
    using NetconfAgent::yangConfig;
};  // NakedNetconfAgent

/// @brief Type definition for the pointer to NakedNetconfAgent objects.
using NakedNetconfAgentPtr = shared_ptr<NakedNetconfAgent>;

/// @brief Clear YANG configuration.
///
/// @param agent The naked netconf agent (fr its startup datastore session).
void clearYang(NakedNetconfAgentPtr agent) {
    if (agent && (agent->startup_sess_)) {
        string xpath = "/kea-dhcp4-server:config";
        EXPECT_NO_THROW_LOG(agent->startup_sess_->deleteItem(xpath));
        EXPECT_NO_THROW_LOG(agent->startup_sess_->applyChanges());
    }
}

// Empirically the requested subnets have sometimes returned in decreasing
// order of subnet ID. To avoid flaky test failures, sort them before
// comparing.
ElementPtr sortSubnets(ElementPtr const& map) {
    ElementPtr arguments(copy(map->get("arguments"), 0));
    ElementPtr dhcp4(copy(arguments->get("Dhcp4"), 0));
    ElementPtr subnet4(copy(dhcp4->get("subnet4")));

    boost::dynamic_pointer_cast<ListElement>(subnet4)->sort("id");

    ElementPtr result(copy(map));
    result->set("arguments", arguments);
    arguments->set("Dhcp4", dhcp4);
    dhcp4->set("subnet4", subnet4);
    return result;
}

/// @brief Test fixture class for netconf agent.
class NetconfAgentTest : public ThreadedTest {
public:
    isc::test::Sandbox sandbox;

    void SetUp() override {
        SysrepoSetup::cleanSharedMemory();
        removeUnixSocketFile();
        io_service_.reset(new IOService());
        agent_.reset(new NakedNetconfAgent());
    }

    void TearDown() override {
        if (thread_) {
            thread_->join();
            thread_.reset();
        }
        if (agent_) {
            clearYang(agent_);
            agent_->clear();
        }
        agent_.reset();
        requests_.clear();
        responses_.clear();
        removeUnixSocketFile();
        SysrepoSetup::cleanSharedMemory();
        io_service_->stopAndPoll();
    }

    /// @brief Returns socket file path.
    ///
    /// If the KEA_SOCKET_TEST_DIR environment variable is specified, the
    /// socket file is created in the location pointed to by this variable.
    /// Otherwise, it is created in the build directory.
    string unixSocketFilePath() {
        string socket_path;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path = string(env) + "/" + TEST_SOCKET;
        } else {
            socket_path = sandbox.join(TEST_SOCKET);
        }
        return (socket_path);
    }

    /// @brief Removes unix socket descriptor.
    void removeUnixSocketFile() {
        static_cast<void>(remove(unixSocketFilePath().c_str()));
    }

    /// @brief Create configuration of the control socket.
    ///
    /// @return a pointer to a control socket configuration.
    CfgControlSocketPtr createCfgControlSocket() {
        CfgControlSocketPtr cfg;
        cfg.reset(new CfgControlSocket(CfgControlSocket::Type::UNIX,
                                       unixSocketFilePath(),
                                       Url("http://127.0.0.1:8000/")));
        return (cfg);
    }

    /// @brief Fake server (returns OK answer).
    void fakeServer();

    /// @brief IOService object.
    IOServicePtr io_service_;

    /// @brief Test netconf agent.
    NakedNetconfAgentPtr agent_;

    /// @brief Request list.
    vector<string> requests_;

    /// @brief Response list.
    vector<string> responses_;
};  // NetconfAgentTest

/// @brief Special test fixture for logging tests.
class NetconfAgentLogTest : public dhcp::test::LogContentTest {
public:
    /// @brief Constructor.
    NetconfAgentLogTest()
        : finished_(false),
          io_service_(new IOService()),
          thread_(),
          agent_(new NakedNetconfAgent()) {
    }

    /// @brief Destructor.
    virtual ~NetconfAgentLogTest() {
        if (agent_) {
            clearYang(agent_);
            agent_->clear();
        }
        agent_.reset();
        // io_service must be stopped to make the thread to return.
        io_service_->stop();
        if (thread_) {
            thread_->join();
            thread_.reset();
        }
        io_service_.reset();
    }

    /// @brief Default change callback (print changes and return OK).
    sysrepo::ErrorCode callback(Session sess,
                                uint32_t /* subscription_id */,
                                string_view module_name,
                                optional<string_view> /* sub_xpath */,
                                Event /* event */,
                                uint32_t /* request_id */) {
        NetconfAgent::logChanges(sess, module_name);
        finished_ = true;
        return (sysrepo::ErrorCode::Ok);
    }

    /// @brief logChanges is called in another thread so we have to wait for it.
    ///
    /// @todo The better way to get notified and get rid of the sleep is with a
    /// conditional variable.
    void waitForCallback() {
        auto const timeout(2s);
        cout << "Waiting 2s for callback..." << endl;
        auto const start(chrono::steady_clock::now());
        while (!finished_) {
            auto const duration(chrono::steady_clock::now() - start);
            if (timeout < duration) {
                FAIL() << "Timeout of 2s expired while waiting for callback.";
            }
            this_thread::sleep_for(1ms);
        }
    }

    /// @brief To know when the callback was called.
    atomic<bool> finished_;

    /// @brief IOService object.
    IOServicePtr io_service_;

    /// @brief Pointer to server thread.
    ThreadPtr thread_;

    /// @brief Test netconf agent.
    NakedNetconfAgentPtr agent_;
};  // NetconfAgentLogTest

/// @brief Fake server (returns OK answer).
void
NetconfAgentTest::fakeServer() {
    // Acceptor.
    boost::asio::local::stream_protocol::acceptor
        acceptor(io_service_->getInternalIOService());
    EXPECT_NO_THROW_LOG(acceptor.open());
    boost::asio::local::stream_protocol::endpoint
        endpoint(unixSocketFilePath());
    boost::asio::socket_base::reuse_address option(true);
    acceptor.set_option(option);
    EXPECT_NO_THROW_LOG(acceptor.bind(endpoint));
    EXPECT_NO_THROW_LOG(acceptor.listen());
    boost::asio::local::stream_protocol::socket
        socket(io_service_->getInternalIOService());

    // Ready.
    signalReady();

    // Timeout.
    bool timeout = false;
    IntervalTimer timer(io_service_);
    timer.setup([&timeout]() {
            timeout = true;
            FAIL() << "timeout";
        }, 1500, IntervalTimer::ONE_SHOT);

    // Accept.
    boost::system::error_code ec;
    bool accepted = false;
    acceptor.async_accept(socket,
                          [&ec, &accepted]
                          (const boost::system::error_code& error) {
                              ec = error;
                              accepted = true;
                          });
    while (!accepted && !timeout) {
        io_service_->runOne();
    }
    ASSERT_FALSE(ec);

    // Receive command.
    string rbuf(1024, ' ');
    size_t received = 0;
    socket.async_receive(boost::asio::buffer(&rbuf[0], rbuf.size()),
                         [&ec, &received]
                         (const boost::system::error_code& error, size_t cnt) {
                             ec = error;
                             received = cnt;
                         });
    while (!received && !timeout) {
        io_service_->runOne();
    }
    ASSERT_FALSE(ec);
    rbuf.resize(received);
    requests_.push_back(rbuf);
    ElementPtr json;
    EXPECT_NO_THROW_LOG(json = Element::fromJSON(rbuf));
    EXPECT_TRUE(json);
    string command;
    ElementPtr config;
    if (json) {
        ConstElementPtr arg;
        EXPECT_NO_THROW_LOG(command = parseCommand(arg, json));
        if (command == "config-get") {
            config = Element::fromJSON("{ \"comment\": \"empty\" }");
        }
    }

    // Send answer.
    string sbuf = createAnswer(CONTROL_RESULT_SUCCESS, config)->str();
    responses_.push_back(sbuf);
    size_t sent = 0;
    socket.async_send(boost::asio::buffer(&sbuf[0], sbuf.size()),
                      [&ec, &sent]
                      (const boost::system::error_code& error, size_t cnt) {
                          ec = error;
                          sent = cnt;
                      });
    while (!sent && !timeout) {
        io_service_->runOne();
    }
    ASSERT_FALSE(ec);

    // Stop timer.
    timer.cancel();

    // Close socket and acceptor.
    if (socket.is_open()) {
        EXPECT_NO_THROW_LOG(socket.close());
    }
    EXPECT_NO_THROW_LOG(acceptor.close());
    // Removed the socket file so it can be called again immediately.
    removeUnixSocketFile();

    /// Finished.
    EXPECT_FALSE(timeout);
    EXPECT_TRUE(accepted);
    EXPECT_TRUE(received);
    EXPECT_TRUE(sent);
    EXPECT_EQ(sent, sbuf.size());

    // signalStopped can't be called here because of the 2 runs for update.
}

// Verifies that the initSysrepo method opens sysrepo connection and sessions.
TEST_F(NetconfAgentTest, initSysrepo) {
    EXPECT_NO_THROW_LOG(agent_->initSysrepo());
    EXPECT_TRUE(agent_->startup_sess_);
    EXPECT_TRUE(agent_->running_sess_);
    EXPECT_EQ(0, agent_->subscriptions_.size());
    EXPECT_LE(16, agent_->modules_.size());
}

// Verifies that the checkModule method emits expected errors.
TEST_F(NetconfAgentLogTest, checkModule) {
    // Various modules should be available.
    EXPECT_EQ(1, YANG_REVISIONS.count("keatest-module"));
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp4-server"));
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp6-server"));

    // Non-existing modules should not.
    EXPECT_EQ(0, agent_->modules_.count("does-not-exist"));

    // kea-dhcp[46]-server should be available.
    EXPECT_NO_THROW_LOG(agent_->initSysrepo());
    EXPECT_EQ(1, agent_->modules_.count("kea-dhcp4-server"));
    EXPECT_EQ(1, agent_->modules_.count("kea-dhcp6-server"));
    EXPECT_TRUE(agent_->checkModule("kea-dhcp4-server"));
    EXPECT_TRUE(agent_->checkModule("kea-dhcp6-server"));

    // Unknown module should emit a missing error.
    EXPECT_EQ(0, agent_->modules_.count("does-not-exist"));
    EXPECT_FALSE(agent_->checkModule("does-not-exist"));
    addString("NETCONF_MODULE_MISSING_ERR Missing essential module "
              "does-not-exist in sysrepo");

    // Patch the found revision to get a revision error.
    const string& module = "kea-dhcp4-server";
    auto it4 = agent_->modules_.find(module);
    if (it4 != agent_->modules_.end()) {
        agent_->modules_.erase(it4);
    }
    // The module was written far after 20180714...
    const string& bad_revision = "2018-07-14";
    agent_->modules_.insert(make_pair(module, bad_revision));
    EXPECT_FALSE(agent_->checkModule(module));
    ostringstream msg;
    msg << "NETCONF_MODULE_REVISION_ERR Essential module " << module
        << " does NOT have the right revision: expected "
        << YANG_REVISIONS.at(module) << ", got " << bad_revision;
    addString(msg.str());

    EXPECT_TRUE(checkFile());
}

// Verifies that the checkModules method emits expected warnings.
TEST_F(NetconfAgentLogTest, checkModules) {
    // kea-dhcp[46]-server must be in YANG_REVISIONS.
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp4-server"));
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp6-server"));

    // kea-dhcp[46]-server should be available.
    EXPECT_NO_THROW_LOG(agent_->initSysrepo());
    EXPECT_EQ(1, agent_->modules_.count("kea-dhcp4-server"));
    EXPECT_EQ(1, agent_->modules_.count("kea-dhcp6-server"));

    // Run checkModules but it will be indirectly checked as
    // emitting nothing.
    ASSERT_NO_THROW_LOG(agent_->checkModules());

    // Remove kea-dhcp6-server.
    const string& module = "kea-dhcp6-server";
    auto it6 = agent_->modules_.find(module);
    if (it6 != agent_->modules_.end()) {
        agent_->modules_.erase(it6);
    }
    ASSERT_NO_THROW_LOG(agent_->checkModules());
    ostringstream mmsg;
    mmsg << "NETCONF_MODULE_MISSING_WARN Missing module " << module
         << " in sysrepo";
    addString(mmsg.str());

    // Add it back with a bad revision.
    const string& bad_revision = "2018-07-14";
    agent_->modules_.insert(make_pair(module, bad_revision));
    ASSERT_NO_THROW_LOG(agent_->checkModules());
    ostringstream rmsg;
    rmsg << "NETCONF_MODULE_REVISION_WARN Module " << module
         << " does NOT have the right revision: expected "
         << YANG_REVISIONS.at(module) << ", got " << bad_revision;
    addString(rmsg.str());

    EXPECT_TRUE(checkFile());
}

// Verifies that the logChanges method handles correctly changes.
TEST_F(NetconfAgentLogTest, logChanges) {
    // Initial YANG configuration.
    const YRTree tree0 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    // Load initial YANG configuration.
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW_LOG(repr.set(tree0, *agent_->startup_sess_));

    // Subscribe configuration changes.
    auto cb = [=, this](Session session, uint32_t subscription_id, string_view module_name,
                        optional<string_view> sub_xpath, Event event, uint32_t request_id) {
        return callback(session, subscription_id, module_name, sub_xpath, event, request_id);
    };
    SubscribeOptions const options(SubscribeOptions::Default | SubscribeOptions::DoneOnly);
    optional<Subscription> subscription;
    EXPECT_NO_THROW_LOG(subscription = agent_->running_sess_->onModuleChange(KEA_DHCP4_SERVER, cb,
                                                                             nullopt, 0,
                                                                             options));
    thread_.reset(new thread([this]() { io_service_->run(); }));

    // Change configuration (subnet #1 moved from 10.0.0.0/24 to 10.0.1/0/24).
    const YRTree tree1 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.1.0/24", LeafBaseType::String, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    EXPECT_NO_THROW_LOG(repr.set(tree1, *agent_->running_sess_));

    // Check that the debug output was correct.
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: created: "
              "/kea-dhcp4-server:config/subnet4[id='2'] (list)");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "created: /kea-dhcp4-server:config/subnet4[id='2']/id = 2");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: created: "
              "/kea-dhcp4-server:config/subnet4[id='2']/subnet = 10.0.2.0/24");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: created: "
              "/kea-dhcp4-server:config/subnet4[id='2']/relay (container)");

    waitForCallback();

    EXPECT_TRUE(checkFile());
}

// Verifies that the logChanges method handles correctly changes.
// Instead of the simple modified of the previous test, now there will
// deleted, created and moved.
TEST_F(NetconfAgentLogTest, logChanges2) {
    // Initial YANG configuration.
    const YRTree tree0 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    // Load initial YANG configuration.
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW_LOG(repr.set(tree0, *agent_->startup_sess_));

    // Subscribe configuration changes.
    auto cb = [=, this](Session session, uint32_t subscription_id, string_view module_name,
                        optional<string_view> sub_xpath, Event event, uint32_t request_id) {
        return callback(session, subscription_id, module_name, sub_xpath, event, request_id);
    };
    SubscribeOptions const options(SubscribeOptions::Default | SubscribeOptions::DoneOnly);
    optional<Subscription> subscription;
    EXPECT_NO_THROW_LOG(subscription = agent_->running_sess_->onModuleChange(KEA_DHCP4_SERVER, cb,
                                                                             nullopt, 0,
                                                                             options));
    thread_.reset(new thread([this]() { io_service_->run(); }));

    // Change configuration (subnet #1 moved to #10).
    string xpath = "/kea-dhcp4-server:config/subnet4[id='1']";
    EXPECT_NO_THROW_LOG(agent_->running_sess_->deleteItem(xpath));
    const YRTree tree1 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='10']/id",
          "10", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='10']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    EXPECT_NO_THROW_LOG(repr.set(tree1, *agent_->running_sess_));

    // Check that the debug output was correct.
    addString(
        "NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: deleted: "
        "/kea-dhcp4-server:config/subnet4[id='1'] (list)");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "deleted: /kea-dhcp4-server:config/subnet4[id='1']/id = 1");
    addString(
        "NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: deleted: "
        "/kea-dhcp4-server:config/subnet4[id='1']/subnet = 10.0.1.0/24");
    addString(
        "NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: deleted: "
        "/kea-dhcp4-server:config/subnet4[id='1']/relay (container)");

    waitForCallback();

    EXPECT_TRUE(checkFile());
}

// Verifies that the keaConfig method works as expected.
TEST_F(NetconfAgentTest, keaConfig) {
    // Netconf configuration.
    string config_prefix = "{\n"
        "  \"Netconf\": {\n"
        "    \"managed-servers\": {\n"
        "      \"dhcp4\": {\n"
        "        \"control-socket\": {\n"
        "          \"socket-type\": \"unix\",\n"
        "          \"socket-name\": \"";
    string config_trailer = "\"\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";
    string config = config_prefix + unixSocketFilePath() + config_trailer;
    NetconfConfigPtr ctx(new NetconfConfig());
    ElementPtr json;
    ParserContext parser_context;
    EXPECT_NO_THROW_LOG(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = copy(netconf_json, 0);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW_LOG(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Launch server.
    thread_.reset(new thread([this]() { fakeServer(); signalStopped(); }));

    // Wait until the server is listening.
    waitReady();

    // Try keaConfig.
    EXPECT_NO_THROW_LOG(agent_->keaConfig(service_pair));

    // Wait server to be stopped.
    waitStopped();

    // Check request.
    ASSERT_EQ(1, requests_.size());
    const string& request_str = requests_[0];
    ElementPtr request;
    ASSERT_NO_THROW_LOG(request = Element::fromJSON(request_str));
    string expected_str = "{\n"
        "\"command\": \"config-get\"\n"
        "}";
    ElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*request));
    // Alternative showing more for debugging...
    // EXPECT_EQ(prettyPrint(expected), prettyPrint(request));

    // Check response.
    ASSERT_EQ(1, responses_.size());
    const string& response_str = responses_[0];
    ElementPtr response;
    ASSERT_NO_THROW_LOG(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0,\n"
        "\"arguments\": {\n"
        "    \"comment\": \"empty\"\n"
        "    }\n"
        "}";
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

// Verifies that the yangConfig method works as expected: apply YANG config
// to the server.
TEST_F(NetconfAgentTest, yangConfig) {
    // YANG configuration.
    const YRTree tree = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    // Load YANG configuration.
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW_LOG(repr.set(tree, *agent_->startup_sess_));

    // Netconf configuration.
    string config_prefix = "{\n"
        "  \"Netconf\": {\n"
        "    \"managed-servers\": {\n"
        "      \"dhcp4\": {\n"
        "        \"control-socket\": {\n"
        "          \"socket-type\": \"unix\",\n"
        "          \"socket-name\": \"";
    string config_trailer = "\"\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";
    string config = config_prefix + unixSocketFilePath() + config_trailer;
    NetconfConfigPtr ctx(new NetconfConfig());
    ElementPtr json;
    ParserContext parser_context;
    EXPECT_NO_THROW_LOG(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = copy(netconf_json, 0);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW_LOG(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Launch server.
    thread_.reset(new thread([this]() { fakeServer(); signalStopped();}));

    // Wait until the server is listening.
    waitReady();

    // Try yangConfig.
    EXPECT_NO_THROW_LOG(agent_->yangConfig(service_pair));

    // Wait server to be stopped.
    waitStopped();

    // Check request.
    ASSERT_EQ(1, requests_.size());
    const string& request_str = requests_[0];
    ElementPtr request;
    ASSERT_NO_THROW_LOG(request = Element::fromJSON(request_str));
    string expected_str = "{\n"
        "\"command\": \"config-set\",\n"
        "\"arguments\": {\n"
        "    \"Dhcp4\": {\n"
        "        \"subnet4\": [\n"
        "            {\n"
        "                \"id\": 1,\n"
        "                \"subnet\": \"10.0.0.0/24\"\n"
        "            },\n"
        "            {\n"
        "                \"id\": 2,\n"
        "                \"subnet\": \"10.0.2.0/24\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "  }\n"
        "}";
    ElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));

    expected = sortSubnets(expected);
    request = sortSubnets(request);
    EXPECT_EQ(prettyPrint(expected), prettyPrint(request));

    // Check response.
    ASSERT_EQ(1, responses_.size());
    const string& response_str = responses_[0];
    ElementPtr response;
    ASSERT_NO_THROW_LOG(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

// Verifies that the subscribeToDataChanges method works as expected.
TEST_F(NetconfAgentTest, subscribeToDataChanges) {
    // Netconf configuration.
    string config_prefix = "{\n"
        "  \"Netconf\": {\n"
        "    \"managed-servers\": {\n"
        "      \"dhcp4\": {\n"
        "        \"control-socket\": {\n"
        "          \"socket-type\": \"unix\",\n"
        "          \"socket-name\": \"";
    string config_trailer = "\"\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";
    string config = config_prefix + unixSocketFilePath() + config_trailer;
    NetconfConfigPtr ctx(new NetconfConfig());
    ElementPtr json;
    ParserContext parser_context;
    EXPECT_NO_THROW_LOG(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = copy(netconf_json, 0);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW_LOG(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Try subscribeToDataChanges.
    EXPECT_EQ(0, agent_->subscriptions_.size());
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    EXPECT_EQ(0, agent_->subscriptions_.size());
    EXPECT_NO_THROW_LOG(agent_->subscribeToDataChanges(service_pair));
    EXPECT_EQ(1, agent_->subscriptions_.size());

    /// Unsubscribe.
    EXPECT_NO_THROW_LOG(agent_->subscriptions_.clear());
}

// Verifies that the update method works as expected: apply new YANG configuration
// to the server. Note it is called by the subscription callback.
TEST_F(NetconfAgentTest, update) {
    // Initial YANG configuration.
    const YRTree tree0 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    // Load initial YANG configuration.
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW_LOG(repr.set(tree0, *agent_->startup_sess_));

    // Netconf configuration.
    // Set validate-changes to false to avoid validate() to be called.
    string config_prefix = "{\n"
        "  \"Netconf\": {\n"
        "    \"validate-changes\": false,\n"
        "    \"managed-servers\": {\n"
        "      \"dhcp4\": {\n"
        "        \"control-socket\": {\n"
        "          \"socket-type\": \"unix\",\n"
        "          \"socket-name\": \"";
    string config_trailer = "\"\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";
    string config = config_prefix + unixSocketFilePath() + config_trailer;
    NetconfConfigPtr ctx(new NetconfConfig());
    ElementPtr json;
    ParserContext parser_context;
    EXPECT_NO_THROW_LOG(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = copy(netconf_json, 0);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW_LOG(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Subscribe to YANG changes.
    EXPECT_EQ(0, agent_->subscriptions_.size());
    EXPECT_NO_THROW_LOG(agent_->subscribeToDataChanges(service_pair));
    EXPECT_EQ(1, agent_->subscriptions_.size());

    // Launch server.
    thread_.reset(new thread([this]() { fakeServer(); signalStopped(); }));

    // Wait until the server is listening.
    waitReady();

    // Change configuration (subnet #1 moved from 10.0.0.0/24 to 10.0.1/0/24).
    const YRTree tree1 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.1.0/24", LeafBaseType::String, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    EXPECT_NO_THROW_LOG(repr.set(tree1, *agent_->running_sess_));

    // Wait server to be stopped.
    waitStopped();

    // Check request.
    ASSERT_EQ(1, requests_.size());
    const string& request_str = requests_[0];
    ElementPtr request;
    ASSERT_NO_THROW_LOG(request = Element::fromJSON(request_str));
    string expected_str = "{\n"
        "\"command\": \"config-set\",\n"
        "\"arguments\": {\n"
        "    \"Dhcp4\": {\n"
        "        \"subnet4\": [\n"
        "            {\n"
        "                \"id\": 1,\n"
        "                \"subnet\": \"10.0.1.0/24\"\n"
        "            },\n"
        "            {\n"
        "                \"id\": 2,\n"
        "                \"subnet\": \"10.0.2.0/24\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "  }\n"
        "}";
    ElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));

    expected = sortSubnets(expected);
    request = sortSubnets(request);
    EXPECT_EQ(prettyPrint(expected), prettyPrint(request));

    // Check response.
    ASSERT_EQ(1, responses_.size());
    const string& response_str = responses_[0];
    ElementPtr response;
    ASSERT_NO_THROW_LOG(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

// Verifies that the validate method works as expected: test new YANG configuration
// with the server. Note it is called by the subscription callback and
// update is called after.
TEST_F(NetconfAgentTest, validate) {
    // Initial YANG configuration.
    const YRTree tree0 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    // Load initial YANG configuration.
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW_LOG(repr.set(tree0, *agent_->startup_sess_));

    // Netconf configuration.
    string config_prefix = "{\n"
        "  \"Netconf\": {\n"
        "    \"managed-servers\": {\n"
        "      \"dhcp4\": {\n"
        "        \"control-socket\": {\n"
        "          \"socket-type\": \"unix\",\n"
        "          \"socket-name\": \"";
    string config_trailer = "\"\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";
    string config = config_prefix + unixSocketFilePath() + config_trailer;
    NetconfConfigPtr ctx(new NetconfConfig());
    ElementPtr json;
    ParserContext parser_context;
    EXPECT_NO_THROW_LOG(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = copy(netconf_json, 0);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW_LOG(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Subscribe to YANG changes.
    EXPECT_EQ(0, agent_->subscriptions_.size());
    EXPECT_NO_THROW_LOG(agent_->subscribeToDataChanges(service_pair));
    EXPECT_EQ(1, agent_->subscriptions_.size());

    // Launch server twice.
    thread_.reset(new thread([this]() {
        fakeServer();
        fakeServer();
        signalStopped();
    }));

    // Wait until the server is listening.
    waitReady();

    // Change configuration (subnet #1 moved from 10.0.0.0/24 to 10.0.1/0/24).
    const YRTree tree1 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.1.0/24", LeafBaseType::String, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", LeafBaseType::String, true }
    });
    EXPECT_NO_THROW_LOG(repr.set(tree1, *agent_->running_sess_));

    // Wait servers to be stopped.
    waitStopped();

    // Check that the fake server received the first request.
    ASSERT_LE(1, requests_.size());
    string request_str = requests_[0];
    ElementPtr request;
    ASSERT_NO_THROW_LOG(request = Element::fromJSON(request_str));
    string expected_str = "{\n"
        "\"command\": \"config-test\",\n"
        "\"arguments\": {\n"
        "    \"Dhcp4\": {\n"
        "        \"subnet4\": [\n"
        "            {\n"
        "                \"id\": 1,\n"
        "                \"subnet\": \"10.0.1.0/24\"\n"
        "            },\n"
        "            {\n"
        "                \"id\": 2,\n"
        "                \"subnet\": \"10.0.2.0/24\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "  }\n"
        "}";
    ElementPtr expected;
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));

    expected = sortSubnets(expected);
    request = sortSubnets(request);
    EXPECT_EQ(prettyPrint(expected), prettyPrint(request));

    // Check that the fake server received the second request.
    ASSERT_EQ(2, requests_.size());
    request_str = requests_[1];
    ASSERT_NO_THROW_LOG(request = Element::fromJSON(request_str));
    expected_str = "{\n"
        "\"command\": \"config-set\",\n"
        "\"arguments\": {\n"
        "    \"Dhcp4\": {\n"
        "        \"subnet4\": [\n"
        "            {\n"
        "                \"id\": 1,\n"
        "                \"subnet\": \"10.0.1.0/24\"\n"
        "            },\n"
        "            {\n"
        "                \"id\": 2,\n"
        "                \"subnet\": \"10.0.2.0/24\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "  }\n"
        "}";
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));

    expected = sortSubnets(expected);
    request = sortSubnets(request);
    EXPECT_EQ(prettyPrint(expected), prettyPrint(request));

    // Check responses.
    ASSERT_EQ(2, responses_.size());
    string response_str = responses_[0];
    ElementPtr response;
    ASSERT_NO_THROW_LOG(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));

    response_str = responses_[1];
    ASSERT_NO_THROW_LOG(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW_LOG(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

// Verifies what happens when the validate method returns an error.
TEST_F(NetconfAgentTest, noValidate) {
    // Initial YANG configuration.
    const YRTree tree0 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true }
    });
    // Load initial YANG configuration.
    ASSERT_NO_THROW_LOG(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW_LOG(repr.set(tree0, *agent_->startup_sess_));

    // Netconf configuration.
    string config_prefix = "{\n"
        "  \"Netconf\": {\n"
        "    \"managed-servers\": {\n"
        "      \"dhcp4\": {\n"
        "        \"control-socket\": {\n"
        "          \"socket-type\": \"unix\",\n"
        "          \"socket-name\": \"";
    string config_trailer = "\"\n"
        "        }\n"
        "      }\n"
        "    }\n"
        "  }\n"
        "}";
    string config = config_prefix + unixSocketFilePath() + config_trailer;
    NetconfConfigPtr ctx(new NetconfConfig());
    ElementPtr json;
    ParserContext parser_context;
    EXPECT_NO_THROW_LOG(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = copy(netconf_json, 0);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW_LOG(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Subscribe to YANG changes.
    EXPECT_EQ(0, agent_->subscriptions_.size());
    EXPECT_NO_THROW_LOG(agent_->subscribeToDataChanges(service_pair));
    EXPECT_EQ(1, agent_->subscriptions_.size());

    // Change configuration (add invalid user context).
    const YRTree tree1 = YangRepr::buildTreeFromVector({
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", LeafBaseType::Uint32, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", LeafBaseType::String, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/user-context",
          "BOGUS", LeafBaseType::String, true }
    });
    EXPECT_THROW_MSG(repr.set(tree1, *agent_->running_sess_), sysrepo::Error,
                     "Session::applyChanges: Couldn't apply changes: SR_ERR_CALLBACK_FAILED");
}

}  // namespace
