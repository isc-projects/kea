// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <hooks/hooks_manager.h>
#include <log/logger_support.h>
#include <stats/stats_mgr.h>
#include <util/boost_time_utils.h>
#include <testutils/io_utils.h>
#include <testutils/unix_control_client.h>
#include <testutils/sandbox.h>

#include "marker_file.h"
#include "test_libraries.h"

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::stats;
using namespace isc::test;

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

class NakedControlledDhcpv4Srv: public ControlledDhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:
    NakedControlledDhcpv4Srv():ControlledDhcpv4Srv(0) {
        CfgMgr::instance().setFamily(AF_INET);
    }

    /// Expose internal methods for the sake of testing
    using Dhcpv4Srv::receivePacket;
    using Dhcpv4Srv::network_state_;
};

/// @brief Fixture class intended for testing control channel in the DHCPv4Srv
class CtrlChannelDhcpv4SrvTest : public ::testing::Test {
public:
    isc::test::Sandbox sandbox;

    /// @brief Path to the UNIX socket being used to communicate with the server
    std::string socket_path_;

    /// @brief Pointer to the tested server object
    boost::shared_ptr<NakedControlledDhcpv4Srv> server_;

    /// @brief Default constructor
    ///
    /// Sets socket path to its default value.
    CtrlChannelDhcpv4SrvTest() {
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path_ = string(env) + "/kea4.sock";
        } else {
            socket_path_ = sandbox.join("kea4.sock");
        }
        reset();
    }

    /// @brief Destructor
    ~CtrlChannelDhcpv4SrvTest() {
        LeaseMgrFactory::destroy();
        StatsMgr::instance().removeAll();

        CommandMgr::instance().closeCommandSocket();
        CommandMgr::instance().deregisterAll();
        CommandMgr::instance().setConnectionTimeout(TIMEOUT_DHCP_SERVER_RECEIVE_COMMAND);

        server_.reset();
    };

    /// @brief Returns pointer to the server's IO service.
    ///
    /// @return Pointer to the server's IO service or null pointer if the server
    /// hasn't been created.
    IOServicePtr getIOService() {
        return (server_ ? server_->getIOService() : IOServicePtr());
    }

    void createUnixChannelServer() {
        static_cast<void>(::remove(socket_path_.c_str()));

        // Just a simple config. The important part here is the socket
        // location information.
        std::string header =
            "{"
            "    \"interfaces-config\": {"
            "        \"interfaces\": [ \"*\" ]"
            "    },"
            "    \"expired-leases-processing\": {"
            "         \"reclaim-timer-wait-time\": 60,"
            "         \"hold-reclaimed-time\": 500,"
            "         \"flush-reclaimed-timer-wait-time\": 60"
            "    },"
            "    \"rebind-timer\": 2000, "
            "    \"renew-timer\": 1000, "
            "    \"subnet4\": [ ],"
            "    \"valid-lifetime\": 4000,"
            "    \"control-socket\": {"
            "        \"socket-type\": \"unix\","
            "        \"socket-name\": \"";

        std::string footer =
            "\"    },"
            "    \"lease-database\": {"
            "       \"type\": \"memfile\", \"persist\": false }"
            "}";

        // Fill in the socket-name value with socket_path_  to
        // make the actual configuration text.
        std::string config_txt = header + socket_path_  + footer;

        ASSERT_NO_THROW(server_.reset(new NakedControlledDhcpv4Srv()));

        ConstElementPtr config;
        ASSERT_NO_THROW(config = parseDHCP4(config_txt));
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
        ASSERT_GT(isc::config::CommandMgr::instance().getControlSocketFD(), -1);
    }


    /// @brief Reset hooks data
    ///
    /// Resets the data for the hooks-related portion of the test by ensuring
    /// that no libraries are loaded and that any marker files are deleted.
    void reset() {
        // Unload any previously-loaded libraries.
        HooksManager::unloadLibraries();

        // Get rid of any marker files.
        static_cast<void>(remove(LOAD_MARKER_FILE));
        static_cast<void>(remove(UNLOAD_MARKER_FILE));

        IfaceMgr::instance().deleteAllExternalSockets();
        CfgMgr::instance().clear();

        // Remove unix socket file
        static_cast<void>(::remove(socket_path_.c_str()));
    }

    /// @brief Conducts a command/response exchange via UnixCommandSocket
    ///
    /// This method connects to the given server over the given socket path.
    /// If successful, it then sends the given command and retrieves the
    /// server's response.  Note that it calls the server's receivePacket()
    /// method where needed to cause the server to process IO events on
    /// control channel the control channel sockets.
    ///
    /// @param command the command text to execute in JSON form
    /// @param response variable into which the received response should be
    /// placed.
    void sendUnixCommand(const std::string& command, std::string& response) {
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

        // Now disconnect and process the close event
        client->disconnectFromServer();

        ASSERT_NO_THROW(getIOService()->poll());
    }

    /// @brief Checks response for list-commands
    ///
    /// This method checks if the list-commands response is generally sane
    /// and whether specified command is mentioned in the response.
    ///
    /// @param rsp response sent back by the server
    /// @param command command expected to be on the list.
    void checkListCommands(const ConstElementPtr& rsp, const std::string& command) {
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
                // Command found, but that's not enough. Need to continue working
                // through the list to see if there are no duplicates.
                cnt++;
            }
        }

        // Exactly one command on the list is expected.
        EXPECT_EQ(1, cnt) << "Command " << command << " not found";
    }

    /// @brief Check if the answer for write-config command is correct
    ///
    /// @param response_txt response in text form (as read from the control socket)
    /// @param exp_status expected status (0 success, 1 failure)
    /// @param exp_txt for success cases this defines the expected filename,
    ///                for failure cases this defines the expected error message
    void checkConfigWrite(const std::string& response_txt, int exp_status,
                          const std::string& exp_txt = "") {

        ConstElementPtr rsp;
        EXPECT_NO_THROW(rsp = Element::fromJSON(response_txt));
        ASSERT_TRUE(rsp);

        int status;
        ConstElementPtr params = parseAnswer(status, rsp);
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
        return (createAnswer(0, "long command received ok"));
    }

    /// @brief Command handler which generates long response
    ///
    /// This handler generates a large response (over 400kB). It includes
    /// a list of randomly generated strings to make sure that the test
    /// can catch out of order delivery.
    static ConstElementPtr longResponseHandler(const std::string&,
                                               const ConstElementPtr&) {
        ElementPtr arguments = Element::createList();
        for (unsigned i = 0; i < 80000; ++i) {
            std::ostringstream s;
            s << std::setw(5) << i;
            arguments->add(Element::create(s.str()));
        }
        return (createAnswer(0, arguments));
    }
};

TEST_F(CtrlChannelDhcpv4SrvTest, commands) {

    ASSERT_NO_THROW(
        server_.reset(new NakedControlledDhcpv4Srv());
    );

    // Use empty parameters list
    ElementPtr params(new isc::data::MapElement());
    int rcode = -1;

    // Case 1: send bogus command
    ConstElementPtr result = ControlledDhcpv4Srv::processCommand("blah", params);
    ConstElementPtr comment = parseAnswer(rcode, result);
    EXPECT_EQ(1, rcode); // expect failure (no such command as blah)

    // Case 2: send shutdown command without any parameters
    result = ControlledDhcpv4Srv::processCommand("shutdown", params);
    comment = parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // expect success

    const pid_t pid(getpid());
    ConstElementPtr x(new isc::data::IntElement(pid));
    params->set("pid", x);

    // Case 3: send shutdown command with 1 parameter: pid
    result = ControlledDhcpv4Srv::processCommand("shutdown", params);
    comment = parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // expect success
}

// Check that the "libreload" command will reload libraries
TEST_F(CtrlChannelDhcpv4SrvTest, libreload) {
    createUnixChannelServer();

    // Ensure no marker files to start with.
    ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Load two libraries
    HookLibsCollection libraries;
    libraries.push_back(make_pair(CALLOUT_LIBRARY_1, ConstElementPtr()));
    libraries.push_back(make_pair(CALLOUT_LIBRARY_2, ConstElementPtr()));
    HooksManager::loadLibraries(libraries);

    // Check they are loaded.
    HookLibsCollection loaded_libraries =
        HooksManager::getLibraryInfo();
    ASSERT_TRUE(libraries == loaded_libraries);

    // ... which also included checking that the marker file created by the
    // load functions exists and holds the correct value (of "12" - the
    // first library appends "1" to the file, the second appends "2"). Also
    // check that the unload marker file does not yet exist.
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "12"));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Now execute the "libreload" command.  This should cause the libraries
    // to unload and to reload.
    std::string response;
    sendUnixCommand("{ \"command\": \"libreload\" }", response);
    EXPECT_EQ("{ \"result\": 0, "
              "\"text\": \"Hooks libraries successfully reloaded.\" }"
              , response);

    // Check that the libraries have unloaded and reloaded.  The libraries are
    // unloaded in the reverse order to which they are loaded.  When they load,
    // they should append information to the loading marker file.
    EXPECT_TRUE(checkMarkerFile(UNLOAD_MARKER_FILE, "21"));
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "1212"));
}

// This test checks which commands are registered by the DHCPv4 server.
TEST_F(CtrlChannelDhcpv4SrvTest, commandsRegistration) {

    ConstElementPtr list_cmds = createCommand("list-commands");
    ConstElementPtr answer;

    // By default the list should be empty (except the standard list-commands
    // supported by the CommandMgr itself)
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());

    // Created server should register several additional commands.
    ASSERT_NO_THROW(
        server_.reset(new NakedControlledDhcpv4Srv());
    );

    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);

    ASSERT_TRUE(answer->get("arguments"));
    std::string command_list = answer->get("arguments")->str();

    EXPECT_TRUE(command_list.find("\"list-commands\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"build-report\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-backend-pull\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-set\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-write\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"leases-reclaim\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"libreload\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"server-tag-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"shutdown\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-remove\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-remove-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-reset\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-reset-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-sample-age-set\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-sample-age-set-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-sample-count-set\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-sample-count-set-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"status-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"version-get\"") != string::npos);

    // Ok, and now delete the server. It should deregister its commands.
    server_.reset();

    // The list should be (almost) empty again.
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());
}

// Tests that the server properly responds to invalid commands sent
// via ControlChannel
TEST_F(CtrlChannelDhcpv4SrvTest, controlChannelNegative) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"bogus\" }", response);
    EXPECT_EQ("{ \"result\": 2,"
              " \"text\": \"'bogus' command not supported.\" }", response);

    sendUnixCommand("utter nonsense", response);
    EXPECT_EQ("{ \"result\": 1, "
              "\"text\": \"invalid first character u\" }",
              response);
}

// Tests that the server properly responds to shtudown command sent
// via ControlChannel
TEST_F(CtrlChannelDhcpv4SrvTest, controlChannelShutdown) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"shutdown\" }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Shutting down.\" }",response);
}

// Tests that the server properly responds to statistics commands.  Note this
// is really only intended to verify that the appropriate Statistics handler
// is called based on the command.  It is not intended to be an exhaustive
// test of Dhcpv4 statistics.
TEST_F(CtrlChannelDhcpv4SrvTest, controlChannelStats) {
    createUnixChannelServer();
    std::string response;

    // Check statistic-get
    sendUnixCommand("{ \"command\" : \"statistic-get\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\" }}", response);
    EXPECT_EQ("{ \"arguments\": {  }, \"result\": 0 }", response);

    // Check statistic-get-all
    sendUnixCommand("{ \"command\" : \"statistic-get-all\", "
                    "  \"arguments\": {}}", response);

    std::set<std::string> initial_stats = {
        "pkt4-received",
        "pkt4-discover-received",
        "pkt4-offer-received",
        "pkt4-request-received",
        "pkt4-ack-received",
        "pkt4-nak-received",
        "pkt4-release-received",
        "pkt4-decline-received",
        "pkt4-inform-received",
        "pkt4-unknown-received",
        "pkt4-sent",
        "pkt4-offer-sent",
        "pkt4-ack-sent",
        "pkt4-nak-sent",
        "pkt4-parse-failed",
        "pkt4-receive-drop"
    };

    // preparing the schema which check if all statistics are set to zero
    std::ostringstream s;
    s << "{ \"arguments\": { ";
    for (auto st = initial_stats.begin(); st != initial_stats.end();) {
        s << "\"" << *st << "\": [ [ 0, \"";
        s << isc::util::ptimeToText(StatsMgr::instance().getObservation(*st)->getInteger().second);
        s << "\" ] ]";
        if (++st != initial_stats.end()) {
            s << ", ";
        }
    }
    s << " }, \"result\": 0 }";

    auto stats_get_all = s.str();

    EXPECT_EQ(stats_get_all, response);

    // Check statistic-reset
    sendUnixCommand("{ \"command\" : \"statistic-reset\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\" }}", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'bogus' statistic found\" }",
              response);

    // Check statistic-reset-all
    sendUnixCommand("{ \"command\" : \"statistic-reset-all\", "
                    "  \"arguments\": {}}", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": "
              "\"All statistics reset to neutral values.\" }", response);

    // Check statistic-remove
    sendUnixCommand("{ \"command\" : \"statistic-remove\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\" }}", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'bogus' statistic found\" }",
              response);

    // Check statistic-remove-all
    sendUnixCommand("{ \"command\" : \"statistic-remove-all\", "
                    "  \"arguments\": {}}", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"All statistics removed.\" }",
              response);

    // Check statistic-sample-age-set
    sendUnixCommand("{ \"command\" : \"statistic-sample-age-set\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\", \"duration\": 1245 }}", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'bogus' statistic found\" }",
              response);

    // Check statistic-sample-age-set-all
    sendUnixCommand("{ \"command\" : \"statistic-sample-age-set-all\", "
                    "  \"arguments\": {"
                    "  \"duration\": 1245 }}", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"All statistics duration limit are set.\" }",
              response);

    // Check statistic-sample-count-set
    sendUnixCommand("{ \"command\" : \"statistic-sample-count-set\", "
                    "  \"arguments\": {"
                    "  \"name\":\"bogus\", \"max-samples\": 100 }}", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": \"No 'bogus' statistic found\" }",
              response);

    // Check statistic-sample-count-set-all
    sendUnixCommand("{ \"command\" : \"statistic-sample-count-set-all\", "
                    "  \"arguments\": {"
                    "  \"max-samples\": 100 }}", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"All statistics count limit are set.\" }",
              response);
}

// Check that the "config-set" command will replace current configuration
TEST_F(CtrlChannelDhcpv4SrvTest, configSet) {
    createUnixChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string set_config_txt = "{ \"command\": \"config-set\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp4_cfg_txt =
        "    \"Dhcp4\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
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
        "        \"subnet4\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"192.2.0.0/24\", \n"
        "                \"pools\": [{ \"pool\": \"192.2.0.1-192.2.0.50\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"192.2.1.0/24\", \n"
        "                \"pools\": [{ \"pool\": \"192.2.1.1-192.2.1.50\" }]}\n";
    string bad_subnet =
        "               {\"comment\": \"192.2.2.0/24\", \n"
        "                \"pools\": [{ \"pool\": \"192.2.2.1-192.2.2.50\" }]}\n";
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
        "        \"space\": \"dhcp4\",\n"
        "        \"encapsulate\": \"\"\n"
        "    }\n"
        "]\n";
    string option_data =
        "    ,\"option-data\": [\n"
        "    {\n"
        "        \"name\": \"foo\",\n"
        "        \"code\": 163,\n"
        "        \"space\": \"dhcp4\",\n"
        "        \"csv-format\": true,\n"
        "        \"data\": \"12345\"\n"
        "    }\n"
        "]\n";
    string control_socket_header =
        "       ,\"control-socket\": { \n"
        "       \"socket-type\": \"unix\", \n"
        "       \"socket-name\": \"";
    string control_socket_footer =
        "\"   \n} \n";
    string logger_txt =
        "    \"Logging\": { \n"
        "        \"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output_options\": [{ \n"
        "                \"output\": \"/dev/null\" \n"
        "            }] \n"
        "        }] \n"
        "    } \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << set_config_txt << ","
        << args_txt
        << dhcp4_cfg_txt
        << subnet1
        << subnet_footer
        << option_def
        << option_data
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp4
        << ","
        << logger_txt
        << "}}";

    // Send the config-set command
    std::string response;
    sendUnixCommand(os.str(), response);

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was indeed applied.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

    OptionDefinitionPtr def = LibDHCP::getRuntimeOptionDef("dhcp4", 163);
    ASSERT_TRUE(def);

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << set_config_txt << ","
        << args_txt
        << dhcp4_cfg_txt
        << bad_subnet
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp4
        "}}";

    // Send the config-set command
    sendUnixCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("{ \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' "
              "parameter is missing for a subnet being configured (<wire>:19:17)\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

    def = LibDHCP::getRuntimeOptionDef("dhcp4", 163);
    ASSERT_TRUE(def);

    // Create a valid config with two subnets and no command channel.
    // It should succeed, client should still receive the response
    os.str("");
    os << set_config_txt << ","
        << args_txt
        << dhcp4_cfg_txt
        << subnet1
        << ",\n"
        << subnet2
        << subnet_footer
        << "}\n"                      // close dhcp4
        << "}}";

    // Verify the control channel socket exists.
    ASSERT_TRUE(fileExists(socket_path_));

    // Send the config-set command.
    sendUnixCommand(os.str(), response);

    // Verify the control channel socket no longer exists.
    EXPECT_FALSE(fileExists(socket_path_));

    // With no command channel, should still receive the response.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(2, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Tests if the server returns its configuration using config-get.
// Note there are separate tests that verify if toElement() called by the
// config-get handler are actually converting the configuration correctly.
TEST_F(CtrlChannelDhcpv4SrvTest, configGet) {
    createUnixChannelServer();
    std::string response;

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
    EXPECT_TRUE(cfg->get("Dhcp4"));
}

// Verify that the "config-test" command will do what we expect.
TEST_F(CtrlChannelDhcpv4SrvTest, configTest) {
    createUnixChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string set_config_txt = "{ \"command\": \"config-set\" \n";
    string config_test_txt = "{ \"command\": \"config-test\" \n";
    string args_txt = " \"arguments\": { \n";
    string dhcp4_cfg_txt =
        "    \"Dhcp4\": { \n"
        "        \"interfaces-config\": { \n"
        "            \"interfaces\": [\"*\"] \n"
        "        },   \n"
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
        "        \"subnet4\": [ \n";
    string subnet1 =
        "               {\"subnet\": \"192.2.0.0/24\", \n"
        "                \"pools\": [{ \"pool\": \"192.2.0.1-192.2.0.50\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"192.2.1.0/24\", \n"
        "                \"pools\": [{ \"pool\": \"192.2.1.1-192.2.1.50\" }]}\n";
    string bad_subnet =
        "               {\"comment\": \"192.2.2.0/24\", \n"
        "                \"pools\": [{ \"pool\": \"192.2.2.1-192.2.2.50\" }]}\n";
    string subnet_footer =
        "          ] \n";
    string control_socket_header =
        "       ,\"control-socket\": { \n"
        "       \"socket-type\": \"unix\", \n"
        "       \"socket-name\": \"";
    string control_socket_footer =
        "\"   \n} \n";
    string logger_txt =
        "    \"Logging\": { \n"
        "        \"loggers\": [ { \n"
        "            \"name\": \"kea\", \n"
        "            \"severity\": \"FATAL\", \n"
        "            \"output_options\": [{ \n"
        "                \"output\": \"/dev/null\" \n"
        "            }] \n"
        "        }] \n"
        "    } \n";

    std::ostringstream os;

    // Create a valid config with all the parts should parse
    os << set_config_txt << ","
        << args_txt
        << dhcp4_cfg_txt
        << subnet1
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp4
        << ","
        << logger_txt
        << "}}";

    // Send the config-set command
    std::string response;
    sendUnixCommand(os.str(), response);

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was indeed applied.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << config_test_txt << ","
        << args_txt
        << dhcp4_cfg_txt
        << bad_subnet
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp4
        "}}";

    // Send the config-test command
    sendUnixCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("{ \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' parameter "
              "is missing for a subnet being configured (<wire>:19:17)\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a valid config with two subnets and no command channel.
    os.str("");
    os << config_test_txt << ","
        << args_txt
        << dhcp4_cfg_txt
        << subnet1
        << ",\n"
        << subnet2
        << subnet_footer
        << "}\n"                      // close dhcp4
        << "}}";

    // Verify the control channel socket exists.
    ASSERT_TRUE(fileExists(socket_path_));

    // Send the config-test command.
    sendUnixCommand(os.str(), response);

    // Verify the control channel socket still exists.
    EXPECT_TRUE(fileExists(socket_path_));

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration seems sane. "
              "Control-socket, hook-libraries, and D2 configuration were "
              "sanity checked, but not applied.\" }",
              response);

    // Check that the config was not applied.
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// This test verifies that the DHCP server handles version-get commands
TEST_F(CtrlChannelDhcpv4SrvTest, getVersion) {
    createUnixChannelServer();

    std::string response;

    // Send the version-get command
    sendUnixCommand("{ \"command\": \"version-get\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the build-report command
    sendUnixCommand("{ \"command\": \"build-report\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("GTEST_VERSION") != string::npos);
}

// This test verifies that the DHCP server handles server-tag-get command
TEST_F(CtrlChannelDhcpv4SrvTest, serverTagGet) {
    createUnixChannelServer();

    std::string response;
    std::string expected;

    // Send the server-tag-get command
    sendUnixCommand("{ \"command\": \"server-tag-get\" }", response);
    expected = "{ \"arguments\": { \"server-tag\": \"\" }, \"result\": 0 }";
    EXPECT_EQ(expected, response);

    // Set a value to the server tag
    CfgMgr::instance().getCurrentCfg()->setServerTag("foobar");

    // Retry...
    sendUnixCommand("{ \"command\": \"server-tag-get\" }", response);
    expected = "{ \"arguments\": { \"server-tag\": \"foobar\" }, \"result\": 0 }";
}

// This test verifies that the DHCP server handles status-get commands
TEST_F(CtrlChannelDhcpv4SrvTest, statusGet) {
    createUnixChannelServer();

    // start_ is initialized by init.
    ASSERT_THROW(server_->init("/no/such/file"), BadValue);

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
}

// This test verifies that the DHCP server handles config-backend-pull command
TEST_F(CtrlChannelDhcpv4SrvTest, configBackendPull) {
    createUnixChannelServer();

    std::string response;
    std::string expected;

    // Send the config-backend-pull command. Note there is no configured backed.
    sendUnixCommand("{ \"command\": \"config-backend-pull\" }", response);
    expected = "{ \"result\": 3, \"text\": \"No config backend.\" }";
    EXPECT_EQ(expected, response);
}

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command
TEST_F(CtrlChannelDhcpv4SrvTest, controlLeasesReclaim) {
    createUnixChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    HWAddrPtr hwaddr0(new HWAddr(HWAddr::fromText("00:01:02:03:04:05")));
    Lease4Ptr lease0(new Lease4(IOAddress("10.0.0.1"), hwaddr0,
                                ClientIdPtr(), 60,
                                time(NULL) - 100, SubnetID(1)));
    HWAddrPtr hwaddr1(new HWAddr(HWAddr::fromText("01:02:03:04:05:06")));
    Lease4Ptr lease1(new Lease4(IOAddress("10.0.0.2"), hwaddr1,
                                ClientIdPtr(), 60,
                                time(NULL) - 100, SubnetID(1)));

    // Add leases to the database.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease0));
    ASSERT_NO_THROW(lease_mgr.addLease(lease1));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease4(IOAddress("10.0.0.1")));
    ASSERT_TRUE(lease_mgr.getLease4(IOAddress("10.0.0.2")));

    // No arguments
    std::string response;
    sendUnixCommand("{ \"command\": \"leases-reclaim\" }", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": "
              "\"Missing mandatory 'remove' parameter.\" }", response);

    // Bad argument name
    sendUnixCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"reclaim\": true } }", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": "
              "\"Missing mandatory 'remove' parameter.\" }", response);

    // Bad remove argument type
    sendUnixCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": \"bogus\" } }", response);
    EXPECT_EQ("{ \"result\": 1, \"text\": "
              "\"'remove' parameter expected to be a boolean.\" }", response);

    // Send the command
    sendUnixCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": false } }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": "
              "\"Reclamation of expired leases is complete.\" }", response);

    // Leases should be reclaimed, but not removed
    ASSERT_NO_THROW(lease0 = lease_mgr.getLease4(IOAddress("10.0.0.1")));
    ASSERT_NO_THROW(lease1 = lease_mgr.getLease4(IOAddress("10.0.0.2")));
    ASSERT_TRUE(lease0);
    ASSERT_TRUE(lease1);
    EXPECT_TRUE(lease0->stateExpiredReclaimed());
    EXPECT_TRUE(lease1->stateExpiredReclaimed());
}

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command with remove = true
TEST_F(CtrlChannelDhcpv4SrvTest, controlLeasesReclaimRemove) {
    createUnixChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    HWAddrPtr hwaddr0(new HWAddr(HWAddr::fromText("00:01:02:03:04:05")));
    Lease4Ptr lease0(new Lease4(IOAddress("10.0.0.1"), hwaddr0,
                                ClientIdPtr(), 60,
                                time(NULL) - 100, SubnetID(1)));
    HWAddrPtr hwaddr1(new HWAddr(HWAddr::fromText("01:02:03:04:05:06")));
    Lease4Ptr lease1(new Lease4(IOAddress("10.0.0.2"), hwaddr1,
                                ClientIdPtr(), 60,
                                time(NULL) - 100, SubnetID(1)));

    // Add leases to the database.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease0));
    ASSERT_NO_THROW(lease_mgr.addLease(lease1));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease4(IOAddress("10.0.0.1")));
    ASSERT_TRUE(lease_mgr.getLease4(IOAddress("10.0.0.2")));

    // Send the command
    std::string response;
    sendUnixCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": true } }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": "
              "\"Reclamation of expired leases is complete.\" }", response);

    // Leases should have been removed.
    ASSERT_NO_THROW(lease0 = lease_mgr.getLease4(IOAddress("10.0.0.1")));
    ASSERT_NO_THROW(lease1 = lease_mgr.getLease4(IOAddress("10.0.0.2")));
    ASSERT_FALSE(lease0);
    ASSERT_FALSE(lease1);
}

// Tests that the server properly responds to shtudown command sent
// via ControlChannel
TEST_F(CtrlChannelDhcpv4SrvTest, listCommands) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"list-commands\" }", response);

    ConstElementPtr rsp;
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));

    // We expect the server to report at least the following commands:
    checkListCommands(rsp, "build-report");
    checkListCommands(rsp, "config-backend-pull");
    checkListCommands(rsp, "config-get");
    checkListCommands(rsp, "config-reload");
    checkListCommands(rsp, "config-set");
    checkListCommands(rsp, "config-test");
    checkListCommands(rsp, "config-write");
    checkListCommands(rsp, "list-commands");
    checkListCommands(rsp, "leases-reclaim");
    checkListCommands(rsp, "libreload");
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

// Tests if config-write can be called without any parameters.
TEST_F(CtrlChannelDhcpv4SrvTest, configWriteNoFilename) {
    createUnixChannelServer();
    std::string response;

    // This is normally set by the command line -c parameter.
    server_->setConfigFile("test1.json");

    // If the filename is not explicitly specified, the name used
    // in -c command line switch is used.
    sendUnixCommand("{ \"command\": \"config-write\" }", response);

    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test1.json");
    ::remove("test1.json");
}

// Tests if config-write can be called with a valid filename as parameter.
TEST_F(CtrlChannelDhcpv4SrvTest, configWriteFilename) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"config-write\", "
                    "\"arguments\": { \"filename\": \"test2.json\" } }", response);
    checkConfigWrite(response, CONTROL_RESULT_SUCCESS, "test2.json");
    ::remove("test2.json");
}

// Tests if config-reload attempts to reload a file and reports that the
// file is missing.
TEST_F(CtrlChannelDhcpv4SrvTest, configReloadMissingFile) {
    createUnixChannelServer();
    std::string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("test6.json");

    // Tell the server to reload its configuration. It should attempt to load
    // test6.json (and fail, because the file is not there).
    sendUnixCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload was rejected.
    EXPECT_EQ("{ \"result\": 1, \"text\": \"Config reload failed: "
              "configuration error using file 'test6.json': Unable to open file "
              "test6.json\" }",
              response);
}

// Tests if config-reload attempts to reload a file and reports that the
// file is not a valid JSON.
TEST_F(CtrlChannelDhcpv4SrvTest, configReloadBrokenFile) {
    createUnixChannelServer();
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
    sendUnixCommand("{ \"command\": \"config-reload\" }", response);

    // Verify the reload will fail.
    EXPECT_EQ("{ \"result\": 1, \"text\": \"Config reload failed: "
              "configuration error using file 'test7.json': "
              "test7.json:1.1: Invalid character: g\" }",
              response);

    ::remove("test7.json");
}

// Tests if config-reload attempts to reload a file and reports that the
// file is loaded correctly.
TEST_F(CtrlChannelDhcpv4SrvTest, configReloadValid) {
    createUnixChannelServer();
    std::string response;

    // This is normally set to whatever value is passed to -c when the server is
    // started, but we're not starting it that way, so need to set it by hand.
    server_->setConfigFile("test8.json");

    // Ok, enough fooling around. Let's create a valid config.
    const std::string cfg_txt =
        "{ \"Dhcp4\": {"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"subnet4\": ["
        "        { \"subnet\": \"192.0.2.0/24\" },"
        "        { \"subnet\": \"192.0.3.0/24\" }"
        "     ],"
        "    \"valid-lifetime\": 4000,"
        "    \"lease-database\": {"
        "       \"type\": \"memfile\", \"persist\": false }"
        "} }";
    ofstream f("test8.json", ios::trunc);
    f << cfg_txt;
    f.close();

    // This command should reload test8.json config.
    sendUnixCommand("{ \"command\": \"config-reload\" }", response);
    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was indeed applied.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(2, subnets->size());

    ::remove("test8.json");
}

// This test verifies if it is possible to disable DHCP service via command.
TEST_F(CtrlChannelDhcpv4SrvTest, dhcpDisable) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"dhcp-disable\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_FALSE(server_->network_state_->isServiceEnabled());
}

// This test verifies that it is possible to disable DHCP service for a short
// period of time, after which the service is automatically enabled.
TEST_F(CtrlChannelDhcpv4SrvTest, dhcpDisableTemporarily) {
    createUnixChannelServer();
    std::string response;

    // Send a command to disable DHCP service for 3 seconds.
    sendUnixCommand("{"
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
    ConstElementPtr cfg = parseAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    // The service should be disabled.
    EXPECT_FALSE(server_->network_state_->isServiceEnabled());
    // And the timer should be scheduled which counts the time to automatic
    // enabling of the service.
    EXPECT_TRUE(server_->network_state_->isDelayedEnableAll());
}

// This test verifies if it is possible to enable DHCP service via command.
TEST_F(CtrlChannelDhcpv4SrvTest, dhcpEnable) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"dhcp-enable\" }", response);
    ConstElementPtr rsp;

    // The response should be a valid JSON.
    EXPECT_NO_THROW(rsp = Element::fromJSON(response));
    ASSERT_TRUE(rsp);

    int status;
    ConstElementPtr cfg = parseAnswer(status, rsp);
    EXPECT_EQ(CONTROL_RESULT_SUCCESS, status);

    EXPECT_TRUE(server_->network_state_->isServiceEnabled());
}

/// Verify that concurrent connections over the control channel can be
///  established.
/// @todo Future Kea 1.3 tickets will modify the behavior of the CommandMgr
/// such that the server will be able to send response in multiple chunks.
/// This test will need to be extended. For now, the receive and write
/// operations are atomic and there is no conflict between concurrent
/// connections.
TEST_F(CtrlChannelDhcpv4SrvTest, concurrentConnections) {
    createUnixChannelServer();

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

    std::string response;
    // The server should respond ok.
    ASSERT_TRUE(client2->getResponse(response));
    EXPECT_TRUE(response.find("\"result\": 0") != std::string::npos);

    // Disconnect the servers.
    client1->disconnectFromServer();
    client2->disconnectFromServer();
    ASSERT_NO_THROW(getIOService()->poll());
}

// This test verifies that the server can receive and process a large command.
TEST_F(CtrlChannelDhcpv4SrvTest, longCommand) {

    std::ostringstream command;

    // This is the desired size of the command sent to the server (1MB). The
    // actual size sent will be slightly greater than that.
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
            std::ostringstream arg;
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
             boost::bind(&CtrlChannelDhcpv4SrvTest::longCommandHandler,
                         command.str(), _1, _2));
    );

    createUnixChannelServer();

    std::string response;
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
        std::string remaining_data = command.str();
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
TEST_F(CtrlChannelDhcpv4SrvTest, longResponse) {
    // We need to generate large response. The simplest way is to create
    // a command and a handler which will generate some static response
    // of a desired size.
    ASSERT_NO_THROW(
        CommandMgr::instance().registerCommand("foo",
             boost::bind(&CtrlChannelDhcpv4SrvTest::longResponseHandler, _1, _2));
    );

    createUnixChannelServer();

    // The UnixControlClient doesn't have any means to check that the entire
    // response has been received. What we want to do is to generate a
    // reference response using our command handler and then compare
    // what we have received over the unix domain socket with this reference
    // response to figure out when to stop receiving.
    std::string reference_response = longResponseHandler("foo", ConstElementPtr())->str();

    // In this stream we're going to collect out partial responses.
    std::ostringstream response;

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
// takes too long, having received a partial command.
TEST_F(CtrlChannelDhcpv4SrvTest, connectionTimeoutPartialCommand) {
    createUnixChannelServer();

    // Set connection timeout to 2s to prevent long waiting time for the
    // timeout during this test.
    const unsigned short timeout = 2000;
    CommandMgr::instance().setConnectionTimeout(timeout);

    // Server's response will be assigned to this variable.
    std::string response;

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
        std::string command = "{ \"command\": \"foo\" ";
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
    EXPECT_EQ("{ \"result\": 1, \"text\": "
              "\"Connection over control channel timed out, "
              "discarded partial command of 19 bytes\" }", response);
}

// This test verifies that the server signals timeout if the transmission
// takes too long, having received no data from the client.
TEST_F(CtrlChannelDhcpv4SrvTest, connectionTimeoutNoData) {
    createUnixChannelServer();

    // Set connection timeout to 2s to prevent long waiting time for the
    // timeout during this test.
    const unsigned short timeout = 2000;
    CommandMgr::instance().setConnectionTimeout(timeout);

    // Server's response will be assigned to this variable.
    std::string response;

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

        // Having sent nothing let's just wait and see if Server times us out.
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
    EXPECT_EQ("{ \"result\": 1, \"text\": "
              "\"Connection over control channel timed out\" }", response);
}

} // End of anonymous namespace
