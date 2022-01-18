// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <asiolink/crypto_tls.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <exceptions/exceptions.h>
#include <util/multi_threading_mgr.h>
#include <util/strutil.h>
#include <ha_log.h>
#include <ha_config.h>
#include <ha_service_states.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::util;
using namespace isc::dhcp;

namespace isc {
namespace ha {

HAConfig::PeerConfig::PeerConfig()
    : tls_context_(), name_(), url_(""), trust_anchor_(), cert_file_(),
      key_file_(), role_(STANDBY), auto_failover_(false), basic_auth_() {
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

void
HAConfig::PeerConfig::addBasicAuthHttpHeader(PostHttpRequestJsonPtr request) const {
    const BasicHttpAuthPtr& auth = getBasicAuth();
    if (!request || !auth) {
        return;
    }
    request->context()->headers_.push_back(BasicAuthHttpHeaderContext(*auth));
}

HAConfig::StateConfig::StateConfig(const int state)
    : state_(state), pausing_(STATE_PAUSE_NEVER) {
}

void
HAConfig::StateConfig::setPausing(const std::string& pausing) {
    pausing_ = stringToPausing(pausing);
}

StatePausing
HAConfig::StateConfig::stringToPausing(const std::string& pausing) {
    if (pausing == "always") {
        return (STATE_PAUSE_ALWAYS);

    } else if (pausing == "never") {
        return (STATE_PAUSE_NEVER);

    } else if (pausing == "once") {
        return (STATE_PAUSE_ONCE);
    }

    isc_throw(BadValue, "unsupported value " << pausing << " of 'pause' parameter");
}

std::string
HAConfig::StateConfig::pausingToString(const StatePausing& pausing) {
    switch (pausing) {
    case STATE_PAUSE_ALWAYS:
        return ("always");

    case STATE_PAUSE_NEVER:
        return ("never");

    case STATE_PAUSE_ONCE:
        return ("once");

    default:
        ;
    }

    isc_throw(BadValue, "unsupported pause enumeration " << static_cast<int>(pausing));
}

HAConfig::StateConfigPtr
HAConfig::StateMachineConfig::getStateConfig(const int state) {
    // Return config for the state if it exists already.
    auto state_config = states_.find(state);
    if (state_config != states_.end()) {
        return (state_config->second);
    }

    // Create config for the state and store its pointer.
    StateConfigPtr new_state_config(new StateConfig(state));
    states_[state] = new_state_config;

    return (new_state_config);
}

HAConfig::HAConfig()
    : this_server_name_(), ha_mode_(HOT_STANDBY), send_lease_updates_(true),
      sync_leases_(true), sync_timeout_(60000), sync_page_limit_(10000),
      delayed_updates_limit_(0), heartbeat_delay_(10000), max_response_delay_(60000),
      max_ack_delay_(10000), max_unacked_clients_(10), wait_backup_ack_(false),
      enable_multi_threading_(false), http_dedicated_listener_(false),
      http_listener_threads_(0), http_client_threads_(0),
      trust_anchor_(), cert_file_(), key_file_(),
      peers_(), state_machine_(new StateMachineConfig()) {
}

HAConfig::PeerConfigPtr
HAConfig::selectNextPeerConfig(const std::string& name) {
    // Check if there is a configuration for this server name already. We can't
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

    } else if (ha_mode == "passive-backup") {
        return (PASSIVE_BACKUP);
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
    case PASSIVE_BACKUP:
        return ("passive-backup");
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

void
HAConfig::validate() {
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

        // The hostname must be an address, not a name.
        IOAddress addr("::");
        try {
            addr = IOAddress(p->second->getUrl().getStrippedHostname());
        } catch (const IOError& ex) {
            isc_throw(HAConfigValidationError, "bad url '"
                      << p->second->getUrl().toText()
                      << "': " << ex.what()
                      << " for server " << p->second->getName());
        }

        // Check TLS setup.
        Optional<std::string> ca = p->second->getTrustAnchor();
        Optional<std::string> cert = p->second->getCertFile();
        Optional<std::string> key = p->second->getKeyFile();
        // When not configured get the value from the global level.
        if (ca.unspecified()) {
            ca = trust_anchor_;
        }
        if (cert.unspecified()) {
            cert = cert_file_;
        }
        if (key.unspecified()) {
            key = key_file_;
        }
        bool have_ca = (!ca.unspecified() && !ca.get().empty());
        bool have_cert = (!cert.unspecified() && !cert.get().empty());
        bool have_key = (!key.unspecified() && !key.get().empty());
        bool use_tls = (have_ca || have_cert || have_key);
        if (use_tls) {
            try {
                // TLS is used: all 3 parameters are required.
                if (!have_ca) {
                    isc_throw(HAConfigValidationError, "trust-anchor parameter"
                              << " is missing or empty: all or none of"
                              << " TLS parameters must be set");
                }
                if (!have_cert) {
                    isc_throw(HAConfigValidationError, "cert-file parameter"
                              << " is missing or empty: all or none of"
                              << " TLS parameters must be set");
                }
                if (!have_key) {
                    isc_throw(HAConfigValidationError, "key-file parameter"
                              << " is missing or empty: all or none of"
                              << " TLS parameters must be set");
                }
                TlsContext::configure(p->second->tls_context_,
                                      TlsRole::CLIENT,
                                      ca.get(),
                                      cert.get(),
                                      key.get());
            } catch (const isc::Exception& ex) {
                isc_throw(HAConfigValidationError, "bad TLS config for server "
                          << p->second->getName() << ": " << ex.what());
            }
        } else {
            // Refuse HTTPS scheme when TLS is not enabled.
            if (p->second->getUrl().getScheme() == Url::HTTPS) {
                isc_throw(HAConfigValidationError, "bad url '"
                          << p->second->getUrl().toText()
                          << "': https scheme is not supported"
                          << " for server " << p->second->getName()
                          << " where TLS is disabled");
            }
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

        // In the load-balancing mode the wait-backup-ack must be false.
        if (wait_backup_ack_) {
            isc_throw(HAConfigValidationError, "'wait-backup-ack' must be set to false in the"
                      " load balancing configuration");
        }

    } else if (ha_mode_ == HOT_STANDBY) {
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

        // In the hot-standby mode the wait-backup-ack must be false.
        if (wait_backup_ack_) {
            isc_throw(HAConfigValidationError, "'wait-backup-ack' must be set to false in the"
                      " hot standby configuration");
        }

        // The server must not transition to communication-recovery state in
        // hot-standby mode.
        if (delayed_updates_limit_ > 0) {
            isc_throw(HAConfigValidationError, "'delayed-updates-limit' must be set to 0 in"
                      " the hot standby configuration");
        }

    } else if (ha_mode_ == PASSIVE_BACKUP) {
        if (peers_cnt.count(PeerConfig::SECONDARY) > 0) {
            isc_throw(HAConfigValidationError, "secondary servers not allowed in the"
                      " passive backup configuration");
        }

        if (peers_cnt.count(PeerConfig::STANDBY) > 0) {
            isc_throw(HAConfigValidationError, "standby servers not allowed in the"
                      " passive backup configuration");
        }

        if (peers_cnt.count(PeerConfig::PRIMARY) == 0) {
            isc_throw(HAConfigValidationError, "primary server required in the"
                      " passive backup configuration");
        }

        // The server must not transition to communication-recovery state in
        // passive-backup mode.
        if (delayed_updates_limit_ > 0) {
            isc_throw(HAConfigValidationError, "'delayed-updates-limit' must be set to 0 in"
                      " the passive backup configuration");
        }
    }

    if (enable_multi_threading_) {
        // We get it from staging because applying the DHCP multi-threading configuration
        // occurs after library loading during the (re)configuration process.
        auto mcfg = CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading();
        bool dhcp_mt_enabled = false;
        uint32_t dhcp_threads = 0;
        uint32_t dummy_queue_size = 0;
        CfgMultiThreading::extract(mcfg, dhcp_mt_enabled, dhcp_threads, dummy_queue_size);

        if (!dhcp_mt_enabled) {
            // HA+MT requires DHCP multi-threading.
            LOG_INFO(ha_logger, HA_CONFIG_DHCP_MT_DISABLED);
            enable_multi_threading_ = false;
            return;
        }

        // When DHCP threads is configured as zero, we should auto-detect.
        if (!dhcp_threads) {
            dhcp_threads = MultiThreadingMgr::detectThreadCount();
            // If machine says it cannot support threads.
            if (!dhcp_threads) {
                LOG_INFO(ha_logger, HA_CONFIG_SYSTEM_MT_UNSUPPORTED);
                enable_multi_threading_ = false;
                return;
            }
        }

        // If http_listener_threads_ is 0, then we use the same number of
        // threads as DHCP does.
        if (http_listener_threads_ == 0) {
            http_listener_threads_ = dhcp_threads;
        }

        // If http_client_threads_ is 0, then we use the same number of
        // threads as DHCP does.
        if (http_client_threads_ == 0) {
            http_client_threads_ = dhcp_threads;
        }
    }
}

} // end of namespace isc::ha
} // end of namespace isc
