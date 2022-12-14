// File created from ../../../src/lib/tcp/tcp_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace tcp {

extern const isc::log::MessageID MT_TCP_LISTENER_MGR_STARTED = "MT_TCP_LISTENER_MGR_STARTED";
extern const isc::log::MessageID MT_TCP_LISTENER_MGR_STOPPED = "MT_TCP_LISTENER_MGR_STOPPED";
extern const isc::log::MessageID MT_TCP_LISTENER_MGR_STOPPING = "MT_TCP_LISTENER_MGR_STOPPING";
extern const isc::log::MessageID TCP_CLIENT_REQUEST_RECEIVED = "TCP_CLIENT_REQUEST_RECEIVED";
extern const isc::log::MessageID TCP_CONNECTION_CLOSE_CALLBACK_FAILED = "TCP_CONNECTION_CLOSE_CALLBACK_FAILED";
extern const isc::log::MessageID TCP_CONNECTION_REJECTED_BY_FILTER = "TCP_CONNECTION_REJECTED_BY_FILTER";
extern const isc::log::MessageID TCP_CONNECTION_SHUTDOWN = "TCP_CONNECTION_SHUTDOWN";
extern const isc::log::MessageID TCP_CONNECTION_SHUTDOWN_FAILED = "TCP_CONNECTION_SHUTDOWN_FAILED";
extern const isc::log::MessageID TCP_CONNECTION_STOP = "TCP_CONNECTION_STOP";
extern const isc::log::MessageID TCP_CONNECTION_STOP_FAILED = "TCP_CONNECTION_STOP_FAILED";
extern const isc::log::MessageID TCP_DATA_RECEIVED = "TCP_DATA_RECEIVED";
extern const isc::log::MessageID TCP_DATA_SENT = "TCP_DATA_SENT";
extern const isc::log::MessageID TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED = "TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED";
extern const isc::log::MessageID TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED = "TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED";
extern const isc::log::MessageID TCP_REQUEST_RECEIVED_FAILED = "TCP_REQUEST_RECEIVED_FAILED";
extern const isc::log::MessageID TCP_REQUEST_RECEIVE_START = "TCP_REQUEST_RECEIVE_START";
extern const isc::log::MessageID TCP_SERVER_RESPONSE_SEND = "TCP_SERVER_RESPONSE_SEND";
extern const isc::log::MessageID TCP_SERVER_RESPONSE_SEND_DETAILS = "TCP_SERVER_RESPONSE_SEND_DETAILS";
extern const isc::log::MessageID TLS_CONNECTION_HANDSHAKE_FAILED = "TLS_CONNECTION_HANDSHAKE_FAILED";
extern const isc::log::MessageID TLS_CONNECTION_HANDSHAKE_START = "TLS_CONNECTION_HANDSHAKE_START";
extern const isc::log::MessageID TLS_REQUEST_RECEIVE_START = "TLS_REQUEST_RECEIVE_START";
extern const isc::log::MessageID TLS_SERVER_RESPONSE_SEND = "TLS_SERVER_RESPONSE_SEND";

} // namespace tcp
} // namespace isc

namespace {

const char* values[] = {
    "MT_TCP_LISTENER_MGR_STARTED", "MtTcpListenerMgr started with %1 threads, listening on %2:%3, use TLS: %4",
    "MT_TCP_LISTENER_MGR_STOPPED", "MtTcpListenerMgr for %1:%2 stopped.",
    "MT_TCP_LISTENER_MGR_STOPPING", "Stopping MtTcpListenerMgr for %1:%2",
    "TCP_CLIENT_REQUEST_RECEIVED", "received TCP request from %1",
    "TCP_CONNECTION_CLOSE_CALLBACK_FAILED", "Connection close callback threw an exception",
    "TCP_CONNECTION_REJECTED_BY_FILTER", "connection from %1 has been denied by the connection filter.",
    "TCP_CONNECTION_SHUTDOWN", "shutting down TCP connection from %1",
    "TCP_CONNECTION_SHUTDOWN_FAILED", "shutting down TCP connection failed",
    "TCP_CONNECTION_STOP", "stopping TCP connection from %1",
    "TCP_CONNECTION_STOP_FAILED", "stopping TCP connection failed",
    "TCP_DATA_RECEIVED", "received %1 bytes from %2",
    "TCP_DATA_SENT", "send %1 bytes to %2",
    "TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED", "closing connection with %1 as a result of a timeout",
    "TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED", "premature connection timeout occurred: in transaction ? %1, transid: %2, current_transid: %3",
    "TCP_REQUEST_RECEIVED_FAILED", "An unexpected error occurred processing a request from %1, error: %2",
    "TCP_REQUEST_RECEIVE_START", "start receiving request from %1 with timeout %2",
    "TCP_SERVER_RESPONSE_SEND", "sending TCP response to %1",
    "TCP_SERVER_RESPONSE_SEND_DETAILS", "detailed information about response sent to %1:\n%2",
    "TLS_CONNECTION_HANDSHAKE_FAILED", "TLS handshake with %1 failed with %2",
    "TLS_CONNECTION_HANDSHAKE_START", "start TLS handshake with %1 with timeout %2",
    "TLS_REQUEST_RECEIVE_START", "start receiving request from %1 with timeout %2",
    "TLS_SERVER_RESPONSE_SEND", "sending TLS response to %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

