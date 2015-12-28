// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FD_SHARE_H_
#define FD_SHARE_H_

/**
 * \file fd_share.h
 * \short Support to transfer file descriptors between processes.
 * \todo This interface is very C-ish. Should we have some kind of exceptions?
 */

namespace isc {
namespace util {
namespace io {

const int FD_SYSTEM_ERROR = -2;
const int FD_OTHER_ERROR = -1;

/**
 * \short Receives a file descriptor.
 * This receives a file descriptor sent over an unix domain socket. This
 * is the counterpart of send_fd().
 *
 * \return FD_SYSTEM_ERROR when there's an error at the operating system
 * level (such as a system call failure).  The global 'errno' variable
 * indicates the specific error.  FD_OTHER_ERROR when there's a different
 * error.
 *
 * \param sock The unix domain socket to read from. Tested and it does
 *     not work with a pipe.
 */
int recv_fd(const int sock);

/**
 * \short Sends a file descriptor.
 * This sends a file descriptor over an unix domain socket. This is the
 * counterpart of recv_fd().
 *
 * \return FD_SYSTEM_ERROR when there's an error at the operating system
 * level (such as a system call failure).  The global 'errno' variable
 * indicates the specific error.
 * \param sock The unix domain socket to send to. Tested and it does not
 *     work with a pipe.
 * \param fd The file descriptor to send. It should work with any valid
 *     file descriptor.
 */
int send_fd(const int sock, const int fd);

} // End for namespace io
} // End for namespace util
} // End for namespace isc

#endif

// Local Variables:
// mode: c++
// End:
