// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>
#include <config/command_interpreter.h>
#include <config/tests/data_def_unittests_config.h>
#include <log/logger_name.h>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <fstream>

using namespace isc::data;
using namespace isc::config;
using namespace std;

namespace {

ElementPtr
el(const std::string& str) {
    return (Element::fromJSON(str));
}

TEST(CommandInterpreterTest, createAnswer) {
    ConstElementPtr answer;
    answer = createAnswer();
    EXPECT_EQ("{ \"result\": 0 }", answer->str());
    answer = createAnswer(1, "error");
    EXPECT_EQ("{ \"result\": 1, \"text\": \"error\" }", answer->str());

    EXPECT_THROW(createAnswer(1, ElementPtr()), CtrlChannelError);
    EXPECT_THROW(createAnswer(1, Element::create(1)), CtrlChannelError);

    ConstElementPtr arg = el("[ \"just\", \"some\", \"data\" ]");
    answer = createAnswer(0, arg);
    EXPECT_EQ("{ \"arguments\": [ \"just\", \"some\", \"data\" ], \"result\": 0 }",
              answer->str());
}

TEST(CommandInterpreterTest, parseAnswer) {
    ConstElementPtr answer;
    ConstElementPtr arg;
    int rcode;

    EXPECT_THROW(parseAnswer(rcode, ElementPtr()), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("1")), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("[]")), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("{  }")), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"something\": 1 }")), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": [ 0 ] }")), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": [ 1 ] }")), CtrlChannelError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": [ 1, 1 ] }")), CtrlChannelError);
    
    answer = el("{ \"result\": 0 }");
    arg = parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);
    EXPECT_TRUE(isNull(arg));

    answer = el("{ \"result\": 1, \"text\": \"error\" }");
    arg = parseAnswer(rcode, answer);
    EXPECT_EQ(1, rcode);
    EXPECT_EQ("error", arg->stringValue());

    answer = el("{ \"result\": 0, \"arguments\": [ \"just\", \"some\", \"data\" ] }");
    arg = parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);
    EXPECT_EQ("[ \"just\", \"some\", \"data\" ]", arg->str());
}

TEST(CommandInterpreterTest, createCommand) {
    ConstElementPtr command;
    ConstElementPtr arg;

    command = createCommand("my_command");
    ASSERT_EQ("{ \"command\": \"my_command\" }", command->str());

    arg = el("1");
    command = createCommand("my_command", arg);
    ASSERT_EQ("{ \"arguments\": 1, \"command\": \"my_command\" }",
              command->str());

    arg = el("[ \"a\", \"b\" ]");
    command = createCommand("my_cmd", arg);
    ASSERT_EQ("{ \"arguments\": [ \"a\", \"b\" ], \"command\": \"my_cmd\" }",
              command->str());

    arg = el("{ \"a\": \"map\" }");
    command = createCommand("foo", arg);
    ASSERT_EQ("{ \"arguments\": { \"a\": \"map\" }, \"command\": \"foo\" }",
              command->str());
}

TEST(CommandInterpreterTest, parseCommand) {
    ConstElementPtr arg;
    std::string cmd;

    // should throw
    EXPECT_THROW(parseCommand(arg, ElementPtr()), CtrlChannelError);
    EXPECT_THROW(parseCommand(arg, el("1")), CtrlChannelError);
    EXPECT_THROW(parseCommand(arg, el("{  }")), CtrlChannelError);
    EXPECT_THROW(parseCommand(arg, el("{ \"not a command\": 1 }")), CtrlChannelError);
    EXPECT_THROW(parseCommand(arg, el("{ \"command\": 1 }")), CtrlChannelError);
    EXPECT_THROW(parseCommand(arg, el("{ \"command\": [] }")), CtrlChannelError);
    EXPECT_THROW(parseCommand(arg, el("{ \"command\": [ 1 ] }")), CtrlChannelError);

    cmd = parseCommand(arg, el("{ \"command\": \"my_command\" }"));
    EXPECT_EQ("my_command", cmd);
    EXPECT_FALSE(arg);

    cmd = parseCommand(arg, el("{ \"command\": \"my_command\", \"arguments\": 1 }"));
    ASSERT_TRUE(arg);
    EXPECT_EQ("my_command", cmd);
    EXPECT_EQ("1", arg->str());

    parseCommand(arg, el("{ \"command\": \"my_command\", \"arguments\": [ \"some\", \"argument\", \"list\" ] }"));
    EXPECT_EQ("my_command", cmd);
    ASSERT_TRUE(arg);
    EXPECT_EQ("[ \"some\", \"argument\", \"list\" ]", arg->str());

}

void doRelatedLoggersTest(const char* input, const char* expected) {
    ConstElementPtr all_conf = isc::data::Element::fromJSON(input);
    ConstElementPtr expected_conf = isc::data::Element::fromJSON(expected);
    EXPECT_EQ(*expected_conf, *isc::config::getRelatedLoggers(all_conf));
}

TEST(LogConfigTest, relatedLoggersTest) {
    // make sure logger configs for 'other' programs are ignored,
    // and that * is substituted correctly
    // We'll use a root logger name of "kea-test".
    isc::log::setRootLoggerName("kea-test");

    doRelatedLoggersTest("[{ \"name\": \"other_module\" }]",
                         "[]");
    doRelatedLoggersTest("[{ \"name\": \"other_module.somelib\" }]",
                         "[]");
    doRelatedLoggersTest("[{ \"name\": \"test_other\" }]",
                         "[]");
    doRelatedLoggersTest("[{ \"name\": \"test_other.somelib\" }]",
                         "[]");
    doRelatedLoggersTest("[ { \"name\": \"other_module\" },"
                         "  { \"name\": \"test\" }]",
                         "[ { \"name\": \"kea-test\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"test\" }]",
                         "[ { \"name\": \"kea-test\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"test.somelib\" }]",
                         "[ { \"name\": \"kea-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"other_module.somelib\" },"
                         "  { \"name\": \"test.somelib\" }]",
                         "[ { \"name\": \"kea-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"other_module.somelib\" },"
                         "  { \"name\": \"test\" },"
                         "  { \"name\": \"test.somelib\" }]",
                         "[ { \"name\": \"kea-test\" },"
                         "  { \"name\": \"kea-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"*\" }]",
                         "[ { \"name\": \"kea-test\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"*.somelib\" }]",
                         "[ { \"name\": \"kea-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"*\", \"severity\": \"DEBUG\" },"
                         "  { \"name\": \"test\", \"severity\": \"WARN\"}]",
                         "[ { \"name\": \"kea-test\", \"severity\": \"WARN\"} ]");
    doRelatedLoggersTest("[ { \"name\": \"*\", \"severity\": \"DEBUG\" },"
                         "  { \"name\": \"some_module\", \"severity\": \"WARN\"}]",
                         "[ { \"name\": \"kea-test\", \"severity\": \"DEBUG\"} ]");
    doRelatedLoggersTest("[ { \"name\": \"kea-test\" }]",
                         "[]");
    // make sure 'bad' things like '*foo.x' or '*lib' are ignored
    // (cfgmgr should have already caught it in the logconfig plugin
    // check, and is responsible for reporting the error)
    doRelatedLoggersTest("[ { \"name\": \"*foo\" }]",
                         "[ ]");
    doRelatedLoggersTest("[ { \"name\": \"*foo.bar\" }]",
                         "[ ]");
    doRelatedLoggersTest("[ { \"name\": \"*foo\" },"
                         "  { \"name\": \"*foo.lib\" },"
                         "  { \"name\": \"test\" } ]",
                         "[ { \"name\": \"kea-test\" } ]");
}

}
