// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CTL_DHCP_H
#define CB_CTL_DHCP_H

#include <cc/stamped_value.h>
#include <process/cb_ctl_base.h>
#include <dhcpsrv/srv_config.h>

namespace isc {
namespace dhcp {

/// @brief Base class for implementing mechanisms to control the use
/// of the Configuration Backends by DHCPv4 and DHCPv6 servers.
///
/// It includes common methods used by the DHCPv4 and DHCPv6 specific
/// derivations.
///
/// @tparam ConfigBackendMgrType Type of the Config Backend Manager used
/// by the server implementing this class. For example, for the DHCPv4
/// server it will be @c ConfigBackendDHCPv4Mgr.
template<typename ConfigBackendMgrType>
class CBControlDHCP : public process::CBControlBase<ConfigBackendMgrType> {
public:

    /// @brief Constructor.
    CBControlDHCP()
        : process::CBControlBase<ConfigBackendMgrType>() {
    }

protected:

    /// @brief Adds globals fetched from config backend(s) to a SrvConfig instance
    ///
    /// Iterates over the given collection of global parameters and adds them to the
    /// given configuration's list of configured globals.
    ///
    /// @param external_cfg SrvConfig instance to update
    /// @param cb_globals collection of global parameters supplied by configuration
    /// backend
    void addGlobalsToConfig(SrvConfigPtr external_cfg,
                            data::StampedValueCollection& cb_globals) const {
        const auto& index = cb_globals.get<data::StampedValueNameIndexTag>();
        for (auto cb_global = index.begin(); cb_global != index.end(); ++cb_global) {

            if ((*cb_global)->amNull()) {
                continue;
            }

            external_cfg->addConfiguredGlobal((*cb_global)->getName(), 
                                              (*cb_global)->getElementValue());
        }
    }
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CB_CTL_DHCP_H
