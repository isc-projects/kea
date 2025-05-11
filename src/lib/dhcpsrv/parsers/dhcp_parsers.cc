// Copyright (C) 2013-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/http_command_config.h>
#include <config/unix_command_config.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <util/encode/encode.h>
#include <util/str.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>

#include <limits>
#include <map>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::util;
namespace ph = std::placeholders;

namespace isc {
namespace dhcp {

// ******************** MACSourcesListConfigParser *************************

void
MACSourcesListConfigParser::parse(CfgMACSource& mac_sources, ConstElementPtr value) {
    uint32_t source = 0;
    size_t cnt = 0;

    // By default, there's only one source defined: ANY.
    // If user specified anything, we need to get rid of that default.
    mac_sources.clear();

    for (auto const& source_elem : value->listValue()) {
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

// ******************** ControlSocketsParser *************************
void ControlSocketsParser::parse(SrvConfig& srv_cfg, ConstElementPtr value) {
    if (value->getType() != Element::list) {
        // Sanity check: not supposed to fail.
        isc_throw(DhcpConfigError,
                  "Specified control-sockets is expected to be a list");
    }
    bool seen_unix(false);
    ElementPtr unix_config = Element::createList();
    ElementPtr http_config = Element::createList();
    for (ElementPtr socket : value->listValue()) {
        if (socket->getType() != Element::map) {
            // Sanity check: not supposed to fail.
            isc_throw(DhcpConfigError,
                      "Specified control-sockets is expected to be a list of maps");
        }
        ConstElementPtr socket_type = socket->get("socket-type");
        if (!socket_type) {
            isc_throw(DhcpConfigError,
                      "'socket-type' parameter is mandatory in control-sockets items");
        }
        if (socket_type->getType() != Element::string) {
            // Sanity check: not supposed to fail.
            isc_throw(DhcpConfigError,
                      "'socket-type' parameter is expected to be a string");
        }
        string type = socket_type->stringValue();
        if (type == "unix") {
            if (seen_unix) {
                isc_throw(DhcpConfigError,
                          "control socket of type 'unix' already configured");
            }
            UnixCommandConfig cmd_config(socket);
            seen_unix = true;
            unix_config->add(socket);
        } else if ((type == "http") || (type == "https")) {
            HttpCommandConfig cmd_config(socket);
            http_config->add(socket);
        } else {
            // Sanity check: not supposed to fail.
            isc_throw(DhcpConfigError,
                      "unsupported 'socket-type': '" << type
                      << "' not 'unix', 'http' or 'https'");
        }
    }
    if (unix_config->size()) {
        srv_cfg.setUnixControlSocketInfo(unix_config);
    }
    if (http_config->size()) {
        srv_cfg.setHttpControlSocketInfo(http_config);
    }
}

// ******************************** OptionDefParser ****************************

OptionDefParser::OptionDefParser(const uint16_t address_family)
    : address_family_(address_family) {
}

OptionDefinitionPtr
OptionDefParser::parse(ConstElementPtr option_def) {

    // Check parameters.
    if (address_family_ == AF_INET) {
        checkKeywords(SimpleParser4::OPTION4_DEF_PARAMETERS, option_def);
    } else {
        checkKeywords(SimpleParser6::OPTION6_DEF_PARAMETERS, option_def);
    }

    // Get mandatory parameters.
    std::string name = getString(option_def, "name");
    int64_t code64 = getInteger(option_def, "code");
    std::string type = getString(option_def, "type");

    // Get optional parameters. Whoever called this parser, should have
    // called SimpleParser::setDefaults first.
    bool array_type = getBoolean(option_def, "array");
    std::string record_types = getString(option_def, "record-types");
    std::string space = getString(option_def, "space");
    std::string encapsulates = getString(option_def, "encapsulate");
    ConstElementPtr user_context = option_def->get("user-context");

    // Check code value.
    if (code64 < 0) {
        isc_throw(DhcpConfigError, "option code must not be negative "
                  "(" << getPosition("code", option_def) << ")");
    } else if (address_family_ == AF_INET &&
               code64 > std::numeric_limits<uint8_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << code64
                  << "', it must not be greater than '"
                  << static_cast<int>(std::numeric_limits<uint8_t>::max())
                  << "' (" << getPosition("code", option_def) << ")");
    } else if (address_family_ == AF_INET6 &&
               code64 > std::numeric_limits<uint16_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << code64
                  << "', it must not be greater than '"
                  << std::numeric_limits<uint16_t>::max()
                  << "' (" << getPosition("code", option_def) << ")");
    }
    uint32_t code = static_cast<uint32_t>(code64);

    // Validate space name.
    if (!OptionSpace::validateName(space)) {
        isc_throw(DhcpConfigError, "invalid option space name '"
                  << space << "' ("
                  << getPosition("space", option_def) << ")");
    }

    // Protect against definition of options 0 (PAD) or 255 (END)
    // in (and only in) the dhcp4 space.
    if (space == DHCP4_OPTION_SPACE) {
        if (code == DHO_PAD) {
            isc_throw(DhcpConfigError, "invalid option code '0': "
                      << "reserved for PAD ("
                      << getPosition("code", option_def) << ")");
        } else if (code == DHO_END) {
            isc_throw(DhcpConfigError, "invalid option code '255': "
                      << "reserved for END ("
                      << getPosition("code", option_def) << ")");
        }
    }

    // For dhcp6 space the value 0 is reserved.
    if (space == DHCP6_OPTION_SPACE) {
        if (code == 0) {
            isc_throw(DhcpConfigError, "invalid option code '0': "
                      << "reserved value ("
                      << getPosition("code", option_def) << ")");
        }
    }

    // Create option definition.
    OptionDefinitionPtr def;
    // We need to check if user has set encapsulated option space
    // name. If so, different constructor will be used.
    if (!encapsulates.empty()) {
        // Arrays can't be used together with sub-options.
        if (array_type) {
            isc_throw(DhcpConfigError, "option '" << space << "."
                      << name << "', comprising an array of data"
                      << " fields may not encapsulate any option space ("
                      << option_def->getPosition() << ")");

        } else if (encapsulates == space) {
            isc_throw(DhcpConfigError, "option must not encapsulate"
                      << " an option space it belongs to: '"
                      << space << "." << name << "' is set to"
                      << " encapsulate '" << space << "' ("
                      << option_def->getPosition() << ")");

        } else {
            def.reset(new OptionDefinition(name, code, space, type,
                      encapsulates.c_str()));
        }

    } else {
        def.reset(new OptionDefinition(name, code, space, type, array_type));

    }

    if (user_context) {
        def->setContext(user_context);
    }

    // Split the list of record types into tokens.
    std::vector<std::string> record_tokens =
    isc::util::str::tokens(record_types, ",");
    // Iterate over each token and add a record type into
    // option definition.
    for (auto const& record_type : record_tokens) {
        try {
            auto const trim_rec = boost::trim_copy(record_type);
            if (!trim_rec.empty()) {
                def->addRecordField(trim_rec);
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
    return (def);
}

// ******************************** OptionDefListParser ************************

OptionDefListParser::OptionDefListParser(const uint16_t address_family)
    : address_family_(address_family) {
}

void
OptionDefListParser::parse(CfgOptionDefPtr storage, ConstElementPtr option_def_list) {
    if (!option_def_list) {
        // Sanity check: not supposed to fail.
        isc_throw(DhcpConfigError, "parser error: a pointer to a list of"
                  << " option definitions is NULL ("
                  << option_def_list->getPosition() << ")");
    }

    OptionDefParser parser(address_family_);
    for (auto const& option_def : option_def_list->listValue()) {
        OptionDefinitionPtr def = parser.parse(option_def);
        try {
            storage->add(def);
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

void
RelayInfoParser::parse(const isc::dhcp::Network::RelayInfoPtr& relay_info,
                       ConstElementPtr relay_elem) {

    if (relay_elem->getType() != Element::map) {
        isc_throw(DhcpConfigError, "relay must be a map");
    }

    ConstElementPtr addresses = relay_elem->get("ip-addresses");
    if (!addresses) {
        isc_throw(DhcpConfigError, "ip-addresses is required");
    }

    // Create our resultant RelayInfo structure
    *relay_info = isc::dhcp::Network::RelayInfo();

    if (addresses->getType() != Element::list) {
        isc_throw(DhcpConfigError, "ip-addresses must be a list "
                  "(" << getPosition("ip-addresses", relay_elem) << ")");
    }

    for (auto const& address_element : addresses->listValue()) {
        addAddress("ip-addresses", address_element->stringValue(),
                   relay_elem, relay_info);
    }
}

void
RelayInfoParser::addAddress(const std::string& name,
                            const std::string& address_str,
                            ConstElementPtr relay_elem,
                            const isc::dhcp::Network::RelayInfoPtr& relay_info) {
    boost::scoped_ptr<isc::asiolink::IOAddress> ip;
    try {
        ip.reset(new isc::asiolink::IOAddress(address_str));
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, "address " << address_str
                  << " is not a valid: "
                  << (family_ == Option::V4 ? "IPv4" : "IPv6")
                  << "address"
                  << " (" << getPosition(name, relay_elem) << ")");
    }

    // Check if the address family matches.
    if ((ip->isV4() && family_ != Option::V4) ||
        (ip->isV6() && family_ != Option::V6) ) {
        isc_throw(DhcpConfigError, "address " << address_str
                  << " is not a: "
                  << (family_ == Option::V4 ? "IPv4" : "IPv6")
                  << "address"
                  << " (" << getPosition(name, relay_elem) << ")");
    }

    try {
        relay_info->addAddress(*ip);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, "cannot add address: " << address_str
                  << " to relay info: " << ex.what()
                  << " (" << getPosition(name, relay_elem) << ")");
    }
}

//****************************** PoolParser ********************************

void
PoolParser::parse(PoolStoragePtr pools,
                  ConstElementPtr pool_structure,
                  const uint16_t address_family,
                  bool encapsulate_options) {

    if (address_family == AF_INET) {
        checkKeywords(SimpleParser4::POOL4_PARAMETERS, pool_structure);
    } else {
        checkKeywords(SimpleParser6::POOL6_PARAMETERS, pool_structure);
    }

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
        } catch (...) {
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
            } catch (...) {
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

    // If there is a pool-id, store it.
    ConstElementPtr pool_id = pool_structure->get("pool-id");
    if (pool_id) {
        if (pool_id->intValue() <= 0) {
            isc_throw(BadValue, "pool-id " << pool_id->intValue() << " is not"
                      << " a positive integer greater than 0");
        } else if (pool_id->intValue() > numeric_limits<uint32_t>::max()) {
            isc_throw(BadValue, "pool-id " << pool_id->intValue() << " is not"
                      << " a 32 bit unsigned integer");
        }

        pool->setID(pool_id->intValue());
    }

    // If there's user-context specified, store it.
    ConstElementPtr user_context = pool_structure->get("user-context");
    if (user_context) {
        // The grammar accepts only maps but still check it.
        if (user_context->getType() != Element::map) {
            isc_throw(isc::dhcp::DhcpConfigError, "User context has to be a map ("
                      << user_context->getPosition() << ")");
        }
        pool->setContext(user_context);
    }

    // Parser pool specific options.
    ConstElementPtr option_data = pool_structure->get("option-data");
    if (option_data) {
        try {
            CfgOptionPtr cfg = pool->getCfgOption();
            auto option_parser = createOptionDataListParser(address_family);
            option_parser->parse(cfg, option_data, encapsulate_options);
        } catch (const std::exception& ex) {
            isc_throw(isc::dhcp::DhcpConfigError, ex.what()
                      << " (" << option_data->getPosition() << ")");
        }
    }

    // Client-class.
    ConstElementPtr client_class = pool_structure->get("client-class");
    if (client_class) {
        string cclass = client_class->stringValue();
        if (!cclass.empty()) {
            pool->allowClientClass(cclass);
        }
    }

    // Setup client class list.
    BaseNetworkParser::getClientClassesElem(pool_structure,
                                            std::bind(&Pool::allowClientClass,
                                                      pool, ph::_1));

    // Setup additional class list.
    BaseNetworkParser::getAdditionalClassesElem(pool_structure,
                                                std::bind(&Pool::addAdditionalClass,
                                                          pool, ph::_1));

    // Parse DDNS behavioral parameters.
    BaseNetworkParser parser;
    parser.parseDdnsParameters(pool_structure, pool);
}

boost::shared_ptr<OptionDataListParser>
PoolParser::createOptionDataListParser(const uint16_t address_family) const {
    return (boost::make_shared<OptionDataListParser>(address_family));
}

//****************************** Pool4Parser *************************

PoolPtr
Pool4Parser::poolMaker (IOAddress &addr, uint32_t len, int32_t) {
    return (PoolPtr(new Pool4(addr, len)));
}

PoolPtr
Pool4Parser::poolMaker (IOAddress &min, IOAddress &max, int32_t) {
    return (PoolPtr(new Pool4(min, max)));
}

//****************************** Pools4ListParser *************************

void
Pools4ListParser::parse(PoolStoragePtr pools, ConstElementPtr pools_list,
                        bool encapsulate_options) {
    for (auto const& pool : pools_list->listValue()) {
        auto const& parser = createPoolConfigParser();
        parser->parse(pools, pool, AF_INET, encapsulate_options);
    }
}

boost::shared_ptr<PoolParser>
Pools4ListParser::createPoolConfigParser() const {
    return (boost::make_shared<Pool4Parser>());
}

//****************************** SubnetConfigParser *************************

SubnetConfigParser::SubnetConfigParser(uint16_t family, bool check_iface)
    : pools_(new PoolStorage()),
      address_family_(family),
      check_iface_(check_iface) {
    relay_info_.reset(new isc::dhcp::Network::RelayInfo());
}

SubnetPtr
SubnetConfigParser::parse(ConstElementPtr subnet, bool encapsulate_options) {

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

    // We create subnet first and then parse the options straight into the subnet's
    // CfgOption structure. Previously, we first parsed the options and then copied
    // them into the CfgOption after creating the subnet but it had two issues. First,
    // it cost performance. Second, copying options reset the isEncapsulated() flag.
    // If the options have been encapsulated we want to preserve the flag to ensure
    // they are not encapsulated several times.
    ConstElementPtr options_params = subnet->get("option-data");
    if (options_params) {
        auto opt_parser = createOptionDataListParser();
        opt_parser->parse(subnet_->getCfgOption(), options_params, encapsulate_options);
    }

    return (subnet_);
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

    // Now parse out the prefix length.
    unsigned int len;
    try {
        len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));
    } catch (const boost::bad_lexical_cast&) {
        ConstElementPtr elem = params->get("subnet");
        isc_throw(DhcpConfigError, "prefix length: '" <<
                  subnet_txt.substr(pos+1) << "' is not an integer ("
                   << elem->getPosition() << ")");
    }

    // Sanity check the prefix length
    if ((addr.isV6() && len > 128) ||
        (addr.isV4() && len > 32)) {
        ConstElementPtr elem = params->get("subnet");
        isc_throw(BadValue,
                  "Invalid prefix length specified for subnet: " << len
                  << " (" << elem->getPosition() << ")");
    }

    // Call the subclass's method to instantiate the subnet
    initSubnet(params, addr, len);

    // Add pools to it.
    for (auto const& pool : *pools_) {
        try {
            subnet_->addPool(pool);
        } catch (const BadValue& ex) {
            // addPool() can throw BadValue if the pool is overlapping or
            // is out of bounds for the subnet.
            isc_throw(DhcpConfigError,
                      ex.what() << " (" << params->getPosition() << ")");
        }
    }
    // If there's user-context specified, store it.
    ConstElementPtr user_context = params->get("user-context");
    if (user_context) {
        // The grammar accepts only maps but still check it.
        if (user_context->getType() != Element::map) {
            isc_throw(isc::dhcp::DhcpConfigError, "User context has to be a map ("
                      << user_context->getPosition() << ")");
        }
        subnet_->setContext(user_context);
    }

    // In order to take advantage of the dynamic inheritance of global
    // parameters to a subnet we need to set a callback function for each
    // subnet to allow for fetching global parameters.
    subnet_->setFetchGlobalsFn([]() -> ConstCfgGlobalsPtr {
        return (CfgMgr::instance().getCurrentCfg()->getConfiguredGlobals());
    });
}

boost::shared_ptr<OptionDataListParser>
SubnetConfigParser::createOptionDataListParser() const {
    return (boost::make_shared<OptionDataListParser>(address_family_));
}

//****************************** Subnet4ConfigParser *************************

Subnet4ConfigParser::Subnet4ConfigParser(bool check_iface)
    : SubnetConfigParser(AF_INET, check_iface) {
}

Subnet4Ptr
Subnet4ConfigParser::parse(ConstElementPtr subnet, bool encapsulate_options) {
    // Check parameters.
    checkKeywords(SimpleParser4::SUBNET4_PARAMETERS, subnet);

    /// Parse Pools first.
    ConstElementPtr pools = subnet->get("pools");
    if (pools) {
        auto const& parser = createPoolsListParser();
        parser->parse(pools_, pools, encapsulate_options);
    }

    SubnetPtr generic = SubnetConfigParser::parse(subnet, encapsulate_options);

    if (!generic) {
        // Sanity check: not supposed to fail.
        isc_throw(DhcpConfigError,
                  "Failed to create an IPv4 subnet (" <<
                  subnet->getPosition() << ")");
    }

    Subnet4Ptr sn4ptr = boost::dynamic_pointer_cast<Subnet4>(subnet_);
    if (!sn4ptr) {
        // If we hit this, it is a programming error.
        isc_throw(Unexpected,
                  "Invalid Subnet4 cast in Subnet4ConfigParser::parse");
    }

    // Set relay information if it was parsed
    if (relay_info_) {
        sn4ptr->setRelayInfo(*relay_info_);
    }

    // Parse Host Reservations for this subnet if any.
    ConstElementPtr reservations = subnet->get("reservations");
    if (reservations) {
        HostCollection hosts;
        HostReservationsListParser<HostReservationParser4> parser;
        parser.parse(subnet_->getID(), reservations, hosts);
        for (auto const& h : hosts) {
            validateResv(sn4ptr, h);
            CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(h);
        }
    }

    // Parse allocator specification.
    auto network4 = boost::dynamic_pointer_cast<Network>(sn4ptr);
    parseAllocatorParams(subnet, network4);

    // Instantiate the allocator.
    sn4ptr->createAllocators();

    return (sn4ptr);
}

void
Subnet4ConfigParser::initSubnet(data::ConstElementPtr params,
                                asiolink::IOAddress addr, uint8_t len) {
    // Subnet ID is required and must be in 1..SUBNET_ID_MAX.
    int64_t subnet_id_max = static_cast<int64_t>(SUBNET_ID_MAX);
    SubnetID subnet_id = static_cast<SubnetID>(getInteger(params, "id", 1,
                                                          subnet_id_max));

    auto subnet4 = Subnet4::create(addr, len, Triplet<uint32_t>(),
                                   Triplet<uint32_t>(), Triplet<uint32_t>(),
                                   subnet_id);
    subnet_ = subnet4;

    ElementPtr mutable_params;
    mutable_params = boost::const_pointer_cast<Element>(params);

    // Parse parameters common to all Network derivations.
    NetworkPtr network = boost::dynamic_pointer_cast<Network>(subnet4);
    parseCommon(mutable_params, network);

    std::ostringstream output;
    output << addr << "/" << static_cast<int>(len) << " with params: ";

    bool has_renew = !subnet4->getT1().unspecified();
    bool has_rebind = !subnet4->getT2().unspecified();
    int64_t renew = -1;
    int64_t rebind = -1;

    // t1 and t2 are optional may be not specified.
    if (has_renew) {
        renew = subnet4->getT1().get();
        output << "t1=" << renew << ", ";
    }
    if (has_rebind) {
        rebind = subnet4->getT2().get();
        output << "t2=" << rebind << ", ";
    }

    if (!subnet4->getValid().unspecified()) {
        output << "valid-lifetime=" << subnet4->getValid().get();
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_NEW_SUBNET4).arg(output.str());

    // Set the match-client-id value for the subnet.
    if (params->contains("match-client-id")) {
        bool match_client_id = getBoolean(params, "match-client-id");
        subnet4->setMatchClientId(match_client_id);
    }

    // Set the authoritative value for the subnet.
    if (params->contains("authoritative")) {
        bool authoritative = getBoolean(params, "authoritative");
        subnet4->setAuthoritative(authoritative);
    }

    // Set next-server. The default value is 0.0.0.0. Nevertheless, the
    // user could have messed that up by specifying incorrect value.
    // To avoid using 0.0.0.0, user can specify "".
    if (params->contains("next-server")) {
        string next_server;
        try {
            next_server = getString(params, "next-server");
            if (!next_server.empty()) {
                subnet4->setSiaddr(IOAddress(next_server));
            }
        } catch (...) {
            ConstElementPtr next = params->get("next-server");
            string pos;
            if (next) {
                pos = next->getPosition().str();
            } else {
                pos = params->getPosition().str();
            }
            isc_throw(DhcpConfigError, "invalid parameter next-server : "
                      << next_server << "(" << pos << ")");
        }
    }

    // Set server-hostname.
    if (params->contains("server-hostname")) {
        std::string sname = getString(params, "server-hostname");
        if (!sname.empty()) {
            if (sname.length() >= Pkt4::MAX_SNAME_LEN) {
                ConstElementPtr error = params->get("server-hostname");
                isc_throw(DhcpConfigError, "server-hostname must be at most "
                          << Pkt4::MAX_SNAME_LEN - 1 << " bytes long, it is "
                          << sname.length() << " ("
                          << error->getPosition() << ")");
            }
            subnet4->setSname(sname);
        }
    }

    // Set boot-file-name.
    if (params->contains("boot-file-name")) {
        std::string filename =getString(params, "boot-file-name");
        if (!filename.empty()) {
            if (filename.length() > Pkt4::MAX_FILE_LEN) {
                ConstElementPtr error = params->get("boot-file-name");
                isc_throw(DhcpConfigError, "boot-file-name must be at most "
                          << Pkt4::MAX_FILE_LEN - 1 << " bytes long, it is "
                          << filename.length() << " ("
                          << error->getPosition() << ")");
            }
            subnet4->setFilename(filename);
        }
    }

    // Get interface name. If it is defined, then the subnet is available
    // directly over specified network interface.
    if (params->contains("interface")) {
        std::string iface = getString(params, "interface");
        if (!iface.empty()) {
            if (check_iface_ && !IfaceMgr::instance().getIface(iface)) {
                ConstElementPtr error = params->get("interface");
                isc_throw(DhcpConfigError, "Specified network interface name " << iface
                          << " for subnet " << subnet4->toText()
                          << " is not present in the system ("
                          << error->getPosition() << ")");
            }

            subnet4->setIface(iface);
        }
    }

    // Try setting up client class.
    if (params->contains("client-class")) {
        string client_class = getString(params, "client-class");
        if (!client_class.empty()) {
            subnet4->allowClientClass(client_class);
        }
    }

    // Setup client class list.
    getClientClassesElem(params, std::bind(&Network::allowClientClass,
                                           boost::dynamic_pointer_cast<Network>(subnet4), ph::_1));

    // Setup additional class list.
    getAdditionalClassesElem(params, std::bind(&Network::addAdditionalClass,
                                               boost::dynamic_pointer_cast<Network>(subnet4), ph::_1));

    // 4o6 specific parameter: 4o6-interface.
    if (params->contains("4o6-interface")) {
        string iface4o6 = getString(params, "4o6-interface");
        if (!iface4o6.empty()) {
            subnet4->get4o6().setIface4o6(iface4o6);
            subnet4->get4o6().enabled(true);
        }
    }

    // 4o6 specific parameter: 4o6-subnet.
    if (params->contains("4o6-subnet")) {
        string subnet4o6 = getString(params, "4o6-subnet");
        if (!subnet4o6.empty()) {
            size_t slash = subnet4o6.find("/");
            if (slash == std::string::npos) {
                isc_throw(DhcpConfigError, "Missing / in the 4o6-subnet parameter:"
                          << subnet4o6 << ", expected format: prefix6/length");
            }
            string prefix = subnet4o6.substr(0, slash);
            string lenstr = subnet4o6.substr(slash + 1);

            len = 128;
            try {
                len = boost::lexical_cast<unsigned int>(lenstr.c_str());
            } catch (const boost::bad_lexical_cast &) {
                isc_throw(DhcpConfigError, "Invalid prefix length specified in "
                          "4o6-subnet parameter: " << subnet4o6 << ", expected 0..128 value");
            }
            subnet4->get4o6().setSubnet4o6(IOAddress(prefix), len);
            subnet4->get4o6().enabled(true);
        }
    }

    // Try 4o6 specific parameter: 4o6-interface-id
    if (params->contains("4o6-interface-id")) {
        std::string ifaceid = getString(params, "4o6-interface-id");
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet4->get4o6().setInterfaceId(opt);
            subnet4->get4o6().enabled(true);
        }
    }

    /// client-class processing is now generic and handled in the common
    /// code (see isc::data::SubnetConfigParser::createSubnet)

    // Here globally defined options were merged to the subnet specific
    // options but this is no longer the case (they have a different
    // and not consecutive priority).

    // Parse t1-percent and t2-percent
    parseTeePercents(params, network);

    // Parse DDNS parameters
    parseDdnsParams(params, network);

    // Parse lease cache parameters
    parseCacheParams(params, network);

    // Set the offer_lft value for the subnet.
    if (params->contains("offer-lifetime")) {
        uint32_t offer_lft = getInteger(params, "offer-lifetime");
        subnet4->setOfferLft(offer_lft);
    }

    // Parse offer-lifetime parameter.
    Network4Ptr network4 = boost::dynamic_pointer_cast<Network4>(subnet4);
    parseOfferLft(params, network4);

}

void
Subnet4ConfigParser::validateResv(const Subnet4Ptr& subnet, ConstHostPtr host) {
    const IOAddress& address = host->getIPv4Reservation();
    if (!address.isV4Zero() && !subnet->inRange(address)) {
        isc_throw(DhcpConfigError, "specified reservation '" << address
                  << "' is not within the IPv4 subnet '"
                  << subnet->toText() << "'");
    }
}

boost::shared_ptr<PoolsListParser>
Subnet4ConfigParser::createPoolsListParser() const {
    return (boost::make_shared<Pools4ListParser>());
}

//**************************** Subnets4ListConfigParser **********************

Subnets4ListConfigParser::Subnets4ListConfigParser(bool check_iface)
    : check_iface_(check_iface) {
}

size_t
Subnets4ListConfigParser::parse(SrvConfigPtr cfg,
                                ConstElementPtr subnets_list,
                                bool encapsulate_options) {
    size_t cnt = 0;
    for (auto const& subnet_json : subnets_list->listValue()) {

        auto const& parser = createSubnetConfigParser();
        Subnet4Ptr subnet = parser->parse(subnet_json, encapsulate_options);
        if (subnet) {

            // Adding a subnet to the Configuration Manager may fail if the
            // subnet id is invalid (duplicate). Thus, we catch exceptions
            // here to append a position in the configuration string.
            try {
                cfg->getCfgSubnets4()->add(subnet);
                cnt++;
            } catch (const std::exception& ex) {
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << subnet_json->getPosition() << ")");
            }
        }
    }
    return (cnt);
}

size_t
Subnets4ListConfigParser::parse(Subnet4Collection& subnets,
                                data::ConstElementPtr subnets_list,
                                bool encapsulate_options) {
    size_t cnt = 0;
    for (auto const& subnet_json : subnets_list->listValue()) {

        auto const& parser = createSubnetConfigParser();
        Subnet4Ptr subnet = parser->parse(subnet_json, encapsulate_options);
        if (subnet) {
            try {
                auto ret = subnets.insert(subnet);
                if (!ret.second) {
                    isc_throw(Unexpected,
                              "can't store subnet because of conflict");
                }
                ++cnt;
            } catch (const std::exception& ex) {
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << subnet_json->getPosition() << ")");
            }
        }
    }
    return (cnt);
}

boost::shared_ptr<Subnet4ConfigParser>
Subnets4ListConfigParser::createSubnetConfigParser() const {
    return (boost::make_shared<Subnet4ConfigParser>(check_iface_));
}

//**************************** Pool6Parser *********************************

PoolPtr
Pool6Parser::poolMaker(IOAddress &addr, uint32_t len, int32_t ptype)
{
    return (PoolPtr(new Pool6(static_cast<isc::dhcp::Lease::Type>
                              (ptype), addr, len)));
}

PoolPtr
Pool6Parser::poolMaker(IOAddress &min, IOAddress &max, int32_t ptype)
{
    return (PoolPtr(new Pool6(static_cast<isc::dhcp::Lease::Type>
                              (ptype), min, max)));
}


//**************************** Pool6ListParser ***************************

void
Pools6ListParser::parse(PoolStoragePtr pools, ConstElementPtr pools_list,
                        bool encapsulate_options) {
    for (auto const& pool : pools_list->listValue()) {
        auto const& parser = createPoolConfigParser();
        parser->parse(pools, pool, AF_INET6, encapsulate_options);
    }
}

boost::shared_ptr<PoolParser>
Pools6ListParser::createPoolConfigParser() const {
    return (boost::make_shared<Pool6Parser>());
}

//**************************** PdPoolParser ******************************

PdPoolParser::PdPoolParser() {
}

void
PdPoolParser::parse(PoolStoragePtr pools, ConstElementPtr pd_pool,
                    bool encapsulate_options) {
    checkKeywords(SimpleParser6::PD_POOL6_PARAMETERS, pd_pool);

    std::string addr_str = getString(pd_pool, "prefix");

    uint8_t prefix_len = getUint8(pd_pool, "prefix-len");

    uint8_t delegated_len = getUint8(pd_pool, "delegated-len");

    std::string excluded_prefix_str = "::";
    if (pd_pool->contains("excluded-prefix")) {
        excluded_prefix_str = getString(pd_pool, "excluded-prefix");
    }

    uint8_t excluded_prefix_len = 0;
    if (pd_pool->contains("excluded-prefix-len")) {
        excluded_prefix_len = getUint8(pd_pool, "excluded-prefix-len");
    }

    ConstElementPtr user_context = pd_pool->get("user-context");
    if (user_context) {
        user_context_ = user_context;
    }

    ConstElementPtr client_class = pd_pool->get("client-class");
    if (client_class) {
        client_class_ = client_class;
    }

    // Check the pool parameters. It will throw an exception if any
    // of the required parameters are invalid.
    try {
        // Attempt to construct the local pool.
        pool_.reset(new Pool6(IOAddress(addr_str),
                              prefix_len,
                              delegated_len,
                              IOAddress(excluded_prefix_str),
                              excluded_prefix_len));
    } catch (const std::exception& ex) {
        // Some parameters don't exist or are invalid. Since we are not
        // aware whether they don't exist or are invalid, let's append
        // the position of the pool map element.
        isc_throw(isc::dhcp::DhcpConfigError, ex.what()
                  << " (" << pd_pool->getPosition() << ")");
    }

    // If there is a pool-id, store it.
    ConstElementPtr pool_id = pd_pool->get("pool-id");
    if (pool_id) {
        if (pool_id->intValue() <= 0) {
            isc_throw(BadValue, "pool-id " << pool_id->intValue() << " is not"
                      << " a positive integer greater than 0");
        } else if (pool_id->intValue() > numeric_limits<uint32_t>::max()) {
            isc_throw(BadValue, "pool-id " << pool_id->intValue() << " is not"
                      << " a 32 bit unsigned integer");
        }

        pool_->setID(pool_id->intValue());
    }

    // We create subnet first and then parse the options straight into the subnet's
    // CfgOption structure. Previously, we first parsed the options and then copied
    // them into the CfgOption after creating the subnet but it had two issues. First,
    // it cost performance. Second, copying options reset the isEncapsulated() flag.
    // If the options have been encapsulated we want to preserve the flag to ensure
    // they are not encapsulated several times.
    ConstElementPtr option_data = pd_pool->get("option-data");
    if (option_data) {
        auto opts_parser = createOptionDataListParser();
        opts_parser->parse(pool_->getCfgOption(), option_data, encapsulate_options);
    }

    if (user_context_) {
        pool_->setContext(user_context_);
    }

    if (client_class_) {
        string cclass = client_class_->stringValue();
        if (!cclass.empty()) {
            pool_->allowClientClass(cclass);
        }
    }

    // Setup client class list.
    BaseNetworkParser::getClientClassesElem(pd_pool,
                                            std::bind(&Pool::allowClientClass,
                                                      boost::dynamic_pointer_cast<Pool>(pool_), ph::_1));

    // Setup additional class list.
    BaseNetworkParser::getAdditionalClassesElem(pd_pool,
                                                std::bind(&Pool::addAdditionalClass,
                                                          boost::dynamic_pointer_cast<Pool>(pool_), ph::_1));

    // Add the local pool to the external storage ptr.
    pools->push_back(pool_);
}

boost::shared_ptr<OptionDataListParser>
PdPoolParser::createOptionDataListParser() const {
    return (boost::make_shared<OptionDataListParser>(AF_INET6));
}

//**************************** PdPoolsListParser ************************

void
PdPoolsListParser::parse(PoolStoragePtr pools, ConstElementPtr pd_pool_list) {
    // Loop through the list of pd pools.
    for (auto const& pd_pool : pd_pool_list->listValue()) {
        auto const& parser = createPdPoolConfigParser();
        parser->parse(pools, pd_pool);
    }
}

boost::shared_ptr<PdPoolParser>
PdPoolsListParser::createPdPoolConfigParser() const {
    return (boost::make_shared<PdPoolParser>());
}

//**************************** Subnet6ConfigParser ***********************

Subnet6ConfigParser::Subnet6ConfigParser(bool check_iface)
    : SubnetConfigParser(AF_INET6, check_iface) {
}

Subnet6Ptr
Subnet6ConfigParser::parse(ConstElementPtr subnet, bool encapsulate_options) {
    // Check parameters.
    checkKeywords(SimpleParser6::SUBNET6_PARAMETERS, subnet);

    /// Parse all pools first.
    ConstElementPtr pools = subnet->get("pools");
    if (pools) {
        auto const& parser = createPoolsListParser();
        parser->parse(pools_, pools, encapsulate_options);
    }
    ConstElementPtr pd_pools = subnet->get("pd-pools");
    if (pd_pools) {
        auto const& parser = createPdPoolsListParser();
        parser->parse(pools_, pd_pools);
    }

    SubnetPtr generic = SubnetConfigParser::parse(subnet, encapsulate_options);

    if (!generic) {
        // Sanity check: not supposed to fail.
        isc_throw(DhcpConfigError,
                  "Failed to create an IPv6 subnet (" <<
                  subnet->getPosition() << ")");
    }

    Subnet6Ptr sn6ptr = boost::dynamic_pointer_cast<Subnet6>(subnet_);
    if (!sn6ptr) {
        // If we hit this, it is a programming error.
        isc_throw(Unexpected,
                  "Invalid Subnet6 cast in Subnet6ConfigParser::parse");
    }

    // Set relay information if it was provided
    if (relay_info_) {
        sn6ptr->setRelayInfo(*relay_info_);
    }

    // Parse Host Reservations for this subnet if any.
    ConstElementPtr reservations = subnet->get("reservations");
    if (reservations) {
        HostCollection hosts;
        HostReservationsListParser<HostReservationParser6> parser;
        parser.parse(subnet_->getID(), reservations, hosts);
        for (auto const& h : hosts) {
            validateResvs(sn6ptr, h);
            CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(h);
        }
    }

    // Parse allocator specification.
    auto network = boost::dynamic_pointer_cast<Network>(sn6ptr);
    parseAllocatorParams(subnet, network);

    // Parse pd-allocator specification.
    auto network6 = boost::dynamic_pointer_cast<Network6>(sn6ptr);
    parsePdAllocatorParams(subnet, network6);

    // Instantiate the allocators.
    sn6ptr->createAllocators();

    return (sn6ptr);
}

// Unused?
void
Subnet6ConfigParser::duplicateOptionWarning(uint32_t code,
                                            asiolink::IOAddress& addr) {
    LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_OPTION_DUPLICATE)
        .arg(code).arg(addr.toText());
}

void
Subnet6ConfigParser::initSubnet(data::ConstElementPtr params,
                                asiolink::IOAddress addr, uint8_t len) {
    // Subnet ID is required and must be in 1..SUBNET_ID_MAX.
    int64_t subnet_id_max = static_cast<int64_t>(SUBNET_ID_MAX);
    SubnetID subnet_id = static_cast<SubnetID>(getInteger(params, "id", 1,
                                                          subnet_id_max));

    // We want to log whether rapid-commit is enabled, so we get this
    // before the actual subnet creation.
    Optional<bool> rapid_commit;
    if (params->contains("rapid-commit")) {
        rapid_commit = getBoolean(params, "rapid-commit");
    }

    // Parse preferred lifetime as it is not parsed by the common function.
    Triplet<uint32_t> pref = parseIntTriplet(params, "preferred-lifetime");

    // Create a new subnet.
    auto subnet6 = Subnet6::create(addr, len, Triplet<uint32_t>(),
                                   Triplet<uint32_t>(),
                                   pref,
                                   Triplet<uint32_t>(),
                                   subnet_id);
    subnet_ = subnet6;

    ElementPtr mutable_params;
    mutable_params = boost::const_pointer_cast<Element>(params);

    // Parse parameters common to all Network derivations.
    NetworkPtr network = boost::dynamic_pointer_cast<Network>(subnet_);
    parseCommon(mutable_params, network);

    // Enable or disable Rapid Commit option support for the subnet.
    if (!rapid_commit.unspecified()) {
        subnet6->setRapidCommit(rapid_commit);
    }

    std::ostringstream output;
    output << addr << "/" << static_cast<int>(len) << " with params: ";
    // t1 and t2 are optional may be not specified.

    bool has_renew = !subnet6->getT1().unspecified();
    bool has_rebind = !subnet6->getT2().unspecified();
    int64_t renew = -1;
    int64_t rebind = -1;

    if (has_renew) {
        renew = subnet6->getT1().get();
        output << "t1=" << renew << ", ";
    }
    if (has_rebind) {
        rebind = subnet6->getT2().get();
        output << "t2=" << rebind << ", ";
    }

    if (!subnet6->getPreferred().unspecified()) {
        output << "preferred-lifetime=" << subnet6->getPreferred().get() << ", ";
    }
    if (!subnet6->getValid().unspecified()) {
        output << "valid-lifetime=" << subnet6->getValid().get();
    }
    if (!subnet6->getRapidCommit().unspecified()) {
        output << ", rapid-commit is "
               << boolalpha << subnet6->getRapidCommit().get();
    }

    LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_NEW_SUBNET6).arg(output.str());

    // Get interface-id option content. For now we support string
    // representation only
    Optional<std::string> ifaceid;
    if (params->contains("interface-id")) {
        ifaceid = getString(params, "interface-id");
    }

    Optional<std::string> iface;
    if (params->contains("interface")) {
        iface = getString(params, "interface");
    }

    // Specifying both interface for locally reachable subnets and
    // interface id for relays is mutually exclusive. Need to test for
    // this condition.
    if (!ifaceid.unspecified() && !iface.unspecified() && !ifaceid.empty() &&
        !iface.empty()) {
        isc_throw(isc::dhcp::DhcpConfigError,
                  "parser error: interface (defined for locally reachable "
                  "subnets) and interface-id (defined for subnets reachable"
                  " via relays) cannot be defined at the same time for "
                  "subnet " << addr << "/" << (int)len << "("
                  << params->getPosition() << ")");
    }

    // Configure interface-id for remote interfaces, if defined
    if (!ifaceid.unspecified() && !ifaceid.empty()) {
        std::string ifaceid_value = ifaceid.get();
        OptionBuffer tmp(ifaceid_value.begin(), ifaceid_value.end());
        OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
        subnet6->setInterfaceId(opt);
    }

    // Get interface name. If it is defined, then the subnet is available
    // directly over specified network interface.
    if (!iface.unspecified() && !iface.empty()) {
        if (check_iface_ && !IfaceMgr::instance().getIface(iface)) {
            ConstElementPtr error = params->get("interface");
            isc_throw(DhcpConfigError, "Specified network interface name " << iface
                      << " for subnet " << subnet6->toText()
                      << " is not present in the system ("
                      << error->getPosition() << ")");
        }

        subnet6->setIface(iface);
    }

    // Try setting up client class.
    if (params->contains("client-class")) {
        string client_class = getString(params, "client-class");
        if (!client_class.empty()) {
            subnet6->allowClientClass(client_class);
        }
    }

    // Setup client class list.
    getClientClassesElem(params, std::bind(&Network::allowClientClass,
                                           boost::dynamic_pointer_cast<Network>(subnet6), ph::_1));

    // Setup additional class list.
    getAdditionalClassesElem(params, std::bind(&Network::addAdditionalClass,
                                               boost::dynamic_pointer_cast<Network>(subnet6), ph::_1));

    /// client-class processing is now generic and handled in the common
    /// code (see isc::data::SubnetConfigParser::createSubnet)

    // Parse t1-percent and t2-percent
    parseTeePercents(params, network);

    // Parse DDNS parameters
    parseDdnsParams(params, network);

    // Parse lease cache parameters
    parseCacheParams(params, network);
}

void
Subnet6ConfigParser::validateResvs(const Subnet6Ptr& subnet, ConstHostPtr host) {
    const IPv6ResrvRange& range = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    BOOST_FOREACH(auto const& it, range) {
        const IOAddress& address = it.second.getPrefix();
        if (!subnet->inRange(address)) {
            isc_throw(DhcpConfigError, "specified reservation '" << address
                      << "' is not within the IPv6 subnet '"
                      << subnet->toText() << "'");
        }
    }
}

boost::shared_ptr<PoolsListParser>
Subnet6ConfigParser::createPoolsListParser() const {
    return (boost::make_shared<Pools6ListParser>());
}

boost::shared_ptr<PdPoolsListParser>
Subnet6ConfigParser::createPdPoolsListParser() const {
    return (boost::make_shared<PdPoolsListParser>());
}

//**************************** Subnet6ListConfigParser ********************

Subnets6ListConfigParser::Subnets6ListConfigParser(bool check_iface)
    : check_iface_(check_iface) {
}

size_t
Subnets6ListConfigParser::parse(SrvConfigPtr cfg,
                                ConstElementPtr subnets_list,
                                bool encapsulate_options) {
    size_t cnt = 0;
    for (auto const& subnet_json : subnets_list->listValue()) {

        auto const& parser = createSubnetConfigParser();
        Subnet6Ptr subnet = parser->parse(subnet_json, encapsulate_options);

        // Adding a subnet to the Configuration Manager may fail if the
        // subnet id is invalid (duplicate). Thus, we catch exceptions
        // here to append a position in the configuration string.
        try {
            cfg->getCfgSubnets6()->add(subnet);
            cnt++;
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << subnet_json->getPosition() << ")");
        }
    }
    return (cnt);
}

size_t
Subnets6ListConfigParser::parse(Subnet6Collection& subnets,
                                ConstElementPtr subnets_list,
                                bool encapsulate_options) {
    size_t cnt = 0;
    for (auto const& subnet_json : subnets_list->listValue()) {

        auto const& parser = createSubnetConfigParser();
        Subnet6Ptr subnet = parser->parse(subnet_json, encapsulate_options);
        if (subnet) {
            try {
                auto ret = subnets.insert(subnet);
                if (!ret.second) {
                    isc_throw(Unexpected,
                              "can't store subnet because of conflict");
                }
                ++cnt;
            } catch (const std::exception& ex) {
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << subnet_json->getPosition() << ")");
            }
        }
    }
    return (cnt);
}

boost::shared_ptr<Subnet6ConfigParser>
Subnets6ListConfigParser::createSubnetConfigParser() const {
    return (boost::make_shared<Subnet6ConfigParser>(check_iface_));
}

//**************************** D2ClientConfigParser **********************

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

    IOAddress server_ip = getAddress(client_config, "server-ip");

    uint32_t server_port = getUint32(client_config, "server-port");

    std::string sender_ip_str = getString(client_config, "sender-ip");

    uint32_t sender_port = getUint32(client_config, "sender-port");

    uint32_t max_queue_size = getUint32(client_config, "max-queue-size");

    dhcp_ddns::NameChangeProtocol ncr_protocol =
        getProtocol(client_config, "ncr-protocol");

    dhcp_ddns::NameChangeFormat ncr_format =
        getFormat(client_config, "ncr-format");

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
                  << " while sender-ip: " << sender_ip.toText()
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
                                            ncr_format));
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << client_config->getPosition() << ")");
    }

    // Add user context
    ConstElementPtr user_context = client_config->get("user-context");
    if (user_context) {
        new_config->setContext(user_context);
    }

    return (new_config);
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
    { "ncr-format", Element::string, "JSON" }
};

size_t
D2ClientConfigParser::setAllDefaults(isc::data::ConstElementPtr d2_config) {
    ElementPtr mutable_d2 = boost::const_pointer_cast<Element>(d2_config);
    return (SimpleParser::setDefaults(mutable_d2, D2_CLIENT_CONFIG_DEFAULTS));
}

void
CompatibilityParser::parse(ConstElementPtr compatibility, SrvConfig& srv_cfg) {
    if (compatibility) {
        auto family = CfgMgr::instance().getFamily();
        for (auto const& kv : compatibility->mapValue()) {
            if (!kv.second || (kv.second->getType() != Element::boolean)) {
                isc_throw(DhcpConfigError,
                          "compatibility parameter values must be "
                          << "boolean (" << kv.first << " at "
                          << kv.second->getPosition() << ")");
            }
            if (kv.first == "lenient-option-parsing") {
                srv_cfg.setLenientOptionParsing(kv.second->boolValue());
            } else if (family == AF_INET) {
                if (kv.first == "ignore-dhcp-server-identifier") {
                    srv_cfg.setIgnoreServerIdentifier(kv.second->boolValue());
                } else if (kv.first == "ignore-rai-link-selection") {
                    srv_cfg.setIgnoreRAILinkSelection(kv.second->boolValue());
                } else if (kv.first == "exclude-first-last-24") {
                    srv_cfg.setExcludeFirstLast24(kv.second->boolValue());
                } else {
                    isc_throw(DhcpConfigError,
                              "unsupported compatibility parameter: "
                              << kv.first << " (" << kv.second->getPosition()
                              << ")");
                }
            } else {
                isc_throw(DhcpConfigError,
                          "unsupported compatibility parameter: "
                          << kv.first << " (" << kv.second->getPosition()
                          << ")");
            }
        }
    }
}

} // namespace dhcp
} // namespace isc
