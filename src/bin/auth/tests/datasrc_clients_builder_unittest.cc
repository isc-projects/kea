// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/name.h>
#include <dns/rrclass.h>

#include <cc/data.h>

#include <datasrc/client.h>

#include <auth/datasrc_clients_mgr.h>
#include <auth/datasrc_config.h>

#include <testutils/dnsmessage_test.h>

#include "test_datasrc_clients_mgr.h"
#include "datasrc_util.h"

#include <gtest/gtest.h>

#include <boost/function.hpp>

#include <cstdlib>
#include <string>
#include <sstream>

using isc::data::ConstElementPtr;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::auth::datasrc_clientmgr_internal;
using namespace isc::auth::unittest;
using namespace isc::testutils;

namespace {
class DataSrcClientsBuilderTest : public ::testing::Test {
protected:
    DataSrcClientsBuilderTest() :
        clients_map(new std::map<RRClass,
                    boost::shared_ptr<ConfigurableClientList> >),
        builder(&command_queue, &cond, &queue_mutex, &clients_map, &map_mutex),
        cond(command_queue, delayed_command_queue), rrclass(RRClass::IN()),
        shutdown_cmd(SHUTDOWN, ConstElementPtr()),
        noop_cmd(NOOP, ConstElementPtr())
    {}

    void configureZones();      // used for loadzone related tests

    ClientListMapPtr clients_map; // configured clients
    std::list<Command> command_queue; // test command queue
    std::list<Command> delayed_command_queue; // commands available after wait
    TestDataSrcClientsBuilder builder;
    TestCondVar cond;
    TestMutex queue_mutex;
    TestMutex map_mutex;
    const RRClass rrclass;
    const Command shutdown_cmd;
    const Command noop_cmd;
};

TEST_F(DataSrcClientsBuilderTest, runSingleCommand) {
    // A simplest case, just to check the basic behavior.
    command_queue.push_back(shutdown_cmd);
    builder.run();
    EXPECT_TRUE(command_queue.empty());
    EXPECT_EQ(0, cond.wait_count); // no wait because command queue is not empty
    EXPECT_EQ(1, queue_mutex.lock_count);
    EXPECT_EQ(1, queue_mutex.unlock_count);
}

TEST_F(DataSrcClientsBuilderTest, runMultiCommands) {
    // Two NOOP commands followed by SHUTDOWN.  We should see two doNoop()
    // calls.
    command_queue.push_back(noop_cmd);
    command_queue.push_back(noop_cmd);
    command_queue.push_back(shutdown_cmd);
    builder.run();
    EXPECT_TRUE(command_queue.empty());
    EXPECT_EQ(1, queue_mutex.lock_count);
    EXPECT_EQ(1, queue_mutex.unlock_count);
    EXPECT_EQ(2, queue_mutex.noop_count);
}

TEST_F(DataSrcClientsBuilderTest, exception) {
    // Let the noop command handler throw exceptions and see if we can see
    // them.  Right now, we simply abort to prevent the system from running
    // with half-broken state.  Eventually we should introduce a better
    // error handling.
    command_queue.push_back(noop_cmd);
    queue_mutex.throw_from_noop = TestMutex::EXCLASS;
    EXPECT_DEATH_IF_SUPPORTED({builder.run();}, "");

    command_queue.push_back(noop_cmd);
    queue_mutex.throw_from_noop = TestMutex::INTEGER;
    EXPECT_DEATH_IF_SUPPORTED({builder.run();}, "");
}

TEST_F(DataSrcClientsBuilderTest, condWait) {
    // command_queue is originally empty, so it will require waiting on
    // condvar.  specialized wait() will make the delayed command available.
    delayed_command_queue.push_back(shutdown_cmd);
    builder.run();

    // There should be one call to wait()
    EXPECT_EQ(1, cond.wait_count);
    // wait() effectively involves one more set of lock/unlock, so we have
    // two in total
    EXPECT_EQ(2, queue_mutex.lock_count);
    EXPECT_EQ(2, queue_mutex.unlock_count);
}

TEST_F(DataSrcClientsBuilderTest, reconfigure) {
    // Full testing of different configurations is not here, but we
    // do check a few cases of correct and erroneous input, to verify
    // the error handling

    // A command structure we'll modify to send different commands
    Command reconfig_cmd(RECONFIGURE, ConstElementPtr());

    // Initially, no clients should be there
    EXPECT_TRUE(clients_map->empty());

    // A config that doesn't do much except be accepted
    ConstElementPtr good_config = isc::data::Element::fromJSON(
        "{"
        "\"IN\": [{"
        "   \"type\": \"MasterFiles\","
        "   \"params\": {},"
        "   \"cache-enable\": true"
        "}]"
        "}"
    );

    // A configuration that is 'correct' in the top-level, but contains
    // bad data for the type it specifies
    ConstElementPtr bad_config = isc::data::Element::fromJSON(
        "{"
        "\"IN\": [{"
        "   \"type\": \"MasterFiles\","
        "   \"params\": { \"foo\": [ 1, 2, 3, 4  ]},"
        "   \"cache-enable\": true"
        "}]"
        "}"
    );

    reconfig_cmd.second = good_config;
    EXPECT_TRUE(builder.handleCommand(reconfig_cmd));
    EXPECT_EQ(1, clients_map->size());
    EXPECT_EQ(1, map_mutex.lock_count);

    // Store the nonempty clients map we now have
    ClientListMapPtr working_config_clients(clients_map);

    // If a 'bad' command argument got here, the config validation should
    // have failed already, but still, the handler should return true,
    // and the clients_map should not be updated.
    reconfig_cmd.second = isc::data::Element::create("{ \"foo\": \"bar\" }");
    EXPECT_TRUE(builder.handleCommand(reconfig_cmd));
    EXPECT_EQ(working_config_clients, clients_map);
    // Building failed, so map mutex should not have been locked again
    EXPECT_EQ(1, map_mutex.lock_count);

    // The same for a configuration that has bad data for the type it
    // specifies
    reconfig_cmd.second = bad_config;
    builder.handleCommand(reconfig_cmd);
    EXPECT_TRUE(builder.handleCommand(reconfig_cmd));
    EXPECT_EQ(working_config_clients, clients_map);
    // Building failed, so map mutex should not have been locked again
    EXPECT_EQ(1, map_mutex.lock_count);

    // The same goes for an empty parameter (it should at least be
    // an empty map)
    reconfig_cmd.second = ConstElementPtr();
    EXPECT_TRUE(builder.handleCommand(reconfig_cmd));
    EXPECT_EQ(working_config_clients, clients_map);
    EXPECT_EQ(1, map_mutex.lock_count);

    // Reconfigure again with the same good clients, the result should
    // be a different map than the original, but not an empty one.
    reconfig_cmd.second = good_config;
    EXPECT_TRUE(builder.handleCommand(reconfig_cmd));
    EXPECT_NE(working_config_clients, clients_map);
    EXPECT_EQ(1, clients_map->size());
    EXPECT_EQ(2, map_mutex.lock_count);

    // And finally, try an empty config to disable all datasource clients
    reconfig_cmd.second = isc::data::Element::createMap();
    EXPECT_TRUE(builder.handleCommand(reconfig_cmd));
    EXPECT_EQ(0, clients_map->size());
    EXPECT_EQ(3, map_mutex.lock_count);

    // Also check if it has been cleanly unlocked every time
    EXPECT_EQ(3, map_mutex.unlock_count);
}

TEST_F(DataSrcClientsBuilderTest, shutdown) {
    EXPECT_FALSE(builder.handleCommand(shutdown_cmd));
}

TEST_F(DataSrcClientsBuilderTest, badCommand) {
    // out-of-range command ID
    EXPECT_THROW(builder.handleCommand(Command(NUM_COMMANDS,
                                               ConstElementPtr())),
                 isc::Unexpected);
}

// A helper function commonly used for the "loadzone" command tests.
// It configures the given data source client lists with a memory data source
// containing two zones, and checks the zones are correctly loaded.
void
zoneChecks(ClientListMapPtr clients_map, RRClass rrclass) {
    EXPECT_EQ(ZoneFinder::SUCCESS, clients_map->find(rrclass)->second->
              find(Name("ns.test1.example")).finder_->
              find(Name("ns.test1.example"), RRType::A())->code);
    EXPECT_EQ(ZoneFinder::NXRRSET, clients_map->find(rrclass)->second->
              find(Name("ns.test1.example")).finder_->
              find(Name("ns.test1.example"), RRType::AAAA())->code);
    EXPECT_EQ(ZoneFinder::SUCCESS, clients_map->find(rrclass)->second->
              find(Name("ns.test2.example")).finder_->
              find(Name("ns.test2.example"), RRType::A())->code);
    EXPECT_EQ(ZoneFinder::NXRRSET, clients_map->find(rrclass)->second->
              find(Name("ns.test2.example")).finder_->
              find(Name("ns.test2.example"), RRType::AAAA())->code);
}

// Another helper that checks after completing loadzone command.
void
newZoneChecks(ClientListMapPtr clients_map, RRClass rrclass) {
    EXPECT_EQ(ZoneFinder::SUCCESS, clients_map->find(rrclass)->second->
              find(Name("ns.test1.example")).finder_->
              find(Name("ns.test1.example"), RRType::A())->code);
    // now test1.example should have ns/AAAA
    EXPECT_EQ(ZoneFinder::SUCCESS, clients_map->find(rrclass)->second->
              find(Name("ns.test1.example")).finder_->
              find(Name("ns.test1.example"), RRType::AAAA())->code);

    // test2.example shouldn't change
    EXPECT_EQ(ZoneFinder::SUCCESS, clients_map->find(rrclass)->second->
              find(Name("ns.test2.example")).finder_->
              find(Name("ns.test2.example"), RRType::A())->code);
    EXPECT_EQ(ZoneFinder::NXRRSET,
              clients_map->find(rrclass)->second->
              find(Name("ns.test2.example")).finder_->
              find(Name("ns.test2.example"), RRType::AAAA())->code);
}

void
DataSrcClientsBuilderTest::configureZones() {
    ASSERT_EQ(0, std::system(INSTALL_PROG " -c " TEST_DATA_DIR "/test1.zone.in "
                             TEST_DATA_BUILDDIR "/test1.zone.copied"));
    ASSERT_EQ(0, std::system(INSTALL_PROG " -c " TEST_DATA_DIR "/test2.zone.in "
                             TEST_DATA_BUILDDIR "/test2.zone.copied"));

    const ConstElementPtr config(
        Element::fromJSON(
            "{"
            "\"IN\": [{"
            "   \"type\": \"MasterFiles\","
            "   \"params\": {"
            "       \"test1.example\": \"" +
            std::string(TEST_DATA_BUILDDIR "/test1.zone.copied") + "\","
            "       \"test2.example\": \"" +
            std::string(TEST_DATA_BUILDDIR "/test2.zone.copied") + "\""
            "   },"
            "   \"cache-enable\": true"
            "}]}"));
    clients_map = configureDataSource(config);
    zoneChecks(clients_map, rrclass);
}

TEST_F(DataSrcClientsBuilderTest, loadzone) {
    // pre test condition checks
    EXPECT_EQ(0, map_mutex.lock_count);
    EXPECT_EQ(0, map_mutex.unlock_count);

    configureZones();

    EXPECT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR
                        "/test1-new.zone.in "
                        TEST_DATA_BUILDDIR "/test1.zone.copied"));
    EXPECT_EQ(0, system(INSTALL_PROG " -c " TEST_DATA_DIR
                        "/test2-new.zone.in "
                        TEST_DATA_BUILDDIR "/test2.zone.copied"));

    const Command loadzone_cmd(LOADZONE, isc::data::Element::fromJSON(
                                   "{\"class\": \"IN\","
                                   " \"origin\": \"test1.example\"}"));
    EXPECT_TRUE(builder.handleCommand(loadzone_cmd));
    EXPECT_EQ(1, map_mutex.lock_count); // we should have acquired the lock
    EXPECT_EQ(1, map_mutex.unlock_count); // and released it.

    newZoneChecks(clients_map, rrclass);
}

TEST_F(DataSrcClientsBuilderTest,
#ifdef USE_STATIC_LINK
       DISABLED_loadZoneSQLite3
#else
       loadZoneSQLite3
#endif
    )
{
    // Prepare the database first
    const std::string test_db = TEST_DATA_BUILDDIR "/auth_test.sqlite3.copied";
    std::stringstream ss("example.org. 3600 IN SOA . . 0 0 0 0 0\n");
    createSQLite3DB(rrclass, Name("example.org"), test_db.c_str(), ss);
    // This describes the data source in the configuration
    const ConstElementPtr config(Element::fromJSON("{"
        "\"IN\": [{"
        "    \"type\": \"sqlite3\","
        "    \"params\": {\"database_file\": \"" + test_db + "\"},"
        "    \"cache-enable\": true,"
        "    \"cache-zones\": [\"example.org\"]"
        "}]}"));
    clients_map = configureDataSource(config);

    // Check that the A record at www.example.org does not exist
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              clients_map->find(rrclass)->second->
              find(Name("example.org")).finder_->
              find(Name("www.example.org"), RRType::A())->code);

    // Add the record to the underlying sqlite database, by loading
    // it as a separate datasource, and updating it
    ConstElementPtr sql_cfg = Element::fromJSON("{ \"type\": \"sqlite3\","
                                                "\"database_file\": \""
                                                + test_db + "\"}");
    DataSourceClientContainer sql_ds("sqlite3", sql_cfg);
    ZoneUpdaterPtr sql_updater =
        sql_ds.getInstance().getUpdater(Name("example.org"), false);
    sql_updater->addRRset(
        *textToRRset("www.example.org. 60 IN A 192.0.2.1"));
    sql_updater->commit();

    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              clients_map->find(rrclass)->second->
              find(Name("example.org")).finder_->
              find(Name("www.example.org"), RRType::A())->code);

    // Now send the command to reload it
    const Command loadzone_cmd(LOADZONE, isc::data::Element::fromJSON(
                                   "{\"class\": \"IN\","
                                   " \"origin\": \"example.org\"}"));
    EXPECT_TRUE(builder.handleCommand(loadzone_cmd));
    // And now it should be present too.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              clients_map->find(rrclass)->second->
              find(Name("example.org")).finder_->
              find(Name("www.example.org"), RRType::A())->code);

    // An error case: the zone has no configuration. (note .com here)
    const Command nozone_cmd(LOADZONE, isc::data::Element::fromJSON(
                                 "{\"class\": \"IN\","
                                 " \"origin\": \"example.com\"}"));
    EXPECT_THROW(builder.handleCommand(nozone_cmd),
                 TestDataSrcClientsBuilder::InternalCommandError);
    // The previous zone is not hurt in any way
    EXPECT_EQ(ZoneFinder::SUCCESS, clients_map->find(rrclass)->second->
              find(Name("example.org")).finder_->
              find(Name("example.org"), RRType::SOA())->code);
}

TEST_F(DataSrcClientsBuilderTest, loadBrokenZone) {
    configureZones();

    ASSERT_EQ(0, std::system(INSTALL_PROG " -c " TEST_DATA_DIR
                             "/test1-broken.zone.in "
                             TEST_DATA_BUILDDIR "/test1.zone.copied"));
    // there's an error in the new zone file.  reload will be rejected.
    const Command loadzone_cmd(LOADZONE, Element::fromJSON(
                                   "{\"class\": \"IN\","
                                   " \"origin\": \"test1.example\"}"));
    EXPECT_THROW(builder.handleCommand(loadzone_cmd),
                 TestDataSrcClientsBuilder::InternalCommandError);
    zoneChecks(clients_map, rrclass);     // zone shouldn't be replaced
}

TEST_F(DataSrcClientsBuilderTest, loadUnreadableZone) {
    configureZones();

    // install the zone file as unreadable
    ASSERT_EQ(0, std::system(INSTALL_PROG " -c -m 000 " TEST_DATA_DIR
                             "/test1.zone.in "
                             TEST_DATA_BUILDDIR "/test1.zone.copied"));
    const Command loadzone_cmd(LOADZONE, Element::fromJSON(
                                   "{\"class\": \"IN\","
                                   " \"origin\": \"test1.example\"}"));
    EXPECT_THROW(builder.handleCommand(loadzone_cmd),
                 TestDataSrcClientsBuilder::InternalCommandError);
    zoneChecks(clients_map, rrclass);     // zone shouldn't be replaced
}

TEST_F(DataSrcClientsBuilderTest, loadZoneInvalidParams) {
    configureZones();

    // null arg: this causes assertion failure
    EXPECT_DEATH_IF_SUPPORTED({
            builder.handleCommand(Command(LOADZONE, ElementPtr()));
        }, "");

    // zone class is bogus (note that this shouldn't happen except in tests)
    EXPECT_THROW(builder.handleCommand(
                     Command(LOADZONE,
                             Element::fromJSON(
                                 "{\"origin\": \"test1.example\","
                                 " \"class\": \"no_such_class\"}"))),
                 InvalidRRClass);

    // not a string
    EXPECT_THROW(builder.handleCommand(
                     Command(LOADZONE,
                             Element::fromJSON(
                                 "{\"origin\": \"test1.example\","
                                 " \"class\": 1}"))),
                 isc::data::TypeError);

    // class or origin is missing: result in assertion failure
    EXPECT_DEATH_IF_SUPPORTED({
            builder.handleCommand(
                Command(LOADZONE,
                        Element::fromJSON("{\"origin\": \"test1.example\"}")));
        }, "");
    EXPECT_DEATH_IF_SUPPORTED({
            builder.handleCommand(Command(LOADZONE,
                                          Element::fromJSON(
                                              "{\"class\": \"IN\"}")));
        }, "");

    // zone doesn't exist in the data source
    EXPECT_THROW(
        builder.handleCommand(
            Command(LOADZONE,
                    Element::fromJSON(
                        "{\"class\": \"IN\", \"origin\": \"xx\"}"))),
        TestDataSrcClientsBuilder::InternalCommandError);

    // origin is bogus
    EXPECT_THROW(builder.handleCommand(
                     Command(LOADZONE,
                             Element::fromJSON(
                                 "{\"class\": \"IN\", \"origin\": \"...\"}"))),
                 EmptyLabel);
    EXPECT_THROW(builder.handleCommand(
                     Command(LOADZONE,
                             Element::fromJSON(
                                 "{\"origin\": 10, \"class\": 1}"))),
                 isc::data::TypeError);
}

} // unnamed namespace
