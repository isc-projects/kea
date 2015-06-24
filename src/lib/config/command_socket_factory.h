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
