// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <gtest/gtest.h>

#include <cc/data.h>

#include <asiolink/asiolink.h>

#include <resolver/resolver.h>

#include <dns/tests/unittest_util.h>
#include <testutils/srv_test.h>
#include <testutils/portconfig.h>

using namespace std;
using namespace isc::data;
using namespace isc::testutils;
using namespace asiolink;
using isc::UnitTestUtil;

namespace {
class ResolverConfig : public ::testing::Test {
    public:
        IOService ios;
        DNSService dnss;
        Resolver server;
        ResolverConfig() :
            dnss(ios, NULL, NULL, NULL)
        {
            server.setDNSService(dnss);
            server.setConfigured();
        }
        void invalidTest(const string &JSON, const string& name);
};

TEST_F(ResolverConfig, forwardAddresses) {
    // Default value should be fully recursive
    EXPECT_TRUE(server.getForwardAddresses().empty());
    EXPECT_FALSE(server.isForwarding());

    // Try putting there some addresses
    vector<pair<string, uint16_t> > addresses;
    addresses.push_back(pair<string, uint16_t>(DEFAULT_REMOTE_ADDRESS, 53));
    addresses.push_back(pair<string, uint16_t>("::1", 53));
    server.setForwardAddresses(addresses);
    EXPECT_EQ(2, server.getForwardAddresses().size());
    EXPECT_EQ("::1", server.getForwardAddresses()[1].first);
    EXPECT_TRUE(server.isForwarding());

    // Is it independent from what we do with the vector later?
    addresses.clear();
    EXPECT_EQ(2, server.getForwardAddresses().size());

    // Did it return to fully recursive?
    server.setForwardAddresses(addresses);
    EXPECT_TRUE(server.getForwardAddresses().empty());
    EXPECT_FALSE(server.isForwarding());
}

TEST_F(ResolverConfig, forwardAddressConfig) {
    // Try putting there some address
    ElementPtr config(Element::fromJSON("{"
        "\"forward_addresses\": ["
        "   {"
        "       \"address\": \"192.0.2.1\","
        "       \"port\": 53"
        "   }"
        "]"
        "}"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_TRUE(server.isForwarding());
    ASSERT_EQ(1, server.getForwardAddresses().size());
    EXPECT_EQ("192.0.2.1", server.getForwardAddresses()[0].first);
    EXPECT_EQ(53, server.getForwardAddresses()[0].second);

    // And then remove all addresses
    config = Element::fromJSON("{"
        "\"forward_addresses\": null"
        "}");
    result = server.updateConfig(config);
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_FALSE(server.isForwarding());
    EXPECT_EQ(0, server.getForwardAddresses().size());
}

TEST_F(ResolverConfig, rootAddressConfig) {
    // Try putting there some address
    ElementPtr config(Element::fromJSON("{"
        "\"root_addresses\": ["
        "   {"
        "       \"address\": \"192.0.2.1\","
        "       \"port\": 53"
        "   }"
        "]"
        "}"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    ASSERT_EQ(1, server.getRootAddresses().size());
    EXPECT_EQ("192.0.2.1", server.getRootAddresses()[0].first);
    EXPECT_EQ(53, server.getRootAddresses()[0].second);

    // And then remove all addresses
    config = Element::fromJSON("{"
        "\"root_addresses\": null"
        "}");
    result = server.updateConfig(config);
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_EQ(0, server.getRootAddresses().size());
}

void
ResolverConfig::invalidTest(const string &JSON, const string& name) {
    isc::testutils::portconfig::configRejected(server, JSON, name);
}

TEST_F(ResolverConfig, invalidForwardAddresses) {
    // Try torturing it with some invalid inputs
    invalidTest("{"
        "\"forward_addresses\": \"error\""
        "}", "Invalid type");
    invalidTest("{"
        "\"forward_addresses\": [{}]"
        "}", "Empty element");
    invalidTest("{"
        "\"forward_addresses\": [{"
        "   \"port\": 1.5,"
        "   \"address\": \"192.0.2.1\""
        "}]}", "Float port");
    invalidTest("{"
        "\"forward_addresses\": [{"
        "   \"port\": -5,"
        "   \"address\": \"192.0.2.1\""
        "}]}", "Negative port");
    invalidTest("{"
        "\"forward_addresses\": [{"
        "   \"port\": 53,"
        "   \"address\": \"bad_address\""
        "}]}", "Bad address");
}

// Try setting the addresses directly
TEST_F(ResolverConfig, listenAddresses) {
    isc::testutils::portconfig::listenAddresses(server);
}

// Try setting some addresses and a rollback
TEST_F(ResolverConfig, listenAddressConfig) {
    isc::testutils::portconfig::listenAddressConfig(server);
}

// Try some invalid configs are rejected
TEST_F(ResolverConfig, invalidListenAddresses) {
    isc::testutils::portconfig::invalidListenAddressConfig(server);
}

// Just test it sets and gets the values correctly
TEST_F(ResolverConfig, timeouts) {
    server.setTimeouts(0, 1, 2, 3);
    EXPECT_EQ(0, server.getQueryTimeout());
    EXPECT_EQ(1, server.getClientTimeout());
    EXPECT_EQ(2, server.getLookupTimeout());
    EXPECT_EQ(3, server.getRetries());
    server.setTimeouts();
    EXPECT_EQ(2000, server.getQueryTimeout());
    EXPECT_EQ(4000, server.getClientTimeout());
    EXPECT_EQ(30000, server.getLookupTimeout());
    EXPECT_EQ(3, server.getRetries());
}

TEST_F(ResolverConfig, timeoutsConfig) {
    ElementPtr config = Element::fromJSON("{"
            "\"timeout_query\": 1000,"
            "\"timeout_client\": 2000,"
            "\"timeout_lookup\": 3000,"
            "\"retries\": 4"
            "}");
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_EQ(1000, server.getQueryTimeout());
    EXPECT_EQ(2000, server.getClientTimeout());
    EXPECT_EQ(3000, server.getLookupTimeout());
    EXPECT_EQ(4, server.getRetries());
}

TEST_F(ResolverConfig, invalidTimeoutsConfig) {
    invalidTest("{"
        "\"timeout_query\": \"error\""
        "}", "Wrong query element type");
    invalidTest("{"
        "\"timeout_query\": -2"
        "}", "Negative query timeout");
    invalidTest("{"
        "\"timeout_client\": \"error\""
        "}", "Wrong client element type");
    invalidTest("{"
        "\"timeout_client\": -2"
        "}", "Negative client timeout");
    invalidTest("{"
        "\"timeout_lookup\": \"error\""
        "}", "Wrong lookup element type");
    invalidTest("{"
        "\"timeout_lookup\": -2"
        "}", "Negative lookup timeout");
    invalidTest("{"
        "\"retries\": \"error\""
        "}", "Wrong retries element type");
    invalidTest("{"
        "\"retries\": -1"
        "}", "Negative number of retries");
}

}
