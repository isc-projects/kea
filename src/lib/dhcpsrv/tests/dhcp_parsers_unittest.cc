// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>
#include <boost/foreach.hpp>

#include <map>
#include <string>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::config;

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
            // Iteraate over the config elements.
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
    /// Note that currently it only supports option-defs and option-data,
    ///
    /// @param config_id is the name of the configuration element.
    /// @return returns a raw pointer to DhcpConfigParser. Note caller is
    /// responsible for deleting it once no longer needed.
    /// @throw throws NotImplemented if element name isn't supported.
    DhcpConfigParser* createConfigParser(const std::string& config_id) {
        DhcpConfigParser* parser = NULL;
        if (config_id.compare("option-data") == 0) {
            parser = new OptionDataListParser(config_id,
                                          parser_context_->options_,
                                          parser_context_,
                                          UtestOptionDataParser::factory);
        } else if (config_id.compare("option-def") == 0) {
            parser  = new OptionDefListParser(config_id,
                                          parser_context_->option_defs_);
        } else {
            isc_throw(NotImplemented,
                "Parser error: configuration parameter not supported: "
                << config_id);
        }

        return (parser);
    }

    /// @brief Convenicee method for parsing a configuration
    ///
    /// Given a configuration string, convert it into Elements
    /// and parse them.
    /// @param config is the configuration string to parse
    ///
    /// @return retuns 0 if the configuration parsed successfully,
    /// non-zero otherwise failure.
    int parseConfiguration (std::string &config) {
        int rcode_ = 1;
        // Turn config into elements.
        // Test json just to make sure its valid.
        ElementPtr json = Element::fromJSON(config);
        EXPECT_TRUE(json);
        if (json) {
            ConstElementPtr status = parseElementSet(json);
            ConstElementPtr comment_ = parseAnswer(rcode_, status);
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
    }

    /// @brief Parser context - provides storage for options and definitions
    ParserContextPtr parser_context_;
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
        "    \"data\": \"192.168.2.1\","
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
                      " #0 192.168.2.1 ( ipv4-address ) \n";

    EXPECT_EQ(val, opt_ptr->toText());
}

};  // Anonymous namespace

