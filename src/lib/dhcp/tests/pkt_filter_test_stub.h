// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PKT_FILTER_TEST_STUB_H
#define PKT_FILTER_TEST_STUB_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt4.h>

namespace isc {
namespace dhcp {
namespace test {

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
    /// address yet. For this dummy class, the true is alaways returned.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const;

    /// @brief Simulate opening of the socket.
    ///
    /// This function simulates opening a primary socket. In reality, it doesn't
    /// open a socket but the socket descriptor returned in the SocketInfo
    /// structure is always set to 0.
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

    bool direct_response_supported_;
};

} // namespace isc::dhcp::test
} // namespace isc::dhcp
} // namespace isc

#endif // PKT_FILTER_TEST_STUB_H
