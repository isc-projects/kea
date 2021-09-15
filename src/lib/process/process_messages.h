// File created from ../../../src/lib/process/process_messages.mes

#ifndef PROCESS_MESSAGES_H
#define PROCESS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace process {

extern const isc::log::MessageID DCTL_ALREADY_RUNNING;
extern const isc::log::MessageID DCTL_CCSESSION_ENDING;
extern const isc::log::MessageID DCTL_CFG_FILE_RELOAD_ERROR;
extern const isc::log::MessageID DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD;
extern const isc::log::MessageID DCTL_COMMAND_RECEIVED;
extern const isc::log::MessageID DCTL_CONFIG_CHECK_COMPLETE;
extern const isc::log::MessageID DCTL_CONFIG_COMPLETE;
extern const isc::log::MessageID DCTL_CONFIG_DEPRECATED;
extern const isc::log::MessageID DCTL_CONFIG_FETCH;
extern const isc::log::MessageID DCTL_CONFIG_FILE_LOAD_FAIL;
extern const isc::log::MessageID DCTL_CONFIG_LOAD_FAIL;
extern const isc::log::MessageID DCTL_CONFIG_START;
extern const isc::log::MessageID DCTL_CONFIG_STUB;
extern const isc::log::MessageID DCTL_CONFIG_UPDATE;
extern const isc::log::MessageID DCTL_DEVELOPMENT_VERSION;
extern const isc::log::MessageID DCTL_INIT_PROCESS;
extern const isc::log::MessageID DCTL_INIT_PROCESS_FAIL;
extern const isc::log::MessageID DCTL_NOT_RUNNING;
extern const isc::log::MessageID DCTL_OPEN_CONFIG_DB;
extern const isc::log::MessageID DCTL_PARSER_FAIL;
extern const isc::log::MessageID DCTL_PID_FILE_ERROR;
extern const isc::log::MessageID DCTL_PROCESS_FAILED;
extern const isc::log::MessageID DCTL_RUN_PROCESS;
extern const isc::log::MessageID DCTL_SESSION_FAIL;
extern const isc::log::MessageID DCTL_SHUTDOWN;
extern const isc::log::MessageID DCTL_SHUTDOWN_SIGNAL_RECVD;
extern const isc::log::MessageID DCTL_STANDALONE;
extern const isc::log::MessageID DCTL_STARTING;
extern const isc::log::MessageID DCTL_UNLOAD_LIBRARIES_ERROR;
extern const isc::log::MessageID DCTL_UNSUPPORTED_SIGNAL;

} // namespace process
} // namespace isc

#endif // PROCESS_MESSAGES_H
