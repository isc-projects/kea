// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/encode/hex.h>

#include <boost/foreach.hpp>

namespace isc {
namespace d2 {

namespace {

typedef std::vector<uint8_t> ByteAddress;

} // end of unnamed namespace

// *********************** D2CfgContext  *************************

D2CfgContext::D2CfgContext()
    : forward_mgr_(new DdnsDomainListMgr("forward_mgr")),
      reverse_mgr_(new DdnsDomainListMgr("reverse_mgr")),
      keys_(new TSIGKeyInfoMap()) {
}

D2CfgContext::D2CfgContext(const D2CfgContext& rhs) : DCfgContextBase(rhs) {
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
    addToParseOrder("interface");
    addToParseOrder("ip_address");
    addToParseOrder("port");
    addToParseOrder("tsig_keys");
    addToParseOrder("forward_ddns");
    addToParseOrder("reverse_ddns");
}

D2CfgMgr::~D2CfgMgr() {
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


isc::dhcp::ParserPtr
D2CfgMgr::createConfigParser(const std::string& config_id) {
    // Get D2 specific context.
    D2CfgContextPtr context = getD2CfgContext();

    // Create parser instance based on element_id.
    isc::dhcp::DhcpConfigParser* parser = NULL;
    if ((config_id == "interface")  ||
        (config_id == "ip_address")) {
        parser = new isc::dhcp::StringParser(config_id,
                                             context->getStringStorage());
    } else if (config_id == "port") {
        parser = new isc::dhcp::Uint32Parser(config_id,
                                             context->getUint32Storage());
    } else if (config_id ==  "forward_ddns") {
        parser = new DdnsDomainListMgrParser("forward_mgr",
                                             context->getForwardMgr(),
                                             context->getKeys());
    } else if (config_id ==  "reverse_ddns") {
        parser = new DdnsDomainListMgrParser("reverse_mgr",
                                             context->getReverseMgr(),
                                             context->getKeys());
    } else if (config_id ==  "tsig_keys") {
        parser = new TSIGKeyInfoListParser("tsig_key_list", context->getKeys());
    } else {
        isc_throw(NotImplemented,
                  "parser error: D2CfgMgr parameter not supported: "
                  << config_id);
    }

    return (isc::dhcp::ParserPtr(parser));
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
