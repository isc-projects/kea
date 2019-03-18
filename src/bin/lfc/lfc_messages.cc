// File created from ../../../src/bin/lfc/lfc_messages.mes on Fri Feb 08 2019 20:33

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace lfc {

extern const isc::log::MessageID LFC_FAIL_PID_CREATE = "LFC_FAIL_PID_CREATE";
extern const isc::log::MessageID LFC_FAIL_PID_DEL = "LFC_FAIL_PID_DEL";
extern const isc::log::MessageID LFC_FAIL_PROCESS = "LFC_FAIL_PROCESS";
extern const isc::log::MessageID LFC_FAIL_ROTATE = "LFC_FAIL_ROTATE";
extern const isc::log::MessageID LFC_PROCESSING = "LFC_PROCESSING";
extern const isc::log::MessageID LFC_READ_STATS = "LFC_READ_STATS";
extern const isc::log::MessageID LFC_ROTATING = "LFC_ROTATING";
extern const isc::log::MessageID LFC_RUNNING = "LFC_RUNNING";
extern const isc::log::MessageID LFC_START = "LFC_START";
extern const isc::log::MessageID LFC_TERMINATE = "LFC_TERMINATE";
extern const isc::log::MessageID LFC_WRITE_STATS = "LFC_WRITE_STATS";

} // namespace lfc
} // namespace isc

namespace {

const char* values[] = {
    "LFC_FAIL_PID_CREATE", ": %1",
    "LFC_FAIL_PID_DEL", ": %1",
    "LFC_FAIL_PROCESS", ": %1",
    "LFC_FAIL_ROTATE", ": %1",
    "LFC_PROCESSING", "Previous file: %1, copy file: %2",
    "LFC_READ_STATS", "Leases: %1, attempts: %2, errors: %3.",
    "LFC_ROTATING", "LFC rotating files",
    "LFC_RUNNING", "LFC instance already running",
    "LFC_START", "Starting lease file cleanup",
    "LFC_TERMINATE", "LFC finished processing",
    "LFC_WRITE_STATS", "Leases: %1, attempts: %2, errors: %3.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

