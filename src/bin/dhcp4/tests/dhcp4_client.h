// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCP4_CLIENT_H
#define DHCP4_CLIENT_H

#include <asiolink/io_address.h>
#include <dhcp/hwaddr.h>
#include <dhcp/pkt4.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {
namespace test {

/// @brief DHCPv4 client used for unit testing.
///
/// This class implements a DHCPv4 "client" which interoperates with the
/// @c NakedDhcpv4Srv class. It calls @c NakedDhcpv4Srv::fakeRecive to
/// deliver client messages to the server for processing. The server places
/// the response in the @c NakedDhcpv4Srv::fake_sent_ container. The client
/// pops messages from this container which simulates reception of the
/// response from the server.
///
/// The client maintains the leases it acquired from the server
///
/// The client exposes a set of functions which simulate different exchange
/// types between the client and the server. It also provides the access to
/// the objects encapsulating responses from the server so as it is possible
/// to verify from the unit test that the server's response is correct.
class Dhcp4Client : public boost::noncopyable {
public:

    /// @brief Holds the DHCPv4 messages taking part in transaction between
    /// the client and the server.
    struct Context {
        /// @brief Holds the last sent message from the client to the server.
        Pkt4Ptr query_;
        /// @brief Holds the last sent message by the server to the client.
        Pkt4Ptr response_;    };

    /// @brief Creates a new client.
    Dhcp4Client();

    /// @brief Creates a new client that communicates with a specified server.
    ///
    /// @param srv An instance of the DHCPv4 server to be used.
    Dhcp4Client(boost::shared_ptr<NakedDhcpv4Srv>& srv);

    /// @brief Sends DHCPINFORM message to the server and receives response.
    ///
    /// This function simulates sending the DHCPINFORM message to the server
    /// and receiving server's response (if any).
    ///
    /// @throw This function doesn't thrown exceptions on its own, but it calls
    /// functions that are not exception safe, so it may emit an exception if
    /// an error occurs.
    void doInform();

    /// @brief Generates a hardware address used by the client.
    ///
    /// It assiges random values to the bytes of the harware address.
    ///
    /// @param htype hardware address type. Currently the only type
    /// supported is ethernet hardware address.
    ///
    /// @return Pointer to the generated hardware address.
    HWAddrPtr generateHWAddr(const uint8_t htype = HTYPE_ETHER) const;

    /// @brief Returns HW address used by the client.
    HWAddrPtr getHWAddress() const;

    /// @brief Returns current context.
    const Context& getContext() const {
        return (context_);
    }

    /// @brief Returns the server that the client is communicating with.
    boost::shared_ptr<NakedDhcpv4Srv> getServer() const {
        return (srv_);
    }

    /// @brief Modifies the client's HW address (adds one to it).
    ///
    /// The HW address should be modified to test negative scenarios when the
    /// client acquires a lease and tries to renew it with a different HW
    /// address. The server should detect the HW address mismatch and react
    /// accordingly.
    ///
    /// The HW address modification affects the value returned by the
    /// @c Dhcp4Client::getHWAddress.
    void modifyHWAddr();

    /// @brief Sets destination address for the messages being sent by the
    /// client.
    ///
    /// By default, the client uses broadcast address 255.255.255.255 to
    /// communicate with the server. In certain cases it may be desired
    /// that different address is used. This function sets the new address
    /// for all future exchanges with the server.
    ///
    /// @param dest_addr New destination address.
    void setDestAddress(const asiolink::IOAddress& dest_addr) {
        dest_addr_ = dest_addr;
    }

    /// @brief Simulate sending messages through a relay.
    ///
    /// @param use Parameter which 'true' value indicates that client should
    /// simulate sending messages via relay.
    /// @param relay_addr Relay address
    void useRelay(const bool use = true,
                  const asiolink::IOAddress& relay_addr =
                  asiolink::IOAddress("10.0.0.2")) {
        use_relay_ = use;
        relay_addr_ = relay_addr;
    }

private:

    /// @brief Creates client's side DHCP message.
    ///
    /// @param msg_type Type of the message to be created.
    /// @return An instance of the message created.
    Pkt4Ptr createMsg(const uint8_t msg_type);

    /// @brief Simulates reception of the message from the server.
    ///
    /// @return Received message.
    Pkt4Ptr receiveOneMsg();

    /// @brief Simulates sending a message to the server.
    ///
    /// This function instantly triggers processing of the message by the
    /// server. The server's response can be gathered by invoking the
    /// @c receiveOneMsg function.
    ///
    /// @param msg Message to be sent.
    void sendMsg(const Pkt4Ptr& msg);

    /// @brief Current context (sent and received message).
    Context context_;

    /// @biref Current transaction id (altered on each send).
    uint32_t curr_transid_;

    /// @brief Currently use destination address.
    asiolink::IOAddress dest_addr_;

    /// @brief Current hardware address of the client.
    HWAddrPtr hwaddr_;

    /// @brief Relay address to use.
    asiolink::IOAddress relay_addr_;

    /// @brief Pointer to the server that the client is communicating with.
    boost::shared_ptr<NakedDhcpv4Srv> srv_;

    /// @brief Enable relaying messages to the server.
    bool use_relay_;
};

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif // DHCP4_CLIENT
