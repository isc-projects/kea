// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_YANG_CONFIGS_H
#define ISC_YANG_CONFIGS_H

#include <yang/testutils/translator_test.h>
#include <yang/yang_models.h>

#include <vector>

namespace isc {
namespace yang {
namespace test {

/// @brief The test module from sysrepo tests.
const std::string testModel = "keatest-module";
const YRTree testTree = YangRepr::buildTreeFromVector({
    { "/keatest-module:container",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/keatest-module:main",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/keatest-module:main/string",
      "str", libyang::LeafBaseType::String, true },
    { "/keatest-module:main/boolean",
      "true", libyang::LeafBaseType::Bool, true },
    { "/keatest-module:main/ui8",
      "8", libyang::LeafBaseType::Uint8, true },
    { "/keatest-module:main/ui16",
      "16", libyang::LeafBaseType::Uint16, true },
    { "/keatest-module:main/ui32",
      "32", libyang::LeafBaseType::Uint32, true },
    { "/keatest-module:main/ui64",
      "64", libyang::LeafBaseType::Uint64, true },
    { "/keatest-module:main/i8",
      "8", libyang::LeafBaseType::Int8, true },
    { "/keatest-module:main/i16",
      "16", libyang::LeafBaseType::Int16, true },
    { "/keatest-module:main/i32",
      "32", libyang::LeafBaseType::Int32, true },
    { "/keatest-module:main/i64",
      "64", libyang::LeafBaseType::Int64, true },
    { "/keatest-module:main/id_ref",
      "keatest-module:id_1", libyang::LeafBaseType::IdentityRef, true },
    { "/keatest-module:main/enum",
      "maybe", libyang::LeafBaseType::Enum, true },
    { "/keatest-module:main/raw",
      "Zm9vYmFy", libyang::LeafBaseType::Binary, true },
    { "/keatest-module:kernel-modules",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief A subnet with two pools with ietf-dhcpv6-server model.
const std::string subnetTwoPoolsModelIetf6 = IETF_DHCPV6_SERVER;
const YRTree subnetTwoPoolsTreeIetf6 = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-id",
      "0", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-prefix",
      "2001:db8::1:0/112", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/start-address",
      "2001:db8::1:0", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/end-address",
      "2001:db8::1:ffff", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/max-address-count",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-id",
      "1", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-prefix",
      "2001:db8::2:0/112", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/start-address",
      "2001:db8::2:0", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/end-address",
      "2001:db8::2:ffff", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/max-address-count",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", libyang::LeafBaseType::Uint16, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/host-reservations",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief A subnet with timers with ietf-dhcpv6-server model.
const std::string subnetTimersModel = IETF_DHCPV6_SERVER;
const YRTree subnetTimersIetf6 = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-id",
      "0", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/pool-prefix",
      "2001:db8::1:0/112", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/start-address",
      "2001:db8::1:0", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/end-address",
      "2001:db8::1:ffff", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/renew-time",
      "1000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/rebind-time",
      "2000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='0']/max-address-count",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-id",
      "1", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/pool-prefix",
      "2001:db8::2:0/112", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/start-address",
      "2001:db8::2:0", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/end-address",
      "2001:db8::2:ffff", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/renew-time",
      "1000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/rebind-time",
      "2000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools/"
      "address-pool[pool-id='1']/max-address-count",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", libyang::LeafBaseType::Uint16, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/host-reservations",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief A subnet with two pools with ietf-dhcpv6-server model
/// which validates.
const std::string validModelIetf6 = IETF_DHCPV6_SERVER;
const YRTree validTreeIetf6 = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes"
      "/vendor-info/ent-num",
      "2495", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-range-id",
      "111", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-description",
      "Subnet#111", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/network-prefix",
      "2001:db8::/48", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/pool-id",
      "0", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/prefix",
      "2001:db8:1::/48", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/prefix-length",
      "48", libyang::LeafBaseType::Uint8, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/valid-lifetime",
      "4000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/preferred-lifetime",
      "3000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/renew-time",
      "1000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/rebind-time",
      "2000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/rapid-commit",
      "false", libyang::LeafBaseType::Bool, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/option-set-id",
      "0", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='0']/max-pd-space-utilization",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/pool-id",
      "1", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/prefix",
      "2001:db8:2::/48", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/prefix-length",
      "48", libyang::LeafBaseType::Uint8, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/valid-lifetime",
      "4000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/preferred-lifetime",
      "3000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/renew-time",
      "1000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/rebind-time",
      "2000", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/rapid-commit",
      "false", libyang::LeafBaseType::Bool, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/option-set-id",
      "0", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools/"
      "pd-pool[pool-id='1']/max-pd-space-utilization",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", libyang::LeafBaseType::Uint16, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/address-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/pd-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='111']/host-reservations",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief A subnet with a pool and option data lists with
/// kea-dhcp4-server:config model.
const std::string subnetOptionsModelKeaDhcp4 = KEA_DHCP4_SERVER;
const YRTree subnetOptionsTreeKeaDhcp4 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp4-server:config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/id",
      "111", libyang::LeafBaseType::Uint32, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/code",
      "100", libyang::LeafBaseType::Uint8, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/space",
      "dns", libyang::LeafBaseType::String, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/data",
      "12121212", libyang::LeafBaseType::String, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/csv-format",
      "false", libyang::LeafBaseType::Bool, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/always-send",
      "false", libyang::LeafBaseType::Bool, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "option-data[code='100'][space='dns']/never-send",
      "false", libyang::LeafBaseType::Bool, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/start-address",
      "10.0.1.0", libyang::LeafBaseType::String, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/end-address",
      "10.0.1.255", libyang::LeafBaseType::String, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/"
      "pool[start-address='10.0.1.0'][end-address='10.0.1.255']/prefix",
      "10.0.1.0/24", libyang::LeafBaseType::String, true },
    { "/kea-dhcp4-server:config/subnet4[id='111']/subnet",
      "10.0.0.0/8", libyang::LeafBaseType::String, true },
    { "/kea-dhcp4-server:config/expired-leases-processing",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/dhcp-ddns",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/config-control",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/sanity-checks",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/interfaces-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/subnet4[id='111']/relay",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/compatibility",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/multi-threading",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief A subnet with a pool and option data lists with
/// kea-dhcp6-server:config model.
const std::string subnetOptionsModelKeaDhcp6 = KEA_DHCP6_SERVER;
const YRTree subnetOptionsTreeKeaDhcp6 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp6-server:config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/id",
      "111", libyang::LeafBaseType::Uint32, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "start-address",
      "2001:db8::1:0", libyang::LeafBaseType::String, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "end-address",
      "2001:db8::1:ffff", libyang::LeafBaseType::String, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "prefix",
      "2001:db8::1:0/112", libyang::LeafBaseType::String, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/code",
      "100", libyang::LeafBaseType::Uint16, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/space",
      "dns", libyang::LeafBaseType::String, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/data",
      "12121212", libyang::LeafBaseType::String, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/csv-format",
      "false", libyang::LeafBaseType::Bool, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/always-send",
      "false", libyang::LeafBaseType::Bool, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/"
      "pool[start-address='2001:db8::1:0'][end-address='2001:db8::1:ffff']/"
      "option-data[code='100'][space='dns']/never-send",
      "false", libyang::LeafBaseType::Bool, true },
    { "/kea-dhcp6-server:config/subnet6[id='111']/subnet",
      "2001:db8::/48", libyang::LeafBaseType::String, true },
    { "/kea-dhcp6-server:config/expired-leases-processing",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/dhcp-ddns",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/config-control",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/sanity-checks",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/interfaces-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/subnet6[id='111']/relay",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/compatibility",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/multi-threading",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief Example from the design document.
const std::string designExampleModel = IETF_DHCPV6_SERVER;
const YRTree designExampleTree = YangRepr::buildTreeFromVector({
    { "/ietf-dhcpv6-server:server",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/network-range-id",
      "1", libyang::LeafBaseType::Uint32, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/network-description",
      "example", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']"
      "/pool-id",
      "0", libyang::LeafBaseType::Uint32, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']"
      "/prefix",
      "2001:db8:20:b00::/57", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/pd-pool[pool-id='0']"
      "/prefix-length",
      "57", libyang::LeafBaseType::Uint8, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/pd-pools/"
      "pd-pool[pool-id='0']/max-pd-space-utilization",
      "disabled", libyang::LeafBaseType::Enum, true },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/network-prefix",
      "2001:db8:20:b00::/56", libyang::LeafBaseType::String, true },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid/type-code",
      "65535", libyang::LeafBaseType::Uint16, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/host-reservations",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/duid",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/lease-storage",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/serv-attributes/vendor-info",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/option-sets",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/relay-opaque-paras",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/rsoo-enabled-options",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/ietf-dhcpv6-server:server/server-config/network-ranges/"
      "network-range[network-range-id='1']/address-pools",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

const YRTree emptyTreeKeaDhcp4 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp4-server:config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/expired-leases-processing",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/dhcp-ddns",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/config-control",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/sanity-checks",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/interfaces-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/compatibility",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp4-server:config/multi-threading",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

const YRTree emptyTreeKeaDhcp6 = YangRepr::buildTreeFromVector({
    { "/kea-dhcp6-server:config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/expired-leases-processing",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/dhcp-ddns",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/config-control",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/sanity-checks",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/interfaces-config",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/compatibility",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
    { "/kea-dhcp6-server:config/multi-threading",
      std::nullopt, libyang::LeafBaseType::Unknown, false },
});

/// @brief Set of example configurations.
const std::vector<std::pair<std::string, YRTree> > TEST_CONFIGS =
{
    { testModel,                   testTree },
    { subnetTwoPoolsModelIetf6,    subnetTwoPoolsTreeIetf6 },
    { subnetTimersModel,           subnetTimersIetf6 },
    { validModelIetf6,             validTreeIetf6 },
    { subnetOptionsModelKeaDhcp4,  subnetOptionsTreeKeaDhcp4 },
    { subnetOptionsModelKeaDhcp6,  subnetOptionsTreeKeaDhcp6 },
    { designExampleModel,          designExampleTree }
};  // TEST_CONFIGS

}  // namespace test
}  // namespace yang
}  // namespace isc

#endif  // ISC_YANG_CONFIGS_H
