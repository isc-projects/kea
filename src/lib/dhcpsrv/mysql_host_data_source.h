// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef MYSQL_HOST_DATA_SOURCE_H
#define MYSQL_HOST_DATA_SOURCE_H

#include <dhcp/hwaddr.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/mysql_connection.h>

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>
#include <mysql.h>


namespace isc {
namespace dhcp {

// Define the current database schema values

const uint32_t CURRENT_VERSION_VERSION = 3;
const uint32_t CURRENT_VERSION_MINOR = 0;


// Forward declaration of the Host exchange objects.  These classes are defined
// in the .cc file.
class MySqlHostReservationExchange;


class MySqlHostDataSource : public BaseHostDataSource, public MySqlConnection {
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
	MySqlHostDataSource(const ParameterMap& parameters);

    /// @brief Destructor (closes database)
    virtual ~MySqlHostDataSource();

    /// @brief Return all hosts for the specified HW address or DUID.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for the specified HW address or DUID. Note, that this method may
    /// return multiple reservations because a particular client may have
    /// reservations in multiple subnets and the same client may be identified
    /// by HW address or DUID. The server is unable to verify that the specific
    /// DUID and HW address belong to the same client, until the client sends
    /// a DHCP message.
    ///
    /// Specifying both hardware address and DUID is allowed for this method
    /// and results in returning all objects that are associated with hardware
    /// address OR duid. For example: if one host is associated with the
    /// specified hardware address and another host is associated with the
    /// specified DUID, two hosts will be returned.
    ///
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available, e.g. DHCPv4 client case.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid = DuidPtr()) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
	///
	/// This method may return multiple @c Host objects if they are connected
	/// to different subnets.
	///
	/// @param address IPv4 address for which the @c Host object is searched.
	///
	/// @return Collection of const @c Host objects.
	virtual ConstHostCollection
	getAll4(const asiolink::IOAddress& address) const;

	/// @brief Returns a host connected to the IPv4 subnet.
	///
	/// Implementations of this method should guard against the case when
	/// mutliple instances of the @c Host are present, e.g. when two
	/// @c Host objects are found, one for the DUID, another one for the
	/// HW address. In such case, an implementation of this method
	/// should throw an exception.
	///
	/// @param subnet_id Subnet identifier.
	/// @param hwaddr HW address of the client or NULL if no HW address
	/// available.
	/// @param duid client id or NULL if not available.
	///
	/// @return Const @c Host object using a specified HW address or DUID.
	virtual ConstHostPtr
	get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
			const DuidPtr& duid = DuidPtr()) const;

	/// @brief Returns a host connected to the IPv4 subnet and having
	/// a reservation for a specified IPv4 address.
	///
	/// One of the use cases for this method is to detect collisions between
	/// dynamically allocated addresses and reserved addresses. When the new
	/// address is assigned to a client, the allocation mechanism should check
	/// if this address is not reserved for some other host and do not allocate
	/// this address if reservation is present.
	///
	/// Implementations of this method should guard against invalid addresses,
	/// such as IPv6 address.
	///
	/// @param subnet_id Subnet identifier.
	/// @param address reserved IPv4 address.
	///
	/// @return Const @c Host object using a specified IPv4 address.
	virtual ConstHostPtr
	get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

	/// @brief Returns a host connected to the IPv6 subnet.
	///
	/// Implementations of this method should guard against the case when
	/// mutliple instances of the @c Host are present, e.g. when two
	/// @c Host objects are found, one for the DUID, another one for the
	/// HW address. In such case, an implementation of this method
	/// should throw an exception.
	///
	/// @param subnet_id Subnet identifier.
	/// @param hwaddr HW address of the client or NULL if no HW address
	/// available.
	/// @param duid DUID or NULL if not available.
	///
	/// @return Const @c Host object using a specified HW address or DUID.
	virtual ConstHostPtr
	get6(const SubnetID& subnet_id, const DuidPtr& duid,
			const HWAddrPtr& hwaddr = HWAddrPtr()) const;

	/// @brief Returns a host using the specified IPv6 prefix.
	///
	/// @param prefix IPv6 prefix for which the @c Host object is searched.
	/// @param prefix_len IPv6 prefix length.
	///
	/// @return Const @c Host object using a specified HW address or DUID.
	virtual ConstHostPtr
	get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

	/// @brief Returns a host from specific subnet and reserved address.
	///
	/// @param subnet_id subnet identfier.
	/// @param address specified address.
	///
	/// @return Const @c host object that has a reservation for specified address.
	virtual ConstHostPtr
	get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

    /// @brief Adds a new host to the collection.
    ///
    /// The implementations of this method should guard against duplicate
    /// reservations for the same host, where possible. For example, when the
    /// reservation for the same HW address and subnet id is added twice, the
    /// implementation should throw an exception. Note, that usually it is
    /// impossible to guard against adding duplicated host, where one instance
    /// is identified by HW address, another one by DUID.
    ///
    /// @param host Pointer to the new @c Host object being added.
    virtual void add(const HostPtr& host);

    /// @brief Return backend type
	///
	/// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
	///
	/// @return Type of the backend.
	virtual std::string getType() const {
		return (std::string("mysql"));
	}

	/// @brief Returns backend name.
	///
	/// Each backend have specific name, e.g. "mysql" or "sqlite".
	///
	/// @return Name of the backend.
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
	/// Commits all pending database operations. On databases that don't
	/// support transactions, this is a no-op.
	///
	/// @throw DbOperationError If the commit failed.
	virtual void commit();

	/// @brief Rollback Transactions
	///
	/// Rolls back all pending database operations. On databases that don't
	/// support transactions, this is a no-op.
	///
	/// @throw DbOperationError If the rollback failed.
	virtual void rollback();

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements
	enum StatementIndex {
		INSERT_HOST,				// Insert new host to collection
		GET_HOST_HWADDR_DUID,		// Get hosts identified by DUID and/or HW address
		GET_HOST_ADDR,				// Get hosts with specified IPv4 address
		GET_HOST_SUBID4_DHCPID,		// Get host with specified IPv4 SubnetID and HW address and/or DUID
		GET_HOST_SUBID6_DHCPID,		// Get host with specified IPv6 SubnetID and HW address and/or DUID
		GET_HOST_SUBID_ADDR,		// Get host with specified IPv4 SubnetID and IPv4 address
		GET_HOST_PREFIX,			// Get host with specified IPv6 prefix
		GET_VERSION,                // Obtain version number
		NUM_STATEMENTS              // Number of statements
	};

private:
	/// @brief Add Host Code
	///
	/// This method performs adding a host operation.
	///	It binds the contents of the host object to
	/// the prepared statement and adds it to the database.
	///
	/// @param stindex Index of statemnent being executed
	/// @param bind MYSQL_BIND array that has been created for the host
	///
	/// @return true if the host was added, false if it was not.
	bool addHost(StatementIndex stindex, std::vector<MYSQL_BIND>& bind);

	/// @brief Get Host Collection Code
	///
	/// This method obtains multiple hosts from the database.
	///
	/// @param stindex Index of statement being executed
	/// @param bind MYSQL_BIND array for input parameters
	/// @param exchange Exchange object to use
	/// @param result ConstHostCollection object returned.  Note that any hosts in
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
	void getHostCollection(StatementIndex stindex, MYSQL_BIND* bind,
			boost::shared_ptr<MySqlHostReservationExchange> exchange,
			ConstHostCollection& result, bool single = false) const;

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
	/// @throw isc::dhcp::DbOperationError An operation on the open database has
	///        failed.
	inline void checkError(int status, StatementIndex index,
			const char* what) const {
		if (status != 0) {
			isc_throw(DbOperationError,
					what << " for <" << text_statements_[index] << ">, reason: "
					<< mysql_error(mysql_) << " (error code " << mysql_errno(mysql_) << ")");
		}
	}


    // Members

    /// The exchange objects are used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)
    boost::shared_ptr<MySqlHostReservationExchange> hostExchange_; ///< Exchange object

};

}
}

#endif // MYSQL_HOST_DATA_SOURCE_H
