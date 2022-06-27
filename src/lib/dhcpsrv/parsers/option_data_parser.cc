// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <limits>
#include <vector>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

// **************************** OptionDataParser *************************

OptionDataParser::OptionDataParser(const uint16_t address_family,
                                   CfgOptionDefPtr cfg_option_def)
    : address_family_(address_family), cfg_option_def_(cfg_option_def) {
}

std::pair<OptionDescriptor, std::string>
OptionDataParser::parse(isc::data::ConstElementPtr single_option) {

    // Check parameters.
    if (address_family_ == AF_INET) {
        checkKeywords(SimpleParser4::OPTION4_PARAMETERS, single_option);
    } else {
        checkKeywords(SimpleParser6::OPTION6_PARAMETERS, single_option);
    }

    // Try to create the option instance.
    std::pair<OptionDescriptor, std::string> opt = createOption(single_option);

    if (!opt.first.option_) {
        // Should never happen (@todo: update message)
        isc_throw(isc::InvalidOperation,
            "parser logic error: no option has been configured and"
            " thus there is nothing to commit. Has build() been called?");
    }

    return (opt);
}

Optional<uint32_t>
OptionDataParser::extractCode(ConstElementPtr parent) const {
    uint32_t code;
    try {
        code = getInteger(parent, "code");

    } catch (const std::exception&) {
        // The code parameter was not found. Return an unspecified
        // value.
        return (Optional<uint32_t>());
    }

    if (address_family_ == AF_INET &&
        code > std::numeric_limits<uint8_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << code
                  << "', it must not be greater than '"
                  << static_cast<int>(std::numeric_limits<uint8_t>::max())
                  << "' (" << getPosition("code", parent)
                  << ")");

    } else if (address_family_ == AF_INET6 &&
               code > std::numeric_limits<uint16_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << code
                  << "', it must not exceed '"
                  << std::numeric_limits<uint16_t>::max()
                  << "' (" << getPosition("code", parent)
                  << ")");

    }

    return (Optional<uint32_t>(code));
}

Optional<std::string>
OptionDataParser::extractName(ConstElementPtr parent) const {
    std::string name;
    try {
        name = getString(parent, "name");

    } catch (...) {
        return (Optional<std::string>());
    }

    if (name.find(" ") != std::string::npos) {
        isc_throw(DhcpConfigError, "invalid option name '" << name
                  << "', space character is not allowed ("
                  << getPosition("name", parent) << ")");
    }

    return (Optional<std::string>(name));
}

std::string
OptionDataParser::extractData(ConstElementPtr parent) const {
    std::string data;
    try {
        data = getString(parent, "data");

    } catch (...) {
        // The "data" parameter was not found. Return an empty value.
        return (data);
    }

    return (data);
}

Optional<bool>
OptionDataParser::extractCSVFormat(ConstElementPtr parent) const {
    bool csv_format = true;
    try {
        csv_format = getBoolean(parent, "csv-format");

    } catch (...) {
        return (Optional<bool>());
    }

    return (Optional<bool>(csv_format));
}

std::string
OptionDataParser::extractSpace(ConstElementPtr parent) const {
    std::string space = address_family_ == AF_INET ?
        DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE;
    try {
        space = getString(parent, "space");

    } catch (...) {
        return (space);
    }

    try {
        if (!OptionSpace::validateName(space)) {
            isc_throw(DhcpConfigError, "invalid option space name '"
                      << space << "'");
        }

        if ((space == DHCP4_OPTION_SPACE) && (address_family_ == AF_INET6)) {
            isc_throw(DhcpConfigError, "'" << DHCP4_OPTION_SPACE
                      << "' option space name is reserved for DHCPv4 server");

        } else if ((space == DHCP6_OPTION_SPACE) &&
                   (address_family_ == AF_INET)) {
            isc_throw(DhcpConfigError, "'" << DHCP6_OPTION_SPACE
                      << "' option space name is reserved for DHCPv6 server");
        }

    } catch (const std::exception& ex) {
        // Append position of the option space parameter.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << getPosition("space", parent) << ")");
    }

    return (space);
}

Optional<bool>
OptionDataParser::extractPersistent(ConstElementPtr parent) const {
    bool persist = false;
    try {
        persist = getBoolean(parent, "always-send");

    } catch (...) {
        return (Optional<bool>());
    }

    return (Optional<bool>(persist));
}

OptionDefinitionPtr
OptionDataParser::findOptionDefinition(const std::string& option_space,
                                       const Optional<uint32_t>& option_code,
                                       const Optional<std::string>& option_name) const {
    OptionDefinitionPtr def;
    if (cfg_option_def_) {
        // Check if the definition was given in the constructor
        if (option_code.unspecified()) {
            def = cfg_option_def_->get(option_space, option_name);
        } else {
            def = cfg_option_def_->get(option_space, option_code);
        }
    }

    if (!def) {
        // Check if this is a standard option.
        if (option_code.unspecified()) {
            def = LibDHCP::getOptionDef(option_space, option_name);
        } else {
            def = LibDHCP::getOptionDef(option_space, option_code);
        }
    }

    if (!def) {
        // Check if this is a vendor-option. If it is, get vendor-specific
        // definition.
        uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(option_space);
        if (vendor_id) {
            const Option::Universe u = address_family_ == AF_INET ?
                Option::V4 : Option::V6;
            if (option_code.unspecified()) {
                def = LibDHCP::getVendorOptionDef(u, vendor_id, option_name);
            } else {
                def = LibDHCP::getVendorOptionDef(u, vendor_id, option_code);
            }
        }
    }

    if (!def) {
        // Check if this is an option specified by a user. We used to
        // check that in the staging configuration, but when the configuration
        // changes are caused by a command the staging configuration doesn't
        // exist. What is always available is the container holding runtime
        // option definitions in LibDHCP. It holds option definitions from
        // the staging configuration in case of the full reconfiguration or
        // the definitions from the current configuration in case there is
        // no staging configuration (after configuration commit). In other
        // words, runtime options are always the ones that we need here.
        if (option_code.unspecified()) {
            def = LibDHCP::getRuntimeOptionDef(option_space, option_name);
        } else {
            def = LibDHCP::getRuntimeOptionDef(option_space, option_code);
        }
    }

    if (!def) {
        // Finish by last resort definitions.
        if (option_code.unspecified()) {
            def = LibDHCP::getLastResortOptionDef(option_space, option_name);
        } else {
            def = LibDHCP::getLastResortOptionDef(option_space, option_code);
        }
    }

    return (def);
}

std::pair<OptionDescriptor, std::string>
OptionDataParser::createOption(ConstElementPtr option_data) {
    const Option::Universe universe = address_family_ == AF_INET ?
        Option::V4 : Option::V6;

    Optional<uint32_t> code_param = extractCode(option_data);
    Optional<std::string> name_param = extractName(option_data);
    Optional<bool> csv_format_param = extractCSVFormat(option_data);
    Optional<bool> persist_param = extractPersistent(option_data);
    std::string data_param = extractData(option_data);
    std::string space_param = extractSpace(option_data);
    ConstElementPtr user_context = option_data->get("user-context");

    // Require that option code or option name is specified.
    if (code_param.unspecified() && name_param.unspecified()) {
        isc_throw(DhcpConfigError, "option data configuration requires one of"
                  " 'code' or 'name' parameters to be specified"
                  << " (" << option_data->getPosition() << ")");
    }

    // Try to find a corresponding option definition using option code or
    // option name.
    OptionDefinitionPtr def = findOptionDefinition(space_param, code_param, name_param);

    // If there is no definition, the user must not explicitly enable the
    // use of csv-format.
    if (!def) {
        // If explicitly requested that the CSV format is to be used,
        // the option definition is a must.
        if (!csv_format_param.unspecified() && csv_format_param) {
            isc_throw(DhcpConfigError, "definition for the option '"
                      << space_param << "." << name_param
                      << "' having code '" << code_param
                      << "' does not exist ("
                      << getPosition("name", option_data)
                      << ")");

        // If there is no option definition and the option code is not specified
        // we have no means to find the option code.
        } else if (!name_param.unspecified() && code_param.unspecified()) {
            isc_throw(DhcpConfigError, "definition for the option '"
                      << space_param << "." << name_param
                      << "' does not exist ("
                      << getPosition("name", option_data)
                      << ")");
        }
    }

    // Transform string of hexadecimal digits into binary format.
    std::vector<uint8_t> binary;
    std::vector<std::string> data_tokens;

    // If the definition is available and csv-format hasn't been explicitly
    // disabled, we will parse the data as comma separated values.
    if (def && (csv_format_param.unspecified() || csv_format_param)) {
        // If the option data is specified as a string of comma
        // separated values then we need to split this string into
        // individual values - each value will be used to initialize
        // one data field of an option.
        // It is the only usage of the escape option: this allows
        // to embed commas in individual values and to return
        // for instance a string value with embedded commas.
        data_tokens = isc::util::str::tokens(data_param, ",", true);

    } else {
        // Try to convert the values in quotes into a vector of ASCII codes.
        // If the identifier lacks opening and closing quote, this will return
        // an empty value, in which case we'll try to decode it as a string of
        // hexadecimal digits.
        try {
            binary = util::str::quotedStringToBinary(data_param);
            if (binary.empty()) {
                util::str::decodeFormattedHexString(data_param, binary);
            }
        } catch (...) {
            isc_throw(DhcpConfigError, "option data is not a valid"
                      << " string of hexadecimal digits: " << data_param
                      << " ("
                      << getPosition("data", option_data)
                      << ")");
        }
    }

    OptionDescriptor desc(false);

    if (!def) {
        // @todo We have a limited set of option definitions initialized at
        // the moment.  In the future we want to initialize option definitions
        // for all options.  Consequently an error will be issued if an option
        // definition does not exist for a particular option code. For now it is
        // ok to create generic option if definition does not exist.
        OptionPtr option(new Option(universe, static_cast<uint16_t>(code_param),
                                    binary));

        desc.option_ = option;
        desc.persistent_ = !persist_param.unspecified() && persist_param;
    } else {

        // Option name is specified it should match the name in the definition.
        if (!name_param.unspecified() && (def->getName() != name_param.get())) {
            isc_throw(DhcpConfigError, "specified option name '"
                      << name_param << "' does not match the "
                      << "option definition: '" << space_param
                      << "." << def->getName() << "' ("
                      << getPosition("name", option_data)
                      << ")");
        }

        // Option definition has been found so let's use it to create
        // an instance of our option.
        try {
            bool use_csv = csv_format_param.unspecified() || csv_format_param;
            OptionPtr option = use_csv ?
                def->optionFactory(universe, def->getCode(), data_tokens) :
                def->optionFactory(universe, def->getCode(), binary);
            desc.option_ = option;
            desc.persistent_ = !persist_param.unspecified() && persist_param;
            if (use_csv) {
                desc.formatted_value_ = data_param;
            }
        } catch (const isc::Exception& ex) {
            isc_throw(DhcpConfigError, "option data does not match"
                      << " option definition (space: " << space_param
                      << ", code: " << def->getCode() << "): "
                      << ex.what() << " ("
                      << getPosition("data", option_data)
                      << ")");
        }
    }

    // Check PAD and END in (and only in) dhcp4 space.
    if (space_param == DHCP4_OPTION_SPACE) {
        if (desc.option_->getType() == DHO_PAD) {
            isc_throw(DhcpConfigError, "invalid option code '0': "
                      << "reserved for PAD ("
                      << option_data->getPosition() << ")");
        } else if (desc.option_->getType() == DHO_END) {
            isc_throw(DhcpConfigError, "invalid option code '255': "
                      << "reserved for END ("
                      << option_data->getPosition() << ")");
        }
    }

    // For dhcp6 space the value 0 is reserved.
    if (space_param == DHCP6_OPTION_SPACE) {
        if (desc.option_->getType() == 0) {
            isc_throw(DhcpConfigError, "invalid option code '0': "
                      << "reserved value ("
                      << option_data->getPosition() << ")");
        }
    }


    // Add user context
    if (user_context) {
        desc.setContext(user_context);
    }

    // All went good, so we can set the option space name.
    return make_pair(desc, space_param);
}

// **************************** OptionDataListParser *************************
OptionDataListParser::OptionDataListParser(//const std::string&,
                                           //const CfgOptionPtr& cfg,
                                           const uint16_t address_family,
                                           CfgOptionDefPtr cfg_option_def)
    : address_family_(address_family), cfg_option_def_(cfg_option_def) {
}


void OptionDataListParser::parse(const CfgOptionPtr& cfg,
                                 isc::data::ConstElementPtr option_data_list) {
    auto option_parser = createOptionDataParser();
    BOOST_FOREACH(ConstElementPtr data, option_data_list->listValue()) {
        std::pair<OptionDescriptor, std::string> option =
            option_parser->parse(data);
        // Use the option description to keep the formatted value
        cfg->add(option.first, option.second);
        cfg->encapsulate();
    }
}

boost::shared_ptr<OptionDataParser>
OptionDataListParser::createOptionDataParser() const {
    auto parser = boost::make_shared<OptionDataParser>(address_family_, cfg_option_def_);
    return (parser);
}

} // end of namespace isc::dhcp
} // end of namespace isc
