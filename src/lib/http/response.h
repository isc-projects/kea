// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <cc/data.h>
#include <http/header_context.h>
#include <http/http_message.h>
#include <http/response_context.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace isc {
namespace http {

/// @brief Generic exception thrown by @ref HttpResponse class.
class HttpResponseError : public HttpMessageError {
public:
    HttpResponseError(const char* file, size_t line, const char* what) :
        HttpMessageError(file, line, what) { };
};

/// @brief HTTP status codes (cf RFC 2068)
enum class HttpStatusCode : std::uint16_t {
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    MOVED_TEMPORARILY = 302,
    NOT_MODIFIED = 304,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    REQUEST_TIMEOUT = 408,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503
};

/// @brief Encapsulates the boolean value indicating if the @ref HttpResponse
/// constructor should call its @c setGenericBody method during construction.
struct CallSetGenericBody {

    /// @brief Constructor.
    ///
    /// @param set A boolean value indicating if the method should be called
    /// or not.
    explicit CallSetGenericBody(const bool set)
        : set_(set) {
    }

    /// @brief Returns encapsulated true.
    static const CallSetGenericBody& yes() {
        static CallSetGenericBody yes(true);
        return (yes);
    }

    /// @brief Returns encapsulated false.
    static const CallSetGenericBody& no() {
        static CallSetGenericBody no(false);
        return (no);
    }

    /// @brief A storage for the boolean flag.
    bool set_;
};

class HttpResponse;

/// @brief Pointer to the @ref HttpResponse object.
typedef boost::shared_ptr<HttpResponse> HttpResponsePtr;

/// @brief Pointer to the const @ref HttpResponse object.
typedef boost::shared_ptr<const HttpResponse> ConstHttpResponsePtr;

/// @brief Represents HTTP response message.
///
/// This derivation of the @c HttpMessage class is specialized to represent
/// HTTP responses. This class provides two constructors for creating an inbound
/// and outbound response instance respectively. This class is associated with
/// an instance of the @c HttpResponseContext, which is used to provide response
/// specific values, such as HTTP status and headers.
///
/// The derivations of this class provide specializations and specify the HTTP
/// versions and headers supported/required in the specific use cases. For example,
/// the @c HttpResponseJson class derives from the @c HttpResponse and it requires
/// that response includes a body in the JSON format.
class HttpResponse : public HttpMessage {
public:

    /// @brief Constructor for the inbound HTTP response.
    explicit HttpResponse();


    /// @brief Constructor for outbound HTTP response.
    ///
    /// Creates basic instance of the object. It sets the HTTP version and the
    /// status code to be included in the response.
    ///
    /// @param version HTTP version.
    /// @param status_code HTTP status code.
    /// @param generic_body Indicates if the constructor should call
    /// @c setGenericBody to create a generic content for the given
    /// status code. This should be set to "no" when the constructor is
    /// called by the derived class which provides its own implementation
    /// of the @c setGenericBody method.
    explicit HttpResponse(const HttpVersion& version,
                          const HttpStatusCode& status_code,
                          const CallSetGenericBody& generic_body =
                          CallSetGenericBody::yes());

    /// @brief Returns pointer to the @ref HttpResponseContext.
    ///
    /// The context holds intermediate data for creating a response. The response
    /// parser stores parsed raw data in the context. When parsing is finished,
    /// the data are validated and committed into the @c HttpResponse.
    ///
    /// @return Pointer to the underlying @ref HttpResponseContext.
    const HttpResponseContextPtr& context() const {
        return (context_);
    }

    /// @brief Commits information held in the context into the response.
    ///
    /// This function reads HTTP version, status code and headers from the
    /// context and validates their values. For the outbound messages, it
    /// automatically appends Content-Length and Date headers to the response.
    /// The Content-Length is set to the body size. The Date is set to the
    /// current date and time.
    virtual void create();

    /// @brief Completes creation of the HTTP response.
    ///
    /// This method marks the response as finalized. The outbound response may now
    /// be sent over the TCP socket. The information from the inbound message may
    /// be read, including the response body.
    virtual void finalize();

    /// @brief Reset the state of the object.
    virtual void reset();

    /// @brief Returns HTTP status code.
    HttpStatusCode getStatusCode() const;

    /// @brief Returns HTTP status phrase.
    std::string getStatusPhrase() const;

    /// @brief Returns HTTP response body as string.
    virtual std::string getBody() const;

    /// @brief Retrieves a single JSON element.
    ///
    /// The element must be at top level of the JSON structure.
    ///
    /// @param element_name Element name.
    ///
    /// @return Pointer to the specified element or NULL if such element
    /// doesn't exist.
    /// @throw HttpResponseJsonError if an error occurred.
    data::ConstElementPtr getJsonElement(const std::string& element_name) const;

    /// @brief Checks if the status code indicates client error.
    ///
    /// @param status_code HTTP status code.
    /// @return true if the status code indicates client error.
    static bool isClientError(const HttpStatusCode& status_code);

    /// @brief Checks if the status code indicates server error.
    ///
    /// @param status_code HTTP status code.
    /// @return true if the status code indicates server error.
    static bool isServerError(const HttpStatusCode& status_code);

    /// @brief Convenience method converting status code to numeric value.
    ///
    /// @param status_code Status code represented as enum.
    /// @return Numeric representation of the status code.
    static uint16_t statusCodeToNumber(const HttpStatusCode& status_code);

    /// @brief Converts status code to string.
    ///
    /// @param status_code HTTP status code.
    /// @return Textual representation of the status code.
    static std::string statusCodeToString(const HttpStatusCode& status_code);

    /// @brief Returns HTTP version and HTTP status as a string.
    std::string toBriefString() const;

    /// @brief Returns HTTP response as string.
    ///
    /// This method is called to generate the outbound HTTP response. Make
    /// sure to call @c finalize prior to calling this method.
    virtual std::string toString() const;

    /// @brief Returns current time formatted as required by RFC 1123.
    ///
    /// This method is virtual so as it can be overridden in unit tests
    /// to return a "predictable" value of time, e.g. constant value.
    ///
    /// @return Current time formatted as required by RFC 1123.
    virtual std::string getDateHeaderValue() const;

private:

    /// @brief Sets generic body for the given status code.
    ///
    /// Most of the classes derived from @ref HttpResponse will expect
    /// a certain content type. Depending on the content type used they
    /// will use different body formats for error messages. For example,
    /// a response using text/html will use HTML within the response
    /// body. The application/json will use JSON body etc. There is a
    /// need to implement class specific way of generating the body
    /// for error messages. Thus, each derivation of this class is
    /// required to implement class specific @ref setGenericBody function
    /// which should be called in the class constructor.
    ///
    /// This is also the case for this class, though the implementation
    /// of @c setGenericBody is currently no-op.
    ///
    /// Note that this class can't be declared virtual because it is
    /// meant to be called from the class constructor.
    ///
    /// @param status_code Status code for which the body should be
    /// generated.
    void setGenericBody(const HttpStatusCode& /*status_code*/) { };

protected:

    /// @brief Pointer to the @ref HttpResponseContext holding parsed
    /// data.
    HttpResponseContextPtr context_;
};

} // namespace http
} // namespace isc

#endif
