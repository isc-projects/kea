// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <stdint.h>
#include <cc/simple_parser.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::asiolink;
using isc::dhcp::DhcpConfigError;

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
