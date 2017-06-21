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
#include <config/command_socket_factory.h>
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

class Connection : public boost::enable_shared_from_this<Connection> {
public:

    Connection(const boost::shared_ptr<UnixDomainSocket>& socket,
               ConnectionPool& connection_pool)
        : socket_(socket), connection_pool_(connection_pool),
          response_in_progress_(false) {
        isc::dhcp::IfaceMgr::instance().addExternalSocket(socket_->getNative(),
                                                          0);

    }

    void start() {
        socket_->asyncReceive(&buf_[0], sizeof(buf_),
                              boost::bind(&Connection::receiveHandler,
                                          shared_from_this(), _1, _2));


    }

    void stop() {
        if (!response_in_progress_) {
            socket_->close();
        }
    }

    void receiveHandler(const boost::system::error_code& ec,
                        size_t bytes_transferred);

private:

    boost::shared_ptr<UnixDomainSocket> socket_;

    std::array<char, 65535> buf_;

    ConnectionPool& connection_pool_;

    bool response_in_progress_;

};


typedef boost::shared_ptr<Connection> ConnectionPtr;

class ConnectionPool {
public:

    void start(const ConnectionPtr& connection) {
        connection->start();
        connections_.insert(connection);
    }

    void stop(const ConnectionPtr& connection) {
        connection->stop();
        connections_.erase(connection);
    }

    void stopAll() {
        for (auto conn = connections_.begin(); conn != connections_.end();
             ++conn) {
            (*conn)->stop();
        }
        connections_.clear();
    }

private:

    std::set<ConnectionPtr> connections_;

};


void
Connection::receiveHandler(const boost::system::error_code& ec,
                           size_t bytes_transferred) {
    if (ec) {
        return;
    }

    ConstElementPtr cmd, rsp;

    try {

        response_in_progress_ = true;

        // Try to interpret it as JSON.
        std::string sbuf(&buf_[0], bytes_transferred);
        cmd = Element::fromJSON(sbuf, true);

        // If successful, then process it as a command.
        rsp = CommandMgr::instance().processCommand(cmd);
    } catch (const Exception& ex) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR1).arg(ex.what());
        rsp = createAnswer(CONTROL_RESULT_ERROR, std::string(ex.what()));
    }

    if (!rsp) {
        response_in_progress_ = false;
        LOG_WARN(command_logger, COMMAND_RESPONSE_ERROR);
        return;
    }

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

    // Send the data back over socket.
    socket_->write(txt.c_str(), len);

    response_in_progress_ = false;


    isc::dhcp::IfaceMgr::instance().deleteExternalSocket(socket_->getNative());

    connection_pool_.stop(shared_from_this());
}

}

namespace isc {
namespace config {

class CommandMgrImpl {
public:

    CommandMgrImpl()
        : io_service_(), acceptor_(), socket_(), socket_name_(),
          connection_pool_() {
    }

    void openCommandSocket(const isc::data::ConstElementPtr& socket_info);

    void doAccept();

    IOServicePtr io_service_;

    boost::shared_ptr<UnixDomainSocketAcceptor> acceptor_;

    boost::shared_ptr<UnixDomainSocket> socket_;

    std::string socket_name_;

    ConnectionPool connection_pool_;
};

void
CommandMgrImpl::openCommandSocket(const isc::data::ConstElementPtr& socket_info) {
    socket_name_.clear();
    
    ConstElementPtr type = socket_info->get("socket-type");
    if (!type) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-type' parameter missing");
    }

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

    acceptor_.reset(new UnixDomainSocketAcceptor(*io_service_));
    UnixDomainSocketEndpoint endpoint(socket_name_);
    acceptor_->open(endpoint);
    acceptor_->bind(endpoint);
    acceptor_->listen();

    doAccept();

    // Install this socket in Interface Manager.
    isc::dhcp::IfaceMgr::instance().addExternalSocket(acceptor_->getNative(), 0);

}

void
CommandMgrImpl::doAccept() {
    socket_.reset(new UnixDomainSocket(*io_service_));
    acceptor_->asyncAccept(*socket_,
    [this](const boost::system::error_code& ec) {
        if (!ec) {
            ConnectionPtr connection(new Connection(socket_, connection_pool_));
            connection_pool_.start(connection);
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
    impl_->connection_pool_.stopAll();

    if (impl_->acceptor_) {
        isc::dhcp::IfaceMgr::instance().deleteExternalSocket(impl_->acceptor_->getNative());
        impl_->acceptor_->close();
        static_cast<void>(::remove(impl_->socket_name_.c_str()));
    }

/*    // Now let's close all existing connections that we may have.
    for (std::list<CommandSocketPtr>::iterator conn = connections_.begin();
         conn != connections_.end(); ++conn) {
        (*conn)->close();
    }
    connections_.clear(); */
}


void CommandMgr::addConnection(const CommandSocketPtr& conn) {
    connections_.push_back(conn);
}

bool CommandMgr::closeConnection(int fd) {

    // Let's iterate over all currently registered connections.
    for (std::list<CommandSocketPtr>::iterator conn = connections_.begin();
         conn != connections_.end(); ++conn) {

        // If found, close it.
        if ((*conn)->getFD() == fd) {
            (*conn)->close();
            connections_.erase(conn);
            return (true);
        }
    }

    return (false);
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
    closeCommandSocket();
    impl_->io_service_ = io_service;
}

void
CommandMgr::commandReader(int sockfd) {

    /// @todo: We do not handle commands that are larger than 64K.

    // We should not expect commands bigger than 64K.
    char buf[65536];
    memset(buf, 0, sizeof(buf));
    ConstElementPtr cmd, rsp;

    // Read incoming data.
    int rval = read(sockfd, buf, sizeof(buf));
    if (rval < 0) {
        // Read failed
        LOG_ERROR(command_logger, COMMAND_SOCKET_READ_FAIL).arg(rval).arg(sockfd);

        /// @todo: Should we close the connection, similar to what is already
        /// being done for rval == 0?
        return;
    } else if (rval == 0) {

        // Remove it from the active connections list.
        instance().closeConnection(sockfd);

        return;
    }

    // Duplicate the connection's socket in the event, the command causes the
    // channel to close (like a reconfig).  This permits us to always have
    // a socket on which to respond. If for some reason  we can't fall back
    // to the connection socket.
    int rsp_fd = dup(sockfd);
    if (rsp_fd < 0 ) {
        // Highly unlikely
        const char* errmsg = strerror(errno);
        LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_DUP_WARN)
                  .arg(errmsg);
        rsp_fd = sockfd;
    }

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_READ).arg(rval).arg(sockfd);

    // Ok, we received something. Let's see if we can make any sense of it.
    try {

        // Try to interpret it as JSON.
        std::string sbuf(buf, static_cast<size_t>(rval));
        cmd = Element::fromJSON(sbuf, true);

        // If successful, then process it as a command.
        rsp = CommandMgr::instance().processCommand(cmd);
    } catch (const Exception& ex) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR1).arg(ex.what());
        rsp = createAnswer(CONTROL_RESULT_ERROR, std::string(ex.what()));
    }

    if (!rsp) {
        LOG_WARN(command_logger, COMMAND_RESPONSE_ERROR);
        // Only close the duped socket if it's different (should be)
        if (rsp_fd != sockfd) {
            close(rsp_fd);
        }

        return;
    }

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

    // Send the data back over socket.
    rval = write(rsp_fd, txt.c_str(), len);
    int saverr = errno;

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_WRITE).arg(len).arg(sockfd);

    if (rval < 0) {
        // Response transmission failed. Since the response failed, it doesn't
        // make sense to send any status codes. Let's log it and be done with
        // it.
        LOG_ERROR(command_logger, COMMAND_SOCKET_WRITE_FAIL)
                  .arg(len).arg(sockfd).arg(strerror(saverr));
    }

    // Only close the duped socket if it's different (should be)
    if (rsp_fd != sockfd) {
        close(rsp_fd);
    }
}

}; // end of isc::config
}; // end of isc
