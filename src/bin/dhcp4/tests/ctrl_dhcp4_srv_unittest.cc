// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcp/dhcp4.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <hooks/hooks_manager.h>
#include <log/logger_support.h>
#include <stats/stats_mgr.h>
#include <testutils/io_utils.h>
#include <testutils/unix_control_client.h>

#include "marker_file.h"
#include "test_libraries.h"

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>

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

class NakedControlledDhcpv4Srv: public ControlledDhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:
    NakedControlledDhcpv4Srv():ControlledDhcpv4Srv(0) { }

    /// Expose internal methods for the sake of testing
    using Dhcpv4Srv::receivePacket;
};

/// @brief Fixture class intended for testin control channel in the DHCPv4Srv
class CtrlChannelDhcpv4SrvTest : public ::testing::Test {
public:

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
            socket_path_ = string(TEST_DATA_BUILDDIR) + "/kea4.sock";
        }
        reset();
    }

    /// @brief Destructor
    ~CtrlChannelDhcpv4SrvTest() {
        LeaseMgrFactory::destroy();
        StatsMgr::instance().removeAll();
        server_.reset();
        reset();
    };

    void createUnixChannelServer() {
        ::remove(socket_path_.c_str());

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
        ::remove(socket_path_.c_str());
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

        // Connect and then call server's receivePacket() so it can
        // detect the control socket connect and call the  accept handler
        ASSERT_TRUE(client->connectToServer(socket_path_));
        ASSERT_NO_THROW(server_->receivePacket(0));

        // Send the command and then call server's receivePacket() so it can
        // detect the inbound data and call the read handler
        ASSERT_TRUE(client->sendCommand(command));
        ASSERT_NO_THROW(server_->receivePacket(0));

        // Read the response generated by the server. Note that getResponse
        // only fails if there an IO error or no response data was present.
        // It is not based on the response content.
        ASSERT_TRUE(client->getResponse(response));

        // Now disconnect and process the close event
        client->disconnectFromServer();
        ASSERT_NO_THROW(server_->receivePacket(0));
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
    std::vector<std::string> loaded_libraries =
        HooksManager::getLibraryNames();
    ASSERT_TRUE(extractNames(libraries) == loaded_libraries);

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
    EXPECT_TRUE(command_list.find("\"config-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-set\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"config-write\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"leases-reclaim\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"libreload\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"shutdown\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-remove\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-remove-all\"") != string::npos);
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
              "\"text\": \"error: unexpected character u in <string>:1:2\" }",
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

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command
TEST_F(CtrlChannelDhcpv4SrvTest, controlLeasesReclaim) {
    createUnixChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    HWAddrPtr hwaddr0(new HWAddr(HWAddr::fromText("00:01:02:03:04:05")));
    Lease4Ptr lease0(new Lease4(IOAddress("10.0.0.1"), hwaddr0,
                                ClientIdPtr(), 60, 10, 20,
                                time(NULL) - 100, SubnetID(1)));
    HWAddrPtr hwaddr1(new HWAddr(HWAddr::fromText("01:02:03:04:05:06")));
    Lease4Ptr lease1(new Lease4(IOAddress("10.0.0.2"), hwaddr1,
                                ClientIdPtr(), 60, 10, 20,
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

// This test verifies that the DHCP server handles version-get commands
TEST_F(CtrlChannelDhcpv4SrvTest, getversion) {
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

// This test verifies that the DHCP server immediately removed expired
// This test verifies that the DHCP server immediately removed expired
// leases on leases-reclaim command with remove = true
TEST_F(CtrlChannelDhcpv4SrvTest, controlLeasesReclaimRemove) {
    createUnixChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    HWAddrPtr hwaddr0(new HWAddr(HWAddr::fromText("00:01:02:03:04:05")));
    Lease4Ptr lease0(new Lease4(IOAddress("10.0.0.1"), hwaddr0,
                                ClientIdPtr(), 60, 10, 20,
                                time(NULL) - 100, SubnetID(1)));
    HWAddrPtr hwaddr1(new HWAddr(HWAddr::fromText("01:02:03:04:05:06")));
    Lease4Ptr lease1(new Lease4(IOAddress("10.0.0.2"), hwaddr1,
                                ClientIdPtr(), 60, 10, 20,
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
    EXPECT_FALSE(lease0);
    EXPECT_FALSE(lease1);
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
    EXPECT_EQ("{ \"arguments\": {  }, \"result\": 0 }", response);

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
        "       \"expired-leases-processing\": { \n"
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
        "               {\"BOGUS\": \"192.2.2.0/24\", \n"
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
              "parameter is missing for a subnet being configured (<string>:20:17)\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

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
    checkListCommands(rsp, "config-get");
    checkListCommands(rsp, "config-reload");
    checkListCommands(rsp, "config-set");
    checkListCommands(rsp, "config-write");
    checkListCommands(rsp, "list-commands");
    checkListCommands(rsp, "leases-reclaim");
    checkListCommands(rsp, "libreload");
    checkListCommands(rsp, "shutdown");
    checkListCommands(rsp, "statistic-get");
    checkListCommands(rsp, "statistic-get-all");
    checkListCommands(rsp, "statistic-remove");
    checkListCommands(rsp, "statistic-remove-all");
    checkListCommands(rsp, "statistic-reset");
    checkListCommands(rsp, "statistic-reset-all");
    checkListCommands(rsp, "version-get");
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
        "       \"expired-leases-processing\": { \n"
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
        "               {\"BOGUS\": \"192.2.2.0/24\", \n"
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
              "\"text\": \"subnet configuration failed: mandatory 'subnet' "
              "parameter is missing for a subnet being configured (<string>:20:17)\" }",
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

    // Send the config-test command
    sendUnixCommand(os.str(), response);

    // Verify the control channel socket still exists.
    EXPECT_TRUE(fileExists(socket_path_));

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration seems sane. "
              "Control-socket, hook-libraries, and D2 configuration were "
              "sanity checked, but not applied.\" }",
              response);

    // Check that the config was not applied
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}
                    
// Tests if config-write can be called without any parameters.
TEST_F(CtrlChannelDhcpv4SrvTest, writeConfigNoFilename) {
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
TEST_F(CtrlChannelDhcpv4SrvTest, writeConfigFilename) {
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
    EXPECT_EQ("{ \"result\": 1, \"text\": \"Config reload failed:"
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
    EXPECT_EQ("{ \"result\": 1, \"text\": \"Config reload failed:"
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

} // End of anonymous namespace
