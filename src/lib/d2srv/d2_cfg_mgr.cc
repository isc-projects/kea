// Copyright (C) 2014-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2srv/d2_log.h>
#include <d2srv/d2_cfg_mgr.h>
#include <d2srv/d2_simple_parser.h>
#include <cc/command_interpreter.h>
#include <util/encode/hex.h>

#include <boost/foreach.hpp>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
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
      keys_(new TSIGKeyInfoMap()),
      control_socket_(ConstElementPtr()) {
}

D2CfgContext::D2CfgContext(const D2CfgContext& rhs) : ConfigBase(rhs) {
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

    control_socket_ = rhs.control_socket_;

    hooks_config_ = rhs.hooks_config_;
}

D2CfgContext::~D2CfgContext() {
}

ElementPtr
D2CfgContext::toElement() const {
    ElementPtr d2 = ConfigBase::toElement();
    // Set user-context
    contextToElement(d2);
    // Set ip-address
    const IOAddress& ip_address = d2_params_->getIpAddress();
    d2->set("ip-address", Element::create(ip_address.toText()));
    // Set port
    size_t port = d2_params_->getPort();
    d2->set("port", Element::create(static_cast<int64_t>(port)));
    // Set dns-server-timeout
    size_t dns_server_timeout = d2_params_->getDnsServerTimeout();
    d2->set("dns-server-timeout",
            Element::create(static_cast<int64_t>(dns_server_timeout)));
    // Set ncr-protocol
    const dhcp_ddns::NameChangeProtocol& ncr_protocol =
        d2_params_->getNcrProtocol();
    d2->set("ncr-protocol",
            Element::create(dhcp_ddns::ncrProtocolToString(ncr_protocol)));
    // Set ncr-format
    const dhcp_ddns::NameChangeFormat& ncr_format = d2_params_->getNcrFormat();
    d2->set("ncr-format",
            Element::create(dhcp_ddns::ncrFormatToString(ncr_format)));
    // Set forward-ddns
    ElementPtr forward_ddns = Element::createMap();
    forward_ddns->set("ddns-domains", forward_mgr_->toElement());
    d2->set("forward-ddns", forward_ddns);
    // Set reverse-ddns
    ElementPtr reverse_ddns = Element::createMap();
    reverse_ddns->set("ddns-domains", reverse_mgr_->toElement());
    d2->set("reverse-ddns", reverse_ddns);
    // Set tsig-keys
    ElementPtr tsig_keys = Element::createList();
    for (TSIGKeyInfoMap::const_iterator key = keys_->begin();
         key != keys_->end(); ++key) {
        tsig_keys->add(key->second->toElement());
    }
    d2->set("tsig-keys", tsig_keys);
    // Set control-socket (skip if null as empty is not legal)
    if (!isNull(control_socket_)) {
        d2->set("control-socket", UserContext::toElement(control_socket_));
    }
    // Set hooks-libraries
    d2->set("hooks-libraries", hooks_config_.toElement());
    // Set DhcpDdns
    ElementPtr result = Element::createMap();
    result->set("DhcpDdns", d2);

    return (result);
}

// *********************** D2CfgMgr  *************************

const char* D2CfgMgr::IPV4_REV_ZONE_SUFFIX = "in-addr.arpa.";

const char* D2CfgMgr::IPV6_REV_ZONE_SUFFIX = "ip6.arpa.";

D2CfgMgr::D2CfgMgr() : DCfgMgrBase(ConfigPtr(new D2CfgContext())) {
}

D2CfgMgr::~D2CfgMgr() {
}

ConfigPtr
D2CfgMgr::createNewContext() {
    return (ConfigPtr(new D2CfgContext()));
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

const isc::data::ConstElementPtr
D2CfgMgr::getControlSocketInfo() {
    return (getD2CfgContext()->getControlSocketInfo());
}

std::string
D2CfgMgr::getConfigSummary(const uint32_t) {
    return (getD2Params()->getConfigSummary());
}

void
D2CfgMgr::setCfgDefaults(ElementPtr mutable_config) {
    D2SimpleParser::setAllDefaults(mutable_config);
}

isc::data::ConstElementPtr
D2CfgMgr::parse(isc::data::ConstElementPtr config_set, bool check_only) {
    // Do a sanity check first.
    if (!config_set) {
        isc_throw(D2CfgError, "Mandatory config parameter not provided");
    }

    D2CfgContextPtr ctx = getD2CfgContext();

    // Set the defaults
    ElementPtr cfg = boost::const_pointer_cast<Element>(config_set);
    D2SimpleParser::setAllDefaults(cfg);

    // And parse the configuration.
    ConstElementPtr answer;
    std::string excuse;
    try {
        // Do the actual parsing
        D2SimpleParser parser;
        parser.parse(ctx, cfg, check_only);
    } catch (const isc::Exception& ex) {
        excuse = ex.what();
        answer = createAnswer(CONTROL_RESULT_ERROR, excuse);
    } catch (...) {
        excuse = "undefined configuration parsing error";
        answer = createAnswer(CONTROL_RESULT_ERROR, excuse);
    }

    // At this stage the answer was created only in case of exception.
    if (answer) {
        if (check_only) {
            LOG_ERROR(d2_logger, DHCP_DDNS_CONFIG_CHECK_FAIL).arg(excuse);
        } else {
            LOG_ERROR(d2_logger, DHCP_DDNS_CONFIG_FAIL).arg(excuse);
        }
        return (answer);
    }

    if (check_only) {
        answer = createAnswer(CONTROL_RESULT_SUCCESS,
                              "Configuration check successful");
    } else {
        answer = createAnswer(CONTROL_RESULT_SUCCESS,
                              "Configuration applied successfully.");
    }

    return (answer);
}

std::list<std::list<std::string>>
D2CfgMgr::jsonPathsToRedact() const {
    static std::list<std::list<std::string>> const list({
        {"tsig-keys", "[]"},
        {"hooks-libraries", "[]", "parameters", "*"},
    });
    return list;
}

}  // namespace d2
}  // namespace isc
