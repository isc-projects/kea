// File created from ../../../../src/hooks/dhcp/lease_query/lease_query_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace lease_query {

extern const isc::log::MessageID BULK_LEASE_QUERY4_UNSUPPORTED_MSG_TYPE = "BULK_LEASE_QUERY4_UNSUPPORTED_MSG_TYPE";
extern const isc::log::MessageID BULK_LEASE_QUERY6_UNSUPPORTED_MSG_TYPE = "BULK_LEASE_QUERY6_UNSUPPORTED_MSG_TYPE";
extern const isc::log::MessageID BULK_LEASE_QUERY_AT_MAX_CONCURRENT_QUERIES = "BULK_LEASE_QUERY_AT_MAX_CONCURRENT_QUERIES";
extern const isc::log::MessageID BULK_LEASE_QUERY_DEQUEUED = "BULK_LEASE_QUERY_DEQUEUED";
extern const isc::log::MessageID BULK_LEASE_QUERY_DUPLICATE_XID = "BULK_LEASE_QUERY_DUPLICATE_XID";
extern const isc::log::MessageID BULK_LEASE_QUERY_EMPTY_REQUEST = "BULK_LEASE_QUERY_EMPTY_REQUEST";
extern const isc::log::MessageID BULK_LEASE_QUERY_INVALID_REQUEST = "BULK_LEASE_QUERY_INVALID_REQUEST";
extern const isc::log::MessageID BULK_LEASE_QUERY_LISTENER_START_FAILED = "BULK_LEASE_QUERY_LISTENER_START_FAILED";
extern const isc::log::MessageID BULK_LEASE_QUERY_PAUSE_CHECK_PERMISSIONS_FAILED = "BULK_LEASE_QUERY_PAUSE_CHECK_PERMISSIONS_FAILED";
extern const isc::log::MessageID BULK_LEASE_QUERY_PAUSE_LISTENER_FAILED = "BULK_LEASE_QUERY_PAUSE_LISTENER_FAILED";
extern const isc::log::MessageID BULK_LEASE_QUERY_PAUSE_LISTENER_ILLEGAL = "BULK_LEASE_QUERY_PAUSE_LISTENER_ILLEGAL";
extern const isc::log::MessageID BULK_LEASE_QUERY_PROCESSING_UNEXPECTED_FAILURE = "BULK_LEASE_QUERY_PROCESSING_UNEXPECTED_FAILURE";
extern const isc::log::MessageID BULK_LEASE_QUERY_QUERY_RECEIVED = "BULK_LEASE_QUERY_QUERY_RECEIVED";
extern const isc::log::MessageID BULK_LEASE_QUERY_REJECTED_CONNECTION = "BULK_LEASE_QUERY_REJECTED_CONNECTION";
extern const isc::log::MessageID BULK_LEASE_QUERY_RESPONSE_SEND_ERROR = "BULK_LEASE_QUERY_RESPONSE_SEND_ERROR";
extern const isc::log::MessageID BULK_LEASE_QUERY_RESPONSE_SENT = "BULK_LEASE_QUERY_RESPONSE_SENT";
extern const isc::log::MessageID BULK_LEASE_QUERY_RESUME_LISTENER_FAILED = "BULK_LEASE_QUERY_RESUME_LISTENER_FAILED";
extern const isc::log::MessageID BULK_LEASE_QUERY_UNPACK_ERROR = "BULK_LEASE_QUERY_UNPACK_ERROR";
extern const isc::log::MessageID DHCP4_LEASE_QUERY_PACKET_PACK_FAILED = "DHCP4_LEASE_QUERY_PACKET_PACK_FAILED";
extern const isc::log::MessageID DHCP4_LEASE_QUERY_PACKET_UNPACK_FAILED = "DHCP4_LEASE_QUERY_PACKET_UNPACK_FAILED";
extern const isc::log::MessageID DHCP4_LEASE_QUERY_PROCESS_FAILED = "DHCP4_LEASE_QUERY_PROCESS_FAILED";
extern const isc::log::MessageID DHCP4_LEASE_QUERY_RECEIVED = "DHCP4_LEASE_QUERY_RECEIVED";
extern const isc::log::MessageID DHCP4_LEASE_QUERY_RESPONSE_SENT = "DHCP4_LEASE_QUERY_RESPONSE_SENT";
extern const isc::log::MessageID DHCP4_LEASE_QUERY_SEND_FAILED = "DHCP4_LEASE_QUERY_SEND_FAILED";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_ERROR_GETTING_RELAY_INFO = "DHCP6_LEASE_QUERY_ERROR_GETTING_RELAY_INFO";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PACKET_PACK = "DHCP6_LEASE_QUERY_PACKET_PACK";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PACKET_PACK_FAILED = "DHCP6_LEASE_QUERY_PACKET_PACK_FAILED";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PACKET_UNPACK_FAILED = "DHCP6_LEASE_QUERY_PACKET_UNPACK_FAILED";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PREFIX_LENGTH_LIST = "DHCP6_LEASE_QUERY_PREFIX_LENGTH_LIST";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PROCESS_FAILED = "DHCP6_LEASE_QUERY_PROCESS_FAILED";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_RECEIVED = "DHCP6_LEASE_QUERY_RECEIVED";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_REPLY_SEND_FAILED = "DHCP6_LEASE_QUERY_REPLY_SEND_FAILED";
extern const isc::log::MessageID DHCP6_LEASE_QUERY_REPLY_SENT = "DHCP6_LEASE_QUERY_REPLY_SENT";
extern const isc::log::MessageID LEASE_QUERY_LOAD_FAILED = "LEASE_QUERY_LOAD_FAILED";
extern const isc::log::MessageID LEASE_QUERY_LOAD_OK = "LEASE_QUERY_LOAD_OK";
extern const isc::log::MessageID LEASE_QUERY_UNLOAD_OK = "LEASE_QUERY_UNLOAD_OK";

} // namespace lease_query
} // namespace isc

namespace {

const char* values[] = {
    "BULK_LEASE_QUERY4_UNSUPPORTED_MSG_TYPE", "Dropping packet with an unsupported DHCPv4 message type %1 received from: %2",
    "BULK_LEASE_QUERY6_UNSUPPORTED_MSG_TYPE", "Dropping packet with an unsupported DHCPv6 message type %1 received from: %2",
    "BULK_LEASE_QUERY_AT_MAX_CONCURRENT_QUERIES", "Queuing query from: %1, details: %2, connection already has %3 queries in progress",
    "BULK_LEASE_QUERY_DEQUEUED", "A query from %1, details: %2, dequeued.",
    "BULK_LEASE_QUERY_DUPLICATE_XID", "Dropping query from: %1, transaction id %2 is a duplicate",
    "BULK_LEASE_QUERY_EMPTY_REQUEST", "A bulk lease query packet received from %1 is empty.",
    "BULK_LEASE_QUERY_INVALID_REQUEST", "A bulk lease query packet received from %1 is invalid, query: %2, error: %3",
    "BULK_LEASE_QUERY_LISTENER_START_FAILED", "Bulk lease query listener thread pool could not be started, error %1",
    "BULK_LEASE_QUERY_PAUSE_CHECK_PERMISSIONS_FAILED", "An unexpected error occurred while checking pause permissions, error %1",
    "BULK_LEASE_QUERY_PAUSE_LISTENER_FAILED", "Listener could not be paused, error %1",
    "BULK_LEASE_QUERY_PAUSE_LISTENER_ILLEGAL", "Pausing multi-threaded processing failed: %1",
    "BULK_LEASE_QUERY_PROCESSING_UNEXPECTED_FAILURE", "A bulk lease query packet processing throws unexpected exception: %1",
    "BULK_LEASE_QUERY_QUERY_RECEIVED", "A bulk lease query packet received from %1, details: %2",
    "BULK_LEASE_QUERY_REJECTED_CONNECTION", "A new bulk lease query connection from %1 was rejected: %2",
    "BULK_LEASE_QUERY_RESPONSE_SEND_ERROR", "A bulk lease query response could not be sent to: %1, response: %2, error: %3",
    "BULK_LEASE_QUERY_RESPONSE_SENT", "A bulk lease query response sent to %1, details: %2",
    "BULK_LEASE_QUERY_RESUME_LISTENER_FAILED", "Listener could not be resumed, error %1",
    "BULK_LEASE_QUERY_UNPACK_ERROR", "A bulk lease query packet received from %1, could not be unpacked, error: %2",
    "DHCP4_LEASE_QUERY_PACKET_PACK_FAILED", "preparing on-wire-format of the packet to be sent: %1, failed %2",
    "DHCP4_LEASE_QUERY_PACKET_UNPACK_FAILED", "failed to parse query from %1 to %2, received over interface %3, reason: %4",
    "DHCP4_LEASE_QUERY_PROCESS_FAILED", "processing failed for lease query: %1, reason: %2",
    "DHCP4_LEASE_QUERY_RECEIVED", "received query: %1",
    "DHCP4_LEASE_QUERY_RESPONSE_SENT", "response: %1, sent to %2:%3",
    "DHCP4_LEASE_QUERY_SEND_FAILED", "unable to send response: %1, iface: %2, address %3:%4 error: %5",
    "DHCP6_LEASE_QUERY_ERROR_GETTING_RELAY_INFO", "failed to get relay information for lease: %1, reason: %2",
    "DHCP6_LEASE_QUERY_PACKET_PACK", "%1: preparing on-wire format of the packet to be sent",
    "DHCP6_LEASE_QUERY_PACKET_PACK_FAILED", "%1: preparing on-wire-format of the packet to be sent failed %2",
    "DHCP6_LEASE_QUERY_PACKET_UNPACK_FAILED", "failed to parse query from %1 to %2, received over interface %3, reason: %4",
    "DHCP6_LEASE_QUERY_PREFIX_LENGTH_LIST", "the list of prefix lengths to use when searching will be: %1",
    "DHCP6_LEASE_QUERY_PROCESS_FAILED", "processing failed for lease query: %1, reason: %2",
    "DHCP6_LEASE_QUERY_RECEIVED", "received query: %1",
    "DHCP6_LEASE_QUERY_REPLY_SEND_FAILED", "unable to send response: %1, iface: %2, address %3:%4 error: %5",
    "DHCP6_LEASE_QUERY_REPLY_SENT", "response: %1, sent to %2:%3",
    "LEASE_QUERY_LOAD_FAILED", "Lease Query hooks library failed to load: %1",
    "LEASE_QUERY_LOAD_OK", "Lease Query hooks library loaded successfully.",
    "LEASE_QUERY_UNLOAD_OK", "Lease Query hooks library unloaded successfully.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

