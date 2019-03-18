// File created from ../../../src/lib/database/db_messages.mes on Fri Feb 08 2019 20:16

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace db {

extern const isc::log::MessageID DATABASE_CQL_CONNECTION_BEGIN_TRANSACTION = "DATABASE_CQL_CONNECTION_BEGIN_TRANSACTION";
extern const isc::log::MessageID DATABASE_CQL_CONNECTION_COMMIT = "DATABASE_CQL_CONNECTION_COMMIT";
extern const isc::log::MessageID DATABASE_CQL_CONNECTION_ROLLBACK = "DATABASE_CQL_CONNECTION_ROLLBACK";
extern const isc::log::MessageID DATABASE_CQL_DEALLOC_ERROR = "DATABASE_CQL_DEALLOC_ERROR";
extern const isc::log::MessageID DATABASE_INVALID_ACCESS = "DATABASE_INVALID_ACCESS";
extern const isc::log::MessageID DATABASE_MYSQL_COMMIT = "DATABASE_MYSQL_COMMIT";
extern const isc::log::MessageID DATABASE_MYSQL_FATAL_ERROR = "DATABASE_MYSQL_FATAL_ERROR";
extern const isc::log::MessageID DATABASE_MYSQL_ROLLBACK = "DATABASE_MYSQL_ROLLBACK";
extern const isc::log::MessageID DATABASE_MYSQL_START_TRANSACTION = "DATABASE_MYSQL_START_TRANSACTION";
extern const isc::log::MessageID DATABASE_PGSQL_COMMIT = "DATABASE_PGSQL_COMMIT";
extern const isc::log::MessageID DATABASE_PGSQL_DEALLOC_ERROR = "DATABASE_PGSQL_DEALLOC_ERROR";
extern const isc::log::MessageID DATABASE_PGSQL_FATAL_ERROR = "DATABASE_PGSQL_FATAL_ERROR";
extern const isc::log::MessageID DATABASE_PGSQL_ROLLBACK = "DATABASE_PGSQL_ROLLBACK";
extern const isc::log::MessageID DATABASE_PGSQL_START_TRANSACTION = "DATABASE_PGSQL_START_TRANSACTION";
extern const isc::log::MessageID DATABASE_TO_JSON_ERROR = "DATABASE_TO_JSON_ERROR";

} // namespace db
} // namespace isc

namespace {

const char* values[] = {
    "DATABASE_CQL_CONNECTION_BEGIN_TRANSACTION", "begin transaction on current connection.",
    "DATABASE_CQL_CONNECTION_COMMIT", "committing to Cassandra database on current connection.",
    "DATABASE_CQL_CONNECTION_ROLLBACK", "rolling back Cassandra database on current connection.",
    "DATABASE_CQL_DEALLOC_ERROR", "An error occurred while closing the CQL connection: %1",
    "DATABASE_INVALID_ACCESS", "invalid database access string: %1",
    "DATABASE_MYSQL_COMMIT", "committing to MySQL database",
    "DATABASE_MYSQL_FATAL_ERROR", "Unrecoverable MySQL error occurred: %1 for <%2>, reason: %3 (error code: %4).",
    "DATABASE_MYSQL_ROLLBACK", "rolling back MySQL database",
    "DATABASE_MYSQL_START_TRANSACTION", "starting new MySQL transaction",
    "DATABASE_PGSQL_COMMIT", "committing to PostgreSQL database",
    "DATABASE_PGSQL_DEALLOC_ERROR", "An error occurred deallocating SQL statements while closing the PostgreSQL lease database: %1",
    "DATABASE_PGSQL_FATAL_ERROR", "Unrecoverable PostgreSQL error occurred: Statement: <%1>, reason: %2 (error code: %3).",
    "DATABASE_PGSQL_ROLLBACK", "rolling back PostgreSQL database",
    "DATABASE_PGSQL_START_TRANSACTION", "starting a new PostgreSQL transaction",
    "DATABASE_TO_JSON_ERROR", "Internal logic error: uknown %1 element found in state: %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

