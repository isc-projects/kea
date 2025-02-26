// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/testutils/test_tls.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/http_command_mgr.h>
#include <config/timeouts.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <hooks/hooks_manager.h>
#include <http/response.h>
#include <http/response_parser.h>
#include <http/testutils/test_http_client.h>
#include <log/logger_support.h>
#include <stats/stats_mgr.h>
#include <util/chrono_time_utils.h>

#include "marker_file.h"
#include "test_libraries.h"

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <atomic>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <thread>

#include <sys/select.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::stats;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "::1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18126;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

class NakedControlledDhcpv6Srv: public ControlledDhcpv6Srv {
    // "Naked" DHCPv6 server, exposes internal fields
public:
    NakedControlledDhcpv6Srv() : ControlledDhcpv6Srv(DHCP6_SERVER_PORT + 10000) {
        CfgMgr::instance().setFamily(AF_INET6);
    }

    /// Expose internal methods for the sake of testing
    using Dhcpv6Srv::receivePacket;
    using Dhcpv6Srv::network_state_;
};

/// @brief Default control connection timeout.
const size_t DEFAULT_CONNECTION_TIMEOUT = 10000;

class HttpCtrlDhcpv6Test : public BaseServerTest {
public:
    HttpCtrlDhcpv6Test()
        : BaseServerTest() {
        reset();
    }

    virtual ~HttpCtrlDhcpv6Test() {
        LeaseMgrFactory::destroy();
        StatsMgr::instance().removeAll();
        CommandMgr::instance().deregisterAll();
        HttpCommandMgr::instance().setConnectionTimeout(DEFAULT_CONNECTION_TIMEOUT);

        reset();
    }

    /// @brief Reset hooks data
    ///
    /// Resets the data for the hooks-related portion of the test by ensuring
    /// that no libraries are loaded and that any marker files are deleted.
    virtual void reset() {
        // Unload any previously-loaded libraries.
        EXPECT_TRUE(HooksManager::unloadLibraries());

        // Get rid of any marker files.
        static_cast<void>(remove(LOAD_MARKER_FILE));
        static_cast<void>(remove(UNLOAD_MARKER_FILE));

        IfaceMgr::instance().deleteAllExternalSockets();
        CfgMgr::instance().clear();
    }
};

/// @brief Base fixture class intended for testing HTTP/HTTPS control channel.
class BaseCtrlChannelDhcpv6Test : public HttpCtrlDhcpv6Test {
public:

    /// @brief List of interfaces (defaults to "*").
    std::string interfaces_;

    /// @brief Pointer to the tested server object
    boost::shared_ptr<NakedControlledDhcpv6Srv> server_;

    /// @brief Default constructor
    ///
    /// Sets socket path to its default value.
    BaseCtrlChannelDhcpv6Test() : interfaces_("\"*\"") {
        reset();
        IfaceMgr::instance().setTestMode(false);
        IfaceMgr::instance().setDetectCallback(std::bind(&IfaceMgr::checkDetectIfaces,
                                               IfaceMgr::instancePtr().get(), ph::_1));
    }

    /// @brief Destructor
    virtual ~BaseCtrlChannelDhcpv6Test() {
        LeaseMgrFactory::destroy();
        StatsMgr::instance().removeAll();

        CommandMgr::instance().deregisterAll();
        HttpCommandMgr::instance().setConnectionTimeout(TIMEOUT_DHCP_SERVER_RECEIVE_COMMAND);

        server_.reset();
        reset();
        IfaceMgr::instance().setTestMode(false);
        IfaceMgr::instance().setDetectCallback(std::bind(&IfaceMgr::checkDetectIfaces,
                                               IfaceMgr::instancePtr().get(), ph::_1));
        IfaceMgr::instance().clearIfaces();
        IfaceMgr::instance().closeSockets();
        IfaceMgr::instance().detectIfaces();
    }

    /// @brief Returns pointer to the server's IO service.
    ///
    /// @return Pointer to the server's IO service or null pointer if the server
    /// hasn't been created.
    IOServicePtr getIOService() {
        return (server_ ? server_->getIOService() : IOServicePtr());
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void timeoutHandler(const bool fail_on_timeout) {
        if (fail_on_timeout) {
            ADD_FAILURE() << "Timeout occurred while running the test!";
        }
        getIOService()->stop();
    }

    /// @brief Runs IO service.
    void runIOService() {
        IOServicePtr io_service = getIOService();
        ASSERT_TRUE(io_service);
        IntervalTimer test_timer(io_service);
        test_timer.setup(std::bind(&BaseCtrlChannelDhcpv6Test::timeoutHandler,
                                   this, true),
                         TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
        // Run until the client stops the service or an error occurs.
        try {
            io_service->run();
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "Exception thrown while running test. Error: " << ex.what();
        } catch (...) {
            ADD_FAILURE() << "Unknown exception thrown while running test.";
        }
        test_timer.cancel();
        if (io_service->stopped()) {
            io_service->restart();
        }
        io_service->poll();
    }

    /// @brief Create a server with a HTTP command channel.
    ///
    /// @param test_config The test configuration to use (if not empty).
    virtual void createHttpChannelServer(std::string test_config = std::string()) = 0;

    /// @brief Reset
    void reset() override {
        HttpCtrlDhcpv6Test::reset();
    }

    /// @brief Constructs a complete HTTP POST given a request body.
    ///
    /// @param request_body string containing the desired request body.
    ///
    /// @return string containing the constructed POST.
    std::string buildPostStr(const std::string& request_body) {
        // Create the command string.
        std::stringstream ss;
        ss << "POST /foo/bar HTTP/1.1\r\n"
              "Content-Type: application/json\r\n"
              "Content-Length: "
              << request_body.size() << "\r\n\r\n"
              << request_body;
        return (ss.str());
    }

    /// @brief Create an HttpResponse from a response string.
    ///
    /// @param response_str a string containing the whole HTTP
    /// response received.
    ///
    /// @return An HttpResponse constructed by parsing the response string.
    HttpResponsePtr parseResponse(const std::string response_str) {
        HttpResponsePtr hr(new HttpResponse());
        HttpResponseParser parser(*hr);
        parser.initModel();
        parser.postBuffer(&response_str[0], response_str.size());
        parser.poll();
        if (!parser.httpParseOk()) {
            isc_throw(Unexpected, "response_str: '" << response_str
                      << "' failed to parse: " << parser.getErrorMessage());
        }

        return (hr);
    }

    /// @brief Conducts a command/response exchange via HttpCommandSocket.
    ///
    /// This method connects to the given server over the given address/port.
    /// If successful, it then sends the given command and retrieves the
    /// server's response.  Note that it polls the server's I/O service
    /// where needed to cause the server to process IO events on
    /// the control channel sockets.
    ///
    /// @param command the command text to execute in JSON form.
    /// @param response variable into which the received response should be
    /// placed.
    /// @param address The server address to connect to.
    /// @param port The server port to connect to.
    virtual void sendHttpCommand(const std::string& command,
                                 std::string& response,
                                 std::string address = std::string(),
                                 int port = 0) = 0;

    /// @brief Parse list answer.
    ///
    /// Clone of parseAnswer but taking the answer as a list and
    /// decapsulating it.
    ///
    /// @param rcode Return code.
    /// @param msg_list The message to parse.
    /// @return The optional argument in the message after decapsulation.
    ConstElementPtr parseListAnswer(int &rcode,
                                    const ConstElementPtr& msg_list) {
        if (!msg_list) {
            isc_throw(CtrlChannelError, "invalid answer: no answer specified");
        }
        if (msg_list->getType() != Element::list) {
            isc_throw(CtrlChannelError, "invalid answer: expected toplevel "
                      << "entry to be a list, got "
                      << Element::typeToName(msg_list->getType())
                      << " instead");
        }
        if (msg_list->size() != 1) {
            isc_throw(CtrlChannelError, "invalid answer: expected toplevel "
                      << "entry to be an one element list, got "
                      << msg_list->size() << " long list instead");
        }
        ConstElementPtr msg = msg_list->get(0);
        if (!msg) {
            isc_throw(CtrlChannelError, "invalid answer: null element");
        }
        if (msg->getType() != Element::map) {
            isc_throw(CtrlChannelError, "invalid answer: expected list of "
                      << "one map, got list of one "
                      << Element::typeToName(msg->getType())
                      << " instead");
        }
        if (!msg->contains(CONTROL_RESULT)) {
            isc_throw(CtrlChannelError, "invalid answer: does not contain "
                      << "mandatory '" << CONTROL_RESULT << "'");
        }

        ConstElementPtr result = msg->get(CONTROL_RESULT);
        if (result->getType() != Element::integer) {
            isc_throw(CtrlChannelError, "invalid answer: expected '"
                      << CONTROL_RESULT << "' to be an integer, got "
                      << Element::typeToName(result->getType())
                      << " instead");
        }

        rcode = result->intValue();

        // If there are arguments, return them.
        ConstElementPtr args = msg->get(CONTROL_ARGUMENTS);
        if (args) {
            return (args);
        }

        // There are no arguments, let's try to return just the text status.
        return (msg->get(CONTROL_TEXT));
    }

    /// @brief Checks response for list-commands.
    ///
    /// This method checks if the list-commands response is generally sane
    /// and whether specified command is mentioned in the response.
    ///
    /// @param rsp response sent back by the server.
    /// @param command command expected to be on the list.
    void checkListCommands(const ConstElementPtr& rsp, const std::string& command) {
        ConstElementPtr params;
        int status_code = -1;
        EXPECT_NO_THROW(params = parseListAnswer(status_code, rsp));
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, status_code);
        ASSERT_TRUE(params);
        ASSERT_EQ(Element::list, params->getType());

        int cnt = 0;
        for (size_t i = 0; i < params->size(); ++i) {
            string tmp = params->get(i)->stringValue();
            if (tmp == command) {
                // Command found, but that's not enough.
                // Need to continue working through the list to see
                // if there are no duplicates.
                cnt++;
            }
        }

        // Exactly one command on the list is expected.
        EXPECT_EQ(1, cnt) << "Command " << command << " not found";
    }

    /// @brief Check if the answer for config-write command is correct.
    ///
    /// @param response_txt response in text form (as read from
    /// the control socket)
    /// @param exp_status expected status (0 success, 1 failure)
    /// @param exp_txt for success cases this defines the expected filename,
    /// for failure cases this defines the expected error message.
    void checkConfigWrite(const std::string& response_txt, int exp_status,
                          const std::string& exp_txt = "") {

        ConstElementPtr rsp;
        EXPECT_NO_THROW(rsp = Element::fromJSON(response_txt));
        ASSERT_TRUE(rsp);

        int status;
        ConstElementPtr params = parseListAnswer(status, rsp);
        EXPECT_EQ(exp_status, status);

        if (exp_status == CONTROL_RESULT_SUCCESS) {
            // Let's check couple things...

            // The parameters must include filename
            ASSERT_TRUE(params);
            ASSERT_TRUE(params->get("filename"));
            ASSERT_EQ(Element::string, params->get("filename")->getType());
            EXPECT_EQ(exp_txt, params->get("filename")->stringValue());

            // The parameters must include size. And the size
            // must indicate some content.
            ASSERT_TRUE(params->get("size"));
            ASSERT_EQ(Element::integer, params->get("size")->getType());
            int64_t size = params->get("size")->intValue();
            EXPECT_LE(1, size);

            // Now check if the file is really there and suitable for
            // opening.
            ifstream f(exp_txt, ios::binary | ios::ate);
            ASSERT_TRUE(f.good());

            // Now check that it is the correct size as reported.
            EXPECT_EQ(size, static_cast<int64_t>(f.tellg()));

            // Finally, check that it's really a JSON.
            ElementPtr from_file = Element::fromJSONFile(exp_txt);
            ASSERT_TRUE(from_file);
        } else if (exp_status == CONTROL_RESULT_ERROR) {

            // Let's check if the reason for failure was given.
            ConstElementPtr text = rsp->get("text");
            ASSERT_TRUE(text);
            ASSERT_EQ(Element::string, text->getType());
            EXPECT_EQ(exp_txt, text->stringValue());
        } else {
            ADD_FAILURE() << "Invalid expected status: " << exp_status;
        }
    }

    /// @brief Handler for long command.
    ///
    /// It checks whether the received command is equal to the one specified
    /// as an argument.
    ///
    /// @param expected_command String representing an expected command.
    /// @param command_name Command name received by the handler.
    /// @param arguments Command arguments received by the handler.
    ///
    /// @returns Success answer.
    static ConstElementPtr
    longCommandHandler(const std::string& expected_command,
                       const std::string& command_name,
                       const ConstElementPtr& arguments) {
        // The handler is called with a command name and the structure holding
        // command arguments. We have to rebuild the command from those
        // two arguments so as it can be compared against expected_command.
        ElementPtr entire_command = Element::createMap();
        entire_command->set("command", Element::create(command_name));
        entire_command->set("arguments", (arguments));

        // The rebuilt command will have a different order of parameters so
        // let's parse expected_command back to JSON to guarantee that
        // both structures are built using the same order.
        EXPECT_EQ(Element::fromJSON(expected_command)->str(),
                  entire_command->str());
        return (createAnswer(CONTROL_RESULT_SUCCESS, "long command received ok"));
    }

    /// @brief Command handler which generates long response
    ///
    /// This handler generates a large response (over 400kB). It includes
    /// a list of randomly generated strings to make sure that the test
    /// can catch out of order delivery.
    static ConstElementPtr
    longResponseHandler(const std::string&, const ConstElementPtr&) {
        ElementPtr arguments = Element::createList();
        for (unsigned i = 0; i < 80000; ++i) {
            std::ostringstream s;
            s << std::setw(5) << i;
            arguments->add(Element::create(s.str()));
        }
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    // Tests that the server properly responds to invalid commands sent
    // via ControlChannel.
    void testControlChannelNegative();

    // Tests that the server properly responds to shutdown command sent
    // via ControlChannel.
    void testControlChannelShutdown();

    // Tests that the server properly responds to statistics commands.
    void testControlChannelStats();

    // Tests if the server returns its configuration using config-get.
    void testConfigGet();

    // Tests if the server returns the hash of its configuration using
    // config-hash-get.
    void testConfigHashGet();

    // This test verifies that the DHCP server handles version-get commands.
    void testGetVersion();

    // This test verifies that the DHCP server handles server-tag-get command.
    void testServerTagGet();

    // This test verifies that the DHCP server handles status-get commands.
    void testStatusGet();

    // Check that status is returned even if LeaseMgr and HostMgr are
    // not created.
    void testNoManagers();

    // Checks that socket status exists in status-get responses.
    void testStatusGetSockets();

    // Checks that socket status includes errors in status-get responses.
    void testStatusGetSocketsErrors();

    // This test verifies that the DHCP server handles
    // config-backend-pull command.
    void testConfigBackendPull();

    // This test verifies that the DHCP server immediately reclaims expired
    // leases on leases-reclaim command.
    void testControlLeasesReclaim();

    // This test verifies that the DHCP server immediately reclaims expired
    // leases on leases-reclaim command with remove = true.
    void testControlLeasesReclaimRemove();

    // Tests that the server properly responds to list-commands command sent
    // via ControlChannel.
    void testListCommands();

    // Tests if config-write can be called without any parameters.
    void testConfigWriteNoFilename();

    // Tests if config-write can be called with a valid filename as parameter.
    void testConfigWriteFilename();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is missing.
    void testConfigReloadMissingFile();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is not a valid JSON.
    void testConfigReloadBrokenFile();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is loaded correctly.
    void testConfigReloadValid();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is loaded correctly.
    void testConfigReloadDetectInterfaces();

    // This test verifies that disable DHCP service command performs
    // sanity check on parameters.
    void testDhcpDisableBadParam();

    // This test verifies if it is possible to disable DHCP service
    // via command.
    void testDhcpDisable();

    // This test verifies if it is possible to disable DHCP service using
    // the origin-id.
    void testDhcpDisableOriginId();

    // This test verifies that it is possible to disable DHCP service
    // for a short period of time, after which the service is
    // automatically enabled.
    void testDhcpDisableTemporarily();

    // This test verifies that enable DHCP service command performs
    // sanity check on parameters.
    void testDhcpEnableBadParam();

    // This test verifies if it is possible to enable DHCP service via command.
    void testDhcpEnable();

    // This test verifies if it is possible to enable DHCP service using
    // the origin-id.
    void testDhcpEnableOriginId();

    // This test verifies that the server can receive and process a
    // large command.
    void testLongCommand();

    // This test verifies that the server can send long response to the client.
    void testLongResponse();

    // This test verifies that the server signals timeout if the transmission
    // takes too long, having received no data from the client.
    void testConnectionTimeoutNoData();
};

/// @brief Fixture class intended for testing HTTP control channel.
class HttpCtrlChannelDhcpv6Test : public BaseCtrlChannelDhcpv6Test {
public:

    /// @brief Create a server with a HTTP command channel.
    ///
    /// @param test_config The test configuration to use (if not empty).
    virtual void createHttpChannelServer(std::string test_config = std::string()) override {
        // Just a simple config. The important part here is the socket
        // location information.
        std::string header =
            "{"
            "    \"interfaces-config\": {"
            "        \"interfaces\": [";

        std::string body = "]"
            "    },"
            "    \"expired-leases-processing\": {"
            "         \"reclaim-timer-wait-time\": 60,"
            "         \"hold-reclaimed-time\": 500,"
            "         \"flush-reclaimed-timer-wait-time\": 60"
            "    },"
            "    \"rebind-timer\": 2000, "
            "    \"renew-timer\": 1000, "
            "    \"subnet6\": [ ],"
            "    \"valid-lifetime\": 4000,"
            "    \"control-socket\": {"
            "        \"socket-type\": \"http\","
            "        \"socket-address\": \"::1\","
            "        \"socket-port\": 18126"
            "    },"
            "    \"lease-database\": {"
            "       \"type\": \"memfile\", \"persist\": false },"
            "    \"loggers\": [ {"
            "       \"name\": \"kea-dhcp6\","
            "       \"severity\": \"INFO\","
            "       \"debuglevel\": 0"
            "       } ]"
            "}";

        std::string config_txt = header + interfaces_ + body;
        if (!test_config.empty()) {
            config_txt = test_config;
        }
        ASSERT_NO_THROW(server_.reset(new NakedControlledDhcpv6Srv()));

        ConstElementPtr config;
        ASSERT_NO_THROW(config = parseDHCP6(config_txt));

        // Parse the logger configuration explicitly into the staging config.
        // Note this does not alter the current loggers, they remain in
        // effect until we apply the logging config below.  If no logging
        // is supplied logging will revert to default logging.
        server_->configureLogger(config, CfgMgr::instance().getStagingCfg());

        // Let's apply the new logging. We do it early, so we'll be able to print
        // out what exactly is wrong with the new config in case of problems.
        CfgMgr::instance().getStagingCfg()->applyLoggingCfg();

        ConstElementPtr answer = server_->processConfig(config);

        // Commit the configuration so any subsequent reconfigurations
        // will only close the command channel if its configuration has
        // changed.
        CfgMgr::instance().commit();

        ASSERT_TRUE(answer);

        int status = 0;
        ConstElementPtr txt = isc::config::parseAnswer(status, answer);
        // This should succeed. If not, print the error message.
        ASSERT_EQ(0, status) << txt->str();

        // Now check that the socket was indeed open.
        ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    }

    /// @brief Conducts a command/response exchange via HttpCommandSocket.
    ///
    /// This method connects to the given server over the given address/port.
    /// If successful, it then sends the given command and retrieves the
    /// server's response.  Note that it polls the server's I/O service
    /// where needed to cause the server to process IO events on
    /// the control channel sockets.
    ///
    /// @param command the command text to execute in JSON form.
    /// @param response variable into which the received response should be
    /// placed.
    /// @param address The server address to connect to.
    /// @param port The server port to connect to.
    virtual void sendHttpCommand(const std::string& command,
                                 std::string& response,
                                 std::string address = std::string(),
                                 int port = 0) override {
        response = "";
        IOServicePtr io_service = getIOService();
        ASSERT_TRUE(io_service);
        if (address.empty()) {
            address = SERVER_ADDRESS;
        }
        if (!port) {
            port = SERVER_PORT;
        }
        TestHttpClientPtr client(new TestHttpClient(io_service, address,
                                                    port));
        ASSERT_TRUE(client);

        // Send the command. This will trigger server's handler which receives
        // data over the HTTP socket. The server will start sending response
        // to the client.
        ASSERT_NO_THROW(client->startRequest(buildPostStr(command)));
        runIOService();
        ASSERT_TRUE(client->receiveDone());

        // Read the response generated by the server.
        HttpResponsePtr hr;
        ASSERT_NO_THROW(hr = parseResponse(client->getResponse()));
        response = hr->getBody();

        // Now close client.
        client->close();

        ASSERT_NO_THROW(io_service->poll());
    }
};

/// @brief Fixture class intended for testing HTTPS control channel.
class HttpsCtrlChannelDhcpv6Test : public BaseCtrlChannelDhcpv6Test {
public:

    /// @brief Create a server with a HTTP command channel.
    ///
    /// @param test_config The test configuration to use (if not empty).
    virtual void createHttpChannelServer(std::string test_config = std::string()) override {
        // Just a simple config. The important part here is the socket
        // location information.
        string ca_dir(string(TEST_CA_DIR));
        ostringstream config_st;
        config_st
            << "{"
            << "    \"interfaces-config\": {"
            << "        \"interfaces\": ["
            << interfaces_
            << "]"
            << "    },"
            << "    \"expired-leases-processing\": {"
            << "         \"reclaim-timer-wait-time\": 60,"
            << "         \"hold-reclaimed-time\": 500,"
            << "         \"flush-reclaimed-timer-wait-time\": 60"
            << "    },"
            << "    \"rebind-timer\": 2000, "
            << "    \"renew-timer\": 1000, "
            << "    \"subnet6\": [ ],"
            << "    \"valid-lifetime\": 4000,"
            << "    \"control-socket\": {"
            << "        \"socket-type\": \"http\","
            << "        \"socket-address\": \"::1\","
            << "        \"socket-port\": 18126,"
            << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\","
            << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\","
            << "        \"key-file\": \"" << ca_dir << "/kea-server.key\""
            << "    },"
            << "    \"lease-database\": {"
            << "       \"type\": \"memfile\", \"persist\": false },"
            << "    \"loggers\": [ {"
            << "       \"name\": \"kea-dhcp6\","
            << "       \"severity\": \"INFO\","
            << "       \"debuglevel\": 0"
            << "       } ]"
            << "}";

        std::string config_txt = config_st.str();

        ASSERT_NO_THROW(server_.reset(new NakedControlledDhcpv6Srv()));
        if (!test_config.empty()) {
            config_txt = test_config;
        }

        ConstElementPtr config;
        ASSERT_NO_THROW(config = parseDHCP6(config_txt));

        // Parse the logger configuration explicitly into the staging config.
        // Note this does not alter the current loggers, they remain in
        // effect until we apply the logging config below.  If no logging
        // is supplied logging will revert to default logging.
        server_->configureLogger(config, CfgMgr::instance().getStagingCfg());

        // Let's apply the new logging. We do it early, so we'll be able to print
        // out what exactly is wrong with the new config in case of problems.
        CfgMgr::instance().getStagingCfg()->applyLoggingCfg();

        ConstElementPtr answer = server_->processConfig(config);

        // Commit the configuration so any subsequent reconfigurations
        // will only close the command channel if its configuration has
        // changed.
        CfgMgr::instance().commit();

        ASSERT_TRUE(answer);

        int status = 0;
        ConstElementPtr txt = isc::config::parseAnswer(status, answer);
        // This should succeed. If not, print the error message.
        ASSERT_EQ(0, status) << txt->str();

        // Now check that the socket was indeed open.
        ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    }

    /// @brief Conducts a command/response exchange via HttpCommandSocket.
    ///
    /// This method connects to the given server over the given address/port.
    /// If successful, it then sends the given command and retrieves the
    /// server's response.  Note that it polls the server's I/O service
    /// where needed to cause the server to process IO events on
    /// the control channel sockets.
    ///
    /// @param command the command text to execute in JSON form.
    /// @param response variable into which the received response should be
    /// placed.
    /// @param address The server address to connect to.
    /// @param port The server port to connect to.
    virtual void sendHttpCommand(const std::string& command,
                                 std::string& response,
                                 std::string address = std::string(),
                                 int port = 0) override {
        response = "";
        IOServicePtr io_service = getIOService();
        ASSERT_TRUE(io_service);

        TlsContextPtr client_tls_context;
        configClient(client_tls_context);
        if (address.empty()) {
            address = SERVER_ADDRESS;
        }
        if (!port) {
            port = SERVER_PORT;
        }
        TestHttpsClientPtr client(new TestHttpsClient(io_service, client_tls_context,
                                                      address, port));
        ASSERT_TRUE(client);

        // Send the command. This will trigger server's handler which receives
        // data over the HTTP socket. The server will start sending response
        // to the client.
        ASSERT_NO_THROW(client->startRequest(buildPostStr(command)));
        runIOService();
        ASSERT_TRUE(client->receiveDone());

        // Read the response generated by the server.
        HttpResponsePtr hr;
        ASSERT_NO_THROW(hr = parseResponse(client->getResponse()));
        response = hr->getBody();

        // Now close client.
        client->close();

        ASSERT_NO_THROW(io_service->poll());
    }
};

// Tests that the server properly responds to invalid commands sent
// via ControlChannel.
void
BaseCtrlChannelDhcpv6Test::testControlChannelNegative() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"bogus\" }", response);
    EXPECT_EQ("[ { \"result\": 2,"
              " \"text\": \"'bogus' command not supported.\" } ]",
              response);

    sendHttpCommand("utter nonsense", response);
    EXPECT_EQ("{ \"result\": 400, \"text\": \"Bad Request\" }", response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, controlChannelNegative) {
    testControlChannelNegative();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, controlChannelNegative) {
    testControlChannelNegative();
}

// Tests that the server properly responds to shutdown command sent
// via ControlChannel.
void
BaseCtrlChannelDhcpv6Test::testControlChannelShutdown() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"shutdown\" }", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Shutting down.\" } ]",
              response);

    EXPECT_EQ(EXIT_SUCCESS, server_->getExitValue());
}

TEST_F(HttpCtrlChannelDhcpv6Test, controlChannelShutdown) {
    testControlChannelShutdown();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, controlChannelShutdown) {
    testControlChannelShutdown();
}

// Tests that the server properly responds to statistics commands.  Note this
// is really only intended to verify that the appropriate Statistics handler
// is called based on the command.  It is not intended to be an exhaustive
// test of Dhcpv6 statistics.
void
BaseCtrlChannelDhcpv6Test::testControlChannelStats() {
    createHttpChannelServer();
    std::string response;

    // Check statistic-get
    sendHttpCommand("{ \"command\" : \"statistic-get\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\" }}", response);
    EXPECT_EQ("[ { \"arguments\": {  }, \"result\": 0 } ]", response);

    // Check statistic-get-all
    sendHttpCommand("{ \"command\" : \"statistic-get-all\", "
                    "  \"arguments\": {}}", response);

    std::set<std::string> initial_stats = {
        "pkt6-received",
        "pkt6-solicit-received",
        "pkt6-advertise-received",
        "pkt6-request-received",
        "pkt6-reply-received",
        "pkt6-renew-received",
        "pkt6-rebind-received",
        "pkt6-decline-received",
        "pkt6-release-received",
        "pkt6-infrequest-received",
        "pkt6-dhcpv4-query-received",
        "pkt6-dhcpv4-response-received",
        "pkt6-addr-reg-inform-received",
        "pkt6-addr-reg-reply-received",
        "pkt6-unknown-received",
        "pkt6-sent",
        "pkt6-advertise-sent",
        "pkt6-reply-sent",
        "pkt6-dhcpv4-response-sent",
        "pkt6-addr-reg-reply-sent",
        "pkt6-parse-failed",
        "pkt6-receive-drop",
        "v6-allocation-fail",
        "v6-allocation-fail-shared-network",
        "v6-allocation-fail-subnet",
        "v6-allocation-fail-no-pools",
        "v6-allocation-fail-classes",
        "v6-ia-na-lease-reuses",
        "v6-ia-pd-lease-reuses",
    };

    std::ostringstream s;
    s << "[ { \"arguments\": { ";
    bool first = true;
    for (auto const& st : initial_stats) {
        if (!first) {
            s << ", ";
        } else {
            first = false;
        }
        s << "\"" << st << "\": [ [ 0, \"";
        s << isc::util::clockToText(StatsMgr::instance().getObservation(st)->getInteger().second);
        s << "\" ] ]";
    }
    s << " }, \"result\": 0 } ]";

    auto stats_get_all = s.str();

    EXPECT_EQ(stats_get_all, response);

    // Check statistic-reset
    sendHttpCommand("{ \"command\" : \"statistic-reset\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\" }}", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"No 'bogus' statistic found\" } ]",
              response);

    // Check statistic-reset-all
    sendHttpCommand("{ \"command\" : \"statistic-reset-all\", "
                    "  \"arguments\": {}}", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": "
              "\"All statistics reset to neutral values.\" } ]",
              response);

    // Check statistic-remove
    sendHttpCommand("{ \"command\" : \"statistic-remove\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\" }}", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"No 'bogus' statistic found\" } ]",
              response);

    // Check statistic-remove-all (deprecated)

    // Check statistic-sample-age-set
    sendHttpCommand("{ \"command\" : \"statistic-sample-age-set\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\", \"duration\": 1245 }}", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"No 'bogus' statistic found\" } ]",
              response);

    // Check statistic-sample-age-set-all
    sendHttpCommand("{ \"command\" : \"statistic-sample-age-set-all\", "
                    "  \"arguments\": {"
                    "  \"duration\": 1245 }}", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": "
              "\"All statistics duration limit are set.\" } ]",
              response);

    // Check statistic-sample-count-set
    sendHttpCommand("{ \"command\" : \"statistic-sample-count-set\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\", \"max-samples\": 100 }}", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"No 'bogus' statistic found\" } ]",
              response);

    // Check statistic-sample-count-set-all
    sendHttpCommand("{ \"command\" : \"statistic-sample-count-set-all\", "
                    "  \"arguments\": {"
                    "  \"max-samples\": 100 }}", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": "
              "\"All statistics count limit are set.\" } ]",
              response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, controlChannelStats) {
    testControlChannelStats();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, controlChannelStats) {
    testControlChannelStats();
}

// Check that the "config-set" command will replace current configuration.
TEST_F(HttpCtrlChannelDhcpv6Test, configSet) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"3003::/64\", \"id\": 2, \n"
        "                \"pools\": [{ \"pool\": \"3003::100-3003::200\" }]}\n";
    string bad_subnet =
        "               {\"comment\": \"3005::/64\", \"id\": 10, \n"
        "                \"pools\": [{ \"pool\": \"3005::100-3005::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string option_def =
        "    ,\"option-def\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"type\": \"uint32\",\n"
        "        \"array\": false,\n"
        "        \"record-types\": \"\",\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket =
        "    ,\"control-socket\": { \n"
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126 \n"
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << option_def
       << option_data
       << control_socket
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"BCE3D0CC68CBBB49C3F5967E3FFCB4E44E55CBFB53814761B12ADB5C7CD95C1F\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def =
        LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << bad_subnet
       << subnet_footer
       << control_socket
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    sendHttpCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("[ { \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' "
              "parameter is missing for a subnet being configured "
              "(<string>:21:17)\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    def = LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Create a valid config with two subnets and no command channel.
    // It should succeed, client should still receive the response
    os.str("");
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << ",\n"
       << subnet2
       << subnet_footer
       << "}\n"                      // close dhcp6
       << "}}";

    // Verify the HTTP control channel socket exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Send the config-set command.
    sendHttpCommand(os.str(), response);

    // Verify the HTTP control channel socket no longer exists.
    ASSERT_NO_THROW(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // With no command channel, should still receive the response.
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"48035E8F9CC25FC1F6175B78CCC6B8A673CACBA9E956C0ED3079C478BF1F2D1A\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(2, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Check that the "config-set" command will replace current configuration.
TEST_F(HttpsCtrlChannelDhcpv6Test, configSet) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string ca_dir(string(TEST_CA_DIR));
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"3003::/64\", \"id\": 2, \n"
        "                \"pools\": [{ \"pool\": \"3003::100-3003::200\" }]}\n";
    string bad_subnet =
        "               {\"comment\": \"3005::/64\", \"id\": 10, \n"
        "                \"pools\": [{ \"pool\": \"3005::100-3005::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string option_def =
        "    ,\"option-def\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"type\": \"uint32\",\n"
        "        \"array\": false,\n"
        "        \"record-types\": \"\",\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket_header =
        "    ,\"control-socket\": { \n"
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126, \n";
    string control_socket_footer =
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << option_def
       << option_data
       << control_socket_header
       << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
       << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
       << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
       << control_socket_footer
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration successful." is there
    EXPECT_NE(response.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Configuration successful.\""),
              std::string::npos);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def =
        LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << bad_subnet
       << subnet_footer
       << control_socket_header
       << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
       << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
       << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
       << control_socket_footer
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    sendHttpCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("[ { \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' "
              "parameter is missing for a subnet being configured "
              "(<string>:21:17)\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    def = LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Create a valid config with two subnets and no command channel.
    // It should succeed, client should still receive the response
    os.str("");
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << ",\n"
       << subnet2
       << subnet_footer
       << "}\n"                      // close dhcp6
       << "}}";

    // Verify the HTTP control channel socket exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Send the config-set command.
    sendHttpCommand(os.str(), response);

    // Verify the HTTP control channel socket no longer exists.
    ASSERT_NO_THROW(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // With no command channel, should still receive the response.
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"48035E8F9CC25FC1F6175B78CCC6B8A673CACBA9E956C0ED3079C478BF1F2D1A\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(2, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Tests if the server returns its configuration using config-get.
// Note there are separate tests that verify if toElement() called by the
// config-get handler are actually converting the configuration correctly.
void
BaseCtrlChannelDhcpv6Test::testConfigGet() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"config-get\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    // Ok, now roughly check if the response seems legit.
    ASSERT_TRUE(cfg);
    ASSERT_EQ(Element::map, cfg->getType());
    EXPECT_TRUE(cfg->get("Dhcp6"));
    EXPECT_TRUE(cfg->get("Dhcp6")->get("loggers"));
}

TEST_F(HttpCtrlChannelDhcpv6Test, configGet) {
    testConfigGet();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configGet) {
    testConfigGet();
}

// Tests if the server returns the hash of its configuration using
// config-hash-get.
void
BaseCtrlChannelDhcpv6Test::testConfigHashGet() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"config-hash-get\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr args = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);
    // The parseListAnswer is trying to be smart with ignoring hash.
    // But this time we really want to see the hash, so we'll retrieve
    // the arguments manually.
    args = rsp->get(0)->get(CONTROL_ARGUMENTS);

    // Ok, now roughly check if the response seems legit.
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());
    ConstElementPtr hash = args->get("hash");
    ASSERT_TRUE(hash);
    ASSERT_EQ(Element::string, hash->getType());
    // SHA-256 -> 64 hex digits.
    EXPECT_EQ(64, hash->stringValue().size());
}

TEST_F(HttpCtrlChannelDhcpv6Test, configHashGet) {
    testConfigHashGet();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configHashGet) {
    testConfigHashGet();
}

// Verify that the "config-test" command will do what we expect.
TEST_F(HttpCtrlChannelDhcpv6Test, configTest) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string config_test_txt = "{ \"command\": \"config-test\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"3003::/64\", \"id\": 2, \n"
        "                \"pools\": [{ \"pool\": \"3003::100-3003::200\" }]}\n";
    string bad_subnet =
        "               {\"comment\": \"3005::/64\", \"id\": 10, \n"
        "                \"pools\": [{ \"pool\": \"3005::100-3005::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string control_socket =
        "    ,\"control-socket\": { \n"
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126 \n"
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << control_socket
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);

    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"DE129E7DD1C402721C83B74C5BBD7C330A0B705108A198CB868377031169BBC2\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_test_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << bad_subnet
       << subnet_footer
       << control_socket
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-test command
    sendHttpCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("[ { \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' "
              "parameter is missing for a subnet being configured "
              "(<string>:21:17)\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a valid config with two subnets and no command channel.
    os.str("");
    os << config_test_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << ",\n"
       << subnet2
       << subnet_footer
       << "}\n"                      // close dhcp6
       << "}}";

    // Verify the HTTP control channel socket exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Send the config-test command.
    sendHttpCommand(os.str(), response);

    // Verify the HTTP control channel socket still exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Configuration seems sane. "
              "Control-socket, hook-libraries, and D2 configuration were "
              "sanity checked, but not applied.\" } ]",
              response);

    // Check that the config was not applied.
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Verify that the "config-test" command will do what we expect.
TEST_F(HttpsCtrlChannelDhcpv6Test, configTest) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string ca_dir(string(TEST_CA_DIR));
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string config_test_txt = "{ \"command\": \"config-test\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"3003::/64\", \"id\": 2, \n"
        "                \"pools\": [{ \"pool\": \"3003::100-3003::200\" }]}\n";
    string bad_subnet =
        "               {\"comment\": \"3005::/64\", \"id\": 10, \n"
        "                \"pools\": [{ \"pool\": \"3005::100-3005::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string control_socket_header =
        "    ,\"control-socket\": { \n"
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126, \n";
    string control_socket_footer =
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << control_socket_header
       << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
       << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
       << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
       << control_socket_footer
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);

    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration successful." is there
    EXPECT_NE(response.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Configuration successful.\""),
              std::string::npos);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_test_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << bad_subnet
       << subnet_footer
       << control_socket_header
       << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
       << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
       << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
       << control_socket_footer
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-test command
    sendHttpCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("[ { \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' "
              "parameter is missing for a subnet being configured "
              "(<string>:21:17)\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a valid config with two subnets and no command channel.
    os.str("");
    os << config_test_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << ",\n"
       << subnet2
       << subnet_footer
       << "}\n"                      // close dhcp6
       << "}}";

    // Verify the HTTP control channel socket exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Send the config-test command.
    sendHttpCommand(os.str(), response);

    // Verify the HTTP control channel socket still exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Configuration seems sane. "
              "Control-socket, hook-libraries, and D2 configuration were "
              "sanity checked, but not applied.\" } ]",
              response);

    // Check that the config was not applied.
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Verify that the "subnet6-select-test" command will do what we expect.
TEST_F(HttpCtrlChannelDhcpv6Test, subnetSelectTest) {
    createHttpChannelServer();

    string command_txt = "{ \"command\": \"subnet6-select-test\", \"arguments\": { \"classes\": [ \"foo\" ] } }";

    // Send the subnet6-select-test command
    std::string response;
    sendHttpCommand(command_txt, response);

    EXPECT_EQ("[ { \"result\": 3, \"text\": \"no subnet selected\" } ]",
              response);
}

// Verify that the "subnet6-select-test" command will do what we expect.
TEST_F(HttpsCtrlChannelDhcpv6Test, subnetSelectTest) {
    createHttpChannelServer();

    string command_txt = "{ \"command\": \"subnet6-select-test\", \"arguments\": { \"classes\": [ \"foo\" ] } }";

    // Send the subnet6-select-test command
    std::string response;
    sendHttpCommand(command_txt, response);

    EXPECT_EQ("[ { \"result\": 3, \"text\": \"no subnet selected\" } ]",
              response);
}

// This test verifies that the DHCP server handles version-get commands.
void
BaseCtrlChannelDhcpv6Test::testGetVersion() {
    createHttpChannelServer();

    std::string response;

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the build-report command
    sendHttpCommand("{ \"command\": \"build-report\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("GTEST_VERSION") != string::npos);
}

TEST_F(HttpCtrlChannelDhcpv6Test, getVersion) {
    testGetVersion();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, getVersion) {
    testGetVersion();
}

// This test verifies that the DHCP server handles server-tag-get command.
void
BaseCtrlChannelDhcpv6Test::testServerTagGet() {
    createHttpChannelServer();

    std::string response;
    std::string expected;

    // Send the server-tag-get command
    sendHttpCommand("{ \"command\": \"server-tag-get\" }", response);
    expected = "[ { \"arguments\": { \"server-tag\": \"\" }, ";
    expected += "\"result\": 0 } ]";
    EXPECT_EQ(expected, response);

    // Set a value to the server tag
    CfgMgr::instance().getCurrentCfg()->setServerTag("foobar");

    // Retry...
    sendHttpCommand("{ \"command\": \"server-tag-get\" }", response);
    expected = "[ { \"arguments\": { \"server-tag\": \"foobar\" }, ";
    expected += "\"result\": 0 } ]";
    EXPECT_EQ(expected, response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, serverTagGet) {
    testServerTagGet();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, serverTagGet) {
    testServerTagGet();
}

// This test verifies that the DHCP server handles status-get commands.
void
BaseCtrlChannelDhcpv6Test::testStatusGet() {
    createHttpChannelServer();

    // start_ is initialized by init.
    ASSERT_THROW(server_->init("/no/such/file"), BadValue);

    std::string response_txt;

    // Send the status-get command.
    sendHttpCommand("{ \"command\": \"status-get\" }", response_txt);
    ConstElementPtr response_list;
    ASSERT_NO_THROW(response_list = Element::fromJSON(response_txt));
    ASSERT_TRUE(response_list);
    ASSERT_EQ(Element::list, response_list->getType());
    EXPECT_EQ(1, response_list->size());
    ConstElementPtr response = response_list->get(0);
    ASSERT_TRUE(response);
    ASSERT_EQ(Element::map, response->getType());
    EXPECT_EQ(2, response->size());
    ConstElementPtr result = response->get("result");
    ASSERT_TRUE(result);
    ASSERT_EQ(Element::integer, result->getType());
    EXPECT_EQ(0, result->intValue());
    ConstElementPtr arguments = response->get("arguments");
    ASSERT_EQ(Element::map, arguments->getType());

    // The returned pid should be the pid of our process.
    auto found_pid = arguments->get("pid");
    ASSERT_TRUE(found_pid);
    EXPECT_EQ(static_cast<int64_t>(getpid()), found_pid->intValue());

    // It is hard to check the actual uptime (and reload) as it is based
    // on current time. Let's just make sure it is within a reasonable
    // range.
    auto found_uptime = arguments->get("uptime");
    ASSERT_TRUE(found_uptime);
    EXPECT_LE(found_uptime->intValue(), 5);
    EXPECT_GE(found_uptime->intValue(), 0);

    auto found_reload = arguments->get("reload");
    ASSERT_TRUE(found_reload);
    EXPECT_LE(found_reload->intValue(), 5);
    EXPECT_GE(found_reload->intValue(), 0);

    auto found_multi_threading = arguments->get("multi-threading-enabled");
    ASSERT_TRUE(found_multi_threading);
    EXPECT_TRUE(found_multi_threading->boolValue());

    auto found_thread_count = arguments->get("thread-pool-size");
    ASSERT_TRUE(found_thread_count);
    // The default value varies between systems.
    // Let's just make sure it's a positive value.
    EXPECT_LE(0, found_thread_count->intValue());

    auto found_queue_size = arguments->get("packet-queue-size");
    ASSERT_TRUE(found_queue_size);
    EXPECT_EQ(64, found_queue_size->intValue());

    auto found_queue_stats = arguments->get("packet-queue-statistics");
    ASSERT_TRUE(found_queue_stats);
    EXPECT_FALSE(found_queue_stats->str().empty());

    auto found_extended_info_tables = arguments->get("extended-info-tables");
    ASSERT_TRUE(found_extended_info_tables);
    EXPECT_FALSE(found_extended_info_tables->boolValue());

    MultiThreadingMgr::instance().setMode(true);
    MultiThreadingMgr::instance().setThreadPoolSize(4);
    MultiThreadingMgr::instance().setPacketQueueSize(64);
    sendHttpCommand("{ \"command\": \"status-get\" }", response_txt);
    ASSERT_NO_THROW(response_list = Element::fromJSON(response_txt));
    ASSERT_TRUE(response_list);
    ASSERT_EQ(Element::list, response_list->getType());
    EXPECT_EQ(1, response_list->size());
    response = response_list->get(0);
    ASSERT_TRUE(response);
    ASSERT_EQ(Element::map, response->getType());
    EXPECT_EQ(2, response->size());
    result = response->get("result");
    ASSERT_TRUE(result);
    ASSERT_EQ(Element::integer, result->getType());
    EXPECT_EQ(0, result->intValue());
    arguments = response->get("arguments");
    ASSERT_EQ(Element::map, arguments->getType());

    // The returned pid should be the pid of our process.
    found_pid = arguments->get("pid");
    ASSERT_TRUE(found_pid);
    EXPECT_EQ(static_cast<int64_t>(getpid()), found_pid->intValue());

    // It is hard to check the actual uptime (and reload) as it is based
    // on current time. Let's just make sure it is within a reasonable
    // range.
    found_uptime = arguments->get("uptime");
    ASSERT_TRUE(found_uptime);
    EXPECT_LE(found_uptime->intValue(), 5);
    EXPECT_GE(found_uptime->intValue(), 0);

    found_reload = arguments->get("reload");
    ASSERT_TRUE(found_reload);
    EXPECT_LE(found_reload->intValue(), 5);
    EXPECT_GE(found_reload->intValue(), 0);

    found_multi_threading = arguments->get("multi-threading-enabled");
    ASSERT_TRUE(found_multi_threading);
    EXPECT_TRUE(found_multi_threading->boolValue());

    found_thread_count = arguments->get("thread-pool-size");
    ASSERT_TRUE(found_thread_count);
    EXPECT_EQ(found_thread_count->intValue(), 4);

    found_queue_size = arguments->get("packet-queue-size");
    ASSERT_TRUE(found_queue_size);
    EXPECT_EQ(found_queue_size->intValue(), 64);

    found_queue_stats = arguments->get("packet-queue-statistics");
    ASSERT_TRUE(found_queue_stats);
    ASSERT_EQ(Element::list, found_queue_stats->getType());
    EXPECT_EQ(3, found_queue_stats->size());
}

TEST_F(HttpCtrlChannelDhcpv6Test, statusGet) {
    testStatusGet();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, statusGet) {
    testStatusGet();
}

// Check that status is returned even if LeaseMgr and HostMgr are not created.
void
BaseCtrlChannelDhcpv6Test::testNoManagers() {
    // Send the status-get command.
    createHttpChannelServer();
    LeaseMgrFactory::destroy();
    HostMgr::create();
    string response_text;
    sendHttpCommand(R"({ "command": "status-get" })", response_text);
    ConstElementPtr response_list;
    ASSERT_NO_THROW(response_list = Element::fromJSON(response_text));
    ASSERT_TRUE(response_list);
    ASSERT_EQ(Element::list, response_list->getType());
    EXPECT_EQ(1, response_list->size());
    ConstElementPtr response = response_list->get(0);
    ASSERT_TRUE(response);
    ASSERT_EQ(Element::map, response->getType());
    ConstElementPtr result(response->get("result"));
    ASSERT_TRUE(result);
    ASSERT_EQ(Element::integer, result->getType());
    EXPECT_EQ(0, result->intValue());
    ConstElementPtr arguments(response->get("arguments"));
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());
}

TEST_F(HttpCtrlChannelDhcpv6Test, noManagers) {
    testNoManagers();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, noManagers) {
    testNoManagers();
}

// Checks that socket status exists in status-get responses.
void
BaseCtrlChannelDhcpv6Test::testStatusGetSockets() {
    // Create dummy interfaces to test socket status.
    isc::dhcp::test::IfaceMgrTestConfig test_config(true);

    // Send the status-get command.
    createHttpChannelServer();
    string response_text;
    sendHttpCommand(R"({ "command": "status-get" })", response_text);
    ConstElementPtr response_list;
    ASSERT_NO_THROW(response_list = Element::fromJSON(response_text));
    ASSERT_TRUE(response_list);
    ASSERT_EQ(Element::list, response_list->getType());
    EXPECT_EQ(1, response_list->size());
    ConstElementPtr response = response_list->get(0);
    ASSERT_TRUE(response);
    ASSERT_EQ(Element::map, response->getType());
    ConstElementPtr result(response->get("result"));
    ASSERT_TRUE(result);
    ASSERT_EQ(Element::integer, result->getType());
    EXPECT_EQ(0, result->intValue());
    ConstElementPtr arguments(response->get("arguments"));
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());

    ConstElementPtr sockets(arguments->get("sockets"));
    ASSERT_TRUE(sockets);
    ASSERT_EQ(Element::map, sockets->getType());

    ConstElementPtr status(sockets->get("status"));
    ASSERT_TRUE(status);
    ASSERT_EQ(Element::string, status->getType());
    EXPECT_EQ("ready", status->stringValue());

    ConstElementPtr errors(sockets->get("errors"));
    ASSERT_FALSE(errors);
}

TEST_F(HttpCtrlChannelDhcpv6Test, statusGetSockets) {
    testStatusGetSockets();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, statusGetSockets) {
    testStatusGetSockets();
}

// Checks that socket status includes errors in status-get responses.
void
BaseCtrlChannelDhcpv6Test::testStatusGetSocketsErrors() {
    // Create dummy interfaces to test socket status and add a custom down interface.
    isc::dhcp::test::IfaceMgrTestConfig test_config(true);
    test_config.addIface("down_interface", 4);
    test_config.setIfaceFlags("down_interface", FlagLoopback(false), FlagUp(false),
                              FlagRunning(true), FlagInactive4(false),
                              FlagInactive6(false));

    // Send the status-get command.
    createHttpChannelServer();
    string response_text;
    sendHttpCommand(R"({ "command": "status-get" })", response_text);
    ConstElementPtr response_list;
    ASSERT_NO_THROW(response_list = Element::fromJSON(response_text));
    ASSERT_TRUE(response_list);
    ASSERT_EQ(Element::list, response_list->getType());
    EXPECT_EQ(1, response_list->size());
    ConstElementPtr response = response_list->get(0);
    ASSERT_TRUE(response);
    ASSERT_EQ(Element::map, response->getType());
    ConstElementPtr result(response->get("result"));
    ASSERT_TRUE(result);
    ASSERT_EQ(Element::integer, result->getType());
    EXPECT_EQ(0, result->intValue());
    ConstElementPtr arguments(response->get("arguments"));
    ASSERT_TRUE(arguments);
    ASSERT_EQ(Element::map, arguments->getType());

    ConstElementPtr sockets(arguments->get("sockets"));
    ASSERT_TRUE(sockets);
    ASSERT_EQ(Element::map, sockets->getType());

    ConstElementPtr status(sockets->get("status"));
    ASSERT_TRUE(status);
    ASSERT_EQ(Element::string, status->getType());
    EXPECT_EQ("failed", status->stringValue());

    ConstElementPtr errors(sockets->get("errors"));
    ASSERT_TRUE(errors);
    ASSERT_EQ(Element::list, errors->getType());
    ASSERT_EQ(1, errors->size());

    ConstElementPtr error(errors->get(0));
    ASSERT_TRUE(error);
    ASSERT_EQ(Element::string, error->getType());
    ASSERT_EQ("the interface down_interface is down", error->stringValue());
}

TEST_F(HttpCtrlChannelDhcpv6Test, statusGetSocketsErrors) {
    testStatusGetSocketsErrors();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, statusGetSocketsErrors) {
    testStatusGetSocketsErrors();
}

// This test verifies that the DHCP server handles config-backend-pull command.
void
BaseCtrlChannelDhcpv6Test::testConfigBackendPull() {
    createHttpChannelServer();

    std::string response;
    std::string expected;

    // Send the config-backend-pull command. Note there is no configured backed.
    sendHttpCommand("{ \"command\": \"config-backend-pull\" }", response);
    expected = "[ { \"result\": 3, \"text\": \"No config backend.\" } ]";
    EXPECT_EQ(expected, response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, configBackendPull) {
    testConfigBackendPull();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configBackendPull) {
    testConfigBackendPull();
}

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command.
void
BaseCtrlChannelDhcpv6Test::testControlLeasesReclaim() {
    createHttpChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    DuidPtr duid0(new DUID(DUID::fromText("00:01:02:03:04:05:06").getDuid()));
    Lease6Ptr lease0(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"),
                                duid0, 1, 50, 60, SubnetID(1)));
    lease0->cltt_ = time(NULL) - 100;
    DuidPtr duid1(new DUID(DUID::fromText("01:02:03:04:05:06:07").getDuid()));
    Lease6Ptr lease1(new Lease6(Lease::TYPE_NA, IOAddress("3000::2"),
                                duid1, 1, 50, 60, SubnetID(1)));
    lease1->cltt_ = time(NULL) - 100;

    // Add leases to the database.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease0));
    ASSERT_NO_THROW(lease_mgr.addLease(lease1));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1")));
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2")));

    // No arguments
    std::string response;
    sendHttpCommand("{ \"command\": \"leases-reclaim\" }", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": "
              "\"Missing mandatory 'remove' parameter.\" } ]",
              response);

    // Bad argument name
    sendHttpCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"reclaim\": true } }", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": "
              "\"Missing mandatory 'remove' parameter.\" } ]",
              response);

    // Bad remove argument type
    sendHttpCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": \"bogus\" } }", response);
    EXPECT_EQ("[ { \"result\": 1, \"text\": "
              "\"'remove' parameter expected to be a boolean.\" } ]",
              response);

    // Send the command
    sendHttpCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": false } }", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": "
              "\"Reclamation of expired leases is complete.\" } ]",
              response);

    // Leases should be reclaimed, but not removed
    ASSERT_NO_THROW(
        lease0 = lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1"))
    );
    ASSERT_NO_THROW(
        lease1 = lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2"))
    );
    ASSERT_TRUE(lease0);
    ASSERT_TRUE(lease1);
    EXPECT_TRUE(lease0->stateExpiredReclaimed());
    EXPECT_TRUE(lease1->stateExpiredReclaimed());
}

TEST_F(HttpCtrlChannelDhcpv6Test, controlLeasesReclaim) {
    testControlLeasesReclaim();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, controlLeasesReclaim) {
    testControlLeasesReclaim();
}

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command with remove = true.
void
BaseCtrlChannelDhcpv6Test::testControlLeasesReclaimRemove() {
    createHttpChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    DuidPtr duid0(new DUID(DUID::fromText("00:01:02:03:04:05:06").getDuid()));
    Lease6Ptr lease0(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"),
                                duid0, 1, 50, 60, SubnetID(1)));
    lease0->cltt_ = time(NULL) - 100;
    DuidPtr duid1(new DUID(DUID::fromText("01:02:03:04:05:06:07").getDuid()));
    Lease6Ptr lease1(new Lease6(Lease::TYPE_NA, IOAddress("3000::2"),
                                duid1, 1, 50, 60, SubnetID(1)));
    lease1->cltt_ = time(NULL) - 100;

    // Add leases to the database.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease0));
    ASSERT_NO_THROW(lease_mgr.addLease(lease1));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1")));
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2")));

    // Send the command
    std::string response;
    sendHttpCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": true } }", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": "
              "\"Reclamation of expired leases is complete.\" } ]",
              response);

    // Leases should have been removed.
    ASSERT_NO_THROW(
        lease0 = lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1"))
    );
    ASSERT_NO_THROW(
        lease1 = lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2"))
    );
    ASSERT_FALSE(lease0);
    ASSERT_FALSE(lease1);
}

TEST_F(HttpCtrlChannelDhcpv6Test, controlLeasesReclaimRemove) {
    testControlLeasesReclaimRemove();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, controlLeasesReclaimRemove) {
    testControlLeasesReclaimRemove();
}

// Tests that the server properly responds to list-commands command sent
// via ControlChannel.
void
BaseCtrlChannelDhcpv6Test::testListCommands() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"list-commands\" }", response);

    ConstElementPtr rsp;
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));

    // We expect the server to report at least the following commands:
    checkListCommands(rsp, "build-report");
    checkListCommands(rsp, "config-backend-pull");
    checkListCommands(rsp, "config-get");
    checkListCommands(rsp, "config-hash-get");
    checkListCommands(rsp, "config-reload");
    checkListCommands(rsp, "config-set");
    checkListCommands(rsp, "config-test");
    checkListCommands(rsp, "config-write");
    checkListCommands(rsp, "list-commands");
    checkListCommands(rsp, "leases-reclaim");
    checkListCommands(rsp, "version-get");
    checkListCommands(rsp, "server-tag-get");
    checkListCommands(rsp, "shutdown");
    checkListCommands(rsp, "statistic-get");
    checkListCommands(rsp, "statistic-get-all");
    checkListCommands(rsp, "statistic-remove");
    checkListCommands(rsp, "statistic-remove-all");
    checkListCommands(rsp, "statistic-reset");
    checkListCommands(rsp, "statistic-reset-all");
    checkListCommands(rsp, "statistic-sample-age-set");
    checkListCommands(rsp, "statistic-sample-age-set-all");
    checkListCommands(rsp, "statistic-sample-count-set");
    checkListCommands(rsp, "statistic-sample-count-set-all");
}

TEST_F(HttpCtrlChannelDhcpv6Test, listCommands) {
    testListCommands();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, listCommands) {
    testListCommands();
}

// Tests if config-write can be called without any parameters.
void
BaseCtrlChannelDhcpv6Test::testConfigWriteNoFilename() {
    createHttpChannelServer();
    std::string response;

    // This is normally set by the command line -c parameter.
    server_->setConfigFile("test1.json");

    // If the filename is not explicitly specified, the name used
    // in -c command line switch is used.
    sendHttpCommand("{ \"command\": \"config-write\" }", response);

    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test1.json");
    ::remove("test1.json");
}

TEST_F(HttpCtrlChannelDhcpv6Test, configWriteNoFilename) {
    testConfigWriteNoFilename();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configWriteNoFilename) {
    testConfigWriteNoFilename();
}

// Tests if config-write can be called with a valid filename as parameter.
void
BaseCtrlChannelDhcpv6Test::testConfigWriteFilename() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"config-write\", "
                    "\"arguments\": { \"filename\": \"test2.json\" } }",
                    response);

    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test2.json");
    ::remove("test2.json");
}

TEST_F(HttpCtrlChannelDhcpv6Test, configWriteFilename) {
    testConfigWriteFilename();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configWriteFilename) {
    testConfigWriteFilename();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is missing.
void
BaseCtrlChannelDhcpv6Test::testConfigReloadMissingFile() {
    createHttpChannelServer();
    std::string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("test6.json");

    // Tell the server to reload its configuration. It should attempt to load
    // test6.json (and fail, because the file is not there).
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was rejected.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"Config reload failed: "
              "configuration error using file 'test6.json': "
              "Unable to open file test6.json\" } ]",
              response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, configReloadMissingFile) {
    testConfigReloadMissingFile();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configReloadMissingFile) {
    testConfigReloadMissingFile();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is not a valid JSON.
void
BaseCtrlChannelDhcpv6Test::testConfigReloadBrokenFile() {
    createHttpChannelServer();
    std::string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("test7.json");

    // Although Kea is smart, its AI routines are not smart enough to handle
    // this one... at least not yet.
    ofstream f("test7.json", ios::trunc);
    f << "gimme some addrs, bro!";
    f.close();

    // Now tell Kea to reload its config.
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload will fail.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"Config reload failed: "
              "configuration error using file 'test7.json': "
              "test7.json:1.1: Invalid character: g\" } ]",
              response);

    ::remove("test7.json");
}

TEST_F(HttpCtrlChannelDhcpv6Test, configReloadBrokenFile) {
    testConfigReloadBrokenFile();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configReloadBrokenFile) {
    testConfigReloadBrokenFile();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is loaded correctly.
void
BaseCtrlChannelDhcpv6Test::testConfigReloadValid() {
    createHttpChannelServer();
    std::string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("test8.json");

    // Ok, enough fooling around. Let's create a valid config.
    const std::string cfg_txt =
        "{ \"Dhcp6\": {"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"subnet6\": ["
        "        { \"subnet\": \"2001:db8:1::/64\", \"id\": 1 },"
        "        { \"subnet\": \"2001:db8:2::/64\", \"id\": 2 }"
        "     ],"
        "    \"lease-database\": {"
        "       \"type\": \"memfile\", \"persist\": false }"
        "} }";
    ofstream f("test8.json", ios::trunc);
    f << cfg_txt;
    f.close();

    // This command should reload test8.json config.
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"2D97C398AFE8414A818D9F04C9ADB62D493861EDD3689015D081880D6A85A3C3\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(2, subnets->size());

    ::remove("test8.json");
}

TEST_F(HttpCtrlChannelDhcpv6Test, configReloadValid) {
    testConfigReloadValid();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configReloadValid) {
    testConfigReloadValid();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is loaded correctly.
void
BaseCtrlChannelDhcpv6Test::testConfigReloadDetectInterfaces() {
    interfaces_ = "\"eth0\"";
    IfacePtr eth0 = IfaceMgrTestConfig::createIface("eth0", ETH0_INDEX,
                                                    "11:22:33:44:55:66");
    auto detectIfaces = [&](bool update_only) {
        if (!update_only) {
            eth0->addAddress(IOAddress("10.0.0.1"));
            eth0->addAddress(IOAddress("fe80::3a60:77ff:fed5:cdef"));
            eth0->addAddress(IOAddress("2001:db8:1::1"));
            IfaceMgr::instance().addInterface(eth0);
        }
        return (false);
    };
    IfaceMgr::instance().setDetectCallback(detectIfaces);
    IfaceMgr::instance().clearIfaces();
    IfaceMgr::instance().closeSockets();
    IfaceMgr::instance().detectIfaces();
    createHttpChannelServer();
    std::string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("test8.json");

    // Ok, enough fooling around. Let's create a valid config.
    const std::string cfg_txt =
        "{ \"Dhcp6\": {"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"eth1\" ]"
        "    },"
        "    \"subnet6\": ["
        "        { \"subnet\": \"2001:db8:1::/64\", \"id\": 1 },"
        "        { \"subnet\": \"2001:db8:2::/64\", \"id\": 2 }"
        "     ],"
        "    \"lease-database\": {"
        "       \"type\": \"memfile\", \"persist\": false }"
        "} }";
    ofstream f("test8.json", ios::trunc);
    f << cfg_txt;
    f.close();

    IfacePtr eth1 = IfaceMgrTestConfig::createIface("eth1", ETH1_INDEX,
                                                    "AA:BB:CC:DD:EE:FF");
    auto detectUpdateIfaces = [&](bool update_only) {
        if (!update_only) {
            eth1->addAddress(IOAddress("192.0.2.3"));
            eth1->addAddress(IOAddress("fe80::3a60:77ff:fed5:abcd"));
            eth1->addAddress(IOAddress("3001:db8:100::1"));
            IfaceMgr::instance().addInterface(eth1);
        }
        return (false);
    };
    IfaceMgr::instance().setDetectCallback(detectUpdateIfaces);

    // This command should reload test8.json config.
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"A3FB93A0D56418589F9368478403AA6164B94D907F3D7BA7FDF764AD58448611\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(2, subnets->size());

    ::remove("test8.json");
}

TEST_F(HttpCtrlChannelDhcpv6Test, configReloadDetectInterfaces) {
    testConfigReloadDetectInterfaces();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, configReloadDetectInterfaces) {
    testConfigReloadDetectInterfaces();
}

// This test verifies that disable DHCP service command performs
// sanity check on parameters.
void
BaseCtrlChannelDhcpv6Test::testDhcpDisableBadParam() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"max-period\": -3"
                    "    }"
                    "}", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"'max-period' must be positive "
              "integer\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": \"\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"'origin-id' argument must "
              "be a number\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": \"foo\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"'origin-id' argument must "
              "be a number\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"invalid value used for 'origin' "
              "parameter: (empty string)\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"test\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"invalid value used for 'origin' "
              "parameter: test\" } ]",
              response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpDisableBadParam) {
    testDhcpDisableBadParam();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpDisableBadParam) {
    testDhcpDisableBadParam();
}

// This test verifies if it is possible to disable DHCP service via command.
void
BaseCtrlChannelDhcpv6Test::testDhcpDisable() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"dhcp-disable\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    server_->network_state_->enableService(NetworkState::USER_COMMAND);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"user\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    server_->network_state_->enableService(NetworkState::USER_COMMAND);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"ha-partner\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    server_->network_state_->enableService(NetworkState::HA_REMOTE_COMMAND);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin\": 2001"
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    server_->network_state_->enableService(NetworkState::HA_REMOTE_COMMAND+1);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpDisable) {
    testDhcpDisable();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpDisable) {
    testDhcpDisable();
}

// This test verifies if it is possible to disable DHCP service using
// the origin-id.
void
BaseCtrlChannelDhcpv6Test::testDhcpDisableOriginId() {
    createHttpChannelServer();
    std::string response;

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": 2002,"
                    "        \"origin\": \"user\""
                    "    }"
                    "}", response);

    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    server_->network_state_->enableService(NetworkState::HA_REMOTE_COMMAND+2);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpDisableOriginId) {
    testDhcpDisableOriginId();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpDisableOriginId) {
    testDhcpDisableOriginId();
}

// This test verifies that it is possible to disable DHCP service for a short
// period of time, after which the service is automatically enabled.
void
BaseCtrlChannelDhcpv6Test::testDhcpDisableTemporarily() {
    createHttpChannelServer();
    std::string response;

    // Send a command to disable DHCP service for 3 seconds.
    sendHttpCommand("{"
                    "    \"command\": \"dhcp-disable\","
                    "    \"arguments\": {"
                    "        \"max-period\": 3"
                    "    }"
                    "}", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    // The service should be disabled.
    EXPECT_FALSE(server_->network_state_->isServiceEnabled());
    // And the timer should be scheduled which counts the time to automatic
    // enabling of the service.
    EXPECT_TRUE(server_->network_state_->isDelayedEnableService());
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpDisableTemporarily) {
    testDhcpDisableTemporarily();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpDisableTemporarily) {
    testDhcpDisableTemporarily();
}

// This test verifies that enable DHCP service command performs sanity check on
// parameters.
void
BaseCtrlChannelDhcpv6Test::testDhcpEnableBadParam() {
    createHttpChannelServer();
    std::string response;
    ConstElementPtr rsp;

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": \"\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"'origin-id' argument must "
              "be a number\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": \"foo\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"'origin-id' argument must "
              "be a number\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"invalid value used for 'origin' "
              "parameter: (empty string)\" } ]",
              response);

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"test\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    EXPECT_EQ("[ { \"result\": 1, \"text\": \"invalid value used for 'origin' "
              "parameter: test\" } ]",
              response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpEnableBadParam) {
    testDhcpEnableBadParam();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpEnableBadParam) {
    testDhcpEnableBadParam();
}

// This test verifies if it is possible to enable DHCP service via command.
void
BaseCtrlChannelDhcpv6Test::testDhcpEnable() {
    createHttpChannelServer();
    std::string response;

    sendHttpCommand("{ \"command\": \"dhcp-enable\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    server_->network_state_->disableService(NetworkState::USER_COMMAND);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"user\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    server_->network_state_->disableService(NetworkState::HA_REMOTE_COMMAND);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin\": \"ha-partner\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());

    server_->network_state_->disableService(NetworkState::HA_REMOTE_COMMAND+2);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin\": 2002"
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpEnable) {
    testDhcpEnable();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpEnable) {
    testDhcpEnable();
}

// This test verifies if it is possible to enable DHCP service using
// the origin-id.
void
BaseCtrlChannelDhcpv6Test::testDhcpEnableOriginId() {
    createHttpChannelServer();
    std::string response;

    ConstElementPtr rsp;

    int status;

    // Disable the service using two distinct origins.
    server_->network_state_->disableService(NetworkState::HA_REMOTE_COMMAND+1);
    server_->network_state_->disableService(NetworkState::USER_COMMAND);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    // Enable the service for the 'origin-id' of 2001. The 'origin' should
    // be ignored.
    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": 2001,"
                    "        \"origin\": \"user\""
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    ConstElementPtr cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    // The service should still be disabled.
    EXPECT_FALSE(server_->network_state_->isServiceEnabled());

    // Enable the service for the user command.
    sendHttpCommand("{"
                    "    \"command\": \"dhcp-enable\","
                    "    \"arguments\": {"
                    "        \"origin-id\": 1"
                    "    }"
                    "}", response);

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    cfg = parseListAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    // The service should be enabled.
    EXPECT_TRUE(server_->network_state_->isServiceEnabled());
}

TEST_F(HttpCtrlChannelDhcpv6Test, dhcpEnableOriginId) {
    testDhcpEnableOriginId();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, dhcpEnableOriginId) {
    testDhcpEnableOriginId();
}

/// Verify that concurrent connections over the HTTP control channel can be
/// established.
TEST_F(HttpCtrlChannelDhcpv6Test, concurrentConnections) {
    EXPECT_NO_THROW(createHttpChannelServer());

    const size_t NB = 5;
    vector<IOServicePtr> io_services;
    vector<TestHttpClientPtr> clients;

    // Create clients.
    for (size_t i = 0; i < NB; ++i) {
        IOServicePtr io_service(new IOService());
        io_services.push_back(io_service);
        TestHttpClientPtr client(new TestHttpClient(io_service, SERVER_ADDRESS,
                                                    SERVER_PORT));
        clients.push_back(client);
    }
    ASSERT_EQ(NB, io_services.size());
    ASSERT_EQ(NB, clients.size());

    // Send requests and receive responses.
    atomic<size_t> terminated;
    terminated = 0;
    vector<thread> threads;
    const string command = "{ \"command\": \"list-commands\" }";
    for (size_t i = 0; i < NB; ++i) {
        threads.push_back(thread([&, i] () {
            TestHttpClientPtr client = clients[i];
            ASSERT_TRUE(client);
            client->startRequest(buildPostStr(command));
            IOServicePtr io_service = io_services[i];
            ASSERT_TRUE(io_service);
            io_service->run();
            ASSERT_TRUE(client->receiveDone());
            HttpResponsePtr hr;
            ASSERT_NO_THROW(hr = parseResponse(client->getResponse()));
            string response = hr->getBody();
            EXPECT_TRUE(response.find("\"result\": 0") != std::string::npos);
            client->close();
            ++terminated;
        }));
    }
    ASSERT_EQ(NB, threads.size());

    // Run the service IO services with a timeout.
    IntervalTimer test_timer(getIOService());
    bool timeout = false;
    test_timer.setup([&timeout] () { timeout = true; },
                     TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    while (!timeout && (terminated < NB)) {
        getIOService()->poll();
    }
    test_timer.cancel();
    EXPECT_FALSE(timeout);

    // Cleanup clients.
    for (IOServicePtr io_service : io_services) {
        io_service->stopAndPoll();
    }
    for (auto th = threads.begin(); th != threads.end(); ++th) {
        th->join();
    }
}

/// Verify that concurrent connections over the HTTPS control channel can be
/// established.
TEST_F(HttpsCtrlChannelDhcpv6Test, concurrentConnections) {
    EXPECT_NO_THROW(createHttpChannelServer());

    const size_t NB = 5;
    vector<IOServicePtr> io_services;
    vector<TestHttpsClientPtr> clients;
    vector<TlsContextPtr> tls_contexts;

    // Create clients.
    for (size_t i = 0; i < NB; ++i) {
        IOServicePtr io_service(new IOService());
        io_services.push_back(io_service);
        TlsContextPtr tls_context;
        configClient(tls_context);
        tls_contexts.push_back(tls_context);
        TestHttpsClientPtr client(new TestHttpsClient(io_service,
                                                      tls_context,
                                                      SERVER_ADDRESS,
                                                      SERVER_PORT));
        clients.push_back(client);
    }
    ASSERT_EQ(NB, io_services.size());
    ASSERT_EQ(NB, clients.size());

    // Send requests and receive responses.
    atomic<size_t> terminated;
    terminated = 0;
    vector<thread> threads;
    const string command = "{ \"command\": \"list-commands\" }";
    for (size_t i = 0; i < NB; ++i) {
        threads.push_back(thread([&, i] () {
            TestHttpsClientPtr client = clients[i];
            ASSERT_TRUE(client);
            client->startRequest(buildPostStr(command));
            IOServicePtr io_service = io_services[i];
            ASSERT_TRUE(io_service);
            io_service->run();
            ASSERT_TRUE(client->receiveDone());
            HttpResponsePtr hr;
            ASSERT_NO_THROW(hr = parseResponse(client->getResponse()));
            string response = hr->getBody();
            EXPECT_TRUE(response.find("\"result\": 0") != std::string::npos);
            client->close();
            ++terminated;
        }));
    }
    ASSERT_EQ(NB, threads.size());

    // Run the service IO services with a timeout.
    IntervalTimer test_timer(getIOService());
    bool timeout = false;
    test_timer.setup([&timeout] () { timeout = true; },
                     TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    while (!timeout && (terminated < NB)) {
        getIOService()->poll();
    }
    test_timer.cancel();
    EXPECT_FALSE(timeout);

    // Cleanup clients.
    for (IOServicePtr io_service : io_services) {
        io_service->stopAndPoll();
    }
    for (auto th = threads.begin(); th != threads.end(); ++th) {
        th->join();
    }
}

// This test verifies that the server can receive and process a large command.
void
BaseCtrlChannelDhcpv6Test::testLongCommand() {

    ostringstream command;

    // This is the desired size of the command sent to the server (1MB).
    // The actual size sent will be slightly greater than that.
    const size_t command_size = 1024 * 1000;

    while (command.tellp() < command_size) {

        // We're sending command 'foo' with arguments being a list of
        // strings. If this is the first transmission, send command name
        // and open the arguments list. Also insert the first argument
        // so as all subsequent arguments can be prefixed with a comma.
        if (command.tellp() == 0) {
            command << "{ \"command\": \"foo\", \"arguments\": [ \"begin\"";

        } else {
            // Generate a random number and insert it into the stream as
            // 10 digits long string.
            ostringstream arg;
            arg << setw(10) << std::rand();
            // Append the argument in the command.
            command << ", \"" << arg.str() << "\"\n";

            // If we have hit the limit of the command size, close braces to
            // get appropriate JSON.
            if (command.tellp() > command_size) {
                command << "] }";
            }
        }
    }

    ASSERT_NO_THROW(
        CommandMgr::instance().registerCommand("foo",
            std::bind(&HttpCtrlChannelDhcpv6Test::longCommandHandler,
                      command.str(), ph::_1, ph::_2));
    );

    createHttpChannelServer();

    string response;
    ASSERT_NO_THROW(sendHttpCommand(command.str(), response));

    EXPECT_EQ("[ { \"result\": 0, \"text\": \"long command received ok\" } ]",
              response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, longCommand) {
    testLongCommand();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, longCommand) {
    testLongCommand();
}

// This test verifies that the server can send long response to the client.
void
BaseCtrlChannelDhcpv6Test::testLongResponse() {
    // We need to generate large response. The simplest way is to create
    // a command and a handler which will generate some static response
    // of a desired size.
    ASSERT_NO_THROW(
        CommandMgr::instance().registerCommand("foo",
            std::bind(&HttpCtrlChannelDhcpv6Test::longResponseHandler,
                      ph::_1, ph::_2));
    );

    createHttpChannelServer();

    // The entire response should be received but anyway check it.
    ConstElementPtr raw_response =
        longResponseHandler("foo", ConstElementPtr());
    ElementPtr json_response = Element::createList();
    json_response->add(isc::data::copy(raw_response));
    string reference_response = json_response->str();

    string response;
    string command = "{ \"command\": \"foo\", \"arguments\": { }  }";
    ASSERT_NO_THROW(sendHttpCommand(command, response));

    // Make sure we have received correct response.
    EXPECT_EQ(reference_response, response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, longResponse) {
    testLongResponse();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, longResponse) {
    testLongResponse();
}

// Verify that the dual stack scenario works as expect.
TEST_F(HttpCtrlChannelDhcpv6Test, dualStack) {
    std::string header =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [";

    std::string body = "]"
        "    },"
        "    \"expired-leases-processing\": {"
        "         \"reclaim-timer-wait-time\": 60,"
        "         \"hold-reclaimed-time\": 500,"
        "         \"flush-reclaimed-timer-wait-time\": 60"
        "    },"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"subnet6\": [ ],"
        "    \"valid-lifetime\": 4000,"
        "    \"control-sockets\": [ {"
        "        \"socket-type\": \"http\","
        "        \"socket-address\": \"::1\","
        "        \"socket-port\": 18126"
        "    },{"
        "        \"socket-type\": \"http\","
        "        \"socket-address\": \"127.0.0.1\","
        "        \"socket-port\": 18126"
        "    } ],"
        "    \"lease-database\": {"
        "       \"type\": \"memfile\", \"persist\": false },"
        "    \"loggers\": [ {"
        "       \"name\": \"kea-dhcp6\","
        "       \"severity\": \"INFO\","
        "       \"debuglevel\": 0"
        "       } ]"
        "}";

    std::string config_txt = header + interfaces_ + body;

    createHttpChannelServer(config_txt);

    std::string response;

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response, "127.0.0.1");
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Verify that the dual stack scenario works as expect.
TEST_F(HttpsCtrlChannelDhcpv6Test, dualStack) {
    string ca_dir(string(TEST_CA_DIR));
    ostringstream config_st;
    config_st
        << "{"
        << "    \"interfaces-config\": {"
        << "        \"interfaces\": ["
        << interfaces_
        << "]"
        << "    },"
        << "    \"expired-leases-processing\": {"
        << "         \"reclaim-timer-wait-time\": 60,"
        << "         \"hold-reclaimed-time\": 500,"
        << "         \"flush-reclaimed-timer-wait-time\": 60"
        << "    },"
        << "    \"rebind-timer\": 2000, "
        << "    \"renew-timer\": 1000, "
        << "    \"subnet6\": [ ],"
        << "    \"valid-lifetime\": 4000,"
        << "    \"control-sockets\": [ {"
        << "        \"socket-type\": \"http\","
        << "        \"socket-address\": \"::1\","
        << "        \"socket-port\": 18126,"
        << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\","
        << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\","
        << "        \"key-file\": \"" << ca_dir << "/kea-server.key\""
        << "    },{"
        << "        \"socket-type\": \"http\","
        << "        \"socket-address\": \"127.0.0.1\","
        << "        \"socket-port\": 18126,"
        << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\","
        << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\","
        << "        \"key-file\": \"" << ca_dir << "/kea-server.key\""
        << "    } ],"
        << "    \"lease-database\": {"
        << "       \"type\": \"memfile\", \"persist\": false },"
        << "    \"loggers\": [ {"
        << "       \"name\": \"kea-dhcp6\","
        << "       \"severity\": \"INFO\","
        << "       \"debuglevel\": 0"
        << "       } ]"
        << "}";

    createHttpChannelServer(config_st.str());

    std::string response;

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response, "127.0.0.1");
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// This test verifies that the server signals timeout if the transmission
// takes too long, having received no data from the client.
void
BaseCtrlChannelDhcpv6Test::testConnectionTimeoutNoData() {
    // Set connection timeout to 2s to prevent long waiting time for the
    // timeout during this test.
    const unsigned short timeout = 2000;
    HttpCommandMgr::instance().setConnectionTimeout(timeout);

    createHttpChannelServer();

    string response;
    ASSERT_NO_THROW(sendHttpCommand("{ \"command\": ", response));

    EXPECT_EQ("{ \"result\": 400, \"text\": \"Bad Request\" }", response);
}

TEST_F(HttpCtrlChannelDhcpv6Test, connectionTimeoutNoData) {
    testConnectionTimeoutNoData();
}

TEST_F(HttpsCtrlChannelDhcpv6Test, connectionTimeoutNoData) {
    testConnectionTimeoutNoData();
}

// Verify that the "config-set" command will reuse listener
TEST_F(HttpCtrlChannelDhcpv6Test, noListenerChange) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string option_def =
        "    ,\"option-def\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"type\": \"uint32\",\n"
        "        \"array\": false,\n"
        "        \"record-types\": \"\",\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket =
        "    ,\"control-socket\": { \n"
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126 \n"
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << option_def
       << option_data
       << control_socket
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"BCE3D0CC68CBBB49C3F5967E3FFCB4E44E55CBFB53814761B12ADB5C7CD95C1F\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def =
        LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Verify the HTTP control channel socket exists.
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    // Send the config-set command.
    sendHttpCommand(os.str(), response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"BCE3D0CC68CBBB49C3F5967E3FFCB4E44E55CBFB53814761B12ADB5C7CD95C1F\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Verify that the "config-set" command will reuse listener
TEST_F(HttpsCtrlChannelDhcpv6Test, noListenerChange) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string ca_dir(string(TEST_CA_DIR));
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string option_def =
        "    ,\"option-def\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"type\": \"uint32\",\n"
        "        \"array\": false,\n"
        "        \"record-types\": \"\",\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket_header =
        "    ,\"control-socket\": { \n";
    string control_socket_footer =
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126 \n"
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << option_def
       << option_data
       << control_socket_header
       << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
       << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
       << "        \"key-file\": \"" << ca_dir << "/kea-server.key\", \n"
       << control_socket_footer
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration successful." is there
    EXPECT_NE(response.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Configuration successful.\""),
              std::string::npos);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def =
        LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Verify the HTTP control channel socket exists.
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    auto const context = HttpCommandMgr::instance().getHttpListener()->getTlsContext().get();

    // Send the config-set command.
    sendHttpCommand(os.str(), response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    // The TLS settings have been applied
    EXPECT_NE(context, HttpCommandMgr::instance().getHttpListener()->getTlsContext().get());

    EXPECT_NE(response.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Configuration successful.\""),
              std::string::npos);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Verify that the "config-set" command will exit with an error
TEST_F(HttpCtrlChannelDhcpv6Test, handleHttpToHttpsSwitch) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string ca_dir(string(TEST_CA_DIR));
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string option_def =
        "    ,\"option-def\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"type\": \"uint32\",\n"
        "        \"array\": false,\n"
        "        \"record-types\": \"\",\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket_header =
        "    ,\"control-socket\": { \n";
    string control_socket_footer =
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126 \n"
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << option_def
       << option_data
       << control_socket_header
       << control_socket_footer
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"BCE3D0CC68CBBB49C3F5967E3FFCB4E44E55CBFB53814761B12ADB5C7CD95C1F\" }, \"result\": 0, \"text\": \"Configuration successful.\" } ]",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def =
        LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Verify the HTTP control channel socket exists.
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    std::ostringstream second_config_os;

    // Create a valid config with all the parts should parse
    second_config_os << config_set_txt << ","
        << args_txt
        << dhcp6_cfg_txt
        << subnet1
        << subnet_footer
        << option_def
        << option_data
        << control_socket_header
        << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
        << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
        << "        \"key-file\": \"" << ca_dir << "/kea-server.key\", \n"
        << control_socket_footer
        << logger_txt
        << "}\n"                      // close dhcp6
        << "}}";

    // Send the config-set command.
    sendHttpCommand(second_config_os.str(), response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    EXPECT_NE(response.find("\"result\": 1"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Can not switch from HTTP to HTTPS sockets using the same address and port.\""),
              std::string::npos);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Verify that the "config-set" command will exit with an error
TEST_F(HttpsCtrlChannelDhcpv6Test, handleHttpsToHttpSwitch) {
    createHttpChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string ca_dir(string(TEST_CA_DIR));
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp6_cfg_txt =
        "    \"Dhcp6\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
        "        \"preferred-lifetime\": 3000, \n"
        "        \"valid-lifetime\": 4000, \n"
        "        \"renew-timer\": 1000, \n"
        "        \"rebind-timer\": 2000, \n"
        "        \"lease-database\": { \n"
        "           \"type\": \"memfile\", \n"
        "           \"persist\":false, \n"
        "           \"lfc-interval\": 0  \n"
        "        }, \n"
        "        \"expired-leases-processing\": { \n"
        "            \"reclaim-timer-wait-time\": 0, \n"
        "            \"hold-reclaimed-time\": 0, \n"
        "            \"flush-reclaimed-timer-wait-time\": 0 \n"
        "        },"
        "        \"subnet6\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"3002::/64\", \"id\": 1, \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string option_def =
        "    ,\"option-def\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"type\": \"uint32\",\n"
        "        \"array\": false,\n"
        "        \"record-types\": \"\",\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp6\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket_header =
        "    ,\"control-socket\": { \n";
    string control_socket_footer =
        "       \"socket-type\": \"http\", \n"
        "       \"socket-address\": \"::1\", \n"
        "       \"socket-port\": 18126 \n"
        "    } \n";
    string logger_txt =
        "       ,\"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output-options\": [{ \n"
        "                \"output\": \"/dev/null\", \n"
        "                \"maxsize\": 0"
        "            }] \n"
        "        }] \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << config_set_txt << ","
       << args_txt
       << dhcp6_cfg_txt
       << subnet1
       << subnet_footer
       << option_def
       << option_data
       << control_socket_header
       << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
       << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
       << "        \"key-file\": \"" << ca_dir << "/kea-server.key\", \n"
       << control_socket_footer
       << logger_txt
       << "}\n"                      // close dhcp6
       << "}}";

    // Send the config-set command
    std::string response;
    sendHttpCommand(os.str(), response);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration successful." is there
    EXPECT_NE(response.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Configuration successful.\""),
              std::string::npos);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def =
        LibDHCP::getRuntimeOptionDef(DHCP6_OPTION_SPACE, 163);
    ASSERT_TRUE(def);

    // Verify the HTTP control channel socket exists.
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    // The TLS settings have not changed
    auto const context = HttpCommandMgr::instance().getHttpListener()->getTlsContext().get();

    std::ostringstream second_config_os;

    // Create a valid config with all the parts should parse
    second_config_os << config_set_txt << ","
        << args_txt
        << dhcp6_cfg_txt
        << subnet1
        << subnet_footer
        << option_def
        << option_data
        << control_socket_header
        << control_socket_footer
        << logger_txt
        << "}\n"                      // close dhcp6
        << "}}";

    // Send the config-set command.
    sendHttpCommand(second_config_os.str(), response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    EXPECT_EQ(context, HttpCommandMgr::instance().getHttpListener()->getTlsContext().get());

    EXPECT_NE(response.find("\"result\": 1"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Can not switch from HTTPS to HTTP sockets using the same address and port.\""),
              std::string::npos);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

} // End of anonymous namespace
