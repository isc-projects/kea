// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_host.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorHost::TranslatorHost(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

TranslatorHost::~TranslatorHost() {
}

ElementPtr
TranslatorHost::getHost(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getHostKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting host reservation:"
                  << ex.what());
    }
    isc_throw(NotImplemented,
              "getHost not implemented for the model: " << model_);
}

ElementPtr
TranslatorHost::getHost(std::string const& xpath) {
    try {
        return getHost(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

ElementPtr
TranslatorHost::getHostKea(DataNode const& data_node) {
    ConstElementPtr id_type = getItem(data_node, "identifier-type");
    ConstElementPtr id = getItem(data_node, "identifier");
    if (!id_type || !id) {
        isc_throw(Unexpected, "getHostKea requires both identifier and "
                  "identifier-type");
    }
    ElementPtr result = Element::createMap();
    result->set(id_type->stringValue(), id);
    ConstElementPtr hostname = getItem(data_node, "hostname");
    if (hostname) {
        result->set("hostname", hostname);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr address = getItem(data_node, "ip-address");
        if (address) {
            result->set("ip-address", address);
        }
    } else {
        ConstElementPtr addresses = getItem(data_node, "ip-addresses");
        if (addresses && (addresses->size() > 0)) {
            result->set("ip-addresses", addresses);
        }
        ConstElementPtr prefixes = getItem(data_node, "prefixes");
        if (prefixes && (prefixes->size() > 0)) {
            result->set("prefixes", prefixes);
        }
    }
    ConstElementPtr options = getOptionDataList(data_node);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr classes = getItem(data_node, "client-classes");
    if (classes) {
        result->set("client-classes", classes);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr next = getItem(data_node, "next-server");
        if (next) {
            result->set("next-server", next);
        }
        ConstElementPtr server_hostname = getItem(data_node, "server-hostname");
        if (server_hostname) {
            result->set("server-hostname", server_hostname);
        }
        ConstElementPtr boot = getItem(data_node, "boot-file-name");
        if (boot) {
            result->set("boot-file-name", boot);
        }
    }
    ConstElementPtr context = getItem(data_node, "user-context");
    if (context) {
        result->set("user-context", Element::fromJSON(context->stringValue()));
    }
    return (result);
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
        isc_throw(SysrepoError,
                  "sysrepo error setting host reservation '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorHost::setHostKea(string const& xpath, ConstElementPtr elem) {
    ConstElementPtr hostname = elem->get("hostname");
    // Skip identifier and identifier type as they are keys.
    if (hostname) {
        setItem(xpath + "/hostname", hostname, LeafBaseType::String);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr address = elem->get("ip-address");
        if (address) {
            setItem(xpath + "/ip-address", address, LeafBaseType::String);
        }
    } else {
        ConstElementPtr addresses = elem->get("ip-addresses");
        if (addresses && (addresses->size() > 0)) {
            for (ConstElementPtr address : addresses->listValue()) {
                setItem(xpath + "/ip-addresses", address, LeafBaseType::String);
            }
        }
        ConstElementPtr prefixes = elem->get("prefixes");
        if (prefixes && (prefixes->size() > 0)) {
            for (ConstElementPtr prefix : prefixes->listValue()) {
                setItem(xpath + "/prefixes", prefix, LeafBaseType::String);
            }
        }
    }
    ConstElementPtr options = elem->get("option-data");
    if (options && (options->size() > 0)) {
        setOptionDataList(xpath, options);
    }
    ConstElementPtr classes = elem->get("client-classes");
    if (classes && (classes->size() > 0)) {
        for (ConstElementPtr cclass : classes->listValue()) {
            setItem(xpath + "/client-classes", cclass, LeafBaseType::String);
        }
    }

    // These are DHCPv4-specific parameters.
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr next = elem->get("next-server");
        if (next) {
            setItem(xpath + "/next-server", next, LeafBaseType::String);
        }
        ConstElementPtr server_hostname = elem->get("server-hostname");
        if (server_hostname) {
            setItem(xpath + "/server-hostname", server_hostname, LeafBaseType::String);
        }
        ConstElementPtr boot = elem->get("boot-file-name");
        if (boot) {
            setItem(xpath + "/boot-file-name", boot, LeafBaseType::String);
        }
    }

    // User context is supported in both kea-dhcp4-server and kea-dhcp6-server.
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

TranslatorHosts::TranslatorHosts(Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorHost(session, model) {
}

TranslatorHosts::~TranslatorHosts() {
}

ElementPtr
TranslatorHosts::getHosts(DataNode const& data_node) {
    return getList<TranslatorHost>(data_node, "host", *this,
                                   &TranslatorHost::getHost);
}

ElementPtr
TranslatorHosts::getHosts(std::string const& xpath) {
    try {
        return getHosts(findXPath(xpath));
    } catch(SysrepoError const&) {
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
        isc_throw(SysrepoError,
                  "sysrepo error setting host reservations '" << elem->str()
                  << "' : " << ex.what());
    }
}

void
TranslatorHosts::setHostsKea(string const& xpath, ConstElementPtr elem) {
    for (size_t i = 0; i < elem->size(); ++i) {
        string id_type = "unknown";
        ConstElementPtr host = elem->get(i);
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
