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

#include <cstring>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include "fd_share.h"

namespace isc {
namespace xfr {

namespace {
// Not all OSes support advanced CMSG macros: CMSG_LEN and CMSG_SPACE.
// In order to ensure as much portability as possible, we provide wrapper
// functions of these macros.
// Note that cmsg_space() could run slow on OSes that do not have
// CMSG_SPACE.
inline socklen_t
cmsg_space(socklen_t len) {
#ifdef CMSG_SPACE
    return (CMSG_SPACE(len));
#else
    struct msghdr msg;
    struct cmsghdr* cmsgp;
    // XXX: The buffer length is an ad hoc value, but should be enough
    // in a practical sense.
    char dummybuf[sizeof(struct cmsghdr) + 1024];

    memset(&msg, 0, sizeof(msg));
    msg.msg_control = dummybuf;
    msg.msg_controllen = sizeof(dummybuf);

    cmsgp = (struct cmsghdr*)dummybuf;
    cmsgp->cmsg_len = cmsg_len(len);

    cmsgp = CMSG_NXTHDR(&msg, cmsgp);
    if (cmsgp != NULL) {
        return ((char*)cmsgp - (char*)msg.msg_control);
    } else {
        return (0);
    }
#endif  // CMSG_SPACE
}
}

int
recv_fd(const int sock) {
    struct msghdr msghdr;
    struct iovec iov_dummy;
    unsigned char dummy_data;

    iov_dummy.iov_base = &dummy_data;
    iov_dummy.iov_len = sizeof(dummy_data);
    msghdr.msg_name = NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov = &iov_dummy;
    msghdr.msg_iovlen = 1;
    msghdr.msg_flags = 0;
    msghdr.msg_controllen = cmsg_space(sizeof(int));
    msghdr.msg_control = malloc(msghdr.msg_controllen);
    if (msghdr.msg_control == NULL) {
        return (-1);
    }

    if (recvmsg(sock, &msghdr, 0) < 0) {
        free(msghdr.msg_control);
        return (-1);
    }
    const struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msghdr);
    int fd = -1;
    if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_RIGHTS) {
        fd = *(const int *)CMSG_DATA(cmsg);
    }
    free(msghdr.msg_control);
    return (fd);
}

int
send_fd(const int sock, const int fd) {
    struct msghdr msghdr;
    struct iovec iov_dummy;
    unsigned char dummy_data = 0;

    iov_dummy.iov_base = &dummy_data;
    iov_dummy.iov_len = sizeof(dummy_data);
    msghdr.msg_name = NULL;
    msghdr.msg_namelen = 0;
    msghdr.msg_iov = &iov_dummy;
    msghdr.msg_iovlen = 1;
    msghdr.msg_flags = 0;
    msghdr.msg_controllen = cmsg_space(sizeof(int));
    msghdr.msg_control = malloc(msghdr.msg_controllen);
    if (msghdr.msg_control == NULL) {
        return (-1);
    }

    struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msghdr);
    cmsg->cmsg_len = msghdr.msg_controllen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int *)CMSG_DATA(cmsg) = fd;

    const int ret = sendmsg(sock, &msghdr, 0);
    free(msghdr.msg_control);
    return (ret >= 0 ? 0 : -1);
}

} // End for namespace xfr
} // End for namespace isc
