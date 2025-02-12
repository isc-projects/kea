// File created from ../../../../src/hooks/dhcp/subnet_cmds/subnet_cmds_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace subnet_cmds {

extern const isc::log::MessageID SUBNET_CMDS_DEINIT_OK = "SUBNET_CMDS_DEINIT_OK";
extern const isc::log::MessageID SUBNET_CMDS_INIT_FAILED = "SUBNET_CMDS_INIT_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_INIT_OK = "SUBNET_CMDS_INIT_OK";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK4_ADD_FAILED = "SUBNET_CMDS_NETWORK4_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK4_DEL_FAILED = "SUBNET_CMDS_NETWORK4_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK4_GET_FAILED = "SUBNET_CMDS_NETWORK4_GET_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK4_LIST_FAILED = "SUBNET_CMDS_NETWORK4_LIST_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK4_SUBNET_ADD_FAILED = "SUBNET_CMDS_NETWORK4_SUBNET_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK4_SUBNET_DEL_FAILED = "SUBNET_CMDS_NETWORK4_SUBNET_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK6_ADD_FAILED = "SUBNET_CMDS_NETWORK6_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK6_DEL_FAILED = "SUBNET_CMDS_NETWORK6_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK6_GET_FAILED = "SUBNET_CMDS_NETWORK6_GET_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK6_LIST_FAILED = "SUBNET_CMDS_NETWORK6_LIST_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK6_SUBNET_ADD_FAILED = "SUBNET_CMDS_NETWORK6_SUBNET_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK6_SUBNET_DEL_FAILED = "SUBNET_CMDS_NETWORK6_SUBNET_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_ADD = "SUBNET_CMDS_NETWORK_ADD";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_DEL = "SUBNET_CMDS_NETWORK_DEL";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_GET = "SUBNET_CMDS_NETWORK_GET";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_GET_EMPTY = "SUBNET_CMDS_NETWORK_GET_EMPTY";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_LIST = "SUBNET_CMDS_NETWORK_LIST";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_LIST_EMPTY = "SUBNET_CMDS_NETWORK_LIST_EMPTY";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_SUBNET_ADD = "SUBNET_CMDS_NETWORK_SUBNET_ADD";
extern const isc::log::MessageID SUBNET_CMDS_NETWORK_SUBNET_DEL = "SUBNET_CMDS_NETWORK_SUBNET_DEL";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_ADD_FAILED = "SUBNET_CMDS_SUBNET4_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_DELTA_ADD_FAILED = "SUBNET_CMDS_SUBNET4_DELTA_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_DELTA_DEL_FAILED = "SUBNET_CMDS_SUBNET4_DELTA_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_DEL_FAILED = "SUBNET_CMDS_SUBNET4_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_GET_FAILED = "SUBNET_CMDS_SUBNET4_GET_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_LIST_FAILED = "SUBNET_CMDS_SUBNET4_LIST_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET4_UPDATE_FAILED = "SUBNET_CMDS_SUBNET4_UPDATE_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_ADD_FAILED = "SUBNET_CMDS_SUBNET6_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_DELTA_ADD_FAILED = "SUBNET_CMDS_SUBNET6_DELTA_ADD_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_DELTA_DEL_FAILED = "SUBNET_CMDS_SUBNET6_DELTA_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_DEL_FAILED = "SUBNET_CMDS_SUBNET6_DEL_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_GET_FAILED = "SUBNET_CMDS_SUBNET6_GET_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_LIST_FAILED = "SUBNET_CMDS_SUBNET6_LIST_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET6_UPDATE_FAILED = "SUBNET_CMDS_SUBNET6_UPDATE_FAILED";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_ADD = "SUBNET_CMDS_SUBNET_ADD";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_DEL = "SUBNET_CMDS_SUBNET_DEL";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_GET = "SUBNET_CMDS_SUBNET_GET";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_GET_EMPTY = "SUBNET_CMDS_SUBNET_GET_EMPTY";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_LIST = "SUBNET_CMDS_SUBNET_LIST";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_LIST_EMPTY = "SUBNET_CMDS_SUBNET_LIST_EMPTY";
extern const isc::log::MessageID SUBNET_CMDS_SUBNET_UPDATE = "SUBNET_CMDS_SUBNET_UPDATE";

} // namespace subnet_cmds
} // namespace isc

namespace {

const char* values[] = {
    "SUBNET_CMDS_DEINIT_OK", "unloading Subnet Commands hooks library successful",
    "SUBNET_CMDS_INIT_FAILED", "loading Subnet Commands hooks library failed: %1",
    "SUBNET_CMDS_INIT_OK", "loading Subnet Commands hooks library successful",
    "SUBNET_CMDS_NETWORK4_ADD_FAILED", "failed to add new IPv4 network: %1",
    "SUBNET_CMDS_NETWORK4_DEL_FAILED", "failed to delete IPv4 network: %1",
    "SUBNET_CMDS_NETWORK4_GET_FAILED", "failed to return an IPv4 network: %1",
    "SUBNET_CMDS_NETWORK4_LIST_FAILED", "failed to return a list of IPv4 networks: %1",
    "SUBNET_CMDS_NETWORK4_SUBNET_ADD_FAILED", "failed to add existing IPv4 subnet to a shared network: %1",
    "SUBNET_CMDS_NETWORK4_SUBNET_DEL_FAILED", "failed to remove a IPv4 subnet from a shared network: %1",
    "SUBNET_CMDS_NETWORK6_ADD_FAILED", "failed to add new IPv6 network: %1",
    "SUBNET_CMDS_NETWORK6_DEL_FAILED", "failed to delete IPv6 network: %1",
    "SUBNET_CMDS_NETWORK6_GET_FAILED", "failed to return an IPv6 network: %1",
    "SUBNET_CMDS_NETWORK6_LIST_FAILED", "failed to return a list of IPv6 networks: %1",
    "SUBNET_CMDS_NETWORK6_SUBNET_ADD_FAILED", "failed to add existing IPv6 subnet to a shared network: %1",
    "SUBNET_CMDS_NETWORK6_SUBNET_DEL_FAILED", "failed to remove a IPv6 subnet from a shared network: %1",
    "SUBNET_CMDS_NETWORK_ADD", "successfully added shared network %1",
    "SUBNET_CMDS_NETWORK_DEL", "successfully deleted shared network %1",
    "SUBNET_CMDS_NETWORK_GET", "successfully retrieved shared network %1",
    "SUBNET_CMDS_NETWORK_GET_EMPTY", "specified shared network is not found: %1",
    "SUBNET_CMDS_NETWORK_LIST", "successfully retrieved list of %1 %2 shared networks",
    "SUBNET_CMDS_NETWORK_LIST_EMPTY", "no %1 shared networks listed",
    "SUBNET_CMDS_NETWORK_SUBNET_ADD", "%1 subnet %2 (id %3) added to shared network %4",
    "SUBNET_CMDS_NETWORK_SUBNET_DEL", "%1 subnet %2 (id %3) removed from shared network %4",
    "SUBNET_CMDS_SUBNET4_ADD_FAILED", "failed to add new IPv4 subnet: %1",
    "SUBNET_CMDS_SUBNET4_DELTA_ADD_FAILED", "failed to update IPv4 subnet: %1",
    "SUBNET_CMDS_SUBNET4_DELTA_DEL_FAILED", "failed to update IPv4 subnet: %1",
    "SUBNET_CMDS_SUBNET4_DEL_FAILED", "failed to delete IPv4 subnet: %1",
    "SUBNET_CMDS_SUBNET4_GET_FAILED", "failed to return an IPv4 subnet: %1",
    "SUBNET_CMDS_SUBNET4_LIST_FAILED", "failed to return a list of IPv4 subnets: %1",
    "SUBNET_CMDS_SUBNET4_UPDATE_FAILED", "failed to update IPv4 subnet: %1",
    "SUBNET_CMDS_SUBNET6_ADD_FAILED", "failed to add new IPv6 subnet: %1",
    "SUBNET_CMDS_SUBNET6_DELTA_ADD_FAILED", "failed to update IPv6 subnet: %1",
    "SUBNET_CMDS_SUBNET6_DELTA_DEL_FAILED", "failed to update IPv6 subnet: %1",
    "SUBNET_CMDS_SUBNET6_DEL_FAILED", "failed to delete IPv6 subnet: %1",
    "SUBNET_CMDS_SUBNET6_GET_FAILED", "failed to return an IPv6 subnet: %1",
    "SUBNET_CMDS_SUBNET6_LIST_FAILED", "failed to return a list of IPv6 subnets: %1",
    "SUBNET_CMDS_SUBNET6_UPDATE_FAILED", "failed to update IPv6 subnet: %1",
    "SUBNET_CMDS_SUBNET_ADD", "successfully added subnet %1 having id %2",
    "SUBNET_CMDS_SUBNET_DEL", "successfully deleted subnet %1 having id %2",
    "SUBNET_CMDS_SUBNET_GET", "successfully retrieved subnet %1 having id %2",
    "SUBNET_CMDS_SUBNET_GET_EMPTY", "specified subnet is not found: %1",
    "SUBNET_CMDS_SUBNET_LIST", "successfully retrieved list of %1 %2 subnets",
    "SUBNET_CMDS_SUBNET_LIST_EMPTY", "no %1 subnets listed",
    "SUBNET_CMDS_SUBNET_UPDATE", "successfully updated subnet %1 having id %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

