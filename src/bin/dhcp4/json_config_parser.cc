// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <database/dbaccess_parser.h>
#include <database/backend_selector.h>
#include <database/server_selector.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/db_type.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/dhcp_queue_control_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/shared_networks_list_parser.h>
#include <dhcpsrv/parsers/sanity_checks_parser.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/timer_mgr.h>
#include <process/config_ctl_parser.h>
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
using namespace isc::process;
using namespace isc::config;
using namespace isc::db;

namespace {

/// @brief Parser that takes care of global DHCPv4 parameters and utility
///        functions that work on global level.
///
/// This class is a collection of utility method that either handle
/// global parameters (see @ref parse), or conducts operations on
/// global level (see @ref sanityChecks and @ref copySubnets4).
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
    /// - user-context
    ///
    /// @throw DhcpConfigError if parameters are missing or
    /// or having incorrect values.
    void parse(const SrvConfigPtr& cfg, const ConstElementPtr& global) {

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

        // Set the global user context.
        ConstElementPtr user_context = global->get("user-context");
        if (user_context) {
            cfg->setContext(user_context);
        }

        // Set the server's logical name
        std::string server_tag = getString(global, "server-tag");
        cfg->setServerTag(server_tag);
    }

    /// @brief Copies subnets from shared networks to regular subnets container
    ///
    /// @param from pointer to shared networks container (copy from here)
    /// @param dest pointer to cfg subnets4 (copy to here)
    /// @throw BadValue if any pointer is missing
    /// @throw DhcpConfigError if there are duplicates (or other subnet defects)
    void
    copySubnets4(const CfgSubnets4Ptr& dest, const CfgSharedNetworks4Ptr& from) {

        if (!dest || !from) {
            isc_throw(BadValue, "Unable to copy subnets: at least one pointer is null");
        }

        const SharedNetwork4Collection* networks = from->getAll();
        if (!networks) {
            // Nothing to copy. Technically, it should return a pointer to empty
            // container, but let's handle null pointer as well.
            return;
        }

        // Let's go through all the networks one by one
        for (auto net = networks->begin(); net != networks->end(); ++net) {

            // For each network go through all the subnets in it.
            const Subnet4Collection* subnets = (*net)->getAllSubnets();
            if (!subnets) {
                // Shared network without subnets it weird, but we decided to
                // accept such configurations.
                continue;
            }

            // For each subnet, add it to a list of regular subnets.
            for (auto subnet = subnets->begin(); subnet != subnets->end(); ++subnet) {
                dest->add(*subnet);
            }
        }
    }

    /// @brief Conducts global sanity checks
    ///
    /// This method is very simple now, but more sanity checks are expected
    /// in the future.
    ///
    /// @param cfg - the parsed structure
    /// @param global global Dhcp4 scope
    /// @throw DhcpConfigError in case of issues found
    void
    sanityChecks(const SrvConfigPtr& cfg, const ConstElementPtr& global) {

        /// Shared network sanity checks
        const SharedNetwork4Collection* networks = cfg->getCfgSharedNetworks4()->getAll();
        if (networks) {
            sharedNetworksSanityChecks(*networks, global->get("shared-networks"));
        }
    }

    /// @brief Sanity checks for shared networks
    ///
    /// This method verifies if there are no issues with shared networks.
    /// @param networks pointer to shared networks being checked
    /// @param json shared-networks element
    /// @throw DhcpConfigError if issues are encountered
    void
    sharedNetworksSanityChecks(const SharedNetwork4Collection& networks,
                               ConstElementPtr json) {

        /// @todo: in case of errors, use json to extract line numbers.
        if (!json) {
            // No json? That means that the shared-networks was never specified
            // in the config.
            return;
        }

        // Used for names uniqueness checks.
        std::set<string> names;

        // Let's go through all the networks one by one
        for (auto net = networks.begin(); net != networks.end(); ++net) {
            string txt;

            // Let's check if all subnets have either the same interface
            // or don't have the interface specified at all.
            string iface = (*net)->getIface();
            bool authoritative = (*net)->getAuthoritative();

            const Subnet4Collection* subnets = (*net)->getAllSubnets();
            if (subnets) {
                // For each subnet, add it to a list of regular subnets.
                for (auto subnet = subnets->begin(); subnet != subnets->end(); ++subnet) {
                    if (iface.empty()) {
                        iface = (*subnet)->getIface();
                        continue;
                    }

                    if ((*subnet)->getIface().empty()) {
                        continue;
                    }

                    if ((*subnet)->getIface() != iface) {
                        isc_throw(DhcpConfigError, "Subnet " << (*subnet)->toText()
                                  << " has specified interface " << (*subnet)->getIface()
                                  << ", but earlier subnet in the same shared-network"
                                  << " or the shared-network itself used " << iface);
                    }

                    if ((*subnet)->getAuthoritative() != authoritative) {
                        isc_throw(DhcpConfigError, "Subnet " << (*subnet)->toText()
                                  << " has different authoritative setting "
                                  << (*subnet)->getAuthoritative()
                                  << " than the shared-network itself: "
                                  << authoritative);
                    }

                    // Let's collect the subnets in case we later find out the
                    // subnet doesn't have a mandatory name.
                    txt += (*subnet)->toText() + " ";
                }
            }

            // Next, let's check name of the shared network.
            if ((*net)->getName().empty()) {
                isc_throw(DhcpConfigError, "Shared-network with subnets "
                          << txt << " is missing mandatory 'name' parameter");
            }

            // Is it unique?
            if (names.find((*net)->getName()) != names.end()) {
                isc_throw(DhcpConfigError, "A shared-network with "
                          "name " << (*net)->getName() << " defined twice.");
            }
            names.insert((*net)->getName());

        }
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
    // data elements aren't equal.
    bool sock_changed = (sock_cfg && current_sock_cfg &&
                         !sock_cfg->equals(*current_sock_cfg));

    // If the previous or new socket configuration doesn't exist or
    // the new configuration differs from the old configuration we
    // close the existing socket and open a new socket as appropriate.
    // Note that closing an existing socket means the client will not
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
configureDhcp4Server(Dhcpv4Srv& server, isc::data::ConstElementPtr config_set,
                     bool check_only) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(CONTROL_RESULT_ERROR,
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
        server.discardPackets();
        server.getCBControl()->reset();
    }

    // Revert any runtime option definitions configured so far and not committed.
    LibDHCP::revertRuntimeOptionDefs();
    // Let's set empty container in case a user hasn't specified any configuration
    // for option definitions. This is equivalent to committing empty container.
    LibDHCP::setRuntimeOptionDefs(OptionDefSpaceContainer());

    // Print the list of known backends.
    HostDataSourceFactory::printRegistered();

    // Answer will hold the result.
    ConstElementPtr answer;
    // Rollback informs whether error occurred and original data
    // have to be restored to global storages.
    bool rollback = false;
    // config_pair holds the details of the current parser when iterating over
    // the parsers.  It is declared outside the loops so in case of an error,
    // the name of the failing parser can be retrieved in the "catch" clause.
    ConfigPair config_pair;
    ElementPtr mutable_cfg;
    SrvConfigPtr srv_cfg;
    try {
        // Get the staging configuration
        srv_cfg = CfgMgr::instance().getStagingCfg();

        // Preserve all scalar global parameters
        srv_cfg->extractConfiguredGlobals(config_set);

        // This is a way to convert ConstElementPtr to ElementPtr.
        // We need a config that can be edited, because we will insert
        // default values and will insert derived values as well.
        mutable_cfg = boost::const_pointer_cast<Element>(config_set);

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

        // This parser is used in several places, so it should be available
        // early.
        Dhcp4ConfigParser global_parser;

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

            if (config_pair.first == "dhcp-queue-control") {
                DHCPQueueControlParser parser;
                srv_cfg->setDHCPQueueControl(parser.parse(config_pair.second));
                continue;
            }

            if (config_pair.first == "host-reservation-identifiers") {
                HostReservationIdsParser4 parser;
                parser.parse(config_pair.second);
                continue;
            }

            if (config_pair.first == "interfaces-config") {
                ElementPtr ifaces_cfg =
                    boost::const_pointer_cast<Element>(config_pair.second);
                if (check_only) {
                    // No re-detection in check only mode
                    ifaces_cfg->set("re-detect", Element::create(false));
                }
                IfacesConfigParser parser(AF_INET);
                CfgIfacePtr cfg_iface = srv_cfg->getCfgIface();
                parser.parse(cfg_iface, ifaces_cfg);
                continue;
            }

            if (config_pair.first == "sanity-checks") {
                SanityChecksParser parser;
                parser.parse(*srv_cfg, config_pair.second);
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
                db::DbAccessParser parser;
                std::string access_string;
                parser.parse(access_string, config_pair.second);
                CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                cfg_db_access->setLeaseDbAccessString(access_string);
                continue;
            }

            if (config_pair.first == "hosts-database") {
                db::DbAccessParser parser;
                std::string access_string;
                parser.parse(access_string, config_pair.second);
                CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                cfg_db_access->setHostDbAccessString(access_string);
                continue;
            }

            if (config_pair.first == "hosts-databases") {
                CfgDbAccessPtr cfg_db_access = srv_cfg->getCfgDbAccess();
                db::DbAccessParser parser;
                auto list = config_pair.second->listValue();
                for (auto it : list) {
                    std::string access_string;
                    parser.parse(access_string, it);
                    cfg_db_access->setHostDbAccessString(access_string);
                }
                continue;
            }

            if (config_pair.first == "subnet4") {
                Subnets4ListConfigParser subnets_parser;
                // parse() returns number of subnets parsed. We may log it one day.
                subnets_parser.parse(srv_cfg, config_pair.second);
                continue;
            }

            if (config_pair.first == "shared-networks") {

                /// We need to create instance of SharedNetworks4ListParser
                /// and parse the list of the shared networks into the
                /// CfgSharedNetworks4 object. One additional step is then to
                /// add subnets from the CfgSharedNetworks4 into CfgSubnets4
                /// as well.
                SharedNetworks4ListParser parser;
                CfgSharedNetworks4Ptr cfg = srv_cfg->getCfgSharedNetworks4();
                parser.parse(cfg, config_pair.second);

                // We also need to put the subnets it contains into normal
                // subnets list.
                global_parser.copySubnets4(srv_cfg->getCfgSubnets4(), cfg);
                continue;
            }

            if (config_pair.first == "reservations") {
                HostCollection hosts;
                HostReservationsListParser<HostReservationParser4> parser;
                parser.parse(SUBNET_ID_GLOBAL, config_pair.second, hosts);
                for (auto h = hosts.begin(); h != hosts.end(); ++h) {
                    srv_cfg->getCfgHosts()->add(*h);
                }

                continue;
            }

            if (config_pair.first == "config-control") {
                ConfigControlParser parser;
                ConfigControlInfoPtr config_ctl_info = parser.parse(config_pair.second);
                CfgMgr::instance().getStagingCfg()->setConfigControlInfo(config_ctl_info);
                continue;
            }

            // Timers are not used in the global scope. Their values are derived
            // to specific subnets (see SimpleParser6::deriveParameters).
            // decline-probation-period, dhcp4o6-port, echo-client-id,
            // user-context are handled in global_parser.parse() which
            // sets global parameters.
            // match-client-id and authoritative are derived to subnet scope
            // level.
            if ( (config_pair.first == "renew-timer") ||
                 (config_pair.first == "rebind-timer") ||
                 (config_pair.first == "valid-lifetime") ||
                 (config_pair.first == "decline-probation-period") ||
                 (config_pair.first == "dhcp4o6-port") ||
                 (config_pair.first == "echo-client-id") ||
                 (config_pair.first == "user-context") ||
                 (config_pair.first == "match-client-id") ||
                 (config_pair.first == "authoritative") ||
                 (config_pair.first == "next-server") ||
                 (config_pair.first == "server-hostname") ||
                 (config_pair.first == "boot-file-name") ||
                 (config_pair.first == "server-tag") ||
                 (config_pair.first == "reservation-mode") ||
                 (config_pair.first == "calculate-tee-times") ||
                 (config_pair.first == "t1-percent") ||
                 (config_pair.first == "t2-percent")) {
                continue;
            }

            // If we got here, no code handled this parameter, so we bail out.
            isc_throw(DhcpConfigError,
                      "unsupported global configuration parameter: " << config_pair.first
                      << " (" << config_pair.second->getPosition() << ")");
        }

        // Apply global options in the staging config.
        global_parser.parse(srv_cfg, mutable_cfg);

        // This method conducts final sanity checks and tweaks. In particular,
        // it checks that there is no conflict between plain subnets and those
        // defined as part of shared networks.
        global_parser.sanityChecks(srv_cfg, mutable_cfg);

    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_FAIL)
                  .arg(config_pair.first).arg(ex.what());
        answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());

        // An error occurred, so make sure that we restore original data.
        rollback = true;

    } catch (...) {
        // For things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_EXCEPTION).arg(config_pair.first);
        answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
                                           " processing error");

        // An error occurred, so make sure that we restore original data.
        rollback = true;
    }

    if (check_only) {
        rollback = true;
        if (!answer) {
            answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS,
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

            // If there are config backends, fetch and merge into staging config
            server.getCBControl()->databaseConfigFetch(srv_cfg,
                                                       CBControlDHCPv4::FetchMode::FETCH_ALL);
        }
        catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
            rollback = true;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
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
    answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS, "Configuration successful.");
    return (answer);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
