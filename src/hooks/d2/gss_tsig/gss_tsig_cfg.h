// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GSS_TSIG_CFG_H
#define GSS_TSIG_CFG_H

#include <asiodns/io_fetch.h>
#include <cc/cfg_to_element.h>
#include <cc/simple_parser.h>
#include <cc/user_context.h>
#include <d2srv/d2_cfg_mgr.h>

#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/random_access_index.hpp>

#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <vector>

namespace isc {
namespace gss_tsig {

/// @brief GSS-TSIG hook configuration for a server.
class DnsServer : public isc::data::CfgToElement, public isc::data::UserContext {
public:
    /// @brief This table defines all server parameters.
    static const isc::data::SimpleKeywords SERVER_PARAMETERS;

    /// @brief Server TKEY exchange statistics names.
    ///
    /// - gss-tsig-key-created
    /// - tkey-sent
    /// - tkey-success
    /// - tkey-timeout
    /// - tkey-error
    static const std::list<std::string> STAT_NAMES;

    /// @brief Constructor.
    ///
    /// A server is mainly recognized using its address and port.
    ///
    /// @param id An identifier.
    /// @param domains A list of DNS domains.
    /// @param ip_address The server IP address.
    /// @param port The server port (default 53).
    DnsServer(const std::string& id,
              const std::set<std::string>& domains,
              const isc::asiolink::IOAddress& ip_address,
              uint16_t port = isc::d2::DnsServerInfo::STANDARD_DNS_PORT);

    /// @brief Destructor.
    ///
    /// Remove the server statistics.
    virtual ~DnsServer();

    /// @brief Reset statistics.
    virtual void resetStats();

    /// @brief Get the ID.
    ///
    /// @return the ID.
    std::string getID() const {
        return (id_);
    }

    /// @brief Set the ID.
    ///
    /// @param id A new ID.
    void setID(const std::string& id) {
        id_ = id;
    }

    /// @brief Get the server IP address.
    ///
    /// @return the server IP address.
    const isc::asiolink::IOAddress& getIpAddress() const {
        return (ip_address_);
    }

    /// @brief Get timer used to rekey or to retry on error.
    ///
    /// @return The timer used to rekey or to retry on error.
    isc::asiolink::IntervalTimerPtr& getTimer() {
        return (timer_);
    }

    /// @brief Get the server port.
    ///
    /// @return the server port.
    uint16_t getPort() const {
        return (port_);
    }

    /// @brief Get the server info list.
    ///
    /// @return the server info list.
    const isc::d2::DnsServerInfoStorage& getServerInfos() const {
        return (server_infos_);
    }

    /// @brief Add a server info to the list.
    ///
    /// @param server_info The new server info to add to the list.
    void addServerInfo(isc::d2::DnsServerInfoPtr server_info) {
        server_infos_.push_back(server_info);
    }

    /// @brief Clear the server info list.
    void clearServerInfos() {
        server_infos_.clear();
    }

    /// @brief Convert the list of DNS domains to the server info list.
    ///
    /// For each domain in the list adds the corresponding server.
    /// An empty list means to add all servers.
    ///
    /// @param d2_config D2 configuration.
    /// @throw isc::NotFound if a domain of the list is not served.
    void buildServerInfo(isc::d2::D2CfgContextPtr d2_config);

    /// @brief Get the DNS server principal.
    ///
    /// @return the DNS server principal.
    const std::string& getServerPrincipal() const {
        return (server_principal_);
    }

    /// @brief Set the DNS server principal.
    ///
    /// @param server_principal A new DNS server principal.
    void setServerPrincipal(const std::string& server_principal) {
        server_principal_ = server_principal;
    }

    /// @brief Get the GSS-TSIG key name suffix.
    ///
    /// @return the GSS-TSIG key name suffix.
    const std::string& getKeyNameSuffix() const {
        return (key_name_suffix_);
    }

    /// @brief Set the GSS-TSIG key name suffix.
    ///
    /// @param key_name_suffix A new GSS-TSIG key name suffix.
    void setKeyNameSuffix(const std::string& key_name_suffix) {
        key_name_suffix_ = key_name_suffix;
        checkKeyNameSuffix();
    }

    /// @brief Build the GSS-TSIG key name suffix.
    ///
    /// The GSS-TSIG key name suffix is the DNS part of the DNS server
    /// principal i.e. the sub-string between '/' and '@'.
    ///
    /// @throw BadValue when the DNS server principal has not the expected
    /// format (this allows an error at argument parse time).
    void buildKeyNameSuffix();

    /// @brief Check and fix the GSS-TSIG key name suffix.
    ///
    /// As a side effect a trailing dot can be added, e.g. when the
    /// suffix was built from a Kerberos principal where usually
    /// the domain part does not have one.
    /// @note: if we want to canonize GSS-TSIG key name suffix this is
    /// the right place to do this.
    void checkKeyNameSuffix();

    /// @brief Get the client/credentials principal.
    ///
    /// @return the client/credentials principal.
    const std::string& getClientPrincipal() const {
        return (cred_principal_);
    }

    /// @brief Set the client/credentials principal.
    ///
    /// @param cred_principal A new client/credentials principal.
    void setClientPrincipal(const std::string& cred_principal) {
        cred_principal_ = cred_principal;
    }

    /// @brief Get the TKEY lifetime.
    ///
    /// @return the TKEY lifetime (expressed in seconds).
    uint32_t getKeyLifetime() const {
        return (tkey_lifetime_);
    }

    /// @brief Get the GSS (anti) replay flag.
    ///
    /// @return the GSS (anti) replay flag.
    bool getGssReplayFlag() const {
        return (gss_replay_flag_);
    }

    /// @brief Set the GSS (anti) replay flag.
    ///
    /// @param flag A new (anti) replay flag value.
    void setGssReplayFlag(bool flag) {
        gss_replay_flag_ = flag;
    }

    /// @brief Get the GSS sequence flag.
    ///
    /// @return the GSS sequence flag.
    bool getGssSequenceFlag() const {
        return (gss_sequence_flag_);
    }

    /// @brief Set the GSS sequence flag.
    ///
    /// @param flag A new sequence flag value.
    void setGssSequenceFlag(bool flag) {
        gss_sequence_flag_ = flag;
    }

    /// @brief Set the TKEY lifetime.
    ///
    /// @param tkey_lifetime A new TKEY lifetime (expressed in seconds).
    void setKeyLifetime(uint32_t tkey_lifetime) {
        tkey_lifetime_ = tkey_lifetime;
    }

    /// @brief Get the rekey interval.
    ///
    /// @return the rekey interval (expressed in seconds).
    uint32_t getRekeyInterval() const {
        return (rekey_interval_);
    }

    /// @brief Set the rekey interval.
    ///
    /// @param rekey_interval A new rekey interval (expressed in seconds).
    void setRekeyInterval(uint32_t rekey_interval) {
        rekey_interval_ = rekey_interval;
    }

    /// @brief Get the retry interval.
    ///
    /// @return the retry interval (expressed in seconds).
    uint32_t getRetryInterval() const {
        return (retry_interval_);
    }

    /// @brief Set the retry interval.
    ///
    /// @param retry_interval A new retry interval (expressed in seconds).
    void setRetryInterval(uint32_t retry_interval) {
        retry_interval_ = retry_interval;
    }

    /// @brief Get the TKEY protocol.
    ///
    /// @return the TKEY protocol.
    isc::asiodns::IOFetch::Protocol getKeyProto() const {
        return (tkey_proto_);
    }

    /// @brief Set the TKEY protocol.
    ///
    /// @param tkey_proto A new TKEY protocol.
    void setKeyProto(isc::asiodns::IOFetch::Protocol tkey_proto) {
        tkey_proto_ = tkey_proto;
    }

    /// @brief Get the fallback flag.
    ///
    /// @return the fallback flag.
    bool getFallback() const {
        return (fallback_);
    }

    /// @brief Set the fallback flag.
    ///
    /// @param fallback A new fallback flag.
    void setFallback(bool fallback) {
        fallback_ = fallback;
    }

    /// @brief Get the TKEY exchange timeout.
    ///
    /// @return the TKEY exchange timeout (expressed in milliseconds).
    uint32_t getExchangeTimeout() const {
        return (exchange_timeout_);
    }

    /// @brief Set the TKEY exchange timeout.
    ///
    /// @param exchange_timeout A new TKEY exchange timeout (expressed in
    /// milliseconds).
    void setExchangeTimeout(uint32_t exchange_timeout) {
        exchange_timeout_ = exchange_timeout;
    }

    /// @brief Unparse a DNS server object.
    ///
    /// Used to get the full state of a DNS server.
    /// @note: the GSS-TSIG key list is added by command handlers.
    ///
    /// @return a pointer to unparsed DNS server object.
    isc::data::ElementPtr toElement() const;

    /// @brief The default TKEY lifetime (expressed in seconds).
    ///
    /// Default value for TKEY lifetime: 3600 seconds (1 hour).
    static constexpr size_t DEFAULT_KEY_LIFETIME = 3600;

    /// @brief The rekey timer interval (expressed in seconds).
    ///
    /// Default value for rekey timer: 2700 seconds (45 minutes).
    static constexpr size_t DEFAULT_REKEY_INTERVAL = 2700;

    /// @brief The retry timer interval (expressed in seconds).
    ///
    /// Default value for retry timer: 120 seconds (2 minutes).
    static constexpr size_t DEFAULT_RETRY_INTERVAL = 120;

    /// @brief The default TKEY exchange timeout (expressed in milliseconds).
    ///
    /// Default value for TKEY exchange timeout: 3000 milliseconds (3 seconds).
    static constexpr size_t DEFAULT_EXCHANGE_TIMEOUT = 3000;

private:
    /// @brief Initialize server statistics.
    void initStats();

    /// @brief Remove server statistics.
    void removeStats();

    /// @brief Convert a D2 DNS domain to a server info.
    ///
    /// @param d2_dns_domain A D2 DNS domain.
    /// @throw @c isc::NotFound if a domain of the list is not served.
    void buildServerInfo(isc::d2::DdnsDomainPtr d2_dns_domain);

    /// @brief The ID.
    std::string id_;

    /// @brief The list of domains.
    std::set<std::string> domains_;

    /// @brief The server IP address.
    isc::asiolink::IOAddress ip_address_;

    /// @brief The server port.
    uint16_t port_;

    /// @brief The server info list.
    isc::d2::DnsServerInfoStorage server_infos_;

    /// @brief The DNS server principal.
    std::string server_principal_;

    /// @brief The GSS-TSIG key name suffix.
    std::string key_name_suffix_;

    /// @brief The client/credentials principal.
    std::string cred_principal_;

    /// @brief The GSS (anti) replay flag.
    bool gss_replay_flag_;

    /// @brief The GSS sequence flag.
    bool gss_sequence_flag_;

    /// @brief The TKEY lifetime (expressed in seconds).
    uint32_t tkey_lifetime_;

    /// @brief The rekey interval (expressed in seconds).
    uint32_t rekey_interval_;

    /// @brief The retry interval (expressed in seconds).
    uint32_t retry_interval_;

    /// @brief The TKEY protocol.
    isc::asiodns::IOFetch::Protocol tkey_proto_;

    /// @brief The fallback flag (governs behavior when no key is available).
    bool fallback_;

    /// @brief The TKEY timeout (expressed in milliseconds).
    uint32_t exchange_timeout_;

    /// @brief The interval timer (used to rekey or to retry on error).
    isc::asiolink::IntervalTimerPtr timer_;
};

/// @brief A pointer to a DNS server.
typedef boost::shared_ptr<DnsServer> DnsServerPtr;

/// @brief Tag for the random access index for searching DNS server.
struct DnsServerIndexTag { };

/// @brief Tag for the id access index for searching DNS server.
struct DnsServerIdTag { };

/// @brief A list of DNS server.
typedef boost::multi_index_container<
    // Multi index container holding pointers to the DNS servers.
    DnsServerPtr,
    // The following holds all indexes.
    boost::multi_index::indexed_by<
        // First index allows the random access (vector).
        boost::multi_index::random_access<
            boost::multi_index::tag<DnsServerIndexTag>
        >,
        // Second index allows the id access.
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<DnsServerIdTag>,
            boost::multi_index::const_mem_fun<DnsServer, std::string,
                                              &DnsServer::getID>
        >
    >
> DnsServerList;

/// @brief A map of DNS server info and DNS server.
typedef std::map<isc::d2::DnsServerInfoPtr, DnsServerPtr> DnsServerRevMap;

/// @brief GSS-TSIG hook configuration.
class GssTsigCfg {
public:
    /// @brief This table defines all global parameters.
    static const isc::data::SimpleKeywords GLOBAL_PARAMETERS;

    /// @brief Constructor.
    GssTsigCfg();

    /// @brief Destructor.
    virtual ~GssTsigCfg();

    /// @brief Get the DNS server list.
    ///
    /// @return the DNS server list.
    const DnsServerList& getServerList() const {
        return (servers_);
    }

    /// @brief Add a DNS server to the list.
    ///
    /// @note: the caller must check if the server ID is already used.
    ///
    /// @param server A new DNS server to add to the list.
    void addServer(DnsServerPtr server) {
        servers_.push_back(server);
    }

    /// @brief Get the DNS server reverse map.
    ///
    /// @return the DNS server reverse map.
    const DnsServerRevMap& getServerRevMap() const {
        return (servers_rev_map_);
    }

    /// @brief Get the DNS server from a server info.
    ///
    /// @param server_info The server info to find.
    /// @return the DNS server or null if not found.
    DnsServerPtr getServer(const isc::d2::DnsServerInfoPtr& server_info) const;

    /// @brief Get the DNS server from its ID.
    ///
    /// @param id The server ID.
    /// @return the DNS server or null if not found.
    DnsServerPtr getServer(const std::string& id) const;

    /// @brief Clear the DNS server list and reverse map.
    void clearServers() {
        servers_.clear();
        servers_rev_map_.clear();
    }

    /// @brief Build the reverse map.
    ///
    /// @param d2_config D2 configuration.
    void buildServerRevMap(isc::d2::D2CfgContextPtr d2_config);

    /// @brief Get the client key table specification.
    ///
    /// @return the client key table specification.
    const std::string& getClientKeyTab() const {
        return (client_keytab_);
    }

    /// @brief Set the client key table specification.
    ///
    /// @param client_keytab A new client key table specification.
    void setClientKeyTab(const std::string& client_keytab) {
        client_keytab_ = client_keytab;
    }

    /// @brief Get the credentials cache specification.
    ///
    /// @return the credentials cache specification.
    const std::string& getCredsCache() const {
        return (creds_cache_);
    }

    /// @brief Set the credentials cache specification.
    ///
    /// @param creds_cache A new credentials cache specification.
    void setCredsCache(const std::string& creds_cache) {
        creds_cache_ = creds_cache;
    }

    /// @brief Configure.
    ///
    /// @param params A map element with parameters.
    /// @throw BadValue and similar exceptions on error.
    void configure(isc::data::ConstElementPtr params);

    /// @brief Get the maximum TKEY lifetime.
    ///
    /// @return the maximum TKEY lifetime.
    uint32_t getMaxKeyLifetime() const {
        return (max_tkey_lifetime_);
    }

    /// @brief Set the maximum TKEY lifetime.
    ///
    /// @param max_tkey_lifetime A new maximum TKEY lifetime.
    void setMaxKeyLifetime(uint32_t max_tkey_lifetime) {
        max_tkey_lifetime_ = max_tkey_lifetime;
    }

private:
    /// @brief The DNS server list.
    DnsServerList servers_;

    /// @brief The DNS server reverse map.
    DnsServerRevMap servers_rev_map_;

    /// @brief The client key table specification.
    std::string client_keytab_;

    /// @brief The credentials cache specification.
    std::string creds_cache_;

    /// @brief The maximum TKEY lifetime.
    uint32_t max_tkey_lifetime_;
};

} // end of namespace isc::gss_tsig
} // end of namespace isc

#endif // GSS_TSIG_CFG_H
