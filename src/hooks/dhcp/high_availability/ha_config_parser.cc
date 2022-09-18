// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_config_parser.h>
#include <ha_log.h>
#include <ha_service_states.h>
#include <cc/dhcp_config_error.h>
#include <util/file_utilities.h>
#include <limits>
#include <set>

using namespace isc::data;
using namespace isc::http;

namespace {

/// @brief Default values for HA load balancing.
const SimpleDefaults HA_CONFIG_LB_DEFAULTS = {
    { "delayed-updates-limit", Element::integer, "100" },
};

/// @brief Default values for HA configuration.
const SimpleDefaults HA_CONFIG_DEFAULTS = {
    { "delayed-updates-limit",      Element::integer, "0" },
    { "heartbeat-delay",            Element::integer, "10000" },
    { "max-ack-delay",              Element::integer, "10000" },
    { "max-response-delay",         Element::integer, "60000" },
    { "max-unacked-clients",        Element::integer, "10" },
    { "max-rejected-lease-updates", Element::integer, "10" },
    { "require-client-certs",       Element::boolean, "true" },
    { "restrict-commands",          Element::boolean, "false" },
    { "send-lease-updates",         Element::boolean, "true" },
    { "sync-leases",                Element::boolean, "true" },
    { "sync-timeout",               Element::integer, "60000" },
    { "sync-page-limit",            Element::integer, "10000" },
    { "wait-backup-ack",            Element::boolean, "false" }
};

/// @brief Default values for HA multi-threading configuration.
const SimpleDefaults HA_CONFIG_MT_DEFAULTS = {
    { "enable-multi-threading",    Element::boolean, "false" },
    { "http-client-threads",       Element::integer, "0" },
    { "http-dedicated-listener",   Element::boolean, "false" },
    { "http-listener-threads",     Element::integer, "0" }
};

/// @brief Default values for HA peer configuration.
const SimpleDefaults HA_CONFIG_PEER_DEFAULTS = {
    { "auto-failover", Element::boolean, "true" }
};

/// @brief Default values for HA state configuration.
const SimpleDefaults HA_CONFIG_STATE_DEFAULTS = {
    { "pause", Element::string, "never" }
};

} // end of anonymous namespace

namespace isc {
namespace ha {

void
HAConfigParser::parse(const HAConfigPtr& config_storage,
                      const ConstElementPtr& config) {
    try {
        // This may cause different types of exceptions. We catch them here
        // and throw unified exception type.
        parseInternal(config_storage, config);
        logConfigStatus(config_storage);

    } catch (const ConfigError& ex) {
        throw;

    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what());
    }
}

void
HAConfigParser::parseInternal(const HAConfigPtr& config_storage,
                              const ConstElementPtr& config) {
    // Config must be provided.
    if (!config) {
        isc_throw(ConfigError, "HA configuration must not be null");
    }

    // Config must be a list. Each contains one relationship between servers in the
    // HA configuration. Currently we support only one relationship.
    if (config->getType() != Element::list) {
        isc_throw(ConfigError, "HA configuration must be a list");
    }

    const auto& config_vec = config->listValue();
    if (config_vec.size() != 1) {
        isc_throw(ConfigError, "invalid number of configurations in the HA configuration"
                  " list. Expected exactly one configuration");
    }

    // Get the HA configuration.
    ElementPtr c = config_vec[0];

    // Get 'mode'. That's the first thing to gather because the defaults we
    // apply to the configuration depend on the mode.
    config_storage->setHAMode(getString(c, "mode"));

    // Set load-balancing specific defaults.
    if (config_storage->getHAMode() == HAConfig::LOAD_BALANCING) {
        setDefaults(c, HA_CONFIG_LB_DEFAULTS);
    }
    // Set general defaults.
    setDefaults(c, HA_CONFIG_DEFAULTS);

    // HA configuration must be a map.
    if (c->getType() != Element::map) {
        isc_throw(ConfigError, "expected list of maps in the HA configuration");
    }

    // It must contain peers section.
    if (!c->contains("peers")) {
        isc_throw(ConfigError, "'peers' parameter missing in HA configuration");
    }

    // Peers configuration must be a list of maps.
    ConstElementPtr peers = c->get("peers");
    if (peers->getType() != Element::list) {
        isc_throw(ConfigError, "'peers' parameter must be a list");
    }

    // State machine configuration must be a map.
    ConstElementPtr state_machine = c->get("state-machine");
    ConstElementPtr states_list;
    if (state_machine) {
        if (state_machine->getType() != Element::map) {
            isc_throw(ConfigError, "'state-machine' parameter must be a map");
        }

        states_list = state_machine->get("states");
        if (states_list && (states_list->getType() != Element::list)) {
            isc_throw(ConfigError, "'states' parameter must be a list");
        }
    }

    // We have made major sanity checks, so let's try to gather some values.

    // Get 'this-server-name'.
    config_storage->setThisServerName(getString(c, "this-server-name"));

    // Get 'send-lease-updates'.
    config_storage->setSendLeaseUpdates(getBoolean(c, "send-lease-updates"));

    // Get 'sync-leases'.
    config_storage->setSyncLeases(getBoolean(c, "sync-leases"));

    // Get 'sync-timeout'.
    uint32_t sync_timeout = getAndValidateInteger<uint32_t>(c, "sync-timeout");
    config_storage->setSyncTimeout(sync_timeout);

    // Get 'sync-page-limit'.
    uint32_t sync_page_limit = getAndValidateInteger<uint32_t>(c, "sync-page-limit");
    config_storage->setSyncPageLimit(sync_page_limit);

    // Get 'delayed-updates-limit'.
    uint32_t delayed_updates_limit = getAndValidateInteger<uint32_t>(c, "delayed-updates-limit");
    config_storage->setDelayedUpdatesLimit(delayed_updates_limit);

    // Get 'heartbeat-delay'.
    uint16_t heartbeat_delay = getAndValidateInteger<uint16_t>(c, "heartbeat-delay");
    config_storage->setHeartbeatDelay(heartbeat_delay);

    // Get 'max-response-delay'.
    uint16_t max_response_delay = getAndValidateInteger<uint16_t>(c, "max-response-delay");
    config_storage->setMaxResponseDelay(max_response_delay);

    // Get 'max-ack-delay'.
    uint16_t max_ack_delay = getAndValidateInteger<uint16_t>(c, "max-ack-delay");
    config_storage->setMaxAckDelay(max_ack_delay);

    // Get 'max-unacked-clients'.
    uint32_t max_unacked_clients = getAndValidateInteger<uint32_t>(c, "max-unacked-clients");
    config_storage->setMaxUnackedClients(max_unacked_clients);

    // Get 'max-rejected-lease-updates'.
    uint32_t max_rejected_lease_updates = getAndValidateInteger<uint32_t>(c, "max-rejected-lease-updates");
    config_storage->setMaxRejectedLeaseUpdates(max_rejected_lease_updates);

    // Get 'wait-backup-ack'.
    config_storage->setWaitBackupAck(getBoolean(c, "wait-backup-ack"));

    // Get multi-threading map.
    ElementPtr mt_config = boost::const_pointer_cast<Element>(c->get("multi-threading"));
    if (!mt_config) {
        // Not there, make an empty one.
        mt_config = Element::createMap();
        c->set("multi-threading", mt_config);
    } else if (mt_config->getType() != Element::map) {
        isc_throw(ConfigError, "multi-threading configuration must be a map");
    }

    // Backfill the MT defaults.
    setDefaults(mt_config, HA_CONFIG_MT_DEFAULTS);

    // Get 'enable-multi-threading'.
    config_storage->setEnableMultiThreading(getBoolean(mt_config, "enable-multi-threading"));

    // Get 'http-dedicated-listener'.
    config_storage->setHttpDedicatedListener(getBoolean(mt_config, "http-dedicated-listener"));

    // Get 'http-listener-threads'.
    uint32_t threads = getAndValidateInteger<uint32_t>(mt_config, "http-listener-threads");
    config_storage->setHttpListenerThreads(threads);

    // Get 'http-client-threads'.
    threads = getAndValidateInteger<uint32_t>(mt_config, "http-client-threads");
    config_storage->setHttpClientThreads(threads);

    // Get optional 'trust-anchor'.
    ConstElementPtr ca = c->get("trust-anchor");
    if (ca) {
        config_storage->setTrustAnchor(getString(c, "trust-anchor"));
    }

    // Get optional 'cert-file'.
    ConstElementPtr cert = c->get("cert-file");
    if (cert) {
        config_storage->setCertFile(getString(c, "cert-file"));
    }

    // Get optional 'key-file'.
    ConstElementPtr key = c->get("key-file");
    if (key) {
        config_storage->setKeyFile(getString(c, "key-file"));
    }

    // Get 'require-client-certs'.
    config_storage->setRequireClientCerts(getBoolean(c, "require-client-certs"));

    // Get 'restrict-commands'.
    config_storage->setRestrictCommands(getBoolean(c, "restrict-commands"));

    // Peers configuration parsing.
    const auto& peers_vec = peers->listValue();

    // Go over configuration of each peer.
    for (auto p = peers_vec.begin(); p != peers_vec.end(); ++p) {

        // Peer configuration is held in a map.
        if ((*p)->getType() != Element::map) {
            isc_throw(ConfigError, "peer configuration must be a map");
        }

        setDefaults(*p, HA_CONFIG_PEER_DEFAULTS);

        // Server name.
        auto cfg = config_storage->selectNextPeerConfig(getString(*p, "name"));

        // URL.
        cfg->setUrl(Url(getString((*p), "url")));

        // Optional trust anchor.
        if ((*p)->contains("trust-anchor")) {
            cfg->setTrustAnchor(getString(*p, ("trust-anchor")));
        }

        // Optional certificate file.
        if ((*p)->contains("cert-file")) {
            cfg->setCertFile(getString(*p, ("cert-file")));
        }

        // Optional private key file.
        if ((*p)->contains("key-file")) {
            cfg->setKeyFile(getString(*p, ("key-file")));
        }

        // Role.
        cfg->setRole(getString(*p, "role"));

        // Auto failover configuration.
        cfg->setAutoFailover(getBoolean(*p, "auto-failover"));

        // Basic HTTP authentication password.
        std::string password;
        if ((*p)->contains("basic-auth-password")) {
            if ((*p)->contains("basic-auth-password-file")) {
                isc_throw(dhcp::DhcpConfigError, "only one of "
                          << "basic-auth-password and "
                          << "basic-auth-password-file parameter can be "
                          << "configured in peer '"
                          << cfg->getName() << "'");
            }
            password = getString((*p), "basic-auth-password");
        }
        if ((*p)->contains("basic-auth-password-file")) {
            std::string password_file =
                getString((*p), "basic-auth-password-file");
            try {
                password = util::file::getContent(password_file);
            } catch (const std::exception& ex) {
                isc_throw(dhcp::DhcpConfigError, "bad password file in peer '"
                          << cfg->getName() << "': " << ex.what());
            }
        }

        // Basic HTTP authentication user.
        if ((*p)->contains("basic-auth-user")) {
            std::string user = getString((*p), "basic-auth-user");
            BasicHttpAuthPtr& auth = cfg->getBasicAuth();
            try {
                if (!user.empty()) {
                    // Validate the user id value.
                    auth.reset(new BasicHttpAuth(user, password));
                }
            } catch (const std::exception& ex) {
                isc_throw(dhcp::DhcpConfigError, ex.what() << " in peer '"
                          << cfg->getName() << "'");
            }
        }
    }

    // Per state configuration is optional.
    if (states_list) {
        const auto& states_vec = states_list->listValue();

        std::set<int> configured_states;

        // Go over per state configurations.
        for (auto s = states_vec.begin(); s != states_vec.end(); ++s) {

            // State configuration is held in map.
            if ((*s)->getType() != Element::map) {
                isc_throw(ConfigError, "state configuration must be a map");
            }

            setDefaults(*s, HA_CONFIG_STATE_DEFAULTS);

            // Get state name and set per state configuration.
            std::string state_name = getString(*s, "state");

            int state = stringToState(state_name);
            // Check that this configuration doesn't duplicate existing configuration.
            if (configured_states.count(state) > 0) {
                isc_throw(ConfigError, "duplicated configuration for the '"
                          << state_name << "' state");
            }
            configured_states.insert(state);

            config_storage->getStateMachineConfig()->
                getStateConfig(state)->setPausing(getString(*s, "pause"));
        }
    }

    // We have gone over the entire configuration and stored it in the configuration
    // storage. However, we need to still validate it to detect errors like:
    // duplicate secondary/primary servers, no configuration for this server etc.
    config_storage->validate();
}

template<typename T>
T HAConfigParser::getAndValidateInteger(const ConstElementPtr& config,
                                        const std::string& parameter_name) const {
    int64_t value = getInteger(config, parameter_name);
    if (value < 0) {
        isc_throw(ConfigError, "'" << parameter_name << "' must not be negative");

    } else if (value > std::numeric_limits<T>::max()) {
        isc_throw(ConfigError, "'" << parameter_name << "' must not be greater than "
                                   << +std::numeric_limits<T>::max());
    }

    return (static_cast<T>(value));
}

void
HAConfigParser::logConfigStatus(const HAConfigPtr& config_storage) const {
    LOG_INFO(ha_logger, HA_CONFIGURATION_SUCCESSFUL);

    // If lease updates are disabled, we want to make sure that the user
    // realizes that and that he has configured some other mechanism to
    // populate leases.
    if (!config_storage->amSendingLeaseUpdates()) {
        LOG_WARN(ha_logger, HA_CONFIG_LEASE_UPDATES_DISABLED);
    }

    // Same as above but for lease database synchronization.
    if (!config_storage->amSyncingLeases()) {
        LOG_WARN(ha_logger, HA_CONFIG_LEASE_SYNCING_DISABLED);
    }

    // Unusual configuration.
    if (config_storage->amSendingLeaseUpdates() !=
        config_storage->amSyncingLeases()) {
        LOG_WARN(ha_logger, HA_CONFIG_LEASE_UPDATES_AND_SYNCING_DIFFER)
            .arg(config_storage->amSendingLeaseUpdates() ? "true" : "false")
            .arg(config_storage->amSyncingLeases() ? "true" : "false");
    }

    // With this setting the server will not take ownership of the partner's
    // scope in case of partner's failure. This setting is OK if the
    // administrator desires to have more control over scopes selection.
    // The administrator will need to send ha-scopes command to instruct
    // the server to take ownership of the scope. In some cases he may
    // also need to send dhcp-enable command to enable DHCP service
    // (specifically hot-standby mode for standby server).
    if (!config_storage->getThisServerConfig()->isAutoFailover()) {
        LOG_WARN(ha_logger, HA_CONFIG_AUTO_FAILOVER_DISABLED)
            .arg(config_storage->getThisServerName());
    }
}

} // end of namespace ha
} // end of namespace isc
