// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_YANG_CONFIGS_H
#define ISC_YANG_CONFIGS_H

#include <yang/yang_models.h>
#include <yang/testutils/translator_test.h>

namespace isc {
namespace yang {
namespace test {

/// @brief The test module from sysrepo tests.
const std::string testModel = "keatest-module";
const YRTree testTree = YangRepr::buildTreeFromVector({
    { "/keatest-module:container", "", SR_CONTAINER_T, false },
    { "/keatest-module:main", "", SR_CONTAINER_T, false },
    { "/keatest-module:main/string", "str", SR_STRING_T, true },
    { "/keatest-module:main/boolean", "true", SR_BOOL_T, true },
    { "/keatest-module:main/ui8", "8", SR_UINT8_T, true },
    { "/keatest-module:main/ui16", "16", SR_UINT16_T, true },
    { "/keatest-module:main/ui32", "32", SR_UINT32_T, true },
    { "/keatest-module:main/i8", "8", SR_INT8_T, true },
    { "/keatest-module:main/i16", "16", SR_INT16_T, true },
    { "/keatest-module:main/i32", "32", SR_INT32_T, true },
    { "/keatest-module:main/id_ref", "keatest-module:id_1",
      SR_IDENTITYREF_T, true },
    { "/keatest-module:main/enum", "maybe", SR_ENUM_T, true },
    { "/keatest-module:main/raw", "Zm9vYmFy", SR_BINARY_T, true },
    { "/keatest-module:kernel-modules", "", SR_CONTAINER_T, false }
});

/// @brief A subnet with two pools with ietf-dhcpv6-server model.
const std::string subnetTwoPoolsModelIetf6 = IETF_DHCPV6_SERVER;
const YRTree subnetTwoPoolsTreeIetf6 = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']", "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']", "", SR_LIST_T, false },
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
      "address-pool[pool-id='1']", "", SR_LIST_T, false },
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
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", SR_UINT16_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/host-reservations",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      "", SR_CONTAINER_T, false },
});

/// @brief A subnet with timers with ietf-dhcpv6-server model.
const std::string subnetTimersModel = IETF_DHCPV6_SERVER;
const YRTree subnetTimersIetf6 = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']", "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']", "", SR_LIST_T, false },
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
      "address-pool[pool-id='1']", "", SR_LIST_T, false },
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
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", SR_UINT16_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/host-reservations",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      "", SR_CONTAINER_T, false },
});

/// @brief A subnet with two pools with ietf-dhcpv6-server model
/// which validates.
const std::string validModelIetf6 = IETF_DHCPV6_SERVER;
const YRTree validTreeIetf6 = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes"
      "/vendor-info/ent-num", "2495", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets"
      "/option-set[option-set-id='0']", "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets"
      "/option-set[option-set-id='0']/option-set-id",
      "0", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']", "", SR_LIST_T, false },
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
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']", "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/pool-id", "0", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/prefix",
      "2001:db8:1::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/prefix-length", "48", SR_UINT8_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/valid-lifetime", "4000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/preferred-lifetime",
      "3000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/renew-time", "1000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/rebind-time", "2000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/rapid-commit", "false", SR_BOOL_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/option-set-id", "0", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/max-pd-space-utilization",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']", "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/pool-id", "1", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/prefix",
      "2001:db8:2::/48", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/prefix-length", "48", SR_UINT8_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/valid-lifetime", "4000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/preferred-lifetime",
      "3000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/renew-time", "1000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/rebind-time", "2000", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/rapid-commit", "false", SR_BOOL_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/option-set-id", "0", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/max-pd-space-utilization",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", SR_UINT16_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/host-reservations",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      "", SR_CONTAINER_T, false },
});

/// @brief A subnet with a pool and option data lists with
/// kea-dhcp4-server:config model.
const std::string subnetOptionsModelKeaDhcp4 = KEA_DHCP4_SERVER;
const YRTree subnetOptionsTreeKeaDhcp4 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']", "",
      SR_LIST_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/id",
      "111", SR_UINT32_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']", "", SR_LIST_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/code",
      "100", SR_UINT8_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/space",
      "dns", SR_STRING_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/data",
      "12121212", SR_STRING_T, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/csv-format",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/always-send",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']",
      "", SR_LIST_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/start-address",
      "10.0.1.0", SR_STRING_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/end-address",
      "10.0.1.255", SR_STRING_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/prefix",
      "10.0.1.0/24", SR_STRING_T, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/subnet",
      "10.0.0.0/8", SR_STRING_T, true },
    { "/kea-dhcp4-server:config/expired-leases-processing",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/dhcp-ddns",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/config-control",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/sanity-checks",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/interfaces-config",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/relay",
      "", SR_CONTAINER_T, false },
});

/// @brief A subnet with a pool and option data lists with
/// kea-dhcp6-server:config model.
const std::string subnetOptionsModelKeaDhcp6 = KEA_DHCP6_SERVER;
const YRTree subnetOptionsTreeKeaDhcp6 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp6-server:config", "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']", "",
      SR_LIST_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/id",
      "111", SR_UINT32_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']",
      "", SR_LIST_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "start-address", "2001:db8::1:0", SR_STRING_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "end-address", "2001:db8::1:ffff", SR_STRING_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "prefix", "2001:db8::1:0/112", SR_STRING_T, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']",
      "", SR_LIST_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/code",
      "100", SR_UINT16_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/space",
      "dns", SR_STRING_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/data",
      "12121212", SR_STRING_T, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/csv-format",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/always-send",
      "false", SR_BOOL_T, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/subnet",
      "2001:db8::/48", SR_STRING_T, true },
    { "/kea-dhcp6-server:config/expired-leases-processing",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/dhcp-ddns",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/config-control",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/sanity-checks",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/interfaces-config",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/relay",
      "", SR_CONTAINER_T, false },
});

/// @brief Example from the design document.
const std::string designExampleModel = IETF_DHCPV6_SERVER;
const YRTree designExampleTree = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server", "", SR_CONTAINER_PRESENCE_T, false },
    { "/ietf-dhcpv6-server:server/server-config", "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']", "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/network-range-id",
      "1", SR_UINT32_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/network-description",
      "example", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']",
      "", SR_LIST_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']"
      "/pool-id",
      "0", SR_UINT32_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']"
      "/prefix",
      "2001:db8:20:b00::/57", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']"
      "/prefix-length",
      "57", SR_UINT8_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/"
      "pd-pool[pool-id='0']/max-pd-space-utilization",
      "disabled", SR_ENUM_T, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/network-prefix",
      "2001:db8:20:b00::/56", SR_STRING_T, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", SR_UINT16_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/host-reservations",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      "", SR_CONTAINER_T, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/address-pools",
      "", SR_CONTAINER_T, false },
});

const YRTree emptyTreeKeaDhcp4 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp4-server:config", "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/expired-leases-processing",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/dhcp-ddns",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/config-control",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/sanity-checks",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp4-server:config/interfaces-config",
      "", SR_CONTAINER_T, false },
});

const YRTree emptyTreeKeaDhcp6 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp6-server:config", "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/expired-leases-processing",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/dhcp-ddns",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/config-control",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/sanity-checks",
      "", SR_CONTAINER_T, false },
    { "/kea-dhcp6-server:config/interfaces-config",
      "", SR_CONTAINER_T, false },
});

/// @brief Set of example configurations.
const std::vector<std::pair<std::string, YRTree> > test_configs =
{
    { testModel,                   testTree },
    { subnetTwoPoolsModelIetf6,    subnetTwoPoolsTreeIetf6 },
    { subnetTimersModel,           subnetTimersIetf6 },
    { validModelIetf6,             validTreeIetf6 },
    { subnetOptionsModelKeaDhcp4,  subnetOptionsTreeKeaDhcp4 },
    { subnetOptionsModelKeaDhcp6,  subnetOptionsTreeKeaDhcp6 },
    { designExampleModel,          designExampleTree }
};

}  // namespace test
}  // namespace yang
}  // namespace isc

#endif // ISC_YANG_CONFIGS_H
