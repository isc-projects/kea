// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <dhcp/dhcp4.h>
#include <dhcp/hwaddr.h>
#include <dhcp/iface_mgr.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/parser_context.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>

#ifdef HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#endif

#include <log/logger_support.h>
#include <util/stopwatch.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <signal.h>
#include <sstream>

#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;

#ifdef HAVE_MYSQL
using namespace isc::db::test;
#endif

using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;

namespace {

class NakedControlledDhcpv4Srv: public ControlledDhcpv4Srv {
    // "Naked" DHCPv4 server, exposes internal fields
public:
    NakedControlledDhcpv4Srv():ControlledDhcpv4Srv(0) { }
    using ControlledDhcpv4Srv::signal_handler_;
};

/// @brief test class for Kea configuration backend
///
/// This class is used for testing Kea configuration backend.
/// It is very simple and currently focuses on reading
/// config file from disk. It is expected to be expanded in the
/// near future.
class JSONFileBackendTest : public isc::dhcp::test::BaseServerTest {
public:
    JSONFileBackendTest() {
    }

    ~JSONFileBackendTest() {
        LeaseMgrFactory::destroy();
        static_cast<void>(remove(TEST_FILE));
        static_cast<void>(remove(TEST_INCLUDE));
    };

    /// @brief writes specified content to a well known file
    ///
    /// Writes specified content to TEST_FILE. Tests will
    /// attempt to read that file.
    ///
    /// @param file_name name of file to be written
    /// @param content content to be written to file
    void writeFile(const std::string& file_name, const std::string& content) {
        static_cast<void>(remove(file_name.c_str()));

        ofstream out(file_name.c_str(), ios::trunc);
        EXPECT_TRUE(out.is_open());
        out << content;
        out.close();
    }

    /// @brief Runs timers for specified time.
    ///
    /// @param io_service Pointer to the IO service to be ran.
    /// @param timeout_ms Amount of time after which the method returns.
    void runTimersWithTimeout(const IOServicePtr& io_service, const long timeout_ms) {
        IntervalTimer timer(*io_service);
        timer.setup([&io_service]() {
            io_service->stop();
        }, timeout_ms, IntervalTimer::ONE_SHOT);
        io_service->run();
        io_service->get_io_service().reset();
    }

    /// Name of a config file used during tests
    static const char* TEST_FILE;
    static const char* TEST_INCLUDE;
};

const char* JSONFileBackendTest::TEST_FILE  = "test-config.json";
const char* JSONFileBackendTest::TEST_INCLUDE = "test-include.json";

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

    writeFile(TEST_FILE, config);

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

// This test verifies that the configurations for various servers
// can coexist and that the DHCPv4 configuration parsers will simply
// ignore them.
TEST_F(JSONFileBackendTest, serverConfigurationsCoexistence) {
    std::string config = "{ \"Dhcp4\": {"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"valid-lifetime\": 4000 }, "
        "\"Dhcp6\": { },"
        "\"DhcpDdns\": { },"
        "\"Control-agent\": { }"
        "}";

    writeFile(TEST_FILE, config);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
    );

    // And configure it using the config file.
    EXPECT_NO_THROW(srv->init(TEST_FILE));
}

// This test checks if configuration can be read from a JSON file
// using hash (#) line comments
TEST_F(JSONFileBackendTest, hashComments) {

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

    writeFile(TEST_FILE, config_hash_comments);

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

// This test checks if configuration can be read from a JSON file
// using C++ line (//) comments.
TEST_F(JSONFileBackendTest, cppLineComments) {

    string config_cpp_line_comments = "// This is a comment. It should be \n"
        "//ignored. Real config starts in line below\n"
        "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "// comments in the middle should be ignored, too\n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/22\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    writeFile(TEST_FILE, config_cpp_line_comments);

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

// This test checks if configuration can be read from a JSON file
// using C block (/* */) comments
TEST_F(JSONFileBackendTest, cBlockComments) {

    string config_c_block_comments = "/* This is a comment. It should be \n"
      "ignored. Real config starts in line below*/\n"
        "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "/* comments in the middle should be ignored, too*/\n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/22\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    writeFile(TEST_FILE, config_c_block_comments);

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

// This test checks if configuration can be read from a JSON file
// using an include file.
TEST_F(JSONFileBackendTest, include) {

    string config_hash_comments = "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ \"*\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "<?include \"" + string(TEST_INCLUDE) + "\"?>,"
        "\"valid-lifetime\": 4000 }"
        "}";
    string include = "\n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/22\" "
        " } ]\n";

    writeFile(TEST_FILE, config_hash_comments);
    writeFile(TEST_INCLUDE, include);

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

// This test checks if recursive include of a file is detected
TEST_F(JSONFileBackendTest, recursiveInclude) {

    string config_recursive_include = "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "  \"interfaces\": [ <?include \"" + string(TEST_INCLUDE) + "\"?> ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/22\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";
    string include = "\"eth\", <?include \"" + string(TEST_INCLUDE) + "\"?>";
    string msg = "configuration error using file '" + string(TEST_FILE) +
        "': Too many nested include.";

    writeFile(TEST_FILE, config_recursive_include);
    writeFile(TEST_INCLUDE, include);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv4Srv(0))
    );

    // And configure it using config with comments.
    try {
        srv->init(TEST_FILE);
        FAIL() << "Expected Dhcp4ParseError but nothing was raised";
    }
    catch (const Exception& ex) {
        EXPECT_EQ(msg, ex.what());
    }
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
    writeFile(TEST_FILE, config_empty);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);

    // Now try to load a config that does not have Dhcp4 component.
    writeFile(TEST_FILE, config_v4);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);

    // Now try to load a config with Dhcp4 full of nonsense.
    writeFile(TEST_FILE, config_nonsense);
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

// This test verifies that the DHCP server installs the timers for reclaiming
// and flushing expired leases.
TEST_F(JSONFileBackendTest, timers) {
    // This is a basic configuration which enables timers for reclaiming
    // expired leases and flushing them after 500 seconds since they expire.
    // Both timers run at 1 second intervals.
    string config =
        "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "\"lease-database\": {"
        "     \"type\": \"memfile\","
        "     \"persist\": false"
        "},"
        "\"expired-leases-processing\": {"
        "     \"reclaim-timer-wait-time\": 1,"
        "     \"hold-reclaimed-time\": 500,"
        "     \"flush-reclaimed-timer-wait-time\": 1"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ ],"
        "\"valid-lifetime\": 4000 }"
        "}";
    writeFile(TEST_FILE, config);

    // Create an instance of the server and initialize it.
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new ControlledDhcpv4Srv(0)));
    ASSERT_NO_THROW(srv->init(TEST_FILE));

    // Create an expired lease. The lease is expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100). The lease will be reclaimed
    // but shouldn't be flushed in the database because the reclaimed are
    // held in the database 500 seconds after reclamation, according to the
    // current configuration.
    HWAddrPtr hwaddr_expired(new HWAddr(HWAddr::fromText("00:01:02:03:04:05")));
    Lease4Ptr lease_expired(new Lease4(IOAddress("10.0.0.1"), hwaddr_expired,
                                       ClientIdPtr(), 60, 10, 20,
                                       time(NULL) - 100, SubnetID(1)));

    // Create expired-reclaimed lease. The lease has expired 1000 - 60 seconds
    // ago. It should be removed from the lease database when the "flush" timer
    // goes off.
    HWAddrPtr hwaddr_reclaimed(new HWAddr(HWAddr::fromText("01:02:03:04:05:06")));
    Lease4Ptr lease_reclaimed(new Lease4(IOAddress("10.0.0.2"), hwaddr_reclaimed,
                                         ClientIdPtr(), 60, 10, 20,
                                         time(NULL) - 1000, SubnetID(1)));
    lease_reclaimed->state_ = Lease4::STATE_EXPIRED_RECLAIMED;

    // Add leases to the database.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease_expired));
    ASSERT_NO_THROW(lease_mgr.addLease(lease_reclaimed));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease4(IOAddress("10.0.0.1")));
    ASSERT_TRUE(lease_mgr.getLease4(IOAddress("10.0.0.2")));

    // Poll the timers for a while to make sure that each of them is executed
    // at least once.
    ASSERT_NO_THROW(runTimersWithTimeout(srv->getIOService(), 5000));

    // Verify that the leases in the database have been processed as expected.

    // First lease should be reclaimed, but not removed.
    ASSERT_NO_THROW(lease_expired = lease_mgr.getLease4(IOAddress("10.0.0.1")));
    ASSERT_TRUE(lease_expired);
    EXPECT_TRUE(lease_expired->stateExpiredReclaimed());

    // Second lease should have been removed.
    ASSERT_NO_THROW(
        lease_reclaimed = lease_mgr.getLease4(IOAddress("10.0.0.2"));
    );
    EXPECT_FALSE(lease_reclaimed);
}

// This test verifies that the server uses default (Memfile) lease database
// backend when no backend is explicitly specified in the configuration.
TEST_F(JSONFileBackendTest, defaultLeaseDbBackend) {
    // This is basic server configuration which excludes lease database
    // backend specification. The default Memfile backend should be
    // initialized in this case.
    string config =
        "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ ],"
        "\"valid-lifetime\": 4000 }"
        "}";
    writeFile(TEST_FILE, config);

    // Create an instance of the server and initialize it.
    boost::scoped_ptr<ControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new ControlledDhcpv4Srv(0)));
    ASSERT_NO_THROW(srv->init(TEST_FILE));

    // The backend should have been created.
    EXPECT_NO_THROW(static_cast<void>(LeaseMgrFactory::instance()));
}

// Starting tests which require MySQL backend availability. Those tests
// will not be executed if Kea has been compiled without the
// --with-mysql.
#ifdef HAVE_MYSQL

/// @brief Test fixture class for the tests utilizing MySQL database
/// backend.
class JSONFileBackendMySQLTest : public JSONFileBackendTest {
public:

    /// @brief Constructor.
    ///
    /// Recreates MySQL schema for a test.
    JSONFileBackendMySQLTest() : JSONFileBackendTest() {
        destroyMySQLSchema();
        createMySQLSchema();
    }

    /// @brief Destructor.
    ///
    /// Destroys MySQL schema.
    virtual ~JSONFileBackendMySQLTest() {
        destroyMySQLSchema();
    }

    /// @brief Creates server configuration with specified backend type.
    ///
    /// @param backend Backend type or empty string to indicate that the
    /// backend configuration should not be placed in the resulting
    /// JSON configuration.
    ///
    /// @return Server configuration.
    std::string createConfiguration(const std::string& backend) const;

    /// @brief Test reconfiguration with a backend change.
    ///
    /// If any of the parameters is an empty string it indicates that the
    /// created configuration should exclude backend configuration.
    ///
    /// @param backend_first Type of a backend to be used initially.
    /// @param backend_second Type of a backend to be used after
    /// reconfiguration.
    void testBackendReconfiguration(const std::string& backend_first,
                                    const std::string& backend_second);
};

std::string
JSONFileBackendMySQLTest::createConfiguration(const std::string& backend) const {
    // This is basic server configuration which excludes lease database
    // backend specification. The default Memfile backend should be
    // initialized in this case.
    std::ostringstream config;
    config <<
        "{ \"Dhcp4\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},";

    // For non-empty lease backend type we have to add a backend configuration
    // section.
    if (!backend.empty()) {
        config <<
        "\"lease-database\": {"
        "     \"type\": \"" << backend << "\"";

        // SQL backends require database credentials.
        if (backend != "memfile") {
            config <<
                ","
                "     \"name\": \"keatest\","
                "     \"user\": \"keatest\","
                "     \"password\": \"keatest\"";
        }
        config << "},";
    }

    // Append the rest of the configuration.
    config <<
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    return (config.str());
}

void
JSONFileBackendMySQLTest::
testBackendReconfiguration(const std::string& backend_first,
                           const std::string& backend_second) {
    writeFile(TEST_FILE, createConfiguration(backend_first));

    // Create an instance of the server and initialize it.
    boost::scoped_ptr<NakedControlledDhcpv4Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedControlledDhcpv4Srv()));
    srv->setConfigFile(TEST_FILE);
    ASSERT_NO_THROW(srv->init(TEST_FILE));

    // The backend should have been created and its type should be
    // correct.
    ASSERT_NO_THROW(static_cast<void>(LeaseMgrFactory::instance()));
    EXPECT_EQ(backend_first.empty() ? "memfile" : backend_first,
              LeaseMgrFactory::instance().getType());

    // New configuration modifies the lease database backend type.
    writeFile(TEST_FILE, createConfiguration(backend_second));

    // Explicitly calling signal handler for SIGHUP to trigger server
    // reconfiguration.
    srv->signal_handler_(SIGHUP);

    // The backend should have been created and its type should be
    // correct.
    ASSERT_NO_THROW(static_cast<void>(LeaseMgrFactory::instance()));
    EXPECT_EQ(backend_second.empty() ? "memfile" : backend_second,
              LeaseMgrFactory::instance().getType());
}


// This test verifies that backend specification can be added on
// server reconfiguration.
TEST_F(JSONFileBackendMySQLTest, reconfigureBackendUndefinedToMySQL) {
    testBackendReconfiguration("", "mysql");
}

// This test verifies that when backend specification is removed the
// default backend is used.
TEST_F(JSONFileBackendMySQLTest, reconfigureBackendMySQLToUndefined) {
    testBackendReconfiguration("mysql", "");
}

// This test verifies that backend type can be changed from Memfile
// to MySQL.
TEST_F(JSONFileBackendMySQLTest, reconfigureBackendMemfileToMySQL) {
    testBackendReconfiguration("memfile", "mysql");
}

#endif

} // End of anonymous namespace
