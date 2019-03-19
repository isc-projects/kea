// File created from ../../../src/lib/process/process_messages.mes on Tue Mar 19 2019 10:06

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace process {

extern const isc::log::MessageID DCTL_ALREADY_RUNNING = "DCTL_ALREADY_RUNNING";
extern const isc::log::MessageID DCTL_CCSESSION_ENDING = "DCTL_CCSESSION_ENDING";
extern const isc::log::MessageID DCTL_CCSESSION_STARTING = "DCTL_CCSESSION_STARTING";
extern const isc::log::MessageID DCTL_CFG_FILE_RELOAD_ERROR = "DCTL_CFG_FILE_RELOAD_ERROR";
extern const isc::log::MessageID DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD = "DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD";
extern const isc::log::MessageID DCTL_COMMAND_RECEIVED = "DCTL_COMMAND_RECEIVED";
extern const isc::log::MessageID DCTL_CONFIG_CHECK_COMPLETE = "DCTL_CONFIG_CHECK_COMPLETE";
extern const isc::log::MessageID DCTL_CONFIG_COMPLETE = "DCTL_CONFIG_COMPLETE";
extern const isc::log::MessageID DCTL_CONFIG_FETCH = "DCTL_CONFIG_FETCH";
extern const isc::log::MessageID DCTL_CONFIG_FILE_LOAD_FAIL = "DCTL_CONFIG_FILE_LOAD_FAIL";
extern const isc::log::MessageID DCTL_CONFIG_LOAD_FAIL = "DCTL_CONFIG_LOAD_FAIL";
extern const isc::log::MessageID DCTL_CONFIG_START = "DCTL_CONFIG_START";
extern const isc::log::MessageID DCTL_CONFIG_STUB = "DCTL_CONFIG_STUB";
extern const isc::log::MessageID DCTL_CONFIG_UPDATE = "DCTL_CONFIG_UPDATE";
extern const isc::log::MessageID DCTL_INIT_PROCESS = "DCTL_INIT_PROCESS";
extern const isc::log::MessageID DCTL_INIT_PROCESS_FAIL = "DCTL_INIT_PROCESS_FAIL";
extern const isc::log::MessageID DCTL_NOT_RUNNING = "DCTL_NOT_RUNNING";
extern const isc::log::MessageID DCTL_OPEN_CONFIG_DB = "DCTL_OPEN_CONFIG_DB";
extern const isc::log::MessageID DCTL_PARSER_FAIL = "DCTL_PARSER_FAIL";
extern const isc::log::MessageID DCTL_PID_FILE_ERROR = "DCTL_PID_FILE_ERROR";
extern const isc::log::MessageID DCTL_PROCESS_FAILED = "DCTL_PROCESS_FAILED";
extern const isc::log::MessageID DCTL_RUN_PROCESS = "DCTL_RUN_PROCESS";
extern const isc::log::MessageID DCTL_SESSION_FAIL = "DCTL_SESSION_FAIL";
extern const isc::log::MessageID DCTL_SHUTDOWN = "DCTL_SHUTDOWN";
extern const isc::log::MessageID DCTL_SHUTDOWN_SIGNAL_RECVD = "DCTL_SHUTDOWN_SIGNAL_RECVD";
extern const isc::log::MessageID DCTL_SIGNAL_ERROR = "DCTL_SIGNAL_ERROR";
extern const isc::log::MessageID DCTL_STANDALONE = "DCTL_STANDALONE";
extern const isc::log::MessageID DCTL_STARTING = "DCTL_STARTING";
extern const isc::log::MessageID DCTL_UNSUPPORTED_SIGNAL = "DCTL_UNSUPPORTED_SIGNAL";

} // namespace process
} // namespace isc

namespace {

const char* values[] = {
    "DCTL_ALREADY_RUNNING", "%1 already running? %2",
    "DCTL_CCSESSION_ENDING", "%1 ending control channel session",
    "DCTL_CCSESSION_STARTING", "%1 starting control channel session, specfile: %2",
    "DCTL_CFG_FILE_RELOAD_ERROR", "configuration reload failed: %1, reverting to current configuration.",
    "DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD", "OS signal %1 received, reloading configuration from file: %2",
    "DCTL_COMMAND_RECEIVED", "%1 received command: %2, arguments: %3",
    "DCTL_CONFIG_CHECK_COMPLETE", "server has completed configuration check: %1, result: %2",
    "DCTL_CONFIG_COMPLETE", "server has completed configuration: %1",
    "DCTL_CONFIG_FETCH", "Fetching configuration data from config backends.",
    "DCTL_CONFIG_FILE_LOAD_FAIL", "%1 reason: %2",
    "DCTL_CONFIG_LOAD_FAIL", "%1 configuration failed to load: %2",
    "DCTL_CONFIG_START", "parsing new configuration: %1",
    "DCTL_CONFIG_STUB", "%1 configuration stub handler called",
    "DCTL_CONFIG_UPDATE", "%1 updated configuration received: %2",
    "DCTL_INIT_PROCESS", "%1 initializing the application",
    "DCTL_INIT_PROCESS_FAIL", "%1 application initialization failed: %2",
    "DCTL_NOT_RUNNING", "%1 application instance is not running",
    "DCTL_OPEN_CONFIG_DB", "Opening configuration database: %1",
    "DCTL_PARSER_FAIL", ": %1",
    "DCTL_PID_FILE_ERROR", "%1 could not create a PID file: %2",
    "DCTL_PROCESS_FAILED", "%1 application execution failed: %2",
    "DCTL_RUN_PROCESS", "%1 starting application event loop",
    "DCTL_SESSION_FAIL", "%1 controller failed to establish Kea session: %1",
    "DCTL_SHUTDOWN", "%1 has shut down, pid: %2, version: %3",
    "DCTL_SHUTDOWN_SIGNAL_RECVD", "OS signal %1 received, starting shutdown",
    "DCTL_SIGNAL_ERROR", "signal handler for signal %1, threw an unexpected exception: %2",
    "DCTL_STANDALONE", "%1 skipping message queue, running standalone",
    "DCTL_STARTING", "%1 starting, pid: %2, version: %3",
    "DCTL_UNSUPPORTED_SIGNAL", "ignoring reception of unsupported signal: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

