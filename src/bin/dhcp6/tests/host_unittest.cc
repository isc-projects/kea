// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_vendor.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/lexical_cast.hpp>
#include <functional>
#include <list>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used by the Host reservation unit tests.
///
/// - Configuration 0:
///   Single subnet with two reservations, one with a hostname, one without
///
/// - Configuration 1:
///   Multiple reservations using different host identifiers.
///
/// - Configuration 2:
///   Same as configuration 1 but 'host-reservation-identifiers' specified
///   in non-default order.
///
/// - Configuration 3:
///   - Used to test that host specific options override pool specific,
///     subnet specific and global options.
///
/// - Configuration 4:
///   - Used to test that client receives options solely specified in a
///     host scope.
///
/// - Configuration 5:
///   - Used to test that host specific vendor options override globally
///     specified vendor options.
///
/// - Configuration 6:
///   - One subnet with very short pool, i.e. two addresses
///
/// - Configuration 7:
///   - Similar to Configuration 6, but one of the addresses reserved to client
///     with the DUID 04:03:02:01.
///
/// Descriptions of next configurations are in the comment with the number.
const char* CONFIGS[] = {
    // Configuration 0:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:04\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::babe\" ],"
        "        \"hostname\": \"alice\""
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1:1::babf\" ]"
        "    } ]"
        " } ]"
   "}",

    // Configuration 1:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"mac-sources\": [ \"ipv6-link-local\" ], "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"hw-address\": \"38:60:77:d5:ff:ee\","
        "        \"ip-addresses\": [ \"2001:db8:1::1\" ]"
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 2:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\", \"hw-address\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"mac-sources\": [ \"ipv6-link-local\" ], "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\" , "
        "    \"reservations\": ["
        "    {"
        "        \"hw-address\": \"38:60:77:d5:ff:ee\","
        "        \"ip-addresses\": [ \"2001:db8:1::1\" ]"
        "    },"
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 3:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"nisp-servers\","
        "    \"data\": \"3000:3::123\""
        "} ],"
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ {"
        "        \"pool\": \"2001:db8:1::/64\","
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:2::111\""
        "        } ]"
        "    } ],"
        "    \"interface\" : \"eth0\","
        "    \"option-data\": [ {"
        "        \"name\": \"dns-servers\","
        "        \"data\": \"3000:2::123\""
        "    },"
        "    {"
        "        \"name\": \"nis-servers\","
        "        \"data\": \"3000:2::123\""
        "    },"
        "    {"
        "        \"name\": \"sntp-servers\","
        "        \"data\": \"3000:2::123\""
        "    } ],"
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:1::234\""
        "        },"
        "        {"
        "            \"name\": \"nis-servers\","
        "            \"data\": \"3000:1::234\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 4:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "        \"option-data\": [ {"
        "            \"name\": \"dns-servers\","
        "            \"data\": \"3000:1::234\""
        "        },"
        "        {"
        "            \"name\": \"nis-servers\","
        "            \"data\": \"3000:1::234\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 5:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "    \"name\": \"vendor-opts\","
        "    \"data\": \"4491\""
        "},"
        "{"
        "    \"name\": \"tftp-servers\","
        "    \"space\": \"vendor-4491\","
        "    \"data\": \"3000:3::123\""
        "} ],"
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ],"
        "    \"interface\" : \"eth0\","
        "    \"reservations\": ["
        "    {"
        "        \"duid\": \"01:02:03:05\","
        "        \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "        \"option-data\": [ {"
        "            \"name\": \"vendor-opts\","
        "            \"data\": \"4491\""
        "        },"
        "        {"
        "            \"name\": \"tftp-servers\","
        "            \"space\": \"vendor-4491\","
        "            \"data\": \"3000:1::234\""
        "        } ]"
        "    } ]"
        " } ]"
    "}",

    // Configuration 6:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 40, "
        "\"preferred-lifetime\": 30,"
        "\"rebind-timer\": 20, "
        "\"renew-timer\": 10, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::2\" } ],"
        "    \"pd-pools\": ["
        "        {"
        "            \"prefix\": \"3000::\","
        "            \"prefix-len\": 119,"
        "            \"delegated-len\": 120"
        "        }"
        "    ],"
        "    \"interface\" : \"eth0\""
        "} ]"
    "}",

    // Configuration 7:
    "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"host-reservation-identifiers\": [ \"duid\" ],"
        "\"valid-lifetime\": 40, "
        "\"preferred-lifetime\": 30,"
        "\"rebind-timer\": 20, "
        "\"renew-timer\": 10, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::2\" } ],"
        "    \"pd-pools\": ["
        "        {"
        "            \"prefix\": \"3000::\","
        "            \"prefix-len\": 119,"
        "            \"delegated-len\": 120"
        "        }"
        "    ],"
        "    \"interface\" : \"eth0\","
        "    \"reservations\": ["
        "        {"
        "            \"duid\": \"04:03:02:01\","
        "            \"ip-addresses\": [ \"2001:db8:1::2\" ],"
        "            \"prefixes\": [ \"3000::100/120\" ]"
        "        }"
        "    ]"
        "} ]"
    "}",

    // Configuration 8: Global HRs TYPE_NAs
    "{ "
        "\"interfaces-config\": { \n"
        "  \"interfaces\": [ \"*\" ] \n"
        "},\n "
        "\"host-reservation-identifiers\": [ \"duid\", \"hw-address\" ], \n"
        "\"reservations\": [ \n"
        "{ \n"
        "   \"duid\": \"01:02:03:04\", \n"
        "   \"hostname\": \"duid-host-fixed-out-of-range\", \n"
        "   \"ip-addresses\": [ \"2001:db8:1::1\" ] \n"
        "}, \n"
        "{ \n"
        "   \"duid\": \"02:02:03:04\", \n"
        "   \"hostname\": \"duid-host-fixed-in-range\", \n"
        "   \"ip-addresses\": [ \"2001:db8:1::77\" ] \n"
        "}, \n"
        "{ \n"
        "   \"duid\": \"01:02:03:05\", \n"
        "   \"hostname\": \"duid-host-dynamic\" \n"
        "}, \n"
        "{ \n"
        "   \"hw-address\": \"38:60:77:d5:ff:ee\", \n"
        "   \"hostname\": \"hw-host\" \n"
        "} \n"
        "], \n"
        "\"valid-lifetime\": 4000,  \n"
        "\"preferred-lifetime\": 3000, \n"
        "\"rebind-timer\": 2000,  \n"
        "\"renew-timer\": 1000,  \n"
        "\"mac-sources\": [ \"ipv6-link-local\" ],  \n"
        "\"subnet6\": [  \n"
        " {  \n"
        "    \"id\": 1, \n"
        "    \"subnet\": \"2001:db8:1::/48\",  \n"
        "    \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], \n"
        "    \"interface\" : \"eth0\", \n"
        "    \"reservations-global\": true, \n"
        "    \"reservations-in-subnet\": false \n"
        " },"
        " {  \n"
        "    \"id\": 2, \n"
        "    \"subnet\": \"2001:db8:2::/48\",  \n"
        "    \"pools\": [ { \"pool\": \"2001:db8:2::/64\" } ], \n"
        "    \"interface\" : \"eth1\", \n"
        "    \"reservations\": [ \n"
        "    { \n"
        "       \"duid\": \"01:02:03:05\", \n"
        "       \"hostname\": \"subnet-duid-host\" \n"
        "    }] \n"
        " }"
        " ] \n"
    "} \n"
    ,
    // Configuration 9: Global HRs TYPE_PDs
    "{ "
        "\"interfaces-config\": { \n"
        "  \"interfaces\": [ \"*\" ] \n"
        "},\n "
        "\"host-reservation-identifiers\": [ \"duid\", \"hw-address\" ], \n"
        "\"reservations\": [ \n"
        "{ \n"
        "   \"duid\": \"01:02:03:04\", \n"
        "   \"hostname\": \"duid-host-fixed\", \n"
        "   \"prefixes\": [ \"4000::100/120\" ]"
        "}, \n"
        "{ \n"
        "   \"duid\": \"01:02:03:05\", \n"
        "   \"hostname\": \"duid-host-dynamic\" \n"
        "} \n"
        "], \n"
        "\"valid-lifetime\": 4000,  \n"
        "\"preferred-lifetime\": 3000, \n"
        "\"rebind-timer\": 2000,  \n"
        "\"renew-timer\": 1000,  \n"
        "\"mac-sources\": [ \"ipv6-link-local\" ],  \n"
        "\"subnet6\": [  \n"
        " {  \n"
        "    \"id\": 1, \n"
        "    \"subnet\": \"2001:db8:1::/48\",  \n"
        "    \"interface\" : \"eth0\", \n"
        "    \"reservations-global\": true, \n"
        "    \"reservations-in-subnet\": false, \n"
        "    \"pd-pools\": [ \n"
        "    { \n"
        "       \"prefix\": \"3000::\", \n"
        "       \"prefix-len\": 119, \n"
        "       \"delegated-len\": 120 \n"
        "    }] \n"
        " },"
        " {  \n"
        "    \"id\": 2, \n"
        "    \"subnet\": \"2001:db8:2::/48\",  \n"
        "    \"interface\" : \"eth1\", \n"
        "    \"pd-pools\": [ \n"
        "    { \n"
        "       \"prefix\": \"3001::\", \n"
        "       \"prefix-len\": 119, \n"
        "       \"delegated-len\": 120 \n"
        "    }], \n"
        "    \"reservations\": [ \n"
        "    { \n"
        "       \"duid\": \"01:02:03:05\", \n"
        "       \"hostname\": \"subnet-duid-host\" \n"
        "    }] \n"
        " }"
        " ] \n"
    "} \n",

    // Configuration 10: client-class reservation in global, shared network
    // and client-class guarded pools.
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"host-reservation-identifiers\": [ \"duid\", \"hw-address\" ], \n"
        "\"client-classes\": ["
        "{"
        "     \"name\": \"reserved_class\""
        "},"
        "{"
        "     \"name\": \"unreserved_class\","
        "     \"test\": \"not member('reserved_class')\""
        "}"
        "],\n"
        "\"reservations-global\": true,\n"
        "\"reservations-in-subnet\": false,\n"
        "\"valid-lifetime\": 4000,\n"
        "\"reservations\": [ \n"
        "{\n"
        "   \"duid\": \"01:02:03:05\",\n"
        "   \"client-classes\": [ \"reserved_class\" ]\n"
        "}\n"
        "],\n"
        "\"shared-networks\": [{"
        "    \"name\": \"frog\",\n"
        "    \"subnet6\": [\n"
        "        {\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"id\": 10,"
        "            \"pools\": ["
        "                {"
        "                    \"pool\": \"2001:db8:1::10-2001:db8:1::11\","
        "                    \"client-class\": \"reserved_class\""
        "                }"
        "            ],\n"
        "            \"interface\": \"eth0\"\n"
        "        },\n"
        "        {\n"
        "            \"subnet\": \"2001:db8:2::/64\", \n"
        "            \"id\": 11,"
        "            \"pools\": ["
        "                {"
        "                    \"pool\": \"2001:db8:2::10-2001:db8:2::11\","
        "                    \"client-class\": \"unreserved_class\""
        "                }"
        "            ],\n"
        "            \"interface\": \"eth0\"\n"
        "        }\n"
        "    ]\n"
        "}]\n"
    "}",

    // Configuration 11: client-class reservation in global, shared network
    // and client-class guarded subnets.
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"host-reservation-identifiers\": [ \"duid\", \"hw-address\" ], \n"
        "\"client-classes\": ["
        "{"
        "     \"name\": \"reserved_class\""
        "},"
        "{"
        "     \"name\": \"unreserved_class\","
        "     \"test\": \"not member('reserved_class')\""
        "}"
        "],\n"
        "\"reservations-global\": true,\n"
        "\"reservations-in-subnet\": false,\n"
        "\"valid-lifetime\": 4000,\n"
        "\"reservations\": [ \n"
        "{\n"
        "   \"duid\": \"01:02:03:05\",\n"
        "   \"client-classes\": [ \"reserved_class\" ]\n"
        "}\n"
        "],\n"
        "\"shared-networks\": [{"
        "    \"name\": \"frog\",\n"
        "    \"subnet6\": [\n"
        "        {\n"
        "            \"subnet\": \"2001:db8:1::/64\", \n"
        "            \"client-class\": \"reserved_class\","
        "            \"id\": 10,"
        "            \"pools\": ["
        "                {"
        "                    \"pool\": \"2001:db8:1::10-2001:db8:1::11\""
        "                }"
        "            ],\n"
        "            \"interface\": \"eth0\"\n"
        "        },\n"
        "        {\n"
        "            \"subnet\": \"2001:db8:2::/64\", \n"
        "            \"client-class\": \"unreserved_class\","
        "            \"id\": 11,"
        "            \"pools\": ["
        "                {"
        "                    \"pool\": \"2001:db8:2::10-2001:db8:2::11\""
        "                }"
        "            ],\n"
        "            \"interface\": \"eth0\"\n"
        "        }\n"
        "    ]\n"
        "}]\n"
    "}",

    // Configuration 12 client-class reservation and client-class guarded pools.
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"client-classes\": ["
        "{"
        "     \"name\": \"reserved_class\""
        "},"
        "{"
        "     \"name\": \"unreserved_class\","
        "     \"test\": \"not member('reserved_class')\""
        "}"
        "],\n"
        "\"valid-lifetime\": 4000,\n"
        "\"subnet6\": [\n"
        "    {\n"
        "        \"subnet\": \"2001:db8:1::/64\", \n"
        "        \"id\": 10,"
        "        \"reservations\": [{ \n"
        "            \"duid\": \"01:02:03:05\",\n"
        "            \"client-classes\": [ \"reserved_class\" ]\n"
        "        }],\n"
        "        \"pools\": ["
        "            {"
        "                \"pool\": \"2001:db8:1::10-2001:db8:1::11\","
        "                \"client-class\": \"reserved_class\""
        "            },"
        "            {"
        "                \"pool\": \"2001:db8:1::20-2001:db8:1::21\","
        "                \"client-class\": \"unreserved_class\""
        "            }"
        "        ],\n"
        "        \"interface\": \"eth0\"\n"
        "    }\n"
        "]\n"
    "}",

    // Configuration 13 multiple reservations for the same IP address.
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"valid-lifetime\": 4000,\n"
        "\"ip-reservations-unique\": false,\n"
        "\"subnet6\": [\n"
        "    {\n"
        "        \"subnet\": \"2001:db8:1::/64\",\n"
        "        \"id\": 10,"
        "        \"reservations\": [\n"
        "            {\n"
        "                \"duid\": \"01:02:03:04\",\n"
        "                \"ip-addresses\": [ \"2001:db8:1::15\" ]\n"
        "            },\n"
        "            {\n"
        "                \"duid\": \"01:02:03:05\",\n"
        "                \"ip-addresses\": [ \"2001:db8:1::15\" ]\n"
        "            }\n"
        "        ],\n"
        "        \"pools\": ["
        "            {\n"
        "                \"pool\": \"2001:db8:1::10-2001:db8:1::200\""
        "            }\n"
        "        ],\n"
        "        \"interface\": \"eth0\"\n"
        "    }\n"
        "]\n"
    "}",

    // Configuration 14 multiple reservations for the same delegated prefix.
    "{ \"interfaces-config\": {\n"
        "      \"interfaces\": [ \"*\" ]\n"
        "},\n"
        "\"valid-lifetime\": 4000,\n"
        "\"ip-reservations-unique\": false,\n"
        "\"subnet6\": [\n"
        "    {\n"
        "        \"subnet\": \"2001:db8:1::/64\",\n"
        "        \"id\": 10,"
        "        \"reservations\": [\n"
        "            {\n"
        "                \"duid\": \"01:02:03:04\",\n"
        "                \"prefixes\": [ \"3000::5a:0/112\" ]\n"
        "            },\n"
        "            {\n"
        "                \"duid\": \"01:02:03:05\",\n"
        "                \"prefixes\": [ \"3000::5a:0/112\" ]\n"
        "            }\n"
        "        ],\n"
        "        \"pd-pools\": ["
        "            {\n"
        "                \"prefix\": \"3000::\",\n"
        "                \"prefix-len\": 64,\n"
        "                \"delegated-len\": 112\n"
        "            }\n"
        "        ],\n"
        "        \"interface\": \"eth0\"\n"
        "    }\n"
        "]\n"
    "}"
};

/// @brief Base class representing leases and hints conveyed within IAs.
///
/// This is a base class for @ref Reservation and @ref Hint classes.
class IAResource {
public:

    /// @brief Constructor.
    ///
    /// Creates a resource instance from a string. The string is provided in
    /// one of the following formats:
    /// - "2001:db8:1::1" for addresses.
    /// - "2001:db8::/64" for prefixes.
    /// - "::/0" to mark lease or hint as unspecified (empty).
    IAResource(const std::string& resource);

    /// @brief Checks if resource is unspecified.
    ///
    /// @return true if resource is unspecified.
    bool isEmpty() const;

    /// @brief Checks if resource is a prefix.
    ///
    /// @return true if resource is a prefix.
    bool isPrefix() const;

    /// @brief Returns prefix or address (depending on resource type).
    const IOAddress& getPrefix() const;

    /// @brief Returns prefix length.
    uint8_t getPrefixLen() const;

    /// @brief Returns textual representation of the resource.
    std::string toText() const;

    /// @brief Operator converting resource to string.
    operator std::string() const;

private:

    /// @brief Holds prefix or address (depending on resource type).
    IOAddress prefix_;

    /// @brief Holds prefix length (for prefixes).
    uint8_t prefix_len_;

};

IAResource::IAResource(const std::string& resource)
    : prefix_(IOAddress::IPV6_ZERO_ADDRESS()), prefix_len_(0) {
    // Check if resource is a prefix, i.e. search for slash.
    size_t slash_pos = resource.find("/");
    if ((slash_pos != std::string::npos) && (slash_pos < resource.size() - 1)) {
        prefix_len_ = boost::lexical_cast<unsigned int>(resource.substr(slash_pos + 1));
    }
    prefix_ = IOAddress(resource.substr(0, slash_pos));
}

bool
IAResource::isEmpty() const {
    return (prefix_.isV6Zero() && (prefix_len_ == 0));
}

bool
IAResource::isPrefix() const {
    return (!isEmpty() && (prefix_len_ > 0));
}

const IOAddress&
IAResource::getPrefix() const {
    return (prefix_);
}

uint8_t
IAResource::getPrefixLen() const {
    return (prefix_len_);
}

std::string
IAResource::toText() const {
    std::ostringstream s;
    s << "\"" << prefix_;
    if (prefix_len_ > 0) {
        s << "/" << static_cast<int>(prefix_len_);
    }
    s << "\"";
    return (s.str());
}

IAResource::operator std::string() const {
    return (toText());
}

/// @brief Address or prefix reservation.
class Reservation : public IAResource {
public:

    /// @brief Constructor
    ///
    /// @param resource Resource string as for @ref IAResource constructor.
    Reservation(const std::string& resource)
        : IAResource(resource) {
    }

    /// @brief Convenience function returning unspecified resource.
    static const Reservation& UNSPEC();

};

const Reservation& Reservation::UNSPEC() {
    static Reservation unspec("::/0");
    return (unspec);
}

/// @brief Address or prefix hint.
class Hint : public IAResource {
public:

    /// @brief Constructor.
    ///
    /// Includes IAID of an IA in which hint should be placed.
    ///
    /// @param iaid IAID of IA in which hint should be placed.
    /// @param resource Resource string as for @ref IAResource constructor.
    Hint(const IAID& iaid, const std::string& resource)
        : IAResource(resource), iaid_(iaid) {
    }

    /// @brief Returns IAID.
    const IAID& getIAID() const;

    /// @brief Convenience function returning unspecified hint.
    static const Hint& UNSPEC();

private:

    /// @brief Holds IAID as 32-bit unsigned integer.
    IAID iaid_;
};

const IAID&
Hint::getIAID() const {
    return (iaid_);
}

const Hint& Hint::UNSPEC() {
    static Hint unspec(IAID(0), "::/0");
    return (unspec);
}

/// @brief Test fixture class for testing host reservations
class HostTest : public Dhcpv6SrvTest {
public:


    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    HostTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true),
          client_(),
          do_solicit_(std::bind(&Dhcp6Client::doSolicit, &client_, true)),
          do_solicit_request_(std::bind(&Dhcp6Client::doSARR, &client_)) {
    }

    /// @brief Checks that specified option contains a desired address.
    ///
    /// The option must cast to the @ref Option6AddrLst type. The function
    /// expects that this option contains at least one address and checks
    /// first address for equality with @ref expected_addr.
    ///
    /// @param option_type Option type.
    /// @param expected_addr Desired address.
    /// @param config Configuration obtained from the server.
    void verifyAddressOption(const uint16_t option_type,
                             const std::string& expected_addr,
                             const Dhcp6Client::Configuration& config) const {
        Option6AddrLstPtr opt = boost::dynamic_pointer_cast<
            Option6AddrLst>(config.findOption(option_type));
        ASSERT_TRUE(opt) << "option " << option_type << " not found or it "
            "is of incorrect type";
        Option6AddrLst::AddressContainer addrs = opt->getAddresses();
        ASSERT_GE(addrs.size(), 1) << "test failed for option type " << option_type;
        EXPECT_EQ(expected_addr, addrs[0].toText())
            << "test failed for option type " << option_type;
    }

    /// @brief Verifies that the reservation is retrieved by the server
    /// using one of the host identifiers.
    ///
    /// @param client Reference to a client to be used in the test.
    /// The client should be preconfigured to insert a specific identifier
    /// into the message, e.g. DUID, HW address etc.
    /// @param config_index Index of the configuration to use in the CONFIGS
    /// table.
    /// @param exp_ip_address Expected IPv6 address in the returned
    /// reservation.
    void testReservationByIdentifier(Dhcp6Client& client,
                                     const unsigned int config_index,
                                     const std::string& exp_ip_address) {
        configure(CONFIGS[config_index], *client.getServer());

        const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getAll();
        ASSERT_EQ(1, subnets->size());

        // Configure client to request IA_NA and append IA_NA option
        //  to the client's message.
        client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

        // Perform 4-way exchange.
        ASSERT_NO_THROW(client.doSARR());

        // Verify that the client we got the reserved address
        ASSERT_EQ(1, client.getLeaseNum());
        Lease6 lease_client = client.getLease(0);
        EXPECT_EQ(exp_ip_address, lease_client.addr_.toText());
    }

    /// @brief Initiate exchange with DHCPv6 server.
    ///
    /// This method initiates DHCPv6 message exchange between a specified
    /// client and the server. The msg_type is used to indicate what kind
    /// of exchange should be initiated. If the message type is a Renew
    /// or Rebind, the 4-way handshake is made first. If the message type
    /// is a Request, the Solicit-Advertise is done prior to this.
    ///
    /// @param msg_type Message type to be sent to the server.
    /// @param client Reference to a client to be used to initiate the
    /// exchange with the server.
    void doExchange(const uint16_t msg_type, Dhcp6Client& client);

    /// @brief Verifies that host specific options override subnet specific
    /// options.
    ///
    /// Overridden options are requested with Option Request option.
    ///
    /// @param msg_type DHCPv6 message type to be sent to the server. If the
    /// message type is Renew or Rebind, the 4-way exchange is made prior to
    /// sending a Renew or Rebind. For a Request case, the Solicit-Advertise
    /// is also performed.
    void testOverrideRequestedOptions(const uint16_t msg_type);

    /// @brief Verifies that client receives options when they are solely
    /// defined in the host scope (and not in the global, subnet or pool
    /// scope).
    ///
    /// @param msg_type DHCPv6 message type to be sent to the server. If the
    /// message type is Renew or Rebind, the 4-way exchange is made prior to
    /// sending a Renew or Rebind. For a Request case, the Solicit-Advertise
    /// is also performed.
    void testHostOnlyOptions(const uint16_t msg_type);

    /// @brief Verifies that host specific vendor options override vendor
    /// options defined in the global scope.
    ///
    /// @param msg_type DHCPv6 message type to be sent to the server. If the
    /// message type is Renew or Rebind, the 4-way exchange is made prior to
    /// sending a Renew or Rebind. For a Request case, the Solicit-Advertise
    /// is also performed.
    void testOverrideVendorOptions(const uint16_t msg_type);

    /// @brief Checks if the client obtained lease for specified reservation.
    ///
    /// @param r Reservation.
    /// @param [out] address_count This value is incremented if the client
    /// obtained the address lease.
    /// @param [out] prefix_count This value is incremented if the client
    /// obtained the prefix lease.
    void testLeaseForIA(const Reservation& r, size_t& address_count,
                        size_t& prefix_count);

    /// @brief Checks if the client obtained lease for specified hint.
    ///
    /// The hint belongs to a specific IA (identified by IAID) and is expected
    /// to be returned in this IA by the server.
    ///
    /// @param h Hint.
    void testLeaseForIA(const Hint& h);

    /// @brief A generic test for assigning multiple reservations to a single
    /// client sending multiple IAs.
    ///
    /// This test creates a server configuration which includes one subnet,
    /// address pool of "2001:db8:1::1 - 2001:db8:1::10" and the prefix pool
    /// of 3001::/32, with delegated prefix length of 64. The configuration
    /// may include between 0 and 6 reservations for a client with DUID of
    /// "01:02:03:04".
    ///
    /// The test performs an exchange with a server, typically 4-way exchange
    /// or Solicit-Advertise. The client's message includes 3 IA_NAs (with
    /// IAIDs in range of 1..3) and 3 IA_PDs (with IAIDs in range of 4..6).
    ///
    /// It is possible to specify hints for selected IAs. The IA is in such
    /// case identified by the IAID.
    ///
    /// The test expects that the server returns 6 leases. It checks if those
    /// leases contain all reserved addresses and prefixes specified as
    /// arguments of the test. If the number of IAs is greater than the
    /// number of reservations it checks that for the remaining IAs the
    /// leases from dynamic pools are assigned.
    ///
    /// The strict_iaid_check flag controls whether the test should verify
    /// that the address or prefix specified as a hint is assigned by the
    /// server to the IA in which the hint was placed by the client.
    ///
    /// @param client_operation Dhcp6Client function to be executed to
    /// perform an exchange with the server.
    /// @param r1 Reservation 1. Default value is "unspecified", in which
    /// case the reservation will not be created.
    /// @param r2 Reservation 2.
    /// @param r3 Reservation 3.
    /// @param r4 Reservation 4.
    /// @param r5 Reservation 5.
    /// @param r6 Reservation 6.
    /// @param strict_iaid_check Indicates if the test should check if the
    /// hints sent by the client have been allocated by the server to the
    /// particular IAs. Default value is NO (no checks).
    /// @param h1 Hint 1. Default value is "unspecified", in which case the
    /// hint will not be included.
    /// @param h2 Hint 2.
    /// @param h3 Hint 3.
    /// @param h4 Hint 4.
    /// @param h5 Hint 5.
    /// @param h6 Hint 6.
    void testMultipleIAs(const std::function<void ()>& client_operation,
                         const Reservation& r1 = Reservation::UNSPEC(),
                         const Reservation& r2 = Reservation::UNSPEC(),
                         const Reservation& r3 = Reservation::UNSPEC(),
                         const Reservation& r4 = Reservation::UNSPEC(),
                         const Reservation& r5 = Reservation::UNSPEC(),
                         const Reservation& r6 = Reservation::UNSPEC(),
                         const StrictIAIDChecking& strict_iaid_check =
                         StrictIAIDChecking::NO(),
                         const Hint& h1 = Hint::UNSPEC(),
                         const Hint& h2 = Hint::UNSPEC(),
                         const Hint& h3 = Hint::UNSPEC(),
                         const Hint& h4 = Hint::UNSPEC(),
                         const Hint& h5 = Hint::UNSPEC(),
                         const Hint& h6 = Hint::UNSPEC());

    /// @brief Checks if specified reservation is for address or prefix and
    /// stores reservation in the textual format on one of the lists.
    ///
    /// @param [out] address_list Reference to a list containing address
    /// reservations.
    /// @param [out] prefix_list Reference to a list containing prefix
    /// reservations.
    static void storeReservation(const Reservation& r,
                                 std::list<std::string>& address_list,
                                 std::list<std::string>& prefix_list);

    /// @brief Creates configuration for testing processing multiple IAs.
    ///
    /// This method creates a server configuration which includes one subnet,
    /// address pool of "2001:db8:1::1 - 2001:db8:1::10" and the prefix pool
    /// of 3001::/32, with delegated prefix length of 64. The configuration
    /// may include between 0 and 6 reservations for a client with DUID of
    /// "01:02:03:04".
    ///
    /// @param r1 Reservation 1. Default value is "unspecified" in which case
    /// the reservation will not be included in the configuration.
    /// @param r2 Reservation 2.
    /// @param r3 Reservation 3.
    /// @param r4 Reservation 4.
    /// @param r5 Reservation 5.
    /// @param r6 Reservation 6.
    ///
    /// @return Text containing server configuration in JSON format.
    std::string configString(const DUID& duid,
                             const Reservation& r1 = Reservation::UNSPEC(),
                             const Reservation& r2 = Reservation::UNSPEC(),
                             const Reservation& r3 = Reservation::UNSPEC(),
                             const Reservation& r4 = Reservation::UNSPEC(),
                             const Reservation& r5 = Reservation::UNSPEC(),
                             const Reservation& r6 = Reservation::UNSPEC()) const;

    /// @brief Verifies that an SARR exchange results in the expected lease
    ///
    /// @param client Client configured to request a single lease
    /// @param exp_address expected address/prefix of the lease
    /// @param exp_hostname expected hostname on the lease
    void sarrTest(Dhcp6Client& client, const std::string& exp_address,
                  const std::string& exp_hostname);

    /// @brief Configures client to include hint.
    ///
    /// @param client Reference to a client.
    /// @param hint Const reference to an object holding the hint.
    static void requestIA(Dhcp6Client& client, const Hint& hint);

    /// @brief Test pool or subnet selection using global class reservation.
    ///
    /// Verifies that client class specified in the global reservation
    /// may be used to influence pool or subnet selection.
    ///
    /// @param config_idx Index of the server configuration from the
    /// @c CONFIGS array.
    /// @param first_address Address to be allocated from the pool having
    /// a reservation.
    /// @param second_address Address to be allocated from the pool not
    /// having a reservation.
    void testGlobalClassSubnetPoolSelection(const int config_idx,
                                            const std::string& first_address = "2001:db8:1::10",
                                            const std::string& second_address = "2001:db8:2::10");

    /// @brief Test that two clients having reservations for the same IP
    /// address are offered the reserved lease.
    ///
    /// This test verifies the case when two clients have reservations for
    /// the same IP address. The first client sends Solicit and is offered
    /// the reserved address. At the same time, the second client having
    /// the reservation for the same IP address performs 4-way exchange
    /// using the reserved address as a hint in Solicit.
    /// The client gets the lease for this address. This test verifies
    /// that the allocation engine correctly identifies that the second
    /// client has a reservation for this address.
    ///
    /// @param duid1 Hardware address of the first client having the
    /// reservation.
    /// @param duid2 Hardware address of the second client having the
    /// reservation.
    void testMultipleClientsRace(const std::string& duid1,
                                 const std::string& duid2);

    /// @brief Configures client to include 6 IAs without hints.
    ///
    /// This method configures the client to include 3 IA_NAs and
    /// 3 IA_PDs.
    ///
    /// @param client Reference to a client.
    static void requestEmptyIAs(Dhcp6Client& client);

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

    /// @brief Instance of the common DHCPv6 client.
    Dhcp6Client client_;

    /// @brief Pointer to the Dhcp6Client::doSolicit method.
    std::function<void() > do_solicit_;

    /// @brief Pointer to the Dhcp6Client::doSARR method.
    std::function<void() > do_solicit_request_;
};

void
HostTest::doExchange(const uint16_t msg_type, Dhcp6Client& client) {
    switch (msg_type) {
    case DHCPV6_INFORMATION_REQUEST:
        ASSERT_NO_THROW(client.doInfRequest());
        break;
    case DHCPV6_REQUEST:
        ASSERT_NO_THROW(client.doSARR());
        break;
    case DHCPV6_SOLICIT:
        ASSERT_NO_THROW(client.doSolicit());
        break;
    case DHCPV6_RENEW:
        ASSERT_NO_THROW(client.doSARR());
        ASSERT_NO_THROW(client.doRenew());
        break;
    case DHCPV6_REBIND:
        ASSERT_NO_THROW(client.doSARR());
        ASSERT_NO_THROW(client.doRebind());
        break;
    default:
        ;
    }

    // Make sure that the server has responded with a Reply.
    ASSERT_TRUE(client.getContext().response_);
    ASSERT_EQ(DHCPV6_REPLY, client.getContext().response_->getType());

}


void
HostTest::testOverrideRequestedOptions(const uint16_t msg_type) {
    Dhcp6Client client;
    // Reservation has been made for a client with this DUID.
    client.setDUID("01:02:03:05");

    // Request all options specified in the configuration.
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);
    client.requestOption(D6O_NISP_SERVERS);
    client.requestOption(D6O_SNTP_SERVERS);

    configure(CONFIGS[3], *client.getServer());

    ASSERT_NO_FATAL_FAILURE(doExchange(msg_type, client));

    {
        SCOPED_TRACE("host specific dns-servers");
        // Host specific DNS server should be used.
        verifyAddressOption(D6O_NAME_SERVERS, "3000:1::234", client.config_);
    }

    {
        SCOPED_TRACE("host specific nis-servers");
        // Host specific NIS server should be used.
        verifyAddressOption(D6O_NIS_SERVERS, "3000:1::234", client.config_);
    }

    {
        SCOPED_TRACE("subnet specific sntp-servers");
        // Subnet specific SNTP server should be used as it is not specified
        // in a host scope.
        verifyAddressOption(D6O_SNTP_SERVERS, "3000:2::123", client.config_);
    }

    {
        SCOPED_TRACE("global nisp-servers");
        // Globally specified NISP server should be used as it is not
        // specified in a host scope.
        verifyAddressOption(D6O_NISP_SERVERS, "3000:3::123", client.config_);
    }
}

void
HostTest::testLeaseForIA(const Reservation& r, size_t& address_count,
                         size_t& prefix_count) {
    if (r.isPrefix()) {
        ++prefix_count;
        EXPECT_TRUE(client_.hasLeaseForPrefix(r.getPrefix(),
                                              r.getPrefixLen(),
                                              IAID(3 + prefix_count)));

    } else if (!r.isEmpty()) {
        ++address_count;
        EXPECT_TRUE(client_.hasLeaseForAddress(r.getPrefix(),
                                               IAID(address_count)));
    }
}

void
HostTest::testLeaseForIA(const Hint& h) {
    if (h.isPrefix()) {
        EXPECT_TRUE(client_.hasLeaseForPrefix(h.getPrefix(), h.getPrefixLen(),
                                              h.getIAID()))
            << "there is no lease for prefix " << h.toText()
            << " and IAID = " << h.getIAID();

    } else if (!h.isEmpty()) {
        EXPECT_TRUE(client_.hasLeaseForAddress(h.getPrefix(), h.getIAID()))
            << "there is no lease for address " << h.toText()
            << " and IAID = " << h.getIAID();
    }
}

void
HostTest::testMultipleIAs(const std::function<void ()>& client_operation,
                          const Reservation& r1, const Reservation& r2,
                          const Reservation& r3, const Reservation& r4,
                          const Reservation& r5, const Reservation& r6,
                          const StrictIAIDChecking& strict_iaid_check,
                          const Hint& h1, const Hint& h2 ,
                          const Hint& h3, const Hint& h4,
                          const Hint& h5, const Hint& h6) {
    client_.setDUID("01:02:03:04");

    /// Create configuration with 0 to 6 reservations.
    const std::string c = configString(*client_.getDuid(), r1, r2, r3,
                                       r4, r5, r6);

    ASSERT_NO_THROW(configure(c, *client_.getServer()));

    // First includes all IAs. They are initially empty.
    requestEmptyIAs(client_);

    // For each specified hint, include it in the respective IA. Hints
    // which are "unspecified" will not be included.
    requestIA(client_, h1);
    requestIA(client_, h2);
    requestIA(client_, h3);
    requestIA(client_, h4);
    requestIA(client_, h5);
    requestIA(client_, h6);


    // Send Solicit and require that the client saves received configuration
    // so as we can test that advertised configuration is correct.
    ASSERT_NO_THROW(client_operation());

    ASSERT_EQ(6, client_.getLeaseNum());

    // Count reserved addresses and prefixes assigned from reservations.
    size_t address_count = 0;
    size_t prefix_count = 0;

    testLeaseForIA(r1, address_count, prefix_count);
    testLeaseForIA(r2, address_count, prefix_count);
    testLeaseForIA(r3, address_count, prefix_count);
    testLeaseForIA(r4, address_count, prefix_count);
    testLeaseForIA(r5, address_count, prefix_count);
    testLeaseForIA(r6, address_count, prefix_count);

    // Get all addresses assigned from the dynamic pool (not reserved).
    std::vector<Lease6> leases =
        client_.getLeasesByAddressRange(IOAddress("2001:db8:1::1"),
                                        IOAddress("2001:db8:1::10"));
    // There are 3 IA_NAs and for a few we have assigned reserved addresses.
    // The remaining ones should be assigned from the dynamic pool.
    ASSERT_EQ(3 - address_count, leases.size());

    // Get all prefixes assigned from the dynamic pool (not reserved).
    leases =  client_.getLeasesByPrefixPool(IOAddress("3001::"), 32, 64);
    ASSERT_EQ(3 - prefix_count, leases.size());

    // Check that the hints have been allocated to respective IAs.
    if (strict_iaid_check) {
        testLeaseForIA(h1);
        testLeaseForIA(h2);
        testLeaseForIA(h3);
        testLeaseForIA(h4);
        testLeaseForIA(h5);
        testLeaseForIA(h6);
    }
}


void
HostTest::storeReservation(const Reservation& r,
                           std::list<std::string>& address_list,
                           std::list<std::string>& prefix_list) {
    if (!r.isEmpty()) {
        if (r.isPrefix()) {
            prefix_list.push_back(r);
        } else {
            address_list.push_back(r);
        }
    }
}

std::string
HostTest::configString(const DUID& duid,
                       const Reservation& r1, const Reservation& r2,
                       const Reservation& r3, const Reservation& r4,
                       const Reservation& r5, const Reservation& r6) const {
    std::list<std::string> address_list;
    std::list<std::string> prefix_list;
    storeReservation(r1, address_list, prefix_list);
    storeReservation(r2, address_list, prefix_list);
    storeReservation(r3, address_list, prefix_list);
    storeReservation(r4, address_list, prefix_list);
    storeReservation(r5, address_list, prefix_list);
    storeReservation(r6, address_list, prefix_list);

    std::ostringstream s;
    s << "{ "
        "\"interfaces-config\": {"
        "  \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 4000, "
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ "
        " { "
        "    \"subnet\": \"2001:db8:1::/48\", "
        "    \"pools\": [ { \"pool\": \"2001:db8:1::1 - 2001:db8:1::10\" } ],"
        "    \"pd-pools\": [ { \"prefix\": \"3001::\", \"prefix-len\": 32,"
        "                      \"delegated-len\": 64 } ],"
        "    \"interface\" : \"eth0\"";

    // Create reservations.
    if (!address_list.empty() || !prefix_list.empty()) {
        s << ","
            "    \"reservations\": ["
            "    {"
            "        \"duid\": ";
        s << "\"" << duid.toText() << "\",";

        if (!address_list.empty()) {
            s << "        \"ip-addresses\": [ "
              << boost::algorithm::join(address_list, ", ")
              << "]";
        }

        if (!prefix_list.empty()) {
            if (!address_list.empty()) {
                s << ", ";
            }
            s << "        \"prefixes\": [ "
              << boost::algorithm::join(prefix_list, ", ")
              << "]";
        }

        s <<  "    } ]";
    }

    s << " } ]"
         "}";

    return (s.str());
}

void
HostTest::requestIA(Dhcp6Client& client, const Hint& hint) {
    if ((hint.getIAID() != 0) && !hint.isEmpty()) {
        if (hint.isPrefix()) {
            client.requestPrefix(hint.getIAID(), hint.getPrefixLen(),
                                 hint.getPrefix());
        } else {
            client.requestAddress(hint.getIAID(), hint.getPrefix());
        }
    }
}

void
HostTest::testHostOnlyOptions(const uint16_t msg_type) {
    Dhcp6Client client;
    client.setDUID("01:02:03:05");
    client.requestOption(D6O_NAME_SERVERS);
    client.requestOption(D6O_NIS_SERVERS);

    configure(CONFIGS[3], *client.getServer());

    ASSERT_NO_FATAL_FAILURE(doExchange(msg_type, client));

    {
        SCOPED_TRACE("host specific dns-servers");
        // DNS servers are specified only in a host scope.
        verifyAddressOption(D6O_NAME_SERVERS, "3000:1::234", client.config_);
    }

    {
        SCOPED_TRACE("host specific nis-servers");
        // NIS servers are specified only in a host scope.
        verifyAddressOption(D6O_NIS_SERVERS, "3000:1::234", client.config_);
    }
}

void
HostTest::testOverrideVendorOptions(const uint16_t msg_type) {
    Dhcp6Client client;
    client.setDUID("01:02:03:05");

    // Client needs to include Vendor Specific Information option
    // with ORO suboption, which the server will use to determine
    // which suboptions should be returned to the client.
    OptionVendorPtr opt_vendor(new OptionVendor(Option::V6, VENDOR_ID_CABLE_LABS));
    // Include ORO with TFTP servers suboption code being requested.
    opt_vendor->addOption(OptionPtr(new OptionUint16(Option::V6, DOCSIS3_V6_ORO,
                                                     DOCSIS3_V6_TFTP_SERVERS)));
    client.addExtraOption(opt_vendor);

    configure(CONFIGS[5], *client.getServer());

    ASSERT_NO_FATAL_FAILURE(doExchange(msg_type, client));

    // Vendor Specific Information option should be returned by the server.
    OptionVendorPtr vendor_opt = boost::dynamic_pointer_cast<
        OptionVendor>(client.config_.findOption(D6O_VENDOR_OPTS));
    ASSERT_TRUE(vendor_opt);

    // TFTP server suboption should be returned because it was requested
    // with Option Request suboption.
    Option6AddrLstPtr tftp = boost::dynamic_pointer_cast<
        Option6AddrLst>(vendor_opt->getOption(DOCSIS3_V6_TFTP_SERVERS));
    ASSERT_TRUE(tftp);

    // Address specified in the host scope should be used.
    Option6AddrLst::AddressContainer addrs = tftp->getAddresses();
    ASSERT_EQ(addrs.size(), 1);
    EXPECT_EQ("3000:1::234", addrs[0].toText());
}

void
HostTest::testGlobalClassSubnetPoolSelection(const int config_idx,
                                             const std::string& first_address,
                                             const std::string& second_address) {
    Dhcp6Client client_resrv;

    // Use DUID for which we have host reservation including client class.
    client_resrv.setDUID("01:02:03:05");

    ASSERT_NO_FATAL_FAILURE(configure(CONFIGS[config_idx], *client_resrv.getServer()));

    // This client should be given an address from the 2001:db8:1::/64 subnet.
    // Let's use the 2001:db8:2::10 as a hint to make sure that the server
    // refuses allocating it and uses the sole pool available for this
    // client.
    client_resrv.requestAddress(1, IOAddress(second_address));
    ASSERT_NO_THROW(client_resrv.doSARR());
    ASSERT_EQ(1, client_resrv.getLeaseNum());
    Lease6 lease_client = client_resrv.getLease(0);
    EXPECT_EQ(first_address, lease_client.addr_.toText());

    // This client has no reservation and therefore should be
    // assigned to the unreserved_class and be given an address
    // from the other pool.
    Dhcp6Client client_no_resrv(client_resrv.getServer());
    client_no_resrv.setDUID("01:02:03:04");

    // Let's use the address of 2001:db8:1::10 as a hint to make sure that the
    // server refuses it in favor of the 2001:db8:2::10.
    client_no_resrv.requestAddress(1, IOAddress(first_address));
    ASSERT_NO_THROW(client_no_resrv.doSARR());
    ASSERT_EQ(1, client_no_resrv.getLeaseNum());
    lease_client = client_no_resrv.getLease(0);
    EXPECT_EQ(second_address, lease_client.addr_.toText());
}

void
HostTest::testMultipleClientsRace(const std::string& duid1,
                                  const std::string& duid2) {
    Dhcp6Client client1;
    client1.setDUID(duid1);
    ASSERT_NO_THROW(configure(CONFIGS[13], *client1.getServer()));
    // client1 performs 4-way exchange to get the reserved lease.
    requestIA(client1, Hint(IAID(1), "2001:db8:1::15"));
    ASSERT_NO_THROW(client1.doSARR());

    // Make sure the client has obtained reserved lease.
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));

    // Create another client that has a reservation for the same
    // IP address.
    Dhcp6Client client2(client1.getServer());
    client2.setDUID(duid2);
    requestIA(client2, Hint(IAID(1), "2001:db8:1::15"));

    // client2 performs 4-way exchange.
    ASSERT_NO_THROW(client2.doSARR());

    // Make sure the client didn't get the reserved lease. This lease has been
    // already taken by the client1.
    EXPECT_FALSE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));

    // Make sure the client2 got a lease from the configured pool.
    EXPECT_TRUE(client2.hasLeaseForAddressRange(IOAddress("2001:db8:1::10"),
                                                IOAddress("2001:db8:1::200")));
}

void
HostTest::requestEmptyIAs(Dhcp6Client& client) {
    // Create IAs with IAIDs between 1 and 6.
    client.requestAddress(1);
    client.requestAddress(2);
    client.requestAddress(3);
    client.requestPrefix(4);
    client.requestPrefix(5);
    client.requestPrefix(6);
}

void
HostTest::sarrTest(Dhcp6Client& client, const std::string& exp_address,
                   const std::string& exp_hostname) {
    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client got a dynamic address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ(exp_address, lease_client.addr_.toText());

    // Check that the server recorded the lease
    // and that the server lease has expected hostname.
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ(exp_hostname, lease_server->hostname_);
}


// Test basic SARR scenarios against a server configured with one subnet
// containing two reservations.  One reservation with a hostname, one
// without a hostname. Scenarios:
//
// - Verify that a client when matched to a host reservation with a hostname
// gets that reservation and the lease hostname matches the reserved hostname
//
// - Verify that a client when matched to a host reservation without a hostname
// gets that reservation and the lease hostname is blank
//
// - Verify that a client that does not match a host reservation gets a dynamic
// lease and the hostname for the lease is blank.
//
TEST_F(HostTest, basicSarrs) {
    Dhcp6Client client;
    configure(CONFIGS[0], *client.getServer());

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and append IA_NA option
    // to the client's message.
    client.setDUID("01:02:03:04");
    client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and lease has reserved hostname
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("alice", lease_server->hostname_);

    // Now redo the client, adding one to the DUID
    client.clearConfig();
    client.modifyDUID();

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babf", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and that the server lease has NO hostname
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("", lease_server->hostname_);

    // Now redo the client with yet another DUID and verify that
    // we get a dynamic address.
    client.clearConfig();
    client.modifyDUID();
    client.clearRequestedIAs();
    client.requestAddress(1234);

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Verify that the client got a dynamic address
    ASSERT_EQ(1, client.getLeaseNum());
    lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::", lease_client.addr_.toText());

    // Check that the server recorded the lease.
    // and that the server lease has NO hostname
    lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    EXPECT_EQ("", lease_server->hostname_);
}

// Test basic SARR and renew situation with a client that matches a host
// reservation
TEST_F(HostTest, sarrAndRenew) {
    Dhcp6Client client;

    configure(CONFIGS[0], *client.getServer());

    // Configure client to request IA_NA.
    client.requestAddress();

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Now play with time
    client.fastFwdTime(1000);

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Do not send the hint while renewing.
    client.clearRequestedIAs();

    // Send Renew message to the server.
    ASSERT_NO_THROW(client.doRenew());

    // Verify that we got an extended lease back
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client2.addr_.toText());

    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);

    // Make sure, that the client's lease matches the lease held by the
    // server and that we have the reserved host name.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    EXPECT_EQ("alice", lease_server2->hostname_);
}

// Test basic SARR and rebind situation with a client that matches a host
// reservation.
TEST_F(HostTest, sarrAndRebind) {
    Dhcp6Client client;

    configure(CONFIGS[0], *client.getServer());

    // Configure client to request IA_NA.
    client.requestAddress();

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(1, subnets->size());

    // Configure client to request IA_NA and aAppend IA_NA option
    //  to the client's message.
    client.setDUID("01:02:03:04");
    client.requestAddress(1234, IOAddress("2001:db8:1:1::dead:beef"));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // Now play with time
    client.fastFwdTime(1000);

    // Verify that the client we got the reserved address
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client.addr_.toText());

    // Do not send the hint while renewing.
    client.clearRequestedIAs();

    // Send Rebind message to the server.
    ASSERT_NO_THROW(client.doRebind());

    // Verify that we got an extended lease back
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client2 = client.getLease(0);
    EXPECT_EQ("2001:db8:1:1::babe", lease_client2.addr_.toText());

    // The client's lease should have been extended. The client will
    // update the cltt to current time when the lease gets extended.
    ASSERT_GE(lease_client2.cltt_ - lease_client.cltt_, 1000);

    // Make sure, that the client's lease matches the lease held by the
    // server and that we have the reserved host name.
    Lease6Ptr lease_server2 = checkLease(lease_client2);
    EXPECT_TRUE(lease_server2);
    EXPECT_EQ("alice", lease_server2->hostname_);
}

// This test verifies that the host reservation by DUID is found by the
// server.
TEST_F(HostTest, reservationByDUID) {
    Dhcp6Client client;
    // Set DUID matching the one used to create host reservations.
    client.setDUID("01:02:03:05");
    // Run the actual test.
    testReservationByIdentifier(client, 1, "2001:db8:1::2");
}

// This test verifies that the host reservation by HW address is found
// by the server.
TEST_F(HostTest, reservationByHWAddress) {
    Dhcp6Client client;
    // Set link local address for the client which the server will
    // use to decode the HW address as 38:60:77:d5:ff:ee. This
    // decoded address will be used to search for host reservations.
    client.setLinkLocal(IOAddress("fe80::3a60:77ff:fed5:ffee"));
    // Run the actual test.
    testReservationByIdentifier(client, 1, "2001:db8:1::1");
}

// This test verifies that order in which host identifiers are used to
// retrieve host reservations can be controlled.
TEST_F(HostTest, hostIdentifiersOrder) {
    Dhcp6Client client;
    // Set DUID matching the one used to create host reservations.
    client.setDUID("01:02:03:05");
    // Set link local address for the client which the server will
    // use to decode the HW address as 38:60:77:d5:ff:ee. This
    // decoded address will be used to search for host reservations.
    client.setLinkLocal(IOAddress("fe80::3a60:77ff:fed5:ffee"));
    testReservationByIdentifier(client, 2, "2001:db8:1::2");
}

// This test checks that host specific options override subnet specific
// and pool specific options. Overridden options are requested with Option
// Request option (Information-request case).
TEST_F(HostTest, overrideRequestedOptionsInformationRequest) {
    testOverrideRequestedOptions(DHCPV6_INFORMATION_REQUEST);
}

// This test checks that host specific options override subnet specific
// and pool specific options. Overridden options are requested with Option
// Request option (Request case).
TEST_F(HostTest, overrideRequestedOptionsRequest) {
    testOverrideRequestedOptions(DHCPV6_REQUEST);
}

// This test checks that host specific options override subnet specific
// and pool specific options. Overridden options are requested with Option
// Request option (Renew case).
TEST_F(HostTest, overrideRequestedOptionsRenew) {
    testOverrideRequestedOptions(DHCPV6_RENEW);
}

// This test checks that host specific options override subnet specific
// and pool specific options. Overridden options are requested with Option
// Request option (Rebind case).
TEST_F(HostTest, overrideRequestedOptionsRebind) {
    testOverrideRequestedOptions(DHCPV6_REBIND);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Information-request case).
TEST_F(HostTest, testHostOnlyOptionsInformationRequest) {
    testHostOnlyOptions(DHCPV6_INFORMATION_REQUEST);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Request case).
TEST_F(HostTest, testHostOnlyOptionsRequest) {
    testHostOnlyOptions(DHCPV6_REQUEST);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Renew case).
TEST_F(HostTest, testHostOnlyOptionsRenew) {
    testHostOnlyOptions(DHCPV6_RENEW);
}

// This test checks that client receives options when they are
// solely defined in the host scope and not in the global or subnet
// scope (Rebind case).
TEST_F(HostTest, testHostOnlyOptionsRebind) {
    testHostOnlyOptions(DHCPV6_REBIND);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (Request case).
TEST_F(HostTest, overrideVendorOptionsRequest) {
    testOverrideVendorOptions(DHCPV6_REQUEST);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (Renew case).
TEST_F(HostTest, overrideVendorOptionsRenew) {
    testOverrideVendorOptions(DHCPV6_RENEW);
}

// This test checks that host specific vendor options override vendor
// options defined in the global scope (Rebind case).
TEST_F(HostTest, overrideVendorOptionsRebind) {
    testOverrideVendorOptions(DHCPV6_REBIND);
}

// In this test the client sends Solicit with 3 IA_NAs and 3 IA_PDs
// without hints and the server should return those IAs with 3 reserved
// addresses and 3 reserved prefixes.
TEST_F(HostTest, multipleIAsSolicit) {
    testMultipleIAs(do_solicit_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation("3000:1:3::/64"));
}

// In this test the client performs 4-way exchange, sending 3 IA_NAs
// and 3 IA_PDs without hints. The server should return those IAs
// with 3 reserved addresses and 3 reserved prefixes.
TEST_F(HostTest, multipleIAsRequest) {
    testMultipleIAs(do_solicit_request_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation("3000:1:3::/64"));
}

// In this test the client sends Solicit with 3 IA_NAs and 3 IA_PDs
// without hints. The server has 2 reservations for addresses and
// 2 reservations for prefixes for this client. The server should
// assign reserved addresses and prefixes to the client, and return
// them in 2 IA_NAs and 2 IA_PDs. For the remaining IA_NA and IA_PD
// the server should allocate address and prefix from a dynamic pools.
TEST_F(HostTest, staticAndDynamicIAs) {
    testMultipleIAs(do_solicit_,
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:3::/64"));
}

// In this test the client sends Solicit with 3 IA_NAs and 3 IA_PDs.
// The client includes an address hint for IAID = 1, a prefix length
// hint for the IAID = 5, and the prefix hint for IAID = 6. The hints
// match the reserved resources and should be allocated for the client.
TEST_F(HostTest, multipleIAsHintsForReservations) {
    testMultipleIAs(do_solicit_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation("3000:1:3::/64"),
                    StrictIAIDChecking::NO(),
                    Hint(IAID(1), "2001:db8:1:1::2"),
                    Hint(IAID(5), "::/64"),
                    Hint(IAID(6), "3000:1:1::/64"));
}

// In this test the client sends Solicit with 3 IA_NAs and 3 IA_PDs.
// The client includes one address hint for IAID = 1 and one
// prefix hint for IAID = 6. The hints point to an address and prefix
// from the dynamic pools, but because the server has reservations
// for other addresses and prefixes outside the pool, the address
// and prefix specified as hint should not be allocated. Instead
// the server should allocate reserved leases.
TEST_F(HostTest, multipleIAsHintsInPool) {
    testMultipleIAs(do_solicit_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation("3000:1:3::/64"),
                    StrictIAIDChecking::NO(),
                    Hint(IAID(1), "2001:db8:1::2"),
                    Hint(IAID(6), "3001::/64"));
}

// In this test, the client sends Solicit with 3 IA_NAs and 3 IA_PDs.
// The client includes one address hint for which the client has
// reservation, one prefix hint for which the client has reservation,
// one hint for an address from the dynamic pool and one hint for a
// prefix from a dynamic pool. The server has reservations for 2
// addresses and 2 prefixes. The server should allocate reserved
// leases and address and prefix from a dynamic pool, which client
// included as hints.
TEST_F(HostTest, staticAndDynamicIAsHints) {
    testMultipleIAs(do_solicit_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation::UNSPEC(),
                    Reservation::UNSPEC(),
                    StrictIAIDChecking::NO(),
                    Hint(IAID(1), "2001:db8:1::2"),
                    Hint(IAID(3), "2001:db8:1:1::1"),
                    Hint(IAID(5), "3001::/64"),
                    Hint(IAID(6), "3000::/64"));
}

// In this test, the client sends Solicit with 3 IA_NAs and 3 IA_PDs.
// The server has reservation for two addresses and two prefixes for
// this client. The client includes address hint in the third IA_NA
// and in the third IA_PD. The server should offer 2 addresses in the
// first two IA_NAs and 2 prefixes in the two IA_PDs. The server should
// respect hints provided within the 3rd IA_NA and 3rd IA_PD. The server
// wouldn't respect hints if they were provided within 1st or 2nd IA of
// a given type, because the server always tries to allocate the
// reserved leases in the first place.
TEST_F(HostTest, staticAndDynamicIAsHintsStrictIAIDCheck) {
    testMultipleIAs(do_solicit_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation::UNSPEC(),
                    Reservation::UNSPEC(),
                    StrictIAIDChecking::YES(),
                    Hint(IAID(3), "2001:db8:1::5"),
                    Hint(IAID(6), "3001:0:0:10::/64"));
}

// In this test, the client performs 4-way exchange and includes 3 IA_NAs
// and 3 IA_PDs. The client provides no hints. The server has 3 address
// reservations and 3 prefix reservations for this client and allocates them
// as a result of 4-way exchange. The client then sends a Renew and the server
// should renew all leases allocated for the client during the 4-way exchange.
TEST_F(HostTest, multipleIAsRenew) {
    // 4-way exchange
    testMultipleIAs(do_solicit_request_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation("3000:1:3::/64"));

    // Renew
    ASSERT_NO_THROW(client_.doRenew());

    // Make sure that the client still has the same leases.
    ASSERT_EQ(6, client_.getLeaseNum());

    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::1")));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::2")));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:1::"), 64));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:2::"), 64));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:3::"), 64));
}

// In this test, the client performs 4-way exchange and includes 3 IA_NAs
// and IA_PDs. The server has 3 address and 3 prefix reservations for the
// client and allocates them all. Once the 4-way exchange is complete,
// the client sends Solicit in which it specifies hints for all IAs. The
// hints are for the reserved addresses but some of them are included in
// different IAs than they are assigned to. The server should ignore hints
// and respond with currently assigned leases.
TEST_F(HostTest, multipleIAsSolicitAfterAcquisition) {
    // 4-way exchange
    testMultipleIAs(do_solicit_request_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("2001:db8:1:1::3"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"),
                    Reservation("3000:1:3::/64"));

    client_.clearRequestedIAs();

    // Specify hints.

    // "2001:db8:1:1::1" is allocated for IAID = 1 but we specify it as
    // a hint for IAID = 3 and so on.
    requestIA(client_, Hint(IAID(3), "2001:db8:1:1::1"));
    requestIA(client_, Hint(IAID(2), "2001:db8:1:1::2"));
    requestIA(client_, Hint(IAID(1), "2001:db8:1:1::3"));
    requestIA(client_, Hint(IAID(6), "3000:1:1::/64"));
    requestIA(client_, Hint(IAID(5), "3000:1:2::/64"));
    requestIA(client_, Hint(IAID(4), "3000:1:3::/64"));

    // Send Solicit with hints as specified above.
    ASSERT_NO_THROW(do_solicit_());

    // Make sure that the client still has the same leases and the leases
    // should be assigned to the same IAs.
    ASSERT_EQ(6, client_.getLeaseNum());

    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::1"),
                                           IAID(1)));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::2"),
                                           IAID(2)));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::3"),
                                           IAID(3)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:1::"), 64,
                                          IAID(4)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:2::"), 64,
                                          IAID(5)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:3::"), 64,
                                          IAID(6)));
}

// In this test, the client performs 4-way exchange and includes 3 IA_NAs and
// 3 IA_PDs and includes no hints. The server has reservations for 2 addresses
// and 2 prefixes for this client. The server allocates reserved leases and
// an additional address and prefix from the dynamic pools. The server is
// reconfigured to add 3rd address and 3rd prefix reservation for the client.
// The client sends a Renew and the server should renew existing leases and
// allocate newly reserved address and prefix, replacing the previously
// allocated dynamic leases. For both dynamically allocated leases, the
// server should return IAs with zero lifetimes.
TEST_F(HostTest, appendReservationDuringRenew) {
    // 4-way exchange to acquire 4 reserved leases and 2 dynamic leases.
    testMultipleIAs(do_solicit_request_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"));

    // The server must have not lease for the address and prefix for which
    // we will later make reservations, because these are outside of the
    // dynamic pool.
    ASSERT_FALSE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    ASSERT_FALSE(client_.hasLeaseForPrefix(IOAddress("3000:1:3::"), 64));

    // Retrieve leases from the dynamic pools and store them so as we can
    // later check that they were returned with zero lifetimes when the
    // reservations are added.
    std::vector<Lease6> leases =
        client_.getLeasesByAddressRange(IOAddress("2001:db8:1::1"),
                                        IOAddress("2001:db8:1::10"));
    ASSERT_EQ(1, leases.size());
    IOAddress dynamic_address_lease = leases[0].addr_;

    leases = client_.getLeasesByPrefixPool(IOAddress("3001::"), 32, 64);
    ASSERT_EQ(1, leases.size());
    IOAddress dynamic_prefix_lease = leases[0].addr_;

    // Add two additional reservations.
    std::string c = configString(*client_.getDuid(),
                                 Reservation("2001:db8:1:1::1"),
                                 Reservation("2001:db8:1:1::2"),
                                 Reservation("2001:db8:1:1::3"),
                                 Reservation("3000:1:1::/64"),
                                 Reservation("3000:1:2::/64"),
                                 Reservation("3000:1:3::/64"));

    ASSERT_NO_THROW(configure(c, *client_.getServer()));

    // Client renews and includes all leases it currently has in the IAs.
    ASSERT_NO_THROW(client_.doRenew());

    // The expectation is that the server allocated two new reserved leases to
    // the client and removed leases allocated from the dynamic pools. The
    // number if leases in the server configuration should include those that
    // are returned with zero lifetimes. Hence, the total number of leases
    // should be equal to 6 + 2 = 8.
    ASSERT_EQ(8, client_.getLeaseNum());

    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::1")));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::2")));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:1::"), 64));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:2::"), 64));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:3::"), 64));

    // Make sure that the replaced leases have been returned with zero lifetimes.
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForAddress(dynamic_address_lease));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForPrefix(dynamic_prefix_lease, 64));

    // Now let's test the scenario when all reservations are removed for this
    // client.
    c = configString(*client_.getDuid());

    ASSERT_NO_THROW(configure(c, *client_.getServer()));

    // An attempt to renew should result in removing all allocated leases,
    // because these leases are no longer reserved and they don't belong to the
    // dynamic pools.
    ASSERT_NO_THROW(client_.doRenew());

    // The total number of leases should include removed leases and newly
    // allocated once, i.e. 6 + 6 = 12.
    ASSERT_EQ(12, client_.getLeaseNum());

    // All removed leases should be returned with zero lifetimes.
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1:1::1")));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1:1::2")));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1:1::3")));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForPrefix(IOAddress("3000:1:1::"), 64));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForPrefix(IOAddress("3000:1:2::"), 64));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForPrefix(IOAddress("3000:1:3::"), 64));

    // Make sure that all address leases are within the dynamic pool range.
    leases = client_.getLeasesByAddressRange(IOAddress("2001:db8:1::1"),
                                            IOAddress("2001:db8:1::10"));
    EXPECT_EQ(3, leases.size());

    // Make sure that all prefix leases are also within the dynamic pool range.
    leases = client_.getLeasesByPrefixPool(IOAddress("3001::"), 32, 64);
    EXPECT_EQ(3, leases.size());
}

// In this test, the client performs 4-way exchange and includes 3 IA_NAs
// and 3 IA_PDs. Initially, the server has 2 address reservations and
// 2 prefix reservations for this client. The server allocates the 2
// reserved addresses to the first 2 IA_NAs and 2 reserved prefixes to the
// first two IA_PDs. The server is reconfigured and 2 new reservations are
// inserted: new address reservation before existing address reservations
// and prefix reservation before existing prefix reservations.
// The server should detect that leases already exist for reserved addresses
// and prefixes and it should not remove existing leases. Instead, it should
// replace dynamically allocated leases with newly added reservations
TEST_F(HostTest, insertReservationDuringRenew) {
    // 4-way exchange to acquire 4 reserved leases and 2 dynamic leases.
    testMultipleIAs(do_solicit_request_,
                    Reservation("2001:db8:1:1::1"),
                    Reservation("2001:db8:1:1::2"),
                    Reservation("3000:1:1::/64"),
                    Reservation("3000:1:2::/64"));

    // The server must have not lease for the address and prefix for which
    // we will later make reservations, because these are outside of the
    // dynamic pool.
    ASSERT_FALSE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::3")));
    ASSERT_FALSE(client_.hasLeaseForPrefix(IOAddress("3000:1:3::"), 64));

    // Retrieve leases from the dynamic pools and store them so as we can
    // later check that they were returned with zero lifetimes when the
    // reservations are added.
    std::vector<Lease6> leases =
        client_.getLeasesByAddressRange(IOAddress("2001:db8:1::1"),
                                        IOAddress("2001:db8:1::10"));
    ASSERT_EQ(1, leases.size());
    IOAddress dynamic_address_lease = leases[0].addr_;

    leases = client_.getLeasesByPrefixPool(IOAddress("3001::"), 32, 64);
    ASSERT_EQ(1, leases.size());
    IOAddress dynamic_prefix_lease = leases[0].addr_;

    // Add two additional reservations.
    std::string c = configString(*client_.getDuid(),
                                 Reservation("2001:db8:1:1::3"),
                                 Reservation("2001:db8:1:1::1"),
                                 Reservation("2001:db8:1:1::2"),
                                 Reservation("3000:1:3::/64"),
                                 Reservation("3000:1:1::/64"),
                                 Reservation("3000:1:2::/64"));

    ASSERT_NO_THROW(configure(c, *client_.getServer()));

    // Client renews and includes all leases it currently has in the IAs.
    ASSERT_NO_THROW(client_.doRenew());

    // The expectation is that the server allocated two new reserved leases to
    // the client and removed leases allocated from the dynamic pools. The
    // number if leases in the server configuration should include those that
    // are returned with zero lifetimes. Hence, the total number of leases
    // should be equal to 6 + 2 = 8.
    ASSERT_EQ(8, client_.getLeaseNum());

    // Even though the new reservations have been added before existing
    // reservations, the server should assign them to the IAs with
    // IAID = 3 (for address) and IAID = 6 (for prefix).
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::1"),
                                           IAID(1)));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::2"),
                                           IAID(2)));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1:1::3"),
                                           IAID(3)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:1::"), 64,
                                          IAID(4)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:2::"), 64,
                                          IAID(5)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3000:1:3::"), 64,
                                          IAID(6)));

    // Make sure that the replaced leases have been returned with zero lifetimes.
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForAddress(dynamic_address_lease));
    EXPECT_TRUE(client_.hasLeaseWithZeroLifetimeForPrefix(dynamic_prefix_lease, 64));
}

// In this test there are two clients. One client obtains two leases: one
// for a prefix, another one for an address. The server is reconfigured
// to make 4 reservations to a different client. Two of those reservations
// are for the prefix and the address assigned to the first client. The
// second client performs 4-way exchange and the server detects that two
// reserved leases are not available because they are in use by another
// client. The server assigns available address and prefix and an address
// and prefix from dynamic pool. The first client renews and the server
// detects that the renewed leases are reserved for another client. As
// a result, the client obtains an address and prefix from the dynamic
// pools. The second client renews and it obtains all reserved
// addresses and prefixes.
TEST_F(HostTest, multipleIAsConflict) {
    Dhcp6Client client;
    client.setDUID("01:02:03:05");

    // Create configuration without any reservations.
    std::string c = configString(*client_.getDuid());

    ASSERT_NO_THROW(configure(c, *client_.getServer()));

    // First client performs 4-way exchange and obtains an address and
    // prefix indicated in hints.
    requestIA(client, Hint(IAID(1), "2001:db8:1::1"));
    requestIA(client, Hint(IAID(2), "3001:0:0:10::/64"));

    ASSERT_NO_THROW(client.doSARR());

    // Make sure the client has obtained requested leases.
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1::1"), IAID(1)));
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("3001:0:0:10::"), 64,
                                         IAID(2)));

    // Reconfigure the server to make reservations for the second client.
    // The reservations include a prefix and address acquired by the
    // first client in the previous transaction.
    c = configString(*client_.getDuid(),
                     Reservation("2001:db8:1::1"),
                     Reservation("2001:db8:1::2"),
                     Reservation("3001:0:0:9::/64"),
                     Reservation("3001:0:0:10::/64"));

    ASSERT_NO_THROW(configure(c, *client_.getServer()));

    // Configure the second client to send two IA_NAs and two IA_PDs with
    // IAIDs from 1 to 4.
    client_.requestAddress(1);
    client_.requestAddress(2);
    client_.requestPrefix(3);
    client_.requestPrefix(4);

    // Perform 4-way exchange.
    ASSERT_NO_THROW(do_solicit_request_());

    // The client should have obtained 4 leases: two prefixes and two addresses.
    ASSERT_EQ(4, client_.getLeaseNum());

    // The address "2001:db8:1::2" is reserved and available so the
    // server should have assigned it.
    ASSERT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1::2"),
                                           IAID(1)));
    // The address "2001:db8:1::1" was hijacked by another client so it
    // must not be assigned to this client.
    ASSERT_FALSE(client_.hasLeaseForAddress(IOAddress("2001:db8:1::1")));
    // This client should have got an address from the dynamic pool excluding
    // two addresses already assigned, i.e. excluding "2001:db8:1::1" and
    // "2001:db8:1::2".
    ASSERT_TRUE(client_.hasLeaseForAddressRange(IOAddress("2001:db8:1::3"),
                                                IOAddress("2001:db8:1::10")));

    // Same story with prefixes.
    ASSERT_TRUE(client_.hasLeaseForPrefix(IOAddress("3001:0:0:9::"), 64,
                                          IAID(3)));
    ASSERT_FALSE(client_.hasLeaseForPrefix(IOAddress("3001:0:0:10::"), 64));


    // Now that the reservations have been made, the first client should get
    // non-reserved leases upon renewal. The server detects that the leases
    // are reserved for someone else.
    ASSERT_NO_THROW(client.doRenew());

    // For those leases, the first client should get 0 lifetimes.
    ASSERT_TRUE(client.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1::1")));
    ASSERT_TRUE(client.hasLeaseWithZeroLifetimeForPrefix(IOAddress("3001:0:0:10::"), 64));

    // The total number of leases should be 4 - two leases with zero lifetimes
    // and two leases with address and prefix from the dynamic pools, which
    // replace previously assigned leases. We don't care too much what those
    // leases are, though.
    EXPECT_EQ(4, client.getLeaseNum());

    // The second client renews and the server should be now able to assign
    // all reserved leases to this client.
    ASSERT_NO_THROW(client_.doRenew());

    // Client requests 4 leases, but there are additional two with zero
    // lifetimes to indicate that the client should not use the address
    // and prefix from the dynamic pools anymore.
    ASSERT_EQ(6, client_.getLeaseNum());

    // Check that the client has all reserved leases.
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1::2"),
                                           IAID(1)));
    EXPECT_TRUE(client_.hasLeaseForAddress(IOAddress("2001:db8:1::1"),
                                           IAID(2)));

    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3001:0:0:9::"), 64,
                                          IAID(3)));
    EXPECT_TRUE(client_.hasLeaseForPrefix(IOAddress("3001:0:0:10::"), 64,
                                          IAID(4)));
}

// This test verifies a scenario in which a client trying to renew a
// lease is refused this lease because it has been reserved to another
// client. The client is assigned another available lease from a
// dynamic pool by reusing an expired lease.
TEST_F(HostTest, conflictResolutionReuseExpired) {
    Dhcp6Client client1;

    ASSERT_NO_THROW(configure(CONFIGS[6], *client1.getServer()));

    // First client performs 4-way exchange and obtains an address and
    // prefix indicated in hints.
    requestIA(client1, Hint(IAID(1), "2001:db8:1::1"));
    requestIA(client1, Hint(IAID(2), "3000::/120"));

    ASSERT_NO_THROW(client1.doSARR());

    // Make sure the client has obtained requested leases.
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::1"), IAID(1)));
    ASSERT_TRUE(client1.hasLeaseForPrefix(IOAddress("3000::"), 120));

    // Create another client which is assigned another lease.
    Dhcp6Client client2(client1.getServer());

    // Second client performs 4-way exchange and obtains an address and
    // prefix indicated in hints.
    requestIA(client2, Hint(IAID(1), "2001:db8:1::2"));
    requestIA(client2, Hint(IAID(2), "3000::100/120"));

    ASSERT_NO_THROW(client2.doSARR());

    // Make sure the client has obtained requested leases.
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::2"), IAID(1)));
    ASSERT_TRUE(client2.hasLeaseForPrefix(IOAddress("3000::100"), 120));

    // Fast forward time to simulate aging of leases. After that, both leases are
    // expired because their valid lifetime is 40s. The second argument indicates
    // that the leases should also be updated on the server.
    client1.fastFwdTime(60, true);
    client2.fastFwdTime(60, true);

    // Reconfigure the server, so as the address 2001:db8:1::2 and prefix
    // 3000::10/120 is now reserved for another client.
    ASSERT_NO_THROW(configure(CONFIGS[7], *client1.getServer()));

    client1.clearRequestedIAs();
    client2.clearRequestedIAs();

    // Try to renew the address of 2001:db8:1::2 and prefix 3000::100/120.
    ASSERT_NO_THROW(client2.doRenew());

    // The renewed address and prefix are now reserved for another client so
    // available leases  should be allocated instead.
    EXPECT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::1")));
    EXPECT_TRUE(client2.hasLeaseForPrefix(IOAddress("3000::"), 120));
    // The previously allocated leases should now be returned with zero lifetimes.
    EXPECT_TRUE(client2.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1::2")));
    EXPECT_TRUE(client2.hasLeaseWithZeroLifetimeForPrefix(IOAddress("3000::100"), 120));

    // We've had a bug in DHCPv6 server that reused lease (allocated previously to
    // a different client) was returned to the client reusing leases. This a big issue
    // because effectively a client reusing an expired lease would get this lease twice:
    // with non-zero lifetimes and the second time with zero lifetimes. This is seriously
    // confusing for the clients. This checks tha the bug has been eliminated.
    EXPECT_FALSE(client2.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(client2.hasLeaseWithZeroLifetimeForPrefix(IOAddress("3000::"), 120));
}

// Verifies fundamental Global vs Subnet host reservations for NA leases
TEST_F(HostTest, globalReservationsNA) {
    Dhcp6Client client;
    ASSERT_NO_FATAL_FAILURE(configure(CONFIGS[8], *client.getServer()));

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    {
        SCOPED_TRACE("Global HR by DUID with in-range reserved address");
        client.setDUID("02:02:03:04");
        client.requestAddress(1234, IOAddress("::"));
        // Should get global reserved address and reserved host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:1::77", "duid-host-fixed-in-range"));
    }

    {
        SCOPED_TRACE("Global HR by DUID with an out-of-range reserved address");
        client.setDUID("01:02:03:04");
        client.requestAddress(1234, IOAddress("::"));
        // Should get global reserved address and reserved host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:1::1", "duid-host-fixed-out-of-range"));
    }

    {
        SCOPED_TRACE("Global HR by DUID with dynamic address");
        client.clearConfig();
        client.setDUID("01:02:03:05");
        client.requestAddress(1234, IOAddress("::"));
        // Should get dynamic address and reserved host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:1::", "duid-host-dynamic"));
    }

    {
        SCOPED_TRACE("Global HR by HW Address with dynamic address");
        client.clearConfig();
        client.setDUID("33:44:55:66");
        client.setLinkLocal(IOAddress("fe80::3a60:77ff:fed5:ffee"));
        client.requestAddress(1234, IOAddress("::"));
        // Should get dynamic address and hardware host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:1::2", "hw-host"));
    }

    {
        SCOPED_TRACE("Default subnet reservations flags excludes global reservations");
        client.clearConfig();
        client.setInterface("eth1");
        client.setDUID("01:02:03:04");
        client.requestAddress(1234, IOAddress("::"));
        // Should get dynamic address and no host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:2::", ""));
    }

    {
        SCOPED_TRACE("Subnet reservation over global");
        client.clearConfig();
        client.setInterface("eth1");
        client.setDUID("01:02:03:05");
        client.requestAddress(1234, IOAddress("::"));
        // Should get dynamic address and host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:2::1", "subnet-duid-host"));
    }

    {
        SCOPED_TRACE("Subnet reservation preferred over global");
        // Patch the second subnet to both global and in-subnet.
        Subnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getSubnet(2);
        ASSERT_TRUE(subnet);
        subnet->setReservationsGlobal(true);
        subnet->setReservationsInSubnet(true);
        client.clearConfig();
        client.setInterface("eth1");
        client.setDUID("01:02:03:05");
        client.requestAddress(1234, IOAddress("::"));
        // Should get dynamic address and host name because it has preference
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "2001:db8:2::1", "subnet-duid-host"));
    }
}

// Verifies fundamental Global vs Subnet host reservations for PD leases
TEST_F(HostTest, globalReservationsPD) {
    Dhcp6Client client;
    ASSERT_NO_FATAL_FAILURE(configure(CONFIGS[9], *client.getServer()));

    const Subnet6Collection* subnets = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getAll();
    ASSERT_EQ(2, subnets->size());

    {
        SCOPED_TRACE("Global HR by DUID with reserved prefix");
        client.setDUID("01:02:03:04");
        client.requestPrefix(1);
        // Should get global reserved prefix and reserved host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "4000::100", "duid-host-fixed"));
    }

    {
        SCOPED_TRACE("Global HR by DUID with dynamic prefix");
        client.clearConfig();
        client.setDUID("01:02:03:05");
        client.requestPrefix(1);
        // Should get dynamic prefix and reserved host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "3000::", "duid-host-dynamic"));
    }

    {
        SCOPED_TRACE("Default subnet reservations flags excludes global reservations");
        client.clearConfig();
        client.setInterface("eth1");
        client.setDUID("01:02:03:04");
        client.requestPrefix(1);
        // Should get dynamic prefix and no host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "3001::", ""));
    }

    {
        SCOPED_TRACE("Subnet reservation over global");
        client.clearConfig();
        client.setInterface("eth1");
        client.setDUID("01:02:03:05");
        client.requestPrefix(1);
        // Should get dynamic prefix and subnet reserved host name
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "3001::100", "subnet-duid-host"));
    }

    {
        SCOPED_TRACE("Subnet reservation preferred over global");
        // Patch the second subnet to both global and in-subnet.
        Subnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getSubnet(2);
        ASSERT_TRUE(subnet);
        subnet->setReservationsGlobal(true);
        subnet->setReservationsInSubnet(true);
        client.clearConfig();
        client.setInterface("eth1");
        client.setDUID("01:02:03:05");
        client.requestPrefix(1);
        // Should get dynamic prefix and subnet reserved host name
        // because it has preference over the global reservation.
        ASSERT_NO_FATAL_FAILURE(sarrTest(client, "3001::100", "subnet-duid-host"));
    }
}

// Verifies that client class specified in the global reservation
// may be used to influence pool selection.
TEST_F(HostTest, clientClassGlobalPoolSelection) {
    ASSERT_NO_FATAL_FAILURE(testGlobalClassSubnetPoolSelection(10));
}

// Verifies that client class specified in the global reservation
// may be used to influence subnet selection within shared network.
TEST_F(HostTest, clientClassGlobalSubnetSelection) {
    ASSERT_NO_FATAL_FAILURE(testGlobalClassSubnetPoolSelection(11));
}

// Verifies that client class specified in the reservation may be
// used to influence pool selection within a subnet.
TEST_F(HostTest, clientClassPoolSelection) {
    ASSERT_NO_FATAL_FAILURE(testGlobalClassSubnetPoolSelection(12, "2001:db8:1::10",
                                                               "2001:db8:1::20"));
}

// Verifies that if the server is configured to allow for specifying
// multiple reservations for the same IP address the first client
// matching the reservation will be given this address. The second
// client will be given a different lease.
TEST_F(HostTest, firstClientGetsReservedAddress) {
    // Create a client which has DUID matching the reservation.
    Dhcp6Client client1;
    client1.setDUID("01:02:03:04");
    ASSERT_NO_THROW(configure(CONFIGS[13], *client1.getServer()));
    // client1 performs 4-way exchange to get the reserved lease.
    requestIA(client1, Hint(IAID(1), "2001:db8:1::10"));
    ASSERT_NO_THROW(client1.doSARR());

    // Make sure the client has obtained reserved lease.
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));

    // Create another client that has a reservation for the same
    // IP address.
    Dhcp6Client client2(client1.getServer());
    client2.setDUID("01:02:03:05");
    requestIA(client2, Hint(IAID(1), "2001:db8:1::10"));

    // client2 performs 4-way exchange.
    ASSERT_NO_THROW(client2.doSARR());

    // Make sure the client didn't get the reserved lease. This lease has been
    // already taken by the client1.
    EXPECT_FALSE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));

    // Make sure the client2 got a lease from the configured pool.
    auto leases = client2.getLeasesByAddressRange(IOAddress("2001:db8:1::10"),
                                                  IOAddress("2001:db8:1::200"));
    EXPECT_EQ(1, leases.size());

    // Verify that the client1 can renew the lease.
    ASSERT_NO_THROW(client1.doRenew());
    EXPECT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));

    // The client2 should also renew the lease.
    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_FALSE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));
    leases = client2.getLeasesByAddressRange(IOAddress("2001:db8:1::10"),
                                             IOAddress("2001:db8:1::200"));
    EXPECT_EQ(1, leases.size());

    // If the client1 releases the reserved lease, the client2 should acquire it.
    ASSERT_NO_THROW(client1.doRelease());
    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::15"), IAID(1)));
}

// Verifies that if the server is configured to allow for specifying
// multiple reservations for the same delegated prefix the first client
// matching the reservation will be given this prefix. The second
// client will be given a different lease.
TEST_F(HostTest, firstClientGetsReservedPrefix) {
    // Create a client which has DUID matching the reservation.
    Dhcp6Client client1;
    client1.setDUID("01:02:03:04");
    ASSERT_NO_THROW(configure(CONFIGS[14], *client1.getServer()));
    // client1 performs 4-way exchange to get the reserved lease.
    client1.requestPrefix(1);
    ASSERT_NO_THROW(client1.doSARR());

    // Make sure the client has obtained reserved lease.
    ASSERT_TRUE(client1.hasLeaseForPrefix(IOAddress("3000::5a:0"), 112, IAID(1)));

    // Create another client that has a reservation for the same
    // IP address.
    Dhcp6Client client2(client1.getServer());
    client2.setDUID("01:02:03:05");
    client2.requestPrefix(1);

    // client2 performs 4-way exchange.
    ASSERT_NO_THROW(client2.doSARR());

    // Make sure the client didn't get the reserved lease. This lease has been
    // already taken by the client1.
    EXPECT_FALSE(client2.hasLeaseForPrefix(IOAddress("3000::5a:0"), 112, IAID(1)));

    // Make sure the client2 got a lease from the configured pool.
    EXPECT_TRUE(client2.hasLeaseForPrefixPool(IOAddress("3000::"), 64, 112));

    // Verify that the client1 can renew the lease.
    ASSERT_NO_THROW(client1.doRenew());
    EXPECT_TRUE(client1.hasLeaseForPrefix(IOAddress("3000::5a:0"), 112, IAID(1)));

    // The client2 should also renew the lease.
    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_TRUE(client2.hasLeaseForPrefixPool(IOAddress("3000::"), 64, 112));

    // If the client1 releases the reserved lease, the client2 should acquire it.
    ASSERT_NO_THROW(client1.doRelease());
    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_TRUE(client2.hasLeaseForPrefix(IOAddress("3000::5a:0"), 112, IAID(1)));
}

/// This test verifies the case when two clients have reservations for
/// the same IP address. The first client sends Solicit and is offered
/// the reserved address. At the same time, the second client having
/// the reservation for the same IP address performs 4-way exchange
/// using the reserved address as a hint in Solicit.
/// The client gets the lease for this address. This test verifies
/// that the allocation engine correctly identifies that the second
/// client has a reservation for this address.
TEST_F(HostTest, multipleClientsRace1) {
    ASSERT_NO_FATAL_FAILURE(testMultipleClientsRace("01:02:03:04", "01:02:03:05"));
}

// This is a second variant of the multipleClientsRace1. The test is almost
// the same but the client matching the second reservation sends Solicit
// first and then the client having the first reservation performs 4-way
// exchange. This is to ensure that the order in which reservations are
// defined does not matter.
TEST_F(HostTest, multipleClientsRace2) {
    ASSERT_NO_FATAL_FAILURE(testMultipleClientsRace("01:02:03:05", "01:02:03:04"));
}

} // end of anonymous namespace
