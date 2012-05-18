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

#include "datasrc_util.h"

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/command.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cc/data.h>

#include <config/ccsession.h>

#include <datasrc/memory_datasrc.h>

#include <asiolink/asiolink.h>

#include <util/unittests/mock_socketsession.h>
#include <testutils/mockups.h>

#include <cassert>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <sys/types.h>
#include <unistd.h>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::config;
using namespace isc::util::unittests;
using namespace isc::testutils;
using namespace isc::auth::unittest;

namespace {

class AuthCommandTest : public ::testing::Test {
protected:
    AuthCommandTest() :
        server_(false, xfrout_, ddns_forwarder_),
        rcode_(-1),
        expect_rcode_(0),
        itimer_(server_.getIOService())
    {
        server_.setStatisticsSession(&statistics_session_);
    }
    void checkAnswer(const int expected_code) {
        parseAnswer(rcode_, result_);
        EXPECT_EQ(expected_code, rcode_);
    }
    MockSession statistics_session_;
    MockXfroutClient xfrout_;
    MockSocketSessionForwarder ddns_forwarder_;
    AuthSrv server_;
    ConstElementPtr result_;
    // The shutdown command parameter
    ConstElementPtr param_;
    int rcode_, expect_rcode_;
    isc::asiolink::IntervalTimer itimer_;
public:
    void stopServer();          // need to be public for boost::bind
    void dontStopServer();          // need to be public for boost::bind
};

TEST_F(AuthCommandTest, unknownCommand) {
    result_ = execAuthServerCommand(server_, "no_such_command",
                                    ConstElementPtr());
    parseAnswer(rcode_, result_);
    EXPECT_EQ(1, rcode_);
}

TEST_F(AuthCommandTest, DISABLED_unexpectedException) {
    // execAuthServerCommand() won't catch standard exceptions.
    // Skip this test for now: ModuleCCSession doesn't seem to validate
    // commands.
    EXPECT_THROW(execAuthServerCommand(server_, "_throw_exception",
                                       ConstElementPtr()),
                 runtime_error);
}

TEST_F(AuthCommandTest, sendStatistics) {
    result_ = execAuthServerCommand(server_, "sendstats", ConstElementPtr());
    // Just check some message has been sent.  Detailed tests specific to
    // statistics are done in its own tests.
    EXPECT_EQ("Stats", statistics_session_.getMessageDest());
    checkAnswer(0);
}

void
AuthCommandTest::stopServer() {
    result_ = execAuthServerCommand(server_, "shutdown", param_);
    parseAnswer(rcode_, result_);
    assert(rcode_ == 0); // make sure the test stops when something is wrong
}

TEST_F(AuthCommandTest, shutdown) {
    // Param defaults to empty/null pointer on creation
    itimer_.setup(boost::bind(&AuthCommandTest::stopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

TEST_F(AuthCommandTest, shutdownCorrectPID) {
    // Put the pid parameter there
    const pid_t pid(getpid());
    ElementPtr param(new isc::data::MapElement());
    param->set("pid", ConstElementPtr(new isc::data::IntElement(pid)));
    param_ = param;
    // With the correct PID, it should act exactly the same as in case
    // of no parameter
    itimer_.setup(boost::bind(&AuthCommandTest::stopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

// This is like stopServer, but the server should not stop after the
// command, it should be running
void
AuthCommandTest::dontStopServer() {
    result_ = execAuthServerCommand(server_, "shutdown", param_);
    parseAnswer(rcode_, result_);
    EXPECT_EQ(expect_rcode_, rcode_);
    rcode_ = -1;
    // We run the stopServer now, to really stop the server.
    // If it had stopped already, it won't be run and the rcode -1 will
    // be left here.
    param_ = ConstElementPtr();
    itimer_.cancel();
    itimer_.setup(boost::bind(&AuthCommandTest::stopServer, this), 1);
}

// If we provide something not an int, the PID is not really specified, so
// act as if nothing came.
TEST_F(AuthCommandTest, shutdownNotInt) {
    // Put the pid parameter there
    ElementPtr param(new isc::data::MapElement());
    param->set("pid", ConstElementPtr(new isc::data::StringElement("pid")));
    param_ = param;
    expect_rcode_ = 1;
    // It should reject to stop if the PID is not an int.
    itimer_.setup(boost::bind(&AuthCommandTest::dontStopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

TEST_F(AuthCommandTest, shutdownIncorrectPID) {
    // The PID = 0 should be taken by init, so we are not init and the
    // PID should be different
    param_ = Element::fromJSON("{\"pid\": 0}");
    itimer_.setup(boost::bind(&AuthCommandTest::dontStopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

// A helper function commonly used for the "loadzone" command tests.
// It configures the server with a memory data source containing two
// zones, and checks the zones are correctly loaded.
void
zoneChecks(AuthSrv& server) {
    EXPECT_TRUE(server.getInMemoryClient(RRClass::IN()));
    EXPECT_EQ(ZoneFinder::SUCCESS, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone_finder->
              find(Name("ns.test1.example"), RRType::A())->code);
    EXPECT_EQ(ZoneFinder::NXRRSET, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone_finder->
              find(Name("ns.test1.example"), RRType::AAAA())->code);
    EXPECT_EQ(ZoneFinder::SUCCESS, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone_finder->
              find(Name("ns.test2.example"), RRType::A())->code);
    EXPECT_EQ(ZoneFinder::NXRRSET, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone_finder->
              find(Name("ns.test2.example"), RRType::AAAA())->code);
}

void
configureZones(AuthSrv& server) {
    ASSERT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR "/test1.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    ASSERT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR "/test2.zone.in "
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
    EXPECT_TRUE(server.getInMemoryClient(RRClass::IN()));
    EXPECT_EQ(ZoneFinder::SUCCESS, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone_finder->
              find(Name("ns.test1.example"), RRType::A())->code);
    // now test1.example should have ns/AAAA
    EXPECT_EQ(ZoneFinder::SUCCESS, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test1.example")).zone_finder->
              find(Name("ns.test1.example"), RRType::AAAA())->code);

    // test2.example shouldn't change
    EXPECT_EQ(ZoneFinder::SUCCESS, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone_finder->
              find(Name("ns.test2.example"), RRType::A())->code);
    EXPECT_EQ(ZoneFinder::NXRRSET, server.getInMemoryClient(RRClass::IN())->
              findZone(Name("ns.test2.example")).zone_finder->
              find(Name("ns.test2.example"), RRType::AAAA())->code);
}

TEST_F(AuthCommandTest, loadZone) {
    configureZones(server_);

    ASSERT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR
                        "/test1-new.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    ASSERT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR
                        "/test2-new.zone.in "
                        TEST_DATA_BUILDDIR "/test2.zone.copied"));

    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\"}"));
    checkAnswer(0);
    newZoneChecks(server_);
}

// This test uses dynamic load of a data source module, and won't work when
// statically linked.
TEST_F(AuthCommandTest,
#ifdef USE_STATIC_LINK
       DISABLED_loadZoneSQLite3
#else
       loadZoneSQLite3
#endif
    )
{
    const char* const SPEC_FILE = AUTH_OBJ_DIR "/auth.spec";

    // Prepare the database first
    const string test_db = TEST_DATA_BUILDDIR "/auth_test.sqlite3.copied";
    const string bad_db = TEST_DATA_BUILDDIR "/does-not-exist.sqlite3";
    stringstream ss("example.org. 3600 IN SOA . . 0 0 0 0 0\n");
    createSQLite3DB(RRClass::IN(), Name("example.org"), test_db.c_str(), ss);

    // Then store a config of the zone to the auth server
    // This omits many config options of the auth server, but these are
    // not read now.
    isc::testutils::MockSession session;
    // The session should not take care of anything or start anything, we
    // need it only to hold the config we're going to put into it.
    ModuleCCSession module_session(SPEC_FILE, session, NULL, NULL, false,
                                  false);
    // This describes the data source in the configuration
    const ElementPtr
        map(Element::fromJSON("{\"datasources\": ["
                              "  {"
                              "    \"type\": \"memory\","
                              "    \"zones\": ["
                              "      {"
                              "        \"origin\": \"example.org\","
                              "        \"file\": \"" + test_db + "\","
                              "        \"filetype\": \"sqlite3\""
                              "      }"
                              "    ]"
                              "  }"
                              "]}"));
    module_session.setLocalConfig(map);
    server_.setConfigSession(&module_session);

    // The loadzone command needs the zone to be already loaded, because
    // it is used for reloading only
    AuthSrv::InMemoryClientPtr dsrc(new InMemoryClient());
    dsrc->addZone(ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("example.org"))));
    server_.setInMemoryClient(RRClass::IN(), dsrc);

    // Now send the command to reload it
    result_ = execAuthServerCommand(server_, "loadzone",
        Element::fromJSON("{\"origin\": \"example.org\"}"));
    checkAnswer(0);

    // Get the zone and look if there are data in it (the original one was
    // empty)
    ASSERT_TRUE(server_.getInMemoryClient(RRClass::IN()));
    EXPECT_EQ(ZoneFinder::SUCCESS, server_.getInMemoryClient(RRClass::IN())->
              findZone(Name("example.org")).zone_finder->
              find(Name("example.org"), RRType::SOA())->code);

    // Some error cases. First, the zone has no configuration.
    dsrc->addZone(ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("example.com"))));
    result_ = execAuthServerCommand(server_, "loadzone",
        Element::fromJSON("{\"origin\": \"example.com\"}"));
    checkAnswer(1);

    // The previous zone is not hurt in any way
    EXPECT_EQ(ZoneFinder::SUCCESS, server_.getInMemoryClient(RRClass::IN())->
              findZone(Name("example.org")).zone_finder->
              find(Name("example.org"), RRType::SOA())->code);

    module_session.setLocalConfig(Element::fromJSON("{\"datasources\": []}"));
    result_ = execAuthServerCommand(server_, "loadzone",
        Element::fromJSON("{\"origin\": \"example.org\"}"));
    checkAnswer(1);

    // The previous zone is not hurt in any way
    EXPECT_EQ(ZoneFinder::SUCCESS, server_.getInMemoryClient(RRClass::IN())->
              findZone(Name("example.org")).zone_finder->
              find(Name("example.org"), RRType::SOA())->code);
    // Configure an unreadable zone. Should fail, but leave the original zone
    // data there
    const ElementPtr
        mapBad(Element::fromJSON("{\"datasources\": ["
                                 "  {"
                                 "    \"type\": \"memory\","
                                 "    \"zones\": ["
                                 "      {"
                                 "        \"origin\": \"example.org\","
                                 "        \"file\": \"" + bad_db + "\","
                                 "        \"filetype\": \"sqlite3\""
                                 "      }"
                                 "    ]"
                                 "  }"
                                 "]}"));
    module_session.setLocalConfig(mapBad);
    result_ = execAuthServerCommand(server_, "loadzone",
        Element::fromJSON("{\"origin\": \"example.com\"}"));
    checkAnswer(1);
    // The previous zone is not hurt in any way
    EXPECT_EQ(ZoneFinder::SUCCESS, server_.getInMemoryClient(RRClass::IN())->
              findZone(Name("example.org")).zone_finder->
              find(Name("example.org"), RRType::SOA())->code);

    // Broken configuration (not valid against the spec)
    const ElementPtr
        broken(Element::fromJSON("{\"datasources\": ["
                                 "  {"
                                 "    \"type\": \"memory\","
                                 "    \"zones\": [[]]"
                                 "  }"
                                 "]}"));
    module_session.setLocalConfig(broken);
    checkAnswer(1);
    // The previous zone is not hurt in any way
    EXPECT_EQ(ZoneFinder::SUCCESS, server_.getInMemoryClient(RRClass::IN())->
              findZone(Name("example.org")).zone_finder->
              find(Name("example.org"), RRType::SOA())->code);
}

TEST_F(AuthCommandTest, loadBrokenZone) {
    configureZones(server_);

    ASSERT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR
                        "/test1-broken.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\"}"));
    checkAnswer(1);
    zoneChecks(server_);     // zone shouldn't be replaced
}

TEST_F(AuthCommandTest, loadUnreadableZone) {
    configureZones(server_);

    // install the zone file as unreadable
    ASSERT_EQ(0, system(INSTALL_PROG " -c -m 000 " TEST_DATA_DIR
                        "/test1.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\"}"));
    checkAnswer(1);
    zoneChecks(server_);     // zone shouldn't be replaced
}

TEST_F(AuthCommandTest, loadZoneWithoutDataSrc) {
    // try to execute load command without configuring the zone beforehand.
    // it should fail.
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\"}"));
    checkAnswer(1);
}

TEST_F(AuthCommandTest, loadSqlite3DataSrc) {
    // For sqlite3 data source we don't have to do anything (the data source
    // (re)loads itself automatically)
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\","
                                        " \"datasrc\": \"sqlite3\"}"));
    checkAnswer(0);
}

TEST_F(AuthCommandTest, loadZoneInvalidParams) {
    configureZones(server_);

    // null arg
    result_ = execAuthServerCommand(server_, "loadzone", ElementPtr());
    checkAnswer(1);

    // zone class is bogus
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\","
                                        " \"class\": \"no_such_class\"}"));
    checkAnswer(1);

    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\","
                                        " \"class\": 1}"));
    checkAnswer(1);

    // unsupported zone class
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\","
                                        " \"class\": \"CH\"}"));
    checkAnswer(1);

    // unsupported data source class
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\","
                                        " \"datasrc\": \"not supported\"}"));
    checkAnswer(1);

    // data source is bogus
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"test1.example\","
                                        " \"datasrc\": 0}"));
    checkAnswer(1);

    // origin is missing
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON("{}"));
    checkAnswer(1);

    // zone doesn't exist in the data source
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON("{\"origin\": \"xx\"}"));
    checkAnswer(1);

    // origin is bogus
    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON(
                                        "{\"origin\": \"...\"}"));
    checkAnswer(1);

    result_ = execAuthServerCommand(server_, "loadzone",
                                    Element::fromJSON("{\"origin\": 10}"));
    checkAnswer(1);
}
}
