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

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <config/ccsession.h>
#include <dhcp/libdhcp++.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfg_option.h>
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

/// @brief Parser for IPv6 pool definitions.
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
    /// @param ptype is the type of IPv6 pool (Pool::PoolType). Note this is
    /// passed in as an int32_t and cast to PoolType to accommodate a
    /// polymorphic interface.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (IOAddress &addr, uint32_t len, int32_t ptype)
    {
        return (PoolPtr(new Pool6(static_cast<isc::dhcp::Lease::Type>
                                  (ptype), addr, len)));
    }

    /// @brief Creates a Pool6 object given starting and ending IPv6 addresses.
    ///
    /// @param min is the first IPv6 address in the pool.
    /// @param max is the last IPv6 address in the pool.
    /// @param ptype is the type of IPv6 pool (Pool::PoolType). Note this is
    /// passed in as an int32_t and cast to PoolType to accommodate a
    /// polymorphic interface.
    /// @return returns a PoolPtr to the new Pool4 object.
    PoolPtr poolMaker (IOAddress &min, IOAddress &max, int32_t ptype)
    {
        return (PoolPtr(new Pool6(static_cast<isc::dhcp::Lease::Type>
                                  (ptype), min, max)));
    }
};

class Pools6ListParser : public PoolsListParser {
public:
    Pools6ListParser(const std::string& dummy, PoolStoragePtr pools)
        :PoolsListParser(dummy, pools) {
    }

protected:
    virtual ParserPtr poolParserMaker(PoolStoragePtr storage) {
        return (ParserPtr(new Pool6Parser("pool", storage)));
    }
};

/// @brief Parser for IPv6 prefix delegation definitions.
///
/// This class handles prefix delegation pool definitions for IPv6 subnets
/// Pool6 objects are created and stored in the given PoolStorage container.
///
/// PdPool defintions currently support three elements: prefix, prefix-len,
/// and delegated-len, as shown in the example JSON text below:
///
/// @code
///
/// {
///     "prefix": "2001:db8:1::",
///     "prefix-len": 64,
///     "delegated-len": 128
/// }
/// @endcode
///
class PdPoolParser : public DhcpConfigParser {
public:

    /// @brief Constructor.
    ///
    /// @param param_name name of the parameter. Note, it is passed through
    /// but unused, parameter is currently always "Dhcp6/subnet6[X]/pool"
    /// @param pools storage container in which to store the parsed pool
    /// upon "commit"
    PdPoolParser(const std::string&,  PoolStoragePtr pools)
        : uint32_values_(new Uint32Storage()),
          string_values_(new StringStorage()), pools_(pools) {
        if (!pools_) {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "PdPoolParser context storage may not be NULL");
        }
    }

    /// @brief Builds a prefix delegation pool from the given configuration
    ///
    /// This function parses configuration entries and creates an instance
    /// of a dhcp::Pool6 configured for prefix delegation.
    ///
    /// @param pd_pool_ pointer to an element that holds configuration entries
    /// that define a prefix delegation pool.
    ///
    /// @throw DhcpConfigError if configuration parsing fails.
    virtual void build(ConstElementPtr pd_pool_) {
        // Parse the elements that make up the option definition.
        BOOST_FOREACH(ConfigPair param, pd_pool_->mapValue()) {
            std::string entry(param.first);
            ParserPtr parser;
            if (entry == "prefix") {
                StringParserPtr str_parser(new StringParser(entry,
                                                            string_values_));
                parser = str_parser;
            } else if (entry == "prefix-len" || entry == "delegated-len") {
                Uint32ParserPtr code_parser(new Uint32Parser(entry,
                                                             uint32_values_));
                parser = code_parser;
            } else {
                isc_throw(DhcpConfigError, "unsupported parameter: " << entry
                          << " (" << param.second->getPosition() << ")");
            }

            parser->build(param.second);
            parser->commit();
        }

        // Try to obtain the pool parameters. It will throw an exception if any
        // of the required parameters are not present or invalid.
        std::string addr_str;
        uint32_t prefix_len;
        uint32_t delegated_len;
        try {
            addr_str = string_values_->getParam("prefix");
            prefix_len = uint32_values_->getParam("prefix-len");
            delegated_len = uint32_values_->getParam("delegated-len");

            // Attempt to construct the local pool.
            pool_.reset(new Pool6(Lease::TYPE_PD, IOAddress(addr_str),
                                  prefix_len, delegated_len));
        } catch (const std::exception& ex) {
            // Some parameters don't exist or are invalid. Since we are not
            // aware whether they don't exist or are invalid, let's append
            // the position of the pool map element.
            isc_throw(isc::dhcp::DhcpConfigError, ex.what()
                      << " (" << pd_pool_->getPosition() << ")");
        }
    }

    // @brief Commits the constructed local pool to the pool storage.
    virtual void commit() {
        // Add the local pool to the external storage ptr.
        pools_->push_back(pool_);
    }

protected:
    /// Storage for subnet-specific integer values.
    Uint32StoragePtr uint32_values_;

    /// Storage for subnet-specific string values.
    StringStoragePtr string_values_;

    /// Parsers are stored here.
    ParserCollection parsers_;

    /// Pointer to the created pool object.
    isc::dhcp::Pool6Ptr pool_;

    /// Pointer to storage to which the local pool is written upon commit.
    isc::dhcp::PoolStoragePtr pools_;
};

/// @brief Parser for a list of prefix delegation pools.
///
/// This parser iterates over a list of prefix delegation pool entries and
/// creates pool instances for each one. If the parsing is successful, the
/// collection of pools is committed to the provided storage.
class PdPoolListParser : public DhcpConfigParser {
public:
    /// @brief Constructor.
    ///
    /// @param dummy first argument is ignored, all Parser constructors
    /// accept string as first argument.
    /// @param storage is the pool storage in which to store the parsed
    /// pools in this list
    /// @throw isc::dhcp::DhcpConfigError if storage is null.
    PdPoolListParser(const std::string&, PoolStoragePtr pools)
        : local_pools_(new PoolStorage()), pools_(pools) {
        if (!pools_) {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "PdPoolListParser pools storage may not be NULL");
        }
    }

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries and creates instances
    /// of prefix delegation pools .
    ///
    /// @param pd_pool_list pointer to an element that holds entries
    /// that define a prefix delegation pool.
    ///
    /// @throw DhcpConfigError if configuration parsing fails.
    void build(isc::data::ConstElementPtr pd_pool_list) {
        // Make sure the local list is empty.
        local_pools_.reset(new PoolStorage());

        // Make sure we have a configuration elements to parse.
        if (!pd_pool_list) {
            isc_throw(DhcpConfigError,
                      "PdPoolListParser: list of pool definitions is NULL");
        }

        // Loop through the list of pd pools.
        BOOST_FOREACH(ConstElementPtr pd_pool, pd_pool_list->listValue()) {
            boost::shared_ptr<PdPoolParser>
                // Create the PdPool parser.
                parser(new PdPoolParser("pd-pool", local_pools_));
                // Build the pool instance
                parser->build(pd_pool);
                // Commit the pool to the local list of pools.
                parser->commit();
        }
    }

    /// @brief  Commits the pools created to the external storage area.
    ///
    /// Note that this method adds the local list of pools to the storage area
    /// rather than replacing its contents.  This permits other parsers to
    /// contribute to the set of pools.
    void commit() {
        // local_pools_ holds the values produced by the build function.
        // At this point parsing should have completed successfully so
        // we can append new data to the supplied storage.
        pools_->insert(pools_->end(), local_pools_->begin(),
                       local_pools_->end());
    }

private:
    /// @brief storage for local pools
    PoolStoragePtr local_pools_;

    /// @brief External storage where pools are stored upon list commit.
    PoolStoragePtr pools_;
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
        :SubnetConfigParser("", globalContext(), IOAddress("::")) {
    }

    /// @brief Parses a single IPv4 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    void build(ConstElementPtr subnet) {
        SubnetConfigParser::build(subnet);

        if (subnet_) {
            Subnet6Ptr sub6ptr = boost::dynamic_pointer_cast<Subnet6>(subnet_);
            if (!sub6ptr) {
                // If we hit this, it is a programming error.
                isc_throw(Unexpected,
                          "Invalid cast in Subnet6ConfigParser::commit");
            }

            // Set relay infomation if it was provided
            if (relay_info_) {
                sub6ptr->setRelayInfo(*relay_info_);
            }

            // Adding a subnet to the Configuration Manager may fail if the
            // subnet id is invalid (duplicate). Thus, we catch exceptions
            // here to append a position in the configuration string.
            try {
                CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(sub6ptr);
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
            (config_id.compare("rebind-timer") == 0) ||
            (config_id.compare("id") == 0)) {
            parser = new Uint32Parser(config_id, uint32_values_);
        } else if ((config_id.compare("subnet") == 0) ||
                   (config_id.compare("interface") == 0) ||
                   (config_id.compare("client-class") == 0) ||
                   (config_id.compare("interface-id") == 0)) {
            parser = new StringParser(config_id, string_values_);
        } else if (config_id.compare("pools") == 0) {
            parser = new Pools6ListParser(config_id, pools_);
        } else if (config_id.compare("relay") == 0) {
            parser = new RelayInfoParser(config_id, relay_info_, Option::V6);
        } else if (config_id.compare("pd-pools") == 0) {
            parser = new PdPoolListParser(config_id, pools_);
        } else if (config_id.compare("option-data") == 0) {
            parser = new OptionDataListParser(config_id, options_, AF_INET6);
        } else {
            isc_throw(NotImplemented, "unsupported parameter: " << config_id);
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
        // Subnet ID is optional. If it is not supplied the value of 0 is used,
        // which means autogenerate.
        SubnetID subnet_id =
            static_cast<SubnetID>(uint32_values_->getOptionalParam("id", 0));

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
                      "subnet " << addr << "/" << (int)len);
            }
        }

        stringstream tmp;
        tmp << addr << "/" << static_cast<int>(len)
            << " with params t1=" << t1 << ", t2=" << t2 << ", pref="
            << pref << ", valid=" << valid;

        LOG_INFO(dhcp6_logger, DHCP6_CONFIG_NEW_SUBNET).arg(tmp.str());

        // Create a new subnet.
        Subnet6* subnet6 = new Subnet6(addr, len, t1, t2, pref, valid,
                                       subnet_id);

        // Configure interface-id for remote interfaces, if defined
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet6->setInterfaceId(opt);
        }

        // Try setting up client class (if specified)
        try {
            string client_class = string_values_->getParam("client-class");
            subnet6->allowClientClass(client_class);
        } catch (const DhcpConfigError&) {
            // That's ok if it fails. client-class is optional.
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
    DhcpConfigParser* createGlobal6DhcpConfigParser(const std::string& config_id,
                                                    ConstElementPtr element) {
    DhcpConfigParser* parser = NULL;
    if ((config_id.compare("preferred-lifetime") == 0)  ||
        (config_id.compare("valid-lifetime") == 0)  ||
        (config_id.compare("renew-timer") == 0)  ||
        (config_id.compare("rebind-timer") == 0))  {
        parser = new Uint32Parser(config_id,
                                 globalContext()->uint32_values_);
    } else if (config_id.compare("interfaces") == 0) {
        parser = new InterfaceListConfigParser(config_id, globalContext());
    } else if (config_id.compare("subnet6") == 0) {
        parser = new Subnets6ListConfigParser(config_id);
    } else if (config_id.compare("option-data") == 0) {
        parser = new OptionDataListParser(config_id, CfgOptionPtr(), AF_INET6);
    } else if (config_id.compare("option-def") == 0) {
        parser  = new OptionDefListParser(config_id, globalContext());
    } else if (config_id.compare("version") == 0) {
        parser  = new StringParser(config_id,
                                   globalContext()->string_values_);
    } else if (config_id.compare("lease-database") == 0) {
        parser = new DbAccessParser(config_id, *globalContext());
    } else if (config_id.compare("hooks-libraries") == 0) {
        parser = new HooksLibrariesParser(config_id);
    } else if (config_id.compare("dhcp-ddns") == 0) {
        parser = new D2ClientConfigParser(config_id);
    } else {
        isc_throw(DhcpConfigError,
                "unsupported global configuration parameter: "
                  << config_id << " (" << element->getPosition() << ")");
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

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND,
              DHCP6_CONFIG_START).arg(config_set->str());

    // Before starting any subnet operations, let's reset the subnet-id counter,
    // so newly recreated configuration starts with first subnet-id equal 1.
    Subnet::resetSubnetID();

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
            ParserPtr parser(createGlobal6DhcpConfigParser(config_pair.first,
                                                           config_pair.second));
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
            config_pair.first = "option-data";
            option_parser->build(option_config->second);
            option_parser->commit();
        }

        // The subnet parser is the last one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator subnet_config =
            values_map.find("subnet6");
        if (subnet_config != values_map.end()) {
            config_pair.first = "subnet6";
            subnet_parser->build(subnet_config->second);
        }

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());
        // An error occured, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_EXCEPTION).arg(config_pair.first);
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

            // This occurs last as if it succeeds, there is no easy way to
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            if (hooks_parser) {
                hooks_parser->commit();
            }
        }
        catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(2, ex.what());
            // An error occured, so make sure to restore the original data.
            rollback = true;
        } catch (...) {
            // for things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(2, "undefined configuration"
                                               " parsing error");
            // An error occured, so make sure to restore the original data.
            rollback = true;
        }
    }

    // Rollback changes as the configuration parsing failed.
    if (rollback) {
        globalContext().reset(new ParserContext(original_context));
        return (answer);
    }

    LOG_INFO(dhcp6_logger, DHCP6_CONFIG_COMPLETE)
        .arg(CfgMgr::instance().getCurrentCfg()->
             getConfigSummary(SrvConfig::CFGSEL_ALL6));

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(0, "Configuration successful.");
    return (answer);
}

ParserContextPtr& globalContext() {
    static ParserContextPtr global_context_ptr(new ParserContext(Option::V6));
    return (global_context_ptr);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
