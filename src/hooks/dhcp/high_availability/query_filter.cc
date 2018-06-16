// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_log.h>
#include <query_filter.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <exceptions/exceptions.h>
#include <array>
#include <iostream>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::log;

namespace {

/// @brief A "mixing table" of 256 distinct values, in pseudo-random order.
///
/// The mixing table comes from section 6 of RFC3074.
std::array<uint8_t, 256> loadb_mx_tbl = { {
    251, 175, 119, 215, 81, 14, 79, 191, 103, 49, 181, 143, 186, 157,  0,
    232, 31, 32, 55, 60, 152, 58, 17, 237, 174, 70, 160, 144, 220, 90, 57,
    223, 59,  3, 18, 140, 111, 166, 203, 196, 134, 243, 124, 95, 222, 179,
    197, 65, 180, 48, 36, 15, 107, 46, 233, 130, 165, 30, 123, 161, 209, 23,
    97, 16, 40, 91, 219, 61, 100, 10, 210, 109, 250, 127, 22, 138, 29, 108,
    244, 67, 207,  9, 178, 204, 74, 98, 126, 249, 167, 116, 34, 77, 193,
    200, 121,  5, 20, 113, 71, 35, 128, 13, 182, 94, 25, 226, 227, 199, 75,
    27, 41, 245, 230, 224, 43, 225, 177, 26, 155, 150, 212, 142, 218, 115,
    241, 73, 88, 105, 39, 114, 62, 255, 192, 201, 145, 214, 168, 158, 221,
    148, 154, 122, 12, 84, 82, 163, 44, 139, 228, 236, 205, 242, 217, 11,
    187, 146, 159, 64, 86, 239, 195, 42, 106, 198, 118, 112, 184, 172, 87,
    2, 173, 117, 176, 229, 247, 253, 137, 185, 99, 164, 102, 147, 45, 66,
    231, 52, 141, 211, 194, 206, 246, 238, 56, 110, 78, 248, 63, 240, 189,
    93, 92, 51, 53, 183, 19, 171, 72, 50, 33, 104, 101, 69, 8, 252, 83, 120,
    76, 135, 85, 54, 202, 125, 188, 213, 96, 235, 136, 208, 162, 129, 190,
    132, 156, 38, 47, 1, 7, 254, 24, 4, 216, 131, 89, 21, 28, 133, 37, 153,
    149, 80, 170, 68, 6, 169, 234, 151 }
};

} // end of anonymous namespace

namespace isc {
namespace ha {

QueryFilter::QueryFilter(const HAConfigPtr& config)
    : config_(config), peers_(), scopes_(), active_servers_(0) {

    // Make sure that the configuration is valid. We make certain
    // assumptions about the availability of the servers' configurations
    // in the config_ structure.
    config_->validate();

    HAConfig::PeerConfigMap peers_map = config->getAllServersConfig();
    std::vector<HAConfig::PeerConfigPtr> backup_peers;

    // The returned configurations are not ordered. Let's iterate over them
    // and put them in the desired order.
    for (auto peer_pair = peers_map.begin(); peer_pair != peers_map.end(); ++peer_pair) {
        auto peer = peer_pair->second;
        // The primary server is always first on the list.
        if (peer->getRole() == HAConfig::PeerConfig::PRIMARY) {
            peers_.insert(peers_.begin(), peer);
            ++active_servers_;

        // The secondary server is always behind the primary server.
        } else if ((peer->getRole() == HAConfig::PeerConfig::SECONDARY) ||
                   (peer->getRole() == HAConfig::PeerConfig::STANDBY)) {
            peers_.push_back(peer);

            // If this is a secondary server, we're in the load balancing
            // mode, in which case we have two active servers.
            if (peer->getRole() == HAConfig::PeerConfig::SECONDARY) {
                ++active_servers_;
            }

        // If this is neither primary nor secondary/standby, it is a backup.
        } else {
            backup_peers.push_back(peer);
        }
    }

    // Append backup servers to the list.
    if (!backup_peers.empty()) {
        peers_.insert(peers_.end(), backup_peers.begin(), backup_peers.end());
    }

    // The query filter is initially setup to serve default scopes, i.e. for the
    // load balancing case the primary and secondary are responsible for their
    // own scopes. The backup servers are not responding to any queries. In the
    // hot standby mode, the primary server is responsible for the entire traffic.
    // The standby server is not responding.
    serveDefaultScopes();
}

void
QueryFilter::serveScope(const std::string& scope_name) {
    validateScopeName(scope_name);
    scopes_[scope_name] = true;
}

void
QueryFilter::serveScopeOnly(const std::string& scope_name) {
    validateScopeName(scope_name);
    serveNoScopes();
    serveScope(scope_name);
}

void
QueryFilter::serveScopes(const std::vector<std::string>& scopes) {
    // Remember currently enabled scopes in case we fail to process
    // the provided list of scopes.
    auto current_scopes = scopes_;
    try {
        serveNoScopes();
        for (size_t i = 0; i < scopes.size(); ++i) {
            serveScope(scopes[i]);
        }

    } catch (...) {
        // There was an error processing scopes list. Need to revert
        // to the previous configuration.
        scopes_ = current_scopes;
        throw;
    }
}

void
QueryFilter::serveDefaultScopes() {
    // Get this server instance configuration.
    HAConfig::PeerConfigPtr my_config = config_->getThisServerConfig();
    HAConfig::PeerConfig::Role my_role = my_config->getRole();

    // Clear scopes.
    serveNoScopes();

    // If I am primary or secondary, then I am only responsible for my own
    // scope.  If I am standby, I am not responsible for any scope.
    if ((my_role == HAConfig::PeerConfig::PRIMARY) ||
        (my_role == HAConfig::PeerConfig::SECONDARY)) {
        serveScope(my_config->getName());
    }
}

void
QueryFilter::serveFailoverScopes() {
    // Clear scopes.
    serveNoScopes();

    // Iterate over the roles of all servers to see which scope should
    // be enabled.
    for (auto peer = peers_.begin(); peer != peers_.end(); ++peer) {
        // The scope of the primary server must always be served. If we're
        // doing load balancing, the scope of the secondary server also
        // has to be served. Regardless if I am primary or secondary,
        // I will start serving queries from both scopes. If I am a
        // standby server, I will start serving the scope of the primary
        // server.
        if (((*peer)->getRole() == HAConfig::PeerConfig::PRIMARY) ||
            ((*peer)->getRole() == HAConfig::PeerConfig::SECONDARY)) {
            serveScope((*peer)->getName());
        }
    }
}

void
QueryFilter::serveNoScopes() {
    scopes_.clear();

    // Disable scope for each peer in the configuration.
    for (auto peer = peers_.begin(); peer != peers_.end(); ++peer) {
        scopes_[(*peer)->getName()] = false;
    }
}

bool
QueryFilter::amServingScope(const std::string& scope_name) const {
    auto scope = scopes_.find(scope_name);
    return ((scope == scopes_.end()) || (scope->second));
}

std::set<std::string>
QueryFilter::getServedScopes() const {
    std::set<std::string> scope_set;
    for (auto scope : scopes_) {
        if (scope.second) {
            scope_set.insert(scope.first);
        }
    }
    return (scope_set);
}

bool
QueryFilter::inScope(const dhcp::Pkt4Ptr& query4, std::string& scope_class) const {
    return (inScopeInternal(query4, scope_class));
}

bool
QueryFilter::inScope(const dhcp::Pkt6Ptr& query6, std::string& scope_class) const {
    return (inScopeInternal(query6, scope_class));
}

template<typename QueryPtrType>
bool
QueryFilter::inScopeInternal(const QueryPtrType& query,
                             std::string& scope_class) const {
    if (!query) {
        isc_throw(BadValue, "query must not be null");
    }

    int candidate_server = 0;

    // If we're doing load balancing we have to check if this query
    // belongs to us or the partner. If it belongs to a partner but
    // we're configured to serve this scope, we should accept it.
    if (config_->getHAMode() == HAConfig::LOAD_BALANCING) {
        candidate_server = loadBalance(query);
        // Malformed query received.
        if (candidate_server < 0) {
            return (false);
        }
    }

    auto scope = peers_[candidate_server]->getName();
    scope_class = makeScopeClass(scope);
    return ((candidate_server >= 0) && amServingScope(scope));
}

int
QueryFilter::loadBalance(const dhcp::Pkt4Ptr& query4) const {
    uint8_t lb_hash = 0;
    // Try to compute the hash by client identifier if the client
    // identifier has been specified.
    OptionPtr opt_client_id = query4->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt_client_id && !opt_client_id->getData().empty()) {
        const auto& client_id_key = opt_client_id->getData();
        lb_hash = loadBalanceHash(&client_id_key[0], client_id_key.size());

    } else {
        // No client identifier available. Use the HW address instead.
        HWAddrPtr hwaddr = query4->getHWAddr();
        if (hwaddr && !hwaddr->hwaddr_.empty()) {
            lb_hash = loadBalanceHash(&hwaddr->hwaddr_[0], hwaddr->hwaddr_.size());

        } else {
            // No client identifier and no HW address. Indicate an
            // error.
            std::stringstream xid;
            xid << "0x" << std::hex << query4->getTransid() << std::dec;
            LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_LOAD_BALANCING_IDENTIFIER_MISSING)
                .arg(xid.str());
            return (-1);
        }
    }

    // The hash value modulo number of active servers gives an index
    // of the server to process the packet.
    return (active_servers_ > 0 ? static_cast<int>(lb_hash % active_servers_) : -1);
}

int
QueryFilter::loadBalance(const dhcp::Pkt6Ptr& query6) const {
    uint8_t lb_hash = 0;
    // Compute the hash by DUID if the DUID.
    OptionPtr opt_duid = query6->getOption(D6O_CLIENTID);
    if (opt_duid && !opt_duid->getData().empty()) {
        const auto& duid_key = opt_duid->getData();
        lb_hash = loadBalanceHash(&duid_key[0], duid_key.size());

    } else {
        // No DUID. Indicate an error.
        std::stringstream xid;
        xid << "0x" << std::hex << query6->getTransid() << std::dec;
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_LOAD_BALANCING_DUID_MISSING)
            .arg(xid.str());
        return (-1);
    }

    // The hash value modulo number of active servers gives an index
    // of the server to process the packet.
    return (active_servers_ > 0 ? static_cast<int>(lb_hash % active_servers_) : -1);
}

uint8_t
QueryFilter::loadBalanceHash(const uint8_t* key, const size_t key_len) const {
    uint8_t hash  = static_cast<uint8_t>(key_len);

    for (auto i = key_len; i > 0;) {
        hash = loadb_mx_tbl[hash ^ key[--i]];
    }

    return (hash);
}

void
QueryFilter::validateScopeName(const std::string& scope_name) const {
    try {
        // If there is no such server, the scope name is invalid.
        static_cast<void>(config_->getPeerConfig(scope_name));

    } catch (...) {
        isc_throw(BadValue, "invalid server name specified '" << scope_name
                  << "' while enabling/disabling HA scopes");
    }
}

std::string
QueryFilter::makeScopeClass(const std::string& scope_name) const {
    return (std::string("HA_") + scope_name);
}


} // end of namespace isc::ha
} // end of namespace isc
