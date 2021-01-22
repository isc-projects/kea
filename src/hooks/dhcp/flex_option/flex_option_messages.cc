// File created from ../../../../src/hooks/dhcp/flex_option/flex_option_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID FLEX_OPTION_LOAD_ERROR = "FLEX_OPTION_LOAD_ERROR";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_ADD = "FLEX_OPTION_PROCESS_ADD";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_ERROR = "FLEX_OPTION_PROCESS_ERROR";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_REMOVE = "FLEX_OPTION_PROCESS_REMOVE";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_SUPERSEDE = "FLEX_OPTION_PROCESS_SUPERSEDE";
extern const isc::log::MessageID FLEX_OPTION_UNLOAD = "FLEX_OPTION_UNLOAD";

namespace {

const char* values[] = {
    "FLEX_OPTION_LOAD_ERROR", "loading Flex Option hooks library failed: %1",
    "FLEX_OPTION_PROCESS_ADD", "Added the option code %1 value by %2",
    "FLEX_OPTION_PROCESS_ERROR", "An error occurred processing query %1: %2",
    "FLEX_OPTION_PROCESS_REMOVE", "Removed option code %1",
    "FLEX_OPTION_PROCESS_SUPERSEDE", "Supersedes the value of option code %1 by %2",
    "FLEX_OPTION_UNLOAD", "Flex Option hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

