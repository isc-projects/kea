// Copyright (C) 2021-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_QUERY_MACROS_DHCP_H
#define PGSQL_QUERY_MACROS_DHCP_H

/// @file pgsql_query_macros_dhcp.h
/// Collection of common macros defining PgSQL prepared statements used
/// to manage Kea DHCP configuration in the database.
///
/// Some of the macros are DHCPv4 specific, other are DHCPv6 specific.
/// Some macros are common for both DHCP server types. The first
/// parameter @c table_prefix should be set to @c dhcp4 or @c dhcp6,
/// depending which DHCP server type it relates to. Provided value
/// is used as a prefix for PgSQL table names. For example, if the
/// prefix is set to @c dhcp4, the table name referred to in the
/// query may be dhcp4_subnet etc. The second argument in the variadic
/// macro is a part of the WHERE clause in the PgSQL query. The fixed
/// part of the WHERE clause is included in the macro.
namespace isc {
namespace dhcp {

namespace {

#ifndef PGSQL_GET_GLOBAL_PARAMETER
#define PGSQL_GET_GLOBAL_PARAMETER(table_prefix, ...) \
    "SELECT" \
    "  g.id," \
    "  g.name," \
    "  g.value," \
    "  g.parameter_type," \
    "  gmt_epoch(g.modification_ts) as modification_ts, " \
    "  s.tag " \
    "FROM " #table_prefix "_global_parameter AS g " \
    "INNER JOIN " #table_prefix "_global_parameter_server AS a " \
    "  ON g.id = a.parameter_id " \
    "INNER JOIN " #table_prefix "_server AS s " \
    "  ON (a.server_id = s.id) " \
    "WHERE (s.tag = $1 OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY g.id, s.id"
#endif

#ifndef PGSQL_GET_SUBNET4
#define PGSQL_GET_SUBNET4_COMMON(server_join, ...) \
    "SELECT" \
    "  s.subnet_id," \
    "  s.subnet_prefix," \
    "  s.interface_4o6," \
    "  s.interface_id_4o6," \
    "  s.subnet_4o6," \
    "  s.boot_file_name," \
    "  s.client_class," \
    "  s.interface," \
    "  s.match_client_id," \
    "  gmt_epoch(s.modification_ts) as modification_ts, " \
    "  s.next_server," \
    "  s.rebind_timer," \
    "  s.relay," \
    "  s.renew_timer," \
    "  s.require_client_classes," \
    "  s.reservations_global," \
    "  s.server_hostname," \
    "  s.shared_network_name," \
    "  s.user_context," \
    "  s.valid_lifetime," \
    "  p.id," \
    "  p.start_address," \
    "  p.end_address," \
    "  p.subnet_id," \
    "  gmt_epoch(p.modification_ts) as modification_ts, " \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.cancelled," \
    "  x.dhcp4_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  gmt_epoch(x.modification_ts) as modification_ts, " \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.cancelled," \
    "  o.dhcp4_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  gmt_epoch(o.modification_ts) as modification_ts, " \
    "  s.calculate_tee_times," \
    "  s.t1_percent," \
    "  s.t2_percent," \
    "  s.authoritative," \
    "  s.min_valid_lifetime," \
    "  s.max_valid_lifetime," \
    "  p.client_class," \
    "  p.require_client_classes," \
    "  p.user_context," \
    "  s.ddns_send_updates," \
    "  s.ddns_override_no_update," \
    "  s.ddns_override_client_update," \
    "  s.ddns_replace_client_name," \
    "  s.ddns_generated_prefix," \
    "  s.ddns_qualifying_suffix," \
    "  s.reservations_in_subnet," \
    "  s.reservations_out_of_pool," \
    "  s.cache_threshold," \
    "  s.cache_max_age," \
    "  s.offer_lifetime," \
    "  srv.tag " \
    "FROM dhcp4_subnet AS s " \
    server_join \
    "LEFT JOIN dhcp4_pool AS p ON s.subnet_id = p.subnet_id " \
    "LEFT JOIN dhcp4_options AS x ON x.scope_id = 5 AND p.id = x.pool_id " \
    "LEFT JOIN dhcp4_options AS o ON o.scope_id = 1 AND s.subnet_id = o.dhcp4_subnet_id " \
    #__VA_ARGS__ \
    " ORDER BY s.subnet_id, p.id, x.option_id, o.option_id"

#define PGSQL_GET_SUBNET4_NO_TAG(...) \
    PGSQL_GET_SUBNET4_COMMON( \
    "INNER JOIN dhcp4_subnet_server AS a " \
    "  ON s.subnet_id = a.subnet_id " \
    "INNER JOIN dhcp4_server AS srv " \
    "  ON (a.server_id = srv.id) ", \
    __VA_ARGS__)

#define PGSQL_GET_SUBNET4_ANY(...) \
    PGSQL_GET_SUBNET4_COMMON( \
    "LEFT JOIN dhcp4_subnet_server AS a "\
    "  ON s.subnet_id = a.subnet_id " \
    "LEFT JOIN dhcp4_server AS srv " \
    "  ON a.server_id = srv.id ", \
    __VA_ARGS__)

#define PGSQL_GET_SUBNET4_UNASSIGNED(...) \
    PGSQL_GET_SUBNET4_COMMON( \
    "LEFT JOIN dhcp4_subnet_server AS a "\
    "  ON s.subnet_id = a.subnet_id " \
    "LEFT JOIN dhcp4_server AS srv " \
    "  ON a.server_id = srv.id ", \
    WHERE a.subnet_id IS NULL __VA_ARGS__)
#endif

#ifndef PGSQL_GET_SUBNET6
#define PGSQL_GET_SUBNET6_COMMON(server_join, ...) \
    "SELECT" \
    "  s.subnet_id," \
    "  s.subnet_prefix," \
    "  s.client_class," \
    "  s.interface," \
    "  gmt_epoch(s.modification_ts) as modification_ts, " \
    "  s.preferred_lifetime," \
    "  s.rapid_commit," \
    "  s.rebind_timer," \
    "  s.relay," \
    "  s.renew_timer," \
    "  s.require_client_classes," \
    "  s.reservations_global," \
    "  s.shared_network_name," \
    "  s.user_context," \
    "  s.valid_lifetime," \
    "  p.id," \
    "  p.start_address," \
    "  p.end_address," \
    "  p.subnet_id," \
    "  gmt_epoch(p.modification_ts) as modification_ts, " \
    "  d.id," \
    "  d.prefix," \
    "  d.prefix_length," \
    "  d.delegated_prefix_length," \
    "  d.subnet_id," \
    "  gmt_epoch(d.modification_ts) as modification_ts, " \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.cancelled," \
    "  x.dhcp6_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  gmt_epoch(x.modification_ts) as modification_ts, " \
    "  x.pd_pool_id," \
    "  y.option_id," \
    "  y.code," \
    "  y.value," \
    "  y.formatted_value," \
    "  y.space," \
    "  y.persistent," \
    "  y.cancelled," \
    "  y.dhcp6_subnet_id," \
    "  y.scope_id," \
    "  y.user_context," \
    "  y.shared_network_name," \
    "  y.pool_id," \
    "  gmt_epoch(y.modification_ts) as modification_ts, " \
    "  y.pd_pool_id," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.cancelled," \
    "  o.dhcp6_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  gmt_epoch(o.modification_ts) as modification_ts, " \
    "  o.pd_pool_id, " \
    "  s.calculate_tee_times," \
    "  s.t1_percent," \
    "  s.t2_percent," \
    "  s.interface_id," \
    "  s.min_preferred_lifetime," \
    "  s.max_preferred_lifetime," \
    "  s.min_valid_lifetime," \
    "  s.max_valid_lifetime," \
    "  p.client_class," \
    "  p.require_client_classes," \
    "  p.user_context," \
    "  d.excluded_prefix," \
    "  d.excluded_prefix_length," \
    "  d.client_class," \
    "  d.require_client_classes," \
    "  d.user_context," \
    "  s.ddns_send_updates," \
    "  s.ddns_override_no_update," \
    "  s.ddns_override_client_update," \
    "  s.ddns_replace_client_name," \
    "  s.ddns_generated_prefix," \
    "  s.ddns_qualifying_suffix," \
    "  s.reservations_in_subnet," \
    "  s.reservations_out_of_pool," \
    "  s.cache_threshold," \
    "  s.cache_max_age," \
    "  srv.tag " \
    "FROM dhcp6_subnet AS s " \
    server_join \
    "LEFT JOIN dhcp6_pool AS p ON s.subnet_id = p.subnet_id " \
    "LEFT JOIN dhcp6_pd_pool AS d ON s.subnet_id = d.subnet_id " \
    "LEFT JOIN dhcp6_options AS x ON x.scope_id = 5 AND p.id = x.pool_id " \
    "LEFT JOIN dhcp6_options AS y ON y.scope_id = 6 AND d.id = y.pd_pool_id " \
    "LEFT JOIN dhcp6_options AS o ON o.scope_id = 1 AND s.subnet_id = o.dhcp6_subnet_id " \
    #__VA_ARGS__                                                        \
    " ORDER BY s.subnet_id, p.id, d.id, x.option_id, y.option_id, o.option_id"

#define PGSQL_GET_SUBNET6_NO_TAG(...) \
    PGSQL_GET_SUBNET6_COMMON( \
    "INNER JOIN dhcp6_subnet_server AS a " \
    "  ON s.subnet_id = a.subnet_id " \
    "INNER JOIN dhcp6_server AS srv " \
    "  ON (a.server_id = srv.id) ", \
    __VA_ARGS__)

#define PGSQL_GET_SUBNET6_ANY(...) \
    PGSQL_GET_SUBNET6_COMMON( \
    "LEFT JOIN dhcp6_subnet_server AS a "\
    "  ON s.subnet_id = a.subnet_id " \
    "LEFT JOIN dhcp6_server AS srv " \
    "  ON a.server_id = srv.id ", \
    __VA_ARGS__)

#define PGSQL_GET_SUBNET6_UNASSIGNED(...) \
    PGSQL_GET_SUBNET6_COMMON( \
    "LEFT JOIN dhcp6_subnet_server AS a "\
    "  ON s.subnet_id = a.subnet_id " \
    "LEFT JOIN dhcp6_server AS srv " \
    "  ON a.server_id = srv.id ", \
    WHERE a.subnet_id IS NULL __VA_ARGS__)
#endif

#ifndef PGSQL_GET_POOL4_COMMON
#define PGSQL_GET_POOL4_COMMON(server_join, ...) \
      "SELECT" \
      "  p.id," \
      "  p.start_address," \
      "  p.end_address," \
      "  p.subnet_id," \
      "  p.client_class," \
      "  p.require_client_classes," \
      "  p.user_context," \
      "  gmt_epoch(p.modification_ts) as modification_ts, " \
      "  x.option_id," \
      "  x.code," \
      "  x.value," \
      "  x.formatted_value," \
      "  x.space," \
      "  x.persistent," \
      "  x.cancelled," \
      "  x.dhcp4_subnet_id," \
      "  x.scope_id," \
      "  x.user_context," \
      "  x.shared_network_name," \
      "  x.pool_id," \
      "  gmt_epoch(x.modification_ts) as modification_ts " \
      "FROM dhcp4_pool AS p " \
      server_join \
      "LEFT JOIN dhcp4_options AS x ON x.scope_id = 5 AND p.id = x.pool_id " \
      #__VA_ARGS__ \
      " ORDER BY p.id, x.option_id"

#define PGSQL_GET_POOL4_RANGE_WITH_TAG(...) \
    PGSQL_GET_POOL4_COMMON( \
       "INNER JOIN dhcp4_subnet_server AS s ON p.subnet_id = s.subnet_id " \
       "INNER JOIN dhcp4_server AS srv " \
       " ON (s.server_id = srv.id) OR (s.server_id = 1) ", \
       __VA_ARGS__)

#define PGSQL_GET_POOL4_RANGE_NO_TAG(...) \
    PGSQL_GET_POOL4_COMMON("", __VA_ARGS__)
#endif

#ifndef PGSQL_GET_POOL6_COMMON
#define PGSQL_GET_POOL6_COMMON(server_join, ...) \
    "SELECT" \
    "  p.id," \
    "  p.start_address," \
    "  p.end_address," \
    "  p.subnet_id," \
    "  p.client_class," \
    "  p.require_client_classes," \
    "  p.user_context," \
    "  gmt_epoch(p.modification_ts) as modification_ts, " \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.cancelled," \
    "  x.dhcp6_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  gmt_epoch(x.modification_ts) as modification_ts, " \
    "  x.pd_pool_id " \
    "FROM dhcp6_pool AS p " \
    server_join \
    "LEFT JOIN dhcp6_options AS x ON x.scope_id = 5 AND p.id = x.pool_id " \
    #__VA_ARGS__ \
    " ORDER BY p.id, x.option_id"

#define PGSQL_GET_POOL6_RANGE_WITH_TAG(...) \
    PGSQL_GET_POOL6_COMMON( \
    "INNER JOIN dhcp6_subnet_server AS s ON p.subnet_id = s.subnet_id " \
    "INNER JOIN dhcp6_server AS srv " \
    " ON (s.server_id = srv.id) OR (s.server_id = 1) ", \
    __VA_ARGS__)

#define PGSQL_GET_POOL6_RANGE_NO_TAG(...) \
    PGSQL_GET_POOL6_COMMON("", __VA_ARGS__)
#endif

#ifndef PGSQL_GET_PD_POOL_COMMON
#define PGSQL_GET_PD_POOL_COMMON(server_join, ...) \
    "SELECT" \
    "  p.id," \
    "  p.prefix," \
    "  p.prefix_length," \
    "  p.delegated_prefix_length," \
    "  p.subnet_id," \
    "  p.excluded_prefix," \
    "  p.excluded_prefix_length," \
    "  p.client_class," \
    "  p.require_client_classes," \
    "  p.user_context," \
    "  gmt_epoch(p.modification_ts) as modification_ts, " \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.cancelled," \
    "  x.dhcp6_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  gmt_epoch(x.modification_ts) as modification_ts, " \
    "  x.pd_pool_id " \
    "FROM dhcp6_pd_pool AS p " \
    server_join \
    "LEFT JOIN dhcp6_options AS x ON x.scope_id = 6 AND p.id = x.pd_pool_id " \
    #__VA_ARGS__ \
    " ORDER BY p.id, x.option_id" \

#define PGSQL_GET_PD_POOL_WITH_TAG(...) \
    PGSQL_GET_PD_POOL_COMMON( \
    "INNER JOIN dhcp6_subnet_server AS s ON p.subnet_id = s.subnet_id " \
    "INNER JOIN dhcp6_server AS srv " \
    " ON (s.server_id = srv.id) OR (s.server_id = 1) ", \
    __VA_ARGS__)

#define PGSQL_GET_PD_POOL_NO_TAG(...) \
    PGSQL_GET_PD_POOL_COMMON("", __VA_ARGS__)
#endif

#ifndef PGSQL_GET_SHARED_NETWORK4
#define PGSQL_GET_SHARED_NETWORK4_COMMON(server_join, ...) \
    "SELECT" \
    "  n.id," \
    "  n.name," \
    "  n.client_class," \
    "  n.interface," \
    "  n.match_client_id," \
    "  gmt_epoch(n.modification_ts) as modification_ts, " \
    "  n.rebind_timer," \
    "  n.relay," \
    "  n.renew_timer," \
    "  n.require_client_classes," \
    "  n.reservations_global," \
    "  n.user_context," \
    "  n.valid_lifetime," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.cancelled," \
    "  o.dhcp4_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  gmt_epoch(o.modification_ts) as modification_ts, " \
    "  n.calculate_tee_times," \
    "  n.t1_percent," \
    "  n.t2_percent," \
    "  n.authoritative," \
    "  n.boot_file_name," \
    "  n.next_server," \
    "  n.server_hostname," \
    "  n.min_valid_lifetime," \
    "  n.max_valid_lifetime," \
    "  n.ddns_send_updates," \
    "  n.ddns_override_no_update," \
    "  n.ddns_override_client_update," \
    "  n.ddns_replace_client_name," \
    "  n.ddns_generated_prefix," \
    "  n.ddns_qualifying_suffix," \
    "  n.reservations_in_subnet," \
    "  n.reservations_out_of_pool," \
    "  n.cache_threshold," \
    "  n.cache_max_age," \
    "  n.offer_lifetime," \
    "  s.tag " \
    "FROM dhcp4_shared_network AS n " \
    server_join \
    "LEFT JOIN dhcp4_options AS o ON o.scope_id = 4 AND n.name = o.shared_network_name " \
    #__VA_ARGS__ \
    " ORDER BY n.id, s.id, o.option_id"

#define PGSQL_GET_SHARED_NETWORK4_NO_TAG(...) \
    PGSQL_GET_SHARED_NETWORK4_COMMON( \
    "INNER JOIN dhcp4_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "INNER JOIN dhcp4_server AS s " \
    "  ON (a.server_id = s.id) ", \
    __VA_ARGS__)

#define PGSQL_GET_SHARED_NETWORK4_ANY(...) \
    PGSQL_GET_SHARED_NETWORK4_COMMON( \
    "LEFT JOIN dhcp4_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "LEFT JOIN dhcp4_server AS s " \
    "  ON a.server_id = s.id ", \
    __VA_ARGS__)

#define PGSQL_GET_SHARED_NETWORK4_UNASSIGNED(...) \
    PGSQL_GET_SHARED_NETWORK4_COMMON( \
    "LEFT JOIN dhcp4_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "LEFT JOIN dhcp4_server AS s " \
    "  ON a.server_id = s.id ", \
    WHERE a.shared_network_id IS NULL __VA_ARGS__)
#endif

#ifndef PGSQL_GET_SHARED_NETWORK6
#define PGSQL_GET_SHARED_NETWORK6_COMMON(server_join, ...) \
    "SELECT" \
    "  n.id," \
    "  n.name," \
    "  n.client_class," \
    "  n.interface," \
    "  gmt_epoch(n.modification_ts) as modification_ts, " \
    "  n.preferred_lifetime," \
    "  n.rapid_commit," \
    "  n.rebind_timer," \
    "  n.relay," \
    "  n.renew_timer," \
    "  n.require_client_classes," \
    "  n.reservations_global," \
    "  n.user_context," \
    "  n.valid_lifetime," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.cancelled," \
    "  o.dhcp6_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  gmt_epoch(o.modification_ts) as modification_ts, " \
    "  o.pd_pool_id, " \
    "  n.calculate_tee_times," \
    "  n.t1_percent," \
    "  n.t2_percent," \
    "  n.interface_id," \
    "  n.min_preferred_lifetime," \
    "  n.max_preferred_lifetime," \
    "  n.min_valid_lifetime," \
    "  n.max_valid_lifetime," \
    "  n.ddns_send_updates," \
    "  n.ddns_override_no_update," \
    "  n.ddns_override_client_update," \
    "  n.ddns_replace_client_name," \
    "  n.ddns_generated_prefix," \
    "  n.ddns_qualifying_suffix," \
    "  n.reservations_in_subnet," \
    "  n.reservations_out_of_pool," \
    "  n.cache_threshold," \
    "  n.cache_max_age," \
    "  s.tag " \
    "FROM dhcp6_shared_network AS n " \
    server_join \
    "LEFT JOIN dhcp6_options AS o ON o.scope_id = 4 AND n.name = o.shared_network_name " \
    #__VA_ARGS__ \
    " ORDER BY n.id, s.id, o.option_id"

#define PGSQL_GET_SHARED_NETWORK6_NO_TAG(...) \
    PGSQL_GET_SHARED_NETWORK6_COMMON( \
    "INNER JOIN dhcp6_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "INNER JOIN dhcp6_server AS s " \
    "  ON (a.server_id = s.id) ", \
    __VA_ARGS__)

#define PGSQL_GET_SHARED_NETWORK6_ANY(...) \
    PGSQL_GET_SHARED_NETWORK6_COMMON( \
    "LEFT JOIN dhcp6_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "LEFT JOIN dhcp6_server AS s " \
    "  ON a.server_id = s.id ", \
    __VA_ARGS__)

#define PGSQL_GET_SHARED_NETWORK6_UNASSIGNED(...) \
    PGSQL_GET_SHARED_NETWORK6_COMMON( \
    "LEFT JOIN dhcp6_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "LEFT JOIN dhcp6_server AS s " \
    "  ON a.server_id = s.id ", \
    WHERE a.shared_network_id IS NULL __VA_ARGS__)
#endif

#ifndef PGSQL_GET_OPTION_DEF
#define PGSQL_GET_OPTION_DEF(table_prefix, ...) \
    "SELECT" \
    "  d.id," \
    "  d.code," \
    "  d.name," \
    "  d.space," \
    "  d.type," \
    "  gmt_epoch(d.modification_ts) as modification_ts, " \
    "  d.is_array," \
    "  d.encapsulate," \
    "  d.record_types," \
    "  d.user_context," \
    "  s.tag " \
    "FROM " #table_prefix "_option_def AS d " \
    "INNER JOIN " #table_prefix "_option_def_server AS a" \
    "  ON d.id = a.option_def_id " \
    "INNER JOIN " #table_prefix "_server AS s " \
    "  ON a.server_id = s.id " \
    "WHERE (s.tag = $1 OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY d.id"
#endif

#ifndef PGSQL_GET_OPTION_COMMON
#define PGSQL_GET_OPTION_COMMON(table_prefix, pd_pool_id, ...) \
    "SELECT" \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.cancelled," \
    "  o." #table_prefix "_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  gmt_epoch(o.modification_ts) as modification_ts, " \
    "  s.tag " \
    pd_pool_id \
    "FROM " #table_prefix "_options AS o " \
    "INNER JOIN " #table_prefix "_options_server AS a" \
    "  ON o.option_id = a.option_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE (s.tag = $1 OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY o.option_id, s.id"

#define PGSQL_GET_OPTION4(...) \
    PGSQL_GET_OPTION_COMMON(dhcp4, "", __VA_ARGS__)

#define PGSQL_GET_OPTION6(...) \
    PGSQL_GET_OPTION_COMMON(dhcp6, ", o.pd_pool_id ", __VA_ARGS__)
#endif

#ifndef PGSQL_GET_AUDIT_ENTRIES_TIME
#define PGSQL_GET_AUDIT_ENTRIES_TIME(table_prefix) \
    "SELECT" \
    "  a.id," \
    "  a.object_type," \
    "  a.object_id," \
    "  a.modification_type," \
    "  gmt_epoch(r.modification_ts) as modification_ts, " \
    "  r.id, " \
    "  r.log_message " \
    "FROM " #table_prefix "_audit AS a " \
    "INNER JOIN " #table_prefix "_audit_revision AS r " \
    "  ON a.revision_id = r.id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON r.server_id = s.id " \
    "WHERE (s.tag = $1 OR s.id = 1) AND ((r.modification_ts, r.id) > (cast($2 as timestamp), $3))" \
    " ORDER BY r.modification_ts, r.id, a.id"
#endif

#ifndef PGSQL_GET_SERVERS_COMMON
#define PGSQL_GET_SERVERS_COMMON(table_prefix, ...) \
    "SELECT" \
    "  s.id," \
    "  s.tag," \
    "  s.description," \
    "  gmt_epoch(s.modification_ts) as modification_ts " \
    "FROM " #table_prefix "_server AS s " \
    "WHERE s.id > 1 " \
    __VA_ARGS__ \
    " ORDER BY s.id"

#define PGSQL_GET_ALL_SERVERS(table_prefix) \
    PGSQL_GET_SERVERS_COMMON(table_prefix, "")

#define PGSQL_GET_SERVER(table_prefix) \
    PGSQL_GET_SERVERS_COMMON(table_prefix, " AND s.tag = $1")
#endif

#ifndef PGSQL_GET_CLIENT_CLASS4_COMMON
#define PGSQL_GET_CLIENT_CLASS4_COMMON(server_join, ...) \
    "SELECT " \
    "  c.id," \
    "  c.name," \
    "  c.test," \
    "  c.next_server," \
    "  c.server_hostname," \
    "  c.boot_file_name," \
    "  c.only_if_required," \
    "  c.valid_lifetime," \
    "  c.min_valid_lifetime," \
    "  c.max_valid_lifetime," \
    "  c.depend_on_known_directly," \
    "  o.depend_on_known_indirectly, " \
    "  gmt_epoch(c.modification_ts) as modification_ts, " \
    "  c.user_context," \
    "  c.offer_lifetime," \
    "  d.id," \
    "  d.code," \
    "  d.name," \
    "  d.space," \
    "  d.type," \
    "  gmt_epoch(d.modification_ts) as modification_ts, " \
    "  d.is_array," \
    "  d.encapsulate," \
    "  d.record_types," \
    "  d.user_context," \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.cancelled," \
    "  x.dhcp4_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  gmt_epoch(x.modification_ts) as modification_ts, " \
    "  s.tag " \
    "FROM dhcp4_client_class AS c " \
    "INNER JOIN dhcp4_client_class_order AS o " \
    "  ON c.id = o.class_id " \
    server_join \
    "LEFT JOIN dhcp4_option_def AS d ON c.id = d.class_id " \
    "LEFT JOIN dhcp4_options AS x ON x.scope_id = 2 AND c.name = x.dhcp_client_class " \
    #__VA_ARGS__ \
    "  ORDER BY o.order_index, d.id, x.option_id"

#define PGSQL_GET_CLIENT_CLASS4_WITH_TAG(...) \
    PGSQL_GET_CLIENT_CLASS4_COMMON( \
    "INNER JOIN dhcp4_client_class_server AS a " \
    "  ON c.id = a.class_id " \
    "INNER JOIN dhcp4_server AS s " \
    "  ON a.server_id = s.id ", \
    __VA_ARGS__)

#define PGSQL_GET_CLIENT_CLASS4_UNASSIGNED(...) \
    PGSQL_GET_CLIENT_CLASS4_COMMON( \
    "LEFT JOIN dhcp4_client_class_server AS a " \
    "  ON c.id = a.class_id " \
    "LEFT JOIN dhcp4_server AS s " \
    "  ON a.server_id = s.id ", \
    WHERE a.class_id IS NULL __VA_ARGS__)
#endif

#ifndef PGSQL_GET_CLIENT_CLASS6_COMMON
#define PGSQL_GET_CLIENT_CLASS6_COMMON(server_join, ...) \
    "SELECT " \
    "  c.id," \
    "  c.name," \
    "  c.test," \
    "  c.only_if_required," \
    "  c.valid_lifetime," \
    "  c.min_valid_lifetime," \
    "  c.max_valid_lifetime," \
    "  c.depend_on_known_directly," \
    "  o.depend_on_known_indirectly, " \
    "  gmt_epoch(c.modification_ts) as modification_ts, " \
    "  c.user_context, " \
    "  d.id," \
    "  d.code," \
    "  d.name," \
    "  d.space," \
    "  d.type," \
    "  gmt_epoch(d.modification_ts) as modification_ts, " \
    "  d.is_array," \
    "  d.encapsulate," \
    "  d.record_types," \
    "  d.user_context," \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.cancelled," \
    "  x.dhcp6_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  gmt_epoch(x.modification_ts) as modification_ts, " \
    "  s.tag, " \
    "  c.preferred_lifetime," \
    "  c.min_preferred_lifetime, " \
    "  c.max_preferred_lifetime " \
    "FROM dhcp6_client_class AS c " \
    "INNER JOIN dhcp6_client_class_order AS o " \
    "  ON c.id = o.class_id " \
    server_join \
    "LEFT JOIN dhcp6_option_def AS d ON c.id = d.class_id " \
    "LEFT JOIN dhcp6_options AS x ON x.scope_id = 2 AND c.name = x.dhcp_client_class " \
    #__VA_ARGS__ \
    "  ORDER BY o.order_index, d.id, x.option_id"

#define PGSQL_GET_CLIENT_CLASS6_WITH_TAG(...) \
    PGSQL_GET_CLIENT_CLASS6_COMMON( \
    "INNER JOIN dhcp6_client_class_server AS a " \
    "  ON c.id = a.class_id " \
    "INNER JOIN dhcp6_server AS s " \
    "  ON a.server_id = s.id ", \
    __VA_ARGS__)

#define PGSQL_GET_CLIENT_CLASS6_UNASSIGNED(...) \
    PGSQL_GET_CLIENT_CLASS6_COMMON( \
    "LEFT JOIN dhcp6_client_class_server AS a " \
    "  ON c.id = a.class_id " \
    "LEFT JOIN dhcp6_server AS s " \
    "  ON a.server_id = s.id ", \
    WHERE a.class_id IS NULL __VA_ARGS__)
#endif

#ifndef PGSQL_INSERT_GLOBAL_PARAMETER
#define PGSQL_INSERT_GLOBAL_PARAMETER(table_prefix) \
    "INSERT INTO " #table_prefix "_global_parameter(" \
    "  name," \
    "  value," \
    "  parameter_type," \
    "  modification_ts" \
    ") VALUES ($1, $2, $3, $4)"
#endif

#ifndef PGSQL_INSERT_GLOBAL_PARAMETER_SERVER
#define PGSQL_INSERT_GLOBAL_PARAMETER_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_global_parameter_server(" \
    "  parameter_id," \
    "  modification_ts," \
    "  server_id" \
    ") VALUES ($1, $2, (SELECT id FROM " #table_prefix "_server WHERE tag = $3))"
#endif

#ifndef PGSQL_INSERT_SUBNET_SERVER
#define PGSQL_INSERT_SUBNET_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_subnet_server(" \
    "  subnet_id," \
    "  modification_ts," \
    "  server_id" \
    ") VALUES ($1, $2, (SELECT id FROM " #table_prefix "_server WHERE tag = $3))"
#endif

#ifndef PGSQL_INSERT_POOL
#define PGSQL_INSERT_POOL(table_prefix) \
    "INSERT INTO " #table_prefix "_pool(" \
    "  start_address," \
    "  end_address," \
    "  subnet_id," \
    "  client_class," \
    "  require_client_classes," \
    "  user_context," \
    "  modification_ts" \
    ") VALUES (cast($1 as inet), cast($2 as inet), $3, $4, $5, cast($6 as json), $7)"
#endif

#ifndef PGSQL_INSERT_PD_POOL
#define PGSQL_INSERT_PD_POOL() \
    "INSERT INTO dhcp6_pd_pool(" \
    "  prefix," \
    "  prefix_length," \
    "  delegated_prefix_length," \
    "  subnet_id," \
    "  excluded_prefix," \
    "  excluded_prefix_length," \
    "  client_class," \
    "  require_client_classes," \
    "  user_context," \
    "  modification_ts" \
    ") VALUES ($1, $2, $3, $4, $5, $6, $7, $8, cast($9 as json), $10)"
#endif

#ifndef PGSQL_INSERT_SHARED_NETWORK_SERVER
#define PGSQL_INSERT_SHARED_NETWORK_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_shared_network_server(" \
    "  shared_network_id," \
    "  modification_ts," \
    "  server_id" \
    ") VALUES (" \
    "    (SELECT id FROM " #table_prefix "_shared_network WHERE name = $1), $2," \
    "    (SELECT id FROM " #table_prefix "_server WHERE tag = $3)" \
    ")"
#endif

#ifndef PGSQL_INSERT_OPTION_DEF
#define PGSQL_INSERT_OPTION_DEF(table_prefix) \
    "INSERT INTO " #table_prefix "_option_def (" \
    "  code," \
    "  name," \
    "  space," \
    "  type," \
    "  modification_ts," \
    "  is_array," \
    "  encapsulate," \
    "  record_types," \
    "  user_context," \
    "  class_id" \
    ") VALUES ($1, $2, $3, $4, $5, $6, $7, $8, cast($9 as json), $10)"
#endif

#ifndef PGSQL_INSERT_OPTION_DEF_CLIENT_CLASS
#define PGSQL_INSERT_OPTION_DEF_CLIENT_CLASS(table_prefix) \
    "INSERT INTO " #table_prefix "_option_def (" \
    "  code," \
    "  name," \
    "  space," \
    "  type," \
    "  modification_ts," \
    "  is_array," \
    "  encapsulate," \
    "  record_types," \
    "  user_context," \
    "  class_id" \
    ") VALUES ($1, $2, $3, $4, $5, $6, $7, $8, cast($9 as json), " \
    "          (SELECT id FROM " #table_prefix "_client_class WHERE name = $10))"
#endif

#ifndef PGSQL_INSERT_OPTION_DEF_SERVER
#define PGSQL_INSERT_OPTION_DEF_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_option_def_server(" \
    "  option_def_id," \
    "  modification_ts," \
    "  server_id" \
    ") VALUES ($1, $2, (SELECT id FROM " #table_prefix "_server WHERE tag = $3))"
#endif

#ifndef PGSQL_INSERT_OPTION_COMMON
#define PGSQL_INSERT_OPTION_COMMON(table_prefix, pd_pool_id, last) \
    "INSERT INTO " #table_prefix "_options (" \
    "  code," \
    "  value," \
    "  formatted_value," \
    "  space," \
    "  persistent," \
    "  cancelled," \
    "  dhcp_client_class," \
    " " #table_prefix "_subnet_id," \
    "  scope_id," \
    "  user_context," \
    "  shared_network_name," \
    "  pool_id," \
    "  modification_ts" \
    pd_pool_id \
    ") VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, cast($10 as json), $11, $12, $13" last ")"

#define PGSQL_INSERT_OPTION4() \
    PGSQL_INSERT_OPTION_COMMON(dhcp4, "", "")

#define PGSQL_INSERT_OPTION6() \
    PGSQL_INSERT_OPTION_COMMON(dhcp6, ", pd_pool_id ", ", $14")
#endif

#ifndef PGSQL_INSERT_OPTION_SERVER
#define PGSQL_INSERT_OPTION_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_options_server (" \
    "  option_id," \
    "  modification_ts," \
    "  server_id" \
    ") VALUES ($1, $2, (SELECT id FROM " #table_prefix "_server WHERE tag = $3))"
#endif

#ifndef PGSQL_INSERT_CLIENT_CLASS_SERVER
#define PGSQL_INSERT_CLIENT_CLASS_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_client_class_server (" \
    "  class_id," \
    "  modification_ts," \
    "  server_id" \
    ") VALUES ((SELECT id FROM " #table_prefix "_client_class WHERE name = $1), $2," \
    "          (SELECT id FROM " #table_prefix "_server WHERE tag = $3))"
#endif

#ifndef PGSQL_INSERT_CLIENT_CLASS_DEPENDENCY
#define PGSQL_INSERT_CLIENT_CLASS_DEPENDENCY(table_prefix) \
    "INSERT INTO " #table_prefix "_client_class_dependency (" \
    "  class_id," \
    "  dependency_id" \
    ") VALUES ((SELECT id FROM " #table_prefix "_client_class WHERE name = $1), " \
    "          (SELECT id FROM " #table_prefix "_client_class WHERE name = $2))"
#endif

#ifndef PGSQL_INSERT_SERVER
#define PGSQL_INSERT_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_server (" \
    "  tag," \
    "  description," \
    "  modification_ts" \
    ") VALUES ($1, $2, $3)"
#endif

#ifndef PGSQL_UPDATE_GLOBAL_PARAMETER
#define PGSQL_UPDATE_GLOBAL_PARAMETER(table_prefix) \
    "UPDATE " #table_prefix "_global_parameter AS g " \
    "SET " \
    "    name = $1, " \
    "    value = $2, " \
    "    parameter_type = $3, " \
    "    modification_ts = $4 " \
    "FROM " #table_prefix "_global_parameter_server as a, " \
    "     " #table_prefix "_server as s " \
    "WHERE g.id = a.parameter_id AND " \
    "      a.server_id = s.id AND " \
    "      s.tag = $5 AND g.name = $6"
#endif

#ifndef PGSQL_UPDATE_OPTION_DEF
#define PGSQL_UPDATE_OPTION_DEF(table_prefix) \
    "UPDATE " #table_prefix "_option_def AS d " \
    "SET" \
    "  code = $1," \
    "  name = $2," \
    "  space = $3," \
    "  type = $4," \
    "  modification_ts = $5," \
    "  is_array = $6," \
    "  encapsulate = $7," \
    "  record_types = $8," \
    "  user_context = cast($9 as json), " \
    "  class_id = $10 " \
    "FROM " #table_prefix "_option_def_server as a, " \
    "     " #table_prefix "_server as s " \
    "WHERE d.id = a.option_def_id AND" \
    "      a.server_id = s.id AND " \
    "      s.tag = $11 AND d.code = $12 AND d.space = $13"
#endif

#ifndef PGSQL_UPDATE_OPTION_DEF_CLIENT_CLASS
#define PGSQL_UPDATE_OPTION_DEF_CLIENT_CLASS(table_prefix) \
    "UPDATE " #table_prefix "_option_def AS d " \
    "SET" \
    "  code = $1," \
    "  name = $2," \
    "  space = $3," \
    "  type = $4," \
    "  modification_ts = $5," \
    "  is_array = $6," \
    "  encapsulate = $7," \
    "  record_types = $8," \
    "  user_context = cast($9 as json) " \
    "FROM " #table_prefix "_option_def_server as a, " \
    "     " #table_prefix "_server as s " \
    "WHERE d.id = a.option_def_id AND " \
    "      a.server_id = s.id AND " \
    "      d.class_id = (SELECT id FROM " #table_prefix "_client_class WHERE name = $10) " \
    "      AND s.tag = $11 AND d.code = $12 AND d.space = $13"
#endif

#ifndef PGSQL_UPDATE_OPTION_NO_TAG
#define PGSQL_UPDATE_OPTION_NO_TAG(table_prefix, pd_pool_id, ...) \
    "UPDATE " #table_prefix "_options AS o " \
    "SET" \
    "  code = $1," \
    "  value = $2," \
    "  formatted_value = $3," \
    "  space = $4," \
    "  persistent = $5," \
    "  cancelled = $6," \
    "  dhcp_client_class = $7," \
    "  " #table_prefix "_subnet_id = $8," \
    "  scope_id = $9," \
    "  user_context = cast($10 as json)," \
    "  shared_network_name = $11," \
    "  pool_id = $12," \
    "  modification_ts = $13 " \
    pd_pool_id \
    "WHERE " #__VA_ARGS__

#define PGSQL_UPDATE_OPTION4_NO_TAG(...) \
    PGSQL_UPDATE_OPTION_NO_TAG(dhcp4, "", __VA_ARGS__)

#define PGSQL_UPDATE_OPTION6_NO_TAG(...) \
    PGSQL_UPDATE_OPTION_NO_TAG(dhcp6, ", pd_pool_id = $14 ", __VA_ARGS__)
#endif

#ifndef PGSQL_UPDATE_OPTION_WITH_TAG
#define PGSQL_UPDATE_OPTION_WITH_TAG(table_prefix, pd_pool_id, ...) \
    "UPDATE " #table_prefix "_options AS o " \
    "SET" \
    "  code = $1," \
    "  value = $2," \
    "  formatted_value = $3," \
    "  space = $4," \
    "  persistent = $5," \
    "  cancelled = $6," \
    "  dhcp_client_class = $7," \
    "  " #table_prefix "_subnet_id = $8," \
    "  scope_id = $9," \
    "  user_context = cast($10 as json)," \
    "  shared_network_name = $11," \
    "  pool_id = $12," \
    "  modification_ts = $13 " \
    pd_pool_id \
    "FROM " #table_prefix "_options_server as a, " \
    "     " #table_prefix "_server as s " \
    "WHERE o.option_id = a.option_id AND " \
    "      a.server_id = s.id " \
    #__VA_ARGS__

#define PGSQL_UPDATE_OPTION4_WITH_TAG(...) \
    PGSQL_UPDATE_OPTION_WITH_TAG(dhcp4, "", AND s.tag = $14 __VA_ARGS__)

#define PGSQL_UPDATE_OPTION6_WITH_TAG(...) \
    PGSQL_UPDATE_OPTION_WITH_TAG(dhcp6, \
    ", pd_pool_id = $14 ", AND s.tag = $15 __VA_ARGS__)
#endif

#ifndef PGSQL_UPDATE_CLIENT_CLASS4
#define PGSQL_UPDATE_CLIENT_CLASS4(follow_class_name_set) \
    "UPDATE dhcp4_client_class SET" \
    "  name = $1," \
    "  test = $2," \
    "  next_server = cast($3 as inet)," \
    "  server_hostname = $4," \
    "  boot_file_name = $5," \
    "  only_if_required = $6," \
    "  valid_lifetime = $7," \
    "  min_valid_lifetime = $8," \
    "  max_valid_lifetime = $9," \
    "  depend_on_known_directly = $10," \
    follow_class_name_set \
    "  modification_ts = $12, " \
    "  user_context = cast($13 as json), " \
    "  offer_lifetime = $14 " \
    "WHERE name = $15"
#endif

#ifndef PGSQL_UPDATE_CLIENT_CLASS6
#define PGSQL_UPDATE_CLIENT_CLASS6(follow_class_name_set) \
    "UPDATE dhcp6_client_class SET" \
    "  name = $1," \
    "  test = $2," \
    "  only_if_required = $3," \
    "  valid_lifetime = $4," \
    "  min_valid_lifetime = $5," \
    "  max_valid_lifetime = $6," \
    "  depend_on_known_directly = $7," \
    follow_class_name_set \
    "  preferred_lifetime = $9, " \
    "  min_preferred_lifetime = $10, " \
    "  max_preferred_lifetime = $11, " \
    "  modification_ts = $12, " \
    "  user_context = cast($13 as json) " \
    "WHERE name = $14"
#endif

#ifndef PGSQL_UPDATE_SERVER
#define PGSQL_UPDATE_SERVER(table_prefix) \
    "UPDATE " #table_prefix "_server " \
    "SET" \
    "  tag = $1," \
    "  description = $2," \
    "  modification_ts = $3 " \
    "WHERE tag = $4"
#endif

#ifndef PGSQL_DELETE_GLOBAL_PARAMETER
#define PGSQL_DELETE_GLOBAL_PARAMETER(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_global_parameter AS g " \
    "USING " \
    "   " #table_prefix "_global_parameter_server AS a, " \
    "   " #table_prefix "_server AS s " \
    "WHERE " \
    "   g.id = a.parameter_id AND " \
    "   a.server_id = s.id AND " \
    "   s.tag = $1 " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED
#define PGSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_global_parameter AS g " \
    "WHERE g.id in ( " \
    "   SELECT g.id FROM " #table_prefix "_global_parameter AS g " \
    "   LEFT JOIN " #table_prefix "_global_parameter_server AS a ON g.id = a.parameter_id " \
    "   WHERE a.parameter_id IS NULL) " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_SUBNET_COMMON
#define PGSQL_DELETE_SUBNET_COMMON(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_subnet AS s " \
    "USING " \
    "   " #table_prefix "_subnet_server AS a, " \
    "   " #table_prefix "_server AS srv " \
    "WHERE " \
    "   s.subnet_id = a.subnet_id AND " \
    "   a.server_id = srv.id " \
    #__VA_ARGS__

#define PGSQL_DELETE_SUBNET_WITH_TAG(table_prefix, ...) \
    PGSQL_DELETE_SUBNET_COMMON(table_prefix, AND srv.tag = $1 __VA_ARGS__)

#define PGSQL_DELETE_SUBNET_ANY(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_subnet AS s " \
    #__VA_ARGS__

#define PGSQL_DELETE_SUBNET_UNASSIGNED(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_subnet AS s " \
    "WHERE s.subnet_id in ( " \
    "   SELECT s.subnet_id FROM " #table_prefix "_subnet AS s " \
    "   LEFT JOIN " #table_prefix "_subnet_server AS a ON s.subnet_id = a.subnet_id " \
    "   WHERE a.subnet_id IS NULL) " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_SUBNET_SERVER
#define PGSQL_DELETE_SUBNET_SERVER(table_prefix) \
    "DELETE FROM " #table_prefix "_subnet_server " \
    "WHERE subnet_id = $1"
#endif

#ifndef PGSQL_DELETE_POOLS
#define PGSQL_DELETE_POOLS(table_prefix) \
    "DELETE FROM " #table_prefix "_pool " \
    "WHERE subnet_id = $1 OR subnet_id = " \
    "(SELECT subnet_id FROM " #table_prefix "_subnet" \
    "    WHERE subnet_prefix = $2)"
#endif

#ifndef PGSQL_DELETE_PD_POOLS
#define PGSQL_DELETE_PD_POOLS() \
    "DELETE FROM dhcp6_pd_pool " \
    "WHERE subnet_id = $1 OR subnet_id = " \
    "(SELECT subnet_id FROM dhcp6_subnet" \
    "    WHERE subnet_prefix = $2)"
#endif

#ifndef PGSQL_DELETE_SHARED_NETWORK_COMMON
#define PGSQL_DELETE_SHARED_NETWORK_COMMON(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_shared_network AS n " \
    "USING " \
    "   " #table_prefix "_shared_network_server AS a, " \
    "   " #table_prefix "_server AS s " \
    "WHERE " \
    "   n.id = a.shared_network_id AND " \
    "   a.server_id = s.id " \
    #__VA_ARGS__

#define PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(table_prefix, ...) \
    PGSQL_DELETE_SHARED_NETWORK_COMMON(table_prefix, AND s.tag = $1 __VA_ARGS__)

#define PGSQL_DELETE_SHARED_NETWORK_ANY(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_shared_network AS n " \
    #__VA_ARGS__

#define PGSQL_DELETE_SHARED_NETWORK_UNASSIGNED(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_shared_network AS n " \
    "WHERE n.id in ( " \
    "   SELECT n.id FROM " #table_prefix "_shared_network AS n " \
    "   LEFT JOIN " #table_prefix "_shared_network_server AS a ON n.id = a.shared_network_id " \
    "   WHERE a.shared_network_id IS NULL) " \
    #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_SHARED_NETWORK_SERVER
#define PGSQL_DELETE_SHARED_NETWORK_SERVER(table_prefix) \
    "DELETE FROM " #table_prefix "_shared_network_server " \
    "WHERE shared_network_id = " \
    "(SELECT id FROM " #table_prefix "_shared_network WHERE name = $1)"
#endif

#ifndef PGSQL_DELETE_OPTION_DEF
#define PGSQL_DELETE_OPTION_DEF(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_option_def AS d " \
    "USING " \
    "   " #table_prefix "_option_def_server AS a, " \
    "   " #table_prefix "_server AS s " \
    "WHERE " \
    "   d.id = a.option_def_id AND " \
    "   a.server_id = s.id AND " \
    "   s.tag = $1 " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_OPTION_DEF_UNASSIGNED
#define PGSQL_DELETE_OPTION_DEF_UNASSIGNED(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_option_def AS d " \
    "WHERE d.id in ( " \
    "   SELECT d.id FROM " #table_prefix "_option_def AS d " \
    "   LEFT JOIN " #table_prefix "_option_def_server AS a ON d.id = a.option_def_id " \
    "   WHERE a.option_def_id IS NULL) " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_OPTION_DEFS_CLIENT_CLASS
#define PGSQL_DELETE_OPTION_DEFS_CLIENT_CLASS(table_prefix) \
    "DELETE FROM " #table_prefix "_option_def " \
    "WHERE class_id = (SELECT id FROM " #table_prefix "_client_class WHERE name = $1)"
#endif

#ifndef PGSQL_DELETE_OPTION_WITH_TAG
#define PGSQL_DELETE_OPTION_WITH_TAG(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_options AS o " \
    "USING " \
    "   " #table_prefix "_options_server AS a, " \
    "   " #table_prefix "_server AS s " \
    "WHERE " \
    "   o.option_id = a.option_id AND " \
    "   a.server_id = s.id AND " \
    "   s.tag = $1 " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_OPTION_NO_TAG
#define PGSQL_DELETE_OPTION_NO_TAG(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_options AS o " \
    #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_OPTION_SUBNET_ID_PREFIX
#define PGSQL_DELETE_OPTION_SUBNET_ID_PREFIX(table_prefix) \
    "DELETE FROM " #table_prefix "_options AS o " \
    "USING " \
    "   " #table_prefix "_subnet AS s " \
    "WHERE " \
    "   s.subnet_id = o." #table_prefix "_subnet_id AND " \
    "   o.scope_id = 1 AND (s.subnet_id = $1 OR s.subnet_prefix = $2)"
#endif

#ifndef PGSQL_DELETE_OPTION_UNASSIGNED
#define PGSQL_DELETE_OPTION_UNASSIGNED(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_options AS o " \
    "WHERE o.option_id in ( " \
    "   SELECT o.option_id FROM " #table_prefix "_options AS o " \
    "   LEFT JOIN " #table_prefix "_options_server AS a ON o.option_id = a.option_id " \
    "   WHERE a.option_id IS NULL) " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_OPTION_POOL_RANGE
#define PGSQL_DELETE_OPTION_POOL_RANGE(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_options AS o " \
    "WHERE " #__VA_ARGS__ \
    "  AND o.pool_id = " \
    "  (SELECT id FROM " #table_prefix "_pool" \
    "   WHERE start_address = cast($1 as inet) AND end_address = cast($2 as inet))"
#endif

#ifndef PGSQL_DELETE_OPTION_PD_POOL
#define PGSQL_DELETE_OPTION_PD_POOL(...) \
    "DELETE FROM dhcp6_options AS o " \
    "WHERE " #__VA_ARGS__ \
    "  AND o.pd_pool_id = " \
    "  (SELECT id FROM dhcp6_pd_pool" \
    "   WHERE prefix = $1 AND prefix_length = $2)"
#endif

#ifndef PGSQL_DELETE_CLIENT_CLASS_DEPENDENCY
#define PGSQL_DELETE_CLIENT_CLASS_DEPENDENCY(table_prefix) \
    "DELETE FROM " #table_prefix "_client_class_dependency " \
    "WHERE class_id = (SELECT id FROM " #table_prefix "_client_class WHERE name = $1)"
#endif

#ifndef PGSQL_DELETE_CLIENT_CLASS_SERVER
#define PGSQL_DELETE_CLIENT_CLASS_SERVER(table_prefix) \
    "DELETE FROM " #table_prefix "_client_class_server " \
    "WHERE class_id = " \
    "(SELECT id FROM " #table_prefix "_client_class WHERE name = $1)"
#endif

#ifndef PGSQL_DELETE_CLIENT_CLASS_COMMON
#define PGSQL_DELETE_CLIENT_CLASS_COMMON(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_client_class AS c " \
    "USING " \
    "   " #table_prefix "_client_class_server AS a, " \
    "   " #table_prefix "_server AS s " \
    "WHERE " \
    "  c.id = a.class_id AND " \
    "  a.server_id = s.id " \
    #__VA_ARGS__

#define PGSQL_DELETE_CLIENT_CLASS_WITH_TAG(table_prefix, ...) \
    PGSQL_DELETE_CLIENT_CLASS_COMMON(table_prefix, AND s.tag = $1 __VA_ARGS__)

#define PGSQL_DELETE_CLIENT_CLASS_ANY(table_prefix, ...) \
    PGSQL_DELETE_CLIENT_CLASS_COMMON(table_prefix, __VA_ARGS__)

#define PGSQL_DELETE_CLIENT_CLASS_UNASSIGNED(table_prefix, ...) \
    "DELETE FROM " #table_prefix "_client_class AS c " \
    "WHERE c.id in (" \
    "   SELECT c.id FROM " #table_prefix "_client_class AS c " \
    "   LEFT JOIN " #table_prefix "_client_class_server AS a ON c.id = a.class_id " \
    "   WHERE a.class_id IS NULL) " #__VA_ARGS__
#endif

#ifndef PGSQL_DELETE_SERVER
#define PGSQL_DELETE_SERVER(table_prefix) \
    "DELETE FROM " #table_prefix "_server " \
    "WHERE tag = $1"
#endif

#ifndef PGSQL_DELETE_ALL_SERVERS
#define PGSQL_DELETE_ALL_SERVERS(table_prefix) \
    "DELETE FROM " #table_prefix "_server " \
    "WHERE id > 1"
#endif

} // end of anonymous namespace

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
