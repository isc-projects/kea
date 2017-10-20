// File created from ../../../src/lib/dhcpsrv/hosts_messages.mes on Fri Oct 20 2017 00:23

#ifndef HOSTS_MESSAGES_H
#define HOSTS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID HOSTS_CFG_ADD_HOST;
extern const isc::log::MessageID HOSTS_CFG_CLOSE_HOST_DATA_SOURCE;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6_HOST;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_HWADDR_DUID;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER_COUNT;
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER_HOST;
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
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_HWADDR_DUID;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_NULL;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_PREFIX;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_DUID_HWADDR;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST;
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_NULL;

} // namespace dhcp
} // namespace isc

#endif // HOSTS_MESSAGES_H
