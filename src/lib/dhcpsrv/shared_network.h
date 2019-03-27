// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_NETWORK_H
#define SHARED_NETWORK_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief A tag for accessing random access index.
struct SharedNetworkRandomAccessIndexTag { };

/// @brief A tag for accessing index by shared network name.
struct SharedNetworkNameIndexTag { };

/// @brief A tag for accessing index by server identifier.
struct SharedNetworkServerIdIndexTag { };

/// @brief Tag for the index for searching by shared network modification
/// time.
struct SharedNetworkModificationTimeIndexTag { };

/// @brief Shared network holding IPv4 subnets.
///
/// Specialization of the @ref Network4 class for IPv4 shared networks.
class SharedNetwork4 : public virtual Network4,
                       public boost::enable_shared_from_this<SharedNetwork4> {
public:

    /// @brief Constructor.
    ///
    /// Sets name of the shared network.
    explicit SharedNetwork4(const std::string& name)
        : name_(name), subnets_() {
    }

    /// @brief Returns a name of the shared network.
    std::string getName() const {
        return (name_);
    }

    /// @brief Sets new name for the shared network.
    ///
    /// @param name New name for the shared network.
    void setName(const std::string& name) {
        name_ = name;
    }

    /// @brief Adds IPv4 subnet to a shared network.
    ///
    /// @param subnet Pointer to a subnet being added to this shared network.
    ///
    /// @throw isc::BadValue if subnet is null.
    /// @throw isc::DuplicateSubnetID if a subnet with the given subnet id
    /// already exists in this shared network.
    /// @throw InvalidOperation if a subnet is already associated with some
    /// shared network.
    void add(const Subnet4Ptr& subnet);

    /// @brief Removes subnet from a shared network.
    ///
    /// @param subnet_id Identifier of a subnet to be removed.
    ///
    /// @throw BadValue When specified subnet doesn't exist.
    void del(const SubnetID& subnet_id);

    /// @brief Removes all subnets from a shared network.
    void delAll();

    /// @brief Returns a pointer to the collection of subnets within this
    /// shared network.
    const Subnet4Collection* getAllSubnets() const {
        return (&subnets_);
    }

    /// @brief Returns a subnet for a specified subnet id.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Shared pointer to a subnet using this id or null pointer
    /// if such subnet doesn't exist within shared network.
    Subnet4Ptr getSubnet(const SubnetID& subnet_id) const;

    /// @brief Retrieves next available IPv4 subnet within shared network.
    ///
    /// See documentation for @ref SharedNetwork4::getNextSubnet.
    ///
    /// @param first_subnet Pointer to a subnet from which the caller is
    /// iterating over subnets within shared network. This is typically a
    /// subnet selected during "subnet selection" step.
    /// @param current_subnet Identifier of a subnet for which next subnet is
    /// to be found.
    ///
    /// @return Pointer to next subnet or null pointer if no more subnets found.
    ///
    /// @throw isc::BadValue if invalid arguments specified, e.g. unable to
    /// find first or current subnet within shared network.
    Subnet4Ptr getNextSubnet(const Subnet4Ptr& first_subnet,
                             const SubnetID& current_subnet) const;

    /// @brief Attempts to find a subnet which is more likely to include available
    /// leases than selected subnet.
    ///
    /// When allocating unreserved leases from a shared network it is important to
    /// remember from which subnet within the shared network we have been recently
    /// handing out leases. The allocation engine can use that information to start
    /// trying allocation of the leases from that subnet rather than from the default
    /// subnet selected for this client. Starting from the default subnet causes a
    /// risk of having to walk over many subnets with exhausted address pools before
    /// getting to the subnet with available leases. This method attempts to find
    /// such subnet by inspecting "last allocation" timestamps. The one with most
    /// recent timestamp is selected.
    ///
    /// The preferred subnet must also fulfil the condition of equal client classes
    /// with the @c selected_subnet.
    ///
    /// @todo Need extensions to this logic when we support more than one client
    /// class for a subnet.
    ///
    /// @param selected_subnet Pointer to a currently selected subnet.
    ///
    /// @return Pointer to a preferred subnet. It may be the same as @c selected_subnet
    /// if no better subnet was found.
    Subnet4Ptr getPreferredSubnet(const Subnet4Ptr& selected_subnet) const;

    /// @brief Unparses shared network object.
    ///
    /// @return A pointer to unparsed shared network configuration.
    virtual data::ElementPtr toElement() const;

private:

    /// @brief Holds a name of a shared network.
    std::string name_;

    /// @brief Collection of IPv4 subnets within shared network.
    Subnet4Collection subnets_;
};

/// @brief Pointer to @ref SharedNetwork4 object.
typedef boost::shared_ptr<SharedNetwork4> SharedNetwork4Ptr;

/// @brief Multi index container holding shared networks.
///
/// This is multi index container can hold pointers to @ref SharedNetwork4
/// objects. It provides indexes for shared network lookups using properties
/// such as shared network's name.
typedef boost::multi_index_container<
    // Multi index container holds pointers to the shared networks.
    SharedNetwork4Ptr,
    boost::multi_index::indexed_by<
        // First is the random access index allowing for accessing objects
        // just like we'd do with vector.
        boost::multi_index::random_access<
            boost::multi_index::tag<SharedNetworkRandomAccessIndexTag>
        >,
        // Second index allows for access by shared network's name.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SharedNetworkNameIndexTag>,
            boost::multi_index::const_mem_fun<SharedNetwork4, std::string,
                                              &SharedNetwork4::getName>
        >,
        // Third index allows for access by server identifier specified for the
        // network.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SharedNetworkServerIdIndexTag>,
            boost::multi_index::const_mem_fun<Network4, asiolink::IOAddress,
                                              &Network4::getServerId>
        >,
        // Fourth index allows for searching using subnet modification time.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SharedNetworkModificationTimeIndexTag>,
            boost::multi_index::const_mem_fun<data::StampedElement,
                                              boost::posix_time::ptime,
                                              &data::StampedElement::getModificationTime>
        >
    >
> SharedNetwork4Collection;

/// @brief Shared network holding IPv6 subnets.
///
/// Specialization of the @ref Network6 class for IPv6 shared networks.
class SharedNetwork6 : public virtual Network6,
                       public boost::enable_shared_from_this<SharedNetwork6> {
public:

    /// @brief Constructor.
    ///
    /// Sets name of the shared network.
    explicit SharedNetwork6(const std::string& name)
        : name_(name), subnets_() {
    }

    /// @brief Returns a name of the shared network.
    std::string getName() const {
        return (name_);
    }

    /// @brief Sets new name for the shared network.
    ///
    /// @param name New name for the shared network.
    void setName(const std::string& name) {
        name_ = name;
    }

    /// @brief Adds IPv6 subnet to a shared network.
    ///
    /// @param subnet Pointer to a subnet being added to this shared network.
    ///
    /// @throw isc::BadValue if subnet is null.
    /// @throw isc::DuplicateSubnetID if a subnet with the given subnet id
    /// already exists in this shared network.
    /// @throw InvalidOperation if a subnet is already associated with some
    /// shared network.
    void add(const Subnet6Ptr& subnet);

    /// @brief Removes subnet from a shared network.
    ///
    /// @param subnet_id Identifier of a subnet to be removed.
    ///
    /// @throw BadValue When specified subnet doesn't exist.
    void del(const SubnetID& subnet_id);

    /// @brief Removes all subnets from a shared network.
    void delAll();

    /// @brief Returns a pointer to the collection of subnets within this
    /// shared network.
    const Subnet6Collection* getAllSubnets() const {
        return (&subnets_);
    }

    /// @brief Returns a subnet for a specified subnet id.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Shared pointer to a subnet using this id or null pointer
    /// if such subnet doesn't exist within shared network.
    Subnet6Ptr getSubnet(const SubnetID& subnet_id) const;

    /// @brief Retrieves next available IPv6 subnet within shared network.
    ///
    /// See documentation for @ref SharedNetwork6::getNextSubnet.
    ///
    /// @param first_subnet Pointer to a subnet from which the caller is
    /// iterating over subnets within shared network. This is typically a
    /// subnet selected during "subnet selection" step.
    /// @param current_subnet Identifier of a subnet for which next subnet is
    /// to be found.
    ///
    /// @return Pointer to next subnet or null pointer if no more subnets found.
    ///
    /// @throw isc::BadValue if invalid arguments specified, e.g. unable to
    /// find first or current subnet within shared network.
    Subnet6Ptr getNextSubnet(const Subnet6Ptr& first_subnet,
                             const SubnetID& current_subnet) const;

    /// @brief Attempts to find a subnet which is more likely to include available
    /// leases than selected subnet.
    ///
    /// When allocating unreserved leases from a shared network it is important to
    /// remember from which subnet within the shared network we have been recently
    /// handing out leases. The allocation engine can use that information to start
    /// trying allocation of the leases from that subnet rather than from the default
    /// subnet selected for this client. Starting from the default subnet causes a
    /// risk of having to walk over many subnets with exhausted address pools before
    /// getting to the subnet with available leases. This method attempts to find
    /// such subnet by inspecting "last allocation" timestamps. The one with most
    /// recent timestamp is selected.
    ///
    /// The preferred subnet must also fulfil the condition of equal client classes
    /// with the @c selected_subnet.
    ///
    /// @param selected_subnet Pointer to a currently selected subnet.
    /// @param lease_type Type of the lease for which preferred subnet should be
    /// returned.
    ///
    /// @return Pointer to a preferred subnet. It may be the same as @c selected_subnet
    /// if no better subnet was found.
    Subnet6Ptr getPreferredSubnet(const Subnet6Ptr& selected_subnet,
                                  const Lease::Type& lease_type) const;

    /// @brief Unparses shared network object.
    ///
    /// @return A pointer to unparsed shared network configuration.
    virtual data::ElementPtr toElement() const;

private:

    /// @brief Holds a name of a shared network.
    std::string name_;

    /// @brief Collection of IPv6 subnets within shared network.
    Subnet6Collection subnets_;
};

/// @brief Pointer to @ref SharedNetwork6 object.
typedef boost::shared_ptr<SharedNetwork6> SharedNetwork6Ptr;

/// @brief Multi index container holding shared networks.
///
/// This is multi index container can hold pointers to @ref SharedNetwork6
/// objects. It provides indexes for shared network lookups using properties
/// such as shared network's name.
typedef boost::multi_index_container<
    // Multi index container holds pointers to the shared networks.
    SharedNetwork6Ptr,
    boost::multi_index::indexed_by<
        // First is the random access index allowing for accessing objects
        // just like we'd do with vector.
        boost::multi_index::random_access<
            boost::multi_index::tag<SharedNetworkRandomAccessIndexTag>
        >,
        // Second index allows for access by shared network's name.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SharedNetworkNameIndexTag>,
            boost::multi_index::const_mem_fun<SharedNetwork6, std::string,
                                              &SharedNetwork6::getName>
        >,
        // Third index allows for searching using subnet modification time.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SharedNetworkModificationTimeIndexTag>,
            boost::multi_index::const_mem_fun<data::StampedElement,
                                              boost::posix_time::ptime,
                                              &data::StampedElement::getModificationTime>
        >
    >
> SharedNetwork6Collection;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORK_H
