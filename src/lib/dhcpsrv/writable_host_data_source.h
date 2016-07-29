// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid = DuidPtr()) = 0;

    /// @brief Non-const version of the @c getAll const method.
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
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) = 0;

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
    /// @return Non-const @c Host object using a specified HW address or DUID.
    virtual HostPtr
    get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
         const DuidPtr& duid = DuidPtr()) = 0;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a begining of a buffer containing
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
    /// @return Non-const @c Host object using a specified HW address or DUID.
    virtual HostPtr
    get6(const SubnetID& subnet_id, const DuidPtr& duid,
         const HWAddrPtr& hwaddr = HWAddrPtr()) = 0;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a begining of a buffer containing
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
    /// @return Non-const @c Host object using a specified HW address or DUID.
    virtual HostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) = 0;

};

}
}

#endif // WRITABLE_HOST_DATA_SOURCE_H
