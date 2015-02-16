// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PKT_FILTER_TEST_UTILS_H
#define PKT_FILTER_TEST_UTILS_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt_filter.h>
#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test fixture class for testing classes derived from PktFilter class.
///
/// This class implements a simple algorithm checking presence of the loopback
/// interface and initializing its index. It assumes that the loopback interface
/// name is one of 'lo' or 'lo0'. If none of those interfaces is found, the
/// constructor will report a failure.
///
/// @todo The interface detection algorithm should be more generic. This will
/// be possible once the cross-OS interface detection is implemented.
class PktFilterTest : public ::testing::Test {
public:

    /// @brief Constructor
    ///
    /// This constructor initializes sock_info_ structure to a default value.
    /// The socket descriptors should be set to a negative value to indicate
    /// that no socket has been opened. Specific tests will reinitialize this
    /// structure with the values of the open sockets. For non-negative socket
    /// descriptors, the class destructor will close associated sockets.
    PktFilterTest(const uint16_t port);

    /// @brief Destructor
    ///
    /// Closes open sockets (if any).
    virtual ~PktFilterTest();

    /// @brief Initializes DHCPv4 message used by tests.
    void initTestMessage();

    /// @brief Detect loopback interface.
    ///
    /// @todo this function will be removed once cross-OS interface
    /// detection is implemented
    void loInit();

    /// @brief Sends a single DHCPv4 message to the loopback address.
    ///
    /// This function opens a datagram socket and binds it to the local loopback
    /// address and client port. The client's port is assumed to be port_ + 1.
    /// The send_msg_sock_ member holds the socket descriptor so as the socket
    /// is closed automatically in the destructor. If the function succeeds to
    /// send a DHCPv4 message, the socket is closed so as the function can be
    /// called again within the same test.
    ///
    /// @param dest Destination address for the packet.
    void sendMessage(const asiolink::IOAddress& dest =
                     asiolink::IOAddress("127.0.0.1"));

    /// @brief Test that the datagram socket is opened correctly.
    ///
    /// This function is used by multiple tests.
    ///
    /// @param sock A descriptor of the open socket.
    void testDgramSocket(const int sock) const;

    /// @brief Checks if the received message matches the test_message_.
    ///
    /// @param rcvd_msg An instance of the message to be tested.
    void testRcvdMessage(const Pkt4Ptr& rcvd_msg) const;

    std::string ifname_;   ///< Loopback interface name
    uint16_t ifindex_;     ///< Loopback interface index.
    uint16_t port_;        ///< A port number used for the test.
    isc::dhcp::SocketInfo sock_info_; ///< A structure holding socket info.
    int send_msg_sock_;    ///< Holds a descriptor of the socket used by
                           ///< sendMessage function.
    Pkt4Ptr test_message_; ///< A DHCPv4 message used by tests.

};

/// @brief A stub implementation of the PktFilter class.
///
/// This class implements abstract methods of the @c isc::dhcp::PktFilter
/// class. It is used by unit tests, which test protected methods of the
/// @c isc::dhcp::test::PktFilter class. The implemented abstract methods are
/// no-op.
class PktFilterStub : public PktFilter {
public:

    /// @brief Checks if the direct DHCPv4 response is supported.
    ///
    /// This function checks if the direct response capability is supported,
    /// i.e. if the server can respond to the client which doesn't have an
    /// address yet. For this dummy class, the true is alaways returned.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const;

    /// @brief Simulate opening of the socket.
    ///
    /// This function simulates opening a primary socket. In reality, it doesn't
    /// open a socket but the socket descriptor returned in the SocketInfo
    /// structure is always set to 0.
    ///
    /// @param iface An interface descriptor.
    /// @param addr Address on the interface to be used to send packets.
    /// @param port Port number to bind socket to.
    /// @param receive_bcast A flag which indicates if socket should be
    /// configured to receive broadcast packets (if true).
    /// @param send_bcast A flag which indicates if the socket should be
    /// configured to send broadcast packets (if true).
    ///
    /// @note All parameters are ignored.
    ///
    /// @return A SocketInfo structure with the socket descriptor set to 0. The
    /// fallback socket descriptor is set to a negative value.
    virtual SocketInfo openSocket(Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port,
                                  const bool receive_bcast,
                                  const bool send_bcast);

    /// @brief Simulate reception of the DHCPv4 message.
    ///
    /// @param iface An interface to be used to receive DHCPv4 message.
    /// @param sock_info A descriptor of the primary and fallback sockets.
    ///
    /// @note All parameters are ignored.
    ///
    /// @return always a NULL object.
    virtual Pkt4Ptr receive(Iface& iface, const SocketInfo& sock_info);

    /// @brief Simulates sending a DHCPv4 message.
    ///
    /// This function does nothing.
    ///
    /// @param iface An interface to be used to send DHCPv4 message.
    /// @param port A port used to send a message.
    /// @param pkt A DHCPv4 to be sent.
    ///
    /// @note All parameters are ignored.
    ///
    /// @return 0.
    virtual int send(const Iface& iface, uint16_t port, const Pkt4Ptr& pkt);

    // Change the scope of the protected function so as they can be unit tested.
    using PktFilter::openFallbackSocket;

};


}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PKT_FILTER_TEST_UTILS_H
