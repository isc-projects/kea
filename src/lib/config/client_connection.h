// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <asiolink/io_service.h>
#include <cc/json_feed.h>
#include <boost/shared_ptr.hpp>
#include <functional>

namespace isc {
namespace config {

class ClientConnectionImpl;

/// @brief Represents client side connection over the unix domain socket.
///
/// This class represents a client side connection between the controlling
/// client and the server exposing control API over a unix domain socket.
/// In particular, this class is used by the Kea Control Agent to establish
/// connections with respective Kea services to forward received commands.
/// As of Kea 1.2 the servers can handle a single connection at the time.
/// In the future, we're planning to support multiple simulatenous connections.
/// In this case, each connection will be handled by a unique instance of the
/// @ref ClientConnection class.
///
/// The @ref ClientConnection supports asynchronous connections. A caller
/// creates an instance of the @ref ClientConnection and calls
/// @ref ClientConnection::start to start asynchronous communication with
/// a remote server. The caller provides a pointer to the callback function
/// (handler) which will be called when the communication with the server
/// completes, i.e. the command is sent to the server and the response
/// from the server is received. If an error occurs, the callback is
/// invoked with an error code indicating a reason for the failure.
///
/// The documentation of the @ref ClientConnection::start explains the
/// sequence of operations performed by this class.
///
/// Even though the @ref ClientConnection is asynchronous in nature, it
/// can also be used in cases requiring synchronous communication. As it
/// has been already mentioned, the servers in Kea 1.2 do not support
/// multiple concurrent connections. The following pseudo code demonstrates
/// how to perform synchronous transaction using this class.
///
/// @code
/// IOService io_service;
/// ClientConnection conn(io_service);
/// bool cb_invoked = false;
/// conn.start(ClientConnection::SocketPath("/tmp/kea.sock"),
///            ClientConnection::ControlCommand(command),
///            [this, &cb_invoked](const boost::system::error_code& ec,
///                   const ConstJSONFeedPtr& feed) {
///                cb_invoked = true;
///                if (ec) {
///                    ... handle error here ...
///                } else {
///                    ... use feed to retrieve the response ...
///                }
///            }
/// );
/// while (!cb_invoked) {
///     io_service.run_one();
/// }
/// @endcode
///
class ClientConnection {
public:

    /// @name Structures used for strong typing.
    ///
    //@{

    /// @brief Encapsulates socket path.
    struct SocketPath {
        explicit SocketPath(const std::string& socket_path)
            : socket_path_(socket_path) { }

        std::string socket_path_;
    };

    /// @brief Encapsulates control command.
    struct ControlCommand {
        explicit ControlCommand(const std::string control_command)
            : control_command_(control_command) { }

        std::string control_command_;
    };

    /// @brief Encapsulates timeout value.
    struct Timeout {
        explicit Timeout(const long timeout)
            : timeout_(timeout) { }

        long timeout_;
    };

    //@}

    /// @brief Type of the callback invoked when the communication with
    /// the server is complete or an error has occurred.
    typedef std::function<void(const boost::system::error_code& ec,
                               const ConstJSONFeedPtr& feed)> Handler;

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service.
    explicit ClientConnection(asiolink::IOService& io_service);

    /// @brief Starts asynchronous transaction with a remote endpoint.
    ///
    /// Starts asynchronous connection with the remote endpoint. If the
    /// connection is successful, the control command is asynchronously
    /// sent to the remote endpoint. When the entire command has been sent,
    /// the response is read asynchronously, possibly in multiple chunks.
    ///
    /// The timeout is specified in milliseconds. The corresponding timer
    /// measures the connection idle time. If the transaction is progressing,
    /// the timer is updated accordingly. If the connection idle time is
    /// longer than the timeout value the connection is closed and the
    /// callback is called with the error code of
    /// @c boost::asio::error::timed_out.
    ///
    /// In other cases, the callback is called with the error code returned
    /// by the boost asynchronous operations. If the transaction is successful
    /// the 'success' status is indicated with the error code. In addition
    /// the instance of the @ref JSONFeed is returned to the caller. It can
    /// be used to retrieve parsed response from the server. Note that the
    /// response may still be malformed, even if no error is signalled in
    /// the handler. The @ref JSONFeed::toElement will return a parsing
    /// error if the JSON appears to be malformed.
    ///
    /// @param socket_path Path to the socket description that the server
    /// is bound to.
    /// @param command Control command to be sent to the server.
    /// @param handler Pointer to the user supplied callback function which
    /// should be invoked when transaction completes or when an error has
    /// occurred during the transaction.
    /// @param timeout Connection timeout in milliseconds.
    void start(const SocketPath& socket_path, const ControlCommand& command,
               Handler handler, const Timeout& timeout = Timeout(5000));

private:

    /// @brief Pointer to the implementation.
    boost::shared_ptr<ClientConnectionImpl> impl_;

};

/// @brief Type of the pointer to the @ref ClientConnection object.
typedef boost::shared_ptr<ClientConnection> ClientConnectionPtr;

} // end of namespace config
} // end of namespace isc

#endif // CLIENT_CONNECTION_H
