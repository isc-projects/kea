// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MEMORY_HOST_DATA_SOURCE_H
#define MEMORY_HOST_DATA_SOURCE_H

#include <dhcpsrv/host_data_source_factory.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Simple host data source implementation for tests.
///
/// It used vector<HostPtr> as a storage and iterates through all hosts when
/// conducting operations. Most operations are skeleton methods that don't
/// work, just several are implemented. Those are used in the tests.
class MemHostDataSource : public virtual BaseHostDataSource {
public:

    /// @brief Constructor.
    MemHostDataSource() : next_host_id_(0) {
    }

    /// @brief Destructor.
    virtual ~MemHostDataSource() = default;

    /// BaseHostDataSource methods.

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This may return hosts from multiple subnets.
    ///
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const;

    /// @brief Return all hosts in a DHCPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id) const;

    /// @brief Return all hosts in a DHCPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname.
    ///
    /// @param hostname The lower case hostname.
    virtual ConstHostCollection
    getAllbyHostname(const std::string& hostname) const;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAllbyHostname4(const std::string& hostname, const SubnetID& subnet_id) const;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAllbyHostname6(const std::string& hostname, const SubnetID& subnet_id) const;

    /// @brief Return range of hosts in a DHCPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    virtual ConstHostCollection
    getPage4(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Return range of hosts in a DHCPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    virtual ConstHostCollection
    getPage6(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Return range of hosts.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    virtual ConstHostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Return range of hosts.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    virtual ConstHostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// Currently not implemented.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    /// @return Empty collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;


    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id,
         const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const;

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    /// @return Const @c Host object using a specified IPv4 address.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id,
         const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv4 subnet and having
    /// a reservation for a specified address.
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
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id,
         const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// Currently not implemented.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    /// @return Const @c Host object using a specified IPv6 prefix.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

    /// @brief Returns all hosts connected to the IPv6 subnet and having
    /// a reservation for a specified address or delegated prefix (lease).
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const;

    /// @brief Adds a new host to the collection.
    ///
    /// @param host Pointer to the new @c Host object being added.
    virtual void add(const HostPtr& host);

    /// @brief Attempts to delete a host by (subnet-id, address)
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del(const SubnetID& subnet_id, const asiolink::IOAddress& addr);

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
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
                      const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
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
                      const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return ("mem");
    }

    /// More lease backend?

    /// @brief Returns name of the database or file used by the backend
    /// @return "mem" string"
    virtual std::string getName() const {
        return (std::string("mem"));
    }

    /// @brief Returns description of the backend.
    /// @return description
    virtual std::string getDescription() const {
        return (std::string("In memory storage, mostly useful for testing."));
    }

    /// @brief Returns version this backend
    /// @return two numbers that each represent practical value of this backend.
    virtual std::pair<uint32_t, uint32_t> getVersion() const {
        return (std::make_pair(0,0));
    }

    /// Specific methods.

    /// @brief Returns store size.
    ///
    /// @return number of hosts in the store.
    virtual size_t size() const;

    /// @brief Controls whether IP reservations are unique or non-unique.
    ///
    /// In a typical case, the IP reservations are unique and backends verify
    /// prior to adding a host reservation to the database that the reservation
    /// for a given IP address does not exist. In some cases it may be required
    /// to allow non-unique IP reservations, e.g. in the case when a host has
    /// several interfaces and independently of which interface is used by this
    /// host to communicate with the DHCP server the same IP address should be
    /// assigned. In this case the @c unique value should be set to false to
    /// disable the checks for uniqueness on the backend side.
    ///
    /// All backends are required to support the case when unique setting is
    /// @c true and they must use this setting by default.
    ///
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique or can be non-unique.
    /// @return true if the new setting was accepted by the backend or false
    /// otherwise.
    virtual bool setIPReservationsUnique(const bool) {
        return (true);
    }

protected:
    // This is very simple storage.

    /// @brief Store
    std::vector<HostPtr> store_;

    /// @brief Next host id
    uint64_t next_host_id_;
};

/// Pointer to the Mem host data source.
typedef boost::shared_ptr<MemHostDataSource> MemHostDataSourcePtr;

/// @brief Factory function.
///
/// @param parameters
/// @return A pointer to a base host data source instance.
HostDataSourcePtr
memFactory(const db::DatabaseConnection::ParameterMap& /*parameters*/);

} // namespace isc::dhcp::test
} // namespace isc::dhcp
} // namespace isc

#endif
