// File created from ../../../../src/hooks/dhcp/stat_cmds/stat_cmds_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID STAT_CMDS_DEINIT_OK = "STAT_CMDS_DEINIT_OK";
extern const isc::log::MessageID STAT_CMDS_INIT_OK = "STAT_CMDS_INIT_OK";
extern const isc::log::MessageID STAT_CMDS_LEASE4_FAILED = "STAT_CMDS_LEASE4_FAILED";
extern const isc::log::MessageID STAT_CMDS_LEASE4_GET = "STAT_CMDS_LEASE4_GET";
extern const isc::log::MessageID STAT_CMDS_LEASE4_GET_FAILED = "STAT_CMDS_LEASE4_GET_FAILED";
extern const isc::log::MessageID STAT_CMDS_LEASE4_GET_INVALID = "STAT_CMDS_LEASE4_GET_INVALID";
extern const isc::log::MessageID STAT_CMDS_LEASE4_GET_NO_SUBNETS = "STAT_CMDS_LEASE4_GET_NO_SUBNETS";
extern const isc::log::MessageID STAT_CMDS_LEASE4_ORPHANED_STATS = "STAT_CMDS_LEASE4_ORPHANED_STATS";
extern const isc::log::MessageID STAT_CMDS_LEASE6_FAILED = "STAT_CMDS_LEASE6_FAILED";
extern const isc::log::MessageID STAT_CMDS_LEASE6_GET = "STAT_CMDS_LEASE6_GET";
extern const isc::log::MessageID STAT_CMDS_LEASE6_GET_FAILED = "STAT_CMDS_LEASE6_GET_FAILED";
extern const isc::log::MessageID STAT_CMDS_LEASE6_GET_INVALID = "STAT_CMDS_LEASE6_GET_INVALID";
extern const isc::log::MessageID STAT_CMDS_LEASE6_GET_NO_SUBNETS = "STAT_CMDS_LEASE6_GET_NO_SUBNETS";
extern const isc::log::MessageID STAT_CMDS_LEASE6_ORPHANED_STATS = "STAT_CMDS_LEASE6_ORPHANED_STATS";

namespace {

const char* values[] = {
    "STAT_CMDS_DEINIT_OK", "unloading Stat Commands hooks library successful",
    "STAT_CMDS_INIT_OK", "loading Stat Commands hooks library successful",
    "STAT_CMDS_LEASE4_FAILED", "stat-lease4-get command failed: reason: %1",
    "STAT_CMDS_LEASE4_GET", "stat-lease4-get command successful, parameters: %1 rows found: %2",
    "STAT_CMDS_LEASE4_GET_FAILED", "stat-lease4-get command failed: parameters: %1, reason: %2",
    "STAT_CMDS_LEASE4_GET_INVALID", "stat-lease4-get command is malformed or invalid, reason: %1",
    "STAT_CMDS_LEASE4_GET_NO_SUBNETS", "stat-lease4-get, parameters: %1, %2\"",
    "STAT_CMDS_LEASE4_ORPHANED_STATS", "stat-lease4-get command omitted statistics for one or more non-existent subnets",
    "STAT_CMDS_LEASE6_FAILED", "stat-lease6-get command failed: reason: %1",
    "STAT_CMDS_LEASE6_GET", "stat-lease6-get command successful, parameters: %1 rows found: %2",
    "STAT_CMDS_LEASE6_GET_FAILED", "stat-lease6-get command failed: parameters: %1, reason: %2",
    "STAT_CMDS_LEASE6_GET_INVALID", "stat-lease6-get command is malformed or invalid, reason: %1",
    "STAT_CMDS_LEASE6_GET_NO_SUBNETS", "stat-lease6-get, parameters: %1, %2\"",
    "STAT_CMDS_LEASE6_ORPHANED_STATS", "stat-lease6-get command omitted statistics for one or more non-existent subnets",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

