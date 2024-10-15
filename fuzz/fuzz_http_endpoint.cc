// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
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
using namespace isc::process;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
using namespace std;

namespace {

void timeoutHandler() {
    cerr << "Timeout occurred while fuzzing!" << endl;
    abort();
}

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

ThreadPool<function<void()>> THREAD_POOL;

static pid_t const PID(getpid());
static string const PID_STR(to_string(PID));

}  // namespace

extern "C" {

int
LLVMFuzzerInitialize() {
    static bool initialized(DoInitialization());
    assert(initialized);

    return 0;
}

int
LLVMFuzzerTearDown() {
    return 0;
}

int
LLVMFuzzerTestOneInput(uint8_t const* data, size_t size) {
    string const address("127.0.0.1");
    int const port(18000);
    int const timeout(100000);

    CmdHttpListener listener(IOAddress(address), port);
    MultiThreadingMgr::instance().setMode(true);

    // Start the server.
    listener.start();

    // Create a client and specify the URL on which the server can be reached.
    IOServicePtr io_service(new IOService());
    IntervalTimer run_io_service_timer(io_service);
    HttpClient client(io_service, false);
    stringstream ss;
    ss << "http://" << address << ":" << port;
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

    // Actually trigger the requests. The requests should be handlded by the
    // server one after another. While the first request is being processed
    // the server should queue another one.
    io_service->getInternalIOService().reset();
    run_io_service_timer.setup(&timeoutHandler, timeout, IntervalTimer::ONE_SHOT);
    io_service->runOne();
    io_service->getInternalIOService().reset();
    io_service->poll();

    // Make sure that the received responses are different. We check that by
    // comparing value of the sequence parameters.
    if (getenv("DEBUG")) {
        if (response) {
            cout << response->getBody() << endl;
        } else {
            cout << "no response" << endl;
        }
    }
    listener.stop();
    io_service->poll();
    client.stop();
    MultiThreadingMgr::instance().setMode(false);

    return 0;
}

}  // extern "C"
