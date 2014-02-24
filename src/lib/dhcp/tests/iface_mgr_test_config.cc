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

#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcp/pkt_filter_inet6.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_filter_test_stub.h>
#include <dhcp/tests/pkt_filter6_test_stub.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

IfaceMgrTestConfig::IfaceMgrTestConfig(const bool default_config) {
    IfaceMgr::instance().closeSockets();
    IfaceMgr::instance().clearIfaces();
    packet_filter4_ = PktFilterPtr(new PktFilterTestStub());
    packet_filter6_ = PktFilter6Ptr(new PktFilter6TestStub());
    IfaceMgr::instance().setPacketFilter(packet_filter4_);
    IfaceMgr::instance().setPacketFilter(packet_filter6_);

    // Create default set of fake interfaces: lo, eth0 and eth1.
    if (default_config) {
        createIfaces();
    }
}

IfaceMgrTestConfig::~IfaceMgrTestConfig() {
    IfaceMgr::instance().closeSockets();
    IfaceMgr::instance().clearIfaces();
    IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterInet()));
    IfaceMgr::instance().setPacketFilter(PktFilter6Ptr(new PktFilterInet6()));

    IfaceMgr::instance().detectIfaces();
}

void
IfaceMgrTestConfig::addAddress(const std::string& iface_name,
                               const IOAddress& address) {
    Iface* iface = IfaceMgr::instance().getIface(iface_name);
    if (iface == NULL) {
        isc_throw(isc::BadValue, "interface '" << iface_name
                  << "' doesn't exist");
    }
    iface->addAddress(address);
}

void
IfaceMgrTestConfig::addIface(const Iface& iface) {
    IfaceMgr::instance().addInterface(iface);
}

void
IfaceMgrTestConfig::addIface(const std::string& name, const int ifindex) {
    IfaceMgr::instance().addInterface(createIface(name, ifindex));
}

Iface
IfaceMgrTestConfig::createIface(const std::string &name, const int ifindex) {
    Iface iface(name, ifindex);
    if (name == "lo") {
        iface.flag_loopback_ = true;
    }
    iface.flag_multicast_ = true;
    // On BSD systems, the SO_BINDTODEVICE option is not supported.
    // Therefore the IfaceMgr will throw an exception on attempt to
    // open sockets on more than one broadcast-capable interface at
    // the same time. In order to prevent this error, we mark all
    // interfaces broadcast-incapable for unit testing.
    iface.flag_broadcast_ = false;
    iface.flag_up_ = true;
    iface.flag_running_ = true;
    iface.inactive4_ = false;
    iface.inactive6_ = false;
    return (iface);
}

void
IfaceMgrTestConfig::createIfaces() {
    // local loopback
    addIface("lo", 0);
    addAddress("lo", IOAddress("127.0.0.1"));
    addAddress("lo", IOAddress("::1"));
    // eth0
    addIface("eth0", 1);
    addAddress("eth0", IOAddress("10.0.0.1"));
    addAddress("eth0", IOAddress("fe80::3a60:77ff:fed5:cdef"));
    addAddress("eth0", IOAddress("2001:db8:1::1"));
    // eth1
    addIface("eth1", 2);
    addAddress("eth1", IOAddress("192.0.2.3"));
    addAddress("eth1", IOAddress("fe80::3a60:77ff:fed5:abcd"));

}

void
IfaceMgrTestConfig::setDirectResponse(const bool direct_resp) {
    boost::shared_ptr<PktFilterTestStub> stub =
        boost::dynamic_pointer_cast<PktFilterTestStub>(getPacketFilter4());
    if (!stub) {
        isc_throw(isc::Unexpected, "unable to set direct response capability for"
                  " test packet filter - current packet filter is not"
                  " of a PktFilterTestStub");
    }
    stub->direct_response_supported_ = direct_resp;
}

void
IfaceMgrTestConfig::setIfaceFlags(const std::string& name,
                                  const FlagLoopback& loopback,
                                  const FlagUp& up,
                                  const FlagRunning& running,
                                  const FlagInactive4& inactive4,
                                  const FlagInactive6& inactive6) {
    Iface* iface = IfaceMgr::instance().getIface(name);
    if (iface == NULL) {
        isc_throw(isc::BadValue, "interface '" << name << "' doesn't exist");
    }
    iface->flag_loopback_ = loopback.flag_;
    iface->flag_up_ = up.flag_;
    iface->flag_running_ = running.flag_;
    iface->inactive4_ = inactive4.flag_;
    iface->inactive6_ = inactive6.flag_;
}

}
}
}
