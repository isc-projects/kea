// File created from src/hooks/dhcp/host_cache/host_cache_messages.mes

#ifndef HOST_CACHE_MESSAGES_H
#define HOST_CACHE_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace host_cache {

extern const isc::log::MessageID HOST_CACHE_ADD;
extern const isc::log::MessageID HOST_CACHE_ADD_DUPLICATE;
extern const isc::log::MessageID HOST_CACHE_COMMAND_CLEAR;
extern const isc::log::MessageID HOST_CACHE_COMMAND_CLEAR_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_FLUSH;
extern const isc::log::MessageID HOST_CACHE_COMMAND_FLUSH_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET;
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET_BY_ID;
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET_BY_ID_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_GET_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_INSERT;
extern const isc::log::MessageID HOST_CACHE_COMMAND_INSERT_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_LOAD;
extern const isc::log::MessageID HOST_CACHE_COMMAND_LOAD_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_REMOVE;
extern const isc::log::MessageID HOST_CACHE_COMMAND_REMOVE_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_SIZE;
extern const isc::log::MessageID HOST_CACHE_COMMAND_SIZE_FAILED;
extern const isc::log::MessageID HOST_CACHE_COMMAND_WRITE;
extern const isc::log::MessageID HOST_CACHE_COMMAND_WRITE_FAILED;
extern const isc::log::MessageID HOST_CACHE_CONFIGURATION_FAILED;
extern const isc::log::MessageID HOST_CACHE_DEINIT_OK;
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_ADDRESS4;
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER4;
extern const isc::log::MessageID HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER6;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_PREFIX;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_PREFIX_HOST;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4_HOST;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6_HOST;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER;
extern const isc::log::MessageID HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER_HOST;
extern const isc::log::MessageID HOST_CACHE_INIT_OK;
extern const isc::log::MessageID HOST_CACHE_PATH_SECURITY_WARNING;

} // namespace host_cache
} // namespace isc

#endif // HOST_CACHE_MESSAGES_H
