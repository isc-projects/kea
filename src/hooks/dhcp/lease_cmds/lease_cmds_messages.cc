// File created from ../../../../src/hooks/dhcp/lease_cmds/lease_cmds_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID LEASE_CMDS_ADD4 = "LEASE_CMDS_ADD4";
extern const isc::log::MessageID LEASE_CMDS_ADD4_CONFLICT = "LEASE_CMDS_ADD4_CONFLICT";
extern const isc::log::MessageID LEASE_CMDS_ADD4_FAILED = "LEASE_CMDS_ADD4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_ADD6 = "LEASE_CMDS_ADD6";
extern const isc::log::MessageID LEASE_CMDS_ADD6_CONFLICT = "LEASE_CMDS_ADD6_CONFLICT";
extern const isc::log::MessageID LEASE_CMDS_ADD6_FAILED = "LEASE_CMDS_ADD6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_BULK_APPLY6 = "LEASE_CMDS_BULK_APPLY6";
extern const isc::log::MessageID LEASE_CMDS_BULK_APPLY6_FAILED = "LEASE_CMDS_BULK_APPLY6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_DEINIT_FAILED = "LEASE_CMDS_DEINIT_FAILED";
extern const isc::log::MessageID LEASE_CMDS_DEINIT_OK = "LEASE_CMDS_DEINIT_OK";
extern const isc::log::MessageID LEASE_CMDS_DEL4 = "LEASE_CMDS_DEL4";
extern const isc::log::MessageID LEASE_CMDS_DEL4_FAILED = "LEASE_CMDS_DEL4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_DEL6 = "LEASE_CMDS_DEL6";
extern const isc::log::MessageID LEASE_CMDS_DEL6_FAILED = "LEASE_CMDS_DEL6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_GET4_FAILED = "LEASE_CMDS_GET4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_GET6_FAILED = "LEASE_CMDS_GET6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_INIT_FAILED = "LEASE_CMDS_INIT_FAILED";
extern const isc::log::MessageID LEASE_CMDS_INIT_OK = "LEASE_CMDS_INIT_OK";
extern const isc::log::MessageID LEASE_CMDS_RESEND_DDNS4 = "LEASE_CMDS_RESEND_DDNS4";
extern const isc::log::MessageID LEASE_CMDS_RESEND_DDNS4_FAILED = "LEASE_CMDS_RESEND_DDNS4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_RESEND_DDNS6 = "LEASE_CMDS_RESEND_DDNS6";
extern const isc::log::MessageID LEASE_CMDS_RESEND_DDNS6_FAILED = "LEASE_CMDS_RESEND_DDNS6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_UPDATE4 = "LEASE_CMDS_UPDATE4";
extern const isc::log::MessageID LEASE_CMDS_UPDATE4_CONFLICT = "LEASE_CMDS_UPDATE4_CONFLICT";
extern const isc::log::MessageID LEASE_CMDS_UPDATE4_FAILED = "LEASE_CMDS_UPDATE4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_UPDATE6 = "LEASE_CMDS_UPDATE6";
extern const isc::log::MessageID LEASE_CMDS_UPDATE6_CONFLICT = "LEASE_CMDS_UPDATE6_CONFLICT";
extern const isc::log::MessageID LEASE_CMDS_UPDATE6_FAILED = "LEASE_CMDS_UPDATE6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_WIPE4 = "LEASE_CMDS_WIPE4";
extern const isc::log::MessageID LEASE_CMDS_WIPE4_FAILED = "LEASE_CMDS_WIPE4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_WIPE6 = "LEASE_CMDS_WIPE6";
extern const isc::log::MessageID LEASE_CMDS_WIPE6_FAILED = "LEASE_CMDS_WIPE6_FAILED";

namespace {

const char* values[] = {
    "LEASE_CMDS_ADD4", "lease4-add command successful (address: %1)",
    "LEASE_CMDS_ADD4_CONFLICT", "lease4-add command failed due to conflict (parameters: %1, reason: %2)",
    "LEASE_CMDS_ADD4_FAILED", "lease4-add command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_ADD6", "lease6-add command successful (address: %1)",
    "LEASE_CMDS_ADD6_CONFLICT", "lease6-add command failed due to conflict (parameters: %1, reason: %2)",
    "LEASE_CMDS_ADD6_FAILED", "lease6-add command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_BULK_APPLY6", "lease6-bulk-apply command successful (applied addresses count: %1)",
    "LEASE_CMDS_BULK_APPLY6_FAILED", "lease6-bulk-apply command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_DEINIT_FAILED", "unloading Lease Commands hooks library failed: %1",
    "LEASE_CMDS_DEINIT_OK", "unloading Lease Commands hooks library successful",
    "LEASE_CMDS_DEL4", "lease4-del command successful (address: %1)",
    "LEASE_CMDS_DEL4_FAILED", "lease4-del command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_DEL6", "lease4-del command successful (address: %1)",
    "LEASE_CMDS_DEL6_FAILED", "lease6-del command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_GET4_FAILED", "lease4-get command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_GET6_FAILED", "lease6-get command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_INIT_FAILED", "loading Lease Commands hooks library failed: %1",
    "LEASE_CMDS_INIT_OK", "loading Lease Commands hooks library successful",
    "LEASE_CMDS_RESEND_DDNS4", "lease4-resend-ddns command successful: %1",
    "LEASE_CMDS_RESEND_DDNS4_FAILED", "lease4-resend-ddns command failed: %1",
    "LEASE_CMDS_RESEND_DDNS6", "lease6-resend-ddns command successful: %1",
    "LEASE_CMDS_RESEND_DDNS6_FAILED", "lease6-resend-ddns command failed: %1",
    "LEASE_CMDS_UPDATE4", "lease4-update command successful (address: %1)",
    "LEASE_CMDS_UPDATE4_CONFLICT", "lease4-update command failed due to conflict (parameters: %1, reason: %2)",
    "LEASE_CMDS_UPDATE4_FAILED", "lease4-update command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_UPDATE6", "lease6-update command successful (address: %1)",
    "LEASE_CMDS_UPDATE6_CONFLICT", "lease6-update command failed due to conflict (parameters: %1, reason: %2)",
    "LEASE_CMDS_UPDATE6_FAILED", "lease6-add command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_WIPE4", "lease4-wipe command successful (parameters: %1)",
    "LEASE_CMDS_WIPE4_FAILED", "lease4-wipe command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_WIPE6", "lease6-wipe command successful (parameters: %1)",
    "LEASE_CMDS_WIPE6_FAILED", "lease6-wipe command failed (parameters: %1, reason: %2)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

