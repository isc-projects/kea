// File created from ../../../../src/lib/log/tests/log_test_messages.mes on Fri Feb 08 2019 20:15

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID LOG_LOCK_TEST_MESSAGE = "LOG_LOCK_TEST_MESSAGE";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "LOG_LOCK_TEST_MESSAGE", "this is a test message.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

