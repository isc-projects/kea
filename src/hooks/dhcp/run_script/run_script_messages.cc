// File created from ../../../../src/hooks/dhcp/run_script/run_script_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID RUN_SCRIPT_LOAD = "RUN_SCRIPT_LOAD";
extern const isc::log::MessageID RUN_SCRIPT_LOAD_ERROR = "RUN_SCRIPT_LOAD_ERROR";
extern const isc::log::MessageID RUN_SCRIPT_UNLOAD = "RUN_SCRIPT_UNLOAD";

namespace {

const char* values[] = {
    "RUN_SCRIPT_LOAD", "Run Script hooks library has been loaded",
    "RUN_SCRIPT_LOAD_ERROR", "Run Script hooks library failed: %1",
    "RUN_SCRIPT_UNLOAD", "Run Script hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

