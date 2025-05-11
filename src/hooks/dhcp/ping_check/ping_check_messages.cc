// File created from src/hooks/dhcp/ping_check/ping_check_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID PING_CHECK_CB4_UPDATE_FAILED = "PING_CHECK_CB4_UPDATE_FAILED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_ECHO_REPLY_RECEIVED = "PING_CHECK_CHANNEL_ECHO_REPLY_RECEIVED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_ECHO_REQUEST_SENT = "PING_CHECK_CHANNEL_ECHO_REQUEST_SENT";
extern const isc::log::MessageID PING_CHECK_CHANNEL_MALFORMED_PACKET_RECEIVED = "PING_CHECK_CHANNEL_MALFORMED_PACKET_RECEIVED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_NETWORK_WRITE_ERROR = "PING_CHECK_CHANNEL_NETWORK_WRITE_ERROR";
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_CLOSED = "PING_CHECK_CHANNEL_SOCKET_CLOSED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_CLOSE_ERROR = "PING_CHECK_CHANNEL_SOCKET_CLOSE_ERROR";
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_OPENED = "PING_CHECK_CHANNEL_SOCKET_OPENED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_READ_FAILED = "PING_CHECK_CHANNEL_SOCKET_READ_FAILED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_WRITE_FAILED = "PING_CHECK_CHANNEL_SOCKET_WRITE_FAILED";
extern const isc::log::MessageID PING_CHECK_CHANNEL_STOP = "PING_CHECK_CHANNEL_STOP";
extern const isc::log::MessageID PING_CHECK_CHANNEL_WATCH_SOCKET_CLEAR_ERROR = "PING_CHECK_CHANNEL_WATCH_SOCKET_CLEAR_ERROR";
extern const isc::log::MessageID PING_CHECK_CHANNEL_WATCH_SOCKET_CLOSE_ERROR = "PING_CHECK_CHANNEL_WATCH_SOCKET_CLOSE_ERROR";
extern const isc::log::MessageID PING_CHECK_DHCP4_SRV_CONFIGURED_FAILED = "PING_CHECK_DHCP4_SRV_CONFIGURED_FAILED";
extern const isc::log::MessageID PING_CHECK_DUPLICATE_CHECK = "PING_CHECK_DUPLICATE_CHECK";
extern const isc::log::MessageID PING_CHECK_LEASE4_OFFER_FAILED = "PING_CHECK_LEASE4_OFFER_FAILED";
extern const isc::log::MessageID PING_CHECK_LOAD_ERROR = "PING_CHECK_LOAD_ERROR";
extern const isc::log::MessageID PING_CHECK_LOAD_OK = "PING_CHECK_LOAD_OK";
extern const isc::log::MessageID PING_CHECK_MGR_CHANNEL_DOWN = "PING_CHECK_MGR_CHANNEL_DOWN";
extern const isc::log::MessageID PING_CHECK_MGR_LEASE_FREE_TO_USE = "PING_CHECK_MGR_LEASE_FREE_TO_USE";
extern const isc::log::MessageID PING_CHECK_MGR_NEXT_ECHO_SCHEDULED = "PING_CHECK_MGR_NEXT_ECHO_SCHEDULED";
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_ECHO_REPLY = "PING_CHECK_MGR_RECEIVED_ECHO_REPLY";
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_UNEXPECTED_ECHO_REPLY = "PING_CHECK_MGR_RECEIVED_UNEXPECTED_ECHO_REPLY";
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_UNEXPECTED_UNREACHABLE_MSG = "PING_CHECK_MGR_RECEIVED_UNEXPECTED_UNREACHABLE_MSG";
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_UNREACHABLE_MSG = "PING_CHECK_MGR_RECEIVED_UNREACHABLE_MSG";
extern const isc::log::MessageID PING_CHECK_MGR_REPLY_RECEIVED_ERROR = "PING_CHECK_MGR_REPLY_RECEIVED_ERROR";
extern const isc::log::MessageID PING_CHECK_MGR_REPLY_TIMEOUT_EXPIRED = "PING_CHECK_MGR_REPLY_TIMEOUT_EXPIRED";
extern const isc::log::MessageID PING_CHECK_MGR_SEND_COMPLETED_ERROR = "PING_CHECK_MGR_SEND_COMPLETED_ERROR";
extern const isc::log::MessageID PING_CHECK_MGR_STARTED = "PING_CHECK_MGR_STARTED";
extern const isc::log::MessageID PING_CHECK_MGR_STARTED_SINGLE_THREADED = "PING_CHECK_MGR_STARTED_SINGLE_THREADED";
extern const isc::log::MessageID PING_CHECK_MGR_START_PING_CHECK = "PING_CHECK_MGR_START_PING_CHECK";
extern const isc::log::MessageID PING_CHECK_MGR_STOPPED = "PING_CHECK_MGR_STOPPED";
extern const isc::log::MessageID PING_CHECK_MGR_STOPPING = "PING_CHECK_MGR_STOPPING";
extern const isc::log::MessageID PING_CHECK_MGR_SUBNET_CONFIG_FAILED = "PING_CHECK_MGR_SUBNET_CONFIG_FAILED";
extern const isc::log::MessageID PING_CHECK_PAUSE_FAILED = "PING_CHECK_PAUSE_FAILED";
extern const isc::log::MessageID PING_CHECK_PAUSE_ILLEGAL = "PING_CHECK_PAUSE_ILLEGAL";
extern const isc::log::MessageID PING_CHECK_PAUSE_PERMISSIONS_FAILED = "PING_CHECK_PAUSE_PERMISSIONS_FAILED";
extern const isc::log::MessageID PING_CHECK_RESUME_FAILED = "PING_CHECK_RESUME_FAILED";
extern const isc::log::MessageID PING_CHECK_UNEXPECTED_READ_ERROR = "PING_CHECK_UNEXPECTED_READ_ERROR";
extern const isc::log::MessageID PING_CHECK_UNEXPECTED_WRITE_ERROR = "PING_CHECK_UNEXPECTED_WRITE_ERROR";
extern const isc::log::MessageID PING_CHECK_UNLOAD = "PING_CHECK_UNLOAD";

namespace {

const char* values[] = {
    "PING_CHECK_CB4_UPDATE_FAILED", "A subnet ping-check parameters failed to parse after being updated %1",
    "PING_CHECK_CHANNEL_ECHO_REPLY_RECEIVED", "from address %1, id %2, sequence %3",
    "PING_CHECK_CHANNEL_ECHO_REQUEST_SENT", "to address %1, id %2, sequence %3",
    "PING_CHECK_CHANNEL_MALFORMED_PACKET_RECEIVED", "error occurred unpacking message %1, discarding it",
    "PING_CHECK_CHANNEL_NETWORK_WRITE_ERROR", "occurred trying to ping %1, error %2",
    "PING_CHECK_CHANNEL_SOCKET_CLOSED", "ICMP socket has been closed.",
    "PING_CHECK_CHANNEL_SOCKET_CLOSE_ERROR", "an attempt to close the ICMP socket failed %1",
    "PING_CHECK_CHANNEL_SOCKET_OPENED", "ICMP socket been opened successfully.",
    "PING_CHECK_CHANNEL_SOCKET_READ_FAILED", "socket read completed with an error %1",
    "PING_CHECK_CHANNEL_SOCKET_WRITE_FAILED", "socket write completed with an error %1",
    "PING_CHECK_CHANNEL_STOP", "channel is stopping operations.",
    "PING_CHECK_CHANNEL_WATCH_SOCKET_CLEAR_ERROR", "an attempt to clear the WatchSocket associated with",
    "PING_CHECK_CHANNEL_WATCH_SOCKET_CLOSE_ERROR", "an attempt to close the WatchSocket associated with",
    "PING_CHECK_DHCP4_SRV_CONFIGURED_FAILED", "dhcp4_srv_configured callout failed %1",
    "PING_CHECK_DUPLICATE_CHECK", "Ping check already in progress for %1, initiated by %2",
    "PING_CHECK_LEASE4_OFFER_FAILED", "lease4_offer callout failed for query %1, lease address %2, reason %3",
    "PING_CHECK_LOAD_ERROR", "loading Ping Check hooks library failed %1",
    "PING_CHECK_LOAD_OK", "Ping Check hooks library loaded successfully.",
    "PING_CHECK_MGR_CHANNEL_DOWN", "Ping Channel has shutdown, ping checking will be skipped",
    "PING_CHECK_MGR_LEASE_FREE_TO_USE", "address %1 is free to use for %2",
    "PING_CHECK_MGR_NEXT_ECHO_SCHEDULED", "for %1, scheduling ECHO_REQUEST %2 of %3",
    "PING_CHECK_MGR_RECEIVED_ECHO_REPLY", "from %1, id %2, sequence %3",
    "PING_CHECK_MGR_RECEIVED_UNEXPECTED_ECHO_REPLY", "from %1, id %2, sequence %3 received after reply-timeout expired",
    "PING_CHECK_MGR_RECEIVED_UNEXPECTED_UNREACHABLE_MSG", "for %1, id %2, sequence %3 received after reply-timeout expired",
    "PING_CHECK_MGR_RECEIVED_UNREACHABLE_MSG", "for %1, id %2, sequence %3",
    "PING_CHECK_MGR_REPLY_RECEIVED_ERROR", "an error occurred processing an ICMP reply message %1",
    "PING_CHECK_MGR_REPLY_TIMEOUT_EXPIRED", "for %1, ECHO REQUEST %2 of %3, reply-timeout %4",
    "PING_CHECK_MGR_SEND_COMPLETED_ERROR", "an error occurred in the send completion callback %1",
    "PING_CHECK_MGR_STARTED", "ping channel operations are running, number of threads %1",
    "PING_CHECK_MGR_STARTED_SINGLE_THREADED", "single-threaded ping channel operations are running",
    "PING_CHECK_MGR_START_PING_CHECK", "for %1, initiated by %2",
    "PING_CHECK_MGR_STOPPED", "channel operations have stopped",
    "PING_CHECK_MGR_STOPPING", "ping channel operations are stopping",
    "PING_CHECK_MGR_SUBNET_CONFIG_FAILED", "user-context for subnet id %1, contains invalid ping-check %2",
    "PING_CHECK_PAUSE_FAILED", "Pausing ping channel operations failed %1",
    "PING_CHECK_PAUSE_ILLEGAL", "Pausing ping channel operations not allowed %1",
    "PING_CHECK_PAUSE_PERMISSIONS_FAILED", "Permissions check for ping-channel pause failed %1",
    "PING_CHECK_RESUME_FAILED", "Resuming ping channel operations failed %1",
    "PING_CHECK_UNEXPECTED_READ_ERROR", "could not start next socket read %1",
    "PING_CHECK_UNEXPECTED_WRITE_ERROR", "could not start next socket write %1",
    "PING_CHECK_UNLOAD", "Ping Check hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

