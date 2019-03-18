// File created from ../../../src/bin/agent/ca_messages.mes on Fri Feb 08 2019 20:33

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace agent {

extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARDED = "CTRL_AGENT_COMMAND_FORWARDED";
extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARD_BEGIN = "CTRL_AGENT_COMMAND_FORWARD_BEGIN";
extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARD_FAILED = "CTRL_AGENT_COMMAND_FORWARD_FAILED";
extern const isc::log::MessageID CTRL_AGENT_CONFIG_CHECK_FAIL = "CTRL_AGENT_CONFIG_CHECK_FAIL";
extern const isc::log::MessageID CTRL_AGENT_CONFIG_FAIL = "CTRL_AGENT_CONFIG_FAIL";
extern const isc::log::MessageID CTRL_AGENT_FAILED = "CTRL_AGENT_FAILED";
extern const isc::log::MessageID CTRL_AGENT_HTTP_SERVICE_STARTED = "CTRL_AGENT_HTTP_SERVICE_STARTED";
extern const isc::log::MessageID CTRL_AGENT_RUN_EXIT = "CTRL_AGENT_RUN_EXIT";
extern const isc::log::MessageID CTRL_AGENT_STARTED = "CTRL_AGENT_STARTED";

} // namespace agent
} // namespace isc

namespace {

const char* values[] = {
    "CTRL_AGENT_COMMAND_FORWARDED", "command %1 successfully forwarded to the service %2",
    "CTRL_AGENT_COMMAND_FORWARD_BEGIN", "begin forwarding command %1 to service %2",
    "CTRL_AGENT_COMMAND_FORWARD_FAILED", "failed forwarding command %1: %2",
    "CTRL_AGENT_CONFIG_CHECK_FAIL", "Control Agent configuration check failed: %1",
    "CTRL_AGENT_CONFIG_FAIL", "Control Agent configuration failed: %1",
    "CTRL_AGENT_FAILED", "application experienced a fatal error: %1",
    "CTRL_AGENT_HTTP_SERVICE_STARTED", "HTTP service bound to address %1:%2",
    "CTRL_AGENT_RUN_EXIT", "application is exiting the event loop",
    "CTRL_AGENT_STARTED", "Kea Control Agent version %1 started",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

