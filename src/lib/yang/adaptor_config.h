// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_CONFIG_H
#define ISC_ADAPTOR_CONFIG_H 1

#include <yang/adaptor_host.h>
#include <yang/adaptor_option.h>
#include <yang/adaptor_pool.h>
#include <yang/adaptor_subnet.h>
#include <list>

namespace isc {
namespace yang {

/// @brief JSON adaptor for configurations.
class AdaptorConfig : public AdaptorHost, public AdaptorOption,
    public AdaptorSubnet {
public:

    /// @brief Constructor.
    AdaptorConfig();

    /// @brief Destructor.
    virtual ~AdaptorConfig();

    /// @brief Pre process a DHCPv4 configuration.
    ///
    /// Assign subnet IDs, check and set default in options.
    ///
    /// @param config The configuration.
    /// @throw MissingKey when a required key is missing.
    static void preProcess4(isc::data::ConstElementPtr config);

    /// @brief Pre process a DHCPv6 configuration.
    ///
    /// Assign subnet IDs, check and set default in options.
    ///
    /// @param config The configuration.
    /// @throw MissingKey when a required key is missing.
    static void preProcess6(isc::data::ConstElementPtr config);

protected:
    /// @brief collectID for a subnet list.
    ///
    /// @param subnets The subnet list.
    /// @param set The reference to the set of assigned IDs.
    /// @return True if all subnets have an ID, false otherwise.
    static bool subnetsCollectID(isc::data::ConstElementPtr subnets,
                                 SubnetIDSet& set);

    /// @brief collectID for a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param set The reference to the set of assigned IDs.
    /// @param subsel The subnet list name.
    /// @return True if all subnets have an ID, false otherwise.
    static bool shareNetworksCollectID(isc::data::ConstElementPtr networks,
                                       SubnetIDSet& set,
                                       const std::string& subsel);

    /// @brief assignID for a subnet list.
    ///
    /// @param subnets The subnet list.
    /// @param set The reference to the set of assigned IDs.
    /// @param next The next ID.
    /// @return True if all subnets have an ID, false otherwise.
    static void subnetsAssignID(isc::data::ConstElementPtr subnets,
                                SubnetIDSet& set, isc::dhcp::SubnetID& next);

    /// @brief assignID for a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param set The reference to the set of assigned IDs.
    /// @param next The next ID.
    /// @param subsel The subnet list name.
    /// @return True if all subnets have an ID, false otherwise.
    static void shareNetworksAssignID(isc::data::ConstElementPtr networks,
                                      SubnetIDSet& set,
                                      isc::dhcp::SubnetID& next,
                                      const std::string& subsel);

    /// @brief canonizePool for a pool list.
    ///
    /// @param pools The pool list.
    static void canonizePools(isc::data::ConstElementPtr pools);

    /// @brief canonizePool for a subnet list.
    ///
    /// @param subnets The subnet list.
    static void poolSubnets(isc::data::ConstElementPtr subnets);

    /// @brief canonizePool for a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param subsel The subnet list name.
    static void poolShareNetworks(isc::data::ConstElementPtr networks,
                                  const std::string& subsel);

    /// @brief Process an option definition list.
    ///
    /// @param defs The option definition list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionDefList(isc::data::ConstElementPtr defs,
                              const std::string& space,
                              OptionCodes& codes);

    /// @brief Process an option data list.
    ///
    /// @param options The option data list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionDataList(isc::data::ConstElementPtr options,
                               const std::string& space,
                               const OptionCodes& codes);

    /// @brief Process options in a client class list.
    ///
    /// @param classes The client class list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionClasses(isc::data::ConstElementPtr classes,
                              const std::string& space,
                              OptionCodes& codes);

    /// @brief Process options in a pool list.
    ///
    /// @param pools The pool list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionPools(isc::data::ConstElementPtr pools,
                            const std::string& space,
                            const OptionCodes& codes);

    /// @brief Process options in a host reservation list.
    ///
    /// @param hosts The host reservation list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionHosts(isc::data::ConstElementPtr hosts,
                            const std::string& space,
                            const OptionCodes& codes);

    /// @brief Process options in a subnet list.
    ///
    /// @param subnets The subnet list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionSubnets(isc::data::ConstElementPtr subnets,
                              const std::string& space,
                              const OptionCodes& codes);

    /// @brief Process options in a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param space The default space name.
    /// @param codes Option definitions.
    static void optionSharedNetworks(isc::data::ConstElementPtr networks,
                                     const std::string& space,
                                     const OptionCodes& codes);

    /// @brief Process host reservation list.
    ///
    /// @param hosts The host reservation list.
    static void hostList(isc::data::ConstElementPtr hosts);

    /// @brief Process host reservations in a subnet list.
    ///
    /// @param subnets The subnet list.
    static void hostSubnets(isc::data::ConstElementPtr subnets);

    /// @brief Process host reservations in a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param space The default space name.
    static void hostSharedNetworks(isc::data::ConstElementPtr networks,
                                   const std::string& space);

    /// @brief updateRelay in a subnet list.
    ///
    /// @param subnets The subnet list.
    static void relaySubnets(isc::data::ConstElementPtr subnets);

    /// @brief updateRelay in a shared network list.
    ///
    /// @param networks The shared network list.
    /// @param subsel The subnet list name.
    static void relaySharedNetworks(isc::data::ConstElementPtr networks,
                                    const std::string& subsel);

    /// @brief Update (hosts) database.
    ///
    /// Force the use of hosts-databases vs. hosts-database.
    ///
    /// @param dhcp The DHCP server.
    static void updateDatabase(isc::data::ConstElementPtr dhcp);

    /// @brief Pre process a configuration.
    ///
    /// Assign subnet IDs, check and set default in options.
    ///
    /// @param dhcp The server configuration.
    /// @param subsel The subnet list name.
    /// @param space The default option space name.
    /// @throw MissingKey when a required key is missing.
    static void preProcess(isc::data::ConstElementPtr dhcp,
                           const std::string& subsel,
                           const std::string& space);
};

}; // end of namespace isc::yang
}; // end of namespace isc

#endif // ISC_ADAPTOR_CONFIG_H
