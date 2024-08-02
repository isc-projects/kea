// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace isc {
namespace http {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to whch HTTP service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Test HTTP response.
typedef test::TestHttpResponseBase<HttpResponseJson> Response;

/// @brief Pointer to test HTTP response.
typedef boost::shared_ptr<Response> ResponsePtr;

/// @brief Generic test HTTP response.
typedef test::TestHttpResponseBase<HttpResponse> GenericResponse;

/// @brief Pointer to generic test HTTP response.
typedef boost::shared_ptr<GenericResponse> GenericResponsePtr;

}
}
