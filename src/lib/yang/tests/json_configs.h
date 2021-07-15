// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_JSON_CONFIGS_H
#define ISC_JSON_CONFIGS_H

#include <string>

namespace isc {
namespace yang {
namespace test {

/// @brief Empty DHCPv4 config.
const std::string emptyJson4 =
    "{\n"
    "  \"Dhcp4\": {\n"
    "  }\n"
    "}";

/// @brief A DHCPv4 config with one subnet with two pools.
const std::string subnetTwoPoolsJson4 =
    "{\n"
    "  \"Dhcp4\": {\n"
    "    \"subnet4\": [\n"
    "      {\n"
    "        \"id\": 111,\n"
    "        \"pools\": [\n"
    "          {\n"
    "            \"pool\": \"10.0.1.0/24\"\n"
    "          },\n"
    "          {\n"
    "            \"pool\": \"10.0.2.0/24\"\n"
    "          }\n"
    "        ],\n"
    "        \"subnet\": \"10.0.0.0/8\"\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

/// @brief A DHCPv6 config with one subnet with two pools and timers.
const std::string subnetTimersJson6 =
    "{\n"
    "  \"Dhcp6\": {\n"
    "    \"subnet6\": [\n"
    "      {\n"
    "        \"id\": 111,\n"
    "        \"renew-timer\": 1000,\n"
    "        \"rebind-timer\": 2000,\n"
    "        \"pools\": [\n"
    "          {\n"
    "            \"pool\": \"2001:db8::1:0/112\"\n"
    "          },\n"
    "          {\n"
    "            \"pool\": \"2001:db8::2:0/112\"\n"
    "          }\n"
    "        ],\n"
    "        \"subnet\": \"2001:db8::/48\"\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

/// @brief A DHCPv4 subnet with one pool and option data lists.
const std::string subnetOptionsJson4 =
    "{\n"
    "  \"Dhcp4\": {\n"
    "    \"subnet4\": [\n"
    "      {\n"
    "        \"id\": 111,\n"
    "        \"option-data\": [\n"
    "          {\n"
    "            \"code\": 100,\n"
    "            \"space\": \"dns\",\n"
    "            \"csv-format\": false,\n"
    "            \"data\": \"12121212\",\n"
    "            \"always-send\": false\n"
    "          }\n"
    "        ],\n"
    "        \"pools\": [\n"
    "          {\n"
    "            \"pool\": \"10.0.1.0/24\"\n"
    "          }\n"
    "        ],\n"
    "        \"subnet\": \"10.0.0.0/8\"\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

/// @brief Empty DHCPv6 config.
const std::string emptyJson6 =
    "{\n"
    "  \"Dhcp6\": {\n"
    "  }\n"
    "}";

/// @brief A DHCPv6 config with one subnet with one pool and option data lists.
const std::string subnetOptionsJson6 =
    "{\n"
    "  \"Dhcp6\": {\n"
    "    \"subnet6\": [\n"
    "      {\n"
    "        \"id\": 111,\n"
    "        \"pools\": [\n"
    "          {\n"
    "            \"option-data\": [\n"
    "              {\n"
    "                \"code\": 100,\n"
    "                \"space\": \"dns\",\n"
    "                \"csv-format\": false,\n"
    "                \"data\": \"12121212\",\n"
    "                \"always-send\": false\n"
    "              }\n"
    "            ],\n"
    "            \"pool\": \"2001:db8::1:0/112\"\n"
    "          }\n"
    "        ],\n"
    "        \"subnet\": \"2001:db8::/48\"\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

/// @brief A DHCPv6 config with one subnet with two pools.
const std::string subnetTwoPoolsJson6 =
    "{\n"
    "  \"Dhcp6\": {\n"
    "    \"subnet6\": [\n"
    "      {\n"
    "        \"id\": 111,\n"
    "        \"pools\": [\n"
    "          {\n"
    "            \"pool\": \"2001:db8::1:0/112\"\n"
    "          },\n"
    "          {\n"
    "            \"pool\": \"2001:db8::2:0/112\"\n"
    "          }\n"
    "        ],\n"
    "        \"subnet\": \"2001:db8::/48\"\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

/// @brief Example from the design document.
const std::string designExampleJson =
    "{\n"
    "  \"Dhcp6\": {\n"
    "    \"subnet6\": [\n"
    "      {\n"
    "        \"id\": 1,\n"
    "        \"subnet\": \"2001:db8:20:b00::/56\",\n"
    "        \"user-context\": { \"description\": \"example\" },\n"
    "        \"pd-pools\": [\n"
    "          {\n"
    "            \"prefix\": \"2001:db8:20:b00::\",\n"
    "            \"prefix-len\": 57\n"
//  "            \"delegated-len\": 57\n"
    "          }\n"
    "        ]\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

}  // namespace test
}  // namespace yang
}  // namespace isc

#endif // ISC_JSON_CONFIGS_H
