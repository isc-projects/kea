// Copyright (C) 2013-2015,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_FILTER6_H
#define PKT_FILTER6_H

#include <asiolink/io_address.h>
#include <dhcp/pkt6.h>

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
/// particular, @c IfaceMgr detects interfaces suitable to send/receive DHCPv6
/// messages. When it intends to open a socket on a particular interface, it
/// will call the PktFilter6::openSocket. If this call is successful, the
/// structure describing a new socket is returned.
///
/// In order to send or receive a DHCPv6 message through this socket,
/// the @c IfaceMgr must use PktFilter6::send or PktFilter6::receive
/// functions of the same class that has been used to open a socket,
/// i.e. all send/receive operations should be performed using this
/// particular class.
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
///
/// @note This class is named after @c PktFilter abstract class which exposes
/// similar interface for DHCPv4. However, the PktFilter class is devoted to
/// solve the problem of sending DHCPv4 messages to the hosts which don't have
/// an IP address yet (a.k.a. direct DHCPv4 traffic). Where required, the
/// custom implementations of @c PktFilter are provided to send and receive
/// messages through raw sockets. In order to filter out the desired traffic
/// Linux Packet Filtering or Berkeley Packet Filtering is used, hence the
/// name of the class. In case of DHCPv6 regular IPv6/UDPv6 sockets are used
/// and derived classes do not use Linux or Berkeley Packet Filtering.
class PktFilter6 {
public:

    /// @brief Virtual Destructor.
    virtual ~PktFilter6() { }

    /// @brief Opens a socket.
    ///
    /// This function open an IPv6 socket on an interface and binds it to a
    /// specified UDP port and IPv6 address.
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
                                  const bool join_multicast) = 0;

    /// @brief Receives DHCPv6 message on the interface.
    ///
    /// This function receives a single DHCPv6 message through using a socket
    /// open on a specified interface.
    ///
    /// @param socket_info A structure holding socket information.
    ///
    /// @return A pointer to received message.
    virtual Pkt6Ptr receive(const SocketInfo& socket_info) = 0;

    /// @brief Sends DHCPv6 message through a specified interface and socket.
    ///
    /// This function sends a DHCPv6 message through a specified interface and
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

    /// @brief Joins IPv6 multicast group on a socket.
    ///
    /// This function joins the socket to the specified multicast group.
    /// The socket descriptor must point to a valid socket bound to the
    /// in6addr_any prior to calling this function.
    ///
    /// @param sock A socket descriptor (socket must be bound).
    /// @param ifname An interface name (for link-scoped multicast groups).
    /// @param mcast A multicast address to join (e.g. "ff02::1:2").
    ///
    /// @return true if multicast join was successful
    static bool joinMulticast(int sock, const std::string& ifname,
                              const std::string & mcast);

};


/// Pointer to a PktFilter object.
typedef boost::shared_ptr<PktFilter6> PktFilter6Ptr;

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER6_H
