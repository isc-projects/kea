// File created from ../../../../src/hooks/dhcp/mysql/mysql_hb_messages.mes

#ifndef MYSQL_HB_MESSAGES_H
#define MYSQL_HB_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID MYSQL_HB_DB;
extern const isc::log::MessageID MYSQL_HB_DB_GET_VERSION;
extern const isc::log::MessageID MYSQL_HB_DB_READONLY;
extern const isc::log::MessageID MYSQL_HB_DB_RECONNECT_ATTEMPT_FAILED;
extern const isc::log::MessageID MYSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE;
extern const isc::log::MessageID MYSQL_HB_DB_RECONNECT_FAILED;
extern const isc::log::MessageID MYSQL_HB_DEINIT_OK;
extern const isc::log::MessageID MYSQL_HB_INIT_OK;
extern const isc::log::MessageID MYSQL_HB_NO_TLS;
extern const isc::log::MessageID MYSQL_HB_TLS_CIPHER;

} // namespace dhcp
} // namespace isc

#endif // MYSQL_HB_MESSAGES_H
