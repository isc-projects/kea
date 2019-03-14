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

        networks_.push_back(network);
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

protected:

    /// @brief Multi index container holding shared networks.
    SharedNetworkCollection networks_;
};

/// @brief Represents configuration of IPv4 shared networks.
class CfgSharedNetworks4 : public CfgSharedNetworks<SharedNetwork4Ptr,
                                                    SharedNetwork4Collection> {
public:

    /// @brief Returns pointer to all configured shared networks.
    const SharedNetwork4Collection* getAll() const {
        return (&networks_);
    }

    /// @brief Checks if specified server identifier has been specified for
    /// any network.
    ///
    /// @param server_id Server identifier.
    ///
    /// @return true if there is a network with a specified server identifier.
    bool hasNetworkWithServerId(const asiolink::IOAddress& server_id) const;

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
    void merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks4& other);
};

/// @brief Pointer to the configuration of IPv4 shared networks.
typedef boost::shared_ptr<CfgSharedNetworks4> CfgSharedNetworks4Ptr;

/// @brief Represents configuration of IPv6 shared networks.
class CfgSharedNetworks6 : public CfgSharedNetworks<SharedNetwork6Ptr,
                                                    SharedNetwork6Collection> {
public:

    /// @brief Returns pointer to all configured shared networks.
    const SharedNetwork6Collection* getAll() const {
        return (&networks_);
    }
};

/// @brief Pointer to the configuration of IPv6 shared networks.
typedef boost::shared_ptr<CfgSharedNetworks6> CfgSharedNetworks6Ptr;


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CFG_SHARED_NETWORKS_H
