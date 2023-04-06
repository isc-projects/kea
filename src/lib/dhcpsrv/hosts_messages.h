// File created from ../../../src/lib/dhcpsrv/hosts_messages.mes

#ifndef HOSTS_MESSAGES_H
#define HOSTS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID HOSTS_BACKENDS_REGISTERED;
extern const isc::log::MessageID HOSTS_BACKEND_DEREGISTER;
extern const isc::log::MessageID HOSTS_BACKEND_REGISTER;
extern const isc::log::MessageID HOSTS_CFG_ADD_HOST;
extern const isc::log::MessageID HOSTS_CFG_CACHE_HOST_DATA_SOURCE;
extern const isc::log::MessageID HOSTS_CFG_CLOSE_HOST_DATA_SOURCE;
extern const isc::log::MessageID HOSTS_CFG_DEL;
extern const isc::log::MessageID HOSTS_CFG_DEL4;
extern const isc::log::MessageID HOSTS_CFG_DEL6;
extern const isc::log::MessageID HOSTS_CFG_DEL_ALL_SUBNET4;
extern const isc::log::MessageID HOSTS_CFG_DEL_ALL_SUBNET6;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID4;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID4_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID4_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID6;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID6_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HOSTNAME_SUBNET_ID6_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID4;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID4_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID4_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID6;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID6_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID6_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS4;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS4_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS4_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_PREFIX;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_PREFIX_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_PREFIX_NULL;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_NULL;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_NULL;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_NULL;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_NULL;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_PREFIX;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_NULL;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET_ALL_SUBNET_ID_ADDRESS4;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET_ALL_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOSTS_MGR_NON_UNIQUE_IP_UNSUPPORTED;

} // namespace dhcp
} // namespace isc

#endif // HOSTS_MESSAGES_H
