// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config/command_mgr.h>
#include <config/command_socket_factory.h>
#include <cc/data.h>
#include <boost/bind.hpp>

namespace isc {
namespace config {

CommandMgr::CommandMgr() {
    registerCommand("list-commands",
        boost::bind(&CommandMgr::listCommandsHandler, this, _1, _2));
}

int CommandMgr::openCtrlSocket(const isc::data::ConstElementPtr& socket_info) {
    if (socket_info_) {
        isc_throw(SocketError, "There is already a control socket open");
    }

    socket_ = CommandSocketFactory::create(socket_info);
    socket_info_ = socket_info;

    /// @todo: install socket in IfaceMgr
    ///CommandSocketFactory::install(socket_, socket_info);
}

void CommandMgr::closeCtrlSocket() {
    if (socket_info_) {
        CommandSocketFactory::close(socket_, socket_info_);
        socket_ = 0;
        socket_info_.reset();
    }
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
}

void CommandMgr::deregisterAll() {
    handlers_.clear();
    registerCommand("list-commands",
        boost::bind(&CommandMgr::listCommandsHandler, this, _1, _2));
}

isc::data::ConstElementPtr
CommandMgr::processCommand(const isc::data::ConstElementPtr& cmd) {
    if (!cmd) {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Command processing failed: NULL command parameter"));
    }

    try {
        isc::data::ConstElementPtr arg;
        std::string name = parseCommand(arg, cmd);

        HandlerContainer::const_iterator it = handlers_.find(name);
        if (it == handlers_.end()) {
            // Ok, there's no such command.
            return (createAnswer(CONTROL_RESULT_ERROR,
                                 "'" + name + "' command not supported."));
        }

        // Call the actual handler and return whatever it returned
        return (it->second(name, arg));

    } catch (const Exception& e) {
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
