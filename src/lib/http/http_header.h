// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace http {

/// @brief Represents HTTP header including a header name and value.
///
/// It includes methods for retrieving header name and value in lower case
/// and for case insensitive comparison of header values.
class HttpHeader {
public:

    /// @brief Constructor.
    ///
    /// @param header_name Header name.
    /// @param header_value Header value.
    explicit HttpHeader(const std::string& header_name,
                        const std::string& header_value = "");

    /// @brief Returns header name.
    std::string getName() const {
        return (header_name_);
    }

    /// @brief Returns header value.
    std::string getValue() const {
        return (header_value_);
    }

    /// @brief Returns header value as unsigned integer.
    ///
    /// @throw BadValue if the header value is not a valid number.
    uint64_t getUint64Value() const;

    /// @brief Returns lower case header name.
    std::string getLowerCaseName() const;

    /// @brief Returns lower case header value.
    std::string getLowerCaseValue() const;

    /// @brief Case insensitive comparison of header value.
    ///
    /// @param v Value to be compared.
    ///
    /// @return true if header value is equal, false otherwise.
    bool isValueEqual(const std::string& v) const;

private:

    std::string header_name_;  ///< Header name.
    std::string header_value_; ///< Header value.
};

/// @brief Pointer to the @c HttpHeader class.
typedef boost::shared_ptr<HttpHeader> HttpHeaderPtr;

/// @brief Represents HTTP Host header.
class HostHttpHeader : public HttpHeader {
public:

    /// @brief Constructor.
    ///
    /// @param header_value Host header value. The default is empty
    /// string.
    explicit HostHttpHeader(const std::string& header_value = "")
        : HttpHeader("Host", header_value) {
    }
};

/// @brief Pointer to the HTTP host header.
typedef boost::shared_ptr<HostHttpHeader> HostHttpHeaderPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif // HTTP_HEADER_H
