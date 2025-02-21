// File created from src/hooks/dhcp/flex_id/flex_id_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID FLEX_ID_EXPRESSION_EMPTY = "FLEX_ID_EXPRESSION_EMPTY";
extern const isc::log::MessageID FLEX_ID_EXPRESSION_EVALUATED = "FLEX_ID_EXPRESSION_EVALUATED";
extern const isc::log::MessageID FLEX_ID_EXPRESSION_EVALUATED_NP = "FLEX_ID_EXPRESSION_EVALUATED_NP";
extern const isc::log::MessageID FLEX_ID_EXPRESSION_HEX = "FLEX_ID_EXPRESSION_HEX";
extern const isc::log::MessageID FLEX_ID_EXPRESSION_INVALID_JSON_TYPE = "FLEX_ID_EXPRESSION_INVALID_JSON_TYPE";
extern const isc::log::MessageID FLEX_ID_EXPRESSION_NOT_DEFINED = "FLEX_ID_EXPRESSION_NOT_DEFINED";
extern const isc::log::MessageID FLEX_ID_EXPRESSION_PARSE_FAILED = "FLEX_ID_EXPRESSION_PARSE_FAILED";
extern const isc::log::MessageID FLEX_ID_IGNORE_IAID_APPLIED_ON_NA = "FLEX_ID_IGNORE_IAID_APPLIED_ON_NA";
extern const isc::log::MessageID FLEX_ID_IGNORE_IAID_APPLIED_ON_PD = "FLEX_ID_IGNORE_IAID_APPLIED_ON_PD";
extern const isc::log::MessageID FLEX_ID_IGNORE_IAID_ENABLED = "FLEX_ID_IGNORE_IAID_ENABLED";
extern const isc::log::MessageID FLEX_ID_IGNORE_IAID_JSON_TYPE = "FLEX_ID_IGNORE_IAID_JSON_TYPE";
extern const isc::log::MessageID FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_NA = "FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_NA";
extern const isc::log::MessageID FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_PD = "FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_PD";
extern const isc::log::MessageID FLEX_ID_LOAD_ERROR = "FLEX_ID_LOAD_ERROR";
extern const isc::log::MessageID FLEX_ID_REPLACE_CLIENT_ID_JSON_TYPE = "FLEX_ID_REPLACE_CLIENT_ID_JSON_TYPE";
extern const isc::log::MessageID FLEX_ID_RESTORE_CLIENT_ID = "FLEX_ID_RESTORE_CLIENT_ID";
extern const isc::log::MessageID FLEX_ID_RESTORE_DUID = "FLEX_ID_RESTORE_DUID";
extern const isc::log::MessageID FLEX_ID_UNLOAD = "FLEX_ID_UNLOAD";
extern const isc::log::MessageID FLEX_ID_USED_AS_CLIENT_ID = "FLEX_ID_USED_AS_CLIENT_ID";
extern const isc::log::MessageID FLEX_ID_USED_AS_DUID = "FLEX_ID_USED_AS_DUID";

namespace {

const char* values[] = {
    "FLEX_ID_EXPRESSION_EMPTY", "Specified identifier-expression is empty",
    "FLEX_ID_EXPRESSION_EVALUATED", "Expression evaluated for packet to \"%1\" (size: %2)",
    "FLEX_ID_EXPRESSION_EVALUATED_NP", "Expression evaluated for packet to 0x%1 (size: %2)",
    "FLEX_ID_EXPRESSION_HEX", "evaluated expression in hexadecimal form \"%1\"",
    "FLEX_ID_EXPRESSION_INVALID_JSON_TYPE", "The identifier-expression is %1, but expected JSON string",
    "FLEX_ID_EXPRESSION_NOT_DEFINED", "Expression (identifier-expression) is not defined.",
    "FLEX_ID_EXPRESSION_PARSE_FAILED", "The identifier-expression is [%1], but fails to parse with error: %2",
    "FLEX_ID_IGNORE_IAID_APPLIED_ON_NA", "the ignore-iaid has changed IAID (%1) to 0 for the IA_NA option.",
    "FLEX_ID_IGNORE_IAID_APPLIED_ON_PD", "the ignore-iaid has changed IAID (%1) to 0 for the IA_PD option.",
    "FLEX_ID_IGNORE_IAID_ENABLED", "the ignore-iaid is set. It only has an effect on clients with at most one IA_NA and one IA_PD.",
    "FLEX_ID_IGNORE_IAID_JSON_TYPE", "the ignore-iaid is %1 but expected boolean value",
    "FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_NA", "the ignore-iaid was not applied on the packet because it contains more than one IA_NA.",
    "FLEX_ID_IGNORE_IAID_NOT_APPLIED_ON_PD", "the ignore-iaid was not applied on the packet because it contains more than one IA_PD.",
    "FLEX_ID_LOAD_ERROR", "An error occurred loading the library %1",
    "FLEX_ID_REPLACE_CLIENT_ID_JSON_TYPE", "the replace-client-id is %1 but expected boolean value",
    "FLEX_ID_RESTORE_CLIENT_ID", "restoring original client identifier '%1' in the response",
    "FLEX_ID_RESTORE_DUID", "restoring original DUID \"%1\" in the response",
    "FLEX_ID_UNLOAD", "Flex-id library has been unloaded.",
    "FLEX_ID_USED_AS_CLIENT_ID", "using flexible identifier \"%1\" as client identifier",
    "FLEX_ID_USED_AS_DUID", "using flexible identifier \"%1\" as DUID",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

