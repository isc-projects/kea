// File created from ../../../src/bin/agent/ca_messages.mes on Fri Oct 20 2017 00:28

#ifndef CA_MESSAGES_H
#define CA_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace agent {

extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARDED;
extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARD_BEGIN;
extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARD_FAILED;
extern const isc::log::MessageID CTRL_AGENT_CONFIG_CHECK_FAIL;
extern const isc::log::MessageID CTRL_AGENT_CONFIG_FAIL;
extern const isc::log::MessageID CTRL_AGENT_FAILED;
extern const isc::log::MessageID CTRL_AGENT_HTTP_SERVICE_STARTED;
extern const isc::log::MessageID CTRL_AGENT_RUN_EXIT;
extern const isc::log::MessageID CTRL_AGENT_STARTED;

} // namespace agent
} // namespace isc

#endif // CA_MESSAGES_H
