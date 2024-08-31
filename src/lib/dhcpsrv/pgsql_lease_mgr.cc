// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/pgsql_lease_mgr.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/multi_threading_mgr.h>

#include <boost/make_shared.hpp>
#include <boost/static_assert.hpp>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Catalog of all the SQL statements currently supported.  Note
/// that the order columns appear in statement body must match the order they
/// that the occur in the table.  This does not apply to the where clause.
PgSqlTaggedStatement tagged_statements[] = {
    // DELETE_LEASE4
    { 2, { OID_INT8, OID_TIMESTAMP },
      "delete_lease4",
      "DELETE FROM lease4 WHERE address = $1 AND expire = $2" },

    // DELETE_LEASE4_STATE_EXPIRED
    { 2, { OID_INT8, OID_TIMESTAMP },
      "delete_lease4_state_expired",
      "DELETE FROM lease4 "
          "WHERE state = $1 AND expire < $2" },

    // DELETE_LEASE6
    { 2, { OID_VARCHAR, OID_TIMESTAMP },
      "delete_lease6",
      "DELETE FROM lease6 WHERE address = cast($1 as inet) AND expire = $2"},

    // DELETE_LEASE6_STATE_EXPIRED
    { 2, { OID_INT8, OID_TIMESTAMP },
      "delete_lease6_state_expired",
      "DELETE FROM lease6 "
          "WHERE state = $1 AND expire < $2" },

    // GET_LEASE4
    { 0, { OID_NONE },
      "get_lease4",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4" },

    // GET_LEASE4_ADDR
    { 1, { OID_INT8 },
      "get_lease4_addr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE address = $1" },

    // GET_LEASE4_CLIENTID
    { 1, { OID_BYTEA },
      "get_lease4_clientid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE client_id = $1" },

    // GET_LEASE4_CLIENTID_SUBID
    { 2, { OID_BYTEA, OID_INT8 },
      "get_lease4_clientid_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE client_id = $1 AND subnet_id = $2" },

    // GET_LEASE4_HWADDR
    { 1, { OID_BYTEA },
      "get_lease4_hwaddr",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE hwaddr = $1" },

    // GET_LEASE4_HWADDR_SUBID
    { 2, { OID_BYTEA, OID_INT8 },
      "get_lease4_hwaddr_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE hwaddr = $1 AND subnet_id = $2" },

    // GET_LEASE4_PAGE
    { 2, { OID_INT8, OID_INT8 },
      "get_lease4_page",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE address > $1 "
      "ORDER BY address "
      "LIMIT $2" },

    // GET_LEASE4_UCTX_PAGE
    { 2, { OID_INT8, OID_INT8 },
      "get_lease4_uctx_page",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE address > $1 AND user_context IS NOT NULL "
      "ORDER BY address "
      "LIMIT $2" },

    // GET_LEASE4_SUBID
    { 1, { OID_INT8 },
      "get_lease4_subid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
      "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE subnet_id = $1" },

    // GET_LEASE4_HOSTNAME
    { 1, { OID_VARCHAR },
      "get_lease4_hostname",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
      "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE lower(hostname) = $1" },

    // GET_LEASE4_EXPIRE
    { 3, { OID_INT8, OID_TIMESTAMP, OID_INT8 },
      "get_lease4_expire",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE state != $1 AND valid_lifetime != 4294967295 AND expire < $2 "
      "ORDER BY expire "
      "LIMIT $3" },

    // GET_LEASE4_RELAYID
    { 3, { OID_BYTEA, OID_INT8, OID_INT8 },
      "get_lease4_relayid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE relay_id = $1 and address > $2 "
      "ORDER BY address "
      "LIMIT $3" },

    // GET_LEASE4_RELAYID_QST
    { 4, { OID_BYTEA, OID_INT8, OID_INT8, OID_INT8 },
      "get_lease4_relayid_qst",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE relay_id = $1 and address > $2 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) >= $3 "
      "ORDER BY address "
      "LIMIT $4" },

    // GET_LEASE4_RELAYID_QSET
    { 5, { OID_BYTEA, OID_INT8, OID_INT8, OID_INT8, OID_INT8 },
      "get_lease4_relayid_qset",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE relay_id = $1 and address > $2 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) >= $3 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) <= $4 "
      "ORDER BY address "
      "LIMIT $5" },

    // GET_LEASE4_RELAYID_QET
    { 4, { OID_BYTEA, OID_INT8, OID_INT8, OID_INT8 },
      "get_lease4_relayid_qet",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE relay_id = $1 and address > $2 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) <= $3 "
      "ORDER BY address "
      "LIMIT $4" },

    // GET_LEASE4_REMOTEID
    { 3, { OID_BYTEA, OID_INT8, OID_INT8 },
      "get_lease4_remoteid",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE remote_id = $1 and address > $2 "
      "ORDER BY address "
      "LIMIT $3" },

    // GET_LEASE4_REMOTEID_QST
    { 4, { OID_BYTEA, OID_INT8, OID_INT8, OID_INT8 },
      "get_lease4_remoteid_qst",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE remote_id = $1 and address > $2 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) >= $3 "
      "ORDER BY address "
      "LIMIT $4" },

    // GET_LEASE4_REMOTEID_QSET
    { 5, { OID_BYTEA, OID_INT8, OID_INT8, OID_INT8, OID_INT8 },
      "get_lease4_remoteid_qset",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE remote_id = $1 and address > $2 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) >= $3 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) <= $4 "
      "ORDER BY address "
      "LIMIT $5" },

    // GET_LEASE4_REMOTEID_QET
    { 4, { OID_BYTEA, OID_INT8, OID_INT8, OID_INT8 },
      "get_lease4_remoteid_qet",
      "SELECT address, hwaddr, client_id, "
        "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id "
      "FROM lease4 "
      "WHERE remote_id = $1 and address > $2 "
      "and EXTRACT(EPOCH FROM expire) - (CASE valid_lifetime WHEN 4294967295 "
       "THEN 0 ELSE valid_lifetime END) <= $3 "
      "ORDER BY address "
      "LIMIT $4" },

    // GET_LEASE6
    { 0, { OID_NONE },
      "get_lease6",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "ORDER BY address "},

    // GET_LEASE6_ADDR
    { 2, { OID_VARCHAR, OID_INT2 },
      "get_lease6_addr",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE address = cast($1 as inet) AND lease_type = $2"},

    // GET_LEASE6_DUID_IAID
    { 3, { OID_BYTEA, OID_INT8, OID_INT2 },
      "get_lease6_duid_iaid",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE duid = $1 AND iaid = $2 AND lease_type = $3" },

    // GET_LEASE6_DUID_IAID_SUBID
    { 4, { OID_INT2, OID_BYTEA, OID_INT8, OID_INT8 },
      "get_lease6_duid_iaid_subid",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE lease_type = $1 "
        "AND duid = $2 AND iaid = $3 AND subnet_id = $4" },

    // GET_LEASE6_PAGE
    { 2, { OID_VARCHAR, OID_INT8 },
      "get_lease6_page",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE address > cast($1 as inet) "
      "ORDER BY address "
      "LIMIT $2"},

    // GET_LEASE6_UCTX_PAGE
    { 2, { OID_VARCHAR, OID_INT8 },
      "get_lease6_uctx_page",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE address > cast($1 as inet) AND user_context IS NOT NULL "
      "ORDER BY address "
      "LIMIT $2" },

    // GET_LEASE6_SUBID
    { 1, { OID_INT8 },
      "get_lease6_subid",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE subnet_id = $1" },

    // GET_LEASE6_SUBID_PAGE
    { 3, { OID_INT8, OID_VARCHAR, OID_INT8 },
      "get_lease6_subid_page",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE subnet_id = $1 AND address > cast($2 as inet) "
      "ORDER BY address "
      "LIMIT $3" },

    // GET_LEASE6_DUID
    { 1, { OID_BYTEA },
      "get_lease6_duid",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE duid = $1" },

    // GET_LEASE6_HOSTNAME
    { 1, { OID_VARCHAR },
      "get_lease6_hostname",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE lower(hostname) = $1" },

    // GET_LEASE6_EXPIRE
    { 3, { OID_INT8, OID_TIMESTAMP, OID_INT8 },
      "get_lease6_expire",
      "SELECT host(address), duid, valid_lifetime, "
        "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, "
        "fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id "
      "FROM lease6 "
      "WHERE state != $1 AND valid_lifetime != 4294967295 AND expire < $2 "
      "ORDER BY expire "
      "LIMIT $3" },

    // INSERT_LEASE4
    { 14, { OID_INT8, OID_BYTEA, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8,
            OID_BOOL, OID_BOOL, OID_VARCHAR, OID_INT8, OID_TEXT, OID_BYTEA,
            OID_BYTEA, OID_INT8 },
      "insert_lease4",
      "INSERT INTO lease4(address, hwaddr, client_id, "
        "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname, "
        "state, user_context, relay_id, remote_id, pool_id) "
      "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14)" },

    // INSERT_LEASE6
    { 18, { OID_VARCHAR, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8,
            OID_INT8, OID_INT2, OID_INT8, OID_INT2, OID_BOOL, OID_BOOL,
            OID_VARCHAR, OID_BYTEA, OID_INT2, OID_INT2, OID_INT8, OID_TEXT,
            OID_INT8},
      "insert_lease6",
      "INSERT INTO lease6(address, duid, valid_lifetime, "
        "expire, subnet_id, pref_lifetime, "
        "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname, "
        "hwaddr, hwtype, hwaddr_source, "
        "state, user_context, pool_id) "
      "VALUES (cast($1 as inet), $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18)" },

    // UPDATE_LEASE4
    { 16, { OID_INT8, OID_BYTEA, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8,
            OID_BOOL, OID_BOOL, OID_VARCHAR, OID_INT8, OID_TEXT, OID_BYTEA,
            OID_BYTEA, OID_INT8, OID_INT8, OID_TIMESTAMP },
      "update_lease4",
      "UPDATE lease4 SET address = $1, hwaddr = $2, "
        "client_id = $3, valid_lifetime = $4, expire = $5, "
        "subnet_id = $6, fqdn_fwd = $7, fqdn_rev = $8, hostname = $9, "
        "state = $10, user_context = $11, relay_id = $12, remote_id = $13, pool_id = $14 "
      "WHERE address = $15 AND expire = $16" },

    // UPDATE_LEASE6
    { 20, { OID_VARCHAR, OID_BYTEA, OID_INT8, OID_TIMESTAMP, OID_INT8, OID_INT8,
            OID_INT2, OID_INT8, OID_INT2, OID_BOOL, OID_BOOL, OID_VARCHAR,
            OID_BYTEA, OID_INT2, OID_INT2,
            OID_INT8, OID_TEXT, OID_INT8, OID_VARCHAR, OID_TIMESTAMP },
      "update_lease6",
      "UPDATE lease6 SET address = cast($1 as inet), duid = $2, "
        "valid_lifetime = $3, expire = $4, subnet_id = $5, "
        "pref_lifetime = $6, lease_type = $7, iaid = $8, "
        "prefix_len = $9, fqdn_fwd = $10, fqdn_rev = $11, hostname = $12, "
        "hwaddr = $13, hwtype = $14, hwaddr_source = $15, "
        "state = $16, user_context = $17, pool_id = $18 "
      "WHERE address = cast($19 as inet) AND expire = $20" },

    // ALL_LEASE4_STATS
    { 0, { OID_NONE },
      "all_lease4_stats",
      "SELECT subnet_id, state, leases as state_count"
      "  FROM lease4_stat ORDER BY subnet_id, state" },

    // SUBNET_LEASE4_STATS
    { 1, { OID_INT8 },
      "subnet_lease4_stats",
      "SELECT subnet_id, state, leases as state_count"
      "  FROM lease4_stat "
      "  WHERE subnet_id = $1 "
      "  ORDER BY state" },

    // SUBNET_RANGE_LEASE4_STATS
    { 2, { OID_INT8, OID_INT8 },
      "subnet_range_lease4_stats",
      "SELECT subnet_id, state, leases as state_count"
      "  FROM lease4_stat "
      "  WHERE subnet_id >= $1 and subnet_id <= $2 "
      "  ORDER BY subnet_id, state" },

    // ALL_POOL_LEASE4_STATS
    { 0, { OID_NONE },
      "all_pool_lease4_stats",
      "SELECT subnet_id, pool_id, state, leases as state_count"
      "  FROM lease4_pool_stat ORDER BY subnet_id, pool_id, state" },

    // ALL_LEASE6_STATS,
    { 0, { OID_NONE },
      "all_lease6_stats",
      "SELECT subnet_id, lease_type, state, leases as state_count"
      "  FROM lease6_stat ORDER BY subnet_id, lease_type, state" },

    // SUBNET_LEASE6_STATS
    { 1, { OID_INT8 },
      "subnet_lease6_stats",
      "SELECT subnet_id, lease_type, state, leases as state_count"
      "  FROM lease6_stat "
      "  WHERE subnet_id = $1 "
      "  ORDER BY lease_type, state" },

    // SUBNET_RANGE_LEASE6_STATS
    { 2, { OID_INT8, OID_INT8 },
      "subnet_range_lease6_stats",
      "SELECT subnet_id, lease_type, state, leases as state_count"
      "  FROM lease6_stat "
      "  WHERE subnet_id >= $1 and subnet_id <= $2 "
      "  ORDER BY subnet_id, lease_type, state" },

    // ALL_POOL_LEASE6_STATS,
    { 0, { OID_NONE },
      "all_pool_lease6_stats",
      "SELECT subnet_id, pool_id, lease_type, state, leases as state_count"
      "  FROM lease6_pool_stat ORDER BY subnet_id, pool_id, lease_type, state" },

    // CHECK_LEASE4_LIMITS
    { 1, { OID_TEXT },
      "check_lease4_limits",
      "SELECT checkLease4Limits($1)" },

    // CHECK_LEASE6_LIMITS
    { 1, { OID_TEXT },
      "check_lease6_limits",
      "SELECT checkLease6Limits($1)" },

    // IS_JSON_SUPPORTED
    { 0, { OID_NONE },
      "is_json_supported",
      "SELECT isJsonSupported()" },

    // GET_LEASE4_COUNT_BY_CLASS
    { 1, { OID_VARCHAR },
      "get_lease4_count_by_class",
      "SELECT leases "
          "FROM lease4_stat_by_client_class "
          "WHERE client_class = $1" },

    // GET_LEASE6_COUNT_BY_CLASS
    { 2, { OID_VARCHAR, OID_INT2 },
      "get_lease6_count_by_class",
      "SELECT leases "
          "FROM lease6_stat_by_client_class "
          "WHERE client_class = $1 AND lease_type = $2" },

    // WIPE_RELAY_ID6
    { 0, { OID_NONE },
      "wipe_relay_id6",
      "DELETE FROM lease6_relay_id" },

    // WIPE_REMOTE_ID6
    { 0, { OID_NONE },
      "wipe_remote_id6",
      "DELETE FROM lease6_remote_id" },

    // DELETE_RELAY_ID6
    { 1, { OID_VARCHAR },
      "delete_relay_id6",
      "DELETE FROM lease6_relay_id WHERE lease_addr = cast($1 as inet)" },

    // DELETE_REMOTE_ID6
    { 1, { OID_VARCHAR },
      "delete_remote_id6",
      "DELETE FROM lease6_remote_id WHERE lease_addr = cast($1 as inet)" },

    // ADD_RELAY_ID6
    { 2, { OID_BYTEA, OID_VARCHAR },
      "add_relay_id6",
      "INSERT INTO lease6_relay_id(relay_id, lease_addr) "
      "VALUES ($1, cast($2 as inet))" },

    // ADD_REMOTE_ID6
    { 2, { OID_BYTEA, OID_VARCHAR },
      "add_remote_id6",
      "INSERT INTO lease6_remote_id(remote_id, lease_addr) "
      "VALUES ($1, cast($2 as inet))" },

    // GET_RELAY_ID6
    { 3, { OID_BYTEA, OID_VARCHAR, OID_INT8 },
      "get_relay_id6",
      "SELECT DISTINCT ON(l.address) "
        "host(l.address), l.duid, l.valid_lifetime, "
        "extract(epoch from l.expire)::bigint, l.subnet_id, l.pref_lifetime, "
        "l.lease_type, l.iaid, l.prefix_len, l.fqdn_fwd, l.fqdn_rev, "
        "l.hostname, l.hwaddr, l.hwtype, l.hwaddr_source, "
        "l.state, l.user_context, l.pool_id "
      "FROM lease6 AS l "
      "INNER JOIN lease6_relay_id AS r "
      " ON l.address = r.lease_addr "
      " WHERE r.relay_id = $1 AND r.lease_addr > cast($2 as inet) "
      "ORDER BY l.address "
      "LIMIT $3" },

    // GET_REMOTE_ID6
    { 3, { OID_BYTEA, OID_VARCHAR, OID_INT8 },
      "get_remote_id6",
      "SELECT DISTINCT ON(l.address) "
        "host(l.address), l.duid, l.valid_lifetime, "
        "extract(epoch from l.expire)::bigint, l.subnet_id, l.pref_lifetime, "
        "l.lease_type, l.iaid, l.prefix_len, l.fqdn_fwd, l.fqdn_rev, "
        "l.hostname, l.hwaddr, l.hwtype, l.hwaddr_source, "
        "l.state, l.user_context, l.pool_id "
      "FROM lease6 AS l "
      "INNER JOIN lease6_remote_id AS r "
      " ON l.address = r.lease_addr "
      " WHERE r.remote_id = $1 AND r.lease_addr > cast($2 as inet) "
      "ORDER BY l.address "
      "LIMIT $3" },

    // COUNT_RELAY_ID6
    { 0, { OID_NONE },
      "count_relay_id6",
      "SELECT COUNT(*) FROM lease6_relay_id" },

    // COUNT_REMOTE_ID6
    { 0, { OID_NONE },
      "count_remote_id6",
      "SELECT COUNT(*) FROM lease6_remote_id" },

    // End of list sentinel
    { 0, { 0 }, 0, 0 }
};

}  // namespace

namespace isc {
namespace dhcp {

/// @brief Base class for marshalling leases to and from PostgreSQL.
///
/// Provides the common functionality to set up binding information between
/// lease objects in the program and their database representation in the
/// database.
class PgSqlLeaseExchange : public PgSqlExchange {
public:

    PgSqlLeaseExchange()
        : addr_str_(""), hwaddr_length_(0), hwaddr_(hwaddr_length_),
          valid_lifetime_(0), valid_lifetime_str_(""), expire_(0),
          expire_str_(""), subnet_id_(0), subnet_id_str_(""), pool_id_(0),
          pool_id_str_(""), cltt_(0), fqdn_fwd_(false), fqdn_rev_(false),
          hostname_(""), state_str_(""), user_context_(""), addr_bin_(16) {
    }

    virtual ~PgSqlLeaseExchange() {}

protected:

    /// @brief Common Instance members used for binding and conversion
    //@{
    std::string          addr_str_;
    size_t               hwaddr_length_;
    std::vector<uint8_t> hwaddr_;
    uint8_t              hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
    uint32_t             valid_lifetime_;
    std::string          valid_lifetime_str_;
    time_t               expire_;
    std::string          expire_str_;
    uint32_t             subnet_id_;
    std::string          subnet_id_str_;
    uint32_t             pool_id_;
    std::string          pool_id_str_;
    time_t               cltt_;
    bool                 fqdn_fwd_;
    bool                 fqdn_rev_;
    std::string          hostname_;
    std::string          state_str_;
    std::string          user_context_;
    std::vector<uint8_t> addr_bin_;
    //@}
};

/// @brief Supports exchanging IPv4 leases with PostgreSQL.
class PgSqlLease4Exchange : public PgSqlLeaseExchange {
private:

    /// @brief Column numbers for each column in the Lease4 table.
    /// These are used for both retrieving data and for looking up
    /// column labels for logging.  Note that their numeric order
    /// MUST match that of the column order in the Lease4 table.
    //@{
    static const size_t ADDRESS_COL = 0;
    static const size_t HWADDR_COL = 1;
    static const size_t CLIENT_ID_COL = 2;
    static const size_t VALID_LIFETIME_COL = 3;
    static const size_t EXPIRE_COL = 4;
    static const size_t SUBNET_ID_COL = 5;
    static const size_t FQDN_FWD_COL = 6;
    static const size_t FQDN_REV_COL = 7;
    static const size_t HOSTNAME_COL = 8;
    static const size_t STATE_COL = 9;
    static const size_t USER_CONTEXT_COL = 10;
    static const size_t RELAY_ID_COL = 11;
    static const size_t REMOTE_ID_COL = 12;
    static const size_t POOL_ID_COL = 13;
    //@}
    /// @brief Number of columns in the table holding DHCPv4 leases.
    static const size_t LEASE_COLUMNS = 14;

public:

    /// @brief Constructor
    PgSqlLease4Exchange()
        : lease_(), addr4_(0), client_id_length_(0),
          relay_id_length_(0), remote_id_length_(0) {

        BOOST_STATIC_ASSERT(13 < LEASE_COLUMNS);

        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));
        memset(relay_id_buffer_, 0, sizeof(relay_id_buffer_));
        memset(remote_id_buffer_, 0, sizeof(remote_id_buffer_));

        // Set the column names (for error messages)
        columns_.push_back("address");
        columns_.push_back("hwaddr");
        columns_.push_back("client_id");
        columns_.push_back("valid_lifetime");
        columns_.push_back("expire");
        columns_.push_back("subnet_id");
        columns_.push_back("fqdn_fwd");
        columns_.push_back("fqdn_rev");
        columns_.push_back("hostname");
        columns_.push_back("state");
        columns_.push_back("user_context");
        columns_.push_back("relay_id");
        columns_.push_back("remote_id");
        columns_.push_back("pool_id");
    }

    /// @brief Creates the bind array for sending Lease4 data to the database.
    ///
    /// Converts each Lease4 member into the appropriate form and adds it
    /// to the bind array.  Note that the array additions must occur in the
    /// order the columns are specified in the SQL statement.  By convention
    /// all columns in the table are explicitly listed in the SQL statement(s)
    /// in the same order as they occur in the table.
    ///
    /// @param lease Lease4 object that is to be written to the database
    /// @param[out] bind_array array to populate with the lease data values
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    void createBindForSend(const Lease4Ptr& lease, PsqlBindArray& bind_array) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease4 object is NULL");
        }

        // Store lease object to ensure it remains valid.
        lease_ = lease;

        try {
            addr_str_ = boost::lexical_cast<std::string>(lease->addr_.toUint32());
            bind_array.add(addr_str_);

            if (lease->hwaddr_ && !lease->hwaddr_->hwaddr_.empty()) {
                // PostgreSql does not provide MAX on variable length types
                // so we have to enforce it ourselves.
                if (lease->hwaddr_->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                        isc_throw(DbOperationError, "Hardware address length : "
                                  << lease_->hwaddr_->hwaddr_.size()
                                  << " exceeds maximum allowed of: "
                                  << HWAddr::MAX_HWADDR_LEN);
                }
                bind_array.add(lease->hwaddr_->hwaddr_);
            } else {
                bind_array.add("");
            }

            if (lease->client_id_) {
                bind_array.add(lease->client_id_->getClientId());
            } else {
                bind_array.add("");
            }

            valid_lifetime_str_ = boost::lexical_cast<std::string>(lease->valid_lft_);
            bind_array.add(valid_lifetime_str_);

            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            // expire = cltt_ + valid_lft_
            // Avoid overflow with infinite valid lifetime by using
            // expire = cltt_ when valid_lft_ = 0xffffffff
            if (lease_->valid_lft_ == Lease::INFINITY_LFT) {
                expire_str_ = convertToDatabaseTime(lease->cltt_, 0);
            } else {
                expire_str_ = convertToDatabaseTime(lease->cltt_,
                                                    lease_->valid_lft_);
            }
            bind_array.add(expire_str_);

            subnet_id_str_ = boost::lexical_cast<std::string>(lease->subnet_id_);
            bind_array.add(subnet_id_str_);

            bind_array.add(lease->fqdn_fwd_);

            bind_array.add(lease->fqdn_rev_);

            bind_array.add(lease->hostname_);

            state_str_ = boost::lexical_cast<std::string>(lease->state_);
            bind_array.add(state_str_);

            ConstElementPtr ctx = lease->getContext();
            if (ctx) {
                user_context_ = ctx->str();
            } else {
                user_context_ = "";
            }
            bind_array.add(user_context_);

            if (!lease->relay_id_.empty()) {
                bind_array.add(lease->relay_id_);
            } else {
                bind_array.addNull();
            }

            if (!lease->remote_id_.empty()) {
                bind_array.add(lease->remote_id_);
            } else {
                bind_array.addNull();
            }

            pool_id_str_ = boost::lexical_cast<std::string>(lease->pool_id_);
            bind_array.add(pool_id_str_);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }
    }

    /// @brief Creates a Lease4 object from a given row in a result set.
    ///
    /// @param r result set containing one or rows from the Lease4 table
    /// @param row row number within the result set from to create the Lease4
    /// object.
    ///
    /// @return Lease4Ptr to the newly created Lease4 object
    /// @throw DbOperationError if the lease cannot be created.
    Lease4Ptr convertFromDatabase(const PgSqlResult& r, int row) {
        try {
            getColumnValue(r, row, ADDRESS_COL, addr4_);

            convertFromBytea(r, row, HWADDR_COL, hwaddr_buffer_,
                             sizeof(hwaddr_buffer_), hwaddr_length_);

            convertFromBytea(r, row, CLIENT_ID_COL, client_id_buffer_,
                             sizeof(client_id_buffer_), client_id_length_);

            getColumnValue(r, row, VALID_LIFETIME_COL, valid_lifetime_);

            expire_ = convertFromDatabaseTime(getRawColumnValue(r, row,
                                                                EXPIRE_COL));

            getColumnValue(r, row, SUBNET_ID_COL, subnet_id_);

            // Recover from overflow (see createBindForSend)
            if (valid_lifetime_ == Lease::INFINITY_LFT) {
                cltt_ = expire_;
            } else {
                cltt_ = expire_ - valid_lifetime_;
            }

            getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);

            getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

            hostname_ = getRawColumnValue(r, row, HOSTNAME_COL);

            uint32_t state;
            getColumnValue(r, row, STATE_COL, state);

            HWAddrPtr hwaddr(new HWAddr(hwaddr_buffer_, hwaddr_length_,
                                        HTYPE_ETHER));

            user_context_ = getRawColumnValue(r, row, USER_CONTEXT_COL);
            ConstElementPtr ctx;
            if (!user_context_.empty()) {
                ctx = Element::fromJSON(user_context_);
                if (!ctx || (ctx->getType() != Element::map)) {
                    isc_throw(BadValue, "user context '" << user_context_
                              << "' is not a JSON map");
                }
            }

            convertFromBytea(r, row, RELAY_ID_COL, relay_id_buffer_,
                             sizeof(relay_id_buffer_), relay_id_length_);

            convertFromBytea(r, row, REMOTE_ID_COL, remote_id_buffer_,
                             sizeof(remote_id_buffer_), remote_id_length_);

            getColumnValue(r, row, POOL_ID_COL, pool_id_);

            Lease4Ptr result(boost::make_shared<Lease4>(addr4_, hwaddr,
                                                        client_id_buffer_,
                                                        client_id_length_,
                                                        valid_lifetime_, cltt_,
                                                        subnet_id_, fqdn_fwd_,
                                                        fqdn_rev_, hostname_));

            result->state_ = state;

            if (ctx) {
                result->setContext(ctx);
            }

            if (relay_id_length_) {
                result->relay_id_.assign(relay_id_buffer_,
                                         relay_id_buffer_ + relay_id_length_);
            }

            if (remote_id_length_) {
                result->remote_id_.assign(remote_id_buffer_,
                                          remote_id_buffer_ + remote_id_length_);
            }

            result->pool_id_ = pool_id_;

            return (result);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not convert data to Lease4, reason: "
                       << ex.what());
        }
    }

private:

    /// @brief Lease4 object currently being sent to the database.
    /// Storing this value ensures that it remains in scope while any bindings
    /// that refer to its contents are in use.
    Lease4Ptr lease_;

    /// @brief Lease4 specific members for binding and conversion.
    uint32_t  addr4_;
    size_t    client_id_length_;
    uint8_t   client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
    size_t    relay_id_length_;
    uint8_t   relay_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
    size_t    remote_id_length_;
    uint8_t   remote_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
};

/// @brief Supports exchanging IPv6 leases with PostgreSQL.
class PgSqlLease6Exchange : public PgSqlLeaseExchange {
private:

    /// @brief Column numbers for each column in the Lease6 table.
    /// These are used for both retrieving data and for looking up
    /// column labels for logging.  Note that their numeric order
    /// MUST match that of the column order in the Lease6 table.
    //@{
    static const size_t ADDRESS_COL = 0;
    static const size_t DUID_COL = 1;
    static const size_t VALID_LIFETIME_COL = 2;
    static const size_t EXPIRE_COL = 3;
    static const size_t SUBNET_ID_COL = 4;
    static const size_t PREF_LIFETIME_COL = 5;
    static const size_t LEASE_TYPE_COL =  6;
    static const size_t IAID_COL = 7;
    static const size_t PREFIX_LEN_COL = 8;
    static const size_t FQDN_FWD_COL = 9;
    static const size_t FQDN_REV_COL = 10;
    static const size_t HOSTNAME_COL = 11;
    static const size_t HWADDR_COL = 12;
    static const size_t HWTYPE_COL = 13;
    static const size_t HWADDR_SOURCE_COL = 14;
    static const size_t STATE_COL = 15;
    static const size_t USER_CONTEXT_COL = 16;
    static const size_t POOL_ID_COL = 17;
    //@}
    /// @brief Number of columns in the table holding DHCPv6 leases.
    static const size_t LEASE_COLUMNS = 18;

public:

    /// @brief Union for marshalling IAID into and out of the database
    /// IAID is defined in the RFC as 4 octets, which Kea code handles as
    /// a uint32_t.  Postgresql however, offers only signed integer types
    /// of sizes 2, 4, and 8 bytes (SMALLINT, INT, and BIGINT respectively).
    /// IAID is used in several indexes so rather than use the BIGINT, we
    /// use this union to safely move the value into and out of an INT column.
    union Uiaid {
        /// @brief Constructor
        /// @param val unsigned 32 bit value for the IAID.
        Uiaid(uint32_t val) : uval_(val) {};

        /// @brief Constructor
        /// @param val signed 32 bit value for the IAID.
        Uiaid(int32_t val) : ival_(val) {};

        /// @brief Return a string representing the signed 32-bit value.
        std::string dbInputString() {
            return (boost::lexical_cast<std::string>(ival_));
        };

        uint32_t uval_;
        int32_t ival_;
    };

    PgSqlLease6Exchange()
        : lease_(), duid_length_(0), duid_(duid_length_), iaid_u_(0),
          iaid_str_(""), lease_type_(Lease6::TYPE_NA), lease_type_str_(""),
          prefix_len_(0), prefix_len_str_(""), pref_lifetime_(0),
          preferred_lifetime_str_(""), hwtype_(0), hwtype_str_(""),
          hwaddr_source_(0), hwaddr_source_str_("") {

        BOOST_STATIC_ASSERT(17 < LEASE_COLUMNS);

        memset(duid_buffer_, 0, sizeof(duid_buffer_));

        // Set the column names (for error messages)
        columns_.push_back("address");
        columns_.push_back("duid");
        columns_.push_back("valid_lifetime");
        columns_.push_back("expire");
        columns_.push_back("subnet_id");
        columns_.push_back("pref_lifetime");
        columns_.push_back("lease_type");
        columns_.push_back("iaid");
        columns_.push_back("prefix_len");
        columns_.push_back("fqdn_fwd");
        columns_.push_back("fqdn_rev");
        columns_.push_back("hostname");
        columns_.push_back("hwaddr");
        columns_.push_back("hwtype");
        columns_.push_back("hwaddr_source");
        columns_.push_back("state");
        columns_.push_back("user_context");
        columns_.push_back("pool_id");
    }

    /// @brief Creates the bind array for sending Lease6 data to the database.
    ///
    /// Converts each Lease6 member into the appropriate form and adds it
    /// to the bind array.  Note that the array additions must occur in the
    /// order the columns are specified in the SQL statement.  By convention
    /// all columns in the table are explicitly listed in the SQL statement(s)
    /// in the same order as they occur in the table.
    ///
    /// @param lease Lease6 object that is to be written to the database
    /// @param[out] bind_array array to populate with the lease data values
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    void createBindForSend(const Lease6Ptr& lease, PsqlBindArray& bind_array) {
        if (!lease) {
            isc_throw(BadValue, "createBindForSend:: Lease6 object is NULL");
        }

        // Store lease object to ensure it remains valid.
        lease_ = lease;
        try {
            addr_str_ = lease_->addr_.toText();
            bind_array.add(addr_str_);

            if (lease_->duid_) {
                bind_array.add(lease_->duid_->getDuid());
            } else {
                isc_throw (BadValue, "IPv6 Lease cannot have a null DUID");
            }

            valid_lifetime_str_ = boost::lexical_cast<std::string>(lease->valid_lft_);
            bind_array.add(valid_lifetime_str_);

            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            // expire = cltt_ + valid_lft_
            // Avoid overflow with infinite valid lifetime by using
            // expire = cltt_ when valid_lft_ = 0xffffffff
            if (lease_->valid_lft_ == Lease::INFINITY_LFT) {
                expire_str_ = convertToDatabaseTime(lease->cltt_, 0);
            } else {
                expire_str_ = convertToDatabaseTime(lease->cltt_,
                                                    lease_->valid_lft_);
            }
            bind_array.add(expire_str_);

            subnet_id_str_ = boost::lexical_cast<std::string>(lease->subnet_id_);
            bind_array.add(subnet_id_str_);

            preferred_lifetime_str_ = boost::lexical_cast<std::string>(lease_->preferred_lft_);
            bind_array.add(preferred_lifetime_str_);

            lease_type_str_ = boost::lexical_cast<std::string>(lease_->type_);
            bind_array.add(lease_type_str_);

            // The iaid is stored as an INT in lease6 table, so we must
            // lexically cast from an integer version to avoid out of range
            // exception failure upon insert.
            iaid_u_.uval_ = lease_->iaid_;
            iaid_str_ = iaid_u_.dbInputString();
            bind_array.add(iaid_str_);

            prefix_len_str_ = boost::lexical_cast<std::string>
                              (static_cast<unsigned int>(lease_->prefixlen_));
            bind_array.add(prefix_len_str_);

            bind_array.add(lease->fqdn_fwd_);

            bind_array.add(lease->fqdn_rev_);

            bind_array.add(lease->hostname_);

            if (lease->hwaddr_ && !lease->hwaddr_->hwaddr_.empty()) {
                // PostgreSql does not provide MAX on variable length types
                // so we have to enforce it ourselves.
                if (lease->hwaddr_->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                        isc_throw(DbOperationError, "Hardware address length : "
                                  << lease_->hwaddr_->hwaddr_.size()
                                  << " exceeds maximum allowed of: "
                                  << HWAddr::MAX_HWADDR_LEN);
                }
                bind_array.add(lease->hwaddr_->hwaddr_);
            } else {
                bind_array.add("");
            }

            if (lease->hwaddr_) {
                hwtype_str_ = boost::lexical_cast<std::string>
                              (static_cast<unsigned int>(lease_->hwaddr_->htype_));
                hwaddr_source_str_ = boost::lexical_cast<std::string>
                                     (static_cast<unsigned int>(lease_->hwaddr_->source_));
            } else {
                hwtype_str_ = boost::lexical_cast<std::string>
                              (static_cast<unsigned int>(HTYPE_UNDEFINED));
                hwaddr_source_str_ = boost::lexical_cast<std::string>
                                     (static_cast<unsigned int>(HWAddr::HWADDR_SOURCE_UNKNOWN));
            }

            bind_array.add(hwtype_str_);

            bind_array.add(hwaddr_source_str_);

            state_str_ = boost::lexical_cast<std::string>(lease->state_);
            bind_array.add(state_str_);

            ConstElementPtr ctx = lease->getContext();
            if (ctx) {
                user_context_ = ctx->str();
            } else {
                user_context_ = "";
            }
            bind_array.add(user_context_);

            pool_id_str_ = boost::lexical_cast<std::string>(lease->pool_id_);
            bind_array.add(pool_id_str_);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }
    }

    /// @brief Creates a Lease6 object from a given row in a result set.
    ///
    /// @param r result set containing one or rows from the Lease6 table
    /// @param row row number within the result set from to create the Lease6
    /// object.
    ///
    /// @return Lease6Ptr to the newly created Lease4 object
    /// @throw DbOperationError if the lease cannot be created.
    Lease6Ptr convertFromDatabase(const PgSqlResult& r, int row) {
        try {

            /// @todo In theory, an administrator could tweak lease
            /// information in the database. In this case, some of the
            /// values could be set to NULL. This is less likely than
            /// in case of host reservations, but we may consider if
            /// retrieved values should be checked for being NULL to
            /// prevent cryptic errors during conversions from NULL
            /// to actual values.

            IOAddress addr(getIPv6Value(r, row, ADDRESS_COL));

            convertFromBytea(r, row, DUID_COL, duid_buffer_, sizeof(duid_buffer_), duid_length_);
            DuidPtr duid_ptr(new DUID(duid_buffer_, duid_length_));

            getColumnValue(r, row, VALID_LIFETIME_COL, valid_lifetime_);

            expire_ = convertFromDatabaseTime(getRawColumnValue(r, row,
                                                                EXPIRE_COL));

            // Recover from overflow (see createBindForSend)
            if (valid_lifetime_ == Lease::INFINITY_LFT) {
                cltt_ = expire_;
            } else {
                cltt_ = expire_ - valid_lifetime_;
            }

            getColumnValue(r, row, SUBNET_ID_COL, subnet_id_);

            getColumnValue(r, row, PREF_LIFETIME_COL, pref_lifetime_);

            getLeaseTypeColumnValue(r, row, LEASE_TYPE_COL, lease_type_);

            getColumnValue(r, row, IAID_COL, iaid_u_.ival_);

            getColumnValue(r, row, PREFIX_LEN_COL, prefix_len_);

            getColumnValue(r, row, FQDN_FWD_COL, fqdn_fwd_);

            getColumnValue(r, row, FQDN_REV_COL, fqdn_rev_);

            hostname_ = getRawColumnValue(r, row, HOSTNAME_COL);

            convertFromBytea(r, row, HWADDR_COL, hwaddr_buffer_,
                             sizeof(hwaddr_buffer_), hwaddr_length_);

            getColumnValue(r, row, HWTYPE_COL, hwtype_);

            getColumnValue(r, row, HWADDR_SOURCE_COL, hwaddr_source_);

            HWAddrPtr hwaddr;

            if (hwaddr_length_) {
                hwaddr.reset(new HWAddr(hwaddr_buffer_, hwaddr_length_,
                                        hwtype_));

                hwaddr->source_ = hwaddr_source_;
            }

            uint32_t state;
            getColumnValue(r, row, STATE_COL, state);

            user_context_ = getRawColumnValue(r, row, USER_CONTEXT_COL);
            ConstElementPtr ctx;
            if (!user_context_.empty()) {
                ctx = Element::fromJSON(user_context_);
                if (!ctx || (ctx->getType() != Element::map)) {
                    isc_throw(BadValue, "user context '" << user_context_
                              << "' is not a JSON map");
                }
            }

            getColumnValue(r, row, POOL_ID_COL, pool_id_);

            if (lease_type_ != Lease::TYPE_PD) {
                prefix_len_ = 128;
            }

            Lease6Ptr result(boost::make_shared<Lease6>(lease_type_, addr,
                                                        duid_ptr,
                                                        iaid_u_.uval_,
                                                        pref_lifetime_,
                                                        valid_lifetime_,
                                                        subnet_id_, fqdn_fwd_,
                                                        fqdn_rev_, hostname_,
                                                        hwaddr, prefix_len_));
            // Update cltt_ and current_cltt_ explicitly.
            result->cltt_ = cltt_;
            result->current_cltt_ = cltt_;

            result->state_ = state;

            if (ctx) {
                result->setContext(ctx);
            }

            result->pool_id_ = pool_id_;

            return (result);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not convert data to Lease6, reason: "
                       << ex.what());
        }
    }

    /// @brief Fetches an integer text column as a Lease6::Type
    ///
    /// @param r the result set containing the query results
    /// @param row the row number within the result set
    /// @param col the column number within the row
    /// @param[out] value parameter to receive the converted value
    ///
    /// Note we depart from overloading getColumnValue to avoid ambiguity
    /// with base class methods for integers.
    ///
    /// @throw  DbOperationError if the value cannot be fetched or is
    /// invalid.
    void getLeaseTypeColumnValue(const PgSqlResult& r, const int row,
                                 const size_t col, Lease6::Type& value) const {
        uint32_t raw_value = 0;
        getColumnValue(r, row, col, raw_value);
        switch (raw_value) {
            case Lease6::TYPE_NA:
            case Lease6::TYPE_TA:
            case Lease6::TYPE_PD:
                value = static_cast<Lease6::Type>(raw_value);
                break;

            default:
                isc_throw(DbOperationError, "Invalid lease type: " << raw_value
                      << " for: " << getColumnLabel(r, col) << " row:" << row);
        }
    }

private:
    /// @brief Lease6 object currently being sent to the database.
    /// Storing this value ensures that it remains in scope while any bindings
    /// that refer to its contents are in use.
    Lease6Ptr            lease_;

    /// @brief Lease6 specific members for binding and conversion.
    //@{
    size_t               duid_length_;
    std::vector<uint8_t> duid_;
    uint8_t              duid_buffer_[DUID::MAX_DUID_LEN];
    union Uiaid          iaid_u_;
    std::string          iaid_str_;
    Lease6::Type         lease_type_;
    std::string          lease_type_str_;
    uint8_t              prefix_len_;
    std::string          prefix_len_str_;
    uint32_t             pref_lifetime_;
    std::string          preferred_lifetime_str_;
    uint32_t             hwtype_;
    std::string          hwtype_str_;
    uint32_t             hwaddr_source_;
    std::string          hwaddr_source_str_;
    //@}
};

/// @brief Base PgSql derivation of the statistical lease data query
///
/// This class provides the functionality such as results storage and row
/// fetching common to fulfilling the statistical lease data query.
///
class PgSqlLeaseStatsQuery : public LeaseStatsQuery {
public:

    /// @brief Constructor to query for all subnets' stats
    ///
    ///  The query created will return statistics for all subnets
    ///
    /// @param conn A open connection to the database housing the lease data
    /// @param statement The lease data SQL prepared statement to execute
    /// @param fetch_type Indicates whether or not lease_type should be
    /// fetched from the result set
    /// @param fetch_pool Indicates if query requires pool data
    PgSqlLeaseStatsQuery(PgSqlConnection& conn, PgSqlTaggedStatement& statement,
                         const bool fetch_type, const bool fetch_pool = false)
        : conn_(conn), statement_(statement), result_set_(), next_row_(0),
          fetch_type_(fetch_type), fetch_pool_(fetch_pool) {
    }

    /// @brief Constructor to query for a single subnet's stats
    ///
    /// The query created will return statistics for a single subnet
    ///
    /// @param conn A open connection to the database housing the lease data
    /// @param statement The lease data SQL prepared statement to execute
    /// @param fetch_type Indicates if query supplies lease type
    /// @param subnet_id id of the subnet for which stats are desired
    PgSqlLeaseStatsQuery(PgSqlConnection& conn, PgSqlTaggedStatement& statement,
                         const bool fetch_type, const SubnetID& subnet_id)
        : LeaseStatsQuery(subnet_id), conn_(conn), statement_(statement), result_set_(),
          next_row_(0), fetch_type_(fetch_type), fetch_pool_(false) {
    }

    /// @brief Constructor to query for the stats for a range of subnets
    ///
    /// The query created will return statistics for the inclusive range of
    /// subnets described by first and last subnet IDs.
    ///
    /// @param conn A open connection to the database housing the lease data
    /// @param statement The lease data SQL prepared statement to execute
    /// @param fetch_type Indicates if query supplies lease type
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    PgSqlLeaseStatsQuery(PgSqlConnection& conn, PgSqlTaggedStatement& statement,
                         const bool fetch_type, const SubnetID& first_subnet_id,
                         const SubnetID& last_subnet_id)
        : LeaseStatsQuery(first_subnet_id, last_subnet_id), conn_(conn), statement_(statement),
          result_set_(), next_row_(0), fetch_type_(fetch_type), fetch_pool_(false) {
    }

    /// @brief Destructor
    virtual ~PgSqlLeaseStatsQuery() {};

    /// @brief Creates the lease statistical data result set
    ///
    /// The result set is populated by executing a prepared SQL query
    /// against the database fetches the lease count per lease state per
    /// (per least type - v6 only) per subnet id.
    ///
    /// Depending upon the selection mode, the query will have either no
    /// parameters (for all subnets), a subnet id for a single subnet, or
    /// a first and last subnet id for a subnet range.
    void start() {

        if (getSelectMode() == ALL_SUBNETS || getSelectMode() == ALL_SUBNET_POOLS) {
            // Run the query with no where clause parameters.
            result_set_.reset(new PgSqlResult(PQexecPrepared(conn_, statement_.name,
                                                             0, 0, 0, 0, 0)));
        } else {
            // Set up the WHERE clause values
            PsqlBindArray parms;

            // Add first_subnet_id used by both single and range.
            parms.addTempString(boost::lexical_cast<std::string>(getFirstSubnetID()));

            // Add last_subnet_id for range.
            if (getSelectMode() == SUBNET_RANGE) {
                // Add last_subnet_id used by range.
                parms.addTempString(boost::lexical_cast<std::string>(getLastSubnetID()));
            }

            // Run the query with where clause parameters.
            result_set_.reset(new PgSqlResult(PQexecPrepared(conn_, statement_.name,
                                              parms.size(), &parms.values_[0],
                                              &parms.lengths_[0], &parms.formats_[0], 0)));
        }

        conn_.checkStatementError(*result_set_, statement_);
    }

    /// @brief Fetches the next row in the result set
    ///
    /// Once the internal result set has been populated by invoking the
    /// the start() method, this method is used to iterate over the
    /// result set rows. Once the last row has been fetched, subsequent
    /// calls will return false.
    ///
    /// Checks against negative values for the state count and logs once
    /// a warning message.
    ///
    /// @param row Storage for the fetched row
    ///
    /// @return True if the fetch succeeded, false if there are no more
    /// rows to fetch.
    bool getNextRow(LeaseStatsRow& row) {
        // If we're past the end, punt.
        if (next_row_ >= result_set_->getRows()) {
            return (false);
        }

        // Fetch the subnet id.
        uint32_t col = 0;
        uint32_t subnet_id;
        PgSqlExchange::getColumnValue(*result_set_, next_row_, col, subnet_id);
        row.subnet_id_ = static_cast<SubnetID>(subnet_id);
        ++col;

        // Fetch the pool id if we were told to do so.
        if (fetch_pool_) {
            PgSqlExchange::getColumnValue(*result_set_, next_row_, col,
                                          row.pool_id_);
            ++col;
        }

        // Fetch the lease type if we were told to do so.
        if (fetch_type_) {
            uint32_t lease_type;
            PgSqlExchange::getColumnValue(*result_set_, next_row_, col,
                                          lease_type);
            row.lease_type_ = static_cast<Lease::Type>(lease_type);
            ++col;
        } else {
            row.lease_type_ = Lease::TYPE_NA;
        }

        // Fetch the lease state.
        PgSqlExchange::getColumnValue(*result_set_, next_row_, col,
                                      row.lease_state_);
        ++col;

        // Fetch the state count.
        PgSqlExchange::getColumnValue(*result_set_, next_row_, col,
                                      row.state_count_);

        // Protect against negative state count.a
        if (row.state_count_ < 0) {
            row.state_count_ = 0;
            if (!negative_count_) {
                negative_count_ = true;
                LOG_WARN(dhcpsrv_logger, DHCPSRV_PGSQL_NEGATIVE_LEASES_STAT);
            }
        }

        // Point to the next row.
        ++next_row_;
        return (true);
    }

protected:

    /// @brief Database connection to use to execute the query
    PgSqlConnection& conn_;

    /// @brief The query's prepared statement
    PgSqlTaggedStatement& statement_;

    /// @brief The result set returned by Postgres.
    boost::shared_ptr<PgSqlResult> result_set_;

    /// @brief Index of the next row to fetch
    uint32_t next_row_;

    /// @brief Indicates if query supplies lease type
    bool fetch_type_;

    /// @brief Indicates if query requires pool data
    bool fetch_pool_;

    /// @brief Received negative state count showing a problem
    static bool negative_count_;
};

// Initialize negative state count flag to false.
bool PgSqlLeaseStatsQuery::negative_count_ = false;

// PgSqlLeaseContext Constructor

PgSqlLeaseContext::PgSqlLeaseContext(const DatabaseConnection::ParameterMap& parameters,
                                     IOServiceAccessorPtr io_service_accessor,
                                     DbCallback db_reconnect_callback)
    : conn_(parameters, io_service_accessor, db_reconnect_callback) {
}

// PgSqlLeaseContextAlloc Constructor and Destructor

PgSqlLeaseMgr::PgSqlLeaseContextAlloc::PgSqlLeaseContextAlloc(
    const PgSqlLeaseMgr& mgr) : ctx_(), mgr_(mgr) {

    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        {
            // we need to protect the whole pool_ operation, hence extra scope {}
            lock_guard<mutex> lock(mgr_.pool_->mutex_);
            if (!mgr_.pool_->pool_.empty()) {
                ctx_ = mgr_.pool_->pool_.back();
                mgr_.pool_->pool_.pop_back();
            }
        }
        if (!ctx_) {
            ctx_ = mgr_.createContext();
        }
    } else {
        // single-threaded
        if (mgr_.pool_->pool_.empty()) {
            isc_throw(Unexpected, "No available PostgreSQL lease context?!");
        }
        ctx_ = mgr_.pool_->pool_.back();
    }
}

PgSqlLeaseMgr::PgSqlLeaseContextAlloc::~PgSqlLeaseContextAlloc() {
    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        lock_guard<mutex> lock(mgr_.pool_->mutex_);
        mgr_.pool_->pool_.push_back(ctx_);
    }
    // If running in single-threaded mode, there's nothing to do here.
}

// PgSqlLeaseTrackingContextAlloc Constructor and Destructor

PgSqlLeaseMgr::PgSqlLeaseTrackingContextAlloc::PgSqlLeaseTrackingContextAlloc(
    PgSqlLeaseMgr& mgr, const LeasePtr& lease) : ctx_(), mgr_(mgr), lease_(lease) {

    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        {
            // we need to protect the whole pool_ operation, hence extra scope {}
            lock_guard<mutex> lock(mgr_.pool_->mutex_);
            if (mgr_.hasCallbacks() && !mgr_.tryLock(lease)) {
                isc_throw(DbOperationError, "unable to lock the lease " << lease->addr_);
            }
            if (!mgr_.pool_->pool_.empty()) {
                ctx_ = mgr_.pool_->pool_.back();
                mgr_.pool_->pool_.pop_back();
            }
        }
        if (!ctx_) {
            ctx_ = mgr_.createContext();
        }
    } else {
        // single-threaded
        if (mgr_.pool_->pool_.empty()) {
            isc_throw(Unexpected, "No available PostgreSQL lease context?!");
        }
        ctx_ = mgr_.pool_->pool_.back();
    }
}

PgSqlLeaseMgr::PgSqlLeaseTrackingContextAlloc::~PgSqlLeaseTrackingContextAlloc() {
    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        lock_guard<mutex> lock(mgr_.pool_->mutex_);
        if (mgr_.hasCallbacks()) {
            mgr_.unlock(lease_);
        }
        mgr_.pool_->pool_.push_back(ctx_);
    }
    // If running in single-threaded mode, there's nothing to do here.
}

// PgSqlLeaseMgr Constructor and Destructor

PgSqlLeaseMgr::PgSqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : TrackingLeaseMgr(), parameters_(parameters) {

    // Check if the extended info tables are enabled.
    setExtendedInfoTablesEnabled(parameters);

    // Check TLS support.
    size_t tls(0);
    tls += parameters.count("trust-anchor");
    tls += parameters.count("cert-file");
    tls += parameters.count("key-file");
    tls += parameters.count("cipher-list");
#ifdef HAVE_PGSQL_SSL
    if ((tls > 0) && !PgSqlConnection::warned_about_tls) {
        PgSqlConnection::warned_about_tls = true;
        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_TLS_SUPPORT)
            .arg(DatabaseConnection::redactedAccessString(parameters_));
        PQinitSSL(1);
    }
#else
    if (tls > 0) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_NO_TLS_SUPPORT)
            .arg(DatabaseConnection::redactedAccessString(parameters_));
        isc_throw(DbOpenError, "Attempt to configure TLS for PostgreSQL "
                  << "backend (built with this feature disabled)");
    }
#endif

    // Create unique timer name per instance.
    timer_name_ = "PgSqlLeaseMgr[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    PgSqlConnection::ensureSchemaVersion(parameters_, DbCallback(&PgSqlLeaseMgr::dbReconnect),
                                         timer_name_);

    // Create an initial context.
    pool_.reset(new PgSqlLeaseContextPool());
    pool_->pool_.push_back(createContext());
}

PgSqlLeaseMgr::~PgSqlLeaseMgr() {
}

bool
PgSqlLeaseMgr::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
    MultiThreadingCriticalSection cs;

    // Invoke application layer connection lost callback.
    if (!DatabaseConnection::invokeDbLostCallback(db_reconnect_ctl)) {
        return (false);
    }

    bool reopened = false;

    const std::string timer_name = db_reconnect_ctl->timerName();

    // At least one connection was lost.
    try {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getCurrentCfg()->getCfgDbAccess();
        LeaseMgrFactory::recreate(cfg_db->getLeaseDbAccessString());
        reopened = true;
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED)
                .arg(ex.what());
    }

    if (reopened) {
        // Cancel the timer.
        if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->unregisterTimer(timer_name);
        }

        // Invoke application layer connection recovered callback.
        if (!DatabaseConnection::invokeDbRecoveredCallback(db_reconnect_ctl)) {
            return (false);
        }
    } else {
        if (!db_reconnect_ctl->checkRetries()) {
            // We're out of retries, log it and initiate shutdown.
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_LEASE_DB_RECONNECT_FAILED)
                    .arg(db_reconnect_ctl->maxRetries());

            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection failed callback.
            DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);
            return (false);
        }

        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        // Start the timer.
        if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->registerTimer(timer_name,
                std::bind(&PgSqlLeaseMgr::dbReconnect, db_reconnect_ctl),
                          db_reconnect_ctl->retryInterval(),
                          asiolink::IntervalTimer::ONE_SHOT);
        }
        TimerMgr::instance()->setup(timer_name);
    }

    return (true);
}

// Create context.

PgSqlLeaseContextPtr
PgSqlLeaseMgr::createContext() const {
    PgSqlLeaseContextPtr ctx(new PgSqlLeaseContext(parameters_,
        IOServiceAccessorPtr(new IOServiceAccessor(&DatabaseConnection::getIOService)),
        &PgSqlLeaseMgr::dbReconnect));

    // Create ReconnectCtl for this connection.
    ctx->conn_.makeReconnectCtl(timer_name_);

    // Open the database.
    ctx->conn_.openDatabase();

    // Now prepare the SQL statements.
    uint32_t i = 0;
    for (; tagged_statements[i].text != NULL; ++i) {
        ctx->conn_.prepareStatement(tagged_statements[i]);
    }

    // Just in case somebody foo-barred things
    if (i != NUM_STATEMENTS) {
        isc_throw(DbOpenError, "Number of statements prepared: " << i
                  << " does not match expected count:" << NUM_STATEMENTS);
    }

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    ctx->exchange4_.reset(new PgSqlLease4Exchange());
    ctx->exchange6_.reset(new PgSqlLease6Exchange());

    return (ctx);
}

std::string
PgSqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "PostgreSQL backend " << PGSQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << PGSQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << PQlibVersion();
    return (tmp.str());
}

bool
PgSqlLeaseMgr::addLeaseCommon(PgSqlLeaseContextPtr& ctx,
                              StatementIndex stindex,
                              PsqlBindArray& bind_array) {
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (ctx->conn_.compareError(r, PgSqlConnection::DUPLICATE_KEY)) {
            return (false);
        }
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }

    return (true);
}

bool
PgSqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_ADD_ADDR4)
        .arg(lease->addr_.toText());

    // Get a context
    PgSqlLeaseTrackingContextAlloc get_context(*this, lease);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    PsqlBindArray bind_array;
    ctx->exchange4_->createBindForSend(lease, bind_array);
    auto result = addLeaseCommon(ctx, INSERT_LEASE4, bind_array);

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackAddLease(lease);
    }

    return (result);
}

bool
PgSqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_ADD_ADDR6)
        .arg(lease->addr_.toText())
        .arg(lease->type_);

    lease->extended_info_action_ = Lease6::ACTION_IGNORE;

    // Get a context
    PgSqlLeaseTrackingContextAlloc get_context(*this, lease);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    PsqlBindArray bind_array;
    ctx->exchange6_->createBindForSend(lease, bind_array);

    auto result = addLeaseCommon(ctx, INSERT_LEASE6, bind_array);

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    if (getExtendedInfoTablesEnabled()) {
        static_cast<void>(addExtendedInfo6(lease));
    }

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackAddLease(lease);
    }

    return (result);
}

template <typename Exchange, typename LeaseCollection>
void
PgSqlLeaseMgr::getLeaseCollection(PgSqlLeaseContextPtr& ctx,
                                  StatementIndex stindex,
                                  PsqlBindArray& bind_array,
                                  Exchange& exchange,
                                  LeaseCollection& result,
                                  bool single) const {
    const int n = tagged_statements[stindex].nbparams;
    PgSqlResult r(PQexecPrepared(ctx->conn_,
                                 tagged_statements[stindex].name, n,
                                 n > 0 ? &bind_array.values_[0] : NULL,
                                 n > 0 ? &bind_array.lengths_[0] : NULL,
                                 n > 0 ? &bind_array.formats_[0] : NULL, 0));

    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);

    int rows = PQntuples(r);
    if (single && rows > 1) {
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << tagged_statements[stindex].name);
    }

    for(int i = 0; i < rows; ++i) {
        result.push_back(exchange->convertFromDatabase(r, i));
    }
}

void
PgSqlLeaseMgr::getLease(PgSqlLeaseContextPtr& ctx,
                        StatementIndex stindex, PsqlBindArray& bind_array,
                        Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(ctx, stindex, bind_array, ctx->exchange4_,
                       collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
PgSqlLeaseMgr::getLease(PgSqlLeaseContextPtr& ctx,
                        StatementIndex stindex, PsqlBindArray& bind_array,
                        Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(ctx, stindex, bind_array, ctx->exchange6_,
                       collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_ADDR4)
        .arg(addr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // LEASE ADDRESS
    std::string addr_str = boost::lexical_cast<std::string>(addr.toUint32());
    bind_array.add(addr_str);

    // Get the data
    Lease4Ptr result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE4_ADDR, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_HWADDR)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // HWADDR
    if (!hwaddr.hwaddr_.empty()) {
        bind_array.add(hwaddr.hwaddr_);
    } else {
        bind_array.add("");
    }

    // Get the data
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_HWADDR, bind_array, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SUBID_HWADDR)
        .arg(subnet_id)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // HWADDR
    if (!hwaddr.hwaddr_.empty()) {
        bind_array.add(hwaddr.hwaddr_);
    } else {
        bind_array.add("");
    }

    // SUBNET_ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // Get the data
    Lease4Ptr result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE4_HWADDR_SUBID, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_CLIENTID)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // CLIENT_ID
    bind_array.add(clientid.getClientId());

    // Get the data
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_CLIENTID, bind_array, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SUBID_CLIENTID)
        .arg(subnet_id)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // CLIENT_ID
    bind_array.add(clientid.getClientId());

    // SUBNET_ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // Get the data
    Lease4Ptr result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE4_CLIENTID_SUBID, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLeases4(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SUBID4)
        .arg(subnet_id);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // SUBNET_ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // ... and get the data
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_SUBID, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLeases4(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_HOSTNAME4)
        .arg(hostname);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // Hostname
    bind_array.add(hostname);

    // ... and get the data
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_HOSTNAME, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLeases4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET4);

    // Provide empty binding array because our query has no parameters in
    // WHERE clause.
    PsqlBindArray bind_array;
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLeases4(const IOAddress& lower_bound_address,
                          const LeasePageSize& page_size) const {
    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_PAGE4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    // Prepare WHERE clause
    PsqlBindArray bind_array;

    // Bind lower bound address
    std::string lb_address_data = boost::lexical_cast<std::string>(lower_bound_address.toUint32());
    bind_array.add(lb_address_data);

    // Bind page size value
    std::string page_size_data = boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    // Get the leases
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_PAGE, bind_array, result);

    return (result);
}

Lease6Ptr
PgSqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_ADDR6)
        .arg(addr.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // LEASE ADDRESS
    std::string addr_str = addr.toText();
    bind_array.add(addr_str);

    // LEASE_TYPE
    std::string type_str_ = boost::lexical_cast<std::string>(lease_type);
    bind_array.add(type_str_);

    // ... and get the data
    Lease6Ptr result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE6_ADDR, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_IAID_DUID)
        .arg(iaid)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // DUID
    bind_array.add(duid.getDuid());

    // IAID
    std::string iaid_str = PgSqlLease6Exchange::Uiaid(iaid).dbInputString();
    bind_array.add(iaid_str);

    // LEASE_TYPE
    std::string lease_type_str = boost::lexical_cast<std::string>(lease_type);
    bind_array.add(lease_type_str);

    // ... and get the data
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_DUID_IAID, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_IAID_SUBID_DUID)
        .arg(iaid)
        .arg(subnet_id)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // LEASE_TYPE
    std::string lease_type_str = boost::lexical_cast<std::string>(lease_type);
    bind_array.add(lease_type_str);

    // DUID
    bind_array.add(duid.getDuid());

    // IAID
    std::string iaid_str = PgSqlLease6Exchange::Uiaid(iaid).dbInputString();
    bind_array.add(iaid_str);

    // SUBNET ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // ... and get the data
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_DUID_IAID_SUBID, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_SUBID6)
        .arg(subnet_id);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // SUBNET_ID
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // ... and get the data
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_SUBID, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(SubnetID subnet_id,
                          const IOAddress& lower_bound_address,
                          const LeasePageSize& page_size) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_PAGE6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(subnet_id);

    // Expecting IPv6 valid address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 start address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    Lease6Collection result;
    // Prepare WHERE clause
    PsqlBindArray bind_array;

    // Bind subnet id.
    std::string subnet_id_str = boost::lexical_cast<std::string>(subnet_id);
    bind_array.add(subnet_id_str);

    // Bind lower bound address
    std::string lb_address_str = lower_bound_address.toText();
    bind_array.add(lb_address_str);

    // Bind page size value
    std::string page_size_data =
    boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Get the leases
    getLeaseCollection(ctx, GET_LEASE6_SUBID_PAGE, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(const DUID& duid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_DUID)
        .arg(duid.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // DUID
    bind_array.add(duid.getDuid());
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // query to fetch the data
    getLeaseCollection(ctx, GET_LEASE6_DUID, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_HOSTNAME6)
        .arg(hostname);

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    // Hostname
    bind_array.add(hostname);

    // ... and get the data
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_HOSTNAME, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET6);

    // Provide empty binding array because our query has no parameters in
    // WHERE clause.
    PsqlBindArray bind_array;
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6, bind_array, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(const IOAddress& lower_bound_address,
                          const LeasePageSize& page_size) const {
    // Expecting IPv6 address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_PAGE6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    // Prepare WHERE clause
    PsqlBindArray bind_array;

    // Bind lower bound address
    std::string lb_address_data = lower_bound_address.toText();
    bind_array.add(lb_address_data);

    // Bind page size value
    std::string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    // Get the leases
    Lease6Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_PAGE, bind_array, result);

    return (result);
}

void
PgSqlLeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_EXPIRED4)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE4_EXPIRE);
}

void
PgSqlLeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_EXPIRED6)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE6_EXPIRE);
}

template<typename LeaseCollection>
void
PgSqlLeaseMgr::getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                      const size_t max_leases,
                                      StatementIndex statement_index) const {
    PsqlBindArray bind_array;

    // Exclude reclaimed leases.
    std::string state_str = boost::lexical_cast<std::string>(Lease::STATE_EXPIRED_RECLAIMED);
    bind_array.add(state_str);

    // Expiration timestamp.
    std::string timestamp_str = PgSqlLeaseExchange::convertToDatabaseTime(time(0));
    bind_array.add(timestamp_str);

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    uint32_t limit = max_leases > 0 ? static_cast<uint32_t>(max_leases) :
        std::numeric_limits<uint32_t>::max();
    std::string limit_str = boost::lexical_cast<std::string>(limit);
    bind_array.add(limit_str);

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Retrieve leases from the database.
    getLeaseCollection(ctx, statement_index, bind_array, expired_leases);
}

template<typename LeasePtr>
void
PgSqlLeaseMgr::updateLeaseCommon(PgSqlLeaseContextPtr& ctx,
                                 StatementIndex stindex,
                                 PsqlBindArray& bind_array,
                                 const LeasePtr& lease) {
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);

    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));

    // Check success case first as it is the most likely outcome.
    if (affected_rows == 1) {
        return;
    }

    // If no rows affected, lease doesn't exist.
    if (affected_rows == 0) {
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_.toText() << " as it does not exist");
    }

    // Should not happen - primary key constraint should only have selected
    // one row.
    isc_throw(DbOperationError, "apparently updated more than one lease "
              "that had the address " << lease->addr_.toText());
}

void
PgSqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_UPDATE_ADDR4)
        .arg(lease->addr_.toText());

    // Get a context
    PgSqlLeaseTrackingContextAlloc get_context(*this, lease);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Create the BIND array for the data being updated
    PsqlBindArray bind_array;
    ctx->exchange4_->createBindForSend(lease, bind_array);

    // Set up the WHERE clause and append it to the SQL_BIND array
    std::string addr4_str = boost::lexical_cast<std::string>(lease->addr_.toUint32());
    bind_array.add(addr4_str);

    std::string expire_str;
    // Avoid overflow (see createBindForSend)
    if (lease->current_valid_lft_ == Lease::INFINITY_LFT) {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_, 0);
    } else {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_,
                                                               lease->current_valid_lft_);
    }
    bind_array.add(expire_str);

    // Drop to common update code
    updateLeaseCommon(ctx, stindex, bind_array, lease);

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackUpdateLease(lease);
    }
}

void
PgSqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_UPDATE_ADDR6)
        .arg(lease->addr_.toText())
        .arg(lease->type_);

    // Get the recorded action and reset it.
    Lease6::ExtendedInfoAction recorded_action = lease->extended_info_action_;
    lease->extended_info_action_ = Lease6::ACTION_IGNORE;

    // Get a context
    PgSqlLeaseTrackingContextAlloc get_context(*this, lease);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Create the BIND array for the data being updated
    PsqlBindArray bind_array;
    ctx->exchange6_->createBindForSend(lease, bind_array);

    // Set up the WHERE clause and append it to the BIND array
    std::string addr_str = lease->addr_.toText();
    bind_array.add(addr_str);

    std::string expire_str;
    // Avoid overflow (see createBindForSend)
    if (lease->current_valid_lft_ == Lease::INFINITY_LFT) {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_, 0);
    } else {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_,
                                                               lease->current_valid_lft_);
    }
    bind_array.add(expire_str);

    // Drop to common update code
    updateLeaseCommon(ctx, stindex, bind_array, lease);

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();

    // Update extended info tables.
    if (getExtendedInfoTablesEnabled()) {
        switch (recorded_action) {
        case Lease6::ACTION_IGNORE:
            break;

        case Lease6::ACTION_DELETE:
            deleteExtendedInfo6(lease->addr_);
            break;

        case Lease6::ACTION_UPDATE:
            deleteExtendedInfo6(lease->addr_);
            static_cast<void>(addExtendedInfo6(lease));
            break;
        }
    }

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackUpdateLease(lease);
    }
}

uint64_t
PgSqlLeaseMgr::deleteLeaseCommon(PgSqlLeaseContextPtr& ctx,
                                 StatementIndex stindex,
                                 PsqlBindArray& bind_array) {
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));

    return (affected_rows);
}

bool
PgSqlLeaseMgr::deleteLease(const Lease4Ptr& lease) {
    const IOAddress& addr = lease->addr_;
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_DELETE_ADDR)
        .arg(addr.toText());

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    std::string addr4_str = boost::lexical_cast<std::string>(addr.toUint32());
    bind_array.add(addr4_str);

    std::string expire_str;
    // Avoid overflow (see createBindForSend)
    if (lease->current_valid_lft_ == Lease::INFINITY_LFT) {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_, 0);
    } else {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_,
                                                               lease->current_valid_lft_);
    }
    bind_array.add(expire_str);

    // Get a context
    PgSqlLeaseTrackingContextAlloc get_context(*this, lease);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    auto affected_rows = deleteLeaseCommon(ctx, DELETE_LEASE4, bind_array);

    // Check success case first as it is the most likely outcome.
    if (affected_rows == 1) {
        if (hasCallbacks()) {
            trackDeleteLease(lease);
        }
        return (true);
    }

    // If no rows affected, lease doesn't exist.
    if (affected_rows == 0) {
        return (false);
    }

    // Should not happen - primary key constraint should only have selected
    // one row.
    isc_throw(DbOperationError, "apparently deleted more than one lease "
              "that had the address " << lease->addr_.toText());
}

bool
PgSqlLeaseMgr::deleteLease(const Lease6Ptr& lease) {
    const IOAddress& addr = lease->addr_;
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_DELETE_ADDR)
        .arg(addr.toText());

    lease->extended_info_action_ = Lease6::ACTION_IGNORE;

    // Set up the WHERE clause value
    PsqlBindArray bind_array;

    std::string addr6_str = addr.toText();
    bind_array.add(addr6_str);

    std::string expire_str;
    // Avoid overflow (see createBindForSend)
    if (lease->current_valid_lft_ == Lease::INFINITY_LFT) {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_, 0);
    } else {
        expire_str = PgSqlLeaseExchange::convertToDatabaseTime(lease->current_cltt_,
                                                               lease->current_valid_lft_);
    }
    bind_array.add(expire_str);

    // Get a context
    PgSqlLeaseTrackingContextAlloc get_context(*this, lease);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    auto affected_rows = deleteLeaseCommon(ctx, DELETE_LEASE6, bind_array);

    // Check success case first as it is the most likely outcome.
    if (affected_rows == 1) {
        // Delete references from extended info tables.
        // Performed by the delete cascade.

        // Run installed callbacks.
        if (hasCallbacks()) {
            trackDeleteLease(lease);
        }
        return (true);
    }

    // If no rows affected, lease doesn't exist.
    if (affected_rows == 0) {
        return (false);
    }

    // Should not happen - primary key constraint should only have selected
    // one row.
    isc_throw(DbOperationError, "apparently deleted more than one lease "
              "that had the address " << lease->addr_.toText());
}

uint64_t
PgSqlLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE4_STATE_EXPIRED));
}

uint64_t
PgSqlLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE6_STATE_EXPIRED));
}

uint64_t
PgSqlLeaseMgr::deleteExpiredReclaimedLeasesCommon(const uint32_t secs,
                                                  StatementIndex statement_index) {
    PsqlBindArray bind_array;

    // State is reclaimed.
    std::string state_str = boost::lexical_cast<std::string>(Lease::STATE_EXPIRED_RECLAIMED);
    bind_array.add(state_str);

    // Expiration timestamp.
    std::string expiration_str = PgSqlLeaseExchange::convertToDatabaseTime(time(0) -
        static_cast<time_t>(secs));
    bind_array.add(expiration_str);

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Delete leases.
    return (deleteLeaseCommon(ctx, statement_index, bind_array));
}

string
PgSqlLeaseMgr::checkLimits(ConstElementPtr const& user_context, StatementIndex const stindex) const {
    // No user context means no limits means allocation allowed means empty string.
    if (!user_context) {
        return string();
    }

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx(get_context.ctx_);

    // Create bindings.
    PsqlBindArray bind_array;
    std::string const user_context_str(user_context->str());
    bind_array.add(user_context_str);

    // Execute the select.
    PgSqlResult r(PQexecPrepared(ctx->conn_,
                                 tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));
    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);

    std::string limits;
    PgSqlExchange::getColumnValue(r, 0, 0, limits);
    return limits;
}

string
PgSqlLeaseMgr::checkLimits4(ConstElementPtr const& user_context) const {
    return checkLimits(user_context, CHECK_LEASE4_LIMITS);
}

string
PgSqlLeaseMgr::checkLimits6(ConstElementPtr const& user_context) const {
    return checkLimits(user_context, CHECK_LEASE6_LIMITS);
}

bool
PgSqlLeaseMgr::isJsonSupported() const {
    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx(get_context.ctx_);

    // Execute the select.
    StatementIndex const stindex(IS_JSON_SUPPORTED);
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 0, 0, 0, 0, 0));
    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);

    bool json_supported;
    PgSqlExchange::getColumnValue(r, 0, 0, json_supported);
    return json_supported;
}

size_t
PgSqlLeaseMgr::getClassLeaseCount(const ClientClass& client_class,
                                  const Lease::Type& ltype /* = Lease::TYPE_V4*/) const {
    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx(get_context.ctx_);

    // Create bindings.
    PsqlBindArray bind_array;
    bind_array.add(client_class);
    if (ltype != Lease::TYPE_V4) {
        bind_array.add(ltype);
    }

    // Execute the select.
    StatementIndex const stindex(ltype == Lease::TYPE_V4 ? GET_LEASE4_COUNT_BY_CLASS :
                                                           GET_LEASE6_COUNT_BY_CLASS);
    PgSqlResult r(PQexecPrepared(ctx->conn_,
                                 tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));
    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);

    int rows = PQntuples(r);
    if (rows == 0) {
        // No entries means 0 leases.
        return 0;
    }

    size_t count;
    PgSqlExchange::getColumnValue(r, 0, 0, count);
    return count;
}

void
PgSqlLeaseMgr::recountClassLeases4() {
    isc_throw(NotImplemented, "PgSqlLeaseMgr::recountClassLeases4() not implemented");
}

void
PgSqlLeaseMgr::recountClassLeases6() {
    isc_throw(NotImplemented, "PgSqlLeaseMgr::recountClassLeases6() not implemented");
}

void
PgSqlLeaseMgr::clearClassLeaseCounts() {
    isc_throw(NotImplemented, "PgSqlLeaseMgr::clearClassLeaseCounts() not implemented");
}

void
PgSqlLeaseMgr::writeLeases4(const std::string&) {
    isc_throw(NotImplemented, "PgSqlLeaseMgr::writeLeases4() not implemented");
}

void
PgSqlLeaseMgr::writeLeases6(const std::string&) {
    isc_throw(NotImplemented, "PgSqlLeaseMgr::writeLeases6() not implemented");
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startLeaseStatsQuery4() {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[ALL_LEASE4_STATS],
                                                      false));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startPoolLeaseStatsQuery4() {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[ALL_POOL_LEASE4_STATS],
                                                      false, true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[SUBNET_LEASE4_STATS],
                                                      false,
                                                      subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                                const SubnetID& last_subnet_id) {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[SUBNET_RANGE_LEASE4_STATS],
                                                      false,
                                                      first_subnet_id,
                                                      last_subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startLeaseStatsQuery6() {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[ALL_LEASE6_STATS],
                                                      true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startPoolLeaseStatsQuery6() {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[ALL_POOL_LEASE6_STATS],
                                                      true, true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[SUBNET_LEASE6_STATS],
                                                      true,
                                                      subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
PgSqlLeaseMgr::startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                                const SubnetID& last_subnet_id) {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new PgSqlLeaseStatsQuery(ctx->conn_,
                                                      tagged_statements[SUBNET_RANGE_LEASE6_STATS],
                                                      true,
                                                      first_subnet_id,
                                                      last_subnet_id));
    query->start();
    return(query);
}

size_t
PgSqlLeaseMgr::wipeLeases4(const SubnetID& /*subnet_id*/) {
    isc_throw(NotImplemented, "wipeLeases4 is not implemented for PostgreSQL backend");
}

size_t
PgSqlLeaseMgr::wipeLeases6(const SubnetID& /*subnet_id*/) {
    isc_throw(NotImplemented, "wipeLeases6 is not implemented for PostgreSQL backend");
}

std::string
PgSqlLeaseMgr::getName() const {
    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    std::string name = "";
    try {
        name = ctx->conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string
PgSqlLeaseMgr::getDescription() const {
    return (std::string("PostgreSQL Database"));
}

std::pair<uint32_t, uint32_t>
PgSqlLeaseMgr::getVersion(const string& timer_name) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_VERSION);

    IOServiceAccessorPtr ac(new IOServiceAccessor(&DatabaseConnection::getIOService));
    DbCallback cb(&PgSqlLeaseMgr::dbReconnect);

    return (PgSqlConnection::getVersion(parameters_, ac, cb, timer_name));
}

void
PgSqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_COMMIT);
}

void
PgSqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_ROLLBACK);
}

void
PgSqlLeaseMgr::deleteExtendedInfo6(const IOAddress& addr) {
    deleteRelayId6(addr);
    deleteRemoteId6(addr);
}

void
PgSqlLeaseMgr::deleteRelayId6(const IOAddress& addr) {
    // Set up the WHERE clause value.
    PsqlBindArray bind_array;

    std::string addr_data = addr.toText();
    bind_array.add(addr_data);

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Delete from lease6_relay_id table.
    StatementIndex stindex = DELETE_RELAY_ID6;

    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }
}

void
PgSqlLeaseMgr::deleteRemoteId6(const IOAddress& addr) {
    // Set up the WHERE clause value.
    PsqlBindArray bind_array;

    std::string addr_data = addr.toText();
    bind_array.add(addr_data);

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Delete from lease6_remote_id table.
    StatementIndex stindex = DELETE_REMOTE_ID6;

    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }
}

void
PgSqlLeaseMgr::addRelayId6(const IOAddress& lease_addr,
                           const vector<uint8_t>& relay_id) {
    // Set up the WHERE clause value.
    PsqlBindArray bind_array;

    // Bind the relay id.
    if (relay_id.empty()) {
        isc_throw(BadValue, "empty relay id");
    }
    bind_array.add(relay_id);

    // Bind the lease address.
    std::string lease_addr_data = lease_addr.toText();
    bind_array.add(lease_addr_data);

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Add to lease6_remote_id table.
    StatementIndex stindex =  ADD_RELAY_ID6;

    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }
}

void
PgSqlLeaseMgr::addRemoteId6(const IOAddress& lease_addr,
                            const vector<uint8_t>& remote_id) {
    // Set up the WHERE clause value.
    PsqlBindArray bind_array;

    // Bind the remote id.
    if (remote_id.empty()) {
        isc_throw(BadValue, "empty remote id");
    }
    bind_array.add(remote_id);

    // Bind the lease address.
    std::string lease_addr_data = lease_addr.toText();
    bind_array.add(lease_addr_data);

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    // Add to lease6_remote_id table.
    StatementIndex stindex =  ADD_REMOTE_ID6;

    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array.values_[0],
                                 &bind_array.lengths_[0],
                                 &bind_array.formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }
}

namespace {

std::string
idToText(const OptionBuffer& id) {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (auto const& it : id) {
        if (delim) {
            tmp << ":";
        }
        tmp << std::setw(2) << std::setfill('0')
            << static_cast<unsigned int>(it);
        delim = true;
    }
    return (tmp.str());
}

} // anonymous namespace

Lease4Collection
PgSqlLeaseMgr::getLeases4ByRelayId(const OptionBuffer& relay_id,
                                   const IOAddress& lower_bound_address,
                                   const LeasePageSize& page_size,
                                   const time_t& qry_start_time /* = 0 */,
                                   const time_t& qry_end_time /* = 0 */) {
    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    // Catch 2038 bug with 32 bit time_t.
    if ((qry_start_time < 0) || (qry_end_time < 0)) {
        isc_throw(BadValue, "negative time value");
    }

    bool have_qst = (qry_start_time > 0);
    bool have_qet = (qry_end_time > 0);

    // Start time must be before end time.
    if (have_qst && have_qet && (qry_start_time > qry_end_time)) {
        isc_throw(BadValue, "start time must be before end time");
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_RELAYID4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(relay_id))
        .arg(qry_start_time)
        .arg(qry_end_time);

    // Prepare WHERE clause
    PsqlBindArray bind_array;

    // Bind relay id
    if (!relay_id.empty()) {
        bind_array.add(relay_id);
    } else {
        bind_array.add("");
    }

    // Bind lower bound address
    std::string lb_address_data =
        boost::lexical_cast<std::string>(lower_bound_address.toUint32());
    bind_array.add(lb_address_data);

    // Bind query start time.
    std::string start_time_str;
    if (have_qst) {
        start_time_str = boost::lexical_cast<std::string>(qry_start_time);
        bind_array.add(start_time_str);
    }

    // Bind query end time.
    std::string end_time_str;
    if (have_qet) {
        end_time_str = boost::lexical_cast<std::string>(qry_end_time);
        bind_array.add(end_time_str);
    }

    // Bind page size value
    std::string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    StatementIndex stindex = GET_LEASE4_RELAYID;
    if (have_qst && !have_qet) {
        stindex = GET_LEASE4_RELAYID_QST;
    } else if (have_qst && have_qet) {
        stindex = GET_LEASE4_RELAYID_QSET;
    } else if (!have_qst && have_qet) {
        stindex = GET_LEASE4_RELAYID_QET;
    }

    // Get the leases
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, stindex, bind_array, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLeases4ByRemoteId(const OptionBuffer& remote_id,
                                    const IOAddress& lower_bound_address,
                                    const LeasePageSize& page_size,
                                    const time_t& qry_start_time /* = 0 */,
                                    const time_t& qry_end_time /* = 0 */) {
    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    // Catch 2038 bug with 32 bit time_t.
    if ((qry_start_time < 0) || (qry_end_time < 0)) {
        isc_throw(BadValue, "negative time value");
    }

    bool have_qst = (qry_start_time > 0);
    bool have_qet = (qry_end_time > 0);

    // Start time must be before end time.
    if (have_qst && have_qet && (qry_start_time > qry_end_time)) {
        isc_throw(BadValue, "start time must be before end time");
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_REMOTEID4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(remote_id))
        .arg(qry_start_time)
        .arg(qry_end_time);

    // Prepare WHERE clause
    PsqlBindArray bind_array;

    // Bind remote id
    if (!remote_id.empty()) {
        bind_array.add(remote_id);
    } else {
        bind_array.add("");
    }

    // Bind lower bound address
    std::string lb_address_data =
        boost::lexical_cast<std::string>(lower_bound_address.toUint32());
    bind_array.add(lb_address_data);

    // Bind query start time.
    std::string start_time_str;
    if (have_qst) {
        start_time_str = boost::lexical_cast<std::string>(qry_start_time);
        bind_array.add(start_time_str);
    }

    // Bind query end time.
    std::string end_time_str;
    if (have_qet) {
        end_time_str = boost::lexical_cast<std::string>(qry_end_time);
        bind_array.add(end_time_str);
    }

    // Bind page size value
    std::string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    StatementIndex stindex = GET_LEASE4_REMOTEID;
    if (have_qst && !have_qet) {
        stindex = GET_LEASE4_REMOTEID_QST;
    } else if (have_qst && have_qet) {
        stindex = GET_LEASE4_REMOTEID_QSET;
    } else if (!have_qst && have_qet) {
        stindex = GET_LEASE4_REMOTEID_QET;
    }

    // Get the leases
    Lease4Collection result;

    // Get a context
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, stindex, bind_array, result);

    return (result);
}

size_t
PgSqlLeaseMgr::upgradeExtendedInfo4(const LeasePageSize& page_size) {
    auto check = CfgMgr::instance().getCurrentCfg()->
        getConsistency()->getExtendedInfoSanityCheck();

    size_t pages = 0;
    size_t updated = 0;
    IOAddress start_addr = IOAddress::IPV4_ZERO_ADDRESS();
    for (;;) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_PAGE)
            .arg(pages)
            .arg(start_addr.toText())
            .arg(updated);

        // Prepare WHERE clause.
        PsqlBindArray bind_array;

        // Bind start address.
        uint32_t start_addr_data = start_addr.toUint32();
        bind_array.add(start_addr_data);

        // Bind page size value.
        std::string page_size_data =
            boost::lexical_cast<std::string>(page_size.page_size_);
        bind_array.add(page_size_data);

        Lease4Collection leases;

        // Get a context.
        {
            PgSqlLeaseContextAlloc get_context(*this);
            PgSqlLeaseContextPtr ctx = get_context.ctx_;

            getLeaseCollection(ctx, GET_LEASE4_UCTX_PAGE, bind_array, leases);
        }

        if (leases.empty()) {
            // Done.
            break;
        }

        ++pages;
        start_addr = leases.back()->addr_;
        for (auto const& lease : leases) {
            ConstElementPtr previous_user_context = lease->getContext();
            vector<uint8_t> previous_relay_id = lease->relay_id_;
            vector<uint8_t> previous_remote_id = lease->remote_id_;
            if (!previous_user_context &&
                previous_relay_id.empty() &&
                previous_remote_id.empty()) {
                continue;
            }
            bool modified = upgradeLease4ExtendedInfo(lease, check);
            try {
                lease->relay_id_.clear();
                lease->remote_id_.clear();
                extractLease4ExtendedInfo(lease, false);
                if (modified ||
                    (previous_relay_id != lease->relay_id_) ||
                    (previous_remote_id != lease->remote_id_)) {
                    updateLease4(lease);
                    ++updated;
                }
            } catch (const NoSuchLease&) {
                // The lease was modified in parallel:
                // as its extended info was processed just ignore.
                continue;
            } catch (const std::exception& ex) {
                // Something when wrong, for instance extract failed.
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_ERROR)
                    .arg(lease->addr_.toText())
                    .arg(ex.what());
            }
        }
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4)
        .arg(pages)
        .arg(updated);

    return (updated);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6ByRelayId(const DUID& relay_id,
                                   const IOAddress& lower_bound_address,
                                   const LeasePageSize& page_size) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_RELAYID6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(relay_id.toText());

    // Expecting IPv6 valid address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 start address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    std::vector<uint8_t> relay_id_data = relay_id.getDuid();
    if (relay_id_data.size() == 0) {
        isc_throw(BadValue, "empty relay id");
    }

    // Set up the WHERE clause value.
    PsqlBindArray bind_array;

    // Bind the relay id.
    bind_array.add(relay_id_data);

    // Bind the lower bound address.
    std::string lb_addr_data = lower_bound_address.toText();
    bind_array.add(lb_addr_data);

    // Bind page size value.
    std::string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;
    Lease6Collection result;

    getLeaseCollection(ctx, GET_RELAY_ID6, bind_array, result);
    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6ByRemoteId(const OptionBuffer& remote_id,
                                    const IOAddress& lower_bound_address,
                                    const LeasePageSize& page_size) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_REMOTEID6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(remote_id));

    // Expecting IPv6 valid address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 start address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    if (remote_id.size() == 0) {
        isc_throw(BadValue, "empty remote id");
    }

    // Set up the WHERE clause value.
    PsqlBindArray bind_array;

    // Bind the remote id.
    bind_array.add(remote_id);

    // Bind the lower bound address.
    std::string lb_addr_data = lower_bound_address.toText();
    bind_array.add(lb_addr_data);

    // Bind page size value.
    std::string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array.add(page_size_data);

    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx = get_context.ctx_;
    Lease6Collection result;

    getLeaseCollection(ctx, GET_REMOTE_ID6, bind_array, result);
    return (result);
}

size_t
PgSqlLeaseMgr::upgradeExtendedInfo6(const LeasePageSize& page_size) {
    auto check = CfgMgr::instance().getCurrentCfg()->
        getConsistency()->getExtendedInfoSanityCheck();

    // First step is to wipe tables if enabled.
    if (getExtendedInfoTablesEnabled()) {
        wipeExtendedInfoTables6();
    }

    size_t pages = 0;
    size_t updated = 0;
    IOAddress start_addr = IOAddress::IPV6_ZERO_ADDRESS();
    for (;;) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_PAGE)
            .arg(pages)
            .arg(start_addr.toText())
            .arg(updated);

        // Prepare WHERE clause.
        PsqlBindArray bind_array;

        // Bind start address.
        std::string start_addr_str = start_addr.toText();
        bind_array.add(start_addr_str);

        // Bind page size value.
        std::string page_size_data =
            boost::lexical_cast<std::string>(page_size.page_size_);
        bind_array.add(page_size_data);

        Lease6Collection leases;

        // Get a context.
        {
            PgSqlLeaseContextAlloc get_context(*this);
            PgSqlLeaseContextPtr ctx = get_context.ctx_;

            getLeaseCollection(ctx, GET_LEASE6_UCTX_PAGE, bind_array, leases);
        }

        if (leases.empty()) {
            // Done.
            break;
        }

        ++pages;
        start_addr = leases.back()->addr_;
        for (auto const& lease : leases) {
            try {
                bool modified = upgradeLease6ExtendedInfo(lease, check);
                if (modified) {
                    updateLease6(lease);
                }
                bool added = (getExtendedInfoTablesEnabled() &&
                              addExtendedInfo6(lease));
                if (modified || added) {
                    ++updated;
                }
            } catch (const NoSuchLease&) {
                // The lease was modified in parallel:
                // as its extended info was processed just ignore.
                continue;
            } catch (const std::exception& ex) {
                // Something when wrong, for instance extract failed.
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_ERROR)
                    .arg(lease->addr_.toText())
                    .arg(ex.what());
            }
        }
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6)
        .arg(pages)
        .arg(updated);

    return (updated);
}

void
PgSqlLeaseMgr::wipeExtendedInfoTables6() {
    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx(get_context.ctx_);

    // Execute WIPE_RELAY_ID6.
    StatementIndex const stindex1 = WIPE_RELAY_ID6;
    PgSqlResult r1(PQexecPrepared(ctx->conn_, tagged_statements[stindex1].name,
                                  0, 0, 0, 0, 0));
    ctx->conn_.checkStatementError(r1, tagged_statements[stindex1]);

    // Execute WIPE_REMOTE_ID6.
    StatementIndex const stindex2 = WIPE_REMOTE_ID6;
    PgSqlResult r2(PQexecPrepared(ctx->conn_, tagged_statements[stindex2].name,
                                  0, 0, 0, 0, 0));
    ctx->conn_.checkStatementError(r2, tagged_statements[stindex2]);
}

size_t
PgSqlLeaseMgr::byRelayId6size() const {
    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx(get_context.ctx_);

    // Execute COUNT_RELAY_ID6.
    StatementIndex stindex = COUNT_RELAY_ID6;
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 0, 0, 0, 0, 0));
    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    uint64_t count;
    PgSqlExchange::getColumnValue(r, 0, 0, count);
    return (static_cast<size_t>(count));
}

size_t
PgSqlLeaseMgr::byRemoteId6size() const {
    // Get a context.
    PgSqlLeaseContextAlloc get_context(*this);
    PgSqlLeaseContextPtr ctx(get_context.ctx_);

    // Execute COUNT_REMOTE_ID6.
    StatementIndex stindex = COUNT_REMOTE_ID6;
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 0, 0, 0, 0, 0));
    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    uint64_t count;
    PgSqlExchange::getColumnValue(r, 0, 0, count);
    return (static_cast<size_t>(count));
}

}  // namespace dhcp
}  // namespace isc
