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


extern "C" {


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

    flush(user_chk_output);
}

// This callout is called at the "subnet4_select" hook.
int subnet4_select(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "UserCheckHook: UserRegistry is null!" << std::endl;
        return (1);
    }

    try {
        // Refresh the registry.
        user_registry->refresh();

        // Get the HWAddress as the user identifier.
        Pkt4Ptr query;
        handle.getArgument("query4", query);
        HWAddrPtr hwaddr = query->getHWAddr();

        // Look for the user.
        UserPtr registered_user = user_registry->findUser(*hwaddr);
        if (registered_user) {
            // User is in the registry, so leave the pre-selected
            // subnet alone.
            Subnet4Ptr subnet;
            handle.getArgument("subnet4", subnet);
            generate_output_record("mac", hwaddr->toText(), subnet->toText(),
                                   true);
        } else {
            // User is not in the registry, so assign them to
            // the last subnet in the collection.  By convention
            // we are assuming this is the restricted subnet.
            const isc::dhcp::Subnet4Collection *subnets = NULL;
            handle.getArgument("subnet4collection", subnets);
            Subnet4Ptr subnet = subnets->back();
            handle.setArgument("subnet4", subnet);
            generate_output_record("mac", hwaddr->toText(), subnet->toText(),
                                   false);
        }
    } catch (const std::exception& ex) {
        std::cout << "UserCheckHook: Exception in subnet4_select callout:"
                  << ex.what() << std::endl;

        return (1);
    }

    return (0);
}
// This callout is called at the "subnet6_select" hook.
int subnet6_select(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "UserCheckHook: UserRegistry is null!" << std::endl;
        return (1);
    }

    try {
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
            // User is in the registry, so leave the pre-selected
            // subnet alone.
            Subnet6Ptr subnet;
            handle.getArgument("subnet6", subnet);
            generate_output_record("duid", duid->toText(), subnet->toText(),
                                   true);
        } else {
            // User is not in the registry, so assign them to
            // the last subnet in the collection.  By convention
            // we are assuming this is the restricted subnet.
            const isc::dhcp::Subnet6Collection *subnets = NULL;
            handle.getArgument("subnet6collection", subnets);
            Subnet6Ptr subnet = subnets->back();
            handle.setArgument("subnet6", subnet);
            generate_output_record("duid", duid->toText(), subnet->toText(),
                                   false);
        }
    } catch (const std::exception& ex) {
        std::cout << "UserCheckHook: Exception in subnet6_select callout:"                        << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

}
