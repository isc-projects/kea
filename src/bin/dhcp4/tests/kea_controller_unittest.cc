// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <log/logger_support.h>

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
using namespace isc::hooks;

namespace {

class NakedControlledDhcpv4Srv: public ControlledDhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:
    NakedControlledDhcpv4Srv():ControlledDhcpv4Srv(0) { }
};

/// @brief test class for Kea configuration backend
///
/// This class is used for testing Kea configuration backend.
/// It is very simple and currently focuses on reading
/// config file from disk. It is expected to be expanded in the
/// near future.
class JSONFileBackendTest : public ::testing::Test {
public:
    JSONFileBackendTest() {
    }

    ~JSONFileBackendTest() {
        isc::log::setDefaultLoggingOutput();
        static_cast<void>(remove(TEST_FILE));
    };

    /// @brief writes specified content to a well known file
    ///
    /// Writes specified content to TEST_FILE. Tests will
    /// attempt to read that file.
    ///
    /// @param content content to be written to file
    void writeFile(const std::string& content) {
        static_cast<void>(remove(TEST_FILE));

        ofstream out(TEST_FILE, ios::trunc);
        EXPECT_TRUE(out.is_open());
        out << content;
        out.close();
    }

    /// Name of a config file used during tests
    static const char* TEST_FILE;
};

const char* JSONFileBackendTest::TEST_FILE  = "test-config.json";

// This test checks if configuration can be read from a JSON file.
TEST_F(JSONFileBackendTest, jsonFile) {

    // Prepare configuration file.
    string config = "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 0 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    writeFile(config);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
    );

    // And configure it using the config file.
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size()); // We expect 3 subnets.


    // Check subnet 1.
    EXPECT_EQ("192.0.2.0", subnets->at(0)->get().first.toText());
    EXPECT_EQ(24, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_V4);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("192.0.2.1", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("192.0.2.100", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_V4, pools1.at(0)->getType());

    // Check subnet 2.
    EXPECT_EQ("192.0.3.0", subnets->at(1)->get().first.toText());
    EXPECT_EQ(24, subnets->at(1)->get().second);

    // Check pools in the second subnet.
    const PoolCollection& pools2 = subnets->at(1)->getPools(Lease::TYPE_V4);
    ASSERT_EQ(1, pools2.size());
    EXPECT_EQ("192.0.3.101", pools2.at(0)->getFirstAddress().toText());
    EXPECT_EQ("192.0.3.150", pools2.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_V4, pools2.at(0)->getType());

    // And finally check subnet 3.
    EXPECT_EQ("192.0.4.0", subnets->at(2)->get().first.toText());
    EXPECT_EQ(24, subnets->at(2)->get().second);

    // ... and it's only pool.
    const PoolCollection& pools3 = subnets->at(2)->getPools(Lease::TYPE_V4);
    EXPECT_EQ("192.0.4.101", pools3.at(0)->getFirstAddress().toText());
    EXPECT_EQ("192.0.4.150", pools3.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_V4, pools3.at(0)->getType());
}

// This test checks if configuration can be read from a JSON file.
TEST_F(JSONFileBackendTest, comments) {

    string config_hash_comments = "# This is a comment. It should be \n"
        "#ignored. Real config starts in line below\n"
        "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "# comments in the middle should be ignored, too\n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/22\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    /// @todo: Implement C++-style (// ...) comments
    /// @todo: Implement C-style (/* ... */) comments

    writeFile(config_hash_comments);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
    );

    // And configure it using config with comments.
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());

    // Check subnet 1.
    EXPECT_EQ("192.0.2.0", subnets->at(0)->get().first.toText());
    EXPECT_EQ(22, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_V4);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("192.0.2.0", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("192.0.2.255", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_V4, pools1.at(0)->getType());
}

// This test checks if configuration detects failure when trying:
// - empty file
// - empty filename
// - no Dhcp4 element
// - Config file that contains Dhcp4 but has a content error
TEST_F(JSONFileBackendTest, configBroken) {

    // Empty config is not allowed, because Dhcp4 element is missing
    string config_empty = "";

    // This config does not have mandatory Dhcp4 element
    string config_v4 = "{ \"Dhcp6\": { \"interfaces\": [ \"*\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"2001:db8::/80\" ],"
        "    \"subnet\": \"2001:db8::/64\" "
        " } ]}";

    // This has Dhcp4 element, but it's utter nonsense
    string config_nonsense = "{ \"Dhcp4\": { \"reviews\": \"are so much fun\" } }";

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
    );

    // Try to configure without filename. Should fail.
    EXPECT_THROW(srv->init(""), BadValue);

    // Try to configure it using empty file. Should fail.
    writeFile(config_empty);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);

    // Now try to load a config that does not have Dhcp4 component.
    writeFile(config_v4);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);

    // Now try to load a config with Dhcp4 full of nonsense.
    writeFile(config_nonsense);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);
}

/// This unit-test reads all files enumerated in configs-test.txt file, loads
/// each of them and verify that they can be loaded.
///
/// @todo: Unfortunately, we have this test disabled, because all loaded
/// configs use memfile, which attempts to create lease file in
/// /usr/local/var/kea/kea-leases4.csv. We have couple options here:
/// a) disable persistence in example configs - a very bad thing to do
///    as users will forget to reenable it and then will be surprised when their
///    leases disappear
/// b) change configs to store lease file in /tmp. It's almost as bad as the
///    previous one. Users will then be displeased when all their leases are
///    wiped. (most systems wipe /tmp during boot)
/// c) read each config and rewrite it on the fly, so persistence is disabled.
///    This is probably the way to go, but this is a work for a dedicated ticket.
///
/// Hence I'm leaving the test in, but it is disabled.
TEST_F(JSONFileBackendTest, DISABLED_loadAllConfigs) {

    // Create server first
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
    );

    const char* configs_list = "configs-list.txt";
    fstream configs(configs_list, ios::in);
    ASSERT_TRUE(configs.is_open());
    std::string config_name;
    while (std::getline(configs, config_name)) {

        // Ignore empty and commented lines
        if (config_name.empty() || config_name[0] == '#') {
            continue;
        }

        // Unit-tests usually do not print out anything, but in this case I
        // think printing out tests configs is warranted.
        std::cout << "Loading config file " << config_name << std::endl;

        try {
            srv->init(config_name);
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "Exception thrown" << ex.what() << endl;
        }
    }
}

} // End of anonymous namespace
