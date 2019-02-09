// File created from ../../../src/bin/netconf/netconf_messages.mes on Fri Feb 08 2019 20:57

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace netconf {

extern const isc::log::MessageID NETCONF_BOOT_UPDATE_COMPLETED = "NETCONF_BOOT_UPDATE_COMPLETED";
extern const isc::log::MessageID NETCONF_CONFIG_CHANGED_DETAIL = "NETCONF_CONFIG_CHANGED_DETAIL";
extern const isc::log::MessageID NETCONF_CONFIG_CHANGE_EVENT = "NETCONF_CONFIG_CHANGE_EVENT";
extern const isc::log::MessageID NETCONF_CONFIG_CHECK_FAIL = "NETCONF_CONFIG_CHECK_FAIL";
extern const isc::log::MessageID NETCONF_CONFIG_FAIL = "NETCONF_CONFIG_FAIL";
extern const isc::log::MessageID NETCONF_FAILED = "NETCONF_FAILED";
extern const isc::log::MessageID NETCONF_GET_CONFIG = "NETCONF_GET_CONFIG";
extern const isc::log::MessageID NETCONF_GET_CONFIG_FAILED = "NETCONF_GET_CONFIG_FAILED";
extern const isc::log::MessageID NETCONF_GET_CONFIG_STARTED = "NETCONF_GET_CONFIG_STARTED";
extern const isc::log::MessageID NETCONF_LOG_CHANGE_FAIL = "NETCONF_LOG_CHANGE_FAIL";
extern const isc::log::MessageID NETCONF_MODULE_INSTALL = "NETCONF_MODULE_INSTALL";
extern const isc::log::MessageID NETCONF_MODULE_MISSING_ERR = "NETCONF_MODULE_MISSING_ERR";
extern const isc::log::MessageID NETCONF_MODULE_MISSING_WARN = "NETCONF_MODULE_MISSING_WARN";
extern const isc::log::MessageID NETCONF_MODULE_REVISION_ERR = "NETCONF_MODULE_REVISION_ERR";
extern const isc::log::MessageID NETCONF_MODULE_REVISION_WARN = "NETCONF_MODULE_REVISION_WARN";
extern const isc::log::MessageID NETCONF_RUN_EXIT = "NETCONF_RUN_EXIT";
extern const isc::log::MessageID NETCONF_SET_CONFIG = "NETCONF_SET_CONFIG";
extern const isc::log::MessageID NETCONF_SET_CONFIG_FAILED = "NETCONF_SET_CONFIG_FAILED";
extern const isc::log::MessageID NETCONF_SET_CONFIG_STARTED = "NETCONF_SET_CONFIG_STARTED";
extern const isc::log::MessageID NETCONF_STARTED = "NETCONF_STARTED";
extern const isc::log::MessageID NETCONF_SUBSCRIBE_CONFIG = "NETCONF_SUBSCRIBE_CONFIG";
extern const isc::log::MessageID NETCONF_SUBSCRIBE_CONFIG_FAILED = "NETCONF_SUBSCRIBE_CONFIG_FAILED";
extern const isc::log::MessageID NETCONF_UPDATE_CONFIG = "NETCONF_UPDATE_CONFIG";
extern const isc::log::MessageID NETCONF_UPDATE_CONFIG_COMPLETED = "NETCONF_UPDATE_CONFIG_COMPLETED";
extern const isc::log::MessageID NETCONF_UPDATE_CONFIG_FAILED = "NETCONF_UPDATE_CONFIG_FAILED";
extern const isc::log::MessageID NETCONF_UPDATE_CONFIG_STARTED = "NETCONF_UPDATE_CONFIG_STARTED";
extern const isc::log::MessageID NETCONF_VALIDATE_CONFIG = "NETCONF_VALIDATE_CONFIG";
extern const isc::log::MessageID NETCONF_VALIDATE_CONFIG_COMPLETED = "NETCONF_VALIDATE_CONFIG_COMPLETED";
extern const isc::log::MessageID NETCONF_VALIDATE_CONFIG_FAILED = "NETCONF_VALIDATE_CONFIG_FAILED";
extern const isc::log::MessageID NETCONF_VALIDATE_CONFIG_REJECTED = "NETCONF_VALIDATE_CONFIG_REJECTED";
extern const isc::log::MessageID NETCONF_VALIDATE_CONFIG_STARTED = "NETCONF_VALIDATE_CONFIG_STARTED";

} // namespace netconf
} // namespace isc

namespace {

const char* values[] = {
    "NETCONF_BOOT_UPDATE_COMPLETED", "Boot-update configuration completed for server %1",
    "NETCONF_CONFIG_CHANGED_DETAIL", "YANG configuration changed: %1",
    "NETCONF_CONFIG_CHANGE_EVENT", "Received YANG configuration change %1 event",
    "NETCONF_CONFIG_CHECK_FAIL", "Netconf configuration check failed: %1",
    "NETCONF_CONFIG_FAIL", "Netconf configuration failed: %1",
    "NETCONF_FAILED", "application experienced a fatal error: %1",
    "NETCONF_GET_CONFIG", "got configuration from %1 server: %2",
    "NETCONF_GET_CONFIG_FAILED", "getting configuration from %1 server failed: %2",
    "NETCONF_GET_CONFIG_STARTED", "getting configuration from %1 server",
    "NETCONF_LOG_CHANGE_FAIL", "Netconf configuration change logging failed: %1",
    "NETCONF_MODULE_INSTALL", "Sysrepo (un)installs a module: %1 (revision %2)",
    "NETCONF_MODULE_MISSING_ERR", "Missing essential module %1 in sysrepo",
    "NETCONF_MODULE_MISSING_WARN", "Missing module %1 in sysrepo",
    "NETCONF_MODULE_REVISION_ERR", "Essential module %1 does have the right revision: expected %2, got %3",
    "NETCONF_MODULE_REVISION_WARN", "Module %1 does have the right revision: expected %2, got %3",
    "NETCONF_RUN_EXIT", "application is exiting the event loop",
    "NETCONF_SET_CONFIG", "set configuration to %1 server: %2",
    "NETCONF_SET_CONFIG_FAILED", "setting configuration to %1 server failed: %2",
    "NETCONF_SET_CONFIG_STARTED", "setting configuration to %1 server",
    "NETCONF_STARTED", "Netconf (version %1) started",
    "NETCONF_SUBSCRIBE_CONFIG", "subscribing configuration changes for %1 server with %2 module",
    "NETCONF_SUBSCRIBE_CONFIG_FAILED", "subscribe configuration changes for %1 server with %2 module failed: %3",
    "NETCONF_UPDATE_CONFIG", "updating configuration with %1 server: %2",
    "NETCONF_UPDATE_CONFIG_COMPLETED", "completed updating configuration for %1 server",
    "NETCONF_UPDATE_CONFIG_FAILED", "updating configuration with %1 server: %2",
    "NETCONF_UPDATE_CONFIG_STARTED", "started updating configuration for %1 server",
    "NETCONF_VALIDATE_CONFIG", "validating configuration with %1 server: %2",
    "NETCONF_VALIDATE_CONFIG_COMPLETED", "completed validating configuration for %1 server",
    "NETCONF_VALIDATE_CONFIG_FAILED", "validating configuration with %1 server got an error: %2",
    "NETCONF_VALIDATE_CONFIG_REJECTED", "validating configuration with %1 server was rejected: %2",
    "NETCONF_VALIDATE_CONFIG_STARTED", "started validating configuration for %1 server",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

