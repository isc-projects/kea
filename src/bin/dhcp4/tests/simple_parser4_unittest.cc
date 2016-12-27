// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>
#include <dhcp4/simple_parser4.h>
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
};

// This test checks if global defaults are properly set for DHCPv4.
TEST_F(SimpleParser4Test, globalDefaults4) {

    ElementPtr empty = Element::fromJSON("{ }");
    size_t num = 0;

    EXPECT_NO_THROW(num = SimpleParser4::setAllDefaults(empty));


    // We expect at least 3 parameters to be inserted.
    EXPECT_TRUE(num >= 3);

    checkIntegerValue(empty, "valid-lifetime", 7200);
    checkIntegerValue(empty, "rebind-timer", 1800);
    checkIntegerValue(empty, "renew-timer", 900);

    // Make sure that preferred-lifetime is not set for v4 (it's v6 only
    // parameter)
    EXPECT_FALSE(empty->get("preferred-lifetime"));
}

// This test checks if the parameters can be inherited from the global
// scope to the subnet scope.
TEST_F(SimpleParser4Test, inheritGlobalToSubnet4) {
    ElementPtr global = Element::fromJSON("{ \"renew-timer\": 1,"
                                          "  \"rebind-timer\": 2,"
                                          "  \"preferred-lifetime\": 3,"
                                          "  \"valid-lifetime\": 4"
                                          "}");
    ElementPtr subnet = Element::fromJSON("{ \"renew-timer\": 100 }");

    // we should inherit 3 parameters. Renew-timer should remain intact,
    // as it was already defined in the subnet scope.
    size_t num;
    EXPECT_NO_THROW(num = SimpleParser4::deriveParams(global, subnet,
                          SimpleParser4::INHERIT_GLOBAL_TO_SUBNET4));
    EXPECT_EQ(2, num);

    // Check the values. 2 of them are inherited, while the third one
    // was already defined in the subnet, so should not be inherited.
    checkIntegerValue(subnet, "renew-timer", 100);
    checkIntegerValue(subnet, "rebind-timer", 2);
    checkIntegerValue(subnet, "valid-lifetime", 4);
}

};
};
};
