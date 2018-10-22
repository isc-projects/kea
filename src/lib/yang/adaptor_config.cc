// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <yang/adaptor_config.h>

using namespace std;
using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace yang {

AdaptorConfig::AdaptorConfig() {
}

AdaptorConfig::~AdaptorConfig() {
}

bool
AdaptorConfig::subnetsCollectID(ConstElementPtr subnets, SubnetIDSet& set) {
    bool have_ids = true;
    if (subnets && (subnets->size() > 0)) {
        for (ConstElementPtr subnet : subnets->listValue()) {
            if (!collectID(subnet, set)) {
                have_ids = false;
            }
        }
    }
    return (have_ids);
}

bool
AdaptorConfig::sharedNetworksCollectID(ConstElementPtr networks,
                                       SubnetIDSet& set,
                                       const string& subsel) {
    bool have_ids = true;
    if (networks && (networks->size() > 0)) {
        for (size_t i = 0; i < networks->size(); ++i) {
            ElementPtr network = networks->getNonConst(i);
            ConstElementPtr subnets = network->get(subsel);
            if (subnets) {
                if (subnets->size() > 0) {
                    if (!subnetsCollectID(subnets, set)) {
                        have_ids = false;
                    }
                } else {
                    network->remove(subsel);
                }
            }
        }
    }
    return (have_ids);
}

void
AdaptorConfig::subnetsAssignID(ConstElementPtr subnets, SubnetIDSet& set,
                               SubnetID& next) {
    if (subnets && (subnets->size() > 0)) {
        for (size_t i = 0; i < subnets->size(); ++i) {
            ElementPtr subnet = subnets->getNonConst(i);
            assignID(subnet, set, next);
        }
    }
}

void
AdaptorConfig::sharedNetworksAssignID(ConstElementPtr networks,
                                      SubnetIDSet& set, SubnetID& next,
                                      const string& subsel) {
    if (networks && (networks->size() > 0)) {
        for (ConstElementPtr network : networks->listValue()) {
            ConstElementPtr subnets = network->get(subsel);
            if (subnets && (subnets->size() > 0)) {
                for (size_t i = 0; i < subnets->size(); ++i) {
                    ElementPtr subnet = subnets->getNonConst(i);
                    assignID(subnet, set, next);
                }
            }
        }
    }
}

void
AdaptorConfig::canonizePools(ConstElementPtr pools) {
    if (pools && (pools->size() > 0)) {
        for (size_t i = 0; i < pools->size(); ++i) {
            ElementPtr pool = pools->getNonConst(i);
            AdaptorPool::canonizePool(pool);
        }
    }
}

void
AdaptorConfig::poolSubnets(ConstElementPtr subnets) {
    if (subnets && (subnets->size() > 0)) {
        for (ConstElementPtr subnet : subnets->listValue()) {
            canonizePools(subnet->get("pools"));
        }
    }
}

void
AdaptorConfig::poolShareNetworks(ConstElementPtr networks,
                                 const string& subsel) {
    if (networks && (networks->size() > 0)) {
        for (ConstElementPtr network : networks->listValue()) {
            poolSubnets(network->get(subsel));
        }
    }
}

void
AdaptorConfig::optionDefList(ConstElementPtr defs,
                             const string& space,
                             OptionCodes& codes) {
    if (defs && (defs->size() > 0)) {
        for (size_t i = 0; i < defs->size(); ++i) {
            ElementPtr def = defs->getNonConst(i);
            checkCode(def);
            checkType(def);
            setSpace(def, space);
            collect(def, codes);
        }
    }
}

void
AdaptorConfig::optionDataList(ConstElementPtr options,const string& space,
                              const OptionCodes& codes) {
    if (options && (options->size() > 0)) {
        for (size_t i = 0; i < options->size(); ++i) {
            ElementPtr option = options->getNonConst(i);
            setSpace(option, space);
            setCode(option, codes);
        }
    }
}

void
AdaptorConfig::optionClasses(ConstElementPtr classes, const string& space,
                             OptionCodes& codes) {
    if (classes && (classes->size() > 0)) {
        for (size_t i = 0; i < classes->size(); ++i) {
            ElementPtr cclass = classes->getNonConst(i);
            if (space == "dhcp4") {
                ConstElementPtr options = cclass->get("option-def");
                if (options) {
                    if (options->size() > 0) {
                        optionDefList(options, space, codes);
                    } else {
                        cclass->remove("option-def");
                    }
                }
            }
            ConstElementPtr options = cclass->get("option-data");
            if (options) {
                if (options->size() > 0) {
                    optionDataList(options, space, codes);
                } else {
                    cclass->remove("option-data");
                }
            }
        }
    }
}

void
AdaptorConfig::optionPools(ConstElementPtr pools, const string& space,
                           const OptionCodes& codes) {
    if (pools && (pools->size() > 0)) {
        for (size_t i = 0; i < pools->size(); ++i) {
            ElementPtr pool = pools->getNonConst(i);
            ConstElementPtr options = pool->get("option-data");
            if (options) {
                if (options->size() > 0) {
                    optionDataList(options, space, codes);
                } else {
                    pool->remove("option-data");
                }
            }
        }
    }
}

void
AdaptorConfig::optionHosts(ConstElementPtr hosts, const string& space,
                           const OptionCodes& codes) {
    if (hosts && (hosts->size() > 0)) {
        for (size_t i = 0; i < hosts->size(); ++i) {
            ElementPtr host = hosts->getNonConst(i);
            ConstElementPtr options = host->get("option-data");
            if (options) {
                if (options->size() > 0) {
                    optionDataList(options, space, codes);
                } else {
                    host->remove("option-data");
                }
            }
        }
    }
}

void
AdaptorConfig::optionSubnets(ConstElementPtr subnets, const string& space,
                             const OptionCodes& codes) {
    if (subnets && (subnets->size() > 0)) {
        for (size_t i = 0; i < subnets->size(); ++i) {
            ElementPtr subnet = subnets->getNonConst(i);
            ConstElementPtr options = subnet->get("option-data");
            if (options) {
                if (options->size() > 0) {
                    optionDataList(options, space, codes);
                } else {
                    subnet->remove("option-data");
                }
            }
            ConstElementPtr pools = subnet->get("pools");
            if (pools) {
                if (pools->size() > 0) {
                    optionPools(pools, space, codes);
                } else {
                    subnet->remove("pools");
                }
            }
            if (space == "dhcp6") {
                ConstElementPtr pools = subnet->get("pd-pools");
                if (pools) {
                    if (pools->size() > 0) {
                        optionPools(pools, space, codes);
                    } else {
                        subnet->remove("pd-pools");
                    }
                }
            }
            ConstElementPtr hosts = subnet->get("reservations");
            if (hosts) {
                if (hosts->size() > 0) {
                    optionHosts(hosts, space, codes);
                } else {
                    subnet->remove("reservations");
                }
            }
        }
    }
}

void
AdaptorConfig::optionSharedNetworks(ConstElementPtr networks,
                                    const string& space,
                                    const OptionCodes& codes) {
    if (networks && (networks->size() > 0)) {
        for (size_t i = 0; i < networks->size(); ++i) {
            ElementPtr network = networks->getNonConst(i);
            ConstElementPtr options = network->get("option-data");
            if (options) {
                if (options->size() > 0) {
                    optionDataList(options, space, codes);
                } else {
                    network->remove("option-data");
                }
            }
            string subnet = "subnet";
            if (space == "dhcp4") {
                subnet += "4";
            } else {
                subnet += "6";
            }
            ConstElementPtr subnets = network->get(subnet);
            if (subnets) {
                if (subnets->size() > 0) {
                    optionSubnets(subnets, space, codes);
                } else {
                    network->remove(subnet);
                }
            }
        }
    }
}

void
AdaptorConfig::requireClassesPools(ConstElementPtr pools) {
    if (pools && (pools->size() > 0)) {
        for (size_t i = 0; i < pools->size(); ++i) {
            ElementPtr pool = pools->getNonConst(i);
            ConstElementPtr requires = pool->get("require-client-classes");
            if (requires && (requires->size() == 0)) {
                pool->remove("require-client-classes");
            }
        }
    }
}

void
AdaptorConfig::requireClassesSubnets(ConstElementPtr subnets) {
    if (subnets && (subnets->size() > 0)) {
        for (size_t i = 0; i < subnets->size(); ++i) {
            ElementPtr subnet = subnets->getNonConst(i);
            requireClassesPools(subnet->get("pools"));
            requireClassesPools(subnet->get("pd-pools"));
            ConstElementPtr requires = subnet->get("require-client-classes");
            if (requires && (requires->size() == 0)) {
                subnet->remove("require-client-classes");
            }
        }
    }
}

void
AdaptorConfig::requireClassesSharedNetworks(ConstElementPtr networks,
                                            const string& subsel) {
    if (networks && (networks->size() > 0)) {
        for (size_t i = 0; i < networks->size(); ++i) {
            ElementPtr network = networks->getNonConst(i);
            requireClassesSubnets(network->get(subsel));
            ConstElementPtr requires = network->get("require-client-classes");
            if (requires && (requires->size() == 0)) {
                network->remove("require-client-classes");
            }
        }
    }
}

void
AdaptorConfig::hostList(ConstElementPtr hosts) {
    if (hosts && (hosts->size() > 0)) {
        for (size_t i = 0; i < hosts->size(); ++i) {
            ElementPtr host = hosts->getNonConst(i);
            quoteIdentifier(host);
        }
    }
}

void
AdaptorConfig::hostSubnets(ConstElementPtr subnets) {
    if (subnets && (subnets->size() > 0)) {
        for (ConstElementPtr subnet : subnets->listValue()) {
            hostList(subnet->get("reservations"));
        }
    }
}

void
AdaptorConfig::hostSharedNetworks(ConstElementPtr networks,
                                  const string& space) {
    if (networks && (networks->size() > 0)) {
        for (ConstElementPtr network : networks->listValue()) {
            if (space == "dhcp4") {
                hostSubnets(network->get("subnet4"));
            } else {
                hostSubnets(network->get("subnet6"));
            }
        }
    }
}

void
AdaptorConfig::relaySubnets(ConstElementPtr subnets) {
    if (subnets && (subnets->size() > 0)) {
        for (size_t i = 0; i < subnets->size(); ++i) {
            ElementPtr subnet = subnets->getNonConst(i);
            updateRelay(subnet);
        }
    }
}

void
AdaptorConfig::relaySharedNetworks(ConstElementPtr networks,
                                   const string& subsel) {
    if (networks && (networks->size() > 0)) {
        for (size_t i = 0; i < networks->size(); ++i) {
            ElementPtr network = networks->getNonConst(i);
            updateRelay(network);
            relaySubnets(network->get(subsel));
        }
    }
}

void
AdaptorConfig::updateDatabase(ConstElementPtr dhcp) {
    ConstElementPtr database = dhcp->get("hosts-database");
    if (!database) {
        return;
    }
    ElementPtr mutable_dhcp = boost::const_pointer_cast<Element>(dhcp);
    mutable_dhcp->remove("hosts-database");
    ElementPtr list = Element::createList();
    list->add(boost::const_pointer_cast<Element>(database));
    mutable_dhcp->set("hosts-databases", list);
}

void
AdaptorConfig::relaySuppliedOptions(ConstElementPtr dhcp) {
    ConstElementPtr options = dhcp->get("relay-supplied-options");
    if (!options || (options->size() > 0)) {
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
        if (subnets->size() > 0) {
            if (!subnetsCollectID(subnets, set)) {
                have_ids = false;
            }
        } else {
            dhcp->remove(subsel);
        }
    }
    ConstElementPtr networks = dhcp->get("shared-networks");
    if (networks) {
        if (networks->size() > 0) {
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
        if (defs->size() > 0) {
            optionDefList(defs, space, codes);
        } else {
            dhcp->remove("option-def");
        }
    }
    ConstElementPtr options = dhcp->get("option-data");
    if (options) {
        if (options->size() > 0) {
            optionDataList(options, space, codes);
        } else {
            dhcp->remove("option-data");
        }
    }
    ConstElementPtr classes = dhcp->get("client-classes");
    if (classes) {
        if (classes->size() > 0) {
            optionClasses(classes, space, codes);
        } else {
            dhcp->remove("client-classes");
        }
    }
    ConstElementPtr hosts = dhcp->get("reservations");
    if (hosts) {
        if (hosts->size() > 0) {
            optionHosts(hosts, space, codes);
        } else {
            dhcp->remove("reservations");
        }
    }
    optionSubnets(subnets, space, codes);
    optionSharedNetworks(networks, space, codes);

    poolSubnets(subnets);
    poolShareNetworks(networks, subsel);

    hostSubnets(subnets);
    hostSharedNetworks(networks, space);

    relaySubnets(subnets);
    relaySharedNetworks(networks, subsel);

    requireClassesSubnets(subnets);
    requireClassesSharedNetworks(networks, subsel);

    updateDatabase(dhcp);

    if (space == "dhcp6") {
        relaySuppliedOptions(dhcp);
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
    preProcess(mutable_dhcp, "subnet4", "dhcp4");
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
    preProcess(mutable_dhcp, "subnet6", "dhcp6");
}

}; // end of namespace isc::yang
}; // end of namespace isc

