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
#include <fcntl.h>

#include <dhcp/tests/pkt_filter6_test_stub.h>

namespace isc {
namespace dhcp {
namespace test {

PktFilter6TestStub::PktFilter6TestStub() {
}

SocketInfo
PktFilter6TestStub::openSocket(const Iface&,
           const isc::asiolink::IOAddress& addr,
           const uint16_t port, const bool) {
    return (SocketInfo(addr, port, 0));
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
PktFilter6TestStub::send(const Iface&, uint16_t, const Pkt6Ptr&) {
    return (0);
}

}
}
}
