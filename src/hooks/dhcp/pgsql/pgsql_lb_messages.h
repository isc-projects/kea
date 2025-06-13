// File created from src/hooks/dhcp/pgsql/pgsql_lb_messages.mes

#ifndef PGSQL_LB_MESSAGES_H
#define PGSQL_LB_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID PGSQL_DEINIT_OK;
extern const isc::log::MessageID PGSQL_INIT_OK;
extern const isc::log::MessageID PGSQL_LB_ADD_ADDR4;
extern const isc::log::MessageID PGSQL_LB_ADD_ADDR6;
extern const isc::log::MessageID PGSQL_LB_COMMIT;
extern const isc::log::MessageID PGSQL_LB_DB;
extern const isc::log::MessageID PGSQL_LB_DB_RECONNECT_ATTEMPT_FAILED;
extern const isc::log::MessageID PGSQL_LB_DB_RECONNECT_ATTEMPT_SCHEDULE;
extern const isc::log::MessageID PGSQL_LB_DB_RECONNECT_FAILED;
extern const isc::log::MessageID PGSQL_LB_DELETED_SUBNET4_ID;
extern const isc::log::MessageID PGSQL_LB_DELETED_SUBNET6_ID;
extern const isc::log::MessageID PGSQL_LB_DELETE_ADDR4;
extern const isc::log::MessageID PGSQL_LB_DELETE_ADDR6;
extern const isc::log::MessageID PGSQL_LB_DELETE_EXPIRED_RECLAIMED4;
extern const isc::log::MessageID PGSQL_LB_DELETE_EXPIRED_RECLAIMED6;
extern const isc::log::MessageID PGSQL_LB_GET4;
extern const isc::log::MessageID PGSQL_LB_GET6;
extern const isc::log::MessageID PGSQL_LB_GET_ADDR4;
extern const isc::log::MessageID PGSQL_LB_GET_ADDR6;
extern const isc::log::MessageID PGSQL_LB_GET_CLIENTID;
extern const isc::log::MessageID PGSQL_LB_GET_DUID;
extern const isc::log::MessageID PGSQL_LB_GET_EXPIRED4;
extern const isc::log::MessageID PGSQL_LB_GET_EXPIRED6;
extern const isc::log::MessageID PGSQL_LB_GET_HOSTNAME4;
extern const isc::log::MessageID PGSQL_LB_GET_HOSTNAME6;
extern const isc::log::MessageID PGSQL_LB_GET_HWADDR;
extern const isc::log::MessageID PGSQL_LB_GET_IAID_DUID;
extern const isc::log::MessageID PGSQL_LB_GET_IAID_SUBID_DUID;
extern const isc::log::MessageID PGSQL_LB_GET_PAGE4;
extern const isc::log::MessageID PGSQL_LB_GET_PAGE6;
extern const isc::log::MessageID PGSQL_LB_GET_RELAYID4;
extern const isc::log::MessageID PGSQL_LB_GET_RELAYID6;
extern const isc::log::MessageID PGSQL_LB_GET_REMOTEID4;
extern const isc::log::MessageID PGSQL_LB_GET_REMOTEID6;
extern const isc::log::MessageID PGSQL_LB_GET_SUBID4;
extern const isc::log::MessageID PGSQL_LB_GET_SUBID6;
extern const isc::log::MessageID PGSQL_LB_GET_SUBID_CLIENTID;
extern const isc::log::MessageID PGSQL_LB_GET_SUBID_HWADDR;
extern const isc::log::MessageID PGSQL_LB_GET_SUBID_PAGE6;
extern const isc::log::MessageID PGSQL_LB_GET_VERSION;
extern const isc::log::MessageID PGSQL_LB_NEGATIVE_LEASES_STAT;
extern const isc::log::MessageID PGSQL_LB_ROLLBACK;
extern const isc::log::MessageID PGSQL_LB_UPDATE_ADDR4;
extern const isc::log::MessageID PGSQL_LB_UPDATE_ADDR6;
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO4;
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO4_ERROR;
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO4_PAGE;
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO6;
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO6_ERROR;
extern const isc::log::MessageID PGSQL_LB_UPGRADE_EXTENDED_INFO6_PAGE;

} // namespace dhcp
} // namespace isc

#endif // PGSQL_LB_MESSAGES_H
