// File created from src/hooks/dhcp/pgsql/pgsql_cb_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace cb {

extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4 = "PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6 = "PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6 = "PGSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4 = "PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6 = "PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS4 = "PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS6 = "PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4 = "PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6 = "PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_OPTION4 = "PGSQL_CB_CREATE_UPDATE_OPTION4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_OPTION6 = "PGSQL_CB_CREATE_UPDATE_OPTION6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_OPTION_DEF4 = "PGSQL_CB_CREATE_UPDATE_OPTION_DEF4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_OPTION_DEF6 = "PGSQL_CB_CREATE_UPDATE_OPTION_DEF6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SERVER4 = "PGSQL_CB_CREATE_UPDATE_SERVER4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SERVER6 = "PGSQL_CB_CREATE_UPDATE_SERVER6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK4 = "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK6 = "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4 = "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6 = "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SUBNET4 = "PGSQL_CB_CREATE_UPDATE_SUBNET4";
extern const isc::log::MessageID PGSQL_CB_CREATE_UPDATE_SUBNET6 = "PGSQL_CB_CREATE_UPDATE_SUBNET6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4 = "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4_RESULT = "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6 = "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6_RESULT = "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4 = "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4_RESULT = "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6 = "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6_RESULT = "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_OPTION_DEFS4 = "PGSQL_CB_DELETE_ALL_OPTION_DEFS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_OPTION_DEFS4_RESULT = "PGSQL_CB_DELETE_ALL_OPTION_DEFS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_OPTION_DEFS6 = "PGSQL_CB_DELETE_ALL_OPTION_DEFS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_OPTION_DEFS6_RESULT = "PGSQL_CB_DELETE_ALL_OPTION_DEFS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SERVERS4 = "PGSQL_CB_DELETE_ALL_SERVERS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SERVERS4_RESULT = "PGSQL_CB_DELETE_ALL_SERVERS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SERVERS6 = "PGSQL_CB_DELETE_ALL_SERVERS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SERVERS6_RESULT = "PGSQL_CB_DELETE_ALL_SERVERS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4 = "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4_RESULT = "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6 = "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6_RESULT = "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SUBNETS4 = "PGSQL_CB_DELETE_ALL_SUBNETS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SUBNETS4_RESULT = "PGSQL_CB_DELETE_ALL_SUBNETS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SUBNETS6 = "PGSQL_CB_DELETE_ALL_SUBNETS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_ALL_SUBNETS6_RESULT = "PGSQL_CB_DELETE_ALL_SUBNETS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_POOL_OPTION4 = "PGSQL_CB_DELETE_BY_POOL_OPTION4";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_POOL_OPTION4_RESULT = "PGSQL_CB_DELETE_BY_POOL_OPTION4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_POOL_OPTION6 = "PGSQL_CB_DELETE_BY_POOL_OPTION6";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_POOL_OPTION6_RESULT = "PGSQL_CB_DELETE_BY_POOL_OPTION6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6 = "PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6_RESULT = "PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_PREFIX_SUBNET4 = "PGSQL_CB_DELETE_BY_PREFIX_SUBNET4";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_PREFIX_SUBNET4_RESULT = "PGSQL_CB_DELETE_BY_PREFIX_SUBNET4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_PREFIX_SUBNET6 = "PGSQL_CB_DELETE_BY_PREFIX_SUBNET6";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_PREFIX_SUBNET6_RESULT = "PGSQL_CB_DELETE_BY_PREFIX_SUBNET6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4 = "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4_RESULT = "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6 = "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6_RESULT = "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4 = "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4_RESULT = "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6 = "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6";
extern const isc::log::MessageID PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6_RESULT = "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_CLIENT_CLASS4 = "PGSQL_CB_DELETE_CLIENT_CLASS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_CLIENT_CLASS4_RESULT = "PGSQL_CB_DELETE_CLIENT_CLASS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_CLIENT_CLASS6 = "PGSQL_CB_DELETE_CLIENT_CLASS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_CLIENT_CLASS6_RESULT = "PGSQL_CB_DELETE_CLIENT_CLASS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_GLOBAL_PARAMETER4 = "PGSQL_CB_DELETE_GLOBAL_PARAMETER4";
extern const isc::log::MessageID PGSQL_CB_DELETE_GLOBAL_PARAMETER4_RESULT = "PGSQL_CB_DELETE_GLOBAL_PARAMETER4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_GLOBAL_PARAMETER6 = "PGSQL_CB_DELETE_GLOBAL_PARAMETER6";
extern const isc::log::MessageID PGSQL_CB_DELETE_GLOBAL_PARAMETER6_RESULT = "PGSQL_CB_DELETE_GLOBAL_PARAMETER6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION4 = "PGSQL_CB_DELETE_OPTION4";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION4_RESULT = "PGSQL_CB_DELETE_OPTION4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION6 = "PGSQL_CB_DELETE_OPTION6";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION6_RESULT = "PGSQL_CB_DELETE_OPTION6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION_DEF4 = "PGSQL_CB_DELETE_OPTION_DEF4";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION_DEF4_RESULT = "PGSQL_CB_DELETE_OPTION_DEF4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION_DEF6 = "PGSQL_CB_DELETE_OPTION_DEF6";
extern const isc::log::MessageID PGSQL_CB_DELETE_OPTION_DEF6_RESULT = "PGSQL_CB_DELETE_OPTION_DEF6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SERVER4 = "PGSQL_CB_DELETE_SERVER4";
extern const isc::log::MessageID PGSQL_CB_DELETE_SERVER4_RESULT = "PGSQL_CB_DELETE_SERVER4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SERVER6 = "PGSQL_CB_DELETE_SERVER6";
extern const isc::log::MessageID PGSQL_CB_DELETE_SERVER6_RESULT = "PGSQL_CB_DELETE_SERVER6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK4 = "PGSQL_CB_DELETE_SHARED_NETWORK4";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK4_RESULT = "PGSQL_CB_DELETE_SHARED_NETWORK4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK6 = "PGSQL_CB_DELETE_SHARED_NETWORK6";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK6_RESULT = "PGSQL_CB_DELETE_SHARED_NETWORK6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4 = "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4_RESULT = "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6 = "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6_RESULT = "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4 = "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4_RESULT = "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6 = "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6";
extern const isc::log::MessageID PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6_RESULT = "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_CLIENT_CLASSES4 = "PGSQL_CB_GET_ALL_CLIENT_CLASSES4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_CLIENT_CLASSES4_RESULT = "PGSQL_CB_GET_ALL_CLIENT_CLASSES4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_CLIENT_CLASSES6 = "PGSQL_CB_GET_ALL_CLIENT_CLASSES6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_CLIENT_CLASSES6_RESULT = "PGSQL_CB_GET_ALL_CLIENT_CLASSES6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4 = "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT = "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6 = "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT = "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTIONS4 = "PGSQL_CB_GET_ALL_OPTIONS4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTIONS4_RESULT = "PGSQL_CB_GET_ALL_OPTIONS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTIONS6 = "PGSQL_CB_GET_ALL_OPTIONS6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTIONS6_RESULT = "PGSQL_CB_GET_ALL_OPTIONS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTION_DEFS4 = "PGSQL_CB_GET_ALL_OPTION_DEFS4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTION_DEFS4_RESULT = "PGSQL_CB_GET_ALL_OPTION_DEFS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTION_DEFS6 = "PGSQL_CB_GET_ALL_OPTION_DEFS6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_OPTION_DEFS6_RESULT = "PGSQL_CB_GET_ALL_OPTION_DEFS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SERVERS4 = "PGSQL_CB_GET_ALL_SERVERS4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SERVERS4_RESULT = "PGSQL_CB_GET_ALL_SERVERS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SERVERS6 = "PGSQL_CB_GET_ALL_SERVERS6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SERVERS6_RESULT = "PGSQL_CB_GET_ALL_SERVERS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SHARED_NETWORKS4 = "PGSQL_CB_GET_ALL_SHARED_NETWORKS4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT = "PGSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SHARED_NETWORKS6 = "PGSQL_CB_GET_ALL_SHARED_NETWORKS6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT = "PGSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SUBNETS4 = "PGSQL_CB_GET_ALL_SUBNETS4";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SUBNETS4_RESULT = "PGSQL_CB_GET_ALL_SUBNETS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SUBNETS6 = "PGSQL_CB_GET_ALL_SUBNETS6";
extern const isc::log::MessageID PGSQL_CB_GET_ALL_SUBNETS6_RESULT = "PGSQL_CB_GET_ALL_SUBNETS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_CLIENT_CLASS4 = "PGSQL_CB_GET_CLIENT_CLASS4";
extern const isc::log::MessageID PGSQL_CB_GET_CLIENT_CLASS6 = "PGSQL_CB_GET_CLIENT_CLASS6";
extern const isc::log::MessageID PGSQL_CB_GET_GLOBAL_PARAMETER4 = "PGSQL_CB_GET_GLOBAL_PARAMETER4";
extern const isc::log::MessageID PGSQL_CB_GET_GLOBAL_PARAMETER6 = "PGSQL_CB_GET_GLOBAL_PARAMETER6";
extern const isc::log::MessageID PGSQL_CB_GET_HOST4 = "PGSQL_CB_GET_HOST4";
extern const isc::log::MessageID PGSQL_CB_GET_HOST6 = "PGSQL_CB_GET_HOST6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4 = "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4_RESULT = "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6 = "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6_RESULT = "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4 = "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT = "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6 = "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT = "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTIONS4 = "PGSQL_CB_GET_MODIFIED_OPTIONS4";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTIONS4_RESULT = "PGSQL_CB_GET_MODIFIED_OPTIONS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTIONS6 = "PGSQL_CB_GET_MODIFIED_OPTIONS6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTIONS6_RESULT = "PGSQL_CB_GET_MODIFIED_OPTIONS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTION_DEFS4 = "PGSQL_CB_GET_MODIFIED_OPTION_DEFS4";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT = "PGSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTION_DEFS6 = "PGSQL_CB_GET_MODIFIED_OPTION_DEFS6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT = "PGSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4 = "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT = "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6 = "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT = "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SUBNETS4 = "PGSQL_CB_GET_MODIFIED_SUBNETS4";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SUBNETS4_RESULT = "PGSQL_CB_GET_MODIFIED_SUBNETS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SUBNETS6 = "PGSQL_CB_GET_MODIFIED_SUBNETS6";
extern const isc::log::MessageID PGSQL_CB_GET_MODIFIED_SUBNETS6_RESULT = "PGSQL_CB_GET_MODIFIED_SUBNETS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_OPTION4 = "PGSQL_CB_GET_OPTION4";
extern const isc::log::MessageID PGSQL_CB_GET_OPTION6 = "PGSQL_CB_GET_OPTION6";
extern const isc::log::MessageID PGSQL_CB_GET_OPTION_DEF4 = "PGSQL_CB_GET_OPTION_DEF4";
extern const isc::log::MessageID PGSQL_CB_GET_OPTION_DEF6 = "PGSQL_CB_GET_OPTION_DEF6";
extern const isc::log::MessageID PGSQL_CB_GET_PORT4 = "PGSQL_CB_GET_PORT4";
extern const isc::log::MessageID PGSQL_CB_GET_PORT6 = "PGSQL_CB_GET_PORT6";
extern const isc::log::MessageID PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4 = "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4";
extern const isc::log::MessageID PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT = "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6 = "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6";
extern const isc::log::MessageID PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT = "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_SERVER4 = "PGSQL_CB_GET_SERVER4";
extern const isc::log::MessageID PGSQL_CB_GET_SERVER6 = "PGSQL_CB_GET_SERVER6";
extern const isc::log::MessageID PGSQL_CB_GET_SHARED_NETWORK4 = "PGSQL_CB_GET_SHARED_NETWORK4";
extern const isc::log::MessageID PGSQL_CB_GET_SHARED_NETWORK6 = "PGSQL_CB_GET_SHARED_NETWORK6";
extern const isc::log::MessageID PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4 = "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4";
extern const isc::log::MessageID PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT = "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6 = "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6";
extern const isc::log::MessageID PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT = "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT";
extern const isc::log::MessageID PGSQL_CB_GET_SUBNET4_BY_PREFIX = "PGSQL_CB_GET_SUBNET4_BY_PREFIX";
extern const isc::log::MessageID PGSQL_CB_GET_SUBNET4_BY_SUBNET_ID = "PGSQL_CB_GET_SUBNET4_BY_SUBNET_ID";
extern const isc::log::MessageID PGSQL_CB_GET_SUBNET6_BY_PREFIX = "PGSQL_CB_GET_SUBNET6_BY_PREFIX";
extern const isc::log::MessageID PGSQL_CB_GET_SUBNET6_BY_SUBNET_ID = "PGSQL_CB_GET_SUBNET6_BY_SUBNET_ID";
extern const isc::log::MessageID PGSQL_CB_GET_TYPE4 = "PGSQL_CB_GET_TYPE4";
extern const isc::log::MessageID PGSQL_CB_GET_TYPE6 = "PGSQL_CB_GET_TYPE6";
extern const isc::log::MessageID PGSQL_CB_NO_TLS_SUPPORT = "PGSQL_CB_NO_TLS_SUPPORT";
extern const isc::log::MessageID PGSQL_CB_RECONNECT_ATTEMPT_FAILED4 = "PGSQL_CB_RECONNECT_ATTEMPT_FAILED4";
extern const isc::log::MessageID PGSQL_CB_RECONNECT_ATTEMPT_FAILED6 = "PGSQL_CB_RECONNECT_ATTEMPT_FAILED6";
extern const isc::log::MessageID PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE4 = "PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE4";
extern const isc::log::MessageID PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE6 = "PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE6";
extern const isc::log::MessageID PGSQL_CB_RECONNECT_FAILED4 = "PGSQL_CB_RECONNECT_FAILED4";
extern const isc::log::MessageID PGSQL_CB_RECONNECT_FAILED6 = "PGSQL_CB_RECONNECT_FAILED6";
extern const isc::log::MessageID PGSQL_CB_REGISTER_BACKEND_TYPE4 = "PGSQL_CB_REGISTER_BACKEND_TYPE4";
extern const isc::log::MessageID PGSQL_CB_REGISTER_BACKEND_TYPE6 = "PGSQL_CB_REGISTER_BACKEND_TYPE6";
extern const isc::log::MessageID PGSQL_CB_TLS_SUPPORT = "PGSQL_CB_TLS_SUPPORT";
extern const isc::log::MessageID PGSQL_CB_UNREGISTER_BACKEND_TYPE4 = "PGSQL_CB_UNREGISTER_BACKEND_TYPE4";
extern const isc::log::MessageID PGSQL_CB_UNREGISTER_BACKEND_TYPE6 = "PGSQL_CB_UNREGISTER_BACKEND_TYPE6";

} // namespace cb
} // namespace isc

namespace {

const char* values[] = {
    "PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4", "create or update option pool start: %1 pool end: %2",
    "PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6", "create or update option pool start: %1 pool end: %2",
    "PGSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6", "create or update option prefix: %1 prefix len: %2",
    "PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4", "create or update option by subnet id: %1",
    "PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6", "create or update option by subnet id: %1",
    "PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS4", "create or update client class: %1",
    "PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS6", "create or update client class: %1",
    "PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4", "create or update global parameter: %1",
    "PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6", "create or update global parameter: %1",
    "PGSQL_CB_CREATE_UPDATE_OPTION4", "create or update option",
    "PGSQL_CB_CREATE_UPDATE_OPTION6", "create or update option",
    "PGSQL_CB_CREATE_UPDATE_OPTION_DEF4", "create or update option definition: %1 code: %2",
    "PGSQL_CB_CREATE_UPDATE_OPTION_DEF6", "create or update option definition: %1 code: %2",
    "PGSQL_CB_CREATE_UPDATE_SERVER4", "create or update server: %1",
    "PGSQL_CB_CREATE_UPDATE_SERVER6", "create or update server: %1",
    "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK4", "create or update shared network: %1",
    "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK6", "create or update shared network: %1",
    "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4", "create or update shared network: %1 option",
    "PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6", "create or update shared network: %1 option",
    "PGSQL_CB_CREATE_UPDATE_SUBNET4", "create or update subnet: %1",
    "PGSQL_CB_CREATE_UPDATE_SUBNET6", "create or update subnet: %1",
    "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4", "delete all client classes",
    "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6", "delete all client classes",
    "PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4", "delete all global parameters",
    "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6", "delete all global parameters",
    "PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_OPTION_DEFS4", "delete all option definitions",
    "PGSQL_CB_DELETE_ALL_OPTION_DEFS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_OPTION_DEFS6", "delete all option definitions",
    "PGSQL_CB_DELETE_ALL_OPTION_DEFS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_SERVERS4", "delete all DHCPv4 servers",
    "PGSQL_CB_DELETE_ALL_SERVERS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_SERVERS6", "delete all DHCPv6 servers",
    "PGSQL_CB_DELETE_ALL_SERVERS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4", "delete all shared networks",
    "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6", "delete all shared networks",
    "PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_SUBNETS4", "delete all subnets",
    "PGSQL_CB_DELETE_ALL_SUBNETS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_ALL_SUBNETS6", "delete all subnets",
    "PGSQL_CB_DELETE_ALL_SUBNETS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_POOL_OPTION4", "delete pool start: %1 pool end: %2 option code: %3 space: %4",
    "PGSQL_CB_DELETE_BY_POOL_OPTION4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_POOL_OPTION6", "delete pool start: %1 pool end: %2 option code: %3 space: %4",
    "PGSQL_CB_DELETE_BY_POOL_OPTION6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6", "delete prefix: %1 prefix len: %2 option code: %3 space: %4",
    "PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_PREFIX_SUBNET4", "delete subnet by prefix: %1",
    "PGSQL_CB_DELETE_BY_PREFIX_SUBNET4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_PREFIX_SUBNET6", "delete subnet by prefix: %1",
    "PGSQL_CB_DELETE_BY_PREFIX_SUBNET6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4", "delete by subnet id: %1 option code: %2 space: %3",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6", "delete by subnet id: %1 option code: %2 space: %3",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4", "delete subnet by subnet id: %1",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6", "delete subnet by subnet id: %1",
    "PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_CLIENT_CLASS4", "delete client class: %1",
    "PGSQL_CB_DELETE_CLIENT_CLASS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_CLIENT_CLASS6", "delete client class: %1",
    "PGSQL_CB_DELETE_CLIENT_CLASS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_GLOBAL_PARAMETER4", "delete global parameter: %1",
    "PGSQL_CB_DELETE_GLOBAL_PARAMETER4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_GLOBAL_PARAMETER6", "delete global parameter: %1",
    "PGSQL_CB_DELETE_GLOBAL_PARAMETER6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_OPTION4", "delete option code: %1 space: %2",
    "PGSQL_CB_DELETE_OPTION4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_OPTION6", "delete option code: %1 space: %2",
    "PGSQL_CB_DELETE_OPTION6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_OPTION_DEF4", "delete option definition code: %1 space: %2",
    "PGSQL_CB_DELETE_OPTION_DEF4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_OPTION_DEF6", "delete option definition code: %1 space: %2",
    "PGSQL_CB_DELETE_OPTION_DEF6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SERVER4", "delete DHCPv4 server: %1",
    "PGSQL_CB_DELETE_SERVER4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SERVER6", "delete DHCPv6 server: %1",
    "PGSQL_CB_DELETE_SERVER6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SHARED_NETWORK4", "delete shared network: %1",
    "PGSQL_CB_DELETE_SHARED_NETWORK4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SHARED_NETWORK6", "delete shared network: %1",
    "PGSQL_CB_DELETE_SHARED_NETWORK6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4", "delete shared network: %1 option code: %2 space: %3",
    "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6", "delete shared network: %1 option code: %2 space: %3",
    "PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4", "delete shared network: %1 subnets",
    "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4_RESULT", "deleted: %1 entries",
    "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6", "delete shared network: %1 subnets",
    "PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6_RESULT", "deleted: %1 entries",
    "PGSQL_CB_GET_ALL_CLIENT_CLASSES4", "retrieving all client classes",
    "PGSQL_CB_GET_ALL_CLIENT_CLASSES4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_CLIENT_CLASSES6", "retrieving all client classes",
    "PGSQL_CB_GET_ALL_CLIENT_CLASSES6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4", "retrieving all global parameters",
    "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6", "retrieving all global parameters",
    "PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_OPTIONS4", "retrieving all options",
    "PGSQL_CB_GET_ALL_OPTIONS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_OPTIONS6", "retrieving all options",
    "PGSQL_CB_GET_ALL_OPTIONS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_OPTION_DEFS4", "retrieving all option definitions",
    "PGSQL_CB_GET_ALL_OPTION_DEFS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_OPTION_DEFS6", "retrieving all option definitions",
    "PGSQL_CB_GET_ALL_OPTION_DEFS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_SERVERS4", "retrieving all servers",
    "PGSQL_CB_GET_ALL_SERVERS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_SERVERS6", "retrieving all DHCPv6 servers",
    "PGSQL_CB_GET_ALL_SERVERS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_SHARED_NETWORKS4", "retrieving all shared networks",
    "PGSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_SHARED_NETWORKS6", "retrieving all shared networks",
    "PGSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_SUBNETS4", "retrieving all subnets",
    "PGSQL_CB_GET_ALL_SUBNETS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_ALL_SUBNETS6", "retrieving all subnets",
    "PGSQL_CB_GET_ALL_SUBNETS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_CLIENT_CLASS4", "retrieving client class: %1",
    "PGSQL_CB_GET_CLIENT_CLASS6", "retrieving client class: %1",
    "PGSQL_CB_GET_GLOBAL_PARAMETER4", "retrieving global parameter: %1",
    "PGSQL_CB_GET_GLOBAL_PARAMETER6", "retrieving global parameter: %1",
    "PGSQL_CB_GET_HOST4", "get host",
    "PGSQL_CB_GET_HOST6", "get host",
    "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4", "retrieving modified client classes from: %1",
    "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6", "retrieving modified client classes from: %1",
    "PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4", "retrieving modified global parameters from: %1",
    "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6", "retrieving modified global parameters from: %1",
    "PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_OPTIONS4", "retrieving modified options from: %1",
    "PGSQL_CB_GET_MODIFIED_OPTIONS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_OPTIONS6", "retrieving modified options from: %1",
    "PGSQL_CB_GET_MODIFIED_OPTIONS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_OPTION_DEFS4", "retrieving modified option definitions from: %1",
    "PGSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_OPTION_DEFS6", "retrieving modified option definitions from: %1",
    "PGSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4", "retrieving modified shared networks from: %1",
    "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6", "retrieving modified shared networks from: %1",
    "PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_SUBNETS4", "retrieving modified subnets from: %1",
    "PGSQL_CB_GET_MODIFIED_SUBNETS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_MODIFIED_SUBNETS6", "retrieving modified subnets from: %1",
    "PGSQL_CB_GET_MODIFIED_SUBNETS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_OPTION4", "retrieving option code: %1 space: %2",
    "PGSQL_CB_GET_OPTION6", "retrieving option code: %1 space: %2",
    "PGSQL_CB_GET_OPTION_DEF4", "retrieving option definition code: %1 space: %2",
    "PGSQL_CB_GET_OPTION_DEF6", "retrieving option definition code: %1 space: %2",
    "PGSQL_CB_GET_PORT4", "get port",
    "PGSQL_CB_GET_PORT6", "get port",
    "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4", "retrieving audit entries from: %1 %2",
    "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6", "retrieving audit entries from: %1 %2",
    "PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_SERVER4", "retrieving DHCPv4 server: %1",
    "PGSQL_CB_GET_SERVER6", "retrieving DHCPv6 server: %1",
    "PGSQL_CB_GET_SHARED_NETWORK4", "retrieving shared network: %1",
    "PGSQL_CB_GET_SHARED_NETWORK6", "retrieving shared network: %1",
    "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4", "retrieving shared network: %1 subnets",
    "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6", "retrieving shared network: %1 subnets",
    "PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT", "retrieving: %1 elements",
    "PGSQL_CB_GET_SUBNET4_BY_PREFIX", "retrieving subnet by prefix: %1",
    "PGSQL_CB_GET_SUBNET4_BY_SUBNET_ID", "retrieving subnet by subnet id: %1",
    "PGSQL_CB_GET_SUBNET6_BY_PREFIX", "retrieving subnet by prefix: %1",
    "PGSQL_CB_GET_SUBNET6_BY_SUBNET_ID", "retrieving subnet by subnet id: %1",
    "PGSQL_CB_GET_TYPE4", "get type",
    "PGSQL_CB_GET_TYPE6", "get type",
    "PGSQL_CB_NO_TLS_SUPPORT", "Attempt to configure TLS (unsupported for PostgreSQL): %1",
    "PGSQL_CB_RECONNECT_ATTEMPT_FAILED4", "database reconnect failed: %1",
    "PGSQL_CB_RECONNECT_ATTEMPT_FAILED6", "database reconnect failed: %1",
    "PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE4", "scheduling attempt %1 of %2 in %3 milliseconds",
    "PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE6", "scheduling attempt %1 of %2 in %3 milliseconds",
    "PGSQL_CB_RECONNECT_FAILED4", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "PGSQL_CB_RECONNECT_FAILED6", "maximum number of database reconnect attempts: %1, has been exhausted without success",
    "PGSQL_CB_REGISTER_BACKEND_TYPE4", "register backend",
    "PGSQL_CB_REGISTER_BACKEND_TYPE6", "register backend",
    "PGSQL_CB_TLS_SUPPORT", "Attempt to configure TLS: %1",
    "PGSQL_CB_UNREGISTER_BACKEND_TYPE4", "unregister backend",
    "PGSQL_CB_UNREGISTER_BACKEND_TYPE6", "unregister backend",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

