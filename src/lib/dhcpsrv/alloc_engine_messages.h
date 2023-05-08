// File created from ../../../src/lib/dhcpsrv/alloc_engine_messages.mes

#ifndef ALLOC_ENGINE_MESSAGES_H
#define ALLOC_ENGINE_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID ALLOC_ENGINE_IGNORING_UNSUITABLE_GLOBAL_ADDRESS;
extern const isc::log::MessageID ALLOC_ENGINE_IGNORING_UNSUITABLE_GLOBAL_ADDRESS6;
extern const isc::log::MessageID ALLOC_ENGINE_LEASE_RECLAIMED;
extern const isc::log::MessageID ALLOC_ENGINE_REMOVAL_NCR_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_ERROR;
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_FAIL;
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_FAIL_CLASSES;
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_FAIL_NO_POOLS;
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_FAIL_SHARED_NETWORK;
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_FAIL_SUBNET;
extern const isc::log::MessageID ALLOC_ENGINE_V4_DECLINED_RECOVERED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_DISCOVER_ADDRESS_CONFLICT;
extern const isc::log::MessageID ALLOC_ENGINE_V4_DISCOVER_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_COMPLETE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_SLOW;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_START;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_TIMEOUT;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASE_RECLAIM;
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASE_RECLAMATION_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_NO_MORE_EXPIRED_LEASES;
extern const isc::log::MessageID ALLOC_ENGINE_V4_OFFER_EXISTING_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_OFFER_NEW_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_OFFER_REQUESTED_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_COMPLETE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_ADDRESS_RESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_ALLOC_REQUESTED;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_EXTEND_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_INVALID;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_IN_USE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_OUT_OF_POOL;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_PICK_ADDRESS;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_REMOVE_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_USE_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V4_REUSE_EXPIRED_LEASE_DATA;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_ERROR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_FAIL;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_FAIL_CLASSES;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_FAIL_NO_POOLS;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_FAIL_SHARED_NETWORK;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_FAIL_SUBNET;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_HR_LEASE_EXISTS;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_LEASES_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_LEASES_NO_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_NO_LEASES_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_NO_V6_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_UNRESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_CALCULATED_PREFERRED_LIFETIME;
extern const isc::log::MessageID ALLOC_ENGINE_V6_DECLINED_RECOVERED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXPIRED_HINT_RESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_ALLOC_UNRESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_ERROR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_LEASE_DATA;
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_NEW_LEASE_DATA;
extern const isc::log::MessageID ALLOC_ENGINE_V6_HINT_RESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_HR_ADDR_GRANTED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_HR_PREFIX_GRANTED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_COMPLETE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_SLOW;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_START;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_TIMEOUT;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASE_RECLAIM;
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASE_RECLAMATION_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_NO_MORE_EXPIRED_LEASES;
extern const isc::log::MessageID ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_COMPLETE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_FAILED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_RENEW_HR;
extern const isc::log::MessageID ALLOC_ENGINE_V6_RENEW_REMOVE_RESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_RENEW_REMOVE_UNRESERVED;
extern const isc::log::MessageID ALLOC_ENGINE_V6_REUSE_EXPIRED_LEASE_DATA;
extern const isc::log::MessageID ALLOC_ENGINE_V6_REVOKED_ADDR_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_REVOKED_PREFIX_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_REVOKED_SHARED_ADDR_LEASE;
extern const isc::log::MessageID ALLOC_ENGINE_V6_REVOKED_SHARED_PREFIX_LEASE;

} // namespace dhcp
} // namespace isc

#endif // ALLOC_ENGINE_MESSAGES_H
