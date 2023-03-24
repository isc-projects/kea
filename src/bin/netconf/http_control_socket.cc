// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file http_control_socket.cc
/// Contains the HTTP socket derived class for control socket communication.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/tls_socket.h>
#include <cc/command_interpreter.h>
#include <config/timeouts.h>
#include <http/client.h>
#include <http/post_request_json.h>
#include <http/response_json.h>
#include <netconf/http_control_socket.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;

namespace isc {
namespace netconf {

template <> ControlSocketBasePtr
createControlSocket<CfgControlSocket::Type::HTTP>(CfgControlSocketPtr ctrl_sock) {
    return (HttpControlSocketPtr(new HttpControlSocket(ctrl_sock)));
}

HttpControlSocket::HttpControlSocket(CfgControlSocketPtr ctrl_sock)
    : ControlSocketBase(ctrl_sock) {
}

ConstElementPtr
HttpControlSocket::configGet(const string& service) {
    if (service == "ca") {
        return (sendCommand(createCommand("config-get")));
    } else {
        return (sendCommand(createCommand("config-get", service)));
    }
}

ConstElementPtr
HttpControlSocket::configTest(ElementPtr config, const string& service) {
    if (service == "ca") {
        return (sendCommand(createCommand("config-test", config)));
    } else {
        return (sendCommand(createCommand("config-test", config, service)));
    }
}

ConstElementPtr
HttpControlSocket::configSet(ElementPtr config, const string& service) {
    if (service == "ca") {
        return (sendCommand(createCommand("config-set", config)));
    } else {
        return (sendCommand(createCommand("config-set", config, service)));
    }
}

ConstElementPtr
HttpControlSocket::sendCommand(ConstElementPtr command) {
    PostHttpRequestJsonPtr request;
    request.reset(new PostHttpRequestJson(HttpRequest::Method::HTTP_POST,
                                          "/",
                                          HttpVersion(1, 1)));
    request->setBodyAsJson(command);
    try {
        request->finalize();
    } catch (exception const& ex) {
        isc_throw(ControlSocketError, "failed to create request: "
                  << ex.what());
    }

    IOServicePtr io_service(new IOService());
    HttpClient client(*io_service, false);
    boost::system::error_code received_ec;
    string receive_errmsg;
    HttpResponseJsonPtr response(new HttpResponseJson());

    client.asyncSendRequest(getUrl(), TlsContextPtr(), request, response,
                [&io_service, &received_ec, &receive_errmsg]
                (const boost::system::error_code& ec,
                const HttpResponsePtr&, const string& errmsg) {
                        // Capture error code and message.
                        received_ec = ec;
                        receive_errmsg = errmsg;
                        // Got the IO service so stop IO service.
                        // This causes to stop IO service when
                        // all handlers have been invoked.
                        io_service->stopWork();
                },
                HttpClient::RequestTimeout(TIMEOUT_AGENT_FORWARD_COMMAND));

    // Perform this synchronously.
    io_service->run();

    if (received_ec) {
        // Got an error code.
        isc_throw(ControlSocketError, "communication error (code): "
                  << received_ec.message());
    }

    if (!receive_errmsg.empty()) {
        // Got an error message.
        isc_throw(ControlSocketError, "communication error (message): "
                  << receive_errmsg);
    }

    if (!response) {
        // Failed to get the answer.
        isc_throw(ControlSocketError, "empty response");
    }

    try {
        return (response->getBodyAsJson());
    } catch (exception const& ex) {
        isc_throw(ControlSocketError, "unparsable response: " << ex.what());
    }
}

}  // namespace netconf
}  // namespace isc

