// File created from src/lib/process/process_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace process {

extern const isc::log::MessageID DCTL_ALREADY_RUNNING = "DCTL_ALREADY_RUNNING";
extern const isc::log::MessageID DCTL_CFG_FILE_RELOAD_ERROR = "DCTL_CFG_FILE_RELOAD_ERROR";
extern const isc::log::MessageID DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD = "DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD";
extern const isc::log::MessageID DCTL_CONFIG_CHECK_COMPLETE = "DCTL_CONFIG_CHECK_COMPLETE";
extern const isc::log::MessageID DCTL_CONFIG_COMPLETE = "DCTL_CONFIG_COMPLETE";
extern const isc::log::MessageID DCTL_CONFIG_DEPRECATED = "DCTL_CONFIG_DEPRECATED";
extern const isc::log::MessageID DCTL_CONFIG_FETCH = "DCTL_CONFIG_FETCH";
extern const isc::log::MessageID DCTL_CONFIG_FILE_LOAD_FAIL = "DCTL_CONFIG_FILE_LOAD_FAIL";
extern const isc::log::MessageID DCTL_CONFIG_START = "DCTL_CONFIG_START";
extern const isc::log::MessageID DCTL_DB_OPEN_CONNECTION_WITH_RETRY_FAILED = "DCTL_DB_OPEN_CONNECTION_WITH_RETRY_FAILED";
extern const isc::log::MessageID DCTL_DEPRECATED_OUTPUT_OPTIONS = "DCTL_DEPRECATED_OUTPUT_OPTIONS";
extern const isc::log::MessageID DCTL_DEVELOPMENT_VERSION = "DCTL_DEVELOPMENT_VERSION";
extern const isc::log::MessageID DCTL_INIT_PROCESS = "DCTL_INIT_PROCESS";
extern const isc::log::MessageID DCTL_INIT_PROCESS_FAIL = "DCTL_INIT_PROCESS_FAIL";
extern const isc::log::MessageID DCTL_NOT_RUNNING = "DCTL_NOT_RUNNING";
extern const isc::log::MessageID DCTL_OPEN_CONFIG_DB = "DCTL_OPEN_CONFIG_DB";
extern const isc::log::MessageID DCTL_PARSER_FAIL = "DCTL_PARSER_FAIL";
extern const isc::log::MessageID DCTL_PID_FILE_ERROR = "DCTL_PID_FILE_ERROR";
extern const isc::log::MessageID DCTL_PROCESS_FAILED = "DCTL_PROCESS_FAILED";
extern const isc::log::MessageID DCTL_RUN_PROCESS = "DCTL_RUN_PROCESS";
extern const isc::log::MessageID DCTL_SHUTDOWN = "DCTL_SHUTDOWN";
extern const isc::log::MessageID DCTL_SHUTDOWN_SIGNAL_RECVD = "DCTL_SHUTDOWN_SIGNAL_RECVD";
extern const isc::log::MessageID DCTL_STANDALONE = "DCTL_STANDALONE";
extern const isc::log::MessageID DCTL_STARTING = "DCTL_STARTING";
extern const isc::log::MessageID DCTL_UNLOAD_LIBRARIES_ERROR = "DCTL_UNLOAD_LIBRARIES_ERROR";
extern const isc::log::MessageID DCTL_UNSUPPORTED_SIGNAL = "DCTL_UNSUPPORTED_SIGNAL";

} // namespace process
} // namespace isc

namespace {

const char* values[] = {
    "DCTL_ALREADY_RUNNING", "%1 already running? %2",
    "DCTL_CFG_FILE_RELOAD_ERROR", "configuration reload failed: %1, reverting to current configuration.",
    "DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD", "OS signal %1 received, reloading configuration from file: %2",
    "DCTL_CONFIG_CHECK_COMPLETE", "server has completed configuration check: %1, result: %2",
    "DCTL_CONFIG_COMPLETE", "server has completed configuration: %1",
    "DCTL_CONFIG_DEPRECATED", "server configuration includes a deprecated object: %1",
    "DCTL_CONFIG_FETCH", "Fetching configuration data from config backends.",
    "DCTL_CONFIG_FILE_LOAD_FAIL", "%1 reason: %2",
    "DCTL_CONFIG_START", "parsing new configuration: %1",
    "DCTL_DB_OPEN_CONNECTION_WITH_RETRY_FAILED", "Failed to connect to database: %1 with error: %2",
    "DCTL_DEPRECATED_OUTPUT_OPTIONS", "The output_options parameter is deprecated. Use output-options parameter instead.",
    "DCTL_DEVELOPMENT_VERSION", "This software is a development branch of Kea. It is not recommended for production use.",
    "DCTL_INIT_PROCESS", "%1 initializing the application",
    "DCTL_INIT_PROCESS_FAIL", "%1 application initialization failed: %2",
    "DCTL_NOT_RUNNING", "%1 application instance is not running",
    "DCTL_OPEN_CONFIG_DB", "Opening configuration database: %1",
    "DCTL_PARSER_FAIL", "Parser error: %1",
    "DCTL_PID_FILE_ERROR", "%1 could not create a PID file: %2",
    "DCTL_PROCESS_FAILED", "%1 application execution failed: %2",
    "DCTL_RUN_PROCESS", "%1 starting application event loop",
    "DCTL_SHUTDOWN", "%1 has shut down, pid: %2, version: %3",
    "DCTL_SHUTDOWN_SIGNAL_RECVD", "OS signal %1 received, starting shutdown",
    "DCTL_STANDALONE", "%1 skipping message queue, running standalone",
    "DCTL_STARTING", "%1 starting, pid: %2, version: %3 (%4)",
    "DCTL_UNLOAD_LIBRARIES_ERROR", "error unloading hooks libraries during shutdown: %1",
    "DCTL_UNSUPPORTED_SIGNAL", "ignoring reception of unsupported signal: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

