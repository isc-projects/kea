// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config/ccsession.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp4/json_config_parser.h>
#include <dhcpsrv/dbaccess_parser.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <dhcpsrv/option_space_container.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <limits>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace {

/// @brief Parser for DHCP4 option data value.
///
/// This parser parses configuration entries that specify value of
/// a single option specific to DHCP4.  It provides the DHCP4-specific
/// implementation of the abstract class OptionDataParser.
class Dhcp4OptionDataParser : public OptionDataParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first param, option names are always "Dhcp4/option-data[n]"
    /// @param options is the option storage in which to store the parsed option
    /// upon "commit".
    /// @param global_context is a pointer to the global context which
    /// stores global scope parameters, options, option defintions.
    Dhcp4OptionDataParser(const std::string&,
        OptionStoragePtr options, ParserContextPtr global_context)
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
        return (new Dhcp4OptionDataParser(param_name, options, global_context));
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
        if (option_space == "dhcp4" &&
            LibDHCP::isStandardOption(Option::V4, option_code)) {
            def = LibDHCP::getOptionDef(Option::V4, option_code);
        } else if (option_space == "dhcp6") {
            isc_throw(DhcpConfigError, "'dhcp6' option space name is reserved"
                     << " for DHCPv6 server");
        } else {
            // Check if this is a vendor-option. If it is, get vendor-specific
            // definition.
            uint32_t vendor_id = SubnetConfigParser::optionSpaceToVendorId(option_space);
            if (vendor_id) {
                def = LibDHCP::getVendorOptionDef(Option::V4, vendor_id, option_code);
            }
        }

        return (def);
    }
};

/// @brief Parser for IPv4 pool definitions.
///
/// This is the IPv4 derivation of the PoolParser class and handles pool
/// definitions, i.e. a list of entries of one of two syntaxes: min-max and
/// prefix/len for IPv4 pools. Pool4 objects are created and stored in chosen
/// PoolStorage container.
///
/// It is useful for parsing Dhcp4/subnet4[X]/pool parameters.
class Pool4Parser : public PoolParser {
public:

    /// @brief Constructor.
    ///
    /// @param param_name name of the parameter. Note, it is passed through
    /// but unused, parameter is currently always "Dhcp4/subnet4[X]/pool"
    /// @param pools storage container in which to store the parsed pool
    /// upon "commit"
    Pool4Parser(const std::string& param_name,  PoolStoragePtr pools)
        :PoolParser(param_name, pools) {
    }

protected:
    /// @brief Creates a Pool4 object given a IPv4 prefix and the prefix length.
    ///
    /// @param addr is the IPv4 prefix of the pool.
    /// @param len is the prefix length.
    /// @param ignored dummy parameter to provide symmetry between the
    /// PoolParser derivations. The V6 derivation requires a third value.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (IOAddress &addr, uint32_t len, int32_t) {
        return (PoolPtr(new Pool4(addr, len)));
    }

    /// @brief Creates a Pool4 object given starting and ending IPv4 addresses.
    ///
    /// @param min is the first IPv4 address in the pool.
    /// @param max is the last IPv4 address in the pool.
    /// @param ignored dummy parameter to provide symmetry between the
    /// PoolParser derivations. The V6 derivation requires a third value.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (IOAddress &min, IOAddress &max, int32_t) {
        return (PoolPtr(new Pool4(min, max)));
    }
};

class Pools4ListParser : public PoolsListParser {
public:
    Pools4ListParser(const std::string& dummy, PoolStoragePtr pools)
        :PoolsListParser(dummy, pools) {
    }

protected:
    virtual ParserPtr poolParserMaker(PoolStoragePtr storage) {
        return (ParserPtr(new Pool4Parser("pool", storage)));
    }
};

/// @brief This class parses a single IPv4 subnet.
///
/// This is the IPv4 derivation of the SubnetConfigParser class and it parses
/// the whole subnet definition. It creates parsersfor received configuration
/// parameters as needed.
class Subnet4ConfigParser : public SubnetConfigParser {
public:
    /// @brief Constructor
    ///
    /// @param ignored first parameter
    /// stores global scope parameters, options, option defintions.
    Subnet4ConfigParser(const std::string&)
        :SubnetConfigParser("", globalContext(), IOAddress("0.0.0.0")) {
    }

    /// @brief Parses a single IPv4 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    void build(ConstElementPtr subnet) {
        SubnetConfigParser::build(subnet);

        if (subnet_) {
            Subnet4Ptr sub4ptr = boost::dynamic_pointer_cast<Subnet4>(subnet_);
            if (!sub4ptr) {
                // If we hit this, it is a programming error.
                isc_throw(Unexpected,
                          "Invalid cast in Subnet4ConfigParser::commit");
            }

            // Set relay information if it was parsed
            if (relay_info_) {
                sub4ptr->setRelayInfo(*relay_info_);
            }

            // Adding a subnet to the Configuration Manager may fail if the
            // subnet id is invalid (duplicate). Thus, we catch exceptions
            // here to append a position in the configuration string.
            try {
                isc::dhcp::CfgMgr::instance().addSubnet4(sub4ptr);
            } catch (const std::exception& ex) {
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << subnet->getPosition() << ")");
            }
        }
    }

    /// @brief Commits subnet configuration.
    ///
    /// This function is currently no-op because subnet should already
    /// be added into the Config Manager in the build().
    void commit() { }

protected:

    /// @brief Creates parsers for entries in subnet definition.
    ///
    /// @param config_id name of the entry
    ///
    /// @return parser object for specified entry name. Note the caller is
    /// responsible for deleting the parser created.
    /// @throw isc::dhcp::DhcpConfigError if trying to create a parser
    /// for unknown config element
    DhcpConfigParser* createSubnetConfigParser(const std::string& config_id) {
        DhcpConfigParser* parser = NULL;
        if ((config_id.compare("valid-lifetime") == 0)  ||
            (config_id.compare("renew-timer") == 0)  ||
            (config_id.compare("rebind-timer") == 0) ||
            (config_id.compare("id") == 0)) {
            parser = new Uint32Parser(config_id, uint32_values_);
        } else if ((config_id.compare("subnet") == 0) ||
                   (config_id.compare("interface") == 0) ||
                   (config_id.compare("client-class") == 0) ||
                   (config_id.compare("next-server") == 0)) {
            parser = new StringParser(config_id, string_values_);
        } else if (config_id.compare("pools") == 0) {
            parser = new Pools4ListParser(config_id, pools_);
        } else if (config_id.compare("relay") == 0) {
            parser = new RelayInfoParser(config_id, relay_info_, Option::V4);
        } else if (config_id.compare("option-data") == 0) {
           parser = new OptionDataListParser(config_id, options_,
                                             global_context_,
                                             Dhcp4OptionDataParser::factory);
        } else {
            isc_throw(NotImplemented, "unsupported parameter: " << config_id);
        }

        return (parser);
    }

    /// @brief Determines if the given option space name and code describe
    /// a standard option for the DHCP4 server.
    ///
    /// @param option_space is the name of the option space to consider
    /// @param code is the numeric option code to consider
    /// @return returns true if the space and code are part of the server's
    /// standard options.
    bool isServerStdOption(std::string option_space, uint32_t code) {
        return ((option_space.compare("dhcp4") == 0)
                && LibDHCP::isStandardOption(Option::V4, code));
    }

    /// @brief Returns the option definition for a given option code from
    /// the DHCP4 server's standard set of options.
    /// @param code is the numeric option code of the desired option definition.
    /// @return returns a pointer the option definition
    OptionDefinitionPtr getServerStdOptionDefinition (uint32_t code) {
        return (LibDHCP::getOptionDef(Option::V4, code));
    }

    /// @brief Issues a DHCP4 server specific warning regarding duplicate subnet
    /// options.
    ///
    /// @param code is the numeric option code of the duplicate option
    /// @param addr is the subnet address
    /// @todo a means to know the correct logger and perhaps a common
    /// message would allow this method to be emitted by the base class.
    virtual void duplicate_option_warning(uint32_t code,
                                         isc::asiolink::IOAddress& addr) {
        LOG_WARN(dhcp4_logger, DHCP4_CONFIG_OPTION_DUPLICATE)
            .arg(code).arg(addr.toText());
    }

    /// @brief Instantiates the IPv4 Subnet based on a given IPv4 address
    /// and prefix length.
    ///
    /// @param addr is IPv4 address of the subnet.
    /// @param len is the prefix length
    void initSubnet(isc::asiolink::IOAddress addr, uint8_t len) {
        // The renew-timer and rebind-timer are optional. If not set, the
        // option 58 and 59 will not be sent to a client. In this case the
        // client will use default values based on the valid-lifetime.
        Triplet<uint32_t> t1 = getOptionalParam("renew-timer");
        Triplet<uint32_t> t2 = getOptionalParam("rebind-timer");
        // The valid-lifetime is mandatory. It may be specified for a
        // particular subnet. If not, the global value should be present.
        // If there is no global value, exception is thrown.
        Triplet<uint32_t> valid = getParam("valid-lifetime");
        // Subnet ID is optional. If it is not supplied the value of 0 is used,
        // which means autogenerate.
        SubnetID subnet_id =
            static_cast<SubnetID>(uint32_values_->getOptionalParam("id", 0));

        stringstream s;
        s << addr << "/" << static_cast<int>(len) << " with params: ";
        // t1 and t2 are optional may be not specified.
        if (!t1.unspecified()) {
            s << "t1=" << t1 << ", ";
        }
        if (!t2.unspecified()) {
            s << "t2=" << t2 << ", ";
        }
        s <<"valid-lifetime=" << valid;

        LOG_INFO(dhcp4_logger, DHCP4_CONFIG_NEW_SUBNET).arg(s.str());

        Subnet4Ptr subnet4(new Subnet4(addr, len, t1, t2, valid, subnet_id));
        subnet_ = subnet4;

        // Try global value first
        try {
            string next_server = globalContext()->string_values_->getParam("next-server");
            if (!next_server.empty()) {
                subnet4->setSiaddr(IOAddress(next_server));
            }
        } catch (const DhcpConfigError&) {
            // Don't care. next_server is optional. We can live without it
        } catch (...) {
            isc_throw(DhcpConfigError, "invalid parameter next-server ("
                      << globalContext()->string_values_->getPosition("next-server")
                      << ")");
        }

        // Try subnet specific value if it's available
        try {
            string next_server = string_values_->getParam("next-server");
            if (!next_server.empty()) {
                subnet4->setSiaddr(IOAddress(next_server));
            }
        } catch (const DhcpConfigError&) {
            // Don't care. next_server is optional. We can live without it
        } catch (...) {
            isc_throw(DhcpConfigError, "invalid parameter next-server ("
                      << string_values_->getPosition("next-server")
                      << ")");
        }


        // Try setting up client class (if specified)
        try {
            string client_class = string_values_->getParam("client-class");
            subnet4->allowClientClass(client_class);
        } catch (const DhcpConfigError&) {
            // That's ok if it fails. client-class is optional.
        }
    }
};

/// @brief this class parses list of DHCP4 subnets
///
/// This is a wrapper parser that handles the whole list of Subnet4
/// definitions. It iterates over all entries and creates Subnet4ConfigParser
/// for each entry.
class Subnets4ListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    /// @param dummy first argument, always ignored. All parsers accept a
    /// string parameter "name" as their first argument.
    Subnets4ListConfigParser(const std::string&) {
    }

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list and creates Subnet4ConfigParser
    /// for each entry.
    ///
    /// @param subnets_list pointer to a list of IPv4 subnets
    void build(ConstElementPtr subnets_list) {
        // @todo: Implement more subtle reconfiguration than toss
        // the old one and replace with the new one.

        // remove old subnets
        CfgMgr::instance().deleteSubnets4();

        BOOST_FOREACH(ConstElementPtr subnet, subnets_list->listValue()) {
            ParserPtr parser(new Subnet4ConfigParser("subnet"));
            parser->build(subnet);
            subnets_.push_back(parser);
        }
    }

    /// @brief commits subnets definitions.
    ///
    /// Iterates over all Subnet4 parsers. Each parser contains definitions of
    /// a single subnet and its parameters and commits each subnet separately.
    void commit() {
        BOOST_FOREACH(ParserPtr subnet, subnets_) {
            subnet->commit();
        }

    }

    /// @brief Returns Subnet4ListConfigParser object
    /// @param param_name name of the parameter
    /// @return Subnets4ListConfigParser object
    static DhcpConfigParser* factory(const std::string& param_name) {
        return (new Subnets4ListConfigParser(param_name));
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
/// those that take format of Dhcp4/param1, Dhcp4/param2 and so forth.
///
/// @param config_id pointer to received global configuration entry
/// @return parser for specified global DHCPv4 parameter
/// @throw NotImplemented if trying to create a parser for unknown
/// config element
    DhcpConfigParser* createGlobalDhcp4ConfigParser(const std::string& config_id,
                                                    ConstElementPtr element) {
    DhcpConfigParser* parser = NULL;
    if ((config_id.compare("valid-lifetime") == 0)  ||
        (config_id.compare("renew-timer") == 0)  ||
        (config_id.compare("rebind-timer") == 0))  {
        parser = new Uint32Parser(config_id,
                                 globalContext()->uint32_values_);
    } else if (config_id.compare("interfaces") == 0) {
        parser = new InterfaceListConfigParser(config_id, globalContext());
    } else if (config_id.compare("subnet4") == 0) {
        parser = new Subnets4ListConfigParser(config_id);
    } else if (config_id.compare("option-data") == 0) {
        parser = new OptionDataListParser(config_id,
                                          globalContext()->options_,
                                          globalContext(),
                                          Dhcp4OptionDataParser::factory);
    } else if (config_id.compare("option-def") == 0) {
        parser  = new OptionDefListParser(config_id, globalContext());
    } else if ((config_id.compare("version") == 0) ||
               (config_id.compare("next-server") == 0)) {
        parser  = new StringParser(config_id,
                                    globalContext()->string_values_);
    } else if (config_id.compare("lease-database") == 0) {
        parser = new DbAccessParser(config_id, *globalContext());
    } else if (config_id.compare("hooks-libraries") == 0) {
        parser = new HooksLibrariesParser(config_id);
    } else if (config_id.compare("echo-client-id") == 0) {
        parser = new BooleanParser(config_id, globalContext()->boolean_values_);
    } else if (config_id.compare("dhcp-ddns") == 0) {
        parser = new D2ClientConfigParser(config_id);
    } else {
        isc_throw(DhcpConfigError,
                "unsupported global configuration parameter: "
                  << config_id << " (" << element->getPosition() << ")");
    }

    return (parser);
}

void commitGlobalOptions() {
    // Although the function is modest for now, it is certain that the number
    // of global switches will increase over time, hence the name.

    // Set whether v4 server is supposed to echo back client-id (yes = RFC6842
    // compatible, no = backward compatibility)
    try {
        bool echo_client_id = globalContext()->boolean_values_->getParam("echo-client-id");
        CfgMgr::instance().echoClientId(echo_client_id);
    } catch (...) {
        // Ignore errors. This flag is optional
    }
}

isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv&, isc::data::ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND,
              DHCP4_CONFIG_START).arg(config_set->str());

    // Before starting any subnet operations, let's reset the subnet-id counter,
    // so newly recreated configuration starts with first subnet-id equal 1.
    Subnet::resetSubnetID();

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
    ParserPtr iface_parser;

    // Some of the parsers alter the state of the system in a way that can't
    // easily be undone. (Or alter it in a way such that undoing the change has
    // the same risk of failure as doing the change.)
    ParserPtr hooks_parser;

    // The subnet parsers implement data inheritance by directly
    // accessing global storage. For this reason the global data
    // parsers must store the parsed data into global storages
    // immediately. This may cause data inconsistency if the
    // parsing operation fails after the global storage has been
    // modified. We need to preserve the original global data here
    // so as we can rollback changes when an error occurs.
    ParserContext original_context(*globalContext());

    // Answer will hold the result.
    ConstElementPtr answer;
    // Rollback informs whether error occured and original data
    // have to be restored to global storages.
    bool rollback = false;
    // config_pair holds the details of the current parser when iterating over
    // the parsers.  It is declared outside the loops so in case of an error,
    // the name of the failing parser can be retrieved in the "catch" clause.
    ConfigPair config_pair;
    try {
        // Make parsers grouping.
        const std::map<std::string, ConstElementPtr>& values_map =
                                                        config_set->mapValue();
        BOOST_FOREACH(config_pair, values_map) {
            ParserPtr parser(createGlobalDhcp4ConfigParser(config_pair.first,
                                                           config_pair.second));
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PARSER_CREATED)
                      .arg(config_pair.first);
            if (config_pair.first == "subnet4") {
                subnet_parser = parser;
            } else if (config_pair.first == "option-data") {
                option_parser = parser;
            } else if (config_pair.first == "interfaces") {
                // The interface parser is independent from any other
                // parser and can be run here before any other parsers.
                iface_parser = parser;
                parser->build(config_pair.second);
            } else if (config_pair.first == "hooks-libraries") {
                // Executing commit will alter currently-loaded hooks
                // libraries.  Check if the supplied libraries are valid,
                // but defer the commit until everything else has committed.
                hooks_parser = parser;
                parser->build(config_pair.second);
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
            config_pair.first = "option-data";
            option_parser->build(option_config->second);
            option_parser->commit();
        }

        // The subnet parser is the last one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator subnet_config =
            values_map.find("subnet4");
        if (subnet_config != values_map.end()) {
            config_pair.first = "subnet4";
            subnet_parser->build(subnet_config->second);
        }

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());

        // An error occured, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // For things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_EXCEPTION).arg(config_pair.first);
        answer = isc::config::createAnswer(1, "undefined configuration"
                                           " processing error");

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

            // No need to commit interface names as this is handled by the
            // CfgMgr::commit() function.

            // Apply global options
            commitGlobalOptions();

            // This occurs last as if it succeeds, there is no easy way
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            if (hooks_parser) {
                hooks_parser->commit();
            }
        }
        catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(2, ex.what());
            rollback = true;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(2, "undefined configuration"
                                               " parsing error");
            rollback = true;
        }
    }

    // Rollback changes as the configuration parsing failed.
    if (rollback) {
        globalContext().reset(new ParserContext(original_context));
        CfgMgr::instance().rollback();
        return (answer);
    }

    LOG_INFO(dhcp4_logger, DHCP4_CONFIG_COMPLETE)
        .arg(CfgMgr::instance().getCurrentCfg()->
             getConfigSummary(Configuration::CFGSEL_ALL4));

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(0, "Configuration successful.");
    return (answer);
}

ParserContextPtr& globalContext() {
    static ParserContextPtr global_context_ptr(new ParserContext(Option::V4));
    return (global_context_ptr);
}



}; // end of isc::dhcp namespace
}; // end of isc namespace
