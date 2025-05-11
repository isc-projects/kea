// File created from src/hooks/dhcp/pgsql/pgsql_lb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID PGSQL_DEINIT_OK = "PGSQL_DEINIT_OK";
extern const isc::log::MessageID PGSQL_INIT_OK = "PGSQL_INIT_OK";
extern const isc::log::MessageID PGSQL_LB_ADD_ADDR4 = "PGSQL_LB_ADD_ADDR4";
extern const isc::log::MessageID PGSQL_LB_ADD_ADDR6 = "PGSQL_LB_ADD_ADDR6";
extern const isc::log::MessageID PGSQL_LB_COMMIT = "PGSQL_LB_COMMIT";
extern const isc::log::MessageID PGSQL_LB_DB = "PGSQL_LB_DB";
extern const isc::log::MessageID PGSQL_LB_DB_RECONNECT_ATTEMPT_FAILED = "PGSQL_LB_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID PGSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE = "PGSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID PGSQL_LB_DB_RECONNECT_FAILED = "PGSQL_LB_DB_RECONNECT_FAILED";
extern const isc::log::MessageID PGSQL_LB_DELETE_ADDR4 = "PGSQL_LB_DELETE_ADDR4";
extern const isc::log::MessageID PGSQL_LB_DELETE_ADDR6 = "PGSQL_LB_DELETE_ADDR6";
extern const isc::log::MessageID PGSQL_LB_DELETE_EXPIRED_RECLAIMED4 = "PGSQL_LB_DELETE_EXPIRED_RECLAIMED4";
extern const isc::log::MessageID PGSQL_LB_DELETE_EXPIRED_RECLAIMED6 = "PGSQL_LB_DELETE_EXPIRED_RECLAIMED6";
extern const isc::log::MessageID PGSQL_LB_GET4 = "PGSQL_LB_GET4";
extern const isc::log::MessageID PGSQL_LB_GET6 = "PGSQL_LB_GET6";
extern const isc::log::MessageID PGSQL_LB_GET_ADDR4 = "PGSQL_LB_GET_ADDR4";
extern const isc::log::MessageID PGSQL_LB_GET_ADDR6 = "PGSQL_LB_GET_ADDR6";
extern const isc::log::MessageID PGSQL_LB_GET_CLIENTID = "PGSQL_LB_GET_CLIENTID";
extern const isc::log::MessageID PGSQL_LB_GET_DUID = "PGSQL_LB_GET_DUID";
extern const isc::log::MessageID PGSQL_LB_GET_EXPIRED4 = "PGSQL_LB_GET_EXPIRED4";
extern const isc::log::MessageID PGSQL_LB_GET_EXPIRED6 = "PGSQL_LB_GET_EXPIRED6";
extern const isc::log::MessageID PGSQL_LB_GET_HOSTNAME4 = "PGSQL_LB_GET_HOSTNAME4";
extern const isc::log::MessageID PGSQL_LB_GET_HOSTNAME6 = "PGSQL_LB_GET_HOSTNAME6";
extern const isc::log::MessageID PGSQL_LB_GET_HWADDR = "PGSQL_LB_GET_HWADDR";
extern const isc::log::MessageID PGSQL_LB_GET_IAID_DUID = "PGSQL_LB_GET_IAID_DUID";
extern const isc::log::MessageID PGSQL_LB_GET_IAID_SUBID_DUID = "PGSQL_LB_GET_IAID_SUBID_DUID";
extern const isc::log::MessageID PGSQL_LB_GET_PAGE4 = "PGSQL_LB_GET_PAGE4";
extern const isc::log::MessageID PGSQL_LB_GET_PAGE6 = "PGSQL_LB_GET_PAGE6";
extern const isc::log::MessageID PGSQL_LB_GET_RELAYID4 = "PGSQL_LB_GET_RELAYID4";
extern const isc::log::MessageID PGSQL_LB_GET_RELAYID6 = "PGSQL_LB_GET_RELAYID6";
extern const isc::log::MessageID PGSQL_LB_GET_REMOTEID4 = "PGSQL_LB_GET_REMOTEID4";
extern const isc::log::MessageID PGSQL_LB_GET_REMOTEID6 = "PGSQL_LB_GET_REMOTEID6";
extern const isc::log::MessageID PGSQL_LB_GET_SUBID4 = "PGSQL_LB_GET_SUBID4";
extern const isc::log::MessageID PGSQL_LB_GET_SUBID6 = "PGSQL_LB_GET_SUBID6";
extern const isc::log::MessageID PGSQL_LB_GET_SUBID_CLIENTID = "PGSQL_LB_GET_SUBID_CLIENTID";
extern const isc::log::MessageID PGSQL_LB_GET_SUBID_HWADDR = "PGSQL_LB_GET_SUBID_HWADDR";
extern const isc::log::MessageID PGSQL_LB_GET_SUBID_PAGE6 = "PGSQL_LB_GET_SUBID_PAGE6";
extern const isc::log::MessageID PGSQL_LB_GET_VERSION = "PGSQL_LB_GET_VERSION";
extern const isc::log::MessageID PGSQL_LB_NEGATIVE_LEASES_STAT = "PGSQL_LB_NEGATIVE_LEASES_STAT";
extern const isc::log::MessageID PGSQL_LB_NO_TLS_SUPPORT = "PGSQL_LB_NO_TLS_SUPPORT";
extern const isc::log::MessageID PGSQL_LB_ROLLBACK = "PGSQL_LB_ROLLBACK";
extern const isc::log::MessageID PGSQL_LB_TLS_SUPPORT = "PGSQL_LB_TLS_SUPPORT";
extern const isc::log::MessageID PGSQL_LB_UPDATE_ADDR4 = "PGSQL_LB_UPDATE_ADDR4";
extern const isc::log::MessageID PGSQL_LB_UPDATE_ADDR6 = "PGSQL_LB_UPDATE_ADDR6";
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO4 = "PGSQL_LB_UPGRADE_EXTENDED_INFO4";
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR = "PGSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR";
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE = "PGSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE";
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO6 = "PGSQL_LB_UPGRADE_EXTENDED_INFO6";
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR = "PGSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR";
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE = "PGSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "PGSQL_DEINIT_OK", "unloading PostgreSQL hooks library successful",
    "PGSQL_INIT_OK", "loading PostgreSQL hooks library successful",
    "PGSQL_LB_ADD_ADDR4", "adding IPv4 lease with address %1",
    "PGSQL_LB_ADD_ADDR6", "adding IPv6 lease with address %1, lease type %2",
    "PGSQL_LB_COMMIT", "committing to PostgreSQL database",
    "PGSQL_LB_DB", "opening PostgreSQL lease database: %1",
    "PGSQL_LB_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "PGSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "PGSQL_LB_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "PGSQL_LB_DELETE_ADDR4", "deleting lease for address %1",
    "PGSQL_LB_DELETE_ADDR6", "deleting lease for address %1",
    "PGSQL_LB_DELETE_EXPIRED_RECLAIMED4", "deleting reclaimed IPv4 leases that expired more than %1 seconds ago",
    "PGSQL_LB_DELETE_EXPIRED_RECLAIMED6", "deleting reclaimed IPv6 leases that expired more than %1 seconds ago",
    "PGSQL_LB_GET4", "obtaining all IPv4 leases",
    "PGSQL_LB_GET6", "obtaining all IPv6 leases",
    "PGSQL_LB_GET_ADDR4", "obtaining IPv4 lease for address %1",
    "PGSQL_LB_GET_ADDR6", "obtaining IPv6 lease for address %1 (lease type %2)",
    "PGSQL_LB_GET_CLIENTID", "obtaining IPv4 leases for client ID %1",
    "PGSQL_LB_GET_DUID", "obtaining IPv6 leases for DUID %1,",
    "PGSQL_LB_GET_EXPIRED4", "obtaining maximum %1 of expired IPv4 leases",
    "PGSQL_LB_GET_EXPIRED6", "obtaining maximum %1 of expired IPv6 leases",
    "PGSQL_LB_GET_HOSTNAME4", "obtaining IPv4 leases for hostname %1",
    "PGSQL_LB_GET_HOSTNAME6", "obtaining IPv6 leases for hostname %1",
    "PGSQL_LB_GET_HWADDR", "obtaining IPv4 leases for hardware address %1",
    "PGSQL_LB_GET_IAID_DUID", "obtaining IPv4 leases for IAID %1 and DUID %2, lease type %3",
    "PGSQL_LB_GET_IAID_SUBID_DUID", "obtaining IPv4 leases for IAID %1, Subnet ID %2, DUID %3, and lease type %4",
    "PGSQL_LB_GET_PAGE4", "obtaining at most %1 IPv4 leases starting from address %2",
    "PGSQL_LB_GET_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2",
    "PGSQL_LB_GET_RELAYID4", "obtaining at most %1 IPv4 leases starting from address %2 with relay id %3 and cltt between %4 and %5",
    "PGSQL_LB_GET_RELAYID6", "obtaining at most %1 IPv6 leases starting from address %2 with relay id %3",
    "PGSQL_LB_GET_REMOTEID4", "obtaining at most %1 IPv4 leases starting from address %2 with remote id %3 and cltt between %4 and %5",
    "PGSQL_LB_GET_REMOTEID6", "obtaining at most %1 IPv6 leases starting from address %2 with remote id %3",
    "PGSQL_LB_GET_SUBID4", "obtaining IPv4 leases for subnet ID %1",
    "PGSQL_LB_GET_SUBID6", "obtaining IPv6 leases for subnet ID %1",
    "PGSQL_LB_GET_SUBID_CLIENTID", "obtaining IPv4 lease for subnet ID %1 and client ID %2",
    "PGSQL_LB_GET_SUBID_HWADDR", "obtaining IPv4 lease for subnet ID %1 and hardware address %2",
    "PGSQL_LB_GET_SUBID_PAGE6", "obtaining at most %1 IPv6 leases starting from address %2 for subnet ID %3",
    "PGSQL_LB_GET_VERSION", "obtaining schema version information",
    "PGSQL_LB_NEGATIVE_LEASES_STAT", "recount of leases returned a negative value",
    "PGSQL_LB_NO_TLS_SUPPORT", "Attempt to configure TLS (unsupported for PostgreSQL): %1",
    "PGSQL_LB_ROLLBACK", "rolling back PostgreSQL database",
    "PGSQL_LB_TLS_SUPPORT", "Attempt to configure TLS: %1",
    "PGSQL_LB_UPDATE_ADDR4", "updating IPv4 lease for address %1",
    "PGSQL_LB_UPDATE_ADDR6", "updating IPv6 lease for address %1, lease type %2",
    "PGSQL_LB_UPGRADE_EXTENDED_INFO4", "upgrading IPv4 leases done in %1 pages with %2 updated leases",
    "PGSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR", "upgrading extending info for IPv4 lease at %1 failed with %2",
    "PGSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE", "upgrading IPv4 lease extended info at page %1 starting at %2 (updated %3)",
    "PGSQL_LB_UPGRADE_EXTENDED_INFO6", "upgrading IPv6 leases done in %1 pages with %2 updated leases",
    "PGSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR", "upgrading extending info for IPv6 lease at %1 failed with %2",
    "PGSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE", "upgrading IPv6 lease extended info at page %1 starting at %2 (updated %3)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

