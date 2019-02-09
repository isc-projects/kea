// File created from ../../../src/lib/dhcp_ddns/dhcp_ddns_messages.mes on Fri Feb 08 2019 20:17

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp_ddns {

extern const isc::log::MessageID DHCP_DDNS_INVALID_NCR = "DHCP_DDNS_INVALID_NCR";
extern const isc::log::MessageID DHCP_DDNS_NCR_FLUSH_IO_ERROR = "DHCP_DDNS_NCR_FLUSH_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_LISTEN_CLOSE_ERROR = "DHCP_DDNS_NCR_LISTEN_CLOSE_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_RECV_NEXT_ERROR = "DHCP_DDNS_NCR_RECV_NEXT_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_SEND_CLOSE_ERROR = "DHCP_DDNS_NCR_SEND_CLOSE_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_SEND_NEXT_ERROR = "DHCP_DDNS_NCR_SEND_NEXT_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_CLEAR_READY_ERROR = "DHCP_DDNS_NCR_UDP_CLEAR_READY_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_RECV_CANCELED = "DHCP_DDNS_NCR_UDP_RECV_CANCELED";
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_RECV_ERROR = "DHCP_DDNS_NCR_UDP_RECV_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_SEND_CANCELED = "DHCP_DDNS_NCR_UDP_SEND_CANCELED";
extern const isc::log::MessageID DHCP_DDNS_NCR_UDP_SEND_ERROR = "DHCP_DDNS_NCR_UDP_SEND_ERROR";
extern const isc::log::MessageID DHCP_DDNS_UDP_SENDER_WATCH_SOCKET_CLOSE_ERROR = "DHCP_DDNS_UDP_SENDER_WATCH_SOCKET_CLOSE_ERROR";
extern const isc::log::MessageID DHCP_DDNS_UNCAUGHT_NCR_RECV_HANDLER_ERROR = "DHCP_DDNS_UNCAUGHT_NCR_RECV_HANDLER_ERROR";
extern const isc::log::MessageID DHCP_DDNS_UNCAUGHT_NCR_SEND_HANDLER_ERROR = "DHCP_DDNS_UNCAUGHT_NCR_SEND_HANDLER_ERROR";

} // namespace dhcp_ddns
} // namespace isc

namespace {

const char* values[] = {
    "DHCP_DDNS_INVALID_NCR", "application received an invalid DNS update request: %1",
    "DHCP_DDNS_NCR_FLUSH_IO_ERROR", "DHCP-DDNS Last send before stopping did not complete successfully: %1",
    "DHCP_DDNS_NCR_LISTEN_CLOSE_ERROR", "application encountered an error while closing the listener used to receive NameChangeRequests : %1",
    "DHCP_DDNS_NCR_RECV_NEXT_ERROR", "application could not initiate the next read following a request receive.",
    "DHCP_DDNS_NCR_SEND_CLOSE_ERROR", "DHCP-DDNS client encountered an error while closing the sender connection used to send NameChangeRequests: %1",
    "DHCP_DDNS_NCR_SEND_NEXT_ERROR", "DHCP-DDNS client could not initiate the next request send following send completion: %1",
    "DHCP_DDNS_NCR_UDP_CLEAR_READY_ERROR", "NCR UDP watch socket failed to clear: %1",
    "DHCP_DDNS_NCR_UDP_RECV_CANCELED", "UDP socket receive was canceled while listening for DNS Update requests",
    "DHCP_DDNS_NCR_UDP_RECV_ERROR", "UDP socket receive error while listening for DNS Update requests: %1",
    "DHCP_DDNS_NCR_UDP_SEND_CANCELED", "UDP socket send was canceled while sending a DNS Update request to DHCP_DDNS: %1",
    "DHCP_DDNS_NCR_UDP_SEND_ERROR", "UDP socket send error while sending a DNS Update request: %1",
    "DHCP_DDNS_UDP_SENDER_WATCH_SOCKET_CLOSE_ERROR", "watch socket failed to close: %1",
    "DHCP_DDNS_UNCAUGHT_NCR_RECV_HANDLER_ERROR", "unexpected exception thrown from the application receive completion handler: %1",
    "DHCP_DDNS_UNCAUGHT_NCR_SEND_HANDLER_ERROR", "unexpected exception thrown from the DHCP-DDNS client send completion handler: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

