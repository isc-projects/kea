// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/tests/pkt_filter_test_utils.h>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// Port number used by tests.
const uint16_t PORT = 10067;

class PktFilterBaseClassTest : public isc::dhcp::test::PktFilterTest {
public:
    /// @brief Constructor
    ///
    /// Does nothing but setting up the UDP port for the test.
    PktFilterBaseClassTest() : PktFilterTest(PORT) {
    }
};

// This test verifies that the fallback socket is successfuly opened and
// bound using the protected function of the PktFilter class.
TEST_F(PktFilterBaseClassTest, openFallbackSocket) {
    // Open socket using the function under test. Note that, we don't have to
    // close the socket on our own because the test fixture constructor
    // will handle it.
    PktFilterStub pkt_filter;
    ASSERT_NO_THROW(sock_info_.fallbackfd_ =
                    pkt_filter.openFallbackSocket(IOAddress("127.0.0.1"), PORT)
    );
    // Test that the socket has been successfully created.
    testDgramSocket(sock_info_.fallbackfd_);

    // Now that we have the socket open, let's try to open another one. This
    // should cause a binding error.
    int another_sock;
    EXPECT_THROW(another_sock =
                 pkt_filter.openFallbackSocket(IOAddress("127.0.0.1"), PORT),
                 isc::dhcp::SocketConfigError);
    // Hard to believe we managed to open another socket. But if so, we have
    // to close it to prevent a resource leak.
    if (another_sock >= 0) {
        close(another_sock);
    }
}

} // anonymous namespace
