// File created from src/hooks/dhcp/pgsql/pgsql_fb_messages.mes

#ifndef PGSQL_FB_MESSAGES_H
#define PGSQL_FB_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID LEGAL_LOG_PGSQL_COMMIT;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DEALLOC_ERROR;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_FATAL_ERROR;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_GET_VERSION;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_INSERT_LOG;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_INVALID_ACCESS;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_NO_TLS_SUPPORT;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_ROLLBACK;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_START_TRANSACTION;
extern const isc::log::MessageID LEGAL_LOG_PGSQL_TLS_SUPPORT;
extern const isc::log::MessageID PGSQL_FB_DB;

} // namespace dhcp
} // namespace isc

#endif // PGSQL_FB_MESSAGES_H
