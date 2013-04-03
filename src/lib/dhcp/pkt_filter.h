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

#ifndef PKT_FILTER_H
#define PKT_FILTER_H

#include <asiolink/io_address.h>

namespace isc {
namespace dhcp {

/// @brief Abstract packet handling class
///
/// This class represents low level method to send and receive DHCP packet.
/// Different methods, represented by classes derived from this class, use
/// different socket families and socket types. Also, various packet filtering
/// methods can be implemented by derived classes, e.g. Linux Packet
/// Filtering (LPF) or Berkeley Packet Filtering (BPF).
///
/// Low-level code operating on sockets may require special privileges to execute.
/// For example: opening raw socket or opening socket on low port number requires
/// root privileges. This makes it impossible or very hard to unit test the IfaceMgr.
/// In order to overcome this problem, it is recommended to create mock object derived
/// from this class that mimics the behavior of the real packet handling class making
/// IfaceMgr testable.
class PktFilter {
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
                           const bool send_bcast) = 0;

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

#endif // PKT_FILTER_H
