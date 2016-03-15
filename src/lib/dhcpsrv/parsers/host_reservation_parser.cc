// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <sys/socket.h>
#include <string>

using namespace isc::asiolink;
using namespace isc::data;

namespace {

/// @brief Returns set of the supported parameters for DHCPv4.
///
/// This function returns the set of supported parameters for
/// host reservation in DHCPv4.
const std::set<std::string>& getSupportedParams4() {
    static std::set<std::string> params_set;
    if (params_set.empty()) {
        const char* params[] = {
            "duid", "hw-address", "hostname", "ip-address",
            "option-data", NULL
        };
        for (int i = 0; params[i] != NULL; ++i) {
            params_set.insert(std::string(params[i]));
        }
    }
    return (params_set);
}

/// @brief Returns set of the supported parameters for DHCPv4.
///
/// This function returns the set of supported parameters for
/// host reservation in DHCPv6.
const std::set<std::string>& getSupportedParams6() {
    static std::set<std::string> params_set;
    if (params_set.empty()) {
        const char* params[] = {
            "duid", "hw-address", "hostname", "ip-addresses", "prefixes",
            "option-data", NULL
        };
        for (int i = 0; params[i] != NULL; ++i) {
            params_set.insert(std::string(params[i]));
        }
    }
    return (params_set);
}

}

namespace isc {
namespace dhcp {

HostReservationParser::HostReservationParser(const SubnetID& subnet_id)
    : DhcpConfigParser(), subnet_id_(subnet_id) {
}

void
HostReservationParser::build(isc::data::ConstElementPtr reservation_data) {
    std::string identifier;
    std::string identifier_name;
    std::string hostname;

    // Gather those parameters that are common for both IPv4 and IPv6
    // reservations.
    BOOST_FOREACH(ConfigPair element, reservation_data->mapValue()) {
        try {
            // Check if we support this parameter.
            if (!isSupportedParameter(element.first)) {
                isc_throw(DhcpConfigError, "unsupported configuration"
                          " parameter '" << element.first << "'");
            }

            if (element.first == "hw-address" || element.first == "duid") {
                if (!identifier_name.empty()) {
                    isc_throw(DhcpConfigError, "the 'hw-address' and 'duid'"
                              " parameters are mutually exclusive");
                }
                identifier = element.second->stringValue();
                identifier_name = element.first;

            } else if (element.first == "hostname") {
                hostname = element.second->stringValue();

            }
        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element.second->getPosition() << ")");
        }
    }

    try {
        // hw-address or duid is a must.
        if (identifier_name.empty()) {
            isc_throw(DhcpConfigError, "'hw-address' or 'duid' is a required"
                      " parameter for host reservation");
        }

        // Create a host object from the basic parameters we already parsed.
        host_.reset(new Host(identifier, identifier_name, SubnetID(0),
                             SubnetID(0), IOAddress("0.0.0.0"), hostname));

    } catch (const std::exception& ex) {
        // Append line number where the error occurred.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << reservation_data->getPosition() << ")");
    }
}

void
HostReservationParser::addHost(isc::data::ConstElementPtr reservation_data) {
    try {
        CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(host_);

    } catch (const std::exception& ex) {
        // Append line number to the exception string.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << reservation_data->getPosition() << ")");
    }
}

HostReservationParser4::HostReservationParser4(const SubnetID& subnet_id)
    : HostReservationParser(subnet_id) {
}

void
HostReservationParser4::build(isc::data::ConstElementPtr reservation_data) {
    HostReservationParser::build(reservation_data);

    host_->setIPv4SubnetID(subnet_id_);

    BOOST_FOREACH(ConfigPair element, reservation_data->mapValue()) {
        // For 'option-data' element we will use another parser which
        // already returns errors with position appended, so don't
        // surround it with try-catch.
        if (element.first == "option-data") {
            CfgOptionPtr cfg_option = host_->getCfgOption4();
            OptionDataListParser parser(element.first, cfg_option, AF_INET);
            parser.build(element.second);

       // Everything else should be surrounded with try-catch to append
       // position.
        } else {
            try {
                if (element.first == "ip-address") {
                    host_->setIPv4Reservation(IOAddress(element.second->
                                                        stringValue()));
                }
            } catch (const std::exception& ex) {
                // Append line number where the error occurred.
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << reservation_data->getPosition() << ")");
            }
        }
    }

    addHost(reservation_data);
}

bool
HostReservationParser4::isSupportedParameter(const std::string& param_name) const {
    return (getSupportedParams4().count(param_name) > 0);
}

HostReservationParser6::HostReservationParser6(const SubnetID& subnet_id)
    : HostReservationParser(subnet_id) {
}

void
HostReservationParser6::build(isc::data::ConstElementPtr reservation_data) {
    HostReservationParser::build(reservation_data);

    host_->setIPv6SubnetID(subnet_id_);

    BOOST_FOREACH(ConfigPair element, reservation_data->mapValue()) {
        // Parse option values. Note that the configuration option parser
        // returns errors with position information appended, so there is no
        // need to surround it with try-clause (and rethrow with position
        // appended).
        if (element.first == "option-data") {
            CfgOptionPtr cfg_option = host_->getCfgOption6();
            OptionDataListParser parser(element.first, cfg_option, AF_INET6);
            parser.build(element.second);

        } else if (element.first == "ip-addresses" || element.first == "prefixes") {
            BOOST_FOREACH(ConstElementPtr prefix_element,
                          element.second->listValue()) {
                try {
                    // For the IPv6 address the prefix length is 128 and the
                    // value specified in the list is a reserved address.
                    IPv6Resrv::Type resrv_type = IPv6Resrv::TYPE_NA;
                    std::string prefix = prefix_element->stringValue();
                    uint8_t prefix_len = 128;

                    // If we're dealing with prefixes, instead of addresses,
                    // we will have to extract the prefix length from the value
                    // specified in the following format: 2001:db8:2000::/64.
                    if (element.first == "prefixes") {
                        // The slash is mandatory for prefixes. If there is no
                        // slash, return an error.
                        size_t len_pos  = prefix.find('/');
                        if (len_pos == std::string::npos) {
                            isc_throw(DhcpConfigError, "prefix reservation"
                                      " requires prefix length be specified"
                                      " in '" << prefix << "'");

                        // If there is nothing after the slash, we should also
                        // report an error.
                        } else if (len_pos >= prefix.length() - 1) {
                            isc_throw(DhcpConfigError, "prefix '" <<  prefix
                                      << "' requires length after '/'");

                        }

                        // Convert the prefix length from the string to the
                        // number. Note, that we don't use the uint8_t type
                        // as the lexical cast would expect a chracter, e.g.
                        // 'a', instead of prefix length, e.g. '64'.
                        try {
                            prefix_len = boost::lexical_cast<
                                unsigned int>(prefix.substr(len_pos + 1));

                        } catch (const boost::bad_lexical_cast&) {
                            isc_throw(DhcpConfigError, "prefix length value '"
                                      << prefix.substr(len_pos + 1)
                                      << "' is invalid");
                        }

                        // Remove the  slash character and the prefix length
                        // from the parsed value.
                        prefix.erase(len_pos);

                        // Finally, set the reservation type.
                        resrv_type = IPv6Resrv::TYPE_PD;
                    }

                    // Create a reservation for an address or prefix.
                    host_->addReservation(IPv6Resrv(resrv_type,
                                                    IOAddress(prefix),
                                                    prefix_len));

                } catch (const std::exception& ex) {
                    // Append line number where the error occurred.
                    isc_throw(DhcpConfigError, ex.what() << " ("
                              << prefix_element->getPosition() << ")");
                }
            }
        }
    }

    // This may fail, but the addHost function will handle this on its own.
    addHost(reservation_data);
}

bool
HostReservationParser6::isSupportedParameter(const std::string& param_name) const {
    return (getSupportedParams6().count(param_name) > 0);
}

} // end of namespace isc::dhcp
} // end of namespace isc
