// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config/command_mgr.h>
#include <config/command_socket_factory.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <dhcp/iface_mgr.h>
#include <config/config_log.h>
#include <boost/bind.hpp>
#include <unistd.h>

using namespace isc::data;

namespace isc {
namespace config {

CommandMgr::CommandMgr()
    : HookedCommandMgr() {
}

CommandSocketPtr
CommandMgr::openCommandSocket(const isc::data::ConstElementPtr& socket_info) {
    if (socket_) {
        isc_throw(SocketError, "There is already a control socket open");
    }

    socket_ = CommandSocketFactory::create(socket_info);

    return (socket_);
}

void CommandMgr::closeCommandSocket() {
    // First, let's close the socket for incoming new connections.
    if (socket_) {
        socket_->close();
        socket_.reset();
    }

    // Now let's close all existing connections that we may have.
    for (std::list<CommandSocketPtr>::iterator conn = connections_.begin();
         conn != connections_.end(); ++conn) {
        (*conn)->close();
    }
    connections_.clear();
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

CommandMgr&
CommandMgr::instance() {
    static CommandMgr cmd_mgr;
    return (cmd_mgr);
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
