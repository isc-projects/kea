// File created from ../../../../src/hooks/dhcp/perfmon/perfmon_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID PERFMON_ALARM_CLEARED = "PERFMON_ALARM_CLEARED";
extern const isc::log::MessageID PERFMON_ALARM_TRIGGERED = "PERFMON_ALARM_TRIGGERED";
extern const isc::log::MessageID PERFMON_DEINIT_FAILED = "PERFMON_DEINIT_FAILED";
extern const isc::log::MessageID PERFMON_DEINIT_OK = "PERFMON_DEINIT_OK";
extern const isc::log::MessageID PERFMON_DHCP4_PKT_EVENTS = "PERFMON_DHCP4_PKT_EVENTS";
extern const isc::log::MessageID PERFMON_DHCP4_PKT_PROCESS_ERROR = "PERFMON_DHCP4_PKT_PROCESS_ERROR";
extern const isc::log::MessageID PERFMON_DHCP4_SOCKET_RECEIVED_TIME_SUPPORT = "PERFMON_DHCP4_SOCKET_RECEIVED_TIME_SUPPORT";
extern const isc::log::MessageID PERFMON_DHCP6_PKT_EVENTS = "PERFMON_DHCP6_PKT_EVENTS";
extern const isc::log::MessageID PERFMON_DHCP6_PKT_PROCESS_ERROR = "PERFMON_DHCP6_PKT_PROCESS_ERROR";
extern const isc::log::MessageID PERFMON_DHCP6_SOCKET_RECEIVED_TIME_SUPPORT = "PERFMON_DHCP6_SOCKET_RECEIVED_TIME_SUPPORT";
extern const isc::log::MessageID PERFMON_INIT_FAILED = "PERFMON_INIT_FAILED";
extern const isc::log::MessageID PERFMON_INIT_OK = "PERFMON_INIT_OK";

namespace {

const char* values[] = {
    "PERFMON_ALARM_CLEARED", "Alarm for %1 has been cleared, reported average duration %2 is now below low-water-ms: %3",
    "PERFMON_ALARM_TRIGGERED", "Alarm for %1 has been triggered since %2, reported average duration %3 exceeds high-water-ms: %4",
    "PERFMON_DEINIT_FAILED", "unloading PerfMon hooks library failed: %1",
    "PERFMON_DEINIT_OK", "unloading PerfMon hooks library successful",
    "PERFMON_DHCP4_PKT_EVENTS", "query: %1 events=[%2]",
    "PERFMON_DHCP4_PKT_PROCESS_ERROR", "Packet event stack was not processed for query %1, reason %2",
    "PERFMON_DHCP4_SOCKET_RECEIVED_TIME_SUPPORT", "Kernel supports socket received time? %1",
    "PERFMON_DHCP6_PKT_EVENTS", "query: %1 events=[%2]",
    "PERFMON_DHCP6_PKT_PROCESS_ERROR", "Packet event stack was not processed for query %1, reason %2",
    "PERFMON_DHCP6_SOCKET_RECEIVED_TIME_SUPPORT", "Kernel supports socket received time? %1",
    "PERFMON_INIT_FAILED", "loading PerfMon hooks library failed: %1",
    "PERFMON_INIT_OK", "loading PerfMon hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

