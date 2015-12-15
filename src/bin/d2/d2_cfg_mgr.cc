// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_log.h>
#include <d2/d2_cfg_mgr.h>
#include <util/encode/hex.h>

#include <boost/foreach.hpp>

namespace isc {
namespace d2 {

namespace {

typedef std::vector<uint8_t> ByteAddress;

} // end of unnamed namespace

// *********************** D2CfgContext  *************************

D2CfgContext::D2CfgContext()
    : d2_params_(new D2Params()),
      forward_mgr_(new DdnsDomainListMgr("forward-ddns")),
      reverse_mgr_(new DdnsDomainListMgr("reverse-ddns")),
      keys_(new TSIGKeyInfoMap()) {
}

D2CfgContext::D2CfgContext(const D2CfgContext& rhs) : DCfgContextBase(rhs) {
    d2_params_ = rhs.d2_params_;
    if (rhs.forward_mgr_) {
        forward_mgr_.reset(new DdnsDomainListMgr(rhs.forward_mgr_->getName()));
        forward_mgr_->setDomains(rhs.forward_mgr_->getDomains());
    }

    if (rhs.reverse_mgr_) {
        reverse_mgr_.reset(new DdnsDomainListMgr(rhs.reverse_mgr_->getName()));
        reverse_mgr_->setDomains(rhs.reverse_mgr_->getDomains());
    }

    keys_ = rhs.keys_;
}

D2CfgContext::~D2CfgContext() {
}

// *********************** D2CfgMgr  *************************

const char* D2CfgMgr::IPV4_REV_ZONE_SUFFIX = "in-addr.arpa.";

const char* D2CfgMgr::IPV6_REV_ZONE_SUFFIX = "ip6.arpa.";

D2CfgMgr::D2CfgMgr() : DCfgMgrBase(DCfgContextBasePtr(new D2CfgContext())) {
    // TSIG keys need to parse before the Domains, so we can catch Domains
    // that specify undefined keys. Create the necessary parsing order now.
    addToParseOrder("tsig-keys");
    addToParseOrder("forward-ddns");
    addToParseOrder("reverse-ddns");
}

D2CfgMgr::~D2CfgMgr() {
}

DCfgContextBasePtr
D2CfgMgr::createNewContext() {
    return (DCfgContextBasePtr(new D2CfgContext()));
}

bool
D2CfgMgr::forwardUpdatesEnabled() {
    // Forward updates are not enabled if no forward servers are defined.
    return (getD2CfgContext()->getForwardMgr()->size() > 0);
}

bool
D2CfgMgr::reverseUpdatesEnabled() {
    // Reverse updates are not enabled if no revese servers are defined.
    return (getD2CfgContext()->getReverseMgr()->size() > 0);
}

bool
D2CfgMgr::matchForward(const std::string& fqdn, DdnsDomainPtr& domain) {
    if (fqdn.empty()) {
        // This is a programmatic error and should not happen.
        isc_throw(D2CfgError, "matchForward passed an empty fqdn");
    }

    // Fetch the forward manager from the D2 context.
    DdnsDomainListMgrPtr mgr = getD2CfgContext()->getForwardMgr();

    // Call the manager's match method and return the result.
    return (mgr->matchDomain(fqdn, domain));
}

bool
D2CfgMgr::matchReverse(const std::string& ip_address, DdnsDomainPtr& domain) {
    // Note, reverseIpAddress will throw if the ip_address is invalid.
    std::string reverse_address = reverseIpAddress(ip_address);

    // Fetch the reverse manager from the D2 context.
    DdnsDomainListMgrPtr mgr = getD2CfgContext()->getReverseMgr();

    return (mgr->matchDomain(reverse_address, domain));
}

std::string
D2CfgMgr::reverseIpAddress(const std::string& address) {
    try {
        // Convert string address into an IOAddress and invoke the
        // appropriate reverse method.
        isc::asiolink::IOAddress ioaddr(address);
        if (ioaddr.isV4()) {
            return (reverseV4Address(ioaddr));
        }

        return (reverseV6Address(ioaddr));

    } catch (const isc::Exception& ex) {
        isc_throw(D2CfgError, "D2CfgMgr cannot reverse address: "
                               << address << " : " << ex.what());
    }
}

std::string
D2CfgMgr::reverseV4Address(const isc::asiolink::IOAddress& ioaddr) {
    if (!ioaddr.isV4()) {
        isc_throw(D2CfgError, "D2CfgMgr address is not IPv4 address :"
                  << ioaddr);
    }

    // Get the address in byte vector form.
    const ByteAddress bytes = ioaddr.toBytes();

    // Walk backwards through vector outputting each octet and a dot.
    std::ostringstream stream;

    // We have to set the following variable to get
    // const_reverse_iterator type of rend(), otherwise Solaris GCC
    // complains on operator!= by trying to use the non-const variant.
    const ByteAddress::const_reverse_iterator end = bytes.rend();

    for (ByteAddress::const_reverse_iterator rit = bytes.rbegin();
         rit != end;
         ++rit)
    {
        stream << static_cast<unsigned int>(*rit) << ".";
    }

    // Tack on the suffix and we're done.
    stream << IPV4_REV_ZONE_SUFFIX;
    return(stream.str());
}

std::string
D2CfgMgr::reverseV6Address(const isc::asiolink::IOAddress& ioaddr) {
    if (!ioaddr.isV6()) {
        isc_throw(D2CfgError, "D2Cfg address is not IPv6 address: " << ioaddr);
    }

    // Turn the address into a string of digits.
    const ByteAddress bytes = ioaddr.toBytes();
    const std::string digits = isc::util::encode::encodeHex(bytes);

    // Walk backwards through string outputting each digits and a dot.
    std::ostringstream stream;

    // We have to set the following variable to get
    // const_reverse_iterator type of rend(), otherwise Solaris GCC
    // complains on operator!= by trying to use the non-const variant.
    const std::string::const_reverse_iterator end = digits.rend();

    for (std::string::const_reverse_iterator rit = digits.rbegin();
         rit != end;
         ++rit)
    {
        stream << static_cast<char>(*rit) << ".";
    }

    // Tack on the suffix and we're done.
    stream << IPV6_REV_ZONE_SUFFIX;
    return(stream.str());
}

const D2ParamsPtr&
D2CfgMgr::getD2Params() {
    return (getD2CfgContext()->getD2Params());
}

std::string
D2CfgMgr::getConfigSummary(const uint32_t) {
    return (getD2Params()->getConfigSummary());
}

void
D2CfgMgr::buildParams(isc::data::ConstElementPtr params_config) {
    // Base class build creates parses and invokes build on each parser.
    // This populate the context scalar stores with all of the parameters.
    DCfgMgrBase::buildParams(params_config);

    // Fetch and validate the parameters from the context to create D2Params.
    // We validate them here rather than just relying on D2Param constructor
    // so we can spit out config text position info with errors.

    // Fetch and validate ip_address.
    D2CfgContextPtr context = getD2CfgContext();
    isc::dhcp::StringStoragePtr strings = context->getStringStorage();
    asiolink::IOAddress ip_address(D2Params::DFT_IP_ADDRESS);

    std::string ip_address_str = strings->getOptionalParam("ip-address",
                                                            D2Params::
                                                            DFT_IP_ADDRESS);
    try {
        ip_address = asiolink::IOAddress(ip_address_str);
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "IP address invalid : \""
                  << ip_address_str << "\" ("
                  << strings->getPosition("ip-address") << ")");
    }

    if ((ip_address.toText() == "0.0.0.0") || (ip_address.toText() == "::")) {
        isc_throw(D2CfgError, "IP address cannot be \"" << ip_address << "\" ("
                   << strings->getPosition("ip-address") << ")");
    }

    // Fetch and validate port.
    isc::dhcp::Uint32StoragePtr ints = context->getUint32Storage();
    uint32_t port = ints->getOptionalParam("port", D2Params::DFT_PORT);

    if (port == 0) {
        isc_throw(D2CfgError, "port cannot be 0 ("
                  << ints->getPosition("port") << ")");
    }

    // Fetch and validate dns_server_timeout.
    uint32_t dns_server_timeout
        = ints->getOptionalParam("dns-server-timeout",
                                 D2Params::DFT_DNS_SERVER_TIMEOUT);

    if (dns_server_timeout < 1) {
        isc_throw(D2CfgError, "DNS server timeout must be larger than 0 ("
                  << ints->getPosition("dns-server-timeout") << ")");
    }

    // Fetch and validate ncr_protocol.
    dhcp_ddns::NameChangeProtocol ncr_protocol;
    try {
        ncr_protocol = dhcp_ddns::
                       stringToNcrProtocol(strings->
                                           getOptionalParam("ncr-protocol",
                                                            D2Params::
                                                            DFT_NCR_PROTOCOL));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "ncr-protocol : "
                  << ex.what() << " ("
                  << strings->getPosition("ncr-protocol") << ")");
    }

    if (ncr_protocol != dhcp_ddns::NCR_UDP) {
        isc_throw(D2CfgError, "ncr-protocol : "
                  << dhcp_ddns::ncrProtocolToString(ncr_protocol)
                  << " is not yet supported ("
                  << strings->getPosition("ncr-protocol") << ")");
    }

    // Fetch and validate ncr_format.
    dhcp_ddns::NameChangeFormat ncr_format;
    try {
        ncr_format = dhcp_ddns::
                     stringToNcrFormat(strings->
                                       getOptionalParam("ncr-format",
                                                        D2Params::
                                                        DFT_NCR_FORMAT));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "ncr-format : "
                  << ex.what() << " ("
                  << strings->getPosition("ncr-format") << ")");
    }

    if (ncr_format != dhcp_ddns::FMT_JSON) {
        isc_throw(D2CfgError, "NCR Format:"
                  << dhcp_ddns::ncrFormatToString(ncr_format)
                  << " is not yet supported ("
                  << strings->getPosition("ncr-format") << ")");
    }

    // Attempt to create the new client config. This ought to fly as
    // we already validated everything.
    D2ParamsPtr params(new D2Params(ip_address, port, dns_server_timeout,
                                    ncr_protocol, ncr_format));

    context->getD2Params() = params;
}

isc::dhcp::ParserPtr
D2CfgMgr::createConfigParser(const std::string& config_id,
                             const isc::data::Element::Position& pos) {
    // Get D2 specific context.
    D2CfgContextPtr context = getD2CfgContext();

    // Create parser instance based on element_id.
    isc::dhcp::ParserPtr parser;
    if ((config_id.compare("port") == 0) ||
        (config_id.compare("dns-server-timeout") == 0)) {
        parser.reset(new isc::dhcp::Uint32Parser(config_id,
                                                 context->getUint32Storage()));
    } else if ((config_id.compare("ip-address") == 0) ||
        (config_id.compare("ncr-protocol") == 0) ||
        (config_id.compare("ncr-format") == 0)) {
        parser.reset(new isc::dhcp::StringParser(config_id,
                                                 context->getStringStorage()));
    } else if (config_id ==  "forward-ddns") {
        parser.reset(new DdnsDomainListMgrParser("forward-ddns",
                                                 context->getForwardMgr(),
                                                 context->getKeys()));
    } else if (config_id ==  "reverse-ddns") {
        parser.reset(new DdnsDomainListMgrParser("reverse-ddns",
                                                 context->getReverseMgr(),
                                                 context->getKeys()));
    } else if (config_id ==  "tsig-keys") {
        parser.reset(new TSIGKeyInfoListParser("tsig-key-list",
                                               context->getKeys()));
    } else {
        isc_throw(NotImplemented,
                  "parser error: D2CfgMgr parameter not supported : "
                  " (" << config_id << pos << ")");
    }

    return (parser);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
