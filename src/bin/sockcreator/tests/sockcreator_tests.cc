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
#include <netinet/in.h>
#include <cstring>
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
    } while(0)

// Just helper macros
#define INADDR_SET(WHAT) do { WHAT.sin_addr.s_addr = INADDR_ANY; } while(0)
#define IN6ADDR_SET(WHAT) do { WHAT.sin6_addr = in6addr_any; } while(0)
// If the get_sock returned something useful, listen must work
#define TCP_CHECK(UNUSED, SOCKET) do { \
        EXPECT_EQ(0, listen(SOCKET, 1)); \
    } while(0)
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
    } while(0)

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
    ASSERT_LT(get_sock(0, NULL, 0), 0);
}

}
