// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>
#include <d2/d2_simple_parser.h>
#include <d2/tests/parser_unittest.h>
#include <cc/data.h>

#include <boost/lexical_cast.hpp>

using namespace isc;
using namespace isc::data;
using namespace isc::d2;

namespace {

/// @brief Text fixture class for D2SimpleParser
class D2SimpleParserTest : public ::testing::Test {
public:
    /// @brief Checks if specified element matches the given integer default
    ///
    /// @param element defaulted element to check
    /// @param deflt SimpleDefault which supplied the default valaue
    void checkIntegerValue(const ConstElementPtr& element, const SimpleDefault& deflt)  {
        ASSERT_TRUE(element);

        // Verify it is an integer.
        ASSERT_EQ(Element::integer, element->getType());

        // Turn default value string into an int.
        int64_t default_value = 0;
        ASSERT_NO_THROW(default_value = boost::lexical_cast<int64_t>(deflt.value_));

        // Verify it has the expected value.
        EXPECT_EQ(default_value, element->intValue());
    }

    /// @brief Checks if specified element matches the given boolean default
    ///
    /// @param element defaulted element to check
    /// @param deflt SimpleDefault which supplied the default valaue
    void checkBooleanValue(const ConstElementPtr& element, const SimpleDefault& deflt)  {
        ASSERT_TRUE(element);

        // Verify it is a bool.
        ASSERT_EQ(Element::boolean, element->getType());

        // Turn default value string into a bool.
        bool default_value = false;
        ASSERT_NO_THROW(boost::lexical_cast<bool>(deflt.value_));

        // Verify it has the expected value.
        EXPECT_EQ(default_value, element->boolValue());
    }

    /// @brief Checks if specified element matches the given string default
    ///
    /// @param element defaulted element to check
    /// @param deflt SimpleDefault which supplied the default valaue
    void checkStringValue(const ConstElementPtr& element, const SimpleDefault& deflt)  {
        ASSERT_TRUE(element);

        // Verify it's a string
        ASSERT_EQ(Element::string, element->getType());

        // Verify it has the expected value
        EXPECT_EQ(deflt.value_, element->stringValue());
    }
};

// This test checks if global defaults are properly set for D2.
TEST_F(D2SimpleParserTest, globalD2Defaults) {

    ElementPtr empty = isc::d2::test::parseJSON("{ }");
    size_t num = 0;

    EXPECT_NO_THROW(num = D2SimpleParser::setAllDefaults(empty));

    // We expect 5 parameters to be inserted.
    EXPECT_EQ(num, 5);

    // Let's go over all parameters we have defaults for.
    BOOST_FOREACH(SimpleDefault deflt, D2SimpleParser::D2_GLOBAL_DEFAULTS) {
        ConstElementPtr x;
        ASSERT_NO_THROW(x = empty->get(deflt.name_));
        
        EXPECT_TRUE(x); 
        if (x) {
            if (deflt.type_ == Element::integer) {
                checkIntegerValue(x, deflt);
            } else if (deflt.type_ == Element::boolean) {
                checkBooleanValue(x, deflt);
            } else if (deflt.type_ == Element::string) {
                checkStringValue(x, deflt);
            } else {
                // add them if we need to. Like what do you if it's a map?
                ADD_FAILURE() << "default type not supported:" << deflt.name_
                            << " ,type: " << deflt.type_;
            } 
        }
    }
}

};

