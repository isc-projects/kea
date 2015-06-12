// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/unittests/test_exceptions.h>

#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>

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
        // it expects an ok answer back, so every time we
        // create a ModuleCCSession, we must set an initial
        // ok answer.
        session.getMessages()->add(createAnswer());
    }
    ConstElementPtr rpcCheck(const std::string& reply) {
        ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL,
                             false, false);
        // Prepare the answer beforehand, it'll block until it gets one
        const ConstElementPtr reply_el(el(reply));
        session.getMessages()->add(reply_el);
        const ConstElementPtr
            result(mccs.rpcCall("test", "Spec2",
                                el("{\"param1\": \"Param 1\","
                                   "\"param2\": \"Param 2\"}")));
        const ConstElementPtr
            request(el("[\"Spec2\", \"*\", {"
                       "  \"command\": [\"test\", {"
                       "    \"param1\": \"Param 1\","
                       "    \"param2\": \"Param 2\""
                       "}]}, -1, true]"));
        // The 0th one is from the initialization, to ConfigManager.
        // our is the 1st.
        EXPECT_TRUE(request->equals(*session.getMsgQueue()->get(1))) <<
            session.getMsgQueue()->get(1)->toWire();
        return (result);
    }
    ~CCSessionTest() {
        isc::log::setRootLoggerName(root_name);
    }
    FakeSession session;
    const std::string root_name;
};

void
notificationCallback(std::vector<std::string>* called,
                     const std::string& id, const std::string& notification,
                     const ConstElementPtr& params)
{
    called->push_back(id);
    EXPECT_EQ("event", notification);
    EXPECT_TRUE(el("{\"param\": true}")->equals(*params));
}

TEST_F(CCSessionTest, receiveNotification) {
    // Not subscribed to the group yet
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL,
                         false, false);
    EXPECT_FALSE(session.haveSubscription("notifications/group", "*"));
    std::vector<std::string> called;
    // Subscribe to the notification. Twice.
    const ModuleCCSession::NotificationID& first =
        mccs.subscribeNotification("group", boost::bind(&notificationCallback,
                                                        &called, "first",
                                                        _1, _2));
    const ModuleCCSession::NotificationID& second =
        mccs.subscribeNotification("group", boost::bind(&notificationCallback,
                                                        &called, "second",
                                                        _1, _2));
    EXPECT_TRUE(session.haveSubscription("notifications/group", "*"));
    EXPECT_TRUE(called.empty());
    // Send the notification
    const isc::data::ConstElementPtr msg = el("{"
        "       \"notification\": ["
        "           \"event\", {"
        "               \"param\": true"
        "           }"
        "       ]"
        "   }");
    session.addMessage(msg, "notifications/group", "*");
    mccs.checkCommand();
    ASSERT_EQ(2, called.size());
    EXPECT_EQ("first", called[0]);
    EXPECT_EQ("second", called[1]);
    called.clear();
    // Unsubscribe one of them
    mccs.unsubscribeNotification(first);
    // We are still subscribed to the group and handle the requests
    EXPECT_TRUE(session.haveSubscription("notifications/group", "*"));
    // Send the notification
    session.addMessage(msg, "notifications/group", "*");
    mccs.checkCommand();
    ASSERT_EQ(1, called.size());
    EXPECT_EQ("second", called[0]);
    // Unsubscribe the other one too. That should cancel the upstream
    // subscription
    mccs.unsubscribeNotification(second);
    EXPECT_FALSE(session.haveSubscription("notifications/group", "*"));
    // Nothing crashes if out of sync notification comes unexpected
    session.addMessage(msg, "notifications/group", "*");
    EXPECT_NO_THROW(mccs.checkCommand());
}

// Test we can send an RPC (command) and get an answer. The answer is success
// in this case.
TEST_F(CCSessionTest, rpcCallSuccess) {
    const ConstElementPtr result =
        rpcCheck("{\"result\": [0, {\"Hello\": \"a\"}]}");
    EXPECT_TRUE(el("{\"Hello\": \"a\"}")->equals(*result));
}

// Test success of RPC, but the answer is empty (eg. a void function on the
// remote side).
TEST_F(CCSessionTest, rpcCallSuccessNone) {
    EXPECT_FALSE(rpcCheck("{\"result\": [0]}"));
}

// Test it successfully raises CCSessionError if the answer is malformed.
TEST_F(CCSessionTest, rpcCallMalformedAnswer) {
    EXPECT_THROW_WITH(rpcCheck("[\"Nonsense\"]"), CCSessionError,
                      "No result part in answer message");
}

// Test it raises exception when the remote side reports an error
TEST_F(CCSessionTest, rpcCallError) {
  EXPECT_THROW_WITH(rpcCheck("{\"result\": [1, \"Error\"]}"), RPCError,
		    *createAnswer(1, "Error"));
}

// Test it raises exception when the remote side doesn't exist
TEST_F(CCSessionTest, rpcNoRecpt) {
    EXPECT_THROW_WITH(rpcCheck("{\"result\": [-1, \"Error\"]}"),
                      RPCRecipientMissing, *createAnswer(-1, "Error"));
}

// Test sending a notification
TEST_F(CCSessionTest, notify) {
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL, false,
                         false);
    mccs.notify("group", "event", el("{\"param\": true}"));
    const ConstElementPtr notification(el(
        "["
        "   \"notifications/group\","
        "   \"*\","
        "   {"
        "       \"notification\": ["
        "           \"event\", {"
        "               \"param\": true"
        "           }"
        "       ]"
        "   },"
        "   -1"
        "]"));
    EXPECT_TRUE(notification->equals(*session.getMsgQueue()->get(1))) <<
            session.getMsgQueue()->get(1)->toWire();
}

// Test sending a notification
TEST_F(CCSessionTest, notifyNoParams) {
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL, false,
                         false);
    mccs.notify("group", "event");
    const ConstElementPtr notification(el(
        "["
        "   \"notifications/group\","
        "   \"*\","
        "   {"
        "       \"notification\": [\"event\"]"
        "   },"
        "   -1"
        "]"));
    EXPECT_TRUE(notification->equals(*session.getMsgQueue()->get(1))) <<
            session.getMsgQueue()->get(1)->toWire();
}

// Try to subscribe and unsubscribe once again
TEST_F(CCSessionTest, subscribe) {
    ModuleCCSession mccs(ccspecfile("spec1.spec"), session, NULL, NULL, false,
                         false);
    EXPECT_FALSE(session.haveSubscription("A group", "*"));
    mccs.subscribe("A group");
    EXPECT_TRUE(session.haveSubscription("A group", "*"));
    mccs.unsubscribe("A group");
    EXPECT_FALSE(session.haveSubscription("A group", "*"));
}

TEST_F(CCSessionTest, createAnswer) {
    ConstElementPtr answer;
    answer = createAnswer();
    EXPECT_EQ("{ \"result\": [ 0 ] }", answer->str());
    answer = createAnswer(1, "error");
    EXPECT_EQ("{ \"result\": [ 1, \"error\" ] }", answer->str());

    EXPECT_THROW_WITH(createAnswer(1, ElementPtr()), CCSessionError,
                      "Bad or no argument for rcode != 0");
    EXPECT_THROW_WITH(createAnswer(1, Element::create(1)), CCSessionError,
                      "Bad or no argument for rcode != 0");

    ConstElementPtr arg = el("[ \"just\", \"some\", \"data\" ]");
    answer = createAnswer(0, arg);
    EXPECT_EQ("{ \"result\": [ 0, [ \"just\", \"some\", \"data\" ] ] }", answer->str());
}

TEST_F(CCSessionTest, parseAnswer) {
    ConstElementPtr answer;
    ConstElementPtr arg;
    int rcode;

    EXPECT_THROW_WITH(parseAnswer(rcode, ElementPtr()), CCSessionError,
                      "No result part in answer message");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("1")), CCSessionError,
                      "No result part in answer message");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("[]")), CCSessionError,
                      "No result part in answer message");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("{  }")), CCSessionError,
                      "No result part in answer message");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("{ \"something\": 1 }")),
                      CCSessionError,
                      "No result part in answer message");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("{ \"result\": 0 }")),
                      CCSessionError,
                      "Result element in answer message is not a list");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("{ \"result\": 1 }")),
                      CCSessionError,
                      "Result element in answer message is not a list");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("{ \"result\": [ 1 ] }")),
                      CCSessionError,
                      "Result with rcode != 0 does not have "
                      "an error description");
    EXPECT_THROW_WITH(parseAnswer(rcode, el("{ \"result\": [ 1, 1 ] }")),
                      CCSessionError,
                      "Error description in result with rcode != 0 "
                      "is not a string");
    
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
    EXPECT_THROW_WITH(parseCommand(arg, ElementPtr()), CCSessionError,
                      "Command Element empty or not a map with \"command\"");
    EXPECT_THROW_WITH(parseCommand(arg, el("1")), CCSessionError,
                      "Command Element empty or not a map with \"command\"");
    EXPECT_THROW_WITH(parseCommand(arg, el("{  }")), CCSessionError,
                      "Command Element empty or not a map with \"command\"");
    EXPECT_THROW_WITH(parseCommand(arg, el("{ \"not a command\": 1 }")),
                      CCSessionError,
                      "Command Element empty or not a map with \"command\"");
    EXPECT_THROW_WITH(parseCommand(arg, el("{ \"command\": 1 }")),
                      CCSessionError,
                      "Command part in command message missing, "
                      "empty, or not a list");
    EXPECT_THROW_WITH(parseCommand(arg, el("{ \"command\": [] }")),
                      CCSessionError,
                      "Command part in command message missing, "
                      "empty, or not a list");
    EXPECT_THROW_WITH(parseCommand(arg, el("{ \"command\": [ 1 ] }")),
                      CCSessionError,
                      "Command part in command message missing, "
                      "empty, or not a list");

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
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"commands\": [ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down Kea\", \"command_name\": \"shutdown\" } ], \"config_data\": [ { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }, { \"item_default\": 1.1, \"item_name\": \"item2\", \"item_optional\": false, \"item_type\": \"real\" }, { \"item_default\": true, \"item_name\": \"item3\", \"item_optional\": false, \"item_type\": \"boolean\" }, { \"item_default\": \"test\", \"item_name\": \"item4\", \"item_optional\": false, \"item_type\": \"string\" }, { \"item_default\": [ \"a\", \"b\" ], \"item_name\": \"item5\", \"item_optional\": false, \"item_type\": \"list\", \"list_item_spec\": { \"item_default\": \"\", \"item_name\": \"list_element\", \"item_optional\": false, \"item_type\": \"string\" } }, { \"item_default\": {  }, \"item_name\": \"item6\", \"item_optional\": false, \"item_type\": \"map\", \"map_item_spec\": [ { \"item_default\": \"default\", \"item_name\": \"value1\", \"item_optional\": true, \"item_type\": \"string\" }, { \"item_name\": \"value2\", \"item_optional\": true, \"item_type\": \"integer\" } ] } ], \"module_name\": \"Spec2\", \"statistics\": [ { \"item_default\": \"1970-01-01T00:00:00Z\", \"item_description\": \"A dummy date time\", \"item_format\": \"date-time\", \"item_name\": \"dummy_time\", \"item_optional\": false, \"item_title\": \"Dummy Time\", \"item_type\": \"string\" } ] } ] }", msg->str());
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

    boost::scoped_ptr<ModuleCCSession> mccs(new ModuleCCSession(
                                         ccspecfile("spec2.spec"),
                                         session, NULL, NULL,
                                         true, false));
    EXPECT_TRUE(session.haveSubscription("Spec2", "*"));
    // The initial message is irrelevant for this test
    // (see session2 test), drop it
    session.getFirstMessage(group, to);
    // Queue should now be empty
    ASSERT_EQ(0, session.getMsgQueue()->size());
    // Invoke the destructor
    mccs.reset();
    // Destructor should have caused a new message
    ASSERT_EQ(1, session.getMsgQueue()->size());
    msg = session.getFirstMessage(group, to);
    EXPECT_EQ("{ \"command\": [ \"stopping\", "
              "{ \"module_name\": \"Spec2\" } ] }", msg->str());
    EXPECT_EQ("ConfigManager", group);
    EXPECT_EQ("*", to);
    EXPECT_EQ(0, session.getMsgQueue()->size());
}

TEST_F(CCSessionTest, session_close_exception) {
    // Test whether an exception encountered during the destructor is
    // handled correctly
    ConstElementPtr msg;
    std::string group, to;

    EXPECT_FALSE(session.haveSubscription("Spec2", "*"));

    boost::scoped_ptr<ModuleCCSession> mccs(new ModuleCCSession(
                                         ccspecfile("spec2.spec"),
                                         session, NULL, NULL,
                                         true, false));
    EXPECT_TRUE(session.haveSubscription("Spec2", "*"));
    // The initial message is irrelevant for this test
    // (see session2 test), drop it
    session.getFirstMessage(group, to);
    // Queue should now be empty
    ASSERT_EQ(0, session.getMsgQueue()->size());

    // Set fake session to throw an exception
    session.setThrowOnSend(true);

    // Invoke the destructor
    mccs.reset();
    // Destructor should not have caused a new message (since fakesession
    // should have thrown an exception)
    ASSERT_EQ(0, session.getMsgQueue()->size());
    //EXPECT_EQ(0, session.getMsgQueue()->size());
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
    EXPECT_EQ("{ \"command\": [ \"module_spec\", { \"commands\": [ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down Kea\", \"command_name\": \"shutdown\" } ], \"config_data\": [ { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }, { \"item_default\": 1.1, \"item_name\": \"item2\", \"item_optional\": false, \"item_type\": \"real\" }, { \"item_default\": true, \"item_name\": \"item3\", \"item_optional\": false, \"item_type\": \"boolean\" }, { \"item_default\": \"test\", \"item_name\": \"item4\", \"item_optional\": false, \"item_type\": \"string\" }, { \"item_default\": [ \"a\", \"b\" ], \"item_name\": \"item5\", \"item_optional\": false, \"item_type\": \"list\", \"list_item_spec\": { \"item_default\": \"\", \"item_name\": \"list_element\", \"item_optional\": false, \"item_type\": \"string\" } }, { \"item_default\": {  }, \"item_name\": \"item6\", \"item_optional\": false, \"item_type\": \"map\", \"map_item_spec\": [ { \"item_default\": \"default\", \"item_name\": \"value1\", \"item_optional\": true, \"item_type\": \"string\" }, { \"item_name\": \"value2\", \"item_optional\": true, \"item_type\": \"integer\" } ] } ], \"module_name\": \"Spec2\", \"statistics\": [ { \"item_default\": \"1970-01-01T00:00:00Z\", \"item_description\": \"A dummy date time\", \"item_format\": \"date-time\", \"item_name\": \"dummy_time\", \"item_optional\": false, \"item_title\": \"Dummy Time\", \"item_type\": \"string\" } ] } ] }", msg->str());
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
    EXPECT_EQ(0, result);

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
    EXPECT_THROW_WITH(mccs.getRemoteConfigValue(module_name, "item1"),
                      CCSessionError, "Remote module "
                      << module_name << " not found.");

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
    EXPECT_THROW_WITH(mccs.addRemoteConfig(ccspecfile("spec2.spec")),
                      CCSessionError, "No result part in answer message");
    
    session.getMessages()->add(createAnswer(1, "my_error"));
    EXPECT_THROW_WITH(mccs.addRemoteConfig(ccspecfile("spec2.spec")),
                      CCSessionError,
                      "Error getting config for Spec2: "
		      << *createAnswer(1, "my_error"));
    
    session.getMessages()->add(createAnswer());
    EXPECT_THROW_WITH(mccs.addRemoteConfig(ccspecfile("spec2.spec")),
                      CCSessionError,
                      "Error getting config for Spec2: " << *createAnswer());

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
            "\"get_module_spec\", { \"module_name\": \"Spec2\" } ] }, -1 ]")));
        EXPECT_TRUE(session.getMsgQueue()->get(qsize - 1)->equals(*el(
            "[ \"ConfigManager\", \"*\", { \"command\": [ \"get_config\","
            "{ \"module_name\": \"Spec2\" } ] }, -1 ]")));
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

        EXPECT_THROW_WITH(module_name =
                              mccs.addRemoteConfig("Spec1", NULL, false),
                          CCSessionError, "Module name mismatch");
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

void
callback(std::string* command, std::string* target, ConstElementPtr *params,
         const std::string& command_real, const std::string& target_real,
         const ConstElementPtr& params_real)
{
    *command = command_real;
    *target = target_real;
    *params = params_real;
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
    EXPECT_EQ(0, result);

    // Check that we can get the ignored commands by registering a callback
    std::string command, target;
    ConstElementPtr params;
    mccs.setUnhandledCallback(boost::bind(&callback, &command, &target,
                                          &params, _1, _2, _3));
    session.addMessage(el("{ \"command\": [ \"good_command\","
                          "{\"param\": true} ] }"), "Spec1", "*");
    EXPECT_EQ(1, session.getMsgQueue()->size());
    result = mccs.checkCommand();
    EXPECT_EQ(0, session.getMsgQueue()->size());
    EXPECT_EQ(0, result);

    EXPECT_EQ("good_command", command);
    EXPECT_EQ("Spec1", target);
    EXPECT_TRUE(params && el("{\"param\": true}")->equals(*params));
}

TEST_F(CCSessionTest, initializationFail) {
    // bad specification
    EXPECT_THROW_WITH(ModuleCCSession(ccspecfile("spec8.spec"), session,
                                      NULL, NULL), CCSessionInitError,
                      "No module_spec in specification");

    // file that does not exist
    EXPECT_THROW_WITH(ModuleCCSession(ccspecfile("does_not_exist_spec"),
                                      session, NULL, NULL),
                      CCSessionInitError, "Undefined error: 0");


    session.getMessages()->add(createAnswer(1, el("\"just an error\"")));

    EXPECT_FALSE(session.haveSubscription("Spec29", "*"));
    EXPECT_THROW_WITH(ModuleCCSession(ccspecfile("spec29.spec"), session,
                                      my_config_handler, my_command_handler),
                      CCSessionInitError,
		      *createAnswer(1, el("\"just an error\"")));
    EXPECT_TRUE(session.haveSubscription("Spec29", "*"));
}

// Test it throws when we try to start it twice (once from the constructor)
TEST_F(CCSessionTest, doubleStartImplicit) {
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, NULL, NULL,
                         true, false);
    EXPECT_THROW_WITH(mccs.start(), CCSessionError,
                      "Module CC session already started");
}

// The same, but both starts are explicit
TEST_F(CCSessionTest, doubleStartExplicit) {
    ModuleCCSession mccs(ccspecfile("spec29.spec"), session, NULL, NULL,
                         false, false);
    mccs.start();
    EXPECT_THROW_WITH(mccs.start(), CCSessionError,
                      "Module CC session already started");
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

/// \brief Test fixture for asynchronous receiving of messages.
///
/// This is an extension to the CCSessionTest. It would be possible to add
/// the functionality to the CCSessionTest, but it is going to be used
/// only by few tests and is non-trivial, so it is placed to a separate
/// sub-class.
class AsyncReceiveCCSessionTest : public CCSessionTest {
protected:
    AsyncReceiveCCSessionTest() :
        mccs_(ccspecfile("spec29.spec"), session, NULL, NULL, false, false),
        msg_(el("{\"result\": [0]}")),
        next_flag_(0)
    {
        // This is just to make sure the messages get through the fake
        // session.
        session.subscribe("test group");
        session.subscribe("other group");
        session.subscribe("<ignored>");
        // Get rid of all unrelated stray messages
        while (session.getMsgQueue()->size() > 0) {
            session.getMsgQueue()->remove(0);
        }
    }
    /// \brief Convenience function to queue a request to get a command
    ///     message.
    ModuleCCSession::AsyncRecvRequestID
        registerCommand(const string& recipient)
    {
        return (mccs_.groupRecvMsgAsync(
                    boost::bind(&AsyncReceiveCCSessionTest::callback, this,
                                next_flag_++, _1, _2, _3), false, -1,
                    recipient));
    }
    /// \brief Convenience function to queue a request to get a reply
    ///     message.
    ModuleCCSession::AsyncRecvRequestID
        registerReply(int seq)
    {
        return (mccs_.groupRecvMsgAsync(
                    boost::bind(&AsyncReceiveCCSessionTest::callback, this,
                                next_flag_++, _1, _2, _3), true, seq));
    }
    /// \brief Check the next called callback was with this flag
    void called(int flag) {
        ASSERT_FALSE(called_.empty());
        EXPECT_EQ(flag, *called_.begin());
        called_.pop_front();
    }
    /// \brief Checks that no more callbacks were called.
    void nothingCalled() {
        EXPECT_TRUE(called_.empty());
    }
    /// \brief The tested session.
    ModuleCCSession mccs_;
    /// \brief The value of message on the last called callback.
    ConstElementPtr last_msg_;
    /// \brief A message that can be used
    ConstElementPtr msg_;
    // Shared part of the simpleCommand and similar tests.
    void commandTest(const string& group) {
        // Push the message inside
        session.addMessage(msg_, "test group", "<unused>");
        EXPECT_TRUE(mccs_.hasQueuedMsgs());
        // Register the callback
        registerCommand(group);
        // But the callback should not be called yet
        // (even if the message is there).
        nothingCalled();
        // But when we call the checkCommand(), it should be called.
        mccs_.checkCommand();
        called(0);
        EXPECT_EQ(msg_, last_msg_);
        // But only once
        nothingCalled();
        // And the message should be eaten
        EXPECT_FALSE(mccs_.hasQueuedMsgs());
        // The callback should have been eaten as well, inserting another
        // message will not invoke it again
        session.addMessage(msg_, "test group", "<unused>");
        mccs_.checkCommand();
        nothingCalled();
    }
    /// \brief Shared part of the simpleResponse and wildcardResponse tests.
    void responseTest(int seq) {
        // Push the message inside
        session.addMessage(msg_, "<ignored>", "<unused>", 1);
        EXPECT_TRUE(mccs_.hasQueuedMsgs());
        // Register the callback
        registerReply(seq);
        // But the callback should not be called yet
        // (even if the message is there).
        nothingCalled();
        // But when we call the checkCommand(), it should be called.
        mccs_.checkCommand();
        called(0);
        EXPECT_EQ(msg_, last_msg_);
        // But only once
        nothingCalled();
        // And the message should be eaten
        EXPECT_FALSE(mccs_.hasQueuedMsgs());
        // The callback should have been eaten as well, inserting another
        // message will not invoke it again
        session.addMessage(msg_, "test group", "<unused>");
        mccs_.checkCommand();
        nothingCalled();
    }
    /// \brief Shared part of the noMatch* tests
    void noMatchTest(int seq, int wanted_seq, bool is_reply) {
        // Push the message inside
        session.addMessage(msg_, "other group", "<unused>", seq);
        EXPECT_TRUE(mccs_.hasQueuedMsgs());
        // Register the callback
        if (is_reply) {
            registerReply(wanted_seq);
        } else {
            registerCommand("test group");
        }
        // But the callback should not be called yet
        // (even if the message is there).
        nothingCalled();
        // And even not now, because it does not match.
        mccs_.checkCommand();
        nothingCalled();
        // And the message should be eaten by the checkCommand
        EXPECT_FALSE(mccs_.hasQueuedMsgs());
    }
private:
    /// \brief The next flag to be handed out
    int next_flag_;
    /// \brief Flags of callbacks already called (as FIFO)
    list<int> called_;
    /// \brief This is the callback registered to the tested groupRecvMsgAsync
    ///     function.
    void callback(int store_flag, const ConstElementPtr&,
                  const ConstElementPtr& msg,
                  const ModuleCCSession::AsyncRecvRequestID&)
    {
        called_.push_back(store_flag);
        last_msg_ = msg;
    }
};

// Test we can receive a command, without anything fancy yet
TEST_F(AsyncReceiveCCSessionTest, simpleCommand) {
    commandTest("test group");
}

// Test we can receive a "wildcard" command - without specifying the
// group to subscribe to. Very similar to simpleCommand test.
TEST_F(AsyncReceiveCCSessionTest, wildcardCommand) {
    commandTest("");
}

// Very similar to simpleCommand, but with a response message
TEST_F(AsyncReceiveCCSessionTest, simpleResponse) {
    responseTest(1);
}

// Matching a response message with wildcard
TEST_F(AsyncReceiveCCSessionTest, wildcardResponse) {
    responseTest(-1);
}

// Check that a wrong command message is not matched
TEST_F(AsyncReceiveCCSessionTest, noMatchCommand) {
    noMatchTest(-1, -1, false);
}

// Check that a wrong response message is not matched
TEST_F(AsyncReceiveCCSessionTest, noMatchResponse) {
    noMatchTest(2, 3, true);
}

// Check that a command will not match on a reply check and vice versa
TEST_F(AsyncReceiveCCSessionTest, noMatchResponseAgainstCommand) {
    // Send a command and check it is not matched as a response
    noMatchTest(-1, -1, true);
}

TEST_F(AsyncReceiveCCSessionTest, noMatchCommandAgainstResponse) {
    noMatchTest(2, -1, false);
}

// We check for command several times before the message actually arrives.
TEST_F(AsyncReceiveCCSessionTest, delayedCallback) {
    // First, register the callback
    registerReply(1);
    // And see it is not called, because the message is not there yet
    EXPECT_FALSE(mccs_.hasQueuedMsgs());
    for (size_t i(0); i < 100; ++ i) {
        mccs_.checkCommand();
        EXPECT_FALSE(mccs_.hasQueuedMsgs());
        nothingCalled();
    }
    // Now the message finally arrives
    session.addMessage(msg_, "<ignored>", "<unused>", 1);
    EXPECT_TRUE(mccs_.hasQueuedMsgs());
    // And now, the callback is happily triggered.
    mccs_.checkCommand();
    called(0);
    EXPECT_EQ(msg_, last_msg_);
    // But only once
    nothingCalled();
}

// See that if we put multiple messages inside, and request some callbacks,
// the callbacks are called in the order of messages, not in the order they
// were registered.
TEST_F(AsyncReceiveCCSessionTest, outOfOrder) {
    // First, put some messages there
    session.addMessage(msg_, "<ignored>", "<unused>", 1);
    session.addMessage(msg_, "test group", "<unused>");
    session.addMessage(msg_, "other group", "<unused>");
    session.addMessage(msg_, "<ignored>", "<unused>", 2);
    session.addMessage(msg_, "<ignored>", "<unused>", 3);
    session.addMessage(msg_, "<ignored>", "<unused>", 4);
    // Now register some callbacks
    registerReply(13); // Will not be called
    registerCommand("other group"); // Matches 3rd message
    registerReply(2); // Matches 4th message
    registerCommand(""); // Matches the 2nd message
    registerCommand("test group"); // Will not be called
    registerReply(-1); // Matches the 1st message
    registerReply(-1); // Matches the 5th message
    // Process all messages there
    while (mccs_.hasQueuedMsgs()) {
        mccs_.checkCommand();
    }
    // These are the numbers of callbacks in the order of messages
    called(5);
    called(3);
    called(1);
    called(2);
    called(6);
    // The last message doesn't trigger anything, so nothing more is called
    nothingCalled();
}

// We first add, then remove the callback again and check that nothing is
// matched.
TEST_F(AsyncReceiveCCSessionTest, cancel) {
    // Add the callback
    ModuleCCSession::AsyncRecvRequestID request(registerReply(1));
    // Add corresponding message
    session.addMessage(msg_, "<ignored>", "<unused>", 1);
    EXPECT_TRUE(mccs_.hasQueuedMsgs());
    // And now, remove the callback again
    mccs_.cancelAsyncRecv(request);
    // And see that Nothing Happens(TM)
    mccs_.checkCommand();
    EXPECT_FALSE(mccs_.hasQueuedMsgs());
    nothingCalled();
}

// We add multiple requests and cancel only one of them to see the rest
// is unaffected.
TEST_F(AsyncReceiveCCSessionTest, cancelSome) {
    // Register few callbacks
    registerReply(1);
    ModuleCCSession::AsyncRecvRequestID request(registerCommand(""));
    registerCommand("test group");
    // Put some messages there
    session.addMessage(msg_, "test group", "<unused>");
    session.addMessage(msg_, "<ignored>", "<unused>", 1);
    // Cancel the second callback. Therefore the first message will be matched
    // by the third callback, not by the second.
    mccs_.cancelAsyncRecv(request);
    // Now, process the messages
    mccs_.checkCommand();
    mccs_.checkCommand();
    // And see how they matched
    called(2);
    called(0);
    nothingCalled();
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
