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

#include <util/unix_socket.h>
#include <unistd.h>

namespace isc {
namespace util {

UnixSocket::UnixSocket(const std::string& local_filename,
                       const std::string& remote_filename) :
        socketfd_(-1),
        remote_addr_len_(0),
        local_filename_(local_filename),
        remote_filename_(remote_filename),
        input_buffer_(RCVBUFSIZE)
{
    // Sanity check that the file names are not empty, nor equal.
    if (local_filename_.empty() || remote_filename_.empty()) {
        isc_throw(UnixSocketInvalidName, "unix socket file name must not"
                  " be empty");

    } else if (local_filename_ == remote_filename_) {
        isc_throw(UnixSocketInvalidName, "local and remote file names for the"
                  " unix socket are equal: '" << local_filename_ << "'");
    }
}

UnixSocket::~UnixSocket() {
    closeFd();
    unlink(local_filename_.c_str());
}

void
UnixSocket::open() {
    // Cant't open socket twice.
    if (isOpen()) {
        isc_throw(UnixSocketOpenError, "unix socket '" << socketfd_
                  << "' is already open");
    }

    // Create socket.
    socketfd_ = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (socketfd_ < 0) {
        isc_throw(UnixSocketOpenError, "Failed to create a socket");
    }

    // Convert the filename to the sockaddr structure.
    struct sockaddr_un local_addr;
    int local_addr_len = 0;
    filenameToSockAddr(local_filename_, local_addr, local_addr_len);
    filenameToSockAddr(remote_filename_, remote_addr_, remote_addr_len_);

    // Remove existing socket file. If this is not done, the bind call
    // may fail with "Address already in use" error.
    unlink(local_filename_.c_str());
    if (bind(socketfd_, reinterpret_cast<struct sockaddr *>(&local_addr),
             local_addr_len) < 0) {
        isc_throw(UnixSocketOpenError,
                  "failed to bind unix socket to '" << local_filename_
                  << "': " << strerror(errno));
    }
}

void
UnixSocket::closeFd() {
    // Close it only if open.
    if (socketfd_ >= 0)
        close(socketfd_);
    socketfd_ = -1;
}

int
UnixSocket::send(const isc::util::OutputBuffer &buf) {
    int len = sendto(socketfd_, buf.getData(), buf.getLength(), 0,
                     reinterpret_cast<struct sockaddr*>(&remote_addr_),
                     remote_addr_len_);
    if (len < 0) {
        isc_throw(UnixSocketSendError, "unix socket failed on sendto: "
                  << strerror(errno));
    }
    return (len);
}

int
UnixSocket::receive() {
    int len = recvfrom(socketfd_, &input_buffer_[0], input_buffer_.size(),
                       0, NULL, NULL);
    if (len < 0) {
        isc_throw(UnixSocketRecvError, "unix socket failed on recvfrom: "
                  << strerror(errno));
    }
    return (len);
}

void
UnixSocket::filenameToSockAddr(const std::string& filename,
                               struct sockaddr_un& sockaddr,
                               int& sockaddr_len) {
    if (filename.empty()) {
        isc_throw(UnixSocketInvalidName,
                  "empty file name specified for unix socket");
    }

    memset(&sockaddr, 0, sizeof(struct sockaddr_un));
    sockaddr.sun_family = AF_UNIX;
    strncpy(sockaddr.sun_path, filename.c_str(), filename.size());
    sockaddr_len = sizeof(sa_family_t) + filename.size();
}

}
}
