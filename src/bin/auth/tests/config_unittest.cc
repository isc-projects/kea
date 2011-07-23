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

#include <datasrc/memory_datasrc.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/common.h>

#include <testutils/mockups.h>
#include <testutils/portconfig.h>

using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::asiodns;
using namespace isc::asiolink;

namespace {
class AuthConfigTest : public ::testing::Test {
protected:
    AuthConfigTest() :
        dnss_(ios_, NULL, NULL, NULL),
        rrclass(RRClass::IN()),
        server(true, xfrout)
    {
        server.setDNSService(dnss_);
    }
    IOService ios_;
    DNSService dnss_;
    const RRClass rrclass;
    MockXfroutClient xfrout;
    AuthSrv server;
};

TEST_F(AuthConfigTest, datasourceConfig) {
    // By default, we don't have any in-memory data source.
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
    configureAuthServer(server, Element::fromJSON(
                            "{\"datasources\": [{\"type\": \"memory\"}]}"));
    // after successful configuration, we should have one (with empty zoneset).
    ASSERT_NE(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
    EXPECT_EQ(0, server.getMemoryDataSrc(rrclass)->getZoneCount());
}

TEST_F(AuthConfigTest, databaseConfig) {
    // right now, "database_file" is handled separately, so the parser
    // doesn't recognize it, but it shouldn't throw an exception due to that.
    EXPECT_NO_THROW(configureAuthServer(
                        server,
                        Element::fromJSON(
                            "{\"database_file\": \"should_be_ignored\"}")));
}

TEST_F(AuthConfigTest, versionConfig) {
    // make sure it does not throw on 'version'
    EXPECT_NO_THROW(configureAuthServer(
                        server,
                        Element::fromJSON("{\"version\": 0}")));
}

TEST_F(AuthConfigTest, exceptionGuarantee) {
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
    // This configuration contains an invalid item, which will trigger
    // an exception.
    EXPECT_THROW(configureAuthServer(
                     server,
                     Element::fromJSON(
                         "{\"datasources\": [{\"type\": \"memory\"}], "
                         " \"no_such_config_var\": 1}")),
                 AuthConfigError);
    // The server state shouldn't change
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
}

TEST_F(AuthConfigTest, exceptionConversion) {
    // This configuration contains a bogus RR class, which will trigger an
    // exception from libdns++.  configureAuthServer() should convert this
    // to AuthConfigError and rethrow the converted one.
    EXPECT_THROW(configureAuthServer(
                     server,
                     Element::fromJSON(
                         "{\"datasources\": "
                         " [{\"type\": \"memory\","
                         "   \"class\": \"BADCLASS\","
                         "   \"zones\": [{\"origin\": \"example.com\","
                         "                \"file\": \"example.zone\"}]}]}")),
                 AuthConfigError);
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
}

class MemoryDatasrcConfigTest : public AuthConfigTest {
protected:
    MemoryDatasrcConfigTest() :
        parser(createAuthConfigParser(server, "datasources"))
    {}
    ~MemoryDatasrcConfigTest() {
        delete parser;
    }
    AuthConfigParser* parser;
};

TEST_F(MemoryDatasrcConfigTest, addZeroDataSrc) {
    parser->build(Element::fromJSON("[]"));
    parser->commit();
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
}

TEST_F(MemoryDatasrcConfigTest, addEmpty) {
    // By default, we don't have any in-memory data source.
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
    parser->build(Element::fromJSON("[{\"type\": \"memory\"}]"));
    parser->commit();
    EXPECT_EQ(0, server.getMemoryDataSrc(rrclass)->getZoneCount());
}

TEST_F(MemoryDatasrcConfigTest, addZeroZone) {
    parser->build(Element::fromJSON("[{\"type\": \"memory\","
                                    "  \"zones\": []}]"));
    parser->commit();
    EXPECT_EQ(0, server.getMemoryDataSrc(rrclass)->getZoneCount());
}

TEST_F(MemoryDatasrcConfigTest, addOneZone) {
    EXPECT_NO_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.zone\"}]}]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());
    // Check it actually loaded something
    EXPECT_EQ(ZoneFinder::SUCCESS, server.getMemoryDataSrc(rrclass)->findZone(
        Name("ns.example.com.")).zone_finder->find(Name("ns.example.com."),
        RRType::A()).code);
}

TEST_F(MemoryDatasrcConfigTest, addMultiZones) {
    EXPECT_NO_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.zone\"},"
                      "              {\"origin\": \"example.org\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.org.zone\"},"
                      "              {\"origin\": \"example.net\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.net.zone\"}]}]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(3, server.getMemoryDataSrc(rrclass)->getZoneCount());
}

TEST_F(MemoryDatasrcConfigTest, replace) {
    EXPECT_NO_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.zone\"}]}]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());
    EXPECT_EQ(isc::datasrc::result::SUCCESS,
              server.getMemoryDataSrc(rrclass)->findZone(
                  Name("example.com")).code);

    // create a new parser, and install a new set of configuration.  It
    // should replace the old one.
    delete parser;
    parser = createAuthConfigParser(server, "datasources"); 
    EXPECT_NO_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.org\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.org.zone\"},"
                      "              {\"origin\": \"example.net\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.net.zone\"}]}]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(2, server.getMemoryDataSrc(rrclass)->getZoneCount());
    EXPECT_EQ(isc::datasrc::result::NOTFOUND,
              server.getMemoryDataSrc(rrclass)->findZone(
                  Name("example.com")).code);
}

TEST_F(MemoryDatasrcConfigTest, exception) {
    // Load a zone
    EXPECT_NO_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.zone\"}]}]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());
    EXPECT_EQ(isc::datasrc::result::SUCCESS,
              server.getMemoryDataSrc(rrclass)->findZone(
                  Name("example.com")).code);

    // create a new parser, and try to load something. It will throw,
    // the given master file should not exist
    delete parser;
    parser = createAuthConfigParser(server, "datasources");
    EXPECT_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.org\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.org.zone\"},"
                      "              {\"origin\": \"example.net\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/nonexistent.zone\"}]}]")), isc::dns::MasterLoadError);
    // As that one throwed exception, it is not expected from us to
    // commit it

    // The original should be untouched
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());
    EXPECT_EQ(isc::datasrc::result::SUCCESS,
              server.getMemoryDataSrc(rrclass)->findZone(
                  Name("example.com")).code);
}

TEST_F(MemoryDatasrcConfigTest, remove) {
    EXPECT_NO_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"" TEST_DATA_DIR
                      "/example.zone\"}]}]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());

    delete parser;
    parser = createAuthConfigParser(server, "datasources"); 
    EXPECT_NO_THROW(parser->build(Element::fromJSON("[]")));
    EXPECT_NO_THROW(parser->commit());
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
}

TEST_F(MemoryDatasrcConfigTest, adDuplicateZones) {
    EXPECT_THROW(parser->build(
                     Element::fromJSON(
                         "[{\"type\": \"memory\","
                         "  \"zones\": [{\"origin\": \"example.com\","
                         "               \"file\": \"" TEST_DATA_DIR
                         "/example.zone\"},"
                         "              {\"origin\": \"example.com\","
                         "               \"file\": \"" TEST_DATA_DIR
                         "/example.com.zone\"}]}]")),
                 AuthConfigError);
}

TEST_F(MemoryDatasrcConfigTest, addBadZone) {
    // origin is missing
    EXPECT_THROW(parser->build(
                     Element::fromJSON(
                         "[{\"type\": \"memory\","
                         "  \"zones\": [{\"file\": \"example.zone\"}]}]")),
                 AuthConfigError);

    // missing zone file
    EXPECT_THROW(parser->build(
                     Element::fromJSON(
                         "[{\"type\": \"memory\","
                         "  \"zones\": [{\"origin\": \"example.com\"}]}]")),
                 AuthConfigError);

    // bogus origin name
    EXPECT_THROW(parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example..com\","
                      "               \"file\": \"example.zone\"}]}]")),
                 EmptyLabel);

    // bogus RR class name
    EXPECT_THROW(parser->build(
                     Element::fromJSON(
                         "[{\"type\": \"memory\","
                         "  \"class\": \"BADCLASS\","
                         "  \"zones\": [{\"origin\": \"example.com\","
                         "               \"file\": \"example.zone\"}]}]")),
                 InvalidRRClass);

    // valid RR class, but not currently supported
    EXPECT_THROW(parser->build(
                     Element::fromJSON(
                         "[{\"type\": \"memory\","
                         "  \"class\": \"CH\","
                         "  \"zones\": [{\"origin\": \"example.com\","
                         "               \"file\": \"example.zone\"}]}]")),
                 isc::InvalidParameter);
}

TEST_F(MemoryDatasrcConfigTest, badDatasrcType) {
    EXPECT_THROW(parser->build(Element::fromJSON("[{\"type\": \"badsrc\"}]")),
                 AuthConfigError);
    EXPECT_THROW(parser->build(Element::fromJSON("[{\"notype\": \"memory\"}]")),
                 AuthConfigError);
    EXPECT_THROW(parser->build(Element::fromJSON("[{\"type\": 1}]")),
                                      isc::data::TypeError);
    EXPECT_THROW(parser->build(Element::fromJSON("[{\"type\": \"memory\"},"
                                                 " {\"type\": \"memory\"}]")),
                 AuthConfigError);
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

TEST_F(StatisticsIntervalConfigTest, setInterval) {
    // initially the timer is not configured.
    EXPECT_EQ(0, server.getStatisticsTimerInterval());

    // initialize the timer
    parser->build(Element::fromJSON("5"));
    parser->commit();
    EXPECT_EQ(5, server.getStatisticsTimerInterval());

    // reset the timer with a new interval
    delete parser;
    parser = createAuthConfigParser(server, "statistics-interval");
    ASSERT_NE(static_cast<void*>(NULL), parser);
    parser->build(Element::fromJSON("10"));
    parser->commit();
    EXPECT_EQ(10, server.getStatisticsTimerInterval());

    // disable the timer again
    delete parser;
    parser = createAuthConfigParser(server, "statistics-interval");
    ASSERT_NE(static_cast<void*>(NULL), parser);
    parser->build(Element::fromJSON("0"));
    parser->commit();
    EXPECT_EQ(0, server.getStatisticsTimerInterval());
}

TEST_F(StatisticsIntervalConfigTest, badInterval) {
    EXPECT_THROW(parser->build(Element::fromJSON("\"should be integer\"")),
                 isc::data::TypeError);
    EXPECT_THROW(parser->build(Element::fromJSON("2.5")),
                 isc::data::TypeError);
    EXPECT_THROW(parser->build(Element::fromJSON("-1")), AuthConfigError);
    // bounds check: interval value must be equal to or shorter than
    // 86400 seconds (1 day)
    EXPECT_NO_THROW(parser->build(Element::fromJSON("86400")));
    EXPECT_THROW(parser->build(Element::fromJSON("86401")), AuthConfigError);
}
}
