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

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/rrclass.h>
#include <dns/masterload.h>

#include <cc/data.h>

#include <datasrc/data_source.h>
#include <datasrc/memory_datasrc.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/common.h>

#include "datasrc_util.h"

#include <util/unittests/mock_socketsession.h>
#include <testutils/mockups.h>
#include <testutils/portconfig.h>
#include <testutils/socket_request.h>

#include <sstream>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::asiodns;
using namespace isc::auth::unittest;
using namespace isc::util::unittests;
using namespace isc::testutils;

namespace {
class AuthConfigTest : public ::testing::Test {
protected:
    AuthConfigTest() :
        dnss_(),
        rrclass(RRClass::IN()),
        server(xfrout, ddns_forwarder),
        // The empty string is expected value of the parameter of
        // requestSocket, not the app_name (there's no fallback, it checks
        // the empty string is passed).
        sock_requestor_(dnss_, address_store_, 53210, "")
    {
        server.setDNSService(dnss_);
    }
    MockDNSService dnss_;
    const RRClass rrclass;
    MockXfroutClient xfrout;
    MockSocketSessionForwarder ddns_forwarder;
    AuthSrv server;
    isc::server_common::portconfig::AddressList address_store_;
private:
    isc::testutils::TestSocketRequestor sock_requestor_;
};

TEST_F(AuthConfigTest, versionConfig) {
    // make sure it does not throw on 'version'
    EXPECT_NO_THROW(configureAuthServer(
                        server,
                        Element::fromJSON("{\"version\": 0}")));
}

TEST_F(AuthConfigTest, exceptionGuarantee) {
    using namespace isc::server_common::portconfig;
    AddressList a, b, c;
    a.push_back(AddressPair("127.0.0.1", 53210));
    server.setListenAddresses(a);
    b = server.getListenAddresses();
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.at(0).first, b.at(0).first);
    EXPECT_EQ(a.at(0).second, b.at(0).second);
    // This configuration contains an invalid item, which will trigger
    // an exception.
    EXPECT_THROW(configureAuthServer(
                     server,
                     Element::fromJSON(
                         "{ \"no_such_config_var\": 1}")),
                 AuthConfigError);
    // The server state shouldn't change
    c = server.getListenAddresses();
    EXPECT_EQ(a.size(), c.size());
    EXPECT_EQ(a.at(0).first, c.at(0).first);
    EXPECT_EQ(a.at(0).second, c.at(0).second);
}

TEST_F(AuthConfigTest, badConfig) {
    // These should normally not happen, but should be handled to avoid
    // an unexpected crash due to a bug of the caller.
    EXPECT_THROW(configureAuthServer(server, ElementPtr()), AuthConfigError);
    EXPECT_THROW(configureAuthServer(server, Element::fromJSON("[]")),
                                     AuthConfigError);
}

TEST_F(AuthConfigTest, unknownConfigVar) {
    EXPECT_THROW(createAuthConfigParser(server, "no_such_config_var"),
                 AuthConfigError);
}

TEST_F(AuthConfigTest, exceptionFromCommit) {
    EXPECT_THROW(configureAuthServer(server, Element::fromJSON(
                                         "{\"_commit_throw\": 10}")),
                 FatalError);
}

// Test invalid address configs are rejected
TEST_F(AuthConfigTest, invalidListenAddressConfig) {
    // This currently passes simply because the config doesn't know listen_on
    isc::testutils::portconfig::invalidListenAddressConfig(server);
}

// Try setting addresses trough config
TEST_F(AuthConfigTest, listenAddressConfig) {
    isc::testutils::portconfig::listenAddressConfig(server);

    // listenAddressConfig should have attempted to create 4 DNS server
    // objects: two IP addresses, TCP and UDP for each.  For UDP, the "SYNC_OK"
    // option should have been specified.
    EXPECT_EQ(2, dnss_.getTCPFdParams().size());
    EXPECT_EQ(2, dnss_.getUDPFdParams().size());
    EXPECT_EQ(DNSService::SERVER_SYNC_OK, dnss_.getUDPFdParams().at(0).options);
    EXPECT_EQ(DNSService::SERVER_SYNC_OK, dnss_.getUDPFdParams().at(1).options);
}

class StatisticsIntervalConfigTest : public AuthConfigTest {
protected:
    StatisticsIntervalConfigTest() :
        parser(createAuthConfigParser(server, "statistics-interval"))
    {}
    ~StatisticsIntervalConfigTest() {
        delete parser;
    }
    AuthConfigParser* parser;
};

}
