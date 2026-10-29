// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cb_cmds_test.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <database/backend_selector.h>
#include <dhcp/option_data_types.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <util/optional.h>
#include <testutils/gtest_utils.h>
#include <set>
#include <string>
#include <sstream>

using namespace isc::cb;
using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;
using namespace isc::util;

namespace {

/// @brief Test fixture class for callouts pertaining to DHCP option definitions.
class OptionDef4CmdsTest : public ConfigCmdsDhcp4Test {
public:

    /// @brief Returns remote-option-def4-set command as text.
    ///
    /// @param def Pointer to the option definition to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeOptionDef4SetConfig(const OptionDefinitionPtr& def,
                                        const std::string& remote_map,
                                        const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option-def4-set\","
            "\"arguments\": {"
            "    \"option-defs\": ";

        CfgOptionDef cfg_option_def;
        cfg_option_def.add(def);

        config += cfg_option_def.toElement()->str();

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

    /// @brief Positive test scenario for setting or updating an option definition.
    ///
    /// @param def Pointer to the option definition to be created or updated.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testOptionDef4Set(const OptionDefinitionPtr& def,
                           const std::string& remote_map = "",
                           const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeOptionDef4SetConfig(def, remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setOptionDef4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ("DHCPv4 option definition successfully set.",
                  msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned list of options.
        auto option_def_list = args->get("option-defs");
        ASSERT_TRUE(option_def_list);
        ASSERT_EQ(Element::list, option_def_list->getType());
        ASSERT_EQ(1U, option_def_list->size());

        auto option_def_0 = option_def_list->get(0);
        ASSERT_TRUE(option_def_0);
        ASSERT_EQ(Element::map, option_def_0->getType());
        EXPECT_EQ(2U, option_def_0->size());

        auto option_def_0_code = option_def_0->get("code");
        ASSERT_TRUE(option_def_0_code);
        ASSERT_EQ(Element::integer, option_def_0_code->getType());
        EXPECT_EQ(static_cast<int64_t>(def->getCode()),
                  option_def_0_code->intValue());

        auto option_def_0_space = option_def_0->get("space");
        ASSERT_TRUE(option_def_0_space);
        ASSERT_EQ(Element::string, option_def_0_space->getType());
        EXPECT_EQ(def->getOptionSpaceName(), option_def_0_space->stringValue());

        // Make sure that the created/updated option definition is in the database
        // and has correct values.
        ASSERT_FALSE(server_tags.empty());
        auto fetched_option_def = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getOptionDef4(BackendSelector(),
                          ServerSelector::ONE(*server_tags.begin()),
                          def->getCode(), def->getOptionSpaceName());
        ASSERT_TRUE(fetched_option_def);
        EXPECT_TRUE(fetched_option_def->equals(*def));
    }

    /// @brief Negative test scenario for setting or updating an option
    /// definition.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testOptionDef4SetFail(const std::string& args,
                               const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option-def4-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setOptionDef4,
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

    /// @brief Returns remote-option-def4-del command as text.
    ///
    /// @param def Pointer to the option definition to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    /// @param force optional boolean flag to pass into delete command as the
    /// force parameter. Defaults to unspecified.
    ///
    /// @return Command in the textual format.
    std::string makeOptionDef4DelConfig(const OptionDefinitionPtr& def,
                                        const std::string& remote_map,
                                        const std::set<std::string>& server_tags,
                                        Optional<bool> force = Optional<bool>()) {
        std::string config = "{"
            "\"command\": \"remote-option-def4-del\","
            "\"arguments\": {"
            "    \"option-defs\": [ { ";

        CfgOptionDef cfg_option_def;
        cfg_option_def.add(def);

        std::ostringstream code;
        code << def->getCode();
        config += "\"code\": " + code.str();
        config += ", \"space\": \"" + def->getOptionSpaceName() + "\"";

        if (!force.unspecified()) {
            config += ", \"force\": " + std::string(force.get() ? "true" : "false");
        }

        config  += " } ]";

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

    /// @brief Positive test scenario for deleting an option definition.
    ///
    /// @param def Pointer to the option definition to be deleted.
    /// @param expected_count Expected number of deleted option definitions.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    /// @param force optional boolean flag to pass into delete command as the
    /// force parameter. Defaults to unspecified.
    void testOptionDef4Del(const OptionDefinitionPtr& def,
                           unsigned expected_count,
                           const std::string& remote_map = "",
                           const std::set<std::string>& server_tags = { ServerTag::ALL },
                           Optional<bool> force = Optional<bool>()) {
        // Generate the command as text.
        std::string command_text = makeOptionDef4DelConfig(def, remote_map, server_tags, force);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delOptionDef4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count
                     << " DHCPv4 option definition(s) deleted.";
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

        // Make sure that the deleted option definition is not in the database.
        ASSERT_FALSE(server_tags.empty());
        auto fetched_option_def = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getOptionDef4(BackendSelector(),
                          ServerSelector::ONE(*server_tags.begin()),
                          def->getCode(), def->getOptionSpaceName());
        ASSERT_FALSE(fetched_option_def);
    }

    /// @brief Negative test scenario for deleting an option definition.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testOptionDef4DelFail(const std::string& args,
                               const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option-def4-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delOptionDef4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-option-def4-get command as text.
    ///
    /// @param def Pointer to the option definition to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeOptionDef4GetConfig(const OptionDefinitionPtr& def,
                                        const std::string& remote_map,
                                        const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option-def4-get\","
            "\"arguments\": {"
            "    \"option-defs\": [ { ";

        CfgOptionDef cfg_option_def;
        cfg_option_def.add(def);

        std::ostringstream code;
        code << def->getCode();
        config += "\"code\": " + code.str();
        config += ", \"space\": \"" + def->getOptionSpaceName() + "\" } ]";

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

    /// @brief Positive test scenario for getting an option definition.
    ///
    /// @param def Pointer to the option definition to be got.
    /// @param expected Pointer to the expected option definition.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testOptionDef4Get(const OptionDefinitionPtr& def,
                           const OptionDefinitionPtr& expected,
                           const std::string& remote_map = "",
                           const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeOptionDef4GetConfig(def, remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::getOptionDef4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (!expected ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "DHCPv4 option definition " << def->getCode()
                     << " in '" << def->getOptionSpaceName() << "' "
                     << (!expected ? "not " : "") << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // Validate returned option definition.
        ConstElementPtr defs = args->get("option-defs");
        ASSERT_TRUE(defs);
        ASSERT_EQ(Element::list, defs->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (!expected) {
            EXPECT_EQ(0U, defs->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(1U, defs->size());
            ConstElementPtr got = defs->get(0);
            ASSERT_TRUE(got);
            OptionDefinitionPtr option_def;
            OptionDefParser parser(AF_INET);
            ASSERT_NO_THROW(option_def = parser.parse(got));
            ASSERT_TRUE(option_def);
            EXPECT_TRUE(expected->equals(*option_def));

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

    /// @brief Negative test scenario for getting an option definition.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testOptionDef4GetFail(const std::string& args,
                               const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option-def4-get\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::getOptionDef4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-option-def4-get-all command as text.
    ///
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeOptionDef4GetAllConfig(const std::string& remote_map,
                                           const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-option-def4-get-all\"";

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

    /// @brief Positive test scenario for getting all option definitions.
    ///
    /// @param expected Expected result.
    /// @param expected_count Expected number of got option definitions.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testOptionDef4GetAll(const CfgOptionDef& expected,
                              unsigned expected_count,
                              const std::string& remote_map = "",
                              const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeOptionDef4GetAllConfig(remote_map, server_tags);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getAllOptionDefs4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_count == 0 ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << expected_count
                     << " DHCPv4 option definition(s) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected_count, static_cast<unsigned>(count->intValue()));

        // Validate returned option definitions.
        ConstElementPtr defs = args->get("option-defs");
        ASSERT_TRUE(defs);
        ASSERT_EQ(Element::list, defs->getType());
        CfgOptionDef got;
        for (auto const& def : defs->listValue()) {
            ASSERT_TRUE(def);
            ASSERT_EQ(Element::map, def->getType());
            OptionDefinitionPtr option_def;
            OptionDefParser parser(AF_INET);
            ASSERT_NO_THROW(option_def = parser.parse(def));
            ASSERT_TRUE(option_def);
            ASSERT_NO_THROW(got.add(option_def));

            // Make sure that metadata is returned.
            auto metadata = def->get("metadata");
            ASSERT_TRUE(metadata);
            auto exp = expected.get(option_def->getOptionSpaceName(),
                                    option_def->getCode());
            ASSERT_FALSE(server_tags.empty());
            auto expected_metadata =
                createMetadata(exp->hasAllServerTag() ?
                               ServerTag::ALL : *server_tags.begin());
            EXPECT_TRUE(isEquivalent(metadata, expected_metadata))
                << "Actual: " << metadata->str()
                << "\nExpected: " << expected_metadata->str();
        }

        // Compare to expected.
        EXPECT_TRUE(isEquivalent(expected.toElement(), got.toElement()));
    }

    /// @brief Negative test scenario for getting all option definitions.
    ///
    /// @param args Arguments for the command in the textual format not
    /// including "arguments".
    /// @param answer_text Expected error message.
    void testOptionDef4GetAllFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option-def4-get-all\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp4Impl::getAllOptionDefs4,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update option definition.
TEST_F(OptionDef4CmdsTest, optionDef4Set) {
    {
        SCOPED_TRACE("add new option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint32"));
        testOptionDef4Set(def, "", { "server1" });
    }

    {
        SCOPED_TRACE("add another option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 223,
                                                     DHCP4_OPTION_SPACE,
                                                     "string"));
        testOptionDef4Set(def);
    }

    {
        SCOPED_TRACE("update existing option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint16"));
        testOptionDef4Set(def, "", { "server1" });
    }

    {
        SCOPED_TRACE("update another option definition with specifying remote");
        OptionDefinitionPtr def(new OptionDefinition("foo", 223,
                                                     DHCP4_OPTION_SPACE,
                                                     "binary"));
        testOptionDef4Set(def, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to add and update option
// definition are rejected and proper error messages are returned.
TEST_F(OptionDef4CmdsTest, optionDef4SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testOptionDef4SetFail("", "invalid command 'remote-option-def4-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty option-def list");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ ]", "'option-defs' list "
                              "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty option-def map");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { } ]",
                              "missing parameter 'name'");
    }

    {
        SCOPED_TRACE("malformed option definition");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"name\": \"foo\" } ]",
                              "missing parameter 'code'");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "{ \"name\": \"foo\", \"code\": 222, \"type\": \"uint32\", "
                              "\"data\": 123 } ]",
                              "spurious 'data' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "{ \"name\": \"foo\", \"code\": 222, \"type\": \"uint32\", "
                              "\"space\": 4 } ]",
                              "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("multiple option definitions");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "{ \"name\": \"foo\", \"code\": 222, \"type\": \"uint32\" },"
                              "{ \"name\": \"bar\", \"code\": \"223\", \"type\": \"uint32\" }"
                              "]",
                              "'option-defs' list must include exactly one element");
    }

    {
        SCOPED_TRACE("conflict standard option code");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"name\": \"foo\", "
                              " \"code\": 3, \"type\": \"string\" } ]",
                              "an option with code 3 already exists"
                              " in space 'dhcp4'");
    }

    {
        SCOPED_TRACE("conflict standard option name");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"name\": \"routers\", "
                              " \"code\": 253, \"type\": \"string\" } ]",
                              "an option with name 'routers' already exists"
                              " in space 'dhcp4'");
    }

    {
        SCOPED_TRACE("no server tags");
        testOptionDef4SetFail("\"option-defs\": [ ]",
                              "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testOptionDef4SetFail("\"server-tags\": [ ]",
                              "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testOptionDef4SetFail("\"server-tags\": [ \" \" ]",
                              "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testOptionDef4SetFail("\"server-tags\": [ null ], "
                              "\"option-defs\": ["
                              "{ \"name\": \"foo\", \"code\": 222, \"type\": \"uint32\" }"
                              "]",
                              "'server-tags' list must contain exactly one"
                              " server tag for the 'remote-option-def4-set'"
                              " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testOptionDef4SetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                              "\"option-defs\": ["
                              "{ \"name\": \"foo\", \"code\": 222, \"type\": \"uint32\" }"
                              "]",
                              "'server-tags' list must contain exactly one"
                              " server tag for the 'remote-option-def4-set'"
                              " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testOptionDef4SetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "    { \"name\": \"foo\", \"code\": 222, \"type\": \"uint32\" }"
                              "],"
                              "\"remote\": {"
                              "    \"type\": \"postgresql\""
                              "}",
                              "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to delete option definition.
TEST_F(OptionDef4CmdsTest, optionDef4Del) {
    {
        SCOPED_TRACE("add and delete new option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint32"));
        testOptionDef4Set(def);
        testOptionDef4Del(def, 1);
    }

    {
        SCOPED_TRACE("add and delete another option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 223,
                                                     DHCP4_OPTION_SPACE,
                                                     "string"));
        testOptionDef4Set(def);
        testOptionDef4Del(def, 1);
    }

    {
        SCOPED_TRACE("delete another option definition without server tag");
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint32"));
        testOptionDef4Set(def, "", { "server1" });
        // When using server tag 'all' it should not delete our definition
        // because this definition was assigned to server1 explicitly.
        testOptionDef4Del(def, 0);
    }

    {
        SCOPED_TRACE("delete another option definition by server tag");
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint32"));
        testOptionDef4Set(def, "", { "server1" });
        testOptionDef4Del(def, 1, "", { "server1" });
    }

    {
        SCOPED_TRACE("delete option definition");
        // Deleting not existing is not an error.
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint16"));
        testOptionDef4Del(def, 0);
    }

    {
        SCOPED_TRACE("delete another option definition with specifying remote");
        OptionDefinitionPtr def(new OptionDefinition("foo", 223,
                                                     DHCP4_OPTION_SPACE,
                                                     "binary"));
        testOptionDef4Set(def, "{ \"type\": \"mysql\" }");
        testOptionDef4Del(def, 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("delete option 0 in not dhcp4 space");
        OptionDefinitionPtr def(new OptionDefinition("zero", 0, "foo",
                                                     "empty"));
        testOptionDef4Set(def);
        testOptionDef4Del(def, 1);
    }

}

// This test verifies that malformed requests to delete option definition
// are rejected and proper error messages are returned.
TEST_F(OptionDef4CmdsTest, optionDef4DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testOptionDef4DelFail("", "invalid command 'remote-option-def4-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty option-def list");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ ]", "'option-defs' list "
                              "must include exactly one element");
    }

    {
        SCOPED_TRACE("malformed option definition");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"space\": \"dhcp4\" } ]",
                              "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("spurious parameter");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1, "
                              "\"name\": \"foo\" } ]",
                              "spurious 'name' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1, "
                              "\"space\": \"\" } ]",
                              "'space' parameter must be a valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1, "
                              "\"space\": \" \" } ]",
                              "'space' parameter must be a valid space name");
    }

    {
        SCOPED_TRACE("out of range code");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1000} ]",
                              "invalid 'code' value not in [0..255]");
    }

    {
        SCOPED_TRACE("conflict with PAD");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 0 } ]",
                              "invalid 'code' value 0: reserved for PAD");
    }

    {
        SCOPED_TRACE("multiple option definitions");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "{ \"code\": 222 },"
                              "{ \"code\": \"223\" }"
                              "]",
                              "'option-defs' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testOptionDef4DelFail("\"option-defs\": [ ]",
                              "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testOptionDef4DelFail("\"server-tags\": [ ]",
                              "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testOptionDef4DelFail("\"server-tags\": [ \" \" ]",
                              "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testOptionDef4DelFail("\"server-tags\": [ null ], "
                              "\"option-defs\": ["
                              "{ \"code\": 222 }"
                              "]",
                              "'server-tags' list must contain exactly one"
                              " server tag for the 'remote-option-def4-del'"
                              " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testOptionDef4DelFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                              "\"option-defs\": ["
                              "{ \"code\": 222 }"
                              "]",
                              "'server-tags' list must contain exactly one"
                              " server tag for the 'remote-option-def4-del'"
                              " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "    { \"code\": 222 }"
                              "],"
                              "\"remote\": {"
                              "    \"type\": \"postgresql\""
                              "}",
                              "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get option definition.
TEST_F(OptionDef4CmdsTest, optionDef4Get) {
    {
        SCOPED_TRACE("add and get new option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 222,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint32"));
        testOptionDef4Set(def, "", { "server1" });
        testOptionDef4Get(def, def, "", { "server1" });
    }

    {
        SCOPED_TRACE("add and get another option definition");
        OptionDefinitionPtr def(new OptionDefinition("foo", 223,
                                                     DHCP4_OPTION_SPACE,
                                                     "string"));
        testOptionDef4Set(def);
        testOptionDef4Get(def, def);
    }

    {
        SCOPED_TRACE("get no option definition");
        // Getting not existing is not an error.
        OptionDefinitionPtr def(new OptionDefinition("foo", 224,
                                                     DHCP4_OPTION_SPACE,
                                                     "uint16"));
        testOptionDef4Get(def, OptionDefinitionPtr());
    }

    {
        SCOPED_TRACE("delete another option definition with specifying remote");
        OptionDefinitionPtr def(new OptionDefinition("foo", 225,
                                                     DHCP4_OPTION_SPACE,
                                                     "binary"));
        testOptionDef4Set(def, "{ \"type\": \"mysql\" }");
        testOptionDef4Get(def, def, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("get option 255 in not dhcp4 space");
        OptionDefinitionPtr def(new OptionDefinition("max", 255, "foo",
                                                     "empty"));
        testOptionDef4Set(def);
        testOptionDef4Get(def, def);
    }
}

// This test verifies that malformed requests to get option definition
// are rejected and proper error messages are returned.
TEST_F(OptionDef4CmdsTest, optionDef4GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testOptionDef4GetFail("", "invalid command 'remote-option-def4-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty option-def list");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ ]", "'option-defs' list "
                              "must include exactly one element");
    }

    {
        SCOPED_TRACE("malformed option definition");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"name\": \"foo\" } ]",
                              "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("spurious parameter");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1, "
                              "\"name\": \"foo\" } ]",
                              "spurious 'name' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1, "
                              "\"space\": \"\" } ]",
                              "'space' parameter must be a valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1, "
                              "\"space\": \" \" } ]",
                              "'space' parameter must be a valid space name");
    }

    {
        SCOPED_TRACE("out of range code");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 1000} ]",
                              "invalid 'code' value not in [0..255]");
    }

    {
        SCOPED_TRACE("conflict with END");
        testOptionDef4DelFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": [ { \"code\": 255, "
                              "\"space\": \"dhcp4\" } ]",
                              "invalid 'code' value 255: reserved for END");
    }

    {
        SCOPED_TRACE("multiple option definitions");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "{ \"code\": 222 },"
                              "{ \"code\": \"223\" }"
                              "]",
                              "'option-defs' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testOptionDef4GetFail("\"option-defs\": [ ]",
                              "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testOptionDef4GetFail("\"server-tags\": [ ]",
                              "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("empty server tag");
        testOptionDef4GetFail("\"server-tags\": [ \" \" ]",
                              "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testOptionDef4GetFail("\"server-tags\": [ null ], "
                              "\"option-defs\": ["
                              "{  \"code\": 222 }"
                              "]",
                              "'server-tags' list must contain exactly one"
                              " server tag for the 'remote-option-def4-get'"
                              " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testOptionDef4GetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                              "\"option-defs\": ["
                              "{  \"code\": 222 }"
                              "]",
                              "'server-tags' list must contain exactly one"
                              " server tag for the 'remote-option-def4-get'"
                              " command");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testOptionDef4GetFail("\"server-tags\": [ \"all\" ], "
                              "\"option-defs\": ["
                              "    { \"code\": 222 }"
                              "],"
                              "\"remote\": {"
                              "    \"type\": \"postgresql\""
                              "}",
                              "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get all option definitions.
TEST_F(OptionDef4CmdsTest, optionDef4GetAll) {
    // Empty.
    CfgOptionDef expected;
    CfgOptionDef expected_all;
    testOptionDef4GetAll(expected, 0);
    testOptionDef4GetAll(expected_all, 0);

    // Add an option definition.
    OptionDefinitionPtr def(new OptionDefinition("foo", 222, DHCP4_OPTION_SPACE,
                                                 "uint32"));
    def->setServerTag("server1");
    testOptionDef4Set(def, "", { "server1" });
    expected.add(def);
    testOptionDef4GetAll(expected, 1, "", { "server1" });

    // Add a second option definition.
    def.reset(new OptionDefinition("bar", 223, DHCP4_OPTION_SPACE, "string"));
    def->setServerTag(ServerTag::ALL);
    testOptionDef4Set(def);
    expected.add(def);
    expected_all.add(def);
    testOptionDef4GetAll(expected, 2, "", { "server1" });

    // With another server only options belonging to all are returned.
    testOptionDef4GetAll(expected_all, 1, "", { "server2" });
    testOptionDef4GetAll(expected_all, 1);

    // Try with a remote.
    def.reset(new OptionDefinition("xyz", 224, DHCP4_OPTION_SPACE, "binary"));
    def->setServerTag(ServerTag::ALL);
    testOptionDef4Set(def, "{ \"type\": \"mysql\" }");
    expected.add(def);
    testOptionDef4GetAll(expected, 3, "{ \"type\": \"mysql\" }", { "server1" });
}

// This test verifies that malformed requests to get all option definitions
// are rejected and proper error messages are returned.
TEST_F(OptionDef4CmdsTest, optionDef4GetAllFail) {
    {
        SCOPED_TRACE("empty arguments");
        testOptionDef4GetAllFail(", \"arguments\": { }",
                                 "invalid command 'remote-option-def4-get-all': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testOptionDef4GetAllFail(", \"arguments\": { "
                                 "\"server-tags\": [ \"all\" ],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "} }",
                                 "no such database found for selector: "
                                 "type=postgresql");
    }
}

// This test verifies force parameter is parsed and utilized.
TEST_F(OptionDef4CmdsTest, optionDef4DelForce) {

    // Add an option definition.
    OptionDefinitionPtr option_def(new OptionDefinition("foo", 222,
                                                        DHCP4_OPTION_SPACE,
                                                        "string"));
    testOptionDef4Set(option_def);

    // Add an option that uses the definition.
    std::string option_cmd =
        R"({
            "command": "remote-option4-global-set",
            "arguments": {
                "options": [{
                "code": 222,
                "space": "dhcp4",
                "data": "puppy"
                }],
                "server-tags": [ "all" ]
            }})";

    ASSERT_NO_THROW_LOG(impl_.run(&TestConfigCmdsDhcp4Impl::setGlobalOption4, option_cmd));

    std::string no_force_arg =
        R"(
            "option-defs": [{
                "code": 222,
                "space": "dhcp4"
            }],
            "server-tags": [ "all" ]
        )";

    testOptionDef4DelFail(no_force_arg, "option exists for option definition: dhcp4.222");

    std::string false_force_arg =
        R"(
            "option-defs": [{
                "code": 222,
                "space": "dhcp4",
                "force": false
            }],
            "server-tags": [ "all" ]
        )";

    testOptionDef4DelFail(false_force_arg, "option exists for option definition: dhcp4.222");

    Optional<bool> force(true);
    testOptionDef4Del(option_def, 1, "", { ServerTag::ALL }, force);
}

}
