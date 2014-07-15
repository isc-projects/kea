// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp4.h>
#include <dhcp/option.h>
#include <dhcp/option_int_array.h>
#include <dhcpsrv/lease.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <boost/pointer_cast.hpp>
#include <cstdlib>

namespace isc {
namespace dhcp {
namespace test {

Dhcp4Client::Configuration::Configuration()
    : routers_(), dns_servers_(), serverid_("0.0.0.0") {
    reset();
}

void
Dhcp4Client::Configuration::reset() {
    routers_.clear();
    dns_servers_.clear();
    serverid_ = asiolink::IOAddress("0.0.0.0");
}

Dhcp4Client::Dhcp4Client() :
    config_(),
    curr_transid_(0),
    dest_addr_("255.255.255.255"),
    hwaddr_(generateHWAddr()),
    relay_addr_("192.0.2.2"),
    requested_options_(),
    server_facing_relay_addr_("10.0.0.2"),
    srv_(boost::shared_ptr<NakedDhcpv4Srv>(new NakedDhcpv4Srv(0))),
    use_relay_(false) {
}

Dhcp4Client::Dhcp4Client(boost::shared_ptr<NakedDhcpv4Srv>& srv) :
    config_(),
    curr_transid_(0),
    dest_addr_("255.255.255.255"),
    hwaddr_(generateHWAddr()),
    relay_addr_("192.0.2.2"),
    requested_options_(),
    server_facing_relay_addr_("10.0.0.2"),
    srv_(srv),
    use_relay_(false) {
}

void
Dhcp4Client::applyConfiguration() {
    Pkt4Ptr resp = context_.response_;
    if (!resp) {
        return;
    }

    config_.reset();

    Option4AddrLstPtr opt_routers = boost::dynamic_pointer_cast<
        Option4AddrLst>(resp->getOption(DHO_ROUTERS));
    if (opt_routers) {
        config_.routers_ = opt_routers->getAddresses();
    }

    Option4AddrLstPtr opt_dns_servers = boost::dynamic_pointer_cast<
        Option4AddrLst>(resp->getOption(DHO_DOMAIN_NAME_SERVERS));
    if (opt_dns_servers) {
        config_.dns_servers_ = opt_dns_servers->getAddresses();
    }

    OptionCustomPtr opt_serverid = boost::dynamic_pointer_cast<
        OptionCustom>(resp->getOption(DHO_DHCP_SERVER_IDENTIFIER));
    if (opt_serverid) {
        config_.serverid_ = opt_serverid->readAddress();
    }

    /// @todo Other possible configuration.
}

void
Dhcp4Client::createLease(const asiolink::IOAddress& addr,
                         const uint32_t valid_lft) {
    Lease4 lease(addr, &hwaddr_->hwaddr_[0], hwaddr_->hwaddr_.size(),
                 0, 0, valid_lft, valid_lft / 2, valid_lft,
                 time(NULL), false, false, "");
    config_.lease_ = lease;
}

Pkt4Ptr
Dhcp4Client::createMsg(const uint8_t msg_type) {
    Pkt4Ptr msg(new Pkt4(msg_type, curr_transid_++));
    msg->setHWAddr(hwaddr_);
    return (msg);
}

void
Dhcp4Client::doInform(const bool set_ciaddr) {
    context_.query_ = createMsg(DHCPINFORM);
    // Request options if any.
    if (!requested_options_.empty()) {
        // Include Parameter Request List if at least one option code
        // has been specified to be requested.
        OptionUint8ArrayPtr prl(new OptionUint8Array(Option::V4,
                                  DHO_DHCP_PARAMETER_REQUEST_LIST));
        for (std::set<uint8_t>::const_iterator opt = requested_options_.begin();
             opt != requested_options_.end(); ++opt) {
            prl->addValue(*opt);
        }
        context_.query_->addOption(prl);
    }
    // The client sending a DHCPINFORM message has an IP address obtained
    // by some other means, e.g. static configuration. The lease which we
    // are using here is most likely set by the createLease method.
    if (set_ciaddr) {
        context_.query_->setCiaddr(config_.lease_.addr_);
    }
    context_.query_->setLocalAddr(config_.lease_.addr_);
    // Send the message to the server.
    sendMsg(context_.query_);
    // Expect response. If there is no response, return.
    context_.response_ = receiveOneMsg();
    if (!context_.response_) {
        return;
    }
    // If DHCPACK has been returned by the server, use the returned
    // configuration.
    if (context_.response_->getType() == DHCPACK) {
        applyConfiguration();
    }
}

HWAddrPtr
Dhcp4Client::generateHWAddr(const uint8_t htype) const {
    if (htype != HTYPE_ETHER) {
        isc_throw(isc::NotImplemented,
                  "The harware address type " << static_cast<int>(htype)
                  << " is currently not supported");
    }
    std::vector<uint8_t> hwaddr;
    // Generate ethernet hardware address by assigning random byte values.
    for (int i = 0; i < HWAddr::ETHERNET_HWADDR_LEN; ++i) {
        hwaddr.push_back(static_cast<uint8_t>(rand() % 255));
    }
    return (HWAddrPtr(new HWAddr(hwaddr, htype)));
}

void
Dhcp4Client::modifyHWAddr() {
    if (!hwaddr_) {
        hwaddr_ = generateHWAddr();
        return;
    }
    // Modify the HW address by adding 1 to its last byte.
    ++hwaddr_->hwaddr_[hwaddr_->hwaddr_.size() - 1];
}

void
Dhcp4Client::requestOption(const uint8_t option) {
    if (option != 0) {
        requested_options_.insert(option);
    }
}

void
Dhcp4Client::requestOptions(const uint8_t option1, const uint8_t option2,
                            const uint8_t option3) {
    requested_options_.clear();
    requestOption(option1);
    requestOption(option2);
    requestOption(option3);
}


Pkt4Ptr
Dhcp4Client::receiveOneMsg() {
    // Return empty pointer if server hasn't responded.
    if (srv_->fake_sent_.empty()) {
        return (Pkt4Ptr());
    }
    Pkt4Ptr msg = srv_->fake_sent_.front();
    srv_->fake_sent_.pop_front();

    // Copy the original message to simulate reception over the wire.
    msg->pack();
    Pkt4Ptr msg_copy(new Pkt4(static_cast<const uint8_t*>
                              (msg->getBuffer().getData()),
                              msg->getBuffer().getLength()));
    msg_copy->setRemoteAddr(msg->getLocalAddr());
    msg_copy->setLocalAddr(msg->getRemoteAddr());
    msg_copy->setIface(msg->getIface());

    msg_copy->unpack();

    return (msg_copy);
}

void
Dhcp4Client::sendMsg(const Pkt4Ptr& msg) {
    srv_->shutdown_ = false;
    if (use_relay_) {
        msg->setHops(1);
        msg->setGiaddr(relay_addr_);
        msg->setLocalAddr(server_facing_relay_addr_);
    }
    // Repack the message to simulate wire-data parsing.
    msg->pack();
    Pkt4Ptr msg_copy(new Pkt4(static_cast<const uint8_t*>
                              (msg->getBuffer().getData()),
                              msg->getBuffer().getLength()));
    msg_copy->setRemoteAddr(msg->getLocalAddr());
    msg_copy->setLocalAddr(dest_addr_);
    msg_copy->setIface("eth0");
    srv_->fakeReceive(msg_copy);
    srv_->run();
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
