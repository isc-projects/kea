// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <hooks/hooks_manager.h>
#include <log/logger_support.h>
#include <stats/stats_mgr.h>
#include <testutils/unix_control_client.h>
#include <testutils/io_utils.h>

#include "marker_file.h"
#include "test_libraries.h"

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <sys/select.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <cstdlib>

using namespace std;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::stats;
using namespace isc::test;

namespace {



class NakedControlledDhcpv6Srv: public ControlledDhcpv6Srv {
    // "Naked" DHCPv6 server, exposes internal fields
public:
    NakedControlledDhcpv6Srv():ControlledDhcpv6Srv(DHCP6_SERVER_PORT + 10000) {
    }

    /// Expose internal methods for the sake of testing
    using Dhcpv6Srv::receivePacket;
};

class CtrlDhcpv6SrvTest : public BaseServerTest {
public:
    CtrlDhcpv6SrvTest()
        : BaseServerTest() {
        reset();
    }

    virtual ~CtrlDhcpv6SrvTest() {
        LeaseMgrFactory::destroy();
        StatsMgr::instance().removeAll();
        reset();
    };


    /// @brief Reset hooks data
    ///
    /// Resets the data for the hooks-related portion of the test by ensuring
    /// that no libraries are loaded and that any marker files are deleted.
    virtual void reset() {
        // Unload any previously-loaded libraries.
        HooksManager::unloadLibraries();

        // Get rid of any marker files.
        static_cast<void>(remove(LOAD_MARKER_FILE));
        static_cast<void>(remove(UNLOAD_MARKER_FILE));
        IfaceMgr::instance().deleteAllExternalSockets();
        CfgMgr::instance().clear();
    }

};

class CtrlChannelDhcpv6SrvTest : public CtrlDhcpv6SrvTest {
public:

    /// @brief Path to the UNIX socket being used to communicate with the server
    std::string socket_path_;

    /// @brief Pointer to the tested server object
    boost::shared_ptr<NakedControlledDhcpv6Srv> server_;

    /// @brief Default constructor
    ///
    /// Sets socket path to its default value.
    CtrlChannelDhcpv6SrvTest() {
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path_ = string(env) + "/kea6.sock";
        } else {
            socket_path_ = string(TEST_DATA_BUILDDIR) + "/kea6.sock";
        }
        reset();
    }

    /// @brief Destructor
    ~CtrlChannelDhcpv6SrvTest() {
        server_.reset();
        reset();
    };

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
            "    \"subnet6\": [ ],"
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

        ASSERT_NO_THROW(server_.reset(new NakedControlledDhcpv6Srv()));

        ConstElementPtr config;
        ASSERT_NO_THROW(config = parseDHCP6(config_txt));
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

    /// @brief Reset
    void reset() {
        CtrlDhcpv6SrvTest::reset();
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
};


TEST_F(CtrlDhcpv6SrvTest, commands) {

    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(DHCP6_SERVER_PORT + 10000))
    );

    // Use empty parameters list
    ElementPtr params(new isc::data::MapElement());
    int rcode = -1;

    // Case 1: send bogus command
    ConstElementPtr result = ControlledDhcpv6Srv::processCommand("blah", params);
    ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
    EXPECT_EQ(1, rcode); // expect failure (no such command as blah)

    // Case 2: send shutdown command without any parameters
    result = ControlledDhcpv6Srv::processCommand("shutdown", params);
    comment = isc::config::parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // expect success

    const pid_t pid(getpid());
    ConstElementPtr x(new isc::data::IntElement(pid));
    params->set("pid", x);

    // Case 3: send shutdown command with 1 parameter: pid
    result = ControlledDhcpv6Srv::processCommand("shutdown", params);
    comment = isc::config::parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // Expect success
}

// Check that the "libreload" command will reload libraries
TEST_F(CtrlChannelDhcpv6SrvTest, libreload) {
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

// Check that the "configReload" command will reload libraries
TEST_F(CtrlDhcpv6SrvTest, configReload) {

    // Sending commands for processing now requires a server that can process
    // them.
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // Now execute the "config-reload" command.  This should cause the libraries
    // to unload and to reload.

    // Use empty parameters list
    // Prepare configuration file.
    string config_txt = "{ \"Dhcp6\": { \"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 0"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }}";

    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseJSON(config_txt));

    // Make sure there are no subnets configured.
    CfgMgr::instance().clear();

    // Now send the command
    int rcode = -1;
    ConstElementPtr result =
        ControlledDhcpv6Srv::processCommand("config-reload", config);
    ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // Expect success

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(3, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

// Check that the "set-config" command will replace current configuration
TEST_F(CtrlChannelDhcpv6SrvTest, set_config) {
    createUnixChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string set_config_txt = "{ \"command\": \"set-config\" \n";
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
        "               {\"subnet\": \"3002::/64\", \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"3003::/64\", \n"
        "                \"pools\": [{ \"pool\": \"3003::100-3003::200\" }]}\n";
    string bad_subnet =
        "               {\"BOGUS\": \"3005::/64\", \n"
        "                \"pools\": [{ \"pool\": \"3005::100-3005::200\" }]}\n";
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
        << dhcp6_cfg_txt
        << subnet1
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp6
        << ","
        << logger_txt
        << "}}";

    // Send the set-config command
    std::string response;
    sendUnixCommand(os.str(), response);

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << set_config_txt << ","
        << args_txt
        << dhcp6_cfg_txt
        << bad_subnet
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp6
        "}}";

    // Send the set-config command
    sendUnixCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("{ \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' parameter is missing for a subnet being configured (<string>:21:17)\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a valid config with two subnets and no command channel.
    // It should succeed but client will not receive a the response
    os.str("");
    os << set_config_txt << ","
        << args_txt
        << dhcp6_cfg_txt
        << subnet1
        << ",\n"
        << subnet2
        << subnet_footer
        << "}\n"                      // close dhcp6
        << "}}";

    /* Verify the control channel socket exists */
    ASSERT_TRUE(fileExists(socket_path_));

    // Send the set-config command
    sendUnixCommand(os.str(), response);

    /* Verify the control channel socket no longer exists */
    EXPECT_FALSE(fileExists(socket_path_));

    // With no command channel, should still receive the response.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(2, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}

  // Verify that the "test-config" command will do what we expect.
TEST_F(CtrlChannelDhcpv6SrvTest, test_config) {
    createUnixChannelServer();

    // Define strings to permutate the config arguments
    // (Note the line feeds makes errors easy to find)
    string set_config_txt = "{ \"command\": \"set-config\" \n";
    string test_config_txt = "{ \"command\": \"test-config\" \n";
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
        "               {\"subnet\": \"3002::/64\", \n"
        "                \"pools\": [{ \"pool\": \"3002::100-3002::200\" }]}\n";
    string subnet2 =
        "               {\"subnet\": \"3003::/64\", \n"
        "                \"pools\": [{ \"pool\": \"3003::100-3003::200\" }]}\n";
    string bad_subnet =
        "               {\"BOGUS\": \"3005::/64\", \n"
        "                \"pools\": [{ \"pool\": \"3005::100-3005::200\" }]}\n";
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
        << dhcp6_cfg_txt
        << subnet1
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp6
        << ","
        << logger_txt
        << "}}";

    // Send the set-config command
    std::string response;
    sendUnixCommand(os.str(), response);

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration successful.\" }",
              response);

    // Check that the config was indeed applied.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a config with malformed subnet that should fail to parse.
    os.str("");
    os << test_config_txt << ","
        << args_txt
        << dhcp6_cfg_txt
        << bad_subnet
        << subnet_footer
        << control_socket_header
        << socket_path_
        << control_socket_footer
        << "}\n"                      // close dhcp6
        "}}";

    // Send the test-config command
    sendUnixCommand(os.str(), response);

    // Should fail with a syntax error
    EXPECT_EQ("{ \"result\": 1, "
              "\"text\": \"subnet configuration failed: mandatory 'subnet' parameter is missing for a subnet being configured (<string>:21:17)\" }",
              response);

    // Check that the config was not lost
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Create a valid config with two subnets and no command channel.
    os.str("");
    os << test_config_txt << ","
        << args_txt
        << dhcp6_cfg_txt
        << subnet1
        << ",\n"
        << subnet2
        << subnet_footer
        << "}\n"                      // close dhcp6
        << "}}";

    /* Verify the control channel socket exists */
    ASSERT_TRUE(fileExists(socket_path_));

    // Send the test-config command
    sendUnixCommand(os.str(), response);

    /* Verify the control channel socket still exists */
    EXPECT_TRUE(fileExists(socket_path_));

    // Verify the configuration was successful.
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Configuration seems sane. Control-socket, hook-libraries, and D2 configuration were sanity checked, but not applied.\" }",
              response);

    // Check that the config was not applied.
    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(1, subnets->size());

    // Clean up after the test.
    CfgMgr::instance().clear();
}


typedef std::map<std::string, isc::data::ConstElementPtr> ElementMap;

// This test checks which commands are registered by the DHCPv4 server.
TEST_F(CtrlDhcpv6SrvTest, commandsRegistration) {

    ConstElementPtr list_cmds = createCommand("list-commands");
    ConstElementPtr answer;

    // By default the list should be empty (except the standard list-commands
    // supported by the CommandMgr itself)
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());

    // Created server should register several additional commands.
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0));
    );

    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);

    ASSERT_TRUE(answer->get("arguments"));
    std::string command_list = answer->get("arguments")->str();

    EXPECT_TRUE(command_list.find("\"list-commands\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-get-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-remove\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-remove-all\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-reset\"") != string::npos);
    EXPECT_TRUE(command_list.find("\"statistic-reset-all\"") != string::npos);

    // Ok, and now delete the server. It should deregister its commands.
    srv.reset();

    // The list should be (almost) empty again.
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());
}

// Tests that the server properly responds to invalid commands sent
// via ControlChannel
TEST_F(CtrlChannelDhcpv6SrvTest, controlChannelNegative) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"bogus\" }", response);
    EXPECT_EQ("{ \"result\": 1,"
              " \"text\": \"'bogus' command not supported.\" }", response);

    sendUnixCommand("utter nonsense", response);
    EXPECT_EQ("{ \"result\": 1, "
              "\"text\": \"error: unexpected character u in <string>:1:2\" }",
              response);
}

// Tests that the server properly responds to shtudown command sent
// via ControlChannel
TEST_F(CtrlChannelDhcpv6SrvTest, controlChannelShutdown) {
    createUnixChannelServer();
    std::string response;

    sendUnixCommand("{ \"command\": \"shutdown\" }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": \"Shutting down.\" }",response);
}

// This test verifies that the DHCP server handles get-version commands
TEST_F(CtrlChannelDhcpv6SrvTest, getversion) {
    createUnixChannelServer();

    std::string response;

    // Send the get-version command
    sendUnixCommand("{ \"command\": \"get-version\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_FALSE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the get-extended-version command
    sendUnixCommand("{ \"command\": \"get-extended-version\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("log4cplus") != string::npos);
    EXPECT_FALSE(response.find("GTEST_VERSION") != string::npos);

    // Send the get-config-report command
    sendUnixCommand("{ \"command\": \"get-config-report\" }", response);
    EXPECT_TRUE(response.find("\"result\": 0") != string::npos);
    EXPECT_TRUE(response.find("GTEST_VERSION") != string::npos);
}

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command
TEST_F(CtrlChannelDhcpv6SrvTest, controlLeasesReclaim) {
    createUnixChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    DuidPtr duid0(new DUID(DUID::fromText("00:01:02:03:04:05:06").getDuid()));
    Lease6Ptr lease0(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"),
                                duid0, 1, 50, 60, 10, 20, SubnetID(1)));
    lease0->cltt_ = time(NULL) - 100;
    DuidPtr duid1(new DUID(DUID::fromText("01:02:03:04:05:06:07").getDuid()));
    Lease6Ptr lease1(new Lease6(Lease::TYPE_NA, IOAddress("3000::2"),
                                duid1, 1, 50, 60, 10, 20, SubnetID(1)));
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

// This test verifies that the DHCP server immediately reclaims expired
// leases on leases-reclaim command with remove = true
TEST_F(CtrlChannelDhcpv6SrvTest, controlLeasesReclaimRemove) {
    createUnixChannelServer();

    // Create expired leases. Leases are expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100).
    DuidPtr duid0(new DUID(DUID::fromText("00:01:02:03:04:05:06").getDuid()));
    Lease6Ptr lease0(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"),
                                duid0, 1, 50, 60, 10, 20, SubnetID(1)));
    lease0->cltt_ = time(NULL) - 100;
    DuidPtr duid1(new DUID(DUID::fromText("01:02:03:04:05:06:07").getDuid()));
    Lease6Ptr lease1(new Lease6(Lease::TYPE_NA, IOAddress("3000::2"),
                                duid1, 1, 50, 60, 10, 20, SubnetID(1)));
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
    sendUnixCommand("{ \"command\": \"leases-reclaim\", "
                    "\"arguments\": { \"remove\": true } }", response);
    EXPECT_EQ("{ \"result\": 0, \"text\": "
              "\"Reclamation of expired leases is complete.\" }", response);

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

// Tests that the server properly responds to statistics commands.  Note this
// is really only intended to verify that the appropriate Statistics handler
// is called based on the command.  It is not intended to be an exhaustive
// test of Dhcpv6 statistics.
TEST_F(CtrlChannelDhcpv6SrvTest, controlChannelStats) {
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

} // End of anonymous namespace
