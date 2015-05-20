// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

/// @file watch_socket.cc

#include <dhcp_ddns/dhcp_ddns_log.h>
#include <dhcp_ddns/watch_socket.h>

#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>

namespace isc {
namespace dhcp_ddns {


const int WatchSocket::SOCKET_NOT_VALID;
const uint32_t WatchSocket::MARKER;

WatchSocket::WatchSocket()
    : source_(SOCKET_NOT_VALID), sink_(SOCKET_NOT_VALID) {
    // Open the pipe.
    int fds[2];
    if (pipe(fds)) {
        const char* errstr = strerror(errno);
        isc_throw(WatchSocketError, "Cannot construct pipe: " << errstr);
    }

    source_ = fds[1];
    sink_ = fds[0];

    if (fcntl(sink_, F_SETFL, O_NONBLOCK)) {
        const char* errstr = strerror(errno);
        isc_throw(WatchSocketError, "Cannot set sink to non-blocking: "
                                     << errstr);
    }
}

WatchSocket::~WatchSocket() {
    closeSocket();
}

void
WatchSocket::markReady() {
    // Make sure it hasn't been orphaned!  Otherwise we may get SIGPIPE.  We
    // use fcntl to check as select() on some systems may show it as ready to
    // read.
    if (fcntl(sink_, F_GETFL) < 0) {
        closeSocket();
        isc_throw(WatchSocketError, "WatchSocket markReady failed:"
                  " select_fd was closed!");
    }

    if (!isReady()) {
        int nbytes = write (source_, &MARKER, sizeof(MARKER));
        if (nbytes != sizeof(MARKER)) {
            // If there's an error get the error message than close
            // the pipe.  This should ensure any further use of the socket
            // or testing the fd with select_fd will fail.
            const char* errstr = strerror(errno);
            closeSocket();
            isc_throw(WatchSocketError, "WatchSocket markReady failed:"
                      << " bytes written: " << nbytes << " : " << errstr);
        }
    }
}

bool
WatchSocket::isReady() {
    // Report it as not ready rather than error here.
    if (sink_ == SOCKET_NOT_VALID) {
        return (false);
    }

    fd_set read_fds;
    FD_ZERO(&read_fds);

    // Add select_fd socket to listening set
    FD_SET(sink_,  &read_fds);

    // Set zero timeout (non-blocking).
    struct timeval select_timeout;
    select_timeout.tv_sec = 0;
    select_timeout.tv_usec = 0;

    // Return true only if read ready, treat error same as not ready.
    return (select(sink_ + 1, &read_fds, NULL, NULL, &select_timeout) > 0);
}

void
WatchSocket::clearReady() {
    if (isReady()) {
        uint32_t buf = 0;
        int nbytes = read (sink_, &buf, sizeof(buf));
        if ((nbytes != sizeof(MARKER) || (buf != MARKER))) {
            // If there's an error get the error message than close
            // the pipe.  This should ensure any further use of the socket
            // or testing the fd with select_fd will fail.
            const char* errstr = strerror(errno);
            closeSocket();
            isc_throw(WatchSocketError, "WatchSocket clearReady failed:"
                      << " bytes read: " << nbytes << " : "
                      << " value read: " << buf << " error :" <<errstr);
        }
    }
}

void
WatchSocket::closeSocket() {
    // Close the pipe fds.  Technically a close can fail (hugely unlikely)
    // but there's no recovery for it either.  If one does fail we log it
    // and go on. Plus this is called by the destructor and no one likes
    // destructors that throw.
    if (source_ != SOCKET_NOT_VALID) {
        if (close(source_)) {
            const char* errstr = strerror(errno);
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_WATCH_SOURCE_CLOSE_ERROR)
                      .arg(errstr);
        }

        source_ = SOCKET_NOT_VALID;
    }

    if (sink_ != SOCKET_NOT_VALID) {
        if (close(sink_)) {
            const char* errstr = strerror(errno);
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_WATCH_SINK_CLOSE_ERROR)
                      .arg(errstr);
        }

        sink_ = SOCKET_NOT_VALID;
    }
}

int
WatchSocket::getSelectFd() {
    return (sink_);
}

} // namespace isc::dhcp_ddns
} // namespace isc
