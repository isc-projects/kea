// Copyright (C) 2013-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/pkt4.h>
#include <dhcp/tests/pkt_filter_test_utils.h>

using namespace isc::asiolink;
using namespace boost::posix_time;

namespace isc {
namespace dhcp {
namespace test {

PktFilterTest::PktFilterTest(const uint16_t port)
    : port_(port),
      sock_info_(isc::asiolink::IOAddress("127.0.0.1"), port, -1, -1),
      send_msg_sock_(-1),
      start_time_(PktEvent::now()) {
    // Initialize ifname_ and ifindex_.
    loInit();
    // Initialize test_message_.
    initTestMessage();
}

PktFilterTest::~PktFilterTest() {
    // Cleanup after each test. This guarantees
    // that the sockets do not hang after a test.
    if (sock_info_.sockfd_ >= 0) {
        close(sock_info_.sockfd_);
    }
    if (sock_info_.fallbackfd_ >=0) {
        close(sock_info_.fallbackfd_);
    }
    if (send_msg_sock_ >= 0) {
        close(send_msg_sock_);
    }
}

void
PktFilterTest::initTestMessage() {
    // Let's create a DHCPv4 message instance.
    test_message_.reset(new Pkt4(DHCPOFFER, 0));

    // Set required fields.
    test_message_->setLocalAddr(IOAddress("127.0.0.1"));
    test_message_->setRemoteAddr(IOAddress("127.0.0.1"));
    test_message_->setRemotePort(port_);
    test_message_->setLocalPort(port_ + 1);
    test_message_->setIndex(ifindex_);
    test_message_->setIface(ifname_);
    test_message_->setHops(6);
    test_message_->setSecs(42);
    test_message_->setCiaddr(IOAddress("192.0.2.1"));
    test_message_->setSiaddr(IOAddress("192.0.2.2"));
    test_message_->setYiaddr(IOAddress("192.0.2.3"));
    test_message_->setGiaddr(IOAddress("192.0.2.4"));

    try {
        test_message_->pack();
    } catch (const isc::Exception& ex) {
        ADD_FAILURE() << "failed to create test message for PktFilterTest";
    }
}

void
PktFilterTest::loInit() {
    if (if_nametoindex("lo") > 0) {
        ifname_ = "lo";
        ifindex_ = if_nametoindex("lo");

    } else if (if_nametoindex("lo0") > 0) {
        ifname_ = "lo0";
        ifindex_ = if_nametoindex("lo0");

    } else {
        std::cout << "Failed to detect loopback interface. Neither "
                  << "lo nor lo0 worked. Giving up." << std::endl;
        FAIL();

    }
}

void
PktFilterTest::sendMessage(const IOAddress& dest) {

    // Packet will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("127.0.0.1");

    struct sockaddr_in addr4;
    memset(&addr4, 0, sizeof(sockaddr));
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port_ + 1);

    send_msg_sock_ = socket(AF_INET, SOCK_DGRAM, 0);
    ASSERT_GE(send_msg_sock_, 0);

    ASSERT_GE(bind(send_msg_sock_, (struct sockaddr *)&addr4,
                   sizeof(addr4)), 0);

    struct sockaddr_in dest_addr4;
    memset(&dest_addr4, 0, sizeof(sockaddr));
    dest_addr4.sin_family = AF_INET;
    dest_addr4.sin_port = htons(port_);
    dest_addr4.sin_addr.s_addr = htonl(dest.toUint32());
    ASSERT_EQ(sendto(send_msg_sock_, test_message_->getBuffer().getData(),
                     test_message_->getBuffer().getLength(), 0,
                     reinterpret_cast<struct sockaddr*>(&dest_addr4),
                     sizeof(sockaddr)), test_message_->getBuffer().getLength());
    close(send_msg_sock_);
    send_msg_sock_ = -1;

}

void
PktFilterTest::testDgramSocket(const int sock) const {
    // Check that socket has been opened.
    ASSERT_GE(sock, 0);

    // Verify that the socket belongs to AF_INET family.
    sockaddr_in sock_address;
    socklen_t sock_address_len = sizeof(sock_address);
    ASSERT_EQ(0, getsockname(sock,
                             reinterpret_cast<sockaddr*>(&sock_address),
                             &sock_address_len));
    EXPECT_EQ(AF_INET, sock_address.sin_family);

    // Verify that the socket is bound the appropriate address.
    const std::string bind_addr(inet_ntoa(sock_address.sin_addr));
    EXPECT_EQ("127.0.0.1", bind_addr);

    // Verify that the socket is bound to appropriate port.
    EXPECT_EQ(port_, ntohs(sock_address.sin_port));

    // Verify that the socket has SOCK_DGRAM type.
    int sock_type;
    socklen_t sock_type_len = sizeof(sock_type);
    ASSERT_EQ(0, getsockopt(sock, SOL_SOCKET, SO_TYPE,
                            &sock_type, &sock_type_len));
    EXPECT_EQ(SOCK_DGRAM, sock_type);
}

void
PktFilterTest::testRcvdMessage(const Pkt4Ptr& rcvd_msg) const {
    EXPECT_EQ(test_message_->getHops(), rcvd_msg->getHops());
    EXPECT_EQ(test_message_->getOp(),   rcvd_msg->getOp());
    EXPECT_EQ(test_message_->getSecs(), rcvd_msg->getSecs());
    EXPECT_EQ(test_message_->getFlags(), rcvd_msg->getFlags());
    EXPECT_EQ(test_message_->getCiaddr(), rcvd_msg->getCiaddr());
    EXPECT_EQ(test_message_->getSiaddr(), rcvd_msg->getSiaddr());
    EXPECT_EQ(test_message_->getYiaddr(), rcvd_msg->getYiaddr());
    EXPECT_EQ(test_message_->getGiaddr(), rcvd_msg->getGiaddr());
    EXPECT_EQ(test_message_->getTransid(), rcvd_msg->getTransid());
    EXPECT_TRUE(test_message_->getSname() == rcvd_msg->getSname());
    EXPECT_TRUE(test_message_->getFile() == rcvd_msg->getFile());
    EXPECT_EQ(test_message_->getHtype(), rcvd_msg->getHtype());
    EXPECT_EQ(test_message_->getHlen(), rcvd_msg->getHlen());
}

void
PktFilterTest::testRcvdMessageAddressPort(const Pkt4Ptr& rcvd_msg) const {
    EXPECT_EQ(test_message_->getRemoteAddr(), rcvd_msg->getLocalAddr());
    EXPECT_EQ(test_message_->getLocalAddr(), rcvd_msg->getRemoteAddr());
    EXPECT_EQ(test_message_->getRemotePort(), rcvd_msg->getLocalPort());
    EXPECT_EQ(test_message_->getLocalPort(), rcvd_msg->getRemotePort());
}

void
PktFilterTest::testReceivedPktEvents(const PktPtr& msg,
                                     bool so_time_supported) const {
    std::list<std::string> expected_events;
    if (so_time_supported) {
        expected_events.push_back(PktEvent::SOCKET_RECEIVED);
    }

    expected_events.push_back(PktEvent::BUFFER_READ);
    testPktEvents(msg, start_time_, expected_events);
}

void
PktFilterTest::testPktEvents(const PktPtr& msg, ptime start_time,
                             std::list<std::string> expected_events) const {
    ASSERT_NE(start_time, PktEvent::EMPTY_TIME());
    auto events = msg->getPktEvents();
    ASSERT_EQ(events.size(), expected_events.size());
    ptime prev_time = start_time;
    auto expected_event = expected_events.begin();
    for (auto const& event : events) {
        ASSERT_EQ(event.label_, *expected_event);
        EXPECT_GE(event.timestamp_, prev_time);
        prev_time = event.timestamp_;
        ++expected_event;
    }
}

bool
PktFilterStub::isDirectResponseSupported() const {
    return (true);
}

bool
PktFilterStub::isSocketReceivedTimeSupported() const {
    return (true);
}

SocketInfo
PktFilterStub::openSocket(Iface&,
           const isc::asiolink::IOAddress& addr,
           const uint16_t port, const bool, const bool) {
    return (SocketInfo(addr, port, 0));
}

Pkt4Ptr
PktFilterStub::receive(Iface&, const SocketInfo&) {
    return Pkt4Ptr();
}

int
PktFilterStub::send(const Iface&, uint16_t, const Pkt4Ptr&) {
    return (0);
}


} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
