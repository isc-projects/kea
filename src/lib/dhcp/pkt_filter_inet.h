// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_FILTER_INET_H
#define PKT_FILTER_INET_H

#include <dhcp/pkt_filter.h>
#include <boost/scoped_array.hpp>

namespace isc {
namespace dhcp {

/// @brief Packet handling class using AF_INET socket family
///
/// This class provides methods to send and receive packet via socket using
/// AF_INET family and SOCK_DGRAM type.
class PktFilterInet : public PktFilter {
public:

    /// @brief Check if packet can be sent to the host without address directly.
    ///
    /// This Packet Filter sends packets through AF_INET datagram sockets, so
    /// it can't inject the HW address of the destination host into the packet.
    /// Therefore this class does not support direct responses.
    ///
    /// @return false always.
    virtual bool isDirectResponseSupported() const {
        return (false);
    }

    /// @brief Open primary and fallback socket.
    ///
    /// @param iface Interface descriptor.
    /// @param addr Address on the interface to be used to send packets.
    /// @param port Port number.
    /// @param receive_bcast Configure socket to receive broadcast messages
    /// @param send_bcast Configure socket to send broadcast messages.
    ///
    /// @return A structure describing a primary and fallback socket.
    /// @throw isc::dhcp::SocketConfigError if error occurs when opening,
    /// binding or configuring the socket.
    virtual SocketInfo openSocket(Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port,
                                  const bool receive_bcast,
                                  const bool send_bcast);

    /// @brief Receive packet over specified socket.
    ///
    /// @param iface interface
    /// @param socket_info structure holding socket information
    ///
    /// @return Received packet
    /// @throw isc::dhcp::SocketReadError if an error occurs during reception
    /// of the packet.
    /// @throw An exception thrown by the isc::dhcp::Pkt4 object if DHCPv4
    /// message parsing fails.
    virtual Pkt4Ptr receive(Iface& iface, const SocketInfo& socket_info);

    /// @brief Send packet over specified socket.
    ///
    /// This function will use local address specified in the @c pkt as a source
    /// address for the packet and the interface index to select the index
    /// through which the packet will be sent. However, if these values
    /// are not specified for the packet (zero IP address and negative
    /// interface index), this function will rely on the routing information
    /// to determine the right outbound interface and source address.
    ///
    /// @param iface interface to be used to send packet
    /// @param sockfd socket descriptor
    /// @param pkt packet to be sent
    ///
    /// @return result of sending a packet. It is 0 if successful.
    /// @throw isc::dhcp::SocketWriteError if an error occurs during sending
    /// a DHCP message through the socket.
    virtual int send(const Iface& iface, uint16_t sockfd, const Pkt4Ptr& pkt);

private:
    /// Length of the socket control buffer.
    static const size_t CONTROL_BUF_LEN;
};

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_INET_H
