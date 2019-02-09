// File created from ../../../src/lib/dhcpsrv/alloc_engine_messages.mes on Fri Feb 08 2019 20:31

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID ALLOC_ENGINE_LEASE_RECLAIMED = "ALLOC_ENGINE_LEASE_RECLAIMED";
extern const isc::log::MessageID ALLOC_ENGINE_REMOVAL_NCR_FAILED = "ALLOC_ENGINE_REMOVAL_NCR_FAILED";
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_ERROR = "ALLOC_ENGINE_V4_ALLOC_ERROR";
extern const isc::log::MessageID ALLOC_ENGINE_V4_ALLOC_FAIL = "ALLOC_ENGINE_V4_ALLOC_FAIL";
extern const isc::log::MessageID ALLOC_ENGINE_V4_DECLINED_RECOVERED = "ALLOC_ENGINE_V4_DECLINED_RECOVERED";
extern const isc::log::MessageID ALLOC_ENGINE_V4_DISCOVER_ADDRESS_CONFLICT = "ALLOC_ENGINE_V4_DISCOVER_ADDRESS_CONFLICT";
extern const isc::log::MessageID ALLOC_ENGINE_V4_DISCOVER_HR = "ALLOC_ENGINE_V4_DISCOVER_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_COMPLETE = "ALLOC_ENGINE_V4_LEASES_RECLAMATION_COMPLETE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_SLOW = "ALLOC_ENGINE_V4_LEASES_RECLAMATION_SLOW";
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_START = "ALLOC_ENGINE_V4_LEASES_RECLAMATION_START";
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASES_RECLAMATION_TIMEOUT = "ALLOC_ENGINE_V4_LEASES_RECLAMATION_TIMEOUT";
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASE_RECLAIM = "ALLOC_ENGINE_V4_LEASE_RECLAIM";
extern const isc::log::MessageID ALLOC_ENGINE_V4_LEASE_RECLAMATION_FAILED = "ALLOC_ENGINE_V4_LEASE_RECLAMATION_FAILED";
extern const isc::log::MessageID ALLOC_ENGINE_V4_NO_MORE_EXPIRED_LEASES = "ALLOC_ENGINE_V4_NO_MORE_EXPIRED_LEASES";
extern const isc::log::MessageID ALLOC_ENGINE_V4_OFFER_EXISTING_LEASE = "ALLOC_ENGINE_V4_OFFER_EXISTING_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_OFFER_NEW_LEASE = "ALLOC_ENGINE_V4_OFFER_NEW_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_OFFER_REQUESTED_LEASE = "ALLOC_ENGINE_V4_OFFER_REQUESTED_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE = "ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_COMPLETE = "ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_COMPLETE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_FAILED = "ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_FAILED";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_ADDRESS_RESERVED = "ALLOC_ENGINE_V4_REQUEST_ADDRESS_RESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_ALLOC_REQUESTED = "ALLOC_ENGINE_V4_REQUEST_ALLOC_REQUESTED";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_EXTEND_LEASE = "ALLOC_ENGINE_V4_REQUEST_EXTEND_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_INVALID = "ALLOC_ENGINE_V4_REQUEST_INVALID";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_IN_USE = "ALLOC_ENGINE_V4_REQUEST_IN_USE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_OUT_OF_POOL = "ALLOC_ENGINE_V4_REQUEST_OUT_OF_POOL";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_PICK_ADDRESS = "ALLOC_ENGINE_V4_REQUEST_PICK_ADDRESS";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_REMOVE_LEASE = "ALLOC_ENGINE_V4_REQUEST_REMOVE_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REQUEST_USE_HR = "ALLOC_ENGINE_V4_REQUEST_USE_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V4_REUSE_EXPIRED_LEASE_DATA = "ALLOC_ENGINE_V4_REUSE_EXPIRED_LEASE_DATA";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_ERROR = "ALLOC_ENGINE_V6_ALLOC_ERROR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_FAIL = "ALLOC_ENGINE_V6_ALLOC_FAIL";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_HR_LEASE_EXISTS = "ALLOC_ENGINE_V6_ALLOC_HR_LEASE_EXISTS";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_LEASES_HR = "ALLOC_ENGINE_V6_ALLOC_LEASES_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_LEASES_NO_HR = "ALLOC_ENGINE_V6_ALLOC_LEASES_NO_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_NO_LEASES_HR = "ALLOC_ENGINE_V6_ALLOC_NO_LEASES_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_NO_V6_HR = "ALLOC_ENGINE_V6_ALLOC_NO_V6_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_ALLOC_UNRESERVED = "ALLOC_ENGINE_V6_ALLOC_UNRESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_DECLINED_RECOVERED = "ALLOC_ENGINE_V6_DECLINED_RECOVERED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXPIRED_HINT_RESERVED = "ALLOC_ENGINE_V6_EXPIRED_HINT_RESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_ALLOC_UNRESERVED = "ALLOC_ENGINE_V6_EXTEND_ALLOC_UNRESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_ERROR = "ALLOC_ENGINE_V6_EXTEND_ERROR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_LEASE = "ALLOC_ENGINE_V6_EXTEND_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_LEASE_DATA = "ALLOC_ENGINE_V6_EXTEND_LEASE_DATA";
extern const isc::log::MessageID ALLOC_ENGINE_V6_EXTEND_NEW_LEASE_DATA = "ALLOC_ENGINE_V6_EXTEND_NEW_LEASE_DATA";
extern const isc::log::MessageID ALLOC_ENGINE_V6_HINT_RESERVED = "ALLOC_ENGINE_V6_HINT_RESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_HR_ADDR_GRANTED = "ALLOC_ENGINE_V6_HR_ADDR_GRANTED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_HR_PREFIX_GRANTED = "ALLOC_ENGINE_V6_HR_PREFIX_GRANTED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_COMPLETE = "ALLOC_ENGINE_V6_LEASES_RECLAMATION_COMPLETE";
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_SLOW = "ALLOC_ENGINE_V6_LEASES_RECLAMATION_SLOW";
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_START = "ALLOC_ENGINE_V6_LEASES_RECLAMATION_START";
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASES_RECLAMATION_TIMEOUT = "ALLOC_ENGINE_V6_LEASES_RECLAMATION_TIMEOUT";
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASE_RECLAIM = "ALLOC_ENGINE_V6_LEASE_RECLAIM";
extern const isc::log::MessageID ALLOC_ENGINE_V6_LEASE_RECLAMATION_FAILED = "ALLOC_ENGINE_V6_LEASE_RECLAMATION_FAILED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_NO_MORE_EXPIRED_LEASES = "ALLOC_ENGINE_V6_NO_MORE_EXPIRED_LEASES";
extern const isc::log::MessageID ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE = "ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE";
extern const isc::log::MessageID ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_COMPLETE = "ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_COMPLETE";
extern const isc::log::MessageID ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_FAILED = "ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_FAILED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_RENEW_HR = "ALLOC_ENGINE_V6_RENEW_HR";
extern const isc::log::MessageID ALLOC_ENGINE_V6_RENEW_REMOVE_RESERVED = "ALLOC_ENGINE_V6_RENEW_REMOVE_RESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_RENEW_REMOVE_UNRESERVED = "ALLOC_ENGINE_V6_RENEW_REMOVE_UNRESERVED";
extern const isc::log::MessageID ALLOC_ENGINE_V6_REUSE_EXPIRED_LEASE_DATA = "ALLOC_ENGINE_V6_REUSE_EXPIRED_LEASE_DATA";
extern const isc::log::MessageID ALLOC_ENGINE_V6_REVOKED_ADDR_LEASE = "ALLOC_ENGINE_V6_REVOKED_ADDR_LEASE";
extern const isc::log::MessageID ALLOC_ENGINE_V6_REVOKED_PREFIX_LEASE = "ALLOC_ENGINE_V6_REVOKED_PREFIX_LEASE";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "ALLOC_ENGINE_LEASE_RECLAIMED", "successfully reclaimed lease %1",
    "ALLOC_ENGINE_REMOVAL_NCR_FAILED", "sending removal name change request failed for lease %1: %2",
    "ALLOC_ENGINE_V4_ALLOC_ERROR", "%1: error during attempt to allocate an IPv4 address: %2",
    "ALLOC_ENGINE_V4_ALLOC_FAIL", "%1: failed to allocate an IPv4 address after %2 attempt(s)",
    "ALLOC_ENGINE_V4_DECLINED_RECOVERED", "IPv4 address %1 was recovered after %2 seconds of probation-period",
    "ALLOC_ENGINE_V4_DISCOVER_ADDRESS_CONFLICT", "%1: conflicting reservation for address %2 with existing lease %3",
    "ALLOC_ENGINE_V4_DISCOVER_HR", "client %1 sending DHCPDISCOVER has reservation for the address %2",
    "ALLOC_ENGINE_V4_LEASES_RECLAMATION_COMPLETE", "reclaimed %1 leases in %2",
    "ALLOC_ENGINE_V4_LEASES_RECLAMATION_SLOW", "expired leases still exist after %1 reclamations",
    "ALLOC_ENGINE_V4_LEASES_RECLAMATION_START", "starting reclamation of expired leases (limit = %1 leases or %2 milliseconds)",
    "ALLOC_ENGINE_V4_LEASES_RECLAMATION_TIMEOUT", "timeout of %1 ms reached while reclaiming IPv4 leases",
    "ALLOC_ENGINE_V4_LEASE_RECLAIM", "%1: reclaiming expired lease for address %2",
    "ALLOC_ENGINE_V4_LEASE_RECLAMATION_FAILED", "failed to reclaim the lease %1: %2",
    "ALLOC_ENGINE_V4_NO_MORE_EXPIRED_LEASES", "all expired leases have been reclaimed",
    "ALLOC_ENGINE_V4_OFFER_EXISTING_LEASE", "allocation engine will try to offer existing lease to the client %1",
    "ALLOC_ENGINE_V4_OFFER_NEW_LEASE", "allocation engine will try to offer new lease to the client %1",
    "ALLOC_ENGINE_V4_OFFER_REQUESTED_LEASE", "allocation engine will try to offer requested lease %1 to the client %2",
    "ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE", "begin deletion of reclaimed leases expired more than %1 seconds ago",
    "ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_COMPLETE", "successfully deleted %1 expired-reclaimed leases",
    "ALLOC_ENGINE_V4_RECLAIMED_LEASES_DELETE_FAILED", "deletion of expired-reclaimed leases failed: %1",
    "ALLOC_ENGINE_V4_REQUEST_ADDRESS_RESERVED", "%1: requested address %2 is reserved",
    "ALLOC_ENGINE_V4_REQUEST_ALLOC_REQUESTED", "%1: trying to allocate requested address %2",
    "ALLOC_ENGINE_V4_REQUEST_EXTEND_LEASE", "%1: extending lifetime of the lease for address %2",
    "ALLOC_ENGINE_V4_REQUEST_INVALID", "client %1 having a reservation for address %2 is requesting invalid address %3",
    "ALLOC_ENGINE_V4_REQUEST_IN_USE", "%1: requested address %2 is in use",
    "ALLOC_ENGINE_V4_REQUEST_OUT_OF_POOL", "client %1, which doesn't have a reservation, requested address %2 out of the dynamic pool",
    "ALLOC_ENGINE_V4_REQUEST_PICK_ADDRESS", "client %1 hasn't specified an address - picking available address from the pool",
    "ALLOC_ENGINE_V4_REQUEST_REMOVE_LEASE", "%1: removing previous client's lease %2",
    "ALLOC_ENGINE_V4_REQUEST_USE_HR", "client %1 hasn't requested specific address, using reserved address %2",
    "ALLOC_ENGINE_V4_REUSE_EXPIRED_LEASE_DATA", "%1: reusing expired lease, updated lease information: %2",
    "ALLOC_ENGINE_V6_ALLOC_ERROR", "%1: error during attempt to allocate an IPv6 address: %2",
    "ALLOC_ENGINE_V6_ALLOC_FAIL", "%1: failed to allocate an IPv6 address after %2 attempt(s)",
    "ALLOC_ENGINE_V6_ALLOC_HR_LEASE_EXISTS", "%1: lease type %2 for reserved address/prefix %3 already exists",
    "ALLOC_ENGINE_V6_ALLOC_LEASES_HR", "leases and static reservations found for client %1",
    "ALLOC_ENGINE_V6_ALLOC_LEASES_NO_HR", "no reservations found but leases exist for client %1",
    "ALLOC_ENGINE_V6_ALLOC_NO_LEASES_HR", "no leases found but reservations exist for client %1",
    "ALLOC_ENGINE_V6_ALLOC_NO_V6_HR", "%1: unable to allocate reserved leases - no IPv6 reservations",
    "ALLOC_ENGINE_V6_ALLOC_UNRESERVED", "no static reservations available - trying to dynamically allocate leases for client %1",
    "ALLOC_ENGINE_V6_DECLINED_RECOVERED", "IPv6 address %1 was recovered after %2 seconds of probation-period",
    "ALLOC_ENGINE_V6_EXPIRED_HINT_RESERVED", "%1: expired lease for the client's hint %2 is reserved for another client",
    "ALLOC_ENGINE_V6_EXTEND_ALLOC_UNRESERVED", "allocate new (unreserved) leases for the renewing client %1",
    "ALLOC_ENGINE_V6_EXTEND_ERROR", "%1: allocation engine experienced error with attempting to extend lease lifetime: %2",
    "ALLOC_ENGINE_V6_EXTEND_LEASE", "%1: extending lifetime of the lease type %2, address %3",
    "ALLOC_ENGINE_V6_EXTEND_LEASE_DATA", "%1: detailed information about the lease being extended: %2",
    "ALLOC_ENGINE_V6_EXTEND_NEW_LEASE_DATA", "%1: new lease information for the lease being extended: %2",
    "ALLOC_ENGINE_V6_HINT_RESERVED", "%1: lease for the client's hint %2 is reserved for another client",
    "ALLOC_ENGINE_V6_HR_ADDR_GRANTED", "reserved address %1 was assigned to client %2",
    "ALLOC_ENGINE_V6_HR_PREFIX_GRANTED", "reserved prefix %1/%2 was assigned to client %3",
    "ALLOC_ENGINE_V6_LEASES_RECLAMATION_COMPLETE", "reclaimed %1 leases in %2",
    "ALLOC_ENGINE_V6_LEASES_RECLAMATION_SLOW", "expired leases still exist after %1 reclamations",
    "ALLOC_ENGINE_V6_LEASES_RECLAMATION_START", "starting reclamation of expired leases (limit = %1 leases or %2 milliseconds)",
    "ALLOC_ENGINE_V6_LEASES_RECLAMATION_TIMEOUT", "timeout of %1 ms reached while reclaiming IPv6 leases",
    "ALLOC_ENGINE_V6_LEASE_RECLAIM", "%1: reclaiming expired lease for prefix %2/%3",
    "ALLOC_ENGINE_V6_LEASE_RECLAMATION_FAILED", "failed to reclaim the lease %1: %2",
    "ALLOC_ENGINE_V6_NO_MORE_EXPIRED_LEASES", "all expired leases have been reclaimed",
    "ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE", "begin deletion of reclaimed leases expired more than %1 seconds ago",
    "ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_COMPLETE", "successfully deleted %1 expired-reclaimed leases",
    "ALLOC_ENGINE_V6_RECLAIMED_LEASES_DELETE_FAILED", "deletion of expired-reclaimed leases failed: %1",
    "ALLOC_ENGINE_V6_RENEW_HR", "allocating leases reserved for the client %1 as a result of Renew",
    "ALLOC_ENGINE_V6_RENEW_REMOVE_RESERVED", "%1: checking if existing client's leases are reserved for another client",
    "ALLOC_ENGINE_V6_RENEW_REMOVE_UNRESERVED", "dynamically allocating leases for the renewing client %1",
    "ALLOC_ENGINE_V6_REUSE_EXPIRED_LEASE_DATA", "%1: reusing expired lease, updated lease information: %2",
    "ALLOC_ENGINE_V6_REVOKED_ADDR_LEASE", "address %1 was revoked from client %2 as it is reserved for client %3",
    "ALLOC_ENGINE_V6_REVOKED_PREFIX_LEASE", "Prefix %1/%2 was revoked from client %3 as it is reserved for client %4",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

