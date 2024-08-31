// File created from ../../../../src/hooks/dhcp/high_availability/ha_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace ha {

extern const isc::log::MessageID HA_BUFFER4_RECEIVE_FAILED = "HA_BUFFER4_RECEIVE_FAILED";
extern const isc::log::MessageID HA_BUFFER4_RECEIVE_NOT_FOR_US = "HA_BUFFER4_RECEIVE_NOT_FOR_US";
extern const isc::log::MessageID HA_BUFFER4_RECEIVE_PACKET_OPTIONS_SKIPPED = "HA_BUFFER4_RECEIVE_PACKET_OPTIONS_SKIPPED";
extern const isc::log::MessageID HA_BUFFER4_RECEIVE_UNPACK_FAILED = "HA_BUFFER4_RECEIVE_UNPACK_FAILED";
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_FAILED = "HA_BUFFER6_RECEIVE_FAILED";
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_NOT_FOR_US = "HA_BUFFER6_RECEIVE_NOT_FOR_US";
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_PACKET_OPTIONS_SKIPPED = "HA_BUFFER6_RECEIVE_PACKET_OPTIONS_SKIPPED";
extern const isc::log::MessageID HA_BUFFER6_RECEIVE_UNPACK_FAILED = "HA_BUFFER6_RECEIVE_UNPACK_FAILED";
extern const isc::log::MessageID HA_COMMAND_PROCESSED_FAILED = "HA_COMMAND_PROCESSED_FAILED";
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED = "HA_COMMUNICATION_INTERRUPTED";
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT4 = "HA_COMMUNICATION_INTERRUPTED_CLIENT4";
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT4_UNACKED = "HA_COMMUNICATION_INTERRUPTED_CLIENT4_UNACKED";
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT6 = "HA_COMMUNICATION_INTERRUPTED_CLIENT6";
extern const isc::log::MessageID HA_COMMUNICATION_INTERRUPTED_CLIENT6_UNACKED = "HA_COMMUNICATION_INTERRUPTED_CLIENT6_UNACKED";
extern const isc::log::MessageID HA_CONFIGURATION_FAILED = "HA_CONFIGURATION_FAILED";
extern const isc::log::MessageID HA_CONFIGURATION_SUCCESSFUL = "HA_CONFIGURATION_SUCCESSFUL";
extern const isc::log::MessageID HA_CONFIG_AUTO_FAILOVER_DISABLED = "HA_CONFIG_AUTO_FAILOVER_DISABLED";
extern const isc::log::MessageID HA_CONFIG_DHCP_MT_DISABLED = "HA_CONFIG_DHCP_MT_DISABLED";
extern const isc::log::MessageID HA_CONFIG_DHCP_MT_DISABLED_AND_KEA_MT_ENABLED = "HA_CONFIG_DHCP_MT_DISABLED_AND_KEA_MT_ENABLED";
extern const isc::log::MessageID HA_CONFIG_LEASE_SYNCING_DISABLED = "HA_CONFIG_LEASE_SYNCING_DISABLED";
extern const isc::log::MessageID HA_CONFIG_LEASE_SYNCING_DISABLED_REMINDER = "HA_CONFIG_LEASE_SYNCING_DISABLED_REMINDER";
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_AND_SYNCING_DIFFER = "HA_CONFIG_LEASE_UPDATES_AND_SYNCING_DIFFER";
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_DISABLED = "HA_CONFIG_LEASE_UPDATES_DISABLED";
extern const isc::log::MessageID HA_CONFIG_LEASE_UPDATES_DISABLED_REMINDER = "HA_CONFIG_LEASE_UPDATES_DISABLED_REMINDER";
extern const isc::log::MessageID HA_CONFIG_SYSTEM_MT_UNSUPPORTED = "HA_CONFIG_SYSTEM_MT_UNSUPPORTED";
extern const isc::log::MessageID HA_CONTINUE_HANDLER_FAILED = "HA_CONTINUE_HANDLER_FAILED";
extern const isc::log::MessageID HA_DEINIT_OK = "HA_DEINIT_OK";
extern const isc::log::MessageID HA_DHCP4_START_SERVICE_FAILED = "HA_DHCP4_START_SERVICE_FAILED";
extern const isc::log::MessageID HA_DHCP6_START_SERVICE_FAILED = "HA_DHCP6_START_SERVICE_FAILED";
extern const isc::log::MessageID HA_DHCP_DISABLE_COMMUNICATIONS_FAILED = "HA_DHCP_DISABLE_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_DHCP_DISABLE_FAILED = "HA_DHCP_DISABLE_FAILED";
extern const isc::log::MessageID HA_DHCP_ENABLE_COMMUNICATIONS_FAILED = "HA_DHCP_ENABLE_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_DHCP_ENABLE_FAILED = "HA_DHCP_ENABLE_FAILED";
extern const isc::log::MessageID HA_HEARTBEAT_COMMUNICATIONS_FAILED = "HA_HEARTBEAT_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_HEARTBEAT_FAILED = "HA_HEARTBEAT_FAILED";
extern const isc::log::MessageID HA_HEARTBEAT_HANDLER_FAILED = "HA_HEARTBEAT_HANDLER_FAILED";
extern const isc::log::MessageID HA_HIGH_CLOCK_SKEW = "HA_HIGH_CLOCK_SKEW";
extern const isc::log::MessageID HA_HIGH_CLOCK_SKEW_CAUSED_TERMINATION = "HA_HIGH_CLOCK_SKEW_CAUSED_TERMINATION";
extern const isc::log::MessageID HA_INIT_OK = "HA_INIT_OK";
extern const isc::log::MessageID HA_INVALID_PARTNER_STATE_COMMUNICATION_RECOVERY = "HA_INVALID_PARTNER_STATE_COMMUNICATION_RECOVERY";
extern const isc::log::MessageID HA_INVALID_PARTNER_STATE_HOT_STANDBY = "HA_INVALID_PARTNER_STATE_HOT_STANDBY";
extern const isc::log::MessageID HA_INVALID_PARTNER_STATE_LOAD_BALANCING = "HA_INVALID_PARTNER_STATE_LOAD_BALANCING";
extern const isc::log::MessageID HA_LEASE4_SERVER_DECLINE_FAILED = "HA_LEASE4_SERVER_DECLINE_FAILED";
extern const isc::log::MessageID HA_LEASES4_COMMITTED_FAILED = "HA_LEASES4_COMMITTED_FAILED";
extern const isc::log::MessageID HA_LEASES4_COMMITTED_NOTHING_TO_UPDATE = "HA_LEASES4_COMMITTED_NOTHING_TO_UPDATE";
extern const isc::log::MessageID HA_LEASES4_COMMITTED_NO_RELATIONSHIP = "HA_LEASES4_COMMITTED_NO_RELATIONSHIP";
extern const isc::log::MessageID HA_LEASES6_COMMITTED_FAILED = "HA_LEASES6_COMMITTED_FAILED";
extern const isc::log::MessageID HA_LEASES6_COMMITTED_NOTHING_TO_UPDATE = "HA_LEASES6_COMMITTED_NOTHING_TO_UPDATE";
extern const isc::log::MessageID HA_LEASES6_COMMITTED_NO_RELATIONSHIP = "HA_LEASES6_COMMITTED_NO_RELATIONSHIP";
extern const isc::log::MessageID HA_LEASES_BACKLOG_COMMUNICATIONS_FAILED = "HA_LEASES_BACKLOG_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_LEASES_BACKLOG_FAILED = "HA_LEASES_BACKLOG_FAILED";
extern const isc::log::MessageID HA_LEASES_BACKLOG_NOTHING_TO_SEND = "HA_LEASES_BACKLOG_NOTHING_TO_SEND";
extern const isc::log::MessageID HA_LEASES_BACKLOG_START = "HA_LEASES_BACKLOG_START";
extern const isc::log::MessageID HA_LEASES_BACKLOG_SUCCESS = "HA_LEASES_BACKLOG_SUCCESS";
extern const isc::log::MessageID HA_LEASES_SYNC_APPLIED_LEASES = "HA_LEASES_SYNC_APPLIED_LEASES";
extern const isc::log::MessageID HA_LEASES_SYNC_COMMUNICATIONS_FAILED = "HA_LEASES_SYNC_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_LEASES_SYNC_FAILED = "HA_LEASES_SYNC_FAILED";
extern const isc::log::MessageID HA_LEASES_SYNC_LEASE_PAGE_RECEIVED = "HA_LEASES_SYNC_LEASE_PAGE_RECEIVED";
extern const isc::log::MessageID HA_LEASE_SYNC_FAILED = "HA_LEASE_SYNC_FAILED";
extern const isc::log::MessageID HA_LEASE_SYNC_STALE_LEASE4_SKIP = "HA_LEASE_SYNC_STALE_LEASE4_SKIP";
extern const isc::log::MessageID HA_LEASE_SYNC_STALE_LEASE6_SKIP = "HA_LEASE_SYNC_STALE_LEASE6_SKIP";
extern const isc::log::MessageID HA_LEASE_UPDATES_DISABLED = "HA_LEASE_UPDATES_DISABLED";
extern const isc::log::MessageID HA_LEASE_UPDATES_ENABLED = "HA_LEASE_UPDATES_ENABLED";
extern const isc::log::MessageID HA_LEASE_UPDATE_COMMUNICATIONS_FAILED = "HA_LEASE_UPDATE_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_LEASE_UPDATE_CONFLICT = "HA_LEASE_UPDATE_CONFLICT";
extern const isc::log::MessageID HA_LEASE_UPDATE_CREATE_UPDATE_FAILED_ON_PEER = "HA_LEASE_UPDATE_CREATE_UPDATE_FAILED_ON_PEER";
extern const isc::log::MessageID HA_LEASE_UPDATE_DELETE_FAILED_ON_PEER = "HA_LEASE_UPDATE_DELETE_FAILED_ON_PEER";
extern const isc::log::MessageID HA_LEASE_UPDATE_FAILED = "HA_LEASE_UPDATE_FAILED";
extern const isc::log::MessageID HA_LEASE_UPDATE_REJECTS_CAUSED_TERMINATION = "HA_LEASE_UPDATE_REJECTS_CAUSED_TERMINATION";
extern const isc::log::MessageID HA_LOAD_BALANCING_DUID_MISSING = "HA_LOAD_BALANCING_DUID_MISSING";
extern const isc::log::MessageID HA_LOAD_BALANCING_IDENTIFIER_MISSING = "HA_LOAD_BALANCING_IDENTIFIER_MISSING";
extern const isc::log::MessageID HA_LOCAL_DHCP_DISABLE = "HA_LOCAL_DHCP_DISABLE";
extern const isc::log::MessageID HA_LOCAL_DHCP_ENABLE = "HA_LOCAL_DHCP_ENABLE";
extern const isc::log::MessageID HA_MAINTENANCE_CANCEL_HANDLER_FAILED = "HA_MAINTENANCE_CANCEL_HANDLER_FAILED";
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_CANCEL_COMMUNICATIONS_FAILED = "HA_MAINTENANCE_NOTIFY_CANCEL_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_CANCEL_FAILED = "HA_MAINTENANCE_NOTIFY_CANCEL_FAILED";
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_COMMUNICATIONS_FAILED = "HA_MAINTENANCE_NOTIFY_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_FAILED = "HA_MAINTENANCE_NOTIFY_FAILED";
extern const isc::log::MessageID HA_MAINTENANCE_NOTIFY_HANDLER_FAILED = "HA_MAINTENANCE_NOTIFY_HANDLER_FAILED";
extern const isc::log::MessageID HA_MAINTENANCE_SHUTDOWN_SAFE = "HA_MAINTENANCE_SHUTDOWN_SAFE";
extern const isc::log::MessageID HA_MAINTENANCE_STARTED = "HA_MAINTENANCE_STARTED";
extern const isc::log::MessageID HA_MAINTENANCE_STARTED_IN_PARTNER_DOWN = "HA_MAINTENANCE_STARTED_IN_PARTNER_DOWN";
extern const isc::log::MessageID HA_MAINTENANCE_START_HANDLER_FAILED = "HA_MAINTENANCE_START_HANDLER_FAILED";
extern const isc::log::MessageID HA_MISSING_CONFIGURATION = "HA_MISSING_CONFIGURATION";
extern const isc::log::MessageID HA_PAUSE_CLIENT_LISTENER_FAILED = "HA_PAUSE_CLIENT_LISTENER_FAILED";
extern const isc::log::MessageID HA_PAUSE_CLIENT_LISTENER_ILLEGAL = "HA_PAUSE_CLIENT_LISTENER_ILLEGAL";
extern const isc::log::MessageID HA_RESET_COMMUNICATIONS_FAILED = "HA_RESET_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_RESET_FAILED = "HA_RESET_FAILED";
extern const isc::log::MessageID HA_RESET_HANDLER_FAILED = "HA_RESET_HANDLER_FAILED";
extern const isc::log::MessageID HA_RESUME_CLIENT_LISTENER_FAILED = "HA_RESUME_CLIENT_LISTENER_FAILED";
extern const isc::log::MessageID HA_SCOPES_HANDLER_FAILED = "HA_SCOPES_HANDLER_FAILED";
extern const isc::log::MessageID HA_SERVICE_STARTED = "HA_SERVICE_STARTED";
extern const isc::log::MessageID HA_STATE_MACHINE_CONTINUED = "HA_STATE_MACHINE_CONTINUED";
extern const isc::log::MessageID HA_STATE_MACHINE_PAUSED = "HA_STATE_MACHINE_PAUSED";
extern const isc::log::MessageID HA_STATE_TRANSITION = "HA_STATE_TRANSITION";
extern const isc::log::MessageID HA_STATE_TRANSITION_PASSIVE_BACKUP = "HA_STATE_TRANSITION_PASSIVE_BACKUP";
extern const isc::log::MessageID HA_SUBNET4_SELECT_FAILED = "HA_SUBNET4_SELECT_FAILED";
extern const isc::log::MessageID HA_SUBNET4_SELECT_INVALID_HA_SERVER_NAME = "HA_SUBNET4_SELECT_INVALID_HA_SERVER_NAME";
extern const isc::log::MessageID HA_SUBNET4_SELECT_NOT_FOR_US = "HA_SUBNET4_SELECT_NOT_FOR_US";
extern const isc::log::MessageID HA_SUBNET4_SELECT_NO_RELATIONSHIP_FOR_SUBNET = "HA_SUBNET4_SELECT_NO_RELATIONSHIP_FOR_SUBNET";
extern const isc::log::MessageID HA_SUBNET4_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET = "HA_SUBNET4_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET";
extern const isc::log::MessageID HA_SUBNET4_SELECT_NO_SUBNET_SELECTED = "HA_SUBNET4_SELECT_NO_SUBNET_SELECTED";
extern const isc::log::MessageID HA_SUBNET6_SELECT_FAILED = "HA_SUBNET6_SELECT_FAILED";
extern const isc::log::MessageID HA_SUBNET6_SELECT_INVALID_HA_SERVER_NAME = "HA_SUBNET6_SELECT_INVALID_HA_SERVER_NAME";
extern const isc::log::MessageID HA_SUBNET6_SELECT_NOT_FOR_US = "HA_SUBNET6_SELECT_NOT_FOR_US";
extern const isc::log::MessageID HA_SUBNET6_SELECT_NO_RELATIONSHIP_FOR_SUBNET = "HA_SUBNET6_SELECT_NO_RELATIONSHIP_FOR_SUBNET";
extern const isc::log::MessageID HA_SUBNET6_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET = "HA_SUBNET6_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET";
extern const isc::log::MessageID HA_SUBNET6_SELECT_NO_SUBNET_SELECTED = "HA_SUBNET6_SELECT_NO_SUBNET_SELECTED";
extern const isc::log::MessageID HA_SYNC_COMPLETE_NOTIFY_COMMUNICATIONS_FAILED = "HA_SYNC_COMPLETE_NOTIFY_COMMUNICATIONS_FAILED";
extern const isc::log::MessageID HA_SYNC_COMPLETE_NOTIFY_FAILED = "HA_SYNC_COMPLETE_NOTIFY_FAILED";
extern const isc::log::MessageID HA_SYNC_COMPLETE_NOTIFY_HANDLER_FAILED = "HA_SYNC_COMPLETE_NOTIFY_HANDLER_FAILED";
extern const isc::log::MessageID HA_SYNC_FAILED = "HA_SYNC_FAILED";
extern const isc::log::MessageID HA_SYNC_HANDLER_FAILED = "HA_SYNC_HANDLER_FAILED";
extern const isc::log::MessageID HA_SYNC_START = "HA_SYNC_START";
extern const isc::log::MessageID HA_SYNC_SUCCESSFUL = "HA_SYNC_SUCCESSFUL";
extern const isc::log::MessageID HA_TERMINATED = "HA_TERMINATED";
extern const isc::log::MessageID HA_TERMINATED_PARTNER_DID_NOT_RESTART = "HA_TERMINATED_PARTNER_DID_NOT_RESTART";
extern const isc::log::MessageID HA_TERMINATED_RESTART_PARTNER = "HA_TERMINATED_RESTART_PARTNER";

} // namespace ha
} // namespace isc

namespace {

const char* values[] = {
    "HA_BUFFER4_RECEIVE_FAILED", "buffer4_receive callout failed: %1",
    "HA_BUFFER4_RECEIVE_NOT_FOR_US", "%1: dropping query to be processed by another server",
    "HA_BUFFER4_RECEIVE_PACKET_OPTIONS_SKIPPED", "an error unpacking an option, caused subsequent options to be skipped: %1",
    "HA_BUFFER4_RECEIVE_UNPACK_FAILED", "failed to parse query from %1 to %2, received over interface %3, reason: %4",
    "HA_BUFFER6_RECEIVE_FAILED", "buffer6_receive callout failed: %1",
    "HA_BUFFER6_RECEIVE_NOT_FOR_US", "%1: dropping query to be processed by another server",
    "HA_BUFFER6_RECEIVE_PACKET_OPTIONS_SKIPPED", "an error unpacking an option, caused subsequent options to be skipped: %1",
    "HA_BUFFER6_RECEIVE_UNPACK_FAILED", "failed to parse query from %1 to %2, received over interface %3, reason: %4",
    "HA_COMMAND_PROCESSED_FAILED", "command_processed callout failed: %1",
    "HA_COMMUNICATION_INTERRUPTED", "%1: communication with %2 is interrupted",
    "HA_COMMUNICATION_INTERRUPTED_CLIENT4", "%1: new client %2 attempting to get a lease from the partner",
    "HA_COMMUNICATION_INTERRUPTED_CLIENT4_UNACKED", "%1: partner server failed to respond to %2, %3 clients unacked so far, %4 clients left before transitioning to the partner-down state",
    "HA_COMMUNICATION_INTERRUPTED_CLIENT6", "%1: new client %2 attempting to get a lease from the partner",
    "HA_COMMUNICATION_INTERRUPTED_CLIENT6_UNACKED", "%1: partner server failed to respond to %2, %3 clients unacked so far, %4 clients left before transitioning to the partner-down state",
    "HA_CONFIGURATION_FAILED", "failed to configure High Availability hooks library: %1",
    "HA_CONFIGURATION_SUCCESSFUL", "HA hook library has been successfully configured",
    "HA_CONFIG_AUTO_FAILOVER_DISABLED", "%1: auto-failover disabled",
    "HA_CONFIG_DHCP_MT_DISABLED", "%1: HA multi-threading has been disabled, it cannot be enabled when Kea global multi-threading is disabled",
    "HA_CONFIG_DHCP_MT_DISABLED_AND_KEA_MT_ENABLED", "%1: HA multi-threading is disabled while Kea global multi-threading is enabled which most likely cause performance degradation.",
    "HA_CONFIG_LEASE_SYNCING_DISABLED", "%1: lease database synchronization between HA servers is disabled",
    "HA_CONFIG_LEASE_SYNCING_DISABLED_REMINDER", "%1: bypassing SYNCING state because lease database synchronization is administratively disabled",
    "HA_CONFIG_LEASE_UPDATES_AND_SYNCING_DIFFER", "%1: unusual configuration where \"send-lease-updates\": %2 and \"sync-leases\": %3",
    "HA_CONFIG_LEASE_UPDATES_DISABLED", "%1: lease updates will not be generated",
    "HA_CONFIG_LEASE_UPDATES_DISABLED_REMINDER", "%1: lease updates are administratively disabled and will not be generated while in %2 state",
    "HA_CONFIG_SYSTEM_MT_UNSUPPORTED", "%1: HA multi-threading has been disabled, auto-detection of thread support reports 0",
    "HA_CONTINUE_HANDLER_FAILED", "ha-continue command failed: %1",
    "HA_DEINIT_OK", "unloading High Availability hooks library successful",
    "HA_DHCP4_START_SERVICE_FAILED", "failed to start DHCPv4 HA services in dhcp4_srv_configured callout: %1",
    "HA_DHCP6_START_SERVICE_FAILED", "failed to start DHCPv6 HA services in dhcp6_srv_configured callout: %1",
    "HA_DHCP_DISABLE_COMMUNICATIONS_FAILED", "%1: failed to send request to disable DHCP service of %2: %3",
    "HA_DHCP_DISABLE_FAILED", "%1: failed to disable DHCP service of %2: %3",
    "HA_DHCP_ENABLE_COMMUNICATIONS_FAILED", "%1: failed to send request to enable DHCP service of %2: %3",
    "HA_DHCP_ENABLE_FAILED", "%1: failed to enable DHCP service of %2: %3",
    "HA_HEARTBEAT_COMMUNICATIONS_FAILED", "%1: failed to send heartbeat to %2: %3",
    "HA_HEARTBEAT_FAILED", "%1: heartbeat to %2 failed: %3",
    "HA_HEARTBEAT_HANDLER_FAILED", "heartbeat command failed: %1",
    "HA_HIGH_CLOCK_SKEW", "%1: %2, please synchronize clocks!",
    "HA_HIGH_CLOCK_SKEW_CAUSED_TERMINATION", "%1: %2, causing HA service to terminate",
    "HA_INIT_OK", "loading High Availability hooks library successful",
    "HA_INVALID_PARTNER_STATE_COMMUNICATION_RECOVERY", "%1: partner is in the communication-recovery state unexpectedly",
    "HA_INVALID_PARTNER_STATE_HOT_STANDBY", "%1: partner is in the hot-standby state unexpectedly",
    "HA_INVALID_PARTNER_STATE_LOAD_BALANCING", "%1: partner is in the load-balancing state unexpectedly",
    "HA_LEASE4_SERVER_DECLINE_FAILED", "lease4_server_decline callout failed: %1",
    "HA_LEASES4_COMMITTED_FAILED", "leases4_committed callout failed: %1",
    "HA_LEASES4_COMMITTED_NOTHING_TO_UPDATE", "%1: leases4_committed callout was invoked without any leases",
    "HA_LEASES4_COMMITTED_NO_RELATIONSHIP", "%1: HA relationship not found: %2",
    "HA_LEASES6_COMMITTED_FAILED", "leases6_committed callout failed: %1",
    "HA_LEASES6_COMMITTED_NOTHING_TO_UPDATE", "%1: leases6_committed callout was invoked without any leases",
    "HA_LEASES6_COMMITTED_NO_RELATIONSHIP", "%1: HA relationship not found: %2",
    "HA_LEASES_BACKLOG_COMMUNICATIONS_FAILED", "%1: failed to communicate with %2 while sending lease updates backlog: %3",
    "HA_LEASES_BACKLOG_FAILED", "%1: failed to send lease updates backlog to %2: %3",
    "HA_LEASES_BACKLOG_NOTHING_TO_SEND", "%1: no leases in backlog after communication recovery",
    "HA_LEASES_BACKLOG_START", "%1: starting to send %2 outstanding lease updates to %3",
    "HA_LEASES_BACKLOG_SUCCESS", "%1: sending lease updates backlog to %2 successful in %3",
    "HA_LEASES_SYNC_APPLIED_LEASES", "%1: applied %2 leases received from the partner in the local lease database",
    "HA_LEASES_SYNC_COMMUNICATIONS_FAILED", "%1: failed to communicate with %2 while syncing leases: %3",
    "HA_LEASES_SYNC_FAILED", "%1: failed to synchronize leases with %2: %3",
    "HA_LEASES_SYNC_LEASE_PAGE_RECEIVED", "%1: received %2 leases from %3",
    "HA_LEASE_SYNC_FAILED", "%1: synchronization failed for lease: %2, reason: %3",
    "HA_LEASE_SYNC_STALE_LEASE4_SKIP", "%1: skipping stale lease %2 in subnet %3",
    "HA_LEASE_SYNC_STALE_LEASE6_SKIP", "%1: skipping stale lease %2 in subnet %3",
    "HA_LEASE_UPDATES_DISABLED", "%1: lease updates will not be sent to the partner while in %2 state",
    "HA_LEASE_UPDATES_ENABLED", "%1: lease updates will be sent to the partner while in %2 state",
    "HA_LEASE_UPDATE_COMMUNICATIONS_FAILED", "%1: failed to send lease update %2 to %3: %4",
    "HA_LEASE_UPDATE_CONFLICT", "%1: lease update %2 sent to %3 returned conflict status code: %4",
    "HA_LEASE_UPDATE_CREATE_UPDATE_FAILED_ON_PEER", "%1: failed to create or update the lease having type %2 for address %3, reason: %4",
    "HA_LEASE_UPDATE_DELETE_FAILED_ON_PEER", "%1: failed to delete the lease having type %2 for address %3, reason: %4",
    "HA_LEASE_UPDATE_FAILED", "%1: lease update %2 sent to %3 failed: %4",
    "HA_LEASE_UPDATE_REJECTS_CAUSED_TERMINATION", "%1: too many rejected lease updates cause the HA service to terminate",
    "HA_LOAD_BALANCING_DUID_MISSING", "%1: load balancing failed for the DHCPv6 message (transaction id: %2) because DUID is missing",
    "HA_LOAD_BALANCING_IDENTIFIER_MISSING", "%1: load balancing failed for the DHCPv4 message (transaction id: %2) because HW address and client identifier are missing",
    "HA_LOCAL_DHCP_DISABLE", "local DHCP service is disabled while the %1 is in the %2 state",
    "HA_LOCAL_DHCP_ENABLE", "local DHCP service is enabled while the %1 is in the %2 state",
    "HA_MAINTENANCE_CANCEL_HANDLER_FAILED", "ha-maintenance-cancel command failed: %1",
    "HA_MAINTENANCE_NOTIFY_CANCEL_COMMUNICATIONS_FAILED", "%1: failed to send ha-maintenance-notify to %2 in attempt to cancel its maintenance: %3",
    "HA_MAINTENANCE_NOTIFY_CANCEL_FAILED", "%1: error returned while processing ha-maintenance-notify by %2 in attempt to cancel its maintenance: %3",
    "HA_MAINTENANCE_NOTIFY_COMMUNICATIONS_FAILED", "%1: failed to send ha-maintenance-notify to %2: %3",
    "HA_MAINTENANCE_NOTIFY_FAILED", "%1: error returned while processing ha-maintenance-notify by %2: %3",
    "HA_MAINTENANCE_NOTIFY_HANDLER_FAILED", "ha-maintenance-notify command failed: %1",
    "HA_MAINTENANCE_SHUTDOWN_SAFE", "%1: the server can now be shutdown for maintenance as the partner has taken over the DHCP traffic",
    "HA_MAINTENANCE_STARTED", "%1: the server is now in the partner-in-maintenance state and the partner is in-maintenance state",
    "HA_MAINTENANCE_STARTED_IN_PARTNER_DOWN", "%1: the server is now in the partner-down mode as a result of requested maintenance",
    "HA_MAINTENANCE_START_HANDLER_FAILED", "ha-maintenance-start command failed: %1",
    "HA_MISSING_CONFIGURATION", "high-availability parameter not specified for High Availability hooks library",
    "HA_PAUSE_CLIENT_LISTENER_FAILED", "%1: pausing multi-threaded HTTP processing failed: %2",
    "HA_PAUSE_CLIENT_LISTENER_ILLEGAL", "%1: pausing multi-threaded HTTP processing failed: %2",
    "HA_RESET_COMMUNICATIONS_FAILED", "%1: failed to send ha-reset command to %2: %3",
    "HA_RESET_FAILED", "%1: failed to reset HA state machine of %2: %3",
    "HA_RESET_HANDLER_FAILED", "ha-reset command failed: %1",
    "HA_RESUME_CLIENT_LISTENER_FAILED", "%1: resuming multi-threaded HTTP processing failed: %2",
    "HA_SCOPES_HANDLER_FAILED", "ha-scopes command failed: %1",
    "HA_SERVICE_STARTED", "%1: started high availability service in %2 mode as %3 server",
    "HA_STATE_MACHINE_CONTINUED", "%1: state machine is un-paused",
    "HA_STATE_MACHINE_PAUSED", "%1: state machine paused in state %2",
    "HA_STATE_TRANSITION", "%1: server transitions from %2 to %3 state, partner state is %4",
    "HA_STATE_TRANSITION_PASSIVE_BACKUP", "%1: server transitions from %2 to %3 state",
    "HA_SUBNET4_SELECT_FAILED", "subnet4_select callout failed: %1",
    "HA_SUBNET4_SELECT_INVALID_HA_SERVER_NAME", "%1: invalid ha-server-name value for subnet %2",
    "HA_SUBNET4_SELECT_NOT_FOR_US", "%1: dropping query in relationship %2 to be processed by another server",
    "HA_SUBNET4_SELECT_NO_RELATIONSHIP_FOR_SUBNET", "%1: HA relationship not found for %2",
    "HA_SUBNET4_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET", "%1: unable to determine HA relationship because selected subnet %2 lacks the ha-server-name",
    "HA_SUBNET4_SELECT_NO_SUBNET_SELECTED", "%1: unable to determine HA relationship because no subnet has been selected for the client",
    "HA_SUBNET6_SELECT_FAILED", "subnet6_select callout failed: %1",
    "HA_SUBNET6_SELECT_INVALID_HA_SERVER_NAME", "%1: invalid ha-server-name value for subnet %2",
    "HA_SUBNET6_SELECT_NOT_FOR_US", "%1: dropping query in relationship %2 to be processed by another server",
    "HA_SUBNET6_SELECT_NO_RELATIONSHIP_FOR_SUBNET", "%1: HA relationship not found for %2",
    "HA_SUBNET6_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET", "%1: unable to determine HA relationship because selected subnet %2 lacks the ha-server-name",
    "HA_SUBNET6_SELECT_NO_SUBNET_SELECTED", "%1: unable to determine HA relationship because no subnet has been selected for the client",
    "HA_SYNC_COMPLETE_NOTIFY_COMMUNICATIONS_FAILED", "%1: failed to send ha-sync-complete-notify to %2: %3",
    "HA_SYNC_COMPLETE_NOTIFY_FAILED", "%1: error processing ha-sync-complete-notify command on %2: %3",
    "HA_SYNC_COMPLETE_NOTIFY_HANDLER_FAILED", "ha-sync-complete-notify command failed: %1",
    "HA_SYNC_FAILED", "%1: lease database synchronization with %2 failed: %3",
    "HA_SYNC_HANDLER_FAILED", "ha-sync command failed: %1",
    "HA_SYNC_START", "%1: starting lease database synchronization with %2",
    "HA_SYNC_SUCCESSFUL", "%1: lease database synchronization with %2 completed successfully in %3",
    "HA_TERMINATED", "HA %1: service terminated due to an unrecoverable condition. Check previous error message(s), address the problem and restart!",
    "HA_TERMINATED_PARTNER_DID_NOT_RESTART", "%1: service is terminating because the terminated partner was not restarted within %2 minutes",
    "HA_TERMINATED_RESTART_PARTNER", "%1: waiting for the partner in the TERMINATED state to be restarted",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

