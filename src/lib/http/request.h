// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <exceptions/exceptions.h>
#include <http/http_types.h>
#include <http/request_context.h>
#include <boost/shared_ptr.hpp>
#include <map>
#include <set>
#include <stdint.h>
#include <string>
#include <utility>

namespace isc {
namespace http {

/// @brief Generic exception thrown by @ref HttpRequest class.
class HttpRequestError : public Exception {
public:
    HttpRequestError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when attempt is made to retrieve a
/// non-existing header.
class HttpRequestNonExistingHeader : public HttpRequestError {
public:
    HttpRequestNonExistingHeader(const char* file, size_t line,
                                 const char* what) :
        HttpRequestError(file, line, what) { };
};

class HttpRequest;

/// @brief Pointer to the @ref HttpRequest object.
typedef boost::shared_ptr<HttpRequest> HttpRequestPtr;

/// @brief Pointer to the const @ref HttpRequest object.
typedef boost::shared_ptr<const HttpRequest> ConstHttpRequestPtr;

/// @brief Represents HTTP request message.
///
/// This object represents parsed HTTP message. The @ref HttpRequestContext
/// contains raw data used as input for this object. This class interprets the
/// data. In particular, it verifies that the appropriate method, HTTP version,
/// and headers were used. The derivations of this class provide specializations
/// and specify the HTTP methods, versions and headers supported/required in
/// the specific use cases.
///
/// For example, the @ref PostHttpRequest class derives from @ref HttpRequest
/// and it requires that parsed messages use POST method. The
/// @ref PostHttpRequestJson, which derives from @ref PostHttpRequest requires
/// that the POST message includes body holding a JSON structure and provides
/// methods to parse the JSON body.
class HttpRequest {
public:

    /// @brief HTTP methods.
    enum class Method {
        HTTP_GET,
        HTTP_POST,
        HTTP_HEAD,
        HTTP_PUT,
        HTTP_DELETE,
        HTTP_OPTIONS,
        HTTP_CONNECT,
        HTTP_METHOD_UNKNOWN
    };

    /// @brief Constructor.
    ///
    /// Creates new context (@ref HttpRequestContext).
    HttpRequest();

    /// @brief Destructor.
    virtual ~HttpRequest();

    /// @brief Returns reference to the @ref HttpRequestContext.
    ///
    /// This method is called by the @ref HttpRequestParser to retrieve the
    /// context in which parsed data is stored.
    ///
    /// @return Pointer to the underlying @ref HttpRequestContext.
    const HttpRequestContextPtr& context() const {
        return (context_);
    }

    /// @brief Specifies an HTTP method allowed for the request.
    ///
    /// Allowed methods must be specified prior to calling @ref create method.
    /// If no method is specified, all methods are supported.
    ///
    /// @param method HTTP method allowed for the request.
    void requireHttpMethod(const HttpRequest::Method& method);

    /// @brief Specifies HTTP version allowed.
    ///
    /// Allowed HTTP versions must be specified prior to calling @ref create
    /// method. If no version is specified, all versions are allowed.
    ///
    /// @param version Version number allowed for the request.
    void requireHttpVersion(const HttpVersion& version);

    /// @brief Specifies a required HTTP header for the request.
    ///
    /// Required headers must be specified prior to calling @ref create method.
    /// The specified header must exist in the received HTTP request. This puts
    /// no requirement on the header value.
    ///
    /// @param header_name Required header name.
    void requireHeader(const std::string& header_name);

    /// @brief Specifies a required value of a header in the request.
    ///
    /// Required header values must be specified prior to calling @ref create
    /// method. The specified header must exist and its value must be equal to
    /// the value specified as second parameter.
    ///
    /// @param header_name HTTP header name.
    /// @param header_value HTTP header valuae.
    void requireHeaderValue(const std::string& header_name,
                            const std::string& header_value);

    /// @brief Checks if the body is required for the HTTP request.
    ///
    /// Current implementation simply checks if the "Content-Length" header
    /// is required for the request.
    ///
    /// @return true if the body is required for this request.
    bool requiresBody() const;

    /// @brief Reads parsed request from the @ref HttpRequestContext, validates
    /// the request and stores parsed information.
    ///
    /// This method must be called before retrieving parsed data using accessors
    /// such as @ref getMethod, @ref getUri etc.
    ///
    /// This method doesn't parse the HTTP request body.
    ///
    /// @throw HttpRequestError if the parsed request doesn't meet the specified
    /// requirements for it.
    virtual void create();

    /// @brief Complete parsing of the HTTP request.
    ///
    /// HTTP request parsing is performed in two stages: HTTP headers, then
    /// request body. The @ref create method parses HTTP headers. Once this is
    /// done, the caller can check if the "Content-Length" was specified and use
    /// it's value to determine the size of the body which is parsed in the
    /// second stage.
    ///
    /// This method generally performs the body parsing, but if it determines
    /// that the @ref create method hasn't been called, it calls @ref create
    /// before parsing the body.
    ///
    /// The derivations must call @ref create if it hasn't been called prior to
    /// calling this method. It must set @ref finalized_ to true if the call
    /// to @ref finalize was successful.
    virtual void finalize();

    /// @brief Reset the state of the object.
    virtual void reset();

    /// @name HTTP data accessors.
    ///
    //@{
    /// @brief Returns HTTP method of the request.
    Method getMethod() const;

    /// @brief Returns HTTP request URI.
    std::string getUri() const;

    /// @brief Returns HTTP version number (major and minor).
    HttpVersion getHttpVersion() const;

    /// @brief Returns a value of the specified HTTP header.
    ///
    /// @param header Name of the HTTP header.
    ///
    /// @throw HttpRequestError if the header doesn't exist.
    std::string getHeaderValue(const std::string& header) const;

    /// @brief Returns a value of the specified HTTP header as number.
    ///
    /// @param header Name of the HTTP header.
    ///
    /// @throw HttpRequestError if the header doesn't exist or if the
    /// header value is not number.
    uint64_t getHeaderValueAsUint64(const std::string& header) const;

    /// @brief Returns HTTP message body as string.
    std::string getBody() const;

    /// @brief Checks if the request has been successfully finalized.
    ///
    /// The request is gets finalized on successfull call to
    /// @ref HttpRequest::finalize.
    ///
    /// @return true if the request has been finalized, false otherwise.
    bool isFinalized() const {
        return (finalized_);
    }

    //@}

protected:

    /// @brief Checks if the @ref create was called.
    ///
    /// @throw HttpRequestError if @ref create wasn't called.
    void checkCreated() const;

    /// @brief Checks if the @ref finalize was called.
    ///
    /// @throw HttpRequestError if @ref finalize wasn't called.
    void checkFinalized() const;

    /// @brief Checks if the set is empty or the specified element belongs
    /// to this set.
    ///
    /// This is a convenience method used by the class to verify that the
    /// given HTTP method belongs to "required methods", HTTP version belongs
    /// to "required versions" etc.
    ///
    /// @param element Reference to the element.
    /// @param element_set Reference to the set of elements.
    /// @tparam Element type, e.g. @ref Method, @ref HttpVersion etc.
    ///
    /// @return true if the element set is empty or if the element belongs
    /// to the set.
    template<typename T>
    bool inRequiredSet(const T& element,
                       const std::set<T>& element_set) const;

    /// @brief Converts HTTP method specified in textual format to @ref Method.
    ///
    /// @param method HTTP method specified in the textual format. This value
    /// is case insensitive.
    ///
    /// @return HTTP method as enum.
    /// @throw HttpRequestError if unknown method specified.
    Method methodFromString(std::string method) const;

    /// @brief Converts HTTP method to string.
    ///
    /// @param method HTTP method specified as enum.
    ///
    /// @return HTTP method as string.
    std::string methodToString(const HttpRequest::Method& method) const;

    /// @brief Set of required HTTP methods.
    ///
    /// If the set is empty, all methods are allowed.
    std::set<Method> required_methods_;

    /// @brief Set of required HTTP versions.
    ///
    /// If the set is empty, all versions are allowed.
    std::set<HttpVersion> required_versions_;

    /// @brief Map holding required HTTP headers.
    ///
    /// The key of this map specifies the HTTP header name. The value
    /// specifies the HTTP header value. If the value is empty, the
    /// header is required but the value of the header is not checked.
    /// If the value is non-empty, the value in the HTTP request must
    /// be equal to the value in the map.
    std::map<std::string, std::string> required_headers_;

    /// @brief Flag indicating whether @ref create was called.
    bool created_;

    /// @brief Flag indicating whether @ref finalize was called.
    bool finalized_;

    /// @brief HTTP method of the request.
    Method method_;

    /// @brief Parsed HTTP headers.
    std::map<std::string, std::string> headers_;

    /// @brief Pointer to the @ref HttpRequestContext holding parsed
    /// data.
    HttpRequestContextPtr context_;
};

}
}

#endif
