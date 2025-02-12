// File created from ../../../../src/hooks/dhcp/limits/limits_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace limits {

extern const isc::log::MessageID LIMITS_CONFIGURATION_LEASE_BACKEND_NOT_AVAILABLE = "LIMITS_CONFIGURATION_LEASE_BACKEND_NOT_AVAILABLE";
extern const isc::log::MessageID LIMITS_CONFIGURATION_LEASE_BACKEND_SHOULD_HAVE_BEEN_AVAILABLE = "LIMITS_CONFIGURATION_LEASE_BACKEND_SHOULD_HAVE_BEEN_AVAILABLE";
extern const isc::log::MessageID LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_CLIENT_CLASS = "LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_CLIENT_CLASS";
extern const isc::log::MessageID LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_SUBNET = "LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_SUBNET";
extern const isc::log::MessageID LIMITS_CONFIGURED_PREFIX_LIMIT_BY_CLIENT_CLASS = "LIMITS_CONFIGURED_PREFIX_LIMIT_BY_CLIENT_CLASS";
extern const isc::log::MessageID LIMITS_CONFIGURED_PREFIX_LIMIT_BY_SUBNET = "LIMITS_CONFIGURED_PREFIX_LIMIT_BY_SUBNET";
extern const isc::log::MessageID LIMITS_CONFIGURED_RATE_LIMIT_BY_CLIENT_CLASS = "LIMITS_CONFIGURED_RATE_LIMIT_BY_CLIENT_CLASS";
extern const isc::log::MessageID LIMITS_CONFIGURED_RATE_LIMIT_BY_SUBNET = "LIMITS_CONFIGURED_RATE_LIMIT_BY_SUBNET";
extern const isc::log::MessageID LIMITS_LEASE_LIMIT_EXCEEDED = "LIMITS_LEASE_LIMIT_EXCEEDED";
extern const isc::log::MessageID LIMITS_LEASE_WITHIN_LIMITS = "LIMITS_LEASE_WITHIN_LIMITS";
extern const isc::log::MessageID LIMITS_PACKET_WIIH_SUBNET_ID_RATE_NO_SUBNET = "LIMITS_PACKET_WIIH_SUBNET_ID_RATE_NO_SUBNET";
extern const isc::log::MessageID LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_DROPPED = "LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_DROPPED";
extern const isc::log::MessageID LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_HONORED = "LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_HONORED";
extern const isc::log::MessageID LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_DROPPED = "LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_DROPPED";
extern const isc::log::MessageID LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_HONORED = "LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_HONORED";

} // namespace limits
} // namespace isc

namespace {

const char* values[] = {
    "LIMITS_CONFIGURATION_LEASE_BACKEND_NOT_AVAILABLE", "Lease backend not available. Could not check JSON support in the database. Continuing without checking...",
    "LIMITS_CONFIGURATION_LEASE_BACKEND_SHOULD_HAVE_BEEN_AVAILABLE", "Lease backend not available when configuration shows it should have been. This is likely a programmatic error. Continuing...",
    "LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_CLIENT_CLASS", "New lease limit of %1 addresses for client class %2 has been configured.",
    "LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_SUBNET", "New lease limit of %1 addresses for subnet with ID %2 has been configured.",
    "LIMITS_CONFIGURED_PREFIX_LIMIT_BY_CLIENT_CLASS", "New lease limit of %1 prefixes for client class %2 has been configured.",
    "LIMITS_CONFIGURED_PREFIX_LIMIT_BY_SUBNET", "New lease limit of %1 prefixes for subnet with ID %2 has been configured.",
    "LIMITS_CONFIGURED_RATE_LIMIT_BY_CLIENT_CLASS", "New rate limit of %1 for client class %2 has been configured.",
    "LIMITS_CONFIGURED_RATE_LIMIT_BY_SUBNET", "New rate limit of %1 for subnet with ID %2 has been configured.",
    "LIMITS_LEASE_LIMIT_EXCEEDED", "Lease was not allocated due to exceeding %1.",
    "LIMITS_LEASE_WITHIN_LIMITS", "Lease with address %1 is within limits.",
    "LIMITS_PACKET_WIIH_SUBNET_ID_RATE_NO_SUBNET", "Packet is not being rate limited due to no subnet specified.",
    "LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_DROPPED", "Packet assigned to client classes %1 is being dropped for exceeding the rate limit of %2 for client class %3.",
    "LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_HONORED", "Packet assigned to client classes %1 is being honored.",
    "LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_DROPPED", "Packet assigned to subnet with ID %1 is being dropped for exceeding the rate limit of %2.",
    "LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_HONORED", "Packet under subnet with ID %1 and limit %2 is being honored.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

