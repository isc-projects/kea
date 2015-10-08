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

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>

#include <netinet/in.h>

#include <fcntl.h>
#include <stdint.h>

#include <cerrno>
#include <csignal>
#include <cstddef>
#include <cstring>
#include <cassert>

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <util/io/fd_share.h>
#include <util/io/socketsession.h>
#include <util/io/sockaddr_util.h>

using namespace std;

namespace isc {
namespace util {
namespace io {

using namespace internal;

// The expected max size of the session header: 2-byte header length,
// 6 32-bit fields, and 2 sockaddr structure. (see the SocketSessionUtility
// overview description in the header file).  sizeof sockaddr_storage
// should be the possible max of any sockaddr structure
const size_t DEFAULT_HEADER_BUFLEN = sizeof(uint16_t) + sizeof(uint32_t) * 6 +
    sizeof(struct sockaddr_storage) * 2;

// The allowable maximum size of data passed with the socket FD.  For now
// we use a fixed value of 65535, the largest possible size of valid DNS
// messages.  We may enlarge it or make it configurable as we see the need
// for more flexibility.
const int MAX_DATASIZE = 65535;

// The initial buffer size for receiving socket session data in the receiver.
// This value is the maximum message size of DNS messages carried over UDP
// (without EDNS).  In our expected usage (at the moment) this should be
// sufficiently large (the expected data is AXFR/IXFR query or an UPDATE
// requests.  The former should be generally quite small.  While the latter
// could be large, it would often be small enough for a single UDP message).
// If it turns out that there are many exceptions, we may want to extend
// the class so that this value can be customized.  Note that the buffer
// will be automatically extended for longer data and this is only about
// efficiency.
const size_t INITIAL_BUFSIZE = 512;

// The (default) socket buffer size for the forwarder and receiver.  This is
// chosen to be sufficiently large to store two full-size DNS messages.  We
// may want to customize this value in future.
const int SOCKSESSION_BUFSIZE = (DEFAULT_HEADER_BUFLEN + MAX_DATASIZE) * 2;

struct SocketSessionForwarder::ForwarderImpl {
    ForwarderImpl() : fd_(-1), buf_(DEFAULT_HEADER_BUFLEN) {}
    struct sockaddr_un sock_un_;
    socklen_t sock_un_len_;
    int fd_;
    OutputBuffer buf_;
};

SocketSessionForwarder::SocketSessionForwarder(const std::string& unix_file) :
    impl_(NULL)
{
    // We need to filter SIGPIPE for subsequent push().  See the class
    // description.
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        isc_throw(Unexpected, "Failed to filter SIGPIPE: " << strerror(errno));
    }

    ForwarderImpl impl;
    if (sizeof(impl.sock_un_.sun_path) - 1 < unix_file.length()) {
        isc_throw(SocketSessionError,
                  "File name for a UNIX domain socket is too long: " <<
                  unix_file);
    }
    impl.sock_un_.sun_family = AF_UNIX;
    // the copy should be safe due to the above check, but we'd be rather
    // paranoid about making it 100% sure even if the check has a bug (with
    // triggering the assertion in the worse case)
    strncpy(impl.sock_un_.sun_path, unix_file.c_str(),
            sizeof(impl.sock_un_.sun_path));
    assert(impl.sock_un_.sun_path[sizeof(impl.sock_un_.sun_path) - 1] == '\0');
    impl.sock_un_len_ = offsetof(struct sockaddr_un, sun_path) +
        unix_file.length();
#ifdef HAVE_SA_LEN
    impl.sock_un_.sun_len = impl.sock_un_len_;
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
SocketSessionForwarder::connectToReceiver() {
    if (impl_->fd_ != -1) {
        isc_throw(BadValue, "Duplicate connect to UNIX domain "
                  "endpoint " << impl_->sock_un_.sun_path);
    }

    impl_->fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (impl_->fd_ == -1) {
        isc_throw(SocketSessionError, "Failed to create a UNIX domain socket: "
                  << strerror(errno));
    }
    // Make the socket non blocking
    int fcntl_flags = fcntl(impl_->fd_, F_GETFL, 0);
    if (fcntl_flags != -1) {
        fcntl_flags |= O_NONBLOCK;
        fcntl_flags = fcntl(impl_->fd_, F_SETFL, fcntl_flags);
    }
    if (fcntl_flags == -1) {
        close();   // note: this is the internal method, not ::close()
        isc_throw(SocketSessionError,
                  "Failed to make UNIX domain socket non blocking: " <<
                  strerror(errno));
    }
    // Ensure the socket send buffer is large enough.  If we can't get the
    // current size, simply set the sufficient size.
    int sndbuf_size;
    socklen_t sndbuf_size_len = sizeof(sndbuf_size);
    if (getsockopt(impl_->fd_, SOL_SOCKET, SO_SNDBUF, &sndbuf_size,
                   &sndbuf_size_len) == -1 ||
        sndbuf_size < SOCKSESSION_BUFSIZE) {
        if (setsockopt(impl_->fd_, SOL_SOCKET, SO_SNDBUF, &SOCKSESSION_BUFSIZE,
                       sizeof(SOCKSESSION_BUFSIZE)) == -1) {
            close();
            isc_throw(SocketSessionError,
                      "Failed to set send buffer size to " <<
                          SOCKSESSION_BUFSIZE);
        }
    }
    if (connect(impl_->fd_, convertSockAddr(&impl_->sock_un_),
                impl_->sock_un_len_) == -1) {
        close();
        isc_throw(SocketSessionError, "Failed to connect to UNIX domain "
                  "endpoint " << impl_->sock_un_.sun_path << ": " <<
                  strerror(errno));
    }
}

void
SocketSessionForwarder::close() {
    if (impl_->fd_ == -1) {
        isc_throw(BadValue, "Attempt of close before connect");
    }
    ::close(impl_->fd_);
    impl_->fd_ = -1;
}

void
SocketSessionForwarder::push(int sock, int family, int type, int protocol,
                             const struct sockaddr& local_end,
                             const struct sockaddr& remote_end,
                             const void* data, size_t data_len)
{
    if (impl_->fd_ == -1) {
        isc_throw(BadValue, "Attempt of push before connect");
    }
    if ((local_end.sa_family != AF_INET && local_end.sa_family != AF_INET6) ||
        (remote_end.sa_family != AF_INET && remote_end.sa_family != AF_INET6))
    {
        isc_throw(BadValue, "Invalid address family: must be "
                  "AF_INET or AF_INET6; " <<
                  static_cast<int>(local_end.sa_family) << ", " <<
                  static_cast<int>(remote_end.sa_family) << " given");
    }
    if (family != local_end.sa_family || family != remote_end.sa_family) {
        isc_throw(BadValue, "Inconsistent address family: must be "
                  << static_cast<int>(family) << "; "
                  << static_cast<int>(local_end.sa_family) << ", "
                  << static_cast<int>(remote_end.sa_family) << " given");
    }
    if (data_len == 0 || data == NULL) {
        isc_throw(BadValue, "Data for a socket session must not be empty");
    }
    if (data_len > MAX_DATASIZE) {
        isc_throw(BadValue, "Invalid socket session data size: " <<
                  data_len << ", must not exceed " << MAX_DATASIZE);
    }

    if (send_fd(impl_->fd_, sock) != 0) {
        isc_throw(SocketSessionError, "FD passing failed: " <<
                  strerror(errno));
    }

    impl_->buf_.clear();
    // Leave the space for the header length
    impl_->buf_.skip(sizeof(uint16_t));
    // Socket properties: family, type, protocol
    impl_->buf_.writeUint32(static_cast<uint32_t>(family));
    impl_->buf_.writeUint32(static_cast<uint32_t>(type));
    impl_->buf_.writeUint32(static_cast<uint32_t>(protocol));
    // Local endpoint
    impl_->buf_.writeUint32(static_cast<uint32_t>(getSALength(local_end)));
    impl_->buf_.writeData(&local_end, getSALength(local_end));
    // Remote endpoint
    impl_->buf_.writeUint32(static_cast<uint32_t>(getSALength(remote_end)));
    impl_->buf_.writeData(&remote_end, getSALength(remote_end));
    // Data length.  Must be fit uint32 due to the range check above.
    const uint32_t data_len32 = static_cast<uint32_t>(data_len);
    assert(data_len == data_len32); // shouldn't cause overflow.
    impl_->buf_.writeUint32(data_len32);
    // Write the resulting header length at the beginning of the buffer
    impl_->buf_.writeUint16At(impl_->buf_.getLength() - sizeof(uint16_t), 0);

    const struct iovec iov[2] = {
        { const_cast<void*>(impl_->buf_.getData()), impl_->buf_.getLength() },
        { const_cast<void*>(data), data_len }
    };
    const int cc = writev(impl_->fd_, iov, 2);
    if (cc != impl_->buf_.getLength() + data_len) {
        if (cc < 0) {
            isc_throw(SocketSessionError,
                      "Write failed in forwarding a socket session: " <<
                      strerror(errno));
        }
        isc_throw(SocketSessionError,
                  "Incomplete write in forwarding a socket session: " << cc <<
                  "/" << (impl_->buf_.getLength() + data_len));
    }
}

SocketSession::SocketSession(int sock, int family, int type, int protocol,
                             const sockaddr* local_end,
                             const sockaddr* remote_end,
                             const void* data, size_t data_len) :
    sock_(sock), family_(family), type_(type), protocol_(protocol),
    local_end_(local_end), remote_end_(remote_end),
    data_(data), data_len_(data_len)
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

struct SocketSessionReceiver::ReceiverImpl {
    ReceiverImpl(int fd) : fd_(fd),
                           sa_local_(convertSockAddr(&ss_local_)),
                           sa_remote_(convertSockAddr(&ss_remote_)),
                           header_buf_(DEFAULT_HEADER_BUFLEN),
                           data_buf_(INITIAL_BUFSIZE)
    {
        if (setsockopt(fd_, SOL_SOCKET, SO_RCVBUF, &SOCKSESSION_BUFSIZE,
                       sizeof(SOCKSESSION_BUFSIZE)) == -1) {
            isc_throw(SocketSessionError,
                      "Failed to set receive buffer size to " <<
                          SOCKSESSION_BUFSIZE);
        }
    }

    const int fd_;
    struct sockaddr_storage ss_local_; // placeholder for local endpoint
    struct sockaddr* const sa_local_;
    struct sockaddr_storage ss_remote_; // placeholder for remote endpoint
    struct sockaddr* const sa_remote_;

    // placeholder for session header and data
    vector<uint8_t> header_buf_;
    vector<uint8_t> data_buf_;
};

SocketSessionReceiver::SocketSessionReceiver(int fd) :
    impl_(new ReceiverImpl(fd))
{
}

SocketSessionReceiver::~SocketSessionReceiver() {
    delete impl_;
}

namespace {
// A shortcut to throw common exception on failure of recv(2)
void
readFail(int actual_len, int expected_len) {
    if (expected_len < 0) {
        isc_throw(SocketSessionError, "Failed to receive data from "
                  "SocketSessionForwarder: " << strerror(errno));
    }
    isc_throw(SocketSessionError, "Incomplete data from "
              "SocketSessionForwarder: " << actual_len << "/" <<
              expected_len);
}

// A helper container for a (socket) file descriptor used in
// SocketSessionReceiver::pop that ensures the socket is closed unless it
// can be safely passed to the caller via release().
struct ScopedSocket : boost::noncopyable {
    ScopedSocket(int fd) : fd_(fd) {}
    ~ScopedSocket() {
        if (fd_ >= 0) {
            close(fd_);
        }
    }
    int release() {
        const int fd = fd_;
        fd_ = -1;
        return (fd);
    }
    int fd_;
};
}

SocketSession
SocketSessionReceiver::pop() {
    ScopedSocket passed_sock(recv_fd(impl_->fd_));
    if (passed_sock.fd_ == FD_SYSTEM_ERROR) {
        isc_throw(SocketSessionError, "Receiving a forwarded FD failed: " <<
                  strerror(errno));
    } else if (passed_sock.fd_ < 0) {
        isc_throw(SocketSessionError, "No FD forwarded");
    }

    uint16_t header_len;
    const int cc_hlen = recv(impl_->fd_, &header_len, sizeof(header_len),
                        MSG_WAITALL);
    if (cc_hlen < sizeof(header_len)) {
        readFail(cc_hlen, sizeof(header_len));
    }
    header_len = InputBuffer(&header_len, sizeof(header_len)).readUint16();
    if (header_len > DEFAULT_HEADER_BUFLEN) {
        isc_throw(SocketSessionError, "Too large header length: " <<
                  header_len);
    }
    impl_->header_buf_.clear();
    impl_->header_buf_.resize(header_len);
    const int cc_hdr = recv(impl_->fd_, &impl_->header_buf_[0], header_len,
                            MSG_WAITALL);
    if (cc_hdr < header_len) {
        readFail(cc_hdr, header_len);
    }

    InputBuffer ibuffer(&impl_->header_buf_[0], header_len);
    try {
        const int family = static_cast<int>(ibuffer.readUint32());
        if (family != AF_INET && family != AF_INET6) {
            isc_throw(SocketSessionError,
                      "Unsupported address family is passed: " << family);
        }
        const int type = static_cast<int>(ibuffer.readUint32());
        const int protocol = static_cast<int>(ibuffer.readUint32());
        const socklen_t local_end_len = ibuffer.readUint32();
        const socklen_t endpoint_minlen = (family == AF_INET) ?
            sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
        if (local_end_len < endpoint_minlen ||
            local_end_len > sizeof(impl_->ss_local_)) {
            isc_throw(SocketSessionError, "Invalid local SA length: " <<
                      local_end_len);
        }
        ibuffer.readData(&impl_->ss_local_, local_end_len);
        const socklen_t remote_end_len = ibuffer.readUint32();
        if (remote_end_len < endpoint_minlen ||
            remote_end_len > sizeof(impl_->ss_remote_)) {
            isc_throw(SocketSessionError, "Invalid remote SA length: " <<
                      remote_end_len);
        }
        ibuffer.readData(&impl_->ss_remote_, remote_end_len);
        if (family != impl_->sa_local_->sa_family ||
            family != impl_->sa_remote_->sa_family) {
            isc_throw(SocketSessionError, "SA family inconsistent: " <<
                      static_cast<int>(impl_->sa_local_->sa_family) << ", " <<
                      static_cast<int>(impl_->sa_remote_->sa_family) <<
                      " given, must be " << family);
        }
        const size_t data_len = ibuffer.readUint32();
        if (data_len == 0 || data_len > MAX_DATASIZE) {
            isc_throw(SocketSessionError,
                      "Invalid socket session data size: " << data_len <<
                      ", must be > 0 and <= " << MAX_DATASIZE);
        }

        impl_->data_buf_.clear();
        impl_->data_buf_.resize(data_len);
        const int cc_data = recv(impl_->fd_, &impl_->data_buf_[0], data_len,
                                 MSG_WAITALL);
        if (cc_data < data_len) {
            readFail(cc_data, data_len);
        }

        return (SocketSession(passed_sock.release(), family, type, protocol,
                              impl_->sa_local_, impl_->sa_remote_,
                              &impl_->data_buf_[0], data_len));
    } catch (const InvalidBufferPosition& ex) {
        // We catch the case where the given header is too short and convert
        // the exception to SocketSessionError.
        isc_throw(SocketSessionError, "bogus socket session header: " <<
                  ex.what());
    }
}

}
}
}
