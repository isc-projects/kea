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

    /// @brief It translates the top level map parameters from flat naming
    /// format (e.g. map-name/element-name) to proper ElementMap objects and
    /// adds all globals fetched from config backend(s) to a SrvConfig instance
    ///
    /// Iterates over the given collection of global parameters and adds them to
    /// the given configuration's list of configured globals.
    ///
    ///
    /// @param external_cfg SrvConfig instance to update
    /// @param cb_globals collection of global parameters supplied by configuration
    /// backend
    void translateAndAddGlobalsToConfig(SrvConfigPtr external_cfg,
                                        data::StampedValueCollection& cb_globals) const {
        auto const& index = cb_globals.get<data::StampedValueNameIndexTag>();
        for (auto const& cb_global : index) {

            if (cb_global->amNull()) {
                continue;
            }

            std::string name = cb_global->getName();
            auto pos = name.find('/');
            if (pos != std::string::npos) {
                const std::string sub_elem(name.substr(pos + 1));
                name = name.substr(0, pos);
                data::ElementPtr sub_param = boost::const_pointer_cast<data::Element>(external_cfg->getConfiguredGlobal(name));
                if (!sub_param) {
                    sub_param = data::Element::createMap();
                }
                sub_param->set(sub_elem, cb_global->getElementValue());
                external_cfg->addConfiguredGlobal(name, sub_param);
            } else {
                // Reuse name and value.
                external_cfg->addConfiguredGlobal(name, cb_global->getElementValue());
            }
        }
    }
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CB_CTL_DHCP_H
