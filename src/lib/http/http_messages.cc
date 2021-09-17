// File created from ../../../src/lib/http/http_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace http {

extern const isc::log::MessageID HTTPS_REQUEST_RECEIVE_START = "HTTPS_REQUEST_RECEIVE_START";
extern const isc::log::MessageID HTTP_BAD_CLIENT_REQUEST_RECEIVED = "HTTP_BAD_CLIENT_REQUEST_RECEIVED";
extern const isc::log::MessageID HTTP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS = "HTTP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS";
extern const isc::log::MessageID HTTP_BAD_SERVER_RESPONSE_RECEIVED = "HTTP_BAD_SERVER_RESPONSE_RECEIVED";
extern const isc::log::MessageID HTTP_BAD_SERVER_RESPONSE_RECEIVED_DETAILS = "HTTP_BAD_SERVER_RESPONSE_RECEIVED_DETAILS";
extern const isc::log::MessageID HTTP_CLIENT_MT_STARTED = "HTTP_CLIENT_MT_STARTED";
extern const isc::log::MessageID HTTP_CLIENT_QUEUE_SIZE_GROWING = "HTTP_CLIENT_QUEUE_SIZE_GROWING";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_RECEIVED = "HTTP_CLIENT_REQUEST_RECEIVED";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_RECEIVED_DETAILS = "HTTP_CLIENT_REQUEST_RECEIVED_DETAILS";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_SEND = "HTTP_CLIENT_REQUEST_SEND";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_SEND_DETAILS = "HTTP_CLIENT_REQUEST_SEND_DETAILS";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_TIMEOUT_OCCURRED = "HTTP_CLIENT_REQUEST_TIMEOUT_OCCURRED";
extern const isc::log::MessageID HTTP_CONNECTION_CLOSE_CALLBACK_FAILED = "HTTP_CONNECTION_CLOSE_CALLBACK_FAILED";
extern const isc::log::MessageID HTTP_CONNECTION_HANDSHAKE_FAILED = "HTTP_CONNECTION_HANDSHAKE_FAILED";
extern const isc::log::MessageID HTTP_CONNECTION_HANDSHAKE_START = "HTTP_CONNECTION_HANDSHAKE_START";
extern const isc::log::MessageID HTTP_CONNECTION_SHUTDOWN = "HTTP_CONNECTION_SHUTDOWN";
extern const isc::log::MessageID HTTP_CONNECTION_SHUTDOWN_FAILED = "HTTP_CONNECTION_SHUTDOWN_FAILED";
extern const isc::log::MessageID HTTP_CONNECTION_STOP = "HTTP_CONNECTION_STOP";
extern const isc::log::MessageID HTTP_CONNECTION_STOP_FAILED = "HTTP_CONNECTION_STOP_FAILED";
extern const isc::log::MessageID HTTP_DATA_RECEIVED = "HTTP_DATA_RECEIVED";
extern const isc::log::MessageID HTTP_IDLE_CONNECTION_TIMEOUT_OCCURRED = "HTTP_IDLE_CONNECTION_TIMEOUT_OCCURRED";
extern const isc::log::MessageID HTTP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED = "HTTP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED";
extern const isc::log::MessageID HTTP_REQUEST_RECEIVE_START = "HTTP_REQUEST_RECEIVE_START";
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_RECEIVED = "HTTP_SERVER_RESPONSE_RECEIVED";
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_RECEIVED_DETAILS = "HTTP_SERVER_RESPONSE_RECEIVED_DETAILS";
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_SEND = "HTTP_SERVER_RESPONSE_SEND";
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_SEND_DETAILS = "HTTP_SERVER_RESPONSE_SEND_DETAILS";

} // namespace http
} // namespace isc

namespace {

const char* values[] = {
    "HTTPS_REQUEST_RECEIVE_START", "start receiving request from %1",
    "HTTP_BAD_CLIENT_REQUEST_RECEIVED", "bad request received from %1: %2",
    "HTTP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS", "detailed information about bad request received from %1:\n%2",
    "HTTP_BAD_SERVER_RESPONSE_RECEIVED", "bad response received when communicating with %1: %2",
    "HTTP_BAD_SERVER_RESPONSE_RECEIVED_DETAILS", "detailed information about bad response received from %1:\n%2",
    "HTTP_CLIENT_MT_STARTED", "HttpClient has been started in multi-threaded mode running %1 threads",
    "HTTP_CLIENT_QUEUE_SIZE_GROWING", "queue for URL: %1, now has %2 entries and may be growing too quickly",
    "HTTP_CLIENT_REQUEST_RECEIVED", "received HTTP request from %1",
    "HTTP_CLIENT_REQUEST_RECEIVED_DETAILS", "detailed information about well-formed request received from %1:\n%2",
    "HTTP_CLIENT_REQUEST_SEND", "sending HTTP request %1 to %2",
    "HTTP_CLIENT_REQUEST_SEND_DETAILS", "detailed information about request sent to %1:\n%2",
    "HTTP_CLIENT_REQUEST_TIMEOUT_OCCURRED", "HTTP request timeout occurred when communicating with %1",
    "HTTP_CONNECTION_CLOSE_CALLBACK_FAILED", "Connection close callback threw an exception",
    "HTTP_CONNECTION_HANDSHAKE_FAILED", "TLS handshake with %1 failed with %2",
    "HTTP_CONNECTION_HANDSHAKE_START", "start TLS handshake with %1 with timeout %2",
    "HTTP_CONNECTION_SHUTDOWN", "shutting down HTTP connection from %1",
    "HTTP_CONNECTION_SHUTDOWN_FAILED", "shutting down HTTP connection failed",
    "HTTP_CONNECTION_STOP", "stopping HTTP connection from %1",
    "HTTP_CONNECTION_STOP_FAILED", "stopping HTTP connection failed",
    "HTTP_DATA_RECEIVED", "received %1 bytes from %2",
    "HTTP_IDLE_CONNECTION_TIMEOUT_OCCURRED", "closing persistent connection with %1 as a result of a timeout",
    "HTTP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED", "premature connection timeout occurred: in transaction ? %1, transid: %2, current_transid: %3",
    "HTTP_REQUEST_RECEIVE_START", "start receiving request from %1 with timeout %2",
    "HTTP_SERVER_RESPONSE_RECEIVED", "received HTTP response from %1",
    "HTTP_SERVER_RESPONSE_RECEIVED_DETAILS", "detailed information about well-formed response received from %1:\n%2",
    "HTTP_SERVER_RESPONSE_SEND", "sending HTTP response %1 to %2",
    "HTTP_SERVER_RESPONSE_SEND_DETAILS", "detailed information about response sent to %1:\n%2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

