// File created from ../../../src/lib/config/config_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace config {

extern const isc::log::MessageID COMMAND_ACCEPTOR_START = "COMMAND_ACCEPTOR_START";
extern const isc::log::MessageID COMMAND_DEREGISTERED = "COMMAND_DEREGISTERED";
extern const isc::log::MessageID COMMAND_EXTENDED_REGISTERED = "COMMAND_EXTENDED_REGISTERED";
extern const isc::log::MessageID COMMAND_HTTP_LISTENER_COMMAND_REJECTED = "COMMAND_HTTP_LISTENER_COMMAND_REJECTED";
extern const isc::log::MessageID COMMAND_HTTP_LISTENER_STARTED = "COMMAND_HTTP_LISTENER_STARTED";
extern const isc::log::MessageID COMMAND_HTTP_LISTENER_STOPPED = "COMMAND_HTTP_LISTENER_STOPPED";
extern const isc::log::MessageID COMMAND_HTTP_LISTENER_STOPPING = "COMMAND_HTTP_LISTENER_STOPPING";
extern const isc::log::MessageID COMMAND_PROCESS_ERROR1 = "COMMAND_PROCESS_ERROR1";
extern const isc::log::MessageID COMMAND_PROCESS_ERROR2 = "COMMAND_PROCESS_ERROR2";
extern const isc::log::MessageID COMMAND_RECEIVED = "COMMAND_RECEIVED";
extern const isc::log::MessageID COMMAND_REGISTERED = "COMMAND_REGISTERED";
extern const isc::log::MessageID COMMAND_RESPONSE_ERROR = "COMMAND_RESPONSE_ERROR";
extern const isc::log::MessageID COMMAND_SOCKET_ACCEPT_FAIL = "COMMAND_SOCKET_ACCEPT_FAIL";
extern const isc::log::MessageID COMMAND_SOCKET_CLOSED_BY_FOREIGN_HOST = "COMMAND_SOCKET_CLOSED_BY_FOREIGN_HOST";
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_CANCEL_FAIL = "COMMAND_SOCKET_CONNECTION_CANCEL_FAIL";
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_CLOSED = "COMMAND_SOCKET_CONNECTION_CLOSED";
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_CLOSE_FAIL = "COMMAND_SOCKET_CONNECTION_CLOSE_FAIL";
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_OPENED = "COMMAND_SOCKET_CONNECTION_OPENED";
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_SHUTDOWN_FAIL = "COMMAND_SOCKET_CONNECTION_SHUTDOWN_FAIL";
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_TIMEOUT = "COMMAND_SOCKET_CONNECTION_TIMEOUT";
extern const isc::log::MessageID COMMAND_SOCKET_READ = "COMMAND_SOCKET_READ";
extern const isc::log::MessageID COMMAND_SOCKET_READ_FAIL = "COMMAND_SOCKET_READ_FAIL";
extern const isc::log::MessageID COMMAND_SOCKET_WRITE = "COMMAND_SOCKET_WRITE";
extern const isc::log::MessageID COMMAND_SOCKET_WRITE_FAIL = "COMMAND_SOCKET_WRITE_FAIL";
extern const isc::log::MessageID COMMAND_WATCH_SOCKET_CLEAR_ERROR = "COMMAND_WATCH_SOCKET_CLEAR_ERROR";
extern const isc::log::MessageID COMMAND_WATCH_SOCKET_CLOSE_ERROR = "COMMAND_WATCH_SOCKET_CLOSE_ERROR";
extern const isc::log::MessageID COMMAND_WATCH_SOCKET_MARK_READY_ERROR = "COMMAND_WATCH_SOCKET_MARK_READY_ERROR";
extern const isc::log::MessageID HTTP_COMMAND_MGR_IGNORED_TLS_SETUP_CHANGES = "HTTP_COMMAND_MGR_IGNORED_TLS_SETUP_CHANGES";
extern const isc::log::MessageID HTTP_COMMAND_MGR_SERVICE_STARTED = "HTTP_COMMAND_MGR_SERVICE_STARTED";
extern const isc::log::MessageID HTTP_COMMAND_MGR_SERVICE_STOPPING = "HTTP_COMMAND_MGR_SERVICE_STOPPING";

} // namespace config
} // namespace isc

namespace {

const char* values[] = {
    "COMMAND_ACCEPTOR_START", "Starting to accept connections via unix domain socket bound to %1",
    "COMMAND_DEREGISTERED", "Command %1 deregistered",
    "COMMAND_EXTENDED_REGISTERED", "Command %1 registered",
    "COMMAND_HTTP_LISTENER_COMMAND_REJECTED", "Command HTTP listener rejected command '%1' from '%2'",
    "COMMAND_HTTP_LISTENER_STARTED", "Command HTTP listener started with %1 threads, listening on %2:%3, use TLS: %4",
    "COMMAND_HTTP_LISTENER_STOPPED", "Command HTTP listener for %1:%2 stopped.",
    "COMMAND_HTTP_LISTENER_STOPPING", "Stopping Command HTTP listener for %1:%2",
    "COMMAND_PROCESS_ERROR1", "Error while processing command: %1",
    "COMMAND_PROCESS_ERROR2", "Error while processing command: %1",
    "COMMAND_RECEIVED", "Received command '%1'",
    "COMMAND_REGISTERED", "Command %1 registered",
    "COMMAND_RESPONSE_ERROR", "Server failed to generate response for command: %1",
    "COMMAND_SOCKET_ACCEPT_FAIL", "Failed to accept incoming connection on command socket %1: %2",
    "COMMAND_SOCKET_CLOSED_BY_FOREIGN_HOST", "Closed command socket %1 by foreign host, %2",
    "COMMAND_SOCKET_CONNECTION_CANCEL_FAIL", "Failed to cancel read operation on socket %1: %2",
    "COMMAND_SOCKET_CONNECTION_CLOSED", "Closed socket %1 for existing command connection",
    "COMMAND_SOCKET_CONNECTION_CLOSE_FAIL", "Failed to close command connection: %1",
    "COMMAND_SOCKET_CONNECTION_OPENED", "Opened socket %1 for incoming command connection",
    "COMMAND_SOCKET_CONNECTION_SHUTDOWN_FAIL", "Encountered error %1 while trying to gracefully shutdown socket",
    "COMMAND_SOCKET_CONNECTION_TIMEOUT", "Timeout occurred for connection over socket %1",
    "COMMAND_SOCKET_READ", "Received %1 bytes over command socket %2",
    "COMMAND_SOCKET_READ_FAIL", "Encountered error %1 while reading from command socket %2",
    "COMMAND_SOCKET_WRITE", "Sent response of %1 bytes (%2 bytes left to send) over command socket %3",
    "COMMAND_SOCKET_WRITE_FAIL", "Error while writing to command socket %1 : %2",
    "COMMAND_WATCH_SOCKET_CLEAR_ERROR", "watch socket failed to clear: %1",
    "COMMAND_WATCH_SOCKET_CLOSE_ERROR", "watch socket failed to close: %1",
    "COMMAND_WATCH_SOCKET_MARK_READY_ERROR", "watch socket failed to mark ready: %1",
    "HTTP_COMMAND_MGR_IGNORED_TLS_SETUP_CHANGES", "ignore a change in TLS setup of the http control socket",
    "HTTP_COMMAND_MGR_SERVICE_STARTED", "started %1 service bound to address %2 port %3",
    "HTTP_COMMAND_MGR_SERVICE_STOPPING", "stopping %1 service %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

