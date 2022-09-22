// File created from ../../../../src/hooks/dhcp/high_availability/ha_messages.mes

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
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED;
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT4;
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT4_UNACKED;
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT6;
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT6_UNACKED;
extern const isc::log::MessageID HA_CONFIGURATION_FAILED;
extern const isc::log::MessageID HA_CONFIGURATION_SUCCESSFUL;
extern const isc::log::MessageID HA_CONFIG_AUTO_FAILOVER_DISABLED;
extern const isc::log::MessageID HA_CONFIG_DHCP_MT_DISABLED;
extern const isc::log::MessageID HA_CONFIG_DHCP_MT_DISABLED_AND_KEA_MT_ENABLED;
extern const isc::log::MessageID HA_CONFIG_LEASE_SYNCING_DISABLED;
extern const isc::log::MessageID HA_CONFIG_LEASE_SYNCING_DISABLED_REMINDER;
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_AND_SYNCING_DIFFER;
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_DISABLED;
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_DISABLED_REMINDER;
extern const isc::log::MessageID HA_CONFIG_SYSTEM_MT_UNSUPPORTED;
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
extern const isc::log::MessageID HA_HIGH_CLOCK_SKEW_CAUSED_TERMINATION;
extern const isc::log::MessageID HA_INIT_OK;
extern const isc::log::MessageID HA_INVALID_PARTNER_STATE_COMMUNICATION_RECOVERY;
extern const isc::log::MessageID HA_INVALID_PARTNER_STATE_HOT_STANDBY;
extern const isc::log::MessageID HA_INVALID_PARTNER_STATE_LOAD_BALANCING;
extern const isc::log::MessageID HA_LEASES4_COMMITTED_FAILED;
extern const isc::log::MessageID HA_LEASES4_COMMITTED_NOTHING_TO_UPDATE;
extern const isc::log::MessageID HA_LEASES6_COMMITTED_FAILED;
extern const isc::log::MessageID HA_LEASES6_COMMITTED_NOTHING_TO_UPDATE;
extern const isc::log::MessageID HA_LEASES_BACKLOG_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_LEASES_BACKLOG_FAILED;
extern const isc::log::MessageID HA_LEASES_BACKLOG_NOTHING_TO_SEND;
extern const isc::log::MessageID HA_LEASES_BACKLOG_START;
extern const isc::log::MessageID HA_LEASES_BACKLOG_SUCCESS;
extern const isc::log::MessageID HA_LEASES_SYNC_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_LEASES_SYNC_FAILED;
extern const isc::log::MessageID HA_LEASES_SYNC_LEASE_PAGE_RECEIVED;
extern const isc::log::MessageID HA_LEASE_SYNC_FAILED;
extern const isc::log::MessageID HA_LEASE_SYNC_STALE_LEASE4_SKIP;
extern const isc::log::MessageID HA_LEASE_SYNC_STALE_LEASE6_SKIP;
extern const isc::log::MessageID HA_LEASE_UPDATES_DISABLED;
extern const isc::log::MessageID HA_LEASE_UPDATES_ENABLED;
extern const isc::log::MessageID HA_LEASE_UPDATE_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_LEASE_UPDATE_CONFLICT;
extern const isc::log::MessageID HA_LEASE_UPDATE_CREATE_UPDATE_FAILED_ON_PEER;
extern const isc::log::MessageID HA_LEASE_UPDATE_DELETE_FAILED_ON_PEER;
extern const isc::log::MessageID HA_LEASE_UPDATE_FAILED;
extern const isc::log::MessageID HA_LEASE_UPDATE_REJECTS_CAUSED_TERMINATION;
extern const isc::log::MessageID HA_LOAD_BALANCING_DUID_MISSING;
extern const isc::log::MessageID HA_LOAD_BALANCING_IDENTIFIER_MISSING;
extern const isc::log::MessageID HA_LOCAL_DHCP_DISABLE;
extern const isc::log::MessageID HA_LOCAL_DHCP_ENABLE;
extern const isc::log::MessageID HA_MAINTENANCE_CANCEL_HANDLER_FAILED;
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_CANCEL_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_CANCEL_FAILED;
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_FAILED;
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_HANDLER_FAILED;
extern const isc::log::MessageID HA_MAINTENANCE_SHUTDOWN_SAFE;
extern const isc::log::MessageID HA_MAINTENANCE_STARTED;
extern const isc::log::MessageID HA_MAINTENANCE_STARTED_IN_PARTNER_DOWN;
extern const isc::log::MessageID HA_MAINTENANCE_START_HANDLER_FAILED;
extern const isc::log::MessageID HA_MISSING_CONFIGURATION;
extern const isc::log::MessageID HA_PAUSE_CLIENT_LISTENER_FAILED;
extern const isc::log::MessageID HA_PAUSE_CLIENT_LISTENER_ILLEGAL;
extern const isc::log::MessageID HA_RESET_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_RESET_FAILED;
extern const isc::log::MessageID HA_RESET_HANDLER_FAILED;
extern const isc::log::MessageID HA_RESUME_CLIENT_LISTENER_FAILED;
extern const isc::log::MessageID HA_SCOPES_HANDLER_FAILED;
extern const isc::log::MessageID HA_SERVICE_STARTED;
extern const isc::log::MessageID HA_STATE_MACHINE_CONTINUED;
extern const isc::log::MessageID HA_STATE_MACHINE_PAUSED;
extern const isc::log::MessageID HA_STATE_TRANSITION;
extern const isc::log::MessageID HA_STATE_TRANSITION_PASSIVE_BACKUP;
extern const isc::log::MessageID HA_SYNC_COMPLETE_NOTIFY_COMMUNICATIONS_FAILED;
extern const isc::log::MessageID HA_SYNC_COMPLETE_NOTIFY_FAILED;
extern const isc::log::MessageID HA_SYNC_COMPLETE_NOTIFY_HANDLER_FAILED;
extern const isc::log::MessageID HA_SYNC_FAILED;
extern const isc::log::MessageID HA_SYNC_HANDLER_FAILED;
extern const isc::log::MessageID HA_SYNC_START;
extern const isc::log::MessageID HA_SYNC_SUCCESSFUL;
extern const isc::log::MessageID HA_TERMINATED;
extern const isc::log::MessageID HA_TERMINATED_RESTART_PARTNER;

} // namespace ha
} // namespace isc

#endif // HA_MESSAGES_H
