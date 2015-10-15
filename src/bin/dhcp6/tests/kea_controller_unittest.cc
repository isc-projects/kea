// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
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
using namespace isc::dhcp;
using namespace isc::hooks;

namespace {

class NakedControlledDhcpv6Srv: public ControlledDhcpv6Srv {
    // "Naked" DHCPv6 server, exposes internal fields
public:
    NakedControlledDhcpv6Srv():ControlledDhcpv6Srv(0) { }
};


class JSONFileBackendTest : public ::testing::Test {
public:
    JSONFileBackendTest() {
    }

    ~JSONFileBackendTest() {
        LeaseMgrFactory::destroy();
        isc::log::setDefaultLoggingOutput();
        static_cast<void>(remove(TEST_FILE));
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
    /// Internally, this method calls @c IfaceMgr::receive6 to run the
    /// callbacks for the installed timers.
    ///
    /// @param timeout_ms Amount of time after which the method returns.
    void runTimersWithTimeout(const long timeout_ms) {
        isc::util::Stopwatch stopwatch;
        while (stopwatch.getTotalMilliseconds() < timeout_ms) {
            // Block for up to one millisecond waiting for the timers'
            // callbacks to be executed.
            IfaceMgr::instancePtr()->receive6(0, 1000);
        }
    }

    static const char* TEST_FILE;
};

const char* JSONFileBackendTest::TEST_FILE = "test-config.json";

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

// This test checks if configuration can be read from a JSON file.
TEST_F(JSONFileBackendTest, comments) {

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

    /// @todo: Implement C++-style (// ...) comments
    /// @todo: Implement C-style (/* ... */) comments

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

    // Create an instance of the server and intialize it.
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
    LeaseMgr& lease_mgr = LeaseMgrFactory().instance();
    ASSERT_NO_THROW(lease_mgr.addLease(lease_expired));
    ASSERT_NO_THROW(lease_mgr.addLease(lease_reclaimed));

    // Make sure they have been added.
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::1")));
    ASSERT_TRUE(lease_mgr.getLease6(Lease::TYPE_NA, IOAddress("3000::2")));

    // Poll the timers for a while to make sure that each of them is executed
    // at least once.
    ASSERT_NO_THROW(runTimersWithTimeout(5000));

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

} // End of anonymous namespace
