// File created from ../../../src/lib/asiodns/asiodns_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace asiodns {

extern const isc::log::MessageID ASIODNS_FETCH_COMPLETED = "ASIODNS_FETCH_COMPLETED";
extern const isc::log::MessageID ASIODNS_FETCH_STOPPED = "ASIODNS_FETCH_STOPPED";
extern const isc::log::MessageID ASIODNS_OPEN_SOCKET = "ASIODNS_OPEN_SOCKET";
extern const isc::log::MessageID ASIODNS_READ_DATA = "ASIODNS_READ_DATA";
extern const isc::log::MessageID ASIODNS_READ_TIMEOUT = "ASIODNS_READ_TIMEOUT";
extern const isc::log::MessageID ASIODNS_SEND_DATA = "ASIODNS_SEND_DATA";
extern const isc::log::MessageID ASIODNS_UNKNOWN_ORIGIN = "ASIODNS_UNKNOWN_ORIGIN";
extern const isc::log::MessageID ASIODNS_UNKNOWN_RESULT = "ASIODNS_UNKNOWN_RESULT";

} // namespace asiodns
} // namespace isc

namespace {

const char* values[] = {
    "ASIODNS_FETCH_COMPLETED", "upstream fetch to %1(%2) has now completed",
    "ASIODNS_FETCH_STOPPED", "upstream fetch to %1(%2) has been stopped",
    "ASIODNS_OPEN_SOCKET", "error %1 opening %2 socket to %3(%4)",
    "ASIODNS_READ_DATA", "error %1 reading %2 data from %3(%4)",
    "ASIODNS_READ_TIMEOUT", "receive timeout while waiting for data from %1(%2)",
    "ASIODNS_SEND_DATA", "error %1 sending data using %2 to %3(%4)",
    "ASIODNS_UNKNOWN_ORIGIN", "unknown origin for ASIO error code %1 (protocol: %2, address %3)",
    "ASIODNS_UNKNOWN_RESULT", "unknown result (%1) when IOFetch::stop() was executed for I/O to %2(%3)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

