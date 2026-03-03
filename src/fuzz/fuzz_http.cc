// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <log/logger_support.h>
#include <process/daemon.h>

#include <cc/data.h>

#include <http/basic_auth_config.h>
#include <http/cfg_http_header.h>
#include <http/date_time.h>
#include <http/http_types.h>
#include <http/request.h>
#include <http/request_parser.h>
#include <http/response.h>
#include <http/response_parser.h>
#include <http/url.h>

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace isc;
using namespace isc::data;
using namespace isc::http;

static constexpr HttpRequest::Method requestMethods[] = {
    HttpRequest::Method::HTTP_GET, HttpRequest::Method::HTTP_POST,
    HttpRequest::Method::HTTP_HEAD, HttpRequest::Method::HTTP_PUT,
    HttpRequest::Method::HTTP_DELETE, HttpRequest::Method::HTTP_OPTIONS,
    HttpRequest::Method::HTTP_CONNECT, HttpRequest::Method::HTTP_METHOD_UNKNOWN
};

static constexpr HttpStatusCode statusCodes[] = {
    HttpStatusCode::OK, HttpStatusCode::CREATED, HttpStatusCode::ACCEPTED,
    HttpStatusCode::NO_CONTENT, HttpStatusCode::MULTIPLE_CHOICES,
    HttpStatusCode::MOVED_PERMANENTLY, HttpStatusCode::MOVED_TEMPORARILY,
    HttpStatusCode::NOT_MODIFIED, HttpStatusCode::BAD_REQUEST,
    HttpStatusCode::UNAUTHORIZED, HttpStatusCode::FORBIDDEN,
    HttpStatusCode::NOT_FOUND, HttpStatusCode::REQUEST_TIMEOUT,
    HttpStatusCode::INTERNAL_SERVER_ERROR, HttpStatusCode::NOT_IMPLEMENTED,
    HttpStatusCode::BAD_GATEWAY, HttpStatusCode::SERVICE_UNAVAILABLE
};

template <typename ParserT>
inline void requestResponseParsing(ParserT& parser, const std::string& payload) {
    size_t off = 0;

    // Parse the payload until data use up
    while (off < payload.size()) {
        size_t remain = payload.size() - off;
        size_t chunk = 1;
        chunk = std::min(remain, (off % 32) + 1);

        parser.postBuffer(reinterpret_cast<const uint8_t*>(payload.data()) + off, chunk);
        off += chunk;
        parser.poll();
        if (!parser.needData()) {
            parser.poll();
        }
    }

    // Finishing the parsing
    if (parser.needData()) {
        parser.postBuffer(nullptr, 0);
        parser.poll();
    }

    parser.getErrorMessage();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
    FuzzedDataProvider fdp(Data, Size);

    HttpRequest request;
    HttpResponse response;

    // Generate random value
    const std::string key = fdp.ConsumeBytesAsString(10);
    const HttpVersion version = fdp.ConsumeBool()?HttpVersion::HTTP_11():HttpVersion::HTTP_10();
    const HttpRequest::Method requestMethod = requestMethods[fdp.ConsumeIntegralInRange<int>(0, 7)];
    const HttpStatusCode statusCode = statusCodes[fdp.ConsumeIntegralInRange<int>(0, 16)];

    // Generate payload
    const std::string payload = fdp.ConsumeRemainingBytesAsString();

    try {
        // Request parsing
        HttpRequestParser requestParser(request);
        requestParser.initModel();

        // Feed payload into request parser and functions
        requestResponseParsing(requestParser, payload);
        request.getHttpVersion();
        request.context();
        request.getMethod();
        request.getUri();
        request.getBasicAuth();
        request.requireHttpVersion(version);
        request.requireHttpMethod(requestMethod);
        request.getHeaderValue(key);
        request.getHeader(key);
        request.requireHeader(key);
        request.finalize();
        request.reset();
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try {
        // Response parsing
        HttpResponseParser responseParser(response);
        responseParser.initModel();

        // Feed payload into response parser and functions
        requestResponseParsing(responseParser, payload);
        response.getStatusCode();
        response.getHttpVersion();
        response.context();
        response.requireHttpVersion(version);
        response.getHeaderValue(key);
        response.getHeader(key);
        response.requireHeader(key);
        response.statusCodeToNumber(statusCode);
        response.statusCodeToString(statusCode);
        response.isClientError(statusCode);
        response.isServerError(statusCode);
        response.create();
        response.finalize();
        response.reset();
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try {
        // Response JSON parsing
        HttpResponseJson json(version, statusCode);
        json.setBodyAsJson(Element::create(payload));
        json.finalize();
        json.reset();
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try {
        // Configuration headers parsing
        ConstElementPtr elem = Element::fromJSON(payload);
        CfgHttpHeaders headers = parseCfgHttpHeaders(elem);
        copyHttpHeaders(headers, request);
        copyHttpHeaders(headers, response);
        CfgHttpHeaderstoElement(headers);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try{
        // Basic Authentication Configuration parsing
        BasicHttpAuthConfig cfg;
        cfg.parse(Element::fromJSON(payload));
        cfg.toElement();
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try{
        // Parse url
        Url url(payload);
        url.isValid();
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try{
        // Parse Datetime
        HttpDateTime::fromAny(payload);
        HttpDateTime::fromRfc1123(payload);
        HttpDateTime::fromRfc850(payload);
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    try {
        request.finalize();
        response.finalize();
        request.reset();
        response.reset();
    } catch (const isc::Exception&) {
        // Slient exceptions
    } catch (const boost::exception&) {
        // Slient exceptions
    }

    return 0;
}
