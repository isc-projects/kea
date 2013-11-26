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


#include <dhcp/pkt4.h>
#include <dhcp/tests/pkt_filter_test_utils.h>

namespace isc {
namespace dhcp {
namespace test {

PktFilterTest::PktFilterTest(const uint16_t port)
    : port_(port),
      sock_info_(isc::asiolink::IOAddress("127.0.0.1"), port, -1, -1) {
    // Initialize ifname_ and ifindex_.
    loInit();
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

bool
PktFilterStub::isDirectResponseSupported() const {
    return (true);
}

SocketInfo
PktFilterStub::openSocket(const Iface&,
           const isc::asiolink::IOAddress& addr,
           const uint16_t port, const bool, const bool) {
    return (SocketInfo(addr, port, 0));
}

Pkt4Ptr
PktFilterStub::receive(const Iface&, const SocketInfo&) {
    return Pkt4Ptr();
}

int
PktFilterStub::send(const Iface&, uint16_t, const Pkt4Ptr&) {
    return (0);
}


} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
