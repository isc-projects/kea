// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_JSON_H
#define HTTP_RESPONSE_JSON_H

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <http/response.h>

namespace isc {
namespace http {

/// @brief Exception thrown when body of the HTTP message is not JSON.
class HttpResponseJsonError : public HttpResponseError {
public:
    HttpResponseJsonError(const char* file, size_t line, const char* what) :
        HttpResponseError(file, line, what) { };
};

class HttpResponseJson;

/// @brief Pointer to the @ref HttpResponseJson object.
typedef boost::shared_ptr<HttpResponseJson> HttpResponseJsonPtr;

/// @brief Represents HTTP response with JSON content.
///
/// This is a specialization of the @ref HttpResponse class which
/// includes "Content-Type" equal to "application/json". It also provides
/// methods to create JSON content within HTTP responses.
class HttpResponseJson : public HttpResponse {
public:

    /// @brief Constructor for the inbound HTTP response.
    explicit HttpResponseJson();

    /// @brief Constructor for the outbound HTTP response.
    ///
    /// @param version HTTP version.
    /// @param status_code HTTP status code.
    /// @param generic_body Indicates if the constructor should call
    /// @c setGenericBody to create a generic content for the given
    /// status code. This should be set to "no" when the constructor is
    /// called by the derived class which provides its own implementation
    /// of the @c setGenericBody method.
    explicit HttpResponseJson(const HttpVersion& version,
                              const HttpStatusCode& status_code,
                              const CallSetGenericBody& generic_body =
                              CallSetGenericBody::yes());

    /// @brief Completes creation of the HTTP response.
    ///
    /// This method marks the response as finalized. The JSON structure is
    /// created and can be used to retrieve the parsed data. If this is the
    /// outbound message, it can be transmitted over the wire as the body
    /// for the message is now committed.
    virtual void finalize();

    /// @brief Reset the state of the object.
    virtual void reset();

    /// @brief Retrieves JSON body.
    ///
    /// @return Pointer to the root element of the JSON structure.
    /// @throw HttpRequestJsonError if an error occurred.
    data::ConstElementPtr getBodyAsJson() const;

    /// @brief Generates JSON content from the data structures represented
    /// as @ref data::ConstElementPtr.
    ///
    /// @param json_body A data structure representing JSON content.
    void setBodyAsJson(const data::ConstElementPtr& json_body);

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

private:

    /// @brief Sets generic body for the given status code.
    ///
    /// This method generates JSON content for the HTTP client and server
    /// errors. The generated JSON structure is a map containing "result"
    /// value holding HTTP status code (e.g. 400) and the "text" string
    /// holding a status code description.
    ///
    /// @param status_code Status code for which the body should be
    /// generated.
    void setGenericBody(const HttpStatusCode& status_code);

protected:

    /// @brief Interprets body as JSON, which can be later retrieved using
    /// data element objects.
    void parseBodyAsJson();

    /// @brief Pointer to the parsed JSON body.
    data::ConstElementPtr json_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
