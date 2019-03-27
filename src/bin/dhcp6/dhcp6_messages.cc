// File created from ../../../src/bin/dhcp6/dhcp6_messages.mes on Tue Mar 26 2019 13:41

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID DHCP6_ACTIVATE_INTERFACE = "DHCP6_ACTIVATE_INTERFACE";
extern const isc::log::MessageID DHCP6_ADD_GLOBAL_STATUS_CODE = "DHCP6_ADD_GLOBAL_STATUS_CODE";
extern const isc::log::MessageID DHCP6_ADD_STATUS_CODE_FOR_IA = "DHCP6_ADD_STATUS_CODE_FOR_IA";
extern const isc::log::MessageID DHCP6_ALREADY_RUNNING = "DHCP6_ALREADY_RUNNING";
extern const isc::log::MessageID DHCP6_BUFFER_RECEIVED = "DHCP6_BUFFER_RECEIVED";
extern const isc::log::MessageID DHCP6_BUFFER_UNPACK = "DHCP6_BUFFER_UNPACK";
extern const isc::log::MessageID DHCP6_BUFFER_WAIT_SIGNAL = "DHCP6_BUFFER_WAIT_SIGNAL";
extern const isc::log::MessageID DHCP6_CB_FETCH_UPDATES_FAIL = "DHCP6_CB_FETCH_UPDATES_FAIL";
extern const isc::log::MessageID DHCP6_CB_FETCH_UPDATES_RETRIES_EXHAUSTED = "DHCP6_CB_FETCH_UPDATES_RETRIES_EXHAUSTED";
extern const isc::log::MessageID DHCP6_CLASS_ASSIGNED = "DHCP6_CLASS_ASSIGNED";
extern const isc::log::MessageID DHCP6_CLASS_UNCONFIGURED = "DHCP6_CLASS_UNCONFIGURED";
extern const isc::log::MessageID DHCP6_CLASS_UNDEFINED = "DHCP6_CLASS_UNDEFINED";
extern const isc::log::MessageID DHCP6_CLASS_UNTESTABLE = "DHCP6_CLASS_UNTESTABLE";
extern const isc::log::MessageID DHCP6_COMMAND_RECEIVED = "DHCP6_COMMAND_RECEIVED";
extern const isc::log::MessageID DHCP6_CONFIG_COMPLETE = "DHCP6_CONFIG_COMPLETE";
extern const isc::log::MessageID DHCP6_CONFIG_LOAD_FAIL = "DHCP6_CONFIG_LOAD_FAIL";
extern const isc::log::MessageID DHCP6_CONFIG_PACKET_QUEUE = "DHCP6_CONFIG_PACKET_QUEUE";
extern const isc::log::MessageID DHCP6_CONFIG_RECEIVED = "DHCP6_CONFIG_RECEIVED";
extern const isc::log::MessageID DHCP6_CONFIG_START = "DHCP6_CONFIG_START";
extern const isc::log::MessageID DHCP6_CONFIG_UPDATE = "DHCP6_CONFIG_UPDATE";
extern const isc::log::MessageID DHCP6_DB_BACKEND_STARTED = "DHCP6_DB_BACKEND_STARTED";
extern const isc::log::MessageID DHCP6_DB_RECONNECT_ATTEMPT_FAILED = "DHCP6_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID DHCP6_DB_RECONNECT_ATTEMPT_SCHEDULE = "DHCP6_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID DHCP6_DB_RECONNECT_DISABLED = "DHCP6_DB_RECONNECT_DISABLED";
extern const isc::log::MessageID DHCP6_DB_RECONNECT_NO_DB_CTL = "DHCP6_DB_RECONNECT_NO_DB_CTL";
extern const isc::log::MessageID DHCP6_DB_RECONNECT_RETRIES_EXHAUSTED = "DHCP6_DB_RECONNECT_RETRIES_EXHAUSTED";
extern const isc::log::MessageID DHCP6_DDNS_CREATE_ADD_NAME_CHANGE_REQUEST = "DHCP6_DDNS_CREATE_ADD_NAME_CHANGE_REQUEST";
extern const isc::log::MessageID DHCP6_DDNS_FQDN_GENERATED = "DHCP6_DDNS_FQDN_GENERATED";
extern const isc::log::MessageID DHCP6_DDNS_GENERATED_FQDN_UPDATE_FAIL = "DHCP6_DDNS_GENERATED_FQDN_UPDATE_FAIL";
extern const isc::log::MessageID DHCP6_DDNS_GENERATE_FQDN = "DHCP6_DDNS_GENERATE_FQDN";
extern const isc::log::MessageID DHCP6_DDNS_LEASE_RENEW_FQDN_CHANGE = "DHCP6_DDNS_LEASE_RENEW_FQDN_CHANGE";
extern const isc::log::MessageID DHCP6_DDNS_RECEIVE_FQDN = "DHCP6_DDNS_RECEIVE_FQDN";
extern const isc::log::MessageID DHCP6_DDNS_REQUEST_SEND_FAILED = "DHCP6_DDNS_REQUEST_SEND_FAILED";
extern const isc::log::MessageID DHCP6_DDNS_RESPONSE_FQDN_DATA = "DHCP6_DDNS_RESPONSE_FQDN_DATA";
extern const isc::log::MessageID DHCP6_DDNS_SEND_FQDN = "DHCP6_DDNS_SEND_FQDN";
extern const isc::log::MessageID DHCP6_DEACTIVATE_INTERFACE = "DHCP6_DEACTIVATE_INTERFACE";
extern const isc::log::MessageID DHCP6_DECLINE_FAIL_DUID_MISMATCH = "DHCP6_DECLINE_FAIL_DUID_MISMATCH";
extern const isc::log::MessageID DHCP6_DECLINE_FAIL_IAID_MISMATCH = "DHCP6_DECLINE_FAIL_IAID_MISMATCH";
extern const isc::log::MessageID DHCP6_DECLINE_FAIL_LEASE_WITHOUT_DUID = "DHCP6_DECLINE_FAIL_LEASE_WITHOUT_DUID";
extern const isc::log::MessageID DHCP6_DECLINE_FAIL_NO_LEASE = "DHCP6_DECLINE_FAIL_NO_LEASE";
extern const isc::log::MessageID DHCP6_DECLINE_LEASE = "DHCP6_DECLINE_LEASE";
extern const isc::log::MessageID DHCP6_DECLINE_PROCESS_IA = "DHCP6_DECLINE_PROCESS_IA";
extern const isc::log::MessageID DHCP6_DHCP4O6_PACKET_RECEIVED = "DHCP6_DHCP4O6_PACKET_RECEIVED";
extern const isc::log::MessageID DHCP6_DHCP4O6_RECEIVE_FAIL = "DHCP6_DHCP4O6_RECEIVE_FAIL";
extern const isc::log::MessageID DHCP6_DHCP4O6_RECEIVING = "DHCP6_DHCP4O6_RECEIVING";
extern const isc::log::MessageID DHCP6_DHCP4O6_SEND_FAIL = "DHCP6_DHCP4O6_SEND_FAIL";
extern const isc::log::MessageID DHCP6_DYNAMIC_RECONFIGURATION = "DHCP6_DYNAMIC_RECONFIGURATION";
extern const isc::log::MessageID DHCP6_DYNAMIC_RECONFIGURATION_FAIL = "DHCP6_DYNAMIC_RECONFIGURATION_FAIL";
extern const isc::log::MessageID DHCP6_FLEX_ID = "DHCP6_FLEX_ID";
extern const isc::log::MessageID DHCP6_HANDLE_SIGNAL_EXCEPTION = "DHCP6_HANDLE_SIGNAL_EXCEPTION";
extern const isc::log::MessageID DHCP6_HOOKS_LIBS_RELOAD_FAIL = "DHCP6_HOOKS_LIBS_RELOAD_FAIL";
extern const isc::log::MessageID DHCP6_HOOK_BUFFER_RCVD_DROP = "DHCP6_HOOK_BUFFER_RCVD_DROP";
extern const isc::log::MessageID DHCP6_HOOK_BUFFER_RCVD_SKIP = "DHCP6_HOOK_BUFFER_RCVD_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_BUFFER_SEND_SKIP = "DHCP6_HOOK_BUFFER_SEND_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_DECLINE_DROP = "DHCP6_HOOK_DECLINE_DROP";
extern const isc::log::MessageID DHCP6_HOOK_DECLINE_SKIP = "DHCP6_HOOK_DECLINE_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_LEASE6_RELEASE_NA_SKIP = "DHCP6_HOOK_LEASE6_RELEASE_NA_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_LEASE6_RELEASE_PD_SKIP = "DHCP6_HOOK_LEASE6_RELEASE_PD_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_LEASES6_COMMITTED_DROP = "DHCP6_HOOK_LEASES6_COMMITTED_DROP";
extern const isc::log::MessageID DHCP6_HOOK_LEASES6_COMMITTED_PARK = "DHCP6_HOOK_LEASES6_COMMITTED_PARK";
extern const isc::log::MessageID DHCP6_HOOK_PACKET_RCVD_SKIP = "DHCP6_HOOK_PACKET_RCVD_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_PACKET_SEND_DROP = "DHCP6_HOOK_PACKET_SEND_DROP";
extern const isc::log::MessageID DHCP6_HOOK_PACKET_SEND_SKIP = "DHCP6_HOOK_PACKET_SEND_SKIP";
extern const isc::log::MessageID DHCP6_HOOK_SUBNET6_SELECT_DROP = "DHCP6_HOOK_SUBNET6_SELECT_DROP";
extern const isc::log::MessageID DHCP6_HOOK_SUBNET6_SELECT_SKIP = "DHCP6_HOOK_SUBNET6_SELECT_SKIP";
extern const isc::log::MessageID DHCP6_INIT_FAIL = "DHCP6_INIT_FAIL";
extern const isc::log::MessageID DHCP6_LEASE_ADVERT = "DHCP6_LEASE_ADVERT";
extern const isc::log::MessageID DHCP6_LEASE_ADVERT_FAIL = "DHCP6_LEASE_ADVERT_FAIL";
extern const isc::log::MessageID DHCP6_LEASE_ALLOC = "DHCP6_LEASE_ALLOC";
extern const isc::log::MessageID DHCP6_LEASE_ALLOC_FAIL = "DHCP6_LEASE_ALLOC_FAIL";
extern const isc::log::MessageID DHCP6_LEASE_DATA = "DHCP6_LEASE_DATA";
extern const isc::log::MessageID DHCP6_LEASE_NA_WITHOUT_DUID = "DHCP6_LEASE_NA_WITHOUT_DUID";
extern const isc::log::MessageID DHCP6_LEASE_PD_WITHOUT_DUID = "DHCP6_LEASE_PD_WITHOUT_DUID";
extern const isc::log::MessageID DHCP6_LEASE_RENEW = "DHCP6_LEASE_RENEW";
extern const isc::log::MessageID DHCP6_NOT_RUNNING = "DHCP6_NOT_RUNNING";
extern const isc::log::MessageID DHCP6_NO_INTERFACES = "DHCP6_NO_INTERFACES";
extern const isc::log::MessageID DHCP6_NO_SOCKETS_OPEN = "DHCP6_NO_SOCKETS_OPEN";
extern const isc::log::MessageID DHCP6_OPEN_SOCKET = "DHCP6_OPEN_SOCKET";
extern const isc::log::MessageID DHCP6_OPEN_SOCKET_FAIL = "DHCP6_OPEN_SOCKET_FAIL";
extern const isc::log::MessageID DHCP6_PACKET_DROP_DHCP_DISABLED = "DHCP6_PACKET_DROP_DHCP_DISABLED";
extern const isc::log::MessageID DHCP6_PACKET_DROP_PARSE_FAIL = "DHCP6_PACKET_DROP_PARSE_FAIL";
extern const isc::log::MessageID DHCP6_PACKET_DROP_SERVERID_MISMATCH = "DHCP6_PACKET_DROP_SERVERID_MISMATCH";
extern const isc::log::MessageID DHCP6_PACKET_DROP_UNICAST = "DHCP6_PACKET_DROP_UNICAST";
extern const isc::log::MessageID DHCP6_PACKET_OPTIONS_SKIPPED = "DHCP6_PACKET_OPTIONS_SKIPPED";
extern const isc::log::MessageID DHCP6_PACKET_PROCESS_EXCEPTION = "DHCP6_PACKET_PROCESS_EXCEPTION";
extern const isc::log::MessageID DHCP6_PACKET_PROCESS_FAIL = "DHCP6_PACKET_PROCESS_FAIL";
extern const isc::log::MessageID DHCP6_PACKET_PROCESS_STD_EXCEPTION = "DHCP6_PACKET_PROCESS_STD_EXCEPTION";
extern const isc::log::MessageID DHCP6_PACKET_RECEIVED = "DHCP6_PACKET_RECEIVED";
extern const isc::log::MessageID DHCP6_PACKET_RECEIVE_FAIL = "DHCP6_PACKET_RECEIVE_FAIL";
extern const isc::log::MessageID DHCP6_PACKET_SEND_FAIL = "DHCP6_PACKET_SEND_FAIL";
extern const isc::log::MessageID DHCP6_PACK_FAIL = "DHCP6_PACK_FAIL";
extern const isc::log::MessageID DHCP6_PARSER_COMMIT_EXCEPTION = "DHCP6_PARSER_COMMIT_EXCEPTION";
extern const isc::log::MessageID DHCP6_PARSER_COMMIT_FAIL = "DHCP6_PARSER_COMMIT_FAIL";
extern const isc::log::MessageID DHCP6_PARSER_EXCEPTION = "DHCP6_PARSER_EXCEPTION";
extern const isc::log::MessageID DHCP6_PARSER_FAIL = "DHCP6_PARSER_FAIL";
extern const isc::log::MessageID DHCP6_PD_LEASE_ADVERT = "DHCP6_PD_LEASE_ADVERT";
extern const isc::log::MessageID DHCP6_PD_LEASE_ADVERT_FAIL = "DHCP6_PD_LEASE_ADVERT_FAIL";
extern const isc::log::MessageID DHCP6_PD_LEASE_ALLOC = "DHCP6_PD_LEASE_ALLOC";
extern const isc::log::MessageID DHCP6_PD_LEASE_ALLOC_FAIL = "DHCP6_PD_LEASE_ALLOC_FAIL";
extern const isc::log::MessageID DHCP6_PD_LEASE_RENEW = "DHCP6_PD_LEASE_RENEW";
extern const isc::log::MessageID DHCP6_PROCESS_IA_NA_EXTEND = "DHCP6_PROCESS_IA_NA_EXTEND";
extern const isc::log::MessageID DHCP6_PROCESS_IA_NA_RELEASE = "DHCP6_PROCESS_IA_NA_RELEASE";
extern const isc::log::MessageID DHCP6_PROCESS_IA_NA_REQUEST = "DHCP6_PROCESS_IA_NA_REQUEST";
extern const isc::log::MessageID DHCP6_PROCESS_IA_PD_EXTEND = "DHCP6_PROCESS_IA_PD_EXTEND";
extern const isc::log::MessageID DHCP6_PROCESS_IA_PD_REQUEST = "DHCP6_PROCESS_IA_PD_REQUEST";
extern const isc::log::MessageID DHCP6_QUERY_DATA = "DHCP6_QUERY_DATA";
extern const isc::log::MessageID DHCP6_RAPID_COMMIT = "DHCP6_RAPID_COMMIT";
extern const isc::log::MessageID DHCP6_RELEASE_NA = "DHCP6_RELEASE_NA";
extern const isc::log::MessageID DHCP6_RELEASE_NA_FAIL = "DHCP6_RELEASE_NA_FAIL";
extern const isc::log::MessageID DHCP6_RELEASE_NA_FAIL_WRONG_DUID = "DHCP6_RELEASE_NA_FAIL_WRONG_DUID";
extern const isc::log::MessageID DHCP6_RELEASE_NA_FAIL_WRONG_IAID = "DHCP6_RELEASE_NA_FAIL_WRONG_IAID";
extern const isc::log::MessageID DHCP6_RELEASE_PD = "DHCP6_RELEASE_PD";
extern const isc::log::MessageID DHCP6_RELEASE_PD_FAIL = "DHCP6_RELEASE_PD_FAIL";
extern const isc::log::MessageID DHCP6_RELEASE_PD_FAIL_WRONG_DUID = "DHCP6_RELEASE_PD_FAIL_WRONG_DUID";
extern const isc::log::MessageID DHCP6_RELEASE_PD_FAIL_WRONG_IAID = "DHCP6_RELEASE_PD_FAIL_WRONG_IAID";
extern const isc::log::MessageID DHCP6_REQUIRED_OPTIONS_CHECK_FAIL = "DHCP6_REQUIRED_OPTIONS_CHECK_FAIL";
extern const isc::log::MessageID DHCP6_RESPONSE_DATA = "DHCP6_RESPONSE_DATA";
extern const isc::log::MessageID DHCP6_SERVER_FAILED = "DHCP6_SERVER_FAILED";
extern const isc::log::MessageID DHCP6_SHUTDOWN = "DHCP6_SHUTDOWN";
extern const isc::log::MessageID DHCP6_SHUTDOWN_REQUEST = "DHCP6_SHUTDOWN_REQUEST";
extern const isc::log::MessageID DHCP6_SOCKET_UNICAST = "DHCP6_SOCKET_UNICAST";
extern const isc::log::MessageID DHCP6_SRV_CONSTRUCT_ERROR = "DHCP6_SRV_CONSTRUCT_ERROR";
extern const isc::log::MessageID DHCP6_SRV_D2STOP_ERROR = "DHCP6_SRV_D2STOP_ERROR";
extern const isc::log::MessageID DHCP6_STANDALONE = "DHCP6_STANDALONE";
extern const isc::log::MessageID DHCP6_STARTED = "DHCP6_STARTED";
extern const isc::log::MessageID DHCP6_STARTING = "DHCP6_STARTING";
extern const isc::log::MessageID DHCP6_START_INFO = "DHCP6_START_INFO";
extern const isc::log::MessageID DHCP6_SUBNET_DATA = "DHCP6_SUBNET_DATA";
extern const isc::log::MessageID DHCP6_SUBNET_DYNAMICALLY_CHANGED = "DHCP6_SUBNET_DYNAMICALLY_CHANGED";
extern const isc::log::MessageID DHCP6_SUBNET_SELECTED = "DHCP6_SUBNET_SELECTED";
extern const isc::log::MessageID DHCP6_SUBNET_SELECTION_FAILED = "DHCP6_SUBNET_SELECTION_FAILED";
extern const isc::log::MessageID DHCP6_UNKNOWN_MSG_RECEIVED = "DHCP6_UNKNOWN_MSG_RECEIVED";
extern const isc::log::MessageID DHCP6_USING_SERVERID = "DHCP6_USING_SERVERID";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "DHCP6_ACTIVATE_INTERFACE", "activating interface %1",
    "DHCP6_ADD_GLOBAL_STATUS_CODE", "%1: adding Status Code to DHCPv6 packet: %2",
    "DHCP6_ADD_STATUS_CODE_FOR_IA", "%1: adding Status Code to IA with iaid=%2: %3",
    "DHCP6_ALREADY_RUNNING", "%1 already running? %2",
    "DHCP6_BUFFER_RECEIVED", "received buffer from %1:%2 to %3:%4 over interface %5",
    "DHCP6_BUFFER_UNPACK", "parsing buffer received from %1 to %2 over interface %3",
    "DHCP6_BUFFER_WAIT_SIGNAL", "signal received while waiting for next packet, next waiting signal is %1",
    "DHCP6_CB_FETCH_UPDATES_FAIL", "error on attempt to fetch configuration updates from the configuration backend(s): %1",
    "DHCP6_CB_FETCH_UPDATES_RETRIES_EXHAUSTED", "maximum number of configuration fetch attempts: 10, has been exhausted without success",
    "DHCP6_CLASS_ASSIGNED", "%1: client packet has been assigned to the following class(es): %2",
    "DHCP6_CLASS_UNCONFIGURED", "%1: client packet belongs to an unconfigured class: %2",
    "DHCP6_CLASS_UNDEFINED", "required class %1 has no definition",
    "DHCP6_CLASS_UNTESTABLE", "required class %1 has no test expression",
    "DHCP6_COMMAND_RECEIVED", "received command %1, arguments: %2",
    "DHCP6_CONFIG_COMPLETE", "DHCPv6 server has completed configuration: %1",
    "DHCP6_CONFIG_LOAD_FAIL", "configuration error using file: %1, reason: %2",
    "DHCP6_CONFIG_PACKET_QUEUE", "DHCPv6 packet queue info after configuration: %1",
    "DHCP6_CONFIG_RECEIVED", "received configuration: %1",
    "DHCP6_CONFIG_START", "DHCPv6 server is processing the following configuration: %1",
    "DHCP6_CONFIG_UPDATE", "updated configuration received: %1",
    "DHCP6_DB_BACKEND_STARTED", "lease database started (type: %1, name: %2)",
    "DHCP6_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "DHCP6_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "DHCP6_DB_RECONNECT_DISABLED", "database reconnect is disabled: max-reconnect-tries %1, reconnect-wait-time %2",
    "DHCP6_DB_RECONNECT_NO_DB_CTL", "unexpected error in database reconnect",
    "DHCP6_DB_RECONNECT_RETRIES_EXHAUSTED", "maximum number of database reconnect attempts: %1, has been exhausted without success, server is shutting down!",
    "DHCP6_DDNS_CREATE_ADD_NAME_CHANGE_REQUEST", "created name change request: %1",
    "DHCP6_DDNS_FQDN_GENERATED", "%1: generated FQDN for the client: %2",
    "DHCP6_DDNS_GENERATED_FQDN_UPDATE_FAIL", "%1: failed to update the lease using address %2, after generating FQDN for a client, reason: %3",
    "DHCP6_DDNS_GENERATE_FQDN", "%1: client did not send a FQDN option; FQDN will be",
    "DHCP6_DDNS_LEASE_RENEW_FQDN_CHANGE", "FQDN %1: FQDN for the renewed lease: %2 has changed. New values: hostname = %3, reverse mapping = %4, forward mapping = %5",
    "DHCP6_DDNS_RECEIVE_FQDN", "%1: received DHCPv6 Client FQDN option: %2",
    "DHCP6_DDNS_REQUEST_SEND_FAILED", "failed sending a request to kea-dhcp-ddns, error: %1,  ncr: %2",
    "DHCP6_DDNS_RESPONSE_FQDN_DATA", "%1: including FQDN option in the server's response: %2",
    "DHCP6_DDNS_SEND_FQDN", "sending DHCPv6 Client FQDN Option to the client: %1",
    "DHCP6_DEACTIVATE_INTERFACE", "deactivate interface %1",
    "DHCP6_DECLINE_FAIL_DUID_MISMATCH", "Client %1 sent DECLINE for address %2, but it belongs to client with DUID %3",
    "DHCP6_DECLINE_FAIL_IAID_MISMATCH", "Client %1 sent DECLINE for address %2, but used a wrong IAID (%3), instead of expected %4",
    "DHCP6_DECLINE_FAIL_LEASE_WITHOUT_DUID", "Client %1 sent DECLINE for address %2, but the associated lease has no DUID",
    "DHCP6_DECLINE_FAIL_NO_LEASE", "Client %1 sent DECLINE for address %2, but there's no lease for it",
    "DHCP6_DECLINE_LEASE", "Client %1 sent DECLINE for address %2 and the server marked it as declined. The lease will be recovered in %3 seconds.",
    "DHCP6_DECLINE_PROCESS_IA", "Processing of IA (IAID: %1) from client %2 started.",
    "DHCP6_DHCP4O6_PACKET_RECEIVED", "received DHCPv4o6 packet from DHCPv4 server (type %1) for %2 port %3 on interface %4",
    "DHCP6_DHCP4O6_RECEIVE_FAIL", "failed to receive DHCPv4o6: %1",
    "DHCP6_DHCP4O6_RECEIVING", "receiving DHCPv4o6 packet from DHCPv4 server",
    "DHCP6_DHCP4O6_SEND_FAIL", "failed to send DHCPv4o6 packet: %1",
    "DHCP6_DYNAMIC_RECONFIGURATION", "initiate server reconfiguration using file: %1, after receiving SIGHUP signal",
    "DHCP6_DYNAMIC_RECONFIGURATION_FAIL", "dynamic server reconfiguration failed with file: %1",
    "DHCP6_FLEX_ID", "flexible identifier generated for incoming packet: %1",
    "DHCP6_HANDLE_SIGNAL_EXCEPTION", "An exception was thrown while handing signal: %1",
    "DHCP6_HOOKS_LIBS_RELOAD_FAIL", "reload of hooks libraries failed",
    "DHCP6_HOOK_BUFFER_RCVD_DROP", "received buffer from %1 to %2 over interface %3 was dropped because a callout set the drop flag",
    "DHCP6_HOOK_BUFFER_RCVD_SKIP", "received buffer from %1 to %2 over interface %3 is not parsed because a callout set the next step to SKIP",
    "DHCP6_HOOK_BUFFER_SEND_SKIP", "%1: prepared DHCPv6 response was dropped because a callout set the next step to SKIP",
    "DHCP6_HOOK_DECLINE_DROP", "During Decline processing (client=%1, interface=%2, addr=%3) hook callout set next step to DROP, dropping packet.",
    "DHCP6_HOOK_DECLINE_SKIP", "During Decline processing (client=%1, interface=%2, addr=%3) hook callout set status to SKIP, skipping decline.",
    "DHCP6_HOOK_LEASE6_RELEASE_NA_SKIP", "%1: DHCPv6 address lease was not released because a callout set the next step to SKIP",
    "DHCP6_HOOK_LEASE6_RELEASE_PD_SKIP", "%1: prefix lease was not released because a callout set the next step to SKIP",
    "DHCP6_HOOK_LEASES6_COMMITTED_DROP", "%1: packet is dropped, because a callout set the next step to DROP",
    "DHCP6_HOOK_LEASES6_COMMITTED_PARK", "%1: packet is parked, because a callout set the next step to PARK",
    "DHCP6_HOOK_PACKET_RCVD_SKIP", "%1: packet is dropped, because a callout set the next step to SKIP",
    "DHCP6_HOOK_PACKET_SEND_DROP", "%1: prepared DHCPv6 response was not sent because a callout set the next ste to DROP",
    "DHCP6_HOOK_PACKET_SEND_SKIP", "%1: prepared DHCPv6 response is not built because a callout set the next step to SKIP",
    "DHCP6_HOOK_SUBNET6_SELECT_DROP", "%1: packet was dropped because a callout set the drop flag",
    "DHCP6_HOOK_SUBNET6_SELECT_SKIP", "%1: no subnet was selected because a callout set the next step to SKIP",
    "DHCP6_INIT_FAIL", "failed to initialize Kea server: %1",
    "DHCP6_LEASE_ADVERT", "%1: lease for address %2 and iaid=%3 will be advertised",
    "DHCP6_LEASE_ADVERT_FAIL", "%1: failed to advertise an address lease for iaid=%2",
    "DHCP6_LEASE_ALLOC", "%1: lease for address %2 and iaid=%3 has been allocated",
    "DHCP6_LEASE_ALLOC_FAIL", "%1: failed to grant an address lease for iaid=%2",
    "DHCP6_LEASE_DATA", "%1: detailed lease information for iaid=%2: %3",
    "DHCP6_LEASE_NA_WITHOUT_DUID", "%1: address lease for address %2 does not have a DUID",
    "DHCP6_LEASE_PD_WITHOUT_DUID", "%1: lease for prefix %2/%3 does not have a DUID",
    "DHCP6_LEASE_RENEW", "%1: lease for address %2 and iaid=%3 has been allocated",
    "DHCP6_NOT_RUNNING", "IPv6 DHCP server is not running",
    "DHCP6_NO_INTERFACES", "failed to detect any network interfaces",
    "DHCP6_NO_SOCKETS_OPEN", "no interface configured to listen to DHCP traffic",
    "DHCP6_OPEN_SOCKET", "opening service sockets on port %1",
    "DHCP6_OPEN_SOCKET_FAIL", "failed to open socket: %1",
    "DHCP6_PACKET_DROP_DHCP_DISABLED", "%1: DHCP service is globally disabled",
    "DHCP6_PACKET_DROP_PARSE_FAIL", "failed to parse packet from %1 to %2, received over interface %3, reason: %4",
    "DHCP6_PACKET_DROP_SERVERID_MISMATCH", "%1: dropping packet with server identifier: %2, server is using: %3",
    "DHCP6_PACKET_DROP_UNICAST", "%1: dropping unicast %2 packet as this packet should be sent to multicast",
    "DHCP6_PACKET_OPTIONS_SKIPPED", "An error upacking an option, caused subsequent options to be skipped: %1",
    "DHCP6_PACKET_PROCESS_EXCEPTION", "exception occurred during packet processing",
    "DHCP6_PACKET_PROCESS_FAIL", "processing of %1 message received from %2 failed: %3",
    "DHCP6_PACKET_PROCESS_STD_EXCEPTION", "exception occurred during packet processing: %1",
    "DHCP6_PACKET_RECEIVED", "%1: %2 (type %3) received from %4 to %5 on interface %6",
    "DHCP6_PACKET_RECEIVE_FAIL", "error on attempt to receive packet: %1",
    "DHCP6_PACKET_SEND_FAIL", "failed to send DHCPv6 packet: %1",
    "DHCP6_PACK_FAIL", "failed to assemble response correctly",
    "DHCP6_PARSER_COMMIT_EXCEPTION", "parser failed to commit changes",
    "DHCP6_PARSER_COMMIT_FAIL", "parser failed to commit changes: %1",
    "DHCP6_PARSER_EXCEPTION", "failed to create or run parser for configuration element %1",
    "DHCP6_PARSER_FAIL", "failed to create or run parser for configuration element %1: %2",
    "DHCP6_PD_LEASE_ADVERT", "%1: lease for prefix %2/%3 and iaid=%4 will be advertised",
    "DHCP6_PD_LEASE_ADVERT_FAIL", "%1: failed to advertise a prefix lease for iaid=%2",
    "DHCP6_PD_LEASE_ALLOC", "%1: lease for prefix %2/%3 and iaid=%4 has been allocated",
    "DHCP6_PD_LEASE_ALLOC_FAIL", "%1: failed to grant a prefix lease for iaid=%2",
    "DHCP6_PD_LEASE_RENEW", "%1: lease for prefix %2/%3 and iaid=%4 has been allocated",
    "DHCP6_PROCESS_IA_NA_EXTEND", "%1: extending lease lifetime for IA_NA option with iaid=%2",
    "DHCP6_PROCESS_IA_NA_RELEASE", "%1: releasing lease for IA_NA option with iaid=%2",
    "DHCP6_PROCESS_IA_NA_REQUEST", "%1: server is processing IA_NA option with iaid=%2 and hint=%3",
    "DHCP6_PROCESS_IA_PD_EXTEND", "%1: extending lease lifetime for IA_PD option with iaid=%2",
    "DHCP6_PROCESS_IA_PD_REQUEST", "%1: server is processing IA_PD option with iaid=%2 and hint=%3",
    "DHCP6_QUERY_DATA", "%1, packet details: %2",
    "DHCP6_RAPID_COMMIT", "%1: Rapid Commit option received, following 2-way exchange",
    "DHCP6_RELEASE_NA", "%1: binding for address %2 and iaid=%3 was released properly",
    "DHCP6_RELEASE_NA_FAIL", "%1: failed to remove address lease for address %2 and iaid=%3",
    "DHCP6_RELEASE_NA_FAIL_WRONG_DUID", "%1: client tried to release address %2, but it belongs to another client using duid=%3",
    "DHCP6_RELEASE_NA_FAIL_WRONG_IAID", "%1: client tried to release address %2, but it used wrong IAID (expected %3, but got %4)",
    "DHCP6_RELEASE_PD", "%1: prefix %2/%3 for iaid=%4 was released properly",
    "DHCP6_RELEASE_PD_FAIL", "%1: failed to release prefix %2/%3 for iaid=%4",
    "DHCP6_RELEASE_PD_FAIL_WRONG_DUID", "%1: client tried to release prefix %2/%3, but it belongs to another client (duid=%4)",
    "DHCP6_RELEASE_PD_FAIL_WRONG_IAID", "%1: client tried to release prefix %2/%3, but it used wrong IAID (expected %4, but got %5)",
    "DHCP6_REQUIRED_OPTIONS_CHECK_FAIL", "%1 message received from %2 failed the following check: %3",
    "DHCP6_RESPONSE_DATA", "responding with packet type %1 data is %2",
    "DHCP6_SERVER_FAILED", "server failed: %1",
    "DHCP6_SHUTDOWN", "server shutdown",
    "DHCP6_SHUTDOWN_REQUEST", "shutdown of server requested",
    "DHCP6_SOCKET_UNICAST", "server is about to open socket on address %1 on interface %2",
    "DHCP6_SRV_CONSTRUCT_ERROR", "error creating Dhcpv6Srv object, reason: %1",
    "DHCP6_SRV_D2STOP_ERROR", "error stopping IO with DHCP_DDNS during shutdown: %1",
    "DHCP6_STANDALONE", "skipping message queue, running standalone",
    "DHCP6_STARTED", "Kea DHCPv6 server version %1 started",
    "DHCP6_STARTING", "Kea DHCPv6 server version %1 starting",
    "DHCP6_START_INFO", "pid: %1, server port: %2, client port: %3, verbose: %4",
    "DHCP6_SUBNET_DATA", "%1: the selected subnet details: %2",
    "DHCP6_SUBNET_DYNAMICALLY_CHANGED", "%1: changed selected subnet %2 to subnet %3 from shared network %4 for client assignments",
    "DHCP6_SUBNET_SELECTED", "%1: the subnet with ID %2 was selected for client assignments",
    "DHCP6_SUBNET_SELECTION_FAILED", "%1: failed to select subnet for the client",
    "DHCP6_UNKNOWN_MSG_RECEIVED", "received unknown message (type %1) on interface %2",
    "DHCP6_USING_SERVERID", "server is using server-id %1 and stores in the file %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

