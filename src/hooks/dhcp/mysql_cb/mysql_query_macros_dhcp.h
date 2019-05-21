// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_QUERY_MACROS_DHCP_H
#define MYSQL_QUERY_MACROS_DHCP_H

/// @file mysql_query_macros_dhcp.h
/// Collection of common macros defining MySQL prepared statements used
/// to manage Kea DHCP configuration in the database.
///
/// Some of the macros are DHCPv4 specific, other are DHCPv6 specific.
/// Some macros are common for both DHCP server types. The first
/// parameter @c table_prefix should be set to @c dhcp4 or @c dhcp6,
/// depending which DHCP server type it relates to. Provided value
/// is used as a prefix for MySQL table names. For example, if the
/// prefix is set to @c dhcp4, the table name referred to in the
/// query may be dhcp4_subnet etc. The second argument in the variadic
/// macro is a part of the WHERE clause in the MySQL query. The fixed
/// part of the WHERE clause is included in the macro.

/// @todo Update queries to also fetch server tags to associate
/// returned configuration elements with particular servers.

namespace isc {
namespace dhcp {

namespace {

#ifndef MYSQL_GET_GLOBAL_PARAMETER
#define MYSQL_GET_GLOBAL_PARAMETER(table_prefix, ...) \
    "SELECT" \
    "  g.id," \
    "  g.name," \
    "  g.value," \
    "  g.parameter_type," \
    "  g.modification_ts," \
    "  s.tag " \
    "FROM " #table_prefix "_global_parameter AS g " \
    "INNER JOIN " #table_prefix "_global_parameter_server AS a " \
    "  ON g.id = a.parameter_id " \
    "INNER JOIN " #table_prefix "_server AS s " \
    "  ON (a.server_id = s.id) OR (a.server_id = 1) " \
    "WHERE (s.tag = ? OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY g.id"

#endif

#ifndef MYSQL_GET_SUBNET4
#define MYSQL_GET_SUBNET4(...) \
    "SELECT" \
    "  s.subnet_id," \
    "  s.subnet_prefix," \
    "  s.4o6_interface," \
    "  s.4o6_interface_id," \
    "  s.4o6_subnet," \
    "  s.boot_file_name," \
    "  s.client_class," \
    "  s.interface," \
    "  s.match_client_id," \
    "  s.modification_ts," \
    "  s.next_server," \
    "  s.rebind_timer," \
    "  s.relay," \
    "  s.renew_timer," \
    "  s.require_client_classes," \
    "  s.reservation_mode," \
    "  s.server_hostname," \
    "  s.shared_network_name," \
    "  s.user_context," \
    "  s.valid_lifetime," \
    "  p.id," \
    "  p.start_address," \
    "  p.end_address," \
    "  p.subnet_id," \
    "  p.modification_ts," \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.dhcp4_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  x.modification_ts," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.dhcp4_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  o.modification_ts," \
    "  s.calculate_tee_times," \
    "  s.t1_percent," \
    "  s.t2_percent," \
    "  s.authoritative," \
    "  s.min_valid_lifetime," \
    "  s.max_valid_lifetime," \
    "  srv.tag " \
    "FROM dhcp4_subnet AS s " \
    "INNER JOIN dhcp4_subnet_server AS a " \
    "  ON s.subnet_id = a.subnet_id " \
    "INNER JOIN dhcp4_server AS srv " \
    "  ON (a.server_id = srv.id) OR (a.server_id = 1) " \
    "LEFT JOIN dhcp4_pool AS p ON s.subnet_id = p.subnet_id " \
    "LEFT JOIN dhcp4_options AS x ON x.scope_id = 5 AND p.id = x.pool_id " \
    "LEFT JOIN dhcp4_options AS o ON o.scope_id = 1 AND s.subnet_id = o.dhcp4_subnet_id " \
    "WHERE (srv.tag = ? OR srv.id = 1) " #__VA_ARGS__ \
    " ORDER BY s.subnet_id, p.id, x.option_id, o.option_id"
#endif

#ifndef MYSQL_GET_SUBNET6
#define MYSQL_GET_SUBNET6(...) \
    "SELECT" \
    "  s.subnet_id," \
    "  s.subnet_prefix," \
    "  s.client_class," \
    "  s.interface," \
    "  s.modification_ts," \
    "  s.preferred_lifetime," \
    "  s.rapid_commit," \
    "  s.rebind_timer," \
    "  s.relay," \
    "  s.renew_timer," \
    "  s.require_client_classes," \
    "  s.reservation_mode," \
    "  s.shared_network_name," \
    "  s.user_context," \
    "  s.valid_lifetime," \
    "  p.id," \
    "  p.start_address," \
    "  p.end_address," \
    "  p.subnet_id," \
    "  p.modification_ts," \
    "  d.id," \
    "  d.prefix," \
    "  d.prefix_length," \
    "  d.delegated_prefix_length," \
    "  d.subnet_id," \
    "  d.modification_ts," \
    "  x.option_id," \
    "  x.code," \
    "  x.value," \
    "  x.formatted_value," \
    "  x.space," \
    "  x.persistent," \
    "  x.dhcp6_subnet_id," \
    "  x.scope_id," \
    "  x.user_context," \
    "  x.shared_network_name," \
    "  x.pool_id," \
    "  x.modification_ts," \
    "  x.pd_pool_id," \
    "  y.option_id," \
    "  y.code," \
    "  y.value," \
    "  y.formatted_value," \
    "  y.space," \
    "  y.persistent," \
    "  y.dhcp6_subnet_id," \
    "  y.scope_id," \
    "  y.user_context," \
    "  y.shared_network_name," \
    "  y.pool_id," \
    "  y.modification_ts," \
    "  y.pd_pool_id," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.dhcp6_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  o.modification_ts," \
    "  o.pd_pool_id, " \
    "  s.calculate_tee_times," \
    "  s.t1_percent," \
    "  s.t2_percent," \
    "  s.interface_id," \
    "  s.min_preferred_lifetime," \
    "  s.max_preferred_lifetime," \
    "  s.min_valid_lifetime," \
    "  s.max_valid_lifetime," \
    "  srv.tag " \
    "FROM dhcp6_subnet AS s " \
    "INNER JOIN dhcp6_subnet_server AS a " \
    "  ON s.subnet_id = a.subnet_id " \
    "INNER JOIN dhcp6_server AS srv " \
    "  ON (a.server_id = srv.id) OR (a.server_id = 1) " \
    "LEFT JOIN dhcp6_pool AS p ON s.subnet_id = p.subnet_id " \
    "LEFT JOIN dhcp6_pd_pool AS d ON s.subnet_id = d.subnet_id " \
    "LEFT JOIN dhcp6_options AS x ON x.scope_id = 5 AND p.id = x.pool_id " \
    "LEFT JOIN dhcp6_options AS y ON y.scope_id = 6 AND d.id = y.pd_pool_id " \
    "LEFT JOIN dhcp6_options AS o ON o.scope_id = 1 AND s.subnet_id = o.dhcp6_subnet_id " \
    "WHERE (srv.tag = ? OR srv.id = 1) " #__VA_ARGS__ \
    " ORDER BY s.subnet_id, p.id, d.id, x.option_id, o.option_id"
#endif

#ifndef MYSQL_GET_SHARED_NETWORK4
#define MYSQL_GET_SHARED_NETWORK4(...) \
    "SELECT" \
    "  n.id," \
    "  n.name," \
    "  n.client_class," \
    "  n.interface," \
    "  n.match_client_id," \
    "  n.modification_ts," \
    "  n.rebind_timer," \
    "  n.relay," \
    "  n.renew_timer," \
    "  n.require_client_classes," \
    "  n.reservation_mode," \
    "  n.user_context," \
    "  n.valid_lifetime," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.dhcp4_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  o.modification_ts," \
    "  n.calculate_tee_times," \
    "  n.t1_percent," \
    "  n.t2_percent," \
    "  n.authoritative," \
    "  n.boot_file_name," \
    "  n.next_server," \
    "  n.server_hostname," \
    "  n.min_valid_lifetime," \
    "  n.max_valid_lifetime," \
    "  s.tag " \
    "FROM dhcp4_shared_network AS n " \
    "INNER JOIN dhcp4_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "INNER JOIN dhcp4_server AS s " \
    "  ON (a.server_id = s.id) OR (a.server_id = 1) " \
    "LEFT JOIN dhcp4_options AS o ON o.scope_id = 4 AND n.name = o.shared_network_name " \
    "WHERE (s.tag = ? OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY n.id, o.option_id"
#endif

#ifndef MYSQL_GET_SHARED_NETWORK6
#define MYSQL_GET_SHARED_NETWORK6(...) \
    "SELECT" \
    "  n.id," \
    "  n.name," \
    "  n.client_class," \
    "  n.interface," \
    "  n.modification_ts," \
    "  n.preferred_lifetime," \
    "  n.rapid_commit," \
    "  n.rebind_timer," \
    "  n.relay," \
    "  n.renew_timer," \
    "  n.require_client_classes," \
    "  n.reservation_mode," \
    "  n.user_context," \
    "  n.valid_lifetime," \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o.dhcp6_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  o.modification_ts," \
    "  o.pd_pool_id, " \
    "  n.calculate_tee_times," \
    "  n.t1_percent," \
    "  n.t2_percent," \
    "  n.interface_id," \
    "  n.min_preferred_lifetime," \
    "  n.max_preferred_lifetime," \
    "  n.min_valid_lifetime," \
    "  n.max_valid_lifetime," \
    "  s.tag " \
    "FROM dhcp6_shared_network AS n " \
    "INNER JOIN dhcp6_shared_network_server AS a " \
    "  ON n.id = a.shared_network_id " \
    "INNER JOIN dhcp6_server AS s " \
    "  ON (a.server_id = s.id) OR (a.server_id = 1) " \
    "LEFT JOIN dhcp6_options AS o ON o.scope_id = 4 AND n.name = o.shared_network_name " \
    "WHERE (s.tag = ? OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY n.id, o.option_id"
#endif

#ifndef MYSQL_GET_OPTION_DEF
#define MYSQL_GET_OPTION_DEF(table_prefix, ...) \
    "SELECT" \
    "  d.id," \
    "  d.code," \
    "  d.name," \
    "  d.space," \
    "  d.type," \
    "  d.modification_ts," \
    "  d.array," \
    "  d.encapsulate," \
    "  d.record_types," \
    "  d.user_context," \
    "  s.tag " \
    "FROM " #table_prefix "_option_def AS d " \
    "INNER JOIN " #table_prefix "_option_def_server AS a" \
    "  ON d.id = a.option_def_id " \
    "INNER JOIN " #table_prefix "_server AS s " \
    "  ON (a.server_id = s.id) OR (a.server_id = 1) " \
    "WHERE (s.tag = ? OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY d.id"
#endif

#ifndef MYSQL_GET_OPTION_COMMON
#define MYSQL_GET_OPTION_COMMON(table_prefix, pd_pool_id, ...) \
    "SELECT" \
    "  o.option_id," \
    "  o.code," \
    "  o.value," \
    "  o.formatted_value," \
    "  o.space," \
    "  o.persistent," \
    "  o." #table_prefix "_subnet_id," \
    "  o.scope_id," \
    "  o.user_context," \
    "  o.shared_network_name," \
    "  o.pool_id," \
    "  o.modification_ts," \
    "  s.tag " \
    pd_pool_id \
    "FROM " #table_prefix "_options AS o " \
    "INNER JOIN " #table_prefix "_options_server AS a" \
    "  ON o.option_id = a.option_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE (s.tag = ? OR s.id = 1) " #__VA_ARGS__ \
    " ORDER BY o.option_id"

#define MYSQL_GET_OPTION4(...) \
    MYSQL_GET_OPTION_COMMON(dhcp4, "", __VA_ARGS__)
#define MYSQL_GET_OPTION6(...) \
    MYSQL_GET_OPTION_COMMON(dhcp6, ", o.pd_pool_id ", __VA_ARGS__)
#endif

#ifndef MYSQL_GET_AUDIT_ENTRIES_TIME
#define MYSQL_GET_AUDIT_ENTRIES_TIME(table_prefix) \
    "SELECT" \
    "  a.id," \
    "  a.object_type," \
    "  a.object_id," \
    "  a.modification_type," \
    "  r.modification_ts," \
    "  r.log_message " \
    "FROM " #table_prefix "_audit AS a " \
    "INNER JOIN " #table_prefix "_audit_revision AS r " \
    "  ON a.revision_id = r.id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON r.server_id = s.id " \
    "WHERE (s.tag = ? OR s.id = 1) AND (r.modification_ts > ?) " \
    "ORDER BY r.modification_ts, r.id"
#endif

#ifndef MYSQL_INSERT_GLOBAL_PARAMETER
#define MYSQL_INSERT_GLOBAL_PARAMETER(table_prefix) \
    "INSERT INTO " #table_prefix "_global_parameter(" \
    "  name," \
    "  value," \
    "  parameter_type," \
    "  modification_ts" \
    ") VALUES (?, ?, ?, ?)"
#endif

#ifndef MYSQL_INSERT_GLOBAL_PARAMETER_SERVER
#define MYSQL_INSERT_GLOBAL_PARAMETER_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_global_parameter_server(" \
    "  parameter_id," \
    "  server_id," \
    "  modification_ts" \
    ") VALUES (?, (SELECT id FROM " #table_prefix "_server WHERE tag = ?), ?)"
#endif

#ifndef MYSQL_INSERT_SUBNET_SERVER
#define MYSQL_INSERT_SUBNET_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_subnet_server(" \
    "  subnet_id," \
    "  server_id," \
    "  modification_ts" \
    ") VALUES (?, (SELECT id FROM " #table_prefix "_server WHERE tag = ?), ?)"
#endif

#ifndef MYSQL_INSERT_POOL
#define MYSQL_INSERT_POOL(table_prefix) \
    "INSERT INTO " #table_prefix "_pool(" \
    "  start_address," \
    "  end_address," \
    "  subnet_id," \
    "  modification_ts" \
    ") VALUES (?, ?, ?, ?)"
#endif

#ifndef MYSQL_INSERT_PD_POOL
#define MYSQL_INSERT_PD_POOL() \
    "INSERT INTO dhcp6_pd_pool(" \
    "  prefix," \
    "  prefix_length," \
    "  delegated_prefix_length," \
    "  subnet_id," \
    "  modification_ts" \
    ") VALUES (?, ?, ?, ?, ?)"
#endif

#ifndef MYSQL_INSERT_SHARED_NETWORK_SERVER
#define MYSQL_INSERT_SHARED_NETWORK_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_shared_network_server(" \
    "  shared_network_id," \
    "  server_id," \
    "  modification_ts" \
    ") VALUES (" \
    "    (SELECT id FROM " #table_prefix "_shared_network WHERE name = ?)," \
    "    (SELECT id FROM " #table_prefix "_server WHERE tag = ?), ?" \
    ")"
#endif

#ifndef MYSQL_INSERT_OPTION_DEF
#define MYSQL_INSERT_OPTION_DEF(table_prefix) \
    "INSERT INTO " #table_prefix "_option_def (" \
    "  code," \
    "  name," \
    "  space," \
    "  type," \
    "  modification_ts," \
    "  array," \
    "  encapsulate," \
    "  record_types," \
    "  user_context" \
    ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"
#endif

#ifndef MYSQL_INSERT_OPTION_DEF_SERVER
#define MYSQL_INSERT_OPTION_DEF_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_option_def_server(" \
    "  option_def_id," \
    "  server_id," \
    "  modification_ts" \
    ") VALUES (?, (SELECT id FROM " #table_prefix "_server WHERE tag = ?), ?)"
#endif

#ifndef MYSQL_INSERT_OPTION_COMMON
#define MYSQL_INSERT_OPTION_COMMON(table_prefix, pd_pool_id, last) \
    "INSERT INTO " #table_prefix "_options (" \
    "  code," \
    "  value," \
    "  formatted_value," \
    "  space," \
    "  persistent," \
    "  dhcp_client_class," \
    " " #table_prefix "_subnet_id," \
    "  scope_id," \
    "  user_context," \
    "  shared_network_name," \
    "  pool_id," \
    "  modification_ts" \
    pd_pool_id \
    ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?" last ")"

#define MYSQL_INSERT_OPTION4() \
    MYSQL_INSERT_OPTION_COMMON(dhcp4, "", "")
#define MYSQL_INSERT_OPTION6() \
    MYSQL_INSERT_OPTION_COMMON(dhcp6, ", pd_pool_id ", ", ?")
#endif

#ifndef MYSQL_INSERT_OPTION_SERVER
#define MYSQL_INSERT_OPTION_SERVER(table_prefix) \
    "INSERT INTO " #table_prefix "_options_server (" \
    "  option_id," \
    "  server_id," \
    "  modification_ts" \
    ") VALUES (?, (SELECT id FROM " #table_prefix "_server WHERE tag = ?), ?)"
#endif

#ifndef MYSQL_UPDATE_GLOBAL_PARAMETER
#define MYSQL_UPDATE_GLOBAL_PARAMETER(table_prefix) \
    "UPDATE " #table_prefix "_global_parameter AS g " \
    "INNER JOIN " #table_prefix "_global_parameter_server AS a" \
    "  ON g.id = a.parameter_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "SET" \
    "  g.name = ?," \
    "  g.value = ?," \
    "  g.parameter_type = ?," \
    "  g.modification_ts = ? " \
    "WHERE s.tag = ? AND g.name = ?"
#endif

#ifndef MYSQL_UPDATE_OPTION_DEF
#define MYSQL_UPDATE_OPTION_DEF(table_prefix) \
    "UPDATE " #table_prefix "_option_def AS d " \
    "INNER JOIN " #table_prefix "_option_def_server AS a" \
    "  ON d.id = a.option_def_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "SET" \
    "  d.code = ?," \
    "  d.name = ?," \
    "  d.space = ?," \
    "  d.type = ?," \
    "  d.modification_ts = ?," \
    "  d.array = ?," \
    "  d.encapsulate = ?," \
    "  d.record_types = ?," \
    "  d.user_context = ? " \
    "WHERE s.tag = ? AND d.code = ? AND d.space = ?"
#endif

#ifndef MYSQL_UPDATE_OPTION_COMMON
#define MYSQL_UPDATE_OPTION_COMMON(table_prefix, pd_pool_id, ...) \
    "UPDATE " #table_prefix "_options AS o " \
    "INNER JOIN " #table_prefix "_options_server AS a" \
    "  ON o.option_id = a.option_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "SET" \
    "  o.code = ?," \
    "  o.value = ?," \
    "  o.formatted_value = ?," \
    "  o.space = ?," \
    "  o.persistent = ?," \
    "  o.dhcp_client_class = ?," \
    "  o." #table_prefix "_subnet_id = ?," \
    "  o.scope_id = ?," \
    "  o.user_context = ?," \
    "  o.shared_network_name = ?," \
    "  o.pool_id = ?," \
    "  o.modification_ts = ? " \
    pd_pool_id \
    "WHERE s.tag = ? " #__VA_ARGS__

#define MYSQL_UPDATE_OPTION4(...) \
    MYSQL_UPDATE_OPTION_COMMON(dhcp4, "", __VA_ARGS__)
#define MYSQL_UPDATE_OPTION6(...) \
    MYSQL_UPDATE_OPTION_COMMON(dhcp6, ", o.pd_pool_id = ? ", __VA_ARGS__)
#endif

#ifndef MYSQL_DELETE_GLOBAL_PARAMETER
#define MYSQL_DELETE_GLOBAL_PARAMETER(table_prefix, ...) \
    "DELETE g FROM " #table_prefix "_global_parameter AS g " \
    "INNER JOIN " #table_prefix "_global_parameter_server AS a " \
    "  ON g.id = a.parameter_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON (a.server_id = s.id) " \
    "WHERE s.tag = ? " #__VA_ARGS__
#endif

#ifndef MYSQL_DELETE_SUBNET
#define MYSQL_DELETE_SUBNET(table_prefix, ...) \
    "DELETE s FROM " #table_prefix "_subnet AS s " \
    "INNER JOIN " #table_prefix "_subnet_server AS a " \
    "  ON s.subnet_id = a.subnet_id " \
    "INNER JOIN " #table_prefix "_server AS srv" \
    "  ON a.server_id = srv.id " \
    "WHERE srv.tag = ? " #__VA_ARGS__
#endif

#ifndef MYSQL_DELETE_POOLS
#define MYSQL_DELETE_POOLS(table_prefix) \
    "DELETE FROM " #table_prefix "_pool " \
    "WHERE subnet_id = ?"
#endif

#ifndef MYSQL_DELETE_PD_POOLS
#define MYSQL_DELETE_PD_POOLS() \
    "DELETE FROM dhcp6_pd_pool " \
    "WHERE subnet_id = ?"
#endif

#ifndef MYSQL_DELETE_SHARED_NETWORK
#define MYSQL_DELETE_SHARED_NETWORK(table_prefix, ...) \
    "DELETE n FROM " #table_prefix "_shared_network AS n " \
    "INNER JOIN " #table_prefix "_shared_network_server AS a" \
    "  ON n.id = a.shared_network_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE s.tag = ? " #__VA_ARGS__
#endif

#ifndef MYSQL_DELETE_OPTION_DEF
#define MYSQL_DELETE_OPTION_DEF(table_prefix, ...) \
    "DELETE d FROM " #table_prefix "_option_def AS d " \
    "INNER JOIN " #table_prefix "_option_def_server AS a" \
    "  ON d.id = a.option_def_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE s.tag = ? " #__VA_ARGS__
#endif

#ifndef MYSQL_DELETE_OPTION
#define MYSQL_DELETE_OPTION(table_prefix, ...) \
    "DELETE o FROM " #table_prefix "_options AS o " \
    "INNER JOIN " #table_prefix "_options_server AS a" \
    "  ON o.option_id = a.option_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE s.tag = ? " #__VA_ARGS__
#endif

#ifndef MYSQL_DELETE_OPTION_POOL_RANGE
#define MYSQL_DELETE_OPTION_POOL_RANGE(table_prefix, ...) \
    "DELETE o FROM " #table_prefix "_options AS o " \
    "INNER JOIN " #table_prefix "_options_server AS a" \
    "  ON o.option_id = a.option_id " \
    "INNER JOIN " #table_prefix "_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE s.tag = ? " #__VA_ARGS__ \
    "  AND o.pool_id = " \
    "  (SELECT id FROM " #table_prefix "_pool" \
    "   WHERE start_address = ? AND end_address = ?)"
#endif

#ifndef MYSQL_DELETE_OPTION_PD_POOL
#define MYSQL_DELETE_OPTION_PD_POOL(...) \
    "DELETE o FROM dhcp6_options AS o " \
    "INNER JOIN dhcp6_options_server AS a" \
    "  ON o.option_id = a.option_id " \
    "INNER JOIN dhcp6_server AS s" \
    "  ON a.server_id = s.id " \
    "WHERE s.tag = ? " #__VA_ARGS__ \
    "  AND o.pd_pool_id = " \
    "  (SELECT id FROM dhcp6_pd_pool" \
    "   WHERE prefix = ? AND prefix_length = ?)"
#endif

} // end of anonymous namespace

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
