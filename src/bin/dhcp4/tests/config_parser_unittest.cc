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

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/config_parser.h>
#include <config/ccsession.h>
#include <dhcp/subnet.h>
#include <dhcp/cfgmgr.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::config;

namespace isc {
namespace dhcp {
extern Uint32Storage uint32_defaults;
}
}

namespace {

class Dhcp4ParserTest : public ::testing::Test {
public:
    Dhcp4ParserTest()
    :rcode_(-1) {
        // Open port 0 means to not do anything at all. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.
        srv_ = new Dhcpv4Srv(0);
    }

    // Checks if global parameter of name have expected_value
    void checkGlobalUint32(string name, uint32_t expected_value) {
        Uint32Storage::const_iterator it = uint32_defaults.find(name);
        if (it == uint32_defaults.end()) {
            ADD_FAILURE() << "Expected uint32 with name " << name
                          << " not found";
            return;
        }
        EXPECT_EQ(expected_value, it->second);
    }

    // Checks if config_result (result of DHCP server configuration) has
    // expected code (0 for success, other for failures).
    // Also stores result in rcode_ and comment_.
    void checkResult(ConstElementPtr status, int expected_code) {
        ASSERT_TRUE(status);
        comment_ = parseAnswer(rcode_, status);
        EXPECT_EQ(expected_code, rcode_);
    }

    ~Dhcp4ParserTest() {
        delete srv_;
    };

    Dhcpv4Srv* srv_;

    int rcode_;
    ConstElementPtr comment_;
};

// Goal of this test is a verification if a very simple config update
// with just a bumped version number. That's the simplest possible
// config update.
TEST_F(Dhcp4ParserTest, version) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0}")));

    // returned value must be 0 (configuration accepted)
    checkResult(x, 0);
}

/// The goal of this test is to verify that the code accepts only
/// valid commands and malformed or unsupported parameters are rejected.
TEST_F(Dhcp4ParserTest, bogusCommand) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    checkResult(x, 1);
}

/// The goal of this test is to verify if wrongly defined subnet will
/// be rejected. Properly defined subnet must include at least one
/// pool definition.
TEST_F(Dhcp4ParserTest, emptySubnet) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{ \"interface\": [ \"all\" ],"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet4\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);

    checkGlobalUint32("rebind-timer", 2000);
    checkGlobalUint32("renew-timer", 1000);
    checkGlobalUint32("valid-lifetime", 4000);
}

/// The goal of this test is to verify if defined subnet uses global
/// parameter timer definitions.
TEST_F(Dhcp4ParserTest, subnetGlobalDefaults) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());
}

// This test checks if it is possible to override global values
// on a per subnet basis.
TEST_F(Dhcp4ParserTest, subnetLocal) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"valid-lifetime\": 4,"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getT1());
    EXPECT_EQ(2, subnet->getT2());
    EXPECT_EQ(4, subnet->getValid());
}

// Test verifies that a subnet with pool values that do not belong to that
// pool are rejected.
TEST_F(Dhcp4ParserTest, poolOutOfSubnet) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.4.0/28\" ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value must be 2 (values error)
    // as the pool does not belong to that subnet
    checkResult(status, 2);
}

// Goal of this test is to verify if pools can be defined
// using prefix/length notation. There is no separate test for min-max
// notation as it was tested in several previous tests.
TEST_F(Dhcp4ParserTest, poolPrefixLen) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.128/28\" ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value must be 0 (configuration accepted)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());
}

/// This test checks if Uint32Parser can really parse the whole range
/// and properly err of out of range values. As we can't call Uint32Parser
/// directly, we are exploiting the fact that it is used to parse global
/// parameter renew-timer and the results are stored in uint32_defaults.
TEST_F(Dhcp4ParserTest, Uint32Parser) {

    ConstElementPtr status;

    // CASE 1: 0 - minimum value, should work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": 0}")));

    // returned value must be ok (0 is a proper value)
    checkResult(status, 0);
    checkGlobalUint32("renew-timer", 0);

    // CASE 2: 4294967295U (UINT_MAX) should work as well
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": 4294967295}")));

    // returned value must be ok (0 is a proper value)
    checkResult(status, 0);
    checkGlobalUint32("renew-timer", 4294967295U);

    // CASE 3: 4294967296U (UINT_MAX + 1) should not work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": 4294967296}")));

    // returned value must be rejected (1 configuration error)
    checkResult(status, 1);

    // CASE 4: -1 (UINT_MIN -1 ) should not work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": -1}")));

    // returned value must be rejected (1 configuration error)
    checkResult(status, 1);
}

};
