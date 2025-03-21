// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_BACKEND_H
#define RADIUS_BACKEND_H

#include <dhcpsrv/base_host_data_source.h>

namespace isc {
namespace radius {

class RadiusBackendImpl;

/// @brief Host backend for Radius.
///
/// This backend handles no data. It can be called when:
///  - an identifier type other than the configured one is used
///  - by the hook for a new client so not yet in the host cache
/// It is a soft error to call it in another case.
class RadiusBackend : public isc::dhcp::BaseHostDataSource {
public:

    /// @brief Constructor.
    RadiusBackend();

    /// @brief Destructor.
    virtual ~RadiusBackend();

    ///
    /// From base class.
    ///

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// Not supported.
    ///
    /// @return Empty collection.
    virtual isc::dhcp::ConstHostCollection
    getAll(const isc::dhcp::Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const override;

    /// @brief Return all hosts in a specified DHCPv4 subnet.
    ///
    /// Not supported.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAll4(const isc::dhcp::SubnetID& subnet_id) const override;

    /// @brief Return all hosts in a specified DHCPv6 subnet.
    ///
    /// Not supported.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAll6(const isc::dhcp::SubnetID& subnet_id) const override;

    /// @brief Return all hosts with a hostname.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname.
    ///
    /// @param hostname The lower case hostname.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAllbyHostname(const std::string& hostname) const override;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAllbyHostname4(const std::string& hostname,
                      const isc::dhcp::SubnetID& subnet_id) const override;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAllbyHostname6(const std::string& hostname,
                      const isc::dhcp::SubnetID& subnet_id) const override;

    /// @brief Return range of hosts in a specified DHCPv4 subnet.
    ///
    /// Not supported.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getPage4(const isc::dhcp::SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const override;

    /// @brief Return range of hosts in a specified DHCPv6 subnet.
    ///
    /// Not supported.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getPage6(const isc::dhcp::SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const override;

    /// @brief Return range of hosts.
    ///
    /// Not supported.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const override;

    /// @brief Return range of hosts.
    ///
    /// Not supported.
    ///
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const dhcp::HostPageSize& page_size) const override;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// Not supported.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    /// @return Always returns an empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAll4(const isc::asiolink::IOAddress& address) const override;

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
    virtual isc::dhcp::ConstHostPtr
    get4(const isc::dhcp::SubnetID& subnet_id,
         const isc::dhcp::Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const override;

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// Not implemented.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return null.
    virtual isc::dhcp::ConstHostPtr
    get4(const isc::dhcp::SubnetID& subnet_id,
         const isc::asiolink::IOAddress& address) const override;

    /// @brief Returns all hosts connected to the IPv4 subnet and having
    /// a reservation for a specified address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAll4(const isc::dhcp::SubnetID& subnet_id,
            const isc::asiolink::IOAddress& address) const override;

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
    virtual isc::dhcp::ConstHostPtr
    get6(const isc::dhcp::SubnetID& subnet_id,
         const isc::dhcp::Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const override;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// Not implemented.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return null.
    virtual isc::dhcp::ConstHostPtr
    get6(const isc::asiolink::IOAddress& prefix,
         const uint8_t prefix_len) const override;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// Not implemented.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return null.
    virtual isc::dhcp::ConstHostPtr
    get6(const isc::dhcp::SubnetID& subnet_id,
         const isc::asiolink::IOAddress& address) const override;

    /// @brief Returns all hosts connected to the IPv6 subnet and having
    /// a reservation for a specified address or delegated prefix (lease).
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return Empty collection of const @c Host objects.
    virtual isc::dhcp::ConstHostCollection
    getAll6(const isc::dhcp::SubnetID& subnet_id,
            const isc::asiolink::IOAddress& address) const override;

    /// @brief Returns a collection of hosts using the specified IPv6 address/prefix.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv6 address for which the @c Host object is searched.
    ///
    /// @return Empty collection of const @c Host objects.
    virtual dhcp::ConstHostCollection
    getAll6(const isc::asiolink::IOAddress& address) const override;

    /// @brief Adds a new host to the collection.
    ///
    /// The implementations of this method should guard against duplicate
    /// reservations for the same host, where possible. For example, when the
    /// reservation for the same HW address and subnet id is added twice, the
    /// implementation should throw an exception. Note, that usually it is
    /// impossible to guard against adding duplicated host, where one instance
    /// is identified by HW address, another one by DUID.
    ///
    /// Not implemented.
    ///
    /// @param host Pointer to the new @c Host object being added.
    /// @note does nothing, in particular does not throw so the entry
    /// can be added to the host cache.
    virtual void add(const isc::dhcp::HostPtr& host) override;

    /// @brief Attempts to delete a host by (subnet-id, address)
    ///
    /// Not implemented for Radius.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return false.
    virtual bool del(const isc::dhcp::SubnetID& subnet_id,
                     const isc::asiolink::IOAddress& addr) override;

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
    ///
    /// Not implemented for Radius.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return false.
    virtual bool del4(const isc::dhcp::SubnetID& subnet_id,
                      const isc::dhcp::Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) override;

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
    ///
    /// Not implemented for Radius.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return false.
    virtual bool del6(const isc::dhcp::SubnetID& subnet_id,
                      const isc::dhcp::Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) override;

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const override {
        return ("radius");
    }

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
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique within the subnet or can be non-unique.
    /// @return true when addresses must be unique, false otherwise because
    /// this backend does not support specifying the same IP address in multiple
    /// host reservations.
    virtual bool setIPReservationsUnique(const bool unique) override;

    /// @brief Return unexpected calls for IPv4.
    size_t getUnexpected4() const;

    /// @brief Return unexpected calls for IPv6.
    size_t getUnexpected6() const;

protected:
    /// @brief Implementation.
    boost::shared_ptr<RadiusBackendImpl> impl_;
};

/// @brief Pointer to host backend.
typedef boost::shared_ptr<RadiusBackend> RadiusBackendPtr;

/// @brief Implementation of host backend for Radius.
class RadiusBackendImpl {
public:

    /// @brief Constructor.
    RadiusBackendImpl();

    /// @brief Destructor.
    virtual ~RadiusBackendImpl();

    /// Host backend method in not const variant.

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
    isc::dhcp::ConstHostPtr
    get4(const isc::dhcp::SubnetID& subnet_id,
         const isc::dhcp::Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len);

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
    isc::dhcp::ConstHostPtr
    get6(const isc::dhcp::SubnetID& subnet_id,
         const isc::dhcp::Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len);

    /// @brief Unexpected call counter - IPv4.
    size_t xcount4_;

    /// @brief Unexpected call counter - IPv6.
    size_t xcount6_;
};

} // end of namespace radius
} // end of namespace isc

#endif // RADIUS_BACKEND_H
