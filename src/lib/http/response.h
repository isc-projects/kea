// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <exceptions/exceptions.h>
#include <http/http_types.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <map>
#include <string>

namespace isc {
namespace http {

/// @brief Generic exception thrown by @ref HttpResponse class.
class HttpResponseError : public Exception {
public:
    HttpResponseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
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
/// This class represents HTTP response message. An instance of this object
/// or its derivation is typically created by the implementation of the
/// @ref HttpResponseCreator interface.
///
/// It contains @c toString method generating a textual representation of
/// the HTTP response, which is send to the client over TCP socket.
class HttpResponse {
public:

    /// @brief Constructor.
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

    /// @brief Destructor.
    ///
    /// A class having virtual methods must have a virtual destructor.
    virtual ~HttpResponse() { }

    /// @brief Adds HTTP header to the response.
    ///
    /// The "Content-Length" and "Date" headers should not be added using this
    /// method because they are generated and added automatically when the
    /// @c toString is called.
    ///
    /// @param name Header name.
    /// @param value Header value.
    /// @tparam ValueType Type of the header value.
    template<typename ValueType>
    void addHeader(const std::string& name, const ValueType& value) {
        addHeaderInternal(name, value, headers_);
    }

    /// @brief Assigns body/content to the message.
    ///
    /// @param body Body to be assigned.
    void setBody(const std::string& body);

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

    /// @brief Converts status code to string.
    ///
    /// @param status_code HTTP status code.
    /// @return Textual representation of the status code.
    static std::string statusCodeToString(const HttpStatusCode& status_code);

    /// @brief Returns HTTP version and HTTP status as a string.
    std::string toBriefString() const;

    /// @brief Returns textual representation of the HTTP response.
    ///
    /// It includes the "Date" header with the current time in RFC 1123 format.
    /// It also includes "Content-Length" when the response has a non-empty
    /// body.
    ///
    /// @return Textual representation of the HTTP response.
    std::string toString() const ;

protected:

    /// @brief Adds HTTP header to the map.
    ///
    /// @param name Header name.
    /// @param value Header value.
    /// @param [out] headers A map to which header value should be inserted.
    /// @tparam ValueType Type of the header value.
    template<typename ValueType>
    void addHeaderInternal(const std::string& name, const ValueType& value,
                           std::map<std::string, std::string>& headers) const {
        try {
            headers[name] = boost::lexical_cast<std::string>(value);

        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(HttpResponseError, "unable to convert the "
                      << name << " header value to a string");
        }
    }

    /// @brief Returns current time formatted as required by RFC 1123.
    ///
    /// This method is virtual so as it can be overridden in unit tests
    /// to return a "predictable" value of time, e.g. constant value.
    ///
    /// @return Current time formatted as required by RFC 1123.
    virtual std::string getDateHeaderValue() const;

    /// @brief Convenience method converting status code to numeric value.
    ///
    /// @param status_code Status code represented as enum.
    /// @return Numeric representation of the status code.
    static uint16_t statusCodeToNumber(const HttpStatusCode& status_code);

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

    /// @brief Holds HTTP version for the response.
    HttpVersion http_version_;

    /// @brief Holds status code for the response.
    HttpStatusCode status_code_;

    /// @brief Holds HTTP headers for the response.
    std::map<std::string, std::string> headers_;

    /// @brief Holds the body/content.
    std::string body_;

};

} // namespace http
} // namespace isc

#endif
