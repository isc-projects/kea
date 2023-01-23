// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2srv/d2_log.h>
#include <d2srv/d2_cfg_mgr.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <sstream>
#include <string>

using namespace isc::process;
using namespace isc::data;

namespace isc {
namespace d2 {

// *********************** D2Params  *************************

D2Params::D2Params(const isc::asiolink::IOAddress& ip_address,
                   const size_t port,
                   const size_t dns_server_timeout,
                   const dhcp_ddns::NameChangeProtocol& ncr_protocol,
                   const dhcp_ddns::NameChangeFormat& ncr_format)
    : ip_address_(ip_address),
    port_(port),
    dns_server_timeout_(dns_server_timeout),
    ncr_protocol_(ncr_protocol),
    ncr_format_(ncr_format) {
    validateContents();
}

D2Params::D2Params()
    : ip_address_(isc::asiolink::IOAddress("127.0.0.1")),
     port_(53001), dns_server_timeout_(500),
     ncr_protocol_(dhcp_ddns::NCR_UDP),
     ncr_format_(dhcp_ddns::FMT_JSON) {
    validateContents();
}

D2Params::~D2Params(){};

void
D2Params::validateContents() {
    if ((ip_address_.toText() == "0.0.0.0") || (ip_address_.toText() == "::")) {
        isc_throw(D2CfgError,
                  "D2Params: IP address cannot be \"" << ip_address_ << "\"");
    }

    if (port_ == 0) {
        isc_throw(D2CfgError, "D2Params: port cannot be 0");
    }

    if (dns_server_timeout_ < 1) {
        isc_throw(D2CfgError,
                  "D2Params: DNS server timeout must be larger than 0");
    }

    if (ncr_format_ != dhcp_ddns::FMT_JSON) {
        isc_throw(D2CfgError, "D2Params: NCR Format:"
                  << dhcp_ddns::ncrFormatToString(ncr_format_)
                  << " is not yet supported");
    }

    if (ncr_protocol_ != dhcp_ddns::NCR_UDP) {
        isc_throw(D2CfgError, "D2Params: NCR Protocol:"
                  << dhcp_ddns::ncrProtocolToString(ncr_protocol_)
                  << " is not yet supported");
    }
}

std::string
D2Params::getConfigSummary() const {
    std::ostringstream s;
    s << "listening on " << getIpAddress() << ", port " << getPort()
      << ", using " << ncrProtocolToString(ncr_protocol_);
    return (s.str());
}

bool
D2Params::operator == (const D2Params& other) const {
    return ((ip_address_ == other.ip_address_) &&
            (port_ == other.port_) &&
            (dns_server_timeout_ == other.dns_server_timeout_) &&
            (ncr_protocol_ == other.ncr_protocol_) &&
            (ncr_format_ == other.ncr_format_));
}

bool
D2Params::operator != (const D2Params& other) const {
    return (!(*this == other));
}

std::string
D2Params::toText() const {
    std::ostringstream stream;

    stream << ", ip-address: " << ip_address_.toText()
           << ", port: " << port_
           << ", dns-server-timeout_: " << dns_server_timeout_
           << ", ncr-protocol: "
           << dhcp_ddns::ncrProtocolToString(ncr_protocol_)
           << ", ncr-format: " << ncr_format_
           << dhcp_ddns::ncrFormatToString(ncr_format_);

    return (stream.str());
}

std::ostream&
operator<<(std::ostream& os, const D2Params& config) {
    os << config.toText();
    return (os);
}

// *********************** TSIGKeyInfo  *************************
// Note these values match corresponding values for Bind9's
// dnssec-keygen
const char* TSIGKeyInfo::HMAC_MD5_STR = "HMAC-MD5";
const char* TSIGKeyInfo::HMAC_SHA1_STR = "HMAC-SHA1";
const char* TSIGKeyInfo::HMAC_SHA224_STR = "HMAC-SHA224";
const char* TSIGKeyInfo::HMAC_SHA256_STR = "HMAC-SHA256";
const char* TSIGKeyInfo::HMAC_SHA384_STR = "HMAC-SHA384";
const char* TSIGKeyInfo::HMAC_SHA512_STR = "HMAC-SHA512";

TSIGKeyInfo::TSIGKeyInfo(const std::string& name, const std::string& algorithm,
                         const std::string& secret, uint32_t digestbits)
    :name_(name), algorithm_(algorithm), secret_(secret),
     digestbits_(digestbits), tsig_key_() {
    remakeKey();
}

TSIGKeyInfo::~TSIGKeyInfo() {
}

const dns::Name&
TSIGKeyInfo::stringToAlgorithmName(const std::string& algorithm_id) {
    if (boost::iequals(algorithm_id, HMAC_MD5_STR)) {
        return (dns::TSIGKey::HMACMD5_NAME());
    } else if (boost::iequals(algorithm_id, HMAC_SHA1_STR)) {
        return (dns::TSIGKey::HMACSHA1_NAME());
    } else if (boost::iequals(algorithm_id, HMAC_SHA224_STR)) {
        return (dns::TSIGKey::HMACSHA224_NAME());
    } else if (boost::iequals(algorithm_id, HMAC_SHA256_STR)) {
        return (dns::TSIGKey::HMACSHA256_NAME());
    } else if (boost::iequals(algorithm_id, HMAC_SHA384_STR)) {
        return (dns::TSIGKey::HMACSHA384_NAME());
    } else if (boost::iequals(algorithm_id, HMAC_SHA512_STR)) {
        return (dns::TSIGKey::HMACSHA512_NAME());
    }

    isc_throw(BadValue, "Unknown TSIG Key algorithm: " << algorithm_id);
}

void
TSIGKeyInfo::remakeKey() {
    try {
        // Since our secret value is base64 encoded already, we need to
        // build the input string for the appropriate D2TsigKey constructor.
        // If secret isn't a valid base64 value, the constructor will throw.
        std::ostringstream stream;
        stream << dns::Name(name_).toText() << ":"
               << secret_ << ":"
               << stringToAlgorithmName(algorithm_);
        if (digestbits_ > 0) {
            stream << ":" << digestbits_;
        }

        tsig_key_.reset(new D2TsigKey(stream.str()));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "Cannot make D2TsigKey: " << ex.what());
    }
}

ElementPtr
TSIGKeyInfo::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set name
    result->set("name", Element::create(name_));
    // Set algorithm
    result->set("algorithm", Element::create(algorithm_));
    // Set secret
    result->set("secret", Element::create(secret_));
    // Set digest-bits
    result->set("digest-bits",
                Element::create(static_cast<int64_t>(digestbits_)));

    return (result);
}

// *********************** DnsServerInfo  *************************
DnsServerInfo::DnsServerInfo(const std::string& hostname,
                             isc::asiolink::IOAddress ip_address,
                             uint32_t port,
                             bool enabled,
                             const TSIGKeyInfoPtr& tsig_key_info,
                             bool inherited_key)
    : hostname_(hostname), ip_address_(ip_address), port_(port),
      enabled_(enabled), tsig_key_info_(tsig_key_info),
      inherited_key_(inherited_key) {
}

DnsServerInfo::~DnsServerInfo() {
}

const std::string
DnsServerInfo::getKeyName() const {
    if (tsig_key_info_) {
        return (tsig_key_info_->getName());
    }

    return ("");
}

std::string
DnsServerInfo::toText() const {
    std::ostringstream stream;
    stream << (getIpAddress().toText()) << " port:" << getPort();
    return (stream.str());
}

ElementPtr
DnsServerInfo::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set hostname
    result->set("hostname", Element::create(hostname_));
    // Set ip-address
    result->set("ip-address", Element::create(ip_address_.toText()));
    // Set port
    result->set("port", Element::create(static_cast<int64_t>(port_)));
    // Set key-name
    if (tsig_key_info_ && !inherited_key_) {
        result->set("key-name", Element::create(tsig_key_info_->getName()));
    }

    return (result);
}

std::ostream&
operator<<(std::ostream& os, const DnsServerInfo& server) {
    os << server.toText();
    return (os);
}

// *********************** DdnsDomain  *************************

DdnsDomain::DdnsDomain(const std::string& name,
                       DnsServerInfoStoragePtr servers,
                       const std::string& key_name)
    : name_(name), servers_(servers), key_name_(key_name) {
}

DdnsDomain::~DdnsDomain() {
}

ElementPtr
DdnsDomain::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user-context
    contextToElement(result);
    // Set name
    result->set("name", Element::create(name_));
    // Set servers
    ElementPtr servers = Element::createList();
    for (DnsServerInfoStorage::const_iterator server = servers_->begin();
         server != servers_->end(); ++server) {
        ElementPtr dns_server = (*server)->toElement();
        servers->add(dns_server);
    }
    // the dns server list may not be empty
    if (!servers->empty()) {
        result->set("dns-servers", servers);
    }
    // Set key-name
    if (!key_name_.empty()) {
        result->set("key-name", Element::create(key_name_));
    }

    return (result);
}

// *********************** DdnsDomainLstMgr  *************************

const char* DdnsDomainListMgr::wildcard_domain_name_ = "*";

DdnsDomainListMgr::DdnsDomainListMgr(const std::string& name) : name_(name),
    domains_(new DdnsDomainMap()) {
}


DdnsDomainListMgr::~DdnsDomainListMgr () {
}

void
DdnsDomainListMgr::setDomains(DdnsDomainMapPtr domains) {
    if (!domains) {
        isc_throw(D2CfgError,
                  "DdnsDomainListMgr::setDomains: Domain list may not be null");
    }

    domains_ = domains;

    // Look for the wild card domain. If present, set the member variable
    // to remember it.  This saves us from having to look for it every time
    // we attempt a match.
    DdnsDomainMap::iterator gotit = domains_->find(wildcard_domain_name_);
    if (gotit != domains_->end()) {
            wildcard_domain_ = gotit->second;
    }
}

bool
DdnsDomainListMgr::matchDomain(const std::string& fqdn, DdnsDomainPtr& domain) {
    // First check the case of one domain to rule them all.
    if ((size() == 1) && (wildcard_domain_)) {
        domain = wildcard_domain_;
        return (true);
    }

    // Iterate over the domain map looking for the domain which matches
    // the longest portion of the given fqdn.

    size_t req_len = fqdn.size();
    size_t match_len = 0;
    DdnsDomainMapPair map_pair;
    DdnsDomainPtr best_match;
    BOOST_FOREACH (map_pair, *domains_) {
        std::string domain_name = map_pair.first;
        size_t dom_len = domain_name.size();

        // If the domain name is longer than the fqdn, then it cant be match.
        if (req_len < dom_len) {
            continue;
        }

        // If the lengths are identical and the names match we're done.
        if (req_len == dom_len) {
            if (boost::iequals(fqdn, domain_name)) {
                // exact match, done
                domain = map_pair.second;
                return (true);
            }
        } else {
            // The fqdn is longer than the domain name.  Adjust the start
            // point of comparison by the excess in length.  Only do the
            // comparison if the adjustment lands on a boundary. This
            // prevents "onetwo.net" from matching "two.net".
            size_t offset = req_len - dom_len;
            if ((fqdn[offset - 1] == '.')  &&
               (boost::iequals(fqdn.substr(offset), domain_name))) {
                // Fqdn contains domain name, keep it if its better than
                // any we have matched so far.
                if (dom_len > match_len) {
                    match_len = dom_len;
                    best_match = map_pair.second;
                }
            }
        }
    }

    if (!best_match) {
        // There's no match. If they specified a wild card domain use it
        // otherwise there's no domain for this entry.
        if (wildcard_domain_) {
            domain = wildcard_domain_;
            return (true);
        }

        LOG_WARN(dhcp_to_d2_logger, DHCP_DDNS_NO_MATCH).arg(fqdn);
        return (false);
    }

    domain = best_match;
    return (true);
}

ElementPtr
DdnsDomainListMgr::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate on ddns domains
    for (DdnsDomainMap::const_iterator domain = domains_->begin();
         domain != domains_->end(); ++domain) {
        ElementPtr ddns_domain = domain->second->toElement();
        result->add(ddns_domain);
    }

    return (result);
}

// *************************** PARSERS ***********************************

// *********************** TSIGKeyInfoParser  *************************

TSIGKeyInfoPtr
TSIGKeyInfoParser::parse(ConstElementPtr key_config) {
    std::string name = getString(key_config, "name");
    std::string algorithm = getString(key_config, "algorithm");
    uint32_t digestbits = getInteger(key_config, "digest-bits");
    std::string secret = getString(key_config, "secret");
    ConstElementPtr user_context = key_config->get("user-context");

    // Algorithm must be valid.
    try {
        TSIGKeyInfo::stringToAlgorithmName(algorithm);
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "tsig-key : " << ex.what()
                  << " (" << getPosition("algorithm", key_config) << ")");
    }

    // Non-zero digest-bits must be an integral number of octets, greater
    // than 80 and at least half of the algorithm key length. It defaults
    // to zero and JSON parsing ensures it's a multiple of 8.
    if ((digestbits > 0) &&
        ((digestbits < 80) ||
         (boost::iequals(algorithm, TSIGKeyInfo::HMAC_SHA224_STR)
          && (digestbits < 112)) ||
         (boost::iequals(algorithm, TSIGKeyInfo::HMAC_SHA256_STR)
          && (digestbits < 128)) ||
         (boost::iequals(algorithm, TSIGKeyInfo::HMAC_SHA384_STR)
          && (digestbits < 192)) ||
         (boost::iequals(algorithm, TSIGKeyInfo::HMAC_SHA512_STR)
          && (digestbits < 256)))) {
        isc_throw(D2CfgError, "tsig-key: digest-bits too small : ("
                                  << getPosition("digest-bits", key_config)
                                  << ")");
        }

    // Everything should be valid, so create the key instance.
    // It is possible for the D2TsigKey constructor to fail such as
    // with an invalid secret content.
    TSIGKeyInfoPtr key_info;
    try {
        key_info.reset(new TSIGKeyInfo(name, algorithm, secret, digestbits));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, ex.what() << " ("
                  << key_config->getPosition() << ")");
    }

    // Add user-context
    if (user_context) {
        key_info->setContext(user_context);
    }

    return (key_info);
}

// *********************** TSIGKeyInfoListParser  *************************

TSIGKeyInfoMapPtr
TSIGKeyInfoListParser::parse(ConstElementPtr key_list) {
    TSIGKeyInfoMapPtr keys(new TSIGKeyInfoMap());
    ConstElementPtr key_config;
    TSIGKeyInfoParser key_parser;
    BOOST_FOREACH(key_config, key_list->listValue()) {
        TSIGKeyInfoPtr key = key_parser.parse(key_config);

        // Duplicates are not allowed and should be flagged as an error.
        if (keys->find(key->getName()) != keys->end()) {
            isc_throw(D2CfgError, "Duplicate TSIG key name specified : "
                      << key->getName()
                      << " (" << getPosition("name", key_config) << ")");
        }

        (*keys)[key->getName()] = key;
    }

    return (keys);
}

// *********************** DnsServerInfoParser  *************************

DnsServerInfoPtr
DnsServerInfoParser::parse(ConstElementPtr server_config,
                           ConstElementPtr domain_config,
                           const TSIGKeyInfoMapPtr keys) {
    std::string hostname = getString(server_config, "hostname");
    std::string ip_address = getString(server_config, "ip-address");
    uint32_t port = getInteger(server_config, "port");
    std::string key_name = getString(server_config, "key-name");
    ConstElementPtr user_context = server_config->get("user-context");

    // Key name is optional. If it is not blank, then find the key in the
    // list of defined keys.
    TSIGKeyInfoPtr tsig_key_info;
    bool inherited_key = true;
    if (key_name.empty()) {
        std::string domain_key_name = getString(domain_config, "key-name");
        if (!domain_key_name.empty()) {
            key_name = domain_key_name;
        }
    } else {
        inherited_key = false;
    }
    if (!key_name.empty()) {
        if (keys) {
            TSIGKeyInfoMap::iterator kit = keys->find(key_name);
            if (kit != keys->end()) {
                tsig_key_info = kit->second;
            }
        }

        if (!tsig_key_info) {
            if (inherited_key) {
                isc_throw(D2CfgError, "DdnsDomain : specifies an "
                          << "undefined key: " << key_name << " ("
                          << getPosition("key-name", domain_config) << ")");
            } else {
                isc_throw(D2CfgError, "Dns Server : specifies an "
                          << "undefined key: " << key_name << " ("
                          << getPosition("key-name", server_config) << ")");
            }
        }
    }

    // The configuration must specify one or the other.
    if (hostname.empty() == ip_address.empty()) {
        isc_throw(D2CfgError, "Dns Server must specify one or the other"
                  " of hostname or IP address"
                  << " (" << server_config->getPosition() << ")");
    }

    DnsServerInfoPtr server_info;
    if (!hostname.empty()) {
        /// @todo when resolvable hostname is supported we create the entry
        /// as follows:
        ///
        /// @code
        /// // When  hostname is specified, create a valid, blank IOAddress
        /// // and then create the DnsServerInfo.
        /// serverInfo.reset(new DnsServerInfo(hostname, io_addr, port));
        ///
        /// @endcode
        ///
        /// Resolution will be done prior to connection during transaction
        /// processing.
        /// Until then we'll throw unsupported.
        isc_throw(D2CfgError, "Dns Server : hostname is not yet supported"
                  << " (" << getPosition("hostname", server_config) << ")");
    } else {
        try {
            // Create an IOAddress from the IP address string given and then
            // create the DnsServerInfo.
            isc::asiolink::IOAddress io_addr(ip_address);
            server_info.reset(new DnsServerInfo(hostname, io_addr, port,
                                                true, tsig_key_info,
                                                inherited_key));
        } catch (const isc::asiolink::IOError& ex) {
            isc_throw(D2CfgError, "Dns Server : invalid IP address : "
                      << ip_address
                      << " (" << getPosition("ip-address", server_config) << ")");
        }
    }

    // Add user-context
    if (user_context) {
        server_info->setContext(user_context);
    }

    return (server_info);
}

// *********************** DnsServerInfoListParser  *************************

DnsServerInfoStoragePtr
DnsServerInfoListParser::parse(ConstElementPtr server_list,
                               ConstElementPtr domain_config,
                               const TSIGKeyInfoMapPtr keys) {
    DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
    ConstElementPtr server_config;
    DnsServerInfoParser parser;
    BOOST_FOREACH(server_config, server_list->listValue()) {
        DnsServerInfoPtr server =
            parser.parse(server_config, domain_config, keys);
        servers->push_back(server);
    }

    return (servers);
}

// *********************** DdnsDomainParser  *************************

DdnsDomainPtr DdnsDomainParser::parse(ConstElementPtr domain_config,
                                      const TSIGKeyInfoMapPtr keys) {
    std::string name = getString(domain_config, "name");
    std::string key_name = getString(domain_config, "key-name");
    ConstElementPtr user_context = domain_config->get("user-context");

    // Parse the list of DNS servers
    ConstElementPtr servers_config;
    try {
        servers_config = domain_config->get("dns-servers");
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "DdnsDomain : missing dns-server list"
                      << " (" << servers_config->getPosition() << ")");
    }

    DnsServerInfoListParser server_parser;
    DnsServerInfoStoragePtr servers =
        server_parser.parse(servers_config, domain_config, keys);
    if (servers->size() == 0) {
        isc_throw(D2CfgError, "DNS server list cannot be empty"
                    << servers_config->getPosition());
    }

    // Instantiate the new domain and add it to domain storage.
    DdnsDomainPtr domain(new DdnsDomain(name, servers, key_name));

    // Add user-context
    if (user_context) {
        domain->setContext(user_context);
    }

    return (domain);
}

// *********************** DdnsDomainListParser  *************************

DdnsDomainMapPtr DdnsDomainListParser::parse(ConstElementPtr domain_list,
                                             const TSIGKeyInfoMapPtr keys) {
    DdnsDomainMapPtr domains(new DdnsDomainMap());
    DdnsDomainParser parser;
    ConstElementPtr domain_config;
    BOOST_FOREACH(domain_config, domain_list->listValue()) {
        DdnsDomainPtr domain = parser.parse(domain_config, keys);

        // Duplicates are not allowed
        if (domains->find(domain->getName()) != domains->end()) {
            isc_throw(D2CfgError, "Duplicate domain specified:"
                      << domain->getName()
                      << " (" << getPosition("name", domain_config) << ")");
        }

        (*domains)[domain->getName()] = domain;
    }

    return (domains);
}

// *********************** DdnsDomainListMgrParser  *************************

DdnsDomainListMgrPtr
DdnsDomainListMgrParser::parse(ConstElementPtr mgr_config,
                               const std::string& mgr_name,
                               const TSIGKeyInfoMapPtr keys) {
    DdnsDomainListMgrPtr mgr(new DdnsDomainListMgr(mgr_name));

    // Parse the list of domains
    ConstElementPtr domains_config = mgr_config->get("ddns-domains");
    if (domains_config) {
        DdnsDomainListParser domain_parser;
        DdnsDomainMapPtr domains =  domain_parser.parse(domains_config, keys);

        // Add the new domain to the domain storage.
        mgr->setDomains(domains);
    }

    return(mgr);
}

} // end of isc::dhcp namespace
} // end of isc namespace
