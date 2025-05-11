// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_asio_socket.h>
#include <cc/dhcp_config_error.h>
#include <config/command_mgr.h>
#include <config/unix_command_config.h>
#include <limits>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace config {

UnixCommandConfig::UnixCommandConfig(ConstElementPtr config)
    : socket_type_("unix"), socket_name_() {
    if (config->getType() != Element::map) {
        isc_throw(DhcpConfigError, "expected map type ("
                  << config->getPosition() << ")");
    }
    // Get socket type.
    ConstElementPtr socket_type = config->get("socket-type");
    if (socket_type) {
        if (socket_type->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'socket-type' ("
                      << socket_type->getPosition() << ")");
        }
        socket_type_ = socket_type->stringValue();
        if ((socket_type_ != "unix")) {
            isc_throw(DhcpConfigError, "unsupported 'socket-type' '"
                      << socket_type_ << "' not 'unix'");
        }
    }
    // Reject HTTP/HTTPS only socket-address.
    if (config->contains("socket-address")) {
        isc_throw(DhcpConfigError,
                  "parameter 'socket-address' is not supported by UNIX "
                  "control sockets");
    }
    // Get socket name.
    ConstElementPtr socket_name = config->get("socket-name");
    if (socket_name) {
        if (socket_name->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'socket-name' ("
                      << socket_name->getPosition() << ")");
        }
        socket_name_ = socket_name->stringValue();
    } else {
        isc_throw(BadSocketInfo, "Mandatory 'socket-name' parameter missing");
    }

    // Get user context.
    ConstElementPtr user_context = config->get("user-context");
    if (user_context) {
        setContext(user_context);
    }
}

ElementPtr
UnixCommandConfig::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context.
    contextToElement(result);
    // Set socket type.
    result->set("socket-type", Element::create(socket_type_));
    // Set socket name.
    result->set("socket-name", Element::create(socket_name_));
    return (result);
}

} // end of isc::config
} // end of isc
