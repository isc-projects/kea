// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file watch_socket.cc

//#include <dhcp_ddns/dhcp_ddns_log.h>
#include <util/watch_socket.h>

#include <fcntl.h>
#include <errno.h>
#include <sstream>
#include <string.h>
#include <sys/select.h>

namespace isc {
namespace util {


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

    if (fcntl(source_, F_SETFD, FD_CLOEXEC)) {
        const char* errstr = strerror(errno);
        isc_throw(WatchSocketError, "Cannot set source to close-on-exec: "
                                     << errstr);
    }

    if (fcntl(sink_, F_SETFD, FD_CLOEXEC)) {
        const char* errstr = strerror(errno);
        isc_throw(WatchSocketError, "Cannot set sink to close-on-exec: "
                                     << errstr);
    }

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

bool
WatchSocket::closeSocket(std::string& error_string) {
    std::ostringstream s;
    // Close the pipe fds.  Technically a close can fail (hugely unlikely)
    // but there's no recovery for it either.  If one does fail we log it
    // and go on. Plus this is called by the destructor and no one likes
    // destructors that throw.
    if (source_ != SOCKET_NOT_VALID) {
        if (close(source_)) {
            // An error occured.
            s << "Could not close source: " << strerror(errno);
        }

        source_ = SOCKET_NOT_VALID;
    }

    if (sink_ != SOCKET_NOT_VALID) {
        if (close(sink_)) {
            // An error occured.
            if (error_string.empty()) {
                s << "could not close sink: " << strerror(errno);
            }
        }

        sink_ = SOCKET_NOT_VALID;
    }

    error_string = s.str();

    // If any errors have been reported, return false.
    return (error_string.empty() ? true : false);
}

void
WatchSocket::closeSocket() {
    std::string error_string;
    closeSocket(error_string);
}

int
WatchSocket::getSelectFd() {
    return (sink_);
}

} // namespace isc::util
} // namespace isc
