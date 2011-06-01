// File created from impldef.mes on Wed Jun  1 10:32:57 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID LOGIMPL_ABOVEDBGMAX = "LOGIMPL_ABOVEDBGMAX";
extern const isc::log::MessageID LOGIMPL_BADDEBUG = "LOGIMPL_BADDEBUG";
extern const isc::log::MessageID LOGIMPL_BELOWDBGMIN = "LOGIMPL_BELOWDBGMIN";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "LOGIMPL_ABOVEDBGMAX", "debug level of %1 is too high and will be set to the maximum of %2",
    "LOGIMPL_BADDEBUG", "debug string is '%1': must be of the form DEBUGn",
    "LOGIMPL_BELOWDBGMIN", "debug level of %1 is too low and will be set to the minimum of %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

