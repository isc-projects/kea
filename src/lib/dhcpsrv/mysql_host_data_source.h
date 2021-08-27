// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_HOST_DATA_SOURCE_H
#define MYSQL_HOST_DATA_SOURCE_H

#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/base_host_data_source.h>
#include <mysql/mysql_connection.h>

#include <stdint.h>

#include <utility>
#include <string>

namespace isc {
namespace dhcp {

/// Forward declaration to the implementation of the @ref MySqlHostDataSource.
class MySqlHostDataSourceImpl;

/// @brief Type of pointers to MySqlHostDataSourceImpl.
typedef boost::shared_ptr<MySqlHostDataSourceImpl> MySqlHostDataSourceImplPtr;

/// Forward declaration for the thread context for the manager pool.
class MySqlHostContext;

/// @brief Type of pointers to contexts.
typedef boost::shared_ptr<MySqlHostContext> MySqlHostContextPtr;

/// @brief MySQL Host Data Source
///
/// This class implements the @ref isc::dhcp::BaseHostDataSource interface to
/// the MySQL database. Use of this backend presupposes that a MySQL database
/// is available and that the Kea schema has been created within it.
class MySqlHostDataSource : public BaseHostDataSource {
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
    /// @throw isc::db::DbOpenError Error opening the database or the
    /// schema version is invalid.
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
    MySqlHostDataSource(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Virtual destructor.
    ///
    /// Releases prepared MySQL statements used by the backend.
    virtual ~MySqlHostDataSource();

    /// @brief Return backend parameters
    ///
    /// Returns the backend parameters
    ///
    /// @return Parameters of the backend.
    virtual isc::db::DatabaseConnection::ParameterMap getParameters() const;

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

    /// @brief Attempts to delete hosts by (subnet-id, address)
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del(const SubnetID& subnet_id,
                     const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet4-id, identifier type, identifier)
    ///
    /// This method supports v4 hosts only.
    ///
    /// @param subnet_id subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del4(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len);

    /// @brief Attempts to delete a host by (subnet6-id, identifier type, identifier)
    ///
    /// This method supports v6 hosts only.
    ///
    /// @param subnet_id subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del6(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len);

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection getAll(const Host::IdentifierType& identifier_type,
                                       const uint8_t* identifier_begin,
                                       const size_t identifier_len) const;

    /// @brief Return all hosts in a DHCPv4 subnet.
    ///
    /// This method returns all @ref Host objects which represent reservations
    /// in a specified subnet.
    ///
    /// @param subnet_id subnet identifier to filter by
    ///
    /// @return Collection of const @ref Host objects.
    virtual ConstHostCollection getAll4(const SubnetID& subnet_id) const;

    /// @brief Return all hosts in a DHCPv6 subnet.
    ///
    /// This method returns all @ref Host objects which represent reservations
    /// in a specified subnet.
    ///
    /// @param subnet_id subnet identifier to filter by
    ///
    /// @return Collection of const @ref Host objects.
    virtual ConstHostCollection getAll6(const SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname.
    ///
    /// MySQL uses the case-insensitive hosts_by_hostname index on hostname.
    ///
    /// @param hostname The lower case hostname.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection getAllbyHostname(const std::string& hostname) const;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection getAllbyHostname4(const std::string& hostname,
                                                  const SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection getAllbyHostname6(const std::string& hostname,
                                                  const SubnetID& subnet_id) const;

    /// @brief Returns range of hosts in a DHCPv4 subnet.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Collection of const @c Host objects (may be empty).
    virtual ConstHostCollection getPage4(const SubnetID& subnet_id,
                                         size_t& source_index,
                                         uint64_t lower_host_id,
                                         const HostPageSize& page_size) const;

    /// @brief Returns range of hosts in a DHCPv6 subnet.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Collection of const @c Host objects (may be empty).
    virtual ConstHostCollection getPage6(const SubnetID& subnet_id,
                                         size_t& source_index,
                                         uint64_t lower_host_id,
                                         const HostPageSize& page_size) const;

    /// @brief Returns range of hosts.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Collection of const @c Host objects (may be empty).
    virtual ConstHostCollection getPage4(size_t& source_index,
                                         uint64_t lower_host_id,
                                         const HostPageSize& page_size) const;

    /// @brief Returns range of hosts.
    ///
    /// This method returns a page of @c Host objects which represent
    /// reservations.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Collection of const @c Host objects (may be empty).
    virtual ConstHostCollection getPage6(size_t& source_index,
                                         uint64_t lower_host_id,
                                         const HostPageSize& page_size) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection getAll4(const asiolink::IOAddress& address) const;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const;

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
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv4 subnet and having
    /// a reservation for a specified address.
    ///
    /// In most cases it is desired that there is at most one reservation
    /// for a given IPv4 address within a subnet. In a default configuration,
    /// the backend does not allow for inserting more than one host with
    /// the same IPv4 reservation. In that case, the number of hosts returned
    /// by this function is 0 or 1.
    ///
    /// If the backend is configured to allow multiple hosts with reservations
    /// for the same IPv4 address in the given subnet, this method can return
    /// more than one host.
    ///
    /// The typical use case when a single IPv4 address is reserved for multiple
    /// hosts is when these hosts represent different interfaces of the same
    /// machine and each interface comes with a different MAC address. In that
    /// case, the same IPv4 address is assigned regardless of which interface is
    /// used by the DHCP client to communicate with the server.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr get6(const SubnetID& subnet_id,
                              const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object using a specified IPv6 prefix.
    virtual ConstHostPtr get6(const asiolink::IOAddress& prefix,
                              const uint8_t prefix_len) const;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual ConstHostPtr get6(const SubnetID& subnet_id,
                              const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv6 subnet and having
    /// a reservation for a specified address or delegated prefix (lease).
    ///
    /// In most cases it is desired that there is at most one reservation
    /// for a given IPv6 lease within a subnet. In a default configuration,
    /// the backend does not allow for inserting more than one host with
    /// the same IPv6 address or prefix. In that case, the number of hosts
    /// returned by this function is 0 or 1.
    ///
    /// If the backend is configured to allow multiple hosts with reservations
    /// for the same IPv6 lease in the given subnet, this method can return
    /// more than one host.
    ///
    /// The typical use case when a single IPv6 lease is reserved for multiple
    /// hosts is when these hosts represent different interfaces of the same
    /// machine and each interface comes with a different MAC address. In that
    /// case, the same IPv6 lease is assigned regardless of which interface is
    /// used by the DHCP client to communicate with the server.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

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
    /// @throw isc::db::DbOperationError An operation on the open database
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

    /// @brief Controls whether IP reservations are unique or non-unique.
    ///
    /// In a typical case, the IP reservations are unique and backends verify
    /// prior to adding a host reservation to the database that the reservation
    /// for a given IP address/subnet does not exist. In some cases it may be
    /// required to allow non-unique IP reservations, e.g. in the case when a
    /// host has several interfaces and independently of which interface is used
    /// by this host to communicate with the DHCP server the same IP address
    /// should be assigned. In this case the @c unique value should be set to
    /// false to disable the checks for uniqueness on the backend side.
    ///
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique within the subnet or can be non-unique.
    /// @return always true because this backend supports both the case when
    /// the addresses must be unique and when they may be non-unique.
    virtual bool setIPReservationsUnique(const bool unique);

    /// @brief Flag which indicates if the host manager has at least one
    /// unusable connection.
    ///
    /// @return true if there is at least one unusable connection, false
    /// otherwise
    virtual bool isUnusable();

    /// @brief Context RAII Allocator.
    class MySqlHostContextAlloc {
    public:

        /// @brief Constructor
        ///
        /// This constructor takes a context of the pool if one is available
        /// or creates a new one.
        ///
        /// @param mgr A parent instance
        MySqlHostContextAlloc(MySqlHostDataSourceImpl& mgr);

        /// @brief Destructor
        ///
        /// This destructor puts back the context in the pool.
        ~MySqlHostContextAlloc();

        /// @brief The context
        MySqlHostContextPtr ctx_;

    private:
        /// @brief The manager
        MySqlHostDataSourceImpl& mgr_;
    };

private:
    /// @brief Pointer to the implementation of the @ref MySqlHostDataSource.
    MySqlHostDataSourceImplPtr impl_;
};

}
}

#endif // MYSQL_HOST_DATA_SOURCE_H
