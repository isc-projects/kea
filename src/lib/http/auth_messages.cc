// File created from ../../../src/lib/http/auth_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace http {

extern const isc::log::MessageID HTTP_CLIENT_REQUEST_AUTHORIZED = "HTTP_CLIENT_REQUEST_AUTHORIZED";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER = "HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_NOT_AUTHORIZED = "HTTP_CLIENT_REQUEST_NOT_AUTHORIZED";
extern const isc::log::MessageID HTTP_CLIENT_REQUEST_NO_AUTH_HEADER = "HTTP_CLIENT_REQUEST_NO_AUTH_HEADER";

} // namespace http
} // namespace isc

namespace {

const char* values[] = {
    "HTTP_CLIENT_REQUEST_AUTHORIZED", "received HTTP request authorized for '%1'",
    "HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER", "received HTTP request with malformed authentication header: %1",
    "HTTP_CLIENT_REQUEST_NOT_AUTHORIZED", "received HTTP request with not matching authentication header",
    "HTTP_CLIENT_REQUEST_NO_AUTH_HEADER", "received HTTP request without required authentication header",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

