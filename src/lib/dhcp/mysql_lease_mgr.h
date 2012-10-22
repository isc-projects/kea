// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __MYSQL_LEASE_MGR_H
#define __MYSQL_LEASE_MGR_H

#include <time.h>
#include <mysql.h>
#include <dhcp/lease_mgr.h>

namespace isc {
namespace dhcp {

/// @brief Abstract Lease Manager
///
/// This is a concrete API for the backend for the MySQL database.
class MySqlLeaseMgr : public LeaseMgr {
public:
    /// @brief Constructor
    ///
    /// Uses the following keywords in the parameters passed to it to
    /// connect to the database:
    /// - name - Name of the database to which to connect
    /// - host - Host name to which to connect
    /// - user - Username under which to connect.
    /// - password - Password for "user" on the database.
    ///
    /// If the database is successfully opened, the version number in the
    /// schema_version table will be checked against hard-coded value in
    /// the implementation file.
    ///
    /// Finally, all the SQL commands are pre-compiled.
    ///
    /// @param parameters A data structure relating keywords and values
    ///        concerned with the database.
    MySqlLeaseMgr(const ParameterMap& parameters);

    /// @brief Destructor (closes database)
    virtual ~MySqlLeaseMgr();

    /// @brief Adds an IPv4 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    ///
    /// @exception DbOperationError Database function failed
    virtual bool addLease(const Lease4Ptr& lease);

    /// @brief Adds an IPv6 lease.
    ///
    /// @param lease lease to be added
    ///
    /// @result true if the lease was added, false if not (because a lease
    ///         with the same address was already there).
    ///
    /// @exception DbOperationError Database function failed
    virtual bool addLease(const Lease6Ptr& lease);

    /// @brief Return IPv4 lease for specified IPv4 address and subnet_id
    ///
    /// This method is used to get a lease for specific subnet_id. There can be
    /// at most one lease for any given subnet, so this method returns a single
    /// pointer.
    ///
    /// @param addr address of the sought lease
    /// @param subnet_id ID of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr,
                                SubnetID subnet_id) const;

    /// @brief Returns an IPv4 lease for specified IPv4 address
    ///
    /// This method return a lease that is associated with a given address.
    /// For other query types (by hardware addr, by client-id) there can be
    /// several leases in different subnets (e.g. for mobile clients that
    /// got address in different subnets). However, for a single address
    /// there can be only one lease, so this method returns a pointer to
    /// a single lease, not a container of leases.
    ///
    /// @param addr address of the searched lease
    /// @param subnet_id ID of the subnet the lease must belong to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
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
    virtual Lease4Collection getLease4(const HWAddr& hwaddr) const;

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
    virtual Lease4Ptr getLease4(const HWAddr& hwaddr,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param clientid client identifier
    ///
    /// @return lease collection
    virtual Lease4Collection getLease4(const ClientId& clientid) const;

    /// @brief Returns existing IPv4 lease for specified client-id
    ///
    /// There can be at most one lease for a given HW address in a single
    /// pool, so this method with either return a single lease or NULL.
    ///
    /// @param clientid client identifier
    /// @param subnet_id identifier of the subnet that lease must belong to
    ///
    /// @return a pointer to the lease (or NULL if a lease is not found)
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const;

    /// @brief Returns existing IPv6 lease for a given IPv6 address.
    ///
    /// For a given address, we assume that there will be only one lease.
    /// The assumtion here is that there will not be site or link-local
    /// addresses used, so there is no way of having address duplication.
    ///
    /// @param addr address of the searched lease
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns existing IPv6 leases for a given DUID+IA combination
    ///
    /// Although in the usual case there will be only one lease, for mobile
    /// clients or clients with multiple static/fixed/reserved leases there
    /// can be more than one. Thus return type is a container, not a single
    /// pointer.
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Collection getLease6(const DUID& duid,
                                       uint32_t iaid) const;

    /// @brief Returns existing IPv6 lease for a given DUID+IA combination
    ///
    /// @param duid client DUID
    /// @param iaid IA identifier
    /// @param subnet_id subnet id of the subnet the lease belongs to
    ///
    /// @return smart pointer to the lease (or NULL if a lease is not found)
    virtual Lease6Ptr getLease6(const DUID& duid, uint32_t iaid,
                                SubnetID subnet_id) const;

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease4(const Lease4Ptr& lease4);

    /// @brief Updates IPv4 lease.
    ///
    /// @param lease4 The lease to be updated.
    ///
    /// If no such lease is present, an exception will be thrown.
    virtual void updateLease6(const Lease6Ptr& lease6);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease4(const isc::asiolink::IOAddress& addr);

    /// @brief Deletes a lease.
    ///
    /// @param addr IPv4 address of the lease to be deleted.
    ///
    /// @return true if deletion was successful, false if no such lease exists
    virtual bool deleteLease6(const isc::asiolink::IOAddress& addr);

    /// @brief Returns backend name.
    ///
    /// Each backend have specific name, e.g. "mysql" or "sqlite".
    virtual std::string getName() const;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    virtual std::string getDescription() const;

    /// @brief Returns backend version.
    ///
    /// @return Version number as a pair of unsigned integers.  "first" is the
    ///         major version number, "second" the minor number.
    ///
    /// @todo: We will need to implement 3 version functions eventually:
    /// A. abstract API version
    /// B. backend version
    /// C. database version (stored in the database scheme)
    ///
    /// and then check that:
    /// B>=A and B=C (it is ok to have newer backend, as it should be backward
    /// compatible)
    /// Also if B>C, some database upgrade procedure may be triggered
    virtual std::pair<uint32_t, uint32_t> getVersion() const;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// @exception DbOperationError if the commit failed.
    virtual void commit();


    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    ///
    /// @exception DbOperationError if the rollback failed.
    virtual void rollback();

    ///@{
    /// The following methods are used to convert between times and time
    /// intervals stored in the Lease object, and the times stored in the
    /// database.  The reason for the difference is because in the DHCP server,
    /// the cltt (Client Time Since Last Transmission) is the natural data; in
    /// the lease file - which may be read by the user - it is the expiry time
    /// of the lease.

    /// @brief Convert Lease Time to Database Times
    ///
    /// Within the DHCP servers, times are stored as cltt (client last transmit
    /// time) and valid_lft (valid lifetime).  In the database, the information
    /// is stored as lease_time (lease time) and expire (time of expiry of the
    /// lease).  They are related by the equations:
    ///
    /// - lease_time = valid_lft
    /// - expire = cltt + valid_lft
    ///
    /// This method converts from the times in the lease object into times
    /// able to be added to the database.
    ///
    /// @param cltt Client last transmit time
    /// @param valid_lft Valid lifetime
    /// @param expire Reference to MYSQL_TIME object where the expiry time of
    ///        the lease will be put.
    /// @param lease_time Reference to the time_t object where the lease time
    ///         will be put.
    static
    void convertToDatabaseTime(time_t cltt, uint32_t valid_lft,
                               MYSQL_TIME& expire, uint32_t& lease_time);

    /// @brief Convert Database Time to Lease Times
    ///
    /// Within the database, time is stored as lease_time (lease time) and
    /// expire (time of expiry of the lease).  In the DHCP server, the
    /// information is stored as cltt (client last transmit time) and
    /// valid_lft (valid lifetime).  These are related by the equations:
    ///
    /// - valid_lft = lease_time
    /// - cltt = expire - lease_time
    ///
    /// This method converts from the times in the database into times
    /// able to be inserted into the lease object.
    ///
    /// @param expire Reference to MYSQL_TIME object from where the expiry
    ///        time of the lease is taken.
    /// @param lease_time lifetime of the lease.
    /// @param cltt Reference to location where client last transmit time
    ///        is put.
    /// @param valid_lft Reference to location where valid lifetime is put.
    static
    void convertFromDatabaseTime(const MYSQL_TIME& expire, uint32_t lease_time,
                                 time_t& cltt, uint32_t& valid_lft);

    ///@}


private:
    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements
    enum StatementIndex {
        GET_LEASE6,         // Get lease 6 by address
        GET_VERSION,        // Obtain version number
        INSERT_LEASE6,      // Add entry to lease6 table
        NUM_STATEMENTS      // Number of statements
    };

    /// @brief Prepare Single Statement
    ///
    /// Creates a prepared statement from the text given and adds it to the
    /// statements_ vector at the given index.
    ///
    /// @param index Index into the statements_ vector into which the text
    ///        should be placed.  The vector must be big enough for the index
    ///        to be valid, else an exception will be thrown.
    /// @param text Text of the SQL statement to be prepared.
    ///
    /// @exception DbOperationError MySQL operation failed, exception will give
    ///            text indicating the reason.
    /// @exception InvalidParameter 'index' is not valid for the vector.
    void prepareStatement(StatementIndex index, const char* text);

    /// @brief Prepare statements
    ///
    /// Creates the prepared statements for all of the SQL statements used
    /// by the MySQL backend.
    void prepareStatements();

    /// @brief Open Database
    ///
    /// Opens the database using the information supplied in the parameters
    /// passed to the constructor.
    ///
    /// @exception DbOpenError Error opening the database
    void openDatabase();

    /// @brief Check Error and Throw Exception
    ///
    /// Virtually all MySQL functions return a status which, if non-zero,
    /// indicates an error.  This inline function conceals a lot of error
    /// checking/exception-throwing code.
    ///
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @exception DbOperationError Error doing a database operation
    inline void checkError(my_bool status, StatementIndex index,
                           const char* what) const {
        if (status != 0) {
            isc_throw(DbOperationError, what << " for <" <<
                      raw_statements_[index] << ">, reason: " <<
                      mysql_error(mysql_));
        }
    }

    // Members
    MYSQL*              mysql_;                 ///< MySQL context object
    std::vector<std::string> raw_statements_;   ///< Raw text of statements
    std::vector<MYSQL_STMT*> statements_;       ///< Prepared statements
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // __MYSQL_LEASE_MGR_H
