// File created from ../../../../src/hooks/dhcp/scripts/scripts_messages.mes on Thu Sep 19 2019 12:34

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID SCRIPTS_HOOK_LOAD_ERROR = "SCRIPTS_HOOK_LOAD_ERROR";
extern const isc::log::MessageID SCRIPTS_HOOK_SCRIPT_ENTRY = "SCRIPTS_HOOK_SCRIPT_ENTRY";
extern const isc::log::MessageID SCRIPTS_HOOK_UNLOAD_ERROR = "SCRIPTS_HOOK_UNLOAD_ERROR";

namespace {

const char* values[] = {
    "SCRIPTS_HOOK_LOAD_ERROR", "DHCP ScriptsHook could not be loaded: %1",
    "SCRIPTS_HOOK_SCRIPT_ENTRY", "DHCP Scripts Hook will use the following script: %1",
    "SCRIPTS_HOOK_UNLOAD_ERROR", "DHCP Scripts Hook an error occurred unloading the library: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

