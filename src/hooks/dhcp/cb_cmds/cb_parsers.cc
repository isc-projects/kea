// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>

#include <cstdint>
#include <iomanip>
#include <utility>

#include <boost/make_shared.hpp>

#include <cb_cmds/cb_parsers.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;

namespace isc {
namespace cb {

string
GlobalParameterNameParser::parse(ConstElementPtr global_parameter) {
    if (global_parameter->getType() != Element::string) {
        isc_throw(BadValue, "parameter name must be a string");
    }

    auto name = global_parameter->stringValue();

    if (name.empty()) {
        isc_throw(BadValue, "'name' parameter must not be empty");
    }
    if (!keywords_.count(name)) {
        isc_throw(BadValue, "unknown parameter '" << name << "'");
    }

    return (name);
}

StampedValueCollection
GlobalParameterParser::parse(const data::ConstElementPtr& global_parameter_data) {
    StampedValueCollection parsed_globals;

    for (auto const& name_value_pair : global_parameter_data->mapValue()) {
        auto name = name_value_pair.first;
        if (name.empty()) {
            isc_throw(BadValue, "name of the global parameter must not be empty");
        }
        auto kit = keywords_.find(name);
        if (kit == keywords_.end()) {
            isc_throw(BadValue, "unknown parameter '" << name << "'");
        }

        auto parameter_value = name_value_pair.second;
        if (parameter_value->getType() != kit->second) {
            isc_throw(BadValue, "bad parameter '" << name << "' value type: "
                      << "expected " << Element::typeToName(kit->second) << ", got "
                      << Element::typeToName(parameter_value->getType()));
        }
        if (parameter_value->getType() == Element::map) {
            for (auto const& sub_name_value_pair : parameter_value->mapValue()) {
                auto sub_name = sub_name_value_pair.first;
                if (sub_name.empty()) {
                    isc_throw(BadValue, "name of the global parameter must not be empty");
                }
                std::string full_name = name + "." + sub_name;
                auto kitf = keywords_.find(full_name);
                if (kitf == keywords_.end()) {
                    isc_throw(BadValue, "unknown parameter '" << name << "." << sub_name << "'");
                }

                auto sub_parameter_value = sub_name_value_pair.second;
                if (sub_parameter_value->getType() != kitf->second) {
                    isc_throw(BadValue, "bad parameter '" << name << "." << sub_name << "' value type: "
                              << "expected " << Element::typeToName(kitf->second) << ", got "
                              << Element::typeToName(sub_parameter_value->getType()));
                }
                StampedValuePtr stamped_value(new StampedValue(full_name,
                                                               copy(sub_parameter_value, 0)));
                parsed_globals.insert(stamped_value);
            }
        } else if (parameter_value->getType() == Element::list) {
            for (size_t i = 0; i < parameter_value->size(); ++i) {
                auto const sub_type = parameter_value->get(i)->getType();
                auto sub_kit = list_keywords_.find(name);
                if (sub_kit == list_keywords_.end()) {
                    isc_throw(BadValue, "unknown list parameter subtype '" << name << "'");
                }
                if (sub_type != sub_kit->second) {
                    isc_throw(BadValue, "bad list parameter '" << name << "' value type: "
                              << "expected " << Element::typeToName(sub_kit->second) << ", got "
                              << Element::typeToName(sub_type));
                }
            }
            StampedValuePtr stamped_value(new StampedValue(name, parameter_value->str()));
            parsed_globals.insert(stamped_value);
        } else {
            StampedValuePtr stamped_value(new StampedValue(name,
                                                           copy(parameter_value, 0)));
            parsed_globals.insert(stamped_value);
        }
    }

    return (parsed_globals);
}

OptionDefinitionPtr
CBOptionDefParser::parse(ConstElementPtr option_def) {
    // Get mutable version of option definition element.
    ElementPtr mutable_option_def =
        boost::const_pointer_cast<Element>(option_def);

    // Apply defaults.
    SimpleParser::setDefaults(mutable_option_def,
                              (address_family_ == AF_INET ?
                               SimpleParser4::OPTION4_DEF_DEFAULTS :
                               SimpleParser6::OPTION6_DEF_DEFAULTS));

    // Call the option definition parser.
    OptionDefParser parser(address_family_);
    OptionDefinitionPtr def = parser.parse(option_def);

    // Check that the option definition does not conflict with
    // a standard option definition.
    if (LibDHCP::getOptionDef(def->getOptionSpaceName(), def->getCode())) {
        isc_throw(BadValue, "an option with code " << def->getCode()
                  << " already exists in space '"
                  << def->getOptionSpaceName() << "'");
    } else if (LibDHCP::getOptionDef(def->getOptionSpaceName(),
                                     def->getName())) {
        isc_throw(BadValue, "an option with name '" << def->getName()
                  << "' already exists in space '"
                  << def->getOptionSpaceName() << "'");
    }

    return (def);
}

SimpleRequiredKeywords
CBOptionPairParser::OPTION_REQUIRED = { "code" };

SimpleKeywords
CBOptionPairParser::OPTION_KEYWORDS = {
    { "code",  Element::integer },
    { "space", Element::string }
};

pair<uint16_t, string>
CBOptionPairParser::parse(ConstElementPtr option, bool skip_keywords /* = false */) {
    checkRequired(OPTION_REQUIRED, option);
    if (!skip_keywords) {
        checkKeywords(OPTION_KEYWORDS, option);
    }
    string space = address_family_ == AF_INET ?
        DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE;
    ConstElementPtr elem = option->get("space");
    if (elem) {
        if (!OptionSpace::validateName(elem->stringValue())) {
            isc_throw(BadValue, "'space' parameter must be a valid space name");
        }
        space = elem->stringValue();
    }

    int64_t code = getInteger(option, "code");
    int64_t max_code;
    if (address_family_ == AF_INET) {
        max_code = numeric_limits<uint8_t>::max();
    } else {
        max_code = numeric_limits<uint16_t>::max();
    }
    if ((code < 0) || (code > max_code)) {
        isc_throw(OutOfRange, "invalid 'code' value not in [0.."
                  << max_code << "]");
    }

    if (space == DHCP4_OPTION_SPACE) {
        if (code == DHO_PAD) {
            isc_throw(OutOfRange, "invalid 'code' value 0: reserved for PAD");
        } else if (code == DHO_END) {
            isc_throw(OutOfRange, "invalid 'code' value 255: reserved for END");
        }
    } else if (space == DHCP6_OPTION_SPACE) {
        if (code == 0) {
            isc_throw(OutOfRange, "invalid 'code' value 0: reserved");
        }
    }

    return (make_pair(static_cast<uint16_t>(code), space));
}

CBOptionDefDelete
CBOptionDefDeleteParser::parse(ConstElementPtr option_def) {
    static SimpleKeywords keywords = {
        { "code",  Element::integer },
        { "space", Element::string },
        { "force", Element::boolean }
    };

    checkKeywords(keywords, option_def);

    ConstElementPtr elem = option_def->get("force");
    bool force = false;
    if (elem) {
        try {
            force = elem->boolValue();
        } catch (const Exception& ex) {
            isc_throw(BadValue, "Invalid 'force' must be a boolean value: " << elem);
        }
    }

    auto opt_pair = CBOptionPairParser::parse(option_def, true);
    return (make_tuple(opt_pair.first, opt_pair.second, force));
}

CBOptionTuple
CBOptionTupleParser::parse(ConstElementPtr option) {
    static SimpleKeywords keywords = {
        { "code",  Element::integer },
        { "space", Element::string },
        { "client-classes", Element::list }
    };

    checkKeywords(keywords, option);

    ConstElementPtr elem = option->get("client-classes");
    ClientClassesPtr cclasses;
    if (elem) {
        cclasses.reset(new ClientClasses());
        cclasses->fromElement(elem);
    }

    auto opt_pair = CBOptionPairParser::parse(option, true);
    return (make_tuple(opt_pair.first, opt_pair.second, cclasses));
}

CBOptionDataParser::CBOptionDataParser(const uint16_t address_family,
                                       CfgOptionDefPtr cfg_option_def,
                                       BackendSelector& backend_selector,
                                       ServerSelector& server_selector)
    : OptionDataParser(address_family, cfg_option_def),
      backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

OptionDefinitionPtr
CBOptionDataParser::findOptionDefinition(const std::string& option_space,
                                         const Optional<uint32_t>& option_code,
                                         const Optional<std::string>& option_name) const {
    OptionDefinitionPtr def;
    if (option_code.unspecified() && option_name.unspecified()) {
        return (def);
    }

    // Class specific option definitions take precedence.
    if (cfg_option_def_) {
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
        // Check if the option has been defined in the config backend.
        OptionDefContainerPtr cb_defs;
        if (address_family_ == AF_INET) {
            cb_defs = boost::make_shared<OptionDefContainer>
                (ConfigBackendDHCPv4Mgr::instance().getPool()->getAllOptionDefs4(backend_selector_,
                                                                                 server_selector_));
        } else {
            cb_defs = boost::make_shared<OptionDefContainer>
                (ConfigBackendDHCPv6Mgr::instance().getPool()->getAllOptionDefs6(backend_selector_,
                                                                                 server_selector_));
        }

        if (!cb_defs->empty()) {
            if (option_code.unspecified()) {
                const OptionDefContainerNameIndex& idx = cb_defs->get<2>();
                const OptionDefContainerNameRange& range = idx.equal_range(option_name);
                if (std::distance(range.first, range.second) > 0) {
                    def = *range.first;
                }
            } else {
                const OptionDefContainerTypeIndex& idx = cb_defs->get<1>();
                const OptionDefContainerTypeRange& range = idx.equal_range(option_code);
                if (std::distance(range.first, range.second) > 0) {
                    def = *range.first;
                }
            }
        }
    }

    // The definition was not found in the config backend. It can be present in our
    // configuration file. For example, this server can be used to manage the
    // configurations for multiple instances and have option definitions defined
    // in the configuration file.
    if (!def) {
        if (option_code.unspecified()) {
            def = LibDHCP::getRuntimeOptionDef(option_space, option_name);
        } else {
            def = LibDHCP::getRuntimeOptionDef(option_space, option_code);
        }
    }

    if (!def) {
        if (option_code.unspecified()) {
            def = LibDHCP::getLastResortOptionDef(option_space, option_name);
        } else {
            def = LibDHCP::getLastResortOptionDef(option_space, option_code);
        }
    }

    return (def);
}

CBOptionDataListParser::CBOptionDataListParser(const uint16_t address_family,
                                               CfgOptionDefPtr cfg_option_def,
                                               BackendSelector& backend_selector,
                                               ServerSelector& server_selector)
    : OptionDataListParser(address_family, cfg_option_def),
      backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

boost::shared_ptr<OptionDataParser>
CBOptionDataListParser::createOptionDataParser() const {
    auto parser = boost::make_shared<CBOptionDataParser>(address_family_, cfg_option_def_,
                                                         backend_selector_, server_selector_);
    return (parser);
}

SimpleRequiredKeywords
CBPoolRangeParser::POOL_REQUIRED = { "pool" };

SimpleKeywords
CBPoolRangeParser::POOL_KEYWORDS = {
    { "pool", Element::string }
};

std::pair<IOAddress, IOAddress>
CBPoolRangeParser::parse(ConstElementPtr pool) {
    checkRequired(POOL_REQUIRED, pool);
    checkKeywords(POOL_KEYWORDS, pool);
    PoolStoragePtr pools(new PoolStorage());
    if (address_family_ == AF_INET) {
        Pool4Parser parser;
        parser.parse(pools, pool, address_family_);
    } else {
        Pool6Parser parser;
        parser.parse(pools, pool, address_family_);
    }
    if (pools->size() != 1) {
        isc_throw(Unexpected, "parser does not return one pool");
    }
    return (make_pair(pools->at(0)->getFirstAddress(),
                      pools->at(0)->getLastAddress()));
}

CBPdPoolParser::CBPdPoolParser(BackendSelector& backend_selector,
                               ServerSelector& server_selector)
    : PdPoolParser(), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

boost::shared_ptr<OptionDataListParser>
CBPdPoolParser::createOptionDataListParser() const {
    auto parser = boost::make_shared<CBOptionDataListParser>(AF_INET6,
                                                             CfgOptionDefPtr(),
                                                             backend_selector_,
                                                             server_selector_);
    return (parser);
}

CBPdPoolsListParser::CBPdPoolsListParser(BackendSelector& backend_selector,
                                         ServerSelector& server_selector)
    : PdPoolsListParser(), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

boost::shared_ptr<PdPoolParser>
CBPdPoolsListParser::createPdPoolConfigParser() const {
    auto parser = boost::make_shared<CBPdPoolParser>(backend_selector_,
                                                     server_selector_);
    return (parser);
}

SimpleRequiredKeywords
CBPdPoolPrefixParser::PD_POOL_REQUIRED = { "prefix", "prefix-len" };

SimpleKeywords
CBPdPoolPrefixParser::PD_POOL_KEYWORDS = {
    { "prefix",     Element::string },
    { "prefix-len", Element::integer }
};

std::pair<IOAddress, uint8_t>
CBPdPoolPrefixParser::parse(ConstElementPtr pd_pool) {
    checkRequired(PD_POOL_REQUIRED, pd_pool);
    checkKeywords(PD_POOL_KEYWORDS, pd_pool);

    string addr_str = getString(pd_pool, "prefix");
    int64_t len = getInteger(pd_pool, "prefix-len");

    if ((len <= 0) || (len > 128)) {
        isc_throw(OutOfRange,
                  "'prefix-len' value must be in range of [1..128]");
    }
    IOAddress addr = IOAddress::IPV6_ZERO_ADDRESS();
    try {
        addr = IOAddress(addr_str);
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "invalid 'prefix': " << ex.what());
    }
    if (!addr.isV6()) {
        isc_throw(BadValue, "'prefix' value is not a valid IPv6 prefix");
    }
    if (len != 128) {
        IOAddress first_address = firstAddrInPrefix(addr, len);
        if (first_address != addr) {
            isc_throw(BadValue, "Invalid Pool6 address boundaries: " << addr
                      << " is not the first address in prefix: " << first_address
                      << "/" << static_cast<uint32_t>(len));
        }
    }
    return (std::make_pair(addr, static_cast<uint8_t>(len)));
}

SimpleRequiredKeywords
CBSubnetIdParser::SUBNET_ID_REQUIRED = { "id" };

SimpleKeywords
CBSubnetIdParser::SUBNET_ID_KEYWORDS = {
    { "id", Element::integer }
};

SubnetID
CBSubnetIdParser::parse(ConstElementPtr subnet) {
    checkRequired(SUBNET_ID_REQUIRED, subnet);
    checkKeywords(SUBNET_ID_KEYWORDS, subnet);
    int64_t id = getInteger(subnet, "id");
    if ((id <= 0) || (id > static_cast<int64_t>(SUBNET_ID_MAX))) {
        isc_throw(OutOfRange, "'id' parameter must be in [1.."
                  << SUBNET_ID_MAX << "] range");
    }
    return (static_cast<SubnetID>(id));
}

SimpleRequiredKeywords
CBSubnetPrefixParser::SUBNET_PREFIX_REQUIRED = { "subnet" };

SimpleKeywords
CBSubnetPrefixParser::SUBNET_PREFIX_KEYWORDS = {
    { "subnet", Element::string }
};

string
CBSubnetPrefixParser::parse(ConstElementPtr subnet) {
    checkRequired(SUBNET_PREFIX_REQUIRED, subnet);
    checkKeywords(SUBNET_PREFIX_KEYWORDS, subnet);
    string prefix = getString(subnet, "subnet");
    if (prefix.empty()) {
        isc_throw(BadValue, "'subnet' parameter must not be empty");
    }
    if (address_family_ == AF_INET) {
        static_cast<void>(Subnet4::parsePrefix(prefix));
    } else {
        static_cast<void>(Subnet6::parsePrefix(prefix));
    }

    // Check against spurious id (0 can be added as default).
    ConstElementPtr id = subnet->get("id");
    if (id && (id->intValue() != 0)) {
        isc_throw(BadValue, "spurious 'id' parameter");
    }
    return (prefix);
}

CBSubnet4ConfigParser::CBSubnet4ConfigParser(BackendSelector& backend_selector,
                                             ServerSelector& server_selector)
    : Subnet4ConfigParser(false), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

Subnet4Ptr
CBSubnet4ConfigParser::parse(data::ConstElementPtr subnet) {

    // Subnet identifier is mandatory.
    data::ConstElementPtr id = subnet->get("id");
    if (!id) {
        isc_throw(BadValue, "subnet 'id' is mandatory for the remote-subnet4-set command");
    }
    if (id->getType() != Element::integer) {
        isc_throw(BadValue, "'id' is not an integer");
    }
    int64_t idv = id->intValue();
    int64_t idmax = SUBNET_ID_MAX;
    if ((idv <= 0) || (idv > idmax)) {
        isc_throw(OutOfRange, "'id' parameter must be in [1.."
                  << idmax << "] range");
    }

    ConstElementPtr hosts = subnet->get("reservations");
    if (hosts) {
        // Reject not a list.
        if (hosts->getType() != Element::list) {
            isc_throw(BadValue, "'reservations' entry is not a list");
        }
        // Reject not empty.
        if (!hosts->empty()) {
            isc_throw(BadValue, "'reservations' entry is not empty. This "
                      "is not supported by the remote-subnet4-set command");
        }
    }

    // Call the parent class method on a copy without the shared network name.
    ElementPtr copy = data::copy(subnet);
    if (copy->contains("shared-network-name")) {
        copy->remove("shared-network-name");
    }
    auto result = Subnet4ConfigParser::parse(copy, false);

    // Check if the subnet should be associated with a shared network.
    auto shared_network_name_element = subnet->get("shared-network-name");
    if (shared_network_name_element) {
        std::string shared_network_name;

        // Shared network name must be a string or null.
        if (shared_network_name_element->getType() == Element::string) {
            shared_network_name = shared_network_name_element->stringValue();

        } else if ((shared_network_name_element->getType() != Element::null)) {
            isc_throw(BadValue, "'shared-network-name' must be a string or null");
        }

        // Associate the subnet with shared network or disassociate if the
        // shared network name is empty or null.
        result->setSharedNetworkName(shared_network_name);

    } else {
        isc_throw(BadValue, "'shared-network-name' is mandatory (but can"
                  " be null or empty)");
    }

    return (result);
}

boost::shared_ptr<OptionDataListParser>
CBSubnet4ConfigParser::createOptionDataListParser() const {
    auto parser = boost::make_shared<CBOptionDataListParser>(AF_INET,
                                                             CfgOptionDefPtr(),
                                                             backend_selector_,
                                                             server_selector_);
    return (parser);
}

boost::shared_ptr<dhcp::PoolsListParser>
CBSubnet4ConfigParser::createPoolsListParser() const {
    auto parser = boost::make_shared<CBPools4ListParser>(backend_selector_,
                                                         server_selector_);
    return (parser);
}

CBSubnet6ConfigParser::CBSubnet6ConfigParser(BackendSelector& backend_selector,
                                             ServerSelector& server_selector)
    : Subnet6ConfigParser(false), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

Subnet6Ptr
CBSubnet6ConfigParser::parse(data::ConstElementPtr subnet) {

    // Subnet identifier is mandatory.
    ConstElementPtr id = subnet->get("id");
    if (!id) {
        isc_throw(BadValue, "subnet 'id' is mandatory for the remote-subnet6-set command");
    }
    if (id->getType() != Element::integer) {
        isc_throw(BadValue, "'id' is not an integer");
    }
    int64_t idv = id->intValue();
    int64_t idmax = dhcp::SUBNET_ID_MAX;
    if ((idv <= 0) || (idv > idmax)) {
        isc_throw(OutOfRange, "'id' parameter must be in [1.."
                  << idmax << "] range");
    }

    ConstElementPtr hosts = subnet->get("reservations");
    if (hosts) {
        // Reject not a list.
        if (hosts->getType() != Element::list) {
            isc_throw(BadValue, "'reservations' entry is not a list");
        }
        // Reject not empty.
        if (!hosts->empty()) {
            isc_throw(BadValue, "'reservations' entry is not empty. This "
                      "is not supported by the remote-subnet6-set command");
        }
    }

    // Call the parent class method on a copy without the shared network name.
    ElementPtr copy = data::copy(subnet);
    if (copy->contains("shared-network-name")) {
        copy->remove("shared-network-name");
    }
    auto result = Subnet6ConfigParser::parse(copy, false);

    // Check if the subnet should be associated with a shared network.
    auto shared_network_name_element = subnet->get("shared-network-name");
    if (shared_network_name_element) {
        std::string shared_network_name;

        // Shared network name must be a string or null.
        if (shared_network_name_element->getType() == Element::string) {
            shared_network_name = shared_network_name_element->stringValue();

        } else if ((shared_network_name_element->getType() != Element::null)) {
            isc_throw(BadValue, "'shared-network-name' must be a string or null");
        }

        // Associate the subnet with shared network or disassociate if the
        // shared network name is empty or null.
        result->setSharedNetworkName(shared_network_name);

    } else {
        isc_throw(BadValue, "'shared-network-name' is mandatory (but can"
                  " be null or empty)");
    }

    return (result);
}

boost::shared_ptr<OptionDataListParser>
CBSubnet6ConfigParser::createOptionDataListParser() const {
    auto parser = boost::make_shared<CBOptionDataListParser>(AF_INET6,
                                                             CfgOptionDefPtr(),
                                                             backend_selector_,
                                                             server_selector_);
    return (parser);
}

boost::shared_ptr<PoolsListParser>
CBSubnet6ConfigParser::createPoolsListParser() const {
    auto parser = boost::make_shared<CBPools6ListParser>(backend_selector_,
                                                         server_selector_);
    return (parser);
}

boost::shared_ptr<PdPoolsListParser>
CBSubnet6ConfigParser::createPdPoolsListParser() const {
    auto parser = boost::make_shared<CBPdPoolsListParser>(backend_selector_,
                                                          server_selector_);
    return (parser);
}

CBSubnets4ListConfigParser::CBSubnets4ListConfigParser(BackendSelector& backend_selector,
                                                       ServerSelector& server_selector)
    : Subnets4ListConfigParser(false), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

boost::shared_ptr<Subnet4ConfigParser>
CBSubnets4ListConfigParser::createSubnetConfigParser() const {
    auto parser = boost::make_shared<CBSubnet4ConfigParser>(backend_selector_, server_selector_);
    return (parser);
}

CBSubnets6ListConfigParser::CBSubnets6ListConfigParser(BackendSelector& backend_selector,
                                                       ServerSelector& server_selector)
    : Subnets6ListConfigParser(false), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

boost::shared_ptr<Subnet6ConfigParser>
CBSubnets6ListConfigParser::createSubnetConfigParser() const {
    auto parser = boost::make_shared<CBSubnet6ConfigParser>(backend_selector_, server_selector_);
    return (parser);
}

SimpleRequiredKeywords
CBSharedNetworkNameParser::SHARED_NETWORK_REQUIRED = { "name" };

SimpleKeywords
CBSharedNetworkNameParser::SHARED_NETWORK_KEYWORDS = {
    { "name", Element::string }
};

string
CBSharedNetworkNameParser::parse(ConstElementPtr shared_network) {
    checkRequired(SHARED_NETWORK_REQUIRED, shared_network);
    checkKeywords(SHARED_NETWORK_KEYWORDS, shared_network);
    string name = getString(shared_network, "name");
    if (name.empty()) {
        isc_throw(BadValue, "'name' parameter must not be empty");
    }
    return (name);
}

CBSharedNetwork4Parser::CBSharedNetwork4Parser(BackendSelector& backend_selector,
                                               ServerSelector& server_selector)
    : SharedNetwork4Parser(false), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

SharedNetwork4Ptr
CBSharedNetwork4Parser::parse(ConstElementPtr shared_network) {
    // Subnets must not be updated via remote-network4-set command.
    // Throw an error if the subnet4 list is included.
    ConstElementPtr subnets = shared_network->get("subnet4");
    if (subnets) {
        isc_throw(BadValue,
                  "'subnet4' must not be specified for the shared network. "
                  "Use 'remote-subnet4-set command to add a subnet to the "
                  "shared network");
    }

    // Call the parent class method.
    SharedNetwork4Ptr net = SharedNetwork4Parser::parse(shared_network, false);

    if (!net) {
        // Should not happen because on errors it throws...
        isc_throw(Unexpected, "SharedNetwork4Parser::parse returns null?!");
    }

    // Last, let's check name of the shared network.
    if (net->getName().empty()) {
        isc_throw(BadValue, "'name' parameter must not be empty");
    }

    return (net);
}

boost::shared_ptr<OptionDataListParser>
CBSharedNetwork4Parser::createOptionDataListParser() const {
    auto parser = boost::make_shared<CBOptionDataListParser>(AF_INET,
                                                             CfgOptionDefPtr(),
                                                             backend_selector_,
                                                             server_selector_);
    return (parser);
}

boost::shared_ptr<Subnets4ListConfigParser>
CBSharedNetwork4Parser::createSubnetsListParser() const {
    auto parser = boost::make_shared<CBSubnets4ListConfigParser>(backend_selector_,
                                                                 server_selector_);
    return (parser);
}

CBSharedNetwork6Parser::CBSharedNetwork6Parser(BackendSelector& backend_selector,
                                               ServerSelector& server_selector)
    : SharedNetwork6Parser(false), backend_selector_(backend_selector),
      server_selector_(server_selector) {
}

SharedNetwork6Ptr
CBSharedNetwork6Parser::parse(ConstElementPtr shared_network) {
    // Subnets must not be updated via remote-network6-set command.
    // Throw an error if the subnet6 list is included.
    ConstElementPtr subnets = shared_network->get("subnet6");
    if (subnets) {
        isc_throw(BadValue,
                  "'subnet6' must not be specified for the shared network. "
                  "Use 'remote-subnet6-set command to add a subnet to the "
                  "shared network");
    }

    // Call the parent class method.
    SharedNetwork6Ptr net = SharedNetwork6Parser::parse(shared_network, false);

    if (!net) {
        // Should not happen because on errors it throws...
        isc_throw(Unexpected, "SharedNetwork6Parser::parse returns null?!");
    }

    // Last, let's check name of the shared network.
    if (net->getName().empty()) {
        isc_throw(BadValue, "'name' parameter must not be empty");
    }

    return (net);
}

boost::shared_ptr<OptionDataListParser>
CBSharedNetwork6Parser::createOptionDataListParser() const {
    auto parser = boost::make_shared<CBOptionDataListParser>(AF_INET6,
                                                             CfgOptionDefPtr(),
                                                             backend_selector_,
                                                             server_selector_);
    return (parser);
}

boost::shared_ptr<Subnets6ListConfigParser>
CBSharedNetwork6Parser::createSubnetsListParser() const {
    auto parser = boost::make_shared<CBSubnets6ListConfigParser>(backend_selector_,
                                                                 server_selector_);
    return (parser);
}

CBClientClassDefParser::CBClientClassDefParser(BackendSelector& backend_selector,
                                               ServerSelector& server_selector)
    : backend_selector_(backend_selector), server_selector_(server_selector) {
}

boost::shared_ptr<OptionDataListParser>
CBClientClassDefParser::createOptionDataListParser(const uint16_t address_family,
                                                   CfgOptionDefPtr cfg_option_def) const {
    auto parser = boost::make_shared<CBOptionDataListParser>(address_family,
                                                             cfg_option_def,
                                                             backend_selector_,
                                                             server_selector_);
    return (parser);
}

CBClientClassParser::CBClientClassParser(uint16_t family,
                                         CfgOptionDefPtr cfg_option_def,
                                         BackendSelector& backend_selector,
                                         ServerSelector& server_selector)
        : family_(family), cfg_option_def_(cfg_option_def), backend_selector_(backend_selector),
          server_selector_(server_selector) {
}

std::pair<ClientClassDefPtr, std::string>
CBClientClassParser::parse(ConstElementPtr client_class) {
    ClientClassDictionaryPtr class_dict = boost::make_shared<ClientClassDictionary>();
    CBClientClassDefParser parser(backend_selector_, server_selector_);
    // Parse with skipping dependency checks. Such checks should be conducted
    // at the database level.
    parser.parse(class_dict, client_class, family_, true, false);

    if (client_class->get("template-test")) {
        isc_throw(BadValue, "template classes are not supported");
    }

    std::string follow_class_name = "";
    if (client_class->contains("follow-class-name")) {
        // This parameter may be null if the caller is not interested in placing
        // an inserted client class into any specific position or the updated
        // class's position should not change.
        if (client_class->get("follow-class-name")->getType() != Element::null) {
            // Otherwise, it should be string.
            follow_class_name = getString(client_class, "follow-class-name");
        }
    }
    ClientClassDefPtr parsed_client_class;
    if (!class_dict->getClasses()->empty()) {
        parsed_client_class = *(class_dict->getClasses()->begin());
    }
    return (std::make_pair(parsed_client_class, follow_class_name));
}

SimpleRequiredKeywords
CBClientClassNameParser::CLIENT_CLASS_REQUIRED = { "name" };

SimpleKeywords
CBClientClassNameParser::CLIENT_CLASS_KEYWORDS = {
    { "name", Element::string }
};

string
CBClientClassNameParser::parse(ConstElementPtr client_class) {
    checkRequired(CLIENT_CLASS_REQUIRED, client_class);
    checkKeywords(CLIENT_CLASS_KEYWORDS, client_class);
    string name = getString(client_class, "name");
    if (name.empty()) {
        isc_throw(BadValue, "'name' parameter must not be empty");
    }
    return (name);
}

SimpleRequiredKeywords
ServerTagParser::SERVER_TAG_REQUIRED = { "server-tag" };

SimpleKeywords
ServerTagParser::SERVER_TAG_KEYWORDS = {
    { "server-tag", Element::string }
};

ServerTag
ServerTagParser::parse(ConstElementPtr server) {
    checkRequired(SERVER_TAG_REQUIRED, server);
    checkKeywords(SERVER_TAG_KEYWORDS, server);
    string tag = getString(server, "server-tag");
    return (ServerTag(tag));
}

SimpleRequiredKeywords
ServerConfigParser::SERVER_CONFIG_REQUIRED = { "server-tag" };

SimpleKeywords
ServerConfigParser::SERVER_CONFIG_KEYWORDS = {
    { "server-tag",  Element::string },
    { "description", Element::string }
};

db::ServerPtr
ServerConfigParser::parse(ConstElementPtr server) {
    checkRequired(SERVER_CONFIG_REQUIRED, server);
    checkKeywords(SERVER_CONFIG_KEYWORDS, server);
    string tag = getString(server, "server-tag");
    ConstElementPtr desc = server->get("description");
    if (desc) {
        return (db::Server::create(ServerTag(tag), desc->stringValue()));
    } else {
        return (db::Server::create(ServerTag(tag)));
    }
}

} // end of namespace cb
} // end of namespace isc
