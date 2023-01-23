// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/shared_network.h>
#include <boost/make_shared.hpp>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Implements common functionality for SharedNetwork4 and
/// SharedNetwork6 classes.
///
/// It provides mechanisms to add, remove and find subnets within shared
/// networks. It also provides means to walk over the subnets within a
/// shared network.
class Impl {
public:

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
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    ///
    /// @throw isc::BadValue if subnet is null.
    /// @throw isc::DuplicateSubnetID if a subnet with the given subnet id
    /// already exists in this shared network.
    /// @throw InvalidOperation if a subnet is already associated with some
    /// shared network.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static void add(SubnetCollectionType& subnets, const SubnetPtrType& subnet) {
        //  Subnet must be non-null.
        if (!subnet) {
            isc_throw(BadValue, "null pointer specified when adding a subnet"
                      " to a shared network");
        }

        // Check if a subnet with this id already exists.
        if (getSubnet<SubnetPtrType>(subnets, subnet->getID())) {
            isc_throw(DuplicateSubnetID, "attempted to add subnet with a"
                      " duplicated subnet identifier " << subnet->getID());
        } else if (getSubnet<SubnetPtrType>(subnets, subnet->toText())) {
            isc_throw(DuplicateSubnetID, "attempted to add subnet with a"
                      " duplicated subnet prefix " << subnet->toText());
        }

        // Check if the subnet is already associated with some network.
        NetworkPtr network;
        subnet->getSharedNetwork(network);
        if (network) {
            isc_throw(InvalidOperation, "subnet " << subnet->getID()
                      << " being added to a shared network"
                      " already belongs to a shared network");
        }

        // Add a subnet to the collection of subnets for this shared network.
        static_cast<void>(subnets.insert(subnet));
    }

    /// @brief Replaces IPv4 subnet in a shared network.
    ///
    /// This generic method replaces a subnet by another subnet
    /// with the same ID in a shared network.
    /// The prefix should be the same too.
    ///
    /// @tparam SubnetPtrType Type of a pointer to a subnet, i.e. Subnet4Ptr
    /// or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    ///
    /// @param [out] subnets Container holding subnets for this shared network.
    /// @param subnet Pointer to a subnet replacing the subnet with the same ID
    /// in this shared network.
    ///
    /// @throw isc::BadValue if subnet is null.
    /// @throw InvalidOperation if a subnet is already associated with some
    /// shared network.
    ////
    /// @return true if the operation succeeded, false otherwise.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static bool replace(SubnetCollectionType& subnets,
                        const SubnetPtrType& subnet) {

        // Check if the new subnet is already associated with some network.
        NetworkPtr network;
        subnet->getSharedNetwork(network);
        if (network) {
            isc_throw(InvalidOperation, "subnet " << subnet->getID()
                      << " being replaced in a shared network"
                      " already belongs to a shared network");
        }

        // Get the subnet with the same ID.
        const SubnetID& subnet_id = subnet->getID();
        auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_it = index.find(subnet_id);
        if (subnet_it == index.end()) {
            // Nothing to replace: return false to get the whole operation
            // to be rollbacked.
            return (false);
        }

        // Replace it.
        return (index.replace(subnet_it, subnet));
    }

    /// @brief Removes a subnet from the shared network.
    ///
    /// @param [out] subnets Container holding subnets for this shared network.
    /// @param subnet_id Identifier of a subnet to be removed.
    ///
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    ///
    /// @return Erased subnet.
    /// @throw BadValue if a subnet with specified identifier doesn't exist.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static SubnetPtrType del(SubnetCollectionType& subnets,
                             const SubnetID& subnet_id) {
        auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_it = index.find(subnet_id);
        if (subnet_it == index.end()) {
            isc_throw(BadValue, "unable to delete subnet " << subnet_id
                      << " from shared network. Subnet doesn't belong"
                      " to this shared network");
        }
        auto subnet = *subnet_it;
        index.erase(subnet_it);
        return (subnet);
    }

    /// @brief Returns a subnet belonging to this network for a given subnet id.
    ///
    /// @param subnets Container holding subnets for this shared network.
    /// @param subnet_id Identifier of a subnet being retrieved.
    ///
    /// @tparam SubnetPtrType Type of a pointer to a subnet, i.e. Subnet4Ptr
    /// or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    ///
    /// @return Pointer to the subnet or null if the subnet doesn't exist.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static SubnetPtrType getSubnet(const SubnetCollectionType& subnets,
                                   const SubnetID& subnet_id) {
        const auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_it = index.find(subnet_id);
        if (subnet_it != index.cend()) {
            return (*subnet_it);
        }

        // Subnet not found.
        return (SubnetPtrType());
    }

    /// @brief Returns a subnet belonging to this network for a given subnet
    /// prefix.
    ///
    /// @param subnets Container holding subnets for this shared network.
    /// @param subnet_prefix Prefix of a subnet being retrieved.
    ///
    /// @tparam SubnetPtrType Type of a pointer to a subnet, i.e. Subnet4Ptr
    /// or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of a container holding subnets, i.e.
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    ///
    /// @return Pointer to the subnet or null if the subnet doesn't exist.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static SubnetPtrType getSubnet(const SubnetCollectionType& subnets,
                                   const std::string& subnet_prefix) {
        const auto& index = subnets.template get<SubnetPrefixIndexTag>();
        auto subnet_it = index.find(subnet_prefix);
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
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    ///
    /// @return Pointer to next subnet or null pointer if no more subnets found.
    ///
    /// @throw isc::BadValue if invalid arguments specified, e.g. unable to
    /// find first or current subnet within the container.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static SubnetPtrType getNextSubnet(const SubnetCollectionType& subnets,
                                       const SubnetPtrType& first_subnet,
                                       const SubnetID& current_subnet) {
        // It is ok to have a shared network without any subnets, but in this
        // case there is nothing else we can return but null pointer.
        if (subnets.empty()) {
            return (SubnetPtrType());
        }

        // Need to retrieve an iterator to the current subnet first. The
        // subnet must exist in this container, thus we throw if the iterator
        // is not found.
        const auto& index = subnets.template get<SubnetSubnetIdIndexTag>();
        auto subnet_it = index.find(current_subnet);
        if (subnet_it == index.cend()) {
            isc_throw(BadValue, "no such subnet " << current_subnet
                      << " within shared network");
        }

        // Step to a next subnet.
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
    /// The preferred subnet must also fulfil the condition of equal client class
    /// with the @c selected_subnet.
    ///
    /// @tparam SubnetPtrType Type of the pointer to a subnet, i.e.
    /// @ref Subnet4Ptr or @ref Subnet6Ptr.
    /// @tparam SubnetCollectionType Type of the container holding subnets, i.e.
    /// @ref Subnet4SimpleCollection or @ref Subnet6SimpleCollection.
    /// @param subnets Container holding subnets belonging to this shared
    /// network.
    /// @param selected_subnet Pointer to a currently selected subnet.
    /// @param lease_type Type of the lease for which preferred subnet should be
    /// returned.
    ///
    /// @return Pointer to a preferred subnet. It may be the same as @c selected_subnet
    /// if no better subnet was found.
    template<typename SubnetPtrType, typename SubnetCollectionType>
    static SubnetPtrType getPreferredSubnet(const SubnetCollectionType& subnets,
                                            const SubnetPtrType& selected_subnet,
                                            const Lease::Type& lease_type) {

        auto preferred_subnet = selected_subnet;
        for (auto s = subnets.begin(); s != subnets.end(); ++s) {
            // It doesn't make sense to check the subnet against itself.
            if (preferred_subnet == (*s)) {
                continue;
            }
            if ((*s)->getClientClass().get() != selected_subnet->getClientClass().get()) {
                continue;
            }
            auto current_subnet_state = (*s)->getAllocationState(lease_type);
            if (!current_subnet_state) {
                continue;
            }
            auto preferred_subnet_state = preferred_subnet->getAllocationState(lease_type);
            if (!preferred_subnet_state) {
                continue;
            }
            // The currently checked subnet has more recent time than the
            // currently preferred subnet. Update the preferred subnet
            // instance.
            if (current_subnet_state->getLastAllocatedTime() >
                preferred_subnet_state->getLastAllocatedTime()) {
                preferred_subnet = (*s);
            }
        }
        return (preferred_subnet);
    }
};

} // end of anonymous namespace

namespace isc {
namespace dhcp {

SharedNetwork4Ptr
SharedNetwork4::create(const std::string& name) {
    return (boost::make_shared<SharedNetwork4>(name));
}

void
SharedNetwork4::add(const Subnet4Ptr& subnet) {
    Impl::add(subnets_, subnet);
    // Associate the subnet with this network.
    subnet->setSharedNetwork(shared_from_this());
    subnet->setSharedNetworkName(name_);
}

bool
SharedNetwork4::replace(const Subnet4Ptr& subnet) {
    // Subnet must be non-null.
    if (!subnet) {
        isc_throw(BadValue, "null pointer specified when adding a subnet"
                  " to a shared network");
    }
    const Subnet4Ptr& old = getSubnet(subnet->getID());
    bool ret = Impl::replace(subnets_, subnet);
    if (ret) {
        // Associate the subnet with this network.
        subnet->setSharedNetwork(shared_from_this());
        subnet->setSharedNetworkName(name_);
        // Deassociate the previous subnet.
        old->setSharedNetwork(NetworkPtr());
        old->setSharedNetworkName("");
    }
    return (ret);
}

void
SharedNetwork4::del(const SubnetID& subnet_id) {
    Subnet4Ptr subnet = Impl::del<Subnet4Ptr>(subnets_, subnet_id);
    subnet->setSharedNetwork(NetworkPtr());
    subnet->setSharedNetworkName("");
}

void
SharedNetwork4::delAll() {
    for (auto subnet = subnets_.cbegin(); subnet != subnets_.cend(); ++subnet) {
        (*subnet)->setSharedNetwork(NetworkPtr());
        (*subnet)->setSharedNetworkName("");
    }
    subnets_.clear();
}

Subnet4Ptr
SharedNetwork4::getSubnet(const SubnetID& subnet_id) const {
    return (Impl::getSubnet<Subnet4Ptr>(subnets_, subnet_id));
}

Subnet4Ptr
SharedNetwork4::getSubnet(const std::string& subnet_prefix) const {
    return (Impl::getSubnet<Subnet4Ptr>(subnets_, subnet_prefix));
}

Subnet4Ptr
SharedNetwork4::getNextSubnet(const Subnet4Ptr& first_subnet,
                              const SubnetID& current_subnet) const {
    return (Impl::getNextSubnet(subnets_, first_subnet, current_subnet));
}

Subnet4Ptr
SharedNetwork4::getPreferredSubnet(const Subnet4Ptr& selected_subnet) const {
    return (Impl::getPreferredSubnet<Subnet4Ptr>(subnets_, selected_subnet,
                                                 Lease::TYPE_V4));
}

bool
SharedNetwork4::subnetsIncludeMatchClientId(const Subnet4Ptr& first_subnet,
                                            const ClientClasses& client_classes) {
    for (Subnet4Ptr subnet = first_subnet; subnet;
         subnet = subnet->getNextSubnet(first_subnet, client_classes)) {
        if (subnet->getMatchClientId()) {
            return (true);
        }
    }
    return (false);
}

ElementPtr
SharedNetwork4::toElement() const {
    ElementPtr map = Network4::toElement();

    // Set shared network name.
    if (!name_.empty()) {
        map->set("name", Element::create(name_));
    }

    ElementPtr subnet4 = Element::createList();
    for (auto subnet = subnets_.cbegin(); subnet != subnets_.cend(); ++subnet) {
        subnet4->add((*subnet)->toElement());
    }

    map->set("subnet4", subnet4);

    return (map);
}

SharedNetwork6Ptr
SharedNetwork6::create(const std::string& name) {
    return (boost::make_shared<SharedNetwork6>(name));
}

void
SharedNetwork6::add(const Subnet6Ptr& subnet) {
    Impl::add(subnets_, subnet);
    // Associate the subnet with this network.
    subnet->setSharedNetwork(shared_from_this());
    subnet->setSharedNetworkName(name_);
}

bool
SharedNetwork6::replace(const Subnet6Ptr& subnet) {
    // Subnet must be non-null.
    if (!subnet) {
        isc_throw(BadValue, "null pointer specified when adding a subnet"
                  " to a shared network");
    }
    const Subnet6Ptr& old = getSubnet(subnet->getID());
    bool ret = Impl::replace(subnets_, subnet);
    if (ret) {
        // Associate the subnet with this network.
        subnet->setSharedNetwork(shared_from_this());
        subnet->setSharedNetworkName(name_);
        // Deassociate the previous subnet.
        old->setSharedNetwork(NetworkPtr());
        old->setSharedNetworkName("");
    }
    return (ret);
}

void
SharedNetwork6::del(const SubnetID& subnet_id) {
    Subnet6Ptr subnet = Impl::del<Subnet6Ptr>(subnets_, subnet_id);
    subnet->setSharedNetwork(NetworkPtr());
    subnet->setSharedNetworkName("");
}

void
SharedNetwork6::delAll() {
    for (auto subnet = subnets_.cbegin(); subnet != subnets_.cend(); ++subnet) {
        (*subnet)->setSharedNetwork(NetworkPtr());
    }
    subnets_.clear();
}

Subnet6Ptr
SharedNetwork6::getSubnet(const SubnetID& subnet_id) const {
    return (Impl::getSubnet<Subnet6Ptr>(subnets_, subnet_id));
}

Subnet6Ptr
SharedNetwork6::getSubnet(const std::string& subnet_prefix) const {
    return (Impl::getSubnet<Subnet6Ptr>(subnets_, subnet_prefix));
}

Subnet6Ptr
SharedNetwork6::getNextSubnet(const Subnet6Ptr& first_subnet,
                              const SubnetID& current_subnet) const {
    return (Impl::getNextSubnet(subnets_, first_subnet, current_subnet));
}

Subnet6Ptr
SharedNetwork6::getPreferredSubnet(const Subnet6Ptr& selected_subnet,
                                   const Lease::Type& lease_type) const {
    return (Impl::getPreferredSubnet(subnets_, selected_subnet, lease_type));
}

ElementPtr
SharedNetwork6::toElement() const {
    ElementPtr map = Network6::toElement();

    // Set shared network name.
    if (!name_.empty()) {
        map->set("name", Element::create(name_));
    }

    ElementPtr subnet6 = Element::createList();
    for (auto subnet = subnets_.cbegin(); subnet != subnets_.cend(); ++subnet) {
        subnet6->add((*subnet)->toElement());
    }

    map->set("subnet6", subnet6);

    return (map);
}

} // end of namespace isc::dhcp
} // end of namespace isc
