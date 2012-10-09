// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <fstream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp6/dhcp6_srv.h>
#include <dhcp6/config_parser.h>
#include <config/ccsession.h>
#include <dhcp/subnet.h>
#include <dhcp/cfgmgr.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::config;

namespace {

class Dhcp6ParserTest : public ::testing::Test {
public:
    Dhcp6ParserTest()
    :rcode_(-1) {
        // Open port 0 means to not do anything at all. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.
        srv_ = new Dhcpv6Srv(0);
    }

    ~Dhcp6ParserTest() {
        delete srv_;
    };

    Dhcpv6Srv* srv_;

    int rcode_;
    ConstElementPtr comment_;
};

// Goal of this test is a verification if a very simple config update
// with just a bumped version number. That's the simplest possible
// config update.
TEST_F(Dhcp6ParserTest, version) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_,
                    Element::fromJSON("{\"version\": 0}")));

    // returned value must be 0 (configuration accepted)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(0, rcode_);
}

/// The goal of this test is to verify that the code accepts only
/// valid commands and malformed or unsupported parameters are rejected.
TEST_F(Dhcp6ParserTest, bogus_command) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_,
                    Element::fromJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(1, rcode_);
}

/// The goal of this test is to verify if wrongly defined subnet will
/// be rejected. Properly defined subnet must include at least one
/// pool definition.
TEST_F(Dhcp6ParserTest, empty_subnet) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_,
                    Element::fromJSON("{ \"interface\": [ \"all\" ],"
                                      "\"preferred-lifetime\": 3000,"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet6\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);
}

/// The goal of this test is to verify if defined subnet uses global
/// parameter timer definitions.
TEST_F(Dhcp6ParserTest, subnet_global_defaults) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(3000, subnet->getPreferred());
    EXPECT_EQ(4000, subnet->getValid());
}

// This test checks if it is possible to override global values
// on a per subnet basis.
TEST_F(Dhcp6ParserTest, subnet_local) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"preferred-lifetime\": 3,"
        "    \"valid-lifetime\": 4,"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));

    // returned value should be 0 (configuration success)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getT1());
    EXPECT_EQ(2, subnet->getT2());
    EXPECT_EQ(3, subnet->getPreferred());
    EXPECT_EQ(4, subnet->getValid());
}

// Test verifies that a subnet with pool values that do not belong to that
// pool are rejected.
TEST_F(Dhcp6ParserTest, pool_out_of_subnet) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"4001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));

    // returned value must be 2 (values error)
    // as the pool does not belong to that subnet
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(2, rcode_);
}

// Goal of this test is to verify if pools can be defined
// using prefix/length notation. There is no separate test for min-max
// notation as it was tested in several previous tests.
TEST_F(Dhcp6ParserTest, pool_prefix_len) {

    ConstElementPtr x;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));

    // returned value must be 1 (configuration parse error)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(3000, subnet->getPreferred());
    EXPECT_EQ(4000, subnet->getValid());
}

};
