// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <cc/command_interpreter.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/classify.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp4.h>
#include <process/config_ctl_info.h>
#include <hooks/hooks_manager.h>
#include <util/doubles.h>

#include "marker_file.h"
#include "test_libraries.h"
#include "test_data_files_config.h"
#include "dhcp4_test_utils.h"
#include "get_config_unittest.h"

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace std;

namespace {
const char* PARSER_CONFIGS[] = {
    // CONFIGURATION 0: one subnet with one pool, no user contexts
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [\"*\" ]"
    "    },"
    "    \"valid-lifetime\": 4000,"
    "    \"rebind-timer\": 2000,"
    "    \"renew-timer\": 1000,"
    "    \"subnet4\": [ {"
    "        \"pools\": [ "
    "            { \"pool\":  \"192.0.2.0/28\" }"
    "        ],"
    "        \"subnet\": \"192.0.2.0/24\""
    "     } ]"
    "}",

    // Configuration 1: one pool with empty user context
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [\"*\" ]"
    "    },"
    "    \"valid-lifetime\": 4000,"
    "    \"rebind-timer\": 2000,"
    "    \"renew-timer\": 1000,"
    "    \"subnet4\": [ {"
    "        \"pools\": [ "
    "            { \"pool\":  \"192.0.2.0/28\","
    "                \"user-context\": {"
    "                }"
    "            }"
    "        ],"
    "        \"subnet\": \"192.0.2.0/24\""
    "     } ]"
    "}",

    // Configuration 2: one pool with user context containing lw4over6 parameters
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [\"*\" ]"
    "    },"
    "    \"valid-lifetime\": 4000,"
    "    \"rebind-timer\": 2000,"
    "    \"renew-timer\": 1000,"
    "    \"subnet4\": [ {"
    "        \"pools\": [ "
    "            { \"pool\":  \"192.0.2.0/28\","
    "                \"user-context\": {"
    "                    \"integer-param\": 42,"
    "                    \"string-param\": \"Sagittarius\","
    "                    \"bool-param\": true"
    "                }"
    "            }"
    "        ],"
    "        \"subnet\": \"192.0.2.0/24\""
    "     } ]"
    "}",

    // Configuration 3: one min-max pool with user context containing lw4over6 parameters
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [\"*\" ]"
    "    },"
    "    \"valid-lifetime\": 4000,"
    "    \"rebind-timer\": 2000,"
    "    \"renew-timer\": 1000,"
    "    \"subnet4\": [ {"
    "        \"pools\": [ "
    "            { \"pool\":  \"192.0.2.0 - 192.0.2.15\","
    "                \"user-context\": {"
    "                    \"integer-param\": 42,"
    "                    \"string-param\": \"Sagittarius\","
    "                    \"bool-param\": true"
    "                }"
    "            }"
    "        ],"
    "        \"subnet\": \"192.0.2.0/24\""
    "     } ]"
    "}",

    // Configuration 4: two host databases
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [\"*\" ]"
    "    },"
    "    \"valid-lifetime\": 4000,"
    "    \"rebind-timer\": 2000,"
    "    \"renew-timer\": 1000,"
    "    \"hosts-databases\": [ {"
    "        \"type\": \"mysql\","
    "        \"name\": \"keatest1\","
    "        \"user\": \"keatest\","
    "        \"password\": \"keatest\""
    "      },{"
    "        \"type\": \"mysql\","
    "        \"name\": \"keatest2\","
    "        \"user\": \"keatest\","
    "        \"password\": \"keatest\""
    "      }"
    "    ]"
    "}",

    // Configuration 5 for comments
    "{"
    "    \"comment\": \"A DHCPv4 server\","
    "    \"interfaces-config\": {"
    "        \"comment\": \"Use wildcard\","
    "        \"interfaces\": [ \"*\" ] },"
    "    \"option-def\": [ {"
    "        \"comment\": \"An option definition\","
    "        \"name\": \"foo\","
    "        \"code\": 100,"
    "        \"type\": \"ipv4-address\","
    "        \"space\": \"isc\""
    "     } ],"
    "    \"option-data\": [ {"
    "        \"comment\": \"Set option value\","
    "        \"name\": \"dhcp-message\","
    "        \"data\": \"ABCDEF0105\","
    "        \"csv-format\": false"
    "     } ],"
    "    \"client-classes\": ["
    "        {"
    "           \"comment\": \"match all\","
    "           \"name\": \"all\","
    "           \"test\": \"'' == ''\""
    "        },"
    "        {"
    "           \"name\": \"none\""
    "        },"
    "        {"
    "           \"comment\": \"a comment\","
    "           \"name\": \"both\","
    "           \"user-context\": {"
    "               \"version\": 1"
    "           }"
    "        }"
    "        ],"
    "    \"control-socket\": {"
    "        \"socket-type\": \"unix\","
    "        \"socket-name\": \"/tmp/kea4-ctrl-socket\","
    "        \"user-context\": { \"comment\": \"Indirect comment\" }"
    "    },"
    "    \"shared-networks\": [ {"
    "        \"comment\": \"A shared network\","
    "        \"name\": \"foo\","
    "        \"subnet4\": ["
    "        { "
    "            \"comment\": \"A subnet\","
    "            \"subnet\": \"192.0.1.0/24\","
    "            \"id\": 100,"
    "            \"pools\": ["
    "            {"
    "                 \"comment\": \"A pool\","
    "                 \"pool\": \"192.0.1.1-192.0.1.10\""
    "            }"
    "            ],"
    "            \"reservations\": ["
    "            {"
    "                 \"comment\": \"A host reservation\","
    "                 \"hw-address\": \"AA:BB:CC:DD:EE:FF\","
    "                 \"hostname\": \"foo.example.com\","
    "                 \"option-data\": [ {"
    "                     \"comment\": \"An option in a reservation\","
    "                     \"name\": \"domain-name\","
    "                     \"data\": \"example.com\""
    "                 } ]"
    "            }"
    "            ]"
    "        }"
    "        ]"
    "     } ],"
    "    \"dhcp-ddns\": {"
    "        \"comment\": \"No dynamic DNS\","
    "        \"enable-updates\": false"
    "    }"
    "}",

    // Configuration 6: config databases
    "{ \n"
    "    \"interfaces-config\": { \n"
    "        \"interfaces\": [\"*\" ] \n"
    "    }, \n"
    "    \"valid-lifetime\": 4000, \n"
    "    \"rebind-timer\": 2000, \n"
    "    \"renew-timer\": 1000, \n"
    "    \"config-control\": { \n"
    "       \"config-fetch-wait-time\": 10, \n"
    "       \"config-databases\": [ { \n"
    "               \"type\": \"mysql\", \n"
    "               \"name\": \"keatest1\", \n"
    "               \"user\": \"keatest\", \n"
    "               \"password\": \"keatest\" \n"
    "           },{ \n"
    "               \"type\": \"mysql\", \n"
    "               \"name\": \"keatest2\", \n"
    "               \"user\": \"keatest\", \n"
    "               \"password\": \"keatest\" \n"
    "           } \n"
    "       ] \n"
    "   } \n"
    "} \n"
};

class Dhcp4ParserTest : public ::testing::Test {
protected:
    // Check that no hooks libraries are loaded.  This is a pre-condition for
    // a number of tests, so is checked in one place.  As this uses an
    // ASSERT call - and it is not clear from the documentation that Gtest
    // predicates can be used in a constructor - the check is placed in SetUp.
    virtual void SetUp() {
        std::vector<std::string> libraries = HooksManager::getLibraryNames();
        ASSERT_TRUE(libraries.empty());
    }

public:
    Dhcp4ParserTest()
    : rcode_(-1) {
        // Open port 0 means to not do anything at all. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.
        srv_.reset(new ControlledDhcpv4Srv(0));
        // Create fresh context.
        resetConfiguration();
    }

public:

    // Checks if the result of DHCP server configuration has
    // expected code (0 for success, other for failures).
    // Also stores result in rcode_ and comment_.
    void checkResult(ConstElementPtr status, int expected_code) {
        ASSERT_TRUE(status);
        comment_ = parseAnswer(rcode_, status);
        EXPECT_EQ(expected_code, rcode_) << "error text:" << comment_->stringValue();
    }

    /// @brief Convenience method for running configuration
    ///
    /// This method does not throw, but signals errors using gtest macros.
    ///
    /// @param config text to be parsed as JSON
    /// @param expected_code expected code (see cc/command_interpreter.h)
    /// @param exp_error expected text error (check skipped if empty)
    void configure(std::string config, int expected_code,
                   std::string exp_error = "") {
        ConstElementPtr json;
        try {
            json = parseDHCP4(config, true);
        } catch(const std::exception& ex) {
            ADD_FAILURE() << "parseDHCP4 failed: " << ex.what();
        }

        ConstElementPtr status;
        EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
        ASSERT_TRUE(status);

        int rcode;
        ConstElementPtr comment = parseAnswer(rcode, status);
        EXPECT_EQ(expected_code, rcode);

        string text;
        ASSERT_NO_THROW(text = comment->stringValue());

        if (expected_code != rcode) {
            std::cout << "Reported status: " << text << std::endl;
        }

        if ((rcode != 0)) {
            if (!exp_error.empty()) {
                EXPECT_EQ(exp_error, text);
            }
        }
    }

    ~Dhcp4ParserTest() {
        resetConfiguration();

        // ... and delete the hooks library marker files if present
        static_cast<void>(remove(LOAD_MARKER_FILE));
        static_cast<void>(remove(UNLOAD_MARKER_FILE));
    };

    /// @brief Returns an interface configuration used by the most of the
    /// unit tests.
    std::string genIfaceConfig() const {
        return ("\"interfaces-config\": {"
                "  \"interfaces\": [ \"*\" ]"
                "}");
    }

    /// @brief Create the simple configuration with single option.
    ///
    /// This function allows to set one of the parameters that configure
    /// option value. These parameters are: "name", "code", "data",
    /// "csv-format" and "space".
    ///
    /// @param param_value string holding option parameter value to be
    /// injected into the configuration string.
    /// @param parameter name of the parameter to be configured with
    /// param value.
    /// @return configuration string containing custom values of parameters
    /// describing an option.
    std::string createConfigWithOption(const std::string& param_value,
                                       const std::string& parameter) {
        std::map<std::string, std::string> params;
        if (parameter == "name") {
            params["name"] = param_value;
            params["space"] = DHCP4_OPTION_SPACE;
            params["code"] = "56";
            params["data"] = "ABCDEF0105";
            params["csv-format"] = "false";
        } else if (parameter == "space") {
            params["name"] = "dhcp-message";
            params["space"] = param_value;
            params["code"] = "56";
            params["data"] = "ABCDEF0105";
            params["csv-format"] = "false";
        } else if (parameter == "code") {
            params["name"] = "dhcp-message";
            params["space"] = DHCP4_OPTION_SPACE;
            params["code"] = param_value;
            params["data"] = "ABCDEF0105";
            params["csv-format"] = "false";
        } else if (parameter == "data") {
            params["name"] = "dhcp-message";
            params["space"] = DHCP4_OPTION_SPACE;
            params["code"] = "56";
            params["data"] = param_value;
            params["csv-format"] = "false";
        } else if (parameter == "csv-format") {
            params["name"] = "dhcp-message";
            params["space"] = DHCP4_OPTION_SPACE;
            params["code"] = "56";
            params["data"] = "ABCDEF0105";
            params["csv-format"] = param_value;
        }
        return (createConfigWithOption(params));
    }

    /// @brief Create simple configuration with single option.
    ///
    /// This function creates a configuration for a single option with
    /// custom values for all parameters that describe the option.
    ///
    /// @params params map holding parameters and their values.
    /// @return configuration string containing custom values of parameters
    /// describing an option.
    std::string createConfigWithOption(const std::map<std::string, std::string>& params) {
        std::ostringstream stream;
        stream << "{ " << genIfaceConfig() << "," <<
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"subnet4\": [ { "
            "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
            "    \"subnet\": \"192.0.2.0/24\", "
            "    \"option-data\": [ {";
        bool first = true;
        typedef std::pair<std::string, std::string> ParamPair;
        BOOST_FOREACH(ParamPair param, params) {
            if (!first) {
                stream << ", ";
            } else {
                // cppcheck-suppress unreadVariable
                first = false;
            }
            if (param.first == "name") {
                stream << "\"name\": \"" << param.second << "\"";
            } else if (param.first == "space") {
                stream << "\"space\": \"" << param.second << "\"";
            } else if (param.first == "code") {
                stream << "\"code\": " << param.second << "";
            } else if (param.first == "data") {
                stream << "\"data\": \"" << param.second << "\"";
            } else if (param.first == "csv-format") {
                stream << "\"csv-format\": " << param.second;
            }
        }
        stream <<
            "        } ]"
            " } ],"
            "\"valid-lifetime\": 4000 }";
        return (stream.str());
    }

    /// @brief Returns an option from the subnet.
    ///
    /// This function returns an option from a subnet to which the
    /// specified subnet address belongs. The option is identified
    /// by its code.
    ///
    /// @param subnet_address Address which belongs to the subnet from
    /// which the option is to be returned.
    /// @param option_code Code of the option to be returned.
    /// @param expected_options_count Expected number of options in
    /// the particular subnet.
    ///
    /// @return Descriptor of the option. If the descriptor holds a
    /// NULL option pointer, it means that there was no such option
    /// in the subnet.
    OptionDescriptor
    getOptionFromSubnet(const IOAddress& subnet_address,
                        const uint16_t option_code,
                        const uint16_t expected_options_count = 1) {
        Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
            getCfgSubnets4()->selectSubnet(subnet_address);
        if (!subnet) {
            /// @todo replace toText() with the use of operator <<.
            ADD_FAILURE() << "A subnet for the specified address "
                          << subnet_address.toText()
                          << "does not exist in Config Manager";
        }
        OptionContainerPtr options =
            subnet->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
        if (expected_options_count != options->size()) {
            ADD_FAILURE() << "The number of options in the subnet '"
                          << subnet_address.toText() << "' is different "
                " than expected number of options '"
                          << expected_options_count << "'";
        }

        // Get the search index. Index #1 is to search using option code.
        const OptionContainerTypeIndex& idx = options->get<1>();

        // Get the options for specified index. Expecting one option to be
        // returned but in theory we may have multiple options with the same
        // code so we get the range.
        std::pair<OptionContainerTypeIndex::const_iterator,
                  OptionContainerTypeIndex::const_iterator> range =
            idx.equal_range(option_code);
        if (std::distance(range.first, range.second) > 1) {
            ADD_FAILURE() << "There is more than one option having the"
                " option code '" << option_code << "' in a subnet '"
                          << subnet_address.toText() << "'. Expected "
                " at most one option";
        } else if (std::distance(range.first, range.second) == 0) {
            return (OptionDescriptor(OptionPtr(), false));
        }

        return (*range.first);
    }

    /// @brief Test invalid option parameter value.
    ///
    /// This test function constructs the simple configuration
    /// string and injects invalid option configuration into it.
    /// It expects that parser will fail with provided option code.
    ///
    /// @param param_value string holding invalid option parameter value
    /// to be injected into configuration string.
    /// @param parameter name of the parameter to be configured with
    /// param_value (can be any of "name", "code", "data")
    void testInvalidOptionParam(const std::string& param_value,
                                const std::string& parameter) {
        ConstElementPtr x;
        std::string config = createConfigWithOption(param_value, parameter);
        ConstElementPtr json = parseDHCP4(config);
        EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
        checkResult(x, 1);
        EXPECT_TRUE(errorContainsPosition(x, "<string>"));
    }

    /// @brief Test invalid option parameter value.
    ///
    /// This test function constructs the simple configuration
    /// string and injects invalid option configuration into it.
    /// It expects that parser will fail with provided option code.
    ///
    /// @param params Map of parameters defining an option.
    void
    testInvalidOptionParam(const std::map<std::string, std::string>& params) {
        ConstElementPtr x;
        std::string config = createConfigWithOption(params);
        ConstElementPtr json = parseDHCP4(config);
        EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
        checkResult(x, 1);
        EXPECT_TRUE(errorContainsPosition(x, "<string>"));
    }

    /// @brief Test option against given code and data.
    ///
    /// @param option_desc option descriptor that carries the option to
    /// be tested.
    /// @param expected_code expected code of the option.
    /// @param expected_data expected data in the option.
    /// @param expected_data_len length of the reference data.
    /// @param extra_data if true extra data is allowed in an option
    /// after tested data.
    void testOption(const OptionDescriptor& option_desc,
                    uint16_t expected_code, const uint8_t* expected_data,
                    size_t expected_data_len,
                    bool extra_data = false) {
        // Check if option descriptor contains valid option pointer.
        ASSERT_TRUE(option_desc.option_);
        // Verify option type.
        EXPECT_EQ(expected_code, option_desc.option_->getType());
        // We may have many different option types being created. Some of them
        // have dedicated classes derived from Option class. In such case if
        // we want to verify the option contents against expected_data we have
        // to prepare raw buffer with the contents of the option. The easiest
        // way is to call pack() which will prepare on-wire data.
        util::OutputBuffer buf(option_desc.option_->getData().size());
        option_desc.option_->pack(buf);
        if (extra_data) {
            // The length of the buffer must be at least equal to size of the
            // reference data but it can sometimes be greater than that. This is
            // because some options carry suboptions that increase the overall
            // length.
            ASSERT_GE(buf.getLength() - option_desc.option_->getHeaderLen(),
                      expected_data_len);
        } else {
            ASSERT_EQ(buf.getLength() - option_desc.option_->getHeaderLen(),
                      expected_data_len);
        }
        // Verify that the data is correct. Do not verify suboptions and a header.
        const uint8_t* data = static_cast<const uint8_t*>(buf.getData());
        EXPECT_EQ(0, memcmp(expected_data, data + option_desc.option_->getHeaderLen(),
                            expected_data_len));
    }

    /// @brief Test option configuration.
    ///
    /// This function creates a configuration for a specified option using
    /// a map of parameters specified as the argument. The map holds
    /// name/value pairs which identifies option's configuration parameters:
    /// - name
    /// - space
    /// - code
    /// - data
    /// - csv-format.
    /// This function applies a new server configuration and checks that the
    /// option being configured is inserted into CfgMgr. The raw contents of
    /// this option are compared with the binary data specified as expected
    /// data passed to this function.
    ///
    /// @param params Map of parameters defining an option.
    /// @param option_code Option code.
    /// @param expected_data Array containing binary data expected to be stored
    /// in the configured option.
    /// @param expected_data_len Length of the array holding reference data.
    void testConfiguration(const std::map<std::string, std::string>& params,
                           const uint16_t option_code,
                           const uint8_t* expected_data,
                           const size_t expected_data_len) {
        std::string config = createConfigWithOption(params);
        ASSERT_TRUE(executeConfiguration(config, "parse option configuration"));
        // The subnet should now hold one option with the specified option code.
        OptionDescriptor desc =
            getOptionFromSubnet(IOAddress("192.0.2.24"), option_code);
        ASSERT_TRUE(desc.option_);
        testOption(desc, option_code, expected_data, expected_data_len);
    }

    /// @brief Parse and Execute configuration
    ///
    /// Parses a configuration and executes a configuration of the server.
    /// If the operation fails, the current test will register a failure.
    ///
    /// @param config Configuration to parse
    /// @param operation Operation being performed.  In the case of an error,
    ///        the error text will include the string "unable to <operation>.".
    ///
    /// @return true if the configuration succeeded, false if not.  In the
    ///         latter case, a failure will have been added to the current test.
    bool
    executeConfiguration(const std::string& config, const char* operation) {
        CfgMgr::instance().clear();
        ConstElementPtr json;
        ConstElementPtr status;
        try {
            json = parseJSON(config);
            status = configureDhcp4Server(*srv_, json);
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "Unable to " << operation << ". "
                   << "The following configuration was used: " << std::endl
                   << config << std::endl
                   << " and the following error message was returned:"
                   << ex.what() << std::endl;
            return (false);
        }

        // The status object must not be NULL
        if (!status) {
            ADD_FAILURE() << "Unable to " << operation << ". "
                   << "The configuration function returned a null pointer.";
            return (false);
        }

        // Store the answer if we need it.

        // Returned value should be 0 (configuration success)
        comment_ = parseAnswer(rcode_, status);
        if (rcode_ != 0) {
            string reason = "";
            if (comment_) {
                reason = string(" (") + comment_->stringValue() + string(")");
            }
            ADD_FAILURE() << "Unable to " << operation << ". "
                   << "The configuration function returned error code "
                   << rcode_ << reason;
            return (false);
        }

        return (true);
    }

    /// @brief Reset configuration database.
    ///
    /// This function resets configuration data base by
    /// removing all subnets and option-data. Reset must
    /// be performed after each test to make sure that
    /// contents of the database do not affect result of
    /// subsequent tests.
    void resetConfiguration() {
        string config = "{ " + genIfaceConfig() + "," +
            "\"hooks-libraries\": [ ], "
            "\"valid-lifetime\": 4000, "
            "\"subnet4\": [ ], "
            "\"dhcp-ddns\": { \"enable-updates\" : false }, "
            "\"option-def\": [ ], "
            "\"option-data\": [ ] }";
        static_cast<void>(executeConfiguration(config,
                                               "reset configuration database"));
        CfgMgr::instance().clear();
    }

    /// @brief Retrieve an option associated with a host.
    ///
    /// The option is retrieved from the "dhcp4" option space.
    ///
    /// @param host Reference to a host for which an option should be retrieved.
    /// @param option_code Option code.
    /// @tparam ReturnType Type of the pointer object returned.
    ///
    /// @return Pointer to an option or NULL pointer if not found.
    template<typename ReturnType>
    ReturnType
    retrieveOption(const Host& host, const uint16_t option_code) const {
        return (retrieveOption<ReturnType>(host, DHCP4_OPTION_SPACE, option_code));
    }

    /// @brief Retrieve an option associated with a host.
    ///
    /// @param host Reference to a host for which an option should be retrieved.
    /// @param space Option space from which option should be retrieved.
    /// @param option_code Option code.
    /// @tparam ReturnType Type of the pointer object returned.
    ///
    /// @return Pointer to an option or NULL pointer if not found.
    template<typename ReturnType>
    ReturnType
    retrieveOption(const Host& host, const std::string& space,
                   const uint16_t option_code) const {
        ConstCfgOptionPtr cfg_option = host.getCfgOption4();
        if (cfg_option) {
            OptionDescriptor opt_desc = cfg_option->get(space, option_code);
            if (opt_desc.option_) {
                return (boost::dynamic_pointer_cast<
                        typename ReturnType::element_type>(opt_desc.option_));
            }
        }
        return (ReturnType());
    }

    /// @brief Checks if specified subnet is part of the collection
    ///
    /// @param col collection of subnets to be inspected
    /// @param subnet text notation (e.g. 192.0.2.0/24)
    /// @param t1 expected renew-timer value
    /// @param t2 expected rebind-timer value
    /// @param valid expected valid-lifetime value
    /// @return the subnet that was examined
    Subnet4Ptr
    checkSubnet(const Subnet4Collection& col, std::string subnet,
                uint32_t t1, uint32_t t2, uint32_t valid) {
        const auto& index = col.get<SubnetPrefixIndexTag>();
        auto subnet_it = index.find(subnet);
        if (subnet_it == index.cend()) {
            ADD_FAILURE() << "Unable to find expected subnet " << subnet;
            return (Subnet4Ptr());
        }
        Subnet4Ptr s = *subnet_it;

        EXPECT_EQ(t1, s->getT1());
        EXPECT_EQ(t2, s->getT2());
        EXPECT_EQ(valid, s->getValid());

        return (s);
    }

    /// @brief This utility method attempts to configure using specified
    ///        config and then returns requested pool from requested subnet
    ///
    /// @param config configuration to be applied
    /// @param subnet_index index of the subnet to be returned (0 - the first subnet)
    /// @param pool_index index of the pool within a subnet (0 - the first pool)
    /// @param pool [out] Pool pointer will be stored here (if found)
    void getPool(const std::string& config, size_t subnet_index,
                 size_t pool_index, PoolPtr& pool) {
        ConstElementPtr status;
        ConstElementPtr json;

        EXPECT_NO_THROW(json = parseDHCP4(config, true));
        EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
        ASSERT_TRUE(status);
        checkResult(status, 0);

        ConstCfgSubnets4Ptr subnets4 = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
        ASSERT_TRUE(subnets4);

        const Subnet4Collection* subnets = subnets4->getAll();
        ASSERT_TRUE(subnets);
        ASSERT_GE(subnets->size(), subnet_index + 1);

        const PoolCollection pools = subnets->at(subnet_index)->getPools(Lease::TYPE_V4);
        ASSERT_GE(pools.size(), pool_index + 1);

        pool = pools.at(pool_index);
        EXPECT_TRUE(pool);
    }

    boost::scoped_ptr<Dhcpv4Srv> srv_;  ///< DHCP4 server under test
    int rcode_;                         ///< Return code from element parsing
    ConstElementPtr comment_;           ///< Reason for parse fail
    isc::dhcp::ClientClasses classify_; ///< used in client classification
};

/// The goal of this test is to verify that the code accepts only
/// valid commands and malformed or unsupported parameters are rejected.
TEST_F(Dhcp4ParserTest, bogusCommand) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_,
                    parseJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    checkResult(x, 1);

    // it should be refused by syntax too
    EXPECT_THROW(parseDHCP4("{\"bogus\": 5}"), Dhcp4ParseError);
}

/// The goal of this test is to verify empty interface-config is accepted.
TEST_F(Dhcp4ParserTest, emptyInterfaceConfig) {

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4("{ \"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"valid-lifetime\": 4000 }"));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);
}

/// The goal of this test is to verify if wrongly defined subnet will
/// be rejected. Properly defined subnet must include at least one
/// pool definition.
TEST_F(Dhcp4ParserTest, emptySubnet) {

    std::string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [  ], "
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    EXPECT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);
}

/// Check that the renew-timer doesn't have to be specified, in which case
/// it is marked unspecified in the Subnet.
TEST_F(Dhcp4ParserTest, unspecifiedRenewTimer) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    EXPECT_TRUE(subnet->getT1().unspecified());
    EXPECT_FALSE(subnet->getT2().unspecified());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());

    // Check that subnet-id is 1
    EXPECT_EQ(1, subnet->getID());
}

/// Check that the rebind-timer doesn't have to be specified, in which case
/// it is marked unspecified in the Subnet.
TEST_F(Dhcp4ParserTest, unspecifiedRebindTimer) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_FALSE(subnet->getT1().unspecified());
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_TRUE(subnet->getT2().unspecified());
    EXPECT_EQ(4000, subnet->getValid());

    // Check that subnet-id is 1
    EXPECT_EQ(1, subnet->getID());
}

/// The goal of this test is to verify if defined subnet uses global
/// parameter timer definitions.
TEST_F(Dhcp4ParserTest, subnetGlobalDefaults) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());

    // Check that subnet-id is 1
    EXPECT_EQ(1, subnet->getID());
}

// Goal of this test is to verify that multiple subnets get unique
// subnet-ids. Also, test checks that it's possible to do reconfiguration
// multiple times.
TEST_F(Dhcp4ParserTest, multipleSubnets) {
    ConstElementPtr x;
    // Collection of four subnets for which subnet ids should be
    // autogenerated - ids are unspecified or set to 0.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 0 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.101 - 192.0.5.150\" } ],"
        "    \"subnet\": \"192.0.5.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    int cnt = 0; // Number of reconfigurations

    do {
        EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
        checkResult(x, 0);

        CfgMgr::instance().commit();

        const Subnet4Collection* subnets =
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
        ASSERT_TRUE(subnets);
        ASSERT_EQ(4, subnets->size()); // We expect 4 subnets

        // Check subnet-ids of each subnet (it should be monotonously increasing)
        EXPECT_EQ(1, subnets->at(0)->getID());
        EXPECT_EQ(2, subnets->at(1)->getID());
        EXPECT_EQ(3, subnets->at(2)->getID());
        EXPECT_EQ(4, subnets->at(3)->getID());

        // Repeat reconfiguration process 10 times and check that the subnet-id
        // is set to the same value. Technically, just two iterations would be
        // sufficient, but it's nice to have a test that exercises reconfiguration
        // a bit.
    } while (++cnt < 10);
}

// This test checks that it is possible to assign arbitrary ids for subnets.
TEST_F(Dhcp4ParserTest, multipleSubnetsExplicitIDs) {
    ConstElementPtr x;
    // Four subnets with arbitrary subnet ids.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1024 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 100 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"id\": 1 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.101 - 192.0.5.150\" } ],"
        "    \"subnet\": \"192.0.5.0/24\", "
        "    \"id\": 34 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    int cnt = 0; // Number of reconfigurations
    do {
        EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
        checkResult(x, 0);

        CfgMgr::instance().commit();

        const Subnet4Collection* subnets =
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getAll();
        ASSERT_TRUE(subnets);
        ASSERT_EQ(4, subnets->size()); // We expect 4 subnets

        // Verify that subnet ids are as expected.
        EXPECT_EQ(1024, subnets->at(0)->getID());
        EXPECT_EQ(100, subnets->at(1)->getID());
        EXPECT_EQ(1, subnets->at(2)->getID());
        EXPECT_EQ(34, subnets->at(3)->getID());

        // Repeat reconfiguration process 10 times and check that the subnet-id
        // is set to the same value.
    } while (++cnt < 3);
}

// Check that the configuration with two subnets having the same id is rejected.
TEST_F(Dhcp4ParserTest, multipleSubnetsOverlappingIDs) {
    ConstElementPtr x;
    // Four subnets, two of them having the same id.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1024 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 100 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"id\": 1024 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.101 - 192.0.5.150\" } ],"
        "    \"subnet\": \"192.0.5.0/24\", "
        "    \"id\": 34 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 1);
    EXPECT_TRUE(errorContainsPosition(x, "<string>"));
}

// Goal of this test is to verify that a previously configured subnet can be
// deleted in subsequent reconfiguration.
TEST_F(Dhcp4ParserTest, reconfigureRemoveSubnet) {
    ConstElementPtr x;

    // All four subnets
    string config4 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 2 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"id\": 3 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.101 - 192.0.5.150\" } ],"
        "    \"subnet\": \"192.0.5.0/24\", "
        "    \"id\": 4 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Three subnets (the last one removed)
    string config_first3 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\":  \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 2 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"id\": 3 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Second subnet removed
    string config_second_removed = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 1 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"id\": 3 "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.101 - 192.0.5.150\" } ],"
        "    \"subnet\": \"192.0.5.0/24\", "
        "    \"id\": 4 "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // CASE 1: Configure 4 subnets, then reconfigure and remove the
    // last one.

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config4));
    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    const Subnet4Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(4, subnets->size()); // We expect 4 subnets

    CfgMgr::instance().clear();

    // Do the reconfiguration (the last subnet is removed)
    ASSERT_NO_THROW(json = parseDHCP4(config_first3));
    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    subnets = CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size()); // We expect 3 subnets now (4th is removed)

    // Check subnet-ids of each subnet (it should be monotonously increasing)
    EXPECT_EQ(1, subnets->at(0)->getID());
    EXPECT_EQ(2, subnets->at(1)->getID());
    EXPECT_EQ(3, subnets->at(2)->getID());

    CfgMgr::instance().clear();

    /// CASE 2: Configure 4 subnets, then reconfigure and remove one
    /// from in between (not first, not last)
    ASSERT_NO_THROW(json = parseDHCP4(config4));
    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    CfgMgr::instance().clear();

    // Do reconfiguration
    ASSERT_NO_THROW(json = parseDHCP4(config_second_removed));
    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    subnets = CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size()); // We expect 4 subnets

    EXPECT_EQ(1, subnets->at(0)->getID());
    // The second subnet (with subnet-id = 2) is no longer there
    EXPECT_EQ(3, subnets->at(1)->getID());
    EXPECT_EQ(4, subnets->at(2)->getID());

}

/// @todo: implement subnet removal test as part of #3281.

// Checks if the next-server and other fixed BOOTP fields defined as
// global parameter are taken into consideration.
TEST_F(Dhcp4ParserTest, nextServerGlobal) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"next-server\": \"1.2.3.4\", "
        "\"server-hostname\": \"foo\", "
        "\"boot-file-name\": \"bar\", "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("1.2.3.4", subnet->getSiaddr().get().toText());
    EXPECT_EQ("foo", subnet->getSname().get());
    EXPECT_EQ("bar", subnet->getFilename().get());
}

// Checks if the next-server and other fixed BOOTP fields defined as
// subnet parameter are taken into consideration.
TEST_F(Dhcp4ParserTest, nextServerSubnet) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"next-server\": \"1.2.3.4\", "
        "    \"server-hostname\": \"foo\", "
        "    \"boot-file-name\": \"bar\", "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("1.2.3.4", subnet->getSiaddr().get().toText());
    EXPECT_EQ("foo", subnet->getSname().get());
    EXPECT_EQ("bar", subnet->getFilename().get());
}

// Test checks several negative scenarios for next-server configuration: bogus
// address, IPv6 address and empty string.
TEST_F(Dhcp4ParserTest, nextServerNegative) {
    IfaceMgrTestConfig test_config(true);

    // Config with junk instead of next-server address
    string config_bogus1 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"next-server\": \"a.b.c.d\", "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // Config with IPv6 next server address
    string config_bogus2 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"next-server\": \"2001:db8::1\", "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // Config with empty next server address
    string config_bogus3 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"next-server\": \"\", "
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // Config with too large server-hostname
    string bigsname(Pkt4::MAX_SNAME_LEN + 1, ' ');
    string config_bogus4 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"server-hostname\": \"" + bigsname + "\", " +
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // Config with too large boot-file-hostname
    string bigfilename(Pkt4::MAX_FILE_LEN + 1, ' ');
    string config_bogus5 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"rebind-timer\": 2000, "
        "    \"renew-timer\": 1000, "
        "    \"boot-file-name\": \"" + bigfilename + "\", " +
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";


    ConstElementPtr json1;
    ASSERT_NO_THROW(json1 = parseDHCP4(config_bogus1));
    ConstElementPtr json2;
    ASSERT_NO_THROW(json2 = parseDHCP4(config_bogus2));
    ConstElementPtr json3;
    ASSERT_NO_THROW(json3 = parseDHCP4(config_bogus3));
    ConstElementPtr json4;
    ASSERT_NO_THROW(json4 = parseDHCP4(config_bogus4));
    ConstElementPtr json5;
    ASSERT_NO_THROW(json5 = parseDHCP4(config_bogus5));

    // check if returned status is always a failure
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json1));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json2));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json3));
    checkResult(status, 0);
    EXPECT_FALSE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json4));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json5));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// Checks if the next-server defined as global value is overridden by subnet
// specific value.
TEST_F(Dhcp4ParserTest, nextServerOverride) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"next-server\": \"192.0.0.1\", "
        "\"server-hostname\": \"nohost\","
        "\"boot-file-name\": \"nofile\","
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"next-server\": \"1.2.3.4\", "
        "    \"server-hostname\": \"some-name.example.org\","
        "    \"boot-file-name\": \"bootfile.efi\","
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("1.2.3.4", subnet->getSiaddr().get().toText());
    EXPECT_EQ("some-name.example.org", subnet->getSname().get());
    EXPECT_EQ("bootfile.efi", subnet->getFilename().get());
}

// Check whether it is possible to configure echo-client-id
TEST_F(Dhcp4ParserTest, echoClientId) {

    string config_false = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"echo-client-id\": false,"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    string config_true = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"echo-client-id\": true,"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json_false;
    ASSERT_NO_THROW(json_false = parseDHCP4(config_false));
    extractConfig(config_false);
    ConstElementPtr json_true;
    ASSERT_NO_THROW(json_true = parseDHCP4(config_true));
    extractConfig(config_true);

    // Let's check the default. It should be true
    ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getEchoClientId());

    // Now check that "false" configuration is really applied.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json_false));
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->getEchoClientId());

    CfgMgr::instance().clear();

    // Now check that "true" configuration is really applied.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json_true));
    ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getEchoClientId());

    // In any case revert back to the default value (true)
    CfgMgr::instance().getStagingCfg()->setEchoClientId(true);
}

// This test checks that the global match-client-id parameter is optional
// and that values under the subnet are used.
TEST_F(Dhcp4ParserTest, matchClientIdNoGlobal) {
    std::string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{"
        "    \"match-client-id\": true,"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        "},"
        "{"
        "    \"match-client-id\": false,"
        "    \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"subnet\": \"192.0.3.0/24\""
        "} ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 0);

    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet1 = cfg->selectSubnet(IOAddress("192.0.2.1"));
    ASSERT_TRUE(subnet1);
    EXPECT_TRUE(subnet1->getMatchClientId());

    Subnet4Ptr subnet2 = cfg->selectSubnet(IOAddress("192.0.3.1"));
    ASSERT_TRUE(subnet2);
    EXPECT_FALSE(subnet2->getMatchClientId());
}

// This test checks that the global match-client-id parameter is used
// when there is no such parameter under subnet and that the parameter
// specified for a subnet overrides the global setting.
TEST_F(Dhcp4ParserTest, matchClientIdGlobal) {
    std::string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"match-client-id\": true,"
        "\"subnet4\": [ "
        "{"
        "    \"match-client-id\": false,"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        "},"
        "{"
        "    \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"subnet\": \"192.0.3.0/24\""
        "} ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 0);

    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet1 = cfg->selectSubnet(IOAddress("192.0.2.1"));
    ASSERT_TRUE(subnet1);
    EXPECT_FALSE(subnet1->getMatchClientId());

    Subnet4Ptr subnet2 = cfg->selectSubnet(IOAddress("192.0.3.1"));
    ASSERT_TRUE(subnet2);
    EXPECT_TRUE(subnet2->getMatchClientId());
}

// This test checks that the global authoritative parameter is optional
// and that values under the subnet are used.
TEST_F(Dhcp4ParserTest, authoritativeNoGlobal) {
    std::string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        "{"
        "    \"authoritative\": true,"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        "},"
        "{"
        "    \"authoritative\": false,"
        "    \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"subnet\": \"192.0.3.0/24\""
        "} ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 0);

    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet1 = cfg->selectSubnet(IOAddress("192.0.2.1"));
    ASSERT_TRUE(subnet1);
    EXPECT_TRUE(subnet1->getAuthoritative());

    Subnet4Ptr subnet2 = cfg->selectSubnet(IOAddress("192.0.3.1"));
    ASSERT_TRUE(subnet2);
    EXPECT_FALSE(subnet2->getAuthoritative());
}

// This test checks that the global authoritative parameter is used
// when there is no such parameter under subnet and that the parameter
// specified for a subnet overrides the global setting.
TEST_F(Dhcp4ParserTest, authoritativeGlobal) {
    std::string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"authoritative\": true,"
        "\"subnet4\": [ "
        "{"
        "    \"authoritative\": false,"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        "},"
        "{"
        "    \"pools\": [ { \"pool\": \"192.0.3.1 - 192.0.3.100\" } ],"
        "    \"subnet\": \"192.0.3.0/24\""
        "} ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 0);

    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet1 = cfg->selectSubnet(IOAddress("192.0.2.1"));
    ASSERT_TRUE(subnet1);
    EXPECT_FALSE(subnet1->getAuthoritative());

    Subnet4Ptr subnet2 = cfg->selectSubnet(IOAddress("192.0.3.1"));
    ASSERT_TRUE(subnet2);
    EXPECT_TRUE(subnet2->getAuthoritative());
}

// This test checks if it is possible to override global values
// on a per subnet basis.
TEST_F(Dhcp4ParserTest, subnetLocal) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"valid-lifetime\": 4,"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getT1());
    EXPECT_EQ(2, subnet->getT2());
    EXPECT_EQ(4, subnet->getValid());
}

// This test checks that multiple pools can be defined and handled properly.
// The test defines 2 subnets, each with 2 pools.
TEST_F(Dhcp4ParserTest, multiplePools) {

    // Collection with two subnets, each with 2 pools.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ "
        "        { \"pool\": \"192.0.2.0/28\" },"
        "        { \"pool\": \"192.0.2.200-192.0.2.255\" }"
        "    ],"
        "    \"subnet\": \"192.0.2.0/24\" "
        " },"
        " {"
        "    \"pools\": [ "
        "    { \"pool\": \"192.0.3.0/25\" },"
        "    { \"pool\": \"192.0.3.128/25\" }"
        "    ],"
        "    \"subnet\": \"192.0.3.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 0);

    const Subnet4Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(2, subnets->size()); // We expect 2 subnets

    // Check the first subnet
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_V4);
    ASSERT_EQ(2, pools1.size());
    EXPECT_EQ("type=V4, 192.0.2.0-192.0.2.15",
              pools1[0]->toText());
    EXPECT_EQ("type=V4, 192.0.2.200-192.0.2.255",
              pools1[1]->toText());
    // There shouldn't be any TA or PD pools
    EXPECT_THROW(subnets->at(0)->getPools(Lease::TYPE_TA), BadValue);
    EXPECT_THROW(subnets->at(0)->getPools(Lease::TYPE_PD), BadValue);

    // Check the second subnet
    const PoolCollection& pools2 = subnets->at(1)->getPools(Lease::TYPE_V4);
    ASSERT_EQ(2, pools2.size());
    EXPECT_EQ("type=V4, 192.0.3.0-192.0.3.127",
              pools2[0]->toText());
    EXPECT_EQ("type=V4, 192.0.3.128-192.0.3.255",
              pools2[1]->toText());
    // There shouldn't be any TA or PD pools
    EXPECT_THROW(subnets->at(0)->getPools(Lease::TYPE_TA).empty(), BadValue);
    EXPECT_THROW(subnets->at(0)->getPools(Lease::TYPE_PD).empty(), BadValue);
}

// Test verifies that a subnet with pool values that do not belong to that
// pool are rejected.
TEST_F(Dhcp4ParserTest, poolOutOfSubnet) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.4.0/28\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value must be 1 (values error)
    // as the pool does not belong to that subnet
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// Goal of this test is to verify if pools can be defined
// using prefix/length notation. There is no separate test for min-max
// notation as it was tested in several previous tests.
TEST_F(Dhcp4ParserTest, poolPrefixLen) {

    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.128/28\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value must be 0 (configuration accepted)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());
}

// Goal of this test is to verify if invalid pool definitions
// return a location in the error message.
TEST_F(Dhcp4ParserTest, badPools) {

    // not a prefix
    string config_bogus1 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"foo/28\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // not a length
    string config_bogus2 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.128/foo\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // invalid prefix length
    string config_bogus3 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.128/100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // not a prefix nor a min-max
    string config_bogus4 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"foo\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // not an address
    string config_bogus5 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"foo - bar\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // min > max
    string config_bogus6 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.200 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    // out of range prefix length (new check)
    string config_bogus7 = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.128/1052\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json1;
    ASSERT_NO_THROW(json1 = parseDHCP4(config_bogus1));
    ConstElementPtr json2;
    ASSERT_NO_THROW(json2 = parseDHCP4(config_bogus2));
    ConstElementPtr json3;
    ASSERT_NO_THROW(json3 = parseDHCP4(config_bogus3));
    ConstElementPtr json4;
    ASSERT_NO_THROW(json4 = parseDHCP4(config_bogus4));
    ConstElementPtr json5;
    ASSERT_NO_THROW(json5 = parseDHCP4(config_bogus5));
    ConstElementPtr json6;
    ASSERT_NO_THROW(json6 = parseDHCP4(config_bogus6));
    ConstElementPtr json7;
    ASSERT_NO_THROW(json7 = parseDHCP4(config_bogus7));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json1));

    // check if returned status is always a failure
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json2));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json3));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json4));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json5));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json6));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json7));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// Goal of this test is to verify no pool definitions is invalid
// and returns a location in the error message.
TEST_F(Dhcp4ParserTest, noPools) {

    // Configuration string.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"user-context\": { } } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    EXPECT_THROW(parseDHCP4(config, true), Dhcp4ParseError);
}

// Goal of this test is to verify that invalid subnet fails to be parsed.
TEST_F(Dhcp4ParserTest, badSubnetValues) {

    // Contains parts needed for a single test scenario.
    struct Scenario {
        std::string description_;
        std::string config_json_;
        std::string exp_error_msg_;
    };

    // Vector of scenarios.
    std::vector<Scenario> scenarios = {
        {
        "IP is not an address",
        "{ \"subnet4\": [ { "
        "    \"subnet\": \"not an address/24\" } ],"
        "\"valid-lifetime\": 4000 }",
        "subnet configuration failed: "
        "Failed to convert string to address 'notanaddress': Invalid argument"
        },
        {
        "IP is Invalid",
        "{ \"subnet4\": [ { "
        "    \"subnet\": \"256.16.1.0/24\" } ],"
        "\"valid-lifetime\": 4000 }",
        "subnet configuration failed: "
        "Failed to convert string to address '256.16.1.0': Invalid argument"
        },
        {
        "Missing prefix",
        "{ \"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0\" } ],"
        "\"valid-lifetime\": 4000 }",
        "subnet configuration failed: "
        "Invalid subnet syntax (prefix/len expected):192.0.2.0 (<string>:1:32)"
        },
        {
        "Prefix not an integer (2 slashes)",
        "{ \"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0//24\" } ],"
        "\"valid-lifetime\": 4000 }",
        "subnet configuration failed: "
        "prefix length: '/24' is not an integer (<string>:1:32)"
        },
        {
        "Prefix value is insane",
        "{ \"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/45938\" } ],"
        "\"valid-lifetime\": 4000 }",
        "subnet configuration failed: "
        "Invalid prefix length specified for subnet: 45938 (<string>:1:32)"
        }
    };

    // Iterate over the list of scenarios.  Each should fail to parse with
    // a specific error message.
    for (auto scenario = scenarios.begin(); scenario != scenarios.end(); ++scenario) {
        {
            SCOPED_TRACE((*scenario).description_);
            ConstElementPtr config;
            ASSERT_NO_THROW(config = parseDHCP4((*scenario).config_json_))
                            << "invalid json, broken test";
            ConstElementPtr status;
            EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, config));
            checkResult(status, 1);
            EXPECT_EQ(comment_->stringValue(), (*scenario).exp_error_msg_);
        }
    }
}

// Goal of this test is to verify that unknown interface fails
// to be parsed.
TEST_F(Dhcp4ParserTest, unknownInterface) {

    // Configuration string.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"interface\": \"ethX\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// The goal of this test is to check whether an option definition
// that defines an option carrying an IPv4 address can be created.
TEST_F(Dhcp4ParserTest, optionDefIpv4Address) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config, true));
    extractConfig(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // We need to commit option definitions because later in this test we
    // will be checking if they get removed when "option-def" parameter
    // is removed from a configuration.
    LibDHCP::commitRuntimeOptionDefs();

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Verify that the option definition data is valid.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, def->getType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());

    // The copy of the option definition should be available in the libdhcp++.
    OptionDefinitionPtr def_libdhcp = LibDHCP::getRuntimeOptionDef("isc", 100);
    ASSERT_TRUE(def_libdhcp);

    // Both definitions should be held in distinct pointers but they should
    // be equal.
    EXPECT_TRUE(def_libdhcp != def);
    EXPECT_TRUE(*def_libdhcp == *def);

    // Let's apply empty configuration. This removes the option definitions
    // configuration and should result in removal of the option 100 from the
    // libdhcp++. Note DHCP4 or OPTION_DEFS parsers do not accept empty maps.
    json.reset(new MapElement());
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    checkResult(status, 0);

    EXPECT_FALSE(LibDHCP::getRuntimeOptionDef("isc", 100));
}

// The goal of this test is to check whether an option definition
// that defines an option carrying a record of data fields can
// be created.
TEST_F(Dhcp4ParserTest, optionDefRecord) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"record\","
        "      \"record-types\": \"uint16, ipv4-address, ipv6-address, string\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));
    extractConfig(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_RECORD_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());

    // The option comprises the record of data fields. Verify that all
    // fields are present and they are of the expected types.
    const OptionDefinition::RecordFieldsCollection& record_fields =
        def->getRecordFields();
    ASSERT_EQ(4, record_fields.size());
    EXPECT_EQ(OPT_UINT16_TYPE, record_fields[0]);
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, record_fields[1]);
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, record_fields[2]);
    EXPECT_EQ(OPT_STRING_TYPE, record_fields[3]);
}

// The goal of this test is to verify that multiple option definitions
// can be created.
TEST_F(Dhcp4ParserTest, optionDefMultiple) {
    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"space\": \"isc\""
        "  },"
        "  {"
        "      \"name\": \"foo-2\","
        "      \"code\": 101,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));
    extractConfig(config);

    // Make sure that the option definitions do not exist yet.
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->
                 getCfgOptionDef()->get("isc", 100));
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->
                 getCfgOptionDef()->get("isc", 101));

    // Use the configuration string to create new option definitions.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Check the first definition we have created.
    OptionDefinitionPtr def1 = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def1);

    // Check the option data.
    EXPECT_EQ("foo", def1->getName());
    EXPECT_EQ(100, def1->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def1->getType());
    EXPECT_FALSE(def1->getArrayType());
    EXPECT_TRUE(def1->getEncapsulatedSpace().empty());

    // Check the second option definition we have created.
    OptionDefinitionPtr def2 = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 101);
    ASSERT_TRUE(def2);

    // Check the option data.
    EXPECT_EQ("foo-2", def2->getName());
    EXPECT_EQ(101, def2->getCode());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, def2->getType());
    EXPECT_FALSE(def2->getArrayType());
    EXPECT_TRUE(def2->getEncapsulatedSpace().empty());
}

// The goal of this test is to verify that the duplicated option
// definition is not accepted.
TEST_F(Dhcp4ParserTest, optionDefDuplicate) {
    // Preconfigure libdhcp++ with option definitions. The new configuration
    // should override it, but when the new configuration fails, it should
    // revert to this original configuration.
    OptionDefSpaceContainer defs;
    OptionDefinitionPtr def(new OptionDefinition("bar", 233, "string"));
    defs.addItem(def, "isc");
    LibDHCP::setRuntimeOptionDefs(defs);
    LibDHCP::commitRuntimeOptionDefs();

    // Configuration string. Both option definitions have
    // the same code and belong to the same option space.
    // This configuration should not be accepted.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"space\": \"isc\""
        "  },"
        "  {"
        "      \"name\": \"foo-2\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Make sure that the option definition does not exist yet.
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->
                 getCfgOptionDef()->get("isc", 100));

    // Use the configuration string to create new option definitions.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    // The new configuration should have inserted option 100, but
    // once configuration failed (on the duplicate option definition)
    // the original configuration in libdhcp++ should be reverted.
    EXPECT_FALSE(LibDHCP::getRuntimeOptionDef("isc", 100));
    def = LibDHCP::getRuntimeOptionDef("isc", 233);
    ASSERT_TRUE(def);
    EXPECT_EQ("bar", def->getName());
    EXPECT_EQ(233, def->getCode());
}

// The goal of this test is to verify that the option definition
// comprising an array of uint32 values can be created.
TEST_F(Dhcp4ParserTest, optionDefArray) {

    // Configuration string. Created option definition should
    // comprise an array of uint32 values.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": true,"
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));
    extractConfig(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def->getType());
    EXPECT_TRUE(def->getArrayType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());
}

// The purpose of this test to verify that encapsulated option
// space name may be specified.
TEST_F(Dhcp4ParserTest, optionDefEncapsulate) {

    // Configuration string. Included the encapsulated
    // option space name.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"sub-opts-space\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));
    extractConfig(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ("sub-opts-space", def->getEncapsulatedSpace());
}

/// The purpose of this test is to verify that the option definition
/// with invalid name is not accepted.
TEST_F(Dhcp4ParserTest, optionDefInvalidName) {
    // Configuration string. The option name is invalid as it
    // contains the % character.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"invalid%name\","
        "      \"code\": 100,"
        "      \"type\": \"string\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that the option definition
/// with invalid type is not accepted.
TEST_F(Dhcp4ParserTest, optionDefInvalidType) {
    // Configuration string. The option type is invalid. It is
    // "sting" instead of "string".
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"sting\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that the option definition
/// with invalid type is not accepted.
TEST_F(Dhcp4ParserTest, optionDefInvalidRecordType) {
    // Configuration string. The third of the record fields
    // is invalid. It is "sting" instead of "string".
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"record\","
        "      \"record-types\": \"uint32,uint8,sting\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that various integer types
/// are supported.
TEST_F(Dhcp4ParserTest, optionIntegerTypes) {
    // Configuration string. The third of the record fields
    // is invalid. It is "sting" instead of "string".
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"record\","
        "      \"record-types\": \"uint8,uint16,uint32,int8,int16,int32\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 0);
}

/// The goal of this test is to verify that the invalid encapsulated
/// option space name is not accepted.
TEST_F(Dhcp4ParserTest, optionDefInvalidEncapsulatedSpace) {
    // Configuration string. The encapsulated option space
    // name is invalid (% character is not allowed).
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"invalid%space%name\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The goal of this test is to verify that the encapsulated
/// option space name can't be specified for the option that
/// comprises an array of data fields.
TEST_F(Dhcp4ParserTest, optionDefEncapsulatedSpaceAndArray) {
    // Configuration string. The encapsulated option space
    // name is set to non-empty value and the array flag
    // is set.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": true,"
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"valid-space-name\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The goal of this test is to verify that the option may not
/// encapsulate option space it belongs to.
TEST_F(Dhcp4ParserTest, optionDefEncapsulateOwnSpace) {
    // Configuration string. Option is set to encapsulate
    // option space it belongs to.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"isc\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that it is not allowed
/// to override the standard option (that belongs to dhcp4 option
/// space and has its definition) and that it is allowed to define
/// option in the dhcp4 option space that has a code which is not
/// used by any of the standard options.
TEST_F(Dhcp4ParserTest, optionStandardDefOverride) {

    // Configuration string. The option code 109 is unassigned so it
    // can be used for a custom option definition in dhcp4 option space.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 109,"
        "      \"type\": \"string\","
        "      \"space\": \"dhcp4\""
        "  } ]"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));
    extractConfig(config);

    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get(DHCP4_OPTION_SPACE, 109);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get(DHCP4_OPTION_SPACE, 109);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(109, def->getCode());
    EXPECT_EQ(OPT_STRING_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());

    // The combination of option space and code is invalid. The 'dhcp4' option
    // space groups standard options and the code 3 is reserved for one of
    // them.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"routers\","
        "      \"code\": 3,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"dhcp4\""
        "  } ]"
        "}";
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));

    // Use the configuration string to create new option definition.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    /// There is no definition for unassigned option 170.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"unassigned-option-170\","
        "      \"code\": 170,"
        "      \"type\": \"string\","
        "      \"space\": \"dhcp4\""
        "  } ]"
        "}";
    ASSERT_NO_THROW(json = parseOPTION_DEFS(config));
    extractConfig(config);

    // Use the configuration string to create new option definition.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    // Expecting success.
    checkResult(status, 0);

    def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get(DHCP4_OPTION_SPACE, 170);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("unassigned-option-170", def->getName());
    EXPECT_EQ(170, def->getCode());
    EXPECT_EQ(OPT_STRING_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());

}

// Goal of this test is to verify that global option data is configured
TEST_F(Dhcp4ParserTest, optionDataDefaultsGlobal) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"dhcp-message\","
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": false"
        " },"
        " {"
        "    \"name\": \"default-ip-ttl\","
        "    \"data\": \"01\","
        "    \"csv-format\": false"
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    // These options are global
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    OptionContainerPtr options = subnet->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(0, options->size());

    options = CfgMgr::instance().getStagingCfg()->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 56.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(23);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 23, foo2_expected, sizeof(foo2_expected));

    // Check that options with other option codes are not returned.
    for (uint8_t code = 24; code < 35; ++code) {
        range = idx.equal_range(code);
        EXPECT_EQ(0, std::distance(range.first, range.second));
    }
}

// Goal of this test is to verify that subnet option data is configured
TEST_F(Dhcp4ParserTest, optionDataDefaultsSubnet) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"option-data\": [ {"
        "        \"name\": \"dhcp-message\","
        "        \"data\": \"ABCDEF0105\","
        "        \"csv-format\": false"
        "     },"
        "     {"
        "        \"name\": \"default-ip-ttl\","
        "        \"data\": \"01\","
        "        \"csv-format\": false"
        "     } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    // These options are subnet options
    OptionContainerPtr options =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(0, options->size());

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    options = subnet->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 56.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(23);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 23, foo2_expected, sizeof(foo2_expected));
}

/// The goal of this test is to verify that two options having the same
/// option code can be added to different option spaces.
TEST_F(Dhcp4ParserTest, optionDataTwoSpaces) {

    // This configuration string is to configure two options
    // sharing the code 56 and having different definitions
    // and belonging to the different option spaces.
    // The option definition must be provided for the
    // option that belongs to the 'isc' option space.
    // The definition is not required for the option that
    // belongs to the 'dhcp4' option space as it is the
    // standard option.
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"dhcp-message\","
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": false"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"data\": \"1234\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 56,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Options should be now available
    // Try to get the option from the space dhcp4.
    OptionDescriptor desc1 =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get(DHCP4_OPTION_SPACE, 56);
    ASSERT_TRUE(desc1.option_);
    EXPECT_EQ(56, desc1.option_->getType());
    // Try to get the option from the space isc.
    OptionDescriptor desc2 =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get("isc", 56);
    ASSERT_TRUE(desc2.option_);
    EXPECT_EQ(56, desc1.option_->getType());
    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    OptionDescriptor desc3 =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get("non-existing", 56);
    ASSERT_FALSE(desc3.option_);
}

// The goal of this test is to verify that it is possible to
// encapsulate option space containing some options with
// another option. In this test we create base option that
// encapsulates option space 'isc' that comprises two other
// options. Also, for all options their definitions are
// created.
TEST_F(Dhcp4ParserTest, optionDataEncapsulate) {

    // @todo DHCP configurations has many dependencies between
    // parameters. First of all, configuration for subnet was
    // inherited from the global values. Thus subnet had to be
    // configured when all global values have been configured.
    // Also, an option can encapsulate another option only
    // if the latter has been configured. For this reason in this
    // test we created two-stage configuration where first we
    // created options that belong to encapsulated option space.
    // In the second stage we add the base option. Also, the Subnet
    // object is configured in the second stage so it is created
    // at the very end (when all other parameters are configured).

    // Starting stage 1. Configure sub-options and their definitions.
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"isc\","
        "    \"data\": \"192.168.2.1\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 1,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 2,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"isc\""
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    CfgMgr::instance().clear();

    // Stage 2. Configure base option and a subnet. Please note that
    // the configuration from the stage 2 is repeated because Kea
    // configuration manager sends whole configuration for the lists
    // where at least one element is being modified or added.
    config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 3000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"base-option\","
        "    \"data\": \"11\""
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"isc\","
        "    \"data\": \"192.168.2.1\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"base-option\","
        "    \"code\": 222,"
        "    \"type\": \"uint8\","
        "    \"space\": \"dhcp4\","
        "    \"encapsulate\": \"isc\""
        "},"
        "{"
        "    \"name\": \"foo\","
        "    \"code\": 1,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 2,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"isc\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ]"
        "}";

    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // We should have one option available.
    OptionContainerPtr options =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the option.
    OptionDescriptor desc =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get(DHCP4_OPTION_SPACE, 222);
    EXPECT_TRUE(desc.option_);
    EXPECT_EQ(222, desc.option_->getType());

    // This option should comprise two sub-options.
    // One of them is 'foo' with code 1.
    OptionPtr option_foo = desc.option_->getOption(1);
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(1, option_foo->getType());

    // ...another one 'foo2' with code 2.
    OptionPtr option_foo2 = desc.option_->getOption(2);
    ASSERT_TRUE(option_foo2);
    EXPECT_EQ(2, option_foo2->getType());
}

// Goal of this test is to verify options configuration
// for a single subnet. In particular this test checks
// that local options configuration overrides global
// option setting.
TEST_F(Dhcp4ParserTest, optionDataInSingleSubnet) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "      \"name\": \"dhcp-message\","
        "      \"data\": \"AB\","
        "      \"csv-format\": false"
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": [ {"
        "          \"name\": \"dhcp-message\","
        "          \"data\": \"ABCDEF0105\","
        "          \"csv-format\": false"
        "        },"
        "        {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"01\","
        "          \"csv-format\": false"
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.24"));
    ASSERT_TRUE(subnet);
    OptionContainerPtr options = subnet->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(23);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 23, foo2_expected, sizeof(foo2_expected));
}

// The goal of this test is to check that the option carrying a boolean
// value can be configured using one of the values: "true", "false", "0"
// or "1".
TEST_F(Dhcp4ParserTest, optionDataBoolean) {
    // Create configuration. Use standard option 19 (ip-forwarding).
    std::map<std::string, std::string> params;
    params["name"] = "ip-forwarding";
    params["space"] = DHCP4_OPTION_SPACE;
    params["code"] = "19";
    params["data"] = "true";
    params["csv-format"] = "true";

    std::string config = createConfigWithOption(params);
    ASSERT_TRUE(executeConfiguration(config, "parse configuration with a"
                                     " boolean value"));

    // The subnet should now hold one option with the code 19.
    OptionDescriptor desc = getOptionFromSubnet(IOAddress("192.0.2.24"),
                                                        19);
    ASSERT_TRUE(desc.option_);

    // This option should be set to "true", represented as 0x1 in the option
    // buffer.
    uint8_t expected_option_data[] = {
        0x1
    };
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // Configure the option with the "1" value. This should have the same
    // effect as if "true" was specified.
    params["data"] = "1";
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // The value of "1" with a few leading zeros should work too.
    params["data"] = "00001";
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // Configure the option with the "false" value.
    params["data"] = "false";
    // The option buffer should now hold the value of 0.
    expected_option_data[0] = 0;
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // Specifying "0" should have the same effect as "false".
    params["data"] = "0";
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // The same effect should be for multiple 0 chars.
    params["data"] = "00000";
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // Bogus values should not be accepted.
    params["data"] = "bogus";
    testInvalidOptionParam(params);

    params["data"] = "2";
    testInvalidOptionParam(params);

    // Now let's test that it is possible to use binary format.
    params["data"] = "0";
    params["csv-format"] = "false";
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // The binary 1 should work as well.
    params["data"] = "1";
    expected_option_data[0] = 1;
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

    // As well as an even number of digits.
    params["data"] = "01";
    testConfiguration(params, 19, expected_option_data,
                      sizeof(expected_option_data));

}

// Goal of this test is to verify options configuration
// for multiple subnets.
TEST_F(Dhcp4ParserTest, optionDataInMultipleSubnets) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": [ {"
        "          \"name\": \"dhcp-message\","
        "          \"data\": \"0102030405060708090A\","
        "          \"csv-format\": false"
        "        } ]"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"option-data\": [ {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"FF\","
        "          \"csv-format\": false"
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    Subnet4Ptr subnet1 = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.100"));
    ASSERT_TRUE(subnet1);
    OptionContainerPtr options1 = subnet1->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(1, options1->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx1 = options1->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range1 =
        idx1.equal_range(56);
    // Expect single option with the code equal to 56.
    ASSERT_EQ(1, std::distance(range1.first, range1.second));
    const uint8_t foo_expected[] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range1.first, 56, foo_expected, sizeof(foo_expected));

    // Test another subnet in the same way.
    Subnet4Ptr subnet2 = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.3.102"));
    ASSERT_TRUE(subnet2);
    OptionContainerPtr options2 = subnet2->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(1, options2->size());

    const OptionContainerTypeIndex& idx2 = options2->get<1>();
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range2 =
        idx2.equal_range(23);
    ASSERT_EQ(1, std::distance(range2.first, range2.second));

    const uint8_t foo2_expected[] = { 0xFF };
    testOption(*range2.first, 23, foo2_expected, sizeof(foo2_expected));
}

// This test verifies that it is possible to specify options on
// pool levels.
TEST_F(Dhcp4ParserTest, optionDataSinglePool) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { "
        "        \"pool\": \"192.0.2.1 - 192.0.2.100\","
        "        \"option-data\": [ {"
        "            \"name\": \"dhcp-message\","
        "            \"data\": \"ABCDEF0105\","
        "            \"csv-format\": false"
        "        },"
        "        {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"01\","
        "          \"csv-format\": false"
        "        } ]"
        "    } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->
        selectSubnet(IOAddress("192.0.2.24"), classify_);
    ASSERT_TRUE(subnet);

    PoolPtr pool = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.2.24"), false);
    ASSERT_TRUE(pool);
    Pool4Ptr pool4 = boost::dynamic_pointer_cast<Pool4>(pool);
    ASSERT_TRUE(pool4);

    OptionContainerPtr options = pool4->getCfgOption()->getAll("dhcp4");
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect a single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(23);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 23, foo2_expected, sizeof(foo2_expected));
}

// This test verifies that it's possible to define different options in
// different pools and those options are not confused.
TEST_F(Dhcp4ParserTest, optionDataMultiplePools) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { "
        "        \"pool\": \"192.0.2.1 - 192.0.2.100\","
        "        \"option-data\": [ {"
        "            \"name\": \"dhcp-message\","
        "            \"data\": \"ABCDEF0105\","
        "            \"csv-format\": false"
        "        } ]"
        "    },"
        "    {"
        "        \"pool\": \"192.0.2.200 - 192.0.2.250\","
        "        \"option-data\": [ {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"01\","
        "          \"csv-format\": false"
        "        } ]"
        "    } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->
        selectSubnet(IOAddress("192.0.2.24"), classify_);
    ASSERT_TRUE(subnet);

    PoolPtr pool1 = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.2.24"), false);
    ASSERT_TRUE(pool1);
    Pool4Ptr pool41 = boost::dynamic_pointer_cast<Pool4>(pool1);
    ASSERT_TRUE(pool41);

    OptionContainerPtr options1 = pool41->getCfgOption()->getAll("dhcp4");
    ASSERT_EQ(1, options1->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx1 = options1->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range1 =
        idx1.equal_range(56);
    // Expect a single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range1.first, range1.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range1.first, 56, foo_expected, sizeof(foo_expected));

    // Test another pool in the same way.
    PoolPtr pool2 = subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.2.240"), false);
    ASSERT_TRUE(pool2);
    Pool4Ptr pool42 = boost::dynamic_pointer_cast<Pool4>(pool2);
    ASSERT_TRUE(pool42);

    OptionContainerPtr options2 = pool42->getCfgOption()->getAll("dhcp4");
    ASSERT_EQ(1, options2->size());

    const OptionContainerTypeIndex& idx2 = options2->get<1>();
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range2 =
        idx2.equal_range(23);
    ASSERT_EQ(1, std::distance(range2.first, range2.second));
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range2.first, 23, foo2_expected, sizeof(foo2_expected));
}


// Verify that empty option name is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionNameEmpty) {
    // Empty option names not allowed.
    testInvalidOptionParam("", "name");
}

// Verify that empty option name with spaces is rejected
// in the configuration.
TEST_F(Dhcp4ParserTest, optionNameSpaces) {
    // Spaces in option names not allowed.
    testInvalidOptionParam("option foo", "name");
}

// Verify that negative option code is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionCodeNegative) {
    // Check negative option code -4. This should fail too.
    testInvalidOptionParam("-4", "code");
}

// Verify that out of bounds option code is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionCodeNonUint8) {
    // The valid option codes are uint16_t values so passing
    // uint16_t maximum value incremented by 1 should result
    // in failure.
    testInvalidOptionParam("257", "code");
}

// Verify that zero option code is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionCodeZero) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0", "code");
}

// Verify that option data which contains non hexadecimal characters
// is rejected by the configuration.
TEST_F(Dhcp4ParserTest, optionDataInvalidChar) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("01020R", "data");
}

// Verify that option data containing '0x' prefix is rejected
// by the configuration.
TEST_F(Dhcp4ParserTest, optionDataUnexpectedPrefix) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0x0102", "data");
}

// Verify that either lower or upper case characters are allowed
// to specify the option data.
TEST_F(Dhcp4ParserTest, optionDataLowerCase) {
    ConstElementPtr x;
    std::string config = createConfigWithOption("0a0b0C0D", "data");
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.5"));
    ASSERT_TRUE(subnet);
    OptionContainerPtr options = subnet->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(1, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0x0A, 0x0B, 0x0C, 0x0D
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));
}

// Verify that specific option object is returned for standard
// option which has dedicated option class derived from Option.
TEST_F(Dhcp4ParserTest, stdOptionData) {
    ConstElementPtr x;
    std::map<std::string, std::string> params;
    params["name"] = "nis-servers";
    params["space"] = DHCP4_OPTION_SPACE;
    // Option code 41 means nis-servers.
    params["code"] = "41";
    // Specify option values in a CSV (user friendly) format.
    params["data"] = "192.0.2.10, 192.0.2.1, 192.0.2.3";
    params["csv-format"] = "true";

    std::string config = createConfigWithOption(params);
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.5"));
    ASSERT_TRUE(subnet);
    OptionContainerPtr options =
        subnet->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(DHO_NIS_SERVERS);
    // Expect single option with the code equal to NIS_SERVERS option code.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // The actual pointer to the option is held in the option field
    // in the structure returned.
    OptionPtr option = range.first->option_;
    ASSERT_TRUE(option);
    // Option object returned for here is expected to be Option6IA
    // which is derived from Option. This class is dedicated to
    // represent standard option IA_NA.
    boost::shared_ptr<Option4AddrLst> option_addrs =
        boost::dynamic_pointer_cast<Option4AddrLst>(option);
    // If cast is unsuccessful than option returned was of a
    // different type than Option6IA. This is wrong.
    ASSERT_TRUE(option_addrs);

    // Get addresses from the option.
    Option4AddrLst::AddressContainer addrs = option_addrs->getAddresses();
    // Verify that the addresses have been configured correctly.
    ASSERT_EQ(3, addrs.size());
    EXPECT_EQ("192.0.2.10", addrs[0].toText());
    EXPECT_EQ("192.0.2.1", addrs[1].toText());
    EXPECT_EQ("192.0.2.3", addrs[2].toText());
}

/// This test checks if Uint32Parser can really parse the whole range
/// and properly err of out of range values. As we can't call Uint32Parser
/// directly, we are exploiting the fact that it is used to parse global
/// parameter renew-timer and the results are stored in uint32_defaults.
/// We get the uint32_defaults using a getUint32Defaults functions which
/// is defined only to access the values from this test.
TEST_F(Dhcp4ParserTest, DISABLED_Uint32Parser) {

    ConstElementPtr status;

    // CASE 1: 0 - minimum value, should work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    parseDHCP4("{\"renew-timer\": 0}")));

    // returned value must be ok (0 is a proper value)
    checkResult(status, 0);
    /// @todo: check that the renew-timer is really 0

    // CASE 2: 4294967295U (UINT_MAX) should work as well
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    parseDHCP4("{\"renew-timer\": 4294967295}")));

    // returned value must be ok (0 is a proper value)
    checkResult(status, 0);
    /// @todo: check that the renew-timer is really 4294967295U

    // CASE 3: 4294967296U (UINT_MAX + 1) should not work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    parseJSON("{\"renew-timer\": 4294967296}")));

    // returned value must be rejected (1 configuration error)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    // CASE 4: -1 (UINT_MIN -1 ) should not work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    parseJSON("{\"renew-timer\": -1}")));

    // returned value must be rejected (1 configuration error)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// The goal of this test is to verify that the domain-search option
// can be set using domain names
TEST_F(Dhcp4ParserTest, domainSearchOption) {
    // Create configuration.
    std::map<std::string, std::string> params;
    params["name"] = "domain-search";
    params["space"] = DHCP4_OPTION_SPACE;
    params["code"] = "119"; // DHO_DOMAIN_SEARCH
    params["data"] = "mydomain.example.com, example.com";
    params["csv-format"] = "true";

    std::string config = createConfigWithOption(params);
    EXPECT_TRUE(executeConfiguration(config, "parse configuration with a"
                                     " domain-search option"));
}

// The goal of this test is to verify that the slp-directory-agent
// option can be set using a trailing array of addresses and
// slp-service-scope without option scope list
TEST_F(Dhcp4ParserTest, slpOptions) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"slp-directory-agent\","
        "    \"data\": \"true, 10.0.0.3, 127.0.0.1\""
        " },"
        " {"
        "    \"name\": \"slp-service-scope\","
        "    \"data\": \"false, \""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    // Get options
    OptionContainerPtr options = CfgMgr::instance().getStagingCfg()->
        getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(DHO_DIRECTORY_AGENT);
    // Expect a single option with the code equal to 78.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t sda_expected[] = {
        0x01, 0x0a, 0x00, 0x00, 0x03, 0x7f, 0x00, 0x00, 0x01
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 78, sda_expected, sizeof(sda_expected));

    range = idx.equal_range(DHO_SERVICE_SCOPE);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t sss_expected[] = {
        0x00
    };
    testOption(*range.first, 79, sss_expected, sizeof(sss_expected));
}

// The goal of this test is to verify that the standard option can
// be configured to encapsulate multiple other options.
TEST_F(Dhcp4ParserTest, stdOptionDataEncapsulate) {

    // The configuration is two stage process in this test.
    // In the first stage we create definitions of suboptions
    // that we will add to the base option.
    // Let's create some dummy options: foo and foo2.
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-encapsulated-options-space\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-encapsulated-options-space\","
        "    \"data\": \"192.168.2.1\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 1,"
        "    \"type\": \"uint32\","
        "    \"space\": \"vendor-encapsulated-options-space\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 2,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"vendor-encapsulated-options-space\""
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    CfgMgr::instance().clear();

    // Once the definitions have been added we can configure the
    // standard option #17. This option comprises an enterprise
    // number and sub options. By convention (introduced in
    // std_option_defs.h) option named 'vendor-opts'
    // encapsulates the option space named 'vendor-opts-space'.
    // We add our dummy options to this option space and thus
    // they should be included as sub-options in the 'vendor-opts'
    // option.
    config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 3000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"vendor-encapsulated-options\","
        "    \"csv-format\": false"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-encapsulated-options-space\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-encapsulated-options-space\","
        "    \"code\": 2,"
        "    \"data\": \"192.168.2.1\","
        "    \"csv-format\": true"
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 1,"
        "    \"type\": \"uint32\","
        "    \"space\": \"vendor-encapsulated-options-space\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 2,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"vendor-encapsulated-options-space\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ]"
        "}";


    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // We should have one option available.
    OptionContainerPtr options =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->getAll(DHCP4_OPTION_SPACE);
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the option.
    OptionDescriptor desc = CfgMgr::instance().getStagingCfg()->
        getCfgOption()->get(DHCP4_OPTION_SPACE, DHO_VENDOR_ENCAPSULATED_OPTIONS);
    EXPECT_TRUE(desc.option_);
    EXPECT_EQ(DHO_VENDOR_ENCAPSULATED_OPTIONS, desc.option_->getType());

    // Option with the code 1 should be added as a sub-option.
    OptionPtr option_foo = desc.option_->getOption(1);
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(1, option_foo->getType());
    // This option comprises a single uint32_t value thus it is
    // represented by OptionInt<uint32_t> class. Let's get the
    // object of this type.
    boost::shared_ptr<OptionInt<uint32_t> > option_foo_uint32 =
        boost::dynamic_pointer_cast<OptionInt<uint32_t> >(option_foo);
    ASSERT_TRUE(option_foo_uint32);
    // Validate the value according to the configuration.
    EXPECT_EQ(1234, option_foo_uint32->getValue());

    // Option with the code 2 should be added as a sub-option.
    OptionPtr option_foo2 = desc.option_->getOption(2);
    ASSERT_TRUE(option_foo2);
    EXPECT_EQ(2, option_foo2->getType());
    // This option comprises the IPV4 address. Such option is
    // represented by OptionCustom object.
    OptionCustomPtr option_foo2_v4 =
        boost::dynamic_pointer_cast<OptionCustom>(option_foo2);
    ASSERT_TRUE(option_foo2_v4);
    // Get the IP address carried by this option and validate it.
    EXPECT_EQ("192.168.2.1", option_foo2_v4->readAddress().toText());

    // Option with the code 3 should not be added.
    EXPECT_FALSE(desc.option_->getOption(3));
}

// This test checks if vendor options can be specified in the config file
// (in hex format), and later retrieved
TEST_F(Dhcp4ParserTest, vendorOptionsHex) {

    // This configuration string is to configure two options
    // sharing the code 1 and belonging to the different vendor spaces.
    // (different vendor-id values).
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"option-one\","
        "    \"space\": \"vendor-4491\"," // VENDOR_ID_CABLE_LABS = 4491
        "    \"code\": 100," // just a random code
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": false"
        " },"
        " {"
        "    \"name\": \"option-two\","
        "    \"space\": \"vendor-1234\","
        "    \"code\": 100,"
        "    \"data\": \"1234\","
        "    \"csv-format\": false"
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1-192.0.2.10\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Try to get the option from the vendor space 4491
    OptionDescriptor desc1 = CfgMgr::instance().getStagingCfg()->
        getCfgOption()->get(VENDOR_ID_CABLE_LABS, 100);
    ASSERT_TRUE(desc1.option_);
    EXPECT_EQ(100, desc1.option_->getType());
    // Try to get the option from the vendor space 1234
    OptionDescriptor desc2 =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get(1234, 100);
    ASSERT_TRUE(desc2.option_);
    EXPECT_EQ(100, desc1.option_->getType());

    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    OptionDescriptor desc3 =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get(5678, 100);
    ASSERT_FALSE(desc3.option_);
}

// This test checks if vendor options can be specified in the config file,
// (in csv format), and later retrieved
TEST_F(Dhcp4ParserTest, vendorOptionsCsv) {

    // This configuration string is to configure two options
    // sharing the code 1 and belonging to the different vendor spaces.
    // (different vendor-id values).
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-4491\","
        "    \"code\": 100,"
        "    \"data\": \"this is a string vendor-opt\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 100,"
        "    \"type\": \"string\","
        "    \"space\": \"vendor-4491\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" "
        " } ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Try to get the option from the vendor space 4491
    OptionDescriptor desc1 = CfgMgr::instance().getStagingCfg()->
        getCfgOption()->get(VENDOR_ID_CABLE_LABS, 100);
    ASSERT_TRUE(desc1.option_);
    EXPECT_EQ(100, desc1.option_->getType());

    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    OptionDescriptor desc2 =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->get(5678, 100);
    ASSERT_FALSE(desc2.option_);
}


// Tests of the hooks libraries configuration.  All tests have the pre-
// condition (checked in the test fixture's SetUp() method) that no hooks
// libraries are loaded at the start of the tests.

// Helper function to return a configuration containing an arbitrary number
// of hooks libraries.
std::string
buildHooksLibrariesConfig(const std::vector<std::string>& libraries) {

    // Create the first part of the configuration string.
    string config =
        "{  \"interfaces-config\": {"
            "    \"interfaces\": [ \"*\" ]"
            "},"
            "\"hooks-libraries\": [";

    // Append the libraries (separated by commas if needed)
    for (unsigned int i = 0; i < libraries.size(); ++i) {
        if (i > 0) {
            config += string(", ");
        }
        config += (string("{ \"library\": \"") + libraries[i] + string("\" }"));
    }

    // Append the remainder of the configuration.
    config += string(
        "],"
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"dhcp-message\","
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": false"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"data\": \"1234\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 56,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ]"
        "}");

    return (config);
}

// Convenience function for creating hooks library configuration with one or
// two character string constants.
std::string
buildHooksLibrariesConfig(const char* library1 = NULL,
                          const char* library2 = NULL) {
    std::vector<std::string> libraries;
    if (library1 != NULL) {
        libraries.push_back(string(library1));
        if (library2 != NULL) {
            libraries.push_back(string(library2));
        }
    }
    return (buildHooksLibrariesConfig(libraries));
}


// The goal of this test is to verify the configuration of hooks libraries if
// none are specified.
TEST_F(Dhcp4ParserTest, NoHooksLibraries) {
    // Parse a configuration containing no names.
    string config = buildHooksLibrariesConfig();
    if (!executeConfiguration(config,
                              "set configuration with no hooks libraries")) {
        FAIL() << "Unable to execute configuration";

    } else {
        // No libraries should be loaded at the end of the test.
        std::vector<std::string> libraries = HooksManager::getLibraryNames();
        EXPECT_TRUE(libraries.empty());
    }
}

// Verify parsing fails with one library that will fail validation.
TEST_F(Dhcp4ParserTest, InvalidLibrary) {
    // Parse a configuration containing a failing library.
    string config = buildHooksLibrariesConfig(NOT_PRESENT_LIBRARY);

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // The status object must not be NULL
    ASSERT_TRUE(status);

    // Returned value should not be 0
    comment_ = parseAnswer(rcode_, status);
    EXPECT_NE(0, rcode_);
}

// Verify the configuration of hooks libraries with two being specified.
TEST_F(Dhcp4ParserTest, LibrariesSpecified) {
    // Marker files should not be present.
    EXPECT_FALSE(checkMarkerFileExists(LOAD_MARKER_FILE));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Set up the configuration with two libraries and load them.
    string config = buildHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                              CALLOUT_LIBRARY_2);
    ASSERT_TRUE(executeConfiguration(config,
                                     "load two valid libraries"));

    // Expect two libraries to be loaded in the correct order (load marker file
    // is present, no unload marker file).
    std::vector<std::string> libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(2, libraries.size());
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "12"));
    EXPECT_FALSE(checkMarkerFileExists(UNLOAD_MARKER_FILE));

    // Commit the changes so as we get the fresh configuration for the
    // second part of this test.
    CfgMgr::instance().commit();

    // Unload the libraries.  The load file should not have changed, but
    // the unload one should indicate the unload() functions have been run.
    config = buildHooksLibrariesConfig();
    ASSERT_TRUE(executeConfiguration(config, "unloading libraries"));
    EXPECT_TRUE(checkMarkerFile(LOAD_MARKER_FILE, "12"));
    EXPECT_TRUE(checkMarkerFile(UNLOAD_MARKER_FILE, "21"));

    // Expect the hooks system to say that none are loaded.
    libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(libraries.empty());

}

// This test verifies that it is possible to select subset of interfaces
// on which server should listen.
TEST_F(Dhcp4ParserTest, selectedInterfaces) {
    IfaceMgrTestConfig test_config(true);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"eth0\", \"eth1\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;

    // Make sure the config manager is clean and there is no hanging
    // interface configuration.
    EXPECT_FALSE(test_config.socketOpen("eth0", AF_INET));
    EXPECT_FALSE(test_config.socketOpen("eth1", AF_INET));

    // Apply configuration.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET, 10000);

    // eth0 and eth1 were explicitly selected. eth2 was not.
    EXPECT_TRUE(test_config.socketOpen("eth0", AF_INET));
    EXPECT_TRUE(test_config.socketOpen("eth1", AF_INET));
}

// This test verifies that it is possible to configure the server in such a way
// that it listens on all interfaces.
TEST_F(Dhcp4ParserTest, allInterfaces) {
    IfaceMgrTestConfig test_config(true);

    ConstElementPtr x;
    // This configuration specifies two interfaces on which server should listen
    // but it also includes asterisk. The asterisk switches server into the
    // mode when it listens on all interfaces regardless of what interface names
    // were specified in the "interfaces" parameter.
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"eth0\", \"*\", \"eth1\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;

    // Make sure there is no old configuration.
    ASSERT_FALSE(test_config.socketOpen("eth0", AF_INET));
    ASSERT_FALSE(test_config.socketOpen("eth1", AF_INET));

    // Apply configuration.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET, 10000);

    // All interfaces should be now active.
    ASSERT_TRUE(test_config.socketOpen("eth0", AF_INET));
    ASSERT_TRUE(test_config.socketOpen("eth1", AF_INET));
}

// This test verifies that it is possible to select subset of interfaces
// and addresses.
TEST_F(Dhcp4ParserTest, selectedInterfacesAndAddresses) {
    IfaceMgrTestConfig test_config(true);

    ConstElementPtr x;
    string config = "{ \"interfaces-config\": {"
        "    \"interfaces\": [ \"eth0/10.0.0.1\", \"eth1/192.0.2.3\" ]"
        "},"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    ConstElementPtr status;

    // Make sure the config manager is clean and there is no hanging
    // interface configuration.
    ASSERT_FALSE(test_config.socketOpen("eth0", "10.0.0.1"));
    ASSERT_FALSE(test_config.socketOpen("eth1", "192.0.2.3"));
    ASSERT_FALSE(test_config.socketOpen("eth1", "192.0.2.5"));

    // Apply configuration.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET, 10000);

    // An address on eth0 was selected
    EXPECT_TRUE(test_config.socketOpen("eth0", "10.0.0.1"));
    // The 192.0.2.3 address on eth1 was selected.
    EXPECT_TRUE(test_config.socketOpen("eth1", "192.0.2.3"));
    // The 192.0.2.5 was not selected, thus the socket should not
    // be bound to this address.
    EXPECT_FALSE(test_config.socketOpen("eth1", "192.0.2.5"));
}


// This test checks the ability of the server to parse a configuration
// containing a full, valid dhcp-ddns (D2ClientConfig) entry.
TEST_F(Dhcp4ParserTest, d2ClientConfig) {
    ConstElementPtr status;

    // Verify that the D2 configuration can be fetched and is set to disabled.
    D2ClientConfigPtr d2_client_config = CfgMgr::instance().getD2ClientConfig();
    EXPECT_FALSE(d2_client_config->getEnableUpdates());

    // Verify that the convenience method agrees.
    ASSERT_FALSE(CfgMgr::instance().ddnsEnabled());

    string config_str = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.168.2.1\", "
        "     \"server-port\" : 777, "
        "     \"sender-ip\" : \"192.168.2.2\", "
        "     \"sender-port\" : 778, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : \"when-present\", "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\", "
        "     \"hostname-char-set\" : \"[^A-Za-z0-9_-]\", "
        "     \"hostname-char-replacement\" : \"x\" }, "
        "\"valid-lifetime\": 4000 }";

    // Convert the JSON string to configuration elements.
    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCP4(config_str, true));
    extractConfig(config_str);

    // Pass the configuration in for parsing.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, config));

    // check if returned status is OK
    checkResult(status, 0);

    // Verify that DHCP-DDNS updating is enabled.
    EXPECT_TRUE(CfgMgr::instance().ddnsEnabled());

    // Verify that the D2 configuration can be retrieved.
    d2_client_config = CfgMgr::instance().getD2ClientConfig();
    ASSERT_TRUE(d2_client_config);

    // Verify that the configuration values are correct.
    EXPECT_TRUE(d2_client_config->getEnableUpdates());
    EXPECT_EQ("192.168.2.1", d2_client_config->getServerIp().toText());
    EXPECT_EQ(777, d2_client_config->getServerPort());
    EXPECT_EQ("192.168.2.2", d2_client_config->getSenderIp().toText());
    EXPECT_EQ(778, d2_client_config->getSenderPort());
    EXPECT_EQ(2048, d2_client_config->getMaxQueueSize());
    EXPECT_EQ(dhcp_ddns::NCR_UDP, d2_client_config->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::FMT_JSON, d2_client_config->getNcrFormat());
    EXPECT_TRUE(d2_client_config->getOverrideNoUpdate());
    EXPECT_TRUE(d2_client_config->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_WHEN_PRESENT, d2_client_config->getReplaceClientNameMode());
    EXPECT_EQ("test.prefix", d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("test.suffix.", d2_client_config->getQualifyingSuffix());
}

// This test checks the ability of the server to handle a configuration
// containing an invalid dhcp-ddns (D2ClientConfig) entry.
TEST_F(Dhcp4ParserTest, invalidD2ClientConfig) {
    ConstElementPtr status;

    // Configuration string with an invalid D2 client config,
    // "server-ip" is invalid.
    string config_str = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"bogus-value\", "
        "     \"server-port\" : 5301, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : \"when-present\", "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" },"
        "\"valid-lifetime\": 4000 }";

    // Convert the JSON string to configuration elements.
    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCP4(config_str));

    // Configuration should not throw, but should fail.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, config));

    // check if returned status is failed.
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    // Verify that the D2 configuration can be fetched and is set to disabled.
    D2ClientConfigPtr d2_client_config = CfgMgr::instance().getD2ClientConfig();
    EXPECT_FALSE(d2_client_config->getEnableUpdates());

    // Verify that the convenience method agrees.
    ASSERT_FALSE(CfgMgr::instance().ddnsEnabled());
}

// This test checks if it is possible to specify relay information
TEST_F(Dhcp4ParserTest, subnetRelayInfo) {

    ConstElementPtr status;

    // A config with relay information.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"valid-lifetime\": 4,"
        "    \"relay\": { "
        "        \"ip-address\": \"192.0.2.123\""
        "    },"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    EXPECT_TRUE(subnet->hasRelays());
    EXPECT_TRUE(subnet->hasRelayAddress(IOAddress("192.0.2.123")));
}

// This test checks if it is possible to specify a list of relays
TEST_F(Dhcp4ParserTest, subnetRelayInfoList) {

    ConstElementPtr status;

    // A config with relay information.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"valid-lifetime\": 4,"
        "    \"relay\": { "
        "        \"ip-addresses\": [ \"192.0.3.123\", \"192.0.3.124\" ]"
        "    },"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    SubnetSelector selector;
    selector.giaddr_ = IOAddress("192.0.2.200");

    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(selector);
    ASSERT_TRUE(subnet);

    EXPECT_TRUE(subnet->hasRelays());
    EXPECT_TRUE(subnet->hasRelayAddress(IOAddress("192.0.3.123")));
    EXPECT_TRUE(subnet->hasRelayAddress(IOAddress("192.0.3.124")));
}


// Goal of this test is to verify that multiple subnets can be configured
// with defined client classes.
TEST_F(Dhcp4ParserTest, classifySubnets) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"client-class\": \"alpha\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"client-class\": \"beta\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"client-class\": \"gamma\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.101 - 192.0.5.150\" } ],"
        "    \"subnet\": \"192.0.5.0/24\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    const Subnet4Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(4, subnets->size()); // We expect 4 subnets

    // Let's check if client belonging to alpha class is supported in subnet[0]
    // and not supported in any other subnet (except subnet[3], which allows
    // everyone).
    ClientClasses classes;
    classes.insert("alpha");
    EXPECT_TRUE (subnets->at(0)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(1)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(2)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(3)->clientSupported(classes));

    // Let's check if client belonging to beta class is supported in subnet[1]
    // and not supported in any other subnet  (except subnet[3], which allows
    // everyone).
    classes.clear();
    classes.insert("beta");
    EXPECT_FALSE(subnets->at(0)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(1)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(2)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(3)->clientSupported(classes));

    // Let's check if client belonging to gamma class is supported in subnet[2]
    // and not supported in any other subnet  (except subnet[3], which allows
    // everyone).
    classes.clear();
    classes.insert("gamma");
    EXPECT_FALSE(subnets->at(0)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(1)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(2)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(3)->clientSupported(classes));

    // Let's check if client belonging to some other class (not mentioned in
    // the config) is supported only in subnet[3], which allows everyone.
    classes.clear();
    classes.insert("delta");
    EXPECT_FALSE(subnets->at(0)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(1)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(2)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(3)->clientSupported(classes));

    // Finally, let's check class-less client. He should be allowed only in
    // the last subnet, which does not have any class restrictions.
    classes.clear();
    EXPECT_FALSE(subnets->at(0)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(1)->clientSupported(classes));
    EXPECT_FALSE(subnets->at(2)->clientSupported(classes));
    EXPECT_TRUE (subnets->at(3)->clientSupported(classes));
}

// Goal of this test is to verify that multiple pools can be configured
// with defined client classes.
TEST_F(Dhcp4ParserTest, classifyPools) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { "
        "        \"pool\": \"192.0.2.1 - 192.0.2.100\", "
        "        \"client-class\": \"alpha\" "
        "     },"
        "     {"
        "        \"pool\": \"192.0.3.101 - 192.0.3.150\", "
        "        \"client-class\": \"beta\" "
        "     },"
        "     {"
        "        \"pool\": \"192.0.4.101 - 192.0.4.150\", "
        "        \"client-class\": \"gamma\" "
        "     },"
        "     {"
        "        \"pool\": \"192.0.5.101 - 192.0.5.150\" "
        "     } ],"
        "    \"subnet\": \"192.0.0.0/16\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    const Subnet4Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(1, subnets->size());
    const PoolCollection& pools = subnets->at(0)->getPools(Lease::TYPE_V4);
    ASSERT_EQ(4, pools.size()); // We expect 4 pools

    // Let's check if client belonging to alpha class is supported in pool[0]
    // and not supported in any other pool (except pool[3], which allows
    // everyone).
    ClientClasses classes;
    classes.insert("alpha");
    EXPECT_TRUE(pools.at(0)->clientSupported(classes));
    EXPECT_FALSE(pools.at(1)->clientSupported(classes));
    EXPECT_FALSE(pools.at(2)->clientSupported(classes));
    EXPECT_TRUE(pools.at(3)->clientSupported(classes));

    // Let's check if client belonging to beta class is supported in pool[1]
    // and not supported in any other pool  (except pools[3], which allows
    // everyone).
    classes.clear();
    classes.insert("beta");
    EXPECT_FALSE(pools.at(0)->clientSupported(classes));
    EXPECT_TRUE(pools.at(1)->clientSupported(classes));
    EXPECT_FALSE(pools.at(2)->clientSupported(classes));
    EXPECT_TRUE(pools.at(3)->clientSupported(classes));

    // Let's check if client belonging to gamma class is supported in pool[2]
    // and not supported in any other pool  (except pool[3], which allows
    // everyone).
    classes.clear();
    classes.insert("gamma");
    EXPECT_FALSE(pools.at(0)->clientSupported(classes));
    EXPECT_FALSE(pools.at(1)->clientSupported(classes));
    EXPECT_TRUE(pools.at(2)->clientSupported(classes));
    EXPECT_TRUE(pools.at(3)->clientSupported(classes));

    // Let's check if client belonging to some other class (not mentioned in
    // the config) is supported only in pool[3], which allows everyone.
    classes.clear();
    classes.insert("delta");
    EXPECT_FALSE(pools.at(0)->clientSupported(classes));
    EXPECT_FALSE(pools.at(1)->clientSupported(classes));
    EXPECT_FALSE(pools.at(2)->clientSupported(classes));
    EXPECT_TRUE(pools.at(3)->clientSupported(classes));

    // Finally, let's check class-less client. He should be allowed only in
    // the last pool, which does not have any class restrictions.
    classes.clear();
    EXPECT_FALSE(pools.at(0)->clientSupported(classes));
    EXPECT_FALSE(pools.at(1)->clientSupported(classes));
    EXPECT_FALSE(pools.at(2)->clientSupported(classes));
    EXPECT_TRUE(pools.at(3)->clientSupported(classes));
}

// This test verifies that the host reservations can be specified for
// respective IPv4 subnets.
TEST_F(Dhcp4ParserTest, reservations) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        " { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"id\": 123,"
        "    \"reservations\": ["
        "    ]"
        " },"
        " {"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "        \"ip-address\": \"192.0.3.112\","
        "        \"hostname\": \"\","
        "        \"option-data\": ["
        "        {"
        "          \"name\": \"name-servers\","
        "          \"data\": \"192.0.3.15\""
        "        },"
        "        {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"32\""
        "        }"
        "        ]"
        "      },"
        "      {"
        "        \"hw-address\": \"01:02:03:04:05:06\","
        "        \"ip-address\": \"192.0.3.120\","
        "        \"hostname\": \"\","
        "        \"option-data\": ["
        "        {"
        "          \"name\": \"name-servers\","
        "          \"data\": \"192.0.3.95\""
        "        },"
        "        {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"11\""
        "        }"
        "        ]"
        "      }"
        "    ],"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 234"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\","
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"0A:09:08:07:06:05:04:03:02:01\","
        "        \"ip-address\": \"192.0.4.101\","
        "        \"hostname\": \"\","
        "        \"option-data\": ["
        "        {"
        "          \"name\": \"name-servers\","
        "          \"data\": \"192.0.4.11\""
        "        },"
        "        {"
        "          \"name\": \"default-ip-ttl\","
        "          \"data\": \"95\""
        "        }"
        "        ]"
        "      },"
        "      {"
        "        \"circuit-id\": \"060504030201\","
        "        \"ip-address\": \"192.0.4.102\","
        "        \"hostname\": \"\""
        "      },"
        "      {"
        "        \"client-id\": \"05:01:02:03:04:05:06\","
        "        \"ip-address\": \"192.0.4.103\","
        "        \"hostname\": \"\""
        "      }"
        "    ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    // Make sure all subnets have been successfully configured. There is no
    // need to sanity check the subnet properties because it should have
    // been already tested by other tests.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size());

    // Hosts configuration must be available.
    CfgHostsPtr hosts_cfg = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(hosts_cfg);

    // Let's create an object holding hardware address of the host having
    // a reservation in the subnet having id of 234. For simplicity the
    // address is a collection of numbers from 1 to 6.
    std::vector<uint8_t> hwaddr;
    for (unsigned int i = 1; i < 7; ++i) {
        hwaddr.push_back(static_cast<uint8_t>(i));
    }
    // Retrieve the reservation and sanity check the address reserved.
    ConstHostPtr host = hosts_cfg->get4(234, Host::IDENT_HWADDR,
                                        &hwaddr[0], hwaddr.size());
    ASSERT_TRUE(host);
    EXPECT_EQ("192.0.3.120", host->getIPv4Reservation().toText());
    // This reservation should be solely assigned to the subnet 234,
    // and not to other two.
    EXPECT_FALSE(hosts_cfg->get4(123, Host::IDENT_HWADDR,
                                 &hwaddr[0], hwaddr.size()));
    EXPECT_FALSE(hosts_cfg->get4(542, Host::IDENT_HWADDR,
                                 &hwaddr[0], hwaddr.size()));
    // Check that options are assigned correctly.
    Option4AddrLstPtr opt_dns =
        retrieveOption<Option4AddrLstPtr>(*host, DHO_NAME_SERVERS);
    ASSERT_TRUE(opt_dns);
    Option4AddrLst::AddressContainer dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(1, dns_addrs.size());
    EXPECT_EQ("192.0.3.95", dns_addrs[0].toText());
    OptionUint8Ptr opt_ttl =
        retrieveOption<OptionUint8Ptr>(*host, DHO_DEFAULT_IP_TTL);
    ASSERT_TRUE(opt_ttl);
    EXPECT_EQ(11, static_cast<int>(opt_ttl->getValue()));

    // Do the same test for the DUID based reservation.
    std::vector<uint8_t> duid;
    for (unsigned int i = 1; i < 0xb; ++i) {
        duid.push_back(static_cast<uint8_t>(i));
    }
    host = hosts_cfg->get4(234, Host::IDENT_DUID, &duid[0], duid.size());
    ASSERT_TRUE(host);
    EXPECT_EQ("192.0.3.112", host->getIPv4Reservation().toText());
    EXPECT_FALSE(hosts_cfg->get4(123, Host::IDENT_DUID, &duid[0], duid.size()));
    EXPECT_FALSE(hosts_cfg->get4(542, Host::IDENT_DUID, &duid[0], duid.size()));
    // Check that options are assigned correctly.
    opt_dns = retrieveOption<Option4AddrLstPtr>(*host, DHO_NAME_SERVERS);
    ASSERT_TRUE(opt_dns);
    dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(1, dns_addrs.size());
    EXPECT_EQ("192.0.3.15", dns_addrs[0].toText());
    opt_ttl = retrieveOption<OptionUint8Ptr>(*host, DHO_DEFAULT_IP_TTL);
    ASSERT_TRUE(opt_ttl);
    EXPECT_EQ(32, static_cast<int>(opt_ttl->getValue()));

    // The circuit-id used for one of the reservations in the subnet 542
    // consists of numbers from 6 to 1. So, let's just reverse the order
    // of the address from the previous test.
    std::vector<uint8_t> circuit_id(hwaddr.rbegin(), hwaddr.rend());
    host = hosts_cfg->get4(542, Host::IDENT_CIRCUIT_ID, &circuit_id[0],
                           circuit_id.size());
    EXPECT_TRUE(host);
    EXPECT_EQ("192.0.4.102", host->getIPv4Reservation().toText());
    // This reservation must not belong to other subnets.
    EXPECT_FALSE(hosts_cfg->get4(123, Host::IDENT_CIRCUIT_ID,
                                 &circuit_id[0], circuit_id.size()));
    EXPECT_FALSE(hosts_cfg->get4(234, Host::IDENT_CIRCUIT_ID,
                                 &circuit_id[0], circuit_id.size()));


    // Repeat the test for the DUID based reservation in this subnet.
    std::vector<uint8_t> duid_r(duid.rbegin(), duid.rend());
    host = hosts_cfg->get4(542, Host::IDENT_DUID, &duid_r[0], duid_r.size());
    ASSERT_TRUE(host);
    EXPECT_EQ("192.0.4.101", host->getIPv4Reservation().toText());
    EXPECT_FALSE(hosts_cfg->get4(123, Host::IDENT_DUID,
                                 &duid_r[0], duid_r.size()));
    EXPECT_FALSE(hosts_cfg->get4(234, Host::IDENT_DUID,
                                 &duid_r[0], duid_r.size()));
    // Check that options are assigned correctly.
    opt_dns = retrieveOption<Option4AddrLstPtr>(*host, DHO_NAME_SERVERS);
    ASSERT_TRUE(opt_dns);
    dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(1, dns_addrs.size());
    EXPECT_EQ("192.0.4.11", dns_addrs[0].toText());
    opt_ttl = retrieveOption<OptionUint8Ptr>(*host, DHO_DEFAULT_IP_TTL);
    ASSERT_TRUE(opt_ttl);
    EXPECT_EQ(95, static_cast<int>(opt_ttl->getValue()));

    // Check that we can find reservation using client identifier.
    ClientIdPtr client_id = ClientId::fromText("05:01:02:03:04:05:06");
    host = hosts_cfg->get4(542, Host::IDENT_CLIENT_ID, &client_id->getDuid()[0],
                           client_id->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ("192.0.4.103", host->getIPv4Reservation().toText());

    // But this reservation should not be returned for other subnet.
    host = hosts_cfg->get4(234, Host::IDENT_CLIENT_ID, &client_id->getDuid()[0],
                           client_id->getDuid().size());
    EXPECT_FALSE(host);
}

// This test checks that it is possible to configure option data for a
// host using a user defined option format.
TEST_F(Dhcp4ParserTest, reservationWithOptionDefinition) {
    ConstElementPtr x;
    // The following configuration contains host declaration in which
    // a non-standard option is used. This option has option definition
    // specified in the configuration.
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-def\": [ {"
        "  \"name\": \"foo\","
        "  \"code\": 100,"
        "  \"type\": \"uint32\","
        "  \"space\": \"isc\""
        "} ],"
        "\"subnet4\": [ "
        " {"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "        \"ip-address\": \"192.0.3.112\","
        "        \"option-data\": ["
        "        {"
        "          \"name\": \"foo\","
        "          \"data\": \"123\","
        "          \"space\": \"isc\""
        "        }"
        "        ]"
        "      }"
        "    ],"
        "    \"pools\": [ { \"pool\": \"192.0.3.101 - 192.0.3.150\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"id\": 234"
        " } ],"
        "\"valid-lifetime\": 4000"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config, true));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    // Hosts configuration must be available.
    CfgHostsPtr hosts_cfg = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(hosts_cfg);

    // Let's create an object holding DUID of the host. For simplicity the
    // address is a collection of numbers from 1 to A.
    std::vector<uint8_t> duid;
    for (unsigned int i = 1; i < 0xB; ++i) {
        duid.push_back(static_cast<uint8_t>(i));
    }
    // Retrieve the reservation and sanity check the address reserved.
    ConstHostPtr host =
        hosts_cfg->get4(234, Host::IDENT_DUID, &duid[0], duid.size());
    ASSERT_TRUE(host);
    EXPECT_EQ("192.0.3.112", host->getIPv4Reservation().toText());

    // Check if the option has been parsed.
    OptionUint32Ptr opt_foo = retrieveOption<OptionUint32Ptr>(*host, "isc",
                                                              100);
    ASSERT_TRUE(opt_foo);
    EXPECT_EQ(100, opt_foo->getType());
    EXPECT_EQ(123, opt_foo->getValue());
}

// This test verifies that the bogus host reservation would trigger a
// server configuration error.
TEST_F(Dhcp4ParserTest, reservationBogus) {
    // Case 1: misspelled hw-address parameter.
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        " { "
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\","
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"hw-addre\": \"06:05:04:03:02:01\","
        "        \"ip-address\": \"192.0.4.102\","
        "        \"hostname\": \"\""
        "      }"
        "    ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseJSON(config));

    CfgMgr::instance().clear();

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 1);

    EXPECT_THROW(parseDHCP4(config), Dhcp4ParseError);

    // Case 2: DUID and HW Address both specified.
    config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        " { "
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\","
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"01:02:03:04:05:06\","
        "        \"hw-address\": \"06:05:04:03:02:01\","
        "        \"ip-address\": \"192.0.4.102\","
        "        \"hostname\": \"\""
        "      }"
        "    ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(json = parseDHCP4(config));

    // Remove existing configuration, if any.
    CfgMgr::instance().clear();

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 1);

    // Case 3: Neither ip address nor hostname specified.
    config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        " { "
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\","
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"hw-address\": \"06:05:04:03:02:01\""
        "      }"
        "    ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(json = parseDHCP4(config));

    // Remove existing configuration, if any.
    CfgMgr::instance().clear();

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 1);

    // Case 4: Broken specification of option data.
    config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ "
        " { "
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],"
        "    \"subnet\": \"192.0.4.0/24\","
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"hw-address\": \"06:05:04:03:02:01\","
        "        \"option-data\": ["
        "        {"
        "          \"name\": \"name-servers\","
        "          \"data\": \"bogus-ip-address\""
        "        }"
        "        ]"
        "      }"
        "    ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ASSERT_NO_THROW(json = parseDHCP4(config));

    // Remove existing configuration, if any.
    CfgMgr::instance().clear();

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 1);
}

/// The goal of this test is to verify that Host Reservation modes can be
/// specified on a per-subnet basis.
TEST_F(Dhcp4ParserTest, hostReservationPerSubnet) {

    /// - Configuration:
    ///   - only addresses (no prefixes)
    ///   - 4 subnets with:
    ///       - 192.0.2.0/24 (all reservations enabled)
    ///       - 192.0.3.0/24 (out-of-pool reservations)
    ///       - 192.0.4.0/24 (reservations disabled)
    ///       - 192.0.5.0/24 (reservations not specified)
    const char* hr_config =
        "{ "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"reservation-mode\": \"all\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.0/24\" } ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"reservation-mode\": \"out-of-pool\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.4.0/24\" } ],"
        "    \"subnet\": \"192.0.4.0/24\", "
        "    \"reservation-mode\": \"disabled\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.5.0/24\" } ],"
        "    \"subnet\": \"192.0.5.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(hr_config));
    extractConfig(hr_config);
    ConstElementPtr result;
    EXPECT_NO_THROW(result = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(result, 0);

    // Let's get all subnets and check that there are 4 of them.
    ConstCfgSubnets4Ptr subnets = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    ASSERT_TRUE(subnets);
    const Subnet4Collection* subnet_col = subnets->getAll();
    ASSERT_EQ(4, subnet_col->size()); // We expect 4 subnets

    // Let's check if the parsed subnets have correct HR modes.

    // Subnet 1
    Subnet4Ptr subnet;
    subnet = subnets->selectSubnet(IOAddress("192.0.2.1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Network::HR_ALL, subnet->getHostReservationMode());

    // Subnet 2
    subnet = subnets->selectSubnet(IOAddress("192.0.3.1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Network::HR_OUT_OF_POOL, subnet->getHostReservationMode());

    // Subnet 3
    subnet = subnets->selectSubnet(IOAddress("192.0.4.1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Network::HR_DISABLED, subnet->getHostReservationMode());

    // Subnet 4
    subnet = subnets->selectSubnet(IOAddress("192.0.5.1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Network::HR_ALL, subnet->getHostReservationMode());
}

/// The goal of this test is to verify that Host Reservation modes can be
/// specified globally.
TEST_F(Dhcp4ParserTest, hostReservationGlobal) {

    /// - Configuration:
    ///   - only addresses (no prefixes)
    ///   - 2 subnets with :
    ///       - 192.0.2.0/24 (all reservations enabled)
    ///       - 192.0.3.0/24 (reservations not specified)
    const char* hr_config =
        "{ "
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"reservation-mode\": \"out-of-pool\", "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.0/24\" } ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"reservation-mode\": \"all\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"192.0.3.0/24\" } ],"
        "    \"subnet\": \"192.0.3.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(hr_config));
    extractConfig(hr_config);
    ConstElementPtr result;
    EXPECT_NO_THROW(result = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(result, 0);

    // Let's get all subnets and check that there are 4 of them.
    ConstCfgSubnets4Ptr subnets = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    ASSERT_TRUE(subnets);
    const Subnet4Collection* subnet_col = subnets->getAll();
    ASSERT_EQ(2, subnet_col->size()); // We expect 2 subnets

    // Let's check if the parsed subnets have correct HR modes.

    // Subnet 1
    Subnet4Ptr subnet;
    subnet = subnets->selectSubnet(IOAddress("192.0.2.1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Network::HR_ALL, subnet->getHostReservationMode());

    // Subnet 2
    subnet = subnets->selectSubnet(IOAddress("192.0.3.1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Network::HR_OUT_OF_POOL, subnet->getHostReservationMode());
}

/// Check that the decline-probation-period has a default value when not
/// specified.
TEST_F(Dhcp4ParserTest, declineTimerDefault) {
    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + "," +
        "\"subnet4\": [ ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);

    // The value of decline-probation-period must be equal to the
    // default value (86400). The default value is defined in GLOBAL6_DEFAULTS in
    // simple_parser6.cc.
    EXPECT_EQ(86400, CfgMgr::instance().getStagingCfg()->getDeclinePeriod());
}

/// Check that the dhcp4o6-port default value has a default value if not
/// specified explicitly.
TEST_F(Dhcp4ParserTest, dhcp4o6portDefault) {

    string config_txt = "{ " + genIfaceConfig() + ","
        "\"subnet4\": [  ] "
        "}";
    ConstElementPtr config;
    ASSERT_NO_THROW(config = parseDHCP4(config_txt));
    extractConfig(config_txt);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, config));

    // returned value should be 0 (success)
    checkResult(status, 0);

    // The value of decline-probation-period must be equal to the
    // default value (0). The default value is defined in GLOBAL4_DEFAULTS in
    // simple_parser4.cc.
    EXPECT_EQ(0, CfgMgr::instance().getStagingCfg()->getDhcp4o6Port());
}


/// Check that the decline-probation-period value can be set properly.
TEST_F(Dhcp4ParserTest, declineTimer) {
    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + "," +
        "\"decline-probation-period\": 12345,"
        "\"subnet4\": [ ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);

    // The value of decline-probation-period must be equal to the
    // value specified.
    EXPECT_EQ(12345,
              CfgMgr::instance().getStagingCfg()->getDeclinePeriod());
}

/// Check that an incorrect decline-probation-period value will be caught.
TEST_F(Dhcp4ParserTest, declineTimerError) {
    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + "," +
        "\"decline-probation-period\": \"soon\","
        "\"subnet4\": [ ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseJSON(config));

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 1 (error)
    checkResult(status, 1);

    // Check that the error contains error position.
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    // Check that the Dhcp4 parser catches the type error
    EXPECT_THROW(parseDHCP4(config), Dhcp4ParseError);
}

// Check that configuration for the expired leases processing may be
// specified.
TEST_F(Dhcp4ParserTest, expiredLeasesProcessing) {
    // Create basic configuration with the expiration specific parameters.
    string config = "{ " + genIfaceConfig() + "," +
        "\"expired-leases-processing\": "
        "{"
        "    \"reclaim-timer-wait-time\": 20,"
        "    \"flush-reclaimed-timer-wait-time\": 35,"
        "    \"hold-reclaimed-time\": 1800,"
        "    \"max-reclaim-leases\": 50,"
        "    \"max-reclaim-time\": 100,"
        "    \"unwarned-reclaim-cycles\": 10"
        "},"
        "\"subnet4\": [ ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // Returned value should be 0 (success)
    checkResult(status, 0);

    // The value of decline-probation-period must be equal to the
    // value specified.
    CfgExpirationPtr cfg = CfgMgr::instance().getStagingCfg()->getCfgExpiration();
    ASSERT_TRUE(cfg);

    // Verify that parameters are correct.
    EXPECT_EQ(20, cfg->getReclaimTimerWaitTime());
    EXPECT_EQ(35, cfg->getFlushReclaimedTimerWaitTime());
    EXPECT_EQ(1800, cfg->getHoldReclaimedTime());
    EXPECT_EQ(50, cfg->getMaxReclaimLeases());
    EXPECT_EQ(100, cfg->getMaxReclaimTime());
    EXPECT_EQ(10, cfg->getUnwarnedReclaimCycles());
}

// Check that invalid configuration for the expired leases processing is
// causing an error.
TEST_F(Dhcp4ParserTest, expiredLeasesProcessingError) {
    // Create basic configuration with the expiration specific parameters.
    // One of the parameters holds invalid value.
    string config = "{ " + genIfaceConfig() + "," +
        "\"expired-leases-processing\": "
        "{"
        "    \"reclaim-timer-wait-time\": -5,"
        "    \"flush-reclaimed-timer-wait-time\": 35,"
        "    \"hold-reclaimed-time\": 1800,"
        "    \"max-reclaim-leases\": 50,"
        "    \"max-reclaim-time\": 100,"
        "    \"unwarned-reclaim-cycles\": 10"
        "},"
        "\"subnet4\": [ ]"
        "}";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // Returned value should be 0 (error)
    checkResult(status, 1);

    // Check that the error contains error position.
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}


// Checks if the DHCPv4 is able to parse the configuration without 4o6 parameters
// and does not set 4o6 fields at all.
TEST_F(Dhcp4ParserTest, 4o6default) {

    ConstElementPtr status;

    // Just a plain v4 config (no 4o6 parameters)
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    Cfg4o6& dhcp4o6 = subnet->get4o6();
    EXPECT_FALSE(dhcp4o6.enabled());
}

// Checks if the DHCPv4 is able to parse the configuration with 4o6 subnet
// defined.
TEST_F(Dhcp4ParserTest, 4o6subnet) {

    ConstElementPtr status;

    // Just a plain v4 config (no 4o6 parameters)
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-subnet\": \"2001:db8::123/45\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    Cfg4o6& dhcp4o6 = subnet->get4o6();
    EXPECT_TRUE(dhcp4o6.enabled());
    EXPECT_EQ(IOAddress("2001:db8::123"), dhcp4o6.getSubnet4o6().get().first);
    EXPECT_EQ(45, dhcp4o6.getSubnet4o6().get().second);
}

// Checks if the DHCPv4 is able to parse the configuration with 4o6 subnet
// defined.
TEST_F(Dhcp4ParserTest, 4o6subnetBogus) {

    ConstElementPtr status;

    // Just a plain v4 config (no 4o6 parameters)
    string config[] = {
        // Bogus configuration 1: missing / in subnet
        "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-subnet\": \"2001:db8::123\" } ],"
        "\"valid-lifetime\": 4000 }",

        // Bogus configuration 2: incorrect address
                "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-subnet\": \"2001:db8:bogus/45\" } ],"
        "\"valid-lifetime\": 4000 }",

        // Bogus configuration 3: incorrect prefix length
        "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-subnet\": \"2001:db8::123/200\" } ],"
        "\"valid-lifetime\": 4000 }"
    };

    ConstElementPtr json1;
    ASSERT_NO_THROW(json1 = parseDHCP4(config[0]));
    ConstElementPtr json2;
    ASSERT_NO_THROW(json2 = parseDHCP4(config[0]));
    ConstElementPtr json3;
    ASSERT_NO_THROW(json3 = parseDHCP4(config[0]));

    // Check that the first config is rejected.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json1));
    checkResult(status, 1);

    // Check that the second config is rejected.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json2));
    checkResult(status, 1);

    // Check that the third config is rejected.
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json3));
    checkResult(status, 1);
}


// Checks if the DHCPv4 is able to parse the configuration with 4o6 network
// interface defined.
TEST_F(Dhcp4ParserTest, 4o6iface) {

    ConstElementPtr status;

    // Just a plain v4 config (no 4o6 parameters)
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-interface\": \"ethX\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    Cfg4o6& dhcp4o6 = subnet->get4o6();
    EXPECT_TRUE(dhcp4o6.enabled());
    EXPECT_EQ("ethX", dhcp4o6.getIface4o6().get());
}

// Checks if the DHCPv4 is able to parse the configuration with both 4o6 network
// interface and v6 subnet defined.
TEST_F(Dhcp4ParserTest, 4o6subnetIface) {

    ConstElementPtr status;

    // Just a plain v4 config (no 4o6 parameters)
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-subnet\": \"2001:db8::543/21\","
        "    \"4o6-interface\": \"ethX\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected subnet configured...
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    // ... and that subnet has 4o6 network interface specified.
    Cfg4o6& dhcp4o6 = subnet->get4o6();
    EXPECT_TRUE(dhcp4o6.enabled());
    EXPECT_EQ(IOAddress("2001:db8::543"), dhcp4o6.getSubnet4o6().get().first);
    EXPECT_EQ(21, dhcp4o6.getSubnet4o6().get().second);
    EXPECT_EQ("ethX", dhcp4o6.getIface4o6().get());
}

// Checks if the DHCPv4 is able to parse the configuration with 4o6 network
// interface-id.
TEST_F(Dhcp4ParserTest, 4o6subnetInterfaceId) {

    ConstElementPtr status;

    // Just a plain v4 config (no 4o6 parameters)
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],"
        "    \"subnet\": \"192.0.2.0/24\","
        "    \"4o6-interface-id\": \"vlan123\" } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected 4o6-interface-id configured.
    Subnet4Ptr subnet = CfgMgr::instance().getStagingCfg()->
        getCfgSubnets4()->selectSubnet(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);

    Cfg4o6& dhcp4o6 = subnet->get4o6();
    EXPECT_TRUE(dhcp4o6.enabled());
    OptionPtr ifaceid = dhcp4o6.getInterfaceId();
    ASSERT_TRUE(ifaceid);

    vector<uint8_t> data = ifaceid->getData();
    EXPECT_EQ(7, data.size());
    const char *exp = "vlan123";
    EXPECT_EQ(0, memcmp(&data[0], exp, data.size()));
}

// Verifies that simple list of valid classes parses and
// is staged for commit.
TEST_F(Dhcp4ParserTest, validClientClassDictionary) {
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"client-classes\" : [ \n"
        "   { \n"
        "       \"name\": \"one\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"two\" \n"
        "   }, \n"
        "   { \n"
        "       \"name\": \"three\" \n"
        "   } \n"
        "], \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ], \n"
        "    \"subnet\": \"192.0.2.0/24\"  \n"
        " } ] \n"
        "} \n";


    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // We check staging config because CfgMgr::commit hasn't been executed.
    ClientClassDictionaryPtr dictionary;
    dictionary = CfgMgr::instance().getStagingCfg()->getClientClassDictionary();
    ASSERT_TRUE(dictionary);
    EXPECT_EQ(3, dictionary->getClasses()->size());

    // Execute the commit
    ASSERT_NO_THROW(CfgMgr::instance().commit());

    // Verify that after commit, the current config has the correct dictionary
    dictionary = CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    ASSERT_TRUE(dictionary);
    EXPECT_EQ(3, dictionary->getClasses()->size());
}

// Verifies that a class list containing an invalid
// class definition causes a configuration error.
TEST_F(Dhcp4ParserTest, invalidClientClassDictionary) {
    string config = "{ " + genIfaceConfig() + "," +
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"client-classes\" : [ \n"
        "   { \n"
        "       \"name\": \"one\", \n"
        "       \"bogus\": \"bad\" \n"
        "   } \n"
        "], \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\":  \"192.0.2.1 - 192.0.2.100\" } ], \n"
        "    \"subnet\": \"192.0.2.0/24\"  \n"
        " } ] \n"
        "} \n";

    EXPECT_THROW(parseDHCP4(config), Dhcp4ParseError);
}

// Test verifies that regular configuration does not provide any user context
// in the address pool.
TEST_F(Dhcp4ParserTest, poolUserContextMissing) {
    extractConfig(PARSER_CONFIGS[0]);
    PoolPtr pool;
    getPool(string(PARSER_CONFIGS[0]), 0, 0, pool);
    ASSERT_TRUE(pool);
    EXPECT_FALSE(pool->getContext());
}

// Test verifies that it's possible to specify empty user context in the
// address pool.
TEST_F(Dhcp4ParserTest, poolUserContextEmpty) {
    extractConfig(PARSER_CONFIGS[1]);
    PoolPtr pool;
    getPool(string(PARSER_CONFIGS[1]), 0, 0, pool);
    ASSERT_TRUE(pool);
    ConstElementPtr ctx = pool->getContext();
    ASSERT_TRUE(ctx);

    // The context should be of type map and not contain any parameters.
    EXPECT_EQ(Element::map, ctx->getType());
    EXPECT_EQ(0, ctx->size());
}

// Test verifies that it's possible to specify parameters in the user context
// in the address pool.
TEST_F(Dhcp4ParserTest, poolUserContextData) {
    extractConfig(PARSER_CONFIGS[2]);
    PoolPtr pool;
    getPool(string(PARSER_CONFIGS[2]), 0, 0, pool);
    ASSERT_TRUE(pool);
    ConstElementPtr ctx = pool->getContext();
    ASSERT_TRUE(ctx);

    // The context should be of type map and contain 4 parameters.
    EXPECT_EQ(Element::map, ctx->getType());
    EXPECT_EQ(3, ctx->size());
    ConstElementPtr int_param  = ctx->get("integer-param");
    ConstElementPtr str_param  = ctx->get("string-param");
    ConstElementPtr bool_param = ctx->get("bool-param");

    ASSERT_TRUE(int_param);
    ASSERT_EQ(Element::integer, int_param->getType());
    int64_t int_value;
    EXPECT_NO_THROW(int_param->getValue(int_value));
    EXPECT_EQ(42L, int_value);

    ASSERT_TRUE(str_param);
    ASSERT_EQ(Element::string, str_param->getType());
    EXPECT_EQ("Sagittarius", str_param->stringValue());

    ASSERT_TRUE(bool_param);
    bool bool_value;
    ASSERT_EQ(Element::boolean, bool_param->getType());
    EXPECT_NO_THROW(bool_param->getValue(bool_value));
    EXPECT_TRUE(bool_value);
}

// Test verifies that it's possible to specify parameters in the user context
// in the min-max address pool.
TEST_F(Dhcp4ParserTest, pooMinMaxlUserContext) {
    extractConfig(PARSER_CONFIGS[3]);
    PoolPtr pool;
    getPool(string(PARSER_CONFIGS[3]), 0, 0, pool);
    ASSERT_TRUE(pool);
    ConstElementPtr ctx = pool->getContext();
    ASSERT_TRUE(ctx);

    // The context should be of type map and contain 4 parameters.
    EXPECT_EQ(Element::map, ctx->getType());
    EXPECT_EQ(3, ctx->size());
    ConstElementPtr int_param  = ctx->get("integer-param");
    ConstElementPtr str_param  = ctx->get("string-param");
    ConstElementPtr bool_param = ctx->get("bool-param");

    ASSERT_TRUE(int_param);
    ASSERT_EQ(Element::integer, int_param->getType());
    int64_t int_value;
    EXPECT_NO_THROW(int_param->getValue(int_value));
    EXPECT_EQ(42L, int_value);

    ASSERT_TRUE(str_param);
    ASSERT_EQ(Element::string, str_param->getType());
    EXPECT_EQ("Sagittarius", str_param->stringValue());

    ASSERT_TRUE(bool_param);
    bool bool_value;
    ASSERT_EQ(Element::boolean, bool_param->getType());
    EXPECT_NO_THROW(bool_param->getValue(bool_value));
    EXPECT_TRUE(bool_value);
}

// Test verifies the error message for an incorrect pool range
// is what we expect.
TEST_F(Dhcp4ParserTest, invalidPoolRange) {
    string config = "{ " + genIfaceConfig() + ", \n" +
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 19.2.0.200\" } ], \n"
        "    \"subnet\": \"192.0.2.0/24\"  \n"
        " } ] \n"
        "} \n";

    string expected = "Failed to create pool defined by: "
        "192.0.2.1-19.2.0.200 (<string>:6:26)";

    configure(config, CONTROL_RESULT_ERROR, expected);
}

// Test verifies the error message for an outside subnet pool range
// is what we expect.
TEST_F(Dhcp4ParserTest, outsideSubnetPool) {
    string config = "{ " + genIfaceConfig() + ", \n" +
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ], \n"
        "    \"subnet\": \"10.0.2.0/24\"  \n"
        " } ] \n"
        "} \n";

    string expected = "subnet configuration failed: "
        "a pool of type V4, with the following address range: "
        "192.0.2.1-192.0.2.100 does not match the prefix of a subnet: "
        "10.0.2.0/24 to which it is being added (<string>:5:14)";

    configure(config, CONTROL_RESULT_ERROR, expected);
}

// Test verifies that empty shared networks are accepted.
TEST_F(Dhcp4ParserTest, sharedNetworksEmpty) {
    string config = "{\n"
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"10.0.2.1 - 10.0.2.100\" } ], \n"
        "    \"subnet\": \"10.0.2.0/24\"  \n"
        " } ],\n"
        "\"shared-networks\": [ ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_SUCCESS, "");
}

// Test verifies that if a shared network is defined, it at least has to have
// a name.
TEST_F(Dhcp4ParserTest, sharedNetworksNoName) {
    string config = "{\n"
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"10.0.2.1 - 10.0.2.100\" } ], \n"
        "    \"subnet\": \"10.0.2.0/24\"  \n"
        " } ],\n"
        "\"shared-networks\": [ { } ]\n"
        "} \n";

    EXPECT_THROW(parseDHCP4(config, true), Dhcp4ParseError);
}

// Test verifies that empty shared networks are accepted.
TEST_F(Dhcp4ParserTest, sharedNetworksEmptyName) {
    string config = "{\n"
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"10.0.2.1 - 10.0.2.100\" } ], \n"
        "    \"subnet\": \"10.0.2.0/24\"  \n"
        " } ],\n"
        "\"shared-networks\": [ { \"name\": \"\" } ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_ERROR,
              "Shared-network with subnets  is missing mandatory 'name' parameter");
}

// Test verifies that a degenerated shared-network (no subnets) is
// accepted.
TEST_F(Dhcp4ParserTest, sharedNetworksName) {
    string config = "{\n"
        "\"subnet4\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"10.0.2.1 - 10.0.2.100\" } ], \n"
        "    \"subnet\": \"10.0.2.0/24\"  \n"
        " } ],\n"
        "\"shared-networks\": [ { \"name\": \"foo\" } ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Now verify that the shared network was indeed configured.
    CfgSharedNetworks4Ptr cfg_net = CfgMgr::instance().getStagingCfg()
        ->getCfgSharedNetworks4();
    ASSERT_TRUE(cfg_net);
    const SharedNetwork4Collection* nets = cfg_net->getAll();
    ASSERT_TRUE(nets);
    ASSERT_EQ(1, nets->size());
    SharedNetwork4Ptr net = *(nets->begin());
    ASSERT_TRUE(net);
    EXPECT_EQ("foo", net->getName());

    // Verify that there are no subnets in this shared-network
    const Subnet4Collection * subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(0, subs->size());
}

// Test verifies that a degenerated shared-network (just one subnet) is
// accepted.
TEST_F(Dhcp4ParserTest, sharedNetworks1subnet) {
    string config = "{\n"
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"shared-networks\": [ {\n"
        "    \"name\": \"foo\"\n,"
        "    \"subnet4\": [ { \n"
        "        \"subnet\": \"192.0.2.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.2.1-192.0.2.10\" } ]\n"
        "    } ]\n"
        " } ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Now verify that the shared network was indeed configured.
    CfgSharedNetworks4Ptr cfg_net = CfgMgr::instance().getStagingCfg()
        ->getCfgSharedNetworks4();
    ASSERT_TRUE(cfg_net);

    // There should be exactly one shared subnet.
    const SharedNetwork4Collection* nets = cfg_net->getAll();
    ASSERT_TRUE(nets);
    ASSERT_EQ(1, nets->size());

    SharedNetwork4Ptr net = *(nets->begin());
    ASSERT_TRUE(net);
    EXPECT_EQ("foo", net->getName());

    // It should have one subnet.
    const Subnet4Collection * subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(1, subs->size());
    checkSubnet(*subs, "192.0.2.0/24", 1000, 2000, 4000);

    // Now make sure the subnet was added to global list of subnets.
    CfgSubnets4Ptr subnets4 = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    ASSERT_TRUE(subnets4);

    subs = subnets4->getAll();
    ASSERT_TRUE(subs);
    checkSubnet(*subs, "192.0.2.0/24", 1000, 2000, 4000);
}

// Test verifies that a proper shared-network (three subnets) is
// accepted. It verifies several things:
// - that more than one subnet can be added to shared subnets
// - that each subnet being part of the shared subnets is also stored in
//   global subnets collection
// - that a subnet can inherit global values
// - that subnet can override global parameters
// - that overridden parameters only affect one subnet and not others
TEST_F(Dhcp4ParserTest, sharedNetworks3subnets) {
    string config = "{\n"
        "\"valid-lifetime\": 4000, \n"
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000, \n"
        "\"shared-networks\": [ {\n"
        "    \"name\": \"foo\"\n,"
        "    \"subnet4\": [\n"
        "    { \n"
        "        \"subnet\": \"192.0.1.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.1.1-192.0.1.10\" } ]\n"
        "    },\n"
        "    { \n"
        "        \"subnet\": \"192.0.2.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.2.1-192.0.2.10\" } ],\n"
        "        \"renew-timer\": 2,\n"
        "        \"rebind-timer\": 22,\n"
        "        \"valid-lifetime\": 222\n"
        "    },\n"
        "    { \n"
        "        \"subnet\": \"192.0.3.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.3.1-192.0.3.10\" } ]\n"
        "    }\n"
        "    ]\n"
        " } ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Now verify that the shared network was indeed configured.
    CfgSharedNetworks4Ptr cfg_net = CfgMgr::instance().getStagingCfg()
        ->getCfgSharedNetworks4();

    // There is expected one shared subnet.
    ASSERT_TRUE(cfg_net);
    const SharedNetwork4Collection* nets = cfg_net->getAll();
    ASSERT_TRUE(nets);
    ASSERT_EQ(1, nets->size());

    SharedNetwork4Ptr net = *(nets->begin());
    ASSERT_TRUE(net);

    EXPECT_EQ("foo", net->getName());

    const Subnet4Collection * subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(3, subs->size());
    checkSubnet(*subs, "192.0.1.0/24", 1000, 2000, 4000);
    checkSubnet(*subs, "192.0.2.0/24", 2, 22, 222);
    checkSubnet(*subs, "192.0.3.0/24", 1000, 2000, 4000);

    // Now make sure the subnet was added to global list of subnets.
    CfgSubnets4Ptr subnets4 = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    ASSERT_TRUE(subnets4);

    subs = subnets4->getAll();
    ASSERT_TRUE(subs);
    checkSubnet(*subs, "192.0.1.0/24", 1000, 2000, 4000);
    checkSubnet(*subs, "192.0.2.0/24", 2, 22, 222);
    checkSubnet(*subs, "192.0.3.0/24", 1000, 2000, 4000);
}

// This test checks if parameters are derived properly:
// - global to shared network
// - shared network to subnet
// Also, it tests that more than one shared network can be defined.
TEST_F(Dhcp4ParserTest, sharedNetworksDerive) {

    // We need to fake the interfaces present, because we want to test
    // interface names inheritance. However, there are sanity checks
    // on subnet level that would refuse the value if the interface
    // is not present.
    IfaceMgrTestConfig iface_config(true);

    // This config is structured in a way that the first shared
    // subnet have many parameters defined. The first subnet
    // should inherit them. The second subnet overrides all
    // values and those values should be used, not those from
    // shared network scope.
    string config = "{\n"
        "\"renew-timer\": 1, \n" // global values here
        "\"rebind-timer\": 2, \n"
        "\"valid-lifetime\": 4, \n"
        "\"shared-networks\": [ {\n"
        "    \"name\": \"foo\"\n," // shared network values here
        "    \"interface\": \"eth0\",\n"
        "    \"match-client-id\": false,\n"
        "    \"authoritative\": true,\n"
        "    \"next-server\": \"1.2.3.4\",\n"
        "    \"server-hostname\": \"foo\",\n"
        "    \"boot-file-name\": \"bar\",\n"
        "    \"relay\": {\n"
        "        \"ip-address\": \"5.6.7.8\"\n"
        "    },\n"
        "    \"reservation-mode\": \"out-of-pool\",\n"
        "    \"renew-timer\": 10,\n"
        "    \"rebind-timer\": 20,\n"
        "    \"valid-lifetime\": 40,\n"
        "    \"subnet4\": [\n"
        "    { \n"
        "        \"subnet\": \"192.0.1.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.1.1-192.0.1.10\" } ]\n"
        "    },\n"
        "    { \n"
        "        \"subnet\": \"192.0.2.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.2.1-192.0.2.10\" } ],\n"
        "        \"renew-timer\": 100,\n"
        "        \"rebind-timer\": 200,\n"
        "        \"valid-lifetime\": 400,\n"
        "        \"match-client-id\": true,\n"
        "        \"next-server\": \"11.22.33.44\",\n"
        "        \"server-hostname\": \"some-name.example.org\",\n"
        "        \"boot-file-name\": \"bootfile.efi\",\n"
        "        \"relay\": {\n"
        "            \"ip-address\": \"55.66.77.88\"\n"
        "        },\n"
        "        \"reservation-mode\": \"disabled\"\n"
        "    }\n"
        "    ]\n"
        " },\n"
        "{ // second shared-network starts here\n"
        "    \"name\": \"bar\",\n"
        "    \"subnet4\": [\n"
        "    {\n"
        "        \"subnet\": \"192.0.3.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.3.1-192.0.3.10\" } ]\n"
        "    }\n"
        "    ]\n"

        " } ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Now verify that the shared network was indeed configured.
    CfgSharedNetworks4Ptr cfg_net = CfgMgr::instance().getStagingCfg()
        ->getCfgSharedNetworks4();

    // Two shared networks are expected.
    ASSERT_TRUE(cfg_net);
    const SharedNetwork4Collection* nets = cfg_net->getAll();
    ASSERT_TRUE(nets);
    ASSERT_EQ(2, nets->size());

    SharedNetwork4Ptr net = nets->at(0);
    ASSERT_TRUE(net);

    // The first shared network has two subnets.
    const Subnet4Collection * subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(2, subs->size());

    // For the first subnet, the renew-timer should be 10, because it was
    // derived from shared-network level. Other parameters a derived
    // from global scope to shared-network level and later again to
    // subnet4 level.
    Subnet4Ptr s = checkSubnet(*subs, "192.0.1.0/24", 10, 20, 40);
    ASSERT_TRUE(s);

    // These are values derived from shared network scope:
    EXPECT_EQ("eth0", s->getIface().get());
    EXPECT_FALSE(s->getMatchClientId());
    EXPECT_TRUE(s->getAuthoritative());
    EXPECT_EQ(IOAddress("1.2.3.4"), s->getSiaddr());
    EXPECT_EQ("foo", s->getSname().get());
    EXPECT_EQ("bar", s->getFilename().get());
    EXPECT_TRUE(s->hasRelayAddress(IOAddress("5.6.7.8")));
    EXPECT_EQ(Network::HR_OUT_OF_POOL, s->getHostReservationMode());

    // For the second subnet, the renew-timer should be 100, because it
    // was specified explicitly. Other parameters a derived
    // from global scope to shared-network level and later again to
    // subnet4 level.
    s = checkSubnet(*subs, "192.0.2.0/24", 100, 200, 400);

    // These are values derived from shared network scope:
    EXPECT_EQ("eth0", s->getIface().get());
    EXPECT_TRUE(s->getMatchClientId());
    EXPECT_TRUE(s->getAuthoritative());
    EXPECT_EQ(IOAddress("11.22.33.44"), s->getSiaddr().get());
    EXPECT_EQ("some-name.example.org", s->getSname().get());
    EXPECT_EQ("bootfile.efi", s->getFilename().get());
    EXPECT_TRUE(s->hasRelayAddress(IOAddress("55.66.77.88")));
    EXPECT_EQ(Network::HR_DISABLED, s->getHostReservationMode());

    // Ok, now check the second shared subnet.
    net = nets->at(1);
    ASSERT_TRUE(net);

    subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(1, subs->size());

    // This subnet should derive its renew-timer from global scope.
    // All other parameters should have default values.
    s = checkSubnet(*subs, "192.0.3.0/24", 1, 2, 4);
    EXPECT_EQ("", s->getIface().get());
    EXPECT_TRUE(s->getMatchClientId());
    EXPECT_FALSE(s->getAuthoritative());
    EXPECT_EQ(IOAddress("0.0.0.0"), s->getSiaddr());
    EXPECT_TRUE(s->getSname().empty());
    EXPECT_TRUE(s->getFilename().empty());
    EXPECT_FALSE(s->hasRelays());
    EXPECT_EQ(Network::HR_ALL, s->getHostReservationMode());
}

// This test checks if client-class is derived properly.
TEST_F(Dhcp4ParserTest, sharedNetworksDeriveClientClass) {

    // This config is structured in a way that the first shared network has
    // client-class defined. This should in general be inherited by subnets, but
    // it's also possible to override the values on subnet level.
    string config = "{\n"
        "\"renew-timer\": 1, \n" // global values here
        "\"rebind-timer\": 2, \n"
        "\"valid-lifetime\": 4, \n"
        "\"shared-networks\": [ {\n"
        "    \"name\": \"foo\"\n," // shared network values here
        "    \"client-class\": \"alpha\",\n"
        "    \"subnet4\": [\n"
        "    { \n"
        "        \"subnet\": \"192.0.1.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.1.1-192.0.1.10\" } ]\n"
        "    },\n"
        "    { \n"
        "        \"subnet\": \"192.0.2.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.2.1-192.0.2.10\" } ],\n"
        "        \"client-class\": \"beta\"\n"
        "    }\n"
        "    ]\n"
        " },\n"
        "{ // second shared-network starts here\n"
        "    \"name\": \"bar\",\n"
        "    \"subnet4\": [\n"
        "    {\n"
        "        \"subnet\": \"192.0.3.0/24\",\n"
        "        \"pools\": [ { \"pool\": \"192.0.3.1-192.0.3.10\" } ]\n"
        "    }\n"
        "    ]\n"

        " } ]\n"
        "} \n";

    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Now verify that the shared network was indeed configured.
    CfgSharedNetworks4Ptr cfg_net = CfgMgr::instance().getStagingCfg()
        ->getCfgSharedNetworks4();

    // Two shared networks are expected.
    ASSERT_TRUE(cfg_net);
    const SharedNetwork4Collection* nets = cfg_net->getAll();
    ASSERT_TRUE(nets);
    ASSERT_EQ(2, nets->size());

    SharedNetwork4Ptr net = nets->at(0);
    ASSERT_TRUE(net);

    EXPECT_EQ("alpha", net->getClientClass().get());

    // The first shared network has two subnets.
    const Subnet4Collection * subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(2, subs->size());

    // For the first subnet, the client-class should be inherited from
    // shared-network level.
    Subnet4Ptr s = checkSubnet(*subs, "192.0.1.0/24", 1, 2, 4);
    ASSERT_TRUE(s);
    EXPECT_EQ("alpha", s->getClientClass().get());

    // For the second subnet, the values are overridden on subnet level.
    // The value should not be inherited.
    s = checkSubnet(*subs, "192.0.2.0/24", 1, 2, 4);
    EXPECT_EQ("beta", s->getClientClass().get()); // beta defined on subnet level

    // Ok, now check the second shared network. It doesn't have anything defined
    // on shared-network or subnet level, so everything should have default
    // values.
    net = nets->at(1);
    ASSERT_TRUE(net);

    subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    EXPECT_EQ(1, subs->size());

    s = checkSubnet(*subs, "192.0.3.0/24", 1, 2, 4);
    EXPECT_TRUE(s->getClientClass().empty());
}

// This test checks multiple host data sources.
TEST_F(Dhcp4ParserTest, hostsDatabases) {

    string config = PARSER_CONFIGS[4];
    extractConfig(config);
    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Check database config
    ConstCfgDbAccessPtr cfgdb =
        CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
    ASSERT_TRUE(cfgdb);
    const std::list<std::string>& hal = cfgdb->getHostDbAccessStringList();
    ASSERT_EQ(2, hal.size());
    // Keywords are in alphabetical order
    EXPECT_EQ("name=keatest1 password=keatest type=mysql user=keatest", hal.front());
    EXPECT_EQ("name=keatest2 password=keatest type=mysql user=keatest", hal.back());
}

// This test checks comments. Please keep it last.
TEST_F(Dhcp4ParserTest, comments) {

    string config = PARSER_CONFIGS[5];
    extractConfig(config);
    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Check global user context.
    ConstElementPtr ctx = CfgMgr::instance().getStagingCfg()->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(1, ctx->size());
    ASSERT_TRUE(ctx->get("comment"));
    EXPECT_EQ("\"A DHCPv4 server\"", ctx->get("comment")->str());

    // There is a network interface configuration.
    ConstCfgIfacePtr iface = CfgMgr::instance().getStagingCfg()->getCfgIface();
    ASSERT_TRUE(iface);

    // Check network interface configuration user context.
    ConstElementPtr ctx_iface = iface->getContext();
    ASSERT_TRUE(ctx_iface);
    ASSERT_EQ(1, ctx_iface->size());
    ASSERT_TRUE(ctx_iface->get("comment"));
    EXPECT_EQ("\"Use wildcard\"", ctx_iface->get("comment")->str());

    // There is a global option definition.
    const OptionDefinitionPtr& opt_def =
        LibDHCP::getRuntimeOptionDef("isc", 100);
    ASSERT_TRUE(opt_def);
    EXPECT_EQ("foo", opt_def->getName());
    EXPECT_EQ(100, opt_def->getCode());
    EXPECT_FALSE(opt_def->getArrayType());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, opt_def->getType());
    EXPECT_TRUE(opt_def->getEncapsulatedSpace().empty());

    // Check option definition user context.
    ConstElementPtr ctx_opt_def = opt_def->getContext();
    ASSERT_TRUE(ctx_opt_def);
    ASSERT_EQ(1, ctx_opt_def->size());
    ASSERT_TRUE(ctx_opt_def->get("comment"));
    EXPECT_EQ("\"An option definition\"", ctx_opt_def->get("comment")->str());

    // There is an option descriptor aka option data.
    const OptionDescriptor& opt_desc =
        CfgMgr::instance().getStagingCfg()->getCfgOption()->
            get(DHCP4_OPTION_SPACE, DHO_DHCP_MESSAGE);
    ASSERT_TRUE(opt_desc.option_);
    EXPECT_EQ(DHO_DHCP_MESSAGE, opt_desc.option_->getType());

    // Check option descriptor user context.
    ConstElementPtr ctx_opt_desc = opt_desc.getContext();
    ASSERT_TRUE(ctx_opt_desc);
    ASSERT_EQ(1, ctx_opt_desc->size());
    ASSERT_TRUE(ctx_opt_desc->get("comment"));
    EXPECT_EQ("\"Set option value\"", ctx_opt_desc->get("comment")->str());

    // And there are some client classes.
    const ClientClassDictionaryPtr& dict =
        CfgMgr::instance().getStagingCfg()->getClientClassDictionary();
    ASSERT_TRUE(dict);
    EXPECT_EQ(3, dict->getClasses()->size());
    ClientClassDefPtr cclass = dict->findClass("all");
    ASSERT_TRUE(cclass);
    EXPECT_EQ("all", cclass->getName());
    EXPECT_EQ("'' == ''", cclass->getTest());

    // Check client class user context.
    ConstElementPtr ctx_class = cclass->getContext();
    ASSERT_TRUE(ctx_class);
    ASSERT_EQ(1, ctx_class->size());
    ASSERT_TRUE(ctx_class->get("comment"));
    EXPECT_EQ("\"match all\"", ctx_class->get("comment")->str());

    // The 'none' class has no user-context/comment.
    cclass = dict->findClass("none");
    ASSERT_TRUE(cclass);
    EXPECT_EQ("none", cclass->getName());
    EXPECT_EQ("", cclass->getTest());
    EXPECT_FALSE(cclass->getContext());

    // The 'both' class has a user context and a comment.
    cclass = dict->findClass("both");
    EXPECT_EQ("both", cclass->getName());
    EXPECT_EQ("", cclass->getTest());
    ctx_class = cclass->getContext();
    ASSERT_TRUE(ctx_class);
    ASSERT_EQ(2, ctx_class->size());
    ASSERT_TRUE(ctx_class->get("comment"));
    EXPECT_EQ("\"a comment\"", ctx_class->get("comment")->str());
    ASSERT_TRUE(ctx_class->get("version"));
    EXPECT_EQ("1", ctx_class->get("version")->str());

    // There is a control socket.
    ConstElementPtr socket =
        CfgMgr::instance().getStagingCfg()->getControlSocketInfo();
    ASSERT_TRUE(socket);
    ASSERT_TRUE(socket->get("socket-type"));
    EXPECT_EQ("\"unix\"", socket->get("socket-type")->str());
    ASSERT_TRUE(socket->get("socket-name"));
    EXPECT_EQ("\"/tmp/kea4-ctrl-socket\"", socket->get("socket-name")->str());

    // Check control socket comment and user context.
    ConstElementPtr ctx_socket = socket->get("user-context");
    ASSERT_EQ(1, ctx_socket->size());
    ASSERT_TRUE(ctx_socket->get("comment"));
    EXPECT_EQ("\"Indirect comment\"", ctx_socket->get("comment")->str());

    // Now verify that the shared network was indeed configured.
    const CfgSharedNetworks4Ptr& cfg_net =
        CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4();
    ASSERT_TRUE(cfg_net);
    const SharedNetwork4Collection* nets = cfg_net->getAll();
    ASSERT_TRUE(nets);
    ASSERT_EQ(1, nets->size());
    SharedNetwork4Ptr net = nets->at(0);
    ASSERT_TRUE(net);
    EXPECT_EQ("foo", net->getName());

    // Check shared network user context.
    ConstElementPtr ctx_net = net->getContext();
    ASSERT_TRUE(ctx_net);
    ASSERT_EQ(1, ctx_net->size());
    ASSERT_TRUE(ctx_net->get("comment"));
    EXPECT_EQ("\"A shared network\"", ctx_net->get("comment")->str());

    // The shared network has a subnet.
    const Subnet4Collection* subs = net->getAllSubnets();
    ASSERT_TRUE(subs);
    ASSERT_EQ(1, subs->size());
    Subnet4Ptr sub = subs->at(0);
    ASSERT_TRUE(sub);
    EXPECT_EQ(100, sub->getID());
    EXPECT_EQ("192.0.1.0/24", sub->toText());

    // Check subnet user context.
    ConstElementPtr ctx_sub = sub->getContext();
    ASSERT_TRUE(ctx_sub);
    ASSERT_EQ(1, ctx_sub->size());
    ASSERT_TRUE(ctx_sub->get("comment"));
    EXPECT_EQ("\"A subnet\"", ctx_sub->get("comment")->str());

    // The subnet has a pool.
    const PoolCollection& pools = sub->getPools(Lease::TYPE_V4);
    ASSERT_EQ(1, pools.size());
    PoolPtr pool = pools.at(0);
    ASSERT_TRUE(pool);

    // Check pool user context.
    ConstElementPtr ctx_pool = pool->getContext();
    ASSERT_TRUE(ctx_pool);
    ASSERT_EQ(1, ctx_pool->size());
    ASSERT_TRUE(ctx_pool->get("comment"));
    EXPECT_EQ("\"A pool\"", ctx_pool->get("comment")->str());

    // The subnet has a host reservation.
    uint8_t hw[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    ConstHostPtr host =
        CfgMgr::instance().getStagingCfg()->getCfgHosts()->
        get4(100, Host::IDENT_HWADDR, &hw[0], sizeof(hw));
    ASSERT_TRUE(host);
    EXPECT_EQ(Host::IDENT_HWADDR, host->getIdentifierType());
    EXPECT_EQ("aa:bb:cc:dd:ee:ff", host->getHWAddress()->toText(false));
    EXPECT_FALSE(host->getDuid());
    EXPECT_EQ(100, host->getIPv4SubnetID());
    EXPECT_EQ(SUBNET_ID_UNUSED, host->getIPv6SubnetID());
    EXPECT_EQ("foo.example.com", host->getHostname());

    // Check host user context.
    ConstElementPtr ctx_host = host->getContext();
    ASSERT_TRUE(ctx_host);
    ASSERT_EQ(1, ctx_host->size());
    ASSERT_TRUE(ctx_host->get("comment"));
    EXPECT_EQ("\"A host reservation\"", ctx_host->get("comment")->str());

    // The host reservation has an option data.
    ConstCfgOptionPtr opts = host->getCfgOption4();
    ASSERT_TRUE(opts);
    EXPECT_FALSE(opts->empty());
    const OptionDescriptor& host_desc =
        opts->get(DHCP4_OPTION_SPACE, DHO_DOMAIN_NAME);
    ASSERT_TRUE(host_desc.option_);
    EXPECT_EQ(DHO_DOMAIN_NAME, host_desc.option_->getType());

    // Check embedded option data user context.
    ConstElementPtr ctx_host_desc = host_desc.getContext();
    ASSERT_TRUE(ctx_host_desc);
    ASSERT_EQ(1, ctx_host_desc->size());
    ASSERT_TRUE(ctx_host_desc->get("comment"));
    EXPECT_EQ("\"An option in a reservation\"",
              ctx_host_desc->get("comment")->str());

    // Finally dynamic DNS update configuration.
    const D2ClientConfigPtr& d2 =
        CfgMgr::instance().getStagingCfg()->getD2ClientConfig();
    ASSERT_TRUE(d2);
    EXPECT_FALSE(d2->getEnableUpdates());

    // Check dynamic DNS update configuration user context.
    ConstElementPtr ctx_d2 = d2->getContext();
    ASSERT_TRUE(ctx_d2);
    ASSERT_EQ(1, ctx_d2->size());
    ASSERT_TRUE(ctx_d2->get("comment"));
    EXPECT_EQ("\"No dynamic DNS\"", ctx_d2->get("comment")->str());

#if 0
    // Loggers section supports comments too.

    string logging = "{\n"
        "\"loggers\": [ {\n"
        "    \"comment\": \"A logger\",\n"
        "    \"name\": \"kea-dhcp4\"\n"
        "} ]\n";
#endif
}

// This test verifies that the global host reservations can be specified
TEST_F(Dhcp4ParserTest, globalReservations) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + "," +
        "\"rebind-timer\": 2000, \n"
        "\"renew-timer\": 1000,\n"
        "\"reservations\": [\n"
        " {\n"
        "        \"duid\": \"01:02:03:04:05:06:07:08:09:0A\",\n"
        "        \"ip-address\": \"192.0.200.1\",\n"
        "        \"hostname\": \"global1\",\n"
        "        \"option-data\": [\n"
        "        {\n"
        "          \"name\": \"name-servers\",\n"
        "          \"data\": \"192.0.3.15\"\n"
        "        },\n"
        "        {\n"
        "          \"name\": \"default-ip-ttl\",\n"
        "          \"data\": \"32\"\n"
        "        }\n"
        "        ]\n"
        " },\n"
        " {\n"
        "        \"hw-address\": \"01:02:03:04:05:06\",\n"
        "        \"hostname\": \"global2\",\n"
        "        \"option-data\": [\n"
        "        {\n"
        "          \"name\": \"name-servers\",\n"
        "          \"data\": \"192.0.3.95\"\n"
        "        },\n"
        "        {\n"
        "          \"name\": \"default-ip-ttl\",\n"
        "          \"data\": \"11\"\n"
        "        }\n"
        "        ]\n"
        " }],\n"
        "\"subnet4\": [ \n"
        " { \n"
        "    \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],\n"
        "    \"subnet\": \"192.0.2.0/24\", \n"
        "    \"id\": 123,\n"
        "    \"reservations\": [\n"
        "    ]\n"
        " },\n"
        " {\n"
        "    \"pools\": [ { \"pool\": \"192.0.4.101 - 192.0.4.150\" } ],\n"
        "    \"subnet\": \"192.0.4.0/24\",\n"
        "    \"id\": 542\n"
        " } ],\n"
        "\"valid-lifetime\": 4000"
        "}\n";

    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(config));
    extractConfig(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    checkResult(x, 0);

    // Make sure all subnets have been successfully configured. There is no
    // need to sanity check the subnet properties because it should have
    // been already tested by other tests.
    const Subnet4Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(2, subnets->size());

    // Hosts configuration must be available.
    CfgHostsPtr hosts_cfg = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(hosts_cfg);

    // Let's create a hardware address of the host named "global2"
    std::vector<uint8_t> hwaddr;
    for (unsigned int i = 1; i < 7; ++i) {
        hwaddr.push_back(static_cast<uint8_t>(i));
    }

    // Retrieve the global reservation and sanity check the  hostname reserved.
    ConstHostPtr host = hosts_cfg->get4(SUBNET_ID_GLOBAL, Host::IDENT_HWADDR,
                                        &hwaddr[0], hwaddr.size());
    ASSERT_TRUE(host);
    EXPECT_EQ("global2", host->getHostname());

    // Check that options are stored correctly.
    Option4AddrLstPtr opt_dns =
        retrieveOption<Option4AddrLstPtr>(*host, DHO_NAME_SERVERS);
    ASSERT_TRUE(opt_dns);
    Option4AddrLst::AddressContainer dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(1, dns_addrs.size());
    EXPECT_EQ("192.0.3.95", dns_addrs[0].toText());
    OptionUint8Ptr opt_ttl =
        retrieveOption<OptionUint8Ptr>(*host, DHO_DEFAULT_IP_TTL);
    ASSERT_TRUE(opt_ttl);
    EXPECT_EQ(11, static_cast<int>(opt_ttl->getValue()));

    // This reservation should be global solely and not assigned to
    // either subnet
    EXPECT_FALSE(hosts_cfg->get4(123, Host::IDENT_HWADDR,
                                 &hwaddr[0], hwaddr.size()));

    EXPECT_FALSE(hosts_cfg->get4(542, Host::IDENT_HWADDR,
                                 &hwaddr[0], hwaddr.size()));

    // Do the same test for the DUID based reservation.
    std::vector<uint8_t> duid;
    for (unsigned int i = 1; i < 0xb; ++i) {
        duid.push_back(static_cast<uint8_t>(i));
    }

    // Retrieve the global reservation and sanity check the  hostname reserved.
    host = hosts_cfg->get4(SUBNET_ID_GLOBAL, Host::IDENT_DUID, &duid[0], duid.size());
    ASSERT_TRUE(host);
    EXPECT_EQ("global1", host->getHostname());

    // Check that options are assigned correctly.
    opt_dns = retrieveOption<Option4AddrLstPtr>(*host, DHO_NAME_SERVERS);
    ASSERT_TRUE(opt_dns);
    dns_addrs = opt_dns->getAddresses();
    ASSERT_EQ(1, dns_addrs.size());
    EXPECT_EQ("192.0.3.15", dns_addrs[0].toText());
    opt_ttl = retrieveOption<OptionUint8Ptr>(*host, DHO_DEFAULT_IP_TTL);
    ASSERT_TRUE(opt_ttl);
    EXPECT_EQ(32, static_cast<int>(opt_ttl->getValue()));

    // This reservation should be global solely and not assigned to
    // either subnet
    EXPECT_FALSE(hosts_cfg->get4(123, Host::IDENT_DUID, &duid[0], duid.size()));
    EXPECT_FALSE(hosts_cfg->get4(542, Host::IDENT_DUID, &duid[0], duid.size()));
}

// Rather than disable these tests they are compiled out.  This avoids them
// reporting as disbabled and thereby drawing attention to them.
// This test verifies that configuration control with unsupported type fails
TEST_F(Dhcp4ParserTest, configControlInfoNoFactory) {
    string config = PARSER_CONFIGS[6];

    // Should fail because "type=mysql" has no factories.
    configure(config, CONTROL_RESULT_ERROR,
              "The type of the configuration backend: 'mysql' is not supported");
}

// This test verifies that configuration control info gets populated.
TEST_F(Dhcp4ParserTest, configControlInfo) {
    string config = PARSER_CONFIGS[6];

    // Should be able to register a backend factory for "mysql".
    ASSERT_TRUE(TestConfigBackendDHCPv4::
                registerBackendType(ConfigBackendDHCPv4Mgr::instance(),
                                    "mysql"));

    // Should parse ok, now that the factory has been registered.
    configure(config, CONTROL_RESULT_SUCCESS, "");

    // Make sure the config control info is there.
    process::ConstConfigControlInfoPtr info =
        CfgMgr::instance().getStagingCfg()->getConfigControlInfo();
    ASSERT_TRUE(info);

    // Fetch the list of config dbs.  It should have two entries.
    const process::ConfigDbInfoList& dblist = info->getConfigDatabases();
    ASSERT_EQ(2, dblist.size());

    // Make sure the entries are what we expect and in the right order.
    // (DbAccessParser creates access strings with the keywords in
    //  alphabetical order).
    EXPECT_EQ("name=keatest1 password=keatest type=mysql user=keatest",
              dblist.front().getAccessString());
    EXPECT_EQ("name=keatest2 password=keatest type=mysql user=keatest",
              dblist.back().getAccessString());

    // Verify that the config-fetch-wait-time is correct.
    EXPECT_FALSE(info->getConfigFetchWaitTime().unspecified());
    EXPECT_EQ(10, info->getConfigFetchWaitTime().get());
}

// Check whether it is possible to configure server-tag
TEST_F(Dhcp4ParserTest, serverTag) {
    // Config without server-tag
    string config_no_tag = "{ " + genIfaceConfig() + "," +
        "\"subnet4\": [  ] "
        "}";

    // Config with server-tag
    string config_tag = "{ " + genIfaceConfig() + "," +
        "\"server-tag\": \"boo\", "
        "\"subnet4\": [  ] "
        "}";

    // Config with an invalid server-tag
    string bad_tag = "{ " + genIfaceConfig() + "," +
        "\"server-tag\": 777, "
        "\"subnet4\": [  ] "
        "}";

    // Let's check the default. It should be empty.
    ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getServerTag().empty());

    // Configuration with no tag should default to an emtpy tag value.
    configure(config_no_tag, CONTROL_RESULT_SUCCESS, "");
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getServerTag().empty());

    // Clear the config
    CfgMgr::instance().clear();

    // Configuration with the tag should have the tag value.
    configure(config_tag, CONTROL_RESULT_SUCCESS, "");
    EXPECT_EQ("boo", CfgMgr::instance().getStagingCfg()->getServerTag().get());

    // Make sure a invalid server-tag fails to parse.
    ASSERT_THROW(parseDHCP4(bad_tag), std::exception);
}

// Check whether it is possible to configure packet queue
TEST_F(Dhcp4ParserTest, dhcpQueueControl) {
    struct Scenario {
        std::string description_;
        std::string json_;
    };

    std::vector<Scenario> scenarios = {
        {
        "no entry",
        ""
        },
        {
        "queue disabled",
        "{ \n"
        "   \"enable-queue\": false \n"
        "} \n"
        },
        {
        "queue disabled, arbitrary content allowed",
        "{ \n"
        "   \"enable-queue\": false, \n"
        "   \"foo\": \"bogus\", \n"
        "   \"random-int\" : 1234 \n"
        "} \n"
        },
        {
        "queue enabled, with queue-type",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\" \n"
        "} \n"
        },
        {
        "queue enabled with queue-type and arbitrary content",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": \"some-type\", \n"
        "   \"foo\": \"bogus\", \n"
        "   \"random-int\" : 1234 \n"
        "} \n"
        }
    };

    // Let's check the default. It should be empty.
    data::ConstElementPtr staged_control;
    staged_control = CfgMgr::instance().getStagingCfg()->getDHCPQueueControl();
    ASSERT_FALSE(staged_control);

    // Iterate over the valid scenarios and verify they succeed.
    data::ElementPtr exp_control;
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            // Clear the config
            CfgMgr::instance().clear();

            // Construct the config JSON
            std::stringstream os;
            os << "{ " + genIfaceConfig();
            if (!scenario.json_.empty()) {
               os << ",\n \"dhcp-queue-control\": "  <<  scenario.json_;
            }

            os << "} \n";

            // Configure the server. This should succeed.
            configure(os.str(), CONTROL_RESULT_SUCCESS, "");

            // Fetch the queue control info.
            staged_control = CfgMgr::instance().getStagingCfg()->getDHCPQueueControl();
            // Make sure the staged queue config exists.
            ASSERT_TRUE(staged_control);
            // Now build the expected queue control content.
            if (scenario.json_.empty()) {
                exp_control = Element::createMap();
            } else {
                try {
                    exp_control = boost::const_pointer_cast<Element>(Element::fromJSON(scenario.json_));
                } catch (const std::exception& ex) {
                    ADD_FAILURE() << " cannot convert expected JSON, test is broken:"
                                << ex.what();
                }
            }

            // Add the defaults to expected queue control.
            SimpleParser4::setDefaults(exp_control, SimpleParser4::DHCP_QUEUE_CONTROL4_DEFAULTS);

            // Verify that the staged queue control equals the expected queue control.
            EXPECT_TRUE(staged_control->equals(*exp_control));
        }
    }
}

// Check that we catch invalid dhcp-queue-control content
TEST_F(Dhcp4ParserTest, dhcpQueueControlInvalid) {
    struct Scenario {
        std::string description_;
        std::string json_;
        std::string exp_error_;
    };

    std::vector<Scenario> scenarios = {
        {
        "not a map",
        "75 \n",
        "<string>:2.24-25: syntax error, unexpected integer, expecting {"
        },
        {
        "enable-queue missing",
        "{ \n"
        "   \"enable-type\": \"some-type\" \n"
        "} \n",
        "<string>:2.2-21: 'enable-queue' is required: (<string>:2:24)"
        },
        {
        "enable-queue not boolean",
        "{ \n"
        "   \"enable-queue\": \"always\" \n"
        "} \n",
        "<string>:2.2-21: 'enable-queue' must be boolean: (<string>:2:24)"
        },
        {
        "queue enabled, type not a string",
        "{ \n"
        "   \"enable-queue\": true, \n"
        "   \"queue-type\": 7777 \n"
        "} \n",
        "<string>:2.2-21: 'queue-type' must be a string: (<string>:2:24)"
        }
    };

    // Iterate over the incorrect scenarios and verify they
    // fail as expected. Note, we use parseDHCP4() directly
    // as all of the errors above are enforced by the grammar.
    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);
        {
            // Construct the config JSON
            std::stringstream os;
            os << "{ " + genIfaceConfig();
            os << ",\n \"dhcp-queue-control\": "  <<  scenario.json_;
            os << "} \n";

            std::string error_msg = "";
            try {
                ASSERT_TRUE(parseDHCP4(os.str(), false)) << "parser returned empty element";
            } catch(const std::exception& ex) {
                error_msg = ex.what();
            }

            ASSERT_FALSE(error_msg.empty()) << "parseDHCP4 should have thrown";
            EXPECT_EQ(scenario.exp_error_, error_msg);
        }
    }
}

// Checks inheritence of calculate-tee-times, t1-perecent, t2-percent
TEST_F(Dhcp4ParserTest, calculateTeeTimesInheritence) {
    // Configure the server. This should succeed.
    string config =
        "{ \n"
        "    \"interfaces-config\": { \n"
        "        \"interfaces\": [\"*\" ] \n"
        "    }, \n"
        "    \"valid-lifetime\": 4000, \n"
        "    \"shared-networks\": [ { \n"
        "        \"name\": \"foo\", \n"
        "       \"calculate-tee-times\": true, \n"
        "       \"t1-percent\": .4, \n"
        "       \"t2-percent\": .75,\n"
        "        \"subnet4\": ["
        "        { "
        "            \"id\": 100,"
        "            \"subnet\": \"192.0.1.0/24\", \n"
        "            \"pools\": [ { \"pool\": \"192.0.1.1-192.0.1.10\" } ], \n"
        "            \"calculate-tee-times\": false,\n"
        "            \"t1-percent\": .45, \n"
        "            \"t2-percent\": .65 \n"
        "        }, \n"
        "        {  \n"
        "            \"id\": 200, \n"
        "            \"subnet\": \"192.0.2.0/24\", \n"
        "            \"pools\": [ { \"pool\": \"192.0.2.1-192.0.2.10\"} ] \n"
        "        } \n"
        "        ] \n"
        "     } ], \n"
        "    \"subnet4\": [ { \n"
        "        \"id\": 300, \n"
        "        \"subnet\": \"192.0.3.0/24\", \n"
        "        \"pools\": [ { \"pool\":  \"192.0.3.0 - 192.0.3.15\" } ]\n"
        "     } ] \n"
        "} \n";

    extractConfig(config);
    configure(config, CONTROL_RESULT_SUCCESS, "");

    CfgSubnets4Ptr subnets4 = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();

    // Subnet 100 should use it's own explicit values.
    ConstSubnet4Ptr subnet4 = subnets4->getBySubnetId(100);
    ASSERT_TRUE(subnet4);
    EXPECT_FALSE(subnet4->getCalculateTeeTimes());
    EXPECT_TRUE(util::areDoublesEquivalent(0.45, subnet4->getT1Percent()));
    EXPECT_TRUE(util::areDoublesEquivalent(0.65, subnet4->getT2Percent()));

    // Subnet 200 should use the shared-network values.
    subnet4 = subnets4->getBySubnetId(200);
    ASSERT_TRUE(subnet4);
    EXPECT_EQ(true, subnet4->getCalculateTeeTimes());
    EXPECT_TRUE(util::areDoublesEquivalent(0.4, subnet4->getT1Percent()));
    EXPECT_TRUE(util::areDoublesEquivalent(0.75, subnet4->getT2Percent()));

    // Subnet 300 should use the global values.
    subnet4 = subnets4->getBySubnetId(300);
    ASSERT_TRUE(subnet4);
    EXPECT_FALSE(subnet4->getCalculateTeeTimes());
    EXPECT_TRUE(util::areDoublesEquivalent(0.5, subnet4->getT1Percent()));
    EXPECT_TRUE(util::areDoublesEquivalent(0.875, subnet4->getT2Percent()));
}


}
