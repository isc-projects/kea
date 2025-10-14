// File created from src/hooks/dhcp/ping_check/ping_check_messages.mes

#ifndef PING_CHECK_MESSAGES_H
#define PING_CHECK_MESSAGES_H

#include <log/message_types.h>

extern const isc::log::MessageID PING_CHECK_CB4_UPDATE_FAILED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_ECHO_REPLY_RECEIVED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_ECHO_REQUEST_SENT;
extern const isc::log::MessageID PING_CHECK_CHANNEL_MALFORMED_PACKET_RECEIVED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_NETWORK_WRITE_ERROR;
extern const isc::log::MessageID PING_CHECK_CHANNEL_NO_LEASE_OR_LEASE_REUSED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_CLOSED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_CLOSE_ERROR;
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_OPENED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_READ_FAILED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_SOCKET_WRITE_FAILED;
extern const isc::log::MessageID PING_CHECK_CHANNEL_STOP;
extern const isc::log::MessageID PING_CHECK_CHANNEL_WATCH_SOCKET_CLEAR_ERROR;
extern const isc::log::MessageID PING_CHECK_CHANNEL_WATCH_SOCKET_CLOSE_ERROR;
extern const isc::log::MessageID PING_CHECK_DHCP4_SRV_CONFIGURED_FAILED;
extern const isc::log::MessageID PING_CHECK_DUPLICATE_CHECK;
extern const isc::log::MessageID PING_CHECK_LEASE4_OFFER_FAILED;
extern const isc::log::MessageID PING_CHECK_LOAD_ERROR;
extern const isc::log::MessageID PING_CHECK_LOAD_OK;
extern const isc::log::MessageID PING_CHECK_MGR_CHANNEL_DOWN;
extern const isc::log::MessageID PING_CHECK_MGR_LEASE_FREE_TO_USE;
extern const isc::log::MessageID PING_CHECK_MGR_NEXT_ECHO_SCHEDULED;
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_ECHO_REPLY;
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_UNEXPECTED_ECHO_REPLY;
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_UNEXPECTED_UNREACHABLE_MSG;
extern const isc::log::MessageID PING_CHECK_MGR_RECEIVED_UNREACHABLE_MSG;
extern const isc::log::MessageID PING_CHECK_MGR_REPLY_RECEIVED_ERROR;
extern const isc::log::MessageID PING_CHECK_MGR_REPLY_TIMEOUT_EXPIRED;
extern const isc::log::MessageID PING_CHECK_MGR_SEND_COMPLETED_ERROR;
extern const isc::log::MessageID PING_CHECK_MGR_STARTED;
extern const isc::log::MessageID PING_CHECK_MGR_STARTED_SINGLE_THREADED;
extern const isc::log::MessageID PING_CHECK_MGR_START_PING_CHECK;
extern const isc::log::MessageID PING_CHECK_MGR_STOPPED;
extern const isc::log::MessageID PING_CHECK_MGR_STOPPING;
extern const isc::log::MessageID PING_CHECK_MGR_SUBNET_CONFIG_FAILED;
extern const isc::log::MessageID PING_CHECK_PAUSE_FAILED;
extern const isc::log::MessageID PING_CHECK_PAUSE_ILLEGAL;
extern const isc::log::MessageID PING_CHECK_PAUSE_PERMISSIONS_FAILED;
extern const isc::log::MessageID PING_CHECK_RESUME_FAILED;
extern const isc::log::MessageID PING_CHECK_UNEXPECTED_READ_ERROR;
extern const isc::log::MessageID PING_CHECK_UNEXPECTED_WRITE_ERROR;
extern const isc::log::MessageID PING_CHECK_UNLOAD;

#endif // PING_CHECK_MESSAGES_H
