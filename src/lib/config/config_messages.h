// File created from ../../../src/lib/config/config_messages.mes on Fri Feb 08 2019 20:16

#ifndef CONFIG_MESSAGES_H
#define CONFIG_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace config {

extern const isc::log::MessageID COMMAND_ACCEPTOR_START;
extern const isc::log::MessageID COMMAND_DEREGISTERED;
extern const isc::log::MessageID COMMAND_EXTENDED_REGISTERED;
extern const isc::log::MessageID COMMAND_PROCESS_ERROR1;
extern const isc::log::MessageID COMMAND_PROCESS_ERROR2;
extern const isc::log::MessageID COMMAND_RECEIVED;
extern const isc::log::MessageID COMMAND_REGISTERED;
extern const isc::log::MessageID COMMAND_RESPONSE_ERROR;
extern const isc::log::MessageID COMMAND_SOCKET_ACCEPT_FAIL;
extern const isc::log::MessageID COMMAND_SOCKET_CLOSED_BY_FOREIGN_HOST;
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_CANCEL_FAIL;
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_CLOSED;
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_CLOSE_FAIL;
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_OPENED;
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_SHUTDOWN_FAIL;
extern const isc::log::MessageID COMMAND_SOCKET_CONNECTION_TIMEOUT;
extern const isc::log::MessageID COMMAND_SOCKET_READ;
extern const isc::log::MessageID COMMAND_SOCKET_READ_FAIL;
extern const isc::log::MessageID COMMAND_SOCKET_WRITE;
extern const isc::log::MessageID COMMAND_SOCKET_WRITE_FAIL;
extern const isc::log::MessageID COMMAND_WATCH_SOCKET_CLEAR_ERROR;
extern const isc::log::MessageID COMMAND_WATCH_SOCKET_CLOSE_ERROR;
extern const isc::log::MessageID COMMAND_WATCH_SOCKET_MARK_READY_ERROR;

} // namespace config
} // namespace isc

#endif // CONFIG_MESSAGES_H
