// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/asio.hpp>

#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/udp_endpoint.h>

#include <boost/lexical_cast.hpp>

#include <cassert>
#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

namespace isc {
namespace asiolink {

const IOEndpoint*
IOEndpoint::create(const int protocol, const IOAddress& address,
                   const unsigned short port)
{
    if (protocol == IPPROTO_UDP) {
        return (new UDPEndpoint(address, port));
    } else if (protocol == IPPROTO_TCP) {
        return (new TCPEndpoint(address, port));
    }
    isc_throw(IOError,
              "IOEndpoint creation attempt for unsupported protocol: " <<
              protocol);
}

bool
IOEndpoint::operator==(const IOEndpoint& other) const {
    return (getProtocol() == other.getProtocol() &&
            getPort() == other.getPort() &&
            getFamily() == other.getFamily() &&
            getAddress() == other.getAddress());
}

bool
IOEndpoint::operator!=(const IOEndpoint& other) const {
    return (!operator==(other));
}

ostream&
operator<<(ostream& os, const IOEndpoint& endpoint) {
    if (endpoint.getFamily() == AF_INET6) {
        os << "[" << endpoint.getAddress() << "]";
    } else {
        // In practice this should be AF_INET, but it's not guaranteed by
        // the interface.  We'll use the result of textual address
        // representation opaquely.
        os << endpoint.getAddress();
    }
    os << ":" << boost::lexical_cast<string>(endpoint.getPort());
    return (os);
}
} // namespace asiolink
} // namespace isc
