// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/unix_domain_socket.h>
#include <asiolink/unix_domain_socket_acceptor.h>
#include <asiolink/unix_domain_socket_endpoint.h>
#include <config/command_mgr.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <cc/json_feed.h>
#include <dhcp/iface_mgr.h>
#include <config/config_log.h>
#include <config/timeouts.h>
#include <util/watch_socket.h>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <array>
#include <unistd.h>
#include <sys/file.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;

namespace {

/// @brief Maximum size of the data chunk sent/received over the socket.
const size_t BUF_SIZE = 32768;

class ConnectionPool;

/// @brief Represents a single connection over control socket.
///
/// An instance of this object is created when the @c CommandMgr acceptor
/// receives new connection from a controlling client.
class Connection : public boost::enable_shared_from_this<Connection> {
public:

    /// @brief Constructor.
    ///
    /// This constructor registers a socket of this connection in the Interface
    /// Manager to cause the blocking call to @c select() to return as soon as
    /// a transmission over the control socket is received.
    ///
    /// It installs two external sockets on the @IfaceMgr to break synchronous
    /// calls to @select(). The @c WatchSocket is used for send operations
    /// over the connection. The native socket is used for signaling reads
    /// over the connection.
    ///
    /// @param io_service IOService object used to handle the asio operations
    /// @param socket Pointer to the object representing a socket which is used
    /// for data transmission.
    /// @param connection_pool Reference to the connection pool to which this
    /// connection belongs.
    /// @param timeout Connection timeout (in seconds).
    Connection(const IOServicePtr& io_service,
               const boost::shared_ptr<UnixDomainSocket>& socket,
               ConnectionPool& connection_pool,
               const long timeout)
        : socket_(socket), timeout_timer_(*io_service), timeout_(timeout),
          buf_(), response_(), connection_pool_(connection_pool), feed_(),
          response_in_progress_(false), watch_socket_(new util::WatchSocket()) {

        LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_CONNECTION_OPENED)
            .arg(socket_->getNative());

        // Callback value of 0 is used to indicate that callback function is
        // not installed.
        isc::dhcp::IfaceMgr::instance().addExternalSocket(watch_socket_->getSelectFd(), 0);
        isc::dhcp::IfaceMgr::instance().addExternalSocket(socket_->getNative(), 0);

        // Initialize state model for receiving and preparsing commands.
        feed_.initModel();

        // Start timer for detecting timeouts.
        scheduleTimer();
    }

    /// @brief Destructor.
    ///
    /// Cancels timeout timer if one is scheduled.
    ~Connection() {
        timeout_timer_.cancel();
    }

    /// @brief This method schedules timer or reschedules existing timer.
    void scheduleTimer() {
        timeout_timer_.setup(boost::bind(&Connection::timeoutHandler, this),
                             timeout_, IntervalTimer::ONE_SHOT);
    }

    /// @brief Close current connection.
    ///
    /// Connection is not closed if the invocation of this method is a result of
    /// server reconfiguration. The connection will be closed once a response is
    /// sent to the client. Closing a socket during processing a request would
    /// cause the server to not send a response to the client.
    void stop() {
        if (!response_in_progress_) {
            LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_CONNECTION_CLOSED)
                .arg(socket_->getNative());

            isc::dhcp::IfaceMgr::instance().deleteExternalSocket(watch_socket_->getSelectFd());
            isc::dhcp::IfaceMgr::instance().deleteExternalSocket(socket_->getNative());

            // Close watch socket and log errors if occur.
            std::string watch_error;
            if (!watch_socket_->closeSocket(watch_error)) {
                LOG_ERROR(command_logger, COMMAND_WATCH_SOCKET_CLOSE_ERROR)
                    .arg(watch_error);
            }

            socket_->close();
            timeout_timer_.cancel();
        }
    }

    /// @brief Gracefully terminates current connection.
    ///
    /// This method should be called prior to closing the socket to initiate
    /// graceful shutdown.
    void terminate();

    /// @brief Start asynchronous read over the unix domain socket.
    ///
    /// This method doesn't block. Once the transmission is received over the
    /// socket, the @c Connection::receiveHandler callback is invoked to
    /// process received data.
    void doReceive() {
        socket_->asyncReceive(&buf_[0], sizeof(buf_),
                              boost::bind(&Connection::receiveHandler,
                                          shared_from_this(), _1, _2));
    }

    /// @brief Starts asynchronous send over the unix domain socket.
    ///
    /// This method doesn't block. Once the send operation (that covers the whole
    /// data if it's small or first BUF_SIZE bytes if its large) is completed, the
    /// @c Connection::sendHandler callback is invoked. That handler will either
    /// close the connection gracefully if all data has been sent, or will
    /// call @ref doSend() again to send the next chunk of data.
    void doSend() {
        size_t chunk_size = (response_.size() < BUF_SIZE) ? response_.size() : BUF_SIZE;
        socket_->asyncSend(&response_[0], chunk_size,
           boost::bind(&Connection::sendHandler, shared_from_this(), _1, _2));

        // Asynchronous send has been scheduled and we need to indicate this
        // to break the synchronous select(). The handler should clear this
        // status when invoked.
        try {
            watch_socket_->markReady();

        } catch (const std::exception& ex) {
            LOG_ERROR(command_logger, COMMAND_WATCH_SOCKET_MARK_READY_ERROR)
                .arg(ex.what());
        }
    }

    /// @brief Handler invoked when the data is received over the control
    /// socket.
    ///
    /// It collects received data into the @c isc::config::JSONFeed object and
    /// schedules additional asynchronous read of data if this object signals
    /// that command is incomplete. When the entire command is received, the
    /// handler processes this command and asynchronously responds to the
    /// controlling client.
    //
    ///
    /// @param ec Error code.
    /// @param bytes_transferred Number of bytes received.
    void receiveHandler(const boost::system::error_code& ec,
                        size_t bytes_transferred);


    /// @brief Handler invoked when the data is sent over the control socket.
    ///
    /// If there are still data to be sent, another asynchronous send is
    /// scheduled. When the entire command is sent, the connection is shutdown
    /// and closed.
    ///
    /// @param ec Error code.
    /// @param bytes_transferred Number of bytes sent.
    void sendHandler(const boost::system::error_code& ec,
                     size_t bytes_transferred);

    /// @brief Handler invoked when timeout has occurred.
    ///
    /// Asynchronously sends a response to the client indicating that the
    /// timeout has occurred.
    void timeoutHandler();

private:

    /// @brief Pointer to the socket used for transmission.
    boost::shared_ptr<UnixDomainSocket> socket_;

    /// @brief Interval timer used to detect connection timeouts.
    IntervalTimer timeout_timer_;

    /// @brief Connection timeout (in milliseconds)
    long timeout_;

    /// @brief Buffer used for received data.
    std::array<char, BUF_SIZE> buf_;

    /// @brief Response created by the server.
    std::string response_;

    /// @brief Reference to the pool of connections.
    ConnectionPool& connection_pool_;

    /// @brief State model used to receive data over the connection and detect
    /// when the command ends.
    JSONFeed feed_;

    /// @brief Boolean flag indicating if the request to stop connection is a
    /// result of server reconfiguration.
    bool response_in_progress_;

    /// @brief Pointer to watch socket instance used to signal that the socket
    /// is ready for read or write.
    util::WatchSocketPtr watch_socket_;
};

/// @brief Pointer to the @c Connection.
typedef boost::shared_ptr<Connection> ConnectionPtr;

/// @brief Holds all open connections.
class ConnectionPool {
public:

    /// @brief Starts new connection.
    ///
    /// @param connection Pointer to the new connection object.
    void start(const ConnectionPtr& connection) {
        connection->doReceive();
        connections_.insert(connection);
    }

    /// @brief Stops running connection.
    ///
    /// @param connection Pointer to the new connection object.
    void stop(const ConnectionPtr& connection) {
        try {
            connection->stop();
            connections_.erase(connection);
        } catch (const std::exception& ex) {
            LOG_ERROR(command_logger, COMMAND_SOCKET_CONNECTION_CLOSE_FAIL)
                .arg(ex.what());
        }
    }

    /// @brief Stops all connections which are allowed to stop.
    void stopAll() {
        for (auto conn = connections_.begin(); conn != connections_.end();
             ++conn) {
            (*conn)->stop();
        }
        connections_.clear();
    }

private:

    /// @brief Pool of connections.
    std::set<ConnectionPtr> connections_;

};

void
Connection::terminate() {
    try {
        socket_->shutdown();

    } catch (const std::exception& ex) {
        LOG_ERROR(command_logger, COMMAND_SOCKET_CONNECTION_SHUTDOWN_FAIL)
            .arg(ex.what());
    }
}

void
Connection::receiveHandler(const boost::system::error_code& ec,
                           size_t bytes_transferred) {
    if (ec) {
        if (ec.value() == boost::asio::error::eof) {
            std::stringstream os;
            if (feed_.getProcessedText().empty()) {
               os << "no input data to discard";
            }
            else {
               os << "discarding partial command of "
                  << feed_.getProcessedText().size() << " bytes";
            }

            // Foreign host has closed the connection. We should remove it from the
            // connection pool.
            LOG_INFO(command_logger, COMMAND_SOCKET_CLOSED_BY_FOREIGN_HOST)
                .arg(socket_->getNative()).arg(os.str());
        } else if (ec.value() != boost::asio::error::operation_aborted) {
            LOG_ERROR(command_logger, COMMAND_SOCKET_READ_FAIL)
                .arg(ec.value()).arg(socket_->getNative());
        }

        connection_pool_.stop(shared_from_this());
        return;

    } else if (bytes_transferred == 0) {
        // Nothing received. Close the connection.
        connection_pool_.stop(shared_from_this());
        return;
    }

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_READ)
        .arg(bytes_transferred).arg(socket_->getNative());

    // Reschedule the timer because the transaction is ongoing.
    scheduleTimer();

    ConstElementPtr rsp;

    try {
        // Received some data over the socket. Append them to the JSON feed
        // to see if we have reached the end of command.
        feed_.postBuffer(&buf_[0], bytes_transferred);
        feed_.poll();
        // If we haven't yet received the full command, continue receiving.
        if (feed_.needData()) {
            doReceive();
            return;
        }

        // Received entire command. Parse the command into JSON.
        if (feed_.feedOk()) {
            ConstElementPtr cmd = feed_.toElement();
            response_in_progress_ = true;

            // Cancel the timer to make sure that long lasting command
            // processing doesn't cause the timeout.
            timeout_timer_.cancel();

            // If successful, then process it as a command.
            rsp = CommandMgr::instance().processCommand(cmd);

            response_in_progress_ = false;

        } else {
            // Failed to parse command as JSON or process the received command.
            // This exception will be caught below and the error response will
            // be sent.
            isc_throw(BadValue, feed_.getErrorMessage());
        }

    } catch (const Exception& ex) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR1).arg(ex.what());
        rsp = createAnswer(CONTROL_RESULT_ERROR, std::string(ex.what()));
    }

    // No response generated. Connection will be closed.
    if (!rsp) {
        LOG_WARN(command_logger, COMMAND_RESPONSE_ERROR);
        rsp = createAnswer(CONTROL_RESULT_ERROR,
                           "internal server error: no response generated");

    } else {

        // Reschedule the timer as it may be either canceled or need to be
        // updated to not timeout before we manage to the send the reply.
        scheduleTimer();

        // Let's convert JSON response to text. Note that at this stage
        // the rsp pointer is always set.
        response_ = rsp->str();

        doSend();
        return;
    }

    // Close the connection if we have sent the entire response.
    connection_pool_.stop(shared_from_this());
}

void
Connection::sendHandler(const boost::system::error_code& ec,
                        size_t bytes_transferred) {
    // Clear the watch socket so as the future send operation can mark it
    // again to interrupt the synchronous select() call.
    try {
        watch_socket_->clearReady();

    } catch (const std::exception& ex) {
        LOG_ERROR(command_logger, COMMAND_WATCH_SOCKET_CLEAR_ERROR)
            .arg(ex.what());
    }

    if (ec) {
        // If an error occurred, log this error and stop the connection.
        if (ec.value() != boost::asio::error::operation_aborted) {
            LOG_ERROR(command_logger, COMMAND_SOCKET_WRITE_FAIL)
                .arg(socket_->getNative()).arg(ec.message());
        }

    } else {

        // Reschedule the timer because the transaction is ongoing.
        scheduleTimer();

        // No error. We are in a process of sending a response. Need to
        // remove the chunk that we have managed to sent with the previous
        // attempt.
        response_.erase(0, bytes_transferred);

        LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_WRITE)
            .arg(bytes_transferred).arg(response_.size())
            .arg(socket_->getNative());

        // Check if there is any data left to be sent and sent it.
        if (!response_.empty()) {
            doSend();
            return;
        }

        // Gracefully shutdown the connection and close the socket if
        // we have sent the whole response.
        terminate();
    }

    // All data sent or an error has occurred. Close the connection.
    connection_pool_.stop(shared_from_this());
}

void
Connection::timeoutHandler() {
    LOG_INFO(command_logger, COMMAND_SOCKET_CONNECTION_TIMEOUT)
        .arg(socket_->getNative());

    try {
        socket_->cancel();

    } catch (const std::exception& ex) {
        LOG_ERROR(command_logger, COMMAND_SOCKET_CONNECTION_CANCEL_FAIL)
            .arg(socket_->getNative())
            .arg(ex.what());
    }

    std::stringstream os;
    os << "Connection over control channel timed out";
    if (!feed_.getProcessedText().empty()) {
        os << ", discarded partial command of "
           << feed_.getProcessedText().size() << " bytes";
    }

    ConstElementPtr rsp = createAnswer(CONTROL_RESULT_ERROR, os.str());
    response_ = rsp->str();
    doSend();
}


}

namespace isc {
namespace config {

/// @brief Implementation of the @c CommandMgr.
class CommandMgrImpl {
public:

    /// @brief Constructor.
    CommandMgrImpl()
        : io_service_(), acceptor_(), socket_(), socket_name_(),
          connection_pool_(), timeout_(TIMEOUT_DHCP_SERVER_RECEIVE_COMMAND) {
    }

    /// @brief Opens acceptor service allowing the control clients to connect.
    ///
    /// @param socket_info Configuration information for the control socket.
    /// @throw BadSocketInfo When socket configuration is invalid.
    /// @throw SocketError When socket operation fails.
    void openCommandSocket(const isc::data::ConstElementPtr& socket_info);

    /// @brief Asynchronously accepts next connection.
    void doAccept();

    /// @brief Returns the lock file name
    std::string getLockName() {
        return (std::string(socket_name_ + ".lock"));
    }

    /// @brief Pointer to the IO service used by the server process for running
    /// asynchronous tasks.
    IOServicePtr io_service_;

    /// @brief Pointer to the acceptor service.
    boost::shared_ptr<UnixDomainSocketAcceptor> acceptor_;

    /// @brief Pointer to the socket into which the new connection is accepted.
    boost::shared_ptr<UnixDomainSocket> socket_;

    /// @brief Path to the unix domain socket descriptor.
    ///
    /// This is used to remove the socket file once the connection terminates.
    std::string socket_name_;

    /// @brief Pool of connections.
    ConnectionPool connection_pool_;

    /// @brief Connection timeout
    long timeout_;
};

void
CommandMgrImpl::openCommandSocket(const isc::data::ConstElementPtr& socket_info) {
    socket_name_.clear();

    if(!socket_info) {
        isc_throw(BadSocketInfo, "Missing socket_info parameters, can't create socket.");
    }

    ConstElementPtr type = socket_info->get("socket-type");
    if (!type) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-type' parameter missing");
    }

    // Only supporting unix sockets right now.
    if (type->stringValue() != "unix") {
        isc_throw(BadSocketInfo, "Invalid 'socket-type' parameter value "
                  << type->stringValue());
    }

    // UNIX socket is requested. It takes one parameter: socket-name that
    // specifies UNIX path of the socket.
    ConstElementPtr name = socket_info->get("socket-name");
    if (!name) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-name' parameter missing");
    }

    if (name->getType() != Element::string) {
        isc_throw(BadSocketInfo, "'socket-name' parameter expected to be a string");
    }

    socket_name_ = name->stringValue();

    // First let's open lock file.
    std::string lock_name = getLockName();
    int lock_fd = open(lock_name.c_str(), O_RDONLY | O_CREAT, 0600);
    if (lock_fd == -1) {
        std::string errmsg = strerror(errno);
        isc_throw(SocketError, "cannot create socket lockfile, "
                  << lock_name  << ", : " << errmsg);
    }

    // Try to acquire lock. If we can't somebody else is actively
    // using it.
    int ret = flock(lock_fd, LOCK_EX | LOCK_NB);
    if (ret != 0) {
        std::string errmsg = strerror(errno);
        isc_throw(SocketError, "cannot lock socket lockfile, "
                  << lock_name  << ", : " << errmsg);
    }

    // We have the lock, so let's remove the pre-existing socket
    // file if it exists.
    static_cast<void>(::remove(socket_name_.c_str()));

    LOG_INFO(command_logger, COMMAND_ACCEPTOR_START)
        .arg(socket_name_);

    try {
        // Start asynchronous acceptor service.
        acceptor_.reset(new UnixDomainSocketAcceptor(*io_service_));
        UnixDomainSocketEndpoint endpoint(socket_name_);
        acceptor_->open(endpoint);
        acceptor_->bind(endpoint);
        acceptor_->listen();
        // Install this socket in Interface Manager.
        isc::dhcp::IfaceMgr::instance().addExternalSocket(acceptor_->getNative(), 0);

        doAccept();

    } catch (const std::exception& ex) {
        isc_throw(SocketError, ex.what());
    }
}

void
CommandMgrImpl::doAccept() {
    // Create a socket into which the acceptor will accept new connection.
    socket_.reset(new UnixDomainSocket(*io_service_));
    acceptor_->asyncAccept(*socket_, [this](const boost::system::error_code& ec) {
        if (!ec) {
            // New connection is arriving. Start asynchronous transmission.
            ConnectionPtr connection(new Connection(io_service_, socket_,
                                                    connection_pool_,
                                                    timeout_));
            connection_pool_.start(connection);

        } else if (ec.value() != boost::asio::error::operation_aborted) {
            LOG_ERROR(command_logger, COMMAND_SOCKET_ACCEPT_FAIL)
                .arg(acceptor_->getNative()).arg(ec.message());
        }

        // Unless we're stopping the service, start accepting connections again.
        if (ec.value() != boost::asio::error::operation_aborted) {
            doAccept();
        }
    });
}

CommandMgr::CommandMgr()
    : HookedCommandMgr(), impl_(new CommandMgrImpl()) {
}

void
CommandMgr::openCommandSocket(const isc::data::ConstElementPtr& socket_info) {
    impl_->openCommandSocket(socket_info);
}

void CommandMgr::closeCommandSocket() {
    // Close acceptor if the acceptor is open.
    if (impl_->acceptor_ && impl_->acceptor_->isOpen()) {
        isc::dhcp::IfaceMgr::instance().deleteExternalSocket(impl_->acceptor_->getNative());
        impl_->acceptor_->close();
        static_cast<void>(::remove(impl_->socket_name_.c_str()));
        static_cast<void>(::remove(impl_->getLockName().c_str()));
    }

    // Stop all connections which can be closed. The only connection that won't
    // be closed is the one over which we have received a request to reconfigure
    // the server. This connection will be held until the CommandMgr responds to
    // such request.
    impl_->connection_pool_.stopAll();
}

int
CommandMgr::getControlSocketFD() {
    return (impl_->acceptor_ ? impl_->acceptor_->getNative() : -1);
}


CommandMgr&
CommandMgr::instance() {
    static CommandMgr cmd_mgr;
    return (cmd_mgr);
}

void
CommandMgr::setIOService(const IOServicePtr& io_service) {
    impl_->io_service_ = io_service;
}

void
CommandMgr::setConnectionTimeout(const long timeout) {
    impl_->timeout_ = timeout;
}


}; // end of isc::config
}; // end of isc
