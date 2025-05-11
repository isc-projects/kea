// File created from src/hooks/dhcp/host_cmds/host_cmds_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID HOST_CMDS_DEINIT_OK = "HOST_CMDS_DEINIT_OK";
extern const isc::log::MessageID HOST_CMDS_INIT_FAILED = "HOST_CMDS_INIT_FAILED";
extern const isc::log::MessageID HOST_CMDS_INIT_OK = "HOST_CMDS_INIT_OK";
extern const isc::log::MessageID HOST_CMDS_RESERV_ADD = "HOST_CMDS_RESERV_ADD";
extern const isc::log::MessageID HOST_CMDS_RESERV_ADD_FAILED = "HOST_CMDS_RESERV_ADD_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_ADD_SUCCESS = "HOST_CMDS_RESERV_ADD_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_DEL = "HOST_CMDS_RESERV_DEL";
extern const isc::log::MessageID HOST_CMDS_RESERV_DEL_FAILED = "HOST_CMDS_RESERV_DEL_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_DEL_SUCCESS = "HOST_CMDS_RESERV_DEL_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET = "HOST_CMDS_RESERV_GET";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_ALL = "HOST_CMDS_RESERV_GET_ALL";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_ALL_FAILED = "HOST_CMDS_RESERV_GET_ALL_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_ALL_SUCCESS = "HOST_CMDS_RESERV_GET_ALL_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_ADDRESS = "HOST_CMDS_RESERV_GET_BY_ADDRESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_ADDRESS_FAILED = "HOST_CMDS_RESERV_GET_BY_ADDRESS_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_ADDRESS_SUCCESS = "HOST_CMDS_RESERV_GET_BY_ADDRESS_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_HOSTNAME = "HOST_CMDS_RESERV_GET_BY_HOSTNAME";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_HOSTNAME_FAILED = "HOST_CMDS_RESERV_GET_BY_HOSTNAME_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_HOSTNAME_SUCCESS = "HOST_CMDS_RESERV_GET_BY_HOSTNAME_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_ID = "HOST_CMDS_RESERV_GET_BY_ID";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_ID_FAILED = "HOST_CMDS_RESERV_GET_BY_ID_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_BY_ID_SUCCESS = "HOST_CMDS_RESERV_GET_BY_ID_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_FAILED = "HOST_CMDS_RESERV_GET_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_PAGE = "HOST_CMDS_RESERV_GET_PAGE";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_PAGE_FAILED = "HOST_CMDS_RESERV_GET_PAGE_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_PAGE_SUCCESS = "HOST_CMDS_RESERV_GET_PAGE_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_GET_SUCCESS = "HOST_CMDS_RESERV_GET_SUCCESS";
extern const isc::log::MessageID HOST_CMDS_RESERV_UPDATE = "HOST_CMDS_RESERV_UPDATE";
extern const isc::log::MessageID HOST_CMDS_RESERV_UPDATE_FAILED = "HOST_CMDS_RESERV_UPDATE_FAILED";
extern const isc::log::MessageID HOST_CMDS_RESERV_UPDATE_SUCCESS = "HOST_CMDS_RESERV_UPDATE_SUCCESS";

namespace {

const char* values[] = {
    "HOST_CMDS_DEINIT_OK", "unloading Host Commands hooks library successful",
    "HOST_CMDS_INIT_FAILED", "loading Host Commands hooks library failed: %1",
    "HOST_CMDS_INIT_OK", "loading Host Commands hooks library successful",
    "HOST_CMDS_RESERV_ADD", "reservation-add command called (parameters: %1)",
    "HOST_CMDS_RESERV_ADD_FAILED", "reservation-add command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_ADD_SUCCESS", "reservation-add command success (parameters: %1)",
    "HOST_CMDS_RESERV_DEL", "reservation-del command called (parameters: %1)",
    "HOST_CMDS_RESERV_DEL_FAILED", "reservation-del command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_DEL_SUCCESS", "reservation-del command success (parameters: %1)",
    "HOST_CMDS_RESERV_GET", "reservation-get command called (parameters: %1)",
    "HOST_CMDS_RESERV_GET_ALL", "reservation-get-all command called (parameters: %1)",
    "HOST_CMDS_RESERV_GET_ALL_FAILED", "reservation-get-all command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_GET_ALL_SUCCESS", "reservation-get-all command success (parameters: %1)",
    "HOST_CMDS_RESERV_GET_BY_ADDRESS", "reservation-get-by-address command called (parameters: %1)",
    "HOST_CMDS_RESERV_GET_BY_ADDRESS_FAILED", "reservation-get-by-address command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_GET_BY_ADDRESS_SUCCESS", "reservation-get-by-address command success (parameters: %1)",
    "HOST_CMDS_RESERV_GET_BY_HOSTNAME", "reservation-get-by-hostname command called (parameters: %1)",
    "HOST_CMDS_RESERV_GET_BY_HOSTNAME_FAILED", "reservation-get-by-hostname command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_GET_BY_HOSTNAME_SUCCESS", "reservation-get-by-hostname command success (parameters: %1)",
    "HOST_CMDS_RESERV_GET_BY_ID", "reservation-get-by-id command called (parameters: %1)",
    "HOST_CMDS_RESERV_GET_BY_ID_FAILED", "reservation-get-by-id command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_GET_BY_ID_SUCCESS", "reservation-get-by-id command success (parameters: %1)",
    "HOST_CMDS_RESERV_GET_FAILED", "reservation-get command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_GET_PAGE", "reservation-get-page command called (parameters: %1)",
    "HOST_CMDS_RESERV_GET_PAGE_FAILED", "reservation-get-page command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_GET_PAGE_SUCCESS", "reservation-get-page command success (parameters: %1)",
    "HOST_CMDS_RESERV_GET_SUCCESS", "reservation-get command success (parameters: %1)",
    "HOST_CMDS_RESERV_UPDATE", "reservation-update command called (parameters: %1)",
    "HOST_CMDS_RESERV_UPDATE_FAILED", "reservation-update command failed (parameters: %1, reason: %2)",
    "HOST_CMDS_RESERV_UPDATE_SUCCESS", "reservation-update command success (parameters: %1)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

