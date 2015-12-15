// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

using namespace isc::data;

namespace isc {
namespace config {

CommandMgr::CommandMgr() {
    registerCommand("list-commands",
        boost::bind(&CommandMgr::listCommandsHandler, this, _1, _2));
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

void CommandMgr::registerCommand(const std::string& cmd, CommandHandler handler) {

    if (!handler) {
        isc_throw(InvalidCommandHandler, "Specified command handler is NULL");
    }

    HandlerContainer::const_iterator it = handlers_.find(cmd);
    if (it != handlers_.end()) {
        isc_throw(InvalidCommandName, "Handler for command '" << cmd
                  << "' is already installed.");
    }

    handlers_.insert(make_pair(cmd, handler));

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_REGISTERED).arg(cmd);
}

void CommandMgr::deregisterCommand(const std::string& cmd) {
    if (cmd == "list-commands") {
        isc_throw(InvalidCommandName,
                  "Can't uninstall internal command 'list-commands'");
    }

    HandlerContainer::iterator it = handlers_.find(cmd);
    if (it == handlers_.end()) {
        isc_throw(InvalidCommandName, "Handler for command '" << cmd
                  << "' not found.");
    }
    handlers_.erase(it);

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_DEREGISTERED).arg(cmd);
}

void CommandMgr::deregisterAll() {

    // No need to log anything here. deregisterAll is not used in production
    // code, just in tests.
    handlers_.clear();
    registerCommand("list-commands",
        boost::bind(&CommandMgr::listCommandsHandler, this, _1, _2));
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

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_READ).arg(rval).arg(sockfd);

    // Ok, we received something. Let's see if we can make any sense of it.
    try {

        // Try to interpret it as JSON.
        cmd = Element::fromJSON(std::string(buf), true);

        // If successful, then process it as a command.
        rsp = CommandMgr::instance().processCommand(cmd);
    } catch (const Exception& ex) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR1).arg(ex.what());
        rsp = createAnswer(CONTROL_RESULT_ERROR, std::string(ex.what()));
    }

    if (!rsp) {
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
    rval = write(sockfd, txt.c_str(), len);

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_SOCKET_WRITE).arg(len).arg(sockfd);

    if (rval < 0) {
        // Response transmission failed. Since the response failed, it doesn't
        // make sense to send any status codes. Let's log it and be done with
        // it.
        LOG_ERROR(command_logger, COMMAND_SOCKET_WRITE_FAIL).arg(len).arg(sockfd);
    }
}

isc::data::ConstElementPtr
CommandMgr::processCommand(const isc::data::ConstElementPtr& cmd) {
    if (!cmd) {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Command processing failed: NULL command parameter"));
    }

    try {
        ConstElementPtr arg;
        std::string name = parseCommand(arg, cmd);

        LOG_INFO(command_logger, COMMAND_RECEIVED).arg(name);

        HandlerContainer::const_iterator it = handlers_.find(name);
        if (it == handlers_.end()) {
            // Ok, there's no such command.
            return (createAnswer(CONTROL_RESULT_ERROR,
                                 "'" + name + "' command not supported."));
        }

        // Call the actual handler and return whatever it returned
        return (it->second(name, arg));

    } catch (const Exception& e) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR2).arg(e.what());
        return (createAnswer(CONTROL_RESULT_ERROR,
                             std::string("Error during command processing:")
                             + e.what()));
    }
}

isc::data::ConstElementPtr
CommandMgr::listCommandsHandler(const std::string& name,
                                const isc::data::ConstElementPtr& params) {
    using namespace isc::data;
    ElementPtr commands = Element::createList();
    for (HandlerContainer::const_iterator it = handlers_.begin();
         it != handlers_.end(); ++it) {
        commands->add(Element::create(it->first));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS, commands));
}

}; // end of isc::config
}; // end of isc
