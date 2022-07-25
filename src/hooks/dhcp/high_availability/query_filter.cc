// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/multi_threading_mgr.h>

#include <array>
#include <iostream>
#include <sstream>

using namespace isc::dhcp;
using namespace isc::log;
using namespace isc::util;

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

/// @brief Table indicating which DHCPv4 message types are of interest to HA.
std::array<bool, DHCP_TYPES_EOF> v4_ha_types = {
    false,  // DHCP_NOTYPE          = 0
    true,   // DHCPDISCOVER         = 1
    false,  // DHCPOFFER            = 2
    true,   // DHCPREQUEST          = 3
    true,   // DHCPDECLINE          = 4
    false,  // DHCPACK              = 5
    false,  // DHCPNAK              = 6
    true,   // DHCPRELEASE          = 7
    true,   // DHCPINFORM           = 8
    false,  // DHCPFORCERENEW       = 9
    false,  // DHCPLEASEQUERY       = 10
    false,  // DHCPLEASEUNASSIGNED  = 11
    false,  // DHCPLEASEUNKNOWN     = 12
    false,  // DHCPLEASEACTIVE      = 13
    false,  // DHCPBULKLEASEQUERY   = 14
    false,  // DHCPLEASEQUERYDONE   = 15
    false,  // DHCPACTIVELEASEQUERY = 16
    false,  // DHCPLEASEQUERYSTATUS = 17
    false   // DHCPTLS              = 18
};

/// @brief Table indicating which DHCPv6 message types are of interest to HA.
std::array<bool, DHCPV6_TYPES_EOF> v6_ha_types = {
    false,  // DHCPV6_NOTYPE               = 0
    true,   // DHCPV6_SOLICIT              = 1
    false,  // DHCPV6_ADVERTISE            = 2
    true,   // DHCPV6_REQUEST              = 3
    true,   // DHCPV6_CONFIRM              = 4
    true,   // DHCPV6_RENEW                = 5
    true,   // DHCPV6_REBIND               = 6
    false,  // DHCPV6_REPLY                = 7
    true,   // DHCPV6_RELEASE              = 8
    true,   // DHCPV6_DECLINE              = 9
    false,  // DHCPV6_RECONFIGURE          = 10
    false,  // DHCPV6_INFORMATION_REQUEST  = 11
    false,  // DHCPV6_RELAY_FORW           = 12
    false,  // DHCPV6_RELAY_REPL           = 13
    false,  // DHCPV6_LEASEQUERY           = 14
    false,  // DHCPV6_LEASEQUERY_REPLY     = 15
    false,  // DHCPV6_LEASEQUERY_DONE      = 16
    false,  // DHCPV6_LEASEQUERY_DATA      = 17
    false,  // DHCPV6_RECONFIGURE_REQUEST  = 18
    false,  // DHCPV6_RECONFIGURE_REPLY    = 19
    /// @todo There is some question as to whether DHCPV4_QUERY should get load-balanced
    /// or not. It may not provide sufficient information to properly scope it. For now
    /// we will not load-balance them.
    false,  // DHCPV6_DHCPV4_QUERY         = 20
    false,  // DHCPV6_DHCPV4_RESPONSE      = 21
    false,  // DHCPV6_ACTIVELEASEQUERY     = 22
    false,  // DHCPV6_STARTTLS             = 23
    false,  // DHCPV6_BNDUPD               = 24
    false,  // DHCPV6_BNDREPLY             = 25
    false,  // DHCPV6_POOLREQ              = 26
    false,  // DHCPV6_POOLRESP             = 27
    false,  // DHCPV6_UPDREQ               = 28
    false,  // DHCPV6_UPDREQALL            = 29
    false,  // DHCPV6_UPDDONE              = 30
    false,  // DHCPV6_CONNECT              = 31
    false,  // DHCPV6_CONNECTREPLY         = 32
    false,  // DHCPV6_DISCONNECT           = 33
    false,  // DHCPV6_STATE                = 34
    false   // DHCPV6_CONTACT              = 35
};

} // end of anonymous namespace

namespace isc {
namespace ha {

QueryFilter::QueryFilter(const HAConfigPtr& config)
    : config_(config), peers_(), scopes_(), active_servers_(0),
      mutex_(new std::mutex) {

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
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        serveScopeInternal(scope_name);
    } else {
        serveScopeInternal(scope_name);
    }
}

void
QueryFilter::serveScopeInternal(const std::string& scope_name) {
    validateScopeName(scope_name);
    scopes_[scope_name] = true;
}

void
QueryFilter::serveScopeOnly(const std::string& scope_name) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        serveScopeOnlyInternal(scope_name);
    } else {
        serveScopeOnlyInternal(scope_name);
    }
}

void
QueryFilter::serveScopeOnlyInternal(const std::string& scope_name) {
    validateScopeName(scope_name);
    serveNoScopesInternal();
    serveScopeInternal(scope_name);
}

void
QueryFilter::serveScopes(const std::vector<std::string>& scopes) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        serveScopesInternal(scopes);
    } else {
        serveScopesInternal(scopes);
    }
}

void
QueryFilter::serveScopesInternal(const std::vector<std::string>& scopes) {
    // Remember currently enabled scopes in case we fail to process
    // the provided list of scopes.
    auto current_scopes = scopes_;
    try {
        serveNoScopesInternal();
        for (size_t i = 0; i < scopes.size(); ++i) {
            serveScopeInternal(scopes[i]);
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
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        serveDefaultScopesInternal();
    } else {
        serveDefaultScopesInternal();
    }
}

void
QueryFilter::serveDefaultScopesInternal() {
    // Get this server instance configuration.
    HAConfig::PeerConfigPtr my_config = config_->getThisServerConfig();
    HAConfig::PeerConfig::Role my_role = my_config->getRole();

    // Clear scopes.
    serveNoScopesInternal();

    // If I am primary or secondary, then I am only responsible for my own
    // scope.  If I am standby, I am not responsible for any scope.
    if ((my_role == HAConfig::PeerConfig::PRIMARY) ||
        (my_role == HAConfig::PeerConfig::SECONDARY)) {
        serveScopeInternal(my_config->getName());
    }
}

void
QueryFilter::serveFailoverScopes() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        serveFailoverScopesInternal();
    } else {
        serveFailoverScopesInternal();
    }
}

void
QueryFilter::serveFailoverScopesInternal() {
    // Clear scopes.
    serveNoScopesInternal();

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
            serveScopeInternal((*peer)->getName());
        }
    }
}

void
QueryFilter::serveNoScopes() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        serveNoScopesInternal();
    } else {
        serveNoScopesInternal();
    }
}

void
QueryFilter::serveNoScopesInternal() {
    scopes_.clear();

    // Disable scope for each peer in the configuration.
    for (auto peer = peers_.begin(); peer != peers_.end(); ++peer) {
        scopes_[(*peer)->getName()] = false;
    }
}

bool
QueryFilter::amServingScope(const std::string& scope_name) const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (amServingScopeInternal(scope_name));
    } else {
        return (amServingScopeInternal(scope_name));
    }
}

bool
QueryFilter::amServingScopeInternal(const std::string& scope_name) const {
    auto scope = scopes_.find(scope_name);
    return ((scope == scopes_.end()) || (scope->second));
}

std::set<std::string>
QueryFilter::getServedScopes() const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (getServedScopesInternal());
    } else {
        return (getServedScopesInternal());
    }
}

std::set<std::string>
QueryFilter::getServedScopesInternal() const {
    std::set<std::string> scope_set;
    for (auto scope : scopes_) {
        if (scope.second) {
            scope_set.insert(scope.first);
        }
    }
    return (scope_set);
}

bool
QueryFilter::isHaType(const dhcp::Pkt4Ptr& query4) {
    auto msg_type = query4->getType();
    return (msg_type < v4_ha_types.size() && v4_ha_types[msg_type]);
}

bool
QueryFilter::isHaType(const dhcp::Pkt6Ptr& query) {
    auto msg_type = query->getType();
    return (msg_type < v6_ha_types.size() && v6_ha_types[msg_type]);
}


bool
QueryFilter::inScope(const dhcp::Pkt4Ptr& query4, std::string& scope_class) const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (inScopeInternal(query4, scope_class));
    } else {
        return (inScopeInternal(query4, scope_class));
    }
}

bool
QueryFilter::inScope(const dhcp::Pkt6Ptr& query6, std::string& scope_class) const {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(*mutex_);
        return (inScopeInternal(query6, scope_class));
    } else {
        return (inScopeInternal(query6, scope_class));
    }
}

template<typename QueryPtrType>
bool
QueryFilter::inScopeInternal(const QueryPtrType& query,
                             std::string& scope_class) const {
    if (!query) {
        isc_throw(BadValue, "query must not be null");
    }


    // If it's not a type HA cares about, it's in scope for this peer.
    if (!isHaType(query)) {
        auto scope = peers_[0]->getName();
        scope_class = makeScopeClass(scope);
        return (true);
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
    return ((candidate_server >= 0) && amServingScopeInternal(scope));
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
