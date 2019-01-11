// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_config_parser.h>
#include <ha_log.h>
#include <ha_service_states.h>
#include <cc/dhcp_config_error.h>
#include <limits>
#include <set>

using namespace isc::data;
using namespace isc::http;

namespace {

/// @brief Default values for HA configuration.
const SimpleDefaults HA_CONFIG_DEFAULTS = {
    { "send-lease-updates", Element::boolean, "true" },
    { "sync-leases", Element::boolean, "true" },
    { "sync-timeout", Element::integer, "60000" },
    { "sync-page-limit", Element::integer, "10000" },
    { "heartbeat-delay", Element::integer, "10000" },
    { "max-response-delay", Element::integer, "60000" },
    { "max-ack-delay", Element::integer, "10000" },
    { "max-unacked-clients", Element::integer, "10" }
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

    // Set default values.
    setDefaults(c, HA_CONFIG_DEFAULTS);

    // HA configuration must be a map.
    if (c->getType() != Element::map) {
        isc_throw(ConfigError, "expected list of maps in the HA configuration");
    }

    // It must contains peers section.
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

    // Get 'mode'.
    config_storage->setHAMode(getString(c, "mode"));

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

    // Peers configuration parsing.
    const auto& peers_vec = peers->listValue();

    // There must be at least two peers specified.
    if (peers_vec.size() < 2) {
        isc_throw(ConfigError, "peers configuration requires at least two peers"
                  " to be specified");
    }

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

        // Role.
        cfg->setRole(getString(*p, "role"));

        // Auto failover configuration.
        cfg->setAutoFailover(getBoolean(*p, "auto-failover"));
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
                  << std::numeric_limits<T>::max());
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
    // scope in case of partner's failure. This setting is ok if the
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
