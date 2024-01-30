// Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cb_ctl_dhcp6.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <boost/foreach.hpp>

using namespace isc::db;
using namespace isc::data;
using namespace isc::process;
using namespace isc::hooks;

namespace {

/// Structure that holds registered hook indexes.
struct CbCtlHooks {
    int hook_index_cb6_updated_; ///< index for "cb6_updated" hook point.

    /// Constructor that registers hook points for CBControlDHCPv6.
    CbCtlHooks() {
        hook_index_cb6_updated_ = HooksManager::registerHook("cb6_updated");
    }
};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
CbCtlHooks hooks_;

}; // anonymous namespace

namespace isc {
namespace dhcp {

void
CBControlDHCPv6::databaseConfigApply(const db::BackendSelector& backend_selector,
                                     const db::ServerSelector& server_selector,
                                     const boost::posix_time::ptime& lb_modification_time,
                                     const db::AuditEntryCollection& audit_entries) {
    bool globals_fetched = false;
    auto reconfig = audit_entries.empty();
    auto cb_update = !reconfig;
    auto current_cfg = CfgMgr::instance().getCurrentCfg();
    auto staging_cfg = CfgMgr::instance().getStagingCfg();

    // Let's first delete all the configuration elements for which DELETE audit
    // entries are found. Although, this may break chronology of the audit in
    // some cases it should not affect the end result of the data fetch. If the
    // object was created and then subsequently deleted, we will first try to
    // delete this object from the local configuration (which will fail because
    // the object does not exist) and then we will try to fetch it from the
    // database which will return no result.
    if (cb_update) {

        auto external_cfg = CfgMgr::instance().createExternalCfg();

        // Get audit entries for deleted global parameters.
        auto const& index = audit_entries.get<AuditEntryObjectTypeTag>();
        auto range = index.equal_range(boost::make_tuple("dhcp6_global_parameter",
                                                         AuditEntry::ModificationType::DELETE));
        if (range.first != range.second) {
            // Some globals have been deleted. Since we currently don't track database
            // identifiers of the global parameters we have to fetch all global
            // parameters for this server. Next, we simply replace existing
            // global parameters with the new parameters. This is slightly
            // inefficient but only slightly. Note that this is a single
            // database query and the number of global parameters is small.
            data::StampedValueCollection globals;
            globals = getMgr().getPool()->getAllGlobalParameters6(backend_selector, server_selector);
            translateAndAddGlobalsToConfig(external_cfg, globals);

            // Add defaults.
            external_cfg->applyDefaultsConfiguredGlobals(SimpleParser6::GLOBAL6_DEFAULTS);

            // Sanity check it.
            external_cfg->sanityChecksLifetime("preferred-lifetime");
            external_cfg->sanityChecksLifetime("valid-lifetime");

            // Now that we successfully fetched the new global parameters, let's
            // remove existing ones and merge them into the current configuration.
            current_cfg->clearConfiguredGlobals();
            CfgMgr::instance().mergeIntoCurrentCfg(external_cfg->getSequence());
            globals_fetched = true;
        }

        try {
            // Get audit entries for deleted option definitions and delete each
            // option definition from the current configuration for which the
            // audit entry is found.
            range = index.equal_range(boost::make_tuple("dhcp6_option_def",
                                                        AuditEntry::ModificationType::DELETE));
            BOOST_FOREACH(auto const& entry, range) {
                current_cfg->getCfgOptionDef()->del(entry->getObjectId());
            }

            // Repeat the same for other configuration elements.

            range = index.equal_range(boost::make_tuple("dhcp6_options",
                                                        AuditEntry::ModificationType::DELETE));
            BOOST_FOREACH(auto const& entry, range) {
                current_cfg->getCfgOption()->del(entry->getObjectId());
            }

            range = index.equal_range(boost::make_tuple("dhcp6_client_class",
                                                        AuditEntry::ModificationType::DELETE));
            BOOST_FOREACH(auto const& entry, range) {
                current_cfg->getClientClassDictionary()->removeClass(entry->getObjectId());
            }

            range = index.equal_range(boost::make_tuple("dhcp6_shared_network",
                                                        AuditEntry::ModificationType::DELETE));
            BOOST_FOREACH(auto const& entry, range) {
                current_cfg->getCfgSharedNetworks6()->del(entry->getObjectId());
            }

            range = index.equal_range(boost::make_tuple("dhcp6_subnet",
                                                        AuditEntry::ModificationType::DELETE));
            BOOST_FOREACH(auto const& entry, range) {
                // If the deleted subnet belongs to a shared network and the
                // shared network is not being removed, we need to detach the
                // subnet from the shared network.
                auto subnet = current_cfg->getCfgSubnets6()->getBySubnetId(entry->getObjectId());
                if (subnet) {
                    // Check if the subnet belongs to a shared network.
                    SharedNetwork6Ptr network;
                    subnet->getSharedNetwork(network);
                    if (network) {
                        // Detach the subnet from the shared network.
                        network->del(subnet->getID());
                    }
                    // Actually delete the subnet from the configuration.
                    current_cfg->getCfgSubnets6()->del(entry->getObjectId());
                }
            }

        } catch (...) {
            // Ignore errors thrown when attempting to delete a non-existing
            // configuration entry. There is no guarantee that the deleted
            // entry is actually there as we're not processing the audit
            // chronologically.
        }
    }

    // Create the external config into which we'll fetch backend config data.
    SrvConfigPtr external_cfg = CfgMgr::instance().createExternalCfg();

    // First let's fetch the globals and add them to external config.
    AuditEntryCollection updated_entries;
    if (!globals_fetched) {
        if (cb_update) {
            updated_entries = fetchConfigElement(audit_entries, "dhcp6_global_parameter");
        }
        if (reconfig || !updated_entries.empty()) {
            data::StampedValueCollection globals;
            globals = getMgr().getPool()->getModifiedGlobalParameters6(backend_selector, server_selector,
                                                                       lb_modification_time);
            translateAndAddGlobalsToConfig(external_cfg, globals);
            globals_fetched = true;
        }
    }

    // Now we fetch the option definitions and add them.
    if (cb_update) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp6_option_def");
    }
    if (reconfig || !updated_entries.empty()) {
        OptionDefContainer option_defs =
            getMgr().getPool()->getModifiedOptionDefs6(backend_selector, server_selector,
                                                       lb_modification_time);
        for (auto const& option_def : option_defs) {
            if (!audit_entries.empty() && !hasObjectId(updated_entries, option_def->getId())) {
                continue;
            }
            external_cfg->getCfgOptionDef()->add(option_def);
        }
    }

    // Next fetch the options. They are returned as a container of OptionDescriptors.
    if (cb_update) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp6_options");
    }
    if (reconfig || !updated_entries.empty()) {
        OptionContainer options = getMgr().getPool()->getModifiedOptions6(backend_selector,
                                                                          server_selector,
                                                                          lb_modification_time);
        for (auto const& option : options) {
            if (!audit_entries.empty() && !hasObjectId(updated_entries, option.getId())) {
                continue;
            }
            external_cfg->getCfgOption()->add(option, option.space_name_);
        }
    }

    // Fetch client classes. They are returned in a ClientClassDictionary.
    if (cb_update) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp6_client_class");
    }
    if (reconfig || !updated_entries.empty()) {
        ClientClassDictionary client_classes = getMgr().getPool()->getAllClientClasses6(backend_selector,
                                                                                        server_selector);
        // Match expressions are not initialized for classes returned from the config backend.
        // We have to ensure to initialize them before they can be used by the server.
        client_classes.initMatchExpr(AF_INET6);

        // Class options also need to be created when returned from the config backend.
        client_classes.createOptions(external_cfg->getCfgOptionDef());

        external_cfg->setClientClassDictionary(boost::make_shared<ClientClassDictionary>(client_classes));
    }

    // Allocator selection at the global level can affect subnets and shared networks
    // for which the allocator hasn't been specified explicitly. Let's see if the
    // allocator has been specified at the global level.
    std::string global_allocator;
    auto allocator = external_cfg->getConfiguredGlobal(CfgGlobals::ALLOCATOR);
    if (allocator && (allocator->getType() == Element::string)) {
        global_allocator = allocator->stringValue();
    }

    // Also, get the PD allocator.
    std::string global_pd_allocator;
    allocator = external_cfg->getConfiguredGlobal(CfgGlobals::PD_ALLOCATOR);
    if (allocator && (allocator->getType() == Element::string)) {
        global_pd_allocator = allocator->stringValue();
    }

    // If we're fetching the changes from the config backend we also want
    // to see if the global allocator has changed. Let's get the currently
    // used allocator too.
    auto allocator_changed = false;
    // We're only affected by the allocator change if this is the update from
    // the configuration backend.
    if (cb_update) {
        auto allocator = CfgMgr::instance().getCurrentCfg()->getConfiguredGlobal(CfgGlobals::ALLOCATOR);
        if (allocator && (allocator->getType() == Element::string)) {
            allocator_changed = (global_allocator != allocator->stringValue());
        }

        // The address allocator hasn't changed. So, let's check if the PD allocator
        // has changed.
        if (!allocator_changed) {
            auto allocator = CfgMgr::instance().getCurrentCfg()->getConfiguredGlobal(CfgGlobals::PD_ALLOCATOR);
            if (allocator && (allocator->getType() == Element::string)) {
                allocator_changed = (global_pd_allocator != allocator->stringValue());
            }
        }
    }

    // Now fetch the shared networks.
    if (cb_update) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp6_shared_network");
    }
    SharedNetwork6Collection networks;
    if (allocator_changed || reconfig) {
        // A change of the allocator or the server reconfiguration can affect all
        // shared networks. Get all shared networks.
        networks = getMgr().getPool()->getAllSharedNetworks6(backend_selector, server_selector);
    } else if (!updated_entries.empty()) {
        networks = getMgr().getPool()->getModifiedSharedNetworks6(backend_selector, server_selector,
                                                                  lb_modification_time);
    }
    for (auto const& network : networks) {
        if (!allocator_changed && cb_update && !hasObjectId(updated_entries, network->getId())) {
            continue;
        }
        // In order to take advantage of the dynamic inheritance of global
        // parameters to a shared network we need to set a callback function
        // for each network to allow for fetching global parameters.
        network->setFetchGlobalsFn([] () -> ConstCfgGlobalsPtr {
            return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
        });
        network->setDefaultAllocatorType(global_allocator);
        network->setDefaultPdAllocatorType(global_pd_allocator);
        external_cfg->getCfgSharedNetworks6()->add(network);
    }

    // Next we fetch subnets.
    if (cb_update) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp6_subnet");
    }
    Subnet6Collection subnets;
    if (allocator_changed || reconfig) {
        // A change of the allocator or the server reconfiguration can affect all
        // subnets. Get all subnets.
        subnets = getMgr().getPool()->getAllSubnets6(backend_selector, server_selector);

    } else if (!updated_entries.empty()) {
        // An update from the config backend when the global allocator hasn't changed
        // means that we only need to handle the modified subnets.
        subnets = getMgr().getPool()->getModifiedSubnets6(backend_selector,
                                                          server_selector,
                                                          lb_modification_time);
    }
    // Iterate over all subnets that may require reconfiguration.
    for (auto const& subnet : subnets) {
        if (!audit_entries.empty() && !hasObjectId(updated_entries, subnet->getID())) {
            continue;
        }
        // In order to take advantage of the dynamic inheritance of global
        // parameters to a subnet we need to set a callback function for each
        // subnet to allow for fetching global parameters.
        subnet->setFetchGlobalsFn([] () -> ConstCfgGlobalsPtr {
            return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
        });
        subnet->setDefaultAllocatorType(global_allocator);
        subnet->setDefaultPdAllocatorType(global_pd_allocator);
        external_cfg->getCfgSubnets6()->add(subnet);
    }

    if (reconfig) {
        // If we're configuring the server after startup, we do not apply the
        // ip-reservations-unique setting here. It will be applied when the
        // configuration is committed.
        auto const& cfg = CfgMgr::instance().getStagingCfg();
        external_cfg->sanityChecksLifetime(*cfg, "preferred-lifetime");
        external_cfg->sanityChecksLifetime(*cfg, "valid-lifetime");
        CfgMgr::instance().mergeIntoStagingCfg(external_cfg->getSequence());

    } else {
        if (globals_fetched) {
            // ip-reservations-unique parameter requires special handling because
            // setting it to false may be unsupported by some host backends.
            bool ip_unique = true;
            auto ip_unique_param = external_cfg->getConfiguredGlobal("ip-reservations-unique");
            if (ip_unique_param && (ip_unique_param->getType() == Element::boolean)) {
                ip_unique = ip_unique_param->boolValue();
            }
            // First try to use the new setting to configure the HostMgr because it
            // may fail if the backend does not support it.
            if (!HostMgr::instance().setIPReservationsUnique(ip_unique)) {
                // The new setting is unsupported by the backend, so do not apply this
                // setting at all.
                LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_IPV6_RESERVATIONS_NON_UNIQUE_IGNORED);
                external_cfg->addConfiguredGlobal("ip-reservations-unique", Element::create(true));
            }
        }
        auto const& cfg = CfgMgr::instance().getCurrentCfg();
        external_cfg->sanityChecksLifetime(*cfg, "preferred-lifetime");
        external_cfg->sanityChecksLifetime(*cfg, "valid-lifetime");
        CfgMgr::instance().mergeIntoCurrentCfg(external_cfg->getSequence());
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->initAllocatorsAfterConfigure();
    }
    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_CONFIG6_MERGED);

    if (cb_update &&
        HooksManager::calloutsPresent(hooks_.hook_index_cb6_updated_)) {
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass a shared pointer to audit entries.
        AuditEntryCollectionPtr ptr(new AuditEntryCollection(audit_entries));
        callout_handle->setArgument("audit_entries", ptr);

        // Call the callouts
        HooksManager::callCallouts(hooks_.hook_index_cb6_updated_, *callout_handle);

        // Ignore the result.
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
