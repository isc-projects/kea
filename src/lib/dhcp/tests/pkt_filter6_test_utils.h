// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

    std::string ifname_;   ///< Loopback interface name.
    uint16_t ifindex_;     ///< Loopback interface index.
    uint16_t port_;        ///< A port number used for the test.
    isc::dhcp::SocketInfo sock_info_; ///< A structure holding socket info.
    int send_msg_sock_;    ///< Holds a descriptor of the socket used by
                           ///< sendMessage function.
    Pkt6Ptr test_message_; ///< A DHCPv6 message used by tests.

};

/// @brief A stub implementation of the PktFilter6 class.
///
/// This class implements abstract methods of the @c isc::dhcp::PktFilter class.
/// The methods of this class mimic operations on sockets, but they neither
/// open actual sockets, nor perform any send nor receive operations on them.
class PktFilter6Stub : public PktFilter6 {
public:

    /// @brief Constructor
    PktFilter6Stub();

    /// @brief Simulate opening of a socket.
    ///
    /// This function simulates opening a socket. In reality, it doesn't open a
    /// socket but the socket descriptor returned in the SocketInfo structure is
    /// always set to 0. On each call to this function, the counter of
    /// invocations is increased by one. This is useful to check if packet
    /// filter object has been correctly installed and is used by @c IfaceMgr.
    /// As in the case of opening a real socket, this function will check
    /// if there is another fake socket "bound" to the same address and port.
    /// If there is, it will throw an exception. This allows to simulate the
    /// conditions when one of the sockets can't be open because there is
    /// a socket already open and test how IfaceMgr will handle it.
    ///
    /// @param iface Interface descriptor.
    /// @param addr Address on the interface to be used to send packets.
    /// @param port Port number.
    /// @param join_multicast A boolean parameter which indicates whether
    /// socket should join All_DHCP_Relay_Agents_and_servers multicast
    /// group.
    ///
    /// @return A structure describing a primary and fallback socket.
    virtual SocketInfo openSocket(const Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port,
                                  const bool join_multicast);

    /// @brief Simulate reception of the DHCPv6 message.
    ///
    /// @param socket_info A structure holding socket information.
    ///
    /// @return Always a NULL object.
    virtual Pkt6Ptr receive(const SocketInfo& socket_info);

    /// @brief Simulate sending a DHCPv6 message.
    ///
    /// This function does nothing.
    ///
    /// @param iface Interface to be used to send packet.
    /// @param sockfd A socket descriptor
    /// @param pkt A packet to be sent.
    ///
    /// @note All parameters are ignored.
    ///
    /// @return 0.
    virtual int send(const Iface& iface, uint16_t sockfd, const Pkt6Ptr& pkt);

    /// Holds the number of invocations to PktFilter6Stub::openSocket.
    int open_socket_count_;

};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PKT_FILTER6_TEST_UTILS_H
