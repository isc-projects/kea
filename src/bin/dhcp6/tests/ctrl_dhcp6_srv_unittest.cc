// Copyright (C) 2012-2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <hooks/hooks_manager.h>

#include "marker_file.h"
#include "test_libraries.h"

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <sys/select.h>
#include <sys/ioctl.h>

using namespace std;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;

namespace {

/// Class that acts as a UnixCommandSocket client
/// It can connect to an open UnixCommandSocket  and exchange ControlChannel
/// commands and responses.
class UnixControlClient {
public:
    UnixControlClient() {
        socket_fd_ = -1;
    }

    ~UnixControlClient() {
        disconnectFromServer();
    }

    /// @brief Closes the Control Channel socket
    void disconnectFromServer() {
        if (socket_fd_ >= 0) {
            static_cast<void>(close(socket_fd_));
            socket_fd_ = -1;
        }
    }

    /// @brief Connects to a Unix socket at the given path
    /// @param socket_path pathname of the socket to open
    /// @return true if the connect was successful, false otherwise
    bool connectToServer(const std::string& socket_path) {
        // Create UNIX socket
        socket_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (socket_fd_ < 0) {
            const char* errmsg = strerror(errno);
            ADD_FAILURE() << "Failed to open unix stream socket: " << errmsg;
            return (false);
        }

        // Prepare socket address
        struct sockaddr_un srv_addr;
        memset(&srv_addr, 0, sizeof(srv_addr));
        srv_addr.sun_family = AF_UNIX;
        strncpy(srv_addr.sun_path, socket_path.c_str(),
                sizeof(srv_addr.sun_path));
        socklen_t len = sizeof(srv_addr);

        // Connect to the specified UNIX socket
        int status = connect(socket_fd_, (struct sockaddr*)&srv_addr, len);
        if (status == -1) {
            const char* errmsg = strerror(errno);
            ADD_FAILURE() << "Failed to connect unix socket: fd=" << socket_fd_
                          << ", path=" << socket_path << " : " << errmsg;
            disconnectFromServer();
            return (false);
        }

        return (true);
    }

    /// @brief Sends the given command across the open Control Channel
    /// @param command the command text to execute in JSON form
    /// @return true if the send succeeds, false otherwise
    bool sendCommand(const std::string& command) {
        // Send command
        int bytes_sent = send(socket_fd_, command.c_str(), command.length(), 0);
        if (bytes_sent < command.length()) {
            const char* errmsg = strerror(errno);
            ADD_FAILURE() << "Failed to send " << command.length()
                      << " bytes, send() returned " << bytes_sent
                      << " : " << errmsg;
            return (false);
        }

        return (true);
    }

    /// @brief Reads the response text from the open Control Channel
    /// @param response variable into which the received response should be
    /// placed.
    /// @return true if data was successfully read from the socket,
    /// false otherwise
    bool getResponse(std::string& response) {
        // Receive response
        // @todo implement select check to see if data is waiting
        char buf[65536];
        memset(buf, 0, sizeof(buf));
        switch (selectCheck()) {
        case -1: {
            const char* errmsg = strerror(errno);
            ADD_FAILURE() << "getResponse - select failed: " << errmsg;
            return (false);
        }
        case 0:
            ADD_FAILURE() << "No response data sent";
            return (false);

        default:
            break;
        }

        int bytes_rcvd = recv(socket_fd_, buf, sizeof(buf), 0);
        if (bytes_rcvd < 0) {
            const char* errmsg = strerror(errno);
            ADD_FAILURE() << "Failed to receive a response. recv() returned "
                      << bytes_rcvd << " : " << errmsg;
            return (false);
        }

        if (bytes_rcvd >= sizeof(buf)) {
            ADD_FAILURE() << "Response size too large: " << bytes_rcvd;
            return (false);
        }

        // Convert the response to a string
        response = string(buf, bytes_rcvd);
        return (true);
    }


    /// @brief Uses select to poll the Control Channel for data waiting
    /// @return -1 on error, 0 if no data is available,  1 if data is ready
    int selectCheck() {
        int maxfd = 0;

        fd_set read_fds;
        FD_ZERO(&read_fds);

        // Add this socket to listening set
        FD_SET(socket_fd_,  &read_fds);
        maxfd = socket_fd_;

        struct timeval select_timeout;
        select_timeout.tv_sec = 0;
        select_timeout.tv_usec = 0;

        return (select(maxfd + 1, &read_fds, NULL, NULL, &select_timeout));
    }

    /// @brief Retains the fd of the open socket
    int socket_fd_;
};


class NakedControlledDhcpv6Srv: public ControlledDhcpv6Srv {
    // "Naked" DHCPv6 server, exposes internal fields
public:
    NakedControlledDhcpv6Srv():ControlledDhcpv6Srv(DHCP6_SERVER_PORT + 10000) {
    }

    /// @brief Exposes server's receivePacket method
    virtual Pkt6Ptr receivePacket(int timeout) {
        return(Dhcpv6Srv::receivePacket(timeout));
    }

};

class CtrlDhcpv6SrvTest : public ::testing::Test {
public:
    CtrlDhcpv6SrvTest() {
        reset();
    }

    virtual ~CtrlDhcpv6SrvTest() {
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
    std::string socket_path_;
    boost::shared_ptr<NakedControlledDhcpv6Srv> server_;

    CtrlChannelDhcpv6SrvTest() {
        socket_path_ = string(TEST_DATA_BUILDDIR) + "/kea6.sock";
        reset();
    }

    ~CtrlChannelDhcpv6SrvTest() {
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

        ConstElementPtr config = Element::fromJSON(config_txt);
        ConstElementPtr answer = server_->processConfig(config);
        ASSERT_TRUE(answer);

        int status = 0;
        isc::config::parseAnswer(status, answer);
        ASSERT_EQ(0, status);

        // Now check that the socket was indeed open.
        ASSERT_GT(isc::config::CommandMgr::instance().getControlSocketFD(), -1);
    }

    /// @brief Reset
    void reset() {
        CtrlDhcpv6SrvTest::reset();
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
TEST_F(CtrlDhcpv6SrvTest, libreload) {

    // Sending commands for processing now requires a server that can process
    // them.
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // Ensure no marker files to start with.
    ASSERT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    ASSERT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Load two libraries
    std::vector<std::string> libraries;
    libraries.push_back(CALLOUT_LIBRARY_1);
    libraries.push_back(CALLOUT_LIBRARY_2);
    HooksManager::loadLibraries(libraries);

    // Check they are loaded.
    std::vector<std::string> loaded_libraries =
        HooksManager::getLibraryNames();
    ASSERT_TRUE(libraries == loaded_libraries);

    // ... which also included checking that the marker file created by the
    // load functions exists and holds the correct value (of "12" - the
    // first library appends "1" to the file, the second appends "2"). Also
    // check that the unload marker file does not yet exist.
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "12"));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Now execute the "libreload" command.  This should cause the libraries
    // to unload and to reload.

    // Use empty parameters list
    ElementPtr params(new isc::data::MapElement());
    int rcode = -1;

    ConstElementPtr result =
        ControlledDhcpv6Srv::processCommand("libreload", params);
    ConstElementPtr comment = isc::config::parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // Expect success

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

    // Now execute the "libreload" command.  This should cause the libraries
    // to unload and to reload.

    // Use empty parameters list
    // Prepare configuration file.
    string config_txt = "{ \"interfaces-config\": {"
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
        "\"valid-lifetime\": 4000 }";

    ElementPtr config = Element::fromJSON(config_txt);

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
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll();
    EXPECT_EQ(3, subnets->size());

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
