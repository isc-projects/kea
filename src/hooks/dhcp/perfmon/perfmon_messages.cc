// File created from ../../../../src/hooks/dhcp/perfmon/perfmon_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID PERFMON_DEINIT_FAILED = "PERFMON_DEINIT_FAILED";
extern const isc::log::MessageID PERFMON_DEINIT_OK = "PERFMON_DEINIT_OK";
extern const isc::log::MessageID PERFMON_INIT_FAILED = "PERFMON_INIT_FAILED";
extern const isc::log::MessageID PERFMON_INIT_OK = "PERFMON_INIT_OK";

namespace {

const char* values[] = {
    "PERFMON_DEINIT_FAILED", "unloading PerfMon hooks library failed: %1",
    "PERFMON_DEINIT_OK", "unloading PerfMon hooks library successful",
    "PERFMON_INIT_FAILED", "loading PerfMon hooks library failed: %1",
    "PERFMON_INIT_OK", "loading PerfMon hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

