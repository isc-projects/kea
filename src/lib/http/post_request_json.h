// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
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
/// @brief Pointer to const @ref PostHttpRequestJson.
typedef boost::shared_ptr<const PostHttpRequestJson> ConstPostHttpRequestJsonPtr;

/// @brief Represents HTTP POST request with JSON body.
///
/// In addition to the requirements specified by the @ref PostHttpRequest
/// this class requires that the "Content-Type" is "application/json".
///
/// This class provides methods to parse and retrieve JSON data structures.
class PostHttpRequestJson : public PostHttpRequest {
public:

    /// @brief Constructor.
    PostHttpRequestJson();

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

    void parseBodyAsJson();

    /// @brief Pointer to the parsed JSON body.
    data::ConstElementPtr json_;

};

} // namespace http
} // namespace isc

#endif
