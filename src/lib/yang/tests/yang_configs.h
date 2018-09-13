// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_YANG_CONFIGS_H
#define ISC_YANG_CONFIGS_H

#include <yang/testutils/translator_test.h>

namespace isc {
namespace yang {
namespace test {

/// @brief The example module from sysrepo tests.
const std::string exampleModel = "example-module";
const YRTree exampleTree = {
    { "/example-module:container",      "", SR_CONTAINER_T, false },
    { "/example-module:container/list", "", SR_LIST_T,      true }
};

/// @brief The test module from sysrepo tests.
const std::string testModel = "test-module";
const YRTree testTree = {
    { "/test-module:main", "", SR_CONTAINER_T, false },
    { "/test-module:main/string", "str", SR_STRING_T, true },
    { "/test-module:main/boolean", "true", SR_BOOL_T, true },
    { "/test-module:main/ui8", "8", SR_UINT8_T, true },
    { "/test-module:main/ui16", "16", SR_UINT16_T, true },
    { "/test-module:main/ui32", "32", SR_UINT32_T, true },
    { "/test-module:main/i8", "8", SR_INT8_T, true },
    { "/test-module:main/i16", "16", SR_INT16_T, true },
    { "/test-module:main/i32", "32", SR_INT32_T, true },
    { "/test-module:main/id_ref", "test-module:id_1", SR_IDENTITYREF_T, true },
    { "/test-module:main/enum", "maybe", SR_ENUM_T, true },
    { "/test-module:main/raw", "Zm9vYmFy", SR_BINARY_T, true },
    { "/test-module:transfer", "", SR_CONTAINER_T, false },
    { "/test-module:transfer/interval", "30", SR_UINT16_T, false },
    { "/test-module:interface", "", SR_CONTAINER_T, false },
    { "/test-module:top-level-default", "default value", SR_STRING_T, false },
    { "/test-module:university", "", SR_CONTAINER_T, false },
    { "/test-module:university/students", "", SR_CONTAINER_T, false },
    { "/test-module:university/classes", "", SR_CONTAINER_T, false },
    { "/test-module:leafref-chain", "", SR_CONTAINER_T, false },
    { "/test-module:kernel-modules", "", SR_CONTAINER_T, false },
    { "/test-module:tpdfs", "", SR_CONTAINER_T, false },
    { "/test-module:tpdfs/unival", "disabled", SR_STRING_T, false }
};

/// @brief A subnet with two pools with ietf-dhcpv6-server model.
const std::string subnetTwoPoolsModelIetf6 = "ietf-dhcpv6-server";
const YRTree subnetTwoPoolsTreeIetf6 = {
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-id", "0", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-prefix",
      "2001:db8::1:0/112", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/start-address",
      "2001:db8::1:0", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/end-address",
      "2001:db8::1:ffff", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/max-address-count",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-id", "1", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-prefix",
      "2001:db8::2:0/112", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/start-address",
      "2001:db8::2:0", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/end-address",
      "2001:db8::2:ffff", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/max-address-count",
      "disabled", SR_ENUM_T, true }
};

/// @brief A subnet with timers with ietf-dhcpv6-server model.
const std::string subnetTimersModel = "ietf-dhcpv6-server";
const YRTree subnetTimersIetf6 = {
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-id", "0", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-prefix",
      "2001:db8::1:0/112", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/start-address",
      "2001:db8::1:0", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/end-address",
      "2001:db8::1:ffff", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/renew-time", "1000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/rebind-time", "2000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/max-address-count",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-id", "1", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-prefix",
      "2001:db8::2:0/112", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/start-address",
      "2001:db8::2:0", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/end-address",
      "2001:db8::2:ffff", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/renew-time", "1000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/rebind-time", "2000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/max-address-count",
      "disabled", SR_ENUM_T, true }
};

/// @brief A subnet with two pools with ietf-dhcpv6-server model
/// which validates.
const std::string validModelIetf6 = "ietf-dhcpv6-server";
const YRTree validTreeIetf6 = {
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes"
      "/vendor-info/ent-num", "2495", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-description",
      "Subnet#111", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-id", "0", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-prefix",
      "2001:db8::1:0/112", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/start-address",
      "2001:db8::1:0", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/end-address",
      "2001:db8::1:ffff", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/valid-lifetime", "4000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/preferred-lifetime",
      "3000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/renew-time", "1000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/rebind-time", "2000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/max-address-count",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/option-set-id", "0", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-id", "1", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-prefix",
      "2001:db8::2:0/112", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/start-address",
      "2001:db8::2:0", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/end-address",
      "2001:db8::2:ffff", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/valid-lifetime", "4000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/preferred-lifetime",
      "3000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/renew-time", "1000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/rebind-time", "2000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/max-address-count",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/option-set-id", "0", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets"
      "/option-set[option-set-id='0']", "", SR_LIST_T, true },
    { "/ietf-dhcpv6-server:server/server-config/option-sets"
      "/option-set[option-set-id='0']/option-set-id",
      "0", SR_UINT32_T, false }
};

/// @brief A subnet with a pool and option data lists with
/// kea-dhcp4:config model.
const std::string subnetOptionsModelKeaDhcp4 = "kea-dhcp4";
const YRTree subnetOptionsTreeKeaDhcp4 = {
    { "/kea-dhcp4:config", "", SR_CONTAINER_T, false },
    { "/kea-dhcp4:config/subnet4", "", SR_CONTAINER_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']", "", SR_LIST_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/id",
      "111", SR_UINT32_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list/"
      "option-data[code='100'][space='dns']", "", SR_LIST_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list/"
      "option-data[code='100'][space='dns']/code",
      "100", SR_UINT8_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list/"
      "option-data[code='100'][space='dns']/space",
      "dns", SR_STRING_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list/"
      "option-data[code='100'][space='dns']/data",
      "12121212", SR_STRING_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list/"
      "option-data[code='100'][space='dns']/csv-format",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/option-data-list/"
      "option-data[code='100'][space='dns']/always-send",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/pools",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/pools/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']",
      "", SR_LIST_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/pools/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/start-address",
      "10.0.1.0", SR_STRING_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/pools/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/end-address",
      "10.0.1.255", SR_STRING_T, false },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/pools/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/prefix",
      "10.0.1.0/24", SR_STRING_T, true },
    { "/kea-dhcp4:config/subnet4/subnet4[id='111']/subnet",
      "10.0.0.0/8", SR_STRING_T, true }
};

/// @brief A subnet with a pool and option data lists with
/// kea-dhcp6:config model.
const std::string subnetOptionsModelKeaDhcp6 = "kea-dhcp6";
const YRTree subnetOptionsTreeKeaDhcp6 = {
    { "/kea-dhcp6:config", "", SR_CONTAINER_T, false },
    { "/kea-dhcp6:config/subnet6", "", SR_CONTAINER_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']", "", SR_LIST_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/id",
      "111", SR_UINT32_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']",
      "", SR_LIST_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "start-address", "2001:db8::1:0", SR_STRING_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "end-address", "2001:db8::1:ffff", SR_STRING_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "prefix", "2001:db8::1:0/112", SR_STRING_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list", "", SR_CONTAINER_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list/option-data[code='100'][space='dns']",
      "", SR_LIST_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list/option-data[code='100'][space='dns']/code",
      "100", SR_UINT16_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list/option-data[code='100'][space='dns']/space",
      "dns", SR_STRING_T, false },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list/option-data[code='100'][space='dns']/data",
      "12121212", SR_STRING_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list/option-data[code='100'][space='dns']/csv-format",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/pools/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data-list/option-data[code='100'][space='dns']/always-send",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp6:config/subnet6/subnet6[id='111']/subnet",
      "2001:db8::/48", SR_STRING_T, true }
};

}; // end of namespace isc::yang::test
}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_YANG_CONFIGS_H
