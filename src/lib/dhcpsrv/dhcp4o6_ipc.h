// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP4O6_IPC_H
#define DHCP4O6_IPC_H

/// @file dhcp4o6_ipc.h Defines the Dhcp4o6IpcBase class.
/// This file defines the class Kea uses as a base for
/// DHCPv4-over-DHCPv6 communication between servers.
///

#include <exceptions/exceptions.h>
#include <dhcp/pkt6.h>
#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when error occurs as a result of use of IPC.
class Dhcp4o6IpcError : public Exception {
public:
    Dhcp4o6IpcError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Base class implementing transmission of the DHCPv4 over
/// DHCPv6 messages (RFC 7341) between the Kea servers.
///
/// When the DHCPv6 server receives the DHCPv4 query message it needs
/// to forward it to the DHCPv4 server for processing. The DHCPv4
/// server processes the message and responds with the DHCPv4 response
/// message to the DHCPv6 server. The server forwards it back to the
/// client. This class implements the communication between the DHCPv4
/// and DHCPv6 servers to allow for transmission of the DHCPv4 query
/// and DHCPv6 response messages.
///
/// This class creates a socket (when @c open is called) and binds it
/// to a port, depending on the configuration. The port number is
/// explicitly specified in the server configuration. This explicit
/// port value is used directly on the DHCPv6 server side. The DHCPv4
/// server uses the port specified + 1.
///
/// The DHCPv4 and DHCPv6 servers use distict instances of classes derived
/// from this base class. Each of these instances is used to send and
/// receive messages sent by the other server.
///
/// In order to make address allocation decisions, the DHCPv4 server
/// requires information about the interface and the source address of
/// the original DHCPv4 query message sent by the client. This
/// information is known by the DHCPv6 server and needs to be conveyed
/// to the DHCPv4 server. The IPC conveys it in the
/// @c ISC_V6_4O6_INTERFACE and @c ISC_V6_4O6_SRC_ADDRESS options
/// within the Vendor Specific Information option, with ISC
/// enterprise id. These options are added by the IPC sender and removed
/// by the IPC receiver.
class Dhcp4o6IpcBase : public boost::noncopyable {
public:

    /// @brief Endpoint type: DHCPv4 or DHCPv6 server.
    enum EndpointType {
        ENDPOINT_TYPE_V4,
        ENDPOINT_TYPE_V6
    };

protected:
    /// @brief Constructor
    ///
    /// Default constructor
    Dhcp4o6IpcBase();

    /// @brief Destructor.
    virtual ~Dhcp4o6IpcBase();

    /// @brief Open communication socket (from base class).
    ///
    /// @param port Port number to use. The socket is bound to this port
    /// if the endpoint type is DHCPv6 server, otherwise the port + 1
    /// value is used.
    /// @param endpoint_type Endpoint type (DHCPv4 or DHCPv6 server).
    ///
    /// @return New socket descriptor.
    int open(const uint16_t port, const EndpointType& endpoint_type);

public:

    /// @brief Open communication socket (for derived classes).
    virtual void open() = 0;

    /// @brief Close communication socket.
    void close();

    /// @brief Receive message over IPC.
    ///
    /// @return a pointer to a DHCPv6 message with interface and remote
    /// address set from the IPC message
    Pkt6Ptr receive();

    /// @brief Send message over IPC.
    ///
    /// The IPC uses @c ISC_V6_4O6_INTERFACE and @c ISC_V6_4O6_SRC_ADDRESS
    /// options conveyed within the Vendor Specific Information option, with
    /// ISC enterprise id, to communicate the client remote address and the
    /// interface on which the DHCPv4 query was received. These options will
    /// be removed by the receiver.
    ///
    /// @param pkt Pointer to a DHCPv6 message with interface and remote
    /// address.
    void send(const Pkt6Ptr& pkt);

protected:

    /// @brief Port number configured for IPC communication.
    uint16_t port_;

    /// @brief Socket descriptor.
    int socket_fd_;
};

} // namespace isc
} // namespace dhcp

#endif
