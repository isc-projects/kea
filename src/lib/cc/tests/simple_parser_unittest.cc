// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stdint.h>
#include <cc/simple_parser.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::data;
using namespace isc::asiolink;
using isc::dhcp::DhcpConfigError;

/// This list defines required keywords.
const SimpleRequiredKeywords REQUIRED_KEYWORDS = { "foobar" };

/// This table defines keywords and types.
const SimpleKeywords KEYWORDS = {
    { "id",     Element::integer },
    { "prefix", Element::string },
    { "map",    Element::map },
    { "any",    Element::any }
};

/// This table defines sample default values. Although these are DHCPv6
/// specific, the mechanism is generic and can be used by any other component.
const SimpleDefaults SAMPLE_DEFAULTS = {
    { "renew-timer",        Element::integer, "900" },
    { "rebind-timer",       Element::integer, "1800" },
    { "preferred-lifetime", Element::integer, "3600" },
    { "valid-lifetime",     Element::integer, "7200" }
};

/// This list defines parameters that can be inherited from one scope
/// to another. Although these are DHCPv6 specific, the mechanism is generic and
/// can be used by any other component.
const ParamsList SAMPLE_INHERITS = {
    "renew-timer",
    "rebind-timer",
    "preferred-lifetime",
    "valid-lifetime"
};

/// @brief Simple Parser test fixture class
class SimpleParserTest : public ::testing::Test {
public:
    /// @brief Checks if specified map has an integer parameter with expected value
    ///
    /// @param map map to be checked
    /// @param param_name name of the parameter to be checked
    /// @param exp_value expected value of the parameter.
    void checkIntegerValue(const ConstElementPtr& map, const std::string& param_name,
                           int64_t exp_value) {

        // First check if the passed element is a map.
        ASSERT_EQ(Element::map, map->getType());

        // Now try to get the element being checked
        ConstElementPtr elem = map->get(param_name);
        ASSERT_TRUE(elem);

        // Now check if it's indeed integer
        ASSERT_EQ(Element::integer, elem->getType());

        // Finally, check if its value meets expectation.
        EXPECT_EQ(exp_value, elem->intValue());
    }
};

class SimpleParserClassTest : public SimpleParser {
public:
    /// @brief Instantiation of getAndConvert
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter for error report
    /// @return a bool value
    bool getAsBool(ConstElementPtr scope, const std::string& name) {
        return (getAndConvert<bool, toBool>(scope, name, "boolean"));
    }

    /// @brief Convert to boolean
    ///
    /// @param str the string "false" or "true"
    /// @return false for "false" and true for "true"
    /// @thrown isc::OutOfRange if not "false" or "true'
    static bool toBool(const std::string& str) {
        if (str == "false") {
            return (false);
        } else if (str == "true") {
            return (true);
        } else {
            isc_throw(TypeError, "not a boolean: " << str);
        }
    }
};

// This test checks if the checkRequired method works as expected.
TEST_F(SimpleParserTest, checkRequired) {
    ConstElementPtr empty = Element::fromJSON("{ }");
    EXPECT_THROW(SimpleParser::checkRequired(REQUIRED_KEYWORDS, empty),
                 DhcpConfigError);
    ConstElementPtr other = Element::fromJSON("{ \"foo\": 1, \"bar\": 2 }");
    EXPECT_THROW(SimpleParser::checkRequired(REQUIRED_KEYWORDS, other),
                 DhcpConfigError);
    ConstElementPtr good = Element::fromJSON("{ \"foobar\": 2 }");
    EXPECT_NO_THROW(SimpleParser::checkRequired(REQUIRED_KEYWORDS, good));
}

// This test checks if the checkKeywords method works as expected.
TEST_F(SimpleParserTest, checkKeywords) {
    ConstElementPtr empty = Element::fromJSON("{ }");
    EXPECT_NO_THROW(SimpleParser::checkKeywords(KEYWORDS, empty));
    ConstElementPtr id = Element::fromJSON("{ \"id\": 1 }");
    EXPECT_NO_THROW(SimpleParser::checkKeywords(KEYWORDS, id));
    ConstElementPtr any = Element::fromJSON("{ \"any\": 1 }");
    EXPECT_NO_THROW(SimpleParser::checkKeywords(KEYWORDS, any));
    ConstElementPtr bad_id = Element::fromJSON("{ \"id\": true }");
    EXPECT_THROW(SimpleParser::checkKeywords(KEYWORDS, bad_id),
                 DhcpConfigError);
    ConstElementPtr bad_prefix = Element::fromJSON("{ \"prefix\": 12 }");
    EXPECT_THROW(SimpleParser::checkKeywords(KEYWORDS, bad_prefix),
                 DhcpConfigError);
    ConstElementPtr bad_map = Element::fromJSON("{ \"map\": [ ] }");
    EXPECT_THROW(SimpleParser::checkKeywords(KEYWORDS, bad_map),
                 DhcpConfigError);
    ConstElementPtr spurious = Element::fromJSON("{ \"spurious\": 1 }");
    EXPECT_THROW(SimpleParser::checkKeywords(KEYWORDS, spurious),
                 DhcpConfigError);

    // Bad type has precedence.
    ConstElementPtr bad = Element::fromJSON("{ \"spurious\": 1, \"id\": true }");
    try {
        SimpleParser::checkKeywords(KEYWORDS, bad);
        ADD_FAILURE() << "expect exception";
    } catch (const DhcpConfigError& ex) {
        EXPECT_EQ("'id' parameter is not an integer", std::string(ex.what()));
    } catch (...) {
        ADD_FAILURE() << "expect DhcpConfigError";
    }
}

// This test checks if the parameters can be inherited from the global
// scope to the subnet scope.
TEST_F(SimpleParserTest, deriveParams) {
    ElementPtr global = Element::fromJSON("{ \"renew-timer\": 1,"
                                          "  \"rebind-timer\": 2,"
                                          "  \"preferred-lifetime\": 3,"
                                          "  \"valid-lifetime\": 4"
                                          "}");
    ElementPtr subnet = Element::fromJSON("{ \"renew-timer\": 100 }");

    // we should inherit 3 parameters. Renew-timer should remain intact,
    // as it was already defined in the subnet scope.
    size_t num;
    EXPECT_NO_THROW(num = SimpleParser::deriveParams(global, subnet,
                                                     SAMPLE_INHERITS));
    EXPECT_EQ(3, num);

    // Check the values. 3 of them are inherited, while the fourth one
    // was already defined in the subnet, so should not be inherited.
    checkIntegerValue(subnet, "renew-timer", 100);
    checkIntegerValue(subnet, "rebind-timer", 2);
    checkIntegerValue(subnet, "preferred-lifetime", 3);
    checkIntegerValue(subnet, "valid-lifetime", 4);
}

// This test checks if global defaults are properly set for DHCPv6.
TEST_F(SimpleParserTest, setDefaults) {

    ElementPtr empty = Element::fromJSON("{ }");
    size_t num = 0;

    EXPECT_NO_THROW(num = SimpleParser::setDefaults(empty, SAMPLE_DEFAULTS));

    // We expect at least 4 parameters to be inserted.
    EXPECT_GE(num, 3);

    checkIntegerValue(empty, "valid-lifetime", 7200);
    checkIntegerValue(empty, "preferred-lifetime", 3600);
    checkIntegerValue(empty, "rebind-timer", 1800);
    checkIntegerValue(empty, "renew-timer", 900);
}

// This test checks if global defaults are properly set for DHCPv6.
TEST_F(SimpleParserTest, setListDefaults) {

    ElementPtr empty = Element::fromJSON("[{}, {}, {}]");
    size_t num;

    EXPECT_NO_THROW(num = SimpleParser::setListDefaults(empty, SAMPLE_DEFAULTS));

    // We expect at least 12 parameters to be inserted (3 entries, with
    // 4 parameters inserted in each)
    EXPECT_EQ(12, num);

    ASSERT_EQ(Element::list, empty->getType());
    ASSERT_EQ(3, empty->size());

    ConstElementPtr first = empty->get(0);
    ConstElementPtr second = empty->get(1);
    ConstElementPtr third = empty->get(2);

    checkIntegerValue(first, "valid-lifetime", 7200);
    checkIntegerValue(first, "preferred-lifetime", 3600);
    checkIntegerValue(first, "rebind-timer", 1800);
    checkIntegerValue(first, "renew-timer", 900);

    checkIntegerValue(second, "valid-lifetime", 7200);
    checkIntegerValue(second, "preferred-lifetime", 3600);
    checkIntegerValue(second, "rebind-timer", 1800);
    checkIntegerValue(second, "renew-timer", 900);

    checkIntegerValue(third, "valid-lifetime", 7200);
    checkIntegerValue(third, "preferred-lifetime", 3600);
    checkIntegerValue(third, "rebind-timer", 1800);
    checkIntegerValue(third, "renew-timer", 900);
}

// This test exercises the getIntType template
TEST_F(SimpleParserTest, getIntType) {

    SimpleParserClassTest parser;

    // getIntType checks it can be found
    ElementPtr not_found = Element::fromJSON("{ \"bar\": 1 }");
    EXPECT_THROW(parser.getUint8(not_found, "foo"), DhcpConfigError);

    // getIntType checks if it is an integer
    ElementPtr not_int = Element::fromJSON("{ \"foo\": \"xyz\" }");
    EXPECT_THROW(parser.getUint8(not_int, "foo"), DhcpConfigError);

    // getIntType checks bounds
    ElementPtr negative = Element::fromJSON("{ \"foo\": -1 }");
    EXPECT_THROW(parser.getUint8(negative, "foo"), DhcpConfigError);
    ElementPtr too_large = Element::fromJSON("{ \"foo\": 1024 }");
    EXPECT_THROW(parser.getUint8(too_large, "foo"), DhcpConfigError);

    // checks if getIntType can return the expected value
    ElementPtr hundred = Element::fromJSON("{ \"foo\": 100 }");
    uint8_t val = 0;
    EXPECT_NO_THROW(val = parser.getUint8(hundred, "foo"));
    EXPECT_EQ(100, val);
}

// This test exercises the getInteger with range checking
TEST_F(SimpleParserTest, getInteger) {

    // The value specified is 100.
    ElementPtr json = Element::fromJSON("{ \"bar\": 100 }");
    int64_t x;

    // Positive case: we expect value in range 0..200. All ok.
    EXPECT_NO_THROW(x = SimpleParser::getInteger(json, "bar", 0, 200));
    EXPECT_EQ(100, x);

    // Border checks: 100 for 100..200 range is still ok.
    EXPECT_NO_THROW(x = SimpleParser::getInteger(json, "bar", 100, 200));
    // Border checks: 100 for 1..100 range is still ok.
    EXPECT_NO_THROW(x = SimpleParser::getInteger(json, "bar", 1, 100));

    // Out of expected range. Should throw.
    EXPECT_THROW(x = SimpleParser::getInteger(json, "bar", 101, 200), OutOfRange);
    EXPECT_THROW(x = SimpleParser::getInteger(json, "bar", 1, 99), OutOfRange);
}

// This test exercises the getAndConvert template
TEST_F(SimpleParserTest, getAndConvert) {

    SimpleParserClassTest parser;

    // getAndConvert checks it can be found
    ElementPtr not_found = Element::fromJSON("{ \"bar\": \"true\" }");
    EXPECT_THROW(parser.getAsBool(not_found, "foo"), DhcpConfigError);

    // getAndConvert checks if it is a string
    ElementPtr not_bool = Element::fromJSON("{ \"foo\": 1 }");
    EXPECT_THROW(parser.getAsBool(not_bool, "foo"), DhcpConfigError);

    // checks if getAndConvert can return the expected value
    ElementPtr a_bool = Element::fromJSON("{ \"foo\": \"false\" }");
    bool val = true;
    EXPECT_NO_THROW(val = parser.getAsBool(a_bool, "foo"));
    EXPECT_FALSE(val);

    // getAndConvert checks conversion
    ElementPtr bad_bool = Element::fromJSON("{ \"foo\": \"bar\" }");
    EXPECT_THROW(parser.getAsBool(bad_bool, "bar"), DhcpConfigError);
}

// This test exercises the getIOAddress
TEST_F(SimpleParserTest, getIOAddress) {

    SimpleParserClassTest parser;

    // getAddress checks it can be found
    ElementPtr not_found = Element::fromJSON("{ \"bar\": 1 }");
    EXPECT_THROW(parser.getAddress(not_found, "foo"), DhcpConfigError);

    // getAddress checks if it is a string
    ElementPtr not_addr = Element::fromJSON("{ \"foo\": 1234 }");
    EXPECT_THROW(parser.getAddress(not_addr, "foo"), DhcpConfigError);

    // checks if getAddress can return the expected value of v4 address
    ElementPtr v4 = Element::fromJSON("{ \"foo\": \"192.0.2.1\" }");
    IOAddress val("::");
    EXPECT_NO_THROW(val = parser.getAddress(v4, "foo"));
    EXPECT_EQ("192.0.2.1" , val.toText());

    // checks if getAddress can return the expected value of v4 address
    ElementPtr v6 = Element::fromJSON("{ \"foo\": \"2001:db8::1\" }");
    EXPECT_NO_THROW(val = parser.getAddress(v6, "foo"));
    EXPECT_EQ("2001:db8::1" , val.toText());
}

// This test exercises getDouble()
TEST_F(SimpleParserTest, getDouble) {

    SimpleParserClassTest parser;
    std::string json =
    "{\n"
    "  \"string\" : \"12.3\",\n"
    "  \"bool\" : true, \n"
    "  \"int\" : 777, \n"
    "  \"map\" : {}, \n"
    "  \"list\" : [], \n"
    "  \"zero\" : 0.0, \n"
    "  \"fraction\" : .75, \n"
    "  \"negative\" : -1.45, \n"
    "  \"positive\" : 346.7 \n"
    "}\n";

    // Create our test set of parameters.
    ElementPtr elems;
    ASSERT_NO_THROW(elems = Element::fromJSON(json)) << " invalid JSON, test is broken";

    // Verify that a non-existant element is caught.
    EXPECT_THROW(parser.getDouble(elems, "not-there"), DhcpConfigError);

    // Verify that wrong element types are caught.
    EXPECT_THROW(parser.getDouble(elems, "string"), DhcpConfigError);
    EXPECT_THROW(parser.getDouble(elems, "int"), DhcpConfigError);
    EXPECT_THROW(parser.getDouble(elems, "bool"), DhcpConfigError);
    EXPECT_THROW(parser.getDouble(elems, "map"), DhcpConfigError);
    EXPECT_THROW(parser.getDouble(elems, "list"), DhcpConfigError);

    // Verify valid values are correct.
    double value;

    EXPECT_NO_THROW(value = parser.getDouble(elems, "zero"));
    EXPECT_EQ(0.0, value);

    EXPECT_NO_THROW(value = parser.getDouble(elems, "fraction"));
    EXPECT_EQ(.75, value);

    EXPECT_NO_THROW(value = parser.getDouble(elems, "negative"));
    EXPECT_EQ(-1.45, value);

    EXPECT_NO_THROW(value = parser.getDouble(elems, "positive"));
    EXPECT_EQ(346.7, value);
}
