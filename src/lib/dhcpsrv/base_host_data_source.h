// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_HOST_DATA_SOURCE_H
#define BASE_HOST_DATA_SOURCE_H

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <dhcpsrv/host.h>
#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>

#include <limits>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when the duplicate @c Host object is detected.
class DuplicateHost : public Exception {
public:
    DuplicateHost(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when a @c Host object is expected, but none are found.
class HostNotFound : public Exception {
public:
    HostNotFound(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when an address is already reserved by a @c Host
/// object (DuplicateHost is same identity, ReservedAddress same address).
class ReservedAddress : public Exception {
public:
    ReservedAddress(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when invalid IP address has been specified for
/// @c Host.
class BadHostAddress : public isc::BadValue {
public:
    BadHostAddress(const char* file, size_t line, const char* what) :
        isc::BadValue(file, line, what) { };
};

/// @brief Wraps value holding size of the page with host reservations.
class HostPageSize {
public:

    /// @brief Constructor.
    ///
    /// @param page_size page size value.
    /// @throw OutOfRange if page size is 0 or greater than uint32_t numeric
    /// limit.
    explicit HostPageSize(const size_t page_size) : page_size_(page_size) {
        if (page_size_ == 0) {
            isc_throw(OutOfRange, "page size of retrieved hosts must not be 0");
        }
        if (page_size_ > std::numeric_limits<uint32_t>::max()) {
            isc_throw(OutOfRange, "page size of retrieved hosts must not be greate than "
                     << std::numeric_limits<uint32_t>::max());
        }
    }

    const size_t page_size_; ///< Holds page size.
};

/// @brief Base interface for the classes implementing simple data source
/// for host reservations.
///
/// This abstract class defines an interface for the classes implementing
/// basic data source for host reservations. This interface allows for
/// adding new reservations (represented by @c Host objects) and retrieving
/// these reservations using various parameters such as HW address or DUID,
/// subnet identifier (either IPv4 or IPv6) or reserved IP address.
///
/// This interface DOES NOT specify the methods to manage existing
/// host reservations such as to remove one IPv6 reservation but leave
/// other reservations. It also lacks the methods used for preparing
/// the data to be added to the SQL database: commit, rollback etc.
/// Such methods are declared in other interfaces.
class BaseHostDataSource {
public:

    /// @brief Specifies the type of an identifier.
    ///
    /// This is currently used only by MySQL host data source for now, but
    /// it is envisaged that it will be used by other host data sources
    /// in the future. Also, this list will grow over time. It is likely
    /// that we'll implement other identifiers in the future, e.g. remote-id.
    ///
    /// Those value correspond directly to dhcp_identifier_type in hosts
    /// table in MySQL schema.
    enum IdType {
        ID_HWADDR = 0, ///< Hardware address
        ID_DUID = 1    ///< DUID/client-id
    };

    /// @brief Default destructor implementation.
    virtual ~BaseHostDataSource() { }

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
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const = 0;

    /// @brief Return all hosts in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id) const = 0;

    /// @brief Return all hosts in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// in a specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id) const = 0;

    /// @brief Return all hosts with a hostname.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname.
    ///
    /// @note: as hostnames are case-insensitive the search key is given
    /// in lower cases, search indexes should either be case-insensitive
    /// or be case-sensitive using the lower case version of hostnames.
    ///
    /// @param hostname The lower case hostname.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAllbyHostname(const std::string& hostname) const = 0;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAllbyHostname4(const std::string& hostname, const SubnetID& subnet_id) const = 0;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAllbyHostname6(const std::string& hostname, const SubnetID& subnet_id) const = 0;

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
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage4(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const = 0;

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
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage6(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const = 0;

    /// @brief Returns range of hosts.
    ///
    /// This method implements paged browsing of host databases. The
    /// parameters specify a page size, an index in sources and the
    /// starting host id of the range. If not zero this host id is
    /// excluded from the returned range. When a source is exhausted
    /// the index is updated. There is no guarantee about the order
    /// of returned host reservations, only the sources and
    /// reservations from the same source are ordered.
    ///
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const = 0;

    /// @brief Returns range of hosts.
    ///
    /// This method implements paged browsing of host databases. The
    /// parameters specify a page size, an index in sources and the
    /// starting host id of the range. If not zero this host id is
    /// excluded from the returned range. When a source is exhausted
    /// the index is updated. There is no guarantee about the order
    /// of returned host reservations, only the sources and
    /// reservations from the same source are ordered.
    ///
    /// @param source_index Index of the source.
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    ///
    /// @return Host collection (may be empty).
    virtual ConstHostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const = 0;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const = 0;

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
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id,
         const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const = 0;

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
    get4(const SubnetID& subnet_id,
         const asiolink::IOAddress& address) const = 0;

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
    /// @param address reserved IPv4 address
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const = 0;

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
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id,
         const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const = 0;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object using a specified IPv6 prefix.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const = 0;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) const = 0;

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
            const asiolink::IOAddress& address) const = 0;

    /// @brief Returns all hosts having a reservation for a specified
    /// address or delegated prefix (lease) in all subnets.
    ///
    /// In most cases it is desired that there is at most one reservation
    /// for a given IPv6 lease within a subnet. In a default configuration,
    /// the backend does not allow for inserting more than one host with
    /// the same IPv6 address or prefix.
    ///
    /// If the backend is configured to allow multiple hosts with reservations
    /// for the same IPv6 lease in the given subnet, this method can return
    /// more than one host per subnet.
    ///
    /// The typical use case when a single IPv6 lease is reserved for multiple
    /// hosts is when these hosts represent different interfaces of the same
    /// machine and each interface comes with a different MAC address. In that
    /// case, the same IPv6 lease is assigned regardless of which interface is
    /// used by the DHCP client to communicate with the server.
    ///
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const asiolink::IOAddress& address) const = 0;

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
    virtual void add(const HostPtr& host) = 0;

    /// @brief Attempts to delete hosts by (subnet-id, address)
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del(const SubnetID& subnet_id, const asiolink::IOAddress& addr) = 0;

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
    ///
    /// This method supports v4 hosts only.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del4(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin, const size_t identifier_len) = 0;

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
    ///
    /// This method supports v6 hosts only.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del6(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin, const size_t identifier_len) = 0;

    /// @brief Attempts to update an existing host entry.
    ///
    /// The implementation is common to multiple host data sources, so let's
    /// provide it in the base host data source. In some instances, it may
    /// require synchronization e.g. with transactions in case of databases.
    ///
    /// @param host the host up to date with the requested changes
    virtual void update(HostPtr const& host) {
        bool deleted(false);
        if (host->getIPv4SubnetID() != SUBNET_ID_UNUSED) {
            std::vector<uint8_t> const& identifier(host->getIdentifier());
            deleted = del4(host->getIPv4SubnetID(), host->getIdentifierType(), identifier.data(),
                identifier.size());
        } else if (host->getIPv6SubnetID() != SUBNET_ID_UNUSED) {
            std::vector<uint8_t> const& identifier(host->getIdentifier());
            deleted = del6(host->getIPv6SubnetID(), host->getIdentifierType(), identifier.data(),
                identifier.size());
        } else {
            isc_throw(HostNotFound, "Mandatory 'subnet-id' parameter missing.");
        }
        if (!deleted) {
            isc_throw(HostNotFound, "Host not updated (not found).");
        }
        add(host);
    }

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const = 0;

    /// @brief Return backend parameters
    ///
    /// Returns the backend parameters
    ///
    /// @return Parameters of the backend.
    virtual isc::db::DatabaseConnection::ParameterMap getParameters() const {
        return (isc::db::DatabaseConnection::ParameterMap());
    }

    /// @brief Commit Transactions
    ///
    /// Commits all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void commit() {};

    /// @brief Rollback Transactions
    ///
    /// Rolls back all pending database operations.  On databases that don't
    /// support transactions, this is a no-op.
    virtual void rollback() {};

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
    /// All backends are required to support the case when unique setting is
    /// @c true and they must use this setting by default.
    ///
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique or can be non-unique.
    /// @return true if the new setting was accepted by the backend or false
    /// otherwise.
    virtual bool setIPReservationsUnique(const bool unique) = 0;

    /// @brief Flag which indicates if the host manager has at least one
    /// unusable connection.
    ///
    /// @return true if there is at least one unusable connection, false
    /// otherwise
    virtual bool isUnusable() {
        return (false);
    }
};

/// @brief HostDataSource pointer
typedef boost::shared_ptr<BaseHostDataSource> HostDataSourcePtr;

/// @brief HostDataSource list
typedef std::vector<HostDataSourcePtr> HostDataSourceList;

}  // namespace dhcp
}  // namespace isc

#endif // BASE_HOST_DATA_SOURCE_H
