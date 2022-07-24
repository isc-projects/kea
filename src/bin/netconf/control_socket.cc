// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file stdout_control_socket.cc
/// Contains the stdout derived class for control socket communication.

#include <config.h>

#include <netconf/control_socket.h>
#include <netconf/http_control_socket.h>
#include <netconf/stdout_control_socket.h>
#include <netconf/unix_control_socket.h>

using namespace std;

namespace isc {
namespace netconf {

ControlSocketBasePtr
controlSocketFactory(CfgControlSocketPtr ctrl_sock) {
    if (!ctrl_sock) {
        isc_throw(BadValue, "null control socket configuration");
    }
    CfgControlSocket::Type sock_type = ctrl_sock->getType();
    switch (sock_type) {
    case CfgControlSocket::Type::UNIX:
        return (createControlSocket<CfgControlSocket::Type::UNIX>(ctrl_sock));
    case CfgControlSocket::Type::HTTP:
        return (createControlSocket<CfgControlSocket::Type::HTTP>(ctrl_sock));
    case CfgControlSocket::Type::STDOUT:
        return (createControlSocket<CfgControlSocket::Type::STDOUT>(ctrl_sock));
    default:
        isc_throw(BadValue, "Unknown control socket type: " << sock_type);
    }
}

} // namespace netconf
} // namespace isc
