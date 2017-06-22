// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/unix_domain_socket.h>
#include <asiolink/unix_domain_socket_acceptor.h>
#include <asiolink/unix_domain_socket_endpoint.h>
#include <config/command_mgr.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <dhcp/iface_mgr.h>
#include <config/config_log.h>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <array>
#include <unistd.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;

namespace {

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
    Connection(const boost::shared_ptr<UnixDomainSocket>& socket,
               ConnectionPool& connection_pool)
        : socket_(socket), connection_pool_(connection_pool),
          response_in_progress_(false) {
        // Callback value of 0 is used to indicate that callback function is
        // not installed.
        isc::dhcp::IfaceMgr::instance().addExternalSocket(socket_->getNative(), 0);
    }

    /// @brief Start asynchronous read over the unix domain socket.
    ///
    /// This method doesn't block. Once the transmission is received over the
    /// socket, the @c Connection::receiveHandler callback is invoked to
    /// process received data.
    void start() {
        socket_->asyncReceive(&buf_[0], sizeof(buf_),
                              boost::bind(&Connection::receiveHandler,
                                          shared_from_this(), _1, _2));


    }

    /// @brief Close current connection.
    ///
    /// Connection is not closed if the invocation of this method is a result of
    /// server reconfiguration. The connection will be closed once a response is
    /// sent to the client. Closing a socket during processing a request would
    /// cause the server to not send a response to the client.
    void stop() {
        if (!response_in_progress_) {
            LOG_INFO(command_logger, COMMAND_SOCKET_CONNECTION_CLOSED)
                .arg(socket_->getNative());

            isc::dhcp::IfaceMgr::instance().deleteExternalSocket(socket_->getNative());
            socket_->close();
        }
    }

    /// @brief Handler invoked when the data is received over the control
    /// socket.
    ///
    /// @param ec Error code.
    /// @param bytes_transferred Number of bytes received.
    void receiveHandler(const boost::system::error_code& ec,
                        size_t bytes_transferred);

private:

    /// @brief Pointer to the socket used for transmission.
    boost::shared_ptr<UnixDomainSocket> socket_;

    /// @brief Buffer used for received data.
    std::array<char, 65535> buf_;

    /// @brief Reference to the pool of connections.
    ConnectionPool& connection_pool_;

    /// @brief Boolean flag indicating if the request to stop connection is a
    /// result of server reconfiguration.
    bool response_in_progress_;

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
        connection->start();
        connections_.insert(connection);
    }

    /// @brief Stops running connection.
    ///
    /// @param connection Pointer to the new connection object.
    void stop(const ConnectionPtr& connection) {
        connection->stop();
        connections_.erase(connection);
    }

    /// @brief Stops all connections which are allowed to stop.
    void stopAll() {
        for (auto conn = connections_.begin(); conn != connections_.end();
             ++conn) {
            (*conn)->stop();
        }
        connections_.clear();
    }

    size_t getConnectionsNum() const {
        return (connections_.size());
    }

private:

    /// @brief Pool of connections.
    std::set<ConnectionPtr> connections_;

};


void
Connection::receiveHandler(const boost::system::error_code& ec,
                           size_t bytes_transferred) {
    if (ec) {
        if (ec.value() == boost::asio::error::eof) {
            // Foreign host has closed the connection. We should remove it from the
            // connection pool.
            LOG_INFO(command_logger, COMMAND_SOCKET_CLOSED_BY_FOREIGN_HOST)
                .arg(socket_->getNative());
            connection_pool_.stop(shared_from_this());

        } else if (ec.value() != boost::asio::error::operation_aborted) {
            LOG_ERROR(command_logger, COMMAND_SOCKET_READ_FAIL)
                .arg(ec.value()).arg(socket_->getNative());
        }

        /// @todo: Should we close the connection, similar to what is already
        /// being done for bytes_transferred == 0.
        return;

    } else if (bytes_transferred == 0) {
        // Nothing received. Close the connection.
        connection_pool_.stop(shared_from_this());
        return;
    }

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_READ)
        .arg(bytes_transferred).arg(socket_->getNative());

    ConstElementPtr cmd, rsp;

    try {

        // Try to interpret it as JSON.
        std::string sbuf(&buf_[0], bytes_transferred);
        cmd = Element::fromJSON(sbuf, true);

        response_in_progress_ = true;

        // If successful, then process it as a command.
        rsp = CommandMgr::instance().processCommand(cmd);

        response_in_progress_ = false;


    } catch (const Exception& ex) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR1).arg(ex.what());
        rsp = createAnswer(CONTROL_RESULT_ERROR, std::string(ex.what()));
    }

    // No response generated. Connection will be closed.
    if (!rsp) {
        LOG_WARN(command_logger, COMMAND_RESPONSE_ERROR);

    } else {

        // Let's convert JSON response to text. Note that at this stage
        // the rsp pointer is always set.
        std::string txt = rsp->str();
        size_t len = txt.length();
        if (len > 65535) {
            // Hmm, our response is too large. Let's send the first
            // 64KB and hope for the best.
            LOG_ERROR(command_logger, COMMAND_SOCKET_RESPONSE_TOOLARGE).arg(len);

            len = 65535;
        }

        try {
            // Send the data back over socket.
            socket_->write(txt.c_str(), len);

        } catch (const std::exception& ex) {
            // Response transmission failed. Since the response failed, it doesn't
            // make sense to send any status codes. Let's log it and be done with
            // it.
            LOG_ERROR(command_logger, COMMAND_SOCKET_WRITE_FAIL)
                .arg(len).arg(socket_->getNative()).arg(ex.what());
        }
    }

    connection_pool_.stop(shared_from_this());
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
          connection_pool_() {
    }

    /// @brief Opens acceptor service allowing the control clients to connect.
    ///
    /// @param socket_info Configuration information for the control socket.
    /// @throw BadSocketInfo When socket configuration is invalid.
    /// @throw SocketError When socket operation fails.
    void openCommandSocket(const isc::data::ConstElementPtr& socket_info);

    /// @brief Asynchronously accepts next connection.
    void doAccept();

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
            ConnectionPtr connection(new Connection(socket_, connection_pool_));
            connection_pool_.start(connection);
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

}; // end of isc::config
}; // end of isc
