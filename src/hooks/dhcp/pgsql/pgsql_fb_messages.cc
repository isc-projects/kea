// File created from src/hooks/dhcp/pgsql/pgsql_fb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID LEGAL_LOG_PGSQL_COMMIT = "LEGAL_LOG_PGSQL_COMMIT";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED = "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE = "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED = "LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DEALLOC_ERROR = "LEGAL_LOG_PGSQL_DEALLOC_ERROR";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_FATAL_ERROR = "LEGAL_LOG_PGSQL_FATAL_ERROR";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_GET_VERSION = "LEGAL_LOG_PGSQL_GET_VERSION";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_INSERT_LOG = "LEGAL_LOG_PGSQL_INSERT_LOG";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_INVALID_ACCESS = "LEGAL_LOG_PGSQL_INVALID_ACCESS";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_ROLLBACK = "LEGAL_LOG_PGSQL_ROLLBACK";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_START_TRANSACTION = "LEGAL_LOG_PGSQL_START_TRANSACTION";
extern const isc::log::MessageID PGSQL_FB_DB = "PGSQL_FB_DB";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "LEGAL_LOG_PGSQL_COMMIT", "committing to PostgreSQL database",
    "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "LEGAL_LOG_PGSQL_DEALLOC_ERROR", "An error occurred deallocating SQL statements while closing the PostgreSQL log database: %1",
    "LEGAL_LOG_PGSQL_FATAL_ERROR", "Unrecoverable PostgreSQL error occurred: Statement: <%1>, reason: %2 (error code: %3).",
    "LEGAL_LOG_PGSQL_GET_VERSION", "obtaining schema version information",
    "LEGAL_LOG_PGSQL_INSERT_LOG", "Adding a log entry to the database: %1",
    "LEGAL_LOG_PGSQL_INVALID_ACCESS", "invalid database access string: %1",
    "LEGAL_LOG_PGSQL_ROLLBACK", "rolling back PostgreSQL database",
    "LEGAL_LOG_PGSQL_START_TRANSACTION", "starting a new PostgreSQL transaction",
    "PGSQL_FB_DB", "opening PostgreSQL log database: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

