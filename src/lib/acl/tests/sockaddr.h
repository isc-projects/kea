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

#ifndef ACL_TEST_SOCKADDR_H
#define ACL_TEST_SOCKADDR_H 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include <exceptions/exceptions.h>

namespace isc {
namespace acl {
namespace tests {

// This is a helper function that returns a sockaddr for the given textual
// IP address.  Note that "inline" is crucial because this function is defined
// in a header file included in multiple .cc files.  Without inline it would
// produce an external linkage and cause troubles at link time.
//
// Note that this function uses a static storage for the return value.
// So if it's called more than once in a singe context (e.g., in the same
// EXPECT_xx()), it's unlikely to work as expected.
inline const struct sockaddr&
getSockAddr(const char* const addr) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICHOST;

    if (getaddrinfo(addr, NULL, &hints, &res) == 0) {
        static struct sockaddr_storage ss;
        void* ss_ptr = &ss;
        memcpy(ss_ptr, res->ai_addr, res->ai_addrlen);
        freeaddrinfo(res);
        return (*static_cast<struct sockaddr*>(ss_ptr));
    }

    // We don't expect getaddrinfo to fail for our tests.  But if that
    // ever happens we throw an exception to make sure the corresponding test
    // fail (either due to a failure of *_NO_THROW or the uncaught exception).
    isc_throw(Unexpected,
              "failed to convert textual IP address to sockaddr for " <<
              addr);
}

} // end of namespace "tests"
} // end of namespace "acl"
} // end of namespace "isc"

#endif  // ACL_TEST_SOCKADDR_H

// Local Variables:
// mode: c++
// End:
