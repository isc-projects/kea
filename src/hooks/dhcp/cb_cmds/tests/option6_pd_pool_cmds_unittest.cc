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
class OptionPdPool6CmdsTest : public ConfigCmdsDhcp6Test {
public:

    /// @brief Inserts subnet and pd pool used in tests into the database.
    void initTestSubnet6() {
        Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 30, 40, 60, 70, 1));
        PoolPtr pdpool(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"), 48, 64));
        subnet->addPool(pdpool);
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateSubnet6(BackendSelector(), ServerSelector::ALL(), subnet);
    }

    /// @brief Returns remote-option6-pd-pool-set as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makePdPoolOption6SetConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-option6-pd-pool-set\","
            "\"arguments\": {"
            "    \"pd-pools\": [ { \"prefix\": \"2001:db8::\", "
            "\"prefix-len\": 48 } ],    \"options\": ";

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
    /// embedded in a prefix delegation pool.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testPdPoolOption6Set(const OptionDescriptorPtr& option,
                              const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text =
            makePdPoolOption6SetConfig(option, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setPdPoolOption6,
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

        auto option_0 = option_list->get(0);
        ASSERT_TRUE(option_0);
        ASSERT_EQ(Element::map, option_0->getType());
        EXPECT_EQ(2U, option_0->size());

        auto option_0_code = option_0->get("code");
        ASSERT_TRUE(option_0_code);
        ASSERT_EQ(Element::integer, option_0_code->getType());
        EXPECT_EQ(static_cast<int64_t>(option->option_->getType()),
                  option_0_code->intValue());

        auto option_0_space = option_0->get("space");
        ASSERT_TRUE(option_0_space);
        ASSERT_EQ(Element::string, option_0_space->getType());
        EXPECT_EQ(option->space_name_, option_0_space->stringValue());

        // Make sure that the created/updated pd pool option is in the database
        // and has correct values.
        auto fetched_subnet = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getSubnet6(BackendSelector(), ServerSelector::ANY(), 1);
        ASSERT_TRUE(fetched_subnet);
        auto fetched_pd_pool = fetched_subnet->getPool(Lease::TYPE_PD,
                                                       IOAddress("2001:db8::1"),
                                                       false);
        ASSERT_TRUE(fetched_pd_pool);
        auto fetched_options = fetched_pd_pool->getCfgOption();
        ASSERT_TRUE(fetched_options);

        // Make sure that the pd pool options are not encapsulated.
        EXPECT_FALSE(fetched_options->isEncapsulated());

        auto fetched_option = fetched_options->get(option->space_name_,
                                                   option->option_->getType());
        ASSERT_TRUE(fetched_option.option_);
        EXPECT_TRUE(fetched_option.equals(*option));
    }

    /// @brief Negative test scenario for setting or updating a DHCP option.
    ///
    /// @param args Arguments for the command in the textual format.
    /// @param answer_text Expected error message.
    void testPdPoolOption6SetFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-pd-pool-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setPdPoolOption6,
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

    /// @brief Returns remote-option6-pd-pool-del as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param include_client_classes when true the option's client_classes_
    /// content is added to the command.
    ///
    /// @return Command in the textual format.
    std::string makePdPoolOption6DelConfig(const OptionDescriptorPtr& option,
                                           const std::string& remote_map,
                                           bool include_client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option6-pd-pool-del\","
            "\"arguments\": {"
            "    \"pd-pools\": [ { \"prefix\": \"2001:db8::\", "
            "\"prefix-len\": 48 } ],    \"options\": [ { ";

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
    /// embedded in a prefix delegation pool.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param expected_count Expected number of deleted DHCP options.
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param include_client_classes when true (default), the option's
    /// client-classes are included in the delete function's parameters.
    void testPdPoolOption6Del(const OptionDescriptorPtr& option,
                              unsigned expected_count,
                              const std::string& remote_map = "",
                              bool include_client_classes = true) {

        // Generate the command as text.
        std::string command_text =
            makePdPoolOption6DelConfig(option, remote_map,
                                       include_client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delPdPoolOption6,
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

        // Make sure that the deleted pd pool option is not in the database.
        auto fetched_subnet = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getSubnet6(BackendSelector(), ServerSelector::ANY(), 1);
        ASSERT_TRUE(fetched_subnet);
        auto fetched_pd_pool = fetched_subnet->getPool(Lease::TYPE_PD,
                                                       IOAddress("2001:db8::1"),
                                                       false);
        ASSERT_TRUE(fetched_pd_pool);
        auto fetched_options = fetched_pd_pool->getCfgOption();
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
    void testPdPoolOption6DelFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-pd-pool-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delPdPoolOption6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update pd pool DHCP option.
TEST_F(OptionPdPool6CmdsTest, pdPoolOption6Set) {
    initTestSubnet6();

    {
        SCOPED_TRACE("add new pd pool option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc);
    }

    {
        SCOPED_TRACE("add another pd pool option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc);
    }

    {
        SCOPED_TRACE("update existing pd pool option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc);
    }

    {
        SCOPED_TRACE("update another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc, "{ \"type\": \"mysql\" }");
    }
}

// This test verifies that malformed requests to add and update pool
// DHCP options are rejected and proper error messages are returned.
TEST_F(OptionPdPool6CmdsTest, pdPoolOption6SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testPdPoolOption6SetFail("", "invalid command 'remote-option6-pd-pool-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty pd pools list");
        testPdPoolOption6SetFail("\"pd-pools\": [ ]",
                                 "'pd-pools' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty pd pool map");
        testPdPoolOption6SetFail("\"pd-pools\": [ { } ]",
                                 "missing 'prefix' parameter");
    }

    {
        SCOPED_TRACE("malformed pd pool");
        testPdPoolOption6SetFail("\"pd-pools\": [ { \"prefix\": true, "
                                 "\"prefix-len\": 123} ]",
                                 "'prefix' parameter is not a string");
    }

    {
        SCOPED_TRACE("invalid pd pool prefix");
        testPdPoolOption6SetFail("\"pd-pools\": [ { \"prefix\": \"xyz\", "
                                 "\"prefix-len\": 123} ]",
                                 "invalid 'prefix': Failed to convert string "
                                 "to address 'xyz': Invalid argument");
    }

    {
        SCOPED_TRACE("invalid pd pool length");
        testPdPoolOption6SetFail("\"pd-pools\": [ { \"prefix\": \"2001:db8::\","
                                 " \"prefix-len\": 133 } ]",
                                 "'prefix-len' value must be in range of [1..128]");
    }

    {
        SCOPED_TRACE("invalid pd pool prefix length");
        testPdPoolOption6SetFail("\"pd-pools\": [ { \"prefix\": \"2001:db8::\","
                                 " \"prefix-len\": 16 } ]",
                                 "Invalid Pool6 address boundaries: 2001:db8:: is not the first address in prefix: 2001::/16");
    }

    {
        SCOPED_TRACE("not IPv6 prefix");
        testPdPoolOption6SetFail("\"pd-pools\": [ { \"prefix\": \"192.0.2.0\","
                                 " \"prefix-len\": 123} ]",
                                 "'prefix' value is not a valid IPv6 prefix");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testPdPoolOption6SetFail("\"pd-pools\": [ { "
                                 "\"id\": 1, \"prefix\": \"2001:db8::/64\", "
                                 "\"prefix-len\": 48 } ]",
                                 "spurious 'id' parameter");
    }

    {
        SCOPED_TRACE("multiple pd pools");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 },"
                                 "{ \"prefix\": \"2001:db8:1::/80\", "
                                 "\"prefix-len\": 48 } "
                                 "]",
                                 "'pd-pools' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testPdPoolOption6SetFail("\"server-tags\": [ ]",
                                 "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("no options list");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ]",
                                 "'options' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("no pd pools list");
        testPdPoolOption6SetFail("\"options\": ["
                                 "{ \"name\": \"bootfile-url\", "
                                 "\"data\": \"my-boot-file\" } ]",
                                 "'pd-pools' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("empty options list");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ ]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { } ]",
                                 "option data configuration requires one of "
                                 "'code' or 'name' parameters to be specified");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ "
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"type\": \"string\" } ]",
                                 "spurious 'type' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ "
                                 "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                                 "\"space\": 4 } ]",
                                 "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"name\": \"new-posix-timezone\" } ]",
                                 "option data does not match option definition");
    }

    {
        SCOPED_TRACE("multiple options");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": ["
                                 "{ \"name\": \"bootfile-url\", \"data\": \"my-boot-file\" },"
                                 "{ \"name\": \"nis-domain-name\", \"data\": \"mydomain\" }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testPdPoolOption6SetFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": ["
                                 "    { \"name\": \"bootfile-url\", \"data\": \"my-boot-file\" }"
                                 "],"
                                 "\"remote\": {"
                                 "    \"type\": \"postgresql\""
                                 "}",
                                 "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to delete pd pool DHCP option.
TEST_F(OptionPdPool6CmdsTest, pdPoolOption6Del) {
    initTestSubnet6();

    {
        SCOPED_TRACE("add and delete new pd pool option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc);
        testPdPoolOption6Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("add and delete another pd pool option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc);
        testPdPoolOption6Del(option_desc, 1);
    }

    {
        SCOPED_TRACE("delete pd pool option");
        // Deleting not existing is not an error.
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Del(option_desc, 0);
    }

    {
        SCOPED_TRACE("delete another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPdPoolOption6Set(option_desc, "{ \"type\": \"mysql\" }");
        testPdPoolOption6Del(option_desc, 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("delete option 0 in not dhcp6 space");
        OptionPtr option(new Option(Option::V6, 0));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = "foo";
        testPdPoolOption6Set(option_desc);
        testPdPoolOption6Del(option_desc, 1);
    }
}

// This test verifies that malformed requests to delete pd pool DHCP
// options are rejected and proper error messages are returned.
TEST_F(OptionPdPool6CmdsTest, pdPoolOption6DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testPdPoolOption6DelFail("", "invalid command 'remote-option6-pd-pool-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty pools list");
        testPdPoolOption6DelFail("\"pd-pools\": [ ]",
                                 "'pd-pools' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty pd pool map");
        testPdPoolOption6DelFail("\"pd-pools\": [ { } ]",
                                 "missing 'prefix' parameter");
    }

    {
        SCOPED_TRACE("malformed pd pool");
        testPdPoolOption6DelFail("\"pd-pools\": [ { \"prefix\": true, "
                                 "\"prefix-len\": 123} ]",
                                 "'prefix' parameter is not a string");
    }

    {
        SCOPED_TRACE("invalid pd pool prefix");
        testPdPoolOption6DelFail("\"pd-pools\": [ { \"prefix\": \"xyz\", "
                                 "\"prefix-len\": 123} ]",
                                 "invalid 'prefix': Failed to convert string "
                                 "to address 'xyz': Invalid argument");
    }

    {
        SCOPED_TRACE("invalid pd pool length");
        testPdPoolOption6DelFail("\"pd-pools\": [ { \"prefix\": \"2001:db8::\","
                                 " \"prefix-len\": 133 } ]",
                                 "'prefix-len' value must be in range of [1..128]");
    }

    {
        SCOPED_TRACE("invalid pd pool prefix length");
        testPdPoolOption6DelFail("\"pd-pools\": [ { \"prefix\": \"2001:db8::\","
                                 " \"prefix-len\": 16 } ]",
                                 "Invalid Pool6 address boundaries: 2001:db8:: is not the first address in prefix: 2001::/16");
    }

    {
        SCOPED_TRACE("not IPv6 prefix");
        testPdPoolOption6DelFail("\"pd-pools\": [ { \"prefix\": \"192.0.2.0\","
                                 " \"prefix-len\": 123} ]",
                                 "'prefix' value is not a valid IPv6 prefix");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testPdPoolOption6DelFail("\"pd-pools\": [ { "
                                 "\"id\": 1, \"prefix\": \"2001:db8::/64\", "
                                 "\"prefix-len\": 48 } ]",
                                 "spurious 'id' parameter");
    }

    {
        SCOPED_TRACE("multiple pd pools");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 },"
                                 "{ \"prefix\": \"2001:db8:1::/80\", "
                                 "\"prefix-len\": 48 } "
                                 "]",
                                 "'pd-pools' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testPdPoolOption6DelFail("\"server-tags\": [ ]",
                               "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("no options list");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ]",
                                 "'options' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("no pd pools list");
        testPdPoolOption6DelFail("\"options\": ["
                                 "{ \"name\": \"bootfile-url\", "
                                 "\"data\": \"my-boot-file\" } ]",
                                 "'pd-pools' parameter must be specified "
                                 "and must be a list");
    }

    {
        SCOPED_TRACE("empty options list");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ ]", "'options' list "
                                 "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { } ]",
                                 "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \"\" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": \" \" } ]",
                                 "'space' parameter must be a "
                                 "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"code\": 1, "
                                 "\"space\": 40 } ]",
                                 "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"code\": \"nis-domain-name\" } ]",
                                 "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"code\": 100000} ]",
                                 "invalid 'code' value not in [0..65535]");
    }

    {
        SCOPED_TRACE("option 0 is reserved");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": [ { \"code\": 0 } ]",
                                 "invalid 'code' value 0: reserved");
    }

    {
        SCOPED_TRACE("multiple options");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
                                 "\"options\": ["
                                 "{ \"code\": 67 },"
                                 "{ \"code\": 40 }"
                                 "]",
                                 "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testPdPoolOption6DelFail("\"pd-pools\": ["
                                 "{ \"prefix\": \"2001:db8::\", "
                                 "\"prefix-len\": 48 } ], "
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
// pd pool options of the same type code and space.
TEST_F(OptionPdPool6CmdsTest, pdPoolOption6WithClientClasses) {
    initTestSubnet6();

    std::vector<OptionDescriptorPtr> descs;

    OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL, "one"));
    OptionDescriptorPtr desc(new OptionDescriptor(option, false, false));
    desc->space_name_ = DHCP6_OPTION_SPACE;
    desc->addClientClass("cc-one");
    descs.push_back(desc);

    option.reset(new OptionString(Option::V6, D6O_BOOTFILE_URL, "two"));
    desc.reset(new OptionDescriptor(option, false, false));
    desc->space_name_ = DHCP6_OPTION_SPACE;
    desc->addClientClass("cc-two");
    descs.push_back(desc);

    option.reset(new OptionString(Option::V6, D6O_BOOTFILE_URL, "none"));
    desc.reset(new OptionDescriptor(option, false, false));
    desc->space_name_ = DHCP6_OPTION_SPACE;
    descs.push_back(desc);

    // Add all three options.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("add desc");
        testPdPoolOption6Set(d);
    }

    // Verify that all three options were added and are returned.
    auto fetched_subnet = ConfigBackendDHCPv6Mgr::instance().getPool()->
        getSubnet6(BackendSelector(), ServerSelector::ANY(), 1);
    ASSERT_TRUE(fetched_subnet);

    auto fetched_pool = fetched_subnet->getPool(Lease::TYPE_PD,
                                                IOAddress("2001:db8::"),
                                                false);
    ASSERT_TRUE(fetched_pool);

    auto fetched_options = fetched_pool->getCfgOption();
    ASSERT_TRUE(fetched_options);

    auto fetched_descs = fetched_options->getList(DHCP6_OPTION_SPACE, D6O_BOOTFILE_URL);
    ASSERT_EQ(fetched_descs.size(), 3U);

    // Deleting without client-classes specified should delete all three.
    SCOPED_TRACE("Deleting without client-classes specified");
    testPdPoolOption6Del(desc, 3, "", false);

    // Re-add them.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("re-adding desc");
        testPdPoolOption6Set(d);
    }

    // Delete them one at a time with client-classes.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("Deleting with client-classes specified");
        testPdPoolOption6Del(d, 1, "", true);
    }
}

}
