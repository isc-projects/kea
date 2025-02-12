// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/srv_config.h>
#include <hooks/callout_handle.h>
#include <limits/limit_manager.h>
#include <util/dhcp_space.h>

using namespace isc::dhcp;
using namespace isc::hooks;

using isc::hooks::CalloutHandle;
using isc::util::DHCPv4;

namespace isc {
namespace limits {

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces
extern "C" {

/// @brief Callout at the cb4_updated hook point
///
/// @param handle CalloutHandle which provides access to context
///
/// @return 0 upon success
int
cb4_updated(CalloutHandle& handle) {
    return (LimitManager::instance().cb_updated<DHCPv4>(handle));
}

/// @brief dhcp4_srv_configured callout implementation
///
/// @param handle CalloutHandle
///
/// @return 0 on success, non-zero otherwise.
int
dhcp4_srv_configured(CalloutHandle& handle) {
    return (LimitManager::instance().dhcp_srv_configured<DHCPv4>(handle));
}

/// @brief Callout at the pkt4_receive hook point
///
/// @param handle CalloutHandle which provides access to context
///
/// @return 0 upon success, non-zero otherwise.
int
pkt4_receive(CalloutHandle& handle) {
    return (LimitManager::instance().pkt_receive<DHCPv4>(handle));
}

/// @brief Callout at the subnet4_select hook point
///
/// @param handle CalloutHandle which provides access to context
///
/// @return 0 upon success, non-zero otherwise.
int
subnet4_select(CalloutHandle& handle) {
    return (LimitManager::instance().subnet_select<DHCPv4>(handle));
}

/// @brief Callout at the leases4_select hook point
///
/// @param handle CalloutHandle which provides access to context
///
/// @return 0 upon success, non-zero otherwise.
int
lease4_select(CalloutHandle& handle) {
    return (LimitManager::instance().lease_callout<DHCPv4>(handle));
}

/// @brief Callout at the leases4_renew hook point
///
/// @param handle CalloutHandle which provides access to context
///
/// @return 0 upon success, non-zero otherwise.
int
lease4_renew(CalloutHandle& handle) {
    return (LimitManager::instance().lease_callout<DHCPv4>(handle, /* lease_update = */ true));
}

}  // extern "C"

}  // namespace limits
}  // namespace isc
