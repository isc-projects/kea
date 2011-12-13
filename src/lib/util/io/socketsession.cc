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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <netinet/in.h>

#include <errno.h>
#include <stdint.h>
#include <string.h>

#include <cassert>
#include <string>
#include <vector>

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include "fd_share.h"
#include "socketsession.h"
#include "sockaddr_util.h"

using namespace std;

namespace isc {
namespace util {
namespace io {

using namespace internal;

struct SocketSessionForwarder::ForwarderImpl {
    ForwarderImpl() : buf_(512) {}
    struct sockaddr_un sock_un_;
    socklen_t sock_un_len_;
    int fd_;
    OutputBuffer buf_;
};

SocketSessionForwarder::SocketSessionForwarder(const std::string& unix_file) :
    impl_(NULL)
{
    ForwarderImpl impl;
    if (sizeof(impl.sock_un_.sun_path) - 1 < unix_file.length()) {
        isc_throw(SocketSessionError,
                  "File name for a UNIX domain socket is too long: " <<
                  unix_file);
    }
    impl.sock_un_.sun_family = AF_UNIX;
    strncpy(impl.sock_un_.sun_path, unix_file.c_str(),
            sizeof(impl.sock_un_.sun_path));
    assert(impl.sock_un_.sun_path[sizeof(impl.sock_un_.sun_path) - 1] == '\0');
    impl.sock_un_len_ = 2 + unix_file.length();
#ifdef HAVE_SA_LEN
    impl.sock_un_.sun_len = sock_un_len_;
#endif
    impl.fd_ = -1;

    impl_ = new ForwarderImpl;
    *impl_ = impl;
}

SocketSessionForwarder::~SocketSessionForwarder() {
    if (impl_->fd_ != -1) {
        close();
    }
    delete impl_;
}

void
SocketSessionForwarder::connectToReceptor() {
    if (impl_->fd_ != -1) {
        isc_throw(SocketSessionError, "Duplicate connect to UNIX domain "
                  "endpoint " << impl_->sock_un_.sun_path);
    }

    impl_->fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (impl_->fd_ == -1) {
        isc_throw(SocketSessionError, "Failed to create a UNIX domain socket: "
                  << strerror(errno));
    }
    if (connect(impl_->fd_, convertSockAddr(&impl_->sock_un_),
                impl_->sock_un_len_) == -1) {
        close();   // note: this is the internal method, not ::close()
        isc_throw(SocketSessionError, "Failed to connect to UNIX domain "
                  "endpoint " << impl_->sock_un_.sun_path << ": " <<
                  strerror(errno));
    }
    int bufsize = 65536 * 2;
    if (setsockopt(impl_->fd_, SOL_SOCKET, SO_SNDBUF, &bufsize,
                   sizeof(bufsize)) == -1) {
        isc_throw(SocketSessionError, "failed to enlarge receive buffer size");
    }
}

void
SocketSessionForwarder::close() {
    if (impl_->fd_ == -1) {
        isc_throw(SocketSessionError, "Attempt of close before connect");
    }
    ::close(impl_->fd_);
    impl_->fd_ = -1;
}

void
SocketSessionForwarder::push(int sock, int family, int sock_type, int protocol,
                             const struct sockaddr& local_end,
                             const struct sockaddr& remote_end,
                             const void* data, size_t data_len)
{
    if (impl_->fd_ == -1) {
        isc_throw(SocketSessionError, "Attempt of push before connect");
    }
    if ((local_end.sa_family != AF_INET && local_end.sa_family != AF_INET6) ||
        (remote_end.sa_family != AF_INET && remote_end.sa_family != AF_INET6))
    {
        isc_throw(SocketSessionError, "Invalid address family: must be "
                  "AF_INET or AF_INET6; " <<
                  static_cast<int>(local_end.sa_family) << ", " <<
                  static_cast<int>(remote_end.sa_family) << " given");
    }
    if (family != local_end.sa_family || family != remote_end.sa_family) {
        isc_throw(SocketSessionError, "Inconsistent address family: must be "
                  << static_cast<int>(family) << "; "
                  << static_cast<int>(local_end.sa_family) << ", "
                  << static_cast<int>(remote_end.sa_family) << " given");
    }

    const int e = send_fd(impl_->fd_, sock);
    if (e != 0) {
        isc_throw(SocketSessionError, "FD passing failed: " << e);
    }

    impl_->buf_.clear();
    // Leave the space for the header length
    impl_->buf_.skip(sizeof(uint16_t));
    // Socket properties: family, type, protocol
    impl_->buf_.writeUint32(static_cast<uint32_t>(family));
    impl_->buf_.writeUint32(static_cast<uint32_t>(sock_type));
    impl_->buf_.writeUint32(static_cast<uint32_t>(protocol));
    // Local endpoint
    impl_->buf_.writeUint32(static_cast<uint32_t>(getSALength(local_end)));
    impl_->buf_.writeData(&local_end, getSALength(local_end));
    // Remote endpoint
    impl_->buf_.writeUint32(static_cast<uint32_t>(getSALength(remote_end)));
    impl_->buf_.writeData(&remote_end, getSALength(remote_end));
    // Data length
    impl_->buf_.writeUint32(static_cast<uint32_t>(data_len));
    // Write the resulting header length at the beginning of the buffer
    impl_->buf_.writeUint16At(impl_->buf_.getLength() - sizeof(uint16_t), 0);

    const int cc = write(impl_->fd_, impl_->buf_.getData(),
                         impl_->buf_.getLength());
    assert(cc == impl_->buf_.getLength());

    const int cc_data = write(impl_->fd_, data, data_len);
    assert(cc_data == data_len);
}

SocketSession::SocketSession(int sock, int family, int type, int protocol,
                             const sockaddr* local_end,
                             const sockaddr* remote_end,
                             size_t data_len, const void* data) :
    sock_(sock), family_(family), type_(type), protocol_(protocol),
    local_end_(local_end), remote_end_(remote_end),
    data_len_(data_len), data_(data)
{
    if (local_end == NULL || remote_end == NULL) {
        isc_throw(BadValue, "sockaddr must be non NULL for SocketSession");
    }
    if (data_len == 0) {
        isc_throw(BadValue, "data_len must be non 0 for SocketSession");
    }
    if (data == NULL) {
        isc_throw(BadValue, "data must be non NULL for SocketSession");
    }
}

const size_t DEFAULT_HEADER_BUFLEN = sizeof(struct sockaddr_storage) * 2 +
    sizeof(uint32_t) * 6;

struct SocketSessionReceptor::ReceptorImpl {
    ReceptorImpl(int fd) : fd_(fd),
                           sa_local_(convertSockAddr(&ss_local_)),
                           sa_remote_(convertSockAddr(&ss_remote_)),
                           header_buf_(DEFAULT_HEADER_BUFLEN), data_buf_(512)
    {}

    const int fd_;
    struct sockaddr_storage ss_local_; // placeholder
    struct sockaddr* const sa_local_;
    struct sockaddr_storage ss_remote_; // placeholder
    struct sockaddr* const sa_remote_;

    vector<char> header_buf_;
    vector<char> data_buf_;
};

SocketSessionReceptor::SocketSessionReceptor(int fd) :
    impl_(new ReceptorImpl(fd))
{
}

SocketSessionReceptor::~SocketSessionReceptor() {
    delete impl_;
}

SocketSession
SocketSessionReceptor::pop() {
    const int passed_fd = recv_fd(impl_->fd_);
    // TODO: error check

    uint16_t header_len;
    const int cc = read(impl_->fd_, &header_len, sizeof(header_len));
    assert(cc == sizeof(header_len)); // XXX
    header_len = InputBuffer(&header_len, sizeof(header_len)).readUint16();
    impl_->header_buf_.clear();
    impl_->header_buf_.resize(header_len);
    read(impl_->fd_, &impl_->header_buf_[0], header_len);

    InputBuffer ibuffer(&impl_->header_buf_[0], header_len);
    const int family = static_cast<int>(ibuffer.readUint32());
    const int type = static_cast<int>(ibuffer.readUint32());
    const int protocol = static_cast<int>(ibuffer.readUint32());
    const socklen_t local_end_len = ibuffer.readUint32();
    assert(local_end_len <= sizeof(impl_->ss_local_)); // XXX
    ibuffer.readData(&impl_->ss_local_, local_end_len);
    const socklen_t remote_end_len = ibuffer.readUint32();
    assert(remote_end_len <= sizeof(impl_->ss_remote_)); // XXX
    ibuffer.readData(&impl_->ss_remote_, remote_end_len);
    const size_t data_len = ibuffer.readUint32();

    impl_->data_buf_.clear();
    impl_->data_buf_.resize(data_len);
    read(impl_->fd_, &impl_->data_buf_[0], data_len);

    return (SocketSession(passed_fd, family, type, protocol,
                          impl_->sa_local_, impl_->sa_remote_, data_len,
                          &impl_->data_buf_[0]));
}

}
}
}
