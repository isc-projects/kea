// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_DATA_PARSER_H
#define OPTION_DATA_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_option_def.h>
#include <util/optional.h>
#include <cstdint>
#include <string>
#include <utility>

namespace isc {
namespace dhcp {

/// @brief Parser for option data value.
///
/// This parser parses configuration entries that specify value of
/// a single option. These entries include option name, option code
/// and data carried by the option. The option data can be specified
/// in one of the two available formats: binary value represented as
/// a string of hexadecimal digits or a list of comma separated values.
/// The format being used is controlled by csv-format configuration
/// parameter. When setting this value to True, the latter format is
/// used. The subsequent values in the CSV format apply to relevant
/// option data fields in the configured option. For example the
/// configuration: "data" : "192.168.2.0, 56, hello world" can be
/// used to set values for the option comprising IPv4 address,
/// integer and string data field. Note that order matters. If the
/// order of values does not match the order of data fields within
/// an option the configuration will not be accepted. If parsing
/// is successful then an instance of an option is created and
/// added to the storage provided by the calling class.
class OptionDataParser : public isc::data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or @c AF_INET6.
    /// @param cfg_option_def Config option definitions (optional)
    OptionDataParser(const uint16_t address_family,
                     CfgOptionDefPtr cfg_option_def = CfgOptionDefPtr());

    /// @brief Parses ElementPtr containing option definition
    ///
    /// This method parses ElementPtr containing the option definition,
    /// instantiates the option for it and then returns a pair
    /// of option descriptor (that holds that new option) and
    /// a string that specifies the option space.
    ///
    /// Note: ElementPtr is expected to contain all fields. If your
    /// ElementPtr does not have them, please use
    /// @ref isc::data::SimpleParser::setDefaults to fill the missing fields
    /// with default values.
    ///
    /// @param single_option ElementPtr containing option definition
    /// @return Option object wrapped in option description and an option
    ///         space
    std::pair<OptionDescriptor, std::string>
    parse(isc::data::ConstElementPtr single_option);

private:

    /// @brief Finds an option definition within an option space
    ///
    /// Given an option space and an option code, find the corresponding
    /// option definition within the option definition storage.
    ///
    /// @param option_space name of the parameter option space
    /// @param search_key an option code or name to be used to lookup the
    /// option definition.
    /// @tparam A numeric type for searching using an option code or the
    /// string for searching using the option name.
    ///
    /// @return OptionDefinitionPtr of the option definition or an
    /// empty OptionDefinitionPtr if not found.
    /// @throw DhcpConfigError if the option space requested is not valid
    /// for this server.
    template<typename SearchKey>
    OptionDefinitionPtr findOptionDefinition(const std::string& option_space,
                                             const SearchKey& search_key) const;

    /// @brief Create option instance.
    ///
    /// Creates an instance of an option and adds it to the provided
    /// options storage. If the option data parsed by \ref build function
    /// are invalid or insufficient this function emits an exception.
    ///
    /// If the option data is given as a string containing a hexadecimal
    /// literal, then it is converted into binary format.  These literals
    /// may contain upper and lower case digits.  They may be octets
    /// delimited by colons or spaces (octets may be 1 or 2 digits)
    /// If not delimited octets then they must be a continous string of
    /// digits with or without a "0x" prefix.  Examples:
    ///
    /// -# ab:cd:ef   - colon delimited
    /// -# ab cd ef   - space delimited
    /// -# 0xabcdef   - 0x prefixed (no delimiters)
    /// -# abcdef     - no prefix or delimeters
    ///
    /// A leading zero is assumed for odd number of digits
    /// in an octet or continuous string.
    ///
    /// @param option_data An element holding data for a single option being
    /// created.
    ///
    /// @return created option descriptor
    ///
    /// @throw DhcpConfigError if parameters provided in the configuration
    /// are invalid.
    std::pair<OptionDescriptor, std::string>
    createOption(isc::data::ConstElementPtr option_data);

    /// @brief Retrieves parsed option code as an optional value.
    ///
    /// @param parent A data element holding full option data configuration.
    ///
    /// @return Option code, possibly unspecified.
    /// @throw DhcpConfigError if option code is invalid.
    util::Optional<uint32_t>
    extractCode(data::ConstElementPtr parent) const;

    /// @brief Retrieves parsed option name as an optional value.
    ///
    /// @param parent A data element holding full option data configuration.
    ///
    /// @return Option name, possibly unspecified.
    /// @throw DhcpConfigError if option name is invalid.
    util::Optional<std::string>
    extractName(data::ConstElementPtr parent) const;

    /// @brief Retrieves csv-format parameter as an optional value.
    ///
    /// @return Value of the csv-format parameter, possibly unspecified.
    util::Optional<bool> extractCSVFormat(data::ConstElementPtr parent) const;

    /// @brief Retrieves option data as a string.
    ///
    /// @param parent A data element holding full option data configuration.
    /// @return Option data as a string. It will return empty string if
    /// option data is unspecified.
    std::string extractData(data::ConstElementPtr parent) const;

    /// @brief Retrieves option space name.
    ///
    /// If option space name is not specified in the configuration the
    /// 'dhcp4' or 'dhcp6' option space name is returned, depending on
    /// the universe specified in the parser context.
    ///
    /// @param parent A data element holding full option data configuration.
    ///
    /// @return Option space name.
    std::string extractSpace(data::ConstElementPtr parent) const;

    /// @brief Retrieves persistent/always-send parameter as an optional value.
    ///
    /// @return Value of the persistent parameter, possibly unspecified.
    util::Optional<bool> extractPersistent(data::ConstElementPtr parent) const;

    /// @brief Address family: @c AF_INET or @c AF_INET6.
    uint16_t address_family_;

    /// @brief Config option definitions
    CfgOptionDefPtr cfg_option_def_;
};

/// @brief Parser for option data values within a subnet.
///
/// This parser iterates over all entries that define options
/// data for a particular subnet and creates a collection of options.
/// If parsing is successful, all these options are added to the Subnet
/// object.
class OptionDataListParser : public isc::data::SimpleParser {
public:
    /// @brief Constructor.
    ///
    /// @param address_family Address family: @c AF_INET or AF_INET6
    /// @param cfg_option_def Config option definitions (optional)
    OptionDataListParser(const uint16_t address_family,
                         CfgOptionDefPtr cfg_option_def = CfgOptionDefPtr());

    /// @brief Parses a list of options, instantiates them and stores in cfg
    ///
    /// This method expects to get a list of options in option_data_list,
    /// iterates over them, creates option objects, wraps them with
    /// option descriptor and stores in specified cfg.
    ///
    /// @param cfg created options will be stored here
    /// @param option_data_list configuration that describes the options
    void parse(const CfgOptionPtr& cfg,
               isc::data::ConstElementPtr option_data_list);
private:
    /// @brief Address family: @c AF_INET or @c AF_INET6
    uint16_t address_family_;

    /// @brief Config option definitions
    CfgOptionDefPtr cfg_option_def_;
};


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // OPTION_DATA_PARSER_H
