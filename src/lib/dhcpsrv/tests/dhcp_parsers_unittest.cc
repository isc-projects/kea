// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <dhcpsrv/parsers/shared_networks_list_parser.h>
#include <dhcpsrv/tests/test_libraries.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks_parser.h>
#include <hooks/hooks_manager.h>
#include <testutils/test_to_element.h>

#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <map>
#include <string>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;
using namespace isc::test;

namespace {

/// @brief DHCP Parser test fixture class
class DhcpParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    DhcpParserTest() {
        resetIfaceCfg();
    }

    /// @brief Destructor.
    virtual ~DhcpParserTest() {
        resetIfaceCfg();
    }

    /// @brief Resets selection of the interfaces from previous tests.
    void resetIfaceCfg() {
        CfgMgr::instance().clear();
    }
};

/// Verifies the code that parses mac sources and adds them to CfgMgr
TEST_F(DhcpParserTest, MacSources) {

    // That's an equivalent of the following snippet:
    // "mac-sources: [ \"duid\", \"ipv6\" ]";
    ElementPtr values = Element::createList();
    values->add(Element::create("duid"));
    values->add(Element::create("ipv6-link-local"));

    // Let's grab server configuration from CfgMgr
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    CfgMACSource& sources = cfg->getMACSources();

    // This should parse the configuration and check that it doesn't throw.
    MACSourcesListConfigParser parser;
    EXPECT_NO_THROW(parser.parse(sources, values));

    // Finally, check the sources that were configured
    CfgMACSources configured_sources =  cfg->getMACSources().get();
    ASSERT_EQ(2, configured_sources.size());
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_DUID, configured_sources[0]);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL, configured_sources[1]);
}

/// @brief Check MACSourcesListConfigParser rejecting empty list
///
/// Verifies that the code rejects an empty mac-sources list.
TEST_F(DhcpParserTest, MacSourcesEmpty) {

    // That's an equivalent of the following snippet:
    // "mac-sources: [ \"duid\", \"ipv6\" ]";
    ElementPtr values = Element::createList();

    // Let's grab server configuration from CfgMgr
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    CfgMACSource& sources = cfg->getMACSources();

    // This should throw, because if specified, at least one MAC source
    // has to be specified.
    MACSourcesListConfigParser parser;
    EXPECT_THROW(parser.parse(sources, values), DhcpConfigError);
}

/// @brief Check MACSourcesListConfigParser rejecting empty list
///
/// Verifies that the code rejects fake mac source.
TEST_F(DhcpParserTest, MacSourcesBogus) {

    // That's an equivalent of the following snippet:
    // "mac-sources: [ \"duid\", \"ipv6\" ]";
    ElementPtr values = Element::createList();
    values->add(Element::create("from-ebay"));
    values->add(Element::create("just-guess-it"));

    // Let's grab server configuration from CfgMgr
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    CfgMACSource& sources = cfg->getMACSources();

    // This should throw, because these are not valid sources.
    MACSourcesListConfigParser parser;
    EXPECT_THROW(parser.parse(sources, values), DhcpConfigError);
}

/// Verifies the code that properly catches duplicate entries
/// in mac-sources definition.
TEST_F(DhcpParserTest, MacSourcesDuplicate) {

    // That's an equivalent of the following snippet:
    // "mac-sources: [ \"duid\", \"ipv6\" ]";
    ElementPtr values = Element::createList();
    values->add(Element::create("ipv6-link-local"));
    values->add(Element::create("duid"));
    values->add(Element::create("duid"));
    values->add(Element::create("duid"));

    // Let's grab server configuration from CfgMgr
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    CfgMACSource& sources = cfg->getMACSources();

    // This should parse the configuration and check that it throws.
    MACSourcesListConfigParser parser;
    EXPECT_THROW(parser.parse(sources, values), DhcpConfigError);
}


/// @brief Test Fixture class which provides basic structure for testing
/// configuration parsing.  This is essentially the same structure provided
/// by dhcp servers.
class ParseConfigTest : public ::testing::Test {
public:
    /// @brief Constructor
    ParseConfigTest()
        :family_(AF_INET6) {
        reset_context();
        CfgMgr::instance().clear();
    }

    ~ParseConfigTest() {
        reset_context();
        CfgMgr::instance().clear();
    }

    /// @brief Parses a configuration.
    ///
    /// Parse the given configuration, populating the context storage with
    /// the parsed elements.
    ///
    /// @param config_set is the set of elements to parse.
    /// @param v6 boolean flag indicating if this is a DHCPv6 configuration.
    /// @return returns an ConstElementPtr containing the numeric result
    /// code and outcome comment.
    isc::data::ConstElementPtr
    parseElementSet(isc::data::ConstElementPtr config_set, bool v6) {
        // Answer will hold the result.
        ConstElementPtr answer;
        if (!config_set) {
            answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
            return (answer);
        }

        ConfigPair config_pair;
        try {
            // Iterate over the config elements.
            const std::map<std::string, ConstElementPtr>& values_map =
                                                      config_set->mapValue();
            BOOST_FOREACH(config_pair, values_map) {

                // These are the simple parsers. No need to go through
                // the ParserPtr hooplas with them.
                if ((config_pair.first == "option-data") ||
                    (config_pair.first == "option-def") ||
                    (config_pair.first == "dhcp-ddns")) {
                    continue;
                }

                // We also don't care about the default values that may be been
                // inserted
                if ((config_pair.first == "preferred-lifetime") ||
                    (config_pair.first == "valid-lifetime") ||
                    (config_pair.first == "renew-timer") ||
                    (config_pair.first == "rebind-timer")) {
                    continue;
                }

                if (config_pair.first == "hooks-libraries") {
                    HooksLibrariesParser hook_parser;
                    HooksConfig&  libraries =
                        CfgMgr::instance().getStagingCfg()->getHooksConfig();
                    hook_parser.parse(libraries, config_pair.second);
                    libraries.verifyLibraries(config_pair.second->getPosition());
                    libraries.loadLibraries();
                    continue;
                }
            }

            // The option definition parser is the next one to be run.
            std::map<std::string, ConstElementPtr>::const_iterator
                                def_config = values_map.find("option-def");
            if (def_config != values_map.end()) {

                CfgOptionDefPtr cfg_def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
                OptionDefListParser def_list_parser;
                def_list_parser.parse(cfg_def, def_config->second);
            }

            // The option values parser is the next one to be run.
            std::map<std::string, ConstElementPtr>::const_iterator
                                option_config = values_map.find("option-data");
            if (option_config != values_map.end()) {
                CfgOptionPtr cfg_option = CfgMgr::instance().getStagingCfg()->getCfgOption();

                OptionDataListParser option_list_parser(family_);
                option_list_parser.parse(cfg_option, option_config->second);
            }

            // The dhcp-ddns parser is the next one to be run.
            std::map<std::string, ConstElementPtr>::const_iterator
                                d2_client_config = values_map.find("dhcp-ddns");
            if (d2_client_config != values_map.end()) {
                // Used to be done by parser commit
                D2ClientConfigParser parser;
                D2ClientConfigPtr cfg = parser.parse(d2_client_config->second);
                CfgMgr::instance().setD2ClientConfig(cfg);
            }

            std::map<std::string, ConstElementPtr>::const_iterator
                                subnets4_config = values_map.find("subnet4");
            if (subnets4_config != values_map.end()) {
                auto srv_config = CfgMgr::instance().getStagingCfg();
                Subnets4ListConfigParser parser;
                parser.parse(srv_config, subnets4_config->second);
            }

            std::map<std::string, ConstElementPtr>::const_iterator
                                subnets6_config = values_map.find("subnet6");
            if (subnets6_config != values_map.end()) {
                auto srv_config = CfgMgr::instance().getStagingCfg();
                Subnets6ListConfigParser parser;
                parser.parse(srv_config, subnets6_config->second);
            }

            std::map<std::string, ConstElementPtr>::const_iterator
                                networks_config = values_map.find("shared-networks");
            if (networks_config != values_map.end()) {
                if (v6) {
                    auto cfg_shared_networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks6();
                    SharedNetworks6ListParser parser;
                    parser.parse(cfg_shared_networks, networks_config->second);

                } else {
                    auto cfg_shared_networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4();
                    SharedNetworks4ListParser parser;
                    parser.parse(cfg_shared_networks, networks_config->second);
                }
            }

            // Everything was fine. Configuration is successful.
            answer = isc::config::createAnswer(0, "Configuration committed.");
        } catch (const isc::Exception& ex) {
            answer = isc::config::createAnswer(1,
                        string("Configuration parsing failed: ") + ex.what());

        } catch (...) {
            answer = isc::config::createAnswer(1,
                                        string("Configuration parsing failed"));
        }

        return (answer);
    }

    /// @brief DHCP-specific method that sets global, and option specific defaults
    ///
    /// This method sets the defaults in the global scope, in option definitions,
    /// and in option data.
    ///
    /// @param global pointer to the Element tree that holds configuration
    /// @param global_defaults array with global default values
    /// @param option_defaults array with option-data default values
    /// @param option_def_defaults array with default values for option definitions
    /// @return number of default values inserted.
    size_t setAllDefaults(isc::data::ElementPtr global,
                          const SimpleDefaults& global_defaults,
                          const SimpleDefaults& option_defaults,
                          const SimpleDefaults& option_def_defaults) {
        size_t cnt = 0;
        // Set global defaults first.
        cnt = SimpleParser::setDefaults(global, global_defaults);

        // Now set option definition defaults for each specified option definition
        ConstElementPtr option_defs = global->get("option-def");
        if (option_defs) {
            BOOST_FOREACH(ElementPtr single_def, option_defs->listValue()) {
                cnt += SimpleParser::setDefaults(single_def, option_def_defaults);
            }
        }

        ConstElementPtr options = global->get("option-data");
        if (options) {
            BOOST_FOREACH(ElementPtr single_option, options->listValue()) {
                cnt += SimpleParser::setDefaults(single_option, option_defaults);
            }
        }

        return (cnt);
    }

    /// This table defines default values for option definitions in DHCPv6
    static const SimpleDefaults OPTION6_DEF_DEFAULTS;

    /// This table defines default values for option definitions in DHCPv4
    static const SimpleDefaults OPTION4_DEF_DEFAULTS;

    /// This table defines default values for options in DHCPv6
    static const SimpleDefaults OPTION6_DEFAULTS;

    /// This table defines default values for options in DHCPv4
    static const SimpleDefaults OPTION4_DEFAULTS;

    /// This table defines default values for both DHCPv4 and DHCPv6
    static const SimpleDefaults GLOBAL6_DEFAULTS;

    /// @brief sets all default values for DHCPv4 and DHCPv6
    ///
    /// This function largely duplicates what SimpleParser4 and SimpleParser6 classes
    /// provide. However, since there are tons of unit-tests in dhcpsrv that need
    /// this functionality and there are good reasons to keep those classes in
    /// src/bin/dhcp{4,6}, the most straightforward way is to simply copy the
    /// minimum code here. Hence this method.
    ///
    /// @todo - TKM, I think this is fairly hideous and we should figure out a
    /// a way to not have to replicate in this fashion.  It may be minimum code
    /// now, but it won't be fairly soon.
    ///
    /// @param config configuration structure to be filled with default values
    /// @param v6 true = DHCPv6, false = DHCPv4
    void setAllDefaults(ElementPtr config, bool v6) {
        if (v6) {
            setAllDefaults(config, GLOBAL6_DEFAULTS, OPTION6_DEFAULTS,
                           OPTION6_DEF_DEFAULTS);
        } else {
            setAllDefaults(config, GLOBAL6_DEFAULTS, OPTION4_DEFAULTS,
                           OPTION4_DEF_DEFAULTS);
        }

        /// D2 client configuration code is in this library
        ConstElementPtr d2_client = config->get("dhcp-ddns");
        if (d2_client) {
            D2ClientConfigParser::setAllDefaults(d2_client);
        }
    }

    /// @brief Convenience method for parsing a configuration
    ///
    /// Given a configuration string, convert it into Elements
    /// and parse them.
    /// @param config is the configuration string to parse
    /// @param v6 boolean value indicating if this is DHCPv6 configuration.
    /// @param set_defaults boolean value indicating if the defaults should
    /// be derived before parsing the configuration.
    ///
    /// @return returns 0 if the configuration parsed successfully,
    /// non-zero otherwise failure.
    int parseConfiguration(const std::string& config, bool v6 = false,
                           bool set_defaults = true) {
        int rcode_ = 1;
        // Turn config into elements.
        // Test json just to make sure its valid.
        ElementPtr json = Element::fromJSON(config);
        EXPECT_TRUE(json);
        if (json) {
            if (set_defaults) {
                setAllDefaults(json, v6);
            }

            ConstElementPtr status = parseElementSet(json, v6);
            ConstElementPtr comment = parseAnswer(rcode_, status);
            error_text_ = comment->stringValue();
            // If error was reported, the error string should contain
            // position of the data element which caused failure.
            if (rcode_ != 0) {
                std::cout << "Error text:" << error_text_ << std::endl;
                EXPECT_TRUE(errorContainsPosition(status, "<string>"));
            }
        }

        return (rcode_);
    }

    /// @brief Find an option for a given space and code within the parser
    /// context.
    /// @param space is the space name of the desired option.
    /// @param code is the numeric "type" of the desired option.
    /// @return returns an OptionPtr which points to the found
    /// option or is empty.
    /// ASSERT_ tests don't work inside functions that return values
    OptionPtr getOptionPtr(std::string space, uint32_t code)
    {
        OptionPtr option_ptr;
        OptionContainerPtr options = CfgMgr::instance().getStagingCfg()->
            getCfgOption()->getAll(space);
        // Should always be able to get options list even if it is empty.
        EXPECT_TRUE(options);
        if (options) {
            // Attempt to find desired option.
            const OptionContainerTypeIndex& idx = options->get<1>();
            const OptionContainerTypeRange& range = idx.equal_range(code);
            int cnt = std::distance(range.first, range.second);
            EXPECT_EQ(1, cnt);
            if (cnt == 1) {
                OptionDescriptor desc = *(idx.begin());
                option_ptr = desc.option_;
                EXPECT_TRUE(option_ptr);
            }
        }

        return (option_ptr);
    }

    /// @brief Wipes the contents of the context to allowing another parsing
    /// during a given test if needed.
    void reset_context(){
        // Note set context universe to V6 as it has to be something.
        CfgMgr::instance().clear();
        family_ = AF_INET6;

        // Ensure no hooks libraries are loaded.
        HooksManager::unloadLibraries();

        // Set it to minimal, disabled config
        D2ClientConfigPtr tmp(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(tmp);
    }

    /// Allows the tests to interrogate the state of the libraries (if required).
    const isc::hooks::HookLibsCollection& getLibraries() {
        return (CfgMgr::instance().getStagingCfg()->getHooksConfig().get());
    }

    /// @brief specifies IP protocol family (AF_INET or AF_INET6)
    uint16_t family_;

    /// @brief Error string if the parsing failed
    std::string error_text_;
};

/// This table defines default values for option definitions in DHCPv6
const SimpleDefaults ParseConfigTest::OPTION6_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp6"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for option definitions in DHCPv4
const SimpleDefaults ParseConfigTest::OPTION4_DEF_DEFAULTS = {
    { "record-types", Element::string,  ""},
    { "space",        Element::string,  "dhcp4"},
    { "array",        Element::boolean, "false"},
    { "encapsulate",  Element::string,  "" }
};

/// This table defines default values for options in DHCPv6
const SimpleDefaults ParseConfigTest::OPTION6_DEFAULTS = {
    { "space",        Element::string,  "dhcp6"},
    { "csv-format",   Element::boolean, "true"},
    { "always-send",  Element::boolean,"false"}
};

/// This table defines default values for options in DHCPv4
const SimpleDefaults ParseConfigTest::OPTION4_DEFAULTS = {
    { "space",        Element::string,  "dhcp4"},
    { "csv-format",   Element::boolean, "true"},
    { "always-send",  Element::boolean, "false"}
};

/// This table defines default values for both DHCPv4 and DHCPv6
const SimpleDefaults ParseConfigTest::GLOBAL6_DEFAULTS = {
    { "renew-timer",        Element::integer, "900" },
    { "rebind-timer",       Element::integer, "1800" },
    { "preferred-lifetime", Element::integer, "3600" },
    { "valid-lifetime",     Element::integer, "7200" }
};

/// @brief Option configuration class
///
/// This class handles option-def and option-data which can be recovered
/// using the toElement() method
class CfgOptionsTest : public CfgToElement {
public:
    /// @brief Constructor
    ///
    /// @param cfg the server configuration where to get option-{def,data}
    CfgOptionsTest(SrvConfigPtr cfg) :
        cfg_option_def_(cfg->getCfgOptionDef()),
        cfg_option_(cfg->getCfgOption()) { }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration (a map with
    /// not empty option-def and option-data lists)
    ElementPtr toElement() const {
        ElementPtr result = Element::createMap();
        // Set option-def
        ConstElementPtr option_def = cfg_option_def_->toElement();
        if (!option_def->empty()) {
            result->set("option-def", option_def);
        }
        // Set option-data
        ConstElementPtr option_data = cfg_option_->toElement();
        if (!option_data->empty()) {
            result->set("option-data", option_data);
        }
        return (result);
    }

    /// @brief Run a toElement test (Element version)
    ///
    /// Use the runToElementTest template but add defaults to the config
    ///
    /// @param family the address family
    /// @param config the expected result without defaults
    void runCfgOptionsTest(uint16_t family, ConstElementPtr expected) {
        ConstElementPtr option_def = expected->get("option-def");
        if (option_def) {
            SimpleParser::setListDefaults(option_def,
                                          family == AF_INET ?
                                          ParseConfigTest::OPTION4_DEF_DEFAULTS :
                                          ParseConfigTest::OPTION6_DEF_DEFAULTS);
        }
        ConstElementPtr option_data = expected->get("option-data");
        if (option_data) {
            SimpleParser::setListDefaults(option_data,
                                          family == AF_INET ?
                                          ParseConfigTest::OPTION4_DEFAULTS :
                                          ParseConfigTest::OPTION6_DEFAULTS);
        }
        runToElementTest<CfgOptionsTest>(expected, *this);
    }

    /// @brief Run a toElement test
    ///
    /// Use the runToElementTest template but add defaults to the config
    ///
    /// @param family the address family
    /// @param expected the expected result without defaults
    void runCfgOptionsTest(uint16_t family, std::string config) {
        ConstElementPtr json;
        ASSERT_NO_THROW(json = Element::fromJSON(config)) << config;
        runCfgOptionsTest(family, json);
    }

private:
    /// @brief Pointer to option definitions configuration.
    CfgOptionDefPtr cfg_option_def_;

    /// @brief Reference to options (data) configuration.
    CfgOptionPtr cfg_option_;
};

/// @brief Check basic parsing of option definitions.
///
/// Note that this tests basic operation of the OptionDefinitionListParser and
/// OptionDefinitionParser.  It uses a simple configuration consisting of
/// one definition and verifies that it is parsed and committed to storage
/// correctly.
TEST_F(ParseConfigTest, basicOptionDefTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"array\": false,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_EQ(0, rcode);


    // Verify that the option definition can be retrieved.
    OptionDefinitionPtr def =
        CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Verify that the option definition is correct.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, def->getType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());

    // Check if libdhcp++ runtime options have been updated.
    OptionDefinitionPtr def_libdhcp = LibDHCP::getRuntimeOptionDef("isc", 100);
    ASSERT_TRUE(def_libdhcp);

    // The LibDHCP should return a separate instance of the option definition
    // but the values should be equal.
    EXPECT_TRUE(def_libdhcp != def);
    EXPECT_TRUE(*def_libdhcp == *def);

    // Check if it can be unparsed.
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, config);
}

/// @brief Check minimal parsing of option definitions.
///
/// Same than basic but without optional parameters set to their default.
TEST_F(ParseConfigTest, minimalOptionDefTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"isc\""
        "  } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_EQ(0, rcode);


    // Verify that the option definition can be retrieved.
    OptionDefinitionPtr def =
        CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get("isc", 100);
    ASSERT_TRUE(def);

    // Verify that the option definition is correct.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, def->getType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());

    // Check if it can be unparsed.
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, config);
}

/// @brief Check parsing of option definitions using default dhcp6 space.
///
/// Same than minimal but using the fact the default universe is V6
/// so the default space is dhcp6
TEST_F(ParseConfigTest, defaultSpaceOptionDefTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 10000,"
        "      \"type\": \"ipv6-address\""
        "  } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config, true);
    ASSERT_EQ(0, rcode);


    // Verify that the option definition can be retrieved.
    OptionDefinitionPtr def =
        CfgMgr::instance().getStagingCfg()->getCfgOptionDef()->get(DHCP6_OPTION_SPACE, 10000);
    ASSERT_TRUE(def);

    // Verify that the option definition is correct.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(10000, def->getCode());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, def->getType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());

    // Check if it can be unparsed.
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, config);
}

/// @brief Check parsing of option definitions using invalid space fails.
TEST_F(ParseConfigTest, badSpaceOptionDefTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100000,"
        "      \"type\": \"ipv6-address\","
        "      \"space\": \"-1\""
        "  } ]"
        "}";

    // Verify that the configuration string does not parse.
    int rcode = parseConfiguration(config, true);
    ASSERT_NE(0, rcode);
}

/// @brief Check basic parsing of options.
///
/// Note that this tests basic operation of the OptionDataListParser and
/// OptionDataParser.  It uses a simple configuration consisting of one
/// one definition and matching option data.  It verifies that the option
/// is parsed and committed to storage correctly.
TEST_F(ParseConfigTest, basicOptionDataTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"isc\""
        " } ], "
        " \"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"code\": 100,"
        "    \"data\": \"192.0.2.0\","
        "    \"csv-format\": true,"
        "    \"always-send\": false"
        " } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_EQ(0, rcode);

    // Verify that the option can be retrieved.
    OptionPtr opt_ptr = getOptionPtr("isc", 100);
    ASSERT_TRUE(opt_ptr);

    // Verify that the option data is correct.
    std::string val = "type=00100, len=00004: 192.0.2.0 (ipv4-address)";

    EXPECT_EQ(val, opt_ptr->toText());

    // Check if it can be unparsed.
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, config);
}

/// @brief Check minimal parsing of options.
///
/// Same than basic but without optional parameters set to their default.
TEST_F(ParseConfigTest, minimalOptionDataTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"space\": \"isc\""
        " } ], "
        " \"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"data\": \"192.0.2.0\""
        " } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_EQ(0, rcode);

    // Verify that the option can be retrieved.
    OptionPtr opt_ptr = getOptionPtr("isc", 100);
    ASSERT_TRUE(opt_ptr);

    // Verify that the option data is correct.
    std::string val = "type=00100, len=00004: 192.0.2.0 (ipv4-address)";

    EXPECT_EQ(val, opt_ptr->toText());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(100));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

/// @brief Check parsing of unknown options fails.
TEST_F(ParseConfigTest, unknownOptionDataTest) {

    // Configuration string.
    std::string config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"data\": \"01\","
        "    \"space\": \"bar\""
        " } ]"
        "}";

    // Verify that the configuration string does not parse.
    int rcode = parseConfiguration(config, true);
    ASSERT_NE(0, rcode);
}

/// @brief Check parsing of options with invalid space fails.
TEST_F(ParseConfigTest, badSpaceOptionDataTest) {

    // Configuration string.
    std::string config =
        "{ \"option-data\": [ {"
        "    \"code\": 100,"
        "    \"data\": \"01\","
        "    \"space\": \"-1\""
        " } ]"
        "}";

    // Verify that the configuration string does not parse.
    int rcode = parseConfiguration(config, true);
    ASSERT_NE(0, rcode);
}

/// @brief Check parsing of options with escape characters.
///
/// Note that this tests basic operation of the OptionDataListParser and
/// OptionDataParser.  It uses a simple configuration consisting of one
/// one definition and matching option data.  It verifies that the option
/// is parsed and committed to storage correctly and that its content
/// has the actual character (e.g. an actual backslash, not double backslash).
TEST_F(ParseConfigTest, escapedOptionDataTest) {

    family_ = AF_INET;

    // We need to use double escapes here. The first backslash will
    // be consumed by C++ preprocessor, so the actual string will
    // have two backslash characters: \\SMSBoot\\x64\\wdsnbp.com.
    //
    std::string config =
        "{\"option-data\": [ {"
        "    \"name\": \"boot-file-name\","
        "    \"data\": \"\\\\SMSBoot\\\\x64\\\\wdsnbp.com\""
        " } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_EQ(0, rcode);

    // Verify that the option can be retrieved.
    OptionPtr opt = getOptionPtr(DHCP4_OPTION_SPACE, DHO_BOOT_FILE_NAME);
    ASSERT_TRUE(opt);

    util::OutputBuffer buf(100);

    uint8_t exp[] = { DHO_BOOT_FILE_NAME, 23, '\\', 'S', 'M', 'S', 'B', 'o', 'o',
                      't', '\\', 'x', '6', '4', '\\', 'w', 'd', 's', 'n', 'b',
                      'p', '.', 'c', 'o', 'm' };
    ASSERT_EQ(25, sizeof(exp));

    opt->pack(buf);
    EXPECT_EQ(Option::OPTION4_HDR_LEN + 23, buf.getLength());

    EXPECT_TRUE(0 == memcmp(buf.getData(), exp, 25));

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(DHO_BOOT_FILE_NAME));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

// This test checks behavior of the configuration parser for option data
// for different values of csv-format parameter and when there is an option
// definition present.
TEST_F(ParseConfigTest, optionDataCSVFormatWithOptionDef) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"name\": \"swap-server\","
        "    \"space\": \"dhcp4\","
        "    \"code\": 16,"
        "    \"data\": \"192.0.2.0\""
        " } ]"
        "}";

    // The default universe is V6. We need to change it to use dhcp4 option
    // space.
    family_ = AF_INET;
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    OptionCustomPtr addr_opt = boost::dynamic_pointer_cast<
        OptionCustom>(getOptionPtr(DHCP4_OPTION_SPACE, 16));
    ASSERT_TRUE(addr_opt);
    EXPECT_EQ("192.0.2.0", addr_opt->readAddress().toText());

    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, config);

    // Explicitly enable csv-format.
    CfgMgr::instance().clear();
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"swap-server\","
        "    \"space\": \"dhcp4\","
        "    \"code\": 16,"
        "    \"csv-format\": true,"
        "    \"data\": \"192.0.2.0\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    addr_opt = boost::dynamic_pointer_cast<
        OptionCustom>(getOptionPtr(DHCP4_OPTION_SPACE, 16));
    ASSERT_TRUE(addr_opt);
    EXPECT_EQ("192.0.2.0", addr_opt->readAddress().toText());

    // To make runToElementTest to work the csv-format must be removed...

    // Explicitly disable csv-format and use hex instead.
    CfgMgr::instance().clear();
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"swap-server\","
        "    \"space\": \"dhcp4\","
        "    \"code\": 16,"
        "    \"csv-format\": false,"
        "    \"data\": \"C0000200\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    addr_opt = boost::dynamic_pointer_cast<
        OptionCustom>(getOptionPtr(DHCP4_OPTION_SPACE, 16));
    ASSERT_TRUE(addr_opt);
    EXPECT_EQ("192.0.2.0", addr_opt->readAddress().toText());

    CfgOptionsTest cfg2(CfgMgr::instance().getStagingCfg());
    cfg2.runCfgOptionsTest(family_, config);
}

// This test verifies that definitions of standard encapsulated
// options can be used.
TEST_F(ParseConfigTest, encapsulatedOptionData) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"space\": \"s46-cont-mape-options\","
        "    \"name\": \"s46-rule\","
        "    \"data\": \"1, 0, 24, 192.0.2.0, 2001:db8:1::/64\""
        " } ]"
        "}";

    // Make sure that we're using correct universe.
    family_ = AF_INET6;
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    OptionCustomPtr s46_rule = boost::dynamic_pointer_cast<OptionCustom>
        (getOptionPtr(MAPE_V6_OPTION_SPACE, D6O_S46_RULE));
    ASSERT_TRUE(s46_rule);

    uint8_t flags;
    uint8_t ea_len;
    uint8_t prefix4_len;
    IOAddress ipv4_prefix(IOAddress::IPV4_ZERO_ADDRESS());
    PrefixTuple ipv6_prefix(PrefixLen(0), IOAddress::IPV6_ZERO_ADDRESS());;

    ASSERT_NO_THROW({
        flags = s46_rule->readInteger<uint8_t>(0);
        ea_len = s46_rule->readInteger<uint8_t>(1);
        prefix4_len = s46_rule->readInteger<uint8_t>(2);
        ipv4_prefix = s46_rule->readAddress(3);
        ipv6_prefix = s46_rule->readPrefix(4);
    });

    EXPECT_EQ(1, flags);
    EXPECT_EQ(0, ea_len);
    EXPECT_EQ(24, prefix4_len);
    EXPECT_EQ("192.0.2.0", ipv4_prefix.toText());
    EXPECT_EQ(64, ipv6_prefix.first.asUnsigned());
    EXPECT_EQ("2001:db8:1::", ipv6_prefix.second.toText());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(D6O_S46_RULE));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

// This test checks behavior of the configuration parser for option data
// for different values of csv-format parameter and when there is no
// option definition.
TEST_F(ParseConfigTest, optionDataCSVFormatNoOptionDef) {
    // This option doesn't have any definition. It is ok to use such
    // an option but the data should be specified in hex, not as CSV.
    // Note that the parser will by default use the CSV format for the
    // data but only in case there is a suitable option definition.
    std::string config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 25000,"
        "    \"data\": \"1, 2, 5\""
        " } ]"
        "}";
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_NE(0, rcode);

    CfgMgr::instance().clear();
    // The data specified here will work both for CSV format and hex format.
    // What we want to test here is that when the csv-format is enforced, the
    // parser will fail because of lack of an option definition.
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 25000,"
        "    \"csv-format\": true,"
        "    \"data\": \"0\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_NE(0, rcode);

    CfgMgr::instance().clear();
    // The same test case as above, but for the data specified in hex should
    // be successful.
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 25000,"
        "    \"csv-format\": false,"
        "    \"data\": \"0\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    ASSERT_EQ(0, rcode);
    OptionPtr opt = getOptionPtr(DHCP6_OPTION_SPACE, 25000);
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getData().size());
    EXPECT_EQ(0, opt->getData()[0]);

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->remove("name");
    opt_data->set("data", Element::create(std::string("00")));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);

    CfgMgr::instance().clear();
    // When csv-format is not specified, the parser will check if the definition
    // exists or not. Since there is no definition, the parser will accept the
    // data in hex.
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 25000,"
        "    \"csv-format\": false,"
        "    \"data\": \"123456\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    opt = getOptionPtr(DHCP6_OPTION_SPACE, 25000);
    ASSERT_TRUE(opt);
    ASSERT_EQ(3, opt->getData().size());
    EXPECT_EQ(0x12, opt->getData()[0]);
    EXPECT_EQ(0x34, opt->getData()[1]);
    EXPECT_EQ(0x56, opt->getData()[2]);

    expected = Element::fromJSON(config);
    opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->remove("name");
    CfgOptionsTest cfg2(CfgMgr::instance().getStagingCfg());
    cfg2.runCfgOptionsTest(family_, expected);
}

// This test verifies that the option name is not mandatory, if the option
// code has been specified.
TEST_F(ParseConfigTest, optionDataNoName) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"space\": \"dhcp6\","
        "    \"code\": 23,"
        "    \"data\": \"2001:db8:1::1\""
        " } ]"
        "}";
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE, 23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::1", opt->getAddresses()[0].toText());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("name", Element::create(std::string("dns-servers")));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

// This test verifies that the option code is not mandatory, if the option
// name has been specified.
TEST_F(ParseConfigTest, optionDataNoCode) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"space\": \"dhcp6\","
        "    \"name\": \"dns-servers\","
        "    \"data\": \"2001:db8:1::1\""
        " } ]"
        "}";
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE, 23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::1", opt->getAddresses()[0].toText());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(D6O_NAME_SERVERS));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

// This test verifies that the option data configuration with a minimal
// set of parameters works as expected.
TEST_F(ParseConfigTest, optionDataMinimal) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"name\": \"dns-servers\","
        "    \"data\": \"2001:db8:1::10\""
        " } ]"
        "}";
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE, 23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::10", opt->getAddresses()[0].toText());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(D6O_NAME_SERVERS));
    opt_data->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);

    CfgMgr::instance().clear();
    // This time using an option code.
    config =
        "{ \"option-data\": [ {"
        "    \"code\": 23,"
        "    \"data\": \"2001:db8:1::20\""
        " } ]"
        "}";
    rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    opt = boost::dynamic_pointer_cast<Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE,
                                                                   23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::20", opt->getAddresses()[0].toText());

    expected = Element::fromJSON(config);
    opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("name", Element::create(std::string("dns-servers")));
    opt_data->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    CfgOptionsTest cfg2(CfgMgr::instance().getStagingCfg());
    cfg2.runCfgOptionsTest(family_, expected);
}

// This test verifies that the option data configuration with a minimal
// set of parameters works as expected when option definition is
// created in the configuration file.
TEST_F(ParseConfigTest, optionDataMinimalWithOptionDef) {
    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo-name\","
        "      \"code\": 2345,"
        "      \"type\": \"ipv6-address\","
        "      \"array\": true,"
        "      \"space\": \"dhcp6\""
        "  } ],"
        "  \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"data\": \"2001:db8:1::10, 2001:db8:1::123\""
        " } ]"
        "}";

    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE, 2345));
    ASSERT_TRUE(opt);
    ASSERT_EQ(2, opt->getAddresses().size());
    EXPECT_EQ("2001:db8:1::10", opt->getAddresses()[0].toText());
    EXPECT_EQ("2001:db8:1::123", opt->getAddresses()[1].toText());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(2345));
    opt_data->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);

    CfgMgr::instance().clear();
    // Do the same test but now use an option code.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo-name\","
        "      \"code\": 2345,"
        "      \"type\": \"ipv6-address\","
        "      \"array\": true,"
        "      \"space\": \"dhcp6\""
        "  } ],"
        "  \"option-data\": [ {"
        "    \"code\": 2345,"
        "    \"data\": \"2001:db8:1::10, 2001:db8:1::123\""
        " } ]"
        "}";

    rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    opt = boost::dynamic_pointer_cast<Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE,
                                                                   2345));
    ASSERT_TRUE(opt);
    ASSERT_EQ(2, opt->getAddresses().size());
    EXPECT_EQ("2001:db8:1::10", opt->getAddresses()[0].toText());
    EXPECT_EQ("2001:db8:1::123", opt->getAddresses()[1].toText());

    expected = Element::fromJSON(config);
    opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("name", Element::create(std::string("foo-name")));
    opt_data->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    CfgOptionsTest cfg2(CfgMgr::instance().getStagingCfg());
    cfg2.runCfgOptionsTest(family_, expected);
}

// This test verifies an empty option data configuration is supported.
TEST_F(ParseConfigTest, emptyOptionData) {
    // Configuration string.
    const std::string config =
        "{ \"option-data\": [ {"
        "    \"name\": \"dhcp4o6-server-addr\""
        " } ]"
        "}";

    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config, true));
    EXPECT_EQ(0, rcode);
    const Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr(DHCP6_OPTION_SPACE, D6O_DHCPV4_O_DHCPV6_SERVER));
    ASSERT_TRUE(opt);
    ASSERT_EQ(0, opt->getAddresses().size());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(D6O_DHCPV4_O_DHCPV6_SERVER));
    opt_data->set("space", Element::create(std::string(DHCP6_OPTION_SPACE)));
    opt_data->set("csv-format", Element::create(false));
    opt_data->set("data", Element::create(std::string("")));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

// This test verifies an option data without suboptions is supported
TEST_F(ParseConfigTest, optionDataNoSubOption) {
    // Configuration string. A global definition for option 43 is needed.
    const std::string config =
        "{ \"option-def\": [ {"
        " \"name\": \"vendor-encapsulated-options\","
        " \"code\": 43,"
        " \"type\": \"empty\","
        " \"space\": \"dhcp4\","
        " \"encapsulate\": \"vendor-encapsulated-options\""
        " } ],"
        " \"option-data\": [ {"
        "    \"name\": \"vendor-encapsulated-options\""
        " } ]"
        "}";

    // The default universe is V6. We need to change it to use dhcp4 option
    // space.
    family_ = AF_INET;
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    const OptionPtr opt = getOptionPtr(DHCP4_OPTION_SPACE, DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(opt);
    ASSERT_EQ(0, opt->getOptions().size());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->set("code", Element::create(DHO_VENDOR_ENCAPSULATED_OPTIONS));
    opt_data->set("space", Element::create(std::string(DHCP4_OPTION_SPACE)));
    opt_data->set("csv-format", Element::create(false));
    opt_data->set("data", Element::create(std::string("")));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

// This tests option-data in CSV format and embedded commas.
TEST_F(ParseConfigTest, commaCSVFormatOptionData) {

    // Configuration string.
    std::string config =
        "{ \"option-data\": [ {"
        "     \"csv-format\": true,"
        "     \"code\": 41,"
        "     \"data\": \"EST5EDT4\\\\,M3.2.0/02:00\\\\,M11.1.0/02:00\","
        "     \"space\": \"dhcp6\""
        " } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config, true);
    ASSERT_EQ(0, rcode);

    // Verify that the option can be retrieved.
    OptionPtr opt = getOptionPtr(DHCP6_OPTION_SPACE, 41);
    ASSERT_TRUE(opt);

    // Get the option as an option string.
    OptionStringPtr opt_str = boost::dynamic_pointer_cast<OptionString>(opt);
    ASSERT_TRUE(opt_str);


    // Verify that the option data is correct.
    string val = "EST5EDT4,M3.2.0/02:00,M11.1.0/02:00";
    EXPECT_EQ(val, opt_str->getValue());

    ElementPtr expected = Element::fromJSON(config);
    ElementPtr opt_data = expected->get("option-data")->getNonConst(0);
    opt_data->remove("csv-format");
    opt_data->set("name", Element::create(std::string("new-posix-timezone")));
    CfgOptionsTest cfg(CfgMgr::instance().getStagingCfg());
    cfg.runCfgOptionsTest(family_, expected);
}

/// The next set of tests check basic operation of the HooksLibrariesParser.
//
// Convenience function to set a configuration of zero or more hooks
// libraries:
//
// lib1 - No parameters
// lib2 - Empty parameters statement
// lib3 - Valid parameters
std::string
setHooksLibrariesConfig(const char* lib1 = NULL, const char* lib2 = NULL,
                        const char* lib3 = NULL) {
    const string lbrace("{");
    const string rbrace("}");
    const string quote("\"");
    const string comma_space(", ");
    const string library("\"library\": ");

    string config = string("{ \"hooks-libraries\": [");
    if (lib1 != NULL) {
        // Library 1 has no parameters
        config += lbrace;
        config += library + quote + std::string(lib1) + quote;
        config += rbrace;

        if (lib2 != NULL) {
            // Library 2 has an empty parameters statement
            config += comma_space + lbrace;
            config += library + quote + std::string(lib2) + quote + comma_space;
            config += string("\"parameters\": {}");
            config += rbrace;

            if (lib3 != NULL) {
                // Library 3 has valid parameters
                config += comma_space + lbrace;
                config += library + quote + std::string(lib3) + quote + comma_space;
                config += string("\"parameters\": {");
                config += string("    \"svalue\": \"string value\", ");
                config += string("    \"ivalue\": 42, ");     // Integer value
                config += string("    \"bvalue\": true");     // Boolean value
                config += string("}");
                config += rbrace;
            }
        }
    }
    config += std::string("] }");

    return (config);
}

// hooks-libraries element that does not contain anything.
TEST_F(ParseConfigTest, noHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Create an empty hooks-libraries configuration element.
    const string config = setHooksLibrariesConfig();

    // Verify that the configuration string parses.
    const int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected =
                    Element::fromJSON(config)->get("hooks-libraries"));
    ASSERT_TRUE(expected);
    const HooksConfig& cfg =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg);

    // Check that the parser recorded nothing.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    EXPECT_TRUE(libraries.empty());

    // Check that there are still no libraries loaded.
    hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());
}

// hooks-libraries element that contains a single library.
TEST_F(ParseConfigTest, oneHooksLibrary) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration with hooks-libraries set to a single library.
    const string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1);

    // Verify that the configuration string parses.
    const int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected =
                    Element::fromJSON(config)->get("hooks-libraries"));
    ASSERT_TRUE(expected);
    const HooksConfig& cfg =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg);

    // Check that the parser recorded a single library.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(1, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0].first);

    // Check that the change was propagated to the hooks manager.
    hooks_libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(1, hooks_libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, hooks_libraries[0]);
}

// hooks-libraries element that contains two libraries
TEST_F(ParseConfigTest, twoHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration with hooks-libraries set to two libraries.
    const string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                                  CALLOUT_LIBRARY_2);

    // Verify that the configuration string parses.
    const int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected =
                    Element::fromJSON(config)->get("hooks-libraries"));
    ASSERT_TRUE(expected);
    const HooksConfig& cfg =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg);

    // Check that the parser recorded two libraries in the expected order.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(2, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0].first);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[1].first);

    // Verify that the change was propagated to the hooks manager.
    hooks_libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(2, hooks_libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, hooks_libraries[0]);
    EXPECT_EQ(CALLOUT_LIBRARY_2, hooks_libraries[1]);
}

// Configure with two libraries, then reconfigure with the same libraries.
TEST_F(ParseConfigTest, reconfigureSameHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration with hooks-libraries set to two libraries.
    const std::string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                                       CALLOUT_LIBRARY_2);

    // Verify that the configuration string parses. The twoHooksLibraries
    // test shows that the list will be as expected.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected =
                    Element::fromJSON(config)->get("hooks-libraries"));
    ASSERT_TRUE(expected);
    const HooksConfig& cfg =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg);

    // The previous test shows that the parser correctly recorded the two
    // libraries and that they loaded correctly.

    // Parse the string again.
    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // The list has not changed between the two parse operations. However,
    // the parameters (or the files they could point to) could have
    // changed, so the libraries are reloaded anyway.
    const HooksConfig& cfg2 =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg2);
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(2, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0].first);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[1].first);

    // ... and check that the same two libraries are still loaded in the
    // HooksManager.
    hooks_libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(2, hooks_libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, hooks_libraries[0]);
    EXPECT_EQ(CALLOUT_LIBRARY_2, hooks_libraries[1]);
}

// Configure the hooks with two libraries, then reconfigure with the same
// libraries, but in reverse order.
TEST_F(ParseConfigTest, reconfigureReverseHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration with hooks-libraries set to two libraries.
    std::string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                                 CALLOUT_LIBRARY_2);

    // Verify that the configuration string parses. The twoHooksLibraries
    // test shows that the list will be as expected.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // A previous test shows that the parser correctly recorded the two
    // libraries and that they loaded correctly.

    // Parse the reversed set of libraries.
    config = setHooksLibrariesConfig(CALLOUT_LIBRARY_2, CALLOUT_LIBRARY_1);
    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // The list has changed, and this is what we should see.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(2, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[0].first);
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[1].first);

    // ... and check that this was propagated to the HooksManager.
    hooks_libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(2, hooks_libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_2, hooks_libraries[0]);
    EXPECT_EQ(CALLOUT_LIBRARY_1, hooks_libraries[1]);
}

// Configure the hooks with two libraries, then reconfigure with
// no libraries.
TEST_F(ParseConfigTest, reconfigureZeroHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration with hooks-libraries set to two libraries.
    std::string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                                 CALLOUT_LIBRARY_2);

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // A previous test shows that the parser correctly recorded the two
    // libraries and that they loaded correctly.

    // Parse the string again, this time without any libraries.
    config = setHooksLibrariesConfig();
    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected =
                    Element::fromJSON(config)->get("hooks-libraries"));
    ASSERT_TRUE(expected);
    const HooksConfig& cfg =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg);

    // The list has changed, and this is what we should see.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    EXPECT_TRUE(libraries.empty());

    // Check that no libraries are currently loaded
    hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());
}

// Check with a set of libraries, some of which are invalid.
TEST_F(ParseConfigTest, invalidHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration string.  This contains an invalid library which should
    // trigger an error in the "build" stage.
    const std::string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                                       NOT_PRESENT_LIBRARY,
                                                       CALLOUT_LIBRARY_2);

    // Verify that the configuration fails to parse. (Syntactically it's OK,
    // but the library is invalid).
    const int rcode = parseConfiguration(config);
    ASSERT_FALSE(rcode == 0) << error_text_;

    // Check that the message contains the library in error.
    EXPECT_FALSE(error_text_.find(NOT_PRESENT_LIBRARY) == string::npos) <<
        "Error text returned from parse failure is " << error_text_;

    // Check that the parser recorded the names but, as they were in error,
    // does not flag them as changed.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(3, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0].first);
    EXPECT_EQ(NOT_PRESENT_LIBRARY, libraries[1].first);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[2].first);

    // ...and check it did not alter the libraries in the hooks manager.
    hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());
}

// Check that trying to reconfigure with an invalid set of libraries fails.
TEST_F(ParseConfigTest, reconfigureInvalidHooksLibraries) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configure with a single library.
    std::string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1);
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // A previous test shows that the parser correctly recorded the two
    // libraries and that they loaded correctly.

    // Configuration string.  This contains an invalid library which should
    // trigger an error in the "build" stage.
    config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1, NOT_PRESENT_LIBRARY,
                                     CALLOUT_LIBRARY_2);

    // Verify that the configuration fails to parse. (Syntactically it's OK,
    // but the library is invalid).
    rcode = parseConfiguration(config);
    EXPECT_FALSE(rcode == 0) << error_text_;

    // Check that the message contains the library in error.
    EXPECT_FALSE(error_text_.find(NOT_PRESENT_LIBRARY) == string::npos) <<
        "Error text returned from parse failure is " << error_text_;

    // Check that the parser recorded the names but, as the library set was
    // incorrect, did not mark the configuration as changed.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(3, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0].first);
    EXPECT_EQ(NOT_PRESENT_LIBRARY, libraries[1].first);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[2].first);

    // ... but check that the hooks manager was not updated with the incorrect
    // names.
    hooks_libraries.clear();
    hooks_libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(1, hooks_libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, hooks_libraries[0]);
}

// Check that if hooks-libraries contains invalid syntax, it is detected.
TEST_F(ParseConfigTest, invalidSyntaxHooksLibraries) {

    // Element holds a mixture of (valid) maps and non-maps.
    string config1 = "{ \"hooks-libraries\": [ "
        "{ \"library\": \"/opt/lib/lib1\" }, "
        "\"/opt/lib/lib2\" "
        "] }";
    string error1 = "one or more entries in the hooks-libraries list is not"
                    " a map";

    int rcode = parseConfiguration(config1);
    ASSERT_NE(0, rcode);
    EXPECT_TRUE(error_text_.find(error1) != string::npos) <<
        "Error text returned from parse failure is " << error_text_;

    // Element holds valid maps, except one where the library element is not
    // a string.
    string config2 = "{ \"hooks-libraries\": [ "
        "{ \"library\": \"/opt/lib/lib1\" }, "
        "{ \"library\": 123 } "
        "] }";
    string error2 = "value of 'library' element is not a string giving"
                    " the path to a hooks library";

    rcode = parseConfiguration(config2);
    ASSERT_NE(0, rcode);
    EXPECT_TRUE(error_text_.find(error2) != string::npos) <<
        "Error text returned from parse failure is " << error_text_;

    // Element holds valid maps, except one where the library element is the
    // empty string.
    string config3 = "{ \"hooks-libraries\": [ "
        "{ \"library\": \"/opt/lib/lib1\" }, "
        "{ \"library\": \"\" } "
        "] }";
    string error3 = "value of 'library' element must not be blank";

    rcode = parseConfiguration(config3);
    ASSERT_NE(0, rcode);
    EXPECT_TRUE(error_text_.find(error3) != string::npos) <<
        "Error text returned from parse failure is " << error_text_;

    // Element holds valid maps, except one where the library element is all
    // spaces.
    string config4 = "{ \"hooks-libraries\": [ "
        "{ \"library\": \"/opt/lib/lib1\" }, "
        "{ \"library\": \"      \" } "
        "] }";
    string error4 = "value of 'library' element must not be blank";

    rcode = parseConfiguration(config4);
    ASSERT_NE(0, rcode);
    EXPECT_TRUE(error_text_.find(error3) != string::npos) <<
        "Error text returned from parse failure is " << error_text_;

    // Element holds valid maps, except one that does not contain a
    // 'library' element.
    string config5 = "{ \"hooks-libraries\": [ "
        "{ \"library\": \"/opt/lib/lib1\" }, "
        "{ \"parameters\": { \"alpha\": 123 } }, "
        "{ \"library\": \"/opt/lib/lib2\" } "
        "] }";
    string error5 = "one or more hooks-libraries elements are missing the"
                    " name of the library";

    rcode = parseConfiguration(config5);
    ASSERT_NE(0, rcode);
    EXPECT_TRUE(error_text_.find(error5) != string::npos) <<
        "Error text returned from parse failure is " << error_text_;
}

// Check that some parameters may have configuration parameters configured.
TEST_F(ParseConfigTest, HooksLibrariesParameters) {
    // Check that no libraries are currently loaded
    vector<string> hooks_libraries = HooksManager::getLibraryNames();
    EXPECT_TRUE(hooks_libraries.empty());

    // Configuration string.  This contains an invalid library which should
    // trigger an error in the "build" stage.
    const std::string config = setHooksLibrariesConfig(CALLOUT_LIBRARY_1,
                                                       CALLOUT_LIBRARY_2,
                                                       CALLOUT_PARAMS_LIBRARY);

    // Verify that the configuration fails to parse. (Syntactically it's OK,
    // but the library is invalid).
    const int rcode = parseConfiguration(config);
    ASSERT_EQ(0, rcode);

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected =
                    Element::fromJSON(config)->get("hooks-libraries"));
    ASSERT_TRUE(expected);
    const HooksConfig& cfg =
        CfgMgr::instance().getStagingCfg()->getHooksConfig();
    runToElementTest<HooksConfig>(expected, cfg);

    // Check that the parser recorded the names.
    isc::hooks::HookLibsCollection libraries = getLibraries();
    ASSERT_EQ(3, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0].first);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[1].first);
    EXPECT_EQ(CALLOUT_PARAMS_LIBRARY, libraries[2].first);

    // Also, check that the third library has its parameters specified.
    // They were set by setHooksLibrariesConfig. The first has no
    // parameters, the second one has an empty map and the third
    // one has actual parameters.
    EXPECT_FALSE(libraries[0].second);
    EXPECT_TRUE(libraries[1].second);
    ASSERT_TRUE(libraries[2].second);

    // Ok, get the parameter for the third library.
    ConstElementPtr params = libraries[2].second;

    // It must be a map.
    ASSERT_EQ(Element::map, params->getType());

    // This map should have 3 parameters:
    // - svalue (and will expect its value to be "string value")
    // - ivalue (and will expect its value to be 42)
    // - bvalue (and will expect its value to be true)
    ConstElementPtr svalue = params->get("svalue");
    ConstElementPtr ivalue = params->get("ivalue");
    ConstElementPtr bvalue = params->get("bvalue");

    // There should be no extra parameters.
    EXPECT_FALSE(params->get("nonexistent"));

    ASSERT_TRUE(svalue);
    ASSERT_TRUE(ivalue);
    ASSERT_TRUE(bvalue);

    ASSERT_EQ(Element::string, svalue->getType());
    ASSERT_EQ(Element::integer, ivalue->getType());
    ASSERT_EQ(Element::boolean, bvalue->getType());

    EXPECT_EQ("string value", svalue->stringValue());
    EXPECT_EQ(42, ivalue->intValue());
    EXPECT_EQ(true, bvalue->boolValue());
}

/// @brief Checks that a valid, enabled D2 client configuration works correctly.
TEST_F(ParseConfigTest, validD2Config) {

    // Configuration string containing valid values.
    std::string config_str =
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.0.2.0\", "
        "     \"server-port\" : 3432, "
        "     \"sender-ip\" : \"192.0.2.1\", "
        "     \"sender-port\" : 3433, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : \"when-present\", "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\", "
        "     \"hostname-char-set\" : \"[^A-Z]\", "
        "     \"hostname-char-replacement\" : \"*\", "
        "     \"user-context\": { \"foo\": \"bar\" } "
        "    }"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config_str);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that DHCP-DDNS is enabled and we can fetch the configuration.
    EXPECT_TRUE(CfgMgr::instance().ddnsEnabled());
    D2ClientConfigPtr d2_client_config;
    ASSERT_NO_THROW(d2_client_config = CfgMgr::instance().getD2ClientConfig());
    ASSERT_TRUE(d2_client_config);

    // Verify that the configuration values are as expected.
    EXPECT_TRUE(d2_client_config->getEnableUpdates());
    EXPECT_EQ("192.0.2.0", d2_client_config->getServerIp().toText());
    EXPECT_EQ(3432, d2_client_config->getServerPort());
    EXPECT_EQ(dhcp_ddns::NCR_UDP, d2_client_config->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::FMT_JSON, d2_client_config->getNcrFormat());
    EXPECT_TRUE(d2_client_config->getOverrideNoUpdate());
    EXPECT_TRUE(d2_client_config->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_WHEN_PRESENT, d2_client_config->getReplaceClientNameMode());
    EXPECT_EQ("test.prefix", d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("test.suffix.", d2_client_config->getQualifyingSuffix());
    ASSERT_TRUE(d2_client_config->getContext());
    EXPECT_EQ("{ \"foo\": \"bar\" }", d2_client_config->getContext()->str());

    // Verify that the configuration object unparses.
    ConstElementPtr expected;
    ASSERT_NO_THROW(expected = Element::fromJSON(config_str)->get("dhcp-ddns"));
    ASSERT_TRUE(expected);
    runToElementTest<D2ClientConfig>(expected, *d2_client_config);

    // Another valid Configuration string.
    // This one is disabled, has IPV6 server ip, control flags false,
    // empty prefix/suffix
    std::string config_str2 =
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : false, "
        "     \"server-ip\" : \"2001:db8::\", "
        "     \"server-port\" : 43567, "
        "     \"sender-ip\" : \"2001:db8::1\", "
        "     \"sender-port\" : 3433, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : false, "
        "     \"override-client-update\" : false, "
        "     \"replace-client-name\" : \"never\", "
        "     \"generated-prefix\" : \"\", "
        "     \"qualifying-suffix\" : \"\", "
        "     \"hostname-char-set\" : \"[^A-Z]\", "
        "     \"hostname-char-replacement\" : \"*\", "
        "     \"user-context\": { \"foo\": \"bar\" } "
        "    }"
        "}";

    // Verify that the configuration string parses.
    rcode = parseConfiguration(config_str2);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that DHCP-DDNS is disabled and we can fetch the configuration.
    EXPECT_FALSE(CfgMgr::instance().ddnsEnabled());
    ASSERT_NO_THROW(d2_client_config = CfgMgr::instance().getD2ClientConfig());
    ASSERT_TRUE(d2_client_config);

    // Verify that the configuration values are as expected.
    EXPECT_FALSE(d2_client_config->getEnableUpdates());
    EXPECT_EQ("2001:db8::", d2_client_config->getServerIp().toText());
    EXPECT_EQ(43567, d2_client_config->getServerPort());
    EXPECT_EQ(dhcp_ddns::NCR_UDP, d2_client_config->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::FMT_JSON, d2_client_config->getNcrFormat());
    EXPECT_FALSE(d2_client_config->getOverrideNoUpdate());
    EXPECT_FALSE(d2_client_config->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, d2_client_config->getReplaceClientNameMode());
    EXPECT_EQ("", d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("", d2_client_config->getQualifyingSuffix());
    ASSERT_TRUE(d2_client_config->getContext());
    EXPECT_EQ("{ \"foo\": \"bar\" }", d2_client_config->getContext()->str());

    ASSERT_NO_THROW(expected = Element::fromJSON(config_str2)->get("dhcp-ddns"));
    ASSERT_TRUE(expected);
    runToElementTest<D2ClientConfig>(expected, *d2_client_config);
}

/// @brief Checks that D2 client can be configured with enable flag of
/// false only.
TEST_F(ParseConfigTest, validDisabledD2Config) {

    // Configuration string.  This defines a disabled D2 client config.
    std::string config_str =
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : false"
        "    }"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config_str);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that DHCP-DDNS is disabled.
    EXPECT_FALSE(CfgMgr::instance().ddnsEnabled());

    // Make sure fetched config agrees.
    D2ClientConfigPtr d2_client_config;
    ASSERT_NO_THROW(d2_client_config = CfgMgr::instance().getD2ClientConfig());
    EXPECT_TRUE(d2_client_config);
    EXPECT_FALSE(d2_client_config->getEnableUpdates());
}

/// @brief Checks that given a partial configuration, parser supplies
/// default values
TEST_F(ParseConfigTest, parserDefaultsD2Config) {

    // Configuration string.  This defines an enabled D2 client config
    // with the mandatory parameter in such a case, all other parameters
    // are optional and their default values will be used.
    std::string config_str =
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config_str);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Verify that DHCP-DDNS is enabled.
    EXPECT_TRUE(CfgMgr::instance().ddnsEnabled());

    // Make sure fetched config is correct.
    D2ClientConfigPtr d2_client_config;
    ASSERT_NO_THROW(d2_client_config = CfgMgr::instance().getD2ClientConfig());
    EXPECT_TRUE(d2_client_config);
    EXPECT_TRUE(d2_client_config->getEnableUpdates());
    EXPECT_EQ(D2ClientConfig::DFT_SERVER_IP,
              d2_client_config->getServerIp().toText());
    EXPECT_EQ(D2ClientConfig::DFT_SERVER_PORT,
              d2_client_config->getServerPort());
    EXPECT_EQ(dhcp_ddns::stringToNcrProtocol(D2ClientConfig::DFT_NCR_PROTOCOL),
              d2_client_config->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::stringToNcrFormat(D2ClientConfig::DFT_NCR_FORMAT),
              d2_client_config->getNcrFormat());
    EXPECT_EQ(D2ClientConfig::DFT_OVERRIDE_NO_UPDATE,
              d2_client_config->getOverrideNoUpdate());
    EXPECT_EQ(D2ClientConfig::DFT_OVERRIDE_CLIENT_UPDATE,
              d2_client_config->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::
              stringToReplaceClientNameMode(D2ClientConfig::
                                            DFT_REPLACE_CLIENT_NAME_MODE),
              d2_client_config->getReplaceClientNameMode());
    EXPECT_EQ(D2ClientConfig::DFT_GENERATED_PREFIX,
              d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("test.suffix.",
              d2_client_config->getQualifyingSuffix());
}


/// @brief Check various invalid D2 client configurations.
TEST_F(ParseConfigTest, invalidD2Config) {
    std::string invalid_configs[] = {
        // Must supply qualifying-suffix when updates are enabled
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true"
        "    }"
        "}",
        // Invalid server ip value
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"x192.0.2.0\", "
        "     \"server-port\" : 53001, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Unknown protocol
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.0.2.0\", "
        "     \"server-port\" : 53001, "
        "     \"ncr-protocol\" : \"Bogus\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Unsupported protocol
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.0.2.0\", "
        "     \"server-port\" : 53001, "
        "     \"ncr-protocol\" : \"TCP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Unknown format
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.0.2.0\", "
        "     \"server-port\" : 53001, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"Bogus\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Invalid Port
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.0.2.0\", "
        "     \"server-port\" : \"bogus\", "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Mismatched server and sender IPs
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"192.0.2.0\", "
        "     \"server-port\" : 3432, "
        "     \"sender-ip\" : \"3001::5\", "
        "     \"sender-port\" : 3433, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Identical server and sender IP/port
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"3001::5\", "
        "     \"server-port\" : 3433, "
        "     \"sender-ip\" : \"3001::5\", "
        "     \"sender-port\" : 3433, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // Invalid replace-client-name value
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true, "
        "     \"server-ip\" : \"3001::5\", "
        "     \"server-port\" : 3433, "
        "     \"sender-ip\" : \"3001::5\", "
        "     \"sender-port\" : 3434, "
        "     \"max-queue-size\" : 2048, "
        "     \"ncr-protocol\" : \"UDP\", "
        "     \"ncr-format\" : \"JSON\", "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : \"BOGUS\", "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
        "    }"
        "}",
        // stop
        ""
    };

    // Fetch the original config.
    D2ClientConfigPtr original_config;
    ASSERT_NO_THROW(original_config = CfgMgr::instance().getD2ClientConfig());

    // Iterate through the invalid configuration strings, attempting to
    // parse each one.  They should fail to parse, but fail gracefully.
    D2ClientConfigPtr current_config;
    int i = 0;
    while (!invalid_configs[i].empty()) {
        // Verify that the configuration string parses without throwing.
        int rcode = parseConfiguration(invalid_configs[i]);

        // Verify that parse result indicates a parsing error.
        ASSERT_TRUE(rcode != 0) << "Invalid config #: " << i
                                << " should not have passed!";

        // Verify that the "official" config still matches the original config.
        ASSERT_NO_THROW(current_config =
                        CfgMgr::instance().getD2ClientConfig());
        EXPECT_EQ(*original_config, *current_config);
        ++i;
    }
}

/// @brief Checks that a valid relay info structure for IPv4 can be handled
TEST_F(ParseConfigTest, validRelayInfo4) {

    // Relay information structure. Very simple for now.
    std::string config_str =
        "    {"
        "     \"ip-address\" : \"192.0.2.1\""
        "    }";
    ElementPtr json = Element::fromJSON(config_str);

    // Create an "empty" RelayInfo to hold the parsed result.
    Network::RelayInfoPtr result(new Network::RelayInfo());

    RelayInfoParser parser(Option::V4);

    EXPECT_NO_THROW(parser.parse(result, json));
    EXPECT_TRUE(result->containsAddress(IOAddress("192.0.2.1")));
}

/// @brief Checks that a bogus relay info structure for IPv4 is rejected.
TEST_F(ParseConfigTest, bogusRelayInfo4) {

    // Invalid config (wrong family type of the ip-address field)
    std::string config_str_bogus1 =
        "    {"
        "     \"ip-address\" : \"2001:db8::1\""
        "    }";
    ElementPtr json_bogus1 = Element::fromJSON(config_str_bogus1);

    // Invalid config (that thing is not an IPv4 address)
    std::string config_str_bogus2 =
        "    {"
        "     \"ip-address\" : \"256.345.123.456\""
        "    }";
    ElementPtr json_bogus2 = Element::fromJSON(config_str_bogus2);

    // Invalid config (ip-address is mandatory)
    std::string config_str_bogus3 =
        "    {"
        "    }";
    ElementPtr json_bogus3 = Element::fromJSON(config_str_bogus3);

    // Create an "empty" RelayInfo to hold the parsed result.
    Network::RelayInfoPtr result(new Network::RelayInfo());

    RelayInfoParser parser(Option::V4);

    // wrong family type
    EXPECT_THROW(parser.parse(result, json_bogus1), DhcpConfigError);

    // Too large byte values in pseudo-IPv4 addr
    EXPECT_THROW(parser.parse(result, json_bogus2), DhcpConfigError);

    // Mandatory ip-address is missing. What a pity.
    EXPECT_THROW(parser.parse(result, json_bogus2), DhcpConfigError);
}

/// @brief Checks that a valid relay info structure for IPv6 can be handled
TEST_F(ParseConfigTest, validRelayInfo6) {

    // Relay information structure. Very simple for now.
    std::string config_str =
        "    {"
        "     \"ip-address\" : \"2001:db8::1\""
        "    }";
    ElementPtr json = Element::fromJSON(config_str);

    // Create an "empty" RelayInfo to hold the parsed result.
    Network::RelayInfoPtr result(new Network::RelayInfo());

    RelayInfoParser parser(Option::V6);

    EXPECT_NO_THROW(parser.parse(result, json));
    EXPECT_TRUE(result->containsAddress(IOAddress("2001:db8::1")));
}

/// @brief Checks that a valid relay info structure for IPv6 can be handled
TEST_F(ParseConfigTest, bogusRelayInfo6) {

    // Invalid config (wrong family type of the ip-address field
    std::string config_str_bogus1 =
        "    {"
        "     \"ip-address\" : \"192.0.2.1\""
        "    }";
    ElementPtr json_bogus1 = Element::fromJSON(config_str_bogus1);

    // That IPv6 address doesn't look right
    std::string config_str_bogus2 =
        "    {"
        "     \"ip-address\" : \"2001:db8:::4\""
        "    }";
    ElementPtr json_bogus2 = Element::fromJSON(config_str_bogus2);

    // Missing mandatory ip-address field.
    std::string config_str_bogus3 =
        "    {"
        "    }";
    ElementPtr json_bogus3 = Element::fromJSON(config_str_bogus3);

    // Create an "empty" RelayInfo to hold the parsed result.
    Network::RelayInfoPtr result(new Network::RelayInfo());

    RelayInfoParser parser(Option::V6);

    // Negative scenario (wrong family type)
    EXPECT_THROW(parser.parse(result, json_bogus1), DhcpConfigError);

    // Looks like IPv6 address, but has too many colons
    EXPECT_THROW(parser.parse(result, json_bogus2), DhcpConfigError);

    // Mandatory ip-address is missing. What a pity.
    EXPECT_THROW(parser.parse(result, json_bogus3), DhcpConfigError);
}

// This test verifies that it is possible to parse an IPv4 subnet for which
// only mandatory parameters are specified without setting the defaults.
TEST_F(ParseConfigTest, defaultSubnet4) {
    std::string config =
        "{"
        "    \"subnet4\": [ {"
        "        \"subnet\": \"192.0.2.0/24\","
        "        \"id\": 123"
        "    } ]"
        "}";

    int rcode = parseConfiguration(config, false, false);
    ASSERT_EQ(0, rcode);

    auto subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getSubnet(123);
    ASSERT_TRUE(subnet);

    EXPECT_TRUE(subnet->hasFetchGlobalsFn());

    EXPECT_TRUE(subnet->getIface().unspecified());
    EXPECT_TRUE(subnet->getIface().empty());

    EXPECT_TRUE(subnet->getClientClass().unspecified());
    EXPECT_TRUE(subnet->getClientClass().empty());

    EXPECT_TRUE(subnet->getValid().unspecified());
    EXPECT_EQ(0, subnet->getValid().get());

    EXPECT_TRUE(subnet->getT1().unspecified());
    EXPECT_EQ(0, subnet->getT1().get());

    EXPECT_TRUE(subnet->getT2().unspecified());
    EXPECT_EQ(0, subnet->getT2().get());

    EXPECT_TRUE(subnet->getHostReservationMode().unspecified());
    EXPECT_EQ(Network::HR_ALL, subnet->getHostReservationMode().get());

    EXPECT_TRUE(subnet->getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(subnet->getCalculateTeeTimes().get());

    EXPECT_TRUE(subnet->getT1Percent().unspecified());
    EXPECT_EQ(0.0, subnet->getT1Percent().get());

    EXPECT_TRUE(subnet->getT2Percent().unspecified());
    EXPECT_EQ(0.0, subnet->getT2Percent().get());

    EXPECT_TRUE(subnet->getMatchClientId().unspecified());
    EXPECT_TRUE(subnet->getMatchClientId().get());

    EXPECT_TRUE(subnet->getAuthoritative().unspecified());
    EXPECT_FALSE(subnet->getAuthoritative().get());

    EXPECT_TRUE(subnet->getSiaddr().unspecified());
    EXPECT_TRUE(subnet->getSiaddr().get().isV4Zero());

    EXPECT_TRUE(subnet->getSname().unspecified());
    EXPECT_TRUE(subnet->getSname().empty());

    EXPECT_TRUE(subnet->getFilename().unspecified());
    EXPECT_TRUE(subnet->getFilename().empty());

    EXPECT_FALSE(subnet->get4o6().enabled());

    EXPECT_TRUE(subnet->get4o6().getIface4o6().unspecified());
    EXPECT_TRUE(subnet->get4o6().getIface4o6().empty());

    EXPECT_TRUE(subnet->get4o6().getSubnet4o6().unspecified());
    EXPECT_TRUE(subnet->get4o6().getSubnet4o6().get().first.isV6Zero());
    EXPECT_EQ(128, subnet->get4o6().getSubnet4o6().get().second);
}

// This test verifies that it is possible to parse an IPv6 subnet for which
// only mandatory parameters are specified without setting the defaults.
TEST_F(ParseConfigTest, defaultSubnet6) {
    std::string config =
        "{"
        "    \"subnet6\": [ {"
        "        \"subnet\": \"2001:db8:1::/64\","
        "        \"id\": 123"
        "    } ]"
        "}";

    int rcode = parseConfiguration(config, true, false);
    ASSERT_EQ(0, rcode);

    auto subnet = CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getSubnet(123);
    ASSERT_TRUE(subnet);

    EXPECT_TRUE(subnet->hasFetchGlobalsFn());

    EXPECT_TRUE(subnet->getIface().unspecified());
    EXPECT_TRUE(subnet->getIface().empty());

    EXPECT_TRUE(subnet->getClientClass().unspecified());
    EXPECT_TRUE(subnet->getClientClass().empty());

    EXPECT_TRUE(subnet->getValid().unspecified());
    EXPECT_EQ(0, subnet->getValid().get());

    EXPECT_TRUE(subnet->getT1().unspecified());
    EXPECT_EQ(0, subnet->getT1().get());

    EXPECT_TRUE(subnet->getT2().unspecified());
    EXPECT_EQ(0, subnet->getT2().get());

    EXPECT_TRUE(subnet->getHostReservationMode().unspecified());
    EXPECT_EQ(Network::HR_ALL, subnet->getHostReservationMode().get());

    EXPECT_TRUE(subnet->getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(subnet->getCalculateTeeTimes().get());

    EXPECT_TRUE(subnet->getT1Percent().unspecified());
    EXPECT_EQ(0.0, subnet->getT1Percent().get());

    EXPECT_TRUE(subnet->getT2Percent().unspecified());
    EXPECT_EQ(0.0, subnet->getT2Percent().get());

    EXPECT_TRUE(subnet->getPreferred().unspecified());
    EXPECT_EQ(0, subnet->getPreferred().get());

    EXPECT_TRUE(subnet->getRapidCommit().unspecified());
    EXPECT_FALSE(subnet->getRapidCommit().get());
}

// This test verifies that it is possible to parse an IPv4 shared network
// for which only mandatory parameter is specified without setting the
// defaults.
TEST_F(ParseConfigTest, defaultSharedNetwork4) {
    std::string config =
        "{"
        "    \"shared-networks\": [ {"
        "        \"name\": \"frog\""
        "    } ]"
        "}";

    int rcode = parseConfiguration(config, false, false);
    ASSERT_EQ(0, rcode);

    auto network =
        CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->getByName("frog");
    ASSERT_TRUE(network);

    EXPECT_TRUE(network->hasFetchGlobalsFn());

    EXPECT_TRUE(network->getIface().unspecified());
    EXPECT_TRUE(network->getIface().empty());

    EXPECT_TRUE(network->getClientClass().unspecified());
    EXPECT_TRUE(network->getClientClass().empty());

    EXPECT_TRUE(network->getValid().unspecified());
    EXPECT_EQ(0, network->getValid().get());

    EXPECT_TRUE(network->getT1().unspecified());
    EXPECT_EQ(0, network->getT1().get());

    EXPECT_TRUE(network->getT2().unspecified());
    EXPECT_EQ(0, network->getT2().get());

    EXPECT_TRUE(network->getHostReservationMode().unspecified());
    EXPECT_EQ(Network::HR_ALL, network->getHostReservationMode().get());

    EXPECT_TRUE(network->getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(network->getCalculateTeeTimes().get());

    EXPECT_TRUE(network->getT1Percent().unspecified());
    EXPECT_EQ(0.0, network->getT1Percent().get());

    EXPECT_TRUE(network->getT2Percent().unspecified());
    EXPECT_EQ(0.0, network->getT2Percent().get());

    EXPECT_TRUE(network->getMatchClientId().unspecified());
    EXPECT_TRUE(network->getMatchClientId().get());

    EXPECT_TRUE(network->getAuthoritative().unspecified());
    EXPECT_FALSE(network->getAuthoritative().get());
}

// This test verifies that it is possible to parse an IPv6 shared network
// for which only mandatory parameter is specified without setting the
// defaults.
TEST_F(ParseConfigTest, defaultSharedNetwork6) {
    std::string config =
        "{"
        "    \"shared-networks\": [ {"
        "        \"name\": \"frog\""
        "    } ]"
        "}";

    int rcode = parseConfiguration(config, true, false);
    ASSERT_EQ(0, rcode);

    auto network =
        CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks6()->getByName("frog");
    ASSERT_TRUE(network);

    EXPECT_TRUE(network->hasFetchGlobalsFn());

    EXPECT_TRUE(network->getIface().unspecified());
    EXPECT_TRUE(network->getIface().empty());

    EXPECT_TRUE(network->getClientClass().unspecified());
    EXPECT_TRUE(network->getClientClass().empty());

    EXPECT_TRUE(network->getValid().unspecified());
    EXPECT_EQ(0, network->getValid().get());

    EXPECT_TRUE(network->getT1().unspecified());
    EXPECT_EQ(0, network->getT1().get());

    EXPECT_TRUE(network->getT2().unspecified());
    EXPECT_EQ(0, network->getT2().get());

    EXPECT_TRUE(network->getHostReservationMode().unspecified());
    EXPECT_EQ(Network::HR_ALL, network->getHostReservationMode().get());

    EXPECT_TRUE(network->getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(network->getCalculateTeeTimes().get());

    EXPECT_TRUE(network->getT1Percent().unspecified());
    EXPECT_EQ(0.0, network->getT1Percent().get());

    EXPECT_TRUE(network->getT2Percent().unspecified());
    EXPECT_EQ(0.0, network->getT2Percent().get());

    EXPECT_TRUE(network->getPreferred().unspecified());
    EXPECT_EQ(0, network->getPreferred().get());

    EXPECT_TRUE(network->getRapidCommit().unspecified());
    EXPECT_FALSE(network->getRapidCommit().get());
}

// There's no test for ControlSocketParser, as it is tested in the DHCPv4 code
// (see CtrlDhcpv4SrvTest.commandSocketBasic in
// src/bin/dhcp4/tests/ctrl_dhcp4_srv_unittest.cc).

};  // Anonymous namespace
