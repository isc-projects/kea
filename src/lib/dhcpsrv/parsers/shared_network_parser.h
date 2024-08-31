// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHARED_SUBNET_PARSER_H
#define SHARED_SUBNET_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Implements parser for IPv4 shared networks.
class SharedNetwork4Parser : public BaseNetworkParser {
public:
    /// @brief Constructor.
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    SharedNetwork4Parser(bool check_iface = true);

    /// @brief Virtual destructor.
    virtual ~SharedNetwork4Parser() {
    }

    /// @brief Parses shared configuration information for IPv4 shared network.
    ///
    /// @param shared_network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @return Pointer to an object representing shared network.
    /// @throw DhcpConfigError when shared network configuration is invalid.
    SharedNetwork4Ptr
    parse(const data::ConstElementPtr& shared_network_data,
          bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @return an instance of the @c OptionDataListParser(AF_INET).
    virtual boost::shared_ptr<OptionDataListParser> createOptionDataListParser() const;

    /// @brief Returns an instance of the @c Subnets4ListConfigParser
    /// to be used for parsing the subnets within the shared network.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the subnets.
    ///
    /// @return an instance of the @c Subnets4ListConfigParser.
    virtual boost::shared_ptr<Subnets4ListConfigParser> createSubnetsListParser() const;

    /// Check if the specified interface exists in the system.
    bool check_iface_;
};

/// @brief Implements parser for IPv6 shared networks.
class SharedNetwork6Parser : public BaseNetworkParser {
public:
    /// @brief Constructor.
    ///
    /// @param check_iface Check if the specified interface exists in
    /// the system.
    SharedNetwork6Parser(bool check_iface = true);

    /// @brief Virtual destructor.
    virtual ~SharedNetwork6Parser() {
    }

    /// @brief Parses shared configuration information for IPv6 shared network.
    ///
    /// @param shared_network_data Data element holding shared network
    /// configuration to be parsed.
    /// @param encapsulate_options a boolean parameter indicating if the
    /// parsed options should be encapsulated with suboptions.
    ///
    /// @return Pointer to an object representing shared network.
    /// @throw DhcpConfigError when shared network configuration is invalid.
    SharedNetwork6Ptr
    parse(const data::ConstElementPtr& shared_network_data,
          bool encapsulate_options = true);

protected:

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @return an instance of the @c OptionDataListParser(AF_INET6).
    virtual boost::shared_ptr<OptionDataListParser> createOptionDataListParser() const;

    /// @brief Returns an instance of the @c Subnets6ListConfigParser
    /// to be used for parsing the subnets within the shared network.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the subnets.
    ///
    /// @return an instance of the @c Subnets6ListConfigParser.
    virtual boost::shared_ptr<Subnets6ListConfigParser> createSubnetsListParser() const;

    /// Check if the specified interface exists in the system.
    bool check_iface_;
};

} // enf of namespace isc::dhcp
} // end of namespace isc

#endif // SHARED_SUBNET_PARSER_H
