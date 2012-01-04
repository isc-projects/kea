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

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

#include <cc/data.h>

#include <config/ccsession.h>

#include <asiodns/asiodns.h>
#include <asiolink/asiolink.h>
#include <asiolink/io_address.h>
#include <asiolink/io_socket.h>
#include <asiolink/io_message.h>

#include <acl/acl.h>

#include <server_common/client.h>

#include <resolver/resolver.h>

#include <dns/tests/unittest_util.h>
#include <testutils/srv_test.h>
#include <testutils/portconfig.h>
#include <testutils/socket_request.h>

using namespace std;
using boost::scoped_ptr;
using namespace isc::acl;
using isc::acl::dns::RequestContext;
using namespace isc::data;
using namespace isc::testutils;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::server_common;
using isc::UnitTestUtil;

namespace {
class ResolverConfig : public ::testing::Test {
protected:
    IOService ios;
    DNSService dnss;
    Resolver server;
    scoped_ptr<const IOEndpoint> endpoint;
    scoped_ptr<const IOMessage> query_message;
    scoped_ptr<const Client> client;
    scoped_ptr<const RequestContext> request;
    ResolverConfig() :
        dnss(ios, NULL, NULL, NULL),
        sock_requestor_(dnss, address_store_, 53210)
    {
        server.setDNSService(dnss);
        server.setConfigured();
    }
    const RequestContext& createRequest(const string& source_addr) {
        endpoint.reset(IOEndpoint::create(IPPROTO_UDP, IOAddress(source_addr),
                                          53210));
        query_message.reset(new IOMessage(NULL, 0,
                                          IOSocket::getDummyUDPSocket(),
                                          *endpoint));
        client.reset(new Client(*query_message));
        request.reset(new RequestContext(client->getRequestSourceIPAddress(),
                                         NULL));
        return (*request);
    }
    void invalidTest(const string &JSON, const string& name);
    isc::server_common::portconfig::AddressList address_store_;
    isc::testutils::TestSocketRequestor sock_requestor_;
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
    ConstElementPtr config(Element::fromJSON("{"
                                             "\"forward_addresses\": ["
                                             " {"
                                             "   \"address\": \"192.0.2.1\","
                                             "   \"port\": 53"
                                             " }"
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
    ConstElementPtr config(Element::fromJSON("{"
                                             "\"root_addresses\": ["
                                             " {"
                                             "    \"address\": \"192.0.2.1\","
                                             "    \"port\": 53"
                                             " }"
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
    // Check it requests the correct addresses
    const char* tokens[] = {
        "TCP:127.0.0.1:53210:1",
        "UDP:127.0.0.1:53210:2",
        "TCP:::1:53210:3",
        "UDP:::1:53210:4",
        NULL
    };
    sock_requestor_.checkTokens(tokens, sock_requestor_.given_tokens_,
                                "Given tokens");
    // It returns back to empty set of addresses afterwards, so
    // they should be released
    sock_requestor_.checkTokens(tokens, sock_requestor_.released_tokens_,
                                "Released tokens");
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
    ConstElementPtr config = Element::fromJSON("{"
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

TEST_F(ResolverConfig, defaultQueryACL) {
    // If no configuration is loaded, the default ACL should reject everything.
    EXPECT_EQ(REJECT, server.getQueryACL().execute(createRequest("192.0.2.1")));
    EXPECT_EQ(REJECT, server.getQueryACL().execute(
                  createRequest("2001:db8::1")));

    // The following would be allowed if the server had loaded the default
    // configuration from the spec file.  In this context it should not have
    // happened, and they should be rejected just like the above cases.
    EXPECT_EQ(REJECT, server.getQueryACL().execute(createRequest("127.0.0.1")));
    EXPECT_EQ(REJECT, server.getQueryACL().execute(createRequest("::1")));
}

TEST_F(ResolverConfig, emptyQueryACL) {
    // Explicitly configured empty ACL should have the same effect.
    ConstElementPtr config(Element::fromJSON("{ \"query_acl\": [] }"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_EQ(REJECT, server.getQueryACL().execute(createRequest("192.0.2.1")));
    EXPECT_EQ(REJECT, server.getQueryACL().execute(
                  createRequest("2001:db8::1")));
}

TEST_F(ResolverConfig, queryACLIPv4) {
    // A simple "accept" query for a specific IPv4 address
    ConstElementPtr config(Element::fromJSON(
                               "{ \"query_acl\": "
                               "  [ {\"action\": \"ACCEPT\","
                               "     \"from\": \"192.0.2.1\"} ] }"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_EQ(ACCEPT, server.getQueryACL().execute(createRequest("192.0.2.1")));
    EXPECT_EQ(REJECT, server.getQueryACL().execute(
                  createRequest("2001:db8::1")));
}

TEST_F(ResolverConfig, queryACLIPv6) {
    // same for IPv6
    ConstElementPtr config(Element::fromJSON(
                               "{ \"query_acl\": "
                               "  [ {\"action\": \"ACCEPT\","
                               "     \"from\": \"2001:db8::1\"} ] }"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_EQ(REJECT, server.getQueryACL().execute(createRequest("192.0.2.1")));
    EXPECT_EQ(ACCEPT, server.getQueryACL().execute(
                  createRequest("2001:db8::1")));
}

TEST_F(ResolverConfig, multiEntryACL) {
    // A bit more complicated one: mixture of IPv4 and IPv6 with 3 rules
    // in total.  We shouldn't have to check so many variations of rules
    // as it should have been tested in the underlying ACL module.  All we
    // have to do to check is a reasonably complicated ACL configuration is
    // loaded as expected.
    ConstElementPtr config(Element::fromJSON(
                               "{ \"query_acl\": "
                               "  [ {\"action\": \"ACCEPT\","
                               "     \"from\": \"192.0.2.1\"},"
                               "    {\"action\": \"REJECT\","
                               "     \"from\": \"192.0.2.0/24\"},"
                               "    {\"action\": \"DROP\","
                               "     \"from\": \"2001:db8::1\"},"
                               "] }"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    EXPECT_EQ(ACCEPT, server.getQueryACL().execute(createRequest("192.0.2.1")));
    EXPECT_EQ(REJECT, server.getQueryACL().execute(createRequest("192.0.2.2")));
    EXPECT_EQ(DROP, server.getQueryACL().execute(
                  createRequest("2001:db8::1")));
    EXPECT_EQ(REJECT, server.getQueryACL().execute(
                  createRequest("2001:db8::2"))); // match the default rule
}


int
getResultCode(ConstElementPtr result) {
    int rcode;
    isc::config::parseAnswer(rcode, result);
    return (rcode);
}

TEST_F(ResolverConfig, queryACLActionOnly) {
    // "action only" rule will be accepted by the loader, which can
    // effectively change the default action.
    ConstElementPtr config(Element::fromJSON(
                               "{ \"query_acl\": "
                               "  [ {\"action\": \"ACCEPT\","
                               "     \"from\": \"192.0.2.1\"},"
                               "    {\"action\": \"DROP\"} ] }"));
    EXPECT_EQ(0, getResultCode(server.updateConfig(config)));
    EXPECT_EQ(ACCEPT, server.getQueryACL().execute(createRequest("192.0.2.1")));

    // We reject non matching queries by default, but the last resort
    // rule should have changed the action in that case to "DROP".
    EXPECT_EQ(DROP, server.getQueryACL().execute(createRequest("192.0.2.2")));
}

TEST_F(ResolverConfig, badQueryACL) {
    // Most of these cases shouldn't happen in practice because the syntax
    // check should be performed before updateConfig().  But we check at
    // least the server code won't crash even if an unexpected input is given.

    // ACL must be a list
    EXPECT_EQ(1, getResultCode(
                  server.updateConfig(
                      Element::fromJSON("{ \"query_acl\": 1 }"))));
    // Each rule must have "action" and "from"
    EXPECT_EQ(1, getResultCode(
                  server.updateConfig(
                      Element::fromJSON("{ \"query_acl\":"
                                        " [ {\"from\": \"192.0.2.1\"} ] }"))));
    // invalid "action"
    EXPECT_EQ(1, getResultCode(
                  server.updateConfig(
                      Element::fromJSON("{ \"query_acl\":"
                                        " [ {\"action\": 1,"
                                        "    \"from\": \"192.0.2.1\"}]}"))));
    EXPECT_EQ(1, getResultCode(
                  server.updateConfig(
                      Element::fromJSON("{ \"query_acl\":"
                                        " [ {\"action\": \"BADACTION\","
                                        "    \"from\": \"192.0.2.1\"}]}"))));
    // invalid "from"
    EXPECT_EQ(1, getResultCode(
                  server.updateConfig(
                      Element::fromJSON("{ \"query_acl\":"
                                        " [ {\"action\": \"ACCEPT\","
                                        "    \"from\": 53}]}"))));
    EXPECT_EQ(1, getResultCode(
                  server.updateConfig(
                      Element::fromJSON("{ \"query_acl\":"
                                        " [ {\"action\": \"ACCEPT\","
                                        "    \"from\": \"1922.0.2.1\"}]}"))));
}

}
