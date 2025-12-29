// File created from src/hooks/dhcp/radius/radius_messages.mes

#ifndef RADIUS_MESSAGES_H
#define RADIUS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace radius {

extern const isc::log::MessageID RADIUS_ACCESS_BUILD_FAILED;
extern const isc::log::MessageID RADIUS_ACCESS_CACHE_GET;
extern const isc::log::MessageID RADIUS_ACCESS_CACHE_INSERT;
extern const isc::log::MessageID RADIUS_ACCESS_CONFLICT;
extern const isc::log::MessageID RADIUS_ACCESS_DROP_PARKED_QUERY;
extern const isc::log::MessageID RADIUS_ACCESS_ERROR;
extern const isc::log::MessageID RADIUS_ACCESS_GET_IDENTIFIER;
extern const isc::log::MessageID RADIUS_ACCESS_GET_IDENTIFIER_FAILED;
extern const isc::log::MessageID RADIUS_ACCESS_HOST_BACKEND_ERROR;
extern const isc::log::MessageID RADIUS_ACCESS_MAX_PENDING_REQUESTS;
extern const isc::log::MessageID RADIUS_ACCESS_NO_HOST_CACHE;
extern const isc::log::MessageID RADIUS_ACCESS_ORPHAN;
extern const isc::log::MessageID RADIUS_ACCESS_RESUME_PARKED_QUERY;
extern const isc::log::MessageID RADIUS_ACCESS_SUBNET_RESELECT;
extern const isc::log::MessageID RADIUS_ACCESS_TERMINATE_ERROR;
extern const isc::log::MessageID RADIUS_ACCOUNTING_ASYNC;
extern const isc::log::MessageID RADIUS_ACCOUNTING_ASYNC_FAILED;
extern const isc::log::MessageID RADIUS_ACCOUNTING_ASYNC_SUCCEED;
extern const isc::log::MessageID RADIUS_ACCOUNTING_ERROR;
extern const isc::log::MessageID RADIUS_ACCOUNTING_HISTORY_UPDATE_FAILED;
extern const isc::log::MessageID RADIUS_ACCOUNTING_NO_HISTORY;
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS;
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS_FAILED;
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS_SUCCEED;
extern const isc::log::MessageID RADIUS_ACCOUNTING_SYNC;
extern const isc::log::MessageID RADIUS_ACCOUNTING_SYNC_FAILED;
extern const isc::log::MessageID RADIUS_ACCOUNTING_SYNC_SUCCEED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC_ACCEPTED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC_FAILED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC_REJECTED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS_FAILED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS_SUCCEED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC_ACCEPTED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC_FAILED;
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC_REJECTED;
extern const isc::log::MessageID RADIUS_BACKEND_GET4;
extern const isc::log::MessageID RADIUS_BACKEND_GET6;
extern const isc::log::MessageID RADIUS_CLEANUP_EXCEPTION;
extern const isc::log::MessageID RADIUS_CONFIGURATION_FAILED;
extern const isc::log::MessageID RADIUS_DECODE_MESSAGE;
extern const isc::log::MessageID RADIUS_DEINIT_OK;
extern const isc::log::MessageID RADIUS_ENCODE_MESSAGE;
extern const isc::log::MessageID RADIUS_EXCHANGE_FAILED;
extern const isc::log::MessageID RADIUS_EXCHANGE_OPEN_FAILED;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_BAD_RESPONSE;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_MISMATCH;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_RESPONSE;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_UNEXPECTED;
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVE_FAILED;
extern const isc::log::MessageID RADIUS_EXCHANGE_SEND_FAILED;
extern const isc::log::MessageID RADIUS_EXCHANGE_SEND_NEW;
extern const isc::log::MessageID RADIUS_EXCHANGE_SEND_RETRY;
extern const isc::log::MessageID RADIUS_EXCHANGE_SENT;
extern const isc::log::MessageID RADIUS_EXCHANGE_START;
extern const isc::log::MessageID RADIUS_EXCHANGE_SYNC_RETURN;
extern const isc::log::MessageID RADIUS_EXCHANGE_TERMINATE;
extern const isc::log::MessageID RADIUS_EXCHANGE_TIMEOUT;
extern const isc::log::MessageID RADIUS_HOOK_FAILED;
extern const isc::log::MessageID RADIUS_INIT_OK;
extern const isc::log::MessageID RADIUS_INTEGER_ATTRIBUTE_FROM_BYTES_FAILED;
extern const isc::log::MessageID RADIUS_INTEGER_ATTRIBUTE_FROM_TEXT_FAILED;
extern const isc::log::MessageID RADIUS_IPADDR_ATTRIBUTE_FROM_BYTES_FAILED;
extern const isc::log::MessageID RADIUS_IPADDR_ATTRIBUTE_FROM_TEXT_FAILED;
extern const isc::log::MessageID RADIUS_IPV6ADDR_ATTRIBUTE_FROM_BYTES_FAILED;
extern const isc::log::MessageID RADIUS_IPV6ADDR_ATTRIBUTE_FROM_TEXT_FAILED;
extern const isc::log::MessageID RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_BYTES_FAILED;
extern const isc::log::MessageID RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_TEXT_FAILED;
extern const isc::log::MessageID RADIUS_PAUSE_FAILED;
extern const isc::log::MessageID RADIUS_PAUSE_ILLEGAL;
extern const isc::log::MessageID RADIUS_PAUSE_PERMISSIONS_FAILED;
extern const isc::log::MessageID RADIUS_REPLY_MESSAGE_ATTRIBUTE;
extern const isc::log::MessageID RADIUS_RESUME_FAILED;
extern const isc::log::MessageID RADIUS_SERVER_CONFIGURED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_APPEND_FAILED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_LOADED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_LOAD_FAILED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_OPENED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_OPEN_FAILED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_STORED;
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_STORE_FAILED;
extern const isc::log::MessageID RADIUS_THREAD_POOL_STARTED;

} // namespace radius
} // namespace isc

#endif // RADIUS_MESSAGES_H
