// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cb_cmds_test.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <database/backend_selector.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <boost/make_shared.hpp>
#include <set>
#include <string>
#include <sstream>

using namespace isc::cb;
using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;

namespace {

/// @brief Test fixture class for callouts pertaining to DHCP options.
class Option6CmdsTest : public ConfigCmdsDhcp6Test {
public:

    /// @brief Returns remote-option6-global-set as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption6SetConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option6-global-set\","
            "\"arguments\": {"
            "    \"options\": ";

        CfgOption cfg_option;
        cfg_option.add(*option, option->space_name_);

        config += cfg_option.toElement()->str();

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

    /// @brief Positive test scenario for setting or updating a DHCP option.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testGlobalOption6Set(const OptionDescriptorPtr& option,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalOption6SetConfig(option, remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setGlobalOption6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("DHCPv6 option successfully set.", msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned list of options.
        auto option_list = args->get("options");
        ASSERT_TRUE(option_list);
        ASSERT_EQ(Element::list, option_list->getType());
        ASSERT_EQ(1U, option_list->size());

        { SCOPED_TRACE("check info"); checkOptionInfo(option_list->get(0), *option); }

        // Make sure that the created/updated global option is in the database
        // and has correct values.
        ASSERT_FALSE(server_tags.empty());
        auto fetched_option = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getOption6(BackendSelector(),
                       ServerSelector::ONE(*server_tags.begin()),
                       option->option_->getType(),
                       option->space_name_);
        ASSERT_TRUE(fetched_option);
        EXPECT_TRUE(fetched_option->equals(*option));
    }

    /// @brief Negative test scenario for setting or updating a DHCP option.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testGlobalOption6SetFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-global-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setGlobalOption6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);

        /// @todo Skipping line number possibly appended to the error message by
        /// the option definition parser. We should modify the parser to not
        /// output the position when used for control commands parsing.
        EXPECT_EQ(0U, answer->stringValue().find(answer_text))
            << "expected: " << answer_text
            << ", found: " << answer->stringValue();
    }

    /// @brief Returns remote-option6-global-del as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    /// @param client_classes client_classes to be included in the command.
    /// It is omitted if it is an empty pointer.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption6DelConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           const std::set<std::string>& server_tags,
                                           const ClientClassesPtr client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option6-global-del\","
            "\"arguments\": {"
            "    \"options\": [ { ";

        CfgOption cfg_option;
        cfg_option.add(*option, option->space_name_);

        std::ostringstream code;
        code << option->option_->getType();
        config += "\"code\": " + code.str();
        config += ", \"space\": \"" + option->space_name_ + "\"";
        if (client_classes) {
            auto elem = client_classes->toElement();
            config += ", \"client-classes\": " + elem->str();
        }

        config += " } ]";

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

    /// @brief Positive test scenario for deleting a DHCP option.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param expected_count Expected number of deleted DHCP options.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    /// @param client_classes client classes to use to identify the option
    void testGlobalOption6Del(const OptionDescriptorPtr& option,
                              unsigned expected_count,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL },
                              const ClientClassesPtr client_classes = ClientClassesPtr()) {
        // Generate the command as text.
        std::string command_text =
            makeGlobalOption6DelConfig(option, remote_map, server_tags, client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delGlobalOption6,
                                             command_text)) << " COMMAND: " << command_text;
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " DHCPv6 option(s) deleted.";
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

        // Make sure that the deleted global option is not in the database.
        if (expected_count) {
            ASSERT_FALSE(server_tags.empty());
            auto fetched_option = ConfigBackendDHCPv6Mgr::instance().getPool()->
                getOption6(BackendSelector(),
                           ServerSelector::ONE(*server_tags.begin()),
                           option->option_->getType(),
                           option->space_name_);
            ASSERT_FALSE(fetched_option);
        }
    }

    /// @brief Negative test scenario for deleting a DHCP option.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testGlobalOption6DelFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-global-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delGlobalOption6,
                                             command_text)) << " COMMAND: " << command_text;
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-option6-global-get as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    /// @param client_classes client_classes to be included in the command.
    /// It is omitted if it is an empty pointer.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption6GetConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           const std::set<std::string>& server_tags,
                                           const ClientClassesPtr client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option6-global-get\","
            "\"arguments\": {"
            "    \"options\": [ { ";

        CfgOption cfg_option;
        cfg_option.add(*option, option->space_name_);

        std::ostringstream code;
        code << option->option_->getType();
        config += "\"code\": " + code.str();
        config += ", \"space\": \"" + option->space_name_ + "\"";
        if (client_classes) {
            auto elem = client_classes->toElement();
            config += ", \"client-classes\": " + elem->str();
        }

        config += " } ]";

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

    /// @brief Positive test scenario for getting a DHCP option.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param expected Pointer to the expected option.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    /// @param client_classes client classes to use to identify the option.
    void testGlobalOption6Get(const OptionDescriptorPtr& option,
                              const OptionDescriptorPtr& expected,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL },
                              const ClientClassesPtr client_classes = ClientClassesPtr()) {
        // Generate the command as text.
        std::string command_text =
            makeGlobalOption6GetConfig(option, remote_map, server_tags, client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getGlobalOption6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "DHCPv6 option " << option->option_->getType();
        if (client_classes) {
            expected_msg << " with client-classes = "
                         << client_classes->toElement()->str();
        }

        expected_msg << " in '" << option->space_name_ << "' "
                     << (!expected ? "not " : "") << "found.";

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned option.
        ConstElementPtr options = args->get("options");
        ASSERT_TRUE(options);
        ASSERT_EQ(Element::list, options->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected) {
            EXPECT_EQ(0U, options->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, options->size());
            ConstElementPtr got = options->get(0);
            ASSERT_TRUE(got);
            std::pair<OptionDescriptor, std::string> option_pair =
              std::make_pair(OptionDescriptor(false, false), "");
            OptionDataParser parser(AF_INET6);
            ASSERT_NO_THROW(option_pair = parser.parse(got));
            option_pair.first.space_name_ = option_pair.second;
            EXPECT_TRUE(expected->equals(option_pair.first));

            // Make sure that metadata is returned.
            auto metadata = got->get("metadata");
            ASSERT_TRUE(metadata);
            auto expected_metadata = createMetadata(*server_tags.begin());
            ASSERT_FALSE(server_tags.empty());
            EXPECT_TRUE(isEquivalent(metadata, expected_metadata))
                << "Actual: " << metadata->str()
                << "\nExpected: " << expected_metadata->str();

            EXPECT_EQ(1, count->intValue());
        }
    }

    /// @brief Negative test scenario for getting a DHCP option.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testGlobalOption6GetFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-global-get\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getGlobalOption6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-option6-global-get-all as text.
    ///
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption6GetAllConfig(const std::string& remote_map,
                                              const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option6-global-get-all\"";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty() || !server_tags.empty()) {
            config += ", \"arguments\": { ";

            // Only include remote if specified.
            if (!remote_map.empty()) {
                config += "\"remote\": " + remote_map;
            }

            // Only include server tags if specified.
            if (!server_tags.empty()) {
                if (!remote_map.empty()) {
                    config += ",";
                }
                config += "\"server-tags\": [";
                for (auto const& tag : server_tags) {
                    config += "\"" + tag + "\",";
                }
                // Remove extraneous comma.
                config.pop_back();
                config += "]";
            }

            config += " }";
        }
        config += "}";
        return (config);
    }

    /// @brief Positive test scenario for getting all DHCP options.
    ///
    /// @param expected Expected result.
    /// @param expected_count Expected number of got DHCP options.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testGlobalOption6GetAll(const CfgOption& expected,
                                 unsigned expected_count,
                                 const std::string& remote_map = "",
                                 const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalOption6GetAllConfig(remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getAllGlobalOptions6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " DHCPv6 option(s) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected_count, static_cast<unsigned>(count->intValue()));

        // Validate returned options.
        ConstElementPtr options = args->get("options");
        ASSERT_TRUE(options);
        ASSERT_EQ(Element::list, options->getType());
        CfgOption got;
        for (auto const& option : options->listValue()) {
            ASSERT_TRUE(option);
            ASSERT_EQ(Element::map, option->getType());
            std::pair<OptionDescriptor, std::string> option_pair =
              std::make_pair(OptionDescriptor(false, false), "");
            OptionDataParser parser(AF_INET6);
            ASSERT_NO_THROW(option_pair = parser.parse(option));
            option_pair.first.space_name_ = option_pair.second;
            ASSERT_NO_THROW(got.add(option_pair.first, option_pair.second));

            // Make sure that metadata is returned.
            auto metadata = option->get("metadata");
            ASSERT_TRUE(metadata);
            auto exp = expected.get(option_pair.second,
                                    option_pair.first.option_->getType());
            ASSERT_FALSE(server_tags.empty());
            auto expected_metadata =
                createMetadata(exp.hasAllServerTag() ?
                               ServerTag::ALL : *server_tags.begin());
            EXPECT_TRUE(isEquivalent(metadata, expected_metadata))
                << "Actual: " << metadata->str()
                << "\nExpected: " << expected_metadata->str();
        }

        // Compare to expected.
        EXPECT_EQ(expected, got);
    }

    /// @brief Negative test scenario for getting all DHCP options.
    ///
    /// @param args Arguments for the command in the textual format not
    /// including "arguments".
    /// @param answer_text Expected error message.
    void testGlobalOption6GetAllFail(const std::string& args,
                                     const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-global-get-all\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getAllGlobalOptions6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update global DHCP option.
TEST_F(Option6CmdsTest, globalOption6Set) {
    {
        SCOPED_TRACE("add new global option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "", { "server1" });
    }

    {
        SCOPED_TRACE("add another global option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6,
                                                D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc);
    }

    {
        SCOPED_TRACE("update existing global option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "", { "server1" });
    }

    {
        SCOPED_TRACE("update another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V6,
                                                D6O_V6_CAPTIVE_PORTAL,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("add an option for which a definition is required");
        // Add option definition for option 1001 to the config backend.
        auto option_def = boost::make_shared<OptionDefinition>("foo", 1001, DHCP6_OPTION_SPACE,
                                                               "string");
        ASSERT_NO_THROW(
            ConfigBackendDHCPv6Mgr::instance().getPool()->
                createUpdateOptionDef6(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def);
        );

        // Add the option 1001 instance.
        OptionStringPtr option(new OptionString(Option::V6, 1001, "baz"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false, "baz"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;

        testGlobalOption6Set(option_desc);
    }
}

// This test verifies that malformed requests to add and update global
// DHCP options are rejected and proper error messages are returned.
TEST_F(Option6CmdsTest, globalOption6SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption6SetFail("", "invalid command 'remote-option6-global-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty options list");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { } ]",
                                 "option data configuration requires one of "
                                 "'code' or 'name' parameters to be specified");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "{ \"name\": \"bootfile-url\","
                                 "  \"data\": \"my-boot-file\", "
                                 "\"type\": \"string\" } ]",
                                 "spurious 'type' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "{ \"name\": \"bootfile-url\","
                                 "  \"data\": \"my-boot-file\", "
                                 "\"space\": 6 } ]",
                                 "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"name\": \"new-posix-timezone\" } ]",
                                 "option data does not match option definition");
    }

    {
        SCOPED_TRACE("multiple options");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "{ \"name\": \"bootfile-url\","
                                 "  \"data\": \"my-boot-file\" },"
                                 "{ \"name\": \"nis-domain-name\","
                                 " \"data\": \"mydomain\" }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption6SetFail("\"options\": [ ]",
                                 "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption6SetFail("\"server-tags\": [ ]",
                                 "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testGlobalOption6SetFail("\"server-tags\": [ \" \" ]",
                                 "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption6SetFail("\"server-tags\": [ null ], "
                                 "\"options\": ["
                                 "{ \"name\": \"nis-domain-name\","
                                 " \"data\": \"mydomain\" }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option6-global-set'"
                                 " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption6SetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                 "\"options\": ["
                                 "{ \"name\": \"nis-domain-name\","
                                 " \"data\": \"mydomain\" }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option6-global-set'"
                                 " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "    { \"name\": \"bootfile-url\","
                                 "      \"data\": \"my-boot-file\" }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("lacking option definition");
        testGlobalOption6SetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "    {"
                                 "        \"name\": \"bootfile-url\","
                                 "        \"data\": \"my-boot-file\","
                                 "        \"space\": \"myspace\""
                                 "    }"
                                 "]",
                                 "definition for the option 'myspace.bootfile-url' does not exist");
    }
}

// This test verifies that it is possible to delete global DHCP option.
TEST_F(Option6CmdsTest, globalOption6Del) {
    {
        SCOPED_TRACE("add and delete new global option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc);
        testGlobalOption6Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("add and delete another global option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6,
                                                D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc);
        testGlobalOption6Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("delete another global option without server tag");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "", { "server1" });
        // When using server tag 'all' it should not delete our option
        // because this option was assigned to server1 explicitly.
        testGlobalOption6Del(option_desc, 0);
    }

    {
        SCOPED_TRACE("delete another global option by server tag");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "", { "server1" });
        testGlobalOption6Del(option_desc, 1, "", { "server1" });
    }

    {
        SCOPED_TRACE("delete global option");
        // Deleting not existing is not an error.
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Del(option_desc, 0);
    }

    {
        SCOPED_TRACE("delete another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V6,
                                                D6O_V6_CAPTIVE_PORTAL,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "{ \"type\": \"mysql\" }");
        testGlobalOption6Del(option_desc, 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("delete option 0 in not dhcp6 space");
        OptionPtr option(new Option(Option::V6, 0));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = "foo";
        testGlobalOption6Set(option_desc);
        testGlobalOption6Del(option_desc, 1);
    }
}

// This test verifies that it is possible to delete global DHCP option.
TEST_F(Option6CmdsTest, globalOption6DelWithClientClasses) {
    OptionDescriptorPtr option_desc;
    const std::set<std::string>& server_tags = { ServerTag::ALL };
    {
        SCOPED_TRACE("Add option with client-classes");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        option_desc.reset(new OptionDescriptor(option, false, false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        option_desc->addClientClass("cc-one");
        option_desc->addClientClass("cc-two");
        testGlobalOption6Set(option_desc);
    }

    ClientClassesPtr client_classes(new ClientClasses());
    {
        SCOPED_TRACE("Delete with empty client-classes list should fail");
        testGlobalOption6Del(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Delete with a non-matching client-classes list should fail");
        client_classes->insert("cc-one");
        testGlobalOption6Del(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Delete when client-classes matches should succeed");
        client_classes->insert("cc-two");
        testGlobalOption6Del(option_desc, 1, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Delete when client-classes is an empty pointer should succeed");
        // Re-add the option.
        testGlobalOption6Set(option_desc);
        testGlobalOption6Del(option_desc, 1, "", server_tags, ClientClassesPtr());
    }
}

// This test verifies that malformed requests to delete global DHCP
// options are rejected and proper error messages are returned.
TEST_F(Option6CmdsTest, globalOption6DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption6DelFail("", "invalid command 'remote-option6-global-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty options list");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { } ]",
                                 "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \"\" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \" \" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": 60 } ]",
                                 "'space' parameter is not a string");

    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": \"nis-domain-name\" } ]",
                                 "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 100000} ]",
                                 "invalid 'code' value not in [0..65535]");
    }

    {
        SCOPED_TRACE("option 0 is reserved");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 0 } ]",
                                 "invalid 'code' value 0: reserved");
    }

    {
        SCOPED_TRACE("multiple options");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "{ \"code\": 67 },"
                                 "{ \"code\": 40 }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption6DelFail("\"options\": [ ]",
                                 "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption6DelFail("\"server-tags\": [ ]",
                                 "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testGlobalOption6DelFail("\"server-tags\": [ \" \" ]",
                                 "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption6DelFail("\"server-tags\": [ null ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option6-global-del'"
                                 " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption6DelFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option6-global-del'"
                                 " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption6DelFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "    { \"code\": 67 }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("client-classes not a list");
        testGlobalOption6DelFail(R"(
            "server-tags": [ "all" ],
            "options": [ {
                "code": 1,
                "space": "dhcp6",
                "client-classes": "bogus"
                } ]
            )",
            "'client-classes' parameter is not a list");
    }
}

// This test verifies that it is possible to get global DHCP option.
TEST_F(Option6CmdsTest, globalOption6Get) {
    {
        SCOPED_TRACE("add and get new global option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "", { "server1" });
        testGlobalOption6Get(option_desc, option_desc, "", { "server1" });
    }

    {
        SCOPED_TRACE("add and get another global option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6,
                                                D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc);
        testGlobalOption6Get(option_desc, option_desc);
    }

    {
        SCOPED_TRACE("get no global option");
        // Getting not existing is not an error.
        OptionPtr option(new OptionInt<uint16_t>(Option::V6,
                                                 D6O_ELAPSED_TIME,
                                                 1024));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Get(option_desc, OptionDescriptorPtr());
    }

    {
        SCOPED_TRACE("add and get another option with specifying remote");
        OptionPtr option(new OptionInt<uint16_t>(Option::V6,
                                                 D6O_ELAPSED_TIME,
                                                 1024));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testGlobalOption6Set(option_desc, "{ \"type\": \"mysql\" }");
        testGlobalOption6Get(option_desc, option_desc,
                             "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that it is possible to get global DHCP options
// with client-classes option.
TEST_F(Option6CmdsTest, globalOption6GetWithClientClasses) {
    OptionDescriptorPtr option_desc;
    const std::set<std::string>& server_tags = { ServerTag::ALL };
    {
        SCOPED_TRACE("Add option with client-classes");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        option_desc.reset(new OptionDescriptor(option, false, false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        option_desc->addClientClass("cc-one");
        option_desc->addClientClass("cc-two");
        testGlobalOption6Set(option_desc);
    }

    ClientClassesPtr client_classes(new ClientClasses());
    {
        SCOPED_TRACE("Get with empty client-classes list should fail");
        testGlobalOption6Get(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Get with a non-matching client-classes list should fail");
        client_classes->insert("cc-one");
        testGlobalOption6Get(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Get when client-classes matches should succeed");
        client_classes->insert("cc-two");
        testGlobalOption6Get(option_desc, option_desc, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Get when client-classes is an empty pointer should succeed");
        testGlobalOption6Get(option_desc, option_desc, "", server_tags, ClientClassesPtr());
    }
}

// This test verifies that malformed requests to get global DHCP
// options are rejected and proper error messages are returned.
TEST_F(Option6CmdsTest, globalOption6GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption6GetFail("", "invalid command 'remote-option6-global-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty options list");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { } ]",
                                 "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \"\" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \" \" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": 40 } ]",
                                 "'space' parameter is not a string");

    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": \"nis-domain-name\" } ]",
                                 "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": [ { \"code\": 100000} ]",
                                 "invalid 'code' value not in [0..65535]");
    }

    {
        SCOPED_TRACE("multiple options");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "{ \"code\": 67 },"
                                 "{ \"code\": 40 }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption6GetFail("\"options\": [ ]",
                                 "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption6GetFail("\"server-tags\": [ ]",
                                 "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testGlobalOption6GetFail("\"server-tags\": [ \" \" ]",
                                 "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption6GetFail("\"server-tags\": [ null ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option6-global-get'"
                                 " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption6GetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option6-global-get'"
                                 " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption6GetFail("\"server-tags\": [ \"all\" ],"
                                 "\"options\": ["
                                 "    { \"code\": 67 }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get all global DHCP options.
TEST_F(Option6CmdsTest, globalOption6GetAll) {
    // Empty.
    CfgOption expected;
    CfgOption expected_all;
    testGlobalOption6GetAll(expected, 0);
    testGlobalOption6GetAll(expected_all, 0);

    // Add an option.
    OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                            "my-boot-file"));
    OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                         false));
    option_desc->space_name_ = DHCP6_OPTION_SPACE;
    option_desc->setServerTag("server1");
    testGlobalOption6Set(option_desc, "", { "server1" });
    expected.add(*option_desc, DHCP6_OPTION_SPACE);
    testGlobalOption6GetAll(expected, 1, "", { "server1" });

    // Add a second option definition.
    option.reset(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                  "myportal"));
    option_desc.reset(new OptionDescriptor(option, true, false, "myportal"));
    option_desc->space_name_ = DHCP6_OPTION_SPACE;
    option_desc->setServerTag(ServerTag::ALL);
    testGlobalOption6Set(option_desc);
    expected.add(*option_desc, DHCP6_OPTION_SPACE);
    expected_all.add(*option_desc, DHCP6_OPTION_SPACE);
    testGlobalOption6GetAll(expected, 2, "", { "server1" });

    // With another server only options belonging to all are returned.
    testGlobalOption6GetAll(expected_all, 1, "", { "server2" });
    testGlobalOption6GetAll(expected_all, 1);

    // Try with a remote.
    OptionPtr option2(new OptionInt<uint16_t>(Option::V6,
                                              D6O_ELAPSED_TIME,
                                              1024));
    option_desc.reset(new OptionDescriptor(option2, false, false));
    option_desc->space_name_ = DHCP6_OPTION_SPACE;
    option_desc->setServerTag(ServerTag::ALL);
    testGlobalOption6Set(option_desc, "{ \"type\": \"mysql\" }");
    expected.add(*option_desc, DHCP6_OPTION_SPACE);
    testGlobalOption6GetAll(expected, 3, "{ \"type\": \"mysql\" }", { "server1" });
}

// This test verifies that malformed requests to get all global DHCP
// options are rejected and proper error messages are returned.
TEST_F(Option6CmdsTest, globalOption6GetAllFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption6GetAllFail(", \"arguments\": { }",
                                    "invalid command 'remote-option6-global-get-all': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption6GetAllFail(", \"arguments\": {"
                                       "    \"remote\": {"
                                       "        \"type\": \"mysql\""
                                       "    }"
                                    " }",
                                    "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ ]"
                                    "}",
                                    "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag");
        testGlobalOption6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ \" \" ]"
                                    "}",
                                    "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ null ]"
                                    "}",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-option6-global-get-all'"
                                    " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ \"server1\", \"server2\" ]"
                                    "}",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-option6-global-get-all'"
                                    " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption6GetAllFail(", \"arguments\": { "
                                    "\"server-tags\": [ \"all\" ],"
                                    "\"remote\": {"
                                    "    \"type\": \"postgresql\""
                                    "} }",
                                    "no such database found for selector: "
                                    "type=postgresql");
    }
}

}
