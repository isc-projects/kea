// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file unix_control_socket.cc
/// Contains the UNIX socket derived class for control socket communication.

#include <config.h>

#include <netconf/unix_control_socket.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <cc/json_feed.h>
#include <config/client_connection.h>
#include <config/timeouts.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;

namespace isc {
namespace netconf {

template <> ControlSocketBasePtr
createControlSocket<CfgControlSocket::Type::UNIX>(CfgControlSocketPtr ctrl_sock) {
    return (UnixControlSocketPtr(new UnixControlSocket(ctrl_sock)));
}

UnixControlSocket::UnixControlSocket(CfgControlSocketPtr ctrl_sock)
    : ControlSocketBase(ctrl_sock) {
}

ConstElementPtr
UnixControlSocket::configGet(const string& /*service*/) {
    return (sendCommand(createCommand("config-get")));
}

ConstElementPtr
UnixControlSocket::configTest(ConstElementPtr config,
                              const string& /*service*/) {
    return (sendCommand(createCommand("config-test", config)));
}

ConstElementPtr
UnixControlSocket::configSet(ConstElementPtr config,
                             const string& /*service*/) {
    return (sendCommand(createCommand("config-set", config)));
}

ConstElementPtr
UnixControlSocket::sendCommand(ConstElementPtr command) {
    // We are using our own IO service because this method is synchronous.
    IOServicePtr io_service(new IOService());
    ClientConnection conn(*io_service);
    boost::system::error_code received_ec;
    ConstJSONFeedPtr received_feed;

    conn.start(ClientConnection::SocketPath(getName()),
               ClientConnection::ControlCommand(command->toWire()),
               [&io_service, &received_ec, &received_feed]
               (const boost::system::error_code& ec, ConstJSONFeedPtr feed) {
                   // Capture error code and parsed data.
                   received_ec = ec;
                   received_feed = feed;
                   // Got the IO service so stop IO service. This causes to
                   // stop IO service when all handlers have been invoked.
                   io_service->stopWork();
               },
               ClientConnection::Timeout(TIMEOUT_AGENT_FORWARD_COMMAND));

    // Perform this synchronously.
    io_service->run();

    if (received_ec) {
        // Got an error.
        isc_throw(ControlSocketError, "communication error: "
                  << received_ec.message());
    }

    if (!received_feed) {
        // Failed to get the answer.
        isc_throw(ControlSocketError, "empty response");
    }

    try {
        return (received_feed->toElement());
    } catch (const std::exception& ex) {
        isc_throw(ControlSocketError, "unparsable response: " << ex.what());
    }
}

} // namespace netconf
} // namespace isc
