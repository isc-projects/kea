// File created from ../../../../src/hooks/dhcp/lease_query/lease_query_messages.mes

#ifndef LEASE_QUERY_MESSAGES_H
#define LEASE_QUERY_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace lease_query {

extern const isc::log::MessageID BULK_LEASE_QUERY4_UNSUPPORTED_MSG_TYPE;
extern const isc::log::MessageID BULK_LEASE_QUERY6_UNSUPPORTED_MSG_TYPE;
extern const isc::log::MessageID BULK_LEASE_QUERY_AT_MAX_CONCURRENT_QUERIES;
extern const isc::log::MessageID BULK_LEASE_QUERY_DEQUEUED;
extern const isc::log::MessageID BULK_LEASE_QUERY_DUPLICATE_XID;
extern const isc::log::MessageID BULK_LEASE_QUERY_EMPTY_REQUEST;
extern const isc::log::MessageID BULK_LEASE_QUERY_INVALID_REQUEST;
extern const isc::log::MessageID BULK_LEASE_QUERY_LISTENER_START_FAILED;
extern const isc::log::MessageID BULK_LEASE_QUERY_PAUSE_CHECK_PERMISSIONS_FAILED;
extern const isc::log::MessageID BULK_LEASE_QUERY_PAUSE_LISTENER_FAILED;
extern const isc::log::MessageID BULK_LEASE_QUERY_PAUSE_LISTENER_ILLEGAL;
extern const isc::log::MessageID BULK_LEASE_QUERY_PROCESSING_UNEXPECTED_FAILURE;
extern const isc::log::MessageID BULK_LEASE_QUERY_QUERY_RECEIVED;
extern const isc::log::MessageID BULK_LEASE_QUERY_REJECTED_CONNECTION;
extern const isc::log::MessageID BULK_LEASE_QUERY_RESPONSE_SEND_ERROR;
extern const isc::log::MessageID BULK_LEASE_QUERY_RESPONSE_SENT;
extern const isc::log::MessageID BULK_LEASE_QUERY_RESUME_LISTENER_FAILED;
extern const isc::log::MessageID BULK_LEASE_QUERY_UNPACK_ERROR;
extern const isc::log::MessageID DHCP4_LEASE_QUERY_PACKET_PACK_FAILED;
extern const isc::log::MessageID DHCP4_LEASE_QUERY_PACKET_UNPACK_FAILED;
extern const isc::log::MessageID DHCP4_LEASE_QUERY_PROCESS_FAILED;
extern const isc::log::MessageID DHCP4_LEASE_QUERY_RECEIVED;
extern const isc::log::MessageID DHCP4_LEASE_QUERY_RESPONSE_SENT;
extern const isc::log::MessageID DHCP4_LEASE_QUERY_SEND_FAILED;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_ERROR_GETTING_RELAY_INFO;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PACKET_PACK;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PACKET_PACK_FAILED;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PACKET_UNPACK_FAILED;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PREFIX_LENGTH_LIST;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_PROCESS_FAILED;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_RECEIVED;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_REPLY_SEND_FAILED;
extern const isc::log::MessageID DHCP6_LEASE_QUERY_REPLY_SENT;
extern const isc::log::MessageID LEASE_QUERY_LOAD_FAILED;
extern const isc::log::MessageID LEASE_QUERY_LOAD_OK;
extern const isc::log::MessageID LEASE_QUERY_UNLOAD_OK;

} // namespace lease_query
} // namespace isc

#endif // LEASE_QUERY_MESSAGES_H
