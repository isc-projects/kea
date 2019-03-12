// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/parser_context.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
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

class NakedControlledDhcpv6Srv: public ControlledDhcpv6Srv {
    // "Naked" DHCPv6 server, exposes internal fields
public:
    NakedControlledDhcpv6Srv():ControlledDhcpv6Srv(0) { }
    using ControlledDhcpv6Srv::signal_handler_;
};


class JSONFileBackendTest : public dhcp::test::BaseServerTest {
public:
    JSONFileBackendTest()
        : BaseServerTest() {
    }

    ~JSONFileBackendTest() {
        LeaseMgrFactory::destroy();
        isc::log::setDefaultLoggingOutput();
        static_cast<void>(remove(TEST_FILE));
        static_cast<void>(remove(TEST_INCLUDE));
    };

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

    static const char* TEST_FILE;
    static const char* TEST_INCLUDE;
};

const char* JSONFileBackendTest::TEST_FILE = "test-config.json";
const char* JSONFileBackendTest::TEST_INCLUDE = "test-include.json";

// This test checks if configuration can be read from a JSON file.
TEST_F(JSONFileBackendTest, jsonFile) {

    // Prepare configuration file.
    string config = "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
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
        "\"valid-lifetime\": 4000 }"
        "}";
    writeFile(TEST_FILE, config);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using the config file.
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size()); // We expect 3 subnets.


    // Check subnet 1.
    EXPECT_EQ("2001:db8:1::", subnets->at(0)->get().first.toText());
    EXPECT_EQ(64, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("2001:db8:1::", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff:ffff", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools1.at(0)->getType());

    // Check subnet 2.
    EXPECT_EQ("2001:db8:2::", subnets->at(1)->get().first.toText());
    EXPECT_EQ(64, subnets->at(1)->get().second);

    // Check pools in the second subnet.
    const PoolCollection& pools2 = subnets->at(1)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(1, pools2.size());
    EXPECT_EQ("2001:db8:2::", pools2.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:2::ffff:ffff:ffff", pools2.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools2.at(0)->getType());

    // And finally check subnet 3.
    EXPECT_EQ("2001:db8:3::", subnets->at(2)->get().first.toText());
    EXPECT_EQ(64, subnets->at(2)->get().second);

    // ... and it's only pool.
    const PoolCollection& pools3 = subnets->at(2)->getPools(Lease::TYPE_NA);
    EXPECT_EQ("2001:db8:3::", pools3.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:3::ffff:ffff:ffff", pools3.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools3.at(0)->getType());
}

// This test verifies that the configurations for various servers
// can coexist and that the DHCPv6 configuration parsers will simply
// ignore them.
TEST_F(JSONFileBackendTest, serverConfigurationsCoexistence) {
    std::string config = "{ \"Dhcp6\": {"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"preferred-lifetime\": 1000, \n"
        "\"valid-lifetime\": 4000 }, "
        "\"Dhcp4\": { },"
        "\"DhcpDdns\": { },"
        "\"Control-agent\": { }"
        "}";

    writeFile(TEST_FILE, config);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using the config file.
    EXPECT_NO_THROW(srv->init(TEST_FILE));
}

// This test checks if configuration can be read from a JSON file
// using hash (#) line comments
TEST_F(JSONFileBackendTest, hashComments) {

    string config_hash_comments = "# This is a comment. It should be \n"
        "#ignored. Real config starts in line below\n"
        "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "# comments in the middle should be ignored, too\n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    writeFile(TEST_FILE, config_hash_comments);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using config without
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());

    // Check subnet 1.
    EXPECT_EQ("2001:db8:1::", subnets->at(0)->get().first.toText());
    EXPECT_EQ(64, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("2001:db8:1::", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff:ffff", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools1.at(0)->getType());
}

// This test checks if configuration can be read from a JSON file
// using C++ line (//) comments.
TEST_F(JSONFileBackendTest, cppLineComments) {

    string config_cpp_line_comments = "// This is a comment. It should be \n"
        "//ignored. Real config starts in line below\n"
        "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "// comments in the middle should be ignored, too\n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

    writeFile(TEST_FILE, config_cpp_line_comments);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using config without
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());

    // Check subnet 1.
    EXPECT_EQ("2001:db8:1::", subnets->at(0)->get().first.toText());
    EXPECT_EQ(64, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("2001:db8:1::", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff:ffff", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools1.at(0)->getType());
}

// This test checks if configuration can be read from a JSON file
// using C block (/* */) comments
TEST_F(JSONFileBackendTest, cBlockComments) {

    string config_c_block_comments = "/* This is a comment. It should be \n"
        "ignored. Real config starts in line below*/\n"
        "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "/* comments in the middle should be ignored, too*/\n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";

      writeFile(TEST_FILE, config_c_block_comments);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using config without
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());

    // Check subnet 1.
    EXPECT_EQ("2001:db8:1::", subnets->at(0)->get().first.toText());
    EXPECT_EQ(64, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("2001:db8:1::", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff:ffff", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools1.at(0)->getType());
}

// This test checks if configuration can be read from a JSON file
// using an include file.
TEST_F(JSONFileBackendTest, include) {

    string config = "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "<?include \"" + string(TEST_INCLUDE) + "\"?>,"
        "\"valid-lifetime\": 4000 }"
        "}";
    string include = "\n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " } ]\n";

    writeFile(TEST_FILE, config);
    writeFile(TEST_INCLUDE, include);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using config without
    EXPECT_NO_THROW(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());

    // Check subnet 1.
    EXPECT_EQ("2001:db8:1::", subnets->at(0)->get().first.toText());
    EXPECT_EQ(64, subnets->at(0)->get().second);

    // Check pools in the first subnet.
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(1, pools1.size());
    EXPECT_EQ("2001:db8:1::", pools1.at(0)->getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff:ffff", pools1.at(0)->getLastAddress().toText());
    EXPECT_EQ(Lease::TYPE_NA, pools1.at(0)->getType());
}

// This test checks if recursive include of a file is detected
TEST_F(JSONFileBackendTest, recursiveInclude) {

    string config_recursive_include = "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "  \"interfaces\": [ <?include \"" + string(TEST_INCLUDE) + "\"?> ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }"
        "}";
    string include = "\"eth\", <?include \"" + string(TEST_INCLUDE) + "\"?>";
    string msg = "configuration error using file '" + string(TEST_FILE) +
        "': Too many nested include.";

    writeFile(TEST_FILE, config_recursive_include);
    writeFile(TEST_INCLUDE, include);


    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using config
    try {
        srv->init(TEST_FILE);
        FAIL() << "Expected Dhcp6ParseError but nothing was raised";
    }
    catch (const Exception& ex) {
        EXPECT_EQ(msg, ex.what());
    }
}

// This test checks if configuration can be read from a JSON file.
// This test checks if configuration detects failure when trying:
// - empty file
// - empty filename
// - no Dhcp6 element
// - Config file that contains Dhcp6 but has a content error
TEST_F(JSONFileBackendTest, configBroken) {

    // Empty config is not allowed, because Dhcp6 element is missing
    string config_empty = "";

    // This config does not have mandatory Dhcp6 element
    string config_v4 = "{ \"Dhcp4\": { \"interfaces\": [ \"*\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.0/24\" ],"
        "    \"subnet\": \"192.0.2.0/24\" "
        " } ]}";

    // This has Dhcp6 element, but it's utter nonsense
    string config_nonsense = "{ \"Dhcp6\": { \"reviews\": \"are so much fun\" } }";

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // Try to configure without filename. Should fail.
    EXPECT_THROW(srv->init(""), BadValue);

    // Try to configure it using empty file. Should fail.
    writeFile(TEST_FILE, config_empty);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);

    // Now try to load a config that does not have Dhcp6 component.
    writeFile(TEST_FILE, config_v4);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);

    // Now try to load a config with Dhcp6 full of nonsense.
    writeFile(TEST_FILE, config_nonsense);
    EXPECT_THROW(srv->init(TEST_FILE), BadValue);
}

// This test verifies that the DHCP server installs the timers for reclaiming
// and flushing expired leases.
TEST_F(JSONFileBackendTest, timers) {
    // This is a basic configuration which enables timers for reclaiming
    // expired leases and flushing them after 500 seconds since they expire.
    // Both timers run at 1 second intervals.
    string config =
        "{ \"Dhcp6\": {"
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
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ ],"
        "\"preferred-lifetime\": 3000, "
        "\"valid-lifetime\": 4000 }"
        "}";
    writeFile(TEST_FILE, config);

    // Create an instance of the server and initialize it.
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(srv.reset(new ControlledDhcpv6Srv(0)));
    ASSERT_NO_THROW(srv->init(TEST_FILE));

    // Create an expired lease. The lease is expired by 40 seconds ago
    // (valid lifetime = 60, cltt = now - 100). The lease will be reclaimed
    // but shouldn't be flushed in the database because the reclaimed are
    // held in the database 500 seconds after reclamation, according to the
    // current configuration.
    DuidPtr duid_expired(new DUID(DUID::fromText("00:01:02:03:04:05:06").getDuid()));
    Lease6Ptr lease_expired(new Lease6(Lease::TYPE_NA, IOAddress("3000::1"),
                                       duid_expired, 1, 50, 60, 10, 20, SubnetID(1)));
    lease_expired->cltt_ = time(NULL) - 100;


    // Create expired-reclaimed lease. The lease has expired 1000 - 60 seconds
    // ago. It should be removed from the lease database when the "flush" timer
    // goes off.
    DuidPtr duid_reclaimed(new DUID(DUID::fromText("01:02:03:04:05:06:07").getDuid()));
    Lease6Ptr lease_reclaimed(new Lease6(Lease::TYPE_NA, IOAddress("3000::2"),
                                         duid_reclaimed, 1, 50, 60, 10, 20, SubnetID(1)));
    lease_reclaimed->cltt_ = time(NULL) - 1000;
    lease_reclaimed->state_ = Lease6::STATE_EXPIRED_RECLAIMED;

    // Add leases to the database.
    LeaseMgr& lease_mgr = LeaseMgrFactory::instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease_expired));
    ASSERT_NO_THROW(lease_mgr.addLease(lease_reclaimed));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1")));
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2")));

    // Poll the timers for a while to make sure that each of them is executed
    // at least once.
    ASSERT_NO_THROW(runTimersWithTimeout(srv->getIOService(), 5000));

    // Verify that the leases in the database have been processed as expected.

    // First lease should be reclaimed, but not removed.
    ASSERT_NO_THROW(
        lease_expired = lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1"))
    );
    ASSERT_TRUE(lease_expired);
    EXPECT_TRUE(lease_expired->stateExpiredReclaimed());

    // Second lease should have been removed.
    ASSERT_NO_THROW(
        lease_reclaimed = lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2"))
    );
    EXPECT_FALSE(lease_reclaimed);
}

// This test verifies that the DUID type can be selected.
TEST_F(JSONFileBackendTest, serverId) {
    string config =
        "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "\"lease-database\": {"
        "     \"type\": \"memfile\","
        "     \"persist\": false"
        "},"
        "\"server-id\": {"
        "     \"type\": \"EN\","
        "     \"enterprise-id\": 1234"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ ],"
        "\"preferred-lifetime\": 3000, "
        "\"valid-lifetime\": 4000 }"
        "}";
    writeFile(TEST_FILE, config);

    // Create an instance of the server and initialize it.
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(srv.reset(new ControlledDhcpv6Srv(0)));
    ASSERT_NO_THROW(srv->init(TEST_FILE));

    // Check that DUID configuration is affected.
    ConstCfgDUIDPtr duid_cfg = CfgMgr::instance().getCurrentCfg()->getCfgDUID();
    ASSERT_TRUE(duid_cfg);
    EXPECT_EQ(DUID::DUID_EN, duid_cfg->getType());
    EXPECT_EQ(1234, duid_cfg->getEnterpriseId());
}

// This test verifies that the server uses default (Memfile) lease database
// backend when no backend is explicitly specified in the configuration.
TEST_F(JSONFileBackendTest, defaultLeaseDbBackend) {
    // This is basic server configuration which excludes lease database
    // backend specification. The default Memfile backend should be
    // initialized in this case.
    string config =
        "{ \"Dhcp6\": {"
        "\"interfaces-config\": {"
        "    \"interfaces\": [ ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "\"subnet6\": [ ],"
        "\"preferred-lifetime\": 3000, "
        "\"valid-lifetime\": 4000 }"
        "}";
    writeFile(TEST_FILE, config);

    // Create an instance of the server and initialize it.
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(srv.reset(new ControlledDhcpv6Srv(0)));
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
        // Ensure we have the proper schema with no transient data.
        createMySQLSchema();
    }

    /// @brief Destructor.
    ///
    /// Destroys MySQL schema.
    virtual ~JSONFileBackendMySQLTest() {
        // If data wipe enabled, delete transient data otherwise destroy the schema
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
        "{ \"Dhcp6\": {"
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
        "\"subnet6\": [ ],"
        "\"preferred-lifetime\": 3000, "
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
    boost::scoped_ptr<NakedControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(srv.reset(new NakedControlledDhcpv6Srv()));
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
