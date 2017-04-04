// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_FILTER_BPF_H
#define PKT_FILTER_BPF_H

#include <dhcp/pkt_filter.h>

#include <util/buffer.h>

namespace isc {
namespace dhcp {

/// @brief Packet handling class using Berkeley Packet Filtering (BPF)
///
/// The BPF is supported on the BSD-like operating systems. It allows for access
/// to low level layers of the inbound and outbound packets. This is specifically
/// useful when the DHCP server is allocating new address to the client.
///
/// The response being sent to the client must include the HW address in the
/// datalink layer. When the regular datagram socket is used the kernel will
/// determine the HW address of the destination using ARP. In the case when
/// the DHCP server is allocating the new address for the client the ARP can't
/// be used because it requires the destination to have the IP address.
///
/// The DHCP server utilizes HW address sent by the client in the DHCP message
/// and stores it in the datalink layer of the outbound packet. The BPF provides
/// the means for crafting the whole packet (including datalink and network
/// layers) and injecting the hardware address of the client.
///
/// The DHCP server receiving the messages sent from the directly connected
/// clients to the broadcast address must be able to determine the interface
/// on which the message arrives. The Linux kernel provides the SO_BINDTODEVICE
/// socket option which allows for binding the socket to the particular
/// interface. This option is not implemented on the BSD-like operating
/// systems. This implies that there may be only one datagram socket listening
/// to broadcast messages and this socket would receive the traffic on all
/// interfaces. This effectively precludes the server from identifying the
/// interface on which the packet arrived. The BPF resolves this problem.
/// The BPF device (socket) can be attached to the selected interface using
/// the ioctl function.
///
/// In nutshell, the BPF device is created by opening the file /dev/bpf%d
/// where %d is a number. The BPF device is configured by issuing ioctl
/// commands listed here: http://www.freebsd.org/cgi/man.cgi?bpf(4).
/// The specific configuration used by Kea DHCP server is described in
/// documentation of @c PktFilterBPF::openSocket.
///
/// Use of BPF requires Kea to encode and decode the datalink and network
/// layer headers. Currently Kea supports encoding and decoding ethernet
/// frames on physical interfaces and pseudo headers received on local
/// loopback interface.
class PktFilterBPF : public PktFilter {
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
    /// This method opens the BPF device and applies the following
    /// configuration to it:
    /// - attach the device to the specified interface
    /// - set filter program to receive DHCP messages encapsulated in UDP
    /// packets
    /// - set immediate mode which causes the read function to return
    /// immediately and do not wait for the whole read buffer to be filled
    /// by the kernel (to avoid hangs)
    ///
    /// It also obtains the following configuration from the kernel:
    /// - major and minor version of the BPF (and checks if it is valid)
    /// - length of the buffer to be used to receive the data from the socket
    ///
    /// @param iface Interface descriptor. Note that the function (re)allocates
    /// the socket read buffer according to the buffer size returned by the
    /// kernel.
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
    /// @return Received packet
    virtual Pkt4Ptr receive(Iface& iface, const SocketInfo& socket_info);

    /// @brief Send packet over specified socket.
    ///
    /// @param iface interface to be used to send packet
    /// @param sockfd socket descriptor
    /// @param pkt packet to be sent
    ///
    /// @return result of sending a packet. It is 0 if successful.
    virtual int send(const Iface& iface, uint16_t sockfd,
                     const Pkt4Ptr& pkt);

private:

    /// @brief Writes pseudo header containing an address family into a buffer.
    ///
    /// BPF utilizes the pseudo headers to pass the ancillary data between the
    /// kernel and the application. For example, when the packet is to be sent
    /// over the local loopback interface the pseudo header must be added before
    /// the network layer header to indicate the address family. Other link
    /// layer header (e.g. ethernet) is not used for local loopback interface.
    ///
    /// The header written by this method consists of 4 bytes and contains the
    /// address family value in host byte order. See sys/socket.h for the
    /// address family values. Typically it will be AF_INET.
    ///
    /// This function doesn't throw.
    ///
    /// @param address_family Address family (e.g. AF_INET).
    /// @param [out] out_buf buffer where a header is written.
    void writeAFPseudoHeader(const uint32_t address_family,
                             util::OutputBuffer& out_buf);

};

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_BPF_H
