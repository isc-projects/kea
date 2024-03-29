// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_FILTER_TEST_STUB_H
#define PKT_FILTER_TEST_STUB_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt4.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief An open socket callback that can be use for a testing purposes.
///
/// @param port Port number to bind socket to.
typedef std::function<void(uint16_t port)> PktFilterOpenSocketCallback;

/// @brief A stub implementation of the PktFilter class.
///
/// This class implements abstract methods of the @c isc::dhcp::PktFilter
/// class. It is used by unit tests, which test protected methods of the
/// @c isc::dhcp::test::PktFilter class. The implemented abstract methods are
/// no-op.
class PktFilterTestStub : public PktFilter {
public:

    /// @brief Constructor.
    PktFilterTestStub();

    /// @brief Checks if the direct DHCPv4 response is supported.
    ///
    /// This function checks if the direct response capability is supported,
    /// i.e. if the server can respond to the client which doesn't have an
    /// address yet. For this dummy class, the true is always returned.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const;

    /// @brief Check if the socket received time is supported.
    ///
    /// If true, then packets received through this filter will include
    /// a SOCKET_RECEIVED event in its event stack.  Other than direct
    /// clients using BPF for which this is always true, this function
    /// is true provided SO_TIMESTAMP is defined.
    ///
    /// @return True if it is supported.
    virtual bool isSocketReceivedTimeSupported() const;

    /// @brief Simulate opening of the socket.
    ///
    /// This function simulates opening a primary socket. Rather than open
    /// an actual socket, the stub performs a read-only open of "/dev/null".
    /// The fd returned by this open saved as the socket's descriptor in the
    /// SocketInfo structure.  This way the filter consumes an actual
    /// descriptor and retains it until its socket is closed.
    ///
    /// @param iface An interface descriptor.
    /// @param addr Address on the interface to be used to send packets.
    /// @param port Port number to bind socket to.
    /// @param receive_bcast A flag which indicates if socket should be
    /// configured to receive broadcast packets (if true).
    /// @param send_bcast A flag which indicates if the socket should be
    /// configured to send broadcast packets (if true).
    ///
    /// @note All parameters are ignored.
    ///
    /// @return A SocketInfo structure with the socket descriptor set to 0. The
    /// fallback socket descriptor is set to a negative value.
    virtual SocketInfo openSocket(Iface& iface,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port,
                                  const bool receive_bcast,
                                  const bool send_bcast);

    /// @brief Simulate reception of the DHCPv4 message.
    ///
    /// @param iface An interface to be used to receive DHCPv4 message.
    /// @param sock_info A descriptor of the primary and fallback sockets.
    ///
    /// @note All parameters are ignored.
    ///
    /// @return always a NULL object.
    virtual Pkt4Ptr receive(Iface& iface, const SocketInfo& sock_info);

    /// @brief Simulates sending a DHCPv4 message.
    ///
    /// This function does nothing.
    ///
    /// @param iface An interface to be used to send DHCPv4 message.
    /// @param port A port used to send a message.
    /// @param pkt A DHCPv4 to be sent.
    ///
    /// @note All parameters are ignored.
    ///
    /// @return 0.
    virtual int send(const Iface& iface, uint16_t port, const Pkt4Ptr& pkt);

    // Change the scope of the protected function so as they can be unit tested.
    using PktFilter::openFallbackSocket;

    /// @brief Set an open socket callback. Use it for testing
    /// purposes, e.g. counting the number of calls or throwing an exception.
    void setOpenSocketCallback(PktFilterOpenSocketCallback callback) {
        open_socket_callback_ = callback;
    }

    /// @brief Flag which indicates if direct response capability is supported.
    bool direct_response_supported_;

private:

    /// @brief The callback used when opening socket.
    PktFilterOpenSocketCallback open_socket_callback_;
};

} // namespace isc::dhcp::test
} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_TEST_STUB_H
