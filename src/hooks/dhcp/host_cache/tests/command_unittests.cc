// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the command entry points.

#include <config.h>

#include <host_cache.h>
#include <host_cache_parsers.h>
#include <hooks/hooks_manager.h>
#include <dhcpsrv/cfgmgr.h>
#include <testutils/env_var_wrapper.h>
#include <testutils/multi_threading_utils.h>
#include <gtest/gtest.h>
#include <fstream>
#include <functional>
#include <iostream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::host_cache;
using namespace isc::test;
using namespace isc::util;
using namespace std;
namespace ph = std::placeholders;

namespace {

/// @brief Test fixture for testing commands for the host-cache library
class CommandTest : public ::testing::Test {
public:
    /// @brief Constructor
    CommandTest() {
        // Save the pre-test data dir and set it to the test directory.
        CfgMgr::instance().clear();
        original_datadir_ = CfgMgr::instance().getDataDir();
        CfgMgr::instance().getDataDir(true, TEST_DATA_BUILDDIR);

        hcptr_.reset(new HostCache());
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor
    virtual ~CommandTest() {
        ::remove("dump.json");
        ::remove("source.json");

        // Revert to original data directory.
        CfgMgr::instance().getDataDir(true, original_datadir_);
    }

    /// @brief Creates a sample IPv4 host
    HostPtr createHost4() {
        HostPtr h(new Host("01:02:03:04:05:06", "hw-address",
                           SubnetID(4), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.100"),
                           "somehost.example.org",
                           std::string(), std::string(),
                           IOAddress("192.0.0.2"),
                           "server-hostname.example.org",
                           "bootfile.efi"));
        return (h);
    }

    /// @brief Creates another sample IPv4 host
    HostPtr createHost4bis() {
        HostPtr h(new Host("07:08:09:0a:0b:0c", "hw-address",
                           SubnetID(4), SubnetID(SUBNET_ID_UNUSED),
                           IOAddress("192.0.2.200"),
                           "otherhost.example.org",
                           std::string(), std::string(),
                           IOAddress("192.0.0.2"),
                           "server-hostname.example.org",
                           "bootfile.efi"));
        return (h);
    }

    /// @brief Creates a sample IPv6 host
    HostPtr createHost6() {
        HostPtr host(new Host("01:02:03:04:05:06", "hw-address",
                              SubnetID(SUBNET_ID_UNUSED), SubnetID(6),
                              IOAddress("0.0.0.0")));
        // Add 2 reservations: 1 for NA, 1 for PD.
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8::cafe:babe")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:dead:beef::"), 64));
        return (host);
    };

    /// @brief Creates another sample IPv6 host
    HostPtr createHost6bis() {
        HostPtr host(new Host("07:08:09:0a:0b:0c", "hw-address",
                              SubnetID(SUBNET_ID_UNUSED), SubnetID(6),
                              IOAddress("0.0.0.0")));
        // Add a reservation for NA.
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8::babe:cafe")));
        return (host);
    };

    string host4_txt = "{\n"
        "\"hw-address\": \"01:02:03:04:05:06\",\n"
        "\"subnet-id4\": 4,\n"
        "\"subnet-id6\": 4294967295,\n" // SUBNET_ID_UNUSED
        "\"ip-address\": \"192.0.2.100\",\n"
        "\"hostname\": \"somehost.example.org\",\n"
        "\"client-classes4\": [ ],\n"
        "\"client-classes6\": [ ],\n"
        "\"option-data4\": [ ],\n"
        "\"option-data6\": [ ],\n"
        "\"next-server\": \"192.0.0.2\",\n"
        "\"server-hostname\": \"server-hostname.example.org\",\n"
        "\"boot-file-name\": \"bootfile.efi\",\n"
        "\"host-id\": 0 }\n";

    string host6_txt = "{\n"
        "\"hw-address\": \"01:02:03:04:05:06\",\n"
        "\"subnet-id4\": 4294967295,\n" // SUBNET_ID_UNUSED
        "\"subnet-id6\": 6,\n"
        "\"ip-addresses\": [ \"2001:db8::cafe:babe\" ],\n"
        "\"prefixes\": [ \"2001:db8:dead:beef::/64\" ],\n"
        "\"hostname\": \"\",\n"
        "\"client-classes4\": [ ],\n"
        "\"client-classes6\": [ ],\n"
        "\"option-data4\": [ ],\n"
        "\"option-data6\": [ ],\n"
        "\"next-server\": \"0.0.0.0\",\n"
        "\"server-hostname\": \"\",\n"
        "\"boot-file-name\": \"\",\n"
        "\"host-id\": 0 }\n";

    /// @brief Handler type
    typedef std::function<int (CalloutHandle& handle)> handlerType;

    /// @brief Check handler
    ///
    /// @param handler handler to call
    /// @param command JSON command
    /// @param result expected value returned by the handler
    /// @param rcode expected rcode from answer
    /// @param answer expected answer
    void checkCommand(handlerType handler, ConstElementPtr command,
                      int result, int rcode, ConstElementPtr answer) {
        // Get a callout handle
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        ASSERT_TRUE(callout_handle);
        callout_handle->setArgument("command", command);
        ConstElementPtr response;
        callout_handle->setArgument("response", response);

        // Call the handler
        EXPECT_EQ(result, handler(*callout_handle));

        // Check the response
        callout_handle->getArgument("response", response);
        int got = 0;
        ConstElementPtr comment = parseAnswer(got, response);
        EXPECT_EQ(rcode, got);
        ASSERT_TRUE(answer);
        ASSERT_TRUE(comment);
        EXPECT_EQ(*answer, *comment);
    }

    /// @brief Check handler
    ///
    /// @param handler handler to call
    /// @param command command string
    /// @param result expected value returned by the handler
    /// @param rcode expected rcode from answer
    /// @param answer expected answer
    void checkCommand(handlerType handler, string command, int result,
                      int rcode, ConstElementPtr answer) {
        ConstElementPtr cmd = Element::fromJSON(command);
        checkCommand(handler, cmd, result, rcode, answer);
    }

    /// @brief Check handler
    ///
    /// @param handler handler to call
    /// @param command JSON command
    /// @param result expected value returned by the handler
    /// @param rcode expected rcode from answer
    /// @param answer expected answer
    void checkCommand(handlerType handler, ConstElementPtr command,
                      int result, int rcode, string answer) {
        checkCommand(handler, command, result, rcode, Element::create(answer));
    }

    /// @brief Check handler
    ///
    /// @param handler handler to call
    /// @param command command string
    /// @param result expected value returned by the handler
    /// @param rcode expected rcode from answer
    /// @param answer expected answer
    void checkCommand(handlerType handler, string command, int result,
                      int rcode, string answer) {
        ConstElementPtr cmd = Element::fromJSON(command);
        checkCommand(handler, cmd, result, rcode, Element::create(answer));
    }

    /// Fill cache with 4 entries.
    void fill() {
        ASSERT_EQ(4294967295U, SUBNET_ID_UNUSED);
        HostPtr host = createHost4();
        EXPECT_EQ(0, hcptr_->insert(host, false));
        host = createHost4bis();
        EXPECT_EQ(0, hcptr_->insert(host, false));
        host = createHost6();
        EXPECT_EQ(0, hcptr_->insert(host, false));
        host = createHost6bis();
        EXPECT_EQ(0, hcptr_->insert(host, false));
        EXPECT_EQ(4, hcptr_->size());
    }

    /// @brief Check host ID handling.
    ///
    /// The issue here is that host ID type is uint64_t and
    /// JSON integer type is int64_t, i.e. unsigned vs signed.
    ///
    /// @param hid host ID
    /// @param jint JSON integer
    void checkHostID(HostID hid, int64_t jint) {
        // Build host
        HostPtr host = createHost4();
        host->setHostId(hid);
        ASSERT_EQ(hid, host->getHostId());

        // Check host -> json
        ElementPtr json;
        ASSERT_NO_THROW(json = isc::host_cache::toElement(host));
        ASSERT_TRUE(json);
        ConstElementPtr host_id = json->get("host-id");
        ASSERT_TRUE(host_id);
        EXPECT_EQ(jint, host_id->intValue());

        // Build json
        json = Element::fromJSON(host4_txt);
        json->set("host-id", Element::create(static_cast<long long>(jint)));
        host_id = json->get("host-id");
        ASSERT_TRUE(host_id);
        ASSERT_EQ(jint, host_id->intValue());

        // Check json -> host
        HCEntryParser parser;
        ASSERT_NO_THROW(host = parser.parse(json));
        ASSERT_TRUE(host);
        EXPECT_EQ(hid, host->getHostId());
    }

    /// @brief Test cache-size command.
    void testSizeCommand();

    /// @brief Test cache-flush command.
    void testFlushCommand();

    /// @brief Test cache-get (aka dump) command.
    void testDumpCommand();

    /// @brief Test cache-get-by-id command using hw-address.
    void testByHwAddressCommand();

    /// @brief Test cache-get-by-id command using client-id.
    void testByClientIdCommand();

    /// @brief Test cache-get-by-id command using flex-id.
    void testByFlexIdCommand();

    /// @brief Test cache-get-by-id command using multiple identifiers.
    void testByIdsCommand();

    /// @brief Test cache-insert command.
    void testInsertCommand();

    /// @brief Test cache-write command.
    void testWriteCommand();

    /// @brief Test cache-load command.
    void testLoadCommand();

    /// @brief Test cache-remove command.
    void testRemoveCommand();

    /// @brief Test global reservations.
    void testGlobal();

    /// @brief Test host-id.
    void testHostID();

    /// @brief Test negative.
    void testNegative();

    /// @brief Host Cache
    HostCachePtr hcptr_;

    /// @brief Stores the pre-test DHCP data directory.
    std::string original_datadir_;
};

/// @brief Size handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int sizeHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheSizeHandler(handle));
}

/// @brief Clear handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int clearHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheClearHandler(handle));
}

/// @brief Flush handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int flushHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheFlushHandler(handle));
}

/// @brief Get handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int getHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheGetHandler(handle));
}

/// @brief Get by identifier handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int getByIdHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheGetByIdHandler(handle));
}

/// @brief Insert handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int insertHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheInsertHandler(handle));
}

/// @brief Write handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int writeHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheWriteHandler(handle));
}

/// @brief Load handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int loadHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheLoadHandler(handle));
}

/// @brief Remove handler function
///
/// @param hcptr Pointer to host cache
/// @param handle Handle
/// @return int 0 if successful, 1 if not
int removeHandler(HostCachePtr hcptr, CalloutHandle& handle) {
    return (hcptr->cacheRemoveHandler(handle));
}

// Verifies different valid and invalid configurations.
TEST_F(CommandTest, config) {
    ConstElementPtr config;

    // Empty config is fine.
    EXPECT_NO_THROW(hcptr_->configure(config));

    // Check defaults.
    EXPECT_EQ(0, hcptr_->getMaximum());

    // Config must be a map.
    config = Element::createList();
    EXPECT_THROW(hcptr_->configure(config), ConfigError);

    // Fill config.
    config = Element::fromJSON("{ \"maximum\": 19 }");
    EXPECT_NO_THROW(hcptr_->configure(config));
    EXPECT_EQ(19, hcptr_->getMaximum());

    // Check maximum.
    config = Element::fromJSON("{ \"maximum\": 0 }");
    EXPECT_NO_THROW(hcptr_->configure(config));
    EXPECT_EQ(0, hcptr_->getMaximum());

    config = Element::fromJSON("{ \"maximum\": -1 }");
    EXPECT_THROW(hcptr_->configure(config), ConfigError);
    config = Element::fromJSON("{ \"maximum\": 1000000001 }");
    EXPECT_THROW(hcptr_->configure(config), ConfigError);
    config = Element::fromJSON("{ \"maximum\": \"infinite\" }");
    EXPECT_THROW(hcptr_->configure(config), ConfigError);

    config = Element::fromJSON("{ \"foo\": \"bar\" }");
    EXPECT_NO_THROW(hcptr_->configure(config));
}

// Verifies that cache-size works as expected.
void
CommandTest::testSizeCommand() {
    // Prepare
    handlerType size_handler = std::bind(&sizeHandler, hcptr_, ph::_1);
    string size_cmd = "{ \"command\": \"cache-size\" }";
    fill();

    ElementPtr result = Element::createMap();
    result->set("size", Element::create(4));

    // Get size (expect 4).
    checkCommand(size_handler, size_cmd, 0, 0, result);
}

// Verifies that cache-flush works as expected.
void
CommandTest::testFlushCommand() {
    // Prepare
    handlerType flush_handler = std::bind(&flushHandler, hcptr_, ph::_1);
    string flush1_cmd = "{ \"command\": \"cache-flush\", \"arguments\": 1 }";
    handlerType clear_handler = std::bind(&clearHandler, hcptr_, ph::_1);
    string clear_cmd = "{ \"command\": \"cache-clear\" }";
    fill();

    // Flush an entry
    checkCommand(flush_handler, flush1_cmd, 0, 0,
                 "Cache flushed (1 entries removed).");
    EXPECT_EQ(3, hcptr_->size());

    // Flush another
    checkCommand(flush_handler, flush1_cmd, 0, 0,
                 "Cache flushed (1 entries removed).");
    EXPECT_EQ(2, hcptr_->size());

    // Flush all aka clear
    checkCommand(clear_handler, clear_cmd, 0, 0, "Cache cleared.");
    EXPECT_EQ(0, hcptr_->size());

    // No issue to flush an empty cache
    checkCommand(flush_handler, flush1_cmd, 0, 0,
                 "Cache flushed (0 entries removed).");

    // Check errors
    string noarg_cmd =  "{ \"command\": \"cache-flush\" }";
    checkCommand(flush_handler, noarg_cmd, 1, 1,
                 "no parameters specified for the command");
    string badarg_cmd =
        "{ \"command\": \"cache-flush\", \"arguments\": true }";
    checkCommand(flush_handler, badarg_cmd, 1, 1,
                 "intValue() called on non-integer Element in (<string>:1:42)");
    string negarg_cmd =
        "{ \"command\": \"cache-flush\", \"arguments\": -1 }";
    checkCommand(flush_handler, negarg_cmd, 1, 1, "invalid (<0) parameter");
    string zeroarg_cmd =
        "{ \"command\": \"cache-flush\", \"arguments\": 0 }";
    checkCommand(flush_handler, zeroarg_cmd, 1, 1,
                 "invalid (0) parameter: please use cache-clear command");
    string notall_cmd =
        "{ \"command\": \"cache-flush\", \"arguments\": \"everything\" }";
}

// Verifies that cache-get dumps the cache content.
void
CommandTest::testDumpCommand() {
    // Prepare
    handlerType get_handler = std::bind(&getHandler, hcptr_, ph::_1);
    string get_cmd = "{ \"command\": \"cache-get\" }";

    // Dump empty cache
    ElementPtr entries = Element::createList();
    checkCommand(get_handler, get_cmd, 0, 3, entries);

    // Dump cache with host4
    EXPECT_EQ(0, hcptr_->insert(createHost4(), false));
    entries->add(Element::fromJSON(host4_txt));
    checkCommand(get_handler, get_cmd, 0, 0, entries);

    // Dump cache with host4 and host6
    EXPECT_EQ(0, hcptr_->insert(createHost6(), false));
    entries->add(Element::fromJSON(host6_txt));
    checkCommand(get_handler, get_cmd, 0, 0, entries);
}

// Verifies that cache-get-by-id returns expected entries using hw-address.
void
CommandTest::testByHwAddressCommand() {
    // Prepare
    handlerType get_by_id_handler = std::bind(&getByIdHandler, hcptr_, ph::_1);
    string get_by_id_cmd = "{ "
      "\"command\": \"cache-get-by-id\","
      "\"arguments\": { \"hw-address\": \"01:02:03:04:05:06\" } }";

    // From empty cache
    ElementPtr entries = Element::createList();
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 3, entries);

    // From cache with host4
    EXPECT_EQ(0, hcptr_->insert(createHost4(), false));
    entries->add(Element::fromJSON(host4_txt));
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 0, entries);

    // From cache with host4 and host6
    EXPECT_EQ(0, hcptr_->insert(createHost6(), false));
    entries->add(Element::fromJSON(host6_txt));
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 0, entries);
}

// Verifies that cache-get-by-id returns expected entries using client-id.
void
CommandTest::testByClientIdCommand() {
    // Prepare
    handlerType get_by_id_handler = std::bind(&getByIdHandler, hcptr_, ph::_1);
    string get_by_id_cmd = "{ "
      "\"command\": \"cache-get-by-id\","
      "\"arguments\": { \"client-id\": \"01:02:03:04:05:06\" } }";

    // From empty cache
    ElementPtr entries = Element::createList();
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 3, entries);

    // From cache with host4
    HostPtr h(new Host("010203040506", "client-id",
                       SubnetID(4), SubnetID(SUBNET_ID_UNUSED),
                       IOAddress("192.0.2.100"),
                       "somehost.example.org",
                       std::string(), std::string(),
                       IOAddress("192.0.0.2"),
                       "server-hostname.example.org",
                       "bootfile.efi"));
    string txt = "{\n"
        "\"client-id\": \"010203040506\",\n"
        "\"subnet-id4\": 4,\n"
        "\"subnet-id6\": 4294967295,\n" // SUBNET_ID_UNUSED
        "\"ip-address\": \"192.0.2.100\",\n"
        "\"hostname\": \"somehost.example.org\",\n"
        "\"client-classes4\": [ ],\n"
        "\"client-classes6\": [ ],\n"
        "\"option-data4\": [ ],\n"
        "\"option-data6\": [ ],\n"
        "\"next-server\": \"192.0.0.2\",\n"
        "\"server-hostname\": \"server-hostname.example.org\",\n"
        "\"boot-file-name\": \"bootfile.efi\",\n"
        "\"host-id\": 0 }\n";
    EXPECT_EQ(0, hcptr_->insert(h, false));
    entries->add(Element::fromJSON(txt));
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 0, entries);
}

// Verifies that cache-get-by-id returns expected entries using flex-id.
void
CommandTest::testByFlexIdCommand() {
    // Prepare
    handlerType get_by_id_handler = std::bind(&getByIdHandler, hcptr_, ph::_1);
    string get_by_id_cmd = "{ "
      "\"command\": \"cache-get-by-id\","
      "\"arguments\": { \"flex-id\": \"01:02:03:04:05:06\" } }";

    // From empty cache
    ElementPtr entries = Element::createList();
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 3, entries);

    // From cache with host4
    HostPtr h(new Host("010203040506", "flex-id",
                       SubnetID(4), SubnetID(SUBNET_ID_UNUSED),
                       IOAddress("192.0.2.100"),
                       "somehost.example.org",
                       std::string(), std::string(),
                       IOAddress("192.0.0.2"),
                       "server-hostname.example.org",
                       "bootfile.efi"));
    string txt = "{\n"
        "\"flex-id\": \"010203040506\",\n"
        "\"subnet-id4\": 4,\n"
        "\"subnet-id6\": 4294967295,\n" // SUBNET_ID_UNUSED
        "\"ip-address\": \"192.0.2.100\",\n"
        "\"hostname\": \"somehost.example.org\",\n"
        "\"client-classes4\": [ ],\n"
        "\"client-classes6\": [ ],\n"
        "\"option-data4\": [ ],\n"
        "\"option-data6\": [ ],\n"
        "\"next-server\": \"192.0.0.2\",\n"
        "\"server-hostname\": \"server-hostname.example.org\",\n"
        "\"boot-file-name\": \"bootfile.efi\",\n"
        "\"host-id\": 0 }\n";
    EXPECT_EQ(0, hcptr_->insert(h, false));
    entries->add(Element::fromJSON(txt));
    checkCommand(get_by_id_handler, get_by_id_cmd, 0, 0, entries);
}

// Verifies that cache-get-by-id rejects multiple identifiers.
void
CommandTest::testByIdsCommand() {
    // Prepare
    handlerType get_by_id_handler = std::bind(&getByIdHandler, hcptr_, ph::_1);
    string get_by_id_cmd = "{ "
      "\"command\": \"cache-get-by-id\","
      "\"arguments\": { \"hw-address\": \"01:02:03:04:05:06\","
      "  \"client-id\": \"010203040506\" } }";

    checkCommand(get_by_id_handler, get_by_id_cmd, 1, 1,
                 "only one identifier can be specified");
}

// Verifies that cache-insert inserts entries into the cache.
void
CommandTest::testInsertCommand() {
    // Prepare
    handlerType add_handler = std::bind(&insertHandler, hcptr_, ph::_1);
    handlerType get_handler = std::bind(&getHandler, hcptr_, ph::_1);
    string get_cmd = "{ \"command\": \"cache-get\" }";
    ElementPtr add = Element::createMap();
    add->set("command", Element::create(string("cache-insert")));

    // Requires arguments
    checkCommand(add_handler, add, 1, 1,
                 "no parameters specified for the command");

    // Empty arguments does nothing
    ElementPtr args = Element::createList();
    add->set("arguments", args);
    checkCommand(add_handler, add, 0, 0,
                 "0 entries inserted (0 overwritten by more recent entries).");
    EXPECT_EQ(0, hcptr_->size());

    // Insert one entry
    args = Element::fromJSON(host4_txt);
    add->set("arguments", args);
    checkCommand(add_handler, add, 0, 0,
                 "1 entries inserted (0 overwritten by more recent entries).");
    EXPECT_EQ(1, hcptr_->size());

    // Insert a list
    args = Element::createList();
    args->add(Element::fromJSON(host6_txt));
    add->set("arguments", args);
    checkCommand(add_handler, add, 0, 0,
                 "1 entries inserted (0 overwritten by more recent entries).");
    EXPECT_EQ(2, hcptr_->size());

    // Overwrite an entry
    args = Element::createList();
    args->add(Element::fromJSON(host4_txt));
    add->set("arguments", args);
    checkCommand(add_handler, add, 0, 0,
                 "1 entries inserted (1 overwritten by more recent entries).");
    EXPECT_EQ(2, hcptr_->size());

    // Check the order
    ElementPtr entries = Element::createList();
    entries->add(Element::fromJSON(host6_txt));
    entries->add(Element::fromJSON(host4_txt));
    add->set("arguments", args);
    checkCommand(get_handler, get_cmd, 0, 0, entries);

    // JSON list (aka array) is ordered.
    args->add(Element::fromJSON(host6_txt));
    // [6, 4] != [4, 6]
    EXPECT_NE(*entries, *args);

    // Make the list parser to fail
    add->set("arguments", Element::create(true));
    checkCommand(add_handler, add, 1, 1,
                 "listValue() called on non-list Element");

    // Make the parser to fail
    args = Element::fromJSON(host4_txt);
    args->remove("hw-address");
    add->set("arguments", args);
    checkCommand(add_handler, add, 1, 1, "no identifier");
}

// Verifies that cache-write really writes the expected file.
void
CommandTest::testWriteCommand() {
    // Prepare
    handlerType write_handler = std::bind(&writeHandler, hcptr_, ph::_1);
    string file_txt = "dump.json";
    string full_file_txt = CfgMgr::instance().getDataDir() + "/" + file_txt;
    string write_cmd =
        "{ \"command\": \"cache-write\", \"arguments\": \"" + file_txt + "\" }";

    // Insert two entries
    EXPECT_EQ(0, hcptr_->insert(createHost4(), false));
    EXPECT_EQ(0, hcptr_->insert(createHost6(), false));
    EXPECT_EQ(2, hcptr_->size());

    // Write file
    checkCommand(write_handler, write_cmd, 0, 0,
                 "2 entries dumped to '" + full_file_txt + "'.");

    // Check file
    ifstream f(full_file_txt, ios::binary | ios::ate);
    ASSERT_TRUE(f.good());
    EXPECT_LE(host4_txt.size(), static_cast<size_t>(f.tellg()));
    ElementPtr from_file = Element::fromJSONFile(full_file_txt);
    ASSERT_TRUE(from_file);
    ElementPtr expected = Element::createList();
    expected->add(Element::fromJSON(host4_txt));
    expected->add(Element::fromJSON(host6_txt));
    EXPECT_EQ(*from_file, *expected);

    // Check with full path.
    write_cmd = "{ \"command\": \"cache-write\", \"arguments\": \"";
    write_cmd += full_file_txt + "\" }";
    checkCommand(write_handler, write_cmd, 0, 0,
                 "2 entries dumped to '" + full_file_txt + "'.");
    ifstream ff(full_file_txt, ios::binary | ios::ate);
    ASSERT_TRUE(ff.good());
    EXPECT_LE(host4_txt.size(), static_cast<size_t>(ff.tellg()));
    from_file = Element::fromJSONFile(full_file_txt);
    ASSERT_TRUE(from_file);
    EXPECT_EQ(*from_file, *expected);

    // Check errors
    string noarg_cmd =  "{ \"command\": \"cache-write\" }";
    checkCommand(write_handler, noarg_cmd, 1, 1,
                 "no parameters specified for the command");
    string badarg_cmd =
        "{ \"command\": \"cache-write\", \"arguments\": true }";
    checkCommand(write_handler, badarg_cmd, 1, 1,
                 "invalid (not a string) parameter");
    string emptyarg_cmd =
        "{ \"command\": \"cache-write\", \"arguments\": \"\" }";
    checkCommand(write_handler, emptyarg_cmd, 1, 1,
                 "parameter is invalid: path: '' has no filename");
    string badpath = "/foo/bar";
    string badpath_cmd =
        "{ \"command\": \"cache-write\", \"arguments\": \"" + badpath + "\" }";
    string exp_error = "parameter is invalid: invalid path specified: ";
    exp_error += "'/foo', ";
    exp_error += "supported path is '";
    exp_error += CfgMgr::instance().getDataDir();
    exp_error += "'";
    checkCommand(write_handler, badpath_cmd, 1, 1, exp_error);
}

// Verifies that cache-load can load a dump file.
void
CommandTest::testLoadCommand() {
    // Prepare
    handlerType load_handler = std::bind(&loadHandler, hcptr_, ph::_1);
    string file_txt = "source.json";
    string load_cmd =
        "{ \"command\": \"cache-load\", \"arguments\": \"" + file_txt + "\" }";

    // Fill file
    ofstream f(file_txt, ios::trunc);
    ASSERT_TRUE(f.is_open());
    f << "[\n"
      << host4_txt << "\n,\n"
      << host6_txt << "\n,\n"
      << host4_txt << "\n]\n";

    f.close();

    // Load file
    checkCommand(load_handler, load_cmd, 0, 0,
                 "3 entries loaded from '" + file_txt + "' (1 overwritten "
                 "by more recent entries).");
    EXPECT_EQ(2, hcptr_->size());

    // Check errors
    string noarg_cmd =  "{ \"command\": \"cache-load\" }";
    checkCommand(load_handler, noarg_cmd, 1, 1,
                 "no parameters specified for the command");
    string badarg_cmd =
        "{ \"command\": \"cache-load\", \"arguments\": true }";
    checkCommand(load_handler, badarg_cmd, 1, 1,
                 "invalid (not a string) parameter");
    string emptyarg_cmd =
        "{ \"command\": \"cache-load\", \"arguments\": \"\" }";
    checkCommand(load_handler, emptyarg_cmd, 1, 1,
                 "invalid (empty string) parameter");
    string nullarg_cmd =
        "{ \"command\": \"cache-load\", \"arguments\": \"/dev/null\" }";
    checkCommand(load_handler, nullarg_cmd, 1, 1, "nothing read");
    string notexists = "/this/does/not/exit";
    string notexists_cmd =
        "{ \"command\": \"cache-load\", \"arguments\": \"" + notexists + "\" }";
    checkCommand(load_handler, notexists_cmd, 1, 1,
                 "failed to read file '" + notexists + "': "
                 "No such file or directory");
}

// Verifies that cache-remove behaves as expected.
void
CommandTest::testRemoveCommand() {
    // Prepare
    handlerType del_handler = std::bind(&removeHandler, hcptr_, ph::_1);
    ElementPtr del = Element::createMap();
    del->set("command", Element::create(string("cache-remove")));
    fill();
    ASSERT_EQ(4, hcptr_->size());

    // Common remove by address.
    ElementPtr args = Element::createMap();
    args->set("subnet-id", Element::create(4));
    args->set("ip-address", Element::create(string("192.0.2.200")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 0, 0, "Host removed.");
    EXPECT_EQ(3, hcptr_->size());

    // Remove it a second time won't find it.
    checkCommand(del_handler, del, 0, 3, "Host not removed (not found).");
    EXPECT_EQ(3, hcptr_->size());

    // Common remove by identifier.
    args = Element::createMap();
    args->set("subnet-id6", Element::create(6));
    args->set("hw-address", Element::create(string("07:08:09:0a:0b:0c")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 0, 0, "Host removed.");
    EXPECT_EQ(2, hcptr_->size());

    // Subnet-id specification is flexible for by address.
    args = Element::createMap();
    args->set("subnet-id6", Element::create(6));
    args->set("ip-address", Element::create(string("2001:db8:dead:beef::")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 0, 0, "Host removed.");
    EXPECT_EQ(1, hcptr_->size());

    // Check errors.

    // No parameters
    del->remove("arguments");
    checkCommand(del_handler, del, 1, 1,
                 "no parameters specified for the command");
    // Not a map
    args = Element::createList();
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "invalid (not a map) parameter");
    // Unknown parameter
    args = Element::createMap();
    args->set("subnetID", Element::create(4));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "unknown parameter 'subnetID'");
    // No subnet-id
    args = Element::createMap();
    args->set("ip-address", Element::create(string("192.0.2.200")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "subnet-id is required");
    // Bad address
    args = Element::createMap();
    args->set("subnet-id", Element::create(4));
    args->set("ip-address", Element::create(string("192.0.2.2.0")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1,
                 "Failed to convert string to address '192.0.2.2.0': "
                 "Invalid argument");
    // Undefined IPv4 address
    args = Element::createMap();
    args->set("subnet-id", Element::create(4));
    args->set("ip-address", Element::create(string("0.0.0.0")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "invalid ip-address '0.0.0.0'");
    // Undefined IPv6 address
    args = Element::createMap();
    args->set("subnet-id", Element::create(6));
    args->set("ip-address", Element::create(string("::")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "invalid ip-address '::'");
    // No address nor identifier
    args = Element::createMap();
    args->set("subnet-id4", Element::create(4));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1,
                 "either ip-address or an identifier is required");
    // Identifier in unknown family
    args = Element::createMap();
    args->set("subnet-id", Element::create(4));
    args->set("hw-address", Element::create(string("07:08:09:0a:0b:0c")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1,
                 "either subnet-id4 or subnet-id6 is required");
    // Bad identifier
    args = Element::createMap();
    args->set("subnet-id4", Element::create(4));
    args->set("hw-address", Element::create(string("foobar")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "invalid identifier 'foobar'");
    // Multiple subnet-id's
    args = Element::createMap();
    args->set("subnet-id", Element::create(4));
    args->set("subnet-id4", Element::create(4));
    args->set("hw-address", Element::create(string("07:08:09:0a:0b:0c")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "inconsistent parameters");
    // Multiple identifiers
    args = Element::createMap();
    args->set("subnet-id4", Element::create(4));
    args->set("hw-address", Element::create(string("07:08:09:0a:0b:0c")));
    args->set("duid", Element::create(string("07:08:09:0a:0b:0c")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "inconsistent parameters");
    // Address and subnet-id in different families.
    args = Element::createMap();
    args->set("subnet-id6", Element::create(4));
    args->set("ip-address", Element::create(string("192.0.2.200")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "inconsistent parameters");
    // The other combination.
    args = Element::createMap();
    args->set("subnet-id4", Element::create(6));
    args->set("ip-address", Element::create(string("2001:db8::cafe:babe")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "inconsistent parameters");
    // Empty identifier
    args = Element::createMap();
    args->set("subnet-id4", Element::create(4));
    args->set("hw-address", Element::create(string("")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 1, 1, "invalid (empty) identifier");

    // All of these failed.
    EXPECT_EQ(1, hcptr_->size());
}

// Verifies that global reservations are handled.
void
CommandTest::testGlobal() {
    // Prepare remove.
    handlerType del_handler = std::bind(&removeHandler, hcptr_, ph::_1);
    ElementPtr del = Element::createMap();
    del->set("command", Element::create(string("cache-remove")));

    // Like fill() but replacing the subnet ID by global (0).
    HostPtr host = createHost4();
    host->setIPv4SubnetID(SUBNET_ID_GLOBAL);
    EXPECT_EQ(0, hcptr_->insert(host, false));
    host = createHost4bis();
    host->setIPv4SubnetID(SUBNET_ID_GLOBAL);
    EXPECT_EQ(0, hcptr_->insert(host, false));
    host = createHost6();
    host->setIPv6SubnetID(SUBNET_ID_GLOBAL);
    EXPECT_EQ(0, hcptr_->insert(host, false));
    host = createHost6bis();
    host->setIPv6SubnetID(SUBNET_ID_GLOBAL);
    EXPECT_EQ(0, hcptr_->insert(host, false));
    EXPECT_EQ(4, hcptr_->size());

    // Copy of remove positive tests.

    // Common remove by address.
    ElementPtr args = Element::createMap();
    args->set("subnet-id",
              Element::create(static_cast<int64_t>(SUBNET_ID_GLOBAL)));
    args->set("ip-address", Element::create(string("192.0.2.200")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 0, 0, "Host removed.");
    EXPECT_EQ(3, hcptr_->size());

    // Remove it a second time won't find it.
    checkCommand(del_handler, del, 0, 3, "Host not removed (not found).");
    EXPECT_EQ(3, hcptr_->size());

    // Common remove by identifier.
    args = Element::createMap();
    args->set("subnet-id6",
              Element::create(static_cast<int64_t>(SUBNET_ID_GLOBAL)));
    args->set("hw-address", Element::create(string("07:08:09:0a:0b:0c")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 0, 0, "Host removed.");
    EXPECT_EQ(2, hcptr_->size());

    // Subnet-id specification is flexible for by address.
    args = Element::createMap();
    args->set("subnet-id6",
              Element::create(static_cast<int64_t>(SUBNET_ID_GLOBAL)));
    args->set("ip-address", Element::create(string("2001:db8:dead:beef::")));
    del->set("arguments", args);
    checkCommand(del_handler, del, 0, 0, "Host removed.");
    EXPECT_EQ(1, hcptr_->size());
}

// Verifies that host-id is correctly handled.
void
CommandTest::testHostID() {
    checkHostID(0, 0);
    checkHostID(1, 1);
    checkHostID(123456ULL, 123456LL);
    // 2^63 - 1
    checkHostID(9223372036854775807ULL, 9223372036854775807LL);
    // 2^63
    checkHostID(9223372036854775808ULL, -9223372036854775807LL - 1);
    // 2^63 + 1
    checkHostID(9223372036854775809ULL, -9223372036854775807LL);
    // 2^63 + 10
    checkHostID(9223372036854775818ULL, -9223372036854775798LL);
    // 2^64 - 10
    checkHostID(18446744073709551606ULL, -10LL);
    // 2^64 - 1
    checkHostID(18446744073709551615ULL, -1LL);
}

// Verifies that the negative cache is correctly handled.
void
CommandTest::testNegative() {
    HostPtr host = createHost4();

    // Check false case.
    bool negative = false;
    host->setNegative(negative);
    ASSERT_EQ(negative, host->getNegative());

    // Check host -> json
    ElementPtr json;
    ASSERT_NO_THROW(json = isc::host_cache::toElement(host));
    ASSERT_TRUE(json);
    ConstElementPtr neg = json->get("negative");
    ASSERT_FALSE(neg);

    // Check json -> host
    HCEntryParser parser;
    ConstHostPtr hostf;
    ASSERT_NO_THROW(hostf = parser.parse(json));
    ASSERT_TRUE(hostf);
    EXPECT_EQ(negative, hostf->getNegative());

    // Again with a negative: false entry
    json->set("negative", Element::create(negative));
    ASSERT_NO_THROW(hostf = parser.parse(json));
    ASSERT_TRUE(hostf);
    EXPECT_EQ(negative,hostf->getNegative());

    // Check true case.
    negative = true;
    host->setNegative(negative);
    ASSERT_EQ(negative, host->getNegative());

    // host -> json
    ASSERT_NO_THROW(json = isc::host_cache::toElement(host));
    ASSERT_TRUE(json);
    neg = json->get("negative");
    ASSERT_TRUE(neg);
    EXPECT_EQ(negative, neg->boolValue());

    // json -> host
    ConstHostPtr hostt;
    ASSERT_NO_THROW(hostt = parser.parse(json));
    ASSERT_TRUE(hostt);
    ASSERT_EQ(negative, hostt->getNegative());
}

TEST_F(CommandTest, size) {
    testSizeCommand();
}

TEST_F(CommandTest, sizeMultiThreading) {
    MultiThreadingTest mt(true);
    testSizeCommand();
}

TEST_F(CommandTest, flush) {
    testFlushCommand();
}

TEST_F(CommandTest, flushMultiThreading) {
    MultiThreadingTest mt(true);
    testFlushCommand();
}

TEST_F(CommandTest, dump) {
    testDumpCommand();
}

TEST_F(CommandTest, dumpMultiThreading) {
    MultiThreadingTest mt(true);
    testDumpCommand();
}

TEST_F(CommandTest, byHwAddress) {
    testByHwAddressCommand();
}

TEST_F(CommandTest, byHwAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testByHwAddressCommand();
}

TEST_F(CommandTest, byClientId) {
    testByClientIdCommand();
}

TEST_F(CommandTest, byClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testByClientIdCommand();
}

TEST_F(CommandTest, byFlexId) {
    testByFlexIdCommand();
}

TEST_F(CommandTest, byFlexIdMultiThreading) {
    MultiThreadingTest mt(true);
    testByFlexIdCommand();
}

TEST_F(CommandTest, byIds) {
    testByIdsCommand();
}

TEST_F(CommandTest, byIdsMultiThreading) {
    MultiThreadingTest mt(true);
    testByIdsCommand();
}

TEST_F(CommandTest, insert) {
    testInsertCommand();
}

TEST_F(CommandTest, insertMultiThreading) {
    MultiThreadingTest mt(true);
    testInsertCommand();
}

TEST_F(CommandTest, write) {
    testWriteCommand();
}

TEST_F(CommandTest, writeMultiThreading) {
    MultiThreadingTest mt(true);
    testWriteCommand();
}

TEST_F(CommandTest, writeEnvVarOverride) {
    EnvVarWrapper data_dir_env_var_("KEA_DHCP_DATA_DIR");
    data_dir_env_var_.setValue("/tmp");
    auto valid_path = CfgMgr::instance().getDataDir(true);
    EXPECT_EQ(valid_path, "/tmp");
    testWriteCommand();
}

TEST_F(CommandTest, load) {
    testLoadCommand();
}

TEST_F(CommandTest, loadMultiThreading) {
    MultiThreadingTest mt(true);
    testLoadCommand();
}

TEST_F(CommandTest, remove) {
    testRemoveCommand();
}

TEST_F(CommandTest, removeMultiThreading) {
    MultiThreadingTest mt(true);
    testRemoveCommand();
}

TEST_F(CommandTest, global) {
    testGlobal();
}

TEST_F(CommandTest, globalMultiThreading) {
    MultiThreadingTest mt(true);
    testGlobal();
}

TEST_F(CommandTest, hostID) {
    testHostID();
}

TEST_F(CommandTest, hostIDMultiThreading) {
    MultiThreadingTest mt(true);
    testHostID();
}

TEST_F(CommandTest, negative) {
    testNegative();
}

TEST_F(CommandTest, negativeMultiThreading) {
    MultiThreadingTest mt(true);
    testNegative();
}

} // end of anonymous namespace
