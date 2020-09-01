// Copyright (C) 2014-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef WRITABLE_HOST_DATA_SOURCE_H
#define WRITABLE_HOST_DATA_SOURCE_H

namespace isc {
namespace dhcp {

/// @brief Interface for retrieving writable host reservations.
///
/// This interface specifies the methods which return pointers to the
/// @c Host objects, which can be modified. Deriving from this interface
/// is needed if the class implementation must return the pointers to the
/// objects which may be modified by the caller. Such classes usually
/// also derive from the @c BaseHostDataSource to implement methods which
/// return the const objects.
class WritableHostDataSource {
public:

    /// @brief Default destructor implementation.
    virtual ~WritableHostDataSource() { }

    /// @brief Non-const version of the @c getAll const method.
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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) = 0;

    /// @brief Returns a collection of hosts in the specified DHCPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll4(const SubnetID& subnet_id) = 0;

    /// @brief Returns a collection of hosts in the specified DHCPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll6(const SubnetID& subnet_id) = 0;

    /// @brief Return all hosts with a hostname.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname.
    ///
    /// @param hostname The lower case hostname.
    ///
    /// @return Collection of @c Host objects.
    virtual HostCollection
    getAllbyHostname(const std::string& hostname) = 0;

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of @c Host objects.
    virtual HostCollection
    getAllbyHostname4(const std::string& hostname, const SubnetID& subnet_id) = 0;

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// using a specified hostname in a specified subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Collection of @c Host objects.
    virtual HostCollection
    getAllbyHostname6(const std::string& hostname, const SubnetID& subnet_id) = 0;

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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getPage4(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) = 0;

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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getPage6(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) = 0;

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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) = 0;

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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) = 0;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
    /// @return Collection of @c Host objects.
    virtual HostCollection
    getAll4(const asiolink::IOAddress& address) = 0;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Non-const @c Host object for which reservation has been made
    /// using the specified identifier.
    virtual HostPtr
    get4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) = 0;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Non-const @c Host object for which reservation has been made
    /// using the specified identifier.
    virtual HostPtr
    get6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) = 0;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Non-const @c Host object using a specified IPv6 prefix.
    virtual HostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) = 0;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    ///
    /// @return @c Host object using a specified IPv6 address/prefix.
    virtual HostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) = 0;
};

}
}

#endif // WRITABLE_HOST_DATA_SOURCE_H
