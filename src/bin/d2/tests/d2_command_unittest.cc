// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/timeouts.h>
#include <testutils/io_utils.h>
#include <testutils/unix_control_client.h>
#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2/parser_context.h>
#include <gtest/gtest.h>
#include <testutils/sandbox.h>
#include <boost/pointer_cast.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace boost::asio;
namespace ph = std::placeholders;

namespace isc {
namespace d2 {

class NakedD2Controller;
typedef boost::shared_ptr<NakedD2Controller> NakedD2ControllerPtr;

class NakedD2Controller : public D2Controller {
    // "Naked" D2 controller, exposes internal methods.
public:
    static DControllerBasePtr& instance() {
        static DControllerBasePtr controller_ptr;
        if (!controller_ptr) {
            controller_ptr.reset(new NakedD2Controller());
        }

        return (controller_ptr);
    }

    virtual ~NakedD2Controller() { deregisterCommands(); }

    using DControllerBase::getIOService;
    using DControllerBase::initProcess;

    D2ProcessPtr getProcess() {
        return (boost::dynamic_pointer_cast<D2Process>(DControllerBase::getProcess()));
    }

private:
    NakedD2Controller() { }
};

}; // namespace isc::d2
}; // namespace isc

namespace {

/// @brief Simple RAII class which stops IO service upon destruction
/// of the object.
class IOServiceWork {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Pointer to the IO service to be stopped.
    explicit IOServiceWork(const IOServicePtr& io_service)
        : io_service_(io_service) {
    }

    /// @brief Destructor.
    ///
    /// Stops IO service.
    ~IOServiceWork() {
        io_service_->stop();
    }

private:

    /// @brief Pointer to the IO service to be stopped upon destruction.
    IOServicePtr io_service_;

};

/// @brief Fixture class intended for testing control channel in D2.
class CtrlChannelD2Test : public ::testing::Test {
public:
    isc::test::Sandbox sandbox;

    /// @brief Path to the UNIX socket being used to communicate with the server.
    string socket_path_;

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
    CtrlChannelD2Test()
        : server_(NakedD2Controller::instance()) {
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path_ = string(env) + "/d2.sock";
        } else {
            socket_path_ = sandbox.join("d2.sock");
        }
        ::remove(socket_path_.c_str());
    }

    /// @brief Destructor.
    ~CtrlChannelD2Test() {
        // Deregister & co.
        server_.reset();

        // Remove files.
        ::remove(CFG_TEST_FILE);
        ::remove(socket_path_.c_str());

        // Reset command manager.
        CommandMgr::instance().deregisterAll();
        CommandMgr::instance().setConnectionTimeout(TIMEOUT_DHCP_SERVER_RECEIVE_COMMAND);
    }

    /// @brief Returns pointer to the server's IO service.
    ///
    /// @return Pointer to the server's IO service or null pointer if the
    /// hasn't been created server.
    IOServicePtr getIOService() {
        return (server_ ? d2Controller()->getIOService() : IOServicePtr());
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

    /// @brief Create a server with a command channel.
    void createUnixChannelServer() {
        ::remove(socket_path_.c_str());

        // Just a simple config. The important part here is the socket
        // location information.
        string header =
            "{"
            "    \"ip-address\": \"192.168.77.1\","
            "    \"port\": 777,"
            "    \"control-socket\": {"
            "        \"socket-type\": \"unix\","
            "        \"socket-name\": \"";

        string footer =
            "\""
            "    },"
            "    \"tsig-keys\": [],"
            "    \"forward-ddns\" : {},"
            "    \"reverse-ddns\" : {}"
            "}";

        // Fill in the socket-name value with socket_path_ to make
        // the actual configuration text.
        string config_txt = header + socket_path_  + footer;

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
        ASSERT_GT(CommandMgr::instance().getControlSocketFD(), -1);
    }

    /// @brief Conducts a command/response exchange via UnixCommandSocket.
    ///
    /// This method connects to the given server over the given socket path.
    /// If successful, it then sends the given command and retrieves the
    /// server's response.  Note that it polls the server's I/O service
    /// where needed to cause the server to process IO events on
    /// the control channel sockets
    ///
    /// @param command the command text to execute in JSON form
    /// @param response variable into which the received response should be
    ///        placed.
    void sendUnixCommand(const string& command, string& response) {
        response = "";
        boost::scoped_ptr<UnixControlClient> client;
        client.reset(new UnixControlClient());
        ASSERT_TRUE(client);

        // Connect to the server. This is expected to trigger server's acceptor
        // handler when IOService::poll() is run.
        ASSERT_TRUE(client->connectToServer(socket_path_));
        ASSERT_NO_THROW(getIOService()->poll());

        // Send the command. This will trigger server's handler which receives
        // data over the unix domain socket. The server will start sending
        // response to the client.
        ASSERT_TRUE(client->sendCommand(command));
        ASSERT_NO_THROW(getIOService()->poll());

        // Read the response generated by the server. Note that getResponse
        // only fails if there an IO error or no response data was present.
        // It is not based on the response content.
        ASSERT_TRUE(client->getResponse(response));

        // Now disconnect and process the close event.
        client->disconnectFromServer();

        ASSERT_NO_THROW(getIOService()->poll());
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
        EXPECT_NO_THROW(params = parseAnswer(status_code, rsp));
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
    /// @param response_txt response in text form.
    ///        (as read from the control socket)
    /// @param exp_status expected status.
    ///        (0 success, 1 failure)
    /// @param exp_txt for success cases this defines the expected filename,
    ///        for failure cases this defines the expected error message.
    void checkConfigWrite(const string& response_txt, int exp_status,
                          const string& exp_txt = "") {

        ConstElementPtr rsp;
        EXPECT_NO_THROW(rsp = Element::fromJSON(response_txt));
        ASSERT_TRUE(rsp);

        int status;
        ConstElementPtr params = parseAnswer(status, rsp);
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
        return (createAnswer(0, "long command received ok"));
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
        return (createAnswer(0, arguments));
    }
};

const char* CtrlChannelD2Test::CFG_TEST_FILE = "d2-test-config.json";

// Test bad syntax rejected by the parser.
TEST_F(CtrlChannelD2Test, parser) {
    // no empty map.
    string bad1 =
        "{"
        "    \"ip-address\": \"192.168.77.1\","
        "    \"port\": 777,"
        "    \"control-socket\": { },"
        "    \"tsig-keys\": [],"
        "    \"forward-ddns\" : {},"
        "    \"reverse-ddns\" : {}"
        "}";
    ASSERT_THROW(parseDHCPDDNS(bad1), D2ParseError);

    // unknown keyword.
    string bad2 =
        "{"
        "    \"ip-address\": \"192.168.77.1\","
        "    \"port\": 777,"
        "    \"control-socket\": {"
        "        \"socket-type\": \"unix\","
        "        \"socket-name\": \"/tmp/d2.sock\","
        "        \"bogus\": \"unknown...\""
        "    },"
        "    \"tsig-keys\": [],"
        "    \"forward-ddns\" : {},"
        "    \"reverse-ddns\" : {}"
        "}";
    ASSERT_THROW(parseDHCPDDNS(bad2), D2ParseError);
}

// Test bad syntax rejected by the process.
TEST_F(CtrlChannelD2Test, configure) {
    ASSERT_TRUE(server_);
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);

    // no type.
    string bad1 =
        "{"
        "    \"ip-address\": \"192.168.77.1\","
        "    \"port\": 777,"
        "    \"control-socket\": {"
        "        \"socket-name\": \"/tmp/d2.sock\""
        "    },"
        "    \"tsig-keys\": [],"
        "    \"forward-ddns\" : {},"
        "    \"reverse-ddns\" : {}"
        "}";
    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(bad1, true));

    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);

    int status = 0;
    ConstElementPtr txt = parseAnswer(status, answer);
    EXPECT_EQ(1, status);
    ASSERT_TRUE(txt);
    ASSERT_EQ(Element::string, txt->getType());
    EXPECT_EQ("Mandatory 'socket-type' parameter missing", txt->stringValue());
    EXPECT_EQ(-1, CommandMgr::instance().getControlSocketFD());

    // bad type.
    string bad2 =
        "{"
        "    \"ip-address\": \"192.168.77.1\","
        "    \"port\": 777,"
        "    \"control-socket\": {"
        "        \"socket-type\": \"bogus\","
        "        \"socket-name\": \"/tmp/d2.sock\""
        "    },"
        "    \"tsig-keys\": [],"
        "    \"forward-ddns\" : {},"
        "    \"reverse-ddns\" : {}"
        "}";
    ASSERT_NO_THROW(config = parseDHCPDDNS(bad2, true));

    answer = proc->configure(config, false);
    ASSERT_TRUE(answer);

    status = 0;
    txt = parseAnswer(status, answer);
    EXPECT_EQ(1, status);
    ASSERT_TRUE(txt);
    ASSERT_EQ(Element::string, txt->getType());
    EXPECT_EQ("Invalid 'socket-type' parameter value bogus",
              txt->stringValue());
    EXPECT_EQ(-1, CommandMgr::instance().getControlSocketFD());

    // no name.
    string bad3 =
        "{"
        "    \"ip-address\": \"192.168.77.1\","
        "    \"port\": 777,"
        "    \"control-socket\": {"
        "        \"socket-type\": \"unix\""
        "    },"
        "    \"tsig-keys\": [],"
        "    \"forward-ddns\" : {},"
        "    \"reverse-ddns\" : {}"
        "}";
    ASSERT_NO_THROW(config = parseDHCPDDNS(bad3, true));

    answer = proc->configure(config, false);
    ASSERT_TRUE(answer);

    status = 0;
    txt = parseAnswer(status, answer);
    EXPECT_EQ(1, status);
    ASSERT_TRUE(txt);
    ASSERT_EQ(Element::string, txt->getType());
    EXPECT_EQ("Mandatory 'socket-name' parameter missing",
              txt->stringValue());
    EXPECT_EQ(-1, CommandMgr::instance().getControlSocketFD());
}

// This test checks which commands are registered by the D2 server.
TEST_F(CtrlChannelD2Test, commandsRegistration) {

    ConstElementPtr list_cmds = createCommand("list-commands");
    ConstElementPtr answer;

    // By default the list should be empty (except the standard list-commands
    // supported by the CommandMgr itself).
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());

    // Created server should register several additional commands.
    EXPECT_NO_THROW(createUnixChannelServer());

    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    string command_list = answer->get("arguments")->str();

    EXPECT_TRUE(command_list.find("\"list-commands\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"build-report\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-reload\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-set\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-test\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-write\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"shutdown\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"status-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-reset\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-reset-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"version-get\"") != string::npos);

    // Ok, and now delete the server. It should deregister its commands.
    server_.reset();

    // The list should be (almost) empty again.
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());
}

// Tests that the server properly responds to invalid commands.
TEST_F(CtrlChannelD2Test, invalid) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"bogus\" }", response);
    EXPECT_EQ("{ \"result\": 2, \"text\": \"'bogus' command not supported.\" }",
              response);

    sendUnixCommand("utter nonsense", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"invalid first character u\" }",
              response);
}

// Tests that the server properly responds to shutdown command.
TEST_F(CtrlChannelD2Test, shutdown) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"shutdown\" }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Shutdown initiated, type is: normal\" }",
              response);
    EXPECT_EQ(EXIT_SUCCESS, server_->getExitValue());
}

// Tests that the server sets exit value supplied as argument
// to shutdown command.
TEST_F(CtrlChannelD2Test, shutdownExitValue) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"shutdown\", "
                    "\"arguments\": { \"exit-value\": 77 }}",
                    response);

    EXPECT_EQ("{ \"result\": 0, \"text\": \"Shutdown initiated, type is: normal\" }",
              response);

    EXPECT_EQ(77, server_->getExitValue());
}

// This test verifies that the DHCP server handles version-get commands.
TEST_F(CtrlChannelD2Test, getversion) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    // Send the version-get command.
    sendUnixCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the build-report command.
    sendUnixCommand("{ \"command\": \"build-report\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("GTEST_VERSION") != string::npos);
}

// Tests that the server properly responds to list-commands command.
TEST_F(CtrlChannelD2Test, listCommands) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"list-commands\" }", response);

    ConstElementPtr rsp;
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));

    // We expect the server to report at least the following commands:
    checkListCommands(rsp, "build-report");
    checkListCommands(rsp, "config-get");
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

// This test verifies that the D2 server handles status-get commands
TEST_F(CtrlChannelD2Test, statusGet) {
    EXPECT_NO_THROW(createUnixChannelServer());

    std::string response_txt;

    // Send the version-get command
    sendUnixCommand("{ \"command\": \"status-get\" }", response_txt);
    ConstElementPtr response;
    ASSERT_NO_THROW(response = Element::fromJSON(response_txt));
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

// Tests if the server returns its configuration using config-get.
// Note there are separate tests that verify if toElement() called by the
// config-get handler are actually converting the configuration correctly.
TEST_F(CtrlChannelD2Test, configGet) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"config-get\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    // Ok, now roughly check if the response seems legit.
    ASSERT_TRUE(cfg);
    ASSERT_EQ(Element::map, cfg->getType());
    EXPECT_TRUE(cfg->get("DhcpDdns"));
}

// Verify that the "config-test" command will do what we expect.
TEST_F(CtrlChannelD2Test, configTest) {

    // Define strings to permutate the config arguments.
    // (Note the line feeds makes errors easy to find)
    string config_test_txt = "{ \"command\": \"config-test\" \n";
    string args_txt = " \"arguments\": { \n";
    string d2_header =
        "    \"DhcpDdns\": \n";
    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n";
    string key1 =
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n";
    string key2 =
        "           {\"name\": \"d2_key.billcat.net\", \n"
        "            \"algorithm\": \"hmac-md5\", \n"
        "            \"digest-bits\": 120, \n"
        "            \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n";
    string bad_key =
        "            {\"BOGUS\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n";
    string key_footer =
        "          ] \n";
    string control_socket_header =
        "       ,\"control-socket\": { \n"
        "           \"socket-type\": \"unix\", \n"
        "           \"socket-name\": \"";
    string control_socket_footer =
        "\"   \n} \n";

    ostringstream os;
    // Create a valid config with all the parts should parse.
    os << d2_cfg_txt
       << key1
       << key_footer
       << control_socket_header
       << socket_path_
       << control_socket_footer
       << "}\n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(os.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
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

    ASSERT_GT(CommandMgr::instance().getControlSocketFD(), -1);

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_test_txt << ","
       << args_txt
       << d2_header
       << d2_cfg_txt
       << bad_key
       << key_footer
       << control_socket_header
       << socket_path_
       << control_socket_footer
       << "}\n"                        // close DhcpDdns.
       << "}}";

    // Send the config-test command.
    string response;
    sendUnixCommand(os.str(), response);

    // Should fail with a syntax error.
    EXPECT_EQ("{ \"result\": 1, \"text\": \"missing parameter 'name' (<wire>:9:14)\" }",
              response);

    // Check that the config was not lost (fix: reacquire the context).
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    // Create a valid config with two keys and no command channel.
    os.str("");
    os << config_test_txt << ","
       << args_txt
       << d2_header
       << d2_cfg_txt
       << key1
       << ",\n"
       << key2
       << key_footer
       << "}\n"                        // close DhcpDdns.
       << "}}";

    // Verify the control channel socket exists.
    ASSERT_TRUE(test::fileExists(socket_path_));

    // Send the config-test command.
    sendUnixCommand(os.str(), response);

    // Verify the control channel socket still exists.
    EXPECT_TRUE(test::fileExists(socket_path_));

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration check successful\" }",
              response);

    // Check that the config was not applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
}

// Verify that the "config-set" command will do what we expect.
TEST_F(CtrlChannelD2Test, configSet) {

    // Define strings to permutate the config arguments.
    // (Note the line feeds makes errors easy to find)
    string config_set_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string d2_header =
        "    \"DhcpDdns\": \n";
    string d2_cfg_txt =
        "    { \n"
        "        \"ip-address\": \"192.168.77.1\", \n"
        "        \"port\": 777, \n"
        "        \"forward-ddns\" : {}, \n"
        "        \"reverse-ddns\" : {}, \n"
        "        \"tsig-keys\": [ \n";
    string key1 =
        "            {\"name\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n";
    string key2 =
        "           {\"name\": \"d2_key.billcat.net\", \n"
        "            \"algorithm\": \"hmac-md5\", \n"
        "            \"digest-bits\": 120, \n"
        "            \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n";
    string bad_key =
        "            {\"BOGUS\": \"d2_key.example.com\", \n"
        "             \"algorithm\": \"hmac-md5\", \n"
        "             \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\"} \n";
    string key_footer =
        "          ] \n";
    string control_socket_header =
        "       ,\"control-socket\": { \n"
        "           \"socket-type\": \"unix\", \n"
        "           \"socket-name\": \"";
    string control_socket_footer =
        "\"   \n} \n";

    ostringstream os;
    // Create a valid config with all the parts should parse.
    os << d2_cfg_txt
       << key1
       << key_footer
       << control_socket_header
       << socket_path_
       << control_socket_footer
       << "}\n";

    ASSERT_TRUE(server_);

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCPDDNS(os.str(), true));
    ASSERT_NO_THROW(d2Controller()->initProcess());
    D2ProcessPtr proc = d2Controller()->getProcess();
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
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

    ASSERT_GT(CommandMgr::instance().getControlSocketFD(), -1);

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_set_txt << ","
       << args_txt
       << d2_header
       << d2_cfg_txt
       << bad_key
       << key_footer
       << control_socket_header
       << socket_path_
       << control_socket_footer
       << "}\n"                        // close DhcpDdns.
       << "}}";

    // Send the config-set command.
    string response;
    sendUnixCommand(os.str(), response);

    // Should fail with a syntax error.
    EXPECT_EQ("{ \"result\": 1, \"text\": \"missing parameter 'name' (<wire>:9:14)\" }",
              response);

    // Check that the config was not lost (fix: reacquire the context).
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());

    // Create a valid config with two keys and no command channel.
    os.str("");
    os << config_set_txt << ","
       << args_txt
       << d2_header
       << d2_cfg_txt
       << key1
       << ",\n"
       << key2
       << key_footer
       << "}\n"                        // close DhcpDdns.
       << "}}";

    // Verify the control channel socket exists.
    ASSERT_TRUE(test::fileExists(socket_path_));

    // Send the config-set command.
    sendUnixCommand(os.str(), response);

    // Verify the control channel socket no longer exists.
    EXPECT_FALSE(test::fileExists(socket_path_));

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration applied successfully.\" }",
              response);

    // Check that the config was applied.
    d2_context = cfg_mgr->getD2CfgContext();
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(2, keys->size());
}

// Tests if config-write can be called without any parameters.
TEST_F(CtrlChannelD2Test, writeConfigNoFilename) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    // This is normally set by the command line -c parameter.
    server_->setConfigFile("test1.json");

    // If the filename is not explicitly specified, the name used
    // in -c command line switch is used.
    sendUnixCommand("{ \"command\": \"config-write\" }", response);

    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test1.json");
    ::remove("test1.json");
}

// Tests if config-write can be called with a valid filename as parameter.
TEST_F(CtrlChannelD2Test, writeConfigFilename) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"config-write\", "
                    "\"arguments\": { \"filename\": \"test2.json\" } }",
                    response);
    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test2.json");
    ::remove("test2.json");
}

// Tests if config-reload attempts to reload a file and reports that the
// file is missing.
TEST_F(CtrlChannelD2Test, configReloadMissingFile) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("does-not-exist.json");

    // Tell the server to reload its configuration. It should attempt to load
    // does-not-exist.json (and fail, because the file is not there).
    sendUnixCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was rejected.
    string expected = "{ \"result\": 1, \"text\": "
        "\"Configuration parsing failed: "
        "Unable to open file does-not-exist.json\" }";
    EXPECT_EQ(expected, response);
}

// Tests if config-reload attempts to reload a file and reports that the
// file is not a valid JSON.
TEST_F(CtrlChannelD2Test, configReloadBrokenFile) {
    EXPECT_NO_THROW(createUnixChannelServer());
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
    // does-not-exist.json (and fail, because the file is not there).
    sendUnixCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was rejected.
    string expected = "{ \"result\": 1, \"text\": "
        "\"Configuration parsing failed: "
        "testbad.json:1.1: Invalid character: b\" }";
    EXPECT_EQ(expected, response);

    // Remove the file.
    ::remove("testbad.json");
}

// Tests if config-reload attempts to reload a file and reports that the
// file is missing.
TEST_F(CtrlChannelD2Test, configReloadFileValid) {
    EXPECT_NO_THROW(createUnixChannelServer());
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
    sendUnixCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was successful.
    string expected = "{ \"result\": 0, \"text\": "
        "\"Configuration applied successfully.\" }";
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

/// Verify that concurrent connections over the control channel can be
/// established. (@todo change when response will be sent in multiple chunks)
TEST_F(CtrlChannelD2Test, concurrentConnections) {
    EXPECT_NO_THROW(createUnixChannelServer());

    boost::scoped_ptr<UnixControlClient> client1(new UnixControlClient());
    ASSERT_TRUE(client1);

    boost::scoped_ptr<UnixControlClient> client2(new UnixControlClient());
    ASSERT_TRUE(client2);

    // Client 1 connects.
    ASSERT_TRUE(client1->connectToServer(socket_path_));
    ASSERT_NO_THROW(getIOService()->poll());

    // Client 2 connects.
    ASSERT_TRUE(client2->connectToServer(socket_path_));
    ASSERT_NO_THROW(getIOService()->poll());

    // Send the command while another client is connected.
    ASSERT_TRUE(client2->sendCommand("{ \"command\": \"list-commands\" }"));
    ASSERT_NO_THROW(getIOService()->poll());

    string response;
    // The server should respond ok.
    ASSERT_TRUE(client2->getResponse(response));
    EXPECT_TRUE(response.find("\"result\": 0") != std::string::npos);

    // Disconnect the servers.
    client1->disconnectFromServer();
    client2->disconnectFromServer();
    ASSERT_NO_THROW(getIOService()->poll());
}

// This test verifies that the server can receive and process a large command.
TEST_F(CtrlChannelD2Test, longCommand) {

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
            std::bind(&CtrlChannelD2Test::longCommandHandler,
                      command.str(), ph::_1, ph::_2));
    );

    createUnixChannelServer();

    string response;
    std::thread th([this, &response, &command]() {

        // IO service will be stopped automatically when this object goes
        // out of scope and is destroyed. This is useful because we use
        // asserts which may break the thread in various exit points.
        IOServiceWork work(getIOService());

        // Create client which we will use to send command to the server.
        boost::scoped_ptr<UnixControlClient> client(new UnixControlClient());
        ASSERT_TRUE(client);

        // Connect to the server. This will trigger acceptor handler on the
        // server side and create a new connection.
        ASSERT_TRUE(client->connectToServer(socket_path_));

        // Initially the remaining_string holds the entire command and we
        // will be erasing the portions that we have sent.
        string remaining_data = command.str();
        while (!remaining_data.empty()) {
            // Send the command in chunks of 1024 bytes.
            const size_t l = remaining_data.size() < 1024 ? remaining_data.size() : 1024;
            ASSERT_TRUE(client->sendCommand(remaining_data.substr(0, l)));
            remaining_data.erase(0, l);
        }

        // Set timeout to 5 seconds to allow the time for the server to send
        // a response.
        const unsigned int timeout = 5;
        ASSERT_TRUE(client->getResponse(response, timeout));

        // We're done. Close the connection to the server.
        client->disconnectFromServer();
        });

    // Run the server until the command has been processed and response
    // received.
    getIOService()->run();

    // Wait for the thread to complete.
    th.join();

    EXPECT_EQ("{ \"result\": 0, \"text\": \"long command received ok\" }",
              response);
}

// This test verifies that the server can send long response to the client.
TEST_F(CtrlChannelD2Test, longResponse) {
    // We need to generate large response. The simplest way is to create
    // a command and a handler which will generate some static response
    // of a desired size
    ASSERT_NO_THROW(
        CommandMgr::instance().registerCommand("foo",
            std::bind(&CtrlChannelD2Test::longResponseHandler, ph::_1, ph::_2));
    );

    createUnixChannelServer();

    // The UnixControlClient doesn't have any means to check that the entire
    // response has been received. What we want to do is to generate a
    // reference response using our command handler and then compare
    // what we have received over the unix domain socket with this reference
    // response to figure out when to stop receiving.
    string reference_response = longResponseHandler("foo", ConstElementPtr())->str();

    // In this stream we're going to collect out partial responses.
    ostringstream response;

    // The client is synchronous so it is useful to run it in a thread.
    std::thread th([this, &response, reference_response]() {

        // IO service will be stopped automatically when this object goes
        // out of scope and is destroyed. This is useful because we use
        // asserts which may break the thread in various exit points.
        IOServiceWork work(getIOService());

        // Remember the response size so as we know when we should stop
        // receiving.
        const size_t long_response_size = reference_response.size();

        // Create the client and connect it to the server.
        boost::scoped_ptr<UnixControlClient> client(new UnixControlClient());
        ASSERT_TRUE(client);
        ASSERT_TRUE(client->connectToServer(socket_path_));

        // Send the stub command.
        std::string command = "{ \"command\": \"foo\", \"arguments\": { }  }";
        ASSERT_TRUE(client->sendCommand(command));

        // Keep receiving response data until we have received the full answer.
        while (response.tellp() < long_response_size) {
            std::string partial;
            const unsigned int timeout = 5;
            ASSERT_TRUE(client->getResponse(partial, timeout));
            response << partial;
        }

        // We have received the entire response, so close the connection and
        // stop the IO service.
        client->disconnectFromServer();
        });

    // Run the server until the entire response has been received.
    getIOService()->run();

    // Wait for the thread to complete.
    th.join();

    // Make sure we have received correct response.
    EXPECT_EQ(reference_response, response.str());
}

// This test verifies that the server signals timeout if the transmission
// takes too long, after receiving a partial command
TEST_F(CtrlChannelD2Test, connectionTimeoutPartialCommand) {
    createUnixChannelServer();

    // Set connection timeout to 2s to prevent long waiting time for the
    // timeout during this test.
    const unsigned short timeout = 2000;
    CommandMgr::instance().setConnectionTimeout(timeout);

    // Server's response will be assigned to this variable.
    string response;

    // It is useful to create a thread and run the server and the client
    // at the same time and independently.
    std::thread th([this, &response]() {

        // IO service will be stopped automatically when this object goes
        // out of scope and is destroyed. This is useful because we use
        // asserts which may break the thread in various exit points.
        IOServiceWork work(getIOService());

        // Create the client and connect it to the server.
        boost::scoped_ptr<UnixControlClient> client(new UnixControlClient());
        ASSERT_TRUE(client);
        ASSERT_TRUE(client->connectToServer(socket_path_));

        // Send partial command. The server will be waiting for the remaining
        // part to be sent and will eventually signal a timeout.
        string command = "{ \"command\": \"foo\" ";
        ASSERT_TRUE(client->sendCommand(command));

        // Let's wait up to 15s for the server's response. The response
        // should arrive sooner assuming that the timeout mechanism for
        // the server is working properly.
        const unsigned int timeout = 15;
        ASSERT_TRUE(client->getResponse(response, timeout));

        // Explicitly close the client's connection.
        client->disconnectFromServer();
        });

    // Run the server until stopped.
    getIOService()->run();

    // Wait for the thread to return.
    th.join();

    // Check that the server has signalled a timeout.
    EXPECT_EQ("{ \"result\": 1, \"text\": \"Connection over control channel timed out, discarded partial command of 19 bytes\" }" ,
              response);
}

// This test verifies that the server signals timeout if the transmission
// takes too long, having received no data from the client.
TEST_F(CtrlChannelD2Test, connectionTimeoutNoData) {
    createUnixChannelServer();

    // Set connection timeout to 2s to prevent long waiting time for the
    // timeout during this test.
    const unsigned short timeout = 2000;
    CommandMgr::instance().setConnectionTimeout(timeout);

    // Server's response will be assigned to this variable.
    string response;

    // It is useful to create a thread and run the server and the client
    // at the same time and independently.
    std::thread th([this, &response]() {

        // IO service will be stopped automatically when this object goes
        // out of scope and is destroyed. This is useful because we use
        // asserts which may break the thread in various exit points.
        IOServiceWork work(getIOService());

        // Create the client and connect it to the server.
        boost::scoped_ptr<UnixControlClient> client(new UnixControlClient());
        ASSERT_TRUE(client);
        ASSERT_TRUE(client->connectToServer(socket_path_));

        // Let's wait up to 15s for the server's response. The response
        // should arrive sooner assuming that the timeout mechanism for
        // the server is working properly.
        const unsigned int timeout = 15;
        ASSERT_TRUE(client->getResponse(response, timeout));

        // Explicitly close the client's connection.
        client->disconnectFromServer();
        });

    // Run the server until stopped.
    getIOService()->run();

    // Wait for the thread to return.
    th.join();

    // Check that the server has signalled a timeout.
    EXPECT_EQ("{ \"result\": 1, \"text\": \"Connection over control channel timed out\" }",
              response);
}

} // End of anonymous namespace
