// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_NETWORK_H
#define SHARED_NETWORK_H

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/assignable_network.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

class SharedNetwork;

/// @brief Pointer to the @ref SharedNetwork object.
typedef boost::shared_ptr<SharedNetwork> SharedNetworkPtr;

/// @brief Represents shared network, which groups multiple subnets.
///
/// Shared networks provide means for grouping multiple subnets together.
/// There are two major use cases for such grouping:
///
/// - Extending available address pools to be allocated for clients on
/// a particular link without a need to renumber.
/// - Fulfill requirement in cable networks whereby two classes of devices
/// are connected on the same link: cable modems and routers. Such devices
/// must be assign addresses/prefixes from different pools based on client
/// classification.
///
/// Shared networks provide similar interface like subnets, thus they both
/// derive from the @ref Network class.
class SharedNetwork : public AssignableNetwork {
protected:

    /// @brief Constructor.
    ///
    /// Sets name of the shared network.
    explicit SharedNetwork(const std::string& name)
        : name_(name) {
    }

public:

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

protected:

    /// @brief Adds a subnet to a shared network.
    ///
    /// This is a generic method for adding a new subnet to a shared network.
    ///
    /// @param [out] subnets Container holding subnets for this shared network.
    /// @param subnet Pointer to a subnet being added to this shared network.
    ///
    /// @tparam SubnetPtrType Type of a pointer to a subnet, i.e. Subnet4Ptr
    /// or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4Collection or @ref Subnet6Collection.
    ///
    /// @throw isc::BadValue if subnet is null.
    /// @throw isc::DuplicateSubnetID if a subnet with the given subnet id
    /// already exists in this shared network.
    /// @throw InvalidOperation if a subnet is already associated with some
    /// shared network.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    void add(SubnetCollectionType& subnets, const SubnetPtrType& subnet) {
        //  Subnet must be non-null.
        if (!subnet) {
            isc_throw(BadValue, "null pointer specified when adding a subnet"
                      " to a shared network");
        }

        // Check if a subnet with this id already exists.
        if (getSubnet<SubnetPtrType>(subnets, subnet->getID())) {
            isc_throw(DuplicateSubnetID, "attempted to add subnet with a"
                      " duplicated subnet identifier " << subnet->getID());
        }

        // Check if the subnet is already associated with some network.
        SharedNetworkPtr network;
        subnet->getSharedNetwork(network);
        if (network) {
            isc_throw(InvalidOperation, "subnet " << subnet->getID()
                      << " being added to a shared network"
                      " already belongs to a shared network");
        }

        // Add a subnet to the collection of subnets for this shared network.
        subnets.push_back(subnet);
        // Associate the subnet with this network.
        setSharedNetwork(subnet);
    }

    /// @brief Removes a subnet from the shared network.
    ///
    /// @param [out] subnets Container holding subnets for this shared network.
    /// @param subnet_id Identifier of a subnet to be removed.
    ///
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4Collection or @ref Subnet6Collection.
    ///
    /// @throw BadValue if a subnet with specified identifier doesn't exist.
    template<typename SubnetCollectionType>
    void del(SubnetCollectionType& subnets, const SubnetID& subnet_id) {
        auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_it = index.find(subnet_id);
        if (subnet_it == index.end()) {
            isc_throw(BadValue, "unable to delete subnet " << subnet_id
                      << " from shared network. Subnet doesn't belong"
                      " to this shared network");
        }
        auto subnet = *subnet_it;
        index.erase(subnet_it);
        clearSharedNetwork(subnet);
    }

    /// @brief Returns a subnet belonging to this network for a given subnet id.
    ///
    /// @param subnets Container holding subnets for this shared network.
    /// @param subnet_id Identifier of a subnet being retrieved.
    ///
    /// @tparam SubnetPtrType Type of a pointer to a subnet, i.e. Subnet4Ptr
    /// or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4Collection or @ref Subnet6Collection.
    ///
    /// @return Pointer to the subnet or null if the subnet doesn't exist.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    SubnetPtrType getSubnet(const SubnetCollectionType& subnets,
                            const SubnetID& subnet_id) const {
        const auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_it = index.find(subnet_id);
        if (subnet_it != index.cend()) {
            return (*subnet_it);
        }

        // Subnet not found.
        return (SubnetPtrType());
    }

    /// @brief Retrieves next available subnet within shared network.
    ///
    /// This method returns next available subnet within a shared network.
    /// The subnets are ordered and retrieved using random access index
    /// (first in/first out). The next subnet means next in turn after
    /// the current subnet, which is specified as an argument. A caller
    /// can iterate over all subnets starting from any of the subnets
    /// belonging to a shared network. This subnet is called here as
    /// a first subnet and is also specified as a method argument. When the
    /// method detects that the next available subnet is a first subnet, it
    /// returns a null pointer to indicate that there are no more subnets
    /// available.
    ///
    /// The typical use case for this method is to allow DHCP server's
    /// allocation engine to walk over the available subnets within a shared
    /// network, starting from a subnet that has been selected during the
    /// "subnet selection" processing step. In some cases the allocation
    /// engine is unable to allocate resources from a selected subnet due
    /// to client classification restrictions or address shortage within
    /// its pools. It then uses this mechanism to move to another subnet
    /// belonging to the same shared network.
    ///
    /// @param subnets Container holding subnets belonging to this shared
    /// network.
    /// @param first_subnet Pointer to a subnet from which the caller is
    /// iterating over subnets within shared network. This is typically a
    /// subnet selected during "subnet selection" step.
    /// @param current_subnet Pointer to a subnet for which next subnet is
    /// to be found.
    ///
    /// @tparam SubnetPtrType Type of the pointer to a subnet, i.e.
    /// @ref Subnet4Ptr or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of the container holding subnets, i.e.
    /// @ref Subnet4Collection or @ref Subnet6Collection.
    ///
    /// @return Pointer to next subnet or null pointer if no more subnets found.
    ///
    /// @throw isc::BadValue if invalid arguments specified, e.g. unable to
    /// find first or current subnet within the container.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    SubnetPtrType getNextSubnet(const SubnetCollectionType& subnets,
                                const SubnetPtrType& first_subnet,
                                const SubnetPtrType& current_subnet) const {
        // Current subnet must not be null. The caller must explicitly set it
        // to one of the pointers that belong to this shared network, typically
        // to a selected subnet.
        if (!current_subnet) {
            isc_throw(BadValue, "null subnet specified for a shared"
                      " network while searching for next subnet is this"
                      " network");
        }

        // It is ok to have a shared network without any subnets, but in this
        // case there is nothing else we can return but null pointer.
        if (subnets.empty()) {
            return (SubnetPtrType());
        }

        // Need to retrieve an iterator to the current subnet first. The
        // subnet must exist in this container, thus we throw if the iterator
        // is not found.
        const auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_id_it = index.find(current_subnet->getID());
        if (subnet_id_it == index.cend()) {
            isc_throw(BadValue, "no such subnet " << current_subnet->getID()
                      << " within shared network");
        }

        // We need to transform this iterator (by subnet id) to a random access
        // index iterator. Multi index container has a nice way of doing it.
        auto subnet_it = subnets.template project<SubnetRandomAccessIndexTag>(subnet_id_it);

        // Step to a next subnet within random access index.
        if (++subnet_it == subnets.cend()) {
            // If we reached the end of the container, start over from the
            // beginning.
            subnet_it = subnets.cbegin();
        }

        // Check if we have made a full circle. If we did, return a null pointer
        // to indicate that there are no more subnets.
        if ((*subnet_it)->getID() == first_subnet->getID()) {
            return (SubnetPtrType());
        }

        // Got the next subnet, so return it.
        return (*subnet_it);
    }

    /// @brief Unparses shared network object.
    ///
    /// @return A pointer to unparsed shared network configuration.
    virtual data::ElementPtr toElement() const;

    /// @brief Holds a name of a shared network.
    std::string name_;

};

/// @brief Shared network holding IPv4 subnets.
///
/// Specialization of the @ref SharedNetwork class for IPv4 subnets.
class SharedNetwork4 : public SharedNetwork,
                       public boost::enable_shared_from_this<SharedNetwork4> {
public:

    /// @brief Constructor.
    ///
    /// Sets name of the shared network.
    explicit SharedNetwork4(const std::string& name)
        : SharedNetwork(name) {
    }

    /// @brief Returns shared pointer to this network.
    ///
    /// This method is required by the parent @ref AssignableNetwork class.
    ///
    /// @return Shared pointer to this object.
    virtual NetworkPtr sharedFromThis();

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
    /// See documentation for @ref SharedNetwork::getNextSubnet.
    ///
    /// @param first_subnet Pointer to a subnet from which the caller is
    /// iterating over subnets within shared network. This is typically a
    /// subnet selected during "subnet selection" step.
    /// @param current_subnet Pointer to a subnet for which next subnet is
    /// to be found.
    ///
    /// @return Pointer to next subnet or null pointer if no more subnets found.
    ///
    /// @throw isc::BadValue if invalid arguments specified, e.g. unable to
    /// find first or current subnet within shared network.
    Subnet4Ptr getNextSubnet(const Subnet4Ptr& first_subnet,
                             const Subnet4Ptr& current_subnet) const;

    /// @brief Unparses shared network object.
    ///
    /// @return A pointer to unparsed shared network configuration.
    virtual data::ElementPtr toElement() const;

private:

    /// @brief Collection of IPv4 subnets within shared network.
    Subnet4Collection subnets_;

};

/// @brief Pointer to @ref SharedNetwork4 object.
typedef boost::shared_ptr<SharedNetwork4> SharedNetwork4Ptr;

/// @brief Shared network holding IPv6 subnets.
///
/// Specialization of the @ref SharedNetwork class for IPv6 subnets.
class SharedNetwork6 : public SharedNetwork,
                       public boost::enable_shared_from_this<SharedNetwork6> {
public:

    /// @brief Constructor.
    ///
    /// Sets name of the shared network.
    explicit SharedNetwork6(const std::string& name)
        : SharedNetwork(name) {
    }

    /// @brief Returns shared pointer to this network.
    ///
    /// This method is required by the parent @ref AssignableNetwork class.
    ///
    /// @return Shared pointer to this object.
    virtual NetworkPtr sharedFromThis();

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
    /// See documentation for @ref SharedNetwork::getNextSubnet.
    ///
    /// @param first_subnet Pointer to a subnet from which the caller is
    /// iterating over subnets within shared network. This is typically a
    /// subnet selected during "subnet selection" step.
    /// @param current_subnet Pointer to a subnet for which next subnet is
    /// to be found.
    ///
    /// @return Pointer to next subnet or null pointer if no more subnets found.
    ///
    /// @throw isc::BadValue if invalid arguments specified, e.g. unable to
    /// find first or current subnet within shared network.
    Subnet6Ptr getNextSubnet(const Subnet6Ptr& first_subnet,
                             const Subnet6Ptr& current_subnet) const;

    /// @brief Unparses shared network object.
    ///
    /// @return A pointer to unparsed shared network configuration.
    virtual data::ElementPtr toElement() const;

private:

    /// @brief Collection of IPv6 subnets within shared network.
    Subnet6Collection subnets_;
};

/// @brief Pointer to @ref SharedNetwork6 object.
typedef boost::shared_ptr<SharedNetwork6> SharedNetwork6Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORK_H
