// Copyright (C) 2013,2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

/// @file subnet_select_co.cc Defines the subnet4_select and subnet6_select callout functions.

#include <config.h>
#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/subnet.h>
#include <user_chk.h>
#include <user_chk_log.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace user_chk;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "subnet4_select" hook.
///
/// This function alters the selected subnet based upon whether or not the
/// requesting DHCP client is a "registered user".  It fetches a pointer to
/// the registered user from the callout context.  This value is presumed to
/// have been set upstream.  If it is non-null that it points to the client's
/// user entry in the UserRegistry.  If it is null, the client is not
/// registered.
///
/// If the client is registered, then replace the selected subnet with the
/// restricted access subnet. By convention, it is assumed that last subnet in
/// the list of available subnets is the restricted access subnet.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int subnet4_select(CalloutHandle& handle) {
    if (!user_registry) {
        LOG_ERROR(user_chk_logger, USER_CHK_SUBNET4_SELECT_REGISTRY_NULL);
        return (1);
    }

    try {
        // Get subnet collection. If it's empty just bail nothing to do.
        const isc::dhcp::Subnet4Collection *subnets = NULL;
        handle.getArgument("subnet4collection", subnets);
        if (subnets->empty()) {
            return (0);
        }

        // Get registered_user pointer.
        UserPtr registered_user;
        handle.getContext(registered_user_label, registered_user);

        if (registered_user) {
            // User is in the registry, so leave the pre-selected subnet alone.
            Subnet4Ptr subnet;
            handle.getArgument("subnet4", subnet);
        } else {
            // User is not in the registry, so assign them to the last subnet
            // in the collection.  By convention we are assuming this is the
            // restricted subnet.
            Subnet4Ptr subnet = subnets->back();
            handle.setArgument("subnet4", subnet);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(user_chk_logger, USER_CHK_SUBNET4_SELECT_ERROR)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief  This callout is called at the "subnet6_select" hook.
///
/// This function alters the selected subnet based upon whether or not the
/// requesting DHCP client is a "registered user".  It fetches a pointer to
/// the registered user from the callout context.  This value is presumed to
/// have been set upstream.  If it is non-null that it points to the client's
/// user entry in the UserRegistry.  If it is null, the client is not
/// registered.
///
/// If the client is registered, then replace the selected subnet with the
/// restricted access subnet. By convention, it is assumed that last subnet in
/// the list of available subnets is the restricted access subnet.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int subnet6_select(CalloutHandle& handle) {
    if (!user_registry) {
        LOG_ERROR(user_chk_logger, USER_CHK_SUBNET6_SELECT_REGISTRY_NULL);
        return (1);
    }

    try {
        // Get subnet collection. If it's empty just bail nothing to do.
        const isc::dhcp::Subnet6Collection *subnets = NULL;
        handle.getArgument("subnet6collection", subnets);
        if (subnets->empty()) {
            return (0);
        }

        // Get registered_user pointer.
        UserPtr registered_user;
        handle.getContext(registered_user_label, registered_user);

        if (registered_user) {
            // User is in the registry, so leave the pre-selected subnet alone.
            Subnet6Ptr subnet;
            handle.getArgument("subnet6", subnet);
        } else {
            // User is not in the registry, so assign them to the last subnet
            // in the collection.  By convention we are assuming this is the
            // restricted subnet.
            Subnet6Ptr subnet = subnets->back();
            handle.setArgument("subnet6", subnet);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(user_chk_logger, USER_CHK_SUBNET6_SELECT_ERROR)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

}
