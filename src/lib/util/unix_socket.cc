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

namespace isc {
namespace util {

UnixSocket::UnixSocket(const std::string& local_filename, const std::string& remote_filename) :
        socketfd_(-1),
        remote_addr_len_(0),
        local_filename_(local_filename),
        remote_filename_(remote_filename)
{
}

UnixSocket::~UnixSocket() {
    closeIPC();
}

int
UnixSocket::open() {
    //create socket
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0) {
        isc_throw(UnixSocketOpenError, "Failed to create a socket");
    }
    socketfd_ = fd;

    bindSocket();
    setRemoteFilename();
    	
    return socketfd_;
}

void
UnixSocket::closeIPC() {
    if(socketfd_ >= 0)
        close(socketfd_);
    socketfd_ = -1;
}

int
UnixSocket::send(const isc::util::OutputBuffer &buf) {
    if (remote_addr_len_ == 0) {
        isc_throw(UnixSocketSendError, "Remote address unset");
    }
    int count = sendto(socketfd_, buf.getData(), buf.getLength(), 0,
                       (struct sockaddr*)&remote_addr_, remote_addr_len_);
    if (count < 0) {
        isc_throw(UnixSocketSendError, "UnixSocket failed on sendto: "
                  << strerror(errno));
    }
    return count;
}

isc::util::InputBuffer
UnixSocket::recv() {
    uint8_t buf[RCVBUFSIZE];
    int len = recvfrom(socketfd_, buf, RCVBUFSIZE, 0, NULL, NULL);
    if (len < 0) {
        isc_throw(UnixSocketRecvError, "UnixSocket failed on recvfrom: "
                  << strerror(errno));
    } 
    isc::util::InputBuffer ibuf(buf, len);
    return ibuf;
}

void
UnixSocket::setRemoteFilename() {
    memset(&remote_addr_, 0, sizeof(struct sockaddr_un));
    remote_addr_.sun_family = AF_UNIX;
    strcpy(&remote_addr_.sun_path[1], remote_filename_.c_str());
    remote_addr_len_ = sizeof(sa_family_t) + remote_filename_.size() + 1;
}

void
UnixSocket::bindSocket() {
    struct sockaddr_un local_addr_;
    int local_addr_len_;
            
    //init address
    memset(&local_addr_, 0, sizeof(struct sockaddr_un));
    local_addr_.sun_family = AF_UNIX;
    strcpy(&local_addr_.sun_path[1], local_filename_.c_str());
    local_addr_len_ = sizeof(sa_family_t) + local_filename_.size() + 1;

    //bind to local_address
    if (bind(socketfd_, (struct sockaddr *)&local_addr_, local_addr_len_) < 0) {
        isc_throw(UnixSocketOpenError, "failed to bind to local address: " + local_filename_);
    }
}


}
}
