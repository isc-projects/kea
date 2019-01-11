// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_HOSTS_H
#define CFG_HOSTS_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_container.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/writable_host_data_source.h>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Represents the host reservations specified in the configuration file.
///
/// This class holds a collection of the host reservations (@c Host objects)
/// which can be retrieved using different search criteria.
///
/// In the typical case the reservations are searched using the client's MAC
/// address or DUID and a subnet that the client is connected to. The
/// reservations can be also retrieved using other parameters, such as reserved
/// IP address.
///
/// The reservations are added to this object by the configuration parsers,
/// when the new configuration is applied for the server. The reservations
/// are retrieved by the @c HostMgr class when the server is allocating or
/// renewing an address or prefix for the particular client.
class CfgHosts : public BaseHostDataSource, public WritableHostDataSource,
                 public isc::data::CfgToElement {
public:

    /// @brief Destructor.
    virtual ~CfgHosts() { }

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type One of the supported identifier types.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin, const size_t identifier_len) const;

    /// @brief Non-const version of the @c getAll const method.
    ///
    /// This method returns all @c Host objects which represent reservations
    /// for a specified identifier. This method may return multiple hosts
    /// because a particular client may have reservations in multiple subnets.
    ///
    /// @param identifier_type One of the supported identifier types.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Collection of non-const @c Host objects.
    virtual HostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len);

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual HostCollection
    getAll4(const asiolink::IOAddress& address);

    /// @brief Returns a collection of hosts using the specified IPv6 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv6 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const asiolink::IOAddress& address) const;

    /// @brief Returns a collection of hosts using the specified IPv6 address.
    ///
    /// This method may return multiple @c Host objects if they are connected
    /// to different subnets.
    ///
    /// @param address IPv6 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual HostCollection
    getAll6(const asiolink::IOAddress& address);

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
    get4(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) const;

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
         const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    ///
    /// @return Const @c Host object using a specified IPv4 address.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

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
    get6(const SubnetID& subnet_id, const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin, const size_t identifier_len) const;

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
         const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object for which specified prefix is reserved.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Non-const @c Host object for which specified prefix is
    /// reserved.
    virtual HostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len);

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address.
    ///
    /// @return Const @c Host object using a specified IPv6 address.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address.
    ///
    /// @return Const @c Host object using a specified IPv6 address.
    virtual HostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address);

    /// @brief Adds a new host to the collection.
    ///
    /// @param host Pointer to the new @c Host object being added.
    ///
    /// @throw DuplicateHost If a host for a particular HW address or DUID
    /// has already been added to the IPv4 or IPv6 subnet.
    virtual void add(const HostPtr& host);

    /// @brief Attempts to delete a host by address.
    ///
    /// This method supports both v4 and v6.
    /// @todo: Not implemented.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    virtual bool del(const SubnetID& subnet_id, const asiolink::IOAddress& addr);

    /// @brief Attempts to delete all hosts for a given IPv4 subnet.
    ///
    /// @param subnet_id Identifier of the subnet for which reservation should
    /// be deleted.
    /// @return Number of deleted hosts.
    virtual size_t delAll4(const SubnetID& subnet_id);

    /// @brief Attempts to delete a host by (subnet4-id, identifier, identifier-type)
    ///
    /// This method supports v4 only.
    /// @todo: Not implemented.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false otherwise.
    virtual bool del4(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Attempts to delete all hosts for a given IPv6 subnet.
    ///
    /// @param subnet_id Identifier of the subnet for which reservation should
    /// be deleted.
    /// @return Number of deleted hosts.
    virtual size_t delAll6(const SubnetID& subnet_id);

    /// @brief Attempts to delete a host by (subnet6-id, identifier, identifier-type)
    ///
    /// This method supports v6 only.
    /// @todo: Not implemented.
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false otherwise.
    virtual bool del6(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin, const size_t identifier_len);

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return (std::string("configuration file"));
    }

    /// @brief Unparse a configuration object
    ///
    /// host reservation lists are not autonomous so they are
    /// not returned directly but with the subnet where they are
    /// declared as:
    /// @code
    /// [
    ///   { "id": 123, "reservations": [ <resv1>, <resv2> ] },
    ///   { "id": 456, "reservations": [ <resv3 ] },
    ///   ...
    /// ]
    /// @endcode
    ///
    /// @ref isc::dhcp::CfgHostsList can be used to handle this
    ///
    /// @return a pointer to unparsed configuration
    isc::data::ElementPtr toElement() const;

private:

    /// @brief Returns @c Host objects for the specific identifier and type.
    ///
    /// This private method is called by the @c CfgHosts::getAllInternal
    /// method which finds the @c Host objects using specified identifier.
    /// The retrieved objects are appended to the @c storage container.
    ///
    /// @param identifier_type The type of the supplied identifier.
    /// @param identifier Pointer to a first byte of the identifier.
    /// @param identifier_len Length of the identifier.
    /// @param [out] storage Container to which the retrieved objects are
    /// appended.
    /// @tparam One of the @c ConstHostCollection of @c HostCollection.
    template<typename Storage>
    void getAllInternal(const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier,
                        const size_t identifier_len,
                        Storage& storage) const;

    /// @brief Returns @c Host objects for the specified IPv4 address.
    ///
    /// This private method is called by the @c CfgHosts::getAll4 methods
    /// to retrieve the @c Host for which the specified IPv4 address is
    /// reserved. The retrieved objects are appended to the @c storage
    /// container.
    ///
    /// @param address IPv4 address.
    /// @param [out] storage Container to which the retrieved objects are
    /// appended.
    /// @tparam One of the @c ConstHostCollection or @c HostCollection.
    template<typename Storage>
    void getAllInternal4(const asiolink::IOAddress& address,
                         Storage& storage) const;

    /// @brief Returns @c Host objects for the specified IPv6 address.
    ///
    /// This private method is called by the @c CfgHosts::getAll6 methods
    /// to retrieve the @c Host for which the specified IPv6 address is
    /// reserved. The retrieved objects are appended to the @c storage
    /// container.
    ///
    /// @param address IPv6 address.
    /// @param [out] storage Container to which the retrieved objects are
    /// appended.
    /// @tparam One of the @c ConstHostCollection or @c HostCollection.
    template<typename Storage>
    void getAllInternal6(const asiolink::IOAddress& address,
                         Storage& storage) const;


    /// @brief Returns @c Host objects for the specified (Subnet-id,IPv6 address) tuple.
    ///
    /// This private method is called by the @c CfgHosts::getAll6 methods
    /// to retrieve the @c Host for which the specified IPv6 address is
    /// reserved and is in specified subnet-id. The retrieved objects are
    /// appended to the @c storage container.
    ///
    /// @param subnet_id Subnet Identifier.
    /// @param address IPv6 address.
    /// @param [out] storage Container to which the retrieved objects are
    /// appended.
    /// @tparam One of the @c ConstHostCollection or @c HostCollection.
    template<typename Storage>
    void
    getAllInternal6(const SubnetID& subnet_id,
                    const asiolink::IOAddress& address,
                    Storage& storage) const;

    /// @brief Returns @c Host object connected to a subnet.
    ///
    /// This private method returns a pointer to the @c Host object using
    /// a specified identifier and connected to an IPv4 or IPv6 subnet.
    ///
    /// @param subnet_id IPv4 or IPv6 subnet identifier.
    /// @param subnet6 A boolean flag which indicates if the subnet identifier
    /// points to a IPv4 (if false) or IPv6 subnet (if true).
    /// @param identifier_type Identifier type.
    /// @param identifier Pointer to a first byte of the buffer holding an
    /// identifier.
    /// @param identifier_len Identifier length.
    ///
    /// @return Pointer to the found host, or NULL if no host found.
    /// @throw isc::dhcp::DuplicateHost if method found more than one matching
    /// @c Host object.
    HostPtr
    getHostInternal(const SubnetID& subnet_id, const bool subnet6,
                    const Host::IdentifierType& identifier_type,
                    const uint8_t* identifier,
                    const size_t identifier_len) const;

    /// @brief Returns the @c Host object holding reservation for the IPv6
    /// address and connected to the specific subnet.
    ///
    /// This private method is called by the public @c get6 method variants.
    ///
    /// @param subnet_id IPv6 subnet identifier.
    /// @param address IPv6 address.
    /// @tparam ReturnType One of @c HostPtr or @c ConstHostPtr
    /// @tparam One of the @c ConstHostCollection or @c HostCollection.
    ///
    /// @return Pointer to the found host, or NULL if no host found.
    /// @throw isc::dhcp::DuplicateHost if method found more than one matching
    /// @c Host object.
    template<typename ReturnType, typename Storage>
    ReturnType getHostInternal6(const SubnetID& subnet_id,
                                const asiolink::IOAddress& address) const;

    template<typename ReturnType>
    ReturnType getHostInternal6(const asiolink::IOAddress& prefix,
                                const uint8_t prefix_len) const;

    /// @brief Adds a new host to the collection.
    ///
    /// This is an internal method called by public @ref add. Contrary to its
    /// name, this is useful for both IPv4 and IPv6 hosts, as this adds the
    /// host to hosts_ storage that is shared by both families. Notes that
    /// for IPv6 host additional steps may be required (see @ref add6).
    ///
    /// @param host Pointer to the new @c Host object being added.
    ///
    /// @throw DuplicateHost If a host for a particular HW address or DUID
    /// has already been added to the IPv4 subnet.
    virtual void add4(const HostPtr& host);

    /// @brief Adds IPv6-specific reservation to hosts collection.
    ///
    /// This is an internal method called by public @ref add. This method adds
    /// IPv6 reservations (IPv6 addresses or prefixes reserved) to the hosts6_
    /// storage. Note the host has been added to the hosts_ already (in @ref add4).
    ///
    /// @param host Pointer to the new @c Host object being added.
    ///
    /// @throw DuplicateHost If a host for a particular HW address or DUID
    /// or for the particular address or prefix has already been added to
    /// the IPv6 subnet.
    virtual void add6(const HostPtr& host);

    /// @brief Multi-index container holding @c Host objects.
    ///
    /// It can be used for finding hosts by the following criteria:
    /// - IPv4 address
    /// - DUID
    /// - HW/MAC address
    HostContainer hosts_;

    /// @brief Multi-index container holding @c Host objects with v6 reservations.
    ///
    /// It can be used for finding hosts by the following criteria:
    /// - IPv6 address
    /// - IPv6 prefix
    HostContainer6 hosts6_;

    /// @brief Unparse a configuration object (DHCPv4 reservations)
    ///
    /// @return a pointer to unparsed configuration
    isc::data::ElementPtr toElement4() const;

    /// @brief Unparse a configuration object (DHCPv6 reservations)
    ///
    /// @return a pointer to unparsed configuration
    isc::data::ElementPtr toElement6() const;
};

/// @name Pointers to the @c CfgHosts objects.
//@{
/// @brief Non-const pointer.
typedef boost::shared_ptr<CfgHosts> CfgHostsPtr;

/// @brief Const pointer.
typedef boost::shared_ptr<const CfgHosts> ConstCfgHostsPtr;

//@}

}
}

#endif // CFG_HOSTS_H
