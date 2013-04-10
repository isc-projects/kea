// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <config/ccsession.h>
#include <dhcp/libdhcp++.h>
#include <dhcp6/config_parser.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dbaccess_parser.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/triplet.h>
#include <log/logger_support.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>
#include <vector>

#include <stdint.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

// Pointers to various parser objects.
typedef boost::shared_ptr<BooleanParser> BooleanParserPtr;
typedef boost::shared_ptr<StringParser> StringParserPtr;
typedef boost::shared_ptr<Uint32Parser> Uint32ParserPtr;

/// @brief Collection of address pools.
///
/// This type is used as intermediate storage, when pools are parsed, but there is
/// no subnet object created yet to store them.
typedef std::vector<isc::dhcp::Pool6Ptr> PoolStorage;

/// @brief Global uint32 parameters that will be used as defaults.
Uint32Storage uint32_defaults;

/// @brief global string parameters that will be used as defaults.
StringStorage string_defaults;

/// @brief Global storage for options that will be used as defaults.
OptionStorage option_defaults;

/// @brief Global storage for option definitions.
OptionDefStorage option_def_intermediate;

/// @brief parser for pool definition
///
/// This parser handles pool definitions, i.e. a list of entries of one
/// of two syntaxes: min-max and prefix/len. Pool6 objects are created
/// and stored in chosen PoolStorage container.
///
/// As there are no default values for pool, setStorage() must be called
/// before build(). Otherwise an exception will be thrown.
///
/// It is useful for parsing Dhcp6/subnet6[X]/pool parameters.
class PoolParser : public DhcpConfigParser {
public:

    /// @brief constructor.
    PoolParser(const std::string& /*param_name*/)
        : pools_(NULL) {
        // ignore parameter name, it is always Dhcp6/subnet6[X]/pool
    }

    /// @brief constructor.
    PoolParser(const std::string& /*param_name*/,  PoolStorage* pools)
        :pools_(pools) {
        // ignore parameter name, it is always Dhcp6/subnet6[X]/pool
    }

    /// @brief parses the actual list
    ///
    /// This method parses the actual list of interfaces.
    /// No validation is done at this stage, everything is interpreted as
    /// interface name.
    /// @param pools_list list of pools defined for a subnet
    /// @throw isc::InvalidOperation if storage was not specified
    ///        (setStorage() not called)
    void build(ConstElementPtr pools_list) {

        // setStorage() should have been called before build
        if (!pools_) {
            isc_throw(isc::InvalidOperation, "parser logic error: no pool storage set,"
                      " but pool parser asked to parse pools");
        }

        BOOST_FOREACH(ConstElementPtr text_pool, pools_list->listValue()) {

            // That should be a single pool representation. It should contain
            // text in the form prefix/len or first - last. Note that spaces
            // are allowed
            string txt = text_pool->stringValue();

            // first let's remove any whitespaces
            boost::erase_all(txt, " "); // space
            boost::erase_all(txt, "\t"); // tabulation

            // Is this prefix/len notation?
            size_t pos = txt.find("/");
            if (pos != string::npos) {
                IOAddress addr("::");
                uint8_t len = 0;
                try {
                    addr = IOAddress(txt.substr(0, pos));

                    // start with the first character after /
                    string prefix_len = txt.substr(pos + 1);

                    // It is lexically cast to int and then downcast to uint8_t.
                    // Direct cast to uint8_t (which is really an unsigned char)
                    // will result in interpreting the first digit as output
                    // value and throwing exception if length is written on two
                    // digits (because there are extra characters left over).

                    // No checks for values over 128. Range correctness will
                    // be checked in Pool6 constructor.
                    len = boost::lexical_cast<int>(prefix_len);
                } catch (...)  {
                    isc_throw(DhcpConfigError, "failed to parse pool "
                              "definition: " << text_pool->stringValue());
                }

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, addr, len));
                local_pools_.push_back(pool);
                continue;
            }

            // Is this min-max notation?
            pos = txt.find("-");
            if (pos != string::npos) {
                // using min-max notation
                IOAddress min(txt.substr(0, pos));
                IOAddress max(txt.substr(pos + 1));

                Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, min, max));

                local_pools_.push_back(pool);
                continue;
            }

            isc_throw(DhcpConfigError, "failed to parse pool definition:"
                      << text_pool->stringValue() <<
                      ". Does not contain - (for min-max) nor / (prefix/len)");
        }
    }

    /// @brief sets storage for value of this parameter
    ///
    /// See @ref dhcpv6ConfigInherit for details.
    ///
    /// @param storage pointer to the storage container
    void setStorage(PoolStorage* storage) {
        pools_ = storage;
    }

    /// @brief Stores the parsed values in a storage provided
    ///        by an upper level parser.
    virtual void commit() {
        if (pools_) {
            // local_pools_ holds the values produced by the build function.
            // At this point parsing should have completed successfuly so
            // we can append new data to the supplied storage.
            pools_->insert(pools_->end(), local_pools_.begin(),
                           local_pools_.end());
        }
    }

    /// @brief factory that constructs PoolParser objects
    ///
    /// @param param_name name of the parameter to be parsed
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new PoolParser(param_name));
    }

private:
    /// @brief pointer to the actual Pools storage
    ///
    /// This is typically a storage somewhere in Subnet parser
    /// (an upper level parser).
    PoolStorage* pools_;
    /// A temporary storage for pools configuration. It is a
    /// storage where pools are stored by build function.
    PoolStorage local_pools_;
};

/// @brief this class parses a single subnet
///
/// This class parses the whole subnet definition. It creates parsers
/// for received configuration parameters as needed.
class Subnet6ConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    Subnet6ConfigParser(const std::string& ) {
        // The parameter should always be "subnet", but we don't check
        // against that here in case some wants to reuse this parser somewhere.
    }

    /// @brief parses parameter value
    ///
    /// @param subnet pointer to the content of subnet definition
    ///
    /// @throw isc::DhcpConfigError if subnet configuration parsing failed.
    void build(ConstElementPtr subnet) {

        BOOST_FOREACH(ConfigPair param, subnet->mapValue()) {
            ParserPtr parser(createSubnet6ConfigParser(param.first));
            parser->build(param.second);
            parsers_.push_back(parser);
        }

        // In order to create new subnet we need to get the data out
        // of the child parsers first. The only way to do it is to
        // invoke commit on them because it will make them write
        // parsed data into storages we have supplied.
        // Note that triggering commits on child parsers does not
        // affect global data because we supplied pointers to storages
        // local to this object. Thus, even if this method fails
        // later on, the configuration remains consistent.
        BOOST_FOREACH(ParserPtr parser, parsers_) {
            parser->commit();
        }

        // Create a subnet.
        createSubnet();
    }

    /// @brief Adds the created subnet to a server's configuration.
    void commit() {
        if (subnet_) {
            isc::dhcp::CfgMgr::instance().addSubnet6(subnet_);
        }
    }

private:

    /// @brief Append sub-options to an option.
    ///
    /// @param option_space a name of the encapsulated option space.
    /// @param option option instance to append sub-options to.
    void appendSubOptions(const std::string& option_space, OptionPtr& option) {
        // Only non-NULL options are stored in option container.
        // If this option pointer is NULL this is a serious error.
        assert(option);

        OptionDefinitionPtr def;
        if (option_space == "dhcp6" &&
            LibDHCP::isStandardOption(Option::V6, option->getType())) {
            def = LibDHCP::getOptionDef(Option::V6, option->getType());
            // Definitions for some of the standard options hasn't been
            // implemented so it is ok to leave here.
            if (!def) {
                return;
            }
        } else {
            const OptionDefContainerPtr defs =
                option_def_intermediate.getItems(option_space);
            const OptionDefContainerTypeIndex& idx = defs->get<1>();
            const OptionDefContainerTypeRange& range =
                idx.equal_range(option->getType());
            // There is no definition so we have to leave.
            if (std::distance(range.first, range.second) == 0) {
                return;
            }

            def = *range.first;

            // If the definition exists, it must be non-NULL.
            // Otherwise it is a programming error.
            assert(def);
        }

        // We need to get option definition for the particular option space
        // and code. This definition holds the information whether our
        // option encapsulates any option space.
        // Get the encapsulated option space name.
        std::string encapsulated_space = def->getEncapsulatedSpace();
        // If option space name is empty it means that our option does not
        // encapsulate any option space (does not include sub-options).
        if (!encapsulated_space.empty()) {
            // Get the sub-options that belong to the encapsulated
            // option space.
            const Subnet::OptionContainerPtr sub_opts =
                option_defaults.getItems(encapsulated_space);
            // Append sub-options to the option.
            BOOST_FOREACH(Subnet::OptionDescriptor desc, *sub_opts) {
                if (desc.option) {
                    option->addOption(desc.option);
                }
            }
        }
    }

    /// @brief Create a new subnet using a data from child parsers.
    ///
    /// @throw isc::dhcp::DhcpConfigError if subnet configuration parsing failed.
    void createSubnet() {
        std::string subnet_txt;
        try {
            subnet_txt = string_values_.getParam("subnet");
        } catch (DhcpConfigError) {
            // rethrow with precise error
            isc_throw(DhcpConfigError,
                      "Mandatory subnet definition in subnet missing");
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
            isc_throw(DhcpConfigError,
                      "Invalid subnet syntax (prefix/len expected):" << subnet_txt);
        }

        // Try to create the address object. It also validates that
        // the address syntax is ok.
        IOAddress addr(subnet_txt.substr(0, pos));
        uint8_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

        // Get all 'time' parameters using inheritance.
        // If the subnet-specific value is defined then use it, else
        // use the global value. The global value must always be
        // present. If it is not, it is an internal error and exception
        // is thrown.
        Triplet<uint32_t> t1 = getParam("renew-timer");
        Triplet<uint32_t> t2 = getParam("rebind-timer");
        Triplet<uint32_t> pref = getParam("preferred-lifetime");
        Triplet<uint32_t> valid = getParam("valid-lifetime");

        // Get interface name. If it is defined, then the subnet is available
        // directly over specified network interface.
        std::string iface;
        try {
            iface = string_values_.getParam("interface");
        } catch (DhcpConfigError) {
            // iface not mandatory so swallow the exception
        }

        /// @todo: Convert this to logger once the parser is working reliably
        stringstream tmp;
        tmp << addr.toText() << "/" << (int)len
            << " with params t1=" << t1 << ", t2=" << t2 << ", pref="
            << pref << ", valid=" << valid;

        LOG_INFO(dhcp6_logger, DHCP6_CONFIG_NEW_SUBNET).arg(tmp.str());

        // Create a new subnet.
        subnet_.reset(new Subnet6(addr, len, t1, t2, pref, valid));

        // Add pools to it.
        for (PoolStorage::iterator it = pools_.begin(); it != pools_.end(); ++it) {
            subnet_->addPool(*it);
        }

        // Configure interface, if defined
        if (!iface.empty()) {
            if (!IfaceMgr::instance().getIface(iface)) {
                isc_throw(DhcpConfigError, "Specified interface name " << iface
                          << " for subnet " << subnet_->toText() << " is not present"
                          << " in the system.");
            }

            subnet_->setIface(iface);
        }

        // We are going to move configured options to the Subnet object.
        // Configured options reside in the container where options
        // are grouped by space names. Thus we need to get all space names
        // and iterate over all options that belong to them.
        std::list<std::string> space_names = options_.getOptionSpaceNames();
        BOOST_FOREACH(std::string option_space, space_names) {
            // Get all options within a particular option space.
            BOOST_FOREACH(Subnet::OptionDescriptor desc,
                          *options_.getItems(option_space)) {
                // The pointer should be non-NULL. The validation is expected
                // to be performed by the OptionDataParser before adding an
                // option descriptor to the container.
                assert(desc.option);
                // We want to check whether an option with the particular
                // option code has been already added. If so, we want
                // to issue a warning.
                Subnet::OptionDescriptor existing_desc =
                    subnet_->getOptionDescriptor("option_space",
                                                 desc.option->getType());
                if (existing_desc.option) {
                    LOG_WARN(dhcp6_logger, DHCP6_CONFIG_OPTION_DUPLICATE)
                        .arg(desc.option->getType()).arg(addr.toText());
                }
                // Add sub-options (if any).
                appendSubOptions(option_space, desc.option);
                // In any case, we add the option to the subnet.
                subnet_->addOption(desc.option, false, option_space);
            }
        }

        // Check all global options and add them to the subnet object if
        // they have been configured in the global scope. If they have been
        // configured in the subnet scope we don't add global option because
        // the one configured in the subnet scope always takes precedence.
        space_names = option_defaults.getOptionSpaceNames();
        BOOST_FOREACH(std::string option_space, space_names) {
            // Get all global options for the particular option space.
            BOOST_FOREACH(Subnet::OptionDescriptor desc,
                          *option_defaults.getItems(option_space)) {
                // The pointer should be non-NULL. The validation is expected
                // to be performed by the OptionDataParser before adding an
                // option descriptor to the container.
                assert(desc.option);
                // Check if the particular option has been already added.
                // This would mean that it has been configured in the
                // subnet scope. Since option values configured in the
                // subnet scope take precedence over globally configured
                // values we don't add option from the global storage
                // if there is one already.
                Subnet::OptionDescriptor existing_desc =
                    subnet_->getOptionDescriptor(option_space, desc.option->getType());
                if (!existing_desc.option) {
                    // Add sub-options (if any).
                    appendSubOptions(option_space, desc.option);

                    subnet_->addOption(desc.option, false, option_space);
                }
            }
        }
    }

    /// @brief creates parsers for entries in subnet definition
    ///
    /// @param config_id name od the entry
    ///
    /// @return parser object for specified entry name
    /// @throw isc::dhcp::DhcpConfigError if trying to create a parser
    ///        for unknown config element
    DhcpConfigParser* createSubnet6ConfigParser(const std::string& config_id) {
        DhcpConfigParser *parser = NULL;
        if ((config_id.compare("preferred-lifetime") == 0)  ||
            (config_id.compare("valid-lifetime") == 0)  ||
            (config_id.compare("renew-timer") == 0)  ||
            (config_id.compare("rebind-timer") == 0))  {
            parser = new Uint32Parser(config_id, &uint32_values_);
        }
        else if ((config_id.compare("subnet") == 0) ||
                 (config_id.compare("interface") == 0)) {
            parser = new StringParser(config_id, &string_values_);
        }
        else if (config_id.compare("pool") == 0) {
            parser = new PoolParser(config_id, &pools_);
        }
        else if (config_id.compare("option-data") == 0) {
           parser = new OptionDataListParser(config_id, &options_, 
                                             &option_def_intermediate,
                                             Dhcp6OptionDataParser::factory);
        } else {
            isc_throw(NotImplemented,
                "parser error: Subnet6 parameter not supported: " << config_id);
        }

        return (parser);
    }

    /// @brief Returns value for a given parameter (after using inheritance)
    ///
    /// This method implements inheritance.  For a given parameter name, it first
    /// checks if there is a global value for it and overwrites it with specific
    /// value if such value was defined in subnet.
    ///
    /// @param name name of the parameter
    /// @return triplet with the parameter name
    /// @throw DhcpConfigError when requested parameter is not present
    isc::dhcp::Triplet<uint32_t> getParam(const std::string& name) {
        uint32_t value = 0;
        try {
            // look for local value 
            value = uint32_values_.getParam(name);
        } catch (DhcpConfigError) {
            try {
                // no local, use global value 
                value = uint32_defaults.getParam(name);
            } catch (DhcpConfigError) {
                isc_throw(DhcpConfigError, "Mandatory parameter " << name
                      << " missing (no global default and no subnet-"
                      << "specific value)");
            }
        }

        return (Triplet<uint32_t>(value));
    }

    /// storage for subnet-specific uint32 values
    Uint32Storage uint32_values_;

    /// storage for subnet-specific integer values
    StringStorage string_values_;

    /// storage for pools belonging to this subnet
    PoolStorage pools_;

    /// storage for options belonging to this subnet
    OptionStorage options_;

    /// parsers are stored here
    ParserCollection parsers_;

    /// Pointer to the created subnet object.
    isc::dhcp::Subnet6Ptr subnet_;
};

/// @brief this class parses a list of subnets
///
/// This is a wrapper parser that handles the whole list of Subnet6
/// definitions. It iterates over all entries and creates Subnet6ConfigParser
/// for each entry.
class Subnets6ListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    Subnets6ListConfigParser(const std::string&) {
        /// parameter name is ignored
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list and creates a Subnet6ConfigParser
    /// for each entry.
    ///
    /// @param subnets_list pointer to a list of IPv6 subnets
    void build(ConstElementPtr subnets_list) {

        // No need to define FactoryMap here. There's only one type
        // used: Subnet6ConfigParser

        BOOST_FOREACH(ConstElementPtr subnet, subnets_list->listValue()) {

            ParserPtr parser(new Subnet6ConfigParser("subnet"));
            parser->build(subnet);
            subnets_.push_back(parser);
        }

    }

    /// @brief commits subnets definitions.
    ///
    /// Iterates over all Subnet6 parsers. Each parser contains definitions
    /// of a single subnet and its parameters and commits each subnet separately.
    void commit() {
        // @todo: Implement more subtle reconfiguration than toss
        // the old one and replace with the new one.

        // remove old subnets
        isc::dhcp::CfgMgr::instance().deleteSubnets6();

        BOOST_FOREACH(ParserPtr subnet, subnets_) {
            subnet->commit();
        }

    }

    /// @brief Returns Subnet6ListConfigParser object
    /// @param param_name name of the parameter
    /// @return Subnets6ListConfigParser object
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new Subnets6ListConfigParser(param_name));
    }

    /// @brief collection of subnet parsers.
    ParserCollection subnets_;
};

} // anonymous namespace

namespace isc {
namespace dhcp {

//************** Dhcp6OptionDataParser methods ****************************

Dhcp6OptionDataParser::Dhcp6OptionDataParser(const std::string& param_name, 
    OptionStorage *options, OptionDefStorage *option_defs)
    :OptionDataParser(param_name, options, option_defs, Option::V6) {
}

OptionDataParser* Dhcp6OptionDataParser::factory(const std::string& param_name,
    OptionStorage *options, OptionDefStorage *option_defs) {
    return new Dhcp6OptionDataParser(param_name, options, option_defs);
}

OptionDefinitionPtr Dhcp6OptionDataParser::findServerSpaceOptionDefinition (
    std::string& option_space, uint32_t option_code) {
    OptionDefinitionPtr def;

    if (option_space == "dhcp6" &&
        LibDHCP::isStandardOption(Option::V6, option_code)) {
        def = LibDHCP::getOptionDef(Option::V6, option_code);

    } else if (option_space == "dhcp4") {
        isc_throw(DhcpConfigError, "'dhcp4' option space name is reserved"
                << " for DHCPv4 server");
    }

    return def;
}

/// @brief creates global parsers
///
/// This method creates global parsers that parse global parameters, i.e.
/// those that take format of Dhcp6/param1, Dhcp6/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv6 parameter
/// @throw NotImplemented if trying to create a parser for unknown config element
DhcpConfigParser* createGlobalDhcpConfigParser(const std::string& config_id) {
    DhcpConfigParser *parser = NULL;
    if ((config_id.compare("preferred-lifetime") == 0)  ||
        (config_id.compare("valid-lifetime") == 0)  ||
        (config_id.compare("renew-timer") == 0)  ||
        (config_id.compare("rebind-timer") == 0))  {
        parser = new Uint32Parser(config_id, &uint32_defaults);
    }
    else if (config_id.compare("interface") == 0) {
        parser = new InterfaceListConfigParser(config_id);
    }
    else if (config_id.compare("subnet6") == 0) {
        parser = new Subnets6ListConfigParser(config_id);
    }
    else if (config_id.compare("option-data") == 0) {
        parser = new OptionDataListParser(config_id, &option_defaults, 
                                          &option_def_intermediate,
                                          Dhcp6OptionDataParser::factory);
    }
    else if (config_id.compare("option-def") == 0) {
        parser  = new OptionDefListParser(config_id, &option_def_intermediate);
    }
    else if (config_id.compare("version") == 0) {
        parser  = new StringParser(config_id, &string_defaults);
    }
    else if (config_id.compare("lease-database") == 0) {
        parser = new DbAccessParser(config_id);
    }
    else {
        isc_throw(NotImplemented,
                "Parser error: Global configuration parameter not supported: "
                << config_id);
    }

    return (parser);
}

ConstElementPtr
configureDhcp6Server(Dhcpv6Srv&, ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    /// @todo: append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_START).arg(config_set->str());

    // Some of the values specified in the configuration depend on
    // other values. Typically, the values in the subnet4 structure
    // depend on the global values. Also, option values configuration
    // must be performed after the option definitions configurations.
    // Thus we group parsers and will fire them in the right order:
    // all parsers other than subnet4 and option-data parser,
    // option-data parser, subnet4 parser.
    ParserCollection independent_parsers;
    ParserPtr subnet_parser;
    ParserPtr option_parser;

    // The subnet parsers implement data inheritance by directly
    // accessing global storage. For this reason the global data
    // parsers must store the parsed data into global storages
    // immediately. This may cause data inconsistency if the
    // parsing operation fails after the global storage has been
    // modified. We need to preserve the original global data here
    // so as we can rollback changes when an error occurs.
    Uint32Storage uint32_local(uint32_defaults);
    StringStorage string_local(string_defaults);
    OptionStorage option_local(option_defaults);
    OptionDefStorage option_def_local(option_def_intermediate);

    // answer will hold the result.
    ConstElementPtr answer;
    // rollback informs whether error occured and original data
    // have to be restored to global storages.
    bool rollback = false;
    // config_pair holds ther details of the current parser when iterating over
    // the parsers.  It is declared outside the loop so in case of error, the
    // name of the failing parser can be retrieved within the "catch" clause.
    ConfigPair config_pair;
    try {

        // Make parsers grouping.
        const std::map<std::string, ConstElementPtr>& values_map =
            config_set->mapValue();
        BOOST_FOREACH(config_pair, values_map) {
            ParserPtr parser(createGlobalDhcpConfigParser(config_pair.first));
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PARSER_CREATED)
                      .arg(config_pair.first);
            if (config_pair.first == "subnet6") {
                subnet_parser = parser;

            } else if (config_pair.first == "option-data") {
                option_parser = parser;

            } else {
                // Those parsers should be started before other
                // parsers so we can call build straight away.
                independent_parsers.push_back(parser);
                parser->build(config_pair.second);
                // The commit operation here may modify the global storage
                // but we need it so as the subnet6 parser can access the
                // parsed data.
                parser->commit();
            }
        }

        // The option values parser is the next one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator option_config =
            values_map.find("option-data");
        if (option_config != values_map.end()) {
            option_parser->build(option_config->second);
            option_parser->commit();
        }

        // The subnet parser is the last one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator subnet_config =
            values_map.find("subnet6");
        if (subnet_config != values_map.end()) {
            subnet_parser->build(subnet_config->second);
        }

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(1,
                     string("Configuration parsing failed: ") + ex.what());
        // An error occured, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_EXCEPTION).arg(config_pair.first);
        answer = isc::config::createAnswer(1,
                     string("Configuration parsing failed"));
        // An error occured, so make sure that we restore original data.
        rollback = true;
    }

    // So far so good, there was no parsing error so let's commit the
    // configuration. This will add created subnets and option values into
    // the server's configuration.
    // This operation should be exception safe but let's make sure.
    if (!rollback) {
        try {
            if (subnet_parser) {
                subnet_parser->commit();
            }
        }
        catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(2,
                         string("Configuration commit failed:") + ex.what());
            // An error occured, so make sure to restore the original data.
            rollback = true;
        } catch (...) {
            // for things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(2,
                         string("Configuration commit failed"));
            // An error occured, so make sure to restore the original data.
            rollback = true;
        }
    }

    // Rollback changes as the configuration parsing failed.
    if (rollback) {
        std::swap(uint32_defaults, uint32_local);
        std::swap(string_defaults, string_local);
        std::swap(option_defaults, option_local);
        std::swap(option_def_intermediate, option_def_local);
        return (answer);
    }

    LOG_INFO(dhcp6_logger, DHCP6_CONFIG_COMPLETE).arg(config_details);

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(0, "Configuration committed.");
    return (answer);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
