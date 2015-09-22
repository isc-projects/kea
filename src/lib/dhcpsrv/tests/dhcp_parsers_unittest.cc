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
#include <cc/data.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/tests/test_libraries.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>

#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>

#include <map>
#include <string>

using namespace std;
using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::hooks;

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


/// @brief Check BooleanParser basic functionality.
///
/// Verifies that the parser:
/// 1. Does not allow empty for storage.
/// 2. Rejects a non-boolean element.
/// 3. Builds with a valid true value.
/// 4. Bbuils with a valid false value.
/// 5. Updates storage upon commit.
TEST_F(DhcpParserTest, booleanParserTest) {

    const std::string name = "boolParm";

    // Verify that parser does not allow empty for storage.
    BooleanStoragePtr bs;
    EXPECT_THROW(BooleanParser(name, bs), isc::dhcp::DhcpConfigError);

    // Construct parser for testing.
    BooleanStoragePtr storage(new BooleanStorage());
    BooleanParser parser(name, storage);

    // Verify that parser with rejects a non-boolean element.
    ElementPtr wrong_element = Element::create("I am a string");
    EXPECT_THROW(parser.build(wrong_element), isc::BadValue);

    // Verify that parser will build with a valid true value.
    bool test_value = true;
    ElementPtr element = Element::create(test_value);
    ASSERT_NO_THROW(parser.build(element));

    // Verify that commit updates storage.
    bool actual_value = !test_value;
    parser.commit();
    EXPECT_NO_THROW((actual_value = storage->getParam(name)));
    EXPECT_EQ(test_value, actual_value);

    // Verify that parser will build with a valid false value.
    test_value = false;
    element->setValue(test_value);
    EXPECT_NO_THROW(parser.build(element));

    // Verify that commit updates storage.
    actual_value = !test_value;
    parser.commit();
    EXPECT_NO_THROW((actual_value = storage->getParam(name)));
    EXPECT_EQ(test_value, actual_value);
}

/// @brief Check StringParser basic functionality
///
/// Verifies that the parser:
/// 1. Does not allow empty for storage.
/// 2. Builds with a nont string value.
/// 3. Builds with a string value.
/// 4. Updates storage upon commit.
TEST_F(DhcpParserTest, stringParserTest) {

    const std::string name = "strParm";

    // Verify that parser does not allow empty for storage.
    StringStoragePtr bs;
    EXPECT_THROW(StringParser(name, bs), isc::dhcp::DhcpConfigError);

    // Construct parser for testing.
    StringStoragePtr storage(new StringStorage());
    StringParser parser(name, storage);

    // Verify that parser with accepts a non-string element.
    ElementPtr element = Element::create(9999);
    EXPECT_NO_THROW(parser.build(element));

    // Verify that commit updates storage.
    parser.commit();
    std::string actual_value;
    EXPECT_NO_THROW((actual_value = storage->getParam(name)));
    EXPECT_EQ("9999", actual_value);

    // Verify that parser will build with a string value.
    const std::string test_value = "test value";
    element = Element::create(test_value);
    ASSERT_NO_THROW(parser.build(element));

    // Verify that commit updates storage.
    parser.commit();
    EXPECT_NO_THROW((actual_value = storage->getParam(name)));
    EXPECT_EQ(test_value, actual_value);
}

/// @brief Check Uint32Parser basic functionality
///
/// Verifies that the parser:
/// 1. Does not allow empty for storage.
/// 2. Rejects a non-integer element.
/// 3. Rejects a negative value.
/// 4. Rejects too large a value.
/// 5. Builds with value of zero.
/// 6. Builds with a value greater than zero.
/// 7. Updates storage upon commit.
TEST_F(DhcpParserTest, uint32ParserTest) {

    const std::string name = "intParm";

    // Verify that parser does not allow empty for storage.
    Uint32StoragePtr bs;
    EXPECT_THROW(Uint32Parser(name, bs), isc::dhcp::DhcpConfigError);

    // Construct parser for testing.
    Uint32StoragePtr storage(new Uint32Storage());
    Uint32Parser parser(name, storage);

    // Verify that parser with rejects a non-interger element.
    ElementPtr wrong_element = Element::create("I am a string");
    EXPECT_THROW(parser.build(wrong_element), isc::BadValue);

    // Verify that parser with rejects a negative value.
    ElementPtr int_element = Element::create(-1);
    EXPECT_THROW(parser.build(int_element), isc::BadValue);

    // Verify that parser with rejects too large a value provided we are on
    // 64-bit platform.
    if (sizeof(long) > sizeof(uint32_t)) {
        long max = (long)(std::numeric_limits<uint32_t>::max()) + 1;
        int_element->setValue(max);
        EXPECT_THROW(parser.build(int_element), isc::BadValue);
    }

    // Verify that parser will build with value of zero.
    int test_value = 0;
    int_element->setValue((long)test_value);
    ASSERT_NO_THROW(parser.build(int_element));

    // Verify that commit updates storage.
    parser.commit();
    uint32_t actual_value = 0;
    EXPECT_NO_THROW((actual_value = storage->getParam(name)));
    EXPECT_EQ(test_value, actual_value);

    // Verify that parser will build with a valid positive value.
    test_value = 77;
    int_element->setValue((long)test_value);
    ASSERT_NO_THROW(parser.build(int_element));

    // Verify that commit updates storage.
    parser.commit();
    EXPECT_NO_THROW((actual_value = storage->getParam(name)));
    EXPECT_EQ(test_value, actual_value);
}

/// @brief Check MACSourcesListConfigParser  basic functionality
///
/// Verifies that the parser:
/// 1. Does not allow empty for storage.
/// 2. Does not allow name other than "mac-sources"
/// 3. Parses list of mac sources and adds them to CfgMgr
TEST_F(DhcpParserTest, MacSourcesListConfigParserTest) {

    const std::string valid_name = "mac-sources";
    const std::string bogus_name = "bogus-name";

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    // Verify that parser constructor fails if parameter name isn't "mac-sources"
    EXPECT_THROW(MACSourcesListConfigParser(bogus_name, parser_context),
                 isc::BadValue);

    // That's an equivalent of the following snippet:
    // "mac-sources: [ \"duid\", \"ipv6\" ]";
    ElementPtr config = Element::createList();
    config->add(Element::create("duid"));
    config->add(Element::create("ipv6-link-local"));

    boost::scoped_ptr<MACSourcesListConfigParser>
        parser(new MACSourcesListConfigParser(valid_name, parser_context));

    // This should parse the configuration and add eth0 and eth1 to the list
    // of interfaces that server should listen on.
    EXPECT_NO_THROW(parser->build(config));
    EXPECT_NO_THROW(parser->commit());

    // Use CfgMgr instance to check if eth0 and eth1 was added, and that
    // eth2 was not added.
    SrvConfigPtr cfg = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(cfg);
    CfgMACSources configured_sources =  cfg->getMACSources().get();

    ASSERT_EQ(2, configured_sources.size());
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_DUID, configured_sources[0]);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL, configured_sources[1]);
}

/// @brief Test Fixture class which provides basic structure for testing
/// configuration parsing.  This is essentially the same structure provided
/// by dhcp servers.
class ParseConfigTest : public ::testing::Test {
public:
    /// @brief Constructor
    ParseConfigTest() {
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
    /// @return returns an ConstElementPtr containing the numeric result
    /// code and outcome comment.
    isc::data::ConstElementPtr parseElementSet(isc::data::ConstElementPtr
                                           config_set) {
        // Answer will hold the result.
        ConstElementPtr answer;
        if (!config_set) {
            answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
            return (answer);
        }

        // option parsing must be done last, so save it if we hit if first
        ParserPtr option_parser;

        ConfigPair config_pair;
        try {
            // Iterate over the config elements.
            const std::map<std::string, ConstElementPtr>& values_map =
                                                      config_set->mapValue();
            BOOST_FOREACH(config_pair, values_map) {
                // Create the parser based on element name.
                ParserPtr parser(createConfigParser(config_pair.first));
                // Options must be parsed last
                if (config_pair.first == "option-data") {
                    option_parser = parser;
                } else {
                    // Anything else  we can call build straight away.
                    parser->build(config_pair.second);
                    parser->commit();
                }
            }

            // The option values parser is the next one to be run.
            std::map<std::string, ConstElementPtr>::const_iterator
                                option_config = values_map.find("option-data");
            if (option_config != values_map.end()) {
                option_parser->build(option_config->second);
                option_parser->commit();
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

    /// @brief Create an element parser based on the element name.
    ///
    /// Creates a parser for the appropriate element and stores a pointer to it
    /// in the appropriate class variable.
    ///
    /// Note that the method currently it only supports option-defs, option-data
    /// and hooks-libraries.
    ///
    /// @param config_id is the name of the configuration element.
    ///
    /// @return returns a shared pointer to DhcpConfigParser.
    ///
    /// @throw throws NotImplemented if element name isn't supported.
    ParserPtr createConfigParser(const std::string& config_id) {
        ParserPtr parser;
        int family = parser_context_->universe_ == Option::V4 ?
            AF_INET : AF_INET6;
        if (config_id.compare("option-data") == 0) {
            parser.reset(new OptionDataListParser(config_id, CfgOptionPtr(),
                                                  family));

        } else if (config_id.compare("option-def") == 0) {
            parser.reset(new OptionDefListParser(config_id,
                                                 parser_context_));

        } else if (config_id.compare("hooks-libraries") == 0) {
            parser.reset(new HooksLibrariesParser(config_id));
            hooks_libraries_parser_ =
                boost::dynamic_pointer_cast<HooksLibrariesParser>(parser);
        } else if (config_id.compare("dhcp-ddns") == 0) {
            parser.reset(new D2ClientConfigParser(config_id));
        } else {
            isc_throw(NotImplemented,
                "Parser error: configuration parameter not supported: "
                << config_id);
        }

        return (parser);
    }

    /// @brief Convenience method for parsing a configuration
    ///
    /// Given a configuration string, convert it into Elements
    /// and parse them.
    /// @param config is the configuration string to parse
    ///
    /// @return retuns 0 if the configuration parsed successfully,
    /// non-zero otherwise failure.
    int parseConfiguration(const std::string& config) {
        int rcode_ = 1;
        // Turn config into elements.
        // Test json just to make sure its valid.
        ElementPtr json = Element::fromJSON(config);
        EXPECT_TRUE(json);
        if (json) {
            ConstElementPtr status = parseElementSet(json);
            ConstElementPtr comment = parseAnswer(rcode_, status);
            error_text_ = comment->stringValue();
            // If error was reported, the error string should contain
            // position of the data element which caused failure.
            if (rcode_ != 0) {
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
        parser_context_.reset(new ParserContext(Option::V6));

        // Ensure no hooks libraries are loaded.
        HooksManager::unloadLibraries();

        // Set it to minimal, disabled config
        D2ClientConfigPtr tmp(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(tmp);
    }

    /// @brief Parsers used in the parsing of the configuration
    ///
    /// Allows the tests to interrogate the state of the parsers (if required).
    boost::shared_ptr<HooksLibrariesParser> hooks_libraries_parser_;

    /// @brief Parser context - provides storage for options and definitions
    ParserContextPtr parser_context_;

    /// @brief Error string if the parsing failed
    std::string error_text_;
};

/// @brief Check Basic parsing of option definitions.
///
/// Note that this tests basic operation of the OptionDefinitionListParser and
/// OptionDefinitionParser.  It uses a simple configuration consisting of one
/// one definition and verifies that it is parsed and committed to storage
/// correctly.
TEST_F(ParseConfigTest, basicOptionDefTest) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0);


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
}

/// @brief Check Basic parsing of options.
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
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        " } ], "
        " \"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"code\": 100,"
        "    \"data\": \"192.0.2.0\","
        "    \"csv-format\": True"
        " } ]"
        "}";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0);

    // Verify that the option can be retrieved.
    OptionPtr opt_ptr = getOptionPtr("isc", 100);
    ASSERT_TRUE(opt_ptr);

    // Verify that the option definition is correct.
    std::string val = "type=00100, len=00004: 192.0.2.0 (ipv4-address)";

    EXPECT_EQ(val, opt_ptr->toText());
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
    parser_context_->universe_ = Option::V4;
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    OptionCustomPtr addr_opt = boost::dynamic_pointer_cast<
        OptionCustom>(getOptionPtr("dhcp4", 16));
    ASSERT_TRUE(addr_opt);
    EXPECT_EQ("192.0.2.0", addr_opt->readAddress().toText());

    // Explicitly enable csv-format.
    CfgMgr::instance().clear();
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"swap-server\","
        "    \"space\": \"dhcp4\","
        "    \"code\": 16,"
        "    \"csv-format\": True,"
        "    \"data\": \"192.0.2.0\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    addr_opt = boost::dynamic_pointer_cast<
        OptionCustom>(getOptionPtr("dhcp4", 16));
    ASSERT_TRUE(addr_opt);
    EXPECT_EQ("192.0.2.0", addr_opt->readAddress().toText());

    // Explicitly disable csv-format and use hex instead.
    CfgMgr::instance().clear();
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"swap-server\","
        "    \"space\": \"dhcp4\","
        "    \"code\": 16,"
        "    \"csv-format\": False,"
        "    \"data\": \"C0000200\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);

    // Verify that the option data is correct.
    addr_opt = boost::dynamic_pointer_cast<
        OptionCustom>(getOptionPtr("dhcp4", 16));
    ASSERT_TRUE(addr_opt);
    EXPECT_EQ("192.0.2.0", addr_opt->readAddress().toText());
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
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
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
        "    \"csv-format\": True,"
        "    \"data\": \"0\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_NE(0, rcode);

    CfgMgr::instance().clear();
    // The same test case as above, but for the data specified in hex should
    // be successful.
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 25000,"
        "    \"csv-format\": False,"
        "    \"data\": \"0\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    ASSERT_EQ(0, rcode);
    OptionPtr opt = getOptionPtr("dhcp6", 25000);
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getData().size());
    EXPECT_EQ(0, opt->getData()[0]);

    CfgMgr::instance().clear();
    // When csv-format is not specified, the parser will check if the definition
    // exists or not. Since there is no definition, the parser will accept the
    // data in hex.
    config =
        "{ \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 25000,"
        "    \"data\": \"123456\""
        " } ]"
        "}";
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    opt = getOptionPtr("dhcp6", 25000);
    ASSERT_TRUE(opt);
    ASSERT_EQ(3, opt->getData().size());
    EXPECT_EQ(0x12, opt->getData()[0]);
    EXPECT_EQ(0x34, opt->getData()[1]);
    EXPECT_EQ(0x56, opt->getData()[2]);
}

// This test verifies that the option name is not mandatory, if the option
// code has been specified.
TEST_F(ParseConfigTest, optionDataNoName) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"space\": \"dhcp6\","
        "    \"code\": 23,"
        "    \"csv-format\": True,"
        "    \"data\": \"2001:db8:1::1\""
        " } ]"
        "}";
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr("dhcp6", 23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::1", opt->getAddresses()[0].toText());
}

// This test verifies that the option code is not mandatory, if the option
// name has been specified.
TEST_F(ParseConfigTest, optionDataNoCode) {
    std::string config =
        "{ \"option-data\": [ {"
        "    \"space\": \"dhcp6\","
        "    \"name\": \"dns-servers\","
        "    \"csv-format\": True,"
        "    \"data\": \"2001:db8:1::1\""
        " } ]"
        "}";
    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr("dhcp6", 23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::1", opt->getAddresses()[0].toText());
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
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr("dhcp6", 23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::10", opt->getAddresses()[0].toText());

    CfgMgr::instance().clear();
    // This time using an option code.
    config =
        "{ \"option-data\": [ {"
        "    \"code\": 23,"
        "    \"data\": \"2001:db8:1::20\""
        " } ]"
        "}";
    rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    opt = boost::dynamic_pointer_cast<Option6AddrLst>(getOptionPtr("dhcp6",
                                                                   23));
    ASSERT_TRUE(opt);
    ASSERT_EQ(1, opt->getAddresses().size());
    EXPECT_EQ( "2001:db8:1::20", opt->getAddresses()[0].toText());
}

// This test verifies that the option data configuration with a minimal
// set of parameters works as expected when option definition is
// created in the configruation file.
TEST_F(ParseConfigTest, optionDataMinimalWithOptionDef) {
    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo-name\","
        "      \"code\": 2345,"
        "      \"type\": \"ipv6-address\","
        "      \"array\": True,"
        "      \"record-types\": \"\","
        "      \"space\": \"dhcp6\","
        "      \"encapsulate\": \"\""
        "  } ],"
        "  \"option-data\": [ {"
        "    \"name\": \"foo-name\","
        "    \"data\": \"2001:db8:1::10, 2001:db8:1::123\""
        " } ]"
        "}";

    int rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
        Option6AddrLst>(getOptionPtr("dhcp6", 2345));
    ASSERT_TRUE(opt);
    ASSERT_EQ(2, opt->getAddresses().size());
    EXPECT_EQ("2001:db8:1::10", opt->getAddresses()[0].toText());
    EXPECT_EQ("2001:db8:1::123", opt->getAddresses()[1].toText());

    CfgMgr::instance().clear();
    // Do the same test but now use an option code.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo-name\","
        "      \"code\": 2345,"
        "      \"type\": \"ipv6-address\","
        "      \"array\": True,"
        "      \"record-types\": \"\","
        "      \"space\": \"dhcp6\","
        "      \"encapsulate\": \"\""
        "  } ],"
        "  \"option-data\": [ {"
        "    \"code\": 2345,"
        "    \"data\": \"2001:db8:1::10, 2001:db8:1::123\""
        " } ]"
        "}";

    rcode = 0;
    ASSERT_NO_THROW(rcode = parseConfiguration(config));
    EXPECT_EQ(0, rcode);
    opt = boost::dynamic_pointer_cast<Option6AddrLst>(getOptionPtr("dhcp6",
                                                                   2345));
    ASSERT_TRUE(opt);
    ASSERT_EQ(2, opt->getAddresses().size());
    EXPECT_EQ("2001:db8:1::10", opt->getAddresses()[0].toText());
    EXPECT_EQ("2001:db8:1::123", opt->getAddresses()[1].toText());

}

};  // Anonymous namespace

/// The next set of tests check basic operation of the HooksLibrariesParser.


// Utility function for setting up the "hooks-libraries" configuration.
//
// Returns a hooks-libraries configuration element that contains zero to
// three libraries, depending on what arguments are supplied.
std::string
setHooksLibrariesConfig(const char* lib1 = NULL, const char* lib2 = NULL,
                        const char* lib3 = NULL) {
    const std::string quote("\"");
    const std::string comma_space(", ");

    std::string config = std::string("{ \"hooks-libraries\": [");
    if (lib1 != NULL) {
        config += (quote + std::string(lib1) + quote);
        if (lib2 != NULL) {
            config += (comma_space + quote + std::string(lib2) + quote);
            if (lib3 != NULL) {
                config += (comma_space + quote + std::string(lib3) + quote);
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

    // Check that the parser recorded nothing.
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_FALSE(changed);
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

    // Check that the parser recorded a single library.
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(changed);
    ASSERT_EQ(1, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0]);

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

    // Check that the parser recorded two libraries in the expected order.
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(changed);
    ASSERT_EQ(2, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0]);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[1]);

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

    // The previous test shows that the parser correctly recorded the two
    // libraries and that they loaded correctly.

    // Parse the string again.
    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // The list has not changed between the two parse operations and this is
    // what we should see.
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_FALSE(changed);
    ASSERT_EQ(2, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0]);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[1]);

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
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(changed);
    ASSERT_EQ(2, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[0]);
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[1]);

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

    // The list has changed, and this is what we should see.
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(changed);
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
    vector<string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_FALSE(changed);
    ASSERT_EQ(3, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0]);
    EXPECT_EQ(NOT_PRESENT_LIBRARY, libraries[1]);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[2]);

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
    vector<string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_FALSE(changed);
    ASSERT_EQ(3, libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, libraries[0]);
    EXPECT_EQ(NOT_PRESENT_LIBRARY, libraries[1]);
    EXPECT_EQ(CALLOUT_LIBRARY_2, libraries[2]);

    // ... but check that the hooks manager was not updated with the incorrect
    // names.
    hooks_libraries.clear();
    hooks_libraries = HooksManager::getLibraryNames();
    ASSERT_EQ(1, hooks_libraries.size());
    EXPECT_EQ(CALLOUT_LIBRARY_1, hooks_libraries[0]);
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
        "     \"always-include-fqdn\" : true, "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
        "     \"generated-prefix\" : \"test.prefix\", "
        "     \"qualifying-suffix\" : \"test.suffix.\" "
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
    EXPECT_TRUE(d2_client_config->getAlwaysIncludeFqdn());
    EXPECT_TRUE(d2_client_config->getOverrideNoUpdate());
    EXPECT_TRUE(d2_client_config->getOverrideClientUpdate());
    EXPECT_TRUE(d2_client_config->getReplaceClientName());
    EXPECT_EQ("test.prefix", d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("test.suffix.", d2_client_config->getQualifyingSuffix());

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
        "     \"always-include-fqdn\" : false, "
        "     \"override-no-update\" : false, "
        "     \"override-client-update\" : false, "
        "     \"replace-client-name\" : false, "
        "     \"generated-prefix\" : \"\", "
        "     \"qualifying-suffix\" : \"\" "
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
    EXPECT_FALSE(d2_client_config->getAlwaysIncludeFqdn());
    EXPECT_FALSE(d2_client_config->getOverrideNoUpdate());
    EXPECT_FALSE(d2_client_config->getOverrideClientUpdate());
    EXPECT_FALSE(d2_client_config->getReplaceClientName());
    EXPECT_EQ("", d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("", d2_client_config->getQualifyingSuffix());
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
    EXPECT_EQ(D2ClientConfig::DFT_ALWAYS_INCLUDE_FQDN,
              d2_client_config->getAlwaysIncludeFqdn());
    EXPECT_EQ(D2ClientConfig::DFT_OVERRIDE_NO_UPDATE,
              d2_client_config->getOverrideNoUpdate());
    EXPECT_EQ(D2ClientConfig::DFT_OVERRIDE_CLIENT_UPDATE,
              d2_client_config->getOverrideClientUpdate());
    EXPECT_EQ(D2ClientConfig::DFT_REPLACE_CLIENT_NAME,
              d2_client_config->getReplaceClientName());
    EXPECT_EQ(D2ClientConfig::DFT_GENERATED_PREFIX,
              d2_client_config->getGeneratedPrefix());
    EXPECT_EQ("test.suffix.",
              d2_client_config->getQualifyingSuffix());
}


/// @brief Check various invalid D2 client configurations.
TEST_F(ParseConfigTest, invalidD2Config) {
    std::string invalid_configs[] = {
        // Must supply at least enable-updates
        "{ \"dhcp-ddns\" :"
        "    {"
        "    }"
        "}",
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
        "     \"always-include-fqdn\" : true, "
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
        "     \"always-include-fqdn\" : true, "
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
        "     \"always-include-fqdn\" : true, "
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
        "     \"always-include-fqdn\" : true, "
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
        "     \"always-include-fqdn\" : true, "
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
        "     \"always-include-fqdn\" : true, "
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
        "     \"always-include-fqdn\" : true, "
        "     \"override-no-update\" : true, "
        "     \"override-client-update\" : true, "
        "     \"replace-client-name\" : true, "
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

/// @brief DHCP Configuration Parser Context test fixture.
class ParserContextTest : public ::testing::Test {
public:
    /// @brief Constructor
    ParserContextTest() { }

    /// @brief Check that the storages of the specific type hold the
    /// same value.
    ///
    /// This function assumes that the ref_values storage holds parameter
    /// called 'foo'.
    ///
    /// @param ref_values A storage holding reference value. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding value to be checked.
    /// @tparam ContainerType A type of the storage.
    template<typename ContainerType>
    void checkValueEq(const boost::shared_ptr<ContainerType>& ref_values,
                      const boost::shared_ptr<ContainerType>& values) {
        ASSERT_NO_THROW(values->getParam("foo"));
        EXPECT_EQ(ref_values->getParam("foo"), values->getParam("foo"));
    }

    /// @brief Check that the storages of the specific type hold the same
    /// position of the parameter.
    ///
    /// @param name A name of the parameter to check.
    /// @param ref_values A storage holding reference position. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding position to be checked.
    /// @tparam ContainerType A type of the storage.
    template<typename ContainerType>
    void checkPositionEq(const std::string& name,
                         const boost::shared_ptr<ContainerType>& ref_values,
                         const boost::shared_ptr<ContainerType>& values) {
        // Verify that the position is correct.
        EXPECT_EQ(ref_values->getPosition(name).line_,
                  values->getPosition(name).line_);

        EXPECT_EQ(ref_values->getPosition(name).pos_,
                  values->getPosition(name).pos_);

        EXPECT_EQ(ref_values->getPosition(name).file_,
                  values->getPosition(name).file_);
    }

    /// @brief Check that the storages of the specific type hold different
    /// value.
    ///
    /// This function assumes that the ref_values storage holds exactly
    /// one parameter called 'foo'.
    ///
    /// @param ref_values A storage holding reference value. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding value to be checked.
    /// @tparam ContainerType A type of the storage.
    /// @tparam ValueType A type of the value in the container.
    template<typename ContainerType>
    void checkValueNeq(const boost::shared_ptr<ContainerType>& ref_values,
                       const boost::shared_ptr<ContainerType>& values) {
        ASSERT_NO_THROW(values->getParam("foo"));
        EXPECT_NE(ref_values->getParam("foo"), values->getParam("foo"));
    }

    /// @brief Check that the storages of the specific type hold different
    /// position.
    ///
    /// @param name A name of the parameter to be checked.
    /// @param ref_values A storage holding reference position. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding position to be checked.
    /// @tparam ContainerType A type of the storage.
    template<typename ContainerType>
    void checkPositionNeq(const std::string& name,
                          const boost::shared_ptr<ContainerType>& ref_values,
                          const boost::shared_ptr<ContainerType>& values) {
        // At least one of the position fields must be different.
        EXPECT_TRUE((ref_values->getPosition(name).line_ !=
                     values->getPosition(name).line_) ||
                    (ref_values->getPosition(name).pos_ !=
                     values->getPosition(name).pos_) ||
                    (ref_values->getPosition(name).file_ !=
                     values->getPosition(name).file_));
    }

    /// @brief Test copy constructor or assignment operator when values
    /// being copied are NULL.
    ///
    /// @param copy Indicates that copy constructor should be tested
    /// (if true), or assignment operator (if false).
    void testCopyAssignmentNull(const bool copy) {
        ParserContext ctx(Option::V6);
        // Release all pointers in the context.
        ctx.boolean_values_.reset();
        ctx.uint32_values_.reset();
        ctx.string_values_.reset();
        ctx.hooks_libraries_.reset();

        // Even if the fields of the context are NULL, it should get
        // copied.
        ParserContextPtr ctx_new(new ParserContext(Option::V6));
        if (copy) {
            ASSERT_NO_THROW(ctx_new.reset(new ParserContext(ctx)));
        } else {
            *ctx_new = ctx;
        }

        // The resulting context has its fields equal to NULL.
        EXPECT_FALSE(ctx_new->boolean_values_);
        EXPECT_FALSE(ctx_new->uint32_values_);
        EXPECT_FALSE(ctx_new->string_values_);
        EXPECT_FALSE(ctx_new->hooks_libraries_);

    }

    /// @brief Test copy constructor or assignment operator.
    ///
    /// @param copy Indicates that copy constructor should be tested (if true),
    /// or assignment operator (if false).
    void testCopyAssignment(const bool copy) {
        // Create new context. It will be later copied/assigned to another
        // context.
        ParserContext ctx(Option::V6);

        // Set boolean parameter 'foo'.
        ASSERT_TRUE(ctx.boolean_values_);
        ctx.boolean_values_->setParam("foo", true,
                                      Element::Position("kea.conf", 123, 234));

        // Set various parameters to test that position is copied between
        // contexts.
        ctx.boolean_values_->setParam("pos0", true,
                                      Element::Position("kea.conf", 1, 2));
        ctx.boolean_values_->setParam("pos1", true,
                                      Element::Position("kea.conf", 10, 20));
        ctx.boolean_values_->setParam("pos2", true,
                                      Element::Position("kea.conf", 100, 200));

        // Set uint32 parameter 'foo'.
        ASSERT_TRUE(ctx.uint32_values_);
        ctx.uint32_values_->setParam("foo", 123,
                                     Element::Position("kea.conf", 123, 234));

        // Set various parameters to test that position is copied between
        // contexts.
        ctx.uint32_values_->setParam("pos0", 123,
                                      Element::Position("kea.conf", 1, 2));
        ctx.uint32_values_->setParam("pos1", 123,
                                      Element::Position("kea.conf", 10, 20));
        ctx.uint32_values_->setParam("pos2", 123,
                                      Element::Position("kea.conf", 100, 200));

        // Ser string parameter 'foo'.
        ASSERT_TRUE(ctx.string_values_);
        ctx.string_values_->setParam("foo", "some string",
                                     Element::Position("kea.conf", 123, 234));

        // Set various parameters to test that position is copied between
        // contexts.
        ctx.string_values_->setParam("pos0", "some string",
                                      Element::Position("kea.conf", 1, 2));
        ctx.string_values_->setParam("pos1", "some string",
                                      Element::Position("kea.conf", 10, 20));
        ctx.string_values_->setParam("pos2", "some string",
                                      Element::Position("kea.conf", 100, 200));


        // Allocate container for hooks libraries and add one library name.
        ctx.hooks_libraries_.reset(new std::vector<std::string>());
        ctx.hooks_libraries_->push_back("library1");

        // We will use ctx_new to assign another context to it or copy
        // construct.
        ParserContextPtr ctx_new(new ParserContext(Option::V4));;
        if (copy) {
            ctx_new.reset(new ParserContext(ctx));
        } else {
            *ctx_new = ctx;
        }

        // New context has the same boolean value.
        ASSERT_TRUE(ctx_new->boolean_values_);
        {
            SCOPED_TRACE("Check that boolean values are equal in both"
                         " contexts");
            checkValueEq(ctx.boolean_values_, ctx_new->boolean_values_);
        }

        // New context has the same boolean values' positions.
        {
            SCOPED_TRACE("Check that positions of boolean values are equal"
                         " in both contexts");
            checkPositionEq("pos0", ctx.boolean_values_,
                            ctx_new->boolean_values_);
            checkPositionEq("pos1", ctx.boolean_values_,
                            ctx_new->boolean_values_);
            checkPositionEq("pos2", ctx.boolean_values_,
                            ctx_new->boolean_values_);
        }

        // New context has the same uint32 value.
        ASSERT_TRUE(ctx_new->uint32_values_);
        {
            SCOPED_TRACE("Check that uint32_t values are equal in both"
                         " contexts");
            checkValueEq(ctx.uint32_values_, ctx_new->uint32_values_);
        }

        // New context has the same uint32 values' positions.
        {
            SCOPED_TRACE("Check that positions of uint32 values are equal"
                         " in both contexts");
            checkPositionEq("pos0", ctx.uint32_values_,
                            ctx_new->uint32_values_);
            checkPositionEq("pos1", ctx.uint32_values_,
                            ctx_new->uint32_values_);
            checkPositionEq("pos2", ctx.uint32_values_,
                            ctx_new->uint32_values_);
        }

        // New context has the same uint32 value position.
        {
            SCOPED_TRACE("Check that positions of uint32_t values are equal"
                         " in both contexts");
            checkPositionEq("foo", ctx.uint32_values_, ctx_new->uint32_values_);
        }

        // New context has the same string value.
        ASSERT_TRUE(ctx_new->string_values_);
        {
            SCOPED_TRACE("Check that string values are equal in both contexts");
            checkValueEq(ctx.string_values_, ctx_new->string_values_);
        }

        // New context has the same string values' positions.
        {
            SCOPED_TRACE("Check that positions of string values are equal"
                         " in both contexts");
            checkPositionEq("pos0", ctx.string_values_,
                            ctx_new->string_values_);
            checkPositionEq("pos1", ctx.string_values_,
                            ctx_new->string_values_);
            checkPositionEq("pos2", ctx.string_values_,
                            ctx_new->string_values_);
        }

        // New context has the same hooks library.
        ASSERT_TRUE(ctx_new->hooks_libraries_);
        {
            ASSERT_EQ(1, ctx_new->hooks_libraries_->size());
            EXPECT_EQ("library1", (*ctx_new->hooks_libraries_)[0]);
        }

        // New context has the same universe.
        EXPECT_EQ(ctx.universe_, ctx_new->universe_);

        // Change the value of the boolean parameter. This should not affect the
        // corresponding value in the new context.
        {
            SCOPED_TRACE("Check that boolean value isn't changed when original"
                         " value and position is changed");
            ctx.boolean_values_->setParam("foo", false,
                                          Element::Position("kea.conf",
                                                            12, 10));
            checkValueNeq(ctx.boolean_values_, ctx_new->boolean_values_);

        }

        {
            SCOPED_TRACE("Check that positions of the boolean parameters aren't"
                         " changed when the corresponding positions in the"
                         " original context are changed");
            // Modify file name.
            ctx.boolean_values_->setParam("pos0", false,
                                          Element::Position("foo.conf",
                                                            1, 2));
            checkPositionNeq("pos0", ctx.boolean_values_,
                             ctx_new->boolean_values_);
            // Modify line number.
            ctx.boolean_values_->setParam("pos1", false,
                                          Element::Position("kea.conf",
                                                            11, 20));
            checkPositionNeq("pos1", ctx.boolean_values_,
                             ctx_new->boolean_values_);
            // Modify position within a line.
            ctx.boolean_values_->setParam("pos2", false,
                                          Element::Position("kea.conf",
                                                            101, 201));
            checkPositionNeq("pos2", ctx.boolean_values_,
                             ctx_new->boolean_values_);

        }

        // Change the value of the uint32_t parameter. This should not affect
        // the corresponding value in the new context.
        {
            SCOPED_TRACE("Check that uint32_t value isn't changed when original"
                         " value and position is changed");
            ctx.uint32_values_->setParam("foo", 987,
                                         Element::Position("kea.conf", 10, 11));
            checkValueNeq(ctx.uint32_values_, ctx_new->uint32_values_);
        }

        {
            SCOPED_TRACE("Check that positions of the uint32 parameters aren't"
                         " changed when the corresponding positions in the"
                         " original context are changed");
            // Modify file name.
            ctx.uint32_values_->setParam("pos0", 123,
                                          Element::Position("foo.conf", 1, 2));
            checkPositionNeq("pos0", ctx.uint32_values_,
                             ctx_new->uint32_values_);
            // Modify line number.
            ctx.uint32_values_->setParam("pos1", 123,
                                          Element::Position("kea.conf",
                                                            11, 20));
            checkPositionNeq("pos1", ctx.uint32_values_,
                             ctx_new->uint32_values_);
            // Modify position within a line.
            ctx.uint32_values_->setParam("pos2", 123,
                                          Element::Position("kea.conf",
                                                            101, 201));
            checkPositionNeq("pos2", ctx.uint32_values_,
                             ctx_new->uint32_values_);

        }

        // Change the value of the string parameter. This should not affect the
        // corresponding value in the new context.
        {
            SCOPED_TRACE("Check that string value isn't changed when original"
                         " value and position is changed");
            ctx.string_values_->setParam("foo", "different string",
                                         Element::Position("kea.conf", 10, 11));
            checkValueNeq(ctx.string_values_, ctx_new->string_values_);
        }

        {
            SCOPED_TRACE("Check that positions of the string parameters aren't"
                         " changed when the corresponding positions in the"
                         " original context are changed");
            // Modify file name.
            ctx.string_values_->setParam("pos0", "some string",
                                          Element::Position("foo.conf", 1, 2));
            checkPositionNeq("pos0", ctx.string_values_,
                             ctx_new->string_values_);
            // Modify line number.
            ctx.string_values_->setParam("pos1", "some string",
                                          Element::Position("kea.conf",
                                                            11, 20));
            checkPositionNeq("pos1", ctx.string_values_,
                             ctx_new->string_values_);
            // Modify position within a line.
            ctx.string_values_->setParam("pos2", "some string",
                                          Element::Position("kea.conf",
                                                            101, 201));
            checkPositionNeq("pos2", ctx.string_values_,
                             ctx_new->string_values_);

        }

        // Change the list of libraries. this should not affect the list in the
        // new context.
        ctx.hooks_libraries_->clear();
        ctx.hooks_libraries_->push_back("library2");
        ASSERT_EQ(1, ctx_new->hooks_libraries_->size());
        EXPECT_EQ("library1", (*ctx_new->hooks_libraries_)[0]);

        // Change the universe. This should not affect the universe value in the
        // new context.
        ctx.universe_ = Option::V4;
        EXPECT_EQ(Option::V6, ctx_new->universe_);

    }

};

// Check that the assignment operator of the ParserContext class copies all
// fields correctly.
TEST_F(ParserContextTest, assignment) {
    testCopyAssignment(false);
}

// Check that the assignment operator of the ParserContext class copies all
// fields correctly when these fields are NULL.
TEST_F(ParserContextTest, assignmentNull) {
    testCopyAssignmentNull(false);
}

// Check that the context is copy constructed correctly.
TEST_F(ParserContextTest, copyConstruct) {
    testCopyAssignment(true);
}

// Check that the context is copy constructed correctly, when context fields
// are NULL.
TEST_F(ParserContextTest, copyConstructNull) {
    testCopyAssignmentNull(true);
}

/// @brief Checks that a valid relay info structure for IPv4 can be handled
TEST_F(ParseConfigTest, validRelayInfo4) {

    // Relay information structure. Very simple for now.
    std::string config_str =
        "    {"
        "     \"ip-address\" : \"192.0.2.1\""
        "    }";
    ElementPtr json = Element::fromJSON(config_str);

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

    // We need to set the default ip-address to something.
    Subnet::RelayInfoPtr result(new Subnet::RelayInfo(asiolink::IOAddress("0.0.0.0")));

    boost::shared_ptr<RelayInfoParser> parser;

    // Subnet4 parser will pass 0.0.0.0 to the RelayInfoParser
    EXPECT_NO_THROW(parser.reset(new RelayInfoParser("ignored", result,
                                                     Option::V4)));
    EXPECT_NO_THROW(parser->build(json));
    EXPECT_NO_THROW(parser->commit());

    EXPECT_EQ("192.0.2.1", result->addr_.toText());

    // Let's check negative scenario (wrong family type)
    EXPECT_THROW(parser->build(json_bogus1), DhcpConfigError);

    // Let's check negative scenario (too large byte values in pseudo-IPv4 addr)
    EXPECT_THROW(parser->build(json_bogus2), DhcpConfigError);
}

/// @brief Checks that a valid relay info structure for IPv6 can be handled
TEST_F(ParseConfigTest, validRelayInfo6) {

    // Relay information structure. Very simple for now.
    std::string config_str =
        "    {"
        "     \"ip-address\" : \"2001:db8::1\""
        "    }";
    ElementPtr json = Element::fromJSON(config_str);

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

    // We need to set the default ip-address to something.
    Subnet::RelayInfoPtr result(new Subnet::RelayInfo(asiolink::IOAddress("::")));

    boost::shared_ptr<RelayInfoParser> parser;
    // Subnet4 parser will pass :: to the RelayInfoParser
    EXPECT_NO_THROW(parser.reset(new RelayInfoParser("ignored", result,
                                                     Option::V6)));
    EXPECT_NO_THROW(parser->build(json));
    EXPECT_NO_THROW(parser->commit());

    EXPECT_EQ("2001:db8::1", result->addr_.toText());

    // Let's check negative scenario (wrong family type)
    EXPECT_THROW(parser->build(json_bogus1), DhcpConfigError);

    // Unparseable text that looks like IPv6 address, but has too many colons
    EXPECT_THROW(parser->build(json_bogus2), DhcpConfigError);
}

// There's no test for ControlSocketParser, as it is tested in the DHCPv4 code
// (see CtrlDhcpv4SrvTest.commandSocketBasic in
// src/bin/dhcp4/tests/ctrl_dhcp4_srv_unittest.cc).
