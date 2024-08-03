// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CREATOR_TEST_H
#define HTTP_RESPONSE_CREATOR_TEST_H

namespace isc {
namespace http {
namespace test {

/// @brief Implementation of the @ref HttpResponseCreator.
class TestHttpResponseCreator : public HttpResponseCreator {
public:

    /// @brief Create a new request.
    ///
    /// @return Pointer to the new instance of the @ref HttpRequest.
    virtual HttpRequestPtr
    createNewHttpRequest() const {
        return (HttpRequestPtr(new PostHttpRequestJson()));
    }

private:

    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP response.
    virtual HttpResponsePtr
    createStockHttpResponse(const HttpRequestPtr& request,
                            const HttpStatusCode& status_code) const {
        // The request hasn't been finalized so the request object
        // doesn't contain any information about the HTTP version number
        // used. But, the context should have this data (assuming the
        // HTTP version is parsed ok).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        ResponsePtr response(new Response(http_version, status_code));
        response->finalize();
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// This method generates 3 types of responses:
    /// - response with a requested content type,
    /// - partial response with incomplete JSON body,
    /// - response with JSON body copied from the request.
    ///
    /// The first one is useful to test situations when received response can't
    /// be parsed because of the content type mismatch. The second one is useful
    /// to test request timeouts. The third type is used by most of the unit tests
    /// to test successful transactions.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response with no content.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) {
        // Request must always be JSON.
        PostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
        data::ConstElementPtr body;
        if (request_json) {
            body = request_json->getBodyAsJson();
            if (body) {
                // Check if the client requested one of the two first response
                // types.
                GenericResponsePtr response;
                data::ConstElementPtr content_type =
                    body->get("requested-content-type");
                data::ConstElementPtr partial_response =
                    body->get("partial-response");
                if (content_type || partial_response) {
                    // The first two response types can only be generated using the
                    // generic response as we have to explicitly modify some of the
                    // values.
                    response.reset(new GenericResponse(request->getHttpVersion(),
                                                       HttpStatusCode::OK));
                    HttpResponseContextPtr ctx = response->context();

                    if (content_type) {
                        // Provide requested content type.
                        ctx->headers_.push_back(HttpHeaderContext("Content-Type",
                                                                  content_type->stringValue()));
                        // It doesn't matter what body is there.
                        ctx->body_ = "abcd";
                        response->finalize();

                    } else {
                        // Generate JSON response.
                        ctx->headers_.push_back(HttpHeaderContext("Content-Type",
                                                                  "application/json"));
                        // The body lacks '}' so the client will be waiting for it and
                        // eventually should time out.
                        ctx->body_ = "{";
                        response->finalize();
                        // The auto generated Content-Length header would be based on the
                        // body size (so set to 1 byte). We have to override it to
                        // account for the missing '}' character.
                        response->setContentLength(2);
                    }
                    return (response);
                }
            }
        }

        // Third type of response is requested.
        ResponsePtr response(new Response(request->getHttpVersion(),
                                          HttpStatusCode::OK));
        // If body was included in the request. Let's copy it.
        if (body) {
            response->setBodyAsJson(body);
        }

        response->finalize();
        return (response);
    }
};

/// @brief Implementation of the test @ref HttpResponseCreatorFactory.
///
/// This factory class creates @ref TestHttpResponseCreator instances.
class TestHttpResponseCreatorFactory : public HttpResponseCreatorFactory {
public:

    /// @brief Creates @ref TestHttpResponseCreator instance.
    virtual HttpResponseCreatorPtr create() const {
        HttpResponseCreatorPtr response_creator(new TestHttpResponseCreator());
        return (response_creator);
    }
};

}
}
}
#endif // HTTP_RESPONSE_CREATOR_TEST_H
