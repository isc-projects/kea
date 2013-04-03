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

#ifndef PKT_FILTER_INET_H
#define PKT_FILTER_INET_H

#include <dhcp/pkt_filter.h>

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

    /// @brief Open socket.
    ///
    /// @param iface interface descriptor
    /// @param addr address on the interface to be used to send packets.
    /// @param port port number.
    /// @param receive_bcast configure socket to receive broadcast messages
    /// @param send_bcast configure socket to send broadcast messages.
    ///
    /// @return created socket's descriptor
    virtual int openSocket(const Iface& iface,
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
    virtual Pkt4Ptr receive(const Iface& iface, const SocketInfo& socket_info);

    /// @brief Send packet over specified socket.
    ///
    /// @param sockfd socket descriptor
    /// @param pkt packet to be sent
    ///
    /// @return result of sending a packet. It is 0 if successful.
    virtual int send(uint16_t sockfd, const Pkt4Ptr& pkt);

private:
    /// Length of the control_buf_ array.
    size_t control_buf_len_;
    /// Control buffer, used in transmission and reception.
    boost::scoped_array<char> control_buf_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_INET_H
