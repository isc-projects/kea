// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_shared_network.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

namespace isc {
namespace yang {

TranslatorSharedNetwork::TranslatorSharedNetwork(S_Session session,
                                                 const string& model)
    : TranslatorBasic(session, model),
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

TranslatorSharedNetwork::~TranslatorSharedNetwork() {
}

ElementPtr
TranslatorSharedNetwork::getSharedNetwork(const string& xpath) {
    try {
        if (model_ == KEA_DHCP4_SERVER) {
            return (getSharedNetworkKea(xpath, "subnet4"));
        } else if (model_ == KEA_DHCP6_SERVER) {
            return (getSharedNetworkKea(xpath, "subnet6"));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting shared network at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getSharedNetwork not implemented for the model: " << model_);
}

ElementPtr
TranslatorSharedNetwork::getSharedNetworkKea(const string& xpath,
                                             const std::string& subsel) {
    ElementPtr result = Element::createMap();
    ConstElementPtr name = getItem(xpath + "/name");
    if (!name) {
        // Can't happen as the name is the key.
        isc_throw(Unexpected, "getSharedNetworkKea requires name: " << xpath);
    }
    result->set("name", name);
    ConstElementPtr subnets = getSubnets(xpath);
    if (subnets && (subnets->size() > 0)) {
        result->set(subsel, subnets);
    }
    if (subsel == "subnet6") {
        ConstElementPtr preferred = getItem(xpath + "/preferred-lifetime");
        if (preferred) {
            result->set("preferred-lifetime", preferred);
        }
    }
    ConstElementPtr valid = getItem(xpath + "/valid-lifetime");
    if (valid) {
        result->set("valid-lifetime", valid);
    }
    ConstElementPtr renew = getItem(xpath + "/renew-timer");
    if (renew) {
        result->set("renew-timer", renew);
    }
    ConstElementPtr rebind = getItem(xpath + "/rebind-timer");
    if (rebind) {
        result->set("rebind-timer", rebind);
    }
    ConstElementPtr options = getOptionDataList(xpath);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr interface = getItem(xpath + "/interface");
    if (interface) {
        result->set("interface", interface);
    }
    if (subsel == "subnet6") {
        ConstElementPtr interface_id = getItem(xpath + "/interface-id");
        if (interface_id) {
            result->set("interface-id", interface_id);
        }
        ConstElementPtr rapid_commit = getItem(xpath + "/rapid-commit");
        if (rapid_commit) {
            result->set("rapid-commit", rapid_commit);
        }
    }
    ConstElementPtr guard =  getItem(xpath + "/client-class");
    if (guard) {
        result->set("client-class", guard);
    }
    ConstElementPtr required = getItems(xpath + "/require-client-classes");
    if (required && (required->size() > 0)) {
        result->set("require-client-classes", required);
    }
    ConstElementPtr mode = getItem(xpath + "/reservation-mode");
    if (mode) {
        result->set("reservation-mode", mode);
    }
    ConstElementPtr relay = getItems(xpath + "/relay/ip-addresses");
    if (relay && (relay->size() > 0)) {
        ElementPtr relay_map = Element::createMap();
        relay_map->set("ip-addresses", relay);
        result->set("relay", relay_map);
    }
    if (subsel == "subnet4") {
        ConstElementPtr match = getItem(xpath + "/match-client-id");
        if (match) {
            result->set("match-client-id", match);
        }
        ConstElementPtr auth = getItem(xpath + "/authoritative");
        if (auth) {
            result->set("authoritative", auth);
        }
        ConstElementPtr next = getItem(xpath + "/next-server");
        if (next) {
            result->set("next-server", next);
        }
        ConstElementPtr hostname = getItem(xpath + "/server-hostname");
        if (hostname) {
            result->set("server-hostname", hostname);
        }
        ConstElementPtr boot = getItem(xpath + "/boot-file-name");
        if (boot) {
            result->set("boot-file-name", boot);
        }
    }
    ConstElementPtr context = getItem(xpath + "/user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
}

void
TranslatorSharedNetwork::setSharedNetwork(const string& xpath,
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting shared network '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorSharedNetwork::setSharedNetworkKea(const string& xpath,
                                             ConstElementPtr elem,
                                             const std::string& subsel) {
    // Skip name which is the key.
    ConstElementPtr subnets = elem->get(subsel);
    if (subnets && (subnets->size() > 0)) {
        setSubnets(xpath, subnets);
    }
    if (subsel == "subnet6") {
        ConstElementPtr preferred = elem->get("preferred-lifetime");
        if (preferred) {
            setItem(xpath + "/preferred-lifetime", preferred, SR_UINT32_T);
        }
    }
    ConstElementPtr valid = elem->get("valid-lifetime");
    if (valid) {
        setItem(xpath + "/valid-lifetime", valid, SR_UINT32_T);
    }
    ConstElementPtr renew = elem->get("renew-timer");
    if (renew) {
        setItem(xpath + "/renew-timer", renew, SR_UINT32_T);
    }
    ConstElementPtr rebind = elem->get("rebind-timer");
    if (rebind) {
        setItem(xpath + "/rebind-timer", rebind, SR_UINT32_T);
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && (options->size() > 0)) {
        setOptionDataList(xpath, options);
    }
    ConstElementPtr interface = elem->get("interface");
    if (interface) {
        setItem(xpath + "/interface", interface, SR_STRING_T);
    }
    if (subsel == "subnet6") {
        ConstElementPtr interface_id = elem->get("interface-id");
        if (interface_id) {
            setItem(xpath + "/interface-id", interface_id, SR_STRING_T);
        }
        ConstElementPtr rapid_commit = elem->get("rapid-commit");
        if (rapid_commit) {
            setItem(xpath + "/rapid-commit", rapid_commit, SR_BOOL_T);
        }
    }
    ConstElementPtr guard = elem->get("client-class");
    if (guard) {
        setItem(xpath + "/client-class", guard, SR_STRING_T);
    }
    ConstElementPtr required = elem->get("require-client-classes");
    if (required && (required->size() > 0)) {
        for (ConstElementPtr rclass : required->listValue()) {
            setItem(xpath + "/require-client-classes", rclass, SR_STRING_T);
        }
    }
    ConstElementPtr mode = elem->get("reservation-mode");
    if (mode) {
        setItem(xpath + "/reservation-mode", mode, SR_ENUM_T);
    }
    ConstElementPtr relay = elem->get("relay");
    if (relay) {
        ConstElementPtr address = relay->get("ip-address");
        ConstElementPtr addresses = relay->get("ip-addresses");
        if (address) {
            setItem(xpath + "/relay/ip-addresses", address, SR_STRING_T);
        } else if (addresses && (addresses->size() > 0)) {
            for (ConstElementPtr addr : addresses->listValue()) {
                setItem(xpath + "/relay/ip-addresses", addr, SR_STRING_T);
            }
        }
    }
    if (subsel == "subnet4") {
        ConstElementPtr match = elem->get("match-client-id");
        if (match) {
            setItem(xpath + "/match-client-id", match, SR_BOOL_T);
        }
        ConstElementPtr auth = elem->get("authoritative");
        if (auth) {
            setItem(xpath + "/authoritative", auth, SR_BOOL_T);
        }
        ConstElementPtr next = elem->get("next-server");
        if (next) {
            setItem(xpath + "/next-server", next, SR_STRING_T);
        }
        ConstElementPtr hostname = elem->get("server-hostname");
        if (hostname) {
            setItem(xpath + "/server-hostname", hostname, SR_STRING_T);
        }
        ConstElementPtr boot = elem->get("boot-file-name");
        if (boot) {
            setItem(xpath + "/boot-file-name", boot, SR_STRING_T);
        }
    }
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        ConstElementPtr repr = Element::create(context->str());
        setItem(xpath + "/user-context", repr, SR_STRING_T);
    }
}

TranslatorSharedNetworks::TranslatorSharedNetworks(S_Session session,
                                                   const string& model)
    : TranslatorBasic(session, model),
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

TranslatorSharedNetworks::~TranslatorSharedNetworks() {
}

ElementPtr
TranslatorSharedNetworks::getSharedNetworks(const string& xpath) {
    try {
        ElementPtr result = Element::createList();
        S_Iter_Value iter = getIter(xpath + "/shared-network");
        if (!iter) {
            // Can't happen.
            isc_throw(Unexpected, "getSharedNetworks: can't get iterator: "
                      << xpath);
        }
        for (;;) {
            const string& network = getNext(iter);
            if (network.empty()) {
                break;
            }
            result->add(getSharedNetwork(network));
        }
        return (result);
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting shared networks at '" << xpath
                  << "': " << ex.what());
    }
}

void
TranslatorSharedNetworks::setSharedNetworks(const string& xpath,
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
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting shared networks '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorSharedNetworks::setSharedNetworksKea(const string& xpath,
                                               ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        ConstElementPtr network = elem->get(i);
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

}; // end of namespace isc::yang
}; // end of namespace isc
