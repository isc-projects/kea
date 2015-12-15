// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/tests/pkt_filter_test_utils.h>
#include <gtest/gtest.h>
#include <fcntl.h>

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
                    pkt_filter.openFallbackSocket(IOAddress("127.0.0.1"), PORT))
        << "Failed to open fallback socket.";

    // Test that the socket has been successfully created.
    testDgramSocket(sock_info_.fallbackfd_);

    // In addition, we should check that the fallback socket is non-blocking.
    int sock_flags = fcntl(sock_info_.fallbackfd_, F_GETFL);
    EXPECT_EQ(O_NONBLOCK, sock_flags & O_NONBLOCK)
        << "Fallback socket is blocking, it should be non-blocking - check"
        " fallback socket flags (fcntl).";

    // Now that we have the socket open, let's try to open another one. This
    // should cause a binding error.
    int another_sock = -1;
    EXPECT_THROW(another_sock =
                 pkt_filter.openFallbackSocket(IOAddress("127.0.0.1"), PORT),
                 isc::dhcp::SocketConfigError)
        << "it should be not allowed to open and bind two fallback sockets"
        " to the same address and port. Surprisingly, the socket bound.";
    // Hard to believe we managed to open another socket. But if so, we have
    // to close it to prevent a resource leak.
    if (another_sock >= 0) {
        close(another_sock);
    }
}

} // anonymous namespace
