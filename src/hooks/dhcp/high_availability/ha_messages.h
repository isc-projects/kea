// File created from ../../../../src/hooks/dhcp/high_availability/ha_messages.mes on Fri Feb 08 2019 20:34

#ifndef HA_MESSAGES_H
#define HA_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace ha {

extern const isc::log::MessageID HA_BUFFER4_RECEIVE_FAILED;
extern const isc::log::MessageID HA_BUFFER4_RECEIVE_NOT_FOR_US;
extern const isc::log::MessageID HA_BUFFER4_RECEIVE_PACKET_OPTIONS_SKIPPED;
extern const isc::log::MessageID HA_BUFFER4_RECEIVE_UNPACK_FAILED;
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_FAILED;
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_NOT_FOR_US;
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_PACKET_OPTIONS_SKIPPED;
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_UNPACK_FAILED;
extern const isc::log::MessageID HA_COMMAND_PROCESSED_FAILED;
extern const isc::log::MessageID HA_CONFIGURATION_FAILED;
extern const isc::log::MessageID HA_CONFIGURATION_SUCCESSFUL;
extern const isc::log::MessageID HA_CONFIG_AUTO_FAILOVER_DISABLED;
extern const isc::log::MessageID HA_CONFIG_LEASE_SYNCING_DISABLED;
extern const isc::log::MessageID HA_CONFIG_LEASE_SYNCING_DISABLED_REMINDER;
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_AND_SYNCING_DIFFER;
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_DISABLED;
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_DISABLED_REMINDER;
extern const isc::log::MessageID HA_CONTINUE_HANDLER_FAILED;
extern const isc::log::MessageID HA_DEINIT_OK;
extern const isc::log::MessageID HA_DHCP4_START_SERVICE_FAILED;
extern const isc::log::MessageID HA_DHCP6_START_SERVICE_FAILED;
extern const isc::log::MessageID HA_DHCP_DISABLE_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_DHCP_DISABLE_FAILED;
extern const isc::log::MessageID HA_DHCP_ENABLE_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_DHCP_ENABLE_FAILED;
extern const isc::log::MessageID HA_HEARTBEAT_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_HEARTBEAT_FAILED;
extern const isc::log::MessageID HA_HEARTBEAT_HANDLER_FAILED;
extern const isc::log::MessageID HA_HIGH_CLOCK_SKEW;
extern const isc::log::MessageID HA_HIGH_CLOCK_SKEW_CAUSES_TERMINATION;
extern const isc::log::MessageID HA_INIT_OK;
extern const isc::log::MessageID HA_LEASES4_COMMITTED_FAILED;
extern const isc::log::MessageID HA_LEASES4_COMMITTED_NOTHING_TO_UPDATE;
extern const isc::log::MessageID HA_LEASES6_COMMITTED_FAILED;
extern const isc::log::MessageID HA_LEASES6_COMMITTED_NOTHING_TO_UPDATE;
extern const isc::log::MessageID HA_LEASES_SYNC_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_LEASES_SYNC_FAILED;
extern const isc::log::MessageID HA_LEASES_SYNC_LEASE_PAGE_RECEIVED;
extern const isc::log::MessageID HA_LEASE_SYNC_FAILED;
extern const isc::log::MessageID HA_LEASE_SYNC_STALE_LEASE4_SKIP;
extern const isc::log::MessageID HA_LEASE_SYNC_STALE_LEASE6_SKIP;
extern const isc::log::MessageID HA_LEASE_UPDATES_DISABLED;
extern const isc::log::MessageID HA_LEASE_UPDATES_ENABLED;
extern const isc::log::MessageID HA_LEASE_UPDATE_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_LEASE_UPDATE_FAILED;
extern const isc::log::MessageID HA_LOAD_BALANCING_DUID_MISSING;
extern const isc::log::MessageID HA_LOAD_BALANCING_IDENTIFIER_MISSING;
extern const isc::log::MessageID HA_LOCAL_DHCP_DISABLE;
extern const isc::log::MessageID HA_LOCAL_DHCP_ENABLE;
extern const isc::log::MessageID HA_MISSING_CONFIGURATION;
extern const isc::log::MessageID HA_SCOPES_HANDLER_FAILED;
extern const isc::log::MessageID HA_SERVICE_STARTED;
extern const isc::log::MessageID HA_STATE_MACHINE_CONTINUED;
extern const isc::log::MessageID HA_STATE_MACHINE_PAUSED;
extern const isc::log::MessageID HA_STATE_TRANSITION;
extern const isc::log::MessageID HA_SYNC_FAILED;
extern const isc::log::MessageID HA_SYNC_HANDLER_FAILED;
extern const isc::log::MessageID HA_SYNC_START;
extern const isc::log::MessageID HA_SYNC_SUCCESSFUL;
extern const isc::log::MessageID HA_TERMINATED;

} // namespace ha
} // namespace isc

#endif // HA_MESSAGES_H
