// File created from ../../../src/lib/http/http_messages.mes

#ifndef HTTP_MESSAGES_H
#define HTTP_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace http {

extern const isc::log::MessageID HTTPS_REQUEST_RECEIVE_START;
extern const isc::log::MessageID HTTP_BAD_CLIENT_REQUEST_RECEIVED;
extern const isc::log::MessageID HTTP_BAD_CLIENT_REQUEST_RECEIVED_DETAILS;
extern const isc::log::MessageID HTTP_BAD_SERVER_RESPONSE_RECEIVED;
extern const isc::log::MessageID HTTP_BAD_SERVER_RESPONSE_RECEIVED_DETAILS;
extern const isc::log::MessageID HTTP_CLIENT_MT_STARTED;
extern const isc::log::MessageID HTTP_CLIENT_QUEUE_SIZE_GROWING;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_RECEIVED;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_RECEIVED_DETAILS;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_SEND;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_SEND_DETAILS;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_TIMEOUT_OCCURRED;
extern const isc::log::MessageID HTTP_CONNECTION_CLOSE_CALLBACK_FAILED;
extern const isc::log::MessageID HTTP_CONNECTION_HANDSHAKE_FAILED;
extern const isc::log::MessageID HTTP_CONNECTION_HANDSHAKE_START;
extern const isc::log::MessageID HTTP_CONNECTION_SHUTDOWN;
extern const isc::log::MessageID HTTP_CONNECTION_SHUTDOWN_FAILED;
extern const isc::log::MessageID HTTP_CONNECTION_STOP;
extern const isc::log::MessageID HTTP_CONNECTION_STOP_FAILED;
extern const isc::log::MessageID HTTP_DATA_RECEIVED;
extern const isc::log::MessageID HTTP_IDLE_CONNECTION_TIMEOUT_OCCURRED;
extern const isc::log::MessageID HTTP_PREMATURE_CONNECTION_TIMEOUT_OCCURRED;
extern const isc::log::MessageID HTTP_REQUEST_RECEIVE_START;
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_RECEIVED;
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_RECEIVED_DETAILS;
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_SEND;
extern const isc::log::MessageID HTTP_SERVER_RESPONSE_SEND_DETAILS;

} // namespace http
} // namespace isc

#endif // HTTP_MESSAGES_H
