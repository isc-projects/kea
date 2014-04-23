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

#include <config/ccsession.h>
#include <dhcp/dhcp6.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>

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


class ControlledJSONDhcpv6SrvTest : public ::testing::Test {
public:
    ControlledJSONDhcpv6SrvTest() {
    }

    ~ControlledJSONDhcpv6SrvTest() {
    };

    void writeFile(const std::string& file_name, const std::string& content) {
        static_cast<void>(unlink(file_name.c_str()));

        ofstream out(file_name.c_str(), ios::trunc);
        EXPECT_TRUE(out.is_open());
        out << content;
        out.close();
    }

    static const char* TEST_FILE;
};

const char* ControlledJSONDhcpv6SrvTest::TEST_FILE = "test-config.json";

// This test checks if configuration can be read from a JSON file.
TEST_F(ControlledJSONDhcpv6SrvTest, jsonFile) {

    // Prepare configuration file.
    string config = "{ \"interfaces\": [ \"*\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " },"
        " {"
        "    \"pool\": [ \"2001:db8:2::/80\" ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 0"
        " },"
        " {"
        "    \"pool\": [ \"2001:db8:3::/80\" ],"
        "    \"subnet\": \"2001:db8:3::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";
    writeFile(TEST_FILE, config);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using the config file.
    EXPECT_TRUE(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets = CfgMgr::instance().getSubnets6();
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
TEST_F(ControlledJSONDhcpv6SrvTest, comments) {

    string config_hash_comments = "# This is a comment. It should be \n"
        "#ignored. Real config starts in line below\n"
        "{ \"interfaces\": [ \"*\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, \n"
        "# comments in the middle should be ignored, too\n"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    /// @todo: Implement C++-style (// ...) comments
    /// @todo: Implement C-style (/* ... */) comments

    writeFile(TEST_FILE, config_hash_comments);

    // Now initialize the server
    boost::scoped_ptr<ControlledDhcpv6Srv> srv;
    ASSERT_NO_THROW(
        srv.reset(new ControlledDhcpv6Srv(0))
    );

    // And configure it using config without
    EXPECT_TRUE(srv->init(TEST_FILE));

    // Now check if the configuration has been applied correctly.
    const Subnet6Collection* subnets = CfgMgr::instance().getSubnets6();
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

} // End of anonymous namespace
