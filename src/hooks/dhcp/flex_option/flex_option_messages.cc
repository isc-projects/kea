// File created from ../../../../src/hooks/dhcp/flex_option/flex_option_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID FLEX_OPTION_LOAD_ERROR = "FLEX_OPTION_LOAD_ERROR";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_ADD = "FLEX_OPTION_PROCESS_ADD";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_CLIENT_CLASS = "FLEX_OPTION_PROCESS_CLIENT_CLASS";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_ERROR = "FLEX_OPTION_PROCESS_ERROR";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_REMOVE = "FLEX_OPTION_PROCESS_REMOVE";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_SUB_ADD = "FLEX_OPTION_PROCESS_SUB_ADD";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_SUB_CLIENT_CLASS = "FLEX_OPTION_PROCESS_SUB_CLIENT_CLASS";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_SUB_REMOVE = "FLEX_OPTION_PROCESS_SUB_REMOVE";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_SUB_SUPERSEDE = "FLEX_OPTION_PROCESS_SUB_SUPERSEDE";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_SUPERSEDE = "FLEX_OPTION_PROCESS_SUPERSEDE";
extern const isc::log::MessageID FLEX_OPTION_PROCESS_VENDOR_ID_MISMATCH = "FLEX_OPTION_PROCESS_VENDOR_ID_MISMATCH";
extern const isc::log::MessageID FLEX_OPTION_UNLOAD = "FLEX_OPTION_UNLOAD";

namespace {

const char* values[] = {
    "FLEX_OPTION_LOAD_ERROR", "loading Flex Option hooks library failed: %1",
    "FLEX_OPTION_PROCESS_ADD", "Added the option code %1 with value %2",
    "FLEX_OPTION_PROCESS_CLIENT_CLASS", "Skip processing of the option code %1 for class '%2'",
    "FLEX_OPTION_PROCESS_ERROR", "An error occurred processing query %1: %2",
    "FLEX_OPTION_PROCESS_REMOVE", "Removed option code %1",
    "FLEX_OPTION_PROCESS_SUB_ADD", "Added the sub-option code %1 in option code %2 with value %3",
    "FLEX_OPTION_PROCESS_SUB_CLIENT_CLASS", "Skip processing of the sub-option code %1 in option code %2 for class '%3'",
    "FLEX_OPTION_PROCESS_SUB_REMOVE", "Removed sub-option code %1 in option code %2",
    "FLEX_OPTION_PROCESS_SUB_SUPERSEDE", "Supersedes the sub-option code %1 in option code %2 with value %3",
    "FLEX_OPTION_PROCESS_SUPERSEDE", "Supersedes the option code %1 with value %2",
    "FLEX_OPTION_PROCESS_VENDOR_ID_MISMATCH", "Skip processing of vendor option code %1 with vendor id %2 not matching wanted %3",
    "FLEX_OPTION_UNLOAD", "Flex Option hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

