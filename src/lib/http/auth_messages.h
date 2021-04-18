// File created from ../../../src/lib/http/auth_messages.mes

#ifndef AUTH_MESSAGES_H
#define AUTH_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace http {

extern const isc::log::MessageID HTTP_CLIENT_REQUEST_AUTHORIZED;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_NOT_AUTHORIZED;
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_NO_AUTH_HEADER;

} // namespace http
} // namespace isc

#endif // AUTH_MESSAGES_H
