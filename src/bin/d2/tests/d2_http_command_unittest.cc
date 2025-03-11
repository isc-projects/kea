// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/testutils/test_tls.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/http_command_mgr.h>
#include <config/timeouts.h>
#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2/parser_context.h>
#include <http/response.h>
#include <http/response_parser.h>
#include <http/testutils/test_http_client.h>
#include <gtest/gtest.h>
#include <boost/pointer_cast.hpp>
#include <atomic>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::http;
using namespace isc::process;
namespace ph = std::placeholders;

namespace isc {
namespace d2 {

// "Naked" D2 controller, exposes internal methods.
class NakedD2Controller;
typedef boost::shared_ptr<NakedD2Controller> NakedD2ControllerPtr;

class NakedD2Controller : public D2Controller {
public:
    static DControllerBasePtr& instance() {
        static DControllerBasePtr controller_ptr;
        if (!controller_ptr) {
            controller_ptr.reset(new NakedD2Controller());
        }

        return (controller_ptr);
    }

    virtual ~NakedD2Controller() {
        deregisterCommands();
    }

    using DControllerBase::getIOService;
    using DControllerBase::initProcess;

    D2ProcessPtr getProcess() {
        return (boost::dynamic_pointer_cast<D2Process>(DControllerBase::getProcess()));
    }

private:
    NakedD2Controller() { }
};

} // namespace isc::d2
} // namespace isc

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18125;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Base fixture class intended for testing HTTP/HTTPS control channel
/// in D2.
class BaseCtrlChannelD2Test : public ::testing::Test {
public:
    /// @brief Reference to the base controller object.
    DControllerBasePtr& server_;

    /// @brief Cast controller object.
    NakedD2Controller* d2Controller() {
        return (dynamic_cast<NakedD2Controller*>(server_.get()));
    }

    /// @brief Configuration file.
    static const char* CFG_TEST_FILE;

    /// @brief Default constructor.
    ///
    /// Sets socket path to its default value.
    BaseCtrlChannelD2Test()
        : server_(NakedD2Controller::instance()) {
    }

    /// @brief Destructor.
    virtual ~BaseCtrlChannelD2Test() {
        // Deregister & co.
        server_.reset();

        // Remove files.
        ::remove(CFG_TEST_FILE);

        // Reset command manager.
        CommandMgr::instance().deregisterAll();
        HttpCommandMgr::instance().setConnectionTimeout(TIMEOUT_AGENT_RECEIVE_COMMAND);
    }

    /// @brief Returns pointer to the server's IO service.
    ///
    /// @return Pointer to the server's IO service or null pointer if the
    /// server hasn't been created.
    IOServicePtr getIOService() {
        return (server_ ? d2Controller()->getIOService() : IOServicePtr());
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
        test_timer.setup(std::bind(&BaseCtrlChannelD2Test::timeoutHandler,
                                   this, true),
                         TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
        // Run until the client stops the service or an error occurs.
        io_service->run();
        test_timer.cancel();
        if (io_service->stopped()) {
            io_service->restart();
        }
        io_service->poll();
    }

    /// @brief Runs parser in DHCPDDNS mode
    ///
    /// @param config input configuration
    /// @param verbose display errors
    /// @return element pointer representing the configuration
    ElementPtr parseDHCPDDNS(const string& config, bool verbose = false) {
        try {
            D2ParserContext ctx;
            return (ctx.parseString(config,
                                    D2ParserContext::PARSER_SUB_DHCPDDNS));
        } catch (const std::exception& ex) {
            if (verbose) {
                cout << "EXCEPTION: " << ex.what() << endl;
            }
            throw;
        }
    }

    /// @brief Create a server with a HTTP command channel.
    virtual void createHttpChannelServer() = 0;

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
    virtual void sendHttpCommand(const string& command,
                                 string& response,
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
    void checkListCommands(const ConstElementPtr& rsp, const string command) {
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
    /// the control socket).
    /// @param exp_status expected status (0 success, 1 failure).
    /// @param exp_txt for success cases this defines the expected filename,
    /// for failure cases this defines the expected error message.
    void checkConfigWrite(const string& response_txt, int exp_status,
                          const string& exp_txt = "") {

        ConstElementPtr rsp;
        EXPECT_NO_THROW(rsp = Element::fromJSON(response_txt));
        ASSERT_TRUE(rsp);

        int status;
        ConstElementPtr params = parseListAnswer(status, rsp);
        EXPECT_EQ(exp_status, status);

        if (exp_status == CONTROL_RESULT_SUCCESS) {
            // Let's check couple things...

            // The parameters must include filename.
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
    longCommandHandler(const string& expected_command,
                       const string& command_name,
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

    /// @brief Command handler which generates long response.
    ///
    /// This handler generates a large response (over 400kB). It includes
    /// a list of randomly generated strings to make sure that the test
    /// can catch out of order delivery.
    static ConstElementPtr
    longResponseHandler(const string&, const ConstElementPtr&) {
        ElementPtr arguments = Element::createList();
        for (unsigned i = 0; i < 80000; ++i) {
            std::ostringstream s;
            s << std::setw(5) << i;
            arguments->add(Element::create(s.str()));
        }
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    // Tests that the server properly responds to invalid commands.
    void testInvalid();

    // Tests that the server properly responds to shutdown command.
    void testShutdown();

    // Tests that the server sets exit value supplied as argument
    // to shutdown command.
    void testShutdownExitValue();

    // This test verifies that the D2 server handles version-get commands.
    void testGetVersion();

    // Tests that the server properly responds to list-commands command.
    void testListCommands();

    // This test verifies that the D2 server handles status-get commands.
    void testStatusGet();

    // Tests if the server returns its configuration using config-get.
    void testConfigGet();

    // Tests if the server returns the hash of its configuration using
    // config-hash-get.
    void testConfigHashGet();

    // Tests if config-write can be called without any parameters.
    void testWriteConfigNoFilename();

    // Tests if config-write can be called with a valid filename as parameter.
    void testWriteConfigFilename();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is missing.
    void testConfigReloadMissingFile();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is not a valid JSON.
    void testConfigReloadBrokenFile();

    // Tests if config-reload attempts to reload a file and reports that the
    // file is loaded correctly.
    void testConfigReloadFileValid();

    // This test verifies that the server can receive and process a
    // large command.
    void testLongCommand();

    // This test verifies that the server can send long response to the client.
    void testLongResponse();

    // This test verifies that the server signals timeout if the transmission
    // takes too long, having received no data from the client.
    void testConnectionTimeoutNoData();
};

const char* BaseCtrlChannelD2Test::CFG_TEST_FILE = "d2-http-test-config.json";

/// @brief Fixture class intended for testing HTTP control channel in D2.
class HttpCtrlChannelD2Test : public BaseCtrlChannelD2Test {
public:

    /// @brief Create a server with a HTTP command channel.
    virtual void createHttpChannelServer() override {
        // Just a simple config. The important part here is the socket
        // location information.
        string config_txt =
            "{"
            "    \"ip-address\": \"192.168.77.1\","
            "    \"port\": 777,"
            "    \"control-socket\": {"
            "        \"socket-type\": \"http\","
            "        \"socket-address\": \"127.0.0.1\","
            "        \"socket-port\": 18125"
            "    },"
            "    \"tsig-keys\": [],"
            "    \"forward-ddns\" : {},"
            "    \"reverse-ddns\" : {}"
            "}";

        ASSERT_TRUE(server_);

        ConstElementPtr config;
        ASSERT_NO_THROW(config = parseDHCPDDNS(config_txt, true));
        ASSERT_NO_THROW(d2Controller()->initProcess());
        D2ProcessPtr proc = d2Controller()->getProcess();
        ASSERT_TRUE(proc);
        ConstElementPtr answer = proc->configure(config, false);
        ASSERT_TRUE(answer);
        ASSERT_NO_THROW(d2Controller()->registerCommands());

        int status = 0;
        ConstElementPtr txt = parseAnswer(status, answer);
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
    virtual void sendHttpCommand(const string& command,
                                 string& response,
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

        // Send the command. This will trigger server's handler which
        // receives data over the HTTP socket. The server will start
        // sending response to the client.
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

/// @brief Fixture class intended for testing HTTPS control channel in D2.
class HttpsCtrlChannelD2Test : public BaseCtrlChannelD2Test {
public:

    /// @brief Create a server with a HTTP command channel.
    virtual void createHttpChannelServer() override {
        // Just a simple config. The important part here is the socket
        // location information.
        string ca_dir(string(TEST_CA_DIR));
        ostringstream cf_st;
        cf_st << "{"
              << "    \"ip-address\": \"192.168.77.1\","
              << "    \"port\": 777,"
              << "    \"control-socket\": {"
              << "        \"socket-type\": \"https\","
              << "        \"socket-address\": \"127.0.0.1\","
              << "        \"socket-port\": 18125,"
              << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\","
              << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\","
              << "        \"key-file\": \"" << ca_dir << "/kea-server.key\""
              << "    },"
              << "    \"tsig-keys\": [],"
              << "    \"forward-ddns\" : {},"
              << "    \"reverse-ddns\" : {}"
              << "}";

        ASSERT_TRUE(server_);

        ConstElementPtr config;
        ASSERT_NO_THROW(config = parseDHCPDDNS(cf_st.str(), true));
        ASSERT_NO_THROW(d2Controller()->initProcess());
        D2ProcessPtr proc = d2Controller()->getProcess();
        ASSERT_TRUE(proc);
        ConstElementPtr answer = proc->configure(config, false);
        ASSERT_TRUE(answer);
        ASSERT_NO_THROW(d2Controller()->registerCommands());

        int status = 0;
        ConstElementPtr txt = parseAnswer(status, answer);
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
    virtual void sendHttpCommand(const string& command,
                                 string& response,
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

        // Send the command. This will trigger server's handler which
        // receives data over the HTTP socket. The server will start
        // sending response to the client.
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

// Tests that the server properly responds to invalid commands.
void
BaseCtrlChannelD2Test::testInvalid() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    sendHttpCommand("{ \"command\": \"bogus\" }", response);
    EXPECT_EQ("[ { \"result\": 2, \"text\": \"'bogus' command not supported.\" } ]",
              response);

    sendHttpCommand("utter nonsense", response);
    EXPECT_EQ("{ \"result\": 400, \"text\": \"Bad Request\" }", response);
}

TEST_F(HttpCtrlChannelD2Test, invalid) {
    testInvalid();
}

TEST_F(HttpsCtrlChannelD2Test, invalid) {
    testInvalid();
}

// Tests that the server properly responds to shutdown command.
void
BaseCtrlChannelD2Test::testShutdown() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    sendHttpCommand("{ \"command\": \"shutdown\" }", response);
    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Shutdown initiated, type is: normal\" } ]",
              response);
    EXPECT_EQ(EXIT_SUCCESS, server_->getExitValue());
}

TEST_F(HttpCtrlChannelD2Test, shutdown) {
    testShutdown();
}

TEST_F(HttpsCtrlChannelD2Test, shutdown) {
    testShutdown();
}

// Tests that the server sets exit value supplied as argument
// to shutdown command.
void
BaseCtrlChannelD2Test::testShutdownExitValue() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    sendHttpCommand("{ \"command\": \"shutdown\", "
                    "\"arguments\": { \"exit-value\": 77 }}",
                    response);

    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Shutdown initiated, type is: normal\" } ]",
              response);

    EXPECT_EQ(77, server_->getExitValue());
}

TEST_F(HttpCtrlChannelD2Test, shutdownExitValue) {
    testShutdownExitValue();
}

TEST_F(HttpsCtrlChannelD2Test, shutdownExitValue) {
    testShutdownExitValue();
}

// This test verifies that the D2 server handles version-get commands.
void
BaseCtrlChannelD2Test::testGetVersion() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    // Send the version-get command.
    sendHttpCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("Hooks directory: ") != string::npos);

    // Send the build-report command.
    sendHttpCommand("{ \"command\": \"build-report\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("Hooks directory: ") != string::npos);
}

TEST_F(HttpCtrlChannelD2Test, getVersion) {
    testGetVersion();
}

TEST_F(HttpsCtrlChannelD2Test, getVersion) {
    testGetVersion();
}

// Tests that the server properly responds to list-commands command.
void
BaseCtrlChannelD2Test::testListCommands() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    sendHttpCommand("{ \"command\": \"list-commands\" }", response);

    ConstElementPtr rsp;
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));

    // We expect the server to report at least the following commands:
    checkListCommands(rsp, "build-report");
    checkListCommands(rsp, "config-get");
    checkListCommands(rsp, "config-hash-get");
    checkListCommands(rsp, "config-reload");
    checkListCommands(rsp, "config-set");
    checkListCommands(rsp, "config-test");
    checkListCommands(rsp, "config-write");
    checkListCommands(rsp, "list-commands");
    checkListCommands(rsp, "statistic-get");
    checkListCommands(rsp, "statistic-get-all");
    checkListCommands(rsp, "statistic-reset");
    checkListCommands(rsp, "statistic-reset-all");
    checkListCommands(rsp, "status-get");
    checkListCommands(rsp, "shutdown");
    checkListCommands(rsp, "version-get");
}

TEST_F(HttpCtrlChannelD2Test, listCommands) {
    testListCommands();
}

TEST_F(HttpsCtrlChannelD2Test, listCommands) {
    testListCommands();
}

// This test verifies that the D2 server handles status-get commands.
void
BaseCtrlChannelD2Test::testStatusGet() {
    EXPECT_NO_THROW(createHttpChannelServer());

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

    // It is hard to check the actual reload time as it is based
    // on current time. Let's just make sure it is within a reasonable
    // range.
    auto found_reload = arguments->get("reload");
    ASSERT_TRUE(found_reload);
    EXPECT_LE(found_reload->intValue(), 5);
    EXPECT_GE(found_reload->intValue(), 0);

    /// @todo uptime is not available in this test, because the launch()
    /// function is not called. This is not critical to test here,
    /// because the same logic is tested for CA and in that case the
    /// uptime is tested.
}

TEST_F(HttpCtrlChannelD2Test, statusGet) {
    testStatusGet();
}

TEST_F(HttpsCtrlChannelD2Test, statusGet) {
    testStatusGet();
}

// Tests if the server returns its configuration using config-get.
// Note there are separate tests that verify if toElement() called by the
// config-get handler are actually converting the configuration correctly.
void
BaseCtrlChannelD2Test::testConfigGet() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

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
    EXPECT_TRUE(cfg->get("DhcpDdns"));
}

TEST_F(HttpCtrlChannelD2Test, configGet) {
    testConfigGet();
}

TEST_F(HttpsCtrlChannelD2Test, configGet) {
    testConfigGet();
}

// Tests if the server returns the hash of its configuration using
// config-hash-get.
void
BaseCtrlChannelD2Test::testConfigHashGet() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

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
    ASSERT_NO_THROW(args = rsp->get(0)->get(CONTROL_ARGUMENTS));

    // Ok, now roughly check if the response seems legit.
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());
    ConstElementPtr hash = args->get("hash");
    ASSERT_TRUE(hash);
    ASSERT_EQ(Element::string, hash->getType());
    // SHA-256 -> 64 hex digits.
    EXPECT_EQ(64, hash->stringValue().size());
}

TEST_F(HttpCtrlChannelD2Test, configHashGet) {
    testConfigHashGet();
}

TEST_F(HttpsCtrlChannelD2Test, configHashGet) {
    testConfigHashGet();
}

// Verify that the "config-test" command will do what we expect.
TEST_F(HttpCtrlChannelD2Test, configTest) {

    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_cfg_txt, true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": { \"hash\": \"029AE1208415D6911B5651A6F82D054F55B7877D2589CFD1DCEB5BFFCD3B13A3\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
              answer->str());
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Create a config with invalid content that should fail to parse.
    string config_test_txt =
        "{ \"command\": \"config-test\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"BOGUS\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n"
        "}} \n";

    // Send the config-test command.
    string response;
    sendHttpCommand(config_test_txt, response);

    // Should fail with a syntax error.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"missing parameter 'name' (<string>:10:14)\" } ]",
              response);

    // Check that the config was not lost (fix: reacquire the context).
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    // Create a valid config with two keys and no command channel.
    config_test_txt =
        "{ \"command\": \"config-test\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"}, \n"
        "           {\"name\": \"d2_key.billcat.net\", \n"
        "            \"algorithm\": \"hmac-md5\", \n"
        "            \"digest-bits\": 120, \n"
        "            \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ] \n"
        "    } \n"
        "}} \n";

    // Send the config-test command.
    sendHttpCommand(config_test_txt, response);

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Configuration check successful\" } ]",
              response);

    // Check that the config was not applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

// Verify that the "config-test" command will do what we expect.
TEST_F(HttpsCtrlChannelD2Test, configTest) {

    string ca_dir(string(TEST_CA_DIR));
    ostringstream d2_st;
    d2_st << "    { \n"
          << "        \"ip-address\": \"192.168.77.1\", \n"
          << "        \"port\": 777, \n"
          << "        \"forward-ddns\" : {}, \n"
          << "        \"reverse-ddns\" : {}, \n"
          << "        \"tsig-keys\": [ \n"
          << "            {\"name\": \"d2_key.example.com\", \n"
          << "             \"algorithm\": \"hmac-md5\", \n"
          << "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
          << "          ], \n"
          << "        \"control-socket\": { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"127.0.0.1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        } \n"
          << "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_st.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration applied successfully." is there
    string answer_txt = answer->str();
    EXPECT_NE(answer_txt.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(answer_txt.find("\"text\": \"Configuration applied successfully.\""),
              std::string::npos);
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Create a config with invalid content that should fail to parse.
    string config_test_txt =
        "{ \"command\": \"config-test\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"BOGUS\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n"
        "}} \n";

    // Send the config-test command.
    string response;
    sendHttpCommand(config_test_txt, response);

    // Should fail with a syntax error.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"missing parameter 'name' (<string>:10:14)\" } ]",
              response);

    // Check that the config was not lost (fix: reacquire the context).
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    // Create a valid config with two keys and no command channel.
    config_test_txt =
        "{ \"command\": \"config-test\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"}, \n"
        "           {\"name\": \"d2_key.billcat.net\", \n"
        "            \"algorithm\": \"hmac-md5\", \n"
        "            \"digest-bits\": 120, \n"
        "            \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ] \n"
        "    } \n"
        "}} \n";

    // Send the config-test command.
    sendHttpCommand(config_test_txt, response);

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"result\": 0, \"text\": \"Configuration check successful\" } ]",
              response);

    // Check that the config was not applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

// Verify that the "config-set" command will do what we expect.
TEST_F(HttpCtrlChannelD2Test, configSet) {

    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_cfg_txt, true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": { \"hash\": \"029AE1208415D6911B5651A6F82D054F55B7877D2589CFD1DCEB5BFFCD3B13A3\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
              answer->str());
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Create a config with invalid content that should fail to parse.
    string config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"BOGUS\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n"
        "}} \n";

    // Send the config-set command.
    string response;
    sendHttpCommand(config_set_txt, response);

    // Should fail with a syntax error.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"missing parameter 'name' (<string>:10:14)\" } ]",
              response);

    // Check that the config was not lost (fix: reacquire the context).
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    // Create a valid config with two keys and no command channel.
    config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"}, \n"
        "           {\"name\": \"d2_key.billcat.net\", \n"
        "            \"algorithm\": \"hmac-md5\", \n"
        "            \"digest-bits\": 120, \n"
        "            \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ] \n"
        "    } \n"
        "}} \n";

    // Verify the HTTP control channel socket exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Send the config-set command.
    sendHttpCommand(config_set_txt, response);

    // Verify the HTTP control channel socket no longer exists.
    ASSERT_NO_THROW(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"5206A1BEC7E3C6ADD5E97C5983861F97739EA05CFEAD823CBBC4"
              "524095AAA10A\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" } ]",
              response);

    // Check that the config was applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(2, keys->size());
}

// Verify that the "config-set" command will do what we expect.
TEST_F(HttpsCtrlChannelD2Test, configSet) {

    string ca_dir(string(TEST_CA_DIR));
    ostringstream d2_st;
    d2_st << "    { \n"
          << "        \"ip-address\": \"192.168.77.1\", \n"
          << "        \"port\": 777, \n"
          << "        \"forward-ddns\" : {}, \n"
          << "        \"reverse-ddns\" : {}, \n"
          << "        \"tsig-keys\": [ \n"
          << "            {\"name\": \"d2_key.example.com\", \n"
          << "             \"algorithm\": \"hmac-md5\", \n"
          << "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
          << "          ], \n"
          << "        \"control-socket\": { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"127.0.0.1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        } \n"
          << "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_st.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration applied successfully." is there
    string answer_txt = answer->str();
    EXPECT_NE(answer_txt.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(answer_txt.find("\"text\": \"Configuration applied successfully.\""),
              std::string::npos);
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Create a config with invalid content that should fail to parse.
    string config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"BOGUS\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n"
        "}} \n";

    // Send the config-set command.
    string response;
    sendHttpCommand(config_set_txt, response);

    // Should fail with a syntax error.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"missing parameter 'name' (<string>:10:14)\" } ]",
              response);

    // Check that the config was not lost (fix: reacquire the context).
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    // Create a valid config with two keys and no command channel.
    config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n"
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"}, \n"
        "           {\"name\": \"d2_key.billcat.net\", \n"
        "            \"algorithm\": \"hmac-md5\", \n"
        "            \"digest-bits\": 120, \n"
        "            \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ] \n"
        "    } \n"
        "}} \n";

    // Verify the HTTP control channel socket exists.
    EXPECT_TRUE(HttpCommandMgr::instance().getHttpListener());

    // Send the config-set command.
    sendHttpCommand(config_set_txt, response);

    // Verify the HTTP control channel socket no longer exists.
    ASSERT_NO_THROW(HttpCommandMgr::instance().closeCommandSockets());
    EXPECT_FALSE(HttpCommandMgr::instance().getHttpListener());

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"5206A1BEC7E3C6ADD5E97C5983861F97739EA05CFEAD823CBBC4"
              "524095AAA10A\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" } ]",
              response);

    // Check that the config was applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(2, keys->size());
}

// Tests if config-write can be called without any parameters.
void
BaseCtrlChannelD2Test::testWriteConfigNoFilename() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    // This is normally set by the command line -c parameter.
    server_->setConfigFile("test1.json");

    // If the filename is not explicitly specified, the name used
    // in -c command line switch is used.
    sendHttpCommand("{ \"command\": \"config-write\" }", response);

    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test1.json");
    ::remove("test1.json");
}

TEST_F(HttpCtrlChannelD2Test, writeConfigNoFilename) {
    testWriteConfigNoFilename();
}

TEST_F(HttpsCtrlChannelD2Test, writeConfigNoFilename) {
    testWriteConfigNoFilename();
}

// Tests if config-write can be called with a valid filename as parameter.
void
BaseCtrlChannelD2Test::testWriteConfigFilename() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    sendHttpCommand("{ \"command\": \"config-write\", "
                    "\"arguments\": { \"filename\": \"test2.json\" } }",
                    response);

    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test2.json");
    ::remove("test2.json");
}

TEST_F(HttpCtrlChannelD2Test, writeConfigFilename) {
    testWriteConfigFilename();
}

TEST_F(HttpsCtrlChannelD2Test, writeConfigFilename) {
    testWriteConfigFilename();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is missing.
void
BaseCtrlChannelD2Test::testConfigReloadMissingFile() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("does-not-exist.json");

    // Tell the server to reload its configuration. It should attempt to load
    // does-not-exist.json (and fail, because the file is not there).
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was rejected.
    string expected = "[ { \"result\": 1, \"text\": "
        "\"Configuration parsing failed: "
        "Unable to open file does-not-exist.json\" } ]";
    EXPECT_EQ(expected, response);
}

TEST_F(HttpCtrlChannelD2Test, configReloadMissingFile) {
    testConfigReloadMissingFile();
}

TEST_F(HttpsCtrlChannelD2Test, configReloadMissingFile) {
    testConfigReloadMissingFile();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is not a valid JSON.
void
BaseCtrlChannelD2Test::testConfigReloadBrokenFile() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("testbad.json");

    // Although Kea is smart, its AI routines are not smart enough to handle
    // this one... at least not yet.
    ofstream f("testbad.json", ios::trunc);
    f << "bla bla bla...";
    f.close();

    // Tell the server to reload its configuration. It should attempt to load
    // testbad.json (and fail, because the file is not valid JSON).
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was rejected.
    string expected = "[ { \"result\": 1, \"text\": "
        "\"Configuration parsing failed: "
        "testbad.json:1.1: Invalid character: b\" } ]";
    EXPECT_EQ(expected, response);

    // Remove the file.
    ::remove("testbad.json");
}

TEST_F(HttpCtrlChannelD2Test, configReloadBrokenFile) {
    testConfigReloadBrokenFile();
}

TEST_F(HttpsCtrlChannelD2Test, configReloadBrokenFile) {
    testConfigReloadBrokenFile();
}

// Tests if config-reload attempts to reload a file and reports that the
// file is loaded correctly.
void
BaseCtrlChannelD2Test::testConfigReloadFileValid() {
    EXPECT_NO_THROW(createHttpChannelServer());
    string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("testvalid.json");

    // Ok, enough fooling around. Let's create a valid config.
    ofstream f("testvalid.json", ios::trunc);
    f << "{ \"DhcpDdns\": "
      << "{"
      << " \"ip-address\": \"192.168.77.1\" , "
      << " \"port\": 777 , "
      << "\"tsig-keys\": [], "
      << "\"forward-ddns\" : {}, "
      << "\"reverse-ddns\" : {} "
      << "}"
      << " }" << endl;
    f.close();

    // Tell the server to reload its configuration. It should attempt to load
    // testvalid.json (and succeed).
    sendHttpCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was successful.
    string expected = "[ { \"arguments\": { \"hash\": \"DC1235F1948D68E06F1425FC28BE326EF01DC4856C3"
                      "833673B9CC8732409B04D\" }, \"result\": 0, \"text\": "
                      "\"Configuration applied successfully.\" } ]";
    EXPECT_EQ(expected, response);

    // Check that the config was indeed applied.
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    D2CfgMgrPtr d2_cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(d2_cfg_mgr);
    D2ParamsPtr d2_params = d2_cfg_mgr->getD2Params();
    ASSERT_TRUE(d2_params);

    EXPECT_EQ("192.168.77.1", d2_params->getIpAddress().toText());
    EXPECT_EQ(777, d2_params->getPort());
    EXPECT_FALSE(d2_cfg_mgr->forwardUpdatesEnabled());
    EXPECT_FALSE(d2_cfg_mgr->reverseUpdatesEnabled());

    // Remove the file.
    ::remove("testvalid.json");
}

TEST_F(HttpCtrlChannelD2Test, configReloadFileValid) {
    testConfigReloadFileValid();
}

TEST_F(HttpsCtrlChannelD2Test, configReloadFileValid) {
    testConfigReloadFileValid();
}

/// Verify that concurrent connections over the HTTP control channel can be
/// established.
TEST_F(HttpCtrlChannelD2Test, concurrentConnections) {
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
TEST_F(HttpsCtrlChannelD2Test, concurrentConnections) {
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
BaseCtrlChannelD2Test::testLongCommand() {

    ostringstream command;

    // This is the desired size of the command sent to the server (1MB).
    // The actual size sent will be slightly greater than that.
    const size_t command_size = 1024 * 1000;

    while (command.tellp() < static_cast<std::streampos>(command_size)) {

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
            if (command.tellp() > static_cast<std::streampos>(command_size)) {
                command << "] }";
            }
        }
    }

    ASSERT_NO_THROW(
        CommandMgr::instance().registerCommand("foo",
            std::bind(&HttpCtrlChannelD2Test::longCommandHandler,
                      command.str(), ph::_1, ph::_2));
    );

    createHttpChannelServer();

    string response;
    ASSERT_NO_THROW(sendHttpCommand(command.str(), response));

    EXPECT_EQ("[ { \"result\": 0, \"text\": \"long command received ok\" } ]",
              response);
}

TEST_F(HttpCtrlChannelD2Test, longCommand) {
    testLongCommand();
}

TEST_F(HttpsCtrlChannelD2Test, longCommand) {
    testLongCommand();
}

// This test verifies that the server can send long response to the client.
void
BaseCtrlChannelD2Test::testLongResponse() {
    // We need to generate large response. The simplest way is to create
    // a command and a handler which will generate some static response
    // of a desired size.
    ASSERT_NO_THROW(
        CommandMgr::instance().registerCommand("foo",
            std::bind(&HttpCtrlChannelD2Test::longResponseHandler,
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

TEST_F(HttpCtrlChannelD2Test, longResponse) {
    testLongResponse();
}

TEST_F(HttpsCtrlChannelD2Test, longResponse) {
    testLongResponse();
}

// Verify that the dual stack scenario works as expect.
TEST_F(HttpCtrlChannelD2Test, dualStack) {

    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-sockets\": [ { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        }, { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"::1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } ] \n"
        "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_cfg_txt, true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": { \"hash\": \"948CDC181979EBB24333894B477C6A29FF158800A11E8AF7C7BA9981F15FC62D\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
              answer->str());
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    string response;

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("Hooks directory: ") != string::npos);

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response, "::1");
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("Hooks directory: ") != string::npos);
}

// Verify that the dual stack scenario works as expect.
TEST_F(HttpsCtrlChannelD2Test, dualStack) {

    string ca_dir(string(TEST_CA_DIR));
    ostringstream d2_st;
    d2_st << "    { \n"
          << "        \"ip-address\": \"192.168.77.1\", \n"
          << "        \"port\": 777, \n"
          << "        \"forward-ddns\" : {}, \n"
          << "        \"reverse-ddns\" : {}, \n"
          << "        \"tsig-keys\": [ \n"
          << "            {\"name\": \"d2_key.example.com\", \n"
          << "             \"algorithm\": \"hmac-md5\", \n"
          << "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
          << "          ], \n"
          << "        \"control-sockets\": [ { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"127.0.0.1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "           \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "           \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "           \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        }, { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"::1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "           \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "           \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "           \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        } ] \n"
          << "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_st.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration applied successfully." is there
    string answer_txt = answer->str();
    EXPECT_NE(answer_txt.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(answer_txt.find("\"text\": \"Configuration applied successfully.\""),
              std::string::npos);
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    string response;

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("Hooks directory: ") != string::npos);

    // Send the version-get command
    sendHttpCommand("{ \"command\": \"version-get\" }", response, "::1");
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("Hooks directory: ") != string::npos);
}

// This test verifies that the server signals timeout if the transmission
// takes too long, having received no data from the client.
void
BaseCtrlChannelD2Test::testConnectionTimeoutNoData() {
    // Set connection timeout to 2s to prevent long waiting time for the
    // timeout during this test.
    const unsigned short timeout = 2000;
    HttpCommandMgr::instance().setConnectionTimeout(timeout);

    createHttpChannelServer();

    string response;
    ASSERT_NO_THROW(sendHttpCommand("{ \"command\": ", response));

    EXPECT_EQ("{ \"result\": 400, \"text\": \"Bad Request\" }", response);
}

TEST_F(HttpCtrlChannelD2Test, connectionTimeoutNoData) {
    testConnectionTimeoutNoData();
}

TEST_F(HttpsCtrlChannelD2Test, connectionTimeoutNoData) {
    testConnectionTimeoutNoData();
}

// Verify that the "config-set" command will reuse listener
TEST_F(HttpCtrlChannelD2Test, noListenerChange) {

    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_cfg_txt, true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": { \"hash\": \"029AE1208415D6911B5651A6F82D054F55B7877D2589CFD1DCEB5BFFCD3B13A3\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
              answer->str());
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    // Create a config with same content that should not recreate listener.
    string config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n";

    config_set_txt += d2_cfg_txt;
    config_set_txt += "}} \n";

    // Send the config-set command.
    string response;
    sendHttpCommand(config_set_txt, response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    // Verify the configuration was successful.
    EXPECT_EQ("[ { \"arguments\": { \"hash\": \"029AE1208415D6911B5651A6F82D054F55B7877D2589CFD1DCEB5BFFCD3B13A3\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" } ]",
              response);

    // Check that the config was applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

// Verify that the "config-set" command will reuse listener
TEST_F(HttpsCtrlChannelD2Test, noListenerChange) {

    string ca_dir(string(TEST_CA_DIR));
    ostringstream d2_st;
    d2_st << "    { \n"
          << "        \"ip-address\": \"192.168.77.1\", \n"
          << "        \"port\": 777, \n"
          << "        \"forward-ddns\" : {}, \n"
          << "        \"reverse-ddns\" : {}, \n"
          << "        \"tsig-keys\": [ \n"
          << "            {\"name\": \"d2_key.example.com\", \n"
          << "             \"algorithm\": \"hmac-md5\", \n"
          << "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
          << "          ], \n"
          << "        \"control-socket\": { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"127.0.0.1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        } \n"
          << "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_st.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration applied successfully." is there
    string answer_txt = answer->str();
    EXPECT_NE(answer_txt.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(answer_txt.find("\"text\": \"Configuration applied successfully.\""),
              std::string::npos);
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    auto const context = HttpCommandMgr::instance().getHttpListener()->getTlsContext().get();

    // Create a config with same content that should not recreate listener.
    string config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n";

    config_set_txt += d2_st.str();
    config_set_txt += "}} \n";

    // Send the config-set command.
    string response;
    sendHttpCommand(config_set_txt, response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    // The TLS settings have been applied
    EXPECT_NE(context, HttpCommandMgr::instance().getHttpListener()->getTlsContext().get());

    // Verify the configuration was successful.
    EXPECT_NE(response.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Configuration applied successfully.\""),
              std::string::npos);

    // Check that the config was applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

// Verify that the "config-set" command will exit with an error
TEST_F(HttpCtrlChannelD2Test, handleHttpToHttpsSwitch) {

    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_cfg_txt, true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": { \"hash\": \"029AE1208415D6911B5651A6F82D054F55B7877D2589CFD1DCEB5BFFCD3B13A3\" }, \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
              answer->str());
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    string ca_dir(string(TEST_CA_DIR));
    ostringstream d2_st;
    d2_st << "    { \n"
          << "        \"ip-address\": \"192.168.77.1\", \n"
          << "        \"port\": 777, \n"
          << "        \"forward-ddns\" : {}, \n"
          << "        \"reverse-ddns\" : {}, \n"
          << "        \"tsig-keys\": [ \n"
          << "            {\"name\": \"d2_key.example.com\", \n"
          << "             \"algorithm\": \"hmac-md5\", \n"
          << "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
          << "          ], \n"
          << "        \"control-socket\": { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"127.0.0.1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        } \n"
          << "    } \n";

    // Create a config with HTTPS and same content that should not recreate listener.
    string config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n";

    config_set_txt += d2_st.str();
    config_set_txt += "}} \n";

    // Send the config-set command.
    string response;
    sendHttpCommand(config_set_txt, response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_FALSE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());

    // Verify the configuration was rejected.
    EXPECT_NE(response.find("\"result\": 1"), std::string::npos);
    EXPECT_NE(response.find("\"text\": \"Can not switch from HTTP to HTTPS sockets using the same address and port.\""),
              std::string::npos);

    // Check that the config was not applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

// Verify that the "config-set" command will exit with an error
TEST_F(HttpsCtrlChannelD2Test, handleHttpsToHttpSwitch) {

    string ca_dir(string(TEST_CA_DIR));
    ostringstream d2_st;
    d2_st << "    { \n"
          << "        \"ip-address\": \"192.168.77.1\", \n"
          << "        \"port\": 777, \n"
          << "        \"forward-ddns\" : {}, \n"
          << "        \"reverse-ddns\" : {}, \n"
          << "        \"tsig-keys\": [ \n"
          << "            {\"name\": \"d2_key.example.com\", \n"
          << "             \"algorithm\": \"hmac-md5\", \n"
          << "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
          << "          ], \n"
          << "        \"control-socket\": { \n"
          << "           \"socket-type\": \"https\", \n"
          << "           \"socket-address\": \"127.0.0.1\", \n"
          << "           \"socket-port\": 18125, \n"
          << "        \"trust-anchor\": \"" << ca_dir << "/kea-ca.crt\", \n"
          << "        \"cert-file\": \"" << ca_dir << "/kea-server.crt\", \n"
          << "        \"key-file\": \"" << ca_dir << "/kea-server.key\" \n"
          << "        } \n"
          << "    } \n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(d2_st.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    // Verify the configuration was successful. The config contains random
    // file paths (CA directory), so the hash will be different each time.
    // As such, we can do simplified checks:
    // - verify the "result": 0 is there
    // - verify the "text": "Configuration applied successfully." is there
    string answer_txt = answer->str();
    EXPECT_NE(answer_txt.find("\"result\": 0"), std::string::npos);
    EXPECT_NE(answer_txt.find("\"text\": \"Configuration applied successfully.\""),
              std::string::npos);
    ASSERT_NO_THROW(d2Controller()->registerCommands());

    // Check that the config was indeed applied.
    D2CfgMgrPtr cfg_mgr = proc->getD2CfgMgr();
    ASSERT_TRUE(cfg_mgr);
    D2CfgContextPtr d2_context = cfg_mgr->getD2CfgContext();
    ASSERT_TRUE(d2_context);
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    auto const listener = HttpCommandMgr::instance().getHttpListener().get();
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    auto const context = HttpCommandMgr::instance().getHttpListener()->getTlsContext().get();

    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n"
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n"
        "          ], \n"
        "        \"control-socket\": { \n"
        "           \"socket-type\": \"http\", \n"
        "           \"socket-address\": \"127.0.0.1\", \n"
        "           \"socket-port\": 18125 \n"
        "        } \n"
        "    } \n";

    // Create a config with HTTP and same content that should not recreate listener.
    string config_set_txt =
        "{ \"command\": \"config-set\", \n"
        "  \"arguments\": { \n"
        "    \"DhcpDdns\": \n";

    config_set_txt += d2_cfg_txt;
    config_set_txt += "}} \n";

    // Send the config-set command.
    string response;
    sendHttpCommand(config_set_txt, response);

    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener());
    EXPECT_EQ(listener, HttpCommandMgr::instance().getHttpListener().get());
    ASSERT_TRUE(HttpCommandMgr::instance().getHttpListener()->getTlsContext());
    // The TLS settings have not changed
    EXPECT_EQ(context, HttpCommandMgr::instance().getHttpListener()->getTlsContext().get());

    // Verify the configuration was rejected.
    EXPECT_EQ("[ { \"result\": 1, \"text\": \"Can not switch from HTTPS to HTTP sockets using the same address and port.\" } ]",
              response);

    // Check that the config was not applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

} // end of anonymous namespace
