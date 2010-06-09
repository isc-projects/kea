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

#include <cstdlib>
#include <cstring>
#include <iostream>

#include <asio.hpp>

#include "fd_share.h"
#include "xfrout_client.h"

using namespace std;
using asio::local::stream_protocol;

namespace isc {
namespace xfr {

struct XfroutClientImpl {
    XfroutClientImpl(const string& file);
    const std::string file_path_;
    asio::io_service io_service_;
    // The socket used to communicate with the xfrout server.
    stream_protocol::socket socket_;
};

XfroutClientImpl::XfroutClientImpl(const string& file) :
    file_path_(file), socket_(io_service_)
{}

XfroutClient::XfroutClient(const string& file) :
    impl_(new XfroutClientImpl(file))
{}

XfroutClient::~XfroutClient()
{
    delete impl_;
}

void
XfroutClient::connect() {
    impl_->socket_.connect(stream_protocol::endpoint(impl_->file_path_));
}

void
XfroutClient::disconnect() {
    impl_->socket_.close();
}

int 
XfroutClient::sendXfroutRequestInfo(const int tcp_sock, uint8_t* msg_data,
                                    const uint16_t msg_len)
{
    if (-1 == send_fd(impl_->socket_.native(), tcp_sock)) {
        isc_throw(XfroutError,
                  "Fail to send socket descriptor to xfrout module");
    }

    // XXX: this shouldn't be blocking send, even though it's unlikely to block.
    const uint8_t lenbuf[2] = { msg_len >> 8, msg_len & 0xff };
    if (send(impl_->socket_.native(), lenbuf, sizeof(lenbuf), 0) !=
        sizeof(lenbuf)) {
        isc_throw(XfroutError,
                  "failed to send XFR request length to xfrout module");
    }
    if (send(impl_->socket_.native(), msg_data, msg_len, 0) != msg_len) {
        isc_throw(XfroutError,
                  "failed to send XFR request data to xfrout module");
    }
    
    int databuf = 0;
    if (recv(impl_->socket_.native(), &databuf, sizeof(int), 0) != 0) {
        isc_throw(XfroutError,
                  "xfr query hasn't been processed properly by xfrout module");
    }

    return 0;
}

} // End for xfr
} // End for isc

