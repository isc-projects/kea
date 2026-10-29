// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <hooks/hooks.h>

#include <functional>

#include <cb_cmds/cb_cmds_dhcp6.h>
#include <cb_cmds/cb_parsers.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::db;
using namespace isc::hooks;

namespace isc {
namespace cb {

const SimpleKeywords ConfigCmdsDhcp6Impl::GLOBAL6_MAP_PARAMETERS = {
    { "compatibility.lenient-option-parsing", Element::boolean },
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
    { "server-id.type", Element::string },
    { "server-id.enterprise-id", Element::integer },
    { "server-id.identifier", Element::string },
    { "server-id.persist", Element::boolean },
    { "dhcp-queue-control.enable-queue", Element::boolean },
    { "dhcp-queue-control.queue-type", Element::string },
    { "dhcp-queue-control.capacity", Element::integer },
    /* not yet supported
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
ConfigCmdsDhcp6Impl::initGlobalContainersParameters() {
    SimpleKeywords globals = SimpleParser6::GLOBAL6_PARAMETERS;
    // Add supported top level map parameters.
    globals.insert(ConfigCmdsDhcp6Impl::GLOBAL6_MAP_PARAMETERS.begin(),
                   ConfigCmdsDhcp6Impl::GLOBAL6_MAP_PARAMETERS.end());
    // Remove unsupported top level list parameters.
    auto globals_copy = globals;
    for (auto const& key : globals_copy) {
        if (key.second == Element::list &&
            SimpleParser6::GLOBAL6_LIST_PARAMETERS.find(key.first) ==
            SimpleParser6::GLOBAL6_LIST_PARAMETERS.end()) {
            globals.erase(key.first);
        }
    }

    return (globals);
}

SimpleKeywords&
ConfigCmdsDhcp6Impl::getGlobalContainersParameters() {
    static SimpleKeywords parameters = ConfigCmdsDhcp6Impl::initGlobalContainersParameters();
    return (parameters);
}

void
ConfigCmdsDhcp6Impl::setGlobalParameter6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const StampedValuePtr& stamped_value) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
        createUpdateGlobalParameter6(backend_selector, server_selector,
                                     stamped_value);
    };
    auto const& globals = ConfigCmdsDhcp6Impl::getGlobalContainersParameters();
    setGlobalParameter(callout_handle, globals, SimpleParser6::GLOBAL6_LIST_PARAMETER_TYPES, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delGlobalParameter6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteGlobalParameter6(backend_selector, server_selector, name));
    };
    auto const& globals = ConfigCmdsDhcp6Impl::getGlobalContainersParameters();
    delGlobalParameter(callout_handle, globals, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::getGlobalParameter6(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getGlobalParameter6(backend_selector, server_selector, name));
    };
    auto const& globals = ConfigCmdsDhcp6Impl::getGlobalContainersParameters();
    getGlobalParameter(callout_handle, globals, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::getAllGlobalParameters6(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllGlobalParameters6(backend_selector, server_selector));
    };
    auto const& globals = ConfigCmdsDhcp6Impl::getGlobalContainersParameters();
    getAllGlobalParameters(callout_handle, globals, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setSubnet6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const Subnet6Ptr& subnet) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
        createUpdateSubnet6(backend_selector, server_selector, subnet);
    };
    setSubnet<Subnet6Ptr, CBSubnet6ConfigParser>(callout_handle,
                                                 AF_INET6,
                                                 create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delSubnet6Id(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const SubnetID& subnet_id) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteSubnet6(backend_selector, server_selector, subnet_id));
    };
    delSubnetId(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::delSubnet6Prefix(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& subnet_prefix) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteSubnet6(backend_selector, server_selector, subnet_prefix));
    };
    delSubnetPrefix(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::getSubnet6Id(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const SubnetID& subnet_id) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getSubnet6(backend_selector, server_selector, subnet_id));
    };
    getSubnetId<Subnet6Ptr>(callout_handle, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::getSubnet6Prefix(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& subnet_prefix) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getSubnet6(backend_selector, server_selector, subnet_prefix));
    };
    getSubnetPrefix<Subnet6Ptr>(callout_handle, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::listSubnets6(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllSubnets6(backend_selector, server_selector));
    };
    listSubnets<Subnet6Collection>(callout_handle, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setSharedNetwork6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const SharedNetwork6Ptr& shared_network) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
        createUpdateSharedNetwork6(backend_selector, server_selector, shared_network);
    };
    setSharedNetwork<SharedNetwork6Ptr, CBSharedNetwork6Parser>
        (callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delSharedNetwork6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteSharedNetwork6(backend_selector, server_selector, name));
    };
    auto delete_all_fun = [] (const BackendSelector& backend_selector,
                              const ServerSelector& server_selector,
                              const std::string& name) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
        deleteSharedNetworkSubnets6(backend_selector, server_selector, name);
    };
    delSharedNetwork(callout_handle, AF_INET6, delete_fun, delete_all_fun);
}

void
ConfigCmdsDhcp6Impl::getSharedNetwork6(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getSharedNetwork6(backend_selector, server_selector, name));

    };
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector,
                           const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getSharedNetworkSubnets6(backend_selector, server_selector, name));
    };
    getSharedNetwork<SharedNetwork6Ptr, Subnet6Collection>
        (callout_handle, AF_INET6, get_fun, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::listSharedNetworks6(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllSharedNetworks6(backend_selector, server_selector));
    };
    listSharedNetworks<SharedNetwork6Collection>
        (callout_handle, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setClientClass6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const ClientClassDefPtr& client_class,
                                 const std::string& follow_class_name) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
        createUpdateClientClass6(backend_selector, server_selector, client_class,
                                 follow_class_name);
    };
    setClientClass(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delClientClass6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteClientClass6(backend_selector, server_selector, name));
    };
    delClientClass(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::getClientClass6(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const std::string& name) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getClientClass6(backend_selector, server_selector, name));

    };
    getClientClass(callout_handle, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::getAllClientClasses6(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllClientClasses6(backend_selector, server_selector));
    };
    getAllClientClasses(callout_handle, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setOptionDef6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const OptionDefinitionPtr& option_def) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
        createUpdateOptionDef6(backend_selector, server_selector, option_def);
    };
    setOptionDef(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delOptionDef6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const uint16_t code,
                          const std::string& space,
                          bool force) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteOptionDef6(backend_selector, server_selector,
                                 code, space, force));
    };
    delOptionDef(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::getOptionDef6(CalloutHandle& callout_handle) {
    auto get_fun = [] (const BackendSelector& backend_selector,
                       const ServerSelector& server_selector,
                       const uint16_t code,
                       const std::string& space) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getOptionDef6(backend_selector, server_selector,
                              code, space));
    };
    getOptionDef(callout_handle, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::getAllOptionDefs6(CalloutHandle& callout_handle) {
    auto get_all_fun = [] (const BackendSelector& backend_selector,
                           const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllOptionDefs6(backend_selector, server_selector));

    };
    getAllOptionDefs(callout_handle, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setGlobalOption6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateOption6(backend_selector, server_selector, option);
    };
    setGlobalOption(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delGlobalOption6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteOption6(backend_selector, server_selector, code,
                              space, client_classes));
    };
    delGlobalOption(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::getGlobalOption6(CalloutHandle& callout_handle) {
    auto get_fun  = [] (const BackendSelector& backend_selector,
                        const ServerSelector& server_selector,
                        const uint16_t code,
                        const std::string& space,
                        const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getOption6(backend_selector, server_selector, code,
                           space, client_classes));
    };
    getGlobalOption(callout_handle, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::getAllGlobalOptions6(CalloutHandle& callout_handle) {
    auto get_all_fun  = [] (const BackendSelector& backend_selector,
                            const ServerSelector& server_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllOptions6(backend_selector, server_selector));
    };
    getAllGlobalOptions(callout_handle, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setServer6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerPtr& server) {
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateServer6(backend_selector, server);
    };
    setServer(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delServer6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerTag& server_tag) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteServer6(backend_selector, server_tag));
    };
    delServer(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::getServer6(CalloutHandle& callout_handle) {
    auto get_fun  = [] (const BackendSelector& backend_selector,
                        const ServerTag& server_tag) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getServer6(backend_selector, server_tag));
    };
    getServer(callout_handle, AF_INET6, get_fun);
}

void
ConfigCmdsDhcp6Impl::getAllServers6(CalloutHandle& callout_handle) {
    auto get_all_fun  = [] (const BackendSelector& backend_selector) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                getAllServers6(backend_selector));
    };
    getAllServers(callout_handle, AF_INET6, get_all_fun);
}

void
ConfigCmdsDhcp6Impl::setSharedNetworkOption6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const std::string& shared_network_name,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateOption6(backend_selector, server_selector,
                                shared_network_name, option);
    };
    setSharedNetworkOption(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delSharedNetworkOption6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const std::string& shared_network_name,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteOption6(backend_selector, server_selector,
                              shared_network_name, code, space, client_classes));
    };
    delSharedNetworkOption(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::setSubnetOption6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const SubnetID& subnet_id,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateOption6(backend_selector, server_selector,
                                subnet_id, option);
    };
    setSubnetOption(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delSubnetOption6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const SubnetID& subnet_id,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteOption6(backend_selector, server_selector,
                              subnet_id, code, space, client_classes));
    };
    delSubnetOption(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::setPoolOption6(CalloutHandle& callout_handle) {
    auto create_update_fun = [] (const BackendSelector& backend_selector,
                                 const ServerSelector& server_selector,
                                 const asiolink::IOAddress& pool_start_address,
                                 const asiolink::IOAddress& pool_end_address,
                                 OptionDescriptor option_descriptor) {
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateOption6(backend_selector, server_selector,
                                pool_start_address, pool_end_address,
                                option);
    };
    setPoolOption(callout_handle, AF_INET6, create_update_fun);
}

void
ConfigCmdsDhcp6Impl::delPoolOption6(CalloutHandle& callout_handle) {
    auto delete_fun = [] (const BackendSelector& backend_selector,
                          const ServerSelector& server_selector,
                          const asiolink::IOAddress& pool_start_address,
                          const asiolink::IOAddress& pool_end_address,
                          const uint16_t code,
                          const std::string& space,
                          const ClientClassesPtr client_classes) {
        return (ConfigBackendDHCPv6Mgr::instance().getPool()->
                deleteOption6(backend_selector, server_selector,
                              pool_start_address, pool_end_address,
                              code, space, client_classes));
    };
    delPoolOption(callout_handle, AF_INET6, delete_fun);
}

void
ConfigCmdsDhcp6Impl::setPdPoolOption6(CalloutHandle& callout_handle) {
    try {
        // Parse the command and store the pd pool prefix.
        std::pair<asiolink::IOAddress, uint8_t> pd_pool_prefix =
            std::make_pair(asiolink::IOAddress::IPV6_ZERO_ADDRESS(), 128);
        db::BackendSelector backend_selector;
        db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
        parser_->parseInputListElement<CBPdPoolPrefixParser>
            (callout_handle, "pd-pools", pd_pool_prefix,
             backend_selector, server_selector,
             ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

        // Parse again the command and store the option data in
        // the option_pair object.
        std::pair<dhcp::OptionDescriptor, std::string> option_pair =
            std::make_pair(dhcp::OptionDescriptor(false, false), "");
        parser_->parseInputListElement
            <dhcp::OptionDataParser, uint16_t, dhcp::CfgOptionDefPtr>
            (callout_handle, "options", AF_INET6,
             dhcp::CfgMgr::instance().getCurrentCfg()->getCfgOptionDef(),
             option_pair);

        auto option_descriptor = option_pair.first;
        option_descriptor.space_name_ = option_pair.second;

        // Pass the received arguments into the configuration backend.
        const OptionDescriptorPtr& option =
            OptionDescriptorPtr(new OptionDescriptor(option_descriptor));
        ConfigBackendDHCPv6Mgr::instance().getPool()->
            createUpdateOption6(backend_selector, server_selector,
                                pd_pool_prefix.first, pd_pool_prefix.second,
                                option);

        // The response contains option code and space.
        data::ElementPtr option_info = data::Element::createMap();
        option_info->set("code",
                         data::Element::create(static_cast<int64_t>
                            (option_descriptor.option_->getType())));
        option_info->set("space",
                         data::Element::create(option_descriptor.space_name_));

        // The option information is encapsulated in a single element list.
        data::ElementPtr response_list = data::Element::createList();
        response_list->add(option_info);

        data::ElementPtr response_arguments = data::Element::createMap();
        response_arguments->set("options", response_list);

        // Configuration backend didn't complain so let's return the success status.
        std::ostringstream msg;
        msg << "DHCPv6 option successfully set.";
        data::ConstElementPtr response =
            config::createAnswer(config::CONTROL_RESULT_SUCCESS,
                                 msg.str(), response_arguments);
        callout_handle.setArgument("response", response);

    } catch (const std::exception& ex) {
        // Something went wrong. Return an error response to the client.
        data::ConstElementPtr response =
            config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
    }
}

void
ConfigCmdsDhcp6Impl::delPdPoolOption6(CalloutHandle& callout_handle) {
    try {
        // Parse the command and store the pd pool prefix.
        std::pair<asiolink::IOAddress, uint8_t> pd_pool_prefix =
            std::make_pair(asiolink::IOAddress::IPV6_ZERO_ADDRESS(), 128);
        db::BackendSelector backend_selector;
        db::ServerSelector server_selector = db::ServerSelector::UNASSIGNED();
        parser_->parseInputListElement<CBPdPoolPrefixParser>
            (callout_handle, "pd-pools", pd_pool_prefix,
             backend_selector, server_selector,
             ConfigCmdsParser::ServerTagsParse::TAGS_FORBIDDEN);

        // Parse again the command and store the option code/space/client classes tuple.
        CBOptionTuple option_tuple;
        parser_->parseInputListElement<CBOptionTupleParser, uint16_t>
            (callout_handle, "options", AF_INET6, option_tuple);

        // Pass the received arguments into the configuration backend.
        uint64_t count = ConfigBackendDHCPv6Mgr::instance().getPool()->
            deleteOption6(backend_selector, server_selector,
                          pd_pool_prefix.first, pd_pool_prefix.second,
                          std::get<0>(option_tuple),
                          std::get<1>(option_tuple),
                          std::get<2>(option_tuple));

        data::ElementPtr response_arguments = data::Element::createMap();
        response_arguments->set("count",
                                data::Element::create(static_cast<long int>(count)));

        // Configuration backend didn't complain so let's return the success status.
        std::ostringstream msg;
        msg << count << " DHCPv6 option(s) deleted.";
        int rcode =
            (count == 0 ? config::CONTROL_RESULT_EMPTY : config::CONTROL_RESULT_SUCCESS);
        data::ConstElementPtr response =
            config::createAnswer(rcode, msg.str(), response_arguments);
        callout_handle.setArgument("response", response);

    } catch (const std::exception& ex) {
        // Something went wrong. Return an error response to the client.
        data::ConstElementPtr response =
            config::createAnswer(config::CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
    }
}

} // end of namespace isc::cb
} // end of namespace isc
