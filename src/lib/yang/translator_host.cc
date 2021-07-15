// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorHost::TranslatorHost(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model) {
}

TranslatorHost::~TranslatorHost() {
}

ElementPtr
    TranslatorHost::getHost(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            return (getHostKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting host reservation at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getHost not implemented for the model: " << model_);
}

ElementPtr
TranslatorHost::getHostKea(const string& xpath) {
    ConstElementPtr id_type = getItem(xpath + "/identifier-type");
    ConstElementPtr id = getItem(xpath + "/identifier");
    if (!id_type || !id) {
        isc_throw(Unexpected, "getHostKea requires both identifier and "
                  "identifier-type");
    }
    ElementPtr result = Element::createMap();
    result->set(id_type->stringValue(), id);
    ConstElementPtr hostname = getItem(xpath + "/hostname");
    if (hostname) {
        result->set("hostname", hostname);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr address = getItem(xpath + "/ip-address");
        if (address) {
            result->set("ip-address", address);
        }
    } else {
        ConstElementPtr addresses = getItems(xpath + "/ip-addresses");
        if (addresses && (addresses->size() > 0)) {
            result->set("ip-addresses", addresses);
        }
        ConstElementPtr prefixes = getItems(xpath + "/prefixes");
        if (prefixes && (prefixes->size() > 0)) {
            result->set("prefixes", prefixes);
        }
    }
    ConstElementPtr options = getOptionDataList(xpath);
    if (options && (options->size() > 0)) {
        result->set("option-data", options);
    }
    ConstElementPtr classes = getItems(xpath + "/client-classes");
    if (classes) {
        result->set("client-classes", classes);
    }
    if (model_ == KEA_DHCP4_SERVER) {
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
TranslatorHost::setHost(const string& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setHostKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setHost not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting host reservation '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorHost::setHostKea(const string& xpath, ConstElementPtr elem) {
    ConstElementPtr hostname = elem->get("hostname");
    // Skip identifier and identifier type as they are keys.
    if (hostname) {
        setItem(xpath + "/hostname", hostname, SR_STRING_T);
    }
    if (model_ == KEA_DHCP4_SERVER) {
        ConstElementPtr address = elem->get("ip-address");
        if (address) {
            setItem(xpath + "/ip-address", address, SR_STRING_T);
        }
    } else {
        ConstElementPtr addresses = elem->get("ip-addresses");
        if (addresses && (addresses->size() > 0)) {
            for (ConstElementPtr address : addresses->listValue()) {
                setItem(xpath + "/ip-addresses", address, SR_STRING_T);
            }
        }
        ConstElementPtr prefixes = elem->get("prefixes");
        if (prefixes && (prefixes->size() > 0)) {
            for (ConstElementPtr prefix : prefixes->listValue()) {
                setItem(xpath + "/prefixes", prefix, SR_STRING_T);
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
            setItem(xpath + "/client-classes", cclass, SR_STRING_T);
        }
    }

    // These are DHCPv4-specific parameters.
    if (model_ == KEA_DHCP4_SERVER) {
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

    // User context is supported in both kea-dhcp4-server and kea-dhcp6-server.
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
    }
}

TranslatorHosts::TranslatorHosts(S_Session session, const string& model)
    : TranslatorBasic(session, model),
      TranslatorOptionData(session, model),
      TranslatorOptionDataList(session, model),
      TranslatorHost(session, model) {
}

TranslatorHosts::~TranslatorHosts() {
}

ElementPtr
TranslatorHosts::getHosts(const string& xpath) {
    return getList<TranslatorHost>(xpath + "/host", *this,
                                   &TranslatorHost::getHost);
}

void
TranslatorHosts::setHosts(const string& xpath, ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER)) {
            setHostsKea(xpath, elem);
        } else {
            isc_throw(NotImplemented,
                      "setHosts not implemented for the model: " << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting host reservations '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorHosts::setHostsKea(const string& xpath, ConstElementPtr elem) {
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
