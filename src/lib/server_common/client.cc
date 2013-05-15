// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <sstream>

#include <acl/ip_check.h>

#include <asiolink/io_endpoint.h>
#include <asiolink/io_message.h>

#include <server_common/client.h>

using namespace isc::acl;
using namespace isc::server_common;
using namespace isc::asiolink;

struct Client::ClientImpl {
    ClientImpl(const IOMessage& request_message) :
        request_(request_message),
        request_src_(request_.getRemoteEndpoint().getSockAddr())
    {}

    const IOMessage& request_;
    const IPAddress request_src_;
};

Client::Client(const IOMessage& request_message) :
    impl_(new ClientImpl(request_message))
{}

Client::~Client() {
    delete impl_;
}

const IOEndpoint&
Client::getRequestSourceEndpoint() const {
    return (impl_->request_.getRemoteEndpoint());
}

const IPAddress&
Client::getRequestSourceIPAddress() const {
    return (impl_->request_src_);
}

std::string
Client::toText() const {
    std::stringstream ss;
    const asiolink::IOAddress& addr =
        impl_->request_.getRemoteEndpoint().getAddress();
    if (addr.isV6()) {
        ss << '[' << addr.toText() << ']';
    } else {
        ss << addr.toText();
    }
    ss << ':' << impl_->request_.getRemoteEndpoint().getPort();
    return (ss.str());
}

std::ostream&
isc::server_common::operator<<(std::ostream& os, const Client& client) {
    return (os << client.toText());
}
