// File created from ../../../src/lib/dhcpsrv/dhcpsrv_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID DHCPSRV_CFGMGR_ADD_IFACE = "DHCPSRV_CFGMGR_ADD_IFACE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_ADD_SUBNET4 = "DHCPSRV_CFGMGR_ADD_SUBNET4";
extern const isc::log::MessageID DHCPSRV_CFGMGR_ADD_SUBNET6 = "DHCPSRV_CFGMGR_ADD_SUBNET6";
extern const isc::log::MessageID DHCPSRV_CFGMGR_ALL_IFACES_ACTIVE = "DHCPSRV_CFGMGR_ALL_IFACES_ACTIVE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_CFG_DHCP_DDNS = "DHCPSRV_CFGMGR_CFG_DHCP_DDNS";
extern const isc::log::MessageID DHCPSRV_CFGMGR_CONFIG4_MERGED = "DHCPSRV_CFGMGR_CONFIG4_MERGED";
extern const isc::log::MessageID DHCPSRV_CFGMGR_CONFIG6_MERGED = "DHCPSRV_CFGMGR_CONFIG6_MERGED";
extern const isc::log::MessageID DHCPSRV_CFGMGR_CONFIGURE_SERVERID = "DHCPSRV_CFGMGR_CONFIGURE_SERVERID";
extern const isc::log::MessageID DHCPSRV_CFGMGR_DEL_SUBNET4 = "DHCPSRV_CFGMGR_DEL_SUBNET4";
extern const isc::log::MessageID DHCPSRV_CFGMGR_DEL_SUBNET6 = "DHCPSRV_CFGMGR_DEL_SUBNET6";
extern const isc::log::MessageID DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES = "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES";
extern const isc::log::MessageID DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES_DONE = "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES_DONE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES = "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES";
extern const isc::log::MessageID DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES_DONE = "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES_DONE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_IPV4_RESERVATIONS_NON_UNIQUE_IGNORED = "DHCPSRV_CFGMGR_IPV4_RESERVATIONS_NON_UNIQUE_IGNORED";
extern const isc::log::MessageID DHCPSRV_CFGMGR_IPV6_RESERVATIONS_NON_UNIQUE_IGNORED = "DHCPSRV_CFGMGR_IPV6_RESERVATIONS_NON_UNIQUE_IGNORED";
extern const isc::log::MessageID DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_DETECTED = "DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_DETECTED";
extern const isc::log::MessageID DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_POSSIBLE = "DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_POSSIBLE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_NEW_SUBNET4 = "DHCPSRV_CFGMGR_NEW_SUBNET4";
extern const isc::log::MessageID DHCPSRV_CFGMGR_NEW_SUBNET6 = "DHCPSRV_CFGMGR_NEW_SUBNET6";
extern const isc::log::MessageID DHCPSRV_CFGMGR_OPTION_DUPLICATE = "DHCPSRV_CFGMGR_OPTION_DUPLICATE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_RENEW_GTR_REBIND = "DHCPSRV_CFGMGR_RENEW_GTR_REBIND";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SOCKET_RAW_UNSUPPORTED = "DHCPSRV_CFGMGR_SOCKET_RAW_UNSUPPORTED";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SOCKET_TYPE_DEFAULT = "DHCPSRV_CFGMGR_SOCKET_TYPE_DEFAULT";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SOCKET_TYPE_SELECT = "DHCPSRV_CFGMGR_SOCKET_TYPE_SELECT";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET4 = "DHCPSRV_CFGMGR_SUBNET4";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET4_ADDR = "DHCPSRV_CFGMGR_SUBNET4_ADDR";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET4_IFACE = "DHCPSRV_CFGMGR_SUBNET4_IFACE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET4_RELAY = "DHCPSRV_CFGMGR_SUBNET4_RELAY";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET6 = "DHCPSRV_CFGMGR_SUBNET6";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET6_IFACE = "DHCPSRV_CFGMGR_SUBNET6_IFACE";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET6_IFACE_ID = "DHCPSRV_CFGMGR_SUBNET6_IFACE_ID";
extern const isc::log::MessageID DHCPSRV_CFGMGR_SUBNET6_RELAY = "DHCPSRV_CFGMGR_SUBNET6_RELAY";
extern const isc::log::MessageID DHCPSRV_CFGMGR_UNICAST_LINK_LOCAL = "DHCPSRV_CFGMGR_UNICAST_LINK_LOCAL";
extern const isc::log::MessageID DHCPSRV_CFGMGR_UPDATE_SUBNET4 = "DHCPSRV_CFGMGR_UPDATE_SUBNET4";
extern const isc::log::MessageID DHCPSRV_CFGMGR_UPDATE_SUBNET6 = "DHCPSRV_CFGMGR_UPDATE_SUBNET6";
extern const isc::log::MessageID DHCPSRV_CFGMGR_USE_ADDRESS = "DHCPSRV_CFGMGR_USE_ADDRESS";
extern const isc::log::MessageID DHCPSRV_CFGMGR_USE_ALLOCATOR = "DHCPSRV_CFGMGR_USE_ALLOCATOR";
extern const isc::log::MessageID DHCPSRV_CFGMGR_USE_UNICAST = "DHCPSRV_CFGMGR_USE_UNICAST";
extern const isc::log::MessageID DHCPSRV_CLOSE_DB = "DHCPSRV_CLOSE_DB";
extern const isc::log::MessageID DHCPSRV_DDNS_TTL_PERCENT_TOO_SMALL = "DHCPSRV_DDNS_TTL_PERCENT_TOO_SMALL";
extern const isc::log::MessageID DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET = "DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_ERROR_EXCEPTION = "DHCPSRV_DHCP_DDNS_ERROR_EXCEPTION";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_HANDLER_NULL = "DHCPSRV_DHCP_DDNS_HANDLER_NULL";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_NCR_REJECTED = "DHCPSRV_DHCP_DDNS_NCR_REJECTED";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_NCR_SENT = "DHCPSRV_DHCP_DDNS_NCR_SENT";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_SENDER_STARTED = "DHCPSRV_DHCP_DDNS_SENDER_STARTED";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_SENDER_STOPPED = "DHCPSRV_DHCP_DDNS_SENDER_STOPPED";
extern const isc::log::MessageID DHCPSRV_DHCP_DDNS_SUSPEND_UPDATES = "DHCPSRV_DHCP_DDNS_SUSPEND_UPDATES";
extern const isc::log::MessageID DHCPSRV_EVAL_ERROR = "DHCPSRV_EVAL_ERROR";
extern const isc::log::MessageID DHCPSRV_EVAL_RESULT = "DHCPSRV_EVAL_RESULT";
extern const isc::log::MessageID DHCPSRV_HOOK_LEASE4_RECOVER_SKIP = "DHCPSRV_HOOK_LEASE4_RECOVER_SKIP";
extern const isc::log::MessageID DHCPSRV_HOOK_LEASE4_RENEW_SKIP = "DHCPSRV_HOOK_LEASE4_RENEW_SKIP";
extern const isc::log::MessageID DHCPSRV_HOOK_LEASE4_SELECT_SKIP = "DHCPSRV_HOOK_LEASE4_SELECT_SKIP";
extern const isc::log::MessageID DHCPSRV_HOOK_LEASE6_EXTEND_SKIP = "DHCPSRV_HOOK_LEASE6_EXTEND_SKIP";
extern const isc::log::MessageID DHCPSRV_HOOK_LEASE6_RECOVER_SKIP = "DHCPSRV_HOOK_LEASE6_RECOVER_SKIP";
extern const isc::log::MessageID DHCPSRV_HOOK_LEASE6_SELECT_SKIP = "DHCPSRV_HOOK_LEASE6_SELECT_SKIP";
extern const isc::log::MessageID DHCPSRV_HOST_MGR_DB_OPEN_CONNECTION_WITH_RETRY_FAILED = "DHCPSRV_HOST_MGR_DB_OPEN_CONNECTION_WITH_RETRY_FAILED";
extern const isc::log::MessageID DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL = "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL";
extern const isc::log::MessageID DHCPSRV_LEASE4_EXTENDED_INFO_UPGRADED = "DHCPSRV_LEASE4_EXTENDED_INFO_UPGRADED";
extern const isc::log::MessageID DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL = "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL";
extern const isc::log::MessageID DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED = "DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED";
extern const isc::log::MessageID DHCPSRV_LEASE_MGR_CALLBACK_EXCEPTION = "DHCPSRV_LEASE_MGR_CALLBACK_EXCEPTION";
extern const isc::log::MessageID DHCPSRV_LEASE_MGR_CALLBACK_UNKNOWN_EXCEPTION = "DHCPSRV_LEASE_MGR_CALLBACK_UNKNOWN_EXCEPTION";
extern const isc::log::MessageID DHCPSRV_LEASE_MGR_DB_OPEN_CONNECTION_WITH_RETRY_FAILED = "DHCPSRV_LEASE_MGR_DB_OPEN_CONNECTION_WITH_RETRY_FAILED";
extern const isc::log::MessageID DHCPSRV_LEASE_SANITY_FAIL = "DHCPSRV_LEASE_SANITY_FAIL";
extern const isc::log::MessageID DHCPSRV_LEASE_SANITY_FAIL_DISCARD = "DHCPSRV_LEASE_SANITY_FAIL_DISCARD";
extern const isc::log::MessageID DHCPSRV_LEASE_SANITY_FIXED = "DHCPSRV_LEASE_SANITY_FIXED";
extern const isc::log::MessageID DHCPSRV_MEMFILE_ADD_ADDR4 = "DHCPSRV_MEMFILE_ADD_ADDR4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_ADD_ADDR6 = "DHCPSRV_MEMFILE_ADD_ADDR6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_BEGIN_BUILD_EXTENDED_INFO_TABLES6 = "DHCPSRV_MEMFILE_BEGIN_BUILD_EXTENDED_INFO_TABLES6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_BEGIN_EXTRACT_EXTENDED_INFO4 = "DHCPSRV_MEMFILE_BEGIN_EXTRACT_EXTENDED_INFO4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6 = "DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6_ERROR = "DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6_ERROR";
extern const isc::log::MessageID DHCPSRV_MEMFILE_COMMIT = "DHCPSRV_MEMFILE_COMMIT";
extern const isc::log::MessageID DHCPSRV_MEMFILE_CONVERTING_LEASE_FILES = "DHCPSRV_MEMFILE_CONVERTING_LEASE_FILES";
extern const isc::log::MessageID DHCPSRV_MEMFILE_DB = "DHCPSRV_MEMFILE_DB";
extern const isc::log::MessageID DHCPSRV_MEMFILE_DELETE_ADDR = "DHCPSRV_MEMFILE_DELETE_ADDR";
extern const isc::log::MessageID DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED4 = "DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED6 = "DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED_START = "DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED_START";
extern const isc::log::MessageID DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4 = "DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4_ERROR = "DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4_ERROR";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET4 = "DHCPSRV_MEMFILE_GET4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET6 = "DHCPSRV_MEMFILE_GET6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET6_DUID = "DHCPSRV_MEMFILE_GET6_DUID";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_ADDR4 = "DHCPSRV_MEMFILE_GET_ADDR4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_ADDR6 = "DHCPSRV_MEMFILE_GET_ADDR6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_CLIENTID = "DHCPSRV_MEMFILE_GET_CLIENTID";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_EXPIRED4 = "DHCPSRV_MEMFILE_GET_EXPIRED4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_EXPIRED6 = "DHCPSRV_MEMFILE_GET_EXPIRED6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_HOSTNAME4 = "DHCPSRV_MEMFILE_GET_HOSTNAME4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_HOSTNAME6 = "DHCPSRV_MEMFILE_GET_HOSTNAME6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_HWADDR = "DHCPSRV_MEMFILE_GET_HWADDR";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_IAID_DUID = "DHCPSRV_MEMFILE_GET_IAID_DUID";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_IAID_SUBID_DUID = "DHCPSRV_MEMFILE_GET_IAID_SUBID_DUID";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_PAGE4 = "DHCPSRV_MEMFILE_GET_PAGE4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_PAGE6 = "DHCPSRV_MEMFILE_GET_PAGE6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_RELAYID4 = "DHCPSRV_MEMFILE_GET_RELAYID4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_RELAYID6 = "DHCPSRV_MEMFILE_GET_RELAYID6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_REMOTEID4 = "DHCPSRV_MEMFILE_GET_REMOTEID4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_REMOTEID6 = "DHCPSRV_MEMFILE_GET_REMOTEID6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_SUBID4 = "DHCPSRV_MEMFILE_GET_SUBID4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_SUBID6 = "DHCPSRV_MEMFILE_GET_SUBID6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_SUBID_CLIENTID = "DHCPSRV_MEMFILE_GET_SUBID_CLIENTID";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_SUBID_HWADDR = "DHCPSRV_MEMFILE_GET_SUBID_HWADDR";
extern const isc::log::MessageID DHCPSRV_MEMFILE_GET_SUBID_PAGE6 = "DHCPSRV_MEMFILE_GET_SUBID_PAGE6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LEASE_FILE_LOAD = "DHCPSRV_MEMFILE_LEASE_FILE_LOAD";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LEASE_LOAD = "DHCPSRV_MEMFILE_LEASE_LOAD";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LEASE_LOAD_ROW_ERROR = "DHCPSRV_MEMFILE_LEASE_LOAD_ROW_ERROR";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_EXECUTE = "DHCPSRV_MEMFILE_LFC_EXECUTE";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_LEASE_FILE_RENAME_FAIL = "DHCPSRV_MEMFILE_LFC_LEASE_FILE_RENAME_FAIL";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_LEASE_FILE_REOPEN_FAIL = "DHCPSRV_MEMFILE_LFC_LEASE_FILE_REOPEN_FAIL";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_SETUP = "DHCPSRV_MEMFILE_LFC_SETUP";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_SPAWN_FAIL = "DHCPSRV_MEMFILE_LFC_SPAWN_FAIL";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_START = "DHCPSRV_MEMFILE_LFC_START";
extern const isc::log::MessageID DHCPSRV_MEMFILE_LFC_UNREGISTER_TIMER_FAILED = "DHCPSRV_MEMFILE_LFC_UNREGISTER_TIMER_FAILED";
extern const isc::log::MessageID DHCPSRV_MEMFILE_NEEDS_DOWNGRADING = "DHCPSRV_MEMFILE_NEEDS_DOWNGRADING";
extern const isc::log::MessageID DHCPSRV_MEMFILE_NEEDS_UPGRADING = "DHCPSRV_MEMFILE_NEEDS_UPGRADING";
extern const isc::log::MessageID DHCPSRV_MEMFILE_NO_STORAGE = "DHCPSRV_MEMFILE_NO_STORAGE";
extern const isc::log::MessageID DHCPSRV_MEMFILE_READ_HWADDR_FAIL = "DHCPSRV_MEMFILE_READ_HWADDR_FAIL";
extern const isc::log::MessageID DHCPSRV_MEMFILE_ROLLBACK = "DHCPSRV_MEMFILE_ROLLBACK";
extern const isc::log::MessageID DHCPSRV_MEMFILE_UPDATE_ADDR4 = "DHCPSRV_MEMFILE_UPDATE_ADDR4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_UPDATE_ADDR6 = "DHCPSRV_MEMFILE_UPDATE_ADDR6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_WIPE_LEASES4 = "DHCPSRV_MEMFILE_WIPE_LEASES4";
extern const isc::log::MessageID DHCPSRV_MEMFILE_WIPE_LEASES4_FINISHED = "DHCPSRV_MEMFILE_WIPE_LEASES4_FINISHED";
extern const isc::log::MessageID DHCPSRV_MEMFILE_WIPE_LEASES6 = "DHCPSRV_MEMFILE_WIPE_LEASES6";
extern const isc::log::MessageID DHCPSRV_MEMFILE_WIPE_LEASES6_FINISHED = "DHCPSRV_MEMFILE_WIPE_LEASES6_FINISHED";
extern const isc::log::MessageID DHCPSRV_MT_DISABLED_QUEUE_CONTROL = "DHCPSRV_MT_DISABLED_QUEUE_CONTROL";
extern const isc::log::MessageID DHCPSRV_MULTIPLE_RAW_SOCKETS_PER_IFACE = "DHCPSRV_MULTIPLE_RAW_SOCKETS_PER_IFACE";
extern const isc::log::MessageID DHCPSRV_MYSQL_ADD_ADDR4 = "DHCPSRV_MYSQL_ADD_ADDR4";
extern const isc::log::MessageID DHCPSRV_MYSQL_ADD_ADDR6 = "DHCPSRV_MYSQL_ADD_ADDR6";
extern const isc::log::MessageID DHCPSRV_MYSQL_COMMIT = "DHCPSRV_MYSQL_COMMIT";
extern const isc::log::MessageID DHCPSRV_MYSQL_DB = "DHCPSRV_MYSQL_DB";
extern const isc::log::MessageID DHCPSRV_MYSQL_DELETED_EXPIRED_RECLAIMED = "DHCPSRV_MYSQL_DELETED_EXPIRED_RECLAIMED";
extern const isc::log::MessageID DHCPSRV_MYSQL_DELETE_ADDR = "DHCPSRV_MYSQL_DELETE_ADDR";
extern const isc::log::MessageID DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED4 = "DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED4";
extern const isc::log::MessageID DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED6 = "DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET4 = "DHCPSRV_MYSQL_GET4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET6 = "DHCPSRV_MYSQL_GET6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_ADDR4 = "DHCPSRV_MYSQL_GET_ADDR4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_ADDR6 = "DHCPSRV_MYSQL_GET_ADDR6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_CLIENTID = "DHCPSRV_MYSQL_GET_CLIENTID";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_DUID = "DHCPSRV_MYSQL_GET_DUID";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_EXPIRED4 = "DHCPSRV_MYSQL_GET_EXPIRED4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_EXPIRED6 = "DHCPSRV_MYSQL_GET_EXPIRED6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_HOSTNAME4 = "DHCPSRV_MYSQL_GET_HOSTNAME4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_HOSTNAME6 = "DHCPSRV_MYSQL_GET_HOSTNAME6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_HWADDR = "DHCPSRV_MYSQL_GET_HWADDR";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_IAID_DUID = "DHCPSRV_MYSQL_GET_IAID_DUID";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_IAID_SUBID_DUID = "DHCPSRV_MYSQL_GET_IAID_SUBID_DUID";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_PAGE4 = "DHCPSRV_MYSQL_GET_PAGE4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_PAGE6 = "DHCPSRV_MYSQL_GET_PAGE6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_RELAYID4 = "DHCPSRV_MYSQL_GET_RELAYID4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_RELAYID6 = "DHCPSRV_MYSQL_GET_RELAYID6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_REMOTEID4 = "DHCPSRV_MYSQL_GET_REMOTEID4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_REMOTEID6 = "DHCPSRV_MYSQL_GET_REMOTEID6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_SUBID4 = "DHCPSRV_MYSQL_GET_SUBID4";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_SUBID6 = "DHCPSRV_MYSQL_GET_SUBID6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_SUBID_CLIENTID = "DHCPSRV_MYSQL_GET_SUBID_CLIENTID";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_SUBID_HWADDR = "DHCPSRV_MYSQL_GET_SUBID_HWADDR";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_SUBID_PAGE6 = "DHCPSRV_MYSQL_GET_SUBID_PAGE6";
extern const isc::log::MessageID DHCPSRV_MYSQL_GET_VERSION = "DHCPSRV_MYSQL_GET_VERSION";
extern const isc::log::MessageID DHCPSRV_MYSQL_HOST_DB = "DHCPSRV_MYSQL_HOST_DB";
extern const isc::log::MessageID DHCPSRV_MYSQL_HOST_DB_GET_VERSION = "DHCPSRV_MYSQL_HOST_DB_GET_VERSION";
extern const isc::log::MessageID DHCPSRV_MYSQL_HOST_DB_READONLY = "DHCPSRV_MYSQL_HOST_DB_READONLY";
extern const isc::log::MessageID DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED = "DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE = "DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID DHCPSRV_MYSQL_HOST_DB_RECONNECT_FAILED = "DHCPSRV_MYSQL_HOST_DB_RECONNECT_FAILED";
extern const isc::log::MessageID DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED = "DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE = "DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID DHCPSRV_MYSQL_LEASE_DB_RECONNECT_FAILED = "DHCPSRV_MYSQL_LEASE_DB_RECONNECT_FAILED";
extern const isc::log::MessageID DHCPSRV_MYSQL_NEGATIVE_LEASES_STAT = "DHCPSRV_MYSQL_NEGATIVE_LEASES_STAT";
extern const isc::log::MessageID DHCPSRV_MYSQL_NO_TLS = "DHCPSRV_MYSQL_NO_TLS";
extern const isc::log::MessageID DHCPSRV_MYSQL_ROLLBACK = "DHCPSRV_MYSQL_ROLLBACK";
extern const isc::log::MessageID DHCPSRV_MYSQL_TLS_CIPHER = "DHCPSRV_MYSQL_TLS_CIPHER";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPDATE_ADDR4 = "DHCPSRV_MYSQL_UPDATE_ADDR4";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPDATE_ADDR6 = "DHCPSRV_MYSQL_UPDATE_ADDR6";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4 = "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_ERROR = "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_ERROR";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_PAGE = "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_PAGE";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6 = "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6_ERROR = "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6_ERROR";
extern const isc::log::MessageID DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6_PAGE = "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6_PAGE";
extern const isc::log::MessageID DHCPSRV_NOTYPE_DB = "DHCPSRV_NOTYPE_DB";
extern const isc::log::MessageID DHCPSRV_NO_SOCKETS_OPEN = "DHCPSRV_NO_SOCKETS_OPEN";
extern const isc::log::MessageID DHCPSRV_OPEN_SOCKET_FAIL = "DHCPSRV_OPEN_SOCKET_FAIL";
extern const isc::log::MessageID DHCPSRV_PGSQL_ADD_ADDR4 = "DHCPSRV_PGSQL_ADD_ADDR4";
extern const isc::log::MessageID DHCPSRV_PGSQL_ADD_ADDR6 = "DHCPSRV_PGSQL_ADD_ADDR6";
extern const isc::log::MessageID DHCPSRV_PGSQL_COMMIT = "DHCPSRV_PGSQL_COMMIT";
extern const isc::log::MessageID DHCPSRV_PGSQL_DB = "DHCPSRV_PGSQL_DB";
extern const isc::log::MessageID DHCPSRV_PGSQL_DELETE_ADDR = "DHCPSRV_PGSQL_DELETE_ADDR";
extern const isc::log::MessageID DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED4 = "DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED4";
extern const isc::log::MessageID DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED6 = "DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET4 = "DHCPSRV_PGSQL_GET4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET6 = "DHCPSRV_PGSQL_GET6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_ADDR4 = "DHCPSRV_PGSQL_GET_ADDR4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_ADDR6 = "DHCPSRV_PGSQL_GET_ADDR6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_CLIENTID = "DHCPSRV_PGSQL_GET_CLIENTID";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_DUID = "DHCPSRV_PGSQL_GET_DUID";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_EXPIRED4 = "DHCPSRV_PGSQL_GET_EXPIRED4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_EXPIRED6 = "DHCPSRV_PGSQL_GET_EXPIRED6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_HOSTNAME4 = "DHCPSRV_PGSQL_GET_HOSTNAME4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_HOSTNAME6 = "DHCPSRV_PGSQL_GET_HOSTNAME6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_HWADDR = "DHCPSRV_PGSQL_GET_HWADDR";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_IAID_DUID = "DHCPSRV_PGSQL_GET_IAID_DUID";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_IAID_SUBID_DUID = "DHCPSRV_PGSQL_GET_IAID_SUBID_DUID";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_PAGE4 = "DHCPSRV_PGSQL_GET_PAGE4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_PAGE6 = "DHCPSRV_PGSQL_GET_PAGE6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_RELAYID4 = "DHCPSRV_PGSQL_GET_RELAYID4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_RELAYID6 = "DHCPSRV_PGSQL_GET_RELAYID6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_REMOTEID4 = "DHCPSRV_PGSQL_GET_REMOTEID4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_REMOTEID6 = "DHCPSRV_PGSQL_GET_REMOTEID6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_SUBID4 = "DHCPSRV_PGSQL_GET_SUBID4";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_SUBID6 = "DHCPSRV_PGSQL_GET_SUBID6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_SUBID_CLIENTID = "DHCPSRV_PGSQL_GET_SUBID_CLIENTID";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_SUBID_HWADDR = "DHCPSRV_PGSQL_GET_SUBID_HWADDR";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_SUBID_PAGE6 = "DHCPSRV_PGSQL_GET_SUBID_PAGE6";
extern const isc::log::MessageID DHCPSRV_PGSQL_GET_VERSION = "DHCPSRV_PGSQL_GET_VERSION";
extern const isc::log::MessageID DHCPSRV_PGSQL_HOST_DB = "DHCPSRV_PGSQL_HOST_DB";
extern const isc::log::MessageID DHCPSRV_PGSQL_HOST_DB_GET_VERSION = "DHCPSRV_PGSQL_HOST_DB_GET_VERSION";
extern const isc::log::MessageID DHCPSRV_PGSQL_HOST_DB_READONLY = "DHCPSRV_PGSQL_HOST_DB_READONLY";
extern const isc::log::MessageID DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED = "DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE = "DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID DHCPSRV_PGSQL_HOST_DB_RECONNECT_FAILED = "DHCPSRV_PGSQL_HOST_DB_RECONNECT_FAILED";
extern const isc::log::MessageID DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED = "DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE = "DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID DHCPSRV_PGSQL_LEASE_DB_RECONNECT_FAILED = "DHCPSRV_PGSQL_LEASE_DB_RECONNECT_FAILED";
extern const isc::log::MessageID DHCPSRV_PGSQL_NEGATIVE_LEASES_STAT = "DHCPSRV_PGSQL_NEGATIVE_LEASES_STAT";
extern const isc::log::MessageID DHCPSRV_PGSQL_NO_TLS_SUPPORT = "DHCPSRV_PGSQL_NO_TLS_SUPPORT";
extern const isc::log::MessageID DHCPSRV_PGSQL_ROLLBACK = "DHCPSRV_PGSQL_ROLLBACK";
extern const isc::log::MessageID DHCPSRV_PGSQL_TLS_SUPPORT = "DHCPSRV_PGSQL_TLS_SUPPORT";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPDATE_ADDR4 = "DHCPSRV_PGSQL_UPDATE_ADDR4";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPDATE_ADDR6 = "DHCPSRV_PGSQL_UPDATE_ADDR6";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4 = "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_ERROR = "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_ERROR";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_PAGE = "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_PAGE";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6 = "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_ERROR = "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_ERROR";
extern const isc::log::MessageID DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_PAGE = "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_PAGE";
extern const isc::log::MessageID DHCPSRV_QUEUE_NCR = "DHCPSRV_QUEUE_NCR";
extern const isc::log::MessageID DHCPSRV_QUEUE_NCR_FAILED = "DHCPSRV_QUEUE_NCR_FAILED";
extern const isc::log::MessageID DHCPSRV_QUEUE_NCR_SKIP = "DHCPSRV_QUEUE_NCR_SKIP";
extern const isc::log::MessageID DHCPSRV_SUBNET4O6_SELECT_FAILED = "DHCPSRV_SUBNET4O6_SELECT_FAILED";
extern const isc::log::MessageID DHCPSRV_SUBNET4_SELECT_BY_ADDRESS_NO_MATCH = "DHCPSRV_SUBNET4_SELECT_BY_ADDRESS_NO_MATCH";
extern const isc::log::MessageID DHCPSRV_SUBNET4_SELECT_BY_INTERFACE_NO_MATCH = "DHCPSRV_SUBNET4_SELECT_BY_INTERFACE_NO_MATCH";
extern const isc::log::MessageID DHCPSRV_SUBNET4_SELECT_BY_RELAY_ADDRESS_NO_MATCH = "DHCPSRV_SUBNET4_SELECT_BY_RELAY_ADDRESS_NO_MATCH";
extern const isc::log::MessageID DHCPSRV_SUBNET4_SELECT_NO_RAI_OPTIONS = "DHCPSRV_SUBNET4_SELECT_NO_RAI_OPTIONS";
extern const isc::log::MessageID DHCPSRV_SUBNET4_SELECT_NO_RELAY_ADDRESS = "DHCPSRV_SUBNET4_SELECT_NO_RELAY_ADDRESS";
extern const isc::log::MessageID DHCPSRV_SUBNET4_SELECT_NO_USABLE_ADDRESS = "DHCPSRV_SUBNET4_SELECT_NO_USABLE_ADDRESS";
extern const isc::log::MessageID DHCPSRV_SUBNET6_SELECT_BY_ADDRESS_NO_MATCH = "DHCPSRV_SUBNET6_SELECT_BY_ADDRESS_NO_MATCH";
extern const isc::log::MessageID DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_ID_NO_MATCH = "DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_ID_NO_MATCH";
extern const isc::log::MessageID DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_NO_MATCH = "DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_NO_MATCH";
extern const isc::log::MessageID DHCPSRV_TEMPLATE_EVAL_ERROR = "DHCPSRV_TEMPLATE_EVAL_ERROR";
extern const isc::log::MessageID DHCPSRV_TEMPLATE_EVAL_RESULT = "DHCPSRV_TEMPLATE_EVAL_RESULT";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_CALLBACK_FAILED = "DHCPSRV_TIMERMGR_CALLBACK_FAILED";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_REGISTER_TIMER = "DHCPSRV_TIMERMGR_REGISTER_TIMER";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_RUN_TIMER_OPERATION = "DHCPSRV_TIMERMGR_RUN_TIMER_OPERATION";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_START_TIMER = "DHCPSRV_TIMERMGR_START_TIMER";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_STOP_TIMER = "DHCPSRV_TIMERMGR_STOP_TIMER";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_UNREGISTER_ALL_TIMERS = "DHCPSRV_TIMERMGR_UNREGISTER_ALL_TIMERS";
extern const isc::log::MessageID DHCPSRV_TIMERMGR_UNREGISTER_TIMER = "DHCPSRV_TIMERMGR_UNREGISTER_TIMER";
extern const isc::log::MessageID DHCPSRV_UNKNOWN_DB = "DHCPSRV_UNKNOWN_DB";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "DHCPSRV_CFGMGR_ADD_IFACE", "listening on interface %1",
    "DHCPSRV_CFGMGR_ADD_SUBNET4", "adding subnet %1",
    "DHCPSRV_CFGMGR_ADD_SUBNET6", "adding subnet %1",
    "DHCPSRV_CFGMGR_ALL_IFACES_ACTIVE", "enabling listening on all interfaces",
    "DHCPSRV_CFGMGR_CFG_DHCP_DDNS", "Setting DHCP-DDNS configuration to: %1",
    "DHCPSRV_CFGMGR_CONFIG4_MERGED", "Configuration backend data has been merged.",
    "DHCPSRV_CFGMGR_CONFIG6_MERGED", "Configuration backend data has been merged.",
    "DHCPSRV_CFGMGR_CONFIGURE_SERVERID", "server configuration includes specification of a server identifier",
    "DHCPSRV_CFGMGR_DEL_SUBNET4", "IPv4 subnet %1 removed",
    "DHCPSRV_CFGMGR_DEL_SUBNET6", "IPv6 subnet %1 removed",
    "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES", "populating free address leases for the FLQ allocator in subnet %1; it can take a while!",
    "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_ADDRESS_LEASES_DONE", "populated %1 free address leases for the FLQ allocator in subnet %2 in %3",
    "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES", "populating free prefix leases for the FLQ allocator in subnet %1; it can take a while!",
    "DHCPSRV_CFGMGR_FLQ_POPULATE_FREE_PREFIX_LEASES_DONE", "populated %1 free prefix leases for the FLQ allocator in subnet %2 completed in %3",
    "DHCPSRV_CFGMGR_IPV4_RESERVATIONS_NON_UNIQUE_IGNORED", "ignoring \"ip-reservations-unique\" setting because at least one of the host database backends does not support non-unique IP reservations in a subnet",
    "DHCPSRV_CFGMGR_IPV6_RESERVATIONS_NON_UNIQUE_IGNORED", "ignoring \"ip-reservations-unique\" setting because at least one of the host database backends does not support non unique IP reservations in a subnet",
    "DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_DETECTED", "the \"ip-reservations-unique\" flag is set to true and multiple reservations for the IP address %1 in subnet %2 are not allowed causing error: %3",
    "DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_POSSIBLE", "setting \"ip-reservations-unique\" from false to true poses a risk that some host backends may still contain multiple reservations for the same IP address",
    "DHCPSRV_CFGMGR_NEW_SUBNET4", "a new subnet has been added to configuration: %1",
    "DHCPSRV_CFGMGR_NEW_SUBNET6", "a new subnet has been added to configuration: %1",
    "DHCPSRV_CFGMGR_OPTION_DUPLICATE", "multiple options with the code: %1 added to the subnet: %2",
    "DHCPSRV_CFGMGR_RENEW_GTR_REBIND", "in %1, the value of renew-timer %2 is greater than the value of rebind-timer %3, ignoring renew-timer",
    "DHCPSRV_CFGMGR_SOCKET_RAW_UNSUPPORTED", "use of raw sockets is unsupported on this OS, UDP sockets will be used",
    "DHCPSRV_CFGMGR_SOCKET_TYPE_DEFAULT", "\"dhcp-socket-type\" not specified , using default socket type %1",
    "DHCPSRV_CFGMGR_SOCKET_TYPE_SELECT", "using socket type %1",
    "DHCPSRV_CFGMGR_SUBNET4", "retrieved subnet %1 for address hint %2",
    "DHCPSRV_CFGMGR_SUBNET4_ADDR", "selected subnet %1 for packet received by matching address %2",
    "DHCPSRV_CFGMGR_SUBNET4_IFACE", "selected subnet %1 for packet received over interface %2",
    "DHCPSRV_CFGMGR_SUBNET4_RELAY", "selected subnet %1, because of matching relay addr %2",
    "DHCPSRV_CFGMGR_SUBNET6", "retrieved subnet %1 for address hint %2",
    "DHCPSRV_CFGMGR_SUBNET6_IFACE", "selected subnet %1 for packet received over interface %2",
    "DHCPSRV_CFGMGR_SUBNET6_IFACE_ID", "selected subnet %1 (interface-id match) for incoming packet",
    "DHCPSRV_CFGMGR_SUBNET6_RELAY", "selected subnet %1, because of matching relay addr %2",
    "DHCPSRV_CFGMGR_UNICAST_LINK_LOCAL", "specified link local address %1 for unicast traffic on interface %2",
    "DHCPSRV_CFGMGR_UPDATE_SUBNET4", "updating subnet %1 (result %2)",
    "DHCPSRV_CFGMGR_UPDATE_SUBNET6", "updating subnet %1 (result %2)",
    "DHCPSRV_CFGMGR_USE_ADDRESS", "listening on address %1, on interface %2",
    "DHCPSRV_CFGMGR_USE_ALLOCATOR", "using the %1 allocator for %2 leases in subnet %3",
    "DHCPSRV_CFGMGR_USE_UNICAST", "listening on unicast address %1, on interface %2",
    "DHCPSRV_CLOSE_DB", "closing currently open %1 database",
    "DHCPSRV_DDNS_TTL_PERCENT_TOO_SMALL", "ddns-ttl-percent %1 of lease lifetime %2 is too small, ignoring it",
    "DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET", "received bad DHCPv4o6 packet: %1",
    "DHCPSRV_DHCP_DDNS_ERROR_EXCEPTION", "error handler for DHCP_DDNS IO generated an expected exception: %1",
    "DHCPSRV_DHCP_DDNS_HANDLER_NULL", "error handler for DHCP_DDNS IO is not set.",
    "DHCPSRV_DHCP_DDNS_NCR_REJECTED", "NameChangeRequest rejected by the sender: %1, ncr: %2",
    "DHCPSRV_DHCP_DDNS_NCR_SENT", "NameChangeRequest sent to kea-dhcp-ddns: %1",
    "DHCPSRV_DHCP_DDNS_SENDER_STARTED", "NameChangeRequest sender has been started: %1",
    "DHCPSRV_DHCP_DDNS_SENDER_STOPPED", "NameChangeRequest sender has been stopped.",
    "DHCPSRV_DHCP_DDNS_SUSPEND_UPDATES", "DHCP_DDNS updates are being suspended.",
    "DHCPSRV_EVAL_ERROR", "%1: Expression '%2' evaluated to %3",
    "DHCPSRV_EVAL_RESULT", "%1: Expression '%2' evaluated to %3",
    "DHCPSRV_HOOK_LEASE4_RECOVER_SKIP", "DHCPv4 lease %1 was not recovered from the declined state because a callout set the skip status.",
    "DHCPSRV_HOOK_LEASE4_RENEW_SKIP", "DHCPv4 lease was not renewed because a callout set the skip flag.",
    "DHCPSRV_HOOK_LEASE4_SELECT_SKIP", "Lease4 creation was skipped, because of callout skip flag.",
    "DHCPSRV_HOOK_LEASE6_EXTEND_SKIP", "DHCPv6 lease lifetime was not extended because a callout set the skip flag for message %1",
    "DHCPSRV_HOOK_LEASE6_RECOVER_SKIP", "DHCPv6 lease %1 was not recovered from declined state because a callout set the skip status.",
    "DHCPSRV_HOOK_LEASE6_SELECT_SKIP", "Lease6 (non-temporary) creation was skipped, because of callout skip flag.",
    "DHCPSRV_HOST_MGR_DB_OPEN_CONNECTION_WITH_RETRY_FAILED", "Failed to connect to database: %1 with error: %2",
    "DHCPSRV_LEASE4_EXTENDED_INFO_SANITY_FAIL", "extended info for lease %1 failed checks (%2)",
    "DHCPSRV_LEASE4_EXTENDED_INFO_UPGRADED", "extended info for lease %1 was upgraded",
    "DHCPSRV_LEASE6_EXTENDED_INFO_SANITY_FAIL", "extended info for lease %1 failed checks (%2)",
    "DHCPSRV_LEASE6_EXTENDED_INFO_UPGRADED", "extended info for lease %1 was upgraded",
    "DHCPSRV_LEASE_MGR_CALLBACK_EXCEPTION", "exception occurred in a lease manager callback for callback type %1, subnet id %2, and lease %3: %4",
    "DHCPSRV_LEASE_MGR_CALLBACK_UNKNOWN_EXCEPTION", "unknown exception occurred in a lease manager callback for callback type %1, subnet id %2, and lease %3",
    "DHCPSRV_LEASE_MGR_DB_OPEN_CONNECTION_WITH_RETRY_FAILED", "Failed to connect to database: %1 with error: %2",
    "DHCPSRV_LEASE_SANITY_FAIL", "The lease %1 with subnet-id %2 failed subnet-id checks (%3).",
    "DHCPSRV_LEASE_SANITY_FAIL_DISCARD", "The lease %1 with subnet-id %2 failed subnet-id checks (%3) and was dropped.",
    "DHCPSRV_LEASE_SANITY_FIXED", "The lease %1 with subnet-id %2 failed subnet-id checks, but was corrected to subnet-id %3.",
    "DHCPSRV_MEMFILE_ADD_ADDR4", "adding IPv4 lease with address %1",
    "DHCPSRV_MEMFILE_ADD_ADDR6", "adding IPv6 lease with address %1",
    "DHCPSRV_MEMFILE_BEGIN_BUILD_EXTENDED_INFO_TABLES6", "building extended info tables with %1 sanity check level, tables %2",
    "DHCPSRV_MEMFILE_BEGIN_EXTRACT_EXTENDED_INFO4", "extract extended info with %1 sanity check level%2",
    "DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6", "building extended info tables saw %1 leases, extended info sanity checks modified %2 leases and %3 leases were entered into tables",
    "DHCPSRV_MEMFILE_BUILD_EXTENDED_INFO_TABLES6_ERROR", "building extended info tables got an exception on the lease for %1: %2",
    "DHCPSRV_MEMFILE_COMMIT", "committing to memory file database",
    "DHCPSRV_MEMFILE_CONVERTING_LEASE_FILES", "running LFC now to convert lease files to the current schema: %1.%2",
    "DHCPSRV_MEMFILE_DB", "opening memory file lease database: %1",
    "DHCPSRV_MEMFILE_DELETE_ADDR", "deleting lease for address %1",
    "DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED4", "deleting reclaimed IPv4 leases that expired more than %1 seconds ago",
    "DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED6", "deleting reclaimed IPv6 leases that expired more than %1 seconds ago",
    "DHCPSRV_MEMFILE_DELETE_EXPIRED_RECLAIMED_START", "starting deletion of %1 expired-reclaimed leases",
    "DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4", "extracting extended info saw %1 leases, extended info sanity checks modified %2 / updated %3 leases and %4 leases have relay or remote id",
    "DHCPSRV_MEMFILE_EXTRACT_EXTENDED_INFO4_ERROR", "extracting extended info got an exception on the lease for %1: %2",
    "DHCPSRV_MEMFILE_GET4", "obtaining all IPv4 leases",
    "DHCPSRV_MEMFILE_GET6", "obtaining all IPv6 leases",
    "DHCPSRV_MEMFILE_GET6_DUID", "obtaining IPv6 leases for DUID %1",
    "DHCPSRV_MEMFILE_GET_ADDR4", "obtaining IPv4 lease for address %1",
    "DHCPSRV_MEMFILE_GET_ADDR6", "obtaining IPv6 lease for address %1 and lease type %2",
    "DHCPSRV_MEMFILE_GET_CLIENTID", "obtaining IPv4 leases for client ID %1",
    "DHCPSRV_MEMFILE_GET_EXPIRED4", "obtaining maximum %1 of expired IPv4 leases",
    "DHCPSRV_MEMFILE_GET_EXPIRED6", "obtaining maximum %1 of expired IPv6 leases",
    "DHCPSRV_MEMFILE_GET_HOSTNAME4", "obtaining IPv4 leases for hostname %1",
    "DHCPSRV_MEMFILE_GET_HOSTNAME6", "obtaining IPv6 leases for hostname %1",
    "DHCPSRV_MEMFILE_GET_HWADDR", "obtaining IPv4 leases for hardware address %1",
    "DHCPSRV_MEMFILE_GET_IAID_DUID", "obtaining IPv6 leases for IAID %1 and DUID %2 and lease type %3",
    "DHCPSRV_MEMFILE_GET_IAID_SUBID_DUID", "obtaining IPv6 leases for IAID %1, Subnet ID %2, DUID %3 and lease type %4",
    "DHCPSRV_MEMFILE_GET_PAGE4", "obtaining at most %1 IPv4 leases starting from address %2",
    "DHCPSRV_MEMFILE_GET_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2",
    "DHCPSRV_MEMFILE_GET_RELAYID4", "obtaining at most %1 IPv4 leases starting from address %2 with relay id %3 and cltt between %4 and %5",
    "DHCPSRV_MEMFILE_GET_RELAYID6", "obtaining at most %1 IPv6 leases starting from address %2 with relay id %3",
    "DHCPSRV_MEMFILE_GET_REMOTEID4", "obtaining at most %1 IPv4 leases starting from address %2 with remote id %3 and cltt between %4 and %5",
    "DHCPSRV_MEMFILE_GET_REMOTEID6", "obtaining at most %1 IPv6 leases starting from address %2 with remote id %3",
    "DHCPSRV_MEMFILE_GET_SUBID4", "obtaining IPv4 leases for subnet ID %1",
    "DHCPSRV_MEMFILE_GET_SUBID6", "obtaining IPv6 leases for subnet ID %1",
    "DHCPSRV_MEMFILE_GET_SUBID_CLIENTID", "obtaining IPv4 lease for subnet ID %1 and client ID %2",
    "DHCPSRV_MEMFILE_GET_SUBID_HWADDR", "obtaining IPv4 lease for subnet ID %1 and hardware address %2",
    "DHCPSRV_MEMFILE_GET_SUBID_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2 for subnet ID %3",
    "DHCPSRV_MEMFILE_LEASE_FILE_LOAD", "loading leases from file %1",
    "DHCPSRV_MEMFILE_LEASE_LOAD", "loading lease %1",
    "DHCPSRV_MEMFILE_LEASE_LOAD_ROW_ERROR", "discarding row %1, error: %2",
    "DHCPSRV_MEMFILE_LFC_EXECUTE", "executing Lease File Cleanup using: %1",
    "DHCPSRV_MEMFILE_LFC_LEASE_FILE_RENAME_FAIL", "failed to rename the current lease file %1 to %2, reason: %3",
    "DHCPSRV_MEMFILE_LFC_LEASE_FILE_REOPEN_FAIL", "failed to reopen lease file %1 after preparing input file for lease file cleanup, reason: %2, new leases will not persist!",
    "DHCPSRV_MEMFILE_LFC_SETUP", "setting up the Lease File Cleanup interval to %1 sec",
    "DHCPSRV_MEMFILE_LFC_SPAWN_FAIL", "lease file cleanup failed to run because kea-lfc process couldn't be spawned",
    "DHCPSRV_MEMFILE_LFC_START", "starting Lease File Cleanup",
    "DHCPSRV_MEMFILE_LFC_UNREGISTER_TIMER_FAILED", "failed to unregister timer 'memfile-lfc': %1",
    "DHCPSRV_MEMFILE_NEEDS_DOWNGRADING", "version of lease file: %1 schema is later than version %2",
    "DHCPSRV_MEMFILE_NEEDS_UPGRADING", "version of lease file: %1 schema is earlier than version %2",
    "DHCPSRV_MEMFILE_NO_STORAGE", "running in non-persistent mode, leases will be lost after restart",
    "DHCPSRV_MEMFILE_READ_HWADDR_FAIL", "failed to read hardware address from lease file: %1",
    "DHCPSRV_MEMFILE_ROLLBACK", "rolling back memory file database",
    "DHCPSRV_MEMFILE_UPDATE_ADDR4", "updating IPv4 lease for address %1",
    "DHCPSRV_MEMFILE_UPDATE_ADDR6", "updating IPv6 lease for address %1",
    "DHCPSRV_MEMFILE_WIPE_LEASES4", "removing all IPv4 leases from subnet %1",
    "DHCPSRV_MEMFILE_WIPE_LEASES4_FINISHED", "removing all IPv4 leases from subnet %1 finished, removed %2 leases",
    "DHCPSRV_MEMFILE_WIPE_LEASES6", "removing all IPv6 leases from subnet %1",
    "DHCPSRV_MEMFILE_WIPE_LEASES6_FINISHED", "removing all IPv6 leases from subnet %1 finished, removed %2 leases",
    "DHCPSRV_MT_DISABLED_QUEUE_CONTROL", "disabling dhcp queue control when multi-threading is enabled.",
    "DHCPSRV_MULTIPLE_RAW_SOCKETS_PER_IFACE", "current configuration will result in opening multiple broadcast capable sockets on some interfaces and some DHCP messages may be duplicated",
    "DHCPSRV_MYSQL_ADD_ADDR4", "adding IPv4 lease with address %1",
    "DHCPSRV_MYSQL_ADD_ADDR6", "adding IPv6 lease with address %1, lease type %2",
    "DHCPSRV_MYSQL_COMMIT", "committing to MySQL database",
    "DHCPSRV_MYSQL_DB", "opening MySQL lease database: %1",
    "DHCPSRV_MYSQL_DELETED_EXPIRED_RECLAIMED", "deleted %1 reclaimed leases from the database",
    "DHCPSRV_MYSQL_DELETE_ADDR", "deleting lease for address %1",
    "DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED4", "deleting reclaimed IPv4 leases that expired more than %1 seconds ago",
    "DHCPSRV_MYSQL_DELETE_EXPIRED_RECLAIMED6", "deleting reclaimed IPv6 leases that expired more than %1 seconds ago",
    "DHCPSRV_MYSQL_GET4", "obtaining all IPv4 leases",
    "DHCPSRV_MYSQL_GET6", "obtaining all IPv6 leases",
    "DHCPSRV_MYSQL_GET_ADDR4", "obtaining IPv4 lease for address %1",
    "DHCPSRV_MYSQL_GET_ADDR6", "obtaining IPv6 lease for address %1, lease type %2",
    "DHCPSRV_MYSQL_GET_CLIENTID", "obtaining IPv4 leases for client ID %1",
    "DHCPSRV_MYSQL_GET_DUID", "obtaining IPv6 lease for duid %1,",
    "DHCPSRV_MYSQL_GET_EXPIRED4", "obtaining maximum %1 of expired IPv4 leases",
    "DHCPSRV_MYSQL_GET_EXPIRED6", "obtaining maximum %1 of expired IPv6 leases",
    "DHCPSRV_MYSQL_GET_HOSTNAME4", "obtaining IPv4 leases for hostname %1",
    "DHCPSRV_MYSQL_GET_HOSTNAME6", "obtaining IPv6 leases for hostname %1",
    "DHCPSRV_MYSQL_GET_HWADDR", "obtaining IPv4 leases for hardware address %1",
    "DHCPSRV_MYSQL_GET_IAID_DUID", "obtaining IPv6 leases for IAID %1, DUID %2, lease type %3",
    "DHCPSRV_MYSQL_GET_IAID_SUBID_DUID", "obtaining IPv6 leases for IAID %1, Subnet ID %2, DUID %3, lease type %4",
    "DHCPSRV_MYSQL_GET_PAGE4", "obtaining at most %1 IPv4 leases starting from address %2",
    "DHCPSRV_MYSQL_GET_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2",
    "DHCPSRV_MYSQL_GET_RELAYID4", "obtaining at most %1 IPv4 leases starting from address %2 with relay id %3 and cltt between %4 and %5",
    "DHCPSRV_MYSQL_GET_RELAYID6", "obtaining at most %1 IPv6 leases starting from address %2 with relay id %3",
    "DHCPSRV_MYSQL_GET_REMOTEID4", "obtaining at most %1 IPv4 leases starting from address %2 with remote id %3 and cltt between %4 and %5",
    "DHCPSRV_MYSQL_GET_REMOTEID6", "obtaining at most %1 IPv6 leases starting from address %2 with remote id %3",
    "DHCPSRV_MYSQL_GET_SUBID4", "obtaining IPv4 leases for subnet ID %1",
    "DHCPSRV_MYSQL_GET_SUBID6", "obtaining IPv6 leases for subnet ID %1",
    "DHCPSRV_MYSQL_GET_SUBID_CLIENTID", "obtaining IPv4 lease for subnet ID %1 and client ID %2",
    "DHCPSRV_MYSQL_GET_SUBID_HWADDR", "obtaining IPv4 lease for subnet ID %1 and hardware address %2",
    "DHCPSRV_MYSQL_GET_SUBID_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2 for subnet ID %3",
    "DHCPSRV_MYSQL_GET_VERSION", "obtaining schema version information",
    "DHCPSRV_MYSQL_HOST_DB", "opening MySQL hosts database: %1",
    "DHCPSRV_MYSQL_HOST_DB_GET_VERSION", "obtaining schema version information for the MySQL hosts database",
    "DHCPSRV_MYSQL_HOST_DB_READONLY", "MySQL host database opened for read access only",
    "DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "DHCPSRV_MYSQL_HOST_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "DHCPSRV_MYSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "DHCPSRV_MYSQL_LEASE_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "DHCPSRV_MYSQL_NEGATIVE_LEASES_STAT", "recount of leases returned a negative value",
    "DHCPSRV_MYSQL_NO_TLS", "TLS was required but is not used",
    "DHCPSRV_MYSQL_ROLLBACK", "rolling back MySQL database",
    "DHCPSRV_MYSQL_TLS_CIPHER", "TLS cipher: %1",
    "DHCPSRV_MYSQL_UPDATE_ADDR4", "updating IPv4 lease for address %1",
    "DHCPSRV_MYSQL_UPDATE_ADDR6", "updating IPv6 lease for address %1, lease type %2",
    "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4", "upgrading IPv4 leases done in %1 pages with %2 updated leases",
    "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_ERROR", "upgrading extending info for IPv4 lease at %1 failed with %2",
    "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO4_PAGE", "upgrading IPv4 lease extended info at page %1 starting at %2 (updated %3)",
    "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6", "upgrading IPv6 leases done in %1 pages with %2 updated leases",
    "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6_ERROR", "upgrading extending info for IPv6 lease at %1 failed with %2",
    "DHCPSRV_MYSQL_UPGRADE_EXTENDED_INFO6_PAGE", "upgrading IPv6 lease extended info at page %1 starting at %2 (updated %3)",
    "DHCPSRV_NOTYPE_DB", "no 'type' keyword to determine database backend: %1",
    "DHCPSRV_NO_SOCKETS_OPEN", "no interface configured to listen to DHCP traffic",
    "DHCPSRV_OPEN_SOCKET_FAIL", "failed to open socket: %1",
    "DHCPSRV_PGSQL_ADD_ADDR4", "adding IPv4 lease with address %1",
    "DHCPSRV_PGSQL_ADD_ADDR6", "adding IPv6 lease with address %1, lease type %2",
    "DHCPSRV_PGSQL_COMMIT", "committing to PostgreSQL database",
    "DHCPSRV_PGSQL_DB", "opening PostgreSQL lease database: %1",
    "DHCPSRV_PGSQL_DELETE_ADDR", "deleting lease for address %1",
    "DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED4", "deleting reclaimed IPv4 leases that expired more than %1 seconds ago",
    "DHCPSRV_PGSQL_DELETE_EXPIRED_RECLAIMED6", "deleting reclaimed IPv6 leases that expired more than %1 seconds ago",
    "DHCPSRV_PGSQL_GET4", "obtaining all IPv4 leases",
    "DHCPSRV_PGSQL_GET6", "obtaining all IPv6 leases",
    "DHCPSRV_PGSQL_GET_ADDR4", "obtaining IPv4 lease for address %1",
    "DHCPSRV_PGSQL_GET_ADDR6", "obtaining IPv6 lease for address %1 (lease type %2)",
    "DHCPSRV_PGSQL_GET_CLIENTID", "obtaining IPv4 leases for client ID %1",
    "DHCPSRV_PGSQL_GET_DUID", "obtaining IPv6 leases for DUID %1,",
    "DHCPSRV_PGSQL_GET_EXPIRED4", "obtaining maximum %1 of expired IPv4 leases",
    "DHCPSRV_PGSQL_GET_EXPIRED6", "obtaining maximum %1 of expired IPv6 leases",
    "DHCPSRV_PGSQL_GET_HOSTNAME4", "obtaining IPv4 leases for hostname %1",
    "DHCPSRV_PGSQL_GET_HOSTNAME6", "obtaining IPv6 leases for hostname %1",
    "DHCPSRV_PGSQL_GET_HWADDR", "obtaining IPv4 leases for hardware address %1",
    "DHCPSRV_PGSQL_GET_IAID_DUID", "obtaining IPv4 leases for IAID %1 and DUID %2, lease type %3",
    "DHCPSRV_PGSQL_GET_IAID_SUBID_DUID", "obtaining IPv4 leases for IAID %1, Subnet ID %2, DUID %3, and lease type %4",
    "DHCPSRV_PGSQL_GET_PAGE4", "obtaining at most %1 IPv4 leases starting from address %2",
    "DHCPSRV_PGSQL_GET_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2",
    "DHCPSRV_PGSQL_GET_RELAYID4", "obtaining at most %1 IPv4 leases starting from address %2 with relay id %3 and cltt between %4 and %5",
    "DHCPSRV_PGSQL_GET_RELAYID6", "obtaining at most %1 IPv6 leases starting from address %2 with relay id %3",
    "DHCPSRV_PGSQL_GET_REMOTEID4", "obtaining at most %1 IPv4 leases starting from address %2 with remote id %3 and cltt between %4 and %5",
    "DHCPSRV_PGSQL_GET_REMOTEID6", "obtaining at most %1 IPv6 leases starting from address %2 with remote id %3",
    "DHCPSRV_PGSQL_GET_SUBID4", "obtaining IPv4 leases for subnet ID %1",
    "DHCPSRV_PGSQL_GET_SUBID6", "obtaining IPv6 leases for subnet ID %1",
    "DHCPSRV_PGSQL_GET_SUBID_CLIENTID", "obtaining IPv4 lease for subnet ID %1 and client ID %2",
    "DHCPSRV_PGSQL_GET_SUBID_HWADDR", "obtaining IPv4 lease for subnet ID %1 and hardware address %2",
    "DHCPSRV_PGSQL_GET_SUBID_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2 for subnet ID %3",
    "DHCPSRV_PGSQL_GET_VERSION", "obtaining schema version information",
    "DHCPSRV_PGSQL_HOST_DB", "opening PostgreSQL hosts database: %1",
    "DHCPSRV_PGSQL_HOST_DB_GET_VERSION", "obtaining schema version information for the PostgreSQL hosts database",
    "DHCPSRV_PGSQL_HOST_DB_READONLY", "PostgreSQL host database opened for read access only",
    "DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "DHCPSRV_PGSQL_HOST_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "DHCPSRV_PGSQL_LEASE_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "DHCPSRV_PGSQL_LEASE_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "DHCPSRV_PGSQL_NEGATIVE_LEASES_STAT", "recount of leases returned a negative value",
    "DHCPSRV_PGSQL_NO_TLS_SUPPORT", "Attempt to configure TLS (unsupported for PostgreSQL): %1",
    "DHCPSRV_PGSQL_ROLLBACK", "rolling back PostgreSQL database",
    "DHCPSRV_PGSQL_TLS_SUPPORT", "Attempt to configure TLS: %1",
    "DHCPSRV_PGSQL_UPDATE_ADDR4", "updating IPv4 lease for address %1",
    "DHCPSRV_PGSQL_UPDATE_ADDR6", "updating IPv6 lease for address %1, lease type %2",
    "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4", "upgrading IPv4 leases done in %1 pages with %2 updated leases",
    "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_ERROR", "upgrading extending info for IPv4 lease at %1 failed with %2",
    "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO4_PAGE", "upgrading IPv4 lease extended info at page %1 starting at %2 (updated %3)",
    "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6", "upgrading IPv6 leases done in %1 pages with %2 updated leases",
    "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_ERROR", "upgrading extending info for IPv6 lease at %1 failed with %2",
    "DHCPSRV_PGSQL_UPGRADE_EXTENDED_INFO6_PAGE", "upgrading IPv6 lease extended info at page %1 starting at %2 (updated %3)",
    "DHCPSRV_QUEUE_NCR", "%1: Name change request to %2 DNS entry queued: %3",
    "DHCPSRV_QUEUE_NCR_FAILED", "%1: queuing %2 name change request failed for lease %3: %4",
    "DHCPSRV_QUEUE_NCR_SKIP", "%1: skip queuing name change request for lease: %2",
    "DHCPSRV_SUBNET4O6_SELECT_FAILED", "Failed to select any subnet for the DHCPv4o6 packet",
    "DHCPSRV_SUBNET4_SELECT_BY_ADDRESS_NO_MATCH", "No subnet matches address: %1",
    "DHCPSRV_SUBNET4_SELECT_BY_INTERFACE_NO_MATCH", "No subnet matches interface: %1",
    "DHCPSRV_SUBNET4_SELECT_BY_RELAY_ADDRESS_NO_MATCH", "No subnet matches relay address: %1",
    "DHCPSRV_SUBNET4_SELECT_NO_RAI_OPTIONS", "No RAI options found to use for subnet selection.",
    "DHCPSRV_SUBNET4_SELECT_NO_RELAY_ADDRESS", "Relay address (giaddr) in client packet is empty.",
    "DHCPSRV_SUBNET4_SELECT_NO_USABLE_ADDRESS", "No subnet selected because no suitable address to use for subnet selection was found.",
    "DHCPSRV_SUBNET6_SELECT_BY_ADDRESS_NO_MATCH", "No subnet matches address: %1",
    "DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_ID_NO_MATCH", "No subnet matches interface id: %1",
    "DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_NO_MATCH", "No subnet matches interface: %1",
    "DHCPSRV_TEMPLATE_EVAL_ERROR", "%1: Expression '%2' evaluated to %3",
    "DHCPSRV_TEMPLATE_EVAL_RESULT", "%1: Expression '%2' evaluated to %3",
    "DHCPSRV_TIMERMGR_CALLBACK_FAILED", "running handler for timer %1 caused exception: %2",
    "DHCPSRV_TIMERMGR_REGISTER_TIMER", "registering timer: %1, using interval: %2 ms",
    "DHCPSRV_TIMERMGR_RUN_TIMER_OPERATION", "running operation for timer: %1",
    "DHCPSRV_TIMERMGR_START_TIMER", "starting timer: %1",
    "DHCPSRV_TIMERMGR_STOP_TIMER", "stopping timer: %1",
    "DHCPSRV_TIMERMGR_UNREGISTER_ALL_TIMERS", "unregistering all timers",
    "DHCPSRV_TIMERMGR_UNREGISTER_TIMER", "unregistering timer: %1",
    "DHCPSRV_UNKNOWN_DB", "unknown database type: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

