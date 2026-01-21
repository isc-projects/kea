// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_CLIENT_SERVER_H
#define RADIUS_CLIENT_SERVER_H

#include <client_attribute.h>
#include <client_message.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/crypto_tls.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/udp_socket.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <chrono>
#include <functional>
#include <list>
#include <mutex>
#include <string>
#include <vector>

namespace isc {
namespace radius {

/// @brief Default RADIUS access/authentication port.
static constexpr uint16_t PW_AUTH_PORT = 1812;

/// @brief Default RADIUS accounting port.
static constexpr uint16_t PW_ACCT_PORT = 1813;

/// @brief Default RADIUS/TLS port.
static constexpr uint16_t PW_TLS_PORT = 2083;

/// @brief Transport protocols.
enum RadiusProtocol {
    PW_PROTO_UDP,
    PW_PROTO_TCP,
    PW_PROTO_TLS
};

/// @brief Transport protocol to text.
std::string protocolToText(const int proto);

/// @brief RADIUS server class.
class Server : public data::CfgToElement {
public:
    /// @brief Get an address from a name.
    ///
    /// @param name the FQDN.
    /// @return the (first) address of the node with the FQDN.
    static asiolink::IOAddress getAddress(const std::string& name);

    /// @brief Get the source address from a destination address.
    ///
    /// @param dest the destination address.
    /// @return the source address to be used to send traffic to the
    /// destination address.
    static asiolink::IOAddress getSrcAddress(const asiolink::IOAddress& dest);

    /// @brief Constructor.
    ///
    /// @param peer_addr The peer/server address.
    /// @param peer_port The peer/server port.
    /// @param local_addr The local/client address.
    /// @param tls_context The TLS client context.
    /// @param secret The shared secret (must not be empty).
    /// @param timeout The timeout in seconds.
    /// @param deadtime The hold-down delay (0 means disabled).
    Server(const asiolink::IOAddress& peer_addr, const uint16_t peer_port,
           const asiolink::IOAddress& local_addr,
           const asiolink::TlsContextPtr& tls_context,
           const std::string& secret, const unsigned timeout,
           const unsigned deadtime = 0)
        : peer_addr_(peer_addr), peer_port_(peer_port),
          local_addr_(local_addr), tls_context_(tls_context), secret_(secret),
          timeout_(timeout), deadtime_(deadtime),
          deadtime_end_(std::chrono::steady_clock::now()),
          mutex_(new std::mutex) {

        // Extra checks.
        setLocalAddress(local_addr);
        setSecret(secret);
        setTimeout(timeout);
    }

    /// @brief Destructor.
    virtual ~Server();

    /// @brief Get peer address.
    ///
    /// @return the peer address.
    asiolink::IOAddress getPeerAddress() const {
        return (peer_addr_);
    }

    /// @brief Get peer port.
    ///
    /// @return the peer port.
    uint16_t getPeerPort() const {
        return (peer_port_);
    }

    /// @brief Set peer port.
    ///
    /// @param peer_port new peer port.
    void setPeerPort(const uint16_t peer_port) {
        peer_port_ = peer_port;
    }

    /// @brief Get local address.
    ///
    /// @return the local address.
    asiolink::IOAddress getLocalAddress() const {
        return (local_addr_);
    }

    /// @brief Get TLS context.
    ///
    /// @return the TLS context.
    asiolink::TlsContextPtr getTlsContext() const {
        return (tls_context_);
    }

    /// @brief Get secret.
    ///
    /// @return the secret.
    std::string getSecret() const {
        return (secret_);
    }

    /// @brief Set secret.
    ///
    /// @param secret new secret (must not be empty).
    void setSecret(const std::string& secret);

    /// @brief Set local address.
    ///
    /// @param local_addr new local address.
    void setLocalAddress(const asiolink::IOAddress& local_addr);

    /// @brief Get timeout.
    ///
    /// @return the timeout in seconds.
    unsigned getTimeout() const {
        return (timeout_);
    }

    /// @brief Set timeout.
    ///
    /// @param timeout new timeout in seconds.
    void setTimeout(const unsigned timeout);

    /// @brief Get deadtime.
    ///
    /// @return the hold-down delay.
    unsigned getDeadtime() const {
        return (deadtime_);
    }

    /// @brief Set deadtime.
    void setDeadtime(const unsigned deadtime) {
        if (deadtime == 0) {
            deadtime_end_ = std::chrono::steady_clock::now();
        }
        deadtime_ = deadtime;

    }

    /// @brief Get deadtime end.
    ///
    /// @return the date of the end of hold-down.
    std::chrono::steady_clock::time_point getDeadtimeEnd() const;

    /// @brief Set deadtime end.
    ///
    /// @param deadtime_end new date of the end of hold-down.
    void setDeadtimeEnd(const std::chrono::steady_clock::time_point& deadtime_end);

    /// @brief Unparse server.
    ///
    /// @return a pointer to unparsed server.
    data::ElementPtr toElement() const override;

protected:
    /// @brief Peer address.
    const asiolink::IOAddress peer_addr_;

    /// @brief Peer port.
    uint16_t peer_port_;

    /// @brief Local address.
    asiolink::IOAddress local_addr_;

    /// @brief TLS context.
    asiolink::TlsContextPtr tls_context_;

    /// @brief Secret.
    std::string secret_;

    /// @brief Timeout.
    unsigned timeout_;

    /// @brief Deadtime i.e. hold-down delay.
    unsigned deadtime_;

    /// @brief Deadtime end i.e. date of hold-down end.
    ///
    /// @note This member is the only state member.
    std::chrono::steady_clock::time_point deadtime_end_;

    /// @brief Mutex to protect the state.
    boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Type of shared pointers to a RADIUS server object.
typedef boost::shared_ptr<Server> ServerPtr;

/// @brief Type of RADIUS server collection.
typedef std::vector<ServerPtr> Servers;

} // end of namespace isc::radius
} // end of namespace isc

#endif
