// File created from ../../../../src/hooks/dhcp/user_chk/user_chk_messages.mes on Fri Feb 08 2019 20:34

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID USER_CHK_HOOK_LOAD_ERROR = "USER_CHK_HOOK_LOAD_ERROR";
extern const isc::log::MessageID USER_CHK_HOOK_UNLOAD_ERROR = "USER_CHK_HOOK_UNLOAD_ERROR";
extern const isc::log::MessageID USER_CHK_SUBNET4_SELECT_ERROR = "USER_CHK_SUBNET4_SELECT_ERROR";
extern const isc::log::MessageID USER_CHK_SUBNET4_SELECT_REGISTRY_NULL = "USER_CHK_SUBNET4_SELECT_REGISTRY_NULL";
extern const isc::log::MessageID USER_CHK_SUBNET6_SELECT_ERROR = "USER_CHK_SUBNET6_SELECT_ERROR";
extern const isc::log::MessageID USER_CHK_SUBNET6_SELECT_REGISTRY_NULL = "USER_CHK_SUBNET6_SELECT_REGISTRY_NULL";

namespace {

const char* values[] = {
    "USER_CHK_HOOK_LOAD_ERROR", "DHCP UserCheckHook could not be loaded: %1",
    "USER_CHK_HOOK_UNLOAD_ERROR", "DHCP UserCheckHook an error occurred unloading the library: %1",
    "USER_CHK_SUBNET4_SELECT_ERROR", "DHCP UserCheckHook an unexpected error occurred in subnet4_select callout: %1",
    "USER_CHK_SUBNET4_SELECT_REGISTRY_NULL", "DHCP UserCheckHook UserRegistry has not been created.",
    "USER_CHK_SUBNET6_SELECT_ERROR", "DHCP UserCheckHook an unexpected error occurred in subnet6_select callout: %1",
    "USER_CHK_SUBNET6_SELECT_REGISTRY_NULL", "DHCP UserCheckHook UserRegistry has not been created.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

