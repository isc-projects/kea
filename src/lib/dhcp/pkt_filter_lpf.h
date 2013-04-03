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

#ifndef PKT_FILTER_LPF_H
#define PKT_FILTER_LPF_H

#include <dhcp/pkt_filter.h>

namespace isc {
namespace dhcp {

/// @brief Packet handling class using Linux Packet Filtering
///
/// This class provides methods to send and recive packet using raw sockets
/// and Linux Packet Filtering.
class PktFilterLPF : public PktFilter {
public:

    /// @brief Open socket.
    ///
    /// @param interface name
    /// @param addr address on the interface to be used to send packets.
    /// @param port port number.
    /// @param receive_bcast configure socket to receive broadcast messages
    /// @param send_bcast configure socket to send broadcast messages.
    ///
    /// @return created socket's descriptor
    virtual int openSocket(const std::string& ifname,
                           const isc::asiolink::IOAddress& addr,
                           const uint16_t port,
                           const bool receive_bcast,
                           const bool send_bcast);

    /// @brief Receive packet over specified socket.
    ///
    /// @param sockfd descriptor of a socket to be used for packet reception
    /// @param timeout_sec integral part of a timeout.
    /// @param timeout_usec fractional part of a timeout (in microseconds).
    ///
    /// @return Received packet
    Pkt4Ptr receive(uint16_t sockfd, uint32_t timeout_sec,
                    uint32_t timeout_usec = 0);

    //    bool send(const Pkt4Ptr& pkt) = 0;
};

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_LPF_H
