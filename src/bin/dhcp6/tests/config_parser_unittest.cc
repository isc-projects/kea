// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/command_interpreter.h>
#include <config/module_spec.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_ia.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/addr_utilities.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <hooks/hooks_manager.h>
#include <defaults.h>

#include "test_data_files_config.h"
#include "test_libraries.h"
#include "marker_file.h"

#include <boost/foreach.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <arpa/inet.h>
#include <unistd.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace std;

namespace {

std::string specfile(const std::string& name) {
    return (std::string(DHCP6_SRC_DIR) + "/" + name);
}

/// @brief Tests that the spec file is valid.
/// Verifies that the DHCP6 configuration specification file is valid.
TEST(Dhcp6SpecTest, basicSpec) {
    ASSERT_NO_THROW(isc::config::
                    moduleSpecFromFile(specfile("dhcp6.spec")));
}

class Dhcp6ParserTest : public ::testing::Test {
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
    Dhcp6ParserTest() :rcode_(-1), srv_(0) {
        // srv_(0) means to not open any sockets. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.

        const IfaceMgr::IfaceCollection& ifaces =
            IfaceMgr::instance().getIfaces();

        // There must be some interface detected
        if (ifaces.empty()) {
            // We can't use ASSERT in constructor
            ADD_FAILURE() << "No interfaces detected.";
        }

        valid_iface_ = (*ifaces.begin())->getName();
        bogus_iface_ = "nonexisting0";

        if (IfaceMgr::instance().getIface(bogus_iface_)) {
            ADD_FAILURE() << "The '" << bogus_iface_ << "' exists on this system"
                          << " while the test assumes that it doesn't, to execute"
                          << " some negative scenarios. Can't continue this test.";
        }

        // Reset configuration for each test.
        resetConfiguration();
    }

    ~Dhcp6ParserTest() {
        // Reset configuration database after each test.
        resetConfiguration();

        // ... and delete the hooks library marker files if present
        static_cast<void>(remove(LOAD_MARKER_FILE));
        static_cast<void>(remove(UNLOAD_MARKER_FILE));
    };

    // Checks if config_result (result of DHCP server configuration) has
    // expected code (0 for success, other for failures).
    // Also stores result in rcode_ and comment_.
    void checkResult(ConstElementPtr status, int expected_code) {
        ASSERT_TRUE(status);
        comment_ = parseAnswer(rcode_, status);
        EXPECT_EQ(expected_code, rcode_);
    }

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
    /// option value. These parameters are: "name", "code", "data" and
    /// "csv-format".
    ///
    /// @param param_value string holding option parameter value to be
    /// injected into the configuration string.
    /// @param parameter name of the parameter to be configured with
    /// param value.
    std::string createConfigWithOption(const std::string& param_value,
                                       const std::string& parameter) {
        std::map<std::string, std::string> params;
        if (parameter == "name") {
            params["name"] = param_value;
            params["space"] = "dhcp6";
            params["code"] = "38";
            params["data"] = "ABCDEF0105";
            params["csv-format"] = "False";
        } else if (parameter == "space") {
            params["name"] = "subscriber-id";
            params["space"] = param_value;
            params["code"] = "38";
            params["data"] = "ABCDEF0105";
            params["csv-format"] = "False";
        } else if (parameter == "code") {
            params["name"] = "subscriber-id";
            params["space"] = "dhcp6";
            params["code"] = param_value;
            params["data"] = "ABCDEF0105";
            params["csv-format"] = "False";
        } else if (parameter == "data") {
            params["name"] = "subscriber-id";
            params["space"] = "dhcp6";
            params["code"] = "38";
            params["data"] = param_value;
            params["csv-format"] = "False";
        } else if (parameter == "csv-format") {
            params["name"] = "subscriber-id";
            params["space"] = "dhcp6";
            params["code"] = "38";
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
    std::string createConfigWithOption(const std::map<std::string,
                                       std::string>& params)
    {
        std::ostringstream stream;
        stream << "{ " << genIfaceConfig() << ","
            "\"preferred-lifetime\": 3000,"
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"option-def\": [ {"
            "  \"name\": \"bool-option\","
            "  \"code\": 1000,"
            "  \"type\": \"boolean\","
            "  \"space\": \"dhcp6\""
            "} ],"
            "\"subnet6\": [ { "
            "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
            "    \"subnet\": \"2001:db8:1::/64\", "
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
                stream << "\"code\": " << param.second;;
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
        Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
            selectSubnet(subnet_address, classify_);
        if (!subnet) {
            /// @todo replace toText() with the use of operator <<.
            ADD_FAILURE() << "A subnet for the specified address "
                          << subnet_address.toText()
                          << " does not exist in Config Manager";
        }
        OptionContainerPtr options =
            subnet->getCfgOption()->getAll("dhcp6");
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
        ConstElementPtr status;
        try {
            ElementPtr json = Element::fromJSON(config);
            status = configureDhcp6Server(srv_, json);

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
    /// This function resets configuration data base by removing all subnets
    /// option-data, and hooks libraries. The reset must be performed after each
    /// test to make sure that contents of the database do not affect the
    /// results of subsequent tests.
    void resetConfiguration() {
        string config = "{ \"interfaces-config\": {"
            "    \"interfaces\": [ ]"
            "},"
            "\"hooks-libraries\": [ ],"
            "\"preferred-lifetime\": 3000,"
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"valid-lifetime\": 4000, "
            "\"subnet6\": [ ], "
            "\"dhcp-ddns\": { \"enable-updates\" : false }, "
            "\"option-def\": [ ], "
            "\"option-data\": [ ] }";
        static_cast<void>(executeConfiguration(config,
                                               "reset configuration database"));
        // The default setting is to listen on all interfaces. In order to
        // properly test interface configuration we disable listening on
        // all interfaces before each test and later check that this setting
        // has been overridden by the configuration used in the test.
        CfgMgr::instance().clear();
        // Create fresh context.
        globalContext()->copyContext(ParserContext(Option::V6));
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
        ElementPtr json = Element::fromJSON(config);
        EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
        checkResult(x, 1);
        EXPECT_TRUE(errorContainsPosition(x, "<string>"));
        CfgMgr::instance().clear();
    }

    /// @brief Test invalid option paramater value.
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
        ElementPtr json = Element::fromJSON(config);
        EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
        checkResult(x, 1);
        EXPECT_TRUE(errorContainsPosition(x, "<string>"));
        CfgMgr::instance().clear();
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
        CfgMgr::instance().clear();

        std::string config = createConfigWithOption(params);
        ASSERT_TRUE(executeConfiguration(config, "parse option configuration"));

        // The subnet should now hold one option with the specified code.
        OptionDescriptor desc =
            getOptionFromSubnet(IOAddress("2001:db8:1::5"), option_code);
        ASSERT_TRUE(desc.option_);
        testOption(desc, option_code, expected_data, expected_data_len);
        CfgMgr::instance().clear();
    }

    /// @brief Tests the Rapid Commit configuration for a subnet.
    ///
    /// This test configures the server with a given configuration and
    /// verifies if the Rapid Commit has been configured successfully
    /// for a subnet.
    ///
    /// @param config Server configuration, possibly including the
    /// 'rapid-commit' parameter.
    /// @param exp_rapid_commit Expected value of the Rapid Commit flag
    /// within a subnet.
    void testRapidCommit(const std::string& config,
                         const bool exp_rapid_commit) {
        // Clear any existing configuration.
        CfgMgr::instance().clear();

        // Configure the server.
        ElementPtr json = Element::fromJSON(config);

        // Make sure that the configuration was successful.
        ConstElementPtr status;
        EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
        checkResult(status, 0);

        // Get the subnet.
        Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
            selectSubnet(IOAddress("2001:db8:1::5"), classify_);
        ASSERT_TRUE(subnet);

        // Check the Rapid Commit flag for the subnet.
        EXPECT_EQ(exp_rapid_commit, subnet->getRapidCommit());

        // Clear any existing configuration.
        CfgMgr::instance().clear();
    }

    int rcode_;          ///< Return code (see @ref isc::config::parseAnswer)
    Dhcpv6Srv srv_;      ///< Instance of the Dhcp6Srv used during tests
    ConstElementPtr comment_; ///< Comment (see @ref isc::config::parseAnswer)
    string valid_iface_; ///< Valid network interface name (present in system)
    string bogus_iface_; ///< invalid network interface name (not in system)
    isc::dhcp::ClientClasses classify_; ///< used in client classification
};

// Goal of this test is a verification if a very simple config update
// with just a bumped version number. That's the simplest possible
// config update.
TEST_F(Dhcp6ParserTest, version) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_,
                    Element::fromJSON("{\"version\": 0}")));

    // returned value must be 0 (configuration accepted)
    checkResult(x, 0);
}

/// The goal of this test is to verify that the code accepts only
/// valid commands and malformed or unsupported parameters are rejected.
TEST_F(Dhcp6ParserTest, bogusCommand) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_,
                    Element::fromJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    checkResult(x, 1);
}

/// The goal of this test is to verify if configuration without any
/// subnets defined can be accepted.
TEST_F(Dhcp6ParserTest, emptySubnet) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
                    Element::fromJSON("{ " + genIfaceConfig() + ","
                                      "\"preferred-lifetime\": 3000,"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet6\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);
}

/// The goal of this test is to verify if defined subnet uses global
/// parameter timer definitions.
TEST_F(Dhcp6ParserTest, subnetGlobalDefaults) {

    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(3000, subnet->getPreferred());
    EXPECT_EQ(4000, subnet->getValid());

    // Check that subnet-id is 1
    EXPECT_EQ(1, subnet->getID());
}

// This test checks that multiple subnets can be defined and handled properly.
TEST_F(Dhcp6ParserTest, multipleSubnets) {
    ConstElementPtr x;
    // Collection of four subnets for which ids should be autogenerated
    // - ids are unspecified or set to 0.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 0"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/80\" } ],"
        "    \"subnet\": \"2001:db8:4::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    int cnt = 0; // Number of reconfigurations

    ElementPtr json = Element::fromJSON(config);

    do {
        EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
        checkResult(x, 0);

        CfgMgr::instance().commit();

        const Subnet6Collection* subnets =
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
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

// This checks that it is possible to assign arbitrary ids for subnets.
TEST_F(Dhcp6ParserTest, multipleSubnetsExplicitIDs) {
    ConstElementPtr x;
    // Four subnets with arbitrary subnet ids.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"id\": 1024"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 100"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 1"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/80\" } ],"
        "    \"subnet\": \"2001:db8:4::/64\", "
        "    \"id\": 34"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    int cnt = 0; // Number of reconfigurations

    ElementPtr json = Element::fromJSON(config);

    do {
        EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
        checkResult(x, 0);

        CfgMgr::instance().commit();

        const Subnet6Collection* subnets =
            CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
        ASSERT_TRUE(subnets);
        ASSERT_EQ(4, subnets->size()); // We expect 4 subnets

        // Check that subnet ids are as expected.
        EXPECT_EQ(1024, subnets->at(0)->getID());
        EXPECT_EQ(100, subnets->at(1)->getID());
        EXPECT_EQ(1, subnets->at(2)->getID());
        EXPECT_EQ(34, subnets->at(3)->getID());

        // Repeat reconfiguration process 10 times and check that the subnet-id
        // is set to the same value.
    } while (++cnt < 3);
}

// CHeck that the configuration with two subnets having the same id is rejected.
TEST_F(Dhcp6ParserTest, multipleSubnetsOverlapingIDs) {
    ConstElementPtr x;
    // Four subnets, two of them have the same id.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"id\": 1024"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 100"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 1024"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/80\" } ],"
        "    \"subnet\": \"2001:db8:4::/64\", "
        "    \"id\": 34"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 1);
    EXPECT_TRUE(errorContainsPosition(x, "<string>"));
}


// Goal of this test is to verify that a previously configured subnet can be
// deleted in subsequent reconfiguration.
TEST_F(Dhcp6ParserTest, reconfigureRemoveSubnet) {
    ConstElementPtr x;

    // All four subnets
    string config4 = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"id\": 1"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 2"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 3"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/80\" } ],"
        "    \"subnet\": \"2001:db8:4::/64\", "
        "    \"id\": 4"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Three subnets (the last one removed)
    string config_first3 = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"id\": 1"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 2"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 3"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // Second subnet removed
    string config_second_removed = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"id\": 1"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 3"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/80\" } ],"
        "    \"subnet\": \"2001:db8:4::/64\", "
        "    \"id\": 4"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    // CASE 1: Configure 4 subnets, then reconfigure and remove the
    // last one.

    ElementPtr json = Element::fromJSON(config4);
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    CfgMgr::instance().commit();

    const Subnet6Collection* subnets =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(4, subnets->size()); // We expect 4 subnets

    // Do the reconfiguration (the last subnet is removed)
    json = Element::fromJSON(config_first3);
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    CfgMgr::instance().commit();

    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size()); // We expect 3 subnets now (4th is removed)

    EXPECT_EQ(1, subnets->at(0)->getID());
    EXPECT_EQ(2, subnets->at(1)->getID());
    EXPECT_EQ(3, subnets->at(2)->getID());

    /// CASE 2: Configure 4 subnets, then reconfigure and remove one
    /// from in between (not first, not last)

    json = Element::fromJSON(config4);
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    CfgMgr::instance().commit();

    // Do reconfiguration
    json = Element::fromJSON(config_second_removed);
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    CfgMgr::instance().commit();

    subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size()); // We expect 4 subnets

    EXPECT_EQ(1, subnets->at(0)->getID());
    // The second subnet (with subnet-id = 2) is no longer there
    EXPECT_EQ(3, subnets->at(1)->getID());
    EXPECT_EQ(4, subnets->at(2)->getID());
}



// This test checks if it is possible to override global values
// on a per subnet basis.
TEST_F(Dhcp6ParserTest, subnetLocal) {

    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"preferred-lifetime\": 3,"
        "    \"valid-lifetime\": 4,"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getT1());
    EXPECT_EQ(2, subnet->getT2());
    EXPECT_EQ(3, subnet->getPreferred());
    EXPECT_EQ(4, subnet->getValid());
}

// This test checks if it is possible to define a subnet with an
// interface defined.
TEST_F(Dhcp6ParserTest, subnetInterface) {

    ConstElementPtr status;

    // There should be at least one interface

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"interface\": \"" + valid_iface_ + "\","
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(valid_iface_, subnet->getIface());
}

// This test checks if invalid interface name will be rejected in
// Subnet6 definition.
TEST_F(Dhcp6ParserTest, subnetInterfaceBogus) {

    ConstElementPtr status;

    // There should be at least one interface

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"interface\": \"" + bogus_iface_ + "\","
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 1 (configuration error)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    EXPECT_FALSE(subnet);
}


// This test checks if it is not allowed to define global interface
// parameter.
TEST_F(Dhcp6ParserTest, interfaceGlobal) {

    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"interface\": \"" + valid_iface_ + "\"," // Not valid. Can be defined in subnet only
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 1 (parse error)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}


// This test checks if it is possible to define a subnet with an
// interface-id option defined.
TEST_F(Dhcp6ParserTest, subnetInterfaceId) {

    const string valid_interface_id = "foobar";
    const string bogus_interface_id = "blah";

    // There should be at least one interface

    const string config = "{ "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"interface-id\": \"" + valid_interface_id + "\","
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // Returned value should be 0 (configuration success)
    checkResult(status, 0);

    // Try to get a subnet based on bogus interface-id option
    OptionBuffer tmp(bogus_interface_id.begin(), bogus_interface_id.end());
    SubnetSelector selector;
    selector.first_relay_linkaddr_ = IOAddress("5000::1");
    selector.interface_id_.reset(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(selector);
    EXPECT_FALSE(subnet);

    // Now try to get subnet for valid interface-id value
    tmp = OptionBuffer(valid_interface_id.begin(), valid_interface_id.end());
    selector.interface_id_.reset(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
    subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(selector);
    ASSERT_TRUE(subnet);
    EXPECT_TRUE(selector.interface_id_->equals(subnet->getInterfaceId()));
}


// This test checks if it is not allowed to define global interface
// parameter.
TEST_F(Dhcp6ParserTest, interfaceIdGlobal) {

    const string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"interface-id\": \"foobar\"," // Not valid. Can be defined in subnet only
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // Returned value should be 1 (parse error)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// This test checks if it is not possible to define a subnet with an
// interface (i.e. local subnet) and interface-id (remote subnet) defined.
TEST_F(Dhcp6ParserTest, subnetInterfaceAndInterfaceId) {

    const string config = "{ \"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"interface\": \"" + valid_iface_ + "\","
        "    \"interface-id\": \"foobar\","
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // Returned value should be 1 (configuration error)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// This test checks the configuration of the Rapid Commit option
// support for the subnet.
TEST_F(Dhcp6ParserTest, subnetRapidCommit) {
    {
        // rapid-commit implicitly set to false.
        SCOPED_TRACE("Default Rapid Commit setting");
        testRapidCommit("{ \"preferred-lifetime\": 3000,"
                        "\"rebind-timer\": 2000, "
                        "\"renew-timer\": 1000, "
                        "\"subnet6\": [ { "
                        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - "
                        "2001:db8:1::ffff\" } ],"
                        "    \"subnet\": \"2001:db8:1::/64\" } ],"
                        "\"valid-lifetime\": 4000 }",
                        false);
    }

    {
        // rapid-commit explicitly set to true.
        SCOPED_TRACE("Enable Rapid Commit");
        testRapidCommit("{ \"preferred-lifetime\": 3000,"
                        "\"rebind-timer\": 2000, "
                        "\"renew-timer\": 1000, "
                        "\"subnet6\": [ { "
                        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - "
                        "2001:db8:1::ffff\" } ],"
                        "    \"rapid-commit\": True,"
                        "    \"subnet\": \"2001:db8:1::/64\" } ],"
                        "\"valid-lifetime\": 4000 }",
                        true);
    }

    {
        // rapid-commit explicitly set to false.
        SCOPED_TRACE("Disable Rapid Commit");
        testRapidCommit("{ \"preferred-lifetime\": 3000,"
                        "\"rebind-timer\": 2000, "
                        "\"renew-timer\": 1000, "
                        "\"subnet6\": [ { "
                        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - "
                        "2001:db8:1::ffff\" } ],"
                        "    \"rapid-commit\": False,"
                        "    \"subnet\": \"2001:db8:1::/64\" } ],"
                        "\"valid-lifetime\": 4000 }",
                        false);
    }
}

// This test checks that multiple pools can be defined and handled properly.
// The test defines 2 subnets, each with 2 pools.
TEST_F(Dhcp6ParserTest, multiplePools) {
    // Collection with two subnets, each with 2 pools.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ "
        "        { \"pool\": \"2001:db8:1::/96\" },"
        "        { \"pool\": \"2001:db8:1:0:abcd::/112\" }"
        "    ],"
        "    \"subnet\": \"2001:db8:1::/64\" "
        " },"
        " {"
        "    \"pools\": [ "
        "    { \"pool\": \"2001:db8:2::1 - 2001:db8:2::ff\" },"
        "    { \"pool\": \"2001:db8:2::300 - 2001:db8:2::3ff\" }"
        "    ],"
        "    \"subnet\": \"2001:db8:2::/64\""
        " } ],"
        "\"valid-lifetime\": 4000 }";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    ConstElementPtr status;
    ASSERT_NO_THROW(status = configureDhcp6Server(srv_, json));
    checkResult(status, 0);

    const Subnet6Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(2, subnets->size()); // We expect 2 subnets

    // Check the first subnet
    const PoolCollection& pools1 = subnets->at(0)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(2, pools1.size());
    EXPECT_EQ("type=IA_NA, 2001:db8:1::-2001:db8:1::ffff:ffff, delegated_len=128",
              pools1[0]->toText());
    EXPECT_EQ("type=IA_NA, 2001:db8:1:0:abcd::-2001:db8:1:0:abcd::ffff, delegated_len=128",
              pools1[1]->toText());
    // There shouldn't be any TA or PD pools
    EXPECT_TRUE(subnets->at(0)->getPools(Lease::TYPE_TA).empty());
    EXPECT_TRUE(subnets->at(0)->getPools(Lease::TYPE_PD).empty());

    // Check the second subnet
    const PoolCollection& pools2 = subnets->at(1)->getPools(Lease::TYPE_NA);
    ASSERT_EQ(2, pools2.size());
    EXPECT_EQ("type=IA_NA, 2001:db8:2::1-2001:db8:2::ff, delegated_len=128",
              pools2[0]->toText());
    EXPECT_EQ("type=IA_NA, 2001:db8:2::300-2001:db8:2::3ff, delegated_len=128",
              pools2[1]->toText());
    // There shouldn't be any TA or PD pools
    EXPECT_TRUE(subnets->at(0)->getPools(Lease::TYPE_TA).empty());
    EXPECT_TRUE(subnets->at(0)->getPools(Lease::TYPE_PD).empty());
}


// Test verifies that a subnet with pool values that do not belong to that
// pool are rejected.
TEST_F(Dhcp6ParserTest, poolOutOfSubnet) {

    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"4001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";


    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value must be 1 (values error)
    // as the pool does not belong to that subnet
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// Goal of this test is to verify if pools can be defined
// using prefix/length notation. There is no separate test for min-max
// notation as it was tested in several previous tests.
// Note this test also verifies that subnets can be configured without
// prefix delegation pools.
TEST_F(Dhcp6ParserTest, poolPrefixLen) {

    ConstElementPtr x;

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));

    // returned value must be 1 (configuration parse error)
    checkResult(x, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(3000, subnet->getPreferred());
    EXPECT_EQ(4000, subnet->getValid());
}

// Goal of this test is to verify the basic parsing of a prefix delegation
// pool. It uses a single, valid pd pool.
TEST_F(Dhcp6ParserTest, pdPoolBasics) {

    ConstElementPtr x;

    // Define a single valid pd pool.
    string config =
        "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8:1::/64\","
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1::\", "
        "          \"prefix-len\": 64, "
        "          \"delegated-len\": 128"
        "        } ],"
        "\"valid-lifetime\": 4000 }"
        "] }";

    // Convert the JSON string into Elements.
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    // Verify that DHCP6 configuration processing succeeds.
    // Returned value must be non-empty ConstElementPtr to config result.
    // rcode should be 0 which indicates successful configuration processing.
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    // Test that we can retrieve the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);

    // Fetch the collection of PD pools.  It should have 1 entry.
    PoolCollection pc;
    ASSERT_NO_THROW(pc = subnet->getPools(Lease::TYPE_PD));
    EXPECT_EQ(1, pc.size());

    // Get a pointer to the pd pool instance, and verify its contents.
    Pool6Ptr p6;
    ASSERT_NO_THROW(p6 = boost::dynamic_pointer_cast<Pool6>(pc[0]));
    ASSERT_TRUE(p6);
    EXPECT_EQ("2001:db8:1::", p6->getFirstAddress().toText());
    EXPECT_EQ(128, p6->getLength());

    // prefix-len is not directly accessible after pool construction, so
    // verify that it was interpreted correctly by checking the last address
    // value.
    isc::asiolink::IOAddress prefixAddress("2001:db8:1::");
    EXPECT_EQ(lastAddrInPrefix(prefixAddress, 64), p6->getLastAddress());
}

// Goal of this test is verify that a list of PD pools can be configured.
// It also verifies that a subnet may be configured with both regular pools
// and pd pools.
TEST_F(Dhcp6ParserTest, pdPoolList) {

    ConstElementPtr x;

    // We will configure three pools of prefixes for the subnet. Note that
    // the 3rd prefix is out of the subnet prefix (the prefix doesn't match
    // the subnet prefix).
    const char* prefixes[] = {
        "2001:db8:1:1::",
        "2001:db8:1:2::",
        "3000:1:3::"
    };

    string config =
        "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1:04::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/40\","
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1:01::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 80"
        "        },"
        "        { \"prefix\": \"2001:db8:1:02::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 88"
        "        },"
        "        { \"prefix\": \"3000:1:03::\", "
        "          \"prefix-len\": 72, "
        "          \"delegated-len\": 96"
        "        }"
        "],"
        "\"valid-lifetime\": 4000 }"
        "] }";

    // Convert the JSON string into Elements.
    ElementPtr json = Element::fromJSON(config);
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    // Verify that DHCP6 configuration processing succeeds.
    // Returned value must be non-empty ConstElementPtr to config result.
    // rcode should be 0 which indicates successful configuration processing.
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    // Test that we can retrieve the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);

    // Fetch the collection of NA pools.  It should have 1 entry.
    PoolCollection pc;
    ASSERT_NO_THROW(pc = subnet->getPools(Lease::TYPE_NA));
    EXPECT_EQ(1, pc.size());

    // Fetch the collection of PD pools.  It should have 3 entries.
    ASSERT_NO_THROW(pc = subnet->getPools(Lease::TYPE_PD));
    EXPECT_EQ(3, pc.size());

    // Loop through the pools and verify their contents.
    for (int i = 0; i < 3; i++) {
        Pool6Ptr p6;
        ASSERT_NO_THROW(p6 = boost::dynamic_pointer_cast<Pool6>(pc[i]));
        ASSERT_TRUE(p6);
        EXPECT_EQ(prefixes[i], p6->getFirstAddress().toText());
        EXPECT_EQ((80 + (i * 8)), p6->getLength());
    }
}

// Goal of this test is to verify the a whole prefix can be delegated and that
// a whole subnet can be delegated.
TEST_F(Dhcp6ParserTest, subnetAndPrefixDelegated) {

    ConstElementPtr x;

    // Define a single valid pd pool.
    string config =
        "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8:1::/64\","
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1::\", "
        "          \"prefix-len\": 64, "
        "          \"delegated-len\": 64"
        "        } ],"
        "\"valid-lifetime\": 4000 }"
        "] }";

    // Convert the JSON string into Elements.
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));

    // Verify that DHCP6 configuration processing succeeds.
    // Returned value must be non-empty ConstElementPtr to config result.
    // rcode should be 0 which indicates successful configuration processing.
    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    // Test that we can retrieve the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);

    ASSERT_TRUE(subnet);

    // Fetch the collection of PD pools.  It should have 1 entry.
    PoolCollection pc;
    ASSERT_NO_THROW(pc = subnet->getPools(Lease::TYPE_PD));
    EXPECT_EQ(1, pc.size());

    // Get a pointer to the pd pool instance, and verify its contents.
    Pool6Ptr p6;
    ASSERT_NO_THROW(p6 = boost::dynamic_pointer_cast<Pool6>(pc[0]));
    ASSERT_TRUE(p6);
    EXPECT_EQ("2001:db8:1::", p6->getFirstAddress().toText());
    EXPECT_EQ(64, p6->getLength());

    // prefix-len is not directly accessible after pool construction, so
    // verify that it was interpreted correctly by checking the last address
    // value.
    isc::asiolink::IOAddress prefixAddress("2001:db8:1::");
    EXPECT_EQ(lastAddrInPrefix(prefixAddress, 64), p6->getLastAddress());
}


// Goal of this test is check for proper handling of invalid prefix delegation
// pool configuration.  It uses an array of invalid configurations to check
// a variety of configuration errors.
TEST_F(Dhcp6ParserTest, invalidPdPools) {

    ConstElementPtr x;

    const char *config[] =  {
        // No prefix.
        "{ \"interfaces-config\": { },"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8:1::/64\","
        "    \"pd-pools\": ["
        "        { "
        "          \"prefix-len\": 64, "
        "          \"delegated-len\": 128"
        "        } ],"
        "\"valid-lifetime\": 4000 }"
        "] }",
        // No prefix-len.
        "{ \"interfaces-config\": { },"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8:1::/64\","
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1::\", "
        "          \"delegated-len\": 128"
        "        } ],"
        "\"valid-lifetime\": 4000 }"
        "] }",
        // No delegated-len.
        "{ \"interfaces-config\": { },"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8:1::/64\","
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1::\", "
        "          \"prefix-len\": 64 "
        "        } ],"
        "\"valid-lifetime\": 4000 }"
        "] }",
        // Delegated length is too short.
        "{ \"interfaces-config\": { },"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"subnet\": \"2001:db8:1::/64\","
        "    \"pd-pools\": ["
        "        { \"prefix\": \"2001:db8:1::\", "
        "          \"prefix-len\": 128, "
        "          \"delegated-len\": 64"
        "        } ],"
        "\"valid-lifetime\": 4000 }"
        "] }"
        };

    ElementPtr json;
    int num_msgs = sizeof(config)/sizeof(char*);
    for (int i = 0; i < num_msgs; i++) {
        // Convert JSON string to Elements.
        ASSERT_NO_THROW(json = Element::fromJSON(config[i]));

        // Configuration processing should fail without a throw.
        ASSERT_NO_THROW(x = configureDhcp6Server(srv_, json));

        // Returned value must be non-empty ConstElementPtr to config result.
        // rcode should be 1 which indicates configuration error.
        checkResult(x, 1);
        EXPECT_TRUE(errorContainsPosition(x, "<string>"));
    }
}

// The goal of this test is to check whether an option definition
// that defines an option carrying an IPv6 address can be created.
TEST_F(Dhcp6ParserTest, optionDefIpv6Address) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv6-address\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Verify that the option definition data is valid.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, def->getType());
}

// The goal of this test is to check whether an option definition
// that defines an option carrying a record of data fields can
// be created.
TEST_F(Dhcp6ParserTest, optionDefRecord) {

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
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
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
TEST_F(Dhcp6ParserTest, optionDefMultiple) {
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
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the option definitions do not exist yet.
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->
                 getCfgOptionDef()->get("isc", 100));
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->
                 getCfgOptionDef()->get("isc", 101));

    // Use the configuration string to create new option definitions.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
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

    // Check the second option definition we have created.
    OptionDefinitionPtr def2 = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 101);
    ASSERT_TRUE(def2);

    // Check the option data.
    EXPECT_EQ("foo-2", def2->getName());
    EXPECT_EQ(101, def2->getCode());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, def2->getType());
    EXPECT_FALSE(def2->getArrayType());
}

// The goal of this test is to verify that the duplicated option
// definition is not accepted.
TEST_F(Dhcp6ParserTest, optionDefDuplicate) {

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
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the option definition does not exist yet.
    ASSERT_FALSE(CfgMgr::instance().getStagingCfg()->
                 getCfgOptionDef()->get("isc", 100));

    // Use the configuration string to create new option definitions.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// The goal of this test is to verify that the option definition
// comprising an array of uint32 values can be created.
TEST_F(Dhcp6ParserTest, optionDefArray) {

    // Configuration string. Created option definition should
    // comprise an array of uint32 values.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": True,"
        "      \"space\": \"isc\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def->getType());
    EXPECT_TRUE(def->getArrayType());
}

// The purpose of this test to verify that encapsulated option
// space name may be specified.
TEST_F(Dhcp6ParserTest, optionDefEncapsulate) {

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
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
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
TEST_F(Dhcp6ParserTest, optionDefInvalidName) {
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
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that the option definition
/// with invalid type is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidType) {
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
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that the option definition
/// with invalid type is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidRecordType) {
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
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The goal of this test is to verify that the invalid encapsulated
/// option space name is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidEncapsulatedSpace) {
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
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The goal of this test is to verify that the encapsulated
/// option space name can't be specified for the option that
/// comprises an array of data fields.
TEST_F(Dhcp6ParserTest, optionDefEncapsulatedSpaceAndArray) {
    // Configuration string. The encapsulated option space
    // name is set to non-empty value and the array flag
    // is set.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": True,"
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"valid-space-name\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The goal of this test is to verify that the option may not
/// encapsulate option space it belongs to.
TEST_F(Dhcp6ParserTest, optionDefEncapsulateOwnSpace) {
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
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// The purpose of this test is to verify that it is not allowed
/// to override the standard option (that belongs to dhcp6 option
/// space and has its definition) and that it is allowed to define
/// option in the dhcp6 option space that has a code which is not
/// used by any of the standard options.
TEST_F(Dhcp6ParserTest, optionStandardDefOverride) {

    // Configuration string. The option code 100 is unassigned
    // so it can be used for a custom option definition in
    // dhcp6 option space.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"string\","
        "      \"space\": \"dhcp6\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    OptionDefinitionPtr def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("dhcp6", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("dhcp6", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_STRING_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());

    // The combination of option space and code is invalid. The 'dhcp6'
    // option space groups standard options and the code 3 is reserved
    // for one of them.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 3,"
        "      \"type\": \"string\","
        "      \"space\": \"dhcp6\""
        "  } ]"
        "}";
    json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    /// @todo The option 63 is a standard DHCPv6 option. However, at this point
    /// there is no definition for this option in libdhcp++, so it should be
    /// allowed to define it from the configuration interface. This test will
    /// have to be removed once definitions for remaining standard options are
    /// created.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"geolocation\","
        "      \"code\": 63,"
        "      \"type\": \"string\","
        "      \"space\": \"dhcp6\""
        "  } ]"
        "}";
    json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting success.
    checkResult(status, 0);

    def = CfgMgr::instance().getStagingCfg()->
        getCfgOptionDef()->get("dhcp6", 63);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("geolocation", def->getName());
    EXPECT_EQ(63, def->getCode());
    EXPECT_EQ(OPT_STRING_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());
}

// Goal of this test is to verify that global option
// data is configured for the subnet if the subnet
// configuration does not include options configuration.
TEST_F(Dhcp6ParserTest, optionDataDefaults) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"subscriber-id\","
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": False"
        " },"
        " {"
        "    \"name\": \"preference\","
        "    \"data\": \"01\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    OptionContainerPtr options = subnet->getCfgOption()->getAll("dhcp6");
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(D6O_SUBSCRIBER_ID);
    // Expect single option with the code equal to 38.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t subid_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, D6O_SUBSCRIBER_ID, subid_expected,
               sizeof(subid_expected));

    range = idx.equal_range(D6O_PREFERENCE);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t pref_expected[] = {
        0x01
    };
    testOption(*range.first, D6O_PREFERENCE, pref_expected,
               sizeof(pref_expected));

    // Check that options with other option codes are not returned.
    for (uint16_t code = 47; code < 57; ++code) {
        range = idx.equal_range(code);
        EXPECT_EQ(0, std::distance(range.first, range.second));
    }
}

/// The goal of this test is to verify that two options having the same
/// option code can be added to different option spaces.
TEST_F(Dhcp6ParserTest, optionDataTwoSpaces) {

    // This configuration string is to configure two options
    // sharing the code 56 and having different definitions
    // and belonging to the different option spaces.
    // The option definition must be provided for the
    // option that belongs to the 'isc' option space.
    // The definition is not required for the option that
    // belongs to the 'dhcp6' option space as it is the
    // standard option.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"subscriber-id\","
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": False"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"data\": \"1234\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 38,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Options should be now available for the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    // Try to get the option from the space dhcp6.
    OptionDescriptor desc1 = subnet->getCfgOption()->get("dhcp6", 38);
    ASSERT_TRUE(desc1.option_);
    EXPECT_EQ(38, desc1.option_->getType());
    // Try to get the option from the space isc.
    OptionDescriptor desc2 = subnet->getCfgOption()->get("isc", 38);
    ASSERT_TRUE(desc2.option_);
    EXPECT_EQ(38, desc1.option_->getType());
    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    OptionDescriptor desc3 = subnet->getCfgOption()->get("non-existing", 38);
    ASSERT_FALSE(desc3.option_);
}

// The goal of this test is to verify that it is possible to
// encapsulate option space containing some options with
// another option. In this test we create base option that
// encapsulates option space 'isc' that comprises two other
// options. Also, for all options their definitions are
// created.
TEST_F(Dhcp6ParserTest, optionDataEncapsulate) {

    // @todo DHCP configurations has many dependencies between
    // parameters. First of all, configuration for subnet is
    // inherited from the global values. Thus subnet has to be
    // configured when all global values have been configured.
    // Also, an option can encapsulate another option only
    // if the latter has been configured. For this reason in this
    // test we created two-stage configuration where first we
    // created options that belong to encapsulated option space.
    // In the second stage we add the base option. Also, the Subnet
    // object is configured in the second stage so it is created
    // at the very end (when all other parameters are configured).

    // Starting stage 1. Configure sub-options and their definitions.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
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
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"isc\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    CfgMgr::instance().clear();

    // Stage 2. Configure base option and a subnet. Please note that
    // the configuration from the stage 2 is repeated because BIND
    // configuration manager sends whole configuration for the lists
    // where at least one element is being modified or added.
    config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000,"
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
        "    \"code\": 100,"
        "    \"type\": \"uint8\","
        "    \"space\": \"dhcp6\","
        "    \"encapsulate\": \"isc\""
        "},"
        "{"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"space\": \"isc\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"isc\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";


    json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Get the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);

    // We should have one option available.
    OptionContainerPtr options = subnet->getCfgOption()->getAll("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the option.
    OptionDescriptor desc = subnet->getCfgOption()->get("dhcp6", 100);
    EXPECT_TRUE(desc.option_);
    EXPECT_EQ(100, desc.option_->getType());

    // This opton should comprise two sub-options.
    // Onf of them is 'foo' with code 110.
    OptionPtr option_foo = desc.option_->getOption(110);
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(110, option_foo->getType());

    // ...another one 'foo2' with code 111.
    OptionPtr option_foo2 = desc.option_->getOption(111);
    ASSERT_TRUE(option_foo2);
    EXPECT_EQ(111, option_foo2->getType());
}

// Goal of this test is to verify options configuration
// for multiple subnets.
TEST_F(Dhcp6ParserTest, optionDataInMultipleSubnets) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"subscriber-id\","
        "          \"data\": \"0102030405060708090A\","
        "          \"csv-format\": False"
        "        } ]"
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"user-class\","
        "          \"data\": \"FFFEFDFCFB\","
        "          \"csv-format\": False"
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    Subnet6Ptr subnet1 = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet1);
    OptionContainerPtr options1 = subnet1->getCfgOption()->getAll("dhcp6");
    ASSERT_EQ(1, options1->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx1 = options1->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range1 =
        idx1.equal_range(D6O_SUBSCRIBER_ID);
    // Expect single option with the code equal to 38.
    ASSERT_EQ(1, std::distance(range1.first, range1.second));
    const uint8_t subid_expected[] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range1.first, D6O_SUBSCRIBER_ID, subid_expected,
               sizeof(subid_expected));

    // Test another subnet in the same way.
    Subnet6Ptr subnet2 = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:2::4"), classify_);
    ASSERT_TRUE(subnet2);
    OptionContainerPtr options2 = subnet2->getCfgOption()->getAll("dhcp6");
    ASSERT_EQ(1, options2->size());

    const OptionContainerTypeIndex& idx2 = options2->get<1>();
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range2 =
        idx2.equal_range(D6O_USER_CLASS);
    ASSERT_EQ(1, std::distance(range2.first, range2.second));

    const uint8_t user_class_expected[] = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB
    };
    testOption(*range2.first, D6O_USER_CLASS, user_class_expected,
               sizeof(user_class_expected));
}

// The goal of this test is to check that the option carrying a boolean
// value can be configured using one of the values: "true", "false", "0"
// or "1".
TEST_F(Dhcp6ParserTest, optionDataBoolean) {
    // Create configuration. Use standard option 1000.
    std::map<std::string, std::string> params;
    params["name"] = "bool-option";
    params["space"] = "dhcp6";
    params["code"] = "1000";
    params["data"] = "true";
    params["csv-format"] = "true";

    std::string config = createConfigWithOption(params);
    ASSERT_TRUE(executeConfiguration(config, "parse configuration with a"
                                     " boolean value"));

    // The subnet should now hold one option with the code 1000.
    OptionDescriptor desc =
        getOptionFromSubnet(IOAddress("2001:db8:1::5"), 1000);
    ASSERT_TRUE(desc.option_);

    // This option should be set to "true", represented as 0x1 in the option
    // buffer.
    uint8_t expected_option_data[] = {
        0x1
    };
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // Configure the option with the "1" value. This should have the same
    // effect as if "true" was specified.
    params["data"] = "1";
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // The value of "1" with a few leading zeros should work too.
    params["data"] = "00001";
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // Configure the option with the "false" value.
    params["data"] = "false";
    // The option buffer should now hold the value of 0.
    expected_option_data[0] = 0;
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // Specifying "0" should have the same effect as "false".
    params["data"] = "0";
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // The same effect should be for multiple 0 chars.
    params["data"] = "00000";
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // Bogus values should not be accepted.
    params["data"] = "bugus";
    testInvalidOptionParam(params);

    params["data"] = "2";
    testInvalidOptionParam(params);

    // Now let's test that it is possible to use binary format.
    params["data"] = "0";
    params["csv-format"] = "false";
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // The binary 1 should work as well.
    params["data"] = "1";
    expected_option_data[0] = 1;
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

    // As well as an even number of digits.
    params["data"] = "01";
    testConfiguration(params, 1000, expected_option_data,
                      sizeof(expected_option_data));

}

// Verify that empty option name is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionNameEmpty) {
    // Empty option names not allowed.
    testInvalidOptionParam("", "name");
}

// Verify that empty option name with spaces is rejected
// in the configuration.
TEST_F(Dhcp6ParserTest, optionNameSpaces) {
    // Spaces in option names not allowed.
    testInvalidOptionParam("option foo", "name");
}

// Verify that negative option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeNegative) {
    // Check negative option code -4. This should fail too.
    testInvalidOptionParam("-4", "code");
}

// Verify that out of bounds option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeNonUint16) {
    // The valid option codes are uint16_t values so passing
    // uint16_t maximum value incremented by 1 should result
    // in failure.
    testInvalidOptionParam("65536", "code");
}

// Verify that out of bounds option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeHighNonUint16) {
    // Another check for uint16_t overflow but this time
    // let's pass even greater option code value.
    testInvalidOptionParam("70000", "code");
}

// Verify that zero option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeZero) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0", "code");
}

// Verify that option data which contains non hexadecimal characters
// is rejected by the configuration.
TEST_F(Dhcp6ParserTest, optionDataInvalidChar) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("01020R", "data");
}

// Verify that option data containing '0x' prefix is rejected
// by the configuration.
TEST_F(Dhcp6ParserTest, optionDataUnexpectedPrefix) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0x0102", "data");
}

// Verify that either lower or upper case characters are allowed
// to specify the option data.
TEST_F(Dhcp6ParserTest, optionDataLowerCase) {
    ConstElementPtr x;
    std::string config = createConfigWithOption("0a0b0C0D", "data");
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    OptionContainerPtr options = subnet->getCfgOption()->getAll("dhcp6");
    ASSERT_EQ(1, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(D6O_SUBSCRIBER_ID);
    // Expect single option with the code equal to 38.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t subid_expected[] = {
        0x0A, 0x0B, 0x0C, 0x0D
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, D6O_SUBSCRIBER_ID, subid_expected,
               sizeof(subid_expected));
}

// Verify that specific option object is returned for standard
// option which has dedicated option class derived from Option.
TEST_F(Dhcp6ParserTest, stdOptionData) {
    ConstElementPtr x;
    std::map<std::string, std::string> params;
    params["name"] = "ia-na";
    params["space"] = "dhcp6";
    // Option code 3 means OPTION_IA_NA.
    params["code"] = "3";
    params["data"] = "12345, 6789, 1516";
    params["csv-format"] = "True";

    std::string config = createConfigWithOption(params);
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);
    OptionContainerPtr options = subnet->getCfgOption()->getAll("dhcp6");
    ASSERT_EQ(1, options->size());

    // Get the search index. Index #1 is to search using option code.
    const OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<OptionContainerTypeIndex::const_iterator,
              OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(D6O_IA_NA);
    // Expect single option with the code equal to IA_NA option code.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // The actual pointer to the option is held in the option field
    // in the structure returned.
    OptionPtr option = range.first->option_;
    ASSERT_TRUE(option);
    // Option object returned for here is expected to be Option6IA
    // which is derived from Option. This class is dedicated to
    // represent standard option IA_NA.
    boost::shared_ptr<Option6IA> optionIA =
        boost::dynamic_pointer_cast<Option6IA>(option);
    // If cast is unsuccessful than option returned was of a
    // different type than Option6IA. This is wrong.
    ASSERT_TRUE(optionIA);
    // If cast was successful we may use accessors exposed by
    // Option6IA to validate that the content of this option
    // has been set correctly.
    EXPECT_EQ(12345, optionIA->getIAID());
    EXPECT_EQ(6789, optionIA->getT1());
    EXPECT_EQ(1516, optionIA->getT2());
}

// This test checks if vendor options can be specified in the config file
// (in hex format), and later retrieved from configured subnet
TEST_F(Dhcp6ParserTest, vendorOptionsHex) {

    // This configuration string is to configure two options
    // sharing the code 1 and belonging to the different vendor spaces.
    // (different vendor-id values).
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"option-one\","
        "    \"space\": \"vendor-4491\","
        "    \"code\": 100,"
        "    \"data\": \"ABCDEF0105\","
        "    \"csv-format\": False"
        " },"
        " {"
        "    \"name\": \"option-two\","
        "    \"space\": \"vendor-1234\","
        "    \"code\": 100,"
        "    \"data\": \"1234\","
        "    \"csv-format\": False"
        " } ],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Options should be now available for the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);

    // Try to get the option from the vendor space 4491
    OptionDescriptor desc1 = subnet->getCfgOption()->get(4491, 100);
    ASSERT_TRUE(desc1.option_);
    EXPECT_EQ(100, desc1.option_->getType());
    // Try to get the option from the vendor space 1234
    OptionDescriptor desc2 = subnet->getCfgOption()->get(1234, 100);
    ASSERT_TRUE(desc2.option_);
    EXPECT_EQ(100, desc1.option_->getType());

    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    OptionDescriptor desc3 = subnet->getCfgOption()->get(5678, 38);
    ASSERT_FALSE(desc3.option_);
}

// This test checks if vendor options can be specified in the config file,
// (in csv format), and later retrieved from configured subnet
TEST_F(Dhcp6ParserTest, vendorOptionsCsv) {

    // This configuration string is to configure two options
    // sharing the code 1 and belonging to the different vendor spaces.
    // (different vendor-id values).
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
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
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Options should be now available for the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);

    // Try to get the option from the vendor space 4491
    OptionDescriptor desc1 = subnet->getCfgOption()->get(4491, 100);
    ASSERT_TRUE(desc1.option_);
    EXPECT_EQ(100, desc1.option_->getType());

    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    OptionDescriptor desc2 = subnet->getCfgOption()->get(5678, 100);
    ASSERT_FALSE(desc2.option_);
}

/// @todo add tests similar to vendorOptionsCsv and vendorOptionsHex, but for
///       vendor options defined in a subnet.

// The goal of this test is to verify that the standard option can
// be configured to encapsulate multiple other options.
/// @todo This test is currently disabled because it relies on the option
/// 17 which is treated differently than all other options. There are no
/// other standard options used by Kea which would encapsulate other
/// options and for which values could be configured here.
TEST_F(Dhcp6ParserTest, DISABLED_stdOptionDataEncapsulate) {

    // The configuration is two stage process in this test.
    // In the first stage we create definitions of suboptions
    // that we will add to the base option.
    // Let's create some dummy options: foo and foo2.
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-opts-space\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-opts-space\","
        "    \"data\": \"192.168.2.1\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"space\": \"vendor-opts-space\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"vendor-opts-space\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
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
    config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"vendor-opts\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-opts-space\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-opts-space\","
        "    \"data\": \"192.168.2.1\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"space\": \"vendor-opts-space\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"vendor-opts-space\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";


    json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Get the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::5"), classify_);
    ASSERT_TRUE(subnet);

    // We should have one option available.
    OptionContainerPtr options = subnet->getCfgOption()->getAll("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the option.
    OptionDescriptor desc = subnet->getCfgOption()->get("dhcp6", D6O_VENDOR_OPTS);
    EXPECT_TRUE(desc.option_);
    EXPECT_EQ(D6O_VENDOR_OPTS, desc.option_->getType());

    // Option with the code 110 should be added as a sub-option.
    OptionPtr option_foo = desc.option_->getOption(110);
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(110, option_foo->getType());
    // This option comprises a single uint32_t value thus it is
    // represented by OptionInt<uint32_t> class. Let's get the
    // object of this type.
    boost::shared_ptr<OptionInt<uint32_t> > option_foo_uint32 =
        boost::dynamic_pointer_cast<OptionInt<uint32_t> >(option_foo);
    ASSERT_TRUE(option_foo_uint32);
    // Validate the value according to the configuration.
    EXPECT_EQ(1234, option_foo_uint32->getValue());

    // Option with the code 111 should be added as a sub-option.
    OptionPtr option_foo2 = desc.option_->getOption(111);
    ASSERT_TRUE(option_foo2);
    EXPECT_EQ(111, option_foo2->getType());
    // This option comprises the IPV4 address. Such option is
    // represented by OptionCustom object.
    OptionCustomPtr option_foo2_v4 =
        boost::dynamic_pointer_cast<OptionCustom>(option_foo2);
    ASSERT_TRUE(option_foo2_v4);
    // Get the IP address carried by this option and validate it.
    EXPECT_EQ("192.168.2.1", option_foo2_v4->readAddress().toText());

    // Option with the code 112 should not be added.
    EXPECT_FALSE(desc.option_->getOption(112));
}

// Tests of the hooks libraries configuration.  All tests have the pre-
// condition (checked in the test fixture's SetUp() method) that no hooks
// libraries are loaded at the start of the tests.


// Helper function to return a configuration containing an arbitrary number
// of hooks libraries.
std::string
buildHooksLibrariesConfig(const std::vector<std::string>& libraries) {
    const string quote("\"");

    // Create the first part of the configuration string.
    string config =
        "{ \"interfaces-config\": { },"
           "\"hooks-libraries\": [";

    // Append the libraries (separated by commas if needed)
    for (int i = 0; i < libraries.size(); ++i) {
        if (i > 0) {
            config += string(", ");
        }
        config += (quote + libraries[i] + quote);
    }

    // Append the remainder of the configuration.
    config += string(
        "],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-opts-space\","
        "    \"data\": \"1234\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-opts-space\","
        "    \"data\": \"192.168.2.1\""
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"space\": \"vendor-opts-space\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"space\": \"vendor-opts-space\""
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
TEST_F(Dhcp6ParserTest, NoHooksLibraries) {
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
TEST_F(Dhcp6ParserTest, InvalidLibrary) {
    // Parse a configuration containing a failing library.
    string config = buildHooksLibrariesConfig(NOT_PRESENT_LIBRARY);

    ConstElementPtr status;
    ElementPtr json = Element::fromJSON(config);
    ASSERT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // The status object must not be NULL
    ASSERT_TRUE(status);

    // Returned value should not be 0
    comment_ = parseAnswer(rcode_, status);
    EXPECT_NE(0, rcode_);
}

// Verify the configuration of hooks libraries with two being specified.
TEST_F(Dhcp6ParserTest, LibrariesSpecified) {
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


// This test verifies that it is possible to select subset of interfaces on
// which server should listen.
TEST_F(Dhcp6ParserTest, selectedInterfaces) {
    IfaceMgrTestConfig test_config(true);

    // Make sure there is no garbage interface configuration in the CfgMgr.
    ASSERT_FALSE(test_config.socketOpen("eth0", AF_INET6));
    ASSERT_FALSE(test_config.socketOpen("eth1", AF_INET6));

    ConstElementPtr status;

    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"eth0\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000 }";


    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value must be 1 (values error)
    // as the pool does not belong to that subnet
    checkResult(status, 0);

    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET6, 10000);

    // eth0 and eth1 were explicitly selected. eth2 was not.
    EXPECT_TRUE(test_config.socketOpen("eth0", AF_INET6));
    EXPECT_FALSE(test_config.socketOpen("eth1", AF_INET6));
}

// This test verifies that it is possible to configure the server to listen on
// all interfaces.
TEST_F(Dhcp6ParserTest, allInterfaces) {
    IfaceMgrTestConfig test_config(true);

    ASSERT_FALSE(test_config.socketOpen("eth0", AF_INET6));
    ASSERT_FALSE(test_config.socketOpen("eth1", AF_INET6));

    ConstElementPtr status;

    // This configuration specifies two interfaces on which server should listen
    // but also includes '*'. This keyword switches server into the
    // mode when it listens on all interfaces regardless of what interface names
    // were specified in the "interfaces" parameter.
    string config = "{ \"interfaces-config\": {"
        "  \"interfaces\": [ \"eth0\", \"eth1\", \"*\" ]"
        "},"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"valid-lifetime\": 4000 }";


    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    checkResult(status, 0);

    CfgMgr::instance().getStagingCfg()->getCfgIface()->openSockets(AF_INET6, 10000);

    // All interfaces should be now active.
    EXPECT_TRUE(test_config.socketOpen("eth0", AF_INET6));
    EXPECT_TRUE(test_config.socketOpen("eth1", AF_INET6));
}


// This test checks if it is possible to specify relay information
TEST_F(Dhcp6ParserTest, subnetRelayInfo) {

    ConstElementPtr status;

    // A config with relay information.
    string config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ],"
        "    \"relay\": { "
        "        \"ip-address\": \"2001:db8:1::abcd\""
        "    },"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"preferred-lifetime\": 3000, "
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet6Ptr subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->
        selectSubnet(IOAddress("2001:db8:1::1"), classify_);
    ASSERT_TRUE(subnet);
    EXPECT_EQ("2001:db8:1::abcd", subnet->getRelayInfo().addr_.toText());
}

// Goal of this test is to verify that multiple subnets can be configured
// with defined client classes.
TEST_F(Dhcp6ParserTest, classifySubnets) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"client-class\": \"alpha\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/80\" } ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"client-class\": \"beta\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/80\" } ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"client-class\": \"gamma\" "
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/80\" } ],"
        "    \"subnet\": \"2001:db8:4::/64\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    const Subnet6Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll();
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

// This test checks the ability of the server to parse a configuration
// containing a full, valid dhcp-ddns (D2ClientConfig) entry.
TEST_F(Dhcp6ParserTest, d2ClientConfig) {
    ConstElementPtr status;

    // Verify that the D2 configuraiton can be fetched and is set to disabled.
    D2ClientConfigPtr d2_client_config = CfgMgr::instance().getD2ClientConfig();
    EXPECT_FALSE(d2_client_config->getEnableUpdates());

    // Verify that the convenience method agrees.
    ASSERT_FALSE(CfgMgr::instance().ddnsEnabled());

    string config_str = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ], "
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"3001::1\", "
        "     \"server-port\" : 777, "
        "     \"sender-ip\" : \"3001::2\", "
        "     \"sender-port\" : 778, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"always-include-fqdn\" : true, "
        "     \"allow-client-update\" : true, "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" },"
        "\"valid-lifetime\": 4000 }";

    // Convert the JSON string to configuration elements.
    ElementPtr config;
    ASSERT_NO_THROW(config = Element::fromJSON(config_str));

    // Pass the configuration in for parsing.
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, config));

    // check if returned status is OK
    checkResult(status, 0);

    // Verify that DHCP-DDNS updating is enabled.
    EXPECT_TRUE(CfgMgr::instance().ddnsEnabled());

    // Verify that the D2 configuration can be retrieved.
    d2_client_config = CfgMgr::instance().getD2ClientConfig();
    ASSERT_TRUE(d2_client_config);

    // Verify that the configuration values are correct.
    EXPECT_TRUE(d2_client_config->getEnableUpdates());
    EXPECT_EQ("3001::1", d2_client_config->getServerIp().toText());
    EXPECT_EQ(777, d2_client_config->getServerPort());
    EXPECT_EQ("3001::2", d2_client_config->getSenderIp().toText());
    EXPECT_EQ(778, d2_client_config->getSenderPort());
    EXPECT_EQ(2048, d2_client_config->getMaxQueueSize());
    EXPECT_EQ(dhcp_ddns::NCR_UDP, d2_client_config->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::FMT_JSON, d2_client_config->getNcrFormat());
    EXPECT_TRUE(d2_client_config->getAlwaysIncludeFqdn());
    EXPECT_TRUE(d2_client_config->getOverrideNoUpdate());
    EXPECT_TRUE(d2_client_config->getOverrideClientUpdate());
    EXPECT_TRUE(d2_client_config->getReplaceClientName());
    EXPECT_EQ("test.prefix", d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("test.suffix.", d2_client_config->getQualifyingSuffix());
}

// This test checks the ability of the server to handle a configuration
// containing an invalid dhcp-ddns (D2ClientConfig) entry.
TEST_F(Dhcp6ParserTest, invalidD2ClientConfig) {
    ConstElementPtr status;

    // Configuration string with an invalid D2 client config,
    // "server-ip" is invalid.
    string config_str = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ], "
        " \"dhcp-ddns\" : {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"bogus-value\", "
        "     \"server-port\" : 5301, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"always-include-fqdn\" : true, "
        "     \"allow-client-update\" : true, "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" },"
        "\"valid-lifetime\": 4000 }";

    // Convert the JSON string to configuration elements.
    ElementPtr config;
    ASSERT_NO_THROW(config = Element::fromJSON(config_str));

    // Configuration should not throw, but should fail.
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, config));

    // check if returned status is failed.
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));

    // Verify that the D2 configuraiton can be fetched and is set to disabled.
    D2ClientConfigPtr d2_client_config = CfgMgr::instance().getD2ClientConfig();
    EXPECT_FALSE(d2_client_config->getEnableUpdates());

    // Verify that the convenience method agrees.
    ASSERT_FALSE(CfgMgr::instance().ddnsEnabled());
}

/// @brief Checks if the reservation is in the range of reservations.
///
/// @param resrv Reservation to be searched for.
/// @param range Range of reservations returned by the @c Host object
/// in which the reservation will be searched.
bool reservationExists(const IPv6Resrv& resrv, const IPv6ResrvRange& range) {
    for (IPv6ResrvIterator it = range.first; it != range.second;
         ++it) {
        if (resrv == it->second) {
            return (true);
        }
    }
    return (false);
}

// This test verifies that the host reservations can be specified for
// respective IPv6 subnets.
TEST_F(Dhcp6ParserTest, reservations) {
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/80\" } ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"id\": 123,"
        "    \"reservations\": ["
        "    ]"
        " },"
        " {"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"01:02:03:04:05:06:07:08:09:0A\","
        "        \"ip-addresses\": [ \"2001:db8:2::1234\" ],"
        "        \"hostname\": \"\""
        "      },"
        "      {"
        "        \"hw-address\": \"01:02:03:04:05:06\","
        "        \"ip-addresses\": [ \"2001:db8:2::abcd\" ],"
        "        \"hostname\": \"\""
        "      }"
        "    ],"
        "    \"pools\": [ ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"id\": 234"
        " },"
        " {"
        "    \"pools\": [ ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"0A:09:08:07:06:05:04:03:02:01\","
        "        \"prefixes\": [ \"2001:db8:3:2::/96\" ],"
        "        \"hostname\": \"\""
        "      },"
        "      {"
        "        \"hw-address\": \"06:05:04:03:02:01\","
        "        \"prefixes\": [ \"2001:db8:3:1::/96\" ],"
        "        \"hostname\": \"\""
        "      }"
        "    ]"
        " } "
        "], "
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 0);

    // Make sure all subnets have been successfully configured. There is no
    // need to sanity check the subnet properties because it should have
    // been already tested by other tests.
    const Subnet6Collection* subnets =
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll();
    ASSERT_TRUE(subnets);
    ASSERT_EQ(3, subnets->size());

    // Hosts configuration must be available.
    CfgHostsPtr hosts_cfg = CfgMgr::instance().getStagingCfg()->getCfgHosts();
    ASSERT_TRUE(hosts_cfg);

    // Let's create an object holding hardware address of the host having
    // a reservation in the subnet having id of 234. For simplicity the
    // address is a collection of numbers from 1 to 6.
    std::vector<uint8_t> hwaddr_vec;
    for (int i = 1; i < 7; ++i) {
        hwaddr_vec.push_back(static_cast<uint8_t>(i));
    }
    HWAddrPtr hwaddr(new HWAddr(hwaddr_vec, HTYPE_ETHER));
    // Retrieve the reservation and sanity check the address reserved.
    ConstHostPtr host = hosts_cfg->get6(234, DuidPtr(), hwaddr);
    ASSERT_TRUE(host);
    IPv6ResrvRange resrv = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(1, std::distance(resrv.first, resrv.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:2::abcd")),
                                  resrv));
    // This reservation should be solely assigned to the subnet 234,
    // and not to other two.
    EXPECT_FALSE(hosts_cfg->get6(123, DuidPtr(), hwaddr));
    EXPECT_FALSE(hosts_cfg->get6(542, DuidPtr(), hwaddr));

    // Do the same test for the DUID based reservation.
    std::vector<uint8_t> duid_vec;
    for (int i = 1; i < 0xb; ++i) {
        duid_vec.push_back(static_cast<uint8_t>(i));
    }
    DuidPtr duid(new DUID(duid_vec));
    host = hosts_cfg->get6(234, duid);
    ASSERT_TRUE(host);
    resrv = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(1, std::distance(resrv.first, resrv.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:2::1234")),
                                  resrv));
    EXPECT_FALSE(hosts_cfg->get6(123, duid));
    EXPECT_FALSE(hosts_cfg->get6(542, duid));

    // The HW address used for one of the reservations in the subnet 542
    // consists of numbers from 6 to 1. So, let's just reverse the order
    // of the address from the previous test.
    hwaddr->hwaddr_.assign(hwaddr_vec.rbegin(), hwaddr_vec.rend());
    host = hosts_cfg->get6(542, DuidPtr(), hwaddr);
    EXPECT_TRUE(host);
    resrv = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(resrv.first, resrv.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                            IOAddress("2001:db8:3:1::"),
                                            96), resrv));

    // This reservation must not belong to other subnets.
    EXPECT_FALSE(hosts_cfg->get6(123, DuidPtr(), hwaddr));
    EXPECT_FALSE(hosts_cfg->get6(234, DuidPtr(), hwaddr));

    // Repeat the test for the DUID based reservation in this subnet.
    duid.reset(new DUID(std::vector<uint8_t>(duid_vec.rbegin(),
                                             duid_vec.rend())));
    host = hosts_cfg->get6(542, duid);
    ASSERT_TRUE(host);
    resrv = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(1, std::distance(resrv.first, resrv.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                            IOAddress("2001:db8:3:2::"),
                                            96), resrv));

    EXPECT_FALSE(hosts_cfg->get6(123, duid));
    EXPECT_FALSE(hosts_cfg->get6(234, duid));
}

// This test verifies that the bogus host reservation would trigger a
// server configuration error.
TEST_F(Dhcp6ParserTest, reservationBogus) {
    // Case 1: misspelled "duid" parameter.
    ConstElementPtr x;
    string config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"pools\": [ ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"dui\": \"0A:09:08:07:06:05:04:03:02:01\","
        "        \"prefixes\": [ \"2001:db8:3:2::/96\" ],"
        "        \"hostname\": \"\""
        "      }"
        "    ]"
        " } "
        "], "
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 1);

    // Case 2: DUID and HW Address both specified.
    config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"pools\": [ ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"hw-address\": \"01:02:03:04:05:06\","
        "        \"duid\": \"0A:09:08:07:06:05:04:03:02:01\","
        "        \"prefixes\": [ \"2001:db8:3:2::/96\" ],"
        "        \"hostname\": \"\""
        "      }"
        "    ]"
        " } "
        "], "
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000 }";

    json = Element::fromJSON(config);

    // Remove existing configuration, if any.
    CfgMgr::instance().clear();

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 1);

    // Case 3: Neither ip address nor hostname specified.
    config = "{ " + genIfaceConfig() + ","
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"pools\": [ ],"
        "    \"subnet\": \"2001:db8:3::/64\", "
        "    \"id\": 542,"
        "    \"reservations\": ["
        "      {"
        "        \"duid\": \"0A:09:08:07:06:05:04:03:02:01\""
        "      }"
        "    ]"
        " } "
        "], "
        "\"preferred-lifetime\": 3000,"
        "\"valid-lifetime\": 4000 }";

    json = Element::fromJSON(config);

    // Remove existing configuration, if any.
    CfgMgr::instance().clear();

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    checkResult(x, 1);

}

/// The goal of this test is to verify that configuration can include
/// MAC/Hardware sources. This test also checks if the aliases are
/// handled properly (rfc6939 = client-addr-relay, rfc4649 = remote-id,
/// rfc4580 = subscriber-id).
TEST_F(Dhcp6ParserTest, macSources) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
        Element::fromJSON("{ " + genIfaceConfig() + ","
                          "\"mac-sources\": [ \"rfc6939\", \"rfc4649\", \"rfc4580\","
                          "\"client-link-addr-option\", \"remote-id\", \"subscriber-id\"],"
                          "\"preferred-lifetime\": 3000,"
                          "\"rebind-timer\": 2000, "
                          "\"renew-timer\": 1000, "
                          "\"subnet6\": [  ], "
                          "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);

    CfgMACSources mac_sources = CfgMgr::instance().getStagingCfg()->getMACSources().get();
    ASSERT_EQ(6, mac_sources.size());
    // Let's check the aliases. They should be recognized to their base methods.
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION, mac_sources[0]);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_REMOTE_ID, mac_sources[1]);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID, mac_sources[2]);

    // Let's check if the actual methods are recognized properly.
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION, mac_sources[3]);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_REMOTE_ID, mac_sources[4]);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID, mac_sources[5]);
}

/// The goal of this test is to verify that MAC sources configuration can be
/// empty.
TEST_F(Dhcp6ParserTest, macSourcesEmpty) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
                    Element::fromJSON("{ " + genIfaceConfig() + ","
                                      "\"mac-sources\": [ ],"
                                      "\"preferred-lifetime\": 3000,"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet6\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);

    CfgMACSources mac_sources = CfgMgr::instance().getStagingCfg()->getMACSources().get();
    EXPECT_EQ(0, mac_sources.size());
}

/// The goal of this test is to verify that MAC sources configuration can
/// only use valid parameters.
TEST_F(Dhcp6ParserTest, macSourcesBogus) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
                    Element::fromJSON("{ " + genIfaceConfig() + ","
                                      "\"mac-sources\": [ \"from-wire\" ],"
                                      "\"preferred-lifetime\": 3000,"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet6\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 1 (failure)
    checkResult(status, 1);
}

/// The goal of this test is to verify that Host Reservation modes can be
/// specified on a per-subnet basis.
TEST_F(Dhcp6ParserTest, hostReservationPerSubnet) {

    /// - Configuration:
    ///   - only addresses (no prefixes)
    ///   - 4 subnets with:
    ///       - 2001:db8:1::/64 (all reservations enabled)
    ///       - 2001:db8:2::/64 (out-of-pool reservations)
    ///       - 2001:db8:3::/64 (reservations disabled)
    ///       - 2001:db8:3::/64 (reservations not specified)
    const char* HR_CONFIG =
        "{"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"reservation-mode\": \"all\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ],"
        "    \"subnet\": \"2001:db8:2::/48\", "
        "    \"reservation-mode\": \"out-of-pool\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:3::/64\" } ],"
        "    \"subnet\": \"2001:db8:3::/48\", "
        "    \"reservation-mode\": \"disabled\""
        " },"
        " {"
        "    \"pools\": [ { \"pool\": \"2001:db8:4::/64\" } ],"
        "    \"subnet\": \"2001:db8:4::/48\" "
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
                    Element::fromJSON(HR_CONFIG)));

    // returned value should be 0 (success)
    checkResult(status, 0);
    CfgMgr::instance().commit();

    // Let's get all subnets and check that there are 4 of them.
    ConstCfgSubnets6Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
    ASSERT_TRUE(subnets);
    const Subnet6Collection* subnet_col = subnets->getAll();
    ASSERT_EQ(4, subnet_col->size()); // We expect 4 subnets

    // Let's check if the parsed subnets have correct HR modes.

    // Subnet 1
    Subnet6Ptr subnet;
    subnet = subnets->selectSubnet(IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Subnet::HR_ALL, subnet->getHostReservationMode());

    // Subnet 2
    subnet = subnets->selectSubnet(IOAddress("2001:db8:2::1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Subnet::HR_OUT_OF_POOL, subnet->getHostReservationMode());

    // Subnet 3
    subnet = subnets->selectSubnet(IOAddress("2001:db8:3::1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Subnet::HR_DISABLED, subnet->getHostReservationMode());

    // Subnet 4
    subnet = subnets->selectSubnet(IOAddress("2001:db8:4::1"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(Subnet::HR_ALL, subnet->getHostReservationMode());
}

/// The goal of this test is to verify that configuration can include
/// Relay Supplied options (specified as numbers).
TEST_F(Dhcp6ParserTest, rsooNumbers) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
        Element::fromJSON("{ " + genIfaceConfig() + ","
                          "\"relay-supplied-options\": [ \"10\", \"20\", \"30\" ],"
                          "\"preferred-lifetime\": 3000,"
                          "\"rebind-timer\": 2000, "
                          "\"renew-timer\": 1000, "
                          "\"subnet6\": [  ], "
                          "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);

    // The following codes should be enabled now
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()->enabled(10));
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()->enabled(20));
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()->enabled(30));

    // This option is on the IANA list, so it should be allowed all the time
    // (http://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml)
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                ->enabled(D6O_ERP_LOCAL_DOMAIN_NAME));

    // Those options are not enabled
    EXPECT_FALSE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()->enabled(25));
    EXPECT_FALSE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()->enabled(1));
}

/// The goal of this test is to verify that configuration can include
/// Relay Supplied options (specified as names).
TEST_F(Dhcp6ParserTest, rsooNames) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
        Element::fromJSON("{ " + genIfaceConfig() + ","
                          "\"relay-supplied-options\": [ \"dns-servers\", \"remote-id\" ],"
                          "\"preferred-lifetime\": 3000,"
                          "\"rebind-timer\": 2000, "
                          "\"renew-timer\": 1000, "
                          "\"subnet6\": [  ], "
                          "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);

    for (uint16_t code = 0; code < D6O_NAME_SERVERS; ++code) {
        EXPECT_FALSE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                     ->enabled(code)) << " for option code " << code;
    }

    // The following code should be enabled now
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                ->enabled(D6O_NAME_SERVERS));

    for (uint16_t code = D6O_NAME_SERVERS + 1; code < D6O_REMOTE_ID; ++code) {
        EXPECT_FALSE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                     ->enabled(code)) << " for option code " << code;
    }

    // Check remote-id. It should be enabled.
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                ->enabled(D6O_REMOTE_ID));
    for (uint16_t code = D6O_REMOTE_ID + 1; code < D6O_ERP_LOCAL_DOMAIN_NAME; ++code) {
        EXPECT_FALSE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                     ->enabled(code)) << " for option code " << code;
    }

    // This option is on the IANA list, so it should be allowed all the time
    // (http://www.iana.org/assignments/dhcpv6-parameters/dhcpv6-parameters.xhtml)
    EXPECT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                ->enabled(D6O_ERP_LOCAL_DOMAIN_NAME));

    for (uint16_t code = D6O_ERP_LOCAL_DOMAIN_NAME + 1; code < 300; ++code) {
        EXPECT_FALSE(CfgMgr::instance().getStagingCfg()->getCfgRSOO()
                     ->enabled(code)) << " for option code " << code;
    }
}

TEST_F(Dhcp6ParserTest, rsooNegativeNumber) {
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
        Element::fromJSON("{ " + genIfaceConfig() + ","
                          "\"relay-supplied-options\": [ \"80\", \"-2\" ],"
                          "\"preferred-lifetime\": 3000,"
                          "\"rebind-timer\": 2000, "
                          "\"renew-timer\": 1000, "
                          "\"subnet6\": [  ], "
                          "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

TEST_F(Dhcp6ParserTest, rsooBogusName) {
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
        Element::fromJSON("{ " + genIfaceConfig() + ","
                          "\"relay-supplied-options\": [ \"bogus\", \"dns-servers\" ],"
                          "\"preferred-lifetime\": 3000,"
                          "\"rebind-timer\": 2000, "
                          "\"renew-timer\": 1000, "
                          "\"subnet6\": [  ], "
                          "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 1);
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

/// Check that the decline-probation-period value can be set properly.
TEST_F(Dhcp6ParserTest, declineTimerDefault) {

    ConstElementPtr status;

    string config_txt = "{ " + genIfaceConfig() + ","
        "\"subnet6\": [  ] "
        "}";
    ElementPtr config = Element::fromJSON(config_txt);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, config));

    // returned value should be 0 (success)
    checkResult(status, 0);

    // The value of decline-probation-period must be equal to the
    // default value.
    EXPECT_EQ(DEFAULT_DECLINE_PROBATION_PERIOD,
              CfgMgr::instance().getStagingCfg()->getDeclinePeriod());
}

/// Check that the decline-probation-period value can be set properly.
TEST_F(Dhcp6ParserTest, declineTimer) {
    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + "," +
        "\"decline-probation-period\": 12345,"
        "\"subnet6\": [ ]"
        "}";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 0 (success)
    checkResult(status, 0);

    // The value of decline-probation-period must be equal to the
    // value specified.
    EXPECT_EQ(12345,
              CfgMgr::instance().getStagingCfg()->getDeclinePeriod());
}

/// Check that an incorrect decline-probation-period value will be caught.
TEST_F(Dhcp6ParserTest, declineTimerError) {
    ConstElementPtr status;

    string config = "{ " + genIfaceConfig() + "," +
        "\"decline-probation-period\": \"soon\","
        "\"subnet6\": [ ]"
        "}";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 1 (error)
    checkResult(status, 1);

    // Check that the error contains error position.
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// Check that configuration for the expired leases processing may be
// specified.
TEST_F(Dhcp6ParserTest, expiredLeasesProcessing) {
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
        "\"subnet6\": [ ]"
        "}";

    ElementPtr json = Element::fromJSON(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

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
TEST_F(Dhcp6ParserTest, expiredLeasesProcessingError) {
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
        "\"subnet6\": [ ]"
        "}";

    ElementPtr json = Element::fromJSON(config);

    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // Returned value should be 0 (error)
    checkResult(status, 1);

    // Check that the error contains error position.
    EXPECT_TRUE(errorContainsPosition(status, "<string>"));
}

// Verifies that simple list of valid classes parses and
// is staged for commit.
TEST_F(Dhcp6ParserTest, validClientClassDictionary) {

    string config = "{ " + genIfaceConfig() + ","
        "\"preferred-lifetime\": 3000, \n"
        "\"rebind-timer\": 2000,  \n"
        "\"renew-timer\": 1000,  \n"
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
        "\"subnet6\": [ {  \n"
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::ffff\" } ], \n"
        "    \"subnet\": \"2001:db8:1::/64\" } ], \n"
        "\"valid-lifetime\": 4000 } \n";

    ConstElementPtr status;
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
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

// Verifies that an class list containing an invalid
// class definition causes a configuraiton error.
TEST_F(Dhcp6ParserTest, invalidClientClassDictionary) {
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

    ConstElementPtr status;
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 1);
}

};
