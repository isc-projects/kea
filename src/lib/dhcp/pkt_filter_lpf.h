// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_FILTER_LPF_H
#define PKT_FILTER_LPF_H

#include <dhcp/pkt_filter.h>

#include <util/buffer.h>

namespace isc {
namespace dhcp {

/// @brief Packet handling class using Linux Packet Filtering
///
/// This class provides methods to send and recive DHCPv4 messages using raw
/// sockets and Linux Packet Filtering. It is used by @c isc::dhcp::IfaceMgr
/// to send DHCPv4 messages to the hosts which don't have an IPv4 address
/// assigned yet.
class PktFilterLPF : public PktFilter {
public:

    /// @brief Check if packet can be sent to the host without address directly.
    ///
    /// This class supports direct responses to the host without address.
    ///
    /// @return true always.
    virtual bool isDirectResponseSupported() const {
        return (true);
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
    /// @throw isc::NotImplemented always
    /// @return Received packet
    virtual Pkt4Ptr receive(Iface& iface, const SocketInfo& socket_info);

    /// @brief Send packet over specified socket.
    ///
    /// @param iface interface to be used to send packet
    /// @param sockfd socket descriptor
    /// @param pkt packet to be sent
    ///
    /// @throw isc::NotImplemented always
    /// @return result of sending a packet. It is 0 if successful.
    virtual int send(const Iface& iface, uint16_t sockfd,
                     const Pkt4Ptr& pkt);

};

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_LPF_H
