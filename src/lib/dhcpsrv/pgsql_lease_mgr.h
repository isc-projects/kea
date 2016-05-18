// Copyright (C) 2013-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_LEASE_MGR_H
#define PGSQL_LEASE_MGR_H

#include <dhcp/hwaddr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/pgsql_connection.h>
#include <dhcpsrv/pgsql_exchange.h>

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>

#include <vector>

namespace isc {
namespace dhcp {

// Forward definitions (needed for shared_ptr definitions)
// See pgsql_lease_mgr.cc file for actual class definitions
class PgSqlLease4Exchange;
class PgSqlLease6Exchange;

/// Defines PostgreSQL backend version: 2.0
const uint32_t PG_CURRENT_VERSION = 2;
const uint32_t PG_CURRENT_MINOR = 0;

/// @brief PostgreSQL Lease Manager
///
/// This class provides the \ref isc::dhcp::LeaseMgr interface to the PostgreSQL
/// database.  Use of this backend presupposes that a PostgreSQL database is
/// available and that the Kea schema has been created within it.
class PgSqlLeaseMgr : public LeaseMgr {
public:

    /// @brief Constructor
    ///
    /// Uses the following keywords in the parameters passed to it to
    /// connect to the database:
    /// - name - Name of the database to which to connect (mandatory)
    /// - host - Host to which to connect (optional, defaults to "localhost")
    /// - user - Username under which to connect (optional)
    /// - password - Password for "user" on the database (optional)
    ///
    /// If the database is successfully opened, the version number in the
    /// schema_version table will be checked against hard-coded value in
    /// the implementation file.
    ///
    /// Finally, all the SQL commands are pre-compiled.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given
    /// @throw isc::dhcp::DbOpenError Error opening the database
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    PgSqlLeaseMgr(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor (closes database)
    virtual ~PgSqlLeaseMgr();

    /// @brief Local version of getDBVersion() class method
    static std::string getDBVersion();

    /// @brief Adds an IPv4 lease
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool addLease(const Lease4Ptr& lease);

    /// @brief Adds an IPv6 lease
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool addLease(const Lease6Ptr& lease);

    /// @brief Returns an IPv4 lease for specified IPv4 address
    ///
    /// This method return a lease that is associated with a given address.
    /// For other query types (by hardware addr, by Client ID) there can be
    /// several leases in different subnets (e.g. for mobile clients that
    /// got address in different subnets). However, for a single address
    /// there can be only one lease, so this method returns a pointer to
    /// a single lease, not a container of leases.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv4 leases for specified hardware address.
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param hwaddr hardware address of the client
    ///
    /// @return lease collection
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Collection getLease4(const isc::dhcp::HWAddr& hwaddr) const;

    /// @brief Returns existing IPv4 leases for specified hardware address
    ///        and a subnet
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param hwaddr hardware address of the client
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const isc::dhcp::HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 leases for specified client-id
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Collection getLease4(const ClientId& clientid) const;

    /// @brief Returns IPv4 lease for the specified client identifier, HW
    /// address and subnet identifier.
    ///
    /// @param client_id A client identifier.
    /// @param hwaddr Hardware address.
    /// @param subnet_id A subnet identifier.
    ///
    /// @return A pointer to the lease or NULL if the lease is not found.
    /// @throw isc::NotImplemented On every call as this function is currently
    /// not implemented for the PostgreSQL backend.
    virtual Lease4Ptr getLease4(const ClientId& client_id, const HWAddr& hwaddr,
                                SubnetID subnet_id) const;


    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// For a given address, we assume that there will be only one lease.
    /// The assumption here is that there will not be site or link-local
    /// addresses used, so there is no way of having address duplication.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::BadValue record retrieved from database had an invalid
    ///        lease type field.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Ptr getLease6(Lease::Type type,
                                const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv6 leases for a given DUID+IA combination
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    ///
    /// @throw isc::BadValue record retrieved from database had an invalid
    ///        lease type field.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                       uint32_t iaid) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param type specifies lease type: (NA, TA or PD)
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id subnet id of the subnet the lease belongs to
    ///
    /// @return lease collection (may be empty if no lease is found)
    ///
    /// @throw isc::BadValue record retrieved from database had an invalid
    ///        lease type field.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                        uint32_t iaid, SubnetID subnet_id) const;

    /// @brief Returns a collection of expired DHCPv6 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases6(Lease6Collection& expired_leases,
                                   const size_t max_leases) const;


    /// @brief Returns a collection of expired DHCPv4 leases.
    ///
    /// This method returns at most @c max_leases expired leases. The leases
    /// returned haven't been reclaimed, i.e. the database query must exclude
    /// reclaimed leases from the results returned.
    ///
    /// @param [out] expired_leases A container to which expired leases returned
    /// by the database backend are added.
    /// @param max_leases A maximum number of leases to be returned. If this
    /// value is set to 0, all expired (but not reclaimed) leases are returned.
    virtual void getExpiredLeases4(Lease4Collection& expired_leases,
                                   const size_t max_leases) const;

    /// @brief Updates IPv4 lease.
    ///
    /// Updates the record of the lease in the database (as identified by the
    /// address) with the data in the passed lease object.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// @throw isc::dhcp::NoSuchLease Attempt to update a lease that did not
    ///        exist.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual void updateLease4(const Lease4Ptr& lease4);

    /// @brief Updates IPv6 lease.
    ///
    /// Updates the record of the lease in the database (as identified by the
    /// address) with the data in the passed lease object.
    ///
    /// @param lease6 The lease to be updated.
    ///
    /// @throw isc::dhcp::NoSuchLease Attempt to update a lease that did not
    ///        exist.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual void updateLease6(const Lease6Ptr& lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr Address of the lease to be deleted.  This can be an IPv4
    ///             address or an IPv6 address.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual bool deleteLease(const isc::asiolink::IOAddress& addr);

    /// @brief Deletes all expired-reclaimed DHCPv4 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases4(const uint32_t secs);

    /// @brief Deletes all expired-reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    ///
    /// @return Number of leases deleted.
    virtual uint64_t deleteExpiredReclaimedLeases6(const uint32_t secs);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("postgresql"));
    }

    /// @brief Returns name of the database.
    ///
    /// @return database name
    virtual std::string getName() const;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    virtual std::pair<uint32_t, uint32_t> getVersion() const;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.
    ///
    /// @throw DbOperationError Iif the commit failed.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.
    ///
    /// @throw DbOperationError If the rollback failed.
    virtual void rollback();

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of compiled SQL
    /// statements
    enum StatementIndex {
        DELETE_LEASE4,              // Delete from lease4 by address
        DELETE_LEASE4_STATE_EXPIRED,// Delete expired lease4s in certain state.
        DELETE_LEASE6,              // Delete from lease6 by address
        DELETE_LEASE6_STATE_EXPIRED,// Delete expired lease6s in certain state.
        GET_LEASE4_ADDR,            // Get lease4 by address
        GET_LEASE4_CLIENTID,        // Get lease4 by client ID
        GET_LEASE4_CLIENTID_SUBID,  // Get lease4 by client ID & subnet ID
        GET_LEASE4_HWADDR,          // Get lease4 by HW address
        GET_LEASE4_HWADDR_SUBID,    // Get lease4 by HW address & subnet ID
        GET_LEASE4_EXPIRE,          // Get expired lease4
        GET_LEASE6_ADDR,            // Get lease6 by address
        GET_LEASE6_DUID_IAID,       // Get lease6 by DUID and IAID
        GET_LEASE6_DUID_IAID_SUBID, // Get lease6 by DUID, IAID and subnet ID
        GET_LEASE6_EXPIRE,          // Get expired lease6
        GET_VERSION,                // Obtain version number
        INSERT_LEASE4,              // Add entry to lease4 table
        INSERT_LEASE6,              // Add entry to lease6 table
        UPDATE_LEASE4,              // Update a Lease4 entry
        UPDATE_LEASE6,              // Update a Lease6 entry
        NUM_STATEMENTS              // Number of statements
    };

private:

    /// @brief Add Lease Common Code
    ///
    /// This method performs the common actions for both flavours (V4 and V6)
    /// of the addLease method.  It binds the contents of the lease object to
    /// the prepared statement and adds it to the database.
    ///
    /// @param stindex Index of statement being executed
    /// @param bind_array array that has been created for the type
    ///        of lease in question.
    ///
    /// @return true if the lease was added, false if it was not added because
    ///         a lease with that address already exists in the database.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    bool addLeaseCommon(StatementIndex stindex, PsqlBindArray& bind_array);

    /// @brief Get Lease Collection Common Code
    ///
    /// This method performs the common actions for obtaining multiple leases
    /// from the database.
    ///
    /// @param stindex Index of statement being executed
    /// @param bind_array array containing the where clause input parameters
    /// @param exchange Exchange object to use
    /// @param result Returned collection of Leases Note that any leases in
    ///        the collection when this method is called are not erased: the
    ///        new data is appended to the end.
    /// @param single If true, only a single data item is to be retrieved.
    ///        If more than one is present, a MultipleRecords exception will
    ///        be thrown.
    ///
    /// @throw isc::dhcp::BadValue Data retrieved from the database was invalid.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::dhcp::MultipleRecords Multiple records were retrieved
    ///        from the database where only one was expected.
    template <typename Exchange, typename LeaseCollection>
    void getLeaseCollection(StatementIndex stindex, PsqlBindArray& bind_array,
                            Exchange& exchange, LeaseCollection& result,
                            bool single = false) const;

    /// @brief Gets Lease4 Collection
    ///
    /// Gets a collection of Lease4 objects.  This is just an interface to
    /// the get lease collection common code.
    ///
    /// @param stindex Index of statement being executed
    /// @param bind_array array containing the where clause input parameters
    /// @param lease LeaseCollection object returned.  Note that any leases in
    ///        the collection when this method is called are not erased: the
    ///        new data is appended to the end.
    ///
    /// @throw isc::dhcp::BadValue Data retrieved from the database was invalid.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::dhcp::MultipleRecords Multiple records were retrieved
    ///        from the database where only one was expected.
    void getLeaseCollection(StatementIndex stindex, PsqlBindArray& bind_array,
                            Lease4Collection& result) const {
        getLeaseCollection(stindex, bind_array, exchange4_, result);
    }

    /// @brief Get Lease6 Collection
    ///
    /// Gets a collection of Lease6 objects.  This is just an interface to
    /// the get lease collection common code.
    ///
    /// @param stindex Index of statement being executed
    /// @param bind_array array containing input parameters for the query
    /// @param lease LeaseCollection object returned.  Note that any existing
    ///        data in the collection is erased first.
    ///
    /// @throw isc::dhcp::BadValue Data retrieved from the database was invalid.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::dhcp::MultipleRecords Multiple records were retrieved
    ///        from the database where only one was expected.
    void getLeaseCollection(StatementIndex stindex, PsqlBindArray& bind_array,
                            Lease6Collection& result) const {
        getLeaseCollection(stindex, bind_array, exchange6_, result);
    }

    /// @brief Get Lease4 Common Code
    ///
    /// This method performs the common actions for the various getLease4()
    /// methods.  It acts as an interface to the getLeaseCollection() method,
    /// but retrieveing only a single lease.
    ///
    /// @param stindex Index of statement being executed
    /// @param bind_array array containing input parameters for the query
    /// @param lease Lease4 object returned
    void getLease(StatementIndex stindex, PsqlBindArray& bind_array,
                  Lease4Ptr& result) const;

    /// @brief Get Lease6 Common Code
    ///
    /// This method performs the common actions for the various getLease4()
    /// methods.  It acts as an interface to the getLeaseCollection() method,
    /// but retrieveing only a single lease.
    ///
    /// @param stindex Index of statement being executed
    /// @param bind_array array containing input parameters for the query
    /// @param lease Lease6 object returned
    void getLease(StatementIndex stindex, PsqlBindArray& bind_array,
                  Lease6Ptr& result) const;

    /// @brief Get expired leases common code.
    ///
    /// This method retrieves expired and not reclaimed leases from the
    /// lease database. The returned leases are ordered by the expiration
    /// time. The maximum number of leases to be returned is specified
    /// as an argument.
    ///
    /// @param [out] expired_leases Reference to the container where the
    ///        retrieved leases are put.
    /// @param max_leases Maximum number of leases to be returned.
    /// @param statement_index One of the @c GET_LEASE4_EXPIRE or
    ///        @c GET_LEASE6_EXPIRE.
    ///
    /// @tparam One of the @c Lease4Collection or @c Lease6Collection.
    template<typename LeaseCollection>
    void getExpiredLeasesCommon(LeaseCollection& expired_leases,
                                const size_t max_leases,
                                StatementIndex statement_index) const;

    /// @brief Update lease common code
    ///
    /// Holds the common code for updating a lease.  It binds the parameters
    /// to the prepared statement, executes it, then checks how many rows
    /// were affected.
    ///
    /// @param stindex Index of prepared statement to be executed
    /// @param bind_array array containing lease values and where clause
    /// parameters for the update.
    /// @param lease Pointer to the lease object whose record is being updated.
    ///
    /// @throw NoSuchLease Could not update a lease because no lease matches
    ///        the address given.
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    template <typename LeasePtr>
    void updateLeaseCommon(StatementIndex stindex, PsqlBindArray& bind_array,
                           const LeasePtr& lease);

    /// @brief Delete lease common code
    ///
    /// Holds the common code for deleting a lease.  It binds the parameters
    /// to the prepared statement, executes the statement and checks to
    /// see how many rows were deleted.
    ///
    /// @param stindex Index of prepared statement to be executed
    /// @param bind_array array containing lease values and where clause
    /// parameters for the delete
    ///
    /// @return Number of deleted leases.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    uint64_t deleteLeaseCommon(StatementIndex stindex,
                               PsqlBindArray& bind_array);

    /// @brief Delete expired-reclaimed leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    /// @param statement_index One of the @c DELETE_LEASE4_STATE_EXPIRED or
    ///        @c DELETE_LEASE6_STATE_EXPIRED.
    ///
    /// @return Number of leases deleted.
    uint64_t deleteExpiredReclaimedLeasesCommon(const uint32_t secs,
                                                StatementIndex statement_index);

    /// The exchange objects are used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)
    boost::scoped_ptr<PgSqlLease4Exchange> exchange4_; ///< Exchange object
    boost::scoped_ptr<PgSqlLease6Exchange> exchange6_; ///< Exchange object

    /// PostgreSQL connection handle
    PgSqlConnection conn_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PGSQL_LEASE_MGR_H
