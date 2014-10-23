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

#ifndef CFG_HOSTS_H
#define CFG_HOSTS_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_container.h>
#include <dhcpsrv/subnet_id.h>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Represents the host reservations specified in the configuration file.
///
/// This class holds a collection of the host reservations (@c Host objects)
/// which can be retrieved using different search criteria.
///
/// In the typical case the reservations are searched using the client's MAC
/// address of DUID and a subnet that the client is connected to. The
/// reservations can be also retrieved using other parameters, such as reserved
/// IP address.
///
/// The reservations are added to this object by the configuration parsers,
/// when the new configuration is applied for the server. The reservations
/// are retrieved by the @c HostMgr class when the server is allocating or
/// renewing an address or prefix for the particular client.
class CfgHosts : public BaseHostDataSource {
public:

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
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available, e.g. DHCPv4 client case.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid = DuidPtr()) const;

    /// @brief Non-const version of the @c getAll const method.
    ///
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available, e.g. DHCPv4 client case.
    ///
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid = DuidPtr());

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
	/// @throw isc::NotImplemented.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
	/// @throw isc::NotImplemented
    virtual HostCollection
    getAll4(const asiolink::IOAddress& address);

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available.
    ///
    /// @return Const @c Host object using a specified HW address or DUID.
    /// @throw isc::dhcp::DuplicateHost if more than one candidate host has
    /// been found.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
         const DuidPtr& duid = DuidPtr()) const;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available.
    ///
    /// @return Non-const @c Host object using a specified HW address or DUID.
    /// @throw isc::dhcp::DuplicateHost if more than one candidate host has
    /// been found.
    virtual HostPtr
    get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
         const DuidPtr& duid = DuidPtr());

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid DUID or NULL if not available.
    ///
    /// @return Const @c Host object using a specified HW address or DUID.
    /// @throw isc::dhcp::DuplicateHost if more than one candidate host has
    /// been found.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const DuidPtr& duid,
         const HWAddrPtr& hwaddr = HWAddrPtr()) const;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid DUID or NULL if not available.
    ///
    /// @return Non-const @c Host object using a specified HW address or DUID.
    /// @throw isc::dhcp::DuplicateHost if more than one candidate host has
    /// been found.
    virtual HostPtr
    get6(const SubnetID& subnet_id, const DuidPtr& duid,
         const HWAddrPtr& hwaddr = HWAddrPtr());

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @throw isc::NotImplemented.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @throw isc::NotImplemented.
    virtual HostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len);


    /// @brief Adds a new host to the collection.
    ///
    /// @param host Pointer to the new @c Host object being added.
    ///
    /// @throw DuplicateHost If a host for a particular HW address or DUID
    /// has already been added to the IPv4 or IPv6 subnet.
    virtual void add(const HostPtr& host);

private:

    /// @brief Returns @c Host objects for the specific identifier and type.
    ///
    /// This private method is called by the @c CfgHosts::getAllInternal
    /// method which finds the @c Host objects using HW address or DUID.
    /// The retrieved objects are appended to the @c storage container.
    ///
    /// @param identifier Binary representation of the HW addres or DUID (or
    /// other future identifier).
    /// @param identifier_type The type of the supplied identifier.
    /// @param [out] storage Container to which the retreived objects are
    /// appended.
    /// @tparam One of the @c ConstHostCollection of @c HostCollection.
    template<typename Storage>
    void getAllInternal(const std::vector<uint8_t>& identifier,
                        const Host::IdentifierType& identifier_type,
                        Storage& storage) const;

    /// @brief Returns @c Host objects for the specified HW address or DUID.
    ///
    /// This private method is called by the @c CfgHosts::getAll methods to
    /// retrieve the @c Host objects using HW address or DUID. The retrieved
    /// objects are appended to the @c storage container.
    ///
    /// @param hwaddr HW address identifying a host.
    /// @param duid DUID identifying a host.
    /// @param [out] storage Container to which the retrieved objects are
    /// appended.
    /// @tparam One of the @c ConstHostCollection or @c HostCollection.
    template<typename Storage>
    void getAllInternal(const HWAddrPtr& hwaddr, const DuidPtr& duid,
                        Storage& storage) const;

    /// @brief Returns @c Host object connected to a subnet.
    ///
    /// This private method returns a pointer to the @c Host object identified
    /// by the HW address or DUID and connected to an IPv4 or IPv6 subnet.
    ///
    /// @param subnet_id IPv4 or IPv6 subnet identifier.
    /// @param subnet6 A boolean flag which indicates if the subnet identifier
    /// points to a IPv4 (if false) or IPv6 subnet (if true).
    /// @param hwaddr HW address identifying a host.
    /// @param duid DUID identifying a host.
    ///
    /// @return Pointer to the found host, or NULL if no host found.
    /// @throw isc::dhcp::DuplicateHost if method found more than one matching
    /// @c Host object.
    HostPtr getHostInternal(const SubnetID& subnet_id,
                            const bool subnet6,
                            const HWAddrPtr& hwaddr,
                            const DuidPtr& duid) const;

    /// @brief Multi-index container holding @c Host objects.
    HostContainer hosts_;

};

}
}

#endif // CFG_HOSTS_H
