// File created from ../../../../src/hooks/dhcp/bootp/bootp_messages.mes on Mon Nov 18 2019 09:30

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID BOOTP_LOAD = "BOOTP_LOAD";
extern const isc::log::MessageID BOOTP_PROCESSED = "BOOTP_PROCESSED";
extern const isc::log::MessageID BOOTP_PROCESS_ERROR = "BOOTP_PROCESS_ERROR";
extern const isc::log::MessageID BOOTP_UNLOAD = "BOOTP_UNLOAD";

namespace {

const char* values[] = {
    "BOOTP_LOAD", "Bootp hooks library has been loaded",
    "BOOTP_PROCESSED", "processed BOOTP query: %1",
    "BOOTP_PROCESS_ERROR", "%1: failed to process packet: %2",
    "BOOTP_UNLOAD", "Bootp hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

