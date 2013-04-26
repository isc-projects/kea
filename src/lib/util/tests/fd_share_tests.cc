// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/io/fd.h>
#include <util/io/fd_share.h>

#include <util/unittests/check_valgrind.h>
#include <util/unittests/fork.h>

#include <gtest/gtest.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>

using namespace isc::util::io;
using namespace isc::util::unittests;

namespace {

// We test that we can transfer a pipe over other pipe
TEST(FDShare, transfer) {

    if (!isc::util::unittests::runningOnValgrind()) {
        // Get a pipe and fork
        int pipes[2];
        ASSERT_NE(-1, socketpair(AF_UNIX, SOCK_STREAM, 0, pipes));
        const pid_t sender(fork());
        ASSERT_NE(-1, sender);
        if (sender) { // We are in parent
            // Close the other side of pipe, we want only writible one
            EXPECT_NE(-1, close(pipes[0]));
            // Get a process to check data
            int fd(0);
            const pid_t checker(check_output(&fd, "data", 4));
            ASSERT_NE(-1, checker);
            // Now, send the file descriptor, close it and close the pipe
            EXPECT_NE(-1, send_fd(pipes[1], fd));
            EXPECT_NE(-1, close(pipes[1]));
            EXPECT_NE(-1, close(fd));
            // Check both subprocesses ended well
            EXPECT_TRUE(process_ok(sender));
            EXPECT_TRUE(process_ok(checker));
        } else { // We are in child. We do not use ASSERT here
            // Close the write end, we only read
            if (close(pipes[1])) {
                exit(1);
            }
            // Get the file descriptor
            const int fd(recv_fd(pipes[0]));
            if (fd == -1) {
                exit(1);
            }
            // This pipe is not needed
            if (close(pipes[0])) {
                exit(1);
            }
            // Send "data" through the received fd, close it and be done
            if (!write_data(fd, "data", 4) || close(fd) == -1) {
                exit(1);
            }
            exit(0);
        }
    }
}

}
