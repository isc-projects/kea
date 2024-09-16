// File created from ../../../../src/hooks/dhcp/pgsql_hb/pgsql_hb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID PGSQL_HB_DB = "PGSQL_HB_DB";
extern const isc::log::MessageID PGSQL_HB_DEINIT_OK = "PGSQL_HB_DEINIT_OK";
extern const isc::log::MessageID PGSQL_HB_INIT_OK = "PGSQL_HB_INIT_OK";

namespace {

const char* values[] = {
    "PGSQL_HB_DB", "opening PostgreSQL hosts database: %1",
    "PGSQL_HB_DEINIT_OK", "unloading PostgreSQL HB hooks library successful",
    "PGSQL_HB_INIT_OK", "loading PostgreSQL HB hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

