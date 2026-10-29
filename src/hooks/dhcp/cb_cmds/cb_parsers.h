// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_PARSERS_H
#define CB_PARSERS_H

#include <cc/stamped_value.h>
#include <cc/server_tag.h>
#include <database/backend_selector.h>
#include <database/server.h>
#include <database/server_selector.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/shared_network_parser.h>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

/// @file cb_parsers.h
/// @brief Parsers for a subset of an object specification, e.g. subnet by id.
/// This includes to the global parameter parser.
/// Specifications are pointers to map elements and parsers assume to be
/// called with this.

namespace isc {
namespace cb {

/// @brief Implements a parser for a global parameter name.
///
/// Used for getting and deleting a global parameter.
class GlobalParameterNameParser : public data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param keywords Global parameter names.
    GlobalParameterNameParser(const data::SimpleKeywords& keywords)
        : keywords_(keywords) {
    }

    /// @brief Parses global parameter name.
    ///
    /// The global parameter name must be a string.
    ///
    /// @param global_parameter pointer to the content of global parameter.
    /// @return Global parameter name.
    /// @throw BadValue if a name is empty or unsupported.
    std::string parse(data::ConstElementPtr global_parameter);

private:
    /// @brief Global parameter names e.g.
    /// @c data::SimpleParser4:GLOBAL4_PARAMETERS
    const data::SimpleKeywords& keywords_;
};

/// @brief Implements a parser for global parameters.
class GlobalParameterParser : public data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param keywords Global parameter names and types.
    /// @param list_keywords Global list parameter names and subtypes.
    GlobalParameterParser(const data::SimpleKeywords& keywords,
                          const data::SimpleKeywords& list_keywords)
        : keywords_(keywords), list_keywords_(list_keywords) {
    }

    /// @brief Parses global parameters information.
    ///
    /// Parsed data must include a map of parameter name/value pairs. The
    /// values can be of a string, integer, boolean or real type.
    ///
    /// @param global_parameter_data Map element holding global parameters
    /// and their values.
    /// @return Collection of stamped values holding parsed data.
    /// @throw BadValue if the parsed element is malformed.
    data::StampedValueCollection
    parse(const data::ConstElementPtr& global_parameter_data);

private:
    /// @brief Global parameter names e.g.
    /// @c data::SimpleParser[4|6]:GLOBAL[4|6]_PARAMETERS
    const data::SimpleKeywords& keywords_;

    /// @brief Global list parameter names e.g.
    /// @c data::SimpleParser[4|6]:GLOBAL[4|6]_LIST_PARAMETER_TYPES
    const data::SimpleKeywords& list_keywords_;
};

/// @brief Implements a parser for option definitions with setting defaults.
class CBOptionDefParser : public data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    CBOptionDefParser(const uint16_t address_family)
        : address_family_(address_family) {
    }

    /// @brief Parses an option definition.
    ///
    /// Sets the defaults and calls @c dhcp::OptionDefParser.
    ///
    /// @param option_def a configuration entry to be parsed.
    /// @return option definition of the parsed structure.
    /// @throw DhcpConfigError if parsing was unsuccessful.
    dhcp::OptionDefinitionPtr parse(data::ConstElementPtr option_def);

private:
    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

/// @brief Implements a parser for parsing the option code and space.
///
/// Used for getting and deleting an option def or data.
class CBOptionPairParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("code").
    static data::SimpleRequiredKeywords OPTION_REQUIRED;

    /// @brief Acceptable keywords and types
    /// ("code": <integer>, "space": <string>).
    static data::SimpleKeywords OPTION_KEYWORDS;

public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    CBOptionPairParser(const uint16_t address_family)
        : address_family_(address_family) {
    }

    /// @brief Destructor.
    virtual ~CBOptionPairParser() {};

    /// @brief Parses an option into code + space pair.
    ///
    /// The option specification is reduced to the code and space pair.
    /// The code is mandatory, the space defaults to the address family
    /// standard space. The parser takes, checks and returns them.
    ///
    /// @param option pointer to the content of option definition.
    /// @param skip_keywords when true the check for spurious keywords is
    /// skipped.  Deriving classes may set to avoid spurious keyword errors
    /// when invoking this method.  Defaults to false.
    /// @return the code and space pair.
    /// @throw DhcpConfigError if the code does not exist, is not an integer
    /// @throw BadValue if the space exists but is not a valid space name.
    /// @throw OutOfRange if the code is out of range
    /// ([0..255] for DHCPv4, [0..65535] for DHCPv6).
    std::pair<uint16_t, std::string> parse(data::ConstElementPtr option,
                                           bool skip_keywords = false);

private:
    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

/// @brief Defines a tuple of values for deleting an option definition:
/// the option code, option space, and force flag.
typedef std::tuple<uint16_t, std::string, bool> CBOptionDefDelete;

/// @brief Defines a tuple for the three values that may be used as a key for an option.
typedef std::tuple<uint16_t, std::string, ClientClassesPtr> CBOptionTuple;

/// @brief Implements a parser for parsing the option code and space and client-classes.
///
/// Used for getting and deleting an option def or data.
class CBOptionTupleParser : public CBOptionPairParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    CBOptionTupleParser(const uint16_t address_family)
        : CBOptionPairParser(address_family) {
    }

    /// @brief Parses an option into code + space pair.
    ///
    /// The option specification is reduced to the code, space, and
    /// (optional) client-classes list. The code is mandatory, the
    /// space defaults to the address family standard space, and
    /// client-classes to an empty pointer. The parser takes, checks
    /// and returns them.
    ///
    /// @param option pointer to the content of option.
    /// @return the code, space and client classes tuple.
    /// @throw DhcpConfigError if the code does not exist, is not an integer
    /// @throw BadValue if the space exists but is not a valid space name.
    /// @throw OutOfRange if the code is out of range
    /// ([0..255] for DHCPv4, [0..65535] for DHCPv6).
    CBOptionTuple parse(data::ConstElementPtr option);
};

/// @brief Implements a parser for parsing the option code, space, and force.
///
/// Used for getting and deleting an option def or data.
class CBOptionDefDeleteParser : public CBOptionPairParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    CBOptionDefDeleteParser(const uint16_t address_family)
        : CBOptionPairParser(address_family) {
    }

    /// @brief Parses an option into code + space pair.
    ///
    /// The option specification is reduced to the code, space, and
    /// (optional) client-classes list. The code is mandatory, the
    /// space defaults to the address family standard space, and
    /// client-classes to an empty pointer. The parser takes, checks
    /// and returns them.
    ///
    /// @param option pointer to the content of option.
    /// @return the code, space and client classes tuple.
    /// @throw DhcpConfigError if the code does not exist, is not an integer
    /// @throw BadValue if the space exists but is not a valid space name.
    /// @throw OutOfRange if the code is out of range
    /// ([0..255] for DHCPv4, [0..65535] for DHCPv6).
    CBOptionDefDelete parse(data::ConstElementPtr option);
};

/// @brief Overrides the default option data parser.
///
/// It modifies the @c findOptionDefinition logic to search for the non-standard
/// option definitions in the configuration backend.
class CBOptionDataParser : public dhcp::OptionDataParser {
public:

    /// @brief Constructor.
    ///
    /// @param address_family address family: @c AF_INET or @c AF_INET6.
    /// @param cfg_option_def container optionally holding option definitions
    /// defined for a class.
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector server selector used to fetch option definitions
    /// during option data parsing.
    CBOptionDataParser(const uint16_t address_family,
                       dhcp::CfgOptionDefPtr cfg_option_def,
                       db::BackendSelector& backend_selector,
                       db::ServerSelector& server_selector);

protected:

    /// @brief Finds an option definition within an option space.
    ///
    /// Given an option space and an option code or option space, find
    /// the corresponding option definition in the configuration
    /// backend and among the standard options.
    ///
    /// It tries to find an option definition using various sources
    /// in the following order:
    ///
    /// - @c cfg_option_def_ structure (passed in the constructor),
    /// - standard option definitions in libdhcp++,
    /// - vendor option definitions in libdhcp++,
    /// - configuration backend for the backend and server selector
    ///   specified in the constructor,
    /// - runtime option definitions,
    /// - last resort option definitions in libdhcp++.
    ///
    /// The function breaks when it finds the first option definition in
    /// any of the sources listed above.
    ///
    /// The caller must specify an option code or an option name. If
    /// neither of them is specified, the function returns a null
    /// pointer. If the option code is specified, the option name is
    /// ignored. If option code is not specified, the option name is
    /// used as a key to find the option definition.
    ///
    /// @param option_space option space name.
    /// @param option_code option code to be used to find the option
    /// definition.
    /// @param option_name option name to be used to find the option
    /// definition if an option code is not specified.
    ///
    /// @return OptionDefinitionPtr of the option definition or an
    /// empty OptionDefinitionPtr if not found.
    /// @throw DhcpConfigError if the option space requested is not valid
    /// for this server.
    virtual dhcp::OptionDefinitionPtr
    findOptionDefinition(const std::string& option_space,
                         const util::Optional<uint32_t>& option_code,
                         const util::Optional<std::string>& option_name) const;

    /// @brief Backend selector to be used to fetch option definitions
    /// during option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector to be used to fetch option definitions
    /// during option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Overrides the default option data list parser.
///
/// It modifies the parser to use the @c CBOptionDataParser for parsing
/// the option data.
class CBOptionDataListParser : public dhcp::OptionDataListParser {
public:

    /// @brief Constructor.
    ///
    /// @param address family: @c AF_INET or @c AF_INET6.
    /// @param cfg_option_def container optionally holding option definitions
    /// defined for a class.
    /// @param backend_selector backend selector used to fetch option
    /// definitions during option data parsing.
    /// @param server_selector server selector used to fetch option
    /// definitions during option data parsing.
    CBOptionDataListParser(const uint16_t address_family,
                           CfgOptionDefPtr cfg_option_def,
                           db::BackendSelector& backend_selector,
                           db::ServerSelector& server_selector);

protected:

    /// @brief Returns an instance of the @c CBOptionDataListParser to
    /// be used in parsing options.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataParser>
    createOptionDataParser() const;

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for an address pool range.
///
/// Used for setting or deleting an option in a pool.
class CBPoolRangeParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("pool").
    static data::SimpleRequiredKeywords POOL_REQUIRED;

    /// @brief Acceptable keywords and types ("pool": <string>).
    static data::SimpleKeywords POOL_KEYWORDS;

public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    CBPoolRangeParser(const uint16_t address_family)
        : address_family_(address_family) {
    }

    /// @brief Parses an address pool range.
    ///
    /// Specialization of the PoolParser to the address pool range only.
    /// Supports both prefix/length and start-end forms.
    ///
    /// @param pool an address pool range being specified.
    /// @return the pair of start and end addresses of the pool range.
    std::pair<asiolink::IOAddress, asiolink::IOAddress>
    parse(data::ConstElementPtr pool);

private:
    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

/// @brief Overrides the default address pool parsers to use CB specific
/// option data parsers.
///
/// @tparam PoolParser Type of the class this class derives from, i.e.
/// @c dhcp::Pool4Parser or @c dhcp::Pool6Parser.
template<typename PoolParser>
class CBPoolParser : public PoolParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector backend selector used to fetch option definitions
    /// during option data parsing.
    CBPoolParser(db::BackendSelector& backend_selector,
                 db::ServerSelector& server_selector)
        : PoolParser(), backend_selector_(backend_selector),
          server_selector_(server_selector) {
    }

protected:

    /// @brief Returns an instance of the @c OptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for option data.
    ///
    /// @param address_family AF_INET (for DHCPv4) or AF_INET6 (for DHCPv6).
    ///
    /// @return an instance of the @c OptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser(const uint16_t address_family) const {
        auto parser = boost::make_shared<CBOptionDataListParser>(address_family,
                                                                 dhcp::CfgOptionDefPtr(),
                                                                 backend_selector_,
                                                                 server_selector_);
        return (parser);
    }

    /// @brief Backend selector used to fetch option definitions during option
    /// data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during option
    /// data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Specialization of the @c CBPoolParser class for DHCPv4.
using CBPool4Parser = CBPoolParser<dhcp::Pool4Parser>;

/// @brief Specialization of the @c CBPoolParser class for DHCPv6.
using CBPool6Parser = CBPoolParser<dhcp::Pool6Parser>;

/// @brief Overrides the default address pool list parsers to use CB specific
/// option data parsers.
///
/// @tparam PoolsListParser Type of the class this class derives from, i.e.
/// @c dhcp::Pools4ListParser or @c dhcp::Pools6ListParser.
/// @tparam PoolParser Type of the class implementing an address pool parser,
/// i.e. @c CBPool4Parser or @c CBPool6Parser.
template<typename PoolsListParser, typename PoolParser>
class CBPoolsListParser : public PoolsListParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector backend selector used to fetch option definitions
    /// during option data parsing.
    CBPoolsListParser(db::BackendSelector& backend_selector,
                      db::ServerSelector& server_selector)
        : backend_selector_(backend_selector), server_selector_(server_selector) {
    }

protected:

    /// @brief Returns an instance of the @c CBPool4Parser to be used in
    /// parsing the address pools.
    ///
    /// This function can be overridden in the child classes to supply
    /// a custom parser for the pools.
    ///
    /// @return an instance of the @c Pool4Parser.
    virtual boost::shared_ptr<dhcp::PoolParser> createPoolConfigParser() const {
        auto parser = boost::make_shared<PoolParser>(backend_selector_, server_selector_);
        return (parser);
    }

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Specialization of the @c CBPoolsListParser class for DHCPv4.
using CBPools4ListParser = CBPoolsListParser<dhcp::Pools4ListParser, CBPool4Parser>;

/// @brief Specialization of the @c CBPoolsListParser class for DHCPv6.
using CBPools6ListParser = CBPoolsListParser<dhcp::Pools6ListParser, CBPool6Parser>;

/// @brief Overrides the default delegated prefix pool parser to use CB
/// specific option data parsers.
class CBPdPoolParser : public PdPoolParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector backend selector used to fetch option definitions
    /// during option data parsing.
    CBPdPoolParser(db::BackendSelector& backend_selector,
                   db::ServerSelector& server_selector);

protected:

    /// @brief Returns an instance of the @c CBOptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser() const;

    /// @brief Backend selector used to fetch option definitions during option
    /// data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during option
    /// data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Overrides the default delegated prefix pool list parser to use CB
/// specific option data parsers.
class CBPdPoolsListParser : public PdPoolsListParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector backend selector used to fetch option definitions
    /// during option data parsing.
    CBPdPoolsListParser(db::BackendSelector& backend_selector,
                        db::ServerSelector& server_selector);

protected:

    /// @brief Returns an instance of the @c CBPdPoolParser to be used in
    /// parsing the prefix delegation pools.
    ///
    /// @return an instance of the @c CBPdPoolParser.
    virtual boost::shared_ptr<PdPoolParser>
    createPdPoolConfigParser() const;

    /// @brief Backend selector used to fetch option definitions during option
    /// data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during option
    /// data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for a prefix delegation pool prefix.
///
/// Used for setting or deleting an option in a pd pool.
class CBPdPoolPrefixParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("prefix" and "prefix-len").
    static data::SimpleRequiredKeywords PD_POOL_REQUIRED;

    /// @brief Acceptable keywords and types
    /// ("prefix": <string> and "prefix-len": <integer>).
    static data::SimpleKeywords PD_POOL_KEYWORDS;

public:
    /// @brief Parses a prefix delegation pool prefix.
    ///
    /// @param pd_pool a pd pool prefix being specified.
    /// @return the pair of address and length of the pd pool prefix.
    std::pair<asiolink::IOAddress, uint8_t>
    parse(data::ConstElementPtr pd_pool);
};

/// @brief Implements a parser for a subnet id.
///
/// Used for getting and deleting a subnet by id.
class CBSubnetIdParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("id").
    static data::SimpleRequiredKeywords SUBNET_ID_REQUIRED;

    /// @brief Acceptable keywords and types ("id": <integer>).
    static data::SimpleKeywords SUBNET_ID_KEYWORDS;

public:
    /// @brief Parses a subnet id.
    ///
    /// The subnet specification is reduced to the subnet id,
    /// which is expected to always be present in "id" parameter and
    /// must be a valid number within the range of allowed subnet ids.
    ///
    /// @param subnet pointer to the content of subnet definition.
    /// @return subnet identifier.
    /// @throw DhcpConfigError if the id does not exist, is not an integer
    /// or another parameter is specified.
    /// @throw OutOfRange if the id is not in the [1..SUBNET_ID_MAX] range.
    dhcp::SubnetID parse(data::ConstElementPtr subnet);
};

/// @brief Implements a parser for a subnet prefix.
///
/// Used for getting and deleting a subnet by prefix.
class CBSubnetPrefixParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("subnet").
    static data::SimpleRequiredKeywords SUBNET_PREFIX_REQUIRED;

    /// @brief Acceptable keywords and types ("subnet": <string>).
    static data::SimpleKeywords SUBNET_PREFIX_KEYWORDS;

public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    CBSubnetPrefixParser(const uint16_t address_family)
        : address_family_(address_family) {
    }

    /// @brief Parses a subnet prefix.
    ///
    /// The subnet specification is reduced to the subnet prefix
    /// which is expected to be always present in "subnet" parameter
    /// and must be a string containing a valid IPv4 or IPv6 prefix.
    ///
    /// @param subnet pointer to the content of subnet definition.
    /// @return subnet prefix.
    /// @throw DhcpConfigError if the prefix does not exist, is not string
    /// or another parameter is specified.
    /// @throw BadValue if the prefix is empty or is not a valid one
    /// according to parsePrefix.
    std::string parse(data::ConstElementPtr subnet);

private:
    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;
};

/// @brief Implements a parser for IPv4 subnets.
///
/// It rejects host reservations and uses CB specific parser for
/// option data.
class CBSubnet4ConfigParser : public Subnet4ConfigParser {
public:
    /// @brief Constructor.
    ///
    /// Call the parent class constructor with check_iface set to false.
    ///
    /// @param backend_selector backend selector for fetching option definitions
    /// during option data parsing.
    /// @param server_selector server selector for fetching option definitions
    /// during option data parsing.
    CBSubnet4ConfigParser(db::BackendSelector& backend_selector,
                          db::ServerSelector& server_selector);

    /// @brief Parses a single subnet configuration.
    ///
    /// Specialization of Subnet4ConfigParser expecting subnet id,
    /// rejecting reservations and requiring shared-network-name being
    /// a string or null value.
    ///
    /// @param subnet a subnet being configured.
    /// @return a pointer to created Subnet4 object.
    /// @throw BadValue if the subnet has a reservations entry which is not
    /// a list or is not empty.
    dhcp::Subnet4Ptr parse(data::ConstElementPtr subnet);

protected:

    /// @brief Returns an instance of the @c CBOptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser() const;

    /// @brief Returns an instance of the @c CBPools4ListParser.
    ///
    /// @return an instance of the @c CBPools4ListParser.
    virtual boost::shared_ptr<dhcp::PoolsListParser>
    createPoolsListParser() const;

    /// @brief Backend selector used for fetching option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used for fetching option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for IPv6 subnets.
///
/// It rejects host reservations and uses CB specific parser for
/// option data.
class CBSubnet6ConfigParser : public Subnet6ConfigParser {
public:
    /// @brief Constructor.
    ///
    /// Call the parent class constructor with check_iface set to false.
    ///
    /// @param backend_selector backend selector for fetching option definitions
    /// during option data parsing.
    /// @param server_selector server selector for fetching option definitions
    /// during option data parsing.
    CBSubnet6ConfigParser(db::BackendSelector& backend_selector,
                          db::ServerSelector& server_selector);

    /// @brief Parses a single subnet configuration.
    ///
    /// Specialization of Subnet4ConfigParser expecting subnet id,
    /// rejecting reservations and requiring shared-network-name being
    /// a string or null value.
    ///
    /// @param subnet a subnet being configured.
    /// @return a pointer to created Subnet4 object.
    /// @throw BadValue if the subnet has a reservations entry which is not
    /// a list or is not empty.
    dhcp::Subnet6Ptr parse(data::ConstElementPtr subnet);

protected:

    /// @brief Returns an instance of the @c CBOptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser() const;

    /// @brief Returns an instance of the @c CBPools6ListParser.
    ///
    /// @return an instance of the @c CBPools6ListParser.
    virtual boost::shared_ptr<dhcp::PoolsListParser>
    createPoolsListParser() const;

    /// @brief Returns an instance of the @c CBPdPoolsListParser.
    ///
    /// @return an instance of the @c CBPdPoolsListParser.
    virtual boost::shared_ptr<dhcp::PdPoolsListParser>
    createPdPoolsListParser() const;

    /// @brief Backend selector used for fetching option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used for fetching option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Overrides the default IPv4 subnet list parser.
///
/// It uses @c CBOptionDataParser (via the @c CBSubnet4ConfigParser) for
/// parsing option data.
class CBSubnets4ListConfigParser : public dhcp::Subnets4ListConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option
    /// definitions during option data parsing.
    /// @param sever_selector backend selector used to fetch option
    /// definitions during option data parsing.
    CBSubnets4ListConfigParser(db::BackendSelector& backend_selector,
                               db::ServerSelector& server_selector);

protected:

    /// @brief Returns an instance of the @c CBSubnet4ConfigParser to be
    /// used in parsing the subnets.
    ///
    /// @return an instance of the @c CBSubnet4ConfigParser.
    virtual boost::shared_ptr<Subnet4ConfigParser>
    createSubnetConfigParser() const;

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Overrides the default IPv6 subnet list parser.
///
/// It uses @c CBOptionDataParser (via the @c CBSubnet6ConfigParser) for
/// parsing option data.
class CBSubnets6ListConfigParser : public dhcp::Subnets6ListConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option
    /// definitions during option data parsing.
    /// @param sever_selector backend selector used to fetch option
    /// definitions during option data parsing.
    CBSubnets6ListConfigParser(db::BackendSelector& backend_selector,
                               db::ServerSelector& server_selector);

protected:

    /// @brief Returns an instance of the @c CBSubnet6ConfigParser to be
    /// used in parsing the subnets.
    ///
    /// @return an instance of the @c CBSubnet6ConfigParser.
    virtual boost::shared_ptr<Subnet6ConfigParser>
    createSubnetConfigParser() const;

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for a shared network name.
///
/// Used for getting and deleting a shared network by name.
class CBSharedNetworkNameParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("name").
    static data::SimpleRequiredKeywords SHARED_NETWORK_REQUIRED;

    /// @brief Acceptable keywords and types ("name": <string>).
    static data::SimpleKeywords SHARED_NETWORK_KEYWORDS;

public:
    /// @brief Parses a shared network name.
    ///
    /// The shared network specification is reduced to the name
    /// which is expected to always be present in the "name"
    /// parameter and must be a non-empty string.
    ///
    /// @param shared_network pointer to the content of shared network definition.
    /// @return the shared network name.
    /// @throw DhcpConfigError if the name does not exist, is not a string
    /// or another parameter is specified.
    /// @throw BadValue if the name is empty.
    std::string parse(data::ConstElementPtr shared_network);
};

/// @brief Implements a parser for IPv4 shared networks.
///
/// It rejects host reservations and uses CB specific parser for
/// option data.
class CBSharedNetwork4Parser : public dhcp::SharedNetwork4Parser {
public:
    /// @brief Constructor.
    ///
    /// Calls the parent class constructor with check_iface set to false.
    ///
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector server selector used to fetch option definitions
    /// during option data parsing.
    CBSharedNetwork4Parser(db::BackendSelector& backend_selector,
                           db::ServerSelector& server_selector);

    /// @brief Parses a single IPv4 shared network configuration.
    ///
    /// Specialization of @ dhcp::SharedNetwork4Parser rejecting reservations
    /// and performing some sanity checks, e.g. against empty names.
    ///
    /// @param shared_network a shared network being configured
    /// @return a pointer to created SharedNetwork4 object.
    /// @throw BadValue if the shared network contains subnets.
    dhcp::SharedNetwork4Ptr parse(data::ConstElementPtr shared_network);

protected:

    /// @brief Returns an instance of the @c CBOptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser() const;

    /// @brief Returns an instance of the @c CBSubnets4ListConfigParser
    /// to be used for parsing the subnets within the shared network.
    ///
    /// @return an instance of the @c CBSubnets4ListConfigParser.
    virtual boost::shared_ptr<Subnets4ListConfigParser>
    createSubnetsListParser() const;

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for IPv6 shared networks.
///
/// It rejects host reservations and uses CB specific parser for
/// option data.
class CBSharedNetwork6Parser : public dhcp::SharedNetwork6Parser {
public:
    /// @brief Constructor.
    ///
    /// Call the parent class constructor with check_iface set to false.
    CBSharedNetwork6Parser(db::BackendSelector& backend_selector,
                           db::ServerSelector& server_selector);

    /// @brief Parses a single IPv6 shared network configuration.
    ///
    /// Specialization of @ dhcp::SharedNetwork6Parser rejecting reservations
    /// and performing some sanity checks, e.g. against empty names.
    ///
    /// @param shared_network a shared network being configured
    /// @return a pointer to created SharedNetwork6 object.
    /// @throw BadValue if the shared network contains subnets.
    dhcp::SharedNetwork6Ptr parse(data::ConstElementPtr shared_network);

protected:

    /// @brief Returns an instance of the @c CBOptionDataListParser to
    /// be used in parsing the option-data structure.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser() const;

    /// @brief Returns an instance of the @c CBSubnets6ListConfigParser
    /// to be used for parsing the subnets within the shared network.
    ///
    /// @return an instance of the @c CBSubnets6ListConfigParser.
    virtual boost::shared_ptr<Subnets6ListConfigParser>
    createSubnetsListParser() const;

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Overrides the default parser for DHCP client classes.
///
/// This parser uses the CB specific parser for options.
class CBClientClassDefParser : public dhcp::ClientClassDefParser {
public:

    /// @brief Constructor.
    ///
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector server selector used to fetch option definitions
    /// during option data parsing.
    CBClientClassDefParser(db::BackendSelector& backend_selector,
                           db::ServerSelector& server_selector);

    /// @brief Returns an instance of the @c CBOptionDataListParser.
    ///
    /// @param address_family @c AF_INET (for DHCPv4) or @c AF_INET6 (for DHCPv6).
    /// @param cfg_option_def structure holding option definitions.
    ///
    /// @return an instance of the @c CBOptionDataListParser.
    virtual boost::shared_ptr<OptionDataListParser>
    createOptionDataListParser(const uint16_t address_family,
                               CfgOptionDefPtr cfg_option_def) const;

protected:

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for a DHCPv4 or DHCPv6 client class.
///
/// It is a wrapper around the @c ClientClassDefParser making it possible
/// to use the parser in the @c parseInputListElement and return the
/// @c follow_client_class value.
class CBClientClassParser : public data::SimpleParser {
public:

    /// @brief Constructor.
    ///
    /// @param family Address family: @c AF_INET or @c AF_INET6.
    /// @param cfg_option_def container optionally holding option definitions
    /// defined for a class.
    /// @param backend_selector backend selector used to fetch option definitions
    /// during option data parsing.
    /// @param server_selector server selector used to fetch option definitions
    /// during option data parsing.
    CBClientClassParser(uint16_t family,
                        CfgOptionDefPtr cfg_option_def,
                        db::BackendSelector& backend_selector,
                        db::ServerSelector& server_selector);

    /// @brief Parses a client class.
    ///
    /// Specialization of the @c ClientClassDefParser returning the
    /// optional value of the @c follow_class_name used to position
    /// the client class after another class.
    ///
    /// @param client_class client class to be parsed.
    /// @return a pair of parsed client class and the value of the
    /// @c follow_class_name.
    std::pair<dhcp::ClientClassDefPtr, std::string>
    parse(data::ConstElementPtr client_class);

private:

    /// Specified address family.
    uint16_t family_;

    /// @brief Pointer to a container holding option definitions for a
    /// parsed class.
    CfgOptionDefPtr cfg_option_def_;

    /// @brief Backend selector used to fetch option definitions during
    /// option data parsing.
    db::BackendSelector& backend_selector_;

    /// @brief Server selector used to fetch option definitions during
    /// option data parsing.
    db::ServerSelector& server_selector_;
};

/// @brief Implements a parser for a client class name.
///
/// Used for getting and deleting a client class by name.
class CBClientClassNameParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("name").
    static data::SimpleRequiredKeywords CLIENT_CLASS_REQUIRED;

    /// @brief Acceptable keywords and types ("name": <string>).
    static data::SimpleKeywords CLIENT_CLASS_KEYWORDS;

public:
    /// @brief Parses a client class name.
    ///
    /// The client specification is reduced to the name which is expected
    /// to always be present in the "name" parameter and must be a non-empty
    /// string.
    ///
    /// @param client_class pointer to the content of client class definition.
    /// @return the client class name.
    /// @throw DhcpConfigError if the name does not exist, is not a string
    /// or another parameter is specified.
    /// @throw BadValue if the name is empty.
    std::string parse(data::ConstElementPtr client_class);
};

/// @brief Implements parser for a server tag.
///
/// Used for getting and deleting a server.
class ServerTagParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("server-tag").
    static data::SimpleRequiredKeywords SERVER_TAG_REQUIRED;

    /// @brief Acceptable keywords and types ("server-tag": <string>).
    static data::SimpleKeywords SERVER_TAG_KEYWORDS;

public:
    /// @brief Parses server tag.
    ///
    /// The server tag must be a string acceptable as a server tag.
    ///
    /// @param server pointer to the content of server.
    /// @return server tag.
    /// @throw BadValue if the string can't be converted to a server tag.
    data::ServerTag parse(data::ConstElementPtr server);
};

/// @brief Implements parser for a server configuration.
///
/// Used for setting a server.
class ServerConfigParser : public data::SimpleParser {
private:
    /// @brief Required keywords ("server-tag").
    static data::SimpleRequiredKeywords SERVER_CONFIG_REQUIRED;

    /// @brief Acceptable keywords and types
    /// (server-tag and description strings).
    static data::SimpleKeywords SERVER_CONFIG_KEYWORDS;

public:
    /// @brief Parses a single server configuration.
    ///
    /// @param server a server being configured.
    /// @return a pointer to created Server object.
    /// @throw BadValue if the tag can't be converted to a server tag.
    db::ServerPtr parse(data::ConstElementPtr server);
};

} // end of namespace cb
} // end of namespace isc

#endif // CB_PARSER_H
