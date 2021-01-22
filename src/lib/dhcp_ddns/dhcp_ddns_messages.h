// File created from ../../../src/lib/dhcp_ddns/dhcp_ddns_messages.mes

#ifndef DHCP_DDNS_MESSAGES_H
#define DHCP_DDNS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp_ddns {

extern const isc::log::MessageID DHCP_DDNS_INVALID_NCR;
extern const isc::log::MessageID DHCP_DDNS_NCR_FLUSH_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_LISTEN_CLOSE_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_RECV_NEXT_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_SEND_CLOSE_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_SEND_NEXT_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_CLEAR_READY_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_RECV_CANCELED;
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_RECV_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_SEND_CANCELED;
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_SEND_ERROR;
extern const isc::log::MessageID DHCP_DDNS_UDP_SENDER_WATCH_SOCKET_CLOSE_ERROR;
extern const isc::log::MessageID DHCP_DDNS_UNCAUGHT_NCR_RECV_HANDLER_ERROR;
extern const isc::log::MessageID DHCP_DDNS_UNCAUGHT_NCR_SEND_HANDLER_ERROR;

} // namespace dhcp_ddns
} // namespace isc

#endif // DHCP_DDNS_MESSAGES_H
