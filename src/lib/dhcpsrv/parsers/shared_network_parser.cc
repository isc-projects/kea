// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_NETWORK_PARSER_H
#define SHARED_NETWORK_PARSER_H

#include <cc/data.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <dhcpsrv/shared_network.h>
#include <boost/pointer_cast.hpp>
#include <string>

using namespace isc::data;

namespace isc {
namespace dhcp {

SharedNetwork4Ptr
SharedNetwork4Parser::parse(const data::ConstElementPtr& shared_network_data) {
    SharedNetwork4Ptr shared_network;
    try {
        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork4 object.
        std::string name = getString(shared_network_data, "name");
        shared_network.reset(new SharedNetwork4(name));

        // interface is an optional parameter
        if (shared_network_data->contains("interface")) {
            shared_network->setIface(getString(shared_network_data, "interface"));
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
            Subnets4ListConfigParser parser;
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

    } catch (const DhcpConfigError&) {
        // Position was already added
        throw;
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << shared_network_data->getPosition() << ")");
    }

    return (shared_network);
}

SharedNetwork6Ptr
SharedNetwork6Parser::parse(const data::ConstElementPtr& shared_network_data) {
    SharedNetwork6Ptr shared_network;
    std::string name;
    try {
        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork6 object.
        std::string name = getString(shared_network_data, "name");
        shared_network.reset(new SharedNetwork6(name));

        // Interface is an optional parameter
        if (shared_network_data->contains("interface")) {
            shared_network->setIface(getString(shared_network_data, "interface"));
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

        if (shared_network_data->contains("subnet6")) {
            auto json = shared_network_data->get("subnet6");

            // Create parser instance of subnet6.
            Subnets6ListConfigParser parser;
            Subnet6Collection subnets;
            parser.parse(subnets, json);

            // Add all returned subnets into shared network.
            for (auto subnet = subnets.cbegin(); subnet != subnets.cend();
                 ++subnet) {
                shared_network->add(*subnet);
            }
        }

    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << shared_network_data->getPosition() << ")");
    }

    return (shared_network);
}

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORK_PARSER_H
