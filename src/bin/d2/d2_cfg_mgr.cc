// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_log.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/d2_simple_parser.h>
#include <util/encode/hex.h>

#include <boost/foreach.hpp>

using namespace isc::process;

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
    // Reverse updates are not enabled if no reverse servers are defined.
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

namespace {

template <typename int_type> int_type
getInt(const std::string& name, isc::data::ConstElementPtr value) {
    int64_t val_int = value->intValue();
    if ((val_int < std::numeric_limits<int_type>::min()) ||
        (val_int > std::numeric_limits<int_type>::max())) {
        isc_throw(D2CfgError, "out of range value (" << val_int
                  << ") specified for parameter '" << name
                  << "' (" << value->getPosition() << ")");
    }
    return (static_cast<int_type>(val_int));
}

isc::asiolink::IOAddress
getIOAddress(const std::string& name, isc::data::ConstElementPtr value) {
    std::string str = value->stringValue();
    try {
        return (isc::asiolink::IOAddress(str));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "invalid address (" << str
                  << ") specified for parameter '" << name
                  << "' (" << value->getPosition() << ")");
    }
}

dhcp_ddns::NameChangeProtocol
getProtocol(const std::string& name, isc::data::ConstElementPtr value) {
    std::string str = value->stringValue();
    try {
        return (dhcp_ddns::stringToNcrProtocol(str));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError,
                  "invalid NameChangeRequest protocol (" << str
                  << ") specified for parameter '" << name
                  << "' (" << value->getPosition() << ")");
    }
}

dhcp_ddns::NameChangeFormat
getFormat(const std::string& name, isc::data::ConstElementPtr value) {
    std::string str = value->stringValue();
    try {
        return (dhcp_ddns::stringToNcrFormat(str));
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError,
                  "invalid NameChangeRequest format (" << str
                  << ") specified for parameter '" << name
                  << "' (" << value->getPosition() << ")");
    }
}

} // anon

bool
D2CfgMgr::parseElement(const std::string& element_id,
                       isc::data::ConstElementPtr element) {

    // Get D2 specific context.
    try {
        D2CfgContextPtr context = getD2CfgContext();
        if ((element_id == "ip-address") ||
            (element_id == "ncr-protocol") ||
            (element_id == "ncr-format") ||
            (element_id == "port")  ||
            (element_id == "dns-server-timeout"))  {
            // global scalar params require nothing extra
        } else {
            // not something we handle here
            return (false);
        }
    } catch (const std::exception& ex) {
        isc_throw(D2CfgError, "element: " << element_id << " : "  << ex.what()
                              << element->getPosition());
    }

    return (true);
};

void
D2CfgMgr::setCfgDefaults(isc::data::ElementPtr mutable_config) {
    D2SimpleParser::setAllDefaults(mutable_config);
}

void
D2CfgMgr::buildParams(isc::data::ConstElementPtr params_config) {

    // Base class build creates parses and invokes build on each parser.
    // This populate the context scalar stores with all of the parameters.
    DCfgMgrBase::buildParams(params_config);

    // Fetch the parameters in the config, performing any logcial
    // validation required.
    asiolink::IOAddress ip_address(0);
    uint32_t port = 0;
    uint32_t dns_server_timeout = 0;
    dhcp_ddns::NameChangeProtocol ncr_protocol = dhcp_ddns::NCR_UDP;
    dhcp_ddns::NameChangeFormat ncr_format = dhcp_ddns::FMT_JSON;

    BOOST_FOREACH(isc::dhcp::ConfigPair param, params_config->mapValue()) {
        std::string entry(param.first);
        isc::data::ConstElementPtr value(param.second);
        try {
            if (entry == "ip-address") {
                ip_address = getIOAddress(entry, value);
                if ((ip_address.toText() == "0.0.0.0") ||
                    (ip_address.toText() == "::")) {
                    isc_throw(D2CfgError, "IP address cannot be \""
                              << ip_address << "\""
                            << " (" << value->getPosition() << ")");
                }
            } else if (entry == "port") {
                port = getInt<uint32_t>(entry, value);
            } else if (entry == "dns-server-timeout") {
                dns_server_timeout = getInt<uint32_t>(entry, value);
            } else if (entry == "ncr-protocol") {
                ncr_protocol = getProtocol(entry, value);
                if (ncr_protocol != dhcp_ddns::NCR_UDP) {
                    isc_throw(D2CfgError, "ncr-protocol : "
                              << dhcp_ddns::ncrProtocolToString(ncr_protocol)
                              << " is not yet supported "
                              << " (" << value->getPosition() << ")");
                }
            } else if (entry == "ncr-format") {
                ncr_format = getFormat(entry, value);
                if (ncr_format != dhcp_ddns::FMT_JSON) {
                    isc_throw(D2CfgError, "NCR Format:"
                              << dhcp_ddns::ncrFormatToString(ncr_format)
                              << " is not yet supported"
                              << " (" << value->getPosition() << ")");
                }
            } else {
                isc_throw(D2CfgError,
                          "unsupported parameter '" << entry
                          << " (" << value->getPosition() << ")");
            }
        } catch (const isc::data::TypeError&) {
            isc_throw(D2CfgError,
                      "invalid value type specified for parameter '" << entry
                      << " (" << value->getPosition() << ")");
        }

    }

    // Attempt to create the new client config. This ought to fly as
    // we already validated everything.
    D2ParamsPtr params(new D2Params(ip_address, port, dns_server_timeout,
                                    ncr_protocol, ncr_format));

    getD2CfgContext()->getD2Params() = params;
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
