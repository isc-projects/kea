// File created from src/hooks/dhcp/lease_cmds/lease_cmds_messages.mes

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
extern const isc::log::MessageID LEASE_CMDS_DEINIT_OK = "LEASE_CMDS_DEINIT_OK";
extern const isc::log::MessageID LEASE_CMDS_DEL4 = "LEASE_CMDS_DEL4";
extern const isc::log::MessageID LEASE_CMDS_DEL4_FAILED = "LEASE_CMDS_DEL4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_DEL6 = "LEASE_CMDS_DEL6";
extern const isc::log::MessageID LEASE_CMDS_DEL6_FAILED = "LEASE_CMDS_DEL6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_GET4_FAILED = "LEASE_CMDS_GET4_FAILED";
extern const isc::log::MessageID LEASE_CMDS_GET6_FAILED = "LEASE_CMDS_GET6_FAILED";
extern const isc::log::MessageID LEASE_CMDS_INIT_OK = "LEASE_CMDS_INIT_OK";
extern const isc::log::MessageID LEASE_CMDS_LEASE4_OFFER_FAILED = "LEASE_CMDS_LEASE4_OFFER_FAILED";
extern const isc::log::MessageID LEASE_CMDS_LEASES4_COMMITTED_FAILED = "LEASE_CMDS_LEASES4_COMMITTED_FAILED";
extern const isc::log::MessageID LEASE_CMDS_LEASES6_COMMITTED_CONFLICT = "LEASE_CMDS_LEASES6_COMMITTED_CONFLICT";
extern const isc::log::MessageID LEASE_CMDS_LEASES6_COMMITTED_FAILED = "LEASE_CMDS_LEASES6_COMMITTED_FAILED";
extern const isc::log::MessageID LEASE_CMDS_LEASES6_COMMITTED_LEASE_ERROR = "LEASE_CMDS_LEASES6_COMMITTED_LEASE_ERROR";
extern const isc::log::MessageID LEASE_CMDS_LOAD_ERROR = "LEASE_CMDS_LOAD_ERROR";
extern const isc::log::MessageID LEASE_CMDS_PATH_SECURITY_WARNING = "LEASE_CMDS_PATH_SECURITY_WARNING";
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
extern const isc::log::MessageID SFLQ_POOL4_CREATE = "SFLQ_POOL4_CREATE";
extern const isc::log::MessageID SFLQ_POOL4_CREATE_FAILED = "SFLQ_POOL4_CREATE_FAILED";
extern const isc::log::MessageID SFLQ_POOL4_DEL = "SFLQ_POOL4_DEL";
extern const isc::log::MessageID SFLQ_POOL4_DEL_FAILED = "SFLQ_POOL4_DEL_FAILED";
extern const isc::log::MessageID SFLQ_POOL4_GET_ALL = "SFLQ_POOL4_GET_ALL";
extern const isc::log::MessageID SFLQ_POOL4_GET_ALL_FAILED = "SFLQ_POOL4_GET_ALL_FAILED";
extern const isc::log::MessageID SFLQ_POOL4_GET_BY_RANGE = "SFLQ_POOL4_GET_BY_RANGE";
extern const isc::log::MessageID SFLQ_POOL4_GET_BY_RANGE_FAILED = "SFLQ_POOL4_GET_BY_RANGE_FAILED";
extern const isc::log::MessageID SFLQ_POOL4_GET_BY_SUBNET = "SFLQ_POOL4_GET_BY_SUBNET";
extern const isc::log::MessageID SFLQ_POOL4_GET_BY_SUBNET_FAILED = "SFLQ_POOL4_GET_BY_SUBNET_FAILED";
extern const isc::log::MessageID SFLQ_POOL6_CREATE = "SFLQ_POOL6_CREATE";
extern const isc::log::MessageID SFLQ_POOL6_CREATE_FAILED = "SFLQ_POOL6_CREATE_FAILED";
extern const isc::log::MessageID SFLQ_POOL6_DEL = "SFLQ_POOL6_DEL";
extern const isc::log::MessageID SFLQ_POOL6_DEL_FAILED = "SFLQ_POOL6_DEL_FAILED";
extern const isc::log::MessageID SFLQ_POOL6_GET_ALL = "SFLQ_POOL6_GET_ALL";
extern const isc::log::MessageID SFLQ_POOL6_GET_ALL_FAILED = "SFLQ_POOL6_GET_ALL_FAILED";
extern const isc::log::MessageID SFLQ_POOL6_GET_BY_RANGE = "SFLQ_POOL6_GET_BY_RANGE";
extern const isc::log::MessageID SFLQ_POOL6_GET_BY_RANGE_FAILED = "SFLQ_POOL6_GET_BY_RANGE_FAILED";
extern const isc::log::MessageID SFLQ_POOL6_GET_BY_SUBNET = "SFLQ_POOL6_GET_BY_SUBNET";
extern const isc::log::MessageID SFLQ_POOL6_GET_BY_SUBNET_FAILED = "SFLQ_POOL6_GET_BY_SUBNET_FAILED";

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
    "LEASE_CMDS_DEINIT_OK", "unloading Lease Commands hooks library successful",
    "LEASE_CMDS_DEL4", "lease4-del command successful (address: %1)",
    "LEASE_CMDS_DEL4_FAILED", "lease4-del command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_DEL6", "lease4-del command successful (address: %1)",
    "LEASE_CMDS_DEL6_FAILED", "lease6-del command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_GET4_FAILED", "lease4-get command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_GET6_FAILED", "lease6-get command failed (parameters: %1, reason: %2)",
    "LEASE_CMDS_INIT_OK", "loading Lease Commands hooks library successful",
    "LEASE_CMDS_LEASE4_OFFER_FAILED", "processing error occurred evaluating binding variables: %1",
    "LEASE_CMDS_LEASES4_COMMITTED_FAILED", "processing error occurred evaluating binding variables: %1",
    "LEASE_CMDS_LEASES6_COMMITTED_CONFLICT", "could not updating lease: %1 for: %2",
    "LEASE_CMDS_LEASES6_COMMITTED_FAILED", "reason: %1",
    "LEASE_CMDS_LEASES6_COMMITTED_LEASE_ERROR", "evaluating binding-variables for lease: %1 for: %2, reason: %3",
    "LEASE_CMDS_LOAD_ERROR", "loading Lease Commands hooks library failed: %1",
    "LEASE_CMDS_PATH_SECURITY_WARNING", "lease file path specified is NOT SECURE: %1",
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
    "SFLQ_POOL4_CREATE", "sflq-pool4-create command succeeded, (parameters: %1)",
    "SFLQ_POOL4_CREATE_FAILED", "sflq-pool4-create command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL4_DEL", "sflq-pool4-del command succeeded, (parameters: %1) pools deleted: %2",
    "SFLQ_POOL4_DEL_FAILED", "sflq-pool4-del command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL4_GET_ALL", "sflq-pool4-get-all command succeeded, pools found: %1",
    "SFLQ_POOL4_GET_ALL_FAILED", "sflq-pool4-get-all command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL4_GET_BY_RANGE", "sflq-pool4-get-by-range command succeeded, (parameters: %1) pools found: %2",
    "SFLQ_POOL4_GET_BY_RANGE_FAILED", "sflq-pool4-get-by-range command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL4_GET_BY_SUBNET", "sflq-pool4-get-by-subnet command succeeded, (parameters: %1) pools found: %2",
    "SFLQ_POOL4_GET_BY_SUBNET_FAILED", "sflq-pool4-get-by-subnet command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL6_CREATE", "sflq-pool6-create command succeeded, (parameters: %1)",
    "SFLQ_POOL6_CREATE_FAILED", "sflq-pool6-create command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL6_DEL", "sflq-pool4-del command succeeded, (parameters: %1) pools deleted: %2",
    "SFLQ_POOL6_DEL_FAILED", "sflq-pool4-del command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL6_GET_ALL", "sflq-pool6-get-all command succeeded, pools found: %1",
    "SFLQ_POOL6_GET_ALL_FAILED", "sflq-pool6-get-all command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL6_GET_BY_RANGE", "sflq-pool6-get-by-range command succeeded, (parameters: %1) pools found: %2",
    "SFLQ_POOL6_GET_BY_RANGE_FAILED", "sflq-pool6-get-by-range command failed, (parameters: %1, reason: %2)",
    "SFLQ_POOL6_GET_BY_SUBNET", "sflq-pool6-get-by-subnet command succeeded, (parameters: %1) pools found: %2",
    "SFLQ_POOL6_GET_BY_SUBNET_FAILED", "sflq-pool6-get-by-subnet command failed, (parameters: %1, reason: %2)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

