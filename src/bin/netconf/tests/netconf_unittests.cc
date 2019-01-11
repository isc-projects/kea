// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <netconf/netconf.h>
#include <netconf/netconf_process.h>
#include <netconf/parser_context.h>
#include <netconf/simple_parser.h>
#include <netconf/unix_control_socket.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <util/threads/thread.h>
#include <yang/yang_models.h>
#include <yang/yang_revisions.h>
#include <yang/translator_config.h>
#include <yang/testutils/translator_test.h>
#include <testutils/log_utils.h>
#include <testutils/threaded_test.h>
#include <gtest/gtest.h>
#include <sstream>

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
using namespace isc::util::thread;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

namespace {

/// @brief Test unix socket file name.
const string TEST_SOCKET = "test-socket";

/// @brief Type definition for the pointer to Thread objects.
typedef boost::shared_ptr<Thread> ThreadPtr;

/// @brief Test version of the NetconfAgent class.
class NakedNetconfAgent : public NetconfAgent {
public:
    /// @brief Constructor.
    NakedNetconfAgent() {
    }

    /// @brief Destructor.
    virtual ~NakedNetconfAgent() {
    }

    /// Export protected methods and fields.
    using NetconfAgent::keaConfig;
    using NetconfAgent::initSysrepo;
    using NetconfAgent::checkModule;
    using NetconfAgent::checkModules;
    using NetconfAgent::yangConfig;
    using NetconfAgent::subscribeConfig;
    using NetconfAgent::conn_;
    using NetconfAgent::startup_sess_;
    using NetconfAgent::running_sess_;
    using NetconfAgent::modules_;
    using NetconfAgent::subscriptions_;
};

/// @brief Type definition for the pointer to NakedNetconfAgent objects.
typedef boost::shared_ptr<NakedNetconfAgent> NakedNetconfAgentPtr;

/// @brief Clear YANG configuration.
///
/// @param agent The naked netconf agent (fr its startup datastore session).
void clearYang(NakedNetconfAgentPtr agent) {
    if (agent && (agent->startup_sess_)) {
        string xpath = "/kea-dhcp4-server:config";
        EXPECT_NO_THROW(agent->startup_sess_->delete_item(xpath.c_str()));
        EXPECT_NO_THROW(agent->startup_sess_->commit());
    }
}

/// @brief Test fixture class for netconf agent.
class NetconfAgentTest : public ThreadedTest {
public:
    /// @brief Constructor.
    NetconfAgentTest()
        : ThreadedTest(),
          io_service_(new IOService()),
          agent_(new NakedNetconfAgent),
          requests_(),
          responses_() {
        NetconfProcess::shut_down = false;
        removeUnixSocketFile();
    }

    /// @brief Destructor.
    virtual ~NetconfAgentTest() {
        NetconfProcess::shut_down = true;
        if (thread_) {
            thread_->wait();
            thread_.reset();
        }
        // io_service must be stopped after the thread returns,
        // otherwise the thread may never return if it is
        // waiting for the completion of some asynchronous tasks.
        io_service_->stop();
        io_service_.reset();
        if (agent_) {
            clearYang(agent_);
            agent_->clear();
        }
        agent_.reset();
        requests_.clear();
        responses_.clear();
        removeUnixSocketFile();
    }

    /// @brief Returns socket file path.
    ///
    /// If the KEA_SOCKET_TEST_DIR environment variable is specified, the
    /// socket file is created in the location pointed to by this variable.
    /// Otherwise, it is created in the build directory.
    static string unixSocketFilePath() {
        ostringstream s;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            s << string(env);
        } else {
            s << TEST_DATA_BUILDDIR;
        }

        s << "/" << TEST_SOCKET;
        return (s.str());
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
};

/// @brief Special test fixture for logging tests.
class NetconfAgentLogTest : public dhcp::test::LogContentTest {
public:
    /// @brief Constructor.
    NetconfAgentLogTest()
        : io_service_(new IOService()),
          thread_(),
          agent_(new NakedNetconfAgent) {
        NetconfProcess::shut_down = false;
    }

    /// @brief Destructor.
    virtual ~NetconfAgentLogTest() {
        NetconfProcess::shut_down = true;
        // io_service must be stopped to make the thread to return.
        io_service_->stop();
        io_service_.reset();
        if (thread_) {
            thread_->wait();
            thread_.reset();
        }
        if (agent_) {
            clearYang(agent_);
            agent_->clear();
        }
        agent_.reset();
    }

    /// @brief IOService object.
    IOServicePtr io_service_;

    /// @brief Pointer to server thread.
    ThreadPtr thread_;

    /// @brief Test netconf agent.
    NakedNetconfAgentPtr agent_;
};

/// @brief Fake server (returns OK answer).
void
NetconfAgentTest::fakeServer() {
    // Acceptor.
    boost::asio::local::stream_protocol::acceptor
        acceptor(io_service_->get_io_service());
    EXPECT_NO_THROW(acceptor.open());
    boost::asio::local::stream_protocol::endpoint
        endpoint(unixSocketFilePath());
    boost::asio::socket_base::reuse_address option(true);
    acceptor.set_option(option);
    EXPECT_NO_THROW(acceptor.bind(endpoint));
    EXPECT_NO_THROW(acceptor.listen());
    boost::asio::local::stream_protocol::socket
        socket(io_service_->get_io_service());

    // Ready.
    signalReady();

    // Timeout.
    bool timeout = false;
    IntervalTimer timer(*io_service_);
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
        io_service_->run_one();
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
        io_service_->run_one();
    }
    ASSERT_FALSE(ec);
    rbuf.resize(received);
    requests_.push_back(rbuf);
    ConstElementPtr json;
    EXPECT_NO_THROW(json = Element::fromJSON(rbuf));
    EXPECT_TRUE(json);
    string command;
    ConstElementPtr config;
    if (json) {
        ConstElementPtr arg;
        EXPECT_NO_THROW(command = parseCommand(arg, json));
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
        io_service_->run_one();
    }
    ASSERT_FALSE(ec);

    // Stop timer.
    timer.cancel();

    // Close socket and acceptor.
    if (socket.is_open()) {
        EXPECT_NO_THROW(socket.close());
    }
    EXPECT_NO_THROW(acceptor.close());
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

/// Verifies the initSysrepo method opens sysrepo connection and sessions.
TEST_F(NetconfAgentTest, initSysrepo) {
    EXPECT_NO_THROW(agent_->initSysrepo());
    EXPECT_TRUE(agent_->conn_);
    EXPECT_TRUE(agent_->startup_sess_);
    EXPECT_TRUE(agent_->running_sess_);
    EXPECT_EQ(1, agent_->subscriptions_.size());
    EXPECT_LE(16, agent_->modules_.size());
    // No way to check the module_install callback (BTW is there
    // an API to install modules? If none only system tests can
    // do something)...
}

/// Verifies the checkModule method emits expected errors.
TEST_F(NetconfAgentLogTest, checkModule) {
    // keatest-module should not be in YANG_REVISIONS.
    EXPECT_EQ(0, YANG_REVISIONS.count("keatest-module"));
    // But kea-dhcp[46]-server must be in.
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp4-server"));
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp6-server"));

    // kea-dhcp[46]-server should be available.
    EXPECT_NO_THROW(agent_->initSysrepo());
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
        << " does have the right revision: expected "
        << YANG_REVISIONS.at(module) << ", got " << bad_revision;
    addString(msg.str());

    // Enable this for debugging.
    // logCheckVerbose(true);
    EXPECT_TRUE(checkFile());
}

/// Verifies the checkModules method emits expected warnings.
TEST_F(NetconfAgentLogTest, checkModules) {
    // kea-dhcp[46]-server must be in YANG_REVISIONS.
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp4-server"));
    ASSERT_EQ(1, YANG_REVISIONS.count("kea-dhcp6-server"));

    // kea-dhcp[46]-server should be available.
    EXPECT_NO_THROW(agent_->initSysrepo());
    EXPECT_EQ(1, agent_->modules_.count("kea-dhcp4-server"));
    EXPECT_EQ(1, agent_->modules_.count("kea-dhcp6-server"));

    // Run checkModules but it will be indirectly check as
    // emitting nothing.
    ASSERT_NO_THROW(agent_->checkModules());

    // Remove kea-dhcp6-server.
    const string& module = "kea-dhcp6-server";
    auto it6 = agent_->modules_.find(module);
    if (it6 != agent_->modules_.end()) {
        agent_->modules_.erase(it6);
    }
    ASSERT_NO_THROW(agent_->checkModules());
    ostringstream mmsg;
    mmsg << "NETCONF_MODULE_MISSING_WARN Missing module " << module
         << " in sysrepo";
    addString(mmsg.str());

    // Add it back with a bad revision.
    const string& bad_revision = "2018-07-14";
    agent_->modules_.insert(make_pair(module, bad_revision));
    ASSERT_NO_THROW(agent_->checkModules());
    ostringstream rmsg;
    rmsg << "NETCONF_MODULE_REVISION_WARN Module " << module
         << " does have the right revision: expected "
         << YANG_REVISIONS.at(module) << ", got " << bad_revision;
    addString(rmsg.str());

    // Enable this for debugging.
    // logCheckVerbose(true);
    EXPECT_TRUE(checkFile());
}

/// @brief Default change callback (print changes and return OK).
class TestCallback : public Callback {
public:
    int module_change(S_Session sess,
                      const char* /*module_name*/,
                      sr_notif_event_t /*event*/,
                      void* /*private_ctx*/) {
        NetconfAgent::logChanges(sess, "/kea-dhcp4-server:config");
        finished = true;
        return (SR_ERR_OK);
    }

    // To know when the callback was called.
    static bool finished;
};

bool TestCallback::finished = false;

/// Verifies the logChanges method handles correctly changes.
TEST_F(NetconfAgentLogTest, logChanges) {
    // Initial YANG configuration.
    const YRTree tree0 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    // Load initial YANG configuration.
    ASSERT_NO_THROW(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW(repr.set(tree0, agent_->startup_sess_));
    EXPECT_NO_THROW(agent_->startup_sess_->commit());

    // Subscribe configuration changes.
    S_Subscribe subs(new Subscribe(agent_->running_sess_));
    S_Callback cb(new TestCallback());
    TestCallback::finished = false;
    EXPECT_NO_THROW(subs->module_change_subscribe(KEA_DHCP4_SERVER.c_str(),
                                                  cb, 0, 0,
                                                  SR_SUBSCR_APPLY_ONLY));
    thread_.reset(new Thread([this]() { io_service_->run(); }));

    // Change configuration (subnet #1 moved from 10.0.0.0/24 to 10.0.1/0/24).
    const YRTree tree1 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.1.0/24", SR_STRING_T, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    EXPECT_NO_THROW(repr.set(tree1, agent_->running_sess_));
    EXPECT_NO_THROW(agent_->running_sess_->commit());

    // Check that the debug output was correct.
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "modified: "
              "/kea-dhcp4-server:config/subnet4[id='1']/subnet = "
              "10.0.0.0/24 => "
              "/kea-dhcp4-server:config/subnet4[id='1']/subnet = "
              "10.0.1.0/24");

    // logChanges is called in another thread so we can have to wait for it.
    while (!TestCallback::finished) {
        usleep(1000);
    }
    // Enable this for debugging.
    // logCheckVerbose(true);
    EXPECT_TRUE(checkFile());
}

/// Verifies the logChanges method handles correctly changes.
/// Instead of the simple modified of the previous etst, now there will
/// deleted, created and moved.
TEST_F(NetconfAgentLogTest, logChanges2) {
    // Initial YANG configuration.
    const YRTree tree0 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    // Load initial YANG configuration.
    ASSERT_NO_THROW(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW(repr.set(tree0, agent_->startup_sess_));
    EXPECT_NO_THROW(agent_->startup_sess_->commit());

    // Subscribe configuration changes.
    S_Subscribe subs(new Subscribe(agent_->running_sess_));
    S_Callback cb(new TestCallback());
    TestCallback::finished = false;
    EXPECT_NO_THROW(subs->module_change_subscribe(KEA_DHCP4_SERVER.c_str(),
                                                  cb, 0, 0,
                                                  SR_SUBSCR_APPLY_ONLY));
    thread_.reset(new Thread([this]() { io_service_->run(); }));

    // Change configuration (subnet #1 moved to #10).
    string xpath = "/kea-dhcp4-server:config/subnet4[id='1']";
    EXPECT_NO_THROW(agent_->running_sess_->delete_item(xpath.c_str()));
    const YRTree tree1 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='10']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='10']/id",
          "10", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='10']/subnet",
          "10.0.0.0/24", SR_STRING_T, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    EXPECT_NO_THROW(repr.set(tree1, agent_->running_sess_));
    EXPECT_NO_THROW(agent_->running_sess_->commit());

    // Check that the debug output was correct.
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "deleted: "
              "/kea-dhcp4-server:config/subnet4[id='1']/id = 1");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "deleted: "
              "/kea-dhcp4-server:config/subnet4[id='1']/subnet = "
              "10.0.0.0/24");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "deleted: "
              "/kea-dhcp4-server:config/subnet4[id='1'] "
              "(list instance)");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "created: "
              "/kea-dhcp4-server:config/subnet4[id='10'] "
              "(list instance)");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "created: "
              "/kea-dhcp4-server:config/subnet4[id='10']/id = 10");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "created: "
              "/kea-dhcp4-server:config/subnet4[id='10']/subnet = "
              "10.0.0.0/24");
    addString("NETCONF_CONFIG_CHANGED_DETAIL YANG configuration changed: "
              "moved: "
              "/kea-dhcp4-server:config/subnet4[id='10'] "
              "after /kea-dhcp4-server:config/subnet4[id='2']");

    // logChanges is called in another thread so we can have to wait for it.
    while (!TestCallback::finished) {
        usleep(1000);
    }
    // Enable this for debugging.
    // logCheckVerbose(true);
    EXPECT_TRUE(checkFile());
}

/// Verifies the keaConfig method works as expected.
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
    EXPECT_NO_THROW(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = boost::const_pointer_cast<Element>(netconf_json);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Launch server.
    thread_.reset(new Thread([this]() { fakeServer(); signalStopped(); }));

    // Wait until the server is listening.
    waitReady();

    // Try keaConfig.
    EXPECT_NO_THROW(agent_->keaConfig(service_pair));

    // Wait server to be stopped.
    waitStopped();

    // Check request.
    ASSERT_EQ(1, requests_.size());
    const string& request_str = requests_[0];
    ConstElementPtr request;
    ASSERT_NO_THROW(request = Element::fromJSON(request_str));
    string expected_str = "{\n"
        "\"command\": \"config-get\"\n"
        "}";
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*request));
    // Alternative showing more for debugging...
    // EXPECT_EQ(prettyPrint(expected), prettyPrint(request));

    // Check response.
    ASSERT_EQ(1, responses_.size());
    const string& response_str = responses_[0];
    ConstElementPtr response;
    ASSERT_NO_THROW(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0,\n"
        "\"arguments\": {\n"
        "    \"comment\": \"empty\"\n"
        "    }\n"
        "}";
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

/// Verifies the yangConfig method works as expected: apply YANG config
/// to the server.
TEST_F(NetconfAgentTest, yangConfig) {
    // YANG configuration.
    const YRTree tree = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    // Load YANG configuration.
    ASSERT_NO_THROW(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW(repr.set(tree, agent_->startup_sess_));
    EXPECT_NO_THROW(agent_->startup_sess_->commit());

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
    EXPECT_NO_THROW(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = boost::const_pointer_cast<Element>(netconf_json);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Launch server.
    thread_.reset(new Thread([this]() { fakeServer(); signalStopped();}));

    // Wait until the server is listening.
    waitReady();

    // Try yangConfig.
    EXPECT_NO_THROW(agent_->yangConfig(service_pair));

    // Wait server to be stopped.
    waitStopped();

    // Check request.
    ASSERT_EQ(1, requests_.size());
    const string& request_str = requests_[0];
    ConstElementPtr request;
    ASSERT_NO_THROW(request = Element::fromJSON(request_str));
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
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*request));

    // Check response.
    ASSERT_EQ(1, responses_.size());
    const string& response_str = responses_[0];
    ConstElementPtr response;
    ASSERT_NO_THROW(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

/// Verifies the subscribeConfig method works as expected.
TEST_F(NetconfAgentTest, subscribeConfig) {
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
    EXPECT_NO_THROW(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = boost::const_pointer_cast<Element>(netconf_json);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Try subscribeConfig.
    EXPECT_EQ(0, agent_->subscriptions_.size());
    ASSERT_NO_THROW(agent_->initSysrepo());
    EXPECT_EQ(1, agent_->subscriptions_.size());
    EXPECT_NO_THROW(agent_->subscribeConfig(service_pair));
    EXPECT_EQ(2, agent_->subscriptions_.size());

    /// Unsubscribe.
    EXPECT_NO_THROW(agent_->subscriptions_.clear());
}

/// Verifies the update method works as expected: apply new YANG configuration
/// to the server. Note it is called by the subscription callback.
TEST_F(NetconfAgentTest, update) {
    // Initial YANG configuration.
    const YRTree tree0 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    // Load initial YANG configuration.
    ASSERT_NO_THROW(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW(repr.set(tree0, agent_->startup_sess_));
    EXPECT_NO_THROW(agent_->startup_sess_->commit());

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
    EXPECT_NO_THROW(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = boost::const_pointer_cast<Element>(netconf_json);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Subscribe YANG changes.
    EXPECT_EQ(1, agent_->subscriptions_.size());
    EXPECT_NO_THROW(agent_->subscribeConfig(service_pair));
    EXPECT_EQ(2, agent_->subscriptions_.size());

    // Launch server.
    thread_.reset(new Thread([this]() { fakeServer(); signalStopped(); }));

    // Wait until the server is listening.
    waitReady();

    // Change configuration (subnet #1 moved from 10.0.0.0/24 to 10.0.1/0/24).
    const YRTree tree1 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.1.0/24", SR_STRING_T, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    EXPECT_NO_THROW(repr.set(tree1, agent_->running_sess_));
    EXPECT_NO_THROW(agent_->running_sess_->commit());

    // Wait server to be stopped.
    waitStopped();

    // Check request.
    ASSERT_EQ(1, requests_.size());
    const string& request_str = requests_[0];
    ConstElementPtr request;
    ASSERT_NO_THROW(request = Element::fromJSON(request_str));
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
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*request));

    // Check response.
    ASSERT_EQ(1, responses_.size());
    const string& response_str = responses_[0];
    ConstElementPtr response;
    ASSERT_NO_THROW(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

/// Verifies the validate method works as expected: test new YANG configuration
/// with the server. Note it is called by the subscription callback and
/// update is called after.
TEST_F(NetconfAgentTest, validate) {
    // Initial YANG configuration.
    const YRTree tree0 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    // Load initial YANG configuration.
    ASSERT_NO_THROW(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW(repr.set(tree0, agent_->startup_sess_));
    EXPECT_NO_THROW(agent_->startup_sess_->commit());

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
    EXPECT_NO_THROW(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = boost::const_pointer_cast<Element>(netconf_json);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Subscribe YANG changes.
    EXPECT_EQ(1, agent_->subscriptions_.size());
    EXPECT_NO_THROW(agent_->subscribeConfig(service_pair));
    EXPECT_EQ(2, agent_->subscriptions_.size());

    // Launch server twice.
    thread_.reset(new Thread([this]()
                             {
                                 fakeServer();
                                 fakeServer();
                                 signalStopped();
                             }));

    // Wait until the server is listening.
    waitReady();

    // Change configuration (subnet #1 moved from 10.0.0.0/24 to 10.0.1/0/24).
    const YRTree tree1 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.1.0/24", SR_STRING_T, true }, // The change is here!
        { "/kea-dhcp4-server:config/subnet4[id='2']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='2']/id",
          "2", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='2']/subnet",
          "10.0.2.0/24", SR_STRING_T, true }
    };
    EXPECT_NO_THROW(repr.set(tree1, agent_->running_sess_));
    EXPECT_NO_THROW(agent_->running_sess_->commit());

    // Wait servers to be stopped.
    waitStopped();

    // Check requests.
    ASSERT_EQ(2, requests_.size());
    string request_str = requests_[0];
    ConstElementPtr request;
    ASSERT_NO_THROW(request = Element::fromJSON(request_str));
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
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*request));

    request_str = requests_[1];
    ASSERT_NO_THROW(request = Element::fromJSON(request_str));
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
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*request));

    // Check responses.
    ASSERT_EQ(2, responses_.size());
    string response_str = responses_[0];
    ConstElementPtr response;
    ASSERT_NO_THROW(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));

    response_str = responses_[1];
    ASSERT_NO_THROW(response = Element::fromJSON(response_str));
    expected_str = "{\n"
        "\"result\": 0\n"
        "}";
    ASSERT_NO_THROW(expected = Element::fromJSON(expected_str));
    EXPECT_TRUE(expected->equals(*response));
}

/// Verifies what happens when the validate method returns an error.
TEST_F(NetconfAgentTest, noValidate) {
    // Initial YANG configuration.
    const YRTree tree0 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true }
    };
    // Load initial YANG configuration.
    ASSERT_NO_THROW(agent_->initSysrepo());
    YangRepr repr(KEA_DHCP4_SERVER);
    ASSERT_NO_THROW(repr.set(tree0, agent_->startup_sess_));
    EXPECT_NO_THROW(agent_->startup_sess_->commit());

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
    EXPECT_NO_THROW(json =
        parser_context.parseString(config, ParserContext::PARSER_NETCONF));
    ASSERT_TRUE(json);
    ASSERT_EQ(Element::map, json->getType());
    ConstElementPtr netconf_json = json->get("Netconf");
    ASSERT_TRUE(netconf_json);
    json = boost::const_pointer_cast<Element>(netconf_json);
    ASSERT_TRUE(json);
    NetconfSimpleParser::setAllDefaults(json);
    NetconfSimpleParser::deriveParameters(json);
    NetconfSimpleParser parser;
    EXPECT_NO_THROW(parser.parse(ctx, json, false));

    // Get service pair.
    CfgServersMapPtr servers_map = ctx->getCfgServersMap();
    ASSERT_TRUE(servers_map);
    ASSERT_EQ(1, servers_map->size());
    CfgServersMapPair service_pair = *servers_map->begin();

    // Subscribe YANG changes.
    EXPECT_EQ(1, agent_->subscriptions_.size());
    EXPECT_NO_THROW(agent_->subscribeConfig(service_pair));
    EXPECT_EQ(2, agent_->subscriptions_.size());

    // Change configuration (add invalid user context).
    const YRTree tree1 = {
        { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']", "", SR_LIST_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/id",
          "1", SR_UINT32_T, false },
        { "/kea-dhcp4-server:config/subnet4[id='1']/subnet",
          "10.0.0.0/24", SR_STRING_T, true },
        { "/kea-dhcp4-server:config/subnet4[id='1']/user-context",
          "BOGUS", SR_STRING_T, true }
    };
    EXPECT_NO_THROW(repr.set(tree1, agent_->running_sess_));
    try {
        agent_->running_sess_->commit();
    } catch (const sysrepo_exception& ex) {
        EXPECT_EQ("Validation of the changes failed", string(ex.what()));
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    } catch (...) {
        ADD_FAILURE() << "unexpected exception";
    }
}

}
