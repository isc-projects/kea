// File created from nsasdef.msg on Thu Apr 28 09:42:02 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace nsas {

extern const isc::log::MessageID NSAS_LOOKUPCANCEL = "LOOKUPCANCEL";
extern const isc::log::MessageID NSAS_LOOKUPZONE = "LOOKUPZONE";

} // namespace nsas
} // namespace isc

namespace {

const char* values[] = {
    "LOOKUPCANCEL", "lookup for zone %s has been cancelled",
    "LOOKUPZONE", "searching NSAS for nameservers for zone %s",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

