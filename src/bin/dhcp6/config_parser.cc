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

/// @brief Parser for DHCP6 option data value.
///
/// This parser parses configuration entries that specify value of
/// a single option specific to DHCP6.  It provides the DHCP6-specific
/// implementation of the abstract class OptionDataParser.
class Dhcp6OptionDataParser : public OptionDataParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first param, option names are always "Dhcp6/option-data[n]"
    /// @param options is the option storage in which to store the parsed option
    /// upon "commit".
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    Dhcp6OptionDataParser(const std::string&, OptionStoragePtr options,
                         ParserContextPtr global_context)
        :OptionDataParser("", options, global_context) {
    }

    /// @brief static factory method for instantiating Dhcp4OptionDataParsers
    ///
    /// @param param_name name of the parameter to be parsed.
    /// @param options storage where the parameter value is to be stored.
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    /// @return returns a pointer to a new OptionDataParser. Caller is
    /// is responsible for deleting it when it is no longer needed.
    static OptionDataParser* factory(const std::string& param_name,
    OptionStoragePtr options, ParserContextPtr global_context) {
        return (new Dhcp6OptionDataParser(param_name, options, global_context));
    }


protected:
    /// @brief Finds an option definition within the server's option space
    ///
    /// Given an option space and an option code, find the correpsonding
    /// option defintion within the server's option defintion storage.
    ///
    /// @param option_space name of the parameter option space
    /// @param option_code numeric value of the parameter to find
    /// @return OptionDefintionPtr of the option defintion or an
    /// empty OptionDefinitionPtr if not found.
    /// @throw DhcpConfigError if the option space requested is not valid
    /// for this server.
    virtual OptionDefinitionPtr findServerSpaceOptionDefinition (
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
};

/// @brief Parser for IPv4 pool definitions.
///
/// This is the IPv6 derivation of the PoolParser class and handles pool
/// definitions, i.e. a list of entries of one of two syntaxes: min-max and
/// prefix/len for IPv6 pools. Pool6 objects are created and stored in chosen
/// PoolStorage container.
///
/// It is useful for parsing Dhcp6/subnet6[X]/pool parameters.
class Pool6Parser : public PoolParser {
public:

    /// @brief Constructor.
    ///
    /// @param param_name name of the parameter. Note, it is passed through
    /// but unused, parameter is currently always "Dhcp6/subnet6[X]/pool"
    /// @param pools storage container in which to store the parsed pool
    /// upon "commit"
    Pool6Parser(const std::string& param_name,  PoolStoragePtr pools)
        :PoolParser(param_name, pools) {
    }

protected:
    /// @brief Creates a Pool6 object given a IPv6 prefix and the prefix length.
    ///
    /// @param addr is the IPv6 prefix of the pool.
    /// @param len is the prefix length.
    /// @param ptype is the type of IPv6 pool (Pool6::Pool6Type). Note this is
    /// passed in as an int32_t and cast to Pool6Type to accommodate a
    /// polymorphic interface.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (IOAddress &addr, uint32_t len, int32_t ptype)
    {
        return (PoolPtr(new Pool6(static_cast<isc::dhcp::Pool6::Pool6Type>
                                  (ptype), addr, len)));
    }

    /// @brief Creates a Pool6 object given starting and ending IPv6 addresses.
    ///
    /// @param min is the first IPv6 address in the pool.
    /// @param max is the last IPv6 address in the pool.
    /// @param ptype is the type of IPv6 pool (Pool6::Pool6Type). Note this is
    /// passed in as an int32_t and cast to Pool6Type to accommodate a
    /// polymorphic interface.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (IOAddress &min, IOAddress &max, int32_t ptype)
    {
        return (PoolPtr(new Pool6(static_cast<isc::dhcp::Pool6::Pool6Type>
                                  (ptype), min, max)));
    }
};

/// @brief This class parses a single IPv6 subnet.
///
/// This is the IPv6 derivation of the SubnetConfigParser class and it parses
/// the whole subnet definition. It creates parsersfor received configuration
/// parameters as needed.
class Subnet6ConfigParser : public SubnetConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param ignored first parameter
    /// stores global scope parameters, options, option defintions.
    Subnet6ConfigParser(const std::string&)
        :SubnetConfigParser("", globalContext()) {
    }

    /// @brief Adds the created subnet to a server's configuration.
    /// @throw throws Unexpected if dynamic cast fails.
    void commit() {
        if (subnet_) {
            Subnet6Ptr sub6ptr = boost::dynamic_pointer_cast<Subnet6>(subnet_);
            if (!sub6ptr) {
                // If we hit this, it is a programming error.
                isc_throw(Unexpected,
                          "Invalid cast in Subnet4ConfigParser::commit");
            }
            isc::dhcp::CfgMgr::instance().addSubnet6(sub6ptr);
        }
    }

protected:

    /// @brief creates parsers for entries in subnet definition
    ///
    /// @param config_id name of the entry
    ///
    /// @return parser object for specified entry name. Note the caller is
    /// responsible for deleting the parser created.
    /// @throw isc::dhcp::DhcpConfigError if trying to create a parser
    /// for unknown config element
    DhcpConfigParser* createSubnetConfigParser(const std::string& config_id) {
        DhcpConfigParser* parser = NULL;
        if ((config_id.compare("preferred-lifetime") == 0)  ||
            (config_id.compare("valid-lifetime") == 0)  ||
            (config_id.compare("renew-timer") == 0)  ||
            (config_id.compare("rebind-timer") == 0))  {
            parser = new Uint32Parser(config_id, uint32_values_);
        } else if ((config_id.compare("subnet") == 0) ||
                   (config_id.compare("interface") == 0) ||
                   (config_id.compare("interface-id") == 0)) {
            parser = new StringParser(config_id, string_values_);
        } else if (config_id.compare("pool") == 0) {
            parser = new Pool6Parser(config_id, pools_);
        } else if (config_id.compare("option-data") == 0) {
           parser = new OptionDataListParser(config_id, options_,
                                             global_context_,
                                             Dhcp6OptionDataParser::factory);
        } else {
            isc_throw(NotImplemented,
                "parser error: Subnet6 parameter not supported: " << config_id);
        }

        return (parser);
    }


    /// @brief Determines if the given option space name and code describe
    /// a standard option for the DHCP6 server.
    ///
    /// @param option_space is the name of the option space to consider
    /// @param code is the numeric option code to consider
    /// @return returns true if the space and code are part of the server's
    /// standard options.
    bool isServerStdOption(std::string option_space, uint32_t code) {
        return ((option_space.compare("dhcp6") == 0)
                && LibDHCP::isStandardOption(Option::V6, code));
    }

    /// @brief Returns the option definition for a given option code from
    /// the DHCP6 server's standard set of options.
    /// @param code is the numeric option code of the desired option definition.
    /// @return returns a pointer the option definition
    OptionDefinitionPtr getServerStdOptionDefinition (uint32_t code) {
        return (LibDHCP::getOptionDef(Option::V6, code));
    }

    /// @brief Issues a DHCP6 server specific warning regarding duplicate subnet
    /// options.
    ///
    /// @param code is the numeric option code of the duplicate option
    /// @param addr is the subnet address
    /// @todo A means to know the correct logger and perhaps a common
    /// message would allow this message to be emitted by the base class.
    virtual void duplicate_option_warning(uint32_t code,
                                         isc::asiolink::IOAddress& addr) {
        LOG_WARN(dhcp6_logger, DHCP6_CONFIG_OPTION_DUPLICATE)
            .arg(code).arg(addr.toText());
    }

    /// @brief Instantiates the IPv6 Subnet based on a given IPv6 address
    /// and prefix length.
    ///
    /// @param addr is IPv6 prefix of the subnet.
    /// @param len is the prefix length
    void initSubnet(isc::asiolink::IOAddress addr, uint8_t len) {
        // Get all 'time' parameters using inheritance.
        // If the subnet-specific value is defined then use it, else
        // use the global value. The global value must always be
        // present. If it is not, it is an internal error and exception
        // is thrown.
        Triplet<uint32_t> t1 = getParam("renew-timer");
        Triplet<uint32_t> t2 = getParam("rebind-timer");
        Triplet<uint32_t> pref = getParam("preferred-lifetime");
        Triplet<uint32_t> valid = getParam("valid-lifetime");

        // Get interface-id option content. For now we support string
        // represenation only
        std::string ifaceid;
        try {
            ifaceid = string_values_->getParam("interface-id");
        } catch (const DhcpConfigError &) {
            // interface-id is not mandatory
        }

        // Specifying both interface for locally reachable subnets and
        // interface id for relays is mutually exclusive. Need to test for
        // this condition.
        if (!ifaceid.empty()) {
            std::string iface;
            try {
                iface = string_values_->getParam("interface");
            } catch (const DhcpConfigError &) {
                // iface not mandatory
            }

            if (!iface.empty()) {
                isc_throw(isc::dhcp::DhcpConfigError,
                      "parser error: interface (defined for locally reachable "
                      "subnets) and interface-id (defined for subnets reachable"
                      " via relays) cannot be defined at the same time for "
                      "subnet " << addr.toText() << "/" << (int)len);
            }
        }

        stringstream tmp;
        tmp << addr.toText() << "/" << static_cast<int>(len)
            << " with params t1=" << t1 << ", t2=" << t2 << ", pref="
            << pref << ", valid=" << valid;

        LOG_INFO(dhcp6_logger, DHCP6_CONFIG_NEW_SUBNET).arg(tmp.str());

        // Create a new subnet.
        Subnet6* subnet6 = new Subnet6(addr, len, t1, t2, pref, valid);

        // Configure interface-id for remote interfaces, if defined
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet6->setInterfaceId(opt);
        }

        subnet_.reset(subnet6);
    }

};


/// @brief this class parses a list of DHCP6 subnets
///
/// This is a wrapper parser that handles the whole list of Subnet6
/// definitions. It iterates over all entries and creates Subnet6ConfigParser
/// for each entry.
class Subnets6ListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    /// @param dummy first argument, always ignored. All parsers accept a
    /// string parameter "name" as their first argument.
    Subnets6ListConfigParser(const std::string&) {
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list and creates a Subnet6ConfigParser
    /// for each entry.
    ///
    /// @param subnets_list pointer to a list of IPv6 subnets
    void build(ConstElementPtr subnets_list) {
        BOOST_FOREACH(ConstElementPtr subnet, subnets_list->listValue()) {
            ParserPtr parser(new Subnet6ConfigParser("subnet"));
            parser->build(subnet);
            subnets_.push_back(parser);
        }

    }

    /// @brief commits subnets definitions.
    ///
    /// Iterates over all Subnet6 parsers. Each parser contains definitions of
    /// a single subnet and its parameters and commits each subnet separately.
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

/// @brief creates global parsers
///
/// This method creates global parsers that parse global parameters, i.e.
/// those that take format of Dhcp6/param1, Dhcp6/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv6 parameter
/// @throw NotImplemented if trying to create a parser for unknown config
/// element
DhcpConfigParser* createGlobal6DhcpConfigParser(const std::string& config_id) {
    DhcpConfigParser* parser = NULL;
    if ((config_id.compare("preferred-lifetime") == 0)  ||
        (config_id.compare("valid-lifetime") == 0)  ||
        (config_id.compare("renew-timer") == 0)  ||
        (config_id.compare("rebind-timer") == 0))  {
        parser = new Uint32Parser(config_id,
                                 globalContext()->uint32_values_);
    } else if (config_id.compare("interfaces") == 0) {
        parser = new InterfaceListConfigParser(config_id);
    } else if (config_id.compare("subnet6") == 0) {
        parser = new Subnets6ListConfigParser(config_id);
    } else if (config_id.compare("option-data") == 0) {
        parser = new OptionDataListParser(config_id,
                                          globalContext()->options_,
                                          globalContext(),
                                          Dhcp6OptionDataParser::factory);
    } else if (config_id.compare("option-def") == 0) {
        parser  = new OptionDefListParser(config_id,
                                          globalContext()->option_defs_);
    } else if (config_id.compare("version") == 0) {
        parser  = new StringParser(config_id,
                                   globalContext()->string_values_);
    } else if (config_id.compare("lease-database") == 0) {
        parser = new DbAccessParser(config_id);
    } else if (config_id.compare("hooks-libraries") == 0) {
        parser = new HooksLibrariesParser(config_id);
    } else {
        isc_throw(NotImplemented,
                "Parser error: Global configuration parameter not supported: "
                << config_id);
    }

    return (parser);
}

isc::data::ConstElementPtr
configureDhcp6Server(Dhcpv6Srv&, isc::data::ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    /// @todo: Append most essential info here (like "2 new subnets configured")
    string config_details;

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND,
              DHCP6_CONFIG_START).arg(config_set->str());

    // Some of the values specified in the configuration depend on
    // other values. Typically, the values in the subnet6 structure
    // depend on the global values. Also, option values configuration
    // must be performed after the option definitions configurations.
    // Thus we group parsers and will fire them in the right order:
    // all parsers other than subnet6 and option-data parser,
    // option-data parser, subnet6 parser.
    ParserCollection independent_parsers;
    ParserPtr subnet_parser;
    ParserPtr option_parser;
    ParserPtr iface_parser;

    // Some of the parsers alter state of the system that can't easily
    // be undone. (Or alter it in a way such that undoing the change
    // has the same risk of failure as doing the change.)
    ParserPtr hooks_parser;

    // The subnet parsers implement data inheritance by directly
    // accessing global storage. For this reason the global data
    // parsers must store the parsed data into global storages
    // immediately. This may cause data inconsistency if the
    // parsing operation fails after the global storage has been
    // modified. We need to preserve the original global data here
    // so as we can rollback changes when an error occurs.
    ParserContext original_context(*globalContext());

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
            ParserPtr parser(createGlobal6DhcpConfigParser(config_pair.first));
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PARSER_CREATED)
                      .arg(config_pair.first);
            if (config_pair.first == "subnet6") {
                subnet_parser = parser;
            } else if (config_pair.first == "option-data") {
                option_parser = parser;
            } else if (config_pair.first == "hooks-libraries") {
                // Executing the commit will alter currently loaded hooks
                // libraries. Check if the supplied libraries are valid,
                // but defer the commit until after everything else has
                // committed.
                hooks_parser = parser;
                hooks_parser->build(config_pair.second);
            } else if (config_pair.first == "interfaces") {
                // The interface parser is independent from any other parser and
                // can be run here before other parsers.
                parser->build(config_pair.second);
                iface_parser = parser;
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

            if (iface_parser) {
                iface_parser->commit();
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
        globalContext().reset(new ParserContext(original_context));
        return (answer);
    }

    // Now commit any changes that have been validated but not yet committed.
    if (hooks_parser) {
        hooks_parser->commit();
    }

    LOG_INFO(dhcp6_logger, DHCP6_CONFIG_COMPLETE).arg(config_details);

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(0, "Configuration committed.");
    return (answer);
}

ParserContextPtr& globalContext() {
    static ParserContextPtr global_context_ptr(new ParserContext(Option::V6));
    return (global_context_ptr);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
