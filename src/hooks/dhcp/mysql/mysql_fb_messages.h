// File created from src/hooks/dhcp/mysql/mysql_fb_messages.mes

#ifndef MYSQL_FB_MESSAGES_H
#define MYSQL_FB_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID LEGAL_LOG_MYSQL_COMMIT;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_FATAL_ERROR;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_GET_VERSION;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_INSERT_LOG;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_INVALID_ACCESS;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_NO_TLS;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_ROLLBACK;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_START_TRANSACTION;
extern const isc::log::MessageID LEGAL_LOG_MYSQL_TLS_CIPHER;
extern const isc::log::MessageID MYSQL_FB_DB;

} // namespace dhcp
} // namespace isc

#endif // MYSQL_FB_MESSAGES_H
