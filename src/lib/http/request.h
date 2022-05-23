// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <hooks/callout_handle_associate.h>
#include <http/basic_auth.h>
#include <http/http_message.h>
#include <http/request_context.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>

namespace isc {
namespace http {

/// @brief Generic exception thrown by @ref HttpRequest class.
class HttpRequestError : public HttpMessageError {
public:
    HttpRequestError(const char* file, size_t line, const char* what) :
        HttpMessageError(file, line, what) { };
};

class HttpRequest;

/// @brief Pointer to the @ref HttpRequest object.
typedef boost::shared_ptr<HttpRequest> HttpRequestPtr;

/// @brief Represents HTTP request message.
///
/// This derivation of the @c HttpMessage class is specialized to represent
/// HTTP requests. This class provides two constructors for creating an inbound
/// and outbound request instance respectively. This class is associated with
/// an instance of the @c HttpRequestContext, which is used to provide request
/// specific values, such as: HTTP method, version, URI and headers.
///
/// The derivations of this class provide specializations and specify the
/// HTTP methods, versions and headers supported/required in the specific use
/// cases. For example, the @c PostHttpRequest class derives from @c HttpRequest
/// and it requires that request uses POST method. The @c PostHttpRequestJson,
/// which derives from @c PostHttpRequest requires that the POST message
/// includes body holding a JSON structure and provides methods to parse the
/// JSON body.
///
/// Objects of this class is used to record some parameters for access control:
///  - the remote address
///  - the use of TLS
///  - the first commonName of the SubjectName of the client certificate
///  - the first commonName of the IssuerName of the client certificate
///  - the user ID of the basic HTTP authentication
///  - a custom value
///
/// Callouts are associated to the request.
class HttpRequest : public HttpMessage, public hooks::CalloutHandleAssociate {
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

    /// @brief Constructor for inbound HTTP request.
    HttpRequest();

    /// @brief Constructor for outbound HTTP request.
    ///
    /// The constructor always includes Host header in the request, regardless
    /// of the HTTP version used.
    ///
    /// @param method HTTP method, e.g. POST.
    /// @param uri URI.
    /// @param version HTTP version.
    /// @param host_header Host header to be included in the request. The default
    /// is the empty Host header.
    /// @param basic_auth Basic HTTP authentication credential. The default
    /// is no authentication.
    HttpRequest(const Method& method, const std::string& uri, const HttpVersion& version,
                const HostHttpHeader& host_header = HostHttpHeader(),
                const BasicHttpAuthPtr& basic_auth = BasicHttpAuthPtr());

    /// @brief Returns pointer to the @ref HttpRequestContext.
    ///
    /// The context holds intermediate data for creating a request. The request
    /// parser stores parsed raw data in the context. When parsing is finished,
    /// the data are validated and committed into the @c HttpRequest.
    ///
    /// @return Pointer to the underlying @ref HttpRequestContext.
    const HttpRequestContextPtr& context() const {
        return (context_);
    }

    /// @brief Returns remote address.
    ///
    /// @return remote address from HTTP connection
    /// getRemote method.
    std::string getRemote() const {
        return (remote_);
    }

    /// @brief Set remote address.
    ///
    /// @param remote Remote end-point address in textual form.
    void setRemote(const std::string& remote) {
        remote_ = remote;
    }

    /// @brief Specifies an HTTP method allowed for the request.
    ///
    /// Allowed methods must be specified prior to calling @ref create method.
    /// If no method is specified, all methods are supported.
    ///
    /// @param method HTTP method allowed for the request.
    void requireHttpMethod(const HttpRequest::Method& method);

    /// @brief Commits information held in the context into the request.
    ///
    /// This function reads HTTP method, version and headers from the context
    /// and validates their values. For the outbound messages, it automatically
    /// appends Content-Length header to the request, based on the length of the
    /// request body.
    ///
    /// @throw HttpRequestError if the parsed request doesn't meet the specified
    /// requirements for it.
    virtual void create();

    /// @brief Completes creation of the HTTP request.
    ///
    /// This method marks the message as finalized. The outbound request may now be
    /// sent over the TCP socket. The information from the inbound message may be
    /// read, including the request body.
    virtual void finalize();

    /// @brief Reset the state of the object.
    virtual void reset();

    /// @brief Returns HTTP method of the request.
    Method getMethod() const;

    /// @brief Returns HTTP request URI.
    std::string getUri() const;


    /// @brief Returns HTTP message body as string.
    std::string getBody() const;

    /// @brief Returns HTTP method, URI and HTTP version as a string.
    std::string toBriefString() const;

    /// @brief Returns HTTP message as string.
    ///
    /// This method is called to generate the outbound HTTP message. Make
    /// sure to call @c finalize prior to calling this method.
    virtual std::string toString() const;

    /// @brief Checks if the client has requested persistent connection.
    ///
    /// For the HTTP/1.0 case, the connection is persistent if the client has
    /// included Connection: keep-alive header. For the HTTP/1.1 case, the
    /// connection is assumed to be persistent unless Connection: close header
    /// has been included.
    ///
    /// @return true if the client has requested persistent connection, false
    /// otherwise.
    bool isPersistent() const;

    /// Access control parameters: get/set methods.

    /// @brief Returns recorded TLS usage.
    ///
    /// @return recorded TLS usage.
    bool getTls() const {
        return (tls_);
    }

    /// @brief Set (record) TLS usage.
    ///
    /// @param tls the TLS usage.
    void setTls(bool tls) {
        tls_ = tls;
    }

    /// @brief Returns recorded subject name.
    ///
    /// @return recorded subject name.
    std::string getSubject() const {
        return (subject_);
    }

    /// @brief Set (record) subject name.
    ///
    /// @param subject the subject name.
    void setSubject(const std::string& subject) {
        subject_ = subject;
    }

    /// @brief Returns recorded issuer name.
    ///
    /// @return recorded issuer name.
    std::string getIssuer() const {
        return (issuer_);
    }

    /// @brief Set (record) issuer name.
    ///
    /// @param issuer the issuer name.
    void setIssuer(const std::string& issuer) {
        issuer_ = issuer;
    }

    /// @brief Returns recorded basic auth.
    ///
    /// @return recorded basic auth.
    std::string getBasicAuth() const {
        return (basic_auth_);
    }

    /// @brief Set (record) basic auth.
    ///
    /// @param basic_auth the basic auth.
    void setBasicAuth(const std::string& basic_auth) {
        basic_auth_ = basic_auth;
    }

    /// @brief Returns recorded custom name.
    ///
    /// @return recorded custom name.
    std::string getCustom() const {
        return (custom_);
    }

    /// @brief Set (record) custom name.
    ///
    /// @param custom the custom name.
    void setCustom(const std::string& custom) {
        custom_ = custom;
    }

    /// Access control parameters: Flags which indicate what information to record.
    /// Remote address and TLS usage are always recorded.

    /// @brief Record subject name.
    static bool recordSubject_;

    /// @brief Record issuer name.
    static bool recordIssuer_;

    /// @brief Record basic auth.
    static bool recordBasicAuth_;

protected:

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

    /// @brief HTTP method of the request.
    Method method_;

    /// @brief Pointer to the @ref HttpRequestContext holding parsed
    /// data.
    HttpRequestContextPtr context_;

    /// @brief Remote address.
    std::string remote_;

    /// @brief TLS usage.
    bool tls_;

    /// @brief Subject name.
    std::string subject_;

    /// @brief Issuer name.
    std::string issuer_;

    /// @brief Basic auth.
    std::string basic_auth_;

    /// @brief Custom name.
    std::string custom_;
};

}
}

#endif
