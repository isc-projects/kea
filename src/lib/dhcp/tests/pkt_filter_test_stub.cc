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
