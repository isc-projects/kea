// File created from src/hooks/dhcp/mysql/mysql_lb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID MYSQL_DEINIT_OK = "MYSQL_DEINIT_OK";
extern const isc::log::MessageID MYSQL_INIT_OK = "MYSQL_INIT_OK";
extern const isc::log::MessageID MYSQL_LB_ADD_ADDR4 = "MYSQL_LB_ADD_ADDR4";
extern const isc::log::MessageID MYSQL_LB_ADD_ADDR6 = "MYSQL_LB_ADD_ADDR6";
extern const isc::log::MessageID MYSQL_LB_COMMIT = "MYSQL_LB_COMMIT";
extern const isc::log::MessageID MYSQL_LB_DB = "MYSQL_LB_DB";
extern const isc::log::MessageID MYSQL_LB_DB_RECONNECT_ATTEMPT_FAILED = "MYSQL_LB_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID MYSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE = "MYSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID MYSQL_LB_DB_RECONNECT_FAILED = "MYSQL_LB_DB_RECONNECT_FAILED";
extern const isc::log::MessageID MYSQL_LB_DELETED_EXPIRED_RECLAIMED = "MYSQL_LB_DELETED_EXPIRED_RECLAIMED";
extern const isc::log::MessageID MYSQL_LB_DELETED_SUBNET4_ID = "MYSQL_LB_DELETED_SUBNET4_ID";
extern const isc::log::MessageID MYSQL_LB_DELETED_SUBNET6_ID = "MYSQL_LB_DELETED_SUBNET6_ID";
extern const isc::log::MessageID MYSQL_LB_DELETE_ADDR4 = "MYSQL_LB_DELETE_ADDR4";
extern const isc::log::MessageID MYSQL_LB_DELETE_ADDR6 = "MYSQL_LB_DELETE_ADDR6";
extern const isc::log::MessageID MYSQL_LB_DELETE_EXPIRED_RECLAIMED4 = "MYSQL_LB_DELETE_EXPIRED_RECLAIMED4";
extern const isc::log::MessageID MYSQL_LB_DELETE_EXPIRED_RECLAIMED6 = "MYSQL_LB_DELETE_EXPIRED_RECLAIMED6";
extern const isc::log::MessageID MYSQL_LB_GET4 = "MYSQL_LB_GET4";
extern const isc::log::MessageID MYSQL_LB_GET6 = "MYSQL_LB_GET6";
extern const isc::log::MessageID MYSQL_LB_GET_ADDR4 = "MYSQL_LB_GET_ADDR4";
extern const isc::log::MessageID MYSQL_LB_GET_ADDR6 = "MYSQL_LB_GET_ADDR6";
extern const isc::log::MessageID MYSQL_LB_GET_CLIENTID = "MYSQL_LB_GET_CLIENTID";
extern const isc::log::MessageID MYSQL_LB_GET_DUID = "MYSQL_LB_GET_DUID";
extern const isc::log::MessageID MYSQL_LB_GET_EXPIRED4 = "MYSQL_LB_GET_EXPIRED4";
extern const isc::log::MessageID MYSQL_LB_GET_EXPIRED6 = "MYSQL_LB_GET_EXPIRED6";
extern const isc::log::MessageID MYSQL_LB_GET_HOSTNAME4 = "MYSQL_LB_GET_HOSTNAME4";
extern const isc::log::MessageID MYSQL_LB_GET_HOSTNAME6 = "MYSQL_LB_GET_HOSTNAME6";
extern const isc::log::MessageID MYSQL_LB_GET_HWADDR = "MYSQL_LB_GET_HWADDR";
extern const isc::log::MessageID MYSQL_LB_GET_IAID_DUID = "MYSQL_LB_GET_IAID_DUID";
extern const isc::log::MessageID MYSQL_LB_GET_IAID_SUBID_DUID = "MYSQL_LB_GET_IAID_SUBID_DUID";
extern const isc::log::MessageID MYSQL_LB_GET_PAGE4 = "MYSQL_LB_GET_PAGE4";
extern const isc::log::MessageID MYSQL_LB_GET_PAGE6 = "MYSQL_LB_GET_PAGE6";
extern const isc::log::MessageID MYSQL_LB_GET_RELAYID4 = "MYSQL_LB_GET_RELAYID4";
extern const isc::log::MessageID MYSQL_LB_GET_RELAYID6 = "MYSQL_LB_GET_RELAYID6";
extern const isc::log::MessageID MYSQL_LB_GET_REMOTEID4 = "MYSQL_LB_GET_REMOTEID4";
extern const isc::log::MessageID MYSQL_LB_GET_REMOTEID6 = "MYSQL_LB_GET_REMOTEID6";
extern const isc::log::MessageID MYSQL_LB_GET_SUBID4 = "MYSQL_LB_GET_SUBID4";
extern const isc::log::MessageID MYSQL_LB_GET_SUBID6 = "MYSQL_LB_GET_SUBID6";
extern const isc::log::MessageID MYSQL_LB_GET_SUBID_CLIENTID = "MYSQL_LB_GET_SUBID_CLIENTID";
extern const isc::log::MessageID MYSQL_LB_GET_SUBID_HWADDR = "MYSQL_LB_GET_SUBID_HWADDR";
extern const isc::log::MessageID MYSQL_LB_GET_SUBID_PAGE6 = "MYSQL_LB_GET_SUBID_PAGE6";
extern const isc::log::MessageID MYSQL_LB_GET_VERSION = "MYSQL_LB_GET_VERSION";
extern const isc::log::MessageID MYSQL_LB_NEGATIVE_LEASES_STAT = "MYSQL_LB_NEGATIVE_LEASES_STAT";
extern const isc::log::MessageID MYSQL_LB_NO_TLS = "MYSQL_LB_NO_TLS";
extern const isc::log::MessageID MYSQL_LB_ROLLBACK = "MYSQL_LB_ROLLBACK";
extern const isc::log::MessageID MYSQL_LB_TLS_CIPHER = "MYSQL_LB_TLS_CIPHER";
extern const isc::log::MessageID MYSQL_LB_UPDATE_ADDR4 = "MYSQL_LB_UPDATE_ADDR4";
extern const isc::log::MessageID MYSQL_LB_UPDATE_ADDR6 = "MYSQL_LB_UPDATE_ADDR6";
extern const isc::log::MessageID MYSQL_LB_UPGRADE_EXTENDED_INFO4 = "MYSQL_LB_UPGRADE_EXTENDED_INFO4";
extern const isc::log::MessageID MYSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR = "MYSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR";
extern const isc::log::MessageID MYSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE = "MYSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE";
extern const isc::log::MessageID MYSQL_LB_UPGRADE_EXTENDED_INFO6 = "MYSQL_LB_UPGRADE_EXTENDED_INFO6";
extern const isc::log::MessageID MYSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR = "MYSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR";
extern const isc::log::MessageID MYSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE = "MYSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "MYSQL_DEINIT_OK", "unloading MySQL hooks library successful",
    "MYSQL_INIT_OK", "loading MySQL hooks library successful",
    "MYSQL_LB_ADD_ADDR4", "adding IPv4 lease with address %1",
    "MYSQL_LB_ADD_ADDR6", "adding IPv6 lease with address %1, lease type %2",
    "MYSQL_LB_COMMIT", "committing to MySQL database",
    "MYSQL_LB_DB", "opening MySQL lease database: %1",
    "MYSQL_LB_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "MYSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "MYSQL_LB_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "MYSQL_LB_DELETED_EXPIRED_RECLAIMED", "deleted %1 reclaimed leases from the database",
    "MYSQL_LB_DELETED_SUBNET4_ID", "deleted %1 leases that match subnet ID %2.",
    "MYSQL_LB_DELETED_SUBNET6_ID", "deleted %1 leases that match subnet ID %2.",
    "MYSQL_LB_DELETE_ADDR4", "deleting lease for address %1",
    "MYSQL_LB_DELETE_ADDR6", "deleting lease for address %1",
    "MYSQL_LB_DELETE_EXPIRED_RECLAIMED4", "deleting reclaimed IPv4 leases that expired more than %1 seconds ago",
    "MYSQL_LB_DELETE_EXPIRED_RECLAIMED6", "deleting reclaimed IPv6 leases that expired more than %1 seconds ago",
    "MYSQL_LB_GET4", "obtaining all IPv4 leases",
    "MYSQL_LB_GET6", "obtaining all IPv6 leases",
    "MYSQL_LB_GET_ADDR4", "obtaining IPv4 lease for address %1",
    "MYSQL_LB_GET_ADDR6", "obtaining IPv6 lease for address %1, lease type %2",
    "MYSQL_LB_GET_CLIENTID", "obtaining IPv4 leases for client ID %1",
    "MYSQL_LB_GET_DUID", "obtaining IPv6 lease for duid %1,",
    "MYSQL_LB_GET_EXPIRED4", "obtaining maximum %1 of expired IPv4 leases",
    "MYSQL_LB_GET_EXPIRED6", "obtaining maximum %1 of expired IPv6 leases",
    "MYSQL_LB_GET_HOSTNAME4", "obtaining IPv4 leases for hostname %1",
    "MYSQL_LB_GET_HOSTNAME6", "obtaining IPv6 leases for hostname %1",
    "MYSQL_LB_GET_HWADDR", "obtaining IPv4 leases for hardware address %1",
    "MYSQL_LB_GET_IAID_DUID", "obtaining IPv6 leases for IAID %1, DUID %2, lease type %3",
    "MYSQL_LB_GET_IAID_SUBID_DUID", "obtaining IPv6 leases for IAID %1, subnet ID %2, DUID %3, lease type %4",
    "MYSQL_LB_GET_PAGE4", "obtaining at most %1 IPv4 leases starting from address %2",
    "MYSQL_LB_GET_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2",
    "MYSQL_LB_GET_RELAYID4", "obtaining at most %1 IPv4 leases starting from address %2 with relay id %3 and cltt between %4 and %5",
    "MYSQL_LB_GET_RELAYID6", "obtaining at most %1 IPv6 leases starting from address %2 with relay id %3",
    "MYSQL_LB_GET_REMOTEID4", "obtaining at most %1 IPv4 leases starting from address %2 with remote id %3 and cltt between %4 and %5",
    "MYSQL_LB_GET_REMOTEID6", "obtaining at most %1 IPv6 leases starting from address %2 with remote id %3",
    "MYSQL_LB_GET_SUBID4", "obtaining IPv4 leases for subnet ID %1",
    "MYSQL_LB_GET_SUBID6", "obtaining IPv6 leases for subnet ID %1",
    "MYSQL_LB_GET_SUBID_CLIENTID", "obtaining IPv4 lease for subnet ID %1 and client ID %2",
    "MYSQL_LB_GET_SUBID_HWADDR", "obtaining IPv4 lease for subnet ID %1 and hardware address %2",
    "MYSQL_LB_GET_SUBID_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2 for subnet ID %3",
    "MYSQL_LB_GET_VERSION", "obtaining schema version information",
    "MYSQL_LB_NEGATIVE_LEASES_STAT", "recount of leases returned a negative value",
    "MYSQL_LB_NO_TLS", "TLS was required but is not used",
    "MYSQL_LB_ROLLBACK", "rolling back MySQL database",
    "MYSQL_LB_TLS_CIPHER", "TLS cipher: %1",
    "MYSQL_LB_UPDATE_ADDR4", "updating IPv4 lease for address %1",
    "MYSQL_LB_UPDATE_ADDR6", "updating IPv6 lease for address %1, lease type %2",
    "MYSQL_LB_UPGRADE_EXTENDED_INFO4", "upgrading IPv4 leases done in %1 pages with %2 updated leases",
    "MYSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR", "upgrading extending info for IPv4 lease at %1 failed with %2",
    "MYSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE", "upgrading IPv4 lease extended info at page %1 starting at %2 (updated %3)",
    "MYSQL_LB_UPGRADE_EXTENDED_INFO6", "upgrading IPv6 leases done in %1 pages with %2 updated leases",
    "MYSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR", "upgrading extending info for IPv6 lease at %1 failed with %2",
    "MYSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE", "upgrading IPv6 lease extended info at page %1 starting at %2 (updated %3)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

