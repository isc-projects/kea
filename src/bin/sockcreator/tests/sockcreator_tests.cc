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

#include "../sockcreator.h"

#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>

using namespace isc::socket_creator;

namespace {

/*
 * Generic version of the creation of socket test. It just tries to
 * create the socket and checks the result is not negative (eg.
 * it is valid descriptor) and that it can listen.
 *
 * This is a macro so ASSERT_* does abort the TEST, not just the
 * function inside.
 */
#define TEST_ANY_CREATE(SOCK_TYPE, ADDR_TYPE, ADDR_FAMILY, ADDR_SET, \
    CHECK_SOCK) \
    do { \
        /*
         * This should create an address that binds on all interfaces
         * and lets the OS choose a free port.
         */ \
        struct ADDR_TYPE addr; \
        memset(&addr, 0, sizeof addr); \
        ADDR_SET(addr); \
        struct sockaddr *addr_ptr = static_cast<struct sockaddr *>( \
            static_cast<void *>(&addr)); \
        addr_ptr->sa_family = ADDR_FAMILY; \
        \
        int socket = get_sock(SOCK_TYPE, addr_ptr, sizeof addr); \
        /* Provide even nice error message. */ \
        ASSERT_GE(socket, 0) << "Couldn't create a socket of type " \
            #SOCK_TYPE " and family " #ADDR_FAMILY ", failed with " \
            << socket << " and errno " << errno; \
        CHECK_SOCK(ADDR_TYPE, socket); \
        EXPECT_EQ(0, close(socket)); \
    } while (0)

// Just helper macros
#define INADDR_SET(WHAT) do { WHAT.sin_addr.s_addr = INADDR_ANY; } while (0)
#define IN6ADDR_SET(WHAT) do { WHAT.sin6_addr = in6addr_any; } while (0)
// If the get_sock returned something useful, listen must work
#define TCP_CHECK(UNUSED, SOCKET) do { \
        EXPECT_EQ(0, listen(SOCKET, 1)); \
    } while (0)
// More complicated with UDP, so we send a packet to ourselfs and se if it
// arrives
#define UDP_CHECK(ADDR_TYPE, SOCKET) do { \
        struct ADDR_TYPE addr; \
        memset(&addr, 0, sizeof addr); \
        struct sockaddr *addr_ptr = static_cast<struct sockaddr *>( \
            static_cast<void *>(&addr)); \
        \
        socklen_t len = sizeof addr; \
        ASSERT_EQ(0, getsockname(SOCKET, addr_ptr, &len)); \
        ASSERT_EQ(5, sendto(SOCKET, "test", 5, 0, addr_ptr, sizeof addr)); \
        char buffer[5]; \
        ASSERT_EQ(5, recv(SOCKET, buffer, 5, 0)); \
        EXPECT_STREQ("test", buffer); \
    } while (0)

/*
 * Several tests to ensure we can create the sockets.
 */
TEST(get_sock, udp4_create) {
    TEST_ANY_CREATE(SOCK_DGRAM, sockaddr_in, AF_INET, INADDR_SET, UDP_CHECK);
}

TEST(get_sock, tcp4_create) {
    TEST_ANY_CREATE(SOCK_STREAM, sockaddr_in, AF_INET, INADDR_SET, TCP_CHECK);
}

TEST(get_sock, udp6_create) {
    TEST_ANY_CREATE(SOCK_DGRAM, sockaddr_in6, AF_INET6, IN6ADDR_SET,
        UDP_CHECK);
}

TEST(get_sock, tcp6_create) {
    TEST_ANY_CREATE(SOCK_STREAM, sockaddr_in6, AF_INET6, IN6ADDR_SET,
        TCP_CHECK);
}

/*
 * Try to ask the get_sock function some nonsense and test if it
 * is able to report error.
 */
TEST(get_sock, fail_with_nonsense) {
    struct sockaddr addr;
    memset(&addr, 0, sizeof addr);
    ASSERT_LT(get_sock(0, &addr, sizeof addr), 0);
}

/*
 * This creates a pipe, forks and feeds the pipe with given data.
 * Used to provide the input in non-blocking/asynchronous way.
 */
pid_t
provide_input(int *read_pipe, const char *input, const size_t length) {
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
check_output(int *write_pipe, const char *output, const size_t length) {
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
        char buffer[length + 1];
        // Try to read one byte more to see if the output ends here
        if (read_data(pipes[0], buffer, length + 1) != length)
            exit(1);
        // Normalize the return value - return 0 on equality, 1 on nonequality
        exit(!!memcmp(buffer, output, length));
    }
}

/*
 * Waits for pid to terminate and checks it terminates successfully (with 0).
 */
bool
process_ok(pid_t process) {
    int status;
    // Make sure it does terminate when the output is shorter than expected
    /*
     * FIXME: if the timeout is reached, this kill the whole test, not just
     * the waitpid call. Should have signal handler. This is no show-stopper,
     * but we might have another tests to run.
     */
    alarm(3);
    if (waitpid(process, &status, 0) == -1) {
        if (errno == EINTR)
            kill(process, SIGTERM);
        return false;
    }
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

/*
 * Helper functions to pass to run during testing.
 */
int
get_sock_dummy(const int type, struct sockaddr *addr, const socklen_t addr_len)
{
    int result(0);
    int port;
    /*
     * We encode the type and address family into the int and return it.
     * Lets ignore the port and address for now
     * First bit is 1 if it is known type. Second tells if TCP or UDP.
     * The familly is similar - third bit is known address family,
     * the fourth is the family.
     */
    switch (type) {
        case SOCK_STREAM:
            result += 1;
            break;
        case SOCK_DGRAM:
            result += 3;
            break;
    }
    switch (addr->sa_family) {
        case AF_INET:
            result += 4;
            port = static_cast<struct sockaddr_in *>(
                static_cast<void *>(addr))->sin_port;
            break;
        case AF_INET6:
            result += 12;
            port = static_cast<struct sockaddr_in6 *>(
                static_cast<void *>(addr))->sin6_port;
            break;
    }
    /*
     * The port should be 0xffff. If it's not, we change the result.
     * The port of 0xbbbb means bind should fail and 0xcccc means
     * socket should fail.
     */
    if (port != 0xffff) {
        errno = 0;
        if (port == 0xbbbb) {
            return -2;
        } else if (port == 0xcccc) {
            return -1;
        } else {
            result += 16;
        }
    }
    return result;
}

int
send_fd_dummy(const int destination, const int what)
{
    /*
     * Make sure it is 1 byte so we know the length. We do not use more during
     * the test anyway.
     */
    char fd_data(what);
    if (!write_data(destination, &fd_data, 1))
        return -1;
}

/*
 * Generic test that it works, with various inputs and outputs.
 * It uses different functions to create the socket and send it and pass
 * data to it and check it returns correct data back, to see if the run()
 * parses the commands correctly.
 */
void run_test(const char *input_data, const size_t input_size,
    const char *output_data, const size_t output_size,
    bool should_succeed = true)
{
    // Prepare the input feeder and output checker processes
    int input_fd, output_fd;
    pid_t input(provide_input(&input_fd, input_data, input_size)),
        output(check_output(&output_fd, output_data, output_size));
    ASSERT_NE(-1, input) << "Couldn't start input feeder";
    ASSERT_NE(-1, output) << "Couldn't start output checker";
    // Run the body
    int result(run(input_fd, output_fd, get_sock_dummy, send_fd_dummy));
    if (should_succeed) {
        EXPECT_EQ(0, result);
    } else {
        EXPECT_NE(0, result);
    }
    // Check the subprocesses say everything is OK too
    EXPECT_TRUE(process_ok(input));
    EXPECT_TRUE(process_ok(output));
}

/*
 * Check it terminates successfully when asked to.
 */
TEST(run, terminate) {
    run_test("T", 1, NULL, 0);
}

/*
 * Check it rejects incorrect input.
 */
TEST(run, bad_input) {
    run_test("XXX", 3, "FI", 2, false);
}

/*
 * Check it correctly parses queries to create sockets.
 */
TEST(run, sockets) {
    run_test(
        "SU4\xff\xff\0\0\0\0" // This has 9 bytes
        "ST4\xff\xff\0\0\0\0" // This has 9 bytes
        "ST6\xff\xff\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" // This has 21 bytes
        "SU6\xff\xff\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" // This has 21 bytes
        "T", 61,
        "S\x07S\x05S\x0dS\x0f", 8);
}

/*
 * Check if failures of get_socket are handled correctly.
 */
TEST(run, bad_sockets) {
    // We need to construct the answer, but it depends on int length.
    size_t int_len(sizeof(int));
    size_t result_len(4 + 2 * int_len);
    char result[result_len];
    // Both errno parts should be 0
    memset(result, 0, result_len);
    // Fill the 2 control parts
    strcpy(result, "EB");
    strcpy(result + 2 + int_len, "ES");
    // Run the test
    run_test(
        "SU4\xbb\xbb\0\0\0\0"
        "SU4\xcc\xcc\0\0\0\0"
        "T", 19,
        result, result_len);
}

}
