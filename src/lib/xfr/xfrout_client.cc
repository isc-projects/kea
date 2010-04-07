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
#include "fd_share.h"
#include "xfrout_client.h"

using boost::asio::local::stream_protocol;

namespace isc {
namespace xfr {

void
XfroutClient::connect() {
    socket_.connect(stream_protocol::endpoint(file_path_));
}

void
XfroutClient::disconnect() {
    socket_.close();
}

void
XfroutClient::sendData(const uint8_t* msg_data, const uint16_t msg_len) {
    int count = 0;
    while (count < msg_len) {
        const int size = send(socket_.native(), msg_data + count,
                              msg_len - count, 0);
        if (size == -1) {
            isc_throw(XfroutError, "auth failed to send data to xfrout module");
        }
        count += size;
    }

    return;
}

int 
XfroutClient::sendXfroutRequestInfo(const int tcp_sock, uint8_t* msg_data,
                                    const uint16_t msg_len)
{
    if (-1 == send_fd(socket_.native(), tcp_sock)) {
        isc_throw(XfroutError,
                  "Fail to send socket descriptor to xfrout module");
    }

    sendData((uint8_t*)&msg_len, 2);
    sendData(msg_data, msg_len);
    
    int databuf = 0;
    if (recv(socket_.native(), &databuf, sizeof(int), 0) != 0) {
        isc_throw(XfroutError,
                  "xfr query hasn't been processed properly by xfrout module");
    }

    return 0;
}

} // End for xfr
} // End for isc

