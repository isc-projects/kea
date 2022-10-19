// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
using namespace libyang;
using namespace sysrepo;

namespace isc {
namespace yang {

TranslatorControlSocket::TranslatorControlSocket(Session session,
                                                 const string& model)
    : TranslatorBasic(session, model) {
}

TranslatorControlSocket::~TranslatorControlSocket() {
}

ElementPtr
TranslatorControlSocket::getControlSocket(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            return (getControlSocketKea(data_node));
        }
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error getting control socket: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getControlSocket not implemented for the model: " << model_);
}

ElementPtr
TranslatorControlSocket::getControlSocketKea(DataNode const& data_node) {
    ConstElementPtr name = getItem(data_node, "socket-name");
    ConstElementPtr type = getItem(data_node, "socket-type");
    if (name && type) {
        ElementPtr result = Element::createMap();
        result->set("socket-name", name);
        result->set("socket-type", type);
        ConstElementPtr context = getItem(data_node, "user-context");
        if (context) {
            result->set("user-context",
                        Element::fromJSON(context->stringValue()));
        }
        return (result);
    }
    return (ElementPtr());
}

ElementPtr
TranslatorControlSocket::getControlSocket(string const& xpath) {
    try {
        return getControlSocket(findXPath(xpath));
    } catch(SysrepoError const&) {
        return ElementPtr();
    }
}

void
TranslatorControlSocket::setControlSocket(string const& xpath,
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
    } catch (Error const& ex) {
        isc_throw(SysrepoError,
                  "sysrepo error setting control socket '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorControlSocket::setControlSocketKea(string const& xpath,
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
    setItem(xpath + "/socket-name", name, LeafBaseType::String);
    setItem(xpath + "/socket-type", type, LeafBaseType::Enum);
    ConstElementPtr context = Adaptor::getContext(elem);
    if (context) {
        setItem(xpath + "/user-context", Element::create(context->str()),
                LeafBaseType::String);
    }
}

}  // namespace yang
}  // namespace isc
