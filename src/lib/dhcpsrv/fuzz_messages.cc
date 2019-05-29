// File created from ../../../src/lib/dhcpsrv/fuzz_messages.mes on Sun Jun 16 2019 18:13

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID FUZZ_DATA_READ = "FUZZ_DATA_READ";
extern const isc::log::MessageID FUZZ_INIT_COMPLETE = "FUZZ_INIT_COMPLETE";
extern const isc::log::MessageID FUZZ_INIT_FAIL = "FUZZ_INIT_FAIL";
extern const isc::log::MessageID FUZZ_INTERFACE = "FUZZ_INTERFACE";
extern const isc::log::MessageID FUZZ_LOOP_EXIT = "FUZZ_LOOP_EXIT";
extern const isc::log::MessageID FUZZ_LOOP_MAX = "FUZZ_LOOP_MAX";
extern const isc::log::MessageID FUZZ_PACKET_PROCESSED_CALLED = "FUZZ_PACKET_PROCESSED_CALLED";
extern const isc::log::MessageID FUZZ_READ_FAIL = "FUZZ_READ_FAIL";
extern const isc::log::MessageID FUZZ_SEND = "FUZZ_SEND";
extern const isc::log::MessageID FUZZ_SEND_ERROR = "FUZZ_SEND_ERROR";
extern const isc::log::MessageID FUZZ_SET = "FUZZ_SET";
extern const isc::log::MessageID FUZZ_SETTING = "FUZZ_SETTING";
extern const isc::log::MessageID FUZZ_SHORT_SEND = "FUZZ_SHORT_SEND";
extern const isc::log::MessageID FUZZ_SHUTDOWN_INITIATED = "FUZZ_SHUTDOWN_INITIATED";
extern const isc::log::MessageID FUZZ_SOCKET_CREATE_FAIL = "FUZZ_SOCKET_CREATE_FAIL";
extern const isc::log::MessageID FUZZ_THREAD_NOT_TERMINATED = "FUZZ_THREAD_NOT_TERMINATED";
extern const isc::log::MessageID FUZZ_THREAD_TERMINATED = "FUZZ_THREAD_TERMINATED";
extern const isc::log::MessageID FUZZ_THREAD_WAIT = "FUZZ_THREAD_WAIT";
extern const isc::log::MessageID FUZZ_WAITED = "FUZZ_WAITED";
extern const isc::log::MessageID FUZZ_WAITING = "FUZZ_WAITING";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "FUZZ_DATA_READ", "read %1 byte(s) from AFL via stdin",
    "FUZZ_INIT_COMPLETE", "fuzz initialization complete: interface %1, address %2, port %3, max loops %4",
    "FUZZ_INIT_FAIL", "fuzz initialization failure, reason: %1",
    "FUZZ_INTERFACE", "fuzzing will use interface %1 (address %2, port %3)",
    "FUZZ_LOOP_EXIT", "fuzzing loop has exited, shutting down Kea",
    "FUZZ_LOOP_MAX", "fuzzing loop will run %1 time(s) before exiting",
    "FUZZ_PACKET_PROCESSED_CALLED", "packetProcessed has been called",
    "FUZZ_READ_FAIL", "error reading input from fuzzer: %1",
    "FUZZ_SEND", "sent %1 byte(s) to the socket connected to the Kea interface",
    "FUZZ_SEND_ERROR", "failed to send data to Kea input socket: %1",
    "FUZZ_SET", "successfully set %1 condition variable",
    "FUZZ_SETTING", "setting %1 condition variable",
    "FUZZ_SHORT_SEND", "expected to send %d bytes to Kea input socket but only sent %2",
    "FUZZ_SHUTDOWN_INITIATED", "shutdown initated, shutdown flag is set",
    "FUZZ_SOCKET_CREATE_FAIL", "failed to crease socket for use by fuzzing thread: %1",
    "FUZZ_THREAD_NOT_TERMINATED", "fuzzing thread has not terminated",
    "FUZZ_THREAD_TERMINATED", "fuzzing thread has terminated",
    "FUZZ_THREAD_WAIT", "waiting for fuzzing thread to terminate",
    "FUZZ_WAITED", "successfully waited for for %1 condition variable to be set",
    "FUZZ_WAITING", "waiting for %1 condition variable to be set",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

