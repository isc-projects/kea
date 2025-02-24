// File created from src/hooks/dhcp/forensic_log/legal_log_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID LEGAL_LOG_COMMAND_NO_LEGAL_STORE = "LEGAL_LOG_COMMAND_NO_LEGAL_STORE";
extern const isc::log::MessageID LEGAL_LOG_COMMAND_WRITE_ERROR = "LEGAL_LOG_COMMAND_WRITE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED = "LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED";
extern const isc::log::MessageID LEGAL_LOG_LEASE4_NO_LEGAL_STORE = "LEGAL_LOG_LEASE4_NO_LEGAL_STORE";
extern const isc::log::MessageID LEGAL_LOG_LEASE4_WRITE_ERROR = "LEGAL_LOG_LEASE4_WRITE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_LEASE6_NO_LEGAL_STORE = "LEGAL_LOG_LEASE6_NO_LEGAL_STORE";
extern const isc::log::MessageID LEGAL_LOG_LEASE6_WRITE_ERROR = "LEGAL_LOG_LEASE6_WRITE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_LOAD_ERROR = "LEGAL_LOG_LOAD_ERROR";
extern const isc::log::MessageID LEGAL_LOG_STORE_CLOSED = "LEGAL_LOG_STORE_CLOSED";
extern const isc::log::MessageID LEGAL_LOG_STORE_CLOSE_ERROR = "LEGAL_LOG_STORE_CLOSE_ERROR";
extern const isc::log::MessageID LEGAL_LOG_STORE_OPEN = "LEGAL_LOG_STORE_OPEN";
extern const isc::log::MessageID LEGAL_LOG_STORE_OPENED = "LEGAL_LOG_STORE_OPENED";
extern const isc::log::MessageID LEGAL_LOG_UNLOAD_ERROR = "LEGAL_LOG_UNLOAD_ERROR";

namespace {

const char* values[] = {
    "LEGAL_LOG_COMMAND_NO_LEGAL_STORE", "LegalStore instance is null",
    "LEGAL_LOG_COMMAND_WRITE_ERROR", "Could not write command entry to the legal store: %1",
    "LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED", "Failed to connect to database: %1 with error: %2",
    "LEGAL_LOG_LEASE4_NO_LEGAL_STORE", "LegalStore instance is null",
    "LEGAL_LOG_LEASE4_WRITE_ERROR", "Could not write to the legal store: %1",
    "LEGAL_LOG_LEASE6_NO_LEGAL_STORE", "LegalStore instance is null",
    "LEGAL_LOG_LEASE6_WRITE_ERROR", "Could not write to the legal store: %1",
    "LEGAL_LOG_LOAD_ERROR", "LEGAL LOGGING DISABLED! An error occurred loading the library: %1",
    "LEGAL_LOG_STORE_CLOSED", "Legal store closed: %1",
    "LEGAL_LOG_STORE_CLOSE_ERROR", "An error occurred closing the store: %1, error: %2",
    "LEGAL_LOG_STORE_OPEN", "opening Legal Log file: %1",
    "LEGAL_LOG_STORE_OPENED", "Legal store opened: %1",
    "LEGAL_LOG_UNLOAD_ERROR", "An error occurred unloading the library: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

