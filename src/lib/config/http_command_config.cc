// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/dhcp_config_error.h>
#include <config/http_command_config.h>
#include <http/basic_auth_config.h>
#include <limits>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::http;
using namespace std;

namespace isc {
namespace config {

IOAddress HttpCommandConfig::DEFAULT_SOCKET_ADDRESS = IOAddress("127.0.0.1");

uint16_t HttpCommandConfig::DEFAULT_SOCKET_PORT = 8000;

string HttpCommandConfig::DEFAULT_AUTHENTICATION_REALM = "";

HttpCommandConfig::HttpCommandConfig(ConstElementPtr config)
    : socket_type_("http"), socket_address_(DEFAULT_SOCKET_ADDRESS),
      socket_port_(DEFAULT_SOCKET_PORT), auth_config_(),
      trust_anchor_(""), cert_file_(""), key_file_(""), cert_required_(true),
      emulate_agent_response_(true) {
    if (config->getType() != Element::map) {
        isc_throw(DhcpConfigError, "expected map type ("
                  << config->getPosition() << ")");
    }
    // Get socket type.
    ConstElementPtr socket_type = config->get("socket-type");
    if (socket_type) {
        if (socket_type->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'socket_type' ("
                      << socket_type->getPosition() << ")");
        }
        socket_type_ = socket_type->stringValue();
        if ((socket_type_ != "http") && (socket_type_ != "https")) {
            isc_throw(DhcpConfigError, "unsupported 'socket-type' '"
                      << socket_type_ << "' not 'http' or 'https'");
        }
    }

    // Get socket address.
    ConstElementPtr socket_name = config->get("socket-name");
    ConstElementPtr socket_address = config->get("socket-address");
    if (socket_name) {
        // socket-name is an alias of socket-address.
        if (socket_address) {
            isc_throw(DhcpConfigError,
                      "specify both 'socket-name' and 'socket-address' "
                      "is forbidden");
        }
        socket_address = socket_name;
    }
    if (socket_address) {
        if (socket_address->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'socket-"
                      << (socket_name ? "name" : "address") << "' ("
                      << socket_address->getPosition() << ")");
        }
        try {
            socket_address_ = IOAddress(socket_address->stringValue());
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "failed to convert '"
                      << socket_address->stringValue()
                      << "' to address: " << ex.what()
                      << " (" << socket_address->getPosition() << ")");
        }
    }

    // Get socket port.
    ConstElementPtr socket_port = config->get("socket-port");
    if (socket_port) {
        if (socket_port->getType() != Element::integer) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'socket-port' ("
                      << socket_port->getPosition() << ")");
        }
        int64_t value = socket_port->intValue();
        if ((value < numeric_limits<uint16_t>::min()) ||
            (value > numeric_limits<uint16_t>::max())) {
            isc_throw(DhcpConfigError,
                      "out of range value " << value
                      << " specified for parameter 'socket-port' ("
                      << socket_port->getPosition() << ")");
        }
        socket_port_ = static_cast<uint16_t>(value);
    }

    // Get HTTP authentication.
    ConstElementPtr auth_config = config->get("authentication");
    if (auth_config) {
        ElementPtr mutable_auth_config =
            boost::const_pointer_cast<Element>(auth_config);
        if (auth_config->getType() != Element::map) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'authentication' ("
                      << auth_config->getPosition() << ")");
        }
        // Default type is basic.
        ConstElementPtr type = auth_config->get("type");
        if (!type) {
            mutable_auth_config->set("type", Element::create(string("basic")));
        }
        // Set default realm when not present.
        ConstElementPtr realm = auth_config->get("realm");
        if (!realm) {
            mutable_auth_config->set("realm",
                Element::create(DEFAULT_AUTHENTICATION_REALM));
        }

        BasicHttpAuthConfigPtr auth(new BasicHttpAuthConfig());
        auth->parse(auth_config);
        auth_config_ = auth;
    }

    // Get trust anchor.
    ConstElementPtr trust_anchor = config->get("trust-anchor");
    if (trust_anchor) {
        if (trust_anchor->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'trust-anchor' ("
                      << trust_anchor->getPosition() << ")");
        }
        trust_anchor_ = trust_anchor->stringValue();
    }

    // Get cert file.
    ConstElementPtr cert_file = config->get("cert-file");
    if (cert_file) {
        if (cert_file->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'cert-file' ("
                      << cert_file->getPosition() << ")");
        }
        cert_file_ = cert_file->stringValue();
    }

    // Get key file.
    ConstElementPtr key_file = config->get("key-file");
    if (key_file) {
        if (key_file->getType() != Element::string) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'key-file' ("
                      << key_file->getPosition() << ")");
        }
        key_file_ = key_file->stringValue();
    }

    // Get cert required.
    ConstElementPtr cert_required = config->get("cert-required");
    if (cert_required) {
        if (cert_required->getType() != Element::boolean) {
            isc_throw(DhcpConfigError,
                      "invalid type specified for parameter 'cert-required' ("
                      << cert_required->getPosition() << ")");
        }
        cert_required_ = cert_required->boolValue();
    }

    // Check the TLS setup.
    checkTlsSetup(socket_type_ == "https");

    // Get user context.
    ConstElementPtr user_context = config->get("user-context");
    if (user_context) {
        setContext(user_context);
    }
}

void
HttpCommandConfig::checkTlsSetup(bool require_tls) const {
    bool have_ca = !trust_anchor_.empty();
    bool have_cert = !cert_file_.empty();
    bool have_key = !key_file_.empty();
    if (!have_ca && !have_cert && !have_key) {
        if (require_tls) {
            isc_throw(DhcpConfigError,
                      "no TLS setup for a HTTPS control socket");
        }
        return;
    }
    // TLS is used: all 3 parameters are required.
    if (!have_ca) {
        isc_throw(DhcpConfigError,
                  "trust-anchor parameter is missing or empty:"
                  " all or none of TLS parameters must be set");
    }
    if (!have_cert) {
        isc_throw(DhcpConfigError, "cert-file parameter is missing or empty:"
                  " all or none of TLS parameters must be set");
    }
    if (!have_key) {
        isc_throw(DhcpConfigError, "key-file parameter is missing or empty:"
                  " all or none of TLS parameters must be set");
    }
}

ElementPtr
HttpCommandConfig::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context.
    contextToElement(result);
    // Set socket type.
    result->set("socket-type", Element::create(socket_type_));
    // Set socket address.
    result->set("socket-address", Element::create(socket_address_.toText()));
    // Set socket port.
    result->set("socket-port",
                Element::create(static_cast<uint32_t>(socket_port_)));
    /// Set authentication.
    if (auth_config_) {
        result->set("authentication", auth_config_->toElement());
    }
    // Set TLS setup when enabled.
    if (!trust_anchor_.empty()) {
        result->set("trust-anchor", Element::create(trust_anchor_));
        result->set("cert-file", Element::create(cert_file_));
        result->set("key-file", Element::create(key_file_));
        result->set("cert-required", Element::create(cert_required_));
    }
    return (result);
}

} // end of isc::config
} // end of isc
