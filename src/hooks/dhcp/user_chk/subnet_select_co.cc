#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <user_registry.h>

extern UserRegistryPtr user_registry;

#include <string>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace std;

extern "C" {

// This callout is called at the "subnet4_select" hook.
int subnet4_select(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "UserRegistry is null!" << std::endl;
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
            //@todo give them an unrestricted subnet
            std::cout << "DHCP4 User is registered! :" 
                      << registered_user->getUserId() << std::endl;
        } else {
            //@todo give them a restricted subnet
           std::cout << "DHCP4 User is NOT registered! :" 
                     << hwaddr->toText() << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cout << "Exception in subnet4_select callout:" << ex.what() 
                  << std::endl;
            
    }

    return (0);
}

// This callout is called at the "subnet6_select" hook.
int subnet6_select(CalloutHandle& handle) {
    if (!user_registry) {
        std::cout << "UserRegistry is null!" << std::endl;
    }

    try {
        // Refresh the registry.
        user_registry->refresh();

        // Get the HWAddress as the user identifier.
        Pkt6Ptr query;
        handle.getArgument("query6", query);

        DuidPtr duid;
        OptionPtr opt_duid = query->getOption(D6O_CLIENTID);
        if (opt_duid) {
            duid = DuidPtr(new DUID(opt_duid->getData()));
        } else {
            std::cout << "DHCP6 query is missing DUID" << std::endl;
        }

        // Look for the user.
        UserPtr registered_user = user_registry->findUser(*duid);
        if (registered_user) {
            //@todo give them an unrestricted subnet
            std::cout << "DHCP6 User is registered! :" 
                      << registered_user->getUserId() << std::endl;
        } else {
            //@todo give them a restricted subnet
           std::cout << "DHCP6 User is NOT registered! :" 
                     << duid->toText() << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cout << "Exception in subnet6_select callout:" << ex.what() 
                  << std::endl;
            
    }

    return (0);
}

}
