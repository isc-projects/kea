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

#ifndef PKT_FILTER6_H
#define PKT_FILTER6_H

namespace isc {
namespace dhcp {

/// Forward declaration to the structure describing a socket.
struct SocketInfo;

/// Forward declaration to the class representing interface
class Iface;

/// @brief Abstract packet handling class for DHCPv6.
///
/// This class defines methods for performing low level operations on IPv6
/// socket:
/// - open socket,
/// - send DHCPv6 message through the socket,
/// - receive DHCPv6 through the socket.
///
/// Methods exposed by this class are called through the @c IfaceMgr only. They
/// are not meant to be called directly, except unit testing.
///
/// The @c IfaceMgr is responsible for managing the pool of sockets. In
/// particular, @IfaceMgr detects interfaces suitable to send/receive DHCPv6
/// messages. When it intends to open a socket on a particular interface, it
/// will call the PktFilter6::openSocket. If this call is successful, the
/// structure describing a new socket is returned.
///
/// In order to send or receive a DHCPv6 message through this socket,
/// the @IfaceMgr must use PktFilter6::send or PktFilter6::receive functions of
/// the same class that has been used to open a socket, i.e. all send/receive
/// operations should be performed using this particular class.
///
/// The major motivation behind creating a separate class, to manage low level
/// operations using sockets, is to make @c IfaceMgr unit testable. By providing
/// a stub implementation of this class which mimics the behavior of the real
/// socket handling class, it is possible to simulate and test various
/// conditions. For example, the @c IfaceMgr::openSockets function will try to
/// open sockets on all available interfaces. The test doesn't have any means
/// to know which interfaces are present. In addition, even if the network
/// interface detection was implemented on the test side, there is no guarantee
/// that the particular system has sufficient number of suitable IPv6-enabled
/// interfaces available for a particular test. Moreover, the test may need
/// to tweak some of the interface configuration to cover certain test
/// scenarios. The proposed solution is to not use the actual interfaces
/// but simply create a pool of fake interfaces which configuration
/// can be freely modified by a test. This however implies that operations
/// on sockets must be simulated.
class PktFilter6 {
public:

    /// @brief Virtual Destructor.
    virtual ~PktFilter6() { }

    /// @brief Open a socket.
    ///
    /// This function open an IPv6 socket on an interface and binds it to a
    /// specified UDP port and IP address.
    ///
    /// @param iface Interface descriptor.
    /// @param addr Address on the interface to be used to send packets.
    /// @param port Port number.
    ///
    /// @return A structure describing a primary and fallback socket.
    virtual SocketInfo openSocket(const Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port) = 0;

    /// @brief Receive DHCPv6 message on the interface.
    ///
    /// This function receives a single DHCPv6 message through using a socket
    /// open on a specified interface.
    ///
    /// @param iface interface
    /// @param socket_info structure holding socket information
    ///
    /// @return A pointer to received message.
    virtual Pkt6Ptr receive(const Iface& iface,
                            const SocketInfo& socket_info) = 0;

    /// @brief Send DHCPv6 message through a specified interface and socket.
    ///
    /// Thie function sends a DHCPv6 message through a specified interface and
    /// socket. In general, there may be multiple sockets open on a single
    /// interface as a single interface may have multiple IPv6 addresses.
    ///
    /// @param iface Interface to be used to send packet.
    /// @param sockfd A socket descriptor
    /// @param pkt A packet to be sent.
    ///
    /// @return A result of sending the message. It is 0 if successful.
    virtual int send(const Iface& iface, uint16_t sockfd,
                     const Pkt6Ptr& pkt) = 0;

};


/// Pointer to a PktFilter object.
typedef boost::shared_ptr<PktFilter6> PktFilter6Ptr;

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER6_H
