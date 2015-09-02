// Copyright (C) 2010-2012, 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/asio.hpp>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <boost/static_assert.hpp>

using namespace boost::asio;
using boost::asio::ip::udp;
using boost::asio::ip::tcp;

using namespace std;

namespace isc {
namespace asiolink {

// XXX: we cannot simply construct the address in the initialization list,
// because we'd like to throw our own exception on failure.
IOAddress::IOAddress(const std::string& address_str) {
    boost::asio::error_code err;
    asio_address_ = ip::address::from_string(address_str, err);
    if (err) {
        isc_throw(IOError, "Failed to convert string to address '"
                  << address_str << "': " << err.message());
    }
}

IOAddress::IOAddress(const boost::asio::ip::address& asio_address) :
    asio_address_(asio_address)
{}

IOAddress::IOAddress(uint32_t v4address):
    asio_address_(boost::asio::ip::address_v4(v4address)) {

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
        const boost::asio::ip::address_v4::bytes_type bytes4 =
            asio_address_.to_v4().to_bytes();
        return (std::vector<uint8_t>(bytes4.begin(), bytes4.end()));
    }

    // Not V4 address, so must be a V6 address (else we could never construct
    // this object).
    const boost::asio::ip::address_v6::bytes_type bytes6 =
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

bool
IOAddress::isV6LinkLocal() const {
    if (!asio_address_.is_v6()) {
        return (false);
    }
    return (asio_address_.to_v6().is_link_local());
}

bool
IOAddress::isV6Multicast() const {
    if (!asio_address_.is_v6()) {
        return (false);
    }
    return (asio_address_.to_v6().is_multicast());
}

IOAddress::operator uint32_t() const {
    if (asio_address_.is_v4()) {
        return (asio_address_.to_v4().to_ulong());
    } else {
        isc_throw(BadValue, "Can't convert " << toText()
                  << " address to IPv4.");
    }
}

std::ostream&
operator<<(std::ostream& os, const IOAddress& address) {
    os << address.toText();
    return (os);
}

IOAddress
IOAddress::subtract(const IOAddress& a, const IOAddress& b) {
    if (a.getFamily() != b.getFamily()) {
        isc_throw(BadValue, "Both addresses have to be the same family");
    }
    if (a.isV4()) {
        // Subtracting v4 is easy. We have uint32_t operator.
        return (IOAddress(static_cast<uint32_t>(a) - static_cast<uint32_t>(b)));
    } else {
        // v6 is more involved.

        // Let's extract the raw data first.
        vector<uint8_t> a_vec = a.toBytes();
        vector<uint8_t> b_vec = b.toBytes();

        // ... and prepare the result
        vector<uint8_t> result(V6ADDRESS_LEN,0);

        // Carry is a boolean, but to avoid its frequent casting, let's
        // use uint8_t. Also, some would prefer to call it borrow, but I prefer
        // carry. Somewhat relevant discussion here:
        // http://en.wikipedia.org/wiki/Carry_flag#Carry_flag_vs._Borrow_flag
        uint8_t carry = 0;

        // Now perform subtraction with borrow.
        for (int i = a_vec.size() - 1; i >= 0; --i) {
            result[i] = a_vec[i] - b_vec[i] - carry;
            carry = (a_vec[i] < b_vec[i] + carry);
        }

        return (fromBytes(AF_INET6, &result[0]));
    }
}

IOAddress
IOAddress::increase(const IOAddress& addr) {
    std::vector<uint8_t> packed(addr.toBytes());

    // Start increasing the least significant byte
    for (int i = packed.size() - 1; i >= 0; --i) {
        // if we haven't overflowed (0xff -> 0x0), than we are done
        if (++packed[i] != 0) {
            break;
        }
    }

    return (IOAddress::fromBytes(addr.getFamily(), &packed[0]));
}


} // namespace asiolink
} // namespace isc
