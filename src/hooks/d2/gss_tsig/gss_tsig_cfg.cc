// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/name.h>
#include <gss_tsig_cfg.h>
#include <stats/stats_mgr.h>

#include <limits>

using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::stats;
using namespace std;

namespace isc {
namespace gss_tsig {

const SimpleKeywords DnsServer::SERVER_PARAMETERS = {
    { "id",                 Element::string },
    { "domain-names",       Element::list },
    { "ip-address",         Element::string },
    { "port",               Element::integer },
    { "server-principal",   Element::string },
    { "client-principal",   Element::string },
    { "gss-replay-flag",    Element::boolean },
    { "gss-sequence-flag",  Element::boolean },
    { "tkey-lifetime",      Element::integer },
    { "rekey-interval",     Element::integer },
    { "retry-interval",     Element::integer },
    { "tkey-protocol",      Element::string },
    { "fallback",           Element::boolean },
    { "exchange-timeout",   Element::integer },
    { "user-context",       Element::map },
    { "comment",            Element::string }
};

const list<string> DnsServer::STAT_NAMES = {
    "gss-tsig-key-created",
    "tkey-sent",
    "tkey-success",
    "tkey-timeout",
    "tkey-error"
};

DnsServer::DnsServer(const string& id, const set<string>& domains,
                     const IOAddress& ip_address, uint16_t port)
    : id_(id), domains_(domains), ip_address_(ip_address), port_(port),
      server_infos_(), server_principal_(""), key_name_suffix_(""),
      cred_principal_(""), gss_replay_flag_(true),
      gss_sequence_flag_(false), tkey_lifetime_(DEFAULT_KEY_LIFETIME),
      rekey_interval_(DEFAULT_REKEY_INTERVAL),
      retry_interval_(DEFAULT_RETRY_INTERVAL), tkey_proto_(IOFetch::TCP),
      fallback_(false), exchange_timeout_(DEFAULT_EXCHANGE_TIMEOUT), timer_() {
    static_assert(DEFAULT_REKEY_INTERVAL < DEFAULT_KEY_LIFETIME,
                  "DEFAULT_REKEY_INTERVAL < DEFAULT_KEY_LIFETIME");
    static_assert(DEFAULT_RETRY_INTERVAL < DEFAULT_REKEY_INTERVAL,
                  "DEFAULT_RETRY_INTERVAL < DEFAULT_REKEY_INTERVAL");
    initStats();
}

DnsServer::~DnsServer() {
    removeStats();
}

void
DnsServer::initStats() {
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& name : DnsServer::STAT_NAMES) {
        const string& sname = StatsMgr::generateName("server", id_, name);
        stats_mgr.setValue(sname, static_cast<int64_t>(0));
    }
}

void
DnsServer::removeStats() {
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& name : DnsServer::STAT_NAMES) {
        const string& sname = StatsMgr::generateName("server", id_, name);
        stats_mgr.del(sname);
    }
}

void
DnsServer::resetStats() {
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& name : DnsServer::STAT_NAMES) {
        const string& sname = StatsMgr::generateName("server", id_, name);
        stats_mgr.reset(sname);
    }
}

void
DnsServer::buildKeyNameSuffix() {
    string suffix = server_principal_;
    size_t pos = suffix.find_first_of("/");
    if (pos != string::npos) {
        suffix = suffix.substr(pos + 1);
    }
    pos = suffix.find_last_of("@");
    if (pos != string::npos) {
        suffix = suffix.substr(0, pos);
    }
    if (suffix.empty()) {
        isc_throw(BadValue, "can't get the GSS-TSIG key name suffix from "
                  << "the DNS server principal '" << server_principal_
                  << "'");
    }
    key_name_suffix_ = string("sig-") + suffix;
    checkKeyNameSuffix();
}

void
DnsServer::checkKeyNameSuffix() {
    // 32 bits mean at most 10 digits
    string tname = "1234567890." + key_name_suffix_;
    try {
        dns::Name dname(tname);
        string nname = dname.toText();
        size_t pos = nname.find_first_of(".");
        if (pos != 10) {
            isc_throw(Unexpected, "string to FQDN failed (dot at "
                      << pos << " instead 10)");
        }
        key_name_suffix_ = nname.substr(pos + 1);
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "check of the GSS-TSIG key name suffix '"
                  << key_name_suffix_ << "' failed: " << ex.what());
    }
}

void
DnsServer::buildServerInfo(isc::d2::D2CfgContextPtr d2_config) {
    if (!d2_config) {
        isc_throw(D2CfgError, "empty D2 config");
    }
    if (!server_infos_.empty()) {
        isc_throw(D2CfgError, "server info list is not empty");
    }
    set<string> seen;
    DdnsDomainListMgrPtr d2_dom_mgr = d2_config->getForwardMgr();
    DdnsDomainMapPtr d2_dom_map;
    if (d2_dom_mgr) {
        d2_dom_map = d2_dom_mgr->getDomains();
    }
    if (d2_dom_map) {
        for (auto const& it : *d2_dom_map) {
            if (!domains_.empty()) {
                if (domains_.count(it.first) == 0) {
                    continue;
                }
                static_cast<void>(seen.insert(it.first));
            }
            buildServerInfo(it.second);
        }
    }
    d2_dom_mgr = d2_config->getReverseMgr();
    if (d2_dom_mgr) {
        d2_dom_map = d2_dom_mgr->getDomains();
    } else {
        d2_dom_map = DdnsDomainMapPtr();
    }
    if (d2_dom_map) {
        for (auto const& it : *d2_dom_map) {
            if (!domains_.empty()) {
                if (domains_.count(it.first) == 0) {
                    continue;
                }
                static_cast<void>(seen.insert(it.first));
            }
            buildServerInfo(it.second);
        }
    }
    if (getServerInfos().empty()) {
        isc_throw(NotFound, "server info can't be found");
    }
    if (!domains_.empty()) {
        for (auto const& domain : domains_) {
            if (seen.count(domain) == 0) {
                isc_throw(NotFound, "domain '" << domain << "' can't be found");
            }
        }
    }
}

void
DnsServer::buildServerInfo(isc::d2::DdnsDomainPtr d2_dns_domain) {
    if (!d2_dns_domain) {
        return;
    }
    DnsServerInfoStoragePtr servers = d2_dns_domain->getServers();
    if (!servers) {
        return;
    }
    for (auto const& info : *servers) {
        if (!info) {
            continue;
        }
        if (!info->isEnabled()) {
            continue;
        }
        if (info->getIpAddress() != getIpAddress()) {
            continue;
        }
        if (info->getPort() != getPort()) {
            continue;
        }
        addServerInfo(info);
    }
}

ElementPtr
DnsServer::toElement() const {
    ElementPtr map = Element::createMap();

    // Add user-context.
    contextToElement(map);

    // ID..
    map->set("id", Element::create(getID()));

    // Domains.
    if (!domains_.empty()) {
        ElementPtr domains = Element::createList();
        for (auto const& domain : domains_) {
            domains->add(Element::create(domain));
        }
        map->set("domain-names", domains);
    }

    // IP address.
    map->set("ip-address", Element::create(ip_address_.toText()));

    // Port.
    map->set("port", Element::create(static_cast<int>(port_)));

    // Server principal.
    map->set("server-principal", Element::create(server_principal_));

    // GSS-TSIG key name suffix.
    map->set("key-name-suffix", Element::create(key_name_suffix_));

    // Client principal.
    if (!cred_principal_.empty()) {
        map->set("client-principal", Element::create(cred_principal_));
    }

    // GSS (anti) replay flag.
    map->set("gss-replay-flag", Element::create(gss_replay_flag_));

    // GSS sequence flag.
    map->set("gss-sequence-flag", Element::create(gss_sequence_flag_));

    // TKEY lifetime.
    map->set("tkey-lifetime",
             Element::create(static_cast<long long>(tkey_lifetime_)));

    // Rekey interval.
    map->set("rekey-interval",
             Element::create(static_cast<long long>(rekey_interval_)));

    // Retry interval.
    map->set("retry-interval",
             Element::create(static_cast<long long>(retry_interval_)));

    // TKEY protocol.
    string proto = (tkey_proto_ == IOFetch::TCP ? "TCP" : "UDP");
    map->set("tkey-protocol", Element::create(proto));

    // Fallback.
    map->set("fallback", Element::create(fallback_));

    // TKEY exchange timeout.
    map->set("exchange-timeout",
             Element::create(static_cast<long long>(exchange_timeout_)));

    return (map);
}

const SimpleKeywords GssTsigCfg::GLOBAL_PARAMETERS = {
    { "server-principal",   Element::string },
    { "client-principal",   Element::string },
    { "client-keytab",      Element::string },
    { "credentials-cache",  Element::string },
    { "gss-replay-flag",    Element::boolean },
    { "gss-sequence-flag",  Element::boolean },
    { "tkey-lifetime",      Element::integer },
    { "rekey-interval",     Element::integer },
    { "retry-interval",     Element::integer },
    { "tkey-protocol",      Element::string },
    { "fallback",           Element::boolean },
    { "exchange-timeout",   Element::integer },
    { "servers",            Element::list },
    { "user-context",       Element::map },
    { "comment",            Element::string }
};

GssTsigCfg::GssTsigCfg()
    : servers_(), servers_rev_map_(), client_keytab_(""), creds_cache_(""),
      max_tkey_lifetime_(0) {
}

GssTsigCfg::~GssTsigCfg() {
}

DnsServerPtr
GssTsigCfg::getServer(const isc::d2::DnsServerInfoPtr& server_info) const {
    auto candidate = servers_rev_map_.find(server_info);
    if (candidate == servers_rev_map_.end()) {
        return (DnsServerPtr());
    }
    return (candidate->second);
}

DnsServerPtr
GssTsigCfg::getServer(const string& id) const {
    auto const& index = servers_.template get<DnsServerIdTag>();
    auto const it = index.find(id);
    if (it == index.cend()) {
        return (DnsServerPtr());
    }
    return (*it);
}

void
GssTsigCfg::buildServerRevMap(D2CfgContextPtr d2_config) {
    if (!servers_rev_map_.empty()) {
        isc_throw(D2CfgError, "server reverse map is not empty");
    }
    for (auto const& server : getServerList()) {
        server->buildServerInfo(d2_config);
        for (auto const& info : server->getServerInfos()) {
            if (servers_rev_map_.count(info) > 0) {
                isc_throw(D2CfgError, "duplicate");
            }
            servers_rev_map_[info] = server;
        }
    }
}

void
GssTsigCfg::configure(ConstElementPtr params) {
    if (!params) {
        isc_throw(BadValue, "gss_tsig parameters entry is mandatory");
    }
    if (params->getType() != Element::map) {
        isc_throw(BadValue, "gss_tsig parameters entry must be a map");
    }
    try {
        SimpleParser::checkKeywords(GLOBAL_PARAMETERS, params);
    } catch(const DhcpConfigError& ex) {
        isc_throw(BadValue, "gss_tsig " << ex.what() << " ("
                  << params->getPosition() << ")");
    }

    ConstElementPtr client_keytab = params->get("client-keytab");
    if (client_keytab) {
        setClientKeyTab(client_keytab->stringValue());
    }

    ConstElementPtr credentials_cache = params->get("credentials-cache");
    if (credentials_cache) {
        setCredsCache(credentials_cache->stringValue());
    }

    string retry_interval_origin = "default";
    string retry_interval_location = "";
    int64_t global_retry_val = DnsServer::DEFAULT_RETRY_INTERVAL;
    ConstElementPtr global_retry_interval = params->get("retry-interval");
    if (global_retry_interval) {
        retry_interval_origin = "global";
        retry_interval_location += " (";
        retry_interval_location += global_retry_interval->getPosition().str();
        retry_interval_location += ")";
        global_retry_val = global_retry_interval->intValue();
        if ((global_retry_val < 0) ||
            (global_retry_val > numeric_limits<uint32_t>::max())) {
            isc_throw(BadValue, "'retry-interval' parameter is out of "
                      "range [0.." << numeric_limits<uint32_t>::max()
                      << "]" << retry_interval_location);
        }
    }

    string rekey_interval_origin = "default";
    string rekey_interval_location = "";
    int64_t global_rekey_val = DnsServer::DEFAULT_REKEY_INTERVAL;
    ConstElementPtr global_rekey_interval = params->get("rekey-interval");
    if (global_rekey_interval) {
        rekey_interval_origin = "global";
        rekey_interval_location += " (";
        rekey_interval_location += global_rekey_interval->getPosition().str();
        rekey_interval_location += ")";
        global_rekey_val = global_rekey_interval->intValue();
        if ((global_rekey_val < 0) ||
            (global_rekey_val > numeric_limits<uint32_t>::max())) {
            isc_throw(BadValue, "'rekey-interval' parameter is out of "
                      "range [0.." << numeric_limits<uint32_t>::max()
                      << "]" << rekey_interval_location);
        }
    }

    string tkey_lifetime_origin = "default";
    string tkey_lifetime_location = "";
    int64_t global_tkey_lifetime_val = DnsServer::DEFAULT_KEY_LIFETIME;
    ConstElementPtr global_tkey_lifetime = params->get("tkey-lifetime");
    if (global_tkey_lifetime) {
        tkey_lifetime_origin = "global";
        tkey_lifetime_location += " (";
        tkey_lifetime_location += global_tkey_lifetime->getPosition().str();
        tkey_lifetime_location += ")";
        global_tkey_lifetime_val = global_tkey_lifetime->intValue();
        if ((global_tkey_lifetime_val < 0) ||
            (global_tkey_lifetime_val > numeric_limits<uint32_t>::max())) {
            isc_throw(BadValue, "'tkey-lifetime' parameter is out of "
                      "range [0.." << numeric_limits<uint32_t>::max()
                      << "]" << tkey_lifetime_location);
        }
    }

    if (global_retry_val >= global_rekey_val) {
        isc_throw(BadValue, "the " << retry_interval_origin
                  << " 'retry-interval' parameter"
                  << retry_interval_location << " must be smaller then the "
                  << rekey_interval_origin << " 'rekey-interval' parameter"
                  << retry_interval_location << ": range [0.."
                  << global_rekey_val << "]");
    }

    if (global_rekey_val >= global_tkey_lifetime_val) {
        isc_throw(BadValue, "the " << rekey_interval_origin
                  << " 'rekey-interval' parameter"
                  << rekey_interval_location << " must be smaller than the "
                  << tkey_lifetime_origin << " 'tkey-lifetime' parameter"
                  << tkey_lifetime_location << ": range [0.."
                  << global_tkey_lifetime_val << "]");
    }

    ConstElementPtr global_tkey_proto = params->get("tkey-protocol");
    if (global_tkey_proto) {
        string val = global_tkey_proto->stringValue();
        if ((val != "UDP") && (val != "TCP")) {
            isc_throw(BadValue, "'tkey-protocol' parameter must be UDP "
                      "or TCP (" << global_tkey_proto->getPosition() << ")");
        }
    }

    ConstElementPtr global_fallback = params->get("fallback");

    ConstElementPtr global_tkey_timeout = params->get("exchange-timeout");
    if (global_tkey_timeout) {
        int64_t val = global_tkey_timeout->intValue();
        if ((val < 0) || (val > numeric_limits<uint32_t>::max())) {
            isc_throw(BadValue, "'exchange-timeout' parameter is out of "
                      "range [0.." << numeric_limits<uint32_t>::max()
                      << "] (" << global_tkey_timeout->getPosition() << ")");
        }
    }

    ConstElementPtr servers = params->get("servers");
    if (!servers) {
        return;
    }

    uint32_t max_tkey_lifetime = 0;
    for (auto const& map : servers->listValue()) {
        if (!map) {
            continue;
        }
        if (map->getType() != Element::map) {
            isc_throw(BadValue, "'servers' parameter must be a list of "
                      "maps (" << map->getPosition() << ")");
        }
        try {
            SimpleParser::checkKeywords(DnsServer::SERVER_PARAMETERS, map);
        } catch (const DhcpConfigError& ex) {
            isc_throw(BadValue, "gss_tsig server " << ex.what() << " ("
                      << map->getPosition() << ")");
        }

        ConstElementPtr id_elem = map->get("id");
        if (!id_elem) {
            isc_throw(BadValue, "'id' parameter is required in "
                      "gss_tsig server entry (" << map->getPosition() << ")");
        }
        const string& id = id_elem->stringValue();
        if (id.empty()) {
            isc_throw(BadValue, "'id' parameter must be not empty in "
                      "gss_tsig server entry (" << map->getPosition() << ")");
        }
        if (getServer(id)) {
            isc_throw(BadValue, "'" << id << "' id is already used in "
                      "gss_tsig server entry (" << map->getPosition() << ")");
        }

        ConstElementPtr domains_list = map->get("domain-names");
        set<string> domains;
        if (domains_list && !domains_list->empty()) {
            for (auto const& domain : domains_list->listValue()) {
                if (!domain) {
                    continue;
                }
                if (domain->getType() != Element::string) {
                    isc_throw(BadValue, "gss_tsig server 'domain-names' list "
                              << "must contain only strings ("
                              << domain->getPosition() << ")");
                }
                // Ignore duplicates.
                static_cast<void>(domains.insert(domain->stringValue()));
            }
        }

        DnsServerPtr srv;
        ConstElementPtr ip_address = map->get("ip-address");
        if (!ip_address) {
            isc_throw(BadValue, "'ip-address' parameter is required in "
                      "gss_tsig server entry (" << map->getPosition() << ")");
        }
        try {
            IOAddress addr(ip_address->stringValue());
            if (map->contains("port")) {
                int64_t port(SimpleParser::getInteger(map, "port", 0,
                                                      numeric_limits<uint16_t>::max()));
                srv.reset(new DnsServer(id, domains, addr,
                                        static_cast<uint16_t>(port)));
            } else {
                srv.reset(new DnsServer(id, domains, addr));
            }
        } catch (const DhcpConfigError& ex) {
            isc_throw(BadValue, "gss_tsig bad server entry: " << ex.what());
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "gss_tsig bad server entry: " << ex.what()
                      << " (" << map->getPosition() << ")");
        }

        ConstElementPtr server_principal = map->get("server-principal");
        bool server_principal_global = false;
        if (!server_principal) {
            server_principal = params->get("server-principal");
            server_principal_global = true;
        }
        if (!server_principal) {
            isc_throw(BadValue, "'server-principal' parameter is required in "
                      "gss_tsig server entry (" << map->getPosition() << ")");
        }
        srv->setServerPrincipal(server_principal->stringValue());
        try {
            srv->buildKeyNameSuffix();
        } catch (const std::exception& ex) {
            if (server_principal_global) {
                isc_throw(BadValue, "gss_tsig bad server-principal parameter: "
                          << ex.what() << " ("
                          << server_principal->getPosition() << ")");
            } else {
                isc_throw(BadValue, "gss_tsig bad server entry: " << ex.what()
                          << " (" << server_principal->getPosition() << ")");
            }
        }

        ConstElementPtr gss_replay_flag = map->get("gss-replay-flag");
        if (!gss_replay_flag) {
            gss_replay_flag = params->get("gss-replay-flag");
        }
        if (gss_replay_flag) {
            srv->setGssReplayFlag(gss_replay_flag->boolValue());
        }

        ConstElementPtr gss_sequence_flag = map->get("gss-sequence-flag");
        if (!gss_sequence_flag) {
            gss_sequence_flag = params->get("gss-sequence-flag");
        }
        if (gss_sequence_flag) {
            srv->setGssSequenceFlag(gss_sequence_flag->boolValue());
        }

        ConstElementPtr cred_principal = map->get("client-principal");
        if (!cred_principal) {
            cred_principal = params->get("client-principal");
        }
        if (cred_principal) {
            srv->setClientPrincipal(cred_principal->stringValue());
        }

        retry_interval_location = "";
        ConstElementPtr retry_interval = map->get("retry-interval");
        if (!retry_interval) {
            retry_interval = global_retry_interval;
        } else {
            retry_interval_origin = "server";
        }
        int64_t retry_val = DnsServer::DEFAULT_RETRY_INTERVAL;
        if (retry_interval) {
            retry_interval_location += " (";
            retry_interval_location += retry_interval->getPosition().str();
            retry_interval_location += ")";
            retry_val = retry_interval->intValue();
            if ((retry_val < 0) ||
                (retry_val > numeric_limits<uint32_t>::max())) {
                isc_throw(BadValue, "'retry-interval' parameter is out of "
                          "range [0.." << numeric_limits<uint32_t>::max()
                          << "]" << retry_interval_location);
            }
            srv->setRetryInterval(retry_val);
        }

        rekey_interval_location = "";
        ConstElementPtr rekey_interval = map->get("rekey-interval");
        if (!rekey_interval) {
            rekey_interval = global_rekey_interval;
        } else {
            rekey_interval_origin = "server";
        }
        int64_t rekey_val = DnsServer::DEFAULT_REKEY_INTERVAL;
        if (rekey_interval) {
            rekey_interval_location += " (";
            rekey_interval_location += rekey_interval->getPosition().str();
            rekey_interval_location += ")";
            rekey_val = rekey_interval->intValue();
            if ((rekey_val < 0) ||
                (rekey_val > numeric_limits<uint32_t>::max())) {
                isc_throw(BadValue, "'rekey-interval' parameter is out of "
                          "range [0.." << numeric_limits<uint32_t>::max()
                          << "]" << rekey_interval_location);
            }
            srv->setRekeyInterval(rekey_val);
        }

        tkey_lifetime_location = "";
        ConstElementPtr tkey_lifetime = map->get("tkey-lifetime");
        if (!tkey_lifetime) {
            tkey_lifetime = global_tkey_lifetime;
        } else {
            tkey_lifetime_origin = "server";
        }
        int64_t tkey_lifetime_val = DnsServer::DEFAULT_KEY_LIFETIME;
        if (tkey_lifetime) {
            tkey_lifetime_location += " (";
            tkey_lifetime_location += tkey_lifetime->getPosition().str();
            tkey_lifetime_location += ")";
            tkey_lifetime_val = tkey_lifetime->intValue();
            if ((tkey_lifetime_val < 0) ||
                (tkey_lifetime_val > numeric_limits<uint32_t>::max())) {
                isc_throw(BadValue, "'tkey-lifetime' parameter is out of "
                          "range [0.." << numeric_limits<uint32_t>::max()
                          << "]" << tkey_lifetime_location);
            }
            srv->setKeyLifetime(tkey_lifetime_val);
        }
        if (tkey_lifetime_val > max_tkey_lifetime) {
            max_tkey_lifetime = tkey_lifetime_val;
        }

        if (retry_val >= rekey_val) {
            isc_throw(BadValue, "the " << retry_interval_origin
                      << " 'retry-interval' parameter"
                      << retry_interval_location << " must be smaller then the "
                      << rekey_interval_origin << " 'rekey-interval' parameter"
                      << retry_interval_location << ": range [0.."
                      << rekey_val << "]");
        }

        if (rekey_val >= tkey_lifetime_val) {
            isc_throw(BadValue, "the " << rekey_interval_origin
                      << " 'rekey-interval' parameter"
                      << rekey_interval_location << " must be smaller than the "
                      << tkey_lifetime_origin << " 'tkey-lifetime' parameter"
                      << tkey_lifetime_location << ": range [0.."
                      << tkey_lifetime_val << "]");
        }

        ConstElementPtr tkey_proto = map->get("tkey-protocol");
        if (!tkey_proto) {
            tkey_proto = global_tkey_proto;
        }
        if (tkey_proto) {
            string val = tkey_proto->stringValue();
            if (val == "UDP") {
                srv->setKeyProto(IOFetch::UDP);
            } else if (val == "TCP") {
                srv->setKeyProto(IOFetch::TCP);
            } else {
                isc_throw(BadValue, "'tkey-protocol' parameter must be UDP "
                          "or TCP (" << tkey_proto->getPosition() << ")");
            }
        }

        ConstElementPtr fallback = map->get("fallback");
        if (!fallback) {
            fallback = global_fallback;
        }
        if (fallback) {
            srv->setFallback(fallback->boolValue());
        }

        ConstElementPtr tkey_timeout = map->get("exchange-timeout");
        if (!tkey_timeout) {
            tkey_timeout = global_tkey_timeout;
        }
        if (tkey_timeout) {
            int64_t val = tkey_timeout->intValue();
            if ((val < 0) || (val > numeric_limits<uint32_t>::max())) {
                isc_throw(BadValue, "'exchange-timeout' parameter is out of "
                          "range [0.." << numeric_limits<uint32_t>::max()
                          << "] (" << tkey_timeout->getPosition() << ")");
            }
            srv->setExchangeTimeout(val);
        }

        addServer(srv);
    }
    setMaxKeyLifetime(max_tkey_lifetime);
}

} // end of namespace isc::gss_tsig
} // end of namespace isc
