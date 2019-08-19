// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <cc/data.h>

using namespace isc::data;

namespace isc {
namespace dhcp {
namespace test {

/// @brief DHCP Parser test fixture class
class SimpleParser4Test : public ::testing::Test {
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

    /// @brief Checks if specified map has a string parameter with expected value
    ///
    /// @param map map to be checked
    /// @param param_name name of the parameter to be checked
    /// @param exp_value expected value of the parameter.
    void checkStringValue(const ConstElementPtr& map, const std::string& param_name,
                          std::string exp_value) {

        // First check if the passed element is a map.
        ASSERT_EQ(Element::map, map->getType());

        // Now try to get the element being checked
        ConstElementPtr elem = map->get(param_name);
        ASSERT_TRUE(elem);

        // Now check if it's indeed integer
        ASSERT_EQ(Element::string, elem->getType());

        // Finally, check if its value meets expectation.
        EXPECT_EQ(exp_value, elem->stringValue());
    }

    /// @brief Checks if specified map has a boolean parameter with expected value
    ///
    /// @param map map to be checked
    /// @param param_name name of the parameter to be checked
    /// @param exp_value expected value of the parameter.
    void checkBoolValue(const ConstElementPtr& map, const std::string& param_name,
                        bool exp_value) {

        // First check if the passed element is a map.
        ASSERT_EQ(Element::map, map->getType());

        // Now try to get the element being checked
        ConstElementPtr elem = map->get(param_name);
        ASSERT_TRUE(elem);

        // Now check if it's indeed integer
        ASSERT_EQ(Element::boolean, elem->getType());

        // Finally, check if its value meets expectation.
        EXPECT_EQ(exp_value, elem->boolValue());
    }
};

// This test checks if global defaults are properly set for DHCPv4.
TEST_F(SimpleParser4Test, globalDefaults4) {

    ElementPtr empty = parseJSON("{ }");
    size_t num = 0;

    EXPECT_NO_THROW(num = SimpleParser4::setAllDefaults(empty));


    // We expect at least 1 parameter to be inserted.
    EXPECT_TRUE(num >= 1);

    checkIntegerValue(empty, "valid-lifetime", 7200);

    // Timers are optional and by default are not present
    EXPECT_FALSE(empty->contains("rebind-timer"));
    EXPECT_FALSE(empty->contains("renew-timer"));

    // Make sure that preferred-lifetime is not set for v4 (it's v6 only
    // parameter)
    EXPECT_FALSE(empty->get("preferred-lifetime"));
}

// This test checks if the parameters can be inherited from the global
// scope to the subnet scope.
TEST_F(SimpleParser4Test, inheritGlobalToSubnet4) {
    ElementPtr global = parseJSON("{ \"renew-timer\": 1,"
                                  "  \"rebind-timer\": 2,"
                                  "  \"valid-lifetime\": 4,"
                                  "  \"min-valid-lifetime\": 3,"
                                  "  \"max-valid-lifetime\": 5,"
                                  "  \"subnet4\": [ { \"renew-timer\": 100 } ] "
                                  "}");
    ConstElementPtr subnets = global->find("subnet4");
    ASSERT_TRUE(subnets);
    ConstElementPtr subnet = subnets->get(0);
    ASSERT_TRUE(subnet);

    // we should inherit 4 parameters. Renew-timer should remain intact,
    // as it was already defined in the subnet scope.
    size_t num;
    EXPECT_NO_THROW(num = SimpleParser4::deriveParameters(global));
    EXPECT_EQ(4, num);

    // Check the values. 2 of them are inherited, while the third one
    // was already defined in the subnet, so should not be inherited.
    checkIntegerValue(subnet, "renew-timer", 100);
    checkIntegerValue(subnet, "rebind-timer", 2);
    checkIntegerValue(subnet, "valid-lifetime", 4);
    checkIntegerValue(subnet, "min-valid-lifetime", 3);
    checkIntegerValue(subnet, "max-valid-lifetime", 5);
}

// This test checks if the parameters in "subnet4" are assigned default values
// if not explicitly specified.
TEST_F(SimpleParser4Test, subnetDefaults4) {
    ElementPtr global = parseJSON("{ \"renew-timer\": 1,"
                                  "  \"rebind-timer\": 2,"
                                  "  \"valid-lifetime\": 4,"
                                  "  \"subnet4\": [ { } ] "
                                  "}");

    size_t num = 0;
    EXPECT_NO_THROW(num = SimpleParser4::setAllDefaults(global));
    EXPECT_LE(1, num); // at least 1 parameter has to be modified

    ConstElementPtr subnets = global->find("subnet4");
    ASSERT_TRUE(subnets);
    ConstElementPtr subnet = subnets->get(0);
    ASSERT_TRUE(subnet);

    // we should have "id" parameter with the default value of 0 added for us.
    checkIntegerValue(subnet, "id", 0);
}

// This test checks if the parameters in option-data are assigned default values
// if not explicitly specified.
TEST_F(SimpleParser4Test, optionDataDefaults4) {
    ElementPtr global = parseJSON("{ \"renew-timer\": 1,"
                                  "  \"rebind-timer\": 2,"
                                  "  \"valid-lifetime\": 4,"
                                  "  \"option-data\": [ { } ] "
                                  "}");

    size_t num = 0;
    EXPECT_NO_THROW(num = SimpleParser4::setAllDefaults(global));
    EXPECT_LE(1, num); // at least 1 parameter has to be modified

    ConstElementPtr options = global->find("option-data");
    ASSERT_TRUE(options);
    ConstElementPtr option = options->get(0);
    ASSERT_TRUE(option);

    // we should have appropriate default value set. See
    // SimpleParser4::OPTION4_DEFAULTS for a list of default values.
    checkStringValue(option, "space", "dhcp4");
    checkBoolValue(option, "csv-format", true);
}

// This test checks if the parameters in option-data are assigned default values
// if not explicitly specified.
TEST_F(SimpleParser4Test, optionDefDefaults4) {
    ElementPtr global = parseJSON("{ "
                                  "    \"option-def\": [ { } ] "
                                  "}");

    size_t num = 0;
    EXPECT_NO_THROW(num = SimpleParser4::setAllDefaults(global));
    EXPECT_LE(1, num); // at least 1 parameter has to be modified

    ConstElementPtr defs = global->find("option-def");
    ASSERT_TRUE(defs);
    ASSERT_EQ(1, defs->size());
    ConstElementPtr def = defs->get(0);
    ASSERT_TRUE(def);

    // we should have appropriate default value set. See
    // SimpleParser4::OPTION4_DEFAULTS for a list of default values.
    checkStringValue(def, "record-types", "");
    checkStringValue(def, "space", "dhcp4");
    checkStringValue(def, "encapsulate", "");
    checkBoolValue(def, "array", false);
}

};
};
};
