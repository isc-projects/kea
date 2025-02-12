// File created from ../../../../src/hooks/dhcp/host_cache/host_cache_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace host_cache {

extern const isc::log::MessageID HOST_CACHE_ADD = "HOST_CACHE_ADD";
extern const isc::log::MessageID HOST_CACHE_ADD_DUPLICATE = "HOST_CACHE_ADD_DUPLICATE";
extern const isc::log::MessageID HOST_CACHE_COMMAND_CLEAR = "HOST_CACHE_COMMAND_CLEAR";
extern const isc::log::MessageID HOST_CACHE_COMMAND_CLEAR_FAILED = "HOST_CACHE_COMMAND_CLEAR_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_FLUSH = "HOST_CACHE_COMMAND_FLUSH";
extern const isc::log::MessageID HOST_CACHE_COMMAND_FLUSH_FAILED = "HOST_CACHE_COMMAND_FLUSH_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET = "HOST_CACHE_COMMAND_GET";
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET_BY_ID = "HOST_CACHE_COMMAND_GET_BY_ID";
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET_BY_ID_FAILED = "HOST_CACHE_COMMAND_GET_BY_ID_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET_FAILED = "HOST_CACHE_COMMAND_GET_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_INSERT = "HOST_CACHE_COMMAND_INSERT";
extern const isc::log::MessageID HOST_CACHE_COMMAND_INSERT_FAILED = "HOST_CACHE_COMMAND_INSERT_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_LOAD = "HOST_CACHE_COMMAND_LOAD";
extern const isc::log::MessageID HOST_CACHE_COMMAND_LOAD_FAILED = "HOST_CACHE_COMMAND_LOAD_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_REMOVE = "HOST_CACHE_COMMAND_REMOVE";
extern const isc::log::MessageID HOST_CACHE_COMMAND_REMOVE_FAILED = "HOST_CACHE_COMMAND_REMOVE_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_SIZE = "HOST_CACHE_COMMAND_SIZE";
extern const isc::log::MessageID HOST_CACHE_COMMAND_SIZE_FAILED = "HOST_CACHE_COMMAND_SIZE_FAILED";
extern const isc::log::MessageID HOST_CACHE_COMMAND_WRITE = "HOST_CACHE_COMMAND_WRITE";
extern const isc::log::MessageID HOST_CACHE_COMMAND_WRITE_FAILED = "HOST_CACHE_COMMAND_WRITE_FAILED";
extern const isc::log::MessageID HOST_CACHE_CONFIGURATION_FAILED = "HOST_CACHE_CONFIGURATION_FAILED";
extern const isc::log::MessageID HOST_CACHE_DEINIT_OK = "HOST_CACHE_DEINIT_OK";
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_ADDRESS4 = "HOST_CACHE_DEL_SUBNET_ID_ADDRESS4";
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_ADDRESS6 = "HOST_CACHE_DEL_SUBNET_ID_ADDRESS6";
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER4 = "HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER4";
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER6 = "HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER6";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_PREFIX = "HOST_CACHE_GET_ONE_PREFIX";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_PREFIX_HOST = "HOST_CACHE_GET_ONE_PREFIX_HOST";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4 = "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4_HOST = "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4_HOST";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6 = "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6_HOST = "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6_HOST";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER = "HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER";
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER_HOST = "HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER_HOST";
extern const isc::log::MessageID HOST_CACHE_INIT_OK = "HOST_CACHE_INIT_OK";

} // namespace host_cache
} // namespace isc

namespace {

const char* values[] = {
    "HOST_CACHE_ADD", "add host: %1",
    "HOST_CACHE_ADD_DUPLICATE", "duplicate host: %1",
    "HOST_CACHE_COMMAND_CLEAR", "cache-clear command successful",
    "HOST_CACHE_COMMAND_CLEAR_FAILED", "cache-clear command failed (reason: %1)",
    "HOST_CACHE_COMMAND_FLUSH", "cache-flush command successful",
    "HOST_CACHE_COMMAND_FLUSH_FAILED", "cache-flush command failed (parameters: %1, reason: %2)",
    "HOST_CACHE_COMMAND_GET", "cache-get command successful (returned: %1)",
    "HOST_CACHE_COMMAND_GET_BY_ID", "cache-get-by-id command successful (returned: %1)",
    "HOST_CACHE_COMMAND_GET_BY_ID_FAILED", "cache-get-by-id command failed (reason: %1)",
    "HOST_CACHE_COMMAND_GET_FAILED", "cache-get command failed (reason: %1)",
    "HOST_CACHE_COMMAND_INSERT", "cache-insert command successful (inserted: %1, overwritten: %2)",
    "HOST_CACHE_COMMAND_INSERT_FAILED", "cache-insert command failed (parameters: %1, reason: %2)",
    "HOST_CACHE_COMMAND_LOAD", "cache-load command successful (loaded: %1, overwritten: %2)",
    "HOST_CACHE_COMMAND_LOAD_FAILED", "cache-load command failed (parameters: %1, reason: %2)",
    "HOST_CACHE_COMMAND_REMOVE", "cache-remove command successful (parameters: %1)",
    "HOST_CACHE_COMMAND_REMOVE_FAILED", "cache-remove command failed (parameters: %1, reason: %2)",
    "HOST_CACHE_COMMAND_SIZE", "cache-clear command successful: %1",
    "HOST_CACHE_COMMAND_SIZE_FAILED", "cache-size command failed (reason: %1)",
    "HOST_CACHE_COMMAND_WRITE", "cache-write command successful (dumped: %1)",
    "HOST_CACHE_COMMAND_WRITE_FAILED", "cache-write command failed (parameters: %1, reason: %2)",
    "HOST_CACHE_CONFIGURATION_FAILED", "failed to configure Host Cache hooks library: %1",
    "HOST_CACHE_DEINIT_OK", "unloading Host Cache hooks library successful",
    "HOST_CACHE_DEL_SUBNET_ID_ADDRESS4", "using subnet id %1 and address %2, delete host: %3",
    "HOST_CACHE_DEL_SUBNET_ID_ADDRESS6", "using subnet id %1 and address %2, delete host: %3",
    "HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER4", "using subnet id %1 and identifier %2, delete host: %3",
    "HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER6", "using subnet id %1 and identifier %2, delete host: %3",
    "HOST_CACHE_GET_ONE_PREFIX", "get one host with reservation for prefix %1/%2",
    "HOST_CACHE_GET_ONE_PREFIX_HOST", "using prefix %1/%2, found host: %3",
    "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4", "get one host with reservation for subnet id %1 and IPv4 address %2",
    "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4_HOST", "using subnet id %1 and address %2, found host: %3",
    "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6", "get one host with reservation for subnet id %1 and including IPv6 address %2",
    "HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6_HOST", "using subnet id %1 and address %2, found host: %3",
    "HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER", "get one host with %1 reservation for subnet id %2, identified by %3",
    "HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER_HOST", "using subnet id %1 and identifier %2, found host: %3",
    "HOST_CACHE_INIT_OK", "loading Host Cache hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

