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
#include <iostream>
#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <boost/bind.hpp>

#include <asio.hpp>
#include <asio/deadline_timer.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <log/dummylog.h>
#include <dns/opcode.h>
#include <dns/rcode.h>

#include <coroutine.h>
#include <asiolink/asiolink.h>

using namespace asio;
using asio::ip::udp;

using namespace std;
using namespace isc::dns;

namespace asiolink {

// Constructor - create socket on the fly

UDPSocket::UDPSocket(IOService& service) :
    socket_ptr_(new asio::ip::udp::socket(service.get_io_service())),
    socket_(*socket_ptr_)
{
}

// Destructor

UDPSocket::~UDPSocket()
{
    delete socket_ptr_;
}

// Open the socket.  Throws an error on failure
// TODO: Make the open more resolient

bool
UDPSocket::open(const IOEndpoint* endpoint, IOCompletionCallback&) {
    if (endpoint->getFamily() == AF_INET) {
        socket_.open(asio::ip::udp::v4());
    }
    else {
        socket_.open(asio::ip::udp::v6());
    }

    // Ensure it can send and receive 4K buffers.
    socket_.set_option(asio::socket_base::send_buffer_size(MAX_SIZE));
    socket_.set_option(asio::socket_base::receive_buffer_size(MAX_SIZE));
;
    // Allow reuse of an existing port/address
    socket_.set_option(asio::socket_base::reuse_address(true));

    return (false);
}

// Send a message.

void
UDPSocket::asyncSend(const void* data, size_t length,
    const IOEndpoint* endpoint, IOCompletionCallback& callback)
{
    // Upconverting.  Not nice, but we have the problem that in the abstract
    // layer we are given an IOEndpoint.  For UDP code it is a UDPEndpoint
    // and for TCP code a TCPEndpoint.  However the member that we are
    // after - the asio endpoint - is different for UPD and TCP and there is
    // no common ancestor.  Hence the promotion here.
    assert(endpoint->getProtocol() == IPPROTO_UDP);
    const UDPEndpoint* udp_endpoint = static_cast<const UDPEndpoint*>(endpoint);

    socket_.async_send_to(buffer(data, length), udp_endpoint->getASIOEndpoint(),
        callback);
}

// Receive a message. Note that the "cumulative" argument is ignored - every UDP
// receive is put into the buffer beginning at the start - there is no concept
// receiving a subsequent part of a message.

void
UDPSocket::asyncReceive(void* data, size_t length, size_t, IOEndpoint* endpoint,
    IOCompletionCallback& callback)
{
    // Upconvert the endpoint again.
    assert(endpoint->getProtocol() == IPPROTO_UDP);
    UDPEndpoint* udp_endpoint = static_cast<UDPEndpoint*>(endpoint);

    socket_.async_receive_from(buffer(data, length),
        udp_endpoint->getASIOEndpoint(), callback);
}

// Cancel I/O on the socket
void
UDPSocket::cancel() {
    socket_.cancel();
}

// Close the socket down

void
UDPSocket::close() {
    socket_.close();
}

} // namespace asiolink
