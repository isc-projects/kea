// File created from src/hooks/dhcp/perfmon/perfmon_messages.mes

#ifndef PERFMON_MESSAGES_H
#define PERFMON_MESSAGES_H

#include <log/message_types.h>

extern const isc::log::MessageID PERFMON_ALARM_CLEARED;
extern const isc::log::MessageID PERFMON_ALARM_TRIGGERED;
extern const isc::log::MessageID PERFMON_CMDS_CONTROL_ERROR;
extern const isc::log::MessageID PERFMON_CMDS_CONTROL_OK;
extern const isc::log::MessageID PERFMON_CMDS_GET_ALL_DURATIONS_ERROR;
extern const isc::log::MessageID PERFMON_CMDS_GET_ALL_DURATIONS_OK;
extern const isc::log::MessageID PERFMON_DEINIT_OK;
extern const isc::log::MessageID PERFMON_DHCP4_PKT_EVENTS;
extern const isc::log::MessageID PERFMON_DHCP4_PKT_PROCESS_ERROR;
extern const isc::log::MessageID PERFMON_DHCP4_SOCKET_RECEIVED_TIME_SUPPORT;
extern const isc::log::MessageID PERFMON_DHCP6_PKT_EVENTS;
extern const isc::log::MessageID PERFMON_DHCP6_PKT_PROCESS_ERROR;
extern const isc::log::MessageID PERFMON_DHCP6_SOCKET_RECEIVED_TIME_SUPPORT;
extern const isc::log::MessageID PERFMON_INIT_FAILED;
extern const isc::log::MessageID PERFMON_INIT_OK;

#endif // PERFMON_MESSAGES_H
