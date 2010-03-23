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

int
send_fds_with_buffer(int sock, const int *fds, unsigned n_fds, void *buffer)
{
    struct msghdr msghdr;
    char nothing = '!';
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
    for(i = 0; i < n_fds; i++)
        ((int *)CMSG_DATA(cmsg))[i] = fds[i];
    
    int ret =  sendmsg(sock, &msghdr, 0);
    return (ret >= 0 ? 0 : -1);
}

int
recv_fds_with_buffer(int sock, int *fds, unsigned n_fds, void *buffer)
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
    for(i = 0; i < n_fds; i++)
        ((int *)CMSG_DATA(cmsg))[i] = -1;
    
    if(recvmsg(sock, &msghdr, 0) < 0)
        return (-1);

    for(i = 0; i < n_fds; i++) {
        fds[i] = ((int *)CMSG_DATA(cmsg))[i];
    }

    n_fds = (msghdr.msg_controllen - sizeof(struct cmsghdr)) / sizeof(int);
    return n_fds;
}

int
recv_fd(int sock)
{
    FD_BUFFER_CREATE(1) buffer;
    int fd = 0;
    int ret = recv_fds_with_buffer(sock, &fd, 1, &buffer);
    if (ret == -1)
        return -1;

    return fd;
}

int
send_fd(int sock, int fd)
{
    FD_BUFFER_CREATE(1) buffer;
    int ret = send_fds_with_buffer(sock, &fd, 1, &buffer);
    return ((ret < 0) ? -1 : ret);
}

} // End for namespace xfr
} // End for namespace isc
