// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_HEADER_CONTEXT_H
#define HTTP_HEADER_CONTEXT_H

#include <boost/lexical_cast.hpp>
#include <cstdint>
#include <string>

namespace isc {
namespace http {

/// @brief HTTP header context.
struct HttpHeaderContext {
    std::string name_;
    std::string value_;

    /// @brief Constructor.
    ///
    /// Sets header name and value to empty strings.
    HttpHeaderContext()
        : name_(), value_() {
    }

    /// @brief Constructor.
    ///
    /// @param name Header name.
    /// @param value Header value.
    HttpHeaderContext(const std::string& name, const std::string& value)
        : name_(name), value_(value) {
    }

    /// @brief Constructor.
    ///
    /// @param name Header name.
    /// @param value Numeric value for the header.
    HttpHeaderContext(const std::string& name, const int64_t value)
        : name_(name), value_(boost::lexical_cast<std::string>(value)) {
    }
};

} // namespace http
} // namespace isc

#endif
