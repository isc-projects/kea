// File created from ../../../src/lib/tcp/tcp_messages.mes

#ifndef TCP_MESSAGES_H
#define TCP_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace tcp {

extern const isc::log::MessageID MT_TCP_LISTENER_MGR_STARTED;
extern const isc::log::MessageID MT_TCP_LISTENER_MGR_STOPPED;
extern const isc::log::MessageID MT_TCP_LISTENER_MGR_STOPPING;
extern const isc::log::MessageID TCP_CLIENT_REQUEST_RECEIVED;
extern const isc::log::MessageID TCP_CONNECTION_CLOSE_CALLBACK_FAILED;
extern const isc::log::MessageID TCP_CONNECTION_REJECTED_BY_FILTER;
extern const isc::log::MessageID TCP_CONNECTION_SHUTDOWN;
extern const isc::log::MessageID TCP_CONNECTION_SHUTDOWN_FAILED;
extern const isc::log::MessageID TCP_CONNECTION_STOP;
extern const isc::log::MessageID TCP_CONNECTION_STOP_FAILED;
extern const isc::log::MessageID TCP_DATA_RECEIVED;
extern const isc::log::MessageID TCP_DATA_SENT;
extern const isc::log::MessageID TCP_IDLE_CONNECTION_TIMEOUT_OCCURRED;
extern const isc::log::MessageID TCP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED;
extern const isc::log::MessageID TCP_REQUEST_RECEIVED_FAILED;
extern const isc::log::MessageID TCP_REQUEST_RECEIVE_START;
extern const isc::log::MessageID TCP_SERVER_RESPONSE_SEND;
extern const isc::log::MessageID TCP_SERVER_RESPONSE_SEND_DETAILS;
extern const isc::log::MessageID TLS_CONNECTION_HANDSHAKE_FAILED;
extern const isc::log::MessageID TLS_CONNECTION_HANDSHAKE_START;
extern const isc::log::MessageID TLS_REQUEST_RECEIVE_START;
extern const isc::log::MessageID TLS_SERVER_RESPONSE_SEND;

} // namespace tcp
} // namespace isc

#endif // TCP_MESSAGES_H
