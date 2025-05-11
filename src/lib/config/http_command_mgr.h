// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_COMMAND_MGR_H
#define HTTP_COMMAND_MGR_H

#include <asiolink/io_service.h>
#include <config/http_command_config.h>
#include <boost/noncopyable.hpp>

namespace isc {
namespace config {

/// @brief Declaration of the implementation class.
class HttpCommandMgrImpl;

/// @brief HTTP Commands Manager implementation for the Kea servers.
///
/// Similar to @c UnixCommandMgr but using HTTP/HTTPS instead of UNIX sockets.
class HttpCommandMgr : public boost::noncopyable {
public:

    /// @brief HttpCommandMgr is a singleton class. This method
    /// returns reference to its sole instance.
    ///
    /// @return The only existing instance of the manager.
    static HttpCommandMgr& instance();

    /// @brief Sets IO service to be used by the http command manager.
    ///
    /// The server should use this method to provide the Command
    /// Manager with the common IO service used by the server.
    /// @param io_service Pointer to the IO service.
    void setIOService(const asiolink::IOServicePtr& io_service);

    /// @brief Override default connection timeout.
    ///
    /// @param timeout New connection timeout in milliseconds.
    void setConnectionTimeout(const long timeout);

    /// @brief Override default idle connection timeout.
    ///
    /// @param timeout New connection timeout in milliseconds.
    void setIdleConnectionTimeout(const long timeout);

    /// @brief Use external sockets flag.
    ///
    /// Add sockets as external sockets of the interface manager
    /// so available I/O on them makes a waiting select to return.
    ///
    /// @param use_external True (default) add external sockets.
    void addExternalSockets(bool use_external = true);

    /// @brief Open http control sockets using configuration.
    ///
    /// @param config Configuration information for the http control sockets.
    void openCommandSockets(const isc::data::ConstElementPtr config);

    /// @brief Open http control socket using configuration.
    ///
    /// Creates http/https listener, or reuses the existing one reapplying
    /// changes.
    ///
    /// @note This function in used internally by @ref openCommandSockets and it
    /// should not be used directly, except for unit tests.
    ///
    /// @param config Configuration information for the http control socket.
    void openCommandSocket(const isc::data::ConstElementPtr config);

    /// @brief Close http control socket.
    ///
    /// @note This function in used internally by @ref closeCommandSockets and it
    /// should not be used directly, except for unit tests.
    ///
    /// @param info Configuration information for the http control socket.
    /// @param remove When true remove the listeners immediately.
    void closeCommandSocket(HttpSocketInfoPtr info = HttpSocketInfoPtr(), bool remove = true);

    /// @brief Close http control sockets.
    void closeCommandSockets();

    /// @brief Returns a const pointer to the HTTP listener.
    ///
    /// @param info Configuration information for the http control socket.
    ///
    /// @return Const pointer to the currently used listener or null pointer if
    /// there is no listener.
    isc::http::ConstHttpListenerPtr getHttpListener(HttpSocketInfoPtr info = HttpSocketInfoPtr()) const;

private:

    /// @brief Private constructor.
    HttpCommandMgr();

    /// @brief Pointer to the implementation of the @ref HttpCommandMgr.
    boost::shared_ptr<HttpCommandMgrImpl> impl_;
};

} // end of isc::config namespace
} // end of isc namespace
#endif
