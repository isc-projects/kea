// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cb_cmds_test.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <database/backend_selector.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <boost/make_shared.hpp>

using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for commands pertaining to client classes.
class ClientClass6CmdsTest : public ConfigCmdsDhcp6Test {
public:

    /// @brief Adds unassigned client class to the configuration backend.
    ///
    /// @param client_class pointer to the client class to be stored.
    void setClientClass(const ClientClassDefPtr& client_class) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateClientClass6(BackendSelector(),
                                     ServerSelector::UNASSIGNED(),
                                     client_class,
                                     "");
    }

    /// @brief Returns remote-client-class6-set command as text.
    ///
    /// @param client_class pointer to a client class to be used in the
    /// command.
    /// @param follow_class_name name value of the follow-class-name parameter.
    /// If the string is equal to "null", the null JSON value is assigned.
    /// @param remote_map a map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeClientClass6SetConfig(const ClientClassDefPtr& client_class,
                                          const std::string& follow_class_name,
                                          const std::string& remote_map,
                                          const std::set<std::string>& server_tags) {
        auto class_element = client_class->toElement();
        std::string config = "{"
            "\"command\": \"remote-class6-set\","
            "\"arguments\": {"
            "    \"client-classes\": [";

        // Include follow-class-name if specified.
        if (!follow_class_name.empty()) {
            if (follow_class_name == "null") {
                class_element->set("follow-class-name", NullElement::create());
            } else {
                class_element->set("follow-class-name", Element::create(follow_class_name));
            }
        }

        config += class_element->str() + "]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // Only include server tags if specified.
        if (!server_tags.empty()) {
            config += ", \"server-tags\": [";
            for (auto const& tag : server_tags) {
                config += "\"" + tag + "\",";
            }
            // Remove extraneous comma.
            config.pop_back();
            config += "]";
        }

        config += "} }";
        return (config);
    }

    /// @brief Returns remote-class6-del command as text.
    ///
    /// @param client_class a pointer to a client class to be used in the
    /// command.
    /// @param remote_map a map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeClientClass6DelConfig(const ClientClassDefPtr& client_class,
                                          const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-class6-del\","
            "\"arguments\": {"
            "    \"client-classes\": [ { ";

        config += "\"name\": \"" + client_class->getName() + "\" } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }
        config += "} }";
        return (config);
    }

    /// @brief Returns remote-class6-get command as text.
    ///
    /// @param client_class pointer to the client class to be used in the
    /// command.
    /// @param remote_map A map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    ///
    /// @return Command in the textual format.
    std::string makeClientClass6GetConfig(const ClientClassDefPtr& client_class,
                                          const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-class6-get\","
            "\"arguments\": {"
            "    \"client-classes\": [ { ";

        config += "\"name\": \"" + client_class->getName() + "\" } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Returns remote-class6-get-all command as text.
    ///
    /// @param remote_map a map to be assigned to the "remote" argument
    /// of the command. If the string is empty the "remote" argument is
    /// not included.
    /// @param server_tags server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeClientClass6GetAllConfig(const std::string& remote_map,
                                             const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-class6-get-all\""
            ", \"arguments\": {";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += "\"remote\": " + remote_map + ",";
        }

        // Always include server tags,
        config += "\"server-tags\": [";
        if (!server_tags.empty()) {
                for (auto const& tag : server_tags) {
                    config += "\"" + tag + "\",";
                }
                // Remove extraneous comma.
                config.pop_back();
        } else {
            // Empty means unassigned.
            config += " null ";
        }

        config += "] } }";
        return (config);
    }

    /// @brief Positive test scenario for setting or updating client class
    ///
    /// @param client_class pointer to a client class to be created or updated.
    /// @param follow_class_name name value of the follow-class-name parameter.
    /// If the string is equal to "null", the null JSON value is assigned.
    /// @param expected_position position at which the client class should be
    /// after the update.
    /// @param remote_map a map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags server tags to be included in the command.
    void testClientClass6Set(const ClientClassDefPtr& client_class,
                             const std::string& follow_class_name = "",
                             const int expected_position = -1,
                             const std::string& remote_map = "",
                             const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        auto command_text = makeClientClass6SetConfig(client_class, follow_class_name,
                                                      remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setClientClass6,
                                             command_text));
        ASSERT_TRUE(response);

        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("DHCPv6 client class successfully set.", msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned list of client classes.
        auto client_class_list = args->get("client-classes");
        ASSERT_TRUE(client_class_list);
        EXPECT_EQ(Element::list, client_class_list->getType());
        ASSERT_EQ(1U, client_class_list->size());

        auto client_class_0 = client_class_list->get(0);
        ASSERT_TRUE(client_class_0);
        ASSERT_EQ(Element::map, client_class_0->getType());
        EXPECT_EQ(1U, client_class_0->size());

        auto client_class_0_name = client_class_0->get("name");
        ASSERT_TRUE(client_class_0_name);
        EXPECT_EQ(Element::string, client_class_0_name->getType());
        EXPECT_EQ(client_class->getName(), client_class_0_name->stringValue());

        auto fetched_client_class = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getClientClass6(BackendSelector(),
                            ServerSelector::ONE(*server_tags.begin()),
                            client_class->getName());
        ASSERT_TRUE(fetched_client_class);
        auto metadata = fetched_client_class->getMetadata();
        ASSERT_TRUE(metadata);
        auto expected_metadata = createMetadata(server_tags);
        EXPECT_EQ(expected_metadata->str(), metadata->str());

        if (client_class->getCfgOption() && !client_class->getCfgOption()->empty()) {
            EXPECT_TRUE(isEquivalent(fetched_client_class->getCfgOption()->toElement(),
                                     client_class->getCfgOption()->toElement()));
        }

        if (expected_position >= 0) {
            auto all_classes = ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllClientClasses6(BackendSelector(),
                                     ServerSelector::ONE(*server_tags.begin()));
            auto class_list = all_classes.getClasses();
            EXPECT_EQ((*(class_list->begin() + expected_position))->getName(),
                      client_class->getName());
        }
    }

    /// @brief Negative test scenario for setting or updating a client class.
    ///
    /// @param args arguments for the command in the textual format.
    /// @param answer_text expected error message.
    void testClientClass6SetFail(const std::string& args,
                                 const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-class6-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setClientClass6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);

        EXPECT_EQ(0U, msg->stringValue().find(answer_text))
            << "expected: " << answer_text
            << ", found: " << msg->stringValue();
    }

    /// @brief Positive test scenario for deleting a client class.
    ///
    /// @param client_class pointer to a client class to be deleted.
    /// @param expected_count Expected number of deleted client classes..
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testClientClass6Del(const ClientClassDefPtr& client_class,
                             unsigned expected_count,
                             const std::string& remote_map = "") {

        // Generate the command as text.
        std::string command_text = makeClientClass6DelConfig(client_class,
                                                             remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delClientClass6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " DHCPv6 client class(es) deleted.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate count.
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected_count, static_cast<unsigned>(count->intValue()));

        // Make sure that the deleted client class is not in the database.
        auto fetched_client_class = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getClientClass6(BackendSelector(), ServerSelector::ANY(), client_class->getName());
        ASSERT_FALSE(fetched_client_class);
    }

    /// @brief Negative test scenario for deleting a client class.
    ///
    /// @param args arguments for the command in the textual format.
    /// @param answer_text expected errors message.
    void testClientClass6DelFail(const std::string& args,
                                 const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-class6-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delClientClass6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Positive test scenario for getting a client class.
    ///
    /// @param client_class a pointer to a client class to be returned.
    /// @param expected_client_class pointer to the expected client class.
    /// @param remote_map a map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testClientClass6Get(const ClientClassDefPtr& client_class,
                             const ClientClassDefPtr& expected_client_class,
                             const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text = makeClientClass6GetConfig(client_class,
                                                             remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getClientClass6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_client_class ? CONTROL_RESULT_SUCCESS : CONTROL_RESULT_EMPTY);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "DHCPv6 client class '" << client_class->getName()
                     << "' " << (!expected_client_class ? "not " : "") << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned client class.
        ConstElementPtr client_classes = args->get("client-classes");
        ASSERT_TRUE(client_classes);
        ASSERT_EQ(Element::list, client_classes->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected_client_class) {
            EXPECT_EQ(0U, client_classes->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, client_classes->size());
            ConstElementPtr got = client_classes->get(0);

            // Make sure that expected client class includes metadata.
            ElementPtr expected_element = expected_client_class->toElement();
            auto tags = expected_client_class->getServerTags();
            ASSERT_FALSE(tags.empty());
            expected_element->set("metadata",
                                  createMetadata(tags.begin()->get()));

            EXPECT_TRUE(isEquivalent(got, expected_element))
                << "Actual: " << got->str()
                << ", \nExpected: " << expected_element->str();
            EXPECT_EQ(1, count->intValue());
        }
    }

    /// @brief Negative test scenario for getting a client class.
    ///
    /// @param args arguments for the command in the textual format.
    /// @param answer_text expected errors message.
    void testClientClass6GetFail(const std::string& args,
                                 const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-class6-get\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getClientClass6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Positive test scenario for getting all client classes.
    ///
    /// @param expected expected result.
    /// @param remote_map a map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command,
    /// empty means UNASSIGNED.
    void testClientClass6GetAll(ConstElementPtr expected,
                                const std::string& remote_map = "",
                                const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Sanity check.
        ASSERT_TRUE(expected) << " bad test";
        ASSERT_EQ(Element::list, expected->getType()) << " bad test";

        // Generate the command as text.
        std::string command_text = makeClientClass6GetAllConfig(remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getAllClientClasses6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected->empty() ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected->size()
                     << " DHCPv6 client class(es) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected->size(), static_cast<size_t>(count->intValue()));

        // Validate returned client classes and the metadata.
        ConstElementPtr networks = args->get("client-classes");
        ASSERT_TRUE(networks);
        EXPECT_TRUE(isEquivalent(expected, networks))
            << "Actual: " << networks->str()
            << "\nExpected: " << expected->str();
    }

    /// @brief Negative test scenario for getting all client classes.
    ///
    /// @param args arguments for the command in the textual format.
    /// @param answer_text expected errors message.
    void testClientClass6GetAllFail(const std::string& args,
                                    const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-class6-get-all\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getAllClientClasses6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update client class.
TEST_F(ClientClass6CmdsTest, clientClass6Set) {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();

    {
        SCOPED_TRACE("add new client class");
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        testClientClass6Set(client_class);
    }

    {
        SCOPED_TRACE("add another client class");
        auto client_class = boost::make_shared<ClientClassDef>("bar", match_expr, cfg_option);
        client_class->setTest("member('foo')");
        testClientClass6Set(client_class, "foo", 1);
    }

    {
        SCOPED_TRACE("update existing client class");
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        client_class->setTest("member('KNOWN')");
        testClientClass6Set(client_class, "null", 0);
    }

    {
        SCOPED_TRACE("update another client class with specifying remote");
        auto client_class = boost::make_shared<ClientClassDef>("bar", match_expr, cfg_option);
        testClientClass6Set(client_class, "", 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("add a client class for multiple servers");
        auto client_class = boost::make_shared<ClientClassDef>("xyz", match_expr, cfg_option);
        testClientClass6Set(client_class, "foo", 1, "", { "server1", "server2" });
    }
}

// This test verifies that the options can be specified with the classes.
TEST_F(ClientClass6CmdsTest, clientClass6SetWithOptions) {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();

    {
        SCOPED_TRACE("add a client class with a standard option");

        // Add a class with a standard option at class level to test
        // that options can be added together with a class to the
        // config backend.
        auto client_class = boost::make_shared<ClientClassDef>("my-class", match_expr, cfg_option);
        OptionStringPtr option(new OptionString(Option::V6, D6O_NIS_SERVERS, "2001:db8:1::1"));
        OptionDescriptor option_desc(option, false, false, "2001:db8:1::1");
        option_desc.space_name_ = DHCP6_OPTION_SPACE;
        client_class->getCfgOption()->add(option_desc, DHCP6_OPTION_SPACE);

        testClientClass6Set(client_class);
    }

    {
        SCOPED_TRACE("add a client class with an option definition specified at global scope");
        auto client_class = boost::make_shared<ClientClassDef>("my-class", match_expr, cfg_option);

        // Define option definition for an option 1001 at the global level and add to the
        // config backend.
        OptionDefinitionPtr option_def(new OptionDefinition("foo", 1001, DHCP6_OPTION_SPACE, "uint32"));
        ASSERT_NO_THROW(
            ConfigBackendDHCPv6Mgr::instance().getPool()->
                createUpdateOptionDef6(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def);
        );

        // Define an option using this definition.
        OptionUint32Ptr option(new OptionUint32(Option::V6, 1001, 123));
        OptionDescriptor option_desc(option, false, false, "123");
        option_desc.space_name_ = DHCP6_OPTION_SPACE;
        client_class->getCfgOption()->add(option_desc, DHCP6_OPTION_SPACE);

        testClientClass6Set(client_class);
    }
}

// This test verifies that malformed requests to add and update client classes
// are rejected and proper error messages are returned.
TEST_F(ClientClass6CmdsTest, clientClass6SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testClientClass6SetFail("", "invalid command 'remote-class6-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty client-classes list");
        testClientClass6SetFail("\"server-tags\": [ \"all\" ], "
                                "\"client-classes\": [ ]", "'client-classes' list "
                                "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty client class map");
        testClientClass6SetFail("\"server-tags\": [ \"all\" ], "
                                "\"client-classes\": [ { } ]",
                                "missing parameter 'name'");
    }

    {
        SCOPED_TRACE("malformed client class");
        testClientClass6SetFail("\"server-tags\": [ \"all\" ], "
                                "\"client-classes\": [ { \"test\": \"member('KNOWN')\" } ]",
                                "missing parameter 'name'");
    }

    {
        SCOPED_TRACE("multiple client classes");
        testClientClass6SetFail("\"server-tags\": [ \"all\" ], "
                                "\"client-classes\": ["
                                "{ \"name\": \"foo\" },"
                                "{ \"name\": \"bar\" }"
                                "]",
                                "'client-classes' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testClientClass6SetFail("\"client-classes\": [ ]",
                                "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testClientClass6SetFail("\"server-tags\": [ null ], "
                                "\"client-classes\": ["
                                "    { \"name\": \"bar\" } ]",
                                "'server-tags' list must contain one or"
                                " more server tags for the "
                                "'remote-class6-set' command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testClientClass6SetFail("\"server-tags\": [ ]",
                                "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testClientClass6SetFail("\"server-tags\": [ \" \" ]",
                                "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("follow class name is not a string");
        testClientClass6SetFail("\"server-tags\": [ \"all\" ], "
                                "\"client-classes\": [ { "
                                "    \"name\": \"foo\","
                                "    \"test\": \"member('KNOWN')\","
                                "    \"follow-class-name\": 1"
                                "} ]",
                                "invalid type specified for parameter 'follow-class-name'");
    }

    {
        SCOPED_TRACE("lacking option definition");
        testClientClass6SetFail("\"server-tags\": [ \"all\" ], "
                                "\"client-classes\": [ { "
                                "    \"name\": \"foo\","
                                "    \"test\": \"member('KNOWN')\","
                                "    \"option-data\": ["
                                "        {"
                                "            \"name\": \"bootfile-url\","
                                "            \"data\": \"my-boot-file\","
                                "            \"space\": \"myspace\""
                                "        }"
                                "    ]"
                                "} ]",
                                "definition for the option 'myspace.bootfile-url' does not exist");
    }
}

// This test verifies that it is possible to delete a client class.
TEST_F(ClientClass6CmdsTest, clientClass6Del) {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();

    {
        SCOPED_TRACE("add and delete new client class");
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        testClientClass6Set(client_class);
        testClientClass6Del(client_class, 1);
    }

    {
        SCOPED_TRACE("add and delete another client class");
        auto client_class = boost::make_shared<ClientClassDef>("bar", match_expr, cfg_option);
        testClientClass6Set(client_class);
        testClientClass6Del(client_class, 1);
    }

    {
        SCOPED_TRACE("delete client class");
        // Deleting not existing is not an error.
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        testClientClass6Del(client_class, 0);
    }

    {
        SCOPED_TRACE("delete another client class with specifying remote");
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        testClientClass6Set(client_class, "", -1, "{ \"type\": \"mysql\" }");
        testClientClass6Del(client_class, 1, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to delete client classes
// are rejected and proper error messages are returned.
TEST_F(ClientClass6CmdsTest, clientClass6DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testClientClass6DelFail("", "invalid command 'remote-class6-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty client-classes list");
        testClientClass6DelFail("\"client-classes\": [ ]",
                                "'client-classes' list "
                                "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty client class map");
        testClientClass6DelFail("\"client-classes\": [ { } ]",
                                "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("malformed client class");
        testClientClass6DelFail("\"client-classes\": [ { \"test\": \"member('KNOWN')\" } ]",
                                "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("multiple client classes");
        testClientClass6DelFail("\"client-classes\": ["
                                "{ \"name\": \"foo\" },"
                                "{ \"name\": \"bar\" }"
                                "]",
                                "'client-classes' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testClientClass6DelFail("\"server-tags\": [ ]",
                                "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testClientClass6DelFail("\"client-classes\": ["
                                "    { \"name\": \"foo\" }"
                                "],"
                                "\"remote\": {"
                                "    \"type\": \"postgresql\""
                                "}",
                                "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get client class
TEST_F(ClientClass6CmdsTest, clientClass6Get) {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();
    CfgOptionDefPtr cfg_option_def = boost::make_shared<CfgOptionDef>();

    {
        SCOPED_TRACE("add and get new client class");
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag("server1");
        testClientClass6Set(client_class, "", -1, "", { "server1" });
        testClientClass6Get(client_class, client_class);
    }

    {
        SCOPED_TRACE("add and get another client class");
        auto client_class = boost::make_shared<ClientClassDef>("bar", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag(ServerTag::ALL);
        testClientClass6Set(client_class);
        testClientClass6Get(client_class, client_class);
    }

    {
        SCOPED_TRACE("get no client class");
        // Getting not existing is not an error.
        auto client_class = boost::make_shared<ClientClassDef>("baz", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag(ServerTag::ALL);
        testClientClass6Get(client_class, ClientClassDefPtr());
    }

    {
        SCOPED_TRACE("add and get client class with specifying remote");
        auto client_class = boost::make_shared<ClientClassDef>("abc", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag(ServerTag::ALL);
        testClientClass6Set(client_class, "", -1, "{ \"type\": \"mysql\" }");
        testClientClass6Get(client_class, client_class, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to get a client class are
// rejected and proper error messages are returned.
TEST_F(ClientClass6CmdsTest, clientClass6GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testClientClass6GetFail("", "invalid command 'remote-class6-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty client-classes list");
        testClientClass6GetFail("\"client-classes\": [ ]",
                                "'client-classes' list "
                                "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty client class map");
        testClientClass6GetFail("\"client-classes\": [ { } ]",
                                "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("malformed client class");
        testClientClass6GetFail("\"client-classes\": [ { \"test\": \"member('KNOWN')\" } ]",
                                "missing 'name' parameter");
    }

    {
        SCOPED_TRACE("multiple client classes");
        testClientClass6GetFail("\"client-classes\": ["
                                "{ \"name\": \"foo\" },"
                                "{ \"name\": \"bar\" }"
                                "]",
                                "'client-classes' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testClientClass6GetFail("\"server-tags\": [ ]",
                                "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testClientClass6GetFail("\"client-classes\": ["
                                "    { \"name\": \"foo\" }"
                                "],"
                                "\"remote\": {"
                                "    \"type\": \"postgresql\""
                                "}",
                                "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get all client classes.
TEST_F(ClientClass6CmdsTest, clientClass6GetAll) {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();
    CfgOptionDefPtr cfg_option_def = boost::make_shared<CfgOptionDef>();

    ElementPtr expected = Element::createList();
    ElementPtr expected_all = Element::createList();
    ElementPtr expected_unassigned = Element::createList();

    {
        SCOPED_TRACE("no client classes in the database");
        testClientClass6GetAll(expected);
        testClientClass6GetAll(expected_all);
        testClientClass6GetAll(expected_unassigned);
    }

    {
        SCOPED_TRACE("add first class for server1");
        auto client_class = boost::make_shared<ClientClassDef>("foo", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag("server1");
        testClientClass6Set(client_class, "", -1, "", { "server1" });
        auto client_class_map = client_class->toElement();
        client_class_map->set("metadata", createMetadata("server1"));
        expected->add(client_class_map);
        testClientClass6GetAll(expected, "", { "server1" });
    }

    {
        SCOPED_TRACE("add second class for all servers");
        auto client_class = boost::make_shared<ClientClassDef>("bar", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag(ServerTag::ALL);
        testClientClass6Set(client_class);
        auto client_class_map = client_class->toElement();
        client_class_map->set("metadata", createMetadata(ServerTag::ALL));
        expected->add(client_class_map);
        expected_all->add(client_class_map);
        testClientClass6GetAll(expected, "", { "server1" });
        testClientClass6GetAll(expected_all);

        // With another server only client class belonging to all is returned.
        testClientClass6GetAll(expected_all, "", { "server2" });
    }

    {
        SCOPED_TRACE("add third class and use remote to fetch it");
        auto client_class = boost::make_shared<ClientClassDef>("abc", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag(ServerTag::ALL);
        testClientClass6Set(client_class, "", -1, "{ \"type\": \"mysql\" }");
        auto client_class_map = client_class->toElement();
        client_class_map->set("metadata", createMetadata(ServerTag::ALL));
        expected->add(client_class_map);
        expected_all->add(client_class_map);
        testClientClass6GetAll(expected, "{ \"type\": \"mysql\" }", { "server1" });
        testClientClass6GetAll(expected_all, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("get classes for multiple server tags");
        auto client_class = boost::make_shared<ClientClassDef>("xyz", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        client_class->setServerTag("server2");
        testClientClass6Set(client_class, "", -1, "", { "server2" });
        testClientClass6GetAll(expected, "", { "server1" });
        auto client_class_map = client_class->toElement();
        client_class_map->set("metadata", createMetadata("server2"));
        expected->add(client_class_map);
        testClientClass6GetAll(expected, "", { "server1", "server2" });
    }

    {
        SCOPED_TRACE("get unassigned client classes");
        testClientClass6GetAll(expected_unassigned, "", { });
        auto client_class = boost::make_shared<ClientClassDef>("uvw", match_expr, cfg_option);
        client_class->setCfgOptionDef(cfg_option_def);
        // Add it directly to the backend (no command yet to do this).
        setClientClass(client_class);
        // Not visible by a server.
        testClientClass6GetAll(expected, "", { "server1", "server2" });
        auto client_class_map = client_class->toElement();
        client_class_map->set("metadata", createMetadata(std::set<std::string>()));
        expected_unassigned->add(client_class_map);
        testClientClass6GetAll(expected_unassigned, "", { });
    }
}

// This test verifies that malformed requests to get all shared networks
// are rejected and proper error messages are returned.
TEST_F(ClientClass6CmdsTest, clientClass6ListFail) {
    {
        SCOPED_TRACE("empty arguments");
        testClientClass6GetAllFail(", \"arguments\": { }",
                                   "invalid command 'remote-class6-get-all': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("no server tags");
        testClientClass6GetAllFail(", \"arguments\": { \"remote\": { } }",
                                   "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testClientClass6GetAllFail(", \"arguments\": { \"server-tags\": [ ] }",
                                   "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("bad formed unassigned");
        testClientClass6GetAllFail(", \"arguments\": { "
                                   "\"server-tags\": [ null, \"all\" ] }",
                                   "when the 'server-tags' list contains "
                                   "multiple elements all these elements must "
                                   "have the string type");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testClientClass6GetAllFail(", \"arguments\": { "
                                   "\"server-tags\": [ \"all\" ], "
                                   "\"remote\": {"
                                   "    \"type\": \"postgresql\""
                                   "} }",
                                   "no such database found for selector: "
                                   "type=postgresql");
    }
}

// This test verifies that the options with client-classes can be specified with the classes.
// Users might not do this but we support it.
TEST_F(ClientClass6CmdsTest, clientClass6SetWithOptionsWithClientClases) {
    ExpressionPtr match_expr = boost::make_shared<Expression>();
    CfgOptionPtr cfg_option = boost::make_shared<CfgOption>();

    {
        SCOPED_TRACE("add a class with two different class-tagged values of an option");

        // Add a class with a two options with different class tags
        auto client_class = boost::make_shared<ClientClassDef>("my-class", match_expr, cfg_option);

        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL, "boot-one"));
        OptionDescriptor option_desc1(option, false, false, "boot-one");
        option_desc1.space_name_ = DHCP6_OPTION_SPACE;
        option_desc1.addClientClass("cc-one");
        client_class->getCfgOption()->add(option_desc1, DHCP6_OPTION_SPACE);

        option.reset(new OptionString(Option::V6, D6O_BOOTFILE_URL, "boot-two"));
        OptionDescriptor option_desc2(option, false, false, "boot-two");
        option_desc2.space_name_ = DHCP6_OPTION_SPACE;
        option_desc2.addClientClass("cc-two");
        client_class->getCfgOption()->add(option_desc2, DHCP6_OPTION_SPACE);

        testClientClass6Set(client_class);
    }

    {
        SCOPED_TRACE("add the same client class, change one class-tagged value, omit the other");

        // Update one option and omit the other.
        auto client_class = boost::make_shared<ClientClassDef>("my-class", match_expr, cfg_option);

        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL, "boot-one-updated"));
        OptionDescriptor option_desc1(option, false, false, "boot-one-updated");
        option_desc1.space_name_ = DHCP6_OPTION_SPACE;
        option_desc1.addClientClass("cc-one");
        client_class->getCfgOption()->add(option_desc1, DHCP6_OPTION_SPACE);

        testClientClass6Set(client_class);
    }
}

}
