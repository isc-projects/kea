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

#include <errno.h>

namespace isc {
namespace dhcp_ddns {

const int WatchSocket::INVALID_SOCKET;
const uint32_t WatchSocket::MARKER;

WatchSocket::WatchSocket() 
    : source_(INVALID_SOCKET), sink_(INVALID_SOCKET), ready_flag_(false) {
    // Open the pipe.
    int fds[2];
    if (pipe(fds)) {
        const char* errstr = strerror(errno);
        isc_throw(WatchSocketError, "Cannot construct pipe: " << errstr);
    }

    source_ = fds[1];
    sink_ = fds[0];
}

WatchSocket::~WatchSocket() {
    // Close the pipe fds.  Technically a close can fail (hugely unlikely)
    // but there's no recovery for it either.  If one does fail we log it 
    // and go on. Plus no likes destructors that throw.
    if (source_ != INVALID_SOCKET) {
        if (close(source_)) {
            const char* errstr = strerror(errno);
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_WATCH_SOURCE_CLOSE_ERROR)
                      .arg(errstr);
        }
    }

    if (sink_ != INVALID_SOCKET) {
        if (close(sink_)) {
            const char* errstr = strerror(errno);
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_WATCH_SINK_CLOSE_ERROR)
                      .arg(errstr);
        }
    }
}

void 
WatchSocket::markReady() {
    if (!isReady()) {
        int nbytes = write (source_, &MARKER, sizeof(MARKER));
        if (nbytes != sizeof(MARKER)) {
            const char* errstr = strerror(errno);
            isc_throw(WatchSocketError, "WatchSocket markReady failed:"
                      << " bytes written: " << nbytes << " : " << errstr);
        }

        ready_flag_ = true;
    } 
}

bool 
WatchSocket::isReady() {
    return (ready_flag_);
}

void 
WatchSocket::clearReady() {
    if (isReady()) {
        uint32_t buf;
        int nbytes = read (sink_, &buf, sizeof(buf));
        if (nbytes != sizeof(MARKER)) { 
            const char* errstr = strerror(errno);
            isc_throw(WatchSocketError, "WatchSocket clearReady failed:"
                      << " bytes read: " << nbytes << " : " << errstr);
        }

        ready_flag_ = false;
    }
}

int 
WatchSocket::getSelectFd() {
    return (sink_);
}

} // namespace isc::dhcp_ddns
} // namespace isc
