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

#include <cassert>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>

#include <config/ccsession.h>

#include <datasrc/memory_datasrc.h>

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/command.h>

#include <asiolink/asiolink.h>

#include <testutils/mockups.h>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::config;

namespace {
class AuthConmmandTest : public ::testing::Test {
protected:
    AuthConmmandTest() : server(false, xfrout), rcode(-1) {
        server.setStatisticsSession(&statistics_session);
    }
    void checkAnswer(const int expected_code) {
        parseAnswer(rcode, result);
        EXPECT_EQ(expected_code, rcode);
    }
    MockSession statistics_session;
    MockXfroutClient xfrout;
    AuthSrv server;
    AuthSrv::ConstMemoryDataSrcPtr memory_datasrc;
    ConstElementPtr result;
    int rcode;
public:
    void stopServer();          // need to be public for boost::bind
};

TEST_F(AuthConmmandTest, unknownCommand) {
    result = execAuthServerCommand(server, "no_such_command",
                                   ConstElementPtr());
    parseAnswer(rcode, result);
    EXPECT_EQ(1, rcode);
}

TEST_F(AuthConmmandTest, DISABLED_unexpectedException) {
    // execAuthServerCommand() won't catch standard exceptions.
    // Skip this test for now: ModuleCCSession doesn't seem to validate
    // commands.
    EXPECT_THROW(execAuthServerCommand(server, "_throw_exception",
                                       ConstElementPtr()),
                 runtime_error);
}

TEST_F(AuthConmmandTest, sendStatistics) {
    result = execAuthServerCommand(server, "sendstats", ConstElementPtr());
    // Just check some message has been sent.  Detailed tests specific to
    // statistics are done in its own tests.
    EXPECT_EQ("Stats", statistics_session.getMessageDest());
    checkAnswer(0);
}

void
AuthConmmandTest::stopServer() {
    result = execAuthServerCommand(server, "shutdown", ConstElementPtr());
    parseAnswer(rcode, result);
    assert(rcode == 0); // make sure the test stops when something is wrong
}

TEST_F(AuthConmmandTest, shutdown) {
    isc::asiolink::IntervalTimer itimer(server.getIOService());
    itimer.setup(boost::bind(&AuthConmmandTest::stopServer, this), 1);
    server.getIOService().run();
    EXPECT_EQ(0, rcode);
}

// A helper function commonly used for the "loadzone" command tests.
// It configures the server with a memory data source containing two
// zones, and checks the zones are correctly loaded.
void
zoneChecks(AuthSrv& server) {
    EXPECT_TRUE(server.getMemoryDataSrc(RRClass::IN()));
    EXPECT_EQ(Zone::SUCCESS, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone->
              find(Name("ns.test1.example"), RRType::A()).code);
    EXPECT_EQ(Zone::NXRRSET, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone->
              find(Name("ns.test1.example"), RRType::AAAA()).code);
    EXPECT_EQ(Zone::SUCCESS, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone->
              find(Name("ns.test2.example"), RRType::A()).code);
    EXPECT_EQ(Zone::NXRRSET, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone->
              find(Name("ns.test2.example"), RRType::AAAA()).code);
}

void
configureZones(AuthSrv& server) {
    ASSERT_EQ(0, system(INSTALL_PROG " " TEST_DATA_DIR "/test1.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    ASSERT_EQ(0, system(INSTALL_PROG " " TEST_DATA_DIR "/test2.zone.in "
                        TEST_DATA_BUILDDIR "/test2.zone.copied"));
    configureAuthServer(server, Element::fromJSON(
                            "{\"datasources\": "
                            " [{\"type\": \"memory\","
                            "   \"zones\": "
                            "[{\"origin\": \"test1.example\","
                            "  \"file\": \""
                               TEST_DATA_BUILDDIR "/test1.zone.copied\"},"
                            " {\"origin\": \"test2.example\","
                            "  \"file\": \""
                               TEST_DATA_BUILDDIR "/test2.zone.copied\"}"
                            "]}]}"));
    zoneChecks(server);
}

void
newZoneChecks(AuthSrv& server) {
    EXPECT_TRUE(server.getMemoryDataSrc(RRClass::IN()));
    EXPECT_EQ(Zone::SUCCESS, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone->
              find(Name("ns.test1.example"), RRType::A()).code);
    // now test1.example should have ns/AAAA
    EXPECT_EQ(Zone::SUCCESS, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone->
              find(Name("ns.test1.example"), RRType::AAAA()).code);

    // test2.example shouldn't change
    EXPECT_EQ(Zone::SUCCESS, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone->
              find(Name("ns.test2.example"), RRType::A()).code);
    EXPECT_EQ(Zone::NXRRSET, server.getMemoryDataSrc(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone->
              find(Name("ns.test2.example"), RRType::AAAA()).code);
}

TEST_F(AuthConmmandTest, loadZone) {
    configureZones(server);

    ASSERT_EQ(0, system(INSTALL_PROG " " TEST_DATA_DIR
                        "/test1-new.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    ASSERT_EQ(0, system(INSTALL_PROG " " TEST_DATA_DIR
                        "/test2-new.zone.in "
                        TEST_DATA_BUILDDIR "/test2.zone.copied"));

    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\"}"));
    checkAnswer(0);
    newZoneChecks(server);
}

TEST_F(AuthConmmandTest, loadBrokenZone) {
    configureZones(server);

    ASSERT_EQ(0, system(INSTALL_PROG " " TEST_DATA_DIR
                        "/test1-broken.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\"}"));
    checkAnswer(1);
    zoneChecks(server);     // zone shouldn't be replaced
}

TEST_F(AuthConmmandTest, loadUnreadableZone) {
    configureZones(server);

    // install the zone file as unreadable
    ASSERT_EQ(0, system(INSTALL_PROG " -m 000 " TEST_DATA_DIR
                        "/test1.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\"}"));
    checkAnswer(1);
    zoneChecks(server);     // zone shouldn't be replaced
}

TEST_F(AuthConmmandTest, loadZoneWithoutDataSrc) {
    // try to execute load command without configuring the zone beforehand.
    // it should fail.
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\"}"));
    checkAnswer(1);
}

TEST_F(AuthConmmandTest, loadSqlite3DataSrc) {
    // For sqlite3 data source we don't have to do anything (the data source
    // (re)loads itself automatically)
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\","
                                       " \"datasrc\": \"sqlite3\"}"));
    checkAnswer(0);
}

TEST_F(AuthConmmandTest, loadZoneInvalidParams) {
    configureZones(server);

    // null arg
    result = execAuthServerCommand(server, "loadzone", ElementPtr());
    checkAnswer(1);

    // zone class is bogus
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\","
                                       " \"class\": \"no_such_class\"}"));
    checkAnswer(1);

    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\","
                                       " \"class\": 1}"));
    checkAnswer(1);

    // unsupported zone class
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\","
                                       " \"class\": \"CH\"}"));
    checkAnswer(1);

    // unsupported data source class
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\","
                                       " \"datasrc\": \"not supported\"}"));
    checkAnswer(1);

    // data source is bogus
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"test1.example\","
                                       " \"datasrc\": 0}"));
    checkAnswer(1);

    // origin is missing
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON("{}"));
    checkAnswer(1);

    // zone doesn't exist in the data source
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON("{\"origin\": \"xx\"}"));
    checkAnswer(1);

    // origin is bogus
    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON(
                                       "{\"origin\": \"...\"}"));
    checkAnswer(1);

    result = execAuthServerCommand(server, "loadzone",
                                   Element::fromJSON("{\"origin\": 10}"));
    checkAnswer(1);
}
}
