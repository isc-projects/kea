// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/adaptor_pool.h>
#include <yang/translator_subnet.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorSubnet::TranslatorSubnet(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model) {
}

ElementPtr
TranslatorSubnet::getSubnet(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getSubnetIetf6(data_node));
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            return (getSubnetKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting subnet:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getSubnet not implemented for the model: " << model_);
}

ElementPtr
TranslatorSubnet::getSubnetFromAbsoluteXpath(string const& xpath) {
    try {
        return getSubnet(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorSubnet::getSubnetIetf6(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    getMandatoryDivergingLeaf(result, data_node, "subnet", "network-prefix");
    getMandatoryDivergingLeaf(result, data_node, "id", "network-range-id");

    checkAndGetDiverging(result, data_node, "pools", "address-pools",
                         [&](DataNode const& node) -> ElementPtr const {
                            return getPools(node);
                         });

    checkAndGet(result, data_node, "pd-pools",
                [&](DataNode const& node) -> ElementPtr const {
                    return getPdPools(node);
                });

    ConstElementPtr description = getItem(data_node, "network-description");
    if (description) {
        ElementPtr context = Element::createMap();
        context->set("description", description);
        result->set("user-context", context);
    }

    if (result->get("pools")) {
        AdaptorPool::toSubnet(model_, result, result->get("pools"));
    }

    /// @todo: timers
    /// @todo: option-data
    /// @todo: reservations

    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorSubnet::getSubnetKea(DataNode const& data_node) {
    ElementPtr result = Element::createMap();

    getMandatoryLeaf(result, data_node, "id");
    getMandatoryLeaf(result, data_node, "subnet");

    checkAndGetLeaf(result, data_node, "cache-max-age");
    checkAndGetLeaf(result, data_node, "cache-threshold");
    checkAndGetLeaf(result, data_node, "calculate-tee-times");
    checkAndGetLeaf(result, data_node, "client-class");
    checkAndGetLeaf(result, data_node, "ddns-generated-prefix");
    checkAndGetLeaf(result, data_node, "ddns-override-client-update");
    checkAndGetLeaf(result, data_node, "ddns-override-no-update");
    checkAndGetLeaf(result, data_node, "ddns-qualifying-suffix");
    checkAndGetLeaf(result, data_node, "ddns-replace-client-name");
    checkAndGetLeaf(result, data_node, "ddns-send-updates");
    checkAndGetLeaf(result, data_node, "ddns-update-on-renew");
    checkAndGetLeaf(result, data_node, "ddns-use-conflict-resolution");
    checkAndGetLeaf(result, data_node, "hostname-char-replacement");
    checkAndGetLeaf(result, data_node, "hostname-char-set");
    checkAndGetLeaf(result, data_node, "interface");
    checkAndGetLeaf(result, data_node, "max-valid-lifetime");
    checkAndGetLeaf(result, data_node, "min-valid-lifetime");
    checkAndGetLeaf(result, data_node, "rebind-timer");
    checkAndGetLeaf(result, data_node, "renew-timer");
    checkAndGetLeaf(result, data_node, "require-client-classes");
    checkAndGetLeaf(result, data_node, "reservation-mode");
    checkAndGetLeaf(result, data_node, "reservations-global");
    checkAndGetLeaf(result, data_node, "reservations-in-subnet");
    checkAndGetLeaf(result, data_node, "reservations-out-of-pool");
    checkAndGetLeaf(result, data_node, "store-extended-info");
    checkAndGetLeaf(result, data_node, "t1-percent");
    checkAndGetLeaf(result, data_node, "t2-percent");
    checkAndGetLeaf(result, data_node, "valid-lifetime");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    ConstElementPtr options = getOptionDataList(data_node);
    if (options) {
        result->set("option-data", options);
    }

    ConstElementPtr pools = getPools(data_node);
    if (pools) {
        result->set("pools", pools);
    }

    checkAndGet(result, data_node, "relay",
                [&](DataNode const& node) -> ElementPtr const {
                    ElementPtr relay(Element::createMap());
                    checkAndGetLeaf(relay, node, "ip-addresses");
                    return relay;
                });

    ConstElementPtr hosts = getHosts(data_node);
    if (hosts) {
        result->set("reservations", hosts);
    }

    if (model_ == KEA_DHCP6_SERVER) {
        checkAndGetLeaf(result, data_node, "interface-id");
        checkAndGetLeaf(result, data_node, "max-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "min-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "preferred-lifetime");
        checkAndGetLeaf(result, data_node, "rapid-commit");

        ElementPtr pd_pools = getPdPools(data_node);
        if (pd_pools) {
            result->set("pd-pools", pd_pools);
        }
    } else if (model_ == KEA_DHCP4_SERVER) {
        checkAndGetLeaf(result, data_node, "authoritative");
        checkAndGetLeaf(result, data_node, "boot-file-name");
        checkAndGetLeaf(result, data_node, "match-client-id");
        checkAndGetLeaf(result, data_node, "next-server");
        checkAndGetLeaf(result, data_node, "server-hostname");

        checkAndGetDivergingLeaf(result, data_node, "4o6-interface", "subnet-4o6-interface");
        checkAndGetDivergingLeaf(result, data_node, "4o6-interface-id", "subnet-4o6-interface-id");
        checkAndGetDivergingLeaf(result, data_node, "4o6-subnet", "subnet-4o6-subnet");
    }

    return (result->empty() ? ElementPtr() : result);
}

void
TranslatorSubnet::setSubnet(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setSubnetIetf6(xpath, elem);
        } else if ((model_ == KEA_DHCP4_SERVER) ||
                   (model_ == KEA_DHCP6_SERVER)) {
            setSubnetKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setSubnet not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting subnet '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorSubnet::setSubnetIetf6(string const& xpath, ConstElementPtr elem) {
    /// Skip key "id".

    setMandatoryDivergingLeaf(elem, xpath, "subnet", "network-prefix", LeafBaseType::String);

    AdaptorPool::fromSubnet(model_, elem, elem->get("pools"));
    ConstElementPtr context = elem->get("user-context");
    if (context && context->contains("description")) {
        ConstElementPtr description = context->get("description");
        if (description->getType() == Element::string) {
            setItem(xpath + "/network-description", description, LeafBaseType::String);
        }
    }
    ConstElementPtr subnet = elem->get("subnet");
    if (!subnet) {
        isc_throw(BadValue, "setSubnetIetf6 requires subnet: " << elem->str());
    }
    setItem(xpath + "/network-prefix", subnet, LeafBaseType::String);
    ConstElementPtr pools = elem->get("pools");
    if (pools && !pools->empty()) {
        setPools(xpath + "/address-pools", pools);
    }
    pools = elem->get("pd-pools");
    if (pools && !pools->empty()) {
        setPdPools(xpath + "/pd-pools", pools);
    }

    /// @todo: option-data
    /// @todo: reservations
}

void
TranslatorSubnet::setSubnetKea(string const& xpath, ConstElementPtr elem) {
    /// Skip key "id".

    ConstElementPtr subnet = elem->get("subnet");
    if (!subnet) {
        isc_throw(BadValue, "setSubnetKea requires subnet: " << elem->str());
    }
    setItem(xpath + "/subnet", subnet, LeafBaseType::String);

    checkAndSetLeaf(elem, xpath, "cache-max-age", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "cache-threshold", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "calculate-tee-times", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "client-class", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-generated-prefix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-override-client-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-override-no-update", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-qualifying-suffix", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-replace-client-name", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "ddns-send-updates", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-update-on-renew", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "ddns-use-conflict-resolution", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "hostname-char-replacement", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "hostname-char-set", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "interface", LeafBaseType::String);
    checkAndSetLeaf(elem, xpath, "max-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "min-valid-lifetime", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "rebind-timer", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "renew-timer", LeafBaseType::Uint32);
    checkAndSetLeaf(elem, xpath, "reservation-mode", LeafBaseType::Enum);
    checkAndSetLeaf(elem, xpath, "reservations-global", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-in-subnet", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "reservations-out-of-pool", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "store-extended-info", LeafBaseType::Bool);
    checkAndSetLeaf(elem, xpath, "t1-percent", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "t2-percent", LeafBaseType::Dec64);
    checkAndSetLeaf(elem, xpath, "valid-lifetime", LeafBaseType::Uint32);

    checkAndSetLeafList(elem, xpath, "require-client-classes", LeafBaseType::String);

    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
    }
    ConstElementPtr pools = elem->get("pools");
    if (pools && !pools->empty()) {
        setPools(xpath, pools);
    }
    ConstElementPtr relay = elem->get("relay");
    if (relay) {
        ConstElementPtr address = relay->get("ip-address");
        ConstElementPtr addresses = relay->get("ip-addresses");
        if (address) {
            setItem(xpath + "/relay/ip-addresses", address, LeafBaseType::String);
        } else if (addresses && !addresses->empty()) {
            for (ElementPtr const& addr : addresses->listValue()) {
                setItem(xpath + "/relay/ip-addresses", addr, LeafBaseType::String);
            }
        }
    }
    ConstElementPtr hosts = elem->get("reservations");
    if (hosts && !hosts->empty()) {
        setHosts(xpath, hosts);
    }

    if (model_ == KEA_DHCP6_SERVER) {
        checkAndSetLeaf(elem, xpath, "interface-id", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "rapid-commit", LeafBaseType::Bool);

        pools = elem->get("pd-pools");
        if (pools && !pools->empty()) {
            setPdPools(xpath, pools);
        }
    } else {
        checkAndSetLeaf(elem, xpath, "authoritative", LeafBaseType::Bool);
        checkAndSetLeaf(elem, xpath, "boot-file-name", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "match-client-id", LeafBaseType::Bool);
        checkAndSetLeaf(elem, xpath, "next-server", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "server-hostname", LeafBaseType::String);

        checkAndSetDivergingLeaf(elem, xpath, "4o6-interface", "subnet-4o6-interface", LeafBaseType::String);
        checkAndSetDivergingLeaf(elem, xpath, "4o6-interface-id", "subnet-4o6-interface-id", LeafBaseType::String);
        checkAndSetDivergingLeaf(elem, xpath, "4o6-subnet", "subnet-4o6-subnet", LeafBaseType::String);
    }
    checkAndSetUserContext(elem, xpath);
}

TranslatorSubnets::TranslatorSubnets(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model),
      TranslatorSubnet(session, model) {
}

ElementPtr
TranslatorSubnets::getSubnets(DataNode const& data_node) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            return (getSubnetsCommon(data_node, "network-range"));
        } else if (model_ == KEA_DHCP4_SERVER) {
            return (getSubnetsCommon(data_node, "subnet4"));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getSubnetsCommon(data_node, "subnet6"));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting subnets:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getSubnets not implemented for the model: " << model_);
}

ElementPtr
TranslatorSubnets::getSubnetsFromAbsoluteXpath(string const& xpath) {
    try {
        return getSubnets(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorSubnets::getSubnetsCommon(DataNode const& data_node,
                                    string const& subsel) {
    return getList<TranslatorSubnet>(data_node, subsel, *this,
                                     &TranslatorSubnet::getSubnet);
}

void
TranslatorSubnets::setSubnets(string const& xpath, ConstElementPtr elem) {
    try {
        if (model_ == IETF_DHCPV6_SERVER) {
            setSubnetsIetf6(xpath, elem);
        } else if (model_ == KEA_DHCP4_SERVER) {
            setSubnetsKea(xpath, elem, "subnet4");
        } else if (model_ == KEA_DHCP6_SERVER) {
            setSubnetsKea(xpath, elem, "subnet6");
        } else {
            isc_throw(NotImplemented,
                      "setSubnets not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting subnets '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorSubnets::setSubnetsIetf6(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr subnet = elem->getNonConst(i);
        ostringstream range;
        range << xpath << "/network-range[network-range-id='";
        ConstElementPtr id = subnet->get("id");
        if (!id) {
            isc_throw(BadValue, "subnet without id: " << elem->str());
        }
        range << id->intValue() << "']";
        setSubnet(range.str(), subnet);
    }
}

void
TranslatorSubnets::setSubnetsKea(string const& xpath, ConstElementPtr elem,
                                 string const& subsel) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr subnet = elem->getNonConst(i);
        if (!subnet->contains("id")) {
            isc_throw(BadValue, "subnet without id: " << subnet->str());
        }
        ostringstream prefix;
        prefix << xpath << "/" << subsel << "[id='"
               << subnet->get("id")->intValue() << "']";
        setSubnet(prefix.str(), subnet);
    }
}

}  // namespace yang
}  // namespace isc
