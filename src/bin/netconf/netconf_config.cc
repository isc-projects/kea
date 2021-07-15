// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/netconf_log.h>
#include <netconf/netconf_cfg_mgr.h>
#include <exceptions/exceptions.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <sstream>
#include <string>

using namespace std;
using namespace isc::process;
using namespace isc::data;
using namespace isc::http;

namespace isc {
namespace netconf {

// *********************** CfgControlSocket  *************************

CfgControlSocket::CfgControlSocket(Type type, const string& name,
                                   const Url& url)
    : type_(type), name_(name), url_(url) {
}

CfgControlSocket::Type
CfgControlSocket::stringToType(const string& type) {
    if (type == "unix") {
        return (CfgControlSocket::Type::UNIX);
    } else if (type == "http") {
        return (CfgControlSocket::Type::HTTP);
    } else if (type == "stdout") {
        return (CfgControlSocket::Type::STDOUT);
    }

    isc_throw(BadValue, "Unknown control socket type: " << type);
}

const string
CfgControlSocket::typeToString(CfgControlSocket::Type type) {
    switch (type) {
    case CfgControlSocket::Type::UNIX:
        return ("unix");
    case CfgControlSocket::Type::HTTP:
        return ("http");
    case CfgControlSocket::Type::STDOUT:
        return ("stdout");
    default:
        isc_throw(BadValue, "Unknown control socket type: " << type);
    }
}

ElementPtr
CfgControlSocket::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set type
    result->set("socket-type", Element::create(typeToString(type_)));
    // Set name
    result->set("socket-name", Element::create(name_));
    // Set url
    result->set("socket-url", Element::create(url_.toText()));
    return (result);
}

// *********************** CfgServer  *************************
CfgServer::CfgServer(const string& model, CfgControlSocketPtr ctrl_sock)
    : model_(model), boot_update_(true), subscribe_changes_(true),
      subscribe_notifications_(true), validate_changes_(true),
      control_socket_(ctrl_sock) {
}

string
CfgServer::toText() const {
    ostringstream s;
    s << "model: " << model_ << ", control socker: ";
    if (!control_socket_) {
        s << "none";
    } else {
        switch (control_socket_->getType()) {
        case CfgControlSocket::Type::UNIX:
            s << "UNIX:'" << control_socket_->getName() << "'";
            break;
        case CfgControlSocket::Type::HTTP:
          s << "HTTP:'" << control_socket_->getUrl().toText() << "'";
            break;
        case CfgControlSocket::Type::STDOUT:
            s << "STDOUT";
            break;
        }
    }
    return (s.str());
}

ElementPtr
CfgServer::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set model
    result->set("model", Element::create(model_));
    // Set boot-update
    result->set("boot-update", Element::create(boot_update_));
    // Set subscribe-changes
    result->set("subscribe-changes", Element::create(subscribe_changes_));
    // Set validate-changes
    result->set("validate-changes", Element::create(validate_changes_));
    // Set control-socket
    if (control_socket_) {
        result->set("control-socket", control_socket_->toElement());
    }
    return (result);
}

ostream&
operator<<(ostream& os, const CfgServer& server) {
    os << server.toText();
    return (os);
}

// *************************** PARSERS ***********************************

// *********************** ControlSocketConfigParser  *************************

CfgControlSocketPtr
ControlSocketConfigParser::parse(ConstElementPtr ctrl_sock_config) {
    CfgControlSocketPtr result;
    string type_str = getString(ctrl_sock_config, "socket-type");
    string name = getString(ctrl_sock_config, "socket-name");
    string url_str = getString(ctrl_sock_config, "socket-url");
    ConstElementPtr user_context = ctrl_sock_config->get("user-context");

    // Type must be valid.
    CfgControlSocket::Type type;
    try {
        type = CfgControlSocket::stringToType(type_str);
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what() << " '" << type_str << "' ("
                  << getPosition("socket-type", ctrl_sock_config)  << ")");
    }

    // Url must be valid.
    Url url(url_str);
    if (!url.isValid()) {
        isc_throw(ConfigError, "invalid control socket url: "
                  << url.getErrorMessage() << " '" << url_str << "' ("
                  << getPosition("socket-url", ctrl_sock_config)  << ")");
    }

    // Create the control socket.
    try {
        result.reset(new CfgControlSocket(type, name, url));
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what() << " ("
                  << ctrl_sock_config->getPosition() << ")");
    }

    // Add user-context.
    if (user_context) {
        result->setContext(user_context);
    }

    return (result);
}

// *********************** ServerConfigParser  *************************

CfgServerPtr
ServerConfigParser::parse(ConstElementPtr server_config) {
    CfgServerPtr result;
    string model = getString(server_config, "model");
    ConstElementPtr user_context = server_config->get("user-context");
    ConstElementPtr ctrl_sock_config = server_config->get("control-socket");
    CfgControlSocketPtr ctrl_sock;
    if (ctrl_sock_config) {
        ControlSocketConfigParser parser;
        ctrl_sock = parser.parse(ctrl_sock_config);
    }
    try {
        result.reset(new CfgServer(model, ctrl_sock));
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what() << " ("
                  << server_config->getPosition() << ")");
    }

    // Add flags.
    result->setBootUpdate(getBoolean(server_config, "boot-update"));
    result->setSubscribeChanges(getBoolean(server_config, "subscribe-changes"));
    result->setValidateChanges(getBoolean(server_config, "validate-changes"));

    // Add user-context.
    if (user_context) {
        result->setContext(user_context);
    }

    return (result);
}

}  // namespace netconf
}  // namespace isc
