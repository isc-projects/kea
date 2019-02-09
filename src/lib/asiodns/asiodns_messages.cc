// File created from ../../../src/lib/asiodns/asiodns_messages.mes on Fri Feb 08 2019 20:17

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace asiodns {

extern const isc::log::MessageID ASIODNS_FD_ADD_TCP = "ASIODNS_FD_ADD_TCP";
extern const isc::log::MessageID ASIODNS_FD_ADD_UDP = "ASIODNS_FD_ADD_UDP";
extern const isc::log::MessageID ASIODNS_FETCH_COMPLETED = "ASIODNS_FETCH_COMPLETED";
extern const isc::log::MessageID ASIODNS_FETCH_STOPPED = "ASIODNS_FETCH_STOPPED";
extern const isc::log::MessageID ASIODNS_OPEN_SOCKET = "ASIODNS_OPEN_SOCKET";
extern const isc::log::MessageID ASIODNS_READ_DATA = "ASIODNS_READ_DATA";
extern const isc::log::MessageID ASIODNS_READ_TIMEOUT = "ASIODNS_READ_TIMEOUT";
extern const isc::log::MessageID ASIODNS_SEND_DATA = "ASIODNS_SEND_DATA";
extern const isc::log::MessageID ASIODNS_SYNC_UDP_CLOSE_FAIL = "ASIODNS_SYNC_UDP_CLOSE_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_ACCEPT_FAIL = "ASIODNS_TCP_ACCEPT_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_CLEANUP_CLOSE_FAIL = "ASIODNS_TCP_CLEANUP_CLOSE_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_CLOSE_ACCEPTOR_FAIL = "ASIODNS_TCP_CLOSE_ACCEPTOR_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_CLOSE_FAIL = "ASIODNS_TCP_CLOSE_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_CLOSE_NORESP_FAIL = "ASIODNS_TCP_CLOSE_NORESP_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_GETREMOTE_FAIL = "ASIODNS_TCP_GETREMOTE_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_READDATA_FAIL = "ASIODNS_TCP_READDATA_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_READLEN_FAIL = "ASIODNS_TCP_READLEN_FAIL";
extern const isc::log::MessageID ASIODNS_TCP_WRITE_FAIL = "ASIODNS_TCP_WRITE_FAIL";
extern const isc::log::MessageID ASIODNS_UDP_ASYNC_SEND_FAIL = "ASIODNS_UDP_ASYNC_SEND_FAIL";
extern const isc::log::MessageID ASIODNS_UDP_CLOSE_FAIL = "ASIODNS_UDP_CLOSE_FAIL";
extern const isc::log::MessageID ASIODNS_UDP_RECEIVE_FAIL = "ASIODNS_UDP_RECEIVE_FAIL";
extern const isc::log::MessageID ASIODNS_UDP_SYNC_RECEIVE_FAIL = "ASIODNS_UDP_SYNC_RECEIVE_FAIL";
extern const isc::log::MessageID ASIODNS_UDP_SYNC_SEND_FAIL = "ASIODNS_UDP_SYNC_SEND_FAIL";
extern const isc::log::MessageID ASIODNS_UNKNOWN_ORIGIN = "ASIODNS_UNKNOWN_ORIGIN";
extern const isc::log::MessageID ASIODNS_UNKNOWN_RESULT = "ASIODNS_UNKNOWN_RESULT";

} // namespace asiodns
} // namespace isc

namespace {

const char* values[] = {
    "ASIODNS_FD_ADD_TCP", "adding a new TCP server by opened fd %1",
    "ASIODNS_FD_ADD_UDP", "adding a new UDP server by opened fd %1",
    "ASIODNS_FETCH_COMPLETED", "upstream fetch to %1(%2) has now completed",
    "ASIODNS_FETCH_STOPPED", "upstream fetch to %1(%2) has been stopped",
    "ASIODNS_OPEN_SOCKET", "error %1 opening %2 socket to %3(%4)",
    "ASIODNS_READ_DATA", "error %1 reading %2 data from %3(%4)",
    "ASIODNS_READ_TIMEOUT", "receive timeout while waiting for data from %1(%2)",
    "ASIODNS_SEND_DATA", "error %1 sending data using %2 to %3(%4)",
    "ASIODNS_SYNC_UDP_CLOSE_FAIL", "failed to close a DNS/UDP socket: %1",
    "ASIODNS_TCP_ACCEPT_FAIL", "failed to accept TCP DNS connection: %1",
    "ASIODNS_TCP_CLEANUP_CLOSE_FAIL", "failed to close a DNS/TCP socket on port cleanup: %1",
    "ASIODNS_TCP_CLOSE_ACCEPTOR_FAIL", "failed to close listening TCP socket: %1",
    "ASIODNS_TCP_CLOSE_FAIL", "failed to close DNS/TCP socket with a client: %1",
    "ASIODNS_TCP_CLOSE_NORESP_FAIL", "failed to close DNS/TCP socket with a client: %1",
    "ASIODNS_TCP_GETREMOTE_FAIL", "failed to get remote address of a DNS TCP connection: %1",
    "ASIODNS_TCP_READDATA_FAIL", "failed to get DNS data on a TCP socket: %1",
    "ASIODNS_TCP_READLEN_FAIL", "failed to get DNS data length on a TCP socket: %1",
    "ASIODNS_TCP_WRITE_FAIL", "failed to send DNS message over a TCP socket: %1",
    "ASIODNS_UDP_ASYNC_SEND_FAIL", "Error sending UDP packet to %1: %2",
    "ASIODNS_UDP_CLOSE_FAIL", "failed to close a DNS/UDP socket: %1",
    "ASIODNS_UDP_RECEIVE_FAIL", "failed to receive UDP DNS packet: %1",
    "ASIODNS_UDP_SYNC_RECEIVE_FAIL", "failed to receive UDP DNS packet: %1",
    "ASIODNS_UDP_SYNC_SEND_FAIL", "Error sending UDP packet to %1: %2",
    "ASIODNS_UNKNOWN_ORIGIN", "unknown origin for ASIO error code %1 (protocol: %2, address %3)",
    "ASIODNS_UNKNOWN_RESULT", "unknown result (%1) when IOFetch::stop() was executed for I/O to %2(%3)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

