// File created from ../../../src/bin/client/client_messages.mes on Tue Nov 19 2019 03:42

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace client {

extern const isc::log::MessageID CLIENT6_UNEXPECTED_EVENT = "CLIENT6_UNEXPECTED_EVENT";

} // namespace client
} // namespace isc

namespace {

const char* values[] = {
    "CLIENT6_UNEXPECTED_EVENT", "state %1 entered with unexpected event %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

