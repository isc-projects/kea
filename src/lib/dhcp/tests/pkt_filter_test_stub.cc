// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <dhcp/tests/pkt_filter_test_stub.h>

namespace isc {
namespace dhcp {
namespace test {

PktFilterTestStub::PktFilterTestStub()
    : direct_response_supported_(true) {
}

bool
PktFilterTestStub::isDirectResponseSupported() const {
    return (direct_response_supported_);
}

SocketInfo
PktFilterTestStub::openSocket(Iface&,
           const isc::asiolink::IOAddress& addr,
           const uint16_t port, const bool, const bool) {
    int fd = open("/dev/null", O_RDONLY);
    if (fd < 0) {
        const char* errmsg = strerror(errno);
        isc_throw(Unexpected,
                  "PktFilterTestStub: cannot open /dev/null:" << errmsg);
    }

    return (SocketInfo(addr, port, fd));
}

Pkt4Ptr
PktFilterTestStub::receive(Iface&, const SocketInfo&) {
    return Pkt4Ptr();
}

int
PktFilterTestStub::send(const Iface&, uint16_t, const Pkt4Ptr&) {
    return (0);
}

}
}
}
