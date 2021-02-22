// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_SERVER_UNIX_SOCKET_H
#define TEST_SERVER_UNIX_SOCKET_H

#include <config.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <list>
#include <stdint.h>
#include <string>
#include <mutex>
#include <condition_variable>

namespace isc {
namespace asiolink {
namespace test {

class ConnectionPool;

/// @brief Provides unix domain socket functionality for unit tests.
///
/// This class represents a server side socket. It can be used to
/// test client's transmission over the unix domain socket. By default,
/// the server side socket echoes the client's message so the client's
/// message (prefixed with the word "received").
///
/// It is also possible to specify a custom response from the server
/// instead of echoing back the request.
///
/// It is possible to make multiple connections to the server side
/// socket simultaneously.
///
/// The test should perform IOService::run_one until it finds that
/// the number of responses sent by the server is greater than
/// expected. The number of responses sent so far can be retrieved
/// using @ref TestServerUnixSocket::getResponseNum.
///
/// This class uses @c shared_from_this() to pass its instance to the
/// @c std::bind function, thus the caller must store shared pointer
/// to this object.
class TestServerUnixSocket {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service.
    /// @param socket_file_path Socket file path.
    /// @param custom_response Custom response to be sent to the client.
    TestServerUnixSocket(IOService& io_service,
                         const std::string& socket_file_path,
                         const std::string& custom_response = "");

    /// @brief Destructor.
    ///
    /// Closes active connections.
    ~TestServerUnixSocket();

    /// @brief Starts timer for detecting test timeout.
    ///
    /// @param test_timeout Test timeout in milliseconds.
    void startTimer(const long test_timeout);

    /// @brief Cancels all asynchronous operations.
    void stopServer();

    /// @brief Generates response of a given length.
    ///
    /// Note: The response may be a few bytes larger than requested.
    ///
    /// @param response_size Desired response size.
    void generateCustomResponse(const uint64_t response_size);

    /// @brief Creates and binds server socket.
    ///
    /// @param use_thread Boolean value indicating if the IO service
    /// is running in thread.
    void bindServerSocket(const bool use_thread = false);

    /// @brief Server acceptor handler.
    ///
    /// @param ec Error code.
    void acceptHandler(const boost::system::error_code& ec);

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    void timeoutHandler();

    /// @brief Return number of responses sent so far to the clients.
    size_t getResponseNum() const;

    /// @brief Indicates if the server has been stopped.
    bool isStopped() {
        return (stopped_);
    }

    /// @brief Waits for the server signal that it is running.
    ///
    /// When the caller starts the service he indicates whether
    /// IO service will be running in thread or not. If threads
    /// are used the caller has to wait for the IO service to
    /// actually run. In such case this function should be invoked
    /// which waits for a posted callback to be executed. When this
    /// happens it means that IO service is running and the main
    /// thread can move forward.
    void waitForRunning();

private:

    /// @brief Asynchronously accept new connections.
    void accept();

    /// @brief Handler invoked to signal that server is running.
    ///
    /// This is used only when thread is used to run IO service.
    void signalRunning();

    /// @brief IO service used by the tests.
    IOService& io_service_;

    /// @brief Server endpoint.
    boost::asio::local::stream_protocol::endpoint server_endpoint_;
    /// @brief Server acceptor.
    boost::asio::local::stream_protocol::acceptor server_acceptor_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Holds custom response to be sent to the client.
    std::string custom_response_;

    /// @brief Pool of connections.
    boost::shared_ptr<ConnectionPool> connection_pool_;

    /// @brief Indicates if IO service has been stopped as a result of
    /// a timeout.
    bool stopped_;

    /// @brief Indicates if the server in a thread is running.
    bool running_;

    /// @brief Mutex used by the server.
    ///
    /// Mutex is used in situations when server's IO service is being run in a
    /// thread to synchronize this thread with a main thread using
    /// @ref signalRunning and @ref waitForRunning.
    std::mutex mutex_;

    /// @brief Conditional variable used by the server.
    ///
    /// Conditional variable is used in situations when server's IO service is
    /// being run in a thread to synchronize this thread with a main thread
    /// using @ref signalRunning and @ref waitForRunning.
    std::condition_variable condvar_;
};

/// @brief Pointer to the @ref TestServerUnixSocket.
typedef boost::shared_ptr<TestServerUnixSocket> TestServerUnixSocketPtr;

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc

#endif // TEST_SERVER_UNIX_SOCKET_H
