// Copyright (C) 2009,2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <cc/command_interpreter.h>
#include <config/tests/data_def_unittests_config.h>
#include <log/logger_name.h>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <fstream>

using namespace isc::data;
using namespace isc::config;
using namespace std;

namespace {


/// @brief Convenience method for creating elements from JSON string
///
/// @param str string to be converted
/// @return Element structure
ElementPtr
el(const std::string& str) {
    return (Element::fromJSON(str));
}

// This test verifies that that createAnswer method is able to generate
// various answers.
TEST(CommandInterpreterTest, createAnswer) {
    ConstElementPtr answer;

    // By default the answer is a successful one.
    answer = createAnswer();
    EXPECT_EQ("{ \"result\": 0 }", answer->str());

    // Let's check if we can generate an error.
    answer = createAnswer(1, "error");
    EXPECT_EQ("{ \"result\": 1, \"text\": \"error\" }", answer->str());

    // This is expected to throw. When status code is non-zero (indicating error),
    // textual explanation is mandatory.
    EXPECT_THROW(createAnswer(1, ElementPtr()), CtrlChannelError);
    EXPECT_THROW(createAnswer(1, Element::create(1)), CtrlChannelError);

    // Let's check if answer can be generate with some data in it.
    ConstElementPtr arg = el("[ \"just\", \"some\", \"data\" ]");
    answer = createAnswer(0, arg);
    EXPECT_EQ("{ \"arguments\": [ \"just\", \"some\", \"data\" ], \"result\": 0 }",
              answer->str());
}

// This test checks whether parseAnswer is able to handle well and malformed
// answers.
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

// This test checks whether createCommand function is able to create commands
// with and without parameters.
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

// This test checks whether parseCommand function is able to parse various valid
// and malformed commands.
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

    parseCommand(arg, el("{ \"command\": \"my_command\", \"arguments\": "
                         "[ \"some\", \"argument\", \"list\" ] }"));
    EXPECT_EQ("my_command", cmd);
    ASSERT_TRUE(arg);
    EXPECT_EQ("[ \"some\", \"argument\", \"list\" ]", arg->str());

}

}
