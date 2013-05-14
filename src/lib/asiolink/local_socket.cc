// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/local_socket.h>
#include <asiolink/io_service.h>

#include <asio.hpp>

#include <boost/bind.hpp>

#include <string>
#include <sys/socket.h>

namespace isc {
namespace asiolink {

class LocalSocket::Impl {
public:
    Impl(IOService& io_service, int fd) :
        asio_sock_(io_service.get_io_service())
    {
        asio_sock_.assign(asio::local::stream_protocol(), fd, ec_);
    }

    void readCompleted(const asio::error_code& ec, ReadCallback user_callback);

    asio::local::stream_protocol::socket asio_sock_;
    asio::error_code ec_;
};

void
LocalSocket::Impl::readCompleted(const asio::error_code& ec,
                                 ReadCallback user_callback)
{
    // assumption check: we pass non empty string iff ec indicates an error.
    const std::string& err_msg = ec ? ec.message() : std::string();
    assert(ec || err_msg.empty());

    user_callback(err_msg);
}

LocalSocket::LocalSocket(IOService& io_service, int fd) :
    impl_(new Impl(io_service, fd))
{}

LocalSocket::~LocalSocket() {
    delete impl_;
}

int
LocalSocket::getNative() const {
    return (impl_->asio_sock_.native());
}

int
LocalSocket::getProtocol() const {
    return (AF_UNIX);
}

void
LocalSocket::asyncRead(const ReadCallback& callback, void* buf,
                       size_t buflen)
{
    asio::async_read(impl_->asio_sock_, asio::buffer(buf, buflen),
                     boost::bind(&Impl::readCompleted, impl_, _1, callback));
}

} // namespace asiolink
} // namespace isc
