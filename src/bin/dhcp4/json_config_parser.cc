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
#include <hooks/hooks_parser.h>
#include <config/command_mgr.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

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
using namespace isc::hooks;

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
        :SubnetConfigParser(AF_INET) {
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

        SubnetPtr generic = SubnetConfigParser::parse(subnet);

        if (!generic) {
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
            for (auto h = hosts.begin(); h != hosts.end(); ++h) {
                CfgMgr::instance().getStagingCfg()->getCfgHosts()->add(*h);
            }
        }

        return (sn4ptr);
    }

protected:

    /// @brief Instantiates the IPv4 Subnet based on a given IPv4 address
    /// and prefix length.
    ///
    /// @param addr is IPv4 address of the subnet.
    /// @param len is the prefix length
    void initSubnet(isc::data::ConstElementPtr params,
                    isc::asiolink::IOAddress addr, uint8_t len) {
        // The renew-timer and rebind-timer are optional. If not set, the
        // option 58 and 59 will not be sent to a client. In this case the
        // client will use default values based on the valid-lifetime.
        Triplet<uint32_t> t1 = getInteger(params, "renew-timer");
        Triplet<uint32_t> t2 = getInteger(params, "rebind-timer");

        // The valid-lifetime is mandatory. It may be specified for a
        // particular subnet. If not, the global value should be present.
        // If there is no global value, exception is thrown.
        Triplet<uint32_t> valid = getInteger(params, "valid-lifetime");

        // Subnet ID is optional. If it is not supplied the value of 0 is used,
        // which means autogenerate. The value was inserted earlier by calling
        // SimpleParser4::setAllDefaults.
        SubnetID subnet_id = static_cast<SubnetID>(getInteger(params, "id"));

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

        // Set the match-client-id value for the subnet. It is always present.
        // If not explicitly specified, the default value was filled in when
        // SimpleParser4::setAllDefaults was called.
        bool match_client_id = getBoolean(params, "match-client-id");
        subnet4->setMatchClientId(match_client_id);

        // Set next-server. The default value is 0.0.0.0. Nevertheless, the
        // user could have messed that up by specifying incorrect value.
        // To avoid using 0.0.0.0, user can specify "".
        string next_server;
        try {
            next_server = getString(params, "next-server");
            if (!next_server.empty()) {
                subnet4->setSiaddr(IOAddress(next_server));
            }
        } catch (...) {
            ConstElementPtr next = params->get("next-server");
            string pos;
            if (next)
                pos = next->getPosition().str();
            else
                pos = params->getPosition().str();
            isc_throw(DhcpConfigError, "invalid parameter next-server : "
                      << next_server << "(" << pos << ")");
        }

        // 4o6 specific parameter: 4o6-interface. If not explicitly specified,
        // it will have the default value of "".
        string iface4o6 = getString(params, "4o6-interface");
        if (!iface4o6.empty()) {
            subnet4->get4o6().setIface4o6(iface4o6);
            subnet4->get4o6().enabled(true);
        }

        // 4o6 specific parameter: 4o6-subnet. If not explicitly specified, it
        // will have the default value of "".
        string subnet4o6 = getString(params, "4o6-subnet");
        if (!subnet4o6.empty()) {
            size_t slash = subnet4o6.find("/");
            if (slash == std::string::npos) {
                isc_throw(DhcpConfigError, "Missing / in the 4o6-subnet parameter:"
                          << subnet4o6 << ", expected format: prefix6/length");
            }
            string prefix = subnet4o6.substr(0, slash);
            string lenstr = subnet4o6.substr(slash + 1);

            uint8_t len = 128;
            try {
                len = boost::lexical_cast<unsigned int>(lenstr.c_str());
            } catch (const boost::bad_lexical_cast &) {
                isc_throw(DhcpConfigError, "Invalid prefix length specified in "
                          "4o6-subnet parameter: " << subnet4o6 << ", expected 0..128 value");
            }
            subnet4->get4o6().setSubnet4o6(IOAddress(prefix), len);
            subnet4->get4o6().enabled(true);
        }

        // Try 4o6 specific parameter: 4o6-interface-id
        std::string ifaceid = getString(params, "4o6-interface-id");
        if (!ifaceid.empty()) {
            OptionBuffer tmp(ifaceid.begin(), ifaceid.end());
            OptionPtr opt(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
            subnet4->get4o6().setInterfaceId(opt);
            subnet4->get4o6().enabled(true);
        }

        /// client-class processing is now generic and handled in the common
        /// code (see @ref isc::data::SubnetConfigParser::createSubnet)
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

/// @brief Parser that takes care of global DHCPv4 parameters.
///
/// See @ref parse method for a list of supported parameters.
class Dhcp4ConfigParser : public isc::data::SimpleParser {
public:

    /// @brief Sets global parameters in staging configuration
    ///
    /// @param global global configuration scope
    /// @param cfg Server configuration (parsed parameters will be stored here)
    ///
    /// Currently this method sets the following global parameters:
    ///
    /// - echo-client-id
    /// - decline-probation-period
    /// - dhcp4o6-port
    ///
    /// @throw DhcpConfigError if parameters are missing or
    /// or having incorrect values.
    void parse(SrvConfigPtr cfg, ConstElementPtr global) {

        // Set whether v4 server is supposed to echo back client-id
        // (yes = RFC6842 compatible, no = backward compatibility)
        bool echo_client_id = getBoolean(global, "echo-client-id");
        cfg->setEchoClientId(echo_client_id);

        // Set the probation period for decline handling.
        uint32_t probation_period =
            getUint32(global, "decline-probation-period");
        cfg->setDeclinePeriod(probation_period);

        // Set the DHCPv4-over-DHCPv6 interserver port.
        uint16_t dhcp4o6_port = getUint16(global, "dhcp4o6-port");
        cfg->setDhcp4o6Port(dhcp4o6_port);
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
configureDhcp4Server(Dhcpv4Srv&, isc::data::ConstElementPtr config_set,
                     bool check_only) {
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

    // Remove any existing timers.
    if (!check_only) {
        TimerMgr::instance()->unregisterTimers();
    }

    // Revert any runtime option definitions configured so far and not committed.
    LibDHCP::revertRuntimeOptionDefs();
    // Let's set empty container in case a user hasn't specified any configuration
    // for option definitions. This is equivalent to commiting empty container.
    LibDHCP::setRuntimeOptionDefs(OptionDefSpaceContainer());

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
                HooksLibrariesParser hooks_parser;
                HooksConfig& libraries = srv_cfg->getHooksConfig();
                hooks_parser.parse(libraries, config_pair.second);
                libraries.verifyLibraries(config_pair.second->getPosition());
                continue;
            }

            // Legacy DhcpConfigParser stuff below
            if (config_pair.first == "dhcp-ddns") {
                // Apply defaults
                D2ClientConfigParser::setAllDefaults(config_pair.second);
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

            // Timers are not used in the global scope. Their values are derived
            // to specific subnets (see SimpleParser6::deriveParameters).
            // decline-probation-period, dhcp4o6-port, echo-client-id are
            // handled in global_parser.parse() which sets global parameters.
            // match-client-id is derived to subnet scope level.
            if ( (config_pair.first == "renew-timer") ||
                 (config_pair.first == "rebind-timer") ||
                 (config_pair.first == "valid-lifetime") ||
                 (config_pair.first == "decline-probation-period") ||
                 (config_pair.first == "dhcp4o6-port") ||
                 (config_pair.first == "echo-client-id") ||
                 (config_pair.first == "match-client-id") ||
                 (config_pair.first == "next-server")) {
                continue;
            }

            // If we got here, no code handled this parameter, so we bail out.
            isc_throw(DhcpConfigError,
                      "unsupported global configuration parameter: " << config_pair.first
                      << " (" << config_pair.second->getPosition() << ")");
        }

        // Apply global options in the staging config.
        Dhcp4ConfigParser global_parser;
        global_parser.parse(srv_cfg, mutable_cfg);

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

            // Apply the staged D2ClientConfig, used to be done by parser commit
            D2ClientConfigPtr cfg;
            cfg = CfgMgr::instance().getStagingCfg()->getD2ClientConfig();
            CfgMgr::instance().setD2ClientConfig(cfg);

            // This occurs last as if it succeeds, there is no easy way
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            const HooksConfig& libraries =
                CfgMgr::instance().getStagingCfg()->getHooksConfig();
            libraries.loadLibraries();
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

}; // end of isc::dhcp namespace
}; // end of isc namespace
