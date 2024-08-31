// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QUERY_FILTER_H
#define QUERY_FILTER_H

#include <ha_config.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

#include <boost/scoped_ptr.hpp>

#include <cstdint>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace isc {
namespace ha {

/// @brief DHCP query filtering class.
///
/// This class is a central point of information about distribution of the
/// DHCP queries processed by the servers within HA setup. It also implements
/// load balancing of the DHCP queries, when configured to do so.
///
/// The query filter uses a term "scope" to identify group of DHCP queries
/// processed by a given server. Currently, we support load balancing
/// between two servers. Therefore, in this mode of operation, there are two
/// scopes named after servers responsible for processing packets belonging
/// to those scopes, e.g. "server1" and "server2".
///
/// In the hot-standby mode, there is only one server processing incoming
/// DHCP queries. Thus, there is only one scope named after the primary
/// server, e.g. "server1".
///
/// This class allows for assigning the server to process queries belonging
/// to various scopes. For example: when a failure of the partner server
/// is detected, the @c QueryFilter::serveFailoverScopes is called to
/// indicate that this server instance should start handling queries
/// belonging to the scope(s) of the server which have died. Converesly,
/// a call to @c QueryFilter::serveDefaultScopes reverts to the default
/// state.
///
/// When DHCP query is received, the @c QueryFilter class is used to determine
/// whether this query should be processed by this server. The
/// @c QueryFilter::inScope methods return boolean value indicating
/// whether the query should be processed or not. If not, the query is
/// dropped.
///
/// The server administrator may force the server to start processing queries
/// from the selected scopes, e.g. the administrator may manually instruct the
/// backup server to take over the traffic of the primary and secondary servers.
/// The 'ha-scopes' command is sent in such case, which enables/disables
/// scopes within this class instance.
class QueryFilter {
public:

    /// @brief Constructor.
    ///
    /// This constructor puts HA peers configurations in the following order:
    /// - primary server configuration,
    /// - secondary or standby server configuration,
    /// - backup servers configurations
    ///
    /// It also sets the @c active_servers_ value to the number of active
    /// servers (responding to DHCP queries) for a given HA mode. In our case,
    /// this is 2 for the load balancing case and 1 for the hot-standby.
    /// Such organization of the configurations makes it easier for the
    /// load balancing algorithm to distribute queries between active servers.
    /// In our simple case, the load balancing algorithm can produce a value
    /// of 0 or 1, which points to a primary or secondary server in the
    /// configuration vector.
    ///
    /// @param config pointer to the HA configuration.
    /// @throw HAConfigValidationError if provided configuration is invalid.
    explicit QueryFilter(const HAConfigPtr& config);

    /// @brief Enable scope.
    ///
    /// Starts serving queries from the specified scope. It doesn't affect
    /// other scopes.
    ///
    /// @param scope_name name of the scope/server to be enabled.
    /// @throw BadValue if scope name doesn't match any of the server names.
    void serveScope(const std::string& scope_name);

    /// @brief Enable scope and disable all other scopes.
    ///
    /// Starts serving queries from the specified scope. Disable all other
    /// scopes.
    ///
    /// @param scope_name name of the scope/server to be enabled.
    /// @throw BadValue if scope name doesn't match any of the server names.
    void serveScopeOnly(const std::string& scope_name);

    /// @brief Enables selected scopes.
    ///
    /// All non listed scopes are disabled.
    ///
    /// @param scopes vector of scope names to be enabled.
    void serveScopes(const std::vector<std::string>& scopes);

    /// @brief Serve default scopes for the given HA mode.
    ///
    /// If this server is primary or secondary (load balancing), the scope
    /// of this server is enabled. All other scopes are disabled.
    void serveDefaultScopes();

    /// @brief Enable scopes required in failover case.
    ///
    /// In the load balancing case, the scopes of the primary and secondary
    /// servers are enabled (this server will handle the entire traffic).
    /// In the hot standby case, the primary server's scope is enabled
    /// (this server will handle the entire traffic normally processed by
    /// the primary server).
    void serveFailoverScopes();

    /// @brief Disables all scopes.
    void serveNoScopes();

    /// @brief Checks if this server instance is configured to process traffic
    /// belonging to a particular scope.
    ///
    /// @param scope_name name of the scope/server.
    /// @return true if the scope is enabled.
    bool amServingScope(const std::string& scope_name) const;

    /// @brief Returns served scopes.
    ///
    /// This method is mostly useful for testing purposes.
    std::set<std::string> getServedScopes() const;

    /// @brief Checks if this server should process the DHCPv4 query.
    ///
    /// This method uses a table of DHCPv4 message types to determine whether or
    /// not a query needs further analysis to determine which HA server
    /// should handle it or if it should simply be processed by this server.
    ///
    /// For message types that qualify (e.g. DHCPDISCOVER, DHCPREQUEST, etc),
    /// it then takes into account enabled scopes for this server and HA mode
    /// to determine whether this query should be processed. It triggers load
    /// balancing when load balancing mode is enabled.
    ///
    /// Non-qualifying message types (e.g. DHCPLEASEQUERY) are passed
    /// through for handling by this server.
    ///
    /// @param query4 pointer to the DHCPv4 query instance.
    /// @param [out] scope_class name of the class which corresponds to the
    /// name of the server which owns the packet. Those class names are used
    /// in subnets, pools and network configurations to associate them with
    /// different servers.
    ///
    /// @return true if the specified query should be processed by this
    /// server, false otherwise.
    bool inScope(const dhcp::Pkt4Ptr& query4, std::string& scope_class) const;

    /// @brief Checks if this server should process the DHCPv6 query.
    ///
    /// This method uses a table of DHCPv6 message types to determine whether or
    /// not a query needs further analysis to determine which HA server
    /// should handle it or if it should simply be processed by this server.
    ///
    /// For message types that qualify (e.g. DHCPV6_SOLICIT, DHCPV6_REQUEST, etc),
    /// it then takes into account enabled scopes for this server and HA mode
    /// to determine whether this query should be processed. It triggers load
    /// balancing when load balancing mode is enabled.
    ///
    /// Non-qualifying message types (e.g. DHCPV6_LEASEQUERY) are passed through
    /// for handling by this server.
    ///
    /// @param query6 pointer to the DHCPv6 query instance.
    /// @param [out] scope_class name of the class which corresponds to the
    /// name of the server which owns the packet. Those class names are used
    /// in subnets, pools and network configurations to associate them with
    /// different servers.
    ///
    /// @return true if the specified query should be processed by this
    /// server, false otherwise.
    bool inScope(const dhcp::Pkt6Ptr& query6, std::string& scope_class) const;

    /// @brief Determines if a DHCPv4 query is a message type HA should process.
    ///
    /// @param query4 DHCPv4 packet to test. Must not be null.
    ///
    /// @return
    static bool isHaType(const dhcp::Pkt4Ptr& query4);

    /// @brief Determines if a DHCPv6 query is a message type HA should process.
    ///
    /// @param query6 DHCPv6 packet to test. Must not be null.
    ///
    /// @return
    static bool isHaType(const dhcp::Pkt6Ptr& query6);

private:
    /// @brief Enable scope.
    ///
    /// Should be called in a thread safe context.
    ///
    /// Starts serving queries from the specified scope. It doesn't affect
    /// other scopes.
    ///
    /// @param scope_name name of the scope/server to be enabled.
    /// @throw BadValue if scope name doesn't match any of the server names.
    void serveScopeInternal(const std::string& scope_name);

    /// @brief Enable scope and disable all other scopes.
    ///
    /// Should be called in a thread safe context.
    ///
    /// Starts serving queries from the specified scope. Disable all other
    /// scopes.
    ///
    /// @param scope_name name of the scope/server to be enabled.
    /// @throw BadValue if scope name doesn't match any of the server names.
    void serveScopeOnlyInternal(const std::string& scope_name);

    /// @brief Enables selected scopes.
    ///
    /// Should be called in a thread safe context.
    ///
    /// All non listed scopes are disabled.
    ///
    /// @param scopes vector of scope names to be enabled.
    void serveScopesInternal(const std::vector<std::string>& scopes);

    /// @brief Serve default scopes for the given HA mode.
    ///
    /// Should be called in a thread safe context.
    ///
    /// If this server is primary or secondary (load balancing), the scope
    /// of this server is enabled. All other scopes are disabled.
    void serveDefaultScopesInternal();

    /// @brief Enable scopes required in failover case.
    ///
    /// Should be called in a thread safe context.
    ///
    /// In the load balancing case, the scopes of the primary and secondary
    /// servers are enabled (this server will handle the entire traffic).
    /// In the hot standby case, the primary server's scope is enabled
    /// (this server will handle the entire traffic normally processed by
    /// the primary server).
    void serveFailoverScopesInternal();

    /// @brief Disables all scopes.
    ///
    /// Should be called in a thread safe context.
    void serveNoScopesInternal();

    /// @brief Checks if this server instance is configured to process traffic
    /// belonging to a particular scope.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @param scope_name name of the scope/server.
    /// @return true if the scope is enabled.
    bool amServingScopeInternal(const std::string& scope_name) const;

    /// @brief Returns served scopes.
    ///
    /// Should be called in a thread safe context.
    ///
    /// This method is mostly useful for testing purposes.
    std::set<std::string> getServedScopesInternal() const;

    /// @brief Generic implementation of the @c inScope function for DHCPv4
    /// and DHCPv6 queries.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @tparam QueryPtrType type of the query, i.e. DHCPv4 or DHCPv6 query.
    /// @param query pointer to the DHCP query instance.
    /// @param [out] scope_class name of the class which corresponds to the
    /// name of the server which owns the packet. Those class names are used
    /// in subnets, pools and network configurations to associate them with
    /// different servers.
    ///
    /// @return true if the specified query should be processed by this
    /// server, false otherwise.
    template<typename QueryPtrType>
    bool inScopeInternal(const QueryPtrType& query, std::string& scope_class) const;

protected:

    /// @brief Performs load balancing of the DHCPv4 queries.
    ///
    /// This method returns an index of the server configuration
    /// held within @c peers_ vector. This points to a server
    /// which should process the given query. Currently, we only
    /// support load balancing between two servers, therefore this
    /// value should be 0 or 1.
    ///
    /// @param query4 pointer to the DHCPv4 query instance.
    /// @return Index of the server which should process the query. It
    /// returns negative value if the query is malformed, i.e. contains
    /// no HW address and no client identifier.
    int loadBalance(const dhcp::Pkt4Ptr& query4) const;

    /// @brief Performs load balancing of the DHCPv6 queries.
    ///
    /// This method returns an index of the server configuration
    /// held within @c peers_ vector. This points to a server
    /// which should process the given query. Currently, we only
    /// support load balancing between two servers, therefore this
    /// value should be 0 or 1.
    ///
    /// @param query6 pointer to the DHCPv6 query instance.
    /// @return Index of the server which should process the query. It
    /// returns negative value if the query is malformed, i.e. contains
    /// no DUID.
    int loadBalance(const dhcp::Pkt6Ptr& query6) const;

    /// @brief Compute load balancing hash.
    ///
    /// The load balancing hash is computed according to section 6
    /// if RFC3074.
    ///
    /// @param key identifier used to compute a hash, i.e. HW address
    /// or client identifier.
    /// @param key_len length of the key.
    ///
    /// @return Computed hash value.
    uint8_t loadBalanceHash(const uint8_t* key, const size_t key_len) const;

    /// @brief Checks if the scope name matches a name of any of the
    /// configured servers.
    ///
    /// @param scope_name scope name to be tested.
    /// @throw BadValue if no server is found for a given scope name.
    void validateScopeName(const std::string& scope_name) const;

    /// @brief Returns scope class name for the specified scope name.
    ///
    /// When the server is designated to process a received DHCP query, it
    /// is often required to assign a class to this query which corresponds
    /// to the particular server. This class name is associated with the
    /// pools, subnets and/or networks which this server should hand out
    /// leases from.
    ///
    /// This function converts scope name to the class name by prefixing
    /// the scope name with "ha_" string.
    ///
    /// @param scope_name scope name to be converted to class name.
    ///
    /// @return Scope class name.
    std::string makeScopeClass(const std::string& scope_name) const;

    /// @brief Pointer to the HA configuration.
    HAConfigPtr config_;

    /// @brief Vector of HA peers configurations.
    std::vector<HAConfig::PeerConfigPtr> peers_;

    /// @brief Holds mapping of the scope names to the flag which indicates
    /// if the scopes are enabled or disabled.
    std::map<std::string, bool> scopes_;

    /// @brief Number of the active servers in the given HA mode.
    int active_servers_;

    /// @brief Mutex to protect the internal state.
    boost::scoped_ptr<std::mutex> mutex_;
};

} // end of namespace isc::ha
} // end of namespace isc

#endif // QUERY_FILTER_H
