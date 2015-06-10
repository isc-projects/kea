// Copyright (C) 2012-2013,2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <hooks/hooks_manager.h>

#include "marker_file.h"
#include "test_libraries.h"

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;

namespace {

class NakedControlledDhcpv6Srv: public ControlledDhcpv6Srv {
    // "Naked" DHCPv6 server, exposes internal fields
public:
    NakedControlledDhcpv6Srv():ControlledDhcpv6Srv(DHCP6_SERVER_PORT + 10000) { }
};

class CtrlDhcpv6SrvTest : public ::testing::Test {
public:
    CtrlDhcpv6SrvTest() {
        reset();
    }

    ~CtrlDhcpv6SrvTest() {
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

} // End of anonymous namespace
