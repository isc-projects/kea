// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <yang/adaptor_config.h>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;

namespace {
const string DHCP4_SPACE = "dhcp4";
const string DHCP6_SPACE = "dhcp6";
}

namespace isc {
namespace yang {

AdaptorConfig::AdaptorConfig() {
}

AdaptorConfig::~AdaptorConfig() {
}

bool
AdaptorConfig::subnetsCollectID(ConstElementPtr subnets, SubnetIDSet& set) {
    bool have_ids = true;

    if (!subnets || subnets->empty()) {
        // There are no subnets defined, so technically there are no ids.
        // However, the flag is used to determine whether the code later
        // needs to call assignIDs. Since there is no need to assign
        // anything, the code returns true here.
        return (true);
    }

    // If there are subnets defined, let's go over them one by one and
    // collect subnet-ids used in them.
    for (ConstElementPtr subnet : subnets->listValue()) {
        if (!collectID(subnet, set)) {
            have_ids = false;
        }
    }
    return (have_ids);
}

bool
AdaptorConfig::sharedNetworksCollectID(ConstElementPtr networks,
                                       SubnetIDSet& set,
                                       const string& subsel) {
    if (!networks || networks->empty()) {
        // There are no shared networks defined, so technically there are no
        // ids. However, the flag is used to determine whether the code later
        // needs to call assignIDs. Since there is no need to assign anything,
        // the code returns true here.
        return (true);
    }

    // This determines if EVERY subnet has subnet-id defined.
    bool have_ids = true;
    for (size_t i = 0; i < networks->size(); ++i) {
        ElementPtr network = networks->getNonConst(i);
        ConstElementPtr subnets = network->get(subsel);
        if (subnets) {
            if (!subnets->empty()) {
                // If there are subnets, collect their subnet-ids. If any
                // of them doesn't have a subnet-id, return false.
                if (!subnetsCollectID(subnets, set)) {
                    have_ids = false;
                }
            } else {
                // There's empty subnets list, so just remove it.
                network->remove(subsel);
            }
        }
    }
    return (have_ids);
}

void
AdaptorConfig::subnetsAssignID(ConstElementPtr subnets, SubnetIDSet& set,
                               SubnetID& next) {
    if (!subnets || subnets->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < subnets->size(); ++i) {
        ElementPtr subnet = subnets->getNonConst(i);
        assignID(subnet, set, next);
    }
}

void
AdaptorConfig::sharedNetworksAssignID(ConstElementPtr networks,
                                      SubnetIDSet& set, SubnetID& next,
                                      const string& subsel) {
    if (!networks || networks->empty()) {
        // nothing to do here.
        return;
    }

    for (ConstElementPtr network : networks->listValue()) {
        ConstElementPtr subnets = network->get(subsel);
        if (!subnets || subnets->empty()) {
            continue;
        }

        for (size_t i = 0; i < subnets->size(); ++i) {
            ElementPtr subnet = subnets->getNonConst(i);
            assignID(subnet, set, next);
        }
    }
}

void
AdaptorConfig::sanitizePools(ConstElementPtr pools) {
    if (!pools || pools->empty()) {
        // nothing to do here.
        return;
    }

    // Canonize (clean up name, remove extra spaces, add one space where
    // needed) every pool on the list.
    for (size_t i = 0; i < pools->size(); ++i) {
        ElementPtr pool = pools->getNonConst(i);
        AdaptorPool::canonizePool(pool);
    }
}

void
AdaptorConfig::sanitizePoolsInSubnets(ConstElementPtr subnets) {
    if (!subnets || subnets->empty()) {
        // nothing to do here.
        return;
    }

    for (ConstElementPtr subnet : subnets->listValue()) {
        sanitizePools(subnet->get("pools"));
    }
}

void
AdaptorConfig::sanitizePoolsInSharedNetworks(ConstElementPtr networks,
                                             const string& subsel) {
    if (!networks || networks->empty()) {
        // nothing to do here.
        return;
    }

    for (ConstElementPtr network : networks->listValue()) {
        sanitizePoolsInSubnets(network->get(subsel));
    }
}

void
AdaptorConfig::sanitizeOptionDefList(ConstElementPtr defs,
                                     const string& space,
                                     OptionCodes& codes) {
    if (!defs || defs->empty()) {
        // nothing to do here.
        return;
    }

    // Do sanity checks on every option definition and fill any missing
    // fields with default values.
    for (size_t i = 0; i < defs->size(); ++i) {
        ElementPtr def = defs->getNonConst(i);
        checkCode(def);
        checkType(def);
        setSpace(def, space);
        collect(def, codes);
    }
}

void
AdaptorConfig::sanitizeOptionDataList(ConstElementPtr options,
                                      const string& space,
                                      const OptionCodes& codes) {
    if (!options || options->empty()) {
        // nothing to do here.
        return;
    }

    // Sanitize option-data. The only missing elements we may possibly
    // need to fill are option space and option code.
    for (size_t i = 0; i < options->size(); ++i) {
        ElementPtr option = options->getNonConst(i);
        setSpace(option, space);
        setCode(option, codes);
    }
}

void
AdaptorConfig::sanitizeOptionClasses(ConstElementPtr classes,
                                     const string& space,
                                     OptionCodes& codes) {
    if (!classes || classes->empty()) {
        // nothing to do here.
        return;
    }

    // For every client class defined...
    for (size_t i = 0; i < classes->size(); ++i) {
        ElementPtr cclass = classes->getNonConst(i);

        if (space == DHCP4_SPACE) {
            ConstElementPtr options = cclass->get("option-def");
            if (options) {
                if (!options->empty()) {
                    // If present, sanitize it.
                    sanitizeOptionDefList(options, space, codes);
                } else {
                    // If empty, remove it.
                    cclass->remove("option-def");
                }
            }
        }

        // also sanitize option data.
        ConstElementPtr options = cclass->get("option-data");
        if (options) {
            if (!options->empty()) {
                // If present, sanitize it.
                sanitizeOptionDataList(options, space, codes);
            } else {
                // If empty, remove it.
                cclass->remove("option-data");
            }
        }
    }
}

void
AdaptorConfig::sanitizeOptionPools(ConstElementPtr pools, const string& space,
                                   const OptionCodes& codes) {
    if (!pools || pools->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < pools->size(); ++i) {
        ElementPtr pool = pools->getNonConst(i);
        ConstElementPtr options = pool->get("option-data");
        if (options) {
            if (!options->empty()) {
                sanitizeOptionDataList(options, space, codes);
            } else {
                pool->remove("option-data");
            }
        }
    }
}

void
AdaptorConfig::sanitizeOptionHosts(ConstElementPtr hosts, const string& space,
                                   const OptionCodes& codes) {
    if (!hosts || hosts->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < hosts->size(); ++i) {
        ElementPtr host = hosts->getNonConst(i);
        ConstElementPtr options = host->get("option-data");
        if (options) {
            if (!options->empty()) {
                sanitizeOptionDataList(options, space, codes);
            } else {
                host->remove("option-data");
            }
        }
    }
}

void
AdaptorConfig::sanitizeOptionSubnets(ConstElementPtr subnets,
                                     const string& space,
                                     const OptionCodes& codes) {
    if (!subnets || subnets->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < subnets->size(); ++i) {
        ElementPtr subnet = subnets->getNonConst(i);

        // Let's try to sanitize option-data first.
        ConstElementPtr options = subnet->get("option-data");
        if (options) {
            if (!options->empty()) {
                sanitizeOptionDataList(options, space, codes);
            } else {
                subnet->remove("option-data");
            }
        }

        // Then try to sanitize pools.
        ConstElementPtr pools = subnet->get("pools");
        if (pools) {
            if (!pools->empty()) {
                sanitizeOptionPools(pools, space, codes);
            } else {
                subnet->remove("pools");
            }
        }

        // If this is v6, also sanitize pd-pools.
        if (space == DHCP6_SPACE) {
            ConstElementPtr pools = subnet->get("pd-pools");
            if (pools) {
                if (!pools->empty()) {
                    sanitizeOptionPools(pools, space, codes);
                } else {
                    subnet->remove("pd-pools");
                }
            }
        }

        // Finally, sanitize host reservations.
        ConstElementPtr hosts = subnet->get("reservations");
        if (hosts) {
            if (!hosts->empty()) {
                sanitizeOptionHosts(hosts, space, codes);
            } else {
                subnet->remove("reservations");
            }
        }
    }
}

void
AdaptorConfig::sanitizeOptionSharedNetworks(ConstElementPtr networks,
                                            const string& space,
                                            const OptionCodes& codes) {
    if (!networks || networks->empty()) {
        // nothing to do here.
        return;
    }

    // For every shared network...
    for (size_t i = 0; i < networks->size(); ++i) {
        ElementPtr network = networks->getNonConst(i);

        // try to sanitize shared network options first.
        ConstElementPtr options = network->get("option-data");
        if (options) {
            if (!options->empty()) {
                sanitizeOptionDataList(options, space, codes);
            } else {
                network->remove("option-data");
            }
        }
        string subnet = "subnet";
        if (space == DHCP4_SPACE) {
            subnet += "4";
        } else {
            subnet += "6";
        }

        // Now try to sanitize subnets.
        ConstElementPtr subnets = network->get(subnet);
        if (subnets) {
            if (!subnets->empty()) {
                sanitizeOptionSubnets(subnets, space, codes);
            } else {
                network->remove(subnet);
            }
        }
    }
}

void
AdaptorConfig::sanitizeRequireClassesPools(ConstElementPtr pools) {
    if (!pools || pools->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < pools->size(); ++i) {
        ElementPtr pool = pools->getNonConst(i);
        ConstElementPtr requires = pool->get("require-client-classes");
        if (requires && requires->empty()) {
            pool->remove("require-client-classes");
        }
    }
}

void
AdaptorConfig::sanitizeRequireClassesSubnets(ConstElementPtr subnets) {
    if (!subnets || subnets->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < subnets->size(); ++i) {
        ElementPtr subnet = subnets->getNonConst(i);
        sanitizeRequireClassesPools(subnet->get("pools"));
        sanitizeRequireClassesPools(subnet->get("pd-pools"));
        ConstElementPtr requires = subnet->get("require-client-classes");
        if (requires && requires->empty()) {
            subnet->remove("require-client-classes");
        }
    }
}

void
AdaptorConfig::requireClassesSharedNetworks(ConstElementPtr networks,
                                            const string& subsel) {
    if (!networks || networks->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < networks->size(); ++i) {
        ElementPtr network = networks->getNonConst(i);
        sanitizeRequireClassesSubnets(network->get(subsel));
        ConstElementPtr requires = network->get("require-client-classes");
        if (requires && requires->empty()) {
            network->remove("require-client-classes");
        }
    }
}

void
AdaptorConfig::sanitizeHostList(ConstElementPtr hosts) {

    if (!hosts || hosts->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < hosts->size(); ++i) {
        ElementPtr host = hosts->getNonConst(i);
        quoteIdentifier(host);
    }
}

void
AdaptorConfig::sanitizeHostSubnets(ConstElementPtr subnets) {

    if (!subnets || subnets->empty()) {
        // nothing to do here.
        return;
    }

    for (ConstElementPtr subnet : subnets->listValue()) {
        sanitizeHostList(subnet->get("reservations"));
    }
}

void
AdaptorConfig::SanitizeHostsInSharedNetworks(ConstElementPtr networks,
                                  const string& space) {
    if (!networks || networks->empty()) {
        // nothing to do here.
        return;
    }

    for (ConstElementPtr network : networks->listValue()) {
        if (space == DHCP4_SPACE) {
            sanitizeHostSubnets(network->get("subnet4"));
        } else {
            sanitizeHostSubnets(network->get("subnet6"));
        }
    }
}

void
AdaptorConfig::sanitizeRelaySubnets(ConstElementPtr subnets) {
    if (!subnets || subnets->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < subnets->size(); ++i) {
        ElementPtr subnet = subnets->getNonConst(i);
        updateRelay(subnet);
    }
}

void
AdaptorConfig::sanitizeRelayInSharedNetworks(ConstElementPtr networks,
                                   const string& subsel) {
    if (!networks || networks->empty()) {
        // nothing to do here.
        return;
    }

    for (size_t i = 0; i < networks->size(); ++i) {
        ElementPtr network = networks->getNonConst(i);
        updateRelay(network);
        sanitizeRelaySubnets(network->get(subsel));
    }
}

void
AdaptorConfig::sanitizeDatabase(ConstElementPtr dhcp) {
    ConstElementPtr database = dhcp->get("hosts-database");
    if (!database) {
        // nothing to do here.
        return;
    }

    ElementPtr mutable_dhcp = boost::const_pointer_cast<Element>(dhcp);
    mutable_dhcp->remove("hosts-database");
    ElementPtr list = Element::createList();
    list->add(boost::const_pointer_cast<Element>(database));
    mutable_dhcp->set("hosts-databases", list);
}

void
AdaptorConfig::sanitizeRelaySuppliedOptions(ConstElementPtr dhcp) {
    ConstElementPtr options = dhcp->get("relay-supplied-options");
    if (!options || !options->empty()) {
        // nothing to do here.
        return;
    }
    ElementPtr mutable_dhcp = boost::const_pointer_cast<Element>(dhcp);
    mutable_dhcp->remove("relay-supplied-options");
}

void
AdaptorConfig::preProcess(ElementPtr dhcp, const string& subsel,
                          const string& space) {
    if (!dhcp) {
        isc_throw(BadValue, "preProcess: null DHCP config");
    }
    bool have_ids = true;
    SubnetIDSet set;
    ConstElementPtr subnets = dhcp->get(subsel);
    if (subnets) {
        if (!subnets->empty()) {
            if (!subnetsCollectID(subnets, set)) {
                have_ids = false;
            }
        } else {
            dhcp->remove(subsel);
        }
    }
    ConstElementPtr networks = dhcp->get("shared-networks");
    if (networks) {
        if (!networks->empty()) {
            if (!sharedNetworksCollectID(networks, set, subsel)) {
                have_ids = false;
            }
        } else {
            dhcp->remove("shared-networks");
        }
    }

    if (!have_ids) {
        SubnetID next(1);
        subnetsAssignID(subnets, set, next);
        sharedNetworksAssignID(networks, set, next, subsel);
    }

    OptionCodes codes;
    initCodes(codes, space);;
    ConstElementPtr defs = dhcp->get("option-def");
    if (defs) {
        if (!defs->empty()) {
            sanitizeOptionDefList(defs, space, codes);
        } else {
            dhcp->remove("option-def");
        }
    }
    ConstElementPtr options = dhcp->get("option-data");
    if (options) {
        if (!options->empty()) {
            sanitizeOptionDataList(options, space, codes);
        } else {
            dhcp->remove("option-data");
        }
    }
    ConstElementPtr classes = dhcp->get("client-classes");
    if (classes) {
        if (!classes->empty()) {
            sanitizeOptionClasses(classes, space, codes);
        } else {
            dhcp->remove("client-classes");
        }
    }
    ConstElementPtr hosts = dhcp->get("reservations");
    if (hosts) {
        if (!hosts->empty()) {
            sanitizeHostList(hosts);
            sanitizeOptionHosts(hosts, space, codes);
        } else {
            dhcp->remove("reservations");
        }
    }
    sanitizeOptionSubnets(subnets, space, codes);
    sanitizeOptionSharedNetworks(networks, space, codes);

    sanitizePoolsInSubnets(subnets);
    sanitizePoolsInSharedNetworks(networks, subsel);

    sanitizeHostSubnets(subnets);
    SanitizeHostsInSharedNetworks(networks, space);

    sanitizeRelaySubnets(subnets);
    sanitizeRelayInSharedNetworks(networks, subsel);

    sanitizeRequireClassesSubnets(subnets);
    requireClassesSharedNetworks(networks, subsel);

    sanitizeDatabase(dhcp);

    if (space == DHCP6_SPACE) {
        sanitizeRelaySuppliedOptions(dhcp);
    }
}

void
AdaptorConfig::preProcess4(ConstElementPtr config) {
    if (!config) {
        isc_throw(BadValue, "preProcess4: null config");
    }
    if (config->getType() != Element::map) {
        isc_throw(BadValue, "preProcess4: not map: " << config->str());
    }
    ConstElementPtr dhcp = config->get("Dhcp4");
    if (!dhcp) {
        return;
    }
    ElementPtr mutable_dhcp = boost::const_pointer_cast<Element>(dhcp);
    preProcess(mutable_dhcp, "subnet4", DHCP4_SPACE);
}

void
AdaptorConfig::preProcess6(ConstElementPtr config) {
    if (!config) {
        isc_throw(BadValue, "preProcess6: null config");
    }
    if (config->getType() != Element::map) {
        isc_throw(BadValue, "preProcess6: not map: " << config->str());
    }
    ConstElementPtr dhcp = config->get("Dhcp6");
    if (!dhcp) {
        return;
    }
    ElementPtr mutable_dhcp = boost::const_pointer_cast<Element>(dhcp);
    preProcess(mutable_dhcp, "subnet6", DHCP6_SPACE);
}

}; // end of namespace isc::yang
}; // end of namespace isc
