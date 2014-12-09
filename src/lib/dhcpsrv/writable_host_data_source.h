// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef WRITABLE_HOST_DATA_SOURCE_H
#define WRITABLE_HOST_DATA_SOURCE_H

#include <dhcpsrv/base_host_data_source.h>

namespace isc {
namespace dhcp {

/// @brief Interface for retrieving writable host reservations.
///
/// This interface extends the @c BaseHostDataSource with methods which return
/// pointers to the @c Host objects, which can be modified.
class WritableHostDataSource : public BaseHostDataSource {
public:

    using BaseHostDataSource::getAll;
    using BaseHostDataSource::getAll4;
    using BaseHostDataSource::get4;
    using BaseHostDataSource::get6;

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
