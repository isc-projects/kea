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
    std::string name;
    try {
        // Shared network is a map.
        const auto& element = shared_network_data->mapValue();

        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork4 object.
        const auto& name_it = element.find("name");
        if (name_it == element.cend()) {
            isc_throw(DhcpConfigError, "parameter \"name\" must be specified for"
                      " a shared network");

        }
        shared_network.reset(new SharedNetwork4(name_it->second->stringValue()));

        // Iterate over all parameters within the map and assign them to the
        // shared network.
        for (auto param = element.cbegin(); param != element.cend(); ++param) {
            if (param->first == "interface") {
                shared_network->setIface(param->second->stringValue());

            } else if (param->first == "option-data") {
                // Create parser instance for option-data.
                CfgOptionPtr cfg_option = shared_network->getCfgOption();
                OptionDataListParser parser(AF_INET);
                parser.parse(cfg_option, param->second);

            } else if (param->first == "subnet4") {
                // Create parser instance of subnet4.
                Subnets4ListConfigParser parser;
                Subnet4Collection subnets;
                parser.parse(subnets, param->second);

                // Add all returned subnets into shared network.
                for (auto subnet = subnets.cbegin(); subnet != subnets.cend();
                     ++subnet) {
                    shared_network->add(*subnet);
                }
            }
        }

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
        // Shared network is a map.
        const auto& element = shared_network_data->mapValue();

        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork6 object.
        const auto& name_it = element.find("name");
        if (name_it == element.cend()) {
            isc_throw(DhcpConfigError, "parameter \"name\" must be specified for"
                      " a shared network");

        }
        shared_network.reset(new SharedNetwork6(name_it->second->stringValue()));

        // Iterate over all parameters within the map and assign them to the
        // shared network.
        for (auto param = element.cbegin(); param != element.cend(); ++param) {
            if (param->first == "interface") {
                shared_network->setIface(param->second->stringValue());

            } else if (param->first == "option-data") {
                // Create parser instance for option-data.
                CfgOptionPtr cfg_option = shared_network->getCfgOption();
                OptionDataListParser parser(AF_INET6);
                parser.parse(cfg_option, param->second);

            } else if (param->first == "subnet6") {
                // Create parser instance of subnet6.
                Subnets6ListConfigParser parser;
                Subnet6Collection subnets;
                parser.parse(subnets, param->second);

                // Add all returned subnets into shared network.
                for (auto subnet = subnets.cbegin(); subnet != subnets.cend();
                     ++subnet) {
                    shared_network->add(*subnet);
                }
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
