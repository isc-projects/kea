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

#ifndef PKT_FILTER_INET_H
#define PKT_FILTER_INET_H

#include <dhcp/pkt_filter.h>
#include <boost/scoped_array.hpp>

namespace isc {
namespace dhcp {

/// @brief Packet handling class using AF_INET socket family
///
/// This class provides methods to send and recive packet via socket using
/// AF_INET family and SOCK_DGRAM type.
class PktFilterInet : public PktFilter {
public:

    /// @brief Constructor
    ///
    /// Allocates control buffer.
    PktFilterInet();

    /// @brief Check if packet can be sent to the host without address directly.
    ///
    /// This Packet Filter sends packets through AF_INET datagram sockets, so
    /// it can't inject the HW address of the destionation host into the packet.
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
    /// @throw An execption thrown by the isc::dhcp::Pkt4 object if DHCPv4
    /// message parsing fails.
    virtual Pkt4Ptr receive(Iface& iface, const SocketInfo& socket_info);

    /// @brief Send packet over specified socket.
    ///
    /// @param iface interface to be used to send packet
    /// @param sockfd socket descriptor
    /// @param pkt packet to be sent
    ///
    /// @return result of sending a packet. It is 0 if successful.
    /// @throw isc::dhcp::SocketWriteError if an error occures during sending
    /// a DHCP message through the socket.
    virtual int send(const Iface& iface, uint16_t sockfd,
                     const Pkt4Ptr& pkt);

private:
    /// Length of the control_buf_ array.
    size_t control_buf_len_;
    /// Control buffer, used in transmission and reception.
    boost::scoped_array<char> control_buf_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_INET_H
