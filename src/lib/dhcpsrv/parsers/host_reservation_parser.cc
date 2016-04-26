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
#include <algorithm>
#include <sys/socket.h>
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::data;

namespace {

/// @brief Returns set of the supported parameters for DHCPv4.
///
/// This function returns the set of supported parameters for
/// host reservation in DHCPv4.
///
/// @param identifiers_only Indicates if the function should only
/// return supported host identifiers (if true) or all supported
/// parameters (if false).
const std::set<std::string>&
getSupportedParams4(const bool identifiers_only = false) {
    // Holds set of host identifiers.
    static std::set<std::string> identifiers_set;
    // Holds set of all supported parameters, including identifiers.
    static std::set<std::string> params_set;
    // If this is first execution of this function, we need
    // to initialize the set.
    if (identifiers_set.empty()) {
        identifiers_set.insert("hw-address");
        identifiers_set.insert("duid");
        identifiers_set.insert("circuit-id");
    }
    // Copy identifiers and add all other parameters.
    if (params_set.empty()) {
        params_set = identifiers_set;
        params_set.insert("hostname");
        params_set.insert("ip-address");
        params_set.insert("option-data");
    }
    return (identifiers_only ? identifiers_set : params_set);
}

/// @brief Returns set of the supported parameters for DHCPv6.
///
/// This function returns the set of supported parameters for
/// host reservation in DHCPv6.
///
/// @param identifiers_only Indicates if the function should only
/// return supported host identifiers (if true) or all supported
/// parameters (if false).
const std::set<std::string>&
getSupportedParams6(const bool identifiers_only = false) {
    // Holds set of host identifiers.
    static std::set<std::string> identifiers_set;
    // Holds set of all supported parameters, including identifiers.
    static std::set<std::string> params_set;
    // If this is first execution of this function, we need
    // to initialize the set.
    if (identifiers_set.empty()) {
        identifiers_set.insert("hw-address");
        identifiers_set.insert("duid");
    }
    // Copy identifiers and add all other parameters.
    if (params_set.empty()) {
        params_set = identifiers_set;
        params_set.insert("hostname");
        params_set.insert("ip-addresses");
        params_set.insert("prefixes");
        params_set.insert("option-data");
    }
    return (identifiers_only ? identifiers_set : params_set);
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

            if (isIdentifierParameter(element.first)) {
                if (!identifier.empty()) {
                    isc_throw(DhcpConfigError, "the '" << element.first
                              << "' and '" << identifier_name
                              << "' are mutually exclusive");
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
        // Host identifier is a must.
        if (identifier_name.empty()) {
            // If there is no identifier specified, we have to display an
            // error message and include the information what identifiers
            // are supported.
            std::ostringstream s;
            BOOST_FOREACH(std::string param_name, getSupportedParameters(true)) {
                if (s.tellp() != std::streampos(0)) {
                    s << ", ";
                }
                s << param_name;
            }
            isc_throw(DhcpConfigError, "one of the supported identifiers must"
                      " be specified for host reservation: "
                      << s.str());

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

bool
HostReservationParser::isIdentifierParameter(const std::string& param_name) const {
    return (getSupportedParameters(true).count(param_name) > 0);
}

bool
HostReservationParser::isSupportedParameter(const std::string& param_name) const {
    return (getSupportedParameters(false).count(param_name) > 0);
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

const std::set<std::string>&
HostReservationParser4::getSupportedParameters(const bool identifiers_only) const {
    return (getSupportedParams4(identifiers_only));
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

const std::set<std::string>&
HostReservationParser6::getSupportedParameters(const bool identifiers_only) const {
    return (getSupportedParams6(identifiers_only));
}

HostReservationIdsParser::HostReservationIdsParser()
    : staging_cfg_() {
}

void
HostReservationIdsParser::build(isc::data::ConstElementPtr ids_list) {
    // Remove any default configuration.
    staging_cfg_->clear();

    BOOST_FOREACH(ConstElementPtr element, ids_list->listValue()) {
        std::string id_name = element->stringValue();
        try {
            if (id_name != "auto") {
                if (!isSupportedIdentifier(id_name)) {
                    isc_throw(isc::BadValue, "unsupported identifier '"
                              << id_name << "'");
                }
                staging_cfg_->addIdentifierType(id_name);

            } else {
                // 'auto' is mutually exclusive with other values. If there
                // are any values in the configuration already it means that
                // some other values have already been specified.
                if (!staging_cfg_->getIdentifierTypes().empty()) {
                    isc_throw(isc::BadValue, "if 'auto' keyword is used,"
                              " no other values can be specified within '"
                              "host-reservation-identifiers' list");
                }
                // Iterate over all identifier types and for those supported
                // in a given context (DHCPv4 or DHCPv6) add the identifier type
                // to the configuration.
                for (unsigned int i = 0;
                     i <= static_cast<unsigned int>(Host::LAST_IDENTIFIER_TYPE);
                     ++i) {
                    std::string supported_id_name =
                        Host::getIdentifierName(static_cast<Host::IdentifierType>(i));
                    if (isSupportedIdentifier(supported_id_name)) {
                        staging_cfg_->addIdentifierType(supported_id_name);
                    }
                }
            }

        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << element->getPosition() << ")");
        }
    }

    // The parsed list must not be empty.
    if (staging_cfg_->getIdentifierTypes().empty()) {
        isc_throw(DhcpConfigError, "'host-reservation-identifiers' list must not"
                  " be empty (" << ids_list->getPosition() << ")");
    }

}

HostReservationIdsParser4::HostReservationIdsParser4()
    : HostReservationIdsParser() {
    staging_cfg_ = CfgMgr::instance().getStagingCfg()->getCfgHostOperations4();
}

bool
HostReservationIdsParser4::isSupportedIdentifier(const std::string& id_name) const {
    return (getSupportedParams4(true).count(id_name) > 0);
}

HostReservationIdsParser6::HostReservationIdsParser6()
    : HostReservationIdsParser() {
    staging_cfg_ = CfgMgr::instance().getStagingCfg()->getCfgHostOperations6();
}

bool
HostReservationIdsParser6::isSupportedIdentifier(const std::string& id_name) const {
    return (getSupportedParams6(true).count(id_name) > 0);
}

} // end of namespace isc::dhcp
} // end of namespace isc
