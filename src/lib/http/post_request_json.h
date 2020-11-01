// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_POST_REQUEST_JSON_H
#define HTTP_POST_REQUEST_JSON_H

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <http/post_request.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace http {

/// @brief Exception thrown when body of the HTTP message is not JSON.
class HttpRequestJsonError : public HttpRequestError {
public:
    HttpRequestJsonError(const char* file, size_t line, const char* what) :
        HttpRequestError(file, line, what) { };
};

class PostHttpRequestJson;

/// @brief Pointer to @ref PostHttpRequestJson.
typedef boost::shared_ptr<PostHttpRequestJson> PostHttpRequestJsonPtr;

/// @brief Represents HTTP POST request with JSON body.
///
/// In addition to the requirements specified by the @ref PostHttpRequest
/// this class requires that the "Content-Type" is "application/json".
///
/// This class provides methods to parse and retrieve JSON data structures.
class PostHttpRequestJson : public PostHttpRequest {
public:

    /// @brief Constructor for inbound HTTP request.
    explicit PostHttpRequestJson();

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
    explicit PostHttpRequestJson(const Method& method, const std::string& uri,
                                 const HttpVersion& version,
                                 const HostHttpHeader& host_header = HostHttpHeader(),
                                 const BasicHttpAuthPtr& basic_auth = BasicHttpAuthPtr());

    /// @brief Complete parsing of the HTTP request.
    ///
    /// This method parses the JSON body into the structure of
    /// @ref data::ConstElementPtr objects.
    virtual void finalize();

    /// @brief Reset the state of the object.
    virtual void reset();

    /// @brief Retrieves JSON body.
    ///
    /// @return Pointer to the root element of the JSON structure.
    /// @throw HttpRequestJsonError if an error occurred.
    data::ConstElementPtr getBodyAsJson() const;

    /// @brief Sets JSON body for an outbound message.
    ///
    /// Note that this method copies the pointer to the body, rather than
    /// the entire data structure. Thus, the original object should not be
    /// modified after this method is called. If the specified pointer is
    /// null, the empty body is set.
    ///
    /// @param body JSON structure to be used as a body.
    void setBodyAsJson(const data::ConstElementPtr& body);

    /// @brief Retrieves a single JSON element.
    ///
    /// The element must be at top level of the JSON structure.
    ///
    /// @param element_name Element name.
    ///
    /// @return Pointer to the specified element or NULL if such element
    /// doesn't exist.
    /// @throw HttpRequestJsonError if an error occurred.
    data::ConstElementPtr getJsonElement(const std::string& element_name) const;

protected:

    /// @brief Interprets body as JSON, which can be later retrieved using
    /// data element objects.
    void parseBodyAsJson();

    /// @brief Pointer to the parsed JSON body.
    data::ConstElementPtr json_;

};

} // namespace http
} // namespace isc

#endif
