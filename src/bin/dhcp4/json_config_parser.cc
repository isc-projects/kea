// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/http_command_mgr.h>
#include <database/dbaccess_parser.h>
#include <database/backend_selector.h>
#include <database/server_selector.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <dhcpsrv/cfg_multi_threading.h>
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
#include <dhcpsrv/parsers/multi_threading_config_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/dhcp_queue_control_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/shared_networks_list_parser.h>
#include <dhcpsrv/parsers/sanity_checks_parser.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/timer_mgr.h>
#include <hooks/hooks_manager.h>
#include <hooks/hooks_parser.h>
#include <process/config_ctl_parser.h>
#include <util/encode/encode.h>
#include <util/multi_threading_mgr.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <netinet/in.h>
#include <vector>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::util;
using namespace isc;
using namespace std;

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

    /// @brief Sets global parameters before other parameters are parsed.
    ///
    /// This method sets selected global parameters before other parameters
    /// are parsed. This is important when the behavior of the parsers
    /// run later depends on these global parameters.
    ///
    /// Currently this method sets the following global parameters:
    /// - ip-reservations-unique
    ///
    /// @param global global configuration scope
    /// @param cfg Server configuration (parsed parameters will be stored here)
    void parseEarly(const SrvConfigPtr& cfg, const ConstElementPtr& global) {
        // Set ip-reservations-unique flag.
        bool ip_reservations_unique = getBoolean(global, "ip-reservations-unique");
        cfg->setIPReservationsUnique(ip_reservations_unique);
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
        for (auto const& net : *networks) {

            // For each network go through all the subnets in it.
            const Subnet4SimpleCollection* subnets = net->getAllSubnets();
            if (!subnets) {
                // Shared network without subnets it weird, but we decided to
                // accept such configurations.
                continue;
            }

            // For each subnet, add it to a list of regular subnets.
            for (auto const& subnet : *subnets) {
                dest->add(subnet);
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

        /// Global lifetime sanity checks
        cfg->sanityChecksLifetime("valid-lifetime");

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
        for (auto const& net : networks) {
            string txt;

            // Let's check if all subnets have either the same interface
            // or don't have the interface specified at all.
            bool authoritative = net->getAuthoritative();
            string iface = net->getIface();

            const Subnet4SimpleCollection* subnets = net->getAllSubnets();
            if (subnets) {
                // For each subnet, add it to a list of regular subnets.
                for (auto const& subnet : *subnets) {
                    if (subnet->getAuthoritative() != authoritative) {
                        isc_throw(DhcpConfigError, "Subnet " << boolalpha
                                  << subnet->toText()
                                  << " has different authoritative setting "
                                  << subnet->getAuthoritative()
                                  << " than the shared-network itself: "
                                  << authoritative);
                    }

                    if (iface.empty()) {
                        iface = subnet->getIface();
                        continue;
                    }

                    if (subnet->getIface().empty()) {
                        continue;
                    }

                    if (subnet->getIface() != iface) {
                        isc_throw(DhcpConfigError, "Subnet " << subnet->toText()
                                  << " has specified interface " << subnet->getIface()
                                  << ", but earlier subnet in the same shared-network"
                                  << " or the shared-network itself used " << iface);
                    }

                    // Let's collect the subnets in case we later find out the
                    // subnet doesn't have a mandatory name.
                    txt += subnet->toText() + " ";
                }
            }

            // Next, let's check name of the shared network.
            if (net->getName().empty()) {
                isc_throw(DhcpConfigError, "Shared-network with subnets "
                          << txt << " is missing mandatory 'name' parameter");
            }

            // Is it unique?
            if (names.find(net->getName()) != names.end()) {
                isc_throw(DhcpConfigError, "A shared-network with "
                          "name " << net->getName() << " defined twice.");
            }
            names.insert(net->getName());

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
        CommandMgr::instance().closeCommandSocket();

        if (sock_cfg) {
            // This will create a control socket and install the external
            // socket in IfaceMgr. That socket will be monitored when
            // Dhcp4Srv::receivePacket() calls IfaceMgr::receive4() and
            // callback in CommandMgr will be called, if necessary.
            CommandMgr::instance().openCommandSocket(sock_cfg);
        }
    }

    // HTTP control socket is simpler: just (re)configure it.

    // Get new config.
    HttpCommandConfigPtr http_config =
        CfgMgr::instance().getStagingCfg()->getHttpControlSocketInfo();
    HttpCommandMgr::instance().configure(http_config);
}

/// @brief Process a DHCPv4 confguration and return an answer stating if the
/// configuration is valid, or specifying details about the error otherwise.
///
/// @param config_set the configuration being processed
isc::data::ConstElementPtr
processDhcp4Config(isc::data::ConstElementPtr config_set) {
    // Revert any runtime option definitions configured so far and not committed.
    LibDHCP::revertRuntimeOptionDefs();
    // Let's set empty container in case a user hasn't specified any configuration
    // for option definitions. This is equivalent to committing empty container.
    LibDHCP::setRuntimeOptionDefs(OptionDefSpaceContainer());

    // Print the list of known backends.
    HostDataSourceFactory::printRegistered();

    // Answer will hold the result.
    ConstElementPtr answer;

    // Global parameter name in case of an error.
    string parameter_name;
    ElementPtr mutable_cfg;
    SrvConfigPtr srv_config;
    try {
        // Get the staging configuration.
        srv_config = CfgMgr::instance().getStagingCfg();

        // This is a way to convert ConstElementPtr to ElementPtr.
        // We need a config that can be edited, because we will insert
        // default values and will insert derived values as well.
        mutable_cfg = boost::const_pointer_cast<Element>(config_set);

        // Set all default values if not specified by the user.
        SimpleParser4::setAllDefaults(mutable_cfg);

        // And now derive (inherit) global parameters to subnets, if not specified.
        SimpleParser4::deriveParameters(mutable_cfg);

        // In principle we could have the following code structured as a series
        // of long if else if clauses. That would give a marginal performance
        // boost, but would make the code less readable. We had serious issues
        // with the parser code debugability, so I decided to keep it as a
        // series of independent ifs.

        // This parser is used in several places.
        Dhcp4ConfigParser global_parser;

        // Apply global options in the staging config, e.g. ip-reservations-unique
        global_parser.parseEarly(srv_config, mutable_cfg);

        // We need definitions first
        ConstElementPtr option_defs = mutable_cfg->get("option-def");
        if (option_defs) {
            parameter_name = "option-def";
            OptionDefListParser parser(AF_INET);
            CfgOptionDefPtr cfg_option_def = srv_config->getCfgOptionDef();
            parser.parse(cfg_option_def, option_defs);
        }

        ConstElementPtr option_datas = mutable_cfg->get("option-data");
        if (option_datas) {
            parameter_name = "option-data";
            OptionDataListParser parser(AF_INET);
            CfgOptionPtr cfg_option = srv_config->getCfgOption();
            parser.parse(cfg_option, option_datas);
        }

        ConstElementPtr control_socket = mutable_cfg->get("control-socket");
        if (control_socket) {
            mutable_cfg->remove("control-socket");
            ElementPtr l = Element::createList();
            l->add(UserContext::toElement(control_socket));
            mutable_cfg->set("control-sockets", l);
        }

        ConstElementPtr control_sockets = mutable_cfg->get("control-sockets");
        if (control_sockets) {
            parameter_name = "control-sockets";
            ControlSocketsParser parser;
            parser.parse(*srv_config, control_sockets);
        }

        ConstElementPtr multi_threading = mutable_cfg->get("multi-threading");
        if (multi_threading) {
            parameter_name = "multi-threading";
            MultiThreadingConfigParser parser;
            parser.parse(*srv_config, multi_threading);
        }

        bool multi_threading_enabled = true;
        uint32_t thread_count = 0;
        uint32_t queue_size = 0;
        CfgMultiThreading::extract(CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading(),
                                   multi_threading_enabled, thread_count, queue_size);

        /// depends on "multi-threading" being enabled, so it must come after.
        ConstElementPtr queue_control = mutable_cfg->get("dhcp-queue-control");
        if (queue_control) {
            parameter_name = "dhcp-queue-control";
            DHCPQueueControlParser parser;
            srv_config->setDHCPQueueControl(parser.parse(queue_control, multi_threading_enabled));
        }

        /// depends on "multi-threading" being enabled, so it must come after.
        ConstElementPtr reservations_lookup_first = mutable_cfg->get("reservations-lookup-first");
        if (reservations_lookup_first) {
            parameter_name = "reservations-lookup-first";
            if (multi_threading_enabled) {
                LOG_WARN(dhcp4_logger, DHCP4_RESERVATIONS_LOOKUP_FIRST_ENABLED);
            }
            srv_config->setReservationsLookupFirst(reservations_lookup_first->boolValue());
        }

        ConstElementPtr hr_identifiers =
            mutable_cfg->get("host-reservation-identifiers");
        if (hr_identifiers) {
            parameter_name = "host-reservation-identifiers";
            HostReservationIdsParser4 parser;
            parser.parse(hr_identifiers);
        }

        ConstElementPtr sanity_checks = mutable_cfg->get("sanity-checks");
        if (sanity_checks) {
            parameter_name = "sanity-checks";
            SanityChecksParser parser;
            parser.parse(*srv_config, sanity_checks);
        }

        ConstElementPtr expiration_cfg =
            mutable_cfg->get("expired-leases-processing");
        if (expiration_cfg) {
            parameter_name = "expired-leases-processing";
            ExpirationConfigParser parser;
            parser.parse(expiration_cfg, CfgMgr::instance().getStagingCfg()->getCfgExpiration());
        }

        // The hooks-libraries configuration must be parsed after parsing
        // multi-threading configuration so that libraries are checked
        // for multi-threading compatibility.
        ConstElementPtr hooks_libraries = mutable_cfg->get("hooks-libraries");
        if (hooks_libraries) {
            parameter_name = "hooks-libraries";
            HooksLibrariesParser hooks_parser;
            HooksConfig& libraries = srv_config->getHooksConfig();
            hooks_parser.parse(libraries, hooks_libraries);
            libraries.verifyLibraries(hooks_libraries->getPosition(),
                                      multi_threading_enabled);
        }

        // D2 client configuration.
        D2ClientConfigPtr d2_client_cfg;

        // Legacy DhcpConfigParser stuff below.
        ConstElementPtr dhcp_ddns = mutable_cfg->get("dhcp-ddns");
        if (dhcp_ddns) {
            parameter_name = "dhcp-ddns";
            // Apply defaults
            D2ClientConfigParser::setAllDefaults(dhcp_ddns);
            D2ClientConfigParser parser;
            d2_client_cfg = parser.parse(dhcp_ddns);
        }

        ConstElementPtr client_classes = mutable_cfg->get("client-classes");
        if (client_classes) {
            parameter_name = "client-classes";
            ClientClassDefListParser parser;
            ClientClassDictionaryPtr dictionary =
                parser.parse(client_classes, AF_INET);
            srv_config->setClientClassDictionary(dictionary);
        }

        // Please move at the end when migration will be finished.
        ConstElementPtr lease_database = mutable_cfg->get("lease-database");
        if (lease_database) {
            parameter_name = "lease-database";
            db::DbAccessParser parser;
            std::string access_string;
            parser.parse(access_string, lease_database);
            CfgDbAccessPtr cfg_db_access = srv_config->getCfgDbAccess();
            cfg_db_access->setLeaseDbAccessString(access_string);
        }

        ConstElementPtr hosts_database = mutable_cfg->get("hosts-database");
        if (hosts_database) {
            parameter_name = "hosts-database";
            db::DbAccessParser parser;
            std::string access_string;
            parser.parse(access_string, hosts_database);
            CfgDbAccessPtr cfg_db_access = srv_config->getCfgDbAccess();
            cfg_db_access->setHostDbAccessString(access_string);
        }

        ConstElementPtr hosts_databases = mutable_cfg->get("hosts-databases");
        if (hosts_databases) {
            parameter_name = "hosts-databases";
            CfgDbAccessPtr cfg_db_access = srv_config->getCfgDbAccess();
            for (auto const& it : hosts_databases->listValue()) {
                db::DbAccessParser parser;
                std::string access_string;
                parser.parse(access_string, it);
                cfg_db_access->setHostDbAccessString(access_string);
            }
        }

        // Keep relative orders of shared networks and subnets.
        ConstElementPtr shared_networks = mutable_cfg->get("shared-networks");
        if (shared_networks) {
            parameter_name = "shared-networks";
            /// We need to create instance of SharedNetworks4ListParser
            /// and parse the list of the shared networks into the
            /// CfgSharedNetworks4 object. One additional step is then to
            /// add subnets from the CfgSharedNetworks4 into CfgSubnets4
            /// as well.
            SharedNetworks4ListParser parser;
            CfgSharedNetworks4Ptr cfg = srv_config->getCfgSharedNetworks4();
            parser.parse(cfg, shared_networks);

            // We also need to put the subnets it contains into normal
            // subnets list.
            global_parser.copySubnets4(srv_config->getCfgSubnets4(), cfg);
        }

        ConstElementPtr subnet4 = mutable_cfg->get("subnet4");
        if (subnet4) {
            parameter_name = "subnet4";
            Subnets4ListConfigParser subnets_parser;
            // parse() returns number of subnets parsed. We may log it one day.
            subnets_parser.parse(srv_config, subnet4);
        }

        ConstElementPtr reservations = mutable_cfg->get("reservations");
        if (reservations) {
            parameter_name = "reservations";
            HostCollection hosts;
            HostReservationsListParser<HostReservationParser4> parser;
            parser.parse(SUBNET_ID_GLOBAL, reservations, hosts);
            for (auto const& h : hosts) {
                srv_config->getCfgHosts()->add(h);
            }
        }

        ConstElementPtr config_control = mutable_cfg->get("config-control");
        if (config_control) {
            parameter_name = "config-control";
            ConfigControlParser parser;
            ConfigControlInfoPtr config_ctl_info = parser.parse(config_control);
            CfgMgr::instance().getStagingCfg()->setConfigControlInfo(config_ctl_info);
        }

        ConstElementPtr compatibility = mutable_cfg->get("compatibility");
        if (compatibility) {
            CompatibilityParser parser;
            parser.parse(compatibility, *CfgMgr::instance().getStagingCfg());
        }

        // Make parsers grouping.
        const std::map<std::string, ConstElementPtr>& values_map =
            mutable_cfg->mapValue();

        for (auto const& config_pair : values_map) {
            parameter_name = config_pair.first;

            // These are converted to SimpleParser and are handled already above.
            if ((config_pair.first == "option-def") ||
                (config_pair.first == "option-data") ||
                (config_pair.first == "control-socket") ||
                (config_pair.first == "control-sockets") ||
                (config_pair.first == "multi-threading") ||
                (config_pair.first == "dhcp-queue-control") ||
                (config_pair.first == "host-reservation-identifiers") ||
                (config_pair.first == "interfaces-config") ||
                (config_pair.first == "sanity-checks") ||
                (config_pair.first == "expired-leases-processing") ||
                (config_pair.first == "hooks-libraries") ||
                (config_pair.first == "dhcp-ddns") ||
                (config_pair.first == "client-classes") ||
                (config_pair.first == "lease-database") ||
                (config_pair.first == "hosts-database") ||
                (config_pair.first == "hosts-databases") ||
                (config_pair.first == "subnet4") ||
                (config_pair.first == "shared-networks") ||
                (config_pair.first == "reservations") ||
                (config_pair.first == "config-control") ||
                (config_pair.first == "loggers") ||
                (config_pair.first == "compatibility")) {
                continue;
            }

            // As of Kea 1.6.0 we have two ways of inheriting the global parameters.
            // The old method is used in JSON configuration parsers when the global
            // parameters are derived into the subnets and shared networks and are
            // being treated as explicitly specified. The new way used by the config
            // backend is the dynamic inheritance whereby each subnet and shared
            // network uses a callback function to return global parameter if it
            // is not specified at lower level. This callback uses configured globals.
            // We deliberately include both default and explicitly specified globals
            // so as the callback can access the appropriate global values regardless
            // whether they are set to a default or other value.
            if ( (config_pair.first == "renew-timer") ||
                 (config_pair.first == "rebind-timer") ||
                 (config_pair.first == "valid-lifetime") ||
                 (config_pair.first == "min-valid-lifetime") ||
                 (config_pair.first == "max-valid-lifetime") ||
                 (config_pair.first == "decline-probation-period") ||
                 (config_pair.first == "dhcp4o6-port") ||
                 (config_pair.first == "echo-client-id") ||
                 (config_pair.first == "match-client-id") ||
                 (config_pair.first == "authoritative") ||
                 (config_pair.first == "next-server") ||
                 (config_pair.first == "server-hostname") ||
                 (config_pair.first == "boot-file-name") ||
                 (config_pair.first == "server-tag") ||
                 (config_pair.first == "reservations-global") ||
                 (config_pair.first == "reservations-in-subnet") ||
                 (config_pair.first == "reservations-out-of-pool") ||
                 (config_pair.first == "calculate-tee-times") ||
                 (config_pair.first == "t1-percent") ||
                 (config_pair.first == "t2-percent") ||
                 (config_pair.first == "cache-threshold") ||
                 (config_pair.first == "cache-max-age") ||
                 (config_pair.first == "hostname-char-set") ||
                 (config_pair.first == "hostname-char-replacement") ||
                 (config_pair.first == "ddns-send-updates") ||
                 (config_pair.first == "ddns-override-no-update") ||
                 (config_pair.first == "ddns-override-client-update") ||
                 (config_pair.first == "ddns-replace-client-name") ||
                 (config_pair.first == "ddns-generated-prefix") ||
                 (config_pair.first == "ddns-qualifying-suffix") ||
                 (config_pair.first == "ddns-update-on-renew") ||
                 (config_pair.first == "ddns-use-conflict-resolution") ||
                 (config_pair.first == "ddns-conflict-resolution-mode") ||
                 (config_pair.first == "ddns-ttl-percent") ||
                 (config_pair.first == "store-extended-info") ||
                 (config_pair.first == "statistic-default-sample-count") ||
                 (config_pair.first == "statistic-default-sample-age") ||
                 (config_pair.first == "early-global-reservations-lookup") ||
                 (config_pair.first == "ip-reservations-unique") ||
                 (config_pair.first == "reservations-lookup-first") ||
                 (config_pair.first == "parked-packet-limit") ||
                 (config_pair.first == "allocator") ||
                 (config_pair.first == "offer-lifetime") ||
                 (config_pair.first == "stash-agent-options") ) {
                CfgMgr::instance().getStagingCfg()->addConfiguredGlobal(config_pair.first,
                                                                        config_pair.second);
                continue;
            }

            // Nothing to configure for the user-context.
            if (config_pair.first == "user-context") {
                continue;
            }

            // If we got here, no code handled this parameter, so we bail out.
            isc_throw(DhcpConfigError,
                      "unsupported global configuration parameter: " << config_pair.first
                      << " (" << config_pair.second->getPosition() << ")");
        }

        // Reset parameter name.
        parameter_name = "<post parsing>";

        // Apply global options in the staging config.
        global_parser.parse(srv_config, mutable_cfg);

        // This method conducts final sanity checks and tweaks. In particular,
        // it checks that there is no conflict between plain subnets and those
        // defined as part of shared networks.
        global_parser.sanityChecks(srv_config, mutable_cfg);

        // Validate D2 client configuration.
        if (!d2_client_cfg) {
            d2_client_cfg.reset(new D2ClientConfig());
        }
        d2_client_cfg->validateContents();
        srv_config->setD2ClientConfig(d2_client_cfg);
    } catch (const isc::Exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_FAIL)
                  .arg(parameter_name).arg(ex.what());
        answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
    } catch (...) {
        // For things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp4_logger, DHCP4_PARSER_EXCEPTION).arg(parameter_name);
        answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration "
                                           "processing error");
    }

    if (!answer) {
        answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS, "Configuration seems sane. "
                                           "Control-socket, hook-libraries, and D2 configuration "
                                           "were sanity checked, but not applied.");
    }

    return (answer);
}

isc::data::ConstElementPtr
configureDhcp4Server(Dhcpv4Srv& server, isc::data::ConstElementPtr config_set,
                     bool check_only, bool extra_checks) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(CONTROL_RESULT_ERROR,
                                                           "Can't parse NULL config");
        return (answer);
    }

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_START)
        .arg(server.redactConfig(config_set)->str());

    auto answer = processDhcp4Config(config_set);

    int status_code = CONTROL_RESULT_SUCCESS;
    isc::config::parseAnswer(status_code, answer);

    SrvConfigPtr srv_config;

    if (status_code == CONTROL_RESULT_SUCCESS) {
        if (check_only) {
            if (extra_checks) {
                // Re-open lease and host database with new parameters.
                try {
                    // Get the staging configuration.
                    srv_config = CfgMgr::instance().getStagingCfg();

                    CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
                    string params = "universe=4 persist=false";
                    cfg_db->setAppendedParameters(params);
                    cfg_db->createManagers();
                } catch (const std::exception& ex) {
                    answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
                    status_code = CONTROL_RESULT_ERROR;
                }

                if (status_code == CONTROL_RESULT_SUCCESS) {
                    std::ostringstream err;
                    // Configure DHCP packet queueing
                    try {
                        data::ConstElementPtr qc;
                        qc = CfgMgr::instance().getStagingCfg()->getDHCPQueueControl();
                        if (IfaceMgr::instance().configureDHCPPacketQueue(AF_INET, qc)) {
                            LOG_INFO(dhcp4_logger, DHCP4_CONFIG_PACKET_QUEUE)
                                     .arg(IfaceMgr::instance().getPacketQueue4()->getInfoStr());
                        }

                    } catch (const std::exception& ex) {
                        err << "Error setting packet queue controls after server reconfiguration: "
                            << ex.what();
                        answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str());
                        status_code = CONTROL_RESULT_ERROR;
                    }
                }
            }
        } else {
            // disable multi-threading (it will be applied by new configuration)
            // this must be done in order to properly handle MT to ST transition
            // when 'multi-threading' structure is missing from new config and
            // to properly drop any task items stored in the thread pool which
            // might reference some handles to loaded hooks, preventing them
            // from being unloaded.
            MultiThreadingMgr::instance().apply(false, 0, 0);

            // Close DHCP sockets and remove any existing timers.
            IfaceMgr::instance().closeSockets();
            TimerMgr::instance()->unregisterTimers();
            server.discardPackets();
            server.getCBControl()->reset();
        }

        if (status_code == CONTROL_RESULT_SUCCESS) {
            string parameter_name;
            ElementPtr mutable_cfg;
            try {
                // Get the staging configuration.
                srv_config = CfgMgr::instance().getStagingCfg();

                // This is a way to convert ConstElementPtr to ElementPtr.
                // We need a config that can be edited, because we will insert
                // default values and will insert derived values as well.
                mutable_cfg = boost::const_pointer_cast<Element>(config_set);

                ConstElementPtr ifaces_config = mutable_cfg->get("interfaces-config");
                if (ifaces_config) {
                    parameter_name = "interfaces-config";
                    IfacesConfigParser parser(AF_INET, check_only);
                    CfgIfacePtr cfg_iface = srv_config->getCfgIface();
                    cfg_iface->reset();
                    parser.parse(cfg_iface, ifaces_config);
                }
            } catch (const isc::Exception& ex) {
                LOG_ERROR(dhcp4_logger, DHCP4_PARSER_FAIL)
                          .arg(parameter_name).arg(ex.what());
                answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
                status_code = CONTROL_RESULT_ERROR;
            } catch (...) {
                // For things like bad_cast in boost::lexical_cast
                LOG_ERROR(dhcp4_logger, DHCP4_PARSER_EXCEPTION).arg(parameter_name);
                answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
                                                   " processing error");
                status_code = CONTROL_RESULT_ERROR;
            }
        }
    }

    // So far so good, there was no parsing error so let's commit the
    // configuration. This will add created subnets and option values into
    // the server's configuration.
    // This operation should be exception safe but let's make sure.
    if (status_code == CONTROL_RESULT_SUCCESS && !check_only) {
        try {

            // Setup the command channel.
            configureCommandChannel();
        } catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
            status_code = CONTROL_RESULT_ERROR;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
                                               " parsing error");
            status_code = CONTROL_RESULT_ERROR;
        }
    }

    if (status_code == CONTROL_RESULT_SUCCESS && (!check_only || extra_checks)) {
        try {
            // No need to commit interface names as this is handled by the
            // CfgMgr::commit() function.

            // Apply the staged D2ClientConfig, used to be done by parser commit
            D2ClientConfigPtr cfg;
            cfg = CfgMgr::instance().getStagingCfg()->getD2ClientConfig();
            CfgMgr::instance().setD2ClientConfig(cfg);
        } catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
            status_code = CONTROL_RESULT_ERROR;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
                                               " parsing error");
            status_code = CONTROL_RESULT_ERROR;
        }
    }

    if (status_code == CONTROL_RESULT_SUCCESS && (!check_only || extra_checks)) {
        try {
            // This occurs last as if it succeeds, there is no easy way to
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            HooksManager::prepareUnloadLibraries();
            static_cast<void>(HooksManager::unloadLibraries());
            IOServiceMgr::instance().clearIOServices();
            const HooksConfig& libraries =
                CfgMgr::instance().getStagingCfg()->getHooksConfig();
            bool multi_threading_enabled = true;
            uint32_t thread_count = 0;
            uint32_t queue_size = 0;
            CfgMultiThreading::extract(CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading(),
                                       multi_threading_enabled, thread_count, queue_size);
            libraries.loadLibraries(multi_threading_enabled);
        } catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());
            status_code = CONTROL_RESULT_ERROR;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
                                               " parsing error");
            status_code = CONTROL_RESULT_ERROR;
        }
    }

    // Moved from the commit block to add the config backend indication.
    if (status_code == CONTROL_RESULT_SUCCESS && (!check_only || extra_checks)) {
        try {
            // If there are config backends, fetch and merge into staging config
            server.getCBControl()->databaseConfigFetch(srv_config,
                                                       CBControlDHCPv4::FetchMode::FETCH_ALL);
        } catch (const isc::Exception& ex) {
            std::ostringstream err;
            err << "during update from config backend database: " << ex.what();
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(err.str());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str());
            status_code = CONTROL_RESULT_ERROR;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            std::ostringstream err;
            err << "during update from config backend database: "
                << "undefined configuration parsing error";
            LOG_ERROR(dhcp4_logger, DHCP4_PARSER_COMMIT_FAIL).arg(err.str());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str());
            status_code = CONTROL_RESULT_ERROR;
        }
    }

    // Rollback changes as the configuration parsing failed.
    if (check_only || status_code != CONTROL_RESULT_SUCCESS) {
        // Revert to original configuration of runtime option definitions
        // in the libdhcp++.
        LibDHCP::revertRuntimeOptionDefs();

        if (status_code == CONTROL_RESULT_SUCCESS && extra_checks) {
            auto notify_libraries = ControlledDhcpv4Srv::finishConfigHookLibraries(config_set);
            if (notify_libraries) {
                return (notify_libraries);
            }

            /// Let postponed hook initializations run.
            try {
                // Handle events registered by hooks using external IOService objects.
                IOServiceMgr::instance().pollIOServices();
            } catch (const std::exception& ex) {
                std::ostringstream err;
                err << "Error initializing hooks: "
                    << ex.what();
                return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
            }
        }

        return (answer);
    }

    LOG_INFO(dhcp4_logger, DHCP4_CONFIG_COMPLETE)
        .arg(CfgMgr::instance().getStagingCfg()->
             getConfigSummary(SrvConfig::CFGSEL_ALL4));

    // Also calculate SHA256 hash of the config that was just set and
    // append it to the response.
    ConstElementPtr config = CfgMgr::instance().getStagingCfg()->toElement();
    string hash = BaseCommandMgr::getHash(config);
    ElementPtr hash_map = Element::createMap();
    hash_map->set("hash", Element::create(hash));

    // Everything was fine. Configuration is successful.
    answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS, "Configuration successful.", hash_map);
    return (answer);
}

}  // namespace dhcp
}  // namespace isc
