// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_JSON_H
#define HTTP_RESPONSE_JSON_H

#include <cc/data.h>
#include <http/response.h>

namespace isc {
namespace http {

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

    /// @brief Constructor.
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

    /// @brief Generates JSON content from the data structures represented
    /// as @ref data::ConstElementPtr.
    ///
    /// @param json_body A data structure representing JSON content.
    virtual void setBodyAsJson(const data::ConstElementPtr& json_body);

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
};

}
}

#endif
