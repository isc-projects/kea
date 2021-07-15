// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file stdout_control_socket.cc
/// Contains the stdout derived class for control socket communication.

#include <config.h>

#include <netconf/stdout_control_socket.h>
#include <cc/command_interpreter.h>

using namespace std;
using namespace isc::config;
using namespace isc::data;

namespace isc {
namespace netconf {

template <> ControlSocketBasePtr
createControlSocket<CfgControlSocket::Type::STDOUT>(CfgControlSocketPtr ctrl_sock) {
    return (StdoutControlSocketPtr(new StdoutControlSocket(ctrl_sock)));
}

StdoutControlSocket::StdoutControlSocket(CfgControlSocketPtr ctrl_sock)
    : ControlSocketBase(ctrl_sock), output_(cout) {
}

StdoutControlSocket::StdoutControlSocket(CfgControlSocketPtr ctrl_sock,
                                         ostream& output)
    : ControlSocketBase(ctrl_sock), output_(output) {
}

ConstElementPtr
StdoutControlSocket::configGet(const string& /*service*/) {
    isc_throw(NotImplemented, "No config-get for stdout control socket");
}

ConstElementPtr
StdoutControlSocket::configTest(ConstElementPtr /*config*/,
                                const string& /*service*/) {
    return (createAnswer());
}

ConstElementPtr
StdoutControlSocket::configSet(ConstElementPtr config,
                               const string& /*service*/) {
    prettyPrint(config, output_);
    output_ << endl;
    return (createAnswer());
}

} // namespace netconf
} // namespace isc
