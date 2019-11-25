// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <dhcpsrv/shared_network.h>
#include <boost/pointer_cast.hpp>
#include <string>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

SharedNetwork4Parser::SharedNetwork4Parser(bool check_iface)
    : check_iface_(check_iface) {
}

SharedNetwork4Ptr
SharedNetwork4Parser::parse(const data::ConstElementPtr& shared_network_data) {
    SharedNetwork4Ptr shared_network;
    try {

        // Check parameters.
        checkKeywords(SimpleParser4::SHARED_NETWORK4_PARAMETERS,
                      shared_network_data);

        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork4 object.
        std::string name = getString(shared_network_data, "name");
        shared_network.reset(new SharedNetwork4(name));

        // Parse timers.
        NetworkPtr network = boost::dynamic_pointer_cast<Network>(shared_network);
        parseCommonTimers(shared_network_data, network);

        // interface is an optional parameter
        if (shared_network_data->contains("interface")) {
            std::string iface = getString(shared_network_data, "interface");
            if (!iface.empty()) {
                if (check_iface_ && !IfaceMgr::instance().getIface(iface)) {
                    ConstElementPtr error =
                        shared_network_data->get("interface");
                    isc_throw(DhcpConfigError,
                              "Specified network interface name " << iface
                              << " for shared network " << name
                              << " is not present in the system ("
                              << error->getPosition() << ")");
                }
                shared_network->setIface(iface);
            }
        }

        if (shared_network_data->contains("option-data")) {
            auto json = shared_network_data->get("option-data");
            // Create parser instance for option-data.
            CfgOptionPtr cfg_option = shared_network->getCfgOption();
            OptionDataListParser parser(AF_INET);
            parser.parse(cfg_option, json);
        }

        if (shared_network_data->contains("subnet4")) {
            auto json = shared_network_data->get("subnet4");

            // Create parser instance of subnet4.
            Subnets4ListConfigParser parser(check_iface_);
            Subnet4Collection subnets;
            parser.parse(subnets, json);

            // Add all returned subnets into shared network.
            for (auto subnet = subnets.cbegin(); subnet != subnets.cend();
                 ++subnet) {
                shared_network->add(*subnet);
            }
        }

        if (shared_network_data->contains("match-client-id")) {
            shared_network->setMatchClientId(getBoolean(shared_network_data,
                                                        "match-client-id"));
        }

        if (shared_network_data->contains("authoritative")) {
            shared_network->setAuthoritative(getBoolean(shared_network_data,
                                                        "authoritative"));
        }

        // Set next-server
        if (shared_network_data->contains("next-server")) {
            std::string next_server;
            try {
                next_server = getString(shared_network_data, "next-server");
                if (!next_server.empty()) {
                    shared_network->setSiaddr(IOAddress(next_server));
                }
            } catch (...) {
                ConstElementPtr next = shared_network_data->get("next-server");
                std::string pos;
                if (next) {
                    pos = next->getPosition().str();
                } else {
                    pos = shared_network_data->getPosition().str();
                }
                isc_throw(DhcpConfigError, "invalid parameter next-server : "
                          << next_server << "(" << pos << ")");
            }
        }

        // Set server-hostname.
        if (shared_network_data->contains("server-hostname")) {
            std::string sname = getString(shared_network_data, "server-hostname");
            if (!sname.empty()) {
                if (sname.length() >= Pkt4::MAX_SNAME_LEN) {
                    ConstElementPtr error = shared_network_data->get("server-hostname");
                    isc_throw(DhcpConfigError, "server-hostname must be at most "
                              << Pkt4::MAX_SNAME_LEN - 1 << " bytes long, it is "
                              << sname.length() << " ("
                              << error->getPosition() << ")");
                }
                shared_network->setSname(sname);
            }
        }

        // Set boot-file-name.
        if (shared_network_data->contains("boot-file-name")) {
            std::string filename = getString(shared_network_data, "boot-file-name");
            if (!filename.empty()) {
                if (filename.length() > Pkt4::MAX_FILE_LEN) {
                    ConstElementPtr error = shared_network_data->get("boot-file-name");
                    isc_throw(DhcpConfigError, "boot-file-name must be at most "
                              << Pkt4::MAX_FILE_LEN - 1 << " bytes long, it is "
                              << filename.length() << " ("
                              << error->getPosition() << ")");
                }
                shared_network->setFilename(filename);
            }
        }

        if (shared_network_data->contains("client-class")) {
            std::string client_class = getString(shared_network_data, "client-class");
            if (!client_class.empty()) {
                shared_network->allowClientClass(client_class);
            }
        }

        ConstElementPtr user_context = shared_network_data->get("user-context");
        if (user_context) {
            shared_network->setContext(user_context);
        }

        if (shared_network_data->contains("require-client-classes")) {
            const std::vector<data::ElementPtr>& class_list =
                shared_network_data->get("require-client-classes")->listValue();
            for (auto cclass = class_list.cbegin();
                 cclass != class_list.cend(); ++cclass) {
                if (((*cclass)->getType() != Element::string) ||
                    (*cclass)->stringValue().empty()) {
                    isc_throw(DhcpConfigError, "invalid class name ("
                              << (*cclass)->getPosition() << ")");
                }
                shared_network->requireClientClass((*cclass)->stringValue());
            }
        }

        if (shared_network_data->contains("relay")) {
            auto relay_parms = shared_network_data->get("relay");
            if (relay_parms) {
                RelayInfoParser parser(Option::V4);
                Network::RelayInfoPtr relay_info(new Network::RelayInfo());
                parser.parse(relay_info, relay_parms);
                shared_network->setRelayInfo(*relay_info);
            }
        }

        // reservation-mode
        parseHostReservationMode(shared_network_data, network);

        parseTeePercents(shared_network_data, network);

        // Parse DDNS parameters
        parseDdnsParams(shared_network_data, network);
    } catch (const DhcpConfigError&) {
        // Position was already added
        throw;
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << shared_network_data->getPosition() << ")");
    }

    // In order to take advantage of the dynamic inheritance of global
    // parameters to a shared network we need to set a callback function
    // for each shared network to allow for fetching global parameters.
     shared_network->setFetchGlobalsFn([]() -> ConstElementPtr {
        return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
    });

    return (shared_network);
}

SharedNetwork6Parser::SharedNetwork6Parser(bool check_iface)
    : check_iface_(check_iface) {
}

SharedNetwork6Ptr
SharedNetwork6Parser::parse(const data::ConstElementPtr& shared_network_data) {
    SharedNetwork6Ptr shared_network;
    std::string name;
    try {
        // Check parameters.
        checkKeywords(SimpleParser6::SHARED_NETWORK6_PARAMETERS,
                      shared_network_data);

        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork6 object.
        std::string name = getString(shared_network_data, "name");
        shared_network.reset(new SharedNetwork6(name));

        NetworkPtr network = boost::dynamic_pointer_cast<Network>(shared_network);
        parseCommonTimers(shared_network_data, network);

        // preferred-lifetime
        shared_network->setPreferred(parseLifetime(shared_network_data,
                                                   "preferred-lifetime"));

        // Get interface-id option content. For now we support string
        // representation only
        Optional<std::string> ifaceid;
        if (shared_network_data->contains("interface-id")) {
            ifaceid = getString(shared_network_data, "interface-id");
        }

        // Interface is an optional parameter
        Optional<std::string> iface;
        if (shared_network_data->contains("interface")) {
            iface = getString(shared_network_data, "interface");
        }

        // Specifying both interface for locally reachable subnets and
        // interface id for relays is mutually exclusive. Need to test for
        // this condition.
        if (!ifaceid.unspecified() && !iface.unspecified() && !ifaceid.empty() &&
            !iface.empty()) {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "parser error: interface (defined for locally reachable "
                      "subnets) and interface-id (defined for subnets reachable"
                      " via relays) cannot be defined at the same time for "
                      "shared network " << name << "("
                      << shared_network_data->getPosition() << ")");
        }

        // Configure interface-id for remote interfaces, if defined
        if (!ifaceid.unspecified() && !ifaceid.empty()) {
            std::string ifaceid_value = ifaceid.get();
            OptionBuffer tmp(ifaceid_value.begin(), ifaceid_value.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            shared_network->setInterfaceId(opt);
        }

        // Set interface name. If it is defined, then subnets are available
        // directly over specified network interface.
        if (!iface.unspecified() && !iface.empty()) {
            if (check_iface_ && !IfaceMgr::instance().getIface(iface)) {
                ConstElementPtr error = shared_network_data->get("interface");
                isc_throw(DhcpConfigError,
                          "Specified network interface name " << iface
                          << " for shared network " << name
                          << " is not present in the system ("
                          << error->getPosition() << ")");
            }
            shared_network->setIface(iface);
        }

        if (shared_network_data->contains("rapid-commit")) {
            shared_network->setRapidCommit(getBoolean(shared_network_data,
                                                      "rapid-commit"));
        }

        if (shared_network_data->contains("option-data")) {
            auto json = shared_network_data->get("option-data");
            // Create parser instance for option-data.
            CfgOptionPtr cfg_option = shared_network->getCfgOption();
            OptionDataListParser parser(AF_INET6);
            parser.parse(cfg_option, json);
        }

        if (shared_network_data->contains("client-class")) {
            std::string client_class = getString(shared_network_data, "client-class");
            if (!client_class.empty()) {
                shared_network->allowClientClass(client_class);
            }
        }

        ConstElementPtr user_context = shared_network_data->get("user-context");
        if (user_context) {
            shared_network->setContext(user_context);
        }

        if (shared_network_data->contains("require-client-classes")) {
            const std::vector<data::ElementPtr>& class_list =
                shared_network_data->get("require-client-classes")->listValue();
            for (auto cclass = class_list.cbegin();
                 cclass != class_list.cend(); ++cclass) {
                if (((*cclass)->getType() != Element::string) ||
                    (*cclass)->stringValue().empty()) {
                    isc_throw(DhcpConfigError, "invalid class name ("
                              << (*cclass)->getPosition() << ")");
                }
                shared_network->requireClientClass((*cclass)->stringValue());
            }
        }

        if (shared_network_data->contains("subnet6")) {
            auto json = shared_network_data->get("subnet6");

            // Create parser instance of subnet6.
            Subnets6ListConfigParser parser(check_iface_);
            Subnet6Collection subnets;
            parser.parse(subnets, json);

            // Add all returned subnets into shared network.
            for (auto subnet = subnets.cbegin(); subnet != subnets.cend();
                 ++subnet) {
                shared_network->add(*subnet);
            }
        }

        if (shared_network_data->contains("relay")) {
            auto relay_parms = shared_network_data->get("relay");
            if (relay_parms) {
                RelayInfoParser parser(Option::V6);
                Network::RelayInfoPtr relay_info(new Network::RelayInfo());
                parser.parse(relay_info, relay_parms);
                shared_network->setRelayInfo(*relay_info);
            }
        }

        // reservation-mode
        parseHostReservationMode(shared_network_data, network);

        parseTeePercents(shared_network_data, network);

        // Parse DDNS parameters
        parseDdnsParams(shared_network_data, network);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << shared_network_data->getPosition() << ")");
    }

    // In order to take advantage of the dynamic inheritance of global
    // parameters to a shared network we need to set a callback function
    // for each shared network which can be used to fetch global parameters.
     shared_network->setFetchGlobalsFn([]() -> ConstElementPtr {
        return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
    });

    return (shared_network);
}

} // end of namespace isc::dhcp
} // end of namespace isc
