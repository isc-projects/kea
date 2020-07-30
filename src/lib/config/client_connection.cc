// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/unix_domain_socket.h>
#include <cc/json_feed.h>
#include <config/client_connection.h>
#include <boost/enable_shared_from_this.hpp>
#include <array>
#include <functional>

using namespace isc::asiolink;

namespace isc {
namespace config {

/// @brief Implementation of the @ref ClientConnection.
class ClientConnectionImpl : public boost::enable_shared_from_this<ClientConnectionImpl> {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Reference to the IO service.
    explicit ClientConnectionImpl(IOService& io_service);

    /// @brief This method schedules timer or reschedules existing timer.
    ///
    /// @param handler Pointer to the user supplied callback function which
    /// should be invoked when transaction completes or when an error has
    /// occurred during the transaction.
    void scheduleTimer(ClientConnection::Handler handler);

    /// @brief Starts asynchronous transaction with a remote endpoint.
    ///
    /// See @ref ClientConnection::start documentation for the details.
    ///
    /// @param socket_path Path to the socket description that the server
    /// is bound to.
    /// @param command Control command to be sent to the server.
    /// @param handler Pointer to the user supplied callback function which
    /// should be invoked when transaction completes or when an error has
    /// occurred during the transaction.
    /// @param timeout Connection timeout in milliseconds.
    void start(const ClientConnection::SocketPath& socket_path,
               const ClientConnection::ControlCommand& command,
               ClientConnection::Handler handler,
               const ClientConnection::Timeout& timeout);

    /// @brief Closes the socket.
    void stop();

    /// @brief Starts asynchronous send.
    ///
    /// This method may be called multiple times internally when the command
    /// is large and can't be sent all at once.
    ///
    /// @param buffer Pointer to the buffer holding input data.
    /// @param length Length of the data in the input buffer.
    /// @param handler User supplied callback invoked after the chunk of data
    /// has been sent.
    void doSend(const void* buffer, const size_t length,
                ClientConnection::Handler handler);

    /// @brief Starts asynchronous receive from the server.
    ///
    /// This method may be called multiple times internally if the response
    /// is large. The @ref JSONFeed instance is used to detect the boundaries
    /// of the command within the stream. Once the entire command has been
    /// received the user callback is invoked and the instance of the
    /// @ref JSONFeed is returned.
    ///
    /// @param handler User supplied callback.
    void doReceive(ClientConnection::Handler handler);

    /// @brief Terminates the connection and invokes a user callback indicating
    /// an error.
    ///
    /// @param ec Error code.
    /// @param handler User callback.
    void terminate(const boost::system::error_code& ec,
                   ClientConnection::Handler handler);

    /// @brief Callback invoked when the timeout occurs.
    ///
    /// It calls @ref terminate with the @c boost::asio::error::timed_out.
    void timeoutCallback(ClientConnection::Handler handler);

private:

    /// @brief Unix domain socket used for communication with a server.
    UnixDomainSocket socket_;

    /// @brief Pointer to the @ref JSONFeed holding a response.
    ///
    ///It may be a null pointer until some part of a response has been received.
    JSONFeedPtr feed_;

    /// @brief Holds the entire command being transmitted over the unix
    /// socket.
    std::string current_command_;

    /// @brief Buffer into which chunks of the response are received.
    std::array<char, 32768> read_buf_;

    /// @brief Instance of the interval timer protecting against timeouts.
    IntervalTimer timer_;

    /// @brief Timeout value used for the timer.
    long timeout_;
};

ClientConnectionImpl::ClientConnectionImpl(IOService& io_service)
    : socket_(io_service), feed_(), current_command_(), timer_(io_service),
      timeout_(0) {
}

void
ClientConnectionImpl::scheduleTimer(ClientConnection::Handler handler) {
    if (timeout_ > 0) {
        timer_.setup(std::bind(&ClientConnectionImpl::timeoutCallback,
                               this, handler),
                     timeout_, IntervalTimer::ONE_SHOT);
    }
}

void
ClientConnectionImpl::start(const ClientConnection::SocketPath& socket_path,
                            const ClientConnection::ControlCommand& command,
                            ClientConnection::Handler handler,
                            const ClientConnection::Timeout& timeout) {
    // Start the timer protecting against timeouts.
    timeout_ = timeout.timeout_;
    scheduleTimer(handler);

    // Store the command in the class member to make sure it is valid
    // the entire time.
    current_command_.assign(command.control_command_);

    // Pass self to lambda to make sure that the instance of this class
    // lives as long as the lambda is held for async connect.
    auto self(shared_from_this());
    // Start asynchronous connect. This will return immediately.
    socket_.asyncConnect(socket_path.socket_path_,
    [this, self, command, handler](const boost::system::error_code& ec) {
        // We failed to connect so we can't proceed. Simply clean up
        // and invoke the user callback to signal an error.
        if (ec) {
            // This doesn't throw.
            terminate(ec, handler);

        } else {
            // Connection successful. Transmit the command to the remote
            // endpoint asynchronously.
            doSend(current_command_.c_str(), current_command_.length(),
                   handler);
        }
    });
}

void
ClientConnectionImpl::doSend(const void* buffer, const size_t length,
                             ClientConnection::Handler handler) {
    // Pass self to lambda to make sure that the instance of this class
    // lives as long as the lambda is held for async send.
    auto self(shared_from_this());
    // Start asynchronous transmission of the command. This will return
    // immediately.
    socket_.asyncSend(buffer, length,
        [this, self, buffer, length, handler]
        (const boost::system::error_code& ec, size_t bytes_transferred) {
        // An error has occurred while sending. Close the connection and
        // signal an error.
        if (ec) {
            // This doesn't throw.
            terminate(ec, handler);

        } else {
            // Sending is in progress, so push back the timeout.
            scheduleTimer(handler);

            // If the number of bytes we have managed to send so far is
            // lower than the amount of data we're trying to send, we
            // have to schedule another send to deliver the rest of
            // the data.
            if (bytes_transferred < length) {
                doSend(static_cast<const char*>(buffer) + bytes_transferred,
                       length - bytes_transferred, handler);

            } else {
                // We have sent all the data. Start receiving a response.
                doReceive(handler);
            }
        }
    });
}

void
ClientConnectionImpl::doReceive(ClientConnection::Handler handler) {
    // Pass self to lambda to make sure that the instance of this class
    // lives as long as the lambda is held for async receive.
    auto self(shared_from_this());
    socket_.asyncReceive(&read_buf_[0], read_buf_.size(),
        [this, self, handler]
        (const boost::system::error_code& ec, size_t length) {
        // An error has occurred while receiving the data. Close the connection
        // and signal an error.
        if (ec) {
            // This doesn't throw.
            terminate(ec, handler);

        } else {
            // Receiving is in progress, so push back the timeout.
            scheduleTimer(handler);

            std::string x(&read_buf_[0], length);
            // Lazy initialization of the JSONFeed. The feed will be "parsing"
            // received JSON stream and will detect when the whole response
            // has been received.
            if (!feed_) {
                feed_.reset(new JSONFeed());
                feed_->initModel();
            }
            // Put everything we have received so far into the feed and process
            // the data.
            feed_->postBuffer(&read_buf_[0], length);
            feed_->poll();
            // If the feed indicates that only a part of the response has been
            // received, schedule another receive to get more data.
            if (feed_->needData()) {
                doReceive(handler);

            } else {
                // We have received the entire response, let's call the handler
                // and indicate success.
                terminate(ec, handler);
            }
        }
    });
}

void
ClientConnectionImpl::terminate(const boost::system::error_code& ec,
                                ClientConnection::Handler handler) {
    try {
        timer_.cancel();
        socket_.close();
        current_command_.clear();
        handler(ec, feed_);

    } catch (...) {
        // None of these operations should throw. In particular, the handler
        // should not throw but if it has been misimplemented, we want to make
        // sure we don't emit any exceptions from here.
    }
}

void
ClientConnectionImpl::timeoutCallback(ClientConnection::Handler handler) {
    // Timeout has occurred. The remote server didn't provide the entire
    // response within the given time frame. Let's close the connection
    // and signal the timeout.
    terminate(boost::asio::error::timed_out, handler);
}

ClientConnection::ClientConnection(asiolink::IOService& io_service)
    : impl_(new ClientConnectionImpl(io_service)) {
}

void
ClientConnection::start(const ClientConnection::SocketPath& socket_path,
                        const ClientConnection::ControlCommand& command,
                        ClientConnection::Handler handler,
                        const ClientConnection::Timeout& timeout) {
    impl_->start(socket_path, command, handler, timeout);
}


} // end of namespace config
} // end of namespace isc
