// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/stamped_value.h>
#include <database/backend_selector.h>
#include <dhcpsrv/cb_ctl_dhcp.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/parsers/simple_parser6.h>

#include <set>
#include <sstream>
#include <string>

#include <cb_cmds/cb_parsers.h>
#include <cb_cmds_test.h>

using namespace isc::cb;
using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;

namespace {

/// @brief Test fixture class for callouts pertaining to the global
/// parameters.
class Global6CmdsTest : public ConfigCmdsDhcp6Test {
public:

    /// @brief Returns remote-global-parameter6-set command as text.
    ///
    /// @param parameters Map holding one more more name/value pairs.
    /// @param stringify_value Make the value a string.
    /// @param remote_map A map to be assigned to be assigned to the "remote"
    /// argument of the command. If the string is empty the "remote" argument
    /// is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string
    makeGlobalParameter6SetConfig(const std::map<std::string, std::string>& parameters,
                                  bool stringify_value,
                                  const std::string& remote_map,
                                  const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-global-parameter6-set\","
            "\"arguments\": {"
            "    \"parameters\": {";

        bool comma = false;
        for (auto const& param : parameters) {
            if (comma) {
                config += ", ";
            }
            config += "\"" + param.first + "\":";
            if (stringify_value) {
                config += "\"" + param.second + "\"";
            } else {
                config += param.second;
            }
            comma = true;
        }
        config += "}";

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

    /// @brief Positive test scenario for setting or updating a global parameter.
    ///
    /// @param parameters Map holding one more more name/value pairs.
    /// @param stringify_value Make the value a string.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testGlobalParameter6Set(const std::map<std::string, std::string>& parameters,
                                 bool stringify_value = true,
                                 const std::string& remote_map = "",
                                 const std::set<std::string>& server_tags = { ServerTag::ALL },
                                 bool is_map = false, size_t map_param_count = 1) {

        // Currently we allow only one server tag at the time for the global
        // parameters.
        ASSERT_EQ(server_tags.size(), 1U);

        // Generate the command as text.
        std::string command_text = makeGlobalParameter6SetConfig(parameters,
                                                                 stringify_value,
                                                                 remote_map,
                                                                 server_tags);
        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setGlobalParameter6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_SUCCESS, rcode);

        std::ostringstream exp_msg;
        size_t param_count = parameters.size();
        if (is_map) {
            param_count = map_param_count;
        }
        exp_msg << param_count << " DHCPv6 global parameter(s) successfully set.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(exp_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        EXPECT_EQ(2U, args->size());

        // Validate returned parameters.
        ConstElementPtr params = args->get("parameters");
        ASSERT_TRUE(params);
        ASSERT_EQ(Element::map, params->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(param_count, static_cast<size_t>(count->intValue()));
        ASSERT_EQ(parameters.size(), static_cast<size_t>(params->size()));

        for (auto const& param : parameters) {
            ConstElementPtr value = params->get(param.first);
            ASSERT_TRUE(value);
            if (value->getType() == Element::string) {
                EXPECT_EQ(param.second, value->stringValue());
            } else {
                EXPECT_EQ(param.second, value->str());
            }
        }

        ServerSelector server_selector = ServerSelector::ONE(*server_tags.begin());

        // Iterate over the parameters and verify that each of them was stored.
        for (auto const& param : parameters) {
            auto parameter_name = param.first;
            auto parameter_value = param.second;
            if (is_map) {
                ElementPtr json_elem = Element::fromJSON(parameter_value);
                if (json_elem->getType() == Element::map) {
                    parameter_name = parameter_name + "." + (*json_elem->mapValue().begin()).first;
                    if ((*json_elem->mapValue().begin()).second->getType() == Element::string) {
                        parameter_value = (*json_elem->mapValue().begin()).second->stringValue();
                    } else {
                        parameter_value = (*json_elem->mapValue().begin()).second->str();
                    }
                }
            }

            // Make sure that the created/updated global parameter is in the database
            // and has the correct value.
            auto fetched_parameter = ConfigBackendDHCPv6Mgr::instance().getPool()->
                getGlobalParameter6(BackendSelector(), server_selector, parameter_name);
            ASSERT_TRUE(fetched_parameter) << "parameter " << parameter_name
                << " was not added";

            // Special cases for booleans.
            if (!stringify_value && (parameter_value == "true")) {
                EXPECT_EQ("1", fetched_parameter->getValue());
            } else if (!stringify_value && (parameter_value == "false")) {
                EXPECT_EQ("0", fetched_parameter->getValue());
            } else {
                EXPECT_EQ(parameter_value, fetched_parameter->getValue());
            }

            // If the parameter was specified for the particular server tag, then
            // querying using ALL() server selector should return no result.
            if (server_selector.getType() == ServerSelector::Type::SUBSET) {
                fetched_parameter = ConfigBackendDHCPv6Mgr::instance().getPool()->
                    getGlobalParameter6(BackendSelector(), ServerSelector::ALL(),
                                        parameter_name);
                EXPECT_FALSE(fetched_parameter);
            }
        }
    }

    /// @brief Negative test scenario for setting or updating a global parameter.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testGlobalParameter6SetFail(const std::string& args,
                                     const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-global-parameter6-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setGlobalParameter6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-global-parameter6-del command as text.
    ///
    /// @param parameter_name Name of the global parameter to be included
    /// in the command.
    /// @param remote_map A map to be assigned to be assigned to the "remote"
    /// argument of the command. If the string is empty the "remote" argument
    /// is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalParameter6DelConfig(const std::string& parameter_name,
                                              const std::string& remote_map,
                                              const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-global-parameter6-del\","
            "\"arguments\": {"
            "    \"parameters\": [ \"" + parameter_name + "\" ]";

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

    /// @brief Positive test scenario for deleting a global parameter.
    ///
    /// @param parameter_name Name of the parameter to be deleted.
    /// @param expected_count Expected number of deleted parameters.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testGlobalParameter6Del(const std::string& parameter_name,
                                 unsigned expected_count,
                                 const std::string& remote_map = "",
                                 const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalParameter6DelConfig(parameter_name,
                                                                 remote_map,
                                                                 server_tags);
        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delGlobalParameter6,
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
                     << " DHCPv6 global parameter(s) deleted.";
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

        // Make sure that the deleted global parameter is not in the database.
        ServerSelector server_selector = ServerSelector::ONE(*server_tags.begin());
        auto fetched_parameter = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getGlobalParameter6(BackendSelector(), server_selector, parameter_name);
        ASSERT_FALSE(fetched_parameter);
    }

    /// @brief Negative test scenario for deleting a global parameter.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testGlobalParameter6DelFail(const std::string& args,
                                     const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-global-parameter6-del\","
            "\"arguments\": {" + args + "}"
            "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delGlobalParameter6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-global-parameter6-get command as text.
    ///
    /// @param parameter_name Name of the global parameter to be included
    /// in the command.
    /// @param remote_map A map to be assigned to be assigned to the "remote"
    /// argument of the command. If the string is empty the "remote" argument
    /// is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalParameter6GetConfig(const std::string& parameter_name,
                                              const std::string& remote_map,
                                              const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-global-parameter6-get\","
            "\"arguments\": {"
            "    \"parameters\": [ \"" + parameter_name + "\" ]";

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

    /// @brief Positive test scenario for getting a global parameter.
    ///
    /// @param parameter_name Name of the parameter to be got.
    /// @param expected_value Value of the parameter to be got.
    /// @param expected_value_type Type of the value of the parameter to be got.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testGlobalParameter6Get(const std::string& parameter_name,
                                 const std::string& expected_value,
                                 int expected_value_type = Element::string,
                                 const std::string& remote_map = "",
                                 const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalParameter6GetConfig(parameter_name,
                                                                 remote_map,
                                                                 server_tags);
        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::getGlobalParameter6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates success.
        int rcode = 0;
        auto args = parseAnswer(rcode, response);
        int expected_rcode = (expected_value.empty() ?
            CONTROL_RESULT_EMPTY : CONTROL_RESULT_SUCCESS);
        EXPECT_EQ(expected_rcode, rcode);

        std::ostringstream expected_msg;
        expected_msg << "'" << parameter_name << "' DHCPv6 global parameter "
                     << (expected_value.empty() ? "not " : "")
                     << "found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        EXPECT_EQ(2U, args->size());

        // Validate returned parameters.
        ConstElementPtr parameters = args->get("parameters");
        ASSERT_TRUE(parameters);
        ASSERT_EQ(Element::map, parameters->getType());
        ConstElementPtr count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());

        if (expected_value.empty()) {
            EXPECT_EQ(0U, parameters->size());
            EXPECT_EQ(0, count->intValue());
        } else {
            ASSERT_EQ(2U, parameters->size());
            std::string param_name;
            std::string sub_param_name;
            bool translated = CBControlDHCP<bool>::translateName(parameter_name,
                                                                 param_name,
                                                                 sub_param_name);

            ConstElementPtr value = parameters->get(param_name);
            ASSERT_TRUE(value);
            if (translated) {
                ASSERT_EQ(Element::map, value->getType());
                value = value->get(sub_param_name);
                ASSERT_TRUE(value);
            }
            ASSERT_EQ(expected_value_type, value->getType());
            if (expected_value_type == Element::string) {
                EXPECT_EQ(expected_value, value->stringValue());
            } else {
                EXPECT_EQ(expected_value, value->str());
            }

            // Metadata
            ConstElementPtr metadata = parameters->get("metadata");
            ASSERT_TRUE(metadata);
            ElementPtr expected_metadata = createMetadata(*server_tags.begin());
            EXPECT_TRUE(isEquivalent(metadata, expected_metadata))
                << "Actual: " << metadata->str()
                << "\nExpected: " << expected_metadata->str();

            EXPECT_EQ(1, count->intValue());
        }
    }

    /// @brief Negative test scenario for getting a global parameter.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testGlobalParameter6GetFail(const std::string& args,
                                     const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-global-parameter6-get\","
            "\"arguments\": {" + args + "}"
            "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::getGlobalParameter6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }

    /// @brief Returns remote-global-parameter6-get-all command as text.
    ///
    /// @param remote_map A map to be assigned to be assigned to the "remote"
    /// argument of the command. If the string is empty the "remote" argument
    /// is not included.
    /// @param server_tags Server tags to be included in the command.
    ///
    /// @return Command in the textual format.
    std::string makeGlobalParameter6GetAllConfig(const std::string& remote_map,
                                                 const std::set<std::string>& server_tags) {
        std::string config = "{"
            "\"command\": \"remote-global-parameter6-get-all\"";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty() || !server_tags.empty()) {
            config += ", \"arguments\": {";

            if (!remote_map.empty()) {
                config += "\"remote\": " + remote_map;
            }

            // Only include server tags if specified.
            if (!server_tags.empty()) {
                if (!remote_map.empty()) {
                    config += ", ";
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

    /// @brief Positive test scenario for getting all global parameters.
    ///
    /// @param expected Expected result.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param server_tags Server tags to be included in the command.
    void testGlobalParameter6GetAll(ConstElementPtr expected,
                                    const std::string& remote_map = "",
                                    const std::set<std::string>& server_tags = { ServerTag::ALL }) {
        // Generate the command as text.
        std::string command_text = makeGlobalParameter6GetAllConfig(remote_map, server_tags);
        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getAllGlobalParameters6,
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
                     << " DHCPv6 global parameter(s) found.";
        auto msg = response->get(CONTROL_TEXT);
        ASSERT_TRUE(msg);
        EXPECT_EQ(expected_msg.str(), msg->stringValue());

        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());
        auto count = args->get("count");
        ASSERT_TRUE(count);
        ASSERT_EQ(Element::integer, count->getType());
        EXPECT_EQ(expected->size(), static_cast<size_t>(count->intValue()));

        // Validate returned parameters.
        auto parameters = args->get("parameters");
        EXPECT_TRUE(isEquivalent(expected, parameters))
            << "Actual: " << parameters->str()
            << "\nExpected: " << expected->str();
    }

    /// @brief Negative test scenario for getting all global parameters.
    ///
    /// @param args Arguments for the command in the textual format not
    /// including "arguments".
    /// @param answer_text Expected error message.
    void testGlobalParameter6GetAllFail(const std::string& args,
                                        const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-global-parameter6-get-all\" " + args + "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response =
                        impl_.run(&TestConfigCmdsDhcp6Impl::getAllGlobalParameters6,
                                  command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update global DHCPv6 parameter.
TEST_F(Global6CmdsTest, globalParameter6Set) {
    {
        SCOPED_TRACE("add new global parameters");
        testGlobalParameter6Set({{"renew-timer", "1000"}, {"rebind-timer", "2000"}},
                                false, "", { "server1" });
    }

    {
        SCOPED_TRACE("add another global parameter");
        testGlobalParameter6Set({{"hostname-char-set", ServerTag::ALL}});
    }

    {
        SCOPED_TRACE("add another global map parameter with specifying remote");
        testGlobalParameter6Set({{"compatibility", "{ \"lenient-option-parsing\": true }"}},
                                false, "{ \"type\": \"mysql\" }", {ServerTag::ALL}, true);
    }

    {
        SCOPED_TRACE("update existing global parameter");
        testGlobalParameter6Set({{"server-tag", "earth"}}, true, "", { "server1" });
    }

    {
        SCOPED_TRACE("update another global parameter with specifying remote");
        testGlobalParameter6Set({{"hostname-char-set", ServerTag::ALL}}, true,
                                "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("update another global map parameter");
        testGlobalParameter6Set({{"compatibility", "{ \"lenient-option-parsing\": false }"}},
                                false, "", {ServerTag::ALL}, true);
    }
}

// This test verifies that it is possible to add global DHCPv6 parameter
// with not string types.
TEST_F(Global6CmdsTest, globalParameter6SetType) {
    {
        SCOPED_TRACE("add integer global parameter");
        testGlobalParameter6Set({{"valid-lifetime", "1"}}, false);
    }

    {
        SCOPED_TRACE("add boolean global parameter");
        testGlobalParameter6Set({{"calculate-tee-times", "true"}}, false);
    }

    {
        SCOPED_TRACE("add real global parameter");
        testGlobalParameter6Set({{"t1-percent", "7.0"}}, false);
    }

    {
        SCOPED_TRACE("add global map parameter");
        testGlobalParameter6Set({{"expired-leases-processing", "{ \"flush-reclaimed-timer-wait-time\": 25, \"unwarned-reclaim-cycles\": 5 }"}},
                                false, "", {ServerTag::ALL}, true, 2);
    }

    {
        SCOPED_TRACE("add global list parameter");
        testGlobalParameter6Set({{"host-reservation-identifiers", "[ \"hw-address\", \"duid\" ]"}},
                                false, "", {ServerTag::ALL}, true, 1);
    }
}

// This test verifies that malformed requests to add and update global parameters
// are rejected and proper error messages are returned.
TEST_F(Global6CmdsTest, globalParameter6SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalParameter6SetFail("", "invalid command 'remote-global-parameter6-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty parameters map");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": { }",
                                    "'parameters' map must not be empty");
    }

    {
        SCOPED_TRACE("empty parameter name");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"\": \"earth\""
                                    "}",
                                    "name of the global parameter must not be empty");
    }

    {
        SCOPED_TRACE("unknown parameter name");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"foo\": \"earth\""
                                    "}",
                                    "unknown parameter 'foo'");
    }

    {
        SCOPED_TRACE("unknown parameter name in map");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"sanity-checks\": { \"foo\": \"earth\" }"
                                    "}",
                                    "unknown parameter 'sanity-checks.foo'");
    }

    {
        SCOPED_TRACE("bad parameter value type");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"calculate-tee-times\": \"true\""
                                    "}",
                                    "bad parameter 'calculate-tee-times' value "
                                    "type: expected boolean, got string");
    }

    {
        SCOPED_TRACE("bad list parameter value type");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"host-reservation-identifiers\": true"
                                    "}",
                                    "bad parameter 'host-reservation-identifiers' value "
                                    "type: expected list, got boolean");
    }

    {
        SCOPED_TRACE("bad parameter value type in map");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"multi-threading\": true"
                                    "}",
                                    "bad parameter 'multi-threading' value type: "
                                    "expected map, got boolean");
    }

    {
        SCOPED_TRACE("different parameter value type in map");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"multi-threading\": { \"thread-pool-size\": true }"
                                    "}",
                                    "bad parameter 'multi-threading.thread-pool-size' "
                                    "value type: expected integer, got boolean");
    }

    {
        SCOPED_TRACE("list parameter value");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"subnet6\": [ ]"
                                    "}",
                                    "unknown parameter 'subnet6'");
    }

    {
        SCOPED_TRACE("bad parameter value type in list");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"host-reservation-identifiers\": [ { \"foo\": \"bar\" } ]"
                                    "}",
                                    "bad list parameter 'host-reservation-identifiers' "
                                    "value type: expected string, got map");
    }

    {
        SCOPED_TRACE("different parameter value type in list");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"host-reservation-identifiers\": [ \"foo\", true ]"
                                    "}",
                                    "bad list parameter 'host-reservation-identifiers' value type: "
                                    "expected string, got boolean");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalParameter6SetFail("\"parameters\": {"
                                    "    \"calculate-tee-times\": true"
                                    "}",
                                    "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalParameter6SetFail("\"server-tags\": [ null ],"
                                    "\"parameters\": {"
                                    "    \"calculate-tee-times\": true"
                                    "}",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-global-parameter6-set'"
                                    " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalParameter6SetFail("\"server-tags\": [ \"server1\", \"server2\" ],"
                                    "\"parameters\": {"
                                    "    \"calculate-tee-times\": true"
                                    "}",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-global-parameter6-set'"
                                    " command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalParameter6SetFail("\"server-tags\": [ ],"
                                    "\"parameters\": {"
                                    "    \"calculate-tee-times\": true"
                                    "}",
                                    "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag in the list");
        testGlobalParameter6SetFail("\"server-tags\": [ \" \" ],"
                                    "\"parameters\": {"
                                    "    \"calculate-tee-times\": true"
                                    "}",
                                    "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalParameter6SetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": {"
                                    "    \"server-tag\": \"earth\" "
                                    "},"
                                    "\"remote\": {"
                                    "    \"type\": \"postgresql\""
                                    "}",
                                    "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to delete global DHCPv6 parameter.
TEST_F(Global6CmdsTest, globalParameter6Del) {
    {
        SCOPED_TRACE("add and delete new global parameter");
        testGlobalParameter6Set({{"renew-timer", "1000"}}, false);
        testGlobalParameter6Del("renew-timer", 1);
    }

    {
        SCOPED_TRACE("add and delete new global map parameter");
        testGlobalParameter6Set({{"dhcp-queue-control", "{ \"enable-queue\": false }"}},
                                false, "", {ServerTag::ALL}, true);
        testGlobalParameter6Del("dhcp-queue-control.enable-queue", 1);
    }

    {
        SCOPED_TRACE("add and delete new global list parameter");
        testGlobalParameter6Set({{"host-reservation-identifiers", "[ \"hw-address\" ]"}},
                                false, "", {ServerTag::ALL}, true);
        testGlobalParameter6Del("host-reservation-identifiers", 1);
    }

    {
        SCOPED_TRACE("delete another parameter without server tag");
        testGlobalParameter6Set({{"rebind-timer", "2000"}}, false, "",
                                { "server1" });
        // When using server tag 'all' it should not delete our parameter
        // because this parameter was assigned to server1 explicitly.
        testGlobalParameter6Del("rebind-timer", 0);
    }

    {
        SCOPED_TRACE("delete another global parameter by server tag");
        testGlobalParameter6Del("rebind-timer", 1, "", { "server1" });
    }

    {
        SCOPED_TRACE("delete global parameter");
        // Deleting not existing is not an error.
        testGlobalParameter6Del("renew-timer", 0);
    }

    {
        SCOPED_TRACE("delete another global parameter with specifying remote");
        testGlobalParameter6Set({{"rebind-timer", "3000"}}, false,
                                "{ \"type\": \"mysql\" }");
        testGlobalParameter6Del("rebind-timer", 1, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to delete global parameters
// are rejected and proper error messages are returned.
TEST_F(Global6CmdsTest, globalParameter6DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalParameter6DelFail("", "invalid command 'remote-global-parameter6-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty parameters list");
        testGlobalParameter6DelFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": [ ]", "'parameters' list "
                                    "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty parameter name");
        testGlobalParameter6DelFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"\""
                                    "]",
                                    "'name' parameter must not be empty");
    }

    {
        SCOPED_TRACE("unknown parameter name");
        testGlobalParameter6DelFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"foo\""
                                    "]",
                                    "unknown parameter 'foo'");
    }

    {
        SCOPED_TRACE("unknown parameter name in map");
        testGlobalParameter6DelFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"compatibility.foo\""
                                    "]",
                                    "unknown parameter 'compatibility.foo'");
    }

    {
        SCOPED_TRACE("multiple parameters");
        testGlobalParameter6DelFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"server-tag\", \"interface\""
                                    "]",
                                    "'parameters' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalParameter6DelFail("\"parameters\": ["
                                    "    \"calculate-tee-times\""
                                    "]",
                                    "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalParameter6DelFail("\"server-tags\": [ null ], "
                                    "\"parameters\": ["
                                    "    \"calculate-tee-times\""
                                    "]",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-global-parameter6-del'"
                                    " command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalParameter6DelFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                    "\"parameters\": ["
                                    "    \"calculate-tee-times\""
                                    "]",
                                    "'server-tags' list must contain exactly one"
                                    " server tag for the 'remote-global-parameter6-del'"
                                    " command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalParameter6DelFail("\"server-tags\": [ ], "
                                    "\"parameters\": ["
                                    "    \"calculate-tee-times\""
                                    "]",
                                    "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag in the list");
        testGlobalParameter6DelFail("\"server-tags\": [ \" \" ], "
                                    "\"parameters\": ["
                                    "    \"calculate-tee-times\""
                                    "]",
                                    "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalParameter6DelFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"server-tag\""
                                    "],"
                                    "\"remote\": {"
                                    "    \"type\": \"postgresql\""
                                    "}",
                                    "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get global DHCPv6 parameter.
TEST_F(Global6CmdsTest, globalParameter6Get) {
    {
        SCOPED_TRACE("add and get new global parameter");
        testGlobalParameter6Set({{"server-tag", "universe"}});
        testGlobalParameter6Get("server-tag", "universe");
    }

    {
        SCOPED_TRACE("add and get new global map parameter");
        testGlobalParameter6Set({{"dhcp-ddns", "{ \"sender-ip\": \"::1\" }"}},
                                false, "", { "server1" }, true);
        testGlobalParameter6Get("dhcp-ddns.sender-ip", "::1", Element::string,
                                "", { "server1" });
    }

    {
        SCOPED_TRACE("add and get new global list parameter");
        testGlobalParameter6Set({{"host-reservation-identifiers", "[ \"hw-address\" ]"}},
                                false, "", { "server1" }, true);
        testGlobalParameter6Get("host-reservation-identifiers", "[ \"hw-address\" ]", Element::list,
                                "", { "server1" });
    }

    {
        SCOPED_TRACE("add and get another global parameter");
        testGlobalParameter6Set({{"hostname-char-set", ServerTag::ALL}});
        testGlobalParameter6Get("hostname-char-set", ServerTag::ALL);
    }

    {
        SCOPED_TRACE("get no global parameter");
        // Getting not existing is not an error.
        testGlobalParameter6Get("dhcp-ddns", "");
    }

    {
        SCOPED_TRACE("get another global parameter with specifying remote");
        testGlobalParameter6Set({{"hostname-char-set", ServerTag::ALL}}, true,
                                "{ \"type\": \"mysql\" }");
        testGlobalParameter6Get("hostname-char-set", ServerTag::ALL,
                                Element::string,
                                "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that it is possible to get global DHCPv6 parameter
// with not string types.
TEST_F(Global6CmdsTest, globalParameter6GetType) {
    {
        SCOPED_TRACE("add and get integer global parameter");
        testGlobalParameter6Set({{"valid-lifetime", "1"}}, false);
        testGlobalParameter6Get("valid-lifetime", "1", Element::integer);
    }

    {
        SCOPED_TRACE("add boolean global parameter");
        testGlobalParameter6Set({{"calculate-tee-times", "true"}}, false);
        testGlobalParameter6Get("calculate-tee-times", "true", Element::boolean);
    }

    {
        SCOPED_TRACE("add real global parameter");
        testGlobalParameter6Set({{"t1-percent", "7.0"}}, false);
        testGlobalParameter6Get("t1-percent", "7.0", Element::real);
    }

    {
        SCOPED_TRACE("add global map parameter");
        testGlobalParameter6Set({{"dhcp-ddns", "{ \"enable-updates\": true }"}},
                                false, "", {ServerTag::ALL}, true);
        testGlobalParameter6Get("dhcp-ddns.enable-updates", "true", Element::boolean);
    }

    {
        SCOPED_TRACE("add global list parameter");
        testGlobalParameter6Set({{"host-reservation-identifiers", "[ \"hw-address\" ]"}},
                                false, "", {ServerTag::ALL}, true);
        testGlobalParameter6Get("host-reservation-identifiers", "[ \"hw-address\" ]", Element::list);
    }
}

// This test verifies that malformed requests to get global parameters
// are rejected and proper error messages are returned.
TEST_F(Global6CmdsTest, globalParameter6GetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalParameter6GetFail("", "invalid command 'remote-global-parameter6-get': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty parameters list");
        testGlobalParameter6GetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": [ ]", "'parameters' list "
                                    "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty parameter name");
        testGlobalParameter6GetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"\""
                                     "]",
                                    "'name' parameter must not be empty");
    }

    {
        SCOPED_TRACE("unknown parameter");
        testGlobalParameter6GetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"foo\""
                                    "]",
                                    "unknown parameter 'foo'");
    }

    {
        SCOPED_TRACE("unknown parameter in map");
        testGlobalParameter6GetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"dhcp-ddns.foo\""
                                    "]",
                                    "unknown parameter 'dhcp-ddns.foo'");
    }

    {
        SCOPED_TRACE("multiple parameters");
        testGlobalParameter6GetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"server-tag\", \"interface\""
                                    "]",
                                    "'parameters' list must include exactly one element");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalParameter6GetFail("\"parameters\": ["
                                    "    \"server-tag\""
                                    "]",
                                    "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalParameter6GetFail("\"server-tags\": [ null ], "
                                    "\"parameters\": ["
                                    "    \"server-tag\""
                                    "]",
                                    "'server-tags' list must contain exactly one server"
                                    " tag for the 'remote-global-parameter6-get' command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalParameter6GetFail("\"server-tags\": [ \"server1\", \"server2\" ], "
                                    "\"parameters\": ["
                                    "    \"server-tag\""
                                    "]",
                                    "'server-tags' list must contain exactly one server"
                                    " tag for the 'remote-global-parameter6-get' command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalParameter6GetFail("\"server-tags\": [ ],"
                                    "\"parameters\": ["
                                    "    \"server-tag\""
                                    "]",
                                    "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag in the list");
        testGlobalParameter6GetFail("\"server-tags\": [ \" \" ],"
                                    "\"parameters\": ["
                                    "    \"server-tag\""
                                    "]",
                                    "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalParameter6GetFail("\"server-tags\": [ \"all\" ], "
                                    "\"parameters\": ["
                                    "    \"server-tag\""
                                    "],"
                                    "\"remote\": {"
                                    "    \"type\": \"postgresql\""
                                    "}",
                                    "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to get all global DHCPv6 parameters.
TEST_F(Global6CmdsTest, globalParameter6GetAll) {
    ElementPtr expected = Element::createList();
    ElementPtr expected_all = Element::createList();
    testGlobalParameter6GetAll(expected, "", { "server1" });
    testGlobalParameter6GetAll(expected_all);

    // Add a parameter.
    testGlobalParameter6Set({{"renew-timer", "1000"}},
                            false, "", { "server1" });
    ElementPtr param = Element::createMap();
    param->set("renew-timer", Element::create(1000));
    param->set("metadata", createMetadata("server1"));
    expected->add(param);
    testGlobalParameter6GetAll(expected, "", { "server1" });

    // Add a second parameter.
    testGlobalParameter6Set({{"hostname-char-set", ServerTag::ALL}});
    param = Element::createMap();
    param->set("hostname-char-set", Element::create(ServerTag::ALL));
    param->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(param);
    expected_all->add(param);
    testGlobalParameter6GetAll(expected, "", { "server1" });

    // Add a map parameter
    testGlobalParameter6Set({{"expired-leases-processing", "{ \"flush-reclaimed-timer-wait-time\": 25, \"unwarned-reclaim-cycles\": 5 }"}},
                              false, "", {ServerTag::ALL}, true, 2);
    param = Element::createMap();
    ElementPtr sub_param = Element::createMap();
    sub_param->set("flush-reclaimed-timer-wait-time", Element::create(25));
    param->set("expired-leases-processing", sub_param);
    param->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(param);
    expected_all->add(param);
    param = Element::createMap();
    sub_param = Element::createMap();
    sub_param->set("unwarned-reclaim-cycles", Element::create(5));
    param->set("expired-leases-processing", sub_param);
    param->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(param);
    expected_all->add(param);

    // Add a list parameter
    testGlobalParameter6Set({{"host-reservation-identifiers", "[ \"hw-address\", \"duid\" ]"}},
                            false, "", {ServerTag::ALL}, true, 1);
    param = Element::createMap();
    sub_param = Element::createList();
    sub_param->add(Element::create("hw-address"));
    sub_param->add(Element::create("duid"));
    param->set("host-reservation-identifiers", sub_param);
    param->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(param);
    expected_all->add(param);

    // With another tag only options belonging to all are returned.
    testGlobalParameter6GetAll(expected_all, "", { "server2" });
    testGlobalParameter6GetAll(expected_all);

    // Try with a remote.
    testGlobalParameter6GetAll(expected, "{ \"type\": \"mysql\" }", { "server1" });
    testGlobalParameter6Set({{"renew-timer", "1000"}}, false, "{ \"type\": \"mysql\" }");
    param = Element::createMap();
    param->set("renew-timer", Element::create(1000));
    param->set("metadata", createMetadata(ServerTag::ALL));
    expected->add(param);
    testGlobalParameter6GetAll(expected, "{ \"type\": \"mysql\" }", { "server1" });
}

// This test verifies that malformed requests to get all global parameters
// are rejected and proper error messages are returned.
TEST_F(Global6CmdsTest, globalParameter6GetAllFail) {
    {
        SCOPED_TRACE("empty arguments");
        testGlobalParameter6GetAllFail(", \"arguments\": { }",
                                       "invalid command 'remote-global-parameter6-get-all': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("no server tags");
        testGlobalParameter6GetAllFail(", \"arguments\": {"
                                       "    \"remote\": {"
                                       "        \"type\": \"mysql\""
                                       "    }"
                                       "}",
                                       "'server-tags' parameter is mandatory");
    }

    {
        SCOPED_TRACE("unassigned server tag");
        testGlobalParameter6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ null ]"
                                       "}",
                                       "'server-tags' list must contain exactly one server tag"
                                       " for the 'remote-global-parameter6-get-all' command");
    }

    {
        SCOPED_TRACE("multiple server tags");
        testGlobalParameter6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ \"server1\", \"server2\" ]"
                                       "}",
                                       "'server-tags' list must contain exactly one server tag"
                                       " for the 'remote-global-parameter6-get-all' command");
    }

    {
        SCOPED_TRACE("empty server tags list");
        testGlobalParameter6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ ]"
                                       "}",
                                       "'server-tags' list must not be empty");
    }

    {
        SCOPED_TRACE("blank server tag in the list");
        testGlobalParameter6GetAllFail(", \"arguments\": {"
                                       "    \"server-tags\": [ \" \" ]"
                                       "}",
                                       "server-tag must not be empty");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testGlobalParameter6GetAllFail(", \"arguments\": { "
                                       "\"server-tags\": [ \"all\" ], "
                                       "\"remote\": {"
                                       "    \"type\": \"postgresql\""
                                       "} }",
                                       "no such database found for selector: "
                                       "type=postgresql");
    }
}

// This test verifies that global container parameters are supported (scalars only)
TEST_F(Global6CmdsTest, testSupportedContainerParameters) {
    for (auto const& elem : ConfigCmdsDhcp6Impl::GLOBAL6_MAP_PARAMETERS) {
        auto sub_type = elem.second;
        EXPECT_TRUE(sub_type == Element::string ||
                    sub_type == Element::integer ||
                    sub_type == Element::boolean ||
                    sub_type == Element::real) << "bad parameter '" << elem.first << "' value type: "
                                               << "expected one of string, integer, boolean, real, got "
                                               << Element::typeToName(sub_type);
    }

    for (auto const& elem : SimpleParser6::GLOBAL6_LIST_PARAMETER_TYPES) {
        auto sub_type = elem.second;
        EXPECT_TRUE(sub_type == Element::string ||
                    sub_type == Element::integer ||
                    sub_type == Element::boolean ||
                    sub_type == Element::real) << "bad parameter '" << elem.first << "' value type: "
                                               << "expected one of string, integer, boolean, real, got "
                                               << Element::typeToName(sub_type);
    }
}

}
