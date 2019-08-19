// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_SHARED_NETWORKS_H
#define CFG_SHARED_NETWORKS_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/shared_network.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief This class holds configuration of shared networks.
///
/// This is a generic class implementing basic functions such as shared network
/// addition, removal and retrieval. It also dumps configuration in the JSON
/// format.
///
/// There are specializations of this class implemented as
/// @ref CfgSharedNetworks4 and @ref CfgSharedNetworks6 for IPv4 and IPv6 cases
/// repspectively.
///
/// @tparam Type of the pointer to a shared network, i.e. @ref SharedNetwork4Ptr
/// or @ref SharedNetwork6Ptr.
template<typename SharedNetworkPtrType, typename SharedNetworkCollection>
class CfgSharedNetworks : public data::CfgToElement {
public:
    /// @brief Returns pointer to all configured shared networks.
    const SharedNetworkCollection* getAll() const {
        return (&networks_);
    }

    /// @brief Adds new shared network to the configuration.
    ///
    /// @param network Pointer to a network
    ///
    /// @throw isc::BadValue when name is a duplicate of existing network's
    /// name.
    void add(const SharedNetworkPtrType& network) {
        if (getByName(network->getName())) {
            isc_throw(BadValue, "duplicate network '" << network->getName() <<
                      "' found in the configuration");
        }

        static_cast<void>(networks_.push_back(network));
    }

    /// @brief Deletes shared network from the configuration.
    ///
    /// @param name Name of the network to be deleted.
    ///
    /// @throw isc::BadValue if the network can't be found.
    void del(const std::string& name) {
        auto& index = networks_.template get<SharedNetworkNameIndexTag>();
        auto shared_network = index.find(name);
        if (shared_network != index.end()) {
            // Delete all subnets from the network
            (*shared_network)->delAll();

            // Then delete the network from the networks list.
            index.erase(shared_network);
        } else {
            isc_throw(BadValue, "unable to delete non-existing network '"
                      << name << "' from shared networks configuration");
        }
    }

    /// @brief Deletes shared networks from the configuration by id.
    ///
    /// Note that there are cases when there will be multiple shared
    /// networks having the same id (typically id of 0). When configuration
    /// backend is in use it sets the unique ids from the database.
    /// In cases when the configuration backend is not used, the ids
    /// default to 0. Passing the id of 0 would result in deleting all
    /// shared networks that were not added via the database.
    ///
    /// @param id Identifier of the shared networks to be deleted.
    ///
    /// @return Number of deleted shared networks.
    uint64_t del(const uint64_t id) {
        auto& index = networks_.template get<SharedNetworkIdIndexTag>();
        auto sn_range = index.equal_range(id);

        // For each shared network found, dereference the subnets belonging
        // to it.
        for (auto it = sn_range.first; it != sn_range.second; ++it) {
            (*it)->delAll();
        }

        // Remove the shared networks.
        return (static_cast<uint64_t>(index.erase(id)));
    }

    /// @brief Retrieves shared network by name.
    ///
    /// @param name Name of the network to be retrieved.
    ///
    /// @return Pointer to the shared network or null pointer if the network
    /// is not found.
    SharedNetworkPtrType getByName(const std::string& name) const {
        const auto& index = networks_.template get<SharedNetworkNameIndexTag>();
        auto shared_network = index.find(name);
        if (shared_network != index.cend()) {
            return (*shared_network);
        }
        return (SharedNetworkPtrType());
    }

    /// @brief Unparses shared networks configuration.
    ///
    /// @return Element object representing a list of shared networks held
    /// within configuration. The networks are sorted by their names.
    virtual data::ElementPtr toElement() const {
        data::ElementPtr list = data::Element::createList();

        // Insert shared networks sorted by their names into the list.
        const auto& index = networks_.template get<SharedNetworkNameIndexTag>();
        for (auto shared_network = index.begin(); shared_network != index.end();
             ++shared_network) {
            list->add((*shared_network)->toElement());
        }
        return (list);
    }

    /// @brief Merges specified shared network configuration into this
    /// configuration.
    ///
    /// This method merges networks from the @c other configuration into this
    /// configuration. The general rule is that existing networks are replaced
    /// by the networks from @c other.
    ///
    /// For each network in @c other, do the following:
    ///
    /// - Any associated subnets are removed.  Shared networks retrieved from
    /// config backends, do not carry their associated subnets (if any) with
    /// them. (Subnet assignments are maintained by subnet merges).
    /// - If a shared network of the same name already exists in this
    /// configuration:
    ///     - All of its associated subnets are moved to the "other" network.
    ///     - The existing network is removed from this configuration.
    /// - The "other" network's option instances are created.
    /// - The "other" network is added to this configuration.
    ///
    /// @warning The merge operation may affect the @c other configuration.
    /// Therefore, the caller must not rely on the data held in the @c other
    /// object after the call to @c merge. Also, the data held in @c other must
    /// not be modified after the call to @c merge because it may affect the
    /// merged configuration.
    ///
    /// @param cfg_def set of of user-defined option definitions to use
    /// when creating option instances.
    /// @param other the shared network configuration to be merged into this
    /// configuration.
    void merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks& other) {
        auto& index = networks_.template get<SharedNetworkNameIndexTag>();

        // Iterate over the subnets to be merged. They will replace the existing
        // subnets with the same id. All new subnets will be inserted into this
        // configuration.
        auto other_networks = other.getAll();
        for (auto other_network = other_networks->begin();
            other_network != other_networks->end(); ++other_network) {

            // In theory we should drop subnet assignments from "other". The
            // idea being  those that come from the CB should not have subnets_
            // populated.  We will quietly throw them away, just in case.
            (*other_network)->delAll();

            // Check if the other network exists in this config.
            auto existing_network = index.find((*other_network)->getName());
            if (existing_network != index.end()) {

                // Somehow the same instance is in both, skip it.
                if (*existing_network == *other_network) {
                    continue;
                }

                // Network exists, which means we're updating it.
                // First we need to move its subnets to the new
                // version of the network.
                const auto subnets = (*existing_network)->getAllSubnets();

                auto copy_subnets(*subnets);
                for (auto subnet = copy_subnets.cbegin(); subnet != copy_subnets.cend(); ++subnet) {
                    (*existing_network)->del((*subnet)->getID());
                    (*other_network)->add(*subnet);
                }

                // Now we discard the existing copy of the network.
                index.erase(existing_network);
            }

            // Create the network's options based on the given definitions.
            (*other_network)->getCfgOption()->createOptions(cfg_def);

            // Add the new/updated nework.
            static_cast<void>(networks_.push_back(*other_network));
        }
    }

protected:

    /// @brief Multi index container holding shared networks.
    SharedNetworkCollection networks_;
};

/// @brief Represents configuration of IPv4 shared networks.
class CfgSharedNetworks4 : public CfgSharedNetworks<SharedNetwork4Ptr,
                                                    SharedNetwork4Collection> {
public:
    /// @brief Checks if specified server identifier has been specified for
    /// any network.
    ///
    /// @param server_id Server identifier.
    ///
    /// @return true if there is a network with a specified server identifier.
    bool hasNetworkWithServerId(const asiolink::IOAddress& server_id) const;
};

/// @brief Pointer to the configuration of IPv4 shared networks.
typedef boost::shared_ptr<CfgSharedNetworks4> CfgSharedNetworks4Ptr;

/// @brief Represents configuration of IPv6 shared networks.
class CfgSharedNetworks6 : public CfgSharedNetworks<SharedNetwork6Ptr,
                                                    SharedNetwork6Collection> {
};

/// @brief Pointer to the configuration of IPv6 shared networks.
typedef boost::shared_ptr<CfgSharedNetworks6> CfgSharedNetworks6Ptr;


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CFG_SHARED_NETWORKS_H
