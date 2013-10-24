// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

/// @file Defines the pkt4_receive and pkt6_receive callout functions.

#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <user_chk.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief  This callout is called at the "pkt4_receive" hook.
///
/// This function searches the UserRegistry for the client indicated by the
/// inbound IPv4 DHCP packet. If the client is found  @todo
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_receive(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "DHCP UserCheckHook : pkt4_receive UserRegistry is null"
                  << std::endl;
        return (1);
    }

    try {
        // Refresh the registry.
        user_registry->refresh();

        // Get the HWAddress to use as the user identifier.
        Pkt4Ptr query;
        handle.getArgument("query4", query);
        HWAddrPtr hwaddr = query->getHWAddr();

        // Store the id we search with.
        handle.setContext(query_user_id_label, hwaddr);

        // Look for the user in the registry.
        UserPtr registered_user = user_registry->findUser(*hwaddr);

        // store user regardless, empty user pointer means non-found
        // cheaper than exception throw overhead
        handle.setContext(registered_user_label, registered_user);
        std::cout << "DHCP UserCheckHook : pkt4_receive user : "
                  << hwaddr->toText() << " is " 
                  << (registered_user ? " registered" : " not registere")
                  << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : pkt4_receive unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

/// @brief  This callout is called at the "pkt6_receive" hook.
///
/// This function searches the UserRegistry for the client indicated by the
/// inbound IPv6 DHCP packet. If the client is found  @todo
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_receive(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "DHCP UserCheckHook : pkt6_receive UserRegistry is null"
                  << std::endl;
        return (1);
    }

    try {
        // Refresh the registry.
        user_registry->refresh();

        // Fetch the inbound packet.
        Pkt6Ptr query;
        handle.getArgument("query6", query);

        // Get the DUID to use as the user identifier.
        OptionPtr opt_duid = query->getOption(D6O_CLIENTID);
        if (!opt_duid) {
            std::cout << "DHCP6 query is missing DUID" << std::endl;
            return (1);
        }
        DuidPtr duid = DuidPtr(new DUID(opt_duid->getData()));

        // Store the id we search with.
        handle.setContext(query_user_id_label, duid);

        // Look for the user in the registry.
        UserPtr registered_user = user_registry->findUser(*duid);

        // store user regardless, empty user pointer means non-found
        // cheaper than exception throw overhead
        handle.setContext(registered_user_label, registered_user);
        std::cout << "DHCP UserCheckHook : pkt6_receive user : "
                  << duid->toText() << " is " 
                  << (registered_user ? " registered" : " not registere")
                  << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : pkt6_receive unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

} // end extern "C"
