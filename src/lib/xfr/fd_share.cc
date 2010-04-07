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

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include "fd_share.h"

namespace isc {
namespace xfr {

#define FD_BUFFER_CREATE(n) \
    struct { \
        struct cmsghdr h; \
        int fd[n]; \
    }

namespace {
int
send_fds_with_buffer(const int sock, const int* fds, const unsigned n_fds,
                     void* buffer)
{
    struct msghdr msghdr;
    char nothing = '!';
    struct iovec nothing_ptr;
    struct cmsghdr* cmsg;

    nothing_ptr.iov_base = &nothing;
    nothing_ptr.iov_len = 1;
    msghdr.msg_name = NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov = &nothing_ptr;
    msghdr.msg_iovlen = 1;
    msghdr.msg_flags = 0;
    msghdr.msg_control = buffer;
    msghdr.msg_controllen = sizeof(struct cmsghdr) + sizeof(int) * n_fds;
    cmsg = CMSG_FIRSTHDR(&msghdr);
    cmsg->cmsg_len = msghdr.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    for (int i = 0; i < n_fds; ++i) {
        ((int *)CMSG_DATA(cmsg))[i] = fds[i];
    }

    const int ret =  sendmsg(sock, &msghdr, 0);
    return (ret >= 0 ? 0 : -1);
}

int
recv_fds_with_buffer(const int sock, int* fds, const unsigned n_fds,
                     void* buffer)
{
    struct msghdr msghdr;
    char nothing;
    struct iovec nothing_ptr;
    struct cmsghdr *cmsg;
    int i;

    nothing_ptr.iov_base = &nothing;
    nothing_ptr.iov_len = 1;
    msghdr.msg_name = NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov = &nothing_ptr;
    msghdr.msg_iovlen = 1;
    msghdr.msg_flags = 0;
    msghdr.msg_control = buffer;
    msghdr.msg_controllen = sizeof(struct cmsghdr) + sizeof(int) * n_fds;
    cmsg = CMSG_FIRSTHDR(&msghdr);
    cmsg->cmsg_len = msghdr.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    for (i = 0; i < n_fds; i++) {
        ((int *)CMSG_DATA(cmsg))[i] = -1;
    }

    if (recvmsg(sock, &msghdr, 0) < 0) {
        return (-1);
    }

    for (i = 0; i < n_fds; i++) {
        fds[i] = ((int *)CMSG_DATA(cmsg))[i];
    }

    return ((msghdr.msg_controllen - sizeof(struct cmsghdr)) / sizeof(int));
}
}

int
recv_fd(const int sock) {
    FD_BUFFER_CREATE(1) buffer;
    int fd = 0;
    if (recv_fds_with_buffer(sock, &fd, 1, &buffer) == -1) {
        return -1;
    }

    return fd;
}

int
send_fd(const int sock, const int fd) {
    FD_BUFFER_CREATE(1) buffer;
    int ret = send_fds_with_buffer(sock, &fd, 1, &buffer);
    return ((ret < 0) ? -1 : ret);
}

} // End for namespace xfr
} // End for namespace isc
