// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_control_socket.h>
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
    : Translator(session, model) {
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
        isc_throw(NetconfError,
                  "getting control socket: " << ex.what());
    }
    isc_throw(NotImplemented,
              "getControlSocket not implemented for the model: " << model_);
}

ElementPtr
TranslatorControlSocket::getControlSocketKea(DataNode const& data_node) {
    ElementPtr result(Element::createMap());
    getMandatoryLeaf(result, data_node, "socket-name");
    getMandatoryLeaf(result, data_node, "socket-type");
    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");
    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorControlSocket::getControlSocketFromAbsoluteXpath(string const& xpath) {
    try {
        return getControlSocket(findXPath(xpath));
    } catch (NetconfError const&) {
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
        isc_throw(NetconfError,
                  "setting control socket '" << elem->str()
                  << "' at '" << xpath << "': " << ex.what());
    }
}

void
TranslatorControlSocket::setControlSocketKea(string const& xpath,
                                             ConstElementPtr elem) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }

    setMandatoryLeaf(elem, xpath, "socket-name", LeafBaseType::String);
    setMandatoryLeaf(elem, xpath, "socket-type", LeafBaseType::Enum);
    checkAndSetUserContext(elem, xpath);
}

}  // namespace yang
}  // namespace isc
