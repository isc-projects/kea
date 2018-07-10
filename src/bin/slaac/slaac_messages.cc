// File created from ../../../src/bin/slaac/slaac_messages.mes on Tue Jul 10 2018 21:11

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace slaac {

extern const isc::log::MessageID SLAAC_START = "SLAAC_START";

} // namespace slaac
} // namespace isc

namespace {

const char* values[] = {
    "SLAAC_START", "Some message param %1 (details %2)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

