// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

// **************************** DebugParser *************************

DebugParser::DebugParser(const std::string& param_name)
    :param_name_(param_name) {
}

void
DebugParser::build(ConstElementPtr new_config) {
    value_ = new_config;
    std::cout << "Build for token: [" << param_name_ << "] = ["
        << value_->str() << "]" << std::endl;
}

void
DebugParser::commit() {
    // Debug message. The whole DebugParser class is used only for parser
    // debugging, and is not used in production code. It is very convenient
    // to keep it around. Please do not turn this cout into logger calls.
    std::cout << "Commit for token: [" << param_name_ << "] = ["
                  << value_->str() << "]" << std::endl;
}

// **************************** BooleanParser  *************************

template<> void ValueParser<bool>::build(isc::data::ConstElementPtr value) {
    // Invoke common code for all specializations of build().
    buildCommon(value);
    // The Config Manager checks if user specified a
    // valid value for a boolean parameter: true or false.
    // We should have a boolean Element, use value directly
    try {
        value_ = value->boolValue();
    } catch (const isc::data::TypeError &) {
        isc_throw(BadValue, " Wrong value type for " << param_name_
                  << " : build called with a non-boolean element "
                  << "(" << value->getPosition() << ").");
    }
}

// **************************** Uin32Parser  *************************

template<> void ValueParser<uint32_t>::build(ConstElementPtr value) {
    // Invoke common code for all specializations of build().
    buildCommon(value);

    int64_t check;
    string x = value->str();
    try {
        check = boost::lexical_cast<int64_t>(x);
    } catch (const boost::bad_lexical_cast &) {
        isc_throw(BadValue, "Failed to parse value " << value->str()
                  << " as unsigned 32-bit integer "
                  "(" << value->getPosition() << ").");
    }
    if (check > std::numeric_limits<uint32_t>::max()) {
        isc_throw(BadValue, "Value " << value->str() << " is too large"
                  " for unsigned 32-bit integer "
                  "(" << value->getPosition() << ").");
    }
    if (check < 0) {
        isc_throw(BadValue, "Value " << value->str() << " is negative."
               << " Only 0 or larger are allowed for unsigned 32-bit integer "
                  "(" << value->getPosition() << ").");
    }

    // value is small enough to fit
    value_ = static_cast<uint32_t>(check);
}

// **************************** StringParser  *************************

template <> void ValueParser<std::string>::build(ConstElementPtr value) {
    // Invoke common code for all specializations of build().
    buildCommon(value);

    // For strings we need to use stringValue() rather than str().
    // str() returns fully escaped special characters, so
    // single backslash would be misrepresented as "\\".
    if (value->getType() == Element::string) {
        value_ = value->stringValue();
    } else {
        value_ = value->str();
    }
    boost::erase_all(value_, "\"");
}

// ******************** MACSourcesListConfigParser *************************

void
MACSourcesListConfigParser::parse(CfgMACSource& mac_sources, ConstElementPtr value) {
    CfgIface cfg_iface;
    uint32_t source = 0;
    size_t cnt = 0;

    // By default, there's only one source defined: ANY.
    // If user specified anything, we need to get rid of that default.
    mac_sources.clear();

    BOOST_FOREACH(ConstElementPtr source_elem, value->listValue()) {
        std::string source_str = source_elem->stringValue();
        try {
            source = CfgMACSource::MACSourceFromText(source_str);
            mac_sources.add(source);
            ++cnt;
        } catch (const InvalidParameter& ex) {
            isc_throw(DhcpConfigError, "The mac-sources value '" << source_str
                      << "' was specified twice (" << value->getPosition() << ")");
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "Failed to convert '"
                      << source_str << "' to any recognized MAC source:"
                      << ex.what() << " (" << value->getPosition() << ")");
        }
    }

    if (!cnt) {
        isc_throw(DhcpConfigError, "If specified, MAC Sources cannot be empty");
    }
}

// ******************** ControlSocketParser *************************
void ControlSocketParser::parse(SrvConfig& srv_cfg, isc::data::ConstElementPtr value) {
    if (!value) {
        isc_throw(DhcpConfigError, "Logic error: specified control-socket is null");
    }

    if (value->getType() != Element::map) {
        isc_throw(DhcpConfigError, "Specified control-socket is expected to be a map"
                  ", i.e. a structure defined within { }");
    }
    srv_cfg.setControlSocketInfo(value);
}

// **************************** OptionDataParser *************************
OptionDataParser::OptionDataParser(const uint16_t address_family)
    : address_family_(address_family) {
}

std::pair<OptionDescriptor, std::string>
OptionDataParser::parse(isc::data::ConstElementPtr single_option) {

    // Try to create the option instance.
    std::pair<OptionDescriptor, std::string> opt = createOption(single_option);

    if (!opt.first.option_) {
        isc_throw(isc::InvalidOperation,
            "parser logic error: no option has been configured and"
            " thus there is nothing to commit. Has build() been called?");
    }

    return (opt);
}

OptionalValue<uint32_t>
OptionDataParser::extractCode(ConstElementPtr parent) const {
    uint32_t code;
    try {
        code = getInteger(parent, "code");

    } catch (const exception&) {
        // The code parameter was not found. Return an unspecified
        // value.
        return (OptionalValue<uint32_t>());
    }

    if (code == 0) {
        isc_throw(DhcpConfigError, "option code must not be zero "
                  "(" << getPosition("code", parent) << ")");

    } else if (address_family_ == AF_INET &&
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

    return (OptionalValue<uint32_t>(code, OptionalValueState(true)));
}

OptionalValue<std::string>
OptionDataParser::extractName(ConstElementPtr parent) const {
    std::string name;
    try {
        name = getString(parent, "name");

    } catch (...) {
        return (OptionalValue<std::string>());
    }

    if (name.find(" ") != std::string::npos) {
        isc_throw(DhcpConfigError, "invalid option name '" << name
                  << "', space character is not allowed ("
                  << getPosition("name", parent) << ")");
    }

    return (OptionalValue<std::string>(name, OptionalValueState(true)));
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

OptionalValue<bool>
OptionDataParser::extractCSVFormat(ConstElementPtr parent) const {
    bool csv_format = true;
    try {
        csv_format = getBoolean(parent, "csv-format");

    } catch (...) {
        return (OptionalValue<bool>(csv_format));
    }

    return (OptionalValue<bool>(csv_format, OptionalValueState(true)));
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

    } catch (std::exception& ex) {
        // Append position of the option space parameter.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << getPosition("space", parent) << ")");
    }

    return (space);
}

template<typename SearchKey>
OptionDefinitionPtr
OptionDataParser::findOptionDefinition(const std::string& option_space,
                                       const SearchKey& search_key) const {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(option_space, search_key);

    if (!def) {
        // Check if this is a vendor-option. If it is, get vendor-specific
        // definition.
        uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(option_space);
        if (vendor_id) {
            const Option::Universe u = address_family_ == AF_INET ?
                Option::V4 : Option::V6;
            def = LibDHCP::getVendorOptionDef(u, vendor_id, search_key);
        }
    }

    if (!def) {
        // Check if this is an option specified by a user.
        def = CfgMgr::instance().getStagingCfg()->getCfgOptionDef()
            ->get(option_space, search_key);
    }

    return (def);
}

std::pair<OptionDescriptor, std::string>
OptionDataParser::createOption(ConstElementPtr option_data) {
    const Option::Universe universe = address_family_ == AF_INET ?
        Option::V4 : Option::V6;

    OptionalValue<uint32_t> code_param =  extractCode(option_data);
    OptionalValue<std::string> name_param = extractName(option_data);
    OptionalValue<bool> csv_format_param = extractCSVFormat(option_data);
    std::string data_param = extractData(option_data);
    std::string space_param = extractSpace(option_data);

    // Require that option code or option name is specified.
    if (!code_param.isSpecified() && !name_param.isSpecified()) {
        isc_throw(DhcpConfigError, "option data configuration requires one of"
                  " 'code' or 'name' parameters to be specified"
                  << " (" << option_data->getPosition() << ")");
    }

    // Try to find a corresponding option definition using option code or
    // option name.
    OptionDefinitionPtr def = code_param.isSpecified() ?
        findOptionDefinition(space_param, code_param) :
        findOptionDefinition(space_param, name_param);

    // If there is no definition, the user must not explicitly enable the
    // use of csv-format.
    if (!def) {
        // If explicitly requested that the CSV format is to be used,
        // the option definition is a must.
        if (csv_format_param.isSpecified() && csv_format_param) {
            isc_throw(DhcpConfigError, "definition for the option '"
                      << space_param << "." << name_param
                      << "' having code '" << code_param
                      << "' does not exist ("
                      << getPosition("name", option_data)
                      << ")");

        // If there is no option definition and the option code is not specified
        // we have no means to find the option code.
        } else if (name_param.isSpecified() && !code_param.isSpecified()) {
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
    if (def && (!csv_format_param.isSpecified() || csv_format_param)) {
        // If the option data is specified as a string of comma
        // separated values then we need to split this string into
        // individual values - each value will be used to initialize
        // one data field of an option.
        // It is the only usage of the escape option: this allows
        // to embed commas in individual values and to return
        // for instance a string value with embedded commas.
        data_tokens = isc::util::str::tokens(data_param, ",", true);

    } else {
        // Otherwise, the option data is specified as a string of
        // hexadecimal digits that we have to turn into binary format.
        try {
            // The decodeHex function expects that the string contains an
            // even number of digits. If we don't meet this requirement,
            // we have to insert a leading 0.
            if (!data_param.empty() && ((data_param.length() % 2) != 0)) {
                data_param = data_param.insert(0, "0");
            }
            util::encode::decodeHex(data_param, binary);
        } catch (...) {
            isc_throw(DhcpConfigError, "option data is not a valid"
                      << " string of hexadecimal digits: " << data_param
                      << " ("
                      << getPosition("data", option_data)
                      << ")");
        }
    }

    OptionPtr option;
    OptionDescriptor desc(false);

    if (!def) {
        // @todo We have a limited set of option definitions initalized at
        // the moment.  In the future we want to initialize option definitions
        // for all options.  Consequently an error will be issued if an option
        // definition does not exist for a particular option code. For now it is
        // ok to create generic option if definition does not exist.
        OptionPtr option(new Option(universe, static_cast<uint16_t>(code_param),
                                    binary));

        desc.option_ = option;
        desc.persistent_ = false;
    } else {

        // Option name is specified it should match the name in the definition.
        if (name_param.isSpecified() && (def->getName() != name_param.get())) {
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
            bool use_csv = !csv_format_param.isSpecified() || csv_format_param;
            OptionPtr option = use_csv ?
                def->optionFactory(universe, def->getCode(), data_tokens) :
                def->optionFactory(universe, def->getCode(), binary);
            desc.option_ = option;
            desc.persistent_ = false;
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

    // All went good, so we can set the option space name.
    return make_pair(desc, space_param);
}

// **************************** OptionDataListParser *************************
OptionDataListParser::OptionDataListParser(//const std::string&,
                                           //const CfgOptionPtr& cfg,
                                           const uint16_t address_family)
    : address_family_(address_family) {
}


void OptionDataListParser::parse(const CfgOptionPtr& cfg,
                                 isc::data::ConstElementPtr option_data_list) {
    OptionDataParser option_parser(address_family_);
    BOOST_FOREACH(ConstElementPtr data, option_data_list->listValue()) {
        std::pair<OptionDescriptor, std::string> option =
            option_parser.parse(data);
        // Use the option description to keep the formatted value
        cfg->add(option.first, option.second);
        cfg->encapsulate();
    }
}

// ******************************** OptionDefParser ****************************

std::pair<isc::dhcp::OptionDefinitionPtr, std::string>
OptionDefParser::parse(ConstElementPtr option_def) {

    // Get mandatory parameters.
    std::string name = getString(option_def, "name");
    uint32_t code = getInteger(option_def, "code");
    std::string type = getString(option_def, "type");

    // Get optional parameters. Whoever called this parser, should have
    // called SimpleParser::setDefaults first.
    bool array_type = getBoolean(option_def, "array");
    std::string record_types = getString(option_def, "record-types");
    std::string space = getString(option_def, "space");
    std::string encapsulates = getString(option_def, "encapsulate");

    if (!OptionSpace::validateName(space)) {
        isc_throw(DhcpConfigError, "invalid option space name '"
                  << space << "' ("
                  << getPosition("space", option_def) << ")");
    }

    // Create option definition.
    OptionDefinitionPtr def;
    // We need to check if user has set encapsulated option space
    // name. If so, different constructor will be used.
    if (!encapsulates.empty()) {
        // Arrays can't be used together with sub-options.
        if (array_type) {
            isc_throw(DhcpConfigError, "option '" << space << "."
                      << "name" << "', comprising an array of data"
                      << " fields may not encapsulate any option space ("
                      << option_def->getPosition() << ")");

        } else if (encapsulates == space) {
            isc_throw(DhcpConfigError, "option must not encapsulate"
                      << " an option space it belongs to: '"
                      << space << "." << name << "' is set to"
                      << " encapsulate '" << space << "' ("
                      << option_def->getPosition() << ")");

        } else {
            def.reset(new OptionDefinition(name, code, type,
                        encapsulates.c_str()));
        }

    } else {
        def.reset(new OptionDefinition(name, code, type, array_type));

    }

    // Split the list of record types into tokens.
    std::vector<std::string> record_tokens =
    isc::util::str::tokens(record_types, ",");
    // Iterate over each token and add a record type into
    // option definition.
    BOOST_FOREACH(std::string record_type, record_tokens) {
        try {
            boost::trim(record_type);
            if (!record_type.empty()) {
                    def->addRecordField(record_type);
            }
        } catch (const Exception& ex) {
            isc_throw(DhcpConfigError, "invalid record type values"
                      << " specified for the option definition: "
                      << ex.what() << " ("
                      << getPosition("record-types", option_def) << ")");
        }
    }

    // Validate the definition.
    try {
        def->validate();
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what()
                  << " (" << option_def->getPosition() << ")");
    }

    // Option definition has been created successfully.
    return make_pair(def, space);
}

// ******************************** OptionDefListParser ************************
void
OptionDefListParser::parse(CfgOptionDefPtr storage, ConstElementPtr option_def_list) {
    if (!option_def_list) {
        isc_throw(DhcpConfigError, "parser error: a pointer to a list of"
                  << " option definitions is NULL ("
                  << option_def_list->getPosition() << ")");
    }

    OptionDefParser parser;
    BOOST_FOREACH(ConstElementPtr option_def, option_def_list->listValue()) {
        OptionDefinitionTuple def;

        def = parser.parse(option_def);
        try {
            storage->add(def.first, def.second);
        } catch (const std::exception& ex) {
            // Append position if there is a failure.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << option_def->getPosition() << ")");
        }
    }

    // All definitions have been prepared. Put them as runtime options into
    // the libdhcp++.
    LibDHCP::setRuntimeOptionDefs(storage->getContainer());
}

//****************************** RelayInfoParser ********************************
RelayInfoParser::RelayInfoParser(const Option::Universe& family)
    : family_(family) {
};

// Can't use a constructor as a function
namespace {
IOAddress buildIOAddress(const std::string& str) { return (IOAddress(str)); }
};

IOAddress
RelayInfoParser::getIOAddress(ConstElementPtr scope,
                              const std::string& name) {
    return (getAndConvert<IOAddress,
            buildIOAddress>(scope, name, "address"));
}

void
RelayInfoParser::parse(const isc::dhcp::Subnet::RelayInfoPtr& cfg,
                       ConstElementPtr relay_info) {
    // There is only one parameter which is mandatory
    IOAddress ip = getIOAddress(relay_info, "ip-address");

    // Check if the address family matches.
    if ((ip.isV4() && family_ != Option::V4) ||
        (ip.isV6() && family_ != Option::V6) ) {
        isc_throw(DhcpConfigError, "ip-address field " << ip.toText()
                  << " does not have IP address of expected family type: "
                  << (family_ == Option::V4 ? "IPv4" : "IPv6")
                  << " (" << getPosition("ip-address", relay_info) << ")");
    }

    // Ok, we're done with parsing. Let's store the result in the structure
    // we were given as configuration storage.
    *cfg = isc::dhcp::Subnet::RelayInfo(ip);
}

//****************************** PoolParser ********************************

void
PoolParser::parse(PoolStoragePtr pools,
                  ConstElementPtr pool_structure,
                  const uint16_t address_family) {

    ConstElementPtr text_pool = pool_structure->get("pool");

    if (!text_pool) {
        isc_throw(DhcpConfigError, "Mandatory 'pool' entry missing in "
                  "definition: (" << pool_structure->getPosition() << ")");
    }

    // That should be a single pool representation. It should contain
    // text is form prefix/len or first - last. Note that spaces
    // are allowed
    string txt = text_pool->stringValue();

    // first let's remove any whitespaces
    boost::erase_all(txt, " "); // space
    boost::erase_all(txt, "\t"); // tabulation

    PoolPtr pool;

    // Is this prefix/len notation?
    size_t pos = txt.find("/");
    if (pos != string::npos) {
        isc::asiolink::IOAddress addr("::");
        uint8_t len = 0;
        try {
            addr = isc::asiolink::IOAddress(txt.substr(0, pos));

            // start with the first character after /
            string prefix_len = txt.substr(pos + 1);

            // It is lexical cast to int and then downcast to uint8_t.
            // Direct cast to uint8_t (which is really an unsigned char)
            // will result in interpreting the first digit as output
            // value and throwing exception if length is written on two
            // digits (because there are extra characters left over).

            // No checks for values over 128. Range correctness will
            // be checked in Pool4 constructor, here we only check
            // the representation fits in an uint8_t as this can't
            // be done by a direct lexical cast as explained...
            int val_len = boost::lexical_cast<int>(prefix_len);
            if ((val_len < std::numeric_limits<uint8_t>::min()) ||
                (val_len > std::numeric_limits<uint8_t>::max())) {
                // This exception will be handled 4 line later!
                isc_throw(OutOfRange, "");
            }
            len = static_cast<uint8_t>(val_len);
        } catch (...)  {
            isc_throw(DhcpConfigError, "Failed to parse pool "
                      "definition: " << txt << " ("
                      << text_pool->getPosition() << ")");
        }

        try {
            pool = poolMaker(addr, len);
            pools->push_back(pool);
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "Failed to create pool defined by: "
                      << txt << " (" << text_pool->getPosition() << ")");
        }

    } else {
        isc::asiolink::IOAddress min("::");
        isc::asiolink::IOAddress max("::");

        // Is this min-max notation?
        pos = txt.find("-");
        if (pos != string::npos) {
            // using min-max notation
            try {
                min = isc::asiolink::IOAddress(txt.substr(0, pos));
                max = isc::asiolink::IOAddress(txt.substr(pos + 1));
            } catch (...)  {
                isc_throw(DhcpConfigError, "Failed to parse pool "
                          "definition: " << txt << " ("
                          << text_pool->getPosition() << ")");
            }

            try {
                pool = poolMaker(min, max);
                pools->push_back(pool);
            } catch (const std::exception& ex) {
                isc_throw(DhcpConfigError, "Failed to create pool defined by: "
                          << txt << " (" << text_pool->getPosition() << ")");
            }
        }
    }

    if (!pool) {
        isc_throw(DhcpConfigError, "invalid pool definition: "
                  << text_pool->stringValue() <<
                  ". There are two acceptable formats <min address-max address>"
                  " or <prefix/len> ("
                  << text_pool->getPosition() << ")");
    }

    // If there's user-context specified, store it.
    ConstElementPtr user_context = pool_structure->get("user-context");
    if (user_context) {
        if (user_context->getType() != Element::map) {
            isc_throw(isc::dhcp::DhcpConfigError, "User context has to be a map ("
                      << user_context->getPosition() << ")");
        }
        pool->setUserContext(user_context);
    }

    // Parser pool specific options.
    ConstElementPtr option_data = pool_structure->get("option-data");
    if (option_data) {
        try {
            // Currently we don't support specifying options for the DHCPv4 server.
            if (address_family == AF_INET) {
                isc_throw(DhcpConfigError, "option-data is not supported for DHCPv4"
                          " address pools");
            }

            CfgOptionPtr cfg = pool->getCfgOption();
            OptionDataListParser option_parser(address_family);
            option_parser.parse(cfg, option_data);
        } catch (const std::exception& ex) {
            isc_throw(isc::dhcp::DhcpConfigError, ex.what()
                      << " (" << option_data->getPosition() << ")");
        }
    }
}

//****************************** SubnetConfigParser *************************

SubnetConfigParser::SubnetConfigParser(uint16_t family)
    : pools_(new PoolStorage()),
      address_family_(family),
      options_(new CfgOption()) {
    string addr = family == AF_INET ? "0.0.0.0" : "::";
    relay_info_.reset(new isc::dhcp::Subnet::RelayInfo(IOAddress(addr)));
}

SubnetPtr
SubnetConfigParser::parse(ConstElementPtr subnet) {

    ConstElementPtr options_params = subnet->get("option-data");
    if (options_params) {
        OptionDataListParser opt_parser(address_family_);
        opt_parser.parse(options_, options_params);
    }

    ConstElementPtr relay_params = subnet->get("relay");
    if (relay_params) {
        Option::Universe u = (address_family_ == AF_INET) ? Option::V4 : Option::V6;
        RelayInfoParser parser(u);
        parser.parse(relay_info_, relay_params);
    }

    // Create a subnet.
    try {
        createSubnet(subnet);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError,
                  "subnet configuration failed: " << ex.what());
    }

    return (subnet_);
}

Subnet::HRMode
SubnetConfigParser::hrModeFromText(const std::string& txt) {
    if ( (txt.compare("disabled") == 0) ||
         (txt.compare("off") == 0) )  {
        return (Subnet::HR_DISABLED);
    } else if (txt.compare("out-of-pool") == 0) {
        return (Subnet::HR_OUT_OF_POOL);
    } else if (txt.compare("all") == 0) {
        return (Subnet::HR_ALL);
    } else {
        isc_throw(BadValue, "Can't convert '" << txt
                  << "' into any valid reservation-mode values");
    }
}

void
SubnetConfigParser::createSubnet(ConstElementPtr params) {
    std::string subnet_txt;
    try {
        subnet_txt = getString(params, "subnet");
    } catch (const DhcpConfigError &) {
        // rethrow with precise error
        isc_throw(DhcpConfigError,
                 "mandatory 'subnet' parameter is missing for a subnet being"
                  " configured (" << params->getPosition() << ")");
    }

    // Remove any spaces or tabs.
    boost::erase_all(subnet_txt, " ");
    boost::erase_all(subnet_txt, "\t");

    // The subnet format is prefix/len. We are going to extract
    // the prefix portion of a subnet string to create IOAddress
    // object from it. IOAddress will be passed to the Subnet's
    // constructor later on. In order to extract the prefix we
    // need to get all characters preceding "/".
    size_t pos = subnet_txt.find("/");
    if (pos == string::npos) {
        ConstElementPtr elem = params->get("subnet");
        isc_throw(DhcpConfigError,
                  "Invalid subnet syntax (prefix/len expected):" << subnet_txt
                  << " (" << elem->getPosition() << ")");
    }

    // Try to create the address object. It also validates that
    // the address syntax is ok.
    isc::asiolink::IOAddress addr(subnet_txt.substr(0, pos));
    uint8_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

    // Call the subclass's method to instantiate the subnet
    initSubnet(params, addr, len);

    // Add pools to it.
    for (PoolStorage::iterator it = pools_->begin(); it != pools_->end();
         ++it) {
        try {
            subnet_->addPool(*it);
        } catch (const BadValue& ex) {
            // addPool() can throw BadValue if the pool is overlapping or
            // is out of bounds for the subnet.
            isc_throw(DhcpConfigError,
                      ex.what() << " (" << params->getPosition() << ")");
        }
    }

    // Now configure parameters that are common for v4 and v6:

    // Get interface name. If it is defined, then the subnet is available
    // directly over specified network interface.
    std::string iface = getString(params, "interface");
    if (!iface.empty()) {
        if (!IfaceMgr::instance().getIface(iface)) {
            ConstElementPtr error = params->get("interface");
            isc_throw(DhcpConfigError, "Specified network interface name " << iface
                      << " for subnet " << subnet_->toText()
                      << " is not present in the system ("
                      << error->getPosition() << ")");
        }

        subnet_->setIface(iface);
    }

    // Let's set host reservation mode. If not specified, the default value of
    // all will be used.
    try {
        std::string hr_mode = getString(params, "reservation-mode");
        subnet_->setHostReservationMode(hrModeFromText(hr_mode));
    } catch (const BadValue& ex) { 
       isc_throw(DhcpConfigError, "Failed to process specified value "
                  " of reservation-mode parameter: " << ex.what()
                  << "(" << getPosition("reservation-mode", params) << ")");
    }

    // Try setting up client class.
    string client_class = getString(params, "client-class");
    if (!client_class.empty()) {
        subnet_->allowClientClass(client_class);
    }

    // Here globally defined options were merged to the subnet specific
    // options but this is no longer the case (they have a different
    // and not consecutive priority).

    // Copy options to the subnet configuration.
    options_->copyTo(*subnet_->getCfgOption());
}

//**************************** D2ClientConfigParser **********************

IOAddress
D2ClientConfigParser::getIOAddress(ConstElementPtr scope,
                                   const std::string& name) {
    return (getAndConvert<IOAddress,
            buildIOAddress>(scope, name, "address"));
}

dhcp_ddns::NameChangeProtocol
D2ClientConfigParser::getProtocol(ConstElementPtr scope,
                                  const std::string& name) {
    return (getAndConvert<dhcp_ddns::NameChangeProtocol,
            dhcp_ddns::stringToNcrProtocol>
            (scope, name, "NameChangeRequest protocol"));
}

dhcp_ddns::NameChangeFormat
D2ClientConfigParser::getFormat(ConstElementPtr scope,
                                const std::string& name) {
    return (getAndConvert<dhcp_ddns::NameChangeFormat,
            dhcp_ddns::stringToNcrFormat>
            (scope, name, "NameChangeRequest format"));
}

D2ClientConfig::ReplaceClientNameMode
D2ClientConfigParser::getMode(ConstElementPtr scope,
                              const std::string& name) {
    return (getAndConvert<D2ClientConfig::ReplaceClientNameMode,
            D2ClientConfig::stringToReplaceClientNameMode>
            (scope, name, "ReplaceClientName mode"));
}

D2ClientConfigPtr
D2ClientConfigParser::parse(isc::data::ConstElementPtr client_config) {
    D2ClientConfigPtr new_config;

    // Get all parameters that are needed to create the D2ClientConfig.
    bool enable_updates = getBoolean(client_config, "enable-updates");

    IOAddress server_ip = getIOAddress(client_config, "server-ip");

    uint32_t server_port = getUint32(client_config, "server-port");

    std::string sender_ip_str = getString(client_config, "sender-ip");

    uint32_t sender_port = getUint32(client_config, "sender-port"); 

    uint32_t max_queue_size = getUint32(client_config, "max-queue-size"); 

    dhcp_ddns::NameChangeProtocol ncr_protocol =
        getProtocol(client_config, "ncr-protocol");

    dhcp_ddns::NameChangeFormat ncr_format =
        getFormat(client_config, "ncr-format");

    bool always_include_fqdn =
        getBoolean(client_config, "always-include-fqdn");

    bool override_no_update =
        getBoolean(client_config, "override-no-update");

    bool override_client_update =
        getBoolean(client_config, "override-client-update");

    D2ClientConfig::ReplaceClientNameMode replace_client_name_mode =
        getMode(client_config, "replace-client-name");

    std::string generated_prefix =
        getString(client_config, "generated-prefix");

    // qualifying-suffix is the only parameter which has no default
    std::string qualifying_suffix = "";
    bool found_qualifying_suffix = false;
    if (client_config->contains("qualifying-suffix")) {
            qualifying_suffix = getString(client_config, "qualifying-suffix");
            found_qualifying_suffix = true;
    }   

    IOAddress sender_ip(0);
    if (sender_ip_str.empty()) {
        // The default sender IP depends on the server IP family
        sender_ip = (server_ip.isV4() ? IOAddress::IPV4_ZERO_ADDRESS() :
                                        IOAddress::IPV6_ZERO_ADDRESS());
    } else {
        try {
            sender_ip = IOAddress(sender_ip_str);
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "invalid address (" << sender_ip_str
                      << ") specified for parameter 'sender-ip' ("
                      << getPosition("sender-ip", client_config) << ")");
        }
    }

    // Qualifying-suffix is required when updates are enabled
    if (enable_updates && !found_qualifying_suffix) {
        isc_throw(DhcpConfigError,
                  "parameter 'qualifying-suffix' is required when "
                  "updates are enabled ("
                  << client_config->getPosition() << ")");
    }

    // Now we check for logical errors. This repeats what is done in
    // D2ClientConfig::validate(), but doing it here permits us to
    // emit meaningful parameter position info in the error.
    if (ncr_format != dhcp_ddns::FMT_JSON) {
        isc_throw(D2ClientError, "D2ClientConfig error: NCR Format: "
                  << dhcp_ddns::ncrFormatToString(ncr_format)
                  << " is not supported. ("
                  << getPosition("ncr-format", client_config) << ")");
    }

    if (ncr_protocol != dhcp_ddns::NCR_UDP) {
        isc_throw(D2ClientError, "D2ClientConfig error: NCR Protocol: "
                  << dhcp_ddns::ncrProtocolToString(ncr_protocol)
                  << " is not supported. ("
                  << getPosition("ncr-protocol", client_config) << ")");
    }

    if (sender_ip.getFamily() != server_ip.getFamily()) {
        isc_throw(D2ClientError,
                  "D2ClientConfig error: address family mismatch: "
                  << "server-ip: " << server_ip.toText()
                  << " is: " << (server_ip.isV4() ? "IPv4" : "IPv6")
                  << " while sender-ip: "  << sender_ip.toText()
                  << " is: " << (sender_ip.isV4() ? "IPv4" : "IPv6")
                  << " (" << getPosition("sender-ip", client_config) << ")");
    }

    if (server_ip == sender_ip && server_port == sender_port) {
        isc_throw(D2ClientError,
                  "D2ClientConfig error: server and sender cannot"
                  " share the exact same IP address/port: "
                  << server_ip.toText() << "/" << server_port
                  << " (" << getPosition("sender-ip", client_config) << ")");
    }

    try {
        // Attempt to create the new client config.
        new_config.reset(new D2ClientConfig(enable_updates,
                                            server_ip,
                                            server_port,
                                            sender_ip,
                                            sender_port,
                                            max_queue_size,
                                            ncr_protocol,
                                            ncr_format,
                                            always_include_fqdn,
                                            override_no_update,
                                            override_client_update,
                                            replace_client_name_mode,
                                            generated_prefix,
                                            qualifying_suffix));

    }  catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << client_config->getPosition() << ")");
    }

    return(new_config);
}

/// @brief This table defines default values for D2 client configuration
const SimpleDefaults D2ClientConfigParser::D2_CLIENT_CONFIG_DEFAULTS = {
    // enable-updates is unconditionally required
    { "server-ip", Element::string, "127.0.0.1" },
    { "server-port", Element::integer, "53001" },
    // default sender-ip depends on server-ip family, so we leave default blank
    // parser knows to use the appropriate ZERO address based on server-ip
    { "sender-ip", Element::string, "" },
    { "sender-port", Element::integer, "0" },
    { "max-queue-size", Element::integer, "1024" },
    { "ncr-protocol", Element::string, "UDP" },
    { "ncr-format", Element::string, "JSON" },
    { "always-include-fqdn", Element::boolean, "false" },
    { "override-no-update", Element::boolean, "false" },
    { "override-client-update", Element::boolean, "false" },
    { "replace-client-name", Element::string, "never" },
    { "generated-prefix", Element::string, "myhost" }
    // qualifying-suffix has no default
};

size_t
D2ClientConfigParser::setAllDefaults(isc::data::ConstElementPtr d2_config) {
    ElementPtr mutable_d2 = boost::const_pointer_cast<Element>(d2_config);
    return (SimpleParser::setDefaults(mutable_d2, D2_CLIENT_CONFIG_DEFAULTS));
}

};  // namespace dhcp
};  // namespace isc
