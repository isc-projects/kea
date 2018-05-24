// Copyright (C) 2016-2018 Deutsche Telekom AG.
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CQL_HOST_DATA_SOURCE_H
#define CQL_HOST_DATA_SOURCE_H

#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/cql_connection.h>

#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Forward declaration to the implementation of @ref CqlHostDataSource.
class CqlHostDataSourceImpl;

/// @brief Cassandra host data source
///
/// Implements @ref isc::dhcp::BaseHostDataSource interface customized to
/// Cassandra. Use of this backend implies that a Cassandra database is
/// available and that the Kea schema has been created within it.
///
/// The database schema is radically different than the MySQL and the
/// PostgreSQL schemas. Rather than creating a different table for
/// hosts, reservations, DHCPv4 options and DHCPv6 options
/// respectively, the data is denormalized  into a single table to
/// benefit from Cassandra's non-relational nature. To make up for the
/// lack of relations, on insertion, the reservations and options are
/// matched against hosts on the server and merged into database
/// entries. When retrieving, each database row is split into the
/// corresponding host, reservation and options.
///
/// There can be an inconsistency in the database due to the order of
/// the changes e.g. if you insert a host with no reservations and no
/// options followed by the same host with one reservation will result
/// in 2 entries versus inserting the host with reservation from the
/// beginning which will result in a single entry. In spite of this,
/// retrieving the host will give you the attached reservation in both
/// cases.
class CqlHostDataSource : public BaseHostDataSource {
public:
    /// @brief Constructor
    ///
    /// Uses the following keywords in the parameters passed to it to connect
    /// to the database:
    /// - keyspace
    /// - host
    /// - user
    /// - password
    /// - contact-points
    /// - reconnect-wait-time
    /// - connect-timeout
    /// - request-timeout
    /// - tcp-keepalive
    /// - tcp-nodelay
    ///
    /// For details regarding those paraemters, see
    /// @ref isc::dhcp::CqlConnection::openDatabase.
    ///
    /// Finally, all the CQL commands are pre-compiled.
    ///
    /// @param parameters a data structure relating keywords and values
    ///        concerned with the database.
    ///
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given
    /// @throw isc::dhcp::DbOpenError Error opening the database
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    explicit CqlHostDataSource(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Virtual destructor.
    ///
    /// Releases prepared CQL statements used by the backend.
    virtual ~CqlHostDataSource();

    /// @brief Adds a new host to the collection.
    ///
    /// The implementations of this method should guard against duplicate
    /// reservations for the same @ref Host, where possible. For example, when
    /// the reservation for the same @ref HWAddr and @ref SubnetID is added
    /// twice, @ref add() should throw a @ref DuplicateEntry exception. Note,
    /// that usually it is impossible to guard against adding duplicated @ref
    /// Host, where one instance is identified by different identifier types.
    ///
    /// @param host pointer to the new @ref Host being added.
    virtual void add(const HostPtr& host) override;

    /// @brief Attempts to delete a host by (subnet-id, address)
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identfier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false if the host was not
    ///     there.
    /// @throw various exceptions in case of errors
    virtual bool del(const SubnetID& subnet_id,
                     const asiolink::IOAddress& addr) override;

    /// @brief Attempts to delete a host by (subnet-id4, identifier-type,
    /// identifier).
    ///
    /// This method supports v4 hosts only.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    ///     an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not
    ///     there.
    /// @throw various exceptions in case of errors
    virtual bool del4(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) override;

    /// @brief Attempts to delete a host by (subnet-id6, identifier-type,
    /// identifier).
    ///
    /// This method supports v6 hosts only.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    ///     an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not
    ///     there.
    /// @throw various exceptions in case of errors
    virtual bool del6(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) override;

    /// @brief Return all @ref Host objects for the specified @ref HWAddr or
    /// @ref DUID.
    ///
    /// Returns all @ref Host objects which represent reservations
    /// for the specified HW address or DUID. Note, that this method may
    /// return multiple reservations because a particular client may have
    /// reservations in multiple subnets and the same client may be identified
    /// by HW address or DUID. The server is unable to verify that the specific
    /// DUID and HW address belong to the same client, until the client sends
    /// a DHCP message.
    ///
    /// Specifying both @ref HWAddr and @ref DUID is allowed for this method
    /// and results in returning all objects that are associated with hardware
    /// address OR duid. For example: if one @ref Host is associated with the
    /// specified @ref HWAddr and another @ref Host is associated with the
    /// specified @ref DUID, two hosts will be returned.
    ///
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available, e.g. DHCPv4 client case.
    ///
    /// @return collection of const @ref Host objects.
    virtual ConstHostCollection
    getAll(const HWAddrPtr& hwaddr,
           const DuidPtr& duid = DuidPtr()) const override;

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @ref Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    ///     an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Collection of const @ref Host objects.
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const override;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @ref Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @ref Host object is searched.
    ///
    /// @return Collection of const @ref Host objects.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const override;

    /// @brief Retrieves a single @ref Host connected to an IPv4 subnet.
    ///
    /// Implementations of this method should guard against the case when
    /// multiple instances of the @ref Host are present, e.g. when two @ref
    /// Host objects are found, one for the @ref DUID, another one for the @ref
    /// HWAddr. In such case, throw a @ref MultipleRecords exception.
    ///
    /// @param subnet_id subnet identifier to filter by
    /// @param hwaddr hardware address of the client to filter by or NULL if not
    ///     available
    /// @param duid client identifier to filter by or NULL if not available
    ///
    /// @return @ref ConstHostPtr to a @ref Host object using a specified @ref
    ///     HWAddr or @ref DUID
    ///
    /// @throw BadValue if both or neither of subnet_id and duid are specified
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const HWAddrPtr& hwaddr,
                              const DuidPtr& duid = DuidPtr()) const override;

    /// @brief Retrieves a @ref Host connected to an IPv4 subnet.
    ///
    /// The host is identified by specific identifier.
    ///
    /// @param subnet_id subnet identifier to filter by
    /// @param identifier_type identifier type to filter by
    /// @param identifier_begin pointer to the beginning of a buffer containing
    ///     a host identifier to filter by
    /// @param identifier_len length of the host identifier buffer
    ///
    /// @return @ref Host object for which a reservation has been made using the
    ///     specified identifier
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const override;

    /// @brief Retrieves a @ref Host connected to an IPv4 subnet.
    ///
    /// The host is identifier by specified IPv4 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Const @ref Host object
    ///
    /// @throw BadValue if address in not a valid IPv4address
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id,
         const asiolink::IOAddress& address) const override;

    /// @brief Retrieves a @ref Host connected to an IPv6 subnet.
    ///
    /// Implementations of this method should guard against the case when
    /// multiple instances of the @ref Host are present, e.g. when two
    /// @ref Host objects are found, one for the @ref DUID, another one for the
    /// @ref HWAddr. In such case, throw a @ref MultipleRecords exception.
    ///
    /// @param subnet_id subnet identifier to filter by
    /// @param hwaddr hardware address of the client to filter by or NULL if not
    ///     available
    /// @param duid client identifier to filter by or NULL if not available
    ///
    /// @return @ref Host object using a specified @ref HWAddr or @ref DUID
    ///
    /// @throw BadValue if both or neither of subnet_id and duid are specified
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id,
         const DuidPtr& duid,
         const HWAddrPtr& hwaddr = HWAddrPtr()) const override;

    /// @brief Returns a @ref Host connected to an IPv6 subnet.
    ///
    /// @param subnet_id subnet identifier to filter by
    /// @param identifier_type identifier type to filter by
    /// @param identifier_begin pointer to the beginning of a buffer containing
    ///     a host identifier to filter by
    /// @param identifier_len length of the host identifier buffer
    ///
    /// @return Const @ref Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr get6(const SubnetID& subnet_id,
                              const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const override;

    /// @brief Returns a @ref Host with the specified reservation prefix.
    ///
    /// @param prefix IPv6 prefix for which the @ref Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @ref Host object using a specified HW address or DUID.
    ///
    /// @throw MultipleRecords if two or more rows are returned from the
    ///     Cassandra database
    virtual ConstHostPtr get6(const asiolink::IOAddress& prefix,
                              const uint8_t prefix_len) const override;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id,
         const asiolink::IOAddress& address) const override;

    /// @brief Returns a collection of all the hosts.
    ///
    /// This method may return multiple @ref Host objects. It is only used in
    /// testing. It may be very slow when running on a production server with
    /// lots of hosts.
    ///
    /// @return Collection of const @ref Host objects.
    virtual ConstHostCollection
    getAllHosts() const;

    /// @brief Returns textual description of the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const;

    /// @brief Returns the name of the database.
    ///
    /// @return database name
    virtual std::string getName() const;

    /// @brief Return backend type
    ///
    /// @return backend type "cql"
    virtual std::string getType() const override;

    /// @brief Retrieves schema version from the DB.
    ///
    /// @return Version number stored in the database, as a pair of unsigned
    ///         integers. "first" is the major version number, "second" is the
    ///         minor version number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database
    ///        has failed.
    virtual VersionPair getVersion() const;

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations (no-op for Cassandra)
    virtual void commit() override;

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations  (no-op for Cassandra)
    virtual void rollback() override;

private:
    /// @brief Pointer to the implementation of the @ref CqlHostDataSource.
    CqlHostDataSourceImpl* impl_;
};  // class CqlHostDataSource

}  // namespace dhcp
}  // namespace isc

#endif  // CQL_HOST_DATA_SOURCE_H
