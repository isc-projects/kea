// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <d2/d2_log.h>
#include <d2/d2_cfg_mgr.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <exceptions/exceptions.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <string>

namespace isc {
namespace d2 {

// *********************** TSIGKeyInfo  *************************

const char* TSIGKeyInfo::MD5_STR = "MD5";
const char* TSIGKeyInfo::SHA1_STR = "SHA1";
const char* TSIGKeyInfo::SHA224_STR = "SHA224";
const char* TSIGKeyInfo::SHA256_STR = "SHA256";
const char* TSIGKeyInfo::SHA384_STR = "SHA384";
const char* TSIGKeyInfo::SHA512_STR = "SHA512";

TSIGKeyInfo::TSIGKeyInfo(const std::string& name, const std::string& algorithm,
                         const std::string& secret)
    :name_(name), algorithm_(algorithm), secret_(secret), tsig_key_() {
    remakeKey();
}

TSIGKeyInfo::~TSIGKeyInfo() {
}

const dns::Name&
TSIGKeyInfo::stringToAlgorithmName(const std::string& algorithm_id) {
    if (boost::iequals(algorithm_id, MD5_STR)) {
        return (dns::TSIGKey::HMACMD5_NAME());
    }
    if (boost::iequals(algorithm_id, SHA1_STR)) {
        return (dns::TSIGKey::HMACSHA1_NAME());
    }
    if (boost::iequals(algorithm_id, SHA224_STR)) {
        return (dns::TSIGKey::HMACSHA224_NAME());
    }
    if (boost::iequals(algorithm_id, SHA256_STR)) {
        return (dns::TSIGKey::HMACSHA256_NAME());
    }
    if (boost::iequals(algorithm_id, SHA384_STR)) {
        return (dns::TSIGKey::HMACSHA384_NAME());
    }
    if (boost::iequals(algorithm_id, SHA512_STR)) {
        return (dns::TSIGKey::HMACSHA512_NAME());
    }

    isc_throw(BadValue, "Unknown TSIG Key algorithm:" << algorithm_id);
}

void
TSIGKeyInfo::remakeKey() {
    try {
        tsig_key_.reset(new dns::TSIGKey(dns::Name(name_),
                                         stringToAlgorithmName(algorithm_),
                                         secret_.c_str(), secret_.size()));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "Cannot make TSIGKey: " << ex.what());
    }
}

// *********************** DnsServerInfo  *************************

const char* DnsServerInfo::EMPTY_IP_STR = "0.0.0.0";

DnsServerInfo::DnsServerInfo(const std::string& hostname,
                             isc::asiolink::IOAddress ip_address, uint32_t port,
                             bool enabled)
    :hostname_(hostname), ip_address_(ip_address), port_(port),
    enabled_(enabled) {
}

DnsServerInfo::~DnsServerInfo() {
}

std::string
DnsServerInfo::toText() const {
    std::ostringstream stream;
    stream << (getIpAddress().toText()) << " port:" << getPort();
    return (stream.str());
}


std::ostream&
operator<<(std::ostream& os, const DnsServerInfo& server) {
    os << server.toText();
    return (os);
}

// *********************** DdnsDomain  *************************

DdnsDomain::DdnsDomain(const std::string& name,
                       DnsServerInfoStoragePtr servers,
                       const TSIGKeyInfoPtr& tsig_key_info)
    : name_(name), servers_(servers),
      tsig_key_info_(tsig_key_info) {
}

DdnsDomain::~DdnsDomain() {
}

const std::string
DdnsDomain::getKeyName() const {
    if (tsig_key_info_) {
        return (tsig_key_info_->getName());
    }

    return ("");
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

        LOG_WARN(dctl_logger, DHCP_DDNS_NO_MATCH).arg(fqdn);
        return (false);
    }

    domain = best_match;
    return (true);
}

// *************************** PARSERS ***********************************

// *********************** TSIGKeyInfoParser  *************************

TSIGKeyInfoParser::TSIGKeyInfoParser(const std::string& entry_name,
                                     TSIGKeyInfoMapPtr keys)
    : entry_name_(entry_name), keys_(keys), local_scalars_() {
    if (!keys_) {
        isc_throw(D2CfgError, "TSIGKeyInfoParser ctor:"
                  " key storage cannot be null");
    }
}

TSIGKeyInfoParser::~TSIGKeyInfoParser() {
}

void
TSIGKeyInfoParser::build(isc::data::ConstElementPtr key_config) {
    isc::dhcp::ConfigPair config_pair;
    // For each element in the key configuration:
    // 1. Create a parser for the element.
    // 2. Invoke the parser's build method passing in the element's
    // configuration.
    // 3. Invoke the parser's commit method to store the element's parsed
    // data to the parser's local storage.
    BOOST_FOREACH (config_pair, key_config->mapValue()) {
        isc::dhcp::ParserPtr parser(createConfigParser(config_pair.first));
        parser->build(config_pair.second);
        parser->commit();
    }

    std::string name;
    std::string algorithm;
    std::string secret;

    // Fetch the key configuration's parsed scalar values from parser's
    // local storage.
    local_scalars_.getParam("name", name);
    local_scalars_.getParam("algorithm", algorithm);
    local_scalars_.getParam("secret", secret);

    // Name cannot be blank.
    if (name.empty()) {
        isc_throw(D2CfgError, "TSIG Key Info must specify name");
    }

    // Algorithm cannot be blank.
    if (algorithm.empty()) {
        isc_throw(D2CfgError, "TSIG Key Info must specify algorithm");
    }

    // Secret cannot be blank.
    if (secret.empty()) {
        isc_throw(D2CfgError, "TSIG Key Info must specify secret");
    }

    // Currently, the premise is that key storage is always empty prior to
    // parsing so we are always adding keys never replacing them. Duplicates
    // are not allowed and should be flagged as a configuration error.
    if (keys_->find(name) != keys_->end()) {
        isc_throw(D2CfgError, "Duplicate TSIG key specified:" << name);
    }

    TSIGKeyInfoPtr key_info(new TSIGKeyInfo(name, algorithm, secret));

    // Add the new TSIGKeyInfo to the key storage.
    (*keys_)[name]=key_info;
}

isc::dhcp::ParserPtr
TSIGKeyInfoParser::createConfigParser(const std::string& config_id) {
    DhcpConfigParser* parser = NULL;
    // Based on the configuration id of the element, create the appropriate
    // parser. Scalars are set to use the parser's local scalar storage.
    if ((config_id == "name")  ||
        (config_id == "algorithm") ||
        (config_id == "secret")) {
        parser = new isc::dhcp::StringParser(config_id,
                                             local_scalars_.getStringStorage());
    } else {
        isc_throw(NotImplemented,
                  "parser error: TSIGKeyInfo parameter not supported: "
                  << config_id);
    }

    // Return the new parser instance.
    return (isc::dhcp::ParserPtr(parser));
}

void
TSIGKeyInfoParser::commit() {
}

// *********************** TSIGKeyInfoListParser  *************************

TSIGKeyInfoListParser::TSIGKeyInfoListParser(const std::string& list_name,
                                       TSIGKeyInfoMapPtr keys)
    :list_name_(list_name), keys_(keys), local_keys_(new TSIGKeyInfoMap()),
     parsers_() {
    if (!keys_) {
        isc_throw(D2CfgError, "TSIGKeyInfoListParser ctor:"
                  " key storage cannot be null");
    }
}

TSIGKeyInfoListParser::~TSIGKeyInfoListParser() {
}

void
TSIGKeyInfoListParser::
build(isc::data::ConstElementPtr key_list) {
    int i = 0;
    isc::data::ConstElementPtr key_config;
    // For each key element in the key list:
    // 1. Create a parser for the key element.
    // 2. Invoke the parser's build method passing in the key's
    // configuration.
    // 3. Add the parser to a local collection of parsers.
    BOOST_FOREACH(key_config, key_list->listValue()) {
        // Create a name for the parser based on its position in the list.
        std::string entry_name = boost::lexical_cast<std::string>(i++);
        isc::dhcp::ParserPtr parser(new TSIGKeyInfoParser(entry_name,
                                                            local_keys_));
        parser->build(key_config);
        parsers_.push_back(parser);
    }

    // Now that we know we have a valid list, commit that list to the
    // area given to us during construction (i.e. to the d2 context).
    *keys_ = *local_keys_;
}

void
TSIGKeyInfoListParser::commit() {
    // Invoke commit on each server parser. This will cause each one to
    // create it's server instance and commit it to storage.
    BOOST_FOREACH(isc::dhcp::ParserPtr parser, parsers_) {
        parser->commit();
    }
}

// *********************** DnsServerInfoParser  *************************

DnsServerInfoParser::DnsServerInfoParser(const std::string& entry_name,
    DnsServerInfoStoragePtr servers)
    : entry_name_(entry_name), servers_(servers), local_scalars_() {
    if (!servers_) {
        isc_throw(D2CfgError, "DnsServerInfoParser ctor:"
                  " server storage cannot be null");
    }
}

DnsServerInfoParser::~DnsServerInfoParser() {
}

void
DnsServerInfoParser::build(isc::data::ConstElementPtr server_config) {
    isc::dhcp::ConfigPair config_pair;
    // For each element in the server configuration:
    // 1. Create a parser for the element.
    // 2. Invoke the parser's build method passing in the element's
    // configuration.
    // 3. Invoke the parser's commit method to store the element's parsed
    // data to the parser's local storage.
    BOOST_FOREACH (config_pair, server_config->mapValue()) {
        isc::dhcp::ParserPtr parser(createConfigParser(config_pair.first));
        parser->build(config_pair.second);
        parser->commit();
    }

    std::string hostname;
    std::string ip_address;
    uint32_t port = DnsServerInfo::STANDARD_DNS_PORT;

    // Fetch the server configuration's parsed scalar values from parser's
    // local storage.
    local_scalars_.getParam("hostname", hostname, DCfgContextBase::OPTIONAL);
    local_scalars_.getParam("ip_address", ip_address,
                            DCfgContextBase::OPTIONAL);
    local_scalars_.getParam("port", port, DCfgContextBase::OPTIONAL);

    // The configuration must specify one or the other.
    if (hostname.empty() == ip_address.empty()) {
        isc_throw(D2CfgError, "Dns Server must specify one or the other"
                  " of hostname and IP address");
    }

    DnsServerInfoPtr serverInfo;
    if (!hostname.empty()) {
        // When  hostname is specified, create a valid, blank IOAddress and
        // then create the DnsServerInfo.
        isc::asiolink::IOAddress io_addr(DnsServerInfo::EMPTY_IP_STR);
        serverInfo.reset(new DnsServerInfo(hostname, io_addr, port));
    } else {
        try {
            // Create an IOAddress from the IP address string given and then
            // create the DnsServerInfo.
            isc::asiolink::IOAddress io_addr(ip_address);
            serverInfo.reset(new DnsServerInfo(hostname, io_addr, port));
        } catch (const isc::asiolink::IOError& ex) {
            isc_throw(D2CfgError, "Invalid IP address:" << ip_address);
        }
    }

    // Add the new DnsServerInfo to the server storage.
    servers_->push_back(serverInfo);
}

isc::dhcp::ParserPtr
DnsServerInfoParser::createConfigParser(const std::string& config_id) {
    DhcpConfigParser* parser = NULL;
    // Based on the configuration id of the element, create the appropriate
    // parser. Scalars are set to use the parser's local scalar storage.
    if ((config_id == "hostname")  ||
        (config_id == "ip_address")) {
        parser = new isc::dhcp::StringParser(config_id,
                                             local_scalars_.getStringStorage());
    } else if (config_id == "port") {
        parser = new isc::dhcp::Uint32Parser(config_id,
                                             local_scalars_.getUint32Storage());
    } else {
        isc_throw(NotImplemented,
                  "parser error: DnsServerInfo parameter not supported: "
                  << config_id);
    }

    // Return the new parser instance.
    return (isc::dhcp::ParserPtr(parser));
}

void
DnsServerInfoParser::commit() {
}

// *********************** DnsServerInfoListParser  *************************

DnsServerInfoListParser::DnsServerInfoListParser(const std::string& list_name,
                                       DnsServerInfoStoragePtr servers)
    :list_name_(list_name), servers_(servers), parsers_() {
    if (!servers_) {
        isc_throw(D2CfgError, "DdnsServerInfoListParser ctor:"
                  " server storage cannot be null");
    }
}

DnsServerInfoListParser::~DnsServerInfoListParser(){
}

void
DnsServerInfoListParser::
build(isc::data::ConstElementPtr server_list){
    int i = 0;
    isc::data::ConstElementPtr server_config;
    // For each server element in the server list:
    // 1. Create a parser for the server element.
    // 2. Invoke the parser's build method passing in the server's
    // configuration.
    // 3. Add the parser to a local collection of parsers.
    BOOST_FOREACH(server_config, server_list->listValue()) {
        // Create a name for the parser based on its position in the list.
        std::string entry_name = boost::lexical_cast<std::string>(i++);
        isc::dhcp::ParserPtr parser(new DnsServerInfoParser(entry_name,
                                                            servers_));
        parser->build(server_config);
        parsers_.push_back(parser);
    }

    // Domains must have at least one server.
    if (parsers_.size() == 0) {
        isc_throw (D2CfgError, "Server List must contain at least one server");
    }
}

void
DnsServerInfoListParser::commit() {
    // Invoke commit on each server parser.
    BOOST_FOREACH(isc::dhcp::ParserPtr parser, parsers_) {
        parser->commit();
    }
}

// *********************** DdnsDomainParser  *************************

DdnsDomainParser::DdnsDomainParser(const std::string& entry_name,
                                   DdnsDomainMapPtr domains,
                                   TSIGKeyInfoMapPtr keys)
    : entry_name_(entry_name), domains_(domains), keys_(keys),
    local_servers_(new DnsServerInfoStorage()), local_scalars_() {
    if (!domains_) {
        isc_throw(D2CfgError,
                  "DdnsDomainParser ctor, domain storage cannot be null");
    }
}


DdnsDomainParser::~DdnsDomainParser() {
}

void
DdnsDomainParser::build(isc::data::ConstElementPtr domain_config) {
    // For each element in the domain configuration:
    // 1. Create a parser for the element.
    // 2. Invoke the parser's build method passing in the element's
    // configuration.
    // 3. Invoke the parser's commit method to store the element's parsed
    // data to the parser's local storage.
    isc::dhcp::ConfigPair config_pair;
    BOOST_FOREACH(config_pair, domain_config->mapValue()) {
        isc::dhcp::ParserPtr parser(createConfigParser(config_pair.first));
        parser->build(config_pair.second);
        parser->commit();
    }

    // Now construct the domain.
    std::string name;
    std::string key_name;

    // Domain name is not optional. The get will throw if its not there.
    local_scalars_.getParam("name", name);

    // Blank domain names are not allowed.
    if (name.empty()) {
        isc_throw(D2CfgError, "Domain name cannot be blank");
    }

    // Currently, the premise is that domain storage is always empty
    // prior to parsing so always adding domains never replacing them.
    // Duplicates are not allowed and should be flagged as a configuration
    // error.
    if (domains_->find(name) != domains_->end()) {
        isc_throw(D2CfgError, "Duplicate domain specified:" << name);
    }

    // Key name is optional. If it is not blank, then find the key in the
    /// list of defined keys.
    TSIGKeyInfoPtr tsig_key_info;
    local_scalars_.getParam("key_name", key_name, DCfgContextBase::OPTIONAL);
    if (!key_name.empty()) {
        if (keys_) {
            TSIGKeyInfoMap::iterator kit = keys_->find(key_name);
            if (kit != keys_->end()) {
                tsig_key_info = kit->second;
            }
        }

        if (!tsig_key_info) {
            isc_throw(D2CfgError, "DdnsDomain :" << name <<
                     " specifies an undefined key:" << key_name);
        }
    }

    // Instantiate the new domain and add it to domain storage.
    DdnsDomainPtr domain(new DdnsDomain(name, local_servers_, tsig_key_info));

    // Add the new domain to the domain storage.
    (*domains_)[name] = domain;
}

isc::dhcp::ParserPtr
DdnsDomainParser::createConfigParser(const std::string& config_id) {
    DhcpConfigParser* parser = NULL;
    // Based on the configuration id of the element, create the appropriate
    // parser. Scalars are set to use the parser's local scalar storage.
    if ((config_id == "name")  ||
        (config_id == "key_name")) {
        parser = new isc::dhcp::StringParser(config_id,
                                             local_scalars_.getStringStorage());
    } else if (config_id == "dns_servers") {
       // Server list parser is given in our local server storage. It will pass
       // this down to its server parsers and is where they will write their
       // server instances upon commit.
       parser = new DnsServerInfoListParser(config_id, local_servers_);
    } else {
       isc_throw(NotImplemented,
                "parser error: DdnsDomain parameter not supported: "
                << config_id);
    }

    // Return the new domain parser instance.
    return (isc::dhcp::ParserPtr(parser));
}

void
DdnsDomainParser::commit() {
}

// *********************** DdnsDomainListParser  *************************

DdnsDomainListParser::DdnsDomainListParser(const std::string& list_name,
                                           DdnsDomainMapPtr domains,
                                           TSIGKeyInfoMapPtr keys)
    :list_name_(list_name), domains_(domains), keys_(keys), parsers_() {
    if (!domains_) {
        isc_throw(D2CfgError, "DdnsDomainListParser ctor:"
                  " domain storage cannot be null");
    }
}

DdnsDomainListParser::~DdnsDomainListParser(){
}

void
DdnsDomainListParser::
build(isc::data::ConstElementPtr domain_list){
    // For each domain element in the domain list:
    // 1. Create a parser for the domain element.
    // 2. Invoke the parser's build method passing in the domain's
    // configuration.
    // 3. Add the parser to the local collection of parsers.
    int i = 0;
    isc::data::ConstElementPtr domain_config;
    BOOST_FOREACH(domain_config, domain_list->listValue()) {
        std::string entry_name = boost::lexical_cast<std::string>(i++);
        isc::dhcp::ParserPtr parser(new DdnsDomainParser(entry_name,
                                                         domains_, keys_));
        parser->build(domain_config);
        parsers_.push_back(parser);
    }
}

void
DdnsDomainListParser::commit() {
    // Invoke commit on each server parser. This will cause each one to
    // create it's server instance and commit it to storage.
    BOOST_FOREACH(isc::dhcp::ParserPtr parser, parsers_) {
        parser->commit();
    }
}


// *********************** DdnsDomainListMgrParser  *************************

DdnsDomainListMgrParser::DdnsDomainListMgrParser(const std::string& entry_name,
                              DdnsDomainListMgrPtr mgr, TSIGKeyInfoMapPtr keys)
    : entry_name_(entry_name), mgr_(mgr), keys_(keys),
    local_domains_(new DdnsDomainMap()), local_scalars_() {
}


DdnsDomainListMgrParser::~DdnsDomainListMgrParser() {
}

void
DdnsDomainListMgrParser::build(isc::data::ConstElementPtr domain_config) {
    // For each element in the domain manager configuration:
    // 1. Create a parser for the element.
    // 2. Invoke the parser's build method passing in the element's
    // configuration.
    // 3. Invoke the parser's commit method to store the element's parsed
    // data to the parser's local storage.
    isc::dhcp::ConfigPair config_pair;
    BOOST_FOREACH(config_pair, domain_config->mapValue()) {
        isc::dhcp::ParserPtr parser(createConfigParser(config_pair.first));
        parser->build(config_pair.second);
        parser->commit();
    }

    // Add the new domain to the domain storage.
    mgr_->setDomains(local_domains_);
}

isc::dhcp::ParserPtr
DdnsDomainListMgrParser::createConfigParser(const std::string& config_id) {
    DhcpConfigParser* parser = NULL;
    if (config_id == "ddns_domains") {
       // Domain list parser is given our local domain storage. It will pass
       // this down to its domain parsers and is where they will write their
       // domain instances upon commit.
       parser = new DdnsDomainListParser(config_id, local_domains_, keys_);
    } else {
       isc_throw(NotImplemented, "parser error: "
                 "DdnsDomainListMgr parameter not supported: " << config_id);
    }

    // Return the new domain parser instance.
    return (isc::dhcp::ParserPtr(parser));
}

void
DdnsDomainListMgrParser::commit() {
}


}; // end of isc::dhcp namespace
}; // end of isc namespace
