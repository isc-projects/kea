// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
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

// *********************** ControlSocket  *************************

ControlSocket::ControlSocket(Type type, const string& name, const Url& url)
    : type_(type), name_(name), url_(url) {
}

ControlSocket::~ControlSocket() {
}

ControlSocket::Type
ControlSocket::stringToType(const string& type) {
    if (type == "unix") {
        return (ControlSocket::Type::UNIX);
    } else if (type == "http") {
        return (ControlSocket::Type::HTTP);
    } else if (type == "stdout") {
        return (ControlSocket::Type::STDOUT);
    }

    isc_throw(BadValue, "Unknown control socket type: " << type);
}

const string
ControlSocket::typeToString(ControlSocket::Type type) {
    switch (type) {
    case ControlSocket::Type::UNIX:
        return ("unix");
    case ControlSocket::Type::HTTP:
        return ("http");
    case ControlSocket::Type::STDOUT:
        return ("stdout");
    }
    /*UNREACHED*/
}

ElementPtr
ControlSocket::toElement() const {
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

// *********************** Server  *************************
Server::Server(const string& model, ControlSocketPtr ctrl_sock)
    : model_(model), control_socket_(ctrl_sock) {
}

Server::~Server() {
}

string
Server::toText() const {
    ostringstream s;
    s << "model: " << model_ << ", control socker: ";
    if (!control_socket_) {
        s << "none";
    } else {
        switch (control_socket_->getType()) {
        case ControlSocket::Type::UNIX:
            s << "UNIX:'" << control_socket_->getName() << "'";
            break;
        case ControlSocket::Type::HTTP:
          s << "HTTP:'" << control_socket_->getUrl().toText() << "'";
            break;
        case ControlSocket::Type::STDOUT:
            s << "STDOUT";
            break;
        }
    }
    return (s.str());
}

ElementPtr
Server::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set model
    result->set("model", Element::create(model_));
    // Set control-socket
    if (control_socket_) {
        result->set("control-socket", control_socket_->toElement());
    }
    return (result);
}

ostream&
operator<<(ostream& os, const Server& server) {
    os << server.toText();
    return (os);
}

// *************************** PARSERS ***********************************

// *********************** ControlSocketParser  *************************

ControlSocketPtr
ControlSocketParser::parse(ConstElementPtr ctrl_sock_config) {
    ControlSocketPtr result;
    string type_str = getString(ctrl_sock_config, "socket-type");
    string name = getString(ctrl_sock_config, "socket-name");
    string url_str = getString(ctrl_sock_config, "socket-url");
    ConstElementPtr user_context = ctrl_sock_config->get("user-context");

    // Type must be valid.
    ControlSocket::Type type;
    try {
        type = ControlSocket::stringToType(type_str);
    } catch (const std::exception& ex) {
        isc_throw(NetconfCfgError, ex.what() << " '" << type_str << "' ("
                  << getPosition("socket-type", ctrl_sock_config)  << ")");
    }

    // Url must be valid.
    Url url(url_str);
    if (!url.isValid()) {
        isc_throw(NetconfCfgError, "invalid control socket url: "
                  << url.getErrorMessage() << " '" << url_str << "' ("
                  << getPosition("socket-url", ctrl_sock_config)  << ")");
    }

    // Create the control socket.
    try {
        result.reset(new ControlSocket(type, name, url));
    } catch (const std::exception& ex) {
        isc_throw(NetconfCfgError, ex.what() << " ("
                  << ctrl_sock_config->getPosition() << ")");
    }

    // Add user-context.
    if (user_context) {
        result->setContext(user_context);
    }

    return (result);
}

// *********************** ServerParser  *************************

ServerPtr
ServerParser::parse(ConstElementPtr server_config) {
    ServerPtr result;
    string model = getString(server_config, "model");
    ConstElementPtr user_context = server_config->get("user-context");
    ConstElementPtr ctrl_sock_config = server_config->get("control-socket");
    ControlSocketPtr ctrl_sock;
    if (ctrl_sock_config) {
        ControlSocketParser parser;
        ctrl_sock = parser.parse(ctrl_sock_config);
    }
    try {
        result.reset(new Server(model, ctrl_sock));
    } catch (const std::exception& ex) {
        isc_throw(NetconfCfgError, ex.what() << " ("
                  << server_config->getPosition() << ")");
    }

    // Add user-context.
    if (user_context) {
        result->setContext(user_context);
    }

    return (result);
}

}; // end of isc::netconf namespace
}; // end of isc namespace
