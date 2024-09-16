// File created from ../../../../src/hooks/dhcp/mysql_lb/mysql_lb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID MYSQL_LB_DB = "MYSQL_LB_DB";
extern const isc::log::MessageID MYSQL_LB_DEINIT_OK = "MYSQL_LB_DEINIT_OK";
extern const isc::log::MessageID MYSQL_LB_INIT_OK = "MYSQL_LB_INIT_OK";

namespace {

const char* values[] = {
    "MYSQL_LB_DB", "opening MySQL lease database: %1",
    "MYSQL_LB_DEINIT_OK", "unloading MySQL LB hooks library successful",
    "MYSQL_LB_INIT_OK", "loading MySQL LB hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

