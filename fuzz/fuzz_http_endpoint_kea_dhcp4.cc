// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <list>

#include <fuzz.h>

#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
#include <cc/data.h>
#include <config/cmd_http_listener.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <http/testutils/test_http_client.h>
#include <process/d_controller.h>
#include <util/filesystem.h>
#include <util/multi_threading_mgr.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
using namespace std;

namespace {

static pid_t const PID(getpid());
static string const PID_STR(to_string(PID));
static string const ADDRESS("127.0.0.1");
static string const KEA_DHCP4_CONF(KEA_FUZZ_DIR() + "/kea-dhcp4-" + PID_STR + ".conf");
static string const KEA_DHCP4_CSV(KEA_FUZZ_DIR() + "/kea-dhcp4-" + PID_STR + ".csv");

static int PORT;
static string PORT_STR;

/// @brief Represents HTTP POST request with JSON body.
///
/// In addition to the requirements specified by the @ref PostHttpRequest
/// this class requires that the "Content-Type" is "application/json".
///
/// This class provides methods to parse and retrieve JSON data structures.
struct PostHttpRequestBytes : PostHttpRequest {
    /// @brief Constructor for inbound HTTP request.
    explicit PostHttpRequestBytes() : PostHttpRequest() {
        requireHeaderValue("Content-Type", "application/json");
    }

    /// @brief Constructor for outbound HTTP request.
    ///
    /// This constructor adds "Content-Type" header with the value of
    /// "application/json" to the context.
    ///
    /// @param method HTTP method, e.g. POST.
    /// @param uri URI.
    /// @param version HTTP version.
    /// @param host_header Host header to be included in the request. The default
    /// is the empty Host header.
    /// @param basic_auth Basic HTTP authentication credential. The default
    /// is no authentication.
    explicit PostHttpRequestBytes(const Method& method,
                                  const string& uri,
                                  const HttpVersion& version,
                                  const HostHttpHeader& host_header = HostHttpHeader(),
                                  const BasicHttpAuthPtr& basic_auth = BasicHttpAuthPtr())
        : PostHttpRequest(method, uri, version, host_header, basic_auth) {
        requireHeaderValue("Content-Type", "application/json");
        context()->headers_.push_back(HttpHeaderContext("Content-Type", "application/json"));
    }

    /// @brief Sets JSON body for an outbound message.
    ///
    /// @param body JSON structure to be used as a body.
    void setBodyAsBytes(vector<uint8_t> const& input) {
        context_->body_ = string(input.begin(), input.end());
    }
};

using PostHttpRequestBytesPtr = boost::shared_ptr<PostHttpRequestBytes>;

}  // namespace

extern "C" {

int
LLVMFuzzerInitialize() {
    static bool initialized(DoInitialization());
    assert(initialized);

    setenv("KEA_DHCP4_FUZZING_ROTATE_PORT", "true", 0);

    return 0;
}

int
LLVMFuzzerTearDown() {
    try {
        remove(KEA_DHCP4_CONF.c_str());
    } catch (...) {
    }
    try {
        remove(KEA_DHCP4_CSV.c_str());
    } catch (...) {
    }
    return 0;
}

int
LLVMFuzzerTestOneInput(uint8_t const* data, size_t size) {
    CfgMgr::instance().clear();
    ControlledDhcpv4Srv server;

    PORT = ControlledDhcpv4Srv::getInstance()->getServerPort();
    PORT_STR = to_string(PORT);

    writeToFile(KEA_DHCP4_CONF, R"(
      {
        "Dhcp4": {
          "control-sockets": [
            {
              "socket-address": ")" + ADDRESS + R"(",
              "socket-port": )" + PORT_STR + R"(,
              "socket-type": "http"
            }
          ],
          "lease-database": {
            "name": ")" + KEA_DHCP4_CSV + R"(",
            "persist": false,
            "type": "memfile"
          }
        }
      }
    )");

    server.init(KEA_DHCP4_CONF);

    HttpClient client(ControlledDhcpv4Srv::getInstance()->getIOService(), false);
    stringstream ss;
    ss << "http://" << ADDRESS << ":" << PORT_STR;
    Url url(ss.str());

    // Initiate request to the server.
    PostHttpRequestBytesPtr request(new PostHttpRequestBytes(
        HttpRequest::Method::HTTP_POST, "/", HttpVersion(1, 1)));

    // Body is a map with a specified parameter included.
    vector<uint8_t> const body(data, data + size);
    request->setBodyAsBytes(body);
    request->finalize();
    HttpResponseJsonPtr response(new HttpResponseJson());
    client.asyncSendRequest(
        url, TlsContextPtr(), request, response,
        [](boost::system::error_code const&,
           HttpResponsePtr const&,
           string const&) {
        });

    ControlledDhcpv4Srv::getInstance()->getIOService()->poll();

    // Make sure that the received responses are different. We check that by
    // comparing value of the sequence parameters.
    if (getenv("DEBUG")) {
        if (response) {
            cout << response->getBody() << endl;
        } else {
            cout << "no response" << endl;
        }
    }
    client.stop();
    ControlledDhcpv4Srv::getInstance()->getIOService()->poll();
    MultiThreadingMgr::instance().setMode(false);

    return 0;
}

}  // extern "C"
