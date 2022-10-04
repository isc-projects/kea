// File created from ../../../src/lib/tcp/tcp_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace asiolink {

extern const isc::log::MessageID TCP_BAD_CLIENT_REQUEST_RECEIVED = "TCP_BAD_CLIENT_REQUEST_RECEIVED";
extern const isc::log::MessageID TCP_CLIENT_REQUEST_RECEIVED = "TCP_CLIENT_REQUEST_RECEIVED";
extern const isc::log::MessageID TCP_CLIENT_REQUEST_RECEIVED_DETAILS = "TCP_CLIENT_REQUEST_RECEIVED_DETAILS";
extern const isc::log::MessageID TCP_CONNECTION_CLOSE_CALLBACK_FAILED = "TCP_CONNECTION_CLOSE_CALLBACK_FAILED";
extern const isc::log::MessageID TCP_CONNECTION_HANDSHAKE_FAILED = "TCP_CONNECTION_HANDSHAKE_FAILED";
extern const isc::log::MessageID TCP_CONNECTION_HANDSHAKE_START = "TCP_CONNECTION_HANDSHAKE_START";
extern const isc::log::MessageID TCP_CONNECTION_SHUTDOWN = "TCP_CONNECTION_SHUTDOWN";
extern const isc::log::MessageID TCP_CONNECTION_SHUTDOWN_FAILED = "TCP_CONNECTION_SHUTDOWN_FAILED";
extern const isc::log::MessageID TCP_CONNECTION_STOP = "TCP_CONNECTION_STOP";
extern const isc::log::MessageID TCP_CONNECTION_STOP_FAILED = "TCP_CONNECTION_STOP_FAILED";
extern const isc::log::MessageID TCP_DATA_RECEIVED = "TCP_DATA_RECEIVED";
extern const isc::log::MessageID TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED = "TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED";
extern const isc::log::MessageID TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED = "TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED";
extern const isc::log::MessageID TCP_REQUEST_RECEIVE_START = "TCP_REQUEST_RECEIVE_START";
extern const isc::log::MessageID TCP_SERVER_RESPONSE_SEND = "TCP_SERVER_RESPONSE_SEND";
extern const isc::log::MessageID TCP_SERVER_RESPONSE_SEND_DETAILS = "TCP_SERVER_RESPONSE_SEND_DETAILS";

} // namespace asiolink
} // namespace isc

namespace {

const char* values[] = {
    "TCP_BAD_CLIENT_REQUEST_RECEIVED", "bad request received from %1: %2",
    "TCP_CLIENT_REQUEST_RECEIVED", "received TCP request from %1",
    "TCP_CLIENT_REQUEST_RECEIVED_DETAILS", "detailed information about well-formed request received from %1:\n%2",
    "TCP_CONNECTION_CLOSE_CALLBACK_FAILED", "Connection close callback threw an exception",
    "TCP_CONNECTION_HANDSHAKE_FAILED", "TLS handshake with %1 failed with %2",
    "TCP_CONNECTION_HANDSHAKE_START", "start TLS handshake with %1 with timeout %2",
    "TCP_CONNECTION_SHUTDOWN", "shutting down TCP connection from %1",
    "TCP_CONNECTION_SHUTDOWN_FAILED", "shutting down TCP connection failed",
    "TCP_CONNECTION_STOP", "stopping TCP connection from %1",
    "TCP_CONNECTION_STOP_FAILED", "stopping TCP connection failed",
    "TCP_DATA_RECEIVED", "received %1 bytes from %2",
    "TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED", "closing persistent connection with %1 as a result of a timeout",
    "TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED", "premature connection timeout occurred: in transaction ? %1, transid: %2, current_transid: %3",
    "TCP_REQUEST_RECEIVE_START", "start receiving request from %1 with timeout %2",
    "TCP_SERVER_RESPONSE_SEND", "sending TCP response %1 to %2",
    "TCP_SERVER_RESPONSE_SEND_DETAILS", "detailed information about response sent to %1:\n%2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

