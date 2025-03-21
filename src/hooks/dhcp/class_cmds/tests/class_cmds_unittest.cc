// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the flexible identifier hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <class_cmds.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <hooks/hooks_manager.h>
#include <config/command_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_option_def.h>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::class_cmds;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c ClassCmds.
class ClassCmdsTest : public ::testing::Test {
public:
    /// @brief Constructor
    ClassCmdsTest() {
        CfgMgr::instance().clear();
        CfgMgr::instance().setFamily(AF_INET);
        CommandMgr::instance();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~ClassCmdsTest() {
        CfgMgr::instance().clear();
        LibDHCP::clearRuntimeOptionDefs();
    }

    /// @brief Adds client class to the server's configuration.
    ///
    /// @param name Class name.
    void addClass(const std::string& name, bool template_class = false) {
        try {
            auto cfg = CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
            ClientClassDefPtr def;
            if (template_class) {
                def.reset(new TemplateClientClassDef(name, ExpressionPtr()));
            } else {
                def.reset(new ClientClassDef(name, ExpressionPtr()));
            }
            cfg->addClass(def);
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "failed to add new class " << name
                          << ", reason " << ex.what();
        }
    }

    /// @brief Checks client class from the server's configuration.
    ///
    /// @param name Class name.
    ClientClassDefPtr getClass(const std::string& name) {
        try {
            auto cfg = CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
            return (cfg->findClass(name));
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "failed to get lass " << name
                          << ", reason " << ex.what();
        }
        return (ClientClassDefPtr());
    }

    /// @brief Tests specified command and verifies response
    ///
    /// This method turns command provided as text into JSON struture and then
    /// passes it to the handler under test for processing. It expects that
    /// the handler returns a response which is validated against the
    /// expected values.
    ///
    /// @param cmd_text JSON command to be sent (must be valid JSON)
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    /// @param handler_ptr Pointer to a method of ClassCmds to be tested.
    /// @return full response returned by the command execution.
    ConstElementPtr
    testCommand(const std::string& cmd_txt, const int exp_result,
                                const std::string& exp_txt,
                                void (ClassCmds::*handler_ptr)(CalloutHandle&)) {
        ConstElementPtr command;
        EXPECT_NO_THROW(command = Element::fromJSON(cmd_txt));
        if (!command) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (ConstElementPtr());
        }

        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("command", command);

        ClassCmds class_cmds;
        EXPECT_NO_THROW((class_cmds.*handler_ptr)(*callout_handle));

        ConstElementPtr response;
        EXPECT_NO_THROW(callout_handle->getArgument("response", response));
        if (!response) {
            ADD_FAILURE() << "no response found for the " << cmd_txt << "command";
            return (ConstElementPtr());
        }

        checkAnswer(response, exp_result, exp_txt);

        return (response);
    }

    /// @brief This variant of the test uses const command handler.
    ///
    /// @param cmd_text JSON command to be sent (must be valid JSON)
    /// @param exp_result 0 - success, 1 - error, 2 - ...
    /// @param exp_txt expected text response (optional)
    /// @param handler_ptr Pointer to a method of ClassCmds to be tested.
    /// @return full response returned by the command execution.
    ConstElementPtr
    testCommandConst(const std::string& cmd_txt, const int exp_result,
                     const std::string& exp_txt,
                     void (ClassCmds::*handler_ptr)(CalloutHandle&) const) {
        ConstElementPtr command;
        EXPECT_NO_THROW(command = Element::fromJSON(cmd_txt));
        if (!command) {
            ADD_FAILURE() << cmd_txt << " is not a valid JSON, test broken";
            return (ConstElementPtr());
        }

        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("command", command);

        ClassCmds class_cmds;
        (class_cmds.*handler_ptr)(*callout_handle);

        ConstElementPtr response;
        EXPECT_NO_THROW(callout_handle->getArgument("response", response));
        if (!response) {
            ADD_FAILURE() << "no response found for the " << cmd_txt << "command";
            return (ConstElementPtr());
        }

        checkAnswer(response, exp_result, exp_txt);

        return (response);
    }

    /// @brief Compares the status in the given parse result to a given value.
    ///
    /// @param answer Element set containing an integer response and string
    /// comment.
    /// @param exp_status is an integer against which to compare the status.
    /// @param exp_txt is expected text (not checked if "")
    ///
    void checkAnswer(isc::data::ConstElementPtr answer,
                     int exp_status,
                     string exp_txt = "") {
        int rcode = 0;
        isc::data::ConstElementPtr comment;
        comment = isc::config::parseAnswer(rcode, answer);

        if (rcode != exp_status) {
            ADD_FAILURE() << "Expected status code " << exp_status
                          << " but received " << rcode << ", comment: "
                          << (comment ? comment->str() : "(none)");
        }

        // Ok, parseAnswer interface is weird. If there are no arguments,
        // it returns content of text. But if there is an argument,
        // it returns the argument and it's not possible to retrieve
        // "text" (i.e. comment).
        if (comment->getType() != Element::string) {
            comment = answer->get("text");
        }

        if (!exp_txt.empty()) {
            EXPECT_EQ(exp_txt, comment->stringValue());
        }
    }

    /// List of libraries to be/being loaded (usually just one)
    HookLibsCollection libraries_;
};

// class-add

// Checks that class-add can handle a situation when the query is
// broken (no arguments).
TEST_F(ClassCmdsTest, ClassAddNoArgs) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\"\n"
        "}";
    string exp_rsp = "invalid command 'class-add': no arguments specified";

    // Arguments entry is required.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (arguments is not a map).
TEST_F(ClassCmdsTest, ClassAddArgsNotMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": [\n"
        "    ]\n"
        "}";
    string exp_rsp = "invalid command 'class-add': expected 'arguments' to be a map, got list instead";

    // Arguments entry must be a map.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (no parameters at all).
TEST_F(ClassCmdsTest, ClassAddNoParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid command 'class-add': 'arguments' is empty";

    // Parameters must be the client-class list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (extra parameters).
TEST_F(ClassCmdsTest, ClassAddExtraParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [ ],\n"
        "        \"bogus\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of arguments 2 for the 'class-add' command. Expecting "
        "'client-classes' list";

    // Parameters must be the client-class list only.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (no client-classes).
TEST_F(ClassCmdsTest, ClassAddNoClasses) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-class\": [ ]\n"
        "    }\n"
        "}";
    string exp_rsp = "missing 'client-classes' argument for the 'class-add' command";

    // Parameters must be the client-class list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (client-classes not a list).
TEST_F(ClassCmdsTest, ClassAddClassesNotList) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": \"foo\"\n"
        "    }\n"
        "}";
    string exp_rsp = "'client-classes' argument specified for the 'class-add' command is not a list";

    // Client-classes must be a list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (client-classes empty).
TEST_F(ClassCmdsTest, ClassAddClassesEmpty) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [ ]\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of classes specified for the 'class-add' command. "
        "Expected one class";

    // Client-classes must have one entry.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (class is not a map).
TEST_F(ClassCmdsTest, ClassAddClassNotMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            \"foobar\"\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid class definition specified for the 'class-add' command. Expected a map";

    // Class entry must be a map.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add can handle a situation when the query is
// broken (duplicate class).
TEST_F(ClassCmdsTest, ClassAddClassDuplicate) {
    // Add the foobar class.
    addClass("foobar");

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "Can't add class: Client Class: foobar has already been defined";

    // Parsing can fail for many reasons already checked so one is enough.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Checks that class-add returns an error when unsupported class parameter
// have been specified.
TEST_F(ClassCmdsTest, ClassAddUnsupportedClassParameter) {
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"bogus-parameter\": 1\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "unsupported client class parameter 'bogus-parameter'";

    // Parsing can fail for many reasons already checked so one is enough.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::addClass);
}

// Check that a well formed class including an option and option definition
// can be added.
TEST_F(ClassCmdsTest, ClassAdd) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"option-def\": [\n"
        "                    {\n"
        "                        \"name\": \"foo\","
        "                        \"code\": 224,\n"
        "                        \"type\": \"uint16\"\n"
        "                    }\n"
        "                ],\n"
        "                \"option-data\": [\n"
        "                    {\n"
        "                        \"name\": \"domain-name-servers\",\n"
        "                        \"data\": \"192.0.2.3\"\n"
        "                    }\n"
        "                ]\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' added";

    // Should succeed.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp, &ClassCmds::addClass);

    // Class should be in the configuration.
    const ClientClassDefPtr& def = getClass("foobar");
    ASSERT_TRUE(def);
    EXPECT_EQ("foobar", def->getName());

    // Verify that the option definition has been added.
    auto cfg_option_def = def->getCfgOptionDef();
    ASSERT_TRUE(cfg_option_def);
    auto option_def = cfg_option_def->get(DHCP4_OPTION_SPACE, 224);
    ASSERT_TRUE(option_def);
    EXPECT_EQ(224, option_def->getCode());

    // Verify that option has been added.
    auto cfg_option = def->getCfgOption();
    ASSERT_TRUE(cfg_option);
    auto option = cfg_option->get(DHCP4_OPTION_SPACE, DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(option.option_);
    EXPECT_EQ(DHO_DOMAIN_NAME_SERVERS, option.option_->getType());
}

// Check that a well formed template class including an option and option definition
// can be added.
TEST_F(ClassCmdsTest, TemplateClassAdd) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-add\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"template-test\": \"pkt.iface\",\n"
        "                \"option-def\": [\n"
        "                    {\n"
        "                        \"name\": \"foo\","
        "                        \"code\": 224,\n"
        "                        \"type\": \"uint16\"\n"
        "                    }\n"
        "                ],\n"
        "                \"option-data\": [\n"
        "                    {\n"
        "                        \"name\": \"domain-name-servers\",\n"
        "                        \"data\": \"192.0.2.3\"\n"
        "                    }\n"
        "                ]\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' added";

    // Should succeed.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp, &ClassCmds::addClass);

    // Class should be in the configuration.
    const ClientClassDefPtr& def = getClass("foobar");
    ASSERT_TRUE(def);
    ASSERT_TRUE(dynamic_cast<TemplateClientClassDef*>(def.get()));
    EXPECT_EQ("foobar", def->getName());

    // Verify that the option definition has been added.
    auto cfg_option_def = def->getCfgOptionDef();
    ASSERT_TRUE(cfg_option_def);
    auto option_def = cfg_option_def->get(DHCP4_OPTION_SPACE, 224);
    ASSERT_TRUE(option_def);
    EXPECT_EQ(224, option_def->getCode());

    // Verify that option has been added.
    auto cfg_option = def->getCfgOption();
    ASSERT_TRUE(cfg_option);
    auto option = cfg_option->get(DHCP4_OPTION_SPACE, DHO_DOMAIN_NAME_SERVERS);
    ASSERT_TRUE(option.option_);
    EXPECT_EQ(DHO_DOMAIN_NAME_SERVERS, option.option_->getType());
}

// class-get

// Checks that class-get can handle a situation when the query is
// broken (no arguments).
TEST_F(ClassCmdsTest, ClassGetNoArgs) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\"\n"
        "}";
    string exp_rsp = "invalid command 'class-get': no arguments specified";

    // Arguments entry is required.
    testCommandConst(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get can handle a situation when the query is
// broken (arguments is not a map).
TEST_F(ClassCmdsTest, ClassGetArgsNotMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": [\n"
        "    ]\n"
        "}";
    string exp_rsp = "invalid command 'class-get': expected 'arguments' to be a map, got list instead";

    // Arguments entry must be a map.
    testCommandConst(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get can handle a situation when the query is
// broken (no parameters at all).
TEST_F(ClassCmdsTest, ClassGetNoParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "invalid command 'class-get': 'arguments' is empty";

    // Parameters must be the name string.
    testCommandConst(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get can handle a situation when the query is
// broken (extra parameters).
TEST_F(ClassCmdsTest, ClassGetExtraParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\",\n"
        "        \"bogus\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of arguments 2 for the 'class-get' command. "
        "Expecting 'name' string";

    // Parameters must be the name string only.
    testCommandConst(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get can handle a situation when the query is
// broken (no name).
TEST_F(ClassCmdsTest, ClassGetNoName) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "        \"bogus\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "missing 'name' argument for the 'class-get' command";

    // Parameters must be the name string.
    testCommandConst(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get can handle a situation when the query is
// broken (name not a string).
TEST_F(ClassCmdsTest, ClassGetNameNotString) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "        \"name\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "'name' argument specified for the 'class-get' command is not a string";

    // Name must be a string.
    testCommandConst(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get(name) can handle a situation when
// the query is correctly formed, but the class is not there.
TEST_F(ClassCmdsTest, ClassGetNotFound) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' not found";

    testCommandConst(cmd, CONTROL_RESULT_EMPTY, exp_rsp, &ClassCmds::getClass);
}

// Checks that class-get(name) can handle a situation when
// the query is correctly formed and the class is returned.
TEST_F(ClassCmdsTest, ClassGet) {
    // Add the foobar class to the configuration.
    addClass("foobar");

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' definition returned";

    // Should have found it.
    ConstElementPtr rsp = testCommandConst(cmd, CONTROL_RESULT_SUCCESS, exp_rsp,
                                           &ClassCmds::getClass);

    // Now check that the class parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr defs = args->get("client-classes");
    ASSERT_TRUE(defs);
    ConstElementPtr def = defs->get(0);
    ASSERT_TRUE(def);
    ASSERT_TRUE(def->get("name"));
    EXPECT_EQ("foobar", def->get("name")->stringValue());
}

// Checks that class-get(name) can handle a situation when
// the query is correctly formed and the template class is returned.
TEST_F(ClassCmdsTest, TemplateClassGet) {
    // Add the foobar class to the configuration.
    addClass("foobar", true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-get\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' definition returned";

    // Should have found it.
    ConstElementPtr rsp = testCommandConst(cmd, CONTROL_RESULT_SUCCESS, exp_rsp,
                                           &ClassCmds::getClass);

    // Now check that the class parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr defs = args->get("client-classes");
    ASSERT_TRUE(defs);
    ConstElementPtr def = defs->get(0);
    ASSERT_TRUE(def);
    ASSERT_TRUE(def->get("name"));
    EXPECT_EQ("foobar", def->get("name")->stringValue());
    ConstElementPtr template_test;
    ASSERT_NO_THROW(template_test = def->get("template-test"));
    ASSERT_TRUE(template_test);
    ASSERT_EQ(template_test->stringValue(), "");
}

// class-list

// Checks that class-list can handle a situation when no classes are
// configured.
TEST_F(ClassCmdsTest, ClassListEmpty) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-list\"\n"
        "}";
    string exp_rsp = "0 classes found";

    // class-list always succeeds.
    ConstElementPtr rsp = testCommandConst(cmd, CONTROL_RESULT_EMPTY, exp_rsp,
                                           &ClassCmds::getClassList);

    // Now check that the empty class list were returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr defs = args->get("client-classes");
    ASSERT_TRUE(defs);
    EXPECT_EQ(0, defs->size());
}

// Checks that class-list can handle a situation when one class is
// configured.
TEST_F(ClassCmdsTest, ClassListOne) {
    // Add the foo class.
    addClass("foo");

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-list\"\n"
        "}";
    string exp_rsp = "1 class found";

    // class-list always succeeds.
    ConstElementPtr rsp = testCommandConst(cmd, CONTROL_RESULT_SUCCESS, exp_rsp,
                                           &ClassCmds::getClassList);

    // Now check that the class list with foo were returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr defs = args->get("client-classes");
    ASSERT_TRUE(defs);
    ASSERT_GE(1, defs->size());
    EXPECT_EQ(1, defs->size());
    ConstElementPtr def = defs->get(0);
    ASSERT_TRUE(def);
    ASSERT_TRUE(def->get("name"));
    EXPECT_EQ("foo", def->get("name")->stringValue());
}

// Checks that class-list can handle a situation when two classes are
// configured.
TEST_F(ClassCmdsTest, ClassListTwo) {
    // Add the foo and bar classes.
    addClass("foo");
    addClass("bar", true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-list\"\n"
        "}";
    string exp_rsp = "2 classes found";

    // class-list always succeeds.
    ConstElementPtr rsp = testCommandConst(cmd, CONTROL_RESULT_SUCCESS, exp_rsp,
                                           &ClassCmds::getClassList);

    // Now check that the class list with foo were returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ConstElementPtr defs = args->get("client-classes");
    ASSERT_TRUE(defs);
    ASSERT_GE(2, defs->size());
    EXPECT_EQ(2, defs->size());
    ConstElementPtr def = defs->get(0);
    ASSERT_TRUE(def);
    ASSERT_TRUE(def->get("name"));
    EXPECT_EQ("foo", def->get("name")->stringValue());
    def = defs->get(1);
    ASSERT_TRUE(def);
    ASSERT_TRUE(def->get("name"));
    EXPECT_EQ("bar", def->get("name")->stringValue());
}

// class-update

// Checks that class-update can handle a situation when the query is
// broken (no arguments).
TEST_F(ClassCmdsTest, ClassUpdateNoArgs) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\"\n"
        "}";
    string exp_rsp = "invalid command 'class-update': no arguments specified";

    // Arguments entry is required.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (arguments is not a map).
TEST_F(ClassCmdsTest, ClassUpdateArgsNotMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": [\n"
        "    ]\n"
        "}";
    string exp_rsp = "invalid command 'class-update': expected 'arguments' to be a map, got list instead";

    // Arguments entry must be a map.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (no parameters at all).
TEST_F(ClassCmdsTest, ClassUpdateNoParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid command 'class-update': 'arguments' is empty";

    // Parameters must be the client-class list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (mandatory client-classes defined, but specifies a list with one entry
// which is an empty map).
TEST_F(ClassCmdsTest, ClassUpdateEmptyEntryInMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [{}]\n"
        "    }\n"
        "}";
    string exp_rsp = "the first class definition is missing a mandatory 'name' parameter";

    // Parameters must be the client-class list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (mandatory client-classes defined, but specifies an empty map).
TEST_F(ClassCmdsTest, ClassUpdateEmptyList) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": []\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of classes specified for the 'class-update'"
        " command. Expected one class";

    // Parameters must be the client-class list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (extra parameters).
TEST_F(ClassCmdsTest, ClassUpdateExtraParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [ ],\n"
        "        \"bogus\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of arguments 2 for the 'class-update' command. Expecting "
        "'client-classes' list";

    // Parameters must be the client-class list only.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (no client-classes).
TEST_F(ClassCmdsTest, ClassUpdateNoClasses) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-class\": [ ]\n"
        "    }\n"
        "}";
    string exp_rsp = "missing 'client-classes' argument for the 'class-update' command";

    // Parameters must be the client-class list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (client-classes not a list).
TEST_F(ClassCmdsTest, ClassUpdateClassesNotList) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": \"foo\"\n"
        "    }\n"
        "}";
    string exp_rsp = "'client-classes' argument specified for the 'class-update' command is not a list";

    // Client-classes must be a list.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (client-classes empty).
TEST_F(ClassCmdsTest, ClassUpdateClassesEmpty) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [ ]\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of classes specified for the 'class-update' command. "
        "Expected one class";

    // Client-classes must have one entry.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when the query is
// broken (class is not a map).
TEST_F(ClassCmdsTest, ClassUpdateClassNotMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            \"foobar\"\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid class definition specified for the 'class-update' command. Expected a map";

    // Class entry must be a map.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update can handle a situation when
// the query is correctly formed, but the class is not there.
TEST_F(ClassCmdsTest, ClassUpdatetNotFound) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' is not found";

    // Update requires the class was already configured.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp, &ClassCmds::updateClass);
}

// Check that a simple, well formed class can be updated.
TEST_F(ClassCmdsTest, ClassUpdate) {
    // Add the foobar class to the configuration.
    addClass("foobar");

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"server-hostname\": \"my-server\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' updated";

    // Should succeed.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp, &ClassCmds::updateClass);

    // Class should be in the configuration.
    const ClientClassDefPtr& def = getClass("foobar");
    ASSERT_TRUE(def);
    EXPECT_EQ("foobar", def->getName());
    EXPECT_EQ("my-server", def->getSname());
}

// Check that a simple, well formed template class can be updated.
TEST_F(ClassCmdsTest, TemplateClassUpdate) {
    // Add the foobar class to the configuration.
    addClass("foobar", true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"template-test\": \"''\","
        "                \"server-hostname\": \"my-server\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' updated";

    // Should succeed.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp, &ClassCmds::updateClass);

    // Class should be in the configuration.
    const ClientClassDefPtr& def = getClass("foobar");
    ASSERT_TRUE(def);
    ASSERT_TRUE(dynamic_cast<TemplateClientClassDef*>(def.get()));
    EXPECT_EQ("foobar", def->getName());
    EXPECT_EQ("my-server", def->getSname());
}

// Check that a simple, well formed class cannot be updated when
// the update changes the KNOWN/UNKNOWN dependency.
TEST_F(ClassCmdsTest, ClassUpdateBad) {
    // Add the foobar class to the configuration.
    addClass("foobar");

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"test\": \"member('KNOWN')\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "modification of the class 'foobar' "
        "would affect its dependency on the KNOWN and/or UNKNOWN "
        "built-in classes. Such modification is not allowed "
        "because there may be other classes depending on those "
        "built-ins via the updated class";

    // Depends on KNOWN/UNKNOWN makes it to fail.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// Checks that class-update returns an error when unsupported class parameter
// have been specified.
TEST_F(ClassCmdsTest, ClassUpdateUnsupportedClassParameter) {
    // Add the foobar class to the configuration.
    addClass("foobar");

    string cmd =
        "{\n"
        "    \"command\": \"class-update\",\n"
        "    \"arguments\": {\n"
        "        \"client-classes\": [\n"
        "            {\n"
        "                \"name\": \"foobar\",\n"
        "                \"bogus-parameter\": 1\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}";
    string exp_rsp = "unsupported client class parameter 'bogus-parameter'";

    // Parsing can fail for many reasons already checked so one is enough.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::updateClass);
}

// class-del

// Checks that class-del can handle a situation when the query is
// broken (no arguments).
TEST_F(ClassCmdsTest, ClassDelNoArgs) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\"\n"
        "}";
    string exp_rsp = "invalid command 'class-del': no arguments specified";

    // Arguments entry is required.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del can handle a situation when the query is
// broken (arguments is not a map).
TEST_F(ClassCmdsTest, ClassDelArgsNotMap) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": [\n"
        "    ]\n"
        "}";
    string exp_rsp = "invalid command 'class-del': expected 'arguments' to be a map, got list instead";

    // Arguments entry must be a map.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del can handle a situation when the query is
// broken (no parameters at all).
TEST_F(ClassCmdsTest, ClassDelNoParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "invalid command 'class-del': 'arguments' is empty";

    // Parameters must be the name string.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del can handle a situation when the query is
// broken (extra parameters).
TEST_F(ClassCmdsTest, ClassDelExtraParams) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\",\n"
        "        \"bogus\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "invalid number of arguments 2 for the 'class-del' command. "
        "Expecting 'name' string";

    // Parameters must be the name string only.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del can handle a situation when the query is
// broken (no name).
TEST_F(ClassCmdsTest, ClassDelNoName) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"bogus\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "missing 'name' argument for the 'class-del' command";

    // Parameters must be the name string.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del can handle a situation when the query is
// broken (name not a string).
TEST_F(ClassCmdsTest, ClassDelNameNotString) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "'name' argument specified for the 'class-del' command is not a string";

    // Name must be a string.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del(name) can handle a situation when
// the query is correctly formed, but the class is not there.
TEST_F(ClassCmdsTest, ClassDelNotFound) {
    // Send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' not found";

    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del(name) can handle a situation when
// the query is correctly formed and the class is deleted.
TEST_F(ClassCmdsTest, ClassDel) {
    // Add the class foobar.
    addClass("foobar");

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' deleted";

    // Should succeed, class should del deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del(name) can handle a situation when
// the query is correctly formed and the template class is deleted.
TEST_F(ClassCmdsTest, TemplateClassDel) {
    // Add the class foobar.
    addClass("foobar", true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foobar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foobar' deleted";

    // Should succeed, class should del deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del(name) can handle a situation when
// the query is correctly formed but the class is referenced
// so cannot be deleted.
TEST_F(ClassCmdsTest, ClassDelInUse) {
    // Add the class foo.
    addClass("foo");

    // Add the class bar using foo.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    ExpressionPtr expr(new Expression());
    TokenPtr token(new TokenMember("foo"));
    expr->push_back(token);
    ClientClassDefPtr def(new ClientClassDef("bar", expr));
    EXPECT_NO_THROW(cfg->addClass(def));

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foo\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foo' is used by class 'bar'";

    // Dangling references is detected.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

// Checks that class-del(name) can handle a situation when
// the query is correctly formed but the template class is referenced
// so cannot be deleted.
TEST_F(ClassCmdsTest, TemplateClassDelInUse) {
    // Add the class foo.
    addClass("foo", true);

    // Add the class bar using foo.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    ExpressionPtr expr(new Expression());
    TokenPtr token(new TokenMember("foo"));
    expr->push_back(token);
    ClientClassDefPtr def(new ClientClassDef("bar", expr));
    EXPECT_NO_THROW(cfg->addClass(def));

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"class-del\",\n"
        "    \"arguments\": {"
        "        \"name\": \"foo\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Class 'foo' is used by class 'bar'";

    // Dangling references is detected.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp, &ClassCmds::delClass);
}

} // end of anonymous namespace
