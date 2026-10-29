// File created from src/hooks/dhcp/rbac/rbac_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID RBAC_CONFIGURED_ACLS = "RBAC_CONFIGURED_ACLS";
extern const isc::log::MessageID RBAC_CONFIGURED_COMMANDS = "RBAC_CONFIGURED_COMMANDS";
extern const isc::log::MessageID RBAC_CONFIGURED_ROLES = "RBAC_CONFIGURED_ROLES";
extern const isc::log::MessageID RBAC_HTTP_AUTH_ERROR = "RBAC_HTTP_AUTH_ERROR";
extern const isc::log::MessageID RBAC_HTTP_AUTH_FAILED = "RBAC_HTTP_AUTH_FAILED";
extern const isc::log::MessageID RBAC_HTTP_AUTH_REJECT = "RBAC_HTTP_AUTH_REJECT";
extern const isc::log::MessageID RBAC_HTTP_AUTH_RESPONSE = "RBAC_HTTP_AUTH_RESPONSE";
extern const isc::log::MessageID RBAC_HTTP_RESPONSE_FAILED = "RBAC_HTTP_RESPONSE_FAILED";
extern const isc::log::MessageID RBAC_LOAD_FAILED = "RBAC_LOAD_FAILED";
extern const isc::log::MessageID RBAC_LOAD_OK = "RBAC_LOAD_OK";
extern const isc::log::MessageID RBAC_READ_API_FILES = "RBAC_READ_API_FILES";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_ACCEPT = "RBAC_TRACE_HTTP_AUTH_ACCEPT";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_BAD_BODY_TYPE = "RBAC_TRACE_HTTP_AUTH_BAD_BODY_TYPE";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_BAD_COMMAND_TYPE = "RBAC_TRACE_HTTP_AUTH_BAD_COMMAND_TYPE";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_COMMAND = "RBAC_TRACE_HTTP_AUTH_COMMAND";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_DISABLED = "RBAC_TRACE_HTTP_AUTH_DISABLED";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_EMPTY_BODY = "RBAC_TRACE_HTTP_AUTH_EMPTY_BODY";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_NO_COMMAND = "RBAC_TRACE_HTTP_AUTH_NO_COMMAND";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_NO_JSON = "RBAC_TRACE_HTTP_AUTH_NO_JSON";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_NO_REQUEST = "RBAC_TRACE_HTTP_AUTH_NO_REQUEST";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_NO_TLS_REJECT = "RBAC_TRACE_HTTP_AUTH_NO_TLS_REJECT";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_RESPONSE = "RBAC_TRACE_HTTP_AUTH_RESPONSE";
extern const isc::log::MessageID RBAC_TRACE_HTTP_AUTH_ROLE = "RBAC_TRACE_HTTP_AUTH_ROLE";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_BAD_BODY_TYPE = "RBAC_TRACE_HTTP_RESPONSE_BAD_BODY_TYPE";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_CONTEXT = "RBAC_TRACE_HTTP_RESPONSE_CONTEXT";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_DISABLED = "RBAC_TRACE_HTTP_RESPONSE_DISABLED";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY = "RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY_LIST = "RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY_LIST";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_MODIFIED = "RBAC_TRACE_HTTP_RESPONSE_MODIFIED";
extern const isc::log::MessageID RBAC_TRACE_HTTP_RESPONSE_NO_ARGUMENTS = "RBAC_TRACE_HTTP_RESPONSE_NO_ARGUMENTS";
extern const isc::log::MessageID RBAC_UNLOAD_OK = "RBAC_UNLOAD_OK";

namespace {

const char* values[] = {
    "RBAC_CONFIGURED_ACLS", "RBAC hooks library has configured %1 named ACLs.",
    "RBAC_CONFIGURED_COMMANDS", "RBAC hooks library has configured %1 extra commands.",
    "RBAC_CONFIGURED_ROLES", "hooks library has configured %1 roles.",
    "RBAC_HTTP_AUTH_ERROR", "Error in http_auth callout: %1.",
    "RBAC_HTTP_AUTH_FAILED", "RBAC processing in http_auth callout failed for unexpected condition: %1.",
    "RBAC_HTTP_AUTH_REJECT", "Role configuration '%1' for role '%2' has rejected command '%3'.",
    "RBAC_HTTP_AUTH_RESPONSE", "RBAC hooks library has returned response: %1.",
    "RBAC_HTTP_RESPONSE_FAILED", "RBAC processing in http_response callout failed for unexpected condition: %1.",
    "RBAC_LOAD_FAILED", "RBAC hooks library failed to load: %1.",
    "RBAC_LOAD_OK", "RBAC hooks library loaded successfully.",
    "RBAC_READ_API_FILES", "RBAC hooks library read API files from '%1' getting %2 commands, %3 access types and %4 hooks.",
    "RBAC_TRACE_HTTP_AUTH_ACCEPT", "Role configuration '%1' for role '%2' has accepted command '%3'.",
    "RBAC_TRACE_HTTP_AUTH_BAD_BODY_TYPE", "Bad body type in JSON request in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_BAD_COMMAND_TYPE", "Bad command type in JSON request in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_COMMAND", "Command '%1' in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_DISABLED", "RBAC hooks library is disabled in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_EMPTY_BODY", "Empty body in JSON request in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_NO_COMMAND", "No command entry in JSON request in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_NO_JSON", "No JSON request in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_NO_REQUEST", "No request in http_auth callout.",
    "RBAC_TRACE_HTTP_AUTH_NO_TLS_REJECT", "Non TLS request has been rejected.",
    "RBAC_TRACE_HTTP_AUTH_RESPONSE", "Response in http_auth callout: %1.",
    "RBAC_TRACE_HTTP_AUTH_ROLE", "Assigned role '%1' in http_auth callout.",
    "RBAC_TRACE_HTTP_RESPONSE_BAD_BODY_TYPE", "Bad body type in JSON response in http_response callout.",
    "RBAC_TRACE_HTTP_RESPONSE_CONTEXT", "Retrieved command '%1' and role config '%2' in http_response callout.",
    "RBAC_TRACE_HTTP_RESPONSE_DISABLED", "RBAC hooks library is disabled in http_response callout.",
    "RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY", "Empty body in JSON response in http_response callout.",
    "RBAC_TRACE_HTTP_RESPONSE_EMPTY_BODY_LIST", "Empty list in JSON response in http_response callout.",
    "RBAC_TRACE_HTTP_RESPONSE_MODIFIED", "The response has been modified by a response filter in http_response callout.",
    "RBAC_TRACE_HTTP_RESPONSE_NO_ARGUMENTS", "No request or response in http_response callout.",
    "RBAC_UNLOAD_OK", "RBAC hooks library unloaded successfully.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

