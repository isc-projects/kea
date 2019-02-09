// File created from ../../../src/lib/dhcpsrv/hosts_messages.mes on Fri Feb 08 2019 20:31

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID HOSTS_BACKENDS_REGISTERED = "HOSTS_BACKENDS_REGISTERED";
extern const isc::log::MessageID HOSTS_BACKEND_DEREGISTER = "HOSTS_BACKEND_DEREGISTER";
extern const isc::log::MessageID HOSTS_BACKEND_REGISTER = "HOSTS_BACKEND_REGISTER";
extern const isc::log::MessageID HOSTS_CFG_ADD_HOST = "HOSTS_CFG_ADD_HOST";
extern const isc::log::MessageID HOSTS_CFG_CACHE_HOST_DATA_SOURCE = "HOSTS_CFG_CACHE_HOST_DATA_SOURCE";
extern const isc::log::MessageID HOSTS_CFG_CLOSE_HOST_DATA_SOURCE = "HOSTS_CFG_CLOSE_HOST_DATA_SOURCE";
extern const isc::log::MessageID HOSTS_CFG_DEL_ALL_SUBNET4 = "HOSTS_CFG_DEL_ALL_SUBNET4";
extern const isc::log::MessageID HOSTS_CFG_DEL_ALL_SUBNET6 = "HOSTS_CFG_DEL_ALL_SUBNET6";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4 = "HOSTS_CFG_GET_ALL_ADDRESS4";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4_COUNT = "HOSTS_CFG_GET_ALL_ADDRESS4_COUNT";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS4_HOST = "HOSTS_CFG_GET_ALL_ADDRESS4_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6 = "HOSTS_CFG_GET_ALL_ADDRESS6";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6_COUNT = "HOSTS_CFG_GET_ALL_ADDRESS6_COUNT";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_ADDRESS6_HOST = "HOSTS_CFG_GET_ALL_ADDRESS6_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER = "HOSTS_CFG_GET_ALL_IDENTIFIER";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER_COUNT = "HOSTS_CFG_GET_ALL_IDENTIFIER_COUNT";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_IDENTIFIER_HOST = "HOSTS_CFG_GET_ALL_IDENTIFIER_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID4 = "HOSTS_CFG_GET_ALL_SUBNET_ID4";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID4_COUNT = "HOSTS_CFG_GET_ALL_SUBNET_ID4_COUNT";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID4_HOST = "HOSTS_CFG_GET_ALL_SUBNET_ID4_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID6 = "HOSTS_CFG_GET_ALL_SUBNET_ID6";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID6_COUNT = "HOSTS_CFG_GET_ALL_SUBNET_ID6_COUNT";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID6_HOST = "HOSTS_CFG_GET_ALL_SUBNET_ID6_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6 = "HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_COUNT = "HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_COUNT";
extern const isc::log::MessageID HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_HOST = "HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_PREFIX = "HOSTS_CFG_GET_ONE_PREFIX";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_PREFIX_HOST = "HOSTS_CFG_GET_ONE_PREFIX_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_PREFIX_NULL = "HOSTS_CFG_GET_ONE_PREFIX_NULL";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4 = "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_HOST = "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_NULL = "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_NULL";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6 = "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_HOST = "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_NULL = "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_NULL";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER = "HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_HOST = "HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_HOST";
extern const isc::log::MessageID HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_NULL = "HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_NULL";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4 = "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER = "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST = "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_NULL = "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_NULL";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_PREFIX = "HOSTS_MGR_ALTERNATE_GET6_PREFIX";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6 = "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER = "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST = "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST";
extern const isc::log::MessageID HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_NULL = "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_NULL";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "HOSTS_BACKENDS_REGISTERED", "the following host backend types are available: %1",
    "HOSTS_BACKEND_DEREGISTER", "deregistered host backend type: %1",
    "HOSTS_BACKEND_REGISTER", "registered host backend type: %1",
    "HOSTS_CFG_ADD_HOST", "add the host for reservations: %1",
    "HOSTS_CFG_CACHE_HOST_DATA_SOURCE", "get host cache data source: %1",
    "HOSTS_CFG_CLOSE_HOST_DATA_SOURCE", "Closing host data source: %1",
    "HOSTS_CFG_DEL_ALL_SUBNET4", "deleted all %1 host(s) for subnet id %2",
    "HOSTS_CFG_DEL_ALL_SUBNET6", "deleted all %1 host(s) including %2 IPv6 reservation(s) for subnet id %3",
    "HOSTS_CFG_GET_ALL_ADDRESS4", "get all hosts with reservations for IPv4 address %1",
    "HOSTS_CFG_GET_ALL_ADDRESS4_COUNT", "using address %1, found %2 host(s)",
    "HOSTS_CFG_GET_ALL_ADDRESS4_HOST", "using address %1 found host: %2",
    "HOSTS_CFG_GET_ALL_ADDRESS6", "get all hosts with reservations for IPv6 address %1",
    "HOSTS_CFG_GET_ALL_ADDRESS6_COUNT", "using address %1, found %2 host(s)",
    "HOSTS_CFG_GET_ALL_ADDRESS6_HOST", "using address %1 found host: %2",
    "HOSTS_CFG_GET_ALL_IDENTIFIER", "get all hosts with reservations using identifier: %1",
    "HOSTS_CFG_GET_ALL_IDENTIFIER_COUNT", "using identifier %1, found %2 host(s)",
    "HOSTS_CFG_GET_ALL_IDENTIFIER_HOST", "using identifier: %1, found host: %2",
    "HOSTS_CFG_GET_ALL_SUBNET_ID4", "get all hosts with reservations for IPv4 subnet %1",
    "HOSTS_CFG_GET_ALL_SUBNET_ID4_COUNT", "using IPv4 subnet %1, found %2 host(s)",
    "HOSTS_CFG_GET_ALL_SUBNET_ID4_HOST", "using IPv4 subnet %1, found host: %2",
    "HOSTS_CFG_GET_ALL_SUBNET_ID6", "get all hosts with reservations for IPv6 subnet %1",
    "HOSTS_CFG_GET_ALL_SUBNET_ID6_COUNT", "using IPv6 subnet %1, found %2 host(s)",
    "HOSTS_CFG_GET_ALL_SUBNET_ID6_HOST", "using IPv6 subnet %1, found host: %2",
    "HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6", "get all hosts with reservations for subnet id %1 and IPv6 address %2",
    "HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_COUNT", "using subnet id %1 and address %2, found %3 host(s)",
    "HOSTS_CFG_GET_ALL_SUBNET_ID_ADDRESS6_HOST", "using subnet id %1 and address %2, found host: %3",
    "HOSTS_CFG_GET_ONE_PREFIX", "get one host with reservation for prefix %1/%2",
    "HOSTS_CFG_GET_ONE_PREFIX_HOST", "using prefix %1/%2, found host: %3",
    "HOSTS_CFG_GET_ONE_PREFIX_NULL", "host not found using prefix %1/%2",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4", "get one host with reservation for subnet id %1 and IPv4 address %2",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_HOST", "using subnet id %1 and address %2, found host: %3",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS4_NULL", "host not found using subnet id %1 and address %2",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6", "get one host with reservation for subnet id %1 and including IPv6 address %2",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_HOST", "using subnet id %1 and address %2, found host: %3",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_ADDRESS6_NULL", "host not found using subnet id %1 and address %2",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER", "get one host with %1 reservation for subnet id %2, identified by %3",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_HOST", "using subnet id %1 and identifier %2, found host: %3",
    "HOSTS_CFG_GET_ONE_SUBNET_ID_IDENTIFIER_NULL", "host not found using subnet id %1 and identifier %2",
    "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_ADDRESS4", "trying alternate sources for host using subnet id %1 and address %2",
    "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER", "get one host with IPv4 reservation for subnet id %1, identified by %2",
    "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_HOST", "using subnet id %1 and identifier %2, found in %3 host: %4",
    "HOSTS_MGR_ALTERNATE_GET4_SUBNET_ID_IDENTIFIER_NULL", "host not found using subnet id %1 and identifier %2",
    "HOSTS_MGR_ALTERNATE_GET6_PREFIX", "trying alternate sources for host using prefix %1/%2",
    "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_ADDRESS6", "trying alternate sources for host using subnet id %1 and IPv6 address %2",
    "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER", "get one host with IPv6 reservation for subnet id %1, identified by %2",
    "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_HOST", "using subnet id %1 and identifier %2, found in %3 host: %4",
    "HOSTS_MGR_ALTERNATE_GET6_SUBNET_ID_IDENTIFIER_NULL", "host not found using subnet id %1 and identifier %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

