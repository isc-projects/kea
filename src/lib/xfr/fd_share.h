#ifndef FD_SHARE_H_
#define FD_SHARE_H_

#include <stdlib.h>

namespace isc {
namespace xfr {

// Receive socket descriptor on unix domain socket 'sock'.
// Returned value is the socket descriptor received.
// Errors are indicated by a return value of -1.
int
recv_fd(int sock);

// Send socket descriptor "fd" to server over unix domain socket 'sock', 
// the connection from socket 'sock' to unix domain server should be established first.
// Errors are indicated by a return value of -1.
int
send_fd(int sock, int fd);

} // End for namespace xfr
} // End for namespace isc

#endif
