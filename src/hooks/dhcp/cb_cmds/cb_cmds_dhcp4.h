// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CMDS_DHCP4_IMPL_H
#define CB_CMDS_DHCP4_IMPL_H

#include <cb_cmds/cb_cmds_impl.h>

namespace isc {
namespace cb {

/// @brief Implementation of the callouts for cb_cmds library for DHCPv4.
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
class ConfigCmdsDhcp4Impl : public ConfigCmdsImpl {
public:

    /// @brief Implements handler for remote-global-parameter4-set
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setGlobalParameter4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-global-parameter4-del
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delGlobalParameter4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-global-parameter4-get
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getGlobalParameter4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-global-parameter4-get-all
    /// command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllGlobalParameters4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet4-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSubnet4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet4-del-by-id command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSubnet4Id(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet4-del-by-prefix command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSubnet4Prefix(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet4-get-by-id command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getSubnet4Id(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet4-get-by-prefix command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getSubnet4Prefix(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-subnet4-list command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void listSubnets4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network4-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSharedNetwork4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network4-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSharedNetwork4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network4-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getSharedNetwork4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-shared-network4-list command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void listSharedNetworks4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class4-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setClientClass4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class4-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delClientClass4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class4-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getClientClass4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-class4-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllClientClasses4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def4-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setOptionDef4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def4-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delOptionDef4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def4-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getOptionDef4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option-def4-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllOptionDefs4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-global-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setGlobalOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-global-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delGlobalOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-global-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getGlobalOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-global-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllGlobalOptions4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server4-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setServer4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server4-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delServer4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server4-get command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getServer4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-server4-get-all command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void getAllServers4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-network-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSharedNetworkOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-network-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSharedNetworkOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-subnet-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setSubnetOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-subnet-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delSubnetOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-pool-set command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void setPoolOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for remote-option4-pool-del command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void delPoolOption4(hooks::CalloutHandle& callout_handle);

    /// @brief Supported global maps parameters (scalars only).
    static const data::SimpleKeywords GLOBAL4_MAP_PARAMETERS;

private:
    /// @brief Initialization function which properly sets the list of
    /// supported global containers parameters.
    static data::SimpleKeywords initGlobalContainersParameters();

    /// @brief Returns the list of supported global containers parameters.
    static data::SimpleKeywords& getGlobalContainersParameters();
};

/// @brief Pointer to the @c ConfigCmdsDhcp4Impl.
typedef boost::shared_ptr<ConfigCmdsDhcp4Impl> ConfigCmdsDhcp4ImplPtr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // CB_CMDS_DHCP4_IMPL_H
