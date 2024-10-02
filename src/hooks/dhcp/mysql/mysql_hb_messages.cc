// File created from ../../../../src/hooks/dhcp/mysql/mysql_hb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID MYSQL_HB_DB = "MYSQL_HB_DB";
extern const isc::log::MessageID MYSQL_HB_DB_GET_VERSION = "MYSQL_HB_DB_GET_VERSION";
extern const isc::log::MessageID MYSQL_HB_DB_READONLY = "MYSQL_HB_DB_READONLY";
extern const isc::log::MessageID MYSQL_HB_DB_RECONNECT_ATTEMPT_FAILED = "MYSQL_HB_DB_RECONNECT_ATTEMPT_FAILED";
extern const isc::log::MessageID MYSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE = "MYSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE";
extern const isc::log::MessageID MYSQL_HB_DB_RECONNECT_FAILED = "MYSQL_HB_DB_RECONNECT_FAILED";
extern const isc::log::MessageID MYSQL_HB_DEINIT_OK = "MYSQL_HB_DEINIT_OK";
extern const isc::log::MessageID MYSQL_HB_INIT_OK = "MYSQL_HB_INIT_OK";
extern const isc::log::MessageID MYSQL_HB_NO_TLS = "MYSQL_HB_NO_TLS";
extern const isc::log::MessageID MYSQL_HB_TLS_CIPHER = "MYSQL_HB_TLS_CIPHER";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "MYSQL_HB_DB", "opening MySQL hosts database: %1",
    "MYSQL_HB_DB_GET_VERSION", "obtaining schema version information for the MySQL hosts database",
    "MYSQL_HB_DB_READONLY", "MySQL host database opened for read access only",
    "MYSQL_HB_DB_RECONNECT_ATTEMPT_FAILED", "database reconnect failed: %1",
    "MYSQL_HB_DB_RECONNECT_ATTEMPT_SCHEDULE", "scheduling attempt %1 of %2 in %3 milliseconds",
    "MYSQL_HB_DB_RECONNECT_FAILED", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "MYSQL_HB_DEINIT_OK", "unloading MySQL HB hooks library successful",
    "MYSQL_HB_INIT_OK", "loading MySQL HB hooks library successful",
    "MYSQL_HB_NO_TLS", "TLS was required but is not used",
    "MYSQL_HB_TLS_CIPHER", "TLS cipher: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

