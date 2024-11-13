// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_HTTP_HEADER_H
#define CFG_HTTP_HEADER_H

#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/user_context.h>
#include <http/request.h>
#include <http/response.h>

namespace isc {
namespace http {

/// @brief Config HTTP header.
class CfgHttpHeader : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    std::string name_;
    std::string value_;

    /// @brief Constructor.
    ///
    /// @param name Header name.
    /// @param value Header value.
    CfgHttpHeader(const std::string& name, const std::string& value)
        : name_(name), value_(value) {
    }

    /// @brief Unparses config HTTP header.
    ///
    /// @return A pointer to unparsed header configuration.
    virtual isc::data::ElementPtr toElement() const;
};

/// @brief Collection of config HTTP headers.
typedef std::vector<CfgHttpHeader> CfgHttpHeaders;

/// @brief Copy config HTTP headers to message.
///
/// @tparam HTTP_MSG Either HttpRequest or HttpResponse.
/// @param headers Config HTTP headers.
/// @param message HTTP_MSG target object.
template<typename HTTP_MSG>
void copyHttpHeaders(const CfgHttpHeaders& headers, const HTTP_MSG& message) {
    for (auto const& header : headers) {
        message.context()->headers_.
            push_back(HttpHeaderContext(header.name_, header.value_));
    }
}

/// @brief Unparse config HTTP headers.
///
/// @param headers Config HTTP headers.
/// @return A pointer to unparsed headers configuration.
isc::data::ElementPtr toElement(const CfgHttpHeaders& headers);

/// @brief Parse config HTTP headers.
///
/// @param config Element holding the HTTP headers configuration.
/// @return The HTTP headers.
/// @throw DhcpConfigError when the configuration is invalid.
CfgHttpHeaders parseCfgHttpHeaders(const isc::data::ConstElementPtr& config);

} // namespace http
} // namespace isc

#endif
