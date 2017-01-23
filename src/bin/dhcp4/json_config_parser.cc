// Copyright (C) 2012-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/simple_parser4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcp4/json_config_parser.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <dhcpsrv/timer_mgr.h>
#include <config/command_mgr.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <defaults.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <limits>
#include <iostream>
#include <netinet/in.h>
#include <vector>
#include <map>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace {

/// @brief Parser for IPv4 pool definitions.
///
/// This is the IPv4 derivation of the PoolParser class and handles pool
/// definitions, i.e. a list of entries of one of two syntaxes: min-max and
/// prefix/len for IPv4 pools. Pool4 objects are created and stored in chosen
/// PoolStorage container.
///
/// It is useful for parsing Dhcp4/subnet4[X]/pool parameters.
class Pool4Parser : public PoolParser {
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

/// @brief Specialization of the pool list parser for DHCPv4
class Pools4ListParser : PoolsListParser {
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
            Pool4Parser parser;
            parser.parse(pools, pool, AF_INET);
        }
    }
};

/// @anchor Subnet4ConfigParser
/// @brief This class parses a single IPv4 subnet.
///
/// This is the IPv4 derivation of the SubnetConfigParser class and it parses
/// the whole subnet definition. It creates parsersfor received configuration
/// parameters as needed.
class Subnet4ConfigParser : public SubnetConfigParser {
public:
    /// @brief Constructor
    ///
    /// stores global scope parameters, options, option definitions.
    Subnet4ConfigParser()
        :SubnetConfigParser("", globalContext(), IOAddress("0.0.0.0")) {
    }

    /// @brief Parses a single IPv4 subnet configuration and adds to the
    /// Configuration Manager.
    ///
    /// @param subnet A new subnet being configured.
    /// @return a pointer to created Subnet4 object
    Subnet4Ptr parse(ConstElementPtr subnet) {
        /// Parse Pools first.
        ConstElementPtr pools = subnet->get("pools");
        if (pools) {
            Pools4ListParser parser;
            parser.parse(pools_, pools);
        }

        SubnetPtr generic = SubnetConfigParser::build(subnet);

        Subnet4Ptr sub4ptr = boost::dynamic_pointer_cast<Subnet4>(generic);
        if (!sub4ptr) {
            // If we hit this, it is a programming error.
            isc_throw(Unexpected,
                      "Invalid Subnet4 cast in Subnet4ConfigParser::parse");
        }

        // Set relay information if it was parsed
        if (relay_info_) {
            sub4ptr->setRelayInfo(*relay_info_);
        }

        // Parse Host Reservations for this subnet if any.
        ConstElementPtr reservations = subnet->get("reservations");
        if (reservations) {
            HostReservationsListParser<HostReservationParser4> parser;
            parser.parse(subnet_->getID(), reservations);
        }

        return (sub4ptr);
    }

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
                   (config_id.compare("next-server") == 0) ||
                   (config_id.compare("reservation-mode") == 0)) {
            parser = new StringParser(config_id, string_values_);
        // pools has been converted to SimpleParser already.
        // relay has been converted to SimpleParser already.
        // option-data has been converted to SimpleParser already.
        } else if (config_id.compare("match-client-id") == 0) {
            parser = new BooleanParser(config_id, boolean_values_);
        } else if (config_id.compare("4o6-subnet") == 0) {
            parser = new StringParser(config_id, string_values_);
        } else if (config_id.compare("4o6-interface") == 0) {
            parser = new StringParser(config_id, string_values_);
        } else if (config_id.compare("4o6-interface-id") == 0) {
            parser = new StringParser(config_id, string_values_);
        } else {
            isc_throw(NotImplemented, "unsupported parameter: " << config_id);
        }

        return (parser);
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

        // match-client-id
        isc::util::OptionalValue<bool> match_client_id;
        try {
            match_client_id = boolean_values_->getParam("match-client-id");

        } catch (...) {
            // Ignore because this parameter is optional and it may be specified
            // in the global scope.
        }

        // If the match-client-id wasn't specified as a subnet specific parameter
        // check if there is global value specified.
        if (!match_client_id.isSpecified()) {
            // If not specified, use false.
            match_client_id.specify(globalContext()->boolean_values_->
                                    getOptionalParam("match-client-id", true));
        }

        // Set the match-client-id value for the subnet.
        subnet4->setMatchClientId(match_client_id.get());

        // next-server
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

        // Try 4o6 specific parameter: 4o6-interface
        string iface4o6 = string_values_->getOptionalParam("4o6-interface", "");
        if (!iface4o6.empty()) {
            subnet4->get4o6().setIface4o6(iface4o6);
            subnet4->get4o6().enabled(true);
        }

        // Try 4o6 specific parameter: 4o6-subnet
        string subnet4o6 = string_values_->getOptionalParam("4o6-subnet", "");
        if (!subnet4o6.empty()) {
            size_t slash = subnet4o6.find("/");
            if (slash == std::string::npos) {
                isc_throw(DhcpConfigError, "Missing / in the 4o6-subnet parameter:"
                          + subnet4o6 +", expected format: prefix6/length");
            }
            string prefix = subnet4o6.substr(0, slash);
            string lenstr = subnet4o6.substr(slash + 1);

            uint8_t len = 128;
            try {
                len = boost::lexical_cast<unsigned int>(lenstr.c_str());
            } catch (const boost::bad_lexical_cast &) {
                isc_throw(DhcpConfigError, "Invalid prefix length specified in "
                          "4o6-subnet parameter: " + subnet4o6 + ", expected 0..128 value");
            }
            subnet4->get4o6().setSubnet4o6(IOAddress(prefix), len);
            subnet4->get4o6().enabled(true);
        }

        // Try 4o6 specific parameter: 4o6-interface-id
        std::string ifaceid = string_values_->getOptionalParam("4o6-interface-id", "");
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet4->get4o6().setInterfaceId(opt);
            subnet4->get4o6().enabled(true);
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
class Subnets4ListConfigParser : public isc::data::SimpleParser {
public:

    /// @brief parses contents of the list
    ///
    /// Iterates over all entries on the list, parses its content
    /// (by instantiating Subnet6ConfigParser) and adds to specified
    /// configuration.
    ///
    /// @param subnets_list pointer to a list of IPv4 subnets
    /// @return number of subnets created
    size_t parse(SrvConfigPtr cfg, ConstElementPtr subnets_list) {
        size_t cnt = 0;
        BOOST_FOREACH(ConstElementPtr subnet_json, subnets_list->listValue()) {

            Subnet4ConfigParser parser;
            Subnet4Ptr subnet = parser.parse(subnet_json);
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
/// @param element pointer to the element to be parsed
/// @return parser for specified global DHCPv4 parameter
/// @throw NotImplemented if trying to create a parser for unknown
/// config element
DhcpConfigParser* createGlobalDhcp4ConfigParser(const std::string& config_id,
                                                ConstElementPtr element) {
    DhcpConfigParser* parser = NULL;
    if ((config_id.compare("valid-lifetime") == 0)  ||
        (config_id.compare("renew-timer") == 0)  ||
        (config_id.compare("rebind-timer") == 0) ||
        (config_id.compare("decline-probation-period") == 0) ||
        (config_id.compare("dhcp4o6-port") == 0) )  {
        parser = new Uint32Parser(config_id,
                                  globalContext()->uint32_values_);
    // subnet4 has been migrated to SimpleParser already.
    // interface-config has been migrated to SimpleParser already.
    // option-data and option-def have been converted to SimpleParser already.
    } else if ((config_id.compare("next-server") == 0)) {
        parser  = new StringParser(config_id,
                                    globalContext()->string_values_);
    // hooks-libraries are now migrated to SimpleParser.
    // lease-database and hosts-database have been converted to SimpleParser already.
     } else if (config_id.compare("echo-client-id") == 0) {
        parser = new BooleanParser(config_id, globalContext()->boolean_values_);
    // dhcp-ddns has been converted to SimpleParser.
    } else if (config_id.compare("match-client-id") == 0) {
        parser = new BooleanParser(config_id, globalContext()->boolean_values_);
    // control-socket has been converted to SimpleParser already.
    // expired-leases-processing has been converted to SimpleParser already.
    // client-classes has been converted to SimpleParser already.
    // host-reservation-identifiers have been converted to SimpleParser already.
    } else {
        isc_throw(DhcpConfigError,
                "unsupported global configuration parameter: "
                  << config_id << " (" << element->getPosition() << ")");
    }

    return (parser);
}

/// @brief Sets global parameters in staging configuration
///
/// Currently this method sets the following global parameters:
///
/// - echo-client-id
/// - decline-probation-period
/// - dhcp4o6-port
void setGlobalParameters4() {
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
configureDhcp4Server(Dhcpv4Srv&, isc::data::ConstElementPtr config_set) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(1,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND,
              DHCP4_CONFIG_START).arg(config_set->str());

    // Reset global context.
    globalContext().reset(new ParserContext(Option::V4));

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
    // other values. Typically, the values in the subnet4 structure
    // depend on the global values. Also, option values configuration
    // must be performed after the option definitions configurations.
    // Thus we group parsers and will fire them in the right order:
    // all parsers other than: lease-database, subnet4 and option-data parser,
    // then: option-data parser, subnet4 parser, lease-database parser.
    // Please do not change this order!
    ParserCollection independent_parsers;

    // Some of the parsers alter the state of the system in a way that can't
    // easily be undone. (Or alter it in a way such that undoing the change has
    // the same risk of failure as doing the change.)
    HooksLibrariesParser hooks_parser;

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
    // Rollback informs whether error occurred and original data
    // have to be restored to global storages.
    bool rollback = false;
    // config_pair holds the details of the current parser when iterating over
    // the parsers.  It is declared outside the loops so in case of an error,
    // the name of the failing parser can be retrieved in the "catch" clause.
    ConfigPair config_pair;
    try {

        SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();

        // This is a way to convert ConstElementPtr to ElementPtr.
        // We need a config that can be edited, because we will insert
        // default values and will insert derived values as well.
        ElementPtr mutable_cfg = boost::const_pointer_cast<Element>(config_set);

        // Set all default values if not specified by the user.
        SimpleParser4::setAllDefaults(mutable_cfg);

        // And now derive (inherit) global parameters to subnets, if not specified.
        SimpleParser4::deriveParameters(mutable_cfg);

        // We need definitions first
        ConstElementPtr option_defs = mutable_cfg->get("option-def");
        if (option_defs) {
            OptionDefListParser parser;
            CfgOptionDefPtr cfg_option_def = srv_cfg->getCfgOptionDef();
            parser.parse(cfg_option_def, option_defs);
        }

        // Make parsers grouping.
        const std::map<std::string, ConstElementPtr>& values_map =
                                                        mutable_cfg->mapValue();
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
                OptionDataListParser parser(AF_INET);
                CfgOptionPtr cfg_option = srv_cfg->getCfgOption();
                parser.parse(cfg_option, config_pair.second);
                continue;
            }

            if (config_pair.first == "control-socket") {
                ControlSocketParser parser;
                parser.parse(*srv_cfg, config_pair.second);
                continue;
            }

            if (config_pair.first == "host-reservation-identifiers") {
                HostReservationIdsParser4 parser;
                parser.parse(config_pair.second);
                continue;
            }

            if (config_pair.first == "interfaces-config") {
                IfacesConfigParser parser(AF_INET);
                CfgIfacePtr cfg_iface = srv_cfg->getCfgIface();
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

            // Legacy DhcpConfigParser stuff below
            if (config_pair.first == "dhcp-ddns") {
                // Apply defaults if not in short cut
                if (!D2ClientConfigParser::isShortCutDisabled(config_pair.second)) {
                    D2ClientConfigParser::setAllDefaults(config_pair.second);
                }
                D2ClientConfigParser parser;
                D2ClientConfigPtr cfg = parser.parse(config_pair.second);
                srv_cfg->setD2ClientConfig(cfg);
                continue;
            }

            if (config_pair.first == "client-classes") {
                ClientClassDefListParser parser;
                ClientClassDictionaryPtr dictionary =
                    parser.parse(config_pair.second, AF_INET);
                srv_cfg->setClientClassDictionary(dictionary);
                continue;
            }

            // Please move at the end when migration will be finished.
            if (config_pair.first == "lease-database") {
                DbAccessParser parser(DbAccessParser::LEASE_DB);
                CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                parser.parse(cfg_db_access, config_pair.second);
                continue;
            }

            if (config_pair.first == "hosts-database") {
                DbAccessParser parser(DbAccessParser::HOSTS_DB);
                CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                parser.parse(cfg_db_access, config_pair.second);
                continue;
            }

            if (config_pair.first == "subnet4") {
                SrvConfigPtr srv_cfg = CfgMgr::instance().getStagingCfg();
                Subnets4ListConfigParser subnets_parser;
                // parse() returns number of subnets parsed. We may log it one day.
                subnets_parser.parse(srv_cfg, config_pair.second);
                continue;
            }

            ParserPtr parser(createGlobalDhcp4ConfigParser(config_pair.first,
                                                           config_pair.second));
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_PARSER_CREATED)
                      .arg(config_pair.first);

            // Those parsers should be started before other
            // parsers so we can call build straight away.
            independent_parsers.push_back(parser);
            parser->build(config_pair.second);
            // The commit operation here may modify the global storage
            // but we need it so as the subnet6 parser can access the
            // parsed data.
            parser->commit();
        }

        // Setup the command channel.
        configureCommandChannel();

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(1, ex.what());

        // An error occurred, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // For things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_EXCEPTION).arg(config_pair.first);
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
            // No need to commit interface names as this is handled by the
            // CfgMgr::commit() function.

            // Apply global options in the staging config.
            setGlobalParameters4();

            // This occurs last as if it succeeds, there is no easy way
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            hooks_parser.loadLibraries();

            // Apply the staged D2ClientConfig, used to be done by parser commit
            D2ClientConfigPtr cfg;
            cfg = CfgMgr::instance().getStagingCfg()->getD2ClientConfig();
            CfgMgr::instance().setD2ClientConfig(cfg);
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
        // Revert to original configuration of runtime option definitions
        // in the libdhcp++.
        LibDHCP::revertRuntimeOptionDefs();
        return (answer);
    }

    LOG_INFO(dhcp4_logger, DHCP4_CONFIG_COMPLETE)
        .arg(CfgMgr::instance().getStagingCfg()->
             getConfigSummary(SrvConfig::CFGSEL_ALL4));

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
