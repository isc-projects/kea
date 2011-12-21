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

#include <server_common/socket_request.h>

#include <gtest/gtest.h>

using namespace isc::server_common;
using namespace isc;

namespace {

// Check it throws an exception when it is not initialized
TEST(SocketRequestorAccess, unitialized) {
    // Make sure it is not initialized
    SocketRequestor::initTest(NULL);
    EXPECT_THROW(socketRequestor(), InvalidOperation);
}

// It returns whatever it is initialized to
TEST(SocketRequestorAccess, initialized) {
    // A concrete implementation that does nothing, just can exist
    class DummyRequestor : public SocketRequestor {
    public:
        DummyRequestor() : SocketRequestor() {}
        virtual void releaseSocket(const std::string&) {}
        virtual SocketID requestSocket(Protocol, const std::string&, uint16_t,
                                       ShareMode, const std::string&)
        {
            return (SocketID(0, "")); // Just to silence warnings
        }
    };
    DummyRequestor requestor;
    // Make sure it is initialized (the test way, of course)
    SocketRequestor::initTest(&requestor);
    // It returs the same "pointer" as inserted
    // The casts are there as the template system seemed to get confused
    // without them, the types should be correct even without them, but
    // the EXPECT_EQ wanted to use long long int instead of pointers.
    EXPECT_EQ(static_cast<const SocketRequestor*>(&requestor),
              static_cast<const SocketRequestor*>(&socketRequestor()));
    // Just that we don't have an invalid pointer anyway
    SocketRequestor::initTest(NULL);
}

}
