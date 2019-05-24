// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PERF_SOCKET_H
#define PERF_SOCKET_H

#include <perfdhcp/command_options.h>

#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/socket_info.h>
#include <dhcp/iface_mgr.h>

namespace isc {
namespace perfdhcp {

/// \brief Socket wrapper structure.
///
/// This is a base class that is inherited by PerfSocket
/// and unit tests derived that. This way it allows mocking
/// out socket operations and avoid using real network
/// interfaces.
class BasePerfSocket : public dhcp::SocketInfo {
public:
    /// Interface index.
    uint16_t ifindex_;

    /// \brief Default constructor of BasePerfSocket.
    BasePerfSocket() :
        SocketInfo(asiolink::IOAddress("127.0.0.1"), 0, 0),
        ifindex_(0) {}

    /// \brief Destructor of the socket wrapper class.
    virtual ~BasePerfSocket() = default;

    /// \brief See description of this method in PerfSocket class below.
    virtual dhcp::Pkt4Ptr receive4(uint32_t timeout_sec, uint32_t timeout_usec) = 0;

    /// \brief See description of this method in PerfSocket class below.
    virtual dhcp::Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec) = 0;

    /// \brief See description of this method in PerfSocket class below.
    virtual bool send(const dhcp::Pkt4Ptr& pkt) = 0;

    /// \brief See description of this method in PerfSocket class below.
    virtual bool send(const dhcp::Pkt6Ptr& pkt) = 0;

    /// \brief See description of this method in PerfSocket class below.
    virtual dhcp::IfacePtr getIface() = 0;
};

/// \brief Socket wrapper structure.
///
/// This is the wrapper that holds descriptor of the socket
/// used to run DHCP test. The wrapped socket is closed in
/// the destructor. This prevents resource leaks when
/// function that created the socket ends (normally or
/// when exception occurs). This structure extends parent
/// structure with new field ifindex_ that holds interface
/// index where socket is bound to.
class PerfSocket : public BasePerfSocket {
public:
    /// \brief Constructor of socket wrapper class.
    ///
    /// This constructor uses provided socket descriptor to
    /// find the name of the interface where socket has been
    /// bound to.
    PerfSocket(CommandOptions& options);

    /// \brief Destructor of the socket wrapper class.
    ///
    /// Destructor closes wrapped socket.
    virtual ~PerfSocket();

    /// \brief Receive DHCPv4 packet from interface.
    ///
    /// \param timeout_sec number of seconds for waiting for a packet,
    /// \param timeout_usec number of microseconds for waiting for a packet,
    /// \return received packet or nullptr if timed out
    virtual dhcp::Pkt4Ptr receive4(uint32_t timeout_sec, uint32_t timeout_usec) override;

    /// \brief Receive DHCPv6 packet from interface.
    ///
    /// \param timeout_sec number of seconds for waiting for a packet,
    /// \param timeout_usec number of microseconds for waiting for a packet,
    /// \return received packet or nullptr if timed out
    virtual dhcp::Pkt6Ptr receive6(uint32_t timeout_sec, uint32_t timeout_usec) override;

    /// \brief Send DHCPv4 packet through interface.
    ///
    /// \param pkt a packet for sending
    /// \return true if operation succeeded
    virtual bool send(const dhcp::Pkt4Ptr& pkt) override;

    /// \brief Send DHCPv6 packet through interface.
    ///
    /// \param pkt a packet for sending
    /// \return true if operation succeeded
    virtual bool send(const dhcp::Pkt6Ptr& pkt) override;

    /// \brief Get interface from IfaceMgr.
    ///
    /// \return shared pointer to Iface.
    virtual dhcp::IfacePtr getIface() override;

protected:
    /// \brief Initialize socket data.
    ///
    /// This method initializes members of the class that Interface
    /// Manager holds: interface name, local address.
    ///
    /// \throw isc::BadValue if interface for specified socket
    /// descriptor does not exist.
    void initSocketData();

    /// \brief Open socket to communicate with DHCP server.
    ///
    /// Method opens socket and binds it to local address. Function will
    /// use either interface name, local address or server address
    /// to create a socket, depending on what is available (specified
    /// from the command line). If socket can't be created for any
    /// reason, exception is thrown.
    /// If destination address is broadcast (for DHCPv4) or multicast
    /// (for DHCPv6) than broadcast or multicast option is set on
    /// the socket. Opened socket is registered and managed by IfaceMgr.
    ///
    /// \throw isc::BadValue if socket can't be created for given
    /// interface, local address or remote address.
    /// \throw isc::InvalidOperation if broadcast option can't be
    /// set for the v4 socket or if multicast option can't be set
    /// for the v6 socket.
    /// \throw isc::Unexpected if internal unexpected error occurred.
    /// \return socket descriptor.
    int openSocket(CommandOptions& options) const;
};

}
}

#endif /* PERF_SOCKET_H */
