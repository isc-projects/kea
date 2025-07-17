// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <asiolink/addr_utilities.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <sys/socket.h>
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::data;

namespace isc {
namespace dhcp {

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
        identifiers_set.insert("client-id");
        identifiers_set.insert("flex-id");
    }
    // Copy identifiers and add all other parameters.
    if (params_set.empty()) {
        params_set = identifiers_set;
        params_set.insert("hostname");
        params_set.insert("ip-address");
        params_set.insert("option-data");
        params_set.insert("next-server");
        params_set.insert("server-hostname");
        params_set.insert("boot-file-name");
        params_set.insert("client-classes");
        params_set.insert("user-context");
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
        identifiers_set.insert("flex-id");
    }
    // Copy identifiers and add all other parameters.
    if (params_set.empty()) {
        params_set = identifiers_set;
        params_set.insert("hostname");
        params_set.insert("ip-addresses");
        params_set.insert("prefixes");
        params_set.insert("excluded-prefixes");
        params_set.insert("option-data");
        params_set.insert("client-classes");
        params_set.insert("user-context");
    }
    return (identifiers_only ? identifiers_set : params_set);
}

/// @brief Extract the prefix from the value specified in
/// the following format: 2001:db8:2000::/64.
///
/// @param prefix Prefix in text format.
/// @param[out] addr Address part of the prefix.
/// @param[out] len Length part of the prefix.
/// @param msg Message to prepend to first error log.
void
parsePrefix(std::string prefix, IOAddress& addr, uint8_t& len, std::string msg) {
    // The slash is mandatory for prefixes. If there is no slash,
    // return an error.
    size_t len_pos  = prefix.find('/');
    if (len_pos == std::string::npos) {
        isc_throw(DhcpConfigError, msg << " requires prefix length "
                  << "be specified in '" << prefix << "'");
    } else if (len_pos >= prefix.length() - 1) {
        // If there is nothing after the slash, we should also
        // report an error.
        isc_throw(DhcpConfigError, "prefix '" <<  prefix
                  << "' requires length after '/'");

    }

    // Convert the prefix length from the string to the number.
    // Note, that we don't use the uint8_t type as the lexical cast
    // would expect a character, e.g. 'a', instead of prefix length,
    // e.g. '64'.
    unsigned int prefix_len = len;
    try {
        prefix_len = boost::lexical_cast<unsigned int>(prefix.substr(len_pos + 1));
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(DhcpConfigError, "prefix length value '"
                  << prefix.substr(len_pos + 1) << "' is invalid");
    }
    if ((prefix_len == 0) || (prefix_len > 128)) {
        isc_throw(OutOfRange,
                  "'prefix-len' value must be in range of [1..128]");
    }
    len = static_cast<uint8_t>(prefix_len);

    // Remove the slash character and the prefix length from the
    // parsed value.
    prefix.erase(len_pos);
    addr = IOAddress(prefix);

    if (len != 128) {
        IOAddress first_address = firstAddrInPrefix(addr, len);
        if (first_address != addr) {
            isc_throw(BadValue, "Prefix address: " << addr
                      << " exceeds prefix/prefix-len pair: " << first_address
                      << "/" << prefix_len);
        }
    }
}

}

HostPtr
HostReservationParser::parse(const SubnetID& subnet_id,
                             isc::data::ConstElementPtr reservation_data,
                             bool encapsulate_options) {
    return (parseInternal(subnet_id, reservation_data, encapsulate_options));
}

HostPtr
HostReservationParser::parseInternal(const SubnetID&,
                                     isc::data::ConstElementPtr reservation_data,
                                     bool) {
    std::string identifier;
    std::string identifier_name;
    std::string hostname;
    ConstElementPtr user_context;
    HostPtr host;

    try {
        // Gather those parameters that are common for both IPv4 and IPv6
        // reservations.
        for (auto const& element : reservation_data->mapValue()) {
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
            } else if (element.first == "user-context") {
                user_context = element.second;
            }
        }

        // Host identifier is a must.
        if (identifier_name.empty()) {
            // If there is no identifier specified, we have to display an
            // error message and include the information what identifiers
            // are supported.
            std::ostringstream s;
            for (auto const& param_name : getSupportedParameters(true)) {
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
        host.reset(new Host(identifier, identifier_name, SUBNET_ID_UNUSED,
                            SUBNET_ID_UNUSED, IOAddress("0.0.0.0"), hostname));

        // Add user context
        if (user_context) {
            host->setContext(user_context);
        }
    } catch (const std::exception& ex) {
        // Append line number where the error occurred.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << reservation_data->getPosition() << ")");
    }

    return (host);
}

bool
HostReservationParser::isIdentifierParameter(const std::string& param_name) const {
    return (getSupportedParameters(true).count(param_name) > 0);
}

bool
HostReservationParser::isSupportedParameter(const std::string& param_name) const {
    return (getSupportedParameters(false).count(param_name) > 0);
}

HostPtr
HostReservationParser4::parseInternal(const SubnetID& subnet_id,
                                      isc::data::ConstElementPtr reservation_data,
                                      bool encapsulate_options) {
    HostPtr host = HostReservationParser::parseInternal(subnet_id, reservation_data,
                                                        encapsulate_options);

    host->setIPv4SubnetID(subnet_id);

    for (auto const& element : reservation_data->mapValue()) {
        // For 'option-data' element we will use another parser which
        // already returns errors with position appended, so don't
        // surround it with try-catch.
        if (element.first == "option-data") {
            CfgOptionPtr cfg_option = host->getCfgOption4();

            // This parser is converted to SimpleParser already. It
            // parses the Element structure immediately, there's no need
            // to go through build/commit phases.
            OptionDataListParser parser(AF_INET);
            parser.parse(cfg_option, element.second, encapsulate_options);

        // Everything else should be surrounded with try-catch to append
        // position.
        } else {
            try {
                if (element.first == "ip-address") {
                    host->setIPv4Reservation(IOAddress(element.second->
                                                        stringValue()));
                } else if (element.first == "next-server") {
                    host->setNextServer(IOAddress(element.second->stringValue()));

                } else if (element.first == "server-hostname") {
                    host->setServerHostname(element.second->stringValue());

                } else if (element.first == "boot-file-name") {
                    host->setBootFileName(element.second->stringValue());

                } else if (element.first == "client-classes") {
                    for (auto const& class_element : element.second->listValue()) {
                        host->addClientClass4(class_element->stringValue());
                    }
                }

            } catch (const std::exception& ex) {
                // Append line number where the error occurred.
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << element.second->getPosition() << ")");
            }
        }
    }

    return (host);
}

const std::set<std::string>&
HostReservationParser4::getSupportedParameters(const bool identifiers_only) const {
    return (getSupportedParams4(identifiers_only));
}

HostPtr
HostReservationParser6::parseInternal(const SubnetID& subnet_id,
                                      isc::data::ConstElementPtr reservation_data,
                                      bool encapsulate_options) {
    HostPtr host = HostReservationParser::parseInternal(subnet_id, reservation_data,
                                                        encapsulate_options);

    host->setIPv6SubnetID(subnet_id);

    ConstElementPtr option_data = reservation_data->get("option-data");
    ConstElementPtr ip_addresses = reservation_data->get("ip-addresses");
    ConstElementPtr prefixes = reservation_data->get("prefixes");
    ConstElementPtr excluded_prefixes = reservation_data->get("excluded-prefixes");
    ConstElementPtr client_classes = reservation_data->get("client-classes");

    // Parse option values. Note that the configuration option parser
    // returns errors with position information appended, so there is no
    // need to surround it with try-clause (and rethrow with position
    // appended).
    if (option_data) {
        CfgOptionPtr cfg_option = host->getCfgOption6();

        // This parser is converted to SimpleParser already. It
        // parses the Element structure immediately, there's no need
        // to go through build/commit phases.
        OptionDataListParser parser(AF_INET6);
        parser.parse(cfg_option, option_data, encapsulate_options);
    }

    if (ip_addresses) {
        for (size_t idx = 0; idx < ip_addresses->size(); ++idx) {
            ConstElementPtr element = ip_addresses->get(idx);
            try {
                // For the IPv6 address the prefix length is 128 and the
                // value specified in the list is a reserved address.
                std::string addr = element->stringValue();
                // Create a reservation for the address.
                host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress(addr), 128));
            } catch (const std::exception& ex) {
                // Append line number where the error occurred.
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << element->getPosition() << ")");
            }
        }
    }

    if (excluded_prefixes) {
        if (!prefixes) {
            isc_throw(DhcpConfigError, "'excluded-prefixes' parameter "
                      "requires the 'prefixes' parameter");
        }
        if (excluded_prefixes->size() != prefixes->size()) {
            isc_throw(DhcpConfigError, "'excluded-prefixes' parameter "
                      "does not match the 'prefixes' parameter: "
                      << excluded_prefixes->size() << " != "
                      << prefixes->size());
        }
    }

    if (prefixes) {
        for (size_t idx = 0; idx < prefixes->size(); ++idx) {
            ConstElementPtr element = prefixes->get(idx);
            try {
                std::string prefix = element->stringValue();
                IOAddress addr("::");
                uint8_t prefix_len(128);
                parsePrefix(prefix, addr, prefix_len, "prefix reservation");
                IPv6Resrv res(IPv6Resrv::TYPE_PD, addr, prefix_len);
                std::string exclude("");
                if (excluded_prefixes) {
                    element = excluded_prefixes->get(idx);
                    exclude = element->stringValue();
                }
                if (!exclude.empty()) {
                    IOAddress excluded_prefix("::");
                    uint8_t excluded_prefix_len(0);
                    parsePrefix(exclude, excluded_prefix, excluded_prefix_len,
                                "exclude prefix");
                    // setPDExclude calls the Option6PDExclude constructor
                    // which throws on invalid prefix.
                    res.setPDExclude(excluded_prefix, excluded_prefix_len);
                }
                host->addReservation(res);
            } catch (const std::exception& ex) {
                // Append line number where the error occurred.
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << element->getPosition() << ")");
            }
        }
    }

    if (client_classes) {
        try {
            for (auto const& class_element : client_classes->listValue()) {
                host->addClientClass6(class_element->stringValue());
            }
        } catch (const std::exception& ex) {
            // Append line number where the error occurred.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << client_classes->getPosition() << ")");
        }
    }

    return (host);
}

const std::set<std::string>&
HostReservationParser6::getSupportedParameters(const bool identifiers_only) const {
    return (getSupportedParams6(identifiers_only));
}

HostReservationIdsParser::HostReservationIdsParser(CfgHostOperationsPtr cfg)
    : staging_cfg_(cfg) {
}

void
HostReservationIdsParser::parse(isc::data::ConstElementPtr ids_list) {
    parseInternal(ids_list);
}

void
HostReservationIdsParser::parseInternal(isc::data::ConstElementPtr ids_list) {
    // Remove existing identifier types.
    staging_cfg_->clearIdentifierTypes();

    for (auto const& element : ids_list->listValue()) {
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

HostReservationIdsParser4::HostReservationIdsParser4(CfgHostOperationsPtr cfg)
    : HostReservationIdsParser(cfg) {
}

bool
HostReservationIdsParser4::isSupportedIdentifier(const std::string& id_name) const {
    return (getSupportedParams4(true).count(id_name) > 0);
}

HostReservationIdsParser6::HostReservationIdsParser6(CfgHostOperationsPtr cfg)
    : HostReservationIdsParser(cfg) {
}

bool
HostReservationIdsParser6::isSupportedIdentifier(const std::string& id_name) const {
    return (getSupportedParams6(true).count(id_name) > 0);
}

} // end of namespace isc::dhcp
} // end of namespace isc
