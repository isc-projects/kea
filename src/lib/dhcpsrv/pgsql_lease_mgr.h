// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef PGSQL_LEASE_MGR_H
#define PGSQL_LEASE_MGR_H

#include <dhcp/hwaddr.h>
#include <dhcpsrv/lease_mgr.h>

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>
#include <libpq-fe.h>

#include <vector>

namespace isc {
namespace dhcp {

/// @brief Structure used to bind C++ input values to dynamic SQL parameters
/// The structure contains three vectors which store the input values,
/// data lengths, and formats.  These vectors are passed directly into the
/// PostgreSQL execute call.
///
/// Note that the data values are stored as pointers. These pointers need to
/// valid for the duration of the PostgreSQL statement execution.  In other
/// words populating them with pointers to values that go out of scope before
/// statement is executed is a bad idea.
struct PsqlBindArray {
    /// @brief Vector of pointers to the data values.
    std::vector<const char *> values_;
    /// @brief Vector of data lengths for each value.
    std::vector<int> lengths_;
    /// @brief Vector of "format" for each value. A value of 0 means the
    /// value is text, 1 means the value is binary.
    std::vector<int> formats_;

    /// @brief Format value for text data.
    static const int TEXT_FMT;
    /// @brief Format value for binary data.
    static const int BINARY_FMT;

    /// @brief Constant string passed to DB for boolean true values.
    static const char* TRUE_STR;
    /// @brief Constant string passed to DB for boolean false values.
    static const char* FALSE_STR;

    /// @brief Fetches the number of entries in the array.
    /// @return Returns size_t containing the number of entries.
    size_t size() {
        return (values_.size());
    }

    /// @brief Indicates it the array is empty.
    /// @return Returns true if there are no entries in the array, false
    /// otherwise.
    bool empty() {

        return (values_.empty());
    }

    /// @brief Adds a char array to bind array based
    ///
    /// Adds a TEXT_FMT value to the end of the bind array, using the given
    /// char* as the data source. Note that value is expected to be NULL
    /// terminated.
    ///
    /// @param value char array containing the null-terminated text to add.
    void add(const char* value);

    /// @brief Adds an string value to the bind array
    ///
    /// Adds a TEXT formatted value to the end of the bind array using the
    /// given string as the data source.
    ///
    /// @param value std::string containing the value to add.
    void add(const std::string& value);

    /// @brief Adds a binary value to the bind array.
    ///
    /// Adds a BINARY_FMT value to the end of the bind array using the
    /// given vector as the data source.
    ///
    /// @param data vector of binary bytes.
    void add(const std::vector<uint8_t>& data);

    /// @brief Adds a boolean value to the bind array.
    ///
    /// Converts the given boolean value to its corresponding to PostgreSQL
    /// string value and adds it as a TEXT_FMT value to the bind array.
    ///
    /// @param value bool value to add.
    void add(const bool& value);

    /// @brief Dumps the contents of the array to a string.
    /// @return std::string containing the dump
    std::string toText();
};

// Forward definitions (needed for shared_ptr definitions)
// See pgsql_lease_mgr.cc file for actual class definitions
class PgSqlLease4Exchange;
class PgSqlLease6Exchange;

/// Defines PostgreSQL backend version: 1.0
const uint32_t PG_CURRENT_VERSION = 1;
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
    PgSqlLeaseMgr(const ParameterMap& parameters);

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
    virtual void deleteExpiredReclaimedLeases4(const uint32_t secs);

    /// @brief Deletes all expired-reclaimed DHCPv6 leases.
    ///
    /// @param secs Number of seconds since expiration of leases before
    /// they can be removed. Leases which have expired later than this
    /// time will not be deleted.
    virtual void deleteExpiredReclaimedLeases6(const uint32_t secs);

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

    /// @brief Checks a result set's SQL state against an error state.
    ///
    /// @param r result set to check
    /// @param error_state error state to compare against
    ///
    /// @return True if the result set's SQL state equals the error_state,
    /// false otherwise.
    bool compareError(PGresult*& r, const char* error_state);

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of compiled SQL
    /// statements
    enum StatementIndex {
        DELETE_LEASE4,              // Delete from lease4 by address
        DELETE_LEASE6,              // Delete from lease6 by address
        GET_LEASE4_ADDR,            // Get lease4 by address
        GET_LEASE4_CLIENTID,        // Get lease4 by client ID
        GET_LEASE4_CLIENTID_SUBID,  // Get lease4 by client ID & subnet ID
        GET_LEASE4_HWADDR,          // Get lease4 by HW address
        GET_LEASE4_HWADDR_SUBID,    // Get lease4 by HW address & subnet ID
        GET_LEASE6_ADDR,            // Get lease6 by address
        GET_LEASE6_DUID_IAID,       // Get lease6 by DUID and IAID
        GET_LEASE6_DUID_IAID_SUBID, // Get lease6 by DUID, IAID and subnet ID
        GET_VERSION,                // Obtain version number
        INSERT_LEASE4,              // Add entry to lease4 table
        INSERT_LEASE6,              // Add entry to lease6 table
        UPDATE_LEASE4,              // Update a Lease4 entry
        UPDATE_LEASE6,              // Update a Lease6 entry
        NUM_STATEMENTS              // Number of statements
    };

private:

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the SQL statements used
    /// by the PostgreSQL backend.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    /// @throw isc::InvalidParameter 'index' is not valid for the vector.  This
    ///        represents an internal error within the code.
    void prepareStatements();

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @throw NoDatabaseName Mandatory database name not given
    /// @throw DbOpenError Error opening the database
    void openDatabase();

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

    /// @brief Checks result of the r object
    ///
    /// Checks status of the operation passed as first argument and throws
    /// DbOperationError with details if it is non-success.
    ///
    /// @param r result of the last PostgreSQL operation
    /// @param index will be used to print out compiled statement name
    ///
    /// @throw isc::dhcp::DbOperationError Detailed PostgreSQL failure
    void checkStatementError(PGresult*& r, StatementIndex index) const;

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
    /// @return true if one or more rows were deleted, false if none were
    ///         deleted.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    bool deleteLeaseCommon(StatementIndex stindex, PsqlBindArray& bind_array);

    /// The exchange objects are used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)
    boost::scoped_ptr<PgSqlLease4Exchange> exchange4_; ///< Exchange object
    boost::scoped_ptr<PgSqlLease6Exchange> exchange6_; ///< Exchange object

    /// PostgreSQL connection handle
    PGconn* conn_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PGSQL_LEASE_MGR_H
