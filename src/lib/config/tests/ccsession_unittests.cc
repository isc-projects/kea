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

// $Id: module_spec_unittests.cc 1321 2010-03-11 10:17:03Z jelte $

#include <config.h>

#include <gtest/gtest.h>

#include <config/tests/fake_session.h>

#include <config/ccsession.h>

#include <fstream>

#include <config/tests/data_def_unittests_config.h>

using namespace isc::data;
using namespace isc::config;
using namespace isc::cc;
using namespace std;

namespace {
std::string
ccspecfile(const std::string name) {
    return (std::string(TEST_DATA_PATH) + "/" + name);
}

ElementPtr
el(const std::string& str) {
    return (Element::fromJSON(str));
}

class CCSessionTest : public ::testing::Test {
protected:
    CCSessionTest() : session(el("[]"), el("[]"), el("[]")) {
        // upon creation of a ModuleCCSession, the class
        // sends its specification to the config manager.
        // it expects an ok answer back, so everytime we
        // create a ModuleCCSession, we must set an initial
        // ok answer.
        session.getMessages()->add(createAnswer());
    }
    ~CCSessionTest() {}
    FakeSession session;
};

TEST_F(CCSessionTest, createAnswer) {
    ConstElementPtr answer;
    answer = createAnswer();
    EXPECT_EQ("{ \"result\": [ 0 ] }", answer->str());
    answer = createAnswer(1, "error");
    EXPECT_EQ("{ \"result\": [ 1, \"error\" ] }", answer->str());

    EXPECT_THROW(createAnswer(1, ElementPtr()), CCSessionError);
    EXPECT_THROW(createAnswer(1, Element::create(1)), CCSessionError);

    ConstElementPtr arg = el("[ \"just\", \"some\", \"data\" ]");
    answer = createAnswer(0, arg);
    EXPECT_EQ("{ \"result\": [ 0, [ \"just\", \"some\", \"data\" ] ] }", answer->str());
}

TEST_F(CCSessionTest, parseAnswer) {
    ConstElementPtr answer;
    ConstElementPtr arg;
    int rcode;

    EXPECT_THROW(parseAnswer(rcode, ElementPtr()), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("1")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("[]")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("{  }")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"something\": 1 }")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": 0 }")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": 1 }")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": [ 1 ] }")), CCSessionError);
    EXPECT_THROW(parseAnswer(rcode, el("{ \"result\": [ 1, 1 ] }")), CCSessionError);
    
    answer = el("{ \"result\": [ 0 ] }");
    arg = parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);
    EXPECT_TRUE(isNull(arg));

    answer = el("{ \"result\": [ 1, \"error\"] }");
    arg = parseAnswer(rcode, answer);
    EXPECT_EQ(1, rcode);
    EXPECT_EQ("error", arg->stringValue());

    answer = el("{ \"result\": [ 0, [ \"just\", \"some\", \"data\" ] ] }");
    arg = parseAnswer(rcode, answer);
    EXPECT_EQ(0, rcode);
    EXPECT_EQ("[ \"just\", \"some\", \"data\" ]", arg->str());
}

TEST_F(CCSessionTest, createCommand) {
    ConstElementPtr command;
    ConstElementPtr arg;

    command = createCommand("my_command");
    ASSERT_EQ("{ \"command\": [ \"my_command\" ] }", command->str());

    arg = el("1");
    command = createCommand("my_command", arg);
    ASSERT_EQ("{ \"command\": [ \"my_command\", 1 ] }", command->str());

    arg = el("[ \"a\", \"b\" ]");
    command = createCommand("my_cmd", arg);
    ASSERT_EQ("{ \"command\": [ \"my_cmd\", [ \"a\", \"b\" ] ] }", command->str());

    arg = el("{ \"a\": \"map\" }");
    command = createCommand("foo", arg);
    ASSERT_EQ("{ \"command\": [ \"foo\", { \"a\": \"map\" } ] }", command->str());
}

TEST_F(CCSessionTest, parseCommand) {
    ConstElementPtr arg;
    std::string cmd;

    // should throw
    EXPECT_THROW(parseCommand(arg, ElementPtr()), CCSessionError);
    EXPECT_THROW(parseCommand(arg, el("1")), CCSessionError);
    EXPECT_THROW(parseCommand(arg, el("{  }")), CCSessionError);
    EXPECT_THROW(parseCommand(arg, el("{ \"not a command\": 1 }")), CCSessionError);
    EXPECT_THROW(parseCommand(arg, el("{ \"command\": 1 }")), CCSessionError);
    EXPECT_THROW(parseCommand(arg, el("{ \"command\": [] }")), CCSessionError);
    EXPECT_THROW(parseCommand(arg, el("{ \"command\": [ 1 ] }")), CCSessionError);

    cmd = parseCommand(arg, el("{ \"command\": [ \"my_command\" ] }"));
    EXPECT_EQ("my_command", cmd);
    EXPECT_TRUE(isNull(arg));

    cmd = parseCommand(arg, el("{ \"command\": [ \"my_command\", 1 ] }"));
    EXPECT_EQ("my_command", cmd);
    EXPECT_EQ("1", arg->str());

    parseCommand(arg, el("{ \"command\": [ \"my_command\", [ \"some\", \"argument\", \"list\" ] ] }"));
    EXPECT_EQ("my_command", cmd);
    EXPECT_EQ("[ \"some\", \"argument\", \"list\" ]", arg->str());

}

TEST_F(CCSessionTest, session1) {
    EXPECT_EQ(false, session.haveSubscription("Spec1", "*"));
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL);
    EXPECT_EQ(true, session.haveSubscription("Spec1", "*"));

    EXPECT_EQ(1, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"module_name\": \"Spec1\" } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(0, session.getMsgQueue()->size());
}

TEST_F(CCSessionTest, session2)
{
    EXPECT_EQ(false, session.haveSubscription("Spec2", "*"));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, NULL, NULL);
    EXPECT_EQ(true, session.haveSubscription("Spec2", "*"));

    EXPECT_EQ(1, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"commands\": [ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down BIND 10\", \"command_name\": \"shutdown\" } ], \"config_data\": [ { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }, { \"item_default\": 1.1, \"item_name\": \"item2\", \"item_optional\": false, \"item_type\": \"real\" }, { \"item_default\": true, \"item_name\": \"item3\", \"item_optional\": false, \"item_type\": \"boolean\" }, { \"item_default\": \"test\", \"item_name\": \"item4\", \"item_optional\": false, \"item_type\": \"string\" }, { \"item_default\": [ \"a\", \"b\" ], \"item_name\": \"item5\", \"item_optional\": false, \"item_type\": \"list\", \"list_item_spec\": { \"item_default\": \"\", \"item_name\": \"list_element\", \"item_optional\": false, \"item_type\": \"string\" } }, { \"item_default\": {  }, \"item_name\": \"item6\", \"item_optional\": false, \"item_type\": \"map\", \"map_item_spec\": [ { \"item_default\": \"default\", \"item_name\": \"value1\", \"item_optional\": true, \"item_type\": \"string\" }, { \"item_name\": \"value2\", \"item_optional\": true, \"item_type\": \"integer\" } ] } ], \"module_name\": \"Spec2\" } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(0, session.getMsgQueue()->size());
}

ConstElementPtr my_config_handler(ConstElementPtr new_config) {
    if (new_config && new_config->contains("item1") &&
        new_config->get("item1")->intValue() == 5) {
        return (createAnswer(6, "I do not like the number 5"));
    }
    return (createAnswer());
}

ConstElementPtr my_command_handler(const std::string& command,
                                   ConstElementPtr arg UNUSED_PARAM)
{
    if (command == "good_command") {
        return (createAnswer());
    } else if (command == "command_with_arg") {
        if (arg) {
            if (arg->getType() == Element::integer) {
                return (createAnswer(0, el("2")));
            } else {
                return (createAnswer(1, "arg bad type"));
            }
        } else {
            return (createAnswer(1, "arg missing"));
        }
    } else {
        return (createAnswer(1, "bad command"));
    }
}

TEST_F(CCSessionTest, session3) {
    // client will ask for config
    session.getMessages()->add(createAnswer(0, el("{}")));

    EXPECT_EQ(false, session.haveSubscription("Spec2", "*"));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, my_config_handler,
                         my_command_handler);
    EXPECT_EQ(true, session.haveSubscription("Spec2", "*"));

    EXPECT_EQ(2, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"commands\": [ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down BIND 10\", \"command_name\": \"shutdown\" } ], \"config_data\": [ { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }, { \"item_default\": 1.1, \"item_name\": \"item2\", \"item_optional\": false, \"item_type\": \"real\" }, { \"item_default\": true, \"item_name\": \"item3\", \"item_optional\": false, \"item_type\": \"boolean\" }, { \"item_default\": \"test\", \"item_name\": \"item4\", \"item_optional\": false, \"item_type\": \"string\" }, { \"item_default\": [ \"a\", \"b\" ], \"item_name\": \"item5\", \"item_optional\": false, \"item_type\": \"list\", \"list_item_spec\": { \"item_default\": \"\", \"item_name\": \"list_element\", \"item_optional\": false, \"item_type\": \"string\" } }, { \"item_default\": {  }, \"item_name\": \"item6\", \"item_optional\": false, \"item_type\": \"map\", \"map_item_spec\": [ { \"item_default\": \"default\", \"item_name\": \"value1\", \"item_optional\": true, \"item_type\": \"string\" }, { \"item_name\": \"value2\", \"item_optional\": true, \"item_type\": \"integer\" } ] } ], \"module_name\": \"Spec2\" } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"get_config\", { \"module_name\": \"Spec2\" } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(0, session.getMsgQueue()->size());
}

TEST_F(CCSessionTest, checkCommand) {
    // client will ask for config
    session.getMessages()->add(createAnswer(0, el("{}")));

    EXPECT_EQ(false, session.haveSubscription("Spec2", "*"));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, my_config_handler,
                         my_command_handler);
    EXPECT_EQ(true, session.haveSubscription("Spec2", "*"));

    EXPECT_EQ(2, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    // checked above, drop em
    msg = session.getFirstMessage(group, to);
    msg = session.getFirstMessage(group, to);

    int result;
    result = mccs.checkCommand();
    EXPECT_EQ(0, result);

    // not a command, should be ignored
    session.addMessage(el("1"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"good_command\" ] }"), "Spec2",
                       "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0 ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": \"bad_command\" }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"Command part in command message missing, empty, or not a list\" ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"bad_command\" ] }"),
                       "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"bad command\" ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"command_with_arg\", 1 ] }"),
                       "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0, 2 ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"command_with_arg\" ] }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"arg missing\" ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"command_with_arg\", \"asdf\" ] }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"arg bad type\" ] }", msg->str());
    EXPECT_EQ(0, result);

    mccs.setCommandHandler(NULL);
    session.addMessage(el("{ \"command\": [ \"whatever\" ] }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"Command given but no command handler for module\" ] }", msg->str());
    EXPECT_EQ(0, result);

    EXPECT_EQ(1, mccs.getValue("item1")->intValue());
    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": 2 } ] }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0 ] }", msg->str());
    EXPECT_EQ(0, result);
    EXPECT_EQ(2, mccs.getValue("item1")->intValue());

    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": \"asdf\" } ] }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 2, \"Error in config validation: Type mismatch\" ] }", msg->str());
    EXPECT_EQ(0, result);
    EXPECT_EQ(2, mccs.getValue("item1")->intValue());

    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": 5 } ] }"), "Spec2", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 6, \"I do not like the number 5\" ] }", msg->str());
    EXPECT_EQ(0, result);
    EXPECT_EQ(2, mccs.getValue("item1")->intValue());
}

TEST_F(CCSessionTest, remoteConfig) {
    std::string module_name;
    int item1;
    
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL);
    EXPECT_EQ(true, session.haveSubscription("Spec1", "*"));
    
    // first simply connect, with no config values, and see we get
    // the default
    session.getMessages()->add(createAnswer(0, el("{}")));

    EXPECT_EQ(false, session.haveSubscription("Spec2", "*"));
    module_name = mccs.addRemoteConfig(ccspecfile("spec2.spec"));
    EXPECT_EQ("Spec2", module_name);
    EXPECT_EQ(true, session.haveSubscription("Spec2", "*"));

    item1 = mccs.getRemoteConfigValue(module_name, "item1")->intValue();
    EXPECT_EQ(1, item1);

    // Remove it and see we get an error asking for a config value
    mccs.removeRemoteConfig(module_name);
    EXPECT_EQ(false, session.haveSubscription("Spec2", "*"));
    EXPECT_THROW(mccs.getRemoteConfigValue(module_name, "item1"), CCSessionError);

    // Now re-add it, with a specific config value, and see we get that
    session.getMessages()->add(createAnswer(0, el("{ \"item1\": 2 }")));
    module_name = mccs.addRemoteConfig(ccspecfile("spec2.spec"));
    item1 = mccs.getRemoteConfigValue(module_name, "item1")->intValue();
    EXPECT_EQ(2, item1);

    // Try a config_update command
    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": 3 } ] }"), module_name, "*");
    mccs.checkCommand();
    item1 = mccs.getRemoteConfigValue(module_name, "item1")->intValue();
    EXPECT_EQ(3, item1);

    // remove, re-add, now with a *bad* config request answer
    mccs.removeRemoteConfig(module_name);
    session.getMessages()->add(el("{}"));
    EXPECT_THROW(mccs.addRemoteConfig(ccspecfile("spec2.spec")), CCSessionError);
    
    session.getMessages()->add(createAnswer(1, "my_error"));
    EXPECT_THROW(mccs.addRemoteConfig(ccspecfile("spec2.spec")), CCSessionError);
    
    session.getMessages()->add(createAnswer());
    EXPECT_THROW(mccs.addRemoteConfig(ccspecfile("spec2.spec")), CCSessionError);
}

TEST_F(CCSessionTest, ignoreRemoteConfigCommands) {
    // client will ask for config
    session.getMessages()->add(createAnswer(0, el("{  }")));

    EXPECT_EQ(false, session.haveSubscription("Spec2", "*"));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, my_config_handler, my_command_handler);
    EXPECT_EQ(true, session.haveSubscription("Spec2", "*"));

    EXPECT_EQ(2, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    // drop the module_spec and config commands
    session.getFirstMessage(group, to);
    session.getFirstMessage(group, to);

    session.getMessages()->add(createAnswer(0, el("{  }")));
    mccs.addRemoteConfig(ccspecfile("spec1.spec"));
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);

    // Check if commands for the module are handled
    session.addMessage(el("{ \"command\": [ \"good_command\" ] }"), "Spec2", "*");
    int result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0 ] }", msg->str());
    EXPECT_EQ(0, result);

    // Check if commands for the other module are ignored
    session.addMessage(el("{ \"command\": [ \"good_command\" ] }"), "Spec1", "*");
    EXPECT_EQ(1, session.getMsgQueue()->size());
    result = mccs.checkCommand();
    EXPECT_EQ(0, session.getMsgQueue()->size());
}

}
