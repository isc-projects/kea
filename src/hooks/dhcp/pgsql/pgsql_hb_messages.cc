// File created from src/hooks/dhcp/pgsql/pgsql_hb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID PGSQL_HB_DB = "PGSQL_HB_DB";
extern const isc::log::MessageID PGSQL_HB_DB_GET_VERSION = "PGSQL_HB_DB_GET_VERSION";
extern const isc::log::MessageID PGSQL_HB_DB_READONLY = "PGSQL_HB_DB_READONLY";
extern const isc::log::MessageID PGSQL_HB_DB_RECONNECT_ATTEMPT_FAILED = "PGSQL_HB_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID PGSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE = "PGSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID PGSQL_HB_DB_RECONNECT_FAILED = "PGSQL_HB_DB_RECONNECT_FAILED";
extern const isc::log::MessageID PGSQL_HB_NO_TLS_SUPPORT = "PGSQL_HB_NO_TLS_SUPPORT";
extern const isc::log::MessageID PGSQL_HB_TLS_SUPPORT = "PGSQL_HB_TLS_SUPPORT";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "PGSQL_HB_DB", "opening PostgreSQL hosts database: %1",
    "PGSQL_HB_DB_GET_VERSION", "obtaining schema version information for the PostgreSQL hosts database",
    "PGSQL_HB_DB_READONLY", "PostgreSQL host database opened for read access only",
    "PGSQL_HB_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "PGSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "PGSQL_HB_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "PGSQL_HB_NO_TLS_SUPPORT", "Attempt to configure TLS (unsupported for PostgreSQL): %1",
    "PGSQL_HB_TLS_SUPPORT", "Attempt to configure TLS: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

