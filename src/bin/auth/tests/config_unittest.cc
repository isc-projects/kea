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

#include <cc/data.h>

#include <datasrc/memory_datasrc.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <auth/config.h>
#include <auth/common.h>

#include <testutils/mockups.h>

using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;

namespace {
class AuthConfigTest : public ::testing::Test {
protected:
    AuthConfigTest() : rrclass(RRClass::IN()), server(true, xfrout) {}
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
    parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"example.zone\"}]}]"));
    parser->commit();
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());
}

TEST_F(MemoryDatasrcConfigTest, addMultiZones) {
    parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"example.zone\"},"
                      "              {\"origin\": \"example.org\","
                      "               \"file\": \"example.org.zone\"},"
                      "              {\"origin\": \"example.net\","
                      "               \"file\": \"example.net.zone\"}]}]"));
    parser->commit();
    EXPECT_EQ(3, server.getMemoryDataSrc(rrclass)->getZoneCount());
}

TEST_F(MemoryDatasrcConfigTest, replace) {
    parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"example.zone\"}]}]"));
    parser->commit();
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());
    EXPECT_EQ(isc::datasrc::result::SUCCESS,
              server.getMemoryDataSrc(rrclass)->findZone(
                  Name("example.com")).code);

    // create a new parser, and install a new set of configuration.  It
    // should replace the old one.
    delete parser;
    parser = createAuthConfigParser(server, "datasources"); 
    parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.org\","
                      "               \"file\": \"example.org.zone\"},"
                      "              {\"origin\": \"example.net\","
                      "               \"file\": \"example.net.zone\"}]}]"));
    parser->commit();
    EXPECT_EQ(2, server.getMemoryDataSrc(rrclass)->getZoneCount());
    EXPECT_EQ(isc::datasrc::result::NOTFOUND,
              server.getMemoryDataSrc(rrclass)->findZone(
                  Name("example.com")).code);
}

TEST_F(MemoryDatasrcConfigTest, remove) {
    parser->build(Element::fromJSON(
                      "[{\"type\": \"memory\","
                      "  \"zones\": [{\"origin\": \"example.com\","
                      "               \"file\": \"example.zone\"}]}]"));
    parser->commit();
    EXPECT_EQ(1, server.getMemoryDataSrc(rrclass)->getZoneCount());

    delete parser;
    parser = createAuthConfigParser(server, "datasources"); 
    parser->build(Element::fromJSON("[]"));
    parser->commit();
    EXPECT_EQ(AuthSrv::MemoryDataSrcPtr(), server.getMemoryDataSrc(rrclass));
}

TEST_F(MemoryDatasrcConfigTest, adDuplicateZones) {
    EXPECT_THROW(parser->build(
                     Element::fromJSON(
                         "[{\"type\": \"memory\","
                         "  \"zones\": [{\"origin\": \"example.com\","
                         "               \"file\": \"example.zone\"},"
                         "              {\"origin\": \"example.com\","
                         "               \"file\": \"example.com.zone\"}]}]")),
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
}
