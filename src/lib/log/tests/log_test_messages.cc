// File created from log_test_messages.mes on Thu May 24 12:52:20 2012

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

