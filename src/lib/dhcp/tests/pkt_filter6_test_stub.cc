// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <exceptions/exceptions.h>
#include <dhcp/tests/pkt_filter6_test_stub.h>
#include <netinet/in.h>
#include <list>

namespace {

/// @brief Retrieves a queue of sent messages.
std::list<isc::dhcp::Pkt6Ptr>& getSent() {
    static std::list<isc::dhcp::Pkt6Ptr> sent;
    return (sent);
}

}

namespace isc {
namespace dhcp {
namespace test {

PktFilter6TestStub::PktFilter6TestStub() {
    getSent().clear();
}

SocketInfo
PktFilter6TestStub::openSocket(const Iface&,
           const isc::asiolink::IOAddress& addr,
           const uint16_t port, const bool) {
    // Create a socket which may be used on select() but which is unlikely
    // to return any data.
    int sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        isc_throw(Unexpected, "PktFilter6TestStub: opening socket failed");
    }

    // Set reuse address
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, static_cast<const void*>(&flag),
                   sizeof(flag)) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "PktFilter6TestStub:: failed to set SO_REUSEADDR on"
                  " socket");
    }

    // Set no blocking
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "PktFilter6TestStub: failed to set O_NONBLOCK on"
                  " socket");
    }

    // Bind to the local address and random port.
    struct sockaddr_in6 local6;
    memset(&local6, 0, sizeof(local6));
    local6.sin6_family = AF_INET6;
#ifdef HAVE_SA_LEN
    local6.sin6_len = sizeof(local6);
#endif

    if (bind(sock, (struct sockaddr *)&local6, sizeof(local6)) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "PktFilter6TestStub: failed to bind socket");
    }

    return (SocketInfo(addr, port, sock));
}

Pkt6Ptr
PktFilter6TestStub::receive(const SocketInfo&) {
    return Pkt6Ptr();
}

bool
PktFilter6TestStub::joinMulticast(int, const std::string&,
                                  const std::string &) {
    return (true);
}

int
PktFilter6TestStub::send(const Iface&, uint16_t, const Pkt6Ptr& pkt) {
    getSent().push_back(pkt);
    return (0);
}

Pkt6Ptr
PktFilter6TestStub::popSent() {
    std::list<Pkt6Ptr>& sent = getSent();
    if (sent.empty()) {
        return (Pkt6Ptr());
    }
    Pkt6Ptr pkt = sent.front();
    sent.pop_front();
    return (pkt);
}

}
}
}
