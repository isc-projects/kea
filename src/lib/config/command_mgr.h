// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_MGR_H
#define COMMAND_MGR_H

#include <cc/data.h>
#include <config/hooked_command_mgr.h>
#include <config/command_socket.h>
#include <boost/noncopyable.hpp>
#include <list>

namespace isc {
namespace config {

/// @brief Commands Manager implementation for the Kea servers.
///
/// This class extends @ref BaseCommandMgr with the ability to receive and
/// respond to commands over unix domain sockets.
class CommandMgr : public HookedCommandMgr, public boost::noncopyable {
public:

    /// @brief CommandMgr is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of the manager
    static CommandMgr& instance();

    /// @brief Opens control socket with parameters specified in socket_info
    ///
    /// Currently supported types are:
    /// - unix (required parameters: socket-type: unix, socket-name:/unix/path)
    ///
    /// This method will close previously open command socket (if exists).
    ///
    /// @throw CommandSocketError if socket creation fails.
    /// @throw SocketError if command socket is already open.
    ///
    /// @param socket_info describes control socket parameters
    /// @return object representing a socket
    CommandSocketPtr
    openCommandSocket(const isc::data::ConstElementPtr& socket_info);

    /// @brief Shuts down any open control sockets
    void closeCommandSocket();

    /// @brief Reads data from a socket, parses as JSON command and processes it
    ///
    /// This method is used to handle traffic on connected socket. This callback
    /// is installed by the @c isc::config::UnixCommandSocket::receiveHandler
    /// (located in the src/lib/config/command_socket_factory.cc)
    /// once the incoming connection is accepted. If end-of-file is detected, this
    /// method will close the socket and will uninstall itself from
    /// @ref isc::dhcp::IfaceMgr.
    ///
    /// @param sockfd socket descriptor of a connected socket
    static void commandReader(int sockfd);

    /// @brief Adds an information about opened connection socket
    ///
    /// @param conn Connection socket to be stored
    void addConnection(const CommandSocketPtr& conn);

    /// @brief Closes connection with a specific socket descriptor
    ///
    /// @param fd socket descriptor
    /// @return true if closed successfully, false if not found
    bool closeConnection(int fd);

    /// @brief Returns control socket descriptor
    ///
    /// This method should be used only in tests.
    int getControlSocketFD() const {
        return (socket_->getFD());
    }

private:

    /// @brief Private constructor
    ///
    /// Registers internal 'list-commands' command.
    CommandMgr();

    /// @brief Control socket structure
    ///
    /// This is the socket that accepts incoming connections. There can be at
    /// most one (if command channel is configured).
    CommandSocketPtr socket_;

    /// @brief Sockets for open connections
    ///
    /// These are the sockets that are dedicated to handle a specific connection.
    /// Their number is equal to number of current control connections.
    std::list<CommandSocketPtr> connections_;
};

}; // end of isc::config namespace
}; // end of isc namespace

#endif
