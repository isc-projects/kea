// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <util/strutil.h>
#include <ha_config.h>
#include <ha_service_states.h>
#include <sstream>

namespace {

/// @brief Creates default state configuration.
///
/// @param [out] state_map map of state configurations into which the
/// newly created configuration should be inserted.
/// @param state state for which new configuration is to be created.
void
createStateConfig(isc::ha::HAConfig::StateConfigMap& state_map, const int state) {
    isc::ha::HAConfig::StateConfigPtr cfg(new isc::ha::HAConfig::StateConfig(state));
    state_map[state] = cfg;
}

} // end of anonymous namespace

namespace isc {
namespace ha {

HAConfig::PeerConfig::PeerConfig()
    : name_(), url_(""), role_(STANDBY), auto_failover_(false) {
}

void
HAConfig::PeerConfig::setName(const std::string& name) {
    // We want to make sure that someone didn't provide a name that consists of
    // a single space, tab etc.
    const std::string& s = util::str::trim(name);
    if (s.empty()) {
        isc_throw(BadValue, "peer name must not be empty");
    }
    name_ = s;
}

void
HAConfig::PeerConfig::setRole(const std::string& role) {
    role_ = stringToRole(role);
}

std::string
HAConfig::PeerConfig::getLogLabel() const {
    std::ostringstream label;
    label << getName() << " (" << getUrl().toText() << ")";
    return (label.str());
}

HAConfig::PeerConfig::Role
HAConfig::PeerConfig::stringToRole(const std::string& role) {
    if (role == "primary") {
        return (HAConfig::PeerConfig::PRIMARY);

    } else if (role == "secondary") {
        return (HAConfig::PeerConfig::SECONDARY);

    } else if (role == "standby") {
        return (HAConfig::PeerConfig::STANDBY);

    } else if (role == "backup") {
        return (HAConfig::PeerConfig::BACKUP);

    }

    // Invalid value specified.
    isc_throw(BadValue, "unsupported value '" << role << "' for role parameter");
}

std::string
HAConfig::PeerConfig::roleToString(const HAConfig::PeerConfig::Role& role) {
    switch (role) {
    case HAConfig::PeerConfig::PRIMARY:
        return ("primary");
    case HAConfig::PeerConfig::SECONDARY:
        return ("secondary");
    case HAConfig::PeerConfig::STANDBY:
        return ("standby");
    case HAConfig::PeerConfig::BACKUP:
        return ("backup");
    default:
        ;
    }
    return ("");
}

HAConfig::StateConfig::StateConfig(const int state)
    : state_(state), pausing_(HAConfig::StateConfig::PAUSE_NEVER) {
}

void
HAConfig::StateConfig::setPausing(const std::string& pausing) {
    pausing_ = stringToPausing(pausing);
}

HAConfig::StateConfig::Pausing
HAConfig::StateConfig::stringToPausing(const std::string& pausing) {
    if (pausing == "always") {
        return (HAConfig::StateConfig::PAUSE_ALWAYS);

    } else if (pausing == "never") {
        return (HAConfig::StateConfig::PAUSE_NEVER);

    } else if (pausing == "once") {
        return (HAConfig::StateConfig::PAUSE_ONCE);
    }

    isc_throw(BadValue, "unsupported value " << pausing << " of 'pause' parameter");
}

std::string
HAConfig::StateConfig::pausingToString(const HAConfig::StateConfig::Pausing& pausing) {
    switch (pausing) {
    case HAConfig::StateConfig::PAUSE_ALWAYS:
        return ("always");

    case HAConfig::StateConfig::PAUSE_NEVER:
        return ("never");

    case HAConfig::StateConfig::PAUSE_ONCE:
        return ("once");

    default:
        ;
    }

    isc_throw(BadValue, "unsupported pause enumeration " << static_cast<int>(pausing));
}

HAConfig::HAConfig()
    : this_server_name_(), ha_mode_(HOT_STANDBY), send_lease_updates_(true),
      sync_leases_(true), sync_timeout_(60000), heartbeat_delay_(10000),
      max_response_delay_(60000), max_ack_delay_(10000), max_unacked_clients_(10),
      peers_(), state_machine_() {

    // Create default state configurations.
    createStateConfig(state_machine_, HA_BACKUP_ST);
    createStateConfig(state_machine_, HA_HOT_STANDBY_ST);
    createStateConfig(state_machine_, HA_LOAD_BALANCING_ST);
    createStateConfig(state_machine_, HA_PARTNER_DOWN_ST);
    createStateConfig(state_machine_, HA_READY_ST);
    createStateConfig(state_machine_, HA_SYNCING_ST);
    createStateConfig(state_machine_, HA_TERMINATED_ST);
    createStateConfig(state_machine_, HA_WAITING_ST);
}

HAConfig::PeerConfigPtr
HAConfig::selectNextPeerConfig(const std::string& name) {
    // Check if there is a configuration for this server name alrady. We can't
    // have two servers with the same name.
    if (peers_.count(name) > 0) {
        isc_throw(BadValue, "peer with name '" << name << "' already specified");
    }

    // Name appears to be unique, so let's add it.
    PeerConfigPtr cfg(new PeerConfig());
    cfg->setName(name);
    peers_[name] = cfg;

    // Return this to the caller so as the caller can set parsed configuration
    // for this peer.
    return (cfg);
}

void
HAConfig::setThisServerName(const std::string& this_server_name) {
    // Avoid names consisting of spaces, tabs etc.
    std::string s = util::str::trim(this_server_name);
    if (s.empty()) {
        isc_throw(BadValue, "'this-server-name' value must not be empty");
    }

    this_server_name_ = s;
}


void
HAConfig::setHAMode(const std::string& ha_mode) {
    ha_mode_ = stringToHAMode(ha_mode);
}

HAConfig::HAMode
HAConfig::stringToHAMode(const std::string& ha_mode) {
    if (ha_mode == "load-balancing") {
        return (LOAD_BALANCING);

    } else if (ha_mode == "hot-standby") {
        return (HOT_STANDBY);
    }

    isc_throw(BadValue, "unsupported value '" << ha_mode << "' for mode parameter");
}

std::string
HAConfig::HAModeToString(const HAMode& ha_mode) {
    switch (ha_mode) {
    case LOAD_BALANCING:
        return ("load-balancing");
    case HOT_STANDBY:
        return ("hot-standby");
    default:
        ;
    }
    return ("");
}

HAConfig::PeerConfigPtr
HAConfig::getPeerConfig(const std::string& name) const {
    auto peer = peers_.find(name);
    if (peer == peers_.end()) {
        isc_throw(InvalidOperation, "no configuration specified for server " << name);
    }

    return (peer->second);
}

HAConfig::PeerConfigPtr
HAConfig::getFailoverPeerConfig() const {
    PeerConfigMap servers = getOtherServersConfig();
    for (auto peer = servers.begin(); peer != servers.end(); ++peer) {
        if (peer->second->getRole() != HAConfig::PeerConfig::BACKUP) {
            return (peer->second);
        }
    }

    isc_throw(InvalidOperation, "no failover partner server found for this"
              " server " << getThisServerName());
}

HAConfig::PeerConfigPtr
HAConfig::getThisServerConfig() const {
    return (getPeerConfig(getThisServerName()));
}

HAConfig::PeerConfigMap
HAConfig::getOtherServersConfig() const {
    PeerConfigMap copy = peers_;
    copy.erase(getThisServerName());
    return (copy);
}

HAConfig::StateConfigPtr
HAConfig::getStateConfig(const int state) const {
    auto state_config = state_machine_.find(state);
    if (state_config == state_machine_.end()) {
        isc_throw(BadValue, "no state machine configuration found for the "
                  << "state identifier " << state);
    }

    return (state_config->second);
}

void
HAConfig::validate() const {
    // Peers configurations must be provided.
    if (peers_.count(getThisServerName()) == 0) {
        isc_throw(HAConfigValidationError, "no peer configuration specified for the '"
                  << getThisServerName() << "'");
    }

    // Gather all the roles and see how many occurrences of each role we get.
    std::map<PeerConfig::Role, unsigned> peers_cnt;
    for (auto p = peers_.begin(); p != peers_.end(); ++p) {
        if (!p->second->getUrl().isValid()) {
            isc_throw(HAConfigValidationError, "invalid URL: "
                      << p->second->getUrl().getErrorMessage()
                      << " for server " << p->second->getName());
        }

        ++peers_cnt[p->second->getRole()];
    }

    // Only one primary server allowed.
    if (peers_cnt.count(PeerConfig::PRIMARY) && (peers_cnt[PeerConfig::PRIMARY] > 1)) {
        isc_throw(HAConfigValidationError, "multiple primary servers specified");
    }

    // Only one secondary server allowed.
    if (peers_cnt.count(PeerConfig::SECONDARY) && (peers_cnt[PeerConfig::SECONDARY] > 1)) {
        isc_throw(HAConfigValidationError, "multiple secondary servers specified");
    }

    // Only one standby server allowed.
    if (peers_cnt.count(PeerConfig::STANDBY) && (peers_cnt[PeerConfig::STANDBY] > 1)) {
        isc_throw(HAConfigValidationError, "multiple standby servers specified");
    }

    if (ha_mode_ == LOAD_BALANCING) {
        // Standby servers not allowed in load balancing configuration.
        if (peers_cnt.count(PeerConfig::STANDBY) > 0) {
            isc_throw(HAConfigValidationError, "standby servers not allowed in the load "
                      "balancing configuration");
        }

        // Require one secondary server in the load balancing configuration.
        if (peers_cnt.count(PeerConfig::SECONDARY) == 0) {
            isc_throw(HAConfigValidationError, "secondary server required in the load"
                      " balancing configuration");
        }

        // Require one primary server in the load balancing configuration.
        if (peers_cnt.count(PeerConfig::PRIMARY) == 0) {
            isc_throw(HAConfigValidationError, "primary server required in the load"
                      " balancing configuration");
        }

    }

    if (ha_mode_ == HOT_STANDBY) {
        // Secondary servers not allowed in the hot standby configuration.
        if (peers_cnt.count(PeerConfig::SECONDARY) > 0) {
            isc_throw(HAConfigValidationError, "secondary servers not allowed in the hot"
                      " standby configuration");
        }

        // Require one standby server in the hot standby configuration.
        if (peers_cnt.count(PeerConfig::STANDBY) == 0) {
            isc_throw(HAConfigValidationError, "standby server required in the hot"
                      " standby configuration");
        }

        // Require one primary server in the hot standby configuration.
        if (peers_cnt.count(PeerConfig::PRIMARY) == 0) {
            isc_throw(HAConfigValidationError, "primary server required in the hot"
                      " standby configuration");
        }
    }
}

} // end of namespace isc::ha
} // end of namespace isc
