// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_SOCKET_FACTORY_H
#define COMMAND_SOCKET_FACTORY_H

#include <cc/data.h>
#include <config/command_socket.h>

namespace isc {
namespace config {

/// A factory class for opening command socket
///
/// This class provides an interface for opening command socket.
class CommandSocketFactory {
public:

    /// @brief Creates a socket specified by socket_info structure
    ///
    ///
    /// Currently supported types are:
    /// - unix
    ///
    /// See @ref CommandMgr::openCommandSocket for detailed description.
    /// @throw CommandSocketError
    ///
    /// @param socket_info structure that describes the socket
    /// @return socket descriptor
    static CommandSocketPtr create(const isc::data::ConstElementPtr& socket_info);
};

};
};

#endif
