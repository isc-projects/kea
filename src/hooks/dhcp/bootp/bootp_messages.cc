// File created from ../../../../src/hooks/dhcp/bootp/bootp_messages.mes on Fri Nov 22 2019 01:05

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID BOOTP_ADDED_CLASS = "BOOTP_ADDED_CLASS";
extern const isc::log::MessageID BOOTP_ADDED_MSGTYPE = "BOOTP_ADDED_MSGTYPE";
extern const isc::log::MessageID BOOTP_LOAD = "BOOTP_LOAD";
extern const isc::log::MessageID BOOTP_UNLOAD = "BOOTP_UNLOAD";

namespace {

const char* values[] = {
    "BOOTP_ADDED_CLASS", "added BOOTP class to a BOOTP query: %1",
    "BOOTP_ADDED_MSGTYPE", "added DHCPREQUEST message type to a BOOTP query: %1",
    "BOOTP_LOAD", "Bootp hooks library has been loaded",
    "BOOTP_UNLOAD", "Bootp hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

