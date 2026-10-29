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
class OptionPool6CmdsTest : public ConfigCmdsDhcp6Test {
public:

    /// @brief Inserts subnet and pools used in tests into the database.
    void initTestSubnet6() {
      Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8::"), 64, 30, 40, 60, 70, 1));
      PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 112));
      PoolPtr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::1:0"),
                                IOAddress("2001:db8::2:0")));
        subnet->addPool(pool1);
        subnet->addPool(pool2);
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateSubnet6(BackendSelector(), ServerSelector::ALL(), subnet);
    }

    /// @brief Returns remote-option6-pool-set as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param pool Which pool (1 or 2).
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    ///
    /// @return Command in the textual format.
    std::string makePoolOption6SetConfig(const OptionDescriptorPtr& option,
                                         int pool,
                                         const std::string& remote_map) {
        std::string config = "{"
            "\"command\": \"remote-option6-pool-set\","
            "\"arguments\": {"
            "    \"pools\": [ { \"pool\": ";
        switch (pool) {
        case 1:
            config += "\"2001:db8::/30\"";
            break;
        default:
            config += "\"2001:db8::1:0 - 2001:db8::2:0\"";
            break;
        }
        config += "} ],    \"options\": ";

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
    /// embedded in a pool.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param pool Which pool (1 or 2).
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    void testPoolOption6Set(const OptionDescriptorPtr& option,
                            int pool,
                            const std::string& remote_map = "") {
        // Generate the command as text.
        std::string command_text =
            makePoolOption6SetConfig(option, pool, remote_map);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setPoolOption6,
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

        // Make sure that the created/updated pool option is in the database
        // and has correct values.
        auto fetched_subnet = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getSubnet6(BackendSelector(), ServerSelector::ANY(), 1);
        ASSERT_TRUE(fetched_subnet);
        auto addr = IOAddress(pool == 1 ? "2001:db8::1" : "2001:db8::1:2");
        auto fetched_pool = fetched_subnet->getPool(Lease::TYPE_NA, addr, false);
        ASSERT_TRUE(fetched_pool);
        auto fetched_options = fetched_pool->getCfgOption();
        ASSERT_TRUE(fetched_options);

        // Make sure that the pool options are not encapsulated.
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
    void testPoolOption6SetFail(const std::string& args,
                                const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-pool-set\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::setPoolOption6,
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

    /// @brief Returns remote-option6-pool-del as text.
    ///
    /// @param option Pointer to the option descriptor to be used in the command.
    /// @param pool Which pool (1 or 2).
    /// @param remote_map A map to be assigned to the "remote" argument of the
    /// command. If the string is empty the "remote" argument is not included.
    /// @param include_client_classes when true the option's client_classes_
    /// content is added to the command.
    ///
    /// @return Command in the textual format.
    std::string makePoolOption6DelConfig(const OptionDescriptorPtr& option,
                                         int pool,
                                         const std::string& remote_map,
                                         bool include_client_classes) {
        std::string config = "{"
            "\"command\": \"remote-option6-pool-del\","
            "\"arguments\": {"
            "    \"pools\": [ { \"pool\": ";
        switch (pool) {
        case 1:
            config += "\"2001:db8::/30\"";
            break;
        default:
            config += "\"2001:db8::1:0 - 2001:db8::2:0\"";
            break;
        }
        config += "} ],    \"options\": [ { ";

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
    /// embedded in a pool.
    ///
    /// @param option Pointer to the option descriptor to be used to create or
    /// update option instance.
    /// @param expected_count Expected number of deleted DHCP options.
    /// @param pool Which pool (1 or 2).
    /// @param remote_map A map to be assigned to the "remote" argument. The
    /// default value is the empty string in which case the "remote" argument
    /// is not included in the command.
    /// @param include_client_classes when true (default), the option's
    /// client-classes are included in the delete function's parameters.
    void testPoolOption6Del(const OptionDescriptorPtr& option,
                            unsigned expected_count, int pool,
                            const std::string& remote_map = "",
                            bool include_client_classes = true) {

        // Generate the command as text.
        std::string command_text =
            makePoolOption6DelConfig(option, pool, remote_map,
                                     include_client_classes);

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delPoolOption6,
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

        // Make sure that the deleted pool option is not in the database.
        auto fetched_subnet = ConfigBackendDHCPv6Mgr::instance().getPool()->
            getSubnet6(BackendSelector(), ServerSelector::ANY(), 1);
        ASSERT_TRUE(fetched_subnet);
        auto addr = IOAddress(pool == 1 ? "2001:db8::1" : "2001:db8::1:2");
        auto fetched_pool = fetched_subnet->getPool(Lease::TYPE_NA, addr, false);
        ASSERT_TRUE(fetched_pool);
        auto fetched_options = fetched_pool->getCfgOption();
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
    void testPoolOption6DelFail(const std::string& args,
                                  const std::string& answer_text) {
        // Generate the command as text.
        std::string command_text = "{"
            "\"command\": \"remote-option6-pool-del\","
            "\"arguments\": {" + args + "}"
        "}";

        // Invoke the callout and get the response.
        ConstElementPtr response;
        ASSERT_NO_THROW(response = impl_.run(&TestConfigCmdsDhcp6Impl::delPoolOption6,
                                             command_text));
        ASSERT_TRUE(response);

        // Make sure that the response indicates error.
        int rcode = 0;
        auto answer = parseAnswer(rcode, response);
        EXPECT_EQ(CONTROL_RESULT_ERROR, rcode);
        EXPECT_EQ(answer_text, answer->stringValue());
    }
};

// This test verifies that it is possible to add and update pool DHCP option.
TEST_F(OptionPool6CmdsTest, poolOption6Set) {
    initTestSubnet6();

    {
        SCOPED_TRACE("add new pool option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 1);
    }

    {
        SCOPED_TRACE("add another pool option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 2);
    }

    {
        SCOPED_TRACE("update existing pool option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 1);
    }

    {
        SCOPED_TRACE("update another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 2, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("add an option for which a definition is required");
        // Add a definition for option 1001 to the config backend.
        auto option_def = boost::make_shared<OptionDefinition>("foo", 1001, DHCP6_OPTION_SPACE,
                                                               "string");
        ASSERT_NO_THROW(
            ConfigBackendDHCPv6Mgr::instance().getPool()->
                createUpdateOptionDef6(BackendSelector(),
                                       ServerSelector::ALL(),
                                       option_def);
        );

        // Set the option 1001.
        OptionStringPtr option(new OptionString(Option::V6, 1001, "baz"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false, "baz"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;

        testPoolOption6Set(option_desc, 1);
    }
}

// This test verifies that malformed requests to add and update pool
// DHCP options are rejected and proper error messages are returned.
TEST_F(OptionPool6CmdsTest, poolOption6SetFail) {
    {
        SCOPED_TRACE("empty arguments");
        testPoolOption6SetFail("", "invalid command 'remote-option6-pool-set': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty pools list");
        testPoolOption6SetFail("\"pools\": [ ]",
                               "'pools' list "
                               "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty pool map");
        testPoolOption6SetFail("\"pools\": [ { } ]",
                               "missing 'pool' parameter");
    }

    {
        SCOPED_TRACE("malformed pool");
        testPoolOption6SetFail("\"pools\": [ { \"pool\": true } ]",
                               "'pool' parameter is not a string");
    }

    {
        SCOPED_TRACE("invalid pool prefix");
        testPoolOption6SetFail("\"pools\": [ { \"pool\": \"2001:db8::/129\" } ]",
                               "Failed to create pool defined by: "
                               "2001:db8::/129 (<string>:1:74)");
    }

    {
        SCOPED_TRACE("invalid pool range");
        testPoolOption6SetFail("\"pools\": [ { \"pool\": "
                               "\"2001:db8::2:2 - 2001:db8::1:1\" } ]",
                               "Failed to create pool defined by: "
                               "2001:db8::2:2-2001:db8::1:1 (<string>:1:74)");
    }

    {
        SCOPED_TRACE("invalid pool prefix");
        testPoolOption6SetFail("\"pools\": [ { \"pool\": "
                               "\"2001:db8::/25\" } ]",
                               "Failed to create pool defined by: "
                               "2001:db8::/25 (<string>:1:74)");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testPoolOption6SetFail("\"pools\": [ { "
                               "\"id\": 1, \"pool\": \"2001:db8::/64\" } ]",
                               "spurious 'id' parameter");
    }

    {
        SCOPED_TRACE("multiple pools");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/64\" },"
                               "{ \"pool\": \"2001:db8:1::/80\" }"
                               "]",
                               "'pools' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testPoolOption6SetFail("\"server-tags\": [ ]",
                               "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("no options list");
        testPoolOption6SetFail("\"pools\": [ { \"pool\": \"2001:db8::/64\" } ]",
                               "'options' parameter must be specified "
                               "and must be a list");
    }

    {
        SCOPED_TRACE("no pools list");
        testPoolOption6SetFail("\"options\": ["
                               "{ \"name\": \"bootfile-url\", "
                               "\"data\": \"my-boot-file\" } ]",
                               "'pools' parameter must be specified "
                               "and must be a list");
    }

    {
        SCOPED_TRACE("empty options list");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ ]",
                               "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { } ]",
                               "option data configuration requires one of "
                               "'code' or 'name' parameters to be specified");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ "
                               "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                               "\"type\": \"string\" } ]",
                               "spurious 'type' parameter");
    }

    {
        SCOPED_TRACE("keyword with bad type");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ "
                               "{ \"name\": \"boot-file-name\", \"data\": \"my-boot-file\", "
                               "\"space\": 4 } ]",
                               "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"name\": \"new-posix-timezone\" } ]",
                               "option data does not match option definition");
    }

    {
        SCOPED_TRACE("multiple options");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": ["
                               "{ \"name\": \"bootfile-url\", \"data\": \"my-boot-file\" },"
                               "{ \"name\": \"nis-domain-name\", \"data\": \"mydomain\" }"
                               "]",
                               "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testPoolOption6SetFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": ["
                               "    { \"name\": \"bootfile-url\", \"data\": \"my-boot-file\" }"
                               "],"
                               "\"remote\": {"
                               "    \"type\": \"postgresql\""
                               "}",
                               "no such database found for selector: type=postgresql");
    }
}

// This test verifies that it is possible to delete pool DHCP option.
TEST_F(OptionPool6CmdsTest, poolOption6Del) {
    initTestSubnet6();

    {
        SCOPED_TRACE("add and delete new pool option");
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "my-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 1);
        testPoolOption6Del(option_desc, 1, 1);
    }

    {
        SCOPED_TRACE("add and delete another pool option with formatted value");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "myportal"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false,
                                                             "myportal"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 2);
        testPoolOption6Del(option_desc, 1, 2);
    }

    {
        SCOPED_TRACE("delete pool option");
        // Deleting not existing is not an error.
        OptionStringPtr option(new OptionString(Option::V6, D6O_BOOTFILE_URL,
                                                "another-boot-file"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Del(option_desc, 0, 1);
        testPoolOption6Del(option_desc, 0, 2);
    }

    {
        SCOPED_TRACE("delete another option with specifying remote");
        OptionStringPtr option(new OptionString(Option::V6, D6O_V6_CAPTIVE_PORTAL,
                                                "anotherdomain"));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, true,
                                                             false,
                                                             "anotherdomain"));
        option_desc->space_name_ = DHCP6_OPTION_SPACE;
        testPoolOption6Set(option_desc, 1, "{ \"type\": \"mysql\" }");
        testPoolOption6Del(option_desc, 1, 1, "{ \"type\": \"mysql\" }");
    }

    {
        SCOPED_TRACE("delete option 0 in not dhcp6 space");
        OptionPtr option(new Option(Option::V6, 0));
        OptionDescriptorPtr option_desc(new OptionDescriptor(option, false,
                                                             false));
        option_desc->space_name_ = "foo";
        testPoolOption6Set(option_desc, 2);
        testPoolOption6Del(option_desc, 1, 2);
    }
}

// This test verifies that malformed requests to delete pool DHCP
// options are rejected and proper error messages are returned.
TEST_F(OptionPool6CmdsTest, poolOption6DelFail) {
    {
        SCOPED_TRACE("empty arguments");
        testPoolOption6DelFail("", "invalid command 'remote-option6-pool-del': 'arguments' is empty");
    }

    {
        SCOPED_TRACE("empty pools list");
        testPoolOption6DelFail("\"pools\": [ ]",
                               "'pools' list "
                               "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty pool map");
        testPoolOption6DelFail("\"pools\": [ { } ]",
                               "missing 'pool' parameter");
    }

    {
        SCOPED_TRACE("malformed pool");
        testPoolOption6DelFail("\"pools\": [ { \"pool\": true } ]",
                               "'pool' parameter is not a string");
    }

    {
        SCOPED_TRACE("invalid pool prefix");
        testPoolOption6DelFail("\"pools\": [ { \"pool\": \"2001:db8::/129\" } ]",
                               "Failed to create pool defined by: "
                               "2001:db8::/129 (<string>:1:74)");
    }

    {
        SCOPED_TRACE("invalid pool range");
        testPoolOption6DelFail("\"pools\": [ { \"pool\": "
                               "\"2001:db8::2:2 - 2001:db8::1:1\" } ]",
                               "Failed to create pool defined by: "
                               "2001:db8::2:2-2001:db8::1:1 (<string>:1:74)");
    }

    {
        SCOPED_TRACE("invalid pool prefix");
        testPoolOption6DelFail("\"pools\": [ { \"pool\": "
                               "\"2001:db8::/25\" } ]",
                               "Failed to create pool defined by: "
                               "2001:db8::/25 (<string>:1:74)");
    }

    {
        SCOPED_TRACE("spurious keyword");
        testPoolOption6DelFail("\"pools\": [ { "
                               "\"id\": 1, \"pool\": \"2001:db8::/64\" } ]",
                               "spurious 'id' parameter");
    }

    {
        SCOPED_TRACE("multiple pools");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" },"
                               "{ \"pool\": \"2001:db8:1::/80\" }"
                               "]",
                               "'pools' list must include exactly one element");
    }

    {
        SCOPED_TRACE("server tags");
        testPoolOption6DelFail("\"server-tags\": [ ]",
                               "'server-tags' parameter is forbidden");
    }

    {
        SCOPED_TRACE("no options list");
        testPoolOption6DelFail("\"pools\": [ { \"pool\": \"2001:db8::/64\" } ]",
                               "'options' parameter must be specified "
                               "and must be a list");
    }

    {
        SCOPED_TRACE("no pools list");
        testPoolOption6DelFail("\"options\": ["
                               "{ \"name\": \"bootfile-url\", "
                               "\"data\": \"my-boot-file\" } ]",
                               "'pools' parameter must be specified "
                               "and must be a list");
    }

    {
        SCOPED_TRACE("empty options list");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ ]", "'options' list "
                               "must include exactly one element");
    }

    {
        SCOPED_TRACE("empty options map");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { } ]",
                               "missing 'code' parameter");
    }

    {
        SCOPED_TRACE("empty space");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"code\": 1, "
                               "\"space\": \"\" } ]",
                               "'space' parameter must be a "
                               "valid space name");
    }

    {
        SCOPED_TRACE("invalid space");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"code\": 1, "
                               "\"space\": \" \" } ]",
                               "'space' parameter must be a "
                               "valid space name");
    }

    {
        SCOPED_TRACE("malformed option (integer instead of string)");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"code\": 1, "
                               "\"space\": 40 } ]",
                               "'space' parameter is not a string");
    }

    {
        SCOPED_TRACE("malformed option (string instead of integer)");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"code\": \"nis-domain-name\" } ]",
                               "'code' parameter is not an integer");
    }

    {
        SCOPED_TRACE("out of range code");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"code\": 100000} ]",
                               "invalid 'code' value not in [0..65535]");
    }

    {
        SCOPED_TRACE("option 0 is reserved");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": [ { \"code\": 0 } ]",
                               "invalid 'code' value 0: reserved");
    }

    {
        SCOPED_TRACE("multiple options");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
                               "\"options\": ["
                               "{ \"code\": 67 },"
                               "{ \"code\": 40 }"
                               "]",
                               "'options' list must include exactly one element");
    }

    {
        SCOPED_TRACE("unsupported backend type");
        testPoolOption6DelFail("\"pools\": ["
                               "{ \"pool\": \"2001:db8::/32\" } ],"
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
// pool options of the same type code and space.
TEST_F(OptionPool6CmdsTest, poolOption6WithClientClasses) {
    initTestSubnet6();

    size_t pool_num = 1;
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
        testPoolOption6Set(d, pool_num);
    }

    // Verify that all three options were added and are returned.
    auto fetched_subnet = ConfigBackendDHCPv6Mgr::instance().getPool()->
        getSubnet6(BackendSelector(), ServerSelector::ANY(), 1);
    ASSERT_TRUE(fetched_subnet);

    auto addr = IOAddress("2001:db8::1");
    auto fetched_pool = fetched_subnet->getPool(Lease::TYPE_NA, addr, false);
    ASSERT_TRUE(fetched_pool);

    auto fetched_options = fetched_pool->getCfgOption();
    ASSERT_TRUE(fetched_options);

    auto fetched_descs = fetched_options->getList(DHCP6_OPTION_SPACE, D6O_BOOTFILE_URL);
    ASSERT_EQ(fetched_descs.size(), 3U);

    // Deleting without client-classes specified should delete all three.
    SCOPED_TRACE("Deleting without client-classes specified");
    testPoolOption6Del(desc, 3, pool_num, "", false);

    // Re-add them.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("re-adding desc");
        testPoolOption6Set(d, pool_num);
    }

    // Delete them one at a time with client-classes.
    for (OptionDescriptorPtr const& d : descs) {
        SCOPED_TRACE("Deleting with client-classes specified");
        testPoolOption6Del(d, 1, pool_num, "", true);
    }
}

}
