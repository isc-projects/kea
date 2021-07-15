// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_control_socket.h>
#include <yang/adaptor.h>
#include <yang/yang_models.h>
#include <sstream>

using namespace std;
using namespace isc::data;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorControlSocket::TranslatorControlSocket(S_Session session,
                                                 const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorControlSocket::~TranslatorControlSocket() {
}

ConstElementPtr
TranslatorControlSocket::getControlSocket(const string& xpath) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            return (getControlSocketKea(xpath));
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting control socket at '" << xpath
                  << "': " << ex.what());
    }
    isc_throw(NotImplemented,
              "getControlSocket not implemented for the model: " << model_);
}

ElementPtr
TranslatorControlSocket::getControlSocketKea(const string& xpath) {
    ConstElementPtr name = getItem(xpath + "/socket-name");
    ConstElementPtr type = getItem(xpath + "/socket-type");
    if (name && type) {
        ElementPtr result = Element::createMap();
        result->set("socket-name", name);
        result->set("socket-type", type);
        ConstElementPtr context = getItem(xpath + "/user-context");
        if (context) {
            result->set("user-context",
                        Element::fromJSON(context->stringValue()));
        }
        return (result);
    }
    return (ElementPtr());
}

void
TranslatorControlSocket::setControlSocket(const string& xpath,
                                          ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            setControlSocketKea(xpath, elem);
        } else {
          isc_throw(NotImplemented,
                    "setControlSocket not implemented for the model: "
                    << model_);
        }
    } catch (const sysrepo_exception& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting control socket '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorControlSocket::setControlSocketKea(const string& xpath,
                                             ConstElementPtr elem) {
    if (!elem) {
        delItem(xpath);
        return;
    }
    ConstElementPtr name = elem->get("socket-name");
    if (!name) {
        isc_throw(BadValue, "setControlSocket missing socket name");
    }
    ConstElementPtr type = elem->get("socket-type");
    if (!type) {
        isc_throw(BadValue, "setControlSocket missing socket type");
    }
    setItem(xpath + "/socket-name", name, SR_STRING_T);
    setItem(xpath + "/socket-type", type, SR_ENUM_T);
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                SR_STRING_T);
    }
}

}  // namespace yang
}  // namespace isc
