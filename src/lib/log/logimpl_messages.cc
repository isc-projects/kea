// File created from logimpl_messages.mes on Sun Mar 15 2015 19:29

#define KEA_LOG_EXPORT

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const KEA_LOG_API isc::log::MessageID LOGIMPL_ABOVE_MAX_DEBUG = "LOGIMPL_ABOVE_MAX_DEBUG";
extern const KEA_LOG_API isc::log::MessageID LOGIMPL_BAD_DEBUG_STRING = "LOGIMPL_BAD_DEBUG_STRING";
extern const KEA_LOG_API isc::log::MessageID LOGIMPL_BELOW_MIN_DEBUG = "LOGIMPL_BELOW_MIN_DEBUG";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "LOGIMPL_ABOVE_MAX_DEBUG", "debug level of %1 is too high and will be set to the maximum of %2",
    "LOGIMPL_BAD_DEBUG_STRING", "debug string '%1' has invalid format",
    "LOGIMPL_BELOW_MIN_DEBUG", "debug level of %1 is too low and will be set to the minimum of %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

