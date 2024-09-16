// File created from ../../../../src/hooks/dhcp/pgsql_lb/pgsql_lb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID PGSQL_LB_DB = "PGSQL_LB_DB";
extern const isc::log::MessageID PGSQL_LB_DEINIT_OK = "PGSQL_LB_DEINIT_OK";
extern const isc::log::MessageID PGSQL_LB_INIT_OK = "PGSQL_LB_INIT_OK";

namespace {

const char* values[] = {
    "PGSQL_LB_DB", "opening PostgreSQL lease database: %1",
    "PGSQL_LB_DEINIT_OK", "unloading PostgreSQL LB hooks library successful",
    "PGSQL_LB_INIT_OK", "loading PostgreSQL LB hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

