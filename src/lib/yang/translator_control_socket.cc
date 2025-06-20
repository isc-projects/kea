// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
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

TranslatorControlSocket::TranslatorControlSocket(Session session, const string& model)
    : Translator(session, model) {
}

ElementPtr
TranslatorControlSocket::getControlSockets(DataNode const& data_node) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS)) {
            return (getControlSocketsKea(data_node));
        } else if (model_ == KEA_CTRL_AGENT) {
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
TranslatorControlSocket::getControlSocketsKea(DataNode const& data_node) {
    return (getList(data_node, "control-sockets", *this, &TranslatorControlSocket::getControlSocketKea));
}

ElementPtr
TranslatorControlSocket::getControlSocketKea(DataNode const& data_node) {
    ElementPtr result(Element::createMap());
    checkAndGetLeaf(result, data_node, "socket-name");
    checkAndGetLeaf(result, data_node, "socket-type");
    if (model_ != KEA_CTRL_AGENT) {
        checkAndGetLeaf(result, data_node, "socket-address");
        checkAndGetLeaf(result, data_node, "socket-port");
        checkAndGetLeaf(result, data_node, "trust-anchor");
        checkAndGetLeaf(result, data_node, "cert-file");
        checkAndGetLeaf(result, data_node, "key-file");
        checkAndGetLeaf(result, data_node, "cert-required");
        checkAndGet(result, data_node, "authentication",
                    [&](DataNode const& node) -> ElementPtr const {
                        // If it exists, add to the existing compatibility map created in getServerKeaDhcpCommon.
                        ConstElementPtr const_authentication(result->get("authentication"));
                        ElementPtr authentication;
                        if (const_authentication) {
                            authentication = copy(const_authentication);
                        } else {
                            authentication = Element::createMap();
                        }

                        checkAndGetDivergingLeaf(authentication, node, "type", "auth-type");
                        checkAndGetLeaf(authentication, node, "realm");
                        checkAndGetLeaf(authentication, node, "directory");
                        ConstElementPtr clients = getControlSocketAuthenticationClients(node);
                        if (clients) {
                            authentication->set("clients", clients);
                        }
                        return (authentication);
                    });
        ConstElementPtr headers = getControlSocketHttpHeaders(data_node);
        if (headers && !headers->empty()) {
            result->set("http-headers", headers);
        }
    }
    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");
    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorControlSocket::getControlSocketHttpHeaders(DataNode const& data_node) {
    return getList(data_node, "http-headers", *this,
                   &TranslatorControlSocket::getControlSocketHttpHeader);
}

ElementPtr
TranslatorControlSocket::getControlSocketHttpHeader(DataNode const& data_node) {
    ElementPtr result(Element::createMap());
    checkAndGetLeaf(result, data_node, "name");
    checkAndGetLeaf(result, data_node, "value");
    checkAndGetAndJsonifyLeaf(result, data_node, "user-context");
    return (result->empty() ? ElementPtr() : result);
}

ElementPtr
TranslatorControlSocket::getControlSocketAuthenticationClients(DataNode const& data_node) {
    return getList(data_node, "clients", *this,
                   &TranslatorControlSocket::getControlSocketAuthenticationClient);
}

ElementPtr
TranslatorControlSocket::getControlSocketAuthenticationClient(DataNode const& data_node) {
    ElementPtr result = Element::createMap();
    getMandatoryLeaf(result, data_node, "user");
    getMandatoryLeaf(result, data_node, "password");
    getMandatoryLeaf(result, data_node, "user-file");
    getMandatoryLeaf(result, data_node, "password-file");
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
TranslatorControlSocket::setControlSockets(string const& xpath,
                                           ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS)) {
            setControlSocketsKea(xpath, elem);
        } else if (model_ == KEA_CTRL_AGENT) {
            setControlSocketKea(xpath, elem, /* has_mandatory_key = */ true);
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
TranslatorControlSocket::setControlSocket(string const& xpath,
                                          ConstElementPtr elem) {
    try {
        if ((model_ == KEA_DHCP4_SERVER) ||
            (model_ == KEA_DHCP6_SERVER) ||
            (model_ == KEA_DHCP_DDNS) ||
            (model_ == KEA_CTRL_AGENT)) {
            setControlSocketKea(xpath, elem, /* has_mandatory_key = */ false);
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
TranslatorControlSocket::setControlSocketsKea(string const& xpath,
                                              ConstElementPtr elem) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr control_socket = elem->getNonConst(i);
        if (!control_socket->contains("socket-type")) {
            isc_throw(BadValue, "control-socket without socket-type: " << control_socket->str());
        }
        string type = control_socket->get("socket-type")->stringValue();
        ostringstream key;
        key << xpath << "[socket-type='" << type << "']";
        setControlSocketKea(key.str(), control_socket, /* has_mandatory_key = */ true);
    }
}

void
TranslatorControlSocket::setControlSocketKea(string const& xpath,
                                             ConstElementPtr elem,
                                             bool has_mandatory_key) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }

    if (has_mandatory_key) {
        // Set the list element. This is important in case we have no other elements except the key.
        setItem(xpath, ElementPtr(), LeafBaseType::Unknown);
    } else {
        checkAndSetLeaf(elem, xpath, "socket-type", LeafBaseType::String);
    }

    checkAndSetLeaf(elem, xpath, "socket-name", LeafBaseType::String);
    if (model_ != KEA_CTRL_AGENT) {
        checkAndSetLeaf(elem, xpath, "socket-address", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "socket-port", LeafBaseType::Uint16);
        checkAndSetLeaf(elem, xpath, "trust-anchor", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "cert-file", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "key-file", LeafBaseType::String);
        checkAndSetLeaf(elem, xpath, "cert-required", LeafBaseType::Bool);
        ConstElementPtr authentication = elem->get("authentication");
        if (authentication && !authentication->empty()) {
            setMandatoryDivergingLeaf(authentication, xpath +"/authentication" , "type", "auth-type", LeafBaseType::String);
            checkAndSetLeaf(authentication, xpath + "/authentication", "realm", LeafBaseType::String);
            checkAndSetLeaf(authentication, xpath + "/authentication", "directory", LeafBaseType::String);
            ConstElementPtr clients = authentication->get("clients");
            setControlSocketAuthenticationClients(xpath + "/authentication/clients", clients);
        }
        ConstElementPtr http_headers = elem->get("http-headers");
        if (http_headers && !http_headers->empty()) {
            setControlSocketHttpHeaders(xpath + "/http-headers", http_headers);
        }
    }
    checkAndSetUserContext(elem, xpath);
}

void
TranslatorControlSocket::setControlSocketAuthenticationClients(string const& xpath,
                                                               ConstElementPtr elem) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }
    for (size_t i = 0; i < elem->size(); ++i) {
        ElementPtr client = elem->getNonConst(i);
        ostringstream key;
        auto user = client->get("user");
        string user_str;
        if (user) {
            user_str = user->stringValue();
        }
        auto password = client->get("password");
        string password_str;
        if (password) {
            password_str = password->stringValue();
        }
        auto user_file = client->get("user-file");
        string user_file_str;
        if (user_file) {
            user_file_str = user_file->stringValue();
        }
        auto password_file = client->get("password-file");
        string password_file_str;
        if (password_file) {
            password_file_str = password_file->stringValue();
        }
        key << xpath << "[user='" << user_str << "'][password='" << password_str
                     << "'][user-file='" << user_file_str << "'][password-file='"
                     << password_file_str << "']";
        setControlSocketAuthenticationClient(key.str(), client);
    }
}

void
TranslatorControlSocket::setControlSocketAuthenticationClient(string const& xpath,
                                                              ConstElementPtr /* elem */) {
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);
}

void
TranslatorControlSocket::setControlSocketHttpHeaders(const std::string& xpath,
                                                     isc::data::ConstElementPtr elem) {
    if (!elem) {
        deleteItem(xpath);
        return;
    }
    for (ConstElementPtr header : elem->listValue()) {
        ConstElementPtr name(header->get("name"));
        if (!name) {
            isc_throw(BadValue, "http header without name: " << header->str());
        }
        ostringstream key;
        key << xpath << "[name='" << name->stringValue() << "']";
        setControlSocketHttpHeader(key.str(), header);
    }
}

void
TranslatorControlSocket::setControlSocketHttpHeader(const std::string& xpath,
                                                    isc::data::ConstElementPtr elem) {
    setItem(xpath, ElementPtr(), LeafBaseType::Unknown);

    checkAndSetLeaf(elem, xpath, "value", LeafBaseType::String);
    checkAndSetUserContext(elem, xpath);
}

}  // namespace yang
}  // namespace isc
