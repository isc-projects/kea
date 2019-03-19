// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/dhcp_config_error.h>
#include <process/config_ctl_parser.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <sstream>
#include <iostream>

using namespace isc::process;
using namespace isc::data;

// Verifies valid configurations are parsed correctly.  The test
// uses round-trip comparison of configuration Elements to determine
// if parsing was correct.
TEST(ConfigCtlInfoParser, validConfigs) {
    std::string configs[] = {
       "{}",

       "{ \"config-databases\": [], \n"
       "  \"config-fetch-wait-time\": 20 \n"
       "}",

       "{ \"config-databases\": [ \n"
       "    { \n"
       "        \"type\": \"mysql\", \n"
       "        \"user\":\"tom\", \n"
       "        \"password\":\"terrific\" \n"
       "    }, \n"
       "    { \n"
       "        \"type\": \"postgresql\",\n"
       "        \"user\":\"bob\", \n"
       "        \"password\":\"wonder\" \n"
       "    } \n"
       "] } \n"
    };

    for (auto config : configs) {
        ConfigControlParser parser;
        ConfigControlInfoPtr ctl_info;

        // Turn the JSON config into Elements.
        ElementPtr source_elem;
        ASSERT_NO_THROW (source_elem = Element::fromJSON(config)) <<
                " JSON error, test is broken: " << config;

        // Parse the Elements into a ConfigControlInfo.
        ASSERT_NO_THROW(ctl_info = parser.parse(source_elem));
        ASSERT_TRUE(ctl_info);

        // Turn the newly constructed info instance back into elements.
        ElementPtr parsed_elem;
        ASSERT_NO_THROW(parsed_elem = ctl_info->toElement());

        // When the config is empty, ControlConfigInfo::toElement still
        // generates a map with an empty db list.  Replace source for
        // element comparison below.
        if (source_elem->size() == 0) {
            ASSERT_NO_THROW (source_elem = Element::fromJSON(
                            "{ \"config-databases\": [] }"));
        }

        // The parsed element should match the source element.
        EXPECT_TRUE(parsed_elem->equals(*source_elem)) << "config: " << config;
    }
}

// Verify that invalid configurations fail to parse gracefully.
TEST(ConfigCtlInfoParser, invalidConfigs) {
    // Note that configurations are must be valid JSON, but invalid logically.
    std::string configs[] = {
       "{ \"config-databases\": \"not_list\" }",
       "{ \"config-databases\": [ \n"
       "    { \n"
       "        \"bogus\": \"param\" \n"
       "    } \n"
       "] } \n",
       "{ \"config-fetch-wait-time\": -1 }",
       "{ \"config-fetch-wait-time\": 65537 }",
       "{ \"config-fetch-wait-time\": \"a-string\" }",
    };

    for (auto config : configs) {
        ConfigControlParser parser;

        // Turn the JSON config into Elements.
        ElementPtr source_elem;
        ASSERT_NO_THROW (source_elem = Element::fromJSON(config)) <<
                " JSON error, test is broken: " << config;

        // Parse the Elements into a ConfigControlInfo.
        ASSERT_THROW(parser.parse(source_elem), isc::ConfigError)
                     << "config: " << config;
    }
}
