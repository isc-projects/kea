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

#include <config.h>

#include <string>

#include <gtest/gtest.h>

#include <cc/data.h>

#include <asiolink/asiolink.h>

#include <resolver/resolver.h>

#include <dns/tests/unittest_util.h>
#include <testutils/srv_test.h>

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
        }
        void invalidTest(const string &JOSN);
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
ResolverConfig::invalidTest(const string &JOSN) {
    ElementPtr config(Element::fromJSON(JOSN));
    EXPECT_FALSE(server.updateConfig(config)->equals(
        *isc::config::createAnswer())) << "Accepted config " << JOSN << endl;
}

TEST_F(ResolverConfig, invalidForwardAddresses) {
    // Try torturing it with some invalid inputs
    invalidTest("{"
        "\"forward_addresses\": \"error\""
        "}");
    invalidTest("{"
        "\"forward_addresses\": [{}]"
        "}");
    invalidTest("{"
        "\"forward_addresses\": [{"
        "   \"port\": 1.5,"
        "   \"address\": \"192.0.2.1\""
        "}]}");
    invalidTest("{"
        "\"forward_addresses\": [{"
        "   \"port\": -5,"
        "   \"address\": \"192.0.2.1\""
        "}]}");
    invalidTest("{"
        "\"forward_addresses\": [{"
        "   \"port\": 53,"
        "   \"address\": \"bad_address\""
        "}]}");
}

TEST_F(ResolverConfig, listenAddresses) {
    // Default value should be fully recursive
    EXPECT_TRUE(server.getListenAddresses().empty());

    // Try putting there some addresses
    vector<pair<string, uint16_t> > addresses;
    addresses.push_back(pair<string, uint16_t>("127.0.0.1", 5321));
    addresses.push_back(pair<string, uint16_t>("::1", 5321));
    server.setListenAddresses(addresses);
    EXPECT_EQ(2, server.getListenAddresses().size());
    EXPECT_EQ("::1", server.getListenAddresses()[1].first);

    // Is it independent from what we do with the vector later?
    addresses.clear();
    EXPECT_EQ(2, server.getListenAddresses().size());

    // Did it return to fully recursive?
    server.setListenAddresses(addresses);
    EXPECT_TRUE(server.getListenAddresses().empty());
}

TEST_F(ResolverConfig, DISABLED_listenAddressConfig) {
    // Try putting there some address
    ElementPtr config(Element::fromJSON("{"
        "\"listen_on\": ["
        "   {"
        "       \"address\": \"127.0.0.1\","
        "       \"port\": 5321"
        "   }"
        "]"
        "}"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    ASSERT_EQ(1, server.getListenAddresses().size());
    EXPECT_EQ("127.0.0.1", server.getListenAddresses()[0].first);
    EXPECT_EQ(5321, server.getListenAddresses()[0].second);

    // As this is example address, the machine should not have it on
    // any interface
    // FIXME: This test aborts, because it tries to rollback and
    //     it is impossible, since the sockets are not closed.
    //     Once #388 is solved, enable this test.
    config = Element::fromJSON("{"
        "\"listen_on\": ["
        "   {"
        "       \"address\": \"192.0.2.0\","
        "       \"port\": 5321"
        "   }"
        "]"
        "}");
    result = server.updateConfig(config);
    EXPECT_FALSE(result->equals(*isc::config::createAnswer()));
    ASSERT_EQ(1, server.getListenAddresses().size());
    EXPECT_EQ("127.0.0.1", server.getListenAddresses()[0].first);
    EXPECT_EQ(5321, server.getListenAddresses()[0].second);
}

TEST_F(ResolverConfig, invalidListenAddresses) {
    // Try torturing it with some invalid inputs
    invalidTest("{"
        "\"listen_on\": \"error\""
        "}");
    invalidTest("{"
        "\"listen_on\": [{}]"
        "}");
    invalidTest("{"
        "\"listen_on\": [{"
        "   \"port\": 1.5,"
        "   \"address\": \"192.0.2.1\""
        "}]}");
    invalidTest("{"
        "\"listen_on\": [{"
        "   \"port\": -5,"
        "   \"address\": \"192.0.2.1\""
        "}]}");
    invalidTest("{"
        "\"listen_on\": [{"
        "   \"port\": 53,"
        "   \"address\": \"bad_address\""
        "}]}");
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
        "}");
    invalidTest("{"
        "\"timeout_query\": -2"
        "}");
    invalidTest("{"
        "\"timeout_client\": \"error\""
        "}");
    invalidTest("{"
        "\"timeout_client\": -2"
        "}");
    invalidTest("{"
        "\"timeout_lookup\": \"error\""
        "}");
    invalidTest("{"
        "\"timeout_lookup\": -2"
        "}");
    invalidTest("{"
        "\"retries\": \"error\""
        "}");
    invalidTest("{"
        "\"retries\": -1"
        "}");
}

}
