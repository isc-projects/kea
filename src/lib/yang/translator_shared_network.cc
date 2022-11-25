// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_shared_network.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorSharedNetwork::TranslatorSharedNetwork(Session session,
                                                 const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model),
      TranslatorSubnet(session, model),
      TranslatorSubnets(session, model) {
}

ElementPtr
TranslatorSharedNetwork::getSharedNetwork(DataNode const& data_node) {
    try {
        if (model_ == KEA_DHCP4_SERVER) {
            return (getSharedNetworkKea(data_node, "subnet4"));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getSharedNetworkKea(data_node, "subnet6"));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting shared network:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getSharedNetwork not implemented for the model: " << model_);
}

ElementPtr
TranslatorSharedNetwork::getSharedNetworkFromAbsoluteXpath(string const& xpath) {
    try {
        return getSharedNetwork(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorSharedNetwork::getSharedNetworkKea(DataNode const& data_node,
                                             string const& subsel) {
    ElementPtr result = Element::createMap();

    getMandatoryLeaf(result, data_node, "name");

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

    ConstElementPtr subnets = getSubnets(data_node);
    if (subnets) {
        result->set(subsel, subnets);
    }

    checkAndGet(result, data_node, "relay",
                [&](DataNode const& node) -> ElementPtr const {
                    ElementPtr relay(Element::createMap());
                    checkAndGetLeaf(relay, node, "ip-addresses");
                    return relay;
                });

    if (subsel == "subnet6") {
        checkAndGetLeaf(result, data_node, "interface-id");
        checkAndGetLeaf(result, data_node, "max-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "min-preferred-lifetime");
        checkAndGetLeaf(result, data_node, "preferred-lifetime");
        checkAndGetLeaf(result, data_node, "rapid-commit");
    } else if (subsel == "subnet4") {
        checkAndGetLeaf(result, data_node, "authoritative");
        checkAndGetLeaf(result, data_node, "boot-file-name");
        checkAndGetLeaf(result, data_node, "match-client-id");
        checkAndGetLeaf(result, data_node, "next-server");
        checkAndGetLeaf(result, data_node, "server-hostname");
    }

    return (result->empty() ? ElementPtr() : result);
}

void
TranslatorSharedNetwork::setSharedNetwork(string const& xpath,
                                          ConstElementPtr elem) {
    try {
        if (model_ == KEA_DHCP4_SERVER) {
            setSharedNetworkKea(xpath, elem, "subnet4");
        } else if (model_ == KEA_DHCP6_SERVER) {
            setSharedNetworkKea(xpath, elem, "subnet6");
        } else {
            isc_throw(NotImplemented,
                      "setSharedNetwork not implemented for the model: "
                      << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting shared network '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorSharedNetwork::setSharedNetworkKea(string const& xpath,
                                             ConstElementPtr elem,
                                             string const& subsel) {
    // Skip key "name".

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

    checkAndSetUserContext(elem, xpath);

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

    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
    }

    ConstElementPtr subnets = elem->get(subsel);
    if (subnets && !subnets->empty()) {
        setSubnets(xpath, subnets);
    }

    if (subsel == "subnet6") {
        checkAndSetLeaf(elem, xpath, "interface-id", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "max-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "min-preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "preferred-lifetime", LeafBaseType::Uint32);
        checkAndSetLeaf(elem, xpath, "rapid-commit", LeafBaseType::Bool);
    } else {
        checkAndSetLeaf(elem, xpath, "authoritative", LeafBaseType::Bool);
        checkAndSetLeaf(elem, xpath, "boot-file-name", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "match-client-id", LeafBaseType::Bool);
        checkAndSetLeaf(elem, xpath, "next-server", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "server-hostname", LeafBaseType::String);
    }
}

TranslatorSharedNetworks::TranslatorSharedNetworks(Session session,
                                                   const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorPool(session, model),
      TranslatorPools(session, model),
      TranslatorPdPool(session, model),
      TranslatorPdPools(session, model),
      TranslatorHost(session, model),
      TranslatorHosts(session, model),
      TranslatorSubnet(session, model),
      TranslatorSubnets(session, model),
      TranslatorSharedNetwork(session, model) {
}

ElementPtr
TranslatorSharedNetworks::getSharedNetworks(DataNode const& data_node) {
    return getList<TranslatorSharedNetwork>(data_node, "shared-network", *this,
                                            &TranslatorSharedNetwork::getSharedNetwork);
}

ElementPtr
TranslatorSharedNetworks::getSharedNetworksFromAbsoluteXpath(string const& xpath) {
    try {
        return getSharedNetworks(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

void
TranslatorSharedNetworks::setSharedNetworks(string const& xpath,
                                            ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setSharedNetworksKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setSharedNetworks not implemented for the model: "
                      << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting shared networks '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorSharedNetworks::setSharedNetworksKea(string const& xpath,
                                               ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr network = elem->getNonConst(i);
        if (!network->contains("name")) {
            isc_throw(BadValue, "setSharedNetworksKea requires name: "
                      << network->str());
        }
        string name = network->get("name")->stringValue();
        ostringstream key;
        key<< xpath << "/shared-network[name='" << name << "']";
        setSharedNetwork(key.str(), network);
    }
}

}  // namespace yang
}  // namespace isc
