// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_FILTER_H
#define PKT_FILTER_H

#include <dhcp/pkt4.h>
#include <asiolink/io_address.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when invalid packet filter object specified.
class InvalidPacketFilter : public Exception {
public:
    InvalidPacketFilter(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// Forward declaration to the structure describing a socket.
struct SocketInfo;

/// Forward declaration to the class representing interface
class Iface;

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

    /// @brief Virtual Destructor
    virtual ~PktFilter() { }

    /// @brief Check if packet can be sent to the host without address directly.
    ///
    /// Checks if the Packet Filter class has capability to send a packet
    /// directly to the client having no address assigned. This capability
    /// is used by DHCPv4 servers which respond to the clients they assign
    /// addresses to. Not all classes derived from PktFilter support this
    /// because it requires injection of the destination host HW address to
    /// the link layer header of the packet.
    ///
    /// @return true of the direct response is supported.
    virtual bool isDirectResponseSupported() const = 0;

    /// @brief Open primary and fallback socket.
    ///
    /// A method implementation in the derived class may open one or two
    /// sockets:
    /// - a primary socket - used for communication with clients. DHCP messages
    /// received using this socket are processed and the same socket is used
    /// to send a response to the client.
    /// - a fallback socket which is optionally opened if there is a need for
    /// the presence of the socket which can be bound to a specific IP address
    /// and UDP port (e.g. raw primary socket can't be). For the details, see
    /// the documentation of @c isc::dhcp::SocketInfo.
    ///
    /// @param iface Interface descriptor.
    /// @param addr Address on the interface to be used to send packets.
    /// @param port Port number.
    /// @param receive_bcast Configure socket to receive broadcast messages
    /// @param send_bcast configure socket to send broadcast messages.
    ///
    /// @return A structure describing a primary and fallback socket.
    virtual SocketInfo openSocket(Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port,
                                  const bool receive_bcast,
                                  const bool send_bcast) = 0;

    /// @brief Receive packet over specified socket.
    ///
    /// @param iface interface
    /// @param socket_info structure holding socket information
    ///
    /// @return Received packet
    virtual Pkt4Ptr receive(Iface& iface,
                            const SocketInfo& socket_info) = 0;

    /// @brief Send packet over specified socket.
    ///
    /// @param iface interface to be used to send packet
    /// @param sockfd socket descriptor
    /// @param pkt packet to be sent
    ///
    /// @return result of sending the packet. It is 0 if successful.
    virtual int send(const Iface& iface, uint16_t sockfd,
                     const Pkt4Ptr& pkt) = 0;

protected:

    /// @brief Default implementation to open a fallback socket.
    ///
    /// This method provides a means to open a fallback socket and bind it
    /// to a given IPv4 address and UDP port. This function may be used by the
    /// derived classes to create a fallback socket. It can be overridden
    /// in the derived classes if it happens to be insufficient on some
    /// environments.
    ///
    /// The fallback socket is meant to be opened together with the other socket
    /// (a.k.a. primary socket) used to receive and handle DHCPv4 traffic. The
    /// traffic received through the fallback should be dropped. The reasoning
    /// behind opening the fallback socket is explained in the documentation of
    /// @c isc::dhcp::SocketInfo structure.
    ///
    /// @param addr An IPv4 address to bind the socket to.
    /// @param port A port number to bind socket to.
    ///
    /// @return A fallback socket descriptor. This descriptor should be assigned
    /// to the @c fallbackfd_ field of the @c isc::dhcp::SocketInfo structure.
    /// @throw isc::dhcp::SocketConfigError if socket opening, binding or
    /// configuration fails.
    virtual int openFallbackSocket(const isc::asiolink::IOAddress& addr,
                                   const uint16_t port);
};

/// Pointer to a PktFilter object.
typedef boost::shared_ptr<PktFilter> PktFilterPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_H
