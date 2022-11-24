// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_host.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorHost::TranslatorHost(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

ElementPtr
TranslatorHost::getHost(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getHostKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "getting host reservation:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getHost not implemented for the model: " << model_);
}

ElementPtr
TranslatorHost::getHostFromAbsoluteXpath(string const& xpath) {
    try {
        return getHost(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorHost::getHostKea(DataNode const& data_node) {
    ConstElementPtr id_type = getItem(data_node, "identifier-type");
    ConstElementPtr id = getItem(data_node, "identifier");
    if (!id_type || !id) {
        isc_throw(MissingNode, "getHostKea requires both identifier and identifier-type");
    }
    ElementPtr result = Element::createMap();
    result->set(id_type->stringValue(), id);

    checkAndGetLeaf(result, data_node, "client-classes");
    checkAndGetLeaf(result, data_node, "hostname");

    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");

    ConstElementPtr options = getOptionDataList(data_node);
    if (options) {
        result->set("option-data", options);
    }

    if (model_ == KEA_DHCP4_SERVER) {
        checkAndGetLeaf(result, data_node, "boot-file-name");
        checkAndGetLeaf(result, data_node, "ip-address");
        checkAndGetLeaf(result, data_node, "next-server");
        checkAndGetLeaf(result, data_node, "server-hostname");
    } else {
        checkAndGetLeaf(result, data_node, "ip-addresses");
        checkAndGetLeaf(result, data_node, "prefixes");
    }

    return (result->empty() ? ElementPtr() : result);
}

void
TranslatorHost::setHost(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setHostKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setHost not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting host reservation '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorHost::setHostKea(string const& xpath, ConstElementPtr elem) {
    // Skip keys "identifier" and "identifier-type".

    checkAndSetLeaf(elem, xpath, "hostname", LeafBaseType::String);

    checkAndSetLeafList(elem, xpath, "client-classes", LeafBaseType::String);

    ConstElementPtr options = elem->get("option-data");
    if (options && !options->empty()) {
        setOptionDataList(xpath, options);
    }

    if (model_ == KEA_DHCP4_SERVER) {
        checkAndSetLeaf(elem, xpath, "boot-file-name", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "ip-address", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "next-server", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "server-hostname", LeafBaseType::String);
    } else {
        checkAndSetLeafList(elem, xpath, "ip-addresses", LeafBaseType::String);
        checkAndSetLeafList(elem, xpath, "prefixes", LeafBaseType::String);
    }

    // User context is supported in both kea-dhcp4-server and kea-dhcp6-server.
    checkAndSetUserContext(elem, xpath);
}

TranslatorHosts::TranslatorHosts(Session session, const string& model)
    : Translator(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorHost(session, model) {
}

ElementPtr
TranslatorHosts::getHosts(DataNode const& data_node) {
    return getList<TranslatorHost>(data_node, "host", *this,
                                   &TranslatorHost::getHost);
}

ElementPtr
TranslatorHosts::getHostsFromAbsoluteXpath(string const& xpath) {
    try {
        return getHosts(findXPath(xpath));
    } catch (NetconfError const&) {
        return ElementPtr();
    }
}

void
TranslatorHosts::setHosts(string const& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setHostsKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setHosts not implemented for the model: " << model_);
        }
    } catch (Error const& ex) {
        isc_throw(NetconfError,
                  "setting host reservations '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorHosts::setHostsKea(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        string id_type = "unknown";
        ElementPtr host = elem->getNonConst(i);
        ConstElementPtr id = host->get("hw-address");
        if (id) {
            id_type = "hw-address";
            goto found;
        }
        id = host->get("duid");
        if (id) {
            id_type = "duid";
            goto found;
        }
        if (model_ == KEA_DHCP4_SERVER) {
            id = host->get("circuit-id");
            if (id) {
                id_type = "circuit-id";
                goto found;
            }
            id = host->get("client-id");
            if (id) {
                id_type = "client-id";
                goto found;
            }
        }
        id = host->get("flex-id");
        if (id) {
            id_type = "flex-id";
            goto found;
        }

    found:
        if (id_type == "unknown") {
            isc_throw(BadValue, "getHosts: can't find the identifier type in "
                      << host->str());
        }
        ostringstream key;
        key << xpath << "/host[identifier-type='" << id_type
            << "'][identifier='" << id->stringValue() << "']";
        setHost(key.str(), host);
    }
}

}  // namespace yang
}  // namespace isc
