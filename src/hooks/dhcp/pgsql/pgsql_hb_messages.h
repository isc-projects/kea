// File created from ../../../../src/hooks/dhcp/pgsql/pgsql_hb_messages.mes

#ifndef PGSQL_HB_MESSAGES_H
#define PGSQL_HB_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID PGSQL_HB_DB;
extern const isc::log::MessageID PGSQL_HB_DB_GET_VERSION;
extern const isc::log::MessageID PGSQL_HB_DB_READONLY;
extern const isc::log::MessageID PGSQL_HB_DB_RECONNECT_ATTEMPT_FAILED;
extern const isc::log::MessageID PGSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE;
extern const isc::log::MessageID PGSQL_HB_DB_RECONNECT_FAILED;
extern const isc::log::MessageID PGSQL_HB_NO_TLS_SUPPORT;
extern const isc::log::MessageID PGSQL_HB_TLS_SUPPORT;

} // namespace dhcp
} // namespace isc

#endif // PGSQL_HB_MESSAGES_H
