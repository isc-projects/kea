// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>

using namespace isc::db;
using namespace isc::data;
using namespace isc::process;
using namespace isc::hooks;

namespace {

/// Structure that holds registered hook indexes.
struct CbCtlHooks {
    int hook_index_cb4_updated_; ///< index for "cb4_updated" hook point.

    /// Constructor that registers hook points for CBControlDHCPv4.
    CbCtlHooks() {
        hook_index_cb4_updated_ = HooksManager::registerHook("cb4_updated");
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
CBControlDHCPv4::databaseConfigApply(const BackendSelector& backend_selector,
                                     const ServerSelector& server_selector,
                                     const boost::posix_time::ptime& lb_modification_time,
                                     const AuditEntryCollection& audit_entries) {

    bool globals_fetched = false;

    // Let's first delete all the configuration elements for which DELETE audit
    // entries are found. Although, this may break chronology of the audit in
    // some cases it should not affect the end result of the data fetch. If the
    // object was created and then subsequently deleted, we will first try to
    // delete this object from the local configuration (which will fail because
    // the object does not exist) and then we will try to fetch it from the
    // database which will return no result.
    if (!audit_entries.empty()) {

        auto cfg = CfgMgr::instance().getCurrentCfg();
        auto external_cfg = CfgMgr::instance().createExternalCfg();

        // Get audit entries for deleted global parameters.
        const auto& index = audit_entries.get<AuditEntryObjectTypeTag>();
        auto range = index.equal_range(boost::make_tuple("dhcp4_global_parameter",
                                                         AuditEntry::ModificationType::DELETE));
        if (range.first != range.second) {
            // Some globals have been deleted. Since we currently don't track database
            // identifiers of the global parameters we have to fetch all global
            // parameters for this server. Next, we simply replace existing
            // global parameters with the new parameters. This is slightly
            // inefficient but only slightly. Note that this is a single
            // database query and the number of global parameters is small.
            data::StampedValueCollection globals;
            globals = getMgr().getPool()->getAllGlobalParameters4(backend_selector, server_selector);
            addGlobalsToConfig(external_cfg, globals);

            // Add defaults.
            external_cfg->applyDefaultsConfiguredGlobals(SimpleParser4::GLOBAL4_DEFAULTS);

            // Sanity check it.
            external_cfg->sanityChecksLifetime("valid-lifetime");

            // Now that we successfully fetched the new global parameters, let's
            // remove existing ones and merge them into the current configuration.
            cfg->clearConfiguredGlobals();
            CfgMgr::instance().mergeIntoCurrentCfg(external_cfg->getSequence());
            globals_fetched = true;
        }

        try {
            // Get audit entries for deleted option definitions and delete each
            // option definition from the current configuration for which the
            // audit entry is found.
            range = index.equal_range(boost::make_tuple("dhcp4_option_def",
                                                        AuditEntry::ModificationType::DELETE));
            for (auto entry = range.first; entry != range.second; ++entry) {
                cfg->getCfgOptionDef()->del((*entry)->getObjectId());
            }

            // Repeat the same for other configuration elements.

            range = index.equal_range(boost::make_tuple("dhcp4_options",
                                                        AuditEntry::ModificationType::DELETE));
            for (auto entry = range.first; entry != range.second; ++entry) {
                cfg->getCfgOption()->del((*entry)->getObjectId());
            }

            range = index.equal_range(boost::make_tuple("dhcp4_client_class",
                                                        AuditEntry::ModificationType::DELETE));
            for (auto entry = range.first; entry != range.second; ++entry) {
                cfg->getClientClassDictionary()->removeClass((*entry)->getObjectId());
            }

            range = index.equal_range(boost::make_tuple("dhcp4_shared_network",
                                                        AuditEntry::ModificationType::DELETE));
            for (auto entry = range.first; entry != range.second; ++entry) {
                cfg->getCfgSharedNetworks4()->del((*entry)->getObjectId());
            }

            range = index.equal_range(boost::make_tuple("dhcp4_subnet",
                                                        AuditEntry::ModificationType::DELETE));
            for (auto entry = range.first; entry != range.second; ++entry) {
                // If the deleted subnet belongs to a shared network and the
                // shared network is not being removed, we need to detach the
                // subnet from the shared network.
                auto subnet = cfg->getCfgSubnets4()->getBySubnetId((*entry)->getObjectId());
                if (subnet) {
                    // Check if the subnet belongs to a shared network.
                    SharedNetwork4Ptr network;
                    subnet->getSharedNetwork(network);
                    if (network) {
                        // Detach the subnet from the shared network.
                        network->del(subnet->getID());
                    }
                    // Actually delete the subnet from the configuration.
                    cfg->getCfgSubnets4()->del((*entry)->getObjectId());
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
    if (!globals_fetched && !audit_entries.empty()) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp4_global_parameter");
    }
    if (!globals_fetched && (audit_entries.empty() || !updated_entries.empty())) {
        data::StampedValueCollection globals;
        globals = getMgr().getPool()->getModifiedGlobalParameters4(backend_selector, server_selector,
                                                                   lb_modification_time);
        addGlobalsToConfig(external_cfg, globals);
        globals_fetched = true;
    }

    // Now we fetch the option definitions and add them.
    if (!audit_entries.empty()) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp4_option_def");
    }
    if (audit_entries.empty() || !updated_entries.empty()) {
        OptionDefContainer option_defs =
            getMgr().getPool()->getModifiedOptionDefs4(backend_selector, server_selector,
                                                       lb_modification_time);
        for (auto option_def = option_defs.begin(); option_def != option_defs.end(); ++option_def) {
            if (!audit_entries.empty() && !hasObjectId(updated_entries, (*option_def)->getId())) {
                continue;
            }
            external_cfg->getCfgOptionDef()->add(*option_def);
        }
    }

    // Next fetch the options. They are returned as a container of OptionDescriptors.
    if (!audit_entries.empty()) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp4_options");
    }
    if (audit_entries.empty() || !updated_entries.empty()) {
        OptionContainer options = getMgr().getPool()->getModifiedOptions4(backend_selector,
                                                                          server_selector,
                                                                          lb_modification_time);
        for (auto option = options.begin(); option != options.end(); ++option) {
            if (!audit_entries.empty() && !hasObjectId(updated_entries, (*option).getId())) {
                continue;
            }
            external_cfg->getCfgOption()->add((*option), (*option).space_name_);
        }
    }

    // Fetch client classes. They are returned in a ClientClassDictionary.
    if (!audit_entries.empty()) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp4_client_class");
    }
    if (audit_entries.empty() || !updated_entries.empty()) {
        ClientClassDictionary client_classes = getMgr().getPool()->getAllClientClasses4(backend_selector,
                                                                                        server_selector);
        // Match expressions are not initialized for classes returned from the config backend.
        // We have to ensure to initialize them before they can be used by the server.
        client_classes.initMatchExpr(AF_INET);
        external_cfg->setClientClassDictionary(boost::make_shared<ClientClassDictionary>(client_classes));
    }

    // Now fetch the shared networks.
    if (!audit_entries.empty()) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp4_shared_network");
    }
    if (audit_entries.empty() || !updated_entries.empty()) {
        SharedNetwork4Collection networks =
            getMgr().getPool()->getModifiedSharedNetworks4(backend_selector, server_selector,
                                                           lb_modification_time);
        for (auto network = networks.begin(); network != networks.end(); ++network) {
            if (!audit_entries.empty() && !hasObjectId(updated_entries, (*network)->getId())) {
                continue;
            }
            // In order to take advantage of the dynamic inheritance of global
            // parameters to a shared network we need to set a callback function
            // for each network to allow for fetching global parameters.
            (*network)->setFetchGlobalsFn([] () -> ConstElementPtr {
                return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
            });
            external_cfg->getCfgSharedNetworks4()->add((*network));
        }
    }

    // Next we fetch subnets.
    if (!audit_entries.empty()) {
        updated_entries = fetchConfigElement(audit_entries, "dhcp4_subnet");
    }
    if (audit_entries.empty() || !updated_entries.empty()) {
        Subnet4Collection subnets = getMgr().getPool()->getModifiedSubnets4(backend_selector,
                                                                            server_selector,
                                                                            lb_modification_time);
        for (auto subnet = subnets.begin(); subnet != subnets.end(); ++subnet) {
            if (!audit_entries.empty() && !hasObjectId(updated_entries, (*subnet)->getID())) {
                continue;
            }
            // In order to take advantage of the dynamic inheritance of global
            // parameters to a subnet we need to set a callback function for each
            // subnet to allow for fetching global parameters.
            (*subnet)->setFetchGlobalsFn([] () -> ConstElementPtr {
                return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
            });
            external_cfg->getCfgSubnets4()->add((*subnet));
        }
    }

    if (audit_entries.empty()) {
        // If we're configuring the server after startup, we do not apply the
        // ip-reservations-unique setting here. It will be applied when the
        // configuration is committed.
        auto const& cfg = CfgMgr::instance().getStagingCfg();
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
                LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_IPV4_RESERVATIONS_NON_UNIQUE_IGNORED);
                external_cfg->addConfiguredGlobal("ip-reservations-unique", Element::create(true));
            }
        }
        auto const& cfg = CfgMgr::instance().getCurrentCfg();
        external_cfg->sanityChecksLifetime(*cfg, "valid-lifetime");
        CfgMgr::instance().mergeIntoCurrentCfg(external_cfg->getSequence());
    }
    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_CONFIG4_MERGED);

    if (!audit_entries.empty() &&
        HooksManager::calloutsPresent(hooks_.hook_index_cb4_updated_)) {
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
        HooksManager::callCallouts(hooks_.hook_index_cb4_updated_, *callout_handle);

        // Ignore the result.
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
