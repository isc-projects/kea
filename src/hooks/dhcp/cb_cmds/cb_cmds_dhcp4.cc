// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <hooks/hooks.h>

#include <cb_cmds/cb_cmds_dhcp4.h>
#include <cb_cmds/cb_parsers.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;
using namespace isc::hooks;

namespace isc {
namespace cb {

const SimpleKeywords ConfigCmdsDhcp4Impl::GLOBAL4_MAP_PARAMETERS = {
    { "compatibility.ignore-dhcp-server-identifier", Element::boolean },
    { "compatibility.ignore-rai-link-selection", Element::boolean },
    { "compatibility.lenient-option-parsing", Element::boolean },
    { "compatibility.exclude-first-last-24", Element::boolean },
    { "dhcp-ddns.enable-updates", Element::boolean },
    { "dhcp-ddns.max-queue-size", Element::integer },
    { "dhcp-ddns.ncr-format", Element::string },
    { "dhcp-ddns.ncr-protocol", Element::string },
    { "dhcp-ddns.sender-ip", Element::string },
    { "dhcp-ddns.sender-port", Element::integer },
    { "dhcp-ddns.server-ip", Element::string },
    { "dhcp-ddns.server-port", Element::integer },
    { "expired-leases-processing.flush-reclaimed-timer-wait-time", Element::integer },
    { "expired-leases-processing.hold-reclaimed-time", Element::integer },
    { "expired-leases-processing.max-reclaim-leases", Element::integer },
    { "expired-leases-processing.max-reclaim-time", Element::integer },
    { "expired-leases-processing.reclaim-timer-wait-time", Element::integer },
    { "expired-leases-processing.unwarned-reclaim-cycles", Element::integer },
    { "multi-threading.enable-multi-threading", Element::boolean },
    { "multi-threading.thread-pool-size", Element::integer },
    { "multi-threading.packet-queue-size", Element::integer },
    { "sanity-checks.lease-checks", Element::string },
    { "sanity-checks.extended-info-checks", Element::string },
    { "dhcp-queue-control.enable-queue", Element::boolean },
    { "dhcp-queue-control.queue-type", Element::string },
    { "dhcp-queue-control.capacity", Element::integer },
    /* not yet supported
    { "interfaces-config.dhcp-socket-type", Element::string },
    { "interfaces-config.outbound-interface", Element::string },
    { "interfaces-config.re-detect", Element::boolean },
    { "interfaces-config.interfaces", Element::list },
    { "interfaces-config.service-sockets-require-all", Element::boolean },
    { "interfaces-config.service-sockets-max-retries", Element::integer },
    { "interfaces-config.service-sockets-retry-wait-time", Element::integer },
    { "lease-database.lfc-interval", Element::integer },
    { "lease-database.max-row-errors", Element::integer },
    { "lease-database.name", Element::string },
    { "lease-database.persist", Element::boolean },
    { "lease-database.type", Element::string },
    { "lease-database.host", Element::string },
    { "lease-database.password", Element::string },
    { "lease-database.port", Element::integer },
    { "lease-database.user", Element::string },
    { "lease-database.readonly", Element::boolean },
    { "lease-database.trust-anchor", Element::string },
    { "lease-database.cert-file", Element::string },
    { "lease-database.key-file", Element::string },
    { "lease-database.ssl-mode", Element::string },
    { "lease-database.cipher-list", Element::string },
    { "lease-database.reconnect-wait-time", Element::integer },
    { "lease-database.max-reconnect-tries", Element::integer },
    { "lease-database.on-fail", Element::string },
    { "lease-database.retry-on-startup", Element::boolean },
    { "lease-database.connect-timeout", Element::integer },
    { "lease-database.read-timeout", Element::integer },
    { "lease-database.write-timeout", Element::integer },
    { "lease-database.tcp-user-timeout", Element::integer },
    { "config-control.config-fetch-wait-time", Element::integer },
    */
};

SimpleKeywords
ConfigCmdsDhcp4Impl::initGlobalContainersParameters() {
    SimpleKeywords globals = SimpleParser4::GLOBAL4_PARAMETERS;
    // Add supported top level map parameters.
    globals.insert(ConfigCmdsDhcp4Impl::GLOBAL4_MAP_PARAMETERS.begin(),
                   ConfigCmdsDhcp4Impl::GLOBAL4_MAP_PARAMETERS.end());
    // Remove unsupported top level list parameters.
    auto globals_copy = globals;
    for (auto const& key : globals_copy) {
        if (key.second == Element::list &&
            SimpleParser4::GLOBAL4_LIST_PARAMETERS.find(key.first) ==
            SimpleParser4::GLOBAL4_LIST_PARAMETERS.end()) {
            globals.erase(key.first);
        }
    }

    return (globals);
}

SimpleKeywords&
ConfigCmdsDhcp4Impl::getGlobalContainersParameters() {
    static SimpleKeywords parameters = ConfigCmdsDhcp4Impl::initGlobalContainersParameters();
    return (parameters);
}

void
ConfigCmdsDhcp4Impl::setGlobalParameter4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const StampedValuePtr& stamped_value) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
        createUpdateGlobalParameter4(backend_selector, server_selector,
                                     stamped_value);
    };
    auto const& globals = ConfigCmdsDhcp4Impl::getGlobalContainersParameters();
    setGlobalParameter(callout_handle, globals, SimpleParser4::GLOBAL4_LIST_PARAMETER_TYPES, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delGlobalParameter4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteGlobalParameter4(backend_selector, server_selector, name));
    };
    auto const& globals = ConfigCmdsDhcp4Impl::getGlobalContainersParameters();
    delGlobalParameter(callout_handle, globals, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::getGlobalParameter4(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getGlobalParameter4(backend_selector, server_selector, name));
    };
    auto const& globals = ConfigCmdsDhcp4Impl::getGlobalContainersParameters();
    getGlobalParameter(callout_handle, globals, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::getAllGlobalParameters4(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllGlobalParameters4(backend_selector, server_selector));
    };
    auto const& globals = ConfigCmdsDhcp4Impl::getGlobalContainersParameters();
    getAllGlobalParameters(callout_handle, globals, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setSubnet4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const Subnet4Ptr& subnet) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
        createUpdateSubnet4(backend_selector, server_selector, subnet);
    };
    setSubnet<Subnet4Ptr, CBSubnet4ConfigParser>(callout_handle,
                                                 AF_INET,
                                                 create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delSubnet4Id(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const SubnetID& subnet_id) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteSubnet4(backend_selector, server_selector, subnet_id));
    };
    delSubnetId(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::delSubnet4Prefix(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& subnet_prefix) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteSubnet4(backend_selector, server_selector, subnet_prefix));
    };
    delSubnetPrefix(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::getSubnet4Id(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const SubnetID& subnet_id) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getSubnet4(backend_selector, server_selector, subnet_id));
    };
    getSubnetId<Subnet4Ptr>(callout_handle, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::getSubnet4Prefix(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& subnet_prefix) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getSubnet4(backend_selector, server_selector, subnet_prefix));
    };
    getSubnetPrefix<Subnet4Ptr>(callout_handle, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::listSubnets4(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllSubnets4(backend_selector, server_selector));
    };
    listSubnets<Subnet4Collection>(callout_handle, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setSharedNetwork4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const SharedNetwork4Ptr& shared_network) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
        createUpdateSharedNetwork4(backend_selector, server_selector, shared_network);
    };
    setSharedNetwork<SharedNetwork4Ptr, CBSharedNetwork4Parser>
        (callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delSharedNetwork4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteSharedNetwork4(backend_selector, server_selector, name));
    };
    auto delete_all_fun = [] (const BackendSelector& backend_selector,
                              const ServerSelector& server_selector,
                              const std::string& name) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
        deleteSharedNetworkSubnets4(backend_selector, server_selector, name);
    };
    delSharedNetwork(callout_handle, AF_INET, delete_fun, delete_all_fun);
}

void
ConfigCmdsDhcp4Impl::getSharedNetwork4(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getSharedNetwork4(backend_selector, server_selector, name));

    };
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector,
                           const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getSharedNetworkSubnets4(backend_selector, server_selector, name));
    };
    getSharedNetwork<SharedNetwork4Ptr, Subnet4Collection>
        (callout_handle, AF_INET, get_fun, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::listSharedNetworks4(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllSharedNetworks4(backend_selector, server_selector));
    };
    listSharedNetworks<SharedNetwork4Collection>
        (callout_handle, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setClientClass4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const ClientClassDefPtr& client_class,
                                 const std::string& follow_class_name) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
        createUpdateClientClass4(backend_selector, server_selector, client_class,
                                 follow_class_name);
    };
    setClientClass(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delClientClass4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteClientClass4(backend_selector, server_selector, name));
    };
    delClientClass(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::getClientClass4(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& name) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getClientClass4(backend_selector, server_selector, name));

    };
    getClientClass(callout_handle, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::getAllClientClasses4(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllClientClasses4(backend_selector, server_selector));
    };
    getAllClientClasses(callout_handle, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setOptionDef4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const OptionDefinitionPtr& option_def) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
        createUpdateOptionDef4(backend_selector, server_selector, option_def);
    };
    setOptionDef(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delOptionDef4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const uint16_t code,
                          const std::string& space,
                          bool force) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteOptionDef4(backend_selector, server_selector,
                                 code, space, force));
    };
    delOptionDef(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::getOptionDef4(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const uint16_t code,
                       const std::string& space) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getOptionDef4(backend_selector, server_selector,
                              code, space));
    };
    getOptionDef(callout_handle, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::getAllOptionDefs4(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllOptionDefs4(backend_selector, server_selector));

    };
    getAllOptionDefs(callout_handle, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setGlobalOption4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateOption4(backend_selector, server_selector, option);
    };
    setGlobalOption(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delGlobalOption4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteOption4(backend_selector, server_selector, code, space,
                              client_classes));
    };
    delGlobalOption(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::getGlobalOption4(CalloutHandle& callout_handle) {
    auto get_fun  = [] (const BackendSelector& backend_selector,
                        const ServerSelector& server_selector,
                        const uint16_t code,
                        const std::string& space,
                        const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getOption4(backend_selector, server_selector, code, space,
                           client_classes));
    };
    getGlobalOption(callout_handle, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::getAllGlobalOptions4(CalloutHandle& callout_handle) {
    auto get_all_fun  = [] (const BackendSelector& backend_selector,
                            const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllOptions4(backend_selector, server_selector));
    };
    getAllGlobalOptions(callout_handle, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setServer4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerPtr& server) {
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateServer4(backend_selector, server);
    };
    setServer(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delServer4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerTag& server_tag) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteServer4(backend_selector, server_tag));
    };
    delServer(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::getServer4(CalloutHandle& callout_handle) {
    auto get_fun  = [] (const BackendSelector& backend_selector,
                        const ServerTag& server_tag) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getServer4(backend_selector, server_tag));
    };
    getServer(callout_handle, AF_INET, get_fun);
}

void
ConfigCmdsDhcp4Impl::getAllServers4(CalloutHandle& callout_handle) {
    auto get_all_fun  = [] (const BackendSelector& backend_selector) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                getAllServers4(backend_selector));
    };
    getAllServers(callout_handle, AF_INET, get_all_fun);
}

void
ConfigCmdsDhcp4Impl::setSharedNetworkOption4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const std::string& shared_network_name,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateOption4(backend_selector, server_selector,
                                shared_network_name, option);
    };
    setSharedNetworkOption(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delSharedNetworkOption4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& shared_network_name,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteOption4(backend_selector, server_selector,
                              shared_network_name, code, space, client_classes));
    };
    delSharedNetworkOption(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::setSubnetOption4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const SubnetID& subnet_id,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateOption4(backend_selector, server_selector,
                                subnet_id, option);
    };
    setSubnetOption(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delSubnetOption4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const SubnetID& subnet_id,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteOption4(backend_selector, server_selector,
                              subnet_id, code, space, client_classes));
    };
    delSubnetOption(callout_handle, AF_INET, delete_fun);
}

void
ConfigCmdsDhcp4Impl::setPoolOption4(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const asiolink::IOAddress& pool_start_address,
                                 const asiolink::IOAddress& pool_end_address,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv4Mgr::instance().getPool()->
            createUpdateOption4(backend_selector, server_selector,
                                pool_start_address, pool_end_address,
                                option);
    };
    setPoolOption(callout_handle, AF_INET, create_update_fun);
}

void
ConfigCmdsDhcp4Impl::delPoolOption4(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const asiolink::IOAddress& pool_start_address,
                          const asiolink::IOAddress& pool_end_address,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv4Mgr::instance().getPool()->
                deleteOption4(backend_selector, server_selector,
                              pool_start_address, pool_end_address,
                              code, space, client_classes));
    };
    delPoolOption(callout_handle, AF_INET, delete_fun);
}

} // end of namespace isc::cb
} // end of namespace isc
