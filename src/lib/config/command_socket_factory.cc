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
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

int createUnixSocket(const std::string& file_name) {

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        isc_throw(isc::config::SocketError, "Failed to create AF_UNIX socket.");
    }

    /// @todo: Do we need any setsockopt here?

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, file_name.c_str(), sizeof(addr.sun_path)-1);
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr))) {
        isc_throw(isc::config::SocketError, "Failed to bind socket " << fd
                  << " to " << file_name);
    }

    return (fd);
}

void closeUnixSocket(int socket_fd, const std::string& file_name) {
    close(socket_fd);
    unlink(file_name.c_str());
}

using namespace isc::data;

namespace isc {
namespace config {

int
CommandSocketFactory::create(const isc::data::ConstElementPtr& socket_info) {
    if(!socket_info) {
        isc_throw(BadSocketInfo, "Missing socket_info parameters, can't create socket.");
    }

    ConstElementPtr type = socket_info->get("socket-type");
    if (!type) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-type' parameter missing");
    }

    ConstElementPtr name = socket_info->get("socket-name");
    if (!name) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-name' parameter missing");
    }

    if (type->stringValue() == "unix") {
        return (createUnixSocket(name->stringValue()));
    } else {
        isc_throw(BadSocketInfo, "Specified socket type ('" + type->stringValue()
                  + "') is not supported.");
    }
}

void CommandSocketFactory::close(int socket_fd,
                                 const isc::data::ConstElementPtr& socket_info) {

    if(!socket_info) {
        isc_throw(BadSocketInfo, "Missing socket_info parameters, can't create socket.");
    }

    ConstElementPtr type = socket_info->get("socket-type");
    if (!type) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-type' parameter missing");
    }

    ConstElementPtr name = socket_info->get("socket-name");
    if (!name) {
        isc_throw(BadSocketInfo, "Mandatory 'socket-name' parameter missing");
    }

    if (type->stringValue() == "unix") {
        return (closeUnixSocket(socket_fd, name->stringValue()));
    } else {
        isc_throw(BadSocketInfo, "Specified socket type ('" + type->stringValue()
                  + "') is not supported.");
    }
}

};
};
