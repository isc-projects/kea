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

// $Id$

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>

#include <asiolink/asiolink.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;

namespace asiolink {

// XXX: we cannot simply construct the address in the initialization list,
// because we'd like to throw our own exception on failure.
IOAddress::IOAddress(const string& address_str) {
    error_code err;
    asio_address_ = ip::address::from_string(address_str, err);
    if (err) {
        isc_throw(IOError, "Failed to convert string to address '"
                  << address_str << "': " << err.message());
    }
}

IOAddress::IOAddress(const ip::address& asio_address) :
    asio_address_(asio_address)
{}

string
IOAddress::toText() const {
    return (asio_address_.to_string());
}

short
IOAddress::getFamily() const {
    if (asio_address_.is_v4()) {
        return (AF_INET);
    } else {
        return (AF_INET6);
    }
}

}
