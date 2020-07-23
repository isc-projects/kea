// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
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

void
IfacesConfigParser::parseInterfacesList(const CfgIfacePtr& cfg_iface,
                                        ConstElementPtr ifaces_list) {
    BOOST_FOREACH(ConstElementPtr iface, ifaces_list->listValue()) {
        std::string iface_name = iface->stringValue();
        try {
            cfg_iface->use(protocol_, iface_name);

        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "Failed to select interface: "
                      << ex.what() << " (" << iface->getPosition() << ")");
        }
    }
}

IfacesConfigParser::IfacesConfigParser(const uint16_t protocol, bool test_mode)
    : protocol_(protocol), test_mode_(test_mode) {
}

void
IfacesConfigParser::parse(const CfgIfacePtr& cfg,
                          const isc::data::ConstElementPtr& ifaces_config) {

    // Check for re-detect before calling parseInterfacesList()
    bool re_detect = getBoolean(ifaces_config, "re-detect");
    cfg->setReDetect(re_detect);
    if (re_detect && !test_mode_) {
        IfaceMgr::instance().clearIfaces();
        IfaceMgr::instance().detectIfaces();
    }

    bool socket_type_specified = false;
    BOOST_FOREACH(ConfigPair element, ifaces_config->mapValue()) {
        try {
            if (element.first == "re-detect") {
                continue;
            }

            if (element.first == "interfaces") {
                parseInterfacesList(cfg, element.second);
                continue;

            }

            if (element.first == "dhcp-socket-type") {
                if (protocol_ == AF_INET) {
                    cfg->useSocketType(AF_INET, element.second->stringValue());
                    socket_type_specified = true;
                    continue;
                } else {
                    isc_throw(DhcpConfigError,
                              "dhcp-socket-type is not supported in DHCPv6");
                }
            }

            if (element.first == "outbound-interface") {
                if (protocol_ == AF_INET) {
                    CfgIface::OutboundIface type =
                        CfgIface::textToOutboundIface(element.second->stringValue());
                    cfg->setOutboundIface(type);
                    continue;
                } else {
                    isc_throw(DhcpConfigError,
                              "outbound-interface is not supported in DHCPv6");
                }
            }

            if (element.first == "user-context") {
                cfg->setContext(element.second);
                continue;
            }

            // This should never happen as the input produced by the parser
            // see (src/bin/dhcpX/dhcpX_parser.yy) should not produce any
            // other parameter, so this case is only to catch bugs in
            // the parser.
            isc_throw(DhcpConfigError, "unsupported parameter '"
                      << element.first << "'");
        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element.second->getPosition() << ")");
        }
    }

    // User hasn't specified the socket type. Log that we are using
    // the default type. Log it only if this is DHCPv4. (DHCPv6 does not use
    // raw sockets).
    if (!socket_type_specified && (protocol_ == AF_INET) ) {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_SOCKET_TYPE_DEFAULT)
            .arg(cfg->socketTypeToText());
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
