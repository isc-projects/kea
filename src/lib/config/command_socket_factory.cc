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

#include <config/command_socket_factory.h>
#include <config/config_log.h>
#include <config/command_mgr.h>
#include <dhcp/iface_mgr.h>
#include <boost/bind.hpp>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <cstdio>
#include <fcntl.h>

using namespace isc::data;

namespace isc {
namespace config {

/// @brief Wrapper for UNIX stream sockets
///
/// There are two UNIX socket types: datagram-based (equivalent of UDP) and
/// stream-based (equivalent of TCP). This class represents stream-based
/// sockets. It opens up a unix-socket and waits for incoming connections.
/// Once incoming connection is detected, accept() system call is called
/// and a new socket for that particular connection is returned. A new
/// object of @ref ConnectionSocket is created.
class UnixCommandSocket : public CommandSocket {
public:
    /// @brief Default constructor
    ///
    /// Opens specified UNIX socket.
    ///
    /// @param filename socket filename
    UnixCommandSocket(const std::string& filename)
        : filename_(filename) {

        // Create the socket and set it up.
        sockfd_ = createUnixSocket(filename_);

        // Install this socket in Interface Manager.
        isc::dhcp::IfaceMgr::instance().addExternalSocket(sockfd_,
            boost::bind(&UnixCommandSocket::receiveHandler, this));
    }

private:

    /// @brief Auxiliary method for creating a UNIX socket
    ///
    /// @param file_name specifies socket file path
    /// @return socket file descriptor
    int createUnixSocket(const std::string& file_name) {

        struct sockaddr_un addr;

        // string.size() returns number of bytes (without trailing zero)
        // we need 1 extra byte for terminating 0.
        if (file_name.size() > sizeof(addr.sun_path) - 1) {
            isc_throw(SocketError, "Failed to open socket: path specified ("
                      << file_name << ") is longer (" << file_name.size()
                      << " bytes) than allowed "
                      << (sizeof(addr.sun_path) - 1) << " bytes.");
        }

        int fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd == -1) {
            isc_throw(isc::config::SocketError, "Failed to create AF_UNIX socket:"
                      << strerror(errno));
        }

        // Let's remove the old file. We don't care about any possible
        // errors here. The file should not be there if the file was
        // shut down properly.
        static_cast<void>(remove(file_name.c_str()));

        // Set this socket to be non-blocking one.
        if (fcntl(fd, F_SETFL, O_NONBLOCK) !=0 ) {
            const char* errmsg = strerror(errno);
            ::close(fd);
            isc_throw(SocketError, "Failed to set non-block mode on unix socket "
                      << fd << ": " << errmsg);
        }

        // Now bind the socket to the specified path.
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, file_name.c_str(), sizeof(addr.sun_path) - 1);
        if (bind(fd, (struct sockaddr*)&addr, sizeof(addr))) {
            const char* errmsg = strerror(errno);
            ::close(fd);
            static_cast<void>(remove(file_name.c_str()));
            isc_throw(isc::config::SocketError, "Failed to bind socket " << fd
                      << " to " << file_name << ": " << errmsg);
        }

        // One means that we allow at most 1 awaiting connections.
        // Any additional attempts will get ECONNREFUSED error.
        // That means that at any given time, there may be at most one controlling
        // connection.
        /// @todo: Make the number of parallel connections configurable.
        int status = listen(fd, 1);
        if (status < 0) {
            const char* errmsg = strerror(errno);
            ::close(fd);
            static_cast<void>(remove(file_name.c_str()));
            isc_throw(isc::config::SocketError, "Failed to listen on socket fd="
                      << fd << ", filename=" << file_name << ": " << errmsg);
        }

        // Woohoo! Socket opened, let's log it!
        LOG_INFO(command_logger, COMMAND_SOCKET_UNIX_OPEN).arg(fd).arg(file_name);

        return (fd);
    }

    /// @brief Connection acceptor, a callback used to accept incoming connections.
    ///
    /// This callback is used on a control socket. Once called, it will accept
    /// incoming connection, create a new socket for it and create an instance
    /// of ConnectionSocket, which will take care of the rest (i.e. install
    /// appropriate callback for that new socket in @ref isc::dhcp::IfaceMgr).
    void receiveHandler() {

        // This method is specific to receiving data over UNIX socket, so using
        // sockaddr_un instead of sockaddr_storage here is ok.
        struct sockaddr_un client_addr;
        socklen_t client_addr_len;
        client_addr_len = sizeof(client_addr);

        // Accept incoming connection. This will create a separate socket for
        // handling this specific connection.
        int fd2 = accept(sockfd_, reinterpret_cast<struct sockaddr*>(&client_addr),
                         &client_addr_len);
        if (fd2 == -1) {
            LOG_ERROR(command_logger, COMMAND_SOCKET_ACCEPT_FAIL)
                .arg(sockfd_).arg(strerror(errno));
            return;
        }

        // And now create an object that represents that new connection.
        CommandSocketPtr conn(new ConnectionSocket(fd2));

        // Not sure if this is really needed, but let's set it to non-blocking
        // mode.
        if (fcntl(fd2, F_SETFL, O_NONBLOCK) != 0) {
            // Failed to set socket to non-blocking mode.
            LOG_ERROR(command_logger, COMMAND_SOCKET_FAIL_NONBLOCK)
                .arg(fd2).arg(sockfd_).arg(strerror(errno));

            conn.reset();
            return;
        }

        // Remember this socket descriptor. It will be needed when we shut down
        // the server.
        CommandMgr::instance().addConnection(conn);

        LOG_INFO(command_logger, COMMAND_SOCKET_CONNECTION_OPENED).arg(fd2)
            .arg(sockfd_);
    }

    // This method is called when we shutdown the connection.
    void close() {
        LOG_INFO(command_logger, COMMAND_SOCKET_UNIX_CLOSE).arg(sockfd_)
            .arg(filename_);

        isc::dhcp::IfaceMgr::instance().deleteExternalSocket(sockfd_);

        // Close should always succeed. We don't care if we're able to delete
        // the socket or not.
        ::close(sockfd_);
        static_cast<void>(remove(filename_.c_str()));
    }

    /// @brief UNIX filename representing this socket
    std::string filename_;
};

CommandSocketPtr
CommandSocketFactory::create(const isc::data::ConstElementPtr& socket_info) {
    if(!socket_info) {
        isc_throw(BadSocketInfo, "Missing socket_info parameters, can't create socket.");
    }

    ConstElementPtr type = socket_info->get("socket-type");
    if (!type) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-type' parameter missing");
    }

    if (type->stringValue() == "unix") {
        // UNIX socket is requested. It takes one parameter: socket-name that
        // specifies UNIX path of the socket.
        ConstElementPtr name = socket_info->get("socket-name");
        if (!name) {
            isc_throw(BadSocketInfo, "Mandatory 'socket-name' parameter missing");
        }
        if (name->getType() != Element::string) {
            isc_throw(BadSocketInfo, "'socket-name' parameter expected to be a string");
        }

        return (CommandSocketPtr(new UnixCommandSocket(name->stringValue())));
    } else {
        isc_throw(BadSocketInfo, "Specified socket type ('" + type->stringValue()
                  + "') is not supported.");
    }
}

};
};
