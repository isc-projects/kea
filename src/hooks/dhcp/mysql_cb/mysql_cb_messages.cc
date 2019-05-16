// File created from ../../../../src/hooks/dhcp/mysql_cb/mysql_cb_messages.mes on Thu May 16 2019 09:34

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace cb {

extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4 = "MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6 = "MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6 = "MYSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4 = "MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6 = "MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4 = "MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6 = "MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_OPTION4 = "MYSQL_CB_CREATE_UPDATE_OPTION4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_OPTION6 = "MYSQL_CB_CREATE_UPDATE_OPTION6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_OPTION_DEF4 = "MYSQL_CB_CREATE_UPDATE_OPTION_DEF4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_OPTION_DEF6 = "MYSQL_CB_CREATE_UPDATE_OPTION_DEF6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK4 = "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK6 = "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4 = "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6 = "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_SUBNET4 = "MYSQL_CB_CREATE_UPDATE_SUBNET4";
extern const isc::log::MessageID MYSQL_CB_CREATE_UPDATE_SUBNET6 = "MYSQL_CB_CREATE_UPDATE_SUBNET6";
extern const isc::log::MessageID MYSQL_CB_DEINIT_OK = "MYSQL_CB_DEINIT_OK";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4 = "MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6 = "MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_OPTION_DEFS4 = "MYSQL_CB_DELETE_ALL_OPTION_DEFS4";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_OPTION_DEFS6 = "MYSQL_CB_DELETE_ALL_OPTION_DEFS6";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_SHARED_NETWORKS4 = "MYSQL_CB_DELETE_ALL_SHARED_NETWORKS4";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_SHARED_NETWORKS6 = "MYSQL_CB_DELETE_ALL_SHARED_NETWORKS6";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_SUBNETS4 = "MYSQL_CB_DELETE_ALL_SUBNETS4";
extern const isc::log::MessageID MYSQL_CB_DELETE_ALL_SUBNETS6 = "MYSQL_CB_DELETE_ALL_SUBNETS6";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_POOL_OPTION4 = "MYSQL_CB_DELETE_BY_POOL_OPTION4";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_POOL_OPTION6 = "MYSQL_CB_DELETE_BY_POOL_OPTION6";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6 = "MYSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_PREFIX_SUBNET4 = "MYSQL_CB_DELETE_BY_PREFIX_SUBNET4";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_PREFIX_SUBNET6 = "MYSQL_CB_DELETE_BY_PREFIX_SUBNET6";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION4 = "MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION4";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION6 = "MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION6";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4 = "MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4";
extern const isc::log::MessageID MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6 = "MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6";
extern const isc::log::MessageID MYSQL_CB_DELETE_GLOBAL_PARAMETER4 = "MYSQL_CB_DELETE_GLOBAL_PARAMETER4";
extern const isc::log::MessageID MYSQL_CB_DELETE_GLOBAL_PARAMETER6 = "MYSQL_CB_DELETE_GLOBAL_PARAMETER6";
extern const isc::log::MessageID MYSQL_CB_DELETE_OPTION4 = "MYSQL_CB_DELETE_OPTION4";
extern const isc::log::MessageID MYSQL_CB_DELETE_OPTION6 = "MYSQL_CB_DELETE_OPTION6";
extern const isc::log::MessageID MYSQL_CB_DELETE_OPTION_DEF4 = "MYSQL_CB_DELETE_OPTION_DEF4";
extern const isc::log::MessageID MYSQL_CB_DELETE_OPTION_DEF6 = "MYSQL_CB_DELETE_OPTION_DEF6";
extern const isc::log::MessageID MYSQL_CB_DELETE_SHARED_NETWORK4 = "MYSQL_CB_DELETE_SHARED_NETWORK4";
extern const isc::log::MessageID MYSQL_CB_DELETE_SHARED_NETWORK6 = "MYSQL_CB_DELETE_SHARED_NETWORK6";
extern const isc::log::MessageID MYSQL_CB_DELETE_SHARED_NETWORK_OPTION4 = "MYSQL_CB_DELETE_SHARED_NETWORK_OPTION4";
extern const isc::log::MessageID MYSQL_CB_DELETE_SHARED_NETWORK_OPTION6 = "MYSQL_CB_DELETE_SHARED_NETWORK_OPTION6";
extern const isc::log::MessageID MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4 = "MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4";
extern const isc::log::MessageID MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6 = "MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS4 = "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS4";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT = "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6 = "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT = "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTIONS4 = "MYSQL_CB_GET_ALL_OPTIONS4";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTIONS4_RESULT = "MYSQL_CB_GET_ALL_OPTIONS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTIONS6 = "MYSQL_CB_GET_ALL_OPTIONS6";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTIONS6_RESULT = "MYSQL_CB_GET_ALL_OPTIONS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTION_DEFS4 = "MYSQL_CB_GET_ALL_OPTION_DEFS4";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTION_DEFS4_RESULT = "MYSQL_CB_GET_ALL_OPTION_DEFS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTION_DEFS6 = "MYSQL_CB_GET_ALL_OPTION_DEFS6";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_OPTION_DEFS6_RESULT = "MYSQL_CB_GET_ALL_OPTION_DEFS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SHARED_NETWORKS4 = "MYSQL_CB_GET_ALL_SHARED_NETWORKS4";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT = "MYSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SHARED_NETWORKS6 = "MYSQL_CB_GET_ALL_SHARED_NETWORKS6";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT = "MYSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SUBNETS4 = "MYSQL_CB_GET_ALL_SUBNETS4";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SUBNETS4_RESULT = "MYSQL_CB_GET_ALL_SUBNETS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SUBNETS6 = "MYSQL_CB_GET_ALL_SUBNETS6";
extern const isc::log::MessageID MYSQL_CB_GET_ALL_SUBNETS6_RESULT = "MYSQL_CB_GET_ALL_SUBNETS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_GLOBAL_PARAMETER4 = "MYSQL_CB_GET_GLOBAL_PARAMETER4";
extern const isc::log::MessageID MYSQL_CB_GET_GLOBAL_PARAMETER6 = "MYSQL_CB_GET_GLOBAL_PARAMETER6";
extern const isc::log::MessageID MYSQL_CB_GET_HOST4 = "MYSQL_CB_GET_HOST4";
extern const isc::log::MessageID MYSQL_CB_GET_HOST6 = "MYSQL_CB_GET_HOST6";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4 = "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT = "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6 = "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT = "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTIONS4 = "MYSQL_CB_GET_MODIFIED_OPTIONS4";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTIONS4_RESULT = "MYSQL_CB_GET_MODIFIED_OPTIONS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTIONS6 = "MYSQL_CB_GET_MODIFIED_OPTIONS6";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTIONS6_RESULT = "MYSQL_CB_GET_MODIFIED_OPTIONS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTION_DEFS4 = "MYSQL_CB_GET_MODIFIED_OPTION_DEFS4";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT = "MYSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTION_DEFS6 = "MYSQL_CB_GET_MODIFIED_OPTION_DEFS6";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT = "MYSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS4 = "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS4";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT = "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6 = "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT = "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SUBNETS4 = "MYSQL_CB_GET_MODIFIED_SUBNETS4";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SUBNETS4_RESULT = "MYSQL_CB_GET_MODIFIED_SUBNETS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SUBNETS6 = "MYSQL_CB_GET_MODIFIED_SUBNETS6";
extern const isc::log::MessageID MYSQL_CB_GET_MODIFIED_SUBNETS6_RESULT = "MYSQL_CB_GET_MODIFIED_SUBNETS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_OPTION4 = "MYSQL_CB_GET_OPTION4";
extern const isc::log::MessageID MYSQL_CB_GET_OPTION6 = "MYSQL_CB_GET_OPTION6";
extern const isc::log::MessageID MYSQL_CB_GET_OPTION_DEF4 = "MYSQL_CB_GET_OPTION_DEF4";
extern const isc::log::MessageID MYSQL_CB_GET_OPTION_DEF6 = "MYSQL_CB_GET_OPTION_DEF6";
extern const isc::log::MessageID MYSQL_CB_GET_PORT4 = "MYSQL_CB_GET_PORT4";
extern const isc::log::MessageID MYSQL_CB_GET_PORT6 = "MYSQL_CB_GET_PORT6";
extern const isc::log::MessageID MYSQL_CB_GET_RECENT_AUDIT_ENTRIES4 = "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES4";
extern const isc::log::MessageID MYSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT = "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6 = "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6";
extern const isc::log::MessageID MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT = "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_SHARED_NETWORK4 = "MYSQL_CB_GET_SHARED_NETWORK4";
extern const isc::log::MessageID MYSQL_CB_GET_SHARED_NETWORK6 = "MYSQL_CB_GET_SHARED_NETWORK6";
extern const isc::log::MessageID MYSQL_CB_GET_SHARED_NETWORK_SUBNETS4 = "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS4";
extern const isc::log::MessageID MYSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT = "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6 = "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6";
extern const isc::log::MessageID MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT = "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT";
extern const isc::log::MessageID MYSQL_CB_GET_SUBNET4_BY_PREFIX = "MYSQL_CB_GET_SUBNET4_BY_PREFIX";
extern const isc::log::MessageID MYSQL_CB_GET_SUBNET4_BY_SUBNET_ID = "MYSQL_CB_GET_SUBNET4_BY_SUBNET_ID";
extern const isc::log::MessageID MYSQL_CB_GET_SUBNET6_BY_PREFIX = "MYSQL_CB_GET_SUBNET6_BY_PREFIX";
extern const isc::log::MessageID MYSQL_CB_GET_SUBNET6_BY_SUBNET_ID = "MYSQL_CB_GET_SUBNET6_BY_SUBNET_ID";
extern const isc::log::MessageID MYSQL_CB_GET_TYPE4 = "MYSQL_CB_GET_TYPE4";
extern const isc::log::MessageID MYSQL_CB_GET_TYPE6 = "MYSQL_CB_GET_TYPE6";
extern const isc::log::MessageID MYSQL_CB_INIT_OK = "MYSQL_CB_INIT_OK";
extern const isc::log::MessageID MYSQL_CB_REGISTER_BACKEND_TYPE4 = "MYSQL_CB_REGISTER_BACKEND_TYPE4";
extern const isc::log::MessageID MYSQL_CB_REGISTER_BACKEND_TYPE6 = "MYSQL_CB_REGISTER_BACKEND_TYPE6";
extern const isc::log::MessageID MYSQL_CB_UNREGISTER_BACKEND_TYPE4 = "MYSQL_CB_UNREGISTER_BACKEND_TYPE4";
extern const isc::log::MessageID MYSQL_CB_UNREGISTER_BACKEND_TYPE6 = "MYSQL_CB_UNREGISTER_BACKEND_TYPE6";

} // namespace cb
} // namespace isc

namespace {

const char* values[] = {
    "MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4", "create or update MySQL CB option pool start: %1 pool end: %2",
    "MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6", "create or update MySQL CB option pool start: %1 pool end: %2",
    "MYSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6", "create or update MySQL CB option prefix: %1 prefix len: %2",
    "MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4", "create or update MySQL CB option by subnet id: %1",
    "MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6", "create or update MySQL CB option by subnet id: %1",
    "MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4", "create or update MySQL CB global parameter: %1",
    "MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6", "create or update MySQL CB global parameter: %1",
    "MYSQL_CB_CREATE_UPDATE_OPTION4", "create or update MySQL CB option",
    "MYSQL_CB_CREATE_UPDATE_OPTION6", "create or update MySQL CB option",
    "MYSQL_CB_CREATE_UPDATE_OPTION_DEF4", "create or update MySQL CB option definition: %1 code: %2",
    "MYSQL_CB_CREATE_UPDATE_OPTION_DEF6", "create or update MySQL CB option definition: %1 code: %2",
    "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK4", "create or update MySQL CB shared network: %1",
    "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK6", "create or update MySQL CB shared network: %1",
    "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4", "create or update MySQL CB shared network: %1 option",
    "MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6", "create or update MySQL CB shared network: %1 option",
    "MYSQL_CB_CREATE_UPDATE_SUBNET4", "create or update MySQL CB subnet: %1",
    "MYSQL_CB_CREATE_UPDATE_SUBNET6", "create or update MySQL CB subnet: %1",
    "MYSQL_CB_DEINIT_OK", "unloading MYSQAL CB hooks library successful",
    "MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4", "delete MySQL CB all global parameters",
    "MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6", "delete MySQL CB all global parameters",
    "MYSQL_CB_DELETE_ALL_OPTION_DEFS4", "delete MySQL CB all option definitions",
    "MYSQL_CB_DELETE_ALL_OPTION_DEFS6", "delete MySQL CB all option definitions",
    "MYSQL_CB_DELETE_ALL_SHARED_NETWORKS4", "delete MySQL CB all shared networks",
    "MYSQL_CB_DELETE_ALL_SHARED_NETWORKS6", "delete MySQL CB all shared networks",
    "MYSQL_CB_DELETE_ALL_SUBNETS4", "delete MySQL CB all subnets",
    "MYSQL_CB_DELETE_ALL_SUBNETS6", "delete MySQL CB all subnets",
    "MYSQL_CB_DELETE_BY_POOL_OPTION4", "delete MySQL CB pool start: %1 pool end: %2 option code: %3 space: %4",
    "MYSQL_CB_DELETE_BY_POOL_OPTION6", "delete MySQL CB pool start: %1 pool end: %2 option code: %3 space: %4",
    "MYSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6", "delete MySQL CB prefix: %1 prefix len: %2 option code: %3 space: %4",
    "MYSQL_CB_DELETE_BY_PREFIX_SUBNET4", "delete MySQL CB subnet by prefix: %1",
    "MYSQL_CB_DELETE_BY_PREFIX_SUBNET6", "delete MySQL CB subnet by prefix: %1",
    "MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION4", "delete MySQL CB by subnet id: %1 option code: %2 space: %3",
    "MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION6", "delete MySQL CB by subnet id: %1 option code: %2 space: %3",
    "MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4", "delete MySQL CB subnet by subnet id: %1",
    "MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6", "delete MySQL CB subnet by subnet id: %1",
    "MYSQL_CB_DELETE_GLOBAL_PARAMETER4", "delete MySQL CB global parameter: %1",
    "MYSQL_CB_DELETE_GLOBAL_PARAMETER6", "delete MySQL CB global parameter: %1",
    "MYSQL_CB_DELETE_OPTION4", "delete MySQL CB option code: %1 space: %2",
    "MYSQL_CB_DELETE_OPTION6", "delete MySQL CB option code: %1 space: %2",
    "MYSQL_CB_DELETE_OPTION_DEF4", "delete MySQL CB option definition code: %1 space: %2",
    "MYSQL_CB_DELETE_OPTION_DEF6", "delete MySQL CB option definition code: %1 space: %2",
    "MYSQL_CB_DELETE_SHARED_NETWORK4", "delete MySQL CB shared network: %1",
    "MYSQL_CB_DELETE_SHARED_NETWORK6", "delete MySQL CB shared network: %1",
    "MYSQL_CB_DELETE_SHARED_NETWORK_OPTION4", "delete MySQL CB shared network: %1 option code: %2 space: %3",
    "MYSQL_CB_DELETE_SHARED_NETWORK_OPTION6", "delete MySQL CB shared network: %1 option code: %2 space: %3",
    "MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4", "delete MySQL CB shared network: %1 subnets",
    "MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6", "delete MySQL CB shared network: %1 subnets",
    "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS4", "retrieving MySQL CB all global parameters",
    "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6", "retrieving MySQL CB all global parameters",
    "MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_OPTIONS4", "retrieving MySQL CB all options",
    "MYSQL_CB_GET_ALL_OPTIONS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_OPTIONS6", "retrieving MySQL CB all options",
    "MYSQL_CB_GET_ALL_OPTIONS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_OPTION_DEFS4", "retrieving MySQL CB all option definitions",
    "MYSQL_CB_GET_ALL_OPTION_DEFS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_OPTION_DEFS6", "retrieving MySQL CB all option definitions",
    "MYSQL_CB_GET_ALL_OPTION_DEFS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_SHARED_NETWORKS4", "retrieving MySQL CB all shared networks",
    "MYSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_SHARED_NETWORKS6", "retrieving MySQL CB all shared networks",
    "MYSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_SUBNETS4", "retrieving all MySQL CB subnets",
    "MYSQL_CB_GET_ALL_SUBNETS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_ALL_SUBNETS6", "retrieving all MySQL CB subnets",
    "MYSQL_CB_GET_ALL_SUBNETS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_GLOBAL_PARAMETER4", "retrieving MySQL CB global parameter: %1",
    "MYSQL_CB_GET_GLOBAL_PARAMETER6", "retrieving MySQL CB global parameter: %1",
    "MYSQL_CB_GET_HOST4", "get MySQL CB host",
    "MYSQL_CB_GET_HOST6", "get MySQL CB host",
    "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4", "retrieving MySQL CB modified global parameters from: %1",
    "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6", "retrieving MySQL CB modified global parameters from: %1",
    "MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_OPTIONS4", "retrieving MySQL CB modified options from: %1",
    "MYSQL_CB_GET_MODIFIED_OPTIONS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_OPTIONS6", "retrieving MySQL CB modified options from: %1",
    "MYSQL_CB_GET_MODIFIED_OPTIONS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_OPTION_DEFS4", "retrieving MySQL CB modified option definitions from: %1",
    "MYSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_OPTION_DEFS6", "retrieving MySQL CB modified option definitions from: %1",
    "MYSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS4", "retrieving MySQL CB modified shared networks from: %1",
    "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6", "retrieving MySQL CB modified shared networks from: %1",
    "MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_SUBNETS4", "retrieving modified MySQL CB subnets from: %1",
    "MYSQL_CB_GET_MODIFIED_SUBNETS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_MODIFIED_SUBNETS6", "retrieving modified MySQL CB subnets from: %1",
    "MYSQL_CB_GET_MODIFIED_SUBNETS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_OPTION4", "retrieving MySQL CB option code: %1 space: %2",
    "MYSQL_CB_GET_OPTION6", "retrieving MySQL CB option code: %1 space: %2",
    "MYSQL_CB_GET_OPTION_DEF4", "retrieving MySQL CB option definition code: %1 space: %2",
    "MYSQL_CB_GET_OPTION_DEF6", "retrieving MySQL CB option definition code: %1 space: %2",
    "MYSQL_CB_GET_PORT4", "get MySQL CB port",
    "MYSQL_CB_GET_PORT6", "get MySQL CB port",
    "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES4", "retrieving MySQL CB audit entries",
    "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6", "retrieving MySQL CB audit entries",
    "MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_SHARED_NETWORK4", "retrieving MySQL CB shared network: %1",
    "MYSQL_CB_GET_SHARED_NETWORK6", "retrieving MySQL CB shared network: %1",
    "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS4", "retrieving MySQL CB shared network: %1 subnets",
    "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6", "retrieving MySQL CB shared network: %1 subnets",
    "MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT", "retrieving: %1 elements",
    "MYSQL_CB_GET_SUBNET4_BY_PREFIX", "retrieving MySQL CB subnet by prefix: %1",
    "MYSQL_CB_GET_SUBNET4_BY_SUBNET_ID", "retrieving MySQL CB subnet by subnet id: %1",
    "MYSQL_CB_GET_SUBNET6_BY_PREFIX", "retrieving MySQL CB subnet by prefix: %1",
    "MYSQL_CB_GET_SUBNET6_BY_SUBNET_ID", "retrieving MySQL CB subnet by subnet id: %1",
    "MYSQL_CB_GET_TYPE4", "get MySQL CB type",
    "MYSQL_CB_GET_TYPE6", "get MySQL CB type",
    "MYSQL_CB_INIT_OK", "loading MYSQL CB hooks library successful",
    "MYSQL_CB_REGISTER_BACKEND_TYPE4", "register MySQL CB backend",
    "MYSQL_CB_REGISTER_BACKEND_TYPE6", "register MySQL CB backend",
    "MYSQL_CB_UNREGISTER_BACKEND_TYPE4", "unregister MySQL CB backend",
    "MYSQL_CB_UNREGISTER_BACKEND_TYPE6", "unregister MySQL CB backend",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

