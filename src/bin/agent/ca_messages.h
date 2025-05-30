// File created from ../src/bin/agent/ca_messages.mes

#ifndef CA_MESSAGES_H
#define CA_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace agent {

extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARDED;
extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARD_BEGIN;
extern const isc::log::MessageID CTRL_AGENT_COMMAND_FORWARD_FAILED;
extern const isc::log::MessageID CTRL_AGENT_COMMAND_RECEIVED;
extern const isc::log::MessageID CTRL_AGENT_CONFIG_CHECK_FAIL;
extern const isc::log::MessageID CTRL_AGENT_CONFIG_FAIL;
extern const isc::log::MessageID CTRL_AGENT_CONFIG_SYNTAX_WARNING;
extern const isc::log::MessageID CTRL_AGENT_FAILED;
extern const isc::log::MessageID CTRL_AGENT_HTTPS_SERVICE_REUSE_FAILED;
extern const isc::log::MessageID CTRL_AGENT_HTTPS_SERVICE_STARTED;
extern const isc::log::MessageID CTRL_AGENT_HTTPS_SERVICE_UPDATED;
extern const isc::log::MessageID CTRL_AGENT_HTTP_SERVICE_REUSE_FAILED;
extern const isc::log::MessageID CTRL_AGENT_HTTP_SERVICE_STARTED;
extern const isc::log::MessageID CTRL_AGENT_HTTP_SERVICE_UPDATED;
extern const isc::log::MessageID CTRL_AGENT_IS_DEPRECATED;
extern const isc::log::MessageID CTRL_AGENT_RUN_EXIT;
extern const isc::log::MessageID CTRL_AGENT_SECURITY_CHECKS_DISABLED;
extern const isc::log::MessageID CTRL_AGENT_STARTED;

} // namespace agent
} // namespace isc

#endif // CA_MESSAGES_H
