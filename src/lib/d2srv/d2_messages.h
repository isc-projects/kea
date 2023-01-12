// File created from ../../../src/lib/d2srv/d2_messages.mes

#ifndef D2_MESSAGES_H
#define D2_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace d2 {

extern const isc::log::MessageID DHCP_DDNS_ADD_FAILED;
extern const isc::log::MessageID DHCP_DDNS_ADD_SUCCEEDED;
extern const isc::log::MessageID DHCP_DDNS_ALREADY_RUNNING;
extern const isc::log::MessageID DHCP_DDNS_AT_MAX_TRANSACTIONS;
extern const isc::log::MessageID DHCP_DDNS_CLEARED_FOR_SHUTDOWN;
extern const isc::log::MessageID DHCP_DDNS_COMMAND;
extern const isc::log::MessageID DHCP_DDNS_CONFIGURE;
extern const isc::log::MessageID DHCP_DDNS_CONFIGURED_CALLOUT_DROP;
extern const isc::log::MessageID DHCP_DDNS_CONFIG_CHECK_FAIL;
extern const isc::log::MessageID DHCP_DDNS_CONFIG_FAIL;
extern const isc::log::MessageID DHCP_DDNS_CONFIG_SYNTAX_WARNING;
extern const isc::log::MessageID DHCP_DDNS_FAILED;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_BAD_DNSCLIENT_STATUS;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_BUILD_FAILURE;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_REJECTED;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_RESP_CORRUPT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_TIMEOUT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_BAD_DNSCLIENT_STATUS;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_BUILD_FAILURE;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_REJECTED;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_RESP_CORRUPT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_TIMEOUT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_BAD_DNSCLIENT_STATUS;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_BUILD_FAILURE;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_REJECTED;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_TIMEOUT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_BAD_DNSCLIENT_STATUS;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_BUILD_FAILURE;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_REJECTED;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_RESP_CORRUPT;
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_TIMEOUT;
extern const isc::log::MessageID DHCP_DDNS_FWD_REQUEST_IGNORED;
extern const isc::log::MessageID DHCP_DDNS_INVALID_RESPONSE;
extern const isc::log::MessageID DHCP_DDNS_NOT_ON_LOOPBACK;
extern const isc::log::MessageID DHCP_DDNS_NO_ELIGIBLE_JOBS;
extern const isc::log::MessageID DHCP_DDNS_NO_FWD_MATCH_ERROR;
extern const isc::log::MessageID DHCP_DDNS_NO_MATCH;
extern const isc::log::MessageID DHCP_DDNS_NO_REV_MATCH_ERROR;
extern const isc::log::MessageID DHCP_DDNS_PROCESS_INIT;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_QUEUE_FULL;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_QUEUE_RECEIVE;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RECONFIGURING;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RECOVERING;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RECV_ERROR;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RESUME_ERROR;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RESUMING;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STARTED;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_START_ERROR;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STOPPED;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STOPPING;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STOP_ERROR;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_UNEXPECTED_HANDLER_ERROR;
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_UNEXPECTED_STOP;
extern const isc::log::MessageID DHCP_DDNS_REMOVE_FAILED;
extern const isc::log::MessageID DHCP_DDNS_REMOVE_SUCCEEDED;
extern const isc::log::MessageID DHCP_DDNS_REQUEST_DROPPED;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_BAD_DNSCLIENT_STATUS;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_BUILD_FAILURE;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_REJECTED;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_RESP_CORRUPT;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_TIMEOUT;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_BAD_DNSCLIENT_STATUS;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_BUILD_FAILURE;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_IO_ERROR;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_REJECTED;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_RESP_CORRUPT;
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_TIMEOUT;
extern const isc::log::MessageID DHCP_DDNS_REV_REQUEST_IGNORED;
extern const isc::log::MessageID DHCP_DDNS_RUN_EXIT;
extern const isc::log::MessageID DHCP_DDNS_SHUTDOWN_COMMAND;
extern const isc::log::MessageID DHCP_DDNS_STARTED;
extern const isc::log::MessageID DHCP_DDNS_STARTING_TRANSACTION;
extern const isc::log::MessageID DHCP_DDNS_STATE_MODEL_UNEXPECTED_ERROR;
extern const isc::log::MessageID DHCP_DDNS_TRANS_SEND_ERROR;
extern const isc::log::MessageID DHCP_DDNS_UPDATE_REQUEST_SENT;
extern const isc::log::MessageID DHCP_DDNS_UPDATE_RESPONSE_RECEIVED;

} // namespace d2
} // namespace isc

#endif // D2_MESSAGES_H
