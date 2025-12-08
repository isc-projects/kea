// File created from src/lib/dhcp/dhcp_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID DHCP_ADD_EXTERNAL_SOCKET = "DHCP_ADD_EXTERNAL_SOCKET";
extern const isc::log::MessageID DHCP_DELETE_ALL_EXTERNAL_SOCKETS = "DHCP_DELETE_ALL_EXTERNAL_SOCKETS";
extern const isc::log::MessageID DHCP_DELETE_EXTERNAL_SOCKET = "DHCP_DELETE_EXTERNAL_SOCKET";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "DHCP_ADD_EXTERNAL_SOCKET", "Attempted to register external socket %1 from different thread %2 than main thread %3",
    "DHCP_DELETE_ALL_EXTERNAL_SOCKETS", "Attempted to unregister external sockets from different thread %1 than main thread %2",
    "DHCP_DELETE_EXTERNAL_SOCKET", "Attempted to unregister external socket %1 from different thread %2 than main thread %3",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

