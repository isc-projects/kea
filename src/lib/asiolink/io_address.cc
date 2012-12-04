// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <unistd.h>             // for some IPC/network system calls
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <boost/static_assert.hpp>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;

namespace isc {
namespace asiolink {

// XXX: we cannot simply construct the address in the initialization list,
// because we'd like to throw our own exception on failure.
IOAddress::IOAddress(const std::string& address_str) {
    asio::error_code err;
    asio_address_ = ip::address::from_string(address_str, err);
    if (err) {
        isc_throw(IOError, "Failed to convert string to address '"
                  << address_str << "': " << err.message());
    }
}

IOAddress::IOAddress(const asio::ip::address& asio_address) :
    asio_address_(asio_address)
{}

IOAddress::IOAddress(uint32_t v4address):
    asio_address_(asio::ip::address_v4(v4address)) {

}

string
IOAddress::toText() const {
    return (asio_address_.to_string());
}

IOAddress
IOAddress::fromBytes(short family, const uint8_t* data) {
    if (data == NULL) {
        isc_throw(BadValue, "NULL pointer received.");
    } else
    if ( (family != AF_INET) && (family != AF_INET6) ) {
        isc_throw(BadValue, "Invalid family type. Only AF_INET and AF_INET6"
                  << "are supported");
    }

    BOOST_STATIC_ASSERT(INET6_ADDRSTRLEN >= INET_ADDRSTRLEN);
    char addr_str[INET6_ADDRSTRLEN];
    inet_ntop(family, data, addr_str, INET6_ADDRSTRLEN);
    return IOAddress(string(addr_str));
}

std::vector<uint8_t>
IOAddress::toBytes() const {
    if (asio_address_.is_v4()) {
        const asio::ip::address_v4::bytes_type bytes4 =
            asio_address_.to_v4().to_bytes();
        return (std::vector<uint8_t>(bytes4.begin(), bytes4.end()));
    }

    // Not V4 address, so must be a V6 address (else we could never construct
    // this object).
    const asio::ip::address_v6::bytes_type bytes6 =
        asio_address_.to_v6().to_bytes();
    return (std::vector<uint8_t>(bytes6.begin(), bytes6.end()));
}

short
IOAddress::getFamily() const {
    if (asio_address_.is_v4()) {
        return (AF_INET);
    } else {
        return (AF_INET6);
    }
}

const asio::ip::address&
IOAddress::getAddress() const {
    return asio_address_;
}

IOAddress::operator uint32_t() const {
    if (getAddress().is_v4()) {
        return (getAddress().to_v4().to_ulong());
    } else {
        isc_throw(BadValue, "Can't convert " << toText()
                  << " address to IPv4.");
    }
}

} // namespace asiolink
} // namespace isc
