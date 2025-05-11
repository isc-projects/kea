// File created from src/hooks/dhcp/ddns_tuning/ddns_tuning_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID DDNS_TUNING4_CALCULATED_HOSTNAME = "DDNS_TUNING4_CALCULATED_HOSTNAME";
extern const isc::log::MessageID DDNS_TUNING4_PROCESS_ERROR = "DDNS_TUNING4_PROCESS_ERROR";
extern const isc::log::MessageID DDNS_TUNING4_SKIPPING_DDNS = "DDNS_TUNING4_SKIPPING_DDNS";
extern const isc::log::MessageID DDNS_TUNING6_CALCULATED_HOSTNAME = "DDNS_TUNING6_CALCULATED_HOSTNAME";
extern const isc::log::MessageID DDNS_TUNING6_PROCESS_ERROR = "DDNS_TUNING6_PROCESS_ERROR";
extern const isc::log::MessageID DDNS_TUNING6_SKIPPING_DDNS = "DDNS_TUNING6_SKIPPING_DDNS";
extern const isc::log::MessageID DDNS_TUNING_GLOBAL_EXPR_SET = "DDNS_TUNING_GLOBAL_EXPR_SET";
extern const isc::log::MessageID DDNS_TUNING_LOAD_ERROR = "DDNS_TUNING_LOAD_ERROR";
extern const isc::log::MessageID DDNS_TUNING_LOAD_OK = "DDNS_TUNING_LOAD_OK";
extern const isc::log::MessageID DDNS_TUNING_SUBNET_EXPRESSION_PARSE = "DDNS_TUNING_SUBNET_EXPRESSION_PARSE";
extern const isc::log::MessageID DDNS_TUNING_SUBNET_EXPRESSION_PARSE_ERROR = "DDNS_TUNING_SUBNET_EXPRESSION_PARSE_ERROR";
extern const isc::log::MessageID DDNS_TUNING_SUBNET_EXPR_CACHED = "DDNS_TUNING_SUBNET_EXPR_CACHED";
extern const isc::log::MessageID DDNS_TUNING_UNLOAD = "DDNS_TUNING_UNLOAD";

namespace {

const char* values[] = {
    "DDNS_TUNING4_CALCULATED_HOSTNAME", "Replacing host name: %1, with calculated host name: %2, for query: %3",
    "DDNS_TUNING4_PROCESS_ERROR", "An error occurred processing query %1: %2",
    "DDNS_TUNING4_SKIPPING_DDNS", "Client is a member matches SKIP_DDNS class, skipping DDNS updates, query: %1",
    "DDNS_TUNING6_CALCULATED_HOSTNAME", "Replacing host name: %1, with calculated host name: %2, for query: %3",
    "DDNS_TUNING6_PROCESS_ERROR", "An error occurred processing query %1: %2",
    "DDNS_TUNING6_SKIPPING_DDNS", "Client is a member matches SKIP_DDNS class, skipping DDNS updates, query: %1",
    "DDNS_TUNING_GLOBAL_EXPR_SET", "Global hostname expression set to: %1",
    "DDNS_TUNING_LOAD_ERROR", "loading DDNS Tuning hooks library failed: %1",
    "DDNS_TUNING_LOAD_OK", "DDNS Tuning hooks library loaded successfully.",
    "DDNS_TUNING_SUBNET_EXPRESSION_PARSE", "Parsing subnet expression (%1) for for subnet %2",
    "DDNS_TUNING_SUBNET_EXPRESSION_PARSE_ERROR", "An error occurred while parsing the hostname expression for subnet %1, %2",
    "DDNS_TUNING_SUBNET_EXPR_CACHED", "Using subnet expression stored in a cache for subnet %1",
    "DDNS_TUNING_UNLOAD", "DDNS Tuning hooks library has been unloaded",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

