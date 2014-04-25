// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <config/ccsession.h>
#include <cc/data.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <dhcpsrv/tests/test_libraries.h>
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
using namespace isc::hooks;

namespace {

/// @brief DHCP Parser test fixture class
class DhcpParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    DhcpParserTest() {
        CfgMgr::instance().deleteActiveIfaces();
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
    actual_value = ~test_value;
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

/// @brief Check InterfaceListParser  basic functionality
///
/// Verifies that the parser:
/// 1. Does not allow empty for storage.
/// 2. Does not allow name other than "interfaces"
/// 3. Parses list of interfaces and adds them to CfgMgr
/// 4. Parses wildcard interface name and sets a CfgMgr flag which indicates
/// that server will listen on all interfaces.
TEST_F(DhcpParserTest, interfaceListParserTest) {

    const std::string name = "interfaces";

    // Verify that parser constructor fails if parameter name isn't "interface"
    EXPECT_THROW(InterfaceListConfigParser("bogus_name"), isc::BadValue);

    boost::scoped_ptr<InterfaceListConfigParser>
        parser(new InterfaceListConfigParser(name));
    ElementPtr list_element = Element::createList();
    list_element->add(Element::create("eth0"));
    list_element->add(Element::create("eth1"));

    // Make sure there are no interfaces added yet.
    ASSERT_FALSE(CfgMgr::instance().isActiveIface("eth0"));
    ASSERT_FALSE(CfgMgr::instance().isActiveIface("eth1"));

    // This should parse the configuration and add eth0 and eth1 to the list
    // of interfaces that server should listen on.
    parser->build(list_element);
    parser->commit();

    // Use CfgMgr instance to check if eth0 and eth1 was added, and that
    // eth2 was not added.
    CfgMgr& cfg_mgr = CfgMgr::instance();
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth0"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth2"));

    // Add keyword all to the configuration. This should activate all
    // interfaces, including eth2, even though it has not been explicitly
    // added.
    list_element->add(Element::create("*"));

    // Reset parser's state.
    parser.reset(new InterfaceListConfigParser(name));
    parser->build(list_element);
    parser->commit();

    EXPECT_TRUE(cfg_mgr.isActiveIface("eth0"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth2"));
}

// Checks whether option space can be detected as vendor-id
TEST_F(DhcpParserTest, vendorOptionSpace) {
    EXPECT_EQ(0, SubnetConfigParser::optionSpaceToVendorId(""));
    EXPECT_EQ(0, SubnetConfigParser::optionSpaceToVendorId("dhcp4"));
    EXPECT_EQ(0, SubnetConfigParser::optionSpaceToVendorId("vendor-"));
    EXPECT_EQ(1, SubnetConfigParser::optionSpaceToVendorId("vendor-1"));
    EXPECT_EQ(4491, SubnetConfigParser::optionSpaceToVendorId("vendor-4491"));
    EXPECT_EQ(12345678, SubnetConfigParser::optionSpaceToVendorId("vendor-12345678"));
}

/// @brief Test Implementation of abstract OptionDataParser class. Allows
/// testing basic option parsing.
class UtestOptionDataParser : public OptionDataParser {
public:

    UtestOptionDataParser(const std::string&,
        OptionStoragePtr options, ParserContextPtr global_context)
        :OptionDataParser("", options, global_context) {
    }

    static OptionDataParser* factory(const std::string& param_name,
        OptionStoragePtr options, ParserContextPtr global_context) {
        return (new UtestOptionDataParser(param_name, options, global_context));
    }

protected:
    // Dummy out last two params since test derivation doesn't use them.
    virtual OptionDefinitionPtr findServerSpaceOptionDefinition (
                std::string&, uint32_t) {
        OptionDefinitionPtr def;
        // always return empty
        return (def);
    }
};

/// @brief Test Fixture class which provides basic structure for testing
/// configuration parsing.  This is essentially the same structure provided
/// by dhcp servers.
class ParseConfigTest : public ::testing::Test {
public:
    /// @brief Constructor
    ParseConfigTest() {
        reset_context();
    }

    ~ParseConfigTest() {
        reset_context();
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
        if (config_id.compare("option-data") == 0) {
            parser.reset(new OptionDataListParser(config_id,
                                              parser_context_->options_,
                                              parser_context_,
                                              UtestOptionDataParser::factory));

        } else if (config_id.compare("option-def") == 0) {
            parser.reset(new OptionDefListParser(config_id,
                                                 parser_context_->option_defs_,
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
        }

        return (rcode_);
    }

    /// @brief Find an option definition for a given space and code within
    /// the parser context.
    /// @param space is the space name of the desired option.
    /// @param code is the numeric "type" of the desired option.
    /// @return returns an OptionDefinitionPtr which points to the found
    /// definition or is empty.
    /// ASSERT_ tests don't work inside functions that return values
    OptionDefinitionPtr getOptionDef(std::string space, uint32_t code)
    {
        OptionDefinitionPtr def;
        OptionDefContainerPtr defs =
                            parser_context_->option_defs_->getItems(space);
        // Should always be able to get definitions list even if it is empty.
        EXPECT_TRUE(defs);
        if (defs) {
            // Attempt to find desired definiton.
            const OptionDefContainerTypeIndex& idx = defs->get<1>();
            const OptionDefContainerTypeRange& range = idx.equal_range(code);
            int cnt = std::distance(range.first, range.second);
            EXPECT_EQ(1, cnt);
            if (cnt == 1) {
                def = *(idx.begin());
            }
        }
        return (def);
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
        Subnet::OptionContainerPtr options =
                            parser_context_->options_->getItems(space);
        // Should always be able to get options list even if it is empty.
        EXPECT_TRUE(options);
        if (options) {
            // Attempt to find desired option.
            const Subnet::OptionContainerTypeIndex& idx = options->get<1>();
            const Subnet::OptionContainerTypeRange& range =
                                                        idx.equal_range(code);
            int cnt = std::distance(range.first, range.second);
            EXPECT_EQ(1, cnt);
            if (cnt == 1) {
                Subnet::OptionDescriptor desc = *(idx.begin());
                option_ptr = desc.option;
                EXPECT_TRUE(option_ptr);
            }
        }

        return (option_ptr);
    }

    /// @brief Wipes the contents of the context to allowing another parsing
    /// during a given test if needed.
    void reset_context(){
        // Note set context universe to V6 as it has to be something.
        CfgMgr::instance().deleteSubnets4();
        CfgMgr::instance().deleteSubnets6();
        CfgMgr::instance().deleteOptionDefs();
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
    OptionDefinitionPtr def = getOptionDef("isc", 100);
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
    std::string val = "type=100, len=4, data fields:\n "
                      " #0 192.0.2.0 ( ipv4-address ) \n";

    EXPECT_EQ(val, opt_ptr->toText());
}

};  // Anonymous namespace

/// These tests check basic operation of the HooksLibrariesParser.

// hooks-libraries that do not contain anything.
TEST_F(ParseConfigTest, noHooksLibrariesTest) {

    // Configuration with hooks-libraries not present.
    string config = "{ \"hooks-libraries\": [] }";

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Check that the parser recorded no change to the current state
    // (as the test starts with no hooks libraries loaded).
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(libraries.empty());
    EXPECT_FALSE(changed);

    // Load a single library and repeat the parse.
    vector<string> basic_library;
    basic_library.push_back(string(CALLOUT_LIBRARY_1));
    HooksManager::loadLibraries(basic_library);

    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // This time the change should have been recorded.
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(libraries.empty());
    EXPECT_TRUE(changed);

    // But repeating it again and we are back to no change.
    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_TRUE(libraries.empty());
    EXPECT_FALSE(changed);

}


TEST_F(ParseConfigTest, validHooksLibrariesTest) {

    // Configuration string.  This contains a set of valid libraries.
    const std::string quote("\"");
    const std::string comma(", ");

    const std::string config =
        std::string("{ ") +
            std::string("\"hooks-libraries\": [") +
                quote + std::string(CALLOUT_LIBRARY_1) + quote + comma +
                quote + std::string(CALLOUT_LIBRARY_2)  + quote +
            std::string("]") +
        std::string("}");

    // Verify that the configuration string parses.
    int rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // Check that the parser holds two libraries and the configuration is
    // recorded as having changed.
    std::vector<std::string> libraries;
    bool changed;
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_EQ(2, libraries.size());
    EXPECT_TRUE(changed);

    // The expected libraries should be the list of libraries specified
    // in the given order.
    std::vector<std::string> expected;
    expected.push_back(CALLOUT_LIBRARY_1);
    expected.push_back(CALLOUT_LIBRARY_2);
    EXPECT_TRUE(expected == libraries);

    // Parse the string again.
    rcode = parseConfiguration(config);
    ASSERT_TRUE(rcode == 0) << error_text_;

    // The list has not changed, and this is what we should see.
    hooks_libraries_parser_->getLibraries(libraries, changed);
    EXPECT_EQ(2, libraries.size());
    EXPECT_FALSE(changed);
}

// Check with a set of libraries, some of which are invalid.
TEST_F(ParseConfigTest, invalidHooksLibrariesTest) {

    /// @todo Initialize global library context to null

    // Configuration string.  This contains an invalid library which should
    // trigger an error in the "build" stage.
    const std::string quote("\"");
    const std::string comma(", ");

    const std::string config =
        std::string("{ ") +
            std::string("\"hooks-libraries\": [") +
                quote + std::string(CALLOUT_LIBRARY_1) + quote + comma +
                quote + std::string(NOT_PRESENT_LIBRARY) + quote + comma +
                quote + std::string(CALLOUT_LIBRARY_2)  + quote +
            std::string("]") +
        std::string("}");

    // Verify that the configuration fails to parse. (Syntactically it's OK,
    // but the library is invalid).
    int rcode = parseConfiguration(config);
    ASSERT_FALSE(rcode == 0) << error_text_;

    // Check that the message contains the library in error.
    EXPECT_FALSE(error_text_.find(NOT_PRESENT_LIBRARY) == string::npos) <<
        "Error text returned from parse failure is " << error_text_;
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

    // Configuration string.  This contains a set of valid libraries.
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

    // Configuration string.  This contains a set of valid libraries.
    std::string config_str =
        "{ \"dhcp-ddns\" :"
        "    {"
        "     \"enable-updates\" : true"
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
    EXPECT_EQ(D2ClientConfig::DFT_QUALIFYING_SUFFIX,
              d2_client_config->getQualifyingSuffix());
}


/// @brief Check various invalid D2 client configurations.
TEST_F(ParseConfigTest, invalidD2Config) {
    std::string invalid_configs[] = {
        // Must supply at lease enable-updates
        "{ \"dhcp-ddns\" :"
        "    {"
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
    /// This function assumes that the ref_values storage holds exactly
    /// one parameter called 'foo'.
    ///
    /// @param ref_values A storage holding reference value. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding value to be checked.
    /// @tparam ContainerType A type of the storage.
    /// @tparam ValueType A type of the value in the container.
    template<typename ContainerType, typename ValueType>
    void checkValueEq(const boost::shared_ptr<ContainerType>& ref_values,
                      const boost::shared_ptr<ContainerType>& values) {
        ASSERT_NO_THROW(values->getParam("foo"));
        EXPECT_EQ(ref_values->getParam("foo"), values->getParam("foo"));
    }

    /// @brief Check that the storages of the specific type hold the same
    /// position.
    ///
    /// This function assumes that the @c ref_values storage holds exactly
    /// one parameter called 'foo'.
    ///
    /// @param ref_values A storage holding reference position. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding position to be checked.
    /// @tparam ContainerType A type of the storage.
    /// @tparam ValueType A type of the value in the container.
    template<typename ContainerType, typename ValueType>
    void checkPositionEq(const boost::shared_ptr<ContainerType>& ref_values,
                         const boost::shared_ptr<ContainerType>& values) {
        // Verify that the position is correct.
        EXPECT_EQ(ref_values->getPosition("foo").line_,
                  values->getPosition("foo").line_);

        EXPECT_EQ(ref_values->getPosition("foo").pos_,
                  values->getPosition("foo").pos_);

        EXPECT_EQ(ref_values->getPosition("foo").file_,
                  values->getPosition("foo").file_);
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
    template<typename ContainerType, typename ValueType>
    void checkValueNeq(const boost::shared_ptr<ContainerType>& ref_values,
                       const boost::shared_ptr<ContainerType>& values) {
        ASSERT_NO_THROW(values->getParam("foo"));
        EXPECT_NE(ref_values->getParam("foo"), values->getParam("foo"));
    }

    /// @brief Check that the storages of the specific type hold fifferent
    /// position.
    ///
    /// This function assumes that the ref_values storage holds exactly
    /// one parameter called 'foo'.
    ///
    /// @param ref_values A storage holding reference position. In the typical
    /// case it is a storage held in the original context, which is assigned
    /// to another context.
    /// @param values A storage holding position to be checked.
    /// @tparam ContainerType A type of the storage.
    /// @tparam ValueType A type of the value in the container.
    template<typename ContainerType, typename ValueType>
    void checkPositionNeq(const boost::shared_ptr<ContainerType>& ref_values,
                          const boost::shared_ptr<ContainerType>& values) {
        // At least one of the position fields must be different.
        EXPECT_TRUE((ref_values->getPosition("foo").line_ !=
                     values->getPosition("foo").line_) ||
                    (ref_values->getPosition("foo").pos_ !=
                     values->getPosition("foo").pos_) ||
                    (ref_values->getPosition("foo").pos_ !=
                     values->getPosition("foo").pos_));
    }

    /// @brief Check that option definition storage in the context holds
    /// one option definition of the specified type.
    ///
    /// @param ctx A pointer to a context.
    /// @param opt_type Expected option type.
    void checkOptionDefinitionType(const ParserContext& ctx,
                                   const uint16_t opt_type) {
        OptionDefContainerPtr opt_defs =
            ctx.option_defs_->getItems("option-space");
        ASSERT_TRUE(opt_defs);
        OptionDefContainerTypeIndex& idx = opt_defs->get<1>();
        OptionDefContainerTypeRange range = idx.equal_range(opt_type);
        EXPECT_EQ(1, std::distance(range.first, range.second));
    }

    /// @brief Check that option storage in the context holds one option
    /// of the specified type.
    ///
    /// @param ctx A pointer to a context.
    /// @param opt_type Expected option type.
    void checkOptionType(const ParserContext& ctx, const uint16_t opt_type) {
        Subnet::OptionContainerPtr options =
            ctx.options_->getItems("option-space");
        ASSERT_TRUE(options);
        Subnet::OptionContainerTypeIndex& idx = options->get<1>();
        Subnet::OptionContainerTypeRange range = idx.equal_range(opt_type);
        ASSERT_EQ(1, std::distance(range.first, range.second));
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
        ctx.options_.reset();
        ctx.option_defs_.reset();
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
        EXPECT_FALSE(ctx_new->options_);
        EXPECT_FALSE(ctx_new->option_defs_);
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

        // Set uint32 parameter 'foo'.
        ASSERT_TRUE(ctx.uint32_values_);
        ctx.uint32_values_->setParam("foo", 123,
                                     Element::Position("kea.conf", 123, 234));

        // Ser string parameter 'foo'.
        ASSERT_TRUE(ctx.string_values_);
        ctx.string_values_->setParam("foo", "some string",
                                     Element::Position("kea.conf", 123, 234));

        // Add new option, with option code 10, to the context.
        ASSERT_TRUE(ctx.options_);
        OptionPtr opt1(new Option(Option::V6, 10));
        Subnet::OptionDescriptor desc1(opt1, false);
        std::string option_space = "option-space";
        ASSERT_TRUE(desc1.option);
        ctx.options_->addItem(desc1, option_space);

        // Add new option definition, with option code 123.
        OptionDefinitionPtr def1(new OptionDefinition("option-foo", 123,
                                                      "string"));
        ctx.option_defs_->addItem(def1, option_space);

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
            checkValueEq<BooleanStorage, bool>(ctx.boolean_values_,
                                               ctx_new->boolean_values_);
        }

        // New context has the same boolean value position.
        {
            SCOPED_TRACE("Check that positions of boolean values are equal"
                         " in both contexts");
            checkPositionEq<BooleanStorage, bool>(ctx.boolean_values_,
                                                  ctx_new->boolean_values_);
        }

        // New context has the same uint32 value.
        ASSERT_TRUE(ctx_new->uint32_values_);
        {
            SCOPED_TRACE("Check that uint32_t values are equal in both"
                         " contexts");
            checkValueEq<Uint32Storage, uint32_t>(ctx.uint32_values_,
                                                  ctx_new->uint32_values_);
        }

        // New context has the same uint32 value position.
        {
            SCOPED_TRACE("Check that positions of uint32_t values are equal"
                         " in both contexts");
            checkPositionEq<Uint32Storage, uint32_t>(ctx.uint32_values_,
                                                     ctx_new->uint32_values_);
        }

        // New context has the same string value.
        ASSERT_TRUE(ctx_new->string_values_);
        {
            SCOPED_TRACE("Check that string values are equal in both contexts");
            checkValueEq<StringStorage, std::string>(ctx.string_values_,
                                                     ctx_new->string_values_);
        }

        // New context has the same string value position.
        {
            SCOPED_TRACE("Check that position of string values are equal"
                         " in both contexts");
            checkPositionEq<StringStorage, std::string>(ctx.string_values_,
                                                        ctx_new->string_values_);
        }

        // New context has the same option.
        ASSERT_TRUE(ctx_new->options_);
        {
            SCOPED_TRACE("Check that the option values are equal in both"
                         " contexts");
            checkOptionType(*ctx_new, 10);
        }

        // New context has the same option definition.
        ASSERT_TRUE(ctx_new->option_defs_);
        {
            SCOPED_TRACE("check that the option definition is equal in both"
                         " contexts");
            checkOptionDefinitionType(*ctx_new, 123);
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
            SCOPED_TRACE("Check that boolean value and position isn't changed"
                         " when original value and position is changed");
            ctx.boolean_values_->setParam("foo", false,
                                          Element::Position("kea.conf",
                                                            12, 10));
            checkValueNeq<BooleanStorage, bool>(ctx.boolean_values_,
                                                ctx_new->boolean_values_);

            checkPositionNeq<BooleanStorage, bool>(ctx.boolean_values_,
                                                   ctx_new->boolean_values_);
        }

        // Change the value of the uint32_t parameter. This should not affect
        // the corresponding value in the new context.
        {
            SCOPED_TRACE("Check that uint32_t value and position isn't changed"
                         " when original value and position is changed");
            ctx.uint32_values_->setParam("foo", 987,
                                         Element::Position("kea.conf",
                                                           10, 11));
            checkValueNeq<Uint32Storage, uint32_t>(ctx.uint32_values_,
                                                   ctx_new->uint32_values_);

            checkPositionNeq<Uint32Storage, uint32_t>(ctx.uint32_values_,
                                                      ctx_new->uint32_values_);

        }

        // Change the value of the string parameter. This should not affect the
        // corresponding value in the new context.
        {
            SCOPED_TRACE("Check that string value and position isn't changed"
                         " when original value and position is changed");
            ctx.string_values_->setParam("foo", "different string",
                                         Element::Position("kea.conf",
                                                           10, 11));
            checkValueNeq<StringStorage, std::string>(ctx.string_values_,
                                                      ctx_new->string_values_);

            checkPositionNeq<
                StringStorage, std::string>(ctx.string_values_,
                                            ctx_new->string_values_);

        }

        // Change the option. This should not affect the option instance in the
        // new context.
        {
            SCOPED_TRACE("Check that option remains the same in the new context"
                         " when the option in the original context is changed");
            ctx.options_->clearItems();
            Subnet::OptionDescriptor desc(OptionPtr(new Option(Option::V6,
                                                               100)),
                                          false);

            ASSERT_TRUE(desc.option);
            ctx.options_->addItem(desc, "option-space");
            checkOptionType(*ctx_new, 10);
        }

        // Change the option definition. This should not affect the option
        // definition in the new context.
        {
            SCOPED_TRACE("Check that option definition remains the same in"
                         " the new context when the option definition in the"
                         " original context is changed");
            ctx.option_defs_->clearItems();
            OptionDefinitionPtr def(new OptionDefinition("option-foo", 234,
                                                         "string"));

            ctx.option_defs_->addItem(def, option_space);
            checkOptionDefinitionType(*ctx_new, 123);
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
