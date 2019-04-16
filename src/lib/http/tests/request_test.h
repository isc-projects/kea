// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_TEST_H
#define HTTP_REQUEST_TEST_H

#include <http/http_types.h>
#include <http/request.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <string>
#include <utility>

namespace isc {
namespace http {
namespace test {

/// @brief Base test fixture class for testing @ref HttpRequest class and its
/// derivations.
///
/// @tparam HttpRequestType Class under test.
template<typename HttpRequestType>
class HttpRequestTestBase : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates HTTP request to be used in unit tests.
    HttpRequestTestBase()
        : request_(new HttpRequestType()) {
    }

    /// @brief Destructor.
    ///
    /// Does nothing.
    virtual ~HttpRequestTestBase() {
    }

    /// @brief Initializes HTTP request context with basic information.
    ///
    /// It sets:
    /// - HTTP method,
    /// - URI,
    /// - HTTP version number.
    ///
    /// @param method HTTP method as string.
    /// @param uri URI.
    /// @param version A pair of values of which the first is the major HTTP
    /// version and the second is the minor HTTP version.
    void setContextBasics(const std::string& method, const std::string& uri,
                          const HttpVersion& version) {
        request_->context()->method_ = method;
        request_->context()->uri_ = uri;
        request_->context()->http_version_major_ = version.major_;
        request_->context()->http_version_minor_ = version.minor_;
    }

    /// @brief Adds HTTP header to the context.
    ///
    /// @param header_name HTTP header name.
    /// @param header_value HTTP header value. This value will be converted to
    /// a string using @c boost::lexical_cast.
    /// @tparam ValueType Header value type.
    template<typename ValueType>
    void addHeaderToContext(const std::string& header_name,
                            const ValueType& header_value) {
        request_->context()->headers_.push_back(HttpHeaderContext(header_name, header_value));
    }

    /// @brief Instance of the @ref HttpRequest or its derivation.
    boost::shared_ptr<HttpRequestType> request_;
};

} // namespace test
} // namespace http
} // namespace isc

#endif
