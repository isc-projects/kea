// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/pkt6.h>
#include <dhcp/tests/pkt_filter6_test_utils.h>

#include <boost/foreach.hpp>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

PktFilter6Test::PktFilter6Test(const uint16_t port)
    : port_(port),
      sock_info_(isc::asiolink::IOAddress("::1"), port, -1, -1),
      send_msg_sock_(-1) {
    // Initialize ifname_ and ifindex_.
    loInit();
    // Initialize test_message_.
    initTestMessage();
}

PktFilter6Test::~PktFilter6Test() {
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
PktFilter6Test::initTestMessage() {
    // Let's create a DHCPv6 message instance.
    test_message_.reset(new Pkt6(DHCPV6_ADVERTISE, 123));

    // Set required fields.
    test_message_->setLocalAddr(IOAddress("::1"));
    test_message_->setRemoteAddr(IOAddress("::1"));
    test_message_->setRemotePort(port_);
    test_message_->setLocalPort(port_ + 1);
    test_message_->setIndex(ifindex_);
    test_message_->setIface(ifname_);

    try {
        test_message_->pack();
    } catch (const isc::Exception& ex) {
        ADD_FAILURE() << "failed to create test message for PktFilter6Test";
    }
}

void
PktFilter6Test::loInit() {
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
PktFilter6Test::sendMessage() {
    // DHCPv6 message will be sent over loopback interface.
    Iface iface(ifname_, ifindex_);
    IOAddress addr("::1");

    // Initialize the source address and port.
    struct sockaddr_in6 addr6;
    memset(&addr6, 0, sizeof(addr6));
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port_);
    memcpy(&addr6.sin6_addr, &addr.toBytes()[0], sizeof(addr6.sin6_addr));

    // Open socket and bind to source address and port.
    send_msg_sock_ = socket(AF_INET6, SOCK_DGRAM, 0);
    ASSERT_GE(send_msg_sock_, 0);

    ASSERT_GE(bind(send_msg_sock_, (struct sockaddr *)&addr6,
                   sizeof(addr6)), 0);

    // Set the destination address and port.
    struct sockaddr_in6 dest_addr6;
    memset(&dest_addr6, 0, sizeof(sockaddr_in6));
    dest_addr6.sin6_family = AF_INET6;
    dest_addr6.sin6_port = htons(port_ + 1);
    memcpy(&dest_addr6.sin6_addr, &addr.toBytes()[0], 16);

    // Initialize the message header structure, required by sendmsg.
    struct msghdr m;
    memset(&m, 0, sizeof(m));
    m.msg_name = &dest_addr6;
    m.msg_namelen = sizeof(dest_addr6);
    // The iovec structure holds the packet data.
    struct iovec v;
    memset(&v, 0, sizeof(v));
    v.iov_base = const_cast<void *>(test_message_->getBuffer().getData());
    v.iov_len = test_message_->getBuffer().getLength();
    // Assign the iovec to msghdr structure.
    m.msg_iov = &v;
    m.msg_iovlen = 1;
    // We should be able to send the whole message. The sendmsg function should
    // return the number of bytes sent, which is equal to the size of our
    // message.
    ASSERT_EQ(sendmsg(send_msg_sock_, &m, 0),
              test_message_->getBuffer().getLength());
    close(send_msg_sock_);
    send_msg_sock_ = -1;

}

void
PktFilter6Test::testDgramSocket(const int sock) const {
    // Check that socket has been opened.
    ASSERT_GE(sock, 0);

    // Verify that the socket belongs to AF_INET family.
    sockaddr_in6 sock_address;
    socklen_t sock_address_len = sizeof(sock_address);
    ASSERT_EQ(0, getsockname(sock,
                             reinterpret_cast<sockaddr*>(&sock_address),
                             &sock_address_len));
    EXPECT_EQ(AF_INET6, sock_address.sin6_family);

    // Verify that the socket is bound the appropriate address.
    char straddr[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &sock_address.sin6_addr, straddr, sizeof(straddr));
    std::string bind_addr(straddr);
    EXPECT_EQ("::1", bind_addr);

    // Verify that the socket is bound to appropriate port.
    EXPECT_EQ(port_, ntohs(sock_address.sin6_port));

    // Verify that the socket has SOCK_DGRAM type.
    int sock_type;
    socklen_t sock_type_len = sizeof(sock_type);
    ASSERT_EQ(0, getsockopt(sock, SOL_SOCKET, SO_TYPE,
                            &sock_type, &sock_type_len));
    EXPECT_EQ(SOCK_DGRAM, sock_type);
}

void
PktFilter6Test::testRcvdMessage(const Pkt6Ptr& rcvd_msg) const {
    // Currently, we don't send any payload in the message.
    // Let's just check that the transaction id matches so as we
    // are sure that we received the message that we expected.
    EXPECT_EQ(test_message_->getTransid(), rcvd_msg->getTransid());
}

PktFilter6Stub::PktFilter6Stub()
    : open_socket_count_ (0) {
}

SocketInfo
PktFilter6Stub::openSocket(const Iface& iface, const isc::asiolink::IOAddress& addr,
                           const uint16_t port, const bool) {
    // Check if there is any other socket bound to the specified address
    // and port on this interface.
    BOOST_FOREACH(SocketInfo socket, iface.getSockets()) {
        if ((socket.addr_ == addr) && (socket.port_ == port)) {
            isc_throw(SocketConfigError, "test socket bind error");
        }
    }
    ++open_socket_count_;
    return (SocketInfo(addr, port, 0));
}

Pkt6Ptr
PktFilter6Stub::receive(const SocketInfo&) {
    return Pkt6Ptr();
}

int
PktFilter6Stub::send(const Iface&, uint16_t, const Pkt6Ptr&) {
    return (0);
}


} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
