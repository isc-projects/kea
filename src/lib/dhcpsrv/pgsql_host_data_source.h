// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_HOST_DATA_SOURCE_H
#define PGSQL_HOST_DATA_SOURCE_H

#include <dhcpsrv/base_host_data_source.h>
#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>

namespace isc {
namespace dhcp {

/// Forward declaration to the implementation of the @ref PgSqlHostDataSource.
class PgSqlHostDataSourceImpl;

/// @brief Type of pointers to PgSqlHostDataSourceImpl.
typedef boost::shared_ptr<PgSqlHostDataSourceImpl> PgSqlHostDataSourceImplPtr;

/// Forward declaration for the thread context for the manager pool.
class PgSqlHostContext;

/// @brief Type of pointers to contexts.
typedef boost::shared_ptr<PgSqlHostContext> PgSqlHostContextPtr;

/// @brief PostgreSQL Host Data Source
///
/// This class implements the @ref isc::dhcp::BaseHostDataSource interface to
/// the PostgreSQL database. Use of this backend presupposes that a PostgreSQL
/// database is available and that the Kea schema has been created within it.
///
/// Reservations are uniquely identified by identifier type and value.
/// The currently supported values are defined in @ref Host::IdentifierType
/// as well as in host_identifier_table:
///
/// - IDENT_HWADDR
/// - IDENT_DUID
/// - IDENT_CIRCUIT_ID
/// - IDENT_CLIENT_ID
///
class PgSqlHostDataSource : public BaseHostDataSource {
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
    /// @throw isc::db::NoDatabaseName Mandatory database name not given
    /// @throw isc::db::DbOpenError Error opening the database
    /// @throw isc::db::DbOperationError An operation on the open database has
    ///        failed.
   PgSqlHostDataSource(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Virtual destructor.
    /// Frees database resources and closes the database connection through
    /// the destruction of member impl_.
    virtual ~PgSqlHostDataSource();

    /// @brief Adds a new host to the collection.
    ///
    /// The method will insert the given host and all of its children (v4
    /// options, v6 options, and v6 reservations) into the database.  It
    /// relies on constraints defined as part of the PostgreSQL schema to
    /// defend against duplicate entries and to ensure referential
    /// integrity.
    ///
    /// Violation of any of these constraints for a host will result in a
    /// DuplicateEntry exception:
    ///
    /// -# IPV4_ADDRESS and DHCP4_SUBNET_ID combination must be unique
    /// -# IPV6 ADDRESS and PREFIX_LEN combination must be unique
    /// -# DHCP ID, DHCP ID TYPE, and DHCP4_SUBNET_ID combination must be unique
    /// -# DHCP ID, DHCP ID TYPE, and DHCP6_SUBNET_ID combination must be unique
    ///
    /// In addition, violating the following referential constraints will
    /// a DbOperationError exception:
    ///
    /// -# DHCP ID TYPE must be defined in the HOST_IDENTIFIER_TYPE table
    /// -# For DHCP4 Options:
    ///  -# HOST_ID must exist with HOSTS
    ///  -# SCOPE_ID must be defined in DHCP_OPTION_SCOPE
    /// -# For DHCP6 Options:
    ///  -# HOST_ID must exist with HOSTS
    ///  -# SCOPE_ID must be defined in DHCP_OPTION_SCOPE
    /// -# For IPV6 Reservations:
    ///  -# HOST_ID must exist with HOSTS
    ///  -# Address and Prefix Length must be unique (DuplicateEntry)
    ///
    /// @param host Pointer to the new @c Host object being added.
    /// @throw DuplicateEntry or DbOperationError dependent on the constraint
    /// violation
    virtual void add(const HostPtr& host);

    /// @brief Attempts to delete a host by (subnet-id, address)
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
    /// in a specified subnet. Global reservations are returned for the
    /// subnet id 0.
    ///
    /// @param subnet_id subnet identifier to filter by
    ///
    /// @return Collection of const @ref Host objects.
    virtual ConstHostCollection getAll4(const SubnetID& subnet_id) const;

    /// @brief Return all hosts in a DHCPv6 subnet.
    ///
    /// This method returns all @ref Host objects which represent reservations
    /// in a specified subnet. Global reservations are returned for the
    /// subnet id 0.
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
    /// PostgreSQL uses the hosts_by_hostname index on LOWER(hostname).
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
    /// This method implements paged browsing of host databases. The
    /// parameters specify a page size, an index in sources and the
    /// starting host id of the range. If not zero this host id is
    /// excluded from the returned range. When a source is exhausted
    /// the index is updated. There is no guarantee about the order
    /// of returned host reservations, only the sources and
    /// reservations from the same source are ordered.
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
    /// This method implements paged browsing of host databases. The
    /// parameters specify a page size, an index in sources and the
    /// starting host id of the range. If not zero this host id is
    /// excluded from the returned range. When a source is exhausted
    /// the index is updated. There is no guarantee about the order
    /// of returned host reservations, only the sources and
    /// reservations from the same source are ordered.
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
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Const @c Host object using a specified IPv4 address.
    /// @throw BadValue is given an IPv6 address
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
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

    /// @brief Return backend type
    ///
    /// Returns the type of database as the string "postgresql".  This is
    /// same value as used for configuration purposes.
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("postgresql"));
    }

    /// @brief Returns the name of the open database
    ///
    /// @return String containing the name of the database
    virtual std::string getName() const;

    /// @brief Returns description of the backend.
    ///
    /// This description may be multiline text that describes the backend.
    ///
    /// @return Description of the backend.
    virtual std::string getDescription() const;

    /// @brief Returns backend version.
    ///
    /// The method is called by the constructor after opening the database
    /// but prior to preparing SQL statements, to verify that the schema version
    /// is correct. Thus it must not rely on a pre-prepared statement or
    /// formal statement execution error checking.
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

    /// @brief Context RAII Allocator.
    class PgSqlHostContextAlloc {
    public:

        /// @brief Constructor
        ///
        /// This constructor takes a context of the pool if one is available
        /// or creates a new one.
        ///
        /// @param mgr A parent instance
        PgSqlHostContextAlloc(const PgSqlHostDataSourceImpl& mgr);

        /// @brief Destructor
        ///
        /// This destructor puts back the context in the pool.
        ~PgSqlHostContextAlloc();

        /// @brief The context
        PgSqlHostContextPtr ctx_;

    private:
        /// @brief The manager
        const PgSqlHostDataSourceImpl& mgr_;
    };

private:
    /// @brief Pointer to the implementation of the @ref PgSqlHostDataSource.
    PgSqlHostDataSourceImplPtr impl_;
};

}
}

#endif // PGSQL_HOST_DATA_SOURCE_H
