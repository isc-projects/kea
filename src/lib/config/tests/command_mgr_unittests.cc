// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <config/command_mgr.h>
#include <cc/command_interpreter.h>

using namespace isc::data;
using namespace isc::config;
using namespace std;

// Test class for Command Manager
class CommandMgrTest : public ::testing::Test {
public:

    /// Default constructor
    CommandMgrTest() {
        handler_name = "";
        handler_params = ElementPtr();
        handler_called = false;

        CommandMgr::instance().deregisterAll();
        CommandMgr::instance().closeCommandSocket();
    }

    /// Default destructor
    ~CommandMgrTest() {
        CommandMgr::instance().deregisterAll();
        CommandMgr::instance().closeCommandSocket();
    }

    /// @brief A simple command handler that always returns an eror
    static ConstElementPtr my_handler(const std::string& name,
                                      const ConstElementPtr& params) {

        handler_name = name;
        handler_params = params;
        handler_called = true;

        return (createAnswer(123, "test error message"));
    }

    /// @brief Name of the command (used in my_handler)
    static std::string handler_name;

    /// @brief Parameters passed to the handler (used in my_handler)
    static ConstElementPtr handler_params;

    /// @brief Indicates whether my_handler was called
    static bool handler_called;
};

/// Name passed to the handler (used in my_handler)
std::string CommandMgrTest::handler_name("");

/// Parameters passed to the handler (used in my_handler)
ConstElementPtr CommandMgrTest::handler_params;

/// Indicates whether my_handler was called
bool CommandMgrTest::handler_called(false);

// Test checks whether the internal command 'list-commands'
// is working properly.
TEST_F(CommandMgrTest, listCommandsEmpty) {

    ConstElementPtr command = createCommand("list-commands");

    ConstElementPtr answer;

    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(command));

    ASSERT_TRUE(answer);

    EXPECT_EQ("{ \"arguments\": [ \"list-commands\" ], \"result\": 0 }",
              answer->str());
}

// Test checks whether calling a bogus command is handled properly.
TEST_F(CommandMgrTest, bogusCommand) {

    ConstElementPtr command = createCommand("no-such-command");

    ConstElementPtr answer;

    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(command));

    // Make sure the status code is non-zero
    ASSERT_TRUE(answer);
    int status_code;
    parseAnswer(status_code, answer);
    EXPECT_EQ(CONTROL_RESULT_ERROR, status_code);
}

// Test checks whether handlers installation is sanitized. In particular,
// whether NULL handler and attempt to install handlers for the same
// command twice are rejected.
TEST_F(CommandMgrTest, handlerInstall) {

    // Check that it's not allowed to install NULL pointer instead of a real
    // command.
    EXPECT_THROW(CommandMgr::instance().registerCommand("my-command",
                 NULL), InvalidCommandHandler);

    // This registration should succeed.
    EXPECT_NO_THROW(CommandMgr::instance().registerCommand("my-command",
                                                           my_handler));

    // Check that it's not possible to install handlers for the same
    // command twice.
    EXPECT_THROW(CommandMgr::instance().registerCommand("my-command",
                 my_handler), InvalidCommandName);
}

// Test checks whether the internal list-commands command is working
// correctly. Also, checks installation and deinstallation of other
// command handlers.
TEST_F(CommandMgrTest, listCommands) {

    // Let's install two custom commands.
    EXPECT_NO_THROW(CommandMgr::instance().registerCommand("make-a-coffee",
                                                           my_handler));
    EXPECT_NO_THROW(CommandMgr::instance().registerCommand("do-the-dishes",
                                                           my_handler));

    // And then run 'list-commands'
    ConstElementPtr list_all = createCommand("list-commands");
    ConstElementPtr answer;

    // Now check that the command is returned by list-commands
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_all));
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": [ \"do-the-dishes\", \"list-commands\", "
              "\"make-a-coffee\" ], \"result\": 0 }", answer->str());

    // Now unregister one command
    EXPECT_NO_THROW(CommandMgr::instance().deregisterCommand("do-the-dishes"));

    // Now check that the command is returned by list-commands
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(list_all));
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": [ \"list-commands\", "
              "\"make-a-coffee\" ], \"result\": 0 }", answer->str());

    // Now test deregistration. It should work the first time.
    EXPECT_NO_THROW(CommandMgr::instance().deregisterCommand("make-a-coffee"));

    // Second time should throw an exception as the handler is no longer there.
    EXPECT_THROW(CommandMgr::instance().deregisterCommand("make-a-coffee"),
                 InvalidCommandName);

    // You can't unistall list-commands as it's the internal handler.
    // It always must be there.
    EXPECT_THROW(CommandMgr::instance().deregisterCommand("list-commands"),
                 InvalidCommandName);

    // Attempt to register a handler for existing command should fail.
    EXPECT_THROW(CommandMgr::instance().registerCommand("list-commands",
                 my_handler), InvalidCommandName);
}

// Test checks whether deregisterAll method uninstalls all handlers,
// except list-commands.
TEST_F(CommandMgrTest, deregisterAll) {

    // Install a couple handlers.
    EXPECT_NO_THROW(CommandMgr::instance().registerCommand("my-command1",
                                                           my_handler));
    EXPECT_NO_THROW(CommandMgr::instance().registerCommand("my-command2",
                                                           my_handler));

    EXPECT_NO_THROW(CommandMgr::instance().deregisterAll());

    ConstElementPtr answer;
    EXPECT_NO_THROW(answer = CommandMgr::instance()
                    .processCommand(createCommand("list-commands")));
    ASSERT_TRUE(answer);
    EXPECT_EQ("{ \"arguments\": [ \"list-commands\" ], \"result\": 0 }",
              answer->str());
}

// Test checks whether a command handler can be installed and then
// runs through processCommand to check that it's indeed called.
TEST_F(CommandMgrTest, processCommand) {

    // Install my handler
    EXPECT_NO_THROW(CommandMgr::instance().registerCommand("my-command",
                                                           my_handler));

    // Now tell CommandMgr to process a command 'my-command' with the
    // specified parameter.
    ElementPtr my_params = Element::fromJSON("[ \"just\", \"some\", \"data\" ]");
    ConstElementPtr command = createCommand("my-command", my_params);
    ConstElementPtr answer;
    EXPECT_NO_THROW(answer = CommandMgr::instance().processCommand(command));

    // There should be an answer.
    ASSERT_TRUE(answer);

    // my_handler remembers all passed parameters and returns status code of 123.
    ConstElementPtr answer_arg;
    int status_code;
    // Check that the returned status code is correct.
    EXPECT_NO_THROW(answer_arg = parseAnswer(status_code, answer));
    EXPECT_EQ(123, status_code);

    // Check that the parameters passed are correct.
    EXPECT_EQ(true, handler_called);
    EXPECT_EQ("my-command", handler_name);
    ASSERT_TRUE(handler_params);
    EXPECT_EQ("[ \"just\", \"some\", \"data\" ]", handler_params->str());
}
