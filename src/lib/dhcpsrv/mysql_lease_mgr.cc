// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/mysql_lease_mgr.h>
#include <dhcpsrv/timer_mgr.h>
#include <mysql/mysql_connection.h>
#include <util/multi_threading_mgr.h>

#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include <boost/static_assert.hpp>
#include <mysqld_error.h>

#include <iostream>
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

/// @file
///
/// This file holds the implementation of the Lease Manager using MySQL.  The
/// implementation uses MySQL's C API, as it comes as standard with the MySQL
/// client libraries.
///
/// In general, each of the database access methods corresponds to one SQL
/// statement.  To avoid the overhead of parsing a statement every time it is
/// used, when the database is opened "prepared statements" are created -
/// essentially doing the SQL parsing up front.  Every time a method is used
/// to access data, the corresponding prepared statement is referenced. Each
/// prepared statement contains a set of placeholders for data, each
/// placeholder being for:
///
/// - data being added to the database (as in adding or updating a lease)
/// - data being retrieved from the database (as in getting lease information)
/// - selection criteria used to determine which records to update/retrieve.
///
/// All such data is associated with the prepared statement using an array of
/// MYSQL_BIND structures.  Each element in the array corresponds to one
/// parameter in the prepared statement - the first element in the array is
/// associated with the first parameter, the second element with the second
/// parameter etc.
///
/// Within this file, the setting up of the MYSQL_BIND arrays for data being
/// passed to and retrieved from the database is handled in the
/// isc::dhcp::MySqlLease4Exchange and isc::dhcp::MySqlLease6Exchange classes.
/// The classes also hold intermediate variables required for exchanging some
/// of the data.
///
/// With these exchange objects in place, many of the methods follow similar
/// logic:
/// - Set up the MYSQL_BIND array for data being transferred to/from the
///   database.  For data being transferred to the database, some of the
///   data is extracted from the lease to intermediate variables, whilst
///   in other cases the MYSQL_BIND arrays point to the data in the lease.
/// - Set up the MYSQL_BIND array for the data selection parameters.
/// - Bind these arrays to the prepared statement.
/// - Execute the statement.
/// - If there is output, copy the data from the bound variables to the output
///   lease object.

namespace {

/// @brief Maximum length of the hostname stored in DNS.
///
/// This length is restricted by the length of the domain-name carried
/// in the Client FQDN %Option (see RFC4702 and RFC4704).
const size_t HOSTNAME_MAX_LEN = 255;

/// @brief Maximum size of an IPv6 address represented as a text string.
///
/// This is 32 hexadecimal characters written in 8 groups of four, plus seven
/// colon separators.
const size_t ADDRESS6_TEXT_MAX_LEN = 39;

/// @brief Maximum length of user context.
const size_t USER_CONTEXT_MAX_LEN = 8192;

/// @brief Maximum length of the text returned by the limit checking functions.
const size_t LIMITS_TEXT_MAX_LEN = 512;

boost::array<TaggedStatement, MySqlLeaseMgr::NUM_STATEMENTS>
tagged_statements = { {
    {MySqlLeaseMgr::DELETE_LEASE4,
                    "DELETE FROM lease4 WHERE address = ? AND expire = ?"},
    {MySqlLeaseMgr::DELETE_LEASE4_STATE_EXPIRED,
                    "DELETE FROM lease4 "
                        "WHERE state = ? AND expire < ?"},
    {MySqlLeaseMgr::DELETE_LEASE6,
                    "DELETE FROM lease6 WHERE address = ? AND expire = ?"},
    {MySqlLeaseMgr::DELETE_LEASE6_STATE_EXPIRED,
                    "DELETE FROM lease6 "
                        "WHERE state = ? AND expire < ?"},
    {MySqlLeaseMgr::GET_LEASE4,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4"},
    {MySqlLeaseMgr::GET_LEASE4_ADDR,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE address = ?"},
    {MySqlLeaseMgr::GET_LEASE4_CLIENTID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE client_id = ?"},
    {MySqlLeaseMgr::GET_LEASE4_CLIENTID_SUBID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE client_id = ? AND subnet_id = ?"},
    {MySqlLeaseMgr::GET_LEASE4_HWADDR,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE hwaddr = ?"},
    {MySqlLeaseMgr::GET_LEASE4_HWADDR_SUBID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE hwaddr = ? AND subnet_id = ?"},
    {MySqlLeaseMgr::GET_LEASE4_PAGE,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE address > ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_UCTX_PAGE,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE address > ? AND user_context IS NOT NULL "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_SUBID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE subnet_id = ?"},
    {MySqlLeaseMgr::GET_LEASE4_HOSTNAME,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE hostname = ?"},
    {MySqlLeaseMgr::GET_LEASE4_EXPIRE,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE state != ? "
                            "AND valid_lifetime != 4294967295 "
                            "AND expire < ? "
                            "ORDER BY expire ASC "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_RELAYID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE relay_id = ? and address > ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_RELAYID_QST,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE relay_id = ? and address > ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " >= ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_RELAYID_QSET,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE relay_id = ? and address > ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " >= ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " <= ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_RELAYID_QET,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE relay_id = ? and address > ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " <= ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_REMOTEID,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE remote_id = ? and address > ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_REMOTEID_QST,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE remote_id = ? and address > ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " >= ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_REMOTEID_QSET,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE remote_id = ? and address > ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " >= ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " <= ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE4_REMOTEID_QET,
                    "SELECT address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id "
                            "FROM lease4 "
                            "WHERE remote_id = ? and address > ? "
                            " and UNIX_TIMESTAMP(expire) - IF"
                             "(valid_lifetime = 4294967295, 0, valid_lifetime)"
                             " <= ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE6,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6"},
    {MySqlLeaseMgr::GET_LEASE6_ADDR,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE address = ? AND lease_type = ?"},
    {MySqlLeaseMgr::GET_LEASE6_DUID_IAID,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE duid = ? AND iaid = ? AND lease_type = ?"},
    {MySqlLeaseMgr::GET_LEASE6_DUID_IAID_SUBID,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE duid = ? AND iaid = ? AND subnet_id = ? "
                            "AND lease_type = ?"},
    {MySqlLeaseMgr::GET_LEASE6_PAGE,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE address > ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE6_UCTX_PAGE,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE address > ? AND user_context IS NOT NULL "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE6_SUBID,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE subnet_id = ?"},
    {MySqlLeaseMgr::GET_LEASE6_DUID,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE duid = ?"},
    {MySqlLeaseMgr::GET_LEASE6_HOSTNAME,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE hostname = ?"},
    {MySqlLeaseMgr::GET_LEASE6_EXPIRE,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE state != ? "
                            "AND valid_lifetime != 4294967295 "
                            "AND expire < ? "
                            "ORDER BY expire ASC "
                            "LIMIT ?"},
    {MySqlLeaseMgr::GET_LEASE6_LINK,
                    "SELECT address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id "
                            "FROM lease6 "
                            "WHERE address BETWEEN ? AND ? "
                            "ORDER BY address "
                            "LIMIT ?"},
    {MySqlLeaseMgr::INSERT_LEASE4,
                    "INSERT INTO lease4(address, hwaddr, client_id, "
                        "valid_lifetime, expire, subnet_id, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "state, user_context, relay_id, remote_id, pool_id) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"},
    {MySqlLeaseMgr::INSERT_LEASE6,
                    "INSERT INTO lease6(address, duid, valid_lifetime, "
                        "expire, subnet_id, pref_lifetime, "
                        "lease_type, iaid, prefix_len, "
                        "fqdn_fwd, fqdn_rev, hostname, "
                        "hwaddr, hwtype, hwaddr_source, "
                        "state, user_context, pool_id) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"},
    {MySqlLeaseMgr::UPDATE_LEASE4,
                    "UPDATE lease4 SET address = ?, hwaddr = ?, "
                        "client_id = ?, valid_lifetime = ?, expire = ?, "
                        "subnet_id = ?, fqdn_fwd = ?, fqdn_rev = ?, "
                        "hostname = ?, "
                        "state = ?, user_context = ?, "
                        "relay_id = ?, remote_id = ?, pool_id = ? "
                            "WHERE address = ? AND expire = ?"},
    {MySqlLeaseMgr::UPDATE_LEASE6,
                    "UPDATE lease6 SET address = ?, duid = ?, "
                        "valid_lifetime = ?, expire = ?, subnet_id = ?, "
                        "pref_lifetime = ?, lease_type = ?, iaid = ?, "
                        "prefix_len = ?, fqdn_fwd = ?, fqdn_rev = ?, "
                        "hostname = ?, hwaddr = ?, hwtype = ?, hwaddr_source = ?, "
                        "state = ?, user_context = ?, pool_id = ? "
                            "WHERE address = ? AND expire = ?"},
    {MySqlLeaseMgr::ALL_LEASE4_STATS,
                    "SELECT subnet_id, state, leases as state_count "
                        "FROM lease4_stat ORDER BY subnet_id, state"},
    {MySqlLeaseMgr::SUBNET_LEASE4_STATS,
                    "SELECT subnet_id, state, leases as state_count "
                        "FROM lease4_stat "
                        "WHERE subnet_id = ? "
                        "ORDER BY state"},
    {MySqlLeaseMgr::SUBNET_RANGE_LEASE4_STATS,
                    "SELECT subnet_id, state, leases as state_count "
                        "FROM lease4_stat "
                        "WHERE subnet_id >= ? and subnet_id <= ? "
                        "ORDER BY subnet_id, state"},
    {MySqlLeaseMgr::ALL_POOL_LEASE4_STATS,
                    "SELECT subnet_id, pool_id, state, leases as state_count "
                        "FROM lease4_pool_stat ORDER BY subnet_id, pool_id, state"},
    {MySqlLeaseMgr::ALL_LEASE6_STATS,
                    "SELECT subnet_id, lease_type, state, leases as state_count "
                        "FROM lease6_stat ORDER BY subnet_id, lease_type, state"},
    {MySqlLeaseMgr::SUBNET_LEASE6_STATS,
                    "SELECT subnet_id, lease_type, state, leases as state_count "
                        "FROM lease6_stat "
                        "WHERE subnet_id = ? "
                        "ORDER BY lease_type, state"},
    {MySqlLeaseMgr::SUBNET_RANGE_LEASE6_STATS,
                    "SELECT subnet_id, lease_type, state, leases as state_count "
                        "FROM lease6_stat "
                        "WHERE subnet_id >= ? and subnet_id <= ? "
                        "ORDER BY subnet_id, lease_type, state"},
    {MySqlLeaseMgr::ALL_POOL_LEASE6_STATS,
                    "SELECT subnet_id, pool_id, lease_type, state, leases as state_count "
                        "FROM lease6_pool_stat ORDER BY subnet_id, pool_id, lease_type, state"},
    {MySqlLeaseMgr::CHECK_LEASE4_LIMITS,
                    "SELECT checkLease4Limits(?)"},
    {MySqlLeaseMgr::CHECK_LEASE6_LIMITS,
                    "SELECT checkLease6Limits(?)"},
    {MySqlLeaseMgr::IS_JSON_SUPPORTED,
                    "SELECT isJsonSupported()"},
    {MySqlLeaseMgr::GET_LEASE4_COUNT_BY_CLASS,
                    "SELECT leases "
                        "FROM lease4_stat_by_client_class "
                        "WHERE client_class = ?"},
    {MySqlLeaseMgr::GET_LEASE6_COUNT_BY_CLASS,
                    "SELECT leases "
                        "FROM lease6_stat_by_client_class "
                        "WHERE client_class = ? AND lease_type = ?"},
} };  // tagged_statements

}  // namespace

namespace isc {
namespace dhcp {

/// @brief Common MySQL and Lease Data Methods
///
/// The MySqlLease4Exchange and MySqlLease6Exchange classes provide the
/// functionality to set up binding information between variables in the
/// program and data extracted from the database.  This class is the common
/// base to both of them, containing some common methods.

class MySqlLeaseExchange {
public:

    /// @brief Set error indicators
    ///
    /// Sets the error indicator for each of the MYSQL_BIND elements.  It points
    /// the "error" field within an element of the input array to the
    /// corresponding element of the passed error array.
    ///
    /// @param bind Array of BIND elements
    /// @param error Array of error elements.  If there is an error in getting
    ///        data associated with one of the "bind" elements, the
    ///        corresponding element in the error array is set to MLM_TRUE.
    /// @param count Size of each of the arrays.
    static void setErrorIndicators(MYSQL_BIND* bind, my_bool* error,
                                   size_t count) {
        for (size_t i = 0; i < count; ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<my_bool*>(&error[i]);
        }
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static std::string getColumnsInError(my_bool* error, std::string* names,
                                         size_t count) {
        std::string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < count; ++i) {
            if (error[i] == MLM_TRUE) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += names[i];
            }
        }

        if (result.empty()) {
            result = "(None)";
        }

        return (result);
    }
};

/// @brief Exchange MySQL and Lease4 Data
///
/// On any MySQL operation, arrays of MYSQL_BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the MySQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all MySqlLeaseMgr::xxx4() calls where it is used.

class MySqlLease4Exchange : public MySqlLeaseExchange {
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
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlLease4Exchange() : addr4_(0), hwaddr_length_(0), hwaddr_null_(MLM_FALSE),
                            client_id_length_(0), client_id_null_(MLM_FALSE),
                            subnet_id_(0), pool_id_(0), valid_lifetime_(0),
                            fqdn_fwd_(false), fqdn_rev_(false), hostname_length_(0),
                            state_(0), user_context_length_(0),
                            user_context_null_(MLM_FALSE), relay_id_length_(0),
                            relay_id_null_(MLM_FALSE), remote_id_length_(0),
                            remote_id_null_(MLM_FALSE) {
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));
        memset(hostname_buffer_, 0, sizeof(hostname_buffer_));
        memset(user_context_, 0, sizeof(user_context_));
        memset(relay_id_buffer_, 0, sizeof(relay_id_buffer_));
        memset(remote_id_buffer_, 0, sizeof(remote_id_buffer_));
        std::fill(&error_[0], &error_[LEASE_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[ADDRESS_COL] = "address";
        columns_[HWADDR_COL] = "hwaddr";
        columns_[CLIENT_ID_COL] = "client_id";
        columns_[VALID_LIFETIME_COL] = "valid_lifetime";
        columns_[EXPIRE_COL] = "expire";
        columns_[SUBNET_ID_COL] = "subnet_id";
        columns_[FQDN_FWD_COL] = "fqdn_fwd";
        columns_[FQDN_REV_COL] = "fqdn_rev";
        columns_[HOSTNAME_COL] = "hostname";
        columns_[STATE_COL] = "state";
        columns_[USER_CONTEXT_COL] = "user_context";
        columns_[RELAY_ID_COL] = "relay_id";
        columns_[REMOTE_ID_COL] = "remote_id";
        columns_[POOL_ID_COL] = "pool_id";
        BOOST_STATIC_ASSERT(13 < LEASE_COLUMNS);
    }

    /// @brief Create MYSQL_BIND objects for Lease4 Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data in the Lease4 object to
    /// the database.
    ///
    /// @param lease Lease object to be added to the database.  None of the
    ///        fields in the lease are modified - the lease data is only read.
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const Lease4Ptr& lease) {

        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // Set up the structures for the various components of the lease4
        // structure.

        try {
            // address: uint32_t
            // The address in the Lease structure is an IOAddress object.  Convert
            // this to an integer for storage.
            addr4_ = lease_->addr_.toUint32();
            bind_[0].buffer_type = MYSQL_TYPE_LONG;
            bind_[0].buffer = reinterpret_cast<char*>(&addr4_);
            bind_[0].is_unsigned = MLM_TRUE;
            // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // hwaddr: varbinary(20) - hardware/MAC address
            HWAddrPtr hwaddr = lease_->hwaddr_;
            if (hwaddr) {
                hwaddr_ = hwaddr->hwaddr_;
                hwaddr_length_ = hwaddr->hwaddr_.size();

                // Make sure that the buffer has at least length of 1, even if
                // empty HW address is passed. This is required by some of the
                // MySQL connectors that the buffer is set to non-null value.
                // Otherwise, null value would be inserted into the database,
                // rather than empty string.
                if (hwaddr_.empty()) {
                    hwaddr_.resize(1);
                }

                bind_[1].buffer_type = MYSQL_TYPE_BLOB;
                bind_[1].buffer = reinterpret_cast<char*>(&(hwaddr_[0]));
                bind_[1].buffer_length = hwaddr_length_;
                bind_[1].length = &hwaddr_length_;
            } else {
                bind_[1].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[1].buffer = NULL;
                bind_[1].is_null = &hwaddr_null_;
            }

            // client_id: varbinary(255)
            if (lease_->client_id_) {
                client_id_ = lease_->client_id_->getClientId();
                client_id_length_ = client_id_.size();

                // Make sure that the buffer has at least length of 1, even if
                // empty client id is passed. This is required by some of the
                // MySQL connectors that the buffer is set to non-null value.
                // Otherwise, null value would be inserted into the database,
                // rather than empty string.
                if (client_id_.empty()) {
                    client_id_.resize(1);
                }

                bind_[2].buffer_type = MYSQL_TYPE_BLOB;
                bind_[2].buffer = reinterpret_cast<char*>(&client_id_[0]);
                bind_[2].buffer_length = client_id_length_;
                bind_[2].length = &client_id_length_;
                // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                                  // reasons, see memset() above
            } else {
                bind_[2].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                client_id_null_ = MLM_TRUE;
                bind_[2].buffer = NULL;
                bind_[2].is_null = &client_id_null_;
            }

            // valid lifetime: unsigned int
            bind_[3].buffer_type = MYSQL_TYPE_LONG;
            bind_[3].buffer = reinterpret_cast<char*>(&lease_->valid_lft_);
            bind_[3].is_unsigned = MLM_TRUE;
            // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // expire: timestamp
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            // Avoid overflow with infinite valid lifetime by using
            // expire = cltt_ when valid_lft_ = 0xffffffff
            uint32_t valid_lft = lease_->valid_lft_;
            if (valid_lft == Lease::INFINITY_LFT) {
                valid_lft = 0;
            }
            MySqlConnection::convertToDatabaseTime(lease_->cltt_, valid_lft,
                                                   expire_);
            bind_[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
            bind_[4].buffer = reinterpret_cast<char*>(&expire_);
            bind_[4].buffer_length = sizeof(expire_);
            // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // subnet_id: unsigned int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&lease_->subnet_id_);
            bind_[5].is_unsigned = MLM_TRUE;
            // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_fwd: boolean
            bind_[6].buffer_type = MYSQL_TYPE_TINY;
            bind_[6].buffer = reinterpret_cast<char*>(&lease_->fqdn_fwd_);
            bind_[6].is_unsigned = MLM_TRUE;
            // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_rev: boolean
            bind_[7].buffer_type = MYSQL_TYPE_TINY;
            bind_[7].buffer = reinterpret_cast<char*>(&lease_->fqdn_rev_);
            bind_[7].is_unsigned = MLM_TRUE;
            // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // hostname: varchar(255)
            // Note that previously we used MYSQL_TYPE_VARCHAR instead of
            // MYSQL_TYPE_STRING. However, that caused 'buffer type not supported'
            // errors on some systems running MariaDB.
            bind_[8].buffer_type = MYSQL_TYPE_STRING;
            bind_[8].buffer = const_cast<char*>(lease_->hostname_.c_str());
            bind_[8].buffer_length = lease_->hostname_.length();
            // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // state: uint32_t
            bind_[9].buffer_type = MYSQL_TYPE_LONG;
            bind_[9].buffer = reinterpret_cast<char*>(&lease_->state_);
            bind_[9].is_unsigned = MLM_TRUE;
            // bind_[9].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // user_context: text
            ConstElementPtr ctx = lease->getContext();
            if (ctx) {
                bind_[10].buffer_type = MYSQL_TYPE_STRING;
                std::string ctx_txt = ctx->str();
                strncpy(user_context_, ctx_txt.c_str(), USER_CONTEXT_MAX_LEN - 1);
                bind_[10].buffer = user_context_;
                bind_[10].buffer_length = ctx_txt.length();
                // bind_[10].is_null = &MLM_FALSE; // commented out for performance
                                                   // reasons, see memset() above
            } else {
                bind_[10].buffer_type = MYSQL_TYPE_NULL;
            }

            // relay_id: varbinary(255)
            relay_id_ = lease_->relay_id_;
            if (!relay_id_.empty()) {
                bind_[11].buffer_type = MYSQL_TYPE_BLOB;
                bind_[11].buffer = reinterpret_cast<char*>(&relay_id_[0]);
                relay_id_length_ = relay_id_.size();
                bind_[11].buffer_length = relay_id_length_;
                bind_[11].length = &relay_id_length_;
            } else {
                bind_[11].buffer_type = MYSQL_TYPE_NULL;
                relay_id_null_ = MLM_TRUE;
                bind_[11].buffer = NULL;
                bind_[11].is_null = &relay_id_null_;
            }

            // remote_id: varbinary(255)
            remote_id_ = lease_->remote_id_;
            if (!remote_id_.empty()) {
                bind_[12].buffer_type = MYSQL_TYPE_BLOB;
                bind_[12].buffer = reinterpret_cast<char*>(&remote_id_[0]);
                remote_id_length_ = remote_id_.size();
                bind_[12].buffer_length = remote_id_length_;
                bind_[12].length = &remote_id_length_;
            } else {
                bind_[12].buffer_type = MYSQL_TYPE_NULL;
                remote_id_null_ = MLM_TRUE;
                bind_[12].buffer = NULL;
                bind_[12].is_null = &remote_id_null_;
            }

            // pool_id: unsigned int
            // Can use lease_->pool_id_ directly as it is of type uint32_t.
            bind_[13].buffer_type = MYSQL_TYPE_LONG;
            bind_[13].buffer = reinterpret_cast<char*>(&lease_->pool_id_);
            bind_[13].is_unsigned = MLM_TRUE;
            // bind_[13].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // Add the error flags
            setErrorIndicators(bind_, error_, LEASE_COLUMNS);

            // .. and check that we have the numbers correct at compile time.
            BOOST_STATIC_ASSERT(13 < LEASE_COLUMNS);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease4: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease4 data from the database.
    /// After data is successfully received, getLeaseData() can be used to copy
    /// it to a Lease6 object.
    std::vector<MYSQL_BIND> createBindForReceive() {

        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // address: uint32_t
        bind_[0].buffer_type = MYSQL_TYPE_LONG;
        bind_[0].buffer = reinterpret_cast<char*>(&addr4_);
        bind_[0].is_unsigned = MLM_TRUE;
        // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // hwaddr: varbinary(20)
        hwaddr_length_ = sizeof(hwaddr_buffer_);
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(hwaddr_buffer_);
        bind_[1].buffer_length = hwaddr_length_;
        bind_[1].length = &hwaddr_length_;
        // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // client_id: varbinary(255)
        client_id_length_ = sizeof(client_id_buffer_);
        bind_[2].buffer_type = MYSQL_TYPE_BLOB;
        bind_[2].buffer = reinterpret_cast<char*>(client_id_buffer_);
        bind_[2].buffer_length = client_id_length_;
        bind_[2].length = &client_id_length_;
        bind_[2].is_null = &client_id_null_;
        // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // valid lifetime: unsigned int
        bind_[3].buffer_type = MYSQL_TYPE_LONG;
        bind_[3].buffer = reinterpret_cast<char*>(&valid_lifetime_);
        bind_[3].is_unsigned = MLM_TRUE;
        // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // expire: timestamp
        bind_[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_[4].buffer = reinterpret_cast<char*>(&expire_);
        bind_[4].buffer_length = sizeof(expire_);
        // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // subnet_id: unsigned int
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&subnet_id_);
        bind_[5].is_unsigned = MLM_TRUE;
        // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_fwd: boolean
        bind_[6].buffer_type = MYSQL_TYPE_TINY;
        bind_[6].buffer = reinterpret_cast<char*>(&fqdn_fwd_);
        bind_[6].is_unsigned = MLM_TRUE;
        // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_rev: boolean
        bind_[7].buffer_type = MYSQL_TYPE_TINY;
        bind_[7].buffer = reinterpret_cast<char*>(&fqdn_rev_);
        bind_[7].is_unsigned = MLM_TRUE;
        // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // hostname: varchar(255)
        // Note that previously we used MYSQL_TYPE_VARCHAR instead of
        // MYSQL_TYPE_STRING. However, that caused 'buffer type not supported'
        // errors on some systems running MariaDB.
        hostname_length_ = sizeof(hostname_buffer_);
        bind_[8].buffer_type = MYSQL_TYPE_STRING;
        bind_[8].buffer = reinterpret_cast<char*>(hostname_buffer_);
        bind_[8].buffer_length = hostname_length_;
        bind_[8].length = &hostname_length_;
        // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // state: uint32_t
        bind_[9].buffer_type = MYSQL_TYPE_LONG;
        bind_[9].buffer = reinterpret_cast<char*>(&state_);
        bind_[9].is_unsigned = MLM_TRUE;
        // bind_[9].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // user_context: text
        user_context_null_ = MLM_FALSE;
        user_context_length_ = sizeof(user_context_);
        bind_[10].buffer_type = MYSQL_TYPE_STRING;
        bind_[10].buffer = reinterpret_cast<char*>(user_context_);
        bind_[10].buffer_length = user_context_length_;
        bind_[10].length = &user_context_length_;
        bind_[10].is_null = &user_context_null_;

        // relay_id: varbinary(255)
        relay_id_length_ = sizeof(relay_id_buffer_);
        bind_[11].buffer_type = MYSQL_TYPE_BLOB;
        bind_[11].buffer = reinterpret_cast<char*>(relay_id_buffer_);
        bind_[11].buffer_length = relay_id_length_;
        bind_[11].length = &relay_id_length_;
        bind_[11].is_null = &relay_id_null_;

        // remote_id: varbinary(255)
        remote_id_length_ = sizeof(remote_id_buffer_);
        bind_[12].buffer_type = MYSQL_TYPE_BLOB;
        bind_[12].buffer = reinterpret_cast<char*>(remote_id_buffer_);
        bind_[12].buffer_length = remote_id_length_;
        bind_[12].length = &remote_id_length_;
        bind_[12].is_null = &remote_id_null_;

        // pool_id: unsigned int
        bind_[13].buffer_type = MYSQL_TYPE_LONG;
        bind_[13].buffer = reinterpret_cast<char*>(&pool_id_);
        bind_[13].is_unsigned = MLM_TRUE;
        // bind_[13].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // Add the error flags
        setErrorIndicators(bind_, error_, LEASE_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(13 < LEASE_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Copy Received Data into Lease4 Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a Lease4 object.
    ///
    /// @return Lease4Ptr Pointer to a Lease6 object holding the relevant
    ///         data.
    Lease4Ptr getLeaseData() {
        // Convert times received from the database to times for the lease
        // structure. See the expire code of createBindForSend for
        // the infinite valid lifetime special case.
        time_t cltt = 0;
        // Recover from overflow
        uint32_t valid_lft = valid_lifetime_;
        if (valid_lft == Lease::INFINITY_LFT) {
            valid_lft = 0;
        }
        MySqlConnection::convertFromDatabaseTime(expire_, valid_lft, cltt);

        if (client_id_null_ == MLM_TRUE) {
            // There's no client-id, so we pass client-id_length_ set to 0
            client_id_length_ = 0;
        }

        // Hostname is passed to Lease4 as a string object. We have to create
        // it from the buffer holding hostname and the buffer length.
        std::string hostname(hostname_buffer_,
                             hostname_buffer_ + hostname_length_);

        // Set hardware address if it was set
        HWAddrPtr hwaddr;
        if (hwaddr_null_ == MLM_FALSE) {
            hwaddr.reset(new HWAddr(hwaddr_buffer_, hwaddr_length_, HTYPE_ETHER));
        }

        // Convert user_context to string as well.
        std::string user_context;
        if (user_context_null_ == MLM_FALSE) {
            user_context_[user_context_length_] = '\0';
            user_context.assign(user_context_);
        }

        // Set the user context if there is one.
        ConstElementPtr ctx;
        if (!user_context.empty()) {
            ctx = Element::fromJSON(user_context);
            if (!ctx || (ctx->getType() != Element::map)) {
                isc_throw(BadValue, "user context '" << user_context
                          << "' is not a JSON map");
            }
        }

        Lease4Ptr lease(boost::make_shared<Lease4>(addr4_, hwaddr,
                                                   client_id_buffer_,
                                                   client_id_length_,
                                                   valid_lifetime_, cltt,
                                                   subnet_id_, fqdn_fwd_,
                                                   fqdn_rev_, hostname));

        // Set state.
        lease->state_ = state_;

        if (ctx) {
            lease->setContext(ctx);
        }

        // Set relay id if it was set.
        if (relay_id_null_ == MLM_FALSE) {
            lease->relay_id_.assign(relay_id_buffer_,
                                    relay_id_buffer_ + relay_id_length_);
        }

        // Set remote id if it was set.
        if (remote_id_null_ == MLM_FALSE) {
            lease->remote_id_.assign(remote_id_buffer_,
                                     remote_id_buffer_ + remote_id_length_);
        }

        // Set pool ID
        lease->pool_id_ = pool_id_;

        return (lease);
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    std::string getErrorColumns() {
        return (getColumnsInError(error_, columns_, LEASE_COLUMNS));
    }

private:

    // Note: All array lengths are equal to the corresponding variable in the
    //       schema.
    // Note: Arrays are declared fixed length for speed of creation
    uint32_t             addr4_;                                         ///< IPv4 address
    MYSQL_BIND           bind_[LEASE_COLUMNS];                           ///< Bind array
    std::string          columns_[LEASE_COLUMNS];                        ///< Column names
    my_bool              error_[LEASE_COLUMNS];                          ///< Error array
    Lease4Ptr            lease_;                                         ///< Pointer to lease object
    std::vector<uint8_t> hwaddr_;                                        ///< Hardware address
    uint8_t              hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];         ///< Hardware address buffer
    unsigned long        hwaddr_length_;                                 ///< Length of Hardware address
    my_bool              hwaddr_null_;                                   ///< Used when Hardware address is null
    std::vector<uint8_t> client_id_;                                     ///< Client identification
    uint8_t              client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN]; ///< Client ID buffer
    unsigned long        client_id_length_;                              ///< Client ID address length
    my_bool              client_id_null_;                                ///< Used when Client ID is null
    MYSQL_TIME           expire_;                                        ///< Lease expire time
    uint32_t             subnet_id_;                                     ///< Subnet identification
    uint32_t             pool_id_;                                       ///< Pool identification
    uint32_t             valid_lifetime_;                                ///< Lease time
    my_bool              fqdn_fwd_;                                      ///< Has forward DNS update been performed
    my_bool              fqdn_rev_;                                      ///< Has reverse DNS update been performed
    char                 hostname_buffer_[HOSTNAME_MAX_LEN];             ///< Client hostname
    unsigned long        hostname_length_;                               ///< Length of client hostname
    uint32_t             state_;                                         ///< Lease state
    char                 user_context_[USER_CONTEXT_MAX_LEN];            ///< User context
    unsigned long        user_context_length_;                           ///< Length of user context
    my_bool              user_context_null_;                             ///< Used when user context is null
    std::vector<uint8_t> relay_id_;                                      ///< Relay id
    uint8_t              relay_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];  ///< Relay id buffer
    unsigned long        relay_id_length_;                               ///< Relay id length
    my_bool              relay_id_null_;                                 ///< Used when Relay id is null
    std::vector<uint8_t> remote_id_;                                     ///< Remote id
    uint8_t              remote_id_buffer_[ClientId::MAX_CLIENT_ID_LEN]; ///< Remote id buffer
    unsigned long        remote_id_length_;                              ///< Remote id length
    my_bool              remote_id_null_;                                ///< Used when Remote id is null
};

/// @brief Exchange MySQL and Lease6 Data
///
/// On any MySQL operation, arrays of MYSQL_BIND structures must be built to
/// describe the parameters in the prepared statements.  Where information is
/// inserted or retrieved - INSERT, UPDATE, SELECT - a large amount of that
/// structure is identical.  This class handles the creation of that array.
///
/// Owing to the MySQL API, the process requires some intermediate variables
/// to hold things like data length etc.  This object holds those variables.
///
/// @note There are no unit tests for this class.  It is tested indirectly
/// in all MySqlLeaseMgr::xxx6() calls where it is used.

class MySqlLease6Exchange : public MySqlLeaseExchange {
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

    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlLease6Exchange() : addr6_length_(16), hwaddr_length_(0),
                            hwaddr_null_(MLM_FALSE), duid_length_(0),
                            iaid_(0), lease_type_(0), prefix_len_(0),
                            pref_lifetime_(0), subnet_id_(0), pool_id_(0),
                            valid_lifetime_(0), fqdn_fwd_(false), fqdn_rev_(false),
                            hostname_length_(0), hwtype_(0), hwaddr_source_(0),
                            state_(0), user_context_length_(0),
                            user_context_null_(MLM_FALSE) {
        memset(addr6_buffer_, 0, sizeof(addr6_buffer_));
        memset(duid_buffer_, 0, sizeof(duid_buffer_));
        memset(hostname_buffer_, 0, sizeof(hostname_buffer_));
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(user_context_, 0, sizeof(user_context_));
        std::fill(&error_[0], &error_[LEASE_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[ADDRESS_COL]  = "address";
        columns_[DUID_COL]  = "duid";
        columns_[VALID_LIFETIME_COL]  = "valid_lifetime";
        columns_[EXPIRE_COL]  = "expire";
        columns_[SUBNET_ID_COL]  = "subnet_id";
        columns_[PREF_LIFETIME_COL]  = "pref_lifetime";
        columns_[LEASE_TYPE_COL]  = "lease_type";
        columns_[IAID_COL]  = "iaid";
        columns_[PREFIX_LEN_COL]  = "prefix_len";
        columns_[FQDN_FWD_COL]  = "fqdn_fwd";
        columns_[FQDN_REV_COL] = "fqdn_rev";
        columns_[HOSTNAME_COL] = "hostname";
        columns_[HWADDR_COL] = "hwaddr";
        columns_[HWTYPE_COL] = "hwtype";
        columns_[HWADDR_SOURCE_COL] = "hwaddr_source";
        columns_[STATE_COL] = "state";
        columns_[USER_CONTEXT_COL] = "user_context";
        columns_[POOL_ID_COL] = "pool_id";
        BOOST_STATIC_ASSERT(17 < LEASE_COLUMNS);
    }

    /// @brief Create MYSQL_BIND objects for Lease6 Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data in the Lease4 object to
    /// the database.
    ///
    /// @param lease Lease object to be added to the database.
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const Lease6Ptr& lease) {
        // Store lease object to ensure it remains valid.
        lease_ = lease;

        // Ensure bind_ array clear for constructing the MYSQL_BIND structures
        // for this lease.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        try {
            // address: binary(16)
            addr6_ = lease->addr_.toBytes();
            if (addr6_.size() != 16) {
                isc_throw(DbOperationError, "lease6 address is not 16 bytes long");
            }

            addr6_length_ = 16;
            bind_[0].buffer_type = MYSQL_TYPE_BLOB;
            bind_[0].buffer = reinterpret_cast<char*>(&addr6_[0]);
            bind_[0].buffer_length = 16;
            bind_[0].length = &addr6_length_;
            // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // duid: varchar(130)
            if (!lease_->duid_) {
                isc_throw(DbOperationError, "lease6 for address " << lease->addr_.toText()
                          << " is missing mandatory client-id.");
            }
            duid_ = lease_->duid_->getDuid();
            duid_length_ = duid_.size();

            bind_[1].buffer_type = MYSQL_TYPE_BLOB;
            bind_[1].buffer = reinterpret_cast<char*>(&(duid_[0]));
            bind_[1].buffer_length = duid_length_;
            bind_[1].length = &duid_length_;
            // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // valid lifetime: unsigned int
            bind_[2].buffer_type = MYSQL_TYPE_LONG;
            bind_[2].buffer = reinterpret_cast<char*>(&lease_->valid_lft_);
            bind_[2].is_unsigned = MLM_TRUE;
            // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // expire: timestamp
            // The lease structure holds the client last transmission time (cltt_)
            // For convenience for external tools, this is converted to lease
            // expiry time (expire).  The relationship is given by:
            //
            // expire = cltt_ + valid_lft_
            // Avoid overflow with infinite valid lifetime by using
            // expire = cltt_ when valid_lft_ = 0xffffffff
            uint32_t valid_lft = lease_->valid_lft_;
            if (valid_lft == Lease::INFINITY_LFT) {
                valid_lft = 0;
            }
            MySqlConnection::convertToDatabaseTime(lease_->cltt_, valid_lft,
                                                   expire_);
            bind_[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
            bind_[3].buffer = reinterpret_cast<char*>(&expire_);
            bind_[3].buffer_length = sizeof(expire_);
            // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // subnet_id: unsigned int
            // Can use lease_->subnet_id_ directly as it is of type uint32_t.
            bind_[4].buffer_type = MYSQL_TYPE_LONG;
            bind_[4].buffer = reinterpret_cast<char*>(&lease_->subnet_id_);
            bind_[4].is_unsigned = MLM_TRUE;
            // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // pref_lifetime: unsigned int
            // Can use lease_->preferred_lft_ directly as it is of type uint32_t.
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&lease_->preferred_lft_);
            bind_[5].is_unsigned = MLM_TRUE;
            // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // lease_type: tinyint
            // Must convert to uint8_t as lease_->type_ is a LeaseType variable.
            lease_type_ = lease_->type_;
            bind_[6].buffer_type = MYSQL_TYPE_TINY;
            bind_[6].buffer = reinterpret_cast<char*>(&lease_type_);
            bind_[6].is_unsigned = MLM_TRUE;
            // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // iaid: unsigned int
            // Can use lease_->iaid_ directly as it is of type uint32_t.
            bind_[7].buffer_type = MYSQL_TYPE_LONG;
            bind_[7].buffer = reinterpret_cast<char*>(&lease_->iaid_);
            bind_[7].is_unsigned = MLM_TRUE;
            // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // prefix_len: unsigned tinyint
            // Can use lease_->prefixlen_ directly as it is uint32_t.
            bind_[8].buffer_type = MYSQL_TYPE_TINY;
            bind_[8].buffer = reinterpret_cast<char*>(&lease_->prefixlen_);
            bind_[8].is_unsigned = MLM_TRUE;
            // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_fwd: boolean
            bind_[9].buffer_type = MYSQL_TYPE_TINY;
            bind_[9].buffer = reinterpret_cast<char*>(&lease_->fqdn_fwd_);
            bind_[9].is_unsigned = MLM_TRUE;
            // bind_[9].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // fqdn_rev: boolean
            bind_[10].buffer_type = MYSQL_TYPE_TINY;
            bind_[10].buffer = reinterpret_cast<char*>(&lease_->fqdn_rev_);
            bind_[10].is_unsigned = MLM_TRUE;
            // bind_[10].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // hostname: varchar(255)
            bind_[11].buffer_type = MYSQL_TYPE_STRING;
            bind_[11].buffer = const_cast<char*>(lease_->hostname_.c_str());
            bind_[11].buffer_length = lease_->hostname_.length();
            // bind_[11].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // hwaddr: varbinary(20) - hardware/MAC address
            HWAddrPtr hwaddr = lease_->hwaddr_;
            if (hwaddr) {
                hwaddr_ = hwaddr->hwaddr_;
                hwaddr_length_ = hwaddr->hwaddr_.size();

                // Make sure that the buffer has at least length of 1, even if
                // empty HW address is passed. This is required by some of the
                // MySQL connectors that the buffer is set to non-null value.
                // Otherwise, null value would be inserted into the database,
                // rather than empty string.
                if (hwaddr_.empty()) {
                    hwaddr_.resize(1);
                }

                bind_[12].buffer_type = MYSQL_TYPE_BLOB;
                bind_[12].buffer = reinterpret_cast<char*>(&(hwaddr_[0]));
                bind_[12].buffer_length = hwaddr_length_;
                bind_[12].length = &hwaddr_length_;
            } else {
                bind_[12].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[12].buffer = NULL;
                bind_[12].is_null = &hwaddr_null_;
            }

            // hardware type: unsigned short int (16 bits)
            if (hwaddr) {
                hwtype_ = lease->hwaddr_->htype_;
                bind_[13].buffer_type = MYSQL_TYPE_SHORT;
                bind_[13].buffer = reinterpret_cast<char*>(&hwtype_);
                bind_[13].is_unsigned = MLM_TRUE;
            } else {
                hwtype_ = 0;
                bind_[13].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[13].buffer = NULL;
                bind_[13].is_null = &hwaddr_null_;
            }

            // hardware source: unsigned int (32 bits)
            if (hwaddr) {
                hwaddr_source_ = lease->hwaddr_->source_;
                bind_[14].buffer_type = MYSQL_TYPE_LONG;
                bind_[14].buffer = reinterpret_cast<char*>(&hwaddr_source_);
                bind_[14].is_unsigned = MLM_TRUE;
            } else {
                hwaddr_source_ = 0;
                bind_[14].buffer_type = MYSQL_TYPE_NULL;
                // According to http://dev.mysql.com/doc/refman/5.5/en/
                // c-api-prepared-statement-data-structures.html, the other
                // fields doesn't matter if type is set to MYSQL_TYPE_NULL,
                // but let's set them to some sane values in case earlier versions
                // didn't have that assumption.
                hwaddr_null_ = MLM_TRUE;
                bind_[14].buffer = NULL;
                bind_[14].is_null = &hwaddr_null_;
            }

            // state: uint32_t
            bind_[15].buffer_type = MYSQL_TYPE_LONG;
            bind_[15].buffer = reinterpret_cast<char*>(&lease_->state_);
            bind_[15].is_unsigned = MLM_TRUE;
            // bind_[15].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // user_context: text
            ConstElementPtr ctx = lease->getContext();
            if (ctx) {
                bind_[16].buffer_type = MYSQL_TYPE_STRING;
                std::string ctx_txt = ctx->str();
                strncpy(user_context_, ctx_txt.c_str(), USER_CONTEXT_MAX_LEN - 1);
                bind_[16].buffer = user_context_;
                bind_[16].buffer_length = ctx_txt.length();
                // bind_[16].is_null = &MLM_FALSE; // commented out for performance
                                                   // reasons, see memset() above
            } else {
                bind_[16].buffer_type = MYSQL_TYPE_NULL;
            }

            // pool_id: unsigned int
            // Can use lease_->pool_id_ directly as it is of type uint32_t.
            bind_[17].buffer_type = MYSQL_TYPE_LONG;
            bind_[17].buffer = reinterpret_cast<char*>(&lease_->pool_id_);
            bind_[17].is_unsigned = MLM_TRUE;
            // bind_[17].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // Add the error flags
            setErrorIndicators(bind_, error_, LEASE_COLUMNS);

            // .. and check that we have the numbers correct at compile time.
            BOOST_STATIC_ASSERT(17 < LEASE_COLUMNS);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Lease6: "
                      << lease_->addr_.toText() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease6 data from the database.
    /// After data is successfully received, getLeaseData() is used to copy
    /// it to a Lease6 object.
    ///
    /// @return Vector of MySQL BIND objects passed to the MySQL data retrieval
    ///         functions.
    std::vector<MYSQL_BIND> createBindForReceive() {

        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // address: binary(16)
        addr6_length_ = 16;
        bind_[0].buffer_type = MYSQL_TYPE_BLOB;
        bind_[0].buffer = reinterpret_cast<char*>(addr6_buffer_);
        bind_[0].buffer_length = addr6_length_;
        bind_[0].length = &addr6_length_;
        // bind_[0].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // duid: varbinary(130)
        duid_length_ = sizeof(duid_buffer_);
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(duid_buffer_);
        bind_[1].buffer_length = duid_length_;
        bind_[1].length = &duid_length_;
        // bind_[1].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // valid lifetime: unsigned int
        bind_[2].buffer_type = MYSQL_TYPE_LONG;
        bind_[2].buffer = reinterpret_cast<char*>(&valid_lifetime_);
        bind_[2].is_unsigned = MLM_TRUE;
        // bind_[2].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // expire: timestamp
        bind_[3].buffer_type = MYSQL_TYPE_TIMESTAMP;
        bind_[3].buffer = reinterpret_cast<char*>(&expire_);
        bind_[3].buffer_length = sizeof(expire_);
        // bind_[3].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // subnet_id: unsigned int
        bind_[4].buffer_type = MYSQL_TYPE_LONG;
        bind_[4].buffer = reinterpret_cast<char*>(&subnet_id_);
        bind_[4].is_unsigned = MLM_TRUE;
        // bind_[4].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // pref_lifetime: unsigned int
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&pref_lifetime_);
        bind_[5].is_unsigned = MLM_TRUE;
        // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // lease_type: tinyint
        bind_[6].buffer_type = MYSQL_TYPE_TINY;
        bind_[6].buffer = reinterpret_cast<char*>(&lease_type_);
        bind_[6].is_unsigned = MLM_TRUE;
        // bind_[6].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // iaid: unsigned int
        bind_[7].buffer_type = MYSQL_TYPE_LONG;
        bind_[7].buffer = reinterpret_cast<char*>(&iaid_);
        bind_[7].is_unsigned = MLM_TRUE;
        // bind_[7].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // prefix_len: unsigned tinyint
        bind_[8].buffer_type = MYSQL_TYPE_TINY;
        bind_[8].buffer = reinterpret_cast<char*>(&prefix_len_);
        bind_[8].is_unsigned = MLM_TRUE;
        // bind_[8].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_fwd: boolean
        bind_[9].buffer_type = MYSQL_TYPE_TINY;
        bind_[9].buffer = reinterpret_cast<char*>(&fqdn_fwd_);
        bind_[9].is_unsigned = MLM_TRUE;
        // bind_[9].is_null = &MLM_FALSE; // commented out for performance
                                          // reasons, see memset() above

        // fqdn_rev: boolean
        bind_[10].buffer_type = MYSQL_TYPE_TINY;
        bind_[10].buffer = reinterpret_cast<char*>(&fqdn_rev_);
        bind_[10].is_unsigned = MLM_TRUE;
        // bind_[10].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // hostname: varchar(255)
        hostname_length_ = sizeof(hostname_buffer_);
        bind_[11].buffer_type = MYSQL_TYPE_STRING;
        bind_[11].buffer = reinterpret_cast<char*>(hostname_buffer_);
        bind_[11].buffer_length = hostname_length_;
        bind_[11].length = &hostname_length_;
        // bind_[11].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // hwaddr: varbinary(20)
        hwaddr_null_ = MLM_FALSE;
        hwaddr_length_ = sizeof(hwaddr_buffer_);
        bind_[12].buffer_type = MYSQL_TYPE_BLOB;
        bind_[12].buffer = reinterpret_cast<char*>(hwaddr_buffer_);
        bind_[12].buffer_length = hwaddr_length_;
        bind_[12].length = &hwaddr_length_;
        bind_[12].is_null = &hwaddr_null_;

        // hardware type: unsigned short int (16 bits)
        bind_[13].buffer_type = MYSQL_TYPE_SHORT;
        bind_[13].buffer = reinterpret_cast<char*>(&hwtype_);
        bind_[13].is_unsigned = MLM_TRUE;

        // hardware source: unsigned int (32 bits)
        bind_[14].buffer_type = MYSQL_TYPE_LONG;
        bind_[14].buffer = reinterpret_cast<char*>(&hwaddr_source_);
        bind_[14].is_unsigned = MLM_TRUE;

        // state: uint32_t
        bind_[15].buffer_type = MYSQL_TYPE_LONG;
        bind_[15].buffer = reinterpret_cast<char*>(&state_);
        bind_[15].is_unsigned = MLM_TRUE;
        // bind_[15].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // user_context: text
        user_context_null_ = MLM_FALSE;
        user_context_length_ = sizeof(user_context_);
        bind_[16].buffer_type = MYSQL_TYPE_STRING;
        bind_[16].buffer = reinterpret_cast<char*>(user_context_);
        bind_[16].buffer_length = user_context_length_;
        bind_[16].length = &user_context_length_;
        bind_[16].is_null = &user_context_null_;

        // pool_id: unsigned int
        bind_[17].buffer_type = MYSQL_TYPE_LONG;
        bind_[17].buffer = reinterpret_cast<char*>(&pool_id_);
        bind_[17].is_unsigned = MLM_TRUE;
        // bind_[17].is_null = &MLM_FALSE; // commented out for performance
                                           // reasons, see memset() above

        // Add the error flags
        setErrorIndicators(bind_, error_, LEASE_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(17 < LEASE_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[LEASE_COLUMNS]));
    }

    /// @brief Copy Received Data into Lease6 Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a Lease6 object.
    ///
    /// @return Lease6Ptr Pointer to a Lease6 object holding the relevant
    ///         data.
    ///
    /// @throw isc::BadValue Unable to convert Lease Type value in database
    Lease6Ptr getLeaseData() {
        // Convert lease from network-order bytes to IOAddress.
        IOAddress addr = IOAddress::fromBytes(AF_INET6, addr6_buffer_);
        std::string address = addr.toText();

        // Set the lease type in a variable of the appropriate data type, which
        // has been initialized with an arbitrary (but valid) value.
        Lease::Type type = Lease::TYPE_NA;
        switch (lease_type_) {
            case Lease::TYPE_NA:
                type = Lease::TYPE_NA;
                break;

            case Lease::TYPE_TA:
                type = Lease::TYPE_TA;
                break;

            case Lease::TYPE_PD:
                type = Lease::TYPE_PD;
                break;

            default:
                isc_throw(BadValue, "invalid lease type returned (" <<
                          static_cast<int>(lease_type_) << ") for lease with "
                          << "address " << address << ". Only 0, 1, or 2 are "
                          << "allowed.");
        }

        if (type != Lease::TYPE_PD) {
            prefix_len_ = 128;
        }

        // Set up DUID,
        DuidPtr duid_ptr(new DUID(duid_buffer_, duid_length_));

        // Hostname is passed to Lease6 as a string object, so we have to
        // create it from the hostname buffer and length.
        std::string hostname(hostname_buffer_,
                             hostname_buffer_ + hostname_length_);

        // Set hardware address if it was set
        HWAddrPtr hwaddr;
        if (hwaddr_null_ == MLM_FALSE) {
            hwaddr.reset(new HWAddr(hwaddr_buffer_, hwaddr_length_, hwtype_));
            hwaddr->source_ = hwaddr_source_;
        }

        // Convert user_context to string as well.
        std::string user_context;
        if (user_context_null_ == MLM_FALSE) {
            user_context_[user_context_length_] = '\0';
            user_context.assign(user_context_);
        }

        // Set the user context if there is one.
        ConstElementPtr ctx;
        if (!user_context.empty()) {
            ctx = Element::fromJSON(user_context);
            if (!ctx || (ctx->getType() != Element::map)) {
                isc_throw(BadValue, "user context '" << user_context
                          << "' is not a JSON map");
            }
        }

        // Create the lease and set the cltt (after converting from the
        // expire time retrieved from the database).
        Lease6Ptr result(boost::make_shared<Lease6>(type, addr, duid_ptr, iaid_,
                                                    pref_lifetime_,
                                                    valid_lifetime_, subnet_id_,
                                                    fqdn_fwd_, fqdn_rev_,
                                                    hostname, hwaddr,
                                                    prefix_len_));
        time_t cltt = 0;
        // Recover from overflow (see expire code of createBindForSend).
        uint32_t valid_lft = valid_lifetime_;
        if (valid_lft == Lease::INFINITY_LFT) {
            valid_lft = 0;
        }
        MySqlConnection::convertFromDatabaseTime(expire_, valid_lft, cltt);
        // Update cltt_ and current_cltt_ explicitly.
        result->cltt_ = cltt;
        result->current_cltt_ = cltt;

        // Set state.
        result->state_ = state_;

        if (ctx) {
            result->setContext(ctx);
        }

        // Set pool ID.
        result->pool_id_ = pool_id_;

        return (result);
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    std::string getErrorColumns() {
        return (getColumnsInError(error_, columns_, LEASE_COLUMNS));
    }

private:

    // Note: All array lengths are equal to the corresponding variable in the
    // schema.
    // Note: arrays are declared fixed length for speed of creation
    std::vector<uint8_t> addr6_;                                   ///< Binary address
    uint8_t              addr6_buffer_[16];                        ///< Binary address buffer
    unsigned long        addr6_length_;                            ///< Binary address length
    MYSQL_BIND           bind_[LEASE_COLUMNS];                     ///< Bind array
    std::string          columns_[LEASE_COLUMNS];                  ///< Column names
    my_bool              error_[LEASE_COLUMNS];                    ///< Error array
    Lease6Ptr            lease_;                                   ///< Pointer to lease object
    std::vector<uint8_t> hwaddr_;                                  ///< Hardware address
    uint8_t              hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];   ///< Hardware address buffer
    unsigned long        hwaddr_length_;                           ///< Length of Hardware address
    my_bool              hwaddr_null_;                             ///< Used when Hardware address is null
    std::vector<uint8_t> duid_;                                    ///< DUID
    uint8_t              duid_buffer_[DUID::MAX_DUID_LEN];         ///< DUID buffer
    unsigned long        duid_length_;                             ///< Length of DUID
    MYSQL_TIME           expire_;                                  ///< Lease expire time
    uint32_t             iaid_;                                    ///< Identity association ID
    uint8_t              lease_type_;                              ///< Lease type
    uint8_t              prefix_len_;                              ///< Prefix length
    uint32_t             pref_lifetime_;                           ///< Preferred lifetime
    uint32_t             subnet_id_;                               ///< Subnet identification
    uint32_t             pool_id_;                                 ///< Pool identification
    uint32_t             valid_lifetime_;                          ///< Lease time
    my_bool              fqdn_fwd_;                                ///< Has forward DNS update been performed
    my_bool              fqdn_rev_;                                ///< Has reverse DNS update been performed
    char                 hostname_buffer_[HOSTNAME_MAX_LEN];       ///< Client hostname
    unsigned long        hostname_length_;                         ///< Length of client hostname
    uint16_t             hwtype_;                                  ///< Hardware type
    uint32_t             hwaddr_source_;                           ///< Source of the hardware address
    uint32_t             state_;                                   ///< Lease state
    char                 user_context_[USER_CONTEXT_MAX_LEN];      ///< User context
    unsigned long        user_context_length_;                     ///< Length of user context
    my_bool              user_context_null_;                       ///< Used when user context is null
};

/// @brief MySql derivation of the statistical lease data query
///
/// This class is used to recalculate lease statistics for MySQL
/// lease storage.  It does so by executing a query which returns a result
/// containing one row per monitored state per lease type per
/// subnet, ordered by subnet id in ascending order.

class MySqlLeaseStatsQuery : public LeaseStatsQuery {
public:

    /// @brief Constructor to query for all subnets' stats
    ///
    ///  The query created will return statistics for all subnets
    ///
    /// @param conn An open connection to the database housing the lease data
    /// @param statement_index Index of the query's prepared statement
    /// @param fetch_type Indicates if query supplies lease type
    /// @param fetch_pool Indicates if query requires pool data
    /// @throw if statement index is invalid.
    MySqlLeaseStatsQuery(MySqlConnection& conn, const size_t statement_index,
                         const bool fetch_type, const bool fetch_pool = false)
        : conn_(conn), statement_index_(statement_index), statement_(NULL),
          fetch_type_(fetch_type), fetch_pool_(fetch_pool),
          // Set the number of columns in the bind array based on fetch_type
          // This is the number of columns expected in the result set
          bind_(fetch_type_ ? (fetch_pool_ ? 5 : 4) : (fetch_pool_ ? 4 : 3)),
          subnet_id_(0), pool_id_(0), lease_type_(Lease::TYPE_NA),
          state_(Lease::STATE_DEFAULT), state_count_(0) {
          validateStatement();
    }

    /// @brief Constructor to query for a single subnet's stats
    ///
    /// The query created will return statistics for a single subnet
    ///
    /// @param conn An open connection to the database housing the lease data
    /// @param statement_index Index of the query's prepared statement
    /// @param fetch_type Indicates if query supplies lease type
    /// @param subnet_id id of the subnet for which stats are desired
    /// @throw BadValue if subnet_id given is 0 or if statement index is invalid.
    MySqlLeaseStatsQuery(MySqlConnection& conn, const size_t statement_index,
                         const bool fetch_type, const SubnetID& subnet_id)
        : LeaseStatsQuery(subnet_id), conn_(conn), statement_index_(statement_index),
          statement_(NULL), fetch_type_(fetch_type), fetch_pool_(false),
          // Set the number of columns in the bind array based on fetch_type
          // This is the number of columns expected in the result set
          bind_(fetch_type_ ? 4 : 3), subnet_id_(0), pool_id_(0),
          lease_type_(Lease::TYPE_NA), state_(Lease::STATE_DEFAULT),
          state_count_(0) {
          validateStatement();
    }

    /// @brief Constructor to query for the stats for a range of subnets
    ///
    /// The query created will return statistics for the inclusive range of
    /// subnets described by first and last subnet IDs.
    ///
    /// @param conn An open connection to the database housing the lease data
    /// @param statement_index Index of the query's prepared statement
    /// @param fetch_type Indicates if query supplies lease type
    /// @param first_subnet_id first subnet in the range of subnets
    /// @param last_subnet_id last subnet in the range of subnets
    /// @throw BadValue if either subnet ID is 0 or if last <= first or
    /// if statement index is invalid.
    MySqlLeaseStatsQuery(MySqlConnection& conn, const size_t statement_index,
                         const bool fetch_type, const SubnetID& first_subnet_id,
                         const SubnetID& last_subnet_id)
        : LeaseStatsQuery(first_subnet_id, last_subnet_id), conn_(conn),
          statement_index_(statement_index), statement_(NULL),
          fetch_type_(fetch_type), fetch_pool_(false),
          // Set the number of columns in the bind array based on fetch_type
          // This is the number of columns expected in the result set
          bind_(fetch_type_ ? 4 : 3), subnet_id_(0), pool_id_(0),
          lease_type_(Lease::TYPE_NA), state_(Lease::STATE_DEFAULT),
          state_count_(0) {
          validateStatement();
    }

    /// @brief Destructor
    virtual ~MySqlLeaseStatsQuery() {
        (void) mysql_stmt_free_result(statement_);
    }

    /// @brief Creates the IPv4 lease statistical data result set
    ///
    /// The result set is populated by executing a SQL query against the
    /// lease(4/6) table which sums the leases per lease state per lease
    /// type (v6 only) per subnet id. This method binds the statement to
    /// the output bind array and then executes the statement, and fetches
    /// entire result set.
    void start() {
        // Set up where clause inputs if needed.
        if (getSelectMode() != ALL_SUBNETS && getSelectMode() != ALL_SUBNET_POOLS) {
            MYSQL_BIND inbind[2];
            memset(inbind, 0, sizeof(inbind));

            // Add first_subnet_id used by both single and range.
            inbind[0].buffer_type = MYSQL_TYPE_LONG;
            inbind[0].buffer = reinterpret_cast<char*>(&first_subnet_id_);
            inbind[0].is_unsigned = MLM_TRUE;

            // Add last_subnet_id for range.
            if (getSelectMode() == SUBNET_RANGE) {
                inbind[1].buffer_type = MYSQL_TYPE_LONG;
                inbind[1].buffer = reinterpret_cast<char*>(&last_subnet_id_);
                inbind[1].is_unsigned = MLM_TRUE;
            }

            // Bind the parameters to the statement
            int status = mysql_stmt_bind_param(statement_, &inbind[0]);
            conn_.checkError(status, statement_index_, "unable to bind parameters");
        }

        int col = 0;
        // subnet_id: unsigned int
        bind_[col].buffer_type = MYSQL_TYPE_LONG;
        bind_[col].buffer = reinterpret_cast<char*>(&subnet_id_);
        bind_[col].is_unsigned = MLM_TRUE;
        ++col;

        // Fetch the pool id if we were told to do so.
        if (fetch_pool_) {
            // pool id: uint32_t
            bind_[col].buffer_type = MYSQL_TYPE_LONG;
            bind_[col].buffer = reinterpret_cast<char*>(&pool_id_);
            bind_[col].is_unsigned = MLM_TRUE;
            ++col;
        }

        // Fetch the lease type if we were told to do so.
        if (fetch_type_) {
            // lease type: uint32_t
            bind_[col].buffer_type = MYSQL_TYPE_LONG;
            bind_[col].buffer = reinterpret_cast<char*>(&lease_type_);
            bind_[col].is_unsigned = MLM_TRUE;
            ++col;
        } else {
            fetch_type_ = Lease::TYPE_NA;
        }

        // state: uint32_t
        bind_[col].buffer_type = MYSQL_TYPE_LONG;
        bind_[col].buffer = reinterpret_cast<char*>(&state_);
        bind_[col].is_unsigned = MLM_TRUE;
        ++col;

        // state_count_: int64_t
        bind_[col].buffer_type = MYSQL_TYPE_LONGLONG;
        bind_[col].buffer = reinterpret_cast<char*>(&state_count_);
        //bind_[col].is_unsigned = MLM_FALSE;

        // Set up the MYSQL_BIND array for the data being returned
        // and bind it to the statement.
        int status = mysql_stmt_bind_result(statement_, &bind_[0]);
        conn_.checkError(status, statement_index_, "outbound binding failed");

        // Execute the statement
        status = MysqlExecuteStatement(statement_);
        conn_.checkError(status, statement_index_, "unable to execute");

        // Ensure that all the lease information is retrieved in one go to avoid
        // overhead of going back and forth between client and server.
        status = mysql_stmt_store_result(statement_);
        conn_.checkError(status, statement_index_, "results storage failed");
    }

    /// @brief Fetches the next row in the result set
    ///
    /// Once the internal result set has been populated by invoking the
    /// the start() method, this method is used to iterate over the
    /// result set rows. Once the last row has been fetched, subsequent
    /// calls will return false.
    ///
    /// Checks against negative values for the state count and logs once
    /// a warning message. Unfortunately not getting the message is not
    /// a proof that detailed counters are correct.
    ///
    /// @param row Storage for the fetched row
    ///
    /// @return True if the fetch succeeded, false if there are no more
    /// rows to fetch.
    bool getNextRow(LeaseStatsRow& row) {
        bool have_row = false;
        int status = mysql_stmt_fetch(statement_);
        if (status == MLM_MYSQL_FETCH_SUCCESS) {
            row.subnet_id_ = static_cast<SubnetID>(subnet_id_);
            row.pool_id_ = pool_id_;
            row.lease_type_ = static_cast<Lease::Type>(lease_type_);
            row.lease_state_ = state_;
            if (state_count_ >= 0) {
                row.state_count_ = state_count_;
            } else {
                row.state_count_ = 0;
                if (!negative_count_) {
                    negative_count_ = true;
                    LOG_WARN(dhcpsrv_logger, DHCPSRV_MYSQL_NEGATIVE_LEASES_STAT);
                }
            }
            have_row = true;
        } else if (status != MYSQL_NO_DATA) {
            conn_.checkError(status, statement_index_, "getNextRow failed");
        }

        return (have_row);
    }

private:

    /// @brief Validate the statement index passed to the constructor
    /// Safely fetch the statement from the connection based on statement index
    /// @throw  BadValue if statement index is out of range
    void validateStatement() {
        if (statement_index_ >= MySqlLeaseMgr::NUM_STATEMENTS) {
            isc_throw(BadValue, "MySqlLeaseStatsQuery"
                      " - invalid statement index" << statement_index_);
        }

        statement_ = conn_.statements_[statement_index_];
    }

    /// @brief Database connection to use to execute the query
    MySqlConnection& conn_;

    /// @brief Index of the query's prepared statement
    size_t statement_index_;

    /// @brief The query's prepared statement
    MYSQL_STMT *statement_;

    /// @brief Indicates if query supplies lease type
    bool fetch_type_;

    /// @brief Indicates if query requires pool data
    bool fetch_pool_;

    /// @brief Bind array used to store the query result set;
    std::vector<MYSQL_BIND> bind_;

    /// @brief Receives subnet ID when fetching a row
    uint32_t subnet_id_;

    /// @brief Receives pool ID when fetching a row
    uint32_t pool_id_;

    /// @brief Receives the lease type when fetching a row
    uint32_t lease_type_;

    /// @brief Receives the lease state when fetching a row
    uint32_t state_;

    /// @brief Receives the state count when fetching a row
    int64_t state_count_;

    /// @brief Received negative state count showing a problem
    static bool negative_count_;
};

// Initialize negative state count flag to false.
bool MySqlLeaseStatsQuery::negative_count_ = false;

// MySqlLeaseContext Constructor

MySqlLeaseContext::MySqlLeaseContext(const DatabaseConnection::ParameterMap& parameters,
                                     IOServiceAccessorPtr io_service_accessor,
                                     DbCallback db_reconnect_callback)
    : conn_(parameters, io_service_accessor, db_reconnect_callback) {
}

// MySqlLeaseContextAlloc Constructor and Destructor

MySqlLeaseMgr::MySqlLeaseContextAlloc::MySqlLeaseContextAlloc(
    const MySqlLeaseMgr& mgr) : ctx_(), mgr_(mgr) {

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
            isc_throw(Unexpected, "No available MySQL lease context?!");
        }
        ctx_ = mgr_.pool_->pool_.back();
    }
}

MySqlLeaseMgr::MySqlLeaseContextAlloc::~MySqlLeaseContextAlloc() {
    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        lock_guard<mutex> lock(mgr_.pool_->mutex_);
        mgr_.pool_->pool_.push_back(ctx_);
    }
    // If running in single-threaded mode, there's nothing to do here.
}

// MySqlLeaseTrackingContextAlloc Constructor and Destructor

MySqlLeaseMgr::MySqlLeaseTrackingContextAlloc::MySqlLeaseTrackingContextAlloc(
    MySqlLeaseMgr& mgr, const LeasePtr& lease) : ctx_(), mgr_(mgr), lease_(lease) {

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
            isc_throw(Unexpected, "No available MySQL lease context?!");
        }
        ctx_ = mgr_.pool_->pool_.back();
    }
}

MySqlLeaseMgr::MySqlLeaseTrackingContextAlloc::~MySqlLeaseTrackingContextAlloc() {
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

void
MySqlLeaseMgr::setExtendedInfoTablesEnabled(const db::DatabaseConnection::ParameterMap& /* parameters */) {
    isc_throw(isc::NotImplemented, "extended info tables are not yet supported by mysql");
}

// MySqlLeaseMgr Constructor and Destructor

MySqlLeaseMgr::MySqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
    : TrackingLeaseMgr(), parameters_(parameters), timer_name_("") {

    // Check if the extended info tables are enabled.
    LeaseMgr::setExtendedInfoTablesEnabled(parameters);

    // Create unique timer name per instance.
    timer_name_ = "MySqlLeaseMgr[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Validate schema version first.
    std::pair<uint32_t, uint32_t> code_version(MYSQL_SCHEMA_VERSION_MAJOR,
                                               MYSQL_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError,
                  "MySQL schema version mismatch: need version: "
                      << code_version.first << "." << code_version.second
                      << " found version: " << db_version.first << "."
                      << db_version.second);
    }

    // Create an initial context.
    pool_.reset(new MySqlLeaseContextPool());
    pool_->pool_.push_back(createContext());
}

MySqlLeaseMgr::~MySqlLeaseMgr() {
}

bool
MySqlLeaseMgr::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
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
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED)
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
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MYSQL_LEASE_DB_RECONNECT_FAILED)
                    .arg(db_reconnect_ctl->maxRetries());

            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection failed callback.
            DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);
            return (false);
        }

        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        // Start the timer.
        if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->registerTimer(timer_name,
                std::bind(&MySqlLeaseMgr::dbReconnect, db_reconnect_ctl),
                          db_reconnect_ctl->retryInterval(),
                          asiolink::IntervalTimer::ONE_SHOT);
        }
        TimerMgr::instance()->setup(timer_name);
    }

    return (true);
}

// Create context.

MySqlLeaseContextPtr
MySqlLeaseMgr::createContext() const {
    MySqlLeaseContextPtr ctx(new MySqlLeaseContext(parameters_,
        IOServiceAccessorPtr(new IOServiceAccessor(&LeaseMgr::getIOService)),
        &MySqlLeaseMgr::dbReconnect));

    // Open the database.
    ctx->conn_.openDatabase();

    // Check if we have TLS when we required it.
    if (ctx->conn_.getTls()) {
        std::string cipher = ctx->conn_.getTlsCipher();
        if (cipher.empty()) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MYSQL_NO_TLS);
        } else {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_MYSQL_TLS_CIPHER)
                .arg(cipher);
        }
    }

    // Prepare all statements likely to be used.
    ctx->conn_.prepareStatements(tagged_statements.begin(),
                                 tagged_statements.end());

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    ctx->exchange4_.reset(new MySqlLease4Exchange());
    ctx->exchange6_.reset(new MySqlLease6Exchange());

    // Create ReconnectCtl for this connection.
    ctx->conn_.makeReconnectCtl(timer_name_);

    return (ctx);
}

std::string
MySqlLeaseMgr::getDBVersion() {
    std::stringstream tmp;
    tmp << "MySQL backend " << MYSQL_SCHEMA_VERSION_MAJOR;
    tmp << "." << MYSQL_SCHEMA_VERSION_MINOR;
    tmp << ", library " << mysql_get_client_info();
    return (tmp.str());
}

// Add leases to the database.  The two public methods accept a lease object
// (either V4 of V6), bind the contents to the appropriate prepared
// statement, then call common code to execute the statement.

bool
MySqlLeaseMgr::addLeaseCommon(MySqlLeaseContextPtr& ctx,
                              StatementIndex stindex,
                              std::vector<MYSQL_BIND>& bind) {
    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], &bind[0]);
    checkError(ctx, status, stindex, "unable to bind parameters");

    // Execute the statement
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);
    if (status != 0) {

        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (mysql_errno(ctx->conn_.mysql_) == ER_DUP_ENTRY) {
            return (false);
        }
        checkError(ctx, status, stindex, "unable to execute");
    }

    // Insert succeeded
    return (true);
}

bool
MySqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ADD_ADDR4)
        .arg(lease->addr_.toText());

    // Get a context
    MySqlLeaseTrackingContextAlloc get_context(*this, lease);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create the MYSQL_BIND array for the lease
    std::vector<MYSQL_BIND> bind = ctx->exchange4_->createBindForSend(lease);

    // ... and drop to common code.
    auto result = addLeaseCommon(ctx, INSERT_LEASE4, bind);

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackAddLease(lease, false);
    }

    return (result);
}

bool
MySqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ADD_ADDR6)
        .arg(lease->addr_.toText())
        .arg(lease->type_);

    // Get a context
    MySqlLeaseTrackingContextAlloc get_context(*this, lease);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create the MYSQL_BIND array for the lease
    std::vector<MYSQL_BIND> bind = ctx->exchange6_->createBindForSend(lease);

    // ... and drop to common code.
    auto result = addLeaseCommon(ctx, INSERT_LEASE6, bind);

    // Update lease current expiration time (allows update between the creation
    // of the Lease up to the point of insertion in the database).
    lease->updateCurrentExpirationTime();

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackAddLease(lease, false);
    }

    return (result);
}

// Extraction of leases from the database.
//
// All getLease() methods ultimately call getLeaseCollection().  This
// binds the input parameters passed to it with the appropriate prepared
// statement and executes the statement.  It then gets the results from the
// database.  getlease() methods that expect a single result back call it
// with the "single" parameter set true: this causes an exception to be
// generated if multiple records can be retrieved from the result set. (Such
// an occurrence either indicates corruption in the database, or that an
// assumption that a query can only return a single record is incorrect.)
// Methods that require a collection of records have "single" set to the
// default value of false.  The logic is the same for both Lease4 and Lease6
// objects,  so the code is templated.
//
// Methods that require a collection of objects access this method through
// two interface methods (also called getLeaseCollection()).  These are
// short enough as to be defined in the header file: all they do is to supply
// the appropriate MySqlLeaseXExchange object depending on the type of the
// LeaseCollection objects passed to them.
//
// Methods that require a single object to be returned access the method
// through two interface methods (called getLease()).  As well as supplying
// the appropriate exchange object, they convert between lease collection
// holding zero or one leases into an appropriate Lease object.

template <typename Exchange, typename LeaseCollection>
void
MySqlLeaseMgr::getLeaseCollection(MySqlLeaseContextPtr& ctx,
                                  StatementIndex stindex,
                                  MYSQL_BIND* bind,
                                  Exchange& exchange,
                                  LeaseCollection& result,
                                  bool single) const {
    int status;

    if (bind) {
        // Bind the selection parameters to the statement
        status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], bind);
        checkError(ctx, status, stindex, "unable to bind WHERE clause parameter");
    }

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange->createBindForReceive();
    status = mysql_stmt_bind_result(ctx->conn_.statements_[stindex], &outbind[0]);
    checkError(ctx, status, stindex, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);
    checkError(ctx, status, stindex, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(ctx->conn_.statements_[stindex]);
    checkError(ctx, status, stindex, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(ctx->conn_.statements_[stindex]);
    int count = 0;
    while ((status = mysql_stmt_fetch(ctx->conn_.statements_[stindex])) == 0) {
        try {
            result.push_back(exchange->getLeaseData());

        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      ctx->conn_.text_statements_[stindex] << ">");
        }

        if (single && (++count > 1)) {
            isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << ctx->conn_.text_statements_[stindex]);
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(ctx, status, stindex, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, ctx->conn_.text_statements_[stindex]
                  << " returned truncated data: columns affected are "
                  << exchange->getErrorColumns());
    }
}

void
MySqlLeaseMgr::getLease(MySqlLeaseContextPtr& ctx,
                        StatementIndex stindex, MYSQL_BIND* bind,
                        Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(ctx, stindex, bind, ctx->exchange4_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
MySqlLeaseMgr::getLease(MySqlLeaseContextPtr& ctx,
                        StatementIndex stindex, MYSQL_BIND* bind,
                        Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" parameter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(ctx, stindex, bind, ctx->exchange6_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

// Basic lease access methods.  Obtain leases from the database using various
// criteria.

Lease4Ptr
MySqlLeaseMgr::getLease4(const IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_ADDR4)
        .arg(addr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    uint32_t addr4 = addr.toUint32();
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&addr4);
    inbind[0].is_unsigned = MLM_TRUE;

    // Get the data
    Lease4Ptr result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE4_ADDR, inbind, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_HWADDR)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;

    unsigned long hwaddr_length = hwaddr.hwaddr_.size();

    // If the data happens to be empty, we have to create a 1 byte dummy
    // buffer and pass it to the binding.
    uint8_t single_byte_data = 0;

    // As "buffer" is "char*" - even though the data is being read - we need
    // to cast away the "const"ness as well as reinterpreting the data as
    // a "char*". (We could avoid the "const_cast" by copying the data to a
    // local variable, but as the data is only being read, this introduces
    // an unnecessary copy).
    uint8_t* data = !hwaddr.hwaddr_.empty() ? const_cast<uint8_t*>(&hwaddr.hwaddr_[0])
        : &single_byte_data;

    inbind[0].buffer = reinterpret_cast<char*>(data);
    inbind[0].buffer_length = hwaddr_length;
    inbind[0].length = &hwaddr_length;

    // Get the data
    Lease4Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_HWADDR, inbind, result);

    return (result);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SUBID_HWADDR)
        .arg(subnet_id)
        .arg(hwaddr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;

    unsigned long hwaddr_length = hwaddr.hwaddr_.size();

    // If the data happens to be empty, we have to create a 1 byte dummy
    // buffer and pass it to the binding.
    std::vector<uint8_t> single_byte_vec(1);

    // As "buffer" is "char*" - even though the data is being read - we need
    // to cast away the "const"ness as well as reinterpreting the data as
    // a "char*". (We could avoid the "const_cast" by copying the data to a
    // local variable, but as the data is only being read, this introduces
    // an unnecessary copy).
    uint8_t* data = !hwaddr.hwaddr_.empty() ? const_cast<uint8_t*>(&hwaddr.hwaddr_[0])
        : &single_byte_vec[0];

    inbind[0].buffer = reinterpret_cast<char*>(data);
    inbind[0].buffer_length = hwaddr_length;
    inbind[0].length = &hwaddr_length;

    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[1].is_unsigned = MLM_TRUE;

    // Get the data
    Lease4Ptr result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE4_HWADDR_SUBID, inbind, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_CLIENTID)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;

    std::vector<uint8_t> client_data = clientid.getClientId();
    unsigned long client_data_length = client_data.size();

    // If the data happens to be empty, we have to create a 1 byte dummy
    // buffer and pass it to the binding.
    if (client_data.empty()) {
        client_data.resize(1);
    }

    inbind[0].buffer = reinterpret_cast<char*>(&client_data[0]);
    inbind[0].buffer_length = client_data_length;
    inbind[0].length = &client_data_length;

    // Get the data
    Lease4Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_CLIENTID, inbind, result);

    return (result);
}

Lease4Ptr
MySqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SUBID_CLIENTID)
        .arg(subnet_id)
        .arg(clientid.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;

    std::vector<uint8_t> client_data = clientid.getClientId();
    unsigned long client_data_length = client_data.size();

    // If the data happens to be empty, we have to create a 1 byte dummy
    // buffer and pass it to the binding.
    if (client_data.empty()) {
        client_data.resize(1);
    }

    inbind[0].buffer = reinterpret_cast<char*>(&client_data[0]);
    inbind[0].buffer_length = client_data_length;
    inbind[0].length = &client_data_length;

    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[1].is_unsigned = MLM_TRUE;

    // Get the data
    Lease4Ptr result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE4_CLIENTID_SUBID, inbind, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLeases4(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SUBID4)
        .arg(subnet_id);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    // Subnet ID
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[0].is_unsigned = MLM_TRUE;

    // ... and get the data
    Lease4Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_SUBID, inbind, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLeases4(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_HOSTNAME4)
        .arg(hostname);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    // Hostname
    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(hostname.c_str());
    inbind[0].buffer_length = hostname.length();

    // ... and get the data
    Lease4Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_HOSTNAME, inbind, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLeases4() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET4);

    Lease4Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4, 0, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLeases4(const IOAddress& lower_bound_address,
                          const LeasePageSize& page_size) const {
    // Expecting IPv4 address.
    if (!lower_bound_address.isV4()) {
        isc_throw(InvalidAddressFamily, "expected IPv4 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_PAGE4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    // Prepare WHERE clause
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Bind lower bound address
    uint32_t lb_address_data = lower_bound_address.toUint32();
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&lb_address_data);
    inbind[0].is_unsigned = MLM_TRUE;

    // Bind page size value
    uint32_t ps = static_cast<uint32_t>(page_size.page_size_);
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&ps);
    inbind[1].is_unsigned = MLM_TRUE;

    // Get the leases
    Lease4Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE4_PAGE, inbind, result);

    return (result);
}

Lease6Ptr
MySqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_ADDR6)
        .arg(addr.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // address: binary(16)
    std::vector<uint8_t>addr6 = addr.toBytes();
    if (addr6.size() != 16) {
        isc_throw(DbOperationError, "lease6 address is not 16 bytes long");
    }

    unsigned long addr6_length = 16;
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&addr6[0]);
    inbind[0].buffer_length = 16;
    inbind[0].length = &addr6_length;

    // LEASE_TYPE
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&lease_type);
    inbind[1].is_unsigned = MLM_TRUE;

    Lease6Ptr result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLease(ctx, GET_LEASE6_ADDR, inbind, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_IAID_DUID)
        .arg(iaid)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // In the following statement, the DUID is being read.  However, the
    // MySQL C interface does not use "const", so the "buffer" element
    // is declared as "char*" instead of "const char*".  To resolve this,
    // the "const" is discarded before the uint8_t* is cast to char*.
    //
    // Note that the const_cast could be avoided by copying the DUID to
    // a writable buffer and storing the address of that in the "buffer"
    // element.  However, this introduces a copy operation (with additional
    // overhead) purely to get round the structures introduced by design of
    // the MySQL interface (which uses the area pointed to by "buffer" as
    // input when specifying query parameters and as output when retrieving
    // data).  For that reason, "const_cast" has been used.
    const vector<uint8_t>& duid_vector = duid.getDuid();
    unsigned long duid_length = duid_vector.size();

    // Make sure that the buffer has at least length of 1, even if
    // empty client id is passed. This is required by some of the
    // MySQL connectors that the buffer is set to non-null value.
    // Otherwise, null value would be inserted into the database,
    // rather than empty string.
    uint8_t single_byte_data = 0;
    uint8_t* data = !duid_vector.empty() ? const_cast<uint8_t*>(&duid_vector[0])
        : &single_byte_data;

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(data);
    inbind[0].buffer_length = duid_length;
    inbind[0].length = &duid_length;

    // IAID
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&iaid);
    inbind[1].is_unsigned = MLM_TRUE;

    // LEASE_TYPE
    inbind[2].buffer_type = MYSQL_TYPE_TINY;
    inbind[2].buffer = reinterpret_cast<char*>(&lease_type);
    inbind[2].is_unsigned = MLM_TRUE;

    // ... and get the data
    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_DUID_IAID, inbind, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid,
                          uint32_t iaid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_IAID_SUBID_DUID)
        .arg(iaid)
        .arg(subnet_id)
        .arg(duid.toText())
        .arg(lease_type);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[4];
    memset(inbind, 0, sizeof(inbind));

    // See the earlier description of the use of "const_cast" when accessing
    // the DUID for an explanation of the reason.
    const vector<uint8_t>& duid_vector = duid.getDuid();
    unsigned long duid_length = duid_vector.size();
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(
            const_cast<uint8_t*>(&duid_vector[0]));
    inbind[0].buffer_length = duid_length;
    inbind[0].length = &duid_length;

    // IAID
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&iaid);
    inbind[1].is_unsigned = MLM_TRUE;

    // Subnet ID
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[2].is_unsigned = MLM_TRUE;

    // LEASE_TYPE
    inbind[3].buffer_type = MYSQL_TYPE_TINY;
    inbind[3].buffer = reinterpret_cast<char*>(&lease_type);
    inbind[3].is_unsigned = MLM_TRUE;

    // ... and get the data
    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_DUID_IAID_SUBID, inbind, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6(SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_SUBID6)
        .arg(subnet_id);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    // Subnet ID
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_id);
    inbind[0].is_unsigned = MLM_TRUE;

    // ... and get the data
    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_SUBID, inbind, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET6);

    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6, 0, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6(const DUID& duid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_DUID)
        .arg(duid.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    const vector<uint8_t>& duid_vector = duid.getDuid();
    unsigned long duid_length = duid_vector.size();

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(
            const_cast<uint8_t*>(&duid_vector[0]));
    inbind[0].buffer_length = duid_length;
    inbind[0].length = &duid_length;

    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_DUID, inbind, result);

    return result;
}

Lease6Collection
MySqlLeaseMgr::getLeases6(const std::string& hostname) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_HOSTNAME6)
        .arg(hostname);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    // Hostname
    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = const_cast<char*>(hostname.c_str());
    inbind[0].buffer_length = hostname.length();

    // ... and get the data
    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_HOSTNAME, inbind, result);

    return (result);
}

Lease6Collection
MySqlLeaseMgr::getLeases6(const IOAddress& lower_bound_address,
                          const LeasePageSize& page_size) const {
    // Expecting IPv6 address.
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_PAGE6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText());

    // Prepare WHERE clause
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Bind lower bound address
    std::vector<uint8_t>lb_addr = lower_bound_address.toBytes();
    if (lb_addr.size() != 16) {
        isc_throw(DbOperationError, "getLeases6() - lower bound address is not 16 bytes long");
    }

    unsigned long lb_addr_length = 16;
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&lb_addr[0]);
    inbind[0].buffer_length = 16;
    inbind[0].length = &lb_addr_length;

    // Bind page size value
    uint32_t ps = static_cast<uint32_t>(page_size.page_size_);
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&ps);
    inbind[1].is_unsigned = MLM_TRUE;

    // Get the leases
    Lease6Collection result;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, GET_LEASE6_PAGE, inbind, result);

    return (result);
}

void
MySqlLeaseMgr::getExpiredLeases4(Lease4Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_EXPIRED4)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE4_EXPIRE);
}

void
MySqlLeaseMgr::getExpiredLeases6(Lease6Collection& expired_leases,
                                 const size_t max_leases) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_EXPIRED6)
        .arg(max_leases);
    getExpiredLeasesCommon(expired_leases, max_leases, GET_LEASE6_EXPIRE);
}

template<typename LeaseCollection>
void
MySqlLeaseMgr::getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                      const size_t max_leases,
                                      StatementIndex statement_index) const {
    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // Exclude reclaimed leases.
    uint32_t state = static_cast<uint32_t>(Lease::STATE_EXPIRED_RECLAIMED);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&state);
    inbind[0].is_unsigned = MLM_TRUE;

    // Expiration timestamp.
    MYSQL_TIME expire_time;
    MySqlConnection::convertToDatabaseTime(time(0), expire_time);
    inbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    inbind[1].buffer = reinterpret_cast<char*>(&expire_time);
    inbind[1].buffer_length = sizeof(expire_time);

    // If the number of leases is 0, we will return all leases. This is
    // achieved by setting the limit to a very high value.
    uint32_t limit = max_leases > 0 ? static_cast<uint32_t>(max_leases) :
        std::numeric_limits<uint32_t>::max();
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&limit);
    inbind[2].is_unsigned = MLM_TRUE;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Get the data
    getLeaseCollection(ctx, statement_index, inbind, expired_leases);
}

// Update lease methods.  These comprise common code that handles the actual
// update, and type-specific methods that set up the parameters for the prepared
// statement depending on the type of lease.

template <typename LeasePtr>
void
MySqlLeaseMgr::updateLeaseCommon(MySqlLeaseContextPtr& ctx,
                                 StatementIndex stindex,
                                 MYSQL_BIND* bind,
                                 const LeasePtr& lease) {

    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], bind);
    checkError(ctx, status, stindex, "unable to bind parameters");

    // Execute
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);
    checkError(ctx, status, stindex, "unable to execute");

    // See how many rows were affected.  The statement should only update a
    // single row.
    int affected_rows = mysql_stmt_affected_rows(ctx->conn_.statements_[stindex]);

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
MySqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_UPDATE_ADDR4)
        .arg(lease->addr_.toText());

    // Get a context
    MySqlLeaseTrackingContextAlloc get_context(*this, lease);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create the MYSQL_BIND array for the data being updated
    std::vector<MYSQL_BIND> bind = ctx->exchange4_->createBindForSend(lease);

    // Set up the WHERE clause and append it to the MYSQL_BIND array
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    uint32_t addr4 = lease->addr_.toUint32();
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&addr4);
    inbind[0].is_unsigned = MLM_TRUE;

    bind.push_back(inbind[0]);

    // See the expire code of createBindForSend for the
    // infinite valid lifetime special case.
    MYSQL_TIME expire;
    uint32_t valid_lft = lease->current_valid_lft_;
    if (valid_lft == Lease::INFINITY_LFT) {
        valid_lft = 0;
    }
    MySqlConnection::convertToDatabaseTime(lease->current_cltt_, valid_lft,
                                           expire);
    inbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    inbind[1].buffer = reinterpret_cast<char*>(&expire);
    inbind[1].buffer_length = sizeof(expire);

    bind.push_back(inbind[1]);

    // Drop to common update code
    updateLeaseCommon(ctx, stindex, &bind[0], lease);

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackUpdateLease(lease, false);
    }
}

void
MySqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_UPDATE_ADDR6)
        .arg(lease->addr_.toText())
        .arg(lease->type_);

    // Get a context
    MySqlLeaseTrackingContextAlloc get_context(*this, lease);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create the MYSQL_BIND array for the data being updated
    std::vector<MYSQL_BIND> bind = ctx->exchange6_->createBindForSend(lease);

    // Set up the WHERE clause and append it to the MYSQL_BIND array
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Bind the where clause address parameter.
    std::vector<uint8_t>addr6 = lease->addr_.toBytes();
    if (addr6.size() != 16) {
        isc_throw(DbOperationError, "updateLease6() - address is not 16 bytes long");
    }

    unsigned long addr6_length = 16;
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&addr6[0]);
    inbind[0].buffer_length = 16;
    inbind[0].length = &addr6_length;

    bind.push_back(inbind[0]);

    // See the expire code of createBindForSend for the
    // infinite valid lifetime special case.
    MYSQL_TIME expire;
    uint32_t valid_lft = lease->current_valid_lft_;
    if (valid_lft == Lease::INFINITY_LFT) {
        valid_lft = 0;
    }
    MySqlConnection::convertToDatabaseTime(lease->current_cltt_, valid_lft,
                                           expire);
    inbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    inbind[1].buffer = reinterpret_cast<char*>(&expire);
    inbind[1].buffer_length = sizeof(expire);

    bind.push_back(inbind[1]);

    // Drop to common update code
    updateLeaseCommon(ctx, stindex, &bind[0], lease);

    // Update lease current expiration time.
    lease->updateCurrentExpirationTime();

    // Run installed callbacks.
    if (hasCallbacks()) {
        trackUpdateLease(lease, false);
    }
}

// Delete lease methods.  Similar to other groups of methods, these comprise
// a per-type method that sets up the relevant MYSQL_BIND array (in this
// case, a single method for both V4 and V6 addresses) and a common method that
// handles the common processing.

uint64_t
MySqlLeaseMgr::deleteLeaseCommon(MySqlLeaseContextPtr& ctx,
                                 StatementIndex stindex,
                                 MYSQL_BIND* bind) {
    // Bind the input parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], bind);
    checkError(ctx, status, stindex, "unable to bind WHERE clause parameter");

    // Execute
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);
    checkError(ctx, status, stindex, "unable to execute");

    // See how many rows were affected.  Note that the statement may delete
    // multiple rows.
    return (static_cast<uint64_t>(mysql_stmt_affected_rows(ctx->conn_.statements_[stindex])));
}

bool
MySqlLeaseMgr::deleteLease(const Lease4Ptr& lease) {
    const IOAddress& addr = lease->addr_;
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_DELETE_ADDR)
        .arg(addr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    uint32_t addr4 = addr.toUint32();

    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&addr4);
    inbind[0].is_unsigned = MLM_TRUE;

    // See the expire code of createBindForSend for the
    // infinite valid lifetime special case.
    MYSQL_TIME expire;
    uint32_t valid_lft = lease->current_valid_lft_;
    if (valid_lft == Lease::INFINITY_LFT) {
        valid_lft = 0;
    }
    MySqlConnection::convertToDatabaseTime(lease->current_cltt_, valid_lft,
                                           expire);
    inbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    inbind[1].buffer = reinterpret_cast<char*>(&expire);
    inbind[1].buffer_length = sizeof(expire);

    // Get a context
    MySqlLeaseTrackingContextAlloc get_context(*this, lease);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    auto affected_rows = deleteLeaseCommon(ctx, DELETE_LEASE4, inbind);

    // Check success case first as it is the most likely outcome.
    if (affected_rows == 1) {
        if (hasCallbacks()) {
            trackDeleteLease(lease, false);
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
MySqlLeaseMgr::deleteLease(const Lease6Ptr& lease) {
    const IOAddress& addr = lease->addr_;
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_DELETE_ADDR)
        .arg(addr.toText());

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Bind the where clause address parameter.
    std::vector<uint8_t>addr6 = addr.toBytes();
    if (addr6.size() != 16) {
        isc_throw(DbOperationError, "deleteLease6() - address is not 16 bytes long");
    }

    unsigned long addr6_length = 16;
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&addr6[0]);
    inbind[0].buffer_length = 16;
    inbind[0].length = &addr6_length;

    // See the expire code of createBindForSend for the
    // infinite valid lifetime special case.
    MYSQL_TIME expire;
    uint32_t valid_lft = lease->current_valid_lft_;
    if (valid_lft == Lease::INFINITY_LFT) {
        valid_lft = 0;
    }
    MySqlConnection::convertToDatabaseTime(lease->current_cltt_, valid_lft,
                                           expire);
    inbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    inbind[1].buffer = reinterpret_cast<char*>(&expire);
    inbind[1].buffer_length = sizeof(expire);

    // Get a context
    MySqlLeaseTrackingContextAlloc get_context(*this, lease);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    auto affected_rows = deleteLeaseCommon(ctx, DELETE_LEASE6, inbind);

    // Check success case first as it is the most likely outcome.
    if (affected_rows == 1) {
        if (hasCallbacks()) {
            trackDeleteLease(lease, false);
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
MySqlLeaseMgr::deleteExpiredReclaimedLeases4(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED4)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE4_STATE_EXPIRED));
}

uint64_t
MySqlLeaseMgr::deleteExpiredReclaimedLeases6(const uint32_t secs) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED6)
        .arg(secs);
    return (deleteExpiredReclaimedLeasesCommon(secs, DELETE_LEASE6_STATE_EXPIRED));
}

uint64_t
MySqlLeaseMgr::deleteExpiredReclaimedLeasesCommon(const uint32_t secs,
                                                  StatementIndex statement_index) {
    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // State is reclaimed.
    uint32_t state = static_cast<uint32_t>(Lease::STATE_EXPIRED_RECLAIMED);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&state);
    inbind[0].is_unsigned = MLM_TRUE;

    // Expiration timestamp.
    MYSQL_TIME expire_time;
    MySqlConnection::convertToDatabaseTime(time(0) - static_cast<time_t>(secs), expire_time);
    inbind[1].buffer_type = MYSQL_TYPE_TIMESTAMP;
    inbind[1].buffer = reinterpret_cast<char*>(&expire_time);
    inbind[1].buffer_length = sizeof(expire_time);

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Get the number of deleted leases and log it.
    uint64_t deleted_leases = deleteLeaseCommon(ctx, statement_index, inbind);
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_DELETED_EXPIRED_RECLAIMED)
        .arg(deleted_leases);

    return (deleted_leases);
}

string
MySqlLeaseMgr::checkLimits(ConstElementPtr const& user_context, StatementIndex const stindex) const {
    // No user context means no limits means allocation allowed means empty string.
    if (!user_context) {
        return string();
    }

    // Get a context.
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create bindings.
    MySqlBindingCollection in_bindings({
        MySqlBinding::createString(user_context->str())
    });
    MySqlBindingCollection out_bindings({
        MySqlBinding::createString(LIMITS_TEXT_MAX_LEN)
    });

    // Execute the select.
    std::string limit_text;
    ctx->conn_.selectQuery(stindex, in_bindings, out_bindings,
                           [&limit_text] (MySqlBindingCollection const& result) {
        limit_text = result[0]->getString();
    });

    return limit_text;
}

string
MySqlLeaseMgr::checkLimits4(ConstElementPtr const& user_context) const {
    return checkLimits(user_context, CHECK_LEASE4_LIMITS);
}

string
MySqlLeaseMgr::checkLimits6(ConstElementPtr const& user_context) const {
    return checkLimits(user_context, CHECK_LEASE6_LIMITS);
}

bool
MySqlLeaseMgr::isJsonSupported() const {
    // Get a context.
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create bindings.
    MySqlBindingCollection in_bindings;
    MySqlBindingCollection out_bindings({
        MySqlBinding::createBool()
    });

    // Execute the select.
    bool json_supported(false);
    ctx->conn_.selectQuery(IS_JSON_SUPPORTED, in_bindings, out_bindings,
                           [&json_supported] (MySqlBindingCollection const& result) {
        json_supported = result[0]->getBool();
    });

    return json_supported;
}

size_t
MySqlLeaseMgr::getClassLeaseCount(const ClientClass& client_class,
                                  const Lease::Type& ltype /* = Lease::TYPE_V4*/) const {
    // Get a context.
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Create bindings.
    MySqlBindingCollection in_bindings({
        MySqlBinding::createString(client_class)
    });
    if (ltype != Lease::TYPE_V4) {
        in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(ltype));
    }
    MySqlBindingCollection out_bindings({
        MySqlBinding::createInteger<int64_t>()
    });

    // Execute the select.
    StatementIndex const stindex(ltype == Lease::TYPE_V4 ? GET_LEASE4_COUNT_BY_CLASS :
                                                           GET_LEASE6_COUNT_BY_CLASS);
    size_t count(0);
    ctx->conn_.selectQuery(stindex, in_bindings, out_bindings,
                           [&count] (MySqlBindingCollection const& result) {
        count = result[0]->getInteger<int64_t>();
    });

    return count;
}

void
MySqlLeaseMgr::recountClassLeases4() {
    isc_throw(NotImplemented, "MySqlLeaseMgr::recountClassLeases4() not implemented");
}

void
MySqlLeaseMgr::recountClassLeases6() {
    isc_throw(NotImplemented, "MySqlLeaseMgr::recountClassLeases6() not implemented");
}

void
MySqlLeaseMgr::clearClassLeaseCounts() {
    isc_throw(NotImplemented, "MySqlLeaseMgr::clearClassLeaseCounts() not implemented");
}

void
MySqlLeaseMgr::writeLeases4(const std::string&) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::writeLeases4() not implemented");
}

void
MySqlLeaseMgr::writeLeases6(const std::string&) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::writeLeases6() not implemented");
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startLeaseStatsQuery4() {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      ALL_LEASE4_STATS,
                                                      false));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startPoolLeaseStatsQuery4() {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      ALL_POOL_LEASE4_STATS,
                                                      false, true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startSubnetLeaseStatsQuery4(const SubnetID& subnet_id) {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      SUBNET_LEASE4_STATS,
                                                      false,
                                                      subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startSubnetRangeLeaseStatsQuery4(const SubnetID& first_subnet_id,
                                                const SubnetID& last_subnet_id) {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      SUBNET_RANGE_LEASE4_STATS,
                                                      false,
                                                      first_subnet_id,
                                                      last_subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startLeaseStatsQuery6() {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      ALL_LEASE6_STATS,
                                                      true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startPoolLeaseStatsQuery6() {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      ALL_POOL_LEASE6_STATS,
                                                      true, true));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startSubnetLeaseStatsQuery6(const SubnetID& subnet_id) {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      SUBNET_LEASE6_STATS,
                                                      true,
                                                      subnet_id));
    query->start();
    return(query);
}

LeaseStatsQueryPtr
MySqlLeaseMgr::startSubnetRangeLeaseStatsQuery6(const SubnetID& first_subnet_id,
                                                const SubnetID& last_subnet_id) {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    LeaseStatsQueryPtr query(new MySqlLeaseStatsQuery(ctx->conn_,
                                                      SUBNET_RANGE_LEASE6_STATS,
                                                      true,
                                                      first_subnet_id,
                                                      last_subnet_id));
    query->start();
    return(query);
}

size_t
MySqlLeaseMgr::wipeLeases4(const SubnetID& /*subnet_id*/) {
    isc_throw(NotImplemented, "wipeLeases4 is not implemented for MySQL backend");
}

size_t
MySqlLeaseMgr::wipeLeases6(const SubnetID& /*subnet_id*/) {
    isc_throw(NotImplemented, "wipeLeases6 is not implemented for MySQL backend");
}

// Miscellaneous database methods.

std::string
MySqlLeaseMgr::getName() const {
    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    std::string name = "";
    try {
        name = ctx->conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string
MySqlLeaseMgr::getDescription() const {
    return (std::string("MySQL Database"));
}

std::pair<uint32_t, uint32_t>
MySqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_VERSION);

    return (MySqlConnection::getVersion(parameters_));
}

void
MySqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
}

void
MySqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
}

void
MySqlLeaseMgr::checkError(MySqlLeaseContextPtr& ctx,
                          int status, StatementIndex index,
                          const char* what) const {
    ctx->conn_.checkError(status, index, what);
}

void
MySqlLeaseMgr::deleteExtendedInfo6(const IOAddress& /* addr */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::deleteExtendedInfo6 not implemented");
}

void
MySqlLeaseMgr::addRelayId6(const IOAddress& /* lease_addr */,
                           const vector<uint8_t>& /* relay_id */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::addRelayId6 not implemented");
}

void
MySqlLeaseMgr::addRemoteId6(const IOAddress& /* lease_addr */,
                            const vector<uint8_t>& /* remote_id */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::addRemoteId6 not implemented");
}

namespace {

std::string
idToText(const OptionBuffer& id) {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (std::vector<uint8_t>::const_iterator it = id.begin();
         it != id.end(); ++it) {
        if (delim) {
            tmp << ":";
        }
        tmp << std::setw(2) << std::setfill('0')
            << static_cast<unsigned int>(*it);
        delim = true;
    }
    return (tmp.str());
}

} // anonymous namespace

Lease4Collection
MySqlLeaseMgr::getLeases4ByRelayId(const OptionBuffer& relay_id,
                                   const IOAddress& lower_bound_address,
                                   const LeasePageSize& page_size,
                                   const time_t& qry_start_time /* = 0 */,
                                   const time_t& qry_end_time /* = 0 */) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_RELAYID4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(relay_id))
        .arg(qry_start_time)
        .arg(qry_end_time);

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

    // Prepare WHERE clause
    size_t bindings = 3;
    if (have_qst) {
        ++bindings;
    }
    if (have_qet) {
        ++bindings;
    }
    MYSQL_BIND inbind[bindings];
    memset(inbind, 0, sizeof(inbind));

    std::vector<uint8_t> relay_id_data = relay_id;
    unsigned long relay_id_length = relay_id.size();

    // If the relay id happens to be empty, we have to create a
    // 1 byte dummy buffer and pass it to the binding.
    if (relay_id_data.empty()) {
        relay_id_data.resize(1);
    }

    // Bind relay id
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&relay_id_data[0]);
    inbind[0].buffer_length = relay_id_length;
    inbind[0].length = &relay_id_length;

    // Bind lower bound address
    uint32_t lb_address_data = lower_bound_address.toUint32();
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&lb_address_data);
    inbind[1].is_unsigned = MLM_TRUE;

    size_t index = 2;
    // Bind query start time.
    uint32_t start_time = static_cast<uint32_t>(qry_start_time);
    if (have_qst) {
        inbind[index].buffer_type = MYSQL_TYPE_LONG;
        inbind[index].buffer = reinterpret_cast<char*>(&start_time);
        inbind[index].is_unsigned = MLM_TRUE;
        ++index;
    }

    // Bind query end time.
    uint32_t end_time = static_cast<uint32_t>(qry_end_time);
    if (have_qet) {
        inbind[index].buffer_type = MYSQL_TYPE_LONG;
        inbind[index].buffer = reinterpret_cast<char*>(&end_time);
        inbind[index].is_unsigned = MLM_TRUE;
        ++index;
    }

    // Bind page size value
    uint32_t ps = static_cast<uint32_t>(page_size.page_size_);
    inbind[index].buffer_type = MYSQL_TYPE_LONG;
    inbind[index].buffer = reinterpret_cast<char*>(&ps);
    inbind[index].is_unsigned = MLM_TRUE;

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
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, stindex, inbind, result);

    return (result);
}

Lease4Collection
MySqlLeaseMgr::getLeases4ByRemoteId(const OptionBuffer& remote_id,
                                    const IOAddress& lower_bound_address,
                                    const LeasePageSize& page_size,
                                    const time_t& qry_start_time /* = 0 */,
                                    const time_t& qry_end_time /* = 0 */) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_REMOTEID4)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(idToText(remote_id))
        .arg(qry_start_time)
        .arg(qry_end_time);

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

    // Prepare WHERE clause
    size_t bindings = 3;
    if (have_qst) {
        ++bindings;
    }
    if (have_qet) {
        ++bindings;
    }
    MYSQL_BIND inbind[bindings];
    memset(inbind, 0, sizeof(inbind));

    std::vector<uint8_t> remote_id_data = remote_id;
    unsigned long remote_id_length = remote_id.size();

    // If the remote id happens to be empty, we have to create a
    // 1 byte dummy buffer and pass it to the binding.
    if (remote_id_data.empty()) {
        remote_id_data.resize(1);
    }

    // Bind remote id
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&remote_id_data[0]);
    inbind[0].buffer_length = remote_id_length;
    inbind[0].length = &remote_id_length;

    // Bind lower bound address
    uint32_t lb_address_data = lower_bound_address.toUint32();
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&lb_address_data);
    inbind[1].is_unsigned = MLM_TRUE;

    size_t index = 2;
    // Bind query start time.
    uint32_t start_time = static_cast<uint32_t>(qry_start_time);
    if (have_qst) {
        inbind[index].buffer_type = MYSQL_TYPE_LONG;
        inbind[index].buffer = reinterpret_cast<char*>(&start_time);
        inbind[index].is_unsigned = MLM_TRUE;
        ++index;
    }

    // Bind query end time.
    uint32_t end_time = static_cast<uint32_t>(qry_end_time);
    if (have_qet) {
        inbind[index].buffer_type = MYSQL_TYPE_LONG;
        inbind[index].buffer = reinterpret_cast<char*>(&end_time);
        inbind[index].is_unsigned = MLM_TRUE;
        ++index;
    }

    // Bind page size value
    uint32_t ps = static_cast<uint32_t>(page_size.page_size_);
    inbind[index].buffer_type = MYSQL_TYPE_LONG;
    inbind[index].buffer = reinterpret_cast<char*>(&ps);
    inbind[index].is_unsigned = MLM_TRUE;

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
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    getLeaseCollection(ctx, stindex, inbind, result);

    return (result);
}

size_t
MySqlLeaseMgr::upgradeExtendedInfo4(const LeasePageSize& page_size) {
    auto check = CfgMgr::instance().getCurrentCfg()->
        getConsistency()->getExtendedInfoSanityCheck();

    size_t pages = 0;
    size_t updated = 0;
    IOAddress start_addr = IOAddress::IPV4_ZERO_ADDRESS();
    for (;;) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_PAGE)
            .arg(pages)
            .arg(start_addr.toText())
            .arg(updated);

        // Prepare WHERE clause.
        MYSQL_BIND inbind[2];
        memset(inbind, 0, sizeof(inbind));

        // Bind start address.
        uint32_t start_addr_data = start_addr.toUint32();
        inbind[0].buffer_type = MYSQL_TYPE_LONG;
        inbind[0].buffer = reinterpret_cast<char*>(&start_addr_data);
        inbind[0].is_unsigned = MLM_TRUE;

        // Bind page size value.
        uint32_t ps = static_cast<uint32_t>(page_size.page_size_);
        inbind[1].buffer_type = MYSQL_TYPE_LONG;
        inbind[1].buffer = reinterpret_cast<char*>(&ps);
        inbind[1].is_unsigned = MLM_TRUE;

        Lease4Collection leases;

        // Get a context.
        {
            MySqlLeaseContextAlloc get_context(*this);
            MySqlLeaseContextPtr ctx = get_context.ctx_;

            getLeaseCollection(ctx, GET_LEASE4_UCTX_PAGE, inbind, leases);
        }

        if (leases.empty()) {
            // Done.
            break;
        }

        ++pages;
        start_addr = leases.back()->addr_;
        for (auto lease : leases) {
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
                          DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_ERROR)
                    .arg(lease->addr_.toText())
                    .arg(ex.what());
            }
        }
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4)
        .arg(pages)
        .arg(updated);

    return (updated);
}

Lease6Collection
MySqlLeaseMgr::getLeases6ByRelayId(const DUID& /* relay_id */,
                                   const IOAddress& /* link_addr */,
                                   uint8_t /* link_len */,
                                   const IOAddress& /* lower_bound_address */,
                                   const LeasePageSize& /* page_size */) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLeases6ByRelayId not implemented");
}

Lease6Collection
MySqlLeaseMgr::getLeases6ByRemoteId(const OptionBuffer& /* remote_id */,
                                    const IOAddress& /* link_addr */,
                                    uint8_t /* link_len */,
                                    const IOAddress& /* lower_bound_address */,
                                    const LeasePageSize& /* page_size*/) {
    isc_throw(NotImplemented, "MySqlLeaseMgr::getLeases6ByRemoteId not implemented");
}

Lease6Collection
MySqlLeaseMgr::getLeases6ByLink(const IOAddress& link_addr,
                                uint8_t link_len,
                                const IOAddress& lower_bound_address,
                                const LeasePageSize& page_size) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_LINKADDR6)
        .arg(page_size.page_size_)
        .arg(lower_bound_address.toText())
        .arg(link_addr.toText())
        .arg(static_cast<unsigned>(link_len));

    // Expecting IPv6 valid prefix and address.
    if (!link_addr.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << link_addr);
    }
    if ((link_len == 0) || (link_len > 128)) {
        isc_throw(OutOfRange, "invalid IPv6 prefix length "
                  << static_cast<unsigned>(link_len));
    }
    if (!lower_bound_address.isV6()) {
        isc_throw(InvalidAddressFamily, "expected IPv6 address while "
                  "retrieving leases from the lease database, got "
                  << lower_bound_address);
    }

    Lease6Collection result;
    const IOAddress& first_addr = firstAddrInPrefix(link_addr, link_len);
    const IOAddress& last_addr = lastAddrInPrefix(link_addr, link_len);
    IOAddress start_addr = lower_bound_address;
    if (lower_bound_address < first_addr) {
        start_addr = first_addr;
    } else if (last_addr <= lower_bound_address) {
        // Range was already done.
        return (result);
    } else {
        // The lower bound address is from the last call so skip it.
        start_addr = IOAddress::increase(lower_bound_address);
    }

    // Prepare WHERE clause
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // Bind start address
    std::vector<uint8_t> start_addr_data = start_addr.toBytes();
    if (start_addr_data.size() != 16) {
        isc_throw(DbOperationError, "start address is not 16 bytes long");
    }
    unsigned long start_addr_size = 16;
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>(&start_addr_data[0]);
    inbind[0].buffer_length = 16;
    inbind[0].length = &start_addr_size;

    // Bind last address
    std::vector<uint8_t> last_addr_data = last_addr.toBytes();
    if (last_addr_data.size() != 16) {
        isc_throw(DbOperationError, "last address is not 16 bytes long");
    }
    unsigned long last_addr_size = 16;
    inbind[1].buffer_type = MYSQL_TYPE_BLOB;
    inbind[1].buffer = reinterpret_cast<char*>(&last_addr_data[0]);
    inbind[1].buffer_length = 16;
    inbind[1].length = &last_addr_size;

    // Bind page size value
    uint32_t ps = static_cast<uint32_t>(page_size.page_size_);
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&ps);
    inbind[2].is_unsigned = MLM_TRUE;

    // Get a context
    MySqlLeaseContextAlloc get_context(*this);
    MySqlLeaseContextPtr ctx = get_context.ctx_;

    // Get the leases
    getLeaseCollection(ctx, GET_LEASE6_LINK, inbind, result);

    return (result);
}

size_t
MySqlLeaseMgr::buildExtendedInfoTables6(bool /* update */, bool /* current */) {
    isc_throw(isc::NotImplemented,
              "MySqlLeaseMgr::buildExtendedInfoTables6 not implemented");
}

}  // namespace dhcp
}  // namespace isc
