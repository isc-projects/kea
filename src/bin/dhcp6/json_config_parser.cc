// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/simple_parser6.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcpsrv/triplet.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>
#include <dhcpsrv/parsers/dhcp_config_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/duid_config_parser.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <log/logger_support.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <defaults.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <limits>
#include <map>
#include <netinet/in.h>
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

/// @brief Specialization of the pool list parser for DHCPv6
class Pools6ListParser : PoolsListParser {
public:

    /// @brief parses the actual structure
    ///
    /// This method parses the actual list of pools.
    ///
    /// @param pools storage container in which to store the parsed pool.
    /// @param pools_list a list of pool structures
    /// @throw isc::dhcp::DhcpConfigError when pool parsing fails
    void parse(PoolStoragePtr pools,
               isc::data::ConstElementPtr pools_list) {
        BOOST_FOREACH(ConstElementPtr pool, pools_list->listValue()) {
            Pool6Parser parser;
            parser.parse(pools, pool, AF_INET6);
        }
    }
};

/// @brief Parser for IPv6 prefix delegation definitions.
///
/// This class handles prefix delegation pool definitions for IPv6 subnets
/// Pool6 objects are created and stored in the given PoolStorage container.
///
/// PdPool definitions currently support three elements: prefix, prefix-len,
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
class PdPoolParser : public isc::data::SimpleParser {
public:

    /// @brief Constructor.
    ///
    PdPoolParser() : options_(new CfgOption()) {
    }

    /// @brief Builds a prefix delegation pool from the given configuration
    ///
    /// This function parses configuration entries and creates an instance
    /// of a dhcp::Pool6 configured for prefix delegation.
    ///
    /// @param pools storage container in which to store the parsed pool.
    /// @param pd_pool_ pointer to an element that holds configuration entries
    /// that define a prefix delegation pool.
    ///
    /// @throw DhcpConfigError if configuration parsing fails.
  void parse(PoolStoragePtr pools,
             ConstElementPtr pd_pool_) {
        std::string addr_str;
        std::string excluded_prefix_str = "::";
        uint8_t prefix_len = 0;
        uint8_t delegated_len = 0;
        uint8_t excluded_prefix_len = 0;

        // Parse the elements that make up the option definition.
        BOOST_FOREACH(ConfigPair param, pd_pool_->mapValue()) {
            std::string entry(param.first);
            ConstElementPtr value(param.second);
            try {
                if (entry == "prefix") {
                    addr_str = value->stringValue();
                } else if (entry == "excluded-prefix") {
                    excluded_prefix_str = value->stringValue();
                } else if (entry == "prefix-len") {
                    prefix_len = getUint8(entry, value);
                } else if (entry == "delegated-len") {
                    delegated_len = getUint8(entry, value);
                } else if (entry == "excluded-prefix-len") {
                    excluded_prefix_len = getUint8(entry, value);
                } else if (entry == "option-data") {
                    OptionDataListParser opts_parser(AF_INET6);
                    opts_parser.parse(options_, value);
                } else if (entry == "user-context") {
                    user_context_ = value;
                } else {
                    isc_throw(isc::dhcp::DhcpConfigError,
                              "unsupported parameter: " << entry
                              << " (" << value->getPosition() << ")");
                }
            } catch (const isc::data::TypeError&) {
                isc_throw(isc::dhcp::DhcpConfigError,
                          "invalid value type specified for parameter '"
                          << entry << "' ("
                          << value->getPosition() << ")");
            }
        }

        // Check the pool parameters. It will throw an exception if any
        // of the required parameters are not present or invalid.
        require_("prefix", pd_pool_);
        require_("prefix-len", pd_pool_);
        require_("delegated-len", pd_pool_);
        try {
            // Attempt to construct the local pool.
            pool_.reset(new Pool6(IOAddress(addr_str),
                                  prefix_len,
                                  delegated_len,
                                  IOAddress(excluded_prefix_str),
                                  excluded_prefix_len));
            // Merge options specified for a pool into pool configuration.
            options_->copyTo(*pool_->getCfgOption());
        } catch (const std::exception& ex) {
            // Some parameters don't exist or are invalid. Since we are not
            // aware whether they don't exist or are invalid, let's append
            // the position of the pool map element.
            isc_throw(isc::dhcp::DhcpConfigError, ex.what()
                      << " (" << pd_pool_->getPosition() << ")");
        }

        if (user_context_) {
            pool_->setUserContext(user_context_);
        }

        // Add the local pool to the external storage ptr.
        pools->push_back(pool_);
    }

private:

    /// @brief Require a mandatory element
    ///
    /// @param name Entry name
    /// @param config Pools configuration
    /// @throw isc::dhcp::DhcpConfigError if not present
    void require_(const std::string& name, ConstElementPtr config) const {
        if (!config->contains(name)) {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "Missing parameter '" << name << "' ("
                      << config->getPosition() << ")");
        }
    }

    /// @brief Get an uint8_t value
    ///
    /// @param name Entry name
    /// @param value Integer element value
    /// @return uint8_t value
    /// @throw isc::data::TypeError when it is not an integer
    /// isc::dhcp::DhcpConfigError when it does not fit in an uint8_t
    uint8_t getUint8(const std::string& name, ConstElementPtr value) const {
        return (extractInt<uint8_t, DhcpConfigError>(name, value));
    }

    /// Pointer to the created pool object.
    isc::dhcp::Pool6Ptr pool_;

    /// A storage for pool specific option values.
    CfgOptionPtr options_;

    isc::data::ConstElementPtr user_context_;
};

/// @brief Parser for a list of prefix delegation pools.
///
/// This parser iterates over a list of prefix delegation pool entries and
/// creates pool instances for each one. If the parsing is successful, the
/// collection of pools is committed to the provided storage.
class PdPoolsListParser : public PoolsListParser {
public:

    /// @brief Parse configuration entries.
    ///
    /// This function parses configuration entries and creates instances
    /// of prefix delegation pools .
    ///
    /// @param storage is the pool storage in which to store the parsed
    /// @param pd_pool_list pointer to an element that holds entries
    /// that define a prefix delegation pool.
    ///
    /// @throw DhcpConfigError if configuration parsing fails.
    void parse(PoolStoragePtr pools,
               isc::data::ConstElementPtr pd_pool_list) {
        // Loop through the list of pd pools.
        BOOST_FOREACH(ConstElementPtr pd_pool, pd_pool_list->listValue()) {
            PdPoolParser parser;
            parser.parse(pools, pd_pool);
        }
    }
};

/// @anchor Subnet6ConfigParser
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
    /// stores global scope parameters, options, option definitions.
    Subnet6ConfigParser(const std::string&)
        :SubnetConfigParser("", globalContext(), IOAddress("::")) {
    }

    /// @brief Parses a single IPv6 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    void build(ConstElementPtr subnet) {
        /// Parse all pools first.
        ConstElementPtr pools = subnet->get("pools");
        if (pools) {
            Pools6ListParser parser;
            parser.parse(pools_, pools);
        }
        ConstElementPtr pd_pools = subnet->get("pd-pools");
        if (pd_pools) {
            PdPoolsListParser parser;
            parser.parse(pools_, pd_pools);
        }

        SubnetConfigParser::build(subnet);

        if (subnet_) {
            Subnet6Ptr sub6ptr = boost::dynamic_pointer_cast<Subnet6>(subnet_);
            if (!sub6ptr) {
                // If we hit this, it is a programming error.
                isc_throw(Unexpected,
                          "Invalid cast in Subnet6ConfigParser::commit");
            }

            // Set relay information if it was provided
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

            // Parse Host Reservations for this subnet if any.
            ConstElementPtr reservations = subnet->get("reservations");
            if (reservations) {
                HostReservationsListParser<HostReservationParser6> parser;
                parser.parse(subnet_->getID(), reservations);
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
                   (config_id.compare("interface-id") == 0) ||
                   (config_id.compare("reservation-mode") == 0)) {
            parser = new StringParser(config_id, string_values_);
        // pools has been converted to SimpleParser.
        // relay has been converted to SimpleParser.
        // pd-pools has been converted to SimpleParser.
        // option-data was here, but it is now converted to SimpleParser
        } else if (config_id.compare("rapid-commit") == 0) {
            parser = new BooleanParser(config_id, boolean_values_);
        } else {
            isc_throw(NotImplemented, "unsupported parameter: " << config_id);
        }

        return (parser);
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
        // representation only
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

        // Gather boolean parameters values.
        bool rapid_commit = boolean_values_->getOptionalParam("rapid-commit", false);

        std::ostringstream output;
        output << addr << "/" << static_cast<int>(len)
               << " with params t1=" << t1 << ", t2="
               << t2 << ", preferred-lifetime=" << pref
               << ", valid-lifetime=" << valid
               << ", rapid-commit is " << (rapid_commit ? "enabled" : "disabled");


        LOG_INFO(dhcp6_logger, DHCP6_CONFIG_NEW_SUBNET).arg(output.str());

        // Create a new subnet.
        Subnet6* subnet6 = new Subnet6(addr, len, t1, t2, pref, valid,
                                       subnet_id);

        // Configure interface-id for remote interfaces, if defined
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet6->setInterfaceId(opt);
        }

        // Enable or disable Rapid Commit option support for the subnet.
        subnet6->setRapidCommit(rapid_commit);

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

/// @brief Parser for list of RSOO options
///
/// This parser handles a Dhcp6/relay-supplied-options entry. It contains a
/// list of RSOO-enabled options which should be sent back to the client.
///
/// The options on this list can be specified using an option code or option
/// name. Therefore, the values on the list should always be enclosed in
/// "quotes".
class RSOOListConfigParser : public DhcpConfigParser {
public:

    /// @brief constructor
    ///
    /// As this is a dedicated parser, it must be used to parse
    /// "relay-supplied-options" parameter only. All other types will throw exception.
    ///
    /// @param param_name name of the configuration parameter being parsed
    /// @throw BadValue if supplied parameter name is not "relay-supplied-options"
    RSOOListConfigParser(const std::string& param_name) {
        if (param_name != "relay-supplied-options") {
            isc_throw(BadValue, "Internal error. RSOO configuration "
                      "parser called for the wrong parameter: " << param_name);
        }
    }

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of sources) and adds each element
    /// to the RSOO list.
    ///
    /// @param value pointer to the content of parsed values
    virtual void build(isc::data::ConstElementPtr value) {
        try {
            BOOST_FOREACH(ConstElementPtr source_elem, value->listValue()) {
                std::string option_str = source_elem->stringValue();
                // This option can be either code (integer) or name. Let's try code first
                int64_t code = 0;
                try {
                    code = boost::lexical_cast<int64_t>(option_str);
                    // Protect against the negative value and too high value.
                    if (code < 0) {
                        isc_throw(BadValue, "invalid option code value specified '"
                                  << option_str << "', the option code must be a"
                                  " non-negative value");

                    } else if (code > std::numeric_limits<uint16_t>::max()) {
                        isc_throw(BadValue, "invalid option code value specified '"
                                  << option_str << "', the option code must not be"
                                  " greater than '" << std::numeric_limits<uint16_t>::max()
                                  << "'");
                    }

                } catch (const boost::bad_lexical_cast &) {
                    // Oh well, it's not a number
                }

                if (!code) {
                    const OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP6_OPTION_SPACE,
                                                                          option_str);
                    if (def) {
                        code = def->getCode();
                    } else {
                        isc_throw(BadValue, "unable to find option code for the "
                                  " specified option name '" << option_str << "'"
                                  " while parsing the list of enabled"
                                  " relay-supplied-options");
                    }
                }
                CfgMgr::instance().getStagingCfg()->getCfgRSOO()->enable(code);
            }
        } catch (const std::exception& ex) {
            // Rethrow exception with the appended position of the parsed
            // element.
            isc_throw(DhcpConfigError, ex.what() << " (" << value->getPosition() << ")");
        }
    }

    /// @brief Does nothing.
    virtual void commit() {}
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
/// @param element pointer to the element to be parsed
/// @return parser for specified global DHCPv6 parameter
/// @throw NotImplemented if trying to create a parser for unknown config
/// element
DhcpConfigParser* createGlobal6DhcpConfigParser(const std::string& config_id,
                                                ConstElementPtr element) {
    DhcpConfigParser* parser = NULL;
    if ((config_id.compare("preferred-lifetime") == 0)  ||
        (config_id.compare("valid-lifetime") == 0)  ||
        (config_id.compare("renew-timer") == 0)  ||
        (config_id.compare("rebind-timer") == 0) ||
        (config_id.compare("decline-probation-period") == 0) ||
        (config_id.compare("dhcp4o6-port") == 0) )  {
        parser = new Uint32Parser(config_id,
                                 globalContext()->uint32_values_);
    } else if (config_id.compare("subnet6") == 0) {
        parser = new Subnets6ListConfigParser(config_id);
    // option-data and option-def are no longer needed here. They're now
    // converted to SimpleParser and are handled in configureDhcp6Server.
    // interfaces-config has been converted to SimpleParser.
    // version was removed - it was a leftover from bindctrl.
    // hooks-libraries is now converted to SimpleParser.
    // lease-database and hosts-database have been converted to SimpleParser already.
    // mac-source has been converted to SimpleParser.
    // dhcp-ddns has been converted to SimpleParser
    } else if (config_id.compare("relay-supplied-options") == 0) {
        parser = new RSOOListConfigParser(config_id);
    // control-socket has been converted to SimpleParser.
    // expired-leases-processing has been converted to SimpleParser.
    // client-classes has been converted to SimpleParser.
    // host-reservation-identifiers have been converted to SimpleParser already.
    // server-id has been migrated to SimpleParser
    } else {
        isc_throw(DhcpConfigError,
                "unsupported global configuration parameter: "
                  << config_id << " (" << element->getPosition() << ")");
    }

    return (parser);
}

/// @brief Sets global parameters in the staging configuration
///
/// Currently this method sets the following global parameters:
///
/// - decline-probation-period
/// - dhcp4o6-port
void setGlobalParameters6() {

    // Set the probation period for decline handling.
    try {
        uint32_t probation_period = globalContext()->uint32_values_
            ->getOptionalParam("decline-probation-period",
                               DEFAULT_DECLINE_PROBATION_PERIOD);
        CfgMgr::instance().getStagingCfg()->setDeclinePeriod(probation_period);
    } catch (...) {
        // That's not really needed.
    }

    // Set the DHCPv4-over-DHCPv6 interserver port.
    try {
        uint32_t dhcp4o6_port = globalContext()->uint32_values_
            ->getOptionalParam("dhcp4o6-port", 0);
        CfgMgr::instance().getStagingCfg()->setDhcp4o6Port(dhcp4o6_port);
    } catch (...) {
        // Ignore errors. This flag is optional
    }
}

/// @brief Initialize the command channel based on the staging configuration
///
/// Only close the current channel, if the new channel configuration is
/// different.  This avoids disconnecting a client and hence not sending them
/// a command result, unless they specifically alter the channel configuration.
/// In that case the user simply has to accept they'll be disconnected.
///
void configureCommandChannel() {
    // Get new socket configuration.
    ConstElementPtr sock_cfg =
        CfgMgr::instance().getStagingCfg()->getControlSocketInfo();

    // Get current socket configuration.
    ConstElementPtr current_sock_cfg =
            CfgMgr::instance().getCurrentCfg()->getControlSocketInfo();

    // Determine if the socket configuration has changed. It has if
    // both old and new configuration is specified but respective
    // data elements are't equal.
    bool sock_changed = (sock_cfg && current_sock_cfg &&
                         !sock_cfg->equals(*current_sock_cfg));

    // If the previous or new socket configuration doesn't exist or
    // the new configuration differs from the old configuration we
    // close the exisitng socket and open a new socket as appropriate.
    // Note that closing an existing socket means the clien will not
    // receive the configuration result.
    if (!sock_cfg || !current_sock_cfg || sock_changed) {
        // Close the existing socket (if any).
        isc::config::CommandMgr::instance().closeCommandSocket();

        if (sock_cfg) {
            // This will create a control socket and install the external
            // socket in IfaceMgr. That socket will be monitored when
            // Dhcp4Srv::receivePacket() calls IfaceMgr::receive4() and
            // callback in CommandMgr will be called, if necessary.
            isc::config::CommandMgr::instance().openCommandSocket(sock_cfg);
        }
    }
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

    // Reset global context.
    globalContext().reset(new ParserContext(Option::V6));

    // Before starting any subnet operations, let's reset the subnet-id counter,
    // so newly recreated configuration starts with first subnet-id equal 1.
    Subnet::resetSubnetID();

    // Remove any existing timers.
    TimerMgr::instance()->unregisterTimers();

    // Revert any runtime option definitions configured so far and not committed.
    LibDHCP::revertRuntimeOptionDefs();
    // Let's set empty container in case a user hasn't specified any configuration
    // for option definitions. This is equivalent to commiting empty container.
    LibDHCP::setRuntimeOptionDefs(OptionDefSpaceContainer());

    // Some of the values specified in the configuration depend on
    // other values. Typically, the values in the subnet6 structure
    // depend on the global values. Also, option values configuration
    // must be performed after the option definitions configurations.
    // Thus we group parsers and will fire them in the right order:
    // all parsers other than lease-database, subnet6 and
    // option-data parser, then option-data parser, subnet6 parser,
    // lease-database parser.
    // Please do not change this order!
    ParserCollection independent_parsers;
    ParserPtr subnet_parser;

    // Some of the parsers alter state of the system that can't easily
    // be undone. (Or alter it in a way such that undoing the change
    // has the same risk of failure as doing the change.)
    HooksLibrariesParser hooks_parser;

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
    // rollback informs whether error occurred and original data
    // have to be restored to global storages.
    bool rollback = false;
    // config_pair holds the details of the current parser when iterating over
    // the parsers.  It is declared outside the loop so in case of error, the
    // name of the failing parser can be retrieved within the "catch" clause.
    ConfigPair config_pair;
    try {

        SrvConfigPtr srv_config = CfgMgr::instance().getStagingCfg();

        // This is a way to convert ConstElementPtr to ElementPtr.
        // We need a config that can be edited, because we will insert
        // default values and will insert derived values as well.
        ElementPtr mutable_cfg = boost::const_pointer_cast<Element>(config_set);

        SimpleParser6::setAllDefaults(mutable_cfg);

        // Make parsers grouping.
        const std::map<std::string, ConstElementPtr>& values_map =
            mutable_cfg->mapValue();

        // We need definitions first
        ConstElementPtr option_defs = mutable_cfg->get("option-def");
        if (option_defs) {
            OptionDefListParser parser;
            CfgOptionDefPtr cfg_option_def = srv_config->getCfgOptionDef();
            parser.parse(cfg_option_def, option_defs);
        }

        BOOST_FOREACH(config_pair, values_map) {
            // In principle we could have the following code structured as a series
            // of long if else if clauses. That would give a marginal performance
            // boost, but would make the code less readable. We had serious issues
            // with the parser code debugability, so I decided to keep it as a
            // series of independent ifs.

            if (config_pair.first == "option-def") {
                // This is converted to SimpleParser and is handled already above.
                continue;
            }

            if (config_pair.first == "option-data") {
                OptionDataListParser parser(AF_INET6);
                CfgOptionPtr cfg_option = srv_config->getCfgOption();
                parser.parse(cfg_option, config_pair.second);
                continue;
            }

            if (config_pair.first == "mac-sources") {
                MACSourcesListConfigParser parser;
                CfgMACSource& mac_source = srv_config->getMACSources();
                parser.parse(mac_source, config_pair.second);
                continue;
            }

            if (config_pair.first == "control-socket") {
                ControlSocketParser parser;
                parser.parse(*srv_config, config_pair.second);
                continue;
            }

            if (config_pair.first == "host-reservation-identifiers") {
                HostReservationIdsParser6 parser;
                parser.parse(config_pair.second);
                continue;
            }

            if (config_pair.first == "server-id") {
                DUIDConfigParser parser;
                const CfgDUIDPtr& cfg = srv_config->getCfgDUID();
                parser.parse(cfg, config_pair.second);
                continue;
            }

            if (config_pair.first == "interfaces-config") {
                IfacesConfigParser parser(AF_INET6);
                CfgIfacePtr cfg_iface = srv_config->getCfgIface();
                parser.parse(cfg_iface, config_pair.second);
                continue;
            }

            if (config_pair.first == "expired-leases-processing") {
                ExpirationConfigParser parser;
                parser.parse(config_pair.second);
                continue;
            }

            if (config_pair.first == "hooks-libraries") {
                hooks_parser.parse(config_pair.second);
                hooks_parser.verifyLibraries();
                continue;
            }

            if (config_pair.first == "dhcp-ddns") {
                // Apply defaults if not in short cut
                if (!D2ClientConfigParser::isShortCutDisabled(config_pair.second)) {
                    D2ClientConfigParser::setAllDefaults(config_pair.second);
                }
                D2ClientConfigParser parser;
                D2ClientConfigPtr cfg = parser.parse(config_pair.second);
                srv_config->setD2ClientConfig(cfg);
                continue;
            }

            if (config_pair.first =="client-classes") {
                ClientClassDefListParser parser;
                ClientClassDictionaryPtr dictionary =
                    parser.parse(config_pair.second, AF_INET6);
                srv_config->setClientClassDictionary(dictionary);
                continue;
            }

            // Please move at the end when migration will be finished.
            if (config_pair.first == "lease-database") {
                DbAccessParser parser(DbAccessParser::LEASE_DB);
                CfgDbAccessPtr cfg_db_access = srv_config->getCfgDbAccess();
                parser.parse(cfg_db_access, config_pair.second);
                continue;
            }

            if (config_pair.first == "host-database") {
                DbAccessParser parser(DbAccessParser::HOSTS_DB);
                CfgDbAccessPtr cfg_db_access = srv_config->getCfgDbAccess();
                parser.parse(cfg_db_access, config_pair.second);
                continue;
            }

            ParserPtr parser(createGlobal6DhcpConfigParser(config_pair.first,
                                                           config_pair.second));
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PARSER_CREATED)
                      .arg(config_pair.first);
            if (config_pair.first == "subnet6") {
                subnet_parser = parser;
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

        // The subnet parser is the next one to be run.
        std::map<std::string, ConstElementPtr>::const_iterator subnet_config =
            values_map.find("subnet6");
        if (subnet_config != values_map.end()) {
            config_pair.first = "subnet6";
            subnet_parser->build(subnet_config->second);
        }

        // Setup the command channel.
        configureCommandChannel();

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());
        // An error occurred, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // for things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_EXCEPTION).arg(config_pair.first);
        answer = isc::config::createAnswer(1, "undefined configuration"
                                           " processing error");
        // An error occurred, so make sure that we restore original data.
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

            // Apply global options in the staging config.
            setGlobalParameters6();

            // No need to commit interface names as this is handled by the
            // CfgMgr::commit() function.

            // This occurs last as if it succeeds, there is no easy way to
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            hooks_parser.loadLibraries();

            // Apply staged D2ClientConfig, used to be done by parser commit
            D2ClientConfigPtr cfg;
            cfg = CfgMgr::instance().getStagingCfg()->getD2ClientConfig();
            CfgMgr::instance().setD2ClientConfig(cfg);
        }
        catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(2, ex.what());
            // An error occurred, so make sure to restore the original data.
            rollback = true;
        } catch (...) {
            // for things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(2, "undefined configuration"
                                               " parsing error");
            // An error occurred, so make sure to restore the original data.
            rollback = true;
        }
    }

    // Rollback changes as the configuration parsing failed.
    if (rollback) {
        globalContext().reset(new ParserContext(original_context));
        // Revert to original configuration of runtime option definitions
        // in the libdhcp++.
        LibDHCP::revertRuntimeOptionDefs();
        return (answer);
    }

    LOG_INFO(dhcp6_logger, DHCP6_CONFIG_COMPLETE)
        .arg(CfgMgr::instance().getStagingCfg()->
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
