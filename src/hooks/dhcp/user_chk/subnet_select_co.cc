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

/// @file Defines the subnet4_select and subnet6_select callout functions.

#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/subnet.h>
#include <user_registry.h>

#include <fstream>
#include <string>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace std;

extern UserRegistryPtr user_registry;
extern std::fstream user_chk_output;
extern const char* registry_fname;
extern const char* user_chk_output_fname;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Adds an entry to the end of the user check outcome file.
///
/// Each user entry is written in an ini-like format, with one name-value pair
/// per line as follows:
///
/// id_type=<id type>
/// client=<id str>
/// subnet=<subnet str>
/// registered=<is registered>"
///
/// where:
/// <id type> text label of the id type: "HW_ADDR" or "DUID"
/// <id str> user's id formatted as either isc::dhcp::Hwaddr.toText() or
/// isc::dhcp::DUID.toText()
/// <subnet str> selected subnet formatted as isc::dhcp::Subnet4::toText() or
/// isc::dhcp::Subnet6::toText() as appropriate.
/// <is registered> "yes" or "no"
///
/// Sample IPv4 entry would like this:
///
/// @code
/// id_type=DUID
/// client=00:01:00:01:19:ef:e6:3b:00:0c:01:02:03:04
/// subnet=2001:db8:2::/64
/// registered=yes
/// id_type=duid
/// @endcode
///
/// Sample IPv4 entry would like this:
///
/// @code
/// id_type=DUID
/// id_type=HW_ADDR
/// client=hwtype=1 00:0c:01:02:03:05
/// subnet=152.77.5.0/24
/// registered=no
/// @endcode
///
/// @param id_type_str text label identify the id type
/// @param id_val_str text representation of the user id
/// @param subnet_str text representation  of the selected subnet
/// @param registered boolean indicating if the user is registered or not
void generate_output_record(const std::string& id_type_str,
                            const std::string& id_val_str,
                            const std::string& subnet_str,
                            const bool& registered)
{
    user_chk_output << "id_type=" << id_type_str << std::endl
                    << "client=" << id_val_str << std::endl
                    << "subnet=" << subnet_str << std::endl
                    << "registered=" << (registered ? "yes" : "no")
                    << std::endl;

    // @todo Flush is here to ensure output is immediate for demo purposes.
    // Performance would generally dictate not using it.
    flush(user_chk_output);
}

/// @brief  This callout is called at the "subnet4_select" hook.
///
/// This function searches the UserRegistry for the client indicated by the
/// inbound IPv4 DHCP packet. If the client is found in the registry output
/// the generate outcome record and return.
///
/// If the client is not found in the registry replace the selected subnet
/// with the restricted access subnet, then generate the outcome record and
/// return.  By convention, it is assumed that last subnet in the list of
/// available subnets is the restricted access subnet.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int subnet4_select(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "DHCP UserCheckHook : subnet4_select UserRegistry is null"
                  << std::endl;
        return (1);
    }

    try {
        // Get subnet collection. If it's empty just bail nothing to do.
        const isc::dhcp::Subnet4Collection *subnets = NULL;
        handle.getArgument("subnet4collection", subnets);
        if (subnets->empty()) {
            return 0;
        }

        // Refresh the registry.
        user_registry->refresh();

        // Get the HWAddress as the user identifier.
        Pkt4Ptr query;
        handle.getArgument("query4", query);
        HWAddrPtr hwaddr = query->getHWAddr();

        // Look for the user.
        UserPtr registered_user = user_registry->findUser(*hwaddr);
        if (registered_user) {
            // User is in the registry, so leave the pre-selected subnet alone.
            Subnet4Ptr subnet;
            handle.getArgument("subnet4", subnet);
            // Add the outcome entry to the output file.
            generate_output_record(UserId::HW_ADDRESS_STR, hwaddr->toText(),
                                   subnet->toText(), true);
        } else {
            // User is not in the registry, so assign them to the last subnet
            // in the collection.  By convention we are assuming this is the
            // restricted subnet.
            Subnet4Ptr subnet = subnets->back();
            handle.setArgument("subnet4", subnet);
            // Add the outcome entry to the output file.
            generate_output_record(UserId::HW_ADDRESS_STR, hwaddr->toText(),
                                   subnet->toText(), false);
        }
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : subnet6_select unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

/// @brief  This callout is called at the "subnet6_select" hook.
///
/// This function searches the UserRegistry for the client indicated by the
/// inbound IPv6 DHCP packet. If the client is found in the registry generate
/// the outcome record and return.
///
/// If the client is not found in the registry replace the selected subnet
/// with the restricted access subnet, then generate the outcome record and
/// return.  By convention, it is assumed that last subnet in the list of
/// available subnets is the restricted access subnet.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int subnet6_select(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "DHCP UserCheckHook : subnet6_select UserRegistry is null"
                  << std::endl;
        return (1);
    }

    try {
        // Get subnet collection. If it's empty just bail nothing to do.
        const isc::dhcp::Subnet6Collection *subnets = NULL;
        handle.getArgument("subnet6collection", subnets);
        if (subnets->empty()) {
            return 0;
        }

        // Refresh the registry.
        user_registry->refresh();

        // Get the HWAddress as the user identifier.
        Pkt6Ptr query;
        handle.getArgument("query6", query);

        DuidPtr duid;
        OptionPtr opt_duid = query->getOption(D6O_CLIENTID);
        if (!opt_duid) {
            std::cout << "DHCP6 query is missing DUID" << std::endl;
            return (1);
        }

        duid = DuidPtr(new DUID(opt_duid->getData()));

        // Look for the user.
        UserPtr registered_user = user_registry->findUser(*duid);
        if (registered_user) {
            // User is in the registry, so leave the pre-selected subnet alone.
            Subnet6Ptr subnet;
            handle.getArgument("subnet6", subnet);
            // Add the outcome entry to the output file.
            generate_output_record(UserId::DUID_STR, duid->toText(),
                                   subnet->toText(), true);
        } else {
            // User is not in the registry, so assign them to the last subnet
            // in the collection.  By convention we are assuming this is the
            // restricted subnet.
            Subnet6Ptr subnet = subnets->back();
            handle.setArgument("subnet6", subnet);
            // Add the outcome entry to the output file.
            generate_output_record(UserId::DUID_STR, duid->toText(),
                                   subnet->toText(), false);
        }
    } catch (const std::exception& ex) {
        std::cout << "DHCP UserCheckHook : subnet6_select unexpected error: "
                  << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

}
