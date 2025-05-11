// File created from src/hooks/dhcp/limits/limits_messages.mes

#ifndef LIMITS_MESSAGES_H
#define LIMITS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace limits {

extern const isc::log::MessageID LIMITS_CONFIGURATION_LEASE_BACKEND_NOT_AVAILABLE;
extern const isc::log::MessageID LIMITS_CONFIGURATION_LEASE_BACKEND_SHOULD_HAVE_BEEN_AVAILABLE;
extern const isc::log::MessageID LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_CLIENT_CLASS;
extern const isc::log::MessageID LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_SUBNET;
extern const isc::log::MessageID LIMITS_CONFIGURED_PREFIX_LIMIT_BY_CLIENT_CLASS;
extern const isc::log::MessageID LIMITS_CONFIGURED_PREFIX_LIMIT_BY_SUBNET;
extern const isc::log::MessageID LIMITS_CONFIGURED_RATE_LIMIT_BY_CLIENT_CLASS;
extern const isc::log::MessageID LIMITS_CONFIGURED_RATE_LIMIT_BY_SUBNET;
extern const isc::log::MessageID LIMITS_LEASE_LIMIT_EXCEEDED;
extern const isc::log::MessageID LIMITS_LEASE_WITHIN_LIMITS;
extern const isc::log::MessageID LIMITS_PACKET_WIIH_SUBNET_ID_RATE_NO_SUBNET;
extern const isc::log::MessageID LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_DROPPED;
extern const isc::log::MessageID LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_HONORED;
extern const isc::log::MessageID LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_DROPPED;
extern const isc::log::MessageID LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_HONORED;

} // namespace limits
} // namespace isc

#endif // LIMITS_MESSAGES_H
