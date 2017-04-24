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
#include <hooks/hooks_parser.h>
#include <log/logger_support.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

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
using namespace isc::hooks;

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
    void parse(PoolStoragePtr pools, ConstElementPtr pd_pool_) {
        std::string addr_str = getString(pd_pool_, "prefix");

        uint8_t prefix_len = getUint8(pd_pool_, "prefix-len");

        uint8_t delegated_len = getUint8(pd_pool_, "delegated-len");

        std::string excluded_prefix_str = "::";
        if (pd_pool_->contains("excluded-prefix")) {
            excluded_prefix_str = getString(pd_pool_, "excluded-prefix");
        }

        uint8_t excluded_prefix_len = 0;
        if (pd_pool_->contains("excluded-prefix-len")) {
            excluded_prefix_len = getUint8(pd_pool_, "excluded-prefix-len");
        }

        ConstElementPtr option_data = pd_pool_->get("option-data");
        if (option_data) {
            OptionDataListParser opts_parser(AF_INET6);
            opts_parser.parse(options_, option_data);
        }
                    
        ConstElementPtr user_context = pd_pool_->get("user-context");
        if (user_context) {
            user_context_ = user_context;
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
    /// stores global scope parameters, options, option definitions.
    Subnet6ConfigParser()
        :SubnetConfigParser(AF_INET6) {
    }

    /// @brief Parses a single IPv6 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    /// @return a pointer to created Subnet6 object
    Subnet6Ptr parse(ConstElementPtr subnet) {
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

        SubnetPtr generic = SubnetConfigParser::parse(subnet);

        if (!generic) {
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
            for (auto h = hosts.begin(); h != hosts.end(); ++h) {
                CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(*h);
            }
        }

        return (sn6ptr);
    }

protected:
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
    void initSubnet(isc::data::ConstElementPtr params,
                    isc::asiolink::IOAddress addr, uint8_t len) {
        // Get all 'time' parameters using inheritance.
        // If the subnet-specific value is defined then use it, else
        // use the global value. The global value must always be
        // present. If it is not, it is an internal error and exception
        // is thrown.
        Triplet<uint32_t> t1 = getInteger(params, "renew-timer");
        Triplet<uint32_t> t2 = getInteger(params, "rebind-timer");
        Triplet<uint32_t> pref = getInteger(params, "preferred-lifetime");
        Triplet<uint32_t> valid = getInteger(params, "valid-lifetime");

        // Subnet ID is optional. If it is not supplied the value of 0 is used,
        // which means autogenerate. The value was inserted earlier by calling
        // SimpleParser6::setAllDefaults.
        SubnetID subnet_id = static_cast<SubnetID>(getInteger(params, "id"));

        // We want to log whether rapid-commit is enabled, so we get this
        // before the actual subnet creation.
        bool rapid_commit = getBoolean(params, "rapid-commit");

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
        subnet_.reset(subnet6);

        // Enable or disable Rapid Commit option support for the subnet.
        subnet6->setRapidCommit(rapid_commit);

        // Get interface-id option content. For now we support string
        // representation only
        std::string ifaceid = getString(params, "interface-id");
        std::string iface = getString(params, "interface");

        // Specifying both interface for locally reachable subnets and
        // interface id for relays is mutually exclusive. Need to test for
        // this condition.
        if (!ifaceid.empty() && !iface.empty()) {
            isc_throw(isc::dhcp::DhcpConfigError,
                      "parser error: interface (defined for locally reachable "
                      "subnets) and interface-id (defined for subnets reachable"
                      " via relays) cannot be defined at the same time for "
                      "subnet " << addr << "/" << (int)len << "("
                      << params->getPosition() << ")");
        }

        // Configure interface-id for remote interfaces, if defined
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet6->setInterfaceId(opt);
        }

        /// client-class processing is now generic and handled in the common
        /// code (see @ref isc::data::SubnetConfigParser::createSubnet)
    }

};


/// @brief this class parses a list of DHCP6 subnets
///
/// This is a wrapper parser that handles the whole list of Subnet6
/// definitions. It iterates over all entries and creates Subnet6ConfigParser
/// for each entry.
class Subnets6ListConfigParser : public isc::data::SimpleParser {
public:

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list, parses its content
    /// (by instantiating Subnet6ConfigParser) and adds to specified
    /// configuration.
    ///
    /// @param cfg configuration (parsed subnets will be stored here)
    /// @param subnets_list pointer to a list of IPv6 subnets
    /// @throw DhcpConfigError if CfgMgr rejects the subnet (e.g. subnet-id is a duplicate)
    size_t parse(SrvConfigPtr cfg, ConstElementPtr subnets_list) {
        size_t cnt = 0;
        BOOST_FOREACH(ConstElementPtr subnet_json, subnets_list->listValue()) {

            Subnet6ConfigParser parser;
            Subnet6Ptr subnet = parser.parse(subnet_json);

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
};

/// @brief Parser for list of RSOO options
///
/// This parser handles a Dhcp6/relay-supplied-options entry. It contains a
/// list of RSOO-enabled options which should be sent back to the client.
///
/// The options on this list can be specified using an option code or option
/// name. Therefore, the values on the list should always be enclosed in
/// "quotes".
class RSOOListConfigParser : public isc::data::SimpleParser {
public:

    /// @brief parses parameters value
    ///
    /// Parses configuration entry (list of sources) and adds each element
    /// to the RSOO list.
    ///
    /// @param value pointer to the content of parsed values
    /// @param cfg server configuration (RSOO will be stored here)
    void parse(SrvConfigPtr cfg, isc::data::ConstElementPtr value) {
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
                cfg->getCfgRSOO()->enable(code);
            }
        } catch (const std::exception& ex) {
            // Rethrow exception with the appended position of the parsed
            // element.
            isc_throw(DhcpConfigError, ex.what() << " (" << value->getPosition() << ")");
        }
    }
};

/// @brief Parser that takes care of global DHCPv6 parameters.
///
/// See @ref parse method for a list of supported parameters.
class Dhcp6ConfigParser : public isc::data::SimpleParser {
public:

    /// @brief Sets global parameters in staging configuration
    ///
    /// @param global global configuration scope
    /// @param cfg Server configuration (parsed parameters will be stored here)
    ///
    /// Currently this method sets the following global parameters:
    ///
    /// - decline-probation-period
    /// - dhcp4o6-port
    ///
    /// @throw DhcpConfigError if parameters are missing or
    /// or having incorrect values.
    void parse(SrvConfigPtr srv_config, ConstElementPtr global) {

        // Set the probation period for decline handling.
        uint32_t probation_period =
            getUint32(global, "decline-probation-period");
        srv_config->setDeclinePeriod(probation_period);

        // Set the DHCPv4-over-DHCPv6 interserver port.
        uint16_t dhcp4o6_port = getUint16(global, "dhcp4o6-port");
        srv_config->setDhcp4o6Port(dhcp4o6_port);
    }
};

} // anonymous namespace

namespace isc {
namespace dhcp {

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
configureDhcp6Server(Dhcpv6Srv&, isc::data::ConstElementPtr config_set,
                     bool check_only) {

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

    // Remove any existing timers.
    if (!check_only) {
        TimerMgr::instance()->unregisterTimers();
    }

    // Revert any runtime option definitions configured so far and not committed.
    LibDHCP::revertRuntimeOptionDefs();
    // Let's set empty container in case a user hasn't specified any configuration
    // for option definitions. This is equivalent to commiting empty container.
    LibDHCP::setRuntimeOptionDefs(OptionDefSpaceContainer());

    // This is a way to convert ConstElementPtr to ElementPtr.
    // We need a config that can be edited, because we will insert
    // default values and will insert derived values as well.
    ElementPtr mutable_cfg = boost::const_pointer_cast<Element>(config_set);

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

        // Set all default values if not specified by the user.
        SimpleParser6::setAllDefaults(mutable_cfg);

        // And now derive (inherit) global parameters to subnets, if not specified.
        SimpleParser6::deriveParameters(mutable_cfg);

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
                HooksLibrariesParser hooks_parser;
                HooksConfig& libraries = srv_config->getHooksConfig();
                hooks_parser.parse(libraries, config_pair.second);
                libraries.verifyLibraries(config_pair.second->getPosition());
                continue;
            }

            if (config_pair.first == "dhcp-ddns") {
                // Apply defaults
                D2ClientConfigParser::setAllDefaults(config_pair.second);
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

            if (config_pair.first == "hosts-database") {
                DbAccessParser parser(DbAccessParser::HOSTS_DB);
                CfgDbAccessPtr cfg_db_access = srv_config->getCfgDbAccess();
                parser.parse(cfg_db_access, config_pair.second);
                continue;
            }

            if (config_pair.first == "subnet6") {
                SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();
                Subnets6ListConfigParser subnets_parser;
                // parse() returns number of subnets parsed. We may log it one day.
                subnets_parser.parse(srv_cfg, config_pair.second);
                continue;
            }

            // Timers are not used in the global scope. Their values are derived
            // to specific subnets (see SimpleParser6::deriveParameters).
            // decline-probation-period and dhcp4o6-port are handled in the
            // global_parser.parse() which sets global parameters.
            if ( (config_pair.first == "renew-timer") ||
                 (config_pair.first == "rebind-timer") ||
                 (config_pair.first == "preferred-lifetime") ||
                 (config_pair.first == "valid-lifetime") ||
                 (config_pair.first == "decline-probation-period") ||
                 (config_pair.first == "dhcp4o6-port")) {
                continue;
            }

            if (config_pair.first == "relay-supplied-options") {
                RSOOListConfigParser parser;
                parser.parse(srv_config, config_pair.second);
                continue;
            }

            // If we got here, no code handled this parameter, so we bail out.
            isc_throw(DhcpConfigError,
                      "unsupported global configuration parameter: " << config_pair.first
                      << " (" << config_pair.second->getPosition() << ")");
        }

        // Apply global options in the staging config.
        Dhcp6ConfigParser global_parser;
        global_parser.parse(srv_config, mutable_cfg);

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

    if (check_only) {
        rollback = true;
        if (!answer) {
            answer = isc::config::createAnswer(0,
            "Configuration seems sane. Control-socket, hook-libraries, and D2 "
            "configuration were sanity checked, but not applied.");
        }
    }

    // So far so good, there was no parsing error so let's commit the
    // configuration. This will add created subnets and option values into
    // the server's configuration.
    // This operation should be exception safe but let's make sure.
    if (!rollback) {
        try {

            // Setup the command channel.
            configureCommandChannel();
            
            // No need to commit interface names as this is handled by the
            // CfgMgr::commit() function.

            // Apply staged D2ClientConfig, used to be done by parser commit
            D2ClientConfigPtr cfg;
            cfg = CfgMgr::instance().getStagingCfg()->getD2ClientConfig();
            CfgMgr::instance().setD2ClientConfig(cfg);

            // This occurs last as if it succeeds, there is no easy way to
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            const HooksConfig& libraries =
                CfgMgr::instance().getStagingCfg()->getHooksConfig();
            libraries.loadLibraries();
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

}; // end of isc::dhcp namespace
}; // end of isc namespace
