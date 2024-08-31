// File created from ../../../src/bin/dhcp4/dhcp4_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID DHCP4_ALREADY_RUNNING = "DHCP4_ALREADY_RUNNING";
extern const isc::log::MessageID DHCP4_BUFFER_RECEIVED = "DHCP4_BUFFER_RECEIVED";
extern const isc::log::MessageID DHCP4_BUFFER_RECEIVE_FAIL = "DHCP4_BUFFER_RECEIVE_FAIL";
extern const isc::log::MessageID DHCP4_BUFFER_UNPACK = "DHCP4_BUFFER_UNPACK";
extern const isc::log::MessageID DHCP4_BUFFER_WAIT_SIGNAL = "DHCP4_BUFFER_WAIT_SIGNAL";
extern const isc::log::MessageID DHCP4_CB_ON_DEMAND_FETCH_UPDATES_FAIL = "DHCP4_CB_ON_DEMAND_FETCH_UPDATES_FAIL";
extern const isc::log::MessageID DHCP4_CB_PERIODIC_FETCH_UPDATES_FAIL = "DHCP4_CB_PERIODIC_FETCH_UPDATES_FAIL";
extern const isc::log::MessageID DHCP4_CB_PERIODIC_FETCH_UPDATES_RETRIES_EXHAUSTED = "DHCP4_CB_PERIODIC_FETCH_UPDATES_RETRIES_EXHAUSTED";
extern const isc::log::MessageID DHCP4_CLASSES_ASSIGNED = "DHCP4_CLASSES_ASSIGNED";
extern const isc::log::MessageID DHCP4_CLASSES_ASSIGNED_AFTER_SUBNET_SELECTION = "DHCP4_CLASSES_ASSIGNED_AFTER_SUBNET_SELECTION";
extern const isc::log::MessageID DHCP4_CLASS_ASSIGNED = "DHCP4_CLASS_ASSIGNED";
extern const isc::log::MessageID DHCP4_CLASS_UNCONFIGURED = "DHCP4_CLASS_UNCONFIGURED";
extern const isc::log::MessageID DHCP4_CLASS_UNDEFINED = "DHCP4_CLASS_UNDEFINED";
extern const isc::log::MessageID DHCP4_CLASS_UNTESTABLE = "DHCP4_CLASS_UNTESTABLE";
extern const isc::log::MessageID DHCP4_CLIENTID_IGNORED_FOR_LEASES = "DHCP4_CLIENTID_IGNORED_FOR_LEASES";
extern const isc::log::MessageID DHCP4_CLIENT_FQDN_DATA = "DHCP4_CLIENT_FQDN_DATA";
extern const isc::log::MessageID DHCP4_CLIENT_FQDN_PROCESS = "DHCP4_CLIENT_FQDN_PROCESS";
extern const isc::log::MessageID DHCP4_CLIENT_HOSTNAME_DATA = "DHCP4_CLIENT_HOSTNAME_DATA";
extern const isc::log::MessageID DHCP4_CLIENT_HOSTNAME_MALFORMED = "DHCP4_CLIENT_HOSTNAME_MALFORMED";
extern const isc::log::MessageID DHCP4_CLIENT_HOSTNAME_PROCESS = "DHCP4_CLIENT_HOSTNAME_PROCESS";
extern const isc::log::MessageID DHCP4_CLIENT_NAME_PROC_FAIL = "DHCP4_CLIENT_NAME_PROC_FAIL";
extern const isc::log::MessageID DHCP4_CONFIG_COMPLETE = "DHCP4_CONFIG_COMPLETE";
extern const isc::log::MessageID DHCP4_CONFIG_LOAD_FAIL = "DHCP4_CONFIG_LOAD_FAIL";
extern const isc::log::MessageID DHCP4_CONFIG_PACKET_QUEUE = "DHCP4_CONFIG_PACKET_QUEUE";
extern const isc::log::MessageID DHCP4_CONFIG_RECEIVED = "DHCP4_CONFIG_RECEIVED";
extern const isc::log::MessageID DHCP4_CONFIG_START = "DHCP4_CONFIG_START";
extern const isc::log::MessageID DHCP4_CONFIG_SYNTAX_WARNING = "DHCP4_CONFIG_SYNTAX_WARNING";
extern const isc::log::MessageID DHCP4_CONFIG_UNRECOVERABLE_ERROR = "DHCP4_CONFIG_UNRECOVERABLE_ERROR";
extern const isc::log::MessageID DHCP4_CONFIG_UNSUPPORTED_OBJECT = "DHCP4_CONFIG_UNSUPPORTED_OBJECT";
extern const isc::log::MessageID DHCP4_DB_RECONNECT_DISABLED = "DHCP4_DB_RECONNECT_DISABLED";
extern const isc::log::MessageID DHCP4_DB_RECONNECT_FAILED = "DHCP4_DB_RECONNECT_FAILED";
extern const isc::log::MessageID DHCP4_DB_RECONNECT_LOST_CONNECTION = "DHCP4_DB_RECONNECT_LOST_CONNECTION";
extern const isc::log::MessageID DHCP4_DB_RECONNECT_NO_DB_CTL = "DHCP4_DB_RECONNECT_NO_DB_CTL";
extern const isc::log::MessageID DHCP4_DB_RECONNECT_SUCCEEDED = "DHCP4_DB_RECONNECT_SUCCEEDED";
extern const isc::log::MessageID DHCP4_DDNS_REQUEST_SEND_FAILED = "DHCP4_DDNS_REQUEST_SEND_FAILED";
extern const isc::log::MessageID DHCP4_DECLINE_FAIL = "DHCP4_DECLINE_FAIL";
extern const isc::log::MessageID DHCP4_DECLINE_LEASE = "DHCP4_DECLINE_LEASE";
extern const isc::log::MessageID DHCP4_DECLINE_LEASE_MISMATCH = "DHCP4_DECLINE_LEASE_MISMATCH";
extern const isc::log::MessageID DHCP4_DECLINE_LEASE_NOT_FOUND = "DHCP4_DECLINE_LEASE_NOT_FOUND";
extern const isc::log::MessageID DHCP4_DEFERRED_OPTION_MISSING = "DHCP4_DEFERRED_OPTION_MISSING";
extern const isc::log::MessageID DHCP4_DEFERRED_OPTION_UNPACK_FAIL = "DHCP4_DEFERRED_OPTION_UNPACK_FAIL";
extern const isc::log::MessageID DHCP4_DEVELOPMENT_VERSION = "DHCP4_DEVELOPMENT_VERSION";
extern const isc::log::MessageID DHCP4_DHCP4O6_BAD_PACKET = "DHCP4_DHCP4O6_BAD_PACKET";
extern const isc::log::MessageID DHCP4_DHCP4O6_HOOK_SUBNET4_SELECT_DROP = "DHCP4_DHCP4O6_HOOK_SUBNET4_SELECT_DROP";
extern const isc::log::MessageID DHCP4_DHCP4O6_HOOK_SUBNET4_SELECT_SKIP = "DHCP4_DHCP4O6_HOOK_SUBNET4_SELECT_SKIP";
extern const isc::log::MessageID DHCP4_DHCP4O6_PACKET_RECEIVED = "DHCP4_DHCP4O6_PACKET_RECEIVED";
extern const isc::log::MessageID DHCP4_DHCP4O6_PACKET_SEND = "DHCP4_DHCP4O6_PACKET_SEND";
extern const isc::log::MessageID DHCP4_DHCP4O6_PACKET_SEND_FAIL = "DHCP4_DHCP4O6_PACKET_SEND_FAIL";
extern const isc::log::MessageID DHCP4_DHCP4O6_RECEIVE_FAIL = "DHCP4_DHCP4O6_RECEIVE_FAIL";
extern const isc::log::MessageID DHCP4_DHCP4O6_RECEIVING = "DHCP4_DHCP4O6_RECEIVING";
extern const isc::log::MessageID DHCP4_DHCP4O6_RESPONSE_DATA = "DHCP4_DHCP4O6_RESPONSE_DATA";
extern const isc::log::MessageID DHCP4_DHCP4O6_SUBNET_DATA = "DHCP4_DHCP4O6_SUBNET_DATA";
extern const isc::log::MessageID DHCP4_DHCP4O6_SUBNET_SELECTED = "DHCP4_DHCP4O6_SUBNET_SELECTED";
extern const isc::log::MessageID DHCP4_DHCP4O6_SUBNET_SELECTION_FAILED = "DHCP4_DHCP4O6_SUBNET_SELECTION_FAILED";
extern const isc::log::MessageID DHCP4_DISCOVER = "DHCP4_DISCOVER";
extern const isc::log::MessageID DHCP4_DYNAMIC_RECONFIGURATION = "DHCP4_DYNAMIC_RECONFIGURATION";
extern const isc::log::MessageID DHCP4_DYNAMIC_RECONFIGURATION_FAIL = "DHCP4_DYNAMIC_RECONFIGURATION_FAIL";
extern const isc::log::MessageID DHCP4_DYNAMIC_RECONFIGURATION_SUCCESS = "DHCP4_DYNAMIC_RECONFIGURATION_SUCCESS";
extern const isc::log::MessageID DHCP4_EMPTY_HOSTNAME = "DHCP4_EMPTY_HOSTNAME";
extern const isc::log::MessageID DHCP4_FLEX_ID = "DHCP4_FLEX_ID";
extern const isc::log::MessageID DHCP4_GENERATE_FQDN = "DHCP4_GENERATE_FQDN";
extern const isc::log::MessageID DHCP4_HOOK_BUFFER_RCVD_DROP = "DHCP4_HOOK_BUFFER_RCVD_DROP";
extern const isc::log::MessageID DHCP4_HOOK_BUFFER_RCVD_SKIP = "DHCP4_HOOK_BUFFER_RCVD_SKIP";
extern const isc::log::MessageID DHCP4_HOOK_BUFFER_SEND_SKIP = "DHCP4_HOOK_BUFFER_SEND_SKIP";
extern const isc::log::MessageID DHCP4_HOOK_DDNS_UPDATE = "DHCP4_HOOK_DDNS_UPDATE";
extern const isc::log::MessageID DHCP4_HOOK_DECLINE_SKIP = "DHCP4_HOOK_DECLINE_SKIP";
extern const isc::log::MessageID DHCP4_HOOK_LEASE4_OFFER_ARGUMENT_MISSING = "DHCP4_HOOK_LEASE4_OFFER_ARGUMENT_MISSING";
extern const isc::log::MessageID DHCP4_HOOK_LEASE4_OFFER_DROP = "DHCP4_HOOK_LEASE4_OFFER_DROP";
extern const isc::log::MessageID DHCP4_HOOK_LEASE4_OFFER_PARK = "DHCP4_HOOK_LEASE4_OFFER_PARK";
extern const isc::log::MessageID DHCP4_HOOK_LEASE4_OFFER_PARKING_LOT_FULL = "DHCP4_HOOK_LEASE4_OFFER_PARKING_LOT_FULL";
extern const isc::log::MessageID DHCP4_HOOK_LEASE4_RELEASE_SKIP = "DHCP4_HOOK_LEASE4_RELEASE_SKIP";
extern const isc::log::MessageID DHCP4_HOOK_LEASES4_COMMITTED_DROP = "DHCP4_HOOK_LEASES4_COMMITTED_DROP";
extern const isc::log::MessageID DHCP4_HOOK_LEASES4_COMMITTED_PARK = "DHCP4_HOOK_LEASES4_COMMITTED_PARK";
extern const isc::log::MessageID DHCP4_HOOK_LEASES4_COMMITTED_PARKING_LOT_FULL = "DHCP4_HOOK_LEASES4_COMMITTED_PARKING_LOT_FULL";
extern const isc::log::MessageID DHCP4_HOOK_PACKET_RCVD_SKIP = "DHCP4_HOOK_PACKET_RCVD_SKIP";
extern const isc::log::MessageID DHCP4_HOOK_PACKET_SEND_DROP = "DHCP4_HOOK_PACKET_SEND_DROP";
extern const isc::log::MessageID DHCP4_HOOK_PACKET_SEND_SKIP = "DHCP4_HOOK_PACKET_SEND_SKIP";
extern const isc::log::MessageID DHCP4_HOOK_SUBNET4_SELECT_4O6_PARKING_LOT_FULL = "DHCP4_HOOK_SUBNET4_SELECT_4O6_PARKING_LOT_FULL";
extern const isc::log::MessageID DHCP4_HOOK_SUBNET4_SELECT_DROP = "DHCP4_HOOK_SUBNET4_SELECT_DROP";
extern const isc::log::MessageID DHCP4_HOOK_SUBNET4_SELECT_PARK = "DHCP4_HOOK_SUBNET4_SELECT_PARK";
extern const isc::log::MessageID DHCP4_HOOK_SUBNET4_SELECT_PARKING_LOT_FULL = "DHCP4_HOOK_SUBNET4_SELECT_PARKING_LOT_FULL";
extern const isc::log::MessageID DHCP4_HOOK_SUBNET4_SELECT_SKIP = "DHCP4_HOOK_SUBNET4_SELECT_SKIP";
extern const isc::log::MessageID DHCP4_INFORM_DIRECT_REPLY = "DHCP4_INFORM_DIRECT_REPLY";
extern const isc::log::MessageID DHCP4_INIT_FAIL = "DHCP4_INIT_FAIL";
extern const isc::log::MessageID DHCP4_INIT_REBOOT = "DHCP4_INIT_REBOOT";
extern const isc::log::MessageID DHCP4_LEASE_ALLOC = "DHCP4_LEASE_ALLOC";
extern const isc::log::MessageID DHCP4_LEASE_OFFER = "DHCP4_LEASE_OFFER";
extern const isc::log::MessageID DHCP4_LEASE_REUSE = "DHCP4_LEASE_REUSE";
extern const isc::log::MessageID DHCP4_MULTI_THREADING_INFO = "DHCP4_MULTI_THREADING_INFO";
extern const isc::log::MessageID DHCP4_NCR_CREATION_FAILED = "DHCP4_NCR_CREATION_FAILED";
extern const isc::log::MessageID DHCP4_NOT_RUNNING = "DHCP4_NOT_RUNNING";
extern const isc::log::MessageID DHCP4_NO_LEASE_INIT_REBOOT = "DHCP4_NO_LEASE_INIT_REBOOT";
extern const isc::log::MessageID DHCP4_OPEN_SOCKET = "DHCP4_OPEN_SOCKET";
extern const isc::log::MessageID DHCP4_OPEN_SOCKETS_FAILED = "DHCP4_OPEN_SOCKETS_FAILED";
extern const isc::log::MessageID DHCP4_OPEN_SOCKETS_NO_RECONNECT_CTL = "DHCP4_OPEN_SOCKETS_NO_RECONNECT_CTL";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0001 = "DHCP4_PACKET_DROP_0001";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0002 = "DHCP4_PACKET_DROP_0002";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0003 = "DHCP4_PACKET_DROP_0003";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0004 = "DHCP4_PACKET_DROP_0004";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0005 = "DHCP4_PACKET_DROP_0005";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0006 = "DHCP4_PACKET_DROP_0006";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0007 = "DHCP4_PACKET_DROP_0007";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0008 = "DHCP4_PACKET_DROP_0008";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0009 = "DHCP4_PACKET_DROP_0009";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0010 = "DHCP4_PACKET_DROP_0010";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0011 = "DHCP4_PACKET_DROP_0011";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0012 = "DHCP4_PACKET_DROP_0012";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0013 = "DHCP4_PACKET_DROP_0013";
extern const isc::log::MessageID DHCP4_PACKET_DROP_0014 = "DHCP4_PACKET_DROP_0014";
extern const isc::log::MessageID DHCP4_PACKET_NAK_0001 = "DHCP4_PACKET_NAK_0001";
extern const isc::log::MessageID DHCP4_PACKET_NAK_0002 = "DHCP4_PACKET_NAK_0002";
extern const isc::log::MessageID DHCP4_PACKET_NAK_0003 = "DHCP4_PACKET_NAK_0003";
extern const isc::log::MessageID DHCP4_PACKET_NAK_0004 = "DHCP4_PACKET_NAK_0004";
extern const isc::log::MessageID DHCP4_PACKET_OPTIONS_SKIPPED = "DHCP4_PACKET_OPTIONS_SKIPPED";
extern const isc::log::MessageID DHCP4_PACKET_PACK = "DHCP4_PACKET_PACK";
extern const isc::log::MessageID DHCP4_PACKET_PACK_FAIL = "DHCP4_PACKET_PACK_FAIL";
extern const isc::log::MessageID DHCP4_PACKET_PROCESS_EXCEPTION = "DHCP4_PACKET_PROCESS_EXCEPTION";
extern const isc::log::MessageID DHCP4_PACKET_PROCESS_EXCEPTION_MAIN = "DHCP4_PACKET_PROCESS_EXCEPTION_MAIN";
extern const isc::log::MessageID DHCP4_PACKET_PROCESS_STD_EXCEPTION = "DHCP4_PACKET_PROCESS_STD_EXCEPTION";
extern const isc::log::MessageID DHCP4_PACKET_PROCESS_STD_EXCEPTION_MAIN = "DHCP4_PACKET_PROCESS_STD_EXCEPTION_MAIN";
extern const isc::log::MessageID DHCP4_PACKET_QUEUE_FULL = "DHCP4_PACKET_QUEUE_FULL";
extern const isc::log::MessageID DHCP4_PACKET_RECEIVED = "DHCP4_PACKET_RECEIVED";
extern const isc::log::MessageID DHCP4_PACKET_SEND = "DHCP4_PACKET_SEND";
extern const isc::log::MessageID DHCP4_PACKET_SEND_FAIL = "DHCP4_PACKET_SEND_FAIL";
extern const isc::log::MessageID DHCP4_PARSER_COMMIT_EXCEPTION = "DHCP4_PARSER_COMMIT_EXCEPTION";
extern const isc::log::MessageID DHCP4_PARSER_COMMIT_FAIL = "DHCP4_PARSER_COMMIT_FAIL";
extern const isc::log::MessageID DHCP4_PARSER_EXCEPTION = "DHCP4_PARSER_EXCEPTION";
extern const isc::log::MessageID DHCP4_PARSER_FAIL = "DHCP4_PARSER_FAIL";
extern const isc::log::MessageID DHCP4_POST_ALLOCATION_NAME_UPDATE_FAIL = "DHCP4_POST_ALLOCATION_NAME_UPDATE_FAIL";
extern const isc::log::MessageID DHCP4_QUERY_DATA = "DHCP4_QUERY_DATA";
extern const isc::log::MessageID DHCP4_QUERY_LABEL = "DHCP4_QUERY_LABEL";
extern const isc::log::MessageID DHCP4_RECLAIM_EXPIRED_LEASES_FAIL = "DHCP4_RECLAIM_EXPIRED_LEASES_FAIL";
extern const isc::log::MessageID DHCP4_RECOVERED_STASHED_RELAY_AGENT_INFO = "DHCP4_RECOVERED_STASHED_RELAY_AGENT_INFO";
extern const isc::log::MessageID DHCP4_RELEASE = "DHCP4_RELEASE";
extern const isc::log::MessageID DHCP4_RELEASE_DELETED = "DHCP4_RELEASE_DELETED";
extern const isc::log::MessageID DHCP4_RELEASE_EXCEPTION = "DHCP4_RELEASE_EXCEPTION";
extern const isc::log::MessageID DHCP4_RELEASE_EXPIRED = "DHCP4_RELEASE_EXPIRED";
extern const isc::log::MessageID DHCP4_RELEASE_FAIL = "DHCP4_RELEASE_FAIL";
extern const isc::log::MessageID DHCP4_RELEASE_FAIL_NO_LEASE = "DHCP4_RELEASE_FAIL_NO_LEASE";
extern const isc::log::MessageID DHCP4_RELEASE_FAIL_WRONG_CLIENT = "DHCP4_RELEASE_FAIL_WRONG_CLIENT";
extern const isc::log::MessageID DHCP4_REQUEST = "DHCP4_REQUEST";
extern const isc::log::MessageID DHCP4_REQUIRED_CLASS_EVAL_ERROR = "DHCP4_REQUIRED_CLASS_EVAL_ERROR";
extern const isc::log::MessageID DHCP4_REQUIRED_CLASS_EVAL_RESULT = "DHCP4_REQUIRED_CLASS_EVAL_RESULT";
extern const isc::log::MessageID DHCP4_RESERVATIONS_LOOKUP_FIRST_ENABLED = "DHCP4_RESERVATIONS_LOOKUP_FIRST_ENABLED";
extern const isc::log::MessageID DHCP4_RESERVED_HOSTNAME_ASSIGNED = "DHCP4_RESERVED_HOSTNAME_ASSIGNED";
extern const isc::log::MessageID DHCP4_RESPONSE_DATA = "DHCP4_RESPONSE_DATA";
extern const isc::log::MessageID DHCP4_RESPONSE_FQDN_DATA = "DHCP4_RESPONSE_FQDN_DATA";
extern const isc::log::MessageID DHCP4_RESPONSE_HOSTNAME_DATA = "DHCP4_RESPONSE_HOSTNAME_DATA";
extern const isc::log::MessageID DHCP4_RESPONSE_HOSTNAME_GENERATE = "DHCP4_RESPONSE_HOSTNAME_GENERATE";
extern const isc::log::MessageID DHCP4_SERVER_FAILED = "DHCP4_SERVER_FAILED";
extern const isc::log::MessageID DHCP4_SERVER_INITIATED_DECLINE = "DHCP4_SERVER_INITIATED_DECLINE";
extern const isc::log::MessageID DHCP4_SERVER_INITIATED_DECLINE_ADD_FAILED = "DHCP4_SERVER_INITIATED_DECLINE_ADD_FAILED";
extern const isc::log::MessageID DHCP4_SERVER_INITIATED_DECLINE_RESOURCE_BUSY = "DHCP4_SERVER_INITIATED_DECLINE_RESOURCE_BUSY";
extern const isc::log::MessageID DHCP4_SERVER_INITIATED_DECLINE_UPDATE_FAILED = "DHCP4_SERVER_INITIATED_DECLINE_UPDATE_FAILED";
extern const isc::log::MessageID DHCP4_SHUTDOWN = "DHCP4_SHUTDOWN";
extern const isc::log::MessageID DHCP4_SHUTDOWN_REQUEST = "DHCP4_SHUTDOWN_REQUEST";
extern const isc::log::MessageID DHCP4_SRV_CONSTRUCT_ERROR = "DHCP4_SRV_CONSTRUCT_ERROR";
extern const isc::log::MessageID DHCP4_SRV_D2STOP_ERROR = "DHCP4_SRV_D2STOP_ERROR";
extern const isc::log::MessageID DHCP4_SRV_DHCP4O6_ERROR = "DHCP4_SRV_DHCP4O6_ERROR";
extern const isc::log::MessageID DHCP4_SRV_UNLOAD_LIBRARIES_ERROR = "DHCP4_SRV_UNLOAD_LIBRARIES_ERROR";
extern const isc::log::MessageID DHCP4_STARTED = "DHCP4_STARTED";
extern const isc::log::MessageID DHCP4_STARTING = "DHCP4_STARTING";
extern const isc::log::MessageID DHCP4_START_INFO = "DHCP4_START_INFO";
extern const isc::log::MessageID DHCP4_SUBNET_DATA = "DHCP4_SUBNET_DATA";
extern const isc::log::MessageID DHCP4_SUBNET_DYNAMICALLY_CHANGED = "DHCP4_SUBNET_DYNAMICALLY_CHANGED";
extern const isc::log::MessageID DHCP4_SUBNET_SELECTED = "DHCP4_SUBNET_SELECTED";
extern const isc::log::MessageID DHCP4_SUBNET_SELECTION_FAILED = "DHCP4_SUBNET_SELECTION_FAILED";
extern const isc::log::MessageID DHCP4_TESTING_MODE_SEND_TO_SOURCE_ENABLED = "DHCP4_TESTING_MODE_SEND_TO_SOURCE_ENABLED";
extern const isc::log::MessageID DHCP4_UNKNOWN_ADDRESS_REQUESTED = "DHCP4_UNKNOWN_ADDRESS_REQUESTED";
extern const isc::log::MessageID DHCP4_V6_ONLY_PREFERRED_MISSING_IN_ACK = "DHCP4_V6_ONLY_PREFERRED_MISSING_IN_ACK";
extern const isc::log::MessageID DHCP4_V6_ONLY_PREFERRED_MISSING_IN_OFFER = "DHCP4_V6_ONLY_PREFERRED_MISSING_IN_OFFER";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "DHCP4_ALREADY_RUNNING", "%1 already running? %2",
    "DHCP4_BUFFER_RECEIVED", "received buffer from %1:%2 to %3:%4 over interface %5",
    "DHCP4_BUFFER_RECEIVE_FAIL", "error on attempt to receive packet: %1",
    "DHCP4_BUFFER_UNPACK", "parsing buffer received from %1 to %2 over interface %3",
    "DHCP4_BUFFER_WAIT_SIGNAL", "signal received while waiting for next packet",
    "DHCP4_CB_ON_DEMAND_FETCH_UPDATES_FAIL", "error on demand attempt to fetch configuration updates from the configuration backend(s): %1",
    "DHCP4_CB_PERIODIC_FETCH_UPDATES_FAIL", "error on periodic attempt to fetch configuration updates from the configuration backend(s): %1",
    "DHCP4_CB_PERIODIC_FETCH_UPDATES_RETRIES_EXHAUSTED", "maximum number of configuration fetch attempts: 10, has been exhausted without success",
    "DHCP4_CLASSES_ASSIGNED", "%1: client packet has been assigned on %2 message to the following classes: %3",
    "DHCP4_CLASSES_ASSIGNED_AFTER_SUBNET_SELECTION", "%1: client packet has been assigned to the following classes: %2",
    "DHCP4_CLASS_ASSIGNED", "%1: client packet has been assigned to the following class: %2",
    "DHCP4_CLASS_UNCONFIGURED", "%1: client packet belongs to an unconfigured class: %2",
    "DHCP4_CLASS_UNDEFINED", "required class %1 has no definition",
    "DHCP4_CLASS_UNTESTABLE", "required class %1 has no test expression",
    "DHCP4_CLIENTID_IGNORED_FOR_LEASES", "%1: not using client identifier for lease allocation for subnet %2",
    "DHCP4_CLIENT_FQDN_DATA", "%1: Client sent FQDN option: %2",
    "DHCP4_CLIENT_FQDN_PROCESS", "%1: processing Client FQDN option",
    "DHCP4_CLIENT_HOSTNAME_DATA", "%1: client sent Hostname option: %2",
    "DHCP4_CLIENT_HOSTNAME_MALFORMED", "%1: client hostname option malformed: %2",
    "DHCP4_CLIENT_HOSTNAME_PROCESS", "%1: processing client's Hostname option",
    "DHCP4_CLIENT_NAME_PROC_FAIL", "%1: failed to process the fqdn or hostname sent by a client: %2",
    "DHCP4_CONFIG_COMPLETE", "DHCPv4 server has completed configuration: %1",
    "DHCP4_CONFIG_LOAD_FAIL", "configuration error using file: %1, reason: %2",
    "DHCP4_CONFIG_PACKET_QUEUE", "DHCPv4 packet queue info after configuration: %1",
    "DHCP4_CONFIG_RECEIVED", "received configuration %1",
    "DHCP4_CONFIG_START", "DHCPv4 server is processing the following configuration: %1",
    "DHCP4_CONFIG_SYNTAX_WARNING", "configuration syntax warning: %1",
    "DHCP4_CONFIG_UNRECOVERABLE_ERROR", "DHCPv4 server new configuration failed with an error which cannot be recovered",
    "DHCP4_CONFIG_UNSUPPORTED_OBJECT", "DHCPv4 server configuration includes an unsupported object: %1",
    "DHCP4_DB_RECONNECT_DISABLED", "database reconnect is disabled: max-reconnect-tries %1, reconnect-wait-time %2",
    "DHCP4_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "DHCP4_DB_RECONNECT_LOST_CONNECTION", "database connection lost.",
    "DHCP4_DB_RECONNECT_NO_DB_CTL", "unexpected error in database reconnect",
    "DHCP4_DB_RECONNECT_SUCCEEDED", "database connection recovered.",
    "DHCP4_DDNS_REQUEST_SEND_FAILED", "failed sending a request to kea-dhcp-ddns, error: %1,  ncr: %2",
    "DHCP4_DECLINE_FAIL", "%1: error on decline lease for address %2: %3",
    "DHCP4_DECLINE_LEASE", "Received DHCPDECLINE for addr %1 from client %2. The lease will be unavailable for %3 seconds.",
    "DHCP4_DECLINE_LEASE_MISMATCH", "Received DHCPDECLINE for addr %1 from client %2, but the data doesn't match: received hwaddr: %3, lease hwaddr: %4, received client-id: %5, lease client-id: %6",
    "DHCP4_DECLINE_LEASE_NOT_FOUND", "Received DHCPDECLINE for addr %1 from client %2, but no such lease found.",
    "DHCP4_DEFERRED_OPTION_MISSING", "%1: cannot find deferred option code %2 in the query",
    "DHCP4_DEFERRED_OPTION_UNPACK_FAIL", "%1: An error unpacking the deferred option %2: %3",
    "DHCP4_DEVELOPMENT_VERSION", "This software is a development branch of Kea. It is not recommended for production use.",
    "DHCP4_DHCP4O6_BAD_PACKET", "%1: received malformed DHCPv4o6 packet: %2",
    "DHCP4_DHCP4O6_HOOK_SUBNET4_SELECT_DROP", "%1: packet was dropped, because a callout set the next step to 'drop'",
    "DHCP4_DHCP4O6_HOOK_SUBNET4_SELECT_SKIP", "%1: no subnet was selected, because a callout set the next skip flag",
    "DHCP4_DHCP4O6_PACKET_RECEIVED", "received DHCPv4o6 packet from DHCPv4 server (type %1) for %2 on interface %3",
    "DHCP4_DHCP4O6_PACKET_SEND", "%1: trying to send packet %2 (type %3) to %4 port %5 on interface %6 encapsulating %7: %8 (type %9)",
    "DHCP4_DHCP4O6_PACKET_SEND_FAIL", "%1: failed to send DHCPv4o6 packet: %2",
    "DHCP4_DHCP4O6_RECEIVE_FAIL", "failed to receive DHCPv4o6: %1",
    "DHCP4_DHCP4O6_RECEIVING", "receiving DHCPv4o6 packet from DHCPv6 server",
    "DHCP4_DHCP4O6_RESPONSE_DATA", "%1: responding with packet %2 (type %3), packet details: %4",
    "DHCP4_DHCP4O6_SUBNET_DATA", "%1: the selected subnet details: %2",
    "DHCP4_DHCP4O6_SUBNET_SELECTED", "%1: the subnet with ID %2 was selected for client assignments",
    "DHCP4_DHCP4O6_SUBNET_SELECTION_FAILED", "%1: failed to select subnet for the client",
    "DHCP4_DISCOVER", "%1: server is processing DHCPDISCOVER with hint=%2",
    "DHCP4_DYNAMIC_RECONFIGURATION", "initiate server reconfiguration using file: %1, after receiving SIGHUP signal or config-reload command",
    "DHCP4_DYNAMIC_RECONFIGURATION_FAIL", "dynamic server reconfiguration failed with file: %1",
    "DHCP4_DYNAMIC_RECONFIGURATION_SUCCESS", "dynamic server reconfiguration succeeded with file: %1",
    "DHCP4_EMPTY_HOSTNAME", "%1: received empty hostname from the client, skipping processing of this option",
    "DHCP4_FLEX_ID", "%1: flexible identifier generated for incoming packet: %2",
    "DHCP4_GENERATE_FQDN", "%1: client did not send a FQDN or hostname; FQDN will be generated for the client",
    "DHCP4_HOOK_BUFFER_RCVD_DROP", "received buffer from %1 to %2 over interface %3 was dropped because a callout set the drop flag",
    "DHCP4_HOOK_BUFFER_RCVD_SKIP", "received buffer from %1 to %2 over interface %3 is not parsed because a callout set the next step to SKIP.",
    "DHCP4_HOOK_BUFFER_SEND_SKIP", "%1: prepared response is dropped because a callout set the next step to SKIP.",
    "DHCP4_HOOK_DDNS_UPDATE", "A hook has updated the DDNS parameters: hostname %1=>%2, forward update %3=>%4, reverse update %5=>%6",
    "DHCP4_HOOK_DECLINE_SKIP", "Decline4 hook callouts set status to DROP, ignoring packet.",
    "DHCP4_HOOK_LEASE4_OFFER_ARGUMENT_MISSING", "hook callouts did not set an argument as expected %1 for %2",
    "DHCP4_HOOK_LEASE4_OFFER_DROP", "%1: packet is dropped, because a callout set the next step to DROP",
    "DHCP4_HOOK_LEASE4_OFFER_PARK", "%1: packet is parked, because a callout set the next step to PARK",
    "DHCP4_HOOK_LEASE4_OFFER_PARKING_LOT_FULL", "The parked-packet-limit %1, has been reached, dropping query: %2",
    "DHCP4_HOOK_LEASE4_RELEASE_SKIP", "%1: lease was not released because a callout set the next step to SKIP",
    "DHCP4_HOOK_LEASES4_COMMITTED_DROP", "%1: packet is dropped, because a callout set the next step to DROP",
    "DHCP4_HOOK_LEASES4_COMMITTED_PARK", "%1: packet is parked, because a callout set the next step to PARK",
    "DHCP4_HOOK_LEASES4_COMMITTED_PARKING_LOT_FULL", "The parked-packet-limit %1, has been reached, dropping query: %2",
    "DHCP4_HOOK_PACKET_RCVD_SKIP", "%1: packet is dropped, because a callout set the next step to SKIP",
    "DHCP4_HOOK_PACKET_SEND_DROP", "%1: prepared DHCPv4 response was not sent because a callout set the next ste to DROP",
    "DHCP4_HOOK_PACKET_SEND_SKIP", "%1: prepared response is not sent, because a callout set the next stp to SKIP",
    "DHCP4_HOOK_SUBNET4_SELECT_4O6_PARKING_LOT_FULL", "The parked-packet-limit %1, has been reached, dropping query: %2",
    "DHCP4_HOOK_SUBNET4_SELECT_DROP", "%1: packet was dropped, because a callout set the next step to 'drop'",
    "DHCP4_HOOK_SUBNET4_SELECT_PARK", "%1: packet was parked",
    "DHCP4_HOOK_SUBNET4_SELECT_PARKING_LOT_FULL", "The parked-packet-limit %1, has been reached, dropping query: %2",
    "DHCP4_HOOK_SUBNET4_SELECT_SKIP", "%1: no subnet was selected, because a callout set the next skip flag",
    "DHCP4_INFORM_DIRECT_REPLY", "%1: DHCPACK in reply to the DHCPINFORM will be sent directly to %2 over %3",
    "DHCP4_INIT_FAIL", "failed to initialize Kea server: %1",
    "DHCP4_INIT_REBOOT", "%1: client is in INIT-REBOOT state and requests address %2",
    "DHCP4_LEASE_ALLOC", "%1: lease %2 has been allocated for %3 seconds",
    "DHCP4_LEASE_OFFER", "%1: lease %2 will be offered",
    "DHCP4_LEASE_REUSE", "%1: lease %2 has been reused for %3 seconds",
    "DHCP4_MULTI_THREADING_INFO", "enabled: %1, number of threads: %2, queue size: %3",
    "DHCP4_NCR_CREATION_FAILED", "%1: failed to generate name change requests for DNS: %2",
    "DHCP4_NOT_RUNNING", "DHCPv4 server is not running",
    "DHCP4_NO_LEASE_INIT_REBOOT", "%1: no lease for address %2 requested by INIT-REBOOT client",
    "DHCP4_OPEN_SOCKET", "opening service sockets on port %1",
    "DHCP4_OPEN_SOCKETS_FAILED", "maximum number of open service sockets attempts: %1, has been exhausted without success",
    "DHCP4_OPEN_SOCKETS_NO_RECONNECT_CTL", "unexpected error in bind service sockets.",
    "DHCP4_PACKET_DROP_0001", "%1: failed to parse packet from %2 to %3, received over interface %4, reason: %5, %6",
    "DHCP4_PACKET_DROP_0002", "%1, from interface %2: no suitable subnet configured for a direct client",
    "DHCP4_PACKET_DROP_0003", "%1, from interface %2: it contains a foreign server identifier",
    "DHCP4_PACKET_DROP_0004", "%1, from interface %2: missing msg-type option",
    "DHCP4_PACKET_DROP_0005", "%1: unrecognized type %2 in option 53",
    "DHCP4_PACKET_DROP_0006", "%1: unsupported DHCPv4 message type %2",
    "DHCP4_PACKET_DROP_0007", "%1: failed to process packet: %2",
    "DHCP4_PACKET_DROP_0008", "%1: DHCP service is globally disabled",
    "DHCP4_PACKET_DROP_0009", "%1: Option 53 missing (no DHCP message type), is this a BOOTP packet?",
    "DHCP4_PACKET_DROP_0010", "dropped as member of the special class 'DROP': %1, %2",
    "DHCP4_PACKET_DROP_0011", "dropped as sent by the same client than a packet being processed by another thread: dropped %1, %2 by thread %3 as duplicate of %4, %5 processed by %6",
    "DHCP4_PACKET_DROP_0012", "dropped as sent by the same client than a packet being processed by another thread: dropped %1, %2 by thread %3 as duplicate of %4, %5 processed by %6",
    "DHCP4_PACKET_DROP_0013", "dropped as member of the special class 'DROP' after host reservation lookup: %1, %2",
    "DHCP4_PACKET_DROP_0014", "dropped as member of the special class 'DROP' after early global host reservations lookup: %1, %2",
    "DHCP4_PACKET_NAK_0001", "%1: failed to select a subnet for incoming packet, src %2, type %3",
    "DHCP4_PACKET_NAK_0002", "%1: invalid address %2 requested by INIT-REBOOT",
    "DHCP4_PACKET_NAK_0003", "%1: failed to advertise a lease, client sent ciaddr %2, requested-ip-address %3",
    "DHCP4_PACKET_NAK_0004", "%1: failed to grant a lease, client sent ciaddr %2, requested-ip-address %3",
    "DHCP4_PACKET_OPTIONS_SKIPPED", "%1: An error unpacking an option, caused subsequent options to be skipped: %2",
    "DHCP4_PACKET_PACK", "%1: preparing on-wire format of the packet to be sent",
    "DHCP4_PACKET_PACK_FAIL", "%1: preparing on-wire-format of the packet to be sent failed %2",
    "DHCP4_PACKET_PROCESS_EXCEPTION", "%1: exception occurred during packet processing",
    "DHCP4_PACKET_PROCESS_EXCEPTION_MAIN", "exception occurred during packet processing",
    "DHCP4_PACKET_PROCESS_STD_EXCEPTION", "%1: exception occurred during packet processing: %2",
    "DHCP4_PACKET_PROCESS_STD_EXCEPTION_MAIN", "exception occurred during packet processing: %1",
    "DHCP4_PACKET_QUEUE_FULL", "multi-threading packet queue is full",
    "DHCP4_PACKET_RECEIVED", "%1: %2 (type %3) received from %4 to %5 on interface %6",
    "DHCP4_PACKET_SEND", "%1: trying to send packet %2 (type %3) from %4:%5 to %6:%7 on interface %8",
    "DHCP4_PACKET_SEND_FAIL", "%1: failed to send DHCPv4 packet: %2",
    "DHCP4_PARSER_COMMIT_EXCEPTION", "parser failed to commit changes",
    "DHCP4_PARSER_COMMIT_FAIL", "parser failed to commit changes: %1",
    "DHCP4_PARSER_EXCEPTION", "failed to create or run parser for configuration element %1",
    "DHCP4_PARSER_FAIL", "failed to create or run parser for configuration element %1: %2",
    "DHCP4_POST_ALLOCATION_NAME_UPDATE_FAIL", "%1: failed to update hostname %2 in a lease after address allocation: %3",
    "DHCP4_QUERY_DATA", "%1, packet details: %2",
    "DHCP4_QUERY_LABEL", "received query: %1",
    "DHCP4_RECLAIM_EXPIRED_LEASES_FAIL", "failed to reclaim expired leases: %1",
    "DHCP4_RECOVERED_STASHED_RELAY_AGENT_INFO", "recovered for query %1 relay agent option from lease %2: %3",
    "DHCP4_RELEASE", "%1: address %2 was released properly.",
    "DHCP4_RELEASE_DELETED", "%1: address %2 was deleted on release.",
    "DHCP4_RELEASE_EXCEPTION", "%1: while trying to release address %2 an exception occurred: %3",
    "DHCP4_RELEASE_EXPIRED", "%1: address %2 expired on release.",
    "DHCP4_RELEASE_FAIL", "%1: failed to remove lease for address %2",
    "DHCP4_RELEASE_FAIL_NO_LEASE", "%1: client is trying to release non-existing lease %2",
    "DHCP4_RELEASE_FAIL_WRONG_CLIENT", "%1: client is trying to release the lease %2 which belongs to a different client",
    "DHCP4_REQUEST", "%1: server is processing DHCPREQUEST with hint=%2",
    "DHCP4_REQUIRED_CLASS_EVAL_ERROR", "%1: Expression '%2' evaluated to %3",
    "DHCP4_REQUIRED_CLASS_EVAL_RESULT", "%1: Expression '%2' evaluated to %3",
    "DHCP4_RESERVATIONS_LOOKUP_FIRST_ENABLED", "Multi-threading is enabled and host reservations lookup is always performed first.",
    "DHCP4_RESERVED_HOSTNAME_ASSIGNED", "%1: server assigned reserved hostname %2",
    "DHCP4_RESPONSE_DATA", "%1: responding with packet %2 (type %3), packet details: %4",
    "DHCP4_RESPONSE_FQDN_DATA", "%1: including FQDN option in the server's response: %2",
    "DHCP4_RESPONSE_HOSTNAME_DATA", "%1: including Hostname option in the server's response: %2",
    "DHCP4_RESPONSE_HOSTNAME_GENERATE", "%1: server has generated hostname %2 for the client",
    "DHCP4_SERVER_FAILED", "server failed: %1",
    "DHCP4_SERVER_INITIATED_DECLINE", "%1: Lease for addr %2 has been found to be already in use. The lease will be unavailable for %3 seconds.",
    "DHCP4_SERVER_INITIATED_DECLINE_ADD_FAILED", "%1: error adding a lease for address %2",
    "DHCP4_SERVER_INITIATED_DECLINE_RESOURCE_BUSY", "%1: error declining a lease for address %2",
    "DHCP4_SERVER_INITIATED_DECLINE_UPDATE_FAILED", "%1: error updating lease for address %2",
    "DHCP4_SHUTDOWN", "server shutdown",
    "DHCP4_SHUTDOWN_REQUEST", "shutdown of server requested",
    "DHCP4_SRV_CONSTRUCT_ERROR", "error creating Dhcpv4Srv object, reason: %1",
    "DHCP4_SRV_D2STOP_ERROR", "error stopping IO with DHCP_DDNS during shutdown: %1",
    "DHCP4_SRV_DHCP4O6_ERROR", "error stopping IO with DHCPv4o6 during shutdown: %1",
    "DHCP4_SRV_UNLOAD_LIBRARIES_ERROR", "error unloading hooks libraries during shutdown: %1",
    "DHCP4_STARTED", "Kea DHCPv4 server version %1 started",
    "DHCP4_STARTING", "Kea DHCPv4 server version %1 (%2) starting",
    "DHCP4_START_INFO", "pid: %1, server port: %2, client port: %3, verbose: %4",
    "DHCP4_SUBNET_DATA", "%1: the selected subnet details: %2",
    "DHCP4_SUBNET_DYNAMICALLY_CHANGED", "%1: changed selected subnet %2 to subnet %3 from shared network %4 for client assignments",
    "DHCP4_SUBNET_SELECTED", "%1: the subnet with ID %2 was selected for client assignments",
    "DHCP4_SUBNET_SELECTION_FAILED", "%1: failed to select subnet for the client",
    "DHCP4_TESTING_MODE_SEND_TO_SOURCE_ENABLED", "All packets will be send to source address of an incoming packet - use only for testing",
    "DHCP4_UNKNOWN_ADDRESS_REQUESTED", "%1: client requested an unknown address, client sent ciaddr %2, requested-ip-address %3",
    "DHCP4_V6_ONLY_PREFERRED_MISSING_IN_ACK", "v6-only-preferred option missing in 0.0.0.0 reply to query: %1",
    "DHCP4_V6_ONLY_PREFERRED_MISSING_IN_OFFER", "v6-only-preferred option missing in 0.0.0.0 offer to query: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

