// Copyright (C) 2018-2026 Internet Systems Consortium, Inc. ("ISC")
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
    return (sendCommand(createCommand("config-get", service)));
}

ConstElementPtr
HttpControlSocket::configTest(ElementPtr config, const string& service) {
    return (sendCommand(createCommand("config-test", config, service)));
}

ConstElementPtr
HttpControlSocket::configSet(ElementPtr config, const string& service) {
    return (sendCommand(createCommand("config-set", config, service)));
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
    HttpClient client(io_service, false);
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
                HttpClient::RequestTimeout(TIMEOUT_DHCP_SERVER_FORWARD_COMMAND));

    // Perform this synchronously.
    io_service->run();

    client.stop();
    io_service->stopAndPoll();

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
        auto response_list = response->getBodyAsJson();
        // If there is no error the expected response is a list.
        if (response_list->getType() == Element::list) {
            // There must be at least one response.
            if (response_list->empty()) {
                isc_throw(ControlSocketError, "list of responses must not be empty");
            }
            return (response_list->get(0));
        }
        // If there is an error the expected response is a map.
        return (response->getBodyAsJson());
    } catch (exception const& ex) {
        isc_throw(ControlSocketError, "unparsable response: " << ex.what());
    }
}

}  // namespace netconf
}  // namespace isc
