// File created from ../../../../src/hooks/dhcp/forensic_log/legal_log_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID LEGAL_LOG_COMMAND_NO_LEGAL_STORE = "LEGAL_LOG_COMMAND_NO_LEGAL_STORE";
extern const isc::log::MessageID LEGAL_LOG_COMMAND_WRITE_ERROR = "LEGAL_LOG_COMMAND_WRITE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED = "LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED";
extern const isc::log::MessageID LEGAL_LOG_INVALID_ACCESS = "LEGAL_LOG_INVALID_ACCESS";
extern const isc::log::MessageID LEGAL_LOG_LEASE4_NO_LEGAL_STORE = "LEGAL_LOG_LEASE4_NO_LEGAL_STORE";
extern const isc::log::MessageID LEGAL_LOG_LEASE4_WRITE_ERROR = "LEGAL_LOG_LEASE4_WRITE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_LEASE6_NO_LEGAL_STORE = "LEGAL_LOG_LEASE6_NO_LEGAL_STORE";
extern const isc::log::MessageID LEGAL_LOG_LEASE6_WRITE_ERROR = "LEGAL_LOG_LEASE6_WRITE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_LOAD_ERROR = "LEGAL_LOG_LOAD_ERROR";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_COMMIT = "LEGAL_LOG_MYSQL_COMMIT";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB = "LEGAL_LOG_MYSQL_DB";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED = "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE = "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED = "LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_FATAL_ERROR = "LEGAL_LOG_MYSQL_FATAL_ERROR";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_GET_VERSION = "LEGAL_LOG_MYSQL_GET_VERSION";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_INSERT_LOG = "LEGAL_LOG_MYSQL_INSERT_LOG";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_NO_TLS = "LEGAL_LOG_MYSQL_NO_TLS";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_ROLLBACK = "LEGAL_LOG_MYSQL_ROLLBACK";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_START_TRANSACTION = "LEGAL_LOG_MYSQL_START_TRANSACTION";
extern const isc::log::MessageID LEGAL_LOG_MYSQL_TLS_CIPHER = "LEGAL_LOG_MYSQL_TLS_CIPHER";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_COMMIT = "LEGAL_LOG_PGSQL_COMMIT";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB = "LEGAL_LOG_PGSQL_DB";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED = "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE = "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED = "LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_DEALLOC_ERROR = "LEGAL_LOG_PGSQL_DEALLOC_ERROR";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_FATAL_ERROR = "LEGAL_LOG_PGSQL_FATAL_ERROR";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_GET_VERSION = "LEGAL_LOG_PGSQL_GET_VERSION";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_INSERT_LOG = "LEGAL_LOG_PGSQL_INSERT_LOG";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_NO_TLS_SUPPORT = "LEGAL_LOG_PGSQL_NO_TLS_SUPPORT";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_ROLLBACK = "LEGAL_LOG_PGSQL_ROLLBACK";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_START_TRANSACTION = "LEGAL_LOG_PGSQL_START_TRANSACTION";
extern const isc::log::MessageID LEGAL_LOG_PGSQL_TLS_SUPPORT = "LEGAL_LOG_PGSQL_TLS_SUPPORT";
extern const isc::log::MessageID LEGAL_LOG_STORE_CLOSED = "LEGAL_LOG_STORE_CLOSED";
extern const isc::log::MessageID LEGAL_LOG_STORE_CLOSE_ERROR = "LEGAL_LOG_STORE_CLOSE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_STORE_OPENED = "LEGAL_LOG_STORE_OPENED";
extern const isc::log::MessageID LEGAL_LOG_UNLOAD_ERROR = "LEGAL_LOG_UNLOAD_ERROR";

namespace {

const char* values[] = {
    "LEGAL_LOG_COMMAND_NO_LEGAL_STORE", "LegalStore instance is null",
    "LEGAL_LOG_COMMAND_WRITE_ERROR", "Could not write command entry to the legal store: %1",
    "LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED", "Failed to connect to database: %1 with error: %2",
    "LEGAL_LOG_INVALID_ACCESS", "invalid database access string: %1",
    "LEGAL_LOG_LEASE4_NO_LEGAL_STORE", "LegalStore instance is null",
    "LEGAL_LOG_LEASE4_WRITE_ERROR", "Could not write to the legal store: %1",
    "LEGAL_LOG_LEASE6_NO_LEGAL_STORE", "LegalStore instance is null",
    "LEGAL_LOG_LEASE6_WRITE_ERROR", "Could not write to the legal store: %1",
    "LEGAL_LOG_LOAD_ERROR", "LEGAL LOGGING DISABLED! An error occurred loading the library: %1",
    "LEGAL_LOG_MYSQL_COMMIT", "committing to MySQL database",
    "LEGAL_LOG_MYSQL_DB", "opening MySQL log database: %1",
    "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "LEGAL_LOG_MYSQL_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "LEGAL_LOG_MYSQL_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "LEGAL_LOG_MYSQL_FATAL_ERROR", "Unrecoverable MySQL error occurred: %1 for <%2>, reason: %3 (error code: %4).",
    "LEGAL_LOG_MYSQL_GET_VERSION", "obtaining schema version information",
    "LEGAL_LOG_MYSQL_INSERT_LOG", "Adding a log entry to the database: %1",
    "LEGAL_LOG_MYSQL_NO_TLS", "TLS was required but is not used",
    "LEGAL_LOG_MYSQL_ROLLBACK", "rolling back MySQL database",
    "LEGAL_LOG_MYSQL_START_TRANSACTION", "starting new MySQL transaction",
    "LEGAL_LOG_MYSQL_TLS_CIPHER", "TLS cipher: %1",
    "LEGAL_LOG_PGSQL_COMMIT", "committing to PostgreSQL database",
    "LEGAL_LOG_PGSQL_DB", "opening PostgreSQL log database: %1",
    "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "LEGAL_LOG_PGSQL_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "LEGAL_LOG_PGSQL_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "LEGAL_LOG_PGSQL_DEALLOC_ERROR", "An error occurred deallocating SQL statements while closing the PostgreSQL log database: %1",
    "LEGAL_LOG_PGSQL_FATAL_ERROR", "Unrecoverable PostgreSQL error occurred: Statement: <%1>, reason: %2 (error code: %3).",
    "LEGAL_LOG_PGSQL_GET_VERSION", "obtaining schema version information",
    "LEGAL_LOG_PGSQL_INSERT_LOG", "Adding a log entry to the database: %1",
    "LEGAL_LOG_PGSQL_NO_TLS_SUPPORT", "Attempt to configure TLS (unsupported for PostgreSQL): %1",
    "LEGAL_LOG_PGSQL_ROLLBACK", "rolling back PostgreSQL database",
    "LEGAL_LOG_PGSQL_START_TRANSACTION", "starting a new PostgreSQL transaction",
    "LEGAL_LOG_PGSQL_TLS_SUPPORT", "Attempt to configure TLS: %1",
    "LEGAL_LOG_STORE_CLOSED", "Legal store closed: %1",
    "LEGAL_LOG_STORE_CLOSE_ERROR", "An error occurred closing the store: %1, error: %2",
    "LEGAL_LOG_STORE_OPENED", "Legal store opened: %1",
    "LEGAL_LOG_UNLOAD_ERROR", "An error occurred unloading the library: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

