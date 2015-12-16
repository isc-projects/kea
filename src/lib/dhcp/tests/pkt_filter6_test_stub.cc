// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
