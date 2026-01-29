// File created from src/lib/dhcp/dhcp_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID DHCP_ADD_EXTERNAL_SOCKET_ALREADY_EXISTS = "DHCP_ADD_EXTERNAL_SOCKET_ALREADY_EXISTS";
extern const isc::log::MessageID DHCP_ADD_EXTERNAL_SOCKET_BAD_THREAD = "DHCP_ADD_EXTERNAL_SOCKET_BAD_THREAD";
extern const isc::log::MessageID DHCP_DELETE_ALL_EXTERNAL_SOCKETS_BAD_THREAD = "DHCP_DELETE_ALL_EXTERNAL_SOCKETS_BAD_THREAD";
extern const isc::log::MessageID DHCP_DELETE_EXTERNAL_SOCKET_BAD_THREAD = "DHCP_DELETE_EXTERNAL_SOCKET_BAD_THREAD";
extern const isc::log::MessageID DHCP_DELETE_EXTERNAL_SOCKET_NOT_FOUND = "DHCP_DELETE_EXTERNAL_SOCKET_NOT_FOUND";
extern const isc::log::MessageID DHCP_IFACE_SOCKET_ERROR = "DHCP_IFACE_SOCKET_ERROR";
extern const isc::log::MessageID DHCP_RECEIVE4_UNKNOWN = "DHCP_RECEIVE4_UNKNOWN";
extern const isc::log::MessageID DHCP_RECEIVE6_UNKNOWN = "DHCP_RECEIVE6_UNKNOWN";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "DHCP_ADD_EXTERNAL_SOCKET_ALREADY_EXISTS", "Adding an already existing external socket %1",
    "DHCP_ADD_EXTERNAL_SOCKET_BAD_THREAD", "Attempted to register external socket %1 from different thread %2 than main thread %3",
    "DHCP_DELETE_ALL_EXTERNAL_SOCKETS_BAD_THREAD", "Attempted to unregister external sockets from different thread %1 than main thread %2",
    "DHCP_DELETE_EXTERNAL_SOCKET_BAD_THREAD", "Attempted to unregister external socket %1 from different thread %2 than main thread %3",
    "DHCP_DELETE_EXTERNAL_SOCKET_NOT_FOUND", "Deleting a not found external socket %1",
    "DHCP_IFACE_SOCKET_ERROR", "Got an error on the interface socket %1 of interface %2: %3",
    "DHCP_RECEIVE4_UNKNOWN", "Received data over unknown socket",
    "DHCP_RECEIVE6_UNKNOWN", "Received data over unknown socket",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

