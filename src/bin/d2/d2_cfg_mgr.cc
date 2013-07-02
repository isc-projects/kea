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

#include <boost/foreach.hpp>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace d2 {

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
D2CfgMgr::matchReverse(const std::string& fqdn, DdnsDomainPtr& domain) {
    if (fqdn.empty()) {
        // This is a programmatic error and should not happen.
        isc_throw(D2CfgError, "matchReverse passed a null or empty fqdn");
    }

    // Fetch the reverse manager from the D2 context.
    DdnsDomainListMgrPtr mgr = getD2CfgContext()->getReverseMgr();

    // Call the manager's match method and return the result.
    return (mgr->matchDomain(fqdn, domain));
}


isc::dhcp::ParserPtr
D2CfgMgr::createConfigParser(const std::string& config_id) {
    // Get D2 specific context.
    D2CfgContextPtr context = getD2CfgContext();

    // Create parser instance based on element_id.
    DhcpConfigParser* parser = NULL;
    if ((config_id == "interface")  ||
        (config_id == "ip_address")) {
        parser = new StringParser(config_id, context->getStringStorage());
    } else if (config_id == "port") {
        parser = new Uint32Parser(config_id, context->getUint32Storage());
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

