// File created from src/lib/dhcp/dhcp_messages.mes

#ifndef DHCP_MESSAGES_H
#define DHCP_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID DHCP_ADD_EXTERNAL_SOCKET;
extern const isc::log::MessageID DHCP_DELETE_ALL_EXTERNAL_SOCKETS;
extern const isc::log::MessageID DHCP_DELETE_EXTERNAL_SOCKET;

} // namespace dhcp
} // namespace isc

#endif // DHCP_MESSAGES_H
