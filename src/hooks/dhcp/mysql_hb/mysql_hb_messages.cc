// File created from ../../../../src/hooks/dhcp/mysql_hb/mysql_hb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID MYSQL_HB_DB = "MYSQL_HB_DB";
extern const isc::log::MessageID MYSQL_HB_DEINIT_OK = "MYSQL_HB_DEINIT_OK";
extern const isc::log::MessageID MYSQL_HB_INIT_OK = "MYSQL_HB_INIT_OK";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "MYSQL_HB_DB", "opening MySQL hosts database: %1",
    "MYSQL_HB_DEINIT_OK", "unloading MySQL HB hooks library successful",
    "MYSQL_HB_INIT_OK", "loading MySQL HB hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

