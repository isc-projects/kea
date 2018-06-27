// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/timeouts.h>
#include <testutils/io_utils.h>
#include <testutils/unix_control_client.h>
#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2/parser_context.h>
#include <gtest/gtest.h>
#include <boost/pointer_cast.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::dhcp::test;
using namespace isc::process;
using namespace boost::asio;

namespace {

class NakedD2Controller;
typedef boost::shared_ptr<NakedD2Controller> NakedD2ControllerPtr;

class NakedD2Controller : public D2Controller {
    // "Naked" D2 controller, exposes internal methods.
public:
    static DControllerBasePtr& instance() {
        if (!getController()) {
            DControllerBasePtr controller_ptr(new NakedD2Controller());
            setController(controller_ptr);
        }

        return (getController());
    }

    virtual ~NakedD2Controller() { }

    using DControllerBase::getIOService;
    using DControllerBase::initProcess;
    using DControllerBase::getProcess;

private:
    NakedD2Controller() { }
};

/// @brief Fixture class intended for testin control channel in D2.
class CtrlChannelD2Test : public ::testing::Test {
public:

    /// @brief Path to the UNIX socket being used to communicate with the server.
    string socket_path_;

    /// @brief Reference to the base controller object.
    DControllerBasePtr& server_;

    /// @brief Cast controller object.
    NakedD2Controller* get() {
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
            socket_path_ = string(TEST_DATA_BUILDDIR) + "/d2.sock";
        }
        ::remove(socket_path_.c_str());
    }

    /// @brief Destructor.
    ~CtrlChannelD2Test() {
        // Include deregister & co.
        server_.reset();

        // Remove files.
        ::remove(CFG_TEST_FILE);
        ::remove(socket_path_.c_str());
    }

    /// @brief Returns pointer to the server's IO service.
    ///
    /// @return Pointer to the server's IO service or null pointer if the
    /// hasn't been created server.
    IOServicePtr getIOService() {
        return (server_ ? get()->getIOService() : IOServicePtr());
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

    /// @brief Convenience method for invoking standard, valid launch.
    ///
    /// This method sets up a timed run of the D2Controller::launch.
    /// It does the following:
    ///  - It creates command line argument variables argc/argv
    ///  - Creates the config file with the given content.
    ///  - Schedules a shutdown time timer to call D2ontroller::executeShutdown
    ///    after the interval
    ///  - Invokes D2Controller::launch() with the command line arguments
    ///
    /// @param config configuration file content to write before calling launch

    /// @param run_time_ms  maximum amount of time to allow runProcess()
    ///        to continue.
    void runWithConfig(const string& config, int run_time_ms) {
        /// write config file.
        ofstream out(CFG_TEST_FILE, ios::trunc);
        ASSERT_TRUE(out.is_open());
        out << "{ \"DhcpDdns\":\n" << config << "\n}\n";
        out.close();

        // Shutdown (without error) after runtime.
        IntervalTimer timer(*getIOService());
        auto genShutdownCallback = [this]() {
            ElementPtr arg_set;
            server_->shutdownHandler(SHUT_DOWN_COMMAND, arg_set);
        };
        timer.setup(genShutdownCallback, run_time_ms);
        
        char* argv[] = { const_cast<char*>("progName"),
                         const_cast<char*>("-c"),
                         const_cast<char*>(CFG_TEST_FILE),
                         const_cast<char*>("-d") };
        server_->launch(4, argv, false);
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
        ASSERT_NO_THROW(get()->initProcess());
        D2ProcessPtr proc = boost::dynamic_pointer_cast<D2Process>(get()->getProcess());
        ASSERT_TRUE(proc);
        ConstElementPtr answer = proc->configure(config, false);
        ASSERT_TRUE(answer);

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
    ASSERT_NO_THROW(get()->initProcess());
    D2ProcessPtr proc = boost::dynamic_pointer_cast<D2Process>(get()->getProcess());
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
    EXPECT_EQ(2, status);
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
    EXPECT_EQ(2, status);
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
    EXPECT_EQ(2, status);
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
    EXPECT_TRUE(command_list.find("\"config-write\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"shutdown\"") != string::npos);
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

// Tests that the server properly responds to shtudown command.
TEST_F(CtrlChannelD2Test, shutdown) {
    EXPECT_NO_THROW(createUnixChannelServer());
    string response;

    sendUnixCommand("{ \"command\": \"shutdown\" }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Shutdown initiated, type is: normal\" }",
              response);
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
    ASSERT_NO_THROW(get()->initProcess());
    D2ProcessPtr proc = boost::dynamic_pointer_cast<D2Process>(get()->getProcess());
    ASSERT_TRUE(proc);
    ConstElementPtr answer = proc->configure(config, false);
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration committed.\" }",
              answer->str());
    
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
    cerr << os.str();
    EXPECT_EQ("{ \"result\": 1, \"text\": \"element: tsig-keys : missing parameter 'name' (<wire>:9:14)<wire>:8:23\" }",
              response);

    // Check that the config was not lost.
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
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration seems sane.\" }",
              response);

    // Check that the config was not applied.
    keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    EXPECT_EQ(1, keys->size());
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

// TODO: concurrentConnections, longCommand, longResponse,
//       connectionTimeoutPartialCommand, connectionTimeoutNoData

} // End of anonymous namespace
