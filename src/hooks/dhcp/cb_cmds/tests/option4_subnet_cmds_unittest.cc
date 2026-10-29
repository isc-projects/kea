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
#include <set>
#include <string>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::cb;
using namespace isc::cb::test;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;

namespace {

/// @brief Test fixture class for callouts pertaining to DHCP options.
class OptionSubnet4CmdsTest : public ConfigCmdsDhcp4Test {
public:

    /// @brief Inserts subnet used in tests into the database.
    void initTestSubnet4() {
    Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1));
    ConfigBackendDHCPv4Mgr::instance().getPool()->
        createUpdateSubnet4(BackendSelector(), ServerSelector::ALL(), subnet);
    }

    /// @brief Returns remote-option4-subnet-set as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makeSubnetOption4SetConfig(const OptionDescriptorPtr& option,
                                                  const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-option4-subnet-set\","
            "\"arguments\": {"
            "    \"subnets\": [ { \"id\": 1 } ],"
            "    \"options\": ";

        CfgOption cfg_option;
        cfg_option.add(*option, option->space_name_);

        config += cfg_option.toElement()->str();

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";
        return (config);
    }

    /// @brief Positive test scenario for setting or updating a DHCP option
    /// embedded in a subnet.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testSubnetOption4Set(const OptionDescriptorPtr& option,
                              const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text =
            makeSubnetOption4SetConfig(option, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setSubnetOption4,
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

        // Make sure that the created/updated subnet option is in the database
        // and has correct values.
        auto fetched_subnet = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSubnet4(BackendSelector(), ServerSelector::ANY(), 1);
        ASSERT_TRUE(fetched_subnet);
        auto fetched_options = fetched_subnet->getCfgOption();
        ASSERT_TRUE(fetched_options);
        auto fetched_option = fetched_options->get(option->space_name_,
                                                   option->option_->getType(),
                                                   option->client_classes_);
        ASSERT_TRUE(fetched_option.option_);
        EXPECT_TRUE(fetched_option.equals(*option));
    }

    /// @brief Negative test scenario for setting or updating a DHCP option.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnetOption4SetFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option4-subnet-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::setSubnetOption4,
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

    /// @brief Returns remote-option4-subnet-del as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param include_client_classes when true the option's client_classes_
    /// content is added to the command.
    ///
    /// @return Command in the textual format.
    std::string makeSubnetOption4DelConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           bool include_client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option4-subnet-del\","
            "\"arguments\": {"
            "    \"subnets\": [ { \"id\": 1 } ],"
            "    \"options\": [ { ";

        CfgOption cfg_option;
        cfg_option.add(*option, option->space_name_);

        std::ostringstream code;
        code << option->option_->getType();
        config += "\"code\": " + code.str();
        config += ", \"space\": \"" + option->space_name_ + "\"";

        if (include_client_classes) {
            config += (", \"client-classes\": "
                   + option->client_classes_.toElement()->str());
        }

        config += " } ]";

        // Only include "remote" parameter if non empty.
        if (!remote_map.empty()) {
            config += ", \"remote\": " + remote_map;
        }

        // No server tags.

        config += "} }";

        return (config);
    }

    /// @brief Positive test scenario for deleting a DHCP option
    /// embedded in a subnet.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param expected_count Expected number of deleted DHCP options.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param include_client_classes when true (default), the option's
    /// client-classes are included in the delete function's parameters.
    void testSubnetOption4Del(const OptionDescriptorPtr& option,
                                     unsigned expected_count,
                                     const std::string& remote_map = "",
                                     bool include_client_classes = true) {

        // Generate the command as text.
        std::string command_text =
            makeSubnetOption4DelConfig(option, remote_map,
                                       include_client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delSubnetOption4,
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

        // Make sure that the deleted subnet option is not in the database.
        auto fetched_subnet = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSubnet4(BackendSelector(), ServerSelector::ANY(), 1);
        ASSERT_TRUE(fetched_subnet);
        auto fetched_options = fetched_subnet->getCfgOption();
        ASSERT_TRUE(fetched_options);
        if (include_client_classes) {
            auto fetched_option = fetched_options->get(option->space_name_,
                                                       option->option_->getType(),
                                                       option->client_classes_);
            ASSERT_FALSE(fetched_option.option_);
        } else {
            auto fetched_option = fetched_options->get(option->space_name_,
                                                       option->option_->getType());
            ASSERT_FALSE(fetched_option.option_);
        }
    }

    /// @brief Negative test scenario for deleting a DHCP option.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testSubnetOption4DelFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option4-subnet-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp4Impl::delSubnetOption4,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update subnet DHCP option.
TEST_F(OptionSubnet4CmdsTest, subnetOption4Set) {
    initTestSubnet4();

    {
        SCOPED_TRACE("add new subnet option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc);
    }

    {
        SCOPED_TRACE("add another subnet option with formatted value");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "mydomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "mydomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc);
    }

    {
        SCOPED_TRACE("update existing subnet option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc);
    }

    {
        SCOPED_TRACE("update another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("add an option for which a definition is required");
        // Add a definition for option 222 to the config backend.
        auto option_def = boost::make_shared<OptionDefinition>("foo", 222, DHCP4_OPTION_SPACE,
                                                               "string");
        ASSERT_NO_THROW(
            ConfigBackendDHCPv4Mgr::instance().getPool()->
                createUpdateOptionDef4(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def);
        );

        // Set the option 222.
        OptionStringPtr option(new OptionString(Option::V4, 222, "baz"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false, "baz"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;

        testSubnetOption4Set(option_desc);
    }
}

// This test verifies that malformed requests to add and update subnet
// DHCP options are rejected and proper error messages are returned.
TEST_F(OptionSubnet4CmdsTest, subnetOption4SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnetOption4SetFail("", "invalid command 'remote-option4-subnet-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnets list");
        testSubnetOption4SetFail("\"subnets\": [ ]",
                                 "'subnets' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnetOption4SetFail("\"subnets\": [ { } ]",
                                 "missing 'id' parameter");
    }

    {
        SCOPED_TRACE("malformed id");
        testSubnetOption4SetFail("\"subnets\": [ { \"id\": true } ]",
                                 "'id' parameter is not an integer");
    }

    {
        SCOPED_TRACE("zero subnet id");
        testSubnetOption4SetFail("\"subnets\": [ { \"id\": 0 } ]",
                                 "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("invalid subnet id");
        testSubnetOption4SetFail("\"subnets\": [ { \"id\": 4294967295 } ]",
                                 "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnetOption4SetFail("\"subnets\": [ { \"interface\": \"eth1\" } ]",
                                 "missing 'id' parameter");
    }

    {
        SCOPED_TRACE("spurious prefix");
        testSubnetOption4SetFail("\"subnets\": [ { "
                                 "\"id\": 1, \"subnet\": \"192.0.2.0/24\" } ]",
                                 "spurious 'subnet' parameter");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 },"
                                 "{ \"id\": 2 }"
                                 "]",
                                 "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSubnetOption4SetFail("\"server-tags\": [ ]",
                                 "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("no options list");
        testSubnetOption4SetFail("\"subnets\": [ { \"id\": 1 } ]",
                                 "'options' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("no subnets list");
        testSubnetOption4SetFail("\"options\": ["
                                 "{ \"name\": \"boot-file-name\", "
                                 "\"data\": \"my-boot-file\" } ]",
                                 "'subnets' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("empty options list");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ ]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { } ]",
                                 "option data configuration requires one of "
                                 "'code' or 'name' parameters to be specified");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ "
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"type\": \"string\" } ]",
                                 "spurious 'type' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ "
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"space\": 4 } ]",
                                 "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"name\": \"nis-domain\" } ]",
                                 "option data does not match option definition");
    }

    {
        SCOPED_TRACE("multiple options");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": ["
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\" },"
                                 "{ \"name\": \"nis-domain\", \"data\": \"mydomain\" }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
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
        testSubnetOption4SetFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": ["
                                 "    {"
                                 "        \"name\": \"boot-file-name\","
                                 "        \"data\": \"my-boot-file\","
                                 "        \"space\": \"myspace\""
                                 "    }"
                                 "]",
                                 "definition for the option 'myspace.boot-file-name' does not exist");
    }
}

// This test verifies that it is possible to delete subnet DHCP option.
TEST_F(OptionSubnet4CmdsTest, subnetOption4Del) {
    initTestSubnet4();

    {
        SCOPED_TRACE("add and delete new subnet option");
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc);
        testSubnetOption4Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("add and delete another subnet option with formatted value");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "mydomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "mydomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc);
        testSubnetOption4Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("delete subnet option");
        // Deleting not existing is not an error.
        OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Del(option_desc, 0);
    }

    {
        SCOPED_TRACE("delete another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V4, DHO_NIS_DOMAIN,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP4_OPTION_SPACE;
        testSubnetOption4Set(option_desc, "{ \"type\": \"mysql\" }");
        testSubnetOption4Del(option_desc, 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("delete option 0 in not dhcp4 space");
        OptionPtr option(new Option(Option::V4, 0));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = "foo";
        testSubnetOption4Set(option_desc);
        testSubnetOption4Del(option_desc, 1);
    }
}

// This test verifies that malformed requests to delete subnet DHCP
// options are rejected and proper error messages are returned.
TEST_F(OptionSubnet4CmdsTest, subnetOption4DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testSubnetOption4DelFail("", "invalid command 'remote-option4-subnet-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty subnets list");
        testSubnetOption4DelFail("\"subnets\": [ ]",
                                 "'subnets' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty subnet map");
        testSubnetOption4DelFail("\"subnets\": [ { } ]",
                                 "missing 'id' parameter");
    }

    {
        SCOPED_TRACE("malformed id");
        testSubnetOption4DelFail("\"subnets\": [ { \"id\": true } ]",
                                 "'id' parameter is not an integer");
    }

    {
        SCOPED_TRACE("zero subnet id");
        testSubnetOption4DelFail("\"subnets\": [ { \"id\": 0 } ]",
                                 "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("invalid subnet id");
        testSubnetOption4DelFail("\"subnets\": [ { \"id\": 4294967295 } ]",
                                 "'id' parameter must be in [1..4294967294] range");
    }

    {
        SCOPED_TRACE("malformed subnet");
        testSubnetOption4DelFail("\"subnets\": [ { \"interface\": \"eth1\" } ]",
                                 "missing 'id' parameter");
    }

    {
        SCOPED_TRACE("spurious prefix");
        testSubnetOption4DelFail("\"subnets\": [ { "
                                 "\"id\": 1, \"subnet\": \"192.0.2.0/24\" } ]",
                                 "spurious 'subnet' parameter");
    }

    {
        SCOPED_TRACE("multiple subnets");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 },"
                                 "{ \"id\": 2 }"
                                 "]",
                                 "'subnets' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testSubnetOption4DelFail("\"server-tags\": [ ]",
                                 "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("no options list");
        testSubnetOption4DelFail("\"subnets\": [ { \"id\": 1 } ]",
                                 "'options' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("no subnets list");
        testSubnetOption4DelFail("\"options\": ["
                                 "{ \"name\": \"boot-file-name\", "
                                 "\"data\": \"my-boot-file\" } ]",
                                 "'subnets' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("empty options list");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { } ]",
                                 "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \"\" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \" \" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": 40 } ]",
                                 "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"code\": \"nis-domain\" } ]",
                                 "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"code\": 1000} ]",
                                 "invalid 'code' value not in [0..255]");
    }

    {
        SCOPED_TRACE("conflict with PAD");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": [ { \"code\": 0 } ]",
                                 "invalid 'code' value 0: reserved for PAD");
    }

    {
        SCOPED_TRACE("multiple options");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": ["
                                 "{ \"code\": 67 },"
                                 "{ \"code\": 40 }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testSubnetOption4DelFail("\"subnets\": ["
                                 "{ \"id\": 1 } ],"
                                 "\"options\": ["
                                 "    { \"code\": 67 }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }
}

// Verifies that client-class tags can be used to distinguish between
// shared-network options of the same type code and space.
TEST_F(OptionSubnet4CmdsTest, subnetOption4WithClientClasses) {
    initTestSubnet4();

    std::vector<OptionDescriptorPtr> descs;

    OptionStringPtr option(new OptionString(Option::V4, DHO_BOOT_FILE_NAME, "one"));
    OptionDescriptorPtr desc(new OptionDescriptor(option, false, false));
    desc->space_name_ = DHCP4_OPTION_SPACE;
    desc->addClientClass("cc-one");
    descs.push_back(desc);

    option.reset(new OptionString(Option::V4, DHO_BOOT_FILE_NAME, "two"));
    desc.reset(new OptionDescriptor(option, false, false));
    desc->space_name_ = DHCP4_OPTION_SPACE;
    desc->addClientClass("cc-two");
    descs.push_back(desc);

    option.reset(new OptionString(Option::V4, DHO_BOOT_FILE_NAME, "none"));
    desc.reset(new OptionDescriptor(option, false, false));
    desc->space_name_ = DHCP4_OPTION_SPACE;
    descs.push_back(desc);

    // Add all three options.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("add desc");
        testSubnetOption4Set(d);
    }

    // Verify that all three options were added and are returned.
    auto fetched_subnet = ConfigBackendDHCPv4Mgr::instance().getPool()->
            getSubnet4(BackendSelector(), ServerSelector::ANY(), 1);

    ASSERT_TRUE(fetched_subnet);
    auto fetched_options = fetched_subnet->getCfgOption();
    ASSERT_TRUE(fetched_options);

    auto fetched_descs = fetched_options->getList(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_EQ(fetched_descs.size(), 3U);

    // Deleting without client-classes specified should delete all three.
    SCOPED_TRACE("Deleting without client-classes specified");
    testSubnetOption4Del(desc, 3, "", false);

    // Re-add them.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("re-adding desc");
        testSubnetOption4Set(d);
    }

    // Delete them one at a time with client-classes.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("Deleting with client-classes specified");
        testSubnetOption4Del(d, 1, "", true);
    }
}

}
