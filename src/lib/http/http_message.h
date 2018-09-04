// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include <exceptions/exceptions.h>
#include <http/http_header.h>
#include <http/http_types.h>
#include <map>
#include <set>
#include <cstdint>
#include <string>

namespace isc {
namespace http {

/// @brief Generic exception thrown by @ref HttpMessage class.
class HttpMessageError : public Exception {
public:
    HttpMessageError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when attempt is made to retrieve a
/// non-existing header.
class HttpMessageNonExistingHeader : public HttpMessageError {
public:
    HttpMessageNonExistingHeader(const char* file, size_t line,
                                 const char* what) :
        HttpMessageError(file, line, what) { };
};


/// @brief Base class for @ref HttpRequest and @ref HttpResponse.
///
/// This abstract class provides a common functionality for the HTTP
/// requests and responses. Each such message can be marked as outbound
/// or inbound. An HTTP inbound request is the one received by the server
/// and HTTP inbound response is the response received by the client.
/// Conversely, an HTTP outbound request is the request created by the
/// client and HTTP outbound response is the response created by the
/// server. There are differences in how the inbound and outbound
/// messages are created. The inbound messages are received over the
/// TCP sockets and parsed by the parsers. The parsed information is
/// stored in a context, i.e. structure holding raw information and
/// associated with the given @c HttpMessage instance. Once the message
/// is parsed and all required information is stored in the context,
/// the @c create method is called to validate and fetch information
/// from the context into the message. The @c finalize method is called
/// to commit the HTTP message body into the message.
///
/// The outbound message is created locally from the known data, e.g.
/// HTTP version number, URI, method etc. The headers can be then
/// appended to the message via the context. In order to use this message
/// the @c finalize method must be called to commit this information.
/// Them, @c toString method can be called to generate the message in
/// the textual form, which can be transferred via TCP socket.
class HttpMessage {
public:

    /// @brief Specifies the direction of the HTTP message.
    enum Direction {
        INBOUND,
        OUTBOUND
    };

    /// @brief Constructor.
    ///
    /// @param direction Direction of the message (inbound or outbound).
    explicit HttpMessage(const Direction& direction);

    /// @brief Destructor.
    virtual ~HttpMessage();

    /// @brief Returns HTTP message direction.
    Direction getDirection() const {
        return (direction_);
    }

    /// @brief Sets direction for the HTTP message.
    ///
    /// This is mostly useful in unit testing.
    ///
    /// @param direction New direction of the HTTP message.
    void setDirection(const Direction& direction) {
        direction_ = direction;
    }

    /// @brief Specifies HTTP version allowed.
    ///
    /// Allowed HTTP versions must be specified prior to calling @ref create
    /// method. If no version is specified, all versions are allowed.
    ///
    /// @param version Version number allowed for the request.
    void requireHttpVersion(const HttpVersion& version);

    /// @brief Specifies a required HTTP header for the HTTP message.
    ///
    /// Required headers must be specified prior to calling @ref create method.
    /// The specified header must exist in the received HTTP request. This puts
    /// no requirement on the header value.
    ///
    /// @param header_name Required header name.
    void requireHeader(const std::string& header_name);

    /// @brief Specifies a required value of a header in the message.
    ///
    /// Required header values must be specified prior to calling @ref create
    /// method. The specified header must exist and its value must be equal to
    /// the value specified as second parameter.
    ///
    /// @param header_name HTTP header name.
    /// @param header_value HTTP header value.
    void requireHeaderValue(const std::string& header_name,
                            const std::string& header_value);

    /// @brief Checks if the body is required for the HTTP message.
    ///
    /// Current implementation simply checks if the "Content-Length" header
    /// is required.
    ///
    /// @return true if the body is required, false otherwise.
    bool requiresBody() const;

    /// @brief Reads parsed message from the context, validates the message and
    /// stores parsed information.
    ///
    /// This method must be called before retrieving parsed data using accessors.
    /// This method doesn't parse the HTTP request body.
    virtual void create() = 0;

    /// @brief Complete parsing HTTP message or creating an HTTP outbound message.
    ///
    /// This method is used in two situations: when a message has been received
    /// into a context and may be fully parsed (including the body) or when the
    /// data for the creation of the outbound message have been stored in a context
    /// and the message can be now created from the context.
    ///
    /// This method should call @c create method if it hasn't been called yet and
    /// then read the message body from the context and interpret it. If the body
    /// doesn't adhere to the requirements for the message (in particular, when the
    /// content type of the body is invalid) an exception should be thrown.
    virtual void finalize() = 0;

    /// @brief Reset the state of the object.
    virtual void reset() = 0;

    /// @brief Returns HTTP version number (major and minor).
    HttpVersion getHttpVersion() const;

    /// @brief Returns object encapsulating HTTP header.
    ///
    /// @param header_name HTTP header name.
    ///
    /// @return Non-null pointer to the header.
    /// @throw HttpMessageNonExistingHeader if header with the specified name
    /// doesn't exist.
    /// @throw HttpMessageError if the request hasn't been created.
    HttpHeaderPtr getHeader(const std::string& header_name) const;

    /// @brief Returns a value of the specified HTTP header.
    ///
    /// @param header_name Name of the HTTP header.
    ///
    /// @throw HttpMessageError if the header doesn't exist.
    std::string getHeaderValue(const std::string& header_name) const;

    /// @brief Returns a value of the specified HTTP header as number.
    ///
    /// @param header_name Name of the HTTP header.
    ///
    /// @throw HttpMessageError if the header doesn't exist or if the
    /// header value is not number.
    uint64_t getHeaderValueAsUint64(const std::string& header_name) const;

    /// @brief Returns HTTP message body as string.
    virtual std::string getBody() const = 0;

    /// @brief Returns HTTP message as text.
    ///
    /// This method is called to generate the outbound HTTP message. Make
    /// sure to call @c finalize prior to calling this method.
    virtual std::string toString() const = 0;

    /// @brief Checks if the message has been successfully finalized.
    ///
    /// The message gets finalized on successful call to @c finalize.
    ///
    /// @return true if the message has been finalized, false otherwise.
    bool isFinalized() const {
        return (finalized_);
    }

protected:

    /// @brief Checks if the @ref create was called.
    ///
    /// @throw HttpMessageError if @ref create wasn't called.
    void checkCreated() const;

    /// @brief Checks if the @ref finalize was called.
    ///
    /// @throw HttpMessageError if @ref finalize wasn't called.
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
    /// @tparam T Element type, @ref HttpVersion etc.
    ///
    /// @return true if the element set is empty or if the element belongs
    /// to the set.
    template<typename T>
    bool inRequiredSet(const T& element,
                       const std::set<T>& element_set) const {
        return (element_set.empty() || element_set.count(element) > 0);
    }

    /// @brief Message direction (inbound or outbound).
    Direction direction_;

    /// @brief Set of required HTTP versions.
    ///
    /// If the set is empty, all versions are allowed.
    std::set<HttpVersion> required_versions_;

    /// @brief HTTP version numbers.
    HttpVersion http_version_;

    /// @brief Map of HTTP headers indexed by lower case header names.
    typedef std::map<std::string, HttpHeaderPtr> HttpHeaderMap;

    /// @brief Map holding required HTTP headers.
    ///
    /// The key of this map specifies the lower case HTTP header name.
    /// If the value of the HTTP header is empty, the header is required
    /// but the value of the header is not checked. If the value is
    /// non-empty, the value in the HTTP request must be equal (case
    /// insensitive) to the value in the map.
    HttpHeaderMap required_headers_;

    /// @brief Flag indicating whether @ref create was called.
    bool created_;

    /// @brief Flag indicating whether @ref finalize was called.
    bool finalized_;

    /// @brief Parsed HTTP headers.
    HttpHeaderMap headers_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif // HTTP_MESSAGE_H
