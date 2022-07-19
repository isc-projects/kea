// Copyright (C) 2012-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <database/dbaccess_parser.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cb_ctl_dhcp4.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/db_type.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/duid_config_parser.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/host_reservations_list_parser.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <dhcpsrv/parsers/multi_threading_config_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/dhcp_queue_control_parser.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <dhcpsrv/parsers/shared_networks_list_parser.h>
#include <dhcpsrv/parsers/sanity_checks_parser.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/timer_mgr.h>
#include <hooks/hooks_manager.h>
#include <hooks/hooks_parser.h>
#include <log/logger_support.h>
#include <process/config_ctl_parser.h>
#include <util/encode/hex.h>
#include <util/multi_threading_mgr.h>
#include <util/strutil.h>
#include <util/triplet.h>

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
using namespace isc::process;
using namespace isc::config;
using namespace isc::util;

namespace {

/// @brief Checks if specified directory exists.
///
/// @param dir_path Path to a directory.
/// @throw BadValue If the directory does not exist or is not a directory.
void dirExists(const string& dir_path) {
    struct stat statbuf;
    if (stat(dir_path.c_str(), &statbuf) < 0) {
        isc_throw(BadValue, "Bad directory '" << dir_path
                  << "': " << strerror(errno));
    }
    if ((statbuf.st_mode & S_IFMT) != S_IFDIR) {
        isc_throw(BadValue, "'" << dir_path << "' is not a directory");
    }
}

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
    void parse(const SrvConfigPtr& cfg, const isc::data::ConstElementPtr& value) {
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

/// @brief Parser that takes care of global DHCPv6 parameters and utility
///        functions that work on global level.
///
/// This class is a collection of utility method that either handle
/// global parameters (see @ref parse), or conducts operations on
/// global level (see @ref sanityChecks and @ref copySubnets6).
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
    /// - data-directory
    /// - decline-probation-period
    /// - dhcp4o6-port
    /// - user-context
    ///
    /// @throw DhcpConfigError if parameters are missing or
    /// or having incorrect values.
    void parse(const SrvConfigPtr& cfg, const ConstElementPtr& global) {

        // Set the data directory for server id file.
        if (global->contains("data-directory")) {
            CfgMgr::instance().setDataDir(getString(global, "data-directory"),
                                          false);
        }

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
    /// @param dest pointer to cfg subnets6 (copy to here)
    /// @throw BadValue if any pointer is missing
    /// @throw DhcpConfigError if there are duplicates (or other subnet defects)
    void
    copySubnets6(const CfgSubnets6Ptr& dest, const CfgSharedNetworks6Ptr& from) {

        if (!dest || !from) {
            isc_throw(BadValue, "Unable to copy subnets: at least one pointer is null");
        }

        const SharedNetwork6Collection* networks = from->getAll();
        if (!networks) {
            // Nothing to copy. Technically, it should return a pointer to empty
            // container, but let's handle null pointer as well.
            return;
        }

        // Let's go through all the networks one by one
        for (auto net = networks->begin(); net != networks->end(); ++net) {

            // For each network go through all the subnets in it.
            const Subnet6SimpleCollection* subnets = (*net)->getAllSubnets();
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

        /// Global lifetime sanity checks
        cfg->sanityChecksLifetime("preferred-lifetime");
        cfg->sanityChecksLifetime("valid-lifetime");

        /// Shared network sanity checks
        const SharedNetwork6Collection* networks = cfg->getCfgSharedNetworks6()->getAll();
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
    sharedNetworksSanityChecks(const SharedNetwork6Collection& networks,
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

            const Subnet6SimpleCollection* subnets = (*net)->getAllSubnets();
            if (subnets) {

                bool rapid_commit = false;

                // For each subnet, add it to a list of regular subnets.
                for (auto subnet = subnets->begin(); subnet != subnets->end(); ++subnet) {

                    // Rapid commit must either be enabled or disabled in all subnets
                    // in the shared network.
                    if (subnet == subnets->begin()) {
                        // If this is the first subnet, remember the value.
                        rapid_commit = (*subnet)->getRapidCommit();
                    } else {
                        // Ok, this is the second or following subnets. The value
                        // must match what was set in the first subnet.
                        if (rapid_commit != (*subnet)->getRapidCommit()) {
                            isc_throw(DhcpConfigError, "All subnets in a shared network "
                                      "must have the same rapid-commit value. Subnet "
                                      << (*subnet)->toText()
                                      << " has specified rapid-commit "
                                      << ( (*subnet)->getRapidCommit() ? "true" : "false")
                                      << ", but earlier subnet in the same shared-network"
                                      << " or the shared-network itself used rapid-commit "
                                      << (rapid_commit ? "true" : "false"));
                        }
                    }

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
configureDhcp6Server(Dhcpv6Srv& server, isc::data::ConstElementPtr config_set,
                     bool check_only) {
    if (!config_set) {
        ConstElementPtr answer = isc::config::createAnswer(CONTROL_RESULT_ERROR,
                                 string("Can't parse NULL config"));
        return (answer);
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_COMMAND, DHCP6_CONFIG_START)
        .arg(server.redactConfig(config_set)->str());

    // Before starting any subnet operations, let's reset the subnet-id counter,
    // so newly recreated configuration starts with first subnet-id equal 1.
    Subnet::resetSubnetID();

    // Close DHCP sockets and remove any existing timers.
    if (!check_only) {
        IfaceMgr::instance().closeSockets();
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

        // Relocate dhcp-ddns parameters that have moved to global scope.
        // Rule is that a global value overrides the dhcp-ddns value, so
        // we need to do this before we apply global defaults.
        // Note this is done for backward compatibility.
        srv_config->moveDdnsParams(mutable_cfg);

        // Move from reservation mode to new reservations flags.
        // @todo add warning
        BaseNetworkParser::moveReservationMode(mutable_cfg);

        // Set all default values if not specified by the user.
        SimpleParser6::setAllDefaults(mutable_cfg);

        // And now derive (inherit) global parameters to subnets, if not specified.
        SimpleParser6::deriveParameters(mutable_cfg);

        // In principle we could have the following code structured as a series
        // of long if else if clauses. That would give a marginal performance
        // boost, but would make the code less readable. We had serious issues
        // with the parser code debugability, so I decided to keep it as a
        // series of independent ifs.

        // This parser is used in several places.
        Dhcp6ConfigParser global_parser;

        // Apply global options in the staging config, e.g. ip-reservations-unique
        global_parser.parseEarly(srv_config, mutable_cfg);

        // Specific check for this global parameter.
        ConstElementPtr data_directory = mutable_cfg->get("data-directory");
        if (data_directory) {
            parameter_name = "data-directory";
            dirExists(data_directory->stringValue());
        }

        // We need definitions first
        ConstElementPtr option_defs = mutable_cfg->get("option-def");
        if (option_defs) {
            parameter_name = "option-def";
            OptionDefListParser parser(AF_INET6);
            CfgOptionDefPtr cfg_option_def = srv_config->getCfgOptionDef();
            parser.parse(cfg_option_def, option_defs);
        }

        ConstElementPtr option_datas = mutable_cfg->get("option-data");
        if (option_datas) {
            parameter_name = "option-data";
            OptionDataListParser parser(AF_INET6);
            CfgOptionPtr cfg_option = srv_config->getCfgOption();
            parser.parse(cfg_option, option_datas);
        }

        ConstElementPtr mac_sources = mutable_cfg->get("mac-sources");
        if (mac_sources) {
            parameter_name = "mac-sources";
            MACSourcesListConfigParser parser;
            CfgMACSource& mac_source = srv_config->getMACSources();
            parser.parse(mac_source, mac_sources);
        }

        ConstElementPtr control_socket = mutable_cfg->get("control-socket");
        if (control_socket) {
            parameter_name = "control-socket";
            ControlSocketParser parser;
            parser.parse(*srv_config, control_socket);
        }

        ConstElementPtr multi_threading = mutable_cfg->get("multi-threading");
        if (multi_threading) {
            parameter_name = "multi-threading";
            MultiThreadingConfigParser parser;
            parser.parse(*srv_config, multi_threading);
        }

        /// depends on "multi-threading" being enabled, so it must come after.
        ConstElementPtr queue_control = mutable_cfg->get("dhcp-queue-control");
        if (queue_control) {
            parameter_name = "dhcp-queue-control";
            DHCPQueueControlParser parser;
            srv_config->setDHCPQueueControl(parser.parse(queue_control));
        }

        /// depends on "multi-threading" being enabled, so it must come after.
        ConstElementPtr reservations_lookup_first = mutable_cfg->get("reservations-lookup-first");
        if (reservations_lookup_first) {
            parameter_name = "reservations-lookup-first";
            if (MultiThreadingMgr::instance().getMode()) {
                LOG_WARN(dhcp6_logger, DHCP6_RESERVATIONS_LOOKUP_FIRST_ENABLED);
            }
            srv_config->setReservationsLookupFirst(reservations_lookup_first->boolValue());
        }

        ConstElementPtr hr_identifiers =
            mutable_cfg->get("host-reservation-identifiers");
        if (hr_identifiers) {
            parameter_name = "host-reservation-identifiers";
            HostReservationIdsParser6 parser;
            parser.parse(hr_identifiers);
        }

        ConstElementPtr server_id = mutable_cfg->get("server-id");
        if (server_id) {
            parameter_name = "server-id";
            DUIDConfigParser parser;
            const CfgDUIDPtr& cfg = srv_config->getCfgDUID();
            parser.parse(cfg, server_id);
        }

        ConstElementPtr ifaces_config = mutable_cfg->get("interfaces-config");
        if (ifaces_config) {
            parameter_name = "interfaces-config";
            IfacesConfigParser parser(AF_INET6, check_only);
            CfgIfacePtr cfg_iface = srv_config->getCfgIface();
            parser.parse(cfg_iface, ifaces_config);
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
            parser.parse(expiration_cfg);
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
            libraries.verifyLibraries(hooks_libraries->getPosition());
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
                parser.parse(client_classes, AF_INET6);
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
            for (auto it : hosts_databases->listValue()) {
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
            /// We need to create instance of SharedNetworks6ListParser
            /// and parse the list of the shared networks into the
            /// CfgSharedNetworks6 object. One additional step is then to
            /// add subnets from the CfgSharedNetworks6 into CfgSubnets6
            /// as well.
            SharedNetworks6ListParser parser;
            CfgSharedNetworks6Ptr cfg = srv_config->getCfgSharedNetworks6();
            parser.parse(cfg, shared_networks);

            // We also need to put the subnets it contains into normal
            // subnets list.
            global_parser.copySubnets6(srv_config->getCfgSubnets6(), cfg);
        }

        ConstElementPtr subnet6 = mutable_cfg->get("subnet6");
        if (subnet6) {
            parameter_name = "subnet6";
            Subnets6ListConfigParser subnets_parser;
            // parse() returns number of subnets parsed. We may log it one day.
            subnets_parser.parse(srv_config, subnet6);
        }

        ConstElementPtr reservations = mutable_cfg->get("reservations");
        if (reservations) {
            parameter_name = "reservations";
            HostCollection hosts;
            HostReservationsListParser<HostReservationParser6> parser;
            parser.parse(SUBNET_ID_GLOBAL, reservations, hosts);
            for (auto h = hosts.begin(); h != hosts.end(); ++h) {
                srv_config->getCfgHosts()->add(*h);
            }
        }

        ConstElementPtr config_control = mutable_cfg->get("config-control");
        if (config_control) {
            parameter_name = "config-control";
            ConfigControlParser parser;
            ConfigControlInfoPtr config_ctl_info = parser.parse(config_control);
            CfgMgr::instance().getStagingCfg()->setConfigControlInfo(config_ctl_info);
        }

        ConstElementPtr rsoo_list = mutable_cfg->get("relay-supplied-options");
        if (rsoo_list) {
            parameter_name = "relay-supplied-options";
            RSOOListConfigParser parser;
            parser.parse(srv_config, rsoo_list);
        }

        ConstElementPtr compatibility = mutable_cfg->get("compatibility");
        if (compatibility) {
            for (auto kv : compatibility->mapValue()) {
                if (kv.first == "lenient-option-parsing") {
                    CfgMgr::instance().getStagingCfg()->setLenientOptionParsing(
                        kv.second->boolValue());
                }
            }
        }

        // Make parsers grouping.
        ConfigPair config_pair;
        const std::map<std::string, ConstElementPtr>& values_map =
            mutable_cfg->mapValue();

        BOOST_FOREACH(config_pair, values_map) {

            parameter_name = config_pair.first;

            // These are converted to SimpleParser and are handled already above.
            if ((config_pair.first == "data-directory") ||
                (config_pair.first == "option-def")  ||
                (config_pair.first == "option-data") ||
                (config_pair.first == "mac-sources") ||
                (config_pair.first == "control-socket") ||
                (config_pair.first == "multi-threading") ||
                (config_pair.first == "dhcp-queue-control") ||
                (config_pair.first == "host-reservation-identifiers") ||
                (config_pair.first == "server-id") ||
                (config_pair.first == "interfaces-config") ||
                (config_pair.first == "sanity-checks") ||
                (config_pair.first == "expired-leases-processing") ||
                (config_pair.first == "hooks-libraries") ||
                (config_pair.first == "dhcp-ddns") ||
                (config_pair.first == "client-classes") ||
                (config_pair.first == "lease-database") ||
                (config_pair.first == "hosts-database") ||
                (config_pair.first == "hosts-databases") ||
                (config_pair.first == "subnet6") ||
                (config_pair.first == "shared-networks") ||
                (config_pair.first == "reservations") ||
                (config_pair.first == "config-control") ||
                (config_pair.first == "relay-supplied-options") ||
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
                 (config_pair.first == "preferred-lifetime") ||
                 (config_pair.first == "min-preferred-lifetime") ||
                 (config_pair.first == "max-preferred-lifetime") ||
                 (config_pair.first == "valid-lifetime") ||
                 (config_pair.first == "min-valid-lifetime") ||
                 (config_pair.first == "max-valid-lifetime") ||
                 (config_pair.first == "decline-probation-period") ||
                 (config_pair.first == "dhcp4o6-port") ||
                 (config_pair.first == "server-tag") ||
                 (config_pair.first == "reservation-mode") ||
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
                 (config_pair.first == "store-extended-info") ||
                 (config_pair.first == "statistic-default-sample-count") ||
                 (config_pair.first == "statistic-default-sample-age") ||
                 (config_pair.first == "early-global-reservations-lookup") ||
                 (config_pair.first == "ip-reservations-unique") ||
                 (config_pair.first == "reservations-lookup-first") ||
                 (config_pair.first == "parked-packet-limit")) {
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
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_FAIL)
                  .arg(parameter_name).arg(ex.what());
        answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());

        // An error occurred, so make sure that we restore original data.
        rollback = true;
    } catch (...) {
        // For things like bad_cast in boost::lexical_cast
        LOG_ERROR(dhcp6_logger, DHCP6_PARSER_EXCEPTION).arg(parameter_name);
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

            // This occurs last as if it succeeds, there is no easy way to
            // revert it.  As a result, the failure to commit a subsequent
            // change causes problems when trying to roll back.
            HooksManager::prepareUnloadLibraries();
            static_cast<void>(HooksManager::unloadLibraries());
            const HooksConfig& libraries =
                CfgMgr::instance().getStagingCfg()->getHooksConfig();
            libraries.loadLibraries();
        } catch (const isc::Exception& ex) {
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_FAIL).arg(ex.what());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, ex.what());

            // An error occurred, so make sure to restore the original data.
            rollback = true;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_EXCEPTION);
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, "undefined configuration"
                                               " parsing error");

            // An error occurred, so make sure to restore the original data.
            rollback = true;
        }
    }

    // Moved from the commit block to add the config backend indication.
    if (!rollback) {
        try {

            // If there are config backends, fetch and merge into staging config
            server.getCBControl()->databaseConfigFetch(srv_config,
                                                       CBControlDHCPv6::FetchMode::FETCH_ALL);
        } catch (const isc::Exception& ex) {
            std::ostringstream err;
            err << "during update from config backend database: " << ex.what();
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_FAIL).arg(err.str());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str());

            // An error occurred, so make sure to restore the original data.
            rollback = true;
        } catch (...) {
            // For things like bad_cast in boost::lexical_cast
            std::ostringstream err;
            err << "during update from config backend database: "
                << "undefined configuration parsing error";
            LOG_ERROR(dhcp6_logger, DHCP6_PARSER_COMMIT_FAIL).arg(err.str());
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str());

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
    answer = isc::config::createAnswer(CONTROL_RESULT_SUCCESS, "Configuration successful.");
    return (answer);
}

}  // namespace dhcp
}  // namespace isc
