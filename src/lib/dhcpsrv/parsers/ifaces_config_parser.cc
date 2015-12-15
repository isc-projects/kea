// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <boost/foreach.hpp>
#include <string>
#include <sys/types.h>

using namespace isc::data;

namespace isc {
namespace dhcp {

InterfaceListConfigParser::InterfaceListConfigParser(const uint16_t protocol)
    : protocol_(protocol) {
}

void
InterfaceListConfigParser::build(ConstElementPtr value) {
    CfgIfacePtr cfg_iface = CfgMgr::instance().getStagingCfg()->getCfgIface();

    BOOST_FOREACH(ConstElementPtr iface, value->listValue()) {
        std::string iface_name = iface->stringValue();
        try {
            cfg_iface->use(protocol_, iface_name);

        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "Failed to select interface: "
                      << ex.what() << " (" << value->getPosition() << ")");
        }
    }
}

void
InterfaceListConfigParser::commit() {
    // Nothing to do.
}

IfacesConfigParser::IfacesConfigParser(const uint16_t protocol)
    : protocol_(protocol) {
}

void
IfacesConfigParser::build(isc::data::ConstElementPtr ifaces_config) {
    BOOST_FOREACH(ConfigPair element, ifaces_config->mapValue()) {
        try {
            if (element.first == "interfaces") {
                InterfaceListConfigParser parser(protocol_);
                parser.build(element.second);

            } 

        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element.second->getPosition() << ")");
        }
    }
}

bool
IfacesConfigParser::isGenericParameter(const std::string& parameter) const {
    // Currently, the "interfaces" is the only common parameter for
    // DHCPv4 and DHCPv6.
    return (parameter == "interfaces");
}

IfacesConfigParser4::IfacesConfigParser4()
    : IfacesConfigParser(AF_INET) {
}

void
IfacesConfigParser4::build(isc::data::ConstElementPtr ifaces_config) {
    IfacesConfigParser::build(ifaces_config);

    // Get the pointer to the interface configuration.
    CfgIfacePtr cfg = CfgMgr::instance().getStagingCfg()->getCfgIface();
    bool socket_type_specified = false;
    BOOST_FOREACH(ConfigPair element, ifaces_config->mapValue()) {
        try {
            if (element.first == "dhcp-socket-type") {
                cfg->useSocketType(AF_INET, element.second->stringValue());
                socket_type_specified = true;

            } else if (!isGenericParameter(element.first)) {
                isc_throw(DhcpConfigError, "usupported parameter '"
                          << element.first << "'");
            }

        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element.second->getPosition() << ")");
        }
    }

    // User hasn't specified the socket type. Log that we are using
    // the default type.
    if (!socket_type_specified) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_SOCKET_TYPE_DEFAULT)
            .arg(cfg->socketTypeToText());
    }
}

IfacesConfigParser6::IfacesConfigParser6()
    : IfacesConfigParser(AF_INET6) {
}

void
IfacesConfigParser6::build(isc::data::ConstElementPtr ifaces_config) {
    IfacesConfigParser::build(ifaces_config);

    BOOST_FOREACH(ConfigPair element, ifaces_config->mapValue()) {
        try {
            if (!isGenericParameter(element.first)) {
                isc_throw(DhcpConfigError, "usupported parameter '"
                          << element.first << "'");
            }

        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element.second->getPosition() << ")");
        }
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
