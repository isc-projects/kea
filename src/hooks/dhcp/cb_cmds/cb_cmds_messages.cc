// File created from src/hooks/dhcp/cb_cmds/cb_cmds_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace cb {

extern const isc::log::MessageID CB_CMDS_CLASS4_DEL_HANDLER_FAILED = "CB_CMDS_CLASS4_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS4_GET_ALL_HANDLER_FAILED = "CB_CMDS_CLASS4_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS4_GET_HANDLER_FAILED = "CB_CMDS_CLASS4_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS4_SET_HANDLER_FAILED = "CB_CMDS_CLASS4_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS6_DEL_HANDLER_FAILED = "CB_CMDS_CLASS6_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS6_GET_ALL_HANDLER_FAILED = "CB_CMDS_CLASS6_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS6_GET_HANDLER_FAILED = "CB_CMDS_CLASS6_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_CLASS6_SET_HANDLER_FAILED = "CB_CMDS_CLASS6_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_DEINIT_OK = "CB_CMDS_DEINIT_OK";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER4_DEL_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER4_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER4_GET_ALL_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER4_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER4_GET_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER4_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER4_SET_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER4_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER6_DEL_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER6_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER6_GET_ALL_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER6_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER6_GET_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER6_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_GLOBAL_PARAMETER6_SET_HANDLER_FAILED = "CB_CMDS_GLOBAL_PARAMETER6_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_INIT_OK = "CB_CMDS_INIT_OK";
extern const isc::log::MessageID CB_CMDS_NETWORK4_DEL_HANDLER_FAILED = "CB_CMDS_NETWORK4_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK4_GET_HANDLER_FAILED = "CB_CMDS_NETWORK4_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK4_LIST_HANDLER_FAILED = "CB_CMDS_NETWORK4_LIST_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK4_SET_HANDLER_FAILED = "CB_CMDS_NETWORK4_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK6_DEL_HANDLER_FAILED = "CB_CMDS_NETWORK6_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK6_GET_HANDLER_FAILED = "CB_CMDS_NETWORK6_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK6_LIST_HANDLER_FAILED = "CB_CMDS_NETWORK6_LIST_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_NETWORK6_SET_HANDLER_FAILED = "CB_CMDS_NETWORK6_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_GLOBAL_DEL_HANDLER_FAILED = "CB_CMDS_OPTION4_GLOBAL_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_GLOBAL_GET_ALL_HANDLER_FAILED = "CB_CMDS_OPTION4_GLOBAL_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_GLOBAL_GET_HANDLER_FAILED = "CB_CMDS_OPTION4_GLOBAL_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_GLOBAL_SET_HANDLER_FAILED = "CB_CMDS_OPTION4_GLOBAL_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_NETWORK_DEL_HANDLER_FAILED = "CB_CMDS_OPTION4_NETWORK_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_NETWORK_SET_HANDLER_FAILED = "CB_CMDS_OPTION4_NETWORK_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_POOL_DEL_HANDLER_FAILED = "CB_CMDS_OPTION4_POOL_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_POOL_SET_HANDLER_FAILED = "CB_CMDS_OPTION4_POOL_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_SUBNET_DEL_HANDLER_FAILED = "CB_CMDS_OPTION4_SUBNET_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION4_SUBNET_SET_HANDLER_FAILED = "CB_CMDS_OPTION4_SUBNET_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_GLOBAL_DEL_HANDLER_FAILED = "CB_CMDS_OPTION6_GLOBAL_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_GLOBAL_GET_ALL_HANDLER_FAILED = "CB_CMDS_OPTION6_GLOBAL_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_GLOBAL_GET_HANDLER_FAILED = "CB_CMDS_OPTION6_GLOBAL_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_GLOBAL_SET_HANDLER_FAILED = "CB_CMDS_OPTION6_GLOBAL_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_NETWORK_DEL_HANDLER_FAILED = "CB_CMDS_OPTION6_NETWORK_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_NETWORK_SET_HANDLER_FAILED = "CB_CMDS_OPTION6_NETWORK_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_PD_POOL_DEL_HANDLER_FAILED = "CB_CMDS_OPTION6_PD_POOL_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_PD_POOL_SET_HANDLER_FAILED = "CB_CMDS_OPTION6_PD_POOL_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_POOL_DEL_HANDLER_FAILED = "CB_CMDS_OPTION6_POOL_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_POOL_SET_HANDLER_FAILED = "CB_CMDS_OPTION6_POOL_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_SUBNET_DEL_HANDLER_FAILED = "CB_CMDS_OPTION6_SUBNET_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION6_SUBNET_SET_HANDLER_FAILED = "CB_CMDS_OPTION6_SUBNET_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF4_DEL_HANDLER_FAILED = "CB_CMDS_OPTION_DEF4_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF4_GET_ALL_HANDLER_FAILED = "CB_CMDS_OPTION_DEF4_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF4_GET_HANDLER_FAILED = "CB_CMDS_OPTION_DEF4_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF4_SET_HANDLER_FAILED = "CB_CMDS_OPTION_DEF4_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF6_DEL_HANDLER_FAILED = "CB_CMDS_OPTION_DEF6_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF6_GET_ALL_HANDLER_FAILED = "CB_CMDS_OPTION_DEF6_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF6_GET_HANDLER_FAILED = "CB_CMDS_OPTION_DEF6_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_OPTION_DEF6_SET_HANDLER_FAILED = "CB_CMDS_OPTION_DEF6_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER4_DEL_HANDLER_FAILED = "CB_CMDS_SERVER4_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER4_GET_ALL_HANDLER_FAILED = "CB_CMDS_SERVER4_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER4_GET_HANDLER_FAILED = "CB_CMDS_SERVER4_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER4_SET_HANDLER_FAILED = "CB_CMDS_SERVER4_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER6_DEL_HANDLER_FAILED = "CB_CMDS_SERVER6_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER6_GET_ALL_HANDLER_FAILED = "CB_CMDS_SERVER6_GET_ALL_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER6_GET_HANDLER_FAILED = "CB_CMDS_SERVER6_GET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SERVER6_SET_HANDLER_FAILED = "CB_CMDS_SERVER6_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET4_DEL_BY_ID_HANDLER_FAILED = "CB_CMDS_SUBNET4_DEL_BY_ID_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET4_DEL_BY_PREFIX_HANDLER_FAILED = "CB_CMDS_SUBNET4_DEL_BY_PREFIX_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET4_GET_BY_ID_HANDLER_FAILED = "CB_CMDS_SUBNET4_GET_BY_ID_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET4_GET_BY_PREFIX_HANDLER_FAILED = "CB_CMDS_SUBNET4_GET_BY_PREFIX_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET4_LIST_HANDLER_FAILED = "CB_CMDS_SUBNET4_LIST_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET4_SET_HANDLER_FAILED = "CB_CMDS_SUBNET4_SET_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET6_DEL_BY_ID_HANDLER_FAILED = "CB_CMDS_SUBNET6_DEL_BY_ID_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET6_DEL_BY_PREFIX_HANDLER_FAILED = "CB_CMDS_SUBNET6_DEL_BY_PREFIX_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET6_GET_BY_ID_HANDLER_FAILED = "CB_CMDS_SUBNET6_GET_BY_ID_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET6_GET_BY_PREFIX_HANDLER_FAILED = "CB_CMDS_SUBNET6_GET_BY_PREFIX_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET6_LIST_HANDLER_FAILED = "CB_CMDS_SUBNET6_LIST_HANDLER_FAILED";
extern const isc::log::MessageID CB_CMDS_SUBNET6_SET_HANDLER_FAILED = "CB_CMDS_SUBNET6_SET_HANDLER_FAILED";

} // namespace cb
} // namespace isc

namespace {

const char* values[] = {
    "CB_CMDS_CLASS4_DEL_HANDLER_FAILED", "remote-class4-del command failed: %1",
    "CB_CMDS_CLASS4_GET_ALL_HANDLER_FAILED", "remote-class4-get-all command failed: %1",
    "CB_CMDS_CLASS4_GET_HANDLER_FAILED", "remote-class4-get command failed: %1",
    "CB_CMDS_CLASS4_SET_HANDLER_FAILED", "remote-class4-set command failed: %1",
    "CB_CMDS_CLASS6_DEL_HANDLER_FAILED", "remote-class6-del command failed: %1",
    "CB_CMDS_CLASS6_GET_ALL_HANDLER_FAILED", "remote-class6-get-all command failed: %1",
    "CB_CMDS_CLASS6_GET_HANDLER_FAILED", "remote-class6-get command failed: %1",
    "CB_CMDS_CLASS6_SET_HANDLER_FAILED", "remote-class6-set command failed: %1",
    "CB_CMDS_DEINIT_OK", "unloading cb_cmds hooks library successful",
    "CB_CMDS_GLOBAL_PARAMETER4_DEL_HANDLER_FAILED", "remote-global-parameter4-del command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER4_GET_ALL_HANDLER_FAILED", "remote-global-parameter4-get-all command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER4_GET_HANDLER_FAILED", "remote-global-parameter4-get command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER4_SET_HANDLER_FAILED", "remote-global-parameter4-set command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER6_DEL_HANDLER_FAILED", "remote-global-parameter6-del command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER6_GET_ALL_HANDLER_FAILED", "remote-global-parameter6-get-all command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER6_GET_HANDLER_FAILED", "remote-global-parameter6-get command failed: %1",
    "CB_CMDS_GLOBAL_PARAMETER6_SET_HANDLER_FAILED", "remote-global-parameter6-set command failed: %1",
    "CB_CMDS_INIT_OK", "loading cb_cmds hooks library successful",
    "CB_CMDS_NETWORK4_DEL_HANDLER_FAILED", "remote-network4-del command failed: %1",
    "CB_CMDS_NETWORK4_GET_HANDLER_FAILED", "remote-network4-get command failed: %1",
    "CB_CMDS_NETWORK4_LIST_HANDLER_FAILED", "remote-network4-list command failed: %1",
    "CB_CMDS_NETWORK4_SET_HANDLER_FAILED", "remote-network4-set command failed: %1",
    "CB_CMDS_NETWORK6_DEL_HANDLER_FAILED", "remote-network6-del command failed: %1",
    "CB_CMDS_NETWORK6_GET_HANDLER_FAILED", "remote-network6-get command failed: %1",
    "CB_CMDS_NETWORK6_LIST_HANDLER_FAILED", "remote-network6-list command failed: %1",
    "CB_CMDS_NETWORK6_SET_HANDLER_FAILED", "remote-network6-set command failed: %1",
    "CB_CMDS_OPTION4_GLOBAL_DEL_HANDLER_FAILED", "remote-global-option4-del command failed: %1",
    "CB_CMDS_OPTION4_GLOBAL_GET_ALL_HANDLER_FAILED", "remote-global-option4-get-all command failed: %1",
    "CB_CMDS_OPTION4_GLOBAL_GET_HANDLER_FAILED", "remote-global-option4-get command failed: %1",
    "CB_CMDS_OPTION4_GLOBAL_SET_HANDLER_FAILED", "remote-global-option4-set command failed: %1",
    "CB_CMDS_OPTION4_NETWORK_DEL_HANDLER_FAILED", "remote-network-option4-del command failed: %1",
    "CB_CMDS_OPTION4_NETWORK_SET_HANDLER_FAILED", "remote-network-option4-set command failed: %1",
    "CB_CMDS_OPTION4_POOL_DEL_HANDLER_FAILED", "remote-pool-option4-del command failed: %1",
    "CB_CMDS_OPTION4_POOL_SET_HANDLER_FAILED", "remote-pool-option4-set command failed: %1",
    "CB_CMDS_OPTION4_SUBNET_DEL_HANDLER_FAILED", "remote-subnet-option4-del command failed: %1",
    "CB_CMDS_OPTION4_SUBNET_SET_HANDLER_FAILED", "remote-subnet-option4-set command failed: %1",
    "CB_CMDS_OPTION6_GLOBAL_DEL_HANDLER_FAILED", "remote-global-option6-del command failed: %1",
    "CB_CMDS_OPTION6_GLOBAL_GET_ALL_HANDLER_FAILED", "remote-global-option6-get-all command failed: %1",
    "CB_CMDS_OPTION6_GLOBAL_GET_HANDLER_FAILED", "remote-global-option6-get command failed: %1",
    "CB_CMDS_OPTION6_GLOBAL_SET_HANDLER_FAILED", "remote-global-option6-set command failed: %1",
    "CB_CMDS_OPTION6_NETWORK_DEL_HANDLER_FAILED", "remote-network-option6-del command failed: %1",
    "CB_CMDS_OPTION6_NETWORK_SET_HANDLER_FAILED", "remote-network-option6-set command failed: %1",
    "CB_CMDS_OPTION6_PD_POOL_DEL_HANDLER_FAILED", "remote-pd-pool-option6-del command failed: %1",
    "CB_CMDS_OPTION6_PD_POOL_SET_HANDLER_FAILED", "remote-pd-pool-option6-set command failed: %1",
    "CB_CMDS_OPTION6_POOL_DEL_HANDLER_FAILED", "remote-pool-option6-del command failed: %1",
    "CB_CMDS_OPTION6_POOL_SET_HANDLER_FAILED", "remote-pool-option6-set command failed: %1",
    "CB_CMDS_OPTION6_SUBNET_DEL_HANDLER_FAILED", "remote-subnet-option6-del command failed: %1",
    "CB_CMDS_OPTION6_SUBNET_SET_HANDLER_FAILED", "remote-subnet-option6-set command failed: %1",
    "CB_CMDS_OPTION_DEF4_DEL_HANDLER_FAILED", "remote-option-def4-del command failed: %1",
    "CB_CMDS_OPTION_DEF4_GET_ALL_HANDLER_FAILED", "remote-option-def4-get-all command failed: %1",
    "CB_CMDS_OPTION_DEF4_GET_HANDLER_FAILED", "remote-option-def4-get command failed: %1",
    "CB_CMDS_OPTION_DEF4_SET_HANDLER_FAILED", "remote-option-def4-set command failed: %1",
    "CB_CMDS_OPTION_DEF6_DEL_HANDLER_FAILED", "remote-option-def6-del command failed: %1",
    "CB_CMDS_OPTION_DEF6_GET_ALL_HANDLER_FAILED", "remote-option-def6-get-all command failed: %1",
    "CB_CMDS_OPTION_DEF6_GET_HANDLER_FAILED", "remote-option-def6-get command failed: %1",
    "CB_CMDS_OPTION_DEF6_SET_HANDLER_FAILED", "remote-option-def6-set command failed: %1",
    "CB_CMDS_SERVER4_DEL_HANDLER_FAILED", "remote-server4-del command failed: %1",
    "CB_CMDS_SERVER4_GET_ALL_HANDLER_FAILED", "remote-server4-get-all command failed: %1",
    "CB_CMDS_SERVER4_GET_HANDLER_FAILED", "remote-server4-get command failed: %1",
    "CB_CMDS_SERVER4_SET_HANDLER_FAILED", "remote-server4-set command failed: %1",
    "CB_CMDS_SERVER6_DEL_HANDLER_FAILED", "remote-server6-del command failed: %1",
    "CB_CMDS_SERVER6_GET_ALL_HANDLER_FAILED", "remote-server6-get-all command failed: %1",
    "CB_CMDS_SERVER6_GET_HANDLER_FAILED", "remote-server6-get command failed: %1",
    "CB_CMDS_SERVER6_SET_HANDLER_FAILED", "remote-server6-set command failed: %1",
    "CB_CMDS_SUBNET4_DEL_BY_ID_HANDLER_FAILED", "remote-subnet4-del-by-id command failed: %1",
    "CB_CMDS_SUBNET4_DEL_BY_PREFIX_HANDLER_FAILED", "remote-subnet4-del-by-prefix command failed: %1",
    "CB_CMDS_SUBNET4_GET_BY_ID_HANDLER_FAILED", "remote-subnet4-get-by-id command failed: %1",
    "CB_CMDS_SUBNET4_GET_BY_PREFIX_HANDLER_FAILED", "remote-subnet4-get-by-prefix command failed: %1",
    "CB_CMDS_SUBNET4_LIST_HANDLER_FAILED", "remote-subnet4-list command failed: %1",
    "CB_CMDS_SUBNET4_SET_HANDLER_FAILED", "remote-subnet4-set command failed: %1",
    "CB_CMDS_SUBNET6_DEL_BY_ID_HANDLER_FAILED", "remote-subnet6-del-by-id command failed: %1",
    "CB_CMDS_SUBNET6_DEL_BY_PREFIX_HANDLER_FAILED", "remote-subnet6-del-by-prefix command failed: %1",
    "CB_CMDS_SUBNET6_GET_BY_ID_HANDLER_FAILED", "remote-subnet6-get-by-id command failed: %1",
    "CB_CMDS_SUBNET6_GET_BY_PREFIX_HANDLER_FAILED", "remote-subnet6-get-by-prefix command failed: %1",
    "CB_CMDS_SUBNET6_LIST_HANDLER_FAILED", "remote-subnet6-list command failed: %1",
    "CB_CMDS_SUBNET6_SET_HANDLER_FAILED", "remote-subnet6-set command failed: %1",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

