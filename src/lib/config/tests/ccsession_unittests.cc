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

#include <config/tests/fake_session.h>

#include <config/ccsession.h>

#include <fstream>

#include <config/tests/data_def_unittests_config.h>

#include <log/logger_name.h>

using namespace isc::data;
using namespace isc::config;
using namespace isc::cc;
using namespace std;

namespace {
std::string
ccspecfile(const std::string& name) {
    return (std::string(TEST_DATA_PATH) + "/" + name);
}

ElementPtr
el(const std::string& str) {
    return (Element::fromJSON(str));
}

class CCSessionTest : public ::testing::Test {
protected:
    CCSessionTest() : session(el("[]"), el("[]"), el("[]")),
                      root_name(isc::log::getRootLoggerName())
    {
        // upon creation of a ModuleCCSession, the class
        // sends its specification to the config manager.
        // it expects an ok answer back, so everytime we
        // create a ModuleCCSession, we must set an initial
        // ok answer.
        session.getMessages()->add(createAnswer());
    }
    ~CCSessionTest() {
        isc::log::setRootLoggerName(root_name);
    }
    FakeSession session;
    const std::string root_name;
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
    EXPECT_EQ(*arg, *Element::createMap());

    cmd = parseCommand(arg, el("{ \"command\": [ \"my_command\", 1 ] }"));
    EXPECT_EQ("my_command", cmd);
    EXPECT_EQ("1", arg->str());

    parseCommand(arg, el("{ \"command\": [ \"my_command\", [ \"some\", \"argument\", \"list\" ] ] }"));
    EXPECT_EQ("my_command", cmd);
    EXPECT_EQ("[ \"some\", \"argument\", \"list\" ]", arg->str());

}

TEST_F(CCSessionTest, session1) {
    EXPECT_FALSE(session.haveSubscription("Spec1", "*"));
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL,
                         true, false);
    EXPECT_TRUE(session.haveSubscription("Spec1", "*"));

    EXPECT_EQ(1, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"module_name\": \"Spec1\" } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(0, session.getMsgQueue()->size());

    // with this argument, the session should not automatically
    // subscribe to logging config
    EXPECT_FALSE(session.haveSubscription("Logging", "*"));
}

TEST_F(CCSessionTest, session2) {
    EXPECT_FALSE(session.haveSubscription("Spec2", "*"));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, NULL, NULL,
                         true, false);
    EXPECT_TRUE(session.haveSubscription("Spec2", "*"));

    EXPECT_EQ(1, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"commands\": [ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down BIND 10\", \"command_name\": \"shutdown\" } ], \"config_data\": [ { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }, { \"item_default\": 1.1, \"item_name\": \"item2\", \"item_optional\": false, \"item_type\": \"real\" }, { \"item_default\": true, \"item_name\": \"item3\", \"item_optional\": false, \"item_type\": \"boolean\" }, { \"item_default\": \"test\", \"item_name\": \"item4\", \"item_optional\": false, \"item_type\": \"string\" }, { \"item_default\": [ \"a\", \"b\" ], \"item_name\": \"item5\", \"item_optional\": false, \"item_type\": \"list\", \"list_item_spec\": { \"item_default\": \"\", \"item_name\": \"list_element\", \"item_optional\": false, \"item_type\": \"string\" } }, { \"item_default\": {  }, \"item_name\": \"item6\", \"item_optional\": false, \"item_type\": \"map\", \"map_item_spec\": [ { \"item_default\": \"default\", \"item_name\": \"value1\", \"item_optional\": true, \"item_type\": \"string\" }, { \"item_name\": \"value2\", \"item_optional\": true, \"item_type\": \"integer\" } ] } ], \"module_name\": \"Spec2\", \"statistics\": [ { \"item_default\": \"1970-01-01T00:00:00Z\", \"item_description\": \"A dummy date time\", \"item_format\": \"date-time\", \"item_name\": \"dummy_time\", \"item_optional\": false, \"item_title\": \"Dummy Time\", \"item_type\": \"string\" } ] } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(0, session.getMsgQueue()->size());
}

TEST_F(CCSessionTest, session_close) {
    // Test whether ModuleCCSession automatically sends a 'stopping'
    // message when it is destroyed
    ConstElementPtr msg;
    std::string group, to;

    EXPECT_FALSE(session.haveSubscription("Spec2", "*"));
    {
        ModuleCCSession mccs(ccspecfile("spec2.spec"), session, NULL, NULL,
                             true, false);
        EXPECT_TRUE(session.haveSubscription("Spec2", "*"));
        // The initial message is irrelevant for this test 
        // (see session2 test), drop it
        session.getFirstMessage(group, to);
        // Queue should now be empty
        ASSERT_EQ(0, session.getMsgQueue()->size());
    }
    // Destructor should have cause a new message
    ASSERT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"stopping\", "
              "{ \"module_name\": \"Spec2\" } ] }", msg->str());
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
                                   ConstElementPtr arg)
{
    if (command == "good_command") {
        return (createAnswer());
    } else if (command == "command_with_arg") {
        if (arg->contains("number")) {
            if (arg->get("number")->getType() == Element::integer) {
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

    EXPECT_FALSE(session.haveSubscription("Spec2", "*"));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, my_config_handler,
                         my_command_handler, true, false);
    EXPECT_TRUE(session.haveSubscription("Spec2", "*"));

    EXPECT_EQ(2, session.getMsgQueue()->size());
    ConstElementPtr msg;
    std::string group, to;
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"commands\": [ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down BIND 10\", \"command_name\": \"shutdown\" } ], \"config_data\": [ { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }, { \"item_default\": 1.1, \"item_name\": \"item2\", \"item_optional\": false, \"item_type\": \"real\" }, { \"item_default\": true, \"item_name\": \"item3\", \"item_optional\": false, \"item_type\": \"boolean\" }, { \"item_default\": \"test\", \"item_name\": \"item4\", \"item_optional\": false, \"item_type\": \"string\" }, { \"item_default\": [ \"a\", \"b\" ], \"item_name\": \"item5\", \"item_optional\": false, \"item_type\": \"list\", \"list_item_spec\": { \"item_default\": \"\", \"item_name\": \"list_element\", \"item_optional\": false, \"item_type\": \"string\" } }, { \"item_default\": {  }, \"item_name\": \"item6\", \"item_optional\": false, \"item_type\": \"map\", \"map_item_spec\": [ { \"item_default\": \"default\", \"item_name\": \"value1\", \"item_optional\": true, \"item_type\": \"string\" }, { \"item_name\": \"value2\", \"item_optional\": true, \"item_type\": \"integer\" } ] } ], \"module_name\": \"Spec2\", \"statistics\": [ { \"item_default\": \"1970-01-01T00:00:00Z\", \"item_description\": \"A dummy date time\", \"item_format\": \"date-time\", \"item_name\": \"dummy_time\", \"item_optional\": false, \"item_title\": \"Dummy Time\", \"item_type\": \"string\" } ] } ] }", msg->str());
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

    EXPECT_FALSE(session.haveSubscription("Spec29", "*"));
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, my_config_handler,
                         my_command_handler, true, false);
    EXPECT_TRUE(session.haveSubscription("Spec29", "*"));

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
    session.addMessage(el("1"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(0, result);
    session.addMessage(el("{ \"command\": [ \"good_command\" ] }"), "Spec29",
                       "*");

    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0 ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": \"bad_command\" }"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(0, session.getMsgQueue()->size());

    session.addMessage(el("{ \"command\": [ \"bad_command\" ] }"),
                       "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"bad command\" ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"command_with_arg\", {\"number\": 1} ] }"),
                       "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0, 2 ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"command_with_arg\" ] }"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"arg missing\" ] }", msg->str());
    EXPECT_EQ(0, result);

    session.addMessage(el("{ \"command\": [ \"command_with_arg\", \"asdf\" ] }"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 3, \"Error in command validation: args for command command_with_arg is not a map\" ] }", msg->str());
    EXPECT_EQ(0, result);

    mccs.setCommandHandler(NULL);
    session.addMessage(el("{ \"command\": [ \"whatever\" ] }"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 1, \"Command given but no command handler for module\" ] }", msg->str());
    EXPECT_EQ(0, result);
}

// A heuristic workaround for clang++: It doesn't seem to compile the whole
// test, probably due to its length.  Dividing the tests into two separate
// test cases seems to work.
TEST_F(CCSessionTest, checkCommand2) {
    session.getMessages()->add(createAnswer(0, el("{}")));
    EXPECT_FALSE(session.haveSubscription("Spec29", "*"));
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, my_config_handler,
                         my_command_handler, true, false);
    EXPECT_TRUE(session.haveSubscription("Spec29", "*"));
    ConstElementPtr msg;
    std::string group, to;
    // checked above, drop em
    msg = session.getFirstMessage(group, to);
    msg = session.getFirstMessage(group, to);

    EXPECT_EQ(1, mccs.getValue("item1")->intValue());
    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": 2 } ] }"), "Spec29", "*");
    int result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 0 ] }", msg->str());
    EXPECT_EQ(0, result);
    EXPECT_EQ(2, mccs.getValue("item1")->intValue());

    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": \"asdf\" } ] }"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 2, \"Error in config validation: Type mismatch\" ] }", msg->str());
    EXPECT_EQ(0, result);
    EXPECT_EQ(2, mccs.getValue("item1")->intValue());

    session.addMessage(el("{ \"command\": [ \"config_update\", { \"item1\": 5 } ] }"), "Spec29", "*");
    result = mccs.checkCommand();
    EXPECT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"result\": [ 6, \"I do not like the number 5\" ] }", msg->str());
    EXPECT_EQ(0, result);
    EXPECT_EQ(2, mccs.getValue("item1")->intValue());
}

std::string remote_module_name;
int remote_item1(0);
ConstElementPtr remote_config;
ModuleCCSession *remote_mccs(NULL);

void remoteHandler(const std::string& module_name,
                   ConstElementPtr config,
                   const ConfigData&) {
    remote_module_name = module_name;
    remote_item1 = remote_mccs->getRemoteConfigValue("Spec2", "item1")->
        intValue();
    remote_config = config;
}

TEST_F(CCSessionTest, remoteConfig) {
    std::string module_name;
    int item1;
    
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL,
                         false, false);
    EXPECT_TRUE(session.haveSubscription("Spec1", "*"));
    
    // first simply connect, with no config values, and see we get
    // the default
    session.getMessages()->add(createAnswer(0, el("{}")));

    EXPECT_FALSE(session.haveSubscription("Spec2", "*"));
    module_name = mccs.addRemoteConfig(ccspecfile("spec2.spec"));
    EXPECT_EQ("Spec2", module_name);
    EXPECT_TRUE(session.haveSubscription("Spec2", "*"));

    item1 = mccs.getRemoteConfigValue(module_name, "item1")->intValue();
    EXPECT_EQ(1, item1);

    // Remove it and see we get an error asking for a config value
    mccs.removeRemoteConfig(module_name);
    EXPECT_FALSE(session.haveSubscription("Spec2", "*"));
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

    {
        SCOPED_TRACE("With module name");
        // Try adding it with downloading the spec from config manager
        ModuleSpec spec(moduleSpecFromFile(ccspecfile("spec2.spec")));
        session.getMessages()->add(createAnswer(0, spec.getFullSpec()));
        session.getMessages()->add(createAnswer(0, el("{}")));

        EXPECT_NO_THROW(module_name = mccs.addRemoteConfig("Spec2", NULL,
                                                           false));

        const size_t qsize(session.getMsgQueue()->size());
        EXPECT_TRUE(session.getMsgQueue()->get(qsize - 2)->equals(*el(
            "[ \"ConfigManager\", \"*\", { \"command\": ["
            "\"get_module_spec\", { \"module_name\": \"Spec2\" } ] } ]")));
        EXPECT_TRUE(session.getMsgQueue()->get(qsize - 1)->equals(*el(
            "[ \"ConfigManager\", \"*\", { \"command\": [ \"get_config\","
            "{ \"module_name\": \"Spec2\" } ] } ]")));
        EXPECT_EQ("Spec2", module_name);
        // Since we returned an empty local config above, the default value
        // for "item1", which is 1, should be used.
        EXPECT_NO_THROW(item1 =
                        mccs.getRemoteConfigValue(module_name,
                                                  "item1")->intValue());
        EXPECT_EQ(1, item1);

        mccs.removeRemoteConfig(module_name);
    }

    {
        SCOPED_TRACE("With bad module name");
        // It is almost the same as above, but we supply wrong module name.
        // It should fail.
        // Try adding it with downloading the spec from config manager
        ModuleSpec spec(moduleSpecFromFile(ccspecfile("spec2.spec")));
        session.getMessages()->add(createAnswer(0, spec.getFullSpec()));

        EXPECT_THROW(module_name = mccs.addRemoteConfig("Spec1", NULL, false),
                     CCSessionError);
    }

    {
        // Try adding it with a handler.
        // Pass non-default value to see the handler is called after
        // downloading the configuration, not too soon.
        SCOPED_TRACE("With handler");
        session.getMessages()->add(createAnswer(0, el("{ \"item1\": 2 }")));
        remote_mccs = &mccs;
        module_name = mccs.addRemoteConfig(ccspecfile("spec2.spec"),
                                           remoteHandler);
        {
            SCOPED_TRACE("Before update");
            EXPECT_EQ("Spec2", module_name);
            EXPECT_TRUE(session.haveSubscription("Spec2", "*"));
            // Now check the parameters the remote handler stored
            // This also checks it was called
            EXPECT_EQ("Spec2", remote_module_name);
            remote_module_name = "";
            EXPECT_EQ(2, remote_item1);
            remote_item1 = 0;
            if (remote_config) {
                EXPECT_EQ(2, remote_config->get("item1")->intValue());
            } else {
                ADD_FAILURE() << "Remote config not set";
            }
            remote_config.reset();
            // Make sure normal way still works
            item1 = mccs.getRemoteConfigValue(module_name,
                                              "item1")->intValue();
            EXPECT_EQ(2, item1);
        }

        {
            SCOPED_TRACE("After update");
            session.addMessage(el("{ \"command\": [ \"config_update\", "
                                  "{ \"item1\": 3 } ] }"), module_name, "*");
            mccs.checkCommand();
            EXPECT_EQ("Spec2", remote_module_name);
            remote_module_name = "";
            EXPECT_EQ(3, remote_item1);
            remote_item1 = 0;
            if (remote_config) {
                EXPECT_EQ(3, remote_config->get("item1")->intValue());
            } else {
                ADD_FAILURE() << "Remote config not set";
            }
            remote_config.reset();
            // Make sure normal way still works
            item1 = mccs.getRemoteConfigValue(module_name,
                                              "item1")->intValue();
            EXPECT_EQ(3, item1);
        }

        remote_mccs = NULL;
        mccs.removeRemoteConfig(module_name);

        {
            SCOPED_TRACE("When removed");
            // Make sure nothing is called any more
            session.addMessage(el("{ \"command\": [ \"config_update\", "
                                  "{ \"item1\": 4 } ] }"), module_name, "*");
            EXPECT_EQ("", remote_module_name);
            EXPECT_EQ(0, remote_item1);
            EXPECT_FALSE(remote_config);
        }
    }
}

TEST_F(CCSessionTest, ignoreRemoteConfigCommands) {
    // client will ask for config
    session.getMessages()->add(createAnswer(0, el("{  }")));

    EXPECT_FALSE(session.haveSubscription("Spec29", "*"));
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, my_config_handler,
                         my_command_handler, false, false);
    EXPECT_TRUE(session.haveSubscription("Spec29", "*"));

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
    session.addMessage(el("{ \"command\": [ \"good_command\" ] }"), "Spec29", "*");
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

TEST_F(CCSessionTest, initializationFail) {
    // bad specification
    EXPECT_THROW(ModuleCCSession(ccspecfile("spec8.spec"), session,
                                 NULL, NULL), CCSessionInitError);

    // file that does not exist
    EXPECT_THROW(ModuleCCSession(ccspecfile("does_not_exist_spec"),
                                 session, NULL, NULL),
                                 CCSessionInitError);


    session.getMessages()->add(createAnswer(1, el("\"just an error\"")));

    EXPECT_FALSE(session.haveSubscription("Spec29", "*"));
    EXPECT_THROW(ModuleCCSession(ccspecfile("spec29.spec"), session,
                                 my_config_handler, my_command_handler),
                                 CCSessionInitError);
    EXPECT_TRUE(session.haveSubscription("Spec29", "*"));
}

// Test it throws when we try to start it twice (once from the constructor)
TEST_F(CCSessionTest, doubleStartImplicit) {
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, NULL, NULL,
                         true, false);
    EXPECT_THROW(mccs.start(), CCSessionError);
}

// The same, but both starts are explicit
TEST_F(CCSessionTest, doubleStartExplicit) {
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, NULL, NULL,
                         false, false);
    mccs.start();
    EXPECT_THROW(mccs.start(), CCSessionError);
}

// Test we can request synchronous receive before we start the session,
// and check there's the mechanism if we do it after
TEST_F(CCSessionTest, delayedStart) {
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, NULL, NULL,
                         false, false);
    session.getMessages()->add(createAnswer());
    ConstElementPtr env, answer;
    EXPECT_NO_THROW(session.group_recvmsg(env, answer, false, 3));
    mccs.start();
    session.getMessages()->add(createAnswer());
    EXPECT_THROW(session.group_recvmsg(env, answer, false, 3),
                 FakeSession::DoubleRead);
}

TEST_F(CCSessionTest, loggingStart) {
    // provide the logging module spec
    ConstElementPtr log_spec = moduleSpecFromFile(LOG_SPEC_FILE).getFullSpec();
    session.getMessages()->add(createAnswer(0, log_spec));
    // just give an empty config
    session.getMessages()->add(createAnswer(0, el("{}")));
    ModuleCCSession mccs(ccspecfile("spec2.spec"), session, NULL, NULL,
                         true, true);
    EXPECT_TRUE(session.haveSubscription("Logging", "*"));
}

TEST_F(CCSessionTest, loggingStartBadSpec) {
    // provide the logging module spec
    session.getMessages()->add(createAnswer(0, el("{}")));
    // just give an empty config
    session.getMessages()->add(createAnswer(0, el("{}")));
    EXPECT_THROW(new ModuleCCSession(ccspecfile("spec2.spec"), session,
                 NULL, NULL), ModuleSpecError);
    EXPECT_FALSE(session.haveSubscription("Logging", "*"));
}

// Similar to the above, but more implicitly by calling addRemoteConfig().
// We should construct ModuleCCSession with start_immediately being false
// if we need to call addRemoteConfig().
// The correct cases are covered in remoteConfig test.
TEST_F(CCSessionTest, doubleStartWithAddRemoteConfig) {
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, NULL, NULL,
                         true, false);
    session.getMessages()->add(createAnswer(0, el("{}")));
    EXPECT_THROW(mccs.addRemoteConfig(ccspecfile("spec2.spec")),
                 FakeSession::DoubleRead);
}

namespace {
void doRelatedLoggersTest(const char* input, const char* expected) {
    ConstElementPtr all_conf = isc::data::Element::fromJSON(input);
    ConstElementPtr expected_conf = isc::data::Element::fromJSON(expected);
    EXPECT_EQ(*expected_conf, *isc::config::getRelatedLoggers(all_conf));
}
} // end anonymous namespace

TEST(LogConfigTest, relatedLoggersTest) {
    // make sure logger configs for 'other' programs are ignored,
    // and that * is substituted correctly
    // We'll use a root logger name of "b10-test".
    isc::log::setRootLoggerName("b10-test");

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
                         "[ { \"name\": \"b10-test\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"test\" }]",
                         "[ { \"name\": \"b10-test\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"test.somelib\" }]",
                         "[ { \"name\": \"b10-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"other_module.somelib\" },"
                         "  { \"name\": \"test.somelib\" }]",
                         "[ { \"name\": \"b10-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"other_module.somelib\" },"
                         "  { \"name\": \"test\" },"
                         "  { \"name\": \"test.somelib\" }]",
                         "[ { \"name\": \"b10-test\" },"
                         "  { \"name\": \"b10-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"*\" }]",
                         "[ { \"name\": \"b10-test\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"*.somelib\" }]",
                         "[ { \"name\": \"b10-test.somelib\" } ]");
    doRelatedLoggersTest("[ { \"name\": \"*\", \"severity\": \"DEBUG\" },"
                         "  { \"name\": \"test\", \"severity\": \"WARN\"}]",
                         "[ { \"name\": \"b10-test\", \"severity\": \"WARN\"} ]");
    doRelatedLoggersTest("[ { \"name\": \"*\", \"severity\": \"DEBUG\" },"
                         "  { \"name\": \"some_module\", \"severity\": \"WARN\"}]",
                         "[ { \"name\": \"b10-test\", \"severity\": \"DEBUG\"} ]");
    doRelatedLoggersTest("[ { \"name\": \"b10-test\" }]",
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
                         "[ { \"name\": \"b10-test\" } ]");
}

}
