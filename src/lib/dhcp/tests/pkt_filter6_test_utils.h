// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PKT_FILTER6_TEST_UTILS_H
#define PKT_FILTER6_TEST_UTILS_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt_filter.h>
#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test fixture class for testing classes derived from PktFilter6 class.
///
/// This class implements a simple algorithm checking presence of the loopback
/// interface and initializing its index. It assumes that the loopback interface
/// name is one of 'lo' or 'lo0'. If none of those interfaces is found, the
/// constructor will report a failure.
///
/// @todo The interface detection algorithm should be more generic. This will
/// be possible once the cross-OS interface detection is implemented.
class PktFilter6Test : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// This constructor initializes sock_info_ structure to a default value.
    /// The socket descriptors should be set to a negative value to indicate
    /// that no socket has been opened. Specific tests will reinitialize this
    /// structure with the values of the open sockets. For non-negative socket
    /// descriptors, the class destructor will close associated sockets.
    PktFilter6Test(const uint16_t port);

    /// @brief Destructor
    ///
    /// Closes open sockets (if any).
    virtual ~PktFilter6Test();

    /// @brief Initializes DHCPv6 message used by tests.
    void initTestMessage();

    /// @brief Detect loopback interface.
    ///
    /// @todo this function will be removed once cross-OS interface
    /// detection is implemented
    void loInit();

    /// @brief Sends a single DHCPv6 message to the loopback address.
    ///
    /// This function opens a datagram socket and binds it to the local loopback
    /// address and client port. The client's port is assumed to be port_ + 1.
    /// The send_msg_sock_ member holds the socket descriptor so as the socket
    /// is closed automatically in the destructor. If the function succeeds to
    /// send a DHCPv6 message, the socket is closed so as the function can be
    /// called again within the same test.
    void sendMessage();

    /// @brief Test that the datagram socket is opened correctly.
    ///
    /// This function is used by multiple tests.
    ///
    /// @param sock A descriptor of the open socket.
    void testDgramSocket(const int sock) const;

    /// @brief Checks if the received message matches the test_message_.
    ///
    /// @param rcvd_msg An instance of the message to be tested.
    void testRcvdMessage(const Pkt6Ptr& rcvd_msg) const;

    std::string ifname_;   ///< Loopback interface name
    uint16_t ifindex_;     ///< Loopback interface index.
    uint16_t port_;        ///< A port number used for the test.
    isc::dhcp::SocketInfo sock_info_; ///< A structure holding socket info.
    int send_msg_sock_;    ///< Holds a descriptor of the socket used by
                           ///< sendMessage function.
    Pkt6Ptr test_message_; ///< A DHCPv6 message used by tests.

};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PKT_FILTER6_TEST_UTILS_H
