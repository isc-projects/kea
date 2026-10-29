// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CMDS_DHCP6_IMPL_H
#define CB_CMDS_DHCP6_IMPL_H

#include <cb_cmds/cb_cmds_impl.h>

namespace isc {
namespace cb {

/// @brief Implementation of the callouts for cb_cmds library for DHCPv6.
///
/// This class implements callouts supported by the cb_cmds hooks
/// library. Isolating callouts implementation in the class makes it
/// easier to unit test the callouts without necessity to load the
/// library.
///
/// Each callout implementation expects that the provided
/// @c callout_handle includes the command along with the arguments.
/// The command structure is extracted from the handle, processed and
/// the response is stored in the @c callout_handle.
class ConfigCmdsDhcp6Impl : public ConfigCmdsImpl {
public:

    /// @brief Implements handler for remote-global-parameter6-set
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setGlobalParameter6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-global-parameter6-del
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delGlobalParameter6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-global-parameter6-get
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getGlobalParameter6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-global-parameter6-get-all
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllGlobalParameters6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet6-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSubnet6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet6-del-by-id command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSubnet6Id(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet6-del-by-prefix command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSubnet6Prefix(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet6-get-by-id command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getSubnet6Id(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet6-get-by-prefix command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getSubnet6Prefix(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet6-list command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void listSubnets6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network6-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSharedNetwork6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network6-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSharedNetwork6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network6-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getSharedNetwork6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network6-list command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void listSharedNetworks6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class6-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setClientClass6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class6-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delClientClass6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class6-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getClientClass6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class6-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllClientClasses6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def6-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setOptionDef6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def6-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delOptionDef6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def6-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getOptionDef6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def6-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllOptionDefs6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-global-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setGlobalOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-global-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delGlobalOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-global-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getGlobalOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-global-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllGlobalOptions6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server6-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setServer6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server6-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delServer6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server6-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getServer6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server6-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllServers6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-network-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSharedNetworkOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-network-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSharedNetworkOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-subnet-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSubnetOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-subnet-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSubnetOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-pool-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setPoolOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-pool-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delPoolOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-pd-pool-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setPdPoolOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option6-pd-pool-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delPdPoolOption6(hooks::CalloutHandle& callout_handle);

    /// @brief Supported global maps parameters (scalars only).
    static const data::SimpleKeywords GLOBAL6_MAP_PARAMETERS;

private:
    /// @brief Initialization function which properly sets the list of
    /// supported global containers parameters.
    static data::SimpleKeywords initGlobalContainersParameters();

    /// @brief Returns the list of supported global containers parameters.
    static data::SimpleKeywords& getGlobalContainersParameters();
};

/// @brief Pointer to the @c ConfigCmdsDhcp6Impl.
typedef boost::shared_ptr<ConfigCmdsDhcp6Impl> ConfigCmdsDhcp6ImplPtr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // CB_CMDS_DHCP6_IMPL_H
