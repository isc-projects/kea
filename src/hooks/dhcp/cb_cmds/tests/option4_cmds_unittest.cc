// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cb_cmds_test.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <database/backend_selector.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
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
class Option4CmdsTest : public ConfigCmdsDhcp4Test {
public:

    /// @brief Returns remote-option4-global-set as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption4SetConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option4-global-set\","
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
    void testGlobalOption4Set(const OptionDescriptorPtr& option,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalOption4SetConfig(option, remote_map,
                                                              server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setGlobalOption4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("DHCPv4 option successfully set.", msg->stringValue());

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
        auto fetched_option = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getOption4(BackendSelector(),
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
    void testGlobalOption4SetFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option4-global-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setGlobalOption4,
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

    /// @brief Returns remote-option4-global-del as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    /// @param client_classes client_classes to be included in the command.
    /// It is omitted if it is an empty pointer.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption4DelConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           const std::set<std::string>& server_tags,
                                           const ClientClassesPtr client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option4-global-del\","
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
    void testGlobalOption4Del(const OptionDescriptorPtr& option,
                              unsigned expected_count,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL },
                              const ClientClassesPtr client_classes = ClientClassesPtr()) {
        // Generate the command as text.
        std::string command_text =
            makeGlobalOption4DelConfig(option, remote_map, server_tags, client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delGlobalOption4,
                                             command_text)) << " COMMAND: " << command_text;
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " DHCPv4 option(s) deleted.";
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
            auto fetched_option = ConfigBackendDHCPv4Mgr::instance().getPool()->
                getOption4(BackendSelector(),
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
    void testGlobalOption4DelFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option4-global-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delGlobalOption4,
                                             command_text)) << " COMMAND: " << command_text;
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-option4-global-get as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    /// @param client_classes client_classes to be included in the command.
    /// It is omitted if it is an empty pointer.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption4GetConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           const std::set<std::string>& server_tags,
                                           const ClientClassesPtr client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option4-global-get\","
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
    /// @param client_classes client classes to use to identify the option
    void testGlobalOption4Get(const OptionDescriptorPtr& option,
                              const OptionDescriptorPtr& expected,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL },
                              const ClientClassesPtr client_classes = ClientClassesPtr()) {
        // Generate the command as text.
        std::string command_text =
            makeGlobalOption4GetConfig(option, remote_map, server_tags, client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getGlobalOption4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "DHCPv4 option " << option->option_->getType();
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
            OptionDataParser parser(AF_INET);
            ASSERT_NO_THROW(option_pair = parser.parse(got));
            option_pair.first.space_name_ = option_pair.second;
            EXPECT_TRUE(expected->equals(option_pair.first));

            // Make sure that metadata is returned.
            auto metadata = got->get("metadata");
            ASSERT_TRUE(metadata);
            ASSERT_FALSE(server_tags.empty());
            auto expected_metadata = createMetadata(*server_tags.begin());
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
    void testGlobalOption4GetFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option4-global-get\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getGlobalOption4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-option4-global-get-all as text.
    ///
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalOption4GetAllConfig(const std::string& remote_map,
                                              const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option4-global-get-all\"";

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
    void testGlobalOption4GetAll(const CfgOption& expected,
                                 unsigned expected_count,
                                 const std::string& remote_map = "",
                                 const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalOption4GetAllConfig(remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getAllGlobalOptions4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count << " DHCPv4 option(s) found.";
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
            OptionDataParser parser(AF_INET);
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
    void testGlobalOption4GetAllFail(const std::string& args,
                                     const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option4-global-get-all\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getAllGlobalOptions4,
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
TEST_F(Option4CmdsTest, globalOption4Set) {
    {
        SCOPED_TRACE("add new global option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "", { "server1" });
    }

    {
        SCOPED_TRACE("add another global option with formatted value");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "mydomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "mydomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc);
    }

    {
        SCOPED_TRACE("update existing global option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "", { "server1" });
    }

    {
        SCOPED_TRACE("update another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("add an option for which a definition is required");
        // Add option definition for option 222 to the config backend.
        auto option_def = boost::make_shared<OptionDefinition>("foo", 222, DHCP4_OPTION_SPACE,
                                                               "string");
        ASSERT_NO_THROW(
            ConfigBackendDHCPv4Mgr::instance().getPool()->
                createUpdateOptionDef4(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def);
        );

        // Add the option 222 instance.
        OptionStringPtr option(new OptionString(Option::V4, 222, "baz"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false, "baz"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;

        testGlobalOption4Set(option_desc);
    }
}

// This test verifies that malformed requests to add and update global
// DHCP options are rejected and proper error messages are returned.
TEST_F(Option4CmdsTest, globalOption4SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption4SetFail("", "invalid command 'remote-option4-global-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty options list");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ ]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { } ]",
                                 "option data configuration requires one of "
                                 "'code' or 'name' parameters to be specified");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], \"options\": ["
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"type\": \"string\" } ]",
                                 "spurious 'type' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], \"options\": ["
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"space\": 4 } ]",
                                 "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"name\": \"nis-domain\" } ]",
                                 "option data does not match option definition");
    }

    {
        SCOPED_TRACE("multiple options");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": ["
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\" },"
                                 "{ \"name\": \"nis-domain\", \"data\": \"mydomain\" }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption4SetFail("\"options\": [ ]",
                                 "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption4SetFail("\"server-tags\": [ ]",
                                 "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testGlobalOption4SetFail("\"server-tags\": [ \" \" ]",
                                 "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption4SetFail("\"server-tags\": [ null ], "
                                 "\"options\": ["
                                 "{ \"name\": \"nis-domain\", \"data\": \"mydomain\" }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option4-global-set'"
                                 " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption4SetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                 "\"options\": ["
                                 "{ \"name\": \"nis-domain\", \"data\": \"mydomain\" }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option4-global-set'"
                                 " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": ["
                                 "    { \"name\": \"boot-file-name\", \"data\": \"my-boot-file\" }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }

    {
        SCOPED_TRACE("lacking option definition");
        testGlobalOption4SetFail("\"server-tags\": [ \"all\" ], \"options\": ["
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"space\": \"myspace\" } ]",
                                 "definition for the option 'myspace.boot-file-name' does not exist");
    }
}

// This test verifies that it is possible to delete global DHCP option.
TEST_F(Option4CmdsTest, globalOption4Del) {
    {
        SCOPED_TRACE("add and delete new global option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc);
        testGlobalOption4Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("add and delete another global option with formatted value");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "mydomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "mydomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc);
        testGlobalOption4Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("delete another global option without server tag");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "", { "server1" });
        // When using server tag 'all' it should not delete our option
        // because this option was assigned to server1 explicitly.
        testGlobalOption4Del(option_desc, 0);
    }

    {
        SCOPED_TRACE("delete another global option by server tag");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "", { "server1" });
        testGlobalOption4Del(option_desc, 1, "", { "server1" });
    }

    {
        SCOPED_TRACE("delete global option");
        // Deleting not existing is not an error.
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Del(option_desc, 0);
    }

    {
        SCOPED_TRACE("delete another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "{ \"type\": \"mysql\" }");
        testGlobalOption4Del(option_desc, 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("delete option 0 in not dhcp4 space");
        OptionPtr option(new Option(Option::V4, 0));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = "foo";
        testGlobalOption4Set(option_desc);
        testGlobalOption4Del(option_desc, 1);
    }
}

// This test verifies that it is possible to delete global DHCP option.
TEST_F(Option4CmdsTest, globalOption4DelWithClientClasses) {
    OptionDescriptorPtr option_desc;
    const std::set<std::string>& server_tags = { ServerTag::ALL };
    {
        SCOPED_TRACE("Add option with client-classes");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        option_desc.reset(new OptionDescriptor(option, false, false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        option_desc->addClientClass("cc-one");
        option_desc->addClientClass("cc-two");
        testGlobalOption4Set(option_desc);
    }

    ClientClassesPtr client_classes(new ClientClasses());
    {
        SCOPED_TRACE("Delete with empty client-classes list should fail");
        testGlobalOption4Del(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Delete with a non-matching client-classes list should fail");
        client_classes->insert("cc-one");
        testGlobalOption4Del(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Delete when client-classes matches should succeed");
        client_classes->insert("cc-two");
        testGlobalOption4Del(option_desc, 1, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Delete when client-classes is an empty pointer should succeed");
        // Re-add the option.
        testGlobalOption4Set(option_desc);
        testGlobalOption4Del(option_desc, 1, "", server_tags, ClientClassesPtr());
    }
}

// This test verifies that malformed requests to delete global DHCP
// options are rejected and proper error messages are returned.
TEST_F(Option4CmdsTest, globalOption4DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption4DelFail("", "invalid command 'remote-option4-global-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty options list");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { } ]",
                                 "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \"\" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \" \" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": 40 } ]",
                                 "'space' parameter is not a string");

    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": \"nis-domain\" } ]",
                                 "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1000} ]",
                                 "invalid 'code' value not in [0..255]");
    }

    {
        SCOPED_TRACE("conflict with PAD");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 0 } ]",
                                 "invalid 'code' value 0: reserved for PAD");
    }

    {
        SCOPED_TRACE("multiple options");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 },"
                                 "{ \"code\": 40 }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption4DelFail("\"options\": [ ]",
                                 "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption4DelFail("\"server-tags\": [ ]",
                                 "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testGlobalOption4DelFail("\"server-tags\": [ \" \" ]",
                                 "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption4DelFail("\"server-tags\": [ null ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option4-global-del'"
                                 " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption4DelFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option4-global-del'"
                                 " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption4DelFail("\"server-tags\": [ \"all\" ], "
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
        testGlobalOption4DelFail(R"(
            "server-tags": [ "all" ],
            "options": [ {
                "code": 1,
                "space": "dhcp4",
                "client-classes": "bogus"
                } ]
            )",
            "'client-classes' parameter is not a list");
    }
}

// This test verifies that it is possible to get global DHCP option.
TEST_F(Option4CmdsTest, globalOption4Get) {
    {
        SCOPED_TRACE("add and get new global option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "", { "server1" });
        testGlobalOption4Get(option_desc, option_desc, "", { "server1" });
    }

    {
        SCOPED_TRACE("add and get another global option with formatted value");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "mydomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "mydomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc);
        testGlobalOption4Get(option_desc, option_desc);
    }

    {
        SCOPED_TRACE("get no global option");
        // Getting not existing is not an error.
        OptionPtr option(new OptionInt<uint16_t>(Option::V4,
                                                 DHO_BOOT_SIZE,
                                                 1024));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Get(option_desc, OptionDescriptorPtr());
    }

    {
        SCOPED_TRACE("add and get another option with specifying remote");
        OptionPtr option(new OptionInt<uint16_t>(Option::V4,
                                                 DHO_BOOT_SIZE,
                                                 1024));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testGlobalOption4Set(option_desc, "{ \"type\": \"mysql\" }");
        testGlobalOption4Get(option_desc, option_desc,
                             "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("get option 255 in not dhcp4 space");
        OptionPtr option(new Option(Option::V4, 255));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = "foo";
        testGlobalOption4Set(option_desc);
        testGlobalOption4Get(option_desc, option_desc);
    }
}

// This test verifies that it is possible to get global DHCP options
// with client-classes option.
TEST_F(Option4CmdsTest, globalOption4GetWithClientClasses) {
    OptionDescriptorPtr option_desc;
    const std::set<std::string>& server_tags = { ServerTag::ALL };
    {
        SCOPED_TRACE("Add option with client-classes");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        option_desc.reset(new OptionDescriptor(option, false, false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        option_desc->addClientClass("cc-one");
        option_desc->addClientClass("cc-two");
        testGlobalOption4Set(option_desc);
    }

    ClientClassesPtr client_classes(new ClientClasses());
    {
        SCOPED_TRACE("Get with empty client-classes list should fail");
        testGlobalOption4Get(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Get with a non-matching client-classes list should fail");
        client_classes->insert("cc-one");
        testGlobalOption4Get(option_desc, 0, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Get when client-classes matches should succeed");
        client_classes->insert("cc-two");
        testGlobalOption4Get(option_desc, option_desc, "", server_tags, client_classes);
    }

    {
        SCOPED_TRACE("Get when client-classes is an empty pointer should succeed");
        testGlobalOption4Get(option_desc, option_desc, "", server_tags, ClientClassesPtr());
    }
}

// This test verifies that malformed requests to get global DHCP
// options are rejected and proper error messages are returned.
TEST_F(Option4CmdsTest, globalOption4GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption4GetFail("", "invalid command 'remote-option4-global-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty options list");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { } ]",
                                 "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \"\" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \" \" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": 40 } ]",
                                 "'space' parameter is not a string");

    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": \"nis-domain\" } ]",
                                 "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 1000} ]",
                                 "invalid 'code' value not in [0..255]");
    }

    {
        SCOPED_TRACE("conflict with END");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": [ { \"code\": 255, "
                                 "\"space\": \"dhcp4\" } ]",
                                 "invalid 'code' value 255: reserved for END");
    }

    {
        SCOPED_TRACE("multiple options");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 },"
                                 "{ \"code\": 40 }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption4GetFail("\"options\": [ ]",
                                 "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption4GetFail("\"server-tags\": [ ]",
                                 "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testGlobalOption4GetFail("\"server-tags\": [ \" \" ]",
                                 "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption4GetFail("\"server-tags\": [ null ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option4-global-get'"
                                 " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption4GetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 }"
                                 "]",
                                 "'server-tags' list must contain exactly one"
                                 " server tag for the 'remote-option4-global-get'"
                                 " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption4GetFail("\"server-tags\": [ \"all\" ], "
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
TEST_F(Option4CmdsTest, globalOption4GetAll) {
    // Empty.
    CfgOption expected;
    CfgOption expected_all;
    testGlobalOption4GetAll(expected, 0);
    testGlobalOption4GetAll(expected_all, 0);

    // Add an option.
    OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                            "my-boot-file"));
    OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                         false));
    option_desc->space_name_ = DHCP4_OPTION_SPACE;
    option_desc->setServerTag("server1");
    testGlobalOption4Set(option_desc, "", { "server1" });
    expected.add(*option_desc, DHCP4_OPTION_SPACE);
    testGlobalOption4GetAll(expected, 1, "", { "server1" });

    // Add a second option definition.
    option.reset(new OptionString(Option::V4, DHO_NIS_DOMAIN, "mydomain"));
    option_desc.reset(new OptionDescriptor(option, true, false, "mydomain"));
    option_desc->space_name_ = DHCP4_OPTION_SPACE;
    option_desc->setServerTag(ServerTag::ALL);
    testGlobalOption4Set(option_desc);
    expected.add(*option_desc, DHCP4_OPTION_SPACE);
    expected_all.add(*option_desc, DHCP4_OPTION_SPACE);
    testGlobalOption4GetAll(expected, 2, "", { "server1" });

    // With another server only options belonging to all are returned.
    testGlobalOption4GetAll(expected_all, 1, "", { "server2" });
    testGlobalOption4GetAll(expected_all, 1);

    // Try with a remote.
    OptionPtr option2(new OptionInt<uint16_t>(Option::V4,
                                              DHO_BOOT_SIZE,
                                              1024));
    option_desc.reset(new OptionDescriptor(option2, false, false));
    option_desc->space_name_ = DHCP4_OPTION_SPACE;
    option_desc->setServerTag(ServerTag::ALL);
    testGlobalOption4Set(option_desc, "{ \"type\": \"mysql\" }");
    expected.add(*option_desc, DHCP4_OPTION_SPACE);
    testGlobalOption4GetAll(expected, 3, "{ \"type\": \"mysql\" }", { "server1" });
}

// This test verifies that malformed requests to get all global DHCP
// options are rejected and proper error messages are returned.
TEST_F(Option4CmdsTest, globalOption4GetAllFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalOption4GetAllFail(", \"arguments\": { }",
                                    "invalid command 'remote-option4-global-get-all': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalOption4GetAllFail(", \"arguments\": {"
                                       "    \"remote\": {"
                                       "        \"type\": \"mysql\""
                                       "    }"
                                    " }",
                                    "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalOption4GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ ]"
                                    "}",
                                    "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag");
        testGlobalOption4GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ \" \" ]"
                                    "}",
                                    "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalOption4GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ null ]"
                                    "}",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-option4-global-get-all'"
                                    " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalOption4GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ \"server1\", \"server2\" ]"
                                    "}",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-option4-global-get-all'"
                                    " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalOption4GetAllFail(", \"arguments\": { "
                                    "\"server-tags\": [ \"all\" ], "
                                    "\"remote\": {"
                                    "    \"type\": \"postgresql\""
                                    "} }",
                                    "no such database found for selector: "
                                    "type=postgresql");
    }
}

}
