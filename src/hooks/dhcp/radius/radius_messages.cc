// File created from src/hooks/dhcp/radius/radius_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace radius {

extern const isc::log::MessageID RADIUS_ACCESS_BUILD_FAILED = "RADIUS_ACCESS_BUILD_FAILED";
extern const isc::log::MessageID RADIUS_ACCESS_CACHE_GET = "RADIUS_ACCESS_CACHE_GET";
extern const isc::log::MessageID RADIUS_ACCESS_CACHE_INSERT = "RADIUS_ACCESS_CACHE_INSERT";
extern const isc::log::MessageID RADIUS_ACCESS_CONFLICT = "RADIUS_ACCESS_CONFLICT";
extern const isc::log::MessageID RADIUS_ACCESS_DROP_PARKED_QUERY = "RADIUS_ACCESS_DROP_PARKED_QUERY";
extern const isc::log::MessageID RADIUS_ACCESS_ERROR = "RADIUS_ACCESS_ERROR";
extern const isc::log::MessageID RADIUS_ACCESS_GET_IDENTIFIER = "RADIUS_ACCESS_GET_IDENTIFIER";
extern const isc::log::MessageID RADIUS_ACCESS_GET_IDENTIFIER_FAILED = "RADIUS_ACCESS_GET_IDENTIFIER_FAILED";
extern const isc::log::MessageID RADIUS_ACCESS_HOST_BACKEND_ERROR = "RADIUS_ACCESS_HOST_BACKEND_ERROR";
extern const isc::log::MessageID RADIUS_ACCESS_MAX_PENDING_REQUESTS = "RADIUS_ACCESS_MAX_PENDING_REQUESTS";
extern const isc::log::MessageID RADIUS_ACCESS_NO_HOST_CACHE = "RADIUS_ACCESS_NO_HOST_CACHE";
extern const isc::log::MessageID RADIUS_ACCESS_ORPHAN = "RADIUS_ACCESS_ORPHAN";
extern const isc::log::MessageID RADIUS_ACCESS_RESUME_PARKED_QUERY = "RADIUS_ACCESS_RESUME_PARKED_QUERY";
extern const isc::log::MessageID RADIUS_ACCESS_SUBNET_RESELECT = "RADIUS_ACCESS_SUBNET_RESELECT";
extern const isc::log::MessageID RADIUS_ACCESS_TERMINATE_ERROR = "RADIUS_ACCESS_TERMINATE_ERROR";
extern const isc::log::MessageID RADIUS_ACCOUNTING_ASYNC = "RADIUS_ACCOUNTING_ASYNC";
extern const isc::log::MessageID RADIUS_ACCOUNTING_ASYNC_FAILED = "RADIUS_ACCOUNTING_ASYNC_FAILED";
extern const isc::log::MessageID RADIUS_ACCOUNTING_ASYNC_SUCCEED = "RADIUS_ACCOUNTING_ASYNC_SUCCEED";
extern const isc::log::MessageID RADIUS_ACCOUNTING_ERROR = "RADIUS_ACCOUNTING_ERROR";
extern const isc::log::MessageID RADIUS_ACCOUNTING_HISTORY_UPDATE_FAILED = "RADIUS_ACCOUNTING_HISTORY_UPDATE_FAILED";
extern const isc::log::MessageID RADIUS_ACCOUNTING_NO_HISTORY = "RADIUS_ACCOUNTING_NO_HISTORY";
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS = "RADIUS_ACCOUNTING_STATUS";
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS_ERROR = "RADIUS_ACCOUNTING_STATUS_ERROR";
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS_FAILED = "RADIUS_ACCOUNTING_STATUS_FAILED";
extern const isc::log::MessageID RADIUS_ACCOUNTING_STATUS_SUCCEED = "RADIUS_ACCOUNTING_STATUS_SUCCEED";
extern const isc::log::MessageID RADIUS_ACCOUNTING_SYNC = "RADIUS_ACCOUNTING_SYNC";
extern const isc::log::MessageID RADIUS_ACCOUNTING_SYNC_FAILED = "RADIUS_ACCOUNTING_SYNC_FAILED";
extern const isc::log::MessageID RADIUS_ACCOUNTING_SYNC_SUCCEED = "RADIUS_ACCOUNTING_SYNC_SUCCEED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC = "RADIUS_AUTHENTICATION_ASYNC";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC_ACCEPTED = "RADIUS_AUTHENTICATION_ASYNC_ACCEPTED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC_FAILED = "RADIUS_AUTHENTICATION_ASYNC_FAILED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_ASYNC_REJECTED = "RADIUS_AUTHENTICATION_ASYNC_REJECTED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS = "RADIUS_AUTHENTICATION_STATUS";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS_ERROR = "RADIUS_AUTHENTICATION_STATUS_ERROR";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS_FAILED = "RADIUS_AUTHENTICATION_STATUS_FAILED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_STATUS_SUCCEED = "RADIUS_AUTHENTICATION_STATUS_SUCCEED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC = "RADIUS_AUTHENTICATION_SYNC";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC_ACCEPTED = "RADIUS_AUTHENTICATION_SYNC_ACCEPTED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC_FAILED = "RADIUS_AUTHENTICATION_SYNC_FAILED";
extern const isc::log::MessageID RADIUS_AUTHENTICATION_SYNC_REJECTED = "RADIUS_AUTHENTICATION_SYNC_REJECTED";
extern const isc::log::MessageID RADIUS_BACKEND_GET4 = "RADIUS_BACKEND_GET4";
extern const isc::log::MessageID RADIUS_BACKEND_GET6 = "RADIUS_BACKEND_GET6";
extern const isc::log::MessageID RADIUS_CLEANUP_EXCEPTION = "RADIUS_CLEANUP_EXCEPTION";
extern const isc::log::MessageID RADIUS_CONFIGURATION_FAILED = "RADIUS_CONFIGURATION_FAILED";
extern const isc::log::MessageID RADIUS_DECODE_MESSAGE = "RADIUS_DECODE_MESSAGE";
extern const isc::log::MessageID RADIUS_DEINIT_OK = "RADIUS_DEINIT_OK";
extern const isc::log::MessageID RADIUS_ENCODE_MESSAGE = "RADIUS_ENCODE_MESSAGE";
extern const isc::log::MessageID RADIUS_EXCHANGE_FAILED = "RADIUS_EXCHANGE_FAILED";
extern const isc::log::MessageID RADIUS_EXCHANGE_OPEN_FAILED = "RADIUS_EXCHANGE_OPEN_FAILED";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED = "RADIUS_EXCHANGE_RECEIVED";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT = "RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT = "RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE = "RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_BAD_RESPONSE = "RADIUS_EXCHANGE_RECEIVED_BAD_RESPONSE";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_MISMATCH = "RADIUS_EXCHANGE_RECEIVED_MISMATCH";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_RESPONSE = "RADIUS_EXCHANGE_RECEIVED_RESPONSE";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVED_UNEXPECTED = "RADIUS_EXCHANGE_RECEIVED_UNEXPECTED";
extern const isc::log::MessageID RADIUS_EXCHANGE_RECEIVE_FAILED = "RADIUS_EXCHANGE_RECEIVE_FAILED";
extern const isc::log::MessageID RADIUS_EXCHANGE_SEND_FAILED = "RADIUS_EXCHANGE_SEND_FAILED";
extern const isc::log::MessageID RADIUS_EXCHANGE_SEND_NEW = "RADIUS_EXCHANGE_SEND_NEW";
extern const isc::log::MessageID RADIUS_EXCHANGE_SEND_RETRY = "RADIUS_EXCHANGE_SEND_RETRY";
extern const isc::log::MessageID RADIUS_EXCHANGE_SENT = "RADIUS_EXCHANGE_SENT";
extern const isc::log::MessageID RADIUS_EXCHANGE_START = "RADIUS_EXCHANGE_START";
extern const isc::log::MessageID RADIUS_EXCHANGE_SYNC_RETURN = "RADIUS_EXCHANGE_SYNC_RETURN";
extern const isc::log::MessageID RADIUS_EXCHANGE_TERMINATE = "RADIUS_EXCHANGE_TERMINATE";
extern const isc::log::MessageID RADIUS_EXCHANGE_TIMEOUT = "RADIUS_EXCHANGE_TIMEOUT";
extern const isc::log::MessageID RADIUS_HOOK_FAILED = "RADIUS_HOOK_FAILED";
extern const isc::log::MessageID RADIUS_INIT_OK = "RADIUS_INIT_OK";
extern const isc::log::MessageID RADIUS_INTEGER_ATTRIBUTE_FROM_BYTES_FAILED = "RADIUS_INTEGER_ATTRIBUTE_FROM_BYTES_FAILED";
extern const isc::log::MessageID RADIUS_INTEGER_ATTRIBUTE_FROM_TEXT_FAILED = "RADIUS_INTEGER_ATTRIBUTE_FROM_TEXT_FAILED";
extern const isc::log::MessageID RADIUS_IPADDR_ATTRIBUTE_FROM_BYTES_FAILED = "RADIUS_IPADDR_ATTRIBUTE_FROM_BYTES_FAILED";
extern const isc::log::MessageID RADIUS_IPADDR_ATTRIBUTE_FROM_TEXT_FAILED = "RADIUS_IPADDR_ATTRIBUTE_FROM_TEXT_FAILED";
extern const isc::log::MessageID RADIUS_IPV6ADDR_ATTRIBUTE_FROM_BYTES_FAILED = "RADIUS_IPV6ADDR_ATTRIBUTE_FROM_BYTES_FAILED";
extern const isc::log::MessageID RADIUS_IPV6ADDR_ATTRIBUTE_FROM_TEXT_FAILED = "RADIUS_IPV6ADDR_ATTRIBUTE_FROM_TEXT_FAILED";
extern const isc::log::MessageID RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_BYTES_FAILED = "RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_BYTES_FAILED";
extern const isc::log::MessageID RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_TEXT_FAILED = "RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_TEXT_FAILED";
extern const isc::log::MessageID RADIUS_PAUSE_FAILED = "RADIUS_PAUSE_FAILED";
extern const isc::log::MessageID RADIUS_PAUSE_ILLEGAL = "RADIUS_PAUSE_ILLEGAL";
extern const isc::log::MessageID RADIUS_PAUSE_PERMISSIONS_FAILED = "RADIUS_PAUSE_PERMISSIONS_FAILED";
extern const isc::log::MessageID RADIUS_REPLY_MESSAGE_ATTRIBUTE = "RADIUS_REPLY_MESSAGE_ATTRIBUTE";
extern const isc::log::MessageID RADIUS_RESUME_FAILED = "RADIUS_RESUME_FAILED";
extern const isc::log::MessageID RADIUS_SERVER_CONFIGURED = "RADIUS_SERVER_CONFIGURED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_APPEND_FAILED = "RADIUS_SESSION_HISTORY_APPEND_FAILED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_LOADED = "RADIUS_SESSION_HISTORY_LOADED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_LOAD_FAILED = "RADIUS_SESSION_HISTORY_LOAD_FAILED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_OPENED = "RADIUS_SESSION_HISTORY_OPENED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_OPEN_FAILED = "RADIUS_SESSION_HISTORY_OPEN_FAILED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_STORED = "RADIUS_SESSION_HISTORY_STORED";
extern const isc::log::MessageID RADIUS_SESSION_HISTORY_STORE_FAILED = "RADIUS_SESSION_HISTORY_STORE_FAILED";
extern const isc::log::MessageID RADIUS_THREAD_POOL_STARTED = "RADIUS_THREAD_POOL_STARTED";

} // namespace radius
} // namespace isc

namespace {

const char* values[] = {
    "RADIUS_ACCESS_BUILD_FAILED", "building Access-Request failed: %1 for incoming message %2",
    "RADIUS_ACCESS_CACHE_GET", "host %1 with attributes %2 was retrieved from the cache",
    "RADIUS_ACCESS_CACHE_INSERT", "host %1 with attributes %2 was inserted into the cache",
    "RADIUS_ACCESS_CONFLICT", "query %1 triggers a conflict for %2",
    "RADIUS_ACCESS_DROP_PARKED_QUERY", "access request terminate callback decided to drop the parked query %1",
    "RADIUS_ACCESS_ERROR", "Access-Request failed with %1 (%2)",
    "RADIUS_ACCESS_GET_IDENTIFIER", "identifier %1 of type %2 and User-Name %3 were set from incoming message %4",
    "RADIUS_ACCESS_GET_IDENTIFIER_FAILED", "no identifier of type %1 can be set from incoming message %2, reason: %3",
    "RADIUS_ACCESS_HOST_BACKEND_ERROR", "Configuring access failed during host backend '%1' setup, reason: %2",
    "RADIUS_ACCESS_MAX_PENDING_REQUESTS", "query '%1' with identifier '%2' was dropped for too many pending access requests",
    "RADIUS_ACCESS_NO_HOST_CACHE", "Configuring access failed: host cache library not loaded.",
    "RADIUS_ACCESS_ORPHAN", "orphan pending access request for %1",
    "RADIUS_ACCESS_RESUME_PARKED_QUERY", "access request terminate callback resumes processing of parked query %1 in %2",
    "RADIUS_ACCESS_SUBNET_RESELECT", "subnet was reselected from 'ID %1' to 'ID %2'",
    "RADIUS_ACCESS_TERMINATE_ERROR", "access request terminate callback got an error: %1",
    "RADIUS_ACCOUNTING_ASYNC", "Asynchronous send Accounting-Request for NAS port %1 with %2",
    "RADIUS_ACCOUNTING_ASYNC_FAILED", "Asynchronous Accounting-Request failed: return code %1 (%2)",
    "RADIUS_ACCOUNTING_ASYNC_SUCCEED", "received valid Accounting-Response (asynchronously)",
    "RADIUS_ACCOUNTING_ERROR", "Accounting-Request failed for %1 on event %2 (%3) failed with %4 (%5)",
    "RADIUS_ACCOUNTING_HISTORY_UPDATE_FAILED", "failed to insert a record for %1 in the history container",
    "RADIUS_ACCOUNTING_NO_HISTORY", "failed to find the date the lease for %1 was created",
    "RADIUS_ACCOUNTING_STATUS", "send Status-Server with %1",
    "RADIUS_ACCOUNTING_STATUS_ERROR", "received error response to Status-Server: %1 (%2) with %3",
    "RADIUS_ACCOUNTING_STATUS_FAILED", "Status-Server failed: return code %1 (%2)",
    "RADIUS_ACCOUNTING_STATUS_SUCCEED", "received valid response to Status-Server",
    "RADIUS_ACCOUNTING_SYNC", "Synchronous send Accounting-Request for NAS port %1 with %2",
    "RADIUS_ACCOUNTING_SYNC_FAILED", "Synchronous Accounting-Request failed: return code %1 (%2)",
    "RADIUS_ACCOUNTING_SYNC_SUCCEED", "received valid Accounting-Response (synchronously)",
    "RADIUS_AUTHENTICATION_ASYNC", "send Access-Request for NAS port %1 with %2",
    "RADIUS_AUTHENTICATION_ASYNC_ACCEPTED", "received valid Access-Accept with %1",
    "RADIUS_AUTHENTICATION_ASYNC_FAILED", "Access-Request failed: return code %1 (%2)",
    "RADIUS_AUTHENTICATION_ASYNC_REJECTED", "received valid Access-Reject with %1",
    "RADIUS_AUTHENTICATION_STATUS", "send Status-Server with %1",
    "RADIUS_AUTHENTICATION_STATUS_ERROR", "received error response to Status-Server: %1 (%2) with %3",
    "RADIUS_AUTHENTICATION_STATUS_FAILED", "Status-Server failed: return code %1 (%2)",
    "RADIUS_AUTHENTICATION_STATUS_SUCCEED", "received valid response to Status-Server",
    "RADIUS_AUTHENTICATION_SYNC", "send Access-Request for NAS port %1 with %2",
    "RADIUS_AUTHENTICATION_SYNC_ACCEPTED", "received valid Access-Accept with %1",
    "RADIUS_AUTHENTICATION_SYNC_FAILED", "Access-Request failed: return code %1 (%2)",
    "RADIUS_AUTHENTICATION_SYNC_REJECTED", "received valid Access-Reject with %1",
    "RADIUS_BACKEND_GET4", "spurious lookup for IPv4 subnet %1 and id %2 of type %3",
    "RADIUS_BACKEND_GET6", "spurious lookup for IPv6 subnet %1 and id %2 of type %3",
    "RADIUS_CLEANUP_EXCEPTION", "Exception on RADIUS cleanup: %1",
    "RADIUS_CONFIGURATION_FAILED", "failed to configure Radius hooks library: %1",
    "RADIUS_DECODE_MESSAGE", "Decoded message '%1' (%2) id %3 length %4 with %5 attributes.",
    "RADIUS_DEINIT_OK", "unloading Radius hooks library successful",
    "RADIUS_ENCODE_MESSAGE", "Encoded message '%1' (%2) id %3 length %4 with %5 attributes.",
    "RADIUS_EXCHANGE_FAILED", "Exchange %1 failed: %2",
    "RADIUS_EXCHANGE_OPEN_FAILED", "Open socket for exchange %1 failed: %2",
    "RADIUS_EXCHANGE_RECEIVED", "Exchange %1 received %2 bytes.",
    "RADIUS_EXCHANGE_RECEIVED_ACCESS_ACCEPT", "Exchange %1 received an Access-Accept.",
    "RADIUS_EXCHANGE_RECEIVED_ACCESS_REJECT", "Exchange %1 received an Access-Reject.",
    "RADIUS_EXCHANGE_RECEIVED_ACCOUNTING_RESPONSE", "Exchange %1 received an Accounting-Response.",
    "RADIUS_EXCHANGE_RECEIVED_BAD_RESPONSE", "Exchange %1 received a bad response: %2",
    "RADIUS_EXCHANGE_RECEIVED_MISMATCH", "Exchange %1: received response with identifier %2 when %3 was expected.",
    "RADIUS_EXCHANGE_RECEIVED_RESPONSE", "Exchange %1 received response: %2",
    "RADIUS_EXCHANGE_RECEIVED_UNEXPECTED", "Exchange %1: sent %2, received unexpected %3",
    "RADIUS_EXCHANGE_RECEIVE_FAILED", "Receive for exchange %1 failed: %2",
    "RADIUS_EXCHANGE_SEND_FAILED", "Send for exchange %1 failed: %2",
    "RADIUS_EXCHANGE_SEND_NEW", "Exchange %1 sends %2 bytes to new server[%3] %4 on port %5",
    "RADIUS_EXCHANGE_SEND_RETRY", "Exchange %1 sends %2 bytes for the %3 try.",
    "RADIUS_EXCHANGE_SENT", "Exchange %1 sent %2 bytes.",
    "RADIUS_EXCHANGE_START", "Start exchange %1",
    "RADIUS_EXCHANGE_SYNC_RETURN", "Synchronous exchange %1 returns with %2",
    "RADIUS_EXCHANGE_TERMINATE", "Exchange %1 terminates with %2",
    "RADIUS_EXCHANGE_TIMEOUT", "Exchange %1 timeout",
    "RADIUS_HOOK_FAILED", "processing for hook %1 failed: %2",
    "RADIUS_INIT_OK", "loading Radius hooks library successful",
    "RADIUS_INTEGER_ATTRIBUTE_FROM_BYTES_FAILED", "Creating an integer attribute %1 '%2' failed: %3",
    "RADIUS_INTEGER_ATTRIBUTE_FROM_TEXT_FAILED", "Creating an integer attribute %1 '%2' from %3 failed.",
    "RADIUS_IPADDR_ATTRIBUTE_FROM_BYTES_FAILED", "Creating an IP address attribute %1 '%2' failed: %3",
    "RADIUS_IPADDR_ATTRIBUTE_FROM_TEXT_FAILED", "Creating an IP address attribute %1 '%2' from %3 failed.",
    "RADIUS_IPV6ADDR_ATTRIBUTE_FROM_BYTES_FAILED", "Creating an IPv6 address attribute %1 '%2' failed: %3",
    "RADIUS_IPV6ADDR_ATTRIBUTE_FROM_TEXT_FAILED", "Creating an IPv6 address attribute %1 '%2' from %3 failed.",
    "RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_BYTES_FAILED", "Creating an IPv6 prefix attribute %1 '%2' failed: %3",
    "RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_TEXT_FAILED", "Creating an IPv6 prefix attribute %1 '%2' from %3 failed.",
    "RADIUS_PAUSE_FAILED", "Pausing the RADIUS thread pool failed: %1",
    "RADIUS_PAUSE_ILLEGAL", "Pausing the RADIUS thread pool not allowed: %1",
    "RADIUS_PAUSE_PERMISSIONS_FAILED", "Checking for permissions to pause the RADIUS thread pool failed: %1",
    "RADIUS_REPLY_MESSAGE_ATTRIBUTE", "Message %1 on exchange %2 has a Reply-Message attribute with value '%3'.",
    "RADIUS_RESUME_FAILED", "Resuming ithe RADIUS thread pool failed: %1",
    "RADIUS_SERVER_CONFIGURED", "configured an %1 server: %2",
    "RADIUS_SESSION_HISTORY_APPEND_FAILED", "appending of a new record for %1 to the session history file failed: %2",
    "RADIUS_SESSION_HISTORY_LOADED", "loading of the session history file succeeded: read %1 records including %2 active records",
    "RADIUS_SESSION_HISTORY_LOAD_FAILED", "loading of the session history file",
    "RADIUS_SESSION_HISTORY_OPENED", "opening of the session history file %1 succeeded",
    "RADIUS_SESSION_HISTORY_OPEN_FAILED", "opening of the session history file %1 failed: %2",
    "RADIUS_SESSION_HISTORY_STORED", "Storing to the session history file succeeded: stored %1 records",
    "RADIUS_SESSION_HISTORY_STORE_FAILED", "Writing to the session history file %1 failed: %2 (stored %3 over %4 records)",
    "RADIUS_THREAD_POOL_STARTED", "RADIUS thread pool started with %1 threads.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

