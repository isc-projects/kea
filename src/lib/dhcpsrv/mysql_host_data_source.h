// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_HOST_DATA_SOURCE_H
#define MYSQL_HOST_DATA_SOURCE_H

#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/db_exceptions.h>
#include <dhcpsrv/mysql_connection.h>

namespace isc {
namespace dhcp {

/// Forward declaration to the implementation of the @ref MySqlHostDataSource.
class MySqlHostDataSourceImpl;

/// @brief MySQL Host Data Source
///
/// This class implements the @ref isc::dhcp::BaseHostDataSource interface to
/// the MySQL database. Use of this backend presupposes that a MySQL database
/// is available and that the Kea schema has been created within it.
class MySqlHostDataSource: public BaseHostDataSource {
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
    MySqlHostDataSource(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Virtual destructor.
    ///
    /// Releases prepared MySQL statements used by the backend.
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

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a begining of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin, const size_t identifier_len) const;

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
    /// should throw an MultipleRecords exception.
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

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a begining of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) const;

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
    /// should throw an MultipleRecords exception.
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

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a begining of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object using a specified HW address or DUID.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

    /// @brief Adds a new host to the collection.
    ///
    /// The implementations of this method should guard against duplicate
    /// reservations for the same host, where possible. For example, when the
    /// reservation for the same HW address and subnet id is added twice, the
    /// addHost method should throw an DuplicateEntry exception. Note, that
    /// usually it is impossible to guard against adding duplicated host, where
    /// one instance is identified by HW address, another one by DUID.
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
    /// Each backend have specific name.
    ///
    /// @return "mysql".
    virtual std::string getName() const;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const;

    /// @brief Returns backend version.
    ///
    /// @return Version number stored in the database, as a pair of unsigned
    ///         integers. "first" is the major version number, "second" the
    ///         minor number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database
    ///        has failed.
    virtual std::pair<uint32_t, uint32_t> getVersion() const;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.
    virtual void commit();

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.
    virtual void rollback();

private:

    /// @brief Pointer to the implementation of the @ref MySqlHostDataSource.
    MySqlHostDataSourceImpl* impl_;
};

}
}

#endif // MYSQL_HOST_DATA_SOURCE_H
