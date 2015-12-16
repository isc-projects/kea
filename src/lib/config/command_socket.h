// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_SOCKET_H
#define COMMAND_SOCKET_H

#include <cc/data.h>
#include <unistd.h>

namespace isc {
namespace config {

/// @brief An exception indicating that specified socket parameters are invalid
class BadSocketInfo : public Exception {
public:
    BadSocketInfo(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief An exception indicating a problem with socket operation
class SocketError : public Exception {
public:
    SocketError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Abstract base class that represents an open command socket
///
/// Derived classes are expected to handle specific socket types (e.g. UNIX
/// or https).
///
/// For derived classes, see @ref UnixCommandSocket for a socket that
/// accepts connections over UNIX socket and @ref ConnectionSocket that
/// handles established connections (currently over UNIX sockets, but
/// should be generic).
class CommandSocket {
public:
    /// @brief Method used to handle incoming data
    ///
    /// This may be registered in @ref isc::dhcp::IfaceMgr
    virtual void receiveHandler() = 0;

    /// @brief General method for closing socket.
    ///
    /// This is the default implementation that simply closes
    /// the socket. Derived classes may do additional steps
    /// to terminate the connection.
    virtual void close() {
        ::close(sockfd_);
    }

    /// @brief Virtual destructor.
    virtual ~CommandSocket() {
        close();
    }

    /// @brief Returns socket descriptor.
    int getFD() const {
        return (sockfd_);
    }

protected:
    /// Stores socket descriptor.
    int sockfd_;
};

/// Pointer to a command socket object
typedef boost::shared_ptr<CommandSocket> CommandSocketPtr;

/// @brief This class represents a streaming socket for handling connections
///
/// Initially a socket (e.g. UNIX) is opened (represented by other classes, e.g.
/// @ref UnixCommandSocket). Once incoming connection is detected, that class
/// calls accept(), which returns a new socket dedicated to handling that
/// specific connection. That socket is represented by this class.
class ConnectionSocket : public CommandSocket {
public:
    /// @brief Default constructor
    ///
    /// This constructor is used in methods that call accept on existing
    /// sockets. accept() returns a socket descriptor. Hence only one
    /// parameter here.
    ///
    /// @param sockfd socket descriptor
    ConnectionSocket(int sockfd);

    /// @brief Method used to handle incoming data
    ///
    /// This method calls isc::config::CommandMgr::commandReader method.
    virtual void receiveHandler();

    /// @brief Closes socket.
    ///
    /// This method closes the socket, prints appropriate log message and
    /// unregisters callback from @ref isc::dhcp::IfaceMgr.
    virtual void close();
};

};
};

#endif
