// File created from src/hooks/dhcp/mysql/mysql_fb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID LEGAL_LOG_MYSQL_COMMIT = "LEGAL_LOG_MYSQL_COMMIT";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED = "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE = "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED = "LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_FATAL_ERROR = "LEGAL_LOG_MYSQL_FATAL_ERROR";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_GET_VERSION = "LEGAL_LOG_MYSQL_GET_VERSION";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_INSERT_LOG = "LEGAL_LOG_MYSQL_INSERT_LOG";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_INVALID_ACCESS = "LEGAL_LOG_MYSQL_INVALID_ACCESS";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_NO_TLS = "LEGAL_LOG_MYSQL_NO_TLS";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_ROLLBACK = "LEGAL_LOG_MYSQL_ROLLBACK";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_START_TRANSACTION = "LEGAL_LOG_MYSQL_START_TRANSACTION";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_TLS_CIPHER = "LEGAL_LOG_MYSQL_TLS_CIPHER";
extern const isc::log::MessageID MYSQL_FB_DB = "MYSQL_FB_DB";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "LEGAL_LOG_MYSQL_COMMIT", "committing to MySQL database",
    "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "LEGAL_LOG_MYSQL_FATAL_ERROR", "Unrecoverable MySQL error occurred: %1 for <%2>, reason: %3 (error code: %4).",
    "LEGAL_LOG_MYSQL_GET_VERSION", "obtaining schema version information",
    "LEGAL_LOG_MYSQL_INSERT_LOG", "Adding a log entry to the database: %1",
    "LEGAL_LOG_MYSQL_INVALID_ACCESS", "invalid database access string: %1",
    "LEGAL_LOG_MYSQL_NO_TLS", "TLS was required but is not used",
    "LEGAL_LOG_MYSQL_ROLLBACK", "rolling back MySQL database",
    "LEGAL_LOG_MYSQL_START_TRANSACTION", "starting new MySQL transaction",
    "LEGAL_LOG_MYSQL_TLS_CIPHER", "TLS cipher: %1",
    "MYSQL_FB_DB", "opening MySQL log database: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

