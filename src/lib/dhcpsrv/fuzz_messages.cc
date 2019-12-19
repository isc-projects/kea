// File created from ../../../src/lib/dhcpsrv/fuzz_messages.mes on Mon Jul 01 2019 12:28

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID FUZZ_DATA_READ = "FUZZ_DATA_READ";
extern const isc::log::MessageID FUZZ_INIT_COMPLETE = "FUZZ_INIT_COMPLETE";
extern const isc::log::MessageID FUZZ_INIT_FAIL = "FUZZ_INIT_FAIL";
extern const isc::log::MessageID FUZZ_READ_FAIL = "FUZZ_READ_FAIL";
extern const isc::log::MessageID FUZZ_SEND = "FUZZ_SEND";
extern const isc::log::MessageID FUZZ_SEND_ERROR = "FUZZ_SEND_ERROR";
extern const isc::log::MessageID FUZZ_SHORT_SEND = "FUZZ_SHORT_SEND";
extern const isc::log::MessageID FUZZ_SOCKET_CREATE_FAIL = "FUZZ_SOCKET_CREATE_FAIL";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "FUZZ_DATA_READ", "read %1 byte(s) from AFL via stdin",
    "FUZZ_INIT_COMPLETE", "fuzz initialization complete: interface %1, address %2, port %3, max loops %4",
    "FUZZ_INIT_FAIL", "fuzz initialization failure, reason: %1",
    "FUZZ_READ_FAIL", "error reading input from fuzzer: %1",
    "FUZZ_SEND", "sent %1 byte(s) to the socket connected to the Kea interface",
    "FUZZ_SEND_ERROR", "failed to send data to Kea input socket: %1",
    "FUZZ_SHORT_SEND", "expected to send %d bytes to Kea input socket but only sent %2",
    "FUZZ_SOCKET_CREATE_FAIL", "failed to crease socket for use by fuzzing thread: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

