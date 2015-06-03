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
        static_cast<void>(unlink(LOAD_MARKER_FILE));
        static_cast<void>(unlink(UNLOAD_MARKER_FILE));
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
    EXPECT_EQ("[ \"list-commands\", \"shutdown\" ]", answer->get("arguments")->str());

    // Ok, and now delete the server. It should deregister its commands.
    srv.reset();

    // The list should be (almost) empty again.
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_cmds));
    ASSERT_TRUE(answer);
    ASSERT_TRUE(answer->get("arguments"));
    EXPECT_EQ("[ \"list-commands\" ]", answer->get("arguments")->str());
}

// Checks if the server is able to parse control socket configuration and
// configures the command socket properly.
TEST_F(CtrlDhcpv4SrvTest, commandSocketBasic) {

    string socket_path = string(TEST_DATA_DIR) + "/kea4.sock";

    // Just a simple config. The important part here is the socket
    // location information.
    std::string config_txt =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"subnet4\": [ ],"
        "    \"valid-lifetime\": 4000,"
        "    \"control-socket\": {"
        "        \"socket-type\": \"unix\","
        "        \"socket-name\": \"" + socket_path + "\""
        "    }"
        "}";

    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0));
    );

    ConstElementPtr config = Element::fromJSON(config_txt);

    ConstElementPtr answer = srv->processConfig(config);
    ASSERT_TRUE(answer);

    int status = 0;
    isc::config::parseAnswer(status, answer);
    EXPECT_EQ(0, status);

    // Now check that the socket was indeed open.
    EXPECT_TRUE(isc::config::CommandMgr::instance().getControlSocketFD() > 0);
}

/// @todo: Implement system tests for the control socket.
/// It is tricky in unit-tests, as it would require running two processes
/// (one for the server itself and a second one for the test that sends
/// command and receives an aswer).
///
/// Alternatively, we could use shell tests. It would be much simpler,
/// but that requires using socat, a tool that is typically not installed.
/// So we'd need a check in configure to check if it's available and
/// fail configure process if missing (or disable the tests).

} // End of anonymous namespace
