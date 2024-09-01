// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_COMMAND_MGR_H
#define UNIX_COMMAND_MGR_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

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

class UnixCommandMgrImpl;

/// @brief Unix Commands Manager implementation for the Kea servers.
///
/// This class receives and responds to commands over unix domain sockets.
class UnixCommandMgr : public boost::noncopyable {
public:

    /// @brief UnixCommandMgr is a singleton class. This method
    /// returns reference to its sole instance.
    ///
    /// @return the only existing instance of the manager.
    static UnixCommandMgr& instance();

    /// @brief Sets IO service to be used by the unix command manager.
    ///
    /// The server should use this method to provide the Unix Command
    /// Manager with the common IO service used by the server.
    /// @param io_service Pointer to the IO service.
    void setIOService(const asiolink::IOServicePtr& io_service);

    /// @brief Override default connection timeout.
    ///
    /// @param timeout New connection timeout in milliseconds.
    void setConnectionTimeout(const long timeout);

    /// @brief Opens unix control socket with parameters specified in socket_info
    /// (required parameters: socket-type: unix, socket-name:/unix/path).
    ///
    /// @throw BadSocketInfo When socket configuration is invalid.
    /// @throw SocketError When socket operation fails.
    ///
    /// @param socket_info Configuration information for the unix control socket.
    void
    openCommandSocket(const isc::data::ConstElementPtr& socket_info);

    /// @brief Shuts down any open unix control sockets
    void closeCommandSocket();

    /// @brief Returns unix control socket descriptor
    ///
    /// This method should be used only in tests.
    int getControlSocketFD();

private:

    /// @brief Private constructor.
    UnixCommandMgr();

    /// @brief Pointer to the implementation of the @ref UnixCommandMgr.
    boost::shared_ptr<UnixCommandMgrImpl> impl_;
};

} // end of isc::config namespace
} // end of isc namespace
#endif
