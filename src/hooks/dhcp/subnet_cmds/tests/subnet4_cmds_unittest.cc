// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/lease_mgr_factory.h>
#include <stats/stats_mgr.h>
#include <tests/subnet_cmds_unittest.h>
#include <testutils/test_to_element.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::test;

#define FIRST_SUBNET "192.0.2.0/24"
#define FIRST_SUBNET_POOL_1 "192.0.2.1-192.0.2.10"
#define FIRST_SUBNET_POOL_2 "192.0.2.11-192.0.2.20"
#define FIRST_SUBNET_POOL_3 "192.0.2.21-192.0.2.30"
#define FIRST_SUBNET_RELAY_ADDRESS_1 "192.168.0.1"
#define FIRST_SUBNET_RELAY_ADDRESS_2 "192.168.0.2"
#define FIRST_SUBNET_RELAY_ADDRESS_3 "192.168.0.3"
#define FIRST_SUBNET_4O6_INTERFACE "eth0"
#define FIRST_SUBNET_4O6_INTERFACE_CHANGED "eth2"
#define FIRST_SUBNET_4O6_INTERFACE_ID "5"
#define FIRST_SUBNET_4O6_SUBNET "198.0.2.0/24"
#define FIRST_OPTION_NAME "routers"
#define FIRST_OPTION_CODE "3"
#define FIRST_SUBNET_FIRST_OPTION_DATA_1 "192.0.3.1"
#define FIRST_SUBNET_FIRST_OPTION_DATA_2 "192.0.4.1"
#define FIRST_SUBNET_FIRST_OPTION_DATA_3 "192.0.9.1"
#define FIRST_SUBNET_FIRST_POOL_OPTION_DATA_1 "192.0.5.1"
#define FIRST_SUBNET_FIRST_POOL_OPTION_DATA_2 "192.0.6.1"
#define FIRST_SUBNET_FIRST_POOL_OPTION_DATA_3 "192.0.7.1"
#define FIRST_SUBNET_FIRST_POOL_OPTION_DATA_4 "192.0.8.1"
#define FIRST_SUBNET_FIRST_POOL_OPTION_DATA_5 "192.0.1.1"
#define FIRST_SUBNET_SECOND_OPTION_DATA_1 "192.2.3.1"
#define FIRST_SUBNET_SECOND_POOL_OPTION_DATA_1 "192.1.3.1"
#define FIRST_SUBNET_POOL_CLIENT_CLASS_1 "phones_server1"
#define FIRST_SUBNET_POOL_CLIENT_CLASS_2 "phones_server2"
#define FIRST_SUBNET_POOL_CLIENT_CLASS_3 "phones_server3"
#define FIRST_SUBNET_POOL_CLIENT_CLASS_4 "phones_server4"
#define FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "late"
#define FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "too-late"
#define FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "extremely-late"
#define FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "almost-late"

#define SECOND_SUBNET "10.0.0.0/8"
#define SECOND_SUBNET_POOL_1 "10.0.0.1-10.0.0.10"
#define SECOND_SUBNET_POOL_2 "10.0.0.11-10.0.0.20"
#define SECOND_SUBNET_POOL_3 "10.0.0.21-10.0.0.30"
#define SECOND_SUBNET_RELAY_ADDRESS_1 "196.168.0.1"
#define SECOND_SUBNET_RELAY_ADDRESS_2 "196.168.0.2"
#define SECOND_SUBNET_RELAY_ADDRESS_3 "196.168.0.3"
#define SECOND_SUBNET_4O6_INTERFACE "eth1"
#define SECOND_SUBNET_4O6_INTERFACE_CHANGED "eth3"
#define SECOND_SUBNET_4O6_INTERFACE_ID "10"
#define SECOND_SUBNET_4O6_INTERFACE_ID_CHANGED "15"
#define SECOND_SUBNET_4O6_SUBNET "200.0.2.0/24"
#define SECOND_SUBNET_4O6_SUBNET_CHANGED "250.0.2.0/24"
#define SECOND_OPTION_NAME "time-servers"
#define SECOND_OPTION_CODE "4"
#define SECOND_SUBNET_FIRST_OPTION_DATA_1 "196.0.3.1"
#define SECOND_SUBNET_FIRST_OPTION_DATA_2 "196.0.4.1"
#define SECOND_SUBNET_FIRST_POOL_OPTION_DATA_1 "196.0.5.1"
#define SECOND_SUBNET_FIRST_POOL_OPTION_DATA_2 "196.0.6.1"
#define SECOND_SUBNET_FIRST_POOL_OPTION_DATA_3 "196.0.7.1"
#define SECOND_SUBNET_SECOND_OPTION_DATA_1 "192.1.4.1"
#define SECOND_SUBNET_SECOND_OPTION_DATA_2 "192.1.5.1"
#define SECOND_SUBNET_SECOND_POOL_OPTION_DATA_1 "192.1.8.1"
#define SECOND_SUBNET_SECOND_POOL_OPTION_DATA_2 "192.1.6.1"
#define SECOND_SUBNET_SECOND_POOL_OPTION_DATA_3 "192.1.7.1"
#define SECOND_SUBNET_POOL_CLIENT_CLASS_1 "phones_server13"
#define SECOND_SUBNET_POOL_CLIENT_CLASS_2 "phones_server14"
#define SECOND_SUBNET_POOL_CLIENT_CLASS_3 "phones_server15"
#define SECOND_SUBNET_POOL_CLIENT_CLASS_4 "phones_server16"
#define SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "early"
#define SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "too-early"
#define SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "extremely-early"
#define SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "almost-early"

namespace {

/// @brief Sequential steps used to test scenario using multiple
/// subnet4-delta-add and subnet4-delta-del commands.
///
/// They are currently used by subnet4DeltaAddAndDelMultiple only.
/// The steps that change the configuration also depend on the check for the
/// other subnet to make sure that it only changed the desired subnet.
/// Because steps can depend on one another, the ones retrieving the
/// configuration must not depend on any other step because that could cause an
/// infinite dependency loop and the test would never complete.
/// Usually the test scenario consists of retrieving the configuration for a
/// subnet, calling either subnet4-delta-add or subnet4-delta-del and checking
/// the result by retrieving the configuration again, also checking that the
/// command only had an effect on the desired subnet.
Scenario test_steps[] = {
    // Scenario 0
    // get the initial data for " FIRST_SUBNET " subnet
    {
        "get initial " FIRST_SUBNET " subnet",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" FIRST_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"4o6-interface-id\": \"\", "
                        "\"4o6-subnet\": \"\", "
                        "\"id\": 101, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [  ], "
                        "\"pools\": [  ], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [  ] }, "
                        "\"renew-timer\": 30, "
                        "\"subnet\": \"" FIRST_SUBNET "\", "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned",
        { }
    },
    // Scenario 1
    // get the initial data for " SECOND_SUBNET " subnet
    {
        "get initial " SECOND_SUBNET " subnet",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" SECOND_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"4o6-interface-id\": \"\", "
                        "\"4o6-subnet\": \"\", "
                        "\"id\": 5, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [  ], "
                        "\"pools\": [  ], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [  ] }, "
                        "\"renew-timer\": 30, "
                        "\"subnet\": \"" SECOND_SUBNET "\", "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned",
        { }
    },
    // Scenario 2
    // update " FIRST_SUBNET " with scalars, options, pools and relay address
    // - add 3 scalars at subnet level
    // - add 2 options at subnet level (duplicates are supported for the same option)
    // - add 2 pools with options and required classes
    // - add 1 relay ip address
    {
        "update " FIRST_SUBNET " with scalars, options, pools and relay address",
        "{ \"command\": \"subnet4-delta-add\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" FIRST_SUBNET_4O6_INTERFACE "\", "
                        "\"4o6-interface-id\": \"" FIRST_SUBNET_4O6_INTERFACE_ID "\", "
                        "\"4o6-subnet\": \"" FIRST_SUBNET_4O6_SUBNET "\", "
                        "\"allocator\": \"iterative\", "
                        "\"id\": 101, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_1 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_2 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_1 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_2 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_4 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_1 "\" ] }, "
                        "\"subnet\": \"" FIRST_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 101, "
                            "\"subnet\": \"" FIRST_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 1 }
    },
    // Scenario 3
    // get the modified data for " FIRST_SUBNET " subnet after first update
    {
        "get modified " FIRST_SUBNET " subnet after first update",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" FIRST_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" FIRST_SUBNET_4O6_INTERFACE "\", "
                        "\"4o6-interface-id\": \"" FIRST_SUBNET_4O6_INTERFACE_ID "\", "
                        "\"4o6-subnet\": \"" FIRST_SUBNET_4O6_SUBNET "\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 101, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_1 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_2 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_1 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_2 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_4 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_1 "\" ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" FIRST_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned",
        { }
    },
    // Scenario 4
    // update " SECOND_SUBNET " with scalars, options, pools and relay address
    // - add 3 scalars at subnet level
    // - add 1 option at subnet level
    // - add 1 pool with option and required classes
    // - add 2 relay ip addresses
    {
        "update " SECOND_SUBNET " with scalars, options, pools and relay address",
        "{ \"command\": \"subnet4-delta-add\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" SECOND_SUBNET_4O6_INTERFACE "\", "
                        "\"4o6-interface-id\": \"" SECOND_SUBNET_4O6_INTERFACE_ID "\", "
                        "\"4o6-subnet\": \"" SECOND_SUBNET_4O6_SUBNET "\", "
                        "\"allocator\": \"iterative\", "
                        "\"id\": 5, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_FIRST_OPTION_DATA_1 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_1 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_1 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" SECOND_SUBNET_RELAY_ADDRESS_1 "\", \"" SECOND_SUBNET_RELAY_ADDRESS_2 "\" ] }, "
                        "\"subnet\": \"" SECOND_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 5, "
                            "\"subnet\": \"" SECOND_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 3 }
    },
    // Scenario 5
    // get the modified data for " SECOND_SUBNET " subnet after first update
    {
        "get modified " SECOND_SUBNET " subnet after first update",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" SECOND_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" SECOND_SUBNET_4O6_INTERFACE "\", "
                        "\"4o6-interface-id\": \"" SECOND_SUBNET_4O6_INTERFACE_ID "\", "
                        "\"4o6-subnet\": \"" SECOND_SUBNET_4O6_SUBNET "\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 5, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_FIRST_OPTION_DATA_1 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_1 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_1 "\" "
                            "} "
                        "], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [ \"" SECOND_SUBNET_RELAY_ADDRESS_1 "\", \"" SECOND_SUBNET_RELAY_ADDRESS_2 "\" ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" SECOND_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned",
        { }
    },
    // Scenario 6
    // update " FIRST_SUBNET " with scalars, options, pools and relay address
    // - change 1 scalar at subnet level
    // - add 1 option at subnet level
    // - change 1 option at subnet level (duplicates are all updated)
    // - add 1 pools with options and required classes
    // - change 1 pool with options and required classes
    // - add 2 relay ip addresses
    {
        "update again " FIRST_SUBNET " with scalars, options, pools and relay address",
        "{ \"command\": \"subnet4-delta-add\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" FIRST_SUBNET_4O6_INTERFACE_CHANGED "\", "
                        "\"id\": 101, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_3 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_SECOND_OPTION_DATA_1 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_3 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_5 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_3 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_4 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_SECOND_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_2 "\", \"" FIRST_SUBNET_RELAY_ADDRESS_3 "\" ] }, "
                        "\"subnet\": \"" FIRST_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 101, "
                            "\"subnet\": \"" FIRST_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 5 }
    },
    // Scenario 7
    // get the modified data for " FIRST_SUBNET " subnet after second update
    {
        "get modified " FIRST_SUBNET " subnet after second update",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" FIRST_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" FIRST_SUBNET_4O6_INTERFACE_CHANGED "\", "
                        "\"4o6-interface-id\": \"" FIRST_SUBNET_4O6_INTERFACE_ID "\", "
                        "\"4o6-subnet\": \"" FIRST_SUBNET_4O6_SUBNET "\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 101, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_3 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_FIRST_OPTION_DATA_3 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" FIRST_SUBNET_SECOND_OPTION_DATA_1 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_1 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_2 "\", \"" FIRST_SUBNET_POOL_CLIENT_CLASS_4 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_SECOND_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_3 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_FIRST_POOL_OPTION_DATA_5 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_3 "\" "
                            "} "
                        "], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_1 "\", \"" FIRST_SUBNET_RELAY_ADDRESS_2 "\", \"" FIRST_SUBNET_RELAY_ADDRESS_3 "\" ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" FIRST_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned",
        { }
    },
    // Scenario 8
    // update " SECOND_SUBNET " with scalars, options, pools and relay address
    // - update 3 scalars at subnet level
    // - add 2 option at subnet level (can add duplicates)
    // - change 1 option at subnet level
    // - add 2 pool with option and required classes
    // - add 2 relay ip addresses
    {
        "update again " SECOND_SUBNET " with scalars, options, pools and relay address",
        "{ \"command\": \"subnet4-delta-add\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" SECOND_SUBNET_4O6_INTERFACE_CHANGED "\", "
                        "\"4o6-interface-id\": \"" SECOND_SUBNET_4O6_INTERFACE_ID_CHANGED "\", "
                        "\"4o6-subnet\": \"" SECOND_SUBNET_4O6_SUBNET_CHANGED "\", "
                        "\"allocator\": \"iterative\", "
                        "\"id\": 5, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_FIRST_OPTION_DATA_2 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_SECOND_OPTION_DATA_1 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_SECOND_OPTION_DATA_2 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_4 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "

                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_2 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_2 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_3 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_3 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" SECOND_SUBNET_RELAY_ADDRESS_3 "\" ] }, "
                        "\"subnet\": \"" SECOND_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 5, "
                            "\"subnet\": \"" SECOND_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 7 }
    },
    // Scenario 9
    // get the modified data for " SECOND_SUBNET " subnet after second update
    {
        "get modified " SECOND_SUBNET " subnet after second update",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" SECOND_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" SECOND_SUBNET_4O6_INTERFACE_CHANGED "\", "
                        "\"4o6-interface-id\": \"" SECOND_SUBNET_4O6_INTERFACE_ID_CHANGED "\", "
                        "\"4o6-subnet\": \"" SECOND_SUBNET_4O6_SUBNET_CHANGED "\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 5, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_FIRST_OPTION_DATA_2 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_SECOND_OPTION_DATA_1 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_SECOND_OPTION_DATA_2 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_1 "\", \"" SECOND_SUBNET_POOL_CLIENT_CLASS_4 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_2 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_2 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_3 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_3 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_3 "\" "
                            "} "
                        "], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [ \"" SECOND_SUBNET_RELAY_ADDRESS_1 "\", \"" SECOND_SUBNET_RELAY_ADDRESS_2 "\", \"" SECOND_SUBNET_RELAY_ADDRESS_3 "\" ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" SECOND_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned",
        { }
    },
    // Scenario 10
    // delete data from " FIRST_SUBNET " subnet
    // - delete 3 scalars at subnet level
    // - delete 3 option at subnet level using code only (can use duplicates)
    // - delete options, scalars and required classes in pools
    // - delete entire pool using key only
    // - delete 2 relay addresses
    {
        "delete data from " FIRST_SUBNET " subnet",
        "{ \"command\": \"subnet4-delta-del\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"" FIRST_SUBNET_4O6_INTERFACE_CHANGED "\", "
                        "\"4o6-interface-id\": \"" FIRST_SUBNET_4O6_INTERFACE_ID "\", "
                        "\"4o6-subnet\": \"" FIRST_SUBNET_4O6_SUBNET "\", "
                        "\"allocator\": \"iterative\", "
                        "\"id\": 101, "
                        "\"option-data\": [ "
                            "{ "
                                "\"code\": " FIRST_OPTION_CODE " "
                            "}, "
                            "{ "
                                "\"code\": " FIRST_OPTION_CODE " "
                            "}, "
                            "{ "
                                "\"code\": " SECOND_OPTION_CODE " "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_1 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_1 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"code\": " FIRST_OPTION_CODE " "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\", \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "}, "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" FIRST_SUBNET_SECOND_POOL_OPTION_DATA_1 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false "
                                    "} "
                                "], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "}, "
                            "{ "
                                "\"pool\": \"" FIRST_SUBNET_POOL_3 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_1 "\", \"" FIRST_SUBNET_RELAY_ADDRESS_3 "\" ] }, "
                        "\"subnet\": \"" FIRST_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 101, "
                            "\"subnet\": \"" FIRST_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 9 }
    },
    // Scenario 11
    // get the modified data for " FIRST_SUBNET " subnet after first delete
    {
        "get modified " FIRST_SUBNET " subnet after first delete",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" FIRST_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"4o6-interface-id\": \"\", "
                        "\"4o6-subnet\": \"\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 101, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [  ], "
                        "\"pools\": [ "
                            "{ "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"option-data\": [  ], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_2 "\", \"" FIRST_SUBNET_POOL_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [  ], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_2 "\" ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" FIRST_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned",
        { }
    },
    // Scenario 12
    // delete data from " SECOND_SUBNET " subnet
    // - delete 1 scalar at subnet level (does not need to match configured value)
    // - delete 1 option at subnet level using entire data (can use duplicates)
    // - delete option, scalars and required classes in pool
    // - delete 2 entire pools using key only
    // - delete 3 relay addresses
    {
        "delete data from " SECOND_SUBNET " subnet",
        "{ \"command\": \"subnet4-delta-del\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"id\": 5, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_SECOND_OPTION_DATA_1 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "}, "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " SECOND_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_SECOND_OPTION_DATA_2 "\", "
                                "\"name\": \"" SECOND_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"pool\": \"" SECOND_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" SECOND_SUBNET_POOL_CLIENT_CLASS_2 "\" ], "
                                "\"evaluate-additional-classes\": [ \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_3 "\", \"" SECOND_SUBNET_POOL_REQUIRE_CLIENT_CLASS_4 "\" ], "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": false, "
                                        "\"code\": " SECOND_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_SECOND_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" SECOND_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_2 "\" "
                            "}, "
                            "{ "
                                "\"pool\": \"" SECOND_SUBNET_POOL_3 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" SECOND_SUBNET_RELAY_ADDRESS_1 "\", \"" SECOND_SUBNET_RELAY_ADDRESS_2 "\", \"" SECOND_SUBNET_RELAY_ADDRESS_3 "\" ] }, "
                        "\"subnet\": \"" SECOND_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 5, "
                            "\"subnet\": \"" SECOND_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 11 }
    },
    // Scenario 13
    // get the modified data for " SECOND_SUBNET " subnet after first delete
    {
        "get modified " SECOND_SUBNET " subnet after first delete",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" SECOND_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"4o6-interface-id\": \"" SECOND_SUBNET_4O6_INTERFACE_ID_CHANGED "\", "
                        "\"4o6-subnet\": \"" SECOND_SUBNET_4O6_SUBNET_CHANGED "\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 5, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [ "
                            "{ "
                                "\"always-send\": false, "
                                "\"code\": " FIRST_OPTION_CODE ", "
                                "\"csv-format\": true, "
                                "\"data\": \"" SECOND_SUBNET_FIRST_OPTION_DATA_2 "\", "
                                "\"name\": \"" FIRST_OPTION_NAME "\", "
                                "\"never-send\": false, "
                                "\"space\": \"dhcp4\" "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": true, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [  ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" SECOND_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned",
        { }
    },
    // Scenario 14
    // delete data from " FIRST_SUBNET " subnet
    // - delete scalar and required classes in pool
    // - delete 1 relay address
    {
        "delete again data from " FIRST_SUBNET " subnet",
        "{ \"command\": \"subnet4-delta-del\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"id\": 101, "
                        "\"pools\": [ "
                            "{ "
                                "\"evaluate-additional-classes\": [ \"" FIRST_SUBNET_POOL_REQUIRE_CLIENT_CLASS_2 "\" ], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_1 "\" "
                            "}, "
                            "{ "
                                "\"client-classes\": [ \"" FIRST_SUBNET_POOL_CLIENT_CLASS_2 "\", \"" FIRST_SUBNET_POOL_CLIENT_CLASS_4 "\" ], "
                                "\"pool\": \"" FIRST_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"relay\": { \"ip-addresses\": [ \"" FIRST_SUBNET_RELAY_ADDRESS_2 "\" ] }, "
                        "\"subnet\": \"" FIRST_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 101, "
                            "\"subnet\": \"" FIRST_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 13 }
    },
    // Scenario 15
    // get the modified data for " FIRST_SUBNET " subnet after second delete
    {
        "get modified " FIRST_SUBNET " subnet after second delete",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" FIRST_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"4o6-interface-id\": \"\", "
                        "\"4o6-subnet\": \"\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 101, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [  ], "
                        "\"pools\": [  ], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [  ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" FIRST_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " FIRST_SUBNET " (id 101) returned",
        { }
    },
    // Scenario 16
    // delete data from " SECOND_SUBNET " subnet
    // - delete 2 scalars at subnet level
    // - delete 1 option at subnet level using key only
    // - delete option, scalars and required classes in pool
    // - delete 2 entire pools using key only
    // - delete 3 relay addresses
    {
        "delete again data from " SECOND_SUBNET " subnet",
        "{ \"command\": \"subnet4-delta-del\", \n"
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface-id\": \"" SECOND_SUBNET_4O6_INTERFACE_ID_CHANGED "\", "
                        "\"4o6-subnet\": \"" SECOND_SUBNET_4O6_SUBNET_CHANGED "\", "
                        "\"allocator\": \"iterative\", "
                        "\"id\": 5, "
                        "\"option-data\": [ "
                            "{ "
                                "\"code\": " FIRST_OPTION_CODE " "
                            "} "
                        "], "
                        "\"pools\": [ "
                            "{ "
                                "\"option-data\": [ "
                                    "{ "
                                        "\"always-send\": true, "
                                        "\"code\": " FIRST_OPTION_CODE ", "
                                        "\"csv-format\": true, "
                                        "\"data\": \"" SECOND_SUBNET_FIRST_POOL_OPTION_DATA_2 "\", "
                                        "\"name\": \"" FIRST_OPTION_NAME "\", "
                                        "\"never-send\": false, "
                                        "\"space\": \"dhcp4\" "
                                    "} "
                                "], "
                                "\"pool\": \"" SECOND_SUBNET_POOL_2 "\" "
                            "} "
                        "], "
                        "\"subnet\": \"" SECOND_SUBNET "\" "
                    "} "
                "] "
            "} "
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnets\": "
                    "[ "
                        "{ "
                            "\"id\": 5, "
                            "\"subnet\": \"" SECOND_SUBNET "\" "
                        "} "
                    "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"IPv4 subnet updated\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "IPv4 subnet updated",
        { 15 }
    },
    // Scenario 13
    // get the modified data for " SECOND_SUBNET " subnet after first delete
    {
        "get modified " SECOND_SUBNET " subnet after first delete",
        "{ \"command\": \"subnet4-get\", \n"
            "\"arguments\": { \"subnet\": \"" SECOND_SUBNET "\" }\n"
        "}\n",
        "{ "
            "\"arguments\": { "
                "\"subnet4\": [ "
                    "{ "
                        "\"4o6-interface\": \"\", "
                        "\"4o6-interface-id\": \"\", "
                        "\"4o6-subnet\": \"\", "
                        "\"allocator\": \"iterative\", "
                        "\"calculate-tee-times\": false, "
                        "\"id\": 5, "
                        "\"max-valid-lifetime\": 60, "
                        "\"min-valid-lifetime\": 60, "
                        "\"option-data\": [  ], "
                        "\"pools\": [  ], "
                        "\"rebind-timer\": 40, "
                        "\"relay\": { \"ip-addresses\": [  ] }, "
                        "\"renew-timer\": 30, "
                        "\"store-extended-info\": false, "
                        "\"subnet\": \"" SECOND_SUBNET "\", "
                        "\"t1-percent\": 0.5, "
                        "\"t2-percent\": 0.875, "
                        "\"valid-lifetime\": 60 "
                    "} "
                "] "
            "}, "
            "\"result\": 0, "
            "\"text\": \"Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned\" "
        "}",
        CONTROL_RESULT_SUCCESS,
        false,
        "Info about IPv4 subnet " SECOND_SUBNET " (id 5) returned",
        { }
    }
};

/// @brief Test fixture class for Subnet Commands hook library.
class Subnet4CmdsTest : public SubnetCmdsTest {
public:

    /// @brief Constructor.
    Subnet4CmdsTest() {
        setFamily(AF_INET);
    }

    /// @brief Add specified subnet to existing IPv4 network
    ///
    /// @param network_name name of the network (must exist already)
    /// @param subnet_str textual representation of the subnet (e.g. 192.0.2.0/24)
    /// @param subnet_id subnet ID to be used.
    /// @return created subnet (or NULL if addition failed for whatever reason)
    Subnet4Ptr addSubnetToNetwork4(const std::string& network_name, const std::string& subnet_str,
                                   const SubnetID& subnet_id) {

        CfgSharedNetworks4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
        SharedNetwork4Ptr network = cfg->getByName(network_name);
        CfgSubnets4Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();

        EXPECT_TRUE(network);
        if (!network) {
            return (Subnet4Ptr());
        }
        try {
            // Split prefix and prefix length.
            auto split_pos = subnet_str.find('/');
            if ((split_pos == std::string::npos) ||
                (split_pos == subnet_str.size() - 1)) {
                ADD_FAILURE() << "invalid subnet " << subnet_str;
                return (Subnet4Ptr());
            }

            IOAddress prefix(subnet_str.substr(0, split_pos));

            EXPECT_TRUE(prefix.isV4());

            // Convert prefix length to a number.
            unsigned prefix_length = boost::lexical_cast<unsigned>
                (subnet_str.substr(split_pos + 1));

            // Create Subnet4.
            Subnet4Ptr subnet(new Subnet4(prefix, prefix_length, 30, 40, 60, subnet_id));
            network->add(subnet);
            subnets->add(subnet);
            addReservations(subnet, CfgMgr::instance().getCurrentCfg()->getCfgHosts());
            subnets->updateStatistics();

            return (subnet);

        } catch (const std::exception& ex) {
            ADD_FAILURE() << "failed to add new IPv4 subnet " << subnet_str
                          << " to network " << network_name << ", reason: " << ex.what();
        }

        return (Subnet4Ptr());
    }

    /// @brief Tests negative scenarios for 'subnet4-get' command.
    ///
    /// @param arguments A string containing arguments.
    /// @param expected_text Test expected to be returned in the response.
    void testSubnet4GetNegative(const std::string& arguments,
                                const std::string& expected_text) {
        testCommandNegative("subnet4-get", arguments, expected_text);
    }

    /// @brief Tests negative scenarios for 'subnet4-add' command.
    ///
    /// @param arguments A string containing arguments.
    /// @param expected_text Test expected to be returned in the response.
    void testSubnet4AddNegative(const std::string& arguments,
                                const std::string& expected_text) {
        testCommandNegative("subnet4-add", arguments, expected_text);
    }

    /// @brief Tests negative scenarios for 'subnet4-update' command.
    ///
    /// @param arguments A string containing arguments.
    /// @param expected_text Test expected to be returned in the response.
    void testSubnet4UpdateNegative(const std::string& arguments,
                                const std::string& expected_text) {
        testCommandNegative("subnet4-update", arguments, expected_text);
    }

    /// @brief Tests negative scenarios for 'subnet4-del' command.
    ///
    /// @param arguments A string containing arguments.
    /// @param expected_text Test expected to be returned in the response.
    /// @param exp_result expected result (CONTROL_RESULT_ERROR if omitted)
    void testSubnet4DelNegative(const std::string& arguments,
                                const std::string& expected_text,
                                int exp_result = CONTROL_RESULT_ERROR) {
        testCommandNegative("subnet4-del", arguments, expected_text,
                            exp_result);
    }

    /// @brief Tests negative scenarios for 'subnet4-delta-add' command.
    ///
    /// @param arguments A string containing arguments.
    /// @param expected_text Test expected to be returned in the response.
    void testSubnet4DeltaAddNegative(const std::string& arguments,
                                     const std::string& expected_text) {
        testCommandNegative("subnet4-delta-add", arguments, expected_text);
    }

    /// @brief Tests negative scenarios for 'subnet4-delta-del' command.
    ///
    /// @param arguments A string containing arguments.
    /// @param expected_text Test expected to be returned in the response.
    void testSubnet4DeltaDelNegative(const std::string& arguments,
                                     const std::string& expected_text) {
        testCommandNegative("subnet4-delta-del", arguments, expected_text);
    }

    /// @brief Tests network4-del command
    ///
    /// @param network string name for the network to be created and deleted
    /// @param command text representation of the command to be tested
    /// @param expected_text expected text to be returned
    /// @param subnets_expected should the subnets be there afterwards?
    /// @param exp_result expected status of the command (CONTROL_RESULT_SUCCESS if omitted)
    void testNetwork4Del(const std::string& network,
                         const std::string& command,
                         const std::string& expected_text,
                         bool subnets_expected,
                         int exp_result = CONTROL_RESULT_SUCCESS) {
        addEmptyNetwork(network, false); // v4 network
        addSubnetToNetwork4(network, "192.0.2.0/24", SubnetID(100));
        addSubnetToNetwork4(network, "192.0.3.0/24", SubnetID(101));
        addSubnetToNetwork4(network, "192.0.4.0/24", SubnetID(102));

        auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
        EXPECT_TRUE(cfg->getByName(network));

        // Command processing should be successful.
        ConstElementPtr response = testCommand(command, exp_result, expected_text);
        ASSERT_TRUE(response);

        if (exp_result != CONTROL_RESULT_SUCCESS) {
            // Skip remaining checks if the command is borked.
            return;
        }

        // Make sure the network is gone.
        EXPECT_FALSE(cfg->getByName(network));

        // Make sure the subnets are gone.
        auto subnet_cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        if (subnets_expected) {
            EXPECT_TRUE(subnet_cfg->getBySubnetId(100));
            EXPECT_TRUE(subnet_cfg->getBySubnetId(101));
            EXPECT_TRUE(subnet_cfg->getBySubnetId(102));

            // Statistics for the preserved subnets must be present.
            EXPECT_TRUE(stats::StatsMgr::instance().getObservation("subnet[100].total-addresses"));
            EXPECT_TRUE(stats::StatsMgr::instance().getObservation("subnet[101].total-addresses"));
            EXPECT_TRUE(stats::StatsMgr::instance().getObservation("subnet[102].total-addresses"));

        } else {
            EXPECT_FALSE(subnet_cfg->getBySubnetId(100));
            EXPECT_FALSE(subnet_cfg->getBySubnetId(101));
            EXPECT_FALSE(subnet_cfg->getBySubnetId(102));

            // Make sure that the reservations are also gone.
            auto cfg_hosts = CfgMgr::instance().getCurrentCfg()->getCfgHosts();
            IOAddress address_subnet1("192.0.2.0");
            IOAddress address_subnet2("192.0.3.0");
            IOAddress address_subnet3("192.0.4.0");
            for (auto i = 0; i < 5; ++i) {
                EXPECT_FALSE(cfg_hosts->get4(SubnetID(100), address_subnet1));
                EXPECT_FALSE(cfg_hosts->get4(SubnetID(101), address_subnet2));
                EXPECT_FALSE(cfg_hosts->get4(SubnetID(102), address_subnet3));

                // Go to next reservation for each subnet.
                address_subnet1 = IOAddress::increase(address_subnet1);
                address_subnet2 = IOAddress::increase(address_subnet2);
                address_subnet3 = IOAddress::increase(address_subnet3);
            }

            // Statistics for these subnets must be gone.
            EXPECT_FALSE(stats::StatsMgr::instance().getObservation("subnet[100].total-addresses"));
            EXPECT_FALSE(stats::StatsMgr::instance().getObservation("subnet[101].total-addresses"));
            EXPECT_FALSE(stats::StatsMgr::instance().getObservation("subnet[102].total-addresses"));
        }
    }
};

// This test verifies that multiple IPv4 subnets are returned as a result
// of sending the 'subnet4-list' command.
TEST_F(Subnet4CmdsTest, subnet4List) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));
    addSubnet("192.168.50.0/24", SubnetID(10));
    addSubnet("192.0.2.0/29", SubnetID(123));
    // Add one IPv6 subnet to the configuration. We want to make sure that
    // this subnet is not returned within the response to the command.
    addSubnet("2001:db8:1::/64", SubnetID(17));

    // Commit configuration updates.
    CfgMgr::instance().commit();

    // Send the command. The returned result should indicate a success and the
    // status message should tell us how many subnets have been returned.
    ConstElementPtr response = testCommand("{ \"command\": \"subnet4-list\" }",
                                           CONTROL_RESULT_SUCCESS,
                                           "3 IPv4 subnets found");

    // Verify that the response has appropriate structure.
    ASSERT_NO_FATAL_FAILURE(checkSubnetListStructure(response, 3));

    // Our 3 IPv4 subnets should be returned in the response.
    ASSERT_TRUE(hasSubnet(response, "10.0.0.0/8", SubnetID(5)));
    ASSERT_TRUE(hasSubnet(response, "192.168.50.0/24", SubnetID(10)));
    ASSERT_TRUE(hasSubnet(response, "192.0.2.0/29", SubnetID(123)));
    // The IPv6 subnet should not be included.
    ASSERT_FALSE(hasSubnet(response, "2001:db8:1::/64", SubnetID(17)));
}

// This test verifies that 'subnet4-list' returns empty list of subnets when
// no IPv4 subnets configured.
TEST_F(Subnet4CmdsTest, noSubnet4List) {
    // Send the command. The returned result should indicate a success and the
    // status message should tell us how many subnets have been returned.
    ConstElementPtr response = testCommand("{ \"command\": \"subnet4-list\" }",
                                           CONTROL_RESULT_EMPTY,
                                           "0 IPv4 subnets found");

    // Verify that the response has appropriate structure and no subnets
    // are included.
    ASSERT_NO_FATAL_FAILURE(checkSubnetListStructure(response, 0));
}

// This test verifies that IPv4 subnet can be retrieved by subnet id
// or a subnet prefix.
TEST_F(Subnet4CmdsTest, subnet4Get) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));
    addSubnet("192.168.50.0/24", SubnetID(10));
    addSubnet("192.0.2.0/29", SubnetID(123));

    // Commit configuration updates.
    CfgMgr::instance().commit();

    // Test that subnets can be retrieved by ID.
    testSubnetGetById("subnet4-get", "10.0.0.0/8", SubnetID(5));
    testSubnetGetById("subnet4-get", "192.168.50.0/24", SubnetID(10));
    testSubnetGetById("subnet4-get", "192.0.2.0/29", SubnetID(123));

    // Test that subnets can be retrieved by prefix.
    testSubnetGetByPrefix("subnet4-get", "10.0.0.0/8", SubnetID(5));
    testSubnetGetByPrefix("subnet4-get", "192.168.50.0/24", SubnetID(10));
    testSubnetGetByPrefix("subnet4-get", "192.0.2.0/29", SubnetID(123));
}

// tests that subnet4-get properly reports returned status
// EMPTY when subnet is not found.
TEST_F(Subnet4CmdsTest, subnet4GetEmpty) {

    // Query by id
    string txt =
        "{\n"
        "    \"command\": \"subnet4-get\",\n"
        "    \"arguments\": {\n"
        "        \"id\": 123\n"
        "    }\n"
        "}\n";
    string exp = "No subnet with id 123 found";
    testCommand(txt, CONTROL_RESULT_EMPTY, exp);

    // Query by subnet
    txt =
        "{\n"
        "    \"command\": \"subnet4-get\",\n"
        "    \"arguments\": {\n"
        "        \"subnet\": \"192.0.2.0/24\"\n"
        "    }\n"
        "}\n";
    exp = "No 192.0.2.0/24 subnet found";
    testCommand(txt, CONTROL_RESULT_EMPTY, exp);
}

// This test verifies negative scenarios for the 'subnet4-get' command.
TEST_F(Subnet4CmdsTest, subnet4GetNegative) {
    // No arguments at all.
    testSubnet4GetNegative("", "no arguments specified for the 'subnet4-get'"
                           " command");
    // Arguments are not in a map.
    testSubnet4GetNegative("5", "arguments specified for the 'subnet4-get'"
                           " command are not a map");
    // No arguments specified.
    testSubnet4GetNegative("{ }", "invalid number of arguments 0 for the"
                           " 'subnet4-get' command. Expecting 'id'"
                           " or 'subnet'");
    // Too many arguments.
    testSubnet4GetNegative("{ \"id\": 5, \"subnet\": \"10.0.0.0/8\" }",
                           "invalid number of arguments 2 for the 'subnet4-get'"
                           " command. Expecting 'id' or 'subnet'");

    // Invalid id argument type.
    testSubnet4GetNegative("{ \"id\": \"foo\" }",
                           "'id' parameter must be an integer");

    // Invalid subnet argument type.
    testSubnet4GetNegative("{ \"subnet\": 6 }",
                           "'subnet' parameter must be a string");

    // Unsupported argument.
    testSubnet4GetNegative("{ \"unsupported-parameter\": 6 }",
                           "'id' or 'subnet' parameter required");
}

// Test that new subnet is added with 'subnet4-add' command.
TEST_F(Subnet4CmdsTest, subnet4Add) {
    // Add the subnet to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));

    // Add non-standard option definition to the LibDHCP runtime options.
    // This is needed to make sure that the server will pick option
    // definition from the current configuration rather than from
    // staging configuration.
    auto cfg_defs = CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    OptionDefinitionPtr def(new OptionDefinition("foo", 254, DHCP4_OPTION_SPACE, "string"));
    ASSERT_NO_THROW(cfg_defs->add(def));
    ASSERT_NO_THROW(LibDHCP::setRuntimeOptionDefs(cfg_defs->getContainer()));

    CfgMgr::instance().commit();

    // Add a configured globals as if we'd parsed the config.
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("renew-timer",
                                                            Element::create(1111));
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("rebind-timer",
                                                            Element::create(2222));

    // Create a command. Include option data for a custom option 'foo'. The
    // parser should check that the definition for this option exists in the
    // current runtime configuration. If the parser is broken it will look
    // for the option in the staging configuration which is only
    // appropriate during full server reconfiguration.
    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"subnet4-add\",\n"
        "    \"arguments\": {\n"
        "        \"subnet4\": [ {\n"
        "            \"id\": 101,\n"
        "            \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],\n"
        "            \"subnet\": \"192.0.2.0/24\",\n"
        "            \"option-data\": [\n"
        "                {\n"
        "                    \"name\": \"foo\",\n"
        "                    \"data\": \"option foo contents\"\n"
        "                }\n"
        "            ]\n"
        "        } ]\n"
        "    }\n"
        "}\n";

    // This is the expected response this command should return.
    string exp_response =
        "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
        "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
        "\"IPv4 subnet added\" }";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "IPv4 subnet added");
    ASSERT_TRUE(response);
    EXPECT_EQ(exp_response, response->str());
    EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));

    // Updated configuration should contain two subnets.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ASSERT_EQ(2, cfg->getAll()->size());

    // Make sure that the subnets are correct.
    ConstSubnet4Ptr subnet = cfg->getBySubnetId(SubnetID(101));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("192.0.2.0/24", subnet->toText());

    // Make sure we inherited the server's globals
    EXPECT_FALSE(subnet->getT1().unspecified());
    EXPECT_EQ(1111, subnet->getT1().get());
    EXPECT_FALSE(subnet->getT2().unspecified());
    EXPECT_EQ(2222, subnet->getT2().get());

    // The subnet we have added initially should still be there.
    subnet = cfg->getBySubnetId(SubnetID(5));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("10.0.0.0/8", subnet->toText());

    // Make sure we didn't overwrite its timer values
    EXPECT_FALSE(subnet->getT1().unspecified());
    EXPECT_EQ(30, subnet->getT1().get());
    EXPECT_FALSE(subnet->getT2().unspecified());
    EXPECT_EQ(40, subnet->getT2().get());

    // Make sure that the statistics have been updated for the new subnet.
    auto total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(100, total_addresses->getInteger().first);
}

// Tests that a new subnet with the FLQ allocator can be added to the
// configuration, and that the allocator is properly initialized.
TEST_F(Subnet4CmdsTest, subnet4AddFLQAllocator) {
    // Create a new subnet with non-default allocator. Note that this
    // allocator requires initialization (i.e., creating a queue of free
    // DHCP leases and installation of the interface manager callbacks).
    // We will test the initialization by verifying that the callbacks
    // are present.
    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"subnet4-add\",\n"
        "    \"arguments\": {\n"
        "        \"subnet4\": [ {\n"
        "            \"id\": 101,\n"
        "            \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],\n"
        "            \"subnet\": \"192.0.2.0/24\",\n"
        "            \"allocator\": \"flq\""
        "        } ]\n"
        "    }\n"
        "}\n";

    // This is the expected response this command should return.
    string exp_response =
        "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
        "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
        "\"IPv4 subnet added\" }";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "IPv4 subnet added");
    ASSERT_TRUE(response);
    EXPECT_EQ(exp_response, response->str());
    EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));

    // Updated configuration should contain one subnet.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ASSERT_EQ(1, cfg->getAll()->size());

    // Make sure that the subnet is correct.
    ConstSubnet4Ptr subnet = cfg->getBySubnetId(SubnetID(101));
    ASSERT_TRUE(subnet);
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
    EXPECT_EQ("flq", subnet->getAllocatorType().get());

    // Make sure that the interface manager now has callbacks. It is the
    // indication that the allocator has been properly initialized.
    auto& lease_mgr = LeaseMgrFactory::instance();
    EXPECT_TRUE(lease_mgr.hasCallbacks());
}


// Test that 'subnet4-add' can be called repeatedly and that id
// will be assigned automatically.
TEST_F(Subnet4CmdsTest, subnet4AddMultiple) {

    // Create a new subnet with id 1.
    std::string command1 = "{\n"
        "    \"command\": \"subnet4-add\",\n"
        "    \"arguments\": {\n"
        "        \"subnet4\": [ {\n"
        "            \"id\": 1,\n"
        "            \"subnet\": \"192.0.2.0/24\"\n"
        "        } ]\n"
        "    }\n"
        "}\n";

    // Creation should be successful.
    string exp_response1 =
        "{ \"arguments\": { \"subnets\": [ { \"id\": 1, "
        "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
        "\"IPv4 subnet added\" }";

    // Command processing should be successful.
    ConstElementPtr response1 = testCommand(command1, CONTROL_RESULT_SUCCESS,
                                            "IPv4 subnet added");
    ASSERT_TRUE(response1);
    EXPECT_EQ(exp_response1, response1->str());

    // Second subnet. Very similar to the first one. The only differences
    // are different identifier and subnet values.
    std::string command2 = "{\n"
        "    \"command\": \"subnet4-add\",\n"
        "    \"arguments\": {\n"
        "        \"subnet4\": [ {\n"
        "            \"id\": 2,\n"
        "            \"subnet\": \"192.0.3.0/24\"\n"
        "        } ]\n"
        "    }\n"
        "}\n";

    string exp_response2 =
        "{ \"arguments\": { \"subnets\": [ { \"id\": 2, "
        "\"subnet\": \"192.0.3.0/24\" } ] }, \"result\": 0, \"text\": "
        "\"IPv4 subnet added\" }";

    // Command processing should be successful.
    ConstElementPtr response2 = testCommand(command2, CONTROL_RESULT_SUCCESS,
                                            "IPv4 subnet added");
    ASSERT_TRUE(response2);
    EXPECT_EQ(exp_response2, response2->str());
}

// Test negative scenarios for 'subnet4-add' command.
TEST_F(Subnet4CmdsTest, subnet4AddNegative) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));

    CfgMgr::instance().commit();

    // No arguments at all.
    testSubnet4AddNegative("", "no arguments specified for the 'subnet4-add'"
                           " command");
    // Empty arguments map.
    testSubnet4AddNegative("{ }", "invalid number of arguments 0 for the"
                           " 'subnet4-add' command. Expecting 'subnet4' list");
    // Invalid parameter as argument.
    testSubnet4AddNegative("{ \"subnet6\": \"foo\" }",
                           "missing 'subnet4' argument for the 'subnet4-add'"
                           " command");
    // Empty subnet4 list.
    testSubnet4AddNegative("{ \"subnet4\": [  ] }",
                           "invalid number of subnets specified for the 'subnet4-add'"
                           " command. Expected one subnet");
    // subnet4 is not a list.
    testSubnet4AddNegative("{ \"subnet4\": \"foo\" }",
                           "'subnet4' argument specified for the 'subnet4-add'"
                           " command is not a list");
    // Invalid subnet definition: missing parameter (subnet).
    testSubnet4AddNegative("{ \"subnet4\": [ { \"valid-lifetime\": 5678 } ] }",
                           "subnet configuration failed: mandatory 'subnet'"
                           " parameter is missing for a subnet being configured"
                           " (<string>:1:58)");
    // Invalid subnet definition: missing parameter (id).
    testSubnet4AddNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" } ] }",
                           "subnet configuration failed: missing parameter"
                           " 'id' (<string>:1:58)");
    // Too many parameters.
    testSubnet4AddNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\","
                           " \"id\": 10 } ],"
                           " \"foo\": \"bar\" }",
                           "invalid number of arguments 2 for the 'subnet4-add'"
                           " command. Expecting 'subnet4' list");
    // Too many subnets.
    testSubnet4AddNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\","
                           " \"id\": 10 },"
                           "{ \"subnet\": \"192.0.2.0/24\", \"id\": 11 } ] }",
                           "invalid number of subnets specified for the"
                           " 'subnet4-add' command. Expected one subnet");
    // Duplicate id.
    testSubnet4AddNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\", "
                           "\"id\": 5 } ] }",
                           "ID of the new IPv4 subnet '5' is already in use");
    // Duplicate subnet prefix.
    testSubnet4AddNegative("{ \"subnet4\": [ { \"subnet\": \"10.0.0.0/8\", "
                           "\"id\": 10 } ] }",
                           "subnet with the prefix of '10.0.0.0/8' already exists");
    // Adding subnet with a host reservation is not allowed. The reservations
    // are created with different set of commands.
    testSubnet4AddNegative("{ \"subnet4\": ["
                           "    {"
                           "        \"subnet\": \"192.0.2.0/24\","
                           "        \"id\": 10,"
                           "        \"reservations\": [ {"
                           "            \"hw-address\": \"01:02:03:04:05:06\","
                           "            \"ip-address\": \"192.0.2.54\""
                           "        } ]"
                           "    }"
                           "]}",
                           "must not specify host reservations with 'subnet4-add'."
                           " Use 'reservation-add' to add a reservation to a subnet");
}

// Test that a subnet is updated with 'subnet4-update' command.
TEST_F(Subnet4CmdsTest, subnet4Update) {
    // Add the subnet to the server configuration.
    addSubnet("192.0.2.0/24", SubnetID(101));
    // Add another subnet.
    addSubnet("10.0.0.0/8", SubnetID(5));

    // Add non-standard option definition to the LibDHCP runtime options.
    // This is needed to make sure that the server will pick option
    // definition from the current configuration rather than from
    // staging configuration.
    auto cfg_defs = CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    OptionDefinitionPtr def(new OptionDefinition("foo", 254, DHCP4_OPTION_SPACE, "string"));
    ASSERT_NO_THROW(cfg_defs->add(def));
    ASSERT_NO_THROW(LibDHCP::setRuntimeOptionDefs(cfg_defs->getContainer()));

    CfgMgr::instance().commit();

    // Add a configured globals as if we'd parsed the config.
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("renew-timer",
                                                            Element::create(1111));
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("rebind-timer",
                                                            Element::create(2222));

    // There are initially no pools so the total number of addresses is 0.
    auto total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(0, total_addresses->getInteger().first);

    // Create a command. Include option data for a custom option 'foo'. The
    // parser should check that the definition for this option exists in the
    // current runtime configuration. If the parser is broken it will look
    // for the option in the staging configuration which is only
    // appropriate during full server reconfiguration.
    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"subnet4-update\",\n"
        "    \"arguments\": {\n"
        "        \"subnet4\": [ {\n"
        "            \"id\": 101,\n"
        "            \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],\n"
        "            \"subnet\": \"192.0.2.0/24\",\n"
        "            \"option-data\": [\n"
        "                {\n"
        "                    \"name\": \"foo\",\n"
        "                    \"data\": \"option foo contents\"\n"
        "                }\n"
        "            ]\n"
        "        } ]\n"
        "    }\n"
        "}\n";

    // This is the expected response this command should return.
    string exp_response =
        "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
        "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
        "\"IPv4 subnet updated\" }";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "IPv4 subnet updated");
    ASSERT_TRUE(response);
    EXPECT_EQ(exp_response, response->str());
    EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));

    // Updated configuration should contain two subnets.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ASSERT_EQ(2, cfg->getAll()->size());

    // Make sure that the subnets are correct.
    auto subnet_it = cfg->getAll()->begin();
    // The other subnet we have added initially should still be there.
    Subnet4Ptr subnet = *subnet_it;;
    ASSERT_TRUE(subnet);
    EXPECT_EQ(5, subnet->getID());
    EXPECT_EQ("10.0.0.0/8", subnet->toText());

    // Make sure we didn't overwrite its timer values
    EXPECT_FALSE(subnet->getT1().unspecified());
    EXPECT_EQ(30, subnet->getT1().get());
    EXPECT_FALSE(subnet->getT2().unspecified());
    EXPECT_EQ(40, subnet->getT2().get());

    // Verify the updated subnet.
    subnet = *++subnet_it;
    ASSERT_TRUE(subnet);
    EXPECT_EQ(101, subnet->getID());
    EXPECT_EQ("192.0.2.0/24", subnet->toText());

    // Make sure we inherited the server's globals
    EXPECT_FALSE(subnet->getT1().unspecified());
    EXPECT_EQ(1111, subnet->getT1().get());
    EXPECT_FALSE(subnet->getT2().unspecified());
    EXPECT_EQ(2222, subnet->getT2().get());

    // Make sure that the statistics have been updated for the new subnet.
    total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(100, total_addresses->getInteger().first);
}

// Test that a subnet is updated with 'subnet4-update' command, and that
// the newly set FLQ allocator is properly initialized.
TEST_F(Subnet4CmdsTest, subnet4UpdateFLQAllocator) {
    // Add the subnet to the server configuration.
    addSubnet("192.0.2.0/24", SubnetID(101));
    CfgMgr::instance().commit();

    // Create a command that updates the subnet to use the FLQ allocator
    // instead of the default allocator.
    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"subnet4-update\",\n"
        "    \"arguments\": {\n"
        "        \"subnet4\": [ {\n"
        "            \"id\": 101,\n"
        "            \"pools\": [ { \"pool\": \"192.0.2.1 - 192.0.2.100\" } ],\n"
        "            \"subnet\": \"192.0.2.0/24\",\n"
        "            \"allocator\": \"flq\"\n"
        "        } ]\n"
        "    }\n"
        "}\n";

    // This is the expected response this command should return.
    string exp_response =
        "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
        "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
        "\"IPv4 subnet updated\" }";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "IPv4 subnet updated");
    ASSERT_TRUE(response);
    EXPECT_EQ(exp_response, response->str());
    EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));

    // Updated configuration should contain one subnet.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ASSERT_EQ(1, cfg->getAll()->size());

    // Make sure that the subnet is correct.
    auto subnet_it = cfg->getAll()->begin();
    Subnet4Ptr subnet = *subnet_it;;
    ASSERT_TRUE(subnet);
    EXPECT_EQ(101, subnet->getID());
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
    EXPECT_EQ("flq", subnet->getAllocatorType().get());

    // Make sure that the interface manager now has callbacks. It is the
    // indication that the allocator has been properly initialized.
    auto& lease_mgr = LeaseMgrFactory::instance();
    EXPECT_TRUE(lease_mgr.hasCallbacks());
}

// Test negative scenarios for 'subnet4-update' command.
TEST_F(Subnet4CmdsTest, subnet4UpdateNegative) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));

    CfgMgr::instance().commit();

    // No arguments at all.
    testSubnet4UpdateNegative("", "no arguments specified for the"
                              " 'subnet4-update' command");
    // Arguments are not a map.
    testSubnet4UpdateNegative("[ ]", "arguments specified for the"
                              " 'subnet4-update' command are not a map");
    // Empty arguments map.
    testSubnet4UpdateNegative("{ }", "invalid number of arguments 0 for the"
                              " 'subnet4-update' command. Expecting"
                              " 'subnet4' list");
    // Invalid parameter as argument.
    testSubnet4UpdateNegative("{ \"subnet6\": \"foo\" }",
                              "missing 'subnet4' argument for the"
                              " 'subnet4-update' command");
    // Empty subnet6 list.
    testSubnet4UpdateNegative("{ \"subnet4\": [  ] }",
                              "invalid number of subnets specified for the"
                              " 'subnet4-update' command. Expected one subnet");
    // subnet4 is not a list.
    testSubnet4UpdateNegative("{ \"subnet4\": \"foo\" }",
                              "'subnet4' argument specified for the"
                              " 'subnet4-update' command is not a list");
    // Invalid subnet definition: missing parameter.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"valid-lifetime\": 5678,"
                              " \"id\": 5 } ] }",
                              "subnet configuration failed: mandatory 'subnet'"
                              " parameter is missing for a subnet being"
                              " configured (<string>:1:61)");
    // Too many parameters.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" } ],"
                              " \"foo\": \"bar\" }",
                              "invalid number of arguments 2 for the"
                              " 'subnet4-update' command. Expecting"
                              " 'subnet4' list");
    // Too many subnets.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" },"
                              "{ \"subnet\": \"192.0.2.0/24\" } ] }",
                              "invalid number of subnets specified for the"
                              " 'subnet4-update' command. Expected one subnet");
    // Missing id.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\""
                              "} ] }",
                              "must specify subnet id with"
                              " 'subnet4-update' command.");
    // Zero id.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                              " \"id\": 0 } ] }",
                              "The 'id' value (0) is not within expected "
                              "range: (1 - 4294967294)");
    // Too large id.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                              " \"id\": 4294967295 } ] }",
                              "The 'id' value (4294967295) is not within"
                              " expected range: (1 - 4294967294)");
    // Not existent id.
    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                              " \"id\": 123 } ] }",
                              "Can't find subnet '123' to update");
    // Adding subnet with a host reservation is not allowed. The reservations
    // are created with different set of commands.
    testSubnet4UpdateNegative("{ \"subnet4\": ["
                              "    {"
                              "        \"id\": 123,"
                              "        \"subnet\": \"192.0.2.0/24\","
                              "        \"reservations\": [ {"
                              "            \"hw-address\": \"01:02:03:04:05:06\","
                              "            \"ip-address\": \"192.0.2.54\""
                              "        } ]"
                              "    }"
                              "]}",
                              "must not specify host reservations with"
                              " 'subnet4-update'.");

    // Prefix conflict: the only case of internal failure.
    addSubnet("10.0.0.0/8", SubnetID(5));
    addSubnet("192.0.2.0/24", SubnetID(1));

    CfgMgr::instance().commit();

    testSubnet4UpdateNegative("{ \"subnet4\": [ { \"subnet\":"
                              "\"192.0.2.0/24\", \"id\": 5 } ] }",
                              "Unable to update subnet '5' in the configuration");
}

// This test verifies that IPv4 subnet can be deleted.
TEST_F(Subnet4CmdsTest, subnet4Del) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));
    addSubnet("192.168.50.0/24", SubnetID(10));
    addSubnet("192.0.2.0/29", SubnetID(123));

    // Commit configuration updates.
    CfgMgr::instance().commit();

    // We should have statistics for the subnet as long as it exists.
    EXPECT_TRUE(stats::StatsMgr::instance().getObservation("subnet[10].total-addresses"));

    // Make sure that reservations have been added to the subnet.
    IOAddress reservation("192.168.50.0");
    for (auto i = 0; i < 5; ++i) {
        EXPECT_TRUE(CfgMgr::instance().getCurrentCfg()->getCfgHosts()->get4(SubnetID(10),
                                                                            reservation));
        reservation = IOAddress::increase(reservation);
    }

    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"subnet4-del\",\n"
        "    \"arguments\": {\n"
        "        \"id\": 10\n"
        "    }\n"
        "}\n";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "IPv4 subnet 192.168.50.0/24"
                                           " (id 10) deleted");
    ASSERT_TRUE(response);
    EXPECT_TRUE(hasSubnet(response, "192.168.50.0/24", 10));

    // Updated configuration should contain two subnets.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ASSERT_EQ(2, cfg->getAll()->size());
    EXPECT_FALSE(cfg->getBySubnetId(SubnetID(10)));

    // Make sure that the reservations are gone after the subnet was
    // deleted.
    reservation = IOAddress("192.168.50.0");
    for (auto i = 0; i < 5; ++i) {
        EXPECT_FALSE(CfgMgr::instance().getCurrentCfg()->getCfgHosts()->get4(SubnetID(10),
                                                                             reservation));
        reservation = IOAddress::increase(reservation);
    }

    // The subnet is gone so the statistics should also be gone.
    EXPECT_FALSE(stats::StatsMgr::instance().getObservation("subnet[10].total-addresses"));
}

// This test verifies negative scenarios for 'subnet4-del' command.
TEST_F(Subnet4CmdsTest, subnet4DelNegative) {
    // Add a single subnet to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));

    // No arguments at all.
    testSubnet4DelNegative("", "no arguments specified for the 'subnet4-del'"
                           " command");
    // Empty arguments map.
    testSubnet4DelNegative("{ }", "invalid number of arguments specified for"
                           " the 'subnet4-del command. Expected subnet identifier");
    // Invalid parameter as argument.
    testSubnet4DelNegative("{ \"bar\": \"foo\" }",
                           "subnet identifier is required for the 'subnet4-del'"
                           " command");
    // Subnet identifier is not a number.
    testSubnet4DelNegative("{ \"id\": \"string\" }",
                           "subnet identifier specified for the 'subnet4-del'"
                           " is not a number");
    // Subnet doesn't exist.
    testSubnet4DelNegative("{ \"id\": 101 }",
                           "no subnet with id 101 found", CONTROL_RESULT_EMPTY);
}

// Test that a subnet is updated with 'subnet4-delta-add' command.
TEST_F(Subnet4CmdsTest, subnet4DeltaAdd) {
    // Add the subnet to the server configuration.
    addSubnet("192.0.2.0/24", SubnetID(101));
    // Add another subnet.
    addSubnet("10.0.0.0/8", SubnetID(5));

    // Add non-standard option definition to the LibDHCP runtime options.
    // This is needed to make sure that the server will pick option
    // definition from the current configuration rather than from
    // staging configuration.
    auto cfg_defs = CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    OptionDefinitionPtr def(new OptionDefinition("foo", 254, DHCP4_OPTION_SPACE, "string"));
    ASSERT_NO_THROW(cfg_defs->add(def));
    ASSERT_NO_THROW(LibDHCP::setRuntimeOptionDefs(cfg_defs->getContainer()));

    CfgMgr::instance().commit();

    // Add a configured globals as if we'd parsed the config.
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("renew-timer",
                                                            Element::create(1111));
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("rebind-timer",
                                                            Element::create(2222));

    // The subnet statistics should exist but it should be 0 as we have no pools.
    auto total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(0, total_addresses->getInteger().first);

    for (uint8_t i = 0; i < 16; ++i) {
        // Create a command. Include option data for a custom option 'foo'. The
        // parser should check that the definition for this option exists in the
        // current runtime configuration. If the parser is broken it will look
        // for the option in the staging configuration which is only
        // appropriate during full server reconfiguration.
        std::ostringstream command;
        command << "{\n"
            "    \"command\": \"subnet4-delta-add\",\n"
            "    \"arguments\": {\n"
            "        \"subnet4\": [ {\n"
            "            \"id\": 101,\n"
            "            \"pools\": [ { \"pool\": \"192.0.2."
                << (i * 10 + 1) << " - 192.0.2." << ((i + 1) * 10) << "\" } ],\n"
            "            \"subnet\": \"192.0.2.0/24\",\n"
            "            \"option-data\": [\n"
            "                {\n"
            "                    \"name\": \"foo\",\n"
            "                    \"data\": \"option foo contents\"\n"
            "                }\n"
            "            ]\n"
            "        } ]\n"
            "    }\n"
            "}\n";

        // This is the expected response this command should return.
        string exp_response =
            "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
            "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
            "\"IPv4 subnet updated\" }";

        // Command processing should be successful.
        ConstElementPtr response = testCommand(command.str(),
                                               CONTROL_RESULT_SUCCESS,
                                               "IPv4 subnet updated");
        ASSERT_TRUE(response);
        EXPECT_EQ(exp_response, response->str());
        EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));

        // Updated configuration should contain two subnets.
        auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        ASSERT_EQ(2, cfg->getAll()->size());

        // Make sure that the subnets are correct.
        auto subnet_it = cfg->getAll()->begin();
        // The other subnet we have added initially should still be there.
        Subnet4Ptr subnet = *subnet_it;;
        ASSERT_TRUE(subnet);
        EXPECT_EQ(5, subnet->getID());
        EXPECT_EQ("10.0.0.0/8", subnet->toText());
        EXPECT_EQ(0, subnet->getPools(Lease::TYPE_V4).size());

        // Make sure we didn't overwrite its timer values
        EXPECT_FALSE(subnet->getT1().unspecified());
        EXPECT_EQ(30, subnet->getT1().get());
        EXPECT_FALSE(subnet->getT2().unspecified());
        EXPECT_EQ(40, subnet->getT2().get());

        // Verify the updated subnet.
        subnet = *++subnet_it;
        ASSERT_TRUE(subnet);
        EXPECT_EQ(101, subnet->getID());
        EXPECT_EQ("192.0.2.0/24", subnet->toText());
        EXPECT_EQ(i + 1, subnet->getPools(Lease::TYPE_V4).size());

        // Make sure we didn't overwrite its timer values
        EXPECT_FALSE(subnet->getT1().unspecified());
        EXPECT_EQ(30, subnet->getT1().get());
        EXPECT_FALSE(subnet->getT2().unspecified());
        EXPECT_EQ(40, subnet->getT2().get());

        // Make sure that the statistics have been updated for the subnet.
        total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
        ASSERT_TRUE(total_addresses);
        EXPECT_EQ((i + 1) * 10, total_addresses->getInteger().first);
    }

    // Prefix conflict: case of internal failure.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ {\n"
                                "    \"id\": 101,\n"
                                "    \"pools\": [ { \"pool\": \"192.0.2.10 - 192.0.2.30\" } ],\n"
                                "    \"subnet\": \"192.0.2.0/24\",\n"
                                "    \"option-data\": [\n"
                                "        {\n"
                                "            \"name\": \"foo\",\n"
                                "            \"data\": \"option foo contents\"\n"
                                "        }\n"
                                "    ]\n"
                                "} ] }\n",
                                "subnet configuration failed: a pool of type V4, with the following "
                                "address range: 192.0.2.10-192.0.2.30 overlaps with an existing pool "
                                "in the subnet: 192.0.2.0/24 to which it is being added (:0:0)");
}

// Test negative scenarios for 'subnet4-delta-add' command.
TEST_F(Subnet4CmdsTest, subnet4DeltaAddNegative) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));

    CfgMgr::instance().commit();

    // No arguments at all.
    testSubnet4DeltaAddNegative("", "no arguments specified for the"
                                " 'subnet4-delta-add' command");
    // Arguments are not a map.
    testSubnet4DeltaAddNegative("[ ]", "arguments specified for the"
                                " 'subnet4-delta-add' command are not a map");
    // Empty arguments map.
    testSubnet4DeltaAddNegative("{ }", "invalid number of arguments 0 for the"
                                " 'subnet4-delta-add' command. Expecting"
                                " 'subnet4' list");
    // Invalid parameter as argument.
    testSubnet4DeltaAddNegative("{ \"subnet6\": \"foo\" }",
                                "missing 'subnet4' argument for the"
                                " 'subnet4-delta-add' command");
    // Empty subnet6 list.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [  ] }",
                                "invalid number of subnets specified for the"
                                " 'subnet4-delta-add' command. Expected one subnet");
    // subnet4 is not a list.
    testSubnet4DeltaAddNegative("{ \"subnet4\": \"foo\" }",
                                "'subnet4' argument specified for the"
                                " 'subnet4-delta-add' command is not a list");
    // Invalid subnet definition: missing parameter.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"valid-lifetime\": 5678,"
                                " \"id\": 5 } ] }",
                                "subnet configuration failed: mandatory 'subnet'"
                                " parameter is missing for a subnet being"
                                " configured (<string>:1:64)");
    // Too many parameters.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" } ],"
                                " \"foo\": \"bar\" }",
                                "invalid number of arguments 2 for the"
                                " 'subnet4-delta-add' command. Expecting"
                                " 'subnet4' list");
    // Too many subnets.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" },"
                                "{ \"subnet\": \"192.0.2.0/24\" } ] }",
                                "invalid number of subnets specified for the"
                                " 'subnet4-delta-add' command. Expected one subnet");
    // Missing id.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\""
                                "} ] }",
                                "must specify subnet id with"
                                " 'subnet4-delta-add' command.");
    // Zero id.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                                " \"id\": 0 } ] }",
                                "The 'id' value (0) is not within expected "
                                "range: (1 - 4294967294)");
    // Too large id.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                                " \"id\": 4294967295 } ] }",
                                "The 'id' value (4294967295) is not within"
                                " expected range: (1 - 4294967294)");
    // Not existent id.
    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                                " \"id\": 123 } ] }",
                                "Can't find subnet '123' to update");
    // Adding subnet with a host reservation is not allowed. The reservations
    // are created with different set of commands.
    testSubnet4DeltaAddNegative("{ \"subnet4\": ["
                                "    {"
                                "        \"id\": 123,"
                                "        \"subnet\": \"192.0.2.0/24\","
                                "        \"reservations\": [ {"
                                "            \"hw-address\": \"01:02:03:04:05:06\","
                                "            \"ip-address\": \"192.0.2.54\""
                                "        } ]"
                                "    }"
                                "]}",
                                "must not specify host reservations with"
                                " 'subnet4-delta-add'.");

    // Prefix conflict: case of internal failure.
    addSubnet("10.0.0.0/8", SubnetID(5));
    addSubnet("192.0.2.0/24", SubnetID(1));

    CfgMgr::instance().commit();

    testSubnet4DeltaAddNegative("{ \"subnet4\": [ { \"subnet\":"
                                "\"192.0.2.0/24\", \"id\": 5 } ] }",
                                "Unable to update subnet '5' in the configuration");
}

// Test that a subnet is updated with 'subnet4-delta-del' command.
TEST_F(Subnet4CmdsTest, subnet4DeltaDel) {
    // Add the subnet to the server configuration.
    addSubnet("192.0.2.0/24", SubnetID(101));
    // Add another subnet.
    addSubnet("10.0.0.0/8", SubnetID(5));

    // Add non-standard option definition to the LibDHCP runtime options.
    // This is needed to make sure that the server will pick option
    // definition from the current configuration rather than from
    // staging configuration.
    auto cfg_defs = CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    OptionDefinitionPtr def(new OptionDefinition("foo", 254, DHCP4_OPTION_SPACE, "string"));
    ASSERT_NO_THROW(cfg_defs->add(def));
    ASSERT_NO_THROW(LibDHCP::setRuntimeOptionDefs(cfg_defs->getContainer()));

    CfgMgr::instance().commit();

    // Add a configured globals as if we'd parsed the config.
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("renew-timer",
                                                            Element::create(1111));
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("rebind-timer",
                                                            Element::create(2222));

    {
        std::ostringstream command;
        command << "{\n"
            "    \"command\": \"subnet4-delta-add\",\n"
            "    \"arguments\": {\n"
            "        \"subnet4\": [ {\n"
            "            \"id\": 101,\n"
            "            \"pools\": [ ";
        for (uint8_t i = 0; i < 16; ++i) {
            command << " { \"pool\": \"192.0.2." << (i * 10 + 1)
                    << " - 192.0.2." << ((i + 1) * 10) << "\" },\n";
        }
        command << "     ],\n"
            "            \"subnet\": \"192.0.2.0/24\",\n"
            "            \"option-data\": [\n"
            "                {\n"
            "                    \"name\": \"foo\",\n"
            "                    \"data\": \"option foo contents\"\n"
            "                }\n"
            "            ]\n"
            "        } ]\n"
            "    }\n"
            "}\n";

        // This is the expected response this command should return.
        string exp_response =
            "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
            "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
            "\"IPv4 subnet updated\" }";

        // Command processing should be successful.
        ConstElementPtr response = testCommand(command.str(),
                                               CONTROL_RESULT_SUCCESS,
                                               "IPv4 subnet updated");
    }

    // We should have the non-zero statistics because some pools exist.
    auto total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(160, total_addresses->getInteger().first);

    // The command can delete pools even if using a different notation:
    // "192.0.2.x-192.0.2.y" vs "192.0.2.x - 192.0.2.y".
    for (uint8_t i = 0; i < 16; ++i) {
        // Create a command. Include option data for a custom option 'foo'. The
        // parser should check that the definition for this option exists in the
        // current runtime configuration. If the parser is broken it will look
        // for the option in the staging configuration which is only
        // appropriate during full server reconfiguration.
        std::ostringstream command;
        command << "{\n"
            "    \"command\": \"subnet4-delta-del\",\n"
            "    \"arguments\": {\n"
            "        \"subnet4\": [ {\n"
            "            \"id\": 101,\n"
            "            \"pools\": [ { \"pool\": \"192.0.2."
                << (i * 10 + 1) << "-192.0.2." << ((i + 1) * 10) << "\" } ],\n"
            "            \"subnet\": \"192.0.2.0/24\",\n"
            "            \"option-data\": [\n"
            "                {\n"
            "                    \"name\": \"foo\",\n"
            "                    \"data\": \"option foo contents\"\n"
            "                }\n"
            "            ]\n"
            "        } ]\n"
            "    }\n"
            "}\n";

        // This is the expected response this command should return.
        string exp_response =
            "{ \"arguments\": { \"subnets\": [ { \"id\": 101, "
            "\"subnet\": \"192.0.2.0/24\" } ] }, \"result\": 0, \"text\": "
            "\"IPv4 subnet updated\" }";

        // Command processing should be successful.
        ConstElementPtr response = testCommand(command.str(),
                                               CONTROL_RESULT_SUCCESS,
                                               "IPv4 subnet updated");
        ASSERT_TRUE(response);
        EXPECT_EQ(exp_response, response->str());
        EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));

        // Updated configuration should contain two subnets.
        auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        ASSERT_EQ(2, cfg->getAll()->size());

        // Make sure that the subnets are correct.
        auto subnet_it = cfg->getAll()->begin();
        // The other subnet we have added initially should still be there.
        Subnet4Ptr subnet = *subnet_it;;
        ASSERT_TRUE(subnet);
        EXPECT_EQ(5, subnet->getID());
        EXPECT_EQ("10.0.0.0/8", subnet->toText());
        EXPECT_EQ(0, subnet->getPools(Lease::TYPE_V4).size());

        // Make sure we didn't overwrite its timer values
        EXPECT_FALSE(subnet->getT1().unspecified());
        EXPECT_EQ(30, subnet->getT1().get());
        EXPECT_FALSE(subnet->getT2().unspecified());
        EXPECT_EQ(40, subnet->getT2().get());

        // Verify the updated subnet.
        subnet = *++subnet_it;
        ASSERT_TRUE(subnet);
        EXPECT_EQ(101, subnet->getID());
        EXPECT_EQ("192.0.2.0/24", subnet->toText());
        EXPECT_EQ(16 - (i + 1), subnet->getPools(Lease::TYPE_V4).size());

        // Make sure we didn't overwrite its timer values
        EXPECT_FALSE(subnet->getT1().unspecified());
        EXPECT_EQ(30, subnet->getT1().get());
        EXPECT_FALSE(subnet->getT2().unspecified());
        EXPECT_EQ(40, subnet->getT2().get());
    }

    // The pools should have been removed, so the statistics is 0.
    total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(0, total_addresses->getInteger().first);
}

// Test negative scenarios for 'subnet4-delta-del' command.
TEST_F(Subnet4CmdsTest, subnet4DeltaDelNegative) {
    // Add several IPv4 subnets to the server configuration.
    addSubnet("10.0.0.0/8", SubnetID(5));

    CfgMgr::instance().commit();

    // No arguments at all.
    testSubnet4DeltaDelNegative("", "no arguments specified for the"
                                " 'subnet4-delta-del' command");
    // Arguments are not a map.
    testSubnet4DeltaDelNegative("[ ]", "arguments specified for the"
                                " 'subnet4-delta-del' command are not a map");
    // Empty arguments map.
    testSubnet4DeltaDelNegative("{ }", "invalid number of arguments 0 for the"
                                " 'subnet4-delta-del' command. Expecting"
                                " 'subnet4' list");
    // Invalid parameter as argument.
    testSubnet4DeltaDelNegative("{ \"subnet6\": \"foo\" }",
                                "missing 'subnet4' argument for the"
                                " 'subnet4-delta-del' command");
    // Empty subnet6 list.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [  ] }",
                                "invalid number of subnets specified for the"
                                " 'subnet4-delta-del' command. Expected one subnet");
    // subnet4 is not a list.
    testSubnet4DeltaDelNegative("{ \"subnet4\": \"foo\" }",
                                "'subnet4' argument specified for the"
                                " 'subnet4-delta-del' command is not a list");
    // Invalid subnet definition: missing parameter.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"valid-lifetime\": 5678,"
                                " \"id\": 5 } ] }",
                                "subnet configuration failed: mandatory 'subnet'"
                                " parameter is missing for a subnet being"
                                " configured (<string>:1:64)");
    // Too many parameters.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" } ],"
                                " \"foo\": \"bar\" }",
                                "invalid number of arguments 2 for the"
                                " 'subnet4-delta-del' command. Expecting"
                                " 'subnet4' list");
    // Too many subnets.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"subnet\": \"192.0.2.0/24\" },"
                                "{ \"subnet\": \"192.0.2.0/24\" } ] }",
                                "invalid number of subnets specified for the"
                                " 'subnet4-delta-del' command. Expected one subnet");
    // Missing id.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\""
                                "} ] }",
                                "must specify subnet id with"
                                " 'subnet4-delta-del' command.");
    // Zero id.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                                " \"id\": 0 } ] }",
                                "The 'id' value (0) is not within expected "
                                "range: (1 - 4294967294)");
    // Too large id.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                                " \"id\": 4294967295 } ] }",
                                "The 'id' value (4294967295) is not within"
                                " expected range: (1 - 4294967294)");
    // Not existent id.
    testSubnet4DeltaDelNegative("{ \"subnet4\": [ { \"subnet\": \"10.1.2.0/29\","
                                " \"id\": 123 } ] }",
                                "Can't find subnet '123' to update");
    // Adding subnet with a host reservation is not allowed. The reservations
    // are created with different set of commands.
    testSubnet4DeltaDelNegative("{ \"subnet4\": ["
                                "    {"
                                "        \"id\": 123,"
                                "        \"subnet\": \"192.0.2.0/24\","
                                "        \"reservations\": [ {"
                                "            \"hw-address\": \"01:02:03:04:05:06\","
                                "            \"ip-address\": \"192.0.2.54\""
                                "        } ]"
                                "    }"
                                "]}",
                                "must not specify host reservations with"
                                " 'subnet4-delta-del'.");
}

// Test that a subnet is updated with multiple 'subnet4-delta-add' and
// 'subnet4-delta-del' commands.
TEST_F(Subnet4CmdsTest, subnet4DeltaAddAndDelMultiple) {
    // Add the subnet to the server configuration.
    addSubnet("192.0.2.0/24", SubnetID(101));
    // Add another subnet.
    addSubnet("10.0.0.0/8", SubnetID(5));

    // Add non-standard option definition to the LibDHCP runtime options.
    // This is needed to make sure that the server will pick option
    // definition from the current configuration rather than from
    // staging configuration.
    auto cfg_defs = CfgMgr::instance().getStagingCfg()->getCfgOptionDef();
    OptionDefinitionPtr def(new OptionDefinition("foo", 254, DHCP4_OPTION_SPACE, "string"));
    ASSERT_NO_THROW(cfg_defs->add(def));
    ASSERT_NO_THROW(LibDHCP::setRuntimeOptionDefs(cfg_defs->getContainer()));

    CfgMgr::instance().commit();

    // Add a configured globals as if we'd parsed the config.
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("renew-timer",
                                                            Element::create(1111));
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("rebind-timer",
                                                            Element::create(2222));

    HandlerType handler;

    auto const& f = [&](const Scenario& test) {
        SCOPED_TRACE(test.desc_);
        // Command processing should be successful.
        ConstElementPtr response = testCommand(test.command_,
                                               CONTROL_RESULT_SUCCESS,
                                               test.exp_text_);
        ASSERT_TRUE(response);
        ASSERT_EQ(test.exp_response_, response->str());
        EXPECT_TRUE(isEquivalent(Element::fromWire(test.exp_response_), response)) <<
                "diff: " << generateDiff(prettyPrint(isc::data::Element::fromWire(test.exp_response_)),
                                         prettyPrint(isc::data::Element::fromWire(response->str())));
        if (test.check_has_subnet_) {
            EXPECT_TRUE(hasSubnet(response, "192.0.2.0/24", 101));
            EXPECT_TRUE(hasSubnet(response, "10.0.0.0/8", 5));
        }

        // Updated configuration should contain two subnets.
        auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        ASSERT_EQ(2, cfg->getAll()->size());

        // Make sure that the subnets are correct.
        auto subnet_it = cfg->getAll()->begin();
        // The other subnet we have added initially should still be there.
        Subnet4Ptr subnet = *subnet_it;;
        ASSERT_TRUE(subnet);
        EXPECT_EQ(5, subnet->getID());
        EXPECT_EQ("10.0.0.0/8", subnet->toText());

        // Make sure we didn't overwrite its timer values
        EXPECT_FALSE(subnet->getT1().unspecified());
        EXPECT_EQ(30, subnet->getT1().get());
        EXPECT_FALSE(subnet->getT2().unspecified());
        EXPECT_EQ(40, subnet->getT2().get());

        // Verify the updated subnet.
        subnet = *++subnet_it;
        ASSERT_TRUE(subnet);
        EXPECT_EQ(101, subnet->getID());
        EXPECT_EQ("192.0.2.0/24", subnet->toText());

        // Make sure we didn't overwrite its timer values
        EXPECT_FALSE(subnet->getT1().unspecified());
        EXPECT_EQ(30, subnet->getT1().get());
        EXPECT_FALSE(subnet->getT2().unspecified());
        EXPECT_EQ(40, subnet->getT2().get());
        for (auto const& again : test.rerun_scenario_) {
            handler(test_steps[again]);
        }
    };

    handler = f;

    for (auto const& test : test_steps) {
        f(test);
    }
}

// Checks whether network4-list command can return a list of shared networks.
// Also checks if only v4 networks are returned.
TEST_F(Subnet4CmdsTest, sharedNetwork4List) {
    addEmptyNetwork("floor1", false); // v4 network
    addEmptyNetwork("office", false); // v4 network
    addEmptyNetwork("lab", true); // v6 network (should be ignored)

    // Send the command. The returned result should indicate a success and the
    // status message should tell us how many subnets have been returned.
    ConstElementPtr response = testCommand("{ \"command\": \"network4-list\" }",
                                           CONTROL_RESULT_SUCCESS,
                                           "2 IPv4 networks found");
    string exp_args =
        "{ \"shared-networks\": [ { \"name\": \"floor1\" }, "
        "{ \"name\": \"office\" } ] }";

    checkArguments(response, exp_args);

    // We can also use our checking routines to verify that networks are returned.
    EXPECT_TRUE(hasNetwork(response, "floor1", false, "", false));
    EXPECT_TRUE(hasNetwork(response, "office", false, "", false));
}

// Checks whether network4-list command can return a situation where there are
// no v4 networks and an empty list is returned.
TEST_F(Subnet4CmdsTest, sharedNetwork4ListEmpty) {
    addEmptyNetwork("lab", true); // v6 network (should be ignored)

    // Send the command. The returned result should indicate an empty list and the
    // status message should tell us how many networks have been returned.
    ConstElementPtr response = testCommand("{ \"command\": \"network4-list\" }",
                                           CONTROL_RESULT_EMPTY,
                                           "0 IPv4 networks found");

    string exp_args = "{ \"shared-networks\": [  ] }";

    checkArguments(response, exp_args);
}

// This test verifies that IPv4 shared network can be retrieved by name.
TEST_F(Subnet4CmdsTest, network4Get) {
    // Add several IPv4 subnets to the server configuration.
    addEmptyNetwork("floor1", false); // v4
    addEmptyNetwork("office", false); // v4
    addEmptyNetwork("lab", true); // v6 (should be ignored)

    addSubnetToNetwork4("office", "192.0.2.0/24", SubnetID(5));
    addSubnetToNetwork4("office", "192.0.3.0/31", SubnetID(6));
    addSubnetToNetwork4("office", "10.0.0.0/8", SubnetID(7));

    string cmd = "{ \"command\": \"network4-get\","
        " \"arguments\": { \"name\": \"office\" } }";

    ConstElementPtr response = testCommand(cmd, CONTROL_RESULT_SUCCESS,
                                           "Info about IPv4 shared network 'office' returned");
    EXPECT_TRUE(hasNetwork(response, "office", true, "192.0.2.0/24", false));
    EXPECT_TRUE(hasNetwork(response, "office", true, "192.0.3.0/31", false));
    EXPECT_TRUE(hasNetwork(response, "office", true, "10.0.0.0/8", false));
}

// This test verifies that network4-get can handle a situation when there
// are no shared networks defined at all.
TEST_F(Subnet4CmdsTest, network4GetEmpty1) {
    string cmd = "{ \"command\": \"network4-get\","
        " \"arguments\": { \"name\": \"floor2\" } }";

    ConstElementPtr response = testCommand(cmd, CONTROL_RESULT_EMPTY,
                                           "No 'floor2' shared network found");
}

// This test verifies that network4-get can handle a situation when there
// are shared networks defined at all, but the specific one requested is not.
TEST_F(Subnet4CmdsTest, network4GetEmpty2) {
    // Add several IPv4 subnets to the server configuration.
    addEmptyNetwork("floor1", false); // v4
    addEmptyNetwork("office", false); // v4
    addEmptyNetwork("lab", true); // v6 (should be ignored)

    string cmd = "{ \"command\": \"network4-get\","
        " \"arguments\": { \"name\": \"floor2\" } }";

    ConstElementPtr response = testCommand(cmd, CONTROL_RESULT_EMPTY,
                                           "No 'floor2' shared network found");
}

// This test verifies that network4-get can handle a situation when there
// is a shared network of requested name specified, but it from a different family.
TEST_F(Subnet4CmdsTest, network4GetOtherFamily) {
    addEmptyNetwork("floor1", true); // it's v6, so should not be returned.

    string cmd = "{ \"command\": \"network4-get\","
        " \"arguments\": { \"name\": \"floor1\" } }";

    ConstElementPtr response = testCommand(cmd, CONTROL_RESULT_EMPTY,
                                           "No 'floor1' shared network found");
}

// Test that new subnet is added with 'network4-add' command.
TEST_F(Subnet4CmdsTest, network4Add) {

    // Create a command. It adds a shared network with two subnets, each with its
    // own option value.
    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"network4-add\",\n"
        "    \"arguments\": {\n"
        "        \"shared-networks\": [ {\n"
        "            \"name\": \"floor1\",\n"
        "            \"renew-timer\": 1011,\n"
        "            \"subnet4\": [ \n"
        "            {\n"
        "                \"id\": 100,\n"
        "                \"pools\": [ { \"pool\": \"192.0.2.2-192.0.2.99\" } ],\n"
        "                \"subnet\": \"192.0.2.0/24\",\n"
        "                \"option-data\": [\n"
        "                    {\n"
        "                        \"name\": \"routers\",\n"
        "                        \"data\": \"192.0.2.1\"\n"
        "                    }\n"
        "                ]\n"
        "            },\n"
        "            {\n"
        "                \"id\": 101,\n"
        "                \"pools\": [ { \"pool\": \"192.0.3.2-192.0.3.99\" } ],\n"
        "                \"subnet\": \"192.0.3.0/24\",\n"
        "                \"renew-timer\": 1001,\n"
        "                \"rebind-timer\": 2002,\n"
        "                \"option-data\": [\n"
        "                    {\n"
        "                        \"name\": \"routers\",\n"
        "                        \"data\": \"192.0.3.1\"\n"
        "                    }\n"
        "                ]\n"
        "            } ]\n"
        "         } ]\n"
        "    }\n"
        "}\n";

    // Add a configured globals as if we'd parsed the config.
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("renew-timer",
                                                            Element::create(1111));
    CfgMgr::instance().getCurrentCfg()->addConfiguredGlobal("rebind-timer",
                                                            Element::create(2222));

    // This is the expected response this command should return.
    string exp_response =
        "{ \"arguments\": { \"shared-networks\": [ { \"name\": \"floor1\" } ] }, "
        "\"result\": 0, \"text\": \"A new IPv4 shared network 'floor1' added\" }";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "A new IPv4 shared network 'floor1' added");
    // Check the response is as expected.
    ASSERT_TRUE(response);
    EXPECT_EQ(exp_response, response->str());

    // Now make sure the network is there and the two subnets are associated
    // with that network.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    ASSERT_EQ(1, cfg->getAll()->size());

    auto net = cfg->getByName("floor1");
    ASSERT_TRUE(net);

    EXPECT_FALSE(net->getT1().unspecified());
    EXPECT_EQ(1011, net->getT1().get());
    EXPECT_FALSE(net->getT2().unspecified());
    EXPECT_EQ(2222, net->getT2().get());

    auto subnets = net->getAllSubnets();
    EXPECT_EQ(2, subnets->size());
    ConstSubnet4Ptr subnet1 = net->getSubnet(100);
    ConstSubnet4Ptr subnet2 = net->getSubnet(101);
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    EXPECT_EQ("192.0.2.0/24", subnet1->toText());
    EXPECT_EQ("192.0.3.0/24", subnet2->toText());

    // Make sure subnet1 inherited the server and network globals
    EXPECT_FALSE(subnet1->getT1().unspecified());
    EXPECT_EQ(1011, subnet1->getT1().get());
    EXPECT_FALSE(subnet1->getT2().unspecified());
    EXPECT_EQ(2222, subnet1->getT2().get());

    // Make sure subnet2 one kept its own
    EXPECT_FALSE(subnet2->getT1().unspecified());
    EXPECT_EQ(1001, subnet2->getT1().get());
    EXPECT_FALSE(subnet2->getT2().unspecified());
    EXPECT_EQ(2002, subnet2->getT2().get());

    // Also make sure the subnets from this network are added to the generic pool
    // of subnets.
    auto cfg_subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    EXPECT_EQ(2, cfg_subnets->getAll()->size());
    subnet1 = cfg_subnets->getBySubnetId(100);
    subnet2 = cfg_subnets->getBySubnetId(101);
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    EXPECT_EQ("192.0.2.0/24", subnet1->toText());
    EXPECT_EQ("192.0.3.0/24", subnet2->toText());

    // Make sure that the statistics have been updated for the subnets.
    auto total_addresses = stats::StatsMgr::instance().getObservation("subnet[100].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(98, total_addresses->getInteger().first);

    total_addresses = stats::StatsMgr::instance().getObservation("subnet[101].total-addresses");
    ASSERT_TRUE(total_addresses);
    EXPECT_EQ(98, total_addresses->getInteger().first);
}

// Tests that a new shared network with the FLQ allocator can be added to the
// configuration, and that the allocator is properly initialized.
TEST_F(Subnet4CmdsTest, network4AddFLQAllocator) {

    // Create a command. It adds a shared network with two subnets, each with its
    // own option value.
    std::ostringstream command;
    command << "{\n"
        "    \"command\": \"network4-add\",\n"
        "    \"arguments\": {\n"
        "        \"shared-networks\": [ {\n"
        "            \"name\": \"floor1\",\n"
        "            \"renew-timer\": 1011,\n"
        "            \"allocator\": \"flq\",\n"
        "            \"subnet4\": [ \n"
        "            {\n"
        "                \"id\": 100,\n"
        "                \"pools\": [ { \"pool\": \"192.0.2.2-192.0.2.99\" } ],\n"
        "                \"subnet\": \"192.0.2.0/24\",\n"
        "                \"allocator\": \"iterative\"\n"
        "            },\n"
        "            {\n"
        "                \"id\": 101,\n"
        "                \"pools\": [ { \"pool\": \"192.0.3.2-192.0.3.99\" } ],\n"
        "                \"subnet\": \"192.0.3.0/24\"\n"
        "            } ]\n"
        "         } ]\n"
        "    }\n"
        "}\n";

    // This is the expected response this command should return.
    string exp_response =
        "{ \"arguments\": { \"shared-networks\": [ { \"name\": \"floor1\" } ] }, "
        "\"result\": 0, \"text\": \"A new IPv4 shared network 'floor1' added\" }";

    // Command processing should be successful.
    ConstElementPtr response = testCommand(command.str(),
                                           CONTROL_RESULT_SUCCESS,
                                           "A new IPv4 shared network 'floor1' added");
    // Check the response is as expected.
    ASSERT_TRUE(response);
    EXPECT_EQ(exp_response, response->str());

    // Now make sure the network is there and the two subnets are associated
    // with that network.
    auto cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    ASSERT_EQ(1, cfg->getAll()->size());

    auto net = cfg->getByName("floor1");
    ASSERT_TRUE(net);

    auto subnets = net->getAllSubnets();
    EXPECT_EQ(2, subnets->size());
    ConstSubnet4Ptr subnet1 = net->getSubnet(100);
    ConstSubnet4Ptr subnet2 = net->getSubnet(101);
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    EXPECT_EQ("192.0.2.0/24", subnet1->toText());
    EXPECT_EQ("192.0.3.0/24", subnet2->toText());

    // Make sure subnet1 uses its own allocator.
    EXPECT_EQ("iterative", subnet1->getAllocatorType().get());

    // Make sure subnet2 inherited the allocator from the shared network.
    EXPECT_EQ("flq", subnet2->getAllocatorType().get());

    // Also make sure the subnets from this network are added to the generic pool
    // of subnets.
    auto cfg_subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    EXPECT_EQ(2, cfg_subnets->getAll()->size());
    subnet1 = cfg_subnets->getBySubnetId(100);
    subnet2 = cfg_subnets->getBySubnetId(101);
    ASSERT_TRUE(subnet1);
    ASSERT_TRUE(subnet2);

    EXPECT_EQ("192.0.2.0/24", subnet1->toText());
    EXPECT_EQ("192.0.3.0/24", subnet2->toText());

    // Make sure that the interface manager now has callbacks. It is the
    // indication that the allocator has been properly initialized.
    auto& lease_mgr = LeaseMgrFactory::instance();
    EXPECT_TRUE(lease_mgr.hasCallbacks());
}


// This test verifies that IPv4 network can be deleted.
// The subnets-action parameter is missing. Expected action:
// subnets should be degraded to stand-along but should not be deleted.
TEST_F(Subnet4CmdsTest, network4Del) {

    string command = "{\n"
        "    \"command\": \"network4-del\",\n"
        "    \"arguments\": {\n"
        "        \"name\": \"floor1\"\n"
        "    }\n"
        "}\n";

    testNetwork4Del("floor1", command, "IPv4 shared network 'floor1' deleted",
                    true, CONTROL_RESULT_SUCCESS);
}

// This test verifies that IPv4 network with subnets can be deleted
// (the parameter subnets-action = "keep") Expected action:
// subnets should be degraded to stand-along but should not be deleted.
TEST_F(Subnet4CmdsTest, network4DelSubnetsActionKeep) {
    string command = "{\n"
        "    \"command\": \"network4-del\",\n"
        "    \"arguments\": {\n"
        "        \"name\": \"floor1\",\n"
        "        \"subnets-action\": \"keep\"\n"
        "    }\n"
        "}\n";

    testNetwork4Del("floor1", command, "IPv4 shared network 'floor1' deleted",
                    true, CONTROL_RESULT_SUCCESS);
}

// This test verifies that IPv4 network with subnets can be deleted
// (the parameter subnets-action = "delete"). Expected action:
// subnets should be removed.
TEST_F(Subnet4CmdsTest, network4DelSubnetsActionDelete) {
    string command = "{\n"
        "    \"command\": \"network4-del\",\n"
        "    \"arguments\": {\n"
        "        \"name\": \"floor1\",\n"
        "        \"subnets-action\": \"delete\"\n"
        "    }\n"
        "}\n";

    testNetwork4Del("floor1", command, "IPv4 shared network 'floor1' deleted",
                    false, CONTROL_RESULT_SUCCESS);
}

// This test verifies that IPv4 network checks values for subnets-action
// The parameter is set to incorrect value. The command
// should be rejected.
TEST_F(Subnet4CmdsTest, network4DelSubnetsActionBogus) {
    // The subnets-action parameter
    string command = "{\n"
        "    \"command\": \"network4-del\",\n"
        "    \"arguments\": {\n"
        "        \"name\": \"floor1\",\n"
        "        \"subnets-action\": \"maybe\"\n"
        "    }\n"
        "}\n";

    testNetwork4Del("floor1", command, "Invalid value for subnets-action parameter: "
                    "maybe, Supported values: 'keep' and 'delete'.",
                    false, CONTROL_RESULT_ERROR);
}

// Checks if a IPv4 subnet can be added to shared network.
TEST_F(Subnet4CmdsTest, network4SubnetAdd) {

    // Create a subnet.
    const SubnetID id(5);
    addSubnet("10.0.0.0/8", id);
    CfgMgr::instance().commit();

    addEmptyNetwork("floor1", false);

    CfgSubnets4Ptr subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
    ConstSubnet4Ptr s = subnets->getBySubnetId(id);
    ASSERT_TRUE(s);

    // This subnet should not belong to any networks
    SharedNetwork4Ptr network;
    s->getSharedNetwork(network);
    EXPECT_FALSE(network);

    string command = "{\n"
        "    \"command\": \"network4-subnet-add\",\n"
        "    \"arguments\": {\n"
        "        \"name\": \"floor1\",\n"
        "        \"id\": 5\n"
        "    }\n"
        "}";

    auto response = testCommand(command, CONTROL_RESULT_SUCCESS,
         "IPv4 subnet 10.0.0.0/8 (id 5) is now part of shared network 'floor1'");

    // Now check that the subnet was added to the network.
    auto networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    ASSERT_EQ(1, networks->getAll()->size());

    auto net = networks->getByName("floor1");
    ASSERT_TRUE(net);
    auto from_network = net->getSubnet(id);
    ASSERT_TRUE(from_network);

    auto from_subnets = subnets->getBySubnetId(id);
    ASSERT_TRUE(from_subnets);
    SharedNetwork4Ptr net_from_subnet;
    from_subnets->getSharedNetwork(net_from_subnet);
    ASSERT_TRUE(net_from_subnet);
    EXPECT_EQ("floor1", net_from_subnet->getName());

    // make sure we're checking the same subnet.
    EXPECT_EQ(from_network->toText(), from_subnets->toText());

    // The statistics for the moved subnet should exist after this operation.
    EXPECT_TRUE(stats::StatsMgr::instance().getObservation("subnet[5].total-addresses"));
}

// Checks if a IPv4 subnet can be removed from a shared network.
TEST_F(Subnet4CmdsTest, network4SubnetDel) {

    // Create a subnet.
    const SubnetID id(5);
    addEmptyNetwork("floor1", false); // v4 network
    Subnet4Ptr subnet = addSubnetToNetwork4("floor1", "10.0.0.0/8", id);

    string command = "{\n"
        "    \"command\": \"network4-subnet-del\",\n"
        "    \"arguments\": {\n"
        "        \"name\": \"floor1\",\n"
        "        \"id\": 5\n"
        "    }\n"
        "}";

    auto response = testCommand(command, CONTROL_RESULT_SUCCESS,
         "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor1'");

    // Now check that the subnet was added to the network.
    auto networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    auto subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();

    ASSERT_EQ(1, networks->getAll()->size());

    auto net = networks->getByName("floor1");
    ASSERT_TRUE(net);
    auto from_network = net->getSubnet(id);
    ASSERT_FALSE(from_network); // it should no longer be part of a network

    // After removing the subnet from a network, it still be present as a plain subnet,
    // but should no longer have any subnet associated with it.
    auto from_subnets = subnets->getBySubnetId(id);
    ASSERT_TRUE(from_subnets);
    from_subnets->getSharedNetwork(net);
    EXPECT_FALSE(net);

    SharedNetwork4Ptr net_from_subnet;
    from_subnets->getSharedNetwork(net_from_subnet);
    EXPECT_FALSE(net_from_subnet);

    // The statistics for the moved subnet should exist after moving the
    // subnet from the shared network to the top-level scope.
    EXPECT_TRUE(stats::StatsMgr::instance().getObservation("subnet[5].total-addresses"));
}

// Checks if a IPv6 subnet is deleted it is removed from its shared network.
TEST_F(Subnet4CmdsTest, inNetworkSubnet4Del) {
    // Create a subnet.
    const SubnetID id(5);
    addEmptyNetwork("floor1", false);
    Subnet4Ptr subnet = addSubnetToNetwork4("floor1", "192.0.2.0/24", id);

    // Verify the subnet was added to the network.
    auto networks = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    auto net = networks->getByName("floor1");
    ASSERT_TRUE(net);
    auto subnet_from_network = net->getSubnet(id);
    ASSERT_TRUE(subnet_from_network);

    string command = "{\n"
        "    \"command\": \"subnet4-del\",\n"
        "    \"arguments\": {\n"
        "        \"id\": 5\n"
        "    }\n"
        "}";

    auto response = testCommand(command, CONTROL_RESULT_SUCCESS,
                                "IPv4 subnet 192.0.2.0/24 (id 5) deleted");

    subnet_from_network = net->getSubnet(id);
    ASSERT_FALSE(subnet_from_network); // it should no longer be part of a network
}

} // end of anonymous namespace
