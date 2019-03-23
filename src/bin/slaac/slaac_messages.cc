// File created from ../../../src/bin/slaac/slaac_messages.mes on Sat Mar 23 2019 15:48

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace slaac {

extern const isc::log::MessageID SLAAC_CONFIG_CHECK_FAIL = "SLAAC_CONFIG_CHECK_FAIL";
extern const isc::log::MessageID SLAAC_CONFIG_FAIL = "SLAAC_CONFIG_FAIL";
extern const isc::log::MessageID SLAAC_FAILED = "SLAAC_FAILED";
extern const isc::log::MessageID SLAAC_START = "SLAAC_START";

} // namespace slaac
} // namespace isc

namespace {

const char* values[] = {
    "SLAAC_CONFIG_CHECK_FAIL", "Slaac configuration check failed: %1",
    "SLAAC_CONFIG_FAIL", "Slaac configuration failed: %1",
    "SLAAC_FAILED", "application experienced a fatal error: %1",
    "SLAAC_START", "Some message param %1 (details %2)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

