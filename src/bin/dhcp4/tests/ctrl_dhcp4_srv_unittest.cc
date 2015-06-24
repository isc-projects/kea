// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <hooks/hooks_manager.h>

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

namespace {

class NakedControlledDhcpv4Srv: public ControlledDhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:
    NakedControlledDhcpv4Srv():ControlledDhcpv4Srv(DHCP4_SERVER_PORT + 10000) { }
};

class CtrlDhcpv4SrvTest : public ::testing::Test {
public:
    CtrlDhcpv4SrvTest() {
        reset();
    }

    ~CtrlDhcpv4SrvTest() {
        reset();
    };

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
    }

    /// @brief sends commands over specified UNIX socket
    ///
    /// @param command command to be sent (should be valid JSON)
    /// @param response response received (expected to be a valid JSON)
    /// @param socket_path UNIX socket path
    ///
    /// @return true if send/response exchange was successful, false otherwise
    bool sendCommandUnixSocket(const std::string& command,
                               std::string& response,
                               const std::string& socket_path) {

        // Create UNIX socket
        int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            ADD_FAILURE() << "Failed to open unix stream socket.";
            return (false);
        }

        // Prepare socket address
        struct sockaddr_un srv_addr;
        memset(&srv_addr, 0, sizeof(struct sockaddr_un));
        srv_addr.sun_family = AF_UNIX;
        strncpy(srv_addr.sun_path, socket_path.c_str(), sizeof(srv_addr.sun_path));
        socklen_t len = sizeof(srv_addr);

        // Connect to the specified UNIX socket
        int status = connect(socket_fd, (struct sockaddr*)&srv_addr, len);
        if (status == -1) {
            ADD_FAILURE() << "Failed to connect unix socket: fd=" << socket_fd
                          << ", path=" << socket_path;
            close(socket_fd);
            return (false);
        }


        // Send command
        cout << "Sending command: " << command << endl;
        int bytes_sent = send(socket_fd, command.c_str(), command.length(), 0);
        if (bytes_sent < command.length()) {
            ADD_FAILURE() << "Failed to send " << command.length()
                      << " bytes, send() returned " << bytes_sent;
            close(socket_fd);
            return (false);
        }

        // Receive response
        /// @todo: this may block if server fails to respond. Some sort of
        /// of a timer is needed.
        char buf[65536];
        memset(buf, 0, sizeof(buf));
        int bytes_rcvd = recv(socket_fd, buf, sizeof(buf), 0);
        if (bytes_rcvd < 0) {
            ADD_FAILURE() << "Failed to receive a response. recv() returned "
                      << bytes_rcvd;
            close(socket_fd);
            return (false);
        }

        // Convert the response to a string, close the socket and return
        response = string(buf, bytes_rcvd);
        cout << "Received response: " << response << endl;
        close(socket_fd);
        return (true);
    }
};

TEST_F(CtrlDhcpv4SrvTest, commands) {

    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(DHCP4_SERVER_PORT + 10000))
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

TEST_F(CtrlDhcpv4SrvTest, libreload) {

    // Sending commands for processing now requires a server that can process
    // them.
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
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
        ControlledDhcpv4Srv::processCommand("libreload", params);
    ConstElementPtr comment = parseAnswer(rcode, result);
    EXPECT_EQ(0, rcode); // Expect success

    // Check that the libraries have unloaded and reloaded.  The libraries are
    // unloaded in the reverse order to which they are loaded.  When they load,
    // they should append information to the loading marker file.
    EXPECT_TRUE(checkMarkerFile(UNLOAD_MARKER_FILE, "21"));
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "1212"));
}

// This test checks which commands are registered by the DHCPv4 server.
TEST_F(CtrlDhcpv4SrvTest, commandsRegistration) {

    ConstElementPtr list_cmds = createCommand("list-commands");
    ConstElementPtr answer;

    // By default the list should be empty (except the standard list-commands
    // supported by the CommandMgr itself)
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());

    // Created server should register several additional commands.
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0));
    );

    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\", \"shutdown\", "
              "\"statistic-get\", \"statistic-get-all\", "
              "\"statistic-remove\", \"statistic-remove-all\", "
              "\"statistic-reset\", \"statistic-reset-all\" ]",
              answer->get("arguments")->str());

    // Ok, and now delete the server. It should deregister its commands.
    srv.reset();

    // The list should be (almost) empty again.
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());
}

} // End of anonymous namespace
