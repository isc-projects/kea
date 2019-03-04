// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_NETWORK_PARSER_H
#define SHARED_NETWORK_PARSER_H

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <dhcpsrv/shared_network.h>
#include <util/optional.h>
#include <boost/pointer_cast.hpp>
#include <string>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

void
SharedNetworkParser::parseCommonTimers(const ConstElementPtr& shared_network_data,
                                       NetworkPtr& network) {
    Triplet<uint32_t> t1;
    if (shared_network_data->contains("renew-timer")) {
        network->setT1(getInteger(shared_network_data, "renew-timer"));
    }

    Triplet<uint32_t> t2;
    if (shared_network_data->contains("rebind-timer")) {
        network->setT2(getInteger(shared_network_data, "rebind-timer"));
    }

    Triplet<uint32_t> valid;
    if (shared_network_data->contains("valid-lifetime")) {
        network->setValid(getInteger(shared_network_data, "valid-lifetime"));
    }
}

void
SharedNetworkParser::parseTeePercents(const ConstElementPtr& shared_network_data,
                                      NetworkPtr& network) {
    bool calculate_tee_times = network->getCalculateTeeTimes();
    if (shared_network_data->contains("calculate-tee-times")) {
        bool calculate_tee_times = getBoolean(shared_network_data, "calculate-tee-times");
        network->setCalculateTeeTimes(calculate_tee_times);
    }

    Optional<double> t2_percent;
    if (shared_network_data->contains("t2-percent")) {
        t2_percent = getDouble(shared_network_data, "t2-percent");
    }

    Optional<double> t1_percent;
    if (shared_network_data->contains("t1-percent")) {
        t1_percent = getDouble(shared_network_data, "t1-percent");
    }
    if (calculate_tee_times) {
        if (!t2_percent.unspecified() && ((t2_percent.get() <= 0.0) ||
                                          (t2_percent.get() >= 1.0))) {
            isc_throw(DhcpConfigError, "t2-percent:  " << t2_percent.get()
                      << " is invalid, it must be greater than 0.0 and less than 1.0");
        }

        if (!t1_percent.unspecified() && ((t1_percent.get() <= 0.0) ||
                                          (t1_percent.get() >= 1.0))) {
            isc_throw(DhcpConfigError, "t1-percent:  " << t1_percent.get()
                      << " is invalid it must be greater than 0.0 and less than 1.0");
        }

        if (!t1_percent.unspecified() && !t2_percent.unspecified() &&
            (t1_percent.get() >= t2_percent.get())) {
            isc_throw(DhcpConfigError, "t1-percent:  " << t1_percent.get()
                      << " is invalid, it must be less than t2-percent: "
                      << t2_percent.get());
        }
    }

    network->setT2Percent(t2_percent);
    network->setT1Percent(t1_percent);
}

SharedNetwork4Ptr
SharedNetwork4Parser::parse(const data::ConstElementPtr& shared_network_data) {
    SharedNetwork4Ptr shared_network;
    try {

        // Make sure that the network name has been specified. The name is required
        // to create a SharedNetwork4 object.
        std::string name = getString(shared_network_data, "name");
        shared_network.reset(new SharedNetwork4(name));

        // Parse timers.
        NetworkPtr network = boost::dynamic_pointer_cast<Network>(shared_network);
        parseCommonTimers(shared_network_data, network);

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

        if (shared_network_data->contains("authoritative")) {
            shared_network->setAuthoritative(getBoolean(shared_network_data,
                                                        "authoritative"));
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

        parseTeePercents(shared_network_data, network);

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

        NetworkPtr network = boost::dynamic_pointer_cast<Network>(shared_network);
        parseCommonTimers(shared_network_data, network);

        // preferred-lifetime
        Triplet<uint32_t> preferred;
        if (shared_network_data->contains("preferred-lifetime")) {
            shared_network->setPreferred(getInteger(shared_network_data,
                                                    "preferred-lifetime"));
        }

        // Interface is an optional parameter
        if (shared_network_data->contains("interface")) {
            shared_network->setIface(getString(shared_network_data, "interface"));
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
            Subnets6ListConfigParser parser;
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

        parseTeePercents(shared_network_data, network);

    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << shared_network_data->getPosition() << ")");
    }

    return (shared_network);
}

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_NETWORK_PARSER_H
