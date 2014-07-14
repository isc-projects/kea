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
#include <dhcp4/tests/dhcp4_client.h>
#include <cstdlib>

namespace isc {
namespace dhcp {
namespace test {

Dhcp4Client::Dhcp4Client() :
    curr_transid_(0),
    dest_addr_("255.255.255.255"),
    hwaddr_(generateHWAddr()),
    relay_addr_("10.0.0.2"),
    srv_(boost::shared_ptr<NakedDhcpv4Srv>(new NakedDhcpv4Srv(0))),
    use_relay_(false) {
}

Dhcp4Client::Dhcp4Client(boost::shared_ptr<NakedDhcpv4Srv>& srv) :
    curr_transid_(0),
    dest_addr_("255.255.255.255"),
    hwaddr_(generateHWAddr()),
    relay_addr_("10.0.0.2"),
    srv_(srv),
    use_relay_(false) {
}
Pkt4Ptr
Dhcp4Client::createMsg(const uint8_t msg_type) {
    Pkt4Ptr msg(new Pkt4(msg_type, curr_transid_++));
    msg->setHWAddr(hwaddr_);
    return (msg);
}

void
Dhcp4Client::doInform() {
    context_.query_ = createMsg(DHCPINFORM);
    sendMsg(context_.query_);
    context_.response_ = receiveOneMsg();
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

Pkt4Ptr
Dhcp4Client::receiveOneMsg() {
    // Return empty pointer if server hasn't responded.
    if (srv_->fake_sent_.empty()) {
        return (Pkt4Ptr());
    }
    Pkt4Ptr msg = srv_->fake_sent_.front();
    srv_->fake_sent_.pop_front();
    return (msg);
}

void
Dhcp4Client::sendMsg(const Pkt4Ptr& msg) {
    srv_->shutdown_ = false;
    if (use_relay_) {
        msg->setGiaddr(relay_addr_);
    }
    // Repack the message to simulate wire-data parsing.
    msg->pack();
    Pkt4Ptr msg_copy(new Pkt4(static_cast<const uint8_t*>
                              (msg->getBuffer().getData()),
                              msg->getBuffer().getLength()));
    msg_copy->setRemoteAddr(asiolink::IOAddress("0.0.0.0"));
    msg_copy->setLocalAddr(dest_addr_);
    msg_copy->setIface("eth0");
    srv_->fakeReceive(msg_copy);
    srv_->run();
}

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc
