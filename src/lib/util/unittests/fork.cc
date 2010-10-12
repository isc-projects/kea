// Copyright (C) 2010  CZ NIC
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

#include "fork.h"

#include <util/io/fd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <cstdio>

using namespace isc::util::io;

namespace {

// Just a NOP function to ignore a signal but let it interrupt function.
void no_handler(int) { }

};

namespace isc {
namespace util {
namespace unittests {

bool
process_ok(pid_t process) {
    // Create a timeout
    struct sigaction ignored, original;
    memset(&ignored, 0, sizeof ignored);
    ignored.sa_handler = no_handler;
    if (sigaction(SIGALRM, &ignored, &original)) {
        return false;
    }
    alarm(3);
    int status;
    int result(waitpid(process, &status, 0) == -1);
    // Cancel the alarm and return the original handler
    alarm(0);
    if (sigaction(SIGALRM, &original, NULL)) {
        return false;
    }
    // Check what we found out
    if (result) {
        if (errno == EINTR)
            kill(process, SIGTERM);
        return false;
    }
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

/*
 * This creates a pipe, forks and feeds the pipe with given data.
 * Used to provide the input in non-blocking/asynchronous way.
 */
pid_t
provide_input(int *read_pipe, const void *input, const size_t length)
{
    int pipes[2];
    if (pipe(pipes)) {
        return -1;
    }
    *read_pipe = pipes[0];
    pid_t pid(fork());
    if (pid) { // We are in the parent
        return pid;
    } else { // This is in the child, just puth the data there
        close(pipes[0]);
        if (!write_data(pipes[1], input, length)) {
            exit(1);
        } else {
            close(pipes[1]);
            exit(0);
        }
    }
}

/*
 * This creates a pipe, forks and reads the pipe and compares it
 * with given data. Used to check output of run in asynchronous way.
 */
pid_t
check_output(int *write_pipe, const void *output, const size_t length)
{
    int pipes[2];
    if (pipe(pipes)) {
        return -1;
    }
    *write_pipe = pipes[1];
    pid_t pid(fork());
    if (pid) { // We are in parent
        return pid;
    } else {
        close(pipes[1]);
        unsigned char buffer[length + 1];
        // Try to read one byte more to see if the output ends here
        size_t got_length(read_data(pipes[0], buffer, length + 1));
        bool ok(true);
        if (got_length != length) {
            fprintf(stderr, "Different length (expected %u, got %u)\n",
                static_cast<unsigned>(length),
                static_cast<unsigned>(got_length));
            ok = false;
        }
        if(!ok || memcmp(buffer, output, length)) {
            const unsigned char *output_c(static_cast<const unsigned char *>(
                output));
            // If the differ, print what we have
            for(size_t i(0); i != got_length; ++ i) {
                fprintf(stderr, "%02hhx", buffer[i]);
            }
            fprintf(stderr, "\n");
            for(size_t i(0); i != length; ++ i) {
                fprintf(stderr, "%02hhx", output_c[i]);
            }
            fprintf(stderr, "\n");
            exit(1);
        } else {
            exit(0);
        }
    }
}

}
}
}
